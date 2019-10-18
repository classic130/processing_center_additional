
/****************************************************************************************
* 
* isapissc.c
* -----
* This is file that implements the IIS filter for the PTA server
*
* Author - Siddharth Bajaj 03/03/01
* 
* Change History
* - Modified code to fix issue with posting lot of data. Filter was not handling
*	the requests that come in multiple ReadRawdata notifications properly -	 Sasidhar Gogineni 03/19/03
* -
*
*****************************************************************************************/


#define WIN32_LEAN_AN_MEAN
//artf14514: Changes Begin
//#define DEBUGMSG 1
#define IIS6 0x00060000
#define IIS5 0x00040000
//artf14514: Changes End

#include <windows.h>
#include <httpfilt.h>
#include <process.h> /* for beginthread */

/* From ISAPI/NSAPI book. */
#include <debug.h> /* debug macro */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time.h"
#include "pta.h"

#include "escape.h"

/* different mutex names */
#define VS_MUTEX_NAME "verisign_ssc_mutex"
#define VS_LOG_MUTEX_NAME "verisign_ssc_log_mutex"
#define VS_THREAD_MUTEX_NAME "verisign_ssc_thread_mutex"

#define LOG_FAILURE "error"
#define LOG_SECURITY "security"
#define LOG_WARN "warning"
#define LOG_INFORM "info"
#define LOG_ACCESS "access"

/* FIX ALL // COMMENTS !!! */

/*******************************************************************************
**
** Data Structures
**
********************************************************************************/
/*  REQUESTINFO holds extra information about the request/response that we
    keep for the duration of the request. A pointer to this is
    stored in the HTTP_FILTER_CONTEXT->pFilterContext. */

typedef struct _REQUESTINFO {
  LPSTR           lpszHeader;         /* A pointer to a saved request header */
  DWORD           lpszHeaderLen;         /* strlen() of above. */

  char contentType[PTA_TINY_BUF_MAX];  /* the client content-type header. */
  char *rqUri; /* the client's uri. T_malloc. */

  DWORD           cbPostLen; /* Content length of original post */
  DWORD           cbPostAccumulated; /* Content length of post we've read so far.*/

  LPSTR           pRequestPost;           /* A copy of the request message POST*/

  BOOL            bIsProtected;         /* Is the URL in our target list? */
  BOOL            bKeepAlive;         /* Is this a keep-alive connection or not? */

  BOOL            bGotHeader;        /* TRUE after we've captured the response header */
  BOOL            bDoneWithHeaders;  /* are we up to the body of the response yet? */

  BOOL            bSentHeader; /* Have we already sent the header w/ the response body?*/
  BOOL            bSentPage; /* have we sent a disk file page? */
  BOOL            bIsMSIE;  /* does the user-agent include the text "MSIE"? */

  BOOL            bDoReadRaw2; /* Did we only get the headers on the first read raw? */

  ITEM prePageJs;
  ITEM page;
  
  /* Instead of pblock_nvreplace, put them here: (T_malloc) */
  char *sscStatus;
  char *validPost;
  char *adminOp;
  char *oldUri;
  /* artf14514: Changes Begin : This is to keep track if the SF_NOTIFY_PREPROC_HEADERS 
				notification was called before or after ReadRawData2*/
	
  BOOL bPreProcSkipped;
  /* artf14514: Changes End */

}  REQUESTINFO, *PREQUESTINFO;


/*******************************************************************************
**
** Function prototypes 
**
********************************************************************************/
/* This function VSUnwrapCertificate is implemented in isapiCDR.c, used to parse
* and add certificate details in the request headers 
*/
int VSUnwrapCertificate(HTTP_FILTER_CONTEXT *pFC, 
                            PHTTP_FILTER_PREPROC_HEADERS pPreProcData, char *certB64);

/* This is the function that can be used to do revocation checking
* This is called by vsPTAAuthorizePost to check the status of the cert
* Pre-declare this fn so we can set a pointer to it in gCfg */
int vsIsapiGetRevocationInfo(ITEM *certItem, int *certStatus,
                             PTATIME *statusExpires, char **userName);

/* Private Prototypes */
int vsPTADoAuthorization(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo,
                      char **pHascKey, client_data_t **pClientData, 
                      int *pCertStatus, char **pNewUrl, char *uri);

DWORD vsEvalStatus(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_PREPROC_HEADERS pPreProcData,
                   PREQUESTINFO pReqInfo, DWORD initialRC, 
                   char *cookieVal, char *uri, char *hascKey, char *adminOp,
                   char *newUrl, int certStatus, client_data_t *clientData);

/* Server event handlers */
DWORD HandleEvent_SendRawData(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pSendData);
DWORD HandleEvent_ReadRawData(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pReadData);
DWORD HandleEvent_PreProcHeaders(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_PREPROC_HEADERS pPreProcData);
DWORD HandleEvent_EndOfNetSession(HTTP_FILTER_CONTEXT *pFC);
DWORD HandleEvent_Log(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_LOG pLogData);

/* Support functions */
DWORD   HandleResponseHeader(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pSendData);
DWORD   HandleResponseBody(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pSendData);
INT	    ExtractContentLength(LPSTR lpszHeader, int len);



/*****************************************************************
* Globals 
******************************************************************/

/* gCfg is defined pta.c */
/* VS_PTA_CONFIG gCfg = { 0 }; */

/* pointer to log file, should be protected using a mutex */
FILE *globalLogFP = 0;

/* mutexes */
HANDLE hMutex = 0;
/* HANDLE hCvmMutex = 0; */
HANDLE hLogMutex = 0;
HANDLE hThreadMutex = 0;

/* thread related variables */
unsigned long hThread = 0;
int volatile endThread = 0;

//artf14514: Changes Begin
DWORD IISVERSION;
//artf14514: Changes End

/****************************************************************************************
* 
* Function:  vsLogInfoMessage
* 
* This is the function that is used to log errors and warnings coming out of the 
* Validation SDK. Specify this function to initialize the VSVAL_UserCtx structure.
*
* Parameters -
* handle (IN) - you can specify a handle which will be returned by the validation
*               SDK. not used.
* fmt (IN) - format of the log message
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/

void vsLogInfoMessage(void *handle, char *fmt, ...) {
  char infoBuf[PTA_LARGE_BUF_MAX];
  PTATIME currentTime;
  char *timeBuf = 0;
  va_list ap;
  va_start(ap, fmt);

  if (globalLogFP==0) return;
  if (WaitForSingleObject(hLogMutex, INFINITE)==WAIT_OBJECT_0) {
    (void) vsprintf(infoBuf, fmt, ap);
    va_end(ap);

    pta_time(&currentTime);
    timeBuf = asctime(localtime((const time_t *) &currentTime));
    pta_make_newline_null(timeBuf);

    fprintf(globalLogFP, "[%s] info: %s\n", timeBuf, infoBuf);
#ifdef DEBUGMSG
	fflush(globalLogFP);
#endif
    ReleaseMutex(hLogMutex);
  }

  return;
}


/****************************************************************************************
* 
* Function:  vsLogMessage
* 
* This is the function that is used to log errors and warnings in the ISAPI filter
* You can specify the severity for the different log messages
*
* Parameters -
* severity (IN) - severity level to be included in the log string, possible values 
*                 include LOG_FAILURE, LOG_SECURITY, LOG_WARN, LOG_INFORM, LOG_ACCESS
* fmt (IN) - format of the log message
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/

void vsLogMessage(char *severity, char *fmt, ...) {

  char infoBuf[PTA_LARGE_BUF_MAX];
  PTATIME currentTime;
  char *timeBuf = 0;
  va_list ap;
  va_start(ap, fmt);

  if (globalLogFP==0) return;
  if (WaitForSingleObject(hLogMutex, INFINITE)==WAIT_OBJECT_0) {

    (void) vsprintf(infoBuf, fmt, ap);
    va_end(ap);

    pta_time(&currentTime);
    timeBuf = asctime(localtime((const time_t *) &currentTime));
    pta_make_newline_null(timeBuf);

    fprintf(globalLogFP, "[%s] %s: %s\n", timeBuf, severity, infoBuf);
#ifdef DEBUGMSG
	fflush(globalLogFP);
#endif
    ReleaseMutex(hLogMutex);
  }

  return;
}



/****************************************************************************************
* 
* Function:  reg_findval
* 
* This returns the pointer to a newly allocated value string for the key specified
*
* Parameters -
* name (IN) - name of the option to find in the registry
* phkey (IN) - pointer to an open registry key
*
* Return values : pointer to a newly allocated string containing the value
*                 0, if the name could not be found
* 
* Change History
* -
* -
*
*****************************************************************************************/

/* returns a newly allocated string. */
char *reg_findval(const char *name, PHKEY phkey) {

  BYTE valueBuf[1024];
  DWORD valueLen = 1024;
  DWORD type = 0;
  char *rStr;
  
  valueBuf[0] = '\0';
  
  if (RegQueryValueEx(*phkey, name,  0, &type, valueBuf, 
                      &valueLen)==ERROR_SUCCESS && type==REG_SZ) {
    
    rStr = sscT_strdup(valueBuf);
  }
  else {
    rStr = 0;
  }
  
  return rStr;
}

/****************************************************************************************
* 
* Function:  vs_reg_findint
* 
* This returns the integer value corresponding to a specified configuration option
*
* Parameters -
* name (IN) - name of the option to find in the registry
* phkey (IN) - pointer to an open registry key
* defaultVal (IN) - the default value if the registry key could not be found
*
* Return values : integer containing the value for option 'name'
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vs_reg_findint(const char *name, PHKEY phkey, int defaultVal) {
  
  char *value = 0;
  int intVal;

  value = reg_findval(name, phkey);

  if (value) { intVal = atoi(value); }
  else { intVal = defaultVal; }

  sscT_free(value);

  return intVal;
}


/****************************************************************************************
* 
* Function:  vs_reg_ison
* 
* This function checks if a particular option is turned on in the registry
*
* Parameters -
* name (IN) - name of the option to find in the registry
* phkey (IN) - pointer to an open registry key

* Return values : 0 - the option is off in the registry
*				  1 - the option is on in the registry
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vs_reg_ison(const char *name, PHKEY phkey) {
  
  char *value = 0;
  int isOn;

  value = reg_findval(name, phkey);

  isOn = ptaCfgStringIsOn(value);
  
  sscT_free(value);

  return isOn;
}


/****************************************************************************************
* 
* Function:  vs_reg_findstr
* 
* This function returns the value for a particular string option from the registry
*
* Parameters -
* name (IN) - name of the option to find in the registry
* phkey (IN) - pointer to an open registry key
* value (OUT) - the string value for that option. 
*
* NOTE: this returns a newly allocated string so you need to free it.
* 
* Return values : pointer to the newly allocated string
*                 0 - if value could not be found
* 
* Change History
* -
* -
*
*****************************************************************************************/
char *vs_reg_findstr(const char *name, PHKEY phkey, char **value) {
  
  char *val = 0;

  val = reg_findval(name, phkey);

  if (val && val[0]) {
    return (*value = val);
  }

  return 0;
}


/****************************************************************************************
* 
* Function:  vs_reg_findmatch
* 
* This function checks if the value for a  particular option in the registry 
* matches a particular value 
*
* Parameters -
* name (IN) - name of the option to find in the registry
* phkey (IN) - pointer to an open registry key
* value (IN) - the value to match against
*
* Return values : 1 - the option value matches 'value'
*				  0 - no match was found
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vs_reg_findmatch(const char *name, PHKEY phkey, char *value) {
  
  char *tmp = 0;
  int match = 0;

  if (vs_reg_findstr(name, phkey, &tmp)) {
    match = (strcmp(tmp, value)==0);
  }
  
  sscT_free(tmp);

  return match;
}


/****************************************************************************************
* 
* Function:  vsAllocDirList
* 
* Given a string of directories, separated by ";" characters, parse it into a list
* N-PLACE!! Replaces each ';' with a null character. May create NULL strings.
*
* Parameters -
* string (IN) - string containing the ';' separated list of directories
* dirList (OUT) - array of pointers to individual directory list
* dirCount (OUT) - the number of directories in the list
*
* Return values : VS_ERR_NO_MEM - if memory cannot be allocated for dirList
*				  0 - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
/* Given a string of directories, separated by ";" characters, parse it into a list */
/* IN-PLACE!! Replaces each ';' with a null character. May create NULL strings. */
int vsAllocDirList(char *string, char ***dirList, int *dirCount) {

  int count, i;
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
  A = (char **) sscT_malloc(sizeof(char *) * count);
  if (A==0) return VS_ERR_NO_MEM;

  /* Now chop out the names */
  i = 0;
  A[0] = string;
  for (p=string; *p; p++) {
    if (*p == ';') {
      *p = 0;
      i++;
      A[i] = p+1;
    }
  }

  *dirList = A;
  *dirCount = count;

  return 0;
}


/****************************************************************************************
* 
* Function:  vsDirIsProtected
* 
* Function checks if the requested URI is protected or not
* true IFF an entry in dirList is a prefix of 'string'. 
* 
* Parameters -
* string (IN) - string containing complete URI
* dirList (IN) - array of pointers to individual directory list
* dirCount (IN) - the number of directories in the list
* handle (IN) - the HTTP_FILTER_CONTEXT
*
* Return values : 1 - URI is protected
*				  0 - URI is not protected
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsDirIsProtected(char *string, char **dirList, int dirCount, HTTP_FILTER_CONTEXT *handle) {

  int i, inList = 0;
  char uri[PTA_LARGE_BUF_MAX];
  int uriLen = PTA_LARGE_BUF_MAX;
  strcpy(uri,string);
  /* Normalize the url. VERY IMPORTANT!  If we don't do this, a user who */
    /* goes to //ssc/page.htm will get in without authentication since it */
    /* won't match anything in the protected dirs list. */
  handle->ServerSupportFunction(handle, SF_REQ_NORMALIZE_URL, uri, uriLen, 0);

  if (uri) {
    _strlwr(uri);
    for (i=0; i<dirCount; i++) {
      if (*(dirList[i]) && strstr(uri, dirList[i])==uri) {
        inList = 1;
        break;
      }
    }
  }

#ifdef DEBUGMSG
  Debug((DEST, "is %s protected, %d", string ? string : "(nil)", inList));
  gCfg.InfoLog(0, "is %s protected, %d", string ? string : "(nil)", inList);
#endif

  return inList;
}


