// Implements CExtractIcon.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ExtrIcon.h"


CExtractIcon::CExtractIcon(LPCITEMIDLIST pidl)
{
	g_DllRefCount++;

	m_pPidlMgr = new CPidlMgr();
	if(!m_pPidlMgr)
	{
		delete this;
		return;
	}

	m_pidl = m_pPidlMgr->Copy(pidl);

	m_ObjRefCount = 1;
}


CExtractIcon::~CExtractIcon()
{
	if(m_pidl)
	{
		m_pPidlMgr->Delete(m_pidl);
		m_pidl = NULL;
	}

	if(m_pPidlMgr)
		delete m_pPidlMgr;

	g_DllRefCount--;
}


// IUnknown Implementation
STDMETHODIMP CExtractIcon::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	// IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = this;

	// IExtractIcon
	else if(IsEqualIID(riid, IID_IExtractIcon))
		*ppReturn = (IExtractIcon*)this;

	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             



STDMETHODIMP_(DWORD) CExtractIcon::AddRef()
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CExtractIcon::Release()
{
	if(--m_ObjRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}


// IExtractIcon Implementation
STDMETHODIMP CExtractIcon::GetIconLocation(UINT uFlags, LPTSTR szIconFile, UINT cchMax, LPINT piIndex, LPUINT puFlags)
{
	// Tell the shell to always call Extract
	*puFlags = GIL_NOTFILENAME;

	// The pidl is either a value or a folder, so find out which it is
	if(m_pPidlMgr->IsFolder(m_pPidlMgr->GetLastItem(m_pidl)))
	{
		// Its a folder
		if(uFlags & GIL_OPENICON)
		{
			// Tell Extract to return the open folder icon
			*piIndex = ICON_INDEX_FOLDEROPEN;
		}
		else
		{
			// Tell Extract to return the closed folder icon
			*piIndex = ICON_INDEX_FOLDER;
		}
	}
	else
	{
		// Its not a folder
		*piIndex = ICON_INDEX_LOCKFILE;
	}

	return S_OK;
}


STDMETHODIMP CExtractIcon::Extract(LPCTSTR pszFile, UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, 
                                   UINT nIconSize)
{
	*phiconLarge = ImageList_GetIcon(g_himlLarge, nIconIndex, ILD_TRANSPARENT);
	*phiconSmall = ImageList_GetIcon(g_himlSmall, nIconIndex, ILD_TRANSPARENT);

	return S_OK;
}

