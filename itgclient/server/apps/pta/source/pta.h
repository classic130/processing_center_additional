
/****************************************************************************************
* 
* pta.h
* This is the top level header file containing all the definitions for the 
* common PTA structures and routines
* Include this file in your plugin specific code 
*
* Author - Siddharth Bajaj 03/03/01
* 
* Change History
* -
* -
*
*****************************************************************************************/


#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#ifndef _PTA_H_
#define _PTA_H_ 1

#ifdef DEBUG
#define DEBUGMSG
#endif
#include "limits.h"
  /*
#include "ptaexternal.h"
  */
#include "valsdk.h"

/**********************************************************************
version number defines 
**********************************************************************/

#ifdef SOLARIS
		#pragma ident "@(#)VeriSign ptaserver 7.2.0.0 2007/10/19"     
#else
#ifdef HPUX
		#pragma VERSIONID "@(#)VeriSign ptaserver 7.2.0.0 2007/10/19" 
#endif
#endif


/********************************************************************
 * Macro definitions
 *******************************************************************/

#ifndef vsMIN
#define vsMIN(x1, x2)     (((x1) <= (x2)) ? (x1) : (x2))
#endif
#ifndef vsMAX
#define vsMAX(x1, x2)     (((x1) >= (x2)) ? (x1) : (x2))
#endif

/**********************************************************************
common defines 
**********************************************************************/

#define PTA_LARGE_BUF_MAX 4096
#define PTA_MAX_LINE_LENGTH 4096
#define PTA_SMALL_BUF_MAX 1024
#define PTA_TINY_BUF_MAX   256
#define MAX_DIGEST_LEN 20
#define MD5_LEN 16
#define SHA_LEN 20
#define SM_MAX_RETRIES_FOR_TOKEN 2
#define SM_SUPPORT_FAILOVER_DEFAULT_OPTION 0

#define PTA_NSAPI_DESCR "VeriSign Personal Trust Agent Plugin, Version 7.2"
#define PTA_FILTER_DESCRIPTION "VeriSign Personal Trust Agent Filter, Version 7.2"
#define APACHE_PTA_DESCRIPTION "VeriSign Personal Trust Agent Module, Version 7.2"
#define APACHE_PTA_LOG_DESCRIPTION "VeriSign PTA 7.2"
#define VS_PTA_PLUGIN_DESC "VeriSign Personal Trust Agent, Version 7.2"

#define PTA_REGISTRY_KEY "Software\\VeriSign\\PTA\\1.0"
#define COMVSSSC_REGISTRY_KEY "Software\\VeriSign\\comvsssc\\1.0"

/*#define HTTP_COOKIE_DATE_FMT "%a, %d-%b-%Y %H:%M:%S GMT"*/

#define PTA_SIGNED_HEADER "The following data is for authentication purpose only."
#define PTA_SIGNED_HEADER_LEN 54
#define SSC_POST_SIG_FIELD "dataSignature="
#define SSC_POST_SIG_FIELD_LEN 14

#define VSVAL_PTA_ERR_BASE 9950	
#define VSVAL_PTA_OS_VERSION                  (VSVAL_PTA_ERR_BASE + 1)
#define VSVAL_PTA_ERR_MAX                         (VSVAL_PTA_ERR_BASE + 2)


#define PTA_MAX_UPDATE_TIME INT_MAX
#define PTA_LDAP_TIMEOUT 120
#define PTA_LDAP_HTTP_CGI "cgi-bin/ldappost.exe"


#define PTA_POST_SIG_FIELD "dataSignature="
#define PTA_POST_SIG_FIELD_LEN 14


/* Very simple struct representing the login page. */
/* We write preVars, then the SSC_VARS section, then postVars. */
#define VS_PTA_LOGIN_TAG "$$SSC_VARS$$"
#define VS_PTA_LOGIN_TAG_LEN 12

/* Additional certificate status codes. */
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

#ifdef DEBUG
#define DEBUGMSG 1
#endif




