// Implements the CClassFactory for the NameSpace Extension.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "ClsFact.h"

// IClassFactory implementation
CClassFactory::CClassFactory()
{
	g_DllRefCount++;
	m_ObjRefCount = 1;
}


CClassFactory::~CClassFactory()
{
	g_DllRefCount--;
}


STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	if(IsEqualIID(riid, IID_IUnknown))
	   *ppReturn = this;
	else if(IsEqualIID(riid, IID_IClassFactory))
	   *ppReturn = (IClassFactory*)this;

	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             



STDMETHODIMP_(DWORD) CClassFactory::AddRef()
{
	return ++m_ObjRefCount;
}


STDMETHODIMP_(DWORD) CClassFactory::Release()
{
	if(--m_ObjRefCount == 0)
	{
	   delete this;
	   return 0;
	}
   
	return m_ObjRefCount;
}


// Support creation of the 'Shell Folder' object. This is the object which Windows Explorer 
// requires from a NameSpace Extension
STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN pUnknown, REFIID riid, LPVOID *ppObject)
{
	*ppObject = NULL;

	if(pUnknown != NULL)
	   return CLASS_E_NOAGGREGATION;

	CShellFolder *pShellFolder = new CShellFolder();
	if(NULL == pShellFolder)
	   return E_OUTOFMEMORY;
  
	HRESULT hResult = pShellFolder->QueryInterface(riid, ppObject);

	// Call Release to decement the ref count
	pShellFolder->Release();

	return hResult;
}



STDMETHODIMP CClassFactory::LockServer(BOOL)
{
	return E_NOTIMPL;
}

