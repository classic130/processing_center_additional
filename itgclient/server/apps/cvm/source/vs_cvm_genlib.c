/**
*  Wrapper Library for the Validation SDK.
*  For Windows.
**/

#include <stdio.h>

/**
*  For threading on different platforms
**/
#if defined(WIN32)
   #include "vs_cvm_win_thr.h"
#elif defined(SOLARIS)
   #include "vs_cvm_sol_thr.h"
#elif defined(HPUX)
   #include "vs_cvm_pos_thr.h"
#elif defined(LINUX) || defined(LINUX64)
   #include "vs_cvm_pos_thr.h"
#elif defined(AIX)
   #include "vs_cvm_pos_thr.h"
#else
   #error "Your platform is not supported!"
#endif

#include "vs_cvm_constants.h"

#include "vs_cvm_genlib.h"

#include "cvmglobal.h"
#include "vsvalsdk.h"

#include "vs_cvm_log.h"



/**
*  GLOBALS
**/


char *globalErrorCgi;

/**
*  For logging
**/
FILE *globalLogFP = 0;
char *globalLogName;
int globalLogInfo;
int globalLogDebug;
int globalLogSecurity;

/** 
*  Handle to validation SDK instance 
**/
VSVAL_SDK *globalValSDK;


/**
*  Variables for time based CRL updates.
**/
CVMTIME globalUpdateSeconds = 0;
CVMTIME globalLastUpdate = 0;


/**
*   Wrapper function to initialize Validation SDK variables .
*   Exported function.
**/
int vs_cvm_genlib_init(CFG_PARAMS cp) {

	int status = 0;
	char errorString[CVM_LARGE_BUF_MAX];

	VSVAL_UserCtx ctx = {0};

	/**
	*  Initialize the contexts (Validation SDK Handle, User Context)
	**/
	if ((status = VSVAL_Init(&globalValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
		return status;
	}


	do {
		/**
		*  Copy the global parameters from the structure.
		*  These are not passed to the Validation SDK
		**/
#if defined(NSAPI3_0)

		globalLogFP = cp.logError;

#else 
		if(!cp.logFileName && cp.logError) {
			globalLogFP = cp.logError;
		} else {
			globalLogName = cp.logFileName;
			if ((globalLogFP = fopen(globalLogName, "a")) == 0) {
				status = VSVAL_ERR_FILE_NOT_OPEN;
				break;
			}
		}
#endif

		vs_cvm_genlib_set_fp(globalLogFP);
		globalLogInfo = 0;
		if (cvmCfgStringIsOn(cp.logInfo)) {
			if (globalLogFP != 0) {
				globalLogInfo = 1;
			}
		}


		if (globalLogInfo == 1) {
			ctx.logFn = vs_cvm_genlib_sdk_log_message;
		} else {
			ctx.logFn = vs_cvm_genlib_sdk_log_null_message;
		}


		globalLogDebug = 0;
		if (cvmCfgStringIsOn(cp.logDebug)) {
			if (globalLogFP != 0) {
				globalLogDebug = 1;
			}
		}


		globalLogSecurity = 0;
		if (cvmCfgStringIsOn(cp.logSecurity) && (globalLogFP != 0) ) {
			globalLogSecurity = 1;
		}


		/**
		*  Use the validation SDK routine VSVAL_SetOpt to pass the initialization 
		*  data to the Validation SDK.
		**/
		if (cp.filePrefix != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "File Prefix : %s", cp.filePrefix);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "file-prefix", cp.filePrefix)) {
				break;
			}
		}

		
		if (cp.urlPrefix != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "URL Prefix : %s", cp.urlPrefix);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "url-prefix", cp.urlPrefix)) {
				break;
			}
		}

		if (cp.cacheDir != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "Cache Dir : %s", cp.cacheDir);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "cache_dir", cp.cacheDir)) {
				break;
			}
		}

		if (cp.httpProxy != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "HTTP Proxy : %s", cp.httpProxy);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "http-proxy", cp.httpProxy)) {
				break;
			}
		}

		if (cp.ldapHttpProxy != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "LDAP HTTP Proxy : %s", cp.ldapHttpProxy);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "ldap-http-proxy", cp.ldapHttpProxy)) {
				break;
			}
		}

		if (cp.ldapTimeOut < 0) {
			cp.ldapTimeOut = CVM_LDAP_TIMEOUT;
		}
		if(globalLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "LDAP Timeout : %d", cp.ldapTimeOut);
		}
		if (status = VSVAL_SetIntOpt(globalValSDK, &ctx, "ldap-timeout", cp.ldapTimeOut)) {
			break;
		}

		if (cp.ocspUrl != 0) {
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "OCSP : %s", cp.ocspUrl);
			}
			if (status = VSVAL_SetOpt(globalValSDK, &ctx, "ocsp-url", cp.ocspUrl)) {
				break;
			}
		}

		if (cp.defaultLdap !=0) {
			status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", cp.defaultLdap);
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "Default LDAP : %s", cp.defaultLdap);
			}

		} else {
			status = VSVAL_SetOpt (globalValSDK, &ctx, "default-ldap", "directory.verisign.com");
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "Default LDAP : directory.verisign.com");
			}

		}
		if (status != 0) {
			break;
		}

