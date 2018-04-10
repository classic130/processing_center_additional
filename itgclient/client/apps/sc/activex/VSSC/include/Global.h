///////////////////////Constant,defination and Headers files////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef __VSSC_GLOBAL_H_
#define __VSSC_GLOBAL_H_



#include <list>

class CUserInfo;
using namespace std ;
typedef list<CUserInfo *> CListUserInfo;

//using namespace std ;
//#include <list>
typedef list<CAttachInfo *> ATTACH_FILE_INFO;




///////Global def and Constant////////////////
#define			CHECK_INIT					0x0001 
#define			CHECK_CERTURL				0x0002 
#define         CHECK_SCTYPE				0x0004
#define         CHECK_RESFIRST				0x0008
#define         CHECK_PTAVER				0x0010


#define         USE_PRC_FOR_NOT_FOUND       0x0001
#define         USE_PRC_FOR_EXPIRED		    0x0002
#define         USE_PRC_FOR_REVOKED         0x0004


#define		RSA_MIN_PAD_LEN						11
#define		VS_MAX_LEN        256

#define		SCRIPT_HASH_MD2						2
#define		SCRIPT_HASH_MD5						3
#define		SCRIPT_HASH_SHA1					4


#define		VS_SHA_1							32772
#define		VS_MD2								32769
#define		VS_MD5								32771

#define		NO_CHAIN_VALIDATE_ONCLIENT			-1
#define		NO_PARSE_OCSP_RESPONSE				-1   


#define		VS_MD2_OID							szOID_RSA_MD2
#define		VS_MD5_OID							szOID_RSA_MD5
#define		VS_SHA1_OID							szOID_OIWSEC_sha1

#define		MY_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

typedef enum _VSSC_MSG_TYPE
{
	VSSC_MSG_PLAINTEXT,
	VSSC_MSG_SIGNED,
	VSSC_MSG_ENCRYPT,
	VSSC_MSG_SIGN_ENCRYPT,
	VSSC_MSG_OPAQUE_SIGN
} VSSC_MSG_TYPE ;

typedef struct _VSSC_SIGN_CERT
{	
		char *szCertIssuerDN;
		char *szCertSerialNum;
		char *szDigestAlgoID;
		char *szSMIMECapabilities;
	

}VSSC_SIGN_CERT,*PVSSC_SIGN_CERT;

typedef struct _VSSC_ENCRYPT_CERT
{	
		 
		char *szCertIssuerDN;
		char *szCertSerialNum;
		char *szDigestAlgoID;
		PCERT_PUBLIC_KEY_INFO    pEncryptPublicKeyInfo;
		PCERT_INFO				 pEncryptCertInfo;

}VSSC_ENCRYPT_CERT,*PVSSC_ENCRYPT_CERT;

typedef struct _VSSC_HASH_MESSAGE_PARA
{
	int			i_nHashAlg;
	TCHAR		*szMIMEMsg;
	DWORD		dwMIMESize;
	_bstr_t		bstrSMIMECap;
	_bstr_t		bstrDigestAlgoID;
	PCERT_INFO	pSignerCert;
}
VSSC_HASH_MESSAGE_PARA ,*PVSSC_HASH_MESSAGE_PARA;

typedef struct _VSSC_ENCODED_CERT
{

	BYTE   *pbData;
	DWORD   cbData;
}
VSSC_ENCODED_CERT ,*PVSSC_ENCODED_CERT;

typedef struct _VSSC_CERT_RDN_INFO
{
	_bstr_t     bstrSerialNum;
	_bstr_t     bstrIssuerDN;
	_bstr_t     bstrSubjectDN;
	_bstr_t     bstrEmailID; 

}
VSSC_CERT_RDN_INFO,*PVSSC_CERT_RDN_INFO;


typedef struct _VSSC_SIGN_MESSAGE_PARA
{
	int				i_nHashAlgType;
	BOOL            bAttachSign;
	BOOL            bAddSignerCert;
	TCHAR           *szMIMEMsg;
	DWORD           cbMIMELen;
	BYTE            *pbSignature;
	DWORD            cbSignature;
	BYTE            *pbAuthAttr;
	DWORD            cbAuthAttr;
	BYTE			*pbEncodedCert;
	DWORD			cbEncodedCert;
	PCERT_INFO		pSignerCert;
}VSSC_SIGN_MESSAGE_PARA ,*PVSSC_SIGN_MESSAGE_PARA;

