
#include <stdio.h>
#include <stdlib.h>

#if    defined (WIN32)
/* Begin Change : Fix for CR30756, Porting to Linux */
#elif  defined (SOLARIS) || defined(AIX)  || defined(LINUX)
/* End Change : Fix for CR30756, Porting to Linux */
#include <dlfcn.h> /* dlxxxx */
#elif  defined (HPUX)
#include <dl.h>    /* shl_xxx */
#else  Platform specific -D<arch> definition required
#error 
#endif

#include "time.h"
#include "nsapi.h"
#include <base/systhr.h>
#include "pta.h"
#include "cookie.h"
#include "escape.h"

/* we only use one func out of cdr. here's its definition. */
int VSUnwrapCertificate ( pblock *pb, Session *sn, Request *rq);

#define VS_FN_NAME_SSC_INIT    "vsSSCInit"
#define VS_FN_NAME_SSC_CHECK   "vsSSCCheck"
#define VS_FN_NAME_SSC_SEND    "vsSSCSend"
#define VS_FN_NAME_REFRESH "vsRefreshCRLs"

/* Critical section variable to protect the following globals */
CRITICAL vsLock = 0;
CRITICAL vsCvmLock = 0;

SYS_THREAD vsThread = 0;

/* Globals */
/* define this in ssc.c VS_SSC_CONFIG gCfg = { 0 }; */

/* Sets some values used by the info logger */
void vsSetGlobalFn(Session *sn, Request *rq, char *fnName) {
  gCfg.sn = sn;
  gCfg.rq = rq;
  gCfg.fnName = fnName;
}

void vsSetCvmGlobalFn(Session *sn, Request *rq, char *fnName) {
  gCfg.cvmSn = sn;
  gCfg.cvmRq = rq;
  gCfg.cvmFnName = fnName;
}

void vsGetGlobalFn(Session **sn, Request **rq, char **fnName) {
  *sn = gCfg.sn;
  *rq = gCfg.rq;
  *fnName = gCfg.fnName;
}

void vsGetCvmGlobalFn(Session **sn, Request **rq, char **fnName) {
  *sn = gCfg.cvmSn;
  *rq = gCfg.cvmRq;
  *fnName = gCfg.cvmFnName;
}

void vsLogInfoMessage(void* handle, char *fmt, ...) {

  char infoBuf[PTA_MAX_LINE_LENGTH];
  va_list ap;
  va_start(ap, fmt);

  (void) vsprintf(infoBuf, fmt, ap);
  va_end(ap);

  log_error(LOG_INFORM, gCfg.fnName, gCfg.sn, gCfg.rq, "%s", infoBuf);

  return;
}

void vsCvmLogInfoMessage(void* handle, char *fmt, ...) {

  char infoBuf[PTA_MAX_LINE_LENGTH];
  va_list ap;
  va_start(ap, fmt);

  (void) vsprintf(infoBuf, fmt, ap);
  va_end(ap);

  log_error(LOG_INFORM, gCfg.cvmFnName, gCfg.cvmSn, gCfg.cvmRq, "%s", infoBuf);

  return;
}


/* Find an integer value in a pblock, if it isn't there, return the default val. */
int vs_pblock_findint(const char *name, pblock *pb, int defaultVal) {
  
  char *value = 0;
  int intVal;

  value = pblock_findval(name, pb);

  if (value) { intVal = atoi(value); }
  else { intVal = defaultVal; }

  return intVal;
}


/* See if a pblock named attribute is set to on. */
int vs_pblock_ison(const char *name, pblock *pb) {
  
  char *value = 0;

  value = pblock_findval(name, pb);

  return ptaCfgStringIsOn(value);
}

/* Gets the value returned from a pblock, checks for NULL or strlen()==0 */
char *vs_pblock_findstr(const char *name, pblock *pb, char **value) {
  
  char *val = 0;

  val = pblock_findval(name, pb);

  if (val && val[0]) {
    return (*value = val);
  }

  return 0;
}


/* returns true if name==value in pb. */
int vs_pblock_findmatch(const char *name, pblock *pb, char *value) {
  
  char *tmp = 0;

  if (vs_pblock_findstr(name, pb, &tmp)) {
    if (strcmp(tmp, value)==0) return 1;
  }
  
  return 0;
}


/* similar to pblock_nvinsert, but removes existing values first. */
pb_param *vs_pblock_nvreplace(const char *name, const char *value, pblock *pb) {

  pb_param *removedBlock = 0;

  removedBlock = pblock_remove(name, pb);

  if (removedBlock) {
    param_free(removedBlock);
  }

  return pblock_nvinsert(name, value, pb);

}


int testDump(pblock *pb, Session *sn, Request *rq) {

  char *pbStr;

  pbStr = pblock_pblock2str(rq->reqpb, 0);
  log_error(LOG_INFORM, "testDump", sn, rq, "rq->reqpb: %s", pbStr);
  FREE(pbStr);

  pbStr = pblock_pblock2str(rq->headers, 0);
  log_error(LOG_INFORM, "testDump", sn, rq, "rq->headers: %s", pbStr);
  FREE(pbStr);

  pbStr = pblock_pblock2str(sn->client, 0);
  log_error(LOG_INFORM, "testDump", sn, rq, "sn->client: %s", pbStr);
  FREE(pbStr);

  return 0;
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

/* Read a file of name=value options and place them all in a pblock. */
int vsAddOptionsToPblock(char *optionFile, pblock *pb) {

  int status = 0;
  
  FILE *fp = 0;
  char line_buf[PTA_MAX_LINE_LENGTH];
  char name_buf[PTA_MAX_LINE_LENGTH], value_buf[PTA_MAX_LINE_LENGTH];
  char *read_status;

  do {

    if (!(fp = fopen(optionFile, "r"))) {
      status = VSVAL_ERR_CONFIG_OPEN;
      break;
    }

    /* Read the config file */
    do {

      if (read_status = nsscGetNextLine(line_buf, PTA_MAX_LINE_LENGTH, fp)) {
        
        if (vsGetNameValue(line_buf, name_buf, value_buf)!=0) {
          status = -1;
          break;
        }
        vs_pblock_nvreplace(name_buf, value_buf, pb);
      }
      
    } while (read_status != 0 && status==0);


  } while (0);

  if (fp) fclose(fp);

  return status;
}


/* pass it cookieVal in hasc. */
int setCookie(Request *rq, char *cookieVal, int delete) {
  char cookie_str[PTA_LARGE_BUF_MAX];

  vsPTAGetCookieHeader(cookie_str, cookieVal, delete);

  pblock_nvinsert("set-cookie", cookie_str, rq->srvhdrs);

  return 0;
}

/* 0 if ok (does not mean we found it) */
/* value (or null) in *cookieVal. *cookieVal can't be freed. */
int findMyCookie(Request *rq, char **cookieVal) {

  int status = 0;
  pblock *cookiePb = 0;
  char *s;

  do {

    *cookieVal = 0;

    cookiePb = get_cookie_pblock(rq);

    if (cookiePb) {
      if (vs_pblock_findstr(gCfg.cookieName, cookiePb, &s)) {
#ifdef DEBUGMSG
        gCfg.InfoLog(0, "%s=%s", gCfg.cookieName, s);
#endif
        *cookieVal = s;
      }

    }

  } while (0);

  if (cookiePb) { pblock_free(cookiePb); }

  return status;
}

void printCookies(Request *rq) {

  char *cookie;

  cookie = pblock_findval("cookie", rq->headers);

#ifdef DEBUGMSG
  if (cookie==0){
    gCfg.InfoLog(0, "No cookies");
  }
  else {
    gCfg.InfoLog(0, "cookies=%s", cookie);
  }
#endif
}



void vsSleeperThread(void *ptr) {
  
  PTATIME currentTime = 0;
  Session *oldSN = 0;
  Request *oldRQ = 0;
  char *oldFnName = 0;
  int refreshStatus = 0;
  char *refreshStatusString = 0;

  VSVAL_UserCtx ctx = {0};

  char buf[PTA_LARGE_BUF_MAX];

  ctx.logFn = vsCvmLogInfoMessage;

  while (1) {

    /* acquire the critical section lock */
    crit_enter(vsCvmLock);
	

    /* Remember the existing error logging info. */	
    vsGetCvmGlobalFn(&oldSN, &oldRQ, &oldFnName);
    vsSetCvmGlobalFn(0, 0, VS_FN_NAME_REFRESH);

	/* vsCvmLogInfoMessage (0, "Waking up...");*/
	
    /* See if we have to update all the CRLs based on timer. */
    pta_time(&currentTime);
    if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {

      gCfg.cvmLastUpdate = currentTime;

    
      /* Re-get all CRLs. */
	  if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
			/* Ignore errors, but print an error message. */
			log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, 
                  "Problems acquiring CRLs. Some not installed.");
			/* Also print the last error's cause. */
			if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
			     sprintf (buf, "Error Code : %d", refreshStatus);
			}
	       log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, buf);
      }
    }

    /* Put the old error logging info back. */
    vsSetCvmGlobalFn(oldSN, oldRQ, oldFnName);

    /* release the lock */
    crit_exit(vsCvmLock);

    /* Make sure the sleep is outside the critical section! */
    systhread_sleep(gCfg.cvmUpdateSeconds * 334); /* Sleep 1/3 update time. In ms. */
  }
  
}



