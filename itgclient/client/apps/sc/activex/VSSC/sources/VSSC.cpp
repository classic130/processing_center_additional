// VSSC.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f VSSCps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "VSSC.h"

#include "VSSC_i.c"
#include "VSSMC.h"

#include <list>

CListUserInfo				*g_pSignerCertInGM=NULL;
CListUserInfo				*g_pEncryptCertInGM=NULL;
CAppContext                 *gp_AppContext=NULL;

DWORD                       g_dwCertTimeOut=0;
DWORD                       g_dwAppErr=0;

g_GlobalMemoryManagement	*gp_GMemMgmt=NULL;





HRESULT CreateComponentCategory(CATID catid, WCHAR* catDescription);
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid);


CComModule _Module;



BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_VSSC, CVSSC)
//OBJECT_ENTRY(CLSID_VSSignerInfo, CVSSignerInfo)
//OBJECT_ENTRY(CLSID_VSSCDllApi, CVSSCDllApi)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{


	

    if (dwReason == DLL_PROCESS_ATTACH)
    {
	    _Module.Init(ObjectMap, hInstance, &LIBID_VSSCLib);
        DisableThreadLibraryCalls(hInstance);
	
		
		if(g_pEncryptCertInGM==NULL)
				g_pEncryptCertInGM=new CListUserInfo;

		if(NULL==gp_GMemMgmt)
			gp_GMemMgmt=new g_GlobalMemoryManagement;

		if(NULL==g_pSignerCertInGM)
			g_pSignerCertInGM=new CListUserInfo;

		if(NULL==gp_AppContext)
			gp_AppContext=new CAppContext;

        


    }
    else if (dwReason == DLL_PROCESS_DETACH)
	{

		
		if(g_pEncryptCertInGM!=NULL)
		{
			
			FreeCertList(g_pEncryptCertInGM);
			
			delete g_pEncryptCertInGM;
			g_pEncryptCertInGM=NULL;
		}
		if(NULL!=gp_GMemMgmt)
		{
				delete gp_GMemMgmt;
				gp_GMemMgmt=NULL;
		}

		if(NULL!=g_pSignerCertInGM)
		{
			
			FreeCertList(g_pSignerCertInGM);
			
			delete g_pSignerCertInGM;
			g_pSignerCertInGM=NULL;
		}

		if(gp_AppContext!=NULL)
		{
			delete gp_AppContext;
			gp_AppContext=NULL;
		}
				
        _Module.Term();
	}

    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	
	DWORD   dwLoadCount=0;

    BOOL bUnloadNow=_Module.GetLockCount();
	if(!bUnloadNow)
	{
		////S_OK

		if(NULL!=gp_GMemMgmt)
		{
			gp_GMemMgmt->VS_GetLoadedCount(&dwLoadCount);
			
		}

		
		if ( 0 != &dwLoadCount )
		{
			return	S_FALSE;
		}
		else
		{
			return	S_OK;
		}
	}
	else
	{
		////S_FALSE
			return	S_FALSE;

	}
		
	
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

    hr=_Module.RegisterServer(TRUE);
	if(FAILED(hr))
        return hr;

	//Safe for intailization
	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data#");
    if(FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_VSSC, CATID_SafeForInitializing);
    if(FAILED(hr))        
		return hr;
    
	// Mark the control as safe for scripting.
	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable#");
	if(FAILED(hr))
        return hr;

    hr = RegisterCLSIDInCategory(CLSID_VSSC, CATID_SafeForScripting);
    if(FAILED(hr))
        return hr;

    return hr;
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
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

