/*
$Revision: 1.1.6.1 $
$Header: /cvs/itgclient/server/apps/exchange/vsexchange/Attic/vslog.cpp,v 1.1.6.1 2003/06/06 22:46:30 npaul Exp $
*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

static char *_VSLOG_CPP= (char *) "$Id: vslog.cpp,v 1.1.6.1 2003/06/06 22:46:30 npaul Exp $";

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>

#ifdef WIN32
  #include <windows.h>
  #include <process.h>
#elif defined(SOLARIS) || defined(HPUX) || defined(AIX)
  #include <unistd.h>
  #ifdef _REENTRANT
    #include <pthread.h>
  #endif
#else
  #error "platform not supported"
#endif

#include "vslog.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Only include here because can't find a Unix prototype for this */
#ifdef SOLARIS
int gethostname(char *name, int namelen); 
#endif

#ifdef __cplusplus
}
#endif


#define SEPARATOR	":"

#define BUFFER_SIZE	1024

#define MAX_EXCEPTION_CODES	100

int gVSLogLevel = VS_LOG_INFO;

static char hostname[128];

static VS_BOOL initialized = eFALSE;
FILE    *logFP = NULL;        /* output log file, if any */
static int     pid;                  /* used to store process id */

#ifdef WIN32
  CRITICAL_SECTION logFileLock;
#elif defined(_REENTRANT)
  pthread_mutex_t  logFileLock;
#endif
int              logFileLockInit = 0;

/* This is part of the C libraries on Sun but not NT?
 * return a pointer to the base name of a pathname
 */
static const char *basename (const char *pathname)
{
  char *p = (char *) pathname;
  char *result = p;

  while (*p) {
    while (*p && (*p != '/') && (*p != '\\')) {
      ++p;
    }
    if (*p && *(p + 1))
      result = ++p;
  }

  return ((const char *) result);
}


VS_STATUS VSAA_Log(
	VS_LOG_TYPE level,
	int line, const char *filename,
	char *format,
	...)
{
    va_list ap;

    char pidstr[24];                     /* used to store thread/process id */
    char timeBuffer[32];                 /* used to format timestamp */
    char levelBuffer[32];                /* used to indicate level */ 
    char strBuffer[BUFFER_SIZE];
    char totalBuffer[BUFFER_SIZE];
    time_t currentTime;
    int total_chars = 0;
    FILE *fp = NULL;
    
    va_start(ap, format);

    do {
        if (!initialized) {
            initialized = eTRUE;
            gethostname (hostname, 128);
									
#ifdef WIN32
            pid = _getpid();
#elif defined(SOLARIS) || defined(HPUX) || defined(AIX)
            pid = getpid();
#endif
        }
            
#ifdef WIN32

        if (!logFileLockInit)
        {
            InitializeCriticalSection(&logFileLock);
            logFileLockInit = 1;
        }    
    
        EnterCriticalSection(&logFileLock);      
        sprintf (pidstr, "%d/%d", pid, GetCurrentThreadId());

#elif defined(SOLARIS) || defined(HPUX) || defined(AIX)

#if defined(_REENTRANT)
        if (!logFileLockInit)
        {
            pthread_mutex_init(&logFileLock, NULL);
            logFileLockInit = 1;
        }    
    
        pthread_mutex_lock(&logFileLock);
        sprintf (pidstr, "%d/%d", pid, pthread_self());
#else
        sprintf (pidstr, "%d", getpid());
#endif
        
#else

       #error "platform not supported"

#endif

        if (level > gVSLogLevel) {
            break;
        }
        
        switch(level) {
        case VS_LOG_EMERGENCY: 
            strcpy(levelBuffer, "EMERGENCY");
            break;
        case VS_LOG_ALERT:
            strcpy(levelBuffer, "ALERT");
            break;
        case VS_LOG_CRITICAL:
            strcpy(levelBuffer, "CRITICAL");
            break;
        case VS_LOG_ERROR:
            strcpy(levelBuffer, "ERROR");
            break;
        case VS_LOG_WARNING:
            strcpy(levelBuffer, "WARNING");
            break;
        case VS_LOG_NOTICE:
            strcpy(levelBuffer, "NOTICE");
            break;
        case VS_LOG_INFO:
            strcpy(levelBuffer, "INFO");
            break;
        case VS_LOG_DEBUG:
            strcpy(levelBuffer, "DEBUG");
            break;
        default:
            strcpy(levelBuffer, "DEBUG");
            break;
        }
        
        time (&currentTime);
        strftime (timeBuffer,32,"%m/%d/%Y %H:%M:%S ", 
        	   localtime ((const time_t *) &currentTime));
        sprintf (totalBuffer, "%s %s", levelBuffer, timeBuffer);
        
        sprintf (strBuffer, " %s(%s)  %s(%d)%s",
            hostname, pidstr, basename ((char *) filename), line,
            SEPARATOR);
        strcat(totalBuffer, strBuffer);
        
        if (logFP != NULL) {
            fp = logFP;
        } else {
            fp = stdout;
        }
        fprintf(fp, totalBuffer);
        total_chars = strlen(totalBuffer) + vfprintf(fp, format, ap);
        fprintf(fp, "\n");
        fflush(fp);
        
        total_chars++;
    } while(0);
    
#ifdef WIN32
    LeaveCriticalSection(&logFileLock);
#elif defined(_REENTRANT) && (defined(SOLARIS) || defined(HPUX) || defined(AIX))
    pthread_mutex_unlock(&logFileLock);
#endif
    
    va_end(ap);

    return eERR_NO_ERROR;
}

