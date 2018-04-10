#ifndef _VS_PTA_UI_DATASTRUCTS_
#define _VS_PTA_UI_DATASTRUCTS_

#include "certstructs.h"
#include "virtualsmartcard.h"

//Forward declaration
typedef struct _OPCTXT* POPCTXT;
typedef struct _UICTXT* PUICTXT;

typedef HRESULT (*LPFNBtnFn) (POPCTXT pOpCtxt);


typedef struct _OPARAMS
{
	CVirtualSmartCard* pVirtualSmartCard;
	PIDLISTNODE pSelectedId;
	_bstr_t tbstrSignature;
	_bstr_t tbstrCertReq;
	_bstr_t tbstrCertPref;
	_bstr_t tbstrTimeOutPasswd;

} OPARAMS, *POPARAMS;

typedef struct _OPCTXT
{
	int nWizardAndUIs;	  //contains a bit field indicating the wizard and UIs to show.
	POPARAMS pOParams;
	int nNumOfProfiles;
	_bstr_t* ptbstrProfiles;
	PIDLISTNODE pCertListHead;
	int nSelectedIdNum;
	BOOL boolFromUI;
	BOOL boolSignMsgSeen;
	BOOL boolIntroSeen;
	_bstr_t tbstrSmartCardName;
	PBYTE pbytePublicKeyId;
	PBYTE pbytePrivKeyBlob;
	DWORD dwPrivKeyBlobSize;
	DWORD dwPublicKeyIdSize;
	DWORD dwKeyType;
	BOOL boolOpenedWithPassword;
	void* pvThePtaObj;
	void* pvThePTAUIObj;
} OPCTXT, *POPCTXT;


//This structure contains the fonts to be used
typedef struct _FONTSINFO
{
	DWORD dwCharset;
  	_bstr_t tbstrTitleFont;
  	_bstr_t tbstrTextFont;
	_bstr_t tbstrBtnFont;
} FONTSINFO, *PFONTSINFO;

//This function contains the text of the buttons
typedef struct _BTNFNS
{
	LPFNBtnFn lpfnBtn1Fn;
	LPFNBtnFn lpfnBtn2Fn;
	LPFNBtnFn lpfnBtn3Fn;
} BTNFNS, *PBTNFNS;

//This function contains the text of the buttons
typedef struct _BTNELEMS
{
	_bstr_t tbstrBtn1Text;
	_bstr_t tbstrBtn2Text;
	_bstr_t tbstrBtn3Text;
} BTNELEMS, *PBTNELEMS;


//This structure contains the UI Context. The UI Context provides
//information about the state in which the UI should be in, information
//required to render the UI for that state and the functions it needs
//to call when the buttons are clicked.
typedef struct _UICTXT
{
	void* pvReserved; //pointer to the CVSPTA Object

	PFONTSINFO pfontInfoCustomFonts;
	PFONTSINFO pfontInfoDefaultFonts;

	PBTNFNS pbtnFns;
	PBTNELEMS pbtnElems;
	
	_bstr_t tbstrDefLogoUrl;
	_bstr_t tbstrCustLogoUrl;
	_bstr_t tbstrDefAffLogoUrl;
	_bstr_t tbstrCustAffLogoUrl;

	int nWhichWizardAndUI;
	int nDefLangId;

	void* pvWizardElems;
	void* pvUIElements; // where the WebBrowser2 is stored.

	BOOL bShowTopMost;
	
} UICTXT, *PUICTXT;


typedef struct _WIZARDELEMENTS
{
	_bstr_t tbstrWizTitle;
}WIZARDELEMENTS, *PWIZARDELEMENTS;


//This structure contains the elements of the
//login wizard
typedef struct _ALLWIZARDELEMENTS
{
	WIZARDELEMENTS theDefWizardElems;
	WIZARDELEMENTS theCustWizardElems;
}ALLWIZARDELEMENTS, *PALLWIZARDELEMENTS;

typedef ALLWIZARDELEMENTS ALL_LOGIN_WIZARDELEMENTS ;
typedef PALLWIZARDELEMENTS PALL_LOGIN_WIZARDELEMENTS ;
typedef ALLWIZARDELEMENTS ALL_SIGN_WIZARDELEMENTS ;
typedef PALLWIZARDELEMENTS PALL_SIGN_WIZARDELEMENTS ;
typedef ALLWIZARDELEMENTS ALL_CREATE_WIZARDELEMENTS;
typedef PALLWIZARDELEMENTS PALL_CREATE_WIZARDELEMENTS;
typedef ALLWIZARDELEMENTS ALL_IMPORT_WIZARDELEMENTS;
typedef PALLWIZARDELEMENTS PALL_IMPORT_WIZARDELEMENTS;
typedef PALLWIZARDELEMENTS PALL_EXPORT_WIZARDELEMENTS;
typedef PALLWIZARDELEMENTS PALL_EXPORTPROFILE_WIZARDELEMENTS;
typedef PALLWIZARDELEMENTS PALL_IMPORTPROFILE_WIZARDELEMENTS;

