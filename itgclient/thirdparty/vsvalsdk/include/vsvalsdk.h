
/* VeriSign Validation SDK */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 2000. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/


#ifndef _VSVAL_SDK_H_
#define _VSVAL_SDK_H_ 1
#define _VSVAL_VAL_SDK_H_ 1

#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif
    
#ifdef WIN32
#ifdef EXPORT  /* User programs should NOT define EXPORT */
#define Dll    __declspec( dllexport )
#else
#define Dll   __declspec( dllimport )
#endif  /* export */
#else /* not win32 */
#define Dll 
#endif /* not win32 */
#include "extparser.h"

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
#define VSVAL_HASH_ALG_MD5   1
#define VSVAL_HASH_ALG_SHA1  2
#define VSVAL_HASH_MD5_LEN  16
#define VSVAL_HASH_SHA1_LEN 20
#define VSVAL_HASH_MAX_LEN  20


  /* Error Codes */
#define VSVAL_ERR_BASE 7700
#define VSVAL_ERR_BAD_VERSION                  (VSVAL_ERR_BASE +   1)
#define VSVAL_ERR_BAD_PARAM                    (VSVAL_ERR_BASE +   2)
#define VSVAL_ERR_ALLOC                        (VSVAL_ERR_BASE +   3)
#define VSVAL_ERR_NULL_HANDLE                  (VSVAL_ERR_BASE +   4)
#define VSVAL_ERR_OPTION_UNKNOWN               (VSVAL_ERR_BASE +   5)
#define VSVAL_ERR_DEFAULT_OPTION               (VSVAL_ERR_BASE +   6)
#define VSVAL_ERR_CONFIG_OPTION                (VSVAL_ERR_BASE +   7)
#define VSVAL_ERR_SERVER_NAME                  (VSVAL_ERR_BASE +   8)
#define VSVAL_ERR_MISSING_CONFIG_VAL           (VSVAL_ERR_BASE +   9)
#define VSVAL_ERR_BER_ENCODING                 (VSVAL_ERR_BASE +  10)
#define VSVAL_ERR_BAD_B64                      (VSVAL_ERR_BASE +  11)
#define VSVAL_ERR_BAD_SIG                      (VSVAL_ERR_BASE +  12)
#define VSVAL_ERR_BAD_HASH                     (VSVAL_ERR_BASE +  13)
#define VSVAL_ERR_UNAVAILABLE_ON_PLATFORM      (VSVAL_ERR_BASE +  14)
#define VSVAL_ERR_COOKIE_DOMAIN                (VSVAL_ERR_BASE +  15)
#define VSVAL_ERR_LOGIN_PAGE                   (VSVAL_ERR_BASE +  16)
#define VSVAL_ERR_NO_URI                       (VSVAL_ERR_BASE +  17)
#define VSVAL_ERR_ADMIN_UNSUPPORTED            (VSVAL_ERR_BASE +  18)
#define VSVAL_ERR_SHLIB                        (VSVAL_ERR_BASE +  19)
#define VSVAL_ERR_VAL_INIT                     (VSVAL_ERR_BASE +  20)
#define VSVAL_ERR_ADMIN_HASC                   (VSVAL_ERR_BASE +  21)
#define VSVAL_ERR_NO_SAVE_CERTS                (VSVAL_ERR_BASE +  22)
#define VSVAL_ERR_OPTION_FILE                  (VSVAL_ERR_BASE +  23)
#define VSVAL_ERR_RANDOM                       (VSVAL_ERR_BASE +  24)
#define VSVAL_ERR_RANDOM_CLOCK                 (VSVAL_ERR_BASE +  25)
#define VSVAL_ERR_RANDOM_FILE                  (VSVAL_ERR_BASE +  26)
#define VSVAL_ERR_FILE_OPEN_SSC                (VSVAL_ERR_BASE +  27)
#define VSVAL_ERR_FILE_READ_SSC                (VSVAL_ERR_BASE +  28)
#define VSVAL_ERR_LOG_FILE                     (VSVAL_ERR_BASE +  29)
#define VSVAL_ERR_NO_ROOT                      (VSVAL_ERR_BASE +  30)
#define VSVAL_ERR_USER_PLUGIN_INIT             (VSVAL_ERR_BASE +  31)

  /* error spawning thread */
#define VSVAL_ERR_THREAD                       (VSVAL_ERR_BASE +  32)

  /* http error, ie, --404 Not Found */
#define VSVAL_ERR_HTTP_HEADER                  (VSVAL_ERR_BASE +  33)

  /* http error connecting to socket */
#define VSVAL_ERR_HTTP_CONNECT                 (VSVAL_ERR_BASE +  34)

  /* http error making socket call */
#define VSVAL_ERR_HTTP_SOCKET                  (VSVAL_ERR_BASE +  35)

  /* error copying file */
#define VSVAL_ERR_COPY_FILE_SRC                (VSVAL_ERR_BASE +  36)

  /* error copying file */
#define VSVAL_ERR_COPY_FILE_DST                (VSVAL_ERR_BASE +  37)

  /* table problem (duplicate entry, etc...) */
#define VSVAL_ERR_BAD_TABLE                    (VSVAL_ERR_BASE +  38)

  /* can't get http url */
#define VSVAL_ERR_GET_HTTP                     (VSVAL_ERR_BASE +  39)

  /* can't get ldap url */
#define VSVAL_ERR_GET_LDAP                     (VSVAL_ERR_BASE +  40)

  /* unsupported url type */
#define VSVAL_ERR_GET_UNSUPPORTED              (VSVAL_ERR_BASE +  41)

  /* can't open config file */
#define VSVAL_ERR_CONFIG_OPEN                  (VSVAL_ERR_BASE +  42)

  /* found a root cert in a config file with no-config-roots set. */
#define VSVAL_ERR_ROOT_IN_CONFIG_FILE          (VSVAL_ERR_BASE +  43)
#define VSVAL_ERR_READ_CONFIG_FILE             (VSVAL_ERR_BASE +  44)

  /* can't open server root cert file */
#define VSVAL_ERR_SERVER_FILE_OPEN             (VSVAL_ERR_BASE +  45)

  /* a file expected to be open wasn't */