VS_STATUS VSAA_LogW(
	VS_LOG_TYPE level,
	int line, const char *filename,
	wchar_t *format,
	...)
{
    va_list ap;

    char pidstr[24];                     /* used to store thread/process id */
    char timeBuffer[32];                 /* used to format timestamp */
    char levelBuffer[32];                /* used to indicate level */ 
    char strBuffer[BUFFER_SIZE];
    char totalBuffer[BUFFER_SIZE];
    time_t currentTime;
    int total_chars = 0;
    FILE *fp = NULL;
    
    va_start(ap, format);

    do {
        if (!initialized) {
            initialized = eTRUE;
            gethostname (hostname, 128);
									
#ifdef WIN32
            pid = _getpid();
#elif defined(SOLARIS) || defined(HPUX) || defined(AIX)
            pid = getpid();
#endif
        }
            
#ifdef WIN32

        if (!logFileLockInit)
        {
            InitializeCriticalSection(&logFileLock);
            logFileLockInit = 1;
        }    
    
        EnterCriticalSection(&logFileLock);      
        sprintf (pidstr, "%d/%d", pid, GetCurrentThreadId());

#elif defined(SOLARIS) || defined(HPUX) || defined(AIX)

#if defined(_REENTRANT)
        if (!logFileLockInit)
        {
            pthread_mutex_init(&logFileLock, NULL);
            logFileLockInit = 1;
        }    
    
        pthread_mutex_lock(&logFileLock);
        sprintf (pidstr, "%d/%d", pid, pthread_self());
#else
        sprintf (pidstr, "%d", getpid());
#endif
        
#else

       #error "platform not supported"

#endif

        if (level > gVSLogLevel) {
            break;
        }
        
        switch(level) {
        case VS_LOG_EMERGENCY: 
            strcpy(levelBuffer, "EMERGENCY");
            break;
        case VS_LOG_ALERT:
            strcpy(levelBuffer, "ALERT");
            break;
        case VS_LOG_CRITICAL:
            strcpy(levelBuffer, "CRITICAL");
            break;
        case VS_LOG_ERROR:
            strcpy(levelBuffer, "ERROR");
            break;
        case VS_LOG_WARNING:
            strcpy(levelBuffer, "WARNING");
            break;
        case VS_LOG_NOTICE:
            strcpy(levelBuffer, "NOTICE");
            break;
        case VS_LOG_INFO:
            strcpy(levelBuffer, "INFO");
            break;
        case VS_LOG_DEBUG:
            strcpy(levelBuffer, "DEBUG");
            break;
        default:
            strcpy(levelBuffer, "DEBUG");
            break;
        }
        
        time (&currentTime);
        strftime (timeBuffer,32,"%m/%d/%Y %H:%M:%S ", 
        	   localtime ((const time_t *) &currentTime));
        sprintf (totalBuffer, "%s %s", levelBuffer, timeBuffer);
        
        sprintf (strBuffer, " %s(%s)  %s(%d)%s",
            hostname, pidstr, basename ((char *) filename), line,
            SEPARATOR);
        strcat(totalBuffer, strBuffer);
        
        if (logFP != NULL) {
            fp = logFP;
        } else {
            fp = stdout;
        }
        fprintf(fp, totalBuffer);
        total_chars = strlen(totalBuffer) + vfwprintf(fp, format, ap);
        fprintf(fp, "\n");
        fflush(fp);
        
        total_chars++;
    } while(0);
    
#ifdef WIN32
    LeaveCriticalSection(&logFileLock);
#elif defined(_REENTRANT) && (defined(SOLARIS) || defined(HPUX) || defined(AIX))
    pthread_mutex_unlock(&logFileLock);
#endif
    
    va_end(ap);

    return eERR_NO_ERROR;
}

