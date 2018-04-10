// CDataObject implementation.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "DataObj.h"
#include "resource.h"
#include "dlgprocs.h"


CDataObject::CDataObject(CShellFolder *psfParent, LPCITEMIDLIST *aPidls, UINT uItemCount)
{
	g_DllRefCount++;

	m_uItemCount = 0;

	m_psfParent = psfParent;
	
	if(m_psfParent)
		m_psfParent->AddRef();

	m_ObjRefCount = 1;

	m_aPidls = NULL;
	SHGetMalloc(&m_pMalloc);
	if(!m_pMalloc)
	{
		delete this;
		return;
	}

	m_pPidlMgr = new CPidlMgr();

	m_uItemCount = uItemCount;

	AllocPidlTable(uItemCount);
	if(m_aPidls)
		FillPidlTable(aPidls, uItemCount);
	
	m_cfPrivateData = RegisterClipboardFormat(CFSTR_VSSAFE);

	m_cFormatEtc = 2;
	m_pFormatEtc = new FORMATETC[m_cFormatEtc];
	SETDefFormatEtc(m_pFormatEtc[0], m_cfPrivateData, TYMED_HGLOBAL);
	SETDefFormatEtc(m_pFormatEtc[1], CF_HDROP, TYMED_HGLOBAL);

	m_iCurrent		= 0;
	m_hDropTarget	= 0;
	m_bDecrypted	= FALSE;
}


CDataObject::~CDataObject()
{
	if(m_psfParent)
		m_psfParent->Release();

	g_DllRefCount--;

	// Make sure the pidls are freed
	if(m_aPidls && m_pMalloc)
		FreePidlTable();
	
	if(m_pPidlMgr)
		delete m_pPidlMgr;

	if(m_pMalloc)
		m_pMalloc->Release();

	delete [] m_pFormatEtc;
}


// IUnknown Implementation
STDMETHODIMP CDataObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = (LPUNKNOWN)(LPCONTEXTMENU)this;
	else if(IsEqualIID(riid, IID_IDataObject))
		*ppReturn = (LPDATAOBJECT)this;
	else if(IsEqualIID(riid, IID_IEnumFORMATETC))
		*ppReturn = (LPENUMFORMATETC)this;
    
	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             



