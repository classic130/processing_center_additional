// Contains DLLMain and standard OLE COM object creation stuff.

#include "stdafx.h"
#include <shlobj.h>
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "pidlmgr.h"
#include "ShlView.h"
#include "ClsFact.h"
#include "ViewList.h"
#include "vspmutil.h"
#include "safedel.h"
#include "resource.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "encdeclist.h"
#include "dlgprocs.h"

#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
#include "Guid.h"
#pragma data_seg()


BOOL EncryptAtLogoff(VOID);
BOOL DecryptAtLogon(VOID);
BOOL OldDllMain(HINSTANCE, DWORD, LPVOID);

extern PolicyVars g_LocalPolicy;
extern BOOL g_bLockedOut;
extern UINT g_nTimerId;
extern CEncDecList *g_EncrAtLogoffList, *g_DecrAtLogonList;

BOOL DeleteEntireKey(HKEY, LPTSTR);
BOOL DecryptAtLogon();

VOID CreateHiddenWindow(VOID);
VOID DestroyHiddenWindow(VOID);

DWORD WINAPI ThreadProc(LPVOID);
LRESULT CALLBACK HiddenWndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE   g_hInst;
BOOL		g_EndSession = FALSE;
UINT        g_DllRefCount;
HIMAGELIST  g_himlLarge = NULL;
HIMAGELIST  g_himlSmall = NULL;
TCHAR       g_szStoragePath[MAX_PATH];
TCHAR		g_szPolicyFile[MAX_PATH];
TCHAR       g_szExtTitle[TITLE_SIZE];
CViewList   *g_pViewList;
TCHAR		g_szWinDir[MAX_PATH_LEN], g_szWinSysDir[MAX_PATH_LEN], g_szDesktopDir[MAX_PATH_LEN];
CSList		*g_ExtensionList = NULL, *g_FoldersList = NULL;
DWORD		g_ExclusionAttr = 0;
TCHAR		g_FolderList[MAX_FOLDERS][MAX_PATH];

// Var used to indicate to the Context Menu handler whether the Encrypted or
// Decrypted view is active. Set it to TRUE initially bcos if none of the views
// are active and a right click is done on a folder under the Safe(we are just
// in the Explorer mode) then the menu items for the Encrypted view should come up.
BOOL g_bEncryptViewActive = TRUE;

BOOL g_LogOn_Off = FALSE;
BOOL g_bPasswordPrompt = FALSE;

HWND g_hAnimateDlg = NULL;
BOOL g_bCancelled = FALSE;
BOOL g_bEncryptErrPrompt = TRUE;
BOOL g_bReadErrPrompt = TRUE;
BOOL g_bFilterErrPrompt = TRUE;
BOOL g_DumpPolicyFile = FALSE;
BOOL g_DumpDataFile = FALSE;

// Variables related to securely deleting a file
BOOL bBufferInit = FALSE;
PTCHAR Buffers[3]; // will contain the pattern to overwrite the deleted file with

// To control whether the FileReplace dialog will be displayed
BOOL g_bPrompt = TRUE; 

// To store the OS version, Win95 or Winnt
DWORD g_dwPlatform;

TCHAR g_szSettingsFile[2*MAX_PATH];
TCHAR g_szDecrSettingsFile[2*MAX_PATH];
TCHAR g_szTokenFile[MAX_PATH_LEN];

DWORD dwThreadId;
HWND g_hHiddenWnd;
static HANDLE hThread;

BOOL OldDllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			g_hInst = hInstance;
			g_DllRefCount = 0;

			g_pViewList = new CViewList();
			g_ExtensionList = new CSList();
			g_FoldersList = new CSList();
			g_EncrAtLogoffList = new CEncDecList();
			g_DecrAtLogonList = new CEncDecList();

			if(!GetGlobalSettings())
			{
				DisplayMessage(GetFocus(), IDS_DLL_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OldDllMain:GetGlobalSetting() failed.", 0);
				return FALSE;
			}

			// Buffers for secure deletion
			if(!BufferInit())
			{
				DisplayMessage(GetFocus(), IDS_DLL_INIT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("OldDllMain:BufferInit() failed.", 0);
				return FALSE;
			}

			// Create the global image lists
			CreateImageLists();
		}
			break;


		case DLL_PROCESS_DETACH:
			// Delete the global certificate list which contains the encryption and
			// signing certificates
			DeleteCertList();

			if(g_nTimerId)
			{
				KillTimer(NULL, g_nTimerId);
				g_nTimerId = 0;
			}

			// deallocate buffers used for secure deletion
			BufferDestroy();

			// destroy the global image lists
			DestroyImageLists();

			if(g_pViewList)
				delete g_pViewList; 

			if(g_ExtensionList)
				delete g_ExtensionList;

			if(g_FoldersList)
				delete g_FoldersList;

			if(g_EncrAtLogoffList)
				delete g_EncrAtLogoffList;
		
			if(g_DecrAtLogonList)
				delete g_DecrAtLogonList;
			
			g_bLockedOut = TRUE;

			break;
	}

	return TRUE;
}                                 


