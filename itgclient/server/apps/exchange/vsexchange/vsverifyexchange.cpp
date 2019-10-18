/*

 * $Revision: 1.6.28.6 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/vsverifyexchange.cpp,v 1.6.28.6 2003/06/20 17:20:31 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*--------------------------------------------------------------------\

 This program verifies input values: email, common name, cert DN with 
 the Exchange/Active directory data. If they are the same, return VSAA_SUCCESS,
 otherwise return VSAA_VERIFY_FAILED. 

 We are using the function call
 static VSAA_STATUS CreateJurisdictionHash_Capi(char **jurisdiction_hash,char *company,
								 char *org,  char *application);

 This implementation is similair to the function in following file.
 common\modules\app_common\source\jurisdiction.c

 
\--------------------------------------------------------------------*/

#define _WIN32_WINNT 0x0400 
#include <windows.h>

#include <wtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <winbase.h>

#include <comdef.h>



#include "../include/vsutil.h"
#include "../include/vsaanls.h"
#include "../include/vsexchangeutil.h"
#include "../include/vsverifyexchange.h"
#include "../include/vslog.h"

#define UNICODE
#include <winldap.h>
#undef UNICODE



#define EXCH_55                 L"1"
#define EXCH_2000               L"2"

#define EXCHANGE_DN_STYLE       "0"
#define MPKI_DN_STYLE           "1"
#define CUSTOM_MPKI_DN_STYLE    "2"
#define ALL_ALLOWED             L"ALL"

#define kSEPARATOR " - "
#define ONSITE_TEST_DRIVE "TestDrive"

#define E_DNPARSEERR			1001 

#define EXCHANGE_DIR_DN			"ldap_DN"
#define VSAA_COMPANY			"corp_company"
#define VSAA_MAIL_EMAIL			"mail_email"
#define VSAA_EXCH_SERVER_AD     "exchange_ServerName"
#define VSAA_EXCH_SRVR			"exch_Srvr"
#define VSAA_EXCH_VER	        "exchange_Version"
#define VSSA_ORG_UNIT		    "org_unit"
#define VSAA_EXCH_VER_STR	    "exchange_VerString"
#define VSAA_JURIS_HASH         "cert_jurisdiction_hash"  


#define CFG_CERT_DN_FORMAT      "CERT_DN_FORMAT"
#define CFG_EXCHANGE_SERVERS    "EXCHANGE_SERVERS"
#define CFG_DOMAIN_CONTROLLERS  "DOMAIN_CONTROLLERS"

typedef enum 
{
  I_EXCHANGE_DIR_DN		= 0,
  I_COMPANY				= 1,
  I_MAIL_EMAIL			= 2,
  I_COMMON_NAME			= 3,
//  I_CERT_DN				= 4,
  I_EXCH_SERVER_AD		= 4,
  I_EXCH_VER			= 5,
  I_ORG_UNIT			= 6,
  I_EXCH_VER_STR		= 7,
  I_EXCH_SRVR			= 8,
  I_JURIS_HASH			= 9
} LOCAL_DATA_INDEX;

	
static VSAA_NAME localData[] =
{
  {EXCHANGE_DIR_DN,			NULL},
  {VSAA_COMPANY,			NULL},
  {VSAA_MAIL_EMAIL,			NULL},
  {VSAA_COMMON_NAME,		NULL},
  //{VSAA_CERT_DN,			NULL},
  {VSAA_EXCH_SERVER_AD,		NULL},
  {VSAA_EXCH_VER,			NULL},
  {VSSA_ORG_UNIT,			NULL},
  {VSAA_EXCH_VER_STR,		NULL},
  {VSAA_EXCH_SRVR,			NULL},
  {VSAA_JURIS_HASH,			NULL},
  {NULL,					NULL}
};

#define VALUE(X) localData[X].pszValue

typedef struct _MailBoxInfo
{
	WCHAR      cn[1024];
	WCHAR      distinguishedName[1024];
	WCHAR      Home_MTA[1024];
	WCHAR      rfc822Mailbox[1024];
	WCHAR	   uid[1024];
	WCHAR      UserDN[1024];
	WCHAR      upn[1024];
	char       *szUTF8_cn;	

}MailBoxInfo;

MailBoxInfo g_objMailBoxInfo;

typedef struct _CertReqInfo
{
	WCHAR*  wszMPKICompanyName;
	WCHAR*  wszMPKIOrgUnit;
	WCHAR*  wszExch_DIR_DN;
	WCHAR*  wszExch_AD_SERVER;
	WCHAR*  wszExch_SRVR;
	WCHAR*  wszExchVer;
	WCHAR*  wszExchVerStr;
	WCHAR*  wszCommon_Name;
	WCHAR*  wszEmail;
	WCHAR*  wszCERTDN;
	char*   szJurisHash;
	char*   szUTF8CERTDN;  
	char *  szUTF8Common_Name;

}CertReqInfo;

CertReqInfo g_objCertReqInfo;

WCHAR *attrs[6]={
				L"cn",
				L"distinguishedName",
				L"Home-MTA",
				L"rfc822Mailbox",
				L"uid",
				NULL
				};
WCHAR *exch2k_attrs[8]={
						L"cn",
						L"distinguishedName",
						L"Home-MTA",
						L"proxyAddresses",
					    L"mailNickname",
						L"userPrincipalName",
						L"legacyExchangeDN",
						NULL
						};


int					g_nCert_DN_Type=0;
int				    g_nNumOfDNAttrs=0;
const char*			g_inputEncoding=NULL;
BOOL				g_bEXCH2000=TRUE;
BOOL				g_bUTF8=FALSE;
_bstr_t*			g_ptbstrDNAttrs;
_bstr_t*			g_ptbstrDNVals;

/////For exchnage 2000
const char * szCert_DN_Format=NULL;
const char * szExchangeServers=NULL;
const char * szDomainControllers=NULL;


//Local functions
VSAA_STATUS InitExchangeVariable();
BSTR _MultiToWideString(LPSTR szInputString);
LPSTR _WideToMultiString(BSTR szwcInputString);

void ObjecSidEncode(BYTE *pbSid, char **szMySid);
int	 BytesToAscHex(unsigned char* pbVal, int nValSize, char *szVal);

BOOL PrepareLDAPDN(_bstr_t& i_bstrExchangeDN,_bstr_t* o_ptbstrldapDN);
VSAA_STATUS EXCH55_LdapAttrsAndValues(LDAP *ldapConnection,LDAPMessage* results);
VSAA_STATUS EXCH2000_LdapAttrsAndValues(LDAP *ldapConnection,LDAPMessage* results);
static VSAA_STATUS CreateJurisdictionHash_Capi (char **jurisdiction_hash,char *company,
								 char *org,  char *application);


HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN,WCHAR wszDelimiter, int* o_pnNumOfDNAttrs,
							   _bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals);

static VSAA_STATUS CheckAllowedServers55();
static VSAA_STATUS CheckAllowedServers2000();
static VSAA_STATUS GetPostedData(const VSAA_NAME anInput[],FILE *fp);
static VSAA_STATUS CheckCert_DN();
static VSAA_STATUS CheckCommonName();

void FreeGlobalMemory();
WCHAR*   GetAccountName(PSID pMySID) ;
int IsAttributeInclude(WCHAR *a) ;
int IsAttributeIncludeE2k(WCHAR *a);

/*******************************************************************/
VSAA_STATUS VerifyExchange(const VSAA_NAME anInput[], 
						   FILE *fp)