STDMETHODIMP_(DWORD) CDataObject::AddRef()
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CDataObject::Release()
{
	if(--m_ObjRefCount == 0)
		delete this;

  	return m_ObjRefCount;
}

 
// IDataObject Implementation
STDMETHODIMP CDataObject::GetData(LPFORMATETC pFE, LPSTGMEDIUM pStgMedium)
{
	// Resetting here as sometimes Enum::Reset isnt called
	m_iCurrent = 0;
	HGLOBAL hGlobal;

	if(pFE->cfFormat == m_cfPrivateData)
	{
		hGlobal = GlobalAlloc(GHND | GMEM_SHARE, sizeof(DROPSRCDATA));
		if(hGlobal == NULL)
			return E_OUTOFMEMORY;

		LPDROPSRCDATA pData = (LPDROPSRCDATA)GlobalLock(hGlobal);
		pData->uItemCount = m_uItemCount;
		pData->aPidls = m_aPidls;
		GlobalUnlock(hGlobal);

		pStgMedium->hGlobal = hGlobal;
		pStgMedium->pUnkForRelease = NULL;
		pStgMedium->tymed = TYMED_HGLOBAL;

		return S_OK;
    }
	else
		if(pFE->cfFormat == CF_HDROP)
		{
			HRESULT hr = E_FAIL;

			// If user has released the mouse then do the decryption. If not then store the current
			// mouse co-ordinates. These are used to determine where the drop is being done, either
			// on the Windows desktop, or explorer tree view, or on some application which supports
			// the CF_HDROP format. 
			HWND hCapture = GetCapture();
			if(hCapture)
			{
				POINT pt;
				if(GetCursorPos(&pt))
				{
					m_hDropTarget = WindowFromPoint(pt);
					if(m_hDropTarget)
					{
						TCHAR szDropTarget[MAX_PATH_LEN];

						// If the directory on which drop is being done is \progra~1\verisign\safe\<username>, 
						// then disable drop out of Safe for this data
						hr = GetDropTargetPath(szDropTarget);
						if(hr == S_OK)
						{
							if(!_strnicmp(szDropTarget, g_szStoragePath, lstrlen(g_szStoragePath)))
								return E_OUTOFMEMORY;
						}
					}
				}
				
				HGLOBAL hGlobal = CreateDragData();
				if(!hGlobal)
					return E_OUTOFMEMORY;

				pStgMedium->hGlobal = hGlobal;
				pStgMedium->pUnkForRelease = NULL;
				pStgMedium->tymed = TYMED_HGLOBAL;
			}
			else
			{
				// GetData() is called multiple times, do decryption only once
				if(!m_bDecrypted)
				{
					TCHAR szDropTarget[MAX_PATH_LEN], szPath[MAX_PATH_LEN];
					hr = GetDropTargetPath(szDropTarget);

					if(!strnicmp(szDropTarget, g_szStoragePath, lstrlen(g_szStoragePath)))
						return E_OUTOFMEMORY;

					// Do the decryption
					if(hr == S_OK)
					{
						CreateAnimateDlg(GetFocus(), 0);

						DWORD dwFattr;
						BOOL bDecryptPrompt = TRUE;
						for(UINT i = 0; i < m_uItemCount; i++)
						{
							m_psfParent->GetPath(m_aPidls[i], szPath, MAX_PATH_LEN);
							dwFattr = GetFileAttributes(szPath);

							if(!(dwFattr & FILE_ATTRIBUTE_DIRECTORY))
							{
								if(DecryptDragged(szPath, szDropTarget, m_pPidlMgr->GetOriginalLocation(m_aPidls[i]), &bDecryptPrompt) == DECR_CANCEL)
									break;
							}
						}

						m_bDecrypted = TRUE;
						DestroyAnimateDlg();

						// Refresh the views now as files have been decrypted and the 
						// 'fileinfo' file has been modified
						RefreshAllViews(FALSE);
					}
				}		// if(!m_bDecrypted)
				else
					hr = S_OK;

				hGlobal = CreateDragData();
				if(!hGlobal)
					return E_OUTOFMEMORY;

				pStgMedium->hGlobal = hGlobal;
				pStgMedium->pUnkForRelease = NULL;
				pStgMedium->tymed = TYMED_HGLOBAL;
			} // cursor released
							
			if(hr != S_OK && hGlobal)
				GlobalFree(hGlobal);

			return hr;
		}	// if(pFE->cfFormat == CF_HDROP)
   
   return E_OUTOFMEMORY;
}



