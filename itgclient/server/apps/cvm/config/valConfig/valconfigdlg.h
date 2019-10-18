// valConfigDlg.h : header file
//

#if !defined(AFX_VALCONFIGDLG_H__DB49B624_2272_11D2_9846_0060B0C189F3__INCLUDED_)
#define AFX_VALCONFIGDLG_H__DB49B624_2272_11D2_9846_0060B0C189F3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CValConfigDlg dialog

class CValConfigDlg : public CDialog
{
// Construction
public:
	CValConfigDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CValConfigDlg)
	enum { IDD = IDD_VALCONFIG_DIALOG };
	CString	m_CfgFilename;
	CString	m_FilePrefix;
	CString	m_UrlPrefix;
	CString	m_CacheDir;
	BOOL	m_LogInfo;
	BOOL	m_LogSecurity;
	CString	m_DefaultLdap;
	CString	m_UpdateHours;
	CString	m_HttpProxy;
	CString	m_ErrorCgi;
	CString	m_LogFileName;
/*  Fix for CR29977 - Begin */
/*	BOOL	m_NoCheckChain;   */
        BOOL    m_CheckChain;
/*  Fix for CR29977 - End   */
	BOOL    m_IsaInstall;
	CString	m_LdapHttpProxy;
	CString	m_ProtectedDirs;
	CString	m_OcspUrl;
	//}}AFX_DATA

	BOOL initFromRegistry(); // Read values from registry
	BOOL initFromHardCoded(); // Read from compiled in strings

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CValConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnResetButton();
    afx_msg void OnYesIsaInstall();
    afx_msg void OnNoIsaInstall();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALCONFIGDLG_H__DB49B624_2272_11D2_9846_0060B0C189F3__INCLUDED_)