#define VSVAL_ERR_FILE_NOT_OPEN                (VSVAL_ERR_BASE +  46)

  /* file in wrong format */
#define VSVAL_ERR_NOT_DER                      (VSVAL_ERR_BASE +  47)

  /* problem reading file (empty) */
#define VSVAL_ERR_FILE_READ                    (VSVAL_ERR_BASE +  48)

  /* can't find a table entry */
#define VSVAL_ERR_NO_TABLE_ENTRY               (VSVAL_ERR_BASE +  49)

  /* Error in Netscape obj.conf file */
#define VSVAL_ERR_OBJ_CONF                     (VSVAL_ERR_BASE +  50)

  /* not a pkcs7 file */
#define VSVAL_ERR_NOT_PKCS7                    (VSVAL_ERR_BASE +  51)

  /* can't read root cert */
#define VSVAL_ERR_BAD_ROOT                     (VSVAL_ERR_BASE +  52)

  /* pkcs7 cert unsupported */
#define VSVAL_ERR_PKCS7_CERT                   (VSVAL_ERR_BASE +  53)

  /* cert encoding unsupported */
#define VSVAL_ERR_BAD_CERT_TYPE                (VSVAL_ERR_BASE +  54)

  /* crl encoding unsupported */
#define VSVAL_ERR_BAD_CRL_TYPE                 (VSVAL_ERR_BASE +  55)

  /* can't open tmp file */
#define VSVAL_ERR_TMP_FILE                     (VSVAL_ERR_BASE +  56)

  /* can't open file */
#define VSVAL_ERR_FILE_OPEN                    (VSVAL_ERR_BASE +  57)

  /* couldn't get an auth-cert string */
#define VSVAL_ERR_NO_AUTH_CERT                 (VSVAL_ERR_BASE +  58)

  /* error reading cert/crl.likely DER encoding*/
#define VSVAL_ERR_READ_ITEM                   (VSVAL_ERR_BASE +  59)

  /* couldn't get a cert or crl to refresh. */
#define VSVAL_ERR_NO_REFRESH                   (VSVAL_ERR_BASE +  60)

  /* user didn't allow us to use ldap default.*/
#define VSVAL_ERR_NO_LDAP_DEFAULT              (VSVAL_ERR_BASE +  61)

  /* config problem reading registry. */
#define VSVAL_ERR_REGISTRY                     (VSVAL_ERR_BASE +  62)

  /* ROOT can't be a URL. */
#define VSVAL_ERR_ROOT_URL                     (VSVAL_ERR_BASE +  63)

#define VSVAL_ERR_OCSP_SERVER_CONFIG           (VSVAL_ERR_BASE +  64)

  /* error adding ocsp issuer */
#define VSVAL_ERR_OCSP_ISSUER                  (VSVAL_ERR_BASE +  65)

  /* can't connect to ocsp server */
#define VSVAL_ERR_OCSP_CONNECT                 (VSVAL_ERR_BASE +  66)

#define VSVAL_ERR_B64_BUFFER	               (VSVAL_ERR_BASE +  67)
#define VSVAL_ERR_B64_INVALID_CHAR	           (VSVAL_ERR_BASE +  68)
#define VSVAL_ERR_NO_BUFFER_SPACE	           (VSVAL_ERR_BASE +  69)
#define VSVAL_ERR_MUTEX_CREATE                 (VSVAL_ERR_BASE +  70)
#define VSVAL_ERR_MUTEX_LOCK                   (VSVAL_ERR_BASE +  71)
#define VSVAL_ERR_MUTEX_UNLOCK                 (VSVAL_ERR_BASE +  72)
#define VSVAL_ERR_MUTEX_TRYLOCK                (VSVAL_ERR_BASE +  73)
#define VSVAL_ERR_MUTEX_DESTROY                (VSVAL_ERR_BASE +  74)


#define VSVAL_ERR_CRYPT_PROVIDER               (VSVAL_ERR_BASE +  75)
#define VSVAL_ERR_CRYPT_SYSTEM_STORE           (VSVAL_ERR_BASE +  76)
#define VSVAL_ERR_TIMESTAMP_SERVER_CONFIG      (VSVAL_ERR_BASE +  77)
#define VSVAL_ERR_NOT_FOUND                    (VSVAL_ERR_BASE +  78)
#define VSVAL_ERR_EXCEPTION                    (VSVAL_ERR_BASE +  79)
#define VSVAL_ERR_CERT_STORE_OPEN              (VSVAL_ERR_BASE +  80)
#define VSVAL_ERR_TS_RESPONSE                  (VSVAL_ERR_BASE +  81)
#define VSVAL_ERR_NOT_SELF_SIGNED              (VSVAL_ERR_BASE +  82)


