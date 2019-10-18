// npsesetup.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "windows.h"
#include "winbase.h"
#include "process.h"
#include "npsesetup.h"
#include "tchar.h"
#include "stdio.h"
#include "stdlib.h"
#include "winerror.h"

int		g_nNSVersion = 0;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	char szSysDir[MAX_PATH];
	char szNSPluginDir[MAX_PATH];
	char szShortSysDir[MAX_PATH];
	char szShortNSPluginDir[MAX_PATH];
	char szCmd[2*MAX_PATH + 16];
	int retVal;
	DWORD err;
	int nSanity;

	int nRet = 0;

	if (lpCmdLine == NULL)
	{
		g_nNSVersion = 4;
//		::MessageBox(NULL, "null 4", "plugin", MB_OK);
	}
	else
	{
		if (strlen(lpCmdLine))
		{
			if (!strcmp(lpCmdLine, "NS6"))
			{
//				::MessageBox(NULL, "6", "plugin", MB_OK);
				g_nNSVersion = 6;
			}
		}
//		else
//		{
//			::MessageBox(NULL, "len = 0", "plugin", MB_OK);
//		}
	}

//	::MessageBox(NULL, "inside vspsetupkm", "vsnpsetupkm", MB_OK);
//	exit (1);
	
	//Check the sanity of the system
	//nSanity = CheckSanity();
	nSanity = 1;
	if(!nSanity)
	{
		MessageBox(NULL,"Setup Failed: You need to upgrade your system before you can install the plugin.\n Please contact your administrator", "Setup Error", MB_OK | MB_SYSTEMMODAL);
	}
	else
	{
		if(nSanity == -1)
		{
			MessageBox(NULL, "Setup Failed: Error occured while checking the sanity of the system.\n Contact your administrator to reslove this problem", "Setup Error", MB_OK | MB_SYSTEMMODAL);
		}
		else
		{
			//Get the sys directory
			if(!GetSystemDirectory(szSysDir,MAX_PATH))
			{
				retVal = -1;
			}
			else
			{

				err = GetShortPathName(szSysDir, szShortSysDir, MAX_PATH);

				if(err == 0 || err > MAX_PATH)
				{
					retVal = -1;
				}
				else
				{

					//Get the Netscape Plugin path
					if(!_GetNSPluginPath(szNSPluginDir))
					{
						retVal = -1;
					}
					else
					{
						err = GetShortPathName(szNSPluginDir, szShortNSPluginDir, MAX_PATH);
					
						if(err == 0 || err > MAX_PATH)
						{
							retVal = -1;
						}
						else
						{
							TCHAR tcharDestFile[MAX_PATH];


							//Create the command to register VSPref.dll
							strcpy(szCmd,szShortSysDir);
							strcat(szCmd, "\\regsvr32");

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\ptav3.dll");


							//Invoke CopyFile
							if(!CopyFile(_T("ptav3.dll"), tcharDestFile,FALSE))
							{
								MessageBox(NULL,_T("Setup Failed: 0x00001 - There was a conflict while copying one of the files"), _T("Setup Error"),MB_OK | MB_SYSTEMMODAL);
								return -1;
							}

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\vssc.dll");

							if(!CopyFile(_T("vssc.dll"), tcharDestFile,FALSE))
							{
								MessageBox(NULL,_T("Setup Failed: 0x00002 - There was a conflict while copying one of the files"), _T("Setup Error"),MB_OK | MB_SYSTEMMODAL);
								return -1;
							}

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\npvssc.dll");

							if(!CopyFile(_T("npvssc.dll"), tcharDestFile,FALSE))
							{
								MessageBox(NULL,_T("Setup Failed: 0x00003 - There was a conflict while copying one of the files"), _T("Setup Error"),MB_OK | MB_SYSTEMMODAL);
								return -1;
							}

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\NPVSSC.class");

							if(!CopyFile(_T("NPVSSC.class"), tcharDestFile,FALSE))
							{
								MessageBox(NULL,_T("Setup Failed: 0x00004 - There was a conflict while copying one of the files"), _T("Setup Error"),MB_OK | MB_SYSTEMMODAL);
								return -1;
							}

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\vscspsign");

							if(!CopyFile(_T("vscspsign"), tcharDestFile,FALSE))
							{
								MessageBox(NULL,_T("Setup Failed: 0x00005 - There was a conflict while copying one of the files"), _T("Setup Error"),MB_OK | MB_SYSTEMMODAL);
								return -1;
							}


							//Copy the following files to the plugin directory
/*
							_tcscpy(szCopyCmd, "copy ");
							_tcscat(szCopyCmd, "ptav3.dll ");
							_tcscat(szCopyCmd, szShortNSPluginDir);
							nRet = system(szCopyCmd);

							_tcscpy(szCopyCmd, "copy ");
							_tcscat(szCopyCmd, "vssc.dll ");
							_tcscat(szCopyCmd, szShortNSPluginDir);
							nRet = system(szCopyCmd);

							_tcscpy(szCopyCmd, "copy ");
							_tcscat(szCopyCmd, "npvssc.dll ");
							_tcscat(szCopyCmd, szShortNSPluginDir);
							nRet = system(szCopyCmd);

							_tcscpy(szCopyCmd, "copy ");
							_tcscat(szCopyCmd, "NPVSSC.class ");
							_tcscat(szCopyCmd, szShortNSPluginDir);
							nRet = system(szCopyCmd);

							_tcscpy(szCopyCmd, "copy ");
							_tcscat(szCopyCmd, "vscspsign ");
							_tcscat(szCopyCmd, szShortNSPluginDir);
							nRet = system(szCopyCmd);
*/
											
							//Invoke regsvr32

							
							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\ptav3.dll");
							err = _spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFile, NULL);
							if(err != 0)
							{
								CHAR	szErrorString[2048] ;
								sprintf(szErrorString, "Setup Failed: Unable to register ptav3.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating Desktop Update", GetLastError());
								MessageBox(
										NULL,
										szErrorString,
										"Setup Error",
										MB_OK | MB_SYSTEMMODAL) ;
								return -1 ;
							}
							

							// Start - Ajay
							TCHAR tcharDestFileVSSC[MAX_PATH];
							_tcscpy(tcharDestFileVSSC, szShortNSPluginDir);
							_tcscat(tcharDestFileVSSC, "\\vssc.dll");
							err = _spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFileVSSC, NULL);
							if(err != 0)
							{
								CHAR	szErrorString[2048] ;
								sprintf(szErrorString, "Setup Failed: Unable to register vssc.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating Desktop Update", GetLastError());
								MessageBox(
										NULL,
										szErrorString,
										"Setup Error",
										MB_OK | MB_SYSTEMMODAL) ;
								return -1 ;
							}
							// End - Ajay


						}
					}
				}

			}
		}
	}

	MessageBox(
		NULL,
		"Setup Succeeded",
		"Setup",
		 MB_OK | MB_SYSTEMMODAL) ;
	return 0;
}


