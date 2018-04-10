/*
 * $Revision: 1.3.84.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/vsexchange/include/vsutil.h,v 1.3.84.1 2003/06/06 22:46:31 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSUTIL_H_
#define _VSUTIL_H_

#include "vsverify.h"

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

/*
 * Common configuration keyword
 */
#define CFG_HOSTNAME            "HOSTNAME"
#define CFG_PORT                "PORT"
#define CFG_LOG                 "LOGFILE"
#define CFG_LOG_LEVEL           "VSAA_LOG_LEVEL"
#define CFG_LOG_HIDE_ATTR       "LOG_HIDE_ATTR"
#define CFG_DB                  "DBFILE"
#define CFG_ODBC                "DATABASE"
#define CFG_USR                 "DBUSERNAME"
#define CFG_PSWD                "DBPASSWORD"
#define CFG_KEY_MGR_SERVICE     "KEY_MGR_SERVICE"
#define CFG_LUNA_FILE           "LUNA"
#define CFG_KEY                 "KEY"
#define CFG_PASSPHRASE          "KEY_PASSWORD"
#define CFG_SSLLOG              "SSL_LOG"
#define CFG_SSLLOG_LEVEL        "SSL_LOG_LEVEL"
#define CFG_AUTHSRV_DLL         "AUTH_SERVICE_DLL"
#define CFG_REGSRV_DLL          "REG_SERVICE_DLL"
#define CFG_EXCHANGE_SERVER     "EXCHANGE_SERVER"
#define CFG_EXCHANGE_DOMAIN     "EXCHANGE_DOMAIN"


/* Debugging level for Secure Channel */
#define VSSC_NONE_STR           "none"
#define VSSC_ERROR_STR          "error"
#define VSSC_INFO_STR           "info"
#define VSSC_DEBUG_STR          "debug"

#define DEBUG_FILE              "pestub.out"
#define CFG_FILE                "pestub.cfg"
#define DB_FILE                 "validuser.txt"
#define LUNA_CFG_FILE           "vsautoauth.conf"
#define KEY_FILE                "public.key"
#define NO_KEY_FILE             "nokey"
#define VSAASRV_LOG_FILE        "vsaasrv.out"
#define VSAASRV_PATH            "VSAASRV_PATH"


#define KEY_ACCT        "AccountNumber"
#define KEY_PIN         "PIN"
#define KEY_FIRST       "mail_firstName"
#define KEY_LAST        "mail_lastName"
#define KEY_USRID		"additional_field5"
#define KEY_EMAIL		"mail_email"
#define KEY_MIDDLE		"mail_middleName"
#define KEY_SSN			"Social_Security_Number"
#define KEY_CHALLENGE	"Challenge_Phrase"
#define KEY_DOB			"usb_dob"
#define KEY_DL			"Driver_License_Number"
#define KEY_WORKPHONE	"additional_field4"
#define KEY_AUTH		"authenticate"
#define KEY_DIRECTORY	"xxx"
#define VSAA_ENCODING_NAME      "character_encoding"


/*
 * external function prototypes in vsutil.cpp
 */
void        Dump        (FILE *debugFile, const char *msg, const VSAA_NAME list[]);
VSAA_NAME * Duplicate	(const VSAA_NAME list[]);
size_t      Entries     (const VSAA_NAME list[]);
const char *FindName    (const char *pszName, size_t nameLen, const VSAA_NAME userInput[]);
VSAA_STATUS GetConfig   (const char *configFile, VSAA_NAME param[]);
void        Release     (VSAA_NAME **list);
int			StrCaseCmp	(const char *s1, const char *s2, size_t len);
int         FlattenNamesAlloc(VSAA_STATUS status, const VSAA_NAME *anInput, unsigned long *len, unsigned char **buffer);
VSAA_NAME * ResurrectNamesAlloc(unsigned long len, const unsigned char *buffer, VSAA_STATUS *status);
VSAA_STATUS ExtractDn(const VSAA_NAME *input, VSAA_NAME **dn);
void        Log(FILE *debugFile, const char *format, ...);
void        StartDebugger(const char *fileName);
VSAA_STATUS VerifyExchangeDll(const VSAA_NAME userInput[], char *exchangeServer, char *exchangeDomain, FILE *debugFile);

#endif
