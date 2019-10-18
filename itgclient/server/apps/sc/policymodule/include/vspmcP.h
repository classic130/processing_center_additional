/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmcP.h,v 1.1.2.1 2001/09/06 22:32:13 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMC_P_H_
#define _VSPMC_P_H_

#include "vspmutil.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define VSPM_EXPORT extern __declspec( dllexport )
#else
#define VSPM_EXPORT extern
#endif

#define SCOPE_CHAR '//'

#define END_USER_SPEC_MAJ 1
#define END_USER_SPEC_MIN 0

/* PMC specific status codes */
#define       VSPM_NOT_SUPPORTED_FEATURE        0xC017
#define       VSPM_INVALID_CRS_URL              0xC018
#define       VSPM_INVALID_ENROLLMENT_URL       0xC019


/* policy value for processType item                              */
/* it is used to map the policy to the VSPM_FIELD_PROCESSING_TYPE */
#define VSPM_USER_INPUT			"USER_INPUT"
#define VSPM_USER_SELECTABLE	"USER_SELECTABLE"
#define VSPM_HARD_CODED			"HARD_CODED"
#define VSPM_SOFTWARE_CONFIG	"SOFTWARE_CONFIG"
#define VSPM_DISPLAY_ONLY		"DISPLAY_ONLY"


/* policy value for type item                            */
/* it is used to provide value checking for the fdf type */
#define VSPM_FDF_TEXT		"TEXT"
#define VSPM_FDF_EMAIL		"EMAIL"
#define VSPM_FDF_CLEAR		"CLEAR"
#define VSPM_FDF_T61		"T61"
#define VSPM_FDF_BASE64		"BASE64"
#define VSPM_FDF_DATE		"DATE"
#define VSPM_FDF_NUMBER		"NUMBER"
#define VSPM_FDF_PHONE		"PHONE"
#define VSPM_FDF_PASSCODE	"PASSCODE"


/* policy value for valueConstraint item                                  */
/* it is used to provide more thorough value checking beyond the fdf type */
#define VSPM_TEXT		"TEXT"
#define VSPM_EMAIL		"EMAIL"
#define VSPM_BASE64		"BASE64"
#define VSPM_CLEAR		"CLEAR"
#define VSPM_T61		"T61"
#define VSPM_PASSCODE	"PASSCODE"


/* Due to the mismatch between fdf entry and policy entry, some enrollment parameters
 * are not directly represented by policy entry. For example the I18N related items
 * There is only one policy entry (CharEncoding) while there are four separate 
 * fdf related entries. Thus we need to "cheat" when counting the parameters
 */

#define MIN_PARAM_COUNT 	5


typedef void *			VSPM_PARAMETER;
typedef void *			VSPM_CRYPT_CONFIG;

typedef enum {
	VSPM_USER_INPUT_FIELD,
	VSPM_USER_SELECTABLE_FIELD,
	VSPM_HARD_CODED_FIELD,
	VSPM_SOFTWARE_CONFIG_FIELD,
	VSPM_DISPLAY_ONLY_FIELD
} VSPM_FIELD_PROCESSING_TYPE;

typedef enum {
	VSPM_VALUE_TEXT,
	VSPM_VALUE_T61,
	VSPM_VALUE_NUMBER,
	VSPM_VALUE_BASE64,
	VSPM_VALUE_EMAIL,
	VSPM_VALUE_PHONE,
	VSPM_VALUE_DATE,
	VSPM_VALUE_CLEAR,
	VSPM_VALUE_PASSCODE
} VSPM_VALUE_TAG;

typedef enum {
	VSPM_REQ_OPTIONAL = 0,
	VSPM_REQ_MANDATORY
} VSPM_REQUIREMENT;

typedef enum {
	VSPM_END_USER = 0,
	VSPM_SERVER,
	VSPM_IPSEC
} VSPM_PRODUCT_TAG;

