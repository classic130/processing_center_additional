// Implements CPidlMgr.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "PidlMgr.h"
#include "ShlFldr.h"
#include "Guid.h"


CPidlMgr::CPidlMgr()
{
	g_DllRefCount++;

	if(FAILED(SHGetMalloc(&m_pMalloc)))
		delete this;
}



CPidlMgr::~CPidlMgr()
{
	if(m_pMalloc)
		m_pMalloc->Release();

	g_DllRefCount--;
}


LPITEMIDLIST CPidlMgr::Create(VOID)
{
	LPITEMIDLIST   pidlOut;
	USHORT         uSize;

	pidlOut = NULL;

	// Calculate the size. This consists of the ITEMIDLIST plus the size of our private PIDL structure. 
	uSize = sizeof(ITEMIDLIST) + sizeof(PIDLDATA);

	// Allocate the memory, adding an additional ITEMIDLIST for the NULL terminating ID List.
	pidlOut = (LPITEMIDLIST)m_pMalloc->Alloc(uSize + sizeof(ITEMIDLIST));

	if(pidlOut)
	{
		LPITEMIDLIST   pidlTemp = pidlOut;

		// Set the size of this item
		pidlTemp->mkid.cb = uSize;

		// Set the NULL terminator to 0
		pidlTemp = GetNextItem(pidlTemp);
		pidlTemp->mkid.cb = 0;
		pidlTemp->mkid.abID[0] = 0;
	}

	return pidlOut;
}


VOID CPidlMgr::Delete(LPITEMIDLIST pidl)
{
	m_pMalloc->Free(pidl);
}



LPITEMIDLIST CPidlMgr::GetNextItem(LPCITEMIDLIST pidl)
{
	if(pidl)
		return (LPITEMIDLIST)(LPBYTE)(((LPBYTE)pidl) + pidl->mkid.cb);
	else
		return NULL;
}


UINT CPidlMgr::GetSize(LPCITEMIDLIST pidl)
{
	UINT cbTotal = 0;
	LPITEMIDLIST pidlTemp = (LPITEMIDLIST)pidl;

	if(pidlTemp)
	{
		while(pidlTemp->mkid.cb)
		{
			cbTotal += pidlTemp->mkid.cb;
			pidlTemp = GetNextItem(pidlTemp);
		}  

		// Add the size of the NULL terminating ITEMIDLIST
		cbTotal += sizeof(ITEMIDLIST);
	}

	return cbTotal;
}


LPITEMIDLIST CPidlMgr::GetLastItem(LPCITEMIDLIST pidl)
{
	LPITEMIDLIST   pidlLast = NULL;

	// Get the PIDL of the last item in the list
	while(pidl && pidl->mkid.cb)
	{
		pidlLast = (LPITEMIDLIST)pidl;
		pidl = GetNextItem(pidl);
	}  

	return pidlLast;
}



LPITEMIDLIST CPidlMgr::Copy(LPCITEMIDLIST pidlSource)
{
	LPITEMIDLIST pidlTarget = NULL;
	UINT cbSource = 0;

	if(NULL == pidlSource)
		return NULL;

	// Allocate the new pidl
	cbSource = GetSize(pidlSource);
	pidlTarget = (LPITEMIDLIST)m_pMalloc->Alloc(cbSource);
	if(!pidlTarget)
		return NULL;

	// Copy the source to the target
	CopyMemory(pidlTarget, pidlSource, cbSource);
	
	return pidlTarget;
}


LPITEMIDLIST CPidlMgr::CopySingleItem(LPCITEMIDLIST pidlSource)
{
	LPITEMIDLIST pidlTarget = NULL;
	UINT cbSource = 0;

	if(NULL == pidlSource)
		return NULL;

	// Allocate the new pidl
	cbSource = pidlSource->mkid.cb;
	pidlTarget = (LPITEMIDLIST)m_pMalloc->Alloc(cbSource + sizeof(ITEMIDLIST));
	if(!pidlTarget)
		return NULL;

	// Copy the source to the target
	ZeroMemory(pidlTarget, cbSource + sizeof(ITEMIDLIST));
	CopyMemory(pidlTarget, pidlSource, cbSource);

	return pidlTarget;
}


inline LPPIDLDATA CPidlMgr::GetDataPointer(LPCITEMIDLIST pidl)
{
	if(!pidl)
		return NULL;

	return (LPPIDLDATA)(pidl->mkid.abID);
}


LPITEMIDLIST CPidlMgr::Concatenate(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2)
{
	LPITEMIDLIST   pidlNew;
	UINT           cb1 = 0, 
	   cb2 = 0;

	// Are both of these NULL?
	if(!pidl1 && !pidl2)
	return NULL;

	// If pidl1 is NULL, just return a copy of pidl2
	if(!pidl1)
	{
		pidlNew = Copy(pidl2);
		return pidlNew;
	}

	// If pidl2 is NULL, just return a copy of pidl1
	if(!pidl2)
	{
		pidlNew = Copy(pidl1);
		return pidlNew;
	}

	cb1 = GetSize(pidl1) - sizeof(ITEMIDLIST);

	cb2 = GetSize(pidl2);

	// Create the new PIDL
	pidlNew = (LPITEMIDLIST)m_pMalloc->Alloc(cb1 + cb2);

	if(pidlNew)
	{
		// Copy the first PIDL
		CopyMemory(pidlNew, pidl1, cb1);

		// Copy the second PIDL
		CopyMemory(((LPBYTE)pidlNew) + cb1, pidl2, cb2);
	}

	return pidlNew;
}