/****************************************************************************************
* 
* Function:  setCookie
* 
* Function adds the cookie header to the response headers. This can be used to set/delete
* cookies from the browser
*
* Parameters -
* pFC (IN) - pointer to the HTTP_FILTER_CONTEXT
* cookieVal (IN) - the value of the cookie
* delete (IN) - whether the cookie is to be deleted or set
*
* Return values : 0 - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
int setCookie(HTTP_FILTER_CONTEXT *pFC, char *cookieVal, int delete) {

  char cookie_str[PTA_LARGE_BUF_MAX];
  char header_str[PTA_LARGE_BUF_MAX];

//artf14514: Changes Begin
  PREQUESTINFO pReqInfo = (PREQUESTINFO)pFC->pFilterContext;
  LPSTR           lpszTemp;
//artf14514: Changes End
  vsPTAGetCookieHeader(cookie_str, cookieVal, delete);

  sprintf(header_str, "Set-Cookie: %s\r\n", cookie_str);


//artf14514: Changes Begin
  if(IISVERSION == IIS5)
  	{
	  pFC->AddResponseHeaders(pFC, header_str, 0);
  	}
  else if(IISVERSION == IIS6)
  	{
		  if(pReqInfo) {
			  if(pReqInfo->lpszHeaderLen > 0) {
				  lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
				  memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
				  pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen(header_str), 0);
				  memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
			  } else
				  pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen(header_str), 0);
			  memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, header_str, strlen(header_str));
			  pReqInfo->lpszHeaderLen += strlen(header_str);
#ifdef DEBUGMSG
			  gCfg.InfoLog(0, "****Set Cookie=%s", cookie_str); 
#endif
		  } else {
#ifdef DEBUGMSG
			    gCfg.InfoLog(0, "Request Info is NULL");
#endif
		}
  	}
//artf14514: Changes End

  return 0;
}


/****************************************************************************************
* 
* Function:  findMyCookie
* 
* Function finds the PTA cookie value in the request headers. If found it is copied in
* cookieVal. The cookie value is stored in gCfg.cookieName
*
* Parameters -
* pFC (IN) - pointer to the HTTP_FILTER_CONTEXT
* pPreProcData (IN) - PHTTP_FILTER_PREPROC_HEADERS
* cookieVal (OUT) - if PTA cookie is found, the value or NULL
*
* Return values : 0 - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
int findMyCookie(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_PREPROC_HEADERS pPreProcData, 
                 char *cookieVal) {

  int status = 0;
  char cookie[PTA_LARGE_BUF_MAX];
  DWORD cookieLen = PTA_LARGE_BUF_MAX;

  char *name, *value;
  char *ptr;
  int fInValue = 0;
  int done = 0;

  do {

    cookie[0] = '\0';
    cookieVal[0] = '\0';
    pPreProcData->GetHeader(pFC, "Cookie:", cookie, &cookieLen);

    // This part should be shared between ns/ms versions. */
    if (cookie[0]) {

      /* Code taken from cookie.c. */
      ptr = cookie;
      while(*ptr && isspace(*ptr))
        ptr++;
      name = ptr;
      while(!done) {
        switch(*ptr) {
        case '=':
          if (!fInValue) {
            *ptr = '\0';
            ptr++;
            while(*ptr && isspace(*ptr)) 
              ptr++;
            value = ptr;
            fInValue = 1;
          }
          break;
        case '\0':
        case ';':
          if (fInValue) {
            if (*ptr) {
              *ptr = '\0';
              ptr++;
              while(*ptr && isspace(*ptr)) 
                ptr++;
              if (!ptr)    /* don't go past edge */
                ptr--;
            } else  
              done = 1;

            /* Instead of putting it into a pblock, return it if it matches. */
            if (strcmp(gCfg.cookieName, name)==0) {
              sprintf(cookieVal, value);
            }

            name = ptr;
            fInValue = 0;
          }
          break;
        }
        ptr++;
      }

    }

  } while (0);


  return status;
}


/****************************************************************************************
* 
* Function:  printCookies
* 
* Function prints all the cookies that are in the request headers to the PTA log file, if
* DEBUGMSG is set 
* 
* Parameters -
* pFC (IN) - pointer to the HTTP_FILTER_CONTEXT
* pPreProcData (IN) - PHTTP_FILTER_PREPROC_HEADERS
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/
void printCookies(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_PREPROC_HEADERS pPreProcData) {

  char cookie[PTA_LARGE_BUF_MAX];
  DWORD cookieLen = PTA_LARGE_BUF_MAX;

  cookie[0] = '\0';
  pPreProcData->GetHeader(pFC, "Cookie:", cookie, &cookieLen);

#ifdef DEBUGMSG
  if (cookieLen==0){
    gCfg.InfoLog(0, "No cookies");
  }
  else {
    gCfg.InfoLog(0, "cookies=%s", cookie);
  }
#endif

}



/****************************************************************************************
* 
* Function:  vsSleeperThread
* 
* This is the function that loops in a separate thread and it refreshes all the certs and
* CRLs. 
* 
* Parameters -
* ptr (IN) - ??
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/
void vsSleeperThread(void *ptr) {
  
  PTATIME currentTime = 0;
  int refreshStatus = 0;
  char *refreshStatusString = 0;

  VSVAL_UserCtx ctx = {0};
  char buf[PTA_LARGE_BUF_MAX];
  DWORD mutexStatus;

  ctx.logFn = gCfg.InfoLog;

  while (1) {

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: in sleeper"));
    gCfg.InfoLog(0, "isapi_ssc: in sleeper");
#endif

	/* See if we have to update all the CRLs based on timer. */
      pta_time(&currentTime);
      if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {

			gCfg.cvmLastUpdate = currentTime;

	        if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
                 /* Ignore errors, but print an error message. */
		         vsLogMessage(LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");
			     /* Also print the last error's cause. */
		         if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
				     sprintf (buf, "Error Code : %d", refreshStatus);
				 }
	             vsLogMessage(LOG_FAILURE, buf);
			}
        }

    /* Make sure the sleep is outside the critical section! */
    /* Sleep 1/3 update time. In ms. */
    mutexStatus = WaitForSingleObjectEx(hThreadMutex, gCfg.cvmUpdateSeconds * 334, 0);

    if (endThread) {
     
      if (mutexStatus==WAIT_OBJECT_0) {
        ReleaseMutex(hThreadMutex);
      }
      endThread = 0;
      return;
    }

  }
  
}


/****************************************************************************************
* 
* Function:  vsIsapiGetRevocationInfo
* 
* This is the function that does  revocation checking
* This is called by vsPTAAuthorizePost to check the status of the cert
* 
* Parameters -
* certItem (IN) - the certificate whose revocation status is to be checked
* certStatus (OUT) - the certificate status
* statusExpires (OUT) - the certificate expiry
* userName (OUT) - cert subject DN
*
* Return values : 0, success
*                 otherwise - error code
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsIsapiGetRevocationInfo(ITEM *certItem, int *certStatus,
                             PTATIME *statusExpires, char **userName) {

  int status = 0, refreshStatus = 0;
  char *refreshStatusString = "";
  PTATIME currentTime;

  VSVAL_UserCtx ctx = {0};
  char buf[PTA_LARGE_BUF_MAX];

  ctx.logFn = gCfg.InfoLog;

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "isapissc: Inside vsIsapiGetRevocationInfo");
#endif 

  do {

    /* look up the certificate */
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


    /* See if we have to update all the CRLs based on timer. */
    pta_time(&currentTime);
    if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {

      gCfg.cvmLastUpdate = currentTime;

      /* Re-get all CRLs. */
      if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
          /* Ignore errors, but print an error message. */
          vsLogMessage(LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");
          /* Also print the last error's cause. */
	      if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
		     sprintf (buf, "Error Code : %d", refreshStatus);
		  }
	      vsLogMessage(LOG_FAILURE, buf);
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
		     sprintf (buf, "Error Code : %d", refreshStatus);
	  }
      vsLogMessage(LOG_FAILURE, buf);
    }


  } while (0); 

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "Revocation cert_status = %d", *certStatus);
#endif

  return status;
}



/****************************************************************************************
* 
* Function:  vsSSCCleanup
* 
* PTA cleanup routine, called when the ISAPI filter unloads
* 
* Parameters -
* param (IN) - ???
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/
void vsSSCCleanup(void *param)
{
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = gCfg.InfoLog;

  VSVAL_HashDestroy(gCfg.vsValSDK, &ctx, gCfg.hTable);

  gCfg.hTable = 0;

  VSVAL_Final (gCfg.vsValSDK);	

  /* Call the user final fn */
  if (gCfg.dlFinal) { (*gCfg.dlFinal) (); }


  /* Unload the user's authorization plugin. */
#ifdef WIN32
  if (gCfg.dlHandle) { FreeLibrary(gCfg.dlHandle); }
#endif

  /*
  if (gCfg.randObj) { vsDestroyRandom(&gCfg.randObj); }
  */

  sscT_free((unsigned char *) gCfg.cookieName);

  vsPTAClearLoginVal(& gCfg.loginValueMS);
  vsPTAClearLoginVal(& gCfg.loginValueNS);

  sscT_free((unsigned char *) gCfg.protectedDirList);

  /* TODO free dynamically allocated memory in vsSSCInit */

}


/****************************************************************************************
* 
* Function:  vsSSCInit
* 
* PTA initialization routine. This is the function that initializes the various data
* structures, the validation SDK and reads the configurations from the registry
* 
* Parameters - none
*
* Return values : 0 - success
*                 errorcode - otherwise
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsSSCInit() {

  int status = 0, pluginStatus = 0;
  char *errorString = "";
  char *cookieName = 0;
  char *protectedDirs = 0;
  char *adminIssuerSerialHasc = 0;
  char *hkeyStr = 0;
  char *logFileName = 0;
  char *cfg_filename = 0;
  char *file_prefix =  0;
  char *url_prefix =   0;
  char *cache_dir =    0;
  char *defaultLdap = 0;
  char *httpProxy = 0;
  char *ldapHttpProxy = 0;
  char *intString = 0;
  char *ocspUrl = 0;
  int ldapTimeOut = 0;
  int randomBytes;

  char valSDKErrorString[PTA_LARGE_BUF_MAX];

  VSVAL_UserCtx ctx = {0};

  unsigned int len = 0;
  HKEY hkey = 0, *phkey = 0;
  HANDLE hEventHandle;
  char *ErrorMessageArray[] = {"The VeriSign PTA filter could not open the registry key. Run the 'loadreg.exe -dump' command to verify your configuration is correct"};
  int x = 0;

#ifdef DEBUGMSG
  Debug((DEST, "isapissc - inside sscInit"));
#endif

  do {

    if ((status = VSVAL_Init(&gCfg.vsValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
      break;
    }

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - after VSVAL_Init status - %d", status));
#endif

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - opening registry key %s", PTA_REGISTRY_KEY));
#endif


    /* Read ISAPI options from registry. */
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, PTA_REGISTRY_KEY, 0,
                     KEY_READ, &hkey)!=ERROR_SUCCESS) {
      status = VSVAL_ERR_REGISTRY;
      break;
    }
    phkey = &hkey;

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - opened registry key %s", PTA_REGISTRY_KEY));
#endif

    /* SETUP THE INFO LOGGER AS THE FIRST THING WE DO!!! */
    logFileName = reg_findval("log-file-name", phkey);
    if (logFileName) {
#ifdef DEBUGMSG
	Debug((DEST, "isapissc - log-file is %s", logFileName));
#endif
      if ((globalLogFP = fopen(logFileName, "a"))==0) {
        status = VS_ERR_LOG_FILE;
        break;
      }
    }


    if (vs_reg_ison("log-info", phkey)) {
		gCfg.InfoLog = vsLogInfoMessage;
		ctx.logFn = vsLogInfoMessage;
	}
    else { 
		gCfg.InfoLog = vsNullLogInfoMessage;
		ctx.logFn = vsNullLogInfoMessage;
	}

    if (vs_reg_ison("debug-wait", phkey)) 
		x=1;

    while(x) {
#ifdef WIN32
      Sleep(100);
#endif
      ;
    }
    
    gCfg.fnGetRevocationInfo = vsIsapiGetRevocationInfo;


    gCfg.randomFile = reg_findval("random-file", phkey); /* null ok. */
    if (gCfg.randomFile != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "random-file", gCfg.randomFile))
		break;

    gCfg.noCRLCheck = vs_reg_ison("no-crl-check", phkey);


   /*
    *
	* Begin CVM configuration 
	*
	*/



	/*cfg_filename = reg_findval("cfg-filename", phkey);*/

    file_prefix = reg_findval("file-prefix", phkey);
    if (file_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "file-prefix", file_prefix))
		break;

	  
	url_prefix =  reg_findval("url-prefix", phkey);
    if (url_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "url-prefix", url_prefix))
		break;

	cache_dir = reg_findval("cache-dir", phkey);
    if (cache_dir != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "cache_dir", cache_dir))
		break;


	httpProxy = reg_findval("http-proxy", phkey);
    if (httpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "http-proxy", httpProxy))
		break;

	ldapHttpProxy = reg_findval("ldap-http-proxy", phkey);
    if (ldapHttpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy))
		break;


    if (intString = reg_findval("ldap-timeout", phkey)) {
      ldapTimeOut = atoi(intString);
    }
    else {
      ldapTimeOut = PTA_LDAP_TIMEOUT;
    }
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "ldap-timeout", ldapTimeOut))
		break;


    /* Must be done AFTER proxy configuration */
    ocspUrl = reg_findval("ocsp-url", phkey);
	gCfg.checkOCSP = 0;
    if (ocspUrl != 0) {	  
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ocsp-url", ocspUrl))
		break;	
	  gCfg.checkOCSP = 1;
	} 

	defaultLdap = reg_findval("default-ldap", phkey);
    if (defaultLdap !=0)
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", defaultLdap);
    else
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", "directory.verisign.com");
    if (status != 0)
      break;


    if (vs_reg_ison("no-check-chain", phkey)) 
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "on");
    else
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "off");
    if (status != 0)
      break;

    if (vs_reg_ison("log-security", phkey)) {
      gCfg.cvmLogSecurity = 1;
      gCfg.logSecurity = 1;
    }


    /* get CRL update frequency. */
    if (intString = reg_findval("update-seconds", phkey)) {
      gCfg.cvmUpdateSeconds = atoi(intString);
    }
    else if (intString = reg_findval("update-minutes", phkey)) {
      gCfg.cvmUpdateSeconds = 60 * atoi(intString);
    }
    else if (intString = reg_findval("update-hours", phkey)) {
      gCfg.cvmUpdateSeconds = 60 * 60 * atoi(intString);
    }
    else {
      gCfg.cvmUpdateSeconds = PTA_MAX_UPDATE_TIME;
    }

	if ( gCfg.cvmUpdateSeconds == 0) {
		status = VS_ERR_INVALID_UPDATE_HOURS;
		break;
	}


	cfg_filename = reg_findval("cfg-filename", phkey);

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - config file - %s, status - %d", cfg_filename, status));
	Debug((DEST, "isapissc - file prefix - %s, status - %d", file_prefix, status));
	Debug((DEST, "isapissc - url prefix - %s, status - %d", url_prefix, status));
	Debug((DEST, "isapissc - cache dir - %s, status - %d", cache_dir, status));
#endif

    if (!cfg_filename || !file_prefix || !cache_dir || (!url_prefix && !ocspUrl)) {
      status = VSVAL_ERR_OBJ_CONF;
      break;
    }

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - about to read config file - %s, status - %d", cfg_filename, status));
	gCfg.InfoLog(0, "isapissc - about to read config file - %s, status - %d", cfg_filename, status);
#endif


    /* check params... make sure there's a trailing / */
    if (status = VSVAL_ReadConfigFile(gCfg.vsValSDK, &ctx, cfg_filename)) {
#ifdef DEBUGMSG
	Debug((DEST, "isapissc - Error in read config file, status - %d", status));
	gCfg.InfoLog(0, "isapissc - Error in read config file, status - %d", status);
#endif
		break;
		/* you don't want to break because the filter will not load and people will have access to information */
		/* assume that some extra CRL or cert could not be read */
	}

#ifdef DEBUGMSG
	Debug((DEST, "isapissc - done CVM configuration, status - %d", status));
	gCfg.InfoLog(0, "isapissc - done CVM configuration, status - %d", status);
