#include "stdafx.h"
#include <shlobj.h>
#include <wininet.h>
#include "vspmspP.h"	// from PM api
#include "vspmutil.h"	// from PM api
#include "vspmsp.h"		// from PM api
#include "resource.h"
#include "dlgprocs.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "util.h"
#include "policysup.h"
#include "certmgmt.h"
#include "encdeclist.h"

// Holds the current policy values. Initialised from fet.policy at the
// program start. POLICY_FILE is updated by the values in 'g_LocalPolicy'
PolicyVars g_LocalPolicy;

// Holds the settings usually present in registry
SafeSettings g_SafeProp;

// Enables/Disables password prompting
BOOL g_bLockedOut = TRUE;
BOOL g_bPasswdFail = FALSE;
UINT g_nTimerId = 0;
BOOL g_bVeriSignCSP = FALSE;

CEncDecList *g_EncrAtLogoffList = NULL, *g_DecrAtLogonList = NULL;

extern IVSProfMgmt *g_pProfMgmt;
extern SelectedCERT currSelCert;
extern TCHAR g_szWinDir[MAX_PATH_LEN], g_szWinSysDir[MAX_PATH_LEN];
extern TCHAR g_szTokenFile[MAX_PATH_LEN];
extern TCHAR g_szPolicyFile[];
extern TCHAR g_szSettingsFile[];
extern TCHAR g_szDecrSettingsFile[];
extern BOOL g_DumpDataFile;
extern BOOL g_DumpPolicyFile;
extern DWORD g_CurrentTickCount, g_PreviousTickCount;
extern TCHAR g_szInstallDir[MAX_PATH];


LoginStat AuthenticateUser(VOID)
{
	HANDLE hFind = NULL;
	WIN32_FIND_DATA wfd;
	TCHAR szAppContext[MAX_MSG_LEN], szTemp[MAX_MSG_LEN];
	TCHAR szClientInfo[CLIENT_INFO_LEN], szClientInfoSig[CLIENT_INFO_SIG_LEN];
	LoginStat stat = LOGIN_CANCEL;
	BOOL bIsProfileInfoPresent, bProfileType;
	LONG lResult = 0;
	HKEY hKey = NULL;

	do
	{
		if(!GetInstallPath())
			break;

		// Read the policy file to get the 'remote host'. First check if enterprise hosted or VeriSign hosted
		if(!ReadPolicyFileVar("Mode", "policyValue", (UINT *)szTemp, TRUE))
			break;

		if(!lstrcmpi(szTemp, "remotehost"))
		{
			if(!ReadPolicyFileVar("GlobalVar", "vsHost", (UINT *)szTemp, TRUE))
				break;

			lstrcpy(g_LocalPolicy.szRemoteHost, "https://");
			lstrcat(g_LocalPolicy.szRemoteHost, szTemp);
		}
		else
			if(!ReadPolicyFileVar("GlobalVar", "remoteHost", (UINT *)&g_LocalPolicy.szRemoteHost, TRUE))
				break;

		hFind = FindFirstFile(g_szSettingsFile, &wfd);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			// Meta data file is not present so check if a profile exists
			GetFETProfileInfo(&bIsProfileInfoPresent, &bProfileType, szAppContext, sizeof(szAppContext),
							  szClientInfo, sizeof(szClientInfo), szClientInfoSig, sizeof(szClientInfoSig));

			if(!bIsProfileInfoPresent)	// Profile path not in Registry
			{
				// Select a certificate to logon first time
				if(!SelectCert(TRUE))
					break;

				if(g_bVeriSignCSP)
				{	// Open profile for the first time
					if(!OpenUserProfile(currSelCert.pCertContext))
						break;
				}

				if(!UpdateListOfCerts())
					break;

				if(!InitSafe())
					break;

				stat = LOGIN_OK;
				break;
			}	
			else
			{
				g_bVeriSignCSP = TRUE;

				if(!OpenUserProfile(NULL))
					break;

				if(!InitSafe())
					break;

				if(!SelectCert(FALSE))
					break;

				stat = LOGIN_OK;
				break;
			}
		}
		else
		{
			FindClose(hFind);
			g_bVeriSignCSP = FALSE;

			// Since for a non-PTA cert we are no longer supporting a password, this verify
			// password will not actually verify a password, it will just verify the metadata file
			if(!VerifyPassword())
				break;
			
			if(!InitSafe())
				break;
				
			// Get the encryption certificate selected in the global variable
			if(!SelectCert(FALSE))	
				break;				

			stat = LOGIN_OK;
			break;
		}

	} while(0);

	if(hKey)
	{
		RegCloseKey(hKey);
		hKey = NULL;
	}

    if (stat != LOGIN_OK) 
    {
		if(g_bVeriSignCSP)
        {
			if(g_pProfMgmt) 
			{
				g_pProfMgmt->CloseProfile();
				g_pProfMgmt->Release();
				g_pProfMgmt = NULL;
				g_bVeriSignCSP = FALSE;
			}
        }
    }

	return stat;
}


