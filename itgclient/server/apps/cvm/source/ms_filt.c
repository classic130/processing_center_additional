
/* ISAPI filter for doing revocation checking. */

#include <stdio.h>

#define WIN32_LEAN_AN_MEAN
#include <windows.h>
#include <httpfilt.h>
#include <httpext.h>
#include <direct.h>

#include <process.h> /* for beginthread */

#include <debug.h> /* Debugging macro from ISAPI/NSAPI book. */
#include <string.h>

#include "sys/types.h"
#include "time.h"

/**
*  Begin Change : Infosys, 7 Jul 04
*  Use generic wrapper to access the validation sdk.
**/


#include "cvmglobal.h"
/*
#include "vsvalsdk.h"
*/

#include "vs_cvm_genlib.h"
#include "vs_cvm_log.h"
#include "vs_cvm_constants.h"

/**
*  End Change : Infosys
**/

#define BUFF_MAX 256

#define VS_RESOURCE_PROTECTED 794
#define VS_RESOURCE_NOT_PROTECTED 795
#define VS_RESOURCE_PROTECTED_BUT_NO_AUTH 796
#define VS_RESOURCE_PROTECTED_AND_AUTH 797
#define VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL 798

/* Globals */

#define INITIAL_CERT_BUF_SIZE 10000

/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved into the generic wrapper.
**/

/*
unsigned long hThread = 0;
/*

/* handle to validation SDK instance */
/*
VSVAL_SDK *globalValSDK;

CVMTIME globalUpdateSeconds = 0;
CVMTIME globalLastUpdate = 0;
*/

/**
*  End Change : Infosys
**/

char *globalErrorCgi = 0;

/* List of protected directories. */
char **globalProtectedDirList;
int globalProtectedDirCount;
int globalIsaInstall = 0;

/* for logging info messages */
/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved into the generic wrapper.
**/

//FILE *globalLogFP = 0;
//char *globalLogName = 0;
//int globalLogInfo = 0;
int globalLogDebug = 0;
//int globalLogSecurity = 0;

CERT_FIELDS *cf;

/**
*  End Change : Infosys
**/

HANDLE hMutexSleep = 0;
HANDLE hMutex = 0;
HANDLE hMutexLog = 0;
SECURITY_ATTRIBUTES saDefaultSecurity = {0};
#define VS_MUTEX_NAME "verisign_validate_mutex"
#define VS_MUTEX_SLEEP_NAME "verisign_validate_mutex_sleep"
#define VS_MUTEX_LOG_NAME "verisign_validate_mutex_log"

/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved into the generic wrapper.
**/

//int sleeperRunning = 1;


/**
*  End Change : Infosys, 7 Jul 04
**/

/* get last web server error */
void vsGetLastErrorISAPI(char *buf) {

  DWORD dwError;
	
  switch (dwError = GetLastError( )) {
	
  case ERROR_INVALID_PARAMETER:
    strcpy( buf, "ERROR_INVALID_PARAMETER" );
    break;
		
  case ERROR_INVALID_INDEX:
    strcpy( buf, "ERROR_INVALID_INDEX" );
    break;
		
  case ERROR_INSUFFICIENT_BUFFER:
    wsprintf( buf, "ERROR_INSUFFICIENT_BUFFER -  %%d bytes required.");
    break;
		
  case ERROR_MORE_DATA:
    strcpy( buf, "ERROR_MORE_DATA" );
    break;
		
  case ERROR_NO_DATA:
    strcpy( buf, "ERROR_NO_DATA" );
    break;
		
  default:
    wsprintf(buf, "*** Error %d (0x%x) occured retrieving server variable ***",
             dwError, dwError);
  }
}

/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved into the generic wrapper.
**/

/*
#define LOG_FAILURE "error"
#define LOG_SECURITY "security"
#define LOG_WARN "warning"
#define LOG_INFO "info"
#define LOG_ACCESS "access"
#define LOG_DEBUG "debug"
*/

/*
void vs_cvm_genlib_log_message(char *severity, char *fmt, ...) {

  char infoBuf[CVM_LARGE_BUF_MAX];
  CVMTIME currentTime;
  char *timeBuf = 0;
  va_list ap;
  va_start(ap, fmt);

  if (globalLogFP==0) return;
*/
/*  
  if (WaitForSingleObject(hMutexLog, INFINITE)==WAIT_OBJECT_0) {
*/
/*
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);

	cvm_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	cvm_make_newline_null(timeBuf);

	fprintf(globalLogFP, "Thread-id:%d [%s] %s: %s\n", GetCurrentThreadId(), timeBuf, severity, infoBuf);
	fflush(globalLogFP);
*/
/*
	ReleaseMutex(hMutexLog);
  }


  return;
}

void vsValSDKLogMessage(void* handle, char *fmt, ...) {
  char infoBuf[CVM_LARGE_BUF_MAX];
  CVMTIME currentTime;
  char *timeBuf = 0;
  va_list ap;
  va_start(ap, fmt);

  if (globalLogFP==0) return;
*/

/*
  if (WaitForSingleObject(hMutexLog, INFINITE)==WAIT_OBJECT_0) {
*/
/*
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);

	cvm_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	cvm_make_newline_null(timeBuf);
	fprintf(globalLogFP, "[%s] info: %s\n", timeBuf, infoBuf);
	fflush (globalLogFP);
*/
/*
	ReleaseMutex(hMutexLog);
  }
*/
/*
  return;
}

void vsNullValSDKLogMessage (void* handle, char *fmt, ...) {
  return;
}

*/
/**
*  End Change : Infosys
**/


BOOL bIsWindowsVersionOK(DWORD dwMajor, DWORD dwMinor, WORD dwSPMajor)
{
    OSVERSIONINFO osvi;
    
    // Initialize the OSVERSIONINFO structure.// 
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx((OSVERSIONINFO*)&osvi);
    
	// if it is not Windows NT return 
	if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) {
		return FALSE;
	}

    // Check the major version.
    if (osvi.dwMajorVersion > dwMajor)
        return TRUE;
    else if (osvi.dwMajorVersion == dwMajor)
    {
        // Check the minor version.
        if (osvi.dwMinorVersion > dwMinor)
            return TRUE;
        else if (osvi.dwMinorVersion == dwMinor)
        {
            // Check the Service Pack.
            if (dwSPMajor && osvi.dwPlatformId == VER_PLATFORM_WIN32_NT)
            {
                HKEY    hKey;
                DWORD   dwCSDVersion;
                DWORD   dwSize;
                BOOL    fMeetsSPRequirement = FALSE;

                if (RegOpenKeyEx (HKEY_LOCAL_MACHINE,
                        "System\\CurrentControlSet\\Control\\Windows",
                        0,
                        KEY_QUERY_VALUE,
                        &hKey) == ERROR_SUCCESS)
                {
                    dwSize = sizeof(dwCSDVersion);
                    if (RegQueryValueEx (hKey,
                            "CSDVersion",
                            NULL,
                            NULL,
                            (unsigned char*)&dwCSDVersion,
                            &dwSize) == ERROR_SUCCESS)
                    {
                        fMeetsSPRequirement = (LOWORD(dwCSDVersion)  >= dwSPMajor);
                    }
                    RegCloseKey(hKey);
                }
                
                return fMeetsSPRequirement;
            }
            return TRUE;
        }
    }
    return FALSE;
}  

