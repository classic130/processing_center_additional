// Implements the IContextMenu interface for context menus in the NameSpace 
// extension. The CShellFolder implements the ContextMenu for "Encrypt" menu item

#include "stdafx.h"
#include "ptav3.h"
#include "common.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "ContMenu.h"
#include "ShlView.h"
#include "viewlist.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "encdeclist.h"

extern CViewList *g_pViewList;
extern SafeSettings g_SafeProp;
extern BOOL g_bLockedOut;
extern CEncDecList *g_EncrAtLogoffList, *g_DecrAtLogonList;
extern TCHAR g_szInstallDir[MAX_PATH];

CContextMenu::CContextMenu(CShellFolder *psfParent, LPCITEMIDLIST *aPidls, UINT uItemCount)
{
	g_DllRefCount++;

	m_ObjRefCount	= 1;
	m_aPidls		= NULL;
	m_uItemCount	= 0;
	m_fBackground	= FALSE;
	m_psfParent		= psfParent;
	if(m_psfParent)
		m_psfParent->AddRef();

	SHGetMalloc(&m_pMalloc);
	if(!m_pMalloc)
	{
		delete this;
		return;
	}

	m_pPidlMgr = new CPidlMgr();
	m_uItemCount = uItemCount;
	if(m_uItemCount)
	{
		m_aPidls = AllocPidlTable(uItemCount);
		if(m_aPidls)
			FillPidlTable(aPidls, uItemCount);
	}
	else
		m_fBackground = TRUE;
}


CContextMenu::~CContextMenu()
{
	if(m_psfParent)
		m_psfParent->Release();

	g_DllRefCount--;

	if(m_aPidls && m_pMalloc)
		FreePidlTable(m_aPidls);
	
	if(m_pPidlMgr)
		delete m_pPidlMgr;

	if(m_pMalloc)
		m_pMalloc->Release();
}


// IUnknown Implementation
STDMETHODIMP CContextMenu::QueryInterface(REFIID riid, LPVOID FAR * ppReturn)
{
	*ppReturn = NULL;

	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = (LPUNKNOWN)(LPCONTEXTMENU)this;
	
	if(IsEqualIID(riid, IID_IContextMenu))
		*ppReturn = (LPCONTEXTMENU)this;
	
	if(IsEqualIID(riid, IID_IShellExtInit))
		*ppReturn = (LPSHELLEXTINIT)this;
	
	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             



STDMETHODIMP_(DWORD) CContextMenu::AddRef()
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CContextMenu::Release()
{
	if(--m_ObjRefCount == 0)
		delete this;

	return m_ObjRefCount;
}


// IContextMenu Implementation
STDMETHODIMP CContextMenu::QueryContextMenu(HMENU hMenu, UINT indexMenu,
                             UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if(!g_bLockedOut && !(CMF_DEFAULTONLY & uFlags))
	{
		if(m_fBackground)	// Add the menu items that apply to the background of the view
		{					
			if(g_bEncryptViewActive)
				InsertBackgroundEncryptItems(hMenu, indexMenu, idCmdFirst);
			else
				InsertBackgroundDecryptItems(hMenu, indexMenu, idCmdFirst);
		}
		else
		{
			if(g_bEncryptViewActive)
				InsertEncryptViewItems(hMenu, indexMenu, idCmdFirst, uFlags);
			else
				InsertDecryptViewItems(hMenu, indexMenu, idCmdFirst, uFlags);
		}

		g_bEncryptViewActive = TRUE;

		return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_LAST + 1));
	}

	g_bEncryptViewActive = TRUE;

	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}