#define VSVAL_ERR_OCSP_ENCODE_ASN_ERROR                          (VSVAL_ERR_BASE +  83)
#define VSVAL_ERR_OCSP_DECODE_ASN_ERROR                          (VSVAL_ERR_BASE +  84)
#define VSVAL_ERR_OCSP_RESPONSE_SUCCESSFUL                       (VSVAL_ERR_BASE +  85)
#define VSVAL_ERR_OCSP_MALFORMED_REQUEST                         (VSVAL_ERR_BASE +  86)
#define VSVAL_ERR_OCSP_INTERNAL_ERROR                            (VSVAL_ERR_BASE +  87)
#define VSVAL_ERR_OCSP_TRY_LATER                                 (VSVAL_ERR_BASE +  88)
#define VSVAL_ERR_OCSP_REQUEST_SIGNATURE_REQUIRED                (VSVAL_ERR_BASE +  89)
#define VSVAL_ERR_OCSP_UNAUTHORIZED                              (VSVAL_ERR_BASE +  90)
#define VSVAL_ERR_OCSP_QM_ERROR                                  (VSVAL_ERR_BASE +  91)
#define VSVAL_ERR_OCSP_REQUESTOR_CERT_MISSING                    (VSVAL_ERR_BASE +  92)
#define VSVAL_ERR_OCSP_REQUEST_SIGNATURE_ALG_NOT_SUPPORTED       (VSVAL_ERR_BASE +  93)
#define VSVAL_ERR_OCSP_REQUEST_MISSING_CLIENT_CERT               (VSVAL_ERR_BASE +  94)
#define VSVAL_ERR_OCSP_REQUEST_INVALID_CLIENT_CERT               (VSVAL_ERR_BASE +  95)
#define VSVAL_ERR_OCSP_RESPONSE_HAS_NO_SIGNATURE                 (VSVAL_ERR_BASE +  96)
#define VSVAL_ERR_OCSP_RESPONSE_HAS_INVALID_SIGNATURE            (VSVAL_ERR_BASE +  97)
#define VSVAL_ERR_OCSP_RESPONSE_SIGNER_CERT_NOT_ATTACHED         (VSVAL_ERR_BASE +  98)
#define VSVAL_ERR_OCSP_RESPONSE_CERT_ID_NOT_MATCH                (VSVAL_ERR_BASE +  99)
#define VSVAL_ERR_OCSP_RESPONSE_INVALID_CERT_STATUS              (VSVAL_ERR_BASE + 100)
#define VSVAL_ERR_OCSP_ISSUER_UNKNOWN                            (VSVAL_ERR_BASE + 101)
#define VSVAL_ERR_OCSP_HASH_ALG_NOT_SUPPORTED                    (VSVAL_ERR_BASE + 102)
#define VSVAL_ERR_OCSP_REQUEST_HAS_NO_SIGNATURE                  (VSVAL_ERR_BASE + 103)
#define VSVAL_ERR_OCSP_REQUEST_HAS_INVALID_SIGNATURE             (VSVAL_ERR_BASE + 104)
        
        
#define VSVAL_ERR_TIMESTAMP_MISSING_PASSWD                       (VSVAL_ERR_BASE + 105)
#define VSVAL_ERR_TIMESTAMP_BADFORMED_RESPONSE                   (VSVAL_ERR_BASE + 106)
#define VSVAL_ERR_TIMESTAMP_RESPONSE_STATUS_NOT_SUCCESSFUL       (VSVAL_ERR_BASE + 107)
#define VSVAL_ERR_TIMESTAMP_RESPONSE_SIGNATURE_INVALID           (VSVAL_ERR_BASE + 108)
#define VSVAL_ERR_TIMESTAMP_MESSAGEIMPRINT_MISSING_IN_RESPONSE   (VSVAL_ERR_BASE + 109)
#define VSVAL_ERR_TIMESTAMP_HASHALG_MISMATCH_IN_RESPONSE         (VSVAL_ERR_BASE + 110)
#define VSVAL_ERR_TIMESTAMP_MESSAGEIMPRINT_MISMATCH_IN_RESPONSE  (VSVAL_ERR_BASE + 111)
#define VSVAL_ERR_TIMESTAMP_NONCE_MISSING_IN_RESPONSE            (VSVAL_ERR_BASE + 112)
#define VSVAL_ERR_TIMESTAMP_NONCE_MISMATCH_IN_RESPONSE           (VSVAL_ERR_BASE + 113)
#define VSVAL_ERR_TIMESTAMP_NO_CERTS_IN_RESPONSE                 (VSVAL_ERR_BASE + 114)

#define VSVAL_ERR_BAD_PASSWORD                                   (VSVAL_ERR_BASE + 115)
#define VSVAL_ERR_NO_CERT_STORE                                  (VSVAL_ERR_BASE + 116)
#define VSVAL_ERR_BAD_CERT_STORE                                 (VSVAL_ERR_BASE + 117)
#define VSVAL_ERR_ITEM_EXISTS_IN_STORE                           (VSVAL_ERR_BASE + 118)
#define VSVAL_ERR_IMPORT_PK12                                    (VSVAL_ERR_BASE + 119)
#define VSVAL_ERR_EXPORT_PK12                                    (VSVAL_ERR_BASE + 120)
#define VSVAL_ERR_FILE_OPEN_SA                                   (VSVAL_ERR_BASE + 121)
#define VSVAL_ERR_FILE_NOT_FOUND_SA                              (VSVAL_ERR_BASE + 122)
#define VSVAL_ERR_TIMESTAMP_ENCODE_ASN_ERROR                     (VSVAL_ERR_BASE + 123)
#define VSVAL_ERR_TIMESTAMP_DECODE_ASN_ERROR                     (VSVAL_ERR_BASE + 124)
#define VSVAL_ERR_TIMEOUT                                        (VSVAL_ERR_BASE + 125)
#define VSVAL_ERR_SIGNER_NOT_FOUND                               (VSVAL_ERR_BASE + 126)
#define VSVAL_ERR_SIGNER_CHAIN_NOT_FOUND                         (VSVAL_ERR_BASE + 127)
#define VSVAL_ERR_IMPORT_PK12_NAME                               (VSVAL_ERR_BASE + 128)
#define VSVAL_ERR_OCSP_RESPONSE_SIGNER_CERT_STATUS               (VSVAL_ERR_BASE + 129)
#define VSVAL_ERR_TIMESTAMP_RESPONSE_SIGNER_CERT_STATUS          (VSVAL_ERR_BASE + 130)
#define VSVAL_ERR_OCSP_RESPONDER_EKU                             (VSVAL_ERR_BASE + 131)
#define VSVAL_ERR_OCSP_NONCE_MISSING_IN_RESPONSE                 (VSVAL_ERR_BASE + 132)
#define VSVAL_ERR_OCSP_NONCE_MISMATCH_IN_RESPONSE                (VSVAL_ERR_BASE + 133)
#define VSVAL_ERR_TIMESTAMP_RESPONDER_EKU                        (VSVAL_ERR_BASE + 134)
#define VSVAL_ERR_TIMESTAMP_QUERY                                (VSVAL_ERR_BASE + 135)

#define VSVAL_ERR_MAX                                            (VSVAL_ERR_BASE + 136)


typedef void *VSVAL_SDK;
  
#define VAL_SDK_VERSION_1_0_1 101
#define VAL_SDK_VERSION_1_2_0 120
#define VAL_SDK_VERSION_1_2_1 121
#define VAL_SDK_VERSION_1_3_0 130
#define VAL_SDK_CURRENT_VERSION VAL_SDK_VERSION_1_3_0

typedef struct VSVAL_CertFields_s {

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
  
} VSVAL_CertFields;