/* 
   This function logs information without modifying original
   data or adding extra data in constrast of VS_Log().
*/
VS_STATUS VS_DataLog(char *format, ...)
{
    va_list ap;    
    FILE    *fp = NULL;
        
    va_start(ap, format);
    
#ifdef WIN32

    if (!logFileLockInit)
    {
        InitializeCriticalSection(&logFileLock);
        logFileLockInit = 1;
    }
    EnterCriticalSection(&logFileLock);            

#elif defined(SOLARIS) || defined(HPUX) ||defined(AIX)

#if defined(_REENTRANT)
        if (!logFileLockInit)
        {
            pthread_mutex_init(&logFileLock, NULL);
            logFileLockInit = 1;
        }    
    
        pthread_mutex_lock(&logFileLock);
#endif
        
#else

       #error "platform not supported"

#endif
    
    if (logFP != NULL) {
        fp = logFP;
    } else {
        fp = stdout;
    }
    
    vfprintf(fp, format, ap);
    fflush(fp);                       
    
#ifdef WIN32
    LeaveCriticalSection(&logFileLock);
#elif defined(_REENTRANT) && (defined(SOLARIS) || defined(HPUX) || defined(AIX))
    pthread_mutex_unlock(&logFileLock);
#endif
    
    va_end(ap);

    return eERR_NO_ERROR;
}

VS_STATUS VS_SetLogLevel(const char *level)
{
	if (level == NULL) {
		return eERR_NO_ERROR;
	}

	if (strcmp(level, "VS_LOG_EMERGENCY") == 0) {
		gVSLogLevel = VS_LOG_EMERGENCY;
	} else if (strcmp(level, "VS_LOG_ALERT") == 0) {
		gVSLogLevel = VS_LOG_ALERT;
	} else if (strcmp(level, "VS_LOG_CRITICAL") == 0) {
		gVSLogLevel = VS_LOG_CRITICAL;
	} else if (strcmp(level, "VS_LOG_ERROR") == 0) {
		gVSLogLevel = VS_LOG_ERROR;
	} else if (strcmp(level, "VS_LOG_WARNING") == 0) {
		gVSLogLevel = VS_LOG_WARNING;
	} else if (strcmp(level, "VS_LOG_NOTICE") == 0) {
		gVSLogLevel = VS_LOG_NOTICE;
	} else if (strcmp(level, "VS_LOG_INFO") == 0) {
		gVSLogLevel = VS_LOG_INFO;
	} else if (strcmp(level, "VS_LOG_DEBUG") == 0) {
		gVSLogLevel = VS_LOG_DEBUG;
	}
	return eERR_NO_ERROR;
}


VS_STATUS VS_OpenLogFile(const char *filename)
{
    int saveVSLogLevel = gVSLogLevel;
    
    if (logFP != NULL) {
        return eERR_LOG_ALREADY_OPEN;
    }
    logFP = fopen (filename, "a+");
    
    if (logFP == NULL) {
        return eERR_CANT_OPEN_LOG;
    }
    
    gVSLogLevel = VS_LOG_INFO;
    VSAA_Log (VS_LOG_INFO, __LINE__, __FILE__, (char *)"Log file opened");
    gVSLogLevel = saveVSLogLevel;
    
    return eERR_NO_ERROR;
}


VS_STATUS VS_CloseLogFile(void)
{
    int saveVSLogLevel = gVSLogLevel;
    
    if (logFP != NULL) {
        gVSLogLevel = VS_LOG_INFO;
        VSAA_Log (VS_LOG_INFO, __LINE__, __FILE__, (char *)"Log file closed");
        gVSLogLevel = saveVSLogLevel;
        
        fclose (logFP);
    }
    
    logFP = NULL;
    
    return eERR_NO_ERROR;
}

VS_STATUS VS_SetLogFile(FILE* fp)
{
    VS_STATUS status = eERR_NO_ERROR;
    
    if(logFP != fp) {
//        VS_CloseLogFile();    
        logFP = fp;
    }
    
    return status;
}

FILE *VS_GetLogFile(void)
{
    return logFP;
}