LPITEMIDLIST CPidlMgr::CreateFolderPidl(LPCTSTR pszName)
{
	LPITEMIDLIST   pidl = Create();
	LPPIDLDATA     pData = GetDataPointer(pidl);

	if(pData)
	{
		memset(pData, 0, sizeof(PIDLDATA));
		pData->bFolder = TRUE;
		lstrcpyn(pData->szName, pszName, MAX_NAME);
	}

	return pidl;
}


LPITEMIDLIST CPidlMgr::CreateItemPidl(LPCTSTR pszName, LPCTSTR szOrigLocation, DWORD dwOrigSize, 
									  FILETIME *ftCreated, FILETIME *ftAccessed, FILETIME *ftModified, FileStatus Status)
{
	LPITEMIDLIST pidl = Create();
	LPPIDLDATA   pData = GetDataPointer(pidl);

	if(pData)
	{
		pData->bFolder = FALSE;

		lstrcpyn(pData->szName, pszName, MAX_NAME);
		lstrcpyn(pData->szOrigLocation, szOrigLocation, MAX_NAME);
		pData->dwOrigSize = dwOrigSize;
		pData->ftDateCreated = *ftCreated;
		pData->ftDateAccessed = *ftAccessed;
		pData->ftDateModified = *ftModified;
		pData->Status = Status;
	}

	return pidl;
}



int CPidlMgr::GetName(LPCITEMIDLIST pidl, LPTSTR pszText, DWORD dwSize)
{
	if(!IsBadWritePtr(pszText, dwSize))
	{
		*pszText = 0;

		LPPIDLDATA pData = GetDataPointer(pidl);

		if(pData)
		{
			lstrcpyn(pszText, pData->szName, dwSize);
			return lstrlen(pszText);
		}
	}

	return 0;
}



int CPidlMgr::GetRelativeName(LPCITEMIDLIST pidl, LPTSTR pszText, DWORD dwSize)
{
	if(!IsBadWritePtr(pszText, dwSize))
	{
		LPITEMIDLIST   pidlTemp;
		*pszText = 0;

		// Walk the list, getting the name for each item
		pidlTemp = (LPITEMIDLIST)pidl;
		while(pidlTemp && pidlTemp->mkid.cb)
		{
			LPTSTR   pszCurrent = pszText + lstrlen(pszText);
			dwSize -= GetName(pidlTemp, pszCurrent, dwSize);
			pidlTemp = GetNextItem(pidlTemp);

			// Don't add a backslash to the last item
			if(pidlTemp && pidlTemp->mkid.cb)
				SmartAppendBackslash(pszCurrent);
		}
		return lstrlen(pszText);
	}

	return 0;
}



int CPidlMgr::GetData(LPCITEMIDLIST pidl, LPTSTR pszText, DWORD dwSize)
{
	if(!IsBadWritePtr(pszText, dwSize))
	{
		*pszText = 0;

		LPPIDLDATA  pData = GetDataPointer(pidl);

		if(pData)
		{
			lstrcpyn(pszText, pData->szName, dwSize);
			return lstrlen(pszText);
		}
	}

	return 0;
}



BOOL CPidlMgr::IsFolder(LPCITEMIDLIST pidl)
{
	LPPIDLDATA  pData = GetDataPointer(pidl);

	if(pData)
		return pData->bFolder;

	return FALSE;
}



FileStatus CPidlMgr::GetStatus(LPCITEMIDLIST pidl)
{
	LPPIDLDATA pData = GetDataPointer(pidl);

	if(pData)
		return pData->Status;

	return INVALID;
}


BOOL CPidlMgr::SetStatus(LPCITEMIDLIST pidl, FileStatus fs)
{
	LPPIDLDATA pData = GetDataPointer(pidl);

	if(pData)
	{
		pData->Status = fs;
		return TRUE;
	}

	return FALSE;
}


LPCTSTR CPidlMgr::GetOriginalLocation(LPCITEMIDLIST pidl)
{
	LPPIDLDATA pData = GetDataPointer(pidl);

	if(pData)
		return (LPCTSTR)pData->szOrigLocation;

	return NULL;
}


DWORD CPidlMgr::GetOriginalSize(LPCITEMIDLIST pidl)
{
	LPPIDLDATA pData = GetDataPointer(pidl);

	if(pData)
		return pData->dwOrigSize;

	return 0;
}


FILETIME CPidlMgr::GetCreationDate(LPCITEMIDLIST pidl)
{
	FILETIME ft;
	memset(&ft, 0, sizeof(ft));

	LPPIDLDATA pData = GetDataPointer(pidl);

	if(pData)
		ft = pData->ftDateCreated;

	return ft;
}