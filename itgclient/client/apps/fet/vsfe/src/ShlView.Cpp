// Implements IShellView.

#include "stdafx.h"

#include <shlobj.h>
#include <windowsx.h>

#include "commands.h"
#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"
#include "PidlMgr.h"
#include "ShlView.h"
#include "Guid.h"
#include "Tools.h"
#include "ViewList.h"
#include "DropSrc.h"
#include "extricon.h"
#include "ShlFldr.h"
#include "ContMenu.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "encdeclist.h"
#include "droptgt.h"
#include "enumidl.h"

extern BOOL g_bSafeClicked;

MYTOOLINFO g_Tools[] = 
{
	IDB_STD_SMALL_COLOR, IDM_PROPERTIES, STD_PROPERTIES, IDS_PROPERTIES, TBSTATE_ENABLED, TBSTYLE_BUTTON,
	0, IDM_SEPARATOR, 0, 0, 0, TBSTYLE_SEP,
	IDB_VIEW_SMALL_COLOR, IDM_VIEW_LARGE, VIEW_LARGEICONS, IDS_VIEW_LARGE, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,
	IDB_VIEW_SMALL_COLOR, IDM_VIEW_SMALL, VIEW_SMALLICONS, IDS_VIEW_SMALL, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,
	IDB_VIEW_SMALL_COLOR, IDM_VIEW_LIST, VIEW_LIST, IDS_VIEW_LIST, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,
	IDB_VIEW_SMALL_COLOR, IDM_VIEW_DETAILS, VIEW_DETAILS, IDS_VIEW_DETAILS, TBSTATE_ENABLED, TBSTYLE_CHECKGROUP,
	0, IDM_SEPARATOR, 0, 0, 0, TBSTYLE_SEP,
	IDB_LOG_OUT, IDM_LOG_OUT, 0, IDS_LOCK_SAFE, TBSTATE_ENABLED, TBSTYLE_BUTTON,
	0, -1, 0, 0, 0, 0,
};


extern CViewList  *g_pViewList;
extern BOOL g_bLockedOut;
extern SafeSettings g_SafeProp;
extern PolicyVars g_LocalPolicy;
extern UINT g_nTimerId;
extern CEncDecList *g_EncrAtLogoffList, *g_DecrAtLogonList;
extern BOOL g_bPasswdFail;

extern BOOL EncryptAtLogoff(VOID);
extern BOOL DecryptAtLogon();

CShellView::CShellView(CShellFolder *pFolder, LPCITEMIDLIST pidl)
{
	g_DllRefCount++;

#ifdef INITCOMMONCONTROLSEX

	INITCOMMONCONTROLSEX iccex;
	iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccex.dwICC = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&iccex);
#else
	InitCommonControls();
#endif   //INITCOMMONCONTROLSEX

	m_hMenu	= NULL;
	m_fInEdit = FALSE;
	m_hAccels = NULL;
	m_hAccels = LoadAccelerators(g_hInst, MAKEINTRESOURCE(IDR_SAFEACCELS));

	m_pPidlMgr = new CPidlMgr();
	if(!m_pPidlMgr)
	{
		delete this;
		return;
	}

	m_psfParent = pFolder;
	if(m_psfParent)
		m_psfParent->AddRef();

	if(FAILED(SHGetMalloc(&m_pMalloc)))
	{
		delete this;
		return;
	}

	m_pidl = m_pPidlMgr->Copy(pidl);

	m_uState = SVUIA_DEACTIVATE;

	if(g_pViewList)
		g_pViewList->AddToList(this);

	m_ObjRefCount = 1;

	m_hBmpVSLogo = m_hBmpEncr = m_hBmpDecr = m_hBmpOpenSafe = m_hBmpSafe = NULL;	

	m_nBmpVSLogoHt = m_nBmpVSLogoWd = 0;

	m_nBmpEncrHt = m_nBmpDecrHt = 0;
	m_nBmpOpenSafeWd = m_nBmpOpenSafeHt = m_nBmpSafeHt = 0;
	
	m_nSplitPos = 0;
	m_hCurNS = NULL;
	m_hBmpEncr = NULL;

	m_bSortAscEncrName = TRUE;
	m_bSortAscEncrDate = TRUE;
	m_bSortAscEncrType = TRUE;
	m_bSortAscEncrSize = TRUE;
	m_bSortAscEncrLoc  = TRUE;

	m_bSortAscDecrName = TRUE;
	m_bSortAscDecrDate = TRUE;
	m_bSortAscDecrType = TRUE;
	m_bSortAscDecrSize = TRUE;
	m_bSortAscDecrLoc  = TRUE;
}


CShellView::~CShellView()
{
	if(g_pViewList)
		g_pViewList->RemoveFromList(this);

	if(m_pidl)
	{
		m_pPidlMgr->Delete(m_pidl);
		m_pidl = NULL;
	}

	if(m_psfParent)
		m_psfParent->Release();

	if(m_pMalloc)
		m_pMalloc->Release();
	
	if(m_pPidlMgr)
		delete m_pPidlMgr;

	g_DllRefCount--;
}


// IUnknown Implementation
STDMETHODIMP CShellView::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	// IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = this;
	
	// IOleWindow
	else if(IsEqualIID(riid, IID_IOleWindow))
		*ppReturn = (IOleWindow*)this;
	
	// IShellView
	else if(IsEqualIID(riid, IID_IShellView))
		*ppReturn = (IShellView*)this;
	
	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             


STDMETHODIMP_(DWORD) CShellView::AddRef()
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CShellView::Release()
{
	if(--m_ObjRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}


// IOleWindow Implementation
STDMETHODIMP CShellView::GetWindow(HWND *phWnd)
{
	*phWnd = m_hWnd;

	return S_OK;
}



STDMETHODIMP CShellView::ContextSensitiveHelp(BOOL fEnterMode)
{
	return E_NOTIMPL;
}



// IShellView Implementation
STDMETHODIMP CShellView::TranslateAccelerator(LPMSG pmsg)
{
	if(m_fInEdit)
	{
		if((pmsg->message >= WM_KEYFIRST) && (pmsg->message <= WM_KEYLAST))
		{
			TranslateMessage(pmsg);
			DispatchMessage(pmsg);
			return S_OK;
		}
	}
	else 
	{
		if(::TranslateAccelerator(m_hWnd, m_hAccels, pmsg))
			return S_OK;
	}

	return S_FALSE;
}



STDMETHODIMP CShellView::EnableModeless(BOOL fEnable)
{
	return E_NOTIMPL;
}



LRESULT CShellView::OnActivate(UINT uState)
{
	// First delete the menu which is there as the new menu is diff from
	// the current or we are abt to get deavtivated
	if(m_hMenu)
	{
		m_pShellBrowser->SetMenuSB(NULL, NULL, NULL);

		m_pShellBrowser->RemoveMenusSB(m_hMenu);

		DestroyMenu(m_hMenu);

		m_hMenu = NULL;
	}

	if(uState == SVUIA_ACTIVATE_FOCUS || uState == SVUIA_ACTIVATE_NOFOCUS)
	{
		m_hMenu = CreateMenu();

		if(m_hMenu)
		{
			OLEMENUGROUPWIDTHS omw = {0, 0, 0, 0, 0, 0};
			MENUITEMINFO       mii;

			m_pShellBrowser->InsertMenusSB(m_hMenu, &omw);

			// Get the file menu so we can merge with it
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_SUBMENU;

			// Merge our items into the File menu
			if(GetMenuItemInfo(m_hMenu, FCIDM_MENU_FILE, FALSE, &mii))
				MergeFileMenu(mii.hSubMenu, (BOOL)(SVUIA_ACTIVATE_FOCUS == uState));
	
			// Merge our items into the Edit menu
			if(!g_bLockedOut && GetMenuItemInfo(m_hMenu, FCIDM_MENU_EDIT, FALSE, &mii))
				MergeEditMenu(mii.hSubMenu, (BOOL)(SVUIA_ACTIVATE_FOCUS == uState));
		
			// Merge our items into the View menu
			if(!g_bLockedOut && GetMenuItemInfo(m_hMenu, FCIDM_MENU_VIEW, FALSE, &mii))
				MergeViewMenu(mii.hSubMenu);

			// Merge our items into the View menu
			if(GetMenuItemInfo(m_hMenu, FCIDM_MENU_HELP, FALSE, &mii))
				MergeHelpMenu(mii.hSubMenu);
			
			m_pShellBrowser->SetMenuSB(m_hMenu, NULL, m_hWnd);

			m_uState = uState;
	
			UpdateToolbar();
		}
	}

	return 0; 
}



// This function activates the view window. Note that activating it 
// will not change the focus, while setting the focus will activate it.
STDMETHODIMP CShellView::UIActivate(UINT uState)
{
	// OnActivate handles the menu merging and internal state
	OnActivate(uState);

	// Only do this if we are active
	if(uState != SVUIA_DEACTIVATE)
	{
		TCHAR szName[MAX_PATH] = TEXT("");
		LRESULT  lResult;
		int      nPartArray[1] = {-1};

		// Update the status bar, set the number of parts
		m_pShellBrowser->SendControlMsg(FCW_STATUS, SB_SETPARTS, 1, (LPARAM)nPartArray, &lResult);

		// Set the text for the parts
		m_pShellBrowser->SendControlMsg(FCW_STATUS, SB_SETTEXT, 0, (LPARAM)g_szExtTitle, &lResult);
	}

	return S_OK;
}



VOID CShellView::MergeFileMenu(HMENU hMenu, BOOL fFocus)
{
	TCHAR			szText[MAX_PATH];
	MENUITEMINFO	mii;
	UINT			uPos = 0, uSelected = 0;

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	if(g_bLockedOut)
	{
		// Add the "Unlock Safe" menu item
		LoadString(g_hInst, IDS_UNLOCK_SAFE, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_LOG_IN;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);

		if(g_bPasswdFail)
		{
			// Add a seperator
			mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mii.fType = MFT_SEPARATOR;
			mii.wID = IDM_SEPARATOR;
			mii.fState = MFS_ENABLED;
			InsertMenuItem(hMenu, uPos++, TRUE, &mii);

			LoadString(g_hInst, IDS_RESTORE_PASSWORD, szText, sizeof(szText));
			mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mii.fType = MFT_STRING;
			mii.fState = MFS_ENABLED;
			mii.dwTypeData = szText;
			mii.wID = IDM_RESTORE_PASSWORD;
			InsertMenuItem(hMenu, uPos++, TRUE, &mii);
		}

	}
	else
	{
		// If any item on the right window pane has the focus
		if(fFocus)	// SVUIA_ACTIVATE_FOCUS  == TRUE
		{
			// Add the encrypt/decrypt menu item depending on which item is selected
			if(GetFocus() == m_hwndListDecr &&
			   ListView_GetSelectedCount(m_hwndListDecr) >= 1)
			{
				LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
				mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
				mii.fType = MFT_STRING;
				mii.fState = MFS_ENABLED | MFS_DEFAULT;
				mii.dwTypeData = szText;
				mii.wID = IDM_OPEN_DECRYPTED;
				InsertMenuItem(hMenu, uPos++, TRUE, &mii);

				LoadString(g_hInst, IDS_ENCRYPT, szText, sizeof(szText));
				mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
				mii.fType = MFT_STRING;
				mii.fState = MFS_ENABLED;
				mii.dwTypeData = szText;
				mii.wID = IDM_ENCRYPT;
				InsertMenuItem(hMenu, uPos++, TRUE, &mii);
			}
			else
			{
				if(GetFocus() == m_hwndListEncr &&
				   (uSelected = ListView_GetSelectedCount(m_hwndListEncr)) >= 1)
				{
					LPITEMIDLIST	*aSelectedItems = NULL;
					aSelectedItems = (LPITEMIDLIST*)m_pMalloc->Alloc((uSelected + 1) * sizeof(LPITEMIDLIST));

					if(aSelectedItems)
					{
						UINT     i;
						LVITEM   lvItem;
						TCHAR szText[MAX_PATH];

						ZeroMemory(&lvItem, sizeof(lvItem));
						lvItem.mask = LVIF_STATE | LVIF_PARAM;
						lvItem.stateMask = LVIS_SELECTED;
						lvItem.iItem = 0;

						i = 0;

						// Construct a list of all selected items storing their PIDL's
						// 'lvItem.lParam' contains the PIDL
						while(ListView_GetItem(m_hwndListEncr, &lvItem) && (i < uSelected))
						{
							if(lvItem.state & LVIS_SELECTED)
							{
								aSelectedItems[i] = (LPITEMIDLIST)lvItem.lParam;
								i++;
							}

							lvItem.iItem++;
						}

						// See if we are in Explore or Open mode. If the browser's tree is present, 
						// then we are in Explore mode.
						BOOL  fExplore = FALSE;
						HWND  hwndTree = NULL;

						if(SUCCEEDED(m_pShellBrowser->GetControlWindow(FCW_TREE, &hwndTree)) && hwndTree)
							fExplore = TRUE;

						DWORD dwAttr = SFGAO_FOLDER;
						m_psfParent->GetAttributesOf(uSelected, 
													 (LPCITEMIDLIST*)aSelectedItems, 
													 &dwAttr);

						// The explore/open items for folders
						if(dwAttr & SFGAO_FOLDER)
						{
							if(fExplore)
							{
								LoadString(g_hInst, IDS_EXPLORE, szText, sizeof(szText));
								mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
								mii.wID = IDM_EXPLORE;
								mii.fType = MFT_STRING;
								mii.dwTypeData = szText;
								mii.fState = MFS_ENABLED | MFS_DEFAULT;
								InsertMenuItem(hMenu, uPos++, TRUE, &mii);

								LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
								mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
								mii.wID = IDM_OPEN;
								mii.fType = MFT_STRING;
								mii.dwTypeData = szText;
								mii.fState = MFS_ENABLED;
								InsertMenuItem(hMenu, uPos++, TRUE, &mii);
							}
							else
							{
								LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
								mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
								mii.wID = IDM_OPEN;
								mii.fType = MFT_STRING;
								mii.dwTypeData = szText;
								mii.fState = MFS_ENABLED | MFS_DEFAULT;
								InsertMenuItem(hMenu, uPos++, TRUE, &mii);

								LoadString(g_hInst, IDS_EXPLORE, szText, sizeof(szText));
								mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
								mii.wID = IDM_EXPLORE;
								mii.fType = MFT_STRING;
								mii.dwTypeData = szText;
								mii.fState = MFS_ENABLED;
								InsertMenuItem(hMenu, uPos++, TRUE, &mii);
							}
						} // if(dwAttr & SFGAO_FOLDER)
						else
						{
							LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
							mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
							mii.fType = MFT_STRING;
							mii.fState = MFS_ENABLED | MFS_DEFAULT;
							mii.dwTypeData = szText;
							mii.wID = IDM_OPEN;
							InsertMenuItem(hMenu, uPos++, TRUE, &mii);
						}

						// Add a seperator
						mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
						mii.fType = MFT_SEPARATOR;
						mii.wID = IDM_SEPARATOR;
						mii.fState = MFS_ENABLED;
						InsertMenuItem(hMenu, uPos++, TRUE, &mii);

						// Decrypt
						LoadString(g_hInst, IDS_DECRYPT, szText, sizeof(szText));
						mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
						mii.wID = IDM_DECRYPT;
						mii.fType = MFT_STRING;
						mii.dwTypeData = szText;
						mii.fState = MFS_ENABLED;
						InsertMenuItem(hMenu, uPos++, TRUE, &mii);

						// DecryptVerify option if folder or signed file
						for(i = 0; i < uSelected; i++)
						{
							m_psfParent->GetPath(aSelectedItems[i], szText, MAX_PATH);

							//  For a folder add decrypt_verify option
							if(m_pPidlMgr->IsFolder(aSelectedItems[i]) || IsSigned(szText))
							{
								LoadString(g_hInst, IDS_DECRYPT_VERIFY, szText, sizeof(szText));
								mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
								mii.wID = IDM_DECRYPT_VERIFY;
								mii.fType = MFT_STRING;
								mii.dwTypeData = szText;
								mii.fState = MFS_ENABLED;
								InsertMenuItem(hMenu, uPos++, TRUE, &mii);

								break;
							}
						}

						// Add the "Properties" menu item if all files selected
						BOOL bAllFolders = TRUE;
						for(i = 0; i < uSelected; i++)
						{
							m_psfParent->GetPath(aSelectedItems[i], szText, MAX_PATH);

							if(!m_pPidlMgr->IsFolder(aSelectedItems[i]))
							{
								bAllFolders = FALSE;
								break;
							}
						}

						if(!bAllFolders)
						{
							// Add a seperator
							mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
							mii.fType = MFT_SEPARATOR;
							mii.wID = IDM_SEPARATOR;
							mii.fState = MFS_ENABLED;
							InsertMenuItem(hMenu, uPos++, TRUE, &mii);

							LoadString(g_hInst, IDS_PROPERTIES, szText, sizeof(szText));
							mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
							mii.fType = MFT_STRING;
							mii.fState = MFS_ENABLED;
							mii.dwTypeData = szText;
							mii.wID = IDM_FILE_PROPERTIES;
							InsertMenuItem(hMenu, uPos++, TRUE, &mii);
						}

						m_pMalloc->Free(aSelectedItems);
					} // if(aSelectedItems)
				}	// GetFocus() == m_hwndListEncr
				else
				{
					// the Encrypted/Decrypted View do not have the focus or no items 
					// are selected 
			
					// Add the "Encrypt File..." menu item only if no item on the Encrypt
					// or Decrypt view is selected
					LoadString(g_hInst, IDS_ENCRYPT_FILE, szText, sizeof(szText));
					mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
					mii.fType = MFT_STRING;
					mii.fState = MFS_ENABLED;
					mii.dwTypeData = szText;
					mii.wID = IDM_ENCRYPT_FILE;

					InsertMenuItem(hMenu, uPos++, TRUE, &mii);

					// Add a seperator
					mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
					mii.fType = MFT_SEPARATOR;
					mii.wID = IDM_SEPARATOR;
					mii.fState = MFS_ENABLED;

					InsertMenuItem(hMenu, uPos++, TRUE, &mii);

					// Add the "Properties" menu item
					LoadString(g_hInst, IDS_PROPERTIES, szText, sizeof(szText));
					mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
					mii.fType = MFT_STRING;
					mii.fState = MFS_ENABLED;
					mii.dwTypeData = szText;
					mii.wID = IDM_PROPERTIES;

					InsertMenuItem(hMenu, uPos++, TRUE, &mii);
			
				}
			}
		} // if(fFocus)
		else
		{
			// Add the "Encrypt File..." menu item only if no item on the Encrypt
			// or Decrypt view is selected
			LoadString(g_hInst, IDS_ENCRYPT_FILE, szText, sizeof(szText));
			mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mii.fType = MFT_STRING;
			mii.fState = MFS_ENABLED;
			mii.dwTypeData = szText;
			mii.wID = IDM_ENCRYPT_FILE;

			InsertMenuItem(hMenu, uPos++, TRUE, &mii);

			// Add a seperator
			mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mii.fType = MFT_SEPARATOR;
			mii.wID = IDM_SEPARATOR;
			mii.fState = MFS_ENABLED;

			InsertMenuItem(hMenu, uPos++, TRUE, &mii);

			// Add the "Properties" menu item
			LoadString(g_hInst, IDS_PROPERTIES, szText, sizeof(szText));
			mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
			mii.fType = MFT_STRING;
			mii.fState = MFS_ENABLED;
			mii.dwTypeData = szText;
			mii.wID = IDM_PROPERTIES;

			InsertMenuItem(hMenu, uPos++, TRUE, &mii);
		}

		// Add a seperator
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_SEPARATOR;
		mii.wID = IDM_SEPARATOR;
		mii.fState = MFS_ENABLED;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);

		// Add the "Lock Safe" menu item
		LoadString(g_hInst, IDS_LOCK_SAFE, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_LOG_OUT;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);
	}	// (!g_bLockedOut)

	// Add a seperator
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_SEPARATOR;
	mii.wID = IDM_SEPARATOR;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, uPos++, TRUE, &mii);

	// Add the "Close" menu item
	LoadString(g_hInst, IDS_CLOSE, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = IDM_CLOSE;
	InsertMenuItem(hMenu, uPos++, TRUE, &mii);

	// Remove the "Create Shortcut", "Delete", "Rename", "Properties", "Close" items
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	RemoveMenu(hMenu, uPos, MF_BYPOSITION);
}


