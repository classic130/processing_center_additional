// valConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "valConfig.h"
#include "valConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CValConfigDlg dialog

CValConfigDlg::CValConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CValConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CValConfigDlg)
	m_CfgFilename = _T("");
	m_FilePrefix = _T("");
	m_UrlPrefix = _T("");
	m_CacheDir = _T("");
	m_LogInfo = TRUE;
	m_LogSecurity = TRUE;
	m_DefaultLdap = _T("");
	m_UpdateHours = _T("");
	m_HttpProxy = _T("");
	m_ErrorCgi = _T("");
	m_LogFileName = _T("");
/*  Fix for CR29977 - Begin */
/*      m_NoCheckChain = FALSE;   */
        m_CheckChain = TRUE;
/*  Fix for CR29977 - End   */
	m_LdapHttpProxy = _T("");
 	m_ProtectedDirs = _T("");
 	m_OcspUrl = _T("");
	m_IsaInstall = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// First set things to the hard coded values...
	initFromHardCoded();
	
	// then override with existing registry values, if any.
	initFromRegistry();

}

void CValConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CValConfigDlg)
	DDX_Text(pDX, IDC_EDIT1, m_CfgFilename);
	DDV_MaxChars(pDX, m_CfgFilename, 1024);
	DDX_Text(pDX, IDC_EDIT2, m_FilePrefix);
	DDV_MaxChars(pDX, m_FilePrefix, 1024);
	DDX_Text(pDX, IDC_EDIT3, m_UrlPrefix);
	DDV_MaxChars(pDX, m_UrlPrefix, 1024);
	DDX_Text(pDX, IDC_EDIT4, m_CacheDir);
	DDV_MaxChars(pDX, m_CacheDir, 1024);
	DDX_Check(pDX, IDC_CHECK1, m_LogInfo);
	DDX_Check(pDX, IDC_CHECK2, m_LogSecurity);
	DDX_Text(pDX, IDC_EDIT5, m_DefaultLdap);
	DDV_MaxChars(pDX, m_DefaultLdap, 1024);
	DDX_Text(pDX, IDC_EDIT6, m_UpdateHours);
	DDV_MaxChars(pDX, m_UpdateHours, 64);
	DDX_Text(pDX, IDC_EDIT7, m_HttpProxy);
	DDV_MaxChars(pDX, m_HttpProxy, 1024);
	DDX_Text(pDX, IDC_EDIT8, m_ErrorCgi);
	DDV_MaxChars(pDX, m_ErrorCgi, 1024);
	DDX_Text(pDX, IDC_EDIT9, m_LogFileName);
	DDV_MaxChars(pDX, m_LogFileName, 1024);
/*  Fix for CR29977 - Begin */
/*	DDX_Check(pDX, IDC_CHECK3, m_NoCheckChain);  */
        DDX_Check(pDX, IDC_CHECK3, m_CheckChain);	
/*  Fix for CR29977 - End   */
        DDX_Text(pDX, IDC_EDIT12, m_LdapHttpProxy);
	DDV_MaxChars(pDX, m_LdapHttpProxy, 1024);
	DDX_Text(pDX, IDC_EDIT13, m_ProtectedDirs);
	DDV_MaxChars(pDX, m_ProtectedDirs, 1024);
	DDX_Text(pDX, IDC_EDIT14, m_OcspUrl);
	DDV_MaxChars(pDX, m_OcspUrl, 1024);

	DDX_Radio(pDX, IDC_RADIO_NO_ISA_INSTALL, m_IsaInstall);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CValConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CValConfigDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnResetButton)
	ON_BN_CLICKED(IDC_RADIO_YES_ISA_INSTALL, OnYesIsaInstall)
	ON_BN_CLICKED(IDC_RADIO_NO_ISA_INSTALL, OnNoIsaInstall)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CValConfigDlg message handlers

BOOL CValConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CValConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CValConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CValConfigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


#define BUF_MAX 1025

CString getRegValue(PHKEY hkey, char *name) {

	BYTE valueBuf[BUF_MAX];
	DWORD valueLen = BUF_MAX;
	DWORD type = 0;
	CString rStr;

	valueBuf[0] = '\0';

	if (RegQueryValueEx(*hkey, name,  0,
		&type, valueBuf, &valueLen)==ERROR_SUCCESS && type==REG_SZ) {

			rStr = valueBuf;
	}
	else {
		rStr = "";
	}

	return rStr;
}

