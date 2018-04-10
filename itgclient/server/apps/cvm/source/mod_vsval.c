/* ====================================================================
 * Copyright (c) 1995-1999 The Apache Group.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed By the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * 4. The names "Apache Server" and "Apache Group" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For written permission, please contact
 *    apache@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache"
 *    nor may "Apache" appear in their names without prior written
 *    permission of the Apache Group.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the Apache Group
 *    for use in the Apache HTTP server project (http://www.apache.org/)."
 *
 * THIS SOFTWARE IS PROVIDED BY THE APACHE GROUP ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE APACHE GROUP OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Group and was originally based
 * on public domain software written at the National Center for
 * Supercomputing Applications, University of Illinois, Urbana-Champaign.
 * For more information on the Apache Group and the Apache HTTP server
 * project, please see <http://www.apache.org/>.
 *
 */

/* 
 * Apache vsval module (CVM).  Based on mod_example.c.
 *
 */

#include <stdio.h>

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#include "util_script.h"

#if defined(WIN32)
   #include <windows.h>
#elif defined(SOLARIS)
   #include <ctype.h>
#elif defined(HPUX)
   #include <ctype.h>
#elif defined(AIX)
   #include <ctype.h>
#elif defined(LINUX)
   #include <ctype.h>
#else
   #error "Your platform is not supported!"
#endif

/**
*  Begin Change : Infosys, 16 Jul 04
*  Use generic wrapper to access the Validation SDK.
**/
/* Validation SDK */
/*include "vsvalsdk.h"*/
#include "cvmglobal.h"

#include "vs_cvm_genlib.h"

/* For the timer-based CRL refresh */
/*#include <sys/types.h>*/
/*#include <time.h>*/

/**
*  End Change : Infosys
**/

#define VSVAL_CFG_OFF   0
#define VSVAL_CFG_ON    1
#define VSVAL_CFG_UNSET 2


/* global configuration for each httpd process */
typedef struct {
  char *lockFileName; /* Can override for cases where apache installed on NFS */
  int updateSeconds;
  int sleepThreshold;
  CVMTIME lastUpdate;
} VSVAL_CfgModule;

/* configuration for the main server and all <VirtualHost> contexts */
typedef struct {
  int protected;
/*  VSVAL_SDK *vs;*/
  int logInfo; /* will be set with special case of SetOpt log-info */
  int logSecurity; /* will be set with special case of SetOpt log-security */
  char *redirectCgi;
  int configuredUrlPrefix;
  int configuredFilePrefix;
  int configuredCacheDir;
  int configuredOCSPUrl;
  int lastUpdateSeconds;
} VSVAL_CfgServer;

/* local configuration for all <Directory> and .htaccess contexts */
typedef struct {
  int protected;
} VSVAL_CfgDir;



VSVAL_CfgModule gCfgModule = {0};

/**
* Infosys : cfgParams is used to pass the parameters to the init function
*           cf is used to retrieve the valid certificate fields
**/

CFG_PARAMS cfgParams;
CERT_FIELDS *cf;

/*
 * Declare ourselves so the configuration routines can find and know us.
 * We'll fill it in at the end of the module.
 */
module vsval_module;
static void trace_add(server_rec *s, int level, const char *fmt, ...);
/*
char *cvmCfgGetNextLine(char *lineBuf, int maxLen, FILE *fp);
*/


/* begin file lock mutex code */
#define USE_FCNTL_SERIALIZED_ACCEPT
#if defined(USE_FCNTL_SERIALIZED_ACCEPT)

#define VSVAL_LOCKFILE_DEFAULT_NAME "vsval_lockfile"

static struct flock val_lock_it;
static struct flock val_unlock_it;

static int val_lock_fd = -1;

static char *expand_val_lock_fname(pool *p, char *val_lock_fname) {
  /* possibly bogus cast */
  return ap_psprintf(p, "%s.%lu", ap_server_root_relative(p, val_lock_fname),
                     (unsigned long)getpid());
}


#define val_mutex_child_init(x)

/*
 * Initialize mutex lock.
 * Must be safe to call this on a restart.
 */
void val_mutex_init(server_rec* server, pool *p, char *val_lock_fname) {

  trace_add(server, APLOG_DEBUG, "val_mutex_init begin");

  val_lock_it.l_whence = SEEK_SET;	/* from current point */
  val_lock_it.l_start = 0;		/* -"- */
  val_lock_it.l_len = 0;			/* until end of file */
  val_lock_it.l_type = F_WRLCK;		/* set exclusive/write lock */
  val_lock_it.l_pid = 0;			/* pid not actually interesting */
  val_unlock_it.l_whence = SEEK_SET;	/* from current point */
  val_unlock_it.l_start = 0;		/* -"- */
  val_unlock_it.l_len = 0;		/* until end of file */
  val_unlock_it.l_type = F_UNLCK;		/* set exclusive/write lock */
  val_unlock_it.l_pid = 0;		/* pid not actually interesting */

  val_lock_fname = expand_val_lock_fname(p, val_lock_fname);
  val_lock_fd = ap_popenf(p, val_lock_fname, O_CREAT | O_WRONLY | O_EXCL, 0644);
  if (val_lock_fd == -1) {
        trace_add(server, APLOG_DEBUG, "val_mutex_init error");
	fprintf(stderr, "Cannot open val_lock file: %s\n", val_lock_fname);
	exit(APEXIT_INIT);
  }
  unlink(val_lock_fname);

  trace_add(server, APLOG_DEBUG, "val_mutex_init end");
}

int val_mutex_on(server_rec *server_conf) {

  int ret;

  trace_add(server_conf, APLOG_DEBUG, "val_mutex_on begin");

  while ((ret = fcntl(val_lock_fd, F_SETLKW, &val_lock_it)) < 0 && errno == EINTR) {
	/* nop */
  }

  if (ret < 0) {
	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,
                 "fcntl: F_SETLKW: Error getting accept val_lock, exiting!  "
                 "Perhaps you need to use the Val_LockFile directive to place "
                 "your val_lock file on a local disk!");
    return ret;
  }

  trace_add(server_conf, APLOG_DEBUG, "val_mutex_on end");
  return 0;
}

