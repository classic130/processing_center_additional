

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/**
*  Begin Change : Infosys, 12 Jul 04
*  Use generic wrapper to access the validation sdk.
**/

/*#include "vsvalsdk.h"*/
#include "vs_cvm_genlib.h"
#include "vs_cvm_log.h"
#include "vs_cvm_constants.h"
/**
*  End Change : Infosys
**/
/* for the timer-based CRL refresh */
#include "sys/types.h"
#include "time.h"
#include "cvmglobal.h"
/* 
  The following three headers are standard for SAFs.  They're used to
  get the data structures and prototypes needed to declare and use SAFs.
 */

#include "base/pblock.h"
#include "base/session.h"
#include "frame/req.h"

#include "frame/protocol.h"
#include "frame/conf.h"
#include "base/util.h"


#define VS_FN_NAME_REFRESH "vsRefreshCRLs"
#define VS_FN_NAME_INIT    "vsCheckCertInit"
#define VS_FN_NAME_CHECK   "vsCheckClientCert"

/* Critical section variable to protect the following globals */
CRITICAL vLock = 0;

/**
*  Begin Change : Infosys, 12 Jul 04
*  Use generic wrapper to access the validation sdk.
**/

/*SYS_THREAD vsThread = 0;*/

/* Globals */
/* handle to validation SDK instance */
/*VSVAL_SDK *globalValSDK;*/
int globalLogSecurity = 0;
int globalLogInfo = 0;

/*
CVMTIME globalUpdateSeconds = 0;
CVMTIME globalLastUpdate = 0;
*/
char *globalErrorCgi = 0;

/* for logging info messages */
Session *globalSN = 0;
Request *globalRQ = 0;
char *globalFnName = 0;

CERT_FIELDS *cf;

/*
void vsNullValSDKLogMessage (void* handle, char *fmt, ...) {
  return;
}

void vsValSDKLogMessage (void* handle, char *fmt, ...) {
  char infoBuf[CVM_LARGE_BUF_MAX];
  va_list ap;
  va_start(ap, fmt);
  
  (void) vsprintf(infoBuf, fmt, ap);
  va_end(ap);
  
  log_error(LOG_WARN, globalFnName, globalSN, globalRQ, "%s", infoBuf);  
  return;
}
*/
/**
*  End Change : Infosys
**/