NSAPI_PUBLIC void vsSSCCleanup(void *param)
{
  
  VSVAL_UserCtx ctx = {0};

  crit_terminate(vsLock);
  vsLock = NULL;
  crit_terminate(vsCvmLock);
  vsCvmLock = NULL;
  ctx.logFn = gCfg.InfoLog;

#ifdef DEBUGMSG
  VSVAL_HashTablePrint(gCfg.vsValSDK, &ctx, gCfg.hTable);
#endif

  VSVAL_HashDestroy(gCfg.vsValSDK, &ctx, gCfg.hTable);
  gCfg.hTable = 0;

  if (vsThread) { systhread_terminate(vsThread); }

  /* Call the user final fn */
  if (gCfg.dlFinal) { (*gCfg.dlFinal) (); }

  /* Unload the user's authorization plugin. */
#if   defined (WIN32)
  if (gCfg.dlHandle) { FreeLibrary(gCfg.dlHandle); }
#elif defined (SOLARIS)
  if (gCfg.dlHandle) { dlclose(gCfg.dlHandle); }
#elif defined (HPUX)
  if (gCfg.dlHandle) { shl_unload(gCfg.dlHandle); }
#endif
  /*
  if (gCfg.randObj) { vsDestroyRandom(&gCfg.randObj); }
  */

  sscT_free((unsigned char *) gCfg.cookieName);

  vsPTAClearLoginVal(& gCfg.loginValueMS);
  vsPTAClearLoginVal(& gCfg.loginValueNS);
  VSVAL_Final (gCfg.vsValSDK);
}

/* Pre-declare this fn so we can use a pointer to it. */
int vsNsapiGetRevocationInfo(ITEM *certItem, int *certStatus,
                             PTATIME *statusExpires, char **userName);