typedef void (*VSVAL_InfoLogFn) (void *handle, char *fmt, ...);

#define VSVAL_BUF_MAX  1024

typedef struct VSVAL_UserCtx_s {

  void *handle; /* will be passed as an extra parameter when logFn is called. */
  void *reserved; /* do not use. */

  /* Leave logFn 0, or set it to a function pointer of type VSVAL_InfoLogFn. */
  /* Some api routines will call out to this fn with helpful debugging information. */
  VSVAL_InfoLogFn logFn;

  /* Will get extra error information if it's available. */
  char errorInfo[VSVAL_BUF_MAX];
} VSVAL_UserCtx;
  




/*** VSVAL_Init
 ***
 *** DESCRIPTION
 ***   This function initializes the SDK.  It must be called before using
 ***   any other API functions.  This function will allocate and return
 ***   a new handle.  You must pass this handle to any SDK functions you call.
 ***   The handle is an opaque data structure and does not contain any
 ***   user-visible fields.  The VSVAL_Final function will be used to
 ***   destroy this handle.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK **vs - OUT - returns pointer to new SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   int version - IN - SDK version number. Must be VAL_SDK_VERSION_1_3_0.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_Init(VSVAL_SDK **vs, VSVAL_UserCtx *userCtx, int version);



/*** VSVAL_Final
 ***
 *** DESCRIPTION
 ***   This function cleanly destroys an SDK handle.
 ***   It will free any memory allocated by the toolkit.
 ***   It should be called when you are done using SDK routines.
 ***   Do not use the handle again after calling this function.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_Final(VSVAL_SDK *vs);



/*** 
 ***   These functions are used to set configuration options.
 ***   Some useful options are: cfg-file-name, cache-dir, 
 ***   file-prefix/url-prefix, no-check-chain, http-proxy, ldap-default, ocsp-url.
 ***
 ***/


/*** VSVAL_SetOpt
 ***
 *** DESCRIPTION
 ***   This function sets a configuration option.
 ***   This information will be recorded in the SDK handle.
 ***   Using 0 (NULL) for value will cause the option to be reset to
 ***   its default behavior.  This function may be called many times to
 ***   change the behavior of the toolkit.  See the documentation for a
 ***   complete list of possible configuration options and their values.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *option - IN - name of the configuration option.
 ***   char *value - IN - new value of the configuration option.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_SetOpt(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char *option, char *value);



/*** VSVAL_SetIntOpt
 ***
 *** DESCRIPTION
 ***   This function sets a configuration option for an option that
 ***   uses integer values. For example,
 ***   VSVAL_SetIntOpt(vs, userCtx, "ldap-timeout", 50) is equivalent to
 ***   VSVAL_SetOpt(vs, userCtx, "ldap-timeout", "50").
 ***   Use this function when your program already has the desired
 ***   config value stored in an integer.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *option - IN - name of the configuration option.
 ***   int nValue - IN - new value of the configuration option.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_SetIntOpt(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char *option, int nvalue);



/*** VSVAL_SetOptVec
 ***
 *** DESCRIPTION
 ***   This function sets many configuration options at once.
 ***   It is equivalent to calling VSVAL_SetOpt once for each option given 
 ***   in the optionVec with the corresponding value in valueVec.
 ***   The input arrays should be null-terminated.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char **optionVec - IN - Null-terminated array of configuration option names.
 ***   char **valueVec - IN - Null-terminated array of configuration option values.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_SetOptVec(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                        char **optionVec, char **valueVec);



/*** VSVAL_SetVOpts
 ***
 *** DESCRIPTION
 ***   This function sets many configuration options at once.
 ***   The option/value pairs should be passed in as consecutive pairs of 
 ***   char pointers. It is equivalent to calling VSVAL_SetOpt once for each
 ***   option/value pair in the argument list.
 ***   npairs is used to specify how many configuration options are read.
 ***   The total number of arguments to the function should be 2 + 2*npairs.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   int npairs - IN - number of name/value pairs to follow
 ***   ... - IN - variable length argument list of pairs of option/value strings.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_SetVOpts(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, int npairs, ... );



/*** VSVAL_GetOpt
 ***
 *** DESCRIPTION
 ***   This function will get the current value of a configuration option.
 ***   It will allocate a pointer to a string version of value.
 ***   Call VSVAL_Free() to free this pointer when you are done with it.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *option - IN - name of the configuration option.
 ***   char **value - OUT - newly allocated pointer to the current value of the
 ***                        configuration option.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_GetOpt(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char **value, char *option);


/*** VSVAL_GetAllOptsToFile
 ***
 *** DESCRIPTION
 ***   This function will get the current value of all configuration options.
 ***   It will write each one's value to a file in the same format that 
 ***   VSVAL_ReadConfigFile reads. NULL values will be commented out.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *filename - IN - name of the output file.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_GetAllOptsToFile(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char *filename);



/*** VSVAL_IsValOption
 ***
 *** DESCRIPTION
 ***   This function will tell if a given option is from this toolkit.
 ***   If the option is a recognized configuration option, TRUE is returned.
 ***   Otherwise, FALSE will be returned.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *option - IN - name of the configuration option.
 ***
 *** RETURNS 
 ***   TRUE (1) or FALSE (0)
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll int VSVAL_IsValOption(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char *option);



/*** VSVAL_MakeCanonicalOptionName
 ***
 *** DESCRIPTION
 ***   This function converts the name of a configuration option into
 ***   a canonical form.  The new name is copied into a buffer
 ***   provided by the caller.
 ***   The canonical version removes '-', '_', isspace() and lowercases.
 ***
 *** ARGUMENTS
 ***   char *outBuf - OUT - buffer to hold the new option name.
 ***   int outLen - IN - bytes available in outBuf.
 ***   char *option - IN - name of the configuration option.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_MakeCanonicalOptionName(char *outBuf, int outLen, char *option);



/*** VSVAL_SetDefaultOptions
 ***
 *** DESCRIPTION
 ***   This function will reset all configuration options to their default values.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_SetDefaultOptions(VSVAL_SDK *vs);



/*** VSVAL_ReadConfigFile
 ***
 *** DESCRIPTION
 ***   This function will read a configuration file.  This file can
 ***   specify the locations of needed certificates and CRLs, as well as
 ***   settings for configuration options.  See the documentation for descriptions
 ***   of the config file.  It can control all aspects of the SDK's behavior,
 ***   including reading from URLs.
 ***   If the cfgFileName parameter is NULL, the configuration option "cfg-file-name"
 ***   will be used.
 ***   If an unknown option is encountered, the function will immediately return 
 ***   an error-- unless the "allow-unknown-options" config option has already been set.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *cfgFileName - IN - name of the configuration file.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ReadConfigFile(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char *cfgFileName);



/*** VSVAL_ReadConfigFileOptions
 ***
 *** DESCRIPTION
 ***   This function will read the configuration options from a config file.
 ***   This allows a user program to share the same config file as the toolkit.
 ***   If the cfgFileName parameter is NULL, the configuration option "cfg-file-name"
 ***   will be used.  Pass in two allocated arrays of maxSize.  These buffers will
 ***   be filled with allocated option name and value strings. Each of these
 ***   pointers (up to nOptions) should be freed with VSVAL_Free when done with it.
 ***   If allOptions is false, only returns unrecognized (non-SDK) options
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char **optionName - OUT - the array is filled with newly allocated pointers
 ***                             to the names of all config options.
 ***   char **optionValue - OUT - the array is filled with newly allocated pointers
 ***                              to the values of all config options.
 ***   int maxSize - IN - number of pointers available in the optionName/Value arrays.
 ***   int *nOptions - OUT - number of values in the optionName/optionValue arrays.
 ***   char *cfgFileName - IN - name of the configuration file.
 ***   int allOptions - IN - should all options be returned?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ReadConfigFileOptions(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                    char **optionName, char **optionValue,
                                    int maxSize, int *nOptions, 
                                    char *cfgFileName, int allOptions);



/*** VSVAL_RefreshCertsCRLs
 ***
 *** DESCRIPTION
 ***   This function will reload all of the certificates and CRLs specified
 ***   in the configuration file.  VSVAL_ReadConfigFile must be called first to 
 ***   read the config file entries.  It will re-acquire any URLs specified in 
 ***   the config file.  This is useful for automatically refreshing CRLs.
 ***   If refreshCerts is FALSE, only CRLs will be reloaded; otherwise both
 ***   certificates and CRLs will be reloaded.  This function will not get
 ***   entries loaded by VSVAL_Load* functions.  It only gets entries from the
 ***   configuration file.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   int refreshCerts - IN - should certificates also be reloaded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_RefreshCertsCRLs(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, int refreshCerts);




/*** 
 ***   These functions are used to read and load trusted roots and other
 ***   CA certificates.
 ***   
 ***   When the comments refer to PEM headers, they are describing the
 ***   the -----BEGIN CERTIFICATE----- and  -----END CERTIFICATE----- 
 ***   style headers and footers sometimes found around Base64-encoded certificates.
 ***
 ***/



