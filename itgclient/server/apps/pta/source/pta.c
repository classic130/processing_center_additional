
/****************************************************************************************
* 
* pta.c
* -----
* This is file that implements the routines that are defines in pta.h
* Add this file to your plugin/filter projects
*
* Author - Siddharth Bajaj 03/03/01
* 
* Change History
* -
* -
*
*****************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


#include "escape.h"
#include "pta.h"

#ifdef WIN32
#include <windows.h> /* Sleep. */
#include <process.h>  /* getpid */
#else
#include <unistd.h> /* for pid_t, sleep, getpid, etc.. */
#endif


/* The global PTA context */
VS_PTA_CONFIG gCfg = { 0 }; /* important global information. */


/****************************************************************************************
* 
* Function:  pta_time
* 
* This is the function that gets the current system time, which is number of 
* seconds since 1970 and adjusts it for the YEAR_BASE and GMT
*
* Parameters -
* theTime (OUT) - the current time
*
* Return values : none 
* 
* Change History
* -
* -
*
*****************************************************************************************/


void pta_time (PTATIME *theTime)
{
  time ((time_t *)theTime);

  /* Correct for a year base different than 1970 */
  (*theTime) -= TIME_ADJUSTMENT;

  /* Correct for local time to GMT */
  (*theTime) += (PTATIME)3600 * GMT_OFFSET;
}


/****************************************************************************************
* 
* Function:  pta_make_newline_null
* 
* This is the function that Replace newline characters in string with NULLs
*
* Parameters -
* str (IN, OUT) - the string to be modified and the modified string
*
* Return values : none 
* 
* Change History
* -
* -
*
*****************************************************************************************/

void pta_make_newline_null(char *str) {

  unsigned int i;

  if (str) {
    for (i=0; i<strlen(str); i++) {
      if (str[i]=='\n' || str[i]=='\r') str[i]='\0';
    }
  }
}


/****************************************************************************************
* 
* Function:  ptaCfgStringIsOn
* 
* This is the function checks if the particular configuration value is on 
*
*
* Parameters -
* value (IN) - the string whose value is on 
*
* Return values : 
*    0 - if value is 0, off, OFF, Off, false, False or FALSE
*    1 - otherwise
* 
* Notes -
*   - Note that a random string "lskdja" will be considered on. 
*   - A non-existent string will be considered off. 
* 
* Change History
* -
* -
*
*****************************************************************************************/

int ptaCfgStringIsOn(const char *value) {

  int off = 0;

  if (value==0 ||
      strcmp(value, "0")==0 ||
      strcmp(value, "off")==0 ||
      strcmp(value, "Off")==0 ||
      strcmp(value, "OFF")==0 ||
      strcmp(value, "false")==0 ||
      strcmp(value, "False")==0 ||
      strcmp(value, "FALSE")==0 ) off = 1;
  else off = 0;

  return !off;
}


/****************************************************************************************
* 
* Function:  sscT_malloc
* 
* This is the function that should be used to allocate memory 
*
*
* Parameters -
* s (IN) - the length in bytes of memory to be allocated
*
* Return values : 
*    0 - if memory could not be allocated
*    otherwise - a pointer to the newly allocated memory
*  
* Change History
* -
* -
*
*****************************************************************************************/

POINTER sscT_malloc (unsigned int s) {
  /*return T_malloc(s);*/
  return ((POINTER)malloc (s == 0 ? 1 : s));
}




char *sscT_strdup(const char *s1) {

  int len;
  char *newStr = 0;

  len = strlen(s1) + 1;

  newStr = (char *) sscT_malloc(sizeof(char) * len);
 
  if (newStr) {
    strcpy(newStr, s1);
  }

  return newStr;
}



/****************************************************************************************
* 
* Function:  sscT_realloc
* 
* This is the function that should be used to reallocate memory 
*
*
* Parameters -
* s (IN) - the length in bytes of the reallocated memory
* p (IN) - pointer the existing memory 
*
* Return values : 
*    a pointer to the newly reallocated memory
*  
* Change History
* -
* -
*
*****************************************************************************************/

POINTER sscT_realloc (POINTER p, unsigned int s) {
  POINTER result;

  if (p == NULL)
    return (sscT_malloc (s));

  if ((result = (POINTER)realloc (p, s == 0 ? 1 : s)) == NULL)
    free (p);
  return (result);

  /*  return T_realloc(p, s);*/
}