/*
 * Verify user input with the Exchange/Active Directory Directory Information
/*******************************************************************/
{
    VSAA_STATUS		status = VSAA_SUCCESS;
  
	PSID			pMySID;
    char			*szmbMySID = NULL;
	char			pszBinaryFilter[256] = "objectSid=";///different attribute for Active directory
														//to store the SID.
	char			*encodedSid;

	WCHAR			*wszmbMySID=NULL;
	WCHAR			*pwszBinaryFilter=NULL;
   	WCHAR			*wszFullLoginName=NULL;
    

	DWORD			err=0;
	ULONG			version = LDAP_VERSION3;
	WCHAR			*buffer=NULL; 
	LDAP			*ldapConnection =NULL;
	LDAPMessage     *results=NULL;
	

	/*
	#ifdef _DEBUG
    char szMessage [256];
    sprintf (szMessage, "Please attach a debbuger to the process 0x%X (%s) and click OK",
              GetCurrentProcessId(), "VSExchange");
    MessageBox(NULL, szMessage, "CGI Debug Time!",
               MB_OK|MB_SERVICE_NOTIFICATION);
    #endif 
	*/

   
	VS_SetLogFile(fp);
	
	//Get Exchange  Variables from pestub.cfg
	status=InitExchangeVariable();
	if(status!=VSAA_SUCCESS)
		return status;

	if(strcmp(szCert_DN_Format,EXCHANGE_DN_STYLE)==0)
					g_nCert_DN_Type=0;
	
	if(strcmp(szCert_DN_Format,MPKI_DN_STYLE)==0)
					g_nCert_DN_Type=1;
	
	if(strcmp(szCert_DN_Format,CUSTOM_MPKI_DN_STYLE)==0)
					g_nCert_DN_Type=2;

	
	status=GetPostedData(anInput,fp);
	if(status!=VSAA_SUCCESS)
	{
		FreeGlobalMemory();
		return status;
	}

	///////compare the jurisdiction hash
	if( g_nCert_DN_Type!=2)
	{
	
		char  *szJurisHash=NULL;
		int retval=CreateJurisdictionHash_Capi(&szJurisHash,VALUE(I_COMPANY),
								VALUE(I_ORG_UNIT),NULL);
		if(retval!=0)
		{
			FreeGlobalMemory();
			return VSAA_VERIFY_FAILED;

		}

			
		if(strnicmp(szJurisHash,g_objCertReqInfo.szJurisHash,
				strlen(g_objCertReqInfo.szJurisHash))!=0)
		{
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Jurisdiction comparision Failed FDF Hash: %s", g_objCertReqInfo.szJurisHash);
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Jurisdiction comparision Failed computed Hash : %s", szJurisHash);
			FreeGlobalMemory();
			return VSAA_VERIFY_FAILED;
		}

		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "INFO: Jurisdiction FDF Hash: %s", g_objCertReqInfo.szJurisHash);
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "INFO: Jurisdiction computed Hash : %s", szJurisHash);

		if(szJurisHash)
			free(szJurisHash);
	}

	//////Get the SID Information
	if ((pMySID = GetMySid()) == NULL)
    {
       
	   VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Failed to get the My SID");
       return VSAA_VERIFY_FAILED;
    }
    
    szmbMySID = EncodeSid(pMySID);
    wszFullLoginName = GetAccountName(pMySID) ;


	//////Write the Request CertInfo to the log file
	VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "INFO: SID is : %s", szmbMySID);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"INFO: wszFullLoginName is : %s", wszFullLoginName);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: Cert Request attributes:");
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_EXCH_SERVER_AD) : %s", g_objCertReqInfo.wszExch_AD_SERVER);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_EXCH_SRVR) : %s", g_objCertReqInfo.wszExch_SRVR);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_COMPANY) : %s", g_objCertReqInfo.wszMPKICompanyName);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_EXCHANGE_DIR_DN):%s", g_objCertReqInfo.wszExch_DIR_DN);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_COMMON_NAME):%s", g_objCertReqInfo.wszCommon_Name);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_EXCH_VER) : %s", g_objCertReqInfo.wszExchVer);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_EXCH_VER_STR) : %s", g_objCertReqInfo.wszExchVerStr);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_MAIL_EMAIL) : %s", g_objCertReqInfo.wszEmail);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: VALUE(I_CERT_DN) : %s", g_objCertReqInfo.wszCERTDN);
	

	if(wcsnicmp(g_objCertReqInfo.wszExchVer,EXCH_55,wcslen(EXCH_55))==0)
	{
		g_bEXCH2000=FALSE;
		status=CheckAllowedServers55();
		if(status!=VSAA_SUCCESS)
		{
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Allowed List of Exchange Servers : %s", szExchangeServers);
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: Enroll for Exchange Server: %s", g_objCertReqInfo.wszExch_SRVR);
			FreeGlobalMemory();
			return status;
		}
	}

	if(wcsnicmp(g_objCertReqInfo.wszExchVer,EXCH_2000,wcslen(EXCH_2000))==0)
	{
		g_bEXCH2000=TRUE;
		status=CheckAllowedServers2000();
		if(status!=VSAA_SUCCESS)
		{
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Allowed List of Exchange Servers : %s", szExchangeServers);
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: Enroll for Exchange server: %s", g_objCertReqInfo.wszExch_SRVR);

			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Valid List of DomainControllers : %s", szDomainControllers);
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: Enroll for Domain Controller: %s", g_objCertReqInfo.wszExch_AD_SERVER);


			FreeGlobalMemory();
			return status;
		}
	}

		
		
	/////Get the MailBox Information for SID
	ldapConnection = ldap_init(g_objCertReqInfo.wszExch_AD_SERVER, LDAP_PORT );
	if ( ldapConnection == NULL ) {
		err=LdapGetLastError();
		buffer=ldap_err2string(err); 
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_init failed : Error Code: 0x%08X", HRESULT_FROM_WIN32(err));
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: ldap_init failed : Error Desc: %s", buffer);
		return VSAA_VERIFY_FAILED;
		

	}

	// Set the version to 3.0 (default is 2.0).
	err = ldap_set_option(ldapConnection,LDAP_OPT_VERSION,&version);
	if (err != LDAP_SUCCESS) {
		err=LdapGetLastError();
		buffer=ldap_err2string(err); 
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_set_option failed : Error Code : 0x%08X", HRESULT_FROM_WIN32(err));
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: ldap_set_option failed : Error Desc : %s", buffer);
		return VSAA_VERIFY_FAILED;
		
	}
	
	err=ldap_connect(ldapConnection, NULL);
	if (err != LDAP_SUCCESS) {
		err=LdapGetLastError();
		buffer=ldap_err2string(err); 
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_connect failed : Error Code : 0x%08X", HRESULT_FROM_WIN32(err));
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: ldap_connect failed : Error Desc : %s", buffer);
		return VSAA_VERIFY_FAILED;
		
	}
	
	// Bind with the caller's credentials.
	err = ldap_bind_s( ldapConnection, NULL, NULL,LDAP_AUTH_NEGOTIATE);
	if (err != LDAP_SUCCESS) {
		err=LdapGetLastError();
		buffer=ldap_err2string(err); 
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_bind_s failed : Error Code : 0x%08X", HRESULT_FROM_WIN32(err));
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: ldap_bind_s failed : Error Desc : %s", buffer);
		return VSAA_VERIFY_FAILED;
		
	}
	
	if(!g_bEXCH2000)
	{
		wszmbMySID=_MultiToWideString(szmbMySID);
		WCHAR  wszAssocNTValue[1024];
		wcscpy(wszAssocNTValue, L"(Assoc-NT-Account=") ;
		wcscat(wszAssocNTValue, (WCHAR*)wszmbMySID);
		wcscat(wszAssocNTValue, L")");
	
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: szAssocNTValue search string is %s", wszAssocNTValue);
		err=ldap_search_s(ldapConnection,
						g_objCertReqInfo.wszExch_DIR_DN,
						LDAP_SCOPE_SUBTREE,
						wszAssocNTValue, ///// search the mailbox assocaited with SID
						attrs, 
						0, 
						&results );
		if(err!=LDAP_SUCCESS){
				err=LdapGetLastError();
				buffer=ldap_err2string(err); 
				VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_search_s failed : Error Code : 0x%08X", HRESULT_FROM_WIN32(err));
				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__,  L"ERROR: ldap_search_s failed : Error Desc : %s", buffer);
				return VSAA_VERIFY_FAILED;
				
		}

		EXCH55_LdapAttrsAndValues(ldapConnection,results);
	}
	else
	{
		
		ObjecSidEncode((BYTE *)pMySID, &encodedSid);
		strcat( pszBinaryFilter,encodedSid);
		pwszBinaryFilter=_MultiToWideString(pszBinaryFilter);

		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: szObjectEncodedSid search string is %s", pwszBinaryFilter);

		err=ldap_search_s(ldapConnection,
						g_objCertReqInfo.wszExch_DIR_DN,
						LDAP_SCOPE_SUBTREE,
						pwszBinaryFilter,
						exch2k_attrs, 
						0, 
						&results );
		if(err!=LDAP_SUCCESS){
				err=LdapGetLastError();
				buffer=ldap_err2string(err); 
				VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_search_s failed : Error Code: 0x%08X", HRESULT_FROM_WIN32(err));
    		    VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: ldap_search_s failed : Error Desc: %s", buffer);
				return VSAA_VERIFY_FAILED;
				
		}

		EXCH2000_LdapAttrsAndValues(ldapConnection,results);

	}

    ldap_msgfree( results );
	ldap_unbind_s( ldapConnection );
 
	//////Wrint the Mail box attribute to the log file
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: Mailbox attributes from Exchange/AD Server:%s", g_objCertReqInfo.wszExch_AD_SERVER);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: cn:%s", g_objMailBoxInfo.cn);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: rfc822Mailbox:%s", g_objMailBoxInfo.rfc822Mailbox);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: uid:%s", g_objMailBoxInfo.uid);
	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: Home_MTA:%s", g_objMailBoxInfo.Home_MTA);


	//////compare the email id
	for ( DWORD num = 0 ; num < wcslen(g_objMailBoxInfo.rfc822Mailbox) ; num++ )
		  g_objMailBoxInfo.rfc822Mailbox[num] = tolower(g_objMailBoxInfo.rfc822Mailbox[num]) ;

	VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: lowered email address ::%s", g_objMailBoxInfo.rfc822Mailbox);

	if ( wcscmp(g_objCertReqInfo.wszEmail,g_objMailBoxInfo.rfc822Mailbox) == 0 ) 
	{
		    
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: email comparision successful ::%s", g_objMailBoxInfo.rfc822Mailbox);

			_bstr_t        bstrDN= g_objMailBoxInfo.distinguishedName;
			WCHAR wszDelimiter=',';/////ldapDN
			HRESULT hr=_ParseDNIntoComponents(bstrDN,wszDelimiter,&g_nNumOfDNAttrs,
															&g_ptbstrDNAttrs,&g_ptbstrDNVals);
			
			if(hr!=S_OK)
			{
				VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: _ParseDNIntoComponents failed : Error Code: 0x%08X", HRESULT_FROM_WIN32(hr));
				return VSAA_VERIFY_FAILED;
				
			}

			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: ParseDNIntoComponents successful ::%s",
										g_objMailBoxInfo.distinguishedName);
			
			status=CheckCommonName();
			if(status!=VSAA_SUCCESS)
			{
				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: CheckCommonName Failed =%d",status);
	 			return status;
			}
			
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: CheckCommonName successful");
			
			status=CheckCert_DN();
			if(status!=VSAA_SUCCESS)
			{
				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: CheckCert_DN Failed =%d",status);
				return status;
			}

			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: CheckCert_DN successful");
			
	}
	else
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: email comparision FAILED Requested EmailID::%s", g_objCertReqInfo.wszEmail);
	}

	if(wszFullLoginName!=NULL)
			free(wszFullLoginName);

	if(pwszBinaryFilter!=NULL)
		   SysFreeString(pwszBinaryFilter);

	if(wszmbMySID!=NULL)
		   SysFreeString(wszmbMySID);

	FreeGlobalMemory();

	return status;
}

