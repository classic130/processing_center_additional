//Defines the core data structures required by the PTA

#ifndef _VS_PTA_CORE_DATASTRUCTS_
#define _VS_PTA_CORE_DATASTRUCTS_

#include <comdef.h>


typedef struct _SRCHCRIT
{
	_bstr_t tbstrIssuerDN;
	_bstr_t tbstrSubjectDN;
	_bstr_t tbstrEmail;
	_bstr_t tbstrSerNum;
	DATE dateExpDate;
	DATE dateEffDate;
	short nDateEquality;
	BOOL boolRenewed;
	short nKeyUsage;
	short nKeySize;
	_variant_t tvarExtOID;
	_variant_t tvarExtVal;
	BOOL boolUseDefault;
}SRCHCRIT, *PSRCHCRIT;

typedef struct _UIPREF
{
	WORD wLangID;
	_bstr_t	tbstrUILogoUrl;
	_bstr_t tbstrNewPasswd_Title;
	_bstr_t tbstrNewPasswd_Text;
	_bstr_t tbstrNewPasswdNoProf_Text;
	short nNewPasswd_OKBtnText;
	short nNewPasswd_CancelBtnText;
	_bstr_t tbstrNewPasswd_HelpUrl;
	_bstr_t tbstrLgnDlg_Title;
	_bstr_t tbstrOpenProf_Title;
	_bstr_t tbstrOpenProf_Text;
	short nOpenProf_OKBtnText;
	short nOpenProf_CancelBtnText;
	_bstr_t tbstrOpenProf_HelpUrl;
	_bstr_t tbstrSelID_Title;
	_bstr_t tbstrSelID_Text;
	short nSelID_OKBtnText;
	short nSelID_CancelBtnText;
	_bstr_t tbstrSelID_HelpUrl;
	BOOL boolSelID_ShowDefChkBox;
	_bstr_t tbstrSelID_ChkBoxText;
	_bstr_t tbstrSgnDlg_Title;
	_bstr_t tbstrCreateDlg_Title;
	_bstr_t tbstrIntroDlg_Title;
	_bstr_t tbstrIntroDlg_Text;
	_bstr_t tbstrIntroDlg_HelpUrl;
	_bstr_t tbstrRvwMsg_Title;
	_bstr_t tbstrRvwMsg_Text;
	short nRvwMsg_OKBtnText;
	short nRvwMsg_CancelBtnText;
	_bstr_t tbstrRvwMsg_HelpUrl;
	_bstr_t tbstrCreatePasswd_Title;
	_bstr_t tbstrCreatePasswd_Text;
	short nCreatePasswd_OKBtnText;
	short nCreatePasswd_CancelBtnText;
	_bstr_t tbstrEnterPasswd_Title;
	_bstr_t tbstrEnterPasswd_Text;
	short nEnterPasswd_OKBtnText;
	short nEnterPasswd_CancelBtnText;
	_bstr_t tbstrChangePasswd_Title;
	_bstr_t tbstrChangePasswd_Text;
	short nChangePasswd_OKBtnText;
	short nChangePasswd_CancelBtnText;
	_bstr_t tbstrChangePasswd_HelpUrl;
	_bstr_t tbstrTimeOut_Title;
	_bstr_t tbstrTimeOut_Text;
	short nTimeOut_OKBtnText;
	short nTimeOut_CancelBtnText;
	_bstr_t tbstrTimeOut_HelpUrl;
	_bstr_t tbstrImpDlg_Title;
	_bstr_t tbstrImpP12_Title;
	_bstr_t tbstrImpP12_Text;
	short nImpP12_OKBtnText;
	short nImpP12_CancelBtnText;
	_bstr_t tbstrImpP12_HelpUrl;
	_bstr_t tbstrExpDlg_Title;
	_bstr_t tbstrExpP12_Title;
	_bstr_t tbstrExpP12_Text;
	short nExpP12_OKBtnText;
	short nExpP12_CancelBtnText;
	_bstr_t tbstrExpP12_HelpUrl;
	_bstr_t tbstrTitleFont;
	_bstr_t tbstrTextFont;
	_bstr_t tbstrBtnFont;

//
//	Anand	Dec 15, 2000		Start
//
	_bstr_t tbstrSignNotificationUI;
	_bstr_t	tbstrDecryptNotificationUI;
//
//	Anand	Dec 15, 2000		End
//
	_bstr_t	tbstrAffLogoUrl;
	_bstr_t	tbstrExpProfileDlg_Title;
	_bstr_t	tbstrImpProfileDlg_Title;
	BOOL boolShowTopMost;

//  Sasi	May 1, 2003 Start
	
	// variables to store values for Get Profile dialog box elements
	_bstr_t tbstrGetSecretQuestion_Title;
	_bstr_t tbstrGetSecretQuestion_Text;
	short nGetSecretQuestion_OKBtnText;
	short nGetSecretQuestion_CancelBtnText;

	// variables to store values for Reset Password dialog box elements
	_bstr_t tbstrResetPasswd_Title;
	_bstr_t tbstrResetPasswd_Text;
	short nResetPasswd_OKBtnText;
	short nResetPasswd_CancelBtnText;

	// variables to store values for Create Secret dialog box elements
	_bstr_t tbstrCreateSecret_Title;
	_bstr_t tbstrCreateSecret_Text;
	short nCreateSecret_OKBtnText;
	short nCreateSecret_CancelBtnText;

//  Sasi	May 1, 2003 End

	// Wasim : Dialog size for the sign transaction dialog
	short nSignTransDlgWidth;
	short nSignTransDlgHeight;

} UIPREF, *PUIPREF;

