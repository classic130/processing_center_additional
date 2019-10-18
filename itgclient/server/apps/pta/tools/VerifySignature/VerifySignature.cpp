#include <stdio.h>
#include <string.h>

#if defined(WIN32)
   #include <windows.h>
   #include <malloc.h>
#elif defined(SOLARIS) || defined(AIX)
   #include <ctype.h>
   #include <dlfcn.h>
#elif defined(HPUX)
   #include <ctype.h>
   #include <dl.h>
#else
   #error "your platform does not support DLL management"
#endif
#define CFG_MAX_LINE_LENGTH 1024
#define MAX_FILE_LENGTH 20480
#define TRUE 1
#define FALSE 0

#define USAGE "The usage for the Signature Verification program is - \n \
\n \
Usage : VerifySignature.exe -config <option-file> [-signature-file <B64-Signature-file>] [-message-file <message-file>] \
 [-signature <B64-signature>] [-message <message>] [-quiet 1]\n \
\n \
Note the current directory should be same containing the executable.\n \
\n \
where :\n \
-config: the file containing PTA options. This is a mandatory option.\n \
    <option-file> - the file containing PTA options\n \
\n \
-signature-file: Use this options if the signature is in a file \n \
    <B64-Signature-file>: the name of the file containing the B64 encoded Signature,\n \
\n \
-signature: Use this option if you are giving the B64 encoded Signature as a parameter\n \
    <B64-signature>: the B64 encoded signature\n \
\n \
-message-file: specify this option if you have the message in a file\n \
    <message-file>: the name of the file containing the message\n \
\n \
-message: specify this option if you are passing the message as a parameter\n \
    <message>: the message that was signed\n \
\n \
-quiet 1: specify this if do not want status messages to be printed. \n"

	
#if defined(WIN32)
   #define MAXPATHLEN          _MAX_PATH
#else
   #define MAXPATHLEN          1024
#endif 
#define VSVERIFY_ERR_BASE 8800
#define VSVERIFY_INVALID_CONFIG				(VSVERIFY_ERR_BASE + 1)
#define VSVERIFY_LIBRARY_ERROR				(VSVERIFY_ERR_BASE + 2)
#define VSVERIFY_INITIALIZE_FAILED			(VSVERIFY_ERR_BASE + 3)
#define VSVERIFY_ERROR_READING_MESSAGE		(VSVERIFY_ERR_BASE + 4)
#define VSVERIFY_ERROR_READING_SIGNATURE	(VSVERIFY_ERR_BASE + 5)

  /* Error Codes */
#define VS_SSC_ERR_BASE 7700
#define VS_SSC_ERR_BAD_VERSION         (VS_SSC_ERR_BASE +  1)
#define VS_SSC_ERR_BAD_PARAM           (VS_SSC_ERR_BASE +  2)
#define VS_SSC_ERR_REVOCATION_WARN     (VS_SSC_ERR_BASE +  3)
#define VS_SSC_ERR_BAD_SIG             (VS_SSC_ERR_BASE +  4)
#define VS_SSC_ERR_BAD_HASH            (VS_SSC_ERR_BASE +  5)
#define VS_SSC_ERR_BAD_INIT            (VS_SSC_ERR_BASE +  6)
#define VS_SSC_ERR_NO_CHAIN            (VS_SSC_ERR_BASE +  7)
#define VS_SSC_ERR_BER_ENCODING        (VS_SSC_ERR_BASE +  8)
#define VS_SSC_ERR_OCSP_SERVER_CONFIG  (VS_SSC_ERR_BASE +  9)
#define VS_SSC_ERR_READ_CONFIG_FILE    (VS_SSC_ERR_BASE + 10)
#define VS_SSC_ERR_ALLOC               (VS_SSC_ERR_BASE + 11)

  /* Certification status codes. */
#define CS_VALID                                  1
#define CS_PENDING                                2
#define CS_EXPIRED                                3
#define CS_CRL_EXPIRED                            4
#define CS_REVOCATION_UNKNOWN                     5
#define CS_REVOKED                                6

int (*_fnInit)(int,char*, char*,char*,char*,int,char*,char*,void(*)(char*,...),char*,char*,char*) ;
int (*_fnVerify)(unsigned char*, int, unsigned char*,  int,
                   unsigned char *, int *, int *,
                   unsigned char **, int *, int *) ;
