// Implements CViewList.

#include "stdafx.h"

#include <shlobj.h>

#include "slist.h"
#include "cryptsup.h"

#include "ptav3.h"

#include "util.h"
#include "PidlMgr.h"
#include "ShlView.h"
#include "ViewList.h"


CViewList::CViewList()
{
	m_pFirst = m_pLast = NULL;

	if(FAILED(SHGetMalloc(&m_pMalloc)))
	{
		delete this;
		return;
	}
}


CViewList::~CViewList()
{
	DeleteList();

	if(m_pMalloc)
		m_pMalloc->Release();
}



CShellView* CViewList::GetNextView(CShellView *pViewIn)
{
	LPVIEWLIST  pTemp;
	CShellView  *pViewOut = NULL;

	if(!pViewIn)
		pTemp = m_pFirst;
	else
	{
		for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
		{
			if(pTemp->pView == pViewIn)
			{
				pTemp = pTemp->pNext;
				break;
			}
		}
	}

	if(pTemp)
		pViewOut = pTemp->pView;
	
	return pViewOut;
}



BOOL CViewList::AddToList(CShellView *pView)
{
	LPVIEWLIST  pNew;

	pNew = (LPVIEWLIST)m_pMalloc->Alloc(sizeof(VIEWLIST));

	if(pNew)
	{
		// Set the next pointer
		pNew->pNext = NULL;
		pNew->pView = pView;

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



VOID CViewList::RemoveFromList(CShellView *pView)
{
	LPVIEWLIST  pDelete;
	LPVIEWLIST  pPrev;

	// Find the item to be removed
	for(pDelete = m_pFirst, pPrev = NULL; pDelete; pDelete = pDelete->pNext)
	{
		if(pDelete->pView == pView)
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



BOOL CViewList::DeleteList(VOID)
{
	LPVIEWLIST pDelete;

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


UINT CViewList::GetCount()
{
	LPVIEWLIST pTemp;
	UINT nCnt = 0;

	for(pTemp = m_pFirst; pTemp; pTemp = pTemp->pNext)
		nCnt++;

	return nCnt;
}