int val_mutex_off(server_rec *server_conf) {

  int ret;

  trace_add(server_conf, APLOG_DEBUG, "val_mutex_off begin");
  while ((ret = fcntl(val_lock_fd, F_SETLKW, &val_unlock_it)) < 0 && errno == EINTR) {
	/* nop */
  }
  if (ret < 0) {
	ap_log_error(APLOG_MARK, APLOG_EMERG, server_conf,
                 "fcntl: F_SETLKW: Error freeing accept val_lock, exiting!  "
                 "Perhaps you need to use the Val_LockFile directive to place "
                 "your val_lock file on a local disk!");
    return ret;
  }
  trace_add(server_conf, APLOG_DEBUG, "val_mutex_off end");
  return 0;
}

#endif
/* end file lock mutex code */



/*--------------------------------------------------------------------------*/
/*                                                                          */
/* These routines are strictly internal to this module, and support its     */
/* operation.  They are not referenced by any external portion of the       */
/* server.                                                                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/

/* Locate our directory configuration record for the current request. */
static VSVAL_CfgDir *our_dconfig(request_rec *r) {
  return (VSVAL_CfgDir *) ap_get_module_config(r->per_dir_config, &vsval_module);
}


/* Locate our server configuration record for the specified server. */
static VSVAL_CfgServer *our_sconfig(server_rec *s) {
  return (VSVAL_CfgServer *) ap_get_module_config(s->module_config, &vsval_module);
}



/*
 Is a directory protected? (bool)
s=server cfg value
d=local directory cfg value 
*/
static int thisDirIsProtected(int s, int d) {
  int r;

  if (s==VSVAL_CFG_UNSET) {
    if (d==VSVAL_CFG_ON || d==VSVAL_CFG_UNSET) {
      r = 1;
    }
    else {
      r = 0;
    }
  }
  else {
    /* server is set */
    if (d==VSVAL_CFG_UNSET) {
      r = (s==VSVAL_CFG_ON);
    }
    else {
      r = (d==VSVAL_CFG_ON);
    }
  }

  return r;
}



/*
 * This routine is used to add a trace of a callback to the list.  We're
 * passed the server record (if available) for the
 * environment to which the callback is supposed to apply, and some text.  We
 * turn this into a textual representation and log it.
 *
 */

static void trace_add(server_rec *s, int level, const char *fmt, ...)
{
  char buf[CVM_LARGE_BUF_MAX];

  va_list ap;
  va_start(ap, fmt);

  (void) vsprintf(buf, fmt, ap);
  va_end(ap);

  umask(0);

  if (s != NULL) {
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|level, s, "%s: %s", APACHE_LOG_DESCRIPTION, buf);
  }
    
}

/**
*  Begin Change : Infosys, 16 Jul 04
*  Methods moved inside generic library.
**/
/*
void vsValSDKLogMessage(void* handle, char *fmt, ...) {
  char buf[CVM_LARGE_BUF_MAX];

  va_list ap;
  va_start(ap, fmt);

  (void) vsprintf(buf, fmt, ap);
  va_end(ap);

  umask(0);

  if (handle != NULL) {
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, (server_rec*)handle, "%s: %s", APACHE_LOG_DESCRIPTION, buf);
  }
}

void vsNullValSDKLogMessage (void* handle, char *fmt, ...) {
  return;
}
*/

/**
*  End Change : Infosys
**/

/*--------------------------------------------------------------------------*/
/* Various command handlers (routines that are called when the              */
/* configuration parser detects a directive declared by our module).        */
/*                                                                          */
/* If a command handler encounters a problem processing the directive, it   */
/* signals this fact by returning a non-NULL pointer to a string            */
/* describing the problem.                                                  */
/*                                                                          */
/* The magic return value DECLINE_CMD is used to deal with directives       */
/* that might be declared by multiple modules.  If the command handler      */
/* returns NULL, the directive was processed; if it returns DECLINE_CMD,    */
/* the next module (if any) that declares the directive is given a chance   */
/* at it.  If it returns any other value, it's treated as the text of an    */
/* error message.                                                           */
/*                                                                          */
/* If an argument was specified in the directive definition                 */
/* (look for "command_rec" below), it's available to the command handler    */
/* via the (void *) info field in the cmd_parms argument passed to the      */
/* handler (cmd->info for the examples below).                              */
/*--------------------------------------------------------------------------*/

/* Allows specific directories to be protected/unprotected. */
/* Should be used in conjunction with ProtectAll. */
static const char *cmd_VSVAL_ProtectDir(cmd_parms *cmd, 
                                        void *mconfig, char *word1) {

  VSVAL_CfgDir *cfgDir = (VSVAL_CfgDir *) mconfig;

  cfgDir->protected = cvmCfgStringIsOn(word1);
  trace_add(cmd->server, APLOG_INFO, "Setting protected directory(%d)", cfgDir->protected);
  return NULL;
}

/* Allows server default to be protected/unprotected. */
/* Can also be used in conjunction with ProtectDir. */
static const char *cmd_VSVAL_ProtectAll(cmd_parms *cmd, 
                                        void *mconfig, char *word1) {

  VSVAL_CfgServer *cfg = (VSVAL_CfgServer *)our_sconfig(cmd->server);

  cfg->protected = cvmCfgStringIsOn(word1);
  trace_add(cmd->server, APLOG_INFO, "Setting ProtectAll(%d)", cfg->protected);
  return NULL;
}

/**
*  Begin Change : Infosys, 16 Jul 04
*  Use generic wrapper to access the Validation SDK.
**/