typedef struct{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
}REGSTRUCT, *LPREGSTRUCT;

	
/*HRESULT OldDllRegisterServer(VOID)
{
	int      i;
	HKEY     hKey;
	LRESULT  lResult;
	DWORD    dwDisp;
	TCHAR    szSubKey[MAX_PATH];
	TCHAR    szCLSID[MAX_PATH];
	TCHAR    szModule[MAX_PATH];
	LPWSTR   pwsz;

	// Get the CLSID in string form
	StringFromIID(CLSID_VSSafe, &pwsz);

	if(pwsz)
	{
	   WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

	   // Free the string
	   LPMALLOC pMalloc;
	   CoGetMalloc(1, &pMalloc);
	   if(pMalloc)
	   {
		  pMalloc->Free(pwsz);
		  pMalloc->Release();
	   }
	}

	// Get this DLL's path and file name
	GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

	// Register the CLSID entries
	REGSTRUCT ClsidEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),	NULL, g_szExtTitle,
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),	TEXT("InfoTip"), TEXT("To protect your Files/Folders drag and drop them on the Safe. The Files will get encrypted."),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),	NULL, TEXT("%s"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),	TEXT("ThreadingModel"), TEXT("Apartment"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\DefaultIcon"), NULL, TEXT("%s,0"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\shellex\\PropertySheetHandlers"),	NULL, NULL,	
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\shellex\\PropertySheetHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"),	NULL, NULL,
		NULL, NULL, NULL, NULL
	};

	for(i = 0; ClsidEntries[i].hRootKey; i++)
	{
	   // Create the sub key string.
	   wsprintf(szSubKey, ClsidEntries[i].lpszSubKey, szCLSID);

	   lResult = RegCreateKeyEx(ClsidEntries[i].hRootKey, szSubKey, 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey,
								&dwDisp);
   
	   if(NOERROR == lResult)
	   {
		  TCHAR szData[MAX_PATH];

		  // If necessary, create the value string
		  if(ClsidEntries[i].lpszData)
		  {
			  wsprintf(szData, ClsidEntries[i].lpszData, szModule);
   
			  lResult = RegSetValueEx(hKey, ClsidEntries[i].lpszValueName, 0, REG_SZ,
									  (LPBYTE)szData, (lstrlen(szData) + 1) * sizeof(TCHAR));
		  }

		  RegCloseKey(hKey);
	   }
	   else
	 	  return SELFREG_E_CLASS;
	 }


	// Register the default flags for the folder.
	wsprintf(szSubKey, TEXT("CLSID\\%s\\ShellFolder"), szCLSID);

	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
							   KEY_WRITE, NULL, &hKey, &dwDisp);
	if(NOERROR == lResult)
    {
		DWORD dwData = SFGAO_FOLDER | SFGAO_HASSUBFOLDER | SFGAO_DROPTARGET | 
					   SFGAO_HASPROPSHEET | SFGAO_BROWSABLE;

		lResult = RegSetValueEx(hKey, TEXT("Attributes"), 0, REG_BINARY, (LPBYTE)&dwData,
								sizeof(dwData));
		RegCloseKey(hKey);
	}
	else
	   return SELFREG_E_CLASS;


	// Register the name space extension
	// Create the sub key string. Change this from "...MyComputer..." to 
	// "...Desktop..." if desired.


#define INSTALL_ON_DESKTOP

	wsprintf(szSubKey, 
#ifdef INSTALL_ON_DESKTOP
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\%s"), 
#else
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\%s"), 
#endif
            szCLSID);

	lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, NULL,
							 REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey,
							 &dwDisp);

	if(NOERROR == lResult)
    {
		TCHAR szData[MAX_PATH];

	    // Create the value string.
	    lstrcpy(szData, g_szExtTitle);

	    lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szData,
								(lstrlen(szData) + 1) * sizeof(TCHAR));

#if 0
		// Create the removal key
		LoadString(g_hInst, IDS_REMOVAL_MESSAGE, szData, sizeof(szData));
		lResult = RegSetValueEx(hKey, "Removal Message", 0, REG_SZ, (LPBYTE)szData,
								(lstrlen(szData) + 1) * sizeof(TCHAR));
#endif

   	    RegCloseKey(hKey);
	}
	else
		return SELFREG_E_CLASS;

	// If running on NT, register the extension as approved.
	OSVERSIONINFO  osvi;

	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

#if 0
	// removed this bcos if the user does not have administrative privileges on his local machine
	// this key cannot be created. refer to 'INFO: Approved Shell Extensions Only Enforced If 
	// EnforceShellExt' for more details
 	if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
	{
		lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));

		lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, NULL,
								 REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey,
								 &dwDisp);

		if(NOERROR == lResult)
		{
			TCHAR szData[MAX_PATH];

			//Create the value string.
			lstrcpy(szData, g_szExtTitle);

			lResult = RegSetValueEx(hKey, szCLSID, 0, REG_SZ, (LPBYTE)szData,
									(lstrlen(szData) + 1) * sizeof(TCHAR));
  
			RegCloseKey(hKey);
		}
		else
			return SELFREG_E_CLASS;
   }
#endif

	REGSTRUCT ContextMenuEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex\\ContextMenuHandlers"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex\\ContextMenuHandlers"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"), NULL, NULL,
		NULL, NULL, NULL, NULL
	};

	for(i = 0; ContextMenuEntries[i].hRootKey; i++)
	{
	
	   lResult = RegCreateKeyEx(ContextMenuEntries[i].hRootKey, 
					ContextMenuEntries[i].lpszSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
					KEY_WRITE, NULL, &hKey, &dwDisp);
   
	   if(NOERROR == lResult)
		  RegCloseKey(hKey);
	   else
		  return SELFREG_E_CLASS;
	}


	DWORD dwVal = 1;
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
					  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
	{
#ifdef _DEBUG
		// Enable dumping of the policy file and decrypted data file, 
		// remove this later, useful for debugging purposes.
		RegSetValueEx(hKey, "DumpPolicyFile", 0, REG_DWORD, (LPBYTE)&dwVal,
					  sizeof(DWORD));

		RegSetValueEx(hKey, "DumpDataFile", 0, REG_DWORD, (LPBYTE)&dwVal,
					  sizeof(DWORD));
#endif

		// Set key for logging error messages
		RegSetValueEx(hKey, "LogErrorMessage", 0, REG_DWORD, (LPBYTE)&dwVal,
					  sizeof(DWORD));

		RegCloseKey(hKey);
	}

	// Registry entries for inplace encryption
	REGSTRUCT FileHandlerEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT(".enc"),	NULL, TEXT("Encrypted.File"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File"), NULL, TEXT("Encrypted File"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\DefaultIcon"), NULL, TEXT("%1"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\shellex"),	NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\shellex\\IconHandler"), NULL, TEXT("{342EE082-2DAB-11d3-8BF3-0010830169AF}"),
		NULL, NULL, NULL, NULL
	};

	for(i = 0; FileHandlerEntries[i].hRootKey; i++)
	{
	   lResult = RegCreateKeyEx(FileHandlerEntries[i].hRootKey, FileHandlerEntries[i].lpszSubKey, 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey,
								&dwDisp);
   	   if(NOERROR == lResult)
	   {
		  // If necessary, create the value string
		  if(FileHandlerEntries[i].lpszData)
		  {
   			  lResult = RegSetValueEx(hKey, FileHandlerEntries[i].lpszValueName, 0, REG_SZ,
								(LPBYTE)FileHandlerEntries[i].lpszData, (lstrlen(FileHandlerEntries[i].lpszData) + 1) * sizeof(TCHAR));
		  }

		  RegCloseKey(hKey);
	   }
	   else
		  return SELFREG_E_CLASS;
	}

	// Add registry entries relating to password prompting and timeout, these will we used
	// only during the CAPI mode
	if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
					  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
	{
		dwVal = 0;
		RegSetValueEx(hKey, "InvalidTries", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));

		dwVal = 0;
		RegSetValueEx(hKey, "LastInvalidTry", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));
		
		RegCloseKey(hKey);
	}

	// Tell the shell that the folder has been added.
	LPITEMIDLIST pidlDesktop, pidlMyComputer;

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

	IMalloc  *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidlDesktop);
	   pMalloc->Free(pidlMyComputer);
	   pMalloc->Release();
	}

	return S_OK;
}*/


