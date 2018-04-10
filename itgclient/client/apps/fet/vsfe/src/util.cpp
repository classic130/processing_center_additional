// Utility function implementation
#include "stdafx.h"
#include <shlobj.h>
#include <wininet.h>
#include <winuser.h>
#include <process.h>
#include "resource.h"
#include "commands.h"
#include "dlgprocs.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "ptadllapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"
#include "VSPS_Defines.h"
#include "util.h"
#include "global.h"
#include "safedel.h"
#include "PidlMgr.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "certmgmt.h"
#include "encdeclist.h"
#include "guid.h"
#include "shlview.h"
#include "viewlist.h"
#include "enumidl.h"
#include "vsferrs.h"

const IID IID_IVSRoamPrefs = {0xd962f4c4,0xddb0,0x11d3,{0xa4,0x28,0xd1,0xa3,0x69,0xca,0x48,0x4f}};
const IID IID_IVSPTADllApi = {0xa453a978,0x2054,0x11d4,{0x81,0x75,0x00,0x60,0xb0,0xf8,0x85,0xe6}};
const IID IID_IVSPTA = {0x6F7864F8,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};
const CLSID CLSID_VSPTA = {0x6F7864F9,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};

SelectedCERT currSelCert;
IVSProfMgmt *g_pProfMgmt = NULL;

extern PolicyVars g_LocalPolicy;
extern SafeSettings g_SafeProp;
extern TCHAR g_szPolicyFile[];
extern TCHAR g_szDecrSettingsFile[];
extern TCHAR g_szSettingsFile[];
extern TCHAR g_szTokenFile[MAX_PATH_LEN];
extern TCHAR g_szDesktopDir[];
extern BOOL g_DumpPolicyFile;
extern BOOL g_DumpDataFile;
extern BOOL g_bPasswordPrompt;
extern UINT g_nTimerId;
extern BOOL g_bLockedOut;
extern HashInfo g_PasswdHash;
extern CViewList *g_pViewList;
extern DWORD g_dwProgressRange;

extern CEncDecList *g_EncrAtLogoffList, *g_DecrAtLogonList;
extern BOOL DecryptAtLogon();
extern BOOL EncryptAtLogoff();
extern TCHAR g_szWinDir[MAX_PATH_LEN], g_szWinSysDir[MAX_PATH_LEN];

extern VOID CreateHiddenWindow(VOID);
extern VOID DestroyHiddenWindow(VOID);

TCHAR g_szInstallDir[MAX_PATH];
DWORD g_CurrentTickCount, g_PreviousTickCount;

extern BOOL g_bVeriSignCSP;


LPSTR _WideToMultiString(BSTR szwcInputString)
{
	LPSTR szmbOutputString = NULL;
	DWORD dwSize = 0;

	if(szwcInputString == NULL)
		return NULL ;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								 szwcInputString, -1, NULL, 0, NULL, NULL) ;

	// Allocate memory for the Multi Byte String.
	if((szmbOutputString = (LPSTR)malloc(dwSize)) == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("_WideToMultiString : Out of memory", 0);
		return NULL;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString, -1, szmbOutputString,
								dwSize, NULL, NULL);
	if(!dwSize)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("_WideToMultiString : Out of memory", 0);
		return NULL;
	}

	return szmbOutputString ;
}


BYTE* _WideToMultiByte(BSTR szwcInputString, DWORD *dwLength)
{
	LPSTR szmbOutputString = NULL;
	DWORD dwSize = 0;

	if(szwcInputString == NULL)
		return NULL;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								 szwcInputString, -1, NULL, 0, NULL, NULL);

	// Allocate memory for the Multi Byte String.
	if((szmbOutputString = (LPSTR)malloc(dwSize)) == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("_WideToMultiByte : Out of memory", 0);
		return NULL;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString, -1, szmbOutputString,
								dwSize, NULL, NULL);
	if(!dwSize)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("_WideToMultiByte : Unable to convert from Wide Char string to Multi Byte string", 0);
		return NULL;
	}

	*dwLength = dwSize;

	return (BYTE*)szmbOutputString;
}


BOOL GetGlobalSettings(VOID)
{
	LoadString(g_hInst, IDS_EXT_TITLE, g_szExtTitle, TITLE_SIZE);

	*g_szStoragePath = 0;

	TCHAR szBuffer[MAX_PATH];
	DWORD dwSizeName;
	dwSizeName = sizeof(szBuffer);

	if(!GetUserName(szBuffer, &dwSizeName))
		lstrcpy(szBuffer, "default");  // if not logged on to Windows use
									   // 'default' as directory for Safe files

	LPITEMIDLIST pidl;

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
	SHGetPathFromIDList(pidl, g_szDesktopDir);

	IMalloc *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidl);
   	   pMalloc->Release();
	}

	GetWindowsDirectory(g_szWinDir, sizeof(g_szWinDir));
	GetSystemDirectory(g_szWinSysDir, sizeof(g_szWinSysDir));

	// Get a list of all CSPs
	EnumCSPs();

	// Get the OS version
	OSVERSIONINFO os;
	memset(&os, 0, sizeof(OSVERSIONINFO));
	os.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&os);

	if(os.dwPlatformId == VER_PLATFORM_WIN32_NT)
		g_dwPlatform = VER_PLATFORM_WIN32_NT;
	else
		g_dwPlatform = VER_PLATFORM_WIN32_WINDOWS;

	HKEY hKey;
	LRESULT lResult;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, 
						   KEY_READ, &hKey);
	if(lResult == ERROR_SUCCESS)
	{
		DWORD dwType;
		DWORD dwSize = sizeof(DWORD);

		RegQueryValueEx(hKey, "DumpPolicyFile", NULL, &dwType,
						(LPBYTE)&g_DumpPolicyFile, &dwSize);

		dwSize = sizeof(DWORD);
		RegQueryValueEx(hKey, "DumpDataFile", NULL, &dwType,
						(LPBYTE)&g_DumpDataFile, &dwSize);
		RegCloseKey(hKey);
	}
	
	return TRUE;
}




BOOL GetInstallPath(VOID)
{
	// Get the install directory from the registry
	DWORD dwErr = 0, dwType = 0, dwSize = 0, dwError = 0;
	HKEY hKey = NULL;
	LRESULT lResult;
	WIN32_FIND_DATA wfd;
	HANDLE hDir = INVALID_HANDLE_VALUE;
	TCHAR szPolicyFile[MAX_PATH] ,szErr[MAX_PATH], szFmt[MAX_PATH], szCachedPolyFile[MAX_PATH];
	TCHAR szError[MAX_PATH], szFormattedErr[2*MAX_PATH];
	HRESULT hr;

	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, KEY_READ, &hKey);
	if(lResult != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_OPEN, MB_OK | MB_ICONERROR);
		wsprintf(szErr, "GetInstallPath() : Could not open registry key for reading\'%s\'", MAIN_KEY_STRING);
		LogErrorMessage(szErr, dwErr);
		return FALSE;
	}

	dwSize = sizeof(g_szInstallDir);
	if(RegQueryValueEx(hKey, "InstallDir", NULL, &dwType, (LPBYTE)g_szInstallDir, &dwSize) != ERROR_SUCCESS)
	{
		// If no Registry entry present then read the file from the <windows\downlo~1> directory 
		// where it was initially downloaded. If file is not present in this directory then 
		// download it from server
		lstrcpy(szPolicyFile, g_szWinDir);
		SmartAppendBackslash(szPolicyFile);
		lstrcat(szPolicyFile, "downlo~1\\");
		lstrcat(szPolicyFile, POLICY_FILE);

		hDir = FindFirstFile(szPolicyFile, &wfd);
		if(hDir != INVALID_HANDLE_VALUE)
		{
			FindClose(hDir);

			// Check if policy file is old, if so get it again
			if(IsOldPolicyFile(szPolicyFile))
			{
				if(!DownloadRemotePolicyFile(szPolicyFile, &dwErr))
				{
					// Ask user whether he wants to continue with current policy settings
					if(dwErr)
					{
						LogErrorMessage("GetInstallPath() : Error downloading policy file", dwErr);
						LoadString(g_hInst, IDS_POLICY_DOWNLOAD_ERR, szErr, MAX_PATH);
						if(MessageBox(GetFocus(), szErr, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
							return FALSE;							
					}
					else
					{
						LoadString(g_hInst, IDS_CONTINUE_POLICY, szErr, MAX_PATH);
						if(MessageBox(GetFocus(), szErr, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
							return FALSE;
					}
				}
			}
		}
		else
		{
			if(!DownloadRemotePolicyFile(szPolicyFile, &dwError))
			{
				// 'dwError' set if there is a error in a call to WinInet fns
				if(dwError)
				{
					if(dwError == ERROR_INTERNET_CANNOT_CONNECT)
					{
						LoadString(g_hInst, IDS_CONNECT_ERROR, szErr, MAX_PATH);
						wsprintf(szFmt, szErr, "");
						MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
					}
					else
						DisplayMessage(GetFocus(), IDS_NETWORK_ERROR, MB_OK | MB_ICONERROR);

					LogErrorMessage("GetInstallPath() : Could not download policy file", dwError);
				}

				RegCloseKey(hKey);
				return FALSE;
			}
		}

		if(!ReadPolicyFileVar("FileEncryption", "InstallDir", (UINT *)&g_LocalPolicy.szInstallDir, TRUE, szPolicyFile))
		{
			RegCloseKey(hKey);
			return FALSE;
		}

		lstrcpy(g_szInstallDir, g_LocalPolicy.szInstallDir);

		// Close the registry key and open it in write mode (NOTE - on Win2K non-power
		// users do not have write access to HKEY_LOCAL_MACHINE, so the assumption is that
		// this case arises only for a non-Win2K platform. For a Win2K platform the
		// 'InstallDir' entry would have been made by the MSIE installer)
		if(hKey)
			RegCloseKey(hKey);

		lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, KEY_WRITE, &hKey);
		if(lResult != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_OPEN, MB_OK | MB_ICONERROR);
			wsprintf(szErr, "GetInstallPath() : Could not open registry key for writing\'%s\'", MAIN_KEY_STRING);
			LogErrorMessage(szErr, dwErr);
			return FALSE;
		}

		if(RegSetValueEx(hKey, "InstallDir", 0, REG_SZ, (LPBYTE)g_szInstallDir, lstrlen(g_szInstallDir)) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_WRITE, MB_OK | MB_ICONERROR);
			LogErrorMessage("GetInstallPath() : Failed to set InstallDir key.", dwErr);
			RegCloseKey(hKey);
			return FALSE;
		}

		RegCloseKey(hKey);

		// Copy the policy from the 'downlo~1' directory to the install directory, this will
		// be the cached policy file, previously the 'downlo~1' directory was the cache directory
		// for the policy file, now it is changed to the install directory. This is because in
		// Win2K non-power user does not have write access to the 'downlo~1' directory.
		// Assumption is that on Win2K non-power user will be atleast be able to write to the
		// install directory

		// But first create the install dir if it does not already exist
		if((hr = CreateRecursiveDirectory(g_szInstallDir)) != S_OK)
		{
			LoadString(g_hInst, IDS_INSTALL_DIR_ERR, szErr, MAX_PATH);
			wsprintf(szFmt, szErr, g_szInstallDir);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szErr, "GetInstallPath() : Unable to create Install directory : \'%s\'", g_szInstallDir);
			LogErrorMessage(szErr, 0);
			return FALSE;
		}

		lstrcpy(szCachedPolyFile, g_szInstallDir);
		lstrcat(szCachedPolyFile, "\\");
		lstrcat(szCachedPolyFile, POLICY_FILE);
		if(!CopyFile(szPolicyFile, szCachedPolyFile, FALSE))
		{
			dwErr = GetLastError();
			MessageBox(GetFocus(), "Unable to copy policy file to the install folder.", "Safe", MB_OK | MB_ICONERROR);
			LogErrorMessage("GetInstallPath() : Failed to copy policy file to the install folder.", dwErr);
			return FALSE;
		}
	}
	else
	{
		RegCloseKey(hKey);

		// First create the install dir if it does not already exist
		if((hr = CreateRecursiveDirectory(g_szInstallDir)) != S_OK)
		{
			LoadString(g_hInst, IDS_INSTALL_DIR_ERR, szErr, MAX_PATH);
			wsprintf(szFmt, szErr, g_szInstallDir);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szErr, "GetInstallPath() : Unable to create Install directory : \'%s\'", g_szInstallDir);
			LogErrorMessage(szErr, 0);
			return FALSE;
		}

		// Install dir is present, check if it has the policy file, if not download it in the
		// install dir, the policy file present in the install dir is a cached policy file. All
		// users of the FET get their initial policy settings from the policy file present in 
		// the install dir
		lstrcpy(szCachedPolyFile, g_szInstallDir);
		lstrcat(szCachedPolyFile, "\\");
		lstrcat(szCachedPolyFile, POLICY_FILE);

		hDir = FindFirstFile(szCachedPolyFile, &wfd);
		if(hDir != INVALID_HANDLE_VALUE)
			FindClose(hDir);
		else
		{
			// Download the policy file to the install dir
			if(!DownloadRemotePolicyFile(szCachedPolyFile, &dwError))
			{
				// 'dwError' set if there is a error in a call to WinInet fns
				if(dwError)
				{
					if(dwError == ERROR_INTERNET_CANNOT_CONNECT)
					{
						LoadString(g_hInst, IDS_CONNECT_ERROR, szErr, MAX_PATH);
						wsprintf(szFmt, szErr, "");
						MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
					}
					else
						DisplayMessage(GetFocus(), IDS_NETWORK_ERROR, MB_OK | MB_ICONERROR);

					LogErrorMessage("GetInstallPath() : Could not download policy file", dwError);
				}

				return FALSE;
			}
		}
	}

	// Create the Safe directory if not already present
	TCHAR szUserName[MAX_PATH];
	DWORD dwNameSize = MAX_PATH;
	lstrcpy(g_szStoragePath, g_szInstallDir);
	if(!GetUserName(szUserName, &dwNameSize))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_USERNAME_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetInstallPath() : Unable to get Windows user name.", dwErr);
		return FALSE;
	}

	SmartAppendBackslash(g_szStoragePath);
	lstrcat(g_szStoragePath, szUserName);
	if((hr = CreateRecursiveDirectory(g_szStoragePath)) != S_OK)
	{
		if(hr == 5)
			LoadString(g_hInst, IDS_SAFE_DIR_ERR_PERM, szError, MAX_PATH);
		else
			LoadString(g_hInst, IDS_SAFE_DIR_ERR, szError, MAX_PATH);

		wsprintf(szFormattedErr, szError, g_szStoragePath);
		MessageBox(GetFocus(), szFormattedErr, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szError, "GetInstallPath() : Unable to create Safe directory : \'%s\'", g_szStoragePath);
		LogErrorMessage(szError, 0);
		return FALSE;
	}

	SetFileAttributes(g_szStoragePath, FILE_ATTRIBUTE_HIDDEN);

	// Get the paths of the metadata files and token file
	lstrcpy(g_szDecrSettingsFile, g_szStoragePath);
	lstrcat(g_szDecrSettingsFile, "\\vsettings_decr");

	lstrcpy(g_szSettingsFile, g_szStoragePath);
	lstrcat(g_szSettingsFile, "\\vsettings");

	lstrcpy(g_szTokenFile, g_szStoragePath);
	lstrcat(g_szTokenFile, "\\vstoken.req");

	lstrcpy(g_szPolicyFile, g_szStoragePath);
	SmartAppendBackslash(g_szPolicyFile);
	lstrcat(g_szPolicyFile, POLICY_FILE);

	return TRUE;
}


// allocate the buffers used in "secure deletion" and fill them with the pattern
BOOL BufferInit(VOID)
{
	if(!bBufferInit)
	{
		srand((unsigned)GetTickCount());
	
		for(int i = 0; i < 3; i++) 
		{
			Buffers[i] = (char *)VirtualAlloc(NULL, CLEANBUFSIZE, MEM_COMMIT, PAGE_READWRITE);
			if(!Buffers[i]) 
			{
				for(int j = 0; j < i; j++) 
					VirtualFree(Buffers[j], 0, MEM_RELEASE);

				return FALSE;
			}

			// Fill each buffer with a different signature
			switch(i) 
			{
				case 0:
					// Do nothing - buffer is zero-filled by Windows
					break;

				case 1:
					// Fill with complement of 0 - 0xFF
					memset(Buffers[i], 0xFF, CLEANBUFSIZE);
					break;
			case 2:
					// Fill with a random value
					for(int j = 0; j < CLEANBUFSIZE; j++) 
						Buffers[i][j] = (BYTE) rand();

					break;
			}
		}	

		bBufferInit = TRUE;
	}

	return TRUE;
}


VOID BufferDestroy(VOID)
{
	if(bBufferInit)
	{
		for(int i = 0; i < 3; i++) 
			VirtualFree(Buffers[i], 0, MEM_RELEASE);

		bBufferInit = FALSE;
	}
}



int WideCharToLocal(LPTSTR pLocal, LPWSTR pWide, DWORD dwChars)
{
	*pLocal = 0;

#ifdef UNICODE
	lstrcpyn(pLocal, pWide, dwChars);
#else
	WideCharToMultiByte(CP_ACP, 0, pWide, -1, pLocal, dwChars, NULL, NULL);
#endif

	return lstrlen(pLocal);
}



VOID CreateImageLists(VOID)
{
	int cx, cy;
	cx = GetSystemMetrics(SM_CXSMICON);
	cy = GetSystemMetrics(SM_CYSMICON);

	if(g_himlSmall)
		ImageList_Destroy(g_himlSmall);

	// Set the small image list
	g_himlSmall = ImageList_Create(cx, cy, ILC_COLORDDB | ILC_MASK, 5 /*4*/, 0);

	if(g_himlSmall)
	{
		HICON       hIcon;
		TCHAR       szFolder[MAX_PATH];
		SHFILEINFO  sfi;

		// Add the safe icon
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_SAFE), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlSmall, hIcon);

		// Add the closed folder icon
		GetWindowsDirectory(szFolder, MAX_PATH);
		SHGetFileInfo(szFolder, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON);
		ImageList_AddIcon(g_himlSmall, sfi.hIcon);

		// Add the open folder icon
		SHGetFileInfo(szFolder, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_SMALLICON 
					  | SHGFI_OPENICON);
		ImageList_AddIcon(g_himlSmall, sfi.hIcon);

		// Add the Safe icon
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_SAFE), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlSmall, hIcon);

		// Add the Unlock icon, this is the overlay image
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_OVERLAY), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlSmall, hIcon);
		ImageList_SetOverlayImage(g_himlSmall, 4, 1);
	}

	if(g_himlLarge)
		ImageList_Destroy(g_himlLarge);

	cx = GetSystemMetrics(SM_CXICON);
	cy = GetSystemMetrics(SM_CYICON);

	// Set the large image list
	g_himlLarge = ImageList_Create(cx, cy, ILC_COLORDDB | ILC_MASK, 5 /*4*/, 0);

	if(g_himlLarge)
	{
		HICON       hIcon;
		TCHAR       szFolder[MAX_PATH];
		SHFILEINFO  sfi;

		// Add the safe icon
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_SAFE), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlLarge, hIcon);

		// Add the closed folder icon
		GetWindowsDirectory(szFolder, MAX_PATH);
		ZeroMemory(&sfi, sizeof(sfi));
		SHGetFileInfo(szFolder, 0, &sfi, sizeof(sfi), SHGFI_ICON);
		ImageList_AddIcon(g_himlLarge, sfi.hIcon);

		// Add the open folder icon
		GetWindowsDirectory(szFolder, MAX_PATH);
		ZeroMemory(&sfi, sizeof(sfi));
		SHGetFileInfo(szFolder, 0, &sfi, sizeof(sfi), SHGFI_ICON | SHGFI_OPENICON);
		ImageList_AddIcon(g_himlLarge, sfi.hIcon);

		// Add the Safe icon
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_SAFE), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlLarge, hIcon);

		// Add the Unlock icon, this is the overlay image
		hIcon = (HICON)LoadImage(g_hInst, MAKEINTRESOURCE(IDI_ICON_OVERLAY), IMAGE_ICON, cx, cy, LR_DEFAULTCOLOR);
		ImageList_AddIcon(g_himlLarge, hIcon);
		ImageList_SetOverlayImage(g_himlLarge, 4, 1);
	}

}


VOID DestroyImageLists(VOID)
{
	if(g_himlSmall)
	{
		ImageList_Remove(g_himlSmall, -1);
		ImageList_Destroy(g_himlSmall);
	}

	if(g_himlLarge)
	{
		ImageList_Remove(g_himlLarge, -1);
		ImageList_Destroy(g_himlLarge);
	}
}


VOID SmartAppendBackslash(LPTSTR pszPath)
{
	if(*(pszPath + lstrlen(pszPath) - 1) != '\\')
		lstrcat(pszPath, TEXT("\\"));
}


VOID SmartAppendFrontslash(LPTSTR pszPath)
{
	if(*(pszPath + lstrlen(pszPath) - 1) != '/')
		lstrcat(pszPath, TEXT("/"));
}




int LocalToWideChar(LPWSTR pWide, LPTSTR pLocal, DWORD dwChars)
{
	*pWide = 0;

#ifdef UNICODE
	lstrcpyn(pWide, pLocal, dwChars);
#else
	MultiByteToWideChar(CP_ACP, 0, pLocal, -1, pWide, dwChars); 
#endif

	return lstrlenW(pWide);
}



