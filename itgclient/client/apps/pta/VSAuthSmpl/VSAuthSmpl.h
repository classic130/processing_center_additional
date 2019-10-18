// VSAuthSmpl.h : main header file for the VSAUTHSMPL DLL
//

#if !defined(AFX_VSAUTHSMPL_H__DD44B60C_0F60_11D5_8204_0060B0F885E6__INCLUDED_)
#define AFX_VSAUTHSMPL_H__DD44B60C_0F60_11D5_8204_0060B0F885E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CVSAuthSmplApp
// See VSAuthSmpl.cpp for the implementation of this class
//

#define AUTHDLL_OPENPROF 0x0001
#define AUTHDLL_CREATEPROF 0x0002

class CVSAuthSmplApp : public CWinApp
{
public:
	CVSAuthSmplApp();
	int GetUsernamePasswd(int i_nPurpose, int i_nPasswdQuality, _bstr_t& i_tbstrAppCtxt, _bstr_t* o_ptbstrUserName, _bstr_t* o_ptbstrPasswd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSAuthSmplApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CVSAuthSmplApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSAUTHSMPL_H__DD44B60C_0F60_11D5_8204_0060B0F885E6__INCLUDED_)
