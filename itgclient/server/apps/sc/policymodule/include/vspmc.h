/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmc.h,v 1.1.2.1 2001/09/06 22:32:12 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMC_H_
#define _VSPMC_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define VSPM_EXPORT extern __declspec( dllexport )
#else
#define VSPM_EXPORT extern
#endif

#define SCOPE_CHAR '//'

/* This enum holds all error codes that can be returned from
 * calls to VeriSign's DLL.
 */

typedef unsigned int VSPM_STATUS;

#define       VSPM_STATUS_NO_ERROR              0xC000    /* no error */
#define       VSPM_CANNOT_OPEN_FILE             0xC001    /* Cannot open the file */
#define       VSPM_INVALID_TOKEN                0xC002    /* Invalid token in the file */
#define       VSPM_NO_CLOSE_SESSION             0xC003    /* No closing bracket */
#define       VSPM_OUT_OF_MEMORY                0xC004    /* No more memory */
#define       VSPM_INVALID_DESCRIPTOR           0xC005    /* The specified VSPM_Descriptor is invalid */
#define       VSPM_NOT_FOUND                    0xC006
#define       VSPM_INVALID_TEXT                 0xC007
#define       VSPM_INVALID_T61                  0xC008
#define       VSPM_INVALID_EMAIL                0xC009
#define       VSPM_INVALID_NUMBER               0xC00A
#define       VSPM_INVALID_BASE64               0xC00B
#define       VSPM_INVALID_PHONE                0xC00C
#define       VSPM_INVALID_DATE                 0xC00D
#define       VSPM_INVALID_TYPE                 0xC00E
#define       VSPM_FIELD_REQUIRED               0xC00F
#define       VSPM_FIELD_TOO_SHORT              0xC010
#define       VSPM_FIELD_TOO_LONG               0xC011
#define       VSPM_INVALID_VERSION              0xC012
#define       VSPM_INDEX_OUT_OF_RANGE           0xC013
#define       VSPM_INVALID_FILE_FORMAT          0xC014
#define       VSPM_NOT_SUPPORTED_FILE_FORMAT    0xC015
#define       VSPM_INVALID_PASSCODE             0xC016

/* PMC specific status codes */
#define       VSPM_NOT_SUPPORTED_FEATURE		0xC017
#define       VSPM_INVALID_CRS_URL				0xC018
#define       VSPM_INVALID_ENROLLMENT_URL			0xC019

typedef void *			VSPM_Descriptor;
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


/* This function opens a policy description file
 *
 *   pathname - IN  - the path name of the policy description file
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reas
on
 *   RETURNS  - a VSPM_Descriptor or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Descriptor
        VSPM_Open (
                const char *pathname,
                VSPM_STATUS *status);


/* This function closes and cleans up the data associated with a previously opened VSPM_Descriptor
 *
 *   pmd - IN  - the descriptor of the policy description file
 *              
 */

VSPM_EXPORT void
        VSPM_Close (
                VSPM_Descriptor pmd);



/* This function returns the a textual explanation associated with a VSPM_STATUS
 *
 *   pmd      - IN  - the descriptor to the policy file
 *   status   - IN  - status code to be explained
 *   RETURNS  - a null-terminated string. This string can contain multi-byte characters.
 *              NULL if an error is encountered
 */

VSPM_EXPORT const char *
		VSPM_DescribeStatus (
				VSPM_Descriptor pmd,
				VSPM_STATUS status);


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


/* This function frees the memory occupied by a null-terminated string
 *
 *   str      - IN  - the null-terminated string
 *   status   - OUT - if the function fails, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPM_FreeString (
                char * str,
                VSPM_STATUS *status);


#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMC_H_ */