typedef enum {
	VSPM_NO_KEY_MANAGER = 0,
	VSPM_SINGLE_KEY,
	VSPM_DUAL_KEY
} VSPM_KEY_MANAGER_TAG;

typedef enum {
	VSPM_MANUAL_AUTH = 0,
	VSPM_AUTO_AUTH
} VSPM_AUTH_SCHEME_TAG;

typedef enum {
	VSPM_FALSE = 0,
	VSPM_TRUE
} VSPM_BOOL;

typedef struct {
	VSPM_BOOL isCSPUserSelectable;
	VSPM_BOOL checkEnhanced;
	VSPM_BOOL isKeyExportable;
	VSPM_BOOL isKeyProtectionUserSelectable;
	VSPM_BOOL isKeyProtected;
	VSPM_BOOL isKeyLengthDegradable;
	unsigned short keyLength;
	char * prefCSP;
	char *minAdvapi32Ver;
	char * minCrypt32Ver;
} _VSPM_CRYPT_CONFIG;


typedef struct {
	VSPM_FIELD_PROCESSING_TYPE fieldType;
	char * displayName;
	char * internalName;
	char * value;
	VSPM_VALUE_TAG tag;
	VSPM_REQUIREMENT req;
	unsigned short minLen;
	unsigned short maxLen;
} _VSPM_PARAMETER;


/* policy entry name definition */
#define VSPM_GLOBALVAR_CONTAINER        "Global/GlobalVar"

#define VSPM_MODE_CONTAINER             "Global/Mode"

#define VSPM_BROWSERVER_CONTAINER       "Global/BrowserVersion"

#define VSPM_CRYPTVER_CONTAINER         "Global/CryptVer"

#define VSPM_REMOTE_HOST                "remoteHost"
#define VSPM_VS_HOST                    "vsHost"
#define VSPM_LOCAL_HOST                 "localHost"
#define VSPM_JURISDICTION_HASH          "jurisdictionHash"
#define VSPM_CORP_NAME                  "corpName"
#define VSPM_ORG_UNIT_NAME              "orgUnitName"
#define VSPM_PROD_CONFIG                "productConfigFile"
#define VSPM_PRIVATE_LABEL              "privateLabel"
#define VSPM_APPLICATION_MS             "applicationMS"
#define VSPM_APPLICATION_NS             "applicationNS"
#define VSPM_CLASS                      "class"
#define VSPM_ORIGINATOR                 "originator"
#define VSPM_CRS_URL                    "crsUrl"
#define VSPM_EXPIRATION_WINDOW          "AbtToExpireWindow"
#define VSPM_ISSUER_DN                  "certIssuerDN"
#define VSPM_ISSUER_CERT                "issuerCert"
#define VSPM_SUBJECT_DN_TEMPLATE        "SubjectDNTemplate"


#define VSPM_USER_ENROLLMENT_CONTAINER  "Enrollment"

#define VSPM_FIRST_NAME_CONTAINER       "FirstName"
#define VSPM_LAST_NAME_CONTAINER        "LastName"
#define VSPM_EMAIL_CONTAINER            "EMAIL"
#define VSPM_EMP_ID_CONTAINER           "EmpID"
#define VSPM_JOB_TITLE_CONTAINER        "JobTitle"
#define VSPM_MAIL_STOP_CONTAINER        "MailStop"
#define VSPM_ADD_FIELD4_CONTAINER       "AddField4"
#define VSPM_ADD_FIELD5_CONTAINER       "AddField5"
#define VSPM_ADD_FIELD6_CONTAINER       "AddField6"
#define VSPM_PASSCODE_CONTAINER         "PassCode"
#define VSPM_SUBS_AGREEMENT_CONTAINER   "SubscriberAgreement"
#define VSPM_CSP_CONTAINER              "CSP"
#define VSPM_CHAR_ENCODING_CONTAINER    "CharEncoding"
#define VSPM_KEY_PROTECT_CONTAINER      "KeyProtect"
#define VSPM_KEY_LENGTH_CONTAINER       "KeyLength"
#define VSPM_KEY_EXPORT_CONTAINER       "KeyExportable"
#define VSPM_KEY_LENGTH_CONTAINER       "KeyLength"
#define VSPM_CERT_PUBLISH_CONTAINER     "CertPublish"