BOOL InitSafe(VOID)
{
	g_EncrAtLogoffList->DeleteList();
	g_DecrAtLogonList->DeleteList();
	g_ExtensionList->DeleteList();
	g_FoldersList->DeleteList();

	HANDLE hFind = NULL;
	WIN32_FIND_DATA wfd;
	DWORD dwError;
	TCHAR szMsg[MAX_MSG_LEN], szFmt[MAX_MSG_LEN], szCachedPolyFile[MAX_PATH_LEN];

	// Construct the path of the cached policy file
	lstrcpy(szCachedPolyFile, g_szInstallDir);
	lstrcat(szCachedPolyFile, "\\");
	lstrcat(szCachedPolyFile, POLICY_FILE);

	// Get current day
	FILETIME ftCurrentDay;
	SYSTEMTIME CurrentTime;
	GetSystemTime(&CurrentTime);
	CurrentTime.wHour = CurrentTime.wMinute = CurrentTime.wSecond = 0;
	CurrentTime.wMilliseconds = 0;
	SystemTimeToFileTime(&CurrentTime, &ftCurrentDay);

	hFind = FindFirstFile(g_szDecrSettingsFile, &wfd);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);

		if(!GetSafeProps())
			return FALSE;

		// Check if Policy file needs to be updated. 'g_SafeProp.ftDay' is the day when the policy file was last downloaded. 
		UDATE uDate;
		DATE Today, LastUpdatedDay;
		ULONG ulFlags = 0;

		uDate.st = CurrentTime;
		VarDateFromUdate(&uDate, ulFlags, &Today);

		FileTimeToSystemTime(&g_SafeProp.ftDay, &uDate.st);
		VarDateFromUdate(&uDate, ulFlags, &LastUpdatedDay);

		if(Today - LastUpdatedDay >= g_SafeProp.lPolicyTimeout)
		{
			if(!DownloadRemotePolicyFile(g_szPolicyFile, &dwError))
			{
				// Ask user whether he wants to continue with current policy settings
				if(dwError)
				{
					wsprintf(szMsg, "InitSafe() : Could not update Policy File \'%s\' because of Network error.", g_szPolicyFile);
					LogErrorMessage(szMsg, dwError);
					LoadString(g_hInst, IDS_POLICY_UPDATE_ERR, szMsg, MAX_PATH);
					if(MessageBox(GetFocus(), szMsg, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
						return FALSE;							
				}
				else
				{
					wsprintf(szMsg, "InitSafe() : Could not update Policy File \'%s\' because of registry error.", g_szPolicyFile);
					LogErrorMessage(szMsg, 0);
					LoadString(g_hInst, IDS_POLICY_UPDATE_ERR, szMsg, MAX_PATH);
					if(MessageBox(GetFocus(), szMsg, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
						return FALSE;
				}
			}
			else
			{
				// If download succeeded update the policy file in our install directory also
				if(!CopyFile(g_szPolicyFile, szCachedPolyFile, FALSE))
				{
					dwError = GetLastError();
					LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_MSG_LEN);
					wsprintf(szFmt, szMsg, g_szPolicyFile, szCachedPolyFile);
					MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
					wsprintf(szMsg, "InitSafe() : Error overwritting policy file \'%s\'", szCachedPolyFile);
					LogErrorMessage(szMsg, dwError);
					return FALSE;
				}

				// Since file has been downloaded update the day in 'Safe' settings
				g_SafeProp.ftDay.dwLowDateTime  = ftCurrentDay.dwLowDateTime;
				g_SafeProp.ftDay.dwHighDateTime = ftCurrentDay.dwHighDateTime;
			}
		}
	} // metadata file present
	else
	{
		// metadata file not present, check if POLICY_FILE is present in our install directory
		hFind = FindFirstFile(szCachedPolyFile, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			FindClose(hFind);

			// Check if policy file is old, if so get it again
			if(IsOldPolicyFile(szCachedPolyFile))
			{
				if(!DownloadRemotePolicyFile(szCachedPolyFile, &dwError))
				{
					// Ask user whether he wants to continue with current policy settings
					if(dwError)
					{
						LogErrorMessage("InitSafe() : Error downloading policy file", dwError);
						LoadString(g_hInst, IDS_POLICY_DOWNLOAD_ERR, szMsg, MAX_MSG_LEN);
						if(MessageBox(GetFocus(), szMsg, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
							return FALSE;							
					}
					else
					{
						LoadString(g_hInst, IDS_CONTINUE_POLICY, szMsg, MAX_MSG_LEN);
						if(MessageBox(GetFocus(), szMsg, "Safe", MB_YESNO | MB_ICONINFORMATION) == IDNO)
							return FALSE;
					}
				}
			}

			// Copy file to 'Safe' directory
			if(!CopyFile(szCachedPolyFile, g_szPolicyFile, FALSE))
			{
				dwError = GetLastError();
				LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_MSG_LEN);
				wsprintf(szFmt, szMsg, szCachedPolyFile, g_szPolicyFile);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
				wsprintf(szMsg, "InitSafe() : Error overwritting policy file \'%s\'", g_szPolicyFile);
				LogErrorMessage(szMsg, dwError);
				return FALSE;
			}
		}
		else
		{
			// File not present in the install directory also, download it
			if(!DownloadRemotePolicyFile(g_szPolicyFile, &dwError))
			{
				if(dwError)
				{
					if(dwError == ERROR_INTERNET_CANNOT_CONNECT)
					{
						LoadString(g_hInst, IDS_CONNECT_ERROR, szMsg, MAX_MSG_LEN);
						wsprintf(szFmt, szMsg, "");
						MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
					}
					else
						DisplayMessage(GetFocus(), IDS_NETWORK_ERROR, MB_OK | MB_ICONERROR);

					LogErrorMessage("InitSafe() : Could not download policy file", dwError);
				}

				return FALSE;
			}

			// Copy file to install directory
			if(!CopyFile(g_szPolicyFile, szCachedPolyFile, FALSE))
			{
				dwError = GetLastError();
				LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_MSG_LEN);
				wsprintf(szFmt, szMsg, g_szPolicyFile, szCachedPolyFile);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
				wsprintf(szMsg, "InitSafe() : Error overwritting policy file \'%s\'", szCachedPolyFile);
				LogErrorMessage(szMsg, dwError);
				return FALSE;
			}
		}

		// Policy file got for the first time. Initialise 'g_SafeProp.ftDay'
		g_SafeProp.ftDay.dwLowDateTime  = ftCurrentDay.dwLowDateTime;
		g_SafeProp.ftDay.dwHighDateTime = ftCurrentDay.dwHighDateTime;

		// Also initialise the column widths to some default values
		for(int i = 0; i < 10; i++)
			g_SafeProp.lDisplaySizes[i] = 0x70;

		// Set 'Safe' default values
		g_SafeProp.bDecryptPane = FALSE;
		//g_SafeProp.pCurrEncrCert = NULL;
		g_SafeProp.pOldEncrCerts = NULL;
	}

	// Read the policy file using the Policy Manager API
	ReadPolicyFile();		
	
	// Set the policy file timeout in 'Safe' properties also. This will be used to determine 
	// whether Policy file needs to to downloaded without first reading it
	g_SafeProp.lPolicyTimeout = g_LocalPolicy.PolicyTimeout;

	if(g_nTimerId)
	{
		KillTimer(NULL, g_nTimerId);
		g_nTimerId = 0;
	}

	g_PreviousTickCount = g_CurrentTickCount = GetTickCount();

	// If VSCSP use password timeout mechanism supported by the CSP
	if(g_bVeriSignCSP)
	{
		HRESULT hr;
		VARIANT varTimeOut;

		varTimeOut.vt = VT_I2;

		/* PRRemove
		if(g_LocalPolicy.PasswdMethod == ENCDEC)
		{
			g_LocalPolicy.PasswdMethod = TIMEOUT;
			g_LocalPolicy.PasswordPromptTimeout = 15;
		}

		if(g_LocalPolicy.PasswdMethod == ENCDEC)
			varTimeOut.iVal = 0;
		else
			varTimeOut.iVal = g_LocalPolicy.PasswordPromptTimeout;
		*/

		varTimeOut.iVal = g_LocalPolicy.PasswordPromptTimeout;

		hr = g_pProfMgmt->put_PasswdTimeOut(varTimeOut);
		if(hr != S_OK)
		{
			LogErrorMessage("InitSafe() : g_pProfMgmt->put_PasswdTimeOut() failed", hr);
			return FALSE;
		}
	}

	return TRUE;
}

// Compare the creation date of the file with today's date. If the difference is greater 
// than the policy timeout then return TRUE
BOOL IsOldPolicyFile(LPCTSTR lpszPolicyFile)
{
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN];
	BY_HANDLE_FILE_INFORMATION fad;
	DWORD dwErr = 0;

	HANDLE hFile = CreateFile(lpszPolicyFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
							  FILE_ATTRIBUTE_ARCHIVE, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "IsOldPolicyFile() : Error opening file \'%s\'", lpszPolicyFile);
		LogErrorMessage(szMsg, dwErr);
		return FALSE;
	}

	GetFileInformationByHandle(hFile, &fad);
	CloseHandle(hFile);

	// Read the Policy File to get the timeout value
	DWORD dwPolicyTimeout;
	VSPM_STATUS status;
	VSPM_Item item = NULL;
	UCHAR *value = NULL;
	VSPM_Container AppContainer = NULL, FileEncrContainer = NULL;
	VSPM_Descriptor fd = VSPM_Open(lpszPolicyFile, &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_OPEN_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "IsOldPolicyFile() : Cannot open the Policy File \'%s\'", lpszPolicyFile);
		LogErrorMessage(szMsg, status);
		return FALSE;
	}

	AppContainer = VSPM_GetContainerByNameFromDescriptor(fd, "Apps", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_MSG_LEN);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("IsOldPolicyFile() : Failed to open Apps container", status);
		VSPM_Close(fd);
		return FALSE;
	}

	FileEncrContainer = VSPM_GetContainerByName(AppContainer, "FileEncryption", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_MSG_LEN);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("IsOldPolicyFile() : Failed to open File Encryption container", status);
		VSPM_FreeContainer(AppContainer, &status);
		VSPM_Close(fd);
		return FALSE;
	}

	item = VSPM_GetItemByName(FileEncrContainer, "PolicyTimeout", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			dwPolicyTimeout = atoi((const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	VSPM_FreeContainer(FileEncrContainer, &status);
	VSPM_FreeContainer(AppContainer, &status);
	VSPM_Close(fd);

	// Check if Policy file we have is old, get current day
	SYSTEMTIME CurrentTime;
	GetSystemTime(&CurrentTime);
	CurrentTime.wHour = CurrentTime.wMinute = CurrentTime.wSecond = 0;
	CurrentTime.wMilliseconds = 0;

	UDATE uDate;
	DATE Today, FileCreationDay;
	ULONG ulFlags = 0;

	uDate.st = CurrentTime;
	VarDateFromUdate(&uDate, ulFlags, &Today);

	FileTimeToSystemTime(&fad.ftCreationTime, &uDate.st);
	uDate.st.wHour = uDate.st.wMinute = uDate.st.wSecond = 0;
	uDate.st.wMilliseconds = 0;

	VarDateFromUdate(&uDate, ulFlags, &FileCreationDay);

	if(Today - FileCreationDay > dwPolicyTimeout)
		return TRUE;
	else
		return FALSE;
}


BOOL UpdateSafe(VOID)
{
	TCHAR szMsg[MAX_MSG_LEN], szFmt[MAX_MSG_LEN], *pStr = NULL, *pToSign = NULL;
	DWORD dwErr, dwDetachedSigLen = 0, dwCurrOffset = 0;
	HANDLE hWriteFile = NULL;
	BOOL bSignature = FALSE;
	ULONG ulCryptErr = 0;
	PSIGN_CONTEXT pSignContext = NULL;
	BYTE *pbDetachedSig = NULL;

	// If already locked out no need to update Safe as it must already have been done
	if(g_bLockedOut)
		return TRUE;

	// Either no certificates or UpdateSafe() has already been called
	if(!g_SafeProp.pCurrEncrCert)
		return TRUE;

	HANDLE hDecrDataFile = NULL, hPolicyFile = NULL;
	TCHAR cReadBuf[MAX_READ_SIZE];
	DWORD dwBytesRead, dwBytesWritten;

	hDecrDataFile = CreateFile(g_szDecrSettingsFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
							   FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDecrDataFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "UpdateSafe:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
		LogErrorMessage(szMsg, dwErr);
		return FALSE;
	}	
	
	// Skip 4 bytes, offset of signature will come here
	SetFilePointer(hDecrDataFile, 4, NULL, FILE_BEGIN);

	// Decrypt Pane
	WriteFile(hDecrDataFile, (PBYTE)&g_SafeProp.bDecryptPane, sizeof(DWORD), &dwBytesWritten, NULL);

	// DisplaySettings 
	WriteFile(hDecrDataFile, (PBYTE)g_SafeProp.lDisplaySizes, 10*sizeof(DWORD), &dwBytesWritten, NULL);

	// Policy File Timeout 
	WriteFile(hDecrDataFile, (PBYTE)&g_SafeProp.lPolicyTimeout, sizeof(DWORD), &dwBytesWritten, NULL);

	// Last Date LOWORD
	WriteFile(hDecrDataFile, (PBYTE)&g_SafeProp.ftDay.dwLowDateTime, sizeof(DWORD), &dwBytesWritten, NULL);

	// Last Date HIWORD
	WriteFile(hDecrDataFile, (PBYTE)&g_SafeProp.ftDay.dwHighDateTime, sizeof(DWORD), &dwBytesWritten, NULL);	

	// Num of Encryption certs
	LPCertDetails pCert = g_SafeProp.pCurrEncrCert;
	DWORD nCertCnt = 0;
	if(pCert)
		nCertCnt++;

	pCert = g_SafeProp.pOldEncrCerts;
	while(pCert)
	{
		if(!lstrcmpi(pCert->szSerialNum, g_SafeProp.pCurrEncrCert->szSerialNum) &&
		   !lstrcmpi(pCert->szIssuerDN, g_SafeProp.pCurrEncrCert->szIssuerDN))
		{
			pCert = pCert->pNext;
			continue;
		}

		if(pCert->dwSigLen == 0)
		{
			pCert = pCert->pNext;
			continue;
		}

		nCertCnt++;
		pCert = pCert->pNext;
	}

	WriteFile(hDecrDataFile, (PBYTE)&nCertCnt, sizeof(DWORD), &dwBytesWritten, NULL);

	// Num Files to be encrypted at logoff 
	DWORD nListCnt = 0;
	if(g_EncrAtLogoffList)
		nListCnt = g_EncrAtLogoffList->GetCount();

	WriteFile(hDecrDataFile, (PBYTE)&nListCnt, sizeof(DWORD), &dwBytesWritten, NULL);

	// Num Files to be decrypted at logon 
	nListCnt = 0;
	if(g_DecrAtLogonList)
		nListCnt = g_DecrAtLogonList->GetCount();

	WriteFile(hDecrDataFile, (PBYTE)&nListCnt, sizeof(DWORD), &dwBytesWritten, NULL);

	// Certificate details of current encryption cert. This cert has to be present
	pCert = g_SafeProp.pCurrEncrCert;
	DWORD dwLen = 0;

	// SerialNum
	dwLen = lstrlen(pCert->szSerialNum);
	WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
	WriteFile(hDecrDataFile, (PBYTE)pCert->szSerialNum, dwLen, &dwBytesWritten, NULL);

	// IssuerDN
	dwLen = lstrlen(pCert->szIssuerDN);
	WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
	WriteFile(hDecrDataFile, (PBYTE)pCert->szIssuerDN, dwLen, &dwBytesWritten, NULL);

	// Signature
	// First check if the signature is present, if not create one here
	if(pCert->dwSigLen == 0)
	{
		pToSign = (TCHAR *)malloc(lstrlen(pCert->szSerialNum) + lstrlen(pCert->szIssuerDN) + 1);
		if(!pToSign)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("UpdateSafe() : Out of memory", 0);
			CloseHandle(hDecrDataFile);
			return FALSE;
		}
		
		lstrcpy(pToSign, pCert->szSerialNum);
		lstrcat(pToSign, pCert->szIssuerDN);

		if(SignStart(currSelCert.pCertContext, szOID_RSA_MD5, &pSignContext, &ulCryptErr) != S_OK)
		{
			LogErrorMessage("UpdateSafe() : SignStart() failed.", ulCryptErr);
			CloseHandle(hDecrDataFile);
			return FALSE;
		}
			
		if(SignEnd(pSignContext, (PBYTE)pToSign, lstrlen(pToSign), &ulCryptErr, &pbDetachedSig, 
				   &dwDetachedSigLen) != S_OK)
		{
			LogErrorMessage("UpdateSafe() : SignEnd() failed.", ulCryptErr);
			CloseHandle(hDecrDataFile);
			return FALSE;
		}

		pCert->dwSigLen = dwDetachedSigLen;
		memcpy(pCert->Signature, (const char *)pbDetachedSig, dwDetachedSigLen);

		free(pbDetachedSig);
		pbDetachedSig = NULL;
	}

	dwLen = pCert->dwSigLen;
	WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
	WriteFile(hDecrDataFile, pCert->Signature, dwLen, &dwBytesWritten, NULL);

	// Certificate details of old encryption cert.
	pCert = g_SafeProp.pOldEncrCerts;
	while(pCert)
	{
		// If the SerialNum and IssuerDN of the current selected cert is same as that of one
		// in the list of old certs then do not add the old cert in the list.
		// Also make the check to see if the dwSigLen is 0. If so don't add.
		// These check are done to prevent the problem that occurs when the user log's on to
		// the Safe next time and an error comes up saying 'Invalid user trying to access the 
		// Safe'

		if(!lstrcmpi(pCert->szSerialNum, g_SafeProp.pCurrEncrCert->szSerialNum) &&
		   !lstrcmpi(pCert->szIssuerDN, g_SafeProp.pCurrEncrCert->szIssuerDN))
		{
			pCert = pCert->pNext;
			continue;
		}

		if(pCert->dwSigLen == 0)
		{
			pCert = pCert->pNext;
			continue;
		}

		// SerialNum
		dwLen = lstrlen(pCert->szSerialNum);
		WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
		WriteFile(hDecrDataFile, (PBYTE)pCert->szSerialNum, dwLen, &dwBytesWritten, NULL);

		// IssuerDN
		dwLen = lstrlen(pCert->szIssuerDN);
		WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
		WriteFile(hDecrDataFile, (PBYTE)pCert->szIssuerDN, dwLen, &dwBytesWritten, NULL);

		// Signature
		dwLen = pCert->dwSigLen;
		WriteFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesWritten, NULL);
		WriteFile(hDecrDataFile, pCert->Signature, dwLen, &dwBytesWritten, NULL);

		pCert = pCert->pNext;
	}

	// List of files to be encrypted at logoff
	DWORD dwListSize = 0, dwFilePos;
	LPEncDec lpList = g_EncrAtLogoffList->GetNextItem(NULL);
	if(lpList)
	{
		// Leave 4 bytes for the length of this list
		dwFilePos = GetFileSize(hDecrDataFile, NULL);
		SetFilePointer(hDecrDataFile, sizeof(DWORD), NULL, FILE_CURRENT);

		while(lpList)
		{
			WriteFile(hDecrDataFile, (PBYTE)lpList->szOrigLoc, lstrlen(lpList->szOrigLoc), &dwBytesRead, NULL);
			WriteFile(hDecrDataFile, ";", 1, &dwBytesRead, NULL);
			WriteFile(hDecrDataFile, (PBYTE)lpList->szLocInSafe, lstrlen(lpList->szLocInSafe), &dwBytesRead, NULL);
			lpList = g_EncrAtLogoffList->GetNextItem(lpList->szOrigLoc);

			if(lpList)
				WriteFile(hDecrDataFile, ";", 1, &dwBytesRead, NULL);
		}

		dwListSize = GetFileSize(hDecrDataFile, NULL) - dwFilePos - sizeof(DWORD);

		// go back and write the length of the list
		SetFilePointer(hDecrDataFile, dwFilePos, NULL, FILE_BEGIN);
		WriteFile(hDecrDataFile, (PBYTE)&dwListSize, sizeof(DWORD), &dwBytesRead, NULL);
		SetFilePointer(hDecrDataFile, dwListSize, NULL, FILE_CURRENT);
	}
	else
		WriteFile(hDecrDataFile, (PBYTE)&dwListSize, sizeof(DWORD), &dwBytesRead, NULL);


	// List of files to be decrypted at logon
	dwListSize = 0;
	lpList = g_DecrAtLogonList->GetNextItem(NULL);
	if(lpList)
	{
		// Leave 4 bytes for the length of this list
		dwFilePos = GetFileSize(hDecrDataFile, NULL);
		SetFilePointer(hDecrDataFile, sizeof(DWORD), NULL, FILE_CURRENT);
	
		while(lpList)
		{
			WriteFile(hDecrDataFile, (PBYTE)lpList->szOrigLoc, lstrlen(lpList->szOrigLoc), &dwBytesRead, NULL);
			WriteFile(hDecrDataFile, ";", 1, &dwBytesRead, NULL);
			WriteFile(hDecrDataFile, (PBYTE)lpList->szLocInSafe, lstrlen(lpList->szLocInSafe), &dwBytesRead, NULL);
			lpList = g_DecrAtLogonList->GetNextItem(lpList->szOrigLoc);

			if(lpList)
				WriteFile(hDecrDataFile, ";", 1, &dwBytesRead, NULL);
		}

		dwListSize = GetFileSize(hDecrDataFile, NULL) - dwFilePos - sizeof(DWORD);

		// go back and write the length of the list
		SetFilePointer(hDecrDataFile, dwFilePos, NULL, FILE_BEGIN);
		WriteFile(hDecrDataFile, (PBYTE)&dwListSize, sizeof(DWORD), &dwBytesRead, NULL);
		dwFilePos = SetFilePointer(hDecrDataFile, dwListSize, NULL, FILE_CURRENT);
	}
	else
		WriteFile(hDecrDataFile, (PBYTE)&dwListSize, sizeof(DWORD), &dwBytesRead, NULL);

	// Generate the policy file
	WritePolicyFile();

	// Write the policy file in the 'dfedecrdata'
	hPolicyFile = CreateFile(g_szPolicyFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hPolicyFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "UpdateSafe:CreateFile() for \'%s\' failed", g_szPolicyFile);
		LogErrorMessage(szMsg, dwErr);
		return FALSE;
	}	

	// Write length of the policy file
	DWORD dwFileSize = GetFileSize(hPolicyFile, NULL);
	WriteFile(hDecrDataFile, (PBYTE)&dwFileSize, sizeof(DWORD), &dwBytesRead, NULL);

	while(ReadFile(hPolicyFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		if(dwBytesRead == 0)
			break;

		if(!WriteFile(hDecrDataFile, cReadBuf, dwBytesRead, &dwBytesWritten, NULL))
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "UpdateSafe : WriteFile() for \'%s\' failed", g_szDecrSettingsFile);
			LogErrorMessage(szMsg, dwErr);
			break;
		}

		if(dwBytesRead < MAX_READ_SIZE)
			break;
	}

	dwFileSize = GetFileSize(hDecrDataFile, NULL);

	// Now write the offset of the signature at the beginning
	SetFilePointer(hDecrDataFile, 0, 0, FILE_BEGIN);
	WriteFile(hDecrDataFile, (PBYTE)&dwFileSize, sizeof(DWORD), &dwBytesRead, NULL);

	CloseHandle(hPolicyFile);
	CloseHandle(hDecrDataFile);
	
	// Now sign the 'dfedecrdata' file using the Encryption cert
	pSignContext = NULL;
	dwDetachedSigLen = 0;
	pbDetachedSig = NULL;

	if(SignStart(currSelCert.pCertContext, szOID_RSA_MD5, &pSignContext, &dwErr) != S_OK)
		return FALSE;

	hDecrDataFile = CreateFile(g_szDecrSettingsFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
							   FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDecrDataFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "UpdateSafe:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
		LogErrorMessage(szMsg, dwErr);
		return FALSE;
	}	

	dwFileSize = GetFileSize(hDecrDataFile, NULL);

	while(ReadFile(hDecrDataFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		dwCurrOffset += dwBytesRead;

		if(dwCurrOffset < dwFileSize)
		{
			if(SignUpdate(pSignContext, (PBYTE)cReadBuf, dwBytesRead, &dwErr) != S_OK)
				break;
		}
		else
		{
			if(SignEnd(pSignContext, (PBYTE)cReadBuf, dwBytesRead, &dwErr, &pbDetachedSig, &dwDetachedSigLen) == S_OK)
				bSignature = TRUE;
				
			break;
		}
	}	// end while

	CloseHandle(hDecrDataFile);

	if(bSignature)
	{
		// Write the detached signature at the end of the 'decrdatafile'
		hDecrDataFile = CreateFile(g_szDecrSettingsFile, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 
								   FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hDecrDataFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "UpdateSafe:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
			LogErrorMessage(szMsg, dwErr);
			return FALSE;
		}	

		SetFilePointer(hDecrDataFile, 0, NULL, FILE_END);

		if(pbDetachedSig)
			WriteFile(hDecrDataFile, pbDetachedSig, dwDetachedSigLen, &dwBytesWritten, NULL);

		CloseHandle(hDecrDataFile);

		if(pbDetachedSig)
			free(pbDetachedSig);

		DeleteFile(g_szSettingsFile);

		// If VSCSP store metadata in profile else store it encrypted in Safe directory
		if(g_bVeriSignCSP)
			SaveApplicationData();
		else
		{
	/* PRRemove
			// Now encrypt the file using the hash of the password
			EncrDecrFileUsingPasswd(g_szDecrSettingsFile, g_szSettingsFile, 1);	// '1' for Encrypt

			// Create a backup of the metadata file(vsettings)
			TCHAR szBackUp[MAX_PATH];
			lstrcpy(szBackUp, g_szSettingsFile);
			lstrcat(szBackUp, ".bak");
			CopyFile(g_szSettingsFile, szBackUp, FALSE);

			// Also create the password recovery file
			CreatePasswordFile();
	*/
			// Just copy the 'g_szDecrSettingsFile' file to the 'g_szSettingsFile' file as it is
			// since there is no password now
			CopyFile(g_szDecrSettingsFile, g_szSettingsFile, FALSE);
		}

		if(!g_DumpDataFile)
			DeleteFile(g_szDecrSettingsFile);

		return TRUE;		
	}
	else		
		return FALSE;
}

