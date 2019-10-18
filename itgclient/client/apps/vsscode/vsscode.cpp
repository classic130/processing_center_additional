// vsscode.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "vsscode.h"
#include "propsht.h"
#include "MainFrm.h"
#include "vsscodeDoc.h"
#include "vsscodeView.h"

#include <comutil.h>
#include "certmgmt.h"
#include "macros.h"
#include "settings.h"
#include "util.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVsscodeApp

BEGIN_MESSAGE_MAP(CVsscodeApp, CWinApp)
	//{{AFX_MSG_MAP(CVsscodeApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVsscodeApp construction

CVsscodeApp::CVsscodeApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVsscodeApp object

CVsscodeApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVsscodeApp initialization

BOOL CVsscodeApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CVsscodeDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CVsscodeView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Set the application name
	m_pMainWnd->SetWindowText(_T("Code Signing Agent"));

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Determine which menu items need to be shown depending on the code type registry key
	CWnd *pMainWnd = NULL;
	CMenu *pMainMenu = NULL, *pSigPopupMenu = NULL;
	UINT nMenuItems = 0;
	CRegSettings usrSettings;

	do
	{
		// First see if we can get to the 'Signature' popup menu at all
		pMainWnd = AfxGetMainWnd();
		if(!pMainWnd)
			break;

		pMainMenu = pMainWnd->GetMenu();
		if(!pMainMenu)
			break;

		nMenuItems = pMainMenu->GetMenuItemCount();

		for(UINT i = 0; i < nMenuItems; i++)
		{
			CString strMenuName;

			pMainMenu->GetMenuString(i, strMenuName, MF_BYPOSITION);

			if(strMenuName == "&Signature")
				break;
		}

		pSigPopupMenu = pMainMenu->GetSubMenu(i);
		if(!pSigPopupMenu)
			break;


		// Check the registry now
		usrSettings.Read();

		if(usrSettings.m_bstrCodeType == _bstr_t("CableModem"))
		{
			// Remove the 'Sign File' menu item
			pSigPopupMenu->RemoveMenu(ID_ONLY_SIGN, MF_BYCOMMAND);
		}
		else
			if(usrSettings.m_bstrCodeType == _bstr_t("SignOp"))
			{
				// Check if we need to do a counter signature also
				if(usrSettings.m_dwCounterSign == 0)
				{
					// Remove the 'Counter Sign File' 'menu item
					pSigPopupMenu->RemoveMenu(ID_SIGN_FILE, MF_BYCOMMAND);
				}
			}
			else
			{
				// Remove all menu items under 'Signature' pop up menu
				pSigPopupMenu->RemoveMenu(ID_ONLY_SIGN, MF_BYCOMMAND);
				pSigPopupMenu->RemoveMenu(ID_SIGN_FILE, MF_BYCOMMAND);
				pSigPopupMenu->RemoveMenu(ID_SIGNATURE_PROPERTIES, MF_BYCOMMAND);
				pSigPopupMenu->RemoveMenu(0, MF_BYPOSITION);
			}

	}while(0);

	INITCOMMONCONTROLSEX cControls;
	cControls.dwSize = sizeof(INITCOMMONCONTROLSEX);
	cControls.dwICC = ICC_DATE_CLASSES;

	InitCommonControlsEx(&cControls);

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVsscodeApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVsscodeApp message handlers