HRESULT OldDllRegisterServer(VOID)
{
	int      i;
	HKEY     hKey;
	LRESULT  lResult;
	DWORD    dwDisp;
	TCHAR    szSubKey[MAX_PATH];
	TCHAR    szModule[MAX_PATH];
	
	// Get this DLL's path and file name
	GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

	// Register the CLSID entries
	REGSTRUCT ClsidEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}"),	NULL, g_szExtTitle,
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}"),	TEXT("InfoTip"), TEXT("To protect your Files/Folders drag and drop them on the Safe. The Files will get encrypted."),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\InprocServer32"),	NULL, TEXT("%s"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\InprocServer32"),	TEXT("ThreadingModel"), TEXT("Apartment"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\DefaultIcon"), NULL, TEXT("%s,0"),
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex\\PropertySheetHandlers"),	NULL, NULL,	
		HKEY_CLASSES_ROOT,   TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex\\PropertySheetHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"),	NULL, NULL,
		NULL, NULL, NULL, NULL
	};

	for(i = 0; ClsidEntries[i].hRootKey; i++)
	{
		lstrcpy(szSubKey, ClsidEntries[i].lpszSubKey);

		lResult = RegCreateKeyEx(ClsidEntries[i].hRootKey, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
								 KEY_WRITE, NULL, &hKey, &dwDisp);
		if(NOERROR == lResult)
		{
			TCHAR szData[MAX_PATH];

			// If necessary, create the value string
			if(ClsidEntries[i].lpszData)
			{
				wsprintf(szData, ClsidEntries[i].lpszData, szModule);
   
				lResult = RegSetValueEx(hKey, ClsidEntries[i].lpszValueName, 0, REG_SZ,
										(LPBYTE)szData, (lstrlen(szData) + 1) * sizeof(TCHAR));
			}

			RegCloseKey(hKey);
		}
		else
	 		return SELFREG_E_CLASS;
	 }

	// Register the default flags for the folder.
	lstrcpy(szSubKey, TEXT("CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\ShellFolder"));

	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE,
							   KEY_WRITE, NULL, &hKey, &dwDisp);
	if(NOERROR == lResult)
    {
		DWORD dwData = SFGAO_FOLDER | SFGAO_HASSUBFOLDER | SFGAO_DROPTARGET | SFGAO_HASPROPSHEET | SFGAO_BROWSABLE;

		lResult = RegSetValueEx(hKey, TEXT("Attributes"), 0, REG_BINARY, (LPBYTE)&dwData, sizeof(dwData));
		RegCloseKey(hKey);
	}
	else
	   return SELFREG_E_CLASS;


	// Register the name space extension
	// Create the sub key string. Change this from "...MyComputer..." to  "...Desktop..." if desired.

