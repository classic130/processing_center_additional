#if !defined(AFX_OPENPROFDLG_H__57B0022C_11B8_11D5_8204_0060B0F885E6__INCLUDED_)
#define AFX_OPENPROFDLG_H__57B0022C_11B8_11D5_8204_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenProfDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COpenProfDlg dialog

class COpenProfDlg : public CDialog
{
// Construction
public:
	COpenProfDlg(CWnd* pParent = NULL);   // standard constructor
	_bstr_t m_tbstrPassword;

// Dialog Data
	//{{AFX_DATA(COpenProfDlg)
	enum { IDD = IDD_OPENPROF };
	CButton	m_OK;
	CButton	m_SquareBtn;
	CButton	m_SemicircleBtn;
	CButton	m_EllipseBtn;
	CButton	m_DiamondBtn;
	CButton	m_CrossBtn;
	CButton	m_CircleBtn;
	CString	m_UserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenProfDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COpenProfDlg)
	afx_msg void OnCircle();
	afx_msg void OnClear();
	afx_msg void OnDiamond();
	afx_msg void OnEllipse();
	afx_msg void OnSemicircle();
	afx_msg void OnSquare();
	afx_msg void OnChangeUsername();
	virtual void OnOK();
	afx_msg void OnCrossbmp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private :
	int m_nPasswdCurrPos;	

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENPROFDLG_H__57B0022C_11B8_11D5_8204_0060B0F885E6__INCLUDED_)
