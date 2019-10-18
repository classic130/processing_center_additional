// CExtractIcon definitions.

#ifndef EXTRACTICON_H
#define EXTRACTICON_H


class CExtractIcon : public IExtractIcon
{
private:
   DWORD          m_ObjRefCount;
	LPITEMIDLIST   m_pidl;
   CPidlMgr       *m_pPidlMgr;

public:
   CExtractIcon(LPCITEMIDLIST);
   ~CExtractIcon();

   //IUnknown methods
   STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
   STDMETHOD_ (ULONG, AddRef) (VOID);
   STDMETHOD_ (ULONG, Release) (VOID);

   //IExtractIcon methods
   STDMETHOD (GetIconLocation) (UINT, LPTSTR, UINT, LPINT, LPUINT);
   STDMETHOD (Extract) (LPCTSTR, UINT, HICON*, HICON*, UINT);
};

#define ICON_INDEX_SAFE       0
#define ICON_INDEX_FOLDER     1
#define ICON_INDEX_FOLDEROPEN 2
#define ICON_INDEX_LOCKFILE	  3  // initially this represents the lock but later
								 // it represents the index of a file
#endif   //EXTRACTICON_H
