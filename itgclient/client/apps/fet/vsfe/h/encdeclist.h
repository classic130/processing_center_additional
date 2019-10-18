// CEncDecList definitions.

#ifndef ENCDECLIST_H
#define ENCDECLIST_H

typedef struct tagENCDEC
{
	struct tagENCDEC *pNext;
	TCHAR szOrigLoc[MAX_PATH];
	TCHAR szLocInSafe[MAX_PATH];
}EncDec, FAR *LPEncDec;


class CEncDecList
{
public:
   CEncDecList();
   ~CEncDecList();
   
   LPEncDec GetNextItem(LPCTSTR);
   BOOL AddToList(LPCTSTR, LPCTSTR);
   VOID RemoveFromList(LPCTSTR);
   LPCTSTR GetLocInSafe(LPCTSTR);
   BOOL SetLocInSafe(LPCTSTR, LPCTSTR);
   UINT GetCount();
   BOOL DeleteList(VOID);
   
private:
   LPMALLOC m_pMalloc;
   LPEncDec m_pFirst;
   LPEncDec m_pLast;
};

#endif   //ENCDECLIST_H
