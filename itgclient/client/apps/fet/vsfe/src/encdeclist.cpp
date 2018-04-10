// Implements CEncDecList.

#include "stdafx.h"

#include <shlobj.h>
#include "encdeclist.h"

CEncDecList::CEncDecList()
{
	m_pFirst = m_pLast = NULL;

	if(FAILED(SHGetMalloc(&m_pMalloc)))
	{
		delete this;
		return;
	}
}


CEncDecList::~CEncDecList()
{
	DeleteList();

	if(m_pMalloc)
		m_pMalloc->Release();
}


BOOL CEncDecList::AddToList(LPCTSTR lpOrigLoc, LPCTSTR lpLocInSafe)
{
	LPEncDec pNew;

	pNew = (LPEncDec)m_pMalloc->Alloc(sizeof(EncDec));
	if(pNew)
	{
		// Set the next pointer
		pNew->pNext = NULL;
		lstrcpy(pNew->szOrigLoc, lpOrigLoc);
		lstrcpy(pNew->szLocInSafe, lpLocInSafe);

		// Is this the first item in the list?
		if(!m_pFirst)
			m_pFirst = pNew;
	
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



VOID CEncDecList::RemoveFromList(LPCTSTR lpOrigLoc)
{
	LPEncDec pDelete;
	LPEncDec pPrev;

	// Find the item to be removed
	for(pDelete = m_pFirst, pPrev = NULL; pDelete; pDelete = pDelete->pNext)
	{
		if(!lstrcmpi(pDelete->szOrigLoc, lpOrigLoc))
			break;

		// Save the previous item in the list
		pPrev = pDelete;
	}

	if(pDelete)
	{
		if(pPrev)
			pPrev->pNext = pDelete->pNext;
		else
		{
			// The item being deleted is the first item in the list
			m_pFirst = pDelete->pNext;
		}

		// Was the last item deleted?
		if(!pDelete->pNext)
			m_pLast = pPrev;

		// Free the list item
		m_pMalloc->Free(pDelete);
	}
}



BOOL CEncDecList::DeleteList(VOID)
{
	LPEncDec pDelete;

	while(m_pFirst)
	{
		pDelete = m_pFirst;
		m_pFirst = pDelete->pNext;

		// Free the list item
		m_pMalloc->Free(pDelete);
	}

	m_pFirst = m_pLast = NULL;

	return TRUE;
}


LPEncDec CEncDecList::GetNextItem(LPCTSTR lpOrigLoc)
{
	LPEncDec pTemp;

	if(!lpOrigLoc)
		pTemp = m_pFirst;
	else
	{
		for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
		{
			if(!lstrcmpi(pTemp->szOrigLoc, lpOrigLoc))
			{
				pTemp = pTemp->pNext;
				break;
			}
		}
	}

	return pTemp;
}



LPCTSTR CEncDecList::GetLocInSafe(LPCTSTR lpOrigLoc)
{
	LPEncDec pTemp;
	LPCTSTR lpLocInSafe = NULL;

	for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
	{
		if(!lstrcmpi(pTemp->szOrigLoc, lpOrigLoc))
			break;
	}

	if(pTemp)
		lpLocInSafe = pTemp->szOrigLoc;
	
	return lpLocInSafe;
}


BOOL CEncDecList::SetLocInSafe(LPCTSTR lpOrigLoc, LPCTSTR lpLocInSafe)
{
	LPEncDec pTemp;

	for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
	{
		if(!lstrcmpi(pTemp->szOrigLoc, lpOrigLoc))
		{
			lstrcpy(pTemp->szLocInSafe, lpLocInSafe);
			break;
		}
	}

	if(!pTemp)	// 'lpszOrigLoc' not present, add new item
		AddToList(lpOrigLoc, lpLocInSafe);

	return TRUE;
}


UINT CEncDecList::GetCount()
{
	LPEncDec pTemp;
	UINT nCnt = 0;

	for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
		nCnt++;

	return nCnt;
}