STDMETHODIMP CContextMenu::InvokeCommand(LPCMINVOKECOMMANDINFO pici)
{
	if(pici->cbSize < sizeof(CMINVOKECOMMANDINFO))
		return E_INVALIDARG;

	// This will also catch if an unsupported verb was specified
	if((DWORD)pici->lpVerb > IDM_LAST)
		return E_INVALIDARG;

	switch(LOWORD(pici->lpVerb))
	{
		case IDM_PROPERTIES:
			// If a file in encrypted/decrypted view is selected then fall through
			if(!m_uItemCount)
			{
				if(PasswordPrompt(SAFE_PROP))
					DoSafeProp(GetParent(pici->hwnd));

				break;
			}

		case IDM_FILE_PROPERTIES:
			if(PasswordPrompt(FILE_PROP))
				DoFileProp(GetParent(pici->hwnd));

			break;

		case IDM_EXPLORE:
			DoExplore(GetParent(pici->hwnd));
			break;

		case IDM_OPEN:
			DoOpen(GetParent(pici->hwnd), TRUE, TRUE);
			break;

		case IDM_SELECT_ALL:
			DoSelectAll(pici->hwnd);
			break;

		case IDM_INVERT_SELECTION:
			DoInvertSelection(pici->hwnd);
			break;

		case IDM_HELP_TOPICS:
			ShowHelp(FETHLP_INTRO);
			break;

		case IDM_ABOUT:
			{
				TCHAR szAbout[MAX_MSG_LEN], szComment[MAX_MSG_LEN];
				HICON hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_SAFE));
				LoadString(g_hInst, IDS_ABOUT_TEXT, szAbout, sizeof(szAbout));
				LoadString(g_hInst, IDS_COMMENT, szComment, sizeof(szComment));
				ShellAbout(GetFocus(), szAbout, szComment, hIcon);
				DestroyIcon(hIcon);
			}
			break;

		case IDM_DELETE:
			DoDelete();
			break;

		case IDM_DECRYPT:
			DoOpen(GetParent(pici->hwnd), FALSE, FALSE);
			break;

		case IDM_DECRYPT_VERIFY:
			DoOpen(GetParent(pici->hwnd), FALSE, TRUE);
			break;

		case IDM_CLOSE:
			::PostMessage(GetParent(pici->hwnd), WM_CLOSE, 0, 0);
			break;

		case IDM_ENCRYPT:
			DoEncrypt();
			break;

		case IDM_CLEAR:
			DoClear(pici->hwnd);
			break;

		case IDM_HIDE:
			ShowDecryptView();
			break;

		case IDM_DECRYPTED_VIEW:
			ShowDecryptView();
			break;

		case IDM_OPEN_DECRYPTED:
			OpenDecryptedFiles(GetParent(pici->hwnd));
			break;

		// File selection dialog for encrypting files
		case IDM_ENCRYPT_FILE:
			ShowEncryptFileDlg(GetParent(pici->hwnd));
			break;
	}

	return NOERROR; 
}


STDMETHODIMP CContextMenu::GetCommandString(UINT idCommand, UINT uFlags,
                   LPUINT lpReserved, LPSTR lpszName, UINT uMaxNameLen)
{
	return E_NOTIMPL;
}



// Private and utility methods
LPITEMIDLIST* CContextMenu::AllocPidlTable(DWORD dwEntries)
{
	LPITEMIDLIST *aPidls;

	dwEntries++;

	aPidls = (LPITEMIDLIST*)m_pMalloc->Alloc(dwEntries * sizeof(LPITEMIDLIST));
	if(aPidls)
		ZeroMemory(aPidls, dwEntries * sizeof(LPITEMIDLIST));

	return aPidls;
}


VOID CContextMenu::FreePidlTable(LPITEMIDLIST *aPidls)
{
	if(aPidls && m_pPidlMgr)
	{
		for(UINT i = 0; aPidls[i]; i++)
			m_pPidlMgr->Delete(aPidls[i]);

		m_pMalloc->Free(aPidls);
	}
}


BOOL CContextMenu::FillPidlTable(LPCITEMIDLIST *aPidls, UINT uItemCount)
{
	if(m_aPidls)
	{
		if(m_pPidlMgr)
		{
			for(UINT i = 0; i < uItemCount; i++)
				m_aPidls[i] = m_pPidlMgr->Copy(aPidls[i]);

			return TRUE;
		}
	}

	return FALSE;
}


BOOL CContextMenu::DoSelectAll(HWND hWnd)
{
	CShellView *pView = (CShellView*)GetViewInterface(hWnd);
	if(pView)
	{
		pView->SelectAll();
		pView->Release();
	}

	return TRUE;
}


BOOL CContextMenu::ShowDecryptView()
{
	g_SafeProp.bDecryptPane = !g_SafeProp.bDecryptPane;	

	CShellView *pView = g_pViewList->GetNextView(NULL);
	while(pView)
	{
		pView->ShowDecryptView();
		pView = g_pViewList->GetNextView(pView);
	}

	return TRUE;
}


BOOL CContextMenu::DoClear(HWND hWnd)
{
	CShellView *pView = g_pViewList->GetNextView(NULL);
	while(pView)
	{
		pView->ClearList();
		pView = g_pViewList->GetNextView(pView);
	}

	// Remove DECRYPTED items from "fileinfo"
	if(g_szStoragePath[0] != '\0')
		RemoveDecryptedContents(g_szStoragePath);

	return TRUE;
}



BOOL CContextMenu::DoInvertSelection(HWND hWnd)
{
	CShellView *pView = (CShellView*)GetViewInterface(hWnd);

	if(pView)
	{
		pView->InvertSelection();
		pView->Release();
	}

	return TRUE;
}


BOOL CContextMenu::DoExplore(HWND hWnd)
{
	LPITEMIDLIST      pidlFQ;
	SHELLEXECUTEINFO  sei;
	BOOL			  bRetVal;

	pidlFQ = m_psfParent->CreateFQPidl(m_aPidls[0]);

	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.fMask = SEE_MASK_IDLIST | SEE_MASK_CLASSNAME;
	sei.lpIDList = pidlFQ;
	sei.lpClass = TEXT("folder");
	sei.hwnd = hWnd;
	sei.nShow = SW_SHOWNORMAL;
	sei.lpVerb = TEXT("explore");

	bRetVal = ShellExecuteEx(&sei);

	m_pPidlMgr->Delete(pidlFQ);

	return bRetVal;
}


