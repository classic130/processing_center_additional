// vsdnotz.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f vsdnotzps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include <comutil.h>
#include <objsafe.h>
#include <shlguid.h>
#include "vsdnotz.h"
#include "vsdnotz_i.c"
#include "ptav3.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzdefines.h"
#include "nzmacros.h"
#include "VSNZ.h"
#include "nzrecord.h"
#include "nzerrs.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VSNZ, CVSNZ)
END_OBJECT_MAP()

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
HRESULT ParseCmdLine(LPCTSTR i_lpCmdLine, _bstr_t& o_tbstrRecordPath, _bstr_t& o_tbstrDocumentPath);

// Structure used for registering notarization specific entries(context menu, icon, etc.)
typedef struct{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
}REGSTRUCT, *LPREGSTRUCT;


/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_VSDNOTZLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{
        _Module.Term();
	}
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	HRESULT hr;
	HRESULT _modulehr;
	DWORD dwLastError = 0;

    // registers object, typelib and all interfaces in typelib
    _modulehr = _Module.RegisterServer(TRUE);
	if(FAILED(_modulehr))
		return _modulehr;

	// Mark the control as safe for initialization
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
    if(FAILED(hr))
        return hr;

	hr = RegisterCLSIDInCategory(CLSID_VSNZ, CATID_SafeForInitializing);
    if(FAILED(hr))        
		return hr;

	// Mark the control as safe for scripting
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");    
	if(FAILED(hr))
        return hr;
    hr = RegisterCLSIDInCategory(CLSID_VSNZ, CATID_SafeForScripting);
    if(FAILED(hr))
        return hr;

	// Register the context menu and receipt file handler specific entries
	TCHAR szModuleName[MAX_FILE_PATH], szShortModuleName[MAX_FILE_PATH], szCommandLine[MAX_FILE_PATH];
	TCHAR szDefaultIcon[MAX_FILE_PATH];
	HKEY hKey = NULL;
	DWORD dwDisp;
	LRESULT lResult;

	if(!GetModuleFileName(_Module.m_hInst, szModuleName, sizeof(szModuleName)))
	{
		dwLastError = GetLastError();
		_LogErrorMsg("DllRegisterServer().", "Error getting module file name.", NULL, dwLastError);
		return SELFREG_E_CLASS;
	}

	if(!GetShortPathName(szModuleName, szShortModuleName, sizeof(szShortModuleName)))
	{
		// If function fails use the long path
		lstrcpy(szShortModuleName, szModuleName);
	}

	lstrcpy(szCommandLine, "rundll32.exe ");
	lstrcat(szCommandLine, szShortModuleName);
	lstrcat(szCommandLine, ",OpenRecord %1");

	lstrcpy(szDefaultIcon, szShortModuleName);
	lstrcat(szDefaultIcon, ",0");

	REGSTRUCT NzEntries[] = 
	{
		HKEY_CLASSES_ROOT,	TEXT("*\\shellex"),	NULL,	NULL,
		HKEY_CLASSES_ROOT,  TEXT("*\\shellex\\ContextMenuHandlers"), NULL, NULL,
		HKEY_CLASSES_ROOT,  TEXT("*\\shellex\\ContextMenuHandlers\\{D66256E2-B99C-11D4-8C74-0010830169AF}"), NULL, NULL,
		//HKEY_CLASSES_ROOT,	TEXT("CLSID\\{D66256E2-B99C-11D4-8C74-0010830169AF}"), NULL, "Verisign Notarization Client",
		//HKEY_CLASSES_ROOT,  TEXT("CLSID\\{D66256E2-B99C-11D4-8C74-0010830169AF}\\InprocServer32"),	NULL, "ModuleName",
		//HKEY_CLASSES_ROOT,  TEXT("CLSID\\{D66256E2-B99C-11D4-8C74-0010830169AF}\\InprocServer32"),	TEXT("ThreadingModel"), TEXT("Apartment"),
		HKEY_CLASSES_ROOT,  TEXT(".rcpt"),	NULL, TEXT("RCPTFile"),
		HKEY_CLASSES_ROOT,  TEXT("RCPTFile"), NULL, TEXT("Receipt file"),
		HKEY_CLASSES_ROOT,	 TEXT("RCPTFILE\\shell"), NULL, NULL,
		HKEY_CLASSES_ROOT,	 TEXT("RCPTFILE\\shell\\open"), NULL, NULL,
		HKEY_CLASSES_ROOT,	 TEXT("RCPTFILE\\shell\\open\\command"), NULL, "CommandLine",
		HKEY_CLASSES_ROOT,	 TEXT("RCPTFILE\\DefaultIcon"), NULL, "DefaultIcon",
		NULL, NULL, NULL, NULL
	};

	for(int i = 0; NzEntries[i].hRootKey; i++)
	{
	   lResult = RegCreateKeyEx(NzEntries[i].hRootKey, NzEntries[i].lpszSubKey, 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);
   	   if(ERROR_SUCCESS == lResult)
	   {
		  /*if(!lstrcmpi(NzEntries[i].lpszData, "ModuleName"))
		  {
			lResult = RegSetValueEx(hKey, NzEntries[i].lpszValueName, 0, REG_SZ,
									(LPBYTE)szModuleName, (lstrlen(szModuleName) + 1) * sizeof(TCHAR));
			if(ERROR_SUCCESS != lResult)
			{
				_LogErrorMsg("DllRegisterServer().", "Error setting registry value \'%s\'.", NzEntries[i].lpszValueName, lResult);
				RegCloseKey(hKey);
				return SELFREG_E_CLASS;
			}

			RegCloseKey(hKey);
			continue;
		  }*/

		  if(!lstrcmpi(NzEntries[i].lpszData, "CommandLine"))
		  {
			lResult = RegSetValueEx(hKey, NzEntries[i].lpszValueName, 0, REG_SZ, (LPBYTE)szCommandLine, 
									(lstrlen(szCommandLine) + 1) * sizeof(TCHAR));
			if(ERROR_SUCCESS != lResult)
			{
				_LogErrorMsg("DllRegisterServer().", "Error setting registry value \'%s\'.", NzEntries[i].lpszValueName, lResult);
				RegCloseKey(hKey);
				return SELFREG_E_CLASS;
			}

			RegCloseKey(hKey);
			continue;
		  }

		  if(!lstrcmpi(NzEntries[i].lpszData, "DefaultIcon"))
		  {
			lResult = RegSetValueEx(hKey, NzEntries[i].lpszValueName, 0, REG_SZ, (LPBYTE)szDefaultIcon, 
									(lstrlen(szDefaultIcon) + 1) * sizeof(TCHAR));
			if(ERROR_SUCCESS != lResult)
			{
				_LogErrorMsg("DllRegisterServer().", "Error setting registry value \'%s\'.", NzEntries[i].lpszValueName, lResult);
				RegCloseKey(hKey);
				return SELFREG_E_CLASS;
			}

			RegCloseKey(hKey);
			continue;
		  }

		  // If necessary, create the value string
		  if(NzEntries[i].lpszData)
		  {
			lResult = RegSetValueEx(hKey, NzEntries[i].lpszValueName, 0, REG_SZ, (LPBYTE)NzEntries[i].lpszData, 
									(lstrlen(NzEntries[i].lpszData) + 1) * sizeof(TCHAR));
			if(ERROR_SUCCESS != lResult)
			{
				_LogErrorMsg("DllRegisterServer().", "Error setting registry value \'%s\'.", NzEntries[i].lpszValueName, lResult);
				RegCloseKey(hKey);
				return SELFREG_E_CLASS;
			}
		  }

		  RegCloseKey(hKey);
	   }
	   else
	   {
		  dwLastError = GetLastError();
		  _LogErrorMsg("DllRegisterServer().", "Error creating registry key \'%s\'.", NzEntries[i].lpszSubKey, dwLastError);
		  return SELFREG_E_CLASS;
	   }
	}

	return _modulehr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	HKEY hKey = NULL;
	LONG lResult = 0;

    // Remove the context menu and receipt file handler specific entries
	RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{D66256E2-B99C-11D4-8C74-0010830169AF}");
	RegDeleteKey(HKEY_CLASSES_ROOT, ".rcpt");

	// Remove the 'open record' handler key
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, "RCPTFile\\shell\\open", 0, KEY_ALL_ACCESS, &hKey);
	if(lResult == ERROR_SUCCESS)
	{
		RegDeleteKey(hKey, "command");
		RegCloseKey(hKey);
	}

	// Remove the default icon key
	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, "RCPTFile", 0, KEY_ALL_ACCESS, &hKey);
	if(lResult == ERROR_SUCCESS)
	{
		RegDeleteKey(hKey, "DefaultIcon");
		RegCloseKey(hKey);
	}

    return _Module.UnregisterServer(TRUE);
}


