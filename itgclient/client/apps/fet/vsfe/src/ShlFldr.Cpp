// Implements CShellFolder.

#include "stdafx.h"
#include <shlobj.h>
#include <prsht.h>
#include <stdio.h>
#include "resource.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "pidlmgr.h"
#include "ShlFldr.h"
#include "ShlView.h"
#include "ExtrIcon.h"
#include "ContMenu.h"
#include "DataObj.h"
#include "DropTgt.h"
#include "ViewList.h"
#include "Guid.h"
#include "enumidl.h"
#include "dlgprocs.h"
#include "vspmspP.h"	// from PM api
#include "vspmutil.h"	// from PM api
#include "vspmsp.h"		// from PM api
#include "policysup.h"


extern BOOL DecryptAtLogon();
extern CViewList *g_pViewList;
extern BOOL g_bLockedOut;
extern BOOL g_bPasswdFail;
extern SafeSettings g_SafeProp;
extern TCHAR g_szPolicyFile[];
extern PolicyVars g_LocalPolicy;
extern TCHAR g_szWinDir[MAX_PATH_LEN], g_szWinSysDir[MAX_PATH_LEN];

extern VOID CreateHiddenWindow(VOID);
extern VOID DestroyHiddenWindow(VOID);

BOOL g_bSafeClicked = FALSE;

CShellFolder::CShellFolder(CShellFolder *pParent, LPCITEMIDLIST pidl)
{
	g_DllRefCount++;

	m_psfParent = pParent;
	if(m_psfParent)
	   m_psfParent->AddRef();

	m_pPidlMgr = new CPidlMgr();
	if(!m_pPidlMgr)
    {
	   delete this;
	   return;
    }

	if(FAILED(SHGetMalloc(&m_pMalloc)))
    {
	   delete this;
	   return;
    }

	m_pDataObj	= NULL;
	m_pidlFQ	= NULL;
	m_pidlRel	= NULL;
	if(pidl)
		m_pidlRel = m_pPidlMgr->Copy(pidl);

	m_bSafeClicked = FALSE;
	m_ObjRefCount = 1;
}


CShellFolder::~CShellFolder()
{
	if(m_pidlRel)
	{
		m_pPidlMgr->Delete(m_pidlRel);
		m_pidlRel = NULL;
	}

	if(m_pidlFQ)
	{
		m_pPidlMgr->Delete(m_pidlFQ);
		m_pidlFQ = NULL;
	}

	if(m_psfParent)
		m_psfParent->Release();

	if(m_pMalloc)
		m_pMalloc->Release();

	if(m_pPidlMgr)
		delete m_pPidlMgr;

    if (m_pDataObj)
        m_pDataObj->Release();

	g_bSafeClicked = FALSE;

	g_DllRefCount--;
}


// IUnknown Implementation
STDMETHODIMP CShellFolder::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	//IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = this;

	//IShellFolder
	else if(IsEqualIID(riid, IID_IShellFolder))
		*ppReturn = (IShellFolder*)this;

#if 0
	//IPersist
	else if(IsEqualIID(riid, IID_IPersist))
		*ppReturn = (IPersist*)this;
#endif

	//IPersistFolder
	else if(IsEqualIID(riid, IID_IPersistFolder))
		*ppReturn = (IPersistFolder*)this;

	//IContextMenu
	else if(IsEqualIID(riid, IID_IContextMenu))
		*ppReturn = (IContextMenu*)this;

	//IShellExtInit
	else if(IsEqualIID(riid, IID_IShellExtInit))
		*ppReturn = (IShellExtInit*)this;

	//IShellPropSheetExt
	else if(IsEqualIID(riid, IID_IShellPropSheetExt))
		*ppReturn = (IShellPropSheetExt*)this;

	//IExtractIcon
	else if(IsEqualIID(riid, IID_IExtractIcon))
		*ppReturn = (IExtractIcon*)this;

	//IPersistFile
	else if(IsEqualIID(riid, IID_IPersistFile))
		*ppReturn = (IPersistFile*)this;

	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             


STDMETHODIMP_(DWORD) CShellFolder::AddRef(VOID)
{
	return ++m_ObjRefCount;
}


STDMETHODIMP_(DWORD) CShellFolder::Release(VOID)
{
	if(--m_ObjRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}


#if 0
// IPersist Implementation
STDMETHODIMP CShellFolder::GetClassID(LPCLSID lpClassID)
{
	*lpClassID = CLSID_VSSafe;
	return S_OK;
}
#endif


// IPersistFolder Implementation
STDMETHODIMP CShellFolder::Initialize(LPCITEMIDLIST pidlFQ)
{
	if(m_pidlFQ)
	{
		m_pPidlMgr->Delete(m_pidlFQ);
		m_pidlFQ = NULL;
	}

	m_pidlFQ = m_pPidlMgr->Copy(pidlFQ);

	return S_OK;
}



// IShellFolder Implementation
STDMETHODIMP CShellFolder::BindToObject(LPCITEMIDLIST pidl, LPBC pbcReserved, 
                                        REFIID riid, LPVOID *ppvOut)
{
	*ppvOut = NULL;

	// Make sure the item is a folder.
	ULONG ulAttribs = SFGAO_FOLDER;
	this->GetAttributesOf(1, &pidl, &ulAttribs);
	if(!(ulAttribs & SFGAO_FOLDER))
		return E_INVALIDARG;

	CShellFolder   *pShellFolder = new CShellFolder(this, pidl);
	if(!pShellFolder)
		return E_OUTOFMEMORY;

	LPITEMIDLIST   pidlTemp = m_pPidlMgr->Concatenate(m_pidlFQ, pidl);
	pShellFolder->Initialize(pidlTemp);
	m_pPidlMgr->Delete(pidlTemp);

	HRESULT  hr = pShellFolder->QueryInterface(riid, ppvOut);

	pShellFolder->Release();

	return hr;
}



STDMETHODIMP CShellFolder::BindToStorage(LPCITEMIDLIST pidl, LPBC pbcReserved, 
                                         REFIID riid, LPVOID *ppvOut)
{
	*ppvOut = NULL;
	return E_NOTIMPL;
}



STDMETHODIMP CShellFolder::CompareIDs(LPARAM lParam, LPCITEMIDLIST pidl1, 
                                      LPCITEMIDLIST pidl2)
{
	HRESULT        hr = E_FAIL;
	LPITEMIDLIST   pidlTemp1;
	LPITEMIDLIST   pidlTemp2;

	// Walk down the lists, comparing each individual item

	pidlTemp1 = (LPITEMIDLIST)pidl1;
	pidlTemp2 = (LPITEMIDLIST)pidl2;

	while(pidlTemp1 && pidlTemp2)
	{
		hr = CompareItems(pidlTemp1, pidlTemp2);
		if(HRESULT_CODE(hr))
		  break;				// The items are different
		  

		pidlTemp1 = m_pPidlMgr->GetNextItem(pidlTemp1);
		pidlTemp2 = m_pPidlMgr->GetNextItem(pidlTemp2);

		if(pidlTemp1 && !pidlTemp1->mkid.cb)
		  pidlTemp1 = NULL;

		if(pidlTemp2 && !pidlTemp2->mkid.cb)
		  pidlTemp2 = NULL;

		hr = E_FAIL;
	}

	if(!pidlTemp1 && pidlTemp2)
	{
		// Pidl1 is at a higher level than pidl2
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(-1));
	}
	else if(pidlTemp1 && !pidlTemp2)
	{
		// Pidl2 is at a higher level than pidl1
		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(1));
	}
	else if(SUCCEEDED(hr))
	{
		// The items are at the same level but are different
		return hr;
	}

	// The items are the same
	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, 0);
}