DWORD _GetNSPluginPath(TCHAR* szNSPluginDir)
{
	DWORD retVal = 1;
	TCHAR* szNavKey = _T("SOFTWARE\\Netscape\\Netscape Navigator");
	TCHAR* szNav6Key = _T("SOFTWARE\\Netscape\\Netscape 6");
	HKEY hkNavKey, hkMainKey;
	TCHAR* szCurVer;
	DWORD dwCurVerSize;
	LPCTSTR szVerKeyName = _T("CurrentVersion");
	LPCTSTR szPluginsKey = _T("Plugins Directory");
	LPCTSTR szInstallDirectory = _T("Install Directory");
	DWORD dwType;
	LPCTSTR szComponents = _T("Components");
	
	if (6 != g_nNSVersion)
	{
		//Open the registry key HKEY_LOCAL_MACHINE\Software\Netscape\Netscape Navigator
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,szNavKey,0,KEY_READ, &hkNavKey))
		{
			retVal = 0;
		}
		else
		{
			//Get the current version field
			if(RegQueryValueEx(hkNavKey, szVerKeyName, 0, &dwType, NULL, &dwCurVerSize))
			{
				retVal = 0;
			}
			else
			{
				if((szCurVer = (TCHAR*)malloc(dwCurVerSize + _tcslen(_T("\\Main")))) == NULL)
				{
					retVal = 0;
				}
				else
				{

					if(RegQueryValueEx(hkNavKey, szVerKeyName, 0, &dwType, (PBYTE)szCurVer, &dwCurVerSize))
					{
						retVal = 0;
					}
					else
					{
						szCurVer[dwCurVerSize] = '\0';
						_tcscat(szCurVer, _T("\\Main"));

						//Open the Main key under the current version key
						if(RegOpenKeyEx(hkNavKey,szCurVer,0,KEY_READ, &hkMainKey))
						{
							retVal = 0;
						}
						else
						{
							//Read the Plugins Directory field
							if(RegQueryValueEx(hkMainKey, szPluginsKey, 0, &dwType, NULL, &retVal))
							{
								retVal = 0;
							}
							else
							{
								if(szNSPluginDir)
								{
									if(RegQueryValueEx(hkMainKey, szPluginsKey, 0, &dwType, (PBYTE)szNSPluginDir, &retVal))
									{
										retVal = 0;
									}
								}
							}
							
							RegCloseKey(hkMainKey);
						}
					}
					free(szCurVer);
				}

			}

				RegCloseKey(hkNavKey);

		}
	}
	else
	{
		//Open the registry key HKEY_LOCAL_MACHINE\Software\Netscape\Netscape Navigator
		if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,szNav6Key,0,KEY_READ, &hkNavKey))
		{
			retVal = 0;
		}
		else
		{
			//Get the current version field
			if(RegQueryValueEx(hkNavKey, szVerKeyName, 0, &dwType, NULL, &dwCurVerSize))
			{
				retVal = 0;
			}
			else
			{
				if((szCurVer = (TCHAR*)malloc(dwCurVerSize + _tcslen(_T("\\Main")))) == NULL)
				{
					retVal = 0;
				}
				else
				{

					if(RegQueryValueEx(hkNavKey, szVerKeyName, 0, &dwType, (PBYTE)szCurVer, &dwCurVerSize))
					{
						retVal = 0;
					}
					else
					{
						szCurVer[dwCurVerSize] = '\0';
						_tcscat(szCurVer, _T("\\Main"));

						//Open the Main key under the current version key
						if(RegOpenKeyEx(hkNavKey,szCurVer,0,KEY_READ, &hkMainKey))
						{
							retVal = 0;
						}
						else
						{
							//Read the Plugins Directory field
							if(RegQueryValueEx(hkMainKey, szInstallDirectory, 0, &dwType, NULL, &retVal))
							{
								retVal = 0;
							}
							else
							{
								if(szNSPluginDir)
								{
									if(RegQueryValueEx(hkMainKey, szInstallDirectory, 0, &dwType, (PBYTE)szNSPluginDir, &retVal))
									{
										retVal = 0;
									}
								}
							}
							
							RegCloseKey(hkMainKey);
							strcat (szNSPluginDir, szComponents);
						}
					}
					free(szCurVer);
				}

			}

				RegCloseKey(hkNavKey);

		}
	}
	return retVal;
}