BOOL GetTextFromSTRRET(IMalloc * pMalloc, LPSTRRET pStrRet, LPCITEMIDLIST pidl, 
                        LPTSTR pszText, DWORD dwSize)
{
	if(IsBadReadPtr(pStrRet, sizeof(UINT)))
		return FALSE;

	if(IsBadWritePtr(pszText, dwSize))
		return FALSE;

	switch(pStrRet->uType)
	{
		case STRRET_CSTR:
			AnsiToLocal(pszText, pStrRet->cStr, dwSize);
			break;

		case STRRET_OFFSET:
			lstrcpyn(pszText, (LPTSTR)(((LPBYTE)pidl) + pStrRet->uOffset), dwSize);
			break;

		case STRRET_WSTR:
		{
			WideCharToLocal(pszText, pStrRet->pOleStr, dwSize);

			if(!pMalloc)
				SHGetMalloc(&pMalloc);
			else
				pMalloc->AddRef();
			
			if(pMalloc)
			{
				pMalloc->Free(pStrRet->pOleStr);
				pMalloc->Release();
			}
		}
			break;

		default:
			return FALSE;
	}

	return TRUE;
}



int AnsiToLocal(LPTSTR pLocal, LPSTR pAnsi, DWORD dwChars)
{
	*pLocal = 0;

#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, pAnsi, -1, pLocal, dwChars); 
#else
	lstrcpyn(pLocal, pAnsi, dwChars);
#endif

	return lstrlen(pLocal);
}



UINT AddViewMenuItems(HMENU hMenu, UINT uOffset, UINT uInsertBefore, 
                      BOOL fByPosition)
{
	MENUITEMINFO   mii;
	TCHAR          szText[MAX_PATH] = TEXT("");
	UINT           uAdded = 0;

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	// Add the view menu items at the correct position in the menu
	LoadString(g_hInst, IDS_VIEW_LARGE, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_VIEW_LARGE;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_VIEW_SMALL, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_VIEW_SMALL;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_VIEW_LIST, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_VIEW_LIST;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_VIEW_DETAILS, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_VIEW_DETAILS;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	return uAdded;
}



UINT AddIconsMenuItems(BOOL bEncrypt, HMENU hMenu, UINT uOffset, UINT uInsertBefore, BOOL fByPosition)
{
	MENUITEMINFO mii;
	TCHAR        szText[MAX_PATH] = TEXT("");
	UINT         uAdded = 0;

	ZeroMemory(&mii, sizeof(mii));
	mii.cbSize = sizeof(mii);

	// Add the Arange Icons menu items at the correct position in the menu
	LoadString(g_hInst, IDS_BY_NAME, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_BY_NAME;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	if(bEncrypt)
		LoadString(g_hInst, IDS_BY_DATE_ENCRYPT, szText, sizeof(szText));
	else
		LoadString(g_hInst, IDS_BY_DATE_DECRYPT, szText, sizeof(szText));

	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_BY_DATE_ENCRYPT;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_BY_TYPE, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_BY_TYPE;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_BY_SIZE, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_BY_SIZE;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;

	LoadString(g_hInst, IDS_BY_ORIGIN, szText, sizeof(szText));
	mii.fMask = MIIM_TYPE | MIIM_ID | MIIM_STATE;
	mii.fType = MFT_STRING;
	mii.fState = MFS_ENABLED;
	mii.dwTypeData = szText;
	mii.wID = uOffset + IDM_BY_ORIGIN;
	InsertMenuItem(hMenu, uInsertBefore, fByPosition, &mii);

	uAdded++;


	return uAdded;
}

// Returns the file size as a formatted string
BOOL GetDisplaySize(__int64 FileSize, TCHAR *szFileSize, BOOL bDetailed)
{
	__int64 sizeKB = 0;
	TCHAR szFormatted[64];

	if(FileSize / 1024)
	{
		sizeKB = FileSize / 1024;

		if(bDetailed)
			GetFormatted(FileSize, szFormatted);

		if(sizeKB / 1024)
			if(bDetailed)
				sprintf(szFileSize, "%0.2fMB (%s bytes)", sizeKB / 1024.0, szFormatted);
			else
				sprintf(szFileSize, "%0.2fMB", sizeKB / 1024.0);
		else
			if(bDetailed)
				sprintf(szFileSize, "%0.2fKB (%s bytes)", FileSize / 1024.0, szFormatted);
			else
				sprintf(szFileSize, "%0.2fKB", FileSize / 1024.0);
	}
	else
		if(bDetailed)
			wsprintf(szFileSize, "%d bytes (%d bytes)", (UINT)FileSize, (UINT)FileSize);
		else
			wsprintf(szFileSize, "%d bytes", (UINT)FileSize);


	return TRUE;
}


BOOL GetFormatted(__int64 FileSize, PTCHAR szFormat)
{
	UINT i = 0, digits = 0;

	while(FileSize)
	{
		szFormat[i++] = UINT(FileSize % 10) + '0';
		FileSize = FileSize / 10;

		digits++;

		if(FileSize && digits == 3)
		{
			szFormat[i++] = ',';
			digits = 0;
		}
	}

	szFormat[i] = '\0';

	_strrev(szFormat);

	return TRUE;
}


BOOL GetDisplayTime(FILETIME *pfTime, PTCHAR szTime, BOOL bDetailed)
{
	char szMonth[12][32] = {"January", "February", "March", "April", "May",
	"June", "July", "August", "September", "October", "November", "December"};

	char szDay[7][32] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
		"Friday", "Saturday"};

	// First convert file time (UTC time) to local time
	FILETIME localTime;
	SYSTEMTIME sysTime;
	FileTimeToLocalFileTime(pfTime, &localTime);

	// Then convert that time to system time
	FileTimeToSystemTime(&localTime, &sysTime);

	if(bDetailed)
		wsprintf(szTime, "%s, %s %d,  %d, %d:%d:%d", szDay[sysTime.wDayOfWeek],
				 szMonth[sysTime.wMonth - 1], sysTime.wDay, sysTime.wYear, sysTime.wHour,
				 sysTime.wMinute, sysTime.wSecond);
	else
		wsprintf(szTime, "%d/%d/%d", sysTime.wMonth, sysTime.wDay, 
				 sysTime.wYear);

	return TRUE;
}



LPVOID GetViewInterface(HWND hWnd)
{
	IUnknown *pRet = NULL;

	if(IsViewWindow(hWnd))
		pRet = (IUnknown*)GetWindowLong(hWnd, VIEW_POINTER_OFFSET);
	
	if(pRet)
		pRet->AddRef();

	return (LPVOID)pRet;
}


BOOL IsViewWindow(HWND hWnd)
{
	if(!hWnd)
		return FALSE;

	TCHAR szClass[MAX_PATH] = TEXT("");

	GetClassName(hWnd, szClass, MAX_PATH);

	if(0 == lstrcmpi(szClass, NS_CLASS_NAME))
		return TRUE;

	return FALSE;
}



BOOL GetTemporaryFile(TCHAR *pTempFile)
{
	TCHAR cTempPath[MAX_PATH];

	if(!GetTempPath(MAX_PATH, cTempPath))
		return FALSE;

	// '0' means get a unique name and create the file
	if(!GetTempFileName(cTempPath, "ENCRYPT", 0, pTempFile))
		return FALSE;

	return TRUE;
}



// Called from EncryptAll(), DoEncrypt() to update the "fileinfo" file for this directory. 
// Also called from CreateEnumList() to create the entries for all files in this directory
BOOL WriteInfoFile(LPCTSTR szFileName)
{
	TCHAR szFileInfo[MAX_PATH], szOrigLocation[MAX_PATH], szOrigValue[16];
	TCHAR szTemp[MAX_PATH], szFmt[MAX_PATH];
	DWORD dwOrigSize, dwPathLen, dwBytesRead;
	FILETIME ftDate;
	BOOL bFileInfoPresent = FALSE;

	// The 'fileinfo' file. will cache the info(orig location, orig size ...) 
	// about each file in this folder. This file will be deleted at logoff

	// Construct the path of the "fileinfo" file
	lstrcpy(szFileInfo, szFileName);
	TCHAR *pBSlash = strrchr(szFileInfo, '\\');
	lstrcpy(pBSlash + 1, "fileinfo");

	// Point it to the filename
	pBSlash = strrchr(szFileName, '\\') + 1;

	HANDLE hEncFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
								 OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hEncFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szTemp, MAX_PATH);
		wsprintf(szFmt, szTemp, szFileName);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szTemp, "WriteFileInfo:CreateFile() for \'%s\' failed", szFileName);
		LogErrorMessage(szTemp, dwErr);
		return FALSE;
	}

	// Skip the length of the encrypted file
	SetFilePointer(hEncFile, sizeof(DWORD), NULL, FILE_BEGIN);

	// the length of Orig Path
	ReadFile(hEncFile, (LPVOID)&dwPathLen, sizeof(DWORD), &dwBytesRead,
			 NULL);
	// the Orig Path
	ReadFile(hEncFile, szOrigLocation, dwPathLen, &dwBytesRead,
			 NULL);
	szOrigLocation[dwPathLen] = '\0';

	// the Original length
	ReadFile(hEncFile, (LPVOID)&dwOrigSize, sizeof(DWORD), &dwBytesRead,
			 NULL);

	WritePrivateProfileString(pBSlash, "OrigLocation", szOrigLocation, szFileInfo);

	sprintf(szOrigValue, "%u", dwOrigSize);
	WritePrivateProfileString(pBSlash, "OrigSize", szOrigValue, szFileInfo);

	// the file Creation time
	ReadFile(hEncFile, &ftDate.dwLowDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	ReadFile(hEncFile, &ftDate.dwHighDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	sprintf(szOrigValue, "%u", ftDate.dwLowDateTime);
	WritePrivateProfileString(pBSlash, "DateCreatedLow", szOrigValue, szFileInfo);

	sprintf(szOrigValue, "%u", ftDate.dwHighDateTime);
	WritePrivateProfileString(pBSlash, "DateCreatedHigh", szOrigValue, szFileInfo);

	// the file Modification time
	ReadFile(hEncFile, &ftDate.dwLowDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	ReadFile(hEncFile, &ftDate.dwHighDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	sprintf(szOrigValue, "%u", ftDate.dwLowDateTime);
	WritePrivateProfileString(pBSlash, "DateModifiedLow", szOrigValue, szFileInfo);

	sprintf(szOrigValue, "%u", ftDate.dwHighDateTime);
	WritePrivateProfileString(pBSlash, "DateModifiedHigh", szOrigValue, szFileInfo);

	// the file Accessed time
	ReadFile(hEncFile, &ftDate.dwLowDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	ReadFile(hEncFile, &ftDate.dwHighDateTime, sizeof(DWORD), &dwBytesRead, 
			 NULL);
	sprintf(szOrigValue, "%u", ftDate.dwLowDateTime);
	WritePrivateProfileString(pBSlash, "DateAccessedLow", szOrigValue, szFileInfo);

	sprintf(szOrigValue, "%u", ftDate.dwHighDateTime);
	WritePrivateProfileString(pBSlash, "DateAccessedHigh", szOrigValue, szFileInfo);

	// "0" = encrypted
	WritePrivateProfileString(pBSlash, "Status", "0", szFileInfo);

	CloseHandle(hEncFile);

	return TRUE;
}


// Takes a pointer to a file and directory and return TRUE if it can be encrypted
EncryptStatus CanEncrypt(LPCTSTR lpszPath)
{
	TCHAR szFmt[MAX_PATH], szErr[MAX_PATH], *pBSlash = NULL;
	EncryptStatus Status = SUCCESS;
	DWORD fAttr = GetFileAttributes(lpszPath);

	pBSlash = strrchr(lpszPath, '\\');

	// Check if ext is '.enc'
	TCHAR *pStr = NULL;
	pStr = strrchr(lpszPath, '.');
	if(pStr)
	{
		if(!strnicmp(pStr, ".enc", 4))
			return SKIP;
	}

	// Check if file(s) in the physical Safe directory is selected
	// for encryption. eg if file in 'c:\progra~1\verisign\safe\profilename'
	// is selected then return FALSE
	//if(!_strnicmp(lpszPath, g_szStoragePath, lstrlen(g_szStoragePath)))
	if(!_strnicmp(lpszPath, g_szInstallDir, lstrlen(g_szInstallDir)))
		return SKIP;

	if(lstrlen(lpszPath) == 3)
	{
		LoadString(g_hInst, IDS_ROOT_FOLDER_ERR, szErr, MAX_PATH);
		wsprintf(szFmt, szErr, lpszPath);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		return ROOT_DIR;
	}
	
	if(!lstrcmpi(lpszPath, g_szWinDir) || !lstrcmpi(lpszPath, g_szWinSysDir))
	{
		LoadString(g_hInst, IDS_OS_FOLDER_ERR, szErr, MAX_PATH);
		wsprintf(szFmt, szErr, lpszPath);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		return SYS_DIR;
	}

	// If encrypting/decrypting at logoff/logon then no need to 
	// do the checks for hidden, read-only... as these have been done before
	 if(g_LogOn_Off)
		 return SUCCESS;

#if 0
	// If user is encrypting anything in the profiles directory
	// return SUCCESS even thought the profiles is in the OS directory
	TCHAR szProfileFolder[MAX_PATH];
	lstrcpy(szProfileFolder, g_szWinDir);
	SmartAppendBackslash(szProfileFolder);
	lstrcat(szProfileFolder, "Profiles");
	if(!_strnicmp(szProfileFolder, lpszPath, lstrlen(szProfileFolder)))
		return SUCCESS;
#endif

#if 0
	if(!_strnicmp(lpszPath, g_szWinDir, lstrlen(g_szWinDir)) ||
	   !_strnicmp(lpszPath, g_szWinSysDir, lstrlen(g_szWinSysDir)))
#else
	if((!_strnicmp(lpszPath, g_szWinDir, lstrlen(g_szWinDir)) ||
	    !_strnicmp(lpszPath, g_szWinSysDir, lstrlen(g_szWinSysDir))) &&
		!HasProfilePath(lpszPath)
	  )
#endif
	{
		LoadString(g_hInst, IDS_OS_FILE_ERR, szErr, MAX_PATH);
		wsprintf(szFmt, szErr, pBSlash + 1);
		Status = IN_SYS_DIR;
	}
	else
	{
		if(CheckFilterOnFile(lpszPath))
		{
			if(g_bFilterErrPrompt)
			{
				LoadString(g_hInst, IDS_FILTER_ERR, szErr, MAX_PATH);
				wsprintf(szFmt, szErr, pBSlash + 1);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
				g_bFilterErrPrompt = FALSE;
			}

			return SKIP;
		}

		if(fAttr & FILE_ATTRIBUTE_DIRECTORY)
			return SUCCESS;
		
		if(fAttr & FILE_ATTRIBUTE_READONLY)
		{
			LoadString(g_hInst, IDS_ENCRYPT_READONLY, szErr, MAX_PATH);
			wsprintf(szFmt, szErr, pBSlash + 1);
			Status = READONLY;
		}
		else
			if(fAttr & FILE_ATTRIBUTE_SYSTEM)
			{
				LoadString(g_hInst, IDS_ENCRYPT_SYSTEM, szErr, MAX_PATH);
				wsprintf(szFmt, szErr, pBSlash + 1);
				Status = SYSTEM;
			}
			else
				if(fAttr & FILE_ATTRIBUTE_TEMPORARY)
				{
					LoadString(g_hInst, IDS_ENCRYPT_TEMP, szErr, MAX_PATH);
					wsprintf(szFmt, szErr, pBSlash + 1);
					Status = TEMPORARY;
				}
				else
					if(fAttr & FILE_ATTRIBUTE_HIDDEN)
					{
						LoadString(g_hInst, IDS_ENCRYPT_HIDDEN, szErr, MAX_PATH);
						wsprintf(szFmt, szErr, pBSlash + 1);
						Status = HIDDEN;
					}
	}

	if(!g_bEncryptErrPrompt)
	{
		if(Status == READONLY || Status == IN_SYS_DIR)
		{
			// Try resetting the attribute
			DWORD fAttr = GetFileAttributes(lpszPath);
			fAttr &= ~FILE_ATTRIBUTE_READONLY;
			if(SetFileAttributes(lpszPath, fAttr))
				return SUCCESS;
			else
				return SKIP;
		}

		return SUCCESS;
	}

	if(Status != SUCCESS)
	{
		HWND hwndParent;
		if(g_hAnimateDlg)
			hwndParent = g_hAnimateDlg;
		else
			hwndParent = GetFocus();

		UINT Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_ENCRYPT_ERROR),
						 hwndParent, (DLGPROC)EncryptError, (LONG)szFmt);

		switch(Action)
		{
			case ID_YES_TO_ALL:
			{
				g_bEncryptErrPrompt = FALSE;  // Don't prompt now on

				// Fall through
			}
			
			case IDOK:
			{
				if(Status == READONLY)
				{
					// Try resetting the attribute
					DWORD fAttr = GetFileAttributes(lpszPath);
					fAttr &= ~FILE_ATTRIBUTE_READONLY;
					if(SetFileAttributes(lpszPath, fAttr))
						return SUCCESS;
					else
						return SKIP;
				}

				return SUCCESS;
			}

			case IDCANCEL:
				return CANCEL;

			case ID_NO:
				return SKIP;
		}
	}

	return Status;
}



// Checks if the path specified is in the '\operating system\profiles' or '\os\desktop' directory
BOOL HasProfilePath(LPCTSTR lpszPath)
{
	TCHAR szProfilePath[2*MAX_PATH], szDesktopPath[2*MAX_PATH];
	
	if(!lpszPath)
		return FALSE;

	lstrcpy(szProfilePath, g_szWinDir);
	SmartAppendBackslash(szProfilePath);
	lstrcat(szProfilePath, "Profiles");

	lstrcpy(szDesktopPath, g_szWinDir);
	SmartAppendBackslash(szDesktopPath);
	lstrcat(szDesktopPath, "Desktop");

	if(!_strnicmp(szProfilePath, lpszPath, lstrlen(szProfilePath)) || 
	   !_strnicmp(szDesktopPath, lpszPath, lstrlen(szDesktopPath)))
	   return TRUE;

	return FALSE;
}


// Checks all files specified by pDataObj to see if any are system files,
// read only or hidden. Returns 'TRUE' if any file can be moved in the Safe
BOOL IsEncryptionAllowed(LPDATAOBJECT pDataObj)
{
	HRESULT		hr = E_FAIL;
	FORMATETC   fmtetc;
	STGMEDIUM   StgMedium;

	fmtetc.cfFormat   = CF_HDROP;
	fmtetc.ptd        = NULL;
	fmtetc.dwAspect   = DVASPECT_CONTENT;
	fmtetc.lindex     = -1;
	fmtetc.tymed      = TYMED_HGLOBAL;

	hr = pDataObj->GetData(&fmtetc, &StgMedium);
	if(SUCCEEDED(hr))
	{
		char szSelected[MAX_PATH], szDrive[4] = "c:\\";
		UINT i = 0;
		UINT nFileCnt = DragQueryFile((HDROP)StgMedium.hGlobal, -1, NULL, 0);

		
		DWORD fAttr = (FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY |
					   FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_TEMPORARY);


		// No encryption for windows/windows system directory, 
		// for files which have these folders in their path 
		// for the root drives "c:\" "d:\" 
		// for the removable drives (n/w drives, cdroms ...)
		while(i < nFileCnt)
		{
			DragQueryFile((HDROP)StgMedium.hGlobal, i, szSelected, 
						  sizeof(szSelected));

			szDrive[0] = szSelected[0];

			if( (lstrlen(szSelected) == 3) ||						// c:\, d:\ not allowed, ie root dirs cannot be encrypted
				(GetDriveType(szDrive) != DRIVE_FIXED) ||			// removable drives like n/w drives, CDROM's, floppy disks cannot be encrypted
				(GetFileAttributes(szSelected) & fAttr) ||			// exclude files having these attributes from encryption
				!_strnicmp(szSelected, g_szWinDir, lstrlen(g_szWinDir)) ||		// files in the Windows or the
				!_strnicmp(szSelected, g_szWinSysDir, lstrlen(g_szWinSysDir))	// the Windows\system dir cannot be encrypted
			  )
			{
				// Special case, in the windows dir, the files in desktop folder can be encrypted
				if(!_strnicmp(szSelected, g_szDesktopDir, lstrlen(g_szDesktopDir)))
					break;

				++i;
			}
			else
				break;
		} 
		
		ReleaseStgMedium(&StgMedium);

		if(nFileCnt && (i == nFileCnt))
			return FALSE;	// none can be encrypted

		return TRUE;	// at least one can be encrypted
	} // if(SUCCEEDED(hr))
	else
		return FALSE;
}


BOOL RemoveFileInfoFiles(LPCTSTR lpszDir)
{
	HANDLE          hFind;
	WIN32_FIND_DATA wfd;
	TCHAR           szTemp[MAX_PATH];

	if(lpszDir == NULL || lpszDir[0] == '\0')
		return FALSE;

	lstrcpy(szTemp, lpszDir);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));
	hFind = FindFirstFile(szTemp, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT(".")) && 
			   lstrcmpi(wfd.cFileName, TEXT("..")))
			{
				// Build the path of the directory or file found
				lstrcpy(szTemp, lpszDir);
				SmartAppendBackslash(szTemp);
				lstrcat(szTemp, wfd.cFileName);

				// We found a directory - call this function recursively
				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
					RemoveFileInfoFiles(szTemp);
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);

		lstrcpy(szTemp, lpszDir);
		SmartAppendBackslash(szTemp);
		lstrcat(szTemp, "fileinfo");
		DeleteFile(szTemp);
		RemoveEmptyFolder(lpszDir);
	}

	return TRUE;
}