/*
BOOL SetDefaultSafeValues(VOID)
{
	g_LocalPolicy.bSecureDelete		= TRUE;
	g_LocalPolicy.bSignatureReqd	= TRUE;
	g_LocalPolicy.EncryptMethod		= MOVE;
	g_LocalPolicy.LockOutPeriod		= 5;  // 5 mins
	lstrcpy(g_LocalPolicy.EncryptionAlg, "RC2-XX bits");
	lstrcpy(g_LocalPolicy.HashAlg, "SHA-1");
	lstrcpy(g_LocalPolicy.szRemoteHost, "https://digitalid.verisign.com/client/index.html");
	g_LocalPolicy.szAppLogoUrl[0] = '\0';
	g_LocalPolicy.szLoginHelpUrl[0] = '\0';
	g_LocalPolicy.szRenewalHelpUrl[0] = '\0';
	g_LocalPolicy.EnterpriseMode = TRUE;
	g_LocalPolicy.PolicyTimeout = 0;	  // 0 days

	g_SafeProp.bDecryptPane = FALSE;
	for(int i = 0; i < 10; i++)
		g_SafeProp.lDisplaySizes[i] = 0x70;

	g_SafeProp.lPolicyTimeout = 0;	// insures downloading of policy file if not present
	//g_SafeProp.pCurrEncrCert = NULL;
	g_SafeProp.pOldEncrCerts = NULL;

	SYSTEMTIME CurrentTime;
	GetSystemTime(&CurrentTime);
	SystemTimeToFileTime(&CurrentTime, &g_SafeProp.ftDay);
	
	g_EncrAtLogoffList->DeleteList();
	g_DecrAtLogonList->DeleteList();

	return TRUE;
}
*/

