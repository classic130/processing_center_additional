// DropSrc.cpp

#include "stdafx.h"

#include <shlobj.h>

#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"
#include "DropSrc.h"

BOOL g_bDragSource;

CDropSource::CDropSource(void)
{
	g_DllRefCount++;
	m_ObjRefCount = 1;

	g_bDragSource = TRUE;
}


CDropSource::~CDropSource(void)
{
	g_DllRefCount--;

	g_bDragSource = FALSE;
}


// IUnknown Implementation
STDMETHODIMP CDropSource::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	// IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
	   *ppReturn = this;

	// IDropTarget
	else if(IsEqualIID(riid, IID_IDropSource))
	   *ppReturn = (IDropSource*)this;

	if(*ppReturn)
    {
	   (*(LPUNKNOWN*)ppReturn)->AddRef();
	   return S_OK;
	}

	return E_NOINTERFACE;
}



STDMETHODIMP_(DWORD) CDropSource::AddRef(VOID)
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CDropSource::Release(VOID)
{
	if(--m_ObjRefCount == 0)
    {
	   delete this;
	   return 0;
    }
   
	return m_ObjRefCount;
}


// IDropSource Implementation
STDMETHODIMP CDropSource::QueryContinueDrag(BOOL fEsc, DWORD dwKeyState)
{
	if(fEsc)
	   return DRAGDROP_S_CANCEL;

	// Make sure the left mouse button is still down
	if(!(dwKeyState & MK_LBUTTON))
	   return DRAGDROP_S_DROP;

	return S_OK;
}


STDMETHODIMP CDropSource::GiveFeedback(DWORD dwEffect)
{
	return DRAGDROP_S_USEDEFAULTCURSORS;
}

