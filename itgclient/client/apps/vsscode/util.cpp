#include "stdafx.h"
#include <comutil.h>
#include <wininet.h>
#include "propsht.h"
#include "util.h"
#include "resource.h"
#include "macros.h"
#include "vsserrs.h"
#include "certmgmt.h"
#include "settings.h"
#include "ptaerrs.h"


/*
I/P -	'i_pErrLocation'	:	Function where the error occurred.
		'i_pErrDesc'	:	Description of the error.
		'i_pErrParam'	:	Any parameter which can be added to a formatted 'i_pErrDesc' string
		'i_dwErrCode'	:	An hresult or any Windows error that may have occurred.
Working -	Creates a log file at the location specified by 'VS_NZLOGFILE' and writes a well
			formatted error string. In addition to the above information this function also 
			writes the Windows user and the time when error occurred.
*/
VOID _LogErrorMsg(LPCTSTR i_pErrLocation, LPCTSTR i_pErrDesc, LPCTSTR i_pErrParam, DWORD i_dwErrCode)
{
	// Read registry key to check if error logging is enabled
	HKEY hKey = NULL;
	LONG lResult = 0;
	DWORD dwLogError = 0, dwSize = sizeof(dwLogError);

	lResult = RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_REG_KEY, 0, KEY_QUERY_VALUE, &hKey);
	if(lResult != ERROR_SUCCESS)
		return;

	lResult = RegQueryValueEx(hKey, LOG_ERROR, NULL, NULL, (LPBYTE)&dwLogError, &dwSize);
	
	RegCloseKey(hKey);
	hKey = NULL;

	if(lResult != ERROR_SUCCESS || dwLogError == 0)
		return;

	HANDLE hLogFile = NULL;
	TCHAR szErrString[ERR_STRING_LEN], szUserName[MAX_STRING_LEN], szErrDescription[MAX_STRING_LEN];
	DWORD dwUserName = sizeof(szUserName), dwBytesWritten = 0;
	SYSTEMTIME sysTime;

	do
	{
		hLogFile = CreateFile(LOGFILE, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hLogFile == INVALID_HANDLE_VALUE)
			break;

		// Seek to the end of the file
		if(SetFilePointer(hLogFile, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER)
			break;

		// Get the logged on user name
		if(!GetUserName(szUserName, &dwUserName))
			lstrcpy(szUserName, "default");

		// Get the local time
		GetLocalTime(&sysTime);

		if(i_pErrParam)
			wsprintf(szErrDescription, i_pErrDesc, i_pErrParam);
		else
			lstrcpy(szErrDescription, i_pErrDesc);

		wsprintf(szErrString, "%s - %s : %d:%d,  %d:%d:%d : %s : %x.\r\n", i_pErrLocation, szUserName, sysTime.wHour, sysTime.wMinute, sysTime.wYear, sysTime.wMonth, sysTime.wDay, szErrDescription, i_dwErrCode);

		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

	}while(0);

	if(hLogFile && hLogFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hLogFile);
		hLogFile = NULL;
	}
	
	return;
}


