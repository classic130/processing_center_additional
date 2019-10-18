#ifndef VSSC_PKCS7ENGINE_H
#define VSSC_PKCS7ENGINE_H

#include "sgmsCommon.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#include "simder_all.h"


#define vssc_szOID_OIWSEC_sha1       "1.3.14.3.2.26"
#define vssc_szOID_RSA_MD2           "1.2.840.113549.2.2"
#define vssc_szOID_RSA_MD5           "1.2.840.113549.2.5"
#define vssc_szOID_RSA_data          "1.2.840.113549.1.7.1"
#define vssc_szOID_RSA_signedData    "1.2.840.113549.1.7.2"
#define vssc_szOID_RSA_envelopedData "1.2.840.113549.1.7.3"
#define vssc_szOID_RSA_digestedData  "1.2.840.113549.1.7.5"

#define vssc_szOID_RSA_DES_EDE3_CBC  "1.2.840.113549.3.7"
#define vssc_szOID_RSA_RC2CBC        "1.2.840.113549.3.2"

#define vssc_szOID_OIWSEC_desCBC     "1.3.14.3.2.7"
#define vssc_szOID_RSA_SHA1RSA       "1.2.840.113549.1.1.5"
#define vssc_szOID_RSA_MD5RSA        "1.2.840.113549.1.1.4"

#define vssc_szOID_RSA_RSA           "1.2.840.113549.1.1.1"
#define VSSC_CERT_RSA_PUBLIC_KEY_OBJID            szOID_RSA_RSA

#define vssc_szOID_RSA_SMIMECapabilities "1.2.840.113549.1.9.15"

#define		VSSC_HASH_SHA1	1
#define		VSSC_HASH_MD2	2
#define		VSSC_HASH_MD5	3

typedef enum _VS_PKCS7_TYPE { PKCS7_SIGNED, PKCS7_ENVELOPED } VS_PKCS7_TYPE ;

typedef struct _VS_PKCS7_BLOB {
	unsigned int cbData;
	unsigned char *pbData;
}	VS_ISSUER_BLOB,		*PVS_ISSUER_BLOB,
	VS_SERIALNO_BLOB,		*PVS_SERIALNO_BLOB,
	VS_CERT_BLOB,			*PVS_CERT_BLOB,
	VS_SIGNATURE_BLOB,		*PVS_SIGNATURE_BLOB,
	VS_DATA_BLOB,			*PVS_DATA_BLOB,
	VS_ENCRYPTED_BLOB,		*PVS_ENCRYPTED_BLOB,
	VS_ENCRYPTEDKEY_BLOB,	*PVS_ENCRYPTEDKEY_BLOB,
	VS_OBJID_BLOB,			*PVS_OBJID_BLOB,
	VS_DIGEST_BLOB,			*PVS_DIGEST_BLOB,
	VS_SIGNEDATTRIBS_BLOB,	*PVS_SIGNEDATTRIBS_BLOB,
	ENCAP_CONTENT_INFO,		*PENCAP_CONTENT_INFO,
	VS_CRL_BLOB,			*PVS_CRL_BLOB;


typedef struct _VS_ALGORITHM_IDENTIFIER {
  char              *pszObjId;
  VS_OBJID_BLOB		Parameters;
} VS_ALGORITHM_IDENTIFIER,     *PVS_ALGORITHM_IDENTIFIER;



typedef struct _VS_SIGNER_INFO{
	VS_ISSUER_BLOB			Issuer;
	VS_SERIALNO_BLOB		SerialNumber;
	VS_CERT_BLOB			CertEncoded; // should be completed chain not just the end user cert - check.
	VS_ALGORITHM_IDENTIFIER	EncObjId;
} VS_SIGNER_INFO, *PVS_SIGNER_INFO;


typedef struct _VS_ENCRYPTED_CONTENT_INFO
{
	VS_ALGORITHM_IDENTIFIER		ContentEncryptionAlgID;
	VS_ENCRYPTED_BLOB			EncryptedContent;
} VS_ENCRYPTED_CONTENT_INFO, *PVS_ENCRYPTED_CONTENT_INFO;

typedef struct _VS_RECIPIENT_INFO
{
	VS_ISSUER_BLOB				Issuer;
	VS_SERIALNO_BLOB			SerialNumber;
	VS_ALGORITHM_IDENTIFIER		KeyEncryptionAlgID;
	VS_ENCRYPTEDKEY_BLOB		EncryptedKey;
} VS_RECIPIENT_INFO, *PVS_RECIPIENT_INFO;