/*** VSVAL_LoadFileRootCertDer
 ***
 *** DESCRIPTION
 ***   This function will read a certificate from a file and mark it
 ***   as a trusted root.  The certificate must be in x509 DER format.
 ***   If isB64 is TRUE, the file will be Base64 decoded first.
 ***   If the certificate contains PEM headers/footers, they will be correctly ignored.
 ***   The configuration option "file-prefix" will be prepended to fileName
 ***   before loading.  Set this option to "" to use absolute paths.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *fileName - IN - the name of the certificate file.
 ***   int isB64 - IN - is the certificate Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadFileRootCertDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                  char *fileName, int isB64);


/*** VSVAL_LoadFileCertDer
 ***
 *** DESCRIPTION
 ***   This function will read a certificate from a file for use as a CA.
 ***   The certificate must be in x509 DER format.
 ***   If isB64 is TRUE, the file will be Base64 decoded first.
 ***   If the certificate contains PEM headers/footers, they will be correctly ignored.
 ***   The configuration option "file-prefix" will be prepended to fileName
 ***   before loading.  Set this option to "" to use absolute paths.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *fileName - IN - the name of the certificate file.
 ***   int isB64 - IN - is the certificate Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadFileCertDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                              char *fileName, int isB64);


/*** VSVAL_LoadFileCRLDer
 ***
 *** DESCRIPTION
 ***   This function will read a CRL from a file for use in revocation checking.
 ***   The CRL must be in x509 DER format.
 ***   If isB64 is TRUE, the file will be Base64 decoded first.
 ***   If the CRL contains PEM headers/footers, they will be correctly ignored.
 ***   The configuration option "file-prefix" will be prepended to fileName
 ***   before loading.  Set this option to "" to use absolute paths.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *fileName - IN - the name of the CRL file.
 ***   int isB64 - IN - is the CRL Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadFileCRLDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                             char *fileName, int isB64);



/*** VSVAL_LoadFileCRLPKCS7
 ***
 *** DESCRIPTION
 ***   This function will read a CRL from a file for use in revocation checking.
 ***   The CRL must be in PKCS7 format.
 ***   If isB64 is TRUE, the file will be Base64 decoded first.
 ***   If the CRL contains PEM headers/footers, they will be correctly ignored.
 ***   The configuration option "file-prefix" will be prepended to fileName
 ***   before loading.  Set this option to "" to use absolute paths.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *fileName - IN - the name of the CRL file.
 ***   int isB64 - IN - is the CRL Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadFileCRLPKCS7(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                               char *fileName, int isB64);



/*** VSVAL_LoadRootCertDer
 ***
 *** DESCRIPTION
 ***   This function will read a certificate from a buffer and mark it
 ***   as a trusted root.  The certificate must be in x509 DER format.
 ***   If isB64 is TRUE, the buffer will be Base64 decoded first.
 ***   If the certificate contains PEM headers/footers, they will be correctly ignored.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *cert - IN - buffer containing the certificate.
 ***   int certLen - IN - length of cert (in bytes).
 ***   int isB64 - IN - is the certificate Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadRootCertDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                              unsigned char *cert, int certLen, int isB64);


/*** VSVAL_LoadCertDer
 ***
 *** DESCRIPTION
 ***   This function will read a certificate from a buffer for use as a CA.
 ***   The certificate must be in x509 DER format.
 ***   If isB64 is TRUE, the buffer will be Base64 decoded first.
 ***   If the certificate contains PEM headers/footers, they will be correctly ignored.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *cert - IN - buffer containing the certificate.
 ***   int certLen - IN - length of cert (in bytes).
 ***   int isB64 - IN - is the certificate Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadCertDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                          unsigned char *cert, int certLen, int isB64);


/*** VSVAL_LoadCRLDer
 ***
 *** DESCRIPTION
 ***   This function will read a CRL from a buffer for use in revocation checking.
 ***   The CRL must be in x509 DER format.
 ***   If isB64 is TRUE, the buffer will be Base64 decoded first.
 ***   If the CRL contains PEM headers/footers, they will be correctly ignored.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *crl - IN - buffer containing the CRL.
 ***   int crlLen - IN - length of CRL (in bytes).
 ***   int isB64 - IN - is the CRL Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadCRLDer(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                         unsigned char *crl, int crlLen, int isB64);


/*** VSVAL_LoadCRLPKCS7
 ***
 *** DESCRIPTION
 ***   This function will read a CRL from a buffer for use in revocation checking.
 ***   The CRL must be in PKCS7 format.
 ***   If isB64 is TRUE, the buffer will be Base64 decoded first.
 ***   If the CRL contains PEM headers/footers, they will be correctly ignored.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *crl - IN - buffer containing the CRL.
 ***   int crlLen - IN - length of CRL (in bytes).
 ***   int isB64 - IN - is the CRL Base64 encoded?
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_LoadCRLPKCS7(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                           unsigned char *crl, int crlLen, int isB64);


  /* Convert error codes and CS_ status codes into text. */