/****************************************************************************************
* 
* Function:  sscT_free
* 
* This is the function that should be used to free memory allocated in sscT_malloc
* and sscT_realloc
*
*
* Parameters -
* p (IN) - pointer the existing memory 
*
* Return values : none
*  
* Change History
* -
* -
*
*****************************************************************************************/

void sscT_free (POINTER s) {
  if (s != NULL)
    free (s);
}



/****************************************************************************************
* 
* Function:  sscErrorString
* 
* This is the function that returns a string representation of the PTA-specific error
* codes
*
*
* Parameters -
* errorCode (IN) - integer error code
* errorString (OUT) - the error string corresponding to errorCode
*
* Return values : 0
*  
* Change History
* -
* -
*
*****************************************************************************************/


/* Convert an error into a string. */
int sscErrorString(char **errorString, int errorCode) {
  
  char *s = 0;
  static char buf[PTA_MAX_LINE_LENGTH];
  
  switch(errorCode) {

  case VS_ERR_NO_MEM:
    s = "Out of memory";
    break;
  case VS_ERR_BAD_PARAM:
    s = "A bad parameter was passed to an api function";
    break;
  case VS_ERR_MISSING_CONFIG_VAL:
    s = "A required value is missing from the configuration file";
    break;
  case VS_ERR_COOKIE_DOMAIN:
    s = "When specifiying a cookie-domain, cookie-name must also be specified";
    break;
  case VS_ERR_LOGIN_PAGE:
    s = "A problem occurred reading the login page";
    break;
  case VS_ERR_RANDOM:
    s = "A problem occurred with the random number generator.";
    break;
  case VS_ERR_RANDOM_CLOCK:
    s = "This computer does not have hardware suitable for seeding the random number generator";
    break;
  case VS_ERR_NO_URI:
    s = "Unable to determine the requested URI";
    break;
  case VS_ERR_ADMIN_UNSUPPORTED:
    s = "You have attempted to use an unsupported administrative feature";
    break;
  case VS_ERR_SHLIB:
    s = "Unable to load the plugin specified by shlib-name";
    break;
  case VS_ERR_VAL_INIT:
    s = "Unable to initialize revocation checking";
    break;
  case VS_ERR_ADMIN_HASC:
    s = "Problem reading admin-issuer-serial";
    break;
  case VS_ERR_NO_SAVE_CERTS:
    s = "no-save-certs cannot be set at the same time as add-env-vars or add-js-vars";
    break;
  case VS_ERR_OPTION_FILE:
    s = "Unable to read/parse the option-file";
    break;
  case VS_ERR_RANDOM_FILE:
    s = "Unable to read random-file";
    break;
  case VS_ERR_FILE_OPEN:
    s = "A file could not be opened.";
    break;
  case VS_ERR_FILE_READ:
    s = "A file could not be read.";
    break;
  case VS_ERR_LOG_FILE:
    s = "Unable to open log-file-name";
    break;
  case VS_ERR_REGISTRY:
    s = "Problem reading the registry";
    break;
  case VS_ERR_NO_ROOT:
    s = "A required root certificate is not loaded";
    break;
  case VS_ERR_MUTEX:
    s = "Problem acquiring a mutex";
    break;
  case VS_ERR_PLUGIN_INIT:
    s = "A user-specified plugin did not initialize properly";
    break;
  case VS_ERR_SERVER_NAME:
    s = "Could not read server-name parameter";
    break;
  case VS_ERR_INVALID_UPDATE_HOURS:
	s = "Invalid value for cert/crl refresh frequency parameter. Please select a non-zero value for update-hours";
	break;

  default:
    sprintf (buf, "Internal Error: Code 0x%04x, %d", errorCode, errorCode);
  }

  if (s==0) s = buf;
  *errorString = s;
        
  return 0;
}


/****************************************************************************************
* 
* Function:  vsPTAAuthorizePost
* 
* This is the function that is used to authorize the post
* It looks up the key in the hash table, calls the revocation callback setup in gCfg 
* to validate certificate statusLooks up the key in the hash table and sees if it 
* is expired. If not, sets the authorized bit. 
* Inherits the certItem, pkcs7 so that it can save them in the clientdata_t structure
* for that session.
*
* NOTE-this function currently frees pkcs7 and certItem->data if it cannot find a link
*      corresponding to the session.
*
* Parameters -
* htable (IN) - pointer to the hash table
* key (IN) - the ITEM that contains the key to search the hash table
* certItem (IN) - the certificate 
* pkcs7 (IN) - the original PKCS 7 that was posted 
* newClientData (OUT) - the pointer to the new clientdata
*
* Return values :
*  CS_VALID - the post is valid
*  CS_SSC_POST_EXPIRED - the session has expired
*  CS_SSC_POST_BAD - the key could not be found in the hash table
*  CS_SSC_POST_REVOKED - the cert was revoked
* 
* Change History
* -
* -
*
*****************************************************************************************/

