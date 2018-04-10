/*
 * $Revision: 1.2.342.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/include/vsverify.h,v 1.2.342.1 2001/03/16 23:48:15 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#pragma ident   "@(#)vsverify.h    4.6    2001/01/09"   /* OnSite 4.6 */

#ifndef _VSVERIFY_H_
#define _VSVERIFY_H_

#include <stdio.h>

#ifdef WIN32
#define EXPORTSPEC __declspec(dllexport)
#else
#define EXPORTSPEC
#endif

#ifdef AASIGN_SOURCE
#define AA_ENTRY EXPORTSPEC
#else
#define AA_ENTRY
#endif

#ifdef __cplusplus
extern "C" {
#endif
/*
 * This header file defines the APIs for Verification and Signing.
 */

/*
 * Section 1. Hook API. This API should be implemented by the customer.
 */

/*
 * The VSAA_Name structure is used to store a name value pair.
 */

typedef struct
{
  char *pszName ;
  char *pszValue ;
} VSAA_NAME ;
/*
 * The arrays of VSAA_NAME are always terminated with an empty entry
 * (i.e. a struct in which pszName and pszValue are NULL). The output
 * structure need not physically copy the strings from the input if
 * they are not modified, it may simply point to those strings. Do not
 * delete / free any of the strings passed as input.
 */


typedef enum 
{
  VSAA_SUCCESS = 0,
  VSAA_VERIFY_FAILED = 1,
  VSAA_SIGN_FAILED = 3,
  VSAA_UPDATE_FAILED = 4,
  VSAA_OUT_OF_MEMORY = 5,
  VSAA_INVALID_CERT =6,
  VSAA_HARD_ERROR=7,
  VSAA_BAD_CONFIG_FILE=8,
  VSAA_CANNOT_LOGIN=9,
  VSAA_SIGNER_NOT_INITED=10,
  VSAA_INTERNAL_ERROR=11,
  VSAA_NO_PUBKEY=12,
  VSAA_BAD_MSG=13,
  VSAA_CERT_PENDING=14,
  VSAA_CERT_FAILURE=15,
  VSAA_CANNOT_REACH_VS=16,
  VSAA_BAD_URL=17,
  VSAA_BAD_CSR=18,
  VSAA_NO_SERVER_URL=19,
  VSAA_NO_ISSUER=20,
  VSAA_NO_SERIAL=21,
  VSAA_NO_REASON=22,
  VSAA_NO_CHALLENGE=23,
  VSAA_NO_COMMENT=24,
  VSAA_NO_TIME=25,
  VSAA_UNKNOWN_REASON=26,
  VSAA_BAD_TIME_FMT=27,
  VSAA_BAD_SERIAL=28,
  VSAA_BAD_ISSUER=29,
  VSAA_TIMEDOUT=30,
  VSAA_LOG_FAILED=31,
  VSAA_SLOT_ID_INVALID=32,
  VSAA_PIN_INCORRECT=33,
  VSAA_TOKEN_NOT_PRESENT=34,
  VSAA_USER_PIN_NOT_INITIALIZED=35,
  VSAA_PRIVATE_KEY_NOT_FOUND=36,
  VSAA_CERT_EXPIRED_OR_NOT_FOUND=37,
  VSAA_CAN_NOT_DECRYPT=38,
  VSAA_CERT_EXPIRED=39,
      
  VSAA_NO_DOMESTIC=99,
  
  /* Common configuration and module errors, range: 100 -- 199 */

  VSAA_ERR_CFG=100,
  VSAA_ERR_CFG_FILE_OPEN,
  VSAA_ERR_CFG_ENTRY_MISSING,  
  VSAA_ERR_CFG_ENTRY_NOT_FOUND,
  VSAA_ERR_CFG_DUPL_ENTRIES,
  VSAA_ERR_CFG_FILE_LINE_TOO_LONG,
  VSAA_ERR_CFG_ILLEGAL_SPACE_MARKER,
  VSAA_ERR_LOAD_DLL,
  VSAA_ERR_QUERY_DLL_API,
  VSAA_ERR_INVALID_DATA,
  VSAA_ERR_CERTIFICATE_NOT_GIVEN,  
  VSAA_ERR_BASE64,
  
  /* LDAP support error codes, range: 200 -- 299 */

  VSAA_LDAP_ERR=200,
  VSAA_LDAP_ERR_CFG,
  VSAA_LDAP_ERR_INIT,
  VSAA_LDAP_ERR_BIND,
  VSAA_LDAP_ERR_SEARCH,
  VSAA_LDAP_ERR_INVALID_DATA,
  VSAA_LDAP_ERR_CFG_BINDDN,
  VSAA_LDAP_ERR_AUTH_ATTR_NOT_FOUND,
  VSAA_LDAP_ERR_AUTH_ATTR_NOT_QUALIFY,
  VSAA_LDAP_ERR_HOSTNAME_NULL,
  VSAA_LDAP_ERR_PORT_MISSING,
  VSAA_LDAP_ERR_AUTHENTICATE_FAILED,
  VSAA_LDAP_ERR_CONNECT_FAILED,

  /* ODBC support error codes, range: 300 -- 399 */

  VSAA_ODBC_ERR=300,
  VSAA_ODBC_ERR_OPEN_CONNECTION,
  VSAA_ODBC_ERR_OPEN_CURSOR,
  VSAA_ODBC_ERR_CFG,
  VSAA_ODBC_ERR_CFG_SQL  

} VSAA_STATUS;

/*
 * Revocation reason flags as defined in PKIX part 1 - 06
 */

#define VSAA_REV_UNUSED				"Unspecified"
#define VSAA_REV_KEYCOMPROMISE			"Key compromise"
#define VSAA_REV_CACOMPROMISE			"CA compromise"
#define VSAA_REV_AFFILIATIONCHANGED		"Affiliation changed"
#define	VSAA_REV_SUPERSEDED			"Superseded"
#define VSAA_REV_CESSATIONOFOPERATION		"Cessation of operation"
#define VSAA_REV_CERTIFICATEHOLD		"Certificate hold"

/*
 * General defines used by aasign and its clients.
 */
#define VSAA_REGISTER		"register"	/* registration operation */
#define VSAA_ERROR_OP		"error_register"/* error notification operation */
#define VSAA_SIGNER_OP		"ReceiveEncryptedResponse"
#define VSAA_RETURN_OP		"DecryptedResponse"
#define VSAA_ENVELOPED_DATA	"encryptedText"
#define VSAA_AA_SUBMIT		"AutoAuthOSUserSubmit"
#define VSAA_AA_PICKUP		"permenant"
#define VSAA_AA_REVOKE		"do user revoke"
#define VSAA_AA_RENEWAL		"userRenewal"
#define VSAA_AUTHENTICATE	"authenticate"
#define VSAA_YES		"YES"
#define VSAA_NO			"NO"
#define VSAA_PENDING		"PENDING"
#define VSAA_CSR		"csr"
#define VSAA_CERT_DN		"cert_DN"
#define VSAA_CERT_SERIAL	"cert_serial"
#define VSAA_CERT_BASE64	"cert_base64"
#define VSAA_COMMON_NAME	"common_name"
#define VSAA_ENROLL_URL		"vsenroll_url"
#define VSAA_RAWOUTPUT		"RAW_OUTPUT"
#define VSAA_XID		"transaction_id"
#define VSAA_NONCE		"nonce"
#define VSAA_ORIG_OP        "original_operation"

#define VSAA_START_ERROR	0xA000

#define VSAA_CLIENT_CERT        "CLIENT_CERT"
#define VSAA_USER_CERT          "USER_CERT"
#define VSAA_RENEW_METHOD       "getMethod"
#define VSAA_RENEW_USER_CERT    "autoAuth"
#define VSAA_RENEW_MSIE         "pkcs7"
#define VSAA_RENEW_ID           "renewalID"
#define VSAA_LIFECYCLE_REQ	    "lifecycle_request"
#define VSAA_RENEW		        "renew"

/*
 * The format for the VSAA_ISSUER value is the base64 encoded DER of the issuer name. This
 * is obtained independently from VeriSign.
 */
#define VSAA_ISSUER		"issuerName"
#define VSAA_SUBJECT		"subjectName"

/*
 * The format for the serial number is a text representation of the hex value of the serial
 * number.
 */
#define VSAA_SERIAL		"certSerial"
#define VSAA_REASON		"reason"
#define VSAA_CHALLENGE		"challenge"
#define VSAA_COMMENT		"comment"
#define VSAA_TIME		"time"

/*
 * The following defines are for names of the pairs for which the values are defined below:
 */
#define VSAA_OPERATION		"operation"
#define VSAA_MSGTYPE		"messageType"
#define VSAA_MSGSTATUS		"messageStatus"
#define VSAA_STATUSCODE		"error_status"
#define VSAA_CERT_OR_CRL	"certOrCRL"
/*
 * The following defines are the operation codes returned by ReceiveEncryptedResponse.
 */
#define VSAA_CERTREP		"CertRep"
#define VSAA_REVREP		"RevRep"

/*
 * The following defines are for the status of the response.
 */
#define VSAA_RESP_SUCCESS	"Response_Success"
#define VSAA_RESP_FAILURE	"Response_Failure"
#define VSAA_RESP_PENDING	"Response_Pending"

/*
 * The MAX_TRIES value defines the number of times sophia will try to contact 
 * VSENROLL_URL before returning an error.
 */
#define VSAA_MAX_TRIES	(3)
#define VSAA_CONNECT_TIMER 60

/*
 * Hook API function: ProcessEntries
 * This function is implemented by the automated authentication partner.
 * If the function succeeds, it returns VSAA_SUCCESS and
 * (*panOutput) contains the name value pairs to be sent to the VeriSign site.
 *
 * The entry list is guaranteed to have "operation" as the first name-value
 * pair and it should be used to switch what the function is expected to do.
 *
 * If the function fails, the function should return one of the
 * error codes above. the (*panOutput) parameter should
 * still contain name value pairs that are sent to VeriSign site.
 *
 * If there is any unexpected error, VSAA_STATUS should be
 * (VSAA_ONSITE_BASE+n), where n >= 0. This error code will be mapped to
 * an error code that can be specified in the "Form Description File"
 * and (*panOutput) will contain name value pairs that can be substituted
 * in the output file.
 */
extern
VSAA_STATUS AA_ENTRY ProcessEntries(VSAA_NAME anInput[], VSAA_NAME **panOutput) ;


/*
 * The FreeEntries() function is used to free data returning from 
 * ProcessEntries() function
 */
extern
void FreeEntries(VSAA_NAME **freeNames);


/*
 * Section 2. Signing API. This is implemented by the signing server and should
 * be called after verification.
 */

/*
 * Signer initialization.
 */

extern VSAA_STATUS AA_ENTRY VSAA_InitSigner(const char *fileName);
extern void AA_ENTRY VSAA_CleanupSigner(void) ;

/*
 * The SetDebugLog function set or reset debugging information for aasign library.
 * This function should be invoked before invoking any other functions.
 * While performing any signing functions, if an error is encountered, this function
 * will emit internal error code.
 */
extern void AA_ENTRY VSAA_SetDebugLog(FILE *fp);

/*
 * The following routines is used to free memory returned from the signing library
 */
extern void EXPORTSPEC VSAA_FreeName(VSAA_NAME **list);


/*
 * The SignEnrollRequest function will sign the name value pairs in the input
 * after flattening the input into a string of the form:
 * "name=value&name=value&..."
 * The name-value pairs in anInput are contained in the signed message that
 * is returned by the function and they need not be specified
 * separately to the CGI at VeriSign (through the panOutput parameter). Only
 * the signed message itself has to be one of the inputs to the post to the
 * VeriSign CGI.
 *
 * A successful enrollment should contain a name-value pair: "Authenticate=YES"
 * a negative verification should contain a name-value pair: "Authenticate=NO",
 * a "don't know" or pending enrollment should contain a name-value pair:
 * "Authenticate=PENDING".
 *
 * There should be exactly one "Authenticate=.." variable in the input or the
 * signing will fail.
 *
 * If the signing fails, the function returns NULL and a message is written
 * to the signing server's log file.
 *
 * The returned name-value pair on a successful signing has the name
 * "VSAA_SIGNED_MESSAGE".
 *
 * The SignEnrollRequest function is thread-safe from the operation point of view. I.e.
 * multiple threads/processes can call SignEnrollRequest simultaeneously. However the
 * session level mutual exclusion has to be handled by the application calling the
 * InitSigner and CleanupSigner functions.
 *
 */
extern VSAA_STATUS AA_ENTRY VSAA_EncodePKCSReq(
	VSAA_NAME verifiedEnrollInfo[], 
	VSAA_NAME **panOutput,
	int allInOne,
	const char *signerConfigFile);


/*
 * The VSAA_EncodeGetCert function requires two names to be present in it's name value pairs:
 * 1. VSAA_ISSUER ("issuerName"): TIPEM format issuer distinguished name
 * 2. VSAA_SERIAL ("certSerial"): half ASCII encoded serial number of the cert being looked up
 */
extern VSAA_STATUS AA_ENTRY VSAA_EncodeGetCert(
	VSAA_NAME anInput[],
	VSAA_NAME **panOutput,
	int allInOne,
	const char *signerConfigFile);


/*
 * The VSAA_EncodeRevReq function requires the following names to be present in the input
 * name value pairs:
 * 1. VSAA_ISSUER ("issuerName"): TIPEM format issuer distinguished name
 * 2. VSAA_SERIAL ("certSerial"): half ASCII encoded serial number of the cert being revoked
 * 3. VSAA_REASON ("reason"): Reason for revocation. The value for this name has to be one
 *		of the VSAA_REV_ defines above.
 * 4. VSAA_CHALLENGE ("challenge"): challenge phrase of the cert being revoked.
 * 5. VSAA_COMMENT ("comment"): comment about the revocation request.
 */
extern VSAA_STATUS AA_ENTRY VSAA_EncodeRevReq(
	VSAA_NAME anInput[],
	VSAA_NAME **panOutput,
	int allInOne,
	const char *signerConfigFile);


/*
 * The VSAA_EncodeGetCRL function requires the following names to be present in the input:
 * 1. VSAA_ISSUER ("issuerName"): TIPEM format issuer distinguished name
 * 2. VSAA_TIME ("time"): time for the CRL's update that is less than but nearest to this value.
 * the format for the time value is (decimal values for each entry):
 * "year month day hour minute second fractionalSecond"
 * e.g the date: February 1, 1998 12.30 pm would be represented as the string:
 *  "1998 2 1 12 30 0 0"
 */
extern VSAA_STATUS AA_ENTRY VSAA_EncodeGetCRL(
	VSAA_NAME anInput[],
	VSAA_NAME **panOutput,
	int allInOne,
	const char *signerConfigFile) ;


extern VSAA_STATUS AA_ENTRY VSAA_EncodePassThru(
        VSAA_NAME anInput[],
        VSAA_NAME **panOutput,
        int allInOne,
        const char *signerConfigFile) ;

/*
 * The VSAA_DecodeCertRep function requires the following names to be present in the input:
 * 1. VSAA_ENVELOPED_DATA ("encryptedText"): base 64 encoded CertRep
 */
extern VSAA_STATUS AA_ENTRY VSAA_DecodeCertRep(
	VSAA_NAME anInput[],
	VSAA_NAME **panOutput,
	int allInOne,
	const char *signerConfigFile);

/* The following functions are provided in libaautil.so library
   to directly exchange messages with PKIclient and decode PKCS7 */

extern VSAA_STATUS AA_ENTRY VSAA_ExchangeMsg(
	const char *pkiclientURL,	// /cgi-bin/crs.exe
	const char *proxyHost,		// 80
	int proxyPort,				// secure-test-fe.bbtest.net
	const VSAA_NAME *req,		// Output of VSAA_Encode*() function
	VSAA_NAME **rsp				// Input of VSAA_DecodeCertRep() function
	);

/*
 * The VSAA_ExtractCert function requires the following names to be present in the input:
 * 1. VSAA_CERT_OR_CRL ("certOrCRL"): base 64 encoded PKCS#7 which contains the cert
 * Output:
 * 1. "cert_DN": subject distinguished name in HTML format.
 * 2. VSAA_CERT_BASE64 ("cert_base64"): base 64 encoded X.509 certificate.
 * 3. VSAA_CERT_SERIAL ("cert_serial"): half ASCII encoded certificate serial number
 */
extern VSAA_STATUS AA_ENTRY VSAA_ExtractCert(
	const VSAA_NAME *req, 
	VSAA_NAME **rsp);

/*
 * The VSAA_DecodeCert function requires the following names to be present in the input:
 * 1. VSAA_CERT_BASE64 ("cert_base64"): base 64 encoded X.509 certificate.
 * Output:
 * 1. VSAA_CERT_SERIAL ("cert_serial"): half ASCII encoded certificate serial number
 * 2. VSAA_ISSUER ("issuerName"): TIPEM format issuer distinguished name
 * 3. VSAA_SUBJECT ("subjectName"): TIPEM format subject distinguished name
 */
extern VSAA_STATUS AA_ENTRY VSAA_DecodeCert(
	const VSAA_NAME *req,
	VSAA_NAME **rsp);

/*
 * The VSAA_SetPassword function set the cert store password prior to calling VSAA_InitSigner.
 * This function is only affected in the software signer
 */
extern VSAA_STATUS AA_ENTRY VSAA_SetPassword(
		const char *password);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif/*_VSVERIFY_H_*/
