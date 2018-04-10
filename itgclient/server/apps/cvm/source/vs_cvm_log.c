/**
*  Provides logging routines for the plugins and the generic wrapper.
**/

#include <stdio.h>
#include <stdarg.h>

#include "time.h"
#include "cvmglobal.h"
#include "vsvalsdk.h"

FILE *logFP = 0;

/**
*  This routine sets the log file pointer.
**/
void vs_cvm_genlib_set_fp(FILE *parLogFP) {

	logFP = parLogFP;

}

/**
*  This routine logs the message in the required format to the file set in the 
*  above routine
**/
void vs_cvm_genlib_log_message(char* severity, char *fmt, ...) {

	char infoBuf[CVM_LARGE_BUF_MAX];
	CVMTIME currentTime;
	char *timeBuf = 0;
	va_list ap;
	va_start(ap, fmt);

	if (logFP == 0) {
		return;
	}

	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);

	cvm_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	cvm_make_newline_null(timeBuf);
	
	fprintf(logFP, "[%s] %s: %s\n", timeBuf, severity, infoBuf);
	fflush (logFP);

	return;

}

/**
*  This routine logs the message in the required format to the file set in the 
*  above routine. This set in the Validation SDK context
**/

void vs_cvm_genlib_sdk_log_message(void* handle, char *fmt, ...) {

	char infoBuf[CVM_LARGE_BUF_MAX];
	CVMTIME currentTime;
	char *timeBuf = 0;
	va_list ap;
	va_start(ap, fmt);

	if (logFP == 0) {
		return;
	}
	
	(void) vsprintf(infoBuf, fmt, ap);
	va_end(ap);

	cvm_time(&currentTime);
	timeBuf = asctime(localtime((const time_t *) &currentTime));
	cvm_make_newline_null(timeBuf);
	
	fprintf(logFP, "[%s] info: %s\n", timeBuf, infoBuf);
	fflush (logFP);

	return;

}
/**
*  A dummy routine to log nothing.
**/

void vs_cvm_genlib_sdk_log_null_message(void* handle, char *fmt, ...) {

	return;

}