/* Main entry for crl checking. */
NSAPI_PUBLIC int vsSSCInit(pblock *pb, Session *sn, Request *rq)
{
  int status = 0, pluginStatus = 0;
  char *errorString = "";
  char *cookieName = 0;
  char *adminIssuerSerialHasc = 0, *pbStr = 0;
  unsigned int len = 0;
  int volatile x = 0;
  VSVAL_UserCtx ctx = {0};

  char *cfg_filename = 0;
  char *file_prefix =  0;
  char *url_prefix =   0;
  char *cache_dir =    0;
  char *intString = 0;
  char *defaultLdap = 0;
  char *httpProxy = 0;
  char *ldapHttpProxy = 0;
  char *ocspUrl = 0;
  int ldapTimeOut = 0;
  int randomBytes=0;

  char valSDKErrorString[PTA_LARGE_BUF_MAX];

  vsSetGlobalFn(sn, rq, VS_FN_NAME_SSC_INIT);

  do {

    /* Make a critical variable */
    vsLock = crit_init();
    vsCvmLock = crit_init();
    /* and register its cleanup function */
    daemon_atrestart(vsSSCCleanup, NULL);

    /* Read NSAPI options from obj.conf */

    /* SETUP THE INFO LOGGER AS THE FIRST THING WE DO!!! */
    if (vs_pblock_ison("log-info", pb)) {
		gCfg.InfoLog = vsLogInfoMessage;		
	}
    else {
		gCfg.InfoLog = vsNullLogInfoMessage;
	}
	ctx.logFn = gCfg.InfoLog;

    if (vs_pblock_ison("debug-wait", pb)) x=1;
    while(x);

    /* Read more options from a file. */
    gCfg.optionFile = pblock_findval("option-file", pb); /* null ok. */
    if (gCfg.optionFile) {
      if (vsAddOptionsToPblock(gCfg.optionFile, pb)) {
        status = VS_ERR_OPTION_FILE;
        break;
      }
    }

    /* SETUP THE INFO LOGGER need to redo this if log-info set in config file !!! */
    if (vs_pblock_ison("log-info", pb)) {
		gCfg.InfoLog = vsLogInfoMessage;		
	}
    else {
		gCfg.InfoLog = vsNullLogInfoMessage;
	}
	ctx.logFn = gCfg.InfoLog;
    
    if ((status = VSVAL_Init(&gCfg.vsValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
      break;
    }


	/* Set up our revocation callback. */
    gCfg.fnGetRevocationInfo = vsNsapiGetRevocationInfo;

    gCfg.randomFile = pblock_findval("random-file", pb); /* null ok. */
    if (gCfg.randomFile != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "random-file", gCfg.randomFile))
		break;


    gCfg.noCRLCheck = vs_pblock_ison("no-crl-check", pb);

    
    /* Read NSAPI options from obj.conf */
    cfg_filename = pblock_findval("cfg-filename", pb);

    file_prefix = pblock_findval("file-prefix", pb);
    if (file_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "file-prefix", file_prefix))
		break;
	  
	url_prefix =  pblock_findval("url-prefix", pb);
    if (url_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "url-prefix", url_prefix))
		break;

	cache_dir = pblock_findval("cache-dir", pb);
    if (cache_dir != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "cache_dir", cache_dir))
		break;

    
	httpProxy = pblock_findval("http-proxy", pb);
    if (httpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "http-proxy", httpProxy))
		break;

	ldapHttpProxy = pblock_findval("ldap-http-proxy", pb);
    if (ldapHttpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy))
		break;


    if (intString = pblock_findval("ldap-timeout", pb)) {
      ldapTimeOut = atoi(intString);
    }
    else {
      ldapTimeOut = PTA_LDAP_TIMEOUT;
    }
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "ldap-timeout", ldapTimeOut))
		break;

    /* Must be done AFTER proxy configuration */
    ocspUrl = pblock_findval("ocsp-url", pb);
	gCfg.checkOCSP = 0;
    if (ocspUrl != 0) {
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ocsp-url", ocspUrl))
		break;	
	  gCfg.checkOCSP = 1;
	} 

	defaultLdap = pblock_findval("default-ldap", pb);
    if (defaultLdap !=0)
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", defaultLdap);
    else
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", "directory.verisign.com");
    if (status != 0)
      break;

    if (vs_pblock_ison("no-check-chain", pb)) {
	  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "on");
      gCfg.cvmCheckChain = 0;
    } else {
	  gCfg.cvmCheckChain = 1;
	  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "off");
	}

    if (vs_pblock_ison("log-security", pb)) {
      gCfg.cvmLogSecurity = 1;
      gCfg.logSecurity = 1;
    }

    /* get CRL update frequency. */
    if (intString = pblock_findval("update-seconds", pb)) {	  
      gCfg.cvmUpdateSeconds = atoi(intString);	  
    }
    else if (intString = pblock_findval("update-minutes", pb)) {
      gCfg.cvmUpdateSeconds = 60 * atoi(intString);
    }
    else if (intString = pblock_findval("update-hours", pb)) {
      gCfg.cvmUpdateSeconds = 60 * 60 * atoi(intString);
    }
    else {
      gCfg.cvmUpdateSeconds = PTA_MAX_UPDATE_TIME;
    }

	if ( gCfg.cvmUpdateSeconds == 0) {
		status = VS_ERR_INVALID_UPDATE_HOURS;
		break;
	}

    if (!cfg_filename || !file_prefix || !cache_dir || (!url_prefix && !ocspUrl)) {
      status = VSVAL_ERR_OBJ_CONF;
      break;
    }

    /* check params... make sure there's a trailing / */
    if (status = VSVAL_ReadConfigFile(gCfg.vsValSDK, &ctx, cfg_filename)) {
		break;
	}

    /* Start a thread to do the timer-based CRL updates. */
    if (gCfg.cvmUpdateSeconds < PTA_MAX_UPDATE_TIME) {
      if ((vsThread = systhread_start(0, 0, vsSleeperThread, 0))==SYS_THREAD_ERROR) {
        status = VSVAL_ERR_THREAD;
        break;
      } 	  
    }


    /* leave this null if not specified. */
    gCfg.shlibName = pblock_findval("shlib-name", pb);

    if (gCfg.shlibName) {
      /* Load the user's authorization plugin. */

#if   defined (WIN32)
      gCfg.dlHandle = LoadLibrary(gCfg.shlibName);
#elif defined (SOLARIS)
      /* Don't do RTLD_LAZY, so we find missing symbols right away. */
      gCfg.dlHandle = dlopen(gCfg.shlibName, RTLD_NOW);
#elif defined (HPUX)
      gCfg.dlHandle = shl_load(gCfg.shlibName, BIND_IMMEDIATE, 0L);
#endif

      if (gCfg.dlHandle==0) {
        status = VS_ERR_SHLIB;
        break;
      }

      /* find the address of function and data objects */
#if   defined (WIN32)
      gCfg.dlInit  = (pFnInit)  GetProcAddress(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) GetProcAddress(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) GetProcAddress(gCfg.dlHandle, "SscFinal");
#elif defined (SOLARIS)
      gCfg.dlInit  = (pFnInit)  dlsym(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) dlsym(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) dlsym(gCfg.dlHandle, "SscFinal");
#elif defined (HPUX)
      shl_findsym(gCfg.dlHandle, "SscInit",  TYPE_PROCEDURE, &gCfg.dlInit);
      shl_findsym(gCfg.dlHandle, "SscCheck", TYPE_PROCEDURE, &gCfg.dlCheck);
      shl_findsym(gCfg.dlHandle, "SscFinal", TYPE_PROCEDURE, &gCfg.dlFinal);
#endif
    }

    /* MD5 or SHA1? */
    if (vs_pblock_findmatch("digest-alg", pb, "MD5")) { gCfg.useMD5 = 1; }

    /* Leave this null if not specified. */
    adminIssuerSerialHasc = pblock_findval("admin-issuer-serial", pb);
    if (adminIssuerSerialHasc) {
      VSVAL_StrToLower(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc); /* same upper/lowercase as bin2hasc. */
      if (VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc, gCfg.adminIssuerSerial, &len)) {
/*      if (ptaHasc2BinBuf(adminIssuerSerialHasc, gCfg.adminIssuerSerial, &len)) {*/
        status = VS_ERR_ADMIN_HASC;
        break;
      }
    }

    gCfg.addEnvVars = vs_pblock_ison("add-env-vars", pb);
    gCfg.addJSVars = vs_pblock_ison("add-js-vars", pb);

    /* this may not do what we want. */
    gCfg.addErrorJSVars = vs_pblock_ison("add-error-js-vars", pb);


    /* Optional memory saving optimization. Requires login on CRL expiration. */
    gCfg.noSaveCerts = vs_pblock_ison("no-save-certs", pb);
    if (gCfg.noSaveCerts && (gCfg.addEnvVars || gCfg.addJSVars)) {
      status = VS_ERR_NO_SAVE_CERTS;
      break;
    }
    gCfg.savePkcs7 = vs_pblock_ison("save-pkcs7", pb);
    
    gCfg.protectJavaDirs = vs_pblock_ison("protect-java-dirs", pb);

    /* Debugging only !!! */
    gCfg.signText = vs_pblock_ison("sign-text", pb);
    gCfg.signCanned = 1;
    gCfg.noSSL = vs_pblock_ison("no-ssl", pb);


    /* Set timeouts. */
    gCfg.absoluteTimeout = 
      60 * vs_pblock_findint("absolute-timeout", pb, 60); /* 1 hr. */
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "absolute-timeout", gCfg.absoluteTimeout/60))
		break;

    gCfg.inactiveTimeout = 
      60 * vs_pblock_findint("inactive-timeout", pb, 10); /* 10 min. */

    /* Defaults to 2x absolute timeout. */
    gCfg.garbageTime = 
      60 * vs_pblock_findint("garbage-time", pb, (2 * gCfg.absoluteTimeout) / 60);
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "garbage-time", gCfg.garbageTime/60))
		break;

    /* login/error pages. */
    if (vs_pblock_findstr("login-page-ms", pb, &(gCfg.loginPageMS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_pblock_findstr("login-page-ns", pb, &(gCfg.loginPageNS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_pblock_findstr("error-url", pb, &(gCfg.errorUrl))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_pblock_findstr("logout-url", pb, &(gCfg.logoutUrl))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }

    /* server-name fqdn. Prevents man-in-the-middle attacks. */
    if (vs_pblock_findstr("server-name", pb, &(gCfg.serverName))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    else {
      VSVAL_StrToLower(gCfg.vsValSDK, &ctx, gCfg.serverName);
      gCfg.serverNameLen = strlen(gCfg.serverName);
      if (gCfg.serverNameLen >= PTA_SMALL_BUF_MAX) {
        status = VS_ERR_SERVER_NAME;
        break;
      }
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "server-name", gCfg.serverName))
		break;

    }

    gCfg.noCacheLogin = vs_pblock_ison("no-cache-login", pb);

    gCfg.noCachePages = vs_pblock_ison("no-cache-pages", pb);

    if (status = vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) {
      break;
    }
    if (status = vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) {
      break;
    }

    /* Cookie name/domain. */
    cookieName = pblock_findval("cookie-name", pb);

    if ((gCfg.cookieName = (char *) sscT_malloc(PTA_LARGE_BUF_MAX))==0) {
      status = VS_ERR_NO_MEM;
      break;
    }

    if (cookieName) { sprintf(gCfg.cookieName, "%s", cookieName); }
    else {

      VSVAL_GenerateRandomBytes (gCfg.vsValSDK, &ctx, (unsigned char*)&randomBytes, sizeof(int));
      sprintf(gCfg.cookieName, "VeriSignPTA%d", randomBytes);
      
      /* Can't specify cookie-domain w/o a cookie-name. */
      /* How would all the servers pick the same random id? */
      if (pblock_findval("cookie-domain", pb)) {
        status = VS_ERR_COOKIE_DOMAIN;
        break;
      }
    }

    gCfg.cookieDomain = pblock_findval("cookie-domain", pb); /* null if not there. */

    /* Make our hash table. */
    if (pblock_findval("htable-size", pb)) {
      VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, atoi(pblock_findval("htable-size", pb)), (VSVAL_pFnHashDestroy)vsPTADestroyClientData , (VSVAL_pFnHashGetISDigest)vsPTAGetISDigest);
      gCfg.hTableSize = atoi(pblock_findval("htable-size", pb));
    }
    else { 
      VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, 12, (VSVAL_pFnHashDestroy)vsPTADestroyClientData , (VSVAL_pFnHashGetISDigest)vsPTAGetISDigest); 
      gCfg.hTableSize = 12;
    }


    /* Call the user init fn */
    if (gCfg.dlInit) {

      pbStr = pblock_pblock2str(pb, 0);
      pluginStatus = (*gCfg.dlInit) (VS_PTA_PLUGIN_DESC, pbStr ? pbStr : "");
      FREE(pbStr);

      if (pluginStatus) {
        status = VS_ERR_PLUGIN_INIT;
        break;
      }
    }

    /* Print a startup message. */
    gCfg.InfoLog(0, "%s starting", VS_PTA_PLUGIN_DESC);
 
  } while (0);

  if (status) {
    
	  if ( status > VS_ERR_BASE && status < VS_ERR_MAX ) {
		sscErrorString(&errorString, status);
		pblock_nvinsert("error", errorString, pb);
		log_error(LOG_FAILURE, VS_FN_NAME_SSC_INIT, sn, rq, "%s", errorString);		
	  }
	  else
		if (status > VSVAL_ERR_BASE && status < VSVAL_ERR_MAX) {
			VSVAL_ErrorString(gCfg.vsValSDK, valSDKErrorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
			pblock_nvinsert("error", valSDKErrorString, pb);
			log_error(LOG_FAILURE, VS_FN_NAME_SSC_INIT, sn, rq, "%s", valSDKErrorString);		
		}
		else {  /* Otherwise errorString is already set. */			
			pblock_nvinsert("error", errorString, pb);
			log_error(LOG_FAILURE, VS_FN_NAME_SSC_INIT, sn, rq, "%s", errorString);
		}
  }
  
  if (status) return REQ_ABORTED;
  else return REQ_PROCEED;

}