HRESULT GetOpenFileNames(UINT i_idOFTitle, UINT i_idOFFilter, BOOL i_bMultipleSel, _bstr_t** o_pptbstrSelFiles, DWORD* o_pdwNumFiles)
{
	HRESULT hr = S_OK;
	OPENFILENAME ofn;
	_bstr_t tbstrFilter = "", tbstrTitle = "";
	WCHAR* pwcharFilter = NULL, *pwcharTitle = NULL;
	TCHAR* tcharFilter = NULL, *pCurrentFile = NULL, szSelFiles[MAX_SEL_FILES], szSelFolder[MAX_FILE_SIZE];
	DWORD dwError = 0, dwSelFiles = 0;

	do
	{
		if(!o_pptbstrSelFiles || !o_pdwNumFiles)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		*o_pptbstrSelFiles = NULL;
		*o_pdwNumFiles = 0;

		szSelFiles[0] = NULL;

		memset(&ofn, 0, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = GetFocus();

		hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), i_idOFFilter, &pwcharFilter);
		CHECK_HRESULT_BREAK

		tbstrFilter = pwcharFilter;
		tcharFilter =  (TCHAR*) malloc(lstrlen((TCHAR*)tbstrFilter) + 8);
		CHECK_MEM_BREAK(tcharFilter)

		lstrcpy(tcharFilter, (TCHAR*)tbstrFilter);

		if(i_idOFFilter == IDS_FILE_FILTER)
			memcpy(tcharFilter + lstrlen((TCHAR*)tbstrFilter), (BYTE*)"\0*.img\0\0", 8);
		else
			if(i_idOFFilter == IDS_FILE_FILTER2)
				memcpy(tcharFilter + lstrlen((TCHAR*)tbstrFilter), (BYTE*)"\0*.*\0\0", 6);
			else
				memcpy(tcharFilter + lstrlen((TCHAR*)tbstrFilter), (BYTE*)"\0*.pfx\0\0", 8);

		ofn.lpstrFilter = (TCHAR*)tcharFilter;

		ofn.nFilterIndex = 1;
		ofn.lpstrFile = szSelFiles;
		ofn.nMaxFile = sizeof(szSelFiles);

		hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID() , i_idOFTitle, &pwcharTitle);
		CHECK_HRESULT_BREAK

		tbstrTitle = pwcharTitle;
		ofn.lpstrTitle = (CHAR*)tbstrTitle;

		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER | OFN_HIDEREADONLY;
		if(i_bMultipleSel)
			ofn.Flags |= OFN_ALLOWMULTISELECT;

		if(!GetOpenFileName(&ofn))
		{
			dwError = CommDlgExtendedError();
			_LogErrorMsg("GetOpenFileNames().", "GetOpenFileName() api failed.", NULL, dwError);
			hr = E_VSSCODE_GETOPENFILERR;
			break;
		}

		if(i_bMultipleSel == TRUE)
		{
			// Get the folder name
			memcpy(szSelFolder, szSelFiles, ofn.nFileOffset);
			if(szSelFolder[ofn.nFileOffset - 1] == '\\')
				szSelFolder[ofn.nFileOffset - 1] = '\0';

			// Find the total number of files that were selected
			pCurrentFile = &szSelFiles[ofn.nFileOffset];
			pCurrentFile = strchr(pCurrentFile, '\0');

			do
			{
				dwSelFiles++;

				pCurrentFile++;

				if(!pCurrentFile)
					break;

				if(*pCurrentFile == '\0')	// last file found
					break;

				pCurrentFile = strchr(pCurrentFile, '\0');

			}while(pCurrentFile);

			*o_pptbstrSelFiles = (_bstr_t*) new _bstr_t[dwSelFiles];
			CHECK_MEM_BREAK(*o_pptbstrSelFiles)

			*o_pdwNumFiles = dwSelFiles;

			pCurrentFile = &szSelFiles[ofn.nFileOffset];

			for(UINT i = 0; i < dwSelFiles; i++)
			{
				(*o_pptbstrSelFiles)[i] = szSelFolder;
				(*o_pptbstrSelFiles)[i] += "\\";
				(*o_pptbstrSelFiles)[i] += pCurrentFile;

				pCurrentFile = strchr(pCurrentFile, '\0');
				pCurrentFile++;
			}
		}
		else
		{
			*o_pptbstrSelFiles = (_bstr_t*) new _bstr_t;
			CHECK_MEM_BREAK(*o_pptbstrSelFiles)

			*o_pdwNumFiles = 1;

			(*o_pptbstrSelFiles)[0] = szSelFiles;
		}

	}while(0);

	FREE_MEMORY(pwcharFilter)
	FREE_MEMORY(tcharFilter)
	FREE_MEMORY(pwcharTitle)

	return hr;
}