BOOL RemoveEmptyFolder(LPCSTR lpszFolder)
{
	if(lpszFolder == NULL || lpszFolder[0] == '\0')
		return FALSE;

	HANDLE          hFind;
	WIN32_FIND_DATA wfd;
	TCHAR           szTemp[MAX_PATH];

	lstrcpy(szTemp, lpszFolder);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));
	hFind = FindFirstFile(szTemp, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(!lstrcmpi(wfd.cFileName, TEXT(".")) ||
			   !lstrcmpi(wfd.cFileName, TEXT("..")))
				continue;
			else
			{
				// Some file/folder present
				FindClose(hFind);
				return FALSE;
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);

		return RemoveDirectory(lpszFolder);
	}

	return TRUE;
}


// Remove all the entries marked DELETED from the "fileinfo" files.
// Also if the 'fileinfo' files contains only DELETED entries remove
// the 'fileinfo' file and the folder
BOOL RemoveDecryptedContents(TCHAR *pEncrFolder)
{
	TCHAR szFileInfo[MAX_PATH];
	FileStatus Status;
	TCHAR szSectionNames[SECTION_NAME_SIZE], *pSectionName;
	BOOL bDeleteFolder = TRUE;

	if(pEncrFolder == NULL || pEncrFolder[0] == '\0')
		return FALSE;

	lstrcpy(szFileInfo, pEncrFolder);
	strcat(szFileInfo, "\\fileinfo");

	// For this directory get all the decrypted files as indicated by the
	// "fileinfo" file
	if(GetPrivateProfileSectionNames(szSectionNames, SECTION_NAME_SIZE,
									 szFileInfo) == SECTION_NAME_SIZE - 2)
	{
		LogErrorMessage("RemoveDecryptedContents() : GetPrivateProfileSectionNames() size exceeded", 0);
		return FALSE;
	}

	pSectionName = szSectionNames;
	
	while(*pSectionName)
	{
		Status = (FileStatus)GetPrivateProfileInt(pSectionName, "Status", 
												  DELETED, szFileInfo);

		// Remove the entry from the "fileinfo" file
		if(Status == DECRYPTED)
			WritePrivateProfileString(pSectionName, NULL, NULL, szFileInfo);
		else
			if(Status == ENCRYPTED)
				bDeleteFolder = FALSE;
	
		pSectionName += lstrlen(pSectionName) + 1;
	}

	
	// If this directory also has sub directories then repeat the above for
	// all directories
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR szPath[MAX_PATH];

	lstrcpy(szPath, pEncrFolder);
	SmartAppendBackslash(szPath);
	lstrcat(szPath, TEXT("*.*"));

	hFind = FindFirstFile(szPath, &wfd);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if((FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes) && 
				lstrcmpi(wfd.cFileName, TEXT(".")) && 
				lstrcmpi(wfd.cFileName, TEXT("..")))
			{
				lstrcpy(szPath, pEncrFolder);
				SmartAppendBackslash(szPath);
				lstrcat(szPath, wfd.cFileName);

				RemoveDecryptedContents(szPath);
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

	// No encrypted files in folder, delete 'fileinfo' and the folder
	if(bDeleteFolder)
	{
		DeleteFile(szFileInfo);
		RemoveDirectory(pEncrFolder);
	}

	return TRUE;
}




BOOL DisplayMessage(HWND hWndParent, UINT uStringId, UINT uType)
{
	if(!g_LogOn_Off)
	{
		TCHAR szText[MAX_PATH], szString[MAX_PATH];
		LoadString(g_hInst, IDS_SAFE, szText, sizeof(szText));
		LoadString(g_hInst, uStringId, szString, sizeof(szString));
		MessageBox(hWndParent, szString, szText, uType);
	}

	return TRUE;
}


// Gets the size and no of files and folders in'lpszLocInSafe'
BOOL GetSafeParameters(LPCTSTR lpszLocInSafe, __int64* FileSize, __int64 *OrigSize, ULONG *ulFiles,
					   ULONG *ulFolders)
{
	HANDLE          hFind, hFile;
	WIN32_FIND_DATA wfd;
	TCHAR           szTemp[MAX_PATH];
	DWORD			dwFileSize;

	lstrcpy(szTemp, lpszLocInSafe);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));
	hFind = FindFirstFile(szTemp, &wfd);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT("."))  && 
			   lstrcmpi(wfd.cFileName, TEXT("..")) &&
			   IsUserFile(lpszLocInSafe, wfd.cFileName))
			{
				// Build the path of the directory or file found
				lstrcpy(szTemp, lpszLocInSafe);
				SmartAppendBackslash(szTemp);
				lstrcat(szTemp, wfd.cFileName);

				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					// We found a directory - call this function recursively
					(*ulFolders)++;
					GetSafeParameters(szTemp, FileSize, OrigSize, ulFiles, ulFolders);
				}
				else
				{
					// Found a file. Get its size.
					(*ulFiles)++;

					hFile = CreateFile(szTemp, GENERIC_READ, FILE_SHARE_READ,
									   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE,
									   NULL);

					dwFileSize = GetFileSize(hFile, NULL);

					*FileSize += dwFileSize;

					if(OrigSize)
					{
						TCHAR szOrigValue[32], szFileInfo[MAX_PATH];

						lstrcpy(szFileInfo, lpszLocInSafe);
						SmartAppendBackslash(szFileInfo);
						lstrcat(szFileInfo, "fileinfo");

						GetPrivateProfileString(wfd.cFileName, "OrigSize", "0x00000000",
												szOrigValue, 32, szFileInfo);
						*OrigSize += atol(szOrigValue);
					}

					CloseHandle(hFile);
				}
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

	return TRUE;
}



BOOL CreateDestFolder(LPCSTR szDestFile, LPTSTR szDestPath)
{
	TCHAR szDestDir[MAX_PATH], *pStr; 

	lstrcpy(szDestDir, szDestFile);
	pStr = strrchr(szDestDir, '\\');
	*pStr = NULL;

	TCHAR szDrive[4] = "c:\\";
	szDrive[0] = szDestFile[0];

	UINT uDriveType = GetDriveType(szDrive);

	if((uDriveType == DRIVE_UNKNOWN) || (uDriveType == DRIVE_NO_ROOT_DIR) ||
		CreateRecursiveDirectory(szDestDir) != S_OK)
	{
		TCHAR szFmt[MAX_PATH], szErr[MAX_PATH], szDir[MAX_PATH];
		LoadString(g_hInst, IDS_DIR_SELECT, szErr, MAX_PATH);
		wsprintf(szFmt, szErr, szDestDir);

		if(!g_LogOn_Off && GetDirectory(szDir, szFmt))
		{
			lstrcpy(szDestPath, szDir);
			SmartAppendBackslash(szDestPath);

			TCHAR *pStr;
			
			pStr = strrchr(szDestFile, '\\');
			lstrcat(szDestPath, pStr + 1);

			return TRUE;
		}

		szDestPath[0] = '\0';
		return FALSE;
	}

	lstrcpy(szDestPath, szDestFile);

	return TRUE;
}

/*
// Create all the directories in the path
BOOL CreateRecursiveDirectory(LPCSTR lpszDirToCreate)
{
	WIN32_FIND_DATA wfd;

	if(lstrlen(lpszDirToCreate) == 2)	// root dirs "a:"
		return TRUE;
	
	HANDLE hDir = FindFirstFile(lpszDirToCreate, &wfd);
	if(hDir != INVALID_HANDLE_VALUE)
	{
		FindClose(hDir);
		return TRUE;
	}

	TCHAR szDirParent[MAX_PATH], *pStr;
	
	lstrcpy(szDirParent, lpszDirToCreate);
	pStr = strrchr(szDirParent, '\\');
	*pStr = NULL;
	
	if(CreateRecursiveDirectory(szDirParent))
		if(CreateDirectory(lpszDirToCreate, NULL))
			return TRUE;
		else
			return FALSE;

	return FALSE;
}
*/


HRESULT CreateRecursiveDirectory(LPCTSTR lpszDirToCreate)
{
	HRESULT hr = S_OK;
	WIN32_FIND_DATA wfd;
	TCHAR szDir[MAX_PATH_LEN], szDirParent[MAX_PATH_LEN];
	TCHAR *pBSlash = NULL;
	HANDLE hDir = NULL;

	do
	{
		if(!lpszDirToCreate)
		{
			hr = E_VSFEMPTYARGS;
			break;
		}

		lstrcpy(szDir, lpszDirToCreate);

		if(szDir[0] == '\0')
		{
			hr = E_VSFEINVALIDARGS;
			break;
		}

		// Check if szDir[0] is a logical drive
		if(!IsLogicalDrive(szDir[0]))
		{
			hr = E_VSFEINVALIDRIVE;
			break;
		}

		if(szDir[1] != ':')
		{
			hr = E_VSFEINVALIDPATH;
			break;
		}

		// A valid path is found return success
		if(szDir[2] == '\0')
			break;

		if(szDir[2] != '\\')
		{
			hr = E_VSFEINVALIDPATH;
			break;
		}

		if(szDir[3] == '\0')
			break;

		hDir = FindFirstFile(szDir, &wfd);
		if(hDir != INVALID_HANDLE_VALUE)
		{
			FindClose(hDir);
			hDir = NULL;
			break;
		}

		lstrcpy(szDirParent, szDir);

		pBSlash = strrchr(szDirParent, '\\');
		*pBSlash = '\0';

		if(CreateRecursiveDirectory(szDirParent) == S_OK)
		{
			if(!CreateDirectory(szDir, NULL))
			{
				hr = GetLastError();
				break;
			}
		}

	}while(0);

	return hr;
}


BOOL IsLogicalDrive(TCHAR cDrive)
{
	BOOL bRetVal = FALSE;
	TCHAR szLogicalDrives[MAX_PATH_LEN];
	TCHAR cLogicalDrive = toupper(cDrive);
	TCHAR *pLogicalDrive = NULL;
	
	do
	{
		if(!GetLogicalDriveStrings(MAX_PATH_LEN, szLogicalDrives))
			break;

		pLogicalDrive = szLogicalDrives;

		while(pLogicalDrive && *pLogicalDrive)
		{
			if(cLogicalDrive == toupper(*pLogicalDrive))
			{
				bRetVal = TRUE;
				break;
			}

			pLogicalDrive += 4;
		}
	}while(0);

	return bRetVal;
}


BOOL GetDirectory(LPTSTR szDir, LPCTSTR lpszDisplayStr)
{
	BOOL fRet;
	TCHAR szPath[MAX_PATH];
	LPITEMIDLIST pidl;
	LPITEMIDLIST pidlRoot;
	LPMALLOC lpMalloc;

	BROWSEINFO bi;

	bi.hwndOwner = GetFocus();
	bi.pszDisplayName = szPath;
	bi.lpszTitle = lpszDisplayStr;
	bi.ulFlags = BIF_RETURNONLYFSDIRS,
	bi.lpfn = NULL;
	bi.lParam = 0;
	bi.iImage = 0;

	if(SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DRIVES, &pidlRoot) != 0)
		return FALSE;

	if(pidlRoot == NULL)
		return FALSE;

	bi.pidlRoot = pidlRoot;
	pidl = SHBrowseForFolder(&bi);

	if(pidl != NULL)
		fRet = SHGetPathFromIDList(pidl, szDir);
	else
		fRet = FALSE;

	// Get the shell's allocator to free PIDLs
	if(!SHGetMalloc(&lpMalloc) && (lpMalloc != NULL))
	{
		if(pidlRoot != NULL)
			lpMalloc->Free(pidlRoot);

		if(pidl != NULL)
			lpMalloc->Free(pidl);

		lpMalloc->Release();
	}

	return fRet;
}




void ScanUserInput()
{
	MSG msg;
	if(PeekMessage(&msg, g_hAnimateDlg, 0, 0, PM_REMOVE))
		IsDialogMessage(g_hAnimateDlg, &msg);
}


void CreateAnimateDlg(HWND hWndParent, BOOL bEncrypt)
{
	TCHAR szDispText[MAX_PATH];

	if(!g_hAnimateDlg)
		g_hAnimateDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_FILE_ENCRYPT_DECRYPT), 
									 GetForegroundWindow()/*hWndParent*/, (DLGPROC)AnimateDlg);
	if(g_hAnimateDlg)
	{
		ShowWindow(g_hAnimateDlg, SW_SHOWNORMAL);

		if(bEncrypt)
		{
			if(g_LogOn_Off)
				LoadString(g_hInst, IDS_ENCRYPT_LOGOFF, szDispText, MAX_PATH);
			else
				LoadString(g_hInst, IDS_ENCRYPTING, szDispText, MAX_PATH);
		}
		else
		{
			if(g_LogOn_Off)
				LoadString(g_hInst, IDS_DECRYPT_LOGON, szDispText, MAX_PATH);
			else
				LoadString(g_hInst, IDS_DECRYPTING, szDispText, MAX_PATH);
		}

		SetWindowText(g_hAnimateDlg, szDispText);
	}

	g_bCancelled = FALSE;
}


void DestroyAnimateDlg()
{
	if(g_hAnimateDlg)
		DestroyWindow(g_hAnimateDlg);

	g_hAnimateDlg = NULL;
}




BOOL IsSigned(LPCTSTR lpszFilePath)
{
	HANDLE hReadFile = NULL;
	hReadFile = CreateFile(lpszFilePath, GENERIC_READ, FILE_SHARE_READ, 
						   NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		DWORD dwErr = GetLastError();
		TCHAR szErr[MAX_PATH], szFmt[MAX_PATH];

		LoadString(g_hInst, IDS_READ_FILE_ERR, szErr, MAX_PATH);
		wsprintf(szFmt, szErr, lpszFilePath);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szErr, "IsSigned:CreateFile() for \'%s\' failed", lpszFilePath);
		LogErrorMessage(szErr, dwErr);
		return FALSE;
	}

	// The DWORD at the beginning of the file contains the offset of the
	// signature
	DWORD dwSigOffset, dwBytesRead, dwFileSize;
	ReadFile(hReadFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

	dwFileSize = GetFileSize(hReadFile, NULL);

	CloseHandle(hReadFile);

	// No Signature present at the end of file
	if(dwSigOffset == dwFileSize)
		return FALSE;
	else
		return TRUE;
}





// If a single item is selected then check whether it can be encrypted
BOOL CanEncryptSingleSel(LPDATAOBJECT pDataObj)
{
	HRESULT		hr = E_FAIL;
	FORMATETC   fmtetc;
	STGMEDIUM   StgMedium;

	fmtetc.cfFormat   = CF_HDROP;
	fmtetc.ptd        = NULL;
	fmtetc.dwAspect   = DVASPECT_CONTENT;
	fmtetc.lindex     = -1;
	fmtetc.tymed      = TYMED_HGLOBAL;

	hr = pDataObj->GetData(&fmtetc, &StgMedium);
	if(SUCCEEDED(hr))
	{
		TCHAR szSelected[MAX_PATH];
		UINT nFileCnt = DragQueryFile((HDROP)StgMedium.hGlobal, -1, NULL, 0);
		DragQueryFile((HDROP)StgMedium.hGlobal, 0, szSelected, sizeof(szSelected));
		ReleaseStgMedium(&StgMedium);

		// Check if file(s) in the physical Safe directory is selected
		// for encryption. eg if file in 'c:\progra~1\verisign\safe\profilename'
		// is selected then return FALSE
		if(!g_bLockedOut)
			//if(!_strnicmp(szSelected, g_szStoragePath, lstrlen(g_szStoragePath)))
			if(!_strnicmp(szSelected, g_szInstallDir, lstrlen(g_szInstallDir)))
				return FALSE;

		if(nFileCnt > 1)
			return TRUE;	// If multiple files selected then fn CanEncrypt() will check whether file can be encrypted

		if(lstrlen(szSelected) == 3)
			return FALSE;	// root directory
		
		if(!lstrcmpi(szSelected, g_szWinDir) || !lstrcmpi(szSelected, g_szWinSysDir))
			return FALSE;	// system directory

		// check if ext is '.enc'
		TCHAR *pStr = NULL;
		pStr = strrchr(szSelected, '.');
		if(pStr)
		{
			if(!strnicmp(pStr, ".enc", 4))
				return FALSE;
		}

		// Special case, check if the Start menu is the the target for encryption
		TCHAR szSpecialFolder[MAX_PATH];
		LPITEMIDLIST pidlFolder;
		
		IMalloc *pMalloc;
		SHGetMalloc(&pMalloc);

		SHGetSpecialFolderLocation(NULL, CSIDL_COMMON_STARTMENU , &pidlFolder);
		SHGetPathFromIDList(pidlFolder, szSpecialFolder);
		pMalloc->Free(pidlFolder);

		if(!lstrcmpi(szSpecialFolder, szSelected))
		{
		   pMalloc->Release();
		   return FALSE;
		}

		SHGetSpecialFolderLocation(NULL, CSIDL_STARTMENU, &pidlFolder);
		SHGetPathFromIDList(pidlFolder, szSpecialFolder);
		pMalloc->Free(pidlFolder);

		if(!lstrcmpi(szSpecialFolder, szSelected))
		{
		   pMalloc->Release();
		   return FALSE;
		}

		pMalloc->Release();

		return TRUE;

	} // if(SUCCEEDED(hr))

	return FALSE;	
}


BOOL CheckFilterOnFile(LPCTSTR lpFilePath)
{
	DWORD dwAttr = GetFileAttributes(lpFilePath);

	// Attribute check
	if((dwAttr & FILE_ATTRIBUTE_READONLY) && 
	   (g_ExclusionAttr & ATTR_READ_ONLY))
			return TRUE;

	if((dwAttr & FILE_ATTRIBUTE_HIDDEN) && 
	   (g_ExclusionAttr & ATTR_HIDDEN))
			return TRUE;

	if((dwAttr & FILE_ATTRIBUTE_ARCHIVE) && 
	   (g_ExclusionAttr & ATTR_ARCHIVE))
			return TRUE;

	if((dwAttr & FILE_ATTRIBUTE_SYSTEM) && 
	   (g_ExclusionAttr & ATTR_SYSTEM))
			return TRUE;

	// Extension check
	LPCTSTR pItem, pExt = NULL;
	pExt = strchr(lpFilePath, '.');
	if(pExt)
	{
		pItem = g_ExtensionList->GetNextItem(NULL);
		while(pItem)
		{
			if(!lstrcmpi(pItem, pExt) || !lstrcmpi(pItem, pExt + 1))
				return TRUE;

			pItem = g_ExtensionList->GetNextItem(pItem);
		}
	}
	
	// Folder check
	pItem = g_FoldersList->GetNextItem(NULL);
	while(pItem)
	{
		if(IsParentFolder(pItem, lpFilePath))
			return TRUE;

		pItem = g_FoldersList->GetNextItem(pItem);
	}

	return FALSE;
}


BOOL IsParentFolder(LPCSTR lpFolder, LPCTSTR lpFile)
{
	TCHAR szTemp[MAX_PATH], *pBSlash;

	DWORD fAttr = GetFileAttributes(lpFile);

	lstrcpy(szTemp, lpFile);

	if(!(fAttr & FILE_ATTRIBUTE_DIRECTORY))
	{
		pBSlash = strrchr(szTemp, '\\');
		*pBSlash = '\0';
	}

	if(!_strnicmp(lpFolder, szTemp, lstrlen(lpFolder)))
		return TRUE;

	return FALSE;
}


BOOL DeleteEntireKey(HKEY hKey, LPTSTR pszSubKey)
{
	LRESULT lResult;
	HKEY hEnumKey;

	lResult = RegOpenKeyEx(hKey, pszSubKey, 0, KEY_ENUMERATE_SUB_KEYS, &hEnumKey);
	if(NOERROR == lResult)
	{
	   TCHAR szKey[MAX_PATH];
	   DWORD dwSize = MAX_PATH;

	   while(ERROR_SUCCESS == RegEnumKeyEx(hEnumKey, 0, szKey, &dwSize, NULL, NULL, NULL, NULL))
	   {
		  DeleteEntireKey(hEnumKey, szKey);
		  dwSize = MAX_PATH;
	   }

   	   RegCloseKey(hEnumKey);
	}
	else
		return FALSE;

	RegDeleteKey(hKey, pszSubKey);

	return TRUE;
}



void _Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;


	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		DWORD		remainingSize, seventySixCount ;
		PCHAR		inputPtr, outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;
			}
			else
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;
			}
			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
		}
	}

}


