// Implements IEnumIDList.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "EnumIDL.h"
#include "ShlFldr.h"



CEnumIDList::CEnumIDList(LPCTSTR pszPath, DWORD dwFlags)
{
	g_DllRefCount++;

	m_pFirst = m_pLast = m_pCurrent = NULL;

	m_szPath[0] = 0;
	if(pszPath)
		lstrcpyn(m_szPath, pszPath, MAX_PATH);

	m_dwFlags = dwFlags;

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

	if(!CreateEnumList())
	{
		delete this;
		return;
	}

	m_ObjRefCount = 1;
}



CEnumIDList::~CEnumIDList()
{
	DeleteList();

	if(m_pMalloc)
		m_pMalloc->Release();

	if(m_pPidlMgr)
		delete m_pPidlMgr;

	g_DllRefCount--;
}



STDMETHODIMP CEnumIDList::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
	*ppReturn = NULL;

	// IUnknown
	if(IsEqualIID(riid, IID_IUnknown))
		*ppReturn = this;

	// IEnumIDList
	else if(IsEqualIID(riid, IID_IEnumIDList))
		*ppReturn = (IEnumIDList*)this;

	if(*ppReturn)
	{
		(*(LPUNKNOWN*)ppReturn)->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}                                             



STDMETHODIMP_(DWORD) CEnumIDList::AddRef()
{
	return ++m_ObjRefCount;
}