/* Given a string of directories, separated by ";" characters, parse it into a list */
/* IN-PLACE!! Replaces each ';' with a null character. May create NULL strings. */
int vsAllocDirList(char *string, char ***dirList, int *dirCount) {

  int count, i, len;
  char *p = 0;
  char **A = 0;

  _strlwr(string);
  /* count how many */
  count = 1;
  for (p=string; *p; p++) {
    if (*p == ';') {
      count++;
    }
  }
  /* and alloc space. */
  A = (char **) malloc(sizeof(char *) * count);
  if (A==0) return -1;

  /* Now chop out the names */
  i = 0;
  A[0] = string;
  for (p=string; *p; p++) {
    if (*p == ';') {
	  if (*(p-1) == '/')
        *(p-1) = '\0';
      *p = '\0';
      i++;
      A[i] = p+1;
    }
  }

  *dirList = A;
  *dirCount = count;

  len = strlen (A[0]);
  if ((A[0][len-1] == '/') && (len != 1)) 
	  A[0][len-1] = '\0';

  return 0;
}

/* true IFF an entry in dirList is a prefix of 'string'. */
int vsDirIsProtected(char *string, char **dirList, int dirCount) {

  int i, inList = 0;

  _strlwr(string);
  for (i=0; i<dirCount; i++) {
    if (*(dirList[i]) && strstr(string, dirList[i])==string) {
      inList = 1;
      break;
    }
  }

  return inList;
}