int vsSetGETUrl(char *url, Session *sn, Request *rq) {

  char buf[PTA_LARGE_BUF_MAX];

  sprintf(buf, "GET %s %s", url, pblock_findval("protocol", rq->reqpb));

  vs_pblock_nvreplace("uri", url, rq->reqpb);
  vs_pblock_nvreplace("method", "GET", rq->reqpb);
  pblock_remove("content-length", rq->headers);
  pblock_remove("content-type", rq->headers);
  vs_pblock_nvreplace("clf-request", buf, rq->reqpb);

  return 0;
}

/* sscT_malloc()'s into outITEMs, outPKCS7. */
int vsGetPostedData(char **outPKCS7, ITEM *outDigest, ITEM *outCert, 
                    Session *sn, Request *rq)
{
  int status = 0, tmpStatus;
  char *lenStr, *method;
  int freeBytes = 0, toRead, iChar;
  int algorithm;
  char *b64Str, *typeStr;
  ITEM b64Item = {0}, postedItem = {0};

  VSVAL_UserCtx ctx = {0};

  ctx.logFn = gCfg.InfoLog;

  do {

    method = pblock_findval("method", rq->reqpb);
    if (method==0 || strcmp(method, "POST")!=0) {
      status = -1;
      break;
    }

    if((request_header("content-length", &lenStr, sn, rq)!=REQ_PROCEED) ||
       (lenStr==0) || (strlen(lenStr)==0)) {
      status = -2;
      break;
    }

    if (request_header("content-type", &typeStr, sn, rq)==REQ_ABORTED) {
      typeStr = "";
    }

    toRead = atoi(lenStr);

    if (toRead<0) {
      status = -3;
      break;
    }

    b64Item.data = sscT_malloc(PTA_LARGE_BUF_MAX + toRead);
    if (b64Item.data==0) {
      status = VS_ERR_NO_MEM;
      break;
    }
    freeBytes = PTA_LARGE_BUF_MAX + toRead;

    while (toRead > 0) {

      iChar =  netbuf_getc(sn->inbuf); 

      if (iChar==IO_ERROR || iChar==IO_EOF) break;
      else toRead--;

      /* append iChar */
      if (freeBytes > 2) {  /* save room for a \n, NULL. */
        b64Item.data[b64Item.len] = iChar; 
        b64Item.len++;
        freeBytes--;
      }
      else {
        b64Item.data = sscT_realloc(b64Item.data, b64Item.len + freeBytes + 5);
        if (b64Item.data==0) {
          status = VS_ERR_NO_MEM;
          break;
        }
        freeBytes += 4;

        b64Item.data[b64Item.len] = iChar; 
        b64Item.len++;
      }
    }
    /* We always have a buffer allocated, even if it's empty. */
    if (b64Item.data) { /* Unless realloc fails. */
      b64Item.data[b64Item.len] = '\0';
    }

  } while (0);

  if (status) return status;

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "read=%d bytes", b64Item.len);
#endif

  /* This will modify our string in place into something that can be deBase64'ed. */
  vsPTAParsePost(&b64Str, (char *) b64Item.data, typeStr);
  
  /* For debugging, can read the b64(pkcs7) from here 
     vsFileRead("/tmp/sha_stuff/a", &tmpItem); */

  /* alloc a copy of the base64-encoded pkcs7 that was posted. For CGIs.  */
  if (outPKCS7) {
    *outPKCS7 = sscT_strdup(b64Str);
  }
  
  tmpStatus = VSVAL_DeBase64Alloc(gCfg.vsValSDK, &ctx, &postedItem.data, &postedItem.len, b64Str);
  
#ifdef DEBUGMSG
  gCfg.InfoLog(0, "debase=%d", tmpStatus);
  gCfg.InfoLog(0, "debase len = %d", postedItem.len);
#endif

  /* Free this data since we'll return the debase64'ed data. */
  sscT_free(b64Item.data);
  outDigest->data = sscT_malloc(VSVAL_HASH_MAX_LEN);
  status = VSVAL_ParseDetachedPKCS7(gCfg.vsValSDK, &ctx, postedItem.data, postedItem.len, 
                                 outDigest->data, &outDigest->len, &algorithm,
                                 &outCert->data, &outCert->len, 0);

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "read pkcs7 st=0x%x = %d", status, status);
  /*
  debugDumpCertItem(gCfg.vsValSDK, &ctx, outCert); 
  */
#endif

  VSVAL_Free(gCfg.vsValSDK, postedItem.data);

  return status;
}

int SSCSendValid(pblock *pb, Session *sn, Request *rq) {

  int rc = 0;
  char buf[PTA_LARGE_BUF_MAX], *postUrl;

  /* Send a valid url */

  do {
    
    /* A GOOD url. */

    if (postUrl = pblock_findval("validPost", sn->client)) {
      /* If we are coming from /vsadmin/post, send a redirect page to their url. */
      vs_pblock_nvreplace("content-type", "text/html", rq->srvhdrs);
      protocol_status(sn, rq, PROTOCOL_OK, " ");
      protocol_start_response(sn, rq);
      
      if (vsPTAGetRedirectPage(buf, postUrl)) {
        gCfg.InfoLog(0, "get redirect page");
        rc = REQ_ABORTED;
        break;
      }

      if (net_write(sn->csd, buf, strlen(buf)) == IO_ERROR ) {
        gCfg.InfoLog(0, "net write1");
        rc = REQ_ABORTED;
        break;
      }

      /* Only do this service fn. Don't run any others since we've sent the page. */
      rc = REQ_PROCEED;
      break;
    }
    else {
      /* else we got a cookie authentication. Continue. */

      /* REMOVE LATER */
      if(pblock_findval("restartRequest", sn->client)) {
        /* uh-oh, shouldn't ever be here.  We only restart urls that fail. */
        gCfg.InfoLog(0, "abort1");
        rc = REQ_ABORTED;
        break;
      }

      /* Environment vars for normal page are set up in sscCheck(). */

      /* Continue running other matching service fns. */
      /* Using REQ_PROCEED will only do this service function. (Not what we want.) */
      rc = REQ_NOACTION;
    }


  } while (0);

  return rc;
}