VSAA_STATUS EXCH55_LdapAttrsAndValues(LDAP	*ldapConnection,LDAPMessage* results)
{
	int i=0;
	ULONG			count;
	LDAPMessage     *e=NULL;
	WCHAR			buffer_value[8024];  //To get the value
	WCHAR           *a=NULL, *dn=NULL;
	BerElement      *ber;
	int             Index=0;
	WCHAR			**vals,*buffer=NULL;
	
	VSAA_STATUS status = VSAA_SUCCESS;

	//for each entry print out name + all attrs and values 
	for ( e = ldap_first_entry( ldapConnection, results );
			e != NULL; e = ldap_next_entry( ldapConnection, e ) )
	{
		if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) 
		{
			ldap_memfree( dn );
		}

	
		for ( a = ldap_first_attribute( ldapConnection, e, &ber ); 
				a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ) ) 
		{
			Index=IsAttributeInclude(a);
			if(Index!=-1)
			{
				///////
				if ((vals = ldap_get_values( ldapConnection, e, a)) != NULL ) 
				{
					count=ldap_count_values(vals);			
					for ( i = 0; vals[i] != NULL; i++ ) 
					{
						swprintf(buffer_value, L"%s",  vals[i] );
					}

					ldap_value_free( vals );
				
					switch(Index)
					{
						case 0:
							 wcscpy(g_objMailBoxInfo.cn,buffer_value);
						break;

                        case 1:
							 wcscpy(g_objMailBoxInfo.distinguishedName,buffer_value);
						break;

						case 2:
							wcscpy(g_objMailBoxInfo.Home_MTA,buffer_value);
						break;
						case 3:
							wcscpy(g_objMailBoxInfo.rfc822Mailbox,buffer_value);
						break;
						case 4:
							wcscpy(g_objMailBoxInfo.uid,buffer_value);
						break;
					}
					
				}
			}

			ldap_memfree( a );
		}

		
	}
	

	return status;
}

VSAA_STATUS EXCH2000_LdapAttrsAndValues(LDAP	*ldapConnection,LDAPMessage* results)
{
	int i=0;
	ULONG			count;
	LDAPMessage     *e=NULL;
	WCHAR			buffer_value[8024];  //To get the value
	WCHAR           *a=NULL, *dn=NULL;
	BerElement      *ber;
	int             Index=0;
	WCHAR			**vals,*buffer=NULL;
	
	VSAA_STATUS status = VSAA_SUCCESS;

	//for each entry print out name + all attrs and values 
	for ( e = ldap_first_entry( ldapConnection, results );
			e != NULL; e = ldap_next_entry( ldapConnection, e ) )
	{
		if ( (dn = ldap_get_dn( ldapConnection, e )) != NULL ) 
		{
			ldap_memfree( dn );
		}

		for ( a = ldap_first_attribute( ldapConnection, e, &ber ); 
				a != NULL; a = ldap_next_attribute( ldapConnection, e, ber ) ) 
		{
			Index=IsAttributeIncludeE2k(a);
			if(Index!=-1)
			{
				///////
				if ((vals = ldap_get_values( ldapConnection, e, a)) != NULL ) 
				{
					count=ldap_count_values(vals);			
					for ( i = 0; vals[i] != NULL; i++ ) 
					{
						////////E2k/////////////
						if (Index == 3 && (wcsncmp(L"SMTP:", vals[i], 5) == 0)) {
								swprintf(buffer_value, L"%s",  &vals[i][5] );
								break;

						} 
						////////////////
						swprintf(buffer_value, L"%s",  vals[i] );
					}

					ldap_value_free( vals );
				
					switch(Index)
					{
						case 0:
							 wcscpy(g_objMailBoxInfo.cn,buffer_value);
						break;

                        case 1:
							 wcscpy(g_objMailBoxInfo.UserDN,buffer_value);
						break;

						case 2:
							wcscpy(g_objMailBoxInfo.Home_MTA,buffer_value);
						break;
						case 3:
							wcscpy(g_objMailBoxInfo.rfc822Mailbox,buffer_value);
						break;
						case 4:
							wcscpy(g_objMailBoxInfo.uid,buffer_value);
						break;
						case 5: /////////UPN
							break;
						case 6: /////legacyExchangeDN/////&E2K
							_bstr_t  bstrlegacyExchangeDN=buffer_value;
							_bstr_t  bstrldapFormatDN;

							PrepareLDAPDN(bstrlegacyExchangeDN,&bstrldapFormatDN);
							wcscpy(g_objMailBoxInfo.distinguishedName,bstrldapFormatDN);
						break;
					}
					
				}
			}
			ldap_memfree( a );
		}
	
	}

	return status;
}


