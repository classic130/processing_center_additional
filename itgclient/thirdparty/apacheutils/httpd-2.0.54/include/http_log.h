/* Copyright 1999-2005 The Apache Software Foundation or its licensors, as
 * applicable.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APACHE_HTTP_LOG_H
#define APACHE_HTTP_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apr_thread_proc.h"

/**
 * @package Apache logging library
 */

#ifdef HAVE_SYSLOG
#include <syslog.h>

#ifndef LOG_PRIMASK
#define LOG_PRIMASK 7
#endif

#define APLOG_EMERG     LOG_EMERG     /* system is unusable */
#define APLOG_ALERT     LOG_ALERT     /* action must be taken immediately */
#define APLOG_CRIT      LOG_CRIT      /* critical conditions */
#define APLOG_ERR       LOG_ERR       /* error conditions */
#define APLOG_WARNING   LOG_WARNING   /* warning conditions */
#define APLOG_NOTICE    LOG_NOTICE    /* normal but significant condition */
#define APLOG_INFO      LOG_INFO      /* informational */
#define APLOG_DEBUG     LOG_DEBUG     /* debug-level messages */

#define APLOG_LEVELMASK LOG_PRIMASK   /* mask off the level value */

#else

#define	APLOG_EMERG	0	/* system is unusable */
#define	APLOG_ALERT	1	/* action must be taken immediately */
#define	APLOG_CRIT	2	/* critical conditions */
#define	APLOG_ERR	3	/* error conditions */
#define	APLOG_WARNING	4	/* warning conditions */
#define	APLOG_NOTICE	5	/* normal but significant condition */
#define	APLOG_INFO	6	/* informational */
#define	APLOG_DEBUG	7	/* debug-level messages */

#define	APLOG_LEVELMASK	7	/* mask off the level value */

#endif

/* APLOG_NOERRNO is ignored and should not be used.  It will be
 * removed in a future release of Apache.
 */
#define APLOG_NOERRNO		(APLOG_LEVELMASK + 1)

/* Use APLOG_TOCLIENT on ap_log_rerror() to give content
 * handlers the option of including the error text in the 
 * ErrorDocument sent back to the client. Setting APLOG_TOCLIENT
 * will cause the error text to be saved in the request_rec->notes 
 * table, keyed to the string "error-notes", if and only if:
 * - the severity level of the message is APLOG_WARNING or greater
 * - there are no other "error-notes" set in request_rec->notes
 * Once error-notes is set, it is up to the content handler to
 * determine whether this text should be sent back to the client.
 * Note: Client generated text streams sent back to the client MUST 
 * be escaped to prevent CSS attacks.
 */
#define APLOG_TOCLIENT          ((APLOG_LEVELMASK + 1) * 2)

/* normal but significant condition on startup, usually printed to stderr */
#define APLOG_STARTUP           ((APLOG_LEVELMASK + 1) * 4) 

#ifndef DEFAULT_LOGLEVEL
#define DEFAULT_LOGLEVEL	APLOG_WARNING
#endif

extern int AP_DECLARE_DATA ap_default_loglevel;

#define APLOG_MARK	__FILE__,__LINE__

/**
 * Set up for logging to stderr.
 * @param p The pool to allocate out of
 */
AP_DECLARE(void) ap_open_stderr_log(apr_pool_t *p);

/**
 * Replace logging to stderr with logging to the given file.
 * @param p The pool to allocate out of
 * @param file Name of the file to log stderr output
 */
AP_DECLARE(apr_status_t) ap_replace_stderr_log(apr_pool_t *p, 
                                               const char *file);

/**
 * Open the error log and replace stderr with it.
 * @param pconf Not used
 * @param plog  The pool to allocate the logs from
 * @param ptemp Pool used for temporary allocations
 * @param s_main The main server
 * @tip ap_open_logs isn't expected to be used by modules, it is
 * an internal core function 
 */
int ap_open_logs(apr_pool_t *pconf, apr_pool_t *plog, 
                 apr_pool_t *ptemp, server_rec *s_main);

/* 
 * The three primary logging functions, ap_log_error, ap_log_rerror, and 
 * ap_log_perror use a printf style format string to build the log message.  
 * It is VERY IMPORTANT that you not include any raw data from the network, 
 * such as the request-URI or request header fields, within the format 
 * string.  Doing so makes the server vulnerable to a denial-of-service 
 * attack and other messy behavior.  Instead, use a simple format string 
 * like "%s", followed by the string containing the untrusted data.
 */

/**
 * One of the primary logging routines in Apache.  This uses a printf-like
 * format to log messages to the error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param s The server on which we are logging
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 * @deffunc void ap_log_error(const char *file, int line, int level, apr_status_t status, const server_rec *s, const char *fmt, ...) 
 */
