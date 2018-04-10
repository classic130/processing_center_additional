// CShellView definitions.


#ifndef SHELLVIEW_H
#define SHELLVIEW_H


//control IDs
#define ID_LISTVIEW_ENCR	2000
#define ID_LISTVIEW_DECR	2001

/**************************************************************************

   CShellView class definition

**************************************************************************/

class CShellView : public IShellView
{
friend class CShellFolder;
friend class CContextMenu;
friend class CDropTarget;

private:
	DWORD          m_ObjRefCount;
    UINT           m_uState;
	LPITEMIDLIST   m_pidl;
	FOLDERSETTINGS m_FolderSettings;
	LPSHELLBROWSER m_pShellBrowser;
	HWND           m_hwndParent;
	HWND           m_hWnd;
	HWND           m_hwndListEncr;	// the list view showing the encrypted items
	HWND           m_hwndListDecr;	// the list view showing the decrypted items
	HMENU          m_hMenu;
    CShellFolder   *m_psfParent;
	LPMALLOC       m_pMalloc;
    CPidlMgr       *m_pPidlMgr;
    HACCEL         m_hAccels;
    BOOL           m_fInEdit;

	HBITMAP		   m_hBmpVSLogo;	// Bitmap info for the Logo bitmap
	UINT		   m_nBmpVSLogoHt;	
	UINT		   m_nBmpVSLogoWd;

	HBITMAP		   m_hBmpEncr;		// Bitmap info for the "Encrypted" bitmap
	UINT		   m_nBmpEncrHt;
	UINT		   m_nBmpEncrWd;

	HBITMAP		   m_hBmpDecr;		// Bitmap info for the "Decrypted" bitmap
	UINT		   m_nBmpDecrHt;
	
	HBITMAP		   m_hBmpOpenSafe;	// Bitmap info for the Open Safe bitmap
	UINT		   m_nBmpOpenSafeHt;
	UINT		   m_nBmpOpenSafeWd;

	HBITMAP		   m_hBmpSafe;		// Bitmap info for the Close Safe bitmap
	UINT		   m_nBmpSafeHt;
	UINT		   m_nBmpSafeWd;
		
	UINT		   m_nSplitPos;		// maintains the current position of the splitter	
	HCURSOR		   m_hCurNS;		// cursor to display when mouse is on the split bar
	BOOL		   m_bSortAscEncrName;
	BOOL		   m_bSortAscEncrDate;
	BOOL		   m_bSortAscEncrType;
	BOOL		   m_bSortAscEncrSize;
	BOOL		   m_bSortAscEncrLoc;

	BOOL		   m_bSortAscDecrName;
	BOOL		   m_bSortAscDecrDate;
	BOOL		   m_bSortAscDecrType;
	BOOL		   m_bSortAscDecrSize;
	BOOL		   m_bSortAscDecrLoc;

	BOOL		   m_bSortAsc;
public:
   CShellView(CShellFolder*, LPCITEMIDLIST);
   ~CShellView();
   
   //IUnknown methods
   STDMETHOD (QueryInterface)(REFIID, LPVOID*);
   STDMETHOD_ (DWORD, AddRef)();
   STDMETHOD_ (DWORD, Release)();
   
   //IOleWindow methods
   STDMETHOD (GetWindow) (HWND*);
   STDMETHOD (ContextSensitiveHelp) (BOOL);

   //IShellView methods
   STDMETHOD (TranslateAccelerator) (LPMSG);
   STDMETHOD (EnableModeless) (BOOL);
   STDMETHOD (UIActivate) (UINT);
   STDMETHOD (Refresh) ();
   STDMETHOD (CreateViewWindow) (LPSHELLVIEW, LPCFOLDERSETTINGS, LPSHELLBROWSER, LPRECT, HWND*);
   STDMETHOD (DestroyViewWindow) (VOID);
   STDMETHOD (GetCurrentInfo) (LPFOLDERSETTINGS);
   STDMETHOD (AddPropertySheetPages) (DWORD, LPFNADDPROPSHEETPAGE, LPARAM);
   STDMETHOD (SaveViewState) (VOID);
   STDMETHOD (SelectItem) (LPCITEMIDLIST, UINT);
   STDMETHOD (GetItemObject) (UINT, REFIID, LPVOID*);

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
	static int CALLBACK SortByName(LPARAM, LPARAM, LPARAM);
	static int CALLBACK SortByDate(LPARAM, LPARAM, LPARAM);
	static int CALLBACK SortByType(LPARAM, LPARAM, LPARAM);
	static int CALLBACK SortBySize(LPARAM, LPARAM, LPARAM);
	static int CALLBACK SortByLoc(LPARAM, LPARAM, LPARAM);
	LRESULT UpdateMenu(HMENU hMenu);
	LRESULT UpdateToolbar(VOID);
	VOID MergeFileMenu(HMENU, BOOL);
	VOID MergeViewMenu(HMENU);
	VOID MergeEditMenu(HMENU, BOOL);
	VOID MergeHelpMenu(HMENU);
	VOID MergeToolbar(VOID);
	LRESULT OnCommand(DWORD, DWORD, HWND);
	LRESULT OnSetFocus(UINT);
	LRESULT OnKillFocus(VOID);
	LRESULT OnNotify(UINT, LPNMHDR);
	LRESULT OnSize(WORD, WORD);
	LRESULT OnPaint(VOID);
	LRESULT OnCreate(VOID);
	LRESULT OnDestroy(VOID);
	BOOL OnMenuSelect(DWORD); 
	BOOL CreateList(VOID);
	BOOL InitList(VOID);
	LRESULT OnSettingChange(LPCTSTR);
	VOID GetShellSettings(VOID);
	VOID DoContextMenu(WORD, WORD, BOOL, DWORD);
	int FindItemPidl(LPCITEMIDLIST);
	LRESULT OnViewLarge(VOID);
	LRESULT OnViewSmall(VOID);
	LRESULT OnViewList(VOID);
	LRESULT OnViewDetails(VOID);
	LRESULT OnArrangeIconEncr(UINT);
	LRESULT OnArrangeIconDecr(UINT);
	void OnArrangeIcon(UINT);
	BOOL AddEncrItem(LPCITEMIDLIST);
	BOOL DeleteItem(LPCITEMIDLIST);
	VOID UpdateData(LPCITEMIDLIST, LPCITEMIDLIST);
	VOID SelectAll(VOID);
	VOID InvertSelection(VOID);
	BOOL AddDecrItem(LPCITEMIDLIST);
	LRESULT OnNotifyEncr(LPNMHDR lpnmh);
	LRESULT OnNotifyDecr(LPNMHDR lpnmh);
	BOOL ShowDecryptView();
	BOOL ClearList();
	BOOL DropAllowed(LPPOINT, BOOL);
	VOID GetDecryptedFileLocation(LPTSTR, LPITEMIDLIST);
	VOID CreateTransparentBitmap(HDC hdcDest, UINT nXDest, 
						UINT nYDest, UINT nWidth, UINT nHeight, HBITMAP);
			
public:
	BOOL AddDecryptedContents(TCHAR *, BOOL);
	LRESULT OnActivate(UINT);
	BOOL BrowseToDesktop(VOID);
	BOOL BrowseToRoot(VOID);
	BOOL CollapseTree(VOID);
	VOID HideViewWindow(VOID);
	VOID ShowViewWindow(VOID);
	BOOL IsExplorerTreePresent();
	VOID DeleteListViewItems(VOID);
	VOID FillList(BOOL);
};

#endif   //SHELLVIEW_H
