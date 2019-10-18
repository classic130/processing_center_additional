/*******************************************************************************
 * Simple LiveConnect Sample Plugin
 * Copyright (c) 1996 Netscape Communications. All rights reserved.
 ******************************************************************************/

import netscape.plugin.Plugin;
import java.util.Date;
import java.lang.reflect.Array;


class NPVSSC extends Plugin {

    /*
    ** A plug-in can consist of code written in java as well as
    ** natively. Here's a dummy method.
    */
    
    /*
    ** This instance variable is used to keep track of the number of
    ** times we've called into this plug-in.
    */
    
    /*
    ** This native method will give us a way to print to stdout from java
    ** instead of just the java console.
    */

	/** XEnroll properties ***/
	public native int set_XEnroll_ProviderType(int nProviderType);
	public native int get_XEnroll_ProviderType();

	public native int set_XEnroll_GenKeyFlags(int nGenKeyFlags);
	public native int get_XEnroll_GenKeyFlags();

	public native int set_XEnroll_ProviderName(String szProviderName);
	public native String get_XEnroll_ProviderName();

	public native int set_XEnroll_HashAlgorithm(String szHashAlgo);
	public native String get_XEnroll_HashAlgorithm();

	public native int set_XEnroll_KeySpec(int nKeySpec);
	public native int get_XEnroll_KeySpec();

	public native int set_XEnroll_DeleteRequestCert(boolean boolFlag);
	public native boolean get_XEnroll_DeleteRequestCert();

	public native int set_XEnroll_WriteCertToCSP(boolean boolFlag);
	public native boolean get_XEnroll_WriteCertToCSP();

	/**** XEnroll methods ***/
	public native String XEnroll_enumProviders(int nIndex, int nFlags);
	public native String XEnroll_createPKCS10(String szDNName, String szUsage);
	public native int XEnroll_acceptPKCS7(String szPKCS7);

	/**** Config Checker Methods ***/
	/*public native int CnfChk_CheckMSEnhCSP();*/
	/*public native int CnfChk_FixEnhCSP(String szEnhCSPVer);*/
	/*public native int CnfChk_GetVersion(String szFileName, StringBuffer szVersion);*/
	/*public native int CnfChk_VerCompare(String szVer1, String szVer2);*/


	/**** VSImport Methods ****/
	public native int VSImport_Import(String PKCS12, String PKCS7, StringBuffer szErrCodeString);
	public native int VSImport_set_KeyExportable(int nFlag);
	public native int VSImport_get_KeyExportable();
	public native int VSImport_set_ProviderName (String szProviderName);
	public native String VSImport_get_ProviderName ();
	
	/**** AddRootCerts Methods ****/
	public native int AddRootCerts_Initialize();
	public native int AddRootCerts_CreateStandardTrustProfile();
	public native int AddRootCerts_CreateVerisignTrustProfile();

	/****	ImportP12 Methods ****/
	public native int P12Import_ImportP12 (int nType, String strP12, StringBuffer strSerialNum, StringBuffer strIssuerDN);

	/****	ExportP12 Methods ****/
	public native int P12Export_ExportP12(int nOutputType, int nFlags, String strFile);
	public native int get_P12Export_PasswdQuality();
	public native int set_P12Export_PasswdQuality(int newVal);
	public native int get_P12Export_PasswdLength();
	public native int set_P12Export_PasswdLength(int newVal);



    /*
    ** This is a publically callable new feature that our plug-in is
    ** providing. We can call it from JavaScript, Java, or from native
    ** code.
    */

	/************************** PTA v2 Properties **************************/ 

	/******************** PTA Interface ********************/
	public native int PTA_Initialize (String AppCtxtName, int useCapi);
	public native int PTA_Close();

	public native int set_PTA_AppPreference (String PrefName, String Value);
	public native String get_PTA_AppPreference (String PrefName);

	public native int set_PTA_CSPName (String CSPName);
	public native String get_PTA_CSPName ();

