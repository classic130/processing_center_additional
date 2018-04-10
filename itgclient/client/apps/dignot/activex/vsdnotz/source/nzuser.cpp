#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "notarize.h"
#include "nzuser.h"
#include "nzutils.h"
#include "nzerrs.h"
#include "nzmacros.h"
#include "nzdefines.h"
#include "resource.h"

CUserSettings::CUserSettings()
{
	// Set some default settings
	m_bstrNzServer = "";
	m_bstrHashAlg = "MD5";
	m_bstrReceiptDescription = "";
	m_dwDisplayDigID = TRUE;
	m_dwValidationFlags = REV_NONE;

	m_bstrLogoUrl = "";
	m_bstrDigNotWizTitle = "";
	m_bstrSelFileTitle = "";
	m_bstrSelFileDescription = "";
	m_bstrSelFileHelpUrl = "";
	m_bstrProgressTitle = "";
	m_bstrProgressDescription = "";
	m_bstrProgressHelpUrl = "";
	m_bstrVerifyRcptTitle = "";
	m_bstrVerifyRcptDescription = "";
	m_bstrVerifyRcptHelpUrl = "";

	m_bstrAppContext = "";
	m_bstrClientInfo = "";
	m_bstrClientInfoSig = "";
	m_bstrSrchCriteria = "";
	m_dwCapi = FALSE;

	m_bstrHostingServer = "";
	m_bstrCrl = "";

	m_dwTimeoutInterval = 0;
	m_dwLastAccessed = 0;
}


CUserSettings::~CUserSettings()
{
}