/*** VSVAL_IsValError
 ***
 *** DESCRIPTION
 ***   This function will tell if a given error code is from this toolkit.
 ***   If the error code is recognized, TRUE is returned. 
 ***   Otherwise, FALSE is returned.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   int errorCode - IN - integer error code.
 ***
 *** RETURNS 
 ***   TRUE (1) or FALSE (0)
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll int VSVAL_IsValError(VSVAL_SDK *vs, int errorCode);



/*** VSVAL_ErrorString
 ***
 *** DESCRIPTION
 ***   This function will provide a text description of an error code.
 ***   The description is copied into a pre-allocated buffer provided by the caller.
 ***   When some errors occurr, they record extra information (such as an
 ***   associated filename) in the userCtx->errorInfo field.
 ***   This field may be passed to this function for a more descriptive result.
 ***   If this is not available, simply pass NULL for errorInfo.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   char *buffer - OUT - buffer to hold the error string.
 ***   int bufferLen - IN - bytes available in outBuf.
 ***   int errorCode - IN - integer error code.
 ***   char *errorInfo - IN - optional pointer to userCtx->errorInfo.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ErrorString(VSVAL_SDK *vs, char *buffer, int bufferLen,
                          int errorCode, char *errorInfo);


/*** VSVAL_CertStatusString
 ***
 *** DESCRIPTION
 ***   This function will provide a text description for a certificate status code.
 ***   It returns a pointer to a static constant string.
 ***   This pointer should not be freed.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   int certStatus - IN - certificate status code (ie, CS_VALID, etc...)
 ***
 *** RETURNS 
 ***   pointer to a static string description
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll char *VSVAL_CertStatusString(VSVAL_SDK *vs, int certStatus);


/*** VSVAL_ParseCert
 ***
 *** DESCRIPTION
 ***   This function will parse a certificate into readable fields.
 ***   It does this in the exact same manner as the VeriSign Certificate
 ***   Parsing Module (CPM).  CPM is also known as CDR.
 ***   This function will allocate a pointer to a new VSVAL_CertFields structure
 ***   that contains all of the readable certificate fields.
 ***   Call VSVAL_FreeCertFields to free the pointer when you are done with it.
 ***   Do not use VSVAL_Free on this pointer or you will cause a memory leak.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   VSVAL_CertFields **certFields - OUT - newly allocated pointer to
 ***                                        a VSVAL_CertFields structure.
 ***   unsigned char *cert - IN - buffer containing the certificate.
 ***   int certLen - IN - length of cert (in bytes).
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ParseCert(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                        VSVAL_CertFields **certFields, 
                        unsigned char *cert, int certLen);


/*** VSVAL_ParseB64Cert
 ***
 *** DESCRIPTION
 ***   This function will parse a Base64 encoded certificate into readable fields.
 ***   It does this in the exact same manner as the VeriSign Certificate
 ***   Parsing Module (CPM).  CPM is also known as CDR.
 ***   This function will allocate a pointer to a new VSVAL_CertFields structure
 ***   that contains all of the readable certificate fields.
 ***   Call VSVAL_FreeCertFields to free the pointer when you are done with it.
 ***   Do not use VSVAL_Free on this pointer or you will cause a memory leak.
 ***   If the certificate contains PEM headers/footers, they will be correctly ignored.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   VSVAL_CertFields **certFields - OUT - newly allocated pointer to
 ***                                        a VSVAL_CertFields structure.
 ***   char *b64Cert - IN - null-terminated Base64 certificate string.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ParseB64Cert(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                           VSVAL_CertFields **certFields, char *b64Cert);



/*** VSVAL_FreeCertFields
 ***
 *** DESCRIPTION
 ***   This function will free a VSVAL_CertFields structure.
 ***   Use it to free the pointers returned by VSVAL_ParseCert/VSVAL_ParseB64Cert.
 ***   Do not use VSVAL_Free to free a VSVAL_CertFields pointer or
 ***   you will cause a memory leak.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_CertFields *certFields - IN - pointer to be freed.
 ***
 *** RETURNS 
 ***   void
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll void VSVAL_FreeCertFields(VSVAL_SDK *vs, VSVAL_CertFields *certFields);


/*** VSVAL_GetRevocationStatus
 ***
 *** DESCRIPTION
 ***   This function will determine the revocation status of a certificate.
 ***   The certificate must be in x509 DER format.
 ***   A chain of certificates will be built until a trusted root is found.
 ***   The revocation status will then be checked based on the configuration
 ***   options that have been set.
 ***   certStatus will get the correct status code. (CS_VALID, CS_REVOKED, etc...)
 ***
 ***   If userName is not null, it will be set to point to a newly allocated 
 ***   printable string version of the cert subject name. 
 ***   This userName should be freed with VSVAL_Free when you are done with it.
 ***
 ***   This function will return non-zero if any error occurrs.  In some cases, 
 ***   certStatus will still be set correctly even if an error occurred.
 ***   If *certStatus is non-zero, a proper revocation check has been performed 
 ***   and the error can be safely ignored. You may still want to take action
 ***   to correct the problem, so the error code is still returned.
 ***   To be extremely conservative, use the return code to see if an error happened.
 ***   To get the most work done, use *certStatus!=0 to check for errors.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *cert - IN - buffer containing the certificate.
 ***   int certLen - IN - length of cert (in bytes).
 ***   int *certStatus - OUT - certificate status code (ie, CS_VALID, etc...)
 ***   char **userName - OUT - optional newly allocated subject name string.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_GetRevocationStatus(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                  unsigned char *cert, int certLen,
                                  int *certStatus, char **userName);

/*** VSVAL_GetRevocationStatusB64
 ***
 *** DESCRIPTION
 ***   This function will determine the revocation status of a Base64
 ***   encoded certificate. If the certificate contains PEM headers/footers, 
 ***   they will be correctly ignored.
 ***
 ***   Otherwise, this function behaves exactly the same as VSVAL_GetRevocationStatus.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *b64Cert - IN - null-terminated Base64 certificate string.
 ***   int *certStatus - OUT - certificate status code (ie, CS_VALID, etc...)
 ***   char **userName - OUT - optional newly allocated subject name string.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_GetRevocationStatusB64(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                                     char *b64Cert, int *certStatus, char **userName);



/*** VSVAL_ParseDetachedPKCS7
 ***
 *** DESCRIPTION
 ***   This function will parse a detached PKCS7 signature message.
 ***   It can be used in conjunction with VSVAL_CompareMsgHash to verify a 
 ***   detached PKCS7 signature. Use VSVAL_VerifyDetachedPKCS7 to do both steps at once.
 ***
 ***   The signed hash from the pkcs7 will be copied into a pre-allocated buffer
 ***   provided by the caller. This hash buffer should contain at least 20 bytes
 ***   (VSVAL_HASH_MAX_LEN) of free space.  No memory will be allocated for the hash.
 ***   hashLen will receive the number of bytes written into hash.
 ***   outAlgorithm will be either VSVAL_HASH_ALG_MD5 or VSVAL_HASH_ALG_SHA.
 ***
 ***   This function will verify only that the PKCS7 was signed correctly. 
 ***   To complete the verification, you must obtain the detached text by other means.
 ***   Hash this text, and compare it to the hash returned by this function.
 ***   If they match, the complete detached PKCS7 has been verified.
 ***   
 ***   The function can optionally return the PKCS7 signer's certificate.
 ***   If cert is not NULL, it will get a newly allocated buffer containing the
 ***   x509 DER of the signer certificate.
 ***   When you are done with it, you must free this pointer with VSVAL_Free.
 ***
 ***   If certStatus is not NULL, it will receive the revocation status of the 
 ***   PKCS7 signer's certificate.  See VSVAL_GetRevocationStatus for details.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *pkcs7 - IN - buffer containing the pkcs7.
 ***   int pkcs7Len - IN - length of pkcs7 (in bytes).
 ***   unsigned char *hash - OUT - the hashed output.
 ***   int *hashLen - OUT - length of hashed output data (in bytes).
 ***   int *outAlgorithm - OUT - which hash algorithm was used in the pkcs7.
 ***   unsigned char **cert - OUT - newly allocated buffer containing the 
 ***                                certificate used to sign the pkcs7.
 ***   int *certLen - OUT - length of output cert (in bytes).
 ***   int *certStatus - OUT - optional certificate status of the signer cert.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_ParseDetachedPKCS7(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                 unsigned char *pkcs7, int pkcs7Len, 
                                 unsigned char *hash, int *hashLen, int *outAlgorithm,
                                 unsigned char **cert, int *certLen, int *certStatus);



/*** VSVAL_VerifyDetachedPKCS7
 ***
 *** DESCRIPTION
 ***   This function will verify a detached PKCS7 signature message.
 ***   To do this, you must obtain both the PKCS7 message and the detached text.
 ***   This function will verify that the PKCS7 was signed correctly, and 
 ***   compare the signature to the detached text.  If they match, 0 is returned.
 ***   Otherwise a bad signature error is returned. 
 ***   
 ***   The function can optionally return the PKCS7 signer's certificate.
 ***   If cert is not NULL, it will get a newly allocated buffer containing the
 ***   x509 DER of the signer certificate.
 ***   When you are done with it, you must free this pointer with VSVAL_Free.
 ***
 ***   If certStatus is not NULL, it will receive the revocation status of the 
 ***   PKCS7 signer's certificate.  See VSVAL_GetRevocationStatus for details.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *pkcs7 - IN - buffer containing the pkcs7.
 ***   int pkcs7Len - IN - length of pkcs7 (in bytes).
 ***   unsigned char *msg - IN - buffer containing the detached text.
 ***   int msgLen - IN - length of msg (in bytes).
 ***   unsigned char **cert - OUT - newly allocated buffer containing the 
 ***                                certificate used to sign the pkcs7.
 ***   int *certLen - OUT - length of output cert (in bytes).
 ***   int *certStatus - OUT - optional certificate status of the signer cert.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_VerifyDetachedPKCS7(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                  unsigned char *pkcs7, int pkcs7Len, 
                                  unsigned char *msg, int msgLen, 
                                  unsigned char **cert, int *certLen, int *certStatus);



/*** VSVAL_CompareMsgHash
 ***
 *** DESCRIPTION
 ***   This function will compute the message digest (hash) of a 
 ***   given buffer and compare it to an existing message digest.
 ***   It can be used in conjunction with VSVAL_ParseDetachedPKCS7 to verify a 
 ***   detached PKCS7 signature. Use VSVAL_VerifyDetachedPKCS7 to do both steps at once.
 ***   The function will return 0 if the given hash/hashLen matches the 
 ***   hash of msg/msgLen.
 ***   The hash algorithm should be either VSVAL_HASH_ALG_MD5 or VSVAL_HASH_ALG_SHA1.
 ***   No memory is allocated by this function.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *msg - IN - buffer containing the data to hash.
 ***   int msgLen - IN - length of data (in bytes).
 ***   int hashAlgorithm - IN - which hash algorithm to use.
 ***   unsigned char *hash - IN - the hash to compare msg with.
 ***   int hashLen - IN - length of hash (in bytes).
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_CompareMsgHash(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                             unsigned char *msg, int msgLen, 
                             int hashAlgorithm, unsigned char *hash, int hashLen);


/*** VSVAL_HashMessage
 ***
 *** DESCRIPTION
 ***   This function will compute the message digest (hash) of a given buffer.
 ***   The hash is copied into a pre-allocated buffer provided by the caller.
 ***   The hash buffer should contain at least 20 bytes (VSVAL_HASH_MAX_LEN).
 ***   The hash algorithm should be either VSVAL_HASH_ALG_MD5 or VSVAL_HASH_ALG_SHA1.
 ***   No memory is allocated by this function.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *msg - IN - buffer containing the data to hash.
 ***   int msgLen - IN - length of data (in bytes).
 ***   int hashAlgorithm - IN - which hash algorithm to use.
 ***   unsigned char *hash - OUT - the hashed output.
 ***   int *hashLen - OUT - length of hashed output data (in bytes).
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_HashMessage(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                          unsigned char *msg, int msgLen, 
                          int hashAlgorithm, unsigned char *hash, int *hashLen);



  /* These functions will do Base64 encoding and decoding. */