typedef struct _CERTIDENTIFIER
{ 
	_bstr_t tbstrCertSerNum;
	_bstr_t tbstrCertIssDN;
} CERTIDENTIFIER, *PCERTIDENTIFIER;

typedef struct _CREATEPARAMS
{
	short	nPasswordQuality;
	short nPasswordLength;

	//These can also be changed after a profile has been opened
	short	nPasswordTimeOut; //Can be specified later
	short	nPasswordLockOutTries;
	short	nPasswordUnlockPeriod;
	VARIANT varReadOKDomains; //Can be specified later
	VARIANT varWriteOKDomains; //Can be specified later

}CREATEPARAMS, *PCREATEPARAMS;


typedef struct _OPENPROFPARAMS
{
	_bstr_t tbstrProfName;
	_bstr_t tbstrPassword;
	_bstr_t tbstrConfirmPassword;
	short nPasswordUsageFlag;
	int		nFlag; //Operation flag
	BOOL	boolRoamProfile;
	BOOL	boolSaveLocal;
	BOOL boolIsUsernameEditable;
	BOOL boolSupportResetPasswd; // flag to indicate whether the roaming server supports password reset or not
	
		// Sasi 06/05/03
		// Used to store first name, last name and e-mail address of the user. This information is passed to the roaming server during the profile creation
	_bstr_t tbstrFirstName;
	_bstr_t tbstrLastName;
	_bstr_t tbstrEmail;

	//Create params
	CREATEPARAMS theCreateParams;

} OPENPROFPARAMS, *POPENPROFPARAMS;

typedef struct _SIGNMSGPARAMS
{
	int nMsgToSignSize;
	PBYTE pbyteMsgToSign;
	int nAlgId;
	BOOL boolAddAuthAttr;

	//	Wasim	Oct 29,	2001		
	DATE	dateSignDate;		// the date-time to be put in the authenticated attributes while signing

	// Sasi 06/23/03
	// Stores UTF-8 encoded message to be signed
	int nUTF8MsgToSignSize;
	PBYTE pbyteUTF8MsgToSign;
	BOOL boolUTF8EncodeMsgToSign;  // indicates whether the message needs to be UTF-8 encoded before it is signed

} SIGNMSGPARAMS, *PSIGNMSGPARAMS;

//
//	Anand	Dec 15, 2000		Start
//
typedef struct _DECRYPTMSGPARAMS
{
	int nMsgToDecryptSize;
	PBYTE pbyteMsgToDecrypt;
} DECRYPTMSGPARAMS, *PDECRYPTMSGPARAMS;
//
//	Anand	Dec 15, 2000		End
//