//This structure contains the information required to render the 
//create profile dialog box.
typedef struct _CREATEPROF_UIELEMENTS
{
}CREATEPROF_UIELEMENTS, *PCREATEPROF_UIELEMENTS;

//This structure contains the information required to render the 
//open profile dialog box.
typedef struct _UIELEMENTS
{
	_bstr_t tbstrTitle;
	_bstr_t tbstrText;
}UIELEMENTS, *PUIELEMENTS;

typedef UIELEMENTS OPENPROF_UIELEMENTS;
typedef PUIELEMENTS POPENPROF_UIELEMENTS;

typedef struct _ALL_OPENPROF_UIELEMENTS
{
	_bstr_t tbstrProfName;
	_bstr_t* ptbstrProfList;
	int nNumOfProfiles;
	_bstr_t tbstrPassword;
	_bstr_t tbstrConfirmPassword;
	BOOL boolShowPassword;
	_bstr_t tbstrPasswordQuality;
	BOOL boolIsUsernameEditable;
	OPENPROF_UIELEMENTS theDefUIElements;
	OPENPROF_UIELEMENTS theCustUIElements;
}ALL_OPENPROF_UIELEMENTS, *PALL_OPENPROF_UIELEMENTS ;

//This structure contains the information required to render the 
//select id dialog box.
typedef struct _SELID_UIELEMENTS
{
	_bstr_t tbstrTitle;
	_bstr_t	tbstrText;
	_bstr_t tbstrChkBoxText;
}SELID_UIELEMENTS, PSELID_UIELEMENTS;

typedef struct _ALL_SELID_UIELEMENTS
{
	PIDLISTNODE pCertListHead;
	int nDefaultIDFromList;
	BOOL boolShowChkBox;
	unsigned int nChkBoxState;
	SELID_UIELEMENTS theDefUIElements;
	SELID_UIELEMENTS theCustUIElements;
	int nSelectedIDFromList;
}ALL_SELID_UIELEMENTS, *PALL_SELID_UIELEMENTS;

typedef UIELEMENTS REVWMSG_UIELEMENTS;
typedef PUIELEMENTS PREVWMSG_UIELEMENTS;

typedef struct _ALL_REVWMSG_UIELEMENTS
{
	_bstr_t tbstrMsgToSign;
	REVWMSG_UIELEMENTS theDefUIElements;
	REVWMSG_UIELEMENTS theCustUIElements;
	CComPtr<IWebBrowser2> pWebBrowser; // RYAN

	// Wasim : Dialog size for the sign transaction dialog
	short nSignTransDlgWidth;
	short nSignTransDlgHeight;

}ALL_REVWMSG_UIELEMENTS, *PALL_REVWMSG_UIELEMENTS;

typedef UIELEMENTS INTRODLG_UIELEMENTS;
typedef PUIELEMENTS PINTRODLG_UIELEMENTS;

typedef struct _ALL_INTRODLG_UIELEMENTS
{
	INTRODLG_UIELEMENTS theDefUIElements;
	INTRODLG_UIELEMENTS theCustUIElements;
}ALL_INTRODLG_UIELEMENTS, *PALL_INTRODLG_UIELEMENTS;

typedef UIELEMENTS CREATEPASSWD_UIELEMENTS;
typedef PUIELEMENTS PCREATEPASSWD_UIELEMENTS;

typedef struct _ALL_CREATEPASSWD_UIELEMENTS
{
	_bstr_t tbstrNewPassword;
	_bstr_t tbstrConfirmPassword;
	BOOL boolShowNewPassword;
	// XXX _bstr_t tbstrPasswordQuality;
	CREATEPASSWD_UIELEMENTS theDefUIElements;
	CREATEPASSWD_UIELEMENTS theCustUIElements;
}ALL_CREATEPASSWD_UIELEMENTS, *PALL_CREATEPASSWD_UIELEMENTS ;

typedef UIELEMENTS ENTERPASSWD_UIELEMENTS;
typedef PUIELEMENTS PENTERPASSWD_UIELEMENTS;