#define INSTALL_ON_DESKTOP

	lstrcpy(szSubKey, 
#ifdef INSTALL_ON_DESKTOP
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{342EE082-2DAB-11D3-8BF3-0010830169AF}")
#else
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\{342EE082-2DAB-11D3-8BF3-0010830169AF}") 
#endif
            );

	lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, 
							 KEY_WRITE, NULL, &hKey, &dwDisp);
	if(NOERROR == lResult)
    {
		TCHAR szData[MAX_PATH];

	    // Create the value string.
	    lstrcpy(szData, g_szExtTitle);

	    lResult = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szData, (lstrlen(szData) + 1) * sizeof(TCHAR));

#if 0
		// Create the removal key
		LoadString(g_hInst, IDS_REMOVAL_MESSAGE, szData, sizeof(szData));
		lResult = RegSetValueEx(hKey, "Removal Message", 0, REG_SZ, (LPBYTE)szData,
								(lstrlen(szData) + 1) * sizeof(TCHAR));
#endif

   	    RegCloseKey(hKey);
	}
	else
		return SELFREG_E_CLASS;

	// If running on NT, register the extension as approved.
	OSVERSIONINFO  osvi;

	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

#if 0
	// removed this bcos if the user does not have administrative privileges on his local machine
	// this key cannot be created. refer to 'INFO: Approved Shell Extensions Only Enforced If 
	// EnforceShellExt' for more details
 	if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
	{
		lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));

		lResult = RegCreateKeyEx(HKEY_LOCAL_MACHINE, szSubKey, 0, NULL,
								 REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey,
								 &dwDisp);

		if(NOERROR == lResult)
		{
			TCHAR szData[MAX_PATH];

			//Create the value string.
			lstrcpy(szData, g_szExtTitle);

			lResult = RegSetValueEx(hKey, "{342EE082-2DAB-11d3-8BF3-0010830169AF}", 0, REG_SZ, (LPBYTE)szData,
									(lstrlen(szData) + 1) * sizeof(TCHAR));
  
			RegCloseKey(hKey);
		}
		else
			return SELFREG_E_CLASS;
   }
