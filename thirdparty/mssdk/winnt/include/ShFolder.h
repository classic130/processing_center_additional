// functions to get shell special folders/
// shfolder.dll supports these on all platforms including Win95, Win98, NT4 and IE4 shell

#ifndef _SHFOLDER_H_
#define _SHFOLDER_H_

#ifndef CSIDL_APPDATA
#define CSIDL_APPDATA                   0x001A      // Application Data, new for NT4
#endif

#ifndef CSIDL_LOCAL_APPDATA

#define CSIDL_LOCAL_APPDATA             0x001C      // non roaming app data, new for NT5
#define CSIDL_MYPICTURES                0x0027      // My Pictures, new for NT5
#define CSIDL_FLAG_CREATE               0x8000      // new for NT5, or this in to force creation of folder
#define CSIDL_WINDOWS                   0x0024
#define CSIDL_SYSTEM                    0x0025

#endif // CSIDL_LOCAL_APPDATA

STDAPI SHGetFolderPathA(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPSTR pszPath);
STDAPI SHGetFolderPathW(HWND hwnd, int csidl, HANDLE hToken, DWORD dwFlags, LPWSTR pszPath);

// protos so callers can GetProcAddress() from shfolder.dll

typedef HRESULT (__stdcall * PFNSHGETFOLDERPATHA)(HWND, int, HANDLE, DWORD, LPSTR);  // "SHGetFolderPathA"
typedef HRESULT (__stdcall * PFNSHGETFOLDERPATHW)(HWND, int, HANDLE, DWORD, LPWSTR); // "SHGetFolderPathW"

#ifdef UNICODE
#define SHGetFolderPath     SHGetFolderPathW
#define PFNSHGETFOLDERPATH  PFNSHGETFOLDERPATHW
#else
#define SHGetFolderPath     SHGetFolderPathA
#define PFNSHGETFOLDERPATH  PFNSHGETFOLDERPATHA
#endif

#endif //  _SHFOLDER_H_