/* Sets a config option for the server's VSVAL_SDK handle. */
static const char *cmd_VSVAL_SetOpt(cmd_parms *cmd, void *mconfig,
                                    char *word1, char *word2) {

  VSVAL_CfgServer *cfgServer = (VSVAL_CfgServer *) our_sconfig(cmd->server);
  VSVAL_CfgModule *cfg = &gCfgModule;
  char *name, *val;
  char canonicalNameBuf[CVM_LARGE_BUF_MAX];
  char errorBuf[CVM_LARGE_BUF_MAX];
  int status = 0;
  int s;
  /*VSVAL_UserCtx ctx = {0};*/

  name = ap_pstrdup(cmd->pool, word1);
  val  = ap_pstrdup(cmd->pool, word2);

/*
  if (cfgServer->logInfo) {
      ctx.logFn = vsValSDKLogMessage;
      ctx.handle = cmd->server;
  } else {
      ctx.logFn = vsNullValSDKLogMessage;
  }
*/
  /* All configuration parameters are set into the cfgParams structure and then passed
     to the cvm init function
  */

  /*
  Infosys replaced function with the generic wrapper function
  if (VSVAL_MakeCanonicalOptionName(canonicalNameBuf, CVM_LARGE_BUF_MAX, name)==0) {
  */
  if (vs_cvm_genlib_make_canonical_opt_name(canonicalNameBuf, name)==0) {
    /* If an error occurrs, assume it's not log-info or log-security */
    if (strcmp("logfilename", canonicalNameBuf)==0) {
	  cfgParams.logFileName = val;
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfgServer->logInfo);
      return NULL;
    }
    if (strcmp("loginfo", canonicalNameBuf)==0) {
      cfgServer->logInfo = cvmCfgStringIsOn(val);
	  /*Added by infosys*/
	  cfgParams.logInfo = val;
	  /*End addition*/
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfgServer->logInfo);
      return NULL;
    }
    if (strcmp("logsecurity", canonicalNameBuf)==0) {
      cfgServer->logSecurity = cvmCfgStringIsOn(val);
	  /*Added by infosys*/
	  cfgParams.logSecurity = val;
	  /*End addition*/
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfgServer->logSecurity);
      return NULL;
    }

/*  Fix for CR29977 - Begin */
    if (strcmp("checkchain", canonicalNameBuf)==0) {

      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, val);

      if (cvmCfgStringIsOn(val) )
           val = "off";
      else
           val = "on";

      cfgParams.noCheckChain = val;
      return NULL;
    }
    if (strcmp("nocheckchain", canonicalNameBuf)==0) {
      cfgParams.noCheckChain = val;
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, val);
      trace_add(cmd->server, APLOG_INFO, NO_CHECK_CHAIN_USAGE_WARNING);
      return NULL;
    }
/*  Fix for CR29977 - End   */

    if (strcmp("updateseconds", canonicalNameBuf) == 0) {
      s = atoi(val);
      cfg->updateSeconds = s;
  	  /*Added by infosys*/
	  cfgParams.updateSeconds = s;
	  /*End addition*/

      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfg->updateSeconds);
      return NULL;
    }
    if (strcmp("updateminutes", canonicalNameBuf) == 0) {
      s = atoi(val);
      cfg->updateSeconds = s*60;
	  /*Added by infosys*/
	  cfgParams.updateSeconds = s*60;
	  /*End addition*/
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfg->updateSeconds/60);
      return NULL;
    }
    if (strcmp("updatehours", canonicalNameBuf) == 0) {
      s = atoi(val);
      cfg->updateSeconds = s*3600;
	  /*Added by infosys*/
	  cfgParams.updateSeconds = s*3600;
	  /*End addition*/
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfg->updateSeconds/3600);
      return NULL;
    }
    if (strcmp("lockfile", canonicalNameBuf)== 0) {  
      cfg->lockFileName = ap_pstrdup(cmd->pool, val);
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %s", name, cfg->lockFileName);
      return NULL;
    } 
    if (strcmp("sleepthreshold", canonicalNameBuf) == 0) {
      s = atoi(val);
      cfg->sleepThreshold = s;
	  /*Added by infosys*/
	  cfgParams.sleepThreshold = s;
	  /*End addition*/
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, cfg->sleepThreshold);
      return NULL;
    }
    if (strcmp("errorcgi", canonicalNameBuf) == 0) {
      cfgServer->redirectCgi = ap_pstrdup(cmd->pool, val);
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %s", name, cfgServer->redirectCgi);
      return NULL;
    }

    /* for the next three options we just want to track if they have been configured and 
     * fall through 
     */
    if (strcmp("cachedir", canonicalNameBuf) == 0) {
      cfgServer->configuredCacheDir = 1;
    }
    if (strcmp("fileprefix", canonicalNameBuf) == 0) {
      cfgServer->configuredFilePrefix = 1;
    }
    if (strcmp("urlprefix", canonicalNameBuf) == 0) {
      cfgServer->configuredUrlPrefix = 1;
    }
    if (strcmp("ocspurl", canonicalNameBuf) == 0) {
      cfgServer->configuredOCSPUrl = 1;
    }
    
    status = 0;
    if (strcmp("cfgfilename", canonicalNameBuf) == 0) {	
		
		/* val_ptr = ap_pstrdup(cmd->pool, value_buf);*/
		trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %s", name, val);
		if ((cfgServer->configuredFilePrefix == 0) ||
			((cfgServer->configuredUrlPrefix == 0) && (cfgServer->configuredOCSPUrl == 0)) ||
			(cfgServer->configuredCacheDir == 0) ) {
			return ap_psprintf(cmd->temp_pool, "%s: You need to set file-prefix, url-prefix or ocsp-url, and cache-dir, before setting cfg-filename", APACHE_LOG_DESCRIPTION);    
		}
	
		/*status = VSVAL_ReadConfigFile(cfgServer->vs, &ctx, val);*/
		/*Added by infosys*/
		cfgParams.cfgFileName = val;
		/*End addition*/

    } 
    else if (strcmp("ldaptimeout", canonicalNameBuf) == 0) {
      s = atoi(val);
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, val);
      /*status = VSVAL_SetIntOpt(cfgServer->vs, &ctx, "ldap-timeout", s);*/
	  /*Added by infosys*/
	  cfgParams.ldapTimeOut = s;
	  /*End addition*/

    }
    else if (strcmp("defaultldap", canonicalNameBuf) == 0) {
      if ( !cvmCfgStringIsOn(val) ) {
          val = ap_pstrdup(cmd->pool, "");
      }
      trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %d", name, val);
      /*status = VSVAL_SetOpt(cfgServer->vs, &ctx, "default-ldap", val);*/
	  /*Added by infosys*/
	  cfgParams.defaultLdap = val;
	  /*End addition*/
    }

    else {
		trace_add(cmd->server, APLOG_INFO, "Setting Option: %s = %s", name, val);
		/*status = VSVAL_SetOpt(cfgServer->vs, &ctx, name, val);*/
		/*Added by infosys*/
	    if (strcmp("cachedir", canonicalNameBuf) == 0) {
			cfgParams.cacheDir = val;
		}
		if (strcmp("fileprefix", canonicalNameBuf) == 0) {
			cfgParams.filePrefix = val;
		}
		if (strcmp("urlprefix", canonicalNameBuf) == 0) {
			cfgParams.urlPrefix = val;
		}
		if (strcmp("ocspurl", canonicalNameBuf) == 0) {
			cfgParams.ocspUrl = val;
		}
	    /*End addition*/
    }

	/*
	status = vs_cvm_genlib_init(cfgParams);

    if (status) {
      if (VSVAL_ErrorString(cfgServer->vs, errorBuf, CVM_LARGE_BUF_MAX, status, ctx.errorInfo)) {
	  if (vs_cvm_genlib_get_err_str(errorBuf, status)) {
			trace_add(cmd->server, APLOG_ERR, "Error in VSVAL_SetOpt(%s, %s): Code %d",
				name, val, status);
      }
      else {
	trace_add(cmd->server, APLOG_ERR, "Error in VSVAL_SetOpt(%s, %s): %s",
		  name, val, errorBuf);
      }
    }
    if (status && (strcmp("cfg-filename", canonicalNameBuf) == 0)) {
      return ap_psprintf(cmd->temp_pool, "%s: Error in VSVAL_ReadConfigFile(%s): Code %d",
                         APACHE_LOG_DESCRIPTION, word1, status);
    }
   */ 
  }
  
  return NULL;
}

