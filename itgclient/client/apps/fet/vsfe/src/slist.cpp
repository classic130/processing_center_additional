// Implements CSList.

#include "stdafx.h"

#include <shlobj.h>
#include "slist.h"

CSList::CSList()
{
	m_pFirst = m_pLast = NULL;

	if(FAILED(SHGetMalloc(&m_pMalloc)))
	{
		delete this;
		return;
	}
}


CSList::~CSList()
{
	DeleteList();

	if(m_pMalloc)
		m_pMalloc->Release();
}


BOOL CSList::AddToList(LPCTSTR lpItem)
{
	LPSLIST pNew;

	pNew = (LPSLIST)m_pMalloc->Alloc(sizeof(SLIST));
	if(pNew)
	{
		// Set the next pointer
		pNew->pNext = NULL;
		lstrcpy(pNew->szItem, lpItem);

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



VOID CSList::RemoveFromList(LPCTSTR lpItem)
{
	LPSLIST pDelete;
	LPSLIST pPrev;

	// Find the item to be removed
	for(pDelete = m_pFirst, pPrev = NULL; pDelete; pDelete = pDelete->pNext)
	{
		if(!lstrcmpi(pDelete->szItem, lpItem))
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



BOOL CSList::DeleteList(VOID)
{
	LPSLIST pDelete;

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


LPCTSTR CSList::GetNextItem(LPCTSTR lpItemIn)
{
	LPSLIST pTemp;
	LPCTSTR lpItemOut = NULL;

	if(!lpItemIn)
		pTemp = m_pFirst;
	else
	{
		for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
		{
			if(!lstrcmpi(pTemp->szItem, lpItemIn))
			{
				pTemp = pTemp->pNext;
				break;
			}
		}
	}

	if(pTemp)
		lpItemOut = pTemp->szItem;
	
	return lpItemOut;
}
