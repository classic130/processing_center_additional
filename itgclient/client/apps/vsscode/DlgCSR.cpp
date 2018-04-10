// DlgCSR.cpp : implementation file
//

#include "stdafx.h"
#include "vsscode.h"
#include <comutil.h>
#include "certmgmt.h"
#include "DlgCSR.h"
#include "propsht.h"
#include "util.h"
#include "macros.h"
#include "vsserrs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCSR dialog


CDlgCSR::CDlgCSR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCSR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCSR)
	m_csCertData = _T("");
	//}}AFX_DATA_INIT
}


void CDlgCSR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCSR)
	DDX_Text(pDX, IDE_CERTIFICATE, m_csCertData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCSR, CDialog)
	//{{AFX_MSG_MAP(CDlgCSR)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCSR message handlers

/*
	Set the 'm_csCertData' member variable to the currently generated certificate enrollment request
*/
HRESULT CDlgCSR::SetCSR(const _bstr_t& i_bstrCSR)
{
	HRESULT hr = S_OK;
	WCHAR* pwCSRNewLine = NULL, pwTemp[2];
	DWORD dwCSRLen = 0;
	CString csTemp;

	do
	{
		pwCSRNewLine = i_bstrCSR.copy();
		dwCSRLen = i_bstrCSR.length();

		for(UINT i = 0; i < dwCSRLen; i++)
		{
			if(pwCSRNewLine[i] == '\r' || pwCSRNewLine[i] == '\n')
				continue;

			pwTemp[0] = pwCSRNewLine[i];
			pwTemp[1] = NULL;

			csTemp = pwTemp;

			m_csCertData += csTemp;
		}

	}while(0);


	SYS_FREE_MEMORY(pwCSRNewLine)

	return hr;
}

/*
	Get the certificate to be installed from the 'm_csCertData' member variable
*/
HRESULT CDlgCSR::GetCertificate(_bstr_t& bstrCert)
{
	HRESULT hr = S_OK;

	bstrCert = m_csCertData;

	return hr;
}


BOOL CDlgCSR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	HRESULT hr = S_OK;
	WCHAR* pwDlgTitle = NULL, *pwDesc = NULL;
	_bstr_t tbstrDlgTitle = "", tbstrDesc = "";
	CWnd* pCertWindow = NULL, *pDescWindow = NULL;

	do
	{
		if(m_CertOp == CERT_INSTALL)
		{
			// Load the dialog box title and the description strings
			hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_CERT_INSTALL, &pwDlgTitle);
			CHECK_HRESULT_BREAK

			hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_INSTALL_DESC, &pwDesc);
			CHECK_HRESULT_BREAK
		}
		else
			if(m_CertOp == CERT_ENROLL)
			{
				// Set the edit control as READ_ONLY
				pCertWindow = GetDlgItem(IDE_CERTIFICATE);
				pCertWindow->SendMessage(EM_SETREADONLY, TRUE, 0);

				// Load the dialog box title and the description strings
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_CERT_ENROLL, &pwDlgTitle);
				CHECK_HRESULT_BREAK
		
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_ENROLL_DESC, &pwDesc);
				CHECK_HRESULT_BREAK
			}

		// Set the dialog box title and the description strings
		tbstrDlgTitle = pwDlgTitle;
		SetWindowText(tbstrDlgTitle);

		tbstrDesc = pwDesc;
		pDescWindow = GetDlgItem(IDC_DESC);
		pDescWindow->SetWindowText(tbstrDesc);

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("CDlgCSR::OnInitDialog().", "Error initializing the dialog box.", NULL, hr);

	FREE_MEMORY(pwDlgTitle)
	FREE_MEMORY(pwDesc)
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgCSR::OnOK() 
{
	UpdateData(TRUE);

	// Check if user has entered something in the dialog box
	if(m_CertOp == CERT_INSTALL)
		if(m_csCertData == "")
		{
			ShowErrorMessage(E_VSSCODE_NO_CERT_SPECIFIED);
			return;
		}
	
	CDialog::OnOK();
}