HGLOBAL CDataObject::CreateDragData(VOID)
{
	UINT nDropFiles = 0;
	TCHAR szFile[MAX_PATH_LEN], *pStr = NULL;
	HGLOBAL hGlobal = NULL;
	DROPFILES *pData = NULL;
	DWORD dwFattr;

	// Construct the 'hGlobal' for our data. 
	// 'm_bDecrypted' is TRUE means GetData() has already been called, in this case return only
	// those files paths which have been successfully decrypted.
	if(m_bDecrypted)
	{
		// First get the amount of space to allocate
		for(UINT i = 0; i < m_uItemCount; i++)
		{
			m_psfParent->GetPath(m_aPidls[i], szFile, MAX_PATH_LEN);

			dwFattr = GetFileAttributes(szFile);

			if(!(dwFattr & FILE_ATTRIBUTE_DIRECTORY))
			{
				// Check if the 'fileinfo' file says that this file has been successfully decrypted
				TCHAR szFileInfo[MAX_PATH_LEN];
				lstrcpy(szFileInfo, szFile);
				pStr = strrchr(szFileInfo, '\\');
				lstrcpy(pStr + 1, "fileinfo");

				pStr = strrchr(szFile, '\\') + 1; // point to filename
				FileStatus Status = (FileStatus)GetPrivateProfileInt(pStr, "Status", DELETED, szFileInfo);
				if(Status == DECRYPTED)
					nDropFiles += lstrlen(szFile) + 1; // Add one for NULL terminator
			}
		}

		if(!nDropFiles)
			return FALSE;

		nDropFiles++;	// Increment because last file is double NULL terminated

		hGlobal = GlobalAlloc(GHND | GMEM_SHARE, sizeof(DROPFILES) + nDropFiles);
		if(hGlobal == NULL)
			return NULL;

		pData = (DROPFILES *)GlobalLock(hGlobal);
		memset(pData, 0, sizeof(DROPFILES) + nDropFiles);
		pData->pFiles = sizeof(DROPFILES);

		pStr = (char *)pData + sizeof(DROPFILES);

		// Now copy the file paths
		for(i = 0; i < m_uItemCount; i++)
		{
			m_psfParent->GetPath(m_aPidls[i], szFile, MAX_PATH_LEN);

			dwFattr = GetFileAttributes(szFile);

			if(!(dwFattr & FILE_ATTRIBUTE_DIRECTORY))
			{
				// Check if the 'fileinfo' file says that this file has been successfully decrypted
				TCHAR szFileInfo[MAX_PATH_LEN], *pBSlash = NULL;
				lstrcpy(szFileInfo, szFile);
				pBSlash = strrchr(szFileInfo, '\\');
				lstrcpy(pBSlash + 1, "fileinfo");

				pBSlash = strrchr(szFile, '\\') + 1; // point to filename
				FileStatus Status = (FileStatus)GetPrivateProfileInt(pBSlash, "Status", DELETED, szFileInfo);
				if(Status == DECRYPTED)
				{
					lstrcpy(pStr, szFile);
					pStr += lstrlen(szFile) + 1;	// Skip the NULL terminator
				}
			}
		}
	}
	else
	{
		// First get the amount of space to allocate
		for(UINT i = 0; i < m_uItemCount; i++)
		{
			m_psfParent->GetPath(m_aPidls[i], szFile, MAX_PATH_LEN);
			dwFattr = GetFileAttributes(szFile);

			if(!(dwFattr & FILE_ATTRIBUTE_DIRECTORY))
				nDropFiles += lstrlen(szFile) + 1; // Add one for NULL terminator
		}

		nDropFiles++;	// Increment because last file is double NULL terminated

		hGlobal = GlobalAlloc(GHND | GMEM_SHARE, sizeof(DROPFILES) + nDropFiles);
		if(hGlobal == NULL)
			return NULL;

		pData = (DROPFILES *)GlobalLock(hGlobal);
		memset(pData, 0, sizeof(DROPFILES) + nDropFiles);
		pData->pFiles = sizeof(DROPFILES);

		pStr = (char *)pData + sizeof(DROPFILES);

		// Now copy the file paths
		for(i = 0; i < m_uItemCount; i++)
		{
			m_psfParent->GetPath(m_aPidls[i], szFile, MAX_PATH_LEN);
			dwFattr = GetFileAttributes(szFile);

			if(!(dwFattr & FILE_ATTRIBUTE_DIRECTORY))
			{
				lstrcpy(pStr, szFile);
				pStr += lstrlen(szFile) + 1;	// Skip the NULL terminator
			}
		}
	}

	GlobalUnlock(hGlobal);
	return hGlobal;
}


HRESULT CDataObject::GetDropTargetPath(LPSTR lpszDropTarget)
{
	// Check if desktop window is the drop target
	if(IsDesktopWindow(m_hDropTarget))
	{
		LPITEMIDLIST pidl;
		SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
		SHGetPathFromIDList(pidl, lpszDropTarget);
		m_pMalloc->Free(pidl);
		return S_OK;
	}
	else
	{
		// Check if a tree is the target of drop
		if(GetTreePath(m_hDropTarget, lpszDropTarget))
			return S_OK;
		else
		{
			// Drag out of Safe to some application which supports CF_HDROP, in this case we 
			// are not able to find out the destination path where the decrypted file will be
			// placed, so as of now not supporting this option
			lstrcpy(lpszDropTarget, "OriginalLocation");
			return E_FAIL;
		}
	}
}



