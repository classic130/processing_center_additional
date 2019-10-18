// VSAuthSmpl.cpp : Defines the initialization routines for the DLL.
//


#include "vsprsauth.h"
#include "vspmutil.h"
#include <process.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define DEBUGLINE			" --VSPRSAuth.DLL---> "
// Constants 
#define PTACONTAINER		"PTAv2"
#define PTAAPPNAME			"ptaAppName"
#define	SGMSPRSCONTAINER	"SGMSPRS"
#define	PTAPASSWORD			"ptaPassword"
#define	PTAFILE				"ptaUserName"
#define PTAPATH				"profilePath" 


//Use policy module API to get the password.
HRESULT GetPTAPasswordFromPolicyFile(_bstr_t & tbstrPasswd, _bstr_t &tbstrUserName)
{
	HRESULT rc = S_OK;
	
	static bool bFirstTime = true; 	
	
	if ( bFirstTime == false )
	{
		// if we come back here a second time that means the authentication failed and we 
		// have a problem. the only way to handle this right now is to return a user cancelled
		// op to the pta
		return E_USERCANCELLED;
	}
	else
	{
		bFirstTime = false;
	}


	// Use Policy Module API to get the policy contents.
	VSPM_STATUS status;
	VSPM_Descriptor pmd = (VSPM_Descriptor) NULL;
	VSPM_Container ptaContainer = (VSPM_Container) NULL;
	VSPM_Container sgmsprsContainer = (VSPM_Container) NULL;
	VSPM_Item pmItem = (VSPM_Item) NULL;
 
	do {
		
		// 1.  Open the policy file.
		if ((pmd=VSPM_Open("sgmsprs.policy", &status)) == NULL) {
			rc = (HRESULT)status;
			break;
		}

//		printf("%sPolicy opened\n", DEBUGLINE);

		
		// 2. Get the SGMSPRS Container index by name
		if ((sgmsprsContainer = VSPM_GetContainerByNameFromDescriptor(
			pmd, SGMSPRSCONTAINER, &status)) == NULL) {
			rc = (HRESULT) status;
			break;
		}

//		printf("%sGot PTA & SGMS containers.\n", DEBUGLINE);


		// 3. Get PTA password 
		if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, PTAPASSWORD, &status )) == NULL) {
			rc = (HRESULT) status;
			break;
		}
		tbstrPasswd = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status);

		// 4. Get PTA profile 
	/*	if ((pmItem = VSPM_GetItemByName (
			sgmsprsContainer, PTAFILE, &status )) == NULL) {
			rc = (HRESULT) status;
			break;
		}
		tbstrUserName = (const char*)VSPM_GetValue(pmItem, &status);
		// need to re-use this pmItem. Free it now.
		VSPM_FreeItem(pmItem, &status); */

		
		// construct the pid using the profile name 
		 int pid = _getpid();
		 char pidbuf[15];
		 tbstrUserName = _itoa(pid,pidbuf,10);


	} while (0);
	if (ptaContainer != NULL) VSPM_FreeContainer(ptaContainer, &status);
	if (sgmsprsContainer != NULL) VSPM_FreeContainer(sgmsprsContainer, &status);
	if (pmd != NULL) VSPM_Close(pmd);
	

	return rc;
}


//extern "C" HRESULT EXPORT GetUsernamePasswd(VARIANT* i_pvarPurpose, VARIANT* i_pvarAppCtxt, VARIANT* i_pvarPasswdQuality,  VARIANT* io_pvarUserName, VARIANT* io_pvarPasswd)
extern "C" HRESULT GetUsernamePasswd(VARIANT* i_pvarPurpose, VARIANT* i_pvarAppCtxt, VARIANT* i_pvarPasswdQuality,  VARIANT* io_pvarUserName, VARIANT* io_pvarPasswd)
{
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	HRESULT retVal = S_OK;
	_bstr_t tbstrPasswd = "";
	_bstr_t tbstrUserName = "";
	
	do 
	{
		
		if(io_pvarPasswd->vt == VT_BSTR && io_pvarPasswd->bstrVal)
			SysFreeString(io_pvarPasswd->bstrVal);

		if(io_pvarUserName->vt == VT_BSTR && io_pvarUserName->bstrVal)
			SysFreeString(io_pvarUserName->bstrVal);

		retVal = GetPTAPasswordFromPolicyFile(tbstrPasswd, tbstrUserName);
		if(retVal != S_OK)
			break;

		io_pvarPasswd->vt = VT_BSTR;
		io_pvarPasswd->bstrVal = SysAllocString(tbstrPasswd);

		io_pvarUserName->vt = VT_BSTR;
		io_pvarUserName->bstrVal = SysAllocString(tbstrUserName);
		
	}while(0);


	return retVal;
}



//extern "C" HRESULT EXPORT ProcessEvent(VARIANT* i_pvarEvent)
extern "C" HRESULT ProcessEvent(VARIANT* i_pvarEvent)
{
	// we cant do anything here for now so just return an S_OK for now.
	return S_OK;
}