/*
Working -	This function initializes the member variables by reading the data from the registry.
			It gets the parameters for the notarization operation and for initializing the PTA.
			If some critical parameters are not present in the registry then this function fails.
			For non critical parameters some defaults are used if the registry does not have any value.
*/
HRESULT CUserSettings::Read()
{
	HRESULT hr = S_FALSE;
	HKEY hNzKey = NULL;
	LONG lResult = 0;
	DWORD dwKeyType = 0;
	LPBYTE pbData = NULL;
	DWORD dwData = 0;

	do
	{
		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, NZ_MAIN_KEY, 0, KEY_QUERY_VALUE, &hNzKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGOPENKEYFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error opening registry key \'%s\'.", NZ_MAIN_KEY, lResult);
			break;
		}


		// Read 'hash algorithm' value
		m_bstrHashAlg = "";
		lResult = RegQueryValueEx(hNzKey, NZ_HASHALG, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_bstrHashAlg = "MD5";		// If not hash alg present in registry default to 'MD5'
		else
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_HASHALG, NULL, &dwKeyType, pbData, &dwData);
			if(lResult != ERROR_SUCCESS)
				m_bstrHashAlg = "MD5";
			else
				m_bstrHashAlg = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Validate the hash alg and set to default if necessary, notarization server
		// supports only 'SHA1' and 'MD5'
		if(_strnicmp(m_bstrHashAlg, "MD5", 3) && _strnicmp(m_bstrHashAlg, "SHA1", 4))
			m_bstrHashAlg = "MD5";

		// Read 'Display digital ID' value
		dwData = sizeof(m_dwDisplayDigID);
		lResult = RegQueryValueEx(hNzKey, NZ_DISP_DIGID, NULL, &dwKeyType, (PBYTE)&m_dwDisplayDigID, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwDisplayDigID = FALSE;	// Default to 'FALSE'

		// Read the 'Validation Flags' value
		dwData = sizeof(m_dwValidationFlags);
		lResult = RegQueryValueEx(hNzKey, NZ_VAL_FLAG, NULL, &dwKeyType, (PBYTE)&m_dwValidationFlags, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwValidationFlags = REV_NONE;	// Default to 'REV_NONE'


		// Read the 'Timeout Interval' value
		dwData = sizeof(m_dwTimeoutInterval);
		lResult = RegQueryValueEx(hNzKey, NZ_TIMEOUT, NULL, &dwKeyType, (PBYTE)&m_dwTimeoutInterval, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwTimeoutInterval = 5;	// Default to 5 minutes


		// Read the 'Last accessed' value
		dwData = sizeof(m_dwLastAccessed);
		lResult = RegQueryValueEx(hNzKey, NZ_LAST_ACCESSED, NULL, &dwKeyType, (PBYTE)&m_dwLastAccessed, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwLastAccessed = GetTickCount();	// Default to current time


		// Read the 'Receipt Description'
		m_bstrReceiptDescription = "";
		lResult = RegQueryValueEx(hNzKey, NZ_RCPTDESC, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_RCPTDESC, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrReceiptDescription = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'LogoUrl'
		m_bstrLogoUrl = "";
		lResult = RegQueryValueEx(hNzKey, NZ_LOGOURL, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_LOGOURL, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrLogoUrl = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Notarization Wizard Title'
		m_bstrDigNotWizTitle = "";
		lResult = RegQueryValueEx(hNzKey, NZ_WIZTITLE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_WIZTITLE, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrDigNotWizTitle = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Select File Title'
		m_bstrSelFileTitle = "";
		lResult = RegQueryValueEx(hNzKey, NZ_SELFILETITLE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_SELFILETITLE, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrSelFileTitle = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Select File Description'
		m_bstrSelFileDescription = "";
		lResult = RegQueryValueEx(hNzKey, NZ_SELFILEDESC, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_SELFILEDESC, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrSelFileDescription = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Select File Help Url'
		m_bstrSelFileHelpUrl = "";
		lResult = RegQueryValueEx(hNzKey, NZ_SELFILEHELPURL, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_SELFILEHELPURL, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrSelFileHelpUrl = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Progress Title'
		m_bstrProgressTitle = "";
		lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSTITLE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSTITLE, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrProgressTitle = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Progress Description'
		m_bstrProgressDescription = "";
		lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSDESC, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSDESC, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrProgressDescription = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Progress Help Url'
		m_bstrProgressHelpUrl = "";
		lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSHELPURL, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_PROGRESSHELPURL, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrProgressHelpUrl = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Verify Receipt Title'
		m_bstrVerifyRcptTitle = "";
		lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTITLE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTITLE, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrVerifyRcptTitle = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Verify Receipt Description'
		m_bstrVerifyRcptDescription = "";
		lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTDESC, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTDESC, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrVerifyRcptDescription = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'Verify Receipt Help Url'
		m_bstrVerifyRcptHelpUrl = "";
		lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTHELPURL, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_VERIFYRCPTHELPURL, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrVerifyRcptHelpUrl = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}


		// Read the 'client info' value
		m_bstrClientInfo = "";
		lResult = RegQueryValueEx(hNzKey, NZ_CLINFO, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_CLINFO, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrClientInfo = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'client info sig' value
		m_bstrClientInfoSig = "";
		lResult = RegQueryValueEx(hNzKey, NZ_CLINFOSIG, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_CLINFOSIG, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrClientInfoSig = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'certificate search criteria' value
		m_bstrSrchCriteria = "";
		lResult = RegQueryValueEx(hNzKey, NZ_SRCHCRITERIA, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)
		
			lResult = RegQueryValueEx(hNzKey, NZ_SRCHCRITERIA, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrSrchCriteria = (LPTSTR)pbData;
		
			FREE_MEMORY(pbData)
		}

		// Read the location of the CRL
		m_bstrCrl = "";
		lResult = RegQueryValueEx(hNzKey, NZ_CRL, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hNzKey, NZ_CRL, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrCrl = (LPTSTR)pbData;
		
			FREE_MEMORY(pbData)
		}

		// Read 'hosting server' value
		m_bstrHostingServer = "";
		lResult = RegQueryValueEx(hNzKey, NZ_HOST_SERVER, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_HOST_SERVER, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, NZ_HOST_SERVER, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_HOST_SERVER, lResult);
			break;
		}

		m_bstrHostingServer = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrHostingServer == _bstr_t(""))
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Null value for the hosting server.", NULL, 0);
			break;
		}


		// Read 'notarization server' value
		m_bstrNzServer = "";
		lResult = RegQueryValueEx(hNzKey, NZ_SERVER, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_SERVER, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, NZ_SERVER, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_SERVER, lResult);
			break;
		}

		m_bstrNzServer = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrNzServer == _bstr_t(""))
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Null value for the notarization server.", NULL, 0);
			break;
		}


		// Read the 'Application Context' value
		lResult = RegQueryValueEx(hNzKey, NZ_APPCONTEXT, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_APPCONTEXT, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, NZ_APPCONTEXT, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_APPCONTEXT, lResult);
			break;
		}

		m_bstrAppContext = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrAppContext == _bstr_t(""))
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Null value for the application context.", NULL, lResult);
			break;
		}

		// Read the 'EnrollHomePage' value
		lResult = RegQueryValueEx(hNzKey, NZ_ENROLL_HOMEPAGE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_ENROLL_HOMEPAGE, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, NZ_ENROLL_HOMEPAGE, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_ENROLL_HOMEPAGE, lResult);
			break;
		}

		m_bstrEnrollPage = (LPTSTR)pbData;
		FREE_MEMORY(pbData)


		// Read the 'RenewalHomePage' value
		lResult = RegQueryValueEx(hNzKey, NZ_RENEWAL_HOMEPAGE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_RENEWAL_HOMEPAGE, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, NZ_RENEWAL_HOMEPAGE, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_RENEWAL_HOMEPAGE, lResult);
			break;
		}

		m_bstrRenewalPage = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		// Read the 'Capi' flag
		dwData = sizeof(m_dwCapi);
		lResult = RegQueryValueEx(hNzKey, NZ_CAPI, NULL, &dwKeyType, (LPBYTE)&m_dwCapi, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CUserSettings::Read().", "Error querying registry value \'%s\'.", NZ_CAPI, lResult);
			break;
		}

		hr = S_OK;

	}while(0);

	FREE_MEMORY(pbData)

	if(hNzKey)
	{
		RegCloseKey(hNzKey);
		hNzKey = NULL;
	}

	return hr;
}


