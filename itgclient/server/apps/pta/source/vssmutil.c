/*
 *	Utilities for PTA SiteMinder Authentication Scheme
 *      Author: Bin Zou
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#ifdef WIN32
#include <Windows.h>
#elif defined SOLARIS
#include <synch.h>
#else
#error WRONG PLATFORM
#endif
#include "pta_challenge_table.h"
#include "pta_challenge_token.h"
#include "pta_memory.h"
#include "pta.h"
#ifdef SOLARIS
/* Version Info */
#pragma ident "@(#)VeriSign PTA Authentication Scheme for Netegrity SiteMinder 1.0 2001/10/14"     
#endif
#define PTA_SM_SEMAPHORE "PTA_SM_SEMAPHORE"
#define PTA_LOG_SEMAPHORE "PTA_LOG_SEMAPHORE"
#define SAFETYLEN 10

#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

/* hash table for storing challenges*/
extern	PTA_CHALLENGE_TABLE ptaChallengeTable = {0};

/*handle to shared memory object*/
extern  HANDLE hMapObject = 0;

/* file handle for vsLogMessage */
extern  FILE *globalLogFP = 0;

/* semaphore handles*/
#ifdef WIN32
extern  HANDLE hLogSemaphore = 0;
extern 	HANDLE hSMSemaphore = 0;
#elif defined SOLARIS
extern  sema_t hLogSemaphore = {0};
extern  sema_t hSMSemaphore = {0};
#else 
#error WRONG PLATFORM
#endif

extern void vsLogMessage(void *handle, char *fmt, ...) {
	char infoBuf[PTA_LARGE_BUF_MAX];
	PTATIME currentTime;
	char *timeBuf = 0;
	va_list ap;

	if (!globalLogFP) return;

	va_start(ap, fmt);
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);
	pta_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	pta_make_newline_null(timeBuf);

#ifdef WIN32
	if (WaitForSingleObject(hLogSemaphore, INFINITE)==WAIT_OBJECT_0) {
#elif defined SOLARIS
        if(sema_wait(&hLogSemaphore) == 0) {
#else
#error WRONG PLATFORM 
#endif
		fprintf(globalLogFP, "[%s]  %s\n", timeBuf, infoBuf);

		fflush(globalLogFP);

#ifdef WIN32
		ReleaseSemaphore(hLogSemaphore,1,0);
#elif defined SOLARIS
                sema_post(&hLogSemaphore);
#else
#error WRONG PLATFORM
#endif
	}

	return;
}

/* this log function provide flexsibility to change what to log at run time */
extern void vsSmLogMessage(int logLevel,char  *fmt, ...) {
  char infoBuf[PTA_LARGE_BUF_MAX];
  va_list ap;
  if(logLevel <= gCfg.logInfo) {
	va_start(ap, fmt);
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);
        vsLogMessage(0,"%s", infoBuf); 
  }
}
extern void vsCfgLogMessage(char *fmt, ...) {
	char infoBuf[PTA_LARGE_BUF_MAX];
	PTATIME currentTime;
	char *timeBuf = 0;
	va_list ap;

	if (!globalLogFP) return;

	va_start(ap, fmt);
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);
	pta_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	pta_make_newline_null(timeBuf);

#ifdef WIN32
	if (WaitForSingleObject(hLogSemaphore, INFINITE)==WAIT_OBJECT_0) {
#elif defined SOLARIS
        if(sema_wait(&hLogSemaphore) == 0) {
#else
#error WRONG PLATFORM 
#endif
		fprintf(globalLogFP, "[%s]  %s\n", timeBuf, infoBuf);

		fflush(globalLogFP);

#ifdef WIN32
		ReleaseSemaphore(hLogSemaphore,1,0);
#elif defined SOLARIS
                sema_post(&hLogSemaphore);
#else
#error WRONG PLATFORM
#endif
	}

	return;
}
/* Get the next non-comment, non-blank line from the file. */
/* Not using one in val.dll since we can't pass a FILE pointer across dlls. */
char *nsscGetNextLine(char *lineBuf, int maxLen, FILE *fp) {

  char *rc = 0;
  int comment = 0;
  char tmpBuf[PTA_MAX_LINE_LENGTH];

  do {
    
    rc = fgets(lineBuf, maxLen, fp);
    
    if (lineBuf[0]=='#' || (sscanf(lineBuf, "%s", tmpBuf) <= 0)) comment = 1;
    else comment = 0;

  } while (rc && comment);

  return rc;
}

/* Take a line of name="value" options, and parse it into name and value. */
/* Reads from line_buf into name, value_buf.  All buffers must already be allocated. */
int vsGetNameValue(char *line_buf, char *name_buf, char *value_buf) {
  
  int status = 0;
  int quoted = 0;
  char *p, *q;

  do {
    name_buf[0] = value_buf[0] = '\0';

    /* 1. skip space 2. read until space,'=' */
    /* 3. skip space, '=','"' 4. read until space, or '"' if we got one earlier. */

    /* 1. */
    p = line_buf;
    while(*p && isspace(*p)) { p++; }

    /* 2. */
    q = name_buf;
    while(*p && !(isspace(*p) || *p=='=')) { *q = *p; q++; p++; }
    *q = '\0';

    /* 3. */
    while(*p && (isspace(*p) || *p=='=' || (*p=='\"' && quoted==0))) {
      if (*p=='\"') quoted = 1;
      p++; 
    }

    if (*p=='\0') {
      status = -1;
      break;
    }

    /* 4. */
    q = value_buf;
    while(*p && ((quoted && *p!='\"') || 
                 (!quoted && !(isspace(*p) || *p=='\r' || *p=='\n'))))
      { *q = *p; q++; p++; }

    *q = '\0';


  } while(0);

  return status;
}