static VSAA_STATUS CheckAllowedServers55()
{
	VSAA_STATUS		status = VSAA_VERIFY_FAILED;

	WCHAR *wszdelimiter=L",";
	WCHAR *wszServerName=NULL;
	WCHAR *wszTmpBuffer=NULL;
	
	wszTmpBuffer=_MultiToWideString((char*)szExchangeServers); 
	if(wszTmpBuffer==NULL)
			return VSAA_OUT_OF_MEMORY;
		
		
	/////Allowed Enrollment For All Exchange Server and Active Directory
	if(wcsnicmp(wszTmpBuffer,ALL_ALLOWED,wcslen(ALL_ALLOWED))==0)
	{
			SysFreeString(wszTmpBuffer);
			return VSAA_SUCCESS;
			

	}

	wszServerName=wcstok(wszTmpBuffer,wszdelimiter);
	while(wszServerName!=NULL)
	{
		if(wcsnicmp(wszServerName,g_objCertReqInfo.wszExch_SRVR,
						wcslen(g_objCertReqInfo.wszExch_SRVR))==0)
		{
			status = VSAA_SUCCESS;
			break;

		}
		wszServerName=wcstok(NULL,wszdelimiter);
	}

	if(wszTmpBuffer!=NULL)
		SysFreeString(wszTmpBuffer);
	return status;
}

static VSAA_STATUS CheckAllowedServers2000()
{
	VSAA_STATUS		status = VSAA_VERIFY_FAILED;

	BOOL  bExchServer=FALSE;

	WCHAR *wszdelimiter=L",";
	WCHAR *wszServerName=NULL;
	WCHAR *wszTmpBuffer=NULL;


	//////check for Exchange Server
	wszTmpBuffer=_MultiToWideString((char*)szExchangeServers); 
	if(wszTmpBuffer==NULL)
			return VSAA_OUT_OF_MEMORY;
		
	
	/////Allowed Enrollment For All Exchange Server and Active Directory
	if(wcsnicmp(wszTmpBuffer,ALL_ALLOWED,wcslen(ALL_ALLOWED))==0)
	{
			SysFreeString(wszTmpBuffer);
			return VSAA_SUCCESS;
			

	}

	wszServerName=wcstok(wszTmpBuffer,wszdelimiter);
	while(wszServerName!=NULL)
	{
		if(wcsnicmp(wszServerName,g_objCertReqInfo.wszExch_SRVR,
						wcslen(g_objCertReqInfo.wszExch_SRVR))==0)
		{
			bExchServer=TRUE;
			break;

		}
		wszServerName=wcstok(NULL,wszdelimiter);
	}

	if(wszTmpBuffer!=NULL)
	{
		SysFreeString(wszTmpBuffer);
		wszTmpBuffer=NULL;
	}


	//////check for AD server
	wszTmpBuffer=_MultiToWideString((char*)szDomainControllers); 
	if(wszTmpBuffer==NULL)
			return VSAA_OUT_OF_MEMORY;
		
	
	/////Allowed Enrollment For All Exchange Server and Active Directory
	if(wcsnicmp(wszTmpBuffer,ALL_ALLOWED,wcslen(ALL_ALLOWED))==0)
	{
			SysFreeString(wszTmpBuffer);
			return VSAA_SUCCESS;
			

	}


	wszServerName=NULL;
	wszServerName=wcstok(wszTmpBuffer,wszdelimiter);
	while(wszServerName!=NULL)
	{
		if(wcsnicmp(wszServerName,g_objCertReqInfo.wszExch_AD_SERVER,
						wcslen(g_objCertReqInfo.wszExch_AD_SERVER))==0)
		{
			if(bExchServer)
					status = VSAA_SUCCESS;

			break;

		}
		wszServerName=wcstok(NULL,wszdelimiter);
	}

	if(wszTmpBuffer!=NULL)
		SysFreeString(wszTmpBuffer);

	
	return status;

}


static VSAA_STATUS GetPostedData(const VSAA_NAME anInput[],FILE *fp)
{
	char *szCertDN=NULL;

	///// copy data to local list
    for (int i=0; localData[i].pszName; i++)
    {
        localData[i].pszValue = (char*) FindName (localData[i].pszName, strlen(localData[i].pszName), 
												  anInput);
		
        if (localData[i].pszValue == NULL)
		{

	        fprintf(fp,"ERROR: Missing input Value %s\n",localData[i].pszName);
	        return VSAA_VERIFY_FAILED;
		}
    }
    
	///////Get all the Request Information
	g_inputEncoding = FindName(VSAA_ENCODING_NAME,strlen(VSAA_ENCODING_NAME),
							   anInput);

	szCertDN=(char*)FindName(VSAA_CERT_DN,strlen(VSAA_CERT_DN),
							   anInput);

	if(g_nCert_DN_Type!=2 && szCertDN==NULL)
	{
				
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: Missing input Value Cert_DN");
	    return VSAA_VERIFY_FAILED;
	}



	if(szCertDN!=NULL && g_nCert_DN_Type!=2)
	{		
		g_objCertReqInfo.wszCERTDN=_MultiToWideString(szCertDN);
		if(g_objCertReqInfo.wszCERTDN==NULL)
		{
			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
			return VSAA_OUT_OF_MEMORY;
		}
	
	
	}
	else
	{
		g_objCertReqInfo.wszCERTDN=_MultiToWideString("none");
	}

	
	

	g_objCertReqInfo.wszMPKICompanyName=_MultiToWideString(VALUE(I_COMPANY));
	if(g_objCertReqInfo.wszMPKICompanyName==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}

	g_objCertReqInfo.wszMPKIOrgUnit=_MultiToWideString(VALUE(I_ORG_UNIT));
	if(g_objCertReqInfo.wszMPKIOrgUnit==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}


	g_objCertReqInfo.wszExch_DIR_DN=_MultiToWideString(VALUE(I_EXCHANGE_DIR_DN));
	if(g_objCertReqInfo.wszExch_DIR_DN==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}

	g_objCertReqInfo.wszExch_AD_SERVER=_MultiToWideString(VALUE(I_EXCH_SERVER_AD));
	if(g_objCertReqInfo.wszExch_AD_SERVER==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}

	g_objCertReqInfo.wszExch_SRVR=_MultiToWideString(VALUE(I_EXCH_SRVR));
	if(g_objCertReqInfo.wszExch_SRVR==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}


	g_objCertReqInfo.wszExchVer=_MultiToWideString(VALUE(I_EXCH_VER));
	if(g_objCertReqInfo.wszExchVer==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}

	g_objCertReqInfo.wszExchVerStr=_MultiToWideString(VALUE(I_EXCH_VER_STR));
	if(g_objCertReqInfo.wszExchVerStr==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
		return VSAA_OUT_OF_MEMORY;
	}
	
	g_objCertReqInfo.wszCommon_Name=_MultiToWideString(VALUE(I_COMMON_NAME));
	if(g_objCertReqInfo.wszCommon_Name==NULL)
	{
		return VSAA_OUT_OF_MEMORY;
	}

	g_objCertReqInfo.wszEmail=_MultiToWideString(VALUE(I_MAIL_EMAIL));
	if(g_objCertReqInfo.wszEmail==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: _MultiToWideString Failed");
	    return VSAA_OUT_OF_MEMORY;	
	}


	g_objCertReqInfo.szJurisHash=VALUE(I_JURIS_HASH);
	if(g_objCertReqInfo.szJurisHash==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: Memory Allocation Failed");
		return VSAA_OUT_OF_MEMORY;
	}

	return VSAA_SUCCESS;

}