// Initialize dialog entries with current registry values. 
BOOL CValConfigDlg::initFromRegistry()
{
	BOOL status = FALSE;
	CString boolString;
	HKEY hkey;
	
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"Software\\VeriSign\\Validate\\2.0", 0, 
		KEY_ALL_ACCESS, &hkey)==ERROR_SUCCESS) {
		
		m_CfgFilename = getRegValue(&hkey, "CfgFilename");
		m_FilePrefix = getRegValue(&hkey, "FilePrefix");
		m_UrlPrefix = getRegValue(&hkey, "UrlPrefix");
		m_CacheDir = getRegValue(&hkey, "CacheDir");
		m_DefaultLdap = getRegValue(&hkey, "DefaultLdap");
		m_UpdateHours = getRegValue(&hkey, "UpdateHours");
		boolString = getRegValue(&hkey, "LogSecurity");
		m_LogSecurity = (boolString[0]=='1' ? 1 : 0);
		boolString = getRegValue(&hkey, "LogInfo");
		m_LogInfo = (boolString[0]=='1' ? 1 : 0);
/*  Fix for CR29977 - Begin */
               
               /* boolString = getRegValue(&hkey, "NoCheckChain");
                m_NoCheckChain = (boolString[0]=='1' ? 1 : 0);
               */ 
                boolString = getRegValue(&hkey, "CheckChain");	
               if (boolString == "") {  
                boolString = getRegValue(&hkey, "NoCheckChain");
                  if ( boolString[0]=='1'){
                    m_CheckChain = 0;
                 } 
                  else{ 
                  if ( boolString[0]=='0')
                    m_CheckChain = 1;
                 } 
                }
               else                
                m_CheckChain = (boolString[0]=='1' ? 1 : 0);
/*  Fix for CR29977 - End   */

		boolString = getRegValue(&hkey, "IsaInstall");
		m_IsaInstall = (boolString[0]=='1' ? 1 : 0);	
		m_ProtectedDirs = getRegValue(&hkey, "ProtectedDirs");
		m_OcspUrl = getRegValue(&hkey, "OcspUrl");
		m_HttpProxy = getRegValue(&hkey, "HttpProxy");
		m_LdapHttpProxy = getRegValue(&hkey, "LdapHttpProxy");
		m_ErrorCgi = getRegValue(&hkey, "ErrorCgi");
		m_LogFileName = getRegValue(&hkey, "LogFileName");
		
		RegCloseKey(hkey);

		status = TRUE;
	}
	else {
		status = FALSE;
	}
	
	return status;
}

// Initialize dialog entries with current registry values. 
BOOL CValConfigDlg::initFromHardCoded()
{
	BOOL status = TRUE;

	m_CfgFilename = _T("c:\\VeriSign\\cvm\\config\\val_config.txt");
	m_FilePrefix = _T("c:\\VeriSign\\cvm\\certcache\\");
	m_UrlPrefix = _T("http://onsitecrl.verisign.com/");
	m_CacheDir = _T("c:\\VeriSign\\cvm\\certcache");
/*  Fix for CR29977 - Begin */
      /* m_NoCheckChain = TRUE;  */
        m_CheckChain = TRUE;
/*  Fix for CR29977 - End   */
        m_LogInfo = TRUE;
	m_LogSecurity = TRUE;
	m_IsaInstall = FALSE;
	m_DefaultLdap = _T("directory.verisign.com");
	m_UpdateHours = _T("24");
	m_HttpProxy = "";
	m_LdapHttpProxy = "";
	m_ProtectedDirs = "/";
	m_OcspUrl = "";
	m_ErrorCgi =  "";
	m_LogFileName = "c:\\VeriSign\\cvm\\logs\\validate.log";		
	return status;
}


void CValConfigDlg::OnResetButton() 
{
	// Reset to factory defaults.

	initFromHardCoded();

	CDialog::UpdateData(FALSE);
}

void CValConfigDlg::OnYesIsaInstall() 
{
	m_IsaInstall = FALSE;
}

void CValConfigDlg::OnNoIsaInstall() 
{
	m_IsaInstall = TRUE;
}