/*
 * ptaGenAuthToken
 * generate a token encrypted by password
 */

int ptaGenAuthToken( char *hascToSign,  const char*   lpszSharedSecret) {
   unsigned char randomBytes[VSVAL_HASH_SHA1_LEN];
   unsigned char encodedChallengeData [PTA_TINY_BUF_MAX];
   int status;
   VSVAL_UserCtx ctx = {0};
   ITEM encodedChallengeToken = {0};
   PTATIME currentTime;
   PTA_CHALLENGE_TOKEN plaintextToken = {0};
   ITEM randomChallenge = {0};
   /* pre allocate buffer for the random challenge*/
   randomChallenge.data = randomBytes;
   randomChallenge.len = VSVAL_HASH_SHA1_LEN;
   encodedChallengeToken.data = encodedChallengeData;
   do {
      /* generate randomChallenge */
      if (status = VSVAL_GenerateRandomBytes(gCfg.vsValSDK, &ctx,  randomChallenge.data, randomChallenge.len))
        break;
      /* calculate expirationTime */
      pta_time(&currentTime); 
      plaintextToken.expirationTime = currentTime + gCfg.tokenTimeout;
      plaintextToken.randomChallenge = &randomChallenge;
      /* allocate the memory for encodedChallenge */
      encodedChallengeToken.len = VSVAL_HASH_SHA1_LEN+sizeof(PTATIME);
      status = VS_PTA_TOKEN_encode(lpszSharedSecret,&encodedChallengeToken,&plaintextToken);
      VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,encodedChallengeToken.data,encodedChallengeToken.len, hascToSign); 
      vsSmLogMessage(PTA_LOG_DEBUG_DETAIL,"DEBUG  ptaGenAuthToken: hascToSign : %s\n",hascToSign);
   } while (0); 
   return status;
}
/* 
 * isITEMequal(ITEM *item1, item *item2)
 * compare two items
 * return 1 if equal 0 otherwise
 */
int isITEMequal(ITEM *item1, ITEM *item2) {
   unsigned char *hascItem1;
   unsigned char *hascItem2;
   VSVAL_UserCtx ctx = {0};

   if(gCfg.logInfo>=PTA_LOG_DEBUG_DETAIL) {
	hascItem1 = (unsigned char*) sscT_malloc (2*item1->len+1);
	hascItem2 = (unsigned char*) sscT_malloc (2*item2->len+1);
	VSVAL_Bin2Hasc(gCfg.vsValSDK, &ctx, item1->data, item1->len, (char *)  hascItem1);
	vsSmLogMessage(PTA_LOG_DEBUG_DETAIL,"DEBUG: Compare item item1:%s",hascItem1);
	sscT_free( hascItem1);
	VSVAL_Bin2Hasc(gCfg.vsValSDK, &ctx, item2->data, item2->len, (char *)  hascItem2);
	vsSmLogMessage(PTA_LOG_DEBUG_DETAIL,"DEBUG: Compare item item2:%s",hascItem2);
	sscT_free( hascItem2);
   }
   if(item1->len == item2->len &&memcmp(item1->data,item2->data,item1->len) == 0 ) 
     return 1;
   else
     return 0;
}
/*
 *  ptaCompareHash
 *  compares the hash passed in against hash from the signature
 */
int ptaCompareHash(ITEM *decodedToSign,ITEM *outDigest)  {
  VSVAL_UserCtx ctx={0};
  int status = 0;
  int len;
  ITEM outHash = {0};
  /* allocate buffer */
  unsigned char outHashdata[VSVAL_HASH_SHA1_LEN + PTA_SIGNED_HEADER_LEN + VSVAL_BUF_MAX];
  unsigned char toSign[VSVAL_HASH_SHA1_LEN + PTA_SIGNED_HEADER_LEN + VSVAL_BUF_MAX], *p ;

  outHash.data = outHashdata; 

  /* compose toSign Value */
  /* Add the canned header. */
  memcpy(toSign, PTA_SIGNED_HEADER, PTA_SIGNED_HEADER_LEN);
  p = toSign + PTA_SIGNED_HEADER_LEN;
  /* add hex decoded toSign */
  memcpy(p,decodedToSign->data,decodedToSign->len);
  /* add hostname */
  memcpy(p + decodedToSign->len, gCfg.serverName, gCfg.serverNameLen);
  len = PTA_SIGNED_HEADER_LEN + decodedToSign->len +  gCfg.serverNameLen;
  /* get the hash of the toSign and compare with the hash from signature*/
  if (gCfg.useMD5) {
    VSVAL_HashMessage(gCfg.vsValSDK, &ctx, toSign, len, VSVAL_HASH_ALG_MD5, outHash.data,(int*)  &outHash.len);
    if( isITEMequal(&outHash,outDigest)) {
       status = VS_PTA_CT_CHALLENGE_VALID;
    } else {
       status = VS_PTA_TOKEN_SIGNATURE_NO_MATCH;
    }
  } else {
    VSVAL_HashMessage(gCfg.vsValSDK, &ctx,toSign, len, VSVAL_HASH_ALG_SHA1, outHash.data, (int*) &outHash.len);
    if( isITEMequal(&outHash,outDigest)) {
       status = VS_PTA_CT_CHALLENGE_VALID;
    } else {
       status = VS_PTA_TOKEN_SIGNATURE_NO_MATCH;
    }
  }
  return status;
      
}