//	Called when a file in the decrypted view is selected for encryption
BOOL CContextMenu::DoEncrypt()
{
	if(!m_uItemCount)
		return FALSE;

	if(!PasswordPrompt(ENCRYPT))
		return FALSE;

	UINT nSelected = m_uItemCount;
	TCHAR szDestPath[MAX_PATH_LEN], *pBSlash = NULL;
	LPCTSTR lpszCurrLoc = NULL;
	EncryptStatus Stat;

	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam;
	memset(&EncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));
	InitStatus stat = InitEncryptParams(&EncryptParam);

	// If doing a renewal just return
	if(stat == RENEW || stat == NO_MATCHES)
	{
		DeinitEncryptParams(&EncryptParam);
		return TRUE;
	}

	if(stat == FAILED)
	{
		DeinitEncryptParams(&EncryptParam);
		return FALSE;
	}

	CreateAnimateDlg(GetFocus(), 1);
	g_bEncryptErrPrompt = TRUE;
	g_bReadErrPrompt	= TRUE;
	g_bFilterErrPrompt	= TRUE;

	while(nSelected--)
	{
		lpszCurrLoc = m_pPidlMgr->GetOriginalLocation(m_aPidls[nSelected]);
		pBSlash = strrchr(lpszCurrLoc, '\\');
		if(!pBSlash)
			break;

		// Get the path of the current active directory in the Safe. This will
		// be the directory where the file will be placed on encryption
		m_psfParent->GetPath(NULL, szDestPath, MAX_PATH_LEN);

		lstrcat(szDestPath, pBSlash);
		
		Stat = EncryptAndSignFile(&EncryptParam, lpszCurrLoc, szDestPath);
		if(Stat == SUCCESS)
		{
			// Check if this file is marked for encr/decr at logon/off. If it is then check
			// if its location in Safe has changed. This is bcos the file could have been
			// encrypted at some other location in Safe. Always do an update
			if(g_DecrAtLogonList->GetLocInSafe(lpszCurrLoc))
				g_DecrAtLogonList->SetLocInSafe(lpszCurrLoc, szDestPath);
			
			if(g_EncrAtLogoffList->GetLocInSafe(lpszCurrLoc))
				g_EncrAtLogoffList->SetLocInSafe(lpszCurrLoc, szDestPath);

			// Now remove the entry from the decrypted list and put it in the 
			// encrypted list
			m_psfParent->UpdateDecrItems(szDestPath, &m_aPidls[nSelected]);
		}
		else
			if(Stat == CANCEL)
				break;

	} // while(nSelected--)

	DestroyAnimateDlg();
	DeinitEncryptParams(&EncryptParam);
	return TRUE;
}


/*	Called to open the files shown in the decrypted view. Only files are shown
    in the decrypted view, no folders are shown.
*/
BOOL CContextMenu::OpenDecryptedFiles(HWND hWnd)
{
	if(!m_uItemCount)
		return FALSE;

	UINT nSelected = m_uItemCount;
	LPCTSTR lpszOrigLoc = NULL;
	TCHAR szFile[MAX_PATH];
	SHELLEXECUTEINFO sei;

	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize	= sizeof(sei);
	sei.hwnd	= hWnd;
	sei.nShow	= SW_SHOWNORMAL;
	sei.lpVerb	= TEXT("open");

	while(nSelected--)
	{
		m_psfParent->GetPath(m_aPidls[nSelected], szFile, MAX_PATH);
		lpszOrigLoc = m_pPidlMgr->GetOriginalLocation(m_aPidls[nSelected]);

		sei.fMask	 = 0;
		sei.lpIDList = 0;
		sei.lpClass	 = '\0';
		sei.lpFile	 = lpszOrigLoc;
		ShellExecuteEx(&sei);
	}

	return TRUE;
}