/* make a url for this server:port/urlName */
int vsMakeErrorUrl(HTTP_FILTER_CONTEXT *pFC, char *urlName, char *outBuf) {

  char *serverName = 0;
  int serverPort = 0;
  int ssl = 0;
  char *fileName = 0;
  CHAR serverNameBuf[1024], serverPortBuf[1024], sslBuf[1024];
  DWORD dwBytes = 0;

  dwBytes = 1024;
  pFC->GetServerVariable(pFC, "SERVER_NAME", serverNameBuf, &dwBytes);
  dwBytes = 1024;
  pFC->GetServerVariable(pFC, "SERVER_PORT", serverPortBuf, &dwBytes);
  dwBytes = 1024;
  pFC->GetServerVariable(pFC, "HTTPS", sslBuf, &dwBytes);

  if (urlName[0]=='/' || urlName[0]=='\\') {
    fileName = strdup(urlName);
  }
  else {
    fileName = (char *) malloc(sizeof(char)*(strlen(urlName)+2));
    if (fileName) {
      sprintf(fileName, "/%s", urlName);
    }
  }

  serverName = serverNameBuf;
  serverPort = atoi(serverPortBuf);
  ssl = (strncmp(sslBuf, "on", 2)==0);
  
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


int vsFillErrorCgiBuffer(HTTP_FILTER_CONTEXT *pFC, char *errorCgiBuf,
                         char *errorCgi, int queryStatus){
  
  char urlBuf[CVM_LARGE_BUF_MAX];

  if(strncmp(errorCgi, "http:", 5)==0 ||
     strncmp(errorCgi, "https:", 6)==0) {
    /* Don't need to do anything. Assume it's an entire url. */
    sprintf(urlBuf, "%s", errorCgi);
  }
  else {
    /* assume it's a file on this server. */
    vsMakeErrorUrl(pFC, errorCgi, urlBuf);
  }

  sprintf(errorCgiBuf, "<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=%s?%d\">", 
          urlBuf, queryStatus);

  return 0;
}

/**
*  Begin Change : Infosys, 7 Jul 2004
*  Replaced calls to Validation SDK by calls to generic wrapper
**/

DWORD vsSendErrorPage(HTTP_FILTER_CONTEXT *pFC, int certStatus, int status) {

  char buf[CVM_LARGE_BUF_MAX], errorCgiBuf[CVM_LARGE_BUF_MAX];
  unsigned int len=0;
  char *statusString = 0;
  //char errorString[VSVAL_BUF_MAX];
  char errorString[GL_VSVAL_BUF_MAX];
  //VSVAL_UserCtx ctx={0};


  //statusString = VSVAL_CertStatusString(globalValSDK, certStatus);
  statusString = vs_cvm_genlib_get_cs_str(certStatus);

  sprintf(buf, "403 %s", statusString);

  pFC->ServerSupportFunction(pFC, SF_REQ_SEND_RESPONSE_HEADER, buf, 0, (DWORD) NULL);

  if (globalErrorCgi) {
    vsFillErrorCgiBuffer(pFC, errorCgiBuf, globalErrorCgi, certStatus);
  }
  else {
    sprintf(errorCgiBuf, "");
  }

  if (status != 0) {
		//if (VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo)!=0) {
	    if (vs_cvm_genlib_get_err_str(errorString, status)!=0) {
			sprintf(errorString, "Error Code: %d", status);	 
		}
		sprintf(buf, "<HTML><HEAD><TITLE>%s</TITLE></HEAD>\n"
			"<BODY>%s<H2>Access Denied</H2>\n"
			"We could not authenticate you based on the certificate that you selected.\n"
			"<BR>Please verify that you are using the correct certificate and try again. \n"
			"<P>If the problem persists please contact the site administrator. \n"
			"<P><B>%s</B></P>"
			"</BODY></HTML>", statusString, errorCgiBuf, errorString);
	} else {
		sprintf(buf, "<HTML><HEAD><TITLE>%s</TITLE></HEAD>\n"
			"<BODY>%s<H2>Access Denied</H2>\n"
			"We could not authenticate you based on the certificate that you selected.\n"
			"<BR>Please verify that you are using the correct certificate and try again. \n"
			"<P>If the problem persists please contact the site administrator. \n"
			"<P><B>Error: %s</B></P>"
			"</BODY></HTML>", statusString, errorCgiBuf, statusString);
	}
  len = strlen(buf) + 1;
  
  pFC->WriteClient(pFC, &buf, &len, (DWORD) NULL);
  
  return SF_STATUS_REQ_FINISHED;

}

/**
*  End Change : Infosys
**/

/* returns a newly allocated string. */
char *getRegValue(PHKEY hkey, char *name) {

  static BYTE valueBuf[1024];
  DWORD valueLen = 1024;
  DWORD type = 0;
  char *rStr;
  
  valueBuf[0] = '\0';
  
  if (RegQueryValueEx(*hkey, name,  0, &type, valueBuf, 
                      &valueLen)==ERROR_SUCCESS && type==REG_SZ) {

    /* 0 for strdup is ok. Just like the value is not in the registry. */
    rStr = strdup(valueBuf);
  }
  else {
    rStr = 0;
  }
  
  return rStr;
}


/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved into the generic wrapper.
**/

/*
void vsSleeperThread(void *ptr) {
  
  CVMTIME currentTime = 0;
  int refreshStatus = 0;
  VSVAL_UserCtx ctx = {0};
  char buf[CVM_LARGE_BUF_MAX];
  int rc = 0;

  if (globalLogInfo == 1)
	ctx.logFn = vsValSDKLogMessage;
  else
	ctx.logFn = vsNullValSDKLogMessage;

  while (sleeperRunning) {
*/	
    /* acquire the critical section lock */
/*
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "CRL Thread: Entering CS");
    }
    if (WaitForSingleObject(hMutex, INFINITE)==WAIT_OBJECT_0) {
	
      if (globalLogDebug == 1) {
         vs_cvm_genlib_log_message(VS_LOG_DEBUG, "CRL Thread: Enter CS Success");
      }
*/
      /* See if we have to update all the CRLs based on timer. */
/*
      cvm_time(&currentTime);
	  if (currentTime > (globalLastUpdate + globalUpdateSeconds)) {
	
		  globalLastUpdate = currentTime;	
*/
		  /* Re-get all CRLs. */
/*
		  if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {
*/ 
             /* Ignore errors, but print an error message. */
/*
		      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");
*/
			/* Also print the last error's cause. */
/*
		     if (VSVAL_ErrorString(globalValSDK, buf, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
				sprintf (buf, "Error Code : %d", refreshStatus);
			 }
	         vs_cvm_genlib_log_message(VS_LOG_FAILURE, buf);
		  } else {
			if (globalLogInfo == 1)
				vs_cvm_genlib_log_message(VS_LOG_INFO, "Successfully refreshed certificates and CRLs.");
		  }
	  }
    }
    else {
      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "CRL Thread: Enter CS Error");
    }
*/
    /* And release the mutex. */
/*
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "CRL Thread: Exiting CS");
    }
    if (ReleaseMutex(hMutex)==0) {
      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "CRL Thread: Exit CS Error");
    }
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "CRL Thread: Exit CS Success");
    }
*/
	/* Sleep 1/3 update time. In ms. */
/*
	rc = WaitForSingleObject(hMutexSleep, globalUpdateSeconds * 334);
*/
	/* Make sure the sleep is outside the critical section! */	
/*
  }	
  
}


void vsCheckCertCleanup() {

*/
	/* cleanup --  At_exit... */
/*
	VSVAL_Final (globalValSDK);	
}
*/

/**
*  End Change : Infosys
**/

/**
*  Begin Change : Infosys, 7 Jul 04
*  All Validation SDK Calls moved to generic wrapper.
**/


/* Main entry for crl checking. */
int vsCheckCertInit() {

  int status = 0;
  //char errorString[CVM_LARGE_BUF_MAX];

  char *boolString;
  HKEY hkey;
 
  //char *cfgFilename = 0;
  //char *file_prefix =  0;
  //char *url_prefix =   0;
  //char *cache_dir =    0;
  char *intString = 0;
  char *tmpString = 0;
  char *protectedDirs = 0;
  //char *ocspUrl = 0;
  //char *defaultLdap = 0;
  //char *httpProxy = 0;
  //char *ldapHttpProxy = 0;
  char logDirectory[_MAX_DIR], *tmpPtr = 0;
  //int ldapTimeOut = 0;

    
  //VSVAL_UserCtx ctx = {0};

  CFG_PARAMS cp;

  do {

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     "Software\\VeriSign\\Validate\\2.0", 0, 
                     KEY_READ, &hkey)!=ERROR_SUCCESS) {
		//status = VSVAL_ERR_REGISTRY;
		status = GL_VSVAL_ERR_REGISTRY;
		vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Error opening registry key HKLM\\Software\\VeriSign\\Validate\\2.0 - %d", status);
		break;
    }
    /* Initialize Contexts */
    //if ((status = VSVAL_Init(&globalValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
    //  break;
    //}

    //globalLogName = getRegValue(&hkey, "LogFileName");
	
    //if (globalLogName) {
	  /* try and create the directory if it does not already exist */
	//  tmpPtr = strrchr (globalLogName, '\\');
	//  if (tmpPtr == NULL)
	//	  tmpPtr = strrchr(globalLogName, '/');
	//  if (tmpPtr != 0) {
	//	 strncpy(logDirectory, globalLogName, tmpPtr-globalLogName);
	//	 logDirectory[tmpPtr-globalLogName] = '\0';
	//	 _mkdir(logDirectory);
	//  }	  
      //if ((globalLogFP = fopen(globalLogName, "a"))==0) {
      //  status = VSVAL_ERR_FILE_NOT_OPEN;
      //  break;
      //}
    //}
	cp.logFileName = getRegValue(&hkey, "LogFileName");
	if (cp.logFileName) {
	  /* try and create the directory if it does not already exist */
	  tmpPtr = strrchr (cp.logFileName, '\\');
	  if (tmpPtr == NULL)
		  tmpPtr = strrchr(cp.logFileName, '/');
	  if (tmpPtr != 0) {
		 strncpy(logDirectory, cp.logFileName, tmpPtr-cp.logFileName);
		 logDirectory[tmpPtr-cp.logFileName] = '\0';
		 _mkdir(logDirectory);
	  }	  
    }


	if ( !bIsWindowsVersionOK(4, 0, 0x600) ) {
		vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Incorrect Software Version: You need Windows NT 4.0 with SP6 or Windows 2000 to run VeriSign CVM");
		status = VSVAL_CVM_OS_VERSION;
		break;
	}


	//globalLogInfo = 0;
    //boolString = getRegValue(&hkey, "LogInfo");
	cp.logInfo = getRegValue(&hkey, "LogInfo");
    //if (cvmCfgStringIsOn(boolString)) {
	//	if (globalLogFP != 0)
	//		globalLogInfo = 1;
	//}

	//if (globalLogInfo == 1) {
	//	ctx.logFn = vsValSDKLogMessage;
	//} else {
	//	ctx.logFn = vsNullValSDKLogMessage;
	//}

	globalLogDebug = 0;
    //boolString = getRegValue(&hkey, "LogDebug");
	cp.logDebug = getRegValue(&hkey, "LogDebug");
	if (cvmCfgStringIsOn(cp.logDebug)) {
			globalLogDebug = 1;
	}

    globalIsaInstall = 0;
    boolString = getRegValue(&hkey, "IsaInstall");
    if (cvmCfgStringIsOn(boolString)) {
      globalIsaInstall = 1;
    }

    /* Read options from Registry */  
    //file_prefix =  getRegValue(&hkey, "FilePrefix");
	cp.filePrefix =  getRegValue(&hkey, "FilePrefix");
    //if (file_prefix != 0)
    //  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "file-prefix", file_prefix))
	//	break;

    //url_prefix = getRegValue(&hkey, "UrlPrefix");
	cp.urlPrefix = getRegValue(&hkey, "UrlPrefix");
	//if (url_prefix != 0)
    //  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "url-prefix", url_prefix))
	//	break;

    //cache_dir = getRegValue(&hkey, "CacheDir");
	cp.cacheDir = getRegValue(&hkey, "CacheDir");
    //if (cache_dir != 0)
    //  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "cache_dir", cache_dir))
	//	break;

	//httpProxy = getRegValue(&hkey, "HttpProxy");
	cp.httpProxy = getRegValue(&hkey, "HttpProxy");
    //if (httpProxy != 0)
    // if (status = VSVAL_SetOpt (globalValSDK, &ctx, "http-proxy", httpProxy))
	//	break;

	//ldapHttpProxy = getRegValue(&hkey, "LdapHttpProxy");
	cp.ldapHttpProxy = getRegValue(&hkey, "LdapHttpProxy");
    //if (ldapHttpProxy != 0)
    //  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy))
	//	break;

    if (intString = getRegValue(&hkey, "LdapTimeout")) {
      //ldapTimeOut = atoi(intString);
		cp.ldapTimeOut = atoi(intString);
    }
    else {
      //ldapTimeOut = CVM_LDAP_TIMEOUT;
		cp.ldapTimeOut = -1;
    }
	//if (status = VSVAL_SetIntOpt (globalValSDK, &ctx, "ldap-timeout", ldapTimeOut))
	//	break;

    /* Must be done AFTER proxy configuration */
    //ocspUrl = getRegValue(&hkey, "OcspUrl");
	cp.ocspUrl = getRegValue(&hkey, "OcspUrl");
    //if (ocspUrl != 0)
    //  if (status = VSVAL_SetOpt (globalValSDK, &ctx, "ocsp-url", ocspUrl))
	//	break;	

	//defaultLdap = getRegValue(&hkey, "DefaultLdap");
	cp.defaultLdap = getRegValue(&hkey, "DefaultLdap");
    //if (defaultLdap !=0)
    //  status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", defaultLdap);
    //else
    //  status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", "directory.verisign.com");
    //if (status != 0)
    //  break;


    //boolString = getRegValue(&hkey, "NoCheckChain");

/*  Fix for CR29977 - Begin */
     if ( getRegValue(&hkey, "CheckChain")){
        cp.noCheckChain = getRegValue(&hkey, "CheckChain");
        if (cvmCfgStringIsOn(cp.noCheckChain)){
           cp.noCheckChain = strdup("off");
          }
        else{
           cp.noCheckChain = strdup("on");
          }
     }
     else{
        if ( getRegValue(&hkey, "NoCheckChain")){
           cp.noCheckChain = getRegValue(&hkey, "NoCheckChain");
         }
     
     else{
           cp.noCheckChain = strdup("off");
        } 
    }
/*  Fix for CR29977 - End   */

    //if (cvmCfgStringIsOn(boolString)) 
    //  status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "on");
    //else
    //  status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "off");
    //if (status != 0)
    //  break;

	//globalLogSecurity = 0;
    //boolString = getRegValue(&hkey, "LogSecurity");
	cp.logSecurity = getRegValue(&hkey, "LogSecurity");
    //if (cvmCfgStringIsOn(boolString) && (globalLogFP != 0) ) {
    //  globalLogSecurity = 1;
    //}

    /* get CRL update frequency. */
    if (intString = getRegValue(&hkey, "UpdateSeconds")) {
      //globalUpdateSeconds = atoi(intString);
		cp.updateSeconds = atoi(intString);
    }
    else if (intString = getRegValue(&hkey, "UpdateMinutes")) {
      //globalUpdateSeconds = 60 * atoi(intString);
		cp.updateSeconds = 60 * atoi(intString);
    }
    else if (intString = getRegValue(&hkey, "UpdateHours")) {
      //globalUpdateSeconds = 60 * 60 * atoi(intString);
		cp.updateSeconds = 60 * 60 * atoi(intString);
    }
    else {
      //globalUpdateSeconds = CVM_MAX_UPDATE_TIME;
		cp.updateSeconds = -1;
    }

	/* if one of the above has been set to 0 by mistake, reset globalUpdateSeconds */
	//if (globalUpdateSeconds == 0)
	//	globalUpdateSeconds = CVM_MAX_UPDATE_TIME;


    if (tmpString = getRegValue(&hkey, "ErrorCgi")) {
      if (tmpString && strlen(tmpString)==0) { 
		  globalErrorCgi = 0; 
	  }
      else { 
		  globalErrorCgi = tmpString; 
	  }
    }

    
    /* List of directories to protect. */
    if ((protectedDirs = getRegValue(&hkey, "ProtectedDirs"))==0) {
      protectedDirs = "/"; /* Default to protecting everything. */
    }

    if (status = vsAllocDirList(protectedDirs, &(globalProtectedDirList),
                                &(globalProtectedDirCount))) {
      break;
    }

    
    //cfgFilename = getRegValue(&hkey, "CfgFilename");
	cp.cfgFileName = getRegValue(&hkey, "CfgFilename");
    //if (!cfgFilename || !file_prefix || (!url_prefix && !ocspUrl) || !cache_dir) {
    //  status = VSVAL_ERR_REGISTRY;
    //  break;
    //}

	RegCloseKey(hkey);


    /* check params... make sure there's a trailing / */
    //if (status = VSVAL_ReadConfigFile(globalValSDK, &ctx, cfgFilename)) {
	//	VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
	//	vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", errorString);
	//	status = 0;
		/* you don't want to break because the filter will not load and people will have access to information */
		/* assume that some extra CRL or cert could not be read */
	//}

    /* Print a startup message. */
    //vs_cvm_genlib_log_message(VS_LOG_INFO, "%s starting", FILTER_DESCRIPTION);
	cp.filterDescription = (char *)malloc(SF_MAX_FILTER_DESC_LEN * sizeof(char));
	lstrcpyn(cp.filterDescription, FILTER_DESCRIPTION, SF_MAX_FILTER_DESC_LEN);
	cp.filterDescription[SF_MAX_FILTER_DESC_LEN] = '\0';



    /* Start a thread to do the timer-based CRL updates. */
    //if (globalUpdateSeconds < CVM_MAX_UPDATE_TIME) {
	//  sleeperRunning = 1;
    //  if ((hThread = _beginthread(vsSleeperThread, 0, 0))==-1) {
	//	status = VSVAL_ERR_THREAD;
	//	break;
    //  }
    //}	
  } while (0);


  //if (status) {
	//  if ((status > VSVAL_ERR_BASE) && (status < VSVAL_ERR_MAX)) {
	//	VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
	//	vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", errorString);
	//  }
  //}

  //if (globalLogFP) {
  //  fflush(globalLogFP);
  //}

  /**
  *   Call the generic wrapper init function
  **/
  status = vs_cvm_genlib_init(cp);
  return status;
}


