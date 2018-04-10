// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include <comutil.h>
#include "vsscode.h"
#include "certmgmt.h"
#include "settings.h"
#include "propsht.h"
#include "MainFrm.h"
#include "sign.h"
#include "util.h"
#include "ptaerrs.h"
#include "macros.h"
#include "vsserrs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_COMMAND(ID_CREATE_CSR, OnCreateCsr)
	ON_COMMAND(ID_INSTALL_CERT, OnInstallCert)
	ON_COMMAND(ID_SIGN_FILE, OnSignFile)
	ON_COMMAND(ID_IMPORT_CERT, OnImportCert)
	ON_COMMAND(ID_EXPORT_CERT, OnExportCert)
	ON_COMMAND(ID_ONLY_SIGN, OnOnlySign)
	ON_COMMAND(ID_SIGNATURE_PROPERTIES, OnSignatureProperties)
	ON_COMMAND(ID_CHANGE_PASSWD, OnChangePasswd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	CRegSettings usrSettings;
	usrSettings.Read();

	m_TimeSettings.bCurrentTime = ((usrSettings.m_dwTimerSetting != 0) ? TRUE : FALSE);
	GetLocalTime(&(m_TimeSettings.sysTime));
}

CMainFrame::~CMainFrame()
{
	// Store the 'TimerSetting' in the registry
	CRegSettings usrSettings;
	usrSettings.m_dwTimerSetting = ((m_TimeSettings.bCurrentTime == TRUE) ? 1 : 0);
	usrSettings.Write(TIMER_SETTING);
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers



void CMainFrame::OnCreateCsr() 
{
	HRESULT hr = S_OK;

	hr = CreateCSR();

	if(hr != S_OK && hr != E_USERCANCELLED)
		ShowErrorMessage(hr);
}



void CMainFrame::OnInstallCert() 
{
	HRESULT hr = S_OK;

	hr = InstallCert();

	if(hr == S_OK)
		ShowSuccessMessage(INSTALL_SUCCEEDED);
	else
		ShowErrorMessage(hr);
}


// For counter signature, or replacing the counter signature with a new one
void CMainFrame::OnSignFile() 
{
	HRESULT hr = S_OK;
		
	hr = SignFile(&m_TimeSettings);

	if(hr == S_OK)
		ShowSuccessMessage(SIGN_SUCCEEDED);
	else
	{
		if(hr != E_VSSCODE_DOCEXISTS)	// This error is already being handled in SignFile() fn
			ShowErrorMessage(hr);
	}
}



void CMainFrame::OnImportCert() 
{
	HRESULT hr = S_OK;
	
	hr = ImportCert();

	if(hr == S_OK)
		ShowSuccessMessage(IMPORT_SUCCEEDED);
	else
		ShowErrorMessage(hr);
}



void CMainFrame::OnExportCert() 
{
	HRESULT hr = S_OK;

	hr = ExportCert();

	if(hr == S_OK)
		ShowSuccessMessage(EXPORT_SUCCEEDED);
	else
		ShowErrorMessage(hr);
}


// For adding the first signature
void CMainFrame::OnOnlySign() 
{
	HRESULT hr = S_OK;
	
	hr = OnlySignFile(&m_TimeSettings); 

	if(hr == S_OK)
		ShowSuccessMessage(SIGN_SUCCEEDED);
	else
	{
		if(hr != E_VSSCODE_DOCEXISTS)	// This error is already being handled in OnlySignFile() fn
			ShowErrorMessage(hr);
	}
}


void CMainFrame::OnSignatureProperties() 
{
	DoSignatureProp(&m_TimeSettings);
}


void CMainFrame::OnChangePasswd() 
{
	HRESULT hr = S_OK;
	
	hr = ChangePassword();

	if(hr == S_OK)
		ShowSuccessMessage(CHANGE_PASSWD_SUCCEEDED);
	else
		ShowErrorMessage(hr);
}