typedef struct _ALL_ENTERPASSWD_UIELEMENTS
{
	_bstr_t tbstrThePassword;
	BOOL boolShowNewPassword;
	// XXX _bstr_t tbstrPasswordQuality;
	CREATEPASSWD_UIELEMENTS theDefUIElements;
	CREATEPASSWD_UIELEMENTS theCustUIElements;
}ALL_ENTERPASSWD_UIELEMENTS, *PALL_ENTERPASSWD_UIELEMENTS ;

typedef UIELEMENTS CHANGEPASSWD_UIELEMENTS;
typedef PUIELEMENTS PCHANGEPASSWD_UIELEMENTS;

typedef struct _ALL_CHANGEPASSWD_UIELEMENTS
{
	_bstr_t tbstrNewPassword;
	_bstr_t tbstrOldPassword;
	_bstr_t tbstrConfirmPassword;
	BOOL boolShowNewPassword;
	BOOL boolShowOldPassword;
	_bstr_t tbstrPasswordQuality;
	CHANGEPASSWD_UIELEMENTS theDefUIElements;
	CHANGEPASSWD_UIELEMENTS theCustUIElements;
}ALL_CHANGEPASSWD_UIELEMENTS, *PALL_CHANGEPASSWD_UIELEMENTS ;

typedef UIELEMENTS IMPORTP12_UIELEMENTS;
typedef PUIELEMENTS PIMPORTP12_UIELEMENTS;

typedef struct _ALL_IMPORTP12_UIELEMENTS
{
	_bstr_t tbstrP12Passwd;
	IMPORTP12_UIELEMENTS theDefUIElements;
	IMPORTP12_UIELEMENTS theCustUIElements;
}ALL_IMPORTP12_UIELEMENTS, *PALL_IMPORTP12_UIELEMENTS;

typedef UIELEMENTS EXPORTP12_UIELEMENTS;
typedef PUIELEMENTS PEXPORTP12_UIELEMENTS;

typedef struct _ALL_EXPORTP12_UIELEMENTS
{
	_bstr_t tbstrP12Passwd;
	_bstr_t tbstrP12ConfPasswd;
	_bstr_t tbstrPasswordQuality;
	BOOL boolShowPassword;
	_bstr_t tbstrKeyFile;
	BOOL boolShowFileName;
	EXPORTP12_UIELEMENTS theDefUIElements;
	EXPORTP12_UIELEMENTS theCustUIElements;
}ALL_EXPORTP12_UIELEMENTS, *PALL_EXPORTP12_UIELEMENTS;


typedef UIELEMENTS GETSECRETQUESTION_UIELEMENTS;
typedef PUIELEMENTS PGETSECRETQUESTION_UIELEMENTS;

// Sasi 05/02/2003
//This structure contains the information required to render the 
//get secret question dialog box.
typedef struct _ALL_GETSECRETQUESTION_UIELEMENTS
{
	_bstr_t tbstrProfName;
	GETSECRETQUESTION_UIELEMENTS theDefUIElements;
	GETSECRETQUESTION_UIELEMENTS theCustUIElements;
}ALL_GETSECRETQUESTION_UIELEMENTS, *PALL_GETSECRETQUESTION_UIELEMENTS ;

typedef UIELEMENTS RESETPASSWD_UIELEMENTS;
typedef PUIELEMENTS PRESETPASSWD_UIELEMENTS;

// Sasi 05/02/2003
//This structure contains the information required to render the 
//reset password dialog box.
typedef struct _ALL_RESETPASSWD_UIELEMENTS
{
	_bstr_t tbstrProfName;
	_bstr_t tbstrSecretQuestion;
	_bstr_t tbstrSecretAnswer;
	_bstr_t tbstrNewPassword;
	_bstr_t tbstrConfirmPassword;
	BOOL boolShowNewPassword;
	_bstr_t tbstrPasswordQuality;
	RESETPASSWD_UIELEMENTS theDefUIElements;
	RESETPASSWD_UIELEMENTS theCustUIElements;
}ALL_RESETPASSWD_UIELEMENTS, *PALL_RESETPASSWD_UIELEMENTS ;

typedef UIELEMENTS CREATESECRET_UIELEMENTS;
typedef PUIELEMENTS PCREATESECRET_UIELEMENTS;

// Sasi 05/02/2003
//This structure contains the information required to render the 
//create secret dialog box.
typedef struct _ALL_CREATESECRET_UIELEMENTS
{
	_bstr_t tbstrProfName;
	_bstr_t tbstrSecretQuestion;
	_bstr_t tbstrSecretAnswer;
	CREATESECRET_UIELEMENTS theDefUIElements;
	CREATESECRET_UIELEMENTS theCustUIElements;
}ALL_CREATESECRET_UIELEMENTS, *PALL_CREATESECRET_UIELEMENTS ;

#endif