BOOL GetSafeProps(VOID)
{
	TCHAR szMsg[MAX_MSG_LEN], szFmt[MAX_MSG_LEN], *pStr = NULL, *pStr2 = NULL;
	DWORD dwErr = 0;
	UINT i = 0;

	DWORD dwBytesRead = 0;
	HANDLE hDecrDataFile = CreateFile(g_szDecrSettingsFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 
									  FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDecrDataFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "GetSafeProp:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
		LogErrorMessage(szMsg, dwErr);
		DeleteFile(g_szDecrSettingsFile);
		return FALSE;
	}

	// Skip the 1st DWORDS which contains the signature offset
	SetFilePointer(hDecrDataFile, sizeof(DWORD), NULL, FILE_BEGIN);

	// Decrypt Pane
	ReadFile(hDecrDataFile, (PBYTE)&g_SafeProp.bDecryptPane, sizeof(DWORD), &dwBytesRead, NULL);

	// Display settings
	ReadFile(hDecrDataFile, (PBYTE)g_SafeProp.lDisplaySizes, 10*sizeof(DWORD), &dwBytesRead, NULL);

	// Policy File Timeout
	ReadFile(hDecrDataFile, (PBYTE)&g_SafeProp.lPolicyTimeout, sizeof(DWORD), &dwBytesRead, NULL);

	// Date
	ReadFile(hDecrDataFile, (PBYTE)&g_SafeProp.ftDay.dwLowDateTime, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, (PBYTE)&g_SafeProp.ftDay.dwHighDateTime, sizeof(DWORD), &dwBytesRead, NULL);

	// Num Encryption certs
	UINT nEncrCerts = 0;
	LPCertDetails pPrevCert = NULL, *pCurrCert = NULL;
	ReadFile(hDecrDataFile, (PBYTE)&nEncrCerts, sizeof(DWORD), &dwBytesRead, NULL);

	// Num of files to Encrypt/Decrypt at logon/logoff
	UINT nEncrAtLogoff = 0, nDecrAtLogon = 0;
	ReadFile(hDecrDataFile, (PBYTE)&nEncrAtLogoff, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, (PBYTE)&nDecrAtLogon, sizeof(DWORD), &dwBytesRead, NULL);
	
	// One encryption cert has to be present as the file is encrypted using it
	pCurrCert = &g_SafeProp.pCurrEncrCert;
	*pCurrCert = (LPCertDetails)malloc(sizeof(CertDetails));

	// Serial Num
	DWORD dwLen;
	ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, (*pCurrCert)->szSerialNum, dwLen, &dwBytesRead, NULL);
	(*pCurrCert)->szSerialNum[dwLen] = '\0';

	// Issuer DN
	ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, (*pCurrCert)->szIssuerDN, dwLen, &dwBytesRead, NULL);
	(*pCurrCert)->szIssuerDN[dwLen] = '\0';

	// Signature
	ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, (*pCurrCert)->Signature, dwLen, &dwBytesRead, NULL);
	(*pCurrCert)->dwSigLen = dwLen;

	(*pCurrCert)->pNext = NULL;

	nEncrCerts--;

	pCurrCert = &g_SafeProp.pOldEncrCerts;
	pPrevCert = NULL;
	while(nEncrCerts)
	{
		*pCurrCert = (LPCertDetails)malloc(sizeof(CertDetails));

		// Serial Num
		ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
		ReadFile(hDecrDataFile, (*pCurrCert)->szSerialNum, dwLen, &dwBytesRead, NULL);
		(*pCurrCert)->szSerialNum[dwLen] = '\0';

		// Issuer DN
		ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
		ReadFile(hDecrDataFile, (*pCurrCert)->szIssuerDN, dwLen, &dwBytesRead, NULL);
		(*pCurrCert)->szIssuerDN[dwLen] = '\0';

		// Signature
		ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
		ReadFile(hDecrDataFile, (*pCurrCert)->Signature, dwLen, &dwBytesRead, NULL);
		(*pCurrCert)->dwSigLen = dwLen;

		(*pCurrCert)->pNext = pPrevCert;
		pPrevCert = *pCurrCert;
		nEncrCerts--;
	}

	// Verify the signature on the IDN and SN. The IDN and SN are signed using the
	// certificate identified by the IDN and SN. During decryption the IDN and SN 
	// of the certificate used to decrypt is compared with that present in list.
	// If it compares then the user logged on to the Safe is valid. 
	// Signing is necessary bcos a malicious user 'M' can construct a 'dfedata' 
	// file with a IDN and SN of the encrypted files. So we need to sign it.
	// Another attack which M can launch is replace the 'dfedata' file with his 
	// 'dfedata' file. In this case the verification of signatures on all the 
	// certificate list will succeed but the extra check which we are performing
	// during decryption(described above) will fail bcos 'M' cannot generate a 
	// 'dfedata' file with a valid IDN and SN since he cannot sign the IDN and SN
	// by the certificate identified by the IDN and SN as he does not have access
	// to the private keys.
	if(!VerifySigList())
	{
		DisplayMessage(GetFocus(), IDS_INVALID_USER, MB_OK | MB_ICONERROR);
		LogErrorMessage("GetSafeProps() : Failed to verify the signature on the Certificate list", 0);
		CloseHandle(hDecrDataFile);
		DeleteFile(g_szDecrSettingsFile);
		return FALSE;
	}


	// Construct the list of files to be Encr/Decr at logoff/logon
	TCHAR szOrigLoc[MAX_PATH_LEN], szLocInSafe[MAX_PATH_LEN];
	i = 0;
	UINT j = 0, nLen = 0;
	pStr = NULL;

	// Length of the list
	ReadFile(hDecrDataFile, (PBYTE)&nLen, sizeof(DWORD), &dwBytesRead, NULL);
	if(nLen)
	{
		TCHAR *pEncrData = (TCHAR *)malloc(nLen);
		if(!pEncrData)
			MessageBox(GetFocus(), "Memory allocation failed", "Safe", MB_OK);

		ReadFile(hDecrDataFile, (PBYTE)pEncrData, nLen, &dwBytesRead, NULL);

		pStr = pEncrData;
		do
		{
			for(j = 0; pStr[i] != ';'; i++, j++)
				szOrigLoc[j] = pStr[i];

			szOrigLoc[j] = '\0';

			i++;
			for(j = 0; pStr[i] != ';'; i++, j++)
			{
				if(i == nLen)
					break;

				szLocInSafe[j] = pStr[i];
			}

			szLocInSafe[j] = '\0';
			i++;

			g_EncrAtLogoffList->AddToList(szOrigLoc, szLocInSafe);
		}
		while(i < nLen);

		free(pEncrData);
	}

	// Length of the list
	ReadFile(hDecrDataFile, (PBYTE)&nLen, sizeof(DWORD), &dwBytesRead, NULL);
	if(nLen)
	{
		TCHAR *pDecrData = (TCHAR *)malloc(nLen);
		if(!pDecrData)
			MessageBox(GetFocus(), "Memory allocation failed", "Safe", MB_OK);

		ReadFile(hDecrDataFile, (PBYTE)pDecrData, nLen, &dwBytesRead, NULL);

		pStr = pDecrData;
		i = 0;
		do
		{
			for(j = 0; pStr[i] != ';'; i++, j++)
				szOrigLoc[j] = pStr[i];

			szOrigLoc[j] = '\0';

			i++;
			for(j = 0; pStr[i] != ';'; i++, j++)
			{
				szLocInSafe[j] = pStr[i];
				if(i == nLen)
					break;
			}

			szLocInSafe[j] = '\0';
			i++;

			g_DecrAtLogonList->AddToList(szOrigLoc, szLocInSafe);
		}
		while(i < nLen);

		free(pDecrData);
	}

	// Create the policy file
	DWORD dwFileSize = 0;
	ReadFile(hDecrDataFile, (PBYTE)&dwFileSize, sizeof(DWORD), &dwBytesRead, NULL);
	
	HANDLE hPolicyFile = CreateFile(g_szPolicyFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
									FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hPolicyFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "GetSafeProp:CreateFile() for \'%s\' failed", g_szPolicyFile);
		LogErrorMessage(szMsg, dwErr);
		CloseHandle(hDecrDataFile);
		DeleteFile(g_szDecrSettingsFile);
		return FALSE;
	}

	TCHAR cReadBuf[MAX_READ_SIZE];
	DWORD dwTotalBytesRead = 0, dwBytesWritten;
	while(ReadFile(hDecrDataFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		dwTotalBytesRead += dwBytesRead;

		if(dwTotalBytesRead >= dwFileSize)
			dwBytesRead -= (dwTotalBytesRead - dwFileSize);

		if(!WriteFile(hPolicyFile, cReadBuf, dwBytesRead, &dwBytesWritten, NULL))
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, g_szPolicyFile);
			MessageBox(GetFocus(), szMsg, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "VerifyPassword:WriteFile() for \'%s\'failed", g_szPolicyFile);
			LogErrorMessage(szMsg, dwErr);
			CloseHandle(hDecrDataFile);
			DeleteFile(g_szDecrSettingsFile);
			return FALSE;
		}

		if(dwTotalBytesRead >= dwFileSize)
			break;
	}

	CloseHandle(hDecrDataFile);
	CloseHandle(hPolicyFile);

	DeleteFile(g_szDecrSettingsFile);

	return TRUE;
}




