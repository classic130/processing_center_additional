// OpenProfDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSAuthSmpl.h"
#include "OpenProfDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenProfDlg dialog
extern CVSAuthSmplApp theApp;

COpenProfDlg::COpenProfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenProfDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COpenProfDlg)
	m_UserName = _T("");
	//}}AFX_DATA_INIT

	m_nPasswdCurrPos = 0;
	m_tbstrPassword = "";
}


void COpenProfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenProfDlg)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_SQUARE, m_SquareBtn);
	DDX_Control(pDX, IDC_SEMICIRCLE, m_SemicircleBtn);
	DDX_Control(pDX, IDC_ELLIPSE, m_EllipseBtn);
	DDX_Control(pDX, IDC_DIAMOND, m_DiamondBtn);
	DDX_Control(pDX, IDC_CROSSBMP, m_CrossBtn);
	DDX_Control(pDX, IDC_CIRCLE, m_CircleBtn);
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COpenProfDlg, CDialog)
	//{{AFX_MSG_MAP(COpenProfDlg)
	ON_BN_CLICKED(IDC_CIRCLE, OnCircle)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_DIAMOND, OnDiamond)
	ON_BN_CLICKED(IDC_ELLIPSE, OnEllipse)
	ON_BN_CLICKED(IDC_SEMICIRCLE, OnSemicircle)
	ON_BN_CLICKED(IDC_SQUARE, OnSquare)
	ON_EN_CHANGE(IDC_USERNAME, OnChangeUsername)
	ON_BN_CLICKED(IDC_CROSSBMP, OnCrossbmp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenProfDlg message handlers

void COpenProfDlg::OnCircle() 
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

void COpenProfDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_nPasswdCurrPos; ++i)
	{
		::ShowWindow((GetDlgItem(IDC_PASSWRDPOS1+i))->m_hWnd,FALSE);
	}
	m_nPasswdCurrPos = 0;
	m_tbstrPassword = "";
}

void COpenProfDlg::OnDiamond() 
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

void COpenProfDlg::OnEllipse() 
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

void COpenProfDlg::OnSemicircle() 
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

void COpenProfDlg::OnSquare() 
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
}

void COpenProfDlg::OnChangeUsername() 
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

void COpenProfDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_tbstrPassword.length() < 6)
	{
		MessageBox("Select a passfigure that has atleast 6 shapes");
		return;
	}
	
	CDialog::OnOK();
}

void COpenProfDlg::OnCrossbmp() 
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

BOOL COpenProfDlg::OnInitDialog() 
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