/* error codes */
#define VS_ERR_BASE  9600
#define VS_ERR_NO_MEM                     (VS_ERR_BASE + 0)
#define VS_ERR_BAD_PARAM                  (VS_ERR_BASE + 1)
#define VS_ERR_MISSING_CONFIG_VAL         (VS_ERR_BASE + 2)
#define VS_ERR_COOKIE_DOMAIN              (VS_ERR_BASE + 3)
#define VS_ERR_LOGIN_PAGE                 (VS_ERR_BASE + 4)
#define VS_ERR_RANDOM                     (VS_ERR_BASE + 5)
#define VS_ERR_NO_URI                     (VS_ERR_BASE + 6)
#define VS_ERR_ADMIN_UNSUPPORTED          (VS_ERR_BASE + 7)
#define VS_ERR_SHLIB                      (VS_ERR_BASE + 8)
#define VS_ERR_VAL_INIT                   (VS_ERR_BASE + 9)
#define VS_ERR_ADMIN_HASC                 (VS_ERR_BASE + 10)
#define VS_ERR_NO_SAVE_CERTS              (VS_ERR_BASE + 11)
#define VS_ERR_OPTION_FILE                (VS_ERR_BASE + 12)
#define VS_ERR_RANDOM_CLOCK               (VS_ERR_BASE + 13)
#define VS_ERR_RANDOM_FILE                (VS_ERR_BASE + 14)
#define VS_ERR_FILE_OPEN                  (VS_ERR_BASE + 15)
#define VS_ERR_FILE_READ                  (VS_ERR_BASE + 16)
#define VS_ERR_LOG_FILE                   (VS_ERR_BASE + 17)
#define VS_ERR_REGISTRY                   (VS_ERR_BASE + 18)
#define VS_ERR_NO_ROOT                    (VS_ERR_BASE + 19)
#define VS_ERR_MUTEX                      (VS_ERR_BASE + 20)
#define VS_ERR_PLUGIN_INIT                (VS_ERR_BASE + 21)
#define VS_ERR_SERVER_NAME                (VS_ERR_BASE + 22)
#define VS_ERR_INVALID_UPDATE_HOURS       (VS_ERR_BASE + 23)
/* Be sure and update VS_ERR_MAX, too. */
#define VS_ERR_MAX                        (VS_ERR_BASE + 24)

/*
 * pta_loglevel_t
 * defines the log level
 *
 */
enum pta_loglevel_t
{
  PTA_LOG_ERROR = 0 /* this includes error and warning message */
 ,PTA_LOG_INFO = 1 /* additional information for deployment confirmation purpose */
 ,PTA_LOG_DEBUG = 2 /* trouble shooting*/
 ,PTA_LOG_DEBUG_DETAIL = 3 /* add details such as print table, print hex */
};


/* POINTER defines a generic pointer type */
typedef unsigned char* POINTER;

typedef unsigned long int PTATIME;


/* For a Macintosh, where time is returned in seconds since
     1/1/1904 12:00:00 AM, YEAR_BASE should be defined as 1904.
   For Microsoft C 7.0, YEAR_BASE should be defined as 1900.
   The following defines YEAR_BASE as 1970 if it has not already been
     defined as something else with C compiler flags.
 */
#ifndef YEAR_BASE
#define YEAR_BASE 1970
#endif

/* Calculate the time adjustment the number of seconds between the year
     base and 1970. */
#define TIME_ADJUSTMENT \
  ((PTATIME)(365 * (1970 - YEAR_BASE) + ((1970 - YEAR_BASE) + 2) / 4) * \
   (PTATIME)24 * (PTATIME)3600)

/* If the time() function returns local time, define GMT_OFFSET to be
     the number of hours that local time is EARLIER than GMT.
*/
#ifndef GMT_OFFSET
#define GMT_OFFSET 0
#endif

#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif


/**********************************************************************
PTA type definitions
**********************************************************************/

/* This is the revocation callback implemented by the server plugins and 
called from vsPTAAuthorizePost 
*/
typedef int (*pFnGetRevocationInfo) (ITEM *certItem, int *certStatus,
                                     PTATIME *statusExpires, char **userName);

/* For Authorization Dll that we load. */
typedef int (*pFnInit)      (char *version, char *cfgString);
typedef int (*pFnCheck)     (int certStatus, char *url,
                             unsigned char *certBuf, unsigned int certLen, 
                             char *pkcs7, char *userName);
typedef int (*pFnFinal)     (void);

/**********************************************************************
PTA specific data structures
**********************************************************************/


typedef struct login_page_s {
  ITEM preVars; /* part of login page BEFORE $$SSC_VARS$$ */
  ITEM postVars; /* part of login page AFTER $$SSC_VARS$$ */
} login_page_t;