void _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	if ( pOutput == NULL )
	{
		PCHAR	filteredInputPtr ;
		int		i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		if(!filteredInputPtr)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
			LogErrorMessage("Base64Decode() : Out of memory", 0);
			return;
		}

		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		*dwOutputSize = filteredCounter ;
		*dwOutputSize = (*dwOutputSize/4)*3 ;

		free(filteredInputPtr) ;
	}
	else
	{
		DWORD		remainingSize ;
		PCHAR		inputPtr, outputPtr, filteredInputPtr ;
		int			i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		if(!filteredInputPtr)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
			LogErrorMessage("Base64Decode() : Out of memory", 0);
			return;
		}

		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		// remainingSize = dwInputSize ;
		remainingSize = filteredCounter ;
		inputPtr = filteredInputPtr ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;

		while((int)remainingSize > 0)
		{
			DWORD tmp, tmpout ;

			_decode(inputPtr[0], &tmpout) ;
			tmp = tmpout ;

			_decode(inputPtr[1], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			_decode(inputPtr[2], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;
				
			_decode(inputPtr[3], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			if ( inputPtr[2] == '=' && inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				*dwOutputSize += 1 ;
			}
			else if ( inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				*dwOutputSize += 2 ;
			}
			else
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				outputPtr[2] = (char)((tmp & 0x000000FF)) ;
				*dwOutputSize += 3 ;
			}

			remainingSize -= 4 ;
			inputPtr += 4 ;
			outputPtr += 3 ;
		}

		free(filteredInputPtr) ;
	}
}


BOOL _decode(short input, DWORD *output)
{
	if ( input >= 'A' && input <= 'Z' )
	{
		*output = input - 'A' ;
		return TRUE ;
	}
	else if ( input >= 'a' && input <= 'z' )
	{
		*output = input - 'a' + 26 ;
		return TRUE ;
	}
	else if ( input >= '1' && input <= '9' )
	{
		*output = input - '1' + 26 + 27 ;
		return TRUE ;
	}
	else if ( input == '0' )
	{
		*output = 26 + 26 ;
		return TRUE ;
	}
	else if ( input == '+' )
	{
		*output = 62 ;
		return TRUE ;
	}
	else if (input == '/' )
	{
		*output = 63 ;
		return TRUE ;
	}
	else if (input == '=' )
	{
		*output = 0 ;
		return TRUE ;
	}
	else
	{
		*output = 0 ;
		return FALSE ;
	}
}


BOOL DeleteCertList(VOID)
{
	LPCertDetails pNextCert = NULL, pCurrCert = NULL;
	
	pCurrCert = g_SafeProp.pCurrEncrCert;
	if(pCurrCert)
	{
		free(pCurrCert);
		g_SafeProp.pCurrEncrCert = NULL;
	}

	pCurrCert = g_SafeProp.pOldEncrCerts;
	while(pCurrCert)
	{
		pNextCert = pCurrCert->pNext;
		free(pCurrCert);
		pCurrCert = pNextCert;
	}

	g_SafeProp.pOldEncrCerts = NULL;

	return TRUE;
}


/* PRRemove
BOOL PasswordPrompt(PasswdPrompt prompt)
{
	TCHAR szMsg[MAX_PATH], szFmt[MAX_PATH];

	if(g_bVeriSignCSP)	// use password mechanism supported
	{					// by the CSP
		if(!g_bLockedOut)
			return TRUE;
	}

	if(g_bLockedOut)
	{
		if(!GetInstallPath())
			return FALSE;

		// Check if user is accessing the properties without selecting a 
		// certificate. i.e. immediately after installation. Do this by 
		// checking if metadata file is present or profile is present
		HANDLE hFind;
		WIN32_FIND_DATA wfd;
		hFind = FindFirstFile(g_szSettingsFile, &wfd);
		if(INVALID_HANDLE_VALUE == hFind)
		{
			DWORD dwSize = 0, dwType;
			HKEY hKey = NULL;
			TCHAR szAppContext[2*MAX_PATH];

			if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_READ, &hKey)
							== ERROR_SUCCESS)
			{
				dwSize = sizeof(szAppContext);
				if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, 
								   (BYTE *)szAppContext, &dwSize) == ERROR_SUCCESS)
				{
					LoadString(g_hInst, IDS_OPEN_SAFE, szFmt, MAX_PATH);
					MessageBox(GetFocus(), szFmt, "Safe", MB_OK);
					RegCloseKey(hKey);
					return FALSE;
				}

				RegCloseKey(hKey);
			}

			LoadString(g_hInst, IDS_NO_IDS_FOR_SAFE, szFmt, MAX_PATH);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK);
			return FALSE;
		}
		else
			FindClose(hFind);

		switch(prompt)
		{
			case SAFE_PROP:
				LoadString(g_hInst, IDS_PASSWD_PROP, szFmt, MAX_PATH);
				break;

			case FILE_PROP:
				LoadString(g_hInst, IDS_PASSWD_FILE, szFmt, MAX_PATH);
				break;

			case ENCRYPT:
				LoadString(g_hInst, IDS_PASSWD_ENCRYPT, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg);
				break;

			case DECRYPT:
				LoadString(g_hInst, IDS_PASSWD_DECRYPT, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg);
				break;

		}

		if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_PASSWD_ENTER), 
			  GetFocus(), (DLGPROC)PasswdAcceptProc, (LPARAM)szFmt) == IDOK)
		{
			if(!VerifyPassword())
				return FALSE;

			if(!InitSafe())
				return FALSE;

			HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

			DecryptAtLogon();

			if(hOldCur)
				SetCursor(hOldCur);

			g_bLockedOut = FALSE;

			UpdateSafeIcon();

			CreateHiddenWindow();

			// If any view were hidden, show them now
			CShellView *pView;
			pView = g_pViewList->GetNextView(NULL);
			while(pView)
			{
				pView->ShowViewWindow();		
				pView = g_pViewList->GetNextView(pView);
			}

			return TRUE;
		}

		return FALSE;
	}

	if(g_LocalPolicy.PasswdMethod == ENCDEC)
	{
		switch(prompt)
		{
			case SAFE_PROP:
				LoadString(g_hInst, IDS_PASSWD_PROP, szFmt, MAX_PATH);
				break;

			case FILE_PROP:
				LoadString(g_hInst, IDS_PASSWD_FILE, szFmt, MAX_PATH);
				break;

			case ENCRYPT:
				LoadString(g_hInst, IDS_PASSWD_ENCRYPT, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg);
				break;

			case DECRYPT:
				LoadString(g_hInst, IDS_PASSWD_DECRYPT, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg);
				break;
		}

		if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_PASSWD_ENTER), 
				GetFocus(), (DLGPROC)PasswdVerifyProc, (LPARAM)szFmt) == IDOK)
			return TRUE;
		else
			return FALSE;
	}
	else
	{
		if(g_LocalPolicy.PasswdMethod == TIMEOUT)
		{
			//if(g_bPasswordPrompt)
			g_CurrentTickCount = GetTickCount();
			if(g_CurrentTickCount == 0)
				g_PreviousTickCount = 0;

			if((g_CurrentTickCount - g_PreviousTickCount) >=
				g_LocalPolicy.PasswordPromptTimeout*60*1000)
			{
				LoadString(g_hInst, IDS_PASSWD_PROMPT_TIMEOUT, szFmt, MAX_PATH);

				if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_PASSWD_ENTER), 
				   GetFocus(), (DLGPROC)PasswdVerifyProc, (LPARAM)szFmt) == IDOK)
				{
					g_bPasswordPrompt = FALSE;
					g_PreviousTickCount = g_CurrentTickCount;
					return TRUE;
				}
				else
					return FALSE;
			}
			else
			{
				// Reset the timeout here as Safe has been accessed either for 
				// encryption/decryption and the callback has not occured yet, so
				// reset the timer.
				g_PreviousTickCount = g_CurrentTickCount;
			}
		}
	}
	
	return TRUE;
}
*/



BOOL PasswordPrompt(PasswdPrompt prompt)
{
	TCHAR szFmt[MAX_PATH];

	if(g_bVeriSignCSP)	// use password mechanism supported by the CSP
	{					
		if(!g_bLockedOut)
			return TRUE;
	}

	if(g_bLockedOut)
	{
		if(!GetInstallPath())
			return FALSE;

		// Check if user is accessing the properties without selecting a 
		// certificate. i.e. immediately after installation. Do this by 
		// checking if metadata file is present or profile is present
		HANDLE hFind;
		WIN32_FIND_DATA wfd;
		hFind = FindFirstFile(g_szSettingsFile, &wfd);
		if(INVALID_HANDLE_VALUE == hFind)
		{
			DWORD dwSize = 0, dwType;
			HKEY hKey = NULL;
			TCHAR szAppContext[2*MAX_PATH];

			if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_READ, &hKey)
							== ERROR_SUCCESS)
			{
				dwSize = sizeof(szAppContext);
				if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, 
								   (BYTE *)szAppContext, &dwSize) == ERROR_SUCCESS)
				{
					LoadString(g_hInst, IDS_OPEN_SAFE, szFmt, MAX_PATH);
					MessageBox(GetFocus(), szFmt, "Safe", MB_OK);
					RegCloseKey(hKey);
					return FALSE;
				}

				RegCloseKey(hKey);
			}

			LoadString(g_hInst, IDS_NO_IDS_FOR_SAFE, szFmt, MAX_PATH);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK);
			return FALSE;
		}
		else
			FindClose(hFind);

		
		if(!VerifyPassword())
			return FALSE;

		if(!InitSafe())
			return FALSE;

		// Get the encryption certificate selected in the global variable
		if(!SelectCert(FALSE))	
			return FALSE;

		HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

		DecryptAtLogon();

		if(hOldCur)
			SetCursor(hOldCur);

		g_bLockedOut = FALSE;

		UpdateSafeIcon();

		CreateHiddenWindow();

		// If any view were hidden, show them now
		CShellView *pView;
		pView = g_pViewList->GetNextView(NULL);
		while(pView)
		{
			pView->ShowViewWindow();		
			pView = g_pViewList->GetNextView(pView);
		}
	}
	
	return TRUE;
}

BOOL CanUnloadDll(VOID)
{
	if(g_bLockedOut)
		return TRUE;
	else
		return FALSE;
}



HTREEITEM GetTreeItemByName(HWND hWnd, HTREEITEM hItem, LPCTSTR szItemName)
{
	TCHAR szBuffer[MAX_PATH];        
	TV_ITEM item;
	HTREEITEM hItemFound;

	// Start from 1st item
	if(hItem == NULL)
		hItem = (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_ROOT, 0);

	while(hItem)
	{
		item.hItem = hItem;
        item.mask = TVIF_TEXT | TVIF_CHILDREN;        
		item.pszText = szBuffer;
        item.cchTextMax = MAX_PATH;
        SendMessage(hWnd, TVM_GETITEM, 0, (LPARAM)&item);
        
		if(!lstrcmp(szBuffer, szItemName))
            return hItem;

		// Check the child items
		if(!lstrcmpi(szBuffer, "Desktop") && item.cChildren)
		{
			hItem = (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, 
										   TVGN_CHILD, (LPARAM)hItem);
			hItemFound = GetTreeItemByName(hWnd, hItem, szItemName);
			if (hItemFound != NULL)                
				return hItemFound;
		}

		// Goto next sibling
		hItem = (HTREEITEM)SendMessage(hWnd, TVM_GETNEXTITEM, TVGN_NEXT, (LPARAM)hItem);
		if(hItem)
		{
			hItemFound = GetTreeItemByName(hWnd, hItem, szItemName);
			if(hItemFound != NULL)                
				return hItemFound;
		}
	}

	return NULL;
}


BOOL ShowHelp(LPCTSTR lpHtmlFile)
{
	TCHAR szExecute[MAX_PATH], *pBSlash = NULL;

	lstrcpy(szExecute, g_LocalPolicy.szRemoteHost);
	if(*(szExecute + lstrlen(szExecute) - 1) != '/')
		lstrcat(szExecute, TEXT("/"));

	if(!lstrcmpi(lpHtmlFile, "ie4_imexid.htm"))
		lstrcat(szExecute, "client/help/tasks/ie4/");
	else
		if(!lstrcmpi(lpHtmlFile, "ie5_impexp.htm"))
			lstrcat(szExecute, "client/help/tasks/ie5/");
		else
			lstrcat(szExecute, "VSApps/client/help/fet/");

	lstrcat(szExecute, lpHtmlFile);

	SHELLEXECUTEINFO sei;
	ZeroMemory(&sei, sizeof(sei));
	sei.cbSize	= sizeof(sei);
	sei.hwnd	= NULL;
	sei.nShow	= SW_SHOWNORMAL;
	sei.lpVerb	= TEXT("open");
	sei.fMask		= 0;
	sei.lpIDList	= 0;
	sei.lpClass		= '\0';
	sei.lpFile		= szExecute;

	ShellExecuteEx(&sei);

	return TRUE;
}


BOOL DecryptFiles(HDROP hSourceFiles)
{
	if(!PasswordPrompt(DECRYPT))
		return FALSE;

	g_bPrompt = TRUE;  // Always set this to TRUE initially

	TCHAR szDecrFile[MAX_PATH], szSelected[MAX_PATH], *pStr;
	TCHAR szFmt[MAX_PATH], szTemp[MAX_PATH], szMsg[MAX_PATH];
	UINT nFileCnt = DragQueryFile(hSourceFiles, -1, NULL, 0);

	CreateAnimateDlg(GetFocus(), 0);

	for(UINT i = 0; i < nFileCnt; i++)
	{
		DragQueryFile(hSourceFiles, i, szSelected, sizeof(szSelected));
		pStr = strrchr(szSelected, '.');
		if(pStr && !_strnicmp(pStr, ".enc", 4))
		{
			lstrcpy(szDecrFile, szSelected);
			pStr = strrchr(szDecrFile, '.');
			*pStr = '\0';

			lstrcpy(szTemp, szSelected);
			pStr = strrchr(szTemp, '\\');
			*pStr = '\0';

			LoadString(g_hInst, IDS_FROM_TO, szMsg, MAX_PATH);
			wsprintf(szFmt, szMsg, szTemp, szTemp);

			SetDlgItemText(g_hAnimateDlg, IDC_FILE_NAME, pStr + 1);
			SetDlgItemText(g_hAnimateDlg, IDC_FROM_TO, szFmt);

			HANDLE hReadFile = CreateFile(szSelected, GENERIC_READ, FILE_SHARE_READ, NULL, 
								  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
			if(hReadFile == INVALID_HANDLE_VALUE)
			{
				DWORD dwErr = GetLastError();
				LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg, szSelected);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
				wsprintf(szMsg, "DecryptAndVerifyFile:CreateFile() for \'%s\' failed", szSelected);
				LogErrorMessage(szMsg, dwErr);
				continue;
			}

			DWORD dwFileSize = GetFileSize(hReadFile, NULL);
			g_dwProgressRange = dwFileSize / MAX_READ_SIZE;

			// File size less than MAX_READ_SIZE
			if(g_dwProgressRange == 0)
				g_dwProgressRange = 1;

			DWORD dwRange = g_dwProgressRange;

			DWORD dwSigOffset, dwBytesRead;
			ReadFile(hReadFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

			// Signature present at the end of file
			if(dwSigOffset != dwFileSize)
				dwRange += g_dwProgressRange;
	
			CloseHandle(hReadFile);

			HWND hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);
			SendMessage(hWndBar, PBM_SETRANGE32, 0, dwRange);
			SendMessage(hWndBar, PBM_SETPOS, 0, 0);
			SendMessage(hWndBar, PBM_SETSTEP, 1, 0);

			SigStatus Stat = VerifySignature(szSelected);	
			if(Stat == SIG_INVALID || Stat == SIG_GEN_FAIL)
			{
				pStr = strrchr(szSelected, '\\');
				LoadString(g_hInst, IDS_VERIFY_FAIL, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg, pStr + 1);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONINFORMATION);
			}

			DecryptStatus DecrStat = DoDecrypt(szSelected, szDecrFile);

			if(DecrStat == DECR_FAIL)
			{
				pStr = strrchr(szSelected, '\\');
				LoadString(g_hInst, IDS_DECRYPT_FAIL, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg, pStr + 1);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONINFORMATION);
			}
			else
				if(DecrStat == DECR_OK)
				{	
					// Delete the '.enc' file if present
					DeleteFile(szSelected);
				}
		}
	}

	DestroyAnimateDlg();

	return TRUE;
}


BOOL CanDecrypt(LPDATAOBJECT pDataObj)
{
	HRESULT		hr = E_FAIL;
	FORMATETC   fmtetc;
	STGMEDIUM   StgMedium;

	fmtetc.cfFormat   = CF_HDROP;
	fmtetc.ptd        = NULL;
	fmtetc.dwAspect   = DVASPECT_CONTENT;
	fmtetc.lindex     = -1;
	fmtetc.tymed      = TYMED_HGLOBAL;

	hr = pDataObj->GetData(&fmtetc, &StgMedium);
	if(SUCCEEDED(hr))
	{
		TCHAR szSelected[MAX_PATH], *pStr;
		UINT nFileCnt = DragQueryFile((HDROP)StgMedium.hGlobal, -1, NULL, 0);

		for(UINT i = 0; i < nFileCnt; i++)
		{
			DragQueryFile((HDROP)StgMedium.hGlobal, i, szSelected, sizeof(szSelected));
			pStr = strrchr(szSelected, '.');
			if(pStr && !_strnicmp(pStr, ".enc", 4))
				continue;
			else
				break;
		}

		ReleaseStgMedium(&StgMedium);

		if(i < nFileCnt)
			return FALSE;
		else
			return TRUE;
	}

	return FALSE;
}


/*
BOOL RestorePassword(VOID)
{
	TCHAR szPasswdFile[MAX_PATH] = {0}, szDecrFile[MAX_PATH], szFmt[MAX_PATH];
	TCHAR szMsg[MAX_PATH];
	DWORD dwBytesRead = 0, dwErr = 0;
	BOOL bSuccess = FALSE, bRetVal = FALSE;
	HANDLE hReadFile = NULL, hWriteFile = NULL, hDecrFile = NULL;

	if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_RECOVER_PASSWORD), GetFocus(), 
				  (DLGPROC)RecoverPasswordProc, (LPARAM)szPasswdFile) == IDCANCEL)
			return FALSE;

	if(!(*szPasswdFile))
		return FALSE;

	// Decrypt the Password file, then verify the dfedata using the 
	// hash obtained from the passwd file, prompt user to change passwd
	hReadFile = CreateFile(szPasswdFile, GENERIC_READ, 0, NULL, 
						   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		hReadFile = NULL;
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, szPasswdFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "RestorePassword : CreateFile() \'%s\' failed.", szPasswdFile);
		LogErrorMessage(szMsg, dwErr);
		goto CleanUp;
	}

	if(!GetTemporaryFile(szDecrFile))
	{
		DisplayMessage(GetFocus(), IDS_TEMP_FILE_ERR, MB_OK | MB_ICONERROR);
		goto CleanUp;
	}

	hWriteFile = CreateFile(szDecrFile, GENERIC_WRITE, 0, NULL, 
							CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hWriteFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		hWriteFile = NULL;
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, szDecrFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "RestorePassword : CreateFile() \'%s\' failed.", szDecrFile);
		LogErrorMessage(szMsg, dwErr);
		goto CleanUp;
	}

	CMSG_STREAM_INFO StreamInfo;
	memset(&StreamInfo, 0, sizeof(CMSG_STREAM_INFO));

	StreamInfo.cbContent		= GetFileSize(hReadFile, NULL);
	StreamInfo.pfnStreamOutput	= StreamOutputCallback;
	StreamInfo.pvArg			= hWriteFile;

	ULONG ulCryptoError, ulDecryptContext;
	TCHAR cReadBuf[MAX_READ_SIZE];
	
	if(DecryptStart(NULL, &ulDecryptContext, &StreamInfo, &ulCryptoError) == S_OK)
	{
		while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
		{
			if(dwBytesRead == MAX_READ_SIZE)
			{
				if(DecryptUpdate(ulDecryptContext, (BYTE *)cReadBuf, 
								 dwBytesRead, &ulCryptoError) != S_OK)
					break;
			}
			else
			{
				if(DecryptEnd(ulDecryptContext, (BYTE *)cReadBuf, dwBytesRead,
							  &ulCryptoError) == S_OK)
					bSuccess = TRUE;

				break;
			}
		}
	}

	if(!bSuccess)			// This handle was not closed by the
	{						// stream callback
		CloseHandle(hWriteFile);
		goto CleanUp;		
	}

	// Read the password hash from the decrypted file
	hDecrFile = CreateFile(szDecrFile, GENERIC_READ, 0, NULL, 
						   OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDecrFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		hDecrFile = NULL;
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, szDecrFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "RestorePassword : CreateFile() \'%s\' failed.", szDecrFile);
		LogErrorMessage(szMsg, dwErr);
		goto CleanUp;
	}

	g_PasswdHash.dwLen = GetFileSize(hDecrFile, NULL);
	if(g_PasswdHash.dwLen > 1024)
	{
		LogErrorMessage("RestorePassword() : Password hash greater than expected", 0);
		goto CleanUp;
	}

	ReadFile(hDecrFile, g_PasswdHash.pbHash, g_PasswdHash.dwLen, &dwBytesRead, NULL);

	if(!VerifyPassword())
		DisplayMessage(GetFocus(), IDS_PASSWD_FILE_ERR, MB_OK | MB_ICONERROR);
	else
	{
		DisplayMessage(GetFocus(), IDS_TOKEN_IMPORTED, MB_OK | MB_ICONINFORMATION);


		if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_NEW_PASSWD), GetFocus(),
				  (DLGPROC)NewPasswordProc, IDS_RECOVER_PASSWD) == IDOK)
			bRetVal = TRUE;
	}

CleanUp:

	if(hDecrFile)
		CloseHandle(hDecrFile);
	
	DeleteFile(szDecrFile);

	if(hReadFile)
		CloseHandle(hReadFile);

	return bRetVal;
}
*/