/* See if a pblock named attribute is set to on. */
int vs_pblock_ison(const char *name, pblock *pb) {
  
  char *value = 0;

  value = pblock_findval(name, pb);

  return cvmCfgStringIsOn(value);
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

/**
*  Begin Change : Infosys, 12 Jul 04
*  Use generic wrapper to access the validation sdk.
**/
NSAPI_PUBLIC void vsCheckCertCleanup(void *param)
{
  /* cleanup --  At_exit... */
  /*if (vsThread) { systhread_terminate(vsThread); vsThread = 0; }*/

  crit_terminate(vLock);
  vLock = NULL;

  /*VSVAL_Final (globalValSDK);*/
  if (globalErrorCgi) {
    free(globalErrorCgi);
    globalErrorCgi = 0;
  }

  vs_cvm_genlib_exit();
}
/**
*  End Change : Infosys
**/


/* make a url for this server:port/urlName */
int vsMakeErrorUrl(char *urlName, char *outBuf) {

  char *serverName = 0;
  int serverPort = 0;
  int ssl = 0;
  char *fileName = 0;

  if (urlName[0]=='/' || urlName[0]=='\\') {
    fileName = strdup(urlName);
  }
  else {
    fileName = (char *) malloc(sizeof(char)*(strlen(urlName)+2));
    if (fileName) {
      sprintf(fileName, "/%s", urlName);
    }
  }

  serverName = server_hostname;
  serverPort = conf_getglobals()->Vport;
  ssl = security_active;
  
  if (ssl) {
    if (serverPort==443) sprintf(outBuf, "https://%s%s", serverName, 
                                 fileName ? fileName : "/");
    else sprintf(outBuf, "https://%s:%d%s", serverName, serverPort,
                 fileName ? fileName : "/");
  }
  else {
    if (serverPort==80) sprintf(outBuf, "http://%s%s", serverName,
                                fileName ? fileName : "/");
    else sprintf(outBuf, "http://%s:%d%s", serverName, serverPort,
                 fileName ? fileName : "/");
  }
  
  if (fileName) free(fileName);

  return 0;
}

/**
*  Begin Change : Infosys, 12 Jul 04
*  Moved to generic wrapper.
**/
/*
void vsSleeperThread(void *ptr) {
  
  CVMTIME currentTime = 0;
  Session *oldSN = 0;
  Request *oldRQ = 0;
  char *oldFnName = 0;
  int refreshStatus = 0;
  char *refreshStatusString = 0;
  VSVAL_UserCtx ctx = {0};
  char buf[CVM_LARGE_BUF_MAX];

  if (globalLogInfo == 1)
	ctx.logFn = vsValSDKLogMessage;
  else
	ctx.logFn = vsNullValSDKLogMessage;

  while (1) {

    if (!vsThread) {
*/      /*
       * Due to race conditions, it is possible that during shutdown, Cleanup
       * happens before termination of thread. In this situation, vLock is 
       * initialized and crit_enter() fails with SEGV on iPlanet 6.0
       */
/*      break;
    }

*/    /* acquire the critical section lock */
/*    crit_enter(vLock);

*/    /* Remember the existing error logging info. */
/*    oldSN = globalSN;
    oldRQ = globalRQ;
    oldFnName = globalFnName;
*/
    /* Set the session and request to null for error logging. */
/*    globalSN = 0;
    globalRQ = 0;
    globalFnName = VS_FN_NAME_REFRESH;
*/

    /* See if we have to update all the CRLs based on timer. */
/*    cvm_time(&currentTime);
    if (currentTime > (globalLastUpdate + globalUpdateSeconds)) {

      globalLastUpdate = currentTime;
*/
      /* Re-get all CRLs. */
/*      if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {*/
        /* Ignore errors, but print an error message. */
/*       log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, 
                  "Problems acquiring CRLs. Some not installed.");
*/	
        /* Also print the last error's cause. */
/*  if (VSVAL_ErrorString(globalValSDK, buf, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
	  sprintf (buf, "Error Code : %d", refreshStatus);
	}
	log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, buf);
      } else {
		if (globalLogInfo == 1)
		  log_error(LOG_INFORM, VS_FN_NAME_REFRESH, 0, 0, "Successfully refreshed certificates and CRLS");
	  }

    }
*/
    /* Put the old error logging info back. */
/*
    globalSN = oldSN;
    globalRQ = oldRQ;
    globalFnName = oldFnName;
*/
    /* release the lock */
/*    crit_exit(vLock);*/

    /* Make sure the sleep is outside the critical section! */
/*    systhread_sleep(globalUpdateSeconds * 334);*/ /* Sleep 1/3 update time. In ms. */
/*  }
}
*/
/**
*  End Change : Infosys
**/

int vsFillErrorCgiBuffer(char *errorCgi){
  
  char urlBuf[CVM_LARGE_BUF_MAX];

  globalErrorCgi = (char *) malloc(CVM_LARGE_BUF_MAX);

  if (globalErrorCgi==0) {
    return VSVAL_ERR_ALLOC;
  }

  if(strncmp(errorCgi, "http:", 5)==0 ||
     strncmp(errorCgi, "https:", 6)==0) {
    /* Don't need to do anything. Assume it's an entire url. */
    sprintf(urlBuf, "%s", errorCgi);
  }
  else {
    /* assume it's a file on this server. */
    vsMakeErrorUrl(errorCgi, urlBuf);
  }

  sprintf(globalErrorCgi, 
          "<HTML><META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=%s?%%d\">", urlBuf);

  return 0;
}

/**
*  Begin Change : Infosys, 12 Jul 04
*  Use generic wrapper to access the validation sdk.
**/

/* Main entry for crl checking. */
NSAPI_PUBLIC int vsCheckCertInit(pblock *pb, Session *sn, Request *rq)
{
  int status = 0;
/* char errorString[VSVAL_BUF_MAX];

  char *cfg_filename = 0;
  char *file_prefix = 0;
  char *url_prefix = 0;
  char *cache_dir = 0;
*/
  char *intString = 0;
  char *errorCgi = 0;
/*
  char *ocspUrl = 0;
  char *defaultLdap = 0;
  char *httpProxy = 0;
  char *ldapHttpProxy = 0;
  int ldapTimeOut = 0;
*/
  int volatile x = 0;
  
  /*VSVAL_UserCtx ctx = {0};*/

  CFG_PARAMS cp;

  globalSN = sn;
  globalRQ = rq;
  globalFnName = VS_FN_NAME_INIT;


  do {

    /* Make a critical variable */
    vLock = crit_init();

    if (vs_pblock_ison("log-info", pb)) 
      globalLogInfo = 1;
	cp.logInfo = malloc(2 * sizeof(char));
	if(globalLogInfo == 1) {
		strcpy(cp.logInfo, "1");
	} else {
		strcpy(cp.logInfo, "0");
	}
/*
	if (globalLogInfo == 1)
		ctx.logFn = vsValSDKLogMessage;
	else
		ctx.logFn = vsNullValSDKLogMessage;
*/
  /* and register its cleanup function */
    daemon_atrestart(vsCheckCertCleanup, NULL);

    /*
    if ((status = VSVAL_Init(&globalValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
      break;
    }
	*/
	
	
	cp.logFileName = master_error_log;

    /* Read NSAPI options from obj.conf */
    /*file_prefix = pblock_findval("file-prefix", pb);*/
	cp.filePrefix = pblock_findval("file-prefix", pb);
    /*if (file_prefix != 0)*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "file-prefix", file_prefix))*/
	/*break;*/

    /*url_prefix = pblock_findval("url-prefix", pb);*/
	cp.urlPrefix = pblock_findval("url-prefix", pb);
    /*if (url_prefix != 0)*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "url-prefix", url_prefix))*/
	/*break;*/

    /*cache_dir = pblock_findval("cache-dir", pb);*/
	cp.cacheDir = pblock_findval("cache-dir", pb);
    /*if (cache_dir != 0)*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "cache_dir", cache_dir))*/
	/*break;*/


    /*httpProxy = pblock_findval("http-proxy", pb);*/
	cp.httpProxy = pblock_findval("http-proxy", pb);
    /*if (httpProxy != 0)*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "http-proxy", httpProxy))*/
	/*break;*/
	
    /*ldapHttpProxy = pblock_findval("ldap-http-proxy", pb);*/
	cp.ldapHttpProxy = pblock_findval("ldap-http-proxy", pb);
    /*if (ldapHttpProxy != 0)*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy))*/
	/*break;*/

    if (intString = pblock_findval("ldap-timeout", pb)) {
    /*  ldapTimeOut = atoi(intString);*/
		cp.ldapTimeOut = atoi(intString);
    }
    else {
    /*  ldapTimeOut = CVM_LDAP_TIMEOUT;*/
		cp.ldapTimeOut = -1;
    }
	/*if (status = VSVAL_SetIntOpt (globalValSDK, &ctx, "ldap-timeout", ldapTimeOut))*/
	/*	break;*/

    /* Must be done AFTER proxy configuration */
    /*ocspUrl = pblock_findval("ocsp-url", pb);*/
	cp.ocspUrl = pblock_findval("ocsp-url", pb);
    /*if (ocspUrl != 0)*/
    /*{*/
    /*  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "ocsp-url", ocspUrl))*/
	/*break;*/
    /*}*/

    if (errorCgi = pblock_findval("error-cgi", pb)) {
      if (status = vsFillErrorCgiBuffer(errorCgi)) {
        break;
      }
    }
    
    /*defaultLdap = pblock_findval("default-ldap", pb);*/
	cp.defaultLdap = pblock_findval("default-ldap", pb);
    /*if (defaultLdap !=0)*/
    /*  status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", defaultLdap);*/
    /*else*/
    /*  status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", "directory.verisign.com");*/
    /*if (status != 0)*/
    /*  break;*/

    /*if (vs_pblock_ison("no-check-chain", pb)) */
	cp.noCheckChain = pblock_findval("no-check-chain", pb);
    /*  status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "on");*/
    /*else*/
    /*  status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "off");*/
    /*if (status != 0)*/
    /*  break;*/

    /*if (vs_pblock_ison("log-security", pb)) {*/
    /*  globalLogSecurity = 1;*/
    /*}*/
	cp.logSecurity = pblock_findval("log-security", pb);

    /* get CRL update frequency. */
    if (intString = pblock_findval("update-seconds", pb)) {
      /*globalUpdateSeconds = atoi(intString);*/
		cp.updateSeconds = atoi(intString);
    }
    else if (intString = pblock_findval("update-minutes", pb)) {
      /*globalUpdateSeconds = 60 * atoi(intString);*/
		cp.updateSeconds = 60 * atoi(intString);
    }
    else if (intString = pblock_findval("update-hours", pb)) {
      /*globalUpdateSeconds = 60 * 60 * atoi(intString);*/
		cp.updateSeconds = 60 * 60 * atoi(intString);
    }
    else {
      /*globalUpdateSeconds = CVM_MAX_UPDATE_TIME;*/
		cp.updateSeconds = -1;
    }


    /* Print a startup message. */
	/*log_error(LOG_INFORM, VS_FN_NAME_INIT, sn, rq, "%s starting", NSAPI_DESCR);*/
	cp.filterDescription = malloc(sizeof(char) * strlen(NSAPI_DESCR) + 1);
	strcpy(cp.filterDescription, NSAPI_DESCR);
    if (vs_pblock_ison("debug-wait", pb)) {
      x = 1;
    }
    while (x) ;

    
    /*cfg_filename = pblock_findval("cfg-filename", pb);*/
	cp.cfgFileName = pblock_findval("cfg-filename", pb);
    /*if (!cfg_filename || !file_prefix || !cache_dir || (!url_prefix && !ocspUrl)) {*/
    /*  status = VSVAL_ERR_OBJ_CONF;*/
    /*  break;*/
    /*}*/

    /* check params... make sure there's a trailing / */
    /*if (status = VSVAL_ReadConfigFile(globalValSDK, &ctx, cfg_filename))*/
    /*  break;*/

    /* Start a thread to do the timer-based CRL updates. */
    /*if (globalUpdateSeconds < CVM_MAX_UPDATE_TIME) {*/
    /*  if ((vsThread = systhread_start(0, 0, vsSleeperThread, 0))==SYS_THREAD_ERROR) {*/
    /*    status = VSVAL_ERR_THREAD;*/
    /*    break;*/
    /*  }*/
    /*}*/


  } while (0);

  /*if (status) {*/
  /*  VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);*/
  /*  pblock_nvinsert("error", errorString, pb);*/
  /*  log_error(LOG_FAILURE, VS_FN_NAME_INIT, sn, rq, "%s", errorString);*/
  /*}*/

  cp.logDebug = 0;

  status = vs_cvm_genlib_init(cp);

  if (status) return REQ_ABORTED;
  else return REQ_PROCEED;

}



/* Main entry for crl checking. */
/* Check validity of certificate */
NSAPI_PUBLIC int vsCheckClientCert(pblock *pb, Session *sn, Request *rq)
{

  int status = 0;
  char *b64Buf = 0, *userName = 0;
  /*char refreshStatusString[VSVAL_BUF_MAX], errorString[VSVAL_BUF_MAX];*/
  CVMTIME currentTime = 0, statusExpires = 0;
  static char redirectBuf[CVM_LARGE_BUF_MAX];
  int certStatus = 0, refreshStatus = 0;
  int rc = REQ_ABORTED;
  pblock *newpb = 0;
  /*VSVAL_UserCtx ctx={0};*/

  char *clientSessionIp = pblock_findval("ip", sn->client);

  if ((sn->iaddr.s_addr == 0) && (!strcmp(clientSessionIp, "0.0.0.0")))
  {
    /*
     * This patch is to support iPlanet 6.0. During instance startup,
     * server initializes the servlet engine and uses 'default object'
     * in the obj.conf to find the document root. If it has a line
     * AuthTrans vsCheckClientCert, it calls vsCheckClientCert to verify
     * the client certificate and during instance startup, there is NO
     * client certificate, hence vsCheckClientCert fails.
     */

    log_error(LOG_SECURITY, VS_FN_NAME_CHECK, sn, rq,
              "No action taken on request received from %s.", clientSessionIp);

    return REQ_NOACTION;
  }

  newpb = pblock_dup(pb);
  if (newpb) {
    /* Acquire the client-auth certificate. */
    vs_pblock_nvreplace("method", "*", newpb);
    vs_pblock_nvreplace("dorequest", "1", newpb);
    vs_pblock_nvreplace("fn", "get-client-cert", newpb); 
    func_exec(newpb, sn, rq);
  }
  else {
    status = VSVAL_ERR_ALLOC;
  }


  /* acquire the critical section lock */
  crit_enter(vLock);

  /*if (globalLogInfo == 1)*/
	/*ctx.logFn = vsValSDKLogMessage;*/
  /*else*/
	/*ctx.logFn = vsNullValSDKLogMessage;*/

  /*do {*/
  
  /*  if (status) break; *//* If we hit an error up above. */

    b64Buf = pblock_findval("auth-cert", rq->vars);

  /*  if (!b64Buf) {*/
  /*    status = VSVAL_ERR_NO_AUTH_CERT;*/
  /*    break;*/
  /*  }*/

  /*  globalSN = sn;*/
  /*  globalRQ = rq;*/
  /*  globalFnName = VS_FN_NAME_CHECK;*/

    /* See if we have to update all the CRLs based on timer. */
  /*  cvm_time(&currentTime);*/
  /*  if (currentTime > (globalLastUpdate + globalUpdateSeconds)) {*/

  /*    globalLastUpdate = currentTime;*/
  /*    if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {*/
        /* Ignore errors, but print an error message. */
  /*      log_error(LOG_FAILURE, VS_FN_NAME_REFRESH, 0, 0, */
  /*                "Problems acquiring CRLs. Some not installed.");*/
	
        /* Also print the last error's cause. */
  /*if (VSVAL_ErrorString(globalValSDK, refreshStatusString, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {   sprintf (refreshStatusString, "Error Code : %d", refreshStatus);*/
	/*}*/
  /*log_error(LOG_FAILURE, VS_FN_NAME_CHECK, 0, 0, refreshStatusString);*/
  /*    }*/
  /*  } */     

    /* look up the certificate */
  /*  status = VSVAL_GetRevocationStatusB64(globalValSDK, &ctx, b64Buf, &certStatus, &userName);*/
  /*} while (0);*/

  /**
  *   Call the generic wrapper validate function
  **/
  status = vs_cvm_genlib_validate((unsigned char*)b64Buf, -1, &certStatus, userName, cf);

  if (status) {
    /* Log Errors */
    /*VSVAL_ErrorString (globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);*/
    /*log_error(LOG_FAILURE, VS_FN_NAME_CHECK, sn, rq, "%s", errorString);*/

    /* Log denials? */
    /*if (globalLogSecurity && certStatus) {*/
    /*  log_error(LOG_SECURITY, VS_FN_NAME_CHECK, sn, rq, */
    /*            "Certificate %s for %s", VSVAL_CertStatusString(globalValSDK, certStatus),*/
    /*            userName ? userName : "client");*/
    /*}*/

    /* Invalidate this ssl session for the next call. */
    if (newpb) {
      vs_pblock_nvreplace("fn", "ssl-logout", newpb);
      func_exec(newpb, sn, rq);
    }

    /* And return a forbidden page. */
    /*protocol_status(sn, rq, PROTOCOL_FORBIDDEN,*/
	/*	VSVAL_CertStatusString(globalValSDK, certStatus));*/
	protocol_status(sn, rq, PROTOCOL_FORBIDDEN,
		vs_cvm_genlib_get_cs_str(certStatus));
	rc = REQ_ABORTED;
  }
  else {

    if (certStatus==CS_VALID) {

      /* Set auth-user, etc... */
      pblock_nvinsert("auth-user", userName, rq->vars);
      pblock_nvinsert("auth-type", "strong", rq->vars);
      rc = REQ_PROCEED;
    }
    else {
      
      /* Log denials? */
      /*if (globalLogSecurity) {*/
      /*  log_error(LOG_SECURITY, VS_FN_NAME_CHECK, sn, rq, */
      /*            "Certificate %s for %s", VSVAL_CertStatusString(globalValSDK, certStatus),*/
      /*            userName ? userName : "client");*/
      /*}*/

      /* Invalidate this ssl session for the next call. */
      if (newpb) {
        vs_pblock_nvreplace("fn", "ssl-logout", newpb);
        func_exec(newpb, sn, rq);
      }

      /* And return a forbidden page. */
      /*protocol_status(sn, rq, PROTOCOL_FORBIDDEN, */
		/*  VSVAL_CertStatusString(globalValSDK, certStatus));*/
	  protocol_status(sn, rq, PROTOCOL_FORBIDDEN,
		vs_cvm_genlib_get_cs_str(certStatus));
      rc = REQ_ABORTED;
    }
  }

  /* Prepend the error redirection tag if the user wants it. */
  if (globalErrorCgi && rc==REQ_ABORTED) {
    if (protocol_start_response(sn, rq)==REQ_PROCEED) {
      sprintf(redirectBuf, globalErrorCgi, certStatus);
      net_write(sn->csd, redirectBuf, strlen(redirectBuf));
    }
  }

  /*VSVAL_Free(globalValSDK, userName);*/
  /* release the lock */
  crit_exit(vLock);

  if (newpb) {
    pblock_free(newpb);
    newpb = 0;
  }
  return rc;
}

/**
*  End Change : Infosys
**/