#endif

	/*
	* End CVM configuration 
	*
	*/

    /* leave this null if not specified. */
    gCfg.shlibName = reg_findval("shlib-name", phkey);

    if (gCfg.shlibName) {
      /* Load the user's authorization plugin. */

#ifdef WIN32
      gCfg.dlHandle = LoadLibrary(gCfg.shlibName);
#else
      /* Don't do RTLD_LAZY, so we find missing symbols right away. */
      gCfg.dlHandle = dlopen(gCfg.shlibName, RTLD_NOW);
#endif

      if (gCfg.dlHandle==0) {
        status = VS_ERR_SHLIB;
        break;
      }

      /* find the address of function and data objects */
#ifdef WIN32
      gCfg.dlInit  = (pFnInit) GetProcAddress(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) GetProcAddress(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) GetProcAddress(gCfg.dlHandle, "SscFinal");
#else
      gCfg.dlInit  = (pFnInit) dlsym(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) dlsym(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) dlsym(gCfg.dlHandle, "SscFinal");
#endif
    }

    /* MD5 or SHA1? */
    if (vs_reg_findmatch("digest-alg", phkey, "MD5")) { gCfg.useMD5 = 1; }

    /* Leave this null if not specified. */
    adminIssuerSerialHasc = reg_findval("admin-issuer-serial", phkey);
    if (adminIssuerSerialHasc) {
      VSVAL_StrToLower(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc); /* same upper/lowercase as bin2hasc. */
      if (VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc, gCfg.adminIssuerSerial, &len)) {
        status = VS_ERR_ADMIN_HASC;
        break;
      }
    }

    gCfg.addEnvVars = vs_reg_ison("add-env-vars", phkey);
    gCfg.addJSVars = vs_reg_ison("add-js-vars", phkey);

    /* this may not do what we want. */
    gCfg.addErrorJSVars = vs_reg_ison("add-error-js-vars", phkey);


    /* Optional memory saving optimization. Requires login on CRL expiration. */
    gCfg.noSaveCerts = vs_reg_ison("no-save-certs", phkey);
    if (gCfg.noSaveCerts && (gCfg.addEnvVars || gCfg.addJSVars)) {
      status = VS_ERR_NO_SAVE_CERTS;
      break;
    }
    gCfg.savePkcs7 = vs_reg_ison("save-pkcs7", phkey);
    
    gCfg.protectJavaDirs = vs_reg_ison("protect-java-dirs", phkey);

    /* Debugging only !!! */
    gCfg.signText = vs_reg_ison("sign-text", phkey);
    gCfg.signCanned = 1;
    gCfg.noSSL = vs_reg_ison("no-ssl", phkey);


    /* Set timeouts. */
    gCfg.absoluteTimeout = 
      60 * vs_reg_findint("absolute-timeout", phkey, 60); /* 1 hr. */
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "absolute-timeout", gCfg.absoluteTimeout/60))
		break;

    gCfg.inactiveTimeout = 
      60 * vs_reg_findint("inactive-timeout", phkey, 10); /* 10 min. */

    /* Defaults to 2x absolute timeout. */
    gCfg.garbageTime = 
      60 * vs_reg_findint("garbage-time", phkey, (2 * gCfg.absoluteTimeout) / 60);
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "garbage-time", gCfg.garbageTime/60))
		break;

    /* login/error pages. */
    if (vs_reg_findstr("login-page-ms", phkey, &(gCfg.loginPageMS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_reg_findstr("login-page-ns", phkey, &(gCfg.loginPageNS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_reg_findstr("error-page", phkey, &(gCfg.errorPage))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_reg_findstr("logout-url", phkey, &(gCfg.logoutUrl))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    } 

    /* server-name fqdn. Prevents man-in-the-middle attacks. */
    if (vs_reg_findstr("server-name", phkey, &(gCfg.serverName))==0) {
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

    /* IIS only-- list of directories to protect. */
    if (vs_reg_findstr("protected-dirs", phkey, &protectedDirs)==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    else {
      if (status = vsAllocDirList(protectedDirs, &(gCfg.protectedDirList),
                                  &(gCfg.protectedDirCount))) {
        break;
      }
    }

    gCfg.noCacheLogin = vs_reg_ison("no-cache-login", phkey);

    gCfg.noCachePages = vs_reg_ison("no-cache-pages", phkey);

    if (status = vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) {
      break;
    }
    if (status = vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) {
      break;
    }
    if (status = VSVAL_FileRead(gCfg.vsValSDK, &ctx, gCfg.errorPage, &(gCfg.errorPageItem.data), &(gCfg.errorPageItem.len))) {
      break;
    }


    /* Cookie name/domain. */
    cookieName = reg_findval("cookie-name", phkey);

    if ((gCfg.cookieName = (char *) sscT_malloc(PTA_LARGE_BUF_MAX))==0) {
      status = VS_ERR_NO_MEM;
      break;
    }

    if (cookieName) { sprintf(gCfg.cookieName, "%s", cookieName); }
    else {

      VSVAL_GenerateRandomBytes(gCfg.vsValSDK, &ctx, (unsigned char*)&randomBytes, sizeof(int));
      sprintf(gCfg.cookieName, "VeriSignPTA_%u", randomBytes);
      
      /* Can't specify cookie-domain w/o a cookie-name. */
      /* How would all the servers pick the same random id? */
      if (reg_findval("cookie-domain", phkey)) {
        status = VS_ERR_COOKIE_DOMAIN;
        break;
      }
    }

    gCfg.cookieDomain = reg_findval("cookie-domain", phkey); /* null if not there. */

    /* Make our hash table. */
    if (reg_findval("htable-size", phkey)) {
      VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, atoi(reg_findval("htable-size", phkey)), (VSVAL_pFnHashDestroy)vsPTADestroyClientData , (VSVAL_pFnHashGetISDigest)vsPTAGetISDigest);
      gCfg.hTableSize = atoi(reg_findval("htable-size", phkey));
    }
    else { 
      VSVAL_HashInit(gCfg.vsValSDK, &ctx, &gCfg.hTable, 12, (VSVAL_pFnHashDestroy)vsPTADestroyClientData , (VSVAL_pFnHashGetISDigest)vsPTAGetISDigest); 
      gCfg.hTableSize = 12;
    }


    /* Call the user init fn */
    if (gCfg.dlInit) { 
      // hkeyStr = reg_hkey2str(phkey, 0);
      pluginStatus = (*gCfg.dlInit) (VS_PTA_PLUGIN_DESC, hkeyStr ? hkeyStr : "");

      if (pluginStatus) {
        status = VS_ERR_PLUGIN_INIT;
        break;
      }

    }

    /* Moved out of CVMInit().  There are problems returning FALSE from dllmain if the */
    /* thread isn't started yet.  I couldn't fix it w/ mutexes, so do this last. */
    /* Start a thread to do the timer-based CRL updates. */

    if (gCfg.cvmUpdateSeconds < PTA_MAX_UPDATE_TIME) {
      if ((hThread = _beginthread(vsSleeperThread, 0, 0))==-1) {
        hThread = 0;
        status = VSVAL_ERR_THREAD;
        break;
      }
    }

#ifdef DEBUGMSG
    Debug((DEST, "spawn sleeper thread %x threadMutex %x", hThread, hThreadMutex));
	gCfg.InfoLog(0, "spawn sleeper thread %x threadMutex %x", hThread, hThreadMutex);
#endif

    /* Print a startup message. */
    gCfg.InfoLog(0, "%s starting", PTA_NSAPI_DESCR);
 
  } while (0);

  if (hkey) RegCloseKey(hkey);

  if (status) {
	  if (status == VSVAL_ERR_REGISTRY) {
		  hEventHandle = RegisterEventSource(NULL,  // uses local computer 
             "VeriSignPTAServer");          // source name 
		  if (hEventHandle != NULL) {
			  ReportEvent(hEventHandle,           // event log handle 
						EVENTLOG_ERROR_TYPE,  // event type 
						0,                    // category zero 
						VSVAL_ERR_REGISTRY,   // event identifier 
						NULL,                 // no user security identifier 
						1,                    // one substitution string 
						0,                    // no data 
						ErrorMessageArray,     // pointer to string array 
						NULL);                // pointer to data
			  DeregisterEventSource(hEventHandle); 
		  } 
	  }

	/* some of the errors might be returned by the validation 
	 * SDK so you need to handle accordingly 
	 */

	  if ( status > VS_ERR_BASE && status < VS_ERR_MAX ) {
		sscErrorString(&errorString, status);
		vsLogMessage(LOG_FAILURE, "%s", errorString);
	  }
	  else
		if (status > VSVAL_ERR_BASE && status < VSVAL_ERR_MAX) {
			VSVAL_ErrorString(gCfg.vsValSDK, valSDKErrorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
			vsLogMessage(LOG_FAILURE, "%s", valSDKErrorString);
		}
		else   /* Otherwise errorString is already set. */
			vsLogMessage(LOG_FAILURE, "%s", errorString);
  }

  if (globalLogFP) {
    fflush(globalLogFP);
  }

  /* TODO free dynamically allocated memory */

  return status;
}


/****************************************************************************************
* 
* Function:  vsAddValidEnvVars
* 
* This function adds certificate details as environment variables as HTTP_ headers. 
* Must be done at preproc header stage. Can't add them as environment vars since the 
* cgi process isn't spawned yet, and we don't have access to its environment.
* 
* Parameters - 
*    pFC (IN) - pointer to the filter context
*    pPreProcData (IN) - pointer to the preproc header structure
*    clientData (IN) - pointer to client_data_t structure for that session
* 
* Return values : 0 - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsAddValidEnvVars(HTTP_FILTER_CONTEXT *pFC,
                      PHTTP_FILTER_PREPROC_HEADERS pPreProcData, 
                      client_data_t *clientData) {

  VSVAL_UserCtx ctx={0};
  ITEM b64Cert = {0};
  ITEM pkcs7Item = {0};
  int tmpStatus;
  unsigned char *b64String;

  ctx.logFn = gCfg.InfoLog;

  /* If we call this from the wrong spot, just return. */
  if (pPreProcData==0) {
    return 0;
  }

  /* Set auth-user, etc... */
  pPreProcData->AddHeader(pFC, "vs_auth_type:", "strong");

  if (clientData) {

    if (clientData->userName) {
      // What is the IIS version?? 
      pPreProcData->AddHeader(pFC, "vs_auth_user:", clientData->userName);
    }
    
    if (clientData->pkcs7) {
      
	  
	  /* call removeEOL */
	  pkcs7Item.len = strlen(clientData->pkcs7) + 1;
	  pkcs7Item.data = sscT_malloc (pkcs7Item.len);
	  strcpy (pkcs7Item.data, clientData->pkcs7);
	  removeEOL (&pkcs7Item);

	  pPreProcData->AddHeader(pFC, "vs_pkcs7:", pkcs7Item.data);

	  if (pkcs7Item.data)
		 sscT_free (pkcs7Item.data);

      if (!gCfg.savePkcs7) {
        sscT_free((unsigned char *) clientData->pkcs7);
        clientData->pkcs7 = 0;
      }
    }

    if (clientData->cert.data &&
        (VSVAL_Base64Alloc(gCfg.vsValSDK, &ctx, &b64String, clientData->cert.data, clientData->cert.len)==0)) {

      /* Remove \r or \n at end of string. (It makes IIS think it's the last header.) 
      for (c = b64Cert.data + b64Cert.len - 1;
           c >= b64Cert.data + b64Cert.len - 2; c--) {
        if (*c=='\r' || *c=='\n') *c = '\0';
        }*/

      /* Let's do this instead. Slower, but also gets rid of icky line breaks. */
      /*vsPTAEatWhite((char *) b64Cert.data);*/
	  b64Cert.data = sscT_strdup (b64String);
	  VSVAL_Free(gCfg.vsValSDK, b64String);

      b64Cert.len=strlen((char*)b64Cert.data)+1;
      removeEOL(&b64Cert);      	  


      pPreProcData->AddHeader(pFC, "vs_auth_cert:", (char *) b64Cert.data);

      /* Here's where we add CDR variables. */
      tmpStatus = VSUnwrapCertificate(pFC, pPreProcData, (char *) b64Cert.data);

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "unwrap = %d", tmpStatus);
#endif

      sscT_free(b64Cert.data);
    }
  }
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "returning from AddEnvVars", tmpStatus);
#endif
  
  return 0;
}

/****************************************************************************************
* 
* Function:  vs_preq_nvreplace
* 
* This function replaces the value for a particular name in the 
* prequest data structure
* 
* Parameters - 
*    name (IN, OUT) - the pointer where the new value is to be replaces
*    value (IN) - the new value
*
* Return values : new pointer for the value string
* 
* Change History
* -
* -
*
*****************************************************************************************/

/* Frees the old value, and replaces it with a newly allocated one. */
char *vs_preq_nvreplace(char **name, char *value) {
  
  if (*name) {
    sscT_free(*name);
  }

  *name = sscT_strdup(value);

  return *name;
}



/****************************************************************************************
* 
* Function:  vsGetPostedData
* 
* This function gets the post data from request, parses the post to get the PKCS7
* and then parses the PKCS7 using the validation SDK
* 
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the request data  stucture
*    outPKCS7 (OUT) - the base64 encoded PKCS7
*    outDigest (OUT) - the digest parsed from PKCS7, outDigest.data should be
*                      preallocated with at least VSVAL_HASH_MAX bytes
*    outCert (OUT) - the certificate 
*
* NOTE: outPKCS7 is allocated in this function and it is the responsibility of the 
*       calling function to free outPKCS7
*
* Return values : 0 - success
*                 errorcode - otherwise
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsGetPostedData(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo,
                    char **outPKCS7, ITEM *outDigest, ITEM *outCert) 
{
  int status = 0, tmpStatus;
  ITEM b64Item = {0}, postedItem = {0};
  char *b64Str, *typeStr;
  int toRead, algorithm;
  VSVAL_UserCtx ctx = {0};

  ctx.logFn = gCfg.InfoLog;

  do {

    typeStr = pReqInfo->contentType;
    toRead = pReqInfo->cbPostLen;

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: vsGetPostedData: con-len=%d, typ=%s", toRead, typeStr));
	gCfg.InfoLog(0, "isapi_ssc: vsGetPostedData: con-len=%d, typ=%s", toRead, typeStr);
#endif

    if (toRead<=0) {
      status = -3;
      break;
    }

    b64Item.len = strlen(pReqInfo->pRequestPost);
    // assert toRead = .len 
    b64Item.data = sscT_malloc(b64Item.len + 1);

    if (b64Item.data==0) {
      status = VS_ERR_NO_MEM;
      break;
    }

    memcpy(b64Item.data, pReqInfo->pRequestPost, b64Item.len);
    b64Item.data[b64Item.len] = '\0';

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
  gCfg.InfoLog(0, "debase=%d, len = %d", tmpStatus, postedItem.len);
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
  debugDumpCertItem(gCfg.vsValSDK, &internalCtx, outCert); 
  */
  /* dump the cert dn */
#endif

  VSVAL_Free(gCfg.vsValSDK, postedItem.data);

  return status;
}