	public native String PTA_CreateCertReq (String SubjectDN, int KeyGenFlag, int HashAlg, Object attributes);
	public native int PTA_InstallCert (String Cert);
	public native int PTA_InstallKeyPair (String privKeyBlob, String pkcs7Cert);

	public native String PTA_SignChallenge (String Challenge, int AlgID);
	public native String PTA_SignTransaction (String Message, int AlgID);
	public native String PTA_SignRenewal (int AlgID);

	public native  int PTA_SelectIDForTrans();
	public native int PTA_SelectIDForChallenge();	

	public native short get_PTA_UseDefCertFlag();
	public native int set_PTA_UseDefCertFlag(short defCertFlag);

	public native int set_PTA_ProtocolName(String protocolName);
	public native String get_PTA_ProtocolName ();

	public native int set_PTA_AuthDll(String authDllName);
	public native String get_PTA_AuthDll ();    

    public native int set_PTA_ProfileIssFrndlyName (String profileIssFrndlyName);
	public native String get_PTA_ProfileIssFrndlyName  ();    

    public native int set_PTA_ProfileIssUniqueId (String profileIssUniqId);
	public native String get_PTA_ProfileIssUniqueId  ();    

	public native int set_PTA_AffLogoUrl (String affLogoUrl);
	public native String get_PTA_AffLogoUrl ();


	/******************** CertPref Interface ********************/
    public native int set_CertPref_CertSerNum(String CertSerNum);
	public native String get_CertPref_CertSerNum();

	public native int set_CertPref_CertIssDN(String CertIssDN);
	public native String get_CertPref_CertIssDN();

	public native int set_CertPref_CertFrndlyName(String CertFrndlyName);
	public native String get_CertPref_CertFrndlyName();

	public native int set_CertPref_CertLogoUrl(String CertLogoUrl);
	public native String get_CertPref_CertLogoUrl();

	public native int set_CertPref_CertDispString(String CertDispString);
	public native String get_CertPref_CertDispString();

	public native int set_CertPref_CertTextureUrl(String CertTextureUrl);
	public native String get_CertPref_CertTextureUrl();

	public native int set_CertPref_MarkAsRenewed(boolean boolMarkAsRenewed);
	public native boolean get_CertPref_MarkAsRenewed();

	public native int set_CertPref_SetPreference(String PrefName, String Value);
	public native String get_CertPref_GetPreference(String PrefName);


	/***************** Profile Management Interface ********************/
	/*public native int set_ProfMgmt_ReadOKDomains(Object ReadDomains);*/
	/*public native Object get_ProfMgmt_ReadOKDomains();*/

	/*public native int set_ProfMgmt_WriteOKDomains(Object WriteDomains);*/
	/*public native Object get_ProfMgmt_WriteOKDomains();*/
 
    public native int set_ProfMgmt_PasswdQuality( int PasswdQuality);
	public native int get_ProfMgmt_PasswdQuality ();

    public native int set_ProfMgmt_PasswdLength( int PasswdLength);
	public native int get_ProfMgmt_PasswdLength ();

    public native int set_ProfMgmt_PasswdTimeOut( int PasswdTimeOut);
	public native int get_ProfMgmt_PasswdTimeOut ();

    public native int set_ProfMgmt_PasswdLockOutTries( int PasswdLockOutTries);
	public native int get_ProfMgmt_PasswdLockOutTries ();

    public native int set_ProfMgmt_PasswdUnLockPeriod( int PasswdUnLockPeriod);
	public native int get_ProfMgmt_PasswdUnLockPeriod ();

	public native int set_ProfMgmt_ProfileName (String ProfileName);
	public native String get_ProfMgmt_ProfileName();

	public native int set_ProfMgmt_Password (String Password);

	public native int set_ProfMgmt_SaveLocal (boolean boolSaveLocal);
	public native boolean get_ProfMgmt_SaveLocal();

	public native int set_ProfMgmt_RoamProfile (boolean boolRoamProfile);
	public native boolean get_ProfMgmt_RoamProfile();

	public native int set_ProfMgmt_OpenProfFlags (int flags);
	public native int get_ProfMgmt_OpenProfFlags ();