STDMETHODIMP CDataObject::GetDataHere (LPFORMATETC pFE, LPSTGMEDIUM pStgMedium)
{
	return E_NOTIMPL;
}



STDMETHODIMP CDataObject::QueryGetData(LPFORMATETC pFE)
{
	BOOL fReturn = FALSE;

	// Resetting here as sometimes Enum::Reset isnt called
	m_iCurrent = 0;

	// Check the aspects we support. Implementations of this object will only
	// support DVASPECT_CONTENT.

	if(!(DVASPECT_CONTENT & pFE->dwAspect))
		return DV_E_DVASPECT;

	if((pFE->cfFormat == m_cfPrivateData) && (pFE->tymed & TYMED_HGLOBAL))
		return S_OK;

	if(pFE->cfFormat == CF_HDROP)
		fReturn |= TYMED_HGLOBAL & pFE->tymed;

	return (fReturn ? S_OK : DV_E_TYMED);
}



STDMETHODIMP CDataObject::GetCanonicalFormatEtc(LPFORMATETC pFEIn, LPFORMATETC pFEOut)
{
	return E_INVALIDARG;
}


STDMETHODIMP CDataObject::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppEFE)
{
	// Resetting here as sometimes Enum::Reset isnt called
	m_iCurrent = 0;

	// Don't allow enumeration if the drag has been started from the view showing decrypted 
	// files, bcos don't want to support drag out of the decrypted view to one of Explorer 
	// views, however drag from decrypted view to encrypted view is supported

	// Also not supporting dragging folders out of the Safe as it is difficult in the case 
	// in which the folder already exists on the destination, in this case Windows also puts 
	// up the overwrite dialog after we do the decryption and put our overwrite dialog 

	*ppEFE = NULL;

	for(UINT i = 0; i < m_uItemCount; i++)
	{
		if(!m_pPidlMgr->IsFolder(m_aPidls[i]))
			break;
	}

	// All folders or drag from decryted view
	if(i == m_uItemCount || m_pPidlMgr->GetStatus(m_aPidls[0]) == DECRYPTED)
		return E_NOTIMPL;
	else
	{
		if(DATADIR_GET == dwDirection)
		   return this->QueryInterface(IID_IEnumFORMATETC, (LPVOID*)ppEFE);
	}

	return E_NOTIMPL;
}



STDMETHODIMP CDataObject::SetData(LPFORMATETC pFE, LPSTGMEDIUM pStgMedium, BOOL fRelease)
{
	return E_NOTIMPL;
}


STDMETHODIMP CDataObject::DAdvise(LPFORMATETC pFE, DWORD advf, IAdviseSink *ppAdviseSink, LPDWORD pdwConnection)
{
	return E_NOTIMPL;
}



STDMETHODIMP CDataObject::DUnadvise(DWORD dwConnection)
{
	return E_NOTIMPL;
}



STDMETHODIMP CDataObject::EnumDAdvise(IEnumSTATDATA** ppEnumAdvise)
{
	return E_NOTIMPL;
}


    
// IEnumFORMATETC Implementation
STDMETHODIMP CDataObject::Next(ULONG uRequested, LPFORMATETC pFormatEtc, ULONG* pulFetched)
{
	if(NULL == m_pFormatEtc)
		return S_FALSE;

	if(NULL != pulFetched)
		*pulFetched = 0L;

	if(NULL == pFormatEtc)
		return E_INVALIDARG;

	ULONG uFetched;
	for(uFetched = 0; m_iCurrent < m_cFormatEtc && uRequested > uFetched; uFetched++)
		*pFormatEtc++ = m_pFormatEtc[m_iCurrent++];
	
	if(NULL != pulFetched)
		*pulFetched = uFetched;

	return ((uFetched == uRequested) ? S_OK : S_FALSE);
}


STDMETHODIMP CDataObject::Skip(ULONG cSkip)
{
	if((m_iCurrent + cSkip) >= m_cFormatEtc)
		return S_FALSE;

	m_iCurrent += cSkip;

	return S_OK;
}