void FreeGlobalMemory()
{
	
	if(g_objCertReqInfo.szUTF8CERTDN!=NULL)
			free(g_objCertReqInfo.szUTF8CERTDN);

	if(g_objCertReqInfo.szUTF8Common_Name!=NULL)
			free(g_objCertReqInfo.szUTF8Common_Name);

	if(g_objCertReqInfo.wszCERTDN!=NULL)
			SysFreeString(g_objCertReqInfo.wszCERTDN);

	if(g_objCertReqInfo.wszCommon_Name!=NULL)
			SysFreeString(g_objCertReqInfo.wszCommon_Name);

	if(g_objCertReqInfo.wszEmail!=NULL)
			SysFreeString(g_objCertReqInfo.wszEmail);

	if(g_objCertReqInfo.wszExch_AD_SERVER!=NULL)
			SysFreeString(g_objCertReqInfo.wszExch_AD_SERVER);

	if(g_objCertReqInfo.wszExch_SRVR!=NULL)
			SysFreeString(g_objCertReqInfo.wszExch_SRVR);

	if(g_objCertReqInfo.wszExch_DIR_DN!=NULL)
			SysFreeString(g_objCertReqInfo.wszExch_DIR_DN);

	if(g_objCertReqInfo.wszExchVer!=NULL)
			SysFreeString(g_objCertReqInfo.wszExchVer);

	if(g_objCertReqInfo.wszMPKICompanyName!=NULL)
			SysFreeString(g_objCertReqInfo.wszMPKICompanyName);

	if(g_objCertReqInfo.wszMPKIOrgUnit!=NULL)
			SysFreeString(g_objCertReqInfo.wszMPKIOrgUnit);

	/*
	if(szCert_DN_Format!=NULL)
		free(szCert_DN_Format);
	if(szExchangeServers!=NULL)
		free(szExchangeServers);
	if(szDomainControllers!=NULL)
		free(szDomainControllers);
	*/

}
/*******************************************************************/
static VSAA_STATUS CheckCert_DN()
/*******************************************************************/
{
   
	VSAA_STATUS status = VSAA_SUCCESS;
	
	WCHAR   *wszFormatedCERTDN=NULL;
	char    *szUTF8FormatedCERTDN=NULL;

	
	DWORD    dwDNLen=wcslen(g_objMailBoxInfo.distinguishedName);
    wszFormatedCERTDN=(WCHAR*)new WCHAR[dwDNLen+256];
	if(wszFormatedCERTDN==NULL)
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: Memory Allocation Failed");
		return VSAA_OUT_OF_MEMORY;
	}
    memset(wszFormatedCERTDN,0,dwDNLen);

	if(g_nCert_DN_Type==0)
	{
		for(int i=0; i<g_nNumOfDNAttrs;i++)
			{
				wcscat(wszFormatedCERTDN,g_ptbstrDNAttrs[i]);
				wcscat(wszFormatedCERTDN,L"=");
				if(g_bUTF8)
					wcscat(wszFormatedCERTDN,L"<0C>");

				if(i==0)
				{
					wcscat(wszFormatedCERTDN,L"\"");
					wcscat(wszFormatedCERTDN,g_objMailBoxInfo.uid);		/////alias
					wcscat(wszFormatedCERTDN, L" (") ;
					wcscat(wszFormatedCERTDN, g_objMailBoxInfo.cn) ;	/////First Name Last Name
					wcscat(wszFormatedCERTDN, L", ") ;
					wcscat(wszFormatedCERTDN, g_objCertReqInfo.wszMPKICompanyName) ;    /////CompanyName
					wcscat(wszFormatedCERTDN, L")\",") ;
					continue;
				}

				wcscat(wszFormatedCERTDN,L"\"");
				wcscat(wszFormatedCERTDN,g_ptbstrDNVals[i]);
				wcscat(wszFormatedCERTDN,L"\"");
				if(i!=g_nNumOfDNAttrs-1)
					wcscat(wszFormatedCERTDN,L",");
			}

			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: wszFormatedCERTDN ::%s",
										wszFormatedCERTDN);

			/////compare the Cert_DN
			if(g_inputEncoding != NULL && strlen(g_inputEncoding) > 0)
			{
				g_bUTF8=TRUE;
				int rc = NativeToUTF8(&g_objCertReqInfo.szUTF8CERTDN, 
									  _WideToMultiString(g_objCertReqInfo.wszCERTDN),
									  g_inputEncoding);

				szUTF8FormatedCERTDN=LDAP_UTF16ToUTF8(wszFormatedCERTDN,wcslen(wszFormatedCERTDN));

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: g_objCertReqInfo.szUTF8CERTDN ::%s",
										g_objCertReqInfo.szUTF8CERTDN);

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: szUTF8FormatedCERTDN ::%s",
										szUTF8FormatedCERTDN);

				if(memcmp(szUTF8FormatedCERTDN,g_objCertReqInfo.szUTF8CERTDN,
											strlen(g_objCertReqInfo.szUTF8CERTDN))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
								
			}
			else
			{
				if(memcmp(wszFormatedCERTDN,g_objCertReqInfo.wszCERTDN,
												wcslen(g_objCertReqInfo.wszCERTDN))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
			}
	}

	if(g_nCert_DN_Type==1)     /////cn=FirstName,ou=MPKIOrgUnit,o=MPKICompanyName
	{
			wcscat(wszFormatedCERTDN,L"cn=");
			if(g_bUTF8)
				wcscat(wszFormatedCERTDN,L"<0C>");
			wcscat(wszFormatedCERTDN,L"\"");
			wcscat(wszFormatedCERTDN, g_objMailBoxInfo.cn) ;		
			wcscat(wszFormatedCERTDN, L"\",") ;

			wcscat(wszFormatedCERTDN,L"ou=");
			if(g_bUTF8)
				wcscat(wszFormatedCERTDN,L"<0C>");

			wcscat(wszFormatedCERTDN,L"\"");
			wcscat(wszFormatedCERTDN, g_objCertReqInfo.wszMPKIOrgUnit) ;		
			wcscat(wszFormatedCERTDN, L"\",") ;


			wcscat(wszFormatedCERTDN,L"o=");
			if(g_bUTF8)
				wcscat(wszFormatedCERTDN,L"<0C>");
			wcscat(wszFormatedCERTDN,L"\"");
			wcscat(wszFormatedCERTDN, g_objCertReqInfo.wszMPKICompanyName) ;		
			wcscat(wszFormatedCERTDN, L"\"") ;

			VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: wszFormatedCERTDN ::%s",
										wszFormatedCERTDN);

			/////compare the Cert_DN
			if(g_inputEncoding != NULL && strlen(g_inputEncoding) > 0)
			{
				g_bUTF8=TRUE;
				int rc = NativeToUTF8(&g_objCertReqInfo.szUTF8CERTDN, 
									  _WideToMultiString(g_objCertReqInfo.wszCERTDN),
									  g_inputEncoding);

				szUTF8FormatedCERTDN=LDAP_UTF16ToUTF8(wszFormatedCERTDN,wcslen(wszFormatedCERTDN));

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: g_objCertReqInfo.szUTF8CERTDN ::%s",
										g_objCertReqInfo.szUTF8CERTDN);

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: szUTF8FormatedCERTDN ::%s",
										szUTF8FormatedCERTDN);

				if(memcmp(szUTF8FormatedCERTDN,g_objCertReqInfo.szUTF8CERTDN,
											strlen(g_objCertReqInfo.szUTF8CERTDN))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
				
			}
			else
			{
				

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: wszFormatedCERTDN ::%s",
										wszFormatedCERTDN);

				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: g_objCertReqInfo.wszCERTDN ::%s",
										g_objCertReqInfo.wszCERTDN);


				if(memcmp(wszFormatedCERTDN,g_objCertReqInfo.wszCERTDN,
												wcslen(g_objCertReqInfo.wszCERTDN))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"Error: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
			}

	}


	if(g_nCert_DN_Type==2)     ///Decide by Back End
	{
		VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"INFO: CERT DN DONE");

	}
   return status;
}