HRESULT LoadStringW(HINSTANCE i_hInst, DWORD i_dwLangId, INT i_nStringID, WCHAR** o_wstrOutBuff)
{
	HRSRC hRes;
	HGLOBAL hGlobal;
	PBYTE pbyteStringTable;
	WORD* pdwTempPtr;
	INT i;
	WORD wStringLen;

	*o_wstrOutBuff = NULL;

	// Find the string table resource
	hRes = FindResourceEx(i_hInst, RT_STRING, (LPTSTR)(i_nStringID/16+1), (WORD)i_dwLangId);
	if(!hRes)
		return E_FAIL;
	
	// Load the resource
	hGlobal = LoadResource(i_hInst, hRes);
	if(!hGlobal)
		return E_VSSCODE_OUTOFMEMORY;

	// Get the string table
	pbyteStringTable = (PBYTE)LockResource(hGlobal);

	// Get to the right string in the string table
	pdwTempPtr = (WORD*)pbyteStringTable;
	wStringLen = 0;
	for(i= 0; i< (i_nStringID % 16) + 1; ++i)
	{
		// Read the length of the string
		pdwTempPtr = pdwTempPtr + wStringLen;
		wStringLen = (WORD)(*pdwTempPtr);
		pdwTempPtr++;
	}

	// Read the string
	*o_wstrOutBuff = (WCHAR*)malloc(sizeof(WCHAR)*(wStringLen + 1));

	if(!*o_wstrOutBuff)
		return E_VSSCODE_OUTOFMEMORY;

	memcpy((void*)*o_wstrOutBuff, (void*)pdwTempPtr, sizeof(WCHAR)*wStringLen);
	(*o_wstrOutBuff)[wStringLen] = 0x0000;

	return S_OK;
}


DWORD _GetDefaultLangID(VOID)
{
	DWORD dwRetVal;

	dwRetVal = GetSystemDefaultLangID();
	if(!_IsLangSupported(dwRetVal))
		dwRetVal= LANG_ENGLISH_US;

	return dwRetVal;
}



BOOL _IsLangSupported(DWORD i_dwLangID)
{
	switch(i_dwLangID)
	{
		case LANG_ENGLISH_US :
			return TRUE;

		default :
			return FALSE;
	}
}


/*
I/P -	'i_pbstrServerPath'	:	Is of the form http(s)://server[:port]/object.
O/P -	'o_pbstrServerName'	:	Is the server name obtained from the input path.
		'o_pbstrServerObject'	:	Is the object obtained from the input path.
		'o_pdwPortNum'	:	Is the port number obtained from the input path. If no port
							number is specified, it is set to 'INTERNET_DEFAULT_HTTP_PORT'
Return -	An hresult indicating the status of the operation.
Working -	This function parses the server path into 3 components, server name, server port
			and server object.
*/
HRESULT ParseServerPath(const _bstr_t& i_pbstrServerPath, _bstr_t* o_pbstrServerName, _bstr_t* o_pbstrServerObject,
						LPDWORD o_pdwPortNum)
{
	HRESULT hr = S_OK;
	TCHAR* pPath = NULL;
	WCHAR* pwszServerPath = NULL;
	WCHAR pwTemp[2];
	UINT uServerPathLen = 0, uIndex = 0;
	_bstr_t bstrServerName = "", bstrServerObject = "", bstrServerPort = "";

	do
	{
		if(!i_pbstrServerPath || !o_pbstrServerName || !o_pbstrServerObject || !o_pdwPortNum)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_pbstrServerPath == _bstr_t(""))
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		*o_pbstrServerName = "";
		*o_pbstrServerObject = "";
		*o_pdwPortNum = INTERNET_DEFAULT_HTTP_PORT;

		pwszServerPath = i_pbstrServerPath.copy();
		uServerPathLen = i_pbstrServerPath.length();

		if(!_wcsnicmp(pwszServerPath, L"http", 4))
		{
			uIndex = 4;

			if(pwszServerPath[uIndex] == L's' || pwszServerPath[uIndex] == L'S')
				uIndex++;

			if(uServerPathLen <= uIndex + 3)
			{
				hr = E_VSSCODE_INVALIDPATH;
				break;
			}

			if(pwszServerPath[uIndex] != L':' || pwszServerPath[uIndex + 1] != L'/' || pwszServerPath[uIndex + 2] != L'/')
			{
				hr = E_VSSCODE_INVALIDPATH;
				break;
			}
			
			uIndex += 3;
		}

		// Search for ':' or '/'
		for(UINT i = uIndex; i < uServerPathLen; i++)
		{
			if(pwszServerPath[i] == L':')
				break;

			if(pwszServerPath[i] == L'/')
			{
				bstrServerObject = &pwszServerPath[i + 1];
				break;
			}
			
			pwTemp[0] = pwszServerPath[i];
			pwTemp[1] = NULL;

			bstrServerName += pwTemp;
		}

		if(pwszServerPath[i] == L':')
		{
			for(i++; i < uServerPathLen; i++)
			{
				if(pwszServerPath[i] == L'/')
				{
					bstrServerObject = &pwszServerPath[i + 1];
					break;
				}

				pwTemp[0] = pwszServerPath[i];
				pwTemp[1] = NULL;

				bstrServerPort += pwTemp;
			}
		}

	}while(0);

	if(hr == S_OK)
	{
		*o_pbstrServerName = bstrServerName.copy();
		*o_pbstrServerObject = bstrServerObject.copy();

		if(bstrServerPort != _bstr_t(""))
			*o_pdwPortNum = atoi(bstrServerPort);
	}

	SYS_FREE_MEMORY(pwszServerPath)

	return hr;
}