int (*_fnUnBase64)(unsigned char **, int *, char *);
void (*_fnFree)(void *);
int _fInitialized=0;
void *_dlHandle ;
int gbQuiet = 0;


/* function declarations */
char *cfgGetNextLine(char *,int,FILE *);
int cfgGetNameValue(char *,char *,char *);
void InitDynamicLibrary();
int InitializeFromConfigFile (const char *,int*);
int vsVerifySignature (char*,char*,char*,char*,int);

int 
main(int argc, char *argv[])
{
	char cfgFileName[MAXPATHLEN];
	char signatureFileName[MAXPATHLEN];
	char messageFileName[MAXPATHLEN];
	char *ptrMessage=NULL;
	char *ptrSignature=NULL;
	int isSignature=0;
	int isMessage=0;
	int isConfig=0;
	int nIndx, nStatus;
	int bValidArg=1;
	int nCheckCrl=0;

	signatureFileName[0] = '\0';
	messageFileName[0] = '\0';

    if (argc < 7) 
    {
      if (gbQuiet == 0) {	
          printf ("\n Insufficient parameters ");
          printf("%s", USAGE);  
      }
	  return VSVERIFY_INVALID_CONFIG;
    }

    for ( nIndx = 1; nIndx < argc; nIndx+=2) {
      if ( strcmp(argv[nIndx], "-config") == 0) {
	     sprintf(cfgFileName, "%s", argv[nIndx+1]);
		 isConfig =1;
	     continue;
	  }
      
      if ( strcmp(argv[nIndx], "-signature") == 0) {
	 	ptrSignature = argv[nIndx+1];
		 isSignature = 1;
	     continue;
	  }

     if ( strcmp(argv[nIndx], "-message") == 0) {
		ptrMessage = argv[nIndx+1];
		 isMessage = 1;
	     continue;
	  }
      
      if ( strcmp(argv[nIndx], "-signature-file") == 0) {
	     sprintf(signatureFileName, "%s", argv[nIndx+1]);
		 isSignature = 1;
	     continue;
	  }
	if ( strcmp(argv[nIndx], "-quiet") == 0) {
	     gbQuiet = 1;
             continue;
	}
      if ( strcmp(argv[nIndx], "-message-file") == 0) {
	     sprintf(messageFileName, "%s", argv[nIndx+1]);
		 isMessage = 1;
	     continue;
	  } else {
	     bValidArg=0;
	     break;
	  }
    }

	do {

		if (bValidArg==FALSE || isConfig == 0 || isMessage == 0 || isSignature == 0)
		{
		    if (gbQuiet == 0) {
			printf("%s", USAGE);
 	  	    }
			nStatus =  VSVERIFY_INVALID_CONFIG;
			break;
		}

		InitDynamicLibrary() ; 
		if (_fInitialized == 0) {
			nStatus =  VSVERIFY_LIBRARY_ERROR;
			break;
		}
		

		nStatus = InitializeFromConfigFile ( cfgFileName, &nCheckCrl );
		if (nStatus != 0)
			 break;

		nStatus = vsVerifySignature ( ptrSignature, signatureFileName, ptrMessage, messageFileName, nCheckCrl );
		if (nStatus != 0)
			break;

	} while (0);

	if (gbQuiet == 0) {	
	printf ("\nSignature Verification Status : %d", nStatus);
	switch (nStatus) {
	   case 0:		
		   printf ("\nThe Signature was verified successfully!!!");
		   break;
	   case VSVERIFY_INVALID_CONFIG:
		   printf ("\nThe options specified were invalid");
		   break;
	   case VSVERIFY_LIBRARY_ERROR:
		   printf ("\nThe PTA libraries could not be loaded. Please make sure that they are in the path and try again");
		   break;
	   case VSVERIFY_INITIALIZE_FAILED:
		   printf ("\nThe PTA library could not be initialized. \n \
			   Please make sure that the configuration file is correct and the roots mentioned in the \n \
			   rsaverify.cfg are present in the correct location");
		   break;
	   case VSVERIFY_ERROR_READING_MESSAGE:
		   printf("\nThe Message file could not be read correctly. Please check the file name and retry.");
		   break;
	   case VSVERIFY_ERROR_READING_SIGNATURE:
		   printf ("\nThe Signature file could not be read correctly. Please check the file name and retry.");
		   break;
	   case VS_SSC_ERR_BAD_SIG:
		   printf ("\nThe signature is invalid !!!");
		   break;
	   case VS_SSC_ERR_BAD_PARAM:
		   printf ("\nThe parameters specified were in error!");
		   break;
	   default:
		   printf("\nGeneric VerifySignature error. Please consult the error-codes.");
		   break;

	}
	printf("\n\n");
        }
	return nStatus;
}

