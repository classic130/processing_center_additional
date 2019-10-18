// CPidlMgr definitions.


#ifndef PIDLMGR_H
#define PIDLMGR_H


#define MAX_NAME MAX_PATH
#define MAX_DATA 128

typedef struct tagPIDLDATA
{
   BOOL bFolder;
   TCHAR szName[MAX_NAME];
   //TCHAR szData[MAX_DATA];

   // The PIDL will contain the Original Location of the file, the Original Size
   // Date Accessed. This is used to display the info in the List View
   // These fields will be valid only for a file. For folder no information will
   // be displayed
   TCHAR szOrigLocation[MAX_PATH];
   DWORD dwOrigSize;
   FILETIME ftDateCreated;
   FILETIME ftDateAccessed;
   FILETIME ftDateModified;
   FileStatus Status;
}PIDLDATA, FAR *LPPIDLDATA;



class CPidlMgr
{
public:
   CPidlMgr();
   ~CPidlMgr();

   VOID Delete(LPITEMIDLIST);
   LPITEMIDLIST GetNextItem(LPCITEMIDLIST);
   LPITEMIDLIST Copy(LPCITEMIDLIST);
   LPITEMIDLIST CopySingleItem(LPCITEMIDLIST);
   LPITEMIDLIST GetLastItem(LPCITEMIDLIST);
   LPITEMIDLIST Concatenate(LPCITEMIDLIST, LPCITEMIDLIST);
   LPITEMIDLIST CreateFolderPidl(LPCTSTR);
   LPITEMIDLIST CreateItemPidl(LPCTSTR, LPCTSTR, DWORD, FILETIME *, FILETIME *, FILETIME *, FileStatus);
   
   int GetName(LPCITEMIDLIST, LPTSTR, DWORD);
   int GetRelativeName(LPCITEMIDLIST, LPTSTR, DWORD);
   int GetData(LPCITEMIDLIST, LPTSTR, DWORD);
   BOOL IsFolder(LPCITEMIDLIST);
   UINT GetSize(LPCITEMIDLIST);

   FileStatus GetStatus(LPCITEMIDLIST);
   BOOL SetStatus(LPCITEMIDLIST, FileStatus);
   LPCTSTR GetOriginalLocation(LPCITEMIDLIST);
   DWORD GetOriginalSize(LPCITEMIDLIST);
   FILETIME GetCreationDate(LPCITEMIDLIST);

private:
   LPMALLOC m_pMalloc;

   LPITEMIDLIST Create(VOID);
   LPPIDLDATA GetDataPointer(LPCITEMIDLIST);
};

#endif   //PIDLMGR_H
