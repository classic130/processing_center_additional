/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/vsprscgi/include/Attic/vslog.h,v 1.1.2.1 2001/10/02 00:57:27 rpandran Exp $
 */

/*-----------------------------------------------------------------------\ 
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSSC_LOG_H_
#define _VSSC_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  erFALSE = 0,
  erTRUE
} VS_BOOL;

/* This enum holds all error codes that can be returned from
 * calls to VeriSign's DLL.
 */

typedef enum {
  eERR_NO_ERROR = 0,      /* no error */
  eERR_INVALID_INDEX,     /* index is out of range */
  eERR_PARAM_REQUIRED,    /* required parameter was not supplied */
  eERR_PARAM_INVALID,     /* parameter value is invalid */
  eERR_LOG_ALREADY_OPEN,
  eERR_CANT_OPEN_LOG
} VS_STATUS;

/* 
 * Logging Level type
 */
typedef enum VS_LOG_TYPE {
    VS_LOG_EMERGENCY,     /* Emergency condition */
    VS_LOG_ALERT,         /* Condition that should be corrected
                               immediately */
    VS_LOG_CRITICAL,      /* Critical condition */
    VS_LOG_ERROR,         /* Errors */
    VS_LOG_WARNING,       /* Warning messages */
    VS_LOG_NOTICE,        /* Conditions that are not errors,
                               but may need special handling */
    VS_LOG_INFO,          /* Informational messages */
    VS_LOG_DEBUG          /* Debugging messages only */
} VS_LOG_TYPE;

/*
 * Macro to provide a status check at the end of functions
 */
#define VSFUNCRETURNLOG(msg,status) \
    if (status != 0) VS_Log (VS_LOG_ERROR, __LINE__, __FILE__, \
        "%s returns error 0x%x", msg, status)

/* VS_Log 
 *	This function logs a message.
 *
 *  level - the logging level.
 *	line - the line number in the source file.  Use the macro 
 *		__LINE__ as input.
 *	filename - the name of the source file.  Use the macro 
 *		__FILE__ as input.
 *	format - a character string used in the same manner as the 
 *		one in printf.
 */

VS_STATUS VS_Log (VS_LOG_TYPE level, int line, const char *filename,
           char *format, ...);

/* VS_DataLog 
 *	This function logs a message without any change or addition
 *  to log file.
 *
 *	format - a character string used in the same manner as the 
 *		one in printf.
 */

VS_STATUS VS_DataLog(char *format, ...);

/* VS_OpenLogFile 
 *	Opens a file where subsequent logging message will be written
 */

VS_STATUS VS_OpenLogFile (const char *filename);


/* VS_SetLogLevel 
 *	Changes "gVSLogLevel" to the same level as indicated
 * 	in the string "level".
 */

VS_STATUS VS_SetLogLevel (const char *level);


/* VS_CloseLogFile 
 *	Closes the log file.
 */

VS_STATUS VS_CloseLogFile (void);

/* VS_GetLogFile
 * Return the file pointer of the log
 */
FILE *VS_GetLogFile(void);

/* VS_SetLogFile
 * Changes "logFP" to the file pointer fp.
 */

VS_STATUS VS_SetLogFile(FILE* fp);

/* Useful macros
 */

#define VSFUNCBREAK(funcname)  { VSFUNCRETURNLOG(funcname, status); break; }

#define VSLOGERROR(msg) \
    VS_Log (VS_LOG_ERROR, __LINE__, __FILE__, msg)

#define VSLOG(level, msg) \
    VS_Log (level, __LINE__, __FILE__, msg)

#define VSTRACE(msg) \
    VS_Log (VS_LOG_DEBUG, __LINE__, __FILE__, ">>> %s", msg)

#ifdef  __cplusplus
}
#endif

#endif	/* _VSLOG_H_ */