    public native int ProfMgmt_OpenProfile();
	public native int ProfMgmt_CloseProfile();

    public native int ProfMgmt_SaveProfile();
    public native int ProfMgmt_ChangePassword();

	public native int set_ProfMgmt_IsUsernameEditable(boolean bUsernameEditable);
	public native boolean get_ProfMgmt_IsUsernameEditable();


	/***************** Search criteria Interface ********************/
	public native int set_SrchCrit_IssuerDN(String IssuerDN);
	public native String get_SrchCrit_IssuerDN();

	public native int set_SrchCrit_SubjectDN(String SubjectDN);
	public native String get_SrchCrit_SubjectDN();

	public native int set_SrchCrit_SerNum(String SerNum);
	public native String get_SrchCrit_SerNum();

	public native int set_SrchCrit_Email(String Email);
	public native String get_SrchCrit_Email();

	public native int set_SrchCrit_ExpDate(Date ExpDate);
	public native Date get_SrchCrit_ExpDate();

	public native int set_SrchCrit_EffDate(Date EffDate);
	public native Date get_SrchCrit_EffDate();

	public native int set_SrchCrit_DateEquality(short DateEquality);
	public native short get_SrchCrit_DateEquality();

	public native int set_SrchCrit_Renewed(boolean Renewed);
	public native boolean get_SrchCrit_Renewed();

	public native int set_SrchCrit_KeyUsage(short KeyUsage);
	public native short get_SrchCrit_KeyUsage();

	public native int set_SrchCrit_KeySize(short KeySize);
	public native short get_SrchCrit_KeySize();

	public native int set_SrchCrit_ExtOID(String ExtOID);
	public native String get_SrchCrit_ExtOID();

	public native int set_SrchCrit_ExtVal(String ExtVal);
	public native String get_SrchCrit_ExtVal();




	/***************** UI Preferences properties *****************/
	/* TODO the data type for this might change */
	public native int set_UIPrefs_Language (int Language);
	public native int get_UIPrefs_Language ();

	public native int set_UIPrefs_TitleFont (String TitleFont);
	public native String get_UIPrefs_TitleFont ();

	public native int set_UIPrefs_TextFont (String TextFont);
	public native String get_UIPrefs_TextFont ();

	public native int set_UIPrefs_BtnFont (String BtnFont);
	public native String get_UIPrefs_BtnFont ();

	public native int set_UIPrefs_UILogoUrl (String UILogoUrl);
	public native String get_UIPrefs_UILogoUrl ();

	public native int set_UIPrefs_NewPasswd_Title (String NewPasswd_Title);
	public native String get_UIPrefs_NewPasswd_Title ();

	public native int set_UIPrefs_NewPasswd_Text (String NewPasswd_Text);
	public native String get_UIPrefs_NewPasswd_Text ();

	public native int set_UIPrefs_NewPasswd_OKBtnText (int NewPasswd_OKBtnText);
	public native int get_UIPrefs_NewPasswd_OKBtnText ();

	public native int set_UIPrefs_NewPasswd_CancelBtnText (int NewPasswd_CancelBtnText);
	public native int get_UIPrefs_NewPasswd_CancelBtnText ();
	
	public native int set_UIPrefs_NewPasswd_HelpUrl (String NewPasswd_HelpUrl);
	public native String get_UIPrefs_NewPasswd_HelpUrl ();

	public native int set_UIPrefs_LgnDlg_Title (String LgnDlg_Title);
	public native String get_UIPrefs_LgnDlg_Title ();

	public native int set_UIPrefs_OpenProf_Title (String OpenProf_Title);
	public native String get_UIPrefs_OpenProf_Title ();
	
	public native int set_UIPrefs_OpenProf_Text (String OpenProf_Text);
	public native String get_UIPrefs_OpenProf_Text ();

	public native int set_UIPrefs_OpenProf_OKBtnText (int OpenProf_OKBtnText);
	public native int get_UIPrefs_OpenProf_OKBtnText ();

