// valConfig.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "valConfig.h"
#include "valConfigDlg.h"

#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BUF_MAX 1025

LONG setValue(PHKEY hkey, const char *name, const char *value) {

	BYTE valueBuf[BUF_MAX];
	DWORD valueLen = 0;

	sprintf((char *) valueBuf, "%s", value);
	valueLen = strlen((char *) valueBuf) + 1;

	return RegSetValueEx(*hkey, name, 0, REG_SZ, 
		valueBuf, valueLen);
	
}

LONG setBoolValue(PHKEY hkey, const char *name, BOOL value) {

	LONG rc = 0;

	if (value) rc = setValue(hkey, name, "1");
	else rc = setValue(hkey, name, "0");

	return rc;
}


/////////////////////////////////////////////////////////////////////////////
// CValConfigApp

BEGIN_MESSAGE_MAP(CValConfigApp, CWinApp)
	//{{AFX_MSG_MAP(CValConfigApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValConfigApp construction

CValConfigApp::CValConfigApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CValConfigApp object

CValConfigApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CValConfigApp initialization

BOOL CValConfigApp::InitInstance()
{
	LONG rc = 0;
	DWORD isNewKey = 0;
	HKEY hkeySoftware, hkeyVerisign, hkeyValidate, hkeyVersion;

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CValConfigDlg dlg;
	m_pMainWnd = &dlg;
	
	int nResponse = dlg.DoModal();
	
	if (nResponse == IDOK)
	{		
		
		if ((rc = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
			"Software", 0, KEY_ALL_ACCESS, &hkeySoftware))
			==ERROR_SUCCESS) {
			
			if((rc=RegCreateKeyEx(hkeySoftware, "VeriSign", 0, 
				0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
				0, &hkeyVerisign, &isNewKey))==ERROR_SUCCESS) {
				
				if((rc=RegCreateKeyEx(hkeyVerisign, "Validate", 0,
					0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
					0, &hkeyValidate, &isNewKey))==ERROR_SUCCESS) {
					
					if((rc=RegCreateKeyEx(hkeyValidate, "2.0", 0,
						0, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
						0, &hkeyVersion, &isNewKey))==ERROR_SUCCESS) {
						
						do {
							
							if ((rc = setValue(&hkeyVersion, 
								"CfgFilename", dlg.m_CfgFilename))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"FilePrefix", dlg.m_FilePrefix))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion, 
								"UrlPrefix", dlg.m_UrlPrefix))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion, 
								"CacheDir", dlg.m_CacheDir))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion, 
								"DefaultLdap", dlg.m_DefaultLdap))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion, 
								"UpdateHours", dlg.m_UpdateHours))
								!=ERROR_SUCCESS)
								break;
							
                                               /*  Fix for CR29977 - Begin */ 
					         /*		if ((rc = setBoolValue(&hkeyVersion,
								"NoCheckChain", dlg.m_NoCheckChain))
								!=ERROR_SUCCESS)
								break;
                                                 */
                                                        if ((rc = setBoolValue(&hkeyVersion,
                                                                "CheckChain", dlg.m_CheckChain))
                                                                !=ERROR_SUCCESS)
                                                                 break;

                                               /*  Fix for CR29977 - End   */                                      
							

							if ((rc = setBoolValue(&hkeyVersion,
								"LogSecurity", dlg.m_LogSecurity))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setBoolValue(&hkeyVersion,
								"LogInfo", dlg.m_LogInfo))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setBoolValue(&hkeyVersion,
								"IsaInstall", dlg.m_IsaInstall))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"HttpProxy", dlg.m_HttpProxy))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"LdapHttpProxy", dlg.m_LdapHttpProxy))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"ProtectedDirs", dlg.m_ProtectedDirs))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"OcspUrl", dlg.m_OcspUrl))
								!=ERROR_SUCCESS)
								break;
							
							if ((rc = setValue(&hkeyVersion,
								"ErrorCgi", dlg.m_ErrorCgi))
								!=ERROR_SUCCESS)
								break;
														
							if ((rc = setValue(&hkeyVersion,
								"LogFileName", dlg.m_LogFileName))
								!=ERROR_SUCCESS)
								break;														
						} while (0);
						
						
						RegCloseKey(hkeyVersion);
					}	
					
					RegCloseKey(hkeyValidate);
				}	
				
				RegCloseKey(hkeyVerisign);
			}	
			RegCloseKey(hkeySoftware);
		}
		
		// Update registry when the dialog is dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// Just don't do anything when canceled.
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