int vsPTAAuthorizePost(hash_table_t *htable, ITEM key, ITEM *certItem,
                    char *pkcs7, client_data_t **newClientData) {

  /*
  link_t *link=0;
  */
  int status = 0;
  PTATIME tm = 0, statusExpires = 0;
  client_data_t *clientData=0;
  int certStatus = 0;
  char *userName = 0;

  VSVAL_UserCtx userCtx = {0};

  userCtx.logFn = gCfg.InfoLog;
  status = VSVAL_HashSearchGarbageCollect(gCfg.vsValSDK, &userCtx, htable, key.data, key.len, 0, (void**)&clientData);

  /* If we found it in the hash table, check it out. */
  if (clientData) {

    /* 
    clientData = link->data;
    */

    /* Save the cert item. */
    if (! gCfg.noSaveCerts) {

      /* If a bad version was already posted, free it. */
      sscT_free((unsigned char *) clientData->cert.data);

      clientData->cert = *certItem; 
    }

    /* Also save the signature. */
    /* If a bad version was already posted, free it. */
    sscT_free((unsigned char *) clientData->pkcs7);
    clientData->pkcs7 = pkcs7;

    /*vsCertISDigest(gCfg.vsValSDK, &internalCtx, clientData->iSDigest, certItem);*/
    VSVAL_CertMD5ISDigest(gCfg.vsValSDK, &userCtx, certItem->data, certItem->len,clientData->iSDigest);

    *newClientData = clientData;

    /* See if the authorization has expired. */
    pta_time(&tm);

    /* For signature posts, only check against the absolute timeout. */
    if (tm < clientData->absolute_timeout) {

      *newClientData = clientData;

      /* Bump the inactivity timeout. */
      clientData->inactive_timeout = tm + gCfg.inactiveTimeout;

      /* would be CS_VALID, but still need to check revocation... */
      if (gCfg.fnGetRevocationInfo(certItem, &certStatus,
                                   &statusExpires, &userName)==0) {
        status = certStatus;

        if (status == CS_VALID) {
          clientData->authorized = 1;
        }

        if (gCfg.noSaveCerts) { 
          /* We won't be able to use the cert to re-check revocation. */
          /* User must replay the cert. */
          clientData->absolute_timeout = vsMIN(clientData->absolute_timeout,
                                               clientData->revocation_timeout);
          clientData->revocation_timeout = clientData->absolute_timeout;
        }
        else {
          clientData->revocation_timeout = statusExpires;
        }
        
        /* Save the new subject dn. (Should already be one there.) */
        if (userName) {
         sscT_free((unsigned char *) clientData->userName);
          clientData->userName = sscT_strdup(userName ? userName : "client");
        }
      }
      else {
        status = CS_SSC_POST_REVOKED;
      }
      
    }
    else {
      status = CS_SSC_POST_EXPIRED;
    }

  }
  else {
    status = CS_SSC_POST_BAD;

    /* In this case we can't save these in the hash table. */
    /* Free them now. */
    sscT_free((unsigned char *) pkcs7);
    sscT_free((unsigned char *) (certItem->data));
  }


  return status;
}

/****************************************************************************************
* 
* Function:  vsPTAAuthorizeCookie
* 
* This is the function that is looks up the key in the hash table and sees if it is authorized.
*
* Parameters -
* htable (IN) - pointer to the hash table
* hascKey (IN) - the ascii key from the client cookie
* newClientData (OUT) - the pointer to the new clientdata
*
* Return values :
*  CS_VALID - the post is valid
*  CS_SSC_COOKIE_EXPIRED - the session has expired
*  CS_SSC_COOKIE_BAD - the key could not be found in the hash table
*  CS_SSC_COOKIE_REVOKED - the cert was revoked
*  CS_SSC_COOKIE_UNAUTH - the session related to the cookie is unauthenticated
* 
* Change History
* -
* -
*
*****************************************************************************************/

