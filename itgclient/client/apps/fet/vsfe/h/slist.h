// CSList definitions.

#ifndef SLIST_H
#define SLIST_H

typedef struct tagSLIST
{
	struct tagSLIST *pNext;
	TCHAR szItem[MAX_PATH];
}SLIST, FAR *LPSLIST;


class CSList
{
public:
   CSList();
   ~CSList();
   
   LPCTSTR GetNextItem(LPCTSTR);
   BOOL AddToList(LPCTSTR);
   VOID RemoveFromList(LPCTSTR);
   BOOL DeleteList(VOID);
   
private:
   LPMALLOC m_pMalloc;
   LPSLIST m_pFirst;
   LPSLIST m_pLast;
};

#endif   //SLIST_H
