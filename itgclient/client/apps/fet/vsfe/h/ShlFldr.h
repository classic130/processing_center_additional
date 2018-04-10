// CShellFolder definitions.


#ifndef SHELLFOLDER_H
#define SHELLFOLDER_H


class CShellFolder : public IShellFolder, 
					 public IShellPropSheetExt,
                     public IPersistFolder,
					 public IExtractIcon,	// these 2 interfaces for the icon handler
                     public IPersistFile, 
					 public IContextMenu,	// these 2 interface to implement the 
					 public IShellExtInit	// context menu. this context menu is
{											// diff from the context menu which 
											// appears in the "Safe", logically the
friend class CShellView;					// the interfaces could have been a part
friend class CContextMenu;					// of a separate CLSID.
friend class CDropTarget;
friend class CDataObject;

private:
	DWORD			m_ObjRefCount;
	LPITEMIDLIST	m_pidlRel;
	LPITEMIDLIST	m_pidlFQ;
	CShellFolder	*m_psfParent;
	LPMALLOC		m_pMalloc;
	CPidlMgr		*m_pPidlMgr;
	LPDATAOBJECT	m_pDataObj;		// for context menu
	TCHAR			m_szFile[MAX_PATH]; // file for which icon is needed
	BOOL			m_bSafeClicked;	// to help in determining that
									// we were right clicked 
public:
	CShellFolder(CShellFolder *pParent = NULL, LPCITEMIDLIST pidl = NULL);
	~CShellFolder();

	//IUnknown methods
	STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
	STDMETHOD_ (ULONG, AddRef) (VOID);
	STDMETHOD_ (ULONG, Release) (VOID);

	//IShellFolder methods
	STDMETHOD (ParseDisplayName) (HWND, LPBC, LPOLESTR, LPDWORD, LPITEMIDLIST*, LPDWORD);
	STDMETHOD (EnumObjects) (HWND, DWORD, LPENUMIDLIST*);
	STDMETHOD (BindToObject) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
	STDMETHOD (BindToStorage) (LPCITEMIDLIST, LPBC, REFIID, LPVOID*);
	STDMETHOD (CompareIDs) (LPARAM, LPCITEMIDLIST, LPCITEMIDLIST);
	STDMETHOD (CreateViewObject) (HWND, REFIID, LPVOID* );
	STDMETHOD (GetAttributesOf) (UINT, LPCITEMIDLIST*, LPDWORD);
	STDMETHOD (GetUIObjectOf) (HWND, UINT, LPCITEMIDLIST*, REFIID, LPUINT, LPVOID*);
	STDMETHOD (GetDisplayNameOf) (LPCITEMIDLIST, DWORD, LPSTRRET);
	STDMETHOD (SetNameOf) (HWND, LPCITEMIDLIST, LPCOLESTR, DWORD, LPITEMIDLIST*);

	//IPersist methods
	//STDMETHODIMP GetClassID(LPCLSID);

	//IPersistFolder methods
	STDMETHODIMP Initialize(LPCITEMIDLIST);

	//IContextMenu methods
	STDMETHODIMP QueryContextMenu(HMENU hMenu, UINT indexMenu, UINT idCmdFirst,
                                  UINT idCmdLast, UINT uFlags);
	STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi);
	STDMETHODIMP GetCommandString(UINT idCmd, UINT uFlags, UINT FAR *reserved, 
								  LPSTR pszName, UINT cchMax);

	//IShellExtInit methods
	STDMETHODIMP Initialize(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, 
							HKEY hKeyID);

	//IShellPropSheetExt
    STDMETHODIMP AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam);
    STDMETHODIMP ReplacePage(UINT uPageID, LPFNADDPROPSHEETPAGE lpfnReplaceWith, 
                             LPARAM lParam);

	//IExtractIcon methods
    STDMETHODIMP GetIconLocation(UINT uFlags, LPSTR szIconFile, UINT cchMax,
                                 int *piIndex, UINT *pwFlags);
    STDMETHODIMP Extract(LPCSTR pszFile, UINT nIconIndex, HICON *phiconLarge,
                         HICON *phiconSmall, UINT nIconSize);

    //IPersistFile methods
    STDMETHODIMP GetClassID(LPCLSID lpClassID);
    STDMETHODIMP IsDirty();
    STDMETHODIMP Load(LPCOLESTR lpszFileName, DWORD grfMode);
    STDMETHODIMP Save(LPCOLESTR lpszFileName, BOOL fRemember);
    STDMETHODIMP SaveCompleted(LPCOLESTR lpszFileName);
    STDMETHODIMP GetCurFile(LPOLESTR FAR* lplpszFileName);

private:
   LPITEMIDLIST CreateFQPidl(LPCITEMIDLIST);
   STDMETHOD (DeleteItems)(LPITEMIDLIST*, UINT);
   STDMETHOD (UpdateEncrItems)(LPITEMIDLIST*, UINT);
   STDMETHOD (UpdateDecrItems)(LPCSTR, LPITEMIDLIST*);
   VOID GetFullName(LPCITEMIDLIST, LPTSTR, DWORD, DWORD);
   VOID GetPath(LPCITEMIDLIST, LPTSTR, DWORD);
   BOOL HasSubFolder(LPCITEMIDLIST);
   VOID NotifyViews(DWORD, LPCITEMIDLIST, LPCITEMIDLIST);
   STDMETHOD (CompareItems) (LPCITEMIDLIST, LPCITEMIDLIST);
   VOID UpdateViews();
};

#endif   //SHELLFOLDER_H