int vsPTAAuthorizeCookie(hash_table_t *htable, char *hascKey, 
                      client_data_t **newClientData) {

  ITEM key = {0,0};
  unsigned char keyBuf[MAX_DIGEST_LEN];
  /*
  link_t *link;
  */
  int status = 0, certStatus = 0;
  client_data_t *clientData=0;
  char *userName = 0;
  PTATIME tm = 0, statusExpires = 0;

  VSVAL_UserCtx ctx={0};

  ctx.logFn = gCfg.InfoLog;

  key.data = keyBuf;
  ptaHasc2ItemBuf(hascKey, &key);

  status = VSVAL_HashSearchGarbageCollect(gCfg.vsValSDK, &ctx, htable, key.data, key.len, 0, (void**)&clientData);

  /* If we found it in the hash table, check it out. */
  if (clientData) {

    /*clientData = link->data;*/
    *newClientData = clientData;

    /* See if it's authorized (not just in the table waiting for a post.) */
    if (clientData->authorized) {
      
      /* See if the authorization has expired. */
      pta_time(&tm);
      if ((tm < clientData->inactive_timeout) &&
          (tm < clientData->absolute_timeout)) {

        /* Bump the inactivity timeout. */
        clientData->inactive_timeout = tm + gCfg.inactiveTimeout;

        if (tm < clientData->revocation_timeout) {
          status = CS_VALID; /* if our revocation info hasn't expired, we're good. */
        }
        else {
          /* would be CS_VALID, but still need to check revocation... */
          if (gCfg.fnGetRevocationInfo(&clientData->cert, &certStatus, 
                                       &statusExpires, &userName)==0) {
            status = certStatus;

            clientData->revocation_timeout = statusExpires;
            /* No need to update clientData->userName since the cert hasn't changed. */
          }
          else {
            status = CS_SSC_COOKIE_REVOKED;
          }
          
          /* If the cert got revoked, it's no longer authorized. */
          if (certStatus != CS_VALID) {
            clientData->authorized = 0; 
          }

        }
      }
      else {
        status = CS_SSC_COOKIE_EXPIRED;
      }

    }
    else {
      status = CS_SSC_COOKIE_UNAUTH;
    }
  }
  else {
    /* Not found in hash table. */
    status = CS_SSC_COOKIE_BAD;
  }

  return status;
}




/****************************************************************************************
* 
* Function:  vsPTAGetCookieHeader
* 
* This is the function that creates the set-cookie header content.
* (The part after 'set-cookie:' )
*
* Parameters -
* cookieVal (IN) - the value of the cookie to be set
* deleteIt (IN) - whether you want to set or delete the cookie 
* cookie_str (OUT) - the preallocated buffer which will contain the cookie header 
*
* Return values : 0
* 
* Change History
* -
* -
*
*****************************************************************************************/
/* Creates the set-cookie header content. (The part after 'set-cookie:' ) */
/* Takes cookieVal in hasc, sprintfs into an already allocated cookie_str. */
int vsPTAGetCookieHeader(char *cookie_str, char *cookieVal, int deleteIt) {

  char buf[PTA_TINY_BUF_MAX];

  if (deleteIt) {
    /* some time in the past. */
    sprintf(buf, " expires=%s; ", "Wed, 03-Feb-1999 03:11:00 GMT");
  }
  else {
    /* Cookie will expire at the end of the user's session. */
    sprintf(buf, " ");
  }

  if (gCfg.noSSL) {
    /* For debugging with network snooping. */
    if (gCfg.cookieDomain) {
      sprintf(cookie_str, "%s=%s;%spath=/; domain=%s", 
              gCfg.cookieName, cookieVal, buf, gCfg.cookieDomain);
    }
    else {
      sprintf(cookie_str, "%s=%s;%spath=/",
              gCfg.cookieName, cookieVal, buf);
    }
  }
  else {
    if (gCfg.cookieDomain) {
      sprintf(cookie_str, "%s=%s;%spath=/; domain=%s; secure", 
              gCfg.cookieName, cookieVal, buf, gCfg.cookieDomain);
    }
    else {
      sprintf(cookie_str, "%s=%s;%spath=/; secure",
              gCfg.cookieName, cookieVal, buf);
    }
  }

  return 0;
}


/*** removeEOL
 ***
 *** DESCRIPTION:
 ***   Strips out \r and \n characters from an ITEM. Replaces
 ***   ITEM's buf with a new possibly smaller buf and frees
 ***   the old one.
 ***
 *** ARGUMENTS
 ***   ITEM *buf  - IN/OUT - pointer to buffer and length
 ***
 *** RETURNS
 ***   int - status code
 ***
 *** POSSIBLE ERROR CODES RETURNED
 ***   1 - out of memory
 ***
 *** REVISION HISTORY
 ***   Date          Author     Desc
 ***   ----          ------     ----
 ***   06/14/2000    Rick       Fixed bug - if no \r or \n characters
 ***     were found, new buf would be the same size as old buf and the
 ***     final strlen call to calculate the length would fail because
 ***     the new buffer wouldn't be null terminted. Instead set the
 ***     length to j.
 ***
 ***/