#define VSPM_USER_RENEWAL_CONTAINER     "Renewal"

#define VSPM_APP_EXCHANGE_CONTAINER     "Apps/ExchangeInt"

#define VSPM_APP_KEY_MANAGER_CONTAINER  "Apps/KeyManager"

#define VSPM_APP_PCA_CONTAINER          "Apps/WAC"

#define VSPM_VERSION_NAME               "Version"
#define VSPM_POLICY_VALUE               "policyValue"
#define VSPM_DISPLAY_NAME               "DisplayName"
#define VSPM_INTERNAL_NAME              "internalName"
#define VSPM_PROCESS_TYPE               "processType"
#define VSPM_VALUE                      "value"
#define VSPM_FDF_TYPE                   "type"
#define VSPM_IS_REQUIRED                "bRequired"
#define VSPM_IS_PROTECTED               "bProtect"
#define VSPM_CAN_DEGRADE                "bDegrade"
#define VSPM_IS_PUBLISHED               "bPublish"
#define VSPM_IN_CERT_FIELD              "bCertField"
#define VSPM_CHECK_ENHANCED             "bCheckEnhanced"
#define VSPM_IS_ENROLL_PARAM			"bEnrollParam"
#define VSPM_VALUE_CONTSTRAINT			"valueConstraint"
#define VSPM_MIN_LEN                    "MinLength"
#define VSPM_MAX_LEN                    "MaxLength"
#define VSPM_ADVAPI                     "minAdvapi32Ver"
#define VSPM_CRYPTVER                   "minCrypt32Ver"
#define VSPM_HELP_EMAIL                 "helpEmail"

#define VSPM_EX_SERVER_DN               "ExServerDN"
#define VSPM_EX_SERVER_SITE             "ExServerSiteName"
#define VSPM_EX_SERVER_DOMAIN           "ExServerDomain"
#define VSPM_PREFERRED_PROV             "preferredProv"
#define VSPM_PROV_NAME                  "provName"
#define VSPM_SUBAGRURL                  "subAgrURL"
#define VSPM_MIN_VER_NS                 "minVersionNS"
#define VSPM_MIN_VER_MS                 "minVersionMS"

#define EXISTS                          "exists"
#define ABSENT                          "absent"

#define YES                             "yes"
#define NO                              "no"

#define Y                               "Y"
#define N                               "N"

#define MANDATORY                       "MANDATORY"
#define OPTIONAL                        "OPTIONAL"

#define TRUE_VAL                        "1"
#define FALSE_VAL                       "0"

#define SINGLE                          "single"
#define DUAL                            "dual"

#define USER                            "user"
#define POLICY                          "policy"

#define DEFAULT                         "default"
#define SPECIFIED                       "specified"

#define SHOW                            "show"
#define NO_SHOW                         "noshow"

#define MANUAL_VAL                      "manualauth"
#define AUTOAUTH_VAL                    "autoauth"
#define PASSCODE_VAL                    "passcodeauth"

#define MANUAL                          "manual"
#define AUTOAUTH                        "autoauth"
#define PASSCODE                        "passcode"

#define VERSION                         "version"
#define CHAR_ENCODING                   "charEncoding"
#define CHAR_SET                        "charSet"
#define CHAR_FILTER                     "charFilter"
#define CHAR_FILTER_PARAM               "charFilterParam"

#define SOPHIALITE_PATH                 "/cgi-bin/sophialite.exe"
#define SOPHIA_PATH                     "/cgi-bin/sophia.exe"


/* This function returns the major and minor numbers of the enrollment
 * specification implemented by the interface
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   maj      - OUT - the major version of the enrollment spec for the product type
 *   min      - OUT - the minor version of the enrollment spec for the product type
 *   status   - OUT - status code
 *   
 */

