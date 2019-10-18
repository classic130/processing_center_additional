/**
*  Solaris based CRL Thread
**/
#include <thread.h>

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

thread_t hThread;

rwlock_t hThrMutex; 

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
		if(rw_wrlock(&hThrMutex) == 0) {
	
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
			rc = -1;
			thr_exit((void *)&rc);
		}

		/* And release the mutex. */
		if (rw_unlock(&hThrMutex) != 0) {

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
	thr_exit((void *)&rc);

}

/**
*  This routine creates the mutexes used for critical sections. Is called during init.
**/
int vs_cvm_genlib_create_mutexes() {

	int iStatus = 0;

	iStatus = rwlock_init(&hThrMutex, USYNC_THREAD, 0);
	if(iStatus == 0) {
		return 1;
	} else {
		if (thrLogInfo == 1) {
			vs_cvm_genlib_log_message(VS_LOG_INFO, "Lock Init returned %d", iStatus);
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
		thr_create(NULL, 0, vs_cvm_genlib_crl_thread, 0, 0, &hThread);

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
	rwlock_destroy(&hThrMutex);

}

