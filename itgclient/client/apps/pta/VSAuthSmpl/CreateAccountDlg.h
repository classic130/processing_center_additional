#if !defined(AFX_CREATEACCOUNTDLG_H__DD44B614_0F60_11D5_8204_0060B0F885E6__INCLUDED_)
#define AFX_CREATEACCOUNTDLG_H__DD44B614_0F60_11D5_8204_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateAccountDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateAccountDlg dialog

class CCreateAccountDlg : public CDialog
{
// Construction
public:
	CCreateAccountDlg(CWnd* pParent = NULL);   // standard constructor
	_bstr_t m_tbstrPassword;

// Dialog Data
	//{{AFX_DATA(CCreateAccountDlg)
	enum { IDD = IDD_CREATEPROF };
	CButton	m_OK;
	CButton	m_SemicircleBtn;
	CButton	m_EllipseBtn;
	CButton	m_DiamondBtn;
	CButton	m_CrossBtn;
	CButton	m_CircleBtn;
	CButton	m_SquareBtn;
	CString	m_UserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateAccountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCreateAccountDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSquare();
	afx_msg void OnCrossbmp();
	afx_msg void OnSemicircle();
	afx_msg void OnDiamond();
	afx_msg void OnEllipse();
	afx_msg void OnCircle();
	afx_msg void OnClear();
	virtual void OnOK();
	afx_msg void OnChangeUsername();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private :
	int m_nPasswdCurrPos;	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEACCOUNTDLG_H__DD44B614_0F60_11D5_8204_0060B0F885E6__INCLUDED_)
