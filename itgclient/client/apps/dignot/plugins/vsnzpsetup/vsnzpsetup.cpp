// vsnzpsetup.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "windows.h"
#include "winbase.h"
#include "process.h"
#include "vsnzpsetup.h"
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

	if (lpCmdLine == NULL)
	{
		g_nNSVersion = 4;
	}
	else
	{
		if (strlen(lpCmdLine))
		{
			if (!strcmp(lpCmdLine, "NS6"))
			{
				g_nNSVersion = 6;
			}
		}
	}

	
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


							//Create the command to register vsdnotz.dll
							strcpy(szCmd,szShortSysDir);
							strcat(szCmd, "\\regsvr32");

							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\vsdnotz.dll");

																
							//Invoke regsvr32
							_spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFile, NULL);

#ifdef PTA
							// Also register the Pta dll
							_tcscpy(tcharDestFile, szShortNSPluginDir);
							_tcscat(tcharDestFile, "\\ptav3.dll");

							//Invoke regsvr32
							_spawnl(_P_WAIT, szCmd, "regsvr32","/s", tcharDestFile, NULL);
#endif

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



int CheckSanity()
{
	TCHAR szSysDir[MAX_PATH];
	TCHAR szShortSysDir[MAX_PATH];
	BOOL retVal = 1;
	DWORD err;
	
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
			TCHAR szFileName[MAX_PATH];
			LPSTR szVer;

			_tcscpy(szFileName,szShortSysDir);
			_tcscat(szFileName, _T("\\crypt32.dll"));

			//Check the version of the crypt32.dll
			if((szVer = _GetVersion(szFileName)) == NULL)
			{
				retVal = -1;
			}
			else
			{
				if(_VerCompare(szVer, "4.0.0.0") == -1)
				{
					retVal = 0;
				}
				else
				{
					free(szVer);
					
					_tcscpy(szFileName,szShortSysDir);
					_tcscat(szFileName, _T("\\advapi32.dll"));

					//Check the version of the advapi32.dll
					if((szVer = _GetVersion(szFileName)) == NULL)
					{
						retVal = -1;
					}
					else
					{
						if(_VerCompare(szVer, "4.0") == -1)
						{
							retVal = 0;
						}
						else
						{
							free(szVer);
							_tcscpy(szFileName,szShortSysDir);
							_tcscat(szFileName, _T("\\rsaenh.dll"));

							//Check the version of the advapi32.dll
							if((szVer = _GetVersion(szFileName)) == NULL)
							{
								//MessageBox(NULL, "Enhanced Cryptographic Provider Not found", NULL, MB_OK);
								retVal = 1; //Enhanced provider not found
							}
							else
							{
								//MessageBox(NULL, "Found the rsaenh.dll", NULL, MB_OK);
								//MessageBox(NULL, szVer, NULL, MB_OK);

								//Check if the enhanced cryptographic provider is good

								if(!_CheckMSEnhCSP(szVer))
								{
									if(!_FixMSEnhCSP(szVer))
									{
										retVal = 0;
									}
									else
									{
										retVal = 1;
									}
								}
								else
								{
									retVal = 1;
								}

								free(szVer);
							}
						}
					
					}
				}
			}
		}
	}
	return retVal;
}

LPSTR _GetVersion(LPSTR szFileName)
{

	//Get the version of the file
	DWORD dwHandle;
	DWORD dwFileVerInfoSize;
	dwFileVerInfoSize = GetFileVersionInfoSize(szFileName, &dwHandle);
	LPSTR szVersion;
	
	if(!dwFileVerInfoSize)
	{
		szVersion = NULL;
	}
	else
	{
		BYTE* verInfo;
		verInfo = (BYTE*)malloc(dwFileVerInfoSize);

		if(!verInfo)
		{
			szVersion = NULL;
		}
		else
		{
			//Return the version of the file
			if(!GetFileVersionInfo(szFileName,dwHandle, dwFileVerInfoSize, (LPVOID)verInfo))
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
		}
	
	}
	return(szVersion);

}