VOID CShellView::MergeViewMenu(HMENU hMenu)
{
	MENUITEMINFO   mii;
	TCHAR          szText[MAX_PATH];

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	// Add the Decrypted option
	LoadString(g_hInst, IDS_DECRYPTED, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = IDM_DECRYPTED_VIEW;
	InsertMenuItem(hMenu, FCIDM_MENU_VIEW_SEP_OPTIONS, FALSE, &mii);

	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_SEPARATOR;
	mii.wID = IDM_SEPARATOR;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, FCIDM_MENU_VIEW_SEP_OPTIONS, FALSE, &mii);

	AddViewMenuItems(hMenu, 0, FCIDM_MENU_VIEW_SEP_OPTIONS, FALSE);
}



VOID CShellView::MergeEditMenu(HMENU hMenu, BOOL fFocus)
{
	UINT uPos = 0;

	if(hMenu)
	{
		MENUITEMINFO   mii;
		TCHAR          szText[MAX_PATH];

		ZeroMemory(&mii, sizeof(mii));
		mii.cbSize = sizeof(mii);

		// Add the select all menu item
		LoadString(g_hInst, IDS_SELECT_ALL, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_SELECT_ALL;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);
		
		// Add the invert selection menu item
		LoadString(g_hInst, IDS_INVERT_SELECTION, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_INVERT_SELECTION;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);

		RemoveMenu(hMenu, uPos, MF_BYPOSITION);
		RemoveMenu(hMenu, uPos, MF_BYPOSITION);
	}
}


VOID CShellView::MergeHelpMenu(HMENU hMenu)
{
	MENUITEMINFO mii;
	UINT		 uPos = 0;

	if(hMenu)
	{
		TCHAR szText[MAX_PATH];

		DeleteMenu(hMenu, 0, MF_BYPOSITION);

		ZeroMemory(&mii, sizeof(mii));
		mii.cbSize = sizeof(mii);

		// Add the 'help topics' menu item
		LoadString(g_hInst, IDS_HELP_TOPICS, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_HELP_TOPICS;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);
		
		// Add the 'about' menu item
		LoadString(g_hInst, IDS_ABOUT, szText, sizeof(szText));
		mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
		mii.fType = MFT_STRING;
		mii.fState = MFS_ENABLED;
		mii.dwTypeData = szText;
		mii.wID = IDM_ABOUT;
		InsertMenuItem(hMenu, uPos++, TRUE, &mii);
	}

}



VOID CShellView::MergeToolbar(VOID)
{
	int         i;
	TBADDBITMAP tbab;
	LRESULT     lStdOffset;
	LRESULT     lViewOffset;
	LRESULT     lCustomOffset;
	BOOL		bActiveDesktopPresent = FALSE;
	static int  iLogoutOffset = 0, iLoginOffset = 0;

	// If Active Desktop is installed then no merging of 
	// toolbars should be done. This is bcos it is not possible
	// to remove the custom buttons which are added by our view.
	// This was confirmed from MSFT support
	HKEY hKey;
	DWORD dwType, dwSize = MAX_PATH;
	TCHAR szActiveDesktop[MAX_PATH];
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, ACTIVE_DESKTOP_KEY,
				0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey, NULL, NULL, &dwType,
				(LPBYTE)szActiveDesktop, &dwSize) == ERROR_SUCCESS)
		{
			if(!lstrcmpi(szActiveDesktop, "shell32.dll"))
				bActiveDesktopPresent = TRUE;	// if active desktop is not present then
		}										// 'szActiveDesktop' will contain 'url.dll'
	}

	RegCloseKey(hKey);


	m_pShellBrowser->SetToolbarItems(NULL, 0, FCT_MERGE);

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = (int)IDB_STD_SMALL_COLOR;
	m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_ADDBITMAP, 0, (LPARAM)&tbab, &lStdOffset);

	tbab.hInst = HINST_COMMCTRL;
	tbab.nID = (int)IDB_VIEW_SMALL_COLOR;
	m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_ADDBITMAP, 0, (LPARAM)&tbab, &lViewOffset);

	if(!bActiveDesktopPresent)
	{
		tbab.hInst = g_hInst;

		if(g_bLockedOut)
			tbab.nID = (int)IDB_LOGOUT;
		else
			tbab.nID = (int)IDB_LOGIN;

		m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_ADDBITMAP, 0, (LPARAM)&tbab, &lCustomOffset);
	}

	// Get the number of items in tool array
	for(i = 0; g_Tools[i].idCommand != -1; i++);

	LPTBBUTTON  ptbb = (LPTBBUTTON)GlobalAlloc(GPTR, sizeof(TBBUTTON) * i);

	if(ptbb)
	{
		for(int j = 0, i = 0; g_Tools[i].idCommand != -1; i++)
		{
			(ptbb + j)->iBitmap = 0;

			switch(g_Tools[i].uImageSet)
			{
				case IDB_STD_SMALL_COLOR:
				{
					(ptbb + j)->iBitmap = lStdOffset + g_Tools[i].iImage;
					break;
				}

				case IDB_VIEW_SMALL_COLOR:
				{
					(ptbb + j)->iBitmap = lViewOffset + g_Tools[i].iImage;
					break;
				}

				case IDB_LOG_OUT:
				{
					if(g_bLockedOut)
					{
						g_Tools[i].idCommand = IDM_LOG_IN;
						g_Tools[i].idString = IDS_UNLOCK_SAFE;
						(ptbb + j)->iBitmap = lCustomOffset + iLoginOffset;//1;
						if(iLoginOffset == 0 && iLogoutOffset == 0)
							iLogoutOffset = 1;
					}
					else
					{
						g_Tools[i].idCommand = IDM_LOG_OUT;
						g_Tools[i].idString = IDS_LOCK_SAFE;
						(ptbb + j)->iBitmap = lCustomOffset + iLogoutOffset;//0;
						if(iLoginOffset == 0 && iLogoutOffset == 0)
							iLoginOffset = 1;
					}
				}
					break;
			}

			if(bActiveDesktopPresent && (g_Tools[i].idCommand == IDM_LOG_IN ||
			   g_Tools[i].idCommand == IDM_LOG_OUT))
				continue;

			if(g_bLockedOut && g_Tools[i].uImageSet != IDB_LOG_OUT)
				continue;

			(ptbb + j)->idCommand = g_Tools[i].idCommand;
			(ptbb + j)->fsState = g_Tools[i].bState;
			(ptbb + j)->fsStyle = g_Tools[i].bStyle;
			(ptbb + j)->dwData = 0;
			(ptbb + j)->iString = 0;
			j++;
		}

		m_pShellBrowser->SetToolbarItems(ptbb, j, FCT_MERGE);

		GlobalFree((HGLOBAL)ptbb);
	}

	UpdateToolbar();
}



STDMETHODIMP CShellView::Refresh(VOID)
{
	if(!g_bLockedOut)
	{
		// Empty the list
		ListView_DeleteAllItems(m_hwndListEncr);
		ListView_DeleteAllItems(m_hwndListDecr);

		// Refill the list
		FillList(TRUE);
	}

	return S_OK;
}


VOID CShellView::DeleteListViewItems(VOID)
{
	ListView_DeleteAllItems(m_hwndListEncr);
	ListView_DeleteAllItems(m_hwndListDecr);
}


STDMETHODIMP CShellView::CreateViewWindow(LPSHELLVIEW pPrevView, 
                                         LPCFOLDERSETTINGS lpfs, 
                                         LPSHELLBROWSER psb, LPRECT prcView, 
                                         HWND *phWnd)
{
	WNDCLASS wc;
	*phWnd = NULL;

	// If our window class has not been registered, then do so
	if(!GetClassInfo(g_hInst, NS_CLASS_NAME, &wc))
	{
		ZeroMemory(&wc, sizeof(wc));

		// For WINNT the CS_HREDRAW | CS_VREDRAW style is causing a flicker of
		// list view. For WIN95 not providing these styles does not cause a proper
		// painting of the background

		if(g_dwPlatform == VER_PLATFORM_WIN32_NT)
			wc.style = 0; 
		else
			wc.style = CS_HREDRAW | CS_VREDRAW;

		wc.lpfnWndProc    = (WNDPROC)WndProc;
		wc.cbClsExtra     = 0;
		wc.cbWndExtra     = 0;
		wc.hInstance      = g_hInst;
		wc.hIcon          = NULL;
		wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
		wc.lpszMenuName   = NULL;
		wc.lpszClassName  = NS_CLASS_NAME;

		if(!RegisterClass(&wc))
			return E_FAIL;
	}

	// Set up the member variables
	m_pShellBrowser = psb;
	m_FolderSettings = *lpfs;

	// Get our parent window
	m_pShellBrowser->GetWindow(&m_hwndParent);

	*phWnd = CreateWindowEx(0, NS_CLASS_NAME, NULL, WS_CHILD | WS_VISIBLE,
						    prcView->left, prcView->top, prcView->right - prcView->left,
						    (prcView->bottom - prcView->top), m_hwndParent, NULL,
						    g_hInst, (LPVOID)this);
	if(!*phWnd)
		return E_FAIL;

	MergeToolbar();

	m_pShellBrowser->AddRef();

	return S_OK;
}



STDMETHODIMP CShellView::DestroyViewWindow(VOID)
{
	// For Win95 getting error when calling SignInit() of the VSPref(goes in the 'catch' 
	// part of the fn) on dllunload() so update the Safe now if this is the last View window 
	// being destroyed
	/*if(g_pViewList->GetCount() == 1)
		UpdateSafe();*/

	// Make absolutely sure all our UI is cleaned up.
	UIActivate(SVUIA_DEACTIVATE);

	if(m_hMenu)
		DestroyMenu(m_hMenu);

	DestroyWindow(m_hWnd);

	// Release the shell browser object
	m_pShellBrowser->Release();

	return S_OK;
}



STDMETHODIMP CShellView::GetCurrentInfo(LPFOLDERSETTINGS lpfs)
{
	*lpfs = m_FolderSettings;

	return S_OK;
}



STDMETHODIMP CShellView::AddPropertySheetPages( DWORD dwReserved, 
                                                LPFNADDPROPSHEETPAGE lpfn, 
                                                LPARAM lParam)
{
	return E_NOTIMPL;
}



STDMETHODIMP CShellView::SaveViewState(VOID)
{
	return S_OK;
}



STDMETHODIMP CShellView::SelectItem(LPCITEMIDLIST pidlItem, UINT uFlags)
{
	return E_NOTIMPL;
}



STDMETHODIMP CShellView::GetItemObject(UINT uItem, REFIID riid, LPVOID *ppvOut)
{
	*ppvOut = NULL;
	return E_NOTIMPL;
}