/**
*  End Change : Infosys
**/

/**
*  Begin Change : Infosys, 16 Jul 04
*  Moved inside Generic Wrapper
**/


/* Process that sleeps and periodically re-gets certs/CRLs. */
/*
int vsSleeperChild(void *v, child_info *ci) {
  server_rec *s = (server_rec *) v;
  CVMTIME currentTime = 0;
  int refreshStatus = 0;
  char buf[CVM_LARGE_BUF_MAX];
  VSVAL_CfgModule *cfg = &gCfgModule;
  VSVAL_UserCtx ctx = {0};
  VSVAL_CfgServer *cfgSrv;
*/
  /* Get our server config record. */
/*  cfgSrv = our_sconfig(s);

  if (cfgSrv->logInfo==1) {
		ctx.logFn = vsValSDKLogMessage;
		ctx.handle = s;
  } else {
	  ctx.logFn = vsNullValSDKLogMessage;
  }
*/
  /* Wait a little while before first update in case of process spawning delays */
/*
  sleep(10);
  if (cfg->sleepThreshold==0) {
    cfg->sleepThreshold=60;
  }

  while (1) {
    val_mutex_on(s);
*/
    /* See if we have to update all the CRLs based on timer. */
/*
    cvm_time(&currentTime);
    if ((currentTime + cfg->sleepThreshold) >
        (cfg->lastUpdate + cfg->updateSeconds)) {

      trace_add(s, APLOG_DEBUG, "Refreshing CRLs");
      cfg->lastUpdate = currentTime;
*/
      /* Re-get all CRLs. */
/*
      ctx.errorInfo[0] = '\0';
      if ((refreshStatus = VSVAL_RefreshCertsCRLs(cfgSrv->vs, &ctx, 1))) {        
*/
        /* Also print the last error's cause. */
/*
        if (VSVAL_ErrorString(cfgSrv->vs, buf, CVM_LARGE_BUF_MAX, 
                              refreshStatus, ctx.errorInfo)) {
          ap_log_error(APLOG_MARK, APLOG_WARNING, s, 
                       "%s: Refresh Error: Code %d", APACHE_LOG_DESCRIPTION, refreshStatus);
        }
        else {
          ap_log_error(APLOG_MARK, APLOG_WARNING, s, "%s: Refresh Error: %s", APACHE_LOG_DESCRIPTION, buf);
        }
      }
      else
	trace_add (s, APLOG_INFO, "Successfully Refreshed Certs and CRLs");
    }

    val_mutex_off(s);

    sleep(cfg->sleepThreshold);*/ /* Just sleep a little while (one minute default) *//*
  }
}
*/
/**
*  End Change : Infosys
**/

/**
*  Begin Change : Infosys, 16 Jul 04
*  Moved inside generic wrapper
**/

/*--------------------------------------------------------------------------*/
/* 
 * This function is called during server initialisation.  Any information
 * that needs to be recorded must be in static cells, since there's no
 * configuration record.
 *
 * There is no return value.
 */