#endif

	REGSTRUCT ContextMenuEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex\\ContextMenuHandlers"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("*\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex\\ContextMenuHandlers"), NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Folder\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"), NULL, NULL,
		NULL, NULL, NULL, NULL
	};

	for(i = 0; ContextMenuEntries[i].hRootKey; i++)
	{
	   lResult = RegCreateKeyEx(ContextMenuEntries[i].hRootKey, ContextMenuEntries[i].lpszSubKey, 
								0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);
	   if(NOERROR == lResult)
		  RegCloseKey(hKey);
	   else
		  return SELFREG_E_CLASS;
	}


	DWORD dwVal = 1;
	if(RegCreateKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
					  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
	{
#ifdef _DEBUG
		// Enable dumping of the policy file and decrypted data file, 
		// remove this later, useful for debugging purposes.
		RegSetValueEx(hKey, "DumpPolicyFile", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));

		RegSetValueEx(hKey, "DumpDataFile", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));
#endif

		// Set key for logging error messages
		RegSetValueEx(hKey, "LogErrorMessage", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));

		RegCloseKey(hKey);
	}

	// Registry entries for inplace encryption
	REGSTRUCT FileHandlerEntries[] = 
	{  
		HKEY_CLASSES_ROOT,   TEXT(".enc"),	NULL, TEXT("Encrypted.File"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File"), NULL, TEXT("Encrypted File"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\DefaultIcon"), NULL, TEXT("%1"),
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\shellex"),	NULL, NULL,
		HKEY_CLASSES_ROOT,   TEXT("Encrypted.File\\shellex\\IconHandler"), NULL, TEXT("{342EE082-2DAB-11d3-8BF3-0010830169AF}"),
		NULL, NULL, NULL, NULL
	};

	for(i = 0; FileHandlerEntries[i].hRootKey; i++)
	{
	   lResult = RegCreateKeyEx(FileHandlerEntries[i].hRootKey, FileHandlerEntries[i].lpszSubKey, 0, NULL,
								REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwDisp);
   	   if(NOERROR == lResult)
	   {
		  // If necessary, create the value string
		  if(FileHandlerEntries[i].lpszData)
		  {
   			  lResult = RegSetValueEx(hKey, FileHandlerEntries[i].lpszValueName, 0, REG_SZ,
								(LPBYTE)FileHandlerEntries[i].lpszData, (lstrlen(FileHandlerEntries[i].lpszData) + 1) * sizeof(TCHAR));
		  }

		  RegCloseKey(hKey);
	   }
	   else
		  return SELFREG_E_CLASS;
	}

	// Add registry entries relating to password prompting and timeout, these will we used
	// only during the CAPI mode
	if(RegCreateKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, NULL, REG_OPTION_NON_VOLATILE, 
					  KEY_WRITE, NULL, &hKey, &dwDisp) == ERROR_SUCCESS)
	{
		dwVal = 0;
		RegSetValueEx(hKey, "InvalidTries", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));

		dwVal = 0;
		RegSetValueEx(hKey, "LastInvalidTry", 0, REG_DWORD, (LPBYTE)&dwVal, sizeof(DWORD));
		
		RegCloseKey(hKey);
	}

	// Tell the shell that the folder has been added.
	LPITEMIDLIST pidlDesktop, pidlMyComputer;

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

	IMalloc  *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidlDesktop);
	   pMalloc->Free(pidlMyComputer);
	   pMalloc->Release();
	}

	return S_OK;
}




