// vsscnpsetup.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "windows.h"
#include "winbase.h"
#include "process.h"
#include "vsscnpsetup.h"
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
 	// TODO: Place code here.

char szSysDir[MAX_PATH];
	char szNSPluginDir[MAX_PATH];
	char szShortSysDir[MAX_PATH];
	char szShortNSPluginDir[MAX_PATH];
	char szCmd[2*MAX_PATH + 16];
	int retVal;
	DWORD err;
	int nSanity;
	CHAR szErrorString[2048];

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
		MessageBox(NULL,"You need to upgrade your system before you can install the plugin.\n Please contact your administrator", "Setup Error", MB_OK);
	}
	else
	{
		if(nSanity == -1)
		{
			MessageBox(NULL, "Error occured while checking the sanity of the system.\n Contact your administrator to reslove this problem", "Setup Error", MB_OK);
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
											
							//Invoke regsvr32
							err = _spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFile, NULL);
							if(err != 0)
							{
								sprintf(szErrorString, "Unable to register ptav3.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating SmartUpdate", GetLastError()) ;
								MessageBox(
										NULL,
										szErrorString,
										"Error : NPVSSC Plugin Download",
										MB_OK | MB_SYSTEMMODAL) ;
								return 1 ;
							}

							// Start - Ajay
							TCHAR tcharDestFileVSSC[MAX_PATH];
							_tcscpy(tcharDestFileVSSC, szShortNSPluginDir);
							_tcscat(tcharDestFileVSSC, "\\vssc.dll");
							err = _spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFileVSSC, NULL);
							if(err != 0)
							{
								sprintf(szErrorString, "Unable to register vssc.dll.\nPlease contact your Administrator. \nWindows Error Code is : 0x%x\nTerminating SmartUpdate", GetLastError()) ;
								MessageBox(
										NULL,
										szErrorString,
										"Error : NPVSSC Plugin Download",
										MB_OK | MB_SYSTEMMODAL) ;
								return 1 ;
							}
							// End - Ajay

							//Create the command to register VSExports.dll
							//strcpy(szCmd,szShortSysDir);
							//strcat(szCmd, "\\regsvr32");

							//_tcscpy(tcharDestFile, szShortNSPluginDir);
							//_tcscat(tcharDestFile, "\\VSExports.dll");
											
							//Invoke regsvr32
							//_spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFile, NULL);

//#ifdef KM
							//strcpy(szCmd,szShortSysDir);
							//strcat(szCmd, "\\regsvr32");

							//_tcscpy(tcharDestFile, szShortNSPluginDir);
							//_tcscat(tcharDestFile, "\\VSImport.dll");
											
							//Invoke regsvr32
							//_spawnl(_P_WAIT, szCmd, "regsvr32", "/s", tcharDestFile, NULL);
//#endif

						}
					}
				}

			}
		}
	}
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


