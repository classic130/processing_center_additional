// oesetupw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winreg.h>
#include <winbase.h>
#include <string.h>
#include <tchar.h>
#include <process.h>
#include <winver.h>
#include <wtypes.h>
#include <oleauto.h>

#define		MAX_REGNAME_SIZE   1024

PCHAR	GetFileVersion(PCHAR szFileName) ;
BOOL	OutLook2KPresent() ;
BOOL	GetRegEntry(HKEY hkResult, DWORD dwKeyType, char *szRegValueName, char *szRegValue) ;
BSTR	_MultiToWideString(LPSTR szInputString) ;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	char szSysDir[MAX_PATH], szShortSysDir[MAX_PATH] ;
	int err ;

	//Get the sys directory
	if(!GetSystemDirectory(szSysDir,MAX_PATH))
	{
		return(1) ;
	}

	err = GetShortPathName(szSysDir, szShortSysDir, MAX_PATH);
	if(err == 0 || err > MAX_PATH)
	{
		return(1) ;
	}

	CHAR	szDest[1024] ;
	CHAR	szExec32Path[256], szRegSvr32Path[256] ;
	PCHAR	szVersion = NULL ;

	sprintf(szExec32Path, "%s\\%s", szShortSysDir, "ExSec32.dll") ;

	sprintf(szRegSvr32Path, "%s\\%s", szShortSysDir, "regsvr32") ;

	WIN32_FIND_DATA		FindFileData ;
	HANDLE				hFindFile ;

	if (!OutLook2KPresent())
	{
		if ( (hFindFile = FindFirstFile(szExec32Path, &FindFileData)) == INVALID_HANDLE_VALUE )
		{
			// exec32.dll is NOT present. 
			// So copy ExSec32.dll to the systems folder
			sprintf(szDest, "%s\\%s", szShortSysDir, "ExSec32.dll") ;
			if ( !CopyFile("ExSec32.dll", szDest, FALSE) )
			{
				CHAR	szErrorString[2048] ;
				sprintf(szErrorString, "Unable to copy %s to the windows system folder.\nPlease close Outlook application and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", "ExSec32.dll", GetLastError()) ;
				MessageBox(
						NULL,
						szErrorString,
						"Error : Go Secure! for Microsoft Exchange",
						MB_OK | MB_SYSTEMMODAL) ;
				return 1 ;
			}
		}
		else
		{
			FindClose(hFindFile) ;

			szVersion = GetFileVersion(szExec32Path) ;

			int compstat ;	
			if ( (compstat = strcmp(szVersion, "5.5.2232.11")) < (int)0 )
			{
				// ExSec32.dll is present but is of lesser version. 
				// So copy ExSec32.dll to the systems folder
				sprintf(szDest, "%s\\%s", szShortSysDir, "ExSec32.dll") ;
				if ( !CopyFile("ExSec32.dll", szDest, FALSE) )
				{
					CHAR	szErrorString[2048] ;
					sprintf(szErrorString, "Unable to copy %s to the windows system folder.\nPlease close Outlook application and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", "ExSec32.dll", GetLastError()) ;
					MessageBox(
							NULL,
							szErrorString,
							"Error : Go Secure! for Microsoft Exchange",
							MB_OK | MB_SYSTEMMODAL) ;
					return 1 ;
				}
			}
		}
	}