STDMETHODIMP CShellFolder::CreateViewObject(HWND hwndOwner, REFIID riid, LPVOID *ppvOut)
{
	HRESULT  hr = E_NOINTERFACE;

	if(IsEqualIID(riid, IID_IShellView))
	{
		CShellView  *pShellView;

		*ppvOut = NULL;

		if(g_bLockedOut)
		{
			LoginStat State = AuthenticateUser();
			if(State == LOGIN_CANCEL)
				return E_INVALIDARG;
			else
				if(State == LOGIN_OK)
				{
					/*if(!InitSafe())
						return E_INVALIDARG;*/

					HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

					DecryptAtLogon();

					if(hOldCur)
						SetCursor(hOldCur);

					g_bLockedOut = FALSE;

					UpdateSafeIcon();

					CreateHiddenWindow();

					// If any view were hidden, show them now
					CShellView *pView;
					pView = g_pViewList->GetNextView(NULL);
					while(pView)
					{
						pView->ShowViewWindow();		
						pView = g_pViewList->GetNextView(pView);
					}

				}
		}

		pShellView = new CShellView(this, m_pidlRel);
		if(!pShellView)
			return E_INVALIDARG;

		hr = pShellView->QueryInterface(riid, ppvOut);

		pShellView->Release();
	}
	else if(IsEqualIID(riid, IID_IDropTarget))
	{
#if 0
		*ppvOut = NULL;

		CDropTarget *pdt = new CDropTarget(this, hwndOwner);
		if(pdt)
		{
			*ppvOut = pdt;
			return S_OK;
		}
#else
		// though the Safe is a drop target, we are not 
		// supporting it here bcos the 'Paste' menu option
		// comes when you right click the Safe when something
		// is there in the clipboard. drop target functionality
		// is supported by registering the the window as
		// a drop target when the window is created OnCreate()
		if(GetCapture())
		{
			*ppvOut = NULL;

			CDropTarget *pdt = new CDropTarget(this, hwndOwner);
			if(pdt)
			{
				*ppvOut = pdt;
				return S_OK;
			}
		}
		else
		{
			*ppvOut = NULL;
			return E_OUTOFMEMORY;
		}
#endif

	}
	else if(IsEqualIID(riid, IID_IContextMenu))
	{
		// Create a context menu object for this folder. This can be used for the 
		// background of a view.
		*ppvOut = NULL;

		CContextMenu *pcm = new CContextMenu(this);
		if(pcm)
		{
			*ppvOut = pcm;
			return S_OK;
		}
	}

	return hr;
}



STDMETHODIMP CShellFolder::EnumObjects(HWND hwndOwner, DWORD dwFlags, 
                                       LPENUMIDLIST *ppEnumIDList)
{
	*ppEnumIDList = NULL;

	if(g_bLockedOut)
		return E_OUTOFMEMORY;

	TCHAR szPath[MAX_PATH];
	GetPath(NULL, szPath, MAX_PATH);
	*ppEnumIDList = new CEnumIDList(szPath, dwFlags);
	if(!*ppEnumIDList)
		return E_OUTOFMEMORY;

	return S_OK;
}



STDMETHODIMP CShellFolder::GetAttributesOf(UINT uCount, LPCITEMIDLIST aPidls[], 
                                           LPDWORD pdwAttribs)
{
	UINT i;

	if(IsBadWritePtr(pdwAttribs, sizeof(DWORD)))
		return E_INVALIDARG;

	if(0 == uCount)
	{
		// This can happen in the Win95 shell when the view is run in rooted mode. 
		// When this occurs, return the attributes for a plain old folder.
		
		*pdwAttribs = SFGAO_FOLDER | SFGAO_HASSUBFOLDER | SFGAO_DROPTARGET | 
					  SFGAO_HASPROPSHEET |SFGAO_BROWSABLE;
	}

	for(i = 0; i < uCount; i++)
	{
		DWORD dwAttribs = 0;

		// Is this item a folder?
		if(m_pPidlMgr->IsFolder(m_pPidlMgr->GetLastItem(aPidls[i])))
		  {
			  dwAttribs |= SFGAO_FOLDER | SFGAO_DROPTARGET | SFGAO_CANLINK | 
						   SFGAO_HASPROPSHEET | SFGAO_BROWSABLE;

			  // Does this folder item have any sub folders?
			  if(HasSubFolder(aPidls[i]))
				 dwAttribs |= SFGAO_HASSUBFOLDER;
		  }

		*pdwAttribs &= dwAttribs;
	}

	return S_OK;
}



