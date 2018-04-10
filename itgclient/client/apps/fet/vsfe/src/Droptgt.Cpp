// Implements CDropTarget.

#include "stdafx.h"
#include <shlobj.h>
#include "commands.h"
#include "resource.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "DropTgt.h"
#include "shlview.h"
#include "dataobj.h"
#include "viewlist.h"

extern CViewList *g_pViewList;
extern BOOL g_bLockedOut;
extern BOOL g_bDragSource;
extern TCHAR g_szInstallDir[MAX_PATH];

CDropTarget::CDropTarget(CShellFolder *psfParent, HWND hwndDrp)
{
	g_DllRefCount++;

	m_psfParent = psfParent;
	if(m_psfParent)
	   m_psfParent->AddRef();
	else
    {
	   delete this;
	   return;
    }

	m_pPidlMgr = new CPidlMgr();
	if(!m_pPidlMgr)
    {
	   delete this;
	   return;
    }

	SHGetMalloc(&m_pMalloc);
	if(!m_pMalloc)
    {
	   delete this;
	   return;
    }

	m_ObjRefCount = 1;

	m_fAcceptFmt = FALSE;
	m_CurrFormat = 0;
	m_hwndOwnerDropTgt = hwndDrp;

	m_EncryptDrag = TRUE;

	m_cfPrivateData = RegisterClipboardFormat(CFSTR_VSSAFE);
}



CDropTarget::~CDropTarget()
{
	if(m_psfParent)
	   m_psfParent->Release();

	if(m_pPidlMgr)
	   delete m_pPidlMgr;

	if(m_pMalloc)
	   m_pMalloc->Release();

	g_DllRefCount--;
}


// IUnknown Implementation
STDMETHODIMP CDropTarget::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	//IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
	   *ppReturn = this;

	//IDropTarget
	else if(IsEqualIID(riid, IID_IDropTarget))
	   *ppReturn = (IDropTarget*)this;

	if(*ppReturn)
    {
	   (*(LPUNKNOWN*)ppReturn)->AddRef();
	   return S_OK;
    }

	return E_NOINTERFACE;
}



STDMETHODIMP_(DWORD) CDropTarget::AddRef(VOID)
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CDropTarget::Release(VOID)
{
	if(--m_ObjRefCount == 0)
    {
		delete this;
		return 0;
    }
   
	return m_ObjRefCount;
}



