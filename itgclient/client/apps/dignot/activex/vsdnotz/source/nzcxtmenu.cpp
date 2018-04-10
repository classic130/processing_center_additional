// Implements the IContextMenu interface

#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "vsdnotz.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzmacros.h"
#include "nzdefines.h"
#include "nzerrs.h"
#include "nzdatacc.h"
#include "VSNZ.h"

/*
Working -	This function adds the 'Notarize' right click context menu option. It determines if
			any files have been selected and if so can they be notarized.
			For more information regarding this function refer to the Windows documentation of 
			the	IContextMenu interface.
*/
STDMETHODIMP CVSNZ::QueryContextMenu(HMENU hMenu,UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, 
									 UINT uFlags)
{
	HRESULT hr = S_OK;
	WCHAR* wcMenuText = NULL;
	LONG lResult = 0;
	HKEY hNzKey = NULL;
	DWORD dwKeyType = 0, dwData = 0, dwContextMenu = 1;

	do
	{
		// Determine if the context menu needs to be shown at all. If the registry key 'ContextMenu'
		// under 'NZ_MAIN_KEY' is equal to 0 then don't show the menu
		lResult = RegOpenKeyEx(HKEY_CURRENT_USER, NZ_MAIN_KEY, 0, KEY_QUERY_VALUE, &hNzKey);
		if(lResult == ERROR_SUCCESS)
		{
			dwData = sizeof(dwContextMenu);
			lResult = RegQueryValueEx(hNzKey, NZ_CONTEXT_MENU, NULL, &dwKeyType, (PBYTE)&dwContextMenu, &dwData);
			if(lResult == ERROR_SUCCESS)
				if(dwContextMenu == 0)
					break;
		}

		if(uFlags & CMF_DEFAULTONLY)
			break;

		hr = _CanNotarizeDocument();
		if(hr == S_OK)
		{
			UINT idCmd = idCmdFirst;
			_bstr_t bstrMenuText = "";
			HRESULT hResult = S_OK;

			// May have to get the default language from the PTA ?
			hResult = _LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_NOTARIZE, &wcMenuText);
			if(hResult != S_OK)
			{
				_LogErrorMsg("CVSNZ::QueryContextMenu().", "Error loading string.", NULL, hResult);
				break;
			}

			bstrMenuText = wcMenuText;

			InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);
			InsertMenu(hMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, bstrMenuText);
			InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

			hr = ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(idCmd-idCmdFirst)));
		}
		else
			_LogErrorMsg("CVSNZ::QueryContextMenu().", "Cannot notarize the document(s).", NULL, hr);

	}while(0);

	FREE_MEMORY(wcMenuText)

	if(hNzKey)
	{
		RegCloseKey(hNzKey);
		hNzKey = NULL;
	}

	return hr;
}


/*
Working -	For more information regarding this function refer to the Windows documentation of 
			the IContextMenu interface.
*/
STDMETHODIMP CVSNZ::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	HRESULT hr = S_OK;

	do
	{
		// If HIWORD(lpcmi->lpVerb) then we have been called programmatically and lpVerb is a 
		// command that should be invoked. Otherwise, the shell has called us, and 
		// LOWORD(lpcmi->lpVerb) is the menu ID the user has selected. Actually, 
		// it's (menu ID - idCmdFirst) from QueryContextMenu(). We do not support getting 
		// called programmatically.
		if(!HIWORD(lpcmi->lpVerb))
		{
			UINT idCmd = LOWORD(lpcmi->lpVerb);

			switch(idCmd)
			{
				case 0:
				{
					hr = _NotarizeDocuments();
					break;
				}
			}
		}
	
	}while(0);

	return hr;
}


/*
Working -	This function returns the string which is displayed on the Windows explorer status
			bar.
			For more information regarding this function refer to the Windows documentation of 
			the IContextMenu interface.
*/
STDMETHODIMP CVSNZ::GetCommandString(UINT idCmd, UINT uFlags, UINT FAR *reserved, LPSTR pszName, 
									 UINT cchMax)
{
	WCHAR* wcMenuStatus = NULL;
	DWORD dwMenuStatusLen = 0;
	_bstr_t bstrMenuStatus = "";
	HRESULT hr = S_OK;

	switch(idCmd)
	{
		// For now only one command is present
		case 0:
		{
			switch(uFlags)
			{
				case GCS_HELPTEXTA :
				case GCS_HELPTEXTW :
				{
					// May have to get the default language from the PTA ?
					hr = _LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_MENU_STATUS, &wcMenuStatus);
					if(hr != S_OK)
					{
						_LogErrorMsg("CVSNZ::GetCommandString().", "Error loading string.", NULL, hr);
						break;
					}

					dwMenuStatusLen = lstrlenW(wcMenuStatus);
					bstrMenuStatus = wcMenuStatus;

					if(uFlags == GCS_HELPTEXTA)
					{
						if(cchMax > dwMenuStatusLen)
							lstrcpy(pszName, bstrMenuStatus);
					}
					else
					{
						if(cchMax > (dwMenuStatusLen + 1) * 2)
							lstrcpyW((LPWSTR)pszName, bstrMenuStatus);
					}

					break;
				}

			}	// end switch(uFlags)
			
			break;
		}
	}	// end switch(idCmd)

	FREE_MEMORY(wcMenuStatus)

	return hr;
}