/*  Fix for CR29977 - Begin */
               if (!cp.noCheckChain) {
                        status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "off");

                      }
               else { 
/*  Fix for CR29977 - End   */
		if (cvmCfgStringIsOn(cp.noCheckChain)) {
			status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "on");
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "No Check Chain : on");
			}

		} else {
			status = VSVAL_SetOpt (globalValSDK, &ctx, "no-check-chain", "off");
			if(globalLogInfo == 1) {
				vs_cvm_genlib_log_message(VS_LOG_INFO, "No Check Chain : off");
			}

		}
		if (status != 0) {
			break;
                   }
		}
                
		/**
		*  Get CRL update frequency. 
		**/
		if (cp.updateSeconds <= 0) {
			globalUpdateSeconds = CVM_MAX_UPDATE_TIME;
		} else {
			globalUpdateSeconds = cp.updateSeconds;
		}
		if(globalLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "Update Seconds : %d", globalUpdateSeconds);
		}



		/**
		*  Call the Validation SDK function VSVAL_ReadConfigFile 
		*  to read the configuration file.
		**/
		if(globalLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "Config File : %s", cp.cfgFileName);
		}
		if (status = VSVAL_ReadConfigFile(globalValSDK, &ctx, cp.cfgFileName)) {
			VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
			vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", errorString);
			status = 0;
		}

		
		vs_cvm_genlib_log_message(VS_LOG_INFO, "%s starting", cp.filterDescription);

		/**
		*  Create Mutexes
		**/
		if(globalLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "Creating Mutexes");
		}
		if(!(vs_cvm_genlib_create_mutexes())) {
			vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Error in Creating Mutexes");
			return VSVAL_ERR_MUTEX_CREATE;
		}


		/**
		*  Start the thread that would update the 
		*  CRL (Certificate Revocation List) at predefined intervals.
		**/
		if(globalLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "Starting Thread");
		}
		status = vs_cvm_genlib_start_crl_thread(&globalLastUpdate, 
												globalUpdateSeconds, 
												globalLogInfo,
												globalValSDK);
		if(status != 0) {
			break;
		}


	} while (0);

	/**
	*  Log Errors
	**/
	if (status) {
		if ((status > VSVAL_ERR_BASE) && (status < VSVAL_ERR_MAX)) {
			VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
			vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", errorString);
		}
	}


	if (globalLogFP) {
		fflush(globalLogFP);
	}

	if(globalLogInfo == 1) {
		vs_cvm_genlib_log_message(VS_LOG_INFO, "End of Init Function : Status %d", status);
	}


	return status;
}