STDMETHODIMP CShellFolder::GetUIObjectOf(HWND hwndOwner, UINT uCount, 
                                         LPCITEMIDLIST *pPidls, REFIID riid, 
                                         LPUINT puReserved, LPVOID *ppvOut)
{
	*ppvOut = NULL;

	if(IsEqualIID(riid, IID_IContextMenu))
	{
		CContextMenu   *pcm = new CContextMenu(this, pPidls, uCount);

		if(pcm)
		{
			*ppvOut = pcm;
			return S_OK;
		}
	}

	else if(IsEqualIID(riid, IID_IDataObject))
	{
		CDataObject *pdo = new CDataObject(this, pPidls, uCount);

		if(pdo)
		{
			*ppvOut = pdo;
			return S_OK;
		}
	}

	if(uCount != 1)
		return E_INVALIDARG;

	if(IsEqualIID(riid, IID_IExtractIcon))
	{
		CExtractIcon   *pei;
		LPITEMIDLIST   pidl;

		pidl = m_pPidlMgr->Concatenate(m_pidlRel, pPidls[0]);

		pei = new CExtractIcon(pidl);

		// The temp PIDL can be deleted because the new CExtractIcon either failed or 
		// made its own copy of it.

		m_pPidlMgr->Delete(pidl);

		if(pei)
		{
			*ppvOut = pei;
			return S_OK;
		}

		return E_OUTOFMEMORY;
	}
	else if(IsEqualIID(riid, IID_IDropTarget))
	{
		CShellFolder *psfTemp = NULL;

		BindToObject(pPidls[0], NULL, IID_IShellFolder, (LPVOID*)&psfTemp);

		if(psfTemp)
		{
			CDropTarget *pdt = new CDropTarget(psfTemp, hwndOwner);

			psfTemp->Release();

			if(pdt)
			{
				*ppvOut = pdt;
				return S_OK;
			}
		}
	}

	return E_NOINTERFACE;
}



STDMETHODIMP CShellFolder::GetDisplayNameOf(LPCITEMIDLIST pidl, DWORD dwFlags, 
                                            LPSTRRET lpName)
{
	TCHAR szText[MAX_PATH] = TEXT("");
	int cchOleStr;

	// Check if locked out. IF so then don't allow enumeration of 
	// folders in left pane of Explorer
	if(g_bLockedOut)
	{
		CShellView *pView;
		pView = g_pViewList->GetNextView(NULL);
		while(pView)
		{
			pView->CollapseTree();
			pView = g_pViewList->GetNextView(pView);
		}
		
		lpName->uType = STRRET_WSTR;
		lpName->pOleStr = NULL;
		return E_NOTIMPL;
	}

	if(dwFlags & SHGDN_FORPARSING)
	{
		// A "path" is being requested - is it full or relative?
		if(dwFlags & SHGDN_INFOLDER)
		{
			// The relative path is being requested
			m_pPidlMgr->GetRelativeName(pidl, szText, ARRAYSIZE(szText));
		}
		else
			GetFullName(pidl, szText, ARRAYSIZE(szText), dwFlags);
	}
	else
	{
		// Only the text of the last item is being requested
		LPITEMIDLIST   pidlLast = m_pPidlMgr->GetLastItem(pidl);
		m_pPidlMgr->GetRelativeName(pidlLast, szText, ARRAYSIZE(szText));
	}

	// Get the number of characters required
	cchOleStr = lstrlen(szText) + 1;

	// Allocate the wide character string
	lpName->pOleStr = (LPWSTR)m_pMalloc->Alloc(cchOleStr * sizeof(WCHAR));
	if(!lpName->pOleStr)
		return E_OUTOFMEMORY;

	lpName->uType = STRRET_WSTR;

	LocalToWideChar(lpName->pOleStr, szText, cchOleStr);

	return S_OK;
}



STDMETHODIMP CShellFolder::ParseDisplayName(HWND hwndOwner, LPBC pbcReserved, 
                                            LPOLESTR lpDisplayName, LPDWORD pdwEaten, 
                                            LPITEMIDLIST *pPidlNew, LPDWORD pdwAttributes)
{
	return E_NOTIMPL;
}



STDMETHODIMP CShellFolder::SetNameOf(HWND hwndOwner, LPCITEMIDLIST pidl, 
									 LPCOLESTR lpName, DWORD dwFlags, 
                                     LPITEMIDLIST *ppidlOut)
{
	return E_NOTIMPL;
}




VOID CShellFolder::GetFullName(LPCITEMIDLIST pidl, LPTSTR pszText, DWORD dwSize, 
                               DWORD dwFlags)
{
	*pszText = 0;

	// Get the name of our fully-qualified PIDL from the desktop folder.
	IShellFolder *psfDesktop = NULL;
	SHGetDesktopFolder(&psfDesktop);
	if(psfDesktop)
	{
		STRRET   str;
		if(SUCCEEDED(psfDesktop->GetDisplayNameOf(m_pidlFQ, dwFlags, &str)))
		{
			GetTextFromSTRRET(m_pMalloc, &str, m_pidlFQ, pszText, dwSize);
			if(*pszText)
				SmartAppendBackslash(pszText);
		}

		psfDesktop->Release();
	}

	// Add the current item's text
	m_pPidlMgr->GetRelativeName(pidl, pszText + lstrlen(pszText), 
								dwSize - lstrlen(pszText));
}


LPITEMIDLIST CShellFolder::CreateFQPidl(LPCITEMIDLIST pidl)
{
	return m_pPidlMgr->Concatenate(m_pidlFQ, pidl);
}



