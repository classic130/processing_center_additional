/**
*  POSIX based CRL Thread
**/
#include <pthread.h>

#include "cvmglobal.h"
#include "vsvalsdk.h"

#include "vs_cvm_log.h"
#include "vs_cvm_constants.h"

#define VS_MUTEX_NAME "verisign_validate_mutex"
#define VS_MUTEX_SLEEP_NAME "verisign_validate_mutex_sleep"

/**
*  GLOBALS
**/
int sleeperRunning = 1;
int thrLogInfo = 0;
unsigned long int thrUpdateSeconds = 0;
unsigned long int *thrLastUpdate;

VSVAL_SDK *globalValSDK;

pthread_t hThread;

pthread_mutex_t hThrMutex; 


/**
*  The routine that is threaded to update the CRL.
**/
void *vs_cvm_genlib_crl_thread(void *ptr) {
  
	CVMTIME currentTime = 0;
	int refreshStatus = 0;
	VSVAL_UserCtx ctx = {0};
	char buf[CVM_LARGE_BUF_MAX];
	int rc = 0;

	if (thrLogInfo == 1) {
		ctx.logFn = vs_cvm_genlib_sdk_log_message;
	} else {
		ctx.logFn = vs_cvm_genlib_sdk_log_null_message;
	}

	while (sleeperRunning) {
	
		/** 
		*  Acquire the critical section lock 
		**/
		if(pthread_mutex_lock(&hThrMutex) == 0) {
	
			/** 
			*  See if we have to update all the CRLs based on timer. 
			**/
			cvm_time(&currentTime);
		
			if (currentTime > (*thrLastUpdate + thrUpdateSeconds)) {
			
				*thrLastUpdate = currentTime;	
			
				/**
				*  Re-get all CRLs. 
				**/
				if (refreshStatus = VSVAL_RefreshCertsCRLs(globalValSDK, &ctx, 0)) {
				
					/**
					*  Ignore errors, but print an error message. 
					**/
					vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Problems acquiring CRLs. Some not installed.");

					/**
					*  Also print the last error's cause. 
					**/
					if (VSVAL_ErrorString(globalValSDK, buf, CVM_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
						sprintf (buf, "Error Code : %d", refreshStatus);
					}
					vs_cvm_genlib_log_message(VS_LOG_FAILURE, buf);
		  
				} else {
					if (thrLogInfo == 1) {
						vs_cvm_genlib_log_message(VS_LOG_INFO, "Successfully refreshed certificates and CRLs.");
					}
				}
			}
		} else {
			vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Could not acquire mutex");
		}

		/* And release the mutex. */
		if (pthread_mutex_unlock(&hThrMutex) != 0) {

			vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Error releasing mutex");

		}

		/**
		*  Sleep 1/3 update time. In ms. 
		*  Make sure the sleep is outside the critical section!
		**/
		sleep((int)(thrUpdateSeconds/3));

	}	
	/**
	*  Exit Thread
	**/
	pthread_exit(NULL);

}

/**
*  This routine creates the mutexes used for critical sections. Is called during init.
**/
int vs_cvm_genlib_create_mutexes() {

	int iStatus;
	iStatus = pthread_mutex_init(&hThrMutex, NULL); 
        if(iStatus == 0) {
                return 1;
        } else {
                if (thrLogInfo == 1) {
                        vs_cvm_genlib_log_message(VS_LOG_INFO, "Mutex Init returned %d", iStatus);
                }
                return 0;
        }

}

/**
*  The routine to start the CRL Thread
**/
int vs_cvm_genlib_start_crl_thread(unsigned long int *glu, 
							   unsigned long int gus, 
							   int gli,
							   VSVAL_SDK *gvsdk) {

	pthread_attr_t attr;
	int threadID;

	thrLastUpdate = glu;
	thrUpdateSeconds = gus;
	thrLogInfo = gli;
	globalValSDK = gvsdk;


	pthread_attr_init(&attr);

	if(thrUpdateSeconds < CVM_MAX_UPDATE_TIME) {

		sleeperRunning = 1;
		pthread_create(&hThread, &attr, vs_cvm_genlib_crl_thread, (void *)&threadID);

	}

	return 0;
}

/**
*  The routine to stop the CRL Thread
**/
void vs_cvm_genlib_stop_crl_thread() {

	/**
	*  Try and get the mutex. 
	**/
	sleeperRunning = 0;

	pthread_mutex_destroy(&hThrMutex);

}