VOID _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	if ( pOutput == NULL )
	{
		PCHAR	filteredInputPtr ;
		int		i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		*dwOutputSize = filteredCounter ;
		*dwOutputSize = (*dwOutputSize/4)*3 ;

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
		free(filteredInputPtr) ;
	}
	else
	{
		DWORD		remainingSize ;
		PCHAR		inputPtr, outputPtr, filteredInputPtr ;
		int			i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		// remainingSize = dwInputSize ;
		remainingSize = filteredCounter ;
		inputPtr = filteredInputPtr ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;

		while((int)remainingSize > 0)
		{
			DWORD tmp, tmpout ;

			_decode(inputPtr[0], &tmpout) ;
			tmp = tmpout ;

			_decode(inputPtr[1], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			_decode(inputPtr[2], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;
				
			_decode(inputPtr[3], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			if ( inputPtr[2] == '=' && inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				*dwOutputSize += 1 ;
			}
			else if ( inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				*dwOutputSize += 2 ;
			}
			else
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				outputPtr[2] = (char)((tmp & 0x000000FF)) ;
				*dwOutputSize += 3 ;
			}

			remainingSize -= 4 ;
			inputPtr += 4 ;
			outputPtr += 3 ;
		}

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
		free(filteredInputPtr) ;
	}
}


BOOL _decode(short input, DWORD *output)
{
	if ( input >= 'A' && input <= 'Z' )
	{
		*output = input - 'A' ;
		return TRUE ;
	}
	else if ( input >= 'a' && input <= 'z' )
	{
		*output = input - 'a' + 26 ;
		return TRUE ;
	}
	else if ( input >= '1' && input <= '9' )
	{
		*output = input - '1' + 26 + 27 ;
		return TRUE ;
	}
	else if ( input == '0' )
	{
		*output = 26 + 26 ;
		return TRUE ;
	}
	else if ( input == '+' )
	{
		*output = 62 ;
		return TRUE ;
	}
	else if (input == '/' )
	{
		*output = 63 ;
		return TRUE ;
	}
	else if (input == '=' )
	{
		*output = 0 ;
		return TRUE ;
	}
	else
	{
		*output = 0 ;
		return FALSE ;
	}
}


unsigned int EraseMemory(unsigned int dwMemoryBlockSize, PBYTE pbyteMemoryBlock)
{
	if ((pbyteMemoryBlock == NULL) || (0 > dwMemoryBlockSize))
		return	-1;

	memset((void*)pbyteMemoryBlock, '0', dwMemoryBlockSize);
	return 0;
}



BOOL ShowErrorMessage(HRESULT hr, LPCTSTR i_pErrParam, ErrType i_eErrType)
{
	UINT iErrStringId = 0;
	WCHAR *wcErrString = NULL;
	TCHAR *cErrString = NULL;
	_bstr_t bstrErrString = "";
	BOOL bRetVal = TRUE;

	do
	{
		if(hr == S_OK)
			break;

		switch(hr)
		{
			case E_PROFDOESNOTEXIST:
			{
				iErrStringId = IDS_KEYS_ERR;
				break;
			}

			case E_VSSCODE_REGOPENKEYFAILED:
			{
				iErrStringId = IDS_REG_OPEN_ERR;
				break;
			}

			case E_VSSCODE_REGQUERYVALFAILED:
			{
				iErrStringId = IDS_REG_READ_ERR;
				break;
			}

			case E_VSSCODE_OUTOFMEMORY:
			{
				iErrStringId = IDS_MEM_ERR;
				break;
			}

			case REGDB_E_CLASSNOTREG:
			{
				iErrStringId = IDS_PTA_ABSENT;
				break;
			}

			case E_VSSCODE_DOCEXISTS:
			{
				iErrStringId = IDS_DOC_EXISTS;
				break;
			}

			case E_VSSCODE_NO_CERT_SPECIFIED:
			{
				iErrStringId = IDS_NO_CERT;
				break;
			}

			case E_INVALIDPKCS7:
			{
				iErrStringId = IDS_INVALID_CERT;
				break;
			}

			case E_VSSCODE_INVALID_PKCS7:
			case E_VSSCODE_INDEFINITE_ENC:
			{
				iErrStringId = IDS_INVALID_IMAGE;
				break;
			}

			case E_VSSCODE_PKCS7DECODERR:
			case E_VSSCODE_NOTSIGNEDATA:
			case E_VSSCODE_PARSESIGNDATA:
			case E_VSSCODE_CONTENTYPERR:
			{
				iErrStringId = IDS_PARSE_PKCS7;
				break;
			}

			default:
				return FALSE;

		}	//	switch(hr)

	
		hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), iErrStringId, &wcErrString);
		CHECK_HRESULT_BREAK

		bstrErrString = wcErrString;

		if(i_pErrParam)
		{
			cErrString = (TCHAR*)malloc(lstrlen(i_pErrParam) + lstrlen((LPCTSTR)bstrErrString) + 1);
			CHECK_MEM_BREAK(cErrString)

			wsprintf(cErrString, (LPCTSTR)bstrErrString, i_pErrParam);
		}
		else
		{
			cErrString = (TCHAR*)malloc(lstrlen((LPCTSTR)bstrErrString) + 1);
			CHECK_MEM_BREAK(cErrString)

			lstrcpy(cErrString, (LPCTSTR)bstrErrString);
		}

		if(i_eErrType == ERR_FATAL)
			MessageBox(GetFocus(), cErrString, "Code Signing Agent", MB_ICONSTOP | MB_ICONERROR | MB_ICONHAND);
		else
			if(i_eErrType == ERR_QUES)
				if(MessageBox(GetFocus(), cErrString, "Code Signing Agent", MB_ICONQUESTION | MB_YESNO) == IDNO)
					bRetVal = FALSE;

	}while(0);


	FREE_MEMORY(wcErrString)
	FREE_MEMORY(cErrString)

	return bRetVal;
}