int 
vsVerifySignature ( char* pcharSignature,
						   char* pcharSignatureFileName, 
						   char* pcharMessage,
						   char* pcharMessageFileName,
						   int pCheckCrl)
{
	unsigned char pbHash[20] ;
	int nHashLen ;
	int hashAlg ;
	int pkcs7Len, mesgLen;
	int nCertStatus = 5;
	int verifyStatus=0;
	char *ptrSignature=0, signatureBuf[MAX_FILE_LENGTH];
	char *ptrMessage=0, messageBuf[MAX_FILE_LENGTH];
	unsigned char *pkcs7;
	unsigned char *cert=0;
	int certLen;
	FILE *fp;

	do {
		/* if you need to read the PKCS7 Signature from file do so */
		if (pcharSignature==NULL) {
			/* read the signature into ptrSignature */
			do 
			{
				if (!(fp = fopen(pcharSignatureFileName, "r")))
					break; 
				if ( fgets ( signatureBuf, MAX_FILE_LENGTH, fp) == NULL)
				{
					if (fp) fclose(fp);
					break;
				}
				if ( signatureBuf[strlen(signatureBuf)-1] == '\n' )
					signatureBuf[strlen(signatureBuf)-1] = '\0';
				if (fp) fclose (fp);
				ptrSignature = signatureBuf;
			} while (0);

		} else {
			ptrSignature = pcharSignature;
		}
		if (ptrSignature == 0) {
			verifyStatus = VSVERIFY_ERROR_READING_SIGNATURE;
			break;
		}

		/* if you need to read the message from the file do so */
		if (pcharMessage==NULL) {
			/* read the message into ptrMessage */
			do 
			{
				if (!(fp = fopen(pcharMessageFileName, "r")))
					break; 
				if ( fgets ( messageBuf, MAX_FILE_LENGTH, fp) == NULL)
				{
					if (fp) fclose(fp);
					break;
				}
				if ( messageBuf[strlen(messageBuf)-1] == '\n' )
					messageBuf[strlen(messageBuf)-1] = '\0';
				if (fp) fclose (fp);
				ptrMessage = messageBuf;
			} while (0);

		} else {
			ptrMessage = pcharMessage;
		}
		if (ptrMessage == 0) {
			verifyStatus = VSVERIFY_ERROR_READING_MESSAGE;
			break;
		}

		mesgLen = strlen (ptrMessage);

		/* UnBase64 PKCS7 Signature */
		verifyStatus = _fnUnBase64 (&pkcs7, &pkcs7Len, ptrSignature);
		if ( verifyStatus != 0 ) {
			break;
		}

		/* Verify the signature */		
		if (pCheckCrl == 0)
			verifyStatus = _fnVerify(pkcs7, pkcs7Len,
			    (unsigned char *)ptrMessage, mesgLen, 
			    pbHash, &nHashLen, &hashAlg,
			    &cert, &certLen, 
			    NULL);
		else
			verifyStatus = _fnVerify(pkcs7, pkcs7Len,
			    (unsigned char *)ptrMessage, mesgLen,  
			    pbHash, &nHashLen, &hashAlg,
			    &cert, &certLen, 
			    (int*)&nCertStatus);				

		/* free the cert */
		if ( cert != NULL) {
			_fnFree (cert);
		}
		/* free the PKCS7 Message */
		if (pkcs7 != NULL) {
			_fnFree (pkcs7);
		}
	} while (0);
	return verifyStatus;
}