LRESULT CALLBACK CShellView::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, 
									 LPARAM lParam)
{
	CShellView  *pThis = (CShellView*)GetWindowLong(hWnd, VIEW_POINTER_OFFSET);
	UINT yPos = 0;
	static HCURSOR hOldCursor = NULL;
	
	switch (uMessage)
	{
		case WM_NCCREATE:
			{
				LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
				pThis = (CShellView*)(lpcs->lpCreateParams);
				SetWindowLong(hWnd, VIEW_POINTER_OFFSET, (LONG)pThis);

				pThis->m_hWnd = hWnd;
			}
			break;

		case WM_MENUSELECT:
			return pThis->OnMenuSelect(wParam);
			
		case WM_SIZE:
			pThis->OnSize(LOWORD(lParam), HIWORD(lParam));
			break;

		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
			return pThis->OnPaint();
		
		case WM_MOUSEMOVE:

			yPos = HIWORD(lParam);					

			// If mouse cursor is at the position of the split bar show the NS cursor
			if(yPos == pThis->m_nSplitPos)
			{
				hOldCursor = SetCursor(pThis->m_hCurNS);
				return 0;
			}

			if(hOldCursor)
			{
				SetCursor(hOldCursor);
				hOldCursor = NULL;
			}

			break;


		case WM_LBUTTONDOWN:

			yPos = HIWORD(lParam);					

			// If on the Split bar
			if(yPos == pThis->m_nSplitPos)
			{
				RECT rect;
				BOOL bFirstTime = TRUE;

	            GetWindowRect(pThis->m_hWnd, &rect);
		        ClipCursor(&rect);

				SetCapture(pThis->m_hWnd);
				hOldCursor = SetCursor(pThis->m_hCurNS);
				GetClientRect(pThis->m_hWnd, &rect);

				HDC hDC = GetDC(pThis->m_hWnd);

				HBRUSH hOldbr = (HBRUSH)SelectObject(hDC, GetStockObject(GRAY_BRUSH));

				BOOL bTracking = TRUE;
				MSG msgModal;

				while(bTracking)
				{
					GetMessage(&msgModal, NULL, WM_MOUSEFIRST, WM_MOUSELAST);
					switch (msgModal.message)
					{
						case WM_MOUSEMOVE:
						{
							yPos = HIWORD(msgModal.lParam);

							// Only redraw if different position than last time and
							// if the Split bar is within the upper and lower limits.
							// The limit is not overwritting the top bitmap and diplaying
							// contents of both the windows to some extent
							if(yPos != pThis->m_nSplitPos && 
							   yPos > 2*pThis->m_nBmpVSLogoHt  &&
							   yPos < rect.bottom - 2*pThis->m_nBmpVSLogoHt)
							{
								if(!bFirstTime)
								{
									// Erase previous split-bar
									PatBlt(hDC, 0, pThis->m_nSplitPos, rect.right, 
										   2, PATINVERT);
								}
								else
									bFirstTime = FALSE;

								pThis->m_nSplitPos = yPos;

								// Draw new split-bar
								PatBlt(hDC, 0, yPos, rect.right, 2, PATINVERT);
							}

							break;
						}

						// End of split-bar drag          
						case WM_LBUTTONUP:     
						case WM_LBUTTONDOWN:
						case WM_LBUTTONDBLCLK:
						case WM_RBUTTONUP:
						case WM_RBUTTONDOWN:
						case WM_RBUTTONDBLCLK:
						{
							yPos = HIWORD(msgModal.lParam);

							// Erase the last split-bar 
							PatBlt(hDC, 0, yPos, 2, 0, PATINVERT);

							if(yPos < 2*pThis->m_nBmpVSLogoHt)
								yPos = 2*pThis->m_nBmpVSLogoHt;
							else
								if(yPos > (rect.bottom - 2*pThis->m_nBmpVSLogoHt))
									yPos = rect.bottom - 2*pThis->m_nBmpVSLogoHt;
						
							pThis->m_nSplitPos = yPos;

							InvalidateRect(pThis->m_hWnd, NULL, TRUE);
							bTracking = FALSE;  // Break out of tracking loop

							PostMessage(pThis->m_hWnd, WM_SIZE, 0, MAKELONG(rect.right, rect.bottom));

							break;
						}

					}
				} // end while

				SelectObject(hDC, hOldbr);
				ReleaseDC(pThis->m_hWnd, hDC);
				SetCursor(hOldCursor);
				ReleaseCapture();
				ClipCursor(NULL);

				return 0;
			}
				
			break;

		case WM_CREATE:
				// Did this as the COM library was not initialised when this extension is 
				// invoked by dbl clicking the desktop icon(basically when the explorer
				// tree is not present)
				CoInitialize(NULL);

				pThis->OnCreate();
	
				return 0;

		case WM_DESTROY:
				pThis->OnDestroy();
				CoUninitialize();
				return 0;


		case WM_COMMAND:
				return pThis->OnCommand(GET_WM_COMMAND_ID(wParam, lParam), 
										GET_WM_COMMAND_CMD(wParam, lParam), 
										GET_WM_COMMAND_HWND(wParam, lParam));

		case WM_INITMENUPOPUP:
				return pThis->UpdateMenu((HMENU)wParam);

		case WM_NOTIFY:
				return pThis->OnNotify((UINT)wParam, (LPNMHDR)lParam);
				
		case WM_SETTINGCHANGE:
				return pThis->OnSettingChange((LPCTSTR)lParam);

		case WM_CONTEXTMENU:
			{
				TCHAR szAppTitle[MAX_PATH];
				WCHAR wcAppTitle[MAX_PATH];

				pThis->DoContextMenu(LOWORD(lParam), HIWORD(lParam), FALSE, (UINT)-1);
				
				LoadString(g_hInst, IDS_EXT_TITLE, szAppTitle, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szAppTitle, -1, wcAppTitle, MAX_PATH);
				pThis->m_pShellBrowser->SetStatusTextSB(wcAppTitle);
				
				return 0;
			}
	}

	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}


