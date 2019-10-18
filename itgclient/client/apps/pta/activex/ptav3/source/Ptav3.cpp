// Ptav3.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f Ptav3ps.mk in the project directory.



#include "stdafx.h"
#include "resource.h"
#include <initguid.h>

#include "..\Include\mangledprofmgmt.h"
#include "..\Include\mangleduiprefs.h"
#include "..\Include\mangledcertprefs.h"
#include "..\Include\mangledsrchcrit.h"
#include "..\Include\mangledseldigid.h"
#include "..\Include\mangledroamprefs.h"
#include "..\Include\mangledptadllapi.h"
#include "..\Include\mangledimport.h"
#include "..\Include\mangledexport.h"

#include "..\Include\Ptav3.h"
#include "..\include\roots.h"

#include "Ptav3_i.c"
#include "profmgmt_i.c"
#include "uiprefs_i.c"
#include "certprefs_i.c"
#include "srchcrit_i.c"
#include "seldigid_i.c"
#include "roamprefs_i.c"
#include "ptadllapi_i.c"
#include "import_i.c"
#include "export_i.c"

#include "..\Include\VSPTA.h"

#include "..\Include\virtualsmartcard.h"

CComModule _Module;
CVirtualSmartCard* _gpVirtualSmartCard;
BOOL _gboolOpenedWithPassword;
PSRCHCRIT	_gpSrchCrit;
CVSPTA* _gpCurrPTA;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VSPTA, CVSPTA)
OBJECT_ENTRY(CLSID_VSROOTS, CVSROOTS)
END_OBJECT_MAP()