/*
	// Irrespective of whether VSGSEExt.dll is present or not, copy/overwrite it in the
	// systems folder
	sprintf(szDest, "%s\\%s", szShortSysDir, "VSGSEExt.dll") ;
	if ( !CopyFile("VSGSEExt.dll", szDest, FALSE) )
	{
			CHAR	szErrorString[2048] ;
			sprintf(szErrorString, "Unable to copy %s to the windows system folder.\nPlease close the Outlook application and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", "VSGSEExt.dll", GetLastError()) ;
			MessageBox(
					NULL,
					szErrorString,
					"Error : Go Secure! for Microsoft Exchange",
					MB_OK | MB_SYSTEMMODAL) ;
			return 1 ;
	}
*/
	CHAR	szDllFileName[2048] ;

	// Assume the controls are already present in the required directory
	// Default value is C:\Program Files\VeriSign\OnSite\ExchangeSoln

	// Register vssgnatb.dll
	strcpy(szDllFileName, "vssgnatb.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Unable to copy %s to the destination folder.\nPlease close the Internet Explorer and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", szDllFileName, GetLastError()) ;
		MessageBox(
				NULL,
				szErrorString,
				"Error : Go Secure! for Microsoft Exchange",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	// Register VSImport.dll
	strcpy(szDllFileName, "VSImport.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Unable to copy %s to the destination folder.\nPlease close the Internet Explorer and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", szDllFileName, GetLastError()) ;
		MessageBox(
				NULL,
				szErrorString,
				"Error : Go Secure! for Microsoft Exchange",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	// Register VSCnfChk.dll
	strcpy(szDllFileName, "VSCnfChk.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Unable to copy %s to the destination folder.\nPlease close the Internet Explorer and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", szDllFileName, GetLastError()) ;
		MessageBox(
				NULL,
				szErrorString,
				"Error : Go Secure! for Microsoft Exchange",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	// Register VSGSE.dll
	strcpy(szDllFileName, "VSGSE.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Unable to copy %s to the destination folder.\nPlease close the Internet Explorer and run the setup program again.\nWindows Error Code is : 0x%x\nTerminating Desktop Update", szDllFileName, GetLastError()) ;
		MessageBox(
				NULL,
				szErrorString,
				"Error : Go Secure! for Microsoft Exchange",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	//make the registry setting to register the exchange extensions

#define MAXLEN 256

	CHAR szKey[MAXLEN];
	CHAR szKeyValue[MAXLEN];
	
	HKEY hRegKey = NULL;

    DWORD dwType=REG_DWORD, dwDisposition = 0 ;
	ULONG lSize = sizeof(DWORD);

	_tcscpy(szKey, _T("Software\\Microsoft\\Exchange\\Client\\Extensions"));

	err=RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey,0,KEY_ALL_ACCESS, &hRegKey);
	
	if(err!= ERROR_SUCCESS) 
		return err;


	strcpy(szKeyValue,"4.0;");
	strcat(szKeyValue,"C:\\Program Files\\VeriSign\\OnSite\\GSE");
	strcat(szKeyValue,"\\VSGSEEXT.dll");
	strcat(szKeyValue,";1;01111111111110;1100000;");


	//_tcscpy(szKeyValue, _T("4.0;D:\\WINNT40s\\SYSTEM32\\VSCRLCHECK.dll;1;01111111111110;1100000;"));

	err=RegSetValueEx(hRegKey, _T("GSE Extensions"), 0, REG_SZ, 
												(CONST BYTE *)&szKeyValue, strlen(szKeyValue));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	RegCloseKey(hRegKey);



#if 0
	OSVERSIONINFO	osvi ;

	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO) ;
	GetVersionEx(&osvi) ;

	// Check if it's Win98
	if ( (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		 ( (osvi.dwMajorVersion > 4) || ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0)) ) )
	{
		// Install ADSI 2.5 Patches for Win98
		err = _spawnl(_P_WAIT, "ads25W98.exe", "ads25W98.exe", NULL) ;
	}
	// Check if it's Win95
	else if ( (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS) &&
		 ( (osvi.dwMajorVersion > 4) || ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion == 0)) ) )
	{
		// Install ADSI 2.5 Patches for Win95
		err = _spawnl(_P_WAIT, "ads25W95.exe", "ads25W95.exe", NULL) ;
	}
	else if ( (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
		 ( (osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion == 0) ) )
	{
		// Install ADSI 2.5 Patches for WinNT4.0
		err = _spawnl(_P_WAIT, "ads25WNT.exe", "ads25WNT.exe", NULL) ;
	}
#endif

#if 0
	sprintf(szRSAENHPath, "%s\\%s", szShortSysDir, "rsaenh.dll") ;
	if ( (hFindFile = FindFirstFile(szRSAENHPath, &FindFileData)) == INVALID_HANDLE_VALUE )
	{
		// rsaenh.dll is NOT present. 
		// So install the Internet Explorer 4.0 Domestic Security Patch
		_spawnl(_P_WAIT, "oufinal.exe", "oufinal.exe", NULL) ;

		// Now install the OutLook 98 QFE
		_spawnl(_P_WAIT, "ol98qfe.exe", "ol98qfe.exe", NULL) ;
	}
	else
	{
		FindClose(hFindFile) ;

		szVersion = GetFileVersion(szRSAENHPath) ;

		int compstat ;	
		if ( (compstat = strcmp(szVersion, "5.0.1620.82")) < (int)0 )
		{
			// rsaenh.dll is present but is of lesser version. 
			// So install the Internet Explorer 4.0 Domestic Security Patch
			_spawnl(_P_WAIT, "oufinal.exe", "oufinal.exe", NULL) ;

			// Now install the OutLook 98 QFE
			_spawnl(_P_WAIT, "ol98qfe.exe", "ol98qfe.exe", NULL) ;
		}
	}
#endif
	if (!OutLook2KPresent())
	{
		// Now install the OutLook 98 QFE
		_spawnl(_P_WAIT, "ol98qfe.exe", "ol98qfe.exe", NULL) ;
	}
	
	MessageBox(
				NULL,
				"Please close all windows programs and reboot your system before enrolling\nfor a Digital ID.",
				"Go Secure! for Microsoft Exchange",
				MB_OK | MB_SYSTEMMODAL) ;

	return(0) ;
}