VSPM_EXPORT void
        VSPM_GetSpecVersion (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
				unsigned short *maj,
				unsigned short *min,
                VSPM_STATUS *status);


/* This function returns the number of enrollment parameters associated with the
 * enrollment policy of a given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 *   RETURNS  - an positive integer or 
 *              0 if no item is found or an error is encountered
 */

VSPM_EXPORT unsigned int
        VSPM_GetParameterCount (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status);


/* This function returns the enrollment parameter based on the product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   index    - IN  - between 0 and the value returned by VSPM_GetParamterCount()
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_PARAMETER or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_PARAMETER
        VSPM_GetParameter (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                unsigned int index,
                VSPM_STATUS *status);


/* This function verifies the enrollment data associated with a parameter
 *
 *   param    - IN  - parameter returned by the VSPM_GetParameter() function
 *   value    - IN  - data to be verified
 *   RETURNS  - status  
 *
 */

VSPM_EXPORT VSPM_STATUS
        VSPM_VerifyParameter (
				const VSPM_PARAMETER param,
                const char *value);


/* This function returns the cryptographic configuration policy for CAPI
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *                    returned by VSPM_ContainerCountFromDescriptor
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - a VSPM_CRYPT_CONFIG or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_CRYPT_CONFIG
        VSPM_GetCryptConfig (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status);


/* This function returns the email address for support issue during
 * the enrollment process
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - an rfc822 email address or
 *              NULL if an error is encountered
 *
 */