/*
Return -	'TRUE' if the document(s) can be notarized else 'FALSE'
Working -	This function checks if any files have been selected by querying 'm_pSelItems'.
			If a file has been selected it returns 'TRUE'. 'm_pSelItems' is set during the 
			initialization of the shell extension.
*/
HRESULT CVSNZ::_CanNotarizeDocument()
{
	HRESULT	hr = S_FALSE;
	FORMATETC fmtetc;
	STGMEDIUM StgMedium;
	UINT nFileCnt = 0;
	TCHAR *pSelectedFile = NULL;
	DWORD dwSelectedFileSize = 0;

	do
	{
		if(!m_pSelItems)
		{
			hr = E_NZNOSELECTION;
			break;
		}

		fmtetc.cfFormat = CF_HDROP;
		fmtetc.ptd = NULL;
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.tymed = TYMED_HGLOBAL;

		hr = m_pSelItems->GetData(&fmtetc, &StgMedium);
		if(!SUCCEEDED(hr))
			break;
		
		nFileCnt = DragQueryFile((HDROP)StgMedium.hGlobal, -1, NULL, 0);

		for(UINT i = 0; i < nFileCnt; i++)
		{
			dwSelectedFileSize = DragQueryFile((HDROP)StgMedium.hGlobal, i, NULL, 0);

			pSelectedFile = (TCHAR *)malloc(dwSelectedFileSize + 1);
			CHECK_MEM_BREAK(pSelectedFile)

			pSelectedFile[0] = '\0';
			DragQueryFile((HDROP)StgMedium.hGlobal, i, pSelectedFile, dwSelectedFileSize + 1);

			if(FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(pSelectedFile))
			{
				FREE_MEMORY(pSelectedFile)
				continue;
			}
			else
			{
				hr = S_OK;
				break;
			}
		}

		ReleaseStgMedium(&StgMedium);
	}
	while(0);

	FREE_MEMORY(pSelectedFile)
	
	return hr;
}


