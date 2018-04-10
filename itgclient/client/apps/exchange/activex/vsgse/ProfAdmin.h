// ProfAdmin.h: interface for the CProfAdmin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFADMIN_H__F0FB0BDF_C480_11D3_A1B5_001083023D07__INCLUDED_)
#define AFX_PROFADMIN_H__F0FB0BDF_C480_11D3_A1B5_001083023D07__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//error definitions
#define    VS_NO_PROFILE_EXISTS             1001
#define		E_VS_NO_PROFILE					0x80008100
#define		E_VS_OUTLOOK2002_NO_BUTTONS		0x80008101
#define		E_NO_ADS						0x80008002
#define     E_DNPARSEERR					0x80008003
#define     E_NOTDEF_OUTLOOK_CLINET			0x80008004


#define     E_UNABLE_TO_GET_SID				0x80008030;
#define     E_FAILED_LDAP_GET_LEN			0x80008031;
#define     E_SID_COMP_FAILED				0x80008032;
#define     E_ENC_CERT_NOTFOUND				0x80008033;
#define     E_SID_NOTFOUND					0x80008034

#define		MAX_NAME						256

#define		OUTLOOK_2000_VERSION			9


#define CHECK_HRESULT if(S_OK != hr) \
								break;

// Start Add : Infosys : CR21346
#define EXCH55_NO_OF_ATTR	7
#define EXCH2K_NO_OF_ATTR	8
// End Add : Infosys : CR21346

// Start Add : Infosys : CR27993
// Security property Tags
#define PR_SECURITY_PROFILES PROP_TAG(PT_MV_BINARY, 0x355)
#define PR_CERT_PROP_VERSION				0x0001
#define PR_CERT_MESSAGE_ENCODING			0x0006
#define PR_CERT_DEFAULTS					0x0020
#define PR_CERT_DISPLAY_NAME_A				0x000B
#define PR_CERT_KEYEX_SHA1_HASH				0x0022
#define PR_CERT_SIGN_SHA1_HASH				0x0009
#define PR_CERT_ASYMETRIC_CAPS				0x0002

// Display name to identify the security property
#define SETTING_DISPLAY_NAME				"VERISIGN SECURITY SETTING"

// GUID for Dilkie property section
#define	DILKIE_MAPIUID		"\xc0\x2e\xbc\x53\x53\xd9\xcd\x11\x97\x52\x00\xaa\x00\x4a\xe4\x0e"

#define SIGN_HASH_PROPERY					5
#define KEYEX_HASH_PROPERY					4
#define PROP_ARRAY_SIZE						7
#define MAX_BUF_SIZE						2048

// Possible nSetDefaultCertFlag values
#define SET_DEFAULT_FOR_NONE				0x00
#define SET_DEFAULT_FOR_SIGN				0x01
#define SET_DEFAULT_FOR_ENCRYPT				0x02
#define SET_DEFAULT_FOR_BOTH				0x03

// Structure to hold the security property
typedef struct _SEC_PROP_BLOB {
		USHORT   tag;
        USHORT   length;
		BYTE   pbdata[MAX_BUF_SIZE];
} SEC_PROP_BLOB;

// End Add : Infosys : CR27993


////struct contains information regarding outlook profile
typedef struct _ProfileInfo
{
	_bstr_t   bstrHomeServer;
	_bstr_t   bstrExchServer;
	_bstr_t   bstrProfileUser;
	_bstr_t   bstrHomeServerDN;
	_bstr_t   bstrProfileUnResName;
	_bstr_t   bstrLegacyExchangeDN;   //For exchnage 2000 
	_bstr_t   bstrBaseDN;

}ProfileInfo;

////struct contains inofrmation regarding the Mailbox
typedef struct _MailBoxInfo
{

	_bstr_t      bstrcn;
	_bstr_t      bstrdistinguishedName;
	_bstr_t      bstrUserDN;
	_bstr_t      bstrHome_MTA;
	_bstr_t      bstrrfc822Mailbox;
	_bstr_t      bstruid;
	_bstr_t      bstrupn;
	_bstr_t      bstrBaseDN;
	// Start Add : Infosys : CR21346
	_bstr_t      bstrFirstName;
	_bstr_t      bstrLastName;
	// End Add : Infosys : CR21346

}MailBoxInfo;


class CProfAdmin  
{
public:

	  int               ncharEncodingInfo;
      HRESULT           hr;
	  DWORD             ldapError;

	  LPPROFADMIN       pProfAdmin ;
      LPSERVICEADMIN    pSvcAdmin ;
      LPMAPITABLE       pMsgSvcTable;
	  LPMAPITABLE       pProfileTable;

	 _bstr_t*			ptbstrDNAttrs;
     _bstr_t*			ptbstrDNVals;
      int				nNumOfDNAttrs;

	  

private:

	_Application              *olApp;
	Inspector                 *olIns;
	NameSpace                 *olNs;
	_MailItem                 *olMail;

	IDispatch                 *pdispItem,*pdispCmdBar;
	CLSID					   clsOlApp;


	DWORD			          m_dwErrorCode ;	


public:
	HRESULT GetDefaultProfile(_bstr_t  *i_bstrDefProfile);
	CProfAdmin();
	virtual ~CProfAdmin();


public:
//private:
	int			 gNumOfExchProfile,ghExchVer,ghExch_UpdateVer;
	int			 gTotalProfile,ghADServerInfo;
	int          gh_CAInfo;
	