/* Check validity of certificate and put result into shared memory. */
int vsCheckClientCert(HTTP_FILTER_CONTEXT *pFC, int *reqFinished,
                      unsigned char *certData, unsigned int certLen) {

  int status = 0;
  int certStatus = 0;
  char *userName = 0;
  //  CVMTIME currentTime = 0, expireTime = 0;
  //  int refreshStatus = 0;
  //  char refreshStatusString[CVM_LARGE_BUF_MAX];
  //  VSVAL_UserCtx ctx = {0};  

  //if (globalLogInfo == 1)
  //  ctx.logFn = vsValSDKLogMessage;
  //else
  //  ctx.logFn = vsNullValSDKLogMessage;

  //do {

  //  /* See if we have to update all the CRLs based on timer. */
  //  cvm_time(&currentTime);
  //  if (currentTime > (globalLastUpdate + globalUpdateSeconds)) {
	  
  //    globalLastUpdate = currentTime;
  //    if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {
  //      /* Ignore errors, but print an error message. */
  //      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");
	
  //      /* Also print the last error's cause. */
  //	if (VSVAL_ErrorString(globalValSDK, refreshStatusString, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
  //		sprintf (refreshStatusString, "Error Code : %d", refreshStatus);
  //  }
  //	vs_cvm_genlib_log_message(VS_LOG_FAILURE, refreshStatusString);
  //    }
  //  }      

    /* look up the certificate */
  //  status = VSVAL_GetRevocationStatus(globalValSDK, &ctx, certData, certLen, &certStatus, &userName);
    
  //} while (0);


  /**
  *   Call the generic wrapper validate function
  **/
  status = vs_cvm_genlib_validate(certData, certLen, &certStatus, userName, cf);

  if (status) {
    /* Log Errors */
    //VSVAL_ErrorString (globalValSDK, refreshStatusString, VSVAL_BUF_MAX, status, ctx.errorInfo);
    //vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", refreshStatusString);

    /* Log denials? */
    //if (globalLogSecurity && certStatus) {
    //  vs_cvm_genlib_log_message(VS_LOG_SECURITY, "Certificate %s for %s", 
    //               VSVAL_CertStatusString(globalValSDK, certStatus), userName ? userName : "client");
    //}

    /* Invalidate this ssl session for the next call. */
    /* Don't know how to for IIS */

    /* Send an error page */
    vsSendErrorPage(pFC, certStatus, status);
    *reqFinished = 1;
  }
  else {

    //if (certStatus==CS_VALID) {

      /* Set auth-user, etc... */
      /* What does this mean for IIS? */

      /* We'll just append this to the log */
    //  if (globalLogSecurity) {
    //    vs_cvm_genlib_log_message(VS_LOG_ACCESS, "auth-user %s", userName ? userName : "client");
    //  }
    //}
    //else {
    if (certStatus != CS_VALID) {
      /* Log denials? */
    //  if (globalLogSecurity) {
    //    vs_cvm_genlib_log_message(VS_LOG_SECURITY, "Certificate %s for %s", 
    //                 VSVAL_CertStatusString(globalValSDK, certStatus), userName ? userName : "client");
    //  }
      /* Invalidate this ssl session for the next call. */
      /* Don't know how to for IIS */

      /* Send an error page */
      vsSendErrorPage(pFC, certStatus, status);
      *reqFinished = 1;
    }
  }

  //if (userName)
  //  VSVAL_Free (globalValSDK, userName);

  return status;
}