/*HRESULT OldDllUnregisterServer(VOID)
{
	LPWSTR   pwsz;
	TCHAR    szCLSID[MAX_PATH];
	TCHAR    szSubKey[MAX_PATH];

	// Get the CLSID in string form
	StringFromIID(CLSID_VSSafe, &pwsz);

	if(pwsz)
	{
	   WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

	   // Free the string
	   LPMALLOC pMalloc;
	   CoGetMalloc(1, &pMalloc);
	   if(pMalloc)
	   {
		  pMalloc->Free(pwsz);
		  pMalloc->Release();
	   }
	}
	else
		return E_FAIL;

	// Delete the namespace extension entries
	wsprintf(szSubKey, 
			 TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\%s"), 
			 szCLSID);
	DeleteEntireKey(HKEY_LOCAL_MACHINE, szSubKey);
	wsprintf(szSubKey, 
			 TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\%s"), 
			 szCLSID);
	DeleteEntireKey(HKEY_LOCAL_MACHINE, szSubKey);

	// Delete the object's registry entries
	wsprintf(szSubKey, TEXT("CLSID\\%s"), szCLSID);
	DeleteEntireKey(HKEY_CLASSES_ROOT, szSubKey);

	// Delete the right click context menu key for Files
	wsprintf(szSubKey, TEXT("*\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"));
	DeleteEntireKey(HKEY_CLASSES_ROOT, szSubKey);

	// Delete the right click context menu key for Folders
	wsprintf(szSubKey, TEXT("Folder\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}"));
	DeleteEntireKey(HKEY_CLASSES_ROOT, szSubKey);

	// Delete the '.enc' file handler key
	DeleteEntireKey(HKEY_CLASSES_ROOT, ".enc");
	DeleteEntireKey(HKEY_CLASSES_ROOT, "Encrypted.File");

	// Delete the 'file encryption tool'
	wsprintf(szSubKey, TEXT("Software\\Verisign Inc.\\File Encryption Tool"));
	DeleteEntireKey(HKEY_CURRENT_USER, szSubKey);
	DeleteEntireKey(HKEY_LOCAL_MACHINE, szSubKey);

	// Delete the approved extensions on NT
	OSVERSIONINFO  osvi;

	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
	{
	   LRESULT  lResult;
	   HKEY     hKey;

	   lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
							  TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
							  0, KEY_SET_VALUE, &hKey);

	   if(NOERROR == lResult)
	   {
		  TCHAR szData[MAX_PATH];

		  // Create the value string.
		  lstrcpy(szData, g_szExtTitle);
		  lResult = RegDeleteValue(hKey, szCLSID);
		  RegCloseKey(hKey);
	   }
	   else
		  return SELFREG_E_CLASS;
	}
	
	// Tell the shell that the folder has been removed.
	LPITEMIDLIST pidlDesktop, pidlMyComputer;

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

	IMalloc  *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidlDesktop);
	   pMalloc->Free(pidlMyComputer);
	   pMalloc->Release();
	}

	return S_OK;
}*/


HRESULT OldDllUnregisterServer(VOID)
{
	TCHAR szSubKey[MAX_PATH];

	// Delete the namespace extension entries
#define INSTALL_ON_DESKTOP

	lstrcpy(szSubKey, 
#ifdef INSTALL_ON_DESKTOP
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\{342EE082-2DAB-11D3-8BF3-0010830169AF}")
#else
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\MyComputer\\NameSpace\\{342EE082-2DAB-11D3-8BF3-0010830169AF}") 
#endif
            );

	RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);

	// Delete the object's registry entries
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\DefaultIcon");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\InprocServer32");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\ShellFolder");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex\\PropertySheetHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex\\PropertySheetHandlers");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}\\shellex");
	RegDeleteKey(HKEY_CLASSES_ROOT, "CLSID\\{342EE082-2DAB-11D3-8BF3-0010830169AF}");

	// Delete the right click context menu key for Files and Folders
	RegDeleteKey(HKEY_CLASSES_ROOT, "*\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Folder\\shellex\\ContextMenuHandlers\\{342EE082-2DAB-11d3-8BF3-0010830169AF}");
		
	// Delete the '.enc' file handler key
	RegDeleteKey(HKEY_CLASSES_ROOT, ".enc");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Encrypted.File\\shellex\\IconHandler");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Encrypted.File\\shellex");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Encrypted.File\\DefaultIcon");
	RegDeleteKey(HKEY_CLASSES_ROOT, "Encrypted.File");

#if 0
	// Delete the approved extensions on NT
	OSVERSIONINFO  osvi;

	osvi.dwOSVersionInfoSize = sizeof(osvi);
	GetVersionEx(&osvi);

	if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
	{
	   LRESULT  lResult;
	   HKEY     hKey;

	   lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
							  TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
							  0, KEY_SET_VALUE, &hKey);

	   if(NOERROR == lResult)
	   {
		  TCHAR szData[MAX_PATH];

		  // Create the value string.
		  lstrcpy(szData, g_szExtTitle);
		  lResult = RegDeleteValue(hKey, szCLSID);
		  RegCloseKey(hKey);
	   }
	   else
		  return SELFREG_E_CLASS;
	}
