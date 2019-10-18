// CContextMenu definitions.


#ifndef CONTMENU_H
#define CONTMENU_H


class CContextMenu : public IContextMenu
{
private:
   DWORD          m_ObjRefCount;
   LPITEMIDLIST   *m_aPidls;
   IMalloc        *m_pMalloc;
   CPidlMgr       *m_pPidlMgr;
   CShellFolder   *m_psfParent;
   UINT           m_uItemCount;
   BOOL           m_fBackground;
   UINT           m_cfPrivateData;
   
public:
   CContextMenu(CShellFolder *psfParent, LPCITEMIDLIST *aPidls = NULL, UINT uItemCount = 0);
   ~CContextMenu();
   
   //IUnknown methods
   STDMETHODIMP QueryInterface(REFIID, LPVOID FAR *);
   STDMETHODIMP_(DWORD) AddRef();
   STDMETHODIMP_(DWORD) Release();

   //IContextMenu methods
   STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);
   STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
   STDMETHODIMP GetCommandString(UINT, UINT, LPUINT, LPSTR, UINT);

   // Methods used by the dialog box callback fns to access the pidl's selected
   LPCTSTR GetOriginalLocation(UINT);
   DWORD GetOriginalSize(UINT);
   FILETIME GetCreationDate(UINT);
   void GetSafeLocation(UINT, TCHAR *);
   UINT GetSelItemCount();

private:
   LPITEMIDLIST* AllocPidlTable(DWORD);
   VOID FreePidlTable(LPITEMIDLIST*);
   BOOL FillPidlTable(LPCITEMIDLIST*, UINT);
   BOOL DoExplore(HWND);
   BOOL DoOpen(HWND, BOOL, BOOL);
   BOOL DoEncrypt();
   BOOL DoSafeProp(HWND);
   BOOL DoFileProp(HWND);
   BOOL DoSelectAll(HWND);
   BOOL DoInvertSelection(HWND);
   BOOL DoClear(HWND);
   BOOL ShowDecryptView(VOID);
   STDMETHODIMP DoDelete(VOID);
   UINT InsertBackgroundEncryptItems(HMENU, UINT, UINT);
   UINT InsertBackgroundDecryptItems(HMENU, UINT, UINT);
   UINT InsertEncryptViewItems(HMENU, UINT, UINT, UINT);
   UINT InsertDecryptViewItems(HMENU, UINT, UINT, UINT);
   BOOL OpenDecryptedFiles(HWND);
   BOOL ShowEncryptFileDlg(HWND);
};


#define MYCMF_MULTISELECT		0x00010000
#define	FETHLP_INTRO			"fet_intro.htm"
#define SELECTED_FILES_SIZE		8192
#define FILE_FILTER				TEXT("All Files (*.*)\0*.*\0\0");

#if 0
// This structure is used to map the commands sent via a verb to a command id
// Commands are send via a verb when a icon on the toolbar is clicked
#define MAX_VERB  64
typedef struct 
{
   TCHAR szVerb[MAX_VERB];
   DWORD dwCommand;
}
VERBMAPPING, FAR *LPVERBMAPPING;
#endif


#endif// CONTMENU_H