static void vsval_server_init(server_rec *s, pool *p) {

  char *note;
  char *sname = s->server_hostname;
  char *lockFileName;
  int status, i, nNumModules;

  lockFileName = gCfgModule.lockFileName ? gCfgModule.lockFileName 
     : VSVAL_LOCKFILE_DEFAULT_NAME;
  val_mutex_init(s, p, lockFileName);


  /*ap_spawn_child(p, vsSleeperChild, s, kill_always, 0, 0, 0);*/
  cfgParams.filterDescription = malloc(100 * sizeof(char));
  strcpy(cfgParams.filterDescription, APACHE_CVM_DESCRIPTION);

  status = vs_cvm_genlib_init(cfgParams);

  if(status) {
	  exit(APEXIT_INIT);
  }
  
  /* Wait a little while before first update in case of process spawning delays */
  sleep(15);

  /* Add trace text for which server we're being called for. */
  sname = (sname != NULL) ? sname : "";
  note = ap_pstrcat(p, "vsval_server_init(", sname, ")", NULL);
  trace_add(s, APLOG_DEBUG, note);
}

/**
*  End Change : Infosys
**/
/* 
 * This function is called during server initialisation when an heavy-weight
 * process (such as a child) is being initialised.  As with the
 * module-initialisation function, any information that needs to be recorded
 * must be in static cells, since there's no configuration record.
 *
 * There is no return value.
 */
static void vsval_child_init(server_rec *s, pool *p) {

  char *note;
  char *sname = s->server_hostname;


  /* Add trace text for which server we're being called for. */
  sname = (sname != NULL) ? sname : "";
  note = ap_pstrcat(p, "vsval_child_init(", sname, ")", NULL);
  trace_add(s, APLOG_DEBUG, note);
}


/* 
 * This function is called when an heavy-weight process (such as a child) is
 * being run down or destroyed.  As with the child-initialisation function,
 * any information that needs to be recorded must be in static cells, since
 * there's no configuration record.
 *
 * There is no return value.
 */

static void vsval_child_exit(server_rec *s, pool *p) {

  char *note;
  char *sname = s->server_hostname;

  /* Add trace text for which server we're being called for. */
  sname = (sname != NULL) ? sname : "";
  note = ap_pstrcat(p, "vsval_child_exit(", sname, ")", NULL);
  trace_add(s, APLOG_DEBUG, note);
  return;
}


/*
 * This function gets called to create up a per-directory configuration
 * record.  This will be called for the "default" server environment, and for
 * each directory for which the parser finds any of our directives applicable.
 * If a directory doesn't have any of our directives involved (i.e., they
 * aren't in the .htaccess file, or a <Location>, <Directory>, or related
 * block), this routine will *not* be called - the configuration for the
 * closest ancestor is used.
 *
 * The return value is a pointer to the created module-specific
 * structure.
 */
static void *vsval_create_dir_config(pool *p, char *dirspec) {

  VSVAL_CfgDir *cfg;
  char *dname = dirspec;

  /* Allocate the space for our record from the pool supplied. */
  cfg = (VSVAL_CfgDir *) ap_pcalloc(p, sizeof(VSVAL_CfgDir));

  /*
   * Now fill in the defaults.  If there are any `parent' configuration
   * records, they'll get merged as part of a separate callback.
   */
  cfg->protected = VSVAL_CFG_UNSET;


  dname = (dname != NULL) ? dname : "nil";
  trace_add(NULL,APLOG_DEBUG,"vsval_create_dir_config(%s)", dname);
  return (void *) cfg;
}


/*
 * This function gets called to merge two per-directory configuration
 * records.  This is typically done to cope with things like .htaccess files
 * or <Location> directives for directories that are beneath one for which a
 * configuration record was already created.  The routine has the
 * responsibility of creating a new record and merging the contents of the
 * other two into it appropriately.  If the module doesn't declare a merge
 * routine, the record for the closest ancestor location (that has one) is
 * used exclusively.
 *
 * The routine MUST NOT modify any of its arguments!
 *
 * The return value is a pointer to the created module-specific structure
 * containing the merged values.
 */
static void *vsval_merge_dir_config(pool *p, void *parent_conf,
                                    void *newloc_conf) {

  VSVAL_CfgDir *merged_config = (VSVAL_CfgDir *) ap_pcalloc(p, sizeof(VSVAL_CfgDir));
  VSVAL_CfgDir *pconf = (VSVAL_CfgDir *) parent_conf;
  VSVAL_CfgDir *nconf = (VSVAL_CfgDir *) newloc_conf;

  if (nconf->protected==VSVAL_CFG_UNSET) {
    merged_config->protected = pconf->protected;
  }
  else {
    merged_config->protected = nconf->protected;
  }

  trace_add(0, APLOG_DEBUG, "merging dirs %d and %d->%d", 
            pconf->protected, nconf->protected,
            merged_config->protected);

  return (void *) merged_config;
}


/*
 * This function gets called to create a per-server configuration
 * record.  It will always be called for the "default" server.
 *
 * The return value is a pointer to the created module-specific
 * structure.
 */
