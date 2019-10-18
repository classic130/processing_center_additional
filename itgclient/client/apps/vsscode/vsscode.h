// vsscode.h : main header file for the VSSCODE application
//

#if !defined(AFX_VSSCODE_H__6F33FF94_7187_11D5_8C95_0010830169AF__INCLUDED_)
#define AFX_VSSCODE_H__6F33FF94_7187_11D5_8C95_0010830169AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVsscodeApp:
// See vsscode.cpp for the implementation of this class
//

class CVsscodeApp : public CWinApp
{
public:
	CVsscodeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVsscodeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CVsscodeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSSCODE_H__6F33FF94_7187_11D5_8C95_0010830169AF__INCLUDED_)