VOID CShellFolder::GetPath(LPCITEMIDLIST pidl, LPTSTR pszPath, DWORD dwSize)
{
	CShellFolder   **ppsf;
	CShellFolder   *psfCurrent;
	int            nCount;

	*pszPath = 0;

	// We need the number of parent items in the chain
	for(nCount = 0, psfCurrent = this; psfCurrent; nCount++)
		psfCurrent = psfCurrent->m_psfParent;

	ppsf = (CShellFolder**)m_pMalloc->Alloc(nCount * sizeof(CShellFolder*));
	if(ppsf)
	{
		int   i;

		// Fill in the interface pointer array
		for(i = 0, psfCurrent = this; i < nCount; i++)
		{
			*(ppsf + i) = psfCurrent;
			psfCurrent = psfCurrent->m_psfParent;
		}

		// Get the name of the root of our storage.
		lstrcpyn(pszPath, g_szStoragePath, dwSize);

		SmartAppendBackslash(pszPath);

		// Starting at the top of the parent chain, walk down, getting the text for 
		// each folder's PIDL.
		for(i = nCount - 1; i >= 0; i--)
		{
			psfCurrent = *(ppsf + i);
			if(psfCurrent)
			{
				LPTSTR   pszCurrent = pszPath + lstrlen(pszPath);
				DWORD    dwCurrentSize = dwSize - lstrlen(pszPath);

				m_pPidlMgr->GetRelativeName(psfCurrent->m_pidlRel, pszCurrent, 
											dwCurrentSize);
				SmartAppendBackslash(pszPath);
			}
		}

		// Add the item's path
		if(pidl)
		{
			m_pPidlMgr->GetRelativeName(pidl, pszPath + lstrlen(pszPath), 
			dwSize - lstrlen(pszPath));
		}

		m_pMalloc->Free(ppsf);
	}

	if(pszPath[lstrlen(pszPath) - 1] == '\\')
		pszPath[lstrlen(pszPath) - 1] = '\0';

}



BOOL CShellFolder::HasSubFolder(LPCITEMIDLIST pidl)
{
	TCHAR           szPath[MAX_PATH], szTemp[MAX_PATH];
	HANDLE          hFind;
	WIN32_FIND_DATA wfd;
	BOOL            fReturn = FALSE;

	if(!m_pPidlMgr->IsFolder(pidl))
		return FALSE;

	GetPath(pidl, szPath, MAX_PATH);
	lstrcpy(szTemp, szPath);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));

	hFind = FindFirstFile(szTemp, &wfd);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if((FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes) && 
				lstrcmpi(wfd.cFileName, TEXT(".")) && 
				lstrcmpi(wfd.cFileName, TEXT("..")))
			{
					fReturn = TRUE;
					break;
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

	return fReturn;
}


// Called when files are being encrypted. This is when a file is selected in the
// list view showing decrypted contents.
STDMETHODIMP CShellFolder::UpdateDecrItems(LPCSTR szDestPath, LPITEMIDLIST* pPidl)
{
	TCHAR szFileInfo[MAX_PATH], *pBSlash = NULL;
	TCHAR szOrigLocation[MAX_PATH], szOrigValue[32];
	DWORD dwOrigSize;
	FILETIME ftDateCreated, ftDateModified, ftDateAccessed;
	FileStatus Status;
	LPITEMIDLIST pidl;

	// Create the fileinfo path
	lstrcpy(szFileInfo, szDestPath);
	pBSlash = strrchr(szFileInfo, '\\');
	lstrcpy(pBSlash + 1, "fileinfo");

	// Get the section name. It is the file name
	pBSlash = strrchr(szDestPath, '\\') + 1;

	// Get the info from the fileinfo.ini file and construct the pidl
	GetPrivateProfileString(pBSlash, "OrigLocation", "c:\\temp",
							szOrigLocation, MAX_PATH, szFileInfo);

	GetPrivateProfileString(pBSlash, "OrigSize", "0x00000000",
							szOrigValue, 32, szFileInfo);
	dwOrigSize = atol(szOrigValue);
	
	GetPrivateProfileString(pBSlash, "DateCreatedLow", "0x00000000",
							szOrigValue, 32, szFileInfo);
 	ftDateCreated.dwLowDateTime = atol(szOrigValue);

	GetPrivateProfileString(pBSlash, "DateCreatedHigh", "0x00000000",
							szOrigValue, 32, szFileInfo);
	ftDateCreated.dwHighDateTime = atol(szOrigValue);

	GetPrivateProfileString(pBSlash, "DateModifiedLow", "0x00000000",
							szOrigValue, 32, szFileInfo);
 	ftDateModified.dwLowDateTime = atol(szOrigValue);

	GetPrivateProfileString(pBSlash, "DateModifiedHigh", "0x00000000",
							szOrigValue, 32, szFileInfo);
	ftDateModified.dwHighDateTime = atol(szOrigValue);

	GetPrivateProfileString(pBSlash, "DateAccessedLow", "0x00000000",
							szOrigValue, 32, szFileInfo);
 	ftDateAccessed.dwLowDateTime = atol(szOrigValue);

	GetPrivateProfileString(pBSlash, "DateAccessedHigh", "0x00000000",
							szOrigValue, 32, szFileInfo);
	ftDateAccessed.dwHighDateTime = atol(szOrigValue);

	Status = (FileStatus)GetPrivateProfileInt(pBSlash, "Status", DELETED, szFileInfo);

	pidl = m_pPidlMgr->CreateItemPidl(pBSlash, szOrigLocation, dwOrigSize,
						&ftDateCreated, &ftDateAccessed, &ftDateModified, Status);

	// Now update the view. 
	LPITEMIDLIST pidlFQ = CreateFQPidl(*pPidl);
	SHChangeNotify(SHCNE_DELETE, SHCNF_IDLIST, pidlFQ, NULL);

	NotifyViews(SHCNE_UPDATEITEM, *pPidl, pidl);

	// Update all views o that proper menu's are displayed
	//UpdateViews();

	m_pPidlMgr->Delete(pidlFQ);
	m_pPidlMgr->Delete(pidl);

	return S_OK;
}


