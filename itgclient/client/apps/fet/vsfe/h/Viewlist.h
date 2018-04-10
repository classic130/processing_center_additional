// CViewList definitions.

#ifndef VIEWLIST_H
#define VIEWLIST_H

typedef struct tagVIEWLIST
	{
		struct tagVIEWLIST   *pNext;
		CShellView           *pView;
	}VIEWLIST, FAR *LPVIEWLIST;


class CViewList
{
public:
   CViewList();
   ~CViewList();
   
   CShellView* GetNextView (CShellView*);
   BOOL AddToList(CShellView*);
   VOID RemoveFromList(CShellView*);
   UINT GetCount(VOID);
   
private:
   BOOL DeleteList(VOID);
   LPMALLOC m_pMalloc;
   LPVIEWLIST m_pFirst;
   LPVIEWLIST m_pLast;
};

#endif   //VIEWLIST_H