static void *vsval_create_server_config(pool *p, server_rec *s) {

  VSVAL_CfgServer *cfg;
  char *sname = s->server_hostname, *errResult = 0;
  char buf[CVM_LARGE_BUF_MAX];
  /*VSVAL_UserCtx ctx = {0};*/
  int status = 0;
  module* mod;
  char* name;
  char* val;
  int intVal;

#if defined (HPUX)
  VSVAL_HP_DlInit(0, 1);
#endif
/*
  ctx.logFn = vsValSDKLogMessage;
  ctx.handle = s;
*/
  /*
   * As with the vsval_create_dir_config() reoutine, we allocate and fill
   * in an empty record.
   */
  cfg = (VSVAL_CfgServer *) ap_pcalloc(p, sizeof(VSVAL_CfgServer));
  cfg->protected = VSVAL_CFG_UNSET;
  cfg->redirectCgi = 0;
/*
  if ((status = VSVAL_Init(&(cfg->vs), &ctx, VAL_SDK_CURRENT_VERSION))) {

    if (VSVAL_ErrorString(cfg->vs, buf, CVM_LARGE_BUF_MAX, status, ctx.errorInfo)) {
      errResult = ap_psprintf(p, "%s: Error in Server Init: Code %d", APACHE_LOG_DESCRIPTION, status);
    }
    else {
      errResult = ap_psprintf(p, "%s: Error in Server Init: %s", APACHE_LOG_DESCRIPTION, buf);
    }
    trace_add(s, APLOG_EMERG, errResult);
    
    fprintf(stderr, errResult);
	exit(APEXIT_INIT);
    return 0;
  }
*/
  name = ap_pstrdup(p, "default-ldap");
  val = ap_pstrdup(p, "directory.verisign.com");
/*
  if ( status = VSVAL_SetOpt(cfg->vs, &ctx, name, val)) {
    if (VSVAL_ErrorString(cfg->vs, buf, CVM_LARGE_BUF_MAX, status, ctx.errorInfo)) {
      errResult = ap_psprintf(p, "%s: Error in Setting default-ldap: Code %d", APACHE_LOG_DESCRIPTION, status);
    }
    else {
      errResult = ap_psprintf(p, "%s: Error in Setting default-ldap: %s", APACHE_LOG_DESCRIPTION, buf);
    }
    trace_add(s, APLOG_EMERG, errResult);
  }
*/
  cfgParams.defaultLdap = val;

  name = ap_pstrdup(p, "ldap-timeout");
  intVal = CVM_LDAP_TIMEOUT;
/*
  if ( status = VSVAL_SetOpt(cfg->vs, &ctx, name, val)) {
    if (VSVAL_ErrorString(cfg->vs, buf, CVM_LARGE_BUF_MAX, status, ctx.errorInfo)) {
      errResult = ap_psprintf(p, "%s: Error in Setting ldap-timeout: Code %d", APACHE_LOG_DESCRIPTION, status);
    }
    else {
      errResult = ap_psprintf(p, "%s: Error in Setting ldap-timeout: %s", APACHE_LOG_DESCRIPTION, buf);
    }
    trace_add(s, APLOG_EMERG, errResult);
  }
*/
  cfgParams.ldapTimeOut = intVal;

  cfg->configuredUrlPrefix = 0;
  cfg->configuredFilePrefix = 0;
  cfg->configuredCacheDir = 0;
  cfg->redirectCgi = 0;
  sname = (sname != NULL) ? sname : "";
  trace_add(s, APLOG_DEBUG, "vsval_create_server_config(%s)", sname);
  trace_add(s, APLOG_WARNING, "%s starting up!", APACHE_CVM_DESCRIPTION);
  return (void *) cfg;
}


/*
 * This function gets called to merge two per-server configuration
 * records.  This is typically done to cope with things like virtual hosts and
 * the default server configuration  The routine has the responsibility of
 * creating a new record and merging the contents of the other two into it
 * appropriately.  If the module doesn't declare a merge routine, the more
 * specific existing record is used exclusively.
 *
 * The routine MUST NOT modify any of its arguments!
 *
 * The return value is a pointer to the created module-specific structure
 * containing the merged values.
 */
static void *vsval_merge_server_config(pool *p, void *server1_conf,
                                       void *server2_conf) {

  VSVAL_CfgServer *merged_config = (VSVAL_CfgServer *) 
    ap_pcalloc(p, sizeof(VSVAL_CfgServer));
  VSVAL_CfgServer *s1conf = (VSVAL_CfgServer *) server1_conf;
  VSVAL_CfgServer *s2conf = (VSVAL_CfgServer *) server2_conf;

  /* Our inheritance rules are our own */
  merged_config->protected = s2conf->protected;
  /*merged_config->vs = s2conf->vs;*/

  trace_add(0, APLOG_DEBUG, "merging %d and %d->%d", 
            s1conf->protected, s2conf->protected,
            merged_config->protected);

  return (void *) merged_config;
}


/* Sends the html text of a forbidden page. */
static void vsval_send_forbidden_page(request_rec *r, int certStatus, int status){

  char buf[CVM_LARGE_BUF_MAX];
  char errorBuf[CVM_LARGE_BUF_MAX];
  /*VSVAL_UserCtx ctx={0};*/
  VSVAL_CfgServer *cfgSrv;
  char *errResult=0;

  cfgSrv = our_sconfig(r->server);
  /*
   * Now send our actual output.  Since we tagged this as being
   * "text/html", we need to embed any HTML.
   */
  trace_add (r->server, APLOG_DEBUG, "vsval_send_forbidden_page");
  /*
  if (cfgSrv->redirectCgi) {
    sprintf(buf, "%d", certStatus);
    ap_rputs(DOCTYPE_HTML_3_2, r);
    ap_rputs("<HTML>\n", r);
    ap_rputs("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=", r);
    ap_rputs(cfgSrv->redirectCgi, r);
    ap_rputs("?", r);
    ap_rputs(buf, r);
    ap_rputs("\">", r);
    ap_rputs("</HTML>\n", r);
  }
  else {
  */
    ap_rputs(DOCTYPE_HTML_3_2, r);
    ap_rputs("<HTML>\n", r);
    ap_rputs(" <HEAD>\n", r);
    ap_rputs("  <TITLE>\n", r);
    if (status == 0) {
      ap_rputs("Certificate ", r);
      /*ap_rputs(VSVAL_CertStatusString(cfgSrv->vs, certStatus), r);*/
	  ap_rputs(vs_cvm_genlib_get_cs_str(certStatus), r);
    }
    else {
      ap_rputs("Forbidden", r);
    }      
    ap_rputs("\n", r);
    ap_rputs("  </TITLE>\n", r);
    ap_rputs(" </HEAD>\n", r);
    ap_rputs(" <BODY>\n", r);
	if (cfgSrv->redirectCgi) {
                sprintf(buf, "%d", certStatus);
		ap_rputs("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=", r);
		ap_rputs(cfgSrv->redirectCgi, r);
		ap_rputs("?", r);
		ap_rputs(buf, r);
		ap_rputs("\">", r);
	}
    ap_rputs("  <H2>\n", r);
    ap_rputs("Access Denied\n", r);
    ap_rputs("  </H2>\n", r);
    ap_rputs("We could not authenticate you based on the certificate that you selected.\n",r);
    ap_rputs("<BR>Please verify that you are using the correct certificate and try again. \n",r);
    ap_rputs("<P>If the problem persists please contact the site administrator. \n",r);
    ap_rputs("<P><B>",r);
    if (status == 0) {
      ap_rputs("Error:  Certificate ", r);
      /*ap_rputs(VSVAL_CertStatusString(cfgSrv->vs, certStatus), r);*/
	  ap_rputs(vs_cvm_genlib_get_cs_str(certStatus), r);
    } else {
      ap_rputs("Error: ", r);
      /*if ((cfgSrv==0) || (VSVAL_ErrorString(cfgSrv->vs, errorBuf, CVM_LARGE_BUF_MAX, status, ctx.errorInfo)!=0)) {*/
	  if ((cfgSrv==0) || (vs_cvm_genlib_get_err_str(errorBuf, status)!=0)) {
	errResult = ap_psprintf(r->pool, "Error Code: %d", status);	 
      }
      else {
	errResult = ap_psprintf(r->pool, "%s (%d)", errorBuf, status);
      } 
      ap_rputs(errResult, r);
    }
    ap_rputs("  </B>\n", r);
    ap_rputs("  <P>\n", r);
    ap_rputs(" </BODY>\n", r);
    ap_rputs("</HTML>\n", r);
/*
  }
*/
}