void CShellFolder::UpdateViews()
{
	if(g_pViewList)
	{
		CShellView *pView;

		pView = g_pViewList->GetNextView(NULL);
		while(pView)
		{
			pView->OnActivate(SVUIA_ACTIVATE_FOCUS);
			pView = g_pViewList->GetNextView(pView);
		}
	}
}



// Called when files are being opened(decrypted)
STDMETHODIMP CShellFolder::UpdateEncrItems(LPITEMIDLIST *aPidls, UINT uCount)
{
	HRESULT  hr = E_FAIL;
	UINT     i;

	for(i = 0; i < uCount; i++)
	{
		if(m_pPidlMgr->IsFolder(aPidls[i]))
			return hr;	// This shld be called only for files
		else
		{
			TCHAR szFile[MAX_PATH], szFileInfo[MAX_PATH], *pBSlash;

			// Get the file name
			GetPath(aPidls[i], szFile, MAX_PATH);

			// Construct the path of the 'fileinfo' file
			lstrcpy(szFileInfo, szFile);
			pBSlash = strrchr(szFileInfo, '\\');
			lstrcpy(pBSlash + 1, "fileinfo");

			// Point to the file name. this is the section name in the ini file
			pBSlash = strrchr(szFile, '\\') + 1;

			// Mark the status of the file as out of Safe, '1' = DECRYPTED
			WritePrivateProfileString(pBSlash, "Status", "1", szFileInfo);

			// Update the 'date created' field in the fileinfo, this
			// is displayed in the 'decrypted view'
			TCHAR szOrigLocation[MAX_PATH], szOrigValue[MAX_PATH];
			strcpy(szOrigLocation, m_pPidlMgr->GetOriginalLocation(aPidls[i]));
			HANDLE hFile = CreateFile(szOrigLocation, GENERIC_READ, FILE_SHARE_READ, NULL, 
					   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);

			BY_HANDLE_FILE_INFORMATION fad;
			GetFileInformationByHandle(hFile, &fad);
			CloseHandle(hFile);

			sprintf(szOrigValue, "%u", fad.ftCreationTime.dwLowDateTime);
			WritePrivateProfileString(pBSlash, "DateCreatedLow", szOrigValue, szFileInfo);

			sprintf(szOrigValue, "%u", fad.ftCreationTime.dwHighDateTime);
			WritePrivateProfileString(pBSlash, "DateCreatedHigh", szOrigValue, szFileInfo);

			// Delete the file from the directory in the Safe. Need to delete bcos
			// an unencrypted shld not be present in Safe
			DeleteFile(szFile);

			// Now update the view. 
			m_pPidlMgr->SetStatus(aPidls[i], DECRYPTED);
			//LPITEMIDLIST pidlFQ = CreateFQPidl(aPidls[i]);
			//SHChangeNotify(SHCNE_DELETE, SHCNF_IDLIST, pidlFQ, NULL);

			NotifyViews(SHCNE_UPDATEITEM, aPidls[i], NULL);

			//m_pPidlMgr->Delete(pidlFQ);
			
			hr = S_OK;
		}
	} // end for()

	return hr;

}



STDMETHODIMP CShellFolder::DeleteItems(LPITEMIDLIST *aPidls, UINT uCount)
{
	HRESULT  hr = E_FAIL;
	UINT     i;

	for(i = 0; i < uCount; i++)
	{
		if(!m_pPidlMgr->IsFolder(aPidls[i]))
		{
			TCHAR szFile[MAX_PATH], szFileInfo[MAX_PATH], *pBSlash;
   
			//get the file name. delete the file
			GetPath(aPidls[i], szFile, MAX_PATH);
			
			DeleteFile(szFile);

			// Mark the status in the ini file as DELETED
			// Construct the path of the 'fileinfo" file
			lstrcpy(szFileInfo, szFile);
			pBSlash = strrchr(szFileInfo, '\\');
			szFileInfo[pBSlash - szFileInfo + 1] = '\0';
			lstrcat(szFileInfo, "fileinfo");

			// Point to the file name. this is the section name is the ini file
			pBSlash = strrchr(szFile, '\\') + 1;

			// Mark the status of the file as out of Safe
			TCHAR szTemp[16];
			wsprintf(szTemp, "%d", DELETED);
			WritePrivateProfileString(pBSlash, "Status", szTemp, szFileInfo);

			// Delete the PIDL and update the view
			LPITEMIDLIST pidlFQ = CreateFQPidl(aPidls[i]);

			SHChangeNotify(SHCNE_DELETE, SHCNF_IDLIST, pidlFQ, NULL);

			NotifyViews(SHCNE_DELETE, aPidls[i], NULL);

			m_pPidlMgr->Delete(pidlFQ);

			hr = S_OK;
		}
	}

	return hr;
}



// This function is used to notify any existing views that something has 
// changed. This is necessary because there is no public way to register for 
// change notifications that get generated in response to SHChangeNotify. 
// Each CShellView adds itself to g_pViewList when it gets created and 
// removes itself from g_pViewList when it is destroyed.
VOID CShellFolder::NotifyViews(DWORD dwType, LPCITEMIDLIST pidlOld, 
                               LPCITEMIDLIST pidlNew)
{
	IShellFolder *psfDesktop;
	SHGetDesktopFolder(&psfDesktop);
	if(psfDesktop)
	{
		if(g_pViewList)
		{
			CShellView *pView;

			pView = g_pViewList->GetNextView(NULL);
			while(pView)
			{
				LPITEMIDLIST pidlView = CreateFQPidl(NULL);

				HRESULT hr;
				hr = psfDesktop->CompareIDs(0, m_pidlFQ, pidlView);
				if(SUCCEEDED(hr) && 0 == HRESULT_CODE(hr))
				{
					switch(dwType)
					{
						case SHCNE_MKDIR:
						case SHCNE_CREATE:
							pView->AddEncrItem(pidlOld);
							break;

						case SHCNE_RMDIR:
						case SHCNE_DELETE:
							pView->DeleteItem(pidlOld);
							break;

						case SHCNE_UPDATEITEM:							
							pView->UpdateData(pidlOld, pidlNew);

							// Update all views o that proper menu's are displayed
							pView->OnActivate(SVUIA_ACTIVATE_FOCUS);
							break;
					}
				}
				pView = g_pViewList->GetNextView(pView);
				m_pPidlMgr->Delete(pidlView);
			}
		}
		psfDesktop->Release();
	}
}