/**
*   Wrapper function to check the validity of the certificate.
*   Exported function.
**/
int vs_cvm_genlib_validate(unsigned char *certData,
						   unsigned int certLen,
						   int *certStatus,
						   char *userName,
						   CERT_FIELDS *certFields) {

	int status = 0;
	CVMTIME currentTime = 0;
	CVMTIME expireTime = 0;
	int refreshStatus = 0;
	char refreshStatusString[CVM_LARGE_BUF_MAX];
	VSVAL_UserCtx ctx = {0}; 
	
	
	if (globalLogInfo == 1)
		ctx.logFn = vs_cvm_genlib_sdk_log_message;
	else
		ctx.logFn = vs_cvm_genlib_sdk_log_null_message;

	do {

		if(!certData) {
			status = VSVAL_ERR_NO_AUTH_CERT;
			break;
		}

		/**
		*  See if we have to update all the CRLs based on timer. 
		**/
		cvm_time(&currentTime);
		if (currentTime > (globalLastUpdate + globalUpdateSeconds)) {
	  
			globalLastUpdate = currentTime;
     
			if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {
				/**
				*  Ignore errors, but print an error message. 
				**/
				vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");
		
				/**
				*  Also print the last error's cause. 
				**/
				if (VSVAL_ErrorString(globalValSDK, refreshStatusString, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
					sprintf (refreshStatusString, "Error Code : %d", refreshStatus);
				}

				vs_cvm_genlib_log_message(VS_LOG_FAILURE, refreshStatusString);
			}
		}      

		/** 
		*  Look up the certificate
		**/
		if(certLen == -1) {
			status = VSVAL_GetRevocationStatusB64(globalValSDK, &ctx, (char *)certData, certStatus, &userName);
		} else {
			status = VSVAL_GetRevocationStatus(globalValSDK, &ctx, certData, certLen, certStatus, &userName);
		}
    
	} while (0);

	if (status) {
		/**
		*  Log Errors 
		**/
		VSVAL_ErrorString (globalValSDK, refreshStatusString, VSVAL_BUF_MAX, status, ctx.errorInfo);
		vs_cvm_genlib_log_message(VS_LOG_FAILURE, "%s", refreshStatusString);

		/**
		*  Check if denials are to be logged. If yes then log them.
		**/
		if (globalLogSecurity && certStatus) {
			vs_cvm_genlib_log_message(VS_LOG_SECURITY, "Certificate %s for %s", 
								VSVAL_CertStatusString(globalValSDK, *certStatus), userName ? userName : "client");
		}

	} else {

		if (*certStatus == CS_VALID) {

			/**
			*  Get the certificate extensions
			**/
			if(certLen == -1) {
				status = VSVAL_ParseB64Cert(globalValSDK, &ctx, &certFields, (char *)certData);
			} else {
				status = VSVAL_ParseCert(globalValSDK, &ctx, &certFields, certData, certLen);
			}

     
			/**
			*  Append validation info to the log
			**/
			if (globalLogSecurity) {
				vs_cvm_genlib_log_message(VS_LOG_ACCESS, "auth-user %s", userName ? userName : "client");
			}

		} else {
      
			/**
			*  Check if denials are to be logged. If yes then log them.
			**/
			if (globalLogSecurity && certStatus) {
				vs_cvm_genlib_log_message(VS_LOG_SECURITY, "Certificate %s for %s", 
									VSVAL_CertStatusString(globalValSDK, *certStatus), userName ? userName : "client");
			}
			
		}
	}

	if (userName) {
		VSVAL_Free (globalValSDK, userName);
	}
        if(certFields != NULL) {
  		VSVAL_FreeCertFields(globalValSDK, certFields);
	}
	return status;
}

/**
*   Wrapper function to cleanup before exit.
*   Exported function.
**/
void vs_cvm_genlib_exit() {

	if (globalLogDebug == 1) {
		vs_cvm_genlib_log_message(VS_LOG_DEBUG, "vs_cvm_genlib_exit::");
	}

	/**
	*  Call the function to release all mutexes/locks.
	**/
	vs_cvm_genlib_stop_crl_thread();

	/**
	*  Notify the Validation SDK so that it carries out the cleanup procedure
	**/
	VSVAL_Final (globalValSDK);	
	globalValSDK = NULL;

	/**
	*  Close the Log file
	**/
	if(globalLogFP) {
		fclose(globalLogFP);
	}
	globalLogFP = 0;

}

/**
*   Wrapper function to get the description of the certificate status.
*   Exported function.
**/
char * vs_cvm_genlib_get_cs_str(int certStatus) {

	return VSVAL_CertStatusString(globalValSDK, certStatus);

}
/**
*   Wrapper function to get the description of an error status.
*   Exported function.
**/
int vs_cvm_genlib_get_err_str(char *errorString, int status) {

	VSVAL_UserCtx ctx = {0};

	return VSVAL_ErrorString(globalValSDK, errorString, VSVAL_BUF_MAX, status, ctx.errorInfo);

}

/**
*   Wrapper function to get the canonical name for an option name.
*   Exported function.
**/
int vs_cvm_genlib_make_canonical_opt_name(char *canonicalNameBuf, char *name) {
	return VSVAL_MakeCanonicalOptionName(canonicalNameBuf, CVM_LARGE_BUF_MAX, name);
}