/**
*  End Change : Infosys
**/


/* Private Prototypes */
DWORD HandleEvent_Authentication(HTTP_FILTER_CONTEXT *pFC, 
                              PHTTP_FILTER_AUTHENT pAuthData);
DWORD HandleEvent_UrlMap(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_URL_MAP pUrlData);
DWORD HandleEvent_AuthComplete(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_AUTH_COMPLETE_INFO pAuthComplete);

/* Entry point for ISAPI filter DLL */
BOOL WINAPI GetFilterVersion(HTTP_FILTER_VERSION *pVersion) {

  /* Set version */
  pVersion->dwFilterVersion = HTTP_FILTER_REVISION;

  /* Provide a short description of the filter */
  lstrcpyn(pVersion->lpszFilterDesc, FILTER_DESCRIPTION, SF_MAX_FILTER_DESC_LEN);

  Debug((DEST, pVersion->lpszFilterDesc));

  /* Set the event we want to be notified about and the notification priority */
    pVersion->dwFlags = (SF_NOTIFY_SECURE_PORT |
						 SF_NOTIFY_URL_MAP |
                         SF_NOTIFY_AUTHENTICATION |
                         SF_NOTIFY_AUTH_COMPLETE |
                         SF_NOTIFY_PREPROC_HEADERS |  /* capturing it to fix the bug with ISA. Q330639 */
                         SF_NOTIFY_ORDER_DEFAULT);

/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved to generic wrapper init function
**/

  /* Create a mutex with no initial owner. */

  hMutex = CreateMutex(&saDefaultSecurity, FALSE, VS_MUTEX_NAME);
  if (hMutex==0) {		
    return FALSE;
  }

/*
  hMutexSleep = CreateMutex(&saDefaultSecurity, FALSE, VS_MUTEX_SLEEP_NAME);
  if (hMutexSleep==0) {
    return FALSE;	
  }

  if(WaitForSingleObject(hMutexSleep, 60000)!=WAIT_OBJECT_0) 
    return FALSE;
*/
/**
*  End Change : Infosys
**/

  if (vsCheckCertInit() != 0) {
    return FALSE;
  }

  return TRUE;
}

