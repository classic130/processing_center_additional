/*--------------------------------------------------------------------\
| VeriSign SSC Client Authorization API                               |
| File: scc_api.c                                                     |
\--------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>

#define EXPORT 1
#include "vsvalsdk.h"
#include "ssc_api.h"

#ifdef SOLARIS
#pragma ident "@(#)VeriSign ptaserver signature verification API 1.0.0.3 2001/09/22"     /* OnSite 4.6 */
#else
#ifdef HPUX
#pragma VERSIONID "@(#)VeriSign ptaserver signature verification API 1.0.0.3 2001/09/22"     /* OnSite 4.6 */
#endif
#endif

/* definition of SSC log info format */
typedef void (*VS_SCC_InfoLogFn) (char *fmt, ...);
static VS_SCC_InfoLogFn globalLogFn;

void vsPKILog (void* handle, char *fmt, ...){
  char infoBuf[CVM_LARGE_BUF_MAX];
  va_list ap;
  
  if (!globalLogFn) 
	 return;

  va_start(ap, fmt);
  
  (void) vsprintf(infoBuf, fmt, ap);
  va_end(ap);
  globalLogFn(infoBuf);
}

/* Global variable vs is hread safe here because CVM api is thread safe. */
Dll VSVAL_SDK* vs;

/* Translate error code from vsvalsdk to ssc */
/* Note: this function only map the errors known to SSC. If not, VS_SSC_ERR_MAX is returned.*/
int ErrorCodeCVM2SSC(int status) {
      /* translate the error code */
      switch (status) {
      case VSVAL_ERR_BAD_SIG:
        status = VS_SSC_ERR_BAD_SIG;
        break;
      case VSVAL_ERR_BAD_PARAM:
        status = VS_SSC_ERR_BAD_PARAM;
        break;
      case VSVAL_ERR_BAD_HASH:
        status = VS_SSC_ERR_BAD_HASH;
        break;
      case VSVAL_ERR_BER_ENCODING:
        status = VS_SSC_ERR_BER_ENCODING;
        break;
      case VSVAL_ERR_OCSP_SERVER_CONFIG:
        status = VS_SSC_ERR_OCSP_SERVER_CONFIG;
        break;
      case VSVAL_ERR_READ_CONFIG_FILE:
        status = VS_SSC_ERR_READ_CONFIG_FILE;
        break;
      case VSVAL_ERR_ALLOC:
        status = VS_SSC_ERR_ALLOC;
        break;
      default:
		status = VS_SSC_ERR_MAX;
        break;
      }
      /* and break out */
	return status;
}

/* Version must be 1 or greater for ocsp version. */
Dll int vsPKIInit(int version, char *cfgFileName,
                  char *cacheDir, char *filePrefix, char *urlPrefix,
                  int checkChain, char *httpProxy, char *ocspUrl, 
                  void (*logFn)(char *fmt, ...), char *ldapDefault,
                  char *ldapHttpProxy, char *ldapHttpCgi) {

  int status = 0;
  VSVAL_UserCtx ctx = {0};

  if (version < SSC_BACK_COMPATIBLE_VERSION || version > SSC_CURRENT_VERSION) {
    return VS_SSC_ERR_BAD_VERSION;
  }
 
  if (cfgFileName==0) {
    return VS_SSC_ERR_BAD_PARAM;
  }

  /* get logging function, if 0, logfunction will not be set*/
  globalLogFn = logFn;
  
  ctx.logFn = vsPKILog;

  do {
	  /* initialize CVM SDK */
	  if(status = VSVAL_Init(&vs,&ctx,VAL_SDK_CURRENT_VERSION)) {
		  break;
	  }

	  /* setup options if they are not null */
	  if(cfgFileName != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"cfg_filename", cfgFileName)) {
			  break;
		  }
	  }
	  if(cacheDir != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"cache-dir", cacheDir)) {
			  break;
		  }
	  }
	  if(filePrefix != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"file-prefix", filePrefix)) {
			  break;
		  }
	  }
	  if(urlPrefix != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"url-prefix",urlPrefix)) {
			  break;
		  }
	  }
	  if(httpProxy != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"http-proxy", httpProxy)) {
			  break;
		  }
	  }
	  if(ocspUrl != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"ocsp-url", ocspUrl)) {
			  break;
		  }
	  }
	  if(ldapDefault != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"default-ldap",ldapDefault)) {
			  break;
		  }
	  }
	  if(ldapHttpProxy != 0) {
		  if(status = VSVAL_SetOpt(vs,&ctx,"ldap-http-proxy", ldapHttpProxy)) {
			  break;
		  }
	  }
	  if(checkChain ==0) {
		  status = VSVAL_SetOpt(vs,&ctx,"no-check-chain", "on");
	  } else {
		  status = VSVAL_SetOpt(vs,&ctx,"no-check-chain", "off");
	  }
	  if(status != 0) break;
      if (status = VSVAL_ReadConfigFile(vs, &ctx, 0)) {
          break;
	  }
  } while (0);

  /* if error, convert code to SSC error */
  if (status && (status = (ErrorCodeCVM2SSC(status)) == VS_SSC_ERR_MAX)) {
    status = VS_SSC_ERR_BAD_INIT;
  }
  return status;
}


/* Cleanup. */
Dll int vsPKIFinal() {

	VSVAL_Final(vs);
    return 0;
}