typedef struct _CREATECERTREQPARAMS
{
	_bstr_t tbstrSubjectDN;
	DWORD dwKeyGenFlags;
	int nHashAlg;
	int nNumOfAttributes;
	_bstr_t* ptbstrAttrOIDs;
	_bstr_t* ptbstrAttrVals;
	// Modified by - Infosys Technologies Ltd. 
	// Change Request - CR#21529
	// Description - Declare an additional element in the CREATECERTPARAMS structure 
	// to store the value of PrivateKeyExportableFlag flag.
	// CR#21529 - Begin
	// Date Modified - July 5, 2004
	BOOL bIsPrivateKeyExportable;
	// CR#21529 - End

} CREATECERTREQPARAMS, *PCREATECERTREQPARAMS;

typedef struct _INSTALLCERTPARAMS
{
	_bstr_t tbstrCertToInstall;
	_bstr_t tbstrKeyToImport;
	DWORD dwKeyGenFlags;
	BOOL boolAlsoImportKey;
} INSTALLCERTPARAMS, *PINSTALLCERTPARAMS;

typedef struct _SETCERTPREFPARAMS
{
	_bstr_t tbstrPrefName;
	_bstr_t tbstrPrefVal;
} SETCERTPREFPARAMS,*PSETCERTPREFPARAMS;

typedef struct _SELIDPARAMS
{
	bool boolUseDefCert;
	bool boolMarkAsDefault;
}SELIDPARAMS, *PSELIDPARAMS;

typedef struct _ROAMPARAMS
{
	int nNumOfRoamingSrvrs;
	_bstr_t tbstrStorageSrvr;
	_bstr_t* ptbstrRoamingSrvrs;
	_bstr_t tbstrClientInfo;
	_bstr_t tbstrClientInfoSig;
	bool boolRoamInfoChanged;
	bool boolRoamingResetFeature;
}ROAMPARAMS, *PROAMPARAMS;

typedef struct _CREATEPASSWDPARAMS 
{
	BOOL boolUseNewPasswd;
	_bstr_t tbstrNewPasswd;
	_bstr_t tbstrConfPasswd;
}CREATEPASSWDPARAMS, *PCREATEPASSWDPARAMS;

typedef struct _ENTERPASSWDPARAMS 
{
	BOOL boolUseNewPasswd;
	_bstr_t tbstrThePasswd;
}ENTERPASSWDPARAMS, *PENTERPASSWDPARAMS;

typedef struct _CHANGEPASSWDPARAMS 
{
	BOOL boolUseOldPasswd;
	_bstr_t tbstrOldPasswd;
	BOOL boolUseNewPasswd;
	_bstr_t tbstrNewPasswd;
	_bstr_t tbstrConfPasswd;
}CHANGEPASSWDPARAMS, *PCHANGEPASSWDPARAMS;

typedef struct _IMPORTP12PARAMS 
{
	int		nKeyFileOrBlob;
	_bstr_t tbstrKeyFileOrBlob;
	_bstr_t tbstrP12Passwd;
	_bstr_t tbstrSerNum;
	_bstr_t tbstrIssDN;
}IMPORTP12PARAMS, *PIMPORTP12PARAMS;

typedef struct _EXPORTP12PARAMS 
{
	int		nKeyFileOrBlob;
	_bstr_t tbstrKeyFileOrBlob;
	_bstr_t tbstrP12Passwd;
	_bstr_t tbstrP12ConfPasswd;
	int nPasswordQuality;
	int nPasswordLength;
	BOOL boolUsePasswd;
	BOOL boolShowFileName;
}EXPORTP12PARAMS, *PEXPORTP12PARAMS;

typedef struct _EXPORTPROFILEPARAMS
{
	int		nExportProfileFlags;
	PBYTE	pbProfilePasswd;
	int		nProfilePasswd;
	_bstr_t tbstrProfileData;
}EXPORTPROFILEPARAMS, *PEXPORTPROFILEPARAMS;