/*
BOOL CreatePasswordFile(VOID)
{
	BOOL bRetVal = FALSE;
	TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH], szAdminCertificate[4096];
	DWORD dwErr = 0, dwDetachedSigLen = 0, dwDecodedAdminCert = 0;
	PSIGN_CONTEXT pSignContext = NULL;
	PBYTE pbDetachedSig = NULL, pbDecodedAdminCert = NULL;
	HCRYPTPROV hCryptProv = NULL;
	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam;
	CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm;
	CMSG_STREAM_INFO StreamInfo;
	ULONG EncryptContext;
	HCERTSTORE hMemCertStore = NULL;
	PCERT_CONTEXT pCertContext = NULL;

	do
	{
		// Check if the Admin cert is present if not then read it from policy file
		if(g_LocalPolicy.dwCertLen == 0)
		{
			if(!ReadPolicyFileVar("FileEncryption", "AdminCert", 
						  (UINT *)szAdminCertificate, TRUE))
				break;
			else
			{
				g_LocalPolicy.dwCertLen = lstrlen(szAdminCertificate);
				memcpy(g_LocalPolicy.AdminCert, szAdminCertificate, g_LocalPolicy.dwCertLen);
			}
		}

		// Sign hash of password using current encryption cert. First
		// get the certificate context
		if(!g_SafeProp.pCurrEncrCert)
		{
			LogErrorMessage("CreatePasswordFile() : No encryption cert selected", 0);
			break;
		}

		if(SignStart(currSelCert.pCertContext, szOID_RSA_MD5, &pSignContext, &dwErr) != S_OK)
			break;

		if(SignEnd(pSignContext, (PBYTE)g_PasswdHash.pbHash, g_PasswdHash.dwLen, &dwErr,
				   &pbDetachedSig, &dwDetachedSigLen) != S_OK)
			break;

		// Now encrypt the pasword hash using the Admin cert
		_Base64Decode((char *)g_LocalPolicy.AdminCert, g_LocalPolicy.dwCertLen, NULL, &dwDecodedAdminCert);
		if(!dwDecodedAdminCert)
		{
			LogErrorMessage("CreatePasswordFile() : Base64 decode failed", 0);
			break;
		}

		pbDecodedAdminCert = (BYTE *)malloc(dwDecodedAdminCert);
		if(!pbDecodedAdminCert)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("CreatePasswordFile() : Out of memory", 0);
			break;
		}

		_Base64Decode((char *)g_LocalPolicy.AdminCert, g_LocalPolicy.dwCertLen, (char *)pbDecodedAdminCert, &dwDecodedAdminCert);

		hMemCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, 0, NULL);
		if(!hMemCertStore)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CreatePasswordFile() : CertOpenStore failed", dwErr);
			break;
		}

		if(!CertAddEncodedCertificateToStore(hMemCertStore, MY_ENCODING_TYPE, (const BYTE *)pbDecodedAdminCert,
				dwDecodedAdminCert, CERT_STORE_ADD_NEW, (PCCERT_CONTEXT*)&pCertContext))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CreatePasswordFile:CertAddEncodedCertificateToStore() failed.", dwErr);
			break;
		}

		if(pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData >= 128)
		{
			// The Admin cert has a 1024 bit key try to acquire enhanced provider
			if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, 
									PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_SERVICE_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("CreatePasswordFile:Enhanced provided not supported on your machine.", dwErr);
				break;
			}
		}
		else
		{
			// The Admin cert has a 512 bit key try to acquire default provider
			if(!CryptAcquireContext(&hCryptProv, NULL, MS_DEF_PROV, 
									PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_SERVICE_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("CreatePasswordFile:Base provided not supported on your machine.", dwErr);
				break;
			}
		}

		memset(&EncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));
		memset(&EncryptAlgorithm, 0, sizeof(EncryptAlgorithm));

		EncryptAlgorithm.pszObjId = szOID_RSA_RC4;

		EncryptParam.cbSize = sizeof(CRYPT_ENCRYPT_MESSAGE_PARA);
		EncryptParam.dwMsgEncodingType = MY_ENCODING_TYPE;
		EncryptParam.ContentEncryptionAlgorithm = EncryptAlgorithm;
		EncryptParam.hCryptProv = hCryptProv;

		HANDLE hPasswdFile = CreateFile(g_szTokenFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
									FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hPasswdFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
			wsprintf(szFmt, szMsg, g_szTokenFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "CreatePasswordFile() : CreateFile() failed for \'%s\'", g_szTokenFile);
			LogErrorMessage(szMsg, dwErr);
			break;
		}	

				
		memset(&StreamInfo, 0, sizeof(CMSG_STREAM_INFO));
		StreamInfo.cbContent = sizeof(DWORD) + g_PasswdHash.dwLen + 
							   dwDetachedSigLen;
		StreamInfo.pfnStreamOutput = StreamOutputCallback;
		StreamInfo.pvArg = hPasswdFile;

		if(EncryptStart(&EncryptParam, &StreamInfo, &EncryptContext, 
						pCertContext, &dwErr) == S_OK)
		{
			EncryptUpdate(EncryptContext, (BYTE *)&g_PasswdHash.dwLen, sizeof(DWORD),
						  &dwErr);
			EncryptUpdate(EncryptContext, g_PasswdHash.pbHash, g_PasswdHash.dwLen,
						  &dwErr);
			EncryptEnd(EncryptContext, pbDetachedSig, dwDetachedSigLen,
					   &dwErr);
		}

		bRetVal = TRUE;
		
	} while(0);


	if(pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
		pCertContext = NULL;
	}

	if(hMemCertStore)
	{
		CertCloseStore(hMemCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
		hMemCertStore = NULL;
	}

	if(pbDecodedAdminCert)
	{
		free(pbDecodedAdminCert);
		pbDecodedAdminCert = NULL;
	}

	if(pbDetachedSig)
	{
		free(pbDetachedSig);
		pbDetachedSig = NULL;
	}

	if(hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
		hCryptProv = NULL;
	}

	return bRetVal;
}
*/


BOOL UpdateSafeIcon(VOID)
{
	TCHAR szModuleFile[MAX_PATH];
	UINT nOldIconIndex = 0;

	GetModuleFileName(g_hInst, szModuleFile, MAX_PATH);

	if(g_bLockedOut)
		nOldIconIndex = 4; // the open Safe icon
	else
		nOldIconIndex = 0; // the close Safe icon

	// Get the icon index of the Safe icon in the SystemImageList
	LPSHELLFOLDER pShellFolder;
	LPENUMIDLIST pEnumIDList = NULL;
	LPITEMIDLIST pItem = NULL;
	IMalloc *pMalloc;
	STRRET sName;
	TCHAR szPath[MAX_PATH], szExtName[MAX_PATH];
	ULONG ulFetched = 0;

	LoadString(g_hInst, IDS_EXT_TITLE, szExtName, sizeof(szExtName));

	SHGetMalloc(&pMalloc);
	SHGetDesktopFolder(&pShellFolder);
	pShellFolder->EnumObjects(NULL, SHCONTF_FOLDERS, &pEnumIDList);
	while(pEnumIDList->Next(1, &pItem, &ulFetched) == NOERROR)
	{
		pShellFolder->GetDisplayNameOf(pItem, 0, &sName);
		GetTextFromSTRRET(NULL, &sName, pItem, szPath, MAX_PATH);
		if(!lstrcmpi(szPath, szExtName))
			break;

		pMalloc->Free(pItem);
		continue;
	}

	pEnumIDList->Release();
	pShellFolder->Release();

	SHFILEINFO sfInfo;
	memset(&sfInfo, 0, sizeof(SHFILEINFO));
	SHGetFileInfo((LPCTSTR)pItem, 0, &sfInfo, sizeof(sfInfo), SHGFI_PIDL | SHGFI_SYSICONINDEX);

	pMalloc->Free(pItem);
	pMalloc->Release();

	// Calls the SHUpdateImage() function to update the Safe icon. This fn
	// is not called by name as it is not documented for all versions of 
	// Windows. It is called by the ordinal number. This fn was given 
	// by Microsoft technical support.
	//UpdateCachedImage(szModuleFile, nOldIconIndex, sfInfo.iIcon);

	// use SHChangeNotify by itself if we can't do anything else
	SHChangeNotify(SHCNE_UPDATEIMAGE, SHCNF_DWORD | SHCNF_FLUSH | SHCNF_FLUSHNOWAIT, 
				   (LPCVOID)sfInfo.iIcon, NULL);

	// Update the registry icon number
	HKEY hKey;
	LRESULT lResult;
	TCHAR szCLSID[MAX_PATH], szKeyName[MAX_PATH];
	LPWSTR pwsz;

	// Get the CLSID in string form
	StringFromIID(CLSID_VSSafe, &pwsz);
	WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

	lstrcpy(szKeyName, "CLSID\\");
	lstrcat(szKeyName, szCLSID);
	lstrcat(szKeyName, "\\DefaultIcon");

	lResult = RegOpenKeyEx(HKEY_CLASSES_ROOT, szKeyName, 0, 
						   KEY_ALL_ACCESS, &hKey);
	if(lResult == ERROR_SUCCESS)
	{
		if(g_bLockedOut)
			lstrcat(szModuleFile, ",0");
		else
			lstrcat(szModuleFile, ",4");

		RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szModuleFile, 
					  (lstrlen(szModuleFile) + 1) * sizeof(TCHAR));
		RegCloseKey(hKey);
	}

	return TRUE;
}



BOOL IsUserFile(LPCTSTR lpszParentFolder, LPCTSTR lpszFileName)
{
	// The recovery file is also to be excluded if it is in
	// the Safe directory
        /*
	HKEY hKey = NULL;
	TCHAR szValue[MAX_PATH], szRecoveryFile[MAX_PATH];
	if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_QUERY_VALUE, 
					&hKey) == ERROR_SUCCESS)
	{
		DWORD dwType, dwSize = MAX_PATH;
		if(RegQueryValueEx(hKey, "RecoveryFile", NULL, &dwType, (LPBYTE)szValue, 
						   &dwSize) == ERROR_SUCCESS)
		{
			lstrcpy(szRecoveryFile, lpszParentFolder);
			SmartAppendBackslash(szRecoveryFile);
			lstrcat(szRecoveryFile, lpszFileName);
		}

		RegCloseKey(hKey);

		if(!lstrcmpi(szRecoveryFile, szValue))
			return FALSE;
	}
        */

	if(!lstrcmpi(lpszFileName, "fileinfo") ||
	   !lstrcmpi(lpszFileName, "vsettings_decr") ||
	   !lstrcmpi(lpszFileName, "vsettings") ||
	   !lstrcmpi(lpszFileName, "vsettings.bak") ||	
	   !lstrcmpi(lpszFileName, "vstoken.req") ||
	   !lstrcmpi(lpszFileName, POLICY_FILE))
		return FALSE;
	else
		return TRUE;
}


BOOL LogIn(BOOL bPasswdPrompt)
{
	CShellView *pView;

	if(bPasswdPrompt)
	{
		LoginStat State = AuthenticateUser();
		if(State == LOGIN_CANCEL || State == LOGIN_INVALID)
		{
			pView = g_pViewList->GetNextView(NULL);
			while(pView)
			{
				pView->HideViewWindow();		
				pView = g_pViewList->GetNextView(pView);
			}

			return FALSE;
		}
	}

	HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	DecryptAtLogon();

	if(hOldCur)
		SetCursor(hOldCur);

	g_bLockedOut = FALSE;

	UpdateSafeIcon();

	CreateHiddenWindow();

	pView = g_pViewList->GetNextView(NULL);
	while(pView)
	{
		pView->ShowViewWindow();		
		pView = g_pViewList->GetNextView(pView);
	}

	return TRUE;
}


BOOL LogOut(VOID)
{
	CShellView *pView;

	if(!UpdateSafe())
		return FALSE;

	HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	EncryptAtLogoff();

	if(hOldCur)
		SetCursor(hOldCur);

	if(!g_DumpPolicyFile)
		DeleteFile(g_szPolicyFile);

	// Delete the global certificate list which contains the encryption and
	// signing certificates
	DeleteCertList();

	if(g_nTimerId)
	{
		KillTimer(NULL, g_nTimerId);
		g_nTimerId = 0;
	}

	g_EncrAtLogoffList->DeleteList();
	g_DecrAtLogonList->DeleteList();
	g_ExtensionList->DeleteList();
	g_FoldersList->DeleteList();

	g_bLockedOut = TRUE;

	UpdateSafeIcon();

	DestroyHiddenWindow();

	pView = g_pViewList->GetNextView(NULL);
	while(pView)
	{
		//pView->BrowseToRoot();
		pView->CollapseTree();
#if 0
		pView->BrowseToDesktop();
#else
		pView->HideViewWindow();		
#endif
		pView = g_pViewList->GetNextView(pView);
	}

	if(g_bVeriSignCSP)
	{
		g_pProfMgmt->CloseProfile();
		g_pProfMgmt->Release();
		g_pProfMgmt = NULL;
		g_bVeriSignCSP = FALSE;
	}

	return TRUE;
}



// Following is code got from Microsoft technical support for updating
// namespace extension icon which appear on the desktop and in the 
// Windows explorer
typedef VOID (STDAPICALLTYPE *PFNSHUPDATEIMAGE_A)(LPCSTR pszModule, int
iIndex, UINT uFlags, int iImageIndex);
typedef VOID (STDAPICALLTYPE *PFNSHUPDATEIMAGE_W)(LPCWSTR pszModule, int
iIndex, UINT uFlags, int iImageIndex);
 
#ifdef UNICODE
	#define PFNSHUPDATEIMAGE   PFNSHUPDATEIMAGE_W
	#define SHUPDATEIMAGE_ORD  192
#else
	#define PFNSHUPDATEIMAGE   PFNSHUPDATEIMAGE_A
	#define SHUPDATEIMAGE_ORD  191
#endif
 
VOID UpdateCachedImage(LPCTSTR pszOldModule, int nOldModuleIndex, int nOldImageListIndex)
{
	DWORD dwMajor;
	DWORD dwMinor;
	TCHAR szShell32[MAX_PATH];

	lstrcpy(szShell32, g_szWinSysDir);
	SmartAppendBackslash(szShell32);
	lstrcat(szShell32, "shell32.dll");
 
	if(GetFileVersion(szShell32, &dwMajor, &dwMinor))
    {
		if(!((4 == dwMajor) && (0 == dwMinor)))
		{
			//try to use the SHUpdateImage function
			HINSTANCE   hShell32 = LoadLibrary(TEXT("shell32.dll"));
			if(hShell32)
			{
				PFNSHUPDATEIMAGE  pfnShUpdateImage =
						(PFNSHUPDATEIMAGE)GetProcAddress(hShell32, (LPSTR)SHUPDATEIMAGE_ORD);
 
				if(pfnShUpdateImage)
				{
					TCHAR szOldModule[MAX_PATH];
					LPTSTR pszFile;
 
					if(!*pszOldModule)
						goto FreeTheLib;
 
					lstrcpyn(szOldModule, pszOldModule, MAX_PATH);

					//take care of any trailing backslash
					if('\\' == szOldModule[lstrlen(szOldModule) - 1])
					{
						szOldModule[lstrlen(szOldModule) - 1] = 0;
					}
             
					for(pszFile = szOldModule + lstrlen(szOldModule) - 1; pszFile > szOldModule; pszFile--)
					{
						if('\\' == *pszFile)
						{
							pszFile++;
							break;
						}
					}
             
					(*pfnShUpdateImage)(pszFile, nOldModuleIndex, 0, nOldImageListIndex);
             }


FreeTheLib:
	          FreeLibrary(hShell32);
		      return;
          }
       }
    }
 
	//use SHChangeNotify by itself if we can't do anything else
	SHChangeNotify(SHCNE_UPDATEIMAGE, SHCNF_DWORD | SHCNF_FLUSH | SHCNF_FLUSHNOWAIT, 
                   (LPCVOID)nOldImageListIndex, NULL);
}



BOOL GetFileVersion(LPTSTR lpszFileName, DWORD *pdwMajor, DWORD *pdwMinor)
{
	DWORD dwSize, dwInput;
	void *pFileVersion = NULL;

	dwSize = GetFileVersionInfoSize(lpszFileName, &dwInput);
	if(dwSize)
	{
		pFileVersion = malloc(dwSize);
		if(!pFileVersion)
			return FALSE;

		if(!GetFileVersionInfo(lpszFileName, 0, dwSize, pFileVersion))
		{
			free(pFileVersion);
			return FALSE;
		}

		VS_FIXEDFILEINFO *pFileInfo;
		UINT dwVersionSize;
		VerQueryValue(pFileVersion, "\\", (LPVOID*)&pFileInfo,
					  &dwVersionSize);

		if(!pFileInfo)
		{
			free(pFileVersion);
			return FALSE;
		}

		*pdwMajor = pFileInfo->dwFileVersionMS;
		*pdwMinor = pFileInfo->dwFileVersionLS;
	}

	free(pFileVersion);
	return TRUE;
}


// The desktop window is not the one visible to the user. The user sees a list view which is a 
// child of the desktop window. This fn determines whether the list view window is the same as the
// 'hWnd' parameter
BOOL IsDesktopWindow(HWND hWnd)
{
	HWND hWndShellDefault;
	HWND hWndChild = FindWindowEx(GetDesktopWindow(), NULL, "Progman", NULL);
	if(hWndChild)
	{
		hWndShellDefault = FindWindowEx(hWndChild, NULL, "SHELLDLL_DefView", NULL);
		if(hWndShellDefault)
			hWndChild = FindWindowEx(hWndShellDefault, NULL, "SysListView32", NULL);

		if(hWndChild == hWnd)
			return TRUE;
		else
		{
			// For Active Desktop check for Internet Explorer_Server
			// rather than "SysListView32"
  			hWndChild = FindWindowEx(hWndShellDefault, NULL, "Internet Explorer_Server", NULL);
			if(hWndChild && hWndChild == hWnd)
				return TRUE;
		}
	}

	return FALSE;
}


// Check if 'hTree' is a drop target. If TRUE then return the absolute path the drop target.
// Assuming that the tree view contains folders and ':' cannot be part of a file/folder name. 
// Assuming that drop is on the explorer tree view.
BOOL GetTreePath(HWND hTree, LPSTR lpszPath)
{
	TCHAR szItemPath[MAX_PATH], *pStr;
	HTREEITEM hItem;
	TVITEM selItem;
	BOOL bRetVal = FALSE;
	lpszPath[0] = '\0';

	hItem = TreeView_GetDropHilight(hTree);
	if(!hItem)
		return FALSE;

	do
	{
		memset(&selItem, 0, sizeof(selItem));
		selItem.mask = TVIF_TEXT;
		selItem.hItem = hItem;
		selItem.pszText = szItemPath;
		selItem.cchTextMax = sizeof(szItemPath);

		if(TreeView_GetItem(hTree, &selItem))
		{
			// If 'szItemPath' contains ':' then stop the loop. 
			pStr = strchr(szItemPath, ':');
			if(pStr)
			{
				*pStr = '\0';
				pStr--;	// point to volume name
				lstrcat(lpszPath, ":");
				lstrcat(lpszPath, pStr);
				_strrev(lpszPath);

				bRetVal = TRUE;
				break;
			}
			else
			{
				_strrev(szItemPath);
				lstrcat(lpszPath, szItemPath);
				lstrcat(lpszPath, "\\");
			}
		}
		else
			break;

		hItem = TreeView_GetParent(hTree, hItem);
	}
	while(hItem);
	
	return bRetVal;
}


VOID SetAnimateDlgText(LPCSTR lpszEncryptedFile, LPCSTR lpszDecryptedFile)
{
	TCHAR *pBSlash = NULL, szFrom[MAX_PATH], szTo[MAX_PATH];
	pBSlash = strrchr(lpszEncryptedFile, '\\');
	SetDlgItemText(g_hAnimateDlg, IDC_FILE_NAME, pBSlash + 1);

	LoadString(g_hInst, IDS_FROM, szFrom, MAX_PATH);
	LoadString(g_hInst, IDS_TO, szTo, MAX_PATH);

	// Construct the From .... To ... string
	TCHAR szTemp[MAX_PATH], szFromTo[MAX_PATH];
	lstrcpy(szTemp, g_szExtTitle);
	lstrcat(szTemp, &lpszEncryptedFile[lstrlen(g_szStoragePath)]);

	pBSlash = strrchr(szTemp, '\\');
	if(pBSlash)
		*pBSlash = '\0';

	wsprintf(szFromTo, "%s \'%s\' %s \'", szFrom, szTemp, szTo);

	lstrcpy(szTemp, lpszDecryptedFile);
	pBSlash = strrchr(szTemp, '\\');
	if(pBSlash)
		*pBSlash = '\0';

	lstrcat(szFromTo, szTemp);
	lstrcat(szFromTo, "'");

	SetDlgItemText(g_hAnimateDlg, IDC_FROM_TO, szFromTo);

	return;
}