/* 
 *  vsSmAuthRelease()
 *  This function is used to clean up shared memory and close Log files
 */
void vsSmAuthRelease() {
        vsSmLogMessage(PTA_LOG_INFO,"In vsSmAuthRelease to release resources"); 
	if (globalLogFP) { fclose(globalLogFP); globalLogFP = 0; }
	Pta_SM_free(hMapObject, ptaChallengeTable.m_ChallengePool);
	VSVAL_Final (gCfg.vsValSDK);
}

/* 
 * vsSmAuthInit
 * read from option files and setup all options
 */
int vsSmAuthInit(const char * lpszServerParam)
{
	int status = 0;
	char *errorString = "";
	char *adminIssuerSerialHasc = 0;
	unsigned int len = 0;
	VSVAL_UserCtx ctx = {0};
        unsigned char * m_SharedMemory;
	char *cfg_filename = 0;
	char *file_prefix =  0;
	char *url_prefix =   0;
	char *cache_dir =    0;
	char *defaultLdap = 0;
	char *httpProxy = 0;
	char *ldapHttpProxy = 0;
	char *ocspUrl = 0;
	char *logFileName = 0;
	int ldapTimeOut = PTA_LDAP_TIMEOUT;
	int randomBytes=0;
	int noCheckChain = 1;
	int len_SharedMemory;
	FILE *fp = 0;
	char line_buf[PTA_MAX_LINE_LENGTH];
	char name_buf[PTA_MAX_LINE_LENGTH], value_buf[PTA_MAX_LINE_LENGTH];
	char *read_status;
	int i, tableSize,hashLen;

	char valSDKErrorString[PTA_LARGE_BUF_MAX];

	/* set default Update seconds */
	gCfg.cvmUpdateSeconds = PTA_MAX_UPDATE_TIME;
	gCfg.absoluteTimeout = 60 * 60;
	gCfg.inactiveTimeout = 60 * 10;
	gCfg.tokenTimeout = 60 * 10;
	gCfg.garbageTime = 2 *  gCfg.absoluteTimeout;
	gCfg.hTableSize = 12;
        gCfg.logInfo = 0;
	/*gCfg.InfoLog = vsCfgLogMessage;*/
	gCfg.InfoLog = vsLogMessage;
    
        /* setup default value for siteminder failover support */
        gCfg.smSupportFailover = SM_SUPPORT_FAILOVER_DEFAULT_OPTION;
        gCfg.smMaxTriesForToken = SM_MAX_RETRIES_FOR_TOKEN;


        ctx.logFn = vsLogMessage;

	/* create semaphore for shared memopry and logging*/
#ifdef WIN32
	hSMSemaphore = CreateSemaphore(NULL,1,1,PTA_SM_SEMAPHORE);
	hLogSemaphore = CreateSemaphore(NULL,1,1,PTA_LOG_SEMAPHORE);
#elif defined SOLARIS
        sema_init(&hSMSemaphore, 1, USYNC_PROCESS, NULL);
        sema_init(&hLogSemaphore, 1, USYNC_PROCESS, NULL);
#else
#error WRONG PLATFORM
#endif
	
	do {

		/* get option file. */
		gCfg.optionFile = (char *) lpszServerParam;

		if (!(fp = fopen(gCfg.optionFile, "r"))) {
			status = VSVAL_ERR_CONFIG_OPEN;
			/*vsSmLogMessage(PTA_LOG_ERROR,"error open option file:%s\n",gCfg.optionFile);*/	
			break;
		}

		/* get sm-log-file first */
		do {

			if (read_status = nsscGetNextLine(line_buf, PTA_MAX_LINE_LENGTH, fp)) {      
				if (vsGetNameValue(line_buf, name_buf, value_buf)!=0) {
				  status = -1;
				  /*vsSmLogMessage(PTA_LOG_ERROR,"error reading option file\n");*/
				  break;
				}
				/* log-file-name */
				if(strcmp(name_buf,"sm-log-file") == 0) {
					logFileName  = sscT_strdup(value_buf);
					if ((globalLogFP = fopen(logFileName, "a"))==0) {
						status = VS_ERR_LOG_FILE;
					}
				}
                                /* log-info */
				if(strcmp(name_buf,"log-info") == 0) {
					gCfg.logInfo = atoi(value_buf);
                                }
                        }
		}  while (read_status != 0 && status==0);

		/*if there is no log file, fails the init function*/
		if(status == VS_ERR_LOG_FILE) {
			return VS_ERR_LOG_FILE;
		}
		
		/*initializ Validation sdk */
		if ((status = VSVAL_Init(&gCfg.vsValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
			vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_Init failed\n");
			/*tentatively no log if init failed*/
			break;
		}
		
		/*rewind the file for the rest of option files*/
		rewind(fp);

		/* Read the rest of the config file */
		do {

			if (read_status = nsscGetNextLine(line_buf, PTA_MAX_LINE_LENGTH, fp)) {      
				if (vsGetNameValue(line_buf, name_buf, value_buf)!=0) {
				  status = -1;
				  vsSmLogMessage(PTA_LOG_ERROR,"ERROR: reading option file\n");
				  break;
				}
                                vsSmLogMessage(PTA_LOG_INFO,"INFO: Reading option %s : %s\n",name_buf,value_buf);
				/* set random file */
				if(strcmp(name_buf,"random-file") == 0) {
					gCfg.randomFile = sscT_strdup(value_buf);
					if (gCfg.randomFile != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "random-file", gCfg.randomFile)) {
							status = -1;
							vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt random-file in \n");
							break;
						}
				}
			
				/* no-crl-checking */
				if(strcmp(name_buf,"no-crl-check") == 0) {
					gCfg.noCRLCheck = atoi(value_buf);
					vsSmLogMessage(PTA_LOG_INFO,"readed no-crl-check:%d \n",gCfg.noCRLCheck);
				}

				/* cfg file name */
				if(strcmp(name_buf,"cfg-filename") == 0) {
					cfg_filename = sscT_strdup(value_buf);
					vsSmLogMessage(PTA_LOG_INFO,"readed cfg-filename %s\n",cfg_filename);
				}
				/* file prefix */
				if(strcmp(name_buf,"file-prefix") == 0) {
					file_prefix = sscT_strdup(value_buf);
					if (file_prefix != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "file-prefix", file_prefix)) {
							status = -1;
							vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt file-prefix \n");
							break;
						}
				}

				/* url-prefix */
				if(strcmp(name_buf,"url-prefix") == 0) {
					url_prefix = sscT_strdup(value_buf);
					if (url_prefix != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "url-prefix", url_prefix)) {
							status = -1;
							vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt url-prefix \n");
							break;
						}
				}

				/* cache-dir */
				if(strcmp(name_buf,"cache-dir") == 0) {
					cache_dir = sscT_strdup(value_buf);
					if (cache_dir != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "cache_dir", cache_dir)) {
							status = -1;
							vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt cache_dir \n");
							break;
						}
				}

				/* http-proxy */
				if(strcmp(name_buf,"http-proxy") == 0) {
					httpProxy = sscT_strdup(value_buf);
					if (httpProxy != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "http-proxy", httpProxy)) {
							status = -1;
							vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt http-proxy \n");
							break;
						}
				}

				/* ldap-http-proxy */
				if(strcmp(name_buf,"ldap-http-proxy") == 0) {
					ldapHttpProxy = sscT_strdup(value_buf);
					if (ldapHttpProxy != 0)
						if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy)) {
							status = -1;
						    vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_SetOpt ldap-http-proxy \n");
							break;
						}
				}

				/* ldap-timeout */
				if(strcmp(name_buf,"ldap-timeout") == 0) {
					ldapTimeOut = atoi(value_buf);
				}
				/* ocsp-url */
				if(strcmp(name_buf,"ocsp-url") == 0) {
					ocspUrl = sscT_strdup(value_buf);
				}
				/* default-ldap */
				if(strcmp(name_buf,"default-ldap") == 0) {
					defaultLdap = sscT_strdup(value_buf);
				}
				/* no-check-chain */
				if(strcmp(name_buf,"no-check-chain") == 0) {
					noCheckChain = atoi(value_buf);
				}
				/* log-security */
				if(strcmp(name_buf,"log-security") == 0) {
					gCfg.cvmLogSecurity = atoi(value_buf);
					gCfg.logSecurity = atoi(value_buf);
				}
				/* update-seconds */
				if(strcmp(name_buf,"update-seconds") == 0) {
					gCfg.cvmUpdateSeconds = atoi(value_buf);
				}
				/* update-minutes */
				if(strcmp(name_buf,"update-minutes") == 0) {
					gCfg.cvmUpdateSeconds = 60 * atoi(value_buf);
				}

				/* update-hours */
				if(strcmp(name_buf,"update-hours") == 0) {
					gCfg.cvmUpdateSeconds = 60 * 60 * atoi(value_buf);
				}
				/* digest-alg */
				if(strcmp(name_buf,"digest-alg") == 0) {
					if(strcmp(value_buf,"MD5") == 0) 
					gCfg.useMD5 = 1;
				}
				/* admin-issuer-serial */
				if(strcmp(name_buf,"admin-issuer-serial") == 0) {
					adminIssuerSerialHasc = sscT_strdup(value_buf);
				}
				/* absolute-timeout */
				if(strcmp(name_buf,"absolute-timeout") == 0) {
					gCfg.absoluteTimeout = 60 * atoi(value_buf);
				}
				/* garbage-time */
				if(strcmp(name_buf,"garbage-time") == 0) {
					gCfg.garbageTime =60 *  atoi(value_buf);
				}
				/* inactive-timeout */
				if(strcmp(name_buf,"inactive-timeout") == 0) {
					gCfg.inactiveTimeout = 60 * atoi(value_buf);
				}
				/* inactive-timeout */
				if(strcmp(name_buf,"token-timeout") == 0) {
					gCfg.tokenTimeout = 60 * atoi(value_buf);
				}
				/* server-name */
				if(strcmp(name_buf,"server-name") == 0) {
					gCfg.serverName = sscT_strdup(value_buf);
				}
				/* sm-login-url */
				if(strcmp(name_buf,"sm-login-url") == 0) {
					gCfg.smLoginUrl = sscT_strdup(value_buf);
				}
				/* htable-size */
				if(strcmp(name_buf,"htable-size") == 0) {
					gCfg.hTableSize  = atoi(value_buf);
				}
                                /* sm-support-failover */
				if(strcmp(name_buf,"sm-support-failover") == 0) {
					gCfg.smSupportFailover = atoi(value_buf);
                                }
                                /* sm-max-tries-for-token */
				if(strcmp(name_buf,"sm-max-tries-for-token") == 0) {
					gCfg.smMaxTriesForToken = atoi(value_buf);
                                }
			}
      
		} while (read_status != 0 && status==0);

		if (fp) fclose(fp);   
    
		/* break out if status not 0*/
		if(status !=0)
			break;

		/* setup ldap-timeout in SDK */
		if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "ldap-timeout", ldapTimeOut))
			break;

		/* setup OCSP, Must be done AFTER proxy configuration */
		gCfg.checkOCSP = 0;
		if (ocspUrl != 0) {
		  if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ocsp-url", ocspUrl))
			break;	
		  gCfg.checkOCSP = 1;
		} 

		/* setup default ldap */
		if (defaultLdap !=0)
		  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", defaultLdap);
		else
		  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", "directory.verisign.com");
		if (status != 0)
		  break;

		/*no check chain */
		if (noCheckChain) {
		  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "on");
		  gCfg.cvmCheckChain = 0;
		} else {
		  gCfg.cvmCheckChain = 1;
		  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "off");
		}

		if (!cfg_filename || !file_prefix || !url_prefix || !cache_dir) {
		  status = VS_ERR_OPTION_FILE;
		  break;
		}
		/* check params... make sure there's a trailing / */
		if (status = VSVAL_ReadConfigFile(gCfg.vsValSDK, &ctx, cfg_filename)) {
                        vsSmLogMessage(PTA_LOG_ERROR,"Error Reading Config file: %s \n", cfg_filename);
			break;
		}
                vsSmLogMessage(0,"INFO: Reading Config file: %s OK\n",cfg_filename);
		/* Leave this null if not specified. */
		if (adminIssuerSerialHasc) {
		  VSVAL_StrToLower(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc); /* same upper/lowercase as bin2hasc. */
		  if (VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc, gCfg.adminIssuerSerial, &len)) {
			status = VS_ERR_ADMIN_HASC;
			break;
		  }
		}

		/*set absoluteTimeout for sdk */
		if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "absolute-timeout", gCfg.absoluteTimeout/60)){
                        vsSmLogMessage(PTA_LOG_ERROR,"ERROR: set absoluteTimeout for sdk\n");
			break;
                }
                vsSmLogMessage(PTA_LOG_INFO,"INFO: set absoluteTimeout for OK\n");

		/* Defaults to 2x absolute timeout. */
		if(gCfg.garbageTime <  (2 * gCfg.absoluteTimeout)) {
		  gCfg.garbageTime = 2 * gCfg.absoluteTimeout;
		}
		/*set garbageTime  for sdk */
		if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "garbage-time", gCfg.garbageTime/60)){
                        vsSmLogMessage(PTA_LOG_ERROR,"ERROR: set garbageTime for sdk\n");
			break;
                }
                vsSmLogMessage(0,"INFO: set garbageTime for OK\n");

		/* server-name fqdn. Prevents man-in-the-middle attacks. */
		if (!gCfg.serverName) {
		  status = VS_ERR_MISSING_CONFIG_VAL;
                  vsSmLogMessage(PTA_LOG_ERROR,"ERROR: missing server name\n");
		  break;
		} else {
                  vsSmLogMessage(0,"INFO: server name len %d\n", strlen(gCfg.serverName));
		  VSVAL_StrToLower(gCfg.vsValSDK, &ctx, gCfg.serverName);
		  gCfg.serverNameLen = strlen(gCfg.serverName);
                  vsSmLogMessage(PTA_LOG_DEBUG,"INFO: server name len %d\n", gCfg.serverNameLen);
		  if (gCfg.serverNameLen >= PTA_SMALL_BUF_MAX) {
                        vsSmLogMessage(PTA_LOG_ERROR,"ERROR: error server name length\n");
			status = VS_ERR_SERVER_NAME;
			break;
		  }
                  vsSmLogMessage(0,"INFO: set server name length  OK\n");
		  if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "server-name", gCfg.serverName)) {
                        vsSmLogMessage(PTA_LOG_ERROR,"ERROR:  VSVAL_SetOpt server-name \n");
			break;
                  }

                  vsSmLogMessage(0,"INFO: VSVAL_SetOpt set server name OK\n");
		}
                vsSmLogMessage(PTA_LOG_DEBUG,"INFO: set server name  OK\n");

		/* Make our hash table. 
		 * this does not work for multiprocess using PTA_CM_TABLE instead 
		 * VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, gCfg.hTableSize, 
	         *			(VSVAL_pFnHashDestroy)vsPTADestroyClientData , 
		 *		(VSVAL_pFnHashGetISDigest)vsPTAGetISDigest);
		 */
	        for (i=0, tableSize = 1; i<gCfg.hTableSize; i++) {
			tableSize *= 2;
		}
                /*
                 * deriving hash length used in the Challenge Table
                 * in case of support failover, we always store random bytes of VSVAL_HASH_SHA1_LEN
                 */ 
                if(gCfg.useMD5 && !gCfg.smSupportFailover) {
		 	hashLen = VSVAL_HASH_MD5_LEN;
		} else {
			hashLen = VSVAL_HASH_SHA1_LEN;
		}
                 
                vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: Before Allocate Memory for challenge table OK\n");
		len_SharedMemory = tableSize*(hashLen +1+ sizeof(PTATIME))+SAFETYLEN;
		m_SharedMemory = Pta_SM_malloc(len_SharedMemory, &hMapObject,gCfg.optionFile); 
                if(m_SharedMemory == 0) {
                     status = 1; /* tempery value later to be changed*/
		     vsSmLogMessage(PTA_LOG_ERROR,"ERROR: Pta_SM_malloc, memory allocation failed \n");
                     break;
                }
                vsSmLogMessage(PTA_LOG_INFO,"INFO: Allocate Memory for challenge table OK\n");

		if(Pta_CT_Init(&ptaChallengeTable, m_SharedMemory,len_SharedMemory,hashLen, gCfg.hTableSize) ==VS_PTA_CT_INIT_ERROR) {
                    status = 1; /* tempery value later to be changed*/
		    vsSmLogMessage(PTA_LOG_ERROR,"Pta_CT_Init, failed to initialize challenge table %d\n",VS_PTA_CT_INIT_ERROR);
                    break;
                }
                vsSmLogMessage(PTA_LOG_INFO,"INFO: Initialize challenge table OK\n");
	} while (0);


	if (status != 0) {
	  if ( status > VS_ERR_BASE && status < VS_ERR_MAX ) {
		sscErrorString(&errorString, status);
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthINIT :%s",errorString);		
	  } else if (status > VSVAL_ERR_BASE && status < VSVAL_ERR_MAX) {
		VSVAL_ErrorString(gCfg.vsValSDK, valSDKErrorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthINIT :%s", valSDKErrorString);		
	  } else if (status > VS_PTA_CT_ERROR_BASE && status < VS_PTA_CT_MAX_ERROR) {
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthINIT [%d]:%s", status, Pta_CT_ErrorString(status));
          } else {  /* Otherwise errorString is already set. */			
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthINIT : Internal Error, Error Code %d",status);
          }
	} else {
		vsSmLogMessage(PTA_LOG_INFO,"INFO: vsSmAuthINIT Successful.");
	}

	return status;

}