/*** VSVAL_Base64Alloc
 ***
 *** DESCRIPTION
 ***   This function will Base64 encode a buffer.
 ***   It will allocate a null-terminated b64String from the given binary data.
 ***   It will NOT add PEM headers/footers to the string.
 ***   Call VSVAL_Free when you are done with the b64String pointer.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char **b64String - OUT - newly allocated, null-terminated string.
 ***   unsigned char *data - IN - buffer containing the data to encode.
 ***   int len - IN - length of data (in bytes).
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_Base64Alloc(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, char **b64String,
                          unsigned char *data, int len);

/*** VSVAL_DeBase64Alloc
 ***
 *** DESCRIPTION
 ***   This function will decode a Base64 encoded string.
 ***   It will allocate a buffer containing the decoded binary data.
 ***   It will put the length of the allocated buffer in len.
 ***   It will NOT handle PEM headers/footers to the string.  If your data
 ***   is a certificate or CRL with these headers, use VSVAL_DeBase64CertAlloc.
 ***   Call VSVAL_Free when you are done with the data pointer.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char **data - OUT - newly allocated buffer containing the decoded data.
 ***   int *len - OUT - length of decoded data (in bytes).
 ***   char *b64String - IN - null-terminated string with Base64 encoded data.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_DeBase64Alloc(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                            unsigned char **data, int *len, char *b64String);


/*** VSVAL_DeBase64CertAlloc
 ***
 *** DESCRIPTION
 ***   This function will decode a Base64 encoded string.
 ***   It will allocate a buffer containing the decoded binary data.
 ***   It will put the length of the allocated buffer in len.
 ***   It will ignore the PEM headers/footers of the string.
 ***   Call VSVAL_Free when you are done with the data pointer.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char **data - OUT - newly allocated buffer containing the decoded data.
 ***   int *len - OUT - length of decoded data (in bytes).
 ***   char *b64Cert - IN - null-terminated string with Base64 encoded certificate/CRL.
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   Any of the VSVAL_ERR_* error codes.
 ***
 ***/