PCHAR	GetFileVersion(PCHAR szFileName)
{
	PCHAR	szVersion = NULL ;

	//Get the version of the file
	DWORD		dwHandle;
	DWORD		dwFileVerInfoSize;
	dwFileVerInfoSize = GetFileVersionInfoSize(szFileName, &dwHandle);

	PBYTE		verInfo ;
	verInfo = (BYTE*)malloc(dwFileVerInfoSize);

	//Return the version of the file
	if(!GetFileVersionInfo(szFileName, dwHandle, dwFileVerInfoSize, (LPVOID)verInfo))
	{
		szVersion = NULL;
	}
	else
	{
		DWORD dwFileVerMS, dwFileVerLS;
		UINT nHiWord, nLowWord;
		char szMSHiWord[16], szMSLoWord[16], szLSHiWord[16], szLSLoWord[16];
		VS_FIXEDFILEINFO*	pFixedFileInfo;
		UINT nFixedFileInfoSize;

		if(!VerQueryValue(verInfo, "\\", (LPVOID*)&pFixedFileInfo, &nFixedFileInfoSize))
		{
			szVersion = NULL;
		}
		else
		{
			dwFileVerMS = pFixedFileInfo->dwFileVersionMS;
			dwFileVerLS = pFixedFileInfo->dwFileVersionLS;

			//Generate the string value for the version
			nHiWord = (dwFileVerMS & 0xFFFF0000) >> 16;
			nLowWord = (dwFileVerMS & 0x0000FFFF);

			itoa(nHiWord, szMSHiWord, 10);
			itoa(nLowWord, szMSLoWord, 10);

			nHiWord = (dwFileVerLS & 0xFFFF0000) >> 16;
			nLowWord = (dwFileVerLS & 0x0000FFFF);

			itoa(nHiWord, szLSHiWord, 10);
			itoa(nLowWord, szLSLoWord, 10);

			if((szVersion = (LPSTR)malloc(strlen(szMSHiWord) + strlen(szMSLoWord) + strlen(szLSHiWord) + strlen(szLSLoWord) + 4)) == NULL)
			{
				szVersion = NULL;
			}
			else
			{
				strcpy(szVersion, szMSHiWord);
				strcat(szVersion, ".");
				strcat(szVersion, szMSLoWord);
				strcat(szVersion, ".");
				strcat(szVersion, szLSHiWord);
				strcat(szVersion, ".");
				strcat(szVersion, szLSLoWord);
			}
		}
	}

	return (szVersion) ;
}

BOOL	OutLook2KPresent()
{
	LONG		errorCode ;
	HKEY		hkResult ;
	DWORD		dwKeyType ;

	// Open the SOFTWARE\Microsoft\Shared Tools\MSinfo\Categories\Applications\OutLook Registry Key
	if ( (errorCode = RegOpenKeyEx(
				HKEY_LOCAL_MACHINE,
				(LPCTSTR) _T("SOFTWARE\\Microsoft\\Shared Tools\\MSinfo\\Categories\\Applications\\OutLook"),
				0,
				KEY_READ,
				&hkResult)) != ERROR_SUCCESS )
	{
		return FALSE ;
	}

	CHAR	szOutLookKey[1024] ;

	dwKeyType = REG_SZ ;
	if ( !GetRegEntry(hkResult, dwKeyType, "", szOutLookKey) )
		return FALSE ;
	else
	{
		if ( strcmp(szOutLookKey, "Microsoft Outlook 2000") == 0 )
			return TRUE ;
		else
			return FALSE ;
	}
}


BOOL	GetRegEntry(HKEY hkResult, DWORD dwKeyType, char *szRegValueName, char *szRegValue)
{
	DWORD		dwKeyDataSize = 0, errorCode = 0 ;
	USHORT		szwRegValue[MAX_REGNAME_SIZE] ;
	CHAR		szretRegValue[1024] ;
	int			i  ;
	BSTR		szwRegValueName = _MultiToWideString(szRegValueName) ;

	// Get the string for "szRegValueName" from the opened Registry Key
	dwKeyDataSize = MAX_REGNAME_SIZE ;
	if ( (errorCode = RegQueryValueExW(
				hkResult,
				szwRegValueName,
				0,
				(LPDWORD)&dwKeyType,
				(LPBYTE)szwRegValue,
				(LPDWORD)&dwKeyDataSize)) != ERROR_SUCCESS )
	{
		return (FALSE) ;
	}

	for ( i = 0 ; i < (int)wcslen(szwRegValue) ; i++ )
	{
		szretRegValue[i] = (CHAR)szwRegValue[i] ;
	}
	szretRegValue[i] = '\0' ;

	strcpy(szRegValue, szretRegValue) ;

	if ( szwRegValueName )
		SysFreeString(szwRegValueName) ;

	return TRUE ;
}

BSTR _MultiToWideString(LPSTR szInputString)
{
	BSTR	szwcOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szInputString == NULL)
		return NULL ;

	// Obtain size of the wide char UNICODE string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								NULL,
								0) ;

	// Allocate memory for the BSTR (UNICODE string).
	szwcOutputString = SysAllocStringLen(NULL, dwSize) ;

	// Copy from (and convert) Multi Byte string to Wide Char string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								szwcOutputString,
								dwSize) ;
	if (!dwSize)
	{
		return(NULL) ;
	}

	return szwcOutputString ;
}