VOID ShowSuccessMessage(OpStatus i_eStat)
{
	WCHAR *wcString = NULL;
	_bstr_t bstrString = "";
	UINT iStringId = 0;

	switch(i_eStat)
	{
		case CHANGE_PASSWD_SUCCEEDED:
		{
			iStringId = IDS_CHNG_PASSWD_SUCCESS;
			break;
		}

		case SIGN_SUCCEEDED:
		{
			iStringId = IDS_SIGN_SUCCESS;
			break;
		}

		case IMPORT_SUCCEEDED:
		{
			iStringId = IDS_IMPORT_SUCCESS;
			break;
		}

		case EXPORT_SUCCEEDED:
		{
			iStringId = IDS_EXPORT_SUCCESS;
			break;
		}

		case INSTALL_SUCCEEDED:
		{
			iStringId = IDS_INSTALL_SUCCESS;
			break;
		}

		default:
			return;
	}

	if(LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), iStringId, &wcString) == S_OK)
	{
		bstrString = wcString;

		::MessageBox(::GetFocus(), bstrString, "Code Signing Agent", MB_ICONINFORMATION | MB_ICONASTERISK);
	}
	
	FREE_MEMORY(wcString)

	return;
}


HRESULT GetUTCTime(LPTimeSettings i_lpTimeSettings, LPSYSTEMTIME o_lpUTCSysTime)
{
	HRESULT hr = S_OK;
	FILETIME ftLocal, ftUTC;
	SYSTEMTIME SysTime;
	
	do
	{
		if(!i_lpTimeSettings || !o_lpUTCSysTime)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		if(i_lpTimeSettings->bCurrentTime)
			GetLocalTime(&SysTime);
		else
			SysTime = i_lpTimeSettings->sysTime;

		if(!SystemTimeToFileTime(&SysTime, &ftLocal))
		{
			hr = E_VSSCODE_DATE_ERR;
			break;
		}

		if(!LocalFileTimeToFileTime(&ftLocal, &ftUTC))
		{
			hr = E_VSSCODE_DATE_ERR;
			break;
		}

		if(!FileTimeToSystemTime(&ftUTC, o_lpUTCSysTime))
		{
			hr = E_VSSCODE_DATE_ERR;
			break;
		}

	}while(0);

	return hr;
}