/*Prototypes*/
/* need to move this prototype to pta.h once the hash functions accept void* */
typedef struct client_data_s {
  char *url; /* the url they were trying to access. */
  char *pkcs7; /* the posted pkcs7 (b64). Freed after it's put in cgi env once. */
  int authorized; /* has this entry been authenticated already? */
  unsigned long int absolute_timeout; /* In GMT seconds. */
  unsigned long int inactive_timeout; /* In GMT seconds. */
  unsigned long int revocation_timeout; /* In GMT seconds. */
  unsigned char iSDigest[MD5_LEN]; /* MD5 Issuer Serial Digest. */
  char *userName; /* the subject dn from the cert. Saved if env-vars or js-vars. */
  ITEM cert; /* saved unless no-save-certs. */
} client_data_t;


  /* the following hash table related definitions should only be used for Apache
     Stronghold version of the PTA */
typedef struct link_s {
  ITEM key;
  client_data_t *data;
  struct link_s *next;
} link_t;

struct hash_table_s;

typedef int (*pHashFn) (struct hash_table_s *htable, ITEM key);

typedef struct hash_table_s {
  link_t **heads;
  int size;
  pHashFn fn;
} hash_table_t;


  /* The PTA runtime configuration data structure */
typedef struct VS_PTA_CONFIG_STRUCT {

  /* These are all ignored and should be removed from this struct:
     signCanned */

  /* RANDOM_OBJ randObj;*/

  char *optionFile; /* Full disk path to optional file holding more config info. */

  /* pointer to Info message logger */
  /* if log-info is on, this points to a real logger, else it's a null logger. */
  void (* InfoLog) (void *handler, char *fmt, ...);
  
  int logSecurity; /* Log security messages? */
  int logInfo; /* Log Info messages? */

  int checkOCSP; /* check OCSP based revocation status */

  /* Md5 of administrator for /vsadmin/* urls.  Specify hascVal in obj.conf. */
  unsigned char adminIssuerSerial[MD5_LEN];

  int addEnvVars; /* add environment vars to rq->headers for cgis? */
  int addJSVars; /* ditto for javascript */
  char *loginPageMS; /* Full disk path to static login page (includes ActiveX control) */
  /* 
     Modified By: Infosys Technologies Ltd. 
     Change Request: CR #27988
     Description: Additional member variable to store the sleep value. This value is a 
     period in milli-seconds for which the filter will halt in case of requests to haydn.exe.
  */    
  int sleepValue; 
  /* CR #27988 Ends. */
  char *loginPageNS; /* Full disk path to static login page (includes ActiveX control) */
  char *smLoginUrl;  /* login page for siteminder */
  int smSupportFailover; /* boolean this feature enable failover of policy server */
  int  smMaxTriesForToken; /* in case of smSupportFailover, max number a token can be validated */

  int noCacheLogin; /* re-read from disk each time? */
  login_page_t loginValueMS; /* Here's where we cache the login page value. */
  login_page_t loginValueNS; /* Here's where we cache the login page value. */

  int noCachePages; /* Send "Pragma: no-cache" for all pages?  */

  char *errorUrl; /* NS. Must be on this server. "/","/cgi-bin/error", etc... */
  char *errorPage; /* IIS. html page. Path to disk file. */
  ITEM errorPageItem; /* IIS. html page. Path to disk file. */
  int addErrorJSVars; /* prepend js var defs to errorurl? */

  char *logoutUrl; /* Must be on this server. Typically a static html page. */

  /* These two are stored in seconds, but specified in minutes in the config file. */
  unsigned int absoluteTimeout; /* Total time can be logged in. Takes priority. */
  unsigned int inactiveTimeout; /* also logged out if inactive for this many seconds. */
  unsigned int garbageTime; /* cert can't be removed until absolute+garbage time. */
  unsigned int tokenTimeout; /* total time a token can be valid */

  char *randomFile; /* Full disk path to optional file to be added to random seed. */

  /* If this is used, Must also set cookieName. */
  char *cookieDomain; /* if not set, defaults to this machine. */

  char *cookieName; /* if not set, name+rand() */

  hash_table_t *hTableSh;
  VSVAL_htable hTable;
  int hTableSize;

  int signText; /* should toSign be treated as ascii instead of normal hasc binary? */
  int signCanned; /* should we add the canned header? */
  int noSSL; /* SSL is not required (on the cookie). ONLY FOR DEBUGGING. */

  /* for logging info messages. Remove this nsapi specific stuff. */
  void *sn;
  void *rq;
  char *fnName;
  /* Since there are two mutexes, cvm and ssc can run at once.  */
  /* Need two sets of these. */
  void *cvmSn;
  void *cvmRq;
  char *cvmFnName;

  int useMD5; /* otherwise uses SHA1 */

  /* For authorization plugins */
  char *shlibName;
  void *dlHandle;
  pFnInit dlInit;
  pFnCheck dlCheck;
  pFnFinal dlFinal;

  int noCRLCheck; /* Do revocation checking? */
  int noSaveCerts; /* keep certs in memory? */
  int savePkcs7; /* keep posted pkcs7's in memory? */

  /* Whoever loads ssc.must provide this. See nsapival.ssl for an example. */
  pFnGetRevocationInfo fnGetRevocationInfo;

  int protectJavaDirs; /* since NS looks for /java/* on server. */

  /* IIS only.  What dirs do we need to protect? */
  char **protectedDirList;
  int protectedDirCount;

  int cvmLogSecurity;
  int cvmCheckChain;
  PTATIME cvmUpdateSeconds;
  PTATIME cvmLastUpdate;
  char *cvmErrorCgi;
  
  VSVAL_SDK *vsValSDK;

  /* Name of this server. fqdn. */
  char *serverName;
  int serverNameLen;
} VS_PTA_CONFIG;