int _VerCompare(LPSTR szVer1, LPSTR szVer2)
{
	BOOL boolVer1StringOver = FALSE;
	BOOL boolVer2StringOver = FALSE;
	BOOL done = FALSE;
	char szVer1Number[16], szVer2Number[16];
	LPSTR szTmpVer1, szTmpVer2;
	char *cptrDotVer1, *cptrDotVer2;
	LPSTR szToken = ".\0\n";
	DWORD dwVer1Number, dwVer2Number;
	long result = 0;

	szTmpVer1 = szVer1;
	szTmpVer2 = szVer2;

	while(!(boolVer1StringOver || boolVer2StringOver || done))
	{
		cptrDotVer1 = strchr(szTmpVer1, '.');
		cptrDotVer2 = strchr(szTmpVer2, '.');

		//Get the next number from the string
		if(cptrDotVer1)
		{
			memcpy(szVer1Number, szTmpVer1, (cptrDotVer1 - szTmpVer1));
			szVer1Number[(cptrDotVer1 - szTmpVer1)] = '\0';
		}
		else
		{
			strcpy(szVer1Number,szTmpVer1);
			boolVer1StringOver = TRUE;
		}

		if(cptrDotVer2)
		{
			memcpy(szVer2Number, szTmpVer2, (cptrDotVer2 - szTmpVer2));
			szVer2Number[(cptrDotVer2 - szTmpVer2)] = '\0';
		}
		else
		{
			strcpy(szVer2Number,szTmpVer2);
			boolVer2StringOver = TRUE;
		}

//		szCurVrsnNumber = strtok(szTmpCurVrsn, szToken);
//		szLatestVrsnNumber = strtok(szTmpLatestVrsn, szToken);

		//if(strcmp(szCurVrsnNumber, "") && strcmp(szLatestVrsnNumber, ""))
		//{
			
			//Convert the strings into ints
			dwVer2Number = atoi(szVer2Number);
			dwVer1Number = atoi(szVer1Number);
			
			//Compare them
			if(dwVer2Number > dwVer1Number)
			{
				result = -1;
				done = TRUE;
			}
			else if (dwVer2Number < dwVer1Number)
			{
				result = 1;
				done = TRUE;
			}
			else
			{
				result = 0;
				done = FALSE;
			}
		//}


//		szTmpLatestVrsn = szTmpCurVrsn = NULL;
		szTmpVer2 = szTmpVer2 + strlen(szVer2Number) + 1;
		szTmpVer1 = szTmpVer1 + strlen(szVer1Number) + 1;
	
	}

	if(!done)
	{
		if(boolVer1StringOver && boolVer2StringOver)
			result = 0;
		else if(boolVer2StringOver)
			result = 1;
		else
			result = -1;
		}

	return result;
}

