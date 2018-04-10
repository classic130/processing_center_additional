// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__6F33FF98_7187_11D5_8C95_0010830169AF__INCLUDED_)
#define AFX_MAINFRM_H__6F33FF98_7187_11D5_8C95_0010830169AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
	TimeSettings m_TimeSettings;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg void OnCreateCsr();
	afx_msg void OnInstallCert();
	afx_msg void OnSignFile();
	afx_msg void OnImportCert();
	afx_msg void OnExportCert();
	afx_msg void OnOnlySign();
	afx_msg void OnSignatureProperties();
	afx_msg void OnChangePasswd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__6F33FF98_7187_11D5_8C95_0010830169AF__INCLUDED_)
