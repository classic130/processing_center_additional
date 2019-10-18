// VSAuthSmpl.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "VSAuthSmpl.h"
#include "createaccountdlg.h"
#include "openprofdlg.h"
#include "vsauthsmplerrs.h"
#include "vsauthsmpldefines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CVSAuthSmplApp

BEGIN_MESSAGE_MAP(CVSAuthSmplApp, CWinApp)
	//{{AFX_MSG_MAP(CVSAuthSmplApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSAuthSmplApp construction

CVSAuthSmplApp::CVSAuthSmplApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

int CVSAuthSmplApp::GetUsernamePasswd(int i_nPurpose, int i_nPasswdQuality, _bstr_t& i_tbstrAppCtxt, _bstr_t* io_ptbstrUserName, _bstr_t* o_ptbstrPasswd)
{
	int retVal = 0;

	do
	{
		if(i_nPurpose == AUTHDLL_CREATEPROF)
		{
			CCreateAccountDlg theCreateAccDlg;
			theCreateAccDlg.m_UserName = (CHAR*)(*io_ptbstrUserName);
			retVal = theCreateAccDlg.DoModal();
			if(retVal == IDOK)
			{
				(*io_ptbstrUserName) = (LPCTSTR)theCreateAccDlg.m_UserName;
				(*o_ptbstrPasswd) = theCreateAccDlg.m_tbstrPassword;
				retVal = S_OK;
			}
			else
			{
				retVal = E_USERCANCELLED;
			}
			
		}
		else
		{
			COpenProfDlg theOpenProfDlg;
			theOpenProfDlg.m_UserName = (CHAR*)(*io_ptbstrUserName);
			retVal = theOpenProfDlg.DoModal();
			if(retVal == IDOK)
			{
				(*io_ptbstrUserName) = (LPCTSTR)theOpenProfDlg.m_UserName;
				(*o_ptbstrPasswd) = theOpenProfDlg.m_tbstrPassword;
				retVal = S_OK;
			}
			else
			{
				retVal = E_USERCANCELLED;
			}
		}

		
		if(retVal != S_OK)
			break;

		
	}while(0);

	return retVal;

}
/////////////////////////////////////////////////////////////////////////////
// The one and only CVSAuthSmplApp object

CVSAuthSmplApp theApp;

extern "C" HRESULT EXPORT GetUsernamePasswd(VARIANT* i_pvarPurpose, VARIANT* i_pvarAppCtxt, VARIANT* i_pvarPasswdQuality,  VARIANT* io_pvarUserName, VARIANT* io_pvarPasswd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	HRESULT retVal = S_OK;
	_bstr_t tbstrUserName= "";
	_bstr_t tbstrPasswd = "";
	int nPasswdQuality = 0;

	do 
	{
		
		
		if(i_pvarPasswdQuality->vt == VT_I2)
			nPasswdQuality = i_pvarPasswdQuality->iVal;

		if(io_pvarUserName->vt == VT_BSTR && io_pvarUserName->bstrVal != NULL)
			tbstrUserName = io_pvarUserName->bstrVal;

		retVal = theApp.GetUsernamePasswd(i_pvarPurpose->iVal,i_pvarPasswdQuality->iVal,_bstr_t(i_pvarAppCtxt->bstrVal),
			&tbstrUserName,&tbstrPasswd);
		
		if(retVal != S_OK)
			break;
	
		if(io_pvarUserName->vt == VT_BSTR && io_pvarUserName->bstrVal)
			SysFreeString(io_pvarUserName->bstrVal);
		io_pvarUserName->vt = VT_BSTR;
		io_pvarUserName->bstrVal = SysAllocString(tbstrUserName);


		if(io_pvarPasswd->vt == VT_BSTR && io_pvarPasswd->bstrVal)
			SysFreeString(io_pvarUserName->bstrVal);
		io_pvarPasswd->vt = VT_BSTR;
		io_pvarPasswd->bstrVal = SysAllocString(tbstrPasswd);
	}while(0);


	return retVal;
}



extern "C" HRESULT EXPORT ProcessEvent(VARIANT* i_pvarEvent)
{
	int nEventID;
	HRESULT retVal = S_OK;

	nEventID = i_pvarEvent->iVal;
	switch(nEventID)
	{
	case (E_INVALIDPASSWD & 0x0000FFFF) :
		MessageBox(NULL,"The Username/PassFigure you have entered is invalid. Try again","Status",MB_OK|MB_ICONEXCLAMATION);
		break;

	case (E_PROFLOCKEDOUT & 0x0000FFFF) :
		MessageBox(NULL,"You have exceeded the maximum number of attampts. Your account has been locked out.","Status",MB_OK|MB_ICONEXCLAMATION);
		break;

	case OPEN_PROF_DOES_NOT_EXIST :
		MessageBox(NULL,"The Username/PassFigure you have entered is invalid. Try again.","Status",MB_OK|MB_ICONEXCLAMATION);
		break;

	case OPEN_PROF_CREATE:
		if(MessageBox(NULL,"This account does not exist. Would you like to create an account?","Status",MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
			retVal = E_USERCANCELLED;
		break;

	case CREATE_PROF_EXISTS:
		MessageBox(NULL,"This account exists already. Choose a different account name?","Status",MB_OK|MB_ICONEXCLAMATION); 
		break;

	case CREATE_PROF_DELETE :
		if(MessageBox(NULL,"This account exists already. Would you like to recreate it?","Status",MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
			retVal = E_USERCANCELLED;
		break;

	case CREATE_PROF_OPEN :
		if(MessageBox(NULL,"This account exists already. Would you like to open it?","Status",MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL)
			retVal = E_USERCANCELLED;
		break;

	default :
		break;
	}

	return retVal;
}