//	Called to select files for encryption from the 'File' menu
BOOL CContextMenu::ShowEncryptFileDlg(HWND hWnd)
{
	static TCHAR szStartDir[MAX_PATH_LEN];
	static BOOL bStartDirInit = FALSE;
	BOOL bOverwritePrompt = TRUE;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	UINT Action;

	OPENFILENAME ofn;
	TCHAR szSelectedFiles[SELECTED_FILES_SIZE];
	TCHAR szFilter[MAX_PATH] = FILE_FILTER;
	szSelectedFiles[0] = '\0';

	LPITEMIDLIST pidlStartDir;
	
	// Select the directory shown to the user for the first time, if not already selected
	if(!bStartDirInit)
	{
		SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidlStartDir);
		SHGetPathFromIDList(pidlStartDir, szStartDir);

		IMalloc *pMalloc;
		if(S_OK == SHGetMalloc(&pMalloc))
		{
		   pMalloc->Free(pidlStartDir);
   		   pMalloc->Release();
		}
		bStartDirInit = TRUE;
	}

	memset(&ofn, 0, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner	= hWnd;
	ofn.hInstance	= NULL;
	ofn.lpstrFilter	= szFilter;
	ofn.nFilterIndex = 1;

	// If only one file is seleted this contains the entire path of the file,
	// If multiple files are selected this contains the 'directory' followed
	// by all the files names, everything is NULL seperated. 
	// Terminated by 2 NULL's
	ofn.lpstrFile	= szSelectedFiles;
	ofn.nMaxFile	= sizeof(szSelectedFiles);
	ofn.lpstrInitialDir = szStartDir;
	ofn.lpstrTitle	= "Select file for Encryption";
	ofn.Flags		= OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY
					  | OFN_NODEREFERENCELINKS | OFN_NONETWORKBUTTON | OFN_PATHMUSTEXIST
					  | OFN_EXPLORER | OFN_ENABLEHOOK;
	ofn.lpfnHook    = (LPOFNHOOKPROC)EncryptHookProc;

	if(GetOpenFileName(&ofn))
	{
		if(!PasswordPrompt(ENCRYPT))
			return FALSE;

		TCHAR szDir[MAX_PATH_LEN];		// directory of the selected files
		TCHAR szDestDir[MAX_PATH_LEN];	// dir in the Safe
		TCHAR szDestPath[MAX_PATH_LEN];	// complete path of the destination
		TCHAR szFilePath[MAX_PATH_LEN];	// file to be encrypted
		TCHAR *pStr = NULL, *pBSlash = NULL;
		TCHAR *pCurrSel = &szSelectedFiles[ofn.nFileOffset]; // pointer to file within all the selected files

		EncryptStatus Stat;

		CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam;
		memset(&EncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));
		InitStatus stat = InitEncryptParams(&EncryptParam);

		// Doing a renewal, return
		if(stat == RENEW  || stat == NO_MATCHES)
		{
			DeinitEncryptParams(&EncryptParam);
			return TRUE;
		}

		if(stat == FAILED)
		{
			DeinitEncryptParams(&EncryptParam);
			return FALSE;
		}

		strncpy(szDir, szSelectedFiles, ofn.nFileOffset);
		if(szDir[ofn.nFileOffset - 1] == '\0')
			SmartAppendBackslash(szDir);	// multiple files were selected
		else
			szDir[ofn.nFileOffset] = '\0';	// only one selected

		// Check if file(s) in the Safe directory are being encrypted, if so give error
		if(!_strnicmp(szDir, g_szInstallDir, lstrlen(g_szInstallDir)))
		{
			DisplayMessage(GetFocus(), IDS_SAFE_DIR, MB_OK | MB_ICONERROR);
			DeinitEncryptParams(&EncryptParam);
			return FALSE;
		}

		// Get the path of the current active directory in the Safe. This will be the directory 
		// where the file will be placed on encryption
		m_psfParent->GetPath(NULL, szDestDir, MAX_PATH_LEN);

		CreateAnimateDlg(GetFocus(), 1);
		g_bEncryptErrPrompt = TRUE;
		g_bReadErrPrompt	= TRUE;
		g_bFilterErrPrompt	= TRUE;

		pCurrSel = &szSelectedFiles[ofn.nFileOffset];
		do
		{
			pStr = strchr(pCurrSel, '\0');
			if(pStr && *(pStr + 1) == '\0')
			{
				// Last file, 2 NULL's
				lstrcpy(szFilePath, szDir);
				lstrcat(szFilePath, pCurrSel);
				pCurrSel = NULL;
			}
			else
			{
				lstrcpy(szFilePath, szDir);
				int iLen = lstrlen(szFilePath);

				for(int i = 0; pCurrSel[i] != '\0'; i++)
					szFilePath[iLen + i] = pCurrSel[i];

				szFilePath[iLen + i] = '\0';
				pCurrSel = &pCurrSel[i + 1]; // point to next file
			}

			// Construct the destination path
			pBSlash = strrchr(szFilePath, '\\');
			lstrcpy(szDestPath, szDestDir);
			lstrcat(szDestPath, pBSlash);

			Action = IDB_YESTOALL;

			// Check if destination file exists
			hFind = FindFirstFile(szDestPath, &wfd);

			if(hFind != INVALID_HANDLE_VALUE)
			{
				// File already exists.
				FindClose(hFind);

				if(bOverwritePrompt)
					Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_REPLACE), GetActiveWindow(), 
									   (DLGPROC)ReplaceConfirm, (LONG)szDestPath);
				else
					Action = IDB_YESTOALL;

				switch(Action)
				{
					case IDB_YESTOALL:
						bOverwritePrompt = FALSE;  // don't prompt now on
						// Fall through code
					case IDOK:
						// Delete the original destination file as we are doing a replace
						DeleteFile(szDestPath); // not checking the err here as the 
						break;					// file might not actually exist

					case IDCANCEL:
						break;

					case IDB_NO:
						break;
				}
			}

			if(Action == IDCANCEL)
				break;

			if(Action == IDB_YESTOALL || Action == IDOK)
			{
				Stat = EncryptAndSignFile(&EncryptParam, szFilePath, szDestPath);

				if(Stat == CANCEL)
					break;
			}

			lstrcpy(szStartDir, szFilePath);
			pBSlash = strrchr(szStartDir, '\\');
			*pBSlash = NULL;
		}
		while(pCurrSel);

		DestroyAnimateDlg();
		DeinitEncryptParams(&EncryptParam);
	}  // if(GetOpenFileName(&ofn))

	return TRUE;
}