	public native int set_UIPrefs_OpenProf_CancelBtnText (int OpenProf_CancelBtnText);
	public native int get_UIPrefs_OpenProf_CancelBtnText ();

	public native int set_UIPrefs_OpenProf_HelpUrl (String OpenProf_HelpUrl);
	public native String get_UIPrefs_OpenProf_HelpUrl ();
	
	public native int set_UIPrefs_SelID_Title (String SelID_Title);
	public native String get_UIPrefs_SelID_Title ();

	public native int set_UIPrefs_SelID_Text (String SelID_Text);
	public native String get_UIPrefs_SelID_Text ();

	public native int set_UIPrefs_SelID_OKBtnText (int SelID_OKBtnText);
	public native int get_UIPrefs_SelID_OKBtnText ();
	
	public native int set_UIPrefs_SelID_CancelBtnText (int SelID_CancelBtnText);
	public native int get_UIPrefs_SelID_CancelBtnText ();

	public native int set_UIPrefs_SelID_ShowDefChkBox(boolean SelID_ShowDefChkBox);
	public native boolean get_UIPrefs_SelID_ShowDefChkBox();

	public native int set_UIPrefs_SelID_ChkBoxText(String SelID_ChkBoxText);
	public native String get_UIPrefs_SelID_ChkBoxText();

	public native int set_UIPrefs_SelID_HelpUrl(String SelID_HelpUrl);
	public native String get_UIPrefs_SelID_HelpUrl();

	public native int set_UIPrefs_SgnDlg_Title(String SgnDlg_Title);
	public native String get_UIPrefs_SgnDlg_Title();

	public native int set_UIPrefs_RvwMsg_Text(String RvwMsg_Text);
	public native String get_UIPrefs_RvwMsg_Text();

	public native int set_UIPrefs_RvwMsg_OKBtnText(int RvwMsg_OKBtnText);
	public native int get_UIPrefs_RvwMsg_OKBtnText();

	public native int set_UIPrefs_RvwMsg_Title(String RvwMsg_Title);
	public native String get_UIPrefs_RvwMsg_Title();

	public native int set_UIPrefs_RvwMsg_CancelBtnText(int RvwMsg_CancelBtnText);
	public native int get_UIPrefs_RvwMsg_CancelBtnText();

	public native int set_UIPrefs_RvwMsg_HelpUrl(String RvwMsg_HelpUrl);
	public native String get_UIPrefs_RvwMsg_HelpUrl();

	public native int set_UIPrefs_IntroDlg_Title(String IntroDlg_Title);
	public native String get_UIPrefs_IntroDlg_Title();

	public native int set_UIPrefs_IntroDlg_Text(String IntroDlg_Text);
	public native String get_UIPrefs_IntroDlg_Text();

	public native int set_UIPrefs_IntroDlg_HelpUrl(String IntroDlg_HelpUrl);
	public native String get_UIPrefs_IntroDlg_HelpUrl ();

	public native int set_UIPrefs_CreateNewProf_Title(String CreateNewProf_Title);
	public native String get_UIPrefs_CreateNewProf_Title();

	public native int set_UIPrefs_ChangePasswd_Title(String ChangePasswd_Title);
	public native String get_UIPrefs_ChangePasswd_Title();

	public native int set_UIPrefs_ChangePasswd_Text(String ChangePasswd_Text);
	public native String get_UIPrefs_ChangePasswd_Text();

	public native int set_UIPrefs_ChangePasswd_OKBtnText(int ChangePasswd_OKBtnText);
	public native int get_UIPrefs_ChangePasswd_OKBtnText();

	public native int set_UIPrefs_ChangePasswd_CancelBtnText(int ChangePasswd_CancelBtnText);
	public native int get_UIPrefs_ChangePasswd_CancelBtnText();

	public native int set_UIPrefs_ChangePasswd_HelpUrl(String ChangePasswd_HelpUrl);
	public native String get_UIPrefs_ChangePasswd_HelpUrl();