/****************************************************************************************
* 
* Function:  vsSetGETUrl
* 
* This function sets the GET url in the request headers
* 
* Parameters - 
*    url (IN) - the url to set in the request header
*    pFC (IN) - the pointer to the filter context
*    pPreProcData (IN) - the pointer to HTTP_FILTER_PREPROC_HEADERS data structure
*
* NOTE: this function does not seem to be used in isapi filter, check
* 
* Return values : 0
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsSetGETUrl(char *url, HTTP_FILTER_CONTEXT *pFC,
                PHTTP_FILTER_PREPROC_HEADERS pPreProcData) {

  pPreProcData->SetHeader(pFC, "url", url);
  pPreProcData->SetHeader(pFC, "method", "GET");
  
  pPreProcData->SetHeader(pFC, "Content-Length:", 0);
  pPreProcData->SetHeader(pFC, "Content-Type:", 0);

  return 0;
}


/****************************************************************************************
* 
* Function:  SSCSendValid
* 
* This function sends a valid page, if this was called during a post to /vsadmin/post
* then it sends the redirect page, otherwises it lets the webserver handle the 
* request. The output page is created in memory and stored in pReqInfo.page to be 
* send out later.
* 
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*
* Return values : SF_STATUS_REQ_ERROR - on error, should not occur
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
* 
* Change History
* -
* -
*
*****************************************************************************************/
int SSCSendValid(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo) {

  int rc = 0;
  char buf[PTA_LARGE_BUF_MAX], *postUrl;

//artf14514: Changes Begin
  LPSTR           lpszTemp;
//artf14514: Changes End

  /* Send a valid url */

  do {
    
    /* A GOOD url. */

    if (postUrl = pReqInfo->validPost) {
      /* If we are coming from /vsadmin/post, send a redirect page to their url. */

//artf14514: Changes Begin
  if(IISVERSION == IIS5)
  	{
	      pFC->AddResponseHeaders(pFC, "Content-Type: text/html\r\n", 0);	  
  	}
  else if(IISVERSION == IIS6)
  	{
		if(pReqInfo->lpszHeaderLen > 0) {
			lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
			memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
			pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Content-Type: text/html\r\n"), 0);
			memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
		} else
			pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen("Content-Type: text/html\r\n"), 0);

		memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, "Content-Type: text/html\r\n", strlen("Content-Type: text/html\r\n"));
		pReqInfo->lpszHeaderLen += strlen("Content-Type: text/html\r\n");
  	}
//artf14514: Changes End

      if (vsPTAGetRedirectPage(buf, postUrl)) {
        gCfg.InfoLog(0, "get redirect page");
        rc = SF_STATUS_REQ_ERROR;
        break;
      }

      pReqInfo->page.len = strlen(buf);
      pReqInfo->page.data = sscT_malloc(pReqInfo->page.len + 1);

      if (pReqInfo->page.data==0) {
        gCfg.InfoLog(0, "sendValid malloc");
        rc = SF_STATUS_REQ_ERROR;
        break;
      }

      memcpy(pReqInfo->page.data, buf, strlen(buf));
      pReqInfo->page.data[pReqInfo->page.len] = '\0';

      /* Only do this service fn. Don't run any others since we've sent the page. */
      rc = SF_STATUS_REQ_NEXT_NOTIFICATION;
      break;
    }
    else {
      /* else we got a cookie authentication. Continue. */
      /* Environment vars for normal page are set up in sscCheck(). */
      rc = SF_STATUS_REQ_NEXT_NOTIFICATION;
    }


  } while (0);

  return rc;
}


/****************************************************************************************
* 
* Function:  SSCSendLogout
* 
* This function sends the logout page, it also sets the cookie to be deleted in the 
* response headers
* 
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
* 
* Change History
* -
* -
*
*****************************************************************************************/
int SSCSendLogout(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo) {

  int rc = 0;

  /* Send the logout-url. */

  do {

    /* Delete their cookie. */
    setCookie(pFC, "Delete", 1);

    /* No environment vars to setup for logout page. */

    /* No javascript vars for logout pages. */

    /* continue on to whatever services the logout url. */
    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  } while (0);

  return rc;
}



/****************************************************************************************
* 
* Function:  SSCSendAdmin
* 
* This function sends the result of the admin operation. This functionality has
* not been extensively tested. The output page is created in memory and stored in 
* pReqInfo.page to be send out later.
* 
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur
* 
* Change History
* -
* -
*
*****************************************************************************************/
int SSCSendAdmin(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo) {

  int rc = 0;
  char *bufPre = "<html><head><title>Admin Operation</title></head>\n"
    "<h2 align=center>Admin Operation Successful</h2><hr>\n";
  char buf[PTA_LARGE_BUF_MAX];
  char *bufEnd = "</body></html>\n";
  char *adminOp = 0;
  int lenPre, len, lenEnd;

//artf14514: Changes Begin
  LPSTR           lpszTemp;
//artf14514: Changes End

  /* Send the successful admin page. */

  do {

    /* The admin page is in html. */
//artf14514: Changes Begin
  if(IISVERSION == IIS5) {
    		pFC->AddResponseHeaders(pFC, "Content-Type: text/html\r\n", 0);
	} 
	else if(IISVERSION == IIS6) {
		    if(pReqInfo->lpszHeaderLen > 0) {
				lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
				memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Content-Type: text/html\r\n"), 0);
				memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
			} else
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen("Content-Type: text/html\r\n"), 0);

			memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, "Content-Type: text/html\r\n", strlen("Content-Type: text/html\r\n"));
			pReqInfo->lpszHeaderLen += strlen("Content-Type: text/html\r\n");
		}
//artf14514: Changes End	

    if ((adminOp = pReqInfo->adminOp)==0) {
      gCfg.InfoLog(0, "Get adminOp");
      rc = SF_STATUS_REQ_ERROR;
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
    lenPre = strlen(bufPre);
    len = strlen(buf);
    lenEnd = strlen(bufEnd);
    pReqInfo->page.len = lenPre + len + lenEnd;

    pReqInfo->page.data = sscT_malloc(pReqInfo->page.len + 1);

    if (pReqInfo->page.data==0) {
      gCfg.InfoLog(0, "sendAdmin malloc");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

    memcpy(pReqInfo->page.data, bufPre, lenPre);
    memcpy(pReqInfo->page.data + lenPre, buf, len);
    memcpy(pReqInfo->page.data + lenPre + len, bufEnd, lenEnd);

    pReqInfo->page.data[pReqInfo->page.len] = '\0';

    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  } while (0);

  return rc;
}


/****************************************************************************************
* 
* Function:  SSCSendLogin
* 
* This function sends the login page. It gets a new value for the client to sign, 
* prepends this as a JavaScript code and sends the login page depending on the 
* browser. The output page is created in memory and stored in pReqInfo.page to be 
* send out later.
* 
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*    sscStatus (IN) - 
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur
* 
* Change History
* -
* -
*
*****************************************************************************************/
int SSCSendLogin(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo, char *sscStatus) {
  int rc = 0;
  ITEM hashItem;
  login_page_t oldLoginNS = {0}, oldLoginMS = {0};
  char buf[PTA_LARGE_BUF_MAX];
  char hascToSign[PTA_TINY_BUF_MAX], hashOfToSign[PTA_TINY_BUF_MAX];
  unsigned char hashBuf[MAX_DIGEST_LEN];
  client_data_t *clientData;

//artf14514: Changes Begin
  LPSTR           lpszTemp;
//artf14514: Changes End

  PTATIME tm = 0;
  char *browserPreBuf, *browserPostBuf;
  int browserPreLen, browserPostLen;

  VSVAL_UserCtx ctx;

  ctx.logFn = gCfg.InfoLog;

  /* login or expired */

  do {

    hashItem.data = hashBuf;
    hashItem.len = 0;
    /* Get a new random piece of data for the client to sign. */
    if (ptaGetValToSign(gCfg.useMD5, hascToSign, hashOfToSign, &hashItem)) {
      gCfg.InfoLog(0, "Get val to sign");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

    /* Over-paranoid? See if there's a duplicate value before inserting. */
/* SB-TODO commented out pending validation SDK bug fix */
	/*
    if (VSVAL_HashSearch(gCfg.vsValSDK, &ctx, gCfg.hTable, hashItem.data, hashItem.len, &hashData)==0) {
      gCfg.InfoLog(0, "Duplicate hash value!");
    }
	*/

    /* Put the hash of this in the hash table. (w/ unauthorized bit set.) */
    if ((clientData = vsPTAInitClientData())==0) {
      gCfg.InfoLog(0, "init client data");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

    pta_time(&tm);
    clientData->authorized = 0;
    clientData->url = sscT_strdup(pReqInfo->oldUri);
    if (clientData->url==0) {
      gCfg.InfoLog(0, "init client data url malloc");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "olduri=%s", clientData->url);
#endif
    clientData->absolute_timeout = tm + gCfg.absoluteTimeout;
    clientData->inactive_timeout = tm + gCfg.inactiveTimeout;
    VSVAL_HashInsert(gCfg.vsValSDK, &ctx, gCfg.hTable, hashItem.data, hashItem.len, (void*)clientData);

    /* The login page must be in html. */
//artf14514: Changes Begin
    if(IISVERSION == IIS5) {
    		pFC->AddResponseHeaders(pFC, "Content-Type: text/html\r\n", 0);
    	}
	else if (IISVERSION == IIS6) {
			if(pReqInfo->lpszHeaderLen > 0) {
				lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
				memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Content-Type: text/html\r\n"), 0);
				memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
			} else
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen("Content-Type: text/html\r\n"), 0);

			memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, "Content-Type: text/html\r\n", strlen("Content-Type: text/html\r\n"));
			pReqInfo->lpszHeaderLen += strlen("Content-Type: text/html\r\n");
		}
//artf14514: Changes End

    /* Get variables: what to sign, etc... */
    if (vsPTAGetJSForLogin(buf, hascToSign, hashOfToSign, sscStatus,
                        gCfg.useMD5 ? "MD5" : "SHA")) {
      gCfg.InfoLog(0, "get js for login");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

        
    /* Reload the login page from disk if we aren't supposed to cache it. */
    if (gCfg.noCacheLogin) {

      /* Save the old one in case there's a problem. */
      oldLoginNS = gCfg.loginValueNS;
      oldLoginMS = gCfg.loginValueMS;

      if (vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueNS = oldLoginNS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginNS);
      }

      if (vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueMS = oldLoginMS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginMS);
      }
    }

    /* Write the page to the client. */
    if (pReqInfo->bIsMSIE) {
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

    pReqInfo->page.len = browserPreLen + strlen(buf) + browserPostLen;

    pReqInfo->page.data = sscT_malloc(pReqInfo->page.len + 1);

    if (pReqInfo->page.data==0) {
      gCfg.InfoLog(0, "sendLogin malloc");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

    memcpy(pReqInfo->page.data, browserPreBuf, browserPreLen);

    memcpy(pReqInfo->page.data + browserPreLen, buf, strlen(buf));

    memcpy(pReqInfo->page.data + browserPreLen + strlen(buf),
           browserPostBuf, browserPostLen);

    pReqInfo->page.data[pReqInfo->page.len] = '\0';

    /* Setup environment vars for login page. Are there any? */
    /* vs_pblock_nvreplace("vs_login", "someValue", rq->headers);  */

    /* delete the cookie ?  setCookie(rq, "Delete", 1); */

    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  } while (0);

  return rc;
}


/****************************************************************************************
* 
* Function:  SSCSendError
* 
* This function sends the error page. Depending on the error string sscStatus
* The output page is created in memory and stored in pReqInfo.page to be 
* send out later.
*
* NOTE: 
* For IIS, we can't send a url for the error since we may not know if an error 
* has occurred until the second read raw event (after preProcHeaders.) 
* By then it's too late to change the type of url (ie, to a cgi) so we can't do 
* the redirect. We use a disk file for the page we can optionally add js vars. 
*
* Parameters - 
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*    sscStatus (IN) - the status error  
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur
* 
* Change History
* -
* -
*
*****************************************************************************************/

int SSCSendError(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo, char *sscStatus) {

  int rc = 0;
  char buf[PTA_LARGE_BUF_MAX];
  int len;

  /* Bad. Send the error-page. */

  do {

    /* Delete their cookie. */
    /* Otherwise, when server gets rebooted, no way to stop sending a bad auth. */
    setCookie(pFC, "Delete", 1);


    if (gCfg.addErrorJSVars) {

      /* prepend variables: what to sign, etc... */
      if (vsPTAGetJSForError(buf, sscStatus, pReqInfo->oldUri ? pReqInfo->oldUri : "")) {
        gCfg.InfoLog(0, "add js for error page");
        rc = SF_STATUS_REQ_ERROR; /* this shouldn't fail. */
        break;
      }

      /* Setup to use the configured html error page. */

      len = strlen(buf);
    }
    else {
      len = 0;
    }

    pReqInfo->page.len = len + gCfg.errorPageItem.len;
    pReqInfo->page.data = sscT_malloc(pReqInfo->page.len + 1);

    if (pReqInfo->page.data==0) {
      gCfg.InfoLog(0, "sendAdmin malloc");
      rc = SF_STATUS_REQ_ERROR;
      break;
    }

    memcpy(pReqInfo->page.data, buf, len);
    memcpy(pReqInfo->page.data + len, gCfg.errorPageItem.data, gCfg.errorPageItem.len);
    pReqInfo->page.data[pReqInfo->page.len] = '\0';

    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  } while (0);

  return rc;
}


/****************************************************************************************
* 
* Function:  vsSSCSend
* 
* Service function for sending the login page, redirect to error, etc...
*
* Parameters:
*    pFC (IN) - the pointer to the filter context
*    pReqInfo (IN) - the pointer to PREQUESTINFO data structure for this request
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
* 
* Change History
* -
* -
*
*****************************************************************************************/
//artf14514: Changes Begin
int vsSSCSend(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo) {

  int rc;
  char *sscStatus;
  int sendNoCache = 1; /* default to true. Remove for regular pages. */
  char buf[PTA_LARGE_BUF_MAX];
  int len = PTA_LARGE_BUF_MAX;

//artf14514: Changes Begin
  LPSTR           lpszTemp;
//artf14514: Change End

  do {
//artf14514: Changes Begin
    if(IISVERSION == IIS6) {
	
	    	if(pReqInfo->lpszHeaderLen > 0) {
			lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("HTTP/1.1 200 OK\r\n"), 0);
			memcpy(lpszTemp, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"));
			memcpy(lpszTemp + strlen("HTTP/1.1 200 OK\r\n"), pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
			pReqInfo->lpszHeader = lpszTemp;
		} else {
			pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen("HTTP/1.1 200 OK\r\n"), 0);
			memcpy(pReqInfo->lpszHeader, "HTTP/1.1 200 OK\r\n", strlen("HTTP/1.1 200 OK\r\n"));
		}
		pReqInfo->lpszHeaderLen += strlen("HTTP/1.1 200 OK\r\n");
    	}
//artf14514: Changes End	
    if (pReqInfo->sscStatus) {
      sscStatus = pReqInfo->sscStatus;
    }
    else {
      sscStatus = "nullSend";
    }

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: vsSSCSend"));
    gCfg.InfoLog(0, "Status = %s", sscStatus);
#endif

    if(strcmp(sscStatus, "valid")==0) {
      /* Send a valid url. */
      rc = SSCSendValid(pFC, pReqInfo);

      /* By default (configurable) we allow normal content to be cached */
      /* by the browser. */
      if (!gCfg.noCachePages) { sendNoCache = 0; }
    }
    else {

      if(strcmp(sscStatus, "login")==0 ||
         strcmp(sscStatus, "expired")==0) {

        /* Send the login page. */
        rc = SSCSendLogin(pFC, pReqInfo, sscStatus);

      }
      else if(strcmp(sscStatus, "logout")==0) {
        /* Remove the client cookie and authentication from the hash table. */
        rc = SSCSendLogout(pFC, pReqInfo);
      }
      else if(strcmp(sscStatus, "admin")==0) {
        /* Send a page indicating the admin operation was successful. */
        rc = SSCSendAdmin(pFC, pReqInfo);
      }
      else {
        /* Send an error page. */
        rc = SSCSendError(pFC, pReqInfo, sscStatus);
      }

    }

  } while (0);

  rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  /* Tell the client not to cache any pages. Otherwise on second logout, */
  /* the client will just show the local page and not send a logout to the server. */
  if (sendNoCache) {
//artf14514: Changes Begin
    	if(IISVERSION == IIS5) {
    		pFC->AddResponseHeaders(pFC, "Pragma: no-cache\r\n", 0);
		/* Some time in the past. */			
    		pFC->AddResponseHeaders(pFC, "Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n", 0);			
    	} 
	else if (IISVERSION == IIS6) {
		    	if(pReqInfo->lpszHeaderLen > 0) {
				lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
				memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Pragma: no-cache\r\n"), 0);
				memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
			} else {
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, strlen("Pragma: no-cache\r\n"), 0);
			}
			memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, "Pragma: no-cache\r\n", strlen("Pragma: no-cache\r\n"));
			pReqInfo->lpszHeaderLen += strlen("Pragma: no-cache\r\n");

			/* Some time in the past. */			
			
			if(pReqInfo->lpszHeaderLen > 0) {
				lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
				memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n"), 0);
				memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
			} else {
				pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen("Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n"), 0);
			}
			memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, "Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n", strlen("Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n"));
			pReqInfo->lpszHeaderLen += strlen("Expires: Tue, 30 Mar 1999 11:54:01 GMT\r\n");
			
		}
  	}
  if (pReqInfo->page.len) {
    sprintf(buf, "Content-Length: %d\r\n", pReqInfo->page.len);
	if(IISVERSION == IIS5) {
    		pFC->AddResponseHeaders(pFC, buf, 0);
	}
	else if(IISVERSION == IIS6) {
		if(pReqInfo->lpszHeaderLen > 0) {
			lpszTemp = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen, 0);
			memcpy(lpszTemp, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
			pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen(buf), 0);
			memcpy(pReqInfo->lpszHeader, lpszTemp, pReqInfo->lpszHeaderLen);
		} else
			pReqInfo->lpszHeader = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + strlen(buf), 0);
		memcpy(pReqInfo->lpszHeader + pReqInfo->lpszHeaderLen, buf, strlen(buf));
		pReqInfo->lpszHeaderLen += strlen(buf);
	}

    /* Must already have all of our headers added. This immediately calls sendraw(). */
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: vsSSCSend calling"));
	gCfg.InfoLog(0, "isapi_ssc: vsSSCSend calling");