/*	'bRunApp' will indicate whether to launch the associated application.
	this also indicates how a folder is handled. If 'TRUE' then open the
	folder else decrypt/verify the folder
	'bVerify' will indicate whether to verify the file/folder
*/
BOOL CContextMenu::DoOpen(HWND hWnd, BOOL bRunApp, BOOL bVerify)
{
	if(!m_uItemCount)
		return FALSE;

	LPITEMIDLIST pidlFQ;
	SHELLEXECUTEINFO sei;
	BOOL fReturn = FALSE;
	UINT nSelected = m_uItemCount;
	LPCTSTR lpszOrigLoc = NULL;
	TCHAR szFile[MAX_PATH_LEN];

	g_bPrompt = TRUE;  // Always set this to TRUE initially

	// 'nSelected' will be 0 if all are 'folders'
	while(nSelected)
	{
		if(!m_pPidlMgr->IsFolder(m_aPidls[nSelected - 1]))
			break;
		
		nSelected--;
	}

	// If a file is selected or if the option is to decrypt then ask password
	if(nSelected != 0 || !bRunApp)
		if(!PasswordPrompt(DECRYPT))
			return FALSE;

	// If a file is selected or if the option is to decrypt then show animation
	if(nSelected != 0 || !bRunApp)
		CreateAnimateDlg(GetFocus(), 0);

	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize = sizeof(sei);
	sei.hwnd = hWnd;
	sei.nShow = SW_SHOWNORMAL;
	sei.lpVerb = TEXT("open");

	nSelected = m_uItemCount;

	DecryptStatus Stat;

	while(nSelected--)
	{
		m_psfParent->GetPath(m_aPidls[nSelected], szFile, MAX_PATH_LEN);

		if(m_pPidlMgr->IsFolder(m_aPidls[nSelected]))
		{
			if(bRunApp)
			{
				pidlFQ = m_psfParent->CreateFQPidl(m_aPidls[nSelected]);
				sei.fMask = SEE_MASK_IDLIST | SEE_MASK_CLASSNAME;
				sei.lpIDList = pidlFQ;
				sei.lpClass = TEXT("folder");
				fReturn = ShellExecuteEx(&sei);
				m_pPidlMgr->Delete(pidlFQ);
			}
			else
			{
				Stat = DecryptAll(szFile);	// Decrypt the folder
				if(Stat == DECR_OK)
				{
					// Notify the explorer that the directory is removed so
					// a refresh can be done. Note: the directory is not
					// physically deleted from the Safe now as it
					// contains the 'fileinfo' files containing information
					// of the recently decrypted files
					pidlFQ = m_psfParent->CreateFQPidl(m_aPidls[nSelected]);
					SHChangeNotify(SHCNE_RMDIR, SHCNF_IDLIST, pidlFQ, NULL);
					m_psfParent->NotifyViews(SHCNE_RMDIR, m_aPidls[nSelected], NULL);
					m_pPidlMgr->Delete(pidlFQ);
				}
				else
					if(Stat == DECR_CANCEL)
					{
						DestroyAnimateDlg();
						return FALSE;
					}
			}
		}
		else
		{
			lpszOrigLoc = m_pPidlMgr->GetOriginalLocation(m_aPidls[nSelected]);
			SetAnimateDlgText(szFile, lpszOrigLoc);
			Stat = DecryptAndVerifyFile(szFile, lpszOrigLoc, bVerify);
			if(Stat == DECR_OK)
			{
				// Update the view. The decrypted file should show up in the 
				// list view showing decrypted files
				m_psfParent->UpdateEncrItems(&m_aPidls[nSelected], 1);

				// Open the file by launching the application only if called for "opening"
				if(bRunApp)
				{
					sei.fMask	 = 0;
					sei.lpIDList = 0;
					sei.lpClass	 = '\0';
					sei.lpFile	 = lpszOrigLoc;
					fReturn = ShellExecuteEx(&sei);
				}
			}
			else
				if(Stat == DECR_CANCEL)
				{
					DestroyAnimateDlg();
					return FALSE;
				}
		}
	}	// while(nSelected--)

	DestroyAnimateDlg();
	return ( (Stat == DECR_OK) ? TRUE : FALSE);
}