/*
typedef struct _AUTHATTRIB {
	unsigned int	cbCertIssuerDN;
	unsigned char	*pbCertIssuerDN ;
	unsigned int	cbCertSerialNum;
	unsigned char	*pbCertSerialNum ; 
	char			*szDigestAlgoID ; 
	char			*szSMIMECapabilities ;
	unsigned int	cbMimeEntityDigest;
	unsigned char	*pbMimeEntityDigest ;
	unsigned int	cbAuthAttrib ; 
	unsigned char	*pbAuthAttrib ;
} AUTHATTRIB ;
*/

typedef struct _AUTHATTRIB {
	unsigned int				cbCertIssuerDN;
	unsigned char				*pbCertIssuerDN ;
	unsigned int				cbCertSerialNum;
	unsigned char				*pbCertSerialNum ; 
	char						*szDigestAlgoID ; 
	VS_ALGORITHM_IDENTIFIER		*SMIMECapabilities ;
	int							nCaps;
	unsigned int				cbMimeEntityDigest;
	unsigned char				*pbMimeEntityDigest ;
	unsigned int				cbAuthAttrib ; 
	unsigned char				*pbAuthAttrib ;
}AUTHATTRIB ;



typedef struct _VS_SIGNER_INFO_PARSE
{
	unsigned int					dwSIVersion;
	VS_ISSUER_BLOB					Issuer;
	VS_SERIALNO_BLOB				SerialNumber;
	VS_ALGORITHM_IDENTIFIER			DigestAlgId;
	VS_SIGNEDATTRIBS_BLOB			SignedAttributes;
	VS_ALGORITHM_IDENTIFIER			SignatureAlgId;
	VS_SIGNATURE_BLOB				SignatureValue;
}VS_SIGNER_INFO_PARSE;

typedef struct _VS_SIGNEDDATA_INFO
{
	unsigned int					dwSDVersion;
	VS_ALGORITHM_IDENTIFIER			DigestAlgId; // BUGBUG This should be more than one but assuming only one in our case 
	ENCAP_CONTENT_INFO				EncapContentInfo;
	VS_CERT_BLOB					CertificateSet; // This is nothing but the DER blob of the cert set. It can have one cert or a chain.
	VS_CRL_BLOB						CrlSet; // Same as Cert
	VS_SIGNER_INFO_PARSE			SignerInfo;  // Here we assume only one SignerInfo.

} VS_SIGNEDDATA_INFO;

typedef struct _VS_ENVELOPEDDATA_INFO
{
	unsigned int				dwVersion;
	VS_RECIPIENT_INFO			*pRecipientInfo;
	int							nRecipientInfos;
	VS_ENCRYPTED_CONTENT_INFO	EncryptedContent;
} VS_ENVELOPEDDATA_INFO;

typedef struct _VS_PKCS7_INFO
{
	VS_PKCS7_TYPE			ePKCS7Type;
	VS_SIGNEDDATA_INFO		SignedDataInfo;
	VS_ENVELOPEDDATA_INFO	EncryptedDataInfo;
} VS_PKCS7_INFO;





////////////// PKCS7 construction functions ////////////

// Might want return error codes; 
// The callee checks to see if the return value = 0, which is a success, 
// if not it is a failure - and the error code returned can be used for debugging

int CreateSignedData(PVS_SIGNATURE_BLOB pSignatureBlob,
					 int i_nHashAlg,
					 PVS_SIGNER_INFO pSignerInfo, 
					 bool bDetached, // TRUE if Detached 
					 unsigned char *pbData, // only for attached, NULL if Detached.
					 unsigned int cbData,   // only for attached, 0 if Detached.
					 unsigned char *pbAuthAttribCollection, // authenticated attributes
					 unsigned int cbAuthAttribCollection,  // length of auth attributes
					 char **pszSignedData64);


int CreateEnvelopedData(PVS_ENCRYPTED_CONTENT_INFO pEncryptedContet,
						PVS_RECIPIENT_INFO pRecipientInfo[],
						int nRecipientInfo,
						char **ppszEnvelopedData64);

void FormatUTCTime(char *szUTCTime);

