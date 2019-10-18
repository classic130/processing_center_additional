// Implements the CDataAccess class

#include "stdafx.h"
#include <comutil.h>
#include <wininet.h>
#include "datacc.h"
#include "macros.h"
#include "vsserrs.h"
#include "propsht.h"
#include "util.h"

// Constructor
CDataAccess::CDataAccess()
{
	m_bstrProtocol = "";
	m_hFile = NULL;
	m_hOpen = NULL;
	m_hConnect = NULL;
	m_hRequest = NULL;
}


// Destructor
CDataAccess::~CDataAccess()
{
	Close();
	m_bstrProtocol = "";
}


/*
Working -	Depending on the protocol the appropriate file handles are closed by this function.
*/
VOID CDataAccess::Close()
{
	if(m_bstrProtocol == _bstr_t("file"))
	{
		if(m_hFile && m_hFile != INVALID_HANDLE_VALUE)
			CloseHandle(m_hFile);
			
		m_hFile = NULL;
	}
	else
		if(m_bstrProtocol == _bstr_t("http"))
		{
			CLOSE_INET_HANDLE(m_hRequest)
			CLOSE_INET_HANDLE(m_hConnect)
			CLOSE_INET_HANDLE(m_hOpen)
		}
}


/*
I/P -	'i_bstrDocument'	:	Is the URL to be opened. It can be of the form 'file://c:\....' or
								'http://www.....' or 'd:\temp\...'
		'i_aMode'	:	Is the mode in which the document needs to be opened. Valid modes are
						read, write, over-write, read-write.
Working -	This function opens the document specified by 'i_bstrDocument' and stores the handle to
			the open document. It stores the protocol in the 'm_bstrProtocol' member variable.
Return -	An hresult indicating the status of the operation. 'S_OK' on success.
*/
HRESULT CDataAccess::Open(const _bstr_t& i_bstrDocument, const AccessMode i_aMode)
{
	HRESULT hr = S_OK;
	DWORD dwLastError = 0, dwAccessMode = 0, dwCreateMode = 0;

	do
	{
		CHECK_NULL_PTR_BREAK(i_bstrDocument)

		if(i_bstrDocument == _bstr_t(""))
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		switch(i_aMode)
		{
			case ACCESS_READ:
			{
				dwAccessMode = GENERIC_READ;
				dwCreateMode = OPEN_EXISTING;
				break;
			}

			case ACCESS_WRITE:
			{
				dwAccessMode = GENERIC_WRITE;
				dwCreateMode = CREATE_NEW;
				break;
			}

			case ACCESS_OVERWRITE:
			{
				dwAccessMode = GENERIC_WRITE;
				dwCreateMode = CREATE_ALWAYS;
				break;
			}

			case ACCESS_READWRITE:
			{
				dwAccessMode = GENERIC_READ | GENERIC_WRITE;
				dwCreateMode = OPEN_EXISTING;
				break;
			}

			default:
			{
				hr = E_VSSCODE_INVALIDARGS;
				break;
			}
		}

		CHECK_HRESULT_BREAK
	
		LPCTSTR pString = i_bstrDocument;
		m_bstrProtocol = "file";				// Default protocol is 'file'
		m_hFile = NULL;
		m_hOpen = NULL;
		m_hConnect = NULL;
		m_hRequest = NULL;
			
		if(!_strnicmp(i_bstrDocument, "http://", 7))
		{
			m_bstrProtocol = "http";
			pString += 7;
		}
		else
			if(!_strnicmp(i_bstrDocument, "file://", 7))
				pString += 7;


		if(m_bstrProtocol == _bstr_t("file"))
		{
			// Open the file and store the handle in the member variable
			m_hFile = CreateFile(pString, dwAccessMode, 0, NULL, dwCreateMode, FILE_ATTRIBUTE_ARCHIVE, NULL);
			if(m_hFile == INVALID_HANDLE_VALUE)
			{
				dwLastError = GetLastError();
				_LogErrorMsg("CDataAccess::Open()", "Error opening file \'%s\'", pString, dwLastError);

				if(dwLastError == ERROR_ACCESS_DENIED)
					hr = E_VSSCODE_DOCNOACCESS;
				else
					if(dwLastError == ERROR_FILE_EXISTS)
						hr = E_VSSCODE_DOCEXISTS;
					else
						if(dwLastError == ERROR_SHARING_VIOLATION)
							hr = E_VSSCODE_DOCSHARE;
						else
							hr = E_VSSCODE_DOCOPENFAILED;

				break;
			}
		}
		else
			if(m_bstrProtocol == _bstr_t("http"))
			{
				_bstr_t bstrServerName = "", bstrServerObject = "";
				DWORD dwPortNum = 0, dwStatusCodeSize = 0, dwStatusCode = 0;

				hr = ParseServerPath(i_bstrDocument, &bstrServerName, &bstrServerObject, &dwPortNum);
				CHECK_HRESULT_BREAK
				
				m_hOpen = InternetOpen("", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
				if(!m_hOpen)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "InternetOpen() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETOPENERR;
					break;
				}

				m_hConnect = InternetConnect(m_hOpen, bstrServerName, (USHORT)dwPortNum, "", "", INTERNET_SERVICE_HTTP, 0, 0);
				if(!m_hConnect)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "InternetConnect() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETCONNECTERR;
					break;
				}

				m_hRequest = HttpOpenRequest(m_hConnect, "GET", bstrServerObject, TEXT("HTTP/1.1"), NULL, NULL,
								   INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE, NULL);
				if(!m_hRequest)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpOpenRequest() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETREQUESTERR;
					break;
				}

				if(!HttpSendRequest(m_hRequest, NULL, 0, 0, 0))
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpSendRequest() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETSENDERR;
					break;
				}

				dwStatusCodeSize = sizeof(DWORD);
				if(!HttpQueryInfo(m_hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatusCode, &dwStatusCodeSize, NULL))
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpQueryInfo() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETQUERYERR;
					break;
				}

				if(dwStatusCode != HTTP_STATUS_OK)
				{
					_LogErrorMsg("CDataAccess::Open().", "Server error occured.", NULL, dwStatusCode);
					hr = E_VSSCODE_INETBADSTAT;
					break;
				}
			}
	
	}while(0);

	if(hr != S_OK)
	{
		Close();
		m_bstrProtocol = "";
	}
	
	return hr;
}


