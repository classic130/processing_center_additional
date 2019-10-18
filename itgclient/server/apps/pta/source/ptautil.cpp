#include <stdio.h>
#include <string.h>
#if defined(WIN32)
   #include <windows.h>
   #include <malloc.h>
#endif
#include "ssc_api.h"
#include "pta.h"

#define CFG_MAX_LINE_LENGTH 1024
#define MAX_FILE_LENGTH 20480

/* Get the next non-comment, non-blank line from the file. */
/* Not using one in val.dll since we can't pass a FILE pointer across dlls. */
/* Take a line of name="value" options, and parse it into name and value. */
/* Reads from line_buf into name, value_buf.  All buffers must already be allocated. */
int cfgGetNameValue(char *line_buf, char *name_buf, char *value_buf) 
{
  
  int status = 0;
  int quoted = 0;
  char *p, *q;

  do 
    {
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



char *cfgGetNextLine(char *lineBuf, int maxLen, FILE *fp) 
{
  char *rc = 0;
  int comment = 0;
  char tmpBuf[CFG_MAX_LINE_LENGTH];

  do 
    {    
      rc = fgets(lineBuf, maxLen, fp);      
      if (lineBuf[0]=='#' || (sscanf(lineBuf, "%s", tmpBuf) <= 0)) 
	comment = 1;
      else
	comment = 0;
    } while (rc && comment);

  return rc;
}


int InitializeFromConfigFile (const char *configFileName, void (*logFn)(char *fmt, ...), int *nCheckCrl)
{
    int libStatus=0;
    /* read the various configuration parameters from the specified
     * configuration file 
     */
    char cfgFileName[CFG_MAX_LINE_LENGTH]; /* the path to rsaverify.cfg */
    char cacheDir[CFG_MAX_LINE_LENGTH];    /* the cert/crl cache directory */
    char filePrefix[CFG_MAX_LINE_LENGTH];  /* the file prefix */
    char urlPrefix[CFG_MAX_LINE_LENGTH];   /* the prefix for all urls */
    int  checkChain;                       /* whether to check the chain */
    char *ptrLdapDefault, *ptrHttpProxy;
    char ldapDefault[CFG_MAX_LINE_LENGTH]; /* default ldap directory */
    char httpProxy[CFG_MAX_LINE_LENGTH];   /* the http proxy, if any */
    char ldapHttpProxy[CFG_MAX_LINE_LENGTH]; /* the http proxy for ldap */
    char ldapHttpCgi[CFG_MAX_LINE_LENGTH]; /* the cgi for ldap */
    char ocspUrl[CFG_MAX_LINE_LENGTH]; /* the OCSP Url */

    int status = 0;    
    FILE *fp = 0;

    char line_buf[CFG_MAX_LINE_LENGTH];
    char name_buf[CFG_MAX_LINE_LENGTH], value_buf[CFG_MAX_LINE_LENGTH];
    char *read_status;
    
    /* initialize the variables */
    strcpy(cfgFileName, "../config/rsaverify.cfg");
    strcpy(cacheDir, "../certcache/");
    strcpy(filePrefix, "../certcache/");
    urlPrefix[0] = '\0';
    checkChain = 0;
    ldapDefault[0] = '\0';
    httpProxy[0] = '\0';
    ldapHttpProxy[0] = '\0';
    ldapHttpCgi[0] = '\0';
    ocspUrl[0] = '\0';
	*nCheckCrl = 0;

    
    do {      
		if (!(fp = fopen(configFileName, "r"))) 
		break; 
		/* the default values will kick in...*/
	
		/* Read the config file */
		do {
	  	
			if (read_status = cfgGetNextLine(line_buf, CFG_MAX_LINE_LENGTH, fp)) 
			{	  
				if (cfgGetNameValue(line_buf, name_buf, value_buf)!=0) 
				{
					status = -1;
					break;
				}
			else
			{
				if (strcmp(name_buf, "cfg-filename")==0)
					strcpy (cfgFileName, value_buf);
				else if (strcmp(name_buf, "cache-dir") == 0)
					strcpy (cacheDir,  value_buf);
				else if (strcmp(name_buf, "file-prefix")==0)
					strcpy(filePrefix, value_buf);
				else if (strcmp(name_buf, "url-prefix")==0)
					strcpy(urlPrefix, value_buf);
				else if (strcmp(name_buf, "no-check-chain")==0)
				{
					if ((strcmp(value_buf,"1")==0) || (strcmp(value_buf,"yes")==0) || (strcmp(value_buf, "on") == 0))
						checkChain=0;
					else
						checkChain=1;
				}
				else if (strcmp(name_buf, "default-ldap")==0)
					strcpy(ldapDefault, value_buf);
				else if (strcmp(name_buf, "http-proxy")==0)
					strcpy(httpProxy, value_buf);
				else if (strcmp(name_buf, "ldap-http-proxy")==0)
					strcpy(filePrefix, ldapHttpProxy);
				else if (strcmp(name_buf, "ldap-http-cgi")==0)
					strcpy(ldapHttpCgi, value_buf);		      
                else if (strcmp(name_buf, "ocsp-url") == 0)
                    strcpy(ocspUrl, value_buf);
			    else if (strcmp(name_buf, "no-crl-check")==0)
				{
					if ((strcmp(value_buf, "1")==0) || (strcmp(value_buf,"yes")==0) || (strcmp(value_buf, "on") == 0))
						*nCheckCrl = 0;
					else
						*nCheckCrl = 1;
				}			
			}
		}  	
	  } while (read_status != 0 && status==0);      

		if (fp) fclose(fp);

		/* currently the PTA plugin does not respect ldapHttpProxy and ldapHttpCgi
		 * so pass in NULL. Even if the parameters are not defined set them to NULL
		 * because for some reason PTA plugin crashes otherwise
		 */
		if (strcmp(ldapDefault, "")==0)
		  ptrLdapDefault = 0;
		else
		  ptrLdapDefault = ldapDefault;

		if (strcmp(httpProxy, "")==0)
		  ptrHttpProxy = 0;
		else
		  ptrHttpProxy = httpProxy;

		
		libStatus = vsPKIInit(SSC_CURRENT_VERSION, cfgFileName, cacheDir, filePrefix, urlPrefix, checkChain, 
						   ptrHttpProxy, ocspUrl, logFn, ptrLdapDefault, 0, 0);   		


    } while (0);
    
        
   return libStatus;
}


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
      if (str[i]=='\n' || str[i]=='\r') 
		str[i]='\0';
    }
  }
}



/* Convert an error into a string. */
int comvsscErrorString(char *errorString, DWORD errorCode) {
  
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
  case VSVERIFY_INVALID_CONFIG:
	s="The options specified were invalid";
	break;
  case VSVERIFY_LIBRARY_ERROR:
	s="The PTA libraries could not be loaded. \
	   Please make sure that they are in the path and try again";
	break;
  case VSVERIFY_INITIALIZE_FAILED:
	s="The PTA library could not be initialized. Please make sure that \
	   the configuration file is correct and the roots mentioned in the \
	   rsaverify.cfg are present in the correct location";
	break;
  case VSVERIFY_ERROR_REGISTRY:
	s="There was an error reading the parameters from the registry. \
	   Please run the loadreg.exe program before you start the service.";
	break;
  case VSVERIFY_ERROR_B64DECODE:
	s="There was an error during Base 64 decode operation.";
	break;
  default:
	if (errorCode < 0x00010000)
		sprintf (buf, "Internal Error: Code 0x%04x, %d", errorCode, errorCode);
	else
		sprintf (buf, "Internal Error: Code 0x%08x, %d", errorCode, errorCode);
  }

  if (s==0) s = buf;
  //*errorString = s;
  strcpy(errorString, s);
        
  return 0;
}