STDMETHODIMP CDataObject::Reset(void)
{
	m_iCurrent = 0;
	return S_OK;
}


STDMETHODIMP CDataObject::Clone(LPENUMFORMATETC* ppEnum)
{
	CDataObject* pNew;

	*ppEnum = NULL;

	// Create the clone.
	pNew = new CDataObject(m_psfParent, (LPCITEMIDLIST*)m_aPidls, m_uItemCount);
	if (NULL == pNew)
		return E_OUTOFMEMORY;

	pNew->m_iCurrent = m_iCurrent;

	*ppEnum = pNew;

	return S_OK;
}



// private and utility methods
BOOL CDataObject::AllocPidlTable(DWORD dwEntries)
{
	m_aPidls = (LPITEMIDLIST*)m_pMalloc->Alloc(dwEntries * sizeof(LPITEMIDLIST));

	if(m_aPidls)
		ZeroMemory(m_aPidls, dwEntries * sizeof(LPITEMIDLIST));

	return (m_aPidls != NULL);
}



VOID CDataObject::FreePidlTable(VOID)
{
	if(m_aPidls && m_pPidlMgr)
	{
		UINT  i;
		for(i = 0; i < m_uItemCount; i++)
			m_pPidlMgr->Delete(m_aPidls[i]);

		m_pMalloc->Free(m_aPidls);

		m_aPidls = NULL;
	}
}



BOOL CDataObject::FillPidlTable(LPCITEMIDLIST *aPidls, UINT uItemCount)
{
	if(m_aPidls)
	{
		if(m_pPidlMgr)
		{
			UINT i;
			for(i = 0; i < uItemCount; i++)
				m_aPidls[i] = m_pPidlMgr->Copy(aPidls[i]);

			return TRUE;
		}
	}

	return FALSE;
}