// Determines whether File/Folder pointed by 'lpszSource' is present
// in 'lpszDest' directory
BOOL IsFileFolderPresent(LPCTSTR lpszSource, LPCTSTR lpszDest)
{
	TCHAR *pStr;
	pStr = strrchr(lpszSource, '\\');

	if(!pStr)
		return FALSE;

	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR szTemp[MAX_PATH];

	lstrcpy(szTemp, lpszDest);
	lstrcat(szTemp, pStr);

	hFind = FindFirstFile(szTemp, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		return TRUE;
	}

	return FALSE;
}


// Determines if all the files represented by the section names in this fileinfo
// file have been decrypted. If so the fileinfo is no longer needed.
BOOL CanDeleteFileInfo(LPCSTR lpszFileInfo)
{
	TCHAR szSectionNames[SECTION_NAME_SIZE], *pSectionName;

	if(GetPrivateProfileSectionNames(szSectionNames, SECTION_NAME_SIZE,
									 lpszFileInfo) == SECTION_NAME_SIZE - 2)
	{
		LogErrorMessage("CanDeleteFileInfo() : GetPrivateProfileSectionNames() size exceeded", 0);
		return FALSE;
	}

	pSectionName = szSectionNames;

	if(!*pSectionName)
		return FALSE;

	while(*pSectionName)
	{
		// Skip the general section as this is not related to a file.
		// What if there is a file named 'general' ???
		if(lstrcmpi(pSectionName, "General"))
		{
			FileStatus Status = (FileStatus)GetPrivateProfileInt(pSectionName, "Status", DELETED, lpszFileInfo);

			if(Status == ENCRYPTED)
				return FALSE;
		}				

		pSectionName += lstrlen(pSectionName) + 1;
	} // end while	

	return TRUE;
}


// Get file path lengths of all files in 'lpszPath' which are not ENCRYPTED
VOID GetDecryptedFilePathSize(LPCSTR lpszPath, UINT *puPathSize)
{
	// Check if 'fileinfo' file is present. If not present assume all files
	// in this directory have been decrypted
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR szTemp[MAX_PATH], szFileInfo[MAX_PATH], *pStr;
	BOOL bFileInfoPresent = FALSE;	

	lstrcpy(szFileInfo, lpszPath);
	SmartAppendBackslash(szFileInfo);
	lstrcat(szFileInfo, "fileinfo");

	hFind = FindFirstFile(szFileInfo, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		bFileInfoPresent = TRUE;
	}

	lstrcpy(szTemp, lpszPath);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));
	hFind = FindFirstFile(szTemp, &wfd);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT(".")) && 
			   lstrcmpi(wfd.cFileName, TEXT("..")) &&
			   IsUserFile(lpszPath, wfd.cFileName))
			{
				//build the path of the directory or file found
				lstrcpy(szTemp, lpszPath);
				SmartAppendBackslash(szTemp);
				lstrcat(szTemp, wfd.cFileName);

				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					//we found a directory - call this function recursively
					GetDecryptedFilePathSize(szTemp, puPathSize);
				}
				else
				{
					// If 'fileinfo' file is present check if the file is DECRYPTED
					if(bFileInfoPresent)
					{
						pStr = strrchr(szTemp, '\\') + 1; // point to filename
						FileStatus Status = (FileStatus)GetPrivateProfileInt(pStr, "Status", DELETED, szFileInfo);
						if(Status == ENCRYPTED)
							continue;
					}

					*puPathSize += lstrlen(szTemp) + 1; // Add one for NULL terminator
				}
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}	
}


// Get file path of all files in 'lpszPath' which are not ENCRYPTED.
// These are stored in 'lpszPathInfo'
VOID GetDecryptedPaths(LPCSTR lpszPath, LPSTR lpszPathInfo)
{
	// Check if 'fileinfo' file is present. If not present assume all files
	// in this directory have been decrypted
	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR szTemp[MAX_PATH], szFileInfo[MAX_PATH], *pStr, *pPathInfo;
	BOOL bFileInfoPresent = FALSE;	

	pPathInfo = lpszPathInfo;

	lstrcpy(szFileInfo, lpszPath);
	SmartAppendBackslash(szFileInfo);
	lstrcat(szFileInfo, "fileinfo");

	hFind = FindFirstFile(szFileInfo, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		bFileInfoPresent = TRUE;
	}

	lstrcpy(szTemp, lpszPath);
	SmartAppendBackslash(szTemp);
	lstrcat(szTemp, TEXT("*.*"));
	hFind = FindFirstFile(szTemp, &wfd);

	if(INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT(".")) && 
			   lstrcmpi(wfd.cFileName, TEXT("..")) &&
			   IsUserFile(lpszPath, wfd.cFileName))
			{
				//build the path of the directory or file found
				lstrcpy(szTemp, lpszPath);
				SmartAppendBackslash(szTemp);
				lstrcat(szTemp, wfd.cFileName);

				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					//we found a directory - call this function recursively
					GetDecryptedPaths(szTemp, pPathInfo);
				}
				else
				{
					// If 'fileinfo' file is present check if the file is DECRYPTED
					if(bFileInfoPresent)
					{
						pStr = strrchr(szTemp, '\\') + 1; // point to filename
						FileStatus Status = (FileStatus)GetPrivateProfileInt(pStr, "Status", DELETED, szFileInfo);
						if(Status == ENCRYPTED)
							continue;
					}

					lstrcpy(pPathInfo, szTemp);
					pPathInfo += lstrlen(szTemp) + 1; // Add one for NULL terminator
				}
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}	
}



VOID RefreshAllViews(BOOL bCheckOrigLocation)
{
	CShellView *pView;
	pView = g_pViewList->GetNextView(NULL);
	while(pView)
	{
		pView->DeleteListViewItems();
		pView->FillList(bCheckOrigLocation);
		pView = g_pViewList->GetNextView(pView);
	}
}



BOOL LogErrorMessage(LPCTSTR lpszErrorMessage, UINT ulWinError)
{
	// Check if registry contains the error logging flag
	TCHAR szMsg[MAX_PATH], szFmt[MAX_PATH];
	DWORD dwErr;
	HKEY hKey;
	LRESULT lResult;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, 
						   KEY_READ, &hKey);
	if(lResult != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_REG_OPEN, szMsg, MAX_PATH);
		wsprintf(szFmt, "LogErrorMessage() : %s : %s , %d", szMsg, MAIN_KEY_STRING, dwErr);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	DWORD dwType, dwLog, dwSize = sizeof(DWORD);

	RegQueryValueEx(hKey, "LogErrorMessage", NULL, &dwType,
					(LPBYTE)&dwLog, &dwSize);
	if(dwLog)
	{
		TCHAR szLogFile[MAX_PATH];
		if(!GetTempPath(MAX_PATH, szLogFile))
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_TEMP_PATH_ERR, szMsg, MAX_PATH);
			wsprintf(szFmt, "LogErrorMessage() : %s , %d", szMsg, dwErr);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			RegCloseKey(hKey);
			return FALSE;
		}

		lstrcat(szLogFile, "fetlog.txt");

		HANDLE hLogFile = NULL;
		hLogFile = CreateFile(szLogFile, GENERIC_WRITE, FILE_SHARE_READ,
							  NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);

		if(hLogFile == INVALID_HANDLE_VALUE)
		{
			LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_PATH);
			wsprintf(szFmt, szMsg, szLogFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			RegCloseKey(hKey);
			return FALSE;
		}

		// If file size > 1MB truncate it
		if(GetFileSize(hLogFile, NULL) > 1024*1024)
			SetEndOfFile(hLogFile);

		// Seek to end and error write information. This includes
		// logged in user, date, time, error message and window
		// error number
		SetFilePointer(hLogFile, 0, NULL, FILE_END);

		TCHAR szUserName[MAX_PATH], szCurrTime[MAX_PATH];
		TCHAR szError[2*MAX_PATH];
		DWORD dwSize = MAX_PATH, dwBytesWritten;
		SYSTEMTIME SysTime;
		FILETIME ft;

		if(!GetUserName(szUserName, &dwSize))
			lstrcpy(szUserName, "default");

		GetSystemTime(&SysTime);
		SystemTimeToFileTime(&SysTime, &ft);
		GetDisplayTime(&ft, szCurrTime, TRUE);

		wsprintf(szError, "%s : %s : %s : %x\r\n", szUserName, szCurrTime, lpszErrorMessage, ulWinError);

		WriteFile(hLogFile, szError, lstrlen(szError), &dwBytesWritten, NULL);

		CloseHandle(hLogFile);
	}

	RegCloseKey(hKey);

	return TRUE;
}


/* PRRemove
// Check if the Admin key can be imported by the end user CSP. This is 
// needed to support password recovery
BOOL CanUseAdminCertificate(VOID)
{
	TCHAR szAdminCertificate[4096];
	if(g_LocalPolicy.dwCertLen == 0)
	{
		if(!ReadPolicyFileVar("FileEncryption", "AdminCert", 
						  (UINT *)szAdminCertificate, TRUE))
			return FALSE;
		else
		{
			g_LocalPolicy.dwCertLen = lstrlen(szAdminCertificate);
			memcpy(g_LocalPolicy.AdminCert, szAdminCertificate, g_LocalPolicy.dwCertLen);
		}
	}

	BYTE *pbDecodedCert = NULL;
	HCRYPTPROV hCryptProv = NULL;
	DWORD dwDecodedCert = 0, dwErr;
	PCCERT_CONTEXT pCertContext = NULL;
	HCERTSTORE hCertStore = NULL;
	BOOL bRetVal = FALSE;
	
	hCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, 0, NULL);
	if(!hCertStore)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("CanUseAdminCertificate:CertOpenStore() failed.", dwErr);
		goto CleanUp;
	}

	_Base64Decode((char *)g_LocalPolicy.AdminCert, g_LocalPolicy.dwCertLen, NULL, &dwDecodedCert);

	pbDecodedCert = (BYTE *)malloc(dwDecodedCert);
	if(pbDecodedCert)
		_Base64Decode((char *)g_LocalPolicy.AdminCert, g_LocalPolicy.dwCertLen, (char *)pbDecodedCert, &dwDecodedCert);

	if(!CertAddEncodedCertificateToStore(hCertStore, MY_ENCODING_TYPE, (const BYTE *)pbDecodedCert,
		dwDecodedCert, CERT_STORE_ADD_NEW, &pCertContext))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("CanUseAdminCertificate:CertAddEncodedCertificateToStore() failed.", dwErr);
		goto CleanUp;
	}

	if(pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData >= 128)
	{
		// The Admin cert has a 1024 bit key try to acquire enhanced provider
		if(!CryptAcquireContext(&hCryptProv, NULL, MS_ENHANCED_PROV, 
								PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_SERVICE_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CanUseAdminCertificate:Enhanced provided not supported on your machine.", dwErr);
			goto CleanUp;
		}
	}
	else
	{
		// The Admin cert has a 512 bit key try to acquire default provider
		if(!CryptAcquireContext(&hCryptProv, NULL, MS_DEF_PROV, 
								PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_SERVICE_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CanUseAdminCertificate:Base provided not supported on your machine.", dwErr);
			goto CleanUp;
		}
	}

	bRetVal = TRUE;

CleanUp:

	if(pCertContext)
		CertFreeCertificateContext(pCertContext);

	if(hCertStore)
		CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);

	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(pbDecodedCert)
		free(pbDecodedCert);

	return bRetVal;
}
*/


// Check if this folder can be added to the list of folders to be 
// displayed. A folder should not be added if it contains only 
// decrypted files
BOOL CanAddFolderToEnumList(LPCSTR lpszFolder)
{

	HANDLE hFind;
	WIN32_FIND_DATA wfd;

	TCHAR szPath[MAX_PATH];
	BOOL bRetVal = FALSE;
		
	lstrcpy(szPath, lpszFolder);
	SmartAppendBackslash(szPath);
	lstrcat(szPath, TEXT("*.*"));

	hFind = FindFirstFile(szPath, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT(".")) && 
			   lstrcmpi(wfd.cFileName, TEXT("..")) &&
			   IsUserFile(lpszFolder, wfd.cFileName))
			{
				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					TCHAR szTempPath[MAX_PATH];
					lstrcpy(szTempPath, lpszFolder);
					SmartAppendBackslash(szTempPath);
					lstrcat(szTempPath, wfd.cFileName);

					bRetVal = CanAddFolderToEnumList(szTempPath);
					if(bRetVal)
						break;
				}
			}
			else
			{
				// File is present
				bRetVal = TRUE;
				break;
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

		return bRetVal;
}



// Checks if 'lpszFolder' only exists in the Safe to show the
// recently decrypted files. 
BOOL IsFolderPresent(LPCTSTR lpszFolder)
{
	TCHAR szFileInfo[MAX_PATH], szPath[MAX_PATH];
	BOOL bRetVal = FALSE;

	lstrcpy(szFileInfo, lpszFolder);
	lstrcat(szFileInfo, "\\fileinfo");

	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	hFind = FindFirstFile(szFileInfo, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);

		TCHAR szSectionNames[SECTION_NAME_SIZE], *pSectionName;

		if(GetPrivateProfileSectionNames(szSectionNames, SECTION_NAME_SIZE,
									 szFileInfo) == SECTION_NAME_SIZE - 2)
		{
			LogErrorMessage("AddDecryptedContents() : GetPrivateProfileSectionNames() size exceeded", 0);
			return FALSE;
		}

		pSectionName = szSectionNames;
		while(*pSectionName)
		{
			// Skip the general section as this is not related to a file.
			// What if there is a file named 'general' ???
			if(lstrcmpi(pSectionName, "General"))
			{
				FileStatus Status = (FileStatus)GetPrivateProfileInt(pSectionName, "Status", DELETED, szFileInfo);

				if(Status == ENCRYPTED)
					return TRUE;
			}				

			pSectionName += lstrlen(pSectionName) + 1;
		} // end while	
	}

	// If no 'fileinfo' or the 'fileinfo' contains only decrypted
	// files repeat the process for other folders as the folder can
	// be present just bcos there are other folders in it
	lstrcpy(szPath, lpszFolder);
	SmartAppendBackslash(szPath);
	lstrcat(szPath, TEXT("*.*"));

	hFind = FindFirstFile(szPath, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if(lstrcmpi(wfd.cFileName, TEXT(".")) && 
			   lstrcmpi(wfd.cFileName, TEXT("..")) &&
			   IsUserFile(lpszFolder, wfd.cFileName))
			{
				if(FILE_ATTRIBUTE_DIRECTORY & wfd.dwFileAttributes)
				{
					TCHAR szTempPath[MAX_PATH];
					lstrcpy(szTempPath, lpszFolder);
					SmartAppendBackslash(szTempPath);
					lstrcat(szTempPath, wfd.cFileName);

					bRetVal = IsFolderPresent(szTempPath);
					if(bRetVal)
						break;
				}
				else
				{
					// A file is present return TRUE
					bRetVal = TRUE;
					break;
				}
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}

	return bRetVal;
}



BOOL SelectCert(BOOL bUI)
{
	VARIANT varAppName, varHostName, varUseCapi, varCertContext;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSSelectedDigID *pSelDigID = NULL;
	HRESULT hr;
	BOOL bRetVal = FALSE, bProfilePresent = FALSE;
	TCHAR szDisplayText[MAX_PATH], *pStr = NULL, *lpAppName = NULL;
	TCHAR *lpUserName = NULL, szAppContext[2*MAX_PATH];
	WCHAR wsz[2*MAX_PATH];
	IVSPTA *pVSPTA = NULL;
	DWORD dwError = 0, dwSize = 0, dwType;
	DATE ExpiryDate;
	UDATE uDate;
	FILETIME ft;
	VARIANT var;
	HKEY hKey = NULL;

	VariantInit(&varCertContext);

	do
	{
		CoInitialize(NULL);
		
		hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, 
							  IID_IVSPTA,(void**)&pVSPTA);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:CoCreateInstance for CLSID_VSPTA failed", hr);
			break;
		}
	
		// Check if registry entry for profile path exists. If present
		// use that AppName to initialize PTA else use some default name
		if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_QUERY_VALUE, 
						&hKey) == ERROR_SUCCESS)
		{
			dwSize = 2*MAX_PATH;
			if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, (LPBYTE)szAppContext, 
							   &dwSize) == ERROR_SUCCESS)
				bProfilePresent = TRUE;
		}

		if(bProfilePresent)
		{
			/*if(!ParseProfilePath(szProfilePath, &lpAppName, &lpUserName))
				break;*/

			if(!MultiByteToWideChar(CP_ACP, 0, szAppContext, -1, wsz, 2*MAX_PATH))
				break;

			varAppName.vt = VT_BSTR;
			varAppName.bstrVal = SysAllocString(wsz);
		}
		else
		{
			varAppName.vt = VT_BSTR;
			varAppName.bstrVal = SysAllocString(L"FET");
		}

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = 1;	// '1' Use CAPI = YES

		hr = pVSPTA->Initialize(&varAppName, &varUseCapi);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:VSPTA init failed", hr);
			break;
		}
		VariantClear(&varAppName);

		hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:QueryInterface() for PTADLLApi failed", hr);
			break;
		}

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = L"localhost";
			
		hr = pPTADllApi->put_HostFQDN(varHostName);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:put_HostFQDN() failed", hr);
			break;
		}
		
		// Get the issuer DN to be set as a cert selection criteria
		// Read the policy file to get the 'ptaIssuerDN', so that
		// we can set the proper certificate selection criteria
		if(!ReadPolicyFileVar("GlobalVar", "ptaIssuerDN", (UINT *)&g_LocalPolicy.szIssuerDN, TRUE))
			break;

		if(!SetCertSelectionCriteria(bUI, pVSPTA))
			break;

		if(bUI)
		{
			hr = pVSPTA->SelIDForChallenge();

			if(hr == E_USERCANCELLED)
				break;
		}
		else
			hr = pVSPTA->SelIDForTrans();

		if(hr != S_OK)
		{
			if(hr == E_CERTNOTFOUND)
			{
				if(bUI)
				{
					LoadString(g_hInst, IDS_INSTALL_DIGID, szDisplayText, sizeof(szDisplayText));
					if(MessageBox(GetFocus(), szDisplayText, "Safe", MB_YESNO | MB_ICONQUESTION) == IDYES)
						GetCertificate();
				}
				else
				{
					LoadString(g_hInst, IDS_DIGID_REMOVED, szDisplayText, sizeof(szDisplayText));
					MessageBox(GetFocus(), szDisplayText, "Safe", MB_ICONERROR);
				}
			}
			else
			{
				MessageBox(GetFocus(), "Select Digital ID failed", "Safe", MB_OK);
				LogErrorMessage("SelectCert:SelID() failed", hr);
			}

			break;
		}

		// Get certificate context and other details 
		// of the selected digital ID
		hr = pVSPTA->get_IVSSelectedDigID((IDispatch**)&pSelDigID);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:get_IVSSelectedDigID() failed", hr);
			break;
		}

		hr = pSelDigID->get_IssuerDN(&var);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:get_IssuerDN() failed", hr);
			break;
		}

		pStr = _WideToMultiString(var.bstrVal);
		VariantClear(&var);
		if(!pStr)
		{
			LogErrorMessage("SelectCert:_WideToMultiString() failed", 0);
			break;
		}
		lstrcpy(currSelCert.szIssuerDN, pStr);
		free(pStr);
		pStr = NULL;

		hr = pSelDigID->get_SerNum(&var);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:get_SerNum() failed", hr);
			break;
		}

		pStr = _WideToMultiString(var.bstrVal);
		VariantClear(&var);
		if(!pStr)
		{
			LogErrorMessage("SelectCert:_WideToMultiString() failed", 0);
			break;
		}
		lstrcpy(currSelCert.szSerialNum, pStr);
		free(pStr);

		hr = pSelDigID->get_ExpDate(&ExpiryDate);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:get_ExpDate() failed", hr);
			break;
		}
	
		VarUdateFromDate(ExpiryDate, 0, &uDate);
		SystemTimeToFileTime(&uDate.st, &ft);
		currSelCert.ft = ft;		

		if(currSelCert.pCertContext)
		{
			CertFreeCertificateContext(currSelCert.pCertContext);
			currSelCert.pCertContext = NULL;
		}

		if(currSelCert.hMemCertStore)
		{
			CertCloseStore(currSelCert.hMemCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
			currSelCert.hMemCertStore = NULL;
		}

		currSelCert.hMemCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, 0, NULL);
		if(!currSelCert.hMemCertStore)
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert() : CertOpenStore() failed", dwError);
			break;
		}

		hr = pPTADllApi->get_SelectedIDCertContext(&varCertContext);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert:get_SelectedIDCertContext() failed", hr);
			break;
		}

		if(!CertAddSerializedElementToStore(currSelCert.hMemCertStore, (const BYTE *)varCertContext.parray->pvData,
			varCertContext.parray->rgsabound[0].cElements, CERT_STORE_ADD_NEW, 0, 
			CERT_STORE_CERTIFICATE_CONTEXT_FLAG , NULL, (const void**)&currSelCert.pCertContext))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SelectCert() : CertAddSerializedElementToStore() failed", dwError);
		}

		if(!IsCertInVSCSP(pPTADllApi))
			break;

		bRetVal = TRUE;

	} while(0);


	VariantClear(&varCertContext);

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(lpAppName)
	{
		free(lpAppName);
		lpAppName = NULL;
	}

	if(lpUserName)
	{
		free(lpUserName);
		lpUserName = NULL;
	}

	if(pSelDigID)
	{
		pSelDigID->Release();
		pSelDigID = NULL;
	}

	if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	if(pVSPTA)
	{
//		pVSPTA->Close();
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	CoUninitialize();

	return bRetVal;
}