BOOL WINAPI TerminateFilter(DWORD dwFlags)
{

/**
*  Begin Change : Infosys, 7 Jul 04
*  Moved to generic wrapper exit function
**/

  //if (globalLogDebug == 1)
  //  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "TerminateFilter::");

  /* Wait a few seconds to try and get the mutex. */
  WaitForSingleObject(hMutex, 5000);

  /* Clean things up. */
  if (hMutex) {CloseHandle(hMutex); hMutex =0;}

  //ReleaseMutex(hMutexSleep);
  //  sleeperRunning = 0;
  //Sleep(5000);  /* Wait a while, otherwise other thread will crash */
  //if (hMutexSleep) {CloseHandle(hMutexSleep);hMutexSleep=0;}

  //vsCheckCertCleanup();
    
  //if (globalLogFP) fclose(globalLogFP);
  //globalLogFP = 0;

  /**
  *  Call the generic wrapper exit function
  **/
  vs_cvm_genlib_exit();

/**
*  End Change : Infosys
**/

  return TRUE;
}

/* Entry point for ISAPI filter DLL - this function is where the work is really done */
DWORD WINAPI HttpFilterProc(HTTP_FILTER_CONTEXT *pFC, 
                            DWORD dwNotificationType, VOID *pvData) {

  DWORD dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;

  switch (dwNotificationType) {

  case SF_NOTIFY_AUTHENTICATION:
    dwRet = HandleEvent_Authentication(pFC, (PHTTP_FILTER_AUTHENT)pvData);
    break;
	
  case SF_NOTIFY_AUTH_COMPLETE:
    if (globalIsaInstall)
      dwRet = HandleEvent_AuthComplete(pFC, (PHTTP_FILTER_AUTH_COMPLETE_INFO)pvData);
    break;

  case SF_NOTIFY_PREPROC_HEADERS:
    break;

  case SF_NOTIFY_URL_MAP:
    dwRet = HandleEvent_UrlMap(pFC, (PHTTP_FILTER_URL_MAP)pvData);
    break;

  default:
    break;
  }

  return dwRet;
}



DWORD HandleEvent_UrlMap(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_URL_MAP	 pUrlData) {

  DWORD   dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  unsigned long cookieLen = 500;
  int cookieExists = 0;
  int reqFinished = 0;
  char errorBuf[1024];
  BYTE newCertBuf[10000];
  unsigned int newCertLen=10000;
  CERT_CONTEXT_EX contextEx = {0}; 
  DWORD dwSize = sizeof(contextEx);
  PCERT_CONTEXT  pCertContext; 
  DWORD   dwPCertContextSize = sizeof(PCERT_CONTEXT);

  CHAR resourceName[MAX_BUFF_SIZE];
  DWORD urlBuffSize = MAX_BUFF_SIZE;

  if (globalLogDebug == 1) {
     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Enter");
  }
  /* in case UrlMap is called the second time */
/*  if ( ( pFC->pFilterContext==(void *) VS_RESOURCE_NOT_PROTECTED) ||
	   ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_AND_AUTH) )
	   return dwRet;
 */
if (  pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_AND_AUTH )
	   return dwRet;

  /* Early abort if an unprotected resource. */
  /* Note: We are not looking at the buffer we stored in the filter context in the */
  /* READ_RAW handler.  That was only used to communicate from READ_RAW to */
  /* PREPROC_HEADERS. PREPROC_HEADERS then overwrote that buffer with either */
  /* VS_RESOURCE_PROTECTED or NOT_PROTECTED. */
  if (!pFC->GetServerVariable (pFC, "URL", resourceName, &urlBuffSize)) {
	  if (globalLogDebug == 1)
		  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Error in getting request URL.");
	  return vsSendErrorPage(pFC, 103, 0);
  }

  /* Normalize the url. VERY IMPORTANT!  If we don't do this, urls */
  /* like //ssc/page.htm will not match /ssc/ in the protected dirs list. */
  pFC->ServerSupportFunction(pFC, SF_REQ_NORMALIZE_URL, resourceName, urlBuffSize, 0);
  if (globalLogDebug == 1)
	  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "Request for resource - %s", resourceName);
  /* Now we use the filter context to tell if this is a protected resource. */
  /* This is always done. It overwrites the previous buffer. */
  if (!vsDirIsProtected(resourceName, globalProtectedDirList, globalProtectedDirCount)) {
	pFC->pFilterContext = (void *) VS_RESOURCE_NOT_PROTECTED;
    if (globalLogDebug == 1)
	  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Resource %s is not protected. falling through", resourceName);
	return dwRet;
  } else
	  pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED;

		
  /* Get the mutex. */
  if (globalLogDebug == 1) {
     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Waiting for CS");
  }
  if (WaitForSingleObject(hMutex, INFINITE)==WAIT_OBJECT_0) {

    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Enter CS Success");
    }

    if (!globalIsaInstall) {

	  /* Give the get_cert fn a pointer to a buf and a 0 len. */
	/* It will return us the needed len. */
	contextEx.CertContext.pbCertEncoded = (BYTE*)newCertBuf;
	contextEx.cbAllocated = newCertLen;

	if (!pFC->ServerSupportFunction(pFC, (enum SF_REQ_TYPE)HSE_REQ_GET_CERT_INFO_EX, 
                                   (LPVOID)&contextEx, (ULONG_PTR)dwSize, (ULONG_PTR) NULL) )	{

		vsGetLastErrorISAPI(errorBuf);	
	        /* And release the mutex. */
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exiting CS");
                }
	        if (ReleaseMutex(hMutex)==0) {
                    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "URL_MAP: Exit CS Error");
		    return vsSendErrorPage(pFC, 103, 0);	
	        }    
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exit CS Success");
                }
		return vsSendErrorPage(pFC, 103, 0);	
	} else {
		  newCertLen = contextEx.CertContext.cbCertEncoded;
	}
    }
    else {

	    __try {


		  if (!pFC->GetServerVariable(pFC, "CERT_CONTEXT", &pCertContext, &dwPCertContextSize))
		  {

			vsGetLastErrorISAPI(errorBuf);    
			vs_cvm_genlib_log_message (VS_LOG_FAILURE, "handle_url_map: Could not get cert_context - %s", errorBuf);
	               /* And release the mutex. */
                       if (globalLogDebug == 1) {
                          vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exiting CS");
                       }
	               if (ReleaseMutex(hMutex)==0) {
                           vs_cvm_genlib_log_message(VS_LOG_FAILURE, "URL_MAP: Exit CS Error");
		           return vsSendErrorPage(pFC, 103, 0);	
	               }    
                       if (globalLogDebug == 1) {
                          vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exit CS Success");
                       }
		       return vsSendErrorPage(pFC, 103, 0);    
		  } else {
			if (globalLogDebug == 1)
			  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Got Cert Context, cert len - %d", pCertContext->cbCertEncoded);

			newCertLen = pCertContext->cbCertEncoded;
			memcpy(newCertBuf, pCertContext->pbCertEncoded, newCertLen);
		  }

		}
		__except(1)
		{
			if (globalLogDebug == 1)
			  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Could not get cert context");

			newCertLen = 0;
		}

	}

	if (newCertLen == 0) {
		  pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED_BUT_NO_AUTH;
		  if (globalLogDebug == 1)
			vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Could not get client certificate in URL_MAP");
	}
	else {
		if (globalLogDebug == 1)
			vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Got client certificate, length = %d", newCertLen);
		if (vsCheckClientCert(pFC, &reqFinished, newCertBuf, newCertLen) || reqFinished ) {
			pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL;
			dwRet = SF_STATUS_REQ_FINISHED;
			if (globalLogDebug == 1)
				vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: client certificate validation failed");

		} else
			pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED_AND_AUTH;
	}

	/* And release the mutex. */
        if (globalLogDebug == 1) {
           vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exiting CS");
        }
	if (ReleaseMutex(hMutex)==0) {
            vs_cvm_genlib_log_message(VS_LOG_FAILURE, "URL_MAP: Exit CS Error");
	    return vsSendErrorPage(pFC, 103, 0);
	}    
        if (globalLogDebug == 1) {
           vs_cvm_genlib_log_message(VS_LOG_DEBUG, "URL_MAP: Exit CS Success");
        }
  }
  else { 
    /* mutex error */ 
    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "URL_MAP: Enter CS Error");
    return vsSendErrorPage(pFC, 104, 0);
  }

  return dwRet;
}