DecryptStatus CDataObject::DecryptDragged(LPCSTR lpszToDecrypt, LPCSTR lpszDropTarget,
										  LPCSTR lpszOrigLocation, BOOL *pbDecryptPrompt)
{
	static BOOL bFirstTime = TRUE;
	DecryptStatus Stat = DECR_OK;

	// 'lpszToDecrypt' is the file in the Safe which is being dragged out of Safe and put in 
	// the directory 'lpszDropTarget'. Decrypt the file and put it in the Safe itself bcos 
	// we have provided this directory path as the source of files for the CF_HDROP. However
	// put the extension ".dec" for the file which is being decrypted. After decryption remove the extension

	// Get the path of current active directory in the Safe
	TCHAR szActiveSafePath[MAX_PATH_LEN], szDecryptedFilePath[MAX_PATH_LEN];
	m_psfParent->GetPath(NULL, szActiveSafePath, MAX_PATH_LEN);

	// Construct the destination path. This is only for display purpose, the file will be 
	// decrypted in the Safe itself
	lstrcpy(szDecryptedFilePath, lpszDropTarget);
	lstrcat(szDecryptedFilePath, &lpszToDecrypt[lstrlen(szActiveSafePath)]);
	SetAnimateDlgText(lpszToDecrypt, szDecryptedFilePath);

	if(*pbDecryptPrompt)
	{
		if(IsFileFolderPresent(lpszToDecrypt, lpszDropTarget))
		{
			Stat = CanDecrypt(lpszToDecrypt, lpszDropTarget, pbDecryptPrompt);
			if(Stat != DECR_OK)
				return Stat;
		}
	}

	// Now construct the actual destination path
	lstrcpy(szDecryptedFilePath, lpszToDecrypt);
	lstrcat(szDecryptedFilePath, ".dec");

	Stat = DecryptAndVerifyFile(lpszToDecrypt, szDecryptedFilePath, TRUE);
	if(Stat == DECR_OK)
	{
		// Delete the encrypted file, remove the ".dec" extension of the decrypted file. 
		// File is not present in the Safe directory in the decrypted state.
		DeleteFile(lpszToDecrypt);
		MoveFile(szDecryptedFilePath, lpszToDecrypt);

		// Also delete the file if it is present outside of the Safe, this is to prevent 
		// Windows from showing its own file overwrite dialog
		lstrcpy(szDecryptedFilePath, lpszDropTarget);
		lstrcat(szDecryptedFilePath, &lpszToDecrypt[lstrlen(szActiveSafePath)]);
		DeleteFile(szDecryptedFilePath);

		// Modify the "fileinfo" file for status and date created(code similar
		// to CShellFolder::UpdateEncrItems())
		TCHAR szFileInfo[MAX_PATH_LEN], *pBSlash = NULL;
		lstrcpy(szFileInfo, lpszToDecrypt);
		pBSlash = strrchr(szFileInfo, '\\');
		lstrcpy(pBSlash + 1, "fileinfo");

		// Point to the file name, this is the section name in the ini file
		pBSlash = strrchr(lpszToDecrypt, '\\');

		// Mark the status of the file as out of Safe, '1' = DECRYPTED
		WritePrivateProfileString(pBSlash + 1, "Status", "1", szFileInfo);

		// Update the 'date created' field in the fileinfo, this is displayed in the 'decrypted view'
		TCHAR szOrigValue[MAX_PATH_LEN];
		HANDLE hFile = CreateFile(lpszToDecrypt, GENERIC_READ, FILE_SHARE_READ, NULL, 
								  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		BY_HANDLE_FILE_INFORMATION fad;
		GetFileInformationByHandle(hFile, &fad);
		CloseHandle(hFile);

		wsprintf(szOrigValue, "%u", fad.ftCreationTime.dwLowDateTime);
		WritePrivateProfileString(pBSlash + 1, "DateCreatedLow", szOrigValue, szFileInfo);

		wsprintf(szOrigValue, "%u", fad.ftCreationTime.dwHighDateTime);
		WritePrivateProfileString(pBSlash + 1, "DateCreatedHigh", szOrigValue, szFileInfo);

		// Check if file has been dropped to some location other then where it was originally. 
		// If so update the 'OrigLocation' in the 'fileinfo' file.
		TCHAR szOrigPath[MAX_PATH_LEN];
		lstrcpy(szOrigPath, lpszOrigLocation);
		pBSlash = strrchr(szOrigPath, '\\');
		if(pBSlash)
			*pBSlash = '\0';

		if(lstrcmpi(szOrigPath, lpszDropTarget))
		{
			TCHAR szNewLocation[MAX_PATH_LEN];
			lstrcpy(szNewLocation, lpszDropTarget);
			lstrcat(szNewLocation, &lpszToDecrypt[lstrlen(szActiveSafePath)]);
			WritePrivateProfileString(pBSlash + 1, "OrigLocation", szNewLocation, szFileInfo);
		}
	}
	
	return Stat;
}



DecryptStatus CDataObject::CanDecrypt(LPCSTR lpszToDecrypt, LPCSTR lpszDropTarget, BOOL *pbDecryptPrompt)
{
	if(*pbDecryptPrompt)
	{
		// Check if the 'szDecryptedFilePath' already exists. If yes prompt the user if he wants to replace.
		HWND hwndParent;
		if(g_hAnimateDlg)
			hwndParent = g_hAnimateDlg;
		else
			hwndParent = GetFocus();

		TCHAR szDestFile[MAX_PATH_LEN], *pBSlash = NULL;
		lstrcpy(szDestFile, lpszDropTarget);
		SmartAppendBackslash(szDestFile);
		pBSlash = strrchr(lpszToDecrypt, '\\');
		lstrcat(szDestFile, pBSlash + 1);

		UINT Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_REPLACE),  hwndParent, 
									 (DLGPROC)ReplaceConfirm, (LONG)szDestFile);

		switch(Action)
		{
			case IDB_YESTOALL:
			{
				*pbDecryptPrompt = FALSE;  // don't prompt now on
				break;
			}
			case IDOK:
				break;

			case IDCANCEL:
				return DECR_CANCEL;

			case IDB_NO:
				return DECR_FAIL;
		}
	}

	return DECR_OK;
}