Dll int VSVAL_DeBase64CertAlloc(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx,
                                unsigned char **data, int *len, char *b64Cert);


/*** VSVAL_Free
 ***
 *** DESCRIPTION
 ***   This function will free a pointer allocated by this toolkit.
 ***   Use it to free the pointers returned by SDK functions that allocate memory.
 ***   Do not use this function to free a VSVAL_CertFields pointer or
 ***   you will cause a memory leak.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   void *p - IN - pointer to be freed.
 ***
 *** RETURNS 
 ***   void
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll void VSVAL_Free(VSVAL_SDK *vs, void *p);



/*** VSVAL_Bin2Hasc
 ***
 *** DESCRIPTION
 ***   This function converts binary data to ascii format.
 ***   Half-ascii or Hex-ascii, depending on your preferred nomenclature.
 ***   Pass in outBuf with at least (2*len+1) bytes already allocated.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   unsigned char *data - IN - binary data to convert.
 ***   unsigned int *len - IN -  length of data (in bytes).
 ***   char *outBuf - OUT - converted ascii string.
 ***
 *** RETURNS 
 ***   outBuf - so that it can be used inline.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll char *VSVAL_Bin2Hasc(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                         unsigned char *data, unsigned int len, char *outBuf);



/*** VSVAL_Hasc2Bin
 ***
 *** DESCRIPTION
 ***   This function convert ascii data to binary format.
 ***   Half-ascii or Hex-ascii, depending on your preferred nomenclature.
 ***   Pass in outBuf with at least (2*len+1) bytes already allocated.
 ***   Writes the data into "buf" and the length into "len".
 ***   "buf" must already be allocated with enough room.
 ***
 *** ARGUMENTS
 ***   VSVAL_SDK *vs - IN - pointer to SDK handle.
 ***   VSVAL_UserCtx *userCtx - IN - pointer to user context.
 ***   char *hasc - IN - ascii string to convert.
 ***   unsigned char *outData - OUT - converted binary data.
 ***   unsigned int *outLen - OUT -  length of data (in bytes).
 ***
 *** RETURNS 
 ***   int - 0 for success, non-zero for any error.
 ***
 *** POSSIBLE ERROR CODES RETURNED:
 ***   None.
 ***
 ***/
Dll int VSVAL_Hasc2Bin(VSVAL_SDK *vs, VSVAL_UserCtx *userCtx, 
                       char *hasc, unsigned char *outData, unsigned int *outLen);



#ifdef __cplusplus
           }
#endif
/* end of C wrapper for C++ */

#endif /*  _VSVAL_SDK_H_ */