STDMETHODIMP_(DWORD) CEnumIDList::Release()
{
	if(--m_ObjRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}



STDMETHODIMP CEnumIDList::Next(DWORD dwElements, LPITEMIDLIST apidl[], LPDWORD pdwFetched)
{
	DWORD    dwIndex;
	HRESULT  hr = S_OK;

	if(dwElements > 1 && !pdwFetched)
		return E_INVALIDARG;

	for(dwIndex = 0; dwIndex < dwElements; dwIndex++)
	{
		// Is this the last item in the list?
		if(!m_pCurrent)
		{
			hr =  S_FALSE;
			break;
		}

		apidl[dwIndex] = m_pPidlMgr->Copy(m_pCurrent->pidl);

		m_pCurrent = m_pCurrent->pNext;
	}

	if(pdwFetched)
		*pdwFetched = dwIndex;

	return hr;
}



VOID CEnumIDList::DeletePidl(LPITEMIDLIST pidl)
{
	m_pPidlMgr->Delete(pidl);
}



STDMETHODIMP CEnumIDList::Skip(DWORD dwSkip)
{
	DWORD    dwIndex;
	HRESULT  hr = S_OK;

	for(dwIndex = 0; dwIndex < dwSkip; dwIndex++)
	{
		// Is this the last item in the list?
		if(!m_pCurrent)
		{
			hr = S_FALSE;
			break;
		}

		m_pCurrent = m_pCurrent->pNext;
	}

	return hr;
}



STDMETHODIMP CEnumIDList::Reset(VOID)
{
	m_pCurrent = m_pFirst;
	return S_OK;
}



STDMETHODIMP CEnumIDList::Clone(LPENUMIDLIST *ppEnum)
{
	HRESULT  hr = E_OUTOFMEMORY;

	*ppEnum = new CEnumIDList(m_szPath, m_dwFlags);

	if(*ppEnum)
	{
		LPENUMLIST  pTemp;

		// Synchronize the current pointer
		for(pTemp = m_pFirst; pTemp != m_pCurrent; pTemp = pTemp->pNext)
			(*ppEnum)->Skip(1);
	
		hr = S_OK;
	}

	return hr;
}



BOOL CEnumIDList::CreateEnumList(VOID)
{
	LPITEMIDLIST pidl;

	// Enumerate the folders
	if(m_dwFlags & SHCONTF_FOLDERS)
	{
		HANDLE          hFind;
		WIN32_FIND_DATA wfd;
		TCHAR           szTemp[MAX_PATH_LEN];

		lstrcpy(szTemp, m_szPath);
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
					TCHAR szPath[MAX_PATH_LEN];
					
					// If the folder contains only the 'fileinfo' file don't add it, this 
					// means that all files in this folder have been decrypted, the folder
					// has been retained just bcos it contains the fileinfo file to show the 
					// list of recently decrypted files. Delete the folder when the Safe is locked
					lstrcpy(szPath, m_szPath);
					SmartAppendBackslash(szPath);
					lstrcat(szPath, wfd.cFileName);
					if(!IsFolderPresent(szPath))
						continue;

					pidl = m_pPidlMgr->CreateFolderPidl(wfd.cFileName);

					if(pidl)
						AddToEnumList(pidl);
				}
			}
			while(FindNextFile(hFind, &wfd));

			FindClose(hFind);
		}
	}   

	if(m_dwFlags & SHCONTF_NONFOLDERS)
	{
		HANDLE          hFind;
		WIN32_FIND_DATA wfd;
		TCHAR           szTemp[MAX_PATH_LEN], szFileInfo[MAX_MSG_LEN];

		// Construct the search path
		lstrcpy(szTemp, m_szPath);
		SmartAppendBackslash(szTemp);
		lstrcat(szTemp, TEXT("*.*"));

		// Construct the path of the "fileinfo" file
		lstrcpy(szFileInfo, m_szPath);
		SmartAppendBackslash(szFileInfo);
		lstrcat(szFileInfo, "fileinfo");

		hFind = FindFirstFile(szTemp, &wfd);

		if(INVALID_HANDLE_VALUE != hFind)
		{
			TCHAR szFile[MAX_PATH_LEN], szOrigLocation[MAX_PATH_LEN], szOrigValue[32];
			DWORD dwOrigSize;
			FILETIME ftDateCreated, ftDateAccessed, ftDateModified;
			FileStatus Status;
			BOOL bUpdated = FALSE;

			// See if the "fileinfo" has been already updated. If it is then no need
			// to call WriteInfoFile() for all the files in this directory.
			// The updated status is reflected by the 'Updated' key under the [General]
			// section
			bUpdated = GetPrivateProfileInt("General", "Updated", 0, szFileInfo);

			if(!bUpdated)
			{
				do
				{
					if((FILE_ATTRIBUTE_ARCHIVE & wfd.dwFileAttributes) && 
						lstrcmpi(wfd.cFileName, TEXT(".")) &&  lstrcmpi(wfd.cFileName, TEXT("..")) &&
						IsUserFile(m_szPath, wfd.cFileName))
					{
						lstrcpy(szFile, wfd.cFileName);

						// Write the information of the original file into the info file. The info
						// file will contain the orig location, orig size ... of the encrypted file
						// This info is written in the encrypted file header before the encrypted
						// data.
					
						// construct the complete path of 'szFile'
						lstrcpy(szTemp, m_szPath);
						SmartAppendBackslash(szTemp);
						lstrcat(szTemp, szFile);

						WriteInfoFile(szTemp);
					}
				}
				while(FindNextFile(hFind, &wfd));
				
				WritePrivateProfileString("General", "Updated", "1", szFileInfo);
			} // if(!bUpdated)

			FindClose(hFind);

			// Get the info from the fileinfo file. this is basically an ini file with the 
			// section names as the file names. 
			
			// Getting all the section names will get even the files which are decrypted(out 
			// of Safe). these files are indicated by "Status = DECRYPTED"
			TCHAR szSectionNames[SECTION_NAME_SIZE], *pSectionName;

			if(GetPrivateProfileSectionNames(szSectionNames, SECTION_NAME_SIZE,
											 szFileInfo) == SECTION_NAME_SIZE - 2)
			{
				LogErrorMessage("CreateEnumList() : GetPrivateProfileSectionNames() size exceeded", 0);
				return FALSE;
			}

			pSectionName = szSectionNames;
			
			while(*pSectionName)
			{
				// Skip the general section as this is not related to a file.
				// What if there is a file named 'general' ???
				if(lstrcmpi(pSectionName, "General"))
				{
					GetPrivateProfileString(pSectionName, "OrigLocation", "c:\\temp", szOrigLocation, MAX_PATH, szFileInfo);

					GetPrivateProfileString(pSectionName, "OrigSize", "0x00000000", szOrigValue, 32, szFileInfo);
					dwOrigSize = atol(szOrigValue);
					
					GetPrivateProfileString(pSectionName, "DateCreatedLow", "0x00000000", szOrigValue, 32, szFileInfo);
 					ftDateCreated.dwLowDateTime = atol(szOrigValue);

					GetPrivateProfileString(pSectionName, "DateCreatedHigh", "0x00000000", szOrigValue, 32, szFileInfo);
					ftDateCreated.dwHighDateTime = atol(szOrigValue);

					GetPrivateProfileString(pSectionName, "DateModifiedLow", "0x00000000", szOrigValue, 32, szFileInfo);
 					ftDateModified.dwLowDateTime = atol(szOrigValue);

					GetPrivateProfileString(pSectionName, "DateModifiedHigh", "0x00000000", szOrigValue, 32, szFileInfo);
					ftDateModified.dwHighDateTime = atol(szOrigValue);

					GetPrivateProfileString(pSectionName, "DateAccessedLow", "0x00000000", szOrigValue, 32, szFileInfo);
 					ftDateAccessed.dwLowDateTime = atol(szOrigValue);

					GetPrivateProfileString(pSectionName, "DateAccessedHigh", "0x00000000", szOrigValue, 32, szFileInfo);
					ftDateAccessed.dwHighDateTime = atol(szOrigValue);

					Status = (FileStatus)GetPrivateProfileInt(pSectionName, "Status", DELETED, szFileInfo);

					if(Status == ENCRYPTED)
					{
						pidl = m_pPidlMgr->CreateItemPidl(pSectionName, szOrigLocation, dwOrigSize,
								  &ftDateCreated, &ftDateAccessed, &ftDateModified, Status);
						if(pidl)
							AddToEnumList(pidl);
					}
				}				

				pSectionName += lstrlen(pSectionName) + 1;
			} // end while
		} //if(INVALID_HANDLE_VALUE != hFind)
	}

	return TRUE;
}



BOOL CEnumIDList::AddToEnumList(LPITEMIDLIST pidl)
{
	LPENUMLIST pNew;

	pNew = (LPENUMLIST)m_pMalloc->Alloc(sizeof(ENUMLIST));

	if(pNew)
	{
		// Set the next pointer
		pNew->pNext = NULL;
		pNew->pidl = pidl;

		// Is this the first item in the list?
		if(!m_pFirst)
		{
			m_pFirst = pNew;
			m_pCurrent = m_pFirst;
		}

		if(m_pLast)
		{
			// Add the new item to the end of the list
			m_pLast->pNext = pNew;
		}

		// Update the last item pointer
		m_pLast = pNew;

		return TRUE;
	}

	return FALSE;
}



BOOL CEnumIDList::DeleteList(VOID)
{
	LPENUMLIST  pDelete;

	while(m_pFirst)
	{
		pDelete = m_pFirst;
		m_pFirst = pDelete->pNext;

		// Free the pidl
		m_pPidlMgr->Delete(pDelete->pidl);

		// Free the list item
		m_pMalloc->Free(pDelete);
	}

	m_pFirst = m_pLast = m_pCurrent = NULL;

	return TRUE;
}