int removeEOL(ITEM * buf) 
{

	int status = 0;
	int i = 0;
	int j = 0;
	unsigned char * newBuf = NULL;

	do {

		newBuf = (unsigned char *) sscT_malloc (buf->len);
		if (newBuf == NULL) {
			status = 1;
			break;
		}

		memset(newBuf, 0, buf->len);

		for (i = 0; i < buf->len; i++) {
			if ((buf->data[i] != '\r') && (buf->data[i] != '\n')) {
				newBuf[j] = buf->data[i];
				j++;
			}
		}

		sscT_free(buf->data);
		/*free(buf->data);*/
		buf->data = newBuf;
		buf->len = j;

	} while (0);

	return status;
}



/* This is where we store data for a particular client. */

client_data_t *vsPTAInitClientData() {

  client_data_t *cd = 0;

  cd = (client_data_t *) sscT_malloc(sizeof(client_data_t));

  if (cd==0) return 0;
  
  memset(cd, 0, sizeof(client_data_t));

  return cd;
}

/*
void vsPTADestroyClientData(client_data_t *cd) {

  if (cd) {
   sscT_free((unsigned char *) (cd->url));
   sscT_free((unsigned char *) (cd->pkcs7));
   sscT_free((unsigned char *) (cd->userName));
   sscT_free(cd->cert.data);
  }
 sscT_free((unsigned char *) cd);
}
*/

/* returns the pointer from the struct, or a constant if it's not available. */
char *vsPTAGetUserName(client_data_t *clientData) {
  if (clientData && clientData->userName) {
    return clientData->userName;
  }
  else {
    return "client";
  }
}


/* Prints the JavaScript header for the login page. */
/* This includes the data the client must sign. */
int vsPTAGetJSForLogin(char *outBuf, char *hascToSign, char *hashOfToSign,
                    char *reason, char *digestAlg) {

  char *bufPtr;
  int status = 0;

  do {
    bufPtr = outBuf;
    bufPtr += sprintf(bufPtr, "<SCRIPT LANGUAGE=\"JavaScript\">\n");
    bufPtr += sprintf(bufPtr, "<!-- \n");
    bufPtr += sprintf(bufPtr, "toSign=\"%s\";\n", hascToSign);
    bufPtr += sprintf(bufPtr, "reasonCode=\"%s\";\n", reason);
    bufPtr += sprintf(bufPtr, "digestAlg=\"%s\";\n", digestAlg);
    bufPtr += sprintf(bufPtr, "// -->\n</script>\n");

  } while (0);

  return status;
}

/* Prints the JavaScript header for the error page. */
int vsPTAGetJSForError(char *outBuf, char *certStatus, char *url) {

  char *bufPtr;
  int status = 0;

  do {
    bufPtr = outBuf;
    bufPtr += sprintf(bufPtr, "<SCRIPT LANGUAGE=\"JavaScript\">\n");
    bufPtr += sprintf(bufPtr, "<!-- Begin SSC Error Definitions\n");
    bufPtr += sprintf(bufPtr, "certStatus=\"%s\";\n", certStatus);
    bufPtr += sprintf(bufPtr, "vsUrl=\"%s\";\n", url);
    bufPtr += sprintf(bufPtr, "// End SSC Error Definitions -->\n");
    bufPtr += sprintf(bufPtr, "</script>\n\n\n");

  } while (0);

  return status;
}

/* Prints an html page to redirect to a url. */
int vsPTAGetRedirectPage(char *outBuf, char *url) {

  char *bufPtr;
  int status = 0;

  do {
    bufPtr = outBuf;

    bufPtr += sprintf(bufPtr, "%s%s%s",
                      "<HTML><HEAD><TITLE>Moved Temporarily</TITLE></HEAD>\n"
                      "<BODY><META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; \n"
                      "URL=", url, "\">\r\n" );
    
    /* The standard says we should print the url here, but we don't. */
    /* Just a blank page to eliminate 'flicker'. */
    /* This works with all broswers we support.*/

  } while (0);

  return status;
}