BOOL ChangeCertificate(VOID)
{
	VARIANT varAppName, varHostName, varUseCapi, varCertContext;
	HRESULT hr;
	BOOL bRetVal = FALSE, bChangeCert = FALSE;
	HKEY hKey = NULL;
	IVSPTA *pVSPTA = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSSelectedDigID *pSelDigID = NULL;
	DWORD dwSize = 0, cbData = 0, dwType = 0, dwError = 0;
	TCHAR *lpUserName = NULL, *lpAppName = NULL, *pStr = NULL;
	TCHAR /*szProfilePath[2*MAX_PATH]*/szAppContext[2*MAX_PATH], szDisplayText[MAX_PATH];
	WCHAR wsz[2*MAX_PATH];
	HCERTSTORE hMemCertStore = NULL;
	PCERT_CONTEXT pCertContext = NULL;
	PCRYPT_KEY_PROV_INFO pvData = NULL;
	LPSTR lpszContainerName = NULL, lpszProviderName = NULL;
	INT nSameProfile;
	DATE ExpiryDate;
	UDATE uDate;
	FILETIME ft;
	VARIANT var;

	VariantInit(&varCertContext);

	do
	{
		CoInitialize(NULL);
		
		hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, 
							  IID_IVSPTA,(void**)&pVSPTA);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:CoCreateInstance for CLSID_VSPTA failed", hr);
			break;
		}

		if(g_bVeriSignCSP)
		{
			if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_QUERY_VALUE, 
							&hKey) != ERROR_SUCCESS)
			{
				dwError = GetLastError();
				DisplayMessage(GetFocus(), IDS_REG_OPEN, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:RegOpenKeyEx() failed", dwError);
				break;
			}
			
			dwSize = 2*MAX_PATH;
			if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, (LPBYTE)szAppContext, 
							   &dwSize) != ERROR_SUCCESS)
			{
				dwError = GetLastError();
				DisplayMessage(GetFocus(), IDS_REG_READ_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:RegQueryValueEx() failed", dwError);
				break;
			}
			
			if(!MultiByteToWideChar(CP_ACP, 0, szAppContext, -1, wsz, 2*MAX_PATH))
				break;

			varAppName.vt = VT_BSTR;
			varAppName.bstrVal = SysAllocString(wsz);
		}
		else
		{
			varAppName.vt = VT_BSTR;
			varAppName.bstrVal = SysAllocString(L"FET");
		}

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = 1;	// '1' Use CAPI = YES

		hr = pVSPTA->Initialize(&varAppName, &varUseCapi);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:VSPTA init failed", hr);
			break;
		}
		VariantClear(&varAppName);

		hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:QueryInterface() for PTADLLApi failed", hr);
			break;
		}

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = L"localhost";
			
		hr = pPTADllApi->put_HostFQDN(varHostName);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:put_HostFQDN() failed", hr);
			break;
		}
		
		// Get the issuer DN to be set as a cert selection criteria
		// Read the policy file to get the 'ptaIssuerDN', so that
		// we can set the proper certificate selection criteria
		if(!ReadPolicyFileVar("GlobalVar", "ptaIssuerDN", (UINT *)&g_LocalPolicy.szIssuerDN, TRUE))
			break;

		if(!SetCertSelectionCriteria(TRUE, pVSPTA))
			break;

		hr = pVSPTA->SelIDForChallenge();

		if(hr == E_USERCANCELLED)
			break;

		if(hr != S_OK)
		{
			if(hr == E_CERTNOTFOUND)
			{
				LoadString(g_hInst, IDS_INSTALL_DIGID, szDisplayText, sizeof(szDisplayText));
				if(MessageBox(GetFocus(), szDisplayText, "Safe", MB_YESNO | MB_ICONQUESTION) == IDYES)
					GetCertificate();
			}
			else
			{
				MessageBox(GetFocus(), "Select Digital ID error", "Safe", MB_OK);
				LogErrorMessage("ChangeCertificate:SelID() failed", hr);
			}

			break;
		}

		hr = pPTADllApi->get_SelectedIDCertContext(&varCertContext);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:get_SelectedIDCertContext() failed", hr);
			break;
		}

		hMemCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, 0, NULL);
		if(!hMemCertStore)
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate() : CertOpenStore() failed", dwError);
			break;
		}

		if(!CertAddSerializedElementToStore(hMemCertStore, (const BYTE *)varCertContext.parray->pvData,
			varCertContext.parray->rgsabound[0].cElements, CERT_STORE_ADD_NEW, 0, 
			CERT_STORE_CERTIFICATE_CONTEXT_FLAG , NULL, (const void**)&pCertContext))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate() : CertAddSerializedElementToStore() failed", dwError);
		}

		if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  NULL, &cbData))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:CertGetCertificateContextProperty() failed", dwError);
			break;
		}

		pvData = (PCRYPT_KEY_PROV_INFO)malloc(cbData);
		if(!pvData)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ChangeCertificate() : Out of memory", 0);
			break;
		}

		if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  (void*)pvData,  &cbData))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("ChangeCertificate:CertGetCertificateContextProperty() failed", dwError);
			break;
		}

		lpszProviderName = _WideToMultiString(pvData->pwszProvName);
		if(!lpszProviderName)
		{
			LogErrorMessage("ChangeCertificate:_WideToMultiString() failed", 0);
			hr = S_FALSE;
			break;
		}

		lpszContainerName = _WideToMultiString(pvData->pwszContainerName);
		if(!lpszContainerName)
		{
			LogErrorMessage("ChangeCertificate:_WideToMultiString() failed", 0);
			hr = S_FALSE;
			break;
		}

		// if old cert is in MSCSP and new one also is in MSCSP then 
		// no prompting needed, this is the simplest case...
		if(!g_bVeriSignCSP && lstrcmpi(CSP_NAME, lpszProviderName) != 0)
			bChangeCert = TRUE;
		else
			// old cert in MSCSP and new one in VSCSP
			if(!g_bVeriSignCSP && !lstrcmpi(CSP_NAME, lpszProviderName))
			{
				/* PRRemove
				if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_CHANGE_CERT),
					GetActiveWindow(), (DLGPROC)ChangeCertProc, 0) == IDOK)
				{*/
					if(OpenUserProfile(pCertContext))
					{
						// Delete the metadata file in the Safe
						// as now we have switched to VeriSign mode
						if(g_szSettingsFile[0] != '\0')
							DeleteFile(g_szSettingsFile);

						g_bVeriSignCSP = TRUE;
						bChangeCert = TRUE;
					}
				//}
			}
			else
				// old cert in VSCSP and new in MSCSP
				if(g_bVeriSignCSP && lstrcmpi(CSP_NAME, lpszProviderName) != 0)
				{
					/* PRRemove
					if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_CHANGE_CERT),
						GetActiveWindow(), (DLGPROC)ChangeCertProc, 1) == IDOK)
					{
						// Show the NewPassword dialog
						if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_NEW_PASSWD), GetFocus(),
								 (DLGPROC)NewPasswordProc, IDS_ENTER_SAFE_PASSWD) == IDOK)
						{*/
							// Close the profile now
							if(UpdateSafe())
							{							
								g_pProfMgmt->CloseProfile();
								g_pProfMgmt->Release();
								g_pProfMgmt = NULL;

								// Delete the registry entry as we are
								// switching from VeriSign mode to MSCSP mode
								if(hKey)
									RegCloseKey(hKey);

								if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_ALL_ACCESS, 
												&hKey) != ERROR_SUCCESS)
								{
									dwError = GetLastError();
									LogErrorMessage("ChangeCertificate:RegOpenKeyEx() failed", dwError);
								}
								else
								{
									if(RegDeleteValue(hKey, FET_APP_CONTEXT) != ERROR_SUCCESS)
									{
										dwError = GetLastError();
										LogErrorMessage("ChangeCertificate:RegOpenKeyEx() failed", dwError);
									}
								}
								
								g_bVeriSignCSP = FALSE;
								bChangeCert = TRUE;
							}
						//}
					//}
				}
				else
				{
					// old in VSCSP and new also in VSCSP, check if
					// certs are in same profile
					nSameProfile = CompareProfiles(lpszContainerName);
					if(!nSameProfile)
					{
						/* PRRemove
						if(DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_CHANGE_CERT),
							GetActiveWindow(), (DLGPROC)ChangeCertProc, 2) == IDOK)
						{*/
							if(UpdateSafe())
							{
								g_pProfMgmt->CloseProfile();
								g_pProfMgmt->Release();
								g_pProfMgmt = NULL;

								// Open new profile
								if(OpenUserProfile(pCertContext))
									bChangeCert = TRUE;
							}
						//}
					}
					else
						if(nSameProfile)
							bChangeCert = TRUE;
				}


		if(bChangeCert)
		{
			// put new context in the global cert context var
			if(currSelCert.pCertContext)
			{
				CertFreeCertificateContext(currSelCert.pCertContext);
				currSelCert.pCertContext = NULL;
			}

			if(currSelCert.hMemCertStore)
			{
				CertCloseStore(currSelCert.hMemCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
				currSelCert.hMemCertStore = NULL;
			}

			currSelCert.hMemCertStore = CertOpenStore(CERT_STORE_PROV_MEMORY, 0, NULL, 0, NULL);
			if(!currSelCert.hMemCertStore)
			{
				dwError = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate() : CertOpenStore() failed", dwError);
				break;
			}

			if(!CertAddSerializedElementToStore(currSelCert.hMemCertStore, (const BYTE *)varCertContext.parray->pvData,
				varCertContext.parray->rgsabound[0].cElements, CERT_STORE_ADD_NEW, 0, 
				CERT_STORE_CERTIFICATE_CONTEXT_FLAG , NULL, (const void**)&currSelCert.pCertContext))
			{
				dwError = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate() : CertAddSerializedElementToStore() failed", dwError);
			}

			// Get certificate context and other details 
			// of the selected digital ID
			hr = pVSPTA->get_IVSSelectedDigID((IDispatch**)&pSelDigID);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:get_IVSSelectedDigID() failed", hr);
				break;
			}

			hr = pSelDigID->get_IssuerDN(&var);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:get_IssuerDN() failed", hr);
				break;
			}

			pStr = _WideToMultiString(var.bstrVal);
			VariantClear(&var);
			if(!pStr)
			{
				LogErrorMessage("ChangeCertificate:_WideToMultiString() failed", 0);
				break;
			}
			lstrcpy(currSelCert.szIssuerDN, pStr);
			free(pStr);
			pStr = NULL;

			hr = pSelDigID->get_SerNum(&var);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:get_SerNum() failed", hr);
				break;
			}

			pStr = _WideToMultiString(var.bstrVal);
			VariantClear(&var);
			if(!pStr)
			{
				LogErrorMessage("ChangeCertificate:_WideToMultiString() failed", 0);
				break;
			}
			lstrcpy(currSelCert.szSerialNum, pStr);
			free(pStr);

			hr = pSelDigID->get_ExpDate(&ExpiryDate);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("ChangeCertificate:get_ExpDate() failed", hr);
				break;
			}
	
			VarUdateFromDate(ExpiryDate, 0, &uDate);
			SystemTimeToFileTime(&uDate.st, &ft);
			currSelCert.ft = ft;		

			bRetVal = TRUE;
		}

	} while(0);

	VariantClear(&varCertContext);

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(lpszContainerName)
	{
		free(lpszContainerName);
		lpszContainerName = NULL;
	}

	if(lpszProviderName)
	{
		free(lpszProviderName);
		lpszProviderName = NULL;
	}

	if(pvData)
	{
		free(pvData);
		pvData = NULL;
	}

	if(pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
		pCertContext = NULL;
	}

	if(hMemCertStore)
	{
		CertCloseStore(hMemCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
		hMemCertStore = NULL;
	}

	if(lpAppName)
	{
		free(lpAppName);
		lpAppName = NULL;
	}

	if(lpUserName)
	{
		free(lpUserName);
		lpUserName = NULL;
	}

	if(pSelDigID)
	{
		pSelDigID->Release();
		pSelDigID = NULL;
	}

	if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	if(pVSPTA)
	{
//		pVSPTA->Close();
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	CoUninitialize();

	return bRetVal;
}


BOOL GetPTAProfileInfo(LPCSTR lpszContainerName, LPTSTR szProfilePath, DWORD dwProfilePathSize,
		LPTSTR lpszClientInfo, DWORD dwClientInfoSize, LPTSTR lpszClientInfoSig, 
		DWORD dwClientInfoSigSize, BOOL *bProfileType)
{
	TCHAR szQueryString[2*MAX_PATH];
	HKEY hKey = NULL;
	DWORD dwErr = 0, dwSize = 0, dwType = 0;

	*szProfilePath = '\0';
	*lpszClientInfo = '\0';
	*lpszClientInfoSig = '\0';
	*bProfileType = NON_ROAMING;

	// Read profile path from registry
	lstrcpy(szQueryString, PTA_KEY);
	lstrcat(szQueryString, "\\");
	lstrcat(szQueryString, lpszContainerName);

	// Use container name to read registry
	if(RegOpenKeyEx(HKEY_CURRENT_USER, szQueryString, 0, KEY_QUERY_VALUE, 
					&hKey) != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_READ_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetPTAProfileInfo:RegOpenKeyEx() failed", dwErr);
		return FALSE;
	}

	dwSize = dwProfilePathSize;
	if(RegQueryValueEx(hKey, PROFILE_NAME, NULL, &dwType, (LPBYTE)szProfilePath, 
					   &dwSize) != ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_READ_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetPTAProfileInfo:RegReadValueEx() failed", dwErr);
		RegCloseKey(hKey);
		return FALSE;
	}

	dwSize = dwClientInfoSize;
	if(RegQueryValueEx(hKey, CLIENT_INFO, NULL, &dwType, (LPBYTE)lpszClientInfo, 
					   &dwSize) == ERROR_SUCCESS)
	{
		dwSize = dwClientInfoSigSize;
		if(RegQueryValueEx(hKey, CLIENT_INFO_SIG, NULL, &dwType, (LPBYTE)lpszClientInfoSig, 
						   &dwSize) == ERROR_SUCCESS)
			*bProfileType = ROAMING;
	}

	RegCloseKey(hKey);

	return TRUE;
}


// returns '0' if profiles are different
//		   '1' if profiles are same
//		  '-1' if some error occured
INT CompareProfiles(LPCSTR lpszNewContainerName)
{
	INT nRetVal = -1;
	DWORD dwErr = 0;
	ULONG nSize = 0;
	PCRYPT_KEY_PROV_INFO pKeyProv = NULL;
	TCHAR szNewProfileName[2*MAX_PATH], szCurrProfileName[2*MAX_PATH];
	TCHAR szClientInfo[CLIENT_INFO_LEN], szClientInfoSig[CLIENT_INFO_SIG_LEN];
	LPSTR lpszCurrContainerName = NULL;
	BOOL bIsRoaming;

	do
	{
		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  NULL, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CompareProfiles:CertGetCertificateContextProperty() failed", dwErr);
			break;
		}

		pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
		if(!pKeyProv)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("CompareProfiles() : Out of memory", 0);
			break;
		}
		
		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  pKeyProv, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("CompareProfiles:CertGetCertificateContextProperty() failed", dwErr);
			break;
		}
			
		lpszCurrContainerName = _WideToMultiString(pKeyProv->pwszContainerName);

		if(!GetPTAProfileInfo(lpszCurrContainerName, szCurrProfileName, sizeof(szCurrProfileName), szClientInfo, sizeof(szClientInfo),
						szClientInfoSig, sizeof(szClientInfoSig), &bIsRoaming))
			break;

		if(!GetPTAProfileInfo(lpszNewContainerName, szNewProfileName, sizeof(szNewProfileName), szClientInfo, sizeof(szClientInfo),
							  szClientInfoSig, sizeof(szClientInfoSig), &bIsRoaming))
			break;

		if(!lstrcmpi(szNewProfileName, szCurrProfileName))
			nRetVal = 1;
		else
			nRetVal = 0;

		break;
		
	} while(0);

	if(lpszCurrContainerName)
	{
		free(lpszCurrContainerName);
		lpszCurrContainerName = NULL;
	}

	if(pKeyProv)
	{
		free(pKeyProv);
		pKeyProv = NULL;
	}

	return nRetVal;
}



BOOL UpdateListOfCerts(VOID)
{
	LPCertDetails *pCurrCert = NULL, *pOldCertList = NULL;
	BOOL bRetVal = FALSE;
	TCHAR *pToSign = NULL;
	BYTE *pbDetachedSig = NULL;
	DWORD dwDetachedSigLen = 0, dwError = 0;
	ULONG ulCryptErr = 0;
	PSIGN_CONTEXT pSignContext = NULL;

	do
	{
		pCurrCert = &g_SafeProp.pCurrEncrCert;
		pOldCertList  = &g_SafeProp.pOldEncrCerts;

		if(*pCurrCert)
		{
			// Add current certificate to the old list
			(*pCurrCert)->pNext = *pOldCertList;
			*pOldCertList = *pCurrCert;
		}

		*pCurrCert = (LPCertDetails)malloc(sizeof(CertDetails));
		if(!*pCurrCert)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("UpdateListOfCerts() : Out of memory", 0);
			break;
		}

		(*pCurrCert)->dwSigLen = 0;
		(*pCurrCert)->pNext = NULL;
	
		lstrcpy((*pCurrCert)->szIssuerDN, currSelCert.szIssuerDN);
		lstrcpy((*pCurrCert)->szSerialNum, currSelCert.szSerialNum);
		(*pCurrCert)->ftExpiryDate = currSelCert.ft;

		// Now sign the IDN and SN using the certificate selected
		if(SignStart(currSelCert.pCertContext, szOID_RSA_MD5, &pSignContext, &ulCryptErr) != S_OK)
			break;

		pToSign = (TCHAR *)malloc(lstrlen((*pCurrCert)->szSerialNum) + lstrlen((*pCurrCert)->szIssuerDN) + 1);
		if(!pToSign)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("UpdateListOfCerts() : Out of memory", 0);
			break;
		}

		lstrcpy(pToSign, (*pCurrCert)->szSerialNum);
		lstrcat(pToSign, (*pCurrCert)->szIssuerDN);

		if(SignEnd(pSignContext, (PBYTE)pToSign, lstrlen(pToSign), &ulCryptErr,
				   &pbDetachedSig, &dwDetachedSigLen) != S_OK)
			break;

		(*pCurrCert)->dwSigLen = dwDetachedSigLen;
		memcpy((*pCurrCert)->Signature, (const char *)pbDetachedSig, dwDetachedSigLen);
		(*pCurrCert)->pNext = NULL;

		bRetVal = TRUE;

	} while(0);

	if(pbDetachedSig)
	{
		free(pbDetachedSig);
		pbDetachedSig = NULL;
	}

	if(pToSign)
	{
		free(pToSign);
		pToSign = NULL;
	}

	return bRetVal;
}



BOOL IsCertInVSCSP(IVSPTADllApi *pPTADllApi)
{
	DWORD dwError = 0, cbData = 0;;
	BOOL bRetVal = FALSE;
	PCRYPT_KEY_PROV_INFO pvData = NULL;
	LPSTR lpszProviderName = NULL;

	do
	{
		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  NULL, &cbData))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("IsCertInVSCSP:CertGetCertificateContextProperty() failed", dwError);
			break;
		}

		pvData = (PCRYPT_KEY_PROV_INFO)malloc(cbData);
		if(!pvData)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("IsCertInVSCSP() : Out of memory", 0);
			break;
		}

		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  (void*)pvData,  &cbData))
		{
			dwError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("IsCertInVSCSP:CryptMsgUpdate() failed", dwError);
			break;
		}

		lpszProviderName = _WideToMultiString(pvData->pwszProvName);
		if(!lpszProviderName)
		{
			LogErrorMessage("IsCertInVSCSP:_WideToMultiString() failed", 0);
			break;
		}

		if(!lstrcmpi(lpszProviderName, CSP_NAME))
			g_bVeriSignCSP = TRUE;
		else
			g_bVeriSignCSP = FALSE;

		bRetVal = TRUE;

	} while(0);


	if(lpszProviderName)
	{
		free(lpszProviderName);
		lpszProviderName = NULL;
	}

	if(pvData)
	{
		free(pvData);
		pvData = NULL;
	}

	return bRetVal;
}