	public native int set_UIPrefs_Timeout_HelpUrl(String ChangePasswd_HelpUrl);
	public native String get_UIPrefs_Timeout_HelpUrl();


	/***************** Selected Digital ID Interface ********************/
	public native String get_SelectedDigID_IssuerDN();
	public native String get_SelectedDigID_SubjectDN();
	public native String get_SelectedDigID_SerNum();
	public native Date get_SelectedDigID_ExpDate();
	public native Date get_SelectedDigID_EffDate();
	public native short get_SelectedDigID_KeyUsage();
	public native short get_SelectedDigID_KeySize();
	public native boolean get_SelectedDigID_Renewed();
	public native String get_SelectedDigID_PubKeyMD5();
	public native String get_SelectedDigID_PubKeySHA1();
	public native String get_SelectedDigID_FrndlyName();
	public native String get_SelectedDigID_LogoUrl();
	public native String get_SelectedDigID_TextureUrl();

	
	/***************** Roaming Preferences Interface ********************/
	public native int set_RoamPrefs_NumOfSrvrs (short NumOfSrvrs);
	public native short get_RoamPrefs_NumOfSrvrs ();

	public native int set_RoamPrefs_RoamingSrvrs (Object RoamingSrvrs);
	public native Object get_RoamPrefs_RoamingSrvrs ();

	public native int set_RoamPrefs_StorageSrvr (String StorageSrvr);
	public native String get_RoamPrefs_StorageSrvr();

	public native int set_RoamPrefs_ClientInfo (String ClientInfo);
	public native String get_RoamPrefs_ClientInfo();

	public native int set_RoamPrefs_ClientInfoSig (String ClientInfoSig);
	public native String get_RoamPrefs_ClientInfoSig();

	/****************** VSSC Properties *********************/

		/****************** String Type ****************/
		public native String get_VSSC_ToRecipientsInfo();
		public native int set_VSSC_ToRecipientsInfo(String newVal);

		public native String get_VSSC_CcRecipientsInfo();
		public native int set_VSSC_CcRecipientsInfo(String newVal);

		public native String get_VSSC_BccRecipientsInfo();
		public native int set_VSSC_BccRecipientsInfo(String newVal);

		public native String get_VSSC_FromInfo();
		public native int set_VSSC_FromInfo(String newVal);

		public native String get_VSSC_Subject();
		public native int set_VSSC_Subject(String newVal);

		public native String get_VSSC_Body();
		public native int set_VSSC_Body(String newVal);

		public native String get_VSSC_Date();
		public native int set_VSSC_Date(String newVal);

		public native String get_VSSC_SelectedAttachments();
		public native int set_VSSC_UnSelectAttachments(String newVal);

		public native String get_VSSC_GetMsg();
		
		/*public native StringBuffer get_VSSC_GetMsg();*/


		/*** Remove this later ***/
		/*public native String get_VSSC_DecryptMsg();*/

		public native String get_VSSC_AttachedFileList();


		/******************* Short type ***************/
		public native short get_VSSC_MsgType();
		public native int set_VSSC_MsgType(short newVal);


		/****************** long type **************/
		public native long get_VSSC_CryptStatus();


		/*************** only set properties ************/
		public native int set_VSSC_MsgPostData(String newVal);

		public native int set_VSSC_CertResolveURL(String newVal);
		


		/***** new ****/
		public native int set_VSSC_UseProxyRecipCert(int newVal);
		
		/*****new ****/
		public native int set_VSSC_AllowDecryption(short newVal);
		

	

	/************************ VSSC Methods *****************************/

		public native int VSSC_Compose(StringBuffer AppStatus);

		public native int VSSC_SelectAttachments(StringBuffer AppStatus);

		public native short VSSC_SaveAttachment(String pFileName, StringBuffer AppStatus);

	
	/*Changed	public native String VSSC_CertificateResolution(String in_pvarEmailInfo);*/
		public native int VSSC_CertificateResolution(String in_pvarEmailInfo, StringBuffer AppStatus);