/*
 * This routine is called to perform any module-specific fixing of header
 * fields, et cetera.  It is invoked just before any content-handler.
 *
 * The return value is OK, DECLINED, or HTTP_mumble.  If we return OK, the
 * server will still call any remaining modules with an handler for this
 * phase.
 */
/* Here's where we do the cvm work, as this is where the certificate is available. */
static int vsval_fixer_upper(request_rec *r) {

  VSVAL_CfgDir *cfgDir;
  VSVAL_CfgServer *cfgSrv;
  const char *b64Cert = 0;
  char *userName = 0, *errResult = 0;
  char buf[CVM_LARGE_BUF_MAX];
  int status = 0, certStatus = 0, refreshStatus=0, isProtected;
  int locked = 0, rc = DECLINED;
  /*VSVAL_UserCtx ctx={0};*/
  CVMTIME currentTime = 0;
  VSVAL_CfgModule *cfg = &gCfgModule;

  do {

    trace_add(r->server, APLOG_DEBUG, "vsval_fixer_upper");

    cfgDir = our_dconfig(r);
    cfgSrv = our_sconfig(r->server);

    if (cfgDir==0 || cfgSrv==0) {
      status = VSVAL_ERR_OBJ_CONF; /* should be ERR_APACHE_CONF */
      break;
    }

    /* If this is not a protected directory, just bail out */
    isProtected = thisDirIsProtected(cfgSrv->protected, cfgDir->protected);
    if (! isProtected) {
      trace_add(r->server, APLOG_DEBUG, "%s not protected, bail!", r->uri);
      break;
    } else {
      trace_add(r->server, APLOG_DEBUG, "%s PROTECTED, checking auth certificate!", r->uri);
	}

    /* Setup our user context for error handling */
	/*
    ctx.errorInfo[0] = '\0';
    ctx.logFn = cfgSrv->logInfo ? vsValSDKLogMessage : vsNullValSDKLogMessage;
    ctx.handle = (void *) r->server;    
	*/


    /* Get the SSL cert from the mod_ssl environment */
    b64Cert = ap_table_get(r->subprocess_env, "ssl_client_cert");

    trace_add(r->server, APLOG_DEBUG, "vsval_fixer_upper: %s cert", 
              b64Cert ? "got" : "did NOT get" );

    if (b64Cert==0) {
      status = VSVAL_ERR_NO_AUTH_CERT; /* No cert */
      break;
    }

	if (strlen(b64Cert)==0) {
      status = VSVAL_ERR_NO_AUTH_CERT; /* No cert */
      break;
    }

    if (val_mutex_on(r->server)<0) {
      trace_add(r->server, APLOG_EMERG, "EMERGENCY error getting mutex");
      status = -2;
      break;
    }
    locked = 1; /* Not an actual lock, just tells us to release it later. */
/*
    cvm_time(&currentTime);
    trace_add(r->server, APLOG_DEBUG, "currenttime - %d, lastUpdate - %d, updateSeconds - %d", currentTime, cfg->lastUpdate, cfg->updateSeconds);
    if ((currentTime + cfg->sleepThreshold) > 
        (cfg->lastUpdate + cfg->updateSeconds)) {
      trace_add(r->server, APLOG_DEBUG, "vsval_fixer_upper: Refreshing CRLs");
      cfg->lastUpdate = currentTime;
*/
      /* Re-get all CRLs. */
/*
      if ((refreshStatus = VSVAL_RefreshCertsCRLs(cfgSrv->vs, &ctx, 1))) {        
*/
        /* Also print the last error's cause. */
/*
		  if (VSVAL_ErrorString(cfgSrv->vs, buf, CVM_LARGE_BUF_MAX, 
                              refreshStatus, ctx.errorInfo)) {
          ap_log_error(APLOG_MARK, APLOG_WARNING, r->server, 
                       "%s: Refresh Error: Code %d", APACHE_LOG_DESCRIPTION, refreshStatus);
        }
        else {
          ap_log_error(APLOG_MARK, APLOG_WARNING, r->server, "%s: Refresh Error: %s", APACHE_LOG_DESCRIPTION, buf);
        }
      }
      else
	trace_add (r->server, APLOG_DEBUG, "Successfully Refreshed Certs and CRLs");
    }
*/
  /* Check the revocation status. */
/*
    if ((status = VSVAL_GetRevocationStatusB64(cfgSrv->vs, &ctx, (char *) b64Cert, 
                                               &certStatus, &userName))) {
      break;
    }
*/
	status = vs_cvm_genlib_validate((unsigned char *)b64Cert, -1, &certStatus, userName, cf);
    if (certStatus!=CS_VALID) {

      /* Log the access denied message, if requested. */
      if (cfgSrv->logSecurity) {
        trace_add(r->server, APLOG_ERR, "Certificate %s for %s",
                  /*VSVAL_CertStatusString(cfgSrv->vs, certStatus), */
	  	  vs_cvm_genlib_get_cs_str(certStatus),
                  userName ? userName : "user");
      }

      /* Send a forbidden results page. */
      r->content_type = "text/html";
      ap_soft_timeout("vsval forbidden page", r);
      r->status = HTTP_FORBIDDEN;
      ap_send_http_header(r);
      /* If we're only sending header info (HEAD request), we're already done. */
      if (r->header_only) {
        ap_kill_timeout(r);
        rc = DONE;
        break;
      }

      /* Send the html text. */
      trace_add (r->server, APLOG_DEBUG, "calling vsval_send_forbidden_page");
      vsval_send_forbidden_page(r, certStatus, status);
      trace_add (r->server, APLOG_DEBUG, "after vsval_send_forbidden_page");

      /* We're all done, so cancel the timeout and tell the server we're done. */
      ap_kill_timeout(r);
      rc = DONE;
    }
    else {
      /* for a cert that's valid, act like we weren't even called. */
      rc = DECLINED;
    }
      
  } while (0);

  /* Get rid of the mutex if we acquired it. */
  if (locked) {
    val_mutex_off(r->server);
  }
  

  /* If we got an error, log it. */
  if (status) {
    /* Send a forbidden results page. */
    r->content_type = "text/html";
    ap_soft_timeout("vsval forbidden page", r);
    r->status = HTTP_FORBIDDEN;
    ap_send_http_header(r);
    /* If we're only sending header info (HEAD request), we're already done. */
    if (!r->header_only) {
      /* Send the html text. 
      vsval_send_forbidden_page(r, 0, status);*/
    }
    ap_kill_timeout(r);
    rc = DONE;
    
    if (cfgSrv) {
      /*if (VSVAL_ErrorString(cfgSrv->vs, buf, CVM_LARGE_BUF_MAX,*/
		if (vs_cvm_genlib_get_err_str(buf, status)) {
        errResult = ap_psprintf(r->pool, "%s: Error in VSVAL_GetStatus: Code %d", APACHE_LOG_DESCRIPTION, status);
      }
      else {
        errResult = ap_psprintf(r->pool, "%s: Error in VSVAL_GetStatus: %s", APACHE_LOG_DESCRIPTION, buf);
      }
      if (errResult) {
        trace_add(r->server, APLOG_ERR, errResult);
      }
    }
  }
  
  /* cleanup */
  /*VSVAL_Free(cfgSrv->vs, userName);*/
  
  return rc;
}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/* All of the routines have been declared now.  Here's the list of          */
/* directives specific to our module, and information about where they      */
/* may appear and how the command parser should pass them to us for         */
/* processing.  Note that care must be taken to ensure that there are NO    */
/* collisions of directive names between modules.                           */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/* 
 * List of directives specific to our module.
 */