BOOL CALLBACK EnumResLangProc(
  HANDLE hModule,    // module handle
  LPCTSTR lpszType,  // pointer to resource type
  LPCTSTR lpszName,  // pointer to resource name
  WORD wIDLanguage,  // resource language identifier
  LONG lParam        // application-defined parameter
);

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);
HRESULT RegisterVeriSignCSP(VOID);
VOID UnRegisterVeriSignCSP(VOID);

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_PTAV3Lib);
        DisableThreadLibraryCalls(hInstance);
		_gpVirtualSmartCard = NULL;
		_gboolOpenedWithPassword = TRUE;
		_gpSrchCrit = NULL;
		_gpCurrPTA = NULL;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{
		if(_gpVirtualSmartCard)
			delete(_gpVirtualSmartCard);
		if(_gpSrchCrit)
			delete(_gpSrchCrit);
		_gboolOpenedWithPassword = TRUE;
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

	// registers object, typelib and all interfaces in typelib
	_modulehr =  _Module.RegisterServer(TRUE);
	if(FAILED(_modulehr))
	{
		return _modulehr;
	}
    
    
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
    if (FAILED(hr))
        return hr;
    hr = RegisterCLSIDInCategory(CLSID_VSPTA, CATID_SafeForInitializing);
    if (FAILED(hr))        
		return hr;

	
	// Mark the control as safe for scripting.
    hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");    
	if (FAILED(hr))
        return hr;
    hr = RegisterCLSIDInCategory(CLSID_VSPTA, CATID_SafeForScripting);
    if (FAILED(hr))
        return hr;

	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
    if (FAILED(hr))
        return hr;
    hr = RegisterCLSIDInCategory(CLSID_VSROOTS, CATID_SafeForInitializing);
    if (FAILED(hr))        
		return hr;

	
	// Mark the control as safe for scripting.
    hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");    
	if (FAILED(hr))
        return hr;
    hr = RegisterCLSIDInCategory(CLSID_VSROOTS, CATID_SafeForScripting);
    if (FAILED(hr))
        return hr;

	RegisterVeriSignCSP();

	return _modulehr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
//	UnRegisterVeriSignCSP();
    return _Module.UnregisterServer(TRUE);
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


#define VSCSP_PROVIDER	"SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\VeriSign Personal Trust Agent (PTA)"
#define	VSCSP_TPM_PROVIDER "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\VeriSign TPM CSP"


HRESULT RegisterVeriSignCSP(VOID)
{
	HRESULT hr = S_FALSE;
	HANDLE hFileSig = NULL;
	DWORD dwNumBytes = 0, dwNumBytesRead = 0, dwError = 0, dwCSPType = CSP_INSTALL_TYPE;
	LPVOID lpvAddress = NULL;
	HKEY hKey = NULL;
	HKEY hTPMCSPKey = NULL;
	TCHAR szImagePath[MAX_PATH*2], szSigFile[MAX_PATH],*pStr= NULL;
	//TCHAR  szErrMsg[MAX_PATH], szCaption[MAX_PATH], szTemp[MAX_PATH];
	
	do
	{
		//LoadString(_Module.m_hInst, IDS_INSTALL_FAILED, szCaption, sizeof(szCaption));

		if(!GetModuleFileName(_Module.m_hInst, szImagePath, sizeof(szImagePath)))
		{
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_MODULE_NAME_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
			break;
		}

		lstrcpy(szSigFile, szImagePath);
		pStr = strrchr(szSigFile, '\\');
		if(!pStr)
		{
			//LoadString(_Module.m_hInst, IDS_STRING_ERR, szErrMsg, sizeof(szErrMsg));
			//MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);
			break;
		}

		lstrcpy(pStr + 1, CSP_SIGNATURE_FILE);
 
		// Read the signature file in memory
		hFileSig = CreateFile(szSigFile, GENERIC_READ, 0, 
							  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		if(hFileSig == INVALID_HANDLE_VALUE)
		{
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_OPEN_FILE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, szSigFile, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
			break;
		}

		dwNumBytes = GetFileSize(hFileSig, NULL);
		if(dwNumBytes == 0xffffffff)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_FILE_SIZE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, szSigFile, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		lpvAddress = VirtualAlloc(NULL, dwNumBytes, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_READWRITE);
		if(!lpvAddress)
		{
			/*LoadString(_Module.m_hInst, IDS_MEMORY_FAIL, szErrMsg, sizeof(szErrMsg));
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
			break;
		}
		
		if(!ReadFile(hFileSig, lpvAddress, dwNumBytes, &dwNumBytesRead, 0))
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_READ_FILE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, szSigFile, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
			break;
		}

        if(dwNumBytesRead != dwNumBytes)
        {
			/*LoadString(_Module.m_hInst, IDS_INVALID_SIGFILE, szErrMsg, sizeof(szErrMsg));
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		// Make registry entries for the CSP
	    dwError = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                    VSCSP_PROVIDER, 0L, "", REG_OPTION_NON_VOLATILE,
                    KEY_ALL_ACCESS, NULL, &hKey, NULL);
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_CREATE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		dwError = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
                    VSCSP_TPM_PROVIDER, 0L, "", REG_OPTION_NON_VOLATILE,
                    KEY_ALL_ACCESS, NULL, &hTPMCSPKey, NULL);
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_CREATE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		dwError = RegSetValueEx(hKey, "Image Path", 0L, REG_SZ, (const unsigned char *)szImagePath,
								lstrlen(szImagePath) + 1);
								
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		dwError = RegSetValueEx(hTPMCSPKey, "Image Path", 0L, REG_SZ, (const unsigned char *)szImagePath,
								lstrlen(szImagePath) + 1);
								
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

	    dwError = RegSetValueEx(hKey, "Type", 0L, REG_DWORD,
                                (const unsigned char *)&dwCSPType, sizeof(DWORD));
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		dwError = RegSetValueEx(hTPMCSPKey, "Type", 0L, REG_DWORD,
                                (const unsigned char *)&dwCSPType, sizeof(DWORD));
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

        dwError = RegSetValueEx(hKey, "Signature", 0L, REG_BINARY,
                                (const unsigned char *)lpvAddress, dwNumBytes);
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		dwError = RegSetValueEx(hTPMCSPKey, "Signature", 0L, REG_BINARY,
                                (const unsigned char *)lpvAddress, dwNumBytes);
		if(dwError != ERROR_SUCCESS)
        {
			/*dwError = GetLastError();
			LoadString(_Module.m_hInst, IDS_REG_WRITE_ERR, szTemp, sizeof(szTemp));
			wsprintf(szErrMsg, szTemp, dwError);
			MessageBox(GetFocus(), szErrMsg, szCaption, MB_OK | MB_ICONERROR);*/
            break;
        }

		hr = S_OK;

	} while(0);


	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(hTPMCSPKey)
	{
		RegCloseKey(hTPMCSPKey);
		hTPMCSPKey = NULL;
	}

	if(lpvAddress)
	{
		VirtualFree(lpvAddress, 0, MEM_RELEASE);
		lpvAddress = NULL;
	}
	
	if(hFileSig)
	{
		CloseHandle(hFileSig);
		hFileSig = NULL;
	}

	return hr;
}


VOID UnRegisterVeriSignCSP(VOID)
{
	RegDeleteKey(HKEY_LOCAL_MACHINE, VSCSP_PROVIDER);
	RegDeleteKey(HKEY_LOCAL_MACHINE, VSCSP_TPM_PROVIDER);
}