DWORD HandleEvent_Authentication(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_AUTHENT pAuthData) {

  DWORD   dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  unsigned long cookieLen = 500;
  int cookieExists = 0;
  int reqFinished = 0;
  char errorBuf[1024];
  BYTE newCertBuf[10000];
  unsigned int newCertLen=10000;
  CERT_CONTEXT_EX contextEx = {0}; 
  DWORD dwSize = sizeof(contextEx);
  PCERT_CONTEXT  pCertContext; 
  DWORD   dwPCertContextSize = sizeof(PCERT_CONTEXT);

  /* Fix for C196028 - Start */
  /* vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Enter"); */
  /* Fix for C196028 - End */
  if ( pFC->pFilterContext==(void *) VS_RESOURCE_NOT_PROTECTED) {
	  if (globalLogDebug == 1)
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Resource is not protected or already authenticated VS_RESOURCE_NOT_PROTECTED");
	  return dwRet;
  }

  if ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_AND_AUTH) {
     if (globalLogDebug == 1)
	vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Resource is not protected or already authenticated VS_RESOURCE_PROTECTED_AND_AUTH");
        return dwRet;
  }
 
  if ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL)  {
	  if (globalLogDebug == 1)
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Resource is not protected or already authenticated VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL");
	  return dwRet;
  }

  memset(errorBuf, 0, 1024);
  /* Get the mutex. */
  if (globalLogDebug == 1) {
     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Waiting for CS");
  }
  if (WaitForSingleObject(hMutex, INFINITE)==WAIT_OBJECT_0) {

    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Enter CS Success");
    }
    if (!globalIsaInstall) {
	  /* Give the get_cert fn a pointer to a buf and a 0 len. */
	/* It will return us the needed len. */
	contextEx.CertContext.pbCertEncoded = (BYTE*)newCertBuf;
	contextEx.cbAllocated = newCertLen;

	if (!pFC->ServerSupportFunction(pFC, (enum SF_REQ_TYPE)HSE_REQ_GET_CERT_INFO_EX, 
                                   (LPVOID)&contextEx, (ULONG_PTR)dwSize, (ULONG_PTR) NULL) )	{
		vsGetLastErrorISAPI(errorBuf);	
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "AUTH-EVENT: Could not get certificate - %s", errorBuf);
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "Please check that you checked Require Client Certificates in IIS Directory Security Tab");
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "You can also get this error if you installed IIS after installing SP6. You will need to reinstall SP6+");
	        /* And release the mutex. */
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exiting CS");
                }
	        if (ReleaseMutex(hMutex)==0) {
                    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTH-EVENT: Exit CS Error");
		    return vsSendErrorPage(pFC, 103, 0);	
	        }    
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exit CS Success");
                }
		return vsSendErrorPage(pFC, 103, 0);	
	} else {
		  newCertLen = contextEx.CertContext.cbCertEncoded;
	}
    }
    else {

	    __try {

		  if (!pFC->GetServerVariable(pFC, "CERT_CONTEXT", &pCertContext, &dwPCertContextSize))
		  {
			vsGetLastErrorISAPI(errorBuf);    
			vs_cvm_genlib_log_message (VS_LOG_FAILURE, "AUTH-EVENT: Could not get cert_context - %s", errorBuf);
	                /* And release the mutex. */
                        if (globalLogDebug == 1) {
                           vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exiting CS");
                        }
	                if (ReleaseMutex(hMutex)==0) {
                            vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTH-EVENT: Exit CS Error");
		            return vsSendErrorPage(pFC, 103, 0);	
	                }    
                        if (globalLogDebug == 1) {
                           vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exit CS Success");
                        }
			return vsSendErrorPage(pFC, 103, 0);    
		  } else {

			if (globalLogDebug == 1)
			  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Got Cert Context, cert len - %d", pCertContext->cbCertEncoded);

			newCertLen = pCertContext->cbCertEncoded;
			memcpy(newCertBuf, pCertContext->pbCertEncoded, newCertLen);
		  }
		}
		__except(1)
		{
			if (globalLogDebug == 1)
			  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Could not get cert context");

			newCertLen = 0;
		}

    }


	if (newCertLen == 0) {
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "AUTH-EVENT: Could not get certificate - %s", errorBuf);
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "Please check that you checked Require Client Certificates in IIS Directory Security Tab");
		vs_cvm_genlib_log_message (VS_LOG_FAILURE, "You can also get this error if you installed IIS after installing SP6. You will need to reinstall SP6+");
	        /* And release the mutex. */
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exiting CS");
                }
	        if (ReleaseMutex(hMutex)==0) {
                    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTH-EVENT: Exit CS Error");
		    return vsSendErrorPage(pFC, 103, 0);	
	        }    
                if (globalLogDebug == 1) {
                   vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exit CS Success");
                }
		return vsSendErrorPage(pFC, 103, 0);
	}

	if (globalLogDebug == 1)
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Got client certificate, length - %d", newCertLen);

	if (vsCheckClientCert(pFC, &reqFinished, newCertBuf, newCertLen) || reqFinished ) {
			dwRet = SF_STATUS_REQ_FINISHED;
			if (globalLogDebug == 1)
				vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: client certificate validation failed");
	}	

	/* And release the mutex. */
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exiting CS");
    }
    if (ReleaseMutex(hMutex)==0) {
        vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTH-EVENT: Exit CS Error");
	return vsSendErrorPage(pFC, 103, 0);
    }    
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTH-EVENT: Exit CS Success");
    }
  }
  else { 
    /* mutex error */ 
    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTH-EVENT: Enter CS Error");
    return vsSendErrorPage(pFC, 104, 0);
  }

  return dwRet;
}