STDMETHODIMP CShellFolder::CompareItems(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
	TCHAR szString1[MAX_PATH] = TEXT("");
	TCHAR szString2[MAX_PATH] = TEXT("");

	// Special case - If one of the items is a folder and the other is an item, always 
	// make the folder come before the item.
	if(m_pPidlMgr->IsFolder(pidl1) != m_pPidlMgr->IsFolder(pidl2))
		return MAKE_HRESULT( SEVERITY_SUCCESS, 
								0, 
								USHORT(m_pPidlMgr->IsFolder(pidl1) ? -1 : 1));

	m_pPidlMgr->GetRelativeName(pidl1, szString1, ARRAYSIZE(szString1));
	m_pPidlMgr->GetRelativeName(pidl2, szString2, ARRAYSIZE(szString2));

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(lstrcmpi(szString1, szString2)));
}



//IContextMenu methods
STDMETHODIMP CShellFolder::QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst,
											UINT idCmdLast, UINT uFlags)
{
	TCHAR szMenuText[32];
	UINT idCmd = idCmdFirst;

	if(CanDecrypt(m_pDataObj))
	{
		LoadString(g_hInst, IDS_DECRYPT, szMenuText, sizeof(szMenuText));

		InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

		InsertMenu(hMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, szMenuText);

		InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

		// Must return number of menu items we added.
		return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(idCmd-idCmdFirst))); 
	}
	else
		if(CanEncryptSingleSel(m_pDataObj))
		{
			if ((uFlags & 0x000F) == CMF_NORMAL || (uFlags & CMF_EXPLORE) ||
				(uFlags & CMF_VERBSONLY))
			{
				LoadString(g_hInst, IDS_ENCRYPT, szMenuText, sizeof(szMenuText));

				InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

				InsertMenu(hMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, szMenuText);

				InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

				// Must return number of menu items we added.
				return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(idCmd-idCmdFirst))); 
			}
		}


	// Right click on desktop icon or explorer left pane icon
	FORMATETC fmtetc;
	STGMEDIUM StgMedium;
	HRESULT hr;

	fmtetc.cfFormat	= CF_HDROP;
	fmtetc.ptd		= NULL;
	fmtetc.dwAspect = DVASPECT_CONTENT;
	fmtetc.lindex   = -1;
	fmtetc.tymed    = TYMED_HGLOBAL;

	hr = m_pDataObj->GetData(&fmtetc, &StgMedium);
	if(FAILED(hr) && m_bSafeClicked)
	{
		if(g_bLockedOut)
			LoadString(g_hInst, IDS_UNLOCK_SAFE, szMenuText, sizeof(szMenuText));
		else
			LoadString(g_hInst, IDS_LOCK_SAFE, szMenuText, sizeof(szMenuText));

		InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);
		InsertMenu(hMenu, indexMenu++, MF_STRING|MF_BYPOSITION, idCmd++, szMenuText);
		InsertMenu(hMenu, indexMenu++, MF_SEPARATOR|MF_BYPOSITION, 0, NULL);

		return ResultFromScode(MAKE_SCODE(SEVERITY_SUCCESS, 0, (USHORT)(idCmd-idCmdFirst))); 
	}

	return NOERROR;
}



STDMETHODIMP CShellFolder::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
	HRESULT		hr = E_FAIL;
	FORMATETC   fmtetc;
	STGMEDIUM   StgMedium;

    UINT idCmd = LOWORD(lpcmi->lpVerb);

	// If HIWORD(lpcmi->lpVerb) then we have been called programmatically
    // and lpVerb is a command that should be invoked.  Otherwise, the shell
    // has called us, and LOWORD(lpcmi->lpVerb) is the menu ID the user has
    // selected.  Actually, it's (menu ID - idCmdFirst) from QueryContextMenu().
	if(!HIWORD(lpcmi->lpVerb))
	{
		// idCmd == 0 if the first command has been invoked. The
		// first command can be either Logoff/Logon if the Safe
		// has been clicked or it can also be Encrypt/Decrypt if a 
		// file has been clicked. Determine how we have been invoked

		fmtetc.cfFormat   = CF_HDROP;
		fmtetc.ptd        = NULL;
		fmtetc.dwAspect   = DVASPECT_CONTENT;
		fmtetc.lindex     = -1;
		fmtetc.tymed      = TYMED_HGLOBAL;

		hr = m_pDataObj->GetData(&fmtetc, &StgMedium);

		if(SUCCEEDED(hr))
		{
			if(g_bLockedOut)
				if(!LogIn(TRUE))
					return hr;
		
			TCHAR szDestFolder[MAX_PATH], szFileSelected[MAX_PATH], *pStr;
		
			DragQueryFile((HDROP)StgMedium.hGlobal, 0, szFileSelected, sizeof(szFileSelected));
			pStr = strrchr(szFileSelected, '.');
			if(pStr && !_strnicmp(pStr, ".enc", 4))
				DecryptFiles((HDROP)StgMedium.hGlobal);
			else
			{
				GetPath(NULL, szDestFolder, MAX_PATH);

				EncryptDroppedItems(GetFocus(), (HDROP)StgMedium.hGlobal, (const PTCHAR)szDestFolder);

				// Refresh all the views
				CShellView *pView;
				pView = g_pViewList->GetNextView(NULL);
				while(pView)
				{
					pView->Refresh();
					pView = g_pViewList->GetNextView(pView);
				}
			}

			// Release the STGMEDIUM
			ReleaseStgMedium(&StgMedium);
		}
		else
		{
			// Right click invoke from desktop icon or icon in the explorer
			// left pane
			if(g_bLockedOut)
			{
				if(g_pViewList->GetCount() > 0)
					LogIn(TRUE);
				else
				{
					LPSHELLFOLDER pShellFolder;
					LPENUMIDLIST pEnumIDList = NULL;
					LPITEMIDLIST pItem = NULL;
					STRRET sName;
					TCHAR szPath[MAX_PATH], szExtName[MAX_PATH];
					ULONG ulFetched = 0;

					LoadString(g_hInst, IDS_EXT_TITLE, szExtName, sizeof(szExtName));

					SHGetDesktopFolder(&pShellFolder);
					pShellFolder->EnumObjects(NULL, SHCONTF_FOLDERS, &pEnumIDList);
					while(pEnumIDList->Next(1, &pItem, &ulFetched) == NOERROR)
					{
						pShellFolder->GetDisplayNameOf(pItem, 0, &sName);
						GetTextFromSTRRET(m_pMalloc, &sName, pItem, szPath, MAX_PATH);
						if(!lstrcmpi(szPath, szExtName))
							break;

						m_pMalloc->Free(pItem);
						continue;
					}

					pEnumIDList->Release();
					pShellFolder->Release();

					SHELLEXECUTEINFO sh;
					memset(&sh, 0, sizeof(SHELLEXECUTEINFO));
					sh.cbSize = sizeof(SHELLEXECUTEINFO);
					sh.nShow = SW_SHOW;
					sh.fMask = SEE_MASK_INVOKEIDLIST;
					sh.hwnd	= GetFocus();
					sh.lpVerb = __TEXT("open");
					sh.lpIDList = pItem;

					ShellExecuteEx(&sh);

					m_pMalloc->Free(pItem);
				
				}
			}
			else
				LogOut();
		}
	}

	return NOERROR;
}