#endif
	
	// Tell the shell that the folder has been removed.
	LPITEMIDLIST pidlDesktop, pidlMyComputer;

	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidlDesktop);
	SHGetSpecialFolderLocation(NULL, CSIDL_DRIVES, &pidlMyComputer);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlDesktop, 0);
	SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_IDLIST, pidlMyComputer, 0);

	IMalloc  *pMalloc;
	if(S_OK == SHGetMalloc(&pMalloc))
	{
	   pMalloc->Free(pidlDesktop);
	   pMalloc->Free(pidlMyComputer);
	   pMalloc->Release();
	}

	return S_OK;
}


BOOL EncryptAtLogoff(VOID)
{
	TCHAR szLocationInSafe[MAX_PATH], szOrigLocation[MAX_PATH];
	HANDLE hFind;
	WIN32_FIND_DATA wfd;

	// Fn. has already been called from LogOut(), no need to encrypt again
	if(g_bLockedOut)
		return TRUE;

	g_LogOn_Off = TRUE;

	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam;
	memset(&EncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));
	InitStatus stat = InitEncryptParams(&EncryptParam);

	if(stat == RENEW || stat == FAILED || stat == NO_MATCHES)
		return FALSE;

	g_bCancelled = FALSE;

	LPEncDec lpList = g_EncrAtLogoffList->GetNextItem(NULL);

	HWND hDlg;
	if(lpList)
	{
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_LOGON_OFF), 
		  				    GetFocus(), (DLGPROC)DlgEncrDecr);

		if(hDlg)
		{
			ShowWindow(hDlg, SW_SHOWNORMAL);
			SetWindowText(hDlg, "Log off...");

			HWND hWnd = GetDlgItem(hDlg, IDC_MSG);
			SetWindowText(hWnd, "Encrypting files at logoff.");
		}
	}

	while(lpList)
	{
		lstrcpy(szLocationInSafe, lpList->szLocInSafe);
		lstrcpy(szOrigLocation, lpList->szOrigLoc);

		// Check if the file is already present in Safe
		hFind = FindFirstFile(szLocationInSafe, &wfd);
 
		if(INVALID_HANDLE_VALUE == hFind)
		{
			// Check if file is present out of Safe, if not then delete entry 
			// from ini file
			hFind = FindFirstFile(szOrigLocation, &wfd);

			if(hFind == INVALID_HANDLE_VALUE)
			{
				lpList = g_EncrAtLogoffList->GetNextItem(szOrigLocation);
				g_EncrAtLogoffList->RemoveFromList(szOrigLocation);
				continue;
			}
			else
			{
				FindClose(hFind);

				if(EncryptFile(&EncryptParam, szOrigLocation, szLocationInSafe) 
							   == SUCCESS)
				{
					TCHAR szToSign[MAX_PATH];
					if(g_LocalPolicy.EncryptMethod == INPLACE)
					{
						lstrcpy(szToSign, szOrigLocation);
						lstrcat(szToSign, ".enc");
					}
					else
						lstrcpy(szToSign, szLocationInSafe);

					// Sign the file and put the signature at the end
					SignUpdateFile(szToSign);
				}
			}
		}
		else
			FindClose(hFind);

		lpList = g_EncrAtLogoffList->GetNextItem(szOrigLocation);
	}

	if(hDlg)
		DestroyWindow(hDlg);

	DeinitEncryptParams(&EncryptParam);

	// Delete all the 'fileinfo' files and the folders which contain
	// only the 'fileinfo' file. The 'fileinfo' files in each folder 
	// in the Safe will be created once when the dir is selected.
	if(g_szStoragePath[0] != '\0')
		RemoveFileInfoFiles(g_szStoragePath);

	g_LogOn_Off = FALSE;

	return TRUE;
}



