// CreateAccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAuthSmpl.h"
#include "CreateAccountDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateAccountDlg dialog
extern CVSAuthSmplApp theApp;

CCreateAccountDlg::CCreateAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateAccountDlg)
	m_UserName = _T("");
	//}}AFX_DATA_INIT

	m_nPasswdCurrPos = 0;
	m_tbstrPassword = "";
}


void CCreateAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateAccountDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_SEMICIRCLE, m_SemicircleBtn);
	DDX_Control(pDX, IDC_ELLIPSE, m_EllipseBtn);
	DDX_Control(pDX, IDC_DIAMOND, m_DiamondBtn);
	DDX_Control(pDX, IDC_CROSSBMP, m_CrossBtn);
	DDX_Control(pDX, IDC_CIRCLE, m_CircleBtn);
	DDX_Control(pDX, IDC_SQUARE, m_SquareBtn);
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateAccountDlg)
	ON_BN_CLICKED(IDC_SQUARE, OnSquare)
	ON_BN_CLICKED(IDC_CROSSBMP, OnCrossbmp)
	ON_BN_CLICKED(IDC_SEMICIRCLE, OnSemicircle)
	ON_BN_CLICKED(IDC_DIAMOND, OnDiamond)
	ON_BN_CLICKED(IDC_ELLIPSE, OnEllipse)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_EN_CHANGE(IDC_USERNAME, OnChangeUsername)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateAccountDlg message handlers

BOOL CCreateAccountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_SquareBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_SQUARE)));
	m_CircleBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_CIRCLE)));
	m_CrossBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_CROSS)));
	m_DiamondBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_DIAMOND)));
	m_SemicircleBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_SEMICIRCLE)));
	m_EllipseBtn.SetBitmap(LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_ELLIPSE)));
	
	if(!m_UserName.IsEmpty())
		m_OK.EnableWindow(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateAccountDlg::OnSquare() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_SQUARE)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "1";
		m_nPasswdCurrPos++;
	}

	return;

}

void CCreateAccountDlg::OnCrossbmp() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_CROSS)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "2";
		m_nPasswdCurrPos++;
	}

}

void CCreateAccountDlg::OnSemicircle() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_SEMICIRCLE)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "3";
		m_nPasswdCurrPos++;
	}
	
}


void CCreateAccountDlg::OnDiamond() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_DIAMOND)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "4";
		m_nPasswdCurrPos++;
	}
	
}

void CCreateAccountDlg::OnEllipse() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_ELLIPSE)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "5";
		m_nPasswdCurrPos++;
	}
	
}

void CCreateAccountDlg::OnCircle() 
{
	// TODO: Add your control notification handler code here
	if(m_nPasswdCurrPos < 8)
	{
		SendDlgItemMessage(IDC_PASSWRDPOS1+m_nPasswdCurrPos,STM_SETIMAGE,IMAGE_BITMAP,
			(LPARAM)LoadBitmap(theApp.m_hInstance,MAKEINTRESOURCE(IDB_CIRCLE)));
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+m_nPasswdCurrPos))->m_hWnd,TRUE);
		m_tbstrPassword = m_tbstrPassword + "6";
		m_nPasswdCurrPos++;
	}
	
}

void CCreateAccountDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_nPasswdCurrPos; ++i)
	{
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+i))->m_hWnd,FALSE);
	}
	m_nPasswdCurrPos = 0;
	m_tbstrPassword = "";
}

void CCreateAccountDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_tbstrPassword.length() < 6)
	{
		MessageBox("Select a passfigure that has atleast 6 shapes");
		return;
	}

	CDialog::OnOK();
}

void CCreateAccountDlg::OnChangeUsername() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	if(!m_UserName.IsEmpty())
	{
		m_OK.EnableWindow();
	}
	else
		m_OK.EnableWindow(FALSE);
}
