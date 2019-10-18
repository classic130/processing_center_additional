/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM n6pta.idl
 */

#ifndef __gen_n6pta_h__
#define __gen_n6pta_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    ns6IPTA */
#define NS_6IPTA_IID_STR "312da841-3dbf-11d3-bcfb-00a0c9c8d91e"

#define NS_6IPTA_IID \
  {0x312da841, 0x3dbf, 0x11d3, \
    { 0xbc, 0xfb, 0x00, 0xa0, 0xc9, 0xc8, 0xd9, 0x1e }}

class NS_NO_VTABLE ns6IPTA : public nsISupports {
 public: 

  NS_DEFINE_STATIC_IID_ACCESSOR(NS_6IPTA_IID)

  /************************** PTA v2 Properties **************************/
/******************** PTA longerface ********************/
  /* long PTA_Initialize (in wstring AppCtxtName, in long UseCapi); */
  NS_IMETHOD PTA_Initialize(const PRUnichar *AppCtxtName, PRInt32 UseCapi, PRInt32 *_retval) = 0;

  /* long PTA_Close (); */
  NS_IMETHOD PTA_Close(PRInt32 *_retval) = 0;

  /* long set_PTA_AppPreference (in wstring PrefName, in wstring Value); */
  NS_IMETHOD Set_PTA_AppPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval) = 0;

  /* wstring get_PTA_AppPreference (in wstring PrefName); */
  NS_IMETHOD Get_PTA_AppPreference(const PRUnichar *PrefName, PRUnichar **_retval) = 0;

  /* long set_PTA_CSPName (in wstring CSPName); */
  NS_IMETHOD Set_PTA_CSPName(const PRUnichar *CSPName, PRInt32 *_retval) = 0;

  /* wstring get_PTA_CSPName (); */
  NS_IMETHOD Get_PTA_CSPName(PRUnichar **_retval) = 0;

  /* wstring PTA_CreateCertReq (in wstring SubjectDN, in long KeyGenFlag, in long HashAlg, in unsigned long count, [array, size_is (count)] in wstring Attribs); */
  NS_IMETHOD PTA_CreateCertReq(const PRUnichar *SubjectDN, PRInt32 KeyGenFlag, PRInt32 HashAlg, PRUint32 count, const PRUnichar **Attribs, PRUnichar **_retval) = 0;

  /* long PTA_InstallCert (in wstring Cert); */
  NS_IMETHOD PTA_InstallCert(const PRUnichar *Cert, PRInt32 *_retval) = 0;

  /* long PTA_InstallKeyPair (in wstring privKeyBlob, in wstring pkcs7Cert); */
  NS_IMETHOD PTA_InstallKeyPair(const PRUnichar *privKeyBlob, const PRUnichar *pkcs7Cert, PRInt32 *_retval) = 0;

  /* wstring PTA_SignChallenge (in wstring Challenge, in long AlgID); */
  NS_IMETHOD PTA_SignChallenge(const PRUnichar *Challenge, PRInt32 AlgID, PRUnichar **_retval) = 0;

  /* wstring PTA_SignTransaction (in wstring Message, in long AlgID); */
  NS_IMETHOD PTA_SignTransaction(const PRUnichar *Message, PRInt32 AlgID, PRUnichar **_retval) = 0;

  /* wstring PTA_SignRenewal (in long AlgID); */
  NS_IMETHOD PTA_SignRenewal(PRInt32 AlgID, PRUnichar **_retval) = 0;

  /* long PTA_SelectIDForTrans (); */
  NS_IMETHOD PTA_SelectIDForTrans(PRInt32 *_retval) = 0;

  /* long PTA_SelectIDForChallenge (); */
  NS_IMETHOD PTA_SelectIDForChallenge(PRInt32 *_retval) = 0;

  /* short get_PTA_UseDefCertFlag (); */
  NS_IMETHOD Get_PTA_UseDefCertFlag(PRInt16 *_retval) = 0;

  /* long set_PTA_UseDefCertFlag (in short defCertFlag); */
  NS_IMETHOD Set_PTA_UseDefCertFlag(PRInt16 defCertFlag, PRInt32 *_retval) = 0;

  /* long set_PTA_ProtocolName (in wstring protocolName); */
  NS_IMETHOD Set_PTA_ProtocolName(const PRUnichar *protocolName, PRInt32 *_retval) = 0;

  /* wstring get_PTA_ProtocolName (); */
  NS_IMETHOD Get_PTA_ProtocolName(PRUnichar **_retval) = 0;

  /* long set_PTA_AuthDll (in wstring authDllName); */
  NS_IMETHOD Set_PTA_AuthDll(const PRUnichar *authDllName, PRInt32 *_retval) = 0;

  /* wstring get_PTA_AuthDll (); */
  NS_IMETHOD Get_PTA_AuthDll(PRUnichar **_retval) = 0;

  /* long set_PTA_ProfileIssFrndlyName (in wstring profileIssFrndlyName); */
  NS_IMETHOD Set_PTA_ProfileIssFrndlyName(const PRUnichar *profileIssFrndlyName, PRInt32 *_retval) = 0;

  /* wstring get_PTA_ProfileIssFrndlyName (); */
  NS_IMETHOD Get_PTA_ProfileIssFrndlyName(PRUnichar **_retval) = 0;

  /* long set_PTA_ProfileIssUniqueId (in wstring profileIssUniqId); */
  NS_IMETHOD Set_PTA_ProfileIssUniqueId(const PRUnichar *profileIssUniqId, PRInt32 *_retval) = 0;

  /* wstring get_PTA_ProfileIssUniqueId (); */
  NS_IMETHOD Get_PTA_ProfileIssUniqueId(PRUnichar **_retval) = 0;

  /* long set_PTA_AffLogoUrl (in wstring affLogoUrl); */
  NS_IMETHOD Set_PTA_AffLogoUrl(const PRUnichar *affLogoUrl, PRInt32 *_retval) = 0;

  /* wstring get_PTA_AffLogoUrl (); */
  NS_IMETHOD Get_PTA_AffLogoUrl(PRUnichar **_retval) = 0;

  /* long set_PTA_EnableCertForCapi (in boolean boolEnableForCapi); */
  NS_IMETHOD Set_PTA_EnableCertForCapi(PRBool boolEnableForCapi, PRInt32 *_retval) = 0;

  /******************** CertPref longerface ********************/
  /* long set_CertPref_CertSerNum (in wstring CertSerNum); */
  NS_IMETHOD Set_CertPref_CertSerNum(const PRUnichar *CertSerNum, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertSerNum (); */
  NS_IMETHOD Get_CertPref_CertSerNum(PRUnichar **_retval) = 0;

  /* long set_CertPref_CertIssDN (in wstring CertIssDN); */
  NS_IMETHOD Set_CertPref_CertIssDN(const PRUnichar *CertIssDN, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertIssDN (); */
  NS_IMETHOD Get_CertPref_CertIssDN(PRUnichar **_retval) = 0;

  /* long set_CertPref_CertFrndlyName (in wstring CertFrndlyName); */
  NS_IMETHOD Set_CertPref_CertFrndlyName(const PRUnichar *CertFrndlyName, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertFrndlyName (); */
  NS_IMETHOD Get_CertPref_CertFrndlyName(PRUnichar **_retval) = 0;

  /* long set_CertPref_CertLogoUrl (in wstring CertLogoUrl); */
  NS_IMETHOD Set_CertPref_CertLogoUrl(const PRUnichar *CertLogoUrl, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertLogoUrl (); */
  NS_IMETHOD Get_CertPref_CertLogoUrl(PRUnichar **_retval) = 0;

  /* long set_CertPref_CertDispString (in wstring CertDispString); */
  NS_IMETHOD Set_CertPref_CertDispString(const PRUnichar *CertDispString, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertDispString (); */
  NS_IMETHOD Get_CertPref_CertDispString(PRUnichar **_retval) = 0;

  /* long set_CertPref_CertTextureUrl (in wstring CertTextureUrl); */
  NS_IMETHOD Set_CertPref_CertTextureUrl(const PRUnichar *CertTextureUrl, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_CertTextureUrl (); */
  NS_IMETHOD Get_CertPref_CertTextureUrl(PRUnichar **_retval) = 0;

  /* long set_CertPref_MarkAsRenewed (in boolean boolMarkAsRenewed); */
  NS_IMETHOD Set_CertPref_MarkAsRenewed(PRBool boolMarkAsRenewed, PRInt32 *_retval) = 0;

  /* boolean get_CertPref_MarkAsRenewed (); */
  NS_IMETHOD Get_CertPref_MarkAsRenewed(PRBool *_retval) = 0;

  /* long set_CertPref_SetPreference (in wstring PrefName, in wstring Value); */
  NS_IMETHOD Set_CertPref_SetPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval) = 0;

  /* wstring get_CertPref_GetPreference (in wstring PrefName); */
  NS_IMETHOD Get_CertPref_GetPreference(const PRUnichar *PrefName, PRUnichar **_retval) = 0;

  /***************** Profile Management Interface ********************/
  /* long set_ProfMgmt_PasswdQuality (in long PasswdQuality); */
  NS_IMETHOD Set_ProfMgmt_PasswdQuality(PRInt32 PasswdQuality, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_PasswdQuality (); */
  NS_IMETHOD Get_ProfMgmt_PasswdQuality(PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_PasswdLength (in long PasswdLength); */
  NS_IMETHOD Set_ProfMgmt_PasswdLength(PRInt32 PasswdLength, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_PasswdLength (); */
  NS_IMETHOD Get_ProfMgmt_PasswdLength(PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_PasswdTimeOut (in long PasswdTimeOut); */
  NS_IMETHOD Set_ProfMgmt_PasswdTimeOut(PRInt32 PasswdTimeOut, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_PasswdTimeOut (); */
  NS_IMETHOD Get_ProfMgmt_PasswdTimeOut(PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_PasswdLockOutTries (in long PasswdLockOutTries); */
  NS_IMETHOD Set_ProfMgmt_PasswdLockOutTries(PRInt32 PasswdLockOutTries, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_PasswdLockOutTries (); */
  NS_IMETHOD Get_ProfMgmt_PasswdLockOutTries(PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_PasswdUnLockPeriod (in long PasswdUnLockPeriod); */
  NS_IMETHOD Set_ProfMgmt_PasswdUnLockPeriod(PRInt32 PasswdUnLockPeriod, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_PasswdUnLockPeriod (); */
  NS_IMETHOD Get_ProfMgmt_PasswdUnLockPeriod(PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_ProfileName (in wstring ProfileName); */
  NS_IMETHOD Set_ProfMgmt_ProfileName(const PRUnichar *ProfileName, PRInt32 *_retval) = 0;

  /* wstring get_ProfMgmt_ProfileName (); */
  NS_IMETHOD Get_ProfMgmt_ProfileName(PRUnichar **_retval) = 0;

  /* long set_ProfMgmt_Password (in wstring Password); */
  NS_IMETHOD Set_ProfMgmt_Password(const PRUnichar *Password, PRInt32 *_retval) = 0;

  /* long set_ProfMgmt_SaveLocal (in boolean boolSaveLocal); */
  NS_IMETHOD Set_ProfMgmt_SaveLocal(PRBool boolSaveLocal, PRInt32 *_retval) = 0;

  /* boolean get_ProfMgmt_SaveLocal (); */
  NS_IMETHOD Get_ProfMgmt_SaveLocal(PRBool *_retval) = 0;

  /* long set_ProfMgmt_RoamProfile (in boolean boolRoamProfile); */
  NS_IMETHOD Set_ProfMgmt_RoamProfile(PRBool boolRoamProfile, PRInt32 *_retval) = 0;

  /* boolean get_ProfMgmt_RoamProfile (); */
  NS_IMETHOD Get_ProfMgmt_RoamProfile(PRBool *_retval) = 0;

  /* long set_ProfMgmt_OpenProfFlags (in long flags); */
  NS_IMETHOD Set_ProfMgmt_OpenProfFlags(PRInt32 flags, PRInt32 *_retval) = 0;

  /* long get_ProfMgmt_OpenProfFlags (); */
  NS_IMETHOD Get_ProfMgmt_OpenProfFlags(PRInt32 *_retval) = 0;

  /* long ProfMgmt_OpenProfile (); */
  NS_IMETHOD ProfMgmt_OpenProfile(PRInt32 *_retval) = 0;

  /* long ProfMgmt_CloseProfile (); */
  NS_IMETHOD ProfMgmt_CloseProfile(PRInt32 *_retval) = 0;

  /* long ProfMgmt_SaveProfile (); */
  NS_IMETHOD ProfMgmt_SaveProfile(PRInt32 *_retval) = 0;

  /* long ProfMgmt_ChangePassword (); */
  NS_IMETHOD ProfMgmt_ChangePassword(PRInt32 *_retval) = 0;

  /***************** Search criteria Interface ********************/
  /* long set_SrchCrit_IssuerDN (in wstring IssuerDN); */
  NS_IMETHOD Set_SrchCrit_IssuerDN(const PRUnichar *IssuerDN, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_IssuerDN (); */
  NS_IMETHOD Get_SrchCrit_IssuerDN(PRUnichar **_retval) = 0;

  /* long set_SrchCrit_SubjectDN (in wstring SubjectDN); */
  NS_IMETHOD Set_SrchCrit_SubjectDN(const PRUnichar *SubjectDN, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_SubjectDN (); */
  NS_IMETHOD Get_SrchCrit_SubjectDN(PRUnichar **_retval) = 0;

  /* long set_SrchCrit_SerNum (in wstring SerNum); */
  NS_IMETHOD Set_SrchCrit_SerNum(const PRUnichar *SerNum, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_SerNum (); */
  NS_IMETHOD Get_SrchCrit_SerNum(PRUnichar **_retval) = 0;

  /* long set_SrchCrit_Email (in wstring Email); */
  NS_IMETHOD Set_SrchCrit_Email(const PRUnichar *Email, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_Email (); */
  NS_IMETHOD Get_SrchCrit_Email(PRUnichar **_retval) = 0;

  /* long set_SrchCrit_ExpDate (in unsigned long long ExpDate); */
  NS_IMETHOD Set_SrchCrit_ExpDate(PRUint64 ExpDate, PRInt32 *_retval) = 0;

  /* unsigned long long get_SrchCrit_ExpDate (); */
  NS_IMETHOD Get_SrchCrit_ExpDate(PRUint64 *_retval) = 0;

  /* long set_SrchCrit_EffDate (in unsigned long long EffDate); */
  NS_IMETHOD Set_SrchCrit_EffDate(PRUint64 EffDate, PRInt32 *_retval) = 0;

  /* unsigned long long get_SrchCrit_EffDate (); */
  NS_IMETHOD Get_SrchCrit_EffDate(PRUint64 *_retval) = 0;

  /* long set_SrchCrit_DateEquality (in short DateEquality); */
  NS_IMETHOD Set_SrchCrit_DateEquality(PRInt16 DateEquality, PRInt32 *_retval) = 0;

  /* short get_SrchCrit_DateEquality (); */
  NS_IMETHOD Get_SrchCrit_DateEquality(PRInt16 *_retval) = 0;

  /* long set_SrchCrit_Renewed (in boolean Renewed); */
  NS_IMETHOD Set_SrchCrit_Renewed(PRBool Renewed, PRInt32 *_retval) = 0;

  /* boolean get_SrchCrit_Renewed (); */
  NS_IMETHOD Get_SrchCrit_Renewed(PRBool *_retval) = 0;

  /* long set_SrchCrit_KeyUsage (in short KeyUsage); */
  NS_IMETHOD Set_SrchCrit_KeyUsage(PRInt16 KeyUsage, PRInt32 *_retval) = 0;

  /* short get_SrchCrit_KeyUsage (); */
  NS_IMETHOD Get_SrchCrit_KeyUsage(PRInt16 *_retval) = 0;

  /* long set_SrchCrit_KeySize (in short KeySize); */
  NS_IMETHOD Set_SrchCrit_KeySize(PRInt16 KeySize, PRInt32 *_retval) = 0;

  /* short get_SrchCrit_KeySize (); */
  NS_IMETHOD Get_SrchCrit_KeySize(PRInt16 *_retval) = 0;

  /* long set_SrchCrit_ExtOID (in wstring ExtOID); */
  NS_IMETHOD Set_SrchCrit_ExtOID(const PRUnichar *ExtOID, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_ExtOID (); */
  NS_IMETHOD Get_SrchCrit_ExtOID(PRUnichar **_retval) = 0;

  /* long set_SrchCrit_ExtVal (in wstring ExtVal); */
  NS_IMETHOD Set_SrchCrit_ExtVal(const PRUnichar *ExtVal, PRInt32 *_retval) = 0;

  /* wstring get_SrchCrit_ExtVal (); */
  NS_IMETHOD Get_SrchCrit_ExtVal(PRUnichar **_retval) = 0;

  /***************** UI Preferences properties *****************/
  /* long set_UIPrefs_Language (in long Language); */
  NS_IMETHOD Set_UIPrefs_Language(PRInt32 Language, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_Language (); */
  NS_IMETHOD Get_UIPrefs_Language(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_TitleFont (in wstring TitleFont); */
  NS_IMETHOD Set_UIPrefs_TitleFont(const PRUnichar *TitleFont, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_TitleFont (); */
  NS_IMETHOD Get_UIPrefs_TitleFont(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_TextFont (in wstring TextFont); */
  NS_IMETHOD Set_UIPrefs_TextFont(const PRUnichar *TextFont, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_TextFont (); */
  NS_IMETHOD Get_UIPrefs_TextFont(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_BtnFont (in wstring BtnFont); */
  NS_IMETHOD Set_UIPrefs_BtnFont(const PRUnichar *BtnFont, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_BtnFont (); */
  NS_IMETHOD Get_UIPrefs_BtnFont(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_UILogoUrl (in wstring UILogoUrl); */
  NS_IMETHOD Set_UIPrefs_UILogoUrl(const PRUnichar *UILogoUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_UILogoUrl (); */
  NS_IMETHOD Get_UIPrefs_UILogoUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_NewPasswd_Title (in wstring NewPasswd_Title); */
  NS_IMETHOD Set_UIPrefs_NewPasswd_Title(const PRUnichar *NewPasswd_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_NewPasswd_Title (); */
  NS_IMETHOD Get_UIPrefs_NewPasswd_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_NewPasswd_Text (in wstring NewPasswd_Text); */
  NS_IMETHOD Set_UIPrefs_NewPasswd_Text(const PRUnichar *NewPasswd_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_NewPasswd_Text (); */
  NS_IMETHOD Get_UIPrefs_NewPasswd_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_NewPasswd_OKBtnText (in long NewPasswd_OKBtnText); */
  NS_IMETHOD Set_UIPrefs_NewPasswd_OKBtnText(PRInt32 NewPasswd_OKBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_NewPasswd_OKBtnText (); */
  NS_IMETHOD Get_UIPrefs_NewPasswd_OKBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_NewPasswd_CancelBtnText (in long NewPasswd_CancelBtnText); */
  NS_IMETHOD Set_UIPrefs_NewPasswd_CancelBtnText(PRInt32 NewPasswd_CancelBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_NewPasswd_CancelBtnText (); */
  NS_IMETHOD Get_UIPrefs_NewPasswd_CancelBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_NewPasswd_HelpUrl (in wstring NewPasswd_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_NewPasswd_HelpUrl(const PRUnichar *NewPasswd_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_NewPasswd_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_NewPasswd_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_LgnDlg_Title (in wstring LgnDlg_Title); */
  NS_IMETHOD Set_UIPrefs_LgnDlg_Title(const PRUnichar *LgnDlg_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_LgnDlg_Title (); */
  NS_IMETHOD Get_UIPrefs_LgnDlg_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_OpenProf_Title (in wstring OpenProf_Title); */
  NS_IMETHOD Set_UIPrefs_OpenProf_Title(const PRUnichar *OpenProf_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_OpenProf_Title (); */
  NS_IMETHOD Get_UIPrefs_OpenProf_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_OpenProf_Text (in wstring OpenProf_Text); */
  NS_IMETHOD Set_UIPrefs_OpenProf_Text(const PRUnichar *OpenProf_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_OpenProf_Text (); */
  NS_IMETHOD Get_UIPrefs_OpenProf_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_OpenProf_OKBtnText (in long OpenProf_OKBtnText); */
  NS_IMETHOD Set_UIPrefs_OpenProf_OKBtnText(PRInt32 OpenProf_OKBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_OpenProf_OKBtnText (); */
  NS_IMETHOD Get_UIPrefs_OpenProf_OKBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_OpenProf_CancelBtnText (in long OpenProf_CancelBtnText); */
  NS_IMETHOD Set_UIPrefs_OpenProf_CancelBtnText(PRInt32 OpenProf_CancelBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_OpenProf_CancelBtnText (); */
  NS_IMETHOD Get_UIPrefs_OpenProf_CancelBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_OpenProf_HelpUrl (in wstring OpenProf_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_OpenProf_HelpUrl(const PRUnichar *OpenProf_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_OpenProf_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_OpenProf_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_SelID_Title (in wstring SelID_Title); */
  NS_IMETHOD Set_UIPrefs_SelID_Title(const PRUnichar *SelID_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_SelID_Title (); */
  NS_IMETHOD Get_UIPrefs_SelID_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_SelID_Text (in wstring SelID_Text); */
  NS_IMETHOD Set_UIPrefs_SelID_Text(const PRUnichar *SelID_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_SelID_Text (); */
  NS_IMETHOD Get_UIPrefs_SelID_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_SelID_OKBtnText (in long SelID_OKBtnText); */
  NS_IMETHOD Set_UIPrefs_SelID_OKBtnText(PRInt32 SelID_OKBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_SelID_OKBtnText (); */
  NS_IMETHOD Get_UIPrefs_SelID_OKBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_SelID_CancelBtnText (in long SelID_CancelBtnText); */
  NS_IMETHOD Set_UIPrefs_SelID_CancelBtnText(PRInt32 SelID_CancelBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_SelID_CancelBtnText (); */
  NS_IMETHOD Get_UIPrefs_SelID_CancelBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_SelID_ShowDefChkBox (in boolean SelID_ShowDefChkBox); */
  NS_IMETHOD Set_UIPrefs_SelID_ShowDefChkBox(PRBool SelID_ShowDefChkBox, PRInt32 *_retval) = 0;

  /* boolean get_UIPrefs_SelID_ShowDefChkBox (); */
  NS_IMETHOD Get_UIPrefs_SelID_ShowDefChkBox(PRBool *_retval) = 0;

  /* long set_UIPrefs_SelID_ChkBoxText (in wstring SelID_ChkBoxText); */
  NS_IMETHOD Set_UIPrefs_SelID_ChkBoxText(const PRUnichar *SelID_ChkBoxText, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_SelID_ChkBoxText (); */
  NS_IMETHOD Get_UIPrefs_SelID_ChkBoxText(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_SelID_HelpUrl (in wstring SelID_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_SelID_HelpUrl(const PRUnichar *SelID_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_SelID_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_SelID_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_SgnDlg_Title (in wstring SgnDlg_Title); */
  NS_IMETHOD Set_UIPrefs_SgnDlg_Title(const PRUnichar *SgnDlg_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_SgnDlg_Title (); */
  NS_IMETHOD Get_UIPrefs_SgnDlg_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_RvwMsg_Text (in wstring RvwMsg_Text); */
  NS_IMETHOD Set_UIPrefs_RvwMsg_Text(const PRUnichar *RvwMsg_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_RvwMsg_Text (); */
  NS_IMETHOD Get_UIPrefs_RvwMsg_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_RvwMsg_OKBtnText (in long RvwMsg_OKBtnText); */
  NS_IMETHOD Set_UIPrefs_RvwMsg_OKBtnText(PRInt32 RvwMsg_OKBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_RvwMsg_OKBtnText (); */
  NS_IMETHOD Get_UIPrefs_RvwMsg_OKBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_RvwMsg_Title (in wstring RvwMsg_Title); */
  NS_IMETHOD Set_UIPrefs_RvwMsg_Title(const PRUnichar *RvwMsg_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_RvwMsg_Title (); */
  NS_IMETHOD Get_UIPrefs_RvwMsg_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_RvwMsg_CancelBtnText (in long RvwMsg_CancelBtnText); */
  NS_IMETHOD Set_UIPrefs_RvwMsg_CancelBtnText(PRInt32 RvwMsg_CancelBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_RvwMsg_CancelBtnText (); */
  NS_IMETHOD Get_UIPrefs_RvwMsg_CancelBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_RvwMsg_HelpUrl (in wstring RvwMsg_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_RvwMsg_HelpUrl(const PRUnichar *RvwMsg_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_RvwMsg_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_RvwMsg_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_IntroDlg_Title (in wstring IntroDlg_Title); */
  NS_IMETHOD Set_UIPrefs_IntroDlg_Title(const PRUnichar *IntroDlg_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_IntroDlg_Title (); */
  NS_IMETHOD Get_UIPrefs_IntroDlg_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_IntroDlg_Text (in wstring IntroDlg_Text); */
  NS_IMETHOD Set_UIPrefs_IntroDlg_Text(const PRUnichar *IntroDlg_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_IntroDlg_Text (); */
  NS_IMETHOD Get_UIPrefs_IntroDlg_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_IntroDlg_HelpUrl (in wstring IntroDlg_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_IntroDlg_HelpUrl(const PRUnichar *IntroDlg_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_IntroDlg_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_IntroDlg_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_CreateNewProf_Title (in wstring CreateNewProf_Title); */
  NS_IMETHOD Set_UIPrefs_CreateNewProf_Title(const PRUnichar *CreateNewProf_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_CreateNewProf_Title (); */
  NS_IMETHOD Get_UIPrefs_CreateNewProf_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_ChangePasswd_Title (in wstring ChangePasswd_Title); */
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Title(const PRUnichar *ChangePasswd_Title, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_ChangePasswd_Title (); */
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Title(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_ChangePasswd_Text (in wstring ChangePasswd_Text); */
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Text(const PRUnichar *ChangePasswd_Text, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_ChangePasswd_Text (); */
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Text(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_ChangePasswd_OKBtnText (in long ChangePasswd_OKBtnText); */
  NS_IMETHOD Set_UIPrefs_ChangePasswd_OKBtnText(PRInt32 ChangePasswd_OKBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_ChangePasswd_OKBtnText (); */
  NS_IMETHOD Get_UIPrefs_ChangePasswd_OKBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_ChangePasswd_CancelBtnText (in long ChangePasswd_CancelBtnText); */
  NS_IMETHOD Set_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 ChangePasswd_CancelBtnText, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_ChangePasswd_CancelBtnText (); */
  NS_IMETHOD Get_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_ChangePasswd_HelpUrl (in wstring ChangePasswd_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_ChangePasswd_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_ChangePasswd_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_ChangePasswd_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_Timeout_HelpUrl (in wstring ChangePasswd_HelpUrl); */
  NS_IMETHOD Set_UIPrefs_Timeout_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval) = 0;

  /* wstring get_UIPrefs_Timeout_HelpUrl (); */
  NS_IMETHOD Get_UIPrefs_Timeout_HelpUrl(PRUnichar **_retval) = 0;

  /* long set_UIPrefs_EnableTopMostWindow (in boolean boolEnableTopMost); */
  NS_IMETHOD Set_UIPrefs_EnableTopMostWindow(PRBool boolEnableTopMost, PRInt32 *_retval) = 0;

  /* long set_UIPrefs_SignTransDlgWidth (in long nWidth); */
  NS_IMETHOD Set_UIPrefs_SignTransDlgWidth(PRInt32 nWidth, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_SignTransDlgWidth (); */
  NS_IMETHOD Get_UIPrefs_SignTransDlgWidth(PRInt32 *_retval) = 0;

  /* long set_UIPrefs_SignTransDlgHeight (in long nHeight); */
  NS_IMETHOD Set_UIPrefs_SignTransDlgHeight(PRInt32 nHeight, PRInt32 *_retval) = 0;

  /* long get_UIPrefs_SignTransDlgHeight (); */
  NS_IMETHOD Get_UIPrefs_SignTransDlgHeight(PRInt32 *_retval) = 0;

  /***************** Selected Digital ID Interface ********************/
  /* wstring get_SelectedDigID_IssuerDN (); */
  NS_IMETHOD Get_SelectedDigID_IssuerDN(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_SubjectDN (); */
  NS_IMETHOD Get_SelectedDigID_SubjectDN(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_SerNum (); */
  NS_IMETHOD Get_SelectedDigID_SerNum(PRUnichar **_retval) = 0;

  /* unsigned long long get_SelectedDigID_ExpDate (); */
  NS_IMETHOD Get_SelectedDigID_ExpDate(PRUint64 *_retval) = 0;

  /* unsigned long long get_SelectedDigID_EffDate (); */
  NS_IMETHOD Get_SelectedDigID_EffDate(PRUint64 *_retval) = 0;

  /* short get_SelectedDigID_KeyUsage (); */
  NS_IMETHOD Get_SelectedDigID_KeyUsage(PRInt16 *_retval) = 0;

  /* short get_SelectedDigID_KeySize (); */
  NS_IMETHOD Get_SelectedDigID_KeySize(PRInt16 *_retval) = 0;

  /* boolean get_SelectedDigID_Renewed (); */
  NS_IMETHOD Get_SelectedDigID_Renewed(PRBool *_retval) = 0;

  /* wstring get_SelectedDigID_PubKeyMD5 (); */
  NS_IMETHOD Get_SelectedDigID_PubKeyMD5(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_PubKeySHA1 (); */
  NS_IMETHOD Get_SelectedDigID_PubKeySHA1(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_FrndlyName (); */
  NS_IMETHOD Get_SelectedDigID_FrndlyName(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_LogoUrl (); */
  NS_IMETHOD Get_SelectedDigID_LogoUrl(PRUnichar **_retval) = 0;

  /* wstring get_SelectedDigID_TextureUrl (); */
  NS_IMETHOD Get_SelectedDigID_TextureUrl(PRUnichar **_retval) = 0;

  /***************** Roaming Preferences Interface ********************/
  /* long set_RoamPrefs_NumOfSrvrs (in short NumOfSrvrs); */
  NS_IMETHOD Set_RoamPrefs_NumOfSrvrs(PRInt16 NumOfSrvrs, PRInt32 *_retval) = 0;

  /* short get_RoamPrefs_NumOfSrvrs (); */
  NS_IMETHOD Get_RoamPrefs_NumOfSrvrs(PRInt16 *_retval) = 0;

  /* long set_RoamPrefs_StorageSrvr (in wstring StorageSrvr); */
  NS_IMETHOD Set_RoamPrefs_StorageSrvr(const PRUnichar *StorageSrvr, PRInt32 *_retval) = 0;

  /* wstring get_RoamPrefs_StorageSrvr (); */
  NS_IMETHOD Get_RoamPrefs_StorageSrvr(PRUnichar **_retval) = 0;

  /* long set_RoamPrefs_ClientInfo (in wstring ClientInfo); */
  NS_IMETHOD Set_RoamPrefs_ClientInfo(const PRUnichar *ClientInfo, PRInt32 *_retval) = 0;

  /* wstring get_RoamPrefs_ClientInfo (); */
  NS_IMETHOD Get_RoamPrefs_ClientInfo(PRUnichar **_retval) = 0;

  /* long set_RoamPrefs_ClientInfoSig (in wstring ClientInfoSig); */
  NS_IMETHOD Set_RoamPrefs_ClientInfoSig(const PRUnichar *ClientInfoSig, PRInt32 *_retval) = 0;

  /* wstring get_RoamPrefs_ClientInfoSig (); */
  NS_IMETHOD Get_RoamPrefs_ClientInfoSig(PRUnichar **_retval) = 0;

  /** XEnroll properties ***/
  /* long set_XEnroll_ProviderType (in long nProviderType); */
  NS_IMETHOD Set_XEnroll_ProviderType(PRInt32 nProviderType, PRInt32 *_retval) = 0;

  /* long get_XEnroll_ProviderType (); */
  NS_IMETHOD Get_XEnroll_ProviderType(PRInt32 *_retval) = 0;

  /* long set_XEnroll_GenKeyFlags (in long nGenKeyFlags); */
  NS_IMETHOD Set_XEnroll_GenKeyFlags(PRInt32 nGenKeyFlags, PRInt32 *_retval) = 0;

  /* long get_XEnroll_GenKeyFlags (); */
  NS_IMETHOD Get_XEnroll_GenKeyFlags(PRInt32 *_retval) = 0;

  /* long set_XEnroll_ProviderName (in wstring szProviderName); */
  NS_IMETHOD Set_XEnroll_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval) = 0;

  /* wstring get_XEnroll_ProviderName (); */
  NS_IMETHOD Get_XEnroll_ProviderName(PRUnichar **_retval) = 0;

  /* long set_XEnroll_HashAlgorithm (in wstring szHashAlgo); */
  NS_IMETHOD Set_XEnroll_HashAlgorithm(const PRUnichar *szHashAlgo, PRInt32 *_retval) = 0;

  /* wstring get_XEnroll_HashAlgorithm (); */
  NS_IMETHOD Get_XEnroll_HashAlgorithm(PRUnichar **_retval) = 0;

  /* long set_XEnroll_KeySpec (in long nKeySpec); */
  NS_IMETHOD Set_XEnroll_KeySpec(PRInt32 nKeySpec, PRInt32 *_retval) = 0;

  /* long get_XEnroll_KeySpec (); */
  NS_IMETHOD Get_XEnroll_KeySpec(PRInt32 *_retval) = 0;

  /* long set_XEnroll_DeleteRequestCert (in boolean boolFlag); */
  NS_IMETHOD Set_XEnroll_DeleteRequestCert(PRBool boolFlag, PRInt32 *_retval) = 0;

  /* boolean get_XEnroll_DeleteRequestCert (); */
  NS_IMETHOD Get_XEnroll_DeleteRequestCert(PRBool *_retval) = 0;

  /* long set_XEnroll_WriteCertToCSP (in boolean boolFlag); */
  NS_IMETHOD Set_XEnroll_WriteCertToCSP(PRBool boolFlag, PRInt32 *_retval) = 0;

  /* boolean get_XEnroll_WriteCertToCSP (); */
  NS_IMETHOD Get_XEnroll_WriteCertToCSP(PRBool *_retval) = 0;

  /**** XEnroll methods ***/
  /* wstring XEnroll_enumProviders (in long nIndex, in long nFlags); */
  NS_IMETHOD XEnroll_enumProviders(PRInt32 nIndex, PRInt32 nFlags, PRUnichar **_retval) = 0;

  /* wstring XEnroll_createPKCS10 (in wstring szDNName, in wstring szUsage); */
  NS_IMETHOD XEnroll_createPKCS10(const PRUnichar *szDNName, const PRUnichar *szUsage, PRUnichar **_retval) = 0;

  /* long XEnroll_acceptPKCS7 (in wstring szPKCS7); */
  NS_IMETHOD XEnroll_acceptPKCS7(const PRUnichar *szPKCS7, PRInt32 *_retval) = 0;

  /**** Error handling method ****/
  /* unsigned long GetLastError (); */
  NS_IMETHOD GetLastError(PRUint32 *_retval) = 0;

  /**** Config Checker Methods ***/
/**** VSImport Methods ****/
  /* long VSImport_Import (in wstring PKCS12, in wstring PKCS7, out wstring szErrCodeString); */
  NS_IMETHOD VSImport_Import(const PRUnichar *PKCS12, const PRUnichar *PKCS7, PRUnichar **szErrCodeString, PRInt32 *_retval) = 0;

  /* long VSImport_set_KeyExportable (in long nFlag); */
  NS_IMETHOD VSImport_set_KeyExportable(PRInt32 nFlag, PRInt32 *_retval) = 0;

  /* long VSImport_get_KeyExportable (); */
  NS_IMETHOD VSImport_get_KeyExportable(PRInt32 *_retval) = 0;

  /* long VSImport_set_ProviderName (in wstring szProviderName); */
  NS_IMETHOD VSImport_set_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval) = 0;

  /* wstring VSImport_get_ProviderName (); */
  NS_IMETHOD VSImport_get_ProviderName(PRUnichar **_retval) = 0;

  /**** AddRootCerts Methods ****/
  /* long AddRootCerts_Initialize (); */
  NS_IMETHOD AddRootCerts_Initialize(PRInt32 *_retval) = 0;

  /* long AddRootCerts_CreateStandardTrustProfile (); */
  NS_IMETHOD AddRootCerts_CreateStandardTrustProfile(PRInt32 *_retval) = 0;

  /* long AddRootCerts_CreateVerisignTrustProfile (); */
  NS_IMETHOD AddRootCerts_CreateVerisignTrustProfile(PRInt32 *_retval) = 0;

  /****	ImportP12 Methods ****/
  /* long P12Import_ImportP12 (in long nType, in wstring strP12, out wstring strSerialNum, out wstring strIssuerDN); */
  NS_IMETHOD P12Import_ImportP12(PRInt32 nType, const PRUnichar *strP12, PRUnichar **strSerialNum, PRUnichar **strIssuerDN, PRInt32 *_retval) = 0;

  /****	ExportP12 Methods ****/
  /* long P12Export_ExportP12 (in long nOutputType, in long nFlags, in wstring strFile); */
  NS_IMETHOD P12Export_ExportP12(PRInt32 nOutputType, PRInt32 nFlags, const PRUnichar *strFile, PRInt32 *_retval) = 0;

  /* long get_P12Export_PasswdQuality (); */
  NS_IMETHOD Get_P12Export_PasswdQuality(PRInt32 *_retval) = 0;

  /* long set_P12Export_PasswdQuality (in long newVal); */
  NS_IMETHOD Set_P12Export_PasswdQuality(PRInt32 newVal, PRInt32 *_retval) = 0;

  /* long get_P12Export_PasswdLength (); */
  NS_IMETHOD Get_P12Export_PasswdLength(PRInt32 *_retval) = 0;

  /* long set_P12Export_PasswdLength (in long newVal); */
  NS_IMETHOD Set_P12Export_PasswdLength(PRInt32 newVal, PRInt32 *_retval) = 0;

  /****	Digital Notarization Methods ****/
  /* long NZ_Initialize (); */
  NS_IMETHOD NZ_Initialize(PRInt32 *_retval) = 0;

  /* long NZ_Close (); */
  NS_IMETHOD NZ_Close(PRInt32 *_retval) = 0;

  /* long set_NZ_NotarizationServer (in wstring ServerName); */
  NS_IMETHOD Set_NZ_NotarizationServer(const PRUnichar *ServerName, PRInt32 *_retval) = 0;

  /* long set_NZ_HashAlg (in wstring HashAlg); */
  NS_IMETHOD Set_NZ_HashAlg(const PRUnichar *HashAlg, PRInt32 *_retval) = 0;

  /* long set_NZ_DisplayDigitalID (in long DisplayID); */
  NS_IMETHOD Set_NZ_DisplayDigitalID(PRInt32 DisplayID, PRInt32 *_retval) = 0;

  /* long set_NZ_CrlLocation (in wstring CrlLocation); */
  NS_IMETHOD Set_NZ_CrlLocation(const PRUnichar *CrlLocation, PRInt32 *_retval) = 0;

  /* long set_NZ_ValidationPreference (in long ValPref); */
  NS_IMETHOD Set_NZ_ValidationPreference(PRInt32 ValPref, PRInt32 *_retval) = 0;

  /* long set_NZ_NotarizationDescription (in wstring Description); */
  NS_IMETHOD Set_NZ_NotarizationDescription(const PRUnichar *Description, PRInt32 *_retval) = 0;

  /* wstring NZ_NotarizeDocument (in wstring DocumentName, in long UIMask, in long ResponseType); */
  NS_IMETHOD NZ_NotarizeDocument(const PRUnichar *DocumentName, PRInt32 UIMask, PRInt32 ResponseType, PRUnichar **_retval) = 0;

  /* wstring NZ_NotarizeHash (in wstring Hash, in long UIMask); */
  NS_IMETHOD NZ_NotarizeHash(const PRUnichar *Hash, PRInt32 UIMask, PRUnichar **_retval) = 0;

  /* long NZ_VerifyNotarizationRecord (in wstring Record, in wstring Document, in long RecordType, in long UIMask); */
  NS_IMETHOD NZ_VerifyNotarizationRecord(const PRUnichar *Record, const PRUnichar *Document, PRInt32 RecordType, PRInt32 UIMask, PRInt32 *_retval) = 0;

  /* long NZ_AddCertificate (in wstring Certificate); */
  NS_IMETHOD NZ_AddCertificate(const PRUnichar *Certificate, PRInt32 *_retval) = 0;

  /**** User Preferences methods of Digital Notarization ****/
  /* long set_NZ_UIPrefs_LogoUrl (in wstring LogoUrl); */
  NS_IMETHOD Set_NZ_UIPrefs_LogoUrl(const PRUnichar *LogoUrl, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_SelFileTitle (in wstring SelFileTitle); */
  NS_IMETHOD Set_NZ_UIPrefs_SelFileTitle(const PRUnichar *SelFileTitle, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_SelFileDescription (in wstring SelFileDesc); */
  NS_IMETHOD Set_NZ_UIPrefs_SelFileDescription(const PRUnichar *SelFileDesc, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_SelFileHelpUrl (in wstring SelFileHelpUrl); */
  NS_IMETHOD Set_NZ_UIPrefs_SelFileHelpUrl(const PRUnichar *SelFileHelpUrl, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ProgressTitle (in wstring ProgressTitle); */
  NS_IMETHOD Set_NZ_UIPrefs_ProgressTitle(const PRUnichar *ProgressTitle, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ProgressDescription (in wstring ProgressDesc); */
  NS_IMETHOD Set_NZ_UIPrefs_ProgressDescription(const PRUnichar *ProgressDesc, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ProgressHelpUrl (in wstring ProgressHelpUrl); */
  NS_IMETHOD Set_NZ_UIPrefs_ProgressHelpUrl(const PRUnichar *ProgressHelpUrl, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ReceiptTitle (in wstring ReceiptTitle); */
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptTitle(const PRUnichar *ReceiptTitle, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ReceiptDescription (in wstring ReceiptDesc); */
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptDescription(const PRUnichar *ReceiptDesc, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_ReceiptHelpUrl (in wstring ReceiptHelpUrl); */
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptHelpUrl(const PRUnichar *ReceiptHelpUrl, PRInt32 *_retval) = 0;

  /* long set_NZ_UIPrefs_WizardTitle (in wstring WizardTitle); */
  NS_IMETHOD Set_NZ_UIPrefs_WizardTitle(const PRUnichar *WizardTitle, PRInt32 *_retval) = 0;

  /**** Application Preferences methods of Digital Notarization ****/
  /* long set_NZ_ApplicationPreference (in wstring ApplicationName, in wstring PreferenceName, in long PreferenceType, in wstring PreferenceValue); */
  NS_IMETHOD Set_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRInt32 PreferenceType, const PRUnichar *PreferenceValue, PRInt32 *_retval) = 0;

  /* wstring get_NZ_ApplicationPreference (in wstring ApplicationName, in wstring PreferenceName); */
  NS_IMETHOD Get_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRUnichar **_retval) = 0;

};

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NS6IPTA \
  NS_IMETHOD PTA_Initialize(const PRUnichar *AppCtxtName, PRInt32 UseCapi, PRInt32 *_retval); \
  NS_IMETHOD PTA_Close(PRInt32 *_retval); \
  NS_IMETHOD Set_PTA_AppPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_AppPreference(const PRUnichar *PrefName, PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_CSPName(const PRUnichar *CSPName, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_CSPName(PRUnichar **_retval); \
  NS_IMETHOD PTA_CreateCertReq(const PRUnichar *SubjectDN, PRInt32 KeyGenFlag, PRInt32 HashAlg, PRUint32 count, const PRUnichar **Attribs, PRUnichar **_retval); \
  NS_IMETHOD PTA_InstallCert(const PRUnichar *Cert, PRInt32 *_retval); \
  NS_IMETHOD PTA_InstallKeyPair(const PRUnichar *privKeyBlob, const PRUnichar *pkcs7Cert, PRInt32 *_retval); \
  NS_IMETHOD PTA_SignChallenge(const PRUnichar *Challenge, PRInt32 AlgID, PRUnichar **_retval); \
  NS_IMETHOD PTA_SignTransaction(const PRUnichar *Message, PRInt32 AlgID, PRUnichar **_retval); \
  NS_IMETHOD PTA_SignRenewal(PRInt32 AlgID, PRUnichar **_retval); \
  NS_IMETHOD PTA_SelectIDForTrans(PRInt32 *_retval); \
  NS_IMETHOD PTA_SelectIDForChallenge(PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_UseDefCertFlag(PRInt16 *_retval); \
  NS_IMETHOD Set_PTA_UseDefCertFlag(PRInt16 defCertFlag, PRInt32 *_retval); \
  NS_IMETHOD Set_PTA_ProtocolName(const PRUnichar *protocolName, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_ProtocolName(PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_AuthDll(const PRUnichar *authDllName, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_AuthDll(PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_ProfileIssFrndlyName(const PRUnichar *profileIssFrndlyName, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_ProfileIssFrndlyName(PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_ProfileIssUniqueId(const PRUnichar *profileIssUniqId, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_ProfileIssUniqueId(PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_AffLogoUrl(const PRUnichar *affLogoUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_PTA_AffLogoUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_PTA_EnableCertForCapi(PRBool boolEnableForCapi, PRInt32 *_retval); \
  NS_IMETHOD Set_CertPref_CertSerNum(const PRUnichar *CertSerNum, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertSerNum(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_CertIssDN(const PRUnichar *CertIssDN, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertIssDN(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_CertFrndlyName(const PRUnichar *CertFrndlyName, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertFrndlyName(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_CertLogoUrl(const PRUnichar *CertLogoUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertLogoUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_CertDispString(const PRUnichar *CertDispString, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertDispString(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_CertTextureUrl(const PRUnichar *CertTextureUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_CertTextureUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_CertPref_MarkAsRenewed(PRBool boolMarkAsRenewed, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_MarkAsRenewed(PRBool *_retval); \
  NS_IMETHOD Set_CertPref_SetPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval); \
  NS_IMETHOD Get_CertPref_GetPreference(const PRUnichar *PrefName, PRUnichar **_retval); \
  NS_IMETHOD Set_ProfMgmt_PasswdQuality(PRInt32 PasswdQuality, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_PasswdQuality(PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_PasswdLength(PRInt32 PasswdLength, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_PasswdLength(PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_PasswdTimeOut(PRInt32 PasswdTimeOut, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_PasswdTimeOut(PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_PasswdLockOutTries(PRInt32 PasswdLockOutTries, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_PasswdLockOutTries(PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_PasswdUnLockPeriod(PRInt32 PasswdUnLockPeriod, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_PasswdUnLockPeriod(PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_ProfileName(const PRUnichar *ProfileName, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_ProfileName(PRUnichar **_retval); \
  NS_IMETHOD Set_ProfMgmt_Password(const PRUnichar *Password, PRInt32 *_retval); \
  NS_IMETHOD Set_ProfMgmt_SaveLocal(PRBool boolSaveLocal, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_SaveLocal(PRBool *_retval); \
  NS_IMETHOD Set_ProfMgmt_RoamProfile(PRBool boolRoamProfile, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_RoamProfile(PRBool *_retval); \
  NS_IMETHOD Set_ProfMgmt_OpenProfFlags(PRInt32 flags, PRInt32 *_retval); \
  NS_IMETHOD Get_ProfMgmt_OpenProfFlags(PRInt32 *_retval); \
  NS_IMETHOD ProfMgmt_OpenProfile(PRInt32 *_retval); \
  NS_IMETHOD ProfMgmt_CloseProfile(PRInt32 *_retval); \
  NS_IMETHOD ProfMgmt_SaveProfile(PRInt32 *_retval); \
  NS_IMETHOD ProfMgmt_ChangePassword(PRInt32 *_retval); \
  NS_IMETHOD Set_SrchCrit_IssuerDN(const PRUnichar *IssuerDN, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_IssuerDN(PRUnichar **_retval); \
  NS_IMETHOD Set_SrchCrit_SubjectDN(const PRUnichar *SubjectDN, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_SubjectDN(PRUnichar **_retval); \
  NS_IMETHOD Set_SrchCrit_SerNum(const PRUnichar *SerNum, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_SerNum(PRUnichar **_retval); \
  NS_IMETHOD Set_SrchCrit_Email(const PRUnichar *Email, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_Email(PRUnichar **_retval); \
  NS_IMETHOD Set_SrchCrit_ExpDate(PRUint64 ExpDate, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_ExpDate(PRUint64 *_retval); \
  NS_IMETHOD Set_SrchCrit_EffDate(PRUint64 EffDate, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_EffDate(PRUint64 *_retval); \
  NS_IMETHOD Set_SrchCrit_DateEquality(PRInt16 DateEquality, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_DateEquality(PRInt16 *_retval); \
  NS_IMETHOD Set_SrchCrit_Renewed(PRBool Renewed, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_Renewed(PRBool *_retval); \
  NS_IMETHOD Set_SrchCrit_KeyUsage(PRInt16 KeyUsage, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_KeyUsage(PRInt16 *_retval); \
  NS_IMETHOD Set_SrchCrit_KeySize(PRInt16 KeySize, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_KeySize(PRInt16 *_retval); \
  NS_IMETHOD Set_SrchCrit_ExtOID(const PRUnichar *ExtOID, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_ExtOID(PRUnichar **_retval); \
  NS_IMETHOD Set_SrchCrit_ExtVal(const PRUnichar *ExtVal, PRInt32 *_retval); \
  NS_IMETHOD Get_SrchCrit_ExtVal(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_Language(PRInt32 Language, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_Language(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_TitleFont(const PRUnichar *TitleFont, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_TitleFont(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_TextFont(const PRUnichar *TextFont, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_TextFont(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_BtnFont(const PRUnichar *BtnFont, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_BtnFont(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_UILogoUrl(const PRUnichar *UILogoUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_UILogoUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_NewPasswd_Title(const PRUnichar *NewPasswd_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_NewPasswd_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_NewPasswd_Text(const PRUnichar *NewPasswd_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_NewPasswd_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_NewPasswd_OKBtnText(PRInt32 NewPasswd_OKBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_NewPasswd_OKBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_NewPasswd_CancelBtnText(PRInt32 NewPasswd_CancelBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_NewPasswd_CancelBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_NewPasswd_HelpUrl(const PRUnichar *NewPasswd_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_NewPasswd_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_LgnDlg_Title(const PRUnichar *LgnDlg_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_LgnDlg_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_OpenProf_Title(const PRUnichar *OpenProf_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_OpenProf_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_OpenProf_Text(const PRUnichar *OpenProf_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_OpenProf_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_OpenProf_OKBtnText(PRInt32 OpenProf_OKBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_OpenProf_OKBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_OpenProf_CancelBtnText(PRInt32 OpenProf_CancelBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_OpenProf_CancelBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_OpenProf_HelpUrl(const PRUnichar *OpenProf_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_OpenProf_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_Title(const PRUnichar *SelID_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_Text(const PRUnichar *SelID_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_OKBtnText(PRInt32 SelID_OKBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_OKBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_CancelBtnText(PRInt32 SelID_CancelBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_CancelBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_ShowDefChkBox(PRBool SelID_ShowDefChkBox, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_ShowDefChkBox(PRBool *_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_ChkBoxText(const PRUnichar *SelID_ChkBoxText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_ChkBoxText(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_SelID_HelpUrl(const PRUnichar *SelID_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SelID_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_SgnDlg_Title(const PRUnichar *SgnDlg_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SgnDlg_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_RvwMsg_Text(const PRUnichar *RvwMsg_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_RvwMsg_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_RvwMsg_OKBtnText(PRInt32 RvwMsg_OKBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_RvwMsg_OKBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_RvwMsg_Title(const PRUnichar *RvwMsg_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_RvwMsg_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_RvwMsg_CancelBtnText(PRInt32 RvwMsg_CancelBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_RvwMsg_CancelBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_RvwMsg_HelpUrl(const PRUnichar *RvwMsg_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_RvwMsg_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_IntroDlg_Title(const PRUnichar *IntroDlg_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_IntroDlg_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_IntroDlg_Text(const PRUnichar *IntroDlg_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_IntroDlg_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_IntroDlg_HelpUrl(const PRUnichar *IntroDlg_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_IntroDlg_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_CreateNewProf_Title(const PRUnichar *CreateNewProf_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_CreateNewProf_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Title(const PRUnichar *ChangePasswd_Title, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Title(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Text(const PRUnichar *ChangePasswd_Text, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Text(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_OKBtnText(PRInt32 ChangePasswd_OKBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_OKBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 ChangePasswd_CancelBtnText, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_Timeout_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_Timeout_HelpUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_UIPrefs_EnableTopMostWindow(PRBool boolEnableTopMost, PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_SignTransDlgWidth(PRInt32 nWidth, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SignTransDlgWidth(PRInt32 *_retval); \
  NS_IMETHOD Set_UIPrefs_SignTransDlgHeight(PRInt32 nHeight, PRInt32 *_retval); \
  NS_IMETHOD Get_UIPrefs_SignTransDlgHeight(PRInt32 *_retval); \
  NS_IMETHOD Get_SelectedDigID_IssuerDN(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_SubjectDN(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_SerNum(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_ExpDate(PRUint64 *_retval); \
  NS_IMETHOD Get_SelectedDigID_EffDate(PRUint64 *_retval); \
  NS_IMETHOD Get_SelectedDigID_KeyUsage(PRInt16 *_retval); \
  NS_IMETHOD Get_SelectedDigID_KeySize(PRInt16 *_retval); \
  NS_IMETHOD Get_SelectedDigID_Renewed(PRBool *_retval); \
  NS_IMETHOD Get_SelectedDigID_PubKeyMD5(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_PubKeySHA1(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_FrndlyName(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_LogoUrl(PRUnichar **_retval); \
  NS_IMETHOD Get_SelectedDigID_TextureUrl(PRUnichar **_retval); \
  NS_IMETHOD Set_RoamPrefs_NumOfSrvrs(PRInt16 NumOfSrvrs, PRInt32 *_retval); \
  NS_IMETHOD Get_RoamPrefs_NumOfSrvrs(PRInt16 *_retval); \
  NS_IMETHOD Set_RoamPrefs_StorageSrvr(const PRUnichar *StorageSrvr, PRInt32 *_retval); \
  NS_IMETHOD Get_RoamPrefs_StorageSrvr(PRUnichar **_retval); \
  NS_IMETHOD Set_RoamPrefs_ClientInfo(const PRUnichar *ClientInfo, PRInt32 *_retval); \
  NS_IMETHOD Get_RoamPrefs_ClientInfo(PRUnichar **_retval); \
  NS_IMETHOD Set_RoamPrefs_ClientInfoSig(const PRUnichar *ClientInfoSig, PRInt32 *_retval); \
  NS_IMETHOD Get_RoamPrefs_ClientInfoSig(PRUnichar **_retval); \
  NS_IMETHOD Set_XEnroll_ProviderType(PRInt32 nProviderType, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_ProviderType(PRInt32 *_retval); \
  NS_IMETHOD Set_XEnroll_GenKeyFlags(PRInt32 nGenKeyFlags, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_GenKeyFlags(PRInt32 *_retval); \
  NS_IMETHOD Set_XEnroll_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_ProviderName(PRUnichar **_retval); \
  NS_IMETHOD Set_XEnroll_HashAlgorithm(const PRUnichar *szHashAlgo, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_HashAlgorithm(PRUnichar **_retval); \
  NS_IMETHOD Set_XEnroll_KeySpec(PRInt32 nKeySpec, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_KeySpec(PRInt32 *_retval); \
  NS_IMETHOD Set_XEnroll_DeleteRequestCert(PRBool boolFlag, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_DeleteRequestCert(PRBool *_retval); \
  NS_IMETHOD Set_XEnroll_WriteCertToCSP(PRBool boolFlag, PRInt32 *_retval); \
  NS_IMETHOD Get_XEnroll_WriteCertToCSP(PRBool *_retval); \
  NS_IMETHOD XEnroll_enumProviders(PRInt32 nIndex, PRInt32 nFlags, PRUnichar **_retval); \
  NS_IMETHOD XEnroll_createPKCS10(const PRUnichar *szDNName, const PRUnichar *szUsage, PRUnichar **_retval); \
  NS_IMETHOD XEnroll_acceptPKCS7(const PRUnichar *szPKCS7, PRInt32 *_retval); \
  NS_IMETHOD GetLastError(PRUint32 *_retval); \
  NS_IMETHOD VSImport_Import(const PRUnichar *PKCS12, const PRUnichar *PKCS7, PRUnichar **szErrCodeString, PRInt32 *_retval); \
  NS_IMETHOD VSImport_set_KeyExportable(PRInt32 nFlag, PRInt32 *_retval); \
  NS_IMETHOD VSImport_get_KeyExportable(PRInt32 *_retval); \
  NS_IMETHOD VSImport_set_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval); \
  NS_IMETHOD VSImport_get_ProviderName(PRUnichar **_retval); \
  NS_IMETHOD AddRootCerts_Initialize(PRInt32 *_retval); \
  NS_IMETHOD AddRootCerts_CreateStandardTrustProfile(PRInt32 *_retval); \
  NS_IMETHOD AddRootCerts_CreateVerisignTrustProfile(PRInt32 *_retval); \
  NS_IMETHOD P12Import_ImportP12(PRInt32 nType, const PRUnichar *strP12, PRUnichar **strSerialNum, PRUnichar **strIssuerDN, PRInt32 *_retval); \
  NS_IMETHOD P12Export_ExportP12(PRInt32 nOutputType, PRInt32 nFlags, const PRUnichar *strFile, PRInt32 *_retval); \
  NS_IMETHOD Get_P12Export_PasswdQuality(PRInt32 *_retval); \
  NS_IMETHOD Set_P12Export_PasswdQuality(PRInt32 newVal, PRInt32 *_retval); \
  NS_IMETHOD Get_P12Export_PasswdLength(PRInt32 *_retval); \
  NS_IMETHOD Set_P12Export_PasswdLength(PRInt32 newVal, PRInt32 *_retval); \
  NS_IMETHOD NZ_Initialize(PRInt32 *_retval); \
  NS_IMETHOD NZ_Close(PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_NotarizationServer(const PRUnichar *ServerName, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_HashAlg(const PRUnichar *HashAlg, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_DisplayDigitalID(PRInt32 DisplayID, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_CrlLocation(const PRUnichar *CrlLocation, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_ValidationPreference(PRInt32 ValPref, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_NotarizationDescription(const PRUnichar *Description, PRInt32 *_retval); \
  NS_IMETHOD NZ_NotarizeDocument(const PRUnichar *DocumentName, PRInt32 UIMask, PRInt32 ResponseType, PRUnichar **_retval); \
  NS_IMETHOD NZ_NotarizeHash(const PRUnichar *Hash, PRInt32 UIMask, PRUnichar **_retval); \
  NS_IMETHOD NZ_VerifyNotarizationRecord(const PRUnichar *Record, const PRUnichar *Document, PRInt32 RecordType, PRInt32 UIMask, PRInt32 *_retval); \
  NS_IMETHOD NZ_AddCertificate(const PRUnichar *Certificate, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_LogoUrl(const PRUnichar *LogoUrl, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileTitle(const PRUnichar *SelFileTitle, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileDescription(const PRUnichar *SelFileDesc, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileHelpUrl(const PRUnichar *SelFileHelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressTitle(const PRUnichar *ProgressTitle, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressDescription(const PRUnichar *ProgressDesc, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressHelpUrl(const PRUnichar *ProgressHelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptTitle(const PRUnichar *ReceiptTitle, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptDescription(const PRUnichar *ReceiptDesc, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptHelpUrl(const PRUnichar *ReceiptHelpUrl, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_UIPrefs_WizardTitle(const PRUnichar *WizardTitle, PRInt32 *_retval); \
  NS_IMETHOD Set_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRInt32 PreferenceType, const PRUnichar *PreferenceValue, PRInt32 *_retval); \
  NS_IMETHOD Get_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRUnichar **_retval); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NS6IPTA(_to) \
  NS_IMETHOD PTA_Initialize(const PRUnichar *AppCtxtName, PRInt32 UseCapi, PRInt32 *_retval) { return _to ## PTA_Initialize(AppCtxtName, UseCapi, _retval); } \
  NS_IMETHOD PTA_Close(PRInt32 *_retval) { return _to ## PTA_Close(_retval); } \
  NS_IMETHOD Set_PTA_AppPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval) { return _to ## Set_PTA_AppPreference(PrefName, Value, _retval); } \
  NS_IMETHOD Get_PTA_AppPreference(const PRUnichar *PrefName, PRUnichar **_retval) { return _to ## Get_PTA_AppPreference(PrefName, _retval); } \
  NS_IMETHOD Set_PTA_CSPName(const PRUnichar *CSPName, PRInt32 *_retval) { return _to ## Set_PTA_CSPName(CSPName, _retval); } \
  NS_IMETHOD Get_PTA_CSPName(PRUnichar **_retval) { return _to ## Get_PTA_CSPName(_retval); } \
  NS_IMETHOD PTA_CreateCertReq(const PRUnichar *SubjectDN, PRInt32 KeyGenFlag, PRInt32 HashAlg, PRUint32 count, const PRUnichar **Attribs, PRUnichar **_retval) { return _to ## PTA_CreateCertReq(SubjectDN, KeyGenFlag, HashAlg, count, Attribs, _retval); } \
  NS_IMETHOD PTA_InstallCert(const PRUnichar *Cert, PRInt32 *_retval) { return _to ## PTA_InstallCert(Cert, _retval); } \
  NS_IMETHOD PTA_InstallKeyPair(const PRUnichar *privKeyBlob, const PRUnichar *pkcs7Cert, PRInt32 *_retval) { return _to ## PTA_InstallKeyPair(privKeyBlob, pkcs7Cert, _retval); } \
  NS_IMETHOD PTA_SignChallenge(const PRUnichar *Challenge, PRInt32 AlgID, PRUnichar **_retval) { return _to ## PTA_SignChallenge(Challenge, AlgID, _retval); } \
  NS_IMETHOD PTA_SignTransaction(const PRUnichar *Message, PRInt32 AlgID, PRUnichar **_retval) { return _to ## PTA_SignTransaction(Message, AlgID, _retval); } \
  NS_IMETHOD PTA_SignRenewal(PRInt32 AlgID, PRUnichar **_retval) { return _to ## PTA_SignRenewal(AlgID, _retval); } \
  NS_IMETHOD PTA_SelectIDForTrans(PRInt32 *_retval) { return _to ## PTA_SelectIDForTrans(_retval); } \
  NS_IMETHOD PTA_SelectIDForChallenge(PRInt32 *_retval) { return _to ## PTA_SelectIDForChallenge(_retval); } \
  NS_IMETHOD Get_PTA_UseDefCertFlag(PRInt16 *_retval) { return _to ## Get_PTA_UseDefCertFlag(_retval); } \
  NS_IMETHOD Set_PTA_UseDefCertFlag(PRInt16 defCertFlag, PRInt32 *_retval) { return _to ## Set_PTA_UseDefCertFlag(defCertFlag, _retval); } \
  NS_IMETHOD Set_PTA_ProtocolName(const PRUnichar *protocolName, PRInt32 *_retval) { return _to ## Set_PTA_ProtocolName(protocolName, _retval); } \
  NS_IMETHOD Get_PTA_ProtocolName(PRUnichar **_retval) { return _to ## Get_PTA_ProtocolName(_retval); } \
  NS_IMETHOD Set_PTA_AuthDll(const PRUnichar *authDllName, PRInt32 *_retval) { return _to ## Set_PTA_AuthDll(authDllName, _retval); } \
  NS_IMETHOD Get_PTA_AuthDll(PRUnichar **_retval) { return _to ## Get_PTA_AuthDll(_retval); } \
  NS_IMETHOD Set_PTA_ProfileIssFrndlyName(const PRUnichar *profileIssFrndlyName, PRInt32 *_retval) { return _to ## Set_PTA_ProfileIssFrndlyName(profileIssFrndlyName, _retval); } \
  NS_IMETHOD Get_PTA_ProfileIssFrndlyName(PRUnichar **_retval) { return _to ## Get_PTA_ProfileIssFrndlyName(_retval); } \
  NS_IMETHOD Set_PTA_ProfileIssUniqueId(const PRUnichar *profileIssUniqId, PRInt32 *_retval) { return _to ## Set_PTA_ProfileIssUniqueId(profileIssUniqId, _retval); } \
  NS_IMETHOD Get_PTA_ProfileIssUniqueId(PRUnichar **_retval) { return _to ## Get_PTA_ProfileIssUniqueId(_retval); } \
  NS_IMETHOD Set_PTA_AffLogoUrl(const PRUnichar *affLogoUrl, PRInt32 *_retval) { return _to ## Set_PTA_AffLogoUrl(affLogoUrl, _retval); } \
  NS_IMETHOD Get_PTA_AffLogoUrl(PRUnichar **_retval) { return _to ## Get_PTA_AffLogoUrl(_retval); } \
  NS_IMETHOD Set_PTA_EnableCertForCapi(PRBool boolEnableForCapi, PRInt32 *_retval) { return _to ## Set_PTA_EnableCertForCapi(boolEnableForCapi, _retval); } \
  NS_IMETHOD Set_CertPref_CertSerNum(const PRUnichar *CertSerNum, PRInt32 *_retval) { return _to ## Set_CertPref_CertSerNum(CertSerNum, _retval); } \
  NS_IMETHOD Get_CertPref_CertSerNum(PRUnichar **_retval) { return _to ## Get_CertPref_CertSerNum(_retval); } \
  NS_IMETHOD Set_CertPref_CertIssDN(const PRUnichar *CertIssDN, PRInt32 *_retval) { return _to ## Set_CertPref_CertIssDN(CertIssDN, _retval); } \
  NS_IMETHOD Get_CertPref_CertIssDN(PRUnichar **_retval) { return _to ## Get_CertPref_CertIssDN(_retval); } \
  NS_IMETHOD Set_CertPref_CertFrndlyName(const PRUnichar *CertFrndlyName, PRInt32 *_retval) { return _to ## Set_CertPref_CertFrndlyName(CertFrndlyName, _retval); } \
  NS_IMETHOD Get_CertPref_CertFrndlyName(PRUnichar **_retval) { return _to ## Get_CertPref_CertFrndlyName(_retval); } \
  NS_IMETHOD Set_CertPref_CertLogoUrl(const PRUnichar *CertLogoUrl, PRInt32 *_retval) { return _to ## Set_CertPref_CertLogoUrl(CertLogoUrl, _retval); } \
  NS_IMETHOD Get_CertPref_CertLogoUrl(PRUnichar **_retval) { return _to ## Get_CertPref_CertLogoUrl(_retval); } \
  NS_IMETHOD Set_CertPref_CertDispString(const PRUnichar *CertDispString, PRInt32 *_retval) { return _to ## Set_CertPref_CertDispString(CertDispString, _retval); } \
  NS_IMETHOD Get_CertPref_CertDispString(PRUnichar **_retval) { return _to ## Get_CertPref_CertDispString(_retval); } \
  NS_IMETHOD Set_CertPref_CertTextureUrl(const PRUnichar *CertTextureUrl, PRInt32 *_retval) { return _to ## Set_CertPref_CertTextureUrl(CertTextureUrl, _retval); } \
  NS_IMETHOD Get_CertPref_CertTextureUrl(PRUnichar **_retval) { return _to ## Get_CertPref_CertTextureUrl(_retval); } \
  NS_IMETHOD Set_CertPref_MarkAsRenewed(PRBool boolMarkAsRenewed, PRInt32 *_retval) { return _to ## Set_CertPref_MarkAsRenewed(boolMarkAsRenewed, _retval); } \
  NS_IMETHOD Get_CertPref_MarkAsRenewed(PRBool *_retval) { return _to ## Get_CertPref_MarkAsRenewed(_retval); } \
  NS_IMETHOD Set_CertPref_SetPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval) { return _to ## Set_CertPref_SetPreference(PrefName, Value, _retval); } \
  NS_IMETHOD Get_CertPref_GetPreference(const PRUnichar *PrefName, PRUnichar **_retval) { return _to ## Get_CertPref_GetPreference(PrefName, _retval); } \
  NS_IMETHOD Set_ProfMgmt_PasswdQuality(PRInt32 PasswdQuality, PRInt32 *_retval) { return _to ## Set_ProfMgmt_PasswdQuality(PasswdQuality, _retval); } \
  NS_IMETHOD Get_ProfMgmt_PasswdQuality(PRInt32 *_retval) { return _to ## Get_ProfMgmt_PasswdQuality(_retval); } \
  NS_IMETHOD Set_ProfMgmt_PasswdLength(PRInt32 PasswdLength, PRInt32 *_retval) { return _to ## Set_ProfMgmt_PasswdLength(PasswdLength, _retval); } \
  NS_IMETHOD Get_ProfMgmt_PasswdLength(PRInt32 *_retval) { return _to ## Get_ProfMgmt_PasswdLength(_retval); } \
  NS_IMETHOD Set_ProfMgmt_PasswdTimeOut(PRInt32 PasswdTimeOut, PRInt32 *_retval) { return _to ## Set_ProfMgmt_PasswdTimeOut(PasswdTimeOut, _retval); } \
  NS_IMETHOD Get_ProfMgmt_PasswdTimeOut(PRInt32 *_retval) { return _to ## Get_ProfMgmt_PasswdTimeOut(_retval); } \
  NS_IMETHOD Set_ProfMgmt_PasswdLockOutTries(PRInt32 PasswdLockOutTries, PRInt32 *_retval) { return _to ## Set_ProfMgmt_PasswdLockOutTries(PasswdLockOutTries, _retval); } \
  NS_IMETHOD Get_ProfMgmt_PasswdLockOutTries(PRInt32 *_retval) { return _to ## Get_ProfMgmt_PasswdLockOutTries(_retval); } \
  NS_IMETHOD Set_ProfMgmt_PasswdUnLockPeriod(PRInt32 PasswdUnLockPeriod, PRInt32 *_retval) { return _to ## Set_ProfMgmt_PasswdUnLockPeriod(PasswdUnLockPeriod, _retval); } \
  NS_IMETHOD Get_ProfMgmt_PasswdUnLockPeriod(PRInt32 *_retval) { return _to ## Get_ProfMgmt_PasswdUnLockPeriod(_retval); } \
  NS_IMETHOD Set_ProfMgmt_ProfileName(const PRUnichar *ProfileName, PRInt32 *_retval) { return _to ## Set_ProfMgmt_ProfileName(ProfileName, _retval); } \
  NS_IMETHOD Get_ProfMgmt_ProfileName(PRUnichar **_retval) { return _to ## Get_ProfMgmt_ProfileName(_retval); } \
  NS_IMETHOD Set_ProfMgmt_Password(const PRUnichar *Password, PRInt32 *_retval) { return _to ## Set_ProfMgmt_Password(Password, _retval); } \
  NS_IMETHOD Set_ProfMgmt_SaveLocal(PRBool boolSaveLocal, PRInt32 *_retval) { return _to ## Set_ProfMgmt_SaveLocal(boolSaveLocal, _retval); } \
  NS_IMETHOD Get_ProfMgmt_SaveLocal(PRBool *_retval) { return _to ## Get_ProfMgmt_SaveLocal(_retval); } \
  NS_IMETHOD Set_ProfMgmt_RoamProfile(PRBool boolRoamProfile, PRInt32 *_retval) { return _to ## Set_ProfMgmt_RoamProfile(boolRoamProfile, _retval); } \
  NS_IMETHOD Get_ProfMgmt_RoamProfile(PRBool *_retval) { return _to ## Get_ProfMgmt_RoamProfile(_retval); } \
  NS_IMETHOD Set_ProfMgmt_OpenProfFlags(PRInt32 flags, PRInt32 *_retval) { return _to ## Set_ProfMgmt_OpenProfFlags(flags, _retval); } \
  NS_IMETHOD Get_ProfMgmt_OpenProfFlags(PRInt32 *_retval) { return _to ## Get_ProfMgmt_OpenProfFlags(_retval); } \
  NS_IMETHOD ProfMgmt_OpenProfile(PRInt32 *_retval) { return _to ## ProfMgmt_OpenProfile(_retval); } \
  NS_IMETHOD ProfMgmt_CloseProfile(PRInt32 *_retval) { return _to ## ProfMgmt_CloseProfile(_retval); } \
  NS_IMETHOD ProfMgmt_SaveProfile(PRInt32 *_retval) { return _to ## ProfMgmt_SaveProfile(_retval); } \
  NS_IMETHOD ProfMgmt_ChangePassword(PRInt32 *_retval) { return _to ## ProfMgmt_ChangePassword(_retval); } \
  NS_IMETHOD Set_SrchCrit_IssuerDN(const PRUnichar *IssuerDN, PRInt32 *_retval) { return _to ## Set_SrchCrit_IssuerDN(IssuerDN, _retval); } \
  NS_IMETHOD Get_SrchCrit_IssuerDN(PRUnichar **_retval) { return _to ## Get_SrchCrit_IssuerDN(_retval); } \
  NS_IMETHOD Set_SrchCrit_SubjectDN(const PRUnichar *SubjectDN, PRInt32 *_retval) { return _to ## Set_SrchCrit_SubjectDN(SubjectDN, _retval); } \
  NS_IMETHOD Get_SrchCrit_SubjectDN(PRUnichar **_retval) { return _to ## Get_SrchCrit_SubjectDN(_retval); } \
  NS_IMETHOD Set_SrchCrit_SerNum(const PRUnichar *SerNum, PRInt32 *_retval) { return _to ## Set_SrchCrit_SerNum(SerNum, _retval); } \
  NS_IMETHOD Get_SrchCrit_SerNum(PRUnichar **_retval) { return _to ## Get_SrchCrit_SerNum(_retval); } \
  NS_IMETHOD Set_SrchCrit_Email(const PRUnichar *Email, PRInt32 *_retval) { return _to ## Set_SrchCrit_Email(Email, _retval); } \
  NS_IMETHOD Get_SrchCrit_Email(PRUnichar **_retval) { return _to ## Get_SrchCrit_Email(_retval); } \
  NS_IMETHOD Set_SrchCrit_ExpDate(PRUint64 ExpDate, PRInt32 *_retval) { return _to ## Set_SrchCrit_ExpDate(ExpDate, _retval); } \
  NS_IMETHOD Get_SrchCrit_ExpDate(PRUint64 *_retval) { return _to ## Get_SrchCrit_ExpDate(_retval); } \
  NS_IMETHOD Set_SrchCrit_EffDate(PRUint64 EffDate, PRInt32 *_retval) { return _to ## Set_SrchCrit_EffDate(EffDate, _retval); } \
  NS_IMETHOD Get_SrchCrit_EffDate(PRUint64 *_retval) { return _to ## Get_SrchCrit_EffDate(_retval); } \
  NS_IMETHOD Set_SrchCrit_DateEquality(PRInt16 DateEquality, PRInt32 *_retval) { return _to ## Set_SrchCrit_DateEquality(DateEquality, _retval); } \
  NS_IMETHOD Get_SrchCrit_DateEquality(PRInt16 *_retval) { return _to ## Get_SrchCrit_DateEquality(_retval); } \
  NS_IMETHOD Set_SrchCrit_Renewed(PRBool Renewed, PRInt32 *_retval) { return _to ## Set_SrchCrit_Renewed(Renewed, _retval); } \
  NS_IMETHOD Get_SrchCrit_Renewed(PRBool *_retval) { return _to ## Get_SrchCrit_Renewed(_retval); } \
  NS_IMETHOD Set_SrchCrit_KeyUsage(PRInt16 KeyUsage, PRInt32 *_retval) { return _to ## Set_SrchCrit_KeyUsage(KeyUsage, _retval); } \
  NS_IMETHOD Get_SrchCrit_KeyUsage(PRInt16 *_retval) { return _to ## Get_SrchCrit_KeyUsage(_retval); } \
  NS_IMETHOD Set_SrchCrit_KeySize(PRInt16 KeySize, PRInt32 *_retval) { return _to ## Set_SrchCrit_KeySize(KeySize, _retval); } \
  NS_IMETHOD Get_SrchCrit_KeySize(PRInt16 *_retval) { return _to ## Get_SrchCrit_KeySize(_retval); } \
  NS_IMETHOD Set_SrchCrit_ExtOID(const PRUnichar *ExtOID, PRInt32 *_retval) { return _to ## Set_SrchCrit_ExtOID(ExtOID, _retval); } \
  NS_IMETHOD Get_SrchCrit_ExtOID(PRUnichar **_retval) { return _to ## Get_SrchCrit_ExtOID(_retval); } \
  NS_IMETHOD Set_SrchCrit_ExtVal(const PRUnichar *ExtVal, PRInt32 *_retval) { return _to ## Set_SrchCrit_ExtVal(ExtVal, _retval); } \
  NS_IMETHOD Get_SrchCrit_ExtVal(PRUnichar **_retval) { return _to ## Get_SrchCrit_ExtVal(_retval); } \
  NS_IMETHOD Set_UIPrefs_Language(PRInt32 Language, PRInt32 *_retval) { return _to ## Set_UIPrefs_Language(Language, _retval); } \
  NS_IMETHOD Get_UIPrefs_Language(PRInt32 *_retval) { return _to ## Get_UIPrefs_Language(_retval); } \
  NS_IMETHOD Set_UIPrefs_TitleFont(const PRUnichar *TitleFont, PRInt32 *_retval) { return _to ## Set_UIPrefs_TitleFont(TitleFont, _retval); } \
  NS_IMETHOD Get_UIPrefs_TitleFont(PRUnichar **_retval) { return _to ## Get_UIPrefs_TitleFont(_retval); } \
  NS_IMETHOD Set_UIPrefs_TextFont(const PRUnichar *TextFont, PRInt32 *_retval) { return _to ## Set_UIPrefs_TextFont(TextFont, _retval); } \
  NS_IMETHOD Get_UIPrefs_TextFont(PRUnichar **_retval) { return _to ## Get_UIPrefs_TextFont(_retval); } \
  NS_IMETHOD Set_UIPrefs_BtnFont(const PRUnichar *BtnFont, PRInt32 *_retval) { return _to ## Set_UIPrefs_BtnFont(BtnFont, _retval); } \
  NS_IMETHOD Get_UIPrefs_BtnFont(PRUnichar **_retval) { return _to ## Get_UIPrefs_BtnFont(_retval); } \
  NS_IMETHOD Set_UIPrefs_UILogoUrl(const PRUnichar *UILogoUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_UILogoUrl(UILogoUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_UILogoUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_UILogoUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_NewPasswd_Title(const PRUnichar *NewPasswd_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_NewPasswd_Title(NewPasswd_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_NewPasswd_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_NewPasswd_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_NewPasswd_Text(const PRUnichar *NewPasswd_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_NewPasswd_Text(NewPasswd_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_NewPasswd_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_NewPasswd_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_NewPasswd_OKBtnText(PRInt32 NewPasswd_OKBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_NewPasswd_OKBtnText(NewPasswd_OKBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_NewPasswd_OKBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_NewPasswd_OKBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_NewPasswd_CancelBtnText(PRInt32 NewPasswd_CancelBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_NewPasswd_CancelBtnText(NewPasswd_CancelBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_NewPasswd_CancelBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_NewPasswd_CancelBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_NewPasswd_HelpUrl(const PRUnichar *NewPasswd_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_NewPasswd_HelpUrl(NewPasswd_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_NewPasswd_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_NewPasswd_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_LgnDlg_Title(const PRUnichar *LgnDlg_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_LgnDlg_Title(LgnDlg_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_LgnDlg_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_LgnDlg_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_OpenProf_Title(const PRUnichar *OpenProf_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_OpenProf_Title(OpenProf_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_OpenProf_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_OpenProf_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_OpenProf_Text(const PRUnichar *OpenProf_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_OpenProf_Text(OpenProf_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_OpenProf_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_OpenProf_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_OpenProf_OKBtnText(PRInt32 OpenProf_OKBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_OpenProf_OKBtnText(OpenProf_OKBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_OpenProf_OKBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_OpenProf_OKBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_OpenProf_CancelBtnText(PRInt32 OpenProf_CancelBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_OpenProf_CancelBtnText(OpenProf_CancelBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_OpenProf_CancelBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_OpenProf_CancelBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_OpenProf_HelpUrl(const PRUnichar *OpenProf_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_OpenProf_HelpUrl(OpenProf_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_OpenProf_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_OpenProf_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_Title(const PRUnichar *SelID_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_Title(SelID_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_SelID_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_Text(const PRUnichar *SelID_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_Text(SelID_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_SelID_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_OKBtnText(PRInt32 SelID_OKBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_OKBtnText(SelID_OKBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_OKBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_SelID_OKBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_CancelBtnText(PRInt32 SelID_CancelBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_CancelBtnText(SelID_CancelBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_CancelBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_SelID_CancelBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_ShowDefChkBox(PRBool SelID_ShowDefChkBox, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_ShowDefChkBox(SelID_ShowDefChkBox, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_ShowDefChkBox(PRBool *_retval) { return _to ## Get_UIPrefs_SelID_ShowDefChkBox(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_ChkBoxText(const PRUnichar *SelID_ChkBoxText, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_ChkBoxText(SelID_ChkBoxText, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_ChkBoxText(PRUnichar **_retval) { return _to ## Get_UIPrefs_SelID_ChkBoxText(_retval); } \
  NS_IMETHOD Set_UIPrefs_SelID_HelpUrl(const PRUnichar *SelID_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_SelID_HelpUrl(SelID_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_SelID_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_SelID_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_SgnDlg_Title(const PRUnichar *SgnDlg_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_SgnDlg_Title(SgnDlg_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_SgnDlg_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_SgnDlg_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_RvwMsg_Text(const PRUnichar *RvwMsg_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_RvwMsg_Text(RvwMsg_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_RvwMsg_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_RvwMsg_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_RvwMsg_OKBtnText(PRInt32 RvwMsg_OKBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_RvwMsg_OKBtnText(RvwMsg_OKBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_RvwMsg_OKBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_RvwMsg_OKBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_RvwMsg_Title(const PRUnichar *RvwMsg_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_RvwMsg_Title(RvwMsg_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_RvwMsg_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_RvwMsg_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_RvwMsg_CancelBtnText(PRInt32 RvwMsg_CancelBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_RvwMsg_CancelBtnText(RvwMsg_CancelBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_RvwMsg_CancelBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_RvwMsg_CancelBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_RvwMsg_HelpUrl(const PRUnichar *RvwMsg_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_RvwMsg_HelpUrl(RvwMsg_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_RvwMsg_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_RvwMsg_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_IntroDlg_Title(const PRUnichar *IntroDlg_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_IntroDlg_Title(IntroDlg_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_IntroDlg_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_IntroDlg_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_IntroDlg_Text(const PRUnichar *IntroDlg_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_IntroDlg_Text(IntroDlg_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_IntroDlg_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_IntroDlg_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_IntroDlg_HelpUrl(const PRUnichar *IntroDlg_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_IntroDlg_HelpUrl(IntroDlg_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_IntroDlg_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_IntroDlg_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_CreateNewProf_Title(const PRUnichar *CreateNewProf_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_CreateNewProf_Title(CreateNewProf_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_CreateNewProf_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_CreateNewProf_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Title(const PRUnichar *ChangePasswd_Title, PRInt32 *_retval) { return _to ## Set_UIPrefs_ChangePasswd_Title(ChangePasswd_Title, _retval); } \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Title(PRUnichar **_retval) { return _to ## Get_UIPrefs_ChangePasswd_Title(_retval); } \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_Text(const PRUnichar *ChangePasswd_Text, PRInt32 *_retval) { return _to ## Set_UIPrefs_ChangePasswd_Text(ChangePasswd_Text, _retval); } \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_Text(PRUnichar **_retval) { return _to ## Get_UIPrefs_ChangePasswd_Text(_retval); } \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_OKBtnText(PRInt32 ChangePasswd_OKBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_ChangePasswd_OKBtnText(ChangePasswd_OKBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_OKBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_ChangePasswd_OKBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 ChangePasswd_CancelBtnText, PRInt32 *_retval) { return _to ## Set_UIPrefs_ChangePasswd_CancelBtnText(ChangePasswd_CancelBtnText, _retval); } \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 *_retval) { return _to ## Get_UIPrefs_ChangePasswd_CancelBtnText(_retval); } \
  NS_IMETHOD Set_UIPrefs_ChangePasswd_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_ChangePasswd_HelpUrl(ChangePasswd_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_ChangePasswd_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_ChangePasswd_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_Timeout_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval) { return _to ## Set_UIPrefs_Timeout_HelpUrl(ChangePasswd_HelpUrl, _retval); } \
  NS_IMETHOD Get_UIPrefs_Timeout_HelpUrl(PRUnichar **_retval) { return _to ## Get_UIPrefs_Timeout_HelpUrl(_retval); } \
  NS_IMETHOD Set_UIPrefs_EnableTopMostWindow(PRBool boolEnableTopMost, PRInt32 *_retval) { return _to ## Set_UIPrefs_EnableTopMostWindow(boolEnableTopMost, _retval); } \
  NS_IMETHOD Set_UIPrefs_SignTransDlgWidth(PRInt32 nWidth, PRInt32 *_retval) { return _to ## Set_UIPrefs_SignTransDlgWidth(nWidth, _retval); } \
  NS_IMETHOD Get_UIPrefs_SignTransDlgWidth(PRInt32 *_retval) { return _to ## Get_UIPrefs_SignTransDlgWidth(_retval); } \
  NS_IMETHOD Set_UIPrefs_SignTransDlgHeight(PRInt32 nHeight, PRInt32 *_retval) { return _to ## Set_UIPrefs_SignTransDlgHeight(nHeight, _retval); } \
  NS_IMETHOD Get_UIPrefs_SignTransDlgHeight(PRInt32 *_retval) { return _to ## Get_UIPrefs_SignTransDlgHeight(_retval); } \
  NS_IMETHOD Get_SelectedDigID_IssuerDN(PRUnichar **_retval) { return _to ## Get_SelectedDigID_IssuerDN(_retval); } \
  NS_IMETHOD Get_SelectedDigID_SubjectDN(PRUnichar **_retval) { return _to ## Get_SelectedDigID_SubjectDN(_retval); } \
  NS_IMETHOD Get_SelectedDigID_SerNum(PRUnichar **_retval) { return _to ## Get_SelectedDigID_SerNum(_retval); } \
  NS_IMETHOD Get_SelectedDigID_ExpDate(PRUint64 *_retval) { return _to ## Get_SelectedDigID_ExpDate(_retval); } \
  NS_IMETHOD Get_SelectedDigID_EffDate(PRUint64 *_retval) { return _to ## Get_SelectedDigID_EffDate(_retval); } \
  NS_IMETHOD Get_SelectedDigID_KeyUsage(PRInt16 *_retval) { return _to ## Get_SelectedDigID_KeyUsage(_retval); } \
  NS_IMETHOD Get_SelectedDigID_KeySize(PRInt16 *_retval) { return _to ## Get_SelectedDigID_KeySize(_retval); } \
  NS_IMETHOD Get_SelectedDigID_Renewed(PRBool *_retval) { return _to ## Get_SelectedDigID_Renewed(_retval); } \
  NS_IMETHOD Get_SelectedDigID_PubKeyMD5(PRUnichar **_retval) { return _to ## Get_SelectedDigID_PubKeyMD5(_retval); } \
  NS_IMETHOD Get_SelectedDigID_PubKeySHA1(PRUnichar **_retval) { return _to ## Get_SelectedDigID_PubKeySHA1(_retval); } \
  NS_IMETHOD Get_SelectedDigID_FrndlyName(PRUnichar **_retval) { return _to ## Get_SelectedDigID_FrndlyName(_retval); } \
  NS_IMETHOD Get_SelectedDigID_LogoUrl(PRUnichar **_retval) { return _to ## Get_SelectedDigID_LogoUrl(_retval); } \
  NS_IMETHOD Get_SelectedDigID_TextureUrl(PRUnichar **_retval) { return _to ## Get_SelectedDigID_TextureUrl(_retval); } \
  NS_IMETHOD Set_RoamPrefs_NumOfSrvrs(PRInt16 NumOfSrvrs, PRInt32 *_retval) { return _to ## Set_RoamPrefs_NumOfSrvrs(NumOfSrvrs, _retval); } \
  NS_IMETHOD Get_RoamPrefs_NumOfSrvrs(PRInt16 *_retval) { return _to ## Get_RoamPrefs_NumOfSrvrs(_retval); } \
  NS_IMETHOD Set_RoamPrefs_StorageSrvr(const PRUnichar *StorageSrvr, PRInt32 *_retval) { return _to ## Set_RoamPrefs_StorageSrvr(StorageSrvr, _retval); } \
  NS_IMETHOD Get_RoamPrefs_StorageSrvr(PRUnichar **_retval) { return _to ## Get_RoamPrefs_StorageSrvr(_retval); } \
  NS_IMETHOD Set_RoamPrefs_ClientInfo(const PRUnichar *ClientInfo, PRInt32 *_retval) { return _to ## Set_RoamPrefs_ClientInfo(ClientInfo, _retval); } \
  NS_IMETHOD Get_RoamPrefs_ClientInfo(PRUnichar **_retval) { return _to ## Get_RoamPrefs_ClientInfo(_retval); } \
  NS_IMETHOD Set_RoamPrefs_ClientInfoSig(const PRUnichar *ClientInfoSig, PRInt32 *_retval) { return _to ## Set_RoamPrefs_ClientInfoSig(ClientInfoSig, _retval); } \
  NS_IMETHOD Get_RoamPrefs_ClientInfoSig(PRUnichar **_retval) { return _to ## Get_RoamPrefs_ClientInfoSig(_retval); } \
  NS_IMETHOD Set_XEnroll_ProviderType(PRInt32 nProviderType, PRInt32 *_retval) { return _to ## Set_XEnroll_ProviderType(nProviderType, _retval); } \
  NS_IMETHOD Get_XEnroll_ProviderType(PRInt32 *_retval) { return _to ## Get_XEnroll_ProviderType(_retval); } \
  NS_IMETHOD Set_XEnroll_GenKeyFlags(PRInt32 nGenKeyFlags, PRInt32 *_retval) { return _to ## Set_XEnroll_GenKeyFlags(nGenKeyFlags, _retval); } \
  NS_IMETHOD Get_XEnroll_GenKeyFlags(PRInt32 *_retval) { return _to ## Get_XEnroll_GenKeyFlags(_retval); } \
  NS_IMETHOD Set_XEnroll_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval) { return _to ## Set_XEnroll_ProviderName(szProviderName, _retval); } \
  NS_IMETHOD Get_XEnroll_ProviderName(PRUnichar **_retval) { return _to ## Get_XEnroll_ProviderName(_retval); } \
  NS_IMETHOD Set_XEnroll_HashAlgorithm(const PRUnichar *szHashAlgo, PRInt32 *_retval) { return _to ## Set_XEnroll_HashAlgorithm(szHashAlgo, _retval); } \
  NS_IMETHOD Get_XEnroll_HashAlgorithm(PRUnichar **_retval) { return _to ## Get_XEnroll_HashAlgorithm(_retval); } \
  NS_IMETHOD Set_XEnroll_KeySpec(PRInt32 nKeySpec, PRInt32 *_retval) { return _to ## Set_XEnroll_KeySpec(nKeySpec, _retval); } \
  NS_IMETHOD Get_XEnroll_KeySpec(PRInt32 *_retval) { return _to ## Get_XEnroll_KeySpec(_retval); } \
  NS_IMETHOD Set_XEnroll_DeleteRequestCert(PRBool boolFlag, PRInt32 *_retval) { return _to ## Set_XEnroll_DeleteRequestCert(boolFlag, _retval); } \
  NS_IMETHOD Get_XEnroll_DeleteRequestCert(PRBool *_retval) { return _to ## Get_XEnroll_DeleteRequestCert(_retval); } \
  NS_IMETHOD Set_XEnroll_WriteCertToCSP(PRBool boolFlag, PRInt32 *_retval) { return _to ## Set_XEnroll_WriteCertToCSP(boolFlag, _retval); } \
  NS_IMETHOD Get_XEnroll_WriteCertToCSP(PRBool *_retval) { return _to ## Get_XEnroll_WriteCertToCSP(_retval); } \
  NS_IMETHOD XEnroll_enumProviders(PRInt32 nIndex, PRInt32 nFlags, PRUnichar **_retval) { return _to ## XEnroll_enumProviders(nIndex, nFlags, _retval); } \
  NS_IMETHOD XEnroll_createPKCS10(const PRUnichar *szDNName, const PRUnichar *szUsage, PRUnichar **_retval) { return _to ## XEnroll_createPKCS10(szDNName, szUsage, _retval); } \
  NS_IMETHOD XEnroll_acceptPKCS7(const PRUnichar *szPKCS7, PRInt32 *_retval) { return _to ## XEnroll_acceptPKCS7(szPKCS7, _retval); } \
  NS_IMETHOD GetLastError(PRUint32 *_retval) { return _to ## GetLastError(_retval); } \
  NS_IMETHOD VSImport_Import(const PRUnichar *PKCS12, const PRUnichar *PKCS7, PRUnichar **szErrCodeString, PRInt32 *_retval) { return _to ## VSImport_Import(PKCS12, PKCS7, szErrCodeString, _retval); } \
  NS_IMETHOD VSImport_set_KeyExportable(PRInt32 nFlag, PRInt32 *_retval) { return _to ## VSImport_set_KeyExportable(nFlag, _retval); } \
  NS_IMETHOD VSImport_get_KeyExportable(PRInt32 *_retval) { return _to ## VSImport_get_KeyExportable(_retval); } \
  NS_IMETHOD VSImport_set_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval) { return _to ## VSImport_set_ProviderName(szProviderName, _retval); } \
  NS_IMETHOD VSImport_get_ProviderName(PRUnichar **_retval) { return _to ## VSImport_get_ProviderName(_retval); } \
  NS_IMETHOD AddRootCerts_Initialize(PRInt32 *_retval) { return _to ## AddRootCerts_Initialize(_retval); } \
  NS_IMETHOD AddRootCerts_CreateStandardTrustProfile(PRInt32 *_retval) { return _to ## AddRootCerts_CreateStandardTrustProfile(_retval); } \
  NS_IMETHOD AddRootCerts_CreateVerisignTrustProfile(PRInt32 *_retval) { return _to ## AddRootCerts_CreateVerisignTrustProfile(_retval); } \
  NS_IMETHOD P12Import_ImportP12(PRInt32 nType, const PRUnichar *strP12, PRUnichar **strSerialNum, PRUnichar **strIssuerDN, PRInt32 *_retval) { return _to ## P12Import_ImportP12(nType, strP12, strSerialNum, strIssuerDN, _retval); } \
  NS_IMETHOD P12Export_ExportP12(PRInt32 nOutputType, PRInt32 nFlags, const PRUnichar *strFile, PRInt32 *_retval) { return _to ## P12Export_ExportP12(nOutputType, nFlags, strFile, _retval); } \
  NS_IMETHOD Get_P12Export_PasswdQuality(PRInt32 *_retval) { return _to ## Get_P12Export_PasswdQuality(_retval); } \
  NS_IMETHOD Set_P12Export_PasswdQuality(PRInt32 newVal, PRInt32 *_retval) { return _to ## Set_P12Export_PasswdQuality(newVal, _retval); } \
  NS_IMETHOD Get_P12Export_PasswdLength(PRInt32 *_retval) { return _to ## Get_P12Export_PasswdLength(_retval); } \
  NS_IMETHOD Set_P12Export_PasswdLength(PRInt32 newVal, PRInt32 *_retval) { return _to ## Set_P12Export_PasswdLength(newVal, _retval); } \
  NS_IMETHOD NZ_Initialize(PRInt32 *_retval) { return _to ## NZ_Initialize(_retval); } \
  NS_IMETHOD NZ_Close(PRInt32 *_retval) { return _to ## NZ_Close(_retval); } \
  NS_IMETHOD Set_NZ_NotarizationServer(const PRUnichar *ServerName, PRInt32 *_retval) { return _to ## Set_NZ_NotarizationServer(ServerName, _retval); } \
  NS_IMETHOD Set_NZ_HashAlg(const PRUnichar *HashAlg, PRInt32 *_retval) { return _to ## Set_NZ_HashAlg(HashAlg, _retval); } \
  NS_IMETHOD Set_NZ_DisplayDigitalID(PRInt32 DisplayID, PRInt32 *_retval) { return _to ## Set_NZ_DisplayDigitalID(DisplayID, _retval); } \
  NS_IMETHOD Set_NZ_CrlLocation(const PRUnichar *CrlLocation, PRInt32 *_retval) { return _to ## Set_NZ_CrlLocation(CrlLocation, _retval); } \
  NS_IMETHOD Set_NZ_ValidationPreference(PRInt32 ValPref, PRInt32 *_retval) { return _to ## Set_NZ_ValidationPreference(ValPref, _retval); } \
  NS_IMETHOD Set_NZ_NotarizationDescription(const PRUnichar *Description, PRInt32 *_retval) { return _to ## Set_NZ_NotarizationDescription(Description, _retval); } \
  NS_IMETHOD NZ_NotarizeDocument(const PRUnichar *DocumentName, PRInt32 UIMask, PRInt32 ResponseType, PRUnichar **_retval) { return _to ## NZ_NotarizeDocument(DocumentName, UIMask, ResponseType, _retval); } \
  NS_IMETHOD NZ_NotarizeHash(const PRUnichar *Hash, PRInt32 UIMask, PRUnichar **_retval) { return _to ## NZ_NotarizeHash(Hash, UIMask, _retval); } \
  NS_IMETHOD NZ_VerifyNotarizationRecord(const PRUnichar *Record, const PRUnichar *Document, PRInt32 RecordType, PRInt32 UIMask, PRInt32 *_retval) { return _to ## NZ_VerifyNotarizationRecord(Record, Document, RecordType, UIMask, _retval); } \
  NS_IMETHOD NZ_AddCertificate(const PRUnichar *Certificate, PRInt32 *_retval) { return _to ## NZ_AddCertificate(Certificate, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_LogoUrl(const PRUnichar *LogoUrl, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_LogoUrl(LogoUrl, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileTitle(const PRUnichar *SelFileTitle, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_SelFileTitle(SelFileTitle, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileDescription(const PRUnichar *SelFileDesc, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_SelFileDescription(SelFileDesc, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_SelFileHelpUrl(const PRUnichar *SelFileHelpUrl, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_SelFileHelpUrl(SelFileHelpUrl, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressTitle(const PRUnichar *ProgressTitle, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ProgressTitle(ProgressTitle, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressDescription(const PRUnichar *ProgressDesc, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ProgressDescription(ProgressDesc, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ProgressHelpUrl(const PRUnichar *ProgressHelpUrl, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ProgressHelpUrl(ProgressHelpUrl, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptTitle(const PRUnichar *ReceiptTitle, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ReceiptTitle(ReceiptTitle, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptDescription(const PRUnichar *ReceiptDesc, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ReceiptDescription(ReceiptDesc, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_ReceiptHelpUrl(const PRUnichar *ReceiptHelpUrl, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_ReceiptHelpUrl(ReceiptHelpUrl, _retval); } \
  NS_IMETHOD Set_NZ_UIPrefs_WizardTitle(const PRUnichar *WizardTitle, PRInt32 *_retval) { return _to ## Set_NZ_UIPrefs_WizardTitle(WizardTitle, _retval); } \
  NS_IMETHOD Set_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRInt32 PreferenceType, const PRUnichar *PreferenceValue, PRInt32 *_retval) { return _to ## Set_NZ_ApplicationPreference(ApplicationName, PreferenceName, PreferenceType, PreferenceValue, _retval); } \
  NS_IMETHOD Get_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRUnichar **_retval) { return _to ## Get_NZ_ApplicationPreference(ApplicationName, PreferenceName, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public ns6IPTA
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NS6IPTA

  _MYCLASS_();
  virtual ~_MYCLASS_();
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, ns6IPTA)

_MYCLASS_::_MYCLASS_()
{
  NS_INIT_ISUPPORTS();
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* long PTA_Initialize (in wstring AppCtxtName, in long UseCapi); */
NS_IMETHODIMP _MYCLASS_::PTA_Initialize(const PRUnichar *AppCtxtName, PRInt32 UseCapi, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long PTA_Close (); */
NS_IMETHODIMP _MYCLASS_::PTA_Close(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_AppPreference (in wstring PrefName, in wstring Value); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_AppPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_AppPreference (in wstring PrefName); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_AppPreference(const PRUnichar *PrefName, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_CSPName (in wstring CSPName); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_CSPName(const PRUnichar *CSPName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_CSPName (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_CSPName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring PTA_CreateCertReq (in wstring SubjectDN, in long KeyGenFlag, in long HashAlg, in unsigned long count, [array, size_is (count)] in wstring Attribs); */
NS_IMETHODIMP _MYCLASS_::PTA_CreateCertReq(const PRUnichar *SubjectDN, PRInt32 KeyGenFlag, PRInt32 HashAlg, PRUint32 count, const PRUnichar **Attribs, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long PTA_InstallCert (in wstring Cert); */
NS_IMETHODIMP _MYCLASS_::PTA_InstallCert(const PRUnichar *Cert, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long PTA_InstallKeyPair (in wstring privKeyBlob, in wstring pkcs7Cert); */
NS_IMETHODIMP _MYCLASS_::PTA_InstallKeyPair(const PRUnichar *privKeyBlob, const PRUnichar *pkcs7Cert, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring PTA_SignChallenge (in wstring Challenge, in long AlgID); */
NS_IMETHODIMP _MYCLASS_::PTA_SignChallenge(const PRUnichar *Challenge, PRInt32 AlgID, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring PTA_SignTransaction (in wstring Message, in long AlgID); */
NS_IMETHODIMP _MYCLASS_::PTA_SignTransaction(const PRUnichar *Message, PRInt32 AlgID, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring PTA_SignRenewal (in long AlgID); */
NS_IMETHODIMP _MYCLASS_::PTA_SignRenewal(PRInt32 AlgID, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long PTA_SelectIDForTrans (); */
NS_IMETHODIMP _MYCLASS_::PTA_SelectIDForTrans(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long PTA_SelectIDForChallenge (); */
NS_IMETHODIMP _MYCLASS_::PTA_SelectIDForChallenge(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_PTA_UseDefCertFlag (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_UseDefCertFlag(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_UseDefCertFlag (in short defCertFlag); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_UseDefCertFlag(PRInt16 defCertFlag, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_ProtocolName (in wstring protocolName); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_ProtocolName(const PRUnichar *protocolName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_ProtocolName (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_ProtocolName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_AuthDll (in wstring authDllName); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_AuthDll(const PRUnichar *authDllName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_AuthDll (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_AuthDll(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_ProfileIssFrndlyName (in wstring profileIssFrndlyName); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_ProfileIssFrndlyName(const PRUnichar *profileIssFrndlyName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_ProfileIssFrndlyName (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_ProfileIssFrndlyName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_ProfileIssUniqueId (in wstring profileIssUniqId); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_ProfileIssUniqueId(const PRUnichar *profileIssUniqId, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_ProfileIssUniqueId (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_ProfileIssUniqueId(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_AffLogoUrl (in wstring affLogoUrl); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_AffLogoUrl(const PRUnichar *affLogoUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_PTA_AffLogoUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_PTA_AffLogoUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_PTA_EnableCertForCapi (in boolean boolEnableForCapi); */
NS_IMETHODIMP _MYCLASS_::Set_PTA_EnableCertForCapi(PRBool boolEnableForCapi, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertSerNum (in wstring CertSerNum); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertSerNum(const PRUnichar *CertSerNum, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertSerNum (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertSerNum(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertIssDN (in wstring CertIssDN); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertIssDN(const PRUnichar *CertIssDN, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertIssDN (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertIssDN(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertFrndlyName (in wstring CertFrndlyName); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertFrndlyName(const PRUnichar *CertFrndlyName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertFrndlyName (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertFrndlyName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertLogoUrl (in wstring CertLogoUrl); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertLogoUrl(const PRUnichar *CertLogoUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertLogoUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertLogoUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertDispString (in wstring CertDispString); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertDispString(const PRUnichar *CertDispString, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertDispString (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertDispString(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_CertTextureUrl (in wstring CertTextureUrl); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_CertTextureUrl(const PRUnichar *CertTextureUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_CertTextureUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_CertTextureUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_MarkAsRenewed (in boolean boolMarkAsRenewed); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_MarkAsRenewed(PRBool boolMarkAsRenewed, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_CertPref_MarkAsRenewed (); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_MarkAsRenewed(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_CertPref_SetPreference (in wstring PrefName, in wstring Value); */
NS_IMETHODIMP _MYCLASS_::Set_CertPref_SetPreference(const PRUnichar *PrefName, const PRUnichar *Value, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_CertPref_GetPreference (in wstring PrefName); */
NS_IMETHODIMP _MYCLASS_::Get_CertPref_GetPreference(const PRUnichar *PrefName, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_PasswdQuality (in long PasswdQuality); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_PasswdQuality(PRInt32 PasswdQuality, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_PasswdQuality (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_PasswdQuality(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_PasswdLength (in long PasswdLength); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_PasswdLength(PRInt32 PasswdLength, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_PasswdLength (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_PasswdLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_PasswdTimeOut (in long PasswdTimeOut); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_PasswdTimeOut(PRInt32 PasswdTimeOut, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_PasswdTimeOut (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_PasswdTimeOut(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_PasswdLockOutTries (in long PasswdLockOutTries); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_PasswdLockOutTries(PRInt32 PasswdLockOutTries, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_PasswdLockOutTries (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_PasswdLockOutTries(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_PasswdUnLockPeriod (in long PasswdUnLockPeriod); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_PasswdUnLockPeriod(PRInt32 PasswdUnLockPeriod, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_PasswdUnLockPeriod (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_PasswdUnLockPeriod(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_ProfileName (in wstring ProfileName); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_ProfileName(const PRUnichar *ProfileName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_ProfMgmt_ProfileName (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_ProfileName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_Password (in wstring Password); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_Password(const PRUnichar *Password, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_SaveLocal (in boolean boolSaveLocal); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_SaveLocal(PRBool boolSaveLocal, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_ProfMgmt_SaveLocal (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_SaveLocal(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_RoamProfile (in boolean boolRoamProfile); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_RoamProfile(PRBool boolRoamProfile, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_ProfMgmt_RoamProfile (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_RoamProfile(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_ProfMgmt_OpenProfFlags (in long flags); */
NS_IMETHODIMP _MYCLASS_::Set_ProfMgmt_OpenProfFlags(PRInt32 flags, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_ProfMgmt_OpenProfFlags (); */
NS_IMETHODIMP _MYCLASS_::Get_ProfMgmt_OpenProfFlags(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long ProfMgmt_OpenProfile (); */
NS_IMETHODIMP _MYCLASS_::ProfMgmt_OpenProfile(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long ProfMgmt_CloseProfile (); */
NS_IMETHODIMP _MYCLASS_::ProfMgmt_CloseProfile(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long ProfMgmt_SaveProfile (); */
NS_IMETHODIMP _MYCLASS_::ProfMgmt_SaveProfile(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long ProfMgmt_ChangePassword (); */
NS_IMETHODIMP _MYCLASS_::ProfMgmt_ChangePassword(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_IssuerDN (in wstring IssuerDN); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_IssuerDN(const PRUnichar *IssuerDN, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_IssuerDN (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_IssuerDN(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_SubjectDN (in wstring SubjectDN); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_SubjectDN(const PRUnichar *SubjectDN, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_SubjectDN (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_SubjectDN(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_SerNum (in wstring SerNum); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_SerNum(const PRUnichar *SerNum, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_SerNum (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_SerNum(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_Email (in wstring Email); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_Email(const PRUnichar *Email, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_Email (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_Email(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_ExpDate (in unsigned long long ExpDate); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_ExpDate(PRUint64 ExpDate, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long long get_SrchCrit_ExpDate (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_ExpDate(PRUint64 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_EffDate (in unsigned long long EffDate); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_EffDate(PRUint64 EffDate, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long long get_SrchCrit_EffDate (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_EffDate(PRUint64 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_DateEquality (in short DateEquality); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_DateEquality(PRInt16 DateEquality, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_SrchCrit_DateEquality (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_DateEquality(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_Renewed (in boolean Renewed); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_Renewed(PRBool Renewed, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_SrchCrit_Renewed (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_Renewed(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_KeyUsage (in short KeyUsage); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_KeyUsage(PRInt16 KeyUsage, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_SrchCrit_KeyUsage (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_KeyUsage(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_KeySize (in short KeySize); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_KeySize(PRInt16 KeySize, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_SrchCrit_KeySize (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_KeySize(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_ExtOID (in wstring ExtOID); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_ExtOID(const PRUnichar *ExtOID, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_ExtOID (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_ExtOID(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_SrchCrit_ExtVal (in wstring ExtVal); */
NS_IMETHODIMP _MYCLASS_::Set_SrchCrit_ExtVal(const PRUnichar *ExtVal, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SrchCrit_ExtVal (); */
NS_IMETHODIMP _MYCLASS_::Get_SrchCrit_ExtVal(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_Language (in long Language); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_Language(PRInt32 Language, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_Language (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_Language(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_TitleFont (in wstring TitleFont); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_TitleFont(const PRUnichar *TitleFont, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_TitleFont (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_TitleFont(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_TextFont (in wstring TextFont); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_TextFont(const PRUnichar *TextFont, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_TextFont (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_TextFont(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_BtnFont (in wstring BtnFont); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_BtnFont(const PRUnichar *BtnFont, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_BtnFont (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_BtnFont(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_UILogoUrl (in wstring UILogoUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_UILogoUrl(const PRUnichar *UILogoUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_UILogoUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_UILogoUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_NewPasswd_Title (in wstring NewPasswd_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_NewPasswd_Title(const PRUnichar *NewPasswd_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_NewPasswd_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_NewPasswd_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_NewPasswd_Text (in wstring NewPasswd_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_NewPasswd_Text(const PRUnichar *NewPasswd_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_NewPasswd_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_NewPasswd_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_NewPasswd_OKBtnText (in long NewPasswd_OKBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_NewPasswd_OKBtnText(PRInt32 NewPasswd_OKBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_NewPasswd_OKBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_NewPasswd_OKBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_NewPasswd_CancelBtnText (in long NewPasswd_CancelBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_NewPasswd_CancelBtnText(PRInt32 NewPasswd_CancelBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_NewPasswd_CancelBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_NewPasswd_CancelBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_NewPasswd_HelpUrl (in wstring NewPasswd_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_NewPasswd_HelpUrl(const PRUnichar *NewPasswd_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_NewPasswd_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_NewPasswd_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_LgnDlg_Title (in wstring LgnDlg_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_LgnDlg_Title(const PRUnichar *LgnDlg_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_LgnDlg_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_LgnDlg_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_OpenProf_Title (in wstring OpenProf_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_OpenProf_Title(const PRUnichar *OpenProf_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_OpenProf_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_OpenProf_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_OpenProf_Text (in wstring OpenProf_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_OpenProf_Text(const PRUnichar *OpenProf_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_OpenProf_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_OpenProf_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_OpenProf_OKBtnText (in long OpenProf_OKBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_OpenProf_OKBtnText(PRInt32 OpenProf_OKBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_OpenProf_OKBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_OpenProf_OKBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_OpenProf_CancelBtnText (in long OpenProf_CancelBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_OpenProf_CancelBtnText(PRInt32 OpenProf_CancelBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_OpenProf_CancelBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_OpenProf_CancelBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_OpenProf_HelpUrl (in wstring OpenProf_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_OpenProf_HelpUrl(const PRUnichar *OpenProf_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_OpenProf_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_OpenProf_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_Title (in wstring SelID_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_Title(const PRUnichar *SelID_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_SelID_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_Text (in wstring SelID_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_Text(const PRUnichar *SelID_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_SelID_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_OKBtnText (in long SelID_OKBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_OKBtnText(PRInt32 SelID_OKBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_SelID_OKBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_OKBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_CancelBtnText (in long SelID_CancelBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_CancelBtnText(PRInt32 SelID_CancelBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_SelID_CancelBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_CancelBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_ShowDefChkBox (in boolean SelID_ShowDefChkBox); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_ShowDefChkBox(PRBool SelID_ShowDefChkBox, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_UIPrefs_SelID_ShowDefChkBox (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_ShowDefChkBox(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_ChkBoxText (in wstring SelID_ChkBoxText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_ChkBoxText(const PRUnichar *SelID_ChkBoxText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_SelID_ChkBoxText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_ChkBoxText(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SelID_HelpUrl (in wstring SelID_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SelID_HelpUrl(const PRUnichar *SelID_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_SelID_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SelID_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SgnDlg_Title (in wstring SgnDlg_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SgnDlg_Title(const PRUnichar *SgnDlg_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_SgnDlg_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SgnDlg_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_RvwMsg_Text (in wstring RvwMsg_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_RvwMsg_Text(const PRUnichar *RvwMsg_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_RvwMsg_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_RvwMsg_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_RvwMsg_OKBtnText (in long RvwMsg_OKBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_RvwMsg_OKBtnText(PRInt32 RvwMsg_OKBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_RvwMsg_OKBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_RvwMsg_OKBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_RvwMsg_Title (in wstring RvwMsg_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_RvwMsg_Title(const PRUnichar *RvwMsg_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_RvwMsg_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_RvwMsg_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_RvwMsg_CancelBtnText (in long RvwMsg_CancelBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_RvwMsg_CancelBtnText(PRInt32 RvwMsg_CancelBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_RvwMsg_CancelBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_RvwMsg_CancelBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_RvwMsg_HelpUrl (in wstring RvwMsg_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_RvwMsg_HelpUrl(const PRUnichar *RvwMsg_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_RvwMsg_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_RvwMsg_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_IntroDlg_Title (in wstring IntroDlg_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_IntroDlg_Title(const PRUnichar *IntroDlg_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_IntroDlg_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_IntroDlg_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_IntroDlg_Text (in wstring IntroDlg_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_IntroDlg_Text(const PRUnichar *IntroDlg_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_IntroDlg_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_IntroDlg_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_IntroDlg_HelpUrl (in wstring IntroDlg_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_IntroDlg_HelpUrl(const PRUnichar *IntroDlg_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_IntroDlg_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_IntroDlg_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_CreateNewProf_Title (in wstring CreateNewProf_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_CreateNewProf_Title(const PRUnichar *CreateNewProf_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_CreateNewProf_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_CreateNewProf_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_ChangePasswd_Title (in wstring ChangePasswd_Title); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_ChangePasswd_Title(const PRUnichar *ChangePasswd_Title, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_ChangePasswd_Title (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_ChangePasswd_Title(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_ChangePasswd_Text (in wstring ChangePasswd_Text); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_ChangePasswd_Text(const PRUnichar *ChangePasswd_Text, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_ChangePasswd_Text (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_ChangePasswd_Text(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_ChangePasswd_OKBtnText (in long ChangePasswd_OKBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_ChangePasswd_OKBtnText(PRInt32 ChangePasswd_OKBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_ChangePasswd_OKBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_ChangePasswd_OKBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_ChangePasswd_CancelBtnText (in long ChangePasswd_CancelBtnText); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 ChangePasswd_CancelBtnText, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_ChangePasswd_CancelBtnText (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_ChangePasswd_CancelBtnText(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_ChangePasswd_HelpUrl (in wstring ChangePasswd_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_ChangePasswd_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_ChangePasswd_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_ChangePasswd_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_Timeout_HelpUrl (in wstring ChangePasswd_HelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_Timeout_HelpUrl(const PRUnichar *ChangePasswd_HelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_UIPrefs_Timeout_HelpUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_Timeout_HelpUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_EnableTopMostWindow (in boolean boolEnableTopMost); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_EnableTopMostWindow(PRBool boolEnableTopMost, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SignTransDlgWidth (in long nWidth); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SignTransDlgWidth(PRInt32 nWidth, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_SignTransDlgWidth (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SignTransDlgWidth(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_UIPrefs_SignTransDlgHeight (in long nHeight); */
NS_IMETHODIMP _MYCLASS_::Set_UIPrefs_SignTransDlgHeight(PRInt32 nHeight, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_UIPrefs_SignTransDlgHeight (); */
NS_IMETHODIMP _MYCLASS_::Get_UIPrefs_SignTransDlgHeight(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_IssuerDN (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_IssuerDN(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_SubjectDN (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_SubjectDN(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_SerNum (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_SerNum(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long long get_SelectedDigID_ExpDate (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_ExpDate(PRUint64 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long long get_SelectedDigID_EffDate (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_EffDate(PRUint64 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_SelectedDigID_KeyUsage (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_KeyUsage(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_SelectedDigID_KeySize (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_KeySize(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_SelectedDigID_Renewed (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_Renewed(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_PubKeyMD5 (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_PubKeyMD5(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_PubKeySHA1 (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_PubKeySHA1(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_FrndlyName (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_FrndlyName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_LogoUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_LogoUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_SelectedDigID_TextureUrl (); */
NS_IMETHODIMP _MYCLASS_::Get_SelectedDigID_TextureUrl(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_RoamPrefs_NumOfSrvrs (in short NumOfSrvrs); */
NS_IMETHODIMP _MYCLASS_::Set_RoamPrefs_NumOfSrvrs(PRInt16 NumOfSrvrs, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* short get_RoamPrefs_NumOfSrvrs (); */
NS_IMETHODIMP _MYCLASS_::Get_RoamPrefs_NumOfSrvrs(PRInt16 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_RoamPrefs_StorageSrvr (in wstring StorageSrvr); */
NS_IMETHODIMP _MYCLASS_::Set_RoamPrefs_StorageSrvr(const PRUnichar *StorageSrvr, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_RoamPrefs_StorageSrvr (); */
NS_IMETHODIMP _MYCLASS_::Get_RoamPrefs_StorageSrvr(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_RoamPrefs_ClientInfo (in wstring ClientInfo); */
NS_IMETHODIMP _MYCLASS_::Set_RoamPrefs_ClientInfo(const PRUnichar *ClientInfo, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_RoamPrefs_ClientInfo (); */
NS_IMETHODIMP _MYCLASS_::Get_RoamPrefs_ClientInfo(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_RoamPrefs_ClientInfoSig (in wstring ClientInfoSig); */
NS_IMETHODIMP _MYCLASS_::Set_RoamPrefs_ClientInfoSig(const PRUnichar *ClientInfoSig, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_RoamPrefs_ClientInfoSig (); */
NS_IMETHODIMP _MYCLASS_::Get_RoamPrefs_ClientInfoSig(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_ProviderType (in long nProviderType); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_ProviderType(PRInt32 nProviderType, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_XEnroll_ProviderType (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_ProviderType(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_GenKeyFlags (in long nGenKeyFlags); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_GenKeyFlags(PRInt32 nGenKeyFlags, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_XEnroll_GenKeyFlags (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_GenKeyFlags(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_ProviderName (in wstring szProviderName); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_XEnroll_ProviderName (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_ProviderName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_HashAlgorithm (in wstring szHashAlgo); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_HashAlgorithm(const PRUnichar *szHashAlgo, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_XEnroll_HashAlgorithm (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_HashAlgorithm(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_KeySpec (in long nKeySpec); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_KeySpec(PRInt32 nKeySpec, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_XEnroll_KeySpec (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_KeySpec(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_DeleteRequestCert (in boolean boolFlag); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_DeleteRequestCert(PRBool boolFlag, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_XEnroll_DeleteRequestCert (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_DeleteRequestCert(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_XEnroll_WriteCertToCSP (in boolean boolFlag); */
NS_IMETHODIMP _MYCLASS_::Set_XEnroll_WriteCertToCSP(PRBool boolFlag, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean get_XEnroll_WriteCertToCSP (); */
NS_IMETHODIMP _MYCLASS_::Get_XEnroll_WriteCertToCSP(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring XEnroll_enumProviders (in long nIndex, in long nFlags); */
NS_IMETHODIMP _MYCLASS_::XEnroll_enumProviders(PRInt32 nIndex, PRInt32 nFlags, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring XEnroll_createPKCS10 (in wstring szDNName, in wstring szUsage); */
NS_IMETHODIMP _MYCLASS_::XEnroll_createPKCS10(const PRUnichar *szDNName, const PRUnichar *szUsage, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long XEnroll_acceptPKCS7 (in wstring szPKCS7); */
NS_IMETHODIMP _MYCLASS_::XEnroll_acceptPKCS7(const PRUnichar *szPKCS7, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* unsigned long GetLastError (); */
NS_IMETHODIMP _MYCLASS_::GetLastError(PRUint32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long VSImport_Import (in wstring PKCS12, in wstring PKCS7, out wstring szErrCodeString); */
NS_IMETHODIMP _MYCLASS_::VSImport_Import(const PRUnichar *PKCS12, const PRUnichar *PKCS7, PRUnichar **szErrCodeString, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long VSImport_set_KeyExportable (in long nFlag); */
NS_IMETHODIMP _MYCLASS_::VSImport_set_KeyExportable(PRInt32 nFlag, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long VSImport_get_KeyExportable (); */
NS_IMETHODIMP _MYCLASS_::VSImport_get_KeyExportable(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long VSImport_set_ProviderName (in wstring szProviderName); */
NS_IMETHODIMP _MYCLASS_::VSImport_set_ProviderName(const PRUnichar *szProviderName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring VSImport_get_ProviderName (); */
NS_IMETHODIMP _MYCLASS_::VSImport_get_ProviderName(PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long AddRootCerts_Initialize (); */
NS_IMETHODIMP _MYCLASS_::AddRootCerts_Initialize(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long AddRootCerts_CreateStandardTrustProfile (); */
NS_IMETHODIMP _MYCLASS_::AddRootCerts_CreateStandardTrustProfile(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long AddRootCerts_CreateVerisignTrustProfile (); */
NS_IMETHODIMP _MYCLASS_::AddRootCerts_CreateVerisignTrustProfile(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long P12Import_ImportP12 (in long nType, in wstring strP12, out wstring strSerialNum, out wstring strIssuerDN); */
NS_IMETHODIMP _MYCLASS_::P12Import_ImportP12(PRInt32 nType, const PRUnichar *strP12, PRUnichar **strSerialNum, PRUnichar **strIssuerDN, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long P12Export_ExportP12 (in long nOutputType, in long nFlags, in wstring strFile); */
NS_IMETHODIMP _MYCLASS_::P12Export_ExportP12(PRInt32 nOutputType, PRInt32 nFlags, const PRUnichar *strFile, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_P12Export_PasswdQuality (); */
NS_IMETHODIMP _MYCLASS_::Get_P12Export_PasswdQuality(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_P12Export_PasswdQuality (in long newVal); */
NS_IMETHODIMP _MYCLASS_::Set_P12Export_PasswdQuality(PRInt32 newVal, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long get_P12Export_PasswdLength (); */
NS_IMETHODIMP _MYCLASS_::Get_P12Export_PasswdLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_P12Export_PasswdLength (in long newVal); */
NS_IMETHODIMP _MYCLASS_::Set_P12Export_PasswdLength(PRInt32 newVal, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long NZ_Initialize (); */
NS_IMETHODIMP _MYCLASS_::NZ_Initialize(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long NZ_Close (); */
NS_IMETHODIMP _MYCLASS_::NZ_Close(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_NotarizationServer (in wstring ServerName); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_NotarizationServer(const PRUnichar *ServerName, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_HashAlg (in wstring HashAlg); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_HashAlg(const PRUnichar *HashAlg, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_DisplayDigitalID (in long DisplayID); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_DisplayDigitalID(PRInt32 DisplayID, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_CrlLocation (in wstring CrlLocation); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_CrlLocation(const PRUnichar *CrlLocation, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_ValidationPreference (in long ValPref); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_ValidationPreference(PRInt32 ValPref, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_NotarizationDescription (in wstring Description); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_NotarizationDescription(const PRUnichar *Description, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring NZ_NotarizeDocument (in wstring DocumentName, in long UIMask, in long ResponseType); */
NS_IMETHODIMP _MYCLASS_::NZ_NotarizeDocument(const PRUnichar *DocumentName, PRInt32 UIMask, PRInt32 ResponseType, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring NZ_NotarizeHash (in wstring Hash, in long UIMask); */
NS_IMETHODIMP _MYCLASS_::NZ_NotarizeHash(const PRUnichar *Hash, PRInt32 UIMask, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long NZ_VerifyNotarizationRecord (in wstring Record, in wstring Document, in long RecordType, in long UIMask); */
NS_IMETHODIMP _MYCLASS_::NZ_VerifyNotarizationRecord(const PRUnichar *Record, const PRUnichar *Document, PRInt32 RecordType, PRInt32 UIMask, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long NZ_AddCertificate (in wstring Certificate); */
NS_IMETHODIMP _MYCLASS_::NZ_AddCertificate(const PRUnichar *Certificate, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_LogoUrl (in wstring LogoUrl); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_LogoUrl(const PRUnichar *LogoUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_SelFileTitle (in wstring SelFileTitle); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_SelFileTitle(const PRUnichar *SelFileTitle, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_SelFileDescription (in wstring SelFileDesc); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_SelFileDescription(const PRUnichar *SelFileDesc, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_SelFileHelpUrl (in wstring SelFileHelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_SelFileHelpUrl(const PRUnichar *SelFileHelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ProgressTitle (in wstring ProgressTitle); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ProgressTitle(const PRUnichar *ProgressTitle, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ProgressDescription (in wstring ProgressDesc); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ProgressDescription(const PRUnichar *ProgressDesc, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ProgressHelpUrl (in wstring ProgressHelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ProgressHelpUrl(const PRUnichar *ProgressHelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ReceiptTitle (in wstring ReceiptTitle); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ReceiptTitle(const PRUnichar *ReceiptTitle, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ReceiptDescription (in wstring ReceiptDesc); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ReceiptDescription(const PRUnichar *ReceiptDesc, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_ReceiptHelpUrl (in wstring ReceiptHelpUrl); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_ReceiptHelpUrl(const PRUnichar *ReceiptHelpUrl, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_UIPrefs_WizardTitle (in wstring WizardTitle); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_UIPrefs_WizardTitle(const PRUnichar *WizardTitle, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long set_NZ_ApplicationPreference (in wstring ApplicationName, in wstring PreferenceName, in long PreferenceType, in wstring PreferenceValue); */
NS_IMETHODIMP _MYCLASS_::Set_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRInt32 PreferenceType, const PRUnichar *PreferenceValue, PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* wstring get_NZ_ApplicationPreference (in wstring ApplicationName, in wstring PreferenceName); */
NS_IMETHODIMP _MYCLASS_::Get_NZ_ApplicationPreference(const PRUnichar *ApplicationName, const PRUnichar *PreferenceName, PRUnichar **_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_n6pta_h__ */