int SSCSendLogout(pblock *pb, Session *sn, Request *rq) {

  int rc = 0;

  /* Send the logout-url. */

  do {

    /* If this is the first time here... */
    if (pblock_findval("restartRequest", sn->client)==0) {

      /* Setup to use the configured logout-url */
      if (vsSetGETUrl(gCfg.logoutUrl, sn, rq)) {
        gCfg.InfoLog(0, "set get logout");
        rc = REQ_ABORTED; /* this shouldn't fail. */
        break;
      }

      /* Delete their cookie. */
      setCookie(rq, "Delete", 1);

      /* No environment vars to setup for logout page. */

      /* and restart the request. */
      vs_pblock_nvreplace("restartRequest", "1", sn->client);
        
      rc = REQ_RESTART; /* redo everything */
    }
    else {
      /* (On the 2nd pass) continue on to whatever services the logout url. */
      /* No javascript vars for logout pages. */

      rc = REQ_NOACTION;
    }

  } while (0);

  return rc;
}

int SSCSendAdmin(pblock *pb, Session *sn, Request *rq) {

  int rc = 0;
  char *bufPre = "<html><head><title>Admin Operation</title></head>\n"
    "<h2 align=center>Admin Operation Successful</h2><hr>\n";
  char buf[PTA_LARGE_BUF_MAX];
  char *bufEnd = "</body></html>\n";
  char *adminOp = 0;

  /* Send the successful admin page. */

  do {

    vs_pblock_nvreplace("content-type", "text/html", rq->srvhdrs);
    protocol_status(sn, rq, PROTOCOL_OK, " ");
    protocol_start_response(sn, rq);

    /* Write the page to the client. */
    if (net_write(sn->csd, bufPre, strlen(bufPre)) == IO_ERROR ) {
      gCfg.InfoLog(0, "admin net write1");
      rc = REQ_ABORTED;
      break;
    }

    if (vs_pblock_findstr("adminOp", sn->client, &adminOp)==0) {
      gCfg.InfoLog(0, "Get adminOp");
      rc = REQ_ABORTED;
      break;
    }

    if (strcmp(adminOp, "reset")==0) {
      sprintf(buf, "Authorization Database Reset");
    }
    else if (strcmp(adminOp, "info")==0) {
      sprintf(buf, "Authorization Database Information");
    }
    else if (strncmp(adminOp, "deny/", 5)==0) {
      sprintf(buf, "Authorization Removed for %s", adminOp + 5);
    }
    else if (strncmp(adminOp, "nodeny/", 7)==0) {
      sprintf(buf, "NO ACTION: %s was not authorized.", adminOp + 7);
    }
    else {
      sprintf(buf, "Unknown Admin Operation.  No action taken.");
    }

    /* Write the page to the client. */
    if (net_write(sn->csd, buf, strlen(buf)) == IO_ERROR ) {
      gCfg.InfoLog(0, "admin net write2");
      rc = REQ_ABORTED;
      break;
    }

    /* Write the page to the client. */
    if (net_write(sn->csd, bufEnd, strlen(bufEnd)) == IO_ERROR ) {
      gCfg.InfoLog(0, "admin net write3");
      rc = REQ_ABORTED;
      break;
    }

    /* Only do this service fn. Don't run any others since we've sent the page. */
    rc = REQ_PROCEED;

  } while (0);

  return rc;
}



int SSCSendLogin(pblock *pb, Session *sn, Request *rq, char *sscStatus) {

  int rc = 0;
  ITEM hashItem;
  login_page_t oldLoginMS = {0}, oldLoginNS = {0};
  char buf[PTA_LARGE_BUF_MAX];
  char hascToSign[PTA_TINY_BUF_MAX], hashOfToSign[PTA_TINY_BUF_MAX];
  unsigned char hashBuf[MAX_DIGEST_LEN];
  client_data_t *clientData;
  PTATIME tm = 0;
  char *browserPreBuf, *browserPostBuf;
  int browserPreLen, browserPostLen;
  char *userAgent = 0, *queryString, *tmpUrl = 0;
  void *hashData;

  VSVAL_UserCtx ctx;

  ctx.logFn = gCfg.InfoLog;
  /* login or expired */

  do {

    /* REMOVE LATER */
    if(pblock_findval("restartRequest", sn->client)) {
      /* uh-oh, shouldn't ever be here.  We only restart urls that fail. */
      rc = REQ_ABORTED;
      gCfg.InfoLog(0, "abort2");
      break;
    }

    hashItem.data = hashBuf;
    hashItem.len = 0;
    /* Get a new random piece of data for the client to sign. */
    if (ptaGetValToSign(gCfg.useMD5, hascToSign, hashOfToSign, &hashItem)) {
      gCfg.InfoLog(0, "Get val to sign");
      rc = REQ_ABORTED;
      break;
    }

    /* Over-paranoid? See if there's a duplicate value before inserting. */
/* SB - TODO waiting for a fix from Stan */
   /* 
    if (VSVAL_HashSearch(gCfg.vsValSDK, &ctx, gCfg.hTable, hashItem.data, hashItem.len, 0, &hashData)==0) {
      gCfg.InfoLog(0,"Duplicate hash value!");
    }
  */

    /* Put the hash of this in the hash table. (w/ unauthorized bit set.) */
    if ((clientData = vsPTAInitClientData())==0) {
      gCfg.InfoLog(0, "init client data");
      rc = REQ_ABORTED;
      break;
    }

    pta_time(&tm);
    clientData->authorized = 0;
    clientData->url = sscT_strdup(pblock_findval("oldUri", sn->client));
    if (clientData->url==0) {
      gCfg.InfoLog(0, "init client data url malloc");
      rc = REQ_ABORTED;
      break;
    }

    /* also handle the query string */
    if (queryString = pblock_findval("oldQueryString", sn->client)) {
      tmpUrl = clientData->url;
      clientData->url = (char *) sscT_malloc(strlen(tmpUrl) + strlen(queryString) + 2);
      if (clientData->url) {
        sprintf(clientData->url, "%s?%s", tmpUrl, queryString);
        sscT_free((unsigned char *) tmpUrl);      
      }
      else {
        clientData->url = tmpUrl; /* use the old one if there's no memory. */
      }
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0,"olduri=%s", clientData->url);
#endif
    clientData->absolute_timeout = tm + gCfg.absoluteTimeout;
    clientData->inactive_timeout = tm + gCfg.inactiveTimeout;
    VSVAL_HashInsert(gCfg.vsValSDK, &ctx, gCfg.hTable, hashItem.data, hashItem.len, (void*)clientData);

    /* The login page must be in html. */
    vs_pblock_nvreplace("content-type", "text/html", rq->srvhdrs);
    protocol_status(sn, rq, PROTOCOL_OK, " ");
    protocol_start_response(sn, rq);

    /* Get variables: what to sign, etc... */
    if (vsPTAGetJSForLogin(buf, hascToSign, hashOfToSign, sscStatus,
                        gCfg.useMD5 ? "MD5" : "SHA")) {
      gCfg.InfoLog(0, "get js for login");
      rc = REQ_ABORTED;
      break;
    }

        
    /* Reload the login page from disk if we aren't supposed to cache it. */
    if (gCfg.noCacheLogin) {

      /* Save the old one in case there's a problem. */
      oldLoginNS = gCfg.loginValueNS;
      oldLoginMS = gCfg.loginValueMS;

      if (vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueMS = oldLoginMS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginMS);
      }

      if (vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueNS = oldLoginNS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginNS);
      }
    }

    /* Write the page to the client. */
    userAgent = pblock_findval("user-agent", rq->headers);

    if (userAgent && strstr(userAgent, "MSIE")) {
      /* Microsoft browser page */
      browserPreBuf = (char *) gCfg.loginValueMS.preVars.data;
      browserPreLen = gCfg.loginValueMS.preVars.len;
      browserPostBuf = (char *) gCfg.loginValueMS.postVars.data;
      browserPostLen = gCfg.loginValueMS.postVars.len;
    }
    else {
      /* Netscape (and all others) browser page */
      browserPreBuf = (char *) gCfg.loginValueNS.preVars.data;
      browserPreLen = gCfg.loginValueNS.preVars.len;
      browserPostBuf = (char *) gCfg.loginValueNS.postVars.data;
      browserPostLen = gCfg.loginValueNS.postVars.len;
    }

    /* Part before SSC_VARS */
    if (net_write(sn->csd, browserPreBuf, browserPreLen) == IO_ERROR ) {
      gCfg.InfoLog(0, "net write1");
      rc = REQ_ABORTED;
      break;
    }

    /* $$SSC_VARS$$ */
    if (net_write(sn->csd, buf, strlen(buf)) == IO_ERROR ) {
      gCfg.InfoLog(0, "net write2");
      rc = REQ_ABORTED;
      break;
    }

    /* Part after SSC_VARS */
    if (net_write(sn->csd, browserPostBuf, browserPostLen) == IO_ERROR ) {
      gCfg.InfoLog(0, "net write3");
      rc = REQ_ABORTED;
      break;
    }



    /* Setup environment vars for login page. Are there any? */
    /* vs_pblock_nvreplace("vs_login", "someValue", rq->headers);  */

    /* delete the cookie ?  setCookie(rq, "Delete", 1); */


    /* Only do this service fn. Don't run any others since we've sent the page. */
    rc = REQ_PROCEED;

  } while (0);

  return rc;
}