int _CheckMSEnhCSP(LPSTR szVersion)
{
	int retVal = 1;
	LONG err;
	LPSTR szRegKey = "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\Microsoft Enhanced Cryptographic Provider v1.0";
	HKEY hkEnhPrvdrKey;
	BYTE bVerInReg[136];
	DWORD dwVerInRegSize;


	//Open the registry key for the enhanced crypt provider
	err = RegOpenKeyEx(  HKEY_LOCAL_MACHINE,// handle of open key
		(LPCTSTR)szRegKey,  // address of name of subkey to open
		0,   // reserved  
		KEY_READ, // security access mask
		&hkEnhPrvdrKey // address of handle of open key
		);

	if(err)
	{
		retVal = 0; //Cryptographic provider not installed or not installed properly
	}
	else
	{
		//Check if the signature field is present
		
		err = RegQueryValueEx(  hkEnhPrvdrKey,// handle of key to query
			(LPTSTR) _T("Signature"),  // address of name of value to query
			NULL,  // reserved
			NULL,  // address of buffer for value type
			bVerInReg,       // address of data buffer
			&dwVerInRegSize     // address of data buffer size
			);

		if(err)
		{
			retVal = 0;
		}
		else
		{
					
			long lCmpResult;
			lCmpResult = _VerCompare(szVersion, "5.0.1620.82");
			if(lCmpResult != 1)
			{
				if(!strcmp(szVersion, "5.0.1620.82"))
				{
					for(int i =0; i < 136; ++i)
					{
						if(bVerInReg[i] != bSigForVer1[i])
						{
							retVal = 0;
						}
					}
				}
				else if(!strcmp(szVersion, "4.0.1381.4"))
				{
					//MessageBox(NULL, "Found the right version", "Error", MB_OK);
					for(int i =0; i < 136; ++i)
					{
						if(bVerInReg[i] != bSigForVer2[i])
						{
							//MessageBox(NULL, "Signature is corrupt", "Error", MB_OK);
							retVal = 0;
						}
					}
				}
				else if(!strcmp(szVersion, "4.0"))
				{
					//MessageBox(NULL, "Found the right version", "Error", MB_OK);
					for(int i =0; i < 136; ++i)
					{
						if(bVerInReg[i] != bSigForVer2[i])
						{
							//MessageBox(NULL, "Signature is corrupt", "Error", MB_OK);
							retVal = 0;
						}
					}
				}
				else if(!strcmp(szVersion, "4.00"))
				{
					//MessageBox(NULL, "Found the right version", "Error", MB_OK);
					for(int i =0; i < 136; ++i)
					{
						if(bVerInReg[i] != bSigForVer2[i])
						{
							//MessageBox(NULL, "Signature is corrupt", "Error", MB_OK);
							retVal = 0;
						}
					}
				}
				else
				{
					retVal = 0;
				}
			}
			else
			{
				retVal = 1;			
			}
			
		}

		RegCloseKey(hkEnhPrvdrKey);
	}

	return(retVal);
}

int _FixMSEnhCSP(LPSTR szVersion)
{
	int retVal = 1;
	int nVersion;


	//Check if we support this version
	if(!strcmp(szVersion, "5.0.1620.82"))
		nVersion = 1;
	else if(!strcmp(szVersion, "4.0.1381.4"))
		nVersion = 2;
	else if(!strcmp(szVersion, "4.0"))
		nVersion = 2;
	else if(!strcmp(szVersion, "4.00"))
		nVersion = 2;
	else
		nVersion = 0;

	if(!nVersion)
	{
		retVal = -1;
	}
	else
	{
		LONG err;
		HKEY hkEnhPrvdrKey;
		LPSTR szRegKey = "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\Microsoft Enhanced Cryptographic Provider v1.0";

		//Open the registry key
		err = RegOpenKeyEx(  HKEY_LOCAL_MACHINE,// handle of open key
			(LPCTSTR)szRegKey,  // address of name of subkey to open
			0,   // reserved  
			KEY_ALL_ACCESS, // security access mask
			&hkEnhPrvdrKey // address of handle of open key
			);

		if(err)
		{
			retVal = 0;
		}
		else
		{
			//Store the signature attribute


			switch(nVersion)
			{
			case 1:
				err = RegSetValueEx(hkEnhPrvdrKey,	// handle to key to set value for
					_T("Signature"),				// name of the value to set
					0,							    // reserved  
					REG_BINARY,				        // flag for value type
					bSigForVer1,					// address of value data
					136								// size of value data
					);
				if(err)
				{
					retVal = 0;
				}
				break;

			case 2:
				err = RegSetValueEx(hkEnhPrvdrKey,	// handle to key to set value for
					_T("Signature"),				// name of the value to set
					0,							    // reserved  
					REG_BINARY,				        // flag for value type
					bSigForVer2,					// address of value data
					136								// size of value data
					);
				if(err)
				{
					retVal = 0;
				}
				break;

			default :
				retVal = 0;
				break;
			}

			RegCloseKey(hkEnhPrvdrKey);
		}
	}
	
	

	return retVal;
}