BOOL DecryptAtLogon(VOID)
{
	g_LogOn_Off = TRUE;

	TCHAR szLocationInSafe[MAX_PATH], szOrigLocation[MAX_PATH], szFileInfo[MAX_PATH];

	HANDLE hFind;
	WIN32_FIND_DATA wfd;
	TCHAR *pStr;

	LPEncDec lpList = g_DecrAtLogonList->GetNextItem(NULL);

	HWND hDlg = NULL;
	if(lpList)
	{
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_LOGON_OFF), 
							GetFocus(), (DLGPROC)DlgEncrDecr);

		if(hDlg)
		{
			ShowWindow(hDlg, SW_SHOWNORMAL);
			SetWindowText(hDlg, "Log on...");

			HWND hWnd = GetDlgItem(hDlg, IDC_MSG);
			SetWindowText(hWnd, "Decrypting files at logon.");
		}
	}

	while(lpList)
	{
		lstrcpy(szLocationInSafe, lpList->szLocInSafe);
		lstrcpy(szOrigLocation, lpList->szOrigLoc);

		// Check if the file is already in decrypted state, out of Safe
		hFind = FindFirstFile(szOrigLocation, &wfd);
		if(INVALID_HANDLE_VALUE == hFind)
		{
			// Check if file is in Safe, if not then remove entry from ini file
			hFind = FindFirstFile(szLocationInSafe, &wfd);
			if(INVALID_HANDLE_VALUE != hFind)
			{
				FindClose(hFind);

				VerifySignature(szLocationInSafe);

				DecryptStatus Stat = DoDecrypt(szLocationInSafe, szOrigLocation);

				if(Stat == DECR_OK)
				{
					// Delete the encrypted source file
					DeleteFile(szLocationInSafe);

					// Remove the directory in Safe if it contains only the "fileinfo" file
					TCHAR szDirSafe[MAX_PATH];

					lstrcpy(szDirSafe, szLocationInSafe);
					pStr = strrchr(szDirSafe, '\\');
					*pStr = '\0';

					// Also put the deleted file in the fileinfo file. Mark the status of the
					// file as DECRYPTED
					// First get the path of "fileinfo" file
					pStr = strrchr(szLocationInSafe, '\\');
					if(pStr)
					{
						*pStr = '\0';
						lstrcpy(szFileInfo, szLocationInSafe); 
						lstrcat(szFileInfo, "\\fileinfo");
					}

					// Point to the filename, this is the section name in szFileInfo
					pStr += 1;

					// Add to the fileinfo file
					WritePrivateProfileString(pStr, "OrigLocation", szOrigLocation, szFileInfo);

					// "1" = decrypted
					WritePrivateProfileString(pStr, "Status", "1", szFileInfo);
				}	// if(Stat == DECR_OK)
			}
			else
			{
				lpList = g_DecrAtLogonList->GetNextItem(szOrigLocation);
				g_DecrAtLogonList->RemoveFromList(szOrigLocation);
				continue;
			}
		}
		else
			FindClose(hFind);	

		lpList = g_DecrAtLogonList->GetNextItem(szOrigLocation);
	}

	if(hDlg)
		DestroyWindow(hDlg);

	g_LogOn_Off = FALSE;

	return TRUE;
}



VOID CreateHiddenWindow(VOID)
{
	hThread = CreateThread(NULL, 0, ThreadProc, 0, 0, &dwThreadId);
}


VOID DestroyHiddenWindow(VOID)
{
	PostMessage(g_hHiddenWnd, WM_DESTROY, 0, 0);

	// Wait till the thread terminates
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	UnregisterClass("vsfe", g_hInst);
}


DWORD WINAPI ThreadProc(LPVOID lpData)
{
   WNDCLASS wc;
   MSG msg;

   wc.style = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc = HiddenWndProc;
   wc.cbClsExtra = 0;
   wc.cbWndExtra = 0;
   wc.hInstance = g_hInst;
   wc.hIcon = NULL;
   wc.hCursor = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
   wc.lpszMenuName = NULL;
   wc.lpszClassName = "vsfe";

   if(!RegisterClass(&wc))
	   return FALSE;

   g_hHiddenWnd = CreateWindow("vsfe", "vsfe", 0, 0, 0, 5, 5, NULL, NULL, g_hInst, NULL);

   if(!g_hHiddenWnd)
      return FALSE;

   	while(GetMessage(&msg, g_hHiddenWnd, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



LRESULT CALLBACK HiddenWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch (uMessage)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		case WM_QUERYENDSESSION:
		{
			// Update the registry icon number
			HKEY hKey;
			LRESULT lResult;
			TCHAR szCLSID[MAX_PATH], szKeyName[MAX_PATH], szModuleFile[MAX_PATH];
			LPWSTR pwsz;

			GetModuleFileName(g_hInst, szModuleFile, MAX_PATH);

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
				lstrcat(szModuleFile, ",0");
				RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szModuleFile, 
							  (lstrlen(szModuleFile) + 1) * sizeof(TCHAR));
				RegCloseKey(hKey);
			}

			return TRUE;
		}
	}

	return DefWindowProc(hWnd, uMessage, wParam, lParam);
}
