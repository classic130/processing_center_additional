// Implements the IVSNZAppPrefs interface

#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "vsdnotz.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzerrs.h"
#include "nzmacros.h"
#include "VSNZ.h"

/*
I/P -	'in_pvarAppName'	:	'Application name' is the registry key which has to be created, 
								for the notarization client the 'Application Name' is 'Notarization'.
								The parent key is always assumed to be HKEY_CURRENT_USER\Software\VeriSign, Inc.
		'inpvarPrefName'	:	'Preference Name' is the subkey name under the 'Application Name',
								for the notarization client one of the "Preference Name' is 'NotarizationServer'
		'in_pvarPrefValue'	:	Is the value of the subkey, currently this function supports only
								'strings' and 'dwords'.
Return -	An hresult indicating the status of the operation.
Working -	This function provides a way to set registry information for applications. It can be
			called from a Web page. This allows a Web site to host a page containing user settings,
			the user would obtain the settings on his end machine by using this page.
*/
STDMETHODIMP CVSNZ::SetApplicationPreference(VARIANT* in_pvarAppName, VARIANT* in_pvarPrefName, VARIANT* in_pvarPrefValue)
{
	HRESULT hr = S_OK;
	HKEY hNzKey = NULL;
	LONG lResult = 0;
	_bstr_t bstrKeyName = "", bstrPrefName = "";
	
	do
	{
		if(!in_pvarAppName || !in_pvarPrefName || !in_pvarPrefValue)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(in_pvarAppName->vt != VT_BSTR || in_pvarPrefName->vt != VT_BSTR)
		{
			hr = E_NZINVALIDARGS;
			break;
		}
		
		if(in_pvarAppName->bstrVal == NULL || in_pvarPrefName->bstrVal == NULL)
		{
			hr = E_NZEMPTYARGS;
			break;
		}
		
		bstrKeyName = VS_MAIN_KEY;
		bstrKeyName += "\\";
		bstrKeyName += in_pvarAppName->bstrVal;

		bstrPrefName = in_pvarPrefName->bstrVal;

		// Create or open the key
		lResult = RegCreateKeyEx(HKEY_CURRENT_USER, (TCHAR*)bstrKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hNzKey, NULL);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGOPENKEYFAILED;
			_LogErrorMsg("CVSNZ::SetApplicationPreference().", "Error creating registry key \'%s\'.", bstrKeyName, lResult);
			break;
		}

		switch(in_pvarPrefValue->vt)
		{
			case VT_BSTR :
			{
				_bstr_t bstrPrefValue = in_pvarPrefValue->bstrVal;

				lResult = RegSetValueEx(hNzKey, bstrPrefName, 0, REG_SZ, (PBYTE)(TCHAR*)bstrPrefValue, lstrlen((TCHAR*)bstrPrefValue) + 1);
				if(lResult != ERROR_SUCCESS)
				{
					_LogErrorMsg("CVSNZ::SetApplicationPreference().", "Error setting registry value \'%s\'.", bstrPrefName, lResult);
					hr = E_NZREGSETVALUEFAILED;
					break;
				}

				break;
			}

			case VT_I2 :
			{
				DWORD dwPrefValue = in_pvarPrefValue->iVal;
				lResult = RegSetValueEx(hNzKey, bstrPrefName, 0, REG_DWORD, (PBYTE)&dwPrefValue, sizeof(DWORD));
				if(lResult != ERROR_SUCCESS)
				{
					_LogErrorMsg("CVSNZ::SetApplicationPreference().", "Error setting registry value \'%s\'.", bstrPrefName, lResult);
					hr = E_NZREGSETVALUEFAILED;
					break;
				}

				break;
			}

			default :
			{
				hr = E_NZTYPENOTSUPPORTED;
				break;
			}
		}

	}while(0);

	if(hNzKey)
	{
		RegCloseKey(hNzKey);
		hNzKey = NULL;
	}
	
	return hr;
}


/*
I/P	-	'in_pvarAppName'	:	'Application name' is the registry key which has to be read, 
								for the notarization client the 'Application Name' is 'Notarization'.
								The parent key is always assumed to be HKEY_CURRENT_USER\Software\VeriSign, Inc.
		'inpvarPrefName'	:	'Preference Name' is the subkey name under the 'Application Name',
								for the notarization client one of the "Preference Name' is 'NotarizationServer'
O/P	-	'o_pvarPrefType'	:	Is the type of value, currently this function supports only
								'strings' and 'dwords', should be enhanced to support all return types.
		'o_pvarPrefValue'	:	Is the value of the subkey.
Return	-	An hresult indicating the status of the operation.
Working	-	This function queries the registry for the value of subkeys.
*/
STDMETHODIMP CVSNZ::GetApplicationPreference(VARIANT* in_pvarAppName, VARIANT* in_pvarPrefName, VARIANT* o_pvarPrefType, VARIANT* o_pvarPrefValue)
{
	HRESULT hr = S_OK;
	HKEY hNzKey = NULL;
	LONG lResult = 0;
	DWORD dwType = 0, dwData = 0;
	LPBYTE pbData = NULL;
	_bstr_t bstrKeyName = "", bstrPrefName = "";
	
	do
	{
		if(!in_pvarAppName || !in_pvarPrefName || !o_pvarPrefType || !o_pvarPrefValue)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(in_pvarAppName->vt != VT_BSTR || in_pvarPrefName->vt != VT_BSTR)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(in_pvarAppName->bstrVal == NULL || in_pvarPrefName->bstrVal == NULL)
		{
			hr = E_NZEMPTYARGS;
			break;
		}
		
		bstrKeyName = VS_MAIN_KEY;
		bstrKeyName += "\\";
		bstrKeyName += in_pvarAppName->bstrVal;

		bstrPrefName = in_pvarPrefName->bstrVal;

		// Open the key
		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, (TCHAR*)bstrKeyName, 0, KEY_QUERY_VALUE, &hNzKey);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGOPENKEYFAILED;
			_LogErrorMsg("CVSNZ::GetApplicationPreference().", "Error opening registry key \'%s\'.", bstrKeyName, lResult);
			break;
		}

		lResult = RegQueryValueEx(hNzKey, (TCHAR*)bstrPrefName, NULL, &dwType, NULL, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CVSNZ::GetApplicationPreference().", "Error querying registry value \'%s\'.", bstrPrefName, lResult);
			break;
		}

		pbData = (PBYTE)malloc(dwData);
		CHECK_MEM_BREAK(pbData)

		lResult = RegQueryValueEx(hNzKey, (TCHAR*)bstrPrefName, NULL, &dwType, pbData, &dwData);
		if(lResult != ERROR_SUCCESS)
		{
			hr = E_NZREGQUERYVALFAILED;
			_LogErrorMsg("CVSNZ::GetApplicationPreference().", "Error querying registry value \'%s\'.", bstrPrefName, lResult);
			break;
		}

		switch(dwType)
		{
			case REG_DWORD :
			{
				o_pvarPrefValue->vt = VT_I2;
				o_pvarPrefValue->iVal = *pbData;

				break;
			}

			case REG_SZ :
			{
				_bstr_t bstrPrefVal = (TCHAR*)pbData;
				o_pvarPrefValue->vt = VT_BSTR;
				o_pvarPrefValue->bstrVal = bstrPrefVal.copy();

				break;
			}

			default :
			{
				hr = E_NZTYPENOTSUPPORTED;
				break;
			}
		}

	}while(0);

	FREE_MEMORY(pbData)

	if(hNzKey)
	{
		RegCloseKey(hNzKey);
		hNzKey = NULL;
	}

	return hr;
}