/* convert a CS_ certificate status code into a string. */
char *vsPTACertStatusString(int certStatus) {

  char *status_string = 0;

  switch (certStatus) {

  case CS_SSC_COOKIE_EXPIRED:
    status_string = "COOKIE_EXPIRED";
    break;

  case CS_SSC_COOKIE_REVOCATION_EXPIRED:
    status_string = "COOKIE_REVOCATION_EXPIRED";
    break;

  case CS_SSC_COOKIE_UNAUTH:
    status_string = "COOKIE_UNAUTH";
    break;

  case CS_SSC_COOKIE_BAD:
    status_string = "COOKIE_BAD";
    break;

  case CS_SSC_POST_EXPIRED:
    status_string = "POST_EXPIRED";
    break;

  case CS_SSC_POST_BAD:
    status_string = "POST_BAD";
    break;

  case CS_SSC_LOGOUT:
    status_string = "LOGOUT";
    break;

  case CS_SSC_BAD_ADMIN:
    status_string = "BAD_ADMIN";
    break;

  case CS_VALID:
    status_string = "VALID";
    break;

  case CS_PENDING:
    status_string = "PENDING";
    break;

  case CS_EXPIRED:
    status_string = "EXPIRED";
    break;

  case CS_CRL_EXPIRED:
    status_string = "CRL_EXPIRED";
    break;

  case CS_REVOCATION_UNKNOWN:
    status_string = "REVOCATION_UNKNOWN";
    break;
    
  case CS_REVOKED:
    status_string = "REVOKED";
    break;
    
  case CS_SSC_POST_REVOKED:
    status_string = "POST_REVOKED";
    break;

  case CS_SSC_COOKIE_REVOKED:
    status_string = "COOKIE_REVOKED";
    break;

  case CS_SSC_PLUGIN_DENIED:
    status_string = "PLUGIN_DENIED";
    break;

  case 0:
    status_string = "NULL_CERTIFICATE_STATUS";
    break;    

  default:
    status_string = "CERTIFICATE_STATUS_UNKNOWN";
    break;
  }

  return status_string;
}




void vsPTAClearLoginVal(login_page_t *l) {
  
 sscT_free((unsigned char *) l->preVars.data);
 sscT_free((unsigned char *) l->postVars.data);

  l->preVars.len = 0;
  l->preVars.data = 0;
  l->postVars.len = 0;
  l->postVars.data = 0;
}

int vsPTAReadLoginVal(char *filename, login_page_t *l) {

  int status = 0;
  ITEM loginItem = {0};
  char *vars;

  VSVAL_UserCtx ctx = {0};

  do {

    /* Initialize to zero. */
    l->preVars = loginItem;
    l->postVars = loginItem;
    
	ctx.logFn = gCfg.InfoLog;
     if(status = VSVAL_FileRead(gCfg.vsValSDK, &ctx, filename, &(loginItem.data), &(loginItem.len))) {
      break;
    }

    /* Look for the tag. */
    if (loginItem.data) { vars = strstr((char *) loginItem.data, VS_PTA_LOGIN_TAG); }
    else { vars = 0; }

    /* If it's not there, prepend the variables. */
    if (vars==0) {
      l->postVars = loginItem; /* Adopt the alloced item. */
      loginItem.data = 0; /* So we don't free it. */
    }
    else {
      /* Split it up into the parts before and after the tag. */
      l->preVars.len = vars - ((char *) loginItem.data);
      loginItem.data[l->preVars.len] = 0;
      l->preVars.data = (unsigned char *) sscT_strdup((char *) loginItem.data);

      if (l->preVars.data==0) {
        status = VSVAL_ERR_ALLOC;
        break;
      }

      l->postVars.len = loginItem.len - VS_PTA_LOGIN_TAG_LEN - l->preVars.len;
      l->postVars.data = (unsigned char *) sscT_strdup(vars + VS_PTA_LOGIN_TAG_LEN);

      if (l->postVars.data==0) {
        status = VSVAL_ERR_ALLOC;
        break;
      }
    }

  } while(status);

  /*
  intCtx->logFn(intCtx->handle, "%d", l->preVars.len);
  intCtx->logFn(intCtx->handle, "%s",
  l->preVars.data ? (char *) l->preVars.data : "");
  intCtx->logFn(intCtx->handle, "%d", l->postVars.len);
  intCtx->logFn(intCtx->handle, "%s", 
  l->postVars.data ? (char *) l->postVars.data : "");
  */

  VSVAL_Free(gCfg.vsValSDK, loginItem.data);

  if (status) return VSVAL_ERR_LOGIN_PAGE;
  else return 0;
}




