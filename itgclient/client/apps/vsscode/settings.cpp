#include "stdafx.h"
#include <comutil.h>
#include "certmgmt.h"
#include "settings.h"
#include "vsserrs.h"
#include "propsht.h"
#include "util.h"
#include "macros.h"
#include "ptav3.h"
#include "ptaiface.h"


CRegSettings::CRegSettings()
{
	m_bstrAppContext = "";
	m_bstrClientInfo = "";
	m_bstrClientInfoSig = "";
	m_bstrSrchCriteria = "";
	m_dwCapi = FALSE;

	m_bstrHashAlg = "SHA1";
	m_dwDisplayDigID = TRUE;

	m_dwPasswordQuality = 0;
	m_dwPasswordLength = 0;
	m_dwPasswordTimeout = 0;
	m_dwPasswordTries = 0;
	m_dwPasswordUnlockPeriod = 0;

	m_dwCounterSign = 0;

	m_dwTimerSetting = 1;	// Default to using current system time

	m_bstrCodeType = "";
}


CRegSettings::~CRegSettings()
{

}


HRESULT CRegSettings::Read(VOID)
{
	HRESULT hr = S_OK;
	HKEY hMainKey = NULL, hCodeKey = NULL;
	LONG lResult = 0;
	DWORD dwKeyType = 0, dwData = 0;
	LPBYTE pbData = NULL;
	_bstr_t bstrCodeKey = "";

	do
	{
		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_REG_KEY, 0, KEY_QUERY_VALUE, &hMainKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGOPENKEYFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error opening registry key \'%s\'.", MAIN_REG_KEY, lResult);
			break;
		}

		// Read the 'code type' value
		m_bstrCodeType = "";
		lResult = RegQueryValueEx(hMainKey, CODE_TYPE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error querying registry value \'%s\'.", CODE_TYPE, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hMainKey, CODE_TYPE, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error querying registry value \'%s\'.", CODE_TYPE, lResult);
			break;
		}

		m_bstrCodeType = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrCodeType == _bstr_t(""))
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Null value for the code type.", NULL, 0);
			break;
		}

		// Use 'm_bstrCodeType' to read from appropriate registry entry
		bstrCodeKey = MAIN_REG_KEY;
		bstrCodeKey += "\\" + m_bstrCodeType;

		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, bstrCodeKey, 0, KEY_QUERY_VALUE, &hCodeKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGOPENKEYFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error opening registry key \'%s\'.", bstrCodeKey, lResult);
			break;
		}

		// Read the 'Application Context' value
		m_bstrAppContext = "";
		lResult = RegQueryValueEx(hCodeKey, APPCONTEXT, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error querying registry value \'%s\'.", APPCONTEXT, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hCodeKey, APPCONTEXT, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error querying registry value \'%s\'.", APPCONTEXT, lResult);
			break;
		}

		m_bstrAppContext = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrAppContext == _bstr_t(""))
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Null value for the application context.", NULL, lResult);
			break;
		}

		// Read the 'Capi' flag
		dwData = sizeof(m_dwCapi);
		lResult = RegQueryValueEx(hCodeKey, CAPI, NULL, &dwKeyType, (LPBYTE)&m_dwCapi, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Read().", "Error querying registry value \'%s\'.", CAPI, lResult);
			break;
		}

		// Read the 'certificate search criteria' value
		m_bstrSrchCriteria = "";
		lResult = RegQueryValueEx(hCodeKey, SRCHCRITERIA, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)
		
			lResult = RegQueryValueEx(hCodeKey, SRCHCRITERIA, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrSrchCriteria = (LPTSTR)pbData;
		
			FREE_MEMORY(pbData)
		}

		// Read the 'client info' value
		m_bstrClientInfo = "";
		lResult = RegQueryValueEx(hCodeKey, CLINFO, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hCodeKey, CLINFO, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrClientInfo = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read the 'client info sig' value
		m_bstrClientInfoSig = "";
		lResult = RegQueryValueEx(hCodeKey, CLINFOSIG, NULL, &dwKeyType, NULL, &dwData);
		if(lResult == ERROR_SUCCESS)
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hCodeKey, CLINFOSIG, NULL, &dwKeyType, pbData, &dwData);
			if(lResult == ERROR_SUCCESS)
				m_bstrClientInfoSig = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Read 'hash algorithm' value
		m_bstrHashAlg = "";
		lResult = RegQueryValueEx(hCodeKey, HASHALG, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_bstrHashAlg = "SHA1";		// If not hash alg present in registry default to 'SHA1'
		else
		{
			pbData = (PBYTE)malloc(dwData);
			CHECK_MEM_BREAK(pbData)

			lResult = RegQueryValueEx(hCodeKey, HASHALG, NULL, &dwKeyType, pbData, &dwData);
			if(lResult != ERROR_SUCCESS)
				m_bstrHashAlg = "SHA1";
			else
				m_bstrHashAlg = (LPTSTR)pbData;

			FREE_MEMORY(pbData)
		}

		// Validate the hash alg and set to default if necessary
		if(_strnicmp(m_bstrHashAlg, "MD5", 3) && _strnicmp(m_bstrHashAlg, "SHA1", 4) &&
			_strnicmp(m_bstrHashAlg, "MD2", 3))
			m_bstrHashAlg = "SHA1";

		// Read 'Display digital ID' value
		dwData = sizeof(m_dwDisplayDigID);
		lResult = RegQueryValueEx(hCodeKey, DISP_DIGID, NULL, &dwKeyType, (PBYTE)&m_dwDisplayDigID, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwDisplayDigID = FALSE;	// Default to 'FALSE'


		// Read the 'password quality' value
		dwData = sizeof(m_dwPasswordQuality);
		lResult = RegQueryValueEx(hCodeKey, PASSWD_QUAL, NULL, &dwKeyType, (PBYTE)&m_dwPasswordQuality, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwPasswordQuality = ANYPASSWDOK;	// Default to any password

		// Read the 'password length' value
		dwData = sizeof(m_dwPasswordLength);
		lResult = RegQueryValueEx(hCodeKey, PASSWD_LEN, NULL, &dwKeyType, (PBYTE)&m_dwPasswordLength, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwPasswordQuality = 6;	// Default to a length of 6 chars

		// Read the 'password timeout' value
		dwData = sizeof(m_dwPasswordTimeout);
		lResult = RegQueryValueEx(hCodeKey, PASSWD_TIMEOUT, NULL, &dwKeyType, (PBYTE)&m_dwPasswordTimeout, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwPasswordTimeout = 2;	// Default to a timeout of 2 minutes

		// Read the 'password tries' value
		dwData = sizeof(m_dwPasswordTries);
		lResult = RegQueryValueEx(hCodeKey, PASSWD_TRIES, NULL, &dwKeyType, (PBYTE)&m_dwPasswordTries, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwPasswordTries = 2;	// Default to 2 minutes

		// Read the 'password unlock period' value
		dwData = sizeof(m_dwPasswordUnlockPeriod);
		lResult = RegQueryValueEx(hCodeKey, PASSWD_TRIES, NULL, &dwKeyType, (PBYTE)&m_dwPasswordUnlockPeriod, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwPasswordUnlockPeriod = 2;	// Default to 2 minutes

		// Read the 'counter sign' only if the code type is 'SignOp'
		if(m_bstrCodeType == _bstr_t("SignOp"))
		{
			dwData = sizeof(m_dwCounterSign);
			lResult = RegQueryValueEx(hCodeKey, COUNTER_SIGN, NULL, &dwKeyType, (PBYTE)&m_dwCounterSign, &dwData);
			if(lResult != ERROR_SUCCESS)
				m_dwCounterSign = 0;	// Default to no counter signatures
		}

		// Read the 'timer setting' value
		dwData = sizeof(m_dwTimerSetting);
		lResult = RegQueryValueEx(hCodeKey, TIMER_SETTING, NULL, &dwKeyType, (PBYTE)&m_dwTimerSetting, &dwData);
		if(lResult != ERROR_SUCCESS)
			m_dwTimerSetting = 1;	// Default to current system time

	}while(0);

	FREE_MEMORY(pbData)

	REG_CLOSE_KEY(hCodeKey)
	REG_CLOSE_KEY(hMainKey)

	return hr;
}


HRESULT CRegSettings::Write(const _bstr_t i_tbstrValueName)
{
	HRESULT hr = S_OK;
	HKEY hMainKey = NULL, hCodeKey = NULL;
	LONG lResult = 0;
	DWORD dwKeyType = 0, dwData = 0;
	LPBYTE pbData = NULL;
	_bstr_t bstrCodeKey = "";

	do
	{
		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_REG_KEY, 0, KEY_QUERY_VALUE, &hMainKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGOPENKEYFAILED;
			_LogErrorMsg("CRegSettings::Write().", "Error opening registry key \'%s\'.", MAIN_REG_KEY, lResult);
			break;
		}		
		
		// Read the 'code type' value
		m_bstrCodeType = "";
		lResult = RegQueryValueEx(hMainKey, CODE_TYPE, NULL, &dwKeyType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Write().", "Error querying registry value \'%s\'.", CODE_TYPE, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hMainKey, CODE_TYPE, NULL, &dwKeyType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Write().", "Error querying registry value \'%s\'.", CODE_TYPE, lResult);
			break;
		}

		m_bstrCodeType = (LPTSTR)pbData;
		FREE_MEMORY(pbData)

		if(m_bstrCodeType == _bstr_t(""))
		{
			hr = E_VSSCODE_REGQUERYVALFAILED;
			_LogErrorMsg("CRegSettings::Write().", "Null value for the code type.", NULL, 0);
			break;
		}

		// Use 'm_bstrCodeType' to write to the appropriate registry entry
		bstrCodeKey = MAIN_REG_KEY;
		bstrCodeKey += "\\" + m_bstrCodeType;

		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, bstrCodeKey, 0, KEY_WRITE, &hCodeKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_VSSCODE_REGOPENKEYFAILED;
			_LogErrorMsg("CRegSettings::Write().", "Error opening registry key \'%s\'.", bstrCodeKey, lResult);
			break;
		}

		if(i_tbstrValueName == _bstr_t("TimerSetting"))
		{
			lResult = RegSetValueEx(hCodeKey, i_tbstrValueName, 0, REG_DWORD, (PBYTE)(&m_dwTimerSetting), sizeof(DWORD));
			if(lResult != ERROR_SUCCESS)
			{
				_LogErrorMsg("CRegSettings::Write().", "Error setting registry value \'%s\'.", i_tbstrValueName, lResult);
				hr = E_VSSCODE_REGSETVALFAILED;
			}

			break;
		}

	}while(0);

	FREE_MEMORY(pbData)

	REG_CLOSE_KEY(hCodeKey)
	REG_CLOSE_KEY(hMainKey)

	return hr;
}