STDMETHODIMP CShellFolder::GetCommandString(UINT idCmd, UINT uFlags, 
											UINT FAR *reserved, LPSTR pszName, 
											UINT cchMax)
{
	if(m_bSafeClicked)
		return NOERROR;

	BOOL bEncrypt = TRUE;
	HRESULT hr;
	FORMATETC fmtetc;
	STGMEDIUM StgMedium;

	fmtetc.cfFormat = CF_HDROP;
	fmtetc.ptd      = NULL;
	fmtetc.dwAspect = DVASPECT_CONTENT;
	fmtetc.lindex   = -1;
	fmtetc.tymed    = TYMED_HGLOBAL;
	
	hr = m_pDataObj->GetData(&fmtetc, &StgMedium);
	if(SUCCEEDED(hr))
	{
		TCHAR szFileSelected[MAX_PATH], *pStr;
		DragQueryFile((HDROP)StgMedium.hGlobal, 0, szFileSelected, sizeof(szFileSelected));
		pStr = strrchr(szFileSelected, '.');
		if(pStr && !_strnicmp(pStr, ".enc", 4))
			bEncrypt = FALSE;

		ReleaseStgMedium(&StgMedium);
	}
	else
		return NOERROR;

	TCHAR szStatusText[MAX_PATH];
	switch(uFlags)
	{
		case GCS_HELPTEXTA:
		case GCS_HELPTEXTW:
		{
			if(bEncrypt)
			{
				if(g_LocalPolicy.EncryptMethod == INPLACE)
					LoadString(g_hInst, IDS_ENCRYPT_INPLACE_ITEM, szStatusText, MAX_PATH);
				else
					LoadString(g_hInst, IDS_ENCRYPT_ITEM, szStatusText, MAX_PATH);
			}
			else
				LoadString(g_hInst, IDS_DECRYPT_ITEM, szStatusText, MAX_PATH);

			if(uFlags == GCS_HELPTEXTW)
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, (WCHAR*)pszName, cchMax);
			else
				lstrcpy(pszName, szStatusText);

			break;
		}
	}

	return NOERROR;
}



//IShellExtInit methods
STDMETHODIMP CShellFolder::Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hKeyID)
{
	// Check if the we are being called for right click on the Safe,
	// do this by querying the registry value
	DWORD dwType, dwDataSize = MAX_PATH;
	TCHAR szData[MAX_PATH];

	m_bSafeClicked = FALSE;
	g_bSafeClicked = FALSE;

	if(RegQueryValueEx(hKeyID, NULL, NULL, &dwType, (PBYTE)szData,
					&dwDataSize) == ERROR_SUCCESS)
	{
		TCHAR szText[MAX_PATH];
		LoadString(g_hInst, IDS_EXT_TITLE, szText, sizeof(szText));

		if(!_strnicmp(szText, szData, lstrlen(szText)))
		{
			m_bSafeClicked = TRUE;
			g_bSafeClicked = TRUE;
		}
	}

    if (m_pDataObj)
    	m_pDataObj->Release();

    // duplicate the object pointer and registry handle
    if (pDataObj)
    {
    	m_pDataObj = pDataObj;
    	pDataObj->AddRef();
    }

    return NOERROR;
}



