// CEnumIDList definitions.


#ifndef ENUMIDLIST_H
#define ENUMIDLIST_H

/**************************************************************************
   structure defintions
**************************************************************************/

typedef struct tagENUMLIST
{
	struct tagENUMLIST   *pNext;
	LPITEMIDLIST         pidl;
}ENUMLIST, FAR *LPENUMLIST;



class CEnumIDList : public IEnumIDList
{
private:
   DWORD       m_ObjRefCount;
   LPMALLOC    m_pMalloc;
   LPENUMLIST  m_pFirst;
   LPENUMLIST  m_pLast;
   LPENUMLIST  m_pCurrent;
   DWORD       m_dwFlags;
   TCHAR       m_szPath[MAX_PATH];
   CPidlMgr    *m_pPidlMgr;
   
public:
   CEnumIDList(LPCTSTR, DWORD);
   ~CEnumIDList();
   
   //IUnknown methods
   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_ (DWORD, AddRef)();
   STDMETHOD_ (DWORD, Release)();
   
   //IEnumIDList
   STDMETHOD (Next) (DWORD, LPITEMIDLIST*, LPDWORD);
   STDMETHOD (Skip) (DWORD);
   STDMETHOD (Reset) (VOID);
   STDMETHOD (Clone) (LPENUMIDLIST*);

   VOID DeletePidl(LPITEMIDLIST);

private:
   BOOL CreateEnumList(VOID);
   BOOL AddToEnumList(LPITEMIDLIST);
   BOOL DeleteList(VOID);
};

#endif   //ENUMIDLIST_H