STDMETHODIMP CContextMenu::DoDelete(VOID)
{
	TCHAR szText[MAX_MSG_LEN], szCaption[MAX_MSG_LEN];
	LoadString(g_hInst, IDS_DELETE_PROMPT, szText, sizeof(szText));
	LoadString(g_hInst, IDS_DELETE_CONFIRM, szCaption, sizeof(szCaption));

	if(MessageBox(GetFocus(), szText, szCaption, MB_YESNO | MB_ICONQUESTION) == IDYES)
		return m_psfParent->DeleteItems(m_aPidls, m_uItemCount);

	return S_OK;
}



BOOL CContextMenu::DoSafeProp(HWND hWnd)
{
	PROPSHEETPAGE psp[4];    
	PROPSHEETHEADER psh;

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

    psh.dwSize = sizeof(PROPSHEETHEADER);    
	psh.dwFlags = PSH_PROPSHEETPAGE | PSH_USECALLBACK;
    psh.hwndParent = hWnd;    
	psh.hInstance = g_hInst;    
	psh.pszIcon = NULL;
    psh.pszCaption = (LPSTR) "Properties";
    psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
	psh.nStartPage		= 0;
    psh.ppsp = (LPCPROPSHEETPAGE) &psp;
	psh.pfnCallback = RemoveContextHelpProc;

	return PropertySheet(&psh);
}


BOOL CContextMenu::DoFileProp(HWND hWnd)
{
	PROPSHEETPAGE psp[1];   
	PROPSHEETHEADER psh;
	TCHAR szText[MAX_MSG_LEN], szCaption[MAX_MSG_LEN], *pFileName = NULL;

	// No items selected, comes here when the Properties button is clicked 
	// when neither the 'Safe' nor any File/Folder has the focus, or the 
	// 'Decrypted' view has focus
	if(!m_uItemCount || !g_bEncryptViewActive)	
		return TRUE;

	m_psfParent->GetPath(m_aPidls[0], szText, MAX_MSG_LEN);
	pFileName = strrchr(szText, '\\');
	if(!pFileName)
		return FALSE;
	
	pFileName += 1;

	strcpy(&szText[lstrlen(szText) + 1], m_pPidlMgr->GetOriginalLocation(m_aPidls[0]));

	lstrcpy(szCaption, pFileName);
	lstrcat(szCaption, " Properties");

	psp[0].dwSize = sizeof(PROPSHEETPAGE);    
	psp[0].dwFlags = PSP_USETITLE | PSP_HASHELP;
	psp[0].hInstance = g_hInst;
	psp[0].pszIcon = NULL;
	psp[0].pszTitle = "General";
	psp[0].lParam = (LONG)this;

	psh.dwSize = sizeof(PROPSHEETHEADER);    
	psh.dwFlags = PSH_PROPSHEETPAGE | PSH_USECALLBACK;
	psh.hwndParent = hWnd;    
	psh.hInstance = g_hInst;    
	psh.pszIcon = NULL;
	psh.nPages = sizeof(psp) / sizeof(PROPSHEETPAGE);
	psh.nStartPage = 0;
	psh.ppsp = (LPCPROPSHEETPAGE) &psp;    
	psh.pszCaption = szCaption;
	psh.pfnCallback = RemoveContextHelpProc;

	for(UINT i = 0; i < m_uItemCount; i++)
		if(!m_pPidlMgr->IsFolder(m_aPidls[i]))
			break;

	if(i == m_uItemCount)	// All selected items are folders
	{
		//Folder properties ??
		//psp[0].pszTemplate = MAKEINTRESOURCE(IDD_FOLDER_PROP);
		//psp[0].pfnDlgProc = (DLGPROC)FolderProperties;    
	}
	else
	{
		// Files/Folders selected. If only one file is selected show Single File Properties
		if(m_uItemCount == 1)
		{
			psp[0].pszTemplate = MAKEINTRESOURCE(IDD_FILE_PROP);
			psp[0].pfnDlgProc = (DLGPROC)FileProperties;
		}
		else
		{
			// Show multiple selection property
			psp[0].pszTemplate = MAKEINTRESOURCE(IDD_MULTI_SEL);
			psp[0].pfnDlgProc = (DLGPROC)MultipleFileProperties;    
			psh.pszCaption = "Properties";
		}

		PropertySheet(&psh);
	}
	
	return TRUE;
}