/*******************************************************************/
static VSAA_STATUS CheckCommonName()
/*
 * 
/*******************************************************************/
{
	VSAA_STATUS status = VSAA_SUCCESS;
	
	WCHAR    *wszFormatedCommon_Name=NULL;
	char     *szUTF8FormatedCommon_Name=NULL;
	char     *szUTF8Common_Name=NULL;


   if(g_nCert_DN_Type==0)
   {
	   		DWORD    dwDNLen=wcslen(g_objCertReqInfo.wszCommon_Name);
			szUTF8FormatedCommon_Name=(char*)new char[dwDNLen+256];
			wszFormatedCommon_Name=(WCHAR*)new WCHAR[dwDNLen];
			if(wszFormatedCommon_Name==NULL)
			{
				VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: Memory Allocation Failed");
				return VSAA_OUT_OF_MEMORY;
			}
				
			memset(wszFormatedCommon_Name,0,dwDNLen);

			wcscat(wszFormatedCommon_Name,g_objMailBoxInfo.uid);		/////alias
			wcscat(wszFormatedCommon_Name, L" (") ;
			wcscat(wszFormatedCommon_Name, g_objMailBoxInfo.cn) ;	/////First Name Last Name
			wcscat(wszFormatedCommon_Name, L", ") ;
			wcscat(wszFormatedCommon_Name, g_objCertReqInfo.wszMPKICompanyName) ;    /////CompanyName
			wcscat(wszFormatedCommon_Name, L")") ;
			

			//////compare the Common Name
			if(g_inputEncoding != NULL && strlen(g_inputEncoding) > 0)
			{
				g_bUTF8=TRUE;
				int rc = NativeToUTF8(&g_objCertReqInfo.szUTF8Common_Name, 
									  _WideToMultiString(g_objCertReqInfo.wszCommon_Name),
									  g_inputEncoding);

				  
				  
				  LdapUnicodeToUTF8(wszFormatedCommon_Name,wcslen(wszFormatedCommon_Name),
									szUTF8FormatedCommon_Name,dwDNLen+256);  

				//szUTF8FormatedCommon_Name=LDAP_UTF16ToUTF8(wszFormatedCommon_Name,wcslen(wszFormatedCommon_Name));
				if(memcmp(szUTF8FormatedCommon_Name,g_objCertReqInfo.szUTF8Common_Name,
											strlen(g_objCertReqInfo.szUTF8Common_Name))!=0)
				{
					status=VSAA_VERIFY_FAILED;
				}
				
			}
			else
			{
				if(memcmp(wszFormatedCommon_Name,g_objCertReqInfo.wszCommon_Name,
												wcslen(g_objCertReqInfo.wszCommon_Name))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
			}
   }
   
   if(g_nCert_DN_Type==1 || g_nCert_DN_Type==2)
   {
			//////compare the Common Name
			if(g_inputEncoding != NULL && strlen(g_inputEncoding) > 0)
			{
				g_bUTF8=TRUE;
				int rc = NativeToUTF8(&g_objCertReqInfo.szUTF8Common_Name, 
									  _WideToMultiString(g_objCertReqInfo.wszCommon_Name),
									  g_inputEncoding);

				szUTF8Common_Name=LDAP_UTF16ToUTF8(g_objMailBoxInfo.cn,wcslen(g_objMailBoxInfo.cn));
				if(memcmp(szUTF8Common_Name,g_objCertReqInfo.szUTF8Common_Name,
											strlen(g_objCertReqInfo.szUTF8Common_Name))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
				
			}
			else
			{
				if(memcmp(g_objMailBoxInfo.cn,g_objCertReqInfo.wszCommon_Name,
												wcslen(g_objCertReqInfo.wszCommon_Name))!=0)
				{
					VSAA_LogW(VS_LOG_INFO,  __LINE__, __FILE__, L"ERROR: memcmp failed Failed");
					status=VSAA_VERIFY_FAILED;
				}
			}


   }

    if(wszFormatedCommon_Name!=NULL)
		delete wszFormatedCommon_Name;

	if(szUTF8FormatedCommon_Name!=NULL)
		free(szUTF8FormatedCommon_Name);

	if(szUTF8Common_Name!=NULL)
		free(szUTF8FormatedCommon_Name);

   return status;
}

int IsAttributeInclude(WCHAR *a)
{
	for (int i=0;i<5;i++)
	{
		if(!_wcsicmp(attrs[i],a))
				return i;
	}
	return -1;
}

WCHAR *  GetAccountName(PSID pMySID)
{

    WCHAR   *w_szName, *w_szDomain, *w_szFull ;

	w_szName = (WCHAR*) malloc(1024);
	w_szDomain = (WCHAR*) malloc(1024);
	w_szFull = (WCHAR*) malloc(1024);

        DWORD           dwName = 512, dwDomain = 512 ;
        SID_NAME_USE 	sidNameUse ;

        if ( !LookupAccountSidW(NULL,pMySID,
                                w_szName,
                                &dwName,
                                w_szDomain,
                                &dwDomain,
                                &sidNameUse) )
        {
                printf("error man!!!") ;
        }

        wcscpy(w_szFull, w_szDomain) ;
        wcscat(w_szFull, L"\\") ;
        wcscat(w_szFull, w_szName) ;

        if(w_szName!=NULL)
                  free(w_szName);

        if(w_szDomain!=NULL)
                  free(w_szDomain);

/*
        if(szName!=NULL)
                        free(szName) ;
        if(szDomain!=NULL)
                        free(szDomain) ;
*/

        return w_szFull ;
}


HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN,WCHAR wszDelimiter, int* o_pnNumOfDNAttrs,
							   _bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals)
{

	WCHAR*			pwszTempStr;
	HRESULT			retVal = S_OK;
	_bstr_t			tbstrFirstDNAttr = "";
	_bstr_t			tbstrFirstDNVal = "";
	UINT			nFirstDNValLen = 0;

	if(i_tbstrSubjectDN.length() == 0)
	{
		*o_pnNumOfDNAttrs = 0;
		return S_OK;
	}

	//Copy the inputted dn into a temporary string
	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrSubjectDN.length()+1];
	if(!pwszTempStr)
		retVal = E_FAIL;
	
	for(unsigned int i=0;i<i_tbstrSubjectDN.length();++i)
		pwszTempStr[i] = ((WCHAR*)(i_tbstrSubjectDN))[i];
	pwszTempStr[i] = L'\0';

	//Obtain the first component type
	WCHAR *pwszStartPtr, *pwszEndPtr, *pwszSpacePtr;
	BOOL boolDone = FALSE;
	int nState = 0;

	pwszStartPtr = pwszTempStr;
	
	do
	{
		switch(nState)
		{
		case 0:
			if(*pwszStartPtr == L' ')
				pwszStartPtr ++;
			else if(*pwszStartPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else if(*pwszStartPtr == wszDelimiter)   ////Delimitor for LDAP DN
			{
				pwszStartPtr ++;
			}
			else
			{
				pwszEndPtr = pwszStartPtr+1;
				nState = 1;
			}

			break;

		case 1:
			if(*pwszEndPtr == L' ')
			{
				*pwszEndPtr = '\0';
				pwszEndPtr++;
			}
			else if(*pwszEndPtr == L'=')
			{
				*pwszEndPtr = '\0';
				boolDone = TRUE;
			}
		
			else if(*pwszEndPtr == L'\0')
			{
				boolDone = TRUE;
				retVal = E_DNPARSEERR;
			}
			else
			{
				pwszEndPtr++;
			}
			break;

		}
	}while(!boolDone);

	if(retVal == S_OK)
	{
		tbstrFirstDNAttr = pwszStartPtr;
		pwszStartPtr = ++pwszEndPtr;
		pwszSpacePtr = pwszEndPtr;
		boolDone = FALSE;
		nState = 0;

		do
		{
			//Now obtain the first component value
			switch(nState)
			{
			case 0:
				if(*pwszStartPtr == L' ')
					pwszStartPtr ++;
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else if(*pwszStartPtr == L'\"')
				{
					pwszEndPtr = pwszStartPtr+1;
					nState = 2;
				}
				else if(*pwszStartPtr == L'<')		// Parsing out "<>" if present
				{
					pwszStartPtr ++;
					nState = 3;
				}
				else if(*pwszStartPtr == L'#')		 // we do not support non-printable strings yet
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
				{
					pwszEndPtr = pwszStartPtr+1;
					nState = 1;
				}
				break;

			case 1:
				if(*pwszEndPtr == L' ')
				{
					pwszEndPtr++;
					
				}
				else if(*pwszEndPtr == wszDelimiter)   ////Delimitor for ldap DN
				{
					*pwszSpacePtr = '\0';
					pwszEndPtr++;
					boolDone = TRUE;
				}
				else if(*pwszEndPtr == L'\0')
				{
					boolDone = TRUE;
					pwszSpacePtr = '\0';
				}
				else if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					nState = 2;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 2:
				if(*pwszEndPtr == L'\"')
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
					nState = 1;
				}
				else
				{
					pwszEndPtr++;
					pwszSpacePtr = pwszEndPtr;
				}
				break;

			case 3:
				if(*pwszStartPtr == L'>')
				{
					pwszStartPtr ++;
					nState = 0;
				}
				else if(*pwszStartPtr == L'\0')
				{
					boolDone = TRUE;
					retVal = E_DNPARSEERR;
				}
				else
					pwszStartPtr ++;
				break;

			}
		}while(!boolDone);
	}

	if(retVal == S_OK)
	{
		WCHAR wcTemp[2];
		wcTemp[0] = '\0';
		nFirstDNValLen = wcslen(pwszStartPtr);
		UINT i = 0;

		// Strip out the quotes from the beginning and end of the string if any. Also if two
		// consecutive quotes are present keep only one because that is the way 'MyCertNameTStr()'
		// has created it
		if(pwszStartPtr[i] == L'"')
		{
			i++;
			nFirstDNValLen--;
		}
		
		for(; i < nFirstDNValLen; i++)
		{
			if(wcTemp[0] == L'"' && pwszStartPtr[i] == L'"')
			{
				wcTemp[0] = '\0';
				continue;
			}

			wcTemp[0] = pwszStartPtr[i];
			wcTemp[1] = '\0';

			tbstrFirstDNVal += wcTemp;
		}

		//Obtain the remaining components
		_bstr_t tbstrRemainingDN = "";
		_bstr_t* ptbstrRemainingAttrs = NULL;
		_bstr_t* ptbstrRemainingVals = NULL;
		int nRemainingAttrs = 0;

		tbstrRemainingDN = pwszEndPtr;
		retVal = _ParseDNIntoComponents(tbstrRemainingDN,wszDelimiter, &nRemainingAttrs, &ptbstrRemainingAttrs,
			&ptbstrRemainingVals);
		if(retVal == S_OK)
		{
			//Allocate space for all the attributes and values
			*o_pnNumOfDNAttrs = nRemainingAttrs + 1;
			*o_pptbstrDNAttrs = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];
			*o_pptbstrDNVals = (_bstr_t*) new _bstr_t[*o_pnNumOfDNAttrs];

			//Save all the attributes and values
			(*o_pptbstrDNAttrs)[0] = tbstrFirstDNAttr;
			(*o_pptbstrDNVals)[0] = tbstrFirstDNVal;

			for(int i=0;i<nRemainingAttrs;++i)
			{
				(*o_pptbstrDNAttrs)[i+1] = ptbstrRemainingAttrs[i];
				(*o_pptbstrDNVals)[i+1] = ptbstrRemainingVals[i];
			}
			delete[] ptbstrRemainingAttrs;
			delete[] ptbstrRemainingVals;
		}

	}

	delete[] pwszTempStr;
	return retVal;
	
}