/* make rnrn -> n, rn->n, remove spaces.  Inefficiently does two passes.  */
void vsPTAEatWhite(char *s) {

  int len, i;
  char *into, *from;

  len = strlen(s);
  into = from = s;

  /* First, lets do rnrn -> rn, rn->n */
  for (i=0; i<len ; i++) {
    /* it looks like this will never dereference a bad pointer. */
    if (*from=='\r' && *(from+1)=='\n') {
      if ( *(from + 2)=='\r' && *(from + 3)=='\n') {
        from += 3;
      }
      else {
        from += 1;
      }
    }
    else {
      *into = *from;
      into++;
      from++;
    }
  }
  /* Null terminate so the next strlen is correct. */
  *into = '\0';

  len = strlen(s);
  into = from = s;

  /* Now we remove spaces. */
  for (i=0; i<len ; i++) {
    if (*from==' ') {
      from += 1;
    }
    else {
      *into = *from;
      into++;
      from++;
    }  
  }

  /* Null terminate. Needed here as well as above. */
  *into = '\0';

  /* IIS doesn't like headers that end with a \n. Make the last one a \0. */
  if (*(into-1)=='\n') { *(into-1) = '\0'; }

}


/* Works in place (sort of). Modifies the string in place, then returns a */
/* ptr to the new string. */
/* Will produce a string that deBase64Alloc will like. */
/* url-decodes, finds the correct name=value pair, removes ' ' , */
/* converts '\r\n\r\n' to '\r\n'. */
int vsPTAParsePost(char **news, char *s, char *content_type) {

  int status = 0;
  int len, i;
  char *fieldStr = 0;
  FILE *fp;
  int isFormEncoded;
  
  do {

    isFormEncoded = (content_type && 
                     (strcmp(content_type, "application/x-www-form-urlencoded")==0));
    if (isFormEncoded) {
      NET_UnEscape(s); /* Decode the form-encoding if necessary. */
    }

    /* Find dataSignature=MIIlsdkfjsdlfksd... */
    fieldStr = strstr(s, PTA_POST_SIG_FIELD);
    
    if (fieldStr==0) {
      if (isFormEncoded) {
        /* This is an error. */
        status = -1;
        break;
      }
      else {
        /* for now, assume a developer posted a b64 file directly. */
        s = s;
      }
    }
    else {
    
      /* Move past the tag. */
      s = fieldStr + PTA_POST_SIG_FIELD_LEN;
    }


    /* ignore any other form &name=value pairs. ('&' can't show up in base64.) */
    len = strlen(s);
    for (i=0; i<len; i++) {
      if(s[i]=='&') {
        if (i>0 && s[i-1]=='\n') { s[i] = '\0'; }
        else {
          /* There's enough room since the string was already null terminated.*/
          s[i] = '\n';
          s[i+1] = '\0'; 
        }
        break;
      }
    }

    vsPTAEatWhite(s);  /* make rnrn -> rn, eat space */

    /* Dump our posted data for debugging */
#ifdef WIN32
    fp = fopen("d:/tmp/b64.txt", "w");
#else
    fp = fopen("/tmp/b64.txt", "w");
#endif
    if (fp) {
      fwrite(s, 1, strlen(s), fp);
      fclose(fp);
    }
    /* end */

  } while (0);

  *news = s;

  return status;
}


int vsPTAIsAdmin(unsigned char *adminISDigest, unsigned char *certISDigest) {

  int isAdmin = 0;
/*
#ifdef DEBUGMSG
  char buf[VSVAL_TINY_BUF_MAX];
#endif
*/
  do {

/* 
#ifdef DEBUGMSG
    intCtx->logFn(intCtx->handle, "ADMIN cert");

    intCtx->logFn(intCtx->handle,
                    "ADMIN COMPARE %s", VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,buf, MD5_LEN, adminISDigest));
    intCtx->logFn(intCtx->handle, 
                    "ADMIN COMPARE %s", VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,buf, MD5_LEN, certISDigest));
#endif
*/

    if (memcmp(adminISDigest, certISDigest, MD5_LEN)==0) {
      isAdmin = 1;
    }
/*
#ifdef DEBUGMSG
    intCtx->logFn(intCtx->handle, "%s Admin", isAdmin ? "GOOD" : "BAD");
#endif
*/
  } while (0);

  return isAdmin;
}