int CreateAuthAttrib (AUTHATTRIB *aaAuthAttrib);



////////////////PKCS7 parser functions/////////

/*
int ParseSignedData(unsigned char* pbSignedDataDerBlob,
					 unsigned int cbSignedDataBlobLen,
					 VS_SIGNEDDATA_INFO *vssdiSignedDataInfo );

int ParseSignerInfo(unsigned char* pbSignerDataDerBlob,
					 unsigned int cbSignerDataBlobLen,
					 VS_SIGNER_INFO_PARSE *vssipSignerInfo );

int ParseEnvelopedData(unsigned char *pbEnvelopedData, 
						unsigned int cbEnvelopedData,
						VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo
						);
*/
int ParseEnvelopedData(DERTree *dtPKCS7,
						  VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo);

int ParseSignedData(DERTree *dtPKCS7,
					   VS_SIGNEDDATA_INFO *vssdiSignedDataInfo);

int ParseSignerInfo(DERTree *dtPKCS7,
					  VS_SIGNER_INFO_PARSE *vssipSignerInfo );

/*
int GetMsgDigestFromAA(unsigned char* pbAuthAttrib, 
						unsigned int cbAuthAttrib,
						unsigned char** ppbMsgDigest,
						unsigned int *cbMsgDigest);
*/

int GetMsgDigestSIDFromAA(unsigned char* pbAuthAttrib, 
						unsigned int cbAuthAttrib,
						AUTHATTRIB *pAuthAtrib);

int ParsePKCS7Data(
				  unsigned char *pbPKCS7Data,
				  unsigned int cbPKCS7Data,
				  VS_PKCS7_INFO *vsspiPKCS7Info
				   );


int ParsePKCS7DataUsingCAPI(
				  unsigned char *pbPKCS7Data,
				  unsigned int cbPKCS7Data,
				  VS_PKCS7_INFO *vsspiPKCS7Info
				   );

int GetPKCS7Type(
				 unsigned char *pbPKCS7Data,
				 unsigned int cbPKCS7Data,
				 VS_PKCS7_TYPE *ePKCS7Type
				 );

// Given a chain or a end entity cert the input, returns the required 
// certificate in the chain which is controlled by nDepth input parameter,
// To get an end entity cert nDepth should be equal to 0
// If the length of the chain is 1, and nDept = 0, it returns the same cert.

// It is important to locate the end entity cert as the nDepth is relative to 
// the EndEntity cert.
// What determines an endentity cert - 1.Basic Constraints should be 0
//									   2.Should not be self signed
//									   3.in a loop,  if current.Subject != next.Issuer

int CertChainParser(	unsigned char* pbCertData,
						unsigned long cbCertData,
						unsigned char** ppbCertOut,
						unsigned long* pcbCertout,
						int	nDepth
					);

// Returns no. of certs in the Cert Chain. 
// Returns 1 if the chain contains only one cert.
// Returns -1 if there is an error.
int GetCertChainLen(	unsigned char* pbCertData,
						unsigned long cbCertData
					);

// Returns true is the last cert in the chain is the End Entity Cert
// Returns false if the first cert in the chain is the End Entity Cert.
bool IsEndEntityCertLast(
						 unsigned char *pbCertChain, 
						 unsigned long cbCertChain
						 );


////////////Free Functions///////////////////
//////
void FreePKCS7Info(VS_PKCS7_INFO *vsspiPKCS7Info);

void FreeEnvelopedInfo(VS_ENVELOPEDDATA_INFO *vseiEnvelopedDataInfo);
void FreeRecipientInfo(VS_RECIPIENT_INFO	*pRecipientInfo, int nRecipientCount);

void FreeSignedDataInfo(VS_SIGNEDDATA_INFO *vssdiSignedDataInfo);
void FreeSignerInfo(VS_SIGNER_INFO_PARSE *vssipSignerInfo);




/////////////Utility functions//////////////
// Moved to sgmscommon.h
/*
void _Base64Encode(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);



void reverse(unsigned int size,
			 unsigned char *input);
*/



///////////////Macros///////////////

#define		CHECKNULLANDSIZE(SimderClass)	\
			if(SimderClass.BaseDERBlob->pbData == NULL || SimderClass.BaseDERBlob->cbData == 0) \
			{ return -1 ; } \
			else {}



#endif // VSSC_PKCS7ENGINE_H