DWORD HandleEvent_AuthComplete(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_AUTH_COMPLETE_INFO pAuthInfo)
{
  DWORD   dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  int     reqFinished = 0;
  char    errorBuf[1024];
  unsigned int newCertLen=10000;
  PCERT_CONTEXT  pCertContext; 
  DWORD   dwSize = sizeof(PCERT_CONTEXT);

  if (globalLogDebug == 1) {
     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Enter");
  }

  if ( pFC->pFilterContext==(void *) VS_RESOURCE_NOT_PROTECTED) {
	  if (globalLogDebug == 1)
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Resource is not protected or already authenticated VS_RESOURCE_NOT_PROTECTED");
	  return dwRet;
  }

  if ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_AND_AUTH) {
     if (globalLogDebug == 1)
	vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Resource is not protected or already authenticated VS_RESOURCE_PROTECTED_AND_AUTH");
        return dwRet;
  }
 
  if ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL)  {
	  if (globalLogDebug == 1)
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Resource is not protected or already authenticated VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL");
	  return dwRet;
  }

/*
  if (( pFC->pFilterContext==(void *) VS_RESOURCE_NOT_PROTECTED) ||
      ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_AND_AUTH) ||
      ( pFC->pFilterContext==(void *) VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL))
  {
    if (globalLogDebug == 1)
      vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Resource is not protected or already authenticated");
    return dwRet;
  }
*/

  memset(errorBuf, 0, 1024);

  if (globalLogDebug == 1) {
     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Waiting for CS");
  }
  /* Get the mutex. */
  if (WaitForSingleObject(hMutex, INFINITE)==WAIT_OBJECT_0)
  {
        if (globalLogDebug == 1) {
           vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Enter CS Success");
        }

	__try {

		if (!pFC->GetServerVariable(pFC, "CERT_CONTEXT", &pCertContext, &dwSize))
		{

		  vsGetLastErrorISAPI(errorBuf);    
		  vs_cvm_genlib_log_message (VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Could not get certificate - %s", errorBuf);
		  vs_cvm_genlib_log_message (VS_LOG_FAILURE, "Please check that you enabled SSL Listner and Checked Client Certificate Authentication in ISA Incoming Web Request Tab");
		  vs_cvm_genlib_log_message (VS_LOG_FAILURE, "You can also get this error if you do not have ISA SP1 and hotfix for Q319375 installed.");
	          /* And release the mutex. */
                  if (globalLogDebug == 1) {
                     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exiting CS");
                  }
	          if (ReleaseMutex(hMutex)==0) {
                      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Exit CS Error");
		      return vsSendErrorPage(pFC, 103, 0);	
	          }    
                  if (globalLogDebug == 1) {
                     vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exit CS Success");
                  }
		  return vsSendErrorPage(pFC, 103, 0);    
	         } else {
			if (globalLogDebug == 1)
			  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Got Cert Context, cert len - %d", pCertContext->cbCertEncoded);

		  newCertLen = pCertContext->cbCertEncoded;
		}

	}
	__except(1)
     {
		if (globalLogDebug == 1)
		  vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Could not get cert context");

		newCertLen = 0;
     }

    if (newCertLen == 0)
    {
      vs_cvm_genlib_log_message (VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Could not get certificate - ");
      vs_cvm_genlib_log_message (VS_LOG_FAILURE, "Please check that you enabled SSL Listner and Checked Client Certificate Authentication in ISA Incoming Web Request Tab");
      vs_cvm_genlib_log_message (VS_LOG_FAILURE, "You can also get this error if you do not have ISA SP1 and hotfix for Q319375 installed.");
      /* And release the mutex. */
      if (globalLogDebug == 1) {
         vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exiting CS");
      }
      if (ReleaseMutex(hMutex)==0) {
          vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Exit CS Error");
          return vsSendErrorPage(pFC, 103, 0);	
      }    
      if (globalLogDebug == 1) {
         vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exit CS Success");
      }
      return vsSendErrorPage(pFC, 103, 0);
    }

    if (globalLogDebug == 1)
      vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Got client certificate, length - %d", newCertLen);

    if (vsCheckClientCert(pFC, &reqFinished, pCertContext->pbCertEncoded, newCertLen) || reqFinished ) {
		pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED_BUT_AUTH_FAIL;

	    dwRet = SF_STATUS_REQ_FINISHED;
		if (globalLogDebug == 1)
			vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: client certificate validation failed");

    } else
		pFC->pFilterContext = (void *) VS_RESOURCE_PROTECTED_AND_AUTH;
		
    /* And release the mutex. */
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exiting CS");
    }
    if (ReleaseMutex(hMutex)==0) {
      vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Exit CS Error");
      return vsSendErrorPage(pFC, 103, 0);
    }    
    if (globalLogDebug == 1) {
       vs_cvm_genlib_log_message(VS_LOG_DEBUG, "AUTHCOMPLETE-EVENT: Exit CS Success");
    }
  }
  else { 
    /* mutex error */ 
    vs_cvm_genlib_log_message(VS_LOG_FAILURE, "AUTHCOMPLETE-EVENT: Enter CS Error");
    return vsSendErrorPage(pFC, 104, 0);
  }

  return dwRet;
}


/* DLL main function is executed on DLL loading and unloading. Note that
   that if IIS has cached the DLL then this will only be called the first
   time the DLL is loaded and when it is unloaded. */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dvReason, LPVOID lpv) {

  CHAR    ModuleName[BUFF_MAX+1];
  static HANDLE hMapFile = 0;
  static LPVOID lpMapAddress = 0;

  switch (dvReason) {

  case DLL_PROCESS_ATTACH:

    GetModuleFileName(NULL, ModuleName, BUFF_MAX);
    GetModuleFileName(hinstDLL, ModuleName, BUFF_MAX);

    break;

  case DLL_PROCESS_DETACH:
    break;
  case DLL_THREAD_ATTACH:
    break;
  case DLL_THREAD_DETACH:
    break;
  }

  return TRUE;
}