#endif
	if(IISVERSION == IIS5) {
    		pFC->ServerSupportFunction(pFC, SF_REQ_SEND_RESPONSE_HEADER, "200 OK", 0, 0);
	} 
//artf14514: Changes End


#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: vsSSCSend called"));
	gCfg.InfoLog(0, "isapi_ssc: vsSSCSend called");
#endif

  }
  return rc;
}
/****************************************************************************************
* 
* Function:  vsIsProtected
* 
* Is this a protected resource? Use the list of urls in the registry.
*
* Parameters:
*    url (IN) - the URL 
*    handle (IN) - handle to the filter context
*
* Return values : 0/1 - depending on if the URL not protected/protected
* 
* Change History
* -
* -
*
*****************************************************************************************/
int vsIsProtected(char *url, HTTP_FILTER_CONTEXT *handle) {

  return vsDirIsProtected(url, gCfg.protectedDirList, gCfg.protectedDirCount, handle);
}


/****************************************************************************************
* 
* Function:  cleanDllGlobals
* 
* Cleanup function called when the DLL unloads
*
* Parameters:none
*
* Return values : none
* 
* Change History
* -
* -
*
*****************************************************************************************/
void cleanDllGlobals() {


  WaitForSingleObject(hMutex, 1000);
  WaitForSingleObject(hLogMutex, 1000);

  if (hMutex) { CloseHandle(hMutex); hMutex = 0; }
  if (hLogMutex) { CloseHandle(hLogMutex); hLogMutex = 0; }

  if (globalLogFP) { fclose(globalLogFP); globalLogFP = 0; }

  endThread = 1;
  ReleaseMutex(hThreadMutex);

  /* If hThread is 0, we didn't spawn a sleeper. */
  /* Don't wait for it-- it'll never wake up since it doesn't exist! */
  if (hThread) {
    while (endThread) { Sleep(10); } /* Wait for the sleeperThread to exit. */
  }
  else {
    endThread = 0; /* Not necessary. Seems appropriate. */
  }
  

  WaitForSingleObject(hThreadMutex, 1000);

  if (hThreadMutex) { CloseHandle(hThreadMutex); hThreadMutex = 0; }

}

/****************************************************************************************
* 
* Function:  DllMain
* 
* DLL main function is executed on DLL loading and unloading. Note that
* that if IIS has cached the DLL then this will only be called the first
* time the DLL is loaded and when it is unloaded.
*
* This function is used to initialize, clean up the PTA filter
*
* Parameters:
*     hinstDLL(IN) - handle to itself.
*     dvReason (IN) - reason can be DLL_PROCESS_ATTACH, DLL_PROCESS_DETACH, 
*                     DLL_THREAD_ATTACH or DLL_THREAD_DETACH
*     lpv (IN) - 
*
* Return values : FALSE - on error
*                 TRUE - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dvReason, LPVOID lpv) {
  CHAR    ModuleName[PTA_TINY_BUF_MAX+1];

  switch (dvReason) {

  case DLL_PROCESS_ATTACH:
    GetModuleFileName(NULL, ModuleName, PTA_TINY_BUF_MAX);
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: DLL loaded by - %s", ModuleName));
#endif
    GetModuleFileName(hinstDLL, ModuleName, PTA_TINY_BUF_MAX);
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: DLL module name is - %s", ModuleName));
#endif

    /*  Create a mutex with no initial owner. */
    hMutex = CreateMutex(0, FALSE, VS_MUTEX_NAME);
    hLogMutex = CreateMutex(0, FALSE, VS_LOG_MUTEX_NAME);
    hThreadMutex = CreateMutex(0, FALSE, VS_THREAD_MUTEX_NAME);
#ifdef DEBUGMSG
    Debug((DEST, "mutex=%x, %x, %x", hMutex, hLogMutex, hThreadMutex));
#endif

	if (hMutex==0 || hLogMutex==0 || hThreadMutex==0) {
      return FALSE;
    }

    WaitForSingleObject(hThreadMutex, INFINITE);

    if (vsSSCInit() != 0) {
#ifdef DEBUGMSG
      Debug((DEST, "ssc init failed"));
#endif
      cleanDllGlobals();

      return FALSE;
    }
#ifdef DEBUGMSG
    Debug((DEST, "ssc init done"));
#endif
    break;

  case DLL_PROCESS_DETACH:

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: DLL being unloaded"));
#endif

    vsSSCCleanup(0);

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: ssc cleanup done"));
#endif

    cleanDllGlobals();    

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: DLL done being unloaded"));
#endif
    break;


  case DLL_THREAD_ATTACH:
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: Thread entering DllMain"));
#endif
    break;

  case DLL_THREAD_DETACH:
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: Thread leaving DllMain"));
#endif
    break;
  }

  return TRUE;
}

/****************************************************************************************
* 
* Function:  GetFilterVersion
* 
* Entry point for ISAPI filter DLL. used to tell IIS which events we are interested in.
*
* Parameters:
*     pVersion(OUT) - this is the data structure where we can set the flags 
*
* Return values : FALSE - on error
*                 TRUE - success
* 
* Change History
* -
* -
*
*****************************************************************************************/
BOOL WINAPI GetFilterVersion(HTTP_FILTER_VERSION *pVersion) {

  if (pVersion==0) {
    return FALSE;
  }

  /* Set version */
  pVersion->dwFilterVersion = HTTP_FILTER_REVISION;

  /* Provide a short description of the filter */
  lstrcpyn(pVersion->lpszFilterDesc, VS_PTA_PLUGIN_DESC, SF_MAX_FILTER_DESC_LEN);

  Debug((DEST, "%s starting", pVersion->lpszFilterDesc));

  //artf14514: Changes Begin
    if (pVersion->dwServerFilterVersion == IIS5)
  {
	IISVERSION = IIS5;	
  }
  else if (pVersion->dwServerFilterVersion == IIS6)
  {
	IISVERSION = IIS6;	
  }

  #ifdef DEBUGMSG
    gCfg.InfoLog(0, "SPB: IIS version is %d", IISVERSION);
  #endif
  //artf14514: Changes End

  /* Set the event we want to be notified about and the notification priority */
  pVersion->dwFlags = (SF_NOTIFY_SECURE_PORT |
                       SF_NOTIFY_NONSECURE_PORT |
                       SF_NOTIFY_READ_RAW_DATA |
                       SF_NOTIFY_PREPROC_HEADERS |
                       SF_NOTIFY_LOG | /* needed/useful ? */
                       SF_NOTIFY_SEND_RAW_DATA |
                       SF_NOTIFY_END_OF_NET_SESSION |
                       SF_NOTIFY_ORDER_HIGH);
  return TRUE;
}


/****************************************************************************************
* 
* Function:  HttpFilterProc
* 
* Entry point for ISAPI filter DLL. the event notificatations are sent to this 
* routine, which calls the different handlers depending on the event
*
* Parameters:
*     pFC(IN) - pointer to the filter context
*     dwNotificationType (IN) - the event id
*     pvData (IN) - event specific data
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* -
* -
*
*****************************************************************************************/
DWORD WINAPI HttpFilterProc(HTTP_FILTER_CONTEXT *pFC,
                            DWORD dwNotificationType, VOID *pvData) {

  DWORD dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;

  switch (dwNotificationType) {
  case SF_NOTIFY_READ_RAW_DATA:
    dwRet = HandleEvent_ReadRawData(pFC, (PHTTP_FILTER_RAW_DATA)pvData);
    break;
  case SF_NOTIFY_PREPROC_HEADERS:
    dwRet = HandleEvent_PreProcHeaders(pFC, (PHTTP_FILTER_PREPROC_HEADERS)pvData);
    break;
  case SF_NOTIFY_LOG:
    dwRet = HandleEvent_Log(pFC, (PHTTP_FILTER_LOG)pvData);
    break;
  case SF_NOTIFY_SEND_RAW_DATA:
    dwRet = HandleEvent_SendRawData(pFC, (PHTTP_FILTER_RAW_DATA)pvData);
    break;
  case SF_NOTIFY_END_OF_NET_SESSION:
    dwRet = HandleEvent_EndOfNetSession(pFC);
    break;
  }
  return dwRet;
}



/****************************************************************************************
* 
* Function:  vsReadRawData2
* 
* Gets called when enough data cannot be read in the first ReadRawData event 
* This can be called one or more times even after a PreProcHeaders event
*
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pReadData (IN) - data specific to RAW_DATA event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 02/12/01 - Siddharth Bajaj - bug fix, the function was behaving erronously if the 
*   post data was split across multiple ReadRawData events. This was noticed with 
*   a Netscape 6 browser
* -
*
*****************************************************************************************/
DWORD vsReadRawData2(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pReadData) {

	DWORD dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
	PREQUESTINFO pReqInfo = (PREQUESTINFO)pFC->pFilterContext;
	LPSTR lpszBuff = 0, lpPtr = 0;
	unsigned int postLen, len;
	int status = 0;
	char *hascKey = 0, *newUrl = 0, *errorString = "";
	int certStatus = 0;
	client_data_t *clientData = 0;
	char cookieVal[1], uri[PTA_LARGE_BUF_MAX];

	/* artf14514: Changes Begin */
	int MessageLength;
	char *lpszData;
	/* artf14514: Change End */

	cookieVal[0] = '\0';

	postLen = pReqInfo->cbPostLen;

#ifdef DEBUGMSG
	Debug((DEST, "isapi_ssc: Raw2 postlen=%d buflen=%d", postLen, pReadData->cbInData));
	gCfg.InfoLog(0, "isapi_ssc: Raw2 postlen=%d buflen=%d", postLen, pReadData->cbInData);
#endif

	do {

		/* artf14514: Changes Begin */
		/* Moved the reading of data outside if (pReqInfo->rqUri && postLen && (strcmp(pReqInfo->rqUri, "/vsadmin/post")==0)) */
		lpszBuff = pReqInfo->pRequestPost;
		len = pReadData->cbInData;
		lpPtr = pReadData->pvInData;

		if (postLen && lpszBuff) {

#ifdef DEBUGMSG
			Debug((DEST, "isapi_ssc: Raw2 accumulating %d bytes, previous data %d bytes", len, pReqInfo->cbPostAccumulated));
			gCfg.InfoLog(0, "isapi_ssc: Raw2 accumulating %d bytes, previous data %d bytes", len, pReqInfo->cbPostAccumulated);
#endif

		/* check to make sure data doesn't exceed content length */
			if( len > pReqInfo->cbPostLen - pReqInfo->cbPostAccumulated )
				len = pReqInfo->cbPostLen - pReqInfo->cbPostAccumulated;

			memcpy(lpszBuff + pReqInfo->cbPostAccumulated, lpPtr, len);     
			pReqInfo->cbPostAccumulated += len;
			lpszBuff[pReqInfo->cbPostAccumulated] = '\0';		 
		} else {
			dwRet = SF_STATUS_REQ_ERROR;
			break;
		}

		/* if pReqInfo->rqUri is null we can assume SF_NOTIFY_PREPROC_HEADERS was not received */
		if (!(pReqInfo->rqUri)) {
#ifdef DEBUGMSG
			Debug((DEST, "isapi_ssc: PreProc Headers was not called"));
			gCfg.InfoLog(0, "isapi_ssc: PreProc Headers was not called");
#endif
			pReqInfo->bPreProcSkipped = TRUE;

			dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
			break;
		}

		if (pReqInfo->rqUri && postLen && lpszBuff && (strcmp(pReqInfo->rqUri, "/vsadmin/post")==0)) {

			/*

			lpszBuff = pReqInfo->pRequestPost;
			len = pReadData->cbInData;
			lpPtr = pReadData->pvInData;

			if (lpszBuff) {

#ifdef DEBUGMSG
				Debug((DEST, "isapi_ssc: Raw2 accumulating %d bytes, previous data %d bytes", len, pReqInfo->cbPostAccumulated));
				gCfg.InfoLog(0, "isapi_ssc: Raw2 accumulating %d bytes, previous data %d bytes", len, pReqInfo->cbPostAccumulated);
#endif

				// check to make sure data doesn't exceed content length
				if( len > pReqInfo->cbPostLen - pReqInfo->cbPostAccumulated )
					len = pReqInfo->cbPostLen - pReqInfo->cbPostAccumulated;

					memcpy(lpszBuff + pReqInfo->cbPostAccumulated, lpPtr, len);     
					pReqInfo->cbPostAccumulated += len;
					lpszBuff[pReqInfo->cbPostAccumulated] = '\0';	
			*/
			/* artf14514: Changes End : Moved this outside the if loop */

			if (pReqInfo->cbPostAccumulated >= pReqInfo->cbPostLen) {
				/* we won't be back here again.  Do the authentication. */

				/* acquire the critical section lock */
				if (WaitForSingleObject(hMutex, INFINITE)!=WAIT_OBJECT_0) {
					status = VS_ERR_MUTEX;
#ifdef DEBUGMSG
					gCfg.InfoLog(0, "isapissc: vsReadRawData2 error acquiring hMutex");
#endif 
					break;
				}
#ifdef DEBUGMSG
				gCfg.InfoLog(0, "isapissc: vsReadRawData2 Acquired hMutex");
#endif 


				status = vsPTADoAuthorization(pFC, pReqInfo, &hascKey, &clientData, 
											  &certStatus, &newUrl, uri);

				if (status) {
					/* Log Errors */
					sscErrorString(&errorString, status);
					vsLogMessage(LOG_FAILURE, "%s", errorString);

					/* Log denials? */
					if (gCfg.logSecurity && certStatus) {
						vsLogMessage(LOG_SECURITY, "Certificate %s for %s", 
						vsPTACertStatusString(certStatus), vsPTAGetUserName(clientData));
					}

					/* And set up to send an error page later. */
					vs_preq_nvreplace(&pReqInfo->sscStatus, errorString);
					dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
				} else {
					dwRet = vsEvalStatus(pFC, 0, pReqInfo, dwRet, cookieVal, uri, 
										 hascKey, 0, newUrl, certStatus, clientData);

					/* artf14514: Changes Begin : For IIS 6 send the page from here since SF_NOTIFY_SEND_RAW_DATA might not occur*/
					if(IISVERSION == IIS6) {
						dwRet = vsSSCSend(pFC, pReqInfo);

						MessageLength = pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2;
						lpszData = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2, 0);
						memcpy(lpszData, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
						memcpy((unsigned char *)lpszData+pReqInfo->lpszHeaderLen, "\r\n", 2);
						memcpy((unsigned char *)lpszData + pReqInfo->lpszHeaderLen+2, pReqInfo->page.data, pReqInfo->page.len);

						pFC->WriteClient(pFC, lpszData, &MessageLength, 0);

						if (pReqInfo->bKeepAlive) {
							dwRet = SF_STATUS_REQ_FINISHED_KEEP_CONN;
						} else {
							dwRet = SF_STATUS_REQ_FINISHED;
						}
					}
					/* artf14514: Changes End */
				}


				/* release the lock */
				if (ReleaseMutex(hMutex)==0) {
					vsLogMessage(LOG_FAILURE, "vsReadRawData2 : Error releasing mutex %x", GetLastError());
				}
#ifdef DEBUGMSG
				gCfg.InfoLog(0, "isapissc: vsReadRawData2: Released hMutex");
#endif 
				sscT_free((unsigned char *) hascKey);


				/* Can't call sscSend here. It calls sendResponseHeader.  It seems like */
				/* IIS doesn't like that called inside a read raw filter. We will use */
				/* the logging event handler to do the send and release the mutex. */
				/* artf14514: Changes End : Moved this outside the if loop */
				/*
				}
				*/
				/* artf14514: Changes End : Moved this outside the if loop */
				/* else this function will be called again to accumulate more POSTed data. */

			}
		} else {
			/* Too much posted or NULL buffer. */
			dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
		}
		/*
		}
		*/
	}while (0);

	return dwRet;
}

