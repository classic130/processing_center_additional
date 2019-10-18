// vsctrl.cpp : Implementation of Cvsctrl

#include "stdafx.h"
#include "Vsctl.h"
#include "vsctrl.h"
#include <shlobj.h>
#include <wininet.h>
#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"

extern TCHAR g_szWinDir[MAX_PATH_LEN];


// Cvsctrl
STDMETHODIMP Cvsctrl::SetEnterpriseServer(BSTR bstrServerName)
{
	if(!bstrServerName)
		return S_FALSE;

	TCHAR *lpEnterpriseServer = _WideToMultiString(bstrServerName);

	if(!lpEnterpriseServer)
		return S_FALSE;

	TCHAR szFmt[MAX_PATH], szErr[MAX_PATH];
	HKEY hKey = NULL;
	DWORD dwDisp, dwErr;
	
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE,
				   KEY_WRITE, NULL, &hKey, &dwDisp) != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_CREATE, MB_OK | MB_ICONERROR);
		wsprintf(szErr, "SetEnterpriseServer:RegCreateKeyEx() : \'%s\'", MAIN_KEY_STRING);
		LogErrorMessage(szErr, dwErr);
		free(lpEnterpriseServer);
		lpEnterpriseServer = NULL;
		return S_FALSE;
	}

	if(RegSetValueEx(hKey, "PolicyFileLocation", 0, REG_SZ, (LPBYTE)lpEnterpriseServer,
					 (lstrlen(lpEnterpriseServer) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_WRITE, MB_OK | MB_ICONERROR);
		LogErrorMessage("SetEnterpriseServer:RegSetValueEx() : PolicyFileLocation",
						dwErr);
		free(lpEnterpriseServer);
		lpEnterpriseServer = NULL;
		return S_FALSE;
	}

	RegCloseKey(hKey);

	// Also download the remote policy file, this download is now a 
	// part of the FET installation as this method is invoked from
	// the Web Page. Download it in the <windows\downlo~1> dir
	TCHAR szPolicyFile[2*MAX_PATH];
	lstrcpy(szPolicyFile, g_szWinDir);
	SmartAppendBackslash(szPolicyFile);
	lstrcat(szPolicyFile, "downlo~1\\");
	lstrcat(szPolicyFile, POLICY_FILE);

	DWORD dwError;
	if(!DownloadRemotePolicyFile(szPolicyFile, &dwError))
	{
		// 'dwError' set if there is a error in a call to WinInet fns
		if(dwError)
		{
			if(dwError == ERROR_INTERNET_CANNOT_CONNECT)
			{
				LoadString(g_hInst, IDS_CONNECT_ERROR, szErr, MAX_PATH);
				wsprintf(szFmt, szErr, lpEnterpriseServer);
				::MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			}
			else
				DisplayMessage(GetFocus(), IDS_NETWORK_ERROR, MB_OK | MB_ICONERROR);

			LogErrorMessage("SetEnterpriseServer() : WinInet Error.", dwError);
		}
	}

	if(lpEnterpriseServer)
	{
		free(lpEnterpriseServer);
		lpEnterpriseServer = NULL;
	}

	return S_OK;
}


STDMETHODIMP Cvsctrl::SetFetContextInformation(BSTR bstrAppContext, BSTR bstrClientInfo, BSTR bstrClientInfoSig)
{
	if(!bstrAppContext || !bstrClientInfo || !bstrClientInfoSig)
		return S_FALSE;

	TCHAR *lpAppContext = NULL, *lpClientInfo = NULL, *lpClientInfoSig = NULL;
	HRESULT hr = S_FALSE;
	HKEY hKey = NULL;
	DWORD dwErr = 0, dwDisp = 0;
		
	do
	{
		lpAppContext = _WideToMultiString(bstrAppContext);
		lpClientInfo = _WideToMultiString(bstrClientInfo);
		lpClientInfoSig = _WideToMultiString(bstrClientInfoSig);

		if(!lpAppContext || !lpClientInfo || !lpClientInfoSig)
			break;

		if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE,
						  KEY_WRITE, NULL, &hKey, &dwDisp) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_CREATE, MB_OK | MB_ICONERROR);
			LogErrorMessage("SetFetContextInformation:RegOpenKeyEx() failed", dwErr);
			break;
		}

		if(RegSetValueEx(hKey, FET_APP_CONTEXT, 0, REG_SZ, (LPBYTE)lpAppContext, 
						 (lstrlen(lpAppContext) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_WRITE, MB_OK | MB_ICONERROR);
			LogErrorMessage("SetFetContextInformation:RegSetValueEx(0) failed", dwErr);
			break;
		}

		if(RegSetValueEx(hKey, CLIENT_INFO, 0, REG_SZ, (LPBYTE)lpClientInfo, 
						 (lstrlen(lpClientInfo) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_WRITE, MB_OK | MB_ICONERROR);
			LogErrorMessage("SetFetContextInformation:RegSetValueEx(1) failed", dwErr);
			break;
		}

		if(RegSetValueEx(hKey, CLIENT_INFO_SIG, 0, REG_SZ, (LPBYTE)lpClientInfoSig, 
						 (lstrlen(lpClientInfoSig) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_WRITE, MB_OK | MB_ICONERROR);
			LogErrorMessage("SetFetContextInformation:RegSetValueEx(2) failed", dwErr);
			break;
		}

		hr = S_OK;
	} while(0);

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(lpAppContext)
	{
		free(lpAppContext);
		lpAppContext = NULL;
	}

	if(lpClientInfo)
	{
		free(lpClientInfo);
		lpClientInfo = NULL;
	}

	if(lpClientInfoSig)
	{
		free(lpClientInfoSig);
		lpClientInfoSig = NULL;
	}

	return hr;
}