BOOL CShellView::OnMenuSelect(DWORD wParam)
{
	TCHAR szStatusText[MAX_PATH];
	WCHAR wcStatusText[MAX_PATH];

	if(g_bSafeClicked)
		return FALSE;

	if(HIWORD(wParam) & MF_POPUP)
	{
		switch(LOWORD(wParam))
		{
			case 0:
				LoadString(g_hInst, IDS_VIEW_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case 2:
				LoadString(g_hInst, IDS_ARRANGE_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;
		}
	}
	else
	{
		switch(LOWORD(wParam))
		{
			case IDM_ENCRYPT_FILE:
				LoadString(g_hInst, IDS_SEL_FILES, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_PROPERTIES:
				LoadString(g_hInst, IDS_SAFE_PROP, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_FILE_PROPERTIES:
				LoadString(g_hInst, IDS_ITEM_PROP, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_LOG_OUT:
				LoadString(g_hInst, IDS_LOCK_THE_SAFE, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_LOG_IN:
				LoadString(g_hInst, IDS_UNLOCK_THE_SAFE, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_CLOSE:
				LoadString(g_hInst, IDS_CLOSE_WINDOW, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_RESTORE_PASSWORD:
				LoadString(g_hInst, IDS_RECOVER_PASSWORD, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_SELECT_ALL:
				LoadString(g_hInst, IDS_SELECT_ALL_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_INVERT_SELECTION:
				LoadString(g_hInst, IDS_INVERT_SELECT_ALL_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_DECRYPTED_VIEW:
				LoadString(g_hInst, IDS_RECENTLY_DECRYPTED, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_VIEW_LARGE:
				LoadString(g_hInst, IDS_VIEW_LARGE_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_VIEW_SMALL:
				LoadString(g_hInst, IDS_VIEW_SMALL_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_VIEW_LIST:
				LoadString(g_hInst, IDS_VIEW_LIST_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_VIEW_DETAILS:
				LoadString(g_hInst, IDS_VIEW_DETAIL_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_HELP_TOPICS:
				LoadString(g_hInst, IDS_HELP, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_ABOUT:
				LoadString(g_hInst, IDS_HELP_ABOUT, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_OPEN:
			{
				// Determine if file or folder or both are selected
				// No status string if both files folders selected
				UINT uSelected = 0, i = 0;
				LVITEM lvItem;
				BOOL bFileSel = FALSE, bFolderSel = FALSE;

				ZeroMemory(&lvItem, sizeof(lvItem));
				lvItem.mask = LVIF_STATE | LVIF_PARAM;
				lvItem.stateMask = LVIS_SELECTED;
				lvItem.iItem = 0;

				uSelected = ListView_GetSelectedCount(m_hwndListEncr);

				// Construct a list of all selected items storing their PIDL's
				// 'lvItem.lParam' contains the PIDL
				while(ListView_GetItem(m_hwndListEncr, &lvItem) && (i < uSelected))
				{
					if(lvItem.state & LVIS_SELECTED)
					{
						if(m_pPidlMgr->IsFolder((LPITEMIDLIST)lvItem.lParam))
							bFolderSel = TRUE;
						else
							bFileSel = TRUE;

						i++;
					}

					if(bFolderSel && bFileSel)
						break;

					lvItem.iItem++;
				}

				if(bFolderSel && bFileSel)
					m_pShellBrowser->SetStatusTextSB(L"");
				else
				{
					if(bFolderSel)
					{
						LoadString(g_hInst, IDS_OPEN_ITEM, szStatusText, MAX_PATH);
						MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
						m_pShellBrowser->SetStatusTextSB(wcStatusText);
					}
					else
						if(bFileSel)
						{
							LoadString(g_hInst, IDS_DECRYPTOPEN_ITEMS, szStatusText, MAX_PATH);
							MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
							m_pShellBrowser->SetStatusTextSB(wcStatusText);
						}
				}
				
				break;
			}

			case IDM_OPEN_DECRYPTED:
				LoadString(g_hInst, IDS_OPEN_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_DECRYPT:
				LoadString(g_hInst, IDS_DECRYPT_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_ENCRYPT:
				LoadString(g_hInst, IDS_ENCRYPT_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_DECRYPT_VERIFY:
				LoadString(g_hInst, IDS_DECRYPTVERIFY_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_EXPLORE:
				LoadString(g_hInst, IDS_EXPLORE_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_DELETE:
				LoadString(g_hInst, IDS_DELETE_ITEMS, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_BY_NAME:
				LoadString(g_hInst, IDS_BY_NAME_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_BY_TYPE:
				LoadString(g_hInst, IDS_BY_TYPE_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_BY_DATE_ENCRYPT:
				LoadString(g_hInst, IDS_BY_DATE_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_BY_SIZE:
				LoadString(g_hInst, IDS_BY_SIZE_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_BY_ORIGIN:
				LoadString(g_hInst, IDS_BY_ORIGIN_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_CLEAR:
				LoadString(g_hInst, IDS_CLEAR_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;

			case IDM_HIDE:
				LoadString(g_hInst, IDS_HIDE_ITEM, szStatusText, MAX_PATH);
				MultiByteToWideChar(CP_ACP, 0, szStatusText, -1, wcStatusText, MAX_PATH);
				m_pShellBrowser->SetStatusTextSB(wcStatusText);
				break;
		}
	}

	return 0;
}



//	Tell the browser one of our windows has received the focus. This should always 
//	be done before merging menus (OnActivate merges the menus) if one of our 
//	windows has the focus.
LRESULT CShellView::OnSetFocus(UINT uState)
{
	m_pShellBrowser->OnViewWindowActive(this);
	return 0;
}



LRESULT CShellView::OnKillFocus(VOID)
{
	OnActivate(SVUIA_ACTIVATE_NOFOCUS);
	return 0;
}



LRESULT CShellView::OnCommand(DWORD dwCmdID, DWORD dwCmd, HWND hwndCmd)
{
	// Ignore command messages while in edit mode
	if(m_fInEdit)
		return 0;

	DoContextMenu(0, 0, FALSE, dwCmdID);

	return 0;
}



LRESULT CShellView::UpdateMenu(HMENU hMenu)
{
	UINT  uCommand;

	// Enable/Disable your menu items here
	switch(m_FolderSettings.ViewMode)
	{
		case FVM_ICON:
			uCommand = IDM_VIEW_LARGE;
			break;

		case FVM_SMALLICON:
			uCommand = IDM_VIEW_SMALL;
			break;

		case FVM_LIST:
			uCommand = IDM_VIEW_LIST;
			break;

		case FVM_DETAILS:
		default:
			uCommand = IDM_VIEW_DETAILS;
			break;
	}

	CheckMenuRadioItem(hMenu, IDM_VIEW_LARGE, IDM_VIEW_DETAILS, uCommand, MF_BYCOMMAND);

	if(g_SafeProp.bDecryptPane)
		CheckMenuItem(hMenu, IDM_DECRYPTED_VIEW, MF_BYCOMMAND | MF_CHECKED);
	else
		CheckMenuItem(hMenu, IDM_DECRYPTED_VIEW, MF_BYCOMMAND | MF_UNCHECKED);

	return 0;
}



LRESULT CShellView::UpdateToolbar(VOID)
{
	LRESULT  lResult;
	UINT     uCommand;

	// Enable/disable/check the toolbar items here
	switch(m_FolderSettings.ViewMode)
	{
		case FVM_ICON:
			uCommand = IDM_VIEW_LARGE;
			break;

		case FVM_SMALLICON:
			uCommand = IDM_VIEW_SMALL;
			break;

		case FVM_LIST:
			uCommand = IDM_VIEW_LIST;
			break;

		case FVM_DETAILS:
		default:
			uCommand = IDM_VIEW_DETAILS;
			break;
	}

	m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_CHECKBUTTON, uCommand, MAKELPARAM(TRUE, 0), &lResult);

	return 0;
}



#define MENU_MAX     100


LRESULT CShellView::OnNotify(UINT CtlID, LPNMHDR lpnmh)
{
	if(CtlID == ID_LISTVIEW_ENCR)
		return OnNotifyEncr(lpnmh);
	else
		if(CtlID == ID_LISTVIEW_DECR)
			return OnNotifyDecr(lpnmh);
		else
		{
			// Display the tooltip string on the toolbar
			switch(lpnmh->code)
			{
				// The original shell on NT will always send TTN_NEEDTEXTW, so handle the 
				// cases separately.
				case TTN_NEEDTEXTA:
				{
					LPNMTTDISPINFOA pttt = (LPNMTTDISPINFOA)lpnmh;
					int i;

					for(i = 0; g_Tools[i].idCommand != -1; i++)
						if(g_Tools[i].idCommand == pttt->hdr.idFrom)
						{
							LoadStringA(g_hInst, g_Tools[i].idString, pttt->szText, sizeof(pttt->szText));
							return TRUE;
						}
				}
					break;

				case TTN_NEEDTEXTW:
				{
					LPNMTTDISPINFOW pttt = (LPNMTTDISPINFOW)lpnmh;
					int i;

					for(i = 0; g_Tools[i].idCommand != -1; i++)
						if(g_Tools[i].idCommand == pttt->hdr.idFrom)
						{
							LoadStringW(g_hInst, g_Tools[i].idString, pttt->szText, sizeof(pttt->szText));
							return TRUE;
						}
				}
					break;


				case HDN_ENDTRACK:
				{
					g_SafeProp.lDisplaySizes[0] = ListView_GetColumnWidth(m_hwndListEncr, 0);
					g_SafeProp.lDisplaySizes[1] = ListView_GetColumnWidth(m_hwndListEncr, 1);
					g_SafeProp.lDisplaySizes[2] = ListView_GetColumnWidth(m_hwndListEncr, 2);
					g_SafeProp.lDisplaySizes[3] = ListView_GetColumnWidth(m_hwndListEncr, 3);
					g_SafeProp.lDisplaySizes[4] = ListView_GetColumnWidth(m_hwndListEncr, 4);

					if(g_SafeProp.bDecryptPane)
					{
						g_SafeProp.lDisplaySizes[5] = ListView_GetColumnWidth(m_hwndListDecr, 0);
						g_SafeProp.lDisplaySizes[6] = ListView_GetColumnWidth(m_hwndListDecr, 1);
						g_SafeProp.lDisplaySizes[7] = ListView_GetColumnWidth(m_hwndListDecr, 2);
						g_SafeProp.lDisplaySizes[8] = ListView_GetColumnWidth(m_hwndListDecr, 3);
						g_SafeProp.lDisplaySizes[9] = ListView_GetColumnWidth(m_hwndListDecr, 4);
					}

			}
					break;

			} // switch(lpnmh->code)
		}
		
	return 0;
}

UINT g_cnt = 0;

LRESULT CShellView::OnNotifyEncr(LPNMHDR lpnmh)
{
	switch(lpnmh->code)
	{
		case NM_SETFOCUS:
			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case NM_KILLFOCUS:
			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case NM_CLICK:
			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case LVN_COLUMNCLICK:
			OnArrangeIconEncr(((LPNMLISTVIEW)lpnmh)->iSubItem);
			break;

		case LVN_DELETEITEM:
		{
			NM_LISTVIEW *lpnmlv = (NM_LISTVIEW*)lpnmh;

			// Delete the pidl because we made a copy of it
			m_pPidlMgr->Delete((LPITEMIDLIST)lpnmlv->lParam);
		}
			break;

#ifdef LVN_ITEMACTIVATE

		case LVN_ITEMACTIVATE:

#else    //LVN_ITEMACTIVATE

		case NM_DBLCLK:
		case NM_RETURN:

#endif   //LVN_ITEMACTIVATE

			DoContextMenu(0, 0, TRUE, (DWORD)-1);
			return 0;

		case LVN_GETDISPINFO:
		{
			NMLVDISPINFO   *lpdi = (NMLVDISPINFO*)lpnmh;
			LPITEMIDLIST   pidl = (LPITEMIDLIST)lpdi->item.lParam;

			// Is the sub-item information being requested?
			switch(lpdi->item.iSubItem)
			{
				case 0:
				{
					// Is the text being requested?
					if(lpdi->item.mask & LVIF_TEXT)
					{
						STRRET   str;

						if(SUCCEEDED(m_psfParent->GetDisplayNameOf(pidl, SHGDN_NORMAL | SHGDN_INFOLDER, &str)))
							GetTextFromSTRRET(m_pMalloc, &str, pidl, lpdi->item.pszText, lpdi->item.cchTextMax);
			
					}

					// Is the image being requested?
					if(lpdi->item.mask & LVIF_IMAGE)
					{
						IExtractIcon   *pei;

						if(SUCCEEDED(m_psfParent->GetUIObjectOf(m_hWnd, 1, (LPCITEMIDLIST*)&pidl, IID_IExtractIcon, NULL, (LPVOID*)&pei)))
						{
							UINT uFlags;
							TCHAR szPath[MAX_PATH];
							SHFILEINFO sfi;

							// If the file is in the encrypted state 
							if(m_pPidlMgr->GetStatus(pidl) == ENCRYPTED)
							{
								// Replace the "lock/file" icon with the new file icon 
								m_psfParent->GetPath(pidl, szPath, MAX_PATH);
								SHGetFileInfo(szPath, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON);
								ImageList_ReplaceIcon(g_himlSmall, ICON_INDEX_LOCKFILE, sfi.hIcon);
								SHGetFileInfo(szPath, 0, &sfi, sizeof(sfi), SHGFI_ICON);
								ImageList_ReplaceIcon(g_himlLarge, ICON_INDEX_LOCKFILE, sfi.hIcon);

								// GetIconLocation will give us the index into our image list
								pei->GetIconLocation(GIL_FORSHELL, NULL, 0, &lpdi->item.iImage, &uFlags);
								pei->Release();
							}
						}
					}
				} // case 0
					break;

				case 1:
				{
					// Display the size. 
					TCHAR szPath[MAX_PATH];
					__int64 FileSize = 0;
					
					if(m_pPidlMgr->IsFolder(pidl))
						lpdi->item.pszText[0] = '\0';
					else
					{
						// Get the path
						if(m_pPidlMgr->GetStatus(pidl) == ENCRYPTED)
							m_psfParent->GetPath(pidl, szPath, MAX_PATH);

						BY_HANDLE_FILE_INFORMATION fad;
						HANDLE hFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ,
												  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE,
												  NULL);

						GetFileInformationByHandle(hFile, &fad);
						CloseHandle(hFile);

						FileSize = fad.nFileSizeHigh + fad.nFileSizeLow;
	
						GetDisplaySize(FileSize, lpdi->item.pszText, FALSE);
					}
				}
					break;

				case 2:
				{	
					// Display the file type
					TCHAR szPath[MAX_PATH];

					// Get the path
					if(m_pPidlMgr->GetStatus(pidl) == ENCRYPTED)
						m_psfParent->GetPath(pidl, szPath, MAX_PATH);

					SHFILEINFO sfi;
					SHGetFileInfo(szPath, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
					lstrcpy(lpdi->item.pszText, sfi.szTypeName);
				}
					break;


				case 3:
				{
					// Display the file encryption date.
					// If 'folder' display blank
					if(m_pPidlMgr->IsFolder(pidl))
						lpdi->item.pszText[0] = '\0';
					else
					{
						if(m_pPidlMgr->GetStatus(pidl) == ENCRYPTED)
						{
							TCHAR szPath[MAX_PATH];
							m_psfParent->GetPath(pidl, szPath, MAX_PATH);

							BY_HANDLE_FILE_INFORMATION fad;
							HANDLE hFile = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ,
													  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);

							GetFileInformationByHandle(hFile, &fad);
							CloseHandle(hFile);

							GetDisplayTime(&fad.ftCreationTime, lpdi->item.pszText, FALSE);
						}
					}
				
				} // case 3
					break;


				case 4:
				{ 
					// Display the original location of the file. 
					// For a file which is a "link" this column shld be blank
					if(m_pPidlMgr->IsFolder(pidl))
						lpdi->item.pszText[0] = '\0';
					else
						if(m_pPidlMgr->GetStatus(pidl) == ENCRYPTED)
							strcpy(lpdi->item.pszText, m_pPidlMgr->GetOriginalLocation(pidl));
				}

				default:
					break;

			} // switch(lpdi->item.iSubItem)
		}
			return 0;

		case LVN_BEGINDRAG:
		{
			HRESULT			hr;
			IDataObject		*pDataObject = NULL;
			UINT			uItemCount;
			LPITEMIDLIST	*aPidls;
			
			// Get the number of selected items
			uItemCount = ListView_GetSelectedCount(m_hwndListEncr);
			if(!uItemCount)
				return 0;

			aPidls = (LPITEMIDLIST*)m_pMalloc->Alloc(uItemCount * sizeof(LPITEMIDLIST));

			if(aPidls)
			{
				int   i;
				UINT  x;

				for(i = 0, x = 0; x < uItemCount && i < ListView_GetItemCount(m_hwndListEncr); i++)
				{
					if(ListView_GetItemState(m_hwndListEncr, i, LVIS_SELECTED))
					{
						LVITEM   lvItem;

						lvItem.mask = LVIF_PARAM;
						lvItem.iItem = i;

						ListView_GetItem(m_hwndListEncr, &lvItem);

						aPidls[x] = (LPITEMIDLIST)lvItem.lParam;
						x++;
					}
				}

				hr = m_psfParent->GetUIObjectOf(m_hWnd, x, 
								    (LPCITEMIDLIST*)aPidls, IID_IDataObject, 
								    NULL, (LPVOID*)&pDataObject);

				if(SUCCEEDED(hr) && pDataObject)
				{
					IDropSource *pDropSource = new CDropSource;

					DWORD dwEffect = DROPEFFECT_MOVE;
					DWORD dwAttributes = SFGAO_CANLINK;

					hr = m_psfParent->GetAttributesOf(uItemCount, 
										(LPCITEMIDLIST*)aPidls, &dwAttributes);

					DoDragDrop(pDataObject, pDropSource, dwEffect, &dwEffect);
					pDataObject->Release();
					pDropSource->Release();
				}

				m_pMalloc->Free(aPidls);
			}
		}
			break;

		case LVN_ITEMCHANGED:
			UpdateToolbar();
			break;

	}

	return 0;
}


LRESULT CShellView::OnNotifyDecr(LPNMHDR lpnmh)
{
	LRESULT lResult;

	switch(lpnmh->code)
	{
		case NM_SETFOCUS:
			
			m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_SETSTATE, IDM_PROPERTIES, MAKELPARAM(TBSTATE_INDETERMINATE, 0), &lResult);

			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case NM_KILLFOCUS:

			m_pShellBrowser->SendControlMsg(FCW_TOOLBAR, TB_SETSTATE, IDM_PROPERTIES, MAKELPARAM(TBSTATE_ENABLED, 0), &lResult);

			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case NM_CLICK:
			OnActivate(SVUIA_ACTIVATE_FOCUS);
			break;

		case LVN_COLUMNCLICK:
			OnArrangeIconDecr(((LPNMLISTVIEW)lpnmh)->iSubItem);
			break;

		case LVN_DELETEITEM:
		{
			NM_LISTVIEW *lpnmlv = (NM_LISTVIEW*)lpnmh;

			m_pPidlMgr->Delete((LPITEMIDLIST)lpnmlv->lParam);
		}
			break;

#ifdef LVN_ITEMACTIVATE

		case LVN_ITEMACTIVATE:

#else    //LVN_ITEMACTIVATE

		case NM_DBLCLK:
		case NM_RETURN:

#endif   //LVN_ITEMACTIVATE

			DoContextMenu(0, 0, TRUE, (DWORD)-1);
			return 0;

		case LVN_GETDISPINFO:
		{
			NMLVDISPINFO   *lpdi = (NMLVDISPINFO*)lpnmh;
			LPITEMIDLIST   pidl = (LPITEMIDLIST)lpdi->item.lParam;
			TCHAR szDecrFileLoc[MAX_PATH];

			if(m_pPidlMgr->GetStatus(pidl) == DECRYPTED)
			{
				GetDecryptedFileLocation(szDecrFileLoc, pidl);

				// Check if the file exists. If it does not then
				// remove the pidl
				HANDLE hFind;
				WIN32_FIND_DATA wfd;

				hFind = FindFirstFile(szDecrFileLoc, &wfd);
				if(INVALID_HANDLE_VALUE != hFind)
					FindClose(hFind);
				else
				{
					int itemIndex = FindItemPidl(pidl);
					if(itemIndex != -1)
						ListView_DeleteItem(m_hwndListDecr, itemIndex);

					break;
				}
			}

			// Is the sub-item information being requested?
			switch(lpdi->item.iSubItem)
			{
				case 0:
				{
					// Is the text being requested?
					if(lpdi->item.mask & LVIF_TEXT)
					{
						STRRET   str;

						if(SUCCEEDED(m_psfParent->GetDisplayNameOf(pidl, SHGDN_NORMAL | SHGDN_INFOLDER, &str)))
							GetTextFromSTRRET(m_pMalloc, &str, pidl, lpdi->item.pszText, lpdi->item.cchTextMax);
					}

					// Is the image being requested?
					if(lpdi->item.mask & LVIF_IMAGE)
					{
						IExtractIcon   *pei;

						if(SUCCEEDED(m_psfParent->GetUIObjectOf(m_hWnd, 1, (LPCITEMIDLIST*)&pidl, IID_IExtractIcon, NULL, (LPVOID*)&pei)))
						{
							UINT uFlags;
							SHFILEINFO sfi;

							// If the file is in the decrypted state 
							if(m_pPidlMgr->GetStatus(pidl) == DECRYPTED)
							{
								GetDecryptedFileLocation(szDecrFileLoc, pidl);

								// Replace the "lock/file" icon with the new file icon 
								SHGetFileInfo(szDecrFileLoc, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON);
								ImageList_ReplaceIcon(g_himlSmall, ICON_INDEX_LOCKFILE, sfi.hIcon);
								SHGetFileInfo(szDecrFileLoc, 0, &sfi, sizeof(sfi), SHGFI_ICON);
								ImageList_ReplaceIcon(g_himlLarge, ICON_INDEX_LOCKFILE, sfi.hIcon);

								// GetIconLocation will give us the index into our image list
								pei->GetIconLocation(GIL_FORSHELL, NULL, 0, &lpdi->item.iImage, &uFlags);
								pei->Release();
							}
						}
					}
				} // case 0
					break;

				case 1:
				{
					// Display the size. 
					__int64 FileSize = 0;
					
					// Get the path
					if(m_pPidlMgr->GetStatus(pidl) == DECRYPTED)
						GetDecryptedFileLocation(szDecrFileLoc, pidl);

					BY_HANDLE_FILE_INFORMATION fad;
					HANDLE hFile = CreateFile(szDecrFileLoc, 0, FILE_SHARE_READ,
											  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE,
											  NULL);

					GetFileInformationByHandle(hFile, &fad);
					CloseHandle(hFile);

					FileSize = fad.nFileSizeHigh + fad.nFileSizeLow;

					GetDisplaySize(FileSize, lpdi->item.pszText, FALSE);
				}
					break;

				case 2:
				{
					// Display the file type
					if(m_pPidlMgr->GetStatus(pidl) == DECRYPTED)
						GetDecryptedFileLocation(szDecrFileLoc, pidl);

					SHFILEINFO sfi;
					SHGetFileInfo(szDecrFileLoc, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
					lstrcpy(lpdi->item.pszText, sfi.szTypeName);
				}
					break;

				case 3:
				{
					// Display the file decryption date.
					if(m_pPidlMgr->GetStatus(pidl) == DECRYPTED)
					{
						GetDecryptedFileLocation(szDecrFileLoc, pidl);
						
						BY_HANDLE_FILE_INFORMATION fad;
						HANDLE hFile = CreateFile(szDecrFileLoc, 0, FILE_SHARE_READ,
												  NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);

						GetFileInformationByHandle(hFile, &fad);
						CloseHandle(hFile);

						GetDisplayTime(&fad.ftCreationTime, lpdi->item.pszText, FALSE);
					}
					
				}
					break;


				case 4:
				{ 
					// Display the current location of the file. 
					// For a file which is a "link" this column shld be blank
					if((m_pPidlMgr->GetStatus(pidl) == DECRYPTED))
						strcpy(lpdi->item.pszText, m_pPidlMgr->GetOriginalLocation(pidl));
				}
					break;

				default:
					break;

			} // switch(lpdi->item.iSubItem)

		}
			break;

		case LVN_BEGINDRAG:
		{
			HRESULT      hr;
			IDataObject	 *pDataObject = NULL;
			UINT         uItemCount;
			LPITEMIDLIST *aPidls;

			// Get the number of selected items
			uItemCount = ListView_GetSelectedCount(m_hwndListDecr);
			if(!uItemCount)
				return 0;

			aPidls = (LPITEMIDLIST*)m_pMalloc->Alloc(uItemCount * sizeof(LPITEMIDLIST));

			if(aPidls)
			{
				int   i;
				UINT  x;

				for(i = 0, x = 0; x < uItemCount && i < ListView_GetItemCount(m_hwndListDecr); i++)
				{
					if(ListView_GetItemState(m_hwndListDecr, i, LVIS_SELECTED))
					{
						LVITEM   lvItem;

						lvItem.mask = LVIF_PARAM;
						lvItem.iItem = i;

						ListView_GetItem(m_hwndListDecr, &lvItem);

						aPidls[x] = (LPITEMIDLIST)lvItem.lParam;
						x++;
					}
				}

				hr = m_psfParent->GetUIObjectOf(m_hWnd, uItemCount, 
								    (LPCITEMIDLIST*)aPidls, IID_IDataObject, 
								    NULL, (LPVOID*)&pDataObject);

				if(SUCCEEDED(hr) && pDataObject)
				{
					IDropSource *pDropSource = new CDropSource;
					DWORD       dwEffect = DROPEFFECT_MOVE;
					DWORD       dwAttributes = SFGAO_CANLINK;

					hr = m_psfParent->GetAttributesOf(uItemCount, 
										(LPCITEMIDLIST*)aPidls, &dwAttributes);

					DoDragDrop(pDataObject, pDropSource, dwEffect, &dwEffect);
					pDataObject->Release();
					pDropSource->Release();
				}

				m_pMalloc->Free(aPidls);
			}
		}
			break;
	} // switch(lpnmh->code)

	return 0;
}


VOID CShellView::GetDecryptedFileLocation(LPTSTR lpszDecrFileLoc, LPITEMIDLIST pidl)
{
	LPCTSTR lpOrigLoc = m_pPidlMgr->GetOriginalLocation(pidl);	
	lstrcpy(lpszDecrFileLoc, lpOrigLoc);

	// Check if the file exists in the original location. This check
	// is needed bcos in the case of drag/drop out of Safe the file
	// still remains in the Safe for sometime till Windows removes it.
	// So in this case the file information like 'icon', 'size'..
	// needs to be picked up from its location in the Safe itself

	HANDLE hFind;
	WIN32_FIND_DATA wfd;

	hFind = FindFirstFile(lpszDecrFileLoc, &wfd);
	if(INVALID_HANDLE_VALUE != hFind)
		FindClose(hFind);
	else
		// Get the decrypted files location in the Safe
		m_psfParent->GetPath(pidl, lpszDecrFileLoc, MAX_PATH);
}


LRESULT CShellView::OnSize(WORD wWidth, WORD wHeight)
{
	if(g_bLockedOut)
	{
		SendMessage(m_hWnd, WM_PAINT, 0, 0);
		return 0;
	}

	// Initially set the Split Bar position in the center of client area
	if(!m_nSplitPos)
		m_nSplitPos = wHeight/2;

	// Resize the ListView to fit our window
	if(m_hwndListEncr && m_hwndListDecr)
	{
		ListView_SetColumnWidth(m_hwndListEncr, 0, g_SafeProp.lDisplaySizes[0]);
		ListView_SetColumnWidth(m_hwndListEncr, 1, g_SafeProp.lDisplaySizes[1]);
		ListView_SetColumnWidth(m_hwndListEncr, 2, g_SafeProp.lDisplaySizes[2]);
		ListView_SetColumnWidth(m_hwndListEncr, 3, g_SafeProp.lDisplaySizes[3]);
		ListView_SetColumnWidth(m_hwndListEncr, 4, g_SafeProp.lDisplaySizes[4]);

		if(g_SafeProp.bDecryptPane)
		{
			MoveWindow(m_hwndListEncr, 0, m_nBmpVSLogoHt, wWidth, 
				   m_nSplitPos - m_nBmpVSLogoHt, TRUE);
			MoveWindow(m_hwndListDecr, 0, m_nSplitPos + 2 + 2*m_nBmpDecrHt, wWidth, 
				   wHeight - (m_nSplitPos + 2 + 2*m_nBmpDecrHt), TRUE);

			ListView_SetColumnWidth(m_hwndListDecr, 0, g_SafeProp.lDisplaySizes[5]);
			ListView_SetColumnWidth(m_hwndListDecr, 1, g_SafeProp.lDisplaySizes[6]);
			ListView_SetColumnWidth(m_hwndListDecr, 2, g_SafeProp.lDisplaySizes[7]);
			ListView_SetColumnWidth(m_hwndListDecr, 3, g_SafeProp.lDisplaySizes[8]);
			ListView_SetColumnWidth(m_hwndListDecr, 4, g_SafeProp.lDisplaySizes[9]);
		}
		else
			MoveWindow(m_hwndListEncr, 0, m_nBmpVSLogoHt, wWidth, 
					   wHeight - m_nBmpVSLogoHt, TRUE);
	}

	return 0;
}


VOID CShellView::CreateTransparentBitmap(HDC hdcDest, UINT nXDest, 
				UINT nYDest, UINT nWidth, UINT nHeight, HBITMAP hSrcBmp)
{
	BITMAP     bm;   
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;   
	POINT      ptSize;

	hdcTemp = CreateCompatibleDC(hdcDest);
	SelectObject(hdcTemp, hSrcBmp);   // Select the bitmap

	GetObject(hSrcBmp, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;            // Get width of bitmap
	ptSize.y = bm.bmHeight;           // Get height of bitmap
	DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
									  // to logical points

	// Create some DCs to hold temporary data.
	hdcBack   = CreateCompatibleDC(hdcDest);   
	hdcObject = CreateCompatibleDC(hdcDest);
	hdcMem    = CreateCompatibleDC(hdcDest);   
	hdcSave   = CreateCompatibleDC(hdcDest);

	// Create a bitmap for each DC. DCs are required for a number of
	// GDI functions.   

	// Monochrome DC
	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);

	// Monochrome DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem    = CreateCompatibleBitmap(hdcDest, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdcDest, ptSize.x, ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);   

	// Set proper mapping mode.
	SetMapMode(hdcTemp, GetMapMode(hdcDest));

	// Save the bitmap sent here, because it will be overwritten.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	cColor = SetBkColor(hdcTemp, RGB(192, 192, 192));

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC back to the original   
	// color.
	SetBkColor(hdcTemp, cColor);

	// Create the inverse of the object mask.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
		  NOTSRCCOPY);

	// Copy the background of the main DC to the destination.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcDest, nXDest, nYDest,
		  SRCCOPY);   

	// Mask out the places where the bitmap will be placed.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

	// Mask out the transparent colored pixels on the bitmap.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

	// Copy the destination to the screen.
	BitBlt(hdcDest, nXDest, nYDest, ptSize.x, ptSize.y, hdcMem, 0, 0,
		  SRCCOPY);

	// Place the original bitmap back into the bitmap sent here.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	// Delete the memory bitmaps.
	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));   

	// Delete the memory DCs.
	DeleteDC(hdcMem);   
	DeleteDC(hdcBack);   
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);   
	DeleteDC(hdcTemp);
}


LRESULT CShellView::OnPaint(VOID)
{
	RECT rc, rect;
	PAINTSTRUCT ps;
	HDC hdc;
	HBITMAP hOldBmp = NULL;

	hdc = GetDC(m_hWnd);

	BeginPaint(m_hWnd, &ps);

	if(!g_bLockedOut)
	{
		GetClientRect(m_hWnd, &rect);

		rc.top = rc.left = 0;
		rc.bottom = m_nBmpOpenSafeHt;
		rc.right = rect.right;

		FillRect(hdc, &rc, (HBRUSH )GetSysColorBrush(COLOR_3DFACE));

		// The Open Safe bitmap
		//HDC memDC = CreateCompatibleDC(NULL);

#if 0
		hOldBmp = (HBITMAP)SelectObject(memDC, m_hBmpOpenSafe);
		BitBlt(hdc, 4, 0, rect.right, m_nBmpOpenSafeHt, memDC, 0, 0, SRCCOPY);
#else
		CreateTransparentBitmap(hdc, 4, 0, rect.right, m_nBmpOpenSafeHt,
								m_hBmpOpenSafe);
#endif

#if 0
		// The "Encrypted" bitmap
		hOldBmp = (HBITMAP)SelectObject(memDC, m_hBmpEncr);
		BitBlt(hdc, 2*m_nBmpOpenSafeWd, (m_nBmpOpenSafeHt - m_nBmpEncrHt)/2, rect.right, 
			   m_nBmpOpenSafeHt, memDC, 0, 0, SRCCOPY);
#else
		CreateTransparentBitmap(hdc, 2*m_nBmpOpenSafeWd, (m_nBmpOpenSafeHt - m_nBmpEncrHt)/2, 
								rect.right, m_nBmpOpenSafeHt, m_hBmpEncr);
#endif

		// To prevent overlapping with the "Encrypted" bitmap
		if(UINT(rect.right) > m_nBmpOpenSafeWd*3 + m_nBmpEncrWd + m_nBmpVSLogoWd)
		{
			// The VSLogo bitmap over the list showing encrypted files
#if 0
			SelectObject(memDC, m_hBmpVSLogo);
			BitBlt(hdc, rect.right - m_nBmpVSLogoWd - m_nBmpVSLogoWd/8, 0, rect.right, 
				   m_nBmpVSLogoHt, memDC, 0, 0, SRCCOPY);
#else
			CreateTransparentBitmap(hdc, rect.right - m_nBmpVSLogoWd - m_nBmpVSLogoWd/8, 0, rect.right, 
						   m_nBmpVSLogoHt, m_hBmpVSLogo);
#endif

		}

		if(g_SafeProp.bDecryptPane)
		{
			rc.left = 0;
			rc.right = rect.right;
			rc.top = m_nSplitPos + 2;
			rc.bottom = rc.top + 2*m_nBmpDecrHt;
			FillRect(hdc, &rc, (HBRUSH )GetSysColorBrush(COLOR_3DFACE));

			// The Split Bar
			HBRUSH hOldbr = (HBRUSH)SelectObject(hdc, GetStockObject(GRAY_BRUSH));
			PatBlt(hdc, 0, m_nSplitPos, rect.right, 2, PATCOPY);

			// The bitmap over the list showing decrypted files. 
			// The Open Safe bitmap
#if 0
			SelectObject(memDC, m_hBmpDecr);
			BitBlt(hdc, 4,  m_nSplitPos + 2 + m_nBmpDecrHt/2, rect.right, 
				   2*m_nBmpDecrHt, memDC, 0, 0, SRCCOPY);
			SelectObject(hdc, hOldbr);
#else
			CreateTransparentBitmap(hdc, 4,  m_nSplitPos + 2 + m_nBmpDecrHt/2, rect.right, 
									2*m_nBmpDecrHt, m_hBmpDecr);
#endif
		}

		//SelectObject(memDC, hOldBmp);
		//DeleteDC(memDC);
		ReleaseDC(m_hWnd, hdc);
	}
	else
	{
		DefWindowProc(m_hWnd, WM_ERASEBKGND, (WPARAM)hdc, 0);

		GetClientRect(m_hWnd, &rect);

		rc.top = rc.left = 0;
		rc.bottom = m_nBmpSafeHt;
		rc.right = rect.right;

		FillRect(hdc, &rc, (HBRUSH )GetSysColorBrush(COLOR_3DFACE));

#if 0
		// The Close Safe bitmap
		HDC memDC = CreateCompatibleDC(NULL);

		HBITMAP hOldBmp = (HBITMAP)SelectObject(memDC, m_hBmpSafe);
		BitBlt(hdc, 4, 0, rect.right, m_nBmpSafeHt, memDC, 0, 0, SRCCOPY);
#else
		CreateTransparentBitmap(hdc, 4, 0, rect.right, m_nBmpSafeHt, m_hBmpSafe);
#endif
		
		// To prevent overlapping with the "Safe" bitmap
		if(UINT(rect.right) > m_nBmpSafeWd*3 + m_nBmpVSLogoWd)
		{
			// The VSLogo bitmap over the list showing encrypted files
#if 0
			SelectObject(memDC, m_hBmpVSLogo);
			BitBlt(hdc, rect.right - m_nBmpVSLogoWd - m_nBmpVSLogoWd/8, 0, rect.right, 
				   m_nBmpVSLogoHt, memDC, 0, 0, SRCCOPY);
#else
			CreateTransparentBitmap(hdc, rect.right - m_nBmpVSLogoWd - m_nBmpVSLogoWd/8, 0, rect.right, 
									m_nBmpVSLogoHt, m_hBmpVSLogo);
#endif
		}

		//SelectObject(memDC, hOldBmp);
		//DeleteDC(memDC);
		ReleaseDC(m_hWnd, hdc);
	}

	EndPaint(m_hWnd, &ps);

	return 0;
}



LRESULT CShellView::OnCreate(VOID)
{
	// The bitmap displayed over the list view
	m_hBmpVSLogo	= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_VSLOGO));
	m_hBmpSafe		= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_CLOSESAFE));
	m_hBmpOpenSafe	= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_OPENSAFE));
	m_hBmpDecr		= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_RECENTLY_DECR));
	m_hBmpEncr		= LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_ENCRYPTED));
	
	// Load the resize curor
	m_hCurNS		= LoadCursor(NULL, IDC_SIZENS);

	// Get bitmap info for Logo bitmap
	int cbSize = 0;
	BITMAP *pBitmap;
	cbSize = GetObject(m_hBmpVSLogo, cbSize, NULL);
	pBitmap = (BITMAP *)malloc(cbSize);
	if(!pBitmap)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ShellView::OnCreate() : Out of memory", 0);
	}

	cbSize = GetObject(m_hBmpVSLogo, cbSize, pBitmap);
	m_nBmpVSLogoHt = pBitmap->bmHeight;
	m_nBmpVSLogoWd = pBitmap->bmWidth;
	free(pBitmap);

	// Get bitmap info for Open Safe bitmap
	cbSize = GetObject(m_hBmpOpenSafe, cbSize, NULL);
	pBitmap = (BITMAP *)malloc(cbSize);
	if(!pBitmap)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ShellView::OnCreate() : Out of memory", 0);
	}

	cbSize = GetObject(m_hBmpOpenSafe, cbSize, pBitmap);
	m_nBmpOpenSafeHt = pBitmap->bmHeight;
	m_nBmpOpenSafeWd = pBitmap->bmWidth;
	free(pBitmap);

	// Get bitmap info for Close Safe bitmap
	cbSize = GetObject(m_hBmpSafe, cbSize, NULL);
	pBitmap = (BITMAP *)malloc(cbSize);
	if(!pBitmap)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ShellView::OnCreate() : Out of memory", 0);
	}

	cbSize = GetObject(m_hBmpSafe, cbSize, pBitmap);
	m_nBmpSafeHt = pBitmap->bmHeight;
	m_nBmpSafeWd = pBitmap->bmWidth; 
	free(pBitmap);

	// Get bitmap info for "Decrypted" bitmap
	cbSize = GetObject(m_hBmpDecr, cbSize, NULL);
	pBitmap = (BITMAP *)malloc(cbSize);
	if(!pBitmap)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ShellView::OnCreate() : Out of memory", 0);
	}

	cbSize = GetObject(m_hBmpDecr, cbSize, pBitmap);
	m_nBmpDecrHt = pBitmap->bmHeight;
	free(pBitmap);

	// Get bitmap info for "Encrypted" bitmap
	cbSize = GetObject(m_hBmpEncr, cbSize, NULL);
	pBitmap = (BITMAP *)malloc(cbSize);
	if(!pBitmap)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("ShellView::OnCreate() : Out of memory", 0);
	}

	cbSize = GetObject(m_hBmpEncr, cbSize, pBitmap);
	m_nBmpEncrHt = pBitmap->bmHeight;
	m_nBmpEncrWd = pBitmap->bmWidth;
	free(pBitmap);

	// Create the ListView
	if(CreateList())
		if(InitList())
			FillList(TRUE);

#if 0		
	HRESULT  hr;
	IDropTarget *pdt;
	// Get the IDropTarget for this folder
	hr = m_psfParent->CreateViewObject(m_hWnd, IID_IDropTarget, 
										(LPVOID*)&pdt);

	if(SUCCEEDED(hr))
	{
		// Register the window as a drop target
		RegisterDragDrop(m_hWnd, pdt);
		pdt->Release();
	}
#else
	CDropTarget *pdt = new CDropTarget(m_psfParent, m_hWnd);
	RegisterDragDrop(m_hWnd, pdt);
	pdt->Release();
#endif

	return 0;
}




LRESULT CShellView::OnDestroy(VOID)
{
	// Delete the bitmap created in OnCreate()
	DeleteObject(m_hBmpVSLogo);
	DeleteObject(m_hBmpOpenSafe);
	DeleteObject(m_hBmpSafe);
	DeleteObject(m_hBmpDecr);
	DeleteObject(m_hBmpEncr);

	// Unregister the window as a drop target
	RevokeDragDrop(m_hWnd);

	return 0;
}



BOOL CShellView::CreateList(VOID)
{
	DWORD dwStyle;

	dwStyle = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER |
			  LVS_SHAREIMAGELISTS | LVS_REPORT | LVS_AUTOARRANGE;

	// Create the list view showing the encrypted items
	m_hwndListEncr = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, NULL, dwStyle,
						 0, 0, 0, 0, m_hWnd, (HMENU)ID_LISTVIEW_ENCR, g_hInst, NULL);

	// Create the list view showing the decrypted items
	m_hwndListDecr = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, NULL, dwStyle,
						0, 0, 0, 0, m_hWnd, (HMENU)ID_LISTVIEW_DECR, g_hInst, NULL);


	if(!m_hwndListEncr || !m_hwndListDecr)
		return FALSE;

	GetShellSettings();

	return TRUE;
}



BOOL CShellView::InitList(VOID)
{
	LVCOLUMN    lvColumn;
	TCHAR       szString[MAX_PATH];

	// Empty the list. first the list showing encrypted contents
	ListView_DeleteAllItems(m_hwndListEncr);

	// Initialize the columns
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.pszText = szString;

	lvColumn.cx = g_SafeProp.lDisplaySizes[0];
	LoadString(g_hInst, IDS_FILE_NAME, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListEncr, 0, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[1];
	LoadString(g_hInst, IDS_FILE_SIZE, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListEncr, 1, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[2];
	LoadString(g_hInst, IDS_FILE_TYPE, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListEncr, 2, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[3];
	LoadString(g_hInst, IDS_DATE_ENCRYPT, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListEncr, 3, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[4];
	LoadString(g_hInst, IDS_ORIG_LOCATION, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListEncr, 4, &lvColumn);

	ListView_SetImageList(m_hwndListEncr, g_himlLarge, LVSIL_NORMAL);
	ListView_SetImageList(m_hwndListEncr, g_himlSmall, LVSIL_SMALL);

	// Empty the list. the list showing decrypted contents
	ListView_DeleteAllItems(m_hwndListDecr);

	lvColumn.cx = g_SafeProp.lDisplaySizes[5];
	LoadString(g_hInst, IDS_FILE_NAME, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListDecr, 0, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[6];
	LoadString(g_hInst, IDS_FILE_SIZE, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListDecr, 1, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[7];
	LoadString(g_hInst, IDS_FILE_TYPE, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListDecr, 2, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[8];
	LoadString(g_hInst, IDS_DATE_DECRYPT, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListDecr, 3, &lvColumn);

	lvColumn.cx = g_SafeProp.lDisplaySizes[9];
	LoadString(g_hInst, IDS_CURR_LOCATION, szString, sizeof(szString));
	ListView_InsertColumn(m_hwndListDecr, 4, &lvColumn);

	ListView_SetImageList(m_hwndListDecr, g_himlLarge, LVSIL_NORMAL);
	ListView_SetImageList(m_hwndListDecr, g_himlSmall, LVSIL_SMALL);

	return TRUE;
}



VOID CShellView::FillList(BOOL bCheckOrigLocation)
{
	LPENUMIDLIST pEnumIDList;
	
	// Add the items for the list view showing encrypted contents
	if(SUCCEEDED(m_psfParent->EnumObjects(m_hWnd, SHCONTF_NONFOLDERS | 
										SHCONTF_FOLDERS, &pEnumIDList)))
	{
		LPITEMIDLIST pidl;
		DWORD        dwFetched;

		while((S_OK == pEnumIDList->Next(1, &pidl, &dwFetched)) && dwFetched)
		{
			AddEncrItem(pidl);

			CEnumIDList* pEnumList = (CEnumIDList*)pEnumIDList;
			pEnumList->DeletePidl(pidl);
		}
	
		pEnumIDList->Release();
	}

	// This adds all files marked as DELETED in all the "fileinfo" files
	AddDecryptedContents(g_szStoragePath, bCheckOrigLocation);	
}


// Add the decypted files to the list view. For this go through the "fileinfo"
// file in each directory and check which files have the Status as DECRYPTED
// 'bCheckOrigLocation' useful for drag/drop out of Safe case
BOOL CShellView::AddDecryptedContents(TCHAR *pEncrFolder, 
									  BOOL bCheckOrigLocation)
{
	TCHAR szFileInfo[MAX_PATH];
	FileStatus Status;
	LPITEMIDLIST pidl;
	TCHAR szSectionNames[SECTION_NAME_SIZE], *pSectionName;
	
	lstrcpy(szFileInfo, pEncrFolder);
	strcat(szFileInfo, "\\fileinfo");

	// For this directory add all the decrypted files as indicated by the
	// "fileinfo" file
	if(GetPrivateProfileSectionNames(szSectionNames, SECTION_NAME_SIZE,
									 szFileInfo) == SECTION_NAME_SIZE - 2)
	{
		LogErrorMessage("AddDecryptedContents() : GetPrivateProfileSectionNames() size exceeded", 0);
		return FALSE;
	}

	pSectionName = szSectionNames;
	
	while(*pSectionName)
	{
		Status = (FileStatus)GetPrivateProfileInt(pSectionName, "Status", 
												  DELETED, szFileInfo);
		if(Status == DECRYPTED)
		{
			TCHAR szOrigLocation[MAX_PATH];
			FILETIME ft;
			WIN32_FIND_DATA wfd;
			HANDLE hFind;

			ft.dwLowDateTime	= 0;
			ft.dwHighDateTime	= 0;
			GetPrivateProfileString(pSectionName, "OrigLocation", "c:\\temp",
									szOrigLocation, MAX_PATH, szFileInfo);

			// Before creating the PIDL check if the file is actually present
			// in szOrigLocation. It could have been deleted or could have 
			// been re-encrypted. If so then delete this entry from the 
			// ini file

			if(!bCheckOrigLocation)
			{
				pidl = m_pPidlMgr->CreateItemPidl(pSectionName, szOrigLocation, 0,
											  &ft, &ft, &ft, Status);
				if(pidl)
					AddDecrItem(pidl);
			}
			else
			{
				hFind = FindFirstFile(szOrigLocation, &wfd);
				if(hFind != INVALID_HANDLE_VALUE )
				{
					FindClose(hFind);

					pidl = m_pPidlMgr->CreateItemPidl(pSectionName, szOrigLocation, 0,
												  &ft, &ft, &ft, Status);
					if(pidl)
						AddDecrItem(pidl);
				}
				else
				{
					// File was either delete or re-encrypted. Remove from ini
					WritePrivateProfileString(pSectionName, NULL, NULL, szFileInfo);
				}
			}

		}

		pSectionName += lstrlen(pSectionName) + 1;
	}

	// If this directory also has sub directories then repeat the above for
	// all directories
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR szPath[MAX_PATH];

	lstrcpy(szPath, pEncrFolder);
	SmartAppendBackslash(szPath);
	lstrcat(szPath, TEXT("*.*"));

	hFind = FindFirstFile(szPath, &wfd);
	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if((FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes) && 
				lstrcmpi(wfd.cFileName, TEXT(".")) && 
				lstrcmpi(wfd.cFileName, TEXT("..")))
			{
				lstrcpy(szPath, pEncrFolder);
				SmartAppendBackslash(szPath);
				lstrcat(szPath, wfd.cFileName);

				AddDecryptedContents(szPath, bCheckOrigLocation);
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

	return TRUE;
}


BOOL CShellView::AddDecrItem(LPCITEMIDLIST pidl)
{
	LVITEM   lvItem;

	ZeroMemory(&lvItem, sizeof(lvItem));

	// Set the mask
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

	// Add the item to the end of the list
	lvItem.iItem = ListView_GetItemCount(m_hwndListDecr);

	// Set the item's data
	lvItem.lParam = (LPARAM)pidl;

	// Get text on a callback basis
	lvItem.pszText = LPSTR_TEXTCALLBACK;

	// Get the image on a callback basis
	lvItem.iImage = I_IMAGECALLBACK;

	if(-1 == ListView_InsertItem(m_hwndListDecr, &lvItem))
		return FALSE;

	return TRUE;
}


#if (_WIN32_IE >= 0x0400)
typedef VOID (WINAPI *PFNSHGETSETTINGSPROC)(LPSHELLFLAGSTATE lpsfs, DWORD dwMask);

VOID CShellView::GetShellSettings(VOID)
{
	SHELLFLAGSTATE       sfs;
	HINSTANCE            hinstShell32;

	/*
	Since SHGetSettings is not implemented in all versions of the shell, get the 
	function address manually at run time. This allows the extension to run on all 
	platforms.
	*/

	ZeroMemory(&sfs, sizeof(sfs));

	/*
	The default, in case any of the following steps fails, is classic Windows 95 
	style.
	*/
	sfs.fWin95Classic = TRUE;

	hinstShell32 = LoadLibrary(TEXT("shell32.dll"));
	if(hinstShell32)
	{
		PFNSHGETSETTINGSPROC pfnSHGetSettings;

		pfnSHGetSettings = (PFNSHGETSETTINGSPROC)GetProcAddress(hinstShell32, "SHGetSettings");
		if(pfnSHGetSettings)
			(*pfnSHGetSettings)(&sfs, SSF_DOUBLECLICKINWEBVIEW | SSF_WIN95CLASSIC);
		FreeLibrary(hinstShell32);
	}

	DWORD dwExStyles = 0;

	if(!sfs.fWin95Classic && !sfs.fDoubleClickInWebView)
		dwExStyles |= LVS_EX_ONECLICKACTIVATE | 
					  LVS_EX_TRACKSELECT | 
					  LVS_EX_UNDERLINEHOT;

	ListView_SetExtendedListViewStyle(m_hwndListEncr, dwExStyles);
}
#else
VOID CShellView::GetShellSettings(VOID)
{
}
#endif



LRESULT CShellView::OnSettingChange(LPCTSTR lpszSection)
{
	if(0 == lstrcmpi(lpszSection, TEXT("ShellState")))
	{
		GetShellSettings();
		return 0;
	}

	return 0;
}



VOID CShellView::DoContextMenu(WORD x, WORD y, BOOL fDefault, DWORD dwCmdIn)
{
	UINT           uSelected = 0;
	LPITEMIDLIST   *aSelectedItems = NULL;
	LPCONTEXTMENU  pContextMenu = NULL;
	HWND hWndActiveList = GetFocus();
	g_bEncryptViewActive = TRUE;

	uSelected = ListView_GetSelectedCount(hWndActiveList);

	// This global var used to pass info about the active view to the context 
	// menu handler QueryContextMenu(). 
	if(hWndActiveList == m_hwndListDecr)
		g_bEncryptViewActive = FALSE;

	if(uSelected)
	{
		aSelectedItems = (LPITEMIDLIST*)m_pMalloc->Alloc((uSelected + 1) * sizeof(LPITEMIDLIST));

		if(aSelectedItems)
		{
			UINT     i;
			LVITEM   lvItem;

			ZeroMemory(&lvItem, sizeof(lvItem));
			lvItem.mask = LVIF_STATE | LVIF_PARAM;
			lvItem.stateMask = LVIS_SELECTED;
			lvItem.iItem = 0;

			i = 0;

			// Construct a list of all selected items storing their PIDL's
			// 'lvItem.lParam' contains the PIDL
			while(ListView_GetItem(hWndActiveList, &lvItem) && (i < uSelected))
			{
				if(lvItem.state & LVIS_SELECTED)
				{
					aSelectedItems[i] = (LPITEMIDLIST)lvItem.lParam;
					i++;
				}

				lvItem.iItem++;
			}

			// Get the Context Menu interface
			m_psfParent->GetUIObjectOf(m_hwndParent, uSelected,
									   (LPCITEMIDLIST*)aSelectedItems,
									   IID_IContextMenu, NULL, 
									   (LPVOID*)&pContextMenu);
		}
	}
	else
		// Get the Context Menu interface
		m_psfParent->CreateViewObject(m_hwndParent, IID_IContextMenu,
									  (LPVOID*)&pContextMenu);
	
	if(pContextMenu)
	{
		HMENU hMenu = CreatePopupMenu();

		// See if we are in Explore or Open mode. If the browser's tree is present, 
		// then we are in Explore mode.
		BOOL fExplore = FALSE;
		HWND hwndTree = NULL;

		if(SUCCEEDED(m_pShellBrowser->GetControlWindow(FCW_TREE, &hwndTree)) && hwndTree)
			fExplore = TRUE;
		
		if(hMenu && SUCCEEDED(pContextMenu->QueryContextMenu(hMenu, 0, 0, MENU_MAX,
															CMF_NORMAL | 
															(fExplore ? CMF_EXPLORE : 0) |
															((uSelected > 1) ? MYCMF_MULTISELECT: 0))))
		{
			UINT  uCommand;

			if(fDefault)
			{
				MENUITEMINFO mii;
				int          nMenuIndex;

				uCommand = 0;

				ZeroMemory(&mii, sizeof(mii));
				mii.cbSize = sizeof(mii);
				mii.fMask = MIIM_STATE | MIIM_ID;

				nMenuIndex = 0;

				// Find the default item in the menu
				while(GetMenuItemInfo(hMenu, nMenuIndex, TRUE, &mii))
				{
					if(mii.fState & MFS_DEFAULT)
					{
						uCommand = mii.wID;
						break;
					}

					nMenuIndex++;
				}
			}
			else if(-1 != dwCmdIn)
			{
				// This command will get sent directly without bringing up the menu
				uCommand = dwCmdIn;
			}
			else
			{
				uCommand = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RETURNCMD,
										  x, y, 0, m_hWnd, NULL);
			}

			if(uCommand > 0)
			{
				// Some commands need to be handled by the view itself
				switch(uCommand)
				{
					case IDM_VIEW_LARGE:
						OnViewLarge();
						break;

					case IDM_VIEW_SMALL:
						OnViewSmall();
						break;

					case IDM_VIEW_LIST:
						OnViewList();
						break;

					case IDM_VIEW_DETAILS:
						OnViewDetails();
						break;

					case IDM_BY_NAME:
						OnArrangeIcon(0);
						break;

					case IDM_BY_DATE_ENCRYPT:
						OnArrangeIcon(3);
						break;

					case IDM_BY_TYPE:
						OnArrangeIcon(2);
						break;

					case IDM_BY_SIZE:
						OnArrangeIcon(1);
						break;

					case IDM_BY_ORIGIN:
						OnArrangeIcon(4);
						break;

					case IDM_LOG_OUT:
						LogOut();
						break;

					case IDM_LOG_IN:
						LogIn(TRUE);
						break;

/*					case IDM_RESTORE_PASSWORD:
						if(RestorePassword())
							LogIn(FALSE);

						break;
*/
					default:
					{
						CMINVOKECOMMANDINFO  cmi;

						ZeroMemory(&cmi, sizeof(cmi));
						cmi.cbSize = sizeof(cmi);
						cmi.hwnd = m_hWnd;
						cmi.lpVerb = (LPCSTR)MAKEINTRESOURCE(uCommand);

						pContextMenu->InvokeCommand(&cmi);

						switch(uCommand)
						{
							case IDM_OPEN:
							case IDM_DELETE:
							case IDM_DECRYPT:
						    case IDM_DECRYPT_VERIFY:
							case IDM_ENCRYPT:
							case IDM_ENCRYPT_FILE:
									// Refresh all the views
									CShellView *pView;
									pView = g_pViewList->GetNextView(NULL);
									while(pView)
									{
										pView->Refresh();
										pView = g_pViewList->GetNextView(pView);
									}
						}
					}
						break;
				}
			}

			DestroyMenu(hMenu);
		}

		pContextMenu->Release();
	}

	if(aSelectedItems)
		m_pMalloc->Free(aSelectedItems);

	UpdateToolbar();
}



VOID CShellView::ShowViewWindow(VOID)
{
	Refresh();

	ShowWindow(m_hwndListEncr, SW_NORMAL);

	if(g_SafeProp.bDecryptPane)
		ShowWindow(m_hwndListDecr, SW_NORMAL);

	RECT rect;
	GetClientRect(m_hWnd, &rect);

	OnSize((USHORT)rect.right, (USHORT)rect.bottom);

	OnActivate(SVUIA_ACTIVATE_FOCUS);
	MergeToolbar();
}


VOID CShellView::HideViewWindow(VOID)
{
	HKEY hKey;
	DWORD dwType, dwSize = MAX_PATH;
	TCHAR szActiveDesktop[MAX_PATH];
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, ACTIVE_DESKTOP_KEY,
				0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hKey, NULL, NULL, &dwType,
				(LPBYTE)szActiveDesktop, &dwSize) == ERROR_SUCCESS)
		{
			if(!lstrcmpi(szActiveDesktop, "url.dll"))
			{
				ShowWindow(m_hwndListEncr, SW_HIDE);
				ShowWindow(m_hwndListDecr, SW_HIDE);

				SendMessage(m_hWnd, WM_PAINT, 0, 0);

				OnActivate(SVUIA_ACTIVATE_FOCUS);
				MergeToolbar();	// if active desktop is present then 'szActiveDesktop' will contain 'shell32.dll'
				RegCloseKey(hKey);
				return;			
			}				
		}					
		
		RegCloseKey(hKey);
	}

	BrowseToDesktop();	
	return;
}



BOOL CShellView::CollapseTree(VOID)
{
	HWND hwndTree = NULL;

	if(SUCCEEDED(m_pShellBrowser->GetControlWindow(FCW_TREE, &hwndTree)))
	{
		HTREEITEM hItem;
		TCHAR szStr[MAX_PATH];
		LoadString(g_hInst, IDS_EXT_TITLE, szStr, MAX_PATH);
		hItem = GetTreeItemByName(hwndTree, NULL, szStr);
		if(hItem)
			TreeView_Expand(hwndTree, hItem, TVE_COLLAPSE | TVE_COLLAPSERESET);
	}

	return TRUE;
}


BOOL CShellView::BrowseToRoot(VOID)
{
	IMalloc *pMalloc;
	STRRET sName;
	LPSHELLFOLDER pShellFolder;
	LPENUMIDLIST pEnumIDList = NULL;
	LPITEMIDLIST pItem = NULL;
	ULONG ulFetched = 0;
	TCHAR szPath[MAX_PATH], szExtName[MAX_PATH];

	LoadString(g_hInst, IDS_EXT_TITLE, szExtName, sizeof(szExtName));

	SHGetMalloc(&pMalloc);
	SHGetDesktopFolder(&pShellFolder);
	pShellFolder->EnumObjects(NULL, SHCONTF_FOLDERS, &pEnumIDList);
	while(pEnumIDList->Next(1, &pItem, &ulFetched) == NOERROR)
	{
		pShellFolder->GetDisplayNameOf(pItem, 0, &sName);
		GetTextFromSTRRET(NULL, &sName, pItem, szPath, MAX_PATH);
		if(!lstrcmpi(szPath, szExtName))
			break;

		pMalloc->Free(pItem);
		continue;
	}

	pEnumIDList->Release();
	pShellFolder->Release();

	int nFlags = SBSP_SAMEBROWSER | SBSP_WRITENOHISTORY;

	m_pShellBrowser->BrowseObject(pItem, nFlags);

	pMalloc->Free(pItem);
	pMalloc->Release();

	return TRUE;
}


BOOL CShellView::BrowseToDesktop(VOID)
{
	LPITEMIDLIST pidlDesktop;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);

	int nFlags = SBSP_SAMEBROWSER | SBSP_WRITENOHISTORY;

	m_pShellBrowser->BrowseObject(pidlDesktop, nFlags);

	IMalloc *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidlDesktop);
   	   pMalloc->Release();
	}

	return TRUE;
}


void CShellView::OnArrangeIcon(UINT nColIndex)
{
	if(GetFocus() == m_hwndListEncr)
		OnArrangeIconEncr(nColIndex);
	else
		OnArrangeIconDecr(nColIndex);
}


BOOL CShellView::AddEncrItem(LPCITEMIDLIST pidl)
{
	LVITEM   lvItem;
	ZeroMemory(&lvItem, sizeof(lvItem));

	// Set the mask
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;

	// Add the item to the end of the list
	lvItem.iItem = ListView_GetItemCount(m_hwndListEncr);

	// Get the item's data
	lvItem.lParam = (LPARAM)m_pPidlMgr->Copy(pidl);

	// Get text on a callback basis
	lvItem.pszText = LPSTR_TEXTCALLBACK;

	// Get the image on a callback basis
	lvItem.iImage = I_IMAGECALLBACK;

	// Set the state to use overlay
	if(!m_pPidlMgr->IsFolder(pidl))
	{
		lvItem.mask |=  LVIF_STATE;
		lvItem.state = INDEXTOOVERLAYMASK(1);
		lvItem.stateMask = LVIS_OVERLAYMASK;
	}

	// Add the item
	if(-1 == ListView_InsertItem(m_hwndListEncr, &lvItem))
		return FALSE;

	return TRUE;
}


// Called from NotifyViews() for the case of SHCNE_RMDIR & SHCNE_DELETE
// The 'pidl' passed is assumed to be that of an item in the Encrypted view
// bcos no delete/remove operation are supported for the Decrypted view
// For the Encrypted view a delete for a 'Folder' occurs when all the files in
// it are decrypted or the 'Folder' itself is decrypted. No 'Delete' operation
// is supported directly for a File/Folder
BOOL CShellView::DeleteItem(LPCITEMIDLIST pidl)
{
	//delete the item from the list
	int nIndex = FindItemPidl(pidl);
	if(nIndex != -1)
		return ListView_DeleteItem(m_hwndListEncr, nIndex);
	
	return FALSE;
}



int CShellView::FindItemPidl(LPCITEMIDLIST pidl)
{
	LVITEM   lvItem;

	ZeroMemory(&lvItem, sizeof(lvItem));
	lvItem.mask = LVIF_PARAM;

	// First check in the encrypted list view
	for(lvItem.iItem = 0; ListView_GetItem(m_hwndListEncr, &lvItem); lvItem.iItem++)
	{
		LPITEMIDLIST pidlFound = (LPITEMIDLIST)lvItem.lParam;
		
		HRESULT hr = m_psfParent->CompareIDs(0, pidl, pidlFound);
		if(SUCCEEDED(hr) && 0 == HRESULT_CODE(hr))
			return lvItem.iItem;	// We found the item
	}

	// Now check in the decrypted list view
	for(lvItem.iItem = 0; ListView_GetItem(m_hwndListDecr, &lvItem); lvItem.iItem++)
	{
		LPITEMIDLIST   pidlFound = (LPITEMIDLIST)lvItem.lParam;
		
		HRESULT hr = m_psfParent->CompareIDs(0, pidl, pidlFound);
		if(SUCCEEDED(hr) && 0 == HRESULT_CODE(hr))
			return lvItem.iItem;	// We found the item
	}

	return -1;
}



// This is called from NotifyView(). Remove the file from encrypted list 
// and show it in the decrypted list or vice versa.
VOID CShellView::UpdateData(LPCITEMIDLIST pidlOld, LPCITEMIDLIST pidlNew)
{
	int i;
	i = FindItemPidl(pidlOld);

	if(-1 != i)
	{
		// pidlNew is valid when called from UpdateDecrItem(). a new PIDL is 
		// created bcos the file is out of Safe. Now it is being put back in the
		// Safe. Some of its attributes(size..) might have been modified so 
		// cannot reuse the old PIDL
		if(pidlNew)
		{
			// Delete the item from the list view showing decrypted contents
			ListView_DeleteItem(m_hwndListDecr, i);
			
			// Add an item in the list view showing encrypted contents
			AddEncrItem(pidlNew);
		}
		else
		{
			// pidlNew is NULL in this case as while decrypting a new PIDL is 
			// not created. The old PIDL is used and its status is marked as
			// decrypted.

			// Delete the item from the list view showing encrypted contents
			ListView_DeleteItem(m_hwndListEncr, i);

			// Add an item in the list view showing decrypted contents
			AddDecrItem(m_pPidlMgr->Copy(pidlOld));
		}
	}
}



LRESULT CShellView::OnViewLarge(VOID)
{
	m_FolderSettings.ViewMode = FVM_ICON;

	DWORD dwStyle = GetWindowLong(m_hwndListEncr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_ICON;
	SetWindowLong(m_hwndListEncr, GWL_STYLE, dwStyle);

	dwStyle = GetWindowLong(m_hwndListDecr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_ICON;
	SetWindowLong(m_hwndListDecr, GWL_STYLE, dwStyle);

	return 0;
}



LRESULT CShellView::OnViewSmall(VOID)
{
	m_FolderSettings.ViewMode = FVM_SMALLICON;

	DWORD dwStyle = GetWindowLong(m_hwndListEncr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_SMALLICON;
	SetWindowLong(m_hwndListEncr, GWL_STYLE, dwStyle);

	dwStyle = GetWindowLong(m_hwndListDecr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_SMALLICON;
	SetWindowLong(m_hwndListDecr, GWL_STYLE, dwStyle);
	
	return 0;
}



LRESULT CShellView::OnViewList(VOID)
{
	m_FolderSettings.ViewMode = FVM_LIST;

	DWORD dwStyle = GetWindowLong(m_hwndListEncr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_LIST;
	SetWindowLong(m_hwndListEncr, GWL_STYLE, dwStyle);

	dwStyle = GetWindowLong(m_hwndListDecr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_LIST;
	SetWindowLong(m_hwndListDecr, GWL_STYLE, dwStyle);

	return 0;
}



LRESULT CShellView::OnViewDetails(VOID)
{
	m_FolderSettings.ViewMode = FVM_DETAILS;

	DWORD dwStyle = GetWindowLong(m_hwndListEncr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_REPORT;
	SetWindowLong(m_hwndListEncr, GWL_STYLE, dwStyle);

	dwStyle = GetWindowLong(m_hwndListDecr, GWL_STYLE);
	dwStyle &= ~LVS_TYPEMASK;
	dwStyle |= LVS_REPORT;
	SetWindowLong(m_hwndListDecr, GWL_STYLE, dwStyle);

	return 0;
}




LRESULT CShellView::OnArrangeIconEncr(UINT uSubItem)
{
	switch(uSubItem)
	{
		case 0:
			m_bSortAscEncrName = !m_bSortAscEncrName;
			m_bSortAsc = m_bSortAscEncrName;
			ListView_SortItems(m_hwndListEncr, &CShellView::SortByName, this);
			break;

		case 1:
			m_bSortAscEncrSize = !m_bSortAscEncrSize;
			m_bSortAsc = m_bSortAscEncrSize;
			ListView_SortItems(m_hwndListEncr, &CShellView::SortBySize, this);
			break;

		case 2:
			m_bSortAscEncrType = !m_bSortAscEncrType;
			m_bSortAsc = m_bSortAscEncrType;
			ListView_SortItems(m_hwndListEncr, &CShellView::SortByType, this);
			break;

		case 3:
			m_bSortAscEncrDate = !m_bSortAscEncrDate;
			m_bSortAsc = m_bSortAscEncrDate;
			ListView_SortItems(m_hwndListEncr, &CShellView::SortByDate, this);
			break;

		case 4:
			m_bSortAscEncrLoc = !m_bSortAscEncrLoc;
			m_bSortAsc = m_bSortAscEncrLoc;
			ListView_SortItems(m_hwndListEncr, &CShellView::SortByLoc, this);
			break;
	}

	return 0;
}



LRESULT CShellView::OnArrangeIconDecr(UINT uSubItem)
{
	switch(uSubItem)
	{
		case 0:
			m_bSortAscDecrName = !m_bSortAscDecrName;
			m_bSortAsc = m_bSortAscDecrName;
			ListView_SortItems(m_hwndListDecr, &CShellView::SortByName, this);
			break;

		case 1:
			m_bSortAscDecrSize = !m_bSortAscDecrSize;
			m_bSortAsc = m_bSortAscDecrSize;
			ListView_SortItems(m_hwndListDecr, &CShellView::SortBySize, this);
			break;

		case 2:
			m_bSortAscDecrType = !m_bSortAscDecrType;
			m_bSortAsc = m_bSortAscDecrType;
			ListView_SortItems(m_hwndListDecr, &CShellView::SortByType, this);
			break;

		case 3:
			m_bSortAscDecrDate = !m_bSortAscDecrDate;
			m_bSortAsc = m_bSortAscDecrDate;
			ListView_SortItems(m_hwndListDecr, &CShellView::SortByDate, this);
			break;

		case 4:
			m_bSortAscDecrLoc = !m_bSortAscDecrLoc;
			m_bSortAsc = m_bSortAscDecrLoc;
			ListView_SortItems(m_hwndListDecr, &CShellView::SortByLoc, this);
			break;
	}

	return 0;
}


int CALLBACK CShellView::SortByLoc(LPARAM lItem1, LPARAM lItem2, 
									LPARAM lAppValue)
{
	CShellView *pShellView = (CShellView *)lAppValue;
	int retVal = 0;

	TCHAR szPath1[MAX_PATH], szPath2[MAX_PATH];
	LPITEMIDLIST pidl1 = (LPITEMIDLIST)lItem1;
	LPITEMIDLIST pidl2 = (LPITEMIDLIST)lItem2;

	if(pShellView->m_pPidlMgr->IsFolder(pidl1) && 
	   pShellView->m_pPidlMgr->IsFolder(pidl2))
	{
		if(pShellView->m_bSortAsc)
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = 1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = -1;
		}
		else
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = -1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = 1;
		}
	}
	else
	{
		TCHAR szLoc1[MAX_PATH], szLoc2[MAX_PATH];

		if(!pShellView->m_pPidlMgr->IsFolder(pidl1) && 
		   !pShellView->m_pPidlMgr->IsFolder(pidl2))
		{			
			strcpy(szLoc1, pShellView->m_pPidlMgr->GetOriginalLocation(pidl1));
			strcpy(szLoc2, pShellView->m_pPidlMgr->GetOriginalLocation(pidl2));

			if(pShellView->m_bSortAsc)
			{
				if(lstrcmp(szLoc1, szLoc2) > 0)
					retVal = 1;
				else
					if(lstrcmp(szLoc1, szLoc2) < 0)
						retVal = -1;
			}
			else
			{
				if(lstrcmp(szLoc1, szLoc2) > 0)
					retVal = -1;
				else
					if(lstrcmp(szLoc1, szLoc2) < 0)
						retVal = 1;
			}
		}
		else
		{
			// One file and one folder
			if(pShellView->m_bSortAsc)
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = -1;
				else
					retVal = 1;
			}
			else
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = 1;
				else
					retVal = -1;
			}
		}
	}
		
	return retVal;
}


int CALLBACK CShellView::SortBySize(LPARAM lItem1, LPARAM lItem2, 
									LPARAM lAppValue)
{
	CShellView *pShellView = (CShellView *)lAppValue;
	int retVal = 0;

	TCHAR szPath1[MAX_PATH], szPath2[MAX_PATH];

	LPITEMIDLIST pidl1 = (LPITEMIDLIST)lItem1;
	LPITEMIDLIST pidl2 = (LPITEMIDLIST)lItem2;

	if(pShellView->m_pPidlMgr->GetStatus(pidl1) == DECRYPTED)
	{
		strcpy(szPath1, pShellView->m_pPidlMgr->GetOriginalLocation(pidl1));
		strcpy(szPath2, pShellView->m_pPidlMgr->GetOriginalLocation(pidl2));
	}
	else
	{
		pShellView->m_psfParent->GetPath(pidl1, szPath1, MAX_PATH);
		pShellView->m_psfParent->GetPath(pidl2, szPath2, MAX_PATH);
	}

	if(pShellView->m_pPidlMgr->IsFolder(pidl1) && 
	   pShellView->m_pPidlMgr->IsFolder(pidl2))
	{
		if(pShellView->m_bSortAsc)
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = 1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = -1;
		}
		else
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = -1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = 1;
		}
	}
	else
	{
		if(!pShellView->m_pPidlMgr->IsFolder(pidl1) && 
		   !pShellView->m_pPidlMgr->IsFolder(pidl2))
		{			
			HANDLE hFile;
			BY_HANDLE_FILE_INFORMATION fad;

			hFile = CreateFile(szPath1, GENERIC_READ, FILE_SHARE_READ, NULL, 
							   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			GetFileInformationByHandle(hFile, &fad);
			__int64 FileSize1 = fad.nFileSizeHigh + fad.nFileSizeLow;
			CloseHandle(hFile);

			hFile = CreateFile(szPath2, GENERIC_READ, FILE_SHARE_READ, NULL, 
							   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			GetFileInformationByHandle(hFile, &fad);
			__int64 FileSize2 = fad.nFileSizeHigh + fad.nFileSizeLow;
			CloseHandle(hFile);

			if(pShellView->m_bSortAsc)
			{
				if(FileSize1 > FileSize2)
					retVal = 1;
				else
					if(FileSize1 < FileSize2)
						retVal = -1;
					else
					{
						// Size are same, compare by name
						if(lstrcmp(szPath1, szPath2) > 0)
							retVal = 1;
						else
							if(lstrcmp(szPath1, szPath2) < 0)
								retVal = -1;
					}
			}
			else
			{
				if(FileSize1 > FileSize2)
					retVal = -1;
				else
					if(FileSize1 < FileSize2)
						retVal = 1;
					else
					{
						// Size are same, compare by name
						if(lstrcmp(szPath1, szPath2) > 0)
							retVal = -1;
						else
							if(lstrcmp(szPath1, szPath2) < 0)
								retVal = 1;
					}
			}
		}
		else
		{
			// One file and one folder
			if(pShellView->m_bSortAsc)
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = -1;
				else
					retVal = 1;
			}
			else
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = 1;
				else
					retVal = -1;
			}
		}
	}
	
	
	return retVal;
}


int CALLBACK CShellView::SortByDate(LPARAM lItem1, LPARAM lItem2, 
									LPARAM lAppValue)
{
	CShellView *pShellView = (CShellView *)lAppValue;
	int retVal = 0;

	TCHAR szPath1[MAX_PATH], szPath2[MAX_PATH];

	LPITEMIDLIST pidl1 = (LPITEMIDLIST)lItem1;
	LPITEMIDLIST pidl2 = (LPITEMIDLIST)lItem2;

	if(pShellView->m_pPidlMgr->GetStatus(pidl1) == DECRYPTED)
	{
		strcpy(szPath1, pShellView->m_pPidlMgr->GetOriginalLocation(pidl1));
		strcpy(szPath2, pShellView->m_pPidlMgr->GetOriginalLocation(pidl2));
	}
	else
	{
		pShellView->m_psfParent->GetPath(pidl1, szPath1, MAX_PATH);
		pShellView->m_psfParent->GetPath(pidl2, szPath2, MAX_PATH);
	}

	if(pShellView->m_pPidlMgr->IsFolder(pidl1) && 
	   pShellView->m_pPidlMgr->IsFolder(pidl2))
	{
		if(pShellView->m_bSortAsc)
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = 1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = -1;
		}
		else
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = -1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = 1;
		}
	}
	else
	{
		if(!pShellView->m_pPidlMgr->IsFolder(pidl1) && 
		   !pShellView->m_pPidlMgr->IsFolder(pidl2))
		{			
			HANDLE hFile;
			BY_HANDLE_FILE_INFORMATION fad;

			hFile = CreateFile(szPath1, GENERIC_READ, FILE_SHARE_READ, NULL, 
							   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			GetFileInformationByHandle(hFile, &fad);
			const FILETIME ft1 = fad.ftCreationTime;
			CloseHandle(hFile);

			
			hFile = CreateFile(szPath2, GENERIC_READ, FILE_SHARE_READ, NULL, 
							   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			GetFileInformationByHandle(hFile, &fad);
			const FILETIME ft2 = fad.ftCreationTime;
			CloseHandle(hFile);

			if(pShellView->m_bSortAsc)
			{
				if(CompareFileTime(&ft1, &ft2) > 0)
					retVal = 1;
				else
					if(CompareFileTime(&ft1, &ft2) < 0)
						retVal = -1;
			}
			else
			{
				if(CompareFileTime(&ft1, &ft2) > 0)
					retVal = -1;
				else
					if(CompareFileTime(&ft1, &ft2) < 0)
						retVal = 1;
			}
		}
		else
		{
			// One file and one folder
			if(pShellView->m_bSortAsc)
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = 1;
				else
					retVal = -1;
			}
			else
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = -1;
				else
					retVal = 1;
			}
		}
	}
	
	
	return retVal;
}


int CALLBACK CShellView::SortByName(LPARAM lItem1, LPARAM lItem2, 
									LPARAM lAppValue)
{
	CShellView *pShellView = (CShellView *)lAppValue;
	int retVal = 0;

	TCHAR szPath1[MAX_PATH], szPath2[MAX_PATH];
	LPITEMIDLIST pidl1 = (LPITEMIDLIST)lItem1;
	LPITEMIDLIST pidl2 = (LPITEMIDLIST)lItem2;

	pShellView->m_psfParent->GetPath(pidl1, szPath1, MAX_PATH);
	pShellView->m_psfParent->GetPath(pidl2, szPath2, MAX_PATH);

	if(pShellView->m_pPidlMgr->IsFolder(pidl1) && 
	   pShellView->m_pPidlMgr->IsFolder(pidl2))
	{
		if(pShellView->m_bSortAsc)
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = 1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = -1;
		}
		else
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = -1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = 1;
		}
	}
	else
	{
		if(!pShellView->m_pPidlMgr->IsFolder(pidl1) && 
		   !pShellView->m_pPidlMgr->IsFolder(pidl2))
		{			
			if(pShellView->m_bSortAsc)
			{
				if(lstrcmp(szPath1, szPath2) > 0)
					retVal = 1;
				else
					if(lstrcmp(szPath1, szPath2) < 0)
						retVal = -1;
			}
			else
			{
				if(lstrcmp(szPath1, szPath2) > 0)
					retVal = -1;
				else
					if(lstrcmp(szPath1, szPath2) < 0)
						retVal = 1;
			}
		}
		else
		{
			// One file and one folder
			if(pShellView->m_bSortAsc)
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = -1;
				else
					retVal = 1;
			}
			else
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = 1;
				else
					retVal = -1;
			}
		}
	}
	
	
	return retVal;
}


int CALLBACK CShellView::SortByType(LPARAM lItem1, LPARAM lItem2, 
									LPARAM lAppValue)
{
	SHFILEINFO sfi;
	CShellView *pShellView = (CShellView *)lAppValue;
	int retVal = 0;

	TCHAR szPath1[MAX_PATH], szPath2[MAX_PATH], szType1[MAX_PATH], szType2[MAX_PATH];
	LPITEMIDLIST pidl1 = (LPITEMIDLIST)lItem1;
	LPITEMIDLIST pidl2 = (LPITEMIDLIST)lItem2;

	if(pShellView->m_pPidlMgr->GetStatus(pidl1) == DECRYPTED)
	{
		strcpy(szPath1, pShellView->m_pPidlMgr->GetOriginalLocation(pidl1));
		SHGetFileInfo(szPath1, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
		lstrcpy(szType1, sfi.szTypeName);

		strcpy(szPath2, pShellView->m_pPidlMgr->GetOriginalLocation(pidl2));
		SHGetFileInfo(szPath2, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
		lstrcpy(szType2, sfi.szTypeName);
	}
	else
	{
		pShellView->m_psfParent->GetPath(pidl1, szPath1, MAX_PATH);
		SHGetFileInfo(szPath1, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
		lstrcpy(szType1, sfi.szTypeName);

		pShellView->m_psfParent->GetPath(pidl2, szPath2, MAX_PATH);
		SHGetFileInfo(szPath2, 0, &sfi, sizeof(sfi), SHGFI_TYPENAME);
		lstrcpy(szType2, sfi.szTypeName);
	}

	if(pShellView->m_pPidlMgr->IsFolder(pidl1) && 
	   pShellView->m_pPidlMgr->IsFolder(pidl2))
	{
		if(pShellView->m_bSortAsc)
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = 1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = -1;
		}
		else
		{
			if(lstrcmp(szPath1, szPath2) > 0)
				retVal = -1;
			else
				if(lstrcmp(szPath1, szPath2) < 0)
					retVal = 1;
		}
	}
	else
	{
		if(!pShellView->m_pPidlMgr->IsFolder(pidl1) && 
		   !pShellView->m_pPidlMgr->IsFolder(pidl2))
		{			
			if(pShellView->m_bSortAsc)
			{
				if(lstrcmp(szType1, szType2) > 0)
					retVal = 1;
				else
					if(lstrcmp(szType1, szType2) < 0)
						retVal = -1;
					else
					{
						// If types are same, check by name
						if(lstrcmp(szPath1, szPath2) > 0)
							retVal = 1;
						else
							if(lstrcmp(szPath1, szPath2) < 0)
								retVal = -1;
					}
			}
			else
			{
				if(lstrcmp(szType1, szType2) > 0)
					retVal = -1;
				else
					if(lstrcmp(szType1, szType2) < 0)
						retVal = 1;
					else
					{
						// If types are same, check by name
						if(lstrcmp(szPath1, szPath2) > 0)
							retVal = -1;
						else
							if(lstrcmp(szPath1, szPath2) < 0)
								retVal = 1;
					}
			}
		}
		else
		{
			// One file and one folder
			if(pShellView->m_bSortAsc)
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = -1;
				else
					retVal = 1;
			}
			else
			{
				if(pShellView->m_pPidlMgr->IsFolder(pidl1))
					retVal = 1;
				else
					retVal = -1;
			}
		}
	}
	
	
	return retVal;
}


VOID CShellView::SelectAll(VOID)
{
	HWND hWndFocus = GetFocus();

	if(hWndFocus != m_hwndListEncr && hWndFocus != m_hwndListDecr)
		hWndFocus = m_hwndListEncr;

	SetFocus(hWndFocus);

	ListView_SetItemState(hWndFocus, -1, LVIS_SELECTED, LVIS_SELECTED);
}


VOID CShellView::InvertSelection(VOID)
{
	HWND hWndFocus = m_hwndListEncr;

	if(GetFocus() == m_hwndListDecr)
		hWndFocus = m_hwndListDecr;


	LVITEM lvItem;
	ZeroMemory(&lvItem, sizeof(lvItem));

	lvItem.mask			= LVIF_STATE;
	lvItem.stateMask	= LVIS_SELECTED;
	lvItem.iItem		= 0;

	while(ListView_GetItem(hWndFocus, &lvItem))
	{
		if(lvItem.state & LVIS_SELECTED)
			lvItem.state &= ~ LVIS_SELECTED;
		else
			lvItem.state |= LVIS_SELECTED;

		ListView_SetItem(hWndFocus, &lvItem);

		lvItem.iItem++;
	}
}



BOOL CShellView::ClearList()
{
	ListView_DeleteAllItems(m_hwndListDecr);

	return TRUE;
}


BOOL CShellView::ShowDecryptView()
{
	RECT rect;
	GetClientRect(m_hWnd, &rect);
	
	UINT width	= rect.right - rect.left;
	UINT height = rect.bottom - rect.top;

	if(g_SafeProp.bDecryptPane)
	{
		ShowWindow(m_hwndListDecr, SW_NORMAL);

		MoveWindow(m_hwndListEncr, 0, m_nBmpVSLogoHt, width, 
			   m_nSplitPos - m_nBmpVSLogoHt, TRUE);
		MoveWindow(m_hwndListDecr, 0, m_nSplitPos + 2 + 2*m_nBmpDecrHt, width, 
			   height - m_nSplitPos + 2 + 2*m_nBmpDecrHt, TRUE);
	}
	else
	{
		ShowWindow(m_hwndListDecr, SW_HIDE);

		MoveWindow(m_hwndListEncr, 0, m_nBmpVSLogoHt, width, 
				    height - m_nBmpVSLogoHt, TRUE);
	}

	InvalidateRect(m_hWnd, NULL, TRUE);

	return TRUE;
}


BOOL CShellView::DropAllowed(LPPOINT pCurPos, BOOL bEncryptDrag)
{
	RECT rcEncr, rcDecr;
	POINT Cur;

	GetCursorPos(&Cur);

	GetWindowRect(m_hwndListEncr, &rcEncr);
	GetWindowRect(m_hwndListDecr, &rcDecr);

	// -1 if CF_HDROP
	if(pCurPos->x == -1 || pCurPos->y == -1)	
	{
		if(PtInRect(&rcDecr, Cur))
			return FALSE;
		else
			return TRUE;
	}
	else
	{
		// Drag/Drop between the 2 listviews
		if(bEncryptDrag)
			return PtInRect(&rcDecr, Cur);
		else
			return PtInRect(&rcEncr, Cur);
	}

	return FALSE;
}


BOOL CShellView::IsExplorerTreePresent(VOID)
{
	HWND hwndTree = NULL;

	if(SUCCEEDED(m_pShellBrowser->GetControlWindow(FCW_TREE, &hwndTree)) 
				&& hwndTree)
		return TRUE;
	else
		return FALSE;
}