AP_DECLARE(void) ap_log_error(const char *file, int line, int level, 
                             apr_status_t status, const server_rec *s, 
                             const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * The second of the primary logging routines in Apache.  This uses 
 * a printf-like format to log messages to the error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param p The pool which we are logging for
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 * @deffunc void ap_log_perror(const char *file, int line, int level, apr_status_t status, apr_pool_t *p, const char *fmt, ...) 
 */
AP_DECLARE(void) ap_log_perror(const char *file, int line, int level, 
                             apr_status_t status, apr_pool_t *p, 
                             const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * The last of the primary logging routines in Apache.  This uses 
 * a printf-like format to log messages to the error_log.
 * @param file The file in which this function is called
 * @param line The line number on which this function is called
 * @param level The level of this error message
 * @param status The status code from the previous command
 * @param s The request which we are logging for
 * @param fmt The format string
 * @param ... The arguments to use to fill out fmt.
 * @tip Use APLOG_MARK to fill out file and line
 * @warning It is VERY IMPORTANT that you not include any raw data from 
 * the network, such as the request-URI or request header fields, within 
 * the format string.  Doing so makes the server vulnerable to a 
 * denial-of-service attack and other messy behavior.  Instead, use a 
 * simple format string like "%s", followed by the string containing the 
 * untrusted data.
 * @deffunc void ap_log_rerror(const char *file, int line, int level, apr_status_t status, request_rec *r, const char *fmt, ...) 
 */
AP_DECLARE(void) ap_log_rerror(const char *file, int line, int level, 
                               apr_status_t status, const request_rec *r, 
                               const char *fmt, ...)
			    __attribute__((format(printf,6,7)));

/**
 * Convert stderr to the error log
 * @param s The current server
 * @deffunc void ap_error_log2stderr(server_rec *s)
 */
AP_DECLARE(void) ap_error_log2stderr(server_rec *s);

/**
 * Log the current pid of the parent process
 * @param p The pool to use for logging
 * @param fname The name of the file to log to
 */
AP_DECLARE(void) ap_log_pid(apr_pool_t *p, const char *fname);

/**
 * Retrieve the pid from a pidfile.
 * @param p The pool to use for logging
 * @param filename The name of the file containing the pid
 * @param mypid Pointer to pid_t (valid only if return APR_SUCCESS)
 */
AP_DECLARE(apr_status_t) ap_read_pid(apr_pool_t *p, const char *filename, pid_t *mypid);

typedef struct piped_log piped_log;

/**
 * The piped logging structure.  Piped logs are used to move functionality
 * out of the main server.  For example, log rotation is done with piped logs.
 */
struct piped_log {
    /** The pool to use for the piped log */
    apr_pool_t *p;
    /** The pipe between the server and the logging process */
    apr_file_t *fds[2];
    /* XXX - an #ifdef that needs to be eliminated from public view. Shouldn't
     * be hard */
#ifdef AP_HAVE_RELIABLE_PIPED_LOGS
    /** The name of the program the logging process is running */
    char *program;
    /** The pid of the logging process */
    apr_proc_t *pid;
#endif
};

/**
 * Open the piped log process
 * @param p The pool to allocate out of
 * @param program The program to run in the logging process
 * @return The piped log structure
 * @deffunc piped_log *ap_open_piped_log(apr_pool_t *p, const char *program)
 */
AP_DECLARE(piped_log *) ap_open_piped_log(apr_pool_t *p, const char *program);

/**
 * Close the piped log and kill the logging process
 * @param pl The piped log structure
 * @deffunc void ap_close_piped_log(piped_log *pl)
 */
AP_DECLARE(void) ap_close_piped_log(piped_log *pl);

/**
 * A macro to access the read side of the piped log pipe
 * @param pl The piped log structure
 * @return The native file descriptor
 * @deffunc ap_piped_log_read_fd(pl)
 */
#define ap_piped_log_read_fd(pl)	((pl)->fds[0])

/**
 * A macro to access the write side of the piped log pipe
 * @param pl The piped log structure
 * @return The native file descriptor
 * @deffunc ap_piped_log_read_fd(pl)
 */
#define ap_piped_log_write_fd(pl)	((pl)->fds[1])

AP_DECLARE_HOOK(void, error_log, (const char *file, int line, int level,
                       apr_status_t status, const server_rec *s,
                       const request_rec *r, apr_pool_t *pool,
                       const char *errstr))

#ifdef __cplusplus
}
#endif

#endif	/* !APACHE_HTTP_LOG_H */
