#ifndef _GLOBAL_INCL
#define _GLOBAL_INCL

#define DISABLE_SIGNCONFIRM_FOR_ALLAPPS 1
#define DISABLE_SIGNCONFIRM_FOR_THISAPP 2

#define ALWAYS_PROMPT_FOR_SIGN_KEY "AlwaysPromptForSign"
#define ALWAYS_PROMPT_FOR_SEL_KEY "AlwaysPromptForSel"
#define UIPREF_DLGTITLE_KEY "UIPref_DlgTitle"
#define UIPREF_DLGTEXT_KEY "UIPref_DlgText"
#define UIPREF_LOGOURL_KEY "UIPref_LogoUrl"
#define	UIPREF_HELP_URL_KEY "UIPref_HelpURL"
#define UIPREF_SHOWDEFCHKBOX_KEY "UIPref_ShowDefChkBox"
#define UIPREF_CHKBOXTEXT_KEY "UIPref_ChkBoxText"
#define UIPREF_ALWAYSPROMPTFORSIGN_KEY "UIPref_AlwaysPromptForSign"
#define UIPREF_ALWAYSPROMPTFORSEL_KEY "UIPref_AlwaysPromptForSel"
#define DEFCERT_STORENAME_KEY "DefCertStoreName"
#define DEFCERT_KEY "DefCert"

#define	UIPREF_BUTTON_TEXT "UIPref_ButtonText"

#define SRCHCRIT_ISSUERDN_KEY "SrchCrit_IssuerDN"
#define SRCHCRIT_SUBJECTDN_KEY "SrchCrit_SubjectDN"
#define SRCHCRIT_EXPDATE_KEY "SrchCrit_ExpDate"
#define SRCHCRIT_EFFDATE_KEY "SrchCrit_EffDate"
#define SRCHCRIT_DATEEQ_KEY "SrchCrit_DateEq"
#define SRCHCRIT_RENEWED_KEY "SrchCrit_Renewed"
#define SRCHCRIT_EXTOID_KEY "SrchCrit_ExtOID"
#define SRCHCRIT_EMAIL_KEY "SrchCrit_Email"
#define SRCHCRIT_STORENAME_KEY "SrchCrit_StoreName"
#define SRCHCRIT_SERNUM_KEY "SrchCrit_SerNum"

#define CERT_FRNDLYNAME_KEY "CertFrndlyName"
#define CERT_DISPSTRING_KEY "CertDispString"
#define CERT_LOGOURL_KEY "CertLogoUrl"
#define CERT_TEXTUREURL_KEY "CertTextureUrl"
#define CERT_RENEWED_KEY "CertRenewedKey"

#define CERT_BITMAPFILE_KEY "CertBitmapFile"

#define VS_INTER_SESSION 1
#define VS_INTRA_SESSION 2
#define VS_VOLATILE 3


#define VS_FOR_DEFAULT 1
#define VS_FOR_REGULAR 2

#define VS_SELECT	1
#define VS_DISPLAY	2


//#define VS_OK 0
#define VS_NO_STORE			0x80000001
#define VS_NO_DEFAULT		0x80000002
#define VS_DEFAULT_SELECTED 0x80000003
#define VS_NO_MATCHES		0x80000004
#define VS_NO_CERT_SEL		0x80000005
#define VS_CERT_SELECTED	0x80000006

#define VS_FRNDLYNAME_X 38
#define VS_FRNDLYNAME_Y 99

#define		STR_RENEWAL_STRING		L"52656E6577204469676974616C204944"

// Wasim : These are taken from the SumBank.htm file
#define EXP_DATE_GREATER_THAN	0x20
#define EXP_DATE_EQUALTO		0x10
#define EXP_DATE_LESS_THAN		0x08
#define EFF_DATE_GREATER_THAN	0x04
#define EFF_DATE_EQUALTO		0x02
#define EFF_DATE_LESS_THAN		0x01


#endif