int SSCSendError(pblock *pb, Session *sn, Request *rq, char *sscStatus) {

  int rc = 0;
  char buf[PTA_LARGE_BUF_MAX];
  char *oldUri = 0;

  /* Bad. Send the error-url. */

  do {

    /* If this is the first time here... */
    if (pblock_findval("restartRequest", sn->client)==0) {

      /* Setup to use the configured error-url */
      if (vsSetGETUrl(gCfg.errorUrl, sn, rq)) {
        gCfg.InfoLog(0, "set get");
        rc = REQ_ABORTED; /* this shouldn't fail. */
        break;
      }

      /* Delete their cookie. */
      /* Otherwise, when server gets rebooted, no way to stop sending a bad auth. */
      setCookie(rq, "Delete", 1);

      /* Setup environment vars for error page. */
      vs_pblock_nvreplace("vs_error", sscStatus, rq->headers); 
      if (oldUri = pblock_findval("oldUri", sn->client)) {
        /* If oldUri != "", use it. */
        if (oldUri[0]) { vs_pblock_nvreplace("vs_url", oldUri, rq->headers); }
      }

      /* and restart the request. */
      vs_pblock_nvreplace("restartRequest", "1", sn->client);
        
      rc = REQ_RESTART; /* redo everything */
    }
    else {
      /* (On the 2nd pass) continue on to whatever services the error url. */

      /* Add javascript vars for html error pages (if requested). */
      if (gCfg.addErrorJSVars) {

        vs_pblock_nvreplace("content-type", "text/html", rq->srvhdrs);
        protocol_status(sn, rq, PROTOCOL_OK, " ");
        protocol_start_response(sn, rq);

        /* prepend variables: what to sign, etc... */
        if (vsPTAGetJSForError(buf, sscStatus, oldUri ? oldUri : "")) {
          gCfg.InfoLog(0, "add js for error page");
          rc = REQ_ABORTED;
          break;
        }

        if (net_write(sn->csd, buf, strlen(buf)) == IO_ERROR ) {
          gCfg.InfoLog(0, "net write1 e");
          rc = REQ_ABORTED;
          break;
        }
      }
      else {
        
        /* If the server thinks the error page is text/plain, force it to html. */
        if (vs_pblock_findmatch("content-type", rq->srvhdrs, "text/plain")) {
          vs_pblock_nvreplace("content-type", "text/html", rq->srvhdrs);
        }

#ifdef DEBUGMSG
          gCfg.InfoLog(0, "snark snark %s ", pblock_findval("content-type", rq->srvhdrs));
#endif
      }
      rc = REQ_NOACTION;
    }

  } while (0);

  return rc;
}



/* Service function for sending the login page, redirect to error, etc... */
NSAPI_PUBLIC int vsSSCSend(pblock *pb, Session *sn, Request *rq) {

  int rc;
  char *sscStatus = "";
  int sendNoCache = 1; /* default to true. Remove for regular pages. */
  

  /* acquire the critical section lock */
  crit_enter(vsLock);

  do {

    vsSetGlobalFn(sn, rq, VS_FN_NAME_SSC_SEND);

    if (vs_pblock_findstr("sscStatus", sn->client, &sscStatus)==0) {
      gCfg.InfoLog(0, "Get sscStatus");
      rc = REQ_ABORTED;
      break;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "Status = %s", sscStatus);
#endif

    if(strcmp(sscStatus, "valid")==0) {
      /* Send a valid url. */
      rc = SSCSendValid(pb, sn, rq);

      /* By default (configurable) we allow normal content to be cached */
      /* by the browser. */
      if (!gCfg.noCachePages) { sendNoCache = 0; }
    }
    else {

      if(strcmp(sscStatus, "login")==0 ||
         strcmp(sscStatus, "expired")==0) {

        /* Send the login page. */
        rc = SSCSendLogin(pb, sn, rq, sscStatus);

      }
      else if(strcmp(sscStatus, "logout")==0) {
        /* Remove the client cookie and authentication from the hash table. */
        rc = SSCSendLogout(pb, sn, rq);
      }
      else if(strcmp(sscStatus, "admin")==0) {
        /* Send a page indicating the admin operation was successful. */
        rc = SSCSendAdmin(pb, sn, rq);
      }
      else {
        /* Send an error page. */
        rc = SSCSendError(pb, sn, rq, sscStatus);
      }

    }

  } while (0);


  /* Tell the client not to cache any pages. Otherwise on second logout, */
  /* the client will just show the local page and not send a logout to the server. */
  if (sendNoCache) {
    vs_pblock_nvreplace("Pragma", "no-cache", rq->srvhdrs);
    /* Some time in the past. */
    vs_pblock_nvreplace("Expires", "Tue, 30 Mar 1999 11:54:01 GMT", rq->srvhdrs);
  }
  
  /* testDump(pb, sn, rq);  Dump everything for debugging reasons. */

  /* release the lock */
  crit_exit(vsLock);

  return rc;
}

