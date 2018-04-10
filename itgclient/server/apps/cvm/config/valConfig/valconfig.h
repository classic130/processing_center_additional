// valConfig.h : main header file for the VALCONFIG application
//

#if !defined(AFX_VALCONFIG_H__DB49B622_2272_11D2_9846_0060B0C189F3__INCLUDED_)
#define AFX_VALCONFIG_H__DB49B622_2272_11D2_9846_0060B0C189F3__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CValConfigApp:
// See valConfig.cpp for the implementation of this class
//

class CValConfigApp : public CWinApp
{
public:
	CValConfigApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CValConfigApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CValConfigApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VALCONFIG_H__DB49B622_2272_11D2_9846_0060B0C189F3__INCLUDED_)