/* Don't free userName. */
Dll int vsPKIGetRevocationStatus(unsigned char *cert, int certLen,
                                 int *certStatus, char **userName) {
  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;

  status = VSVAL_GetRevocationStatus(vs, &ctx, cert, certLen, certStatus, userName);

  /* if error, convert code to SSC error */
  if (status && (status =ErrorCodeCVM2SSC(status)) == VS_SSC_ERR_MAX) {
    status = VS_SSC_ERR_REVOCATION_WARN;
  }
  return status;
}

/* outLen will be 16 or 20.  The data will be in hash, */
/* which must already be allocated. cert will get the signer cert (must be freed). */
Dll int vsPKIParsePKCS7(unsigned char *pkcs7, int pkcs7Len, 
                        unsigned char *hash, int *hashLen, int *outAlgorithm, 
                        unsigned char **cert, int *certLen, int *certStatus) {

  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;

  status = VSVAL_ParseDetachedPKCS7(vs, &ctx, pkcs7, pkcs7Len,hash,hashLen, outAlgorithm,cert,certLen,certStatus);

  /* if error, convert code to SSC error */
  if(status) {
	  status = ErrorCodeCVM2SSC(status);
  }
  return status;
}

Dll int vsPKICompareMsgHash(unsigned char *msg, int msgLen, 
                            int outAlgorithm, unsigned char *hash, int hashLen) {

  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;

  status = VSVAL_CompareMsgHash(vs,&ctx, msg,msgLen,outAlgorithm,hash,hashLen);

  /* if error, convert code to SSC error */
  if(status) {
	  status = ErrorCodeCVM2SSC(status);
  }
  return status;
}

/* As above, but also verifies that msg is the message that was signed. */
Dll int vsPKIVerifyPKCS7(unsigned char *pkcs7, int pkcs7Len, 
                         unsigned char *msg, int msgLen, 
                         unsigned char *hash, int *hashLen, int *outAlgorithm, 
                         unsigned char **cert, int *certLen, int *certStatus) {

  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;
 
  status = VSVAL_ParseDetachedPKCS7(vs, &ctx, pkcs7, pkcs7Len,hash,hashLen, outAlgorithm,cert,certLen,certStatus);
  if(status == 0) {
	  if(status = VSVAL_CompareMsgHash(vs,&ctx, msg,msgLen,*outAlgorithm,hash,*hashLen)) {
		  status = VS_SSC_ERR_BAD_SIG;
	  }
  }
  /* if error, convert code to SSC error */
  if(status) {
	  status = ErrorCodeCVM2SSC(status);
  }
  return status;
}

/* to, from Base64.  Does not handle ---BEGIN CERT---, CRL, etc... */
/* Must free (null-terminated) *b64String when done. */
Dll int vsPKIBase64Alloc(char **b64String, unsigned char *data, int len) {
  
  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;

  status = VSVAL_Base64Alloc(vs,&ctx,b64String,data,len);

  /* if error, convert code to SSC error */
  if(status) {
	  status = ErrorCodeCVM2SSC(status);
  }
  return status;
}

/* Must free *data when done. */
Dll int vsPKIUnBase64Alloc(unsigned char **data, int *len, char *b64String) {
  
  int status = 0;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = vsPKILog;

  status = VSVAL_DeBase64Alloc(vs,&ctx,data,len,b64String);

  /* if error, convert code to SSC error */
  if(status) {
	  status = ErrorCodeCVM2SSC(status);
  }
  return status;
}

/* parse a certificate to readable fields */
/* The function will allocated  a pointer to a new VS_SSC_CertFields that contains all*/
/* readable cert fields. call vsPKIFreeCertFields to free the pointer when you are done with it*/
/* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */

Dll int vsPKIParseCert(VS_SSC_CertFields **certFields, unsigned char *cert, int certLen) {

	int status;
    VSVAL_UserCtx ctx = {0};
    ctx.logFn = vsPKILog;

	status = VSVAL_ParseCert(vs,&ctx,(VSVAL_CertFields**) certFields, cert,certLen);
		/* Special Note: we used cast to convert between VSVAL_CertFields and VS_SSC_CertFields */
		/* because they are identical. Attention is needed when CVM updates*/

	/* if error, convert code to SSC error */
    if(status) {
	  status = ErrorCodeCVM2SSC(status);
	}
    return status;
}

/* parse a Base64 encoded certificate to readable fields */
/* The function will allocated  a pointer to a new VS_SSC_CertFields that contains all*/
/* readable cert fields. call vsPKIFreeCertFields to free the pointer when you are done with it*/
/* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */
Dll int vsPKIParseB64Cert(VS_SSC_CertFields **certFields,  char *b64cert) {
	
	int status;
    VSVAL_UserCtx ctx = {0};
	ctx.logFn = vsPKILog;

	status = VSVAL_ParseB64Cert(vs,&ctx,(VSVAL_CertFields**) certFields, b64cert);
		/* Special Note: we used cast to convert between VSVAL_CertFields and VS_SSC_CertFields */
		/* because they are identical. Attention is needed when CVM updates*/

	/* if error, convert code to SSC error */
    if(status) {
	  status = ErrorCodeCVM2SSC(status);
	}
    return status;

}

/* Free up memory for certfields. This function must be called to free up the memory of free cert*/
/* DO NOT use vsPKIFree() to free up cert field. This will cause memory leak */
Dll void vsPKIFreeCertFields(VS_SSC_CertFields *certFields) {

	VSVAL_FreeCertFields(vs, (VSVAL_CertFields *) certFields);
}


Dll void vsPKIFree(void *p) {
	VSVAL_Free(vs,p);
}