STDMETHODIMP CShellFolder::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)
{
	HPROPSHEETPAGE hPage1, hPage2, hPage3, hPage4;

	if(!PasswordPrompt(SAFE_PROP))
		return E_INVALIDARG;

	PROPSHEETPAGE psp[4];    
	memset(&psp, 0, 4*sizeof(PROPSHEETPAGE));

    psp[0].dwSize = sizeof(PROPSHEETPAGE);    
	psp[0].dwFlags = PSP_USETITLE | PSP_HASHELP;
    psp[0].hInstance = g_hInst;
    psp[0].pszTemplate = MAKEINTRESOURCE(IDD_SAFE_PROP);    
	psp[0].pszIcon = NULL;
    psp[0].pfnDlgProc = (DLGPROC)SafeProperties;    
	psp[0].pszTitle = "General";
    psp[0].lParam = 0;    

	psp[1].dwSize = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags = PSP_USETITLE | PSP_HASHELP;
	psp[1].hInstance = g_hInst;
    psp[1].pszTemplate = MAKEINTRESOURCE(IDD_ADVANCED_OPTS);    
	psp[1].pszIcon = NULL;
    psp[1].pfnDlgProc = (DLGPROC)AdvancedOpts;
    psp[1].pszTitle = "Advanced";    
	psp[1].lParam = 0;    

	psp[2].dwSize = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags = PSP_USETITLE | PSP_HASHELP;    
	psp[2].hInstance = g_hInst;
    psp[2].pszTemplate = MAKEINTRESOURCE(IDD_FILTER);    
	psp[2].pszIcon = NULL;
    psp[2].pfnDlgProc = (DLGPROC)FilterProc;
    psp[2].pszTitle = "Filter";    
	psp[2].lParam = 0;    


	psp[3].dwSize = sizeof(PROPSHEETPAGE);
    psp[3].dwFlags = PSP_USETITLE | PSP_HASHELP;    
	psp[3].hInstance = g_hInst;
    psp[3].pszTemplate = MAKEINTRESOURCE(IDD_CERT_MGMT);    
	psp[3].pszIcon = NULL;
    psp[3].pfnDlgProc = (DLGPROC)CertMgmt;
    psp[3].pszTitle = "Digital ID";    
	psp[3].lParam = 0;    

	hPage1 = CreatePropertySheetPage(&psp[0]);
	hPage2 = CreatePropertySheetPage(&psp[1]);
	hPage3 = CreatePropertySheetPage(&psp[2]);
	hPage4 = CreatePropertySheetPage(&psp[3]);
	
	if(hPage1 != NULL && hPage2 != NULL && hPage3 != NULL && hPage4 != NULL)
	{
		if(!lpfnAddPage(hPage1, lParam) || !lpfnAddPage(hPage2, lParam) ||
		   !lpfnAddPage(hPage3, lParam) || !lpfnAddPage(hPage4, lParam))
		{
			DestroyPropertySheetPage(hPage1);
			DestroyPropertySheetPage(hPage2);
			DestroyPropertySheetPage(hPage3);
			DestroyPropertySheetPage(hPage4);
		}

		return NOERROR;
	}

	return E_INVALIDARG;
}
 

STDMETHODIMP CShellFolder::ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, 
									   LPARAM lParam)
{
	return E_FAIL;
}


// IExtractIcon methods
STDMETHODIMP CShellFolder::GetIconLocation(UINT uFlags, LPSTR szIconFile,
							  UINT cchMax, int *piIndex, UINT *pwFlags)
{
	HRESULT hr = S_FALSE;
	TCHAR szFile[MAX_PATH], szExt[32], *pStr = NULL;

	lstrcpy(szFile, m_szFile);
	pStr = strrchr(szFile, '.');
	if(pStr)
	{	
		*pStr = '\0';
		pStr = strrchr(szFile, '.');
		if(pStr)
		{
			lstrcpy(szExt, pStr);

			*pwFlags |= GIL_DONTCACHE | GIL_PERINSTANCE;

			HKEY hKey = NULL;
			if(RegOpenKeyEx(HKEY_CLASSES_ROOT, szExt, 0, KEY_QUERY_VALUE, 
							&hKey) == ERROR_SUCCESS)
			{
				TCHAR szValue[MAX_PATH];
				DWORD dwType, dwSize = MAX_PATH;
				if(RegQueryValueEx(hKey, NULL, NULL, &dwType, 
							(LPBYTE)szValue, &dwSize) == ERROR_SUCCESS)
				{
					HKEY hKeyIcon = NULL;
					lstrcat(szValue, "\\DefaultIcon");
					if(RegOpenKeyEx(HKEY_CLASSES_ROOT, szValue, 0, KEY_QUERY_VALUE, 
									&hKeyIcon) == ERROR_SUCCESS)
					{
						dwSize = MAX_PATH;
						if(RegQueryValueEx(hKeyIcon, NULL, NULL, &dwType, 
							(LPBYTE)szValue, &dwSize) == ERROR_SUCCESS)
						{
							pStr = strrchr(szValue, ',');
							if(pStr)
							{
								*pStr = '\0';
								lstrcpy(szIconFile, szValue);
								*piIndex = atoi(pStr + 1);

								if(!strnicmp(szIconFile, "%SystemRoot%", 12))
								{
									lstrcpy(szIconFile, g_szWinDir);
									pStr = strrchr(szValue, '%');
									lstrcat(szIconFile, pStr + 1);
								}

								hr = S_OK;
							}
						}

						RegCloseKey(hKeyIcon);
					}
				}

				RegCloseKey(hKey);
			}
		}
	}

	return hr;
}


STDMETHODIMP CShellFolder::Extract(LPCSTR lpszFile, UINT nIconIndex, 
				HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize)
{
	return S_FALSE;
}


// IPersistFile methods
STDMETHODIMP CShellFolder::GetClassID(LPCLSID lpClassID)
{
	return E_FAIL;
}


STDMETHODIMP CShellFolder::IsDirty()
{
	return S_FALSE;
}


STDMETHODIMP CShellFolder::Load(LPCOLESTR lpszFileName, DWORD grfMode)
{
	WideCharToMultiByte(CP_ACP, 0, lpszFileName, -1, m_szFile, 
						sizeof(m_szFile), NULL, NULL);
	return NOERROR;
}


STDMETHODIMP CShellFolder::Save(LPCOLESTR lpszFileName, BOOL fRemember)
{
    return E_FAIL;
}


STDMETHODIMP CShellFolder::SaveCompleted(LPCOLESTR lpszFileName)
{
	return E_FAIL;
}


STDMETHODIMP CShellFolder::GetCurFile(LPOLESTR FAR* lplpszFileName)
{
	return E_FAIL;
}