static const command_rec vsval_cmds[] =
{
  /* Directory config */
    {
        "VSVAL_ProtectDir",              /* directive name */
        cmd_VSVAL_ProtectDir,            /* config action routine */
        NULL,                   /* argument to include in call */
        OR_AUTHCFG,             /* where available */
        TAKE1,                /* arguments */
        "VSVAL_ProtectDir on|off" /* directive description */
    },
    {
        "VSVAL_ProtectAll",              /* directive name */
        cmd_VSVAL_ProtectAll,            /* config action routine */
        NULL,                   /* argument to include in call */
        RSRC_CONF,             /* where available */
        TAKE1,                /* arguments */
        "VSVAL_ProtectAll on|off" /* directive description */
    },
    {
        "VSVAL_SetOpt",              /* directive name */
        cmd_VSVAL_SetOpt,            /* config action routine */
        NULL,                   /* argument to include in call */
        RSRC_CONF,             /* where available */
        TAKE2,                /* arguments */
        "VSVAL_SetOpt name value" /* directive description */
    },
    {NULL}
};


/*--------------------------------------------------------------------------*/
/*                                                                          */
/* Finally, the list of callback routines and data structures that          */
/* provide the hooks into our module from the other parts of the server.    */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/* 
 * Module definition for configuration.  If a particular callback is not
 * needed, replace its routine name below with the word NULL.
 *
 * The number in brackets indicates the order in which the routine is called
 * during request processing.  Note that not all routines are necessarily
 * called (such as if a resource doesn't have access restrictions).
 */
module MODULE_VAR_EXPORT vsval_module =
{
    STANDARD_MODULE_STUFF,
    vsval_server_init,               /* module initializer */
    vsval_create_dir_config,  /* per-directory config creator */
    vsval_merge_dir_config,   /* dir config merger */
    vsval_create_server_config,       /* server config creator */
    vsval_merge_server_config,        /* server config merger */
    vsval_cmds,               /* command table */
    NULL,           /* [7] list of handlers */
    NULL,  /* [2] filename-to-URI translation */
    NULL,      /* [5] check/validate user_id */
    NULL,       /* [6] check user_id is valid *here* */
    NULL,     /* [4] check access by host address */
    NULL,       /* [7] MIME type checker/setter */
    vsval_fixer_upper,        /* [8] fixups */
    NULL,             /* [10] logger */
#if MODULE_MAGIC_NUMBER >= 19970103
    NULL,      /* [3] header parser */
#endif
#if MODULE_MAGIC_NUMBER >= 19970719
    vsval_child_init,         /* process initializer */
#endif
#if MODULE_MAGIC_NUMBER >= 19970728
    vsval_child_exit,         /* process exit/cleanup */
#endif
#if MODULE_MAGIC_NUMBER >= 19970902
    NULL   /* [1] post read_request handling */
#endif
};

