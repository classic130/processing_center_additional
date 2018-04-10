// Implements the CDataAccess class

#include "stdafx.h"
#include <comutil.h>
#include <wininet.h>
#include "ptav3.h"
#include "nzdatacc.h"
#include "nzmacros.h"
#include "nzerrs.h"
#include "nzdefines.h"
#include "notarize.h"
#include "nzutils.h"

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
		if(m_bstrProtocol == _bstr_t("http") || m_bstrProtocol == _bstr_t("https"))
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
HRESULT CDataAccess::Open(const _bstr_t& i_bstrDocument, const AccessMode i_aMode, const _bstr_t& i_bstrUAgent)
{
	HRESULT hr = S_OK;
	DWORD dwLastError = 0, dwAccessMode = 0, dwCreateMode = 0;

	do
	{
		CHECK_NULL_PTR_BREAK(i_bstrDocument)

		if(i_bstrDocument == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
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
				hr = E_NZINVALIDARGS;
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
			if(!_strnicmp(i_bstrDocument, "https://", 8))
			{
				m_bstrProtocol = "https";
				pString += 8;
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
					hr = E_NZDOCNOACCESS;
				else
					if(dwLastError == ERROR_FILE_EXISTS)
						hr = E_NZDOCEXISTS;
					else
						if(dwLastError == ERROR_SHARING_VIOLATION)
							hr = E_NZDOCSHARE;
						else
							hr = E_NZDOCOPENFAILED;

				break;
			}
		}
		else
			if(m_bstrProtocol == _bstr_t("http") || m_bstrProtocol == _bstr_t("https"))
			{
				_bstr_t bstrServerName = "", bstrServerObject = "";
				DWORD dwPortNum = 0, dwStatusCodeSize = 0, dwStatusCode = 0, dwFlags = 0;
				char *pcszHttpHeaders = NULL;

				hr = _ParseServerPath(i_bstrDocument, &bstrServerName, &bstrServerObject, &dwPortNum);
				CHECK_HRESULT_BREAK
				
				m_hOpen = InternetOpen(i_bstrUAgent, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
				if(!m_hOpen)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "InternetOpen() failed.", NULL, dwLastError);
					hr = E_NZINETOPENERR;
					break;
				}

				m_hConnect = InternetConnect(m_hOpen, bstrServerName, (USHORT)dwPortNum, "", "", INTERNET_SERVICE_HTTP, 0, 0);
				if(!m_hConnect)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "InternetConnect() failed.", NULL, dwLastError);
					hr = E_NZINETCONNECTERR;
					break;
				}

				dwFlags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;
				if(m_bstrProtocol == _bstr_t("https"))
					dwFlags |= INTERNET_FLAG_SECURE;

				m_hRequest = HttpOpenRequest(m_hConnect, "GET", bstrServerObject, TEXT("HTTP/1.0")/*TEXT("HTTP/1.1")*/, NULL, NULL,
								   dwFlags, NULL);
				if(!m_hRequest)
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpOpenRequest() failed.", NULL, dwLastError);
					hr = E_NZINETREQUESTERR;
					break;
				}

				// try to figure out whether the browser is IE or Netscape from the user-agent.
				
				if (myStrStr(i_bstrUAgent, IE_USERAGENT))
				{
					// the browser is IE.
					pcszHttpHeaders = IE_HTTP_HEADERS;
				}
				else if (myStrStr(i_bstrUAgent, NS_USERAGENT))
				{
					// the browser is probably netscape.
					pcszHttpHeaders = NS_HTTP_HEADERS;
				}
				else
				{
					// it is some other browser. Set it to Netscape headers.
					pcszHttpHeaders = NS_HTTP_HEADERS;
				}

				if (!HttpAddRequestHeaders(m_hRequest, pcszHttpHeaders, 
						lstrlen(pcszHttpHeaders), HTTP_ADDREQ_FLAG_ADD|HTTP_ADDREQ_FLAG_REPLACE))
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpAddRequestHeaders() failed.", NULL, dwLastError);
					hr = E_NZINETREQUESTERR;
					break;
				};

				if(!HttpSendRequest(m_hRequest, 0, 0, 0, 0))
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpSendRequest() failed.", NULL, dwLastError);

					if(dwLastError == ERROR_INTERNET_CLIENT_AUTH_CERT_NEEDED)
						hr = E_NZCAUTHNEEDED;
					else
						if(dwLastError == ERROR_INTERNET_SEC_CERT_DATE_INVALID || 
							dwLastError == ERROR_INTERNET_SEC_CERT_CN_INVALID ||
							dwLastError == ERROR_INTERNET_SEC_INVALID_CERT || 
							dwLastError == ERROR_INTERNET_SEC_CERT_REVOKED)
							hr = E_NZSECCERT;	
						else
							hr = E_NZINETSENDERR;

					break;
				}

				dwStatusCodeSize = sizeof(DWORD);
				if(!HttpQueryInfo(m_hRequest, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER, &dwStatusCode, &dwStatusCodeSize, NULL))
				{
					dwLastError = GetLastError();
					_LogErrorMsg("CDataAccess::Open().", "HttpQueryInfo() failed.", NULL, dwLastError);
					hr = E_NZINETQUERYERR;
					break;
				}

				if(dwStatusCode != HTTP_STATUS_OK)
				{
					_LogErrorMsg("CDataAccess::Open().", "Server error occured.", NULL, dwStatusCode);
					hr = E_NZINETBADSTAT;
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
				hr = E_NZDOCNOTOPENED;
				break;
			}

			if(!ReadFile(m_hFile, o_pbBytesRead, *io_dwBytesRead, &dwBytesRead, NULL))
			{
				dwLastError = GetLastError();
				*io_dwBytesRead = 0;
				_LogErrorMsg("CDataAccess::Read().", "Error reading file.", NULL, dwLastError);
				hr = E_NZDOCREADFAILED;
				break;
			}

			*io_dwBytesRead = dwBytesRead;
		}
		else
			if(m_bstrProtocol == _bstr_t("http") || m_bstrProtocol == _bstr_t("https"))
			{
				if(!m_hRequest)
				{
					hr = E_NZDOCNOTOPENED;
					break;
				}

				if(!InternetReadFile(m_hRequest, (LPVOID)o_pbBytesRead, *io_dwBytesRead, &dwBytesRead))
				{
					dwLastError = GetLastError();
					*io_dwBytesRead = 0;
					_LogErrorMsg("CDataAccess::Read().", "InternetReadFile() failed.", NULL, dwLastError);
					hr = E_NZINETREADERR;
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
				hr = E_NZDOCNOTOPENED;
				break;
			}

			if(!WriteFile(m_hFile, i_pbData, i_dwDataLen, &dwBytesWritten, NULL))
			{
				dwLastError = GetLastError();
				_LogErrorMsg("CDataAccess::Write().", "Error writing file.", NULL, dwLastError);
				hr = E_NZDOCWRITEFAILED;
				break;
			}

			if(o_pdwBytesWritten)
				*o_pdwBytesWritten = dwBytesWritten;
		}
		else
			if(m_bstrProtocol == _bstr_t("http") || m_bstrProtocol == _bstr_t("https"))
			{
				_LogErrorMsg("CDataAccess::Write().", "Write using http protocol not supported.", NULL, 0);
				hr = E_NZTYPENOTSUPPORTED;
				break;
			}

	}while(0);

	return hr;
}