	_bstr_t      ghbstrExchVerStr;
	_bstr_t		 m_bstrSerialNum;
	
	
	
	_bstr_t       ghbstrHomeServer; 
	_bstr_t       ghbstrMailDN;
	_bstr_t       ghbstrCurrentProfile; 
	_bstr_t       bstrCurrentProfile;


	_bstr_t      ghbstrUserCertificate;
	_bstr_t      ghbstrSMIMECertificate;
	_bstr_t      ghbstrADServerInfoList;

	
	BOOL         gLDAPAccess,ghVer;
	BOOL		 UserOrSMIME;
	BOOL         gbDefOutLookClient;
	BOOL         bRenewCert; 
	BOOL         bSetEFSCert;

	MailBoxInfo gMailBoxInfo; 
	ProfileInfo m_pInfo;

public:
	HRESULT GetUserLastName(_bstr_t *o_pbstrLastName);
	HRESULT GetUserFirstName(_bstr_t *o_pbstrFirstName);
	short nSetDefaultCertFlag;

	/////MAPI Functions to get the profile information
	HRESULT EnumExchProfile();
	HRESULT GetProfileInfo(_bstr_t& i_bstrProfile,ProfileInfo *pProfileInfo);
	HRESULT IsExchProfile(_bstr_t& i_bstrProfileName);
	HRESULT FindExchVer(_bstr_t& i_bstrProfile);
	HRESULT HrOpenInbox(LPMDB pmdb, LPMAPIFOLDER FAR * lppF);
	HRESULT HrOpenDefaultStore(LPMAPISESSION pses, LPMAPIFOLDER *pFolder);
	HRESULT ExchVerByMapi(LPMAPISESSION   lpSession);
	HRESULT CHECKREGForGC();
	HRESULT PromptProfileSelection();
	

	/////LDAP call to get the mailbox information
	HRESULT CheckUpdateRight(_bstr_t& i_bstrServerName,	_bstr_t&i_bstrMailDN);
	HRESULT GetMailBoxInfo(_bstr_t& i_bstrServerName,_bstr_t&i_bstrMailDN,MailBoxInfo * );
	HRESULT Exch2k_GetMailBoxInfo(_bstr_t& i_bstrExchSrvr, _bstr_t& i_bstrMailDN,BOOL bAutoDC, MailBoxInfo *pMailBoxInfo);
	HRESULT Exch2k_CheckUpdateRight(_bstr_t& i_bstrServerName, _bstr_t& i_bstrMailDN,BOOL bAutoDC);
	HRESULT Exch2k_GetDefNamCnxt_Domain(LDAP *ldapConnection,WCHAR**szDefNamingContext);
	
	/////returning MailBox properties
	HRESULT GetAttributes();
	HRESULT GetAlias(_bstr_t* i_bstrAlias);
	HRESULT GetDN(_bstr_t* o_bstrDN);
	HRESULT GetUserDN(_bstr_t* o_bstrUserDN);
	HRESULT GetHomeMTA(_bstr_t* pHomeMTA);
	HRESULT GetRFC822MailBox(_bstr_t* o_bstrRFC822Name);
	HRESULT GetFullName(_bstr_t* o_pbstrName);
	HRESULT GetHomeServer(_bstr_t* o_pbstrHomeServer);
	HRESULT GetExchServer(_bstr_t* o_pbstrExchServer);
    HRESULT GetUserPrincipalName(_bstr_t* o_bstrUPN);
	HRESULT IsUserMemberOfAdminGroup(BOOL *bResult);

	/////Update the LDAP attributes
	HRESULT VerifyCertChain(BSTR newVal);
	HRESULT UpdateCertificateData();
	HRESULT Exch2k_CertUpdate();
	HRESULT CertUpdate();


	/////misc Func
	HRESULT UpdateClientExt();
	HRESULT GetVers(char * szFileName,char *szVer);
	HRESULT CertFriendlyName(BSTR newVal);
	HRESULT GetCertificateProperties(unsigned char *,unsigned int );
	
	HRESULT AddEncrypt_SignButton();




private:
	HRESULT GetCertHash(FRDLYNAMETYPE pType, BYTE *lpbSecBlob, ULONG cbSecBlob, SEC_PROP_BLOB *SecPropBlob);
	HRESULT CreateSecurityBlob(BSTR newVal, HCERTSTORE hCertStore, BYTE *lpbSecBlob, ULONG *cbSecBlob, PBYTE pbUserCertificate, DWORD cbUserCertificate);
	HRESULT AssignCertToProfile(BSTR newVal, HCERTSTORE hCertStore, PBYTE pbUserCertificate, DWORD cbUserCertificate);
	BOOL PrepareLDAPDN(_bstr_t& i_bstrExchangeDN,_bstr_t* o_ptbstrldapDN);

	HRESULT Exchange2000();
	HRESULT Exchange55();
	
	int IsAttributeInclude(WCHAR *a);
	int Hascii2Bin(PCHAR InBuf, PCHAR *OutBuf, int *OutLen);
	void Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize);

	


};

#endif // !defined(AFX_PROFADMIN_H__F0FB0BDF_C480_11D3_A1B5_001083023D07__INCLUDED_)
