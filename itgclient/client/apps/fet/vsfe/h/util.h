#ifndef UTIL_H
#define UTIL_H

#ifdef _cplusplus
extern "C" {
#endif   //_cplusplus


#define TITLE_SIZE				64
#define CFSTR_VSSAFE			TEXT("VSSafeDataFormat")
#define NS_CLASS_NAME			(TEXT("VSSafeClass"))
#define VIEW_POINTER_OFFSET		GWL_USERDATA
#define FILTER_ATTRIBUTES		(FILE_ATTRIBUTE_SYSTEM | FILE_ATTRIBUTE_HIDDEN)
#define INITIAL_COLUMN_SIZE		200
#define NO_LISTVW_HEADERS		10
#define CLEANBUFSIZE			65536
#define MAX_READ_SIZE			1024
#define VALUE_STRING            (TEXT("Display Settings"))
#define ACTIVE_DESKTOP_KEY		(TEXT("Software\\Classes\\CLSID\\{AEB6717E-7E19-11d0-97EE-00C04FD91972}\\InProcServer32"))
#define DISPLAY_SETTINGS_COUNT  1
#define SECTION_NAME_SIZE		1024*32 - 2
#define	SECTION_SIZE			SECTION_NAME_SIZE		
#define MAX_EXT					1024
#define MAX_FOLDERS				1024
#define MAX_PATH_LEN			2*MAX_PATH
#define MAX_MSG_LEN				1024
#define POLICY_FILE				"fet.policy"
#define CSP_NAME				"VeriSign Personal Trust Agent (PTA)"


// Registry entries for FET
#define MAIN_KEY_STRING         (TEXT("Software\\VeriSign Inc.\\File Encryption Tool"))
#define FET_APP_CONTEXT			"ApplicationContext"
#define	PROFILE_NAME			"Profile"
#define PROFILE_PATH			"ProfilePath"
#define PROFILE_TYPE			"ProfileType"
#define CLIENT_INFO				"ClientInfo"
#define CLIENT_INFO_SIG			"ClientInfoSig"

// PTA specific defines
#define PTA_KEY					(TEXT("Software\\VeriSign, Inc.\\Pta3\\Cryptography"))
#define	ROAMING					1
#define NON_ROAMING				0
#define	CLIENT_INFO_LEN			8192
#define	CLIENT_INFO_SIG_LEN		4096
#define	PROFILE_NAME_ENDING		" Profile.pta"
#define	USER_NAME_ENDING		"'s "

// Exclusion attributes
#define ATTR_HIDDEN		0x00000001
#define ATTR_READ_ONLY	0x00000002
#define ATTR_SYSTEM		0x00000004
#define ATTR_ARCHIVE	0x00000008


enum FileStatus
{
	ENCRYPTED,		// file is in Safe
	DECRYPTED,		// file is out of Safe
	DELETED,		// file has been deleted
	INVALID			// invalid state
};

enum EncryptMethod
{
	MOVE,			// move file to Safe and delete original file
	LINK,			// same as above but a link is also create in original location
	INPLACE			// encrypt the file in-place and create a link in the Safe
};

enum PasswordMethod
{
	TIMEOUT,		// prompt for password on timeout
	ENCDEC			// prompt for password whenever a file or group of file is 
};					// encrypted/decrypted


enum PasswdPrompt
{
	SAFE_PROP,		// prompt for password when accessing Safe properties
	FILE_PROP,		// prompt for password when accessing File properties
	ENCRYPT,		// prompt for password before encryption
	DECRYPT			// prompt for password before decryption
};


extern UINT g_DllRefCount;
extern TCHAR g_szExtTitle[];
extern HINSTANCE g_hInst;
extern int g_nColumn[NO_LISTVW_HEADERS];
extern TCHAR g_szStoragePath[];
extern HIMAGELIST g_himlLarge;
extern HIMAGELIST g_himlSmall;
extern BOOL bBufferInit;
extern PTCHAR Buffers[3];
extern char g_Name[MAX_PATH];  
extern BOOL g_bPrompt;
extern TCHAR szWinDir[MAX_PATH], szWinSysDir[MAX_PATH], szDesktopDir[MAX_PATH];
extern BOOL g_bEncryptViewActive, g_LogOn_Off;
extern CSList *g_ExtensionList, *g_FoldersList;
extern DWORD g_ExclusionAttr;
extern EncryptMethod g_EncryptMethod;
extern HWND g_hAnimateDlg;
extern BOOL g_bCancelled;
extern BOOL g_bEncryptErrPrompt;
extern BOOL g_bReadErrPrompt;
extern BOOL g_bFilterErrPrompt;
extern BOOL g_bCheckExpiry;
extern BOOL g_bSecureDelete;

extern DWORD g_dwPlatform;


int WideCharToLocal(LPTSTR, LPWSTR, DWORD);
LPSTR _WideToMultiString(BSTR szwcInputString);
BYTE* _WideToMultiByte(BSTR szwcInputString, DWORD *dwLength);

BOOL GetGlobalSettings(void);
BOOL DeleteEntireKey(HKEY, LPTSTR);
INT CompareProfiles(LPCSTR);

void CreateImageLists(void);
void DestroyImageLists(void);

BOOL BufferInit(VOID);
void BufferDestroy(VOID);

BOOL GetDirectory(LPTSTR, LPCTSTR);
BOOL CreateDestFolder(LPCSTR, LPTSTR);
//BOOL CreateRecursiveDirectory(LPCSTR);
HRESULT CreateRecursiveDirectory(LPCTSTR lpszDirToCreate);
BOOL IsLogicalDrive(TCHAR cDrive);
void ScanUserInput();
void CreateAnimateDlg(HWND, BOOL);
void DestroyAnimateDlg();
BOOL CheckFilterOnFile(LPCTSTR);
BOOL IsParentFolder(LPCSTR, LPCTSTR);
BOOL CreatePasswordFile(VOID);
BOOL UpdateSafeIcon(VOID);
BOOL IsUserFile(LPCTSTR, LPCTSTR);
BOOL IsSigned(LPCTSTR);
BOOL GetInstallPath(VOID);
BOOL IsDesktopWindow(HWND);
BOOL GetTreePath(HWND, LPSTR);
BOOL CanDeleteFileInfo(LPCSTR);
VOID GetDecryptedFilePathSize(LPCSTR, UINT*);
VOID GetDecryptedPaths(LPCSTR, LPSTR);
BOOL CanAddFolderToEnumList(LPCSTR);

BOOL GetTemporaryFile(TCHAR *);

void SmartAppendBackslash(LPTSTR);
VOID SmartAppendFrontslash(LPTSTR);
int LocalToWideChar(LPWSTR, LPTSTR, DWORD);
BOOL GetTextFromSTRRET(IMalloc*, LPSTRRET, LPCITEMIDLIST, LPTSTR, DWORD);
int AnsiToLocal(LPTSTR, LPSTR, DWORD);
UINT AddViewMenuItems(HMENU, UINT, UINT, BOOL);
UINT AddIconsMenuItems(BOOL, HMENU , UINT , UINT , BOOL);
BOOL GetDisplaySize(__int64, TCHAR*, BOOL bDetailed = TRUE);
BOOL GetFormatted(__int64, TCHAR*);
BOOL GetDisplayTime(FILETIME*, PTCHAR, BOOL bDetailed = TRUE);
LPVOID GetViewInterface(HWND);
BOOL IsViewWindow(HWND);
BOOL RemoveFileInfoFiles(LPCTSTR);
BOOL RemoveEmptyFolder(LPCTSTR);
BOOL WriteInfoFile(LPCTSTR);
BOOL RemoveDecryptedContents(TCHAR *);
BOOL GetSafeParameters(LPCTSTR, __int64*, __int64*, ULONG*, ULONG*);
VOID UpdateCachedImage(LPCTSTR, int, int);
BOOL LogErrorMessage(LPCTSTR, UINT);

BOOL DisplayMessage(HWND, UINT, UINT);
VOID SetAnimateDlgText(LPCSTR, LPCSTR);

BOOL DeleteCertList(VOID);

BOOL SelectCert(BOOL);
BOOL SetCertSelectionCriteria(BOOL, IVSPTA *);
BOOL UpdateListOfCerts(VOID);
BOOL IsCertInVSCSP(IVSPTADllApi *);
BOOL OpenUserProfile(PCCERT_CONTEXT);
BOOL ChangeCertificate(VOID);

BOOL GetApplicationData(IVSPTA *);
BOOL SaveApplicationData(VOID);

BOOL RestorePassword(VOID);

BOOL IsEncryptionAllowed(LPDATAOBJECT);
EncryptStatus CanEncrypt(LPCTSTR);
BOOL CanEncryptSingleSel(LPDATAOBJECT);
BOOL UpdateRegistry(HKEY);
void EnumCSPs(void);
BOOL ShowHelp(LPCTSTR);
HTREEITEM GetTreeItemByName(HWND, HTREEITEM, LPCTSTR);
BOOL GetFileVersion(LPTSTR, DWORD *, DWORD *);
BOOL IsFileFolderPresent(LPCTSTR, LPCTSTR);
VOID RefreshAllViews(BOOL);
BOOL CanUseAdminCertificate(VOID);
BOOL IsFolderPresent(LPCTSTR);
BOOL HasProfilePath(LPCTSTR);
BOOL ParseProfilePath(LPCSTR, LPTSTR*, LPSTR*);
BOOL GetPTAProfileInfo(LPCSTR, LPTSTR, DWORD, LPTSTR, DWORD, LPTSTR, DWORD, BOOL*);

BOOL LogIn(BOOL);
BOOL LogOut(VOID);


void CALLBACK TimerProc(HWND, UINT, UINT, DWORD);

BOOL DecryptFiles(HDROP);
BOOL CanDecrypt(LPDATAOBJECT);

BOOL PasswordPrompt(PasswdPrompt);
BOOL CanUnloadDll(VOID);

BOOL _decode(short, DWORD*);
void _Base64Decode(PCHAR, DWORD, PCHAR, DWORD*);
void _Base64Encode(PCHAR, DWORD, PCHAR, DWORD*);

typedef struct
{
	BYTE pbHash[1024];
	DWORD dwLen;
}HashInfo, *LPHashInfo;

typedef struct 
{
	HCERTSTORE hMemCertStore;
	PCERT_CONTEXT pCertContext;
	TCHAR szIssuerDN[2*MAX_PATH];
	TCHAR szSerialNum[2*MAX_PATH];
	FILETIME ft;
}SelectedCERT, LPSelectedCERT;



#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

#ifdef _cplusplus
}
#endif   //_cplusplus


#endif   //UTIL_H