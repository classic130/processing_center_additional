// vsscsetup.cpp : Defines the entry point for the application.
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
#include "stdafx.h"

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

	CHAR	szRegSvr32Path[256] ;
	PCHAR	szVersion = NULL ;

	sprintf(szRegSvr32Path, "%s\\%s", szShortSysDir, "regsvr32") ;

	CHAR	szDllFileName[2048] ;

	// Assume the controls are already present in the required directory
	// Default value is C:\Program Files\VeriSign\PTA\SecureExpress

	// Register vssgnatb.dll
	strcpy(szDllFileName, "ptav3.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Setup Failed: Unable to register ptav3.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating Desktop Update", GetLastError());
		MessageBox(
				NULL,
				szErrorString,
				"Setup Error",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	// Register VSImport.dll
	strcpy(szDllFileName, "vssc.dll") ;
	err = _spawnl(_P_WAIT, szRegSvr32Path, szRegSvr32Path, "/s", szDllFileName, NULL) ;
	if ( err != 0 )
	{
		CHAR	szErrorString[2048] ;
		sprintf(szErrorString, "Setup Failed: Unable to register vssc.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating Desktop Update", GetLastError());
		MessageBox(
				NULL,
				szErrorString,
				"Setup Error",
				MB_OK | MB_SYSTEMMODAL) ;
		return 1 ;
	}

	MessageBox(
			NULL,
			"Setup Succeeded",
			"Setup",
			 MB_OK | MB_SYSTEMMODAL) ;


	return 0;

}