/****************************************************************************************
* 
* Function:  HandleEvent_ReadRawData
* 
* Here we handle the SF_NOTIFY_READ_RAW_DATA event. We scan the body of raw request.
* we keep a copy of the request so we can analyze it in PREPROC_HEADERS
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pReadData (IN) - data specific to RAW_DATA event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleEvent_ReadRawData(HTTP_FILTER_CONTEXT *pFC, 
                              PHTTP_FILTER_RAW_DATA pReadData) {

  DWORD           dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  PREQUESTINFO    pReqInfo;    
  LPSTR lpszBuff;
  LPSTR lpPtr = 0, lpEnd = 0;
  int postLen, dif;

#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: ReadRawData"));
  gCfg.InfoLog(0, "isapi_ssc: ReadRawData");
#endif

  if (pFC->pFilterContext && ((PREQUESTINFO) pFC->pFilterContext)->bDoReadRaw2) {
    return vsReadRawData2(pFC, pReadData);
  }

  /* Allocate some space to save our own request context information */
  pFC->pFilterContext = pFC->AllocMem(pFC, sizeof(REQUESTINFO), 0);

  if (pFC->pFilterContext == NULL) {
    dwRet = SF_STATUS_REQ_ERROR;
  }
  else {
    /*  Initialize our request information to be saved across notifications
        for this request. */
    pReqInfo = (PREQUESTINFO)pFC->pFilterContext;

    memset(pReqInfo, 0, sizeof(*pReqInfo)); /* init everything to 0. */

    /* Now read the post (if there is one). */
    postLen = ExtractContentLength(pReadData->pvInData, pReadData->cbInData);

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: ReadRawData postlen=%d buflen=%d", postLen, pReadData->cbInData));
	gCfg.InfoLog(0, "isapi_ssc: ReadRawData postlen=%d buflen=%d", postLen, pReadData->cbInData);
#endif

    if (postLen) {
      lpPtr = pReadData->pvInData;
      lpEnd = lpPtr + pReadData->cbInData;

#ifdef DEBUGMSG
      Debug((DEST, "isapi_ssc: ReadRawData +4"));
	  gCfg.InfoLog(0, "isapi_ssc: ReadRawData +4");
#endif

      /* Find the beginning of the message body */
      while (lpPtr+4 < lpEnd && !(*lpPtr=='\r' && *(lpPtr+1)=='\n' 
                                  && *(lpPtr+2)=='\r' && *(lpPtr+3)=='\n')) lpPtr++;
		
      /* if we're past the end and aren't at the end of the headers, error. */
      /* This might be ok, but I've never seen this behavior from IIS. */
      /* Either it gives the whole post, or it gives just the header the first time. */
      if (lpPtr+4 >= lpEnd && !(*lpPtr=='\r' && *(lpPtr+1)=='\n' 
                                && *(lpPtr+2)=='\r' && *(lpPtr+3)=='\n')) {
        
#ifdef DEBUGMSG
        Debug((DEST, "isapi_22 +4 %x %x %x %x, %x %x", 
               *(lpPtr+0), *(lpPtr+1), *(lpPtr+2), *(lpPtr+3), '\r', '\n'));
        Debug((DEST, "isapi_ssc: ReadRawData +4 error %x %x %x", 
               pReadData->pvInData, lpPtr, lpEnd));
#endif
        dwRet = SF_STATUS_REQ_ERROR;;
      }
      else {
        lpPtr += 4;
        dif = lpEnd - lpPtr;

        if (dif > postLen) {
          /* Netscape client adds something extra. Starts with 'data' so assume */
          /* it's correct to chop off the end. */
          dif = postLen;
        }

#ifdef DEBUGMSG
        Debug((DEST, "isapi_ssc: ReadRawData: dif=%d, con-len=%d", dif, postLen));
		gCfg.InfoLog(0, "isapi_ssc: ReadRawData: dif=%d, con-len=%d", dif, postLen);
#endif

        if ((lpszBuff = pFC->AllocMem(pFC, postLen + 1, 0)) == NULL) {
          SetLastError(ERROR_NOT_ENOUGH_MEMORY);
          dwRet = SF_STATUS_REQ_ERROR;
        }
        else {

          memcpy(lpszBuff, lpPtr, dif);
          lpszBuff[dif]='\0';
          pReqInfo->pRequestPost = lpszBuff;
          pReqInfo->cbPostLen = postLen;
          
          if (dif < postLen) {
            pReqInfo->bDoReadRaw2 = 1;
			pReqInfo->cbPostAccumulated = dif;
#ifdef DEBUGMSG
			Debug((DEST, "isapi_ssc: ReadRawData: Setting bDoReadRaw2 as 1"));               
			gCfg.InfoLog(0, "isapi_ssc: ReadRawData: Setting bDoReadRaw2 as 1");
#endif

          }
        }

      }
    }
  }
  return dwRet;
}



/****************************************************************************************
* 
* Function:  vsEvalStatus
* 
* Here in this routine, we evaluate the status for the current request. The status is 
* stored in pReqInfo->sscStatus and depending on the status vsSSCSend will send
* the appropriate response
* 
* This routine also calls the Check routine for the authorization dll if
* confiugured to do so 
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pPreProcData (IN) - pointer to data for the PreProc event
*     pReqInfo (IN, OUT) - pointer to request info data structure
*     initialRC (IN) - the initial return code
*     cookieVal (OUT) - the cookie value to send
*     uri (IN) - requested URI
*     hascKey (IN) - ascii session key for the user
*     adminOp (IN) - whether this is an admin operation
*     newUrl (IN) -
*     certStatus (IN) - the status of the certificate 
*     clientData (IN) - pointer to session information
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD vsEvalStatus(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_PREPROC_HEADERS pPreProcData,
                   PREQUESTINFO pReqInfo, DWORD initialRC, 
                   char *cookieVal, char *uri, char *hascKey, char *adminOp,
                   char *newUrl, int certStatus, client_data_t *clientData) {

  DWORD rc = initialRC; /* It's bad form to modify a passed in parameter. */

  /* Call out to user plugin. */
  /* We don't call the plugin if there's no cookie, and status is VALID. */
  /* In that case, we set a cookie and the plugin will be called on the redirect. */
  if (gCfg.dlCheck && !adminOp && (cookieVal[0] || certStatus != CS_VALID)) {
    if (clientData) {
      certStatus = gCfg.dlCheck(certStatus, uri, 
                                clientData->cert.data, clientData->cert.len,
                                clientData->pkcs7, vsPTAGetUserName(clientData));
    }
    else {
      certStatus = gCfg.dlCheck(certStatus, uri, 0, 0, 0, 0);
    }
      
    /* If they changed !valid->valid, must set a cookie. */
    if (certStatus==CS_VALID && !cookieVal[0]) {
      setCookie(pFC, hascKey, 0);
      sprintf(cookieVal, hascKey);
    }
  }

  if (certStatus==CS_VALID && !adminOp) {
      
    /* Set the real url */
    if (newUrl) { 
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "set real url to %s", newUrl);
#endif
      vs_preq_nvreplace(&pReqInfo->validPost, newUrl);
    }

    /* need to set up pblock/env vars here since we won't have them in Send(). */
    if (cookieVal[0] && gCfg.addEnvVars && pPreProcData) {
      // What if cookie==0, but plugin says valid? 
      // We now sprintf into cookieVal above. Does that cover it?
      vsAddValidEnvVars(pFC, pPreProcData, clientData);
    }

    vs_preq_nvreplace(&pReqInfo->sscStatus, "valid");
    rc = SF_STATUS_REQ_NEXT_NOTIFICATION; /* Not changing uri value.  Just continue. */
      
  }
  else if (certStatus==CS_VALID && adminOp) {

    vs_preq_nvreplace(&pReqInfo->sscStatus, "admin");
    vs_preq_nvreplace(&pReqInfo->adminOp, adminOp);
    rc = SF_STATUS_REQ_NEXT_NOTIFICATION; /* Not changing uri value.  Just continue. */
  }
  else {
      
    /* If they were denied, send the login or error page. */
    /* which one is determined by the status code. */

    /* Log denials if it is not a login request */
    if (gCfg.logSecurity && certStatus != 0) {
      vsLogMessage(LOG_SECURITY, "Certificate %s for %s",
                   vsPTACertStatusString(certStatus), vsPTAGetUserName(clientData));
    }

    /* Set the status code for the send function. */
    if (uri[0]) { vs_preq_nvreplace(&pReqInfo->oldUri, uri); }
    else { vs_preq_nvreplace(&pReqInfo->oldUri, ""); }

    if (certStatus==0) {
      vs_preq_nvreplace(&pReqInfo->sscStatus, "login");
    }
    else if (certStatus==CS_SSC_COOKIE_EXPIRED ||
             certStatus==CS_SSC_POST_EXPIRED) {
      vs_preq_nvreplace(&pReqInfo->sscStatus, "expired");
    }
    else if (certStatus==CS_SSC_LOGOUT) {
      vs_preq_nvreplace(&pReqInfo->sscStatus, "logout");
    }
    else {
      vs_preq_nvreplace(&pReqInfo->sscStatus, vsPTACertStatusString(certStatus));
    }


    /* Go on to our service function. */
    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;

  }
#ifdef DEBUGMSG
			gCfg.InfoLog(0, "isapi_ssc: returnin from vsEvalStatus");
#endif

  return rc;
}

/****************************************************************************************
* 
* Function:  vsPTADoAuthorization
* 
* Here we scan the body of raw request.
* we keep a copy of the request so we can analyze it in PREPROC_HEADERS
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pReqInfo (IN) - request data structure
*     lock (IN) - if you need to lock the clientData structure so that it won't be garbage
*                 collected. 
*     pHascKey (OUT) - the ascii session key 
*     pClientData (OUT) - pointer to client session information
*     pCertStatus (OUT) - cert status 
*     pNewUrl (OUT) - new URL 
*     uri (OUT) - url
*
* Return values : 0 - success
*                errorcode - otherwise      
* 
* Change History
* - 
* -
*
*****************************************************************************************/
int vsPTADoAuthorization(HTTP_FILTER_CONTEXT *pFC, PREQUESTINFO pReqInfo, 
                      char **pHascKey, client_data_t **pClientData, 
                      int *pCertStatus, char **pNewUrl, char *uri) {

  int status = 0;
  ITEM outDigest = {0}, outCert = {0};
  char *outPKCS7 = 0;
  VSVAL_UserCtx ctx = {0};

  ctx.logFn = gCfg.InfoLog;
#ifdef DEBUGMSG
	  Debug((DEST, "isapissc.c: vsDoAuthorization"));
	  gCfg.InfoLog(0, "isapissc.c: vsDoAuthorization");
#endif

  do {
    /* Allocs memory */
    if (status = vsGetPostedData(pFC, pReqInfo, &outPKCS7, &outDigest, &outCert)) {
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "get=0x%x = %d", status, status);
	  Debug((DEST, "get=0x%x = %d", status, status));
#endif
      /* In this case we can't save these in the hash table in authorizePost. */
      /* Free them now. */
      sscT_free((unsigned char *) outPKCS7);
      sscT_free((unsigned char *) (outCert.data));

      break;
    }


    /* dup the return value since it's a static buffer. */
	*pHascKey = (unsigned char*) sscT_malloc (2*outDigest.len+1);
	VSVAL_Bin2Hasc(gCfg.vsValSDK, &ctx, outDigest.data, outDigest.len, *pHascKey);
    /*Bin2Hasc(*pHascKey, outDigest.data, outDigest.len);*/
    
    if (*pHascKey==0) {
      /* In this case we can't save these in the hash table in authorizePost. */
      /* Free them now. */
      sscT_free((unsigned char *) outPKCS7);
      sscT_free((unsigned char *) (outCert.data));

      status = VS_ERR_NO_MEM;
      break;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "hascKey=%s", *pHascKey);
#endif

    /* See if the post holds a good authentication. */
    *pClientData = 0;
	 
	*pCertStatus = vsPTAAuthorizePost(gCfg.hTable, outDigest,
			                           &outCert, outPKCS7, pClientData);

    if (*pCertStatus==CS_VALID) {
      setCookie(pFC, *pHascKey, 0);
      *pNewUrl = (*pClientData)->url;
    }
    else if (*pClientData) {
      /* If there's an error or expiration, don't redirect to vsadmin/post. */
      /* Use the original url.  This clobbers uri for anyone later. */
      sprintf(uri, (*pClientData)->url);
      *pNewUrl = (*pClientData)->url;
    }
    else {
      /* Doesn't work for bad sigs since we stored the url in the hash table */
      /* along with the good signature. Can't find it given only the bad hash. */
      uri[0] = '\0';
      /* Send them to "/". Only needed/used by user plugins that change a bad */
      /* (!CS_VALID) status to CS_VALID. We must send them somewhere. */
      *pNewUrl = "/";
    }

    sscT_free(outDigest.data);
    /* sscT_free(outCert.data); This is saved in the hash table. don't free it. */

  } while (0);

  return status;
}