// Read the local policy file using the PM API and initialise 'g_LocalPolicy'
BOOL ReadPolicyFile(VOID)
{
	VSPM_STATUS status;
	VSPM_Container AppContainer = NULL, FileEncrContainer = NULL;
	VSPM_Item item = NULL;
	UCHAR *value = NULL;
	TCHAR *pStr = NULL, szMsg[MAX_PATH], szFmt[MAX_PATH];
	TCHAR szHostingMode[MAX_PATH], szTemp[MAX_PATH];

	VSPM_Descriptor fd = VSPM_Open(g_szPolicyFile, &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_OPEN_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, g_szPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "ReadPolicyFile() : Cannot open the Policy File \'%s\'", g_szPolicyFile);
		LogErrorMessage(szMsg, status);
		return FALSE;
	}

	// Reading the File Encryption Container
	AppContainer = VSPM_GetContainerByNameFromDescriptor(fd, "Apps", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open Apps container", status);
		VSPM_Close(fd);
		return FALSE;
	}

	FileEncrContainer = VSPM_GetContainerByName(AppContainer, "FileEncryption", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open File Encryption container", status);
		VSPM_FreeContainer(AppContainer, &status);
		VSPM_Close(fd);
		return FALSE;
	}

	
	item = VSPM_GetItemByName(FileEncrContainer, "EncryptedFileLoc", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.EncryptMethod = (EncryptMethod)atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bEncrMethodForced = atoi(pStr + 1);
			
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	
	item = VSPM_GetItemByName(FileEncrContainer, "EnableSigning", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.bSignatureReqd = atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bSigReqdForced = atoi(pStr + 1);

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	
	item = VSPM_GetItemByName(FileEncrContainer, "EncryptionAlg", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.EncryptionAlg, (const char *)value);
			pStr = strrchr(g_LocalPolicy.EncryptionAlg, ':');
			if(pStr)
			{
				*pStr = '\0';
				g_LocalPolicy.bEncrAlgForced = atoi(pStr + 1);
			}

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}
	

	item = VSPM_GetItemByName(FileEncrContainer, "HashingAlg", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.HashAlg, (const char *)value);
			pStr = strrchr(g_LocalPolicy.HashAlg, ':');
			if(pStr)
			{
				*pStr = '\0';
				g_LocalPolicy.bHashAlgForced = atoi(pStr + 1);
			}

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}
	

	item = VSPM_GetItemByName(FileEncrContainer, "SecureDelete", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.bSecureDelete = atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bSecDelForced = atoi(pStr + 1);

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(FileEncrContainer, "DesktopLockoutTime", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.LockOutPeriod = atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bLockPeriodForced = atoi(pStr + 1);

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(FileEncrContainer, "EnterpriseMode", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.EnterpriseMode = atoi((const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(FileEncrContainer, "PolicyTimeout", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.PolicyTimeout = atoi((const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(FileEncrContainer, "FileFilters", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szFilter, (const char *)value);
			pStr = strrchr(g_LocalPolicy.szFilter, ':');
			if(pStr)
			{
				*pStr = '\0';
				g_LocalPolicy.bFilterForced = atoi(pStr + 1);
			}

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);

		// Initialize the extension, folder and attribute lists
		InitFilters();
	}

	/* PRRemove
	item = VSPM_GetItemByName(FileEncrContainer, "PasswordMethod", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.PasswdMethod = (PasswordMethod)atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bPasswdMethodForced = atoi(pStr + 1);

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}
	*/

	item = VSPM_GetItemByName(FileEncrContainer, "PasswordPromptTimeout", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			g_LocalPolicy.PasswordPromptTimeout = atoi((const char *)value);
			pStr = strrchr((const char *)value, ':');
			if(pStr)
				g_LocalPolicy.bPasswdTimeoutForced = atoi(pStr + 1);

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(FileEncrContainer, "InstallDir", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szInstallDir, (const char *)value);
			pStr = strrchr(g_LocalPolicy.szInstallDir, ':');
			if(pStr)
			{
				*pStr = '\0';
				pStr = strrchr(g_LocalPolicy.szInstallDir, ':');
				if(!pStr)
					lstrcpy(g_LocalPolicy.szInstallDir, (const char *)value);
			}

			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}


	/* PRRemove
	item = VSPM_GetItemByName(FileEncrContainer, "AdminCert", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			TCHAR szTempCert[4096];
			lstrcpy(szTempCert, (const char *)value);
			pStr = strrchr(szTempCert, ':');
			if(pStr)
				*pStr = '\0';

			g_LocalPolicy.dwCertLen = lstrlen(szTempCert);
			memcpy(g_LocalPolicy.AdminCert, szTempCert, g_LocalPolicy.dwCertLen);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}
	*/


	VSPM_FreeContainer(FileEncrContainer, &status);

	// Reading the Global Container
	VSPM_Container GlobalContainer = NULL, GlobalVarContainer = NULL;
	VSPM_Container GlobalModeContainer = NULL;

	GlobalContainer = VSPM_GetContainerByNameFromDescriptor(fd, "Global", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open Global container", status);
		VSPM_Close(fd);
		return TRUE;
	}

	// Get the remote host depending on the mode. Mode could
	// be either enterprise or verisign
	GlobalModeContainer = VSPM_GetContainerByName(GlobalContainer, "Mode", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open Global Mode container", status);
		VSPM_FreeContainer(GlobalContainer, &status);
		VSPM_Close(fd);
		return TRUE;
	}

	item = VSPM_GetItemByName(GlobalModeContainer, "policyValue", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(szHostingMode, (const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	
	GlobalVarContainer = VSPM_GetContainerByName(GlobalContainer, "GlobalVar", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open Global Var container", status);
		VSPM_FreeContainer(GlobalContainer, &status);
		VSPM_Close(fd);
		return TRUE;
	}
	
	// Depending on the hosting mode get either the 'remoteHost'
	// or the 'vsHost'
	if(!lstrcmpi(szHostingMode, "remotehost"))
	{
		item = VSPM_GetItemByName(GlobalVarContainer, "vsHost", &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			value = VSPM_GetValue(item, &status);	
			if(status == VSPM_STATUS_NO_ERROR)
			{
				lstrcpy(szTemp, (const char *)value);
				lstrcpy(g_LocalPolicy.szRemoteHost, "https://");
				lstrcat(g_LocalPolicy.szRemoteHost, szTemp);
				VSPM_FreeString(value, &status);
			}

			VSPM_FreeItem(item, &status);
		}
	}
	else
	{
		item = VSPM_GetItemByName(GlobalVarContainer, "remoteHost", &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			value = VSPM_GetValue(item, &status);	
			if(status == VSPM_STATUS_NO_ERROR)
			{
				lstrcpy(g_LocalPolicy.szRemoteHost, (const char *)value);
				VSPM_FreeString(value, &status);
			}

			VSPM_FreeItem(item, &status);
		}
	}

	item = VSPM_GetItemByName(GlobalVarContainer, "ptaIssuerDN", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szIssuerDN, (const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	VSPM_FreeContainer(GlobalModeContainer, &status);
	VSPM_FreeContainer(GlobalVarContainer, &status);
	VSPM_FreeContainer(GlobalContainer, &status);

	// Reading the PTAv2 Container
	VSPM_Container PTAContainer = NULL;

	PTAContainer = VSPM_GetContainerByName(AppContainer, "PTAv2", &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
		MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
		LogErrorMessage("ReadPolicyFile() : Failed to open PTA container", status);
		VSPM_Close(fd);
		return TRUE;
	}

	item = VSPM_GetItemByName(PTAContainer, "ptaAppLogoUrl", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szAppLogoUrl, (const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	item = VSPM_GetItemByName(PTAContainer, "ptaLoginHelpUrl", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szLoginHelpUrl, (const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}


	item = VSPM_GetItemByName(PTAContainer, "ptaRenewHelpUrl", &status);
	if(status == VSPM_STATUS_NO_ERROR)
	{
		value = VSPM_GetValue(item, &status);	
		if(status == VSPM_STATUS_NO_ERROR)
		{
			lstrcpy(g_LocalPolicy.szRenewalHelpUrl, (const char *)value);
			VSPM_FreeString(value, &status);
		}

		VSPM_FreeItem(item, &status);
	}

	VSPM_FreeContainer(PTAContainer, &status);
	VSPM_FreeContainer(AppContainer, &status);

	VSPM_Close(fd);

	return TRUE;
}


// Read the policy file variable(item) from the Safe install directory or from the policy file passed
// 'lpszContainer' is the innermost container name
// 'lpszItem' is the variable to be read
BOOL ReadPolicyFileVar(LPCTSTR lpszContainer, LPCTSTR lpszItem, UINT *Value, BOOL bIsString, LPCTSTR lpszPolyFilePath)
{
	TCHAR szPolicyFile[MAX_PATH];

	if(lpszPolyFilePath == NULL)
	{
		lstrcpy(szPolicyFile, g_szInstallDir);
		lstrcat(szPolicyFile, "\\");
		lstrcat(szPolicyFile, POLICY_FILE);
	}
	else
		lstrcpy(szPolicyFile, lpszPolyFilePath);

	VSPM_STATUS status;
	VSPM_Container AppContainer = NULL, FileEncrContainer = NULL;
	VSPM_Item item = NULL;
	UCHAR *value = NULL;
	TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH], *pStr = NULL;

	VSPM_Descriptor fd = VSPM_Open(szPolicyFile, &status);
	if(status != VSPM_STATUS_NO_ERROR)
	{
		LoadString(g_hInst, IDS_POLICY_OPEN_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, szPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "ReadPolicyFileVar() : Cannot open the Policy File \'%s\'", szPolicyFile);
		LogErrorMessage(szMsg, status);
		return FALSE;
	}

	if(!lstrcmpi(lpszContainer, "FileEncryption"))
	{
		AppContainer = VSPM_GetContainerByNameFromDescriptor(fd, "Apps", &status);
		if(status != VSPM_STATUS_NO_ERROR)
		{
			LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
			MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
			LogErrorMessage("ReadPolicyFileVar() : Failed to open Apps container", status);
			VSPM_Close(fd);
			return FALSE;
		}

		FileEncrContainer = VSPM_GetContainerByName(AppContainer, "FileEncryption", &status);
		if(status != VSPM_STATUS_NO_ERROR)
		{
			LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
			MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
			LogErrorMessage("ReadPolicyFileVar() : Failed to open File Encryption container", status);
			VSPM_FreeContainer(AppContainer, &status);
			VSPM_Close(fd);
			return FALSE;
		}

		item = VSPM_GetItemByName(FileEncrContainer, lpszItem, &status);
		if(status == VSPM_STATUS_NO_ERROR)
		{
			value = VSPM_GetValue(item, &status);	
			if(status == VSPM_STATUS_NO_ERROR)
			{
				if(bIsString)
				{
					lstrcpy((char *)Value, (const char *)value);
					pStr = strrchr((char *)Value, ':');
					if(pStr)
					{
						*pStr = '\0';

						if(!lstrcmpi(lpszItem, "InstallDir"))
						{
							pStr = strrchr((char *)Value, ':');
							if(!pStr)
								lstrcpy((char *)Value, (const char *)value);
						}
					}
				}
				else
					*Value = atoi((const char *)value);
				
				VSPM_FreeString(value, &status);
			}

			VSPM_FreeItem(item, &status);
		}

		VSPM_FreeContainer(FileEncrContainer, &status);
		VSPM_FreeContainer(AppContainer, &status);
		VSPM_Close(fd);
		return TRUE;
	}
	else
		if(!lstrcmpi(lpszContainer, "GlobalVar") || !lstrcmpi(lpszContainer, "Mode"))
		{
			VSPM_Container GlobalContainer = NULL, GlobalSubContainer = NULL;

			GlobalContainer = VSPM_GetContainerByNameFromDescriptor(fd, "Global", &status);
			if(status != VSPM_STATUS_NO_ERROR)
			{
				LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
				MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
				LogErrorMessage("ReadPolicyFileVar() : Failed to open Global container", status);
				VSPM_Close(fd);
				return FALSE;
			}

			GlobalSubContainer = VSPM_GetContainerByName(GlobalContainer, lpszContainer, &status);
			if(status != VSPM_STATUS_NO_ERROR)
			{
				LoadString(g_hInst, IDS_POLICY_CNT_ERR, szMsg, MAX_PATH);
				MessageBox(GetFocus(), szMsg, "Safe", MB_ICONERROR);
				LogErrorMessage("ReadPolicyFileVar() : Failed to open Global Sub container", status);
				VSPM_FreeContainer(GlobalContainer, &status);
				VSPM_Close(fd);
				return FALSE;
			}
			
			item = VSPM_GetItemByName(GlobalSubContainer, lpszItem, &status);
			if(status == VSPM_STATUS_NO_ERROR)
			{
				value = VSPM_GetValue(item, &status);	
				if(status == VSPM_STATUS_NO_ERROR)
				{
					if(bIsString)
						lstrcpy((char *)Value, (const char *)value);
					else
						*Value = atoi((const char *)value);
					
					VSPM_FreeString(value, &status);
				}

				VSPM_FreeItem(item, &status);
			}

			VSPM_FreeContainer(GlobalSubContainer, &status);
			VSPM_FreeContainer(GlobalContainer, &status);
			VSPM_Close(fd);
			return TRUE;
		}
		
	VSPM_Close(fd);
	return FALSE;
}

// Write the the 'Safe' properties back to the local policy file using the
// PM API.
BOOL WritePolicyFile(VOID)
{
	VSPM_STATUS status;
	TCHAR szUrl[MAX_PATH];

	lstrcpy(szUrl, "file://");
	lstrcat(szUrl, g_szPolicyFile);

	// Overwrite the local policy file. No new policies are generated
	VSPMSP_GeneratePolicy(NULL, g_szPolicyFile, NULL, g_szPolicyFile, &status);

	if(status != VSPM_STATUS_NO_ERROR)
	{
		TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH];
		LoadString(g_hInst, IDS_POLICY_WRITE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, g_szPolicyFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "WritePolicyFile : VSPMSP_GeneratePolicy() for \'%s\' failed.", g_szPolicyFile);
		LogErrorMessage(szMsg, status);
		return FALSE;
	}
	
	return TRUE;
}



// Called from the PM API. This fn. sets the values of the items in the
// File Encryption Container. The values are taken from 'g_LocalPolicy'
// This is used to update the local policy file.
void UpdatePolicies(VSContainer *FileContainer, VSPM_STATUS *status)
{
	VSPM_Container AppContainer = NULL, FileEncrContainer = NULL;
	VSPM_Item item = NULL;
	TCHAR szTemp[16], szValue[MAX_PATH];

	*status = VSPM_STATUS_NO_ERROR;

	AppContainer = VSPMSP_GetContainerByName(FileContainer, "Apps", 
											 strlen("Apps"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	FileEncrContainer = VSPMSP_GetContainerByName(AppContainer, "FileEncryption", 
										strlen("FileEncryption"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "EncryptedFileLoc", 
								strlen("EncryptedFileLoc"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.EncryptMethod, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bEncrMethodForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "EnableSigning", 
								strlen("EnableSigning"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.bSignatureReqd, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bSigReqdForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "EncryptionAlg", 
								strlen("EncryptionAlg"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	lstrcpy(szValue, g_LocalPolicy.EncryptionAlg);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bEncrAlgForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "HashingAlg", 
								strlen("HashingAlg"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	lstrcpy(szValue, g_LocalPolicy.HashAlg);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bHashAlgForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "SecureDelete", 
								strlen("SecureDelete"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.bSecureDelete, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bSecDelForced, szTemp, 10);
	lstrcat(szValue, szTemp);
	
	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "DesktopLockoutTime", 
								strlen("DesktopLockoutTime"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.LockOutPeriod, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bLockPeriodForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	item = VSPMSP_GetItemByName(FileEncrContainer, "FileFilters", 
								strlen("FileFilters"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	TCHAR szStr[2*MAX_PATH];
	szStr[0] = '\0';

	LPCTSTR pItem;
	pItem = g_ExtensionList->GetNextItem(NULL);
	if(pItem)
	{
		while(pItem)
		{
			lstrcat(szStr, pItem);
			pItem = g_ExtensionList->GetNextItem(pItem);
			if(pItem)
				lstrcat(szStr, ",");
			else
				lstrcat(szStr, ";");
		}
	}
	else
		lstrcpy(szStr, "none;");

	pItem = g_FoldersList->GetNextItem(NULL);
	if(pItem)
	{
		while(pItem)
		{
			lstrcat(szStr, pItem);
			pItem = g_FoldersList->GetNextItem(pItem);
			if(pItem)
				lstrcat(szStr, ",");
			else
				lstrcat(szStr, ";");
		}
	}
	else
		lstrcat(szStr, "none;");

	if(g_ExclusionAttr)
	{
		if(g_ExclusionAttr & ATTR_HIDDEN)
			lstrcat(szStr, "H");

		if(g_ExclusionAttr & ATTR_READ_ONLY)
			lstrcat(szStr, "R");

		if(g_ExclusionAttr & ATTR_SYSTEM)
			lstrcat(szStr, "S");

		if(g_ExclusionAttr & ATTR_ARCHIVE)
			lstrcat(szStr, "A");
	}
	else
		lstrcat(szStr, "none");

	itoa(g_LocalPolicy.bFilterForced, szTemp, 10);
	lstrcat(szStr, ":");
	lstrcat(szStr, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szStr, strlen(szStr), status);

	/* PRRemove
	item = VSPMSP_GetItemByName(FileEncrContainer, "PasswordMethod", 
								strlen("PasswordMethod"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.PasswdMethod, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bPasswdMethodForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;
	*/

	item = VSPMSP_GetItemByName(FileEncrContainer, "PasswordPromptTimeout", 
								strlen("PasswordPromptTimeout"), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	itoa(g_LocalPolicy.PasswordPromptTimeout, szTemp, 10);
	lstrcpy(szValue, szTemp);
	lstrcat(szValue, ":");
	itoa(g_LocalPolicy.bPasswdTimeoutForced, szTemp, 10);
	lstrcat(szValue, szTemp);

	VSPMSP_SetValue(item, (unsigned char *)szValue, strlen(szValue), status);
	if(*status != VSPM_STATUS_NO_ERROR)
		return;

	return;
}


BOOL DownloadRemotePolicyFile(LPCSTR lpszPolicyPath, DWORD *pdwError)
{
	HINTERNET hInternet = NULL;
	HINTERNET hConnect  = NULL;
	HINTERNET hRequest	= NULL;
	HANDLE hLocalFile = NULL;
	DWORD dwErr, dwSize, dwType;
	TCHAR *pStr = NULL, szHost[MAX_PATH], szObjectPath[MAX_PATH];
	HKEY hKey = NULL;
	TCHAR szFmt[MAX_PATH], szMsg[MAX_PATH], szUrl[MAX_PATH];
	BOOL bRetVal = FALSE;
	INT nPortNo = -1;
	UINT fRequestFlags = INTERNET_FLAG_RELOAD;

	*pdwError = 0;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE, MAIN_KEY_STRING, 0, KEY_READ, &hKey)
					!= ERROR_SUCCESS)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_REG_OPEN, MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "DownloadRemotePolicyFile() : Could not open registry key \'%s\'", MAIN_KEY_STRING);
		LogErrorMessage(szMsg, dwErr);
		return FALSE;
	}
	else
	{
		dwSize = sizeof(szUrl);
		if(RegQueryValueEx(hKey, "PolicyFileLocation", NULL, &dwType, 
						   (BYTE *)szUrl, &dwSize) != ERROR_SUCCESS)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_REG_READ_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("DownloadRemotePolicyFile() : Could not query registry key \'PolicyFileLocation\'", dwErr);
			return FALSE;
		}
	}

	RegCloseKey(hKey);

	// Format of szUrl - "http://host:port/virtual directory" or file://...
	if(!_strnicmp(szUrl, "file", 4))
	{
		pStr = strchr(szUrl, '/');
		if(pStr)
		{
			if(!*(pStr + 2))
				return FALSE;

			TCHAR szPolicyFile[MAX_PATH];
			lstrcpy(szPolicyFile, pStr + 2);
			SmartAppendBackslash(szPolicyFile);
			lstrcat(szPolicyFile, POLICY_FILE);

			if(!CopyFile(szPolicyFile, lpszPolicyPath, FALSE))
			{
				TCHAR szMsg[MAX_PATH], szFmt[MAX_PATH];

				dwErr = GetLastError();
				LoadString(g_hInst, IDS_COPY_FILE_ERR, szMsg, MAX_PATH);
				wsprintf(szFmt, szMsg, szPolicyFile, lpszPolicyPath);
				MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
				wsprintf(szMsg, "DownloadRemotePolicyFile() : %s", szFmt);
				LogErrorMessage(szMsg, dwErr);
				return FALSE;
			}
		}
		else
			return FALSE;

		return TRUE;
	}

	pStr = strchr(szUrl, '/');
	if(pStr)
	{
		if(!*(pStr + 2))
			return FALSE;

		// Obtain the host name
		lstrcpy(szHost, pStr + 2);

		pStr = strchr(szHost, '/');
		if(pStr)
			*pStr = '\0';


		// Obtain the object path
		lstrcpy(szObjectPath, "/");

		if(pStr && *(pStr + 1) != NULL)
		{
			lstrcat(szObjectPath, pStr + 1);
			lstrcat(szObjectPath, "/");
		}
		
		lstrcat(szObjectPath, POLICY_FILE);

		// Check if host name contains a port
		pStr = strchr(szHost, ':');
		if(pStr)
		{
			*pStr = '\0';
			nPortNo = atoi(pStr + 1);
		}
	}
	else
		return FALSE;

	HCURSOR hOldCur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	hInternet = InternetOpen("File Encryption", 0, NULL, NULL, 0);
	if(!hInternet)
	{
		*pdwError = GetLastError();
		goto CleanUp;
	}

	if(!_strnicmp(szUrl, "https", 5))
	{
		hConnect = InternetConnect(hInternet, szHost, ((nPortNo == -1) ? INTERNET_DEFAULT_HTTPS_PORT : nPortNo), 
								   NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
		fRequestFlags |= INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID | INTERNET_FLAG_IGNORE_CERT_CN_INVALID;
	}
	else
		hConnect = InternetConnect(hInternet, szHost, ((nPortNo == -1) ? INTERNET_DEFAULT_HTTP_PORT : nPortNo), 
							   NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	if(!hConnect)
	{
		*pdwError = GetLastError();
		goto CleanUp;
	}

	hRequest = HttpOpenRequest(hConnect, "GET", szObjectPath, NULL,
				NULL, NULL, fRequestFlags, 0);

	if(!hRequest)
	{
		*pdwError = GetLastError();
		goto CleanUp;
	}
	

	if(!HttpSendRequest(hRequest, NULL, 0, 0, 0))
	{
		*pdwError = GetLastError();
		goto CleanUp;
	}

	hLocalFile = CreateFile(lpszPolicyPath, GENERIC_WRITE, FILE_SHARE_READ,
							NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);

	if(hLocalFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_PATH);
		wsprintf(szFmt, szMsg, lpszPolicyPath);
		MessageBox(GetFocus(), szFmt, "Safe", MB_ICONERROR);
		wsprintf(szMsg, "DownloadRemotePolicyFile : CreateFile() for \'%s\' failed", lpszPolicyPath);
		LogErrorMessage(szMsg, dwErr);
		hLocalFile = NULL;
		goto CleanUp;
	}

	TCHAR szReadBuf[2048];
	DWORD dwBytesRead, dwBytesWritten;
	while(InternetReadFile(hRequest, szReadBuf, sizeof(szReadBuf), &dwBytesRead))
	{
		WriteFile(hLocalFile, szReadBuf, dwBytesRead, &dwBytesWritten, NULL);

		if(dwBytesRead != sizeof(szReadBuf))
			break;
	}

	bRetVal = TRUE;
	
CleanUp:

	if(hLocalFile)
		CloseHandle(hLocalFile);

	if(hRequest)
		InternetCloseHandle(hRequest);

	if(hConnect)
		InternetCloseHandle(hConnect);

	if(hInternet)
		InternetCloseHandle(hInternet);

	if(hOldCur)
		SetCursor(hOldCur);

	return bRetVal;
}



// The filter present is the policy file is of the form(extensions;folders;attributes)
// eg. ".exe,.txt;c:\temp,c:\;HRS. This function will parse the filter
// and initialise the globals 'g_ExtensionList', 'g_FoldersList' and
// 'g_ExclusionAttr'
BOOL InitFilters(VOID)
{
	// Select the extensions from the policy file
	int i = 0, j = 0;
	TCHAR szFilter[2*MAX_PATH], szValue[MAX_PATH], *pStr = NULL;

	lstrcpy(szFilter, g_LocalPolicy.szFilter);
	pStr = strchr(szFilter, ';');
	if(!pStr)
		return FALSE;

	*pStr = '\0';

	if(lstrcmpi(szFilter, "none") != 0)
	{
		i = 0;
		while(szFilter[i])
		{
			for(j = 0; szFilter[i] != ',' && szFilter[i] != '\0'; i++, j++)
				szValue[j] = szFilter[i];

			szValue[j] = '\0';

			g_ExtensionList->AddToList(_strlwr(szValue));

			if(szFilter[i] == ',')
				i++;
		}	
	}

	pStr = strchr(g_LocalPolicy.szFilter, ';');
	lstrcpy(szFilter, pStr + 1);
	pStr = strchr(szFilter, ';');
	if(!pStr)
		return FALSE;

	*pStr = '\0';

	if(lstrcmpi(szFilter, "none") != 0)
	{
		i = 0;
		while(szFilter[i])
		{
			for(j = 0; szFilter[i] != ',' && szFilter[i] != '\0'; i++, j++)
				szValue[j] = szFilter[i];

			szValue[j] = '\0';

			g_FoldersList->AddToList(_strlwr(szValue));

			if(szFilter[i] == ',')
				i++;
		}	
	}

	pStr = strchr(g_LocalPolicy.szFilter, ';');
	pStr = strchr(pStr + 1, ';');
	lstrcpy(szFilter, pStr + 1);

	// See if any exclusion attributes are specified
	if(lstrcmpi(szFilter, "none") != 0)
	{
		i = 0;
		while(szFilter[i] != '\0')
		{
			switch(szFilter[i])
			{
				case 'H':
				{
					g_ExclusionAttr |= ATTR_HIDDEN;
					break;
				}

				case 'R':
				{
					g_ExclusionAttr |= ATTR_READ_ONLY;
					break;
				}

				case 'S':
				{
					g_ExclusionAttr |= ATTR_SYSTEM;
					break;
				}

				case 'A':
				{
					g_ExclusionAttr |= ATTR_ARCHIVE;
					break;
				}
			}

			i++;
		}
	}

	return TRUE;
}



BOOL GetFETProfileInfo(BOOL *bIsProfileInfoPresent, BOOL *bProfileType, LPTSTR lpszAppContext, DWORD dwAppContextSize,
					   LPTSTR lpszClientInfo, DWORD dwClientInfoSize, LPTSTR lpszClientInfoSig, DWORD dwClientInfoSigSize)
{
	HKEY hKey = NULL;
	DWORD dwErr = 0, dwSize = 0, dwType = 0;
	BOOL bRetVal = FALSE;

	*bIsProfileInfoPresent = FALSE;
	*bProfileType = NON_ROAMING;
	
	if(RegOpenKeyEx(HKEY_CURRENT_USER, MAIN_KEY_STRING, 0, KEY_READ, &hKey)
					== ERROR_SUCCESS)
	{
		dwSize = dwAppContextSize;
		if(RegQueryValueEx(hKey, FET_APP_CONTEXT, NULL, &dwType, 
						   (BYTE *)lpszAppContext, &dwSize) == ERROR_SUCCESS)
		{
			*bIsProfileInfoPresent = TRUE;

			// Check if clientinfo and clientinfosig are present if both
			// are present we will initialize in roaming mode
			dwSize = dwClientInfoSize;
			if(RegQueryValueEx(hKey, CLIENT_INFO, NULL, &dwType, 
					   (BYTE *)lpszClientInfo, &dwSize) == ERROR_SUCCESS)
			{
				dwSize = dwClientInfoSigSize;
				if(RegQueryValueEx(hKey, CLIENT_INFO_SIG, NULL, &dwType, 
					   (BYTE *)lpszClientInfoSig, &dwSize) == ERROR_SUCCESS)
					*bProfileType = ROAMING;
			}

			bRetVal = TRUE;
		}

		RegCloseKey(hKey);
	}

	return bRetVal;
}