typedef struct DecCert_Info
{
	_bstr_t bstrIssuerDN;
	_bstr_t bstrSubjectDN;
	
	_bstr_t bstrSubjectDN_CN;
	_bstr_t bstrSubjectDN_OU;
	_bstr_t bstrSubjectDN_O;
	_bstr_t bstrSubjectDN_E;

	_bstr_t bstrSerNum;

	DATE dateExpDate;
	DATE dateEffDate;

	short nKeyUsage;
	short nKeySize;

}DECCERT_INFO, *PDECCERT_INFO;

typedef struct _VSSC_CERT_BLOB {
	unsigned int cbData;
	unsigned char *pbData;
}	VSSC_ISSUERDN_BLOB,		*PVS_ISSUERDN_BLOB,
	VSSC_SERIALNUM_BLOB,	*PVS_SERIALNUM_BLOB;

typedef struct _CERT_RESOLVE_INFO{
	int			nVersion;		  /////Version of Cert Resolve Request	
	int			nOperation;		  /////UserCertificate  OR SMIMECertificate	
	int			ReqCrit;		  /////Email or IssuerDN/SerialNumber	
	char		*pszSCType;		  /////SCType	
}CERT_RESOLVE_INFO,*PCERT_RESOLVE_INFO;


typedef struct _CERT_REQ_CRIT_INFO
{
	char				*pszEmailAddr;	/////EmailAddress 
	VSSC_ISSUERDN_BLOB	IssuerDN;		/////Issuer&SerialNumber
	VSSC_SERIALNUM_BLOB SerialNum;		/////of required certificate
}CERT_REQ_CRIT_INFO,*PCERT_REQ_CRIT_INFO;

typedef struct _CERT_REQ_RESPONSE_INFO
{
	DWORD       dwVersion;
	DWORD       dwOperation;
	DWORD       dwReqCrit;
	_bstr_t     bstrSCType;
	_bstr_t     bstrEmailAddr;
	_bstr_t     bstrSeialNum;
	_bstr_t     bstrIssuerDN;
	DWORD       dwStatus;
			
			
}CERT_REQ_RESPONSE_INFO,*PCERT_REQ_RESPONSE_INFO;

typedef struct _CERT_STATUS_INFO
{
	DWORD     dwResolutionTypeBit;
	DWORD     dwRevocationTypeBit;
	DWORD     dwRevocationSubTypeBit;
	DWORD     dwRevocationStatusBit;
	DWORD     dwChainValidateTypeBit;
	DWORD     dwChainValidateStatusBit;

	DWORD     dwRevocationStatus;
	DWORD     dwChainValidationStatus;
	BOOL      bIsExpired;
			
}CERT_STATUS_INFO,*PCERT_STATUS_INFO;


//
//	different message modes
//
#define		VSSC_COMPOSE			0
#define		VSSC_VIEW				1
#define		VSSC_REPLY				2
#define		VSSC_FORWARD			3
#define		VSSC_ATTACH				4
#define		VSSC_ERROR_INFO			5



#define       VS_RESOLUTION_FAILED                      0x0000
#define       VS_ENC_CERT_SIGNED_PKCS7					0x0001
#define       VS_ENC_CERT_X509_CERT						0x0002
#define       VS_ENC_CERT_SIGNED_PKCS7_ICA				0x0003

#define       VS_REVOCATION_TYPE_CRLDP					0x0000
#define       VS_REVOCATION_TYPE_OCSP					0x0001

#define       VS_REVOCATION_SUBTYPE_SERVER              0x0000
#define       VS_REVOCATION_SUBTYPE_CLIENT              0x0001    

#define       VS_REV_STATUS_NOT_REV						0x0000
#define       VS_REV_STATUS_REVOKED						0x0001
#define       VS_REV_STATUS_FAILED						0x0002

#define       VS_CHAIN_VALIDATE_TYPE_SERVER				0x0000
#define       VS_CHAIN_VALIDATE_TYPE_CLIENT				0x0001

#define       VS_CHAIN_VALIDATE_SUCCESS					0x0000
#define       VS_CHAIN_VALIDATE_FAILED					0x0001



#endif