/*
Return -	An hresult indicating success of the operation.
Working -	This function is called when the user selects the notarize option on the context
			menu. It reads the application settings from the registry and initializes the PTA.
			For each file that is selected it calls _DoDigitalNotarization() function. After
			successful notarization is creates a notarization record(receipt) which has the
			name of the file that is selected appended by extension '.rcpt'
*/
HRESULT CVSNZ::_NotarizeDocuments()
{
	HRESULT hr = S_FALSE;
	FORMATETC fmtetc;
	STGMEDIUM StgMedium;
	UINT nFileCnt = 0, nSelFiles = 0;
	TCHAR *pSelectedFile = NULL, **pSelFiles = NULL;
	WCHAR* wcErrString = NULL;
	DWORD dwSelectedFileSize = 0, *pdwRecordLengths = NULL, dwTickCount = 0, dwTimeElapsed = 0;
	BOOL bCloseProfile = FALSE;
	PBYTE* pbRecords = NULL;
	IVSPTA* pVSPta = NULL;
	_bstr_t bstrErrTitle = "", bstrErrMessage = "";
	LONG lResult = 0;
	HKEY hNzKey = NULL;
	
	do
	{
		if(!m_pSelItems)
		{
			hr = E_NZNOSELECTION;
			break;
		}

		// Read user settings from the registry
		hr = m_UsrSettings.Read();

		if(hr != S_OK)
		{
			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_DNZ_ERROR, &wcErrString) != S_OK)
				break;

			bstrErrTitle = wcErrString;

			FREE_MEMORY(wcErrString)

			if(hr == E_NZREGOPENKEYFAILED)
			{
				// The registry entry for 'Notarization' does not exist
				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_USR_SETTINGS_ERR3, &wcErrString) != S_OK)
					break;

				bstrErrMessage = wcErrString;

				FREE_MEMORY(wcErrString)

				::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_OK);
			}
			else
				if(hr == E_NZREGQUERYVALFAILED)
				{
					// Some required registry entries are absent, goto page from where the control was
					// downloaded to set the entries again

					// If the hosting server value is absent or NULL we cannot goto the page from where
					// the user settings can be set in the registry
					if(m_UsrSettings.m_bstrHostingServer != _bstr_t(""))
					{
						if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_USR_SETTINGS_ERR, &wcErrString) != S_OK)
							break;

						bstrErrMessage = wcErrString;
					
						if(::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_YESNO) == IDYES)
							LaunchApp(m_UsrSettings.m_bstrHostingServer);
					}
					else
					{
						if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_USR_SETTINGS_ERR2, &wcErrString) != S_OK)
							break;

						bstrErrMessage = wcErrString;

						::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_OK);
					}

					FREE_MEMORY(wcErrString)

					break;
				}
		}
				
		CHECK_HRESULT_BREAK

		// Check if the profile needs to be closed
		dwTickCount = GetTickCount();

		dwTimeElapsed = dwTickCount - m_UsrSettings.m_dwLastAccessed;
		dwTimeElapsed = dwTimeElapsed / 60000;	// in minutes

		if(dwTimeElapsed >= m_UsrSettings.m_dwTimeoutInterval)
			bCloseProfile = TRUE;

		// Initialize the PTA with the user settings 
		hr = _InitializePTA(TRUE, &pVSPta, bCloseProfile);
		CHECK_HRESULT_BREAK

		// Query the data object for the selected file(s) and do the notarization operation
		fmtetc.cfFormat = CF_HDROP;
		fmtetc.ptd = NULL;
		fmtetc.dwAspect = DVASPECT_CONTENT;
		fmtetc.lindex = -1;
		fmtetc.tymed = TYMED_HGLOBAL;

		hr = m_pSelItems->GetData(&fmtetc, &StgMedium);
		if(!SUCCEEDED(hr))
			break;

		nFileCnt = DragQueryFile((HDROP)StgMedium.hGlobal, -1, NULL, 0);

		pSelFiles = (TCHAR**)malloc(nFileCnt * sizeof(TCHAR**));
		CHECK_MEM_BREAK(pSelFiles)

		pbRecords = (PBYTE*)malloc(nFileCnt * sizeof(PBYTE*));
		CHECK_MEM_BREAK(pbRecords)

		pdwRecordLengths = (LPDWORD)malloc(nFileCnt * sizeof(LPDWORD));
		CHECK_MEM_BREAK(pdwRecordLengths)

		for(UINT i = 0; i < nFileCnt; i++)
		{
			pSelFiles[i] = NULL;
			pbRecords[i] = NULL;
			pdwRecordLengths[i] = 0;
		}

		for(i = 0; i < nFileCnt; i++)
		{
			dwSelectedFileSize = DragQueryFile((HDROP)StgMedium.hGlobal, i, NULL, 0);

			pSelectedFile = (TCHAR *)malloc(dwSelectedFileSize + 1);
			CHECK_MEM_BREAK(pSelectedFile)

			pSelectedFile[0] = '\0';
			DragQueryFile((HDROP)StgMedium.hGlobal, i, pSelectedFile, dwSelectedFileSize + 1);

			if(FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(pSelectedFile))
			{
				FREE_MEMORY(pSelectedFile)
				continue;
			}
			else
			{
				pSelFiles[nSelFiles] = pSelectedFile;
				nSelFiles++;
			}
		}

		ReleaseStgMedium(&StgMedium);

		hr = _DoDigitalNotarization(pVSPta, (LPCTSTR*)pSelFiles, NULL, nSelFiles, FALSE, UIFLAG_PROGRESS | UIFLAG_COMPLETE, RT_NZRESPONSE/*RT_NZRECORD*/, TRUE, pbRecords, pdwRecordLengths);
		CHECK_HRESULT_BREAK

		// Write the current time in the registry as the last accessed time
		dwTickCount = GetTickCount();

		// Create or open the key
		lResult = RegCreateKeyEx(HKEY_CURRENT_USER, NZ_MAIN_KEY, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hNzKey, NULL);
		if(lResult != ERROR_SUCCESS)
			_LogErrorMsg("CVSNZ::_NotarizeDocuments().", "Error creating registry key \'%s\'.", NZ_MAIN_KEY, lResult);
		else
		{
			lResult = RegSetValueEx(hNzKey, NZ_LAST_ACCESSED, 0, REG_DWORD, (PBYTE)&dwTickCount, sizeof(DWORD));
			if(lResult != ERROR_SUCCESS)
				_LogErrorMsg("CVSNZ::_NotarizeDocuments().", "Error setting registry value \'%s\'.", NZ_LAST_ACCESSED, lResult);
		
			RegCloseKey(hNzKey);
			hNzKey = NULL;
		}
	}while(0);

	_UnInitializePTA(pVSPta);

	for(UINT i = 0; i < nSelFiles; i++)
	{
		FREE_MEMORY(pSelFiles[i]);
		FREE_MEMORY(pbRecords[i])
	}
	
	FREE_MEMORY(pSelFiles)
	FREE_MEMORY(pbRecords)
	FREE_MEMORY(pdwRecordLengths)

	return hr;
}