VSAA_STATUS InitExchangeVariable()
{
	#define CONFIG(X)	FindName(X, strlen(X), configData)
	static VSAA_NAME configData[] =
	{
		
		{CFG_CERT_DN_FORMAT,		"none"},
       	{CFG_EXCHANGE_SERVERS,	    "none"},
		{CFG_DOMAIN_CONTROLLERS,    "none"},
		
		{NULL, NULL}
	};

	VSAA_STATUS rc;
	
	int i;
		
	if ((rc = GetConfig(CFG_FILE, configData)) != VSAA_SUCCESS)
		return rc;
	
	/* Ensure that all parameters are present */
	for (i=0; configData[i].pszName; i++)
	{
		if((configData[i].pszName==NULL) && (configData[i].pszValue == NULL))
			return VSAA_BAD_CONFIG_FILE;
	}

	szCert_DN_Format = CONFIG(CFG_CERT_DN_FORMAT);
	if (!strcmp(szCert_DN_Format, "none"))
	{
		szCert_DN_Format = NULL;
		return VSAA_BAD_CONFIG_FILE;
	}

	szExchangeServers = CONFIG(CFG_EXCHANGE_SERVERS);
	if (!strcmp(szExchangeServers, "none"))
		szExchangeServers = NULL;
	szDomainControllers = CONFIG(CFG_DOMAIN_CONTROLLERS);
	if (!strcmp(szDomainControllers, "none"))
		szDomainControllers = NULL;

	/////Init the Global CertReqInfo

	g_objCertReqInfo.wszMPKICompanyName=NULL;
	g_objCertReqInfo.wszMPKIOrgUnit=NULL;
	g_objCertReqInfo.wszExch_DIR_DN=NULL;
	g_objCertReqInfo.wszExch_AD_SERVER=NULL;
	g_objCertReqInfo.wszExch_SRVR=NULL;
	g_objCertReqInfo.wszExchVer=NULL;
	g_objCertReqInfo.wszCommon_Name=NULL;
	g_objCertReqInfo.wszEmail=NULL;
	g_objCertReqInfo.wszCERTDN=NULL;
	g_objCertReqInfo.szUTF8CERTDN=NULL;
	g_objCertReqInfo.szUTF8Common_Name=NULL;
	g_objCertReqInfo.szJurisHash=NULL;


    return VSAA_SUCCESS;
}