VSPM_EXPORT const char *
        VSPM_GetHelpEmail (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the URL for CRS enrollment
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   protocol - OUT - The OnSite CRS enrollment transport protocol
 *   hostName - OUT - The OnSite CRS enrollment host name
 *   portNumber - OUT - The OnSite CRS enrollment port number
 *   crsURI   - OUT - The OnSite CRS enrollment responder path name
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_GetCRSEnrollmentURL (
                VSPM_Descriptor pmd,
                const char** protocol, 
                const char** hostName, 
                const char** portNumber, 
                const char** crsURI, 
                VSPM_STATUS *status);


/* This function returns the URL for enrollment
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   protocol - OUT - The OnSite enrollment transport protocol
 *   hostName - OUT - The OnSite enrollment host name
 *   portNumber - OUT - The OnSite enrollment port number
 *   cgiURI   - OUT - The OnSite enrollment responder path name
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_GetEnrollmentURL (
                VSPM_Descriptor pmd,
                const char** protocol, 
                const char** hostName, 
                const char** portNumber, 
                const char** cgiURI, 
                VSPM_STATUS *status);


/* This function returns the number of days before the certificate expiration date 
 * the subscriber should be reminded to renew the certificate
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - number of days before the certificate expiration date
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetCertExpireWindow (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the key manager configuration tag
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - VSPM_KEY_MANAGER_TAG
 *
 */

VSPM_EXPORT VSPM_KEY_MANAGER_TAG
        VSPM_GetKeyManagerTag (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the authentication scheme configuration tag
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   status   - OUT - status code
 *   RETURNS  - VSPM_AUTH_SCHEME_TAG
 *
 */

VSPM_EXPORT VSPM_AUTH_SCHEME_TAG
        VSPM_GetAuthSchemeTag (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function returns the field processing type of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_FIELD_PROCESSING_TYPE
 *
 */

VSPM_EXPORT VSPM_FIELD_PROCESSING_TYPE
        VSPM_GetFieldProcessingType (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the display name of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetDisplayName (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the internal name of the certificate enrollment
 * parameter
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetInternalName (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the value of the certificate enrollment
 * parameter. Applicable only if the processing type is
 * VSPM_HARD_CODED_FIELD
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetParamValue (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the value tag of the certificate enrollment
 * parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_VALUE_TAG
 *
 */

VSPM_EXPORT VSPM_VALUE_TAG
		VSPM_GetValueTag (
				VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the field requirement of the certificate enrollment
 * parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - VSPM_REQUIREMENT
 *
 */

VSPM_EXPORT VSPM_REQUIREMENT
        VSPM_GetRequirement (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the minimum length in character
 * of the certificate enrollment parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - minimum length in number of characters
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetMinLen (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the maximum length in character
 * of the certificate enrollment parameter.
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   RETURNS  - maximum length in number of characters
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetMaxLen (
                VSPM_PARAMETER param,
				VSPM_STATUS *status );


/* This function returns the default/preferred CSP from
 * cryptographic policy
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - null terminated string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCSP (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether the CSP is user selectable 
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsCSPUserSelectable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether an application should check for
 * the existence of enhanced cryptographic provider
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_CheckEnhancedProvider (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether an application allow key
 * pairs to be exported
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyExportable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether an application allows the subscriber to
 * decide whether or not to enable key protection
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyProtectionUserSelectable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether the private key should be protected
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyProtected (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns the size of the key
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the number of bits for the key
 *
 */

VSPM_EXPORT unsigned short
        VSPM_GetKeyLength (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns whether an application allows key size to be
 * degraded if the one returned by VSPM_GetKeyLength() is not available
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - VSPM_FALSE or VSPM_TRUE
 *
 */

VSPM_EXPORT VSPM_BOOL
        VSPM_IsKeyLengthDegradable (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns the minimum version required for ADVAPI32
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the version string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetMinAdvapi32Ver (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns the minimum version required for CRYPT32
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   RETURNS   - the version string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetMinCrypt32Ver (
                VSPM_CRYPT_CONFIG cryptConf,
				VSPM_STATUS *status );


/* This function returns the issuer's DN using the rfc 1779 format for a
 * given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - issuer DN string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCertIssuerDN (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status);


/* This function returns the template to format the subject DN
 * using the rfc 1779 format for a given product type
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *   RETURNS  - subject DN template string
 *
 */

VSPM_EXPORT const char *
        VSPM_GetCertSubjectDNTemplate (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
                VSPM_STATUS *status);


/* This function returns the issuer's certificate in binary X.509 format
 *
 *   pmd      - IN  - the descriptor of the policy description file
 *   prodType - IN  - the product type of the enrollment policy
 *   issuerIndex - IN - issuer's index in the certificate chain.
 *                      (Note: It has to be 0 for this release)
 *   certBuf  - OUT - issuer's X.509 certificate in binary format
 *   certSize - OUT - the size of certBuf
 *   status   - OUT - if the function returns NULL, the return status indicates the
 *                    failure reason
 *
 */

VSPM_EXPORT void
        VSPM_GetCertIssuerChain (
                VSPM_Descriptor pmd,
				VSPM_PRODUCT_TAG prodType,
				unsigned int issuerIndex,
				char ** certBuf,
				unsigned int * certSize,
                VSPM_STATUS *status);


/* This function deallocates the memory occupied by a VSPM_PARAMETER structure
 *
 *   param    - IN  - the reference to VSPM_PARAMETER
 *   status   - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeParam (
                VSPM_PARAMETER param,
                VSPM_STATUS *status);


/* This function deallocates the memory occupied by a VSPM_CRYPT_CONFIG structure
 *
 *   cryptConf - IN  - the reference to VSPM_CRYPT_CONFIG
 *   status    - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeCryptConfig (
                VSPM_CRYPT_CONFIG cryptConf,
                VSPM_STATUS *status);


/* This function deallocates the buffer containing the binary X.509 certificate
 *
 *   certBuf - IN  - the pointer to the certificate buffer
 *   status  - OUT - status code
 *
 */

VSPM_EXPORT void
        VSPM_FreeCertBuf (
                char * certBuf,
                VSPM_STATUS *status);


/* private functions */
_VSPM_PARAMETER * 
		GetInternalParam(
				VSPM_Descriptor pmd, 
				unsigned int index, 
				VSPM_STATUS *status);

#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMC_P_H_ */