int vsSmAuthQuery(char * buffer,const char*   lpszSharedSecret) {

	ITEM hashItem;
	char hascToSign[PTA_TINY_BUF_MAX], hashOfToSign[PTA_TINY_BUF_MAX];
    	unsigned char hashBuf[MAX_DIGEST_LEN];
	int rc = 0;
	PTATIME tm = 0;
	VSVAL_UserCtx ctx = {0};
	ctx.logFn = vsLogMessage;

        hashItem.data = hashBuf;
        hashItem.len = 0;

        /* get challenge */
        if(gCfg.smSupportFailover) {
            /* incase suport failover generate a encrpted hascToSign */
            ptaGenAuthToken(hascToSign,lpszSharedSecret);
	    vsSmLogMessage(PTA_LOG_DEBUG,"Support Failover\n");
	    vsSmLogMessage(PTA_LOG_DEBUG,"hascToSign:%s",hascToSign);
        } else {
           /* traditional toSign */
           if(ptaGetValToSign(gCfg.useMD5, hascToSign, hashOfToSign, &hashItem))
       		return VS_ERR_RANDOM;
	   vsSmLogMessage(PTA_LOG_DEBUG,"No Failover\n");
	   vsSmLogMessage(PTA_LOG_DEBUG,"hascToSign:%s\n",hascToSign);
	   vsSmLogMessage(PTA_LOG_DEBUG,"hashOfToSign:%s\n",hashOfToSign);

	   pta_time(&tm);
	   tm = tm + gCfg.inactiveTimeout;
	   vsSmLogMessage(PTA_LOG_DEBUG,"Token Expiration Time : %d\n",tm);
#ifdef WIN32
	   if (WaitForSingleObject(hSMSemaphore, INFINITE)==WAIT_OBJECT_0) {	
#elif defined SOLARIS   
           if(sema_wait(&hSMSemaphore) == 0) {
#else
#error
#endif
	   vsSmLogMessage(PTA_LOG_DEBUG,"got semaphore \n");
           if(gCfg.logInfo >= PTA_LOG_DEBUG_DETAIL) {
		Pta_CT_PrintTable(&ptaChallengeTable);
           }
	   if(Pta_CT_Insert( &ptaChallengeTable,hashItem, &tm) != VS_PTA_CT_OK) {
                vsSmLogMessage(PTA_LOG_ERROR,"Failed inserting entry into hash table");
		rc = VS_PTA_CT_EXCEEDED_SIZE;
	   }
	   vsSmLogMessage(PTA_LOG_DEBUG,"after insert challenge \n");
           if(gCfg.logInfo >= PTA_LOG_DEBUG_DETAIL) {
                Pta_CT_PrintTable(&ptaChallengeTable);
           }

#ifdef WIN32
		ReleaseSemaphore(hSMSemaphore,1,0);
#elif defined SOLARIS
                sema_post(&hSMSemaphore);
#else
#error WRONG PLATFORM
#endif
	   }

        }
        sprintf(buffer,"%s?toSign=%s&digestAlg=%s",gCfg.smLoginUrl,hascToSign,gCfg.useMD5 ? "MD5" : "SHA");
	vsSmLogMessage(PTA_LOG_DEBUG,"buffer:%s",buffer);
	return rc;

}

int vsSmAuthenticate(const char *postedToSign,const char * postedSignature,char * outBuffer, int maxBufferLen,const char*   lpszSharedSecret) {

	int status = 0, certStatus = 0, rc = 0;
	ITEM outDigest = {0}, outCert = {0}, postedItem = {0}, signatureITEM = {0},decodedToSign = {0}, challengeItem = {0};
        PTA_CHALLENGE_TOKEN challengeToken = {0};
	unsigned char * hascKey;
        unsigned char hashBuf[MAX_DIGEST_LEN];
        unsigned char decodedToSignData [VSVAL_BUF_MAX], challengeData[VSVAL_BUF_MAX];
	int algorithm;
	VSVAL_CertFields * certFields = 0;
	VSVAL_UserCtx ctx = {0};
	char valSDKErrorString[PTA_LARGE_BUF_MAX];
	char *errorString = "";
	ctx.logFn = vsLogMessage;
        /* allocate memory buffer */
        decodedToSign.data = decodedToSignData;
        challengeItem.data = challengeData;
        challengeToken.randomChallenge = &challengeItem;
	/* remove EOL of  posted data */
	signatureITEM.data = (unsigned char *) sscT_strdup(postedSignature);
	signatureITEM.len = strlen(postedSignature);
	removeEOL(&signatureITEM);
       
	vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: Signature:%s\n",(char*) signatureITEM.data);
	vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: postedToSign : %s : length : %d\n",(char*)  postedToSign,strlen(postedToSign));

	do {
		/* debase64 posted signature */
		status = VSVAL_DeBase64Alloc(gCfg.vsValSDK, &ctx, &postedItem.data, (int *) &postedItem.len, (char *) signatureITEM.data);
		if(status != 0) {
			vsSmLogMessage(PTA_LOG_ERROR,"ERROR: VSVAL_DeBase64Alloc failed, status=%d", status);
                        rc = -1;
			break;
		}
		sscT_free(signatureITEM.data);
		vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: postedItem.len:%d\n",postedItem.len);

		/* get the digest of the data */
		outDigest.data = hashBuf;
		outDigest.len = 0;
		/*preset certstatus*/
		certStatus = CS_VALID;
		if( gCfg.noCRLCheck ==1) {
			status = VSVAL_ParseDetachedPKCS7(gCfg.vsValSDK, &ctx, postedItem.data, postedItem.len, 
									 outDigest.data, (int *) &outDigest.len, &algorithm,
									 &outCert.data, (int *) &outCert.len, 0);
		} else {
			status = VSVAL_ParseDetachedPKCS7(gCfg.vsValSDK, &ctx, postedItem.data, postedItem.len, 
									 outDigest.data, (int *) &outDigest.len, &algorithm,
									 &outCert.data, (int *) &outCert.len, &certStatus);
		}
		if(status != 0) {
			vsSmLogMessage(PTA_LOG_ERROR,"Error: VSVAL_ParseDetachedPKCS7, status =%d",status);
			rc = -1;
			break;
		}

		status = VSVAL_ParseCert(gCfg.vsValSDK, &ctx,  &certFields, outCert.data, outCert.len);
        /* Note: Do we want to call VSVAL_FreeCertFields even if rc != 0? */
		if(status == 0) {
			strcpy(outBuffer,certFields->commonName);
			VSVAL_FreeCertFields(gCfg.vsValSDK, certFields);
		} else {
			rc = -1;
			break;
		}


		if(certStatus != CS_VALID) {
			if(gCfg.logSecurity == 1) {
				vsSmLogMessage(0,"SECURITY: Invalid digital ID, cn = %s, certstatus = %d (%s)",outBuffer,certStatus, vsPTACertStatusString(certStatus));
			}
                        /* in case of no fail over mode, delete challenge from the table */
                        if(!gCfg.smSupportFailover) {
			    Pta_CT_Delete( &ptaChallengeTable,outDigest);
                        }
			rc = -1;
			break;
		}


		vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: after ParseDetachedPKCS7,outDigest.len :%d:status:%d\n",outDigest.len,status);
                if(gCfg.logInfo>=PTA_LOG_DEBUG_DETAIL) {
			Pta_CT_PrintTable(&ptaChallengeTable);
		        hascKey = (unsigned char*) sscT_malloc (2*outDigest.len+1);
		        VSVAL_Bin2Hasc(gCfg.vsValSDK, &ctx, outDigest.data, outDigest.len, (char *) hascKey);
		        vsSmLogMessage(PTA_LOG_DEBUG_DETAIL,"DEBUG: hascKey:%s",hascKey);
		        sscT_free(hascKey);
                 }

	/* get semaphore first */
#ifdef WIN32
		if (WaitForSingleObject(hSMSemaphore, INFINITE)==WAIT_OBJECT_0) {	
#elif defined SOLARIS   
        if(sema_wait(&hSMSemaphore) == 0) {
#else
#error WRONG PLATFORM
#endif
                        if(gCfg.smSupportFailover) {
                        /* support failover */
                             /* get toSign */
                              /* if toSign is bigger than we expected, return error*/
                              if(strlen(postedToSign) >= (VSVAL_BUF_MAX)) {
                                 rc= -1;
                                 status = VS_PTA_TOKEN_SIGNATURE_NO_MATCH ;
                                 break; 
                              }
                              vsSmLogMessage(PTA_LOG_DEBUG,"hex decode toSign : len : %d : value : %s\n",strlen(postedToSign),postedToSign);
                              VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx, (char *) postedToSign,decodedToSign.data ,&decodedToSign.len); 
                              vsSmLogMessage(PTA_LOG_DEBUG,"decodedToSign size : %d\n",decodedToSign.len);
                              status = ptaCompareHash(&decodedToSign,&outDigest);
                              vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: ptaCompareHash: %d\n",status);
                              if(status !=  VS_PTA_CT_CHALLENGE_VALID) {
                                    rc = -1;
                                    break;
                              }
                              /* validate token */
                               VS_PTA_TOKEN_decode(lpszSharedSecret, &decodedToSign,&challengeToken); 
                               status = VS_PTA_TOKEN_validate(&challengeToken, &ptaChallengeTable,gCfg.smMaxTriesForToken); 
                               vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG: VS_PTA_TOKEN_validate : %d\n",status);
                               if(status ==  VS_PTA_TOKEN_VALID) {
                                   status = VS_PTA_CT_CHALLENGE_VALID; 
                               } 
                        } else {
                        /* in case failover is not supported check against challenge table*/
			     status = Pta_CT_ValidateChallenge( &ptaChallengeTable,outDigest);
			     vsSmLogMessage(PTA_LOG_DEBUG,"after Pta_CT_ValidateChallenge status=%d",status);
                        }
                        if(gCfg.logInfo>=PTA_LOG_DEBUG_DETAIL) {
			     Pta_CT_PrintTable(&ptaChallengeTable);
                        }
			if (status != VS_PTA_CT_CHALLENGE_VALID) {
				rc = -1;
				break;
			}
		}
			
	} while (0);

#ifdef WIN32
			ReleaseSemaphore(hSMSemaphore,1,0);
#elif defined SOLARIS
            sema_post(&hSMSemaphore);
#else
#error WRONG PLATFORM
#endif
        vsSmLogMessage(PTA_LOG_DEBUG,"DEBUG status : %d\n",status);
	if (status != 0 && status !=VS_PTA_CT_CHALLENGE_VALID ) 
	{
	  if ( status > VS_ERR_BASE && status < VS_ERR_MAX ) {
		sscErrorString(&errorString, status);
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthenticate [%d]:%s",status, errorString);		
	  } else if (status > VSVAL_ERR_BASE && status < VSVAL_ERR_MAX) {
		VSVAL_ErrorString(gCfg.vsValSDK, valSDKErrorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthenticate [%d]:%s", status, valSDKErrorString);		
	  } else if (status > VS_PTA_CT_ERROR_BASE && status < VS_PTA_CT_MAX_ERROR) {
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthenticate [%d]:%s", status, Pta_CT_ErrorString(status));
          } else {  
		vsSmLogMessage(PTA_LOG_ERROR,"ERROR: vsSmAuthenticate : Internal Error, Error Code - %d",status);
          }
	} else {
		if ( certStatus == CS_VALID )
		vsSmLogMessage(PTA_LOG_INFO,"INFO: vsSmAuthenticate Success, cn = %s", outBuffer);
	}

        VSVAL_Free(gCfg.vsValSDK, postedItem.data);
	VSVAL_Free(gCfg.vsValSDK, outCert.data);
	return rc;
}

#ifdef __cplusplus
}
#endif