	/*Changed	public native String VSSC_SMIMECertificateResolution(String in_pvarEmailInfo);*/
		public native int VSSC_SMIMECertificateResolution(StringBuffer AppStatus);

		public native short VSSC_Decompose(String i_pvarSMIMEMsg, StringBuffer AppStatus);


	
		/*public native int VSSC_Initialize(int i_pMsgObjID, short i_pMode, StringBuffer AppStatus);*/
		public native int VSSC_Initialize(int i_pMsgObjID, short i_pMode, StringBuffer AppStatus);
		public native int VSSC_StoreAll(short i_pModeType, StringBuffer AppStatus);
		public native int VSSC_InternetInitialize(String in_pvarURL, String in_pvarMethod, String in_pvarPostData, StringBuffer AppStatus);
		public native int VSSC_InternetSendRequest(StringBuffer AppStatus);

		/***** check this later ****/
		/*public native String VSSC_ChangeVarType(Object in_pvarByteArray, short in_pvarType);*/


		public native int get_VSSC_MsgObjID();
		public native long get_VSSC_MsgBlobSize();
		public native long get_VSSC_InternetDataSize();
		public native String get_VSSC_InternetData();
		


		public native int set_VSSC_UseInternetData(boolean newVal);

		/**** Start New *****/

		public native long VSSC_SelectedAttachmentSize(String in_pvarFileName, StringBuffer AppStatus);

		public native int set_VSSC_AddSignerCertificate(boolean newVal);
		/*public native int set_VSSC_AddAuthAttributes(boolean newVal);*/
		public native int set_VSSC_AddRFC822Header(boolean newVal);
		public native int set_VSSC_AddMIMEHeader(boolean newVal);
		public native int set_VSSC_OpaqueSign(boolean newVal);
		public native int set_VSSC_AddSenderRecipientInfo(boolean newVal);

		public native int set_VSSC_SCType(String newVal);
		public native String get_VSSC_SCType();

		public native int set_VSSC_CertificateTimeOut(short newVal);
		public native short get_VSSC_CertificateTimeOut();

		public native int set_VSSC_MessageTimeOut(short newVal);
		public native short get_VSSC_MessageTimeOut();

		public native int VSSC_ClearAll(short ModeType, StringBuffer AppStatus);

		public native int set_VSSC_UsePKCS7Certificate(boolean newVal);
		public native int set_VSSC_AddSMIMECapabilities(boolean newVal);

		public native int set_VSSC_ShowSelIDUI(boolean newVal);

		public native int set_VSSC_SupportedPTAVer(String newVal);
		public native short get_VSSC_InstalledPTAVer();

		public native int set_VSSC_URLEncodeData(boolean newVal);

		public native int VSSC_ResolveProxyRecipCert(String in_EmailAddress, StringBuffer out_AppStatus, StringBuffer out_Status);  

		public native int set_VSSC_UseSimder(boolean newVal);
		

		

		/***** End New *****/

		


	


		/*********************** ResolveRcpt Properties ********************/

		public native String get_ResolveRcpt_EmailAddress();
		public native short get_ResolveRcpt_Recipient_Count();

		/***** Start New *******/
		public native int get_ResolveRcpt_Status();
		public native String get_ResolveRcpt_IssuerDN();
		public native String get_ResolveRcpt_SerialNumber();

		public native int get_ResolveRcpt_RevocationStatus();
		public native int get_ResolveRcpt_ChainValidationStatus();
		public native boolean get_ResolveRcpt_IsCertExpired();
		/***** End New *******/

		/*********************** ResolveRcpt Methods ********************/
		public native int ResolveRcpt_First();
		public native int ResolveRcpt_Next();


		/************************ SignerInfo Properties **************/
		public native String get_SignerInfo_SubjectCN();
		public native String get_SignerInfo_SubjectDN();
		public native String get_SignerInfo_IssuerDN();
		public native String get_SignerInfo_SubjectSerialNumber();
		public native Date get_SignerInfo_SubjectValidFrom();
		public native Date get_SignerInfo_SubjectValidTo();

		/**** Error handling method ****/
		public native long GetLastError();


}