/* This is called by ssc.o (we put a pointer to it in gCfg.) This is so */
/* we can use the mutex to protect things if we need to do a refresh. */
int vsNsapiGetRevocationInfo(ITEM *certItem, int *certStatus,
                             PTATIME *statusExpires, char **userName) {

  int status = 0, refreshStatus = 0;
  char *refreshStatusString = "";
  PTATIME currentTime;

  Session *oldSN, *oldCvmSN;
  Request *oldRQ, *oldCvmRQ;
  char *oldFnName, *oldCvmFnName;

  VSVAL_UserCtx ctx = {0};

  char buf[PTA_LARGE_BUF_MAX];

  ctx.logFn = gCfg.InfoLog;

  do {

    /* See if they want use to check CRLs... */
    if (gCfg.noCRLCheck && gCfg.checkOCSP==0) {

      /* If not, just do an expiration time check. */
      /* Does NOT check the entire chain for intermediate CA expiration!!! */

      /* Puts result into certStatus. */
      if (status = VSVAL_IsCertExpired(gCfg.vsValSDK, &ctx, certItem->data, certItem->len, certStatus)) 
        break;

      *statusExpires = PTA_MAX_UPDATE_TIME;
      *userName = sscT_malloc(PTA_SMALL_BUF_MAX);
      if (*userName!=0)
	VSVAL_CertNamePrintable(gCfg.vsValSDK, &ctx, *userName, PTA_SMALL_BUF_MAX, certItem->data, certItem->len);
      break;
    }

    /* Release the SSC lock, get the CVM lock */
    /* Remember the existing error logging info. */
    vsGetGlobalFn(&oldSN, &oldRQ, &oldFnName);
    crit_exit(vsLock);
    crit_enter(vsCvmLock);
    vsGetCvmGlobalFn(&oldCvmSN, &oldCvmRQ, &oldCvmFnName);
    vsSetCvmGlobalFn(oldSN, oldRQ, oldFnName);

    ctx.logFn = vsCvmLogInfoMessage;

    /* See if we have to update all the CRLs based on timer. */
    pta_time(&currentTime);
    if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {

      gCfg.cvmLastUpdate = currentTime;

      /* Re-get all CRLs. */
      if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
          /* Ignore errors, but print an error message. */
          log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, 
                  "Problems acquiring CRLs. Some not installed.");
          /* Also print the last error's cause. */
	      if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
		     sprintf (buf, "Error Code : %d", refreshStatus);
		  }
	      log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, buf);
	  }
      
    }      

    /* We'll only count this as an error if *certStatus isn't set. */
    /* Otherwise url refresh errors give us an error instead of using a valid crl. */
    *certStatus = 0;
	refreshStatus = VSVAL_GetRevocationStatus(gCfg.vsValSDK, &ctx, certItem->data, 
											certItem->len, certStatus, userName);

    if (refreshStatus) {

      if (*certStatus==0) {
        status = refreshStatus; /* Didn't get a cert status. Must return an error. */
      }

      /* Log the error for the server admin. (Even if we got a certStatus.) */
	  if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
	     sprintf (buf, "Error Code : %d", buf);
	  }
      log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, refreshStatusString);
    }

    /* Switch locks again. */
    vsSetCvmGlobalFn(oldCvmSN, oldCvmRQ, oldCvmFnName);
    crit_exit(vsCvmLock);
    crit_enter(vsLock);
    vsSetGlobalFn(oldSN, oldRQ, oldFnName);

  } while (0); 

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "Revocation cert_status = %d", *certStatus);
#endif

  return status;
}

int vsAddValidEnvVars(pblock *pb, Session *sn, Request *rq, 
                      client_data_t *clientData) {

  ITEM b64Cert = {0};
  ITEM pkcs7Item = {0};
  VSVAL_UserCtx ctx={0};
  int tmpStatus;

  ctx.logFn = gCfg.InfoLog;

  /* Set auth-user, etc... */
  pblock_nvinsert("auth-type", "strong", rq->vars);

  if (clientData) {

    if (clientData->userName) {
      pblock_nvinsert("auth-user", clientData->userName, rq->vars);
    }
    
    if (clientData->pkcs7) {

	  /* call removeEOL */
	  pkcs7Item.len = strlen(clientData->pkcs7) + 1;
	  pkcs7Item.data = sscT_malloc (pkcs7Item.len);
	  strcpy (pkcs7Item.data, clientData->pkcs7);
	  removeEOL (&pkcs7Item);


      vs_pblock_nvreplace("vs-pkcs7", pkcs7Item.data, rq->headers);

	  if (pkcs7Item.data)
		 sscT_free (pkcs7Item.data);

      if (!gCfg.savePkcs7) {
        sscT_free((unsigned char *) clientData->pkcs7);
        clientData->pkcs7 = 0;
      }
    }
	
    if (clientData->cert.data &&
        (VSVAL_Base64Alloc(gCfg.vsValSDK, &ctx, &b64Cert.data, clientData->cert.data, clientData->cert.len)==0)) {
      b64Cert.len=strlen((char*)b64Cert.data)+1;
      removeEOL(&b64Cert);      	  
      pblock_nvinsert("auth-cert", (char *) b64Cert.data, rq->vars);
      sscT_free(b64Cert.data);
    }

    tmpStatus = VSUnwrapCertificate(pb, sn, rq);

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "unwrap = %d", tmpStatus);
#endif
  }

  return 0;
}

/* Main entry for certificate verification. */
NSAPI_PUBLIC int vsSSCCheck(pblock *pb, Session *sn, Request *rq)
{

  int status = 0;
  int rc = REQ_ABORTED;
  char *errorString = "", *newUrl;
  client_data_t *clientData;
  char *uri, *cookieVal, *hascKey=0, *outPKCS7, *queryString = 0;
  char *adminOp = 0, *denyHasc;
  ITEM outDigest = {0}, outCert = {0};
  int certStatus = 0, oldHtableSize;
  char adminOpBuf[PTA_LARGE_BUF_MAX];

  VSVAL_UserCtx ctx = {0};

  ctx.logFn = gCfg.InfoLog;

  /* struct timeval tp; for performance timing. */

  /* acquire the critical section lock */
  crit_enter(vsLock);

  vsSetGlobalFn(sn, rq, VS_FN_NAME_SSC_CHECK);

  /* If we're here after restarting the request, continue on. */
  if (pblock_findval("restartRequest", sn->client)) {

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "restartRequest ON");
#endif
    /* This message is from send() pass1--> send() pass 2.  Don't remove it. */
    /* release the lock and proceed */
    crit_exit(vsLock);
    return REQ_PROCEED;
  }

  do {

    if (vs_pblock_findstr("uri", rq->reqpb, &uri)==0) {
      status = VS_ERR_NO_URI;
      break;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "uri=%s", uri);
#endif

    if (gCfg.protectJavaDirs==0 && strstr(uri, "/java/")) {

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "skipping java uri=%s", uri);
#endif
      crit_exit(vsLock);
      return REQ_PROCEED;
    }

    clientData = 0;
    cookieVal = newUrl = 0;

    /* We will use cookieVal to know if we are actually sending a page. */
    /* To get a page, the user must be presenting a cookie, vsadmin/post sets it and */
    /* does a redirect. */

    /* First, examine the cookie presented. */
    if ((findMyCookie(rq, &cookieVal)==0) && cookieVal) {
      
      /* See if the cookie holds a good authentication. */
	  
      certStatus = vsPTAAuthorizeCookie(gCfg.hTable, cookieVal, &clientData);
      

      /* We probably won't use the url in this link since we'll only redirect to */
      /* this url if they try to go to vsadmin/post incorrectly. */

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "found cookie, certStatus=%d", certStatus);
#endif
    }

    if (strncmp(uri, "/vsadmin/", 9)==0) {

      if (certStatus==CS_VALID) {
        /* already authenticated, but requesting a special url */
        
        /* if requesting /vsadmin/post, why? */
        if (strcmp(uri, "/vsadmin/post")==0) {
          /* send them to the originally requested url. */
          newUrl = clientData->url; /* This clientData is from the cookie auth. */
        }
        else {
          /* See if they're the admin, and then handle their request. */
          if (gCfg.adminIssuerSerial && cookieVal &&
              vsPTAIsAdmin(gCfg.adminIssuerSerial, clientData->iSDigest)) {

            if (strcmp(uri, "/vsadmin/reset")==0) {
              VSVAL_HashDestroy(gCfg.vsValSDK, &ctx, gCfg.hTable);
              VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, gCfg.hTableSize, (VSVAL_pFnHashDestroy)vsPTADestroyClientData , (VSVAL_pFnHashGetISDigest)vsPTAGetISDigest);
              adminOp = "reset";
            }
            else if (strcmp(uri, "/vsadmin/info")==0) {
              adminOp = "info";
            }
            else if (strncmp(uri, "/vsadmin/deny/", 14)==0) {

#ifdef DEBUGMSG
  VSVAL_HashTablePrint(gCfg.vsValSDK, &ctx, gCfg.hTable);
#endif

              denyHasc = uri + 14;
#ifdef DEBUGMSG
              gCfg.InfoLog(0, "Delete %s", denyHasc);
#endif
              if (VSVAL_HashDeleteISDigest(gCfg.vsValSDK, &ctx, gCfg.hTable, denyHasc)) {
                sprintf(adminOpBuf, "deny/%s", denyHasc);
                adminOp = adminOpBuf;
              }
              else {
                sprintf(adminOpBuf, "nodeny/%s", denyHasc);
                adminOp = adminOpBuf;
              }

#ifdef DEBUGMSG
  VSVAL_HashTablePrint(gCfg.vsValSDK, &ctx, gCfg.hTable);
#endif

            }
          }
          else {
            certStatus = CS_SSC_BAD_ADMIN;
          }
        }
      }
      else {
        /* If they didn't present a cookie, we must authenticate them */

        /* Didn't present a useful cookie (if we did get one, it wasn't valid). */
        /* This tells later code we used a post to authenticate, not the cookie. */
        cookieVal = 0;

        if (strcmp(uri, "/vsadmin/post")==0) {
          
          /* Allocs memory */
          outPKCS7 = 0;
          if (status = vsGetPostedData(&outPKCS7, &outDigest, &outCert, sn, rq)) {
#ifdef DEBUGMSG
            gCfg.InfoLog(0, "get=0x%x = %d", status, status);
#endif

            /* In this case we can't save these in the hash table in authorizePost. */
            /* Free them now. */
            sscT_free((unsigned char *) outPKCS7);
            sscT_free((unsigned char *) (outCert.data));

            break;
          }

          /* dup the return value since it's a static buffer. */
		  hascKey = (unsigned char*) sscT_malloc (2*outDigest.len+1);
		  VSVAL_Bin2Hasc(gCfg.vsValSDK, &ctx, outDigest.data, outDigest.len, hascKey);
    
          if (hascKey==0) {
            /* In this case we can't save these in the hash table in authorizePost. */
            /* Free them now. */
            sscT_free((unsigned char *) outPKCS7);
            sscT_free((unsigned char *) (outCert.data));
            
            status = VS_ERR_NO_MEM;
            break;
          }

#ifdef DEBUGMSG
          gCfg.InfoLog(0, "hascKey=%s", hascKey);
#endif

          /* See if the post holds a good authentication. */
          clientData = 0;
          certStatus = vsPTAAuthorizePost(gCfg.hTable, outDigest,
                                       &outCert, outPKCS7, &clientData);

          if (certStatus==CS_VALID) {
            setCookie(rq, hascKey, 0);
            newUrl = clientData->url;
          }
          else if (clientData) {
            /* If there's an error or expiration, don't redirect to vsadmin/post. */
            /* Use the original url.  This clobbers uri for anyone later. */
            uri = clientData->url;
            newUrl = clientData->url;
          }
          else {
            /* Doesn't work for bad sigs since we stored the url in the hash table */
            /* along with the good signature. Can't find it given only the bad hash. */
            uri = 0;
            /* Send them to "/". Only needed/used by user plugins that change a bad */
            /* (!CS_VALID) status to CS_VALID. We must send them somewhere. */
            newUrl = "/";
          }

          sscT_free(outDigest.data);
          /* sscT_free(outCert.data); This is saved in the hash table. don't free it. */

        }
        else {
          /* no access to special urls w/o authentication. */
          /* Must send login page. */
        }
      }
    }
