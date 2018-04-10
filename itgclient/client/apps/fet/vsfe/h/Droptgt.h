// CDropTarget definitions.

class FAR CDropTarget : public IDropTarget
{
public:
   CDropTarget(CShellFolder*, HWND);
   ~CDropTarget();

   //IUnknown methods
   STDMETHOD(QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_(ULONG, AddRef)(void);
   STDMETHOD_(ULONG, Release)(void);

   //IDropTarget methods
   STDMETHOD(DragEnter)(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
   STDMETHOD(DragOver)(DWORD, POINTL, LPDWORD);
   STDMETHOD(DragLeave)(VOID);
   STDMETHOD(Drop)(LPDATAOBJECT, DWORD, POINTL, LPDWORD);

private:
   CShellFolder   *m_psfParent;
   CPidlMgr       *m_pPidlMgr;
   IMalloc        *m_pMalloc;
   ULONG          m_ObjRefCount;  
   BOOL           m_fAcceptFmt;
   UINT           m_cfPrivateData;
   BOOL			  m_EncryptAllowed;
   POINT		  m_ptCurPos;
   HWND			  m_hwndOwnerDropTgt;
   UINT			  m_CurrFormat;
   BOOL			  m_EncryptDrag;

   BOOL QueryDrop(DWORD, LPDWORD);
   DWORD GetDropEffectFromKeyState(DWORD);
   LPITEMIDLIST* AllocPidlTable(DWORD);
   VOID FreePidlTable(LPITEMIDLIST*);
   BOOL IsDropAllowed(BOOL);
};
