// gsesetupw.cpp : Defines the entry point for the application.
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

	CHAR	szExec32Path[256], szRegSvr32Path[256] ;
	PCHAR	szVersion = NULL ;

	sprintf(szExec32Path, "%s\\%s", szShortSysDir, "ExSec32.dll") ;

	sprintf(szRegSvr32Path, "%s\\%s", szShortSysDir, "regsvr32") ;

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




	return 0;
}