// IDropTarget Implementation
STDMETHODIMP CDropTarget::DragEnter(LPDATAOBJECT pDataObj, DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{  
	FORMATETC fmtetc;

	fmtetc.cfFormat   = CF_HDROP;
	fmtetc.ptd        = NULL;
	fmtetc.dwAspect   = DVASPECT_CONTENT;
	fmtetc.lindex     = -1;
	fmtetc.tymed      = TYMED_HGLOBAL;

	// If we are the drag source then disable the CF_HDROP format
	if(g_bDragSource)
		m_fAcceptFmt = FALSE;
	else
		m_fAcceptFmt = (S_OK == pDataObj->QueryGetData(&fmtetc)) ? TRUE : FALSE;

	if(m_fAcceptFmt)
	{
		m_ptCurPos.x = -1;
		m_ptCurPos.y = -1;

		m_CurrFormat = CF_HDROP;

		// Check if file(s) in the physical Safe directory is selected for encryption. 
		// eg if file in 'c:\progra~1\verisign\safe\profilename' is selected then return FALSE
		if(!g_bLockedOut)
		{
			STGMEDIUM StgMedium;
			HRESULT hr = pDataObj->GetData(&fmtetc, &StgMedium);
			if(SUCCEEDED(hr))
			{
				TCHAR szFileDropped[MAX_PATH_LEN];
				DragQueryFile((HDROP)StgMedium.hGlobal, 0, szFileDropped, sizeof(szFileDropped));
				ReleaseStgMedium(&StgMedium);

				//if(!_strnicmp(szFileDropped, g_szStoragePath, lstrlen(g_szStoragePath)))
				if(!_strnicmp(szFileDropped, g_szInstallDir, lstrlen(g_szInstallDir)))
				{
					*pdwEffect = DROPEFFECT_NONE;
					return E_FAIL;
				}
			}
		}
	}
	else
	{
		m_ptCurPos.x = 0;
		m_ptCurPos.y = 0;

		fmtetc.cfFormat = m_cfPrivateData;
		m_fAcceptFmt = (S_OK == pDataObj->QueryGetData(&fmtetc)) ? TRUE : FALSE;
		m_CurrFormat = m_cfPrivateData;

		if(m_fAcceptFmt)
		{
			HRESULT hr = E_FAIL;
			STGMEDIUM StgMedium;

			hr = pDataObj->GetData(&fmtetc, &StgMedium);
			if(SUCCEEDED(hr))
			{
				LPDROPSRCDATA pData = (LPDROPSRCDATA)GlobalLock(StgMedium.hGlobal);
				LPCONTEXTMENU pContextMenu = NULL;
			
				// Check the status of the pidl. All pidl's will either be in the ENCRYPTED
				// or DECRYPTED state.
				if(m_pPidlMgr->IsFolder(pData->aPidls[0]) || m_pPidlMgr->GetStatus(pData->aPidls[0]) == ENCRYPTED)
					m_EncryptDrag = TRUE;
				else
					m_EncryptDrag = FALSE;
	
				GlobalUnlock(StgMedium.hGlobal);
				GlobalFree(StgMedium.hGlobal);
			}
		}
	}

	if(m_fAcceptFmt)
	{
		if(IsDropAllowed(m_EncryptDrag))
			QueryDrop(dwKeyState, pdwEffect);
		else
			*pdwEffect = DROPEFFECT_NONE;
	}
	else
		*pdwEffect = DROPEFFECT_NONE;

	return S_OK;
}



STDMETHODIMP CDropTarget::DragOver(DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
	if(m_fAcceptFmt)
	{
		if(IsDropAllowed(m_EncryptDrag))
			QueryDrop(dwKeyState, pdwEffect);
		else
			*pdwEffect = DROPEFFECT_NONE;
	}
	else
		*pdwEffect = DROPEFFECT_NONE;
	
	return S_OK;
}



STDMETHODIMP CDropTarget::DragLeave(VOID)
{
	m_fAcceptFmt = FALSE;
	m_CurrFormat = 0;
	return S_OK;
}



STDMETHODIMP CDropTarget::Drop(LPDATAOBJECT pDataObj, DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{   
	HRESULT hr = E_FAIL;
	TCHAR szDestFolder[MAX_PATH_LEN];

	if(g_bLockedOut)
		if(!LogIn(TRUE))
			return hr;

	if(QueryDrop(dwKeyState, pdwEffect))
	{
		FORMATETC fmtetc;
		STGMEDIUM StgMedium;

		fmtetc.cfFormat   = CF_HDROP;
		fmtetc.ptd        = NULL;
		fmtetc.dwAspect   = DVASPECT_CONTENT;
		fmtetc.lindex     = -1;
		fmtetc.tymed      = TYMED_HGLOBAL;

		// If we are the drag source then disable the CF_HDROP format
		if(g_bDragSource)
			hr = E_FAIL;
		else
			hr = pDataObj->GetData(&fmtetc, &StgMedium);

		if(SUCCEEDED(hr))
		{
			// Check if file(s) in the physical Safe directory is being dropped. eg if file 
			// in 'c:\progra~1\verisign\safe\profilename' is dropped on Safe return FALSE
			TCHAR szFileDropped[MAX_PATH_LEN];
			DragQueryFile((HDROP)StgMedium.hGlobal, 0, szFileDropped, sizeof(szFileDropped));
			if(!_strnicmp(szFileDropped, g_szStoragePath, lstrlen(g_szStoragePath)))
				return E_FAIL;

			m_psfParent->GetPath(NULL, szDestFolder, MAX_PATH_LEN);

			EncryptDroppedItems(m_hwndOwnerDropTgt, (HDROP)StgMedium.hGlobal, (const PTCHAR)szDestFolder);

			// Release the STGMEDIUM
			ReleaseStgMedium(&StgMedium);
		}
	   	else
		{
			// Drag/Drop between the encrypted/decrypted views
		   fmtetc.cfFormat   = m_cfPrivateData;

		   hr = pDataObj->GetData(&fmtetc, &StgMedium);
		   if(SUCCEEDED(hr))
		   {
				LPDROPSRCDATA pData = (LPDROPSRCDATA)GlobalLock(StgMedium.hGlobal);
				LPCONTEXTMENU pContextMenu = NULL;

				m_psfParent->GetUIObjectOf(m_hwndOwnerDropTgt, pData->uItemCount, (LPCITEMIDLIST*)pData->aPidls,
										   IID_IContextMenu, NULL, (LPVOID*)&pContextMenu);

				CMINVOKECOMMANDINFO cmi;

				ZeroMemory(&cmi, sizeof(cmi));
				cmi.cbSize = sizeof(cmi);
				cmi.hwnd = m_hwndOwnerDropTgt;

				// Check the status of the pidl. All pidl's will either be in the ENCRYPTED
				// or DECRYPTED state.
				if(m_pPidlMgr->IsFolder(pData->aPidls[0]) ||
				   m_pPidlMgr->GetStatus(pData->aPidls[0]) == ENCRYPTED)
					cmi.lpVerb = (LPCSTR)MAKEINTRESOURCE(IDM_DECRYPT_VERIFY);
				else
				{
					g_bPrompt = TRUE;  // Always set this to TRUE initially
					cmi.lpVerb = (LPCSTR)MAKEINTRESOURCE(IDM_ENCRYPT);
				}
	
				pContextMenu->InvokeCommand(&cmi);

				pContextMenu->Release();

				GlobalUnlock(StgMedium.hGlobal);
				GlobalFree(StgMedium.hGlobal);
			}
		}

		// Refresh all the views
		CShellView *pView;
		pView = g_pViewList->GetNextView(NULL);
		while(pView)
		{
			pView->Refresh();
			pView = g_pViewList->GetNextView(pView);
		}
	}

	*pdwEffect = DROPEFFECT_NONE;

	return hr;
}



BOOL CDropTarget::QueryDrop(DWORD dwKeyState, LPDWORD pdwEffect)
{
	DWORD dwOKEffects = *pdwEffect;

	*pdwEffect = DROPEFFECT_NONE;

	*pdwEffect = GetDropEffectFromKeyState(dwKeyState);

	// we don't accept links
	if(DROPEFFECT_LINK == *pdwEffect)
		*pdwEffect = DROPEFFECT_NONE;

	// Check if the drag source application allows the drop effect desired by the 
	// user. The drag source specifies this in DoDragDrop. 
	if(*pdwEffect & dwOKEffects)
		return TRUE;

	return FALSE;
}



DWORD CDropTarget::GetDropEffectFromKeyState(DWORD dwKeyState)
{
	// move is the default
	DWORD dwDropEffect = DROPEFFECT_MOVE;

	if(dwKeyState & MK_CONTROL)
    {
	   if(dwKeyState & MK_SHIFT)
		  dwDropEffect = DROPEFFECT_LINK;
	   else
		  dwDropEffect = DROPEFFECT_COPY;
	}

	return dwDropEffect;
}




LPITEMIDLIST* CDropTarget::AllocPidlTable(DWORD dwEntries)
{
	LPITEMIDLIST   *aPidls;

	dwEntries++;

	aPidls = (LPITEMIDLIST*)m_pMalloc->Alloc(dwEntries * sizeof(LPITEMIDLIST));

	if(aPidls)
	   ZeroMemory(aPidls, dwEntries * sizeof(LPITEMIDLIST));

	return aPidls;
}




VOID CDropTarget::FreePidlTable(LPITEMIDLIST *aPidls)
{
	if(aPidls && m_pPidlMgr)
	{
		UINT  i;
		for(i = 0; aPidls[i]; i++)
			m_pPidlMgr->Delete(aPidls[i]);
   
		m_pMalloc->Free(aPidls);
	}
}


BOOL CDropTarget::IsDropAllowed(BOOL bEncryptDrag)
{
	BOOL bDropAllowed = FALSE;

	if(m_hwndOwnerDropTgt)
	{
		CShellView *pView = (CShellView *)GetViewInterface(m_hwndOwnerDropTgt);

		if(pView)
		{
			bDropAllowed = pView->DropAllowed(&m_ptCurPos, bEncryptDrag);
			pView->Release();
		}
		else
		{
			if(m_CurrFormat == CF_HDROP)
				bDropAllowed = TRUE;
		}
	}

	return bDropAllowed;
}