/****************************************************************************************
* 
* Function:  HandleEvent_PreProcHeaders
* 
* handle the SF_NOTIFY_PREPROC_HEADERS event. This is where we analyse the actual 
* request. This is the routine that does the meat of the processing
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pPreProcData (IN) - data specific to SF_NOTIFY_PREPROC_HEADERS event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleEvent_PreProcHeaders(HTTP_FILTER_CONTEXT *pFC, 
								 PHTTP_FILTER_PREPROC_HEADERS pPreProcData) {

  int status = 0;
  DWORD rc = SF_STATUS_REQ_ERROR;

  char *errorString = "", *newUrl;
  client_data_t *clientData;
  char cookieVal[PTA_LARGE_BUF_MAX], *hascKey=0, *adminOp = 0, *denyHasc;
  int certStatus = 0;
  char adminOpBuf[PTA_LARGE_BUF_MAX];
  CHAR tmpBuf[PTA_LARGE_BUF_MAX], uri[PTA_LARGE_BUF_MAX];
  DWORD tmpLen, uriLen;
#ifdef DEBUGMSG
  char rqMethod[PTA_LARGE_BUF_MAX], rqVer[PTA_LARGE_BUF_MAX];
  DWORD rqMethodLen, rqVerLen;
#endif
  PREQUESTINFO	pReqInfo;


  VSVAL_UserCtx ctx = {0};
  ctx.logFn = gCfg.InfoLog;


  do {

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: PreProcHeaders"));
	gCfg.InfoLog(0, "isapi_ssc: PreProcHeaders");
#endif

    /* Get our handle that lasts throughout the request. */
    pReqInfo = (PREQUESTINFO)pFC->pFilterContext;


    /* Display User-Agent header */
    tmpBuf[0] = '\0';
    tmpLen = PTA_LARGE_BUF_MAX;
    pPreProcData->GetHeader(pFC, "User-Agent:", tmpBuf, &tmpLen);
    pReqInfo->bIsMSIE = (tmpLen && (strstr(tmpBuf, "MSIE") != 0));
#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: PreProcHeaders: User-Agent = %s (isIE=%d)",
           tmpBuf, pReqInfo->bIsMSIE));
#endif


    /* Show http request */
    uriLen = PTA_LARGE_BUF_MAX;
    uri[0] = '\0';
    if (! pPreProcData->GetHeader(pFC, "url", uri, &uriLen)) {
      gCfg.InfoLog(0, "No mem for url");
      /* can return in middle of fn since we haven't locked the mutex yet. */
      SetLastError(ERROR_NOT_ENOUGH_MEMORY);
      return SF_STATUS_REQ_ERROR;
    }

    pReqInfo->rqUri = sscT_strdup(uri);
    if (pReqInfo->rqUri==0) {
      gCfg.InfoLog(0, "No mem for strdup url");
      /* can return in middle of fn since we haven't locked the mutex yet. */
      SetLastError(ERROR_NOT_ENOUGH_MEMORY);
      return SF_STATUS_REQ_ERROR;
    }

    /* Pretend POSTs to our special url aren't. We don't use this header anyway. */
    /* Otherwise there are "405 method not allowed" errors. */
    if (strcmp(uri, "/vsadmin/post")==0) {
      pPreProcData->SetHeader(pFC, "method", "HEAD");
    }

#ifdef DEBUGMSG
    /* This is just for debugging, so we don't check for buffer lengths. */
    rqMethodLen = rqVerLen = PTA_LARGE_BUF_MAX;
    rqMethod[0] = rqVer[0] = '\0';
    pPreProcData->GetHeader(pFC, "method", rqMethod, &rqMethodLen);
    pPreProcData->GetHeader(pFC, "version", rqVer, &rqVerLen);
    Debug((DEST, "isapi_ssc: %s %s %s", rqMethod, uri, rqVer ));
	gCfg.InfoLog(0, "isapi_ssc: %s %s %s", rqMethod, uri, rqVer);
#endif

    /* See if this is a keep-alive connection. */
    tmpLen = PTA_LARGE_BUF_MAX;
    tmpBuf[0] = '\0';
    pPreProcData->GetHeader(pFC, "Connection:", tmpBuf, &tmpLen);
    pReqInfo->bKeepAlive = (tmpLen && (_stricmp(tmpBuf, "Keep-Alive")==0));

    pReqInfo->contentType[0] = '\0';
    tmpLen = PTA_TINY_BUF_MAX; /* This does NOT correspond to tmpBuf! */
    pPreProcData->GetHeader(pFC, "content-type:", pReqInfo->contentType, &tmpLen);

    if ((! vsIsProtected(uri,pFC)) ||
        (gCfg.protectJavaDirs==0 && strstr(uri, "/java/"))) {

#ifdef DEBUGMSG
      Debug((DEST, "skipping uri=%s", uri));
	  gCfg.InfoLog(0, "skipping uri=%s", uri);
#endif
      /* can return in middle of fn since we haven't locked the mutex yet. */
      return SF_STATUS_REQ_NEXT_NOTIFICATION;

    }
    else {
      pReqInfo->bIsProtected = TRUE;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "uri=%s", uri);
#endif

    printCookies(pFC, pPreProcData);

#ifdef DEBUGMSG
	gCfg.InfoLog(0, "isapissc: before PreProcData Acquiring hMutex");
#endif 
    /* acquire the critical section lock */
    if (WaitForSingleObject(hMutex, INFINITE)!=WAIT_OBJECT_0) {
      status = VS_ERR_MUTEX;
#ifdef DEBUGMSG
	gCfg.InfoLog(0, "isapissc: PreProcData error acquiring hMutex");
#endif 
      break;
    }
#ifdef DEBUGMSG
	gCfg.InfoLog(0, "isapissc: PreProcData Acquired hMutex");
#endif 

    clientData = 0;
    cookieVal[0] = '\0';
    newUrl = 0;

    /* We will use cookieVal to know if we are actually sending a page. */
    /* To get a page, the user must be presenting a cookie, vsadmin/post sets it and */
    /* does a redirect. */

    /* First, examine the cookie presented. */
    if ((findMyCookie(pFC, pPreProcData, cookieVal)==0) && cookieVal[0]) {
      
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
          if (gCfg.adminIssuerSerial && cookieVal[0] &&
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
        cookieVal[0] = '\0';

        if (strcmp(uri, "/vsadmin/post")==0) {

          if (pReqInfo->bDoReadRaw2==0) {
            
            status = vsPTADoAuthorization(pFC, pReqInfo, &hascKey, &clientData, 
                                       &certStatus, &newUrl, uri);
          }

        }
        else {
          /* no access to special urls w/o authentication. */
          /* Must send login page. */
        }
      }
    }
    else if (_stricmp(uri, gCfg.logoutUrl)==0) {
      
      if (certStatus==CS_VALID || certStatus==CS_SSC_COOKIE_EXPIRED) {

        /* If they are expired, it's better to show them the logout page than error. */

        /* Log out the user by removing the authentication from the hash table. */
	VSVAL_HashDeleteHasc(gCfg.vsValSDK, &ctx, gCfg.hTable, cookieVal);

        certStatus = CS_SSC_LOGOUT;
      }
    }

  /* If we are sending the page directly, must get the server to ignore this. */
  /* Otherwise, it sends "304 not modifed" and we don't get our page sent. */
  /* Ditch the caching info. Should be smarter, but that's hard since we might */
  /* not know enough until after raw2. */
  pPreProcData->SetHeader(pFC, "If-Modified-Since:", 0);

  if (status) {

    /* Log Errors */
    sscErrorString(&errorString, status);
    vsLogMessage(LOG_FAILURE, "%s", errorString);
    
    /* Log denials? */
    if (gCfg.logSecurity && certStatus) {
      vsLogMessage(LOG_SECURITY, "Certificate %s for %s", 
                   vsPTACertStatusString(certStatus), vsPTAGetUserName(clientData));
    }

    /* And set up to send an error page later. */
    vs_preq_nvreplace(&pReqInfo->sscStatus, errorString);
    rc = SF_STATUS_REQ_NEXT_NOTIFICATION;
  }
  else {
    if (pReqInfo->bDoReadRaw2==0) {
      rc = vsEvalStatus(pFC, pPreProcData, pReqInfo, rc, cookieVal, uri, hascKey, 
                        adminOp, newUrl, certStatus, clientData);
    }
    else {
		 // check the certificate status for requests coming in multiple notifications.
		 // vsadmin requests are handled in vsReadRawData2 function
	  if ( strcmp(uri, "/vsadmin/post") != 0 )
			rc = vsEvalStatus(pFC, pPreProcData, pReqInfo, rc, cookieVal, uri, hascKey, 
							adminOp, newUrl, certStatus, clientData);
	  else
		  rc = SF_STATUS_REQ_NEXT_NOTIFICATION;
    }
  }

  if (pReqInfo->bDoReadRaw2==0 || (strcmp(uri, "/vsadmin/post") != 0) ) {
    sscT_free((unsigned char *) hascKey);

    /* Call the send function here for ISAPIs (no separate service fn.) */
    rc = vsSSCSend(pFC, pReqInfo);
    /* Otherwise we'll release it in read raw 2 */
  }

    /* release the lock */
  if (ReleaseMutex(hMutex)==0) {
      vsLogMessage(LOG_FAILURE, "PreProcData: Error releasing mutex %x", GetLastError());
  }

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "isapissc: PreProcData Released hMutex");
#endif 

  } while (0);

  return rc;
}


/****************************************************************************************
* 
* Function:  HandleEvent_Log
* 
* Here we handle the SF_NOTIFY_LOG event. We call vsSSCSend to actually send the 
* headers and store the page to be sent in the request info data structure
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pLogData (IN) - data specific to SF_NOTIFY_LOG event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleEvent_Log(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_LOG pLogData) {

  DWORD   dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  PREQUESTINFO	pReqInfo;

  /* artf14514: Changes Begin */
  int MessageLength;
  char *lpszData;
  int status = 0;
  char *hascKey = 0, *newUrl = 0, *errorString = "";
  int certStatus = 0;
  client_data_t *clientData = 0;
  char  cookieVal[1], uri[PTA_LARGE_BUF_MAX];

  /* artf14514: Change End */



  pReqInfo =(PREQUESTINFO)pFC->pFilterContext;

  /* Show the server variables. */
  /* dump_vars(pFC); */
    
  /* Display client IP address */
#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: Log: Client IP address = %s", pLogData->pszClientHostName));
  gCfg.InfoLog(0, "isapi_ssc: Log: Client IP address = %s", pLogData->pszClientHostName);
#endif

  do {
	if (pReqInfo->bDoReadRaw2 && (strcmp(pReqInfo->rqUri, "/vsadmin/post")==0)) {

#ifdef DEBUGMSG
		gCfg.InfoLog(0, "isapissc: before HandleEvent_log Acquiring hMutex");
#endif 
		/* acquire the critical section lock */
		if (WaitForSingleObject(hMutex, INFINITE)!=WAIT_OBJECT_0) {
#ifdef DEBUGMSG
			gCfg.InfoLog(0, "isapissc: HandleEvent_Log error acquiring hMutex");
#endif
			break;
		}
#ifdef DEBUGMSG
		gCfg.InfoLog(0, "isapissc: HandleEvent_Log Acquired hMutex");
#endif 

		/* artf14514: Changes Begin */
		if(IISVERSION != IIS6) {
			dwRet = vsSSCSend(pFC, pReqInfo);
		} else {
			/* Check if the PreProc Headers was called before ReadRawData2 */
			/* if not do the authorization part here */
			/* acquire the critical section lock */
			if(pReqInfo->bPreProcSkipped) {
			
				pReqInfo->bPreProcSkipped = FALSE;


				status = vsPTADoAuthorization(pFC, pReqInfo, &hascKey, &clientData, 
											  &certStatus, &newUrl, uri);

				if (status) {
					/* Log Errors */
					sscErrorString(&errorString, status);
					vsLogMessage(LOG_FAILURE, "%s", errorString);

					/* Log denials? */
					if (gCfg.logSecurity && certStatus) {
						vsLogMessage(LOG_SECURITY, "Certificate %s for %s", 
						vsPTACertStatusString(certStatus), vsPTAGetUserName(clientData));
					}

					/* And set up to send an error page later. */
					vs_preq_nvreplace(&pReqInfo->sscStatus, errorString);
					dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
				} else {
					dwRet = vsEvalStatus(pFC, 0, pReqInfo, dwRet, cookieVal, uri, 
										 hascKey, 0, newUrl, certStatus, clientData);

					/* artf14514: Changes Begin : For IIS 6 send the page from here since SF_NOTIFY_SEND_RAW_DATA might not occur*/
					if(IISVERSION == IIS6) {
						dwRet = vsSSCSend(pFC, pReqInfo);

						MessageLength = pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2;
						lpszData = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2, 0);
						memcpy(lpszData, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
						memcpy((unsigned char *)lpszData+pReqInfo->lpszHeaderLen, "\r\n", 2);
						memcpy((unsigned char *)lpszData + pReqInfo->lpszHeaderLen+2, pReqInfo->page.data, pReqInfo->page.len);

						pFC->WriteClient(pFC, lpszData, &MessageLength, 0);

						if (pReqInfo->bKeepAlive) {
							dwRet = SF_STATUS_REQ_FINISHED_KEEP_CONN;
						} else {
							dwRet = SF_STATUS_REQ_FINISHED;
						}
					}
					/* artf14514: Changes End */
				}

			}

			/* artf14514: Changes End */

		}
    
		/* release the lock */
		if (ReleaseMutex(hMutex)==0) {
			vsLogMessage(LOG_FAILURE, "HandleEvent_Log : Error releasing mutex %x", GetLastError());
		}
#ifdef DEBUGMSG
		gCfg.InfoLog(0, "isapissc: HandleEvent_Log: Release hMutex");
#endif 
	}

	if ( (pReqInfo->bDoReadRaw2 == 0) || (strcmp(pReqInfo->rqUri, "/vsadmin/post")!=0) ){

		if (pReqInfo->bKeepAlive) {
			dwRet = SF_STATUS_REQ_FINISHED_KEEP_CONN;
		}
		  else {
			dwRet = SF_STATUS_REQ_FINISHED;
		}

	}

  }while (0);

  return dwRet;
}