typedef struct _IMPORTPROFILEPARAMS
{
	PBYTE	pbProfilePasswd;
	int		nProfilePasswd;
	_bstr_t tbstrProfileData;
}IMPORTPROFILEPARAMS, *PIMPORTPROFILEPARAMS;

	// structure to store parameters used in GetSecretQuestion dialog
typedef struct _GETSECRETQUESTIONPARAMS
{
	_bstr_t tbstrProfName;
	_bstr_t tbstrSecretQuestion;
} GETSECRETQUESTIONPARAMS, *PGETSECRETQUESTIONPARAMS;

	// structure to store parameters used in ResetPassword dialog
typedef struct _RESETPASSWDPARAMS 
{
	_bstr_t tbstrProfName;
	_bstr_t tbstrSecretQuestion;
	_bstr_t tbstrSecretAnswer;
	BOOL boolUseNewPasswd;
	_bstr_t tbstrNewPasswd;
	_bstr_t tbstrConfPasswd;
}RESETPASSWDPARAMS, *PRESETPASSWDPARAMS;

	// structure to store parameters used in CreateSecret dialog
typedef struct _CREATESECRETPARAMS
{
	CVirtualSmartCard* pVirtualSmartCard;
	_bstr_t tbstrProfName;
	_bstr_t tbstrSecretQuestion;
	_bstr_t tbstrSecretAnswer;
} CREATESECRETPARAMS, *PCREATESECRETPARAMS;

typedef struct _APPCTXT
{
	_bstr_t tbstrAppCtxtName;
	_bstr_t tbstrHostName;
	_bstr_t tbstrProtocolName;
	_bstr_t	tbstrCSPName;
	_bstr_t tbstrAuthDll;
	HMODULE hModAuthDll;
	_bstr_t tbstrProfileIssFrndlyName;
	_bstr_t tbstrProfileIssUniqueId;
	short nIsCapi;
	DWORD	dwIsTPM;
	BOOL boolIsAttached;
	BOOL boolShowUI;
	UIPREF theUIPrefs;
	UIPREF theDefUIPrefs;
	SRCHCRIT theSrchCrit;
	CERTIDENTIFIER theCertIdentifier;
	OPENPROFPARAMS theOpenProfParams;
	SELIDPARAMS theSelIdParams;
	SIGNMSGPARAMS theSignMsgParams;
	CREATECERTREQPARAMS theCreateCertReqParams;
	INSTALLCERTPARAMS theInstallCertParams;
	SETCERTPREFPARAMS theCertPrefParams;
	ROAMPARAMS theRoamingParams;
	CREATEPASSWDPARAMS theCreatePasswdParams;
	ENTERPASSWDPARAMS theEnterPasswdParams;
	CHANGEPASSWDPARAMS theChangePasswdParams;
	IMPORTP12PARAMS theImportP12Params;
	EXPORTP12PARAMS theExportP12Params;
	EXPORTPROFILEPARAMS theExportProfileParams;
	IMPORTPROFILEPARAMS theImportProfileParams;

//
//	Sasi	May 01, 2003		Start
//
	GETSECRETQUESTIONPARAMS theGetSecretQuestionParams;
	RESETPASSWDPARAMS theResetPasswdParams;
	CREATESECRETPARAMS theCreateSecretParams;
//
//	Sasi	May 01, 2003		End
//

//
//	Anand	Dec 13, 2000		Start
//
	BOOL	boolHashData;
	BOOL	boolP7Output;
	BOOL	boolSignNotificationUI;
	DWORD	dwDecryptUI;

	DECRYPTMSGPARAMS theDecryptMsgParams;
//
//	Anand	Dec 13, 2000		End
//

//
//	Sameer	Oct 25, 2001		Start
//
	BOOL	boolShowSelIDUI;
//
//	Sameer	Oct 25, 2001		End
//


//	Wasim	Apr 19, 2002
	BOOL	boolCapiCert;				// To enable/disable dumping of certs in the CAPI store while
										// installing cert or opening a profile

} APPCTXT, *PAPPCTXT;

#endif