/*
I/P -	'io_dwBytesRead'	:	Holds the size of 'o_pbBytesRead' on input
O/P -	'o_pbBytesRead'	:	Is the variable which will store the data that has been read. It
							is allocated by the calling function. 
	-	'io_dwBytesRead'	:	Is an I/O parameter. On input it holds the size of 'o_pbBytesRead', on
								output it contains the bytes actually read. If the number of bytes
								read is less than the number of bytes requested then end of file 
								has been reached.
Return -	An hresult indicating the status of the operation. 'S_OK' on success.
Working -	This function reads the data appropriately depending on the protocol.
*/
HRESULT CDataAccess::Read(LPBYTE o_pbBytesRead, DWORD* io_dwBytesRead)
{
	HRESULT hr = S_OK;
	DWORD dwBytesRead = 0, dwLastError = 0;

	do
	{
		CHECK_NULL_PTR_BREAK(o_pbBytesRead)
		CHECK_NULL_PTR_BREAK(io_dwBytesRead)

		if(m_bstrProtocol == _bstr_t("file"))
		{
			if(!m_hFile)
			{
				hr = E_VSSCODE_DOCNOTOPENED;
				break;
			}

			if(!ReadFile(m_hFile, o_pbBytesRead, *io_dwBytesRead, &dwBytesRead, NULL))
			{
				dwLastError = GetLastError();
				*io_dwBytesRead = 0;
				_LogErrorMsg("CDataAccess::Read().", "Error reading file.", NULL, dwLastError);
				hr = E_VSSCODE_DOCREADFAILED;
				break;
			}

			*io_dwBytesRead = dwBytesRead;
		}
		else
			if(m_bstrProtocol == _bstr_t("http"))
			{
				if(!m_hRequest)
				{
					hr = E_VSSCODE_DOCNOTOPENED;
					break;
				}

				if(!InternetReadFile(m_hRequest, (LPVOID)o_pbBytesRead, *io_dwBytesRead, &dwBytesRead))
				{
					dwLastError = GetLastError();
					*io_dwBytesRead = 0;
					_LogErrorMsg("CDataAccess::Read().", "InternetReadFile() failed.", NULL, dwLastError);
					hr = E_VSSCODE_INETREADERR;
					break;
				}

				*io_dwBytesRead = dwBytesRead;
			}
		
	}while(0);

	return hr;
}


/*
I/P -	'i_pbData'	:	Is the data to be written.
		'i_dwDataLen'	:	Number of bytes of data to be written.
O/P -	'o_pdwBytesWritten'	:	Number of bytes of data actually written(optional).
Return -	An hresult indicating the status of the operation. 'S_OK' on success.	
Working -	Writes the data to the file depending on the protocol.
*/
HRESULT CDataAccess::Write(const LPBYTE i_pbData, const DWORD i_dwDataLen, LPDWORD o_pdwBytesWritten)
{
	HRESULT hr = S_OK;
	DWORD dwBytesWritten = 0, dwLastError = 0;

	do
	{
		CHECK_NULL_PTR_BREAK(i_pbData)

		if(i_dwDataLen == 0)
			break;

		if(m_bstrProtocol == _bstr_t("file"))
		{
			if(!m_hFile)
			{
				hr = E_VSSCODE_DOCNOTOPENED;
				break;
			}

			if(!WriteFile(m_hFile, i_pbData, i_dwDataLen, &dwBytesWritten, NULL))
			{
				dwLastError = GetLastError();
				_LogErrorMsg("CDataAccess::Write().", "Error writing file.", NULL, dwLastError);
				hr = E_VSSCODE_DOCWRITEFAILED;
				break;
			}

			if(o_pdwBytesWritten)
				*o_pdwBytesWritten = dwBytesWritten;
		}
		else
			if(m_bstrProtocol == _bstr_t("http"))
			{

			}

	}while(0);

	return hr;
}


HRESULT CDataAccess::GetSize(LPDWORD o_pdwSize)
{
	HRESULT hr = S_OK;
	DWORD dwSize = 0, dwLastError = 0;

	do
	{
		CHECK_NULL_PTR_BREAK(o_pdwSize)

		if(m_bstrProtocol == _bstr_t("file"))
		{
			if(!m_hFile)
			{
				hr = E_VSSCODE_DOCNOTOPENED;
				break;
			}

			if((dwSize = GetFileSize(m_hFile, NULL)) == -1)
			{
				dwLastError = GetLastError();
				_LogErrorMsg("CDataAccess::GetSize().", "Error obtaining file size.", NULL, dwLastError);
				hr = E_VSSCODE_DOCSIZEFAILED;
				break;
			}

			*o_pdwSize = dwSize;
		}
		else
			if(m_bstrProtocol == _bstr_t("http"))
			{

			}

	}while(0);

	return hr;
}