/**********************************************************************
common utility routines
**********************************************************************/

void pta_time (PTATIME *theTime);
void pta_make_newline_null(char *str);
int ptaCfgStringIsOn(const char *value);
/*
void (* ptaGlobalInfoLog) (char *fmt, ...);
*/
unsigned char * sscT_malloc (unsigned int s);
char *sscT_strdup(const char *s1);
unsigned char * sscT_realloc (unsigned char * p, unsigned int s);
void sscT_free (unsigned char * s);

int sscErrorString(char **errorString, int errorCode);

void vsNullLogInfoMessage(void *handle, char *fmt, ...);
int removeEOL(ITEM * buf) ;		

int ptaLogBase2(int n);
int ptaKeyEq(ITEM l, ITEM r);
int ptaHasc2ItemBuf(char *hasc, ITEM *item);
char *pta_strstr_ni(char *s1, char *s2, long ns1);


/**********************************************************************
PTA routines 
**********************************************************************/

/* functions moved to the pta code base from the old code base */
int vsPTAGetCookieHeader(char *cookie_str, char *cookieVal, int deleteIt);
int vsPTAAuthorizePost(hash_table_t *htable, ITEM key, ITEM *certItem,
                    char *pkcs7, client_data_t **newClientData);
int vsPTAAuthorizeCookie(hash_table_t *htable, char *hascKey, client_data_t **newClientData);

int ptaGetValToSign(int useMD5, char *hascToSign, char *hashOfToSign, ITEM *outHash);
client_data_t *vsPTAInitClientData();
  /*
void vsPTADestroyClientData(client_data_t *cd);
  */
/* call back function to clean up the data stored in hash table entry */
int vsPTADestroyClientData(void* data);
unsigned char *vsPTAGetISDigest(void *data);
char *vsPTAGetUserName(client_data_t *clientData);

int vsPTAGetJSForLogin(char *outBuf, char *hascToSign, char *hashOfToSign, 
                        char *reason, char *digestAlg);
int vsPTAGetJSForError(char *outBuf, char *certStatus, char *url);
int vsPTAGetRedirectPage(char *outBuf, char *url);
char *vsPTACertStatusString(int certStatus);


void vsPTAClearLoginVal(login_page_t *l);                                /* used - move */
int vsPTAReadLoginVal(char *filename, login_page_t *l);              /* used - move */

void vsPTAEatWhite(char *s);
int vsPTAParsePost(char **news, char *s, char *content_type);
int vsPTAIsAdmin(unsigned char *adminISDigest, unsigned char *certISDigest);


  /* still external ?? */
/* from util.c */
char *vs_strstr_ni(char *s1, char *s2, long ns1);


/**********************************************************************
globals this is actually in pta.c
**********************************************************************/
extern VS_PTA_CONFIG gCfg;


#ifdef __cplusplus
}
#endif
/* end of C wrapper for C++ */

#endif /*  _PTA_H_ */
