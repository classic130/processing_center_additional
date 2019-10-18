#if !defined(AFX_DLGCSR_H__6F33FFA3_7187_11D5_8C95_0010830169AF__INCLUDED_)
#define AFX_DLGCSR_H__6F33FFA3_7187_11D5_8C95_0010830169AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCSR.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCSR dialog

class CDlgCSR : public CDialog
{
// Construction
public:
	CDlgCSR(CWnd* pParent = NULL);   // standard constructor

	CertificateOp m_CertOp;

// Dialog Data
	//{{AFX_DATA(CDlgCSR)
	enum { IDD = IDD_DLG_CERTIFICATE };
	CString	m_csCertData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCSR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation


public:
	HRESULT SetCSR(const _bstr_t& i_bstrCSR);
	HRESULT GetCertificate(_bstr_t& bstrCert);

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCSR)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCSR_H__6F33FFA3_7187_11D5_8C95_0010830169AF__INCLUDED_)