BOOL OpenUserProfile(PCCERT_CONTEXT pCertContext)
{
	HRESULT hr;
	BOOL bRetVal = FALSE;
	IVSPTA *pVSPTA = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSUIPrefs *pIVSUIPref = NULL;
	IVSRoamPrefs *pRoamPrefs = NULL;
	VARIANT varUserName, varAppName, varHostName, varUseCapi;
	VARIANT varOpenProfFlag, varRoamProfile, varSaveLocal, varOpenProfTitle;
	TCHAR szProfilePath[MAX_PATH_LEN], szAppContext[MAX_PATH_LEN], szMsg[MAX_MSG_LEN];
	TCHAR *lpszContainerName = NULL;
	TCHAR *lpAppName = NULL, *lpUserName = NULL;
	WCHAR wsz[MAX_PATH_LEN];
	ULONG nSize = 0;
	PCRYPT_KEY_PROV_INFO pKeyProv = NULL;
	HKEY hKey = NULL;
	DWORD dwSize = 0, dwErr = 0, dwDisp = 0;
	BOOL bIsProfileInfoPresent, bProfileType;
	TCHAR szClientInfo[CLIENT_INFO_LEN], szClientInfoSig[CLIENT_INFO_SIG_LEN];

	VariantInit(&varOpenProfTitle);

	CoInitialize(NULL); // Don't know where to do the CoUninitialize() for this
	do
	{
		hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSPTA,(void**)&pVSPTA);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:CoCreateInstance for CLSID_VSPTA failed", hr);
			break;
		}

		hr = pVSPTA->get_IVSProfMgmt((IDispatch**)&g_pProfMgmt);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:get_IVSProfMgmt for CLSID_VSProfMgmt failed", hr);
			break;
		}

		hr = pVSPTA->get_IVSUIPrefs((IDispatch**)&pIVSUIPref);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:get_IVSUIPrefs for CLSID_VSUIPrefs failed", hr);
			break;
		}

		if(!pCertContext)
		{
			if(!GetFETProfileInfo(&bIsProfileInfoPresent, &bProfileType, szAppContext, sizeof(szAppContext),
						  szClientInfo, sizeof(szClientInfo), szClientInfoSig, sizeof(szClientInfoSig)))
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:GetFETProfileInfo() failed", hr);
				break;
			}
		}
		else
		{
			// Cert selected for first time. Get container name from
			// registry and then use it to get the profile name
			if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
												  NULL, &nSize))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:CertGetCertificateContextProperty() failed", dwErr);
				break;
			}

			pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
			if(!pKeyProv)
			{
				DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
				LogErrorMessage("OpenUserProfile() : Out of memory", 0);
				break;
			}
		
			if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
												  pKeyProv, &nSize))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:CertGetCertificateContextProperty() failed", dwErr);
				break;
			}
			
			lpszContainerName = _WideToMultiString(pKeyProv->pwszContainerName);

			if(!GetPTAProfileInfo(lpszContainerName, szProfilePath, sizeof(szProfilePath), szClientInfo, sizeof(szClientInfo),
							szClientInfoSig, sizeof(szClientInfoSig), &bProfileType))
				break;

			// Put app context in the registry
			if(!ParseProfilePath(szProfilePath, &lpAppName, &lpUserName))
				break;

			if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
							  KEY_WRITE, NULL, &hKey, &dwDisp) != ERROR_SUCCESS)
			{
				dwErr = GetLastError();
				LoadString(g_hInst, IDS_REG_CREATE, szMsg, MAX_MSG_LEN);
				LogErrorMessage("OpenUserProfile:RegOpenKeyEx() failed", dwErr);
				break;
			}

			if(RegSetValueEx(hKey, FET_APP_CONTEXT, 0, REG_SZ, (LPBYTE)lpAppName, 
							 (lstrlen(lpAppName) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
			{
				dwErr = GetLastError();
				LoadString(g_hInst, IDS_REG_WRITE, szMsg, MAX_MSG_LEN);
				LogErrorMessage("OpenUserProfile:RegSetValueEx() failed", dwErr);
				break;
			}

			lstrcpy(szAppContext, lpAppName);

			if(bProfileType == ROAMING)
			{
				if(RegSetValueEx(hKey, CLIENT_INFO, 0, REG_SZ, (LPBYTE)szClientInfo, 
								 (lstrlen(szClientInfo) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
				{
					dwErr = GetLastError();
					LoadString(g_hInst, IDS_REG_WRITE, szMsg, MAX_MSG_LEN);
					LogErrorMessage("OpenUserProfile:RegSetValueEx() failed", dwErr);
					break;
				}

				if(RegSetValueEx(hKey, CLIENT_INFO_SIG, 0, REG_SZ, (LPBYTE)szClientInfoSig, 
								 (lstrlen(szClientInfoSig) + 1) * sizeof(TCHAR)) != ERROR_SUCCESS)
				{
					dwErr = GetLastError();
					LoadString(g_hInst, IDS_REG_WRITE, szMsg, MAX_MSG_LEN);
					LogErrorMessage("OpenUserProfile:RegSetValueEx() failed", dwErr);
					break;
				}
			}
		} 

		if(bProfileType == ROAMING)
		{
			varRoamProfile.vt = VT_BOOL;
			varRoamProfile.boolVal = 1;	// roam

			varSaveLocal.vt = VT_BOOL;
			varSaveLocal.boolVal = 0;	// do not save local
		}
		else
		{
			varRoamProfile.vt = VT_BOOL;
			varRoamProfile.boolVal = 0;	// dont roam

			varSaveLocal.vt = VT_BOOL;
			varSaveLocal.boolVal = 1;	// do save local
		}

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = 0;	// '0' Use CAPI = NO

		if(!MultiByteToWideChar(CP_ACP, 0, szAppContext, -1, wsz, MAX_PATH_LEN))
			break;

		varAppName.vt = VT_BSTR;
		varAppName.bstrVal = SysAllocString(wsz);
		
		hr = pVSPTA->Initialize(&varAppName, &varUseCapi);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:VSPTA init failed", hr);
			break;
		}
		VariantClear(&varAppName);

		hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:QueryInterface() for PTADLLApi failed", hr);
			break;
		}

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = L"localhost";
			
		hr = pPTADllApi->put_HostFQDN(varHostName);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:put_HostFQDN() failed", hr);
			break;
		}

		// If selecting a cert for first time then set the profile name
		if(pCertContext)
		{
			if(!MultiByteToWideChar(CP_ACP, 0, lpUserName, -1, wsz, MAX_PATH_LEN))
				break;

			varUserName.vt = VT_BSTR;
			varUserName.bstrVal = SysAllocString(wsz);
			hr = g_pProfMgmt->put_ProfileName(varUserName);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:put_ProfileName for failed", hr);
				break;
			}
			VariantClear(&varUserName);
		}

		varOpenProfFlag.vt = VT_I2;
		varOpenProfFlag.iVal = OPENPROF_OPEN_ONLY;
		hr = g_pProfMgmt->put_OpenProfFlags(varOpenProfFlag);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:put_OpenProfFlags failed", hr);
			break;
		}

		hr = g_pProfMgmt->put_RoamProfile(varRoamProfile);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:put_RoamProfile failed", hr);
			break;
		}

		hr = g_pProfMgmt->put_SaveLocal(varSaveLocal);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("OpenUserProfile:put_SaveLocal failed", hr);
			break;
		}

		if(bProfileType == ROAMING)
		{
			VARIANT varClientInfo, varClientInfoSig;
			WCHAR wcClientInfo[2*CLIENT_INFO_LEN];

			hr = pVSPTA->QueryInterface(IID_IVSRoamPrefs, (void **) &pRoamPrefs);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:QueryInterface() for RoamPrefs failed", hr);
				break;
			}

			if(!MultiByteToWideChar(CP_ACP, 0, szClientInfo, -1, wcClientInfo, 2*CLIENT_INFO_LEN))
				break;

			varClientInfo.vt = VT_BSTR;
			varClientInfo.bstrVal = SysAllocString(wcClientInfo);
			hr = pRoamPrefs->put_ClientInfo(varClientInfo);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:put_RoamPrefs_ClientInfo() failed", hr);
				VariantClear(&varClientInfo);
				break;
			}
			VariantClear(&varClientInfo);

			if(!MultiByteToWideChar(CP_ACP, 0, szClientInfoSig, -1, wcClientInfo, 2*CLIENT_INFO_LEN))
				break;

			varClientInfoSig.vt = VT_BSTR;
			varClientInfoSig.bstrVal = SysAllocString(wcClientInfo);
			hr = pRoamPrefs->put_ClientInfoSig(varClientInfoSig);
			if(hr != S_OK)
			{
				DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OpenUserProfile:put_RoamPrefs_ClientInfoSig() failed", hr);
				VariantClear(&varClientInfoSig);
				break;
			}
			VariantClear(&varClientInfoSig);
		}

		if(LoadString(g_hInst, IDS_OPEN_FET_PROFILE, szMsg, MAX_MSG_LEN))
		{
			if(MultiByteToWideChar(CP_ACP, 0, szMsg, -1, wsz, MAX_PATH_LEN))
			{	
				varOpenProfTitle.vt = VT_BSTR;
				varOpenProfTitle.bstrVal = SysAllocString(wsz);

				hr = pIVSUIPref->put_OpenProf_Title(varOpenProfTitle);
			}
		}

		hr = g_pProfMgmt->OpenProfile();
		if(hr != S_OK)
		{
			if(hr != E_USERCANCELLED)
				MessageBox(GetFocus(), "Unable to open user profile", "Safe", MB_OK | MB_ICONERROR);

			LogErrorMessage("OpenUserProfile:OpenProfile failed", hr);
			break;
		}

		// Profile is present, read the metadata in the profile and put it in the Safe directory
		if(!pCertContext)
			if(!GetApplicationData(pVSPTA))
				break;

		bRetVal = TRUE;

	} while(0);

	VariantClear(&varOpenProfTitle);

	if(lpAppName)
	{
		free(lpAppName);
		lpAppName = NULL;
	}

	if(lpUserName)
	{
		free(lpUserName);
		lpUserName = NULL;
	}

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(lpszContainerName)
	{
		free(lpszContainerName);
		lpszContainerName = NULL;
	}

	if(pKeyProv)
	{
		free(pKeyProv);
		pKeyProv = NULL;
	}

	if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	if(pRoamPrefs)
	{
		pRoamPrefs->Release();
		pRoamPrefs = NULL;
	}

	if(pIVSUIPref)
	{
		pIVSUIPref->Release();
		pIVSUIPref = NULL;
	}

	if(pVSPTA)
	{
#if 1
//		pVSPTA->Close();
#endif
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	return bRetVal;
}


// Save the metadata file in the profile
BOOL SaveApplicationData(VOID)
{
	HRESULT hr;
	BOOL bRetVal = FALSE;
	IVSPTA *pVSPTA = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	VARIANT varAppName, varHostName, varUseCapi;
	VARIANT varAppPref, varMetaData;
	TCHAR /*szProfilePath[2*MAX_PATH]*/ szAppContext[2*MAX_PATH], szMsg[MAX_PATH];
	TCHAR szFmt[MAX_PATH], *lpAppName = NULL, *lpUserName = NULL;
	WCHAR wsz[2*MAX_PATH];
	HKEY hKey = NULL;
	DWORD dwType, dwSize = 0, dwErr = 0, dwFileSize = 0;
	DWORD dwBytesRead = 0;
	HANDLE hDecrMetaFile = NULL;
	
	CoInitialize(NULL); 

	do
	{
		hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, 
							  IID_IVSPTA,(void**)&pVSPTA);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:CoCreateInstance for CLSID_VSPTA failed", hr);
			break;
		}

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = 0;	// '0' Use CAPI = NO

		if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_QUERY_VALUE, 
						&hKey) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_REG_OPEN, szMsg, MAX_PATH);
			LogErrorMessage("SaveApplicationData:RegOpenKeyEx() failed", dwErr);
			break;
		}

		dwSize = 2*MAX_PATH;
		if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, (LPBYTE)szAppContext, 
						   &dwSize) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_READ_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:RegReadValueEx() failed", dwErr);
			break;
		}

		/*if(!ParseProfilePath(szProfilePath, &lpAppName, &lpUserName))
			break;*/

		if(!MultiByteToWideChar(CP_ACP, 0, szAppContext, -1, wsz, 2*MAX_PATH))
			break;

		varAppName.vt = VT_BSTR;
		varAppName.bstrVal = SysAllocString(wsz);
		
		hr = pVSPTA->Initialize(&varAppName, &varUseCapi);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:VSPTA init failed", hr);
			break;
		}
		VariantClear(&varAppName);

		hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:QueryInterface() for PTADLLApi failed", hr);
			break;
		}

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = L"localhost";
			
		hr = pPTADllApi->put_HostFQDN(varHostName);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:put_HostFQDN() failed", hr);
			break;
		}

		varAppPref.vt = VT_BSTR;
		varAppPref.bstrVal = L"FET_METADATA";

		// Read the decrypted metadata file in memory
		hDecrMetaFile = CreateFile(g_szDecrSettingsFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
							 FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hDecrMetaFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_PATH);
			wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "SaveApplicationData:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
			LogErrorMessage(szMsg, dwErr);
			break;
		}	

		dwFileSize = GetFileSize(hDecrMetaFile, NULL);

		varMetaData.vt = VT_ARRAY;
		varMetaData.parray = SafeArrayCreateVector(VT_UI1, 0, dwFileSize);
		if(!varMetaData.parray)
		{
			LogErrorMessage("SaveApplicationData : SafeArrayCreateVector() failed", 0);
			break;
		}
		
		if(!ReadFile(hDecrMetaFile, varMetaData.parray->pvData, dwFileSize, &dwBytesRead, NULL))
		{
			LogErrorMessage("SaveApplicationData : ReadFile() failed", 0);
			break;
		}

		hr = pVSPTA->AppPref_SetPreference(&varAppPref, &varMetaData);
		if(hr != S_OK)
		{
			DisplayMessage(GetFocus(), IDS_PTA_INIT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SaveApplicationData:AppPref_SetPreference() failed", hr);
			break;
		}
		VariantClear(&varMetaData);

		bRetVal = TRUE;

	} while(0);

	if(lpAppName)
	{
		free(lpAppName);
		lpAppName = NULL;
	}

	if(lpUserName)
	{
		free(lpUserName);
		lpUserName = NULL;
	}

	if(hDecrMetaFile)
	{
		CloseHandle(hDecrMetaFile);
		hDecrMetaFile = NULL;
	}

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

	if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	if(pVSPTA)
	{
#if 1
//		pVSPTA->Close();
#endif
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	CoUninitialize();

	return bRetVal;
}


// Get the metadata file in the profile and put it in the
// Safe directory
BOOL GetApplicationData(IVSPTA *pVSPTA)
{
	BOOL bRetVal = FALSE;
	HRESULT hr;
	VARIANT varAppPref, varMetaData;
	TCHAR szMsg[MAX_PATH], szFmt[MAX_PATH], *pData = NULL;
	HANDLE hDecrMetaFile = NULL;
	DWORD dwErr = 0, dwBytesWritten = 0, cbData = 0;
	PBYTE pbData = NULL;

	VariantInit(&varMetaData);

	do
	{
		varAppPref.vt = VT_BSTR;
		varAppPref.bstrVal = L"FET_METADATA";

		hr = pVSPTA->AppPref_GetPreference(&varAppPref, &varMetaData);
		if(hr != S_OK)
		{
#if 0
			if(hr == E_VS_INVALID_APP_PREF)
				LoadString(g_hInst, IDS_INVALID_PROFILE, szMsg, MAX_PATH);
			else
				LoadString(g_hInst, IDS_APP_DATA_ERR, szMsg, MAX_PATH);

			MessageBox(GetFocus(), szMsg, "Safe", MB_OK | MB_ICONERROR);
#else
			if(MessageBox(GetFocus(), "The profile which you have selected does not contain the File Encryption preferences. Do you wish to select another certificate to open the Safe?.", "Safe", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				// Remove the registry entry for the app context, this will allow
				// the user to select another certificate
				HKEY hKey = NULL;
				if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_ALL_ACCESS,
								&hKey) != ERROR_SUCCESS)
				{
					dwErr = GetLastError();
					LogErrorMessage("GetApplicationData:RegOpenKeyEx() failed", dwErr);
				}
				else
				{
					if(RegDeleteValue(hKey, FET_APP_CONTEXT) != ERROR_SUCCESS)
					{
						dwErr = GetLastError();
						LogErrorMessage("GetApplicationData:RegOpenKeyEx() failed", dwErr);
					}
					
					RegCloseKey(hKey);
				}
				
				MessageBox(GetFocus(), "Please open the Safe again.", "Safe", MB_OK | MB_ICONINFORMATION);
			}
#endif
			
			LogErrorMessage("GetApplicationData:AppPref_GetPreference() failed", hr);
			break;
		}

		// Write the metadata in the decrypted metadata file
		hDecrMetaFile = CreateFile(g_szDecrSettingsFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
								   FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hDecrMetaFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
			wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "GetApplicationData:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
			LogErrorMessage(szMsg, dwErr);
			break;
		}

		if(SafeArrayAccessData((SAFEARRAY FAR*)varMetaData.parray,(void HUGEP* FAR*)&pbData) != S_OK)
		{
			LoadString(g_hInst, IDS_APP_DATA_ERR, szMsg, MAX_PATH);
			MessageBox(GetFocus(), szMsg, "Safe", MB_OK | MB_ICONERROR);
			LogErrorMessage("GetApplicationData:SafeArrayAccessData() failed", 0);
			break;
		}
		else
		{
			long lBound;    
			long uBound;
			
			// Verify that the SafeArray is the proper shape.
			SafeArrayGetLBound((SAFEARRAY FAR*)varMetaData.parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)varMetaData.parray, 1, &uBound);
			cbData = uBound - lBound + 1;
			SafeArrayUnaccessData((SAFEARRAY *)varMetaData.parray);

			if(cbData <= 0)
			{
				LoadString(g_hInst, IDS_APP_DATA_ERR, szMsg, MAX_PATH);
				MessageBox(GetFocus(), szMsg, "Safe", MB_OK | MB_ICONERROR);
				LogErrorMessage("GetApplicationData:cbData invalid", 0);
				break;
			}
		}

		if(!WriteFile(hDecrMetaFile, pbData, cbData, &dwBytesWritten, NULL))
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_APP_DATA_ERR, szMsg, MAX_PATH);
			MessageBox(GetFocus(), szMsg, "Safe", MB_OK | MB_ICONERROR);
			LogErrorMessage("GetApplicationData:WriteFile() failed", dwErr);
			break;
		}

		bRetVal = TRUE;
		
	} while(0);

	
	if(pData)
	{
		free(pData);
		pData = NULL;
	}

	if(hDecrMetaFile)
	{
		CloseHandle(hDecrMetaFile);
		hDecrMetaFile = NULL;
	}

	if(!bRetVal)
	{
		DeleteFile(g_szDecrSettingsFile);
	}

	VariantClear(&varMetaData);

	return bRetVal;
}


#if 0
BOOL ParseProfilePath(LPCSTR lpszProfilePath, LPTSTR *lpAppName, LPSTR *lpUserName)
{
	BOOL bRetVal = FALSE;
	TCHAR *pStartStr = NULL, *pProfilePath = NULL, szProfilePath[2*MAX_PATH];

	lstrcpy(szProfilePath, lpszProfilePath);

	do
	{
		// Parse profile and extract AppName and ProfileName
		pProfilePath = strchr(szProfilePath, '\'');
		if(!pProfilePath)
		{
			LogErrorMessage("ParseProfilePath():Error parsing Profile Path(1)", 0);
			break;
		}

		*pProfilePath = NULL;
		pStartStr = strrchr(szProfilePath, '\\') + 1;
		if(!pStartStr)
		{
			LogErrorMessage("ParseProfilePath():Error parsing Profile Path(2)", 0);
			break;
		}

		*lpUserName = (char *)malloc(lstrlen(pStartStr) + 1);
		if(!*lpUserName)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ParseProfilePath() : Out of memory", 0);
			break;
		}

		lstrcpy(*lpUserName, pStartStr);

		pStartStr = pProfilePath + 3;
		pProfilePath = strstr(pStartStr, "Profile.pta");
		if(!pProfilePath)
		{
			LogErrorMessage("ParseProfilePath():Error parsing Profile Path(3)", 0);
			break;
		}

		pProfilePath--;
		*pProfilePath = NULL;

		*lpAppName = (char *)malloc(lstrlen(pStartStr) + 1);
		if(!*lpAppName)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ParseProfilePath() : Out of memory", 0);
			break;
		}

		lstrcpy(*lpAppName, pStartStr);
		
		bRetVal = TRUE;
		break;

	} while(0);

	return bRetVal;
}
#else
BOOL ParseProfilePath(LPCSTR lpszProfilePath, LPTSTR *lpAppName, LPSTR *lpUserName)
{
	BOOL bRetVal = FALSE;
	TCHAR *pStr = NULL, *pProfilePath = NULL, szProfilePath[2*MAX_PATH];

	lstrcpy(szProfilePath, lpszProfilePath);

	// Remove the Profile.pta suffix if present
	pProfilePath = strstr(szProfilePath, PROFILE_NAME_ENDING);
	if(pProfilePath)
		*pProfilePath = '\0';

	// Remove the path if present
	pProfilePath = strrchr(szProfilePath, '\\');
	if(pProfilePath)
		pProfilePath += 1;
	else
		pProfilePath = szProfilePath;

	do
	{
		// Search for "'"
		pStr = strchr(pProfilePath, '\'');
		if(!pStr)
		{
			LogErrorMessage("ParseProfilePath():Error parsing Profile Path(1)", 0);
			break;
		}

		*pStr = '\0';

		// Copy the user name
		*lpUserName = (char *)malloc(lstrlen(pProfilePath) + 1);
		if(!*lpUserName)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ParseProfilePath() : Out of memory", 0);
			break;
		}

		lstrcpy(*lpUserName, pProfilePath);

		// Point to the App name and copy it
		pStr += 3;

		*lpAppName = (char *)malloc(lstrlen(pStr) + 1);
		if(!*lpAppName)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("ParseProfilePath() : Out of memory", 0);
			break;
		}

		lstrcpy(*lpAppName, pStr);

		bRetVal = TRUE;
	} while(0);

	return bRetVal;
}
#endif