#ifndef WIN32
    else if (strcmp(uri, gCfg.logoutUrl)==0) {
#else
    else if (_stricmp(uri, gCfg.logoutUrl)==0) {
#endif      
      if (certStatus==CS_VALID || certStatus==CS_SSC_COOKIE_EXPIRED) {

        /* If they are expired, it's better to show them the logout page than error. */

        /* Log out the user by removing the authentication from the hash table. */
        VSVAL_HashDeleteHasc(gCfg.vsValSDK, &ctx, gCfg.hTable, cookieVal);

        certStatus = CS_SSC_LOGOUT;
      }
    }

  } while (0);

  if (status) {

    /* Log Errors */
    sscErrorString(&errorString, status);
    log_error(LOG_FAILURE, VS_FN_NAME_SSC_CHECK, sn, rq, "%s", errorString);

    /* Log denials? */
    if (gCfg.logSecurity && certStatus) {
      log_error(LOG_SECURITY, VS_FN_NAME_SSC_CHECK, sn, rq, 
                "Certificate %s for %s", vsPTACertStatusString(certStatus), 
                vsPTAGetUserName(clientData));
    }

    /* And set up to send an error page later. */
    vs_pblock_nvreplace("sscStatus", errorString, sn->client);
    rc = REQ_PROCEED;
  }
  else {

    /* Call out to user plugin. */
    /* We don't call the plugin if there's no cookie, and status is VALID. */
    /* In that case, we set a cookie and the plugin will be called on the redirect. */
    if (gCfg.dlCheck && !adminOp && (cookieVal || certStatus != CS_VALID)) {
      if (clientData) {
        certStatus = gCfg.dlCheck(certStatus, uri, 
                                  clientData->cert.data, clientData->cert.len,
                                  clientData->pkcs7, vsPTAGetUserName(clientData));
      }
      else {
        certStatus = gCfg.dlCheck(certStatus, uri, 0, 0, 0, 0);
      }
      
      /* If they changed !valid->valid, must set a cookie. */
      if (certStatus==CS_VALID && !cookieVal) {
        setCookie(rq, hascKey, 0);
      }
    }

    if (certStatus==CS_VALID && !adminOp) {
      
      /* Set the real url */
      if (newUrl) { 
#ifdef DEBUGMSG
        gCfg.InfoLog(0, "set real url to %s", newUrl);
#endif
        vs_pblock_nvreplace("validPost", newUrl, sn->client); 
      }

      /* need to set up pblock/env vars here since we won't have them in Send(). */
      if (cookieVal && gCfg.addEnvVars) {
        vsAddValidEnvVars(pb, sn, rq, clientData);
      }

      vs_pblock_nvreplace("sscStatus", "valid", sn->client);
      rc = REQ_PROCEED; /* Not changing uri value.  Just continue. */
      
    }
    else if (certStatus==CS_VALID && adminOp) {
      vs_pblock_nvreplace("sscStatus", "admin", sn->client);
      vs_pblock_nvreplace("adminOp", adminOp, sn->client);
      rc = REQ_PROCEED; /* Not changing uri value.  Just continue. */
    }
    else {
      
      /* If they were denied, send the login or error page. */
      /* which one is determined by the status code. */

      /* Log denials if it is not a login request */
      if (gCfg.logSecurity && certStatus != 0) {
        log_error(LOG_SECURITY, VS_FN_NAME_SSC_CHECK, sn, rq, 
                  "Certificate %s for %s", vsPTACertStatusString(certStatus),
                  vsPTAGetUserName(clientData));
      }

      /* Set the status code for the send function. */
      if (uri) { vs_pblock_nvreplace("oldUri", uri, sn->client); }
      else { vs_pblock_nvreplace("oldUri", "", sn->client); }

      if (vs_pblock_findstr("query", rq->reqpb, &queryString)) {
        vs_pblock_nvreplace("oldQueryString", queryString, sn->client);
      }

      if (certStatus==0) {
        vs_pblock_nvreplace("sscStatus", "login", sn->client);
      }
      else if (certStatus==CS_SSC_COOKIE_EXPIRED ||
               certStatus==CS_SSC_POST_EXPIRED) {
        vs_pblock_nvreplace("sscStatus", "expired", sn->client);
      }
      else if (certStatus==CS_SSC_LOGOUT) {
        vs_pblock_nvreplace("sscStatus", "logout", sn->client);
      }
      else {
        vs_pblock_nvreplace("sscStatus", vsPTACertStatusString(certStatus), sn->client);
      }


      /* Go on to our service function. */
      rc = REQ_PROCEED;

    }
  }

  /* performance timing
     gettimeofday(&tp, 0);
     gCfg.InfoLog(0, "tp = %d, %d", tp.tv_sec, tp.tv_usec);
  */

  sscT_free((unsigned char *) hascKey);

  /* release the lock */
  crit_exit(vsLock);

  return rc;
}

