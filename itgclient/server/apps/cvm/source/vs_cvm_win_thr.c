/**
*  Windows based CRL Thread
**/
#include <windows.h>
#include <process.h>
#include <time.h>

#include "cvmglobal.h"
#include "vsvalsdk.h"

#include "vs_cvm_log.h"
#include "vs_cvm_constants.h"

#define VS_MUTEX_NAME "verisign_crl_update_mutex"
#define VS_MUTEX_SLEEP_NAME "verisign_crl_update_sleep_mutex"

/**
*  GLOBALS
**/
int sleeperRunning = 1;
int thrLogInfo = 1;
unsigned long int thrUpdateSeconds = 0;
unsigned long int *thrLastUpdate;

VSVAL_SDK *globalValSDK;

unsigned long hThread = 0;

HANDLE hThrMutex = 0;
HANDLE hThrMutexSleep = 0;

SECURITY_ATTRIBUTES saDefSec = {0};

/**
*  The routine that is threaded to update the CRL.
**/
void vs_cvm_genlib_crl_thread(void *ptr) {
  
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
		if (WaitForSingleObject(hThrMutex, INFINITE)==WAIT_OBJECT_0) {
	
		/** 
		*  See if we have to update all the CRLs based on timer. 
		**/
		cvm_time(&currentTime);
		
		if (currentTime > (unsigned long)(*thrLastUpdate + thrUpdateSeconds)) {
			
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
	if (ReleaseMutex(hThrMutex) == 0) {

		vs_cvm_genlib_log_message(VS_LOG_FAILURE, "Error releasing mutex");

	}

	/**
	*  Sleep 1/3 update time. In ms. 
	*  Make sure the sleep is outside the critical section!
	**/
	rc = WaitForSingleObject(hThrMutexSleep, thrUpdateSeconds * 334);
	
  }	
  
}

/**
*  This routine creates the mutexes used for critical sections. Is called during init.
**/
int vs_cvm_genlib_create_mutexes() {


	char curTime[128];
	char curDate[128];
	char vsMutexName[400];
	char vsMutexSleepName[400];

	_strtime(curTime);
	_strdate(curDate);

	sprintf(vsMutexName, "%s_%s_%s", VS_MUTEX_NAME, curDate, curTime);
	sprintf(vsMutexSleepName, "%s_%s_%s", VS_MUTEX_SLEEP_NAME, curDate, curTime);

	hThrMutex = CreateMutex(&saDefSec, FALSE, vsMutexName);
	if (hThrMutex == 0) {		
		return FALSE;
	}

	if (thrLogInfo == 1) {
		vs_cvm_genlib_log_message(VS_LOG_INFO, "Created mutex %s", vsMutexName);
	}


	hThrMutexSleep = CreateMutex(&saDefSec, FALSE, vsMutexSleepName);
	if (hThrMutexSleep == 0) {
		return FALSE;	
	}

	if (thrLogInfo == 1) {
		vs_cvm_genlib_log_message(VS_LOG_INFO, "Created mutex %s", vsMutexSleepName);
	}


	if(WaitForSingleObject(hThrMutexSleep, 60000) != WAIT_OBJECT_0) {
		return FALSE;
	}

	return TRUE;
}

/**
*  The routine to start the CRL Thread
**/
int vs_cvm_genlib_start_crl_thread(unsigned long int *glu, 
								   unsigned long int gus, 
							       int gli,
							       VSVAL_SDK *gvsdk) {

	thrLastUpdate = glu;
	thrUpdateSeconds = gus;
	thrLogInfo = gli;
	globalValSDK = gvsdk;

	if(thrUpdateSeconds < CVM_MAX_UPDATE_TIME) {

		sleeperRunning = 1;
		if((hThread = _beginthread(vs_cvm_genlib_crl_thread, 0, 0)) == -1) {

			return VSVAL_ERR_THREAD;

		}
	}

	return 0;
}

/**
*  The routine to stop the CRL Thread
**/
void vs_cvm_genlib_stop_crl_thread() {

	/**
	*  Wait a few seconds to try and get the mutex. 
	**/
	WaitForSingleObject(hThrMutex, 5000);

	/**
	*  Clean things up. 
	**/
	if (hThrMutex) {
		CloseHandle(hThrMutex); 
		hThrMutex =0;
	}

	ReleaseMutex(hThrMutexSleep);
	sleeperRunning = 0;

	/**
	*  Wait a while, otherwise other thread will crash 
	**/
	Sleep(5000);
	if (hThrMutexSleep) {
		CloseHandle(hThrMutexSleep);
		hThrMutexSleep=0;
	}

}

