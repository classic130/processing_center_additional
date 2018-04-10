/**
*  Header file for the CVM Generic Wrapper
**/


/**
*  Structure for passing initialization parameters.
**/

#include "vsvalsdk.h"

#define GL_VSVAL_BUF_MAX VSVAL_BUF_MAX
#define GL_VSVAL_ERR_REGISTRY VSVAL_ERR_REGISTRY

typedef struct {
	char *logFileName;	
	char *logInfo;
	char *logDebug;
	char *logSecurity;
	char *filePrefix;
	char *urlPrefix;
	char *cacheDir;
	char *httpProxy;
	char *ldapHttpProxy;
	char *defaultLdap;
	int ldapTimeOut;
	char *ocspUrl;
	char *noCheckChain;
	int updateSeconds;
	char *cfgFileName;
	int debugWait;
	char *lockFile;
	int sleepThreshold;
	char *filterDescription;
	FILE *logError;
} CFG_PARAMS;

typedef struct VSVAL_CertFields_s CERT_FIELDS;

/**
*  Functions exported by the CVM Generic Library
**/
int vs_cvm_genlib_init(CFG_PARAMS cp);
int vs_cvm_genlib_validate(unsigned char *certData, 
						   unsigned int certLen, 
						   int *certStatus, 
						   char *userName,
						   CERT_FIELDS *cf);
void vs_cvm_genlib_exit();
char * vs_cvm_genlib_get_cs_str(int certStatus);
int vs_cvm_genlib_get_err_str(char *errorString, int status);
int vs_cvm_genlib_make_canonical_opt_name(char *canonicalNameBuf, char *name);