BOOL PrepareLDAPDN(_bstr_t& i_bstrExchangeDN, _bstr_t* o_ptbstrldapDN)
{

	HRESULT hr;

    _bstr_t*				ptbstrDNAttrs;
    _bstr_t*				ptbstrDNVals;
    int					    nNumOfDNAttrs=0;
	WCHAR                   wszDelimiter='/';

	hr=_ParseDNIntoComponents(i_bstrExchangeDN,wszDelimiter,&nNumOfDNAttrs,&ptbstrDNAttrs,&ptbstrDNVals);
	if(hr==S_OK)
	{
        for(int i=0; i<nNumOfDNAttrs;i++)
		{
	
			*o_ptbstrldapDN+=ptbstrDNAttrs[nNumOfDNAttrs-i-1];
			*o_ptbstrldapDN+=L"=";
			*o_ptbstrldapDN+=L"\"";
			*o_ptbstrldapDN+=ptbstrDNVals[nNumOfDNAttrs-i-1];
			*o_ptbstrldapDN+=L"\"";
			if(i!=nNumOfDNAttrs-1)
				*o_ptbstrldapDN+=L",";
		}
	}
	else
	{
		VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: PrepareLDAPDN_ParseDNIntoComponents failed : Error Code: 0x%08X", HRESULT_FROM_WIN32(hr));
		return FALSE;
	}


	return TRUE;
}



int IsAttributeIncludeE2k(WCHAR* a)
{
	//////E2K/////
	for (int i=0;i<8;i++)
	{
		if(!_wcsicmp(exch2k_attrs[i],a))
				return i;
	}
	return -1;
}


void ObjecSidEncode(BYTE *pbSid, char **szMySid)
{
	/////Sid 28 byte
	char *szTemp = (char*)malloc(28*3);
	*szMySid=(char*)malloc(28*3);

	int j=0;

	char *szAscHex = (char *)malloc(3);;

	for(int i=0;i<28;i++)
	{
		if((pbSid[i]<=0x40 || pbSid[i]>0x5a) && (pbSid[i]<0x61 || pbSid[i]>0x7a)&&
			(pbSid[i]<0x30 || pbSid[i]>0x39))
		{
			//convert binary to hex representation
			szTemp[j] = '\\';
			j++;
			BytesToAscHex(&pbSid[i], 1, szAscHex);
			memcpy(&szTemp[j], szAscHex, 2);
			j += 2;
			
		}
		else
		{
			//convert binary to acsii value
			szTemp[j] = pbSid[i];
			j++;

		}
	}
	szTemp[j] = '\0';
	*szMySid = szTemp;
}

int BytesToAscHex(unsigned char* pbVal, int nValSize, char* szVal)
{

	char szDigitAscVal[] = "0123456789ABCDEF";
	char szDigit[2];

	szDigit[1] = '\0';
	for(int i=0,j = 0;i<nValSize;++i, j+=2)
	{
		szDigit[0] = szDigitAscVal[((pbVal[i] & 0xF0)>>4)];
		szVal[0] =  szDigit[0];
		szDigit[0] = szDigitAscVal[(pbVal[i] & 0x0F)];
		szVal[1] = szDigit[0];
	}
	szVal[2] = '\0';

	return 1;
}

static VSAA_STATUS CreateJurisdictionHash_Capi (
												char **jurisdiction_hash,
												char *company,
												char *org,
												char *application
												)
{

		BOOL				bResult=FALSE;
		HCRYPTHASH			hHash;
		DWORD				dwBufferSize,dwInputDataLen,err=0;
		PBYTE				pBuffer=NULL;
		int					digestLen=0;
		char				*szJurisdictionHash=NULL;

		_bstr_t				bstrJurisdiction="";
		_bstr_t				bstrSEP=kSEPARATOR;


		HCRYPTPROV			hProv;


		if ((application != NULL) && 
			(strstr(application, ONSITE_TEST_DRIVE) != NULL))
		{
			bstrJurisdiction += ONSITE_TEST_DRIVE;
			bstrJurisdiction += company;
		}
		else
			bstrJurisdiction += company;

		 if (strlen(org) > 0)
				bstrJurisdiction += bstrSEP + org;


        dwInputDataLen=bstrJurisdiction.length();
		szJurisdictionHash=(char*)malloc(dwInputDataLen);
		if(szJurisdictionHash==NULL)
		{
			return VSAA_OUT_OF_MEMORY;
		}

		strcpy(szJurisdictionHash,bstrJurisdiction);
		bstrJurisdiction="";

		bResult = CryptAcquireContext(
            &hProv,              
            NULL,                // Use default key container.
            NULL,				 // Use default CSP.
            PROV_RSA_FULL,       
            CRYPT_VERIFYCONTEXT );  
		
		if(!bResult)
		{
			err=GetLastError();
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: CryptAcquireContext failed : Error Code: 0x%08X\n", HRESULT_FROM_WIN32(err));
    		return VSAA_VERIFY_FAILED;
		}

		// Obtain handle to hash object.
		bResult = CryptCreateHash(
					hProv,               
					CALG_MD5,            // Hashing algorithm
					0,                   
					0,                   
					&hHash);             

		if(!bResult)
		{
			err=GetLastError();
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: CryptCreateHash failed : Error Code: 0x%08X\n", HRESULT_FROM_WIN32(err));
    		return VSAA_VERIFY_FAILED;

		}

		// Hash data.
		bResult = CryptHashData(
					hHash,               
					(PBYTE)szJurisdictionHash,             // Pointer to data buffer
					dwInputDataLen,    // Length of data
					0);                 
		if(!bResult)
		{
			err=GetLastError();
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: CryptHashData failed : Error Code: 0x%08X\n", HRESULT_FROM_WIN32(err));
    		return VSAA_VERIFY_FAILED;

		}

		if(szJurisdictionHash!=NULL)
				free(szJurisdictionHash);

	

		// Get hash value.
		bResult = CryptGetHashParam(hHash,              
									HP_HASHVAL,         
									NULL,            
									&dwBufferSize,     
									0);                

		if(!bResult)
		{
			err=GetLastError();
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: CryptGetHashParam failed : Error Code: 0x%08X\n", HRESULT_FROM_WIN32(err));
    		return VSAA_VERIFY_FAILED;

		}



		// Create buffer to hold hash value.
		pBuffer = (PBYTE)malloc(dwBufferSize);

		// Get hash value.
		bResult = CryptGetHashParam(
					hHash,              
					HP_HASHVAL,         
					pBuffer,            
					&dwBufferSize,      
					0);                 

		if(!bResult)
		{
			err=GetLastError();
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: CryptGetHashParam failed : Error Code: 0x%08X\n", HRESULT_FROM_WIN32(err));
    		return VSAA_VERIFY_FAILED;

		}

		// Release hash object.
		if(hHash)
			CryptDestroyHash(hHash);

		CryptReleaseContext(hProv,0); 

		
		int retval=Bin2Hasc(jurisdiction_hash,pBuffer,dwBufferSize);
		if(!retval)
		{
			VSAA_Log(VS_LOG_INFO,  __LINE__, __FILE__,  "ERROR: Bin2Hasc failed" );
			return VSAA_VERIFY_FAILED;
		}
		

		if(pBuffer)
			free(pBuffer);


	return VSAA_SUCCESS;
}