/*
Working -	This function is called a '.rcpt' file is double clicked. This is the handler for
			the record(receipt) files. Is is invoked via the 'rundll32.exe'. It creates an 
			instance of the VSNZ class and calls the 'VerifyNotarizationRecord()' activex 
			method to do the verification.
*/
STDAPI OpenRecord(HWND hWnd, HINSTANCE hInst, LPSTR lpszCmdLine, INT nCmdShow)
{
	HRESULT hr = S_OK;
	IVSNZ *pVSNZ = NULL;
	LONG lResult = 0;
	HKEY hNzKey = NULL;
	DWORD dwValidationFlags = 0, dwData = 0, dwKeyType = 0;
	IVSNZUIPrefs *pVSNzUIPref = NULL;
	VARIANT varValidationPref, varRecord, varRecordType, varUIFlag, varLogoUrl;
	VARIANT varRcptTitle, varRcptHelpUrl, varNzServer, varDocument;
	_bstr_t bstrRecordPath = "", bstrDocumentPath = "", bstrLogoUrl = "", bstrErrTitle = "", bstrErrString = "";
	WCHAR *wcErrString = NULL;
	CUserSettings theUserSettings;

	VariantInit(&varValidationPref);
	VariantInit(&varRecord);
	VariantInit(&varRecordType);
	VariantInit(&varUIFlag);
	VariantInit(&varLogoUrl);
	VariantInit(&varRcptTitle);
	VariantInit(&varNzServer);
	VariantInit(&varRcptHelpUrl);
	VariantInit(&varDocument);

	CoInitialize(NULL);

	do
	{
		CHECK_NULL_PTR_BREAK(lpszCmdLine)

		hr = ParseCmdLine(lpszCmdLine, bstrRecordPath, bstrDocumentPath);
		CHECK_HRESULT_BREAK

		// Get user interface settings from the registry
		theUserSettings.Read();

		hr = CoCreateInstance(CLSID_VSNZ, NULL, CLSCTX_INPROC_SERVER, IID_IVSNZ,(void**)&pVSNZ);
		CHECK_HRESULT_BREAK

		varNzServer.vt = VT_BSTR;
		varNzServer.bstrVal = theUserSettings.m_bstrNzServer.copy();

		hr = pVSNZ->put_NotarizationServer(varNzServer);
		CHECK_HRESULT_BREAK

		varValidationPref.vt = VT_I2;
		varValidationPref.iVal = (UINT)theUserSettings.m_dwValidationFlags;

		hr = pVSNZ->put_ValidationPreference(varValidationPref);
		CHECK_HRESULT_BREAK

		hr = pVSNZ->get_IVSNZUIPrefs((IDispatch**)&pVSNzUIPref);
		CHECK_HRESULT_BREAK

		varLogoUrl.vt = VT_BSTR;
		varLogoUrl.bstrVal = theUserSettings.m_bstrLogoUrl.copy();

		hr = pVSNzUIPref->put_UILogoUrl(varLogoUrl);
		CHECK_HRESULT_BREAK

		varRcptTitle.vt = VT_BSTR;
		varRcptTitle.bstrVal = theUserSettings.m_bstrVerifyRcptTitle.copy();

		hr = pVSNzUIPref->put_UIVerifyRcptTitle(varRcptTitle);
		CHECK_HRESULT_BREAK

		varRcptHelpUrl.vt = VT_BSTR;
		varRcptHelpUrl.bstrVal = theUserSettings.m_bstrVerifyRcptHelpUrl.copy();

		hr = pVSNzUIPref->put_UIVerifyRcptHelpUrl(varRcptHelpUrl);
		CHECK_HRESULT_BREAK

		varRecord.vt = VT_BSTR;
		varRecord.bstrVal = bstrRecordPath.copy();

		varRecordType.vt = VT_I2;
		varRecordType.iVal = NZRECORD_URL;

		varUIFlag.vt = VT_I2;
		varUIFlag.iVal = UIFLAG_VERIFICATION | UIFLAG_WEB_LINK;

		varDocument.vt = VT_BSTR;
		varDocument.bstrVal = bstrDocumentPath.copy();

		CVSNZ *cVSNZ = (CVSNZ *) pVSNZ;
		cVSNZ->SetShowSaveLink(false);

		hr = pVSNZ->VerifyNotarizationRecord(&varRecord, &varDocument, &varRecordType, &varUIFlag);
		if(hr == E_NZDOCOPENFAILED)
		{
			// The document that was notarized does not exist at the location from which it
			// was notarized, prompt the user to find the document
			_bstr_t tbstrOpenFile = "";
			
			// Load the message box title first
			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_DNZ_ERROR, &wcErrString) == S_OK)
			{
				bstrErrTitle = wcErrString;
				FREE_MEMORY(wcErrString)
			}

			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_PROMPT_FOR_DOC, &wcErrString) == S_OK)
			{
				bstrErrString = wcErrString;
				FREE_MEMORY(wcErrString)
			}

			if(::MessageBox(GetFocus(), bstrErrString, bstrErrTitle, MB_ICONQUESTION | MB_APPLMODAL | MB_YESNO) == IDYES)
			{
				hr = _SelectOpenOrSaveFile(SELECT_OPEN, GetFocus(), IDS_LOCATE_DOC, NULL, 0, _bstr_t(""), &tbstrOpenFile);
				CHECK_HRESULT_BREAK
			}

			// Try verifying the record again with the selected file name
			varDocument.vt = VT_BSTR;
			varDocument.bstrVal = tbstrOpenFile.copy();

			hr = pVSNZ->VerifyNotarizationRecord(&varRecord, &varDocument, &varRecordType, &varUIFlag);
			CHECK_HRESULT_BREAK
		}

		CHECK_HRESULT_BREAK

	}while(0);

	RELEASE_INTERFACE_PTR(pVSNzUIPref)
	RELEASE_INTERFACE_PTR(pVSNZ)

	VariantClear(&varLogoUrl);
	VariantClear(&varUIFlag);
	VariantClear(&varRecordType);
	VariantClear(&varRecord);
	VariantClear(&varValidationPref);
	VariantClear(&varRcptTitle);
	VariantClear(&varNzServer);
	VariantClear(&varRcptHelpUrl);
	VariantClear(&varDocument);
	
	if(hNzKey)
	{
		RegCloseKey(hNzKey);
		hNzKey = NULL;
	}

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("OpenRecord().", "Error opening record.", NULL, hr);

 	return hr;
}



HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)    
{
    ICatRegister* pcr = NULL ;    
	HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (FAILED(hr))        
		return hr;
    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered.
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409 ; // english
    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is.
    int len = wcslen(catDescription);    
	if (len>127) 
		len = 127;
    wcsncpy(catinfo.szDescription, catDescription, len);
        // Make sure the description is null terminated.
        catinfo.szDescription[len] = '\0';
    hr = pcr->RegisterCategories(1, &catinfo);
		pcr->Release();
        return hr;   
}


HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)    
{
	// Register your component categories information.    
	ICatRegister* pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))    {
       // Register this category as being "implemented" by the class.
       CATID rgcatid[1] ;       
	   rgcatid[0] = catid;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);    
	}
    if (pcr != NULL)        
		pcr->Release();        
	return hr;        
}



HRESULT ParseCmdLine(LPCTSTR i_lpCmdLine, _bstr_t& o_tbstrRecordPath, _bstr_t& o_tbstrDocumentPath)
{
	HRESULT hr = S_OK;
	_bstr_t bstrCmdLine = "";
	WCHAR* pwCmdLine = NULL;
	TCHAR* pFileName = NULL;
	DWORD dwCmdLine = 0, dwFileNameIndex = 0;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	do
	{
		CHECK_NULL_PTR_BREAK(i_lpCmdLine)

		if(i_lpCmdLine[0] == '\0')
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		o_tbstrRecordPath = "";
		o_tbstrDocumentPath = "";

		bstrCmdLine = i_lpCmdLine;
		dwCmdLine = bstrCmdLine.length();
		pwCmdLine = bstrCmdLine.copy();

		// Get the directory name
		for(INT i = dwCmdLine - 1; i >= 0; i--)
		{
			if(pwCmdLine[i] == L'\\')
			{
				pwCmdLine[i] = NULL;
				break;
			}
		}

		// Get the long file name corresponding to 'lpszCmdLine'
		hFind = FindFirstFile(i_lpCmdLine, &wfd);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		// Construct the record name
		o_tbstrRecordPath = pwCmdLine;
		o_tbstrRecordPath += "\\";
		o_tbstrRecordPath += wfd.cFileName;

		// The document name is the record name without the '.rcpt' extension. For old receipt
		// format the file name against which to verify the notarization is first obtained from
		// the receipt itself, if this file is not present the file name passed in document name is 
		// used. For new receipt format the file name information is not encoded in the receipt
		// so the doocument name is used as the document against which to check the notarization.
		// This document name is obtained from the name of the recipt file itself by removing the
		// '.rcpt' extension and any 'Version (x) of...' prefix which may be present.

		pFileName = (TCHAR*)malloc(lstrlen(wfd.cFileName) + 1);
		CHECK_MEM_BREAK(pFileName)

		lstrcpy(pFileName, wfd.cFileName);

		// Remove the '.rcpt. extension first
		for(i = lstrlen(pFileName) - 1; i >= 0; i--)
		{
			if(pFileName[i] == '.')
			{
				pFileName[i] = '\0';
				break;
			}
		}
		
		// Now remove the "Version (x..) of ...' prefix if present
		if(!_strnicmp(pFileName, "Version (", 9))
		{
			for(i = 9; i < lstrlen(pFileName); i++)
			{
				if(pFileName[i] == ')')
				{
					if(!_strnicmp(&pFileName[i + 1], " of ", 4))
					{
						dwFileNameIndex = i + 5;
						break;
					}
				}
			}
		}

		// Construct the document name
		o_tbstrDocumentPath = pwCmdLine;
		o_tbstrDocumentPath += "\\";
		o_tbstrDocumentPath += &pFileName[dwFileNameIndex];
		
	}while(0);

	SYS_FREE_MEMORY(pwCmdLine)
	
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	FREE_MEMORY(pFileName)

	return hr;
}