/*
I/P -	'i_pCaller'	:	Is the name of the function which calls this function.
Working -	Writes the values of the class members in the log file. Only for a DEBUG
			build. Used for trouble shooting.
*/
VOID CUserSettings::Dump(LPCTSTR i_pCaller)
{
#if 0
#ifdef _DEBUG
	HANDLE hLogFile = NULL;
	SYSTEMTIME sysTime;
	TCHAR szErrString[ERR_STRING_LEN], szUserName[MAX_STRING_LEN];
	DWORD dwBytesWritten = 0, dwUserName = sizeof(szUserName);

	do
	{
		hLogFile = CreateFile(VS_NZLOGFILE, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
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

		WriteFile(hLogFile, "---- User settings ----\r\n", 25, &dwBytesWritten, NULL);

		wsprintf(szErrString, "%s : %s : %d:%d,  %d:%d:%d\r\n", i_pCaller, szUserName, sysTime.wHour, sysTime.wMinute, sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Notarization Server : %s\r\n", (LPCTSTR)m_bstrNzServer);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Hash Algorithm : %s\r\n", (LPCTSTR)m_bstrHashAlg);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Display Digital ID : %d\r\n", m_dwDisplayDigID);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Validation flags : %x\r\n", m_dwValidationFlags);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Logo URL : %s\r\n", (LPCTSTR)m_bstrLogoUrl);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Wizard Title : %s\r\n", (LPCTSTR)m_bstrDigNotWizTitle);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "File Title : %s\r\n", (LPCTSTR)m_bstrSelFileTitle);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "File Description : %s\r\n", (LPCTSTR)m_bstrSelFileDescription);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "File Help URL : %s\r\n", (LPCTSTR)m_bstrSelFileHelpUrl);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Progress Title : %s\r\n", (LPCTSTR)m_bstrProgressTitle);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Progress Description : %s\r\n", (LPCTSTR)m_bstrProgressDescription);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Progress Help URL : %s\r\n", (LPCTSTR)m_bstrProgressHelpUrl);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Receipt Title : %s\r\n", (LPCTSTR)m_bstrVerifyRcptTitle);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Receipt Description : %s\r\n", (LPCTSTR)m_bstrVerifyRcptDescription);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Receipt Help URL : %s\r\n", (LPCTSTR)m_bstrVerifyRcptHelpUrl);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Application Context : %s\r\n", (LPCTSTR)m_bstrAppContext);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Client Info : %s\r\n", (LPCTSTR)m_bstrClientInfo);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Client Info Sig : %s\r\n", (LPCTSTR)m_bstrClientInfoSig);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Search Criteria : %s\r\n", (LPCTSTR)m_bstrSrchCriteria);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Capi Mode : %d\r\n", m_dwCapi);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		wsprintf(szErrString, "Hosting Server : %s\r\n", (LPCTSTR)m_bstrHostingServer);
		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

		WriteFile(hLogFile, "-------------------------\r\n", 25, &dwBytesWritten, NULL);

	}while(0);

	if(hLogFile && hLogFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hLogFile);
		hLogFile = NULL;
	}

	return;
#endif
#endif
}