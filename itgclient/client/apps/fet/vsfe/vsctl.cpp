// vsctl.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f vsctlps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <shlobj.h>
#include "vsctl.h"
#include "vsctl_i.c"
#include "vsctrl.h"
#include "guid.h"
#include "clsfact.h"
#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"

extern HRESULT OldDllRegisterServer(VOID);
extern HRESULT OldDllUnregisterServer(VOID);
extern BOOL OldDllMain(HINSTANCE, DWORD, LPVOID);
extern UINT g_DllRefCount;

#include <ObjSafe.h>

HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription) ;
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid) ;

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_vsctrl, Cvsctrl)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{

    if (dwReason == DLL_PROCESS_ATTACH)
    {
		// Check if the this is a 'namespace extension'. The registry entry 
		// could have been removed if the user deletes the Safe from the desktop

        _Module.Init(ObjectMap, hInstance, &LIBID_VSCTLLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();

	return OldDllMain(hInstance, dwReason, NULL);
}

// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
	if(_Module.GetLockCount() == 0 && g_DllRefCount == 0)
	{
		if(CanUnloadDll())
			return S_OK;
		else
			return S_FALSE;
	}

	return S_FALSE;
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if(IsEqualCLSID(rclsid, CLSID_VSSafe))
	{
	   	CClassFactory *pClassFactory = new CClassFactory();
		if(NULL == pClassFactory)
		   return E_OUTOFMEMORY;
   
		//get the QueryInterface return for our return value
		HRESULT hResult = pClassFactory->QueryInterface(riid, ppv);

		//call Release to decrement the ref count - creating the object set it to one 
		//and QueryInterface incremented it - since its being used externally (not by 
		//us), we only want the ref count to be 1
		pClassFactory->Release();

		//return the result from QueryInterface
		return hResult;
	}

    return _Module.GetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
	HRESULT hr;

	hr = _Module.RegisterServer(TRUE);
	if(FAILED(hr))
		return hr;

	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
    if(FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_vsctrl, CATID_SafeForInitializing);
    if(FAILED(hr))        
		return hr;
    
	// Mark the control as safe for scripting.
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
	if(FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_vsctrl, CATID_SafeForScripting);
    if(FAILED(hr))
        return hr;

	hr = OldDllRegisterServer();

    return hr ;
}



// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
    OldDllUnregisterServer();

    return _Module.UnregisterServer(TRUE);
}



HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription)
{
    ICatRegister	*pcr = NULL ;    
	HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr) ;
    if (FAILED(hr))        
		return hr ;

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered.
    CATEGORYINFO catinfo ;
    catinfo.catid = catid ;
    catinfo.lcid = 0x0409 ; // english

    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is.
    int len = wcslen(catDescription);    
	if (len > 127) 
		len = 127 ;
    wcsncpy(catinfo.szDescription, catDescription, len) ;

	// Make sure the description is null terminated.
	catinfo.szDescription[len] = '\0' ;
    hr = pcr->RegisterCategories(1, &catinfo) ;
	pcr->Release() ;
	return hr ;
}


HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.    
	ICatRegister* pcr = NULL ;
    HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr) ;
    if (SUCCEEDED(hr))
	{
       // Register this category as being "implemented" by the class.
       CATID rgcatid[1] ;       
		rgcatid[0] = catid ;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid) ;
	}

    if (pcr != NULL)        
		pcr->Release();

	return hr;        
}


