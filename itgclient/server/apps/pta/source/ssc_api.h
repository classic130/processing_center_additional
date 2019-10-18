
/* VeriSign SSC Client Authorization API */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 2000. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*--------------------------------------------------------------------\
| Version:                                                            |
| Current Version: 3                                                  |
| Backward compatibility: Compatible with version 1.0                 |
| Major changes since last version:                                   |
|       1. current version is using CVM SDK                           |
|       2. added  vsPKIParseCert(),vsPKIParseB64Cert() and            | 
|          vsPKIFreeCertFields() for certificate parsing and          |
|          free up memory of CertFields respectively                  |     
|       3. support for HP/UX 11.0                                     |
\--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {  
  /* This allows for C++ inclusion/use of this header file */
#endif
    
#ifndef _SSC_API_H_
#define _SSC_API_H_ 1

#include "extparser.h"

#ifdef WIN32
#ifdef EXPORT  /* User programs should not define EXPORT */
#define Dll    __declspec( dllexport )
#else
#define Dll   __declspec( dllimport )
#endif  /* export */
#else /* not win32 */
#define Dll 
#endif /* not win32 */


#define SSC_CURRENT_VERSION						  3

  /* Backward compatible version */
#define SSC_BACK_COMPATIBLE_VERSION				  1


  /* maxmum size of logging */
#define	CVM_LARGE_BUF_MAX						2048

  /* Certification status codes. */
#define CS_VALID                                  1
#define CS_PENDING                                2
#define CS_EXPIRED                                3
#define CS_CRL_EXPIRED                            4
#define CS_REVOCATION_UNKNOWN                     5
#define CS_REVOKED                                6

  /* These are needed for writing server access control plugins. */
#define CS_SSC_LOGIN                              0
#define CS_SSC_COOKIE_EXPIRED                    31
#define CS_SSC_COOKIE_REVOCATION_EXPIRED         32
#define CS_SSC_COOKIE_UNAUTH                     33
#define CS_SSC_COOKIE_BAD                        34
#define CS_SSC_POST_EXPIRED                      35
#define CS_SSC_POST_BAD                          36
#define CS_SSC_LOGOUT                            37
#define CS_SSC_BAD_ADMIN                         38
#define CS_SSC_POST_REVOKED                      39
#define CS_SSC_PLUGIN_DENIED                     40
#define CS_SSC_COOKIE_REVOKED                    41

  /* Which type of signature algorithm was used to sign a message? */
#define VS_SIG_ALG_MD5 1
#define VS_SIG_ALG_SHA 2
#define VS_SIG_MD5_LEN 16
#define VS_SIG_SHA_LEN 20
#define VS_SIG_MAX_LEN 20

  /* Error Codes */
#define VS_SSC_ERR_BASE 7700
#define VS_SSC_ERR_BAD_VERSION         (VS_SSC_ERR_BASE +  1)
#define VS_SSC_ERR_BAD_PARAM           (VS_SSC_ERR_BASE +  2)
#define VS_SSC_ERR_REVOCATION_WARN     (VS_SSC_ERR_BASE +  3)
#define VS_SSC_ERR_BAD_SIG             (VS_SSC_ERR_BASE +  4)
#define VS_SSC_ERR_BAD_HASH            (VS_SSC_ERR_BASE +  5)
#define VS_SSC_ERR_BAD_INIT            (VS_SSC_ERR_BASE +  6)
#define VS_SSC_ERR_NO_CHAIN            (VS_SSC_ERR_BASE +  7)
#define VS_SSC_ERR_BER_ENCODING        (VS_SSC_ERR_BASE +  8)
#define VS_SSC_ERR_OCSP_SERVER_CONFIG  (VS_SSC_ERR_BASE +  9)
#define VS_SSC_ERR_READ_CONFIG_FILE    (VS_SSC_ERR_BASE + 10)
#define VS_SSC_ERR_ALLOC               (VS_SSC_ERR_BASE + 11)
#define VS_SSC_ERR_MAX                 (VS_SSC_ERR_BASE + 12)

#define VSVERIFY_ERR_BASE 0x80008000
#define VSVERIFY_INVALID_CONFIG				(VSVERIFY_ERR_BASE + 1)
#define VSVERIFY_LIBRARY_ERROR				(VSVERIFY_ERR_BASE + 2)
#define VSVERIFY_INITIALIZE_FAILED			(VSVERIFY_ERR_BASE + 3)
#define VSVERIFY_ERROR_READING_MESSAGE		(VSVERIFY_ERR_BASE + 4)
#define VSVERIFY_ERROR_READING_SIGNATURE	(VSVERIFY_ERR_BASE + 5)
#define VSVERIFY_ERROR_REGISTRY             (VSVERIFY_ERR_BASE + 6)
#define VSVERIFY_ERROR_B64DECODE            (VSVERIFY_ERR_BASE + 7)
#define VSVERIFY_ERR_MAX                    (VSVERIFY_ERR_BASE + 8)
	
typedef struct VS_SSC_CertFields_s {

  char  *emailAddress;
  char  *commonName; 
  char  *title;
  char  *uniqueID; 
  char  *address; 
  char  *organization; 
  char **organizationUnits;
  int    orgUnitCount; 
  char  *issuerOrganization;
  char  *issuerLocality;
  char  *issuerCountry; 
  char  *issuerCommonName;
  char **issuerOrganizationUnits;
  int    issuerOrgUnitCount; 
  char  *notBefore;
  char  *notAfter;
  VSCertV3Extensions_MV v3Extensions;
  
} VS_SSC_CertFields;

  /* All functions return 0 for succes, or else VS_SSC_ERR_ */

  /* Must call this function first. Initializes the api and reads Certs/CRLs. */
  /*
    version: must be 1 or greater
    cfgFileName: name of configuration file containing Cert/CRL locations.
    cacheDir: Place on disk to store Certs/CRLs. Could use a system temp dir.
    filePrefix/urlPrefix: used in config file. Can be "" (cannot be 0).
    checkChain: 0 only checks lowest CRL in hierarchy, otherwise check all.
    httpProxy: Specify an http proxy, for example, "proxy:80". Can be 0.
    ocspUrl: use ocsp instead of CRL checking. Specify as http://server:port/url

    logFn: Pointer to a logging function. Normally this should be 0.
    Some api routines will call out to this fn with helpful information for debugging.

    ldapDefault: ldap server to query if cert/CRL is unavailable.
                 Disable with "". 0 uses VeriSign default.
    ldapHttpProxy/ldapHttpCgi: used for doing ldap over http. Leave 0 or see docs.
  */
  Dll int vsPKIInit(int version, char *cfgFileName,
                    char *cacheDir, char *filePrefix, char *urlPrefix,
                    int checkChain, char *httpProxy, char *ocspUrl, 
                    void (*logFn)(char *fmt, ...), char *ldapDefault,
                    char *ldapHttpProxy, char *ldapHttpCgi);

  /* Call this function at the end to free memory, cleanup, etc.. */
  Dll int vsPKIFinal();

  /* See if a given cert is revoked. */
  /* Pass in cert/certLen with a DER encoded cert buffer.
     Output will be the certStatus (CS_VALID, CS_REVOKED, etc...)
     
     If userName is not null, it will be set to point to a static buffer which
     contains the cert subject name. This userName should not be freed and will
     be overwritten by subsequent calls to this function.

     Will return VS_SSC_ERR_REVOCATION if any error occurrs.  In some cases, 
     *certStatus will still be set appropriately.  If *certStatus is non-zero,
     a proper revocation check has been performed and this error can be ignored.

  */
  Dll int vsPKIGetRevocationStatus(unsigned char *cert, int certLen,
                                   int *certStatus, char **userName);

  /* Pass in pkcs7/pkcs7Len which is a buffer containing the DER of a
     PKCS7 detached signature. 
        
     The return code will be 0 for success, or else an error code.

     Upon success:
     hash will have 16 or 20 bytes of message digest written into it. (hash must
     already be allocated with at least 20 bytes of space).
     hashLen receives the number of bytes written into hash.

     outAlgorithm will be VS_SIG_ALG_MD5 or VS_SIG_ALG_SHA.

     cert/certLen will get the pkcs7's signer's certificate if they are nonzero.
     This memory must be freed later with vsPKIFree().

     if certStatus!=0, it will receive the revocation status. 
  */
  Dll int vsPKIParsePKCS7(unsigned char *pkcs7, int pkcs7Len, 
                          unsigned char *hash, int *hashLen, int *outAlgorithm,
                          unsigned char **cert, int *certLen, int *certStatus);

  /* Hash a message and compare it to another. */
  /* Returns 0 if the given hash/hashLen matches the hash of msg/msgLen. */
  Dll int vsPKICompareMsgHash(unsigned char *msg, int msgLen, 
                              int outAlgorithm, unsigned char *hash, int hashLen);


  /* Similar to vsPKIParsePKCS7(), but also takes a message. If the msg/msgLen matches
   that of the pkcs7, 0 is returned.  Otherwise a bad signature error is returned. */
  Dll int vsPKIVerifyPKCS7(unsigned char *pkcs7, int pkcs7Len, 
                           unsigned char *msg, int msgLen, 
                           unsigned char *hash, int *hashLen, int *outAlgorithm, 
                           unsigned char **cert, int *certLen, int *certStatus);



  /* This two functions will do Base64 encoding and decoding. */
  /* They will NOT handle "---BEGIN CERT---" style headers and footers when decoding. */

  /* Will allocate a null-terminated *b64String from the given binary data/len. */
  /* It should be freed when done with it. */
  Dll int vsPKIBase64Alloc(char **b64String, unsigned char *data, int len);

  /* Will allocate len bytes of binary data from the given null-terminated b64 string. */
  /* Must free data when done with it. */
  Dll int vsPKIUnBase64Alloc(unsigned char **data, int *len, char *b64String);

  /* parse a certificate to readable fields */
  /* The function will allocated  a pointer to a new VS_SSC_CertFields that contains all*/
  /* readable cert fields. call vsPKIFreeCertFields to free the pointer when you are done with it*/
  /* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */
  
  Dll int vsPKIParseCert(VS_SSC_CertFields **certFields, unsigned char *cert, int certLen);

  /* parse a Base64 encoded certificate to readable fields */
  /* The function will allocated  a pointer to a new VS_SSC_CertFields that contains all*/
  /* readable cert fields. call vsPKIFreeCertFields to free the pointer when you are done with it*/
  /* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */
  Dll int vsPKIParseB64Cert(VS_SSC_CertFields **certFields,  char *b64cert);

  /* Free up memory for certfields. This function must be called to free up the memory of free cert*/
  /* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */
  Dll void vsPKIFreeCertFields(VS_SSC_CertFields *certFields);

  /* Use this to free data allocated by these functions. */
  Dll void vsPKIFree(void *p);

#ifdef __cplusplus
           }
#endif
/* end of C wrapper for C++ */

#endif /*  _SSC_API_H_ */