int InitializeFromConfigFile (const char *configFileName, int* nCheckCrl)
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

    
    do 
      {
	if (!(fp = fopen(configFileName, "r"))) 
	  break; 
	/* the default values will kick in...*/
	
	/* Read the config file */
	do 
	  {	
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
      } while (0);
    
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
   /* changed Siddharth 072200 */
   
   libStatus = _fnInit(1, cfgFileName, cacheDir, filePrefix, urlPrefix, checkChain, 
                       ptrHttpProxy, ocspUrl, 0, ptrLdapDefault, 0, 0);   
    
   return libStatus;
}



void InitDynamicLibrary()
{
#if defined(WIN32)
  _fInitialized = 0 ;
  _dlHandle = LoadLibrary("libvsssc.dll");
  _fnInit = (int (*)(int,char*,char*,char*,char*,int,char*,char*,void(*)(char*, ...),char*,char*,char*))GetProcAddress((HINSTANCE)_dlHandle, "vsPKIInit") ;
  _fnVerify = (int (*)(unsigned char*,int,unsigned char*,int, unsigned char*,int*, int *, unsigned char**,int*,int*))
				GetProcAddress((HINSTANCE)_dlHandle, "vsPKIVerifyPKCS7") ;
  _fnUnBase64 = (int(*)(unsigned char **, int *, char *))GetProcAddress((HINSTANCE)_dlHandle, "vsPKIUnBase64Alloc") ;
  _fnFree = (void (*)(void*))GetProcAddress((HINSTANCE)_dlHandle, "vsPKIFree");
  if( (_fnInit == NULL) || (_fnVerify == NULL) || (_fnUnBase64 == NULL) || (_fnFree == NULL) )  return ;
  _fInitialized = 1 ;

#elif defined (SOLARIS) || defined(AIX)

  /* Don't do RTLD_LAZY, so we find missing symbols right away. */
  _dlHandle = dlopen("libvsssc.so", RTLD_NOW);
  if( _dlHandle == NULL )  return ;
  _fnInit  = (int (*)(int,char*,char*,char*,char*,int,char*,char*,void(*)(char*, ...),char*,char*,char*))dlsym(_dlHandle, "vsPKIInit");
  _fnVerify = (int (*)(unsigned char*,int,unsigned char*,int, unsigned char*,int*, int *, unsigned char**,int*,int*))dlsym(_dlHandle, "vsPKIVerifyPKCS7");
  _fnUnBase64 = (int(*)(unsigned char **, int *, char *))dlsym(_dlHandle, "vsPKIUnBase64Alloc") ;
  _fnFree = (void (*)(void*))dlsym(_dlHandle, "vsPKIFree");

  if( (_fnInit == NULL) || (_fnVerify == NULL) || (_fnUnBase64 == NULL) || (_fnFree == NULL) )  
	return;
  _fInitialized = 1;

#elif defined(HPUX)

  void* funcAddr = NULL;

  _dlHandle = shl_load("libvsssc.sl", BIND_IMMEDIATE|DYNAMIC_PATH, 0);
  if (_dlHandle == NULL) 
     return;

  shl_findsym((shl_t*)&_dlHandle, "vsPKIInit", TYPE_UNDEFINED, &funcAddr);
  _fnInit  = (int (*)(int,char*,char*,char*,char*,int,char*,char*,void(*)(char*, ...),char*,char*,char*))funcAddr;
  shl_findsym((shl_t*)&_dlHandle, "vsPKIVerifyPKCS7", TYPE_UNDEFINED, &funcAddr);
  _fnVerify = (int (*)(unsigned char*,int,unsigned char*,int, unsigned char*,int*, int *, unsigned char**,int*,int*))funcAddr;
  shl_findsym((shl_t*)&_dlHandle, "vsPKIUnBase64Alloc", TYPE_UNDEFINED, &funcAddr);
  _fnUnBase64 = (int(*)(unsigned char **, int *, char *))funcAddr;
  shl_findsym((shl_t*)&_dlHandle, "vsPKIFree", TYPE_UNDEFINED, &funcAddr);
  _fnFree = (void (*)(void*))funcAddr;

  if (_fnInit == NULL || _fnVerify == NULL || (_fnUnBase64 == NULL) || (_fnFree == NULL))  
     return;

  _fInitialized = 1 ;

#else

   #error "unsupported platform"

#endif
}

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

/* Get the next non-comment, non-blank line from the file. */
/* Not using one in val.dll since we can't pass a FILE pointer across dlls. */
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