int ptaLogBase2(int n) {

  int i = 0;

  while (n/2 != 0) {
    i++;
    n /= 2;
  }

  return i;
}

void vsNullLogInfoMessage(void * handle, char *fmt, ...) {
  return;
}

int ptaKeyEq(ITEM l, ITEM r) {
  return (l.data && r.data && (l.len==r.len) && (memcmp(l.data, r.data, l.len)==
0));
}



/* Uses SHA1 by default.  Can be flagged to use MD5. */
/* Puts the hash value into *outHash. outHash->data must already be allocated. */
/* Puts the hasc of the value that must be signed into hascToSign. Already alloced. */
int ptaGetValToSign(int useMD5, char *hascToSign, char *hashOfToSign, ITEM *outHash) {
  VSVAL_UserCtx ctx={0};
  int status = 0;
  int len;
  unsigned char toSign[VSVAL_HASH_SHA1_LEN + PTA_SIGNED_HEADER_LEN + VSVAL_BUF_MAX], *p;

  ctx.logFn = gCfg.InfoLog;

  do {

    /* Add the canned header. */
    memcpy(toSign, PTA_SIGNED_HEADER, PTA_SIGNED_HEADER_LEN);
    p = toSign + PTA_SIGNED_HEADER_LEN;
    len = PTA_SIGNED_HEADER_LEN;

    if (status = VSVAL_GenerateRandomBytes(gCfg.vsValSDK, &ctx, p, VSVAL_HASH_SHA1_LEN))
        break;

    len += VSVAL_HASH_SHA1_LEN;

    VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx, p, VSVAL_HASH_SHA1_LEN, hascToSign);

    /* Now tack on the fqDn server-name.*/ 
     p += VSVAL_HASH_SHA1_LEN;
     len += gCfg.serverNameLen;
     memcpy(p, gCfg.serverName, gCfg.serverNameLen);
#ifdef DEBUGMSG
    /*intCtx->logFn(intCtx->handle, "Mmmm... I'm digesting %d bytes!!!", len);*/
#endif
    if (useMD5) { 
      VSVAL_HashMessage(gCfg.vsValSDK, &ctx, toSign, len, VSVAL_HASH_ALG_MD5, outHash->data, &(outHash->len)); 
    }
    else { 
      VSVAL_HashMessage(gCfg.vsValSDK, &ctx,toSign, len, VSVAL_HASH_ALG_SHA1, outHash->data, &(outHash->len)); 
    }
    VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx, outHash->data, outHash->len, hashOfToSign);
  } while (0);
  return status;
}

int ptaHasc2ItemBuf(char *hasc, ITEM *item)
{
   VSVAL_UserCtx ctx={0};
   ctx.logFn = gCfg.InfoLog;
   VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx, hasc, item->data, &item->len);
   return 0;
}

int vsPTADestroyClientData(void* data){
  client_data_t *cd;
  cd = (client_data_t*)data;
  if (cd) {
    sscT_free((unsigned char *) (cd->url));
    sscT_free((unsigned char *) (cd->pkcs7));
    sscT_free((unsigned char *) (cd->userName));
    sscT_free(cd->cert.data);
  }
  sscT_free((unsigned char *) cd);
  return 0;
}


unsigned char *vsPTAGetISDigest(void *data){
  client_data_t *cd;
  cd = (client_data_t*)data;
  if (cd) {
    return cd->iSDigest;
  } else {
    return NULL;
  }
}


/* Case-insensitive strstr. Length limited: examines at most n bytes of s1. */
char *pta_strstr_ni(char *s1, char *s2, long ns1) {

  long i;
  char *last_s1, *this_s1;
  char *this_s2;
  char s1c, s2c;
  int all_match;

  if (s1==0 || s2==0) {
    return 0;
  }

  if (*s2==0) {
    return s1;
  }
  else if (*s1==0 || ns1==0L) {
    return 0;
  }

  last_s1 = s1 + ns1;

  for (i=0L; i<ns1; i++) {

    this_s1 = s1 + i;
    this_s2 = s2;
    all_match = 1;

    while ((s1c = *this_s1) && (s2c = *this_s2) && (this_s1 < last_s1)) {
      if (tolower(s1c)!=tolower(s2c)) {
        all_match = 0;
        break;
      }
      this_s1++;
      this_s2++;
    }

    /* The 'and' may have short-circuited, so make sure this is done. */
    s2c = *this_s2;

    if (all_match && ((s1c && !s2c) || (!s1c && !s2c))) {
      return s1 + i;
    }
  }

  return 0;
}