UINT CContextMenu::InsertBackgroundEncryptItems(HMENU hMenu, UINT indexMenu, UINT idCmdFirst)
{
	HMENU          hPopup;
	TCHAR          szText[MAX_MSG_LEN];
	MENUITEMINFO   mii;

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	// Add the View submenu
	hPopup = CreatePopupMenu();

	if(hPopup)
	{
		AddViewMenuItems(hPopup, idCmdFirst, -1, TRUE);

		LoadString(g_hInst, IDS_VIEW, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
		mii.wID = idCmdFirst + IDM_VIEW;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		mii.hSubMenu = hPopup;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// Only add a separator if needed
		mii.fMask = MIIM_TYPE;
		GetMenuItemInfo(hMenu, indexMenu, TRUE, &mii);
		if(!(mii.fType & MFT_SEPARATOR))
		{
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_ID | MIIM_TYPE;
			mii.wID = 0;
			mii.fType = MFT_SEPARATOR;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
	}

	// Add the Icons submenu
	hPopup = CreatePopupMenu();
	if(hPopup)
	{
		AddIconsMenuItems(TRUE, hPopup, idCmdFirst, -1, TRUE);

		LoadString(g_hInst, IDS_ARRANGE_ICONS, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
		mii.wID = idCmdFirst + IDM_ARRANGE_ICONS;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		mii.hSubMenu = hPopup;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// Only add a separator if needed
		mii.fMask = MIIM_TYPE;
		GetMenuItemInfo(hMenu, indexMenu, TRUE, &mii);
		if(!(mii.fType & MFT_SEPARATOR))
		{
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_ID | MIIM_TYPE;
			mii.wID = 0;
			mii.fType = MFT_SEPARATOR;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
	}

	LoadString(g_hInst, IDS_PROPERTIES, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_PROPERTIES;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
	
	return indexMenu;
}


UINT CContextMenu::InsertBackgroundDecryptItems(HMENU hMenu, UINT indexMenu, UINT idCmdFirst)
{
	HMENU        hPopup;
	TCHAR        szText[MAX_MSG_LEN];
	MENUITEMINFO mii;

	HWND hwndDecr = GetFocus();

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	// Add the View submenu
	hPopup = CreatePopupMenu();
	if(hPopup)
	{
		AddViewMenuItems(hPopup, idCmdFirst, -1, TRUE);

		LoadString(g_hInst, IDS_VIEW, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
		mii.wID = idCmdFirst + IDM_VIEW;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		mii.hSubMenu = hPopup;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// Only add a separator if needed
		mii.fMask = MIIM_TYPE;
		GetMenuItemInfo(hMenu, indexMenu, TRUE, &mii);
		if(!(mii.fType & MFT_SEPARATOR))
		{
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_ID | MIIM_TYPE;
			mii.wID = 0;
			mii.fType = MFT_SEPARATOR;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
	}

	// Add the Icons submenu
	hPopup = CreatePopupMenu();
	if(hPopup)
	{
		AddIconsMenuItems(FALSE, hPopup, idCmdFirst, -1, TRUE);

		LoadString(g_hInst, IDS_ARRANGE_ICONS, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE | MIIM_SUBMENU;
		mii.wID = idCmdFirst + IDM_ARRANGE_ICONS;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		mii.hSubMenu = hPopup;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// Only add a separator if needed
		mii.fMask = MIIM_TYPE;
		GetMenuItemInfo(hMenu, indexMenu, TRUE, &mii);
		if(!(mii.fType & MFT_SEPARATOR))
		{
			ZeroMemory(&mii, sizeof(mii));
			mii.cbSize = sizeof(mii);
			mii.fMask = MIIM_ID | MIIM_TYPE;
			mii.wID = 0;
			mii.fType = MFT_SEPARATOR;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
	}

	LoadString(g_hInst, IDS_CLEAR, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_CLEAR;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;

	if(ListView_GetItemCount(hwndDecr))
		mii.fState = MFS_ENABLED;
	else
		mii.fState = MFS_DISABLED;

	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	// Seperator
	mii.fMask = MIIM_ID | MIIM_TYPE;
	mii.wID = 0;
	mii.fType = MFT_SEPARATOR;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	LoadString(g_hInst, IDS_HIDE, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_HIDE;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	return indexMenu;
}



UINT CContextMenu::InsertDecryptViewItems(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT uFlags)
{
	MENUITEMINFO   mii;
	TCHAR          szText[MAX_MSG_LEN];

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_OPEN_DECRYPTED;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;
	mii.fState = MFS_ENABLED | MFS_DEFAULT;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
	
	LoadString(g_hInst, IDS_ENCRYPT, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_ENCRYPT;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	return indexMenu;
}


UINT CContextMenu::InsertEncryptViewItems(HMENU hMenu, UINT indexMenu, UINT idCmdFirst, UINT uFlags)
{
	MENUITEMINFO mii;
	TCHAR        szText[MAX_MSG_LEN];
	BOOL         fExplore = uFlags & CMF_EXPLORE;
	DWORD        dwAttr = SFGAO_FOLDER;

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	m_psfParent->GetAttributesOf(m_uItemCount, (LPCITEMIDLIST*)m_aPidls, &dwAttr);

	// Only add the Open and Explore items if all items are folders.
	if(dwAttr & SFGAO_FOLDER)
	{
		if(fExplore)
		{
			LoadString(g_hInst, IDS_EXPLORE, szText, sizeof(szText));
			mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
			mii.wID = idCmdFirst + IDM_EXPLORE;
			mii.fType = MFT_STRING;
			mii.dwTypeData = szText;
			mii.fState = MFS_ENABLED | MFS_DEFAULT;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

			LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
			mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
			mii.wID = idCmdFirst + IDM_OPEN;
			mii.fType = MFT_STRING;
			mii.dwTypeData = szText;
			mii.fState = MFS_ENABLED;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
		else
		{
			LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
			mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
			mii.wID = idCmdFirst + IDM_OPEN;
			mii.fType = MFT_STRING;
			mii.dwTypeData = szText;
			mii.fState = MFS_ENABLED | MFS_DEFAULT;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

			LoadString(g_hInst, IDS_EXPLORE, szText, sizeof(szText));
			mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
			mii.wID = idCmdFirst + IDM_EXPLORE;
			mii.fType = MFT_STRING;
			mii.dwTypeData = szText;
			mii.fState = MFS_ENABLED;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
		}
	}
	else
	{
		LoadString(g_hInst, IDS_OPEN, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
		mii.wID = idCmdFirst + IDM_OPEN;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED | MFS_DEFAULT;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
	}

	// Insert a seperator
	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);
	mii.fMask = MIIM_ID | MIIM_TYPE;
	mii.wID = 0;
	mii.fType = MFT_SEPARATOR;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	LoadString(g_hInst, IDS_DECRYPT, szText, sizeof(szText));
	mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
	mii.wID = idCmdFirst + IDM_DECRYPT;
	mii.fType = MFT_STRING;
	mii.dwTypeData = szText;
	mii.fState = MFS_ENABLED;
	InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

	// Check if any file among those selected is signed
	for(UINT i = 0; i < m_uItemCount; i++)
	{
		m_psfParent->GetPath(m_aPidls[i], szText, MAX_MSG_LEN);

		//  For a folder add decrypt_verify option
		if(m_pPidlMgr->IsFolder(m_aPidls[i]) || IsSigned(szText))
		{
			LoadString(g_hInst, IDS_DECRYPT_VERIFY, szText, sizeof(szText));
			mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
			mii.wID = idCmdFirst + IDM_DECRYPT_VERIFY;
			mii.fType = MFT_STRING;
			mii.dwTypeData = szText;
			mii.fState = MFS_ENABLED;
			InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
			break;
		}
	}

	// No 'Properties' and 'Delete' menu item if all folders selected
	BOOL bAllFolders = TRUE;
	for(i = 0; i < m_uItemCount; i++)
	{
		if(!m_pPidlMgr->IsFolder(m_aPidls[i]))
		{
			bAllFolders = FALSE;
			break;
		}
	}

	if(!bAllFolders)
	{
		// Insert a seperator
		ZeroMemory(&mii, sizeof(mii));
		mii.cbSize = sizeof(mii);
		mii.fMask = MIIM_ID | MIIM_TYPE;
		mii.wID = 0;
		mii.fType = MFT_SEPARATOR;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// The Delete menu item
		LoadString(g_hInst, IDS_DELETE, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
		mii.wID = idCmdFirst + IDM_DELETE;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		// Insert a seperator
		ZeroMemory(&mii, sizeof(mii));
		mii.cbSize = sizeof(mii);
		mii.fMask = MIIM_ID | MIIM_TYPE;
		mii.wID = 0;
		mii.fType = MFT_SEPARATOR;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);

		LoadString(g_hInst, IDS_PROPERTIES, szText, sizeof(szText));
		mii.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
		mii.wID = idCmdFirst + IDM_FILE_PROPERTIES;
		mii.fType = MFT_STRING;
		mii.dwTypeData = szText;
		mii.fState = MFS_ENABLED;
		InsertMenuItem(hMenu, indexMenu++, TRUE, &mii);
	}
	
	return indexMenu;
}


void CContextMenu::GetSafeLocation(UINT nIndex, TCHAR *lpszPath)
{
	m_psfParent->GetPath(m_aPidls[nIndex], lpszPath, MAX_PATH);
}

LPCTSTR CContextMenu::GetOriginalLocation(UINT nIndex)
{
	return m_pPidlMgr->GetOriginalLocation(m_aPidls[nIndex]);
}
   

DWORD CContextMenu::GetOriginalSize(UINT nIndex)
{
	return m_pPidlMgr->GetOriginalSize(m_aPidls[nIndex]);
}


FILETIME CContextMenu::GetCreationDate(UINT nIndex)
{
	return m_pPidlMgr->GetCreationDate(m_aPidls[nIndex]);
}


UINT CContextMenu::GetSelItemCount()
{
	return m_uItemCount;
}