/****************************************************************************************
* 
* Function:  HandleEvent_EndOfNetSession
* 
* Here we handle the SF_NOTIFY_END_OF_NET_SESSION event. This is used by us mainly to 
* free the memory allocated in the request data structure
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*
* Return values : SF_STATUS_REQ_NEXT_NOTIFICATION - successful       
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleEvent_EndOfNetSession(HTTP_FILTER_CONTEXT *pFC) {

    DWORD			dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
    PREQUESTINFO	pReqInfo;

    pReqInfo =(PREQUESTINFO)pFC->pFilterContext;

#ifdef DEBUGMSG
    Debug((DEST, "isapi_ssc: EndOfNetSession"));
	gCfg.InfoLog(0, "isapi_ssc: EndOfNetSession");
#endif

    /*  The end of the request - so cleanup all data allocated
        during the course of the request. Note that any AllocMem()
        data structures are freed automatically by the server. */

    if (pReqInfo) {
      /* Clean up memory we've allocated. */
      /* Things using AllocMem() are automatically freed. */
      if (pReqInfo->rqUri) sscT_free((unsigned char *) pReqInfo->rqUri);

      if (pReqInfo->sscStatus) sscT_free((unsigned char *) pReqInfo->sscStatus);
      if (pReqInfo->validPost) sscT_free((unsigned char *) pReqInfo->validPost);
      if (pReqInfo->adminOp) sscT_free((unsigned char *) pReqInfo->adminOp);
      if (pReqInfo->oldUri) sscT_free((unsigned char *) pReqInfo->oldUri);

#ifdef DEBUGMSG
      Debug((DEST, "isapi_ssc: EndOfNetSession page 0x%x, len = %d",
             pReqInfo->page.data, pReqInfo->page.len));
#endif

      sscT_free(pReqInfo->page.data);
      sscT_free(pReqInfo->prePageJs.data);

    }

    return dwRet;
}

/****************************************************************************************
* 
* Function:  HandleEvent_SendRawData
* 
* Here we handle the SF_NOTIFY_SEND_RAW_DATA event. We send the output page that is 
* create earlier in the pRequestInfo.page. 
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pSendData (IN) - data specific to SF_NOTIFY_SEND_RAW_DATA event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleEvent_SendRawData(HTTP_FILTER_CONTEXT *pFC, 
                              PHTTP_FILTER_RAW_DATA pSendData) {

  DWORD   dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  DWORD   dwBytes;
  LPSTR   lpszBuffer;
  PREQUESTINFO    pReqInfo;
  int goodServerHeader = 0;

#ifdef DEBUGMSG
  FILE *fp;
#endif

  pReqInfo = (PREQUESTINFO)pFC->pFilterContext;

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "isapi_ssc: SendRawData");
  Debug((DEST, "isapi_ssc: SendRawData"));
#endif

  if (pReqInfo==0) {
    return SF_STATUS_REQ_ERROR;
  }

  if (pReqInfo->bIsProtected==0) {
	gCfg.InfoLog(0, "isapi_ssc: SendRawData - Not protected");
    return dwRet;
  }

	gCfg.InfoLog(0, "isapi_ssc: SendRawData - Protected");

  /* Capture beginning characters of the raw response */
  lpszBuffer = (char *) pFC->AllocMem(pFC, PTA_SMALL_BUF_MAX+1, 0);
  if (lpszBuffer==0) {
    return SF_STATUS_REQ_ERROR;
  }
  dwBytes = vsMIN(PTA_SMALL_BUF_MAX, pSendData->cbInData);

  memcpy(lpszBuffer, pSendData->pvInData, dwBytes);
  lpszBuffer[dwBytes]='\0';

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "isapi_ssc: SendRawData: Old Response[1-%d]", dwBytes);
  Debug((DEST, "isapi_ssc: SendRawData: Old Response[1-%d]", dwBytes));

  Debug((DEST, "isapi_ssc: SendRaw page 0x%x, len = %d",
         pReqInfo->page.data, pReqInfo->page.len));
#endif


  /*  Note that for each request SF_NOTIFY_SEND_RAW_DATA occurs at least twice. The
      first time when the server sends the header, and thereafter whenever 
      a write is issued to send the body of the response. We must stop the
      server sending the header since the Content-Length field will be wrong. */

  /* See if a header or the body of a response */
#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: SendRaw gotheader=%d, len=%d, done=%d",
         pReqInfo->bGotHeader, pReqInfo->page.len, pReqInfo->bDoneWithHeaders));

  gCfg.InfoLog(0, "isapi_ssc: SendRaw gotheader=%d, len=%d, done=%d",
         pReqInfo->bGotHeader, pReqInfo->page.len, pReqInfo->bDoneWithHeaders);

#endif

//artf14514: Changes Begin
	if(IISVERSION == IIS6) {
		  if( (pReqInfo->sscStatus == NULL) || 
			  (strcmp(pReqInfo->sscStatus, "valid")!=0) ||
			  (pReqInfo->bDoReadRaw2 && (strncmp(pReqInfo->rqUri, "/vsadmin/", 9)==0)) ) {
				if(!pReqInfo->bDoneWithHeaders) {
					  if (pReqInfo->lpszHeaderLen || pReqInfo->page.len) {
							pSendData->cbInData = pSendData->cbInBuffer = pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2;
							pSendData->pvInData = pFC->AllocMem(pFC, pReqInfo->lpszHeaderLen + pReqInfo->page.len + 2, 0);
							memcpy(pSendData->pvInData, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
							memcpy((unsigned char *)pSendData->pvInData+pReqInfo->lpszHeaderLen, "\r\n", 2);
							memcpy((unsigned char *)pSendData->pvInData + pReqInfo->lpszHeaderLen+2, pReqInfo->page.data, pReqInfo->page.len);
							pReqInfo->bDoneWithHeaders = 1;

					  } else {
						pSendData->cbInData = pSendData->cbInBuffer = 0;
						pSendData->pvInData = NULL;
					  }
				} else {
					pSendData->cbInData = pSendData->cbInBuffer = 0;
					pSendData->pvInData = NULL;
				}
		}
	}
	else if(IISVERSION == IIS5) {
//artf14514 : Changes End		
		  /* If we've already captured the response header... */
		  if (pReqInfo->bDoneWithHeaders) {
		    /* Send the entire response (including the saved header) */
		    dwRet = HandleResponseBody(pFC, pSendData);
		  }
		  else {
		    /* Save the server's header, or ours. */

		    /* If the header is from us... */
		    /* (We always send the first header since we call the server support function */
		    /* at a time before the web server normally would.) */ 
		    /* Except in raw2 case... then it's backwards. Get a bad header (ignore it) then */
		    /* save the good one and body. */

    if (pReqInfo->bDoReadRaw2 && (strcmp(pReqInfo->rqUri, "/vsadmin/post")==0)) {
		      if (pReqInfo->bGotHeader) {
		        /* Save our header. */
				dwRet = HandleResponseHeader(pFC, pSendData);
				pReqInfo->bDoneWithHeaders = 1;
		      }
		      else {
		        /* ignore the one from the server, and we're done. */
		        pReqInfo->bGotHeader = 1;

		        /* In the meantime convince the server not to send its header */
		        pSendData->cbInData = pSendData->cbInBuffer = 0;
		        pSendData->pvInData = NULL;
		      }
		    }
		    else if (pReqInfo->page.len) {
		      /* If we haven't got it yet, save it. */
      if (!pReqInfo->bGotHeader) {

		        dwRet = HandleResponseHeader(pFC, pSendData);
		        pReqInfo->bGotHeader = 1;

		      }
		      else {

		        /* ignore the one from the server, and we're done. */
		        pReqInfo->bDoneWithHeaders = 1;
		         
		        /* Does the server think it's sending a good page? */
		        //if (pReqInfo->lpszHeader && (strstr(pReqInfo->lpszHeader, "200 OK")==0)) goodServerHeader = 1;
        if (strstr(pReqInfo->lpszHeader, "200 OK")==0) goodServerHeader = 1;

		        /* In the meantime convince the server not to send its header */
		        pSendData->cbInData = pSendData->cbInBuffer = 0;
		        pSendData->pvInData = NULL;
		      }
		    }
		    else {
		      dwRet = HandleResponseHeader(pFC, pSendData);
		      pReqInfo->bGotHeader = 1;
		      pReqInfo->bDoneWithHeaders = 1;
		    }
		  }
		  
		  /* If the server thought it was sending an error page, it won't send a body. */
		  if (pReqInfo->bDoneWithHeaders && pReqInfo->lpszHeader && !goodServerHeader) {
		    dwRet = HandleResponseBody(pFC, pSendData);
		  }
				}

//artf14514: Changes Begin
#ifdef DEBUGMSG
  if(pSendData->pvInData) {
    Debug((DEST, "isapi_ssc: SendRawData - sending %d bytes", pSendData->cbInData));
	gCfg.InfoLog(0, "isapi_ssc: SendRawData - sending %d bytes", pSendData->cbInData);
	fp = fopen("c:\\temp\\senddata.txt", "a");
	fwrite(pSendData->pvInData, 1, pSendData->cbInData, fp);
	fclose(fp);
  } else {
    Debug((DEST, "isapi_ssc: SendRawData - No data"));
	gCfg.InfoLog(0, "isapi_ssc: SendRawData - No data");
  }
#endif
//artf14514: Changes End

  return dwRet;
}

/****************************************************************************************
* 
* Function:  HandleResponseHeader
* 
* Here we send the response headers. 
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pSendData (IN) - data specific to SF_NOTIFY_SEND_RAW_DATA event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleResponseHeader(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pSendData) {

  DWORD           dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  PREQUESTINFO    pReqInfo;

  pReqInfo = (PREQUESTINFO)pFC->pFilterContext;
#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: handle response header"));
#endif

  /* Allocate a buffer to store the header */
  pReqInfo->lpszHeader = pFC->AllocMem(pFC, pSendData->cbInData+1, 0);
  if (pReqInfo->lpszHeader == NULL) {
    SetLastError(ERROR_NOT_ENOUGH_MEMORY);
    dwRet = SF_STATUS_REQ_ERROR;
  }
  else {
    /* Save the header until we're ready to send the whole response */
    memcpy(pReqInfo->lpszHeader, (char*)pSendData->pvInData, pSendData->cbInData);
    pReqInfo->lpszHeader[pSendData->cbInData]='\0';
    pReqInfo->lpszHeaderLen = pSendData->cbInData;

    /* In the meantime convince the server not to send its header */
    pSendData->cbInData = pSendData->cbInBuffer = 0;
    pSendData->pvInData = NULL;				
  }

  return dwRet;
}

/****************************************************************************************
* 
* Function:  HandleResponseBody
* 
* Here we send the response body
* 
* Parameters:
*     pFC(IN) - pointer to the filter context
*     pSendData (IN) - data specific to SF_NOTIFY_SEND_RAW_DATA event
*
* Return values : various status codes that are specified by ISAPI, mainly
*                 SF_STATUS_REQ_NEXT_NOTIFICATION - successful 
*                 SF_STATUS_REQ_ERROR - on error, should not occur        
* 
* Change History
* - 
* -
*
*****************************************************************************************/
DWORD HandleResponseBody(HTTP_FILTER_CONTEXT *pFC, PHTTP_FILTER_RAW_DATA pSendData)
{
  DWORD           dwRet = SF_STATUS_REQ_NEXT_NOTIFICATION;
  PREQUESTINFO    pReqInfo;
  DWORD           cbRefs=0;
  int status = 0;
  int newLen;
  char *newData;

  pReqInfo = (PREQUESTINFO)pFC->pFilterContext;
#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: handle response body"));
#endif

  do {

    /* ->page holds the ENTIRE item. Send the header plus req->page.*/
    if (pReqInfo->page.len && pReqInfo->bSentPage==0) {
      newLen = pReqInfo->page.len + pReqInfo->lpszHeaderLen;
      newData = pFC->AllocMem(pFC, newLen + 1, 0);

      if (newData == 0) {
        status = VS_ERR_NO_MEM;
        break;
      }

      memcpy(newData, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);
      memcpy(newData + pReqInfo->lpszHeaderLen, pReqInfo->page.data, pReqInfo->page.len);
      newData[newLen] = '\0';
      pReqInfo->bSentPage = 1; /* Remember that we sent the whole page. */
    }
    else if (pReqInfo->bSentPage==0) {

      if (pReqInfo->bSentHeader) {
        /* We'll do the else clause first.  After we've sent the headers and preJs, */
        /* we just pass on the data for the rest of the chunks. */
        newLen = pSendData->cbInData;
        newData = pSendData->pvInData;
      }
      else {
        /* otherwise, send the header + prePageJs + serverBuffer */
        newLen = pSendData->cbInData + pReqInfo->lpszHeaderLen + pReqInfo->prePageJs.len;
        newData = pFC->AllocMem(pFC, newLen + 1, 0);

        if (newData == 0) {
          status = VS_ERR_NO_MEM;
          break;
        }

        /* Copy header... */
        memcpy(newData, pReqInfo->lpszHeader, pReqInfo->lpszHeaderLen);

        /* Copy prePageJs vars... The len will be 0 if we don't need them.*/
        memcpy(newData+pReqInfo->lpszHeaderLen, pReqInfo->prePageJs.data,
               pReqInfo->prePageJs.len);

        /* Copy any data we've gotten... */
        memcpy(newData+pReqInfo->lpszHeaderLen + pReqInfo->prePageJs.len,
               pSendData->pvInData, pSendData->cbInData);

        newData[newLen] = '\0';

        pReqInfo->bSentHeader = 1; /* Remember that we just sent the header. */
      }
    }
    else {
      newLen = 0;
      newData = 0;
    }

  } while (0);

  if (status) {

    if (status==VS_ERR_NO_MEM) SetLastError(ERROR_NOT_ENOUGH_MEMORY);

    dwRet = SF_STATUS_REQ_ERROR;
    newLen = 0;
    newData = 0;
  }

  pSendData->cbInBuffer = pSendData->cbInData = newLen;
  pSendData->pvInData = newData;

#ifdef DEBUGMSG
  Debug((DEST, "isapi_ssc: SendRawData: new response=\n"));
#endif

  return dwRet;
}

/****************************************************************************************
* 
* Function:  ExtractContentLength
* 
* This function extracts the content-length for a particular request from the request
* headers
* 
* Parameters:
*     lpszHeader(IN) - header
*     len (IN) - length of lpszHeader
*
* Return values : the content length       
* 
* Change History
* - 
* -
*
*****************************************************************************************/
INT ExtractContentLength(LPSTR lpszHeader, int len)
{
    LPSTR   pContLenPos = 0;
    CHAR    Length[12];
    INT	    i=0;
    INT	    cbLength=0;

    if (lpszHeader) {
      pContLenPos = pta_strstr_ni(lpszHeader, "Content-Length:", len);
    }

    if (pContLenPos > (lpszHeader + len)) {
#ifdef DEBUGMSG
      Debug((DEST, "isapi_ssc: extract found extra content-len ignored"));
#endif
      return 0; /* past where a null-terminator would be. */
    }

    if (pContLenPos) {
        /* Find the end of the header - should be a \r\n */
        while (*pContLenPos >= ' ') {
            if (isdigit(*pContLenPos))
                Length[i++]=*pContLenPos;
            ++pContLenPos; 
        }
        Length[i]='\0';
        cbLength = atoi(Length);
    }

    return cbLength;
}

