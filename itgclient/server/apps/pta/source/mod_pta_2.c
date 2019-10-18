#if    defined (WIN32)
#elif  defined (SOLARIS)
#include <dlfcn.h> /* dlxxxx */
#elif  defined (LINUX)
#include <dlfcn.h> /* dlxxxx */
#elif  defined (HPUX)
#include <dl.h>    /* shl_xxx */
#else  /* Platform specific -D<arch> definition required*/
#error 
#endif

#include <unistd.h>   /* for usleep() */
#include <pthread.h>  /* for threads under Apache (at least for now anyway) */

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#include "http_request.h"
#include "util_script.h"
#include "http_connection.h"

#include "apr_compat.h"
#include "apr_lib.h"
#include "apr_strings.h"


#include <stdio.h>
#include "ssc_hash_sh.h"
#include "escape.h"
#include "time.h"
#include "pta.h"
#undef PEM_STRING_EVP_PKEY
#define PTA_MAX_UPDATE_TIME INT_MAX

#define  m_pthread_mutexattr_t  NULL
#define  m_pthread_attr_t NULL
#define  m_pthread_addr_t NULL
module AP_MODULE_DECLARE_DATA pta_2_module; //Binit: Changed the declaration

#define PTA_MOD_CONFIG_KEY "pta_2_module"

int VSUnwrapCertificate(request_rec *req);
static void PTAShowRequest(request_rec * req, const char *func_name, const char *str);

typedef struct {
  int pta_init_count; /* to keep track of how times we're called */
  int htable_size;
  apr_pool_t *pool;
} ptaModConfigRec;

typedef struct {
  char *option_file;
  int log_info;
  int debug_wait;
  int function_trace;
  sscHashPool *hash_pool;
} ptaSrvInfo;

typedef struct {
  char *handler;
} ptaDirInfo;

/* Macros to get ptrs to PTA config structures from given module config */
#define GET_PTA_SRV_INFO(MOD_CONFIG) ( (ptaSrvInfo *) ap_get_module_config(MOD_CONFIG, &pta_2_module) )
#define GET_PTA_DIR_INFO(MOD_CONFIG) ( (ptaDirInfo *) ap_get_module_config(MOD_CONFIG, &pta_2_module) )

#define VS_FN_NAME_PTA_INIT    "vsPTAInit"
#define VS_FN_NAME_PTA_CHECK   "vsPTACheck"
#define VS_FN_NAME_PTA_SEND    "vsPTASend"
#define VS_FN_NAME_REFRESH "vsRefreshCRLs"
/* PTA Version Info */
static const char *pta_version = "mod_pta/0.8";

#define PTA_PCM_EXISTS     1
#define PTA_PCM_ISREG      2
#define PTA_PCM_ISDIR      4
#define PTA_PCM_ISNONZERO  8
#define PTA_FLAGS_CHECK_FILE (PTA_PCM_EXISTS|PTA_PCM_ISREG|PTA_PCM_ISNONZERO)
typedef unsigned int pta_pathcheck_t;

/* Critical section variable to protect the following globals */
#define VSLOCK "vsLock"
#define VSCVMLOCK "vsCvmLock"
static pthread_mutex_t vsLock;
static pthread_mutex_t vsCvmLock;

#if defined (HPUX)
pthread_t vsThread = {0};
#elif  defined (SOLARIS)
pthread_t vsThread = 0;
#elif  defined (LINUX)
pthread_t vsThread = 0;
#else
#error
#endif 

/* Globals */
/* define this in ptc.c VS_SSC_CONFIG gCfg = { 0 }; */

/* Sets some values used by the info logger */
void vsSetGlobalFn(server_rec *server, request_rec *req, char *fnName)
{
  gCfg.sn = server;
  gCfg.rq = req;
  gCfg.fnName = fnName;
}

void vsSetCvmGlobalFn(server_rec *server, request_rec *req, char *fnName)
{
  gCfg.cvmSn = server;
  gCfg.cvmRq = req;
  gCfg.cvmFnName = fnName;
}

void vsGetGlobalFn(server_rec **server, request_rec **req, char **fnName)
{
  *server = gCfg.sn;
  *req = gCfg.rq;
  *fnName = gCfg.fnName;
}

void vsGetCvmGlobalFn(server_rec **server, request_rec **req, char **fnName)
{
  *server = gCfg.cvmSn;
  *req = gCfg.cvmRq;
  *fnName = gCfg.cvmFnName;
}

/* Pre-declare this fn so we can use a pointer to it. */
int vsApacheApiGetRevocationInfo(ITEM *certItem, int *certStatus,PTATIME *statusExpires, char **userName);

void vsLogError(int level,int lineNo, const char *func, server_rec *server, char *fmt, ...)
{
  char infoBuf[PTA_MAX_LINE_LENGTH];
  va_list ap;
  va_start(ap, fmt);

  (void) vsnprintf(infoBuf, PTA_MAX_LINE_LENGTH, fmt, ap);
  va_end(ap);
  ap_log_error(__FILE__,lineNo,APLOG_NOERRNO|level,1, server, "%s", infoBuf);

  return;
}

/* Find an integer value in a table, if it isn't there, return the default val. */
int vs_table_findint(apr_table_t *tbl, const char *name, int defaultVal)
{
  const char *value = 0;
  int intVal;
  value = apr_table_get(tbl, name);

  if (value) { intVal = atoi(value); }
  else { intVal = defaultVal; }

  return intVal;
}


/* See if a table named attribute is set to on. */
int vs_table_value_ison(apr_table_t *tbl, const char *attr_name)
{
  const char *value = 0;
  value = apr_table_get(tbl, attr_name);
  return ptaCfgStringIsOn(value);
}

/* Gets the value returned from a table, checks for NULL or strlen()==0 */
char *vs_table_findstr(apr_table_t *tbl, const char *attr_name, char **value)
{
  char *val = 0;
  val = (char *) apr_table_get(tbl, attr_name);
  if (val && val[0]) {
    return (*value = val);
  }
  return 0;
}


/* returns true if name==value in table. */
int vs_table_findmatch(apr_table_t *tbl, const char *name, const char *value)
{
  char *tmp = 0;
  if (vs_table_findstr(tbl, name, &tmp)) {
    if (strcmp(tmp, value)==0) return 1;
  }
  return 0;
}


/* similar to table_set, but removes existing values first. */
void vs_table_nvreplace(apr_table_t *tbl, const char *name, const char *value)
{
  ap_table_unset(tbl, name);
  apr_table_set(tbl, name, value);
}


/* compute size of a table entry in format: '{KEY}="{VALUE}"{space}' */
int tbl2strsize(void *data, const char *key, const char *value)
{
  int *size = (int *)(data);
  *size += strlen(key) + 1 + 1 + strlen(value) + 1 + 1; 
  return 1; /* keep going */
}

 
/* concatenate table entry to buffer in format: '{KEY}="{VALUE}"{space}' */
int tbl2strcat(void *data, const char *key, const char *value)
{
  int offset = 0;
  char *buf = (char *)(data);
  /* Ignore spurious fields which just get in the way  of debug output */ 
  if ( strcmp(key, "PERL_CUR_HOOK")==0 ) {
    return 1;
  }
  strcat(buf, key);
  strcat(buf, "=");
  strcat(buf, "\"");
  if ( strcmp(key, "SSL_CLIENT_CERT")==0 || strcmp(key, "vs-pkcs7")==0 ) {
    /* Just show the first and last four bytes */
    strncat(buf, value, 4);
    strcat(buf, " ... ");
    offset = (strlen(value) > 7) ? strlen(value) - 4 : strlen(value);
    strcat(buf, value + offset);
  }
  else {
    strcat(buf, value);
  }
  strcat(buf, "\" ");
  return 1; /* keep going */
}
 

/* The vs_table2str function copies all entries of a specified
   table into a newly allocated string. Each name-value pair in the string
   is separated from its neighbor pair by a space and is in the format
   name="value". pool is used to provide space for the allocation.
*/
char *vs_table2str(const apr_table_t *tbl, apr_pool_t *pool)
{
  int size = 0;
  char *buff;
  /* compute size of needed string buffer (for sum of all table elements) */
  ap_table_do(tbl2strsize, (void *) &size, tbl, NULL);
  /* allocate buffer (plus terminating byte) */
  buff = ap_pcalloc(pool, size + 1);
  /* concatenate 'name="value" ' strings into buffer */
  ap_table_do(tbl2strcat, (void *) buff, tbl, NULL);
  /* Knock off the single trailing space (if any) */
  if (strlen(buff) > 0) {
    buff[strlen(buff) - 1] = '\0';
  }
  return buff;
}

/* Process String configuration items here */
static const char * vsPTA_set_string_config(cmd_parms *parms,void *mconfig, char *arg)
{
  int offset = (int) (long) (parms->info);    /* extract offset of string */
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(parms->server->module_config);
  *(char **) ((char *) pta_srv_info + offset) = arg;
  return NULL;
}

static int vsPTA_util_path_check(unsigned int pcm, const char *path, apr_pool_t *p)
{
    apr_finfo_t finfo;
    if (path == NULL)
        return 0;
    if (pcm & PTA_PCM_EXISTS && apr_stat(&finfo, path, 
                                APR_FINFO_TYPE|APR_FINFO_SIZE, p) != 0)
        return 0;
    if (pcm & PTA_PCM_ISREG && finfo.filetype != APR_REG)
        return 0;
    if (pcm & PTA_PCM_ISDIR && finfo.filetype != APR_DIR)
        return 0;
    if (pcm & PTA_PCM_ISNONZERO && finfo.size <= 0)
        return 0;
    return 1;
}

static const char *vsPTA_cmd_check_file(cmd_parms *parms, const char **file)
{
    const char *filepath = ap_server_root_relative(parms->pool, *file);
    if (!filepath) {
        return apr_pstrcat(parms->pool, parms->cmd->name,
                           ": Invalid file path ", *file, NULL);
    }
    *file = filepath;
    if (vsPTA_util_path_check(PTA_FLAGS_CHECK_FILE, *file, parms->pool)) {
        return NULL;
    }
    return apr_pstrcat(parms->pool, parms->cmd->name,
                       ": file '", *file, 
                       "' does not exist or is empty", NULL);
}

static const char *vsPTA_cmd_check_aidx_max(cmd_parms *parms, const char *arg)
{
    ptaSrvInfo *sc = GET_PTA_SRV_INFO(parms->server->module_config);
    const char *err; 
    if ((err = vsPTA_cmd_check_file(parms, &arg))) {
        return err;
    }
    sc->option_file = arg;
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, "vsPTA_cmd_check_aidx_max", NULL, "Value of sc->option_file = %s", sc->option_file);
#endif
    return NULL;
}

const char *vsPTA_set_file_config(cmd_parms *cmd, void *dcfg, const char *arg)
{
  const char *err;
  if ((err = vsPTA_cmd_check_aidx_max(cmd, arg))) {
    return err;
  }
  return NULL;
}

static const char * vsPTA_set_flag_config(cmd_parms *parms,void *mconfig, int f)
{
  int offset = (int) (long) (parms->info);    /* extract offset of integer */
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(parms->server->module_config);

  *(int *) ((char *) pta_srv_info + offset) = f ? 1 : 0;
  return NULL;
}

void vsLogInfoMessage(void *handle, char *fmt, ...)
{
  server_rec *server = NULL;
  char infoBuf[PTA_MAX_LINE_LENGTH];
  va_list ap;
  va_start(ap, fmt);

  (void) vsnprintf(infoBuf, PTA_MAX_LINE_LENGTH, fmt, ap);
  va_end(ap);

  if ( gCfg.sn ) {
    server = (server_rec *)(gCfg.sn);
  } else if ( gCfg.rq ) {
    server = ((request_rec *)(gCfg.rq))->server;
  } else {
    fprintf(stderr, "vsLogInfoMesage: no usable server pointer!\n");
    fprintf(stderr, "msg:%s\n", infoBuf);
    return;
  }
  vsLogError(APLOG_INFO,__LINE__, gCfg.fnName, server, infoBuf);
  return;
}

/*
** List of status code, status name value pairs
*/
typedef struct {
  int status;
  char *name;
} apache_status_name;

static const apache_status_name apache_status_codes[] =
{
  { OK,           "OK" },
  { DECLINED,     "DECLINED" },
  { HTTP_FORBIDDEN,    "HTTP_FORBIDDEN" },
  { HTTP_INTERNAL_SERVER_ERROR, "HTTP_INTERNAL_SERVER_ERROR" }
};
/*
** Returns name of given Apache Status code
*/
static const char *GetApacheStatusName(int status)
{
  int i;
  const char *name = "UNKNOWN";
  for (i=0; i < (int) (sizeof(apache_status_codes)/sizeof(apache_status_name));
            i++) {
    if ( apache_status_codes[i].status == status ) {
      name = apache_status_codes[i].name;
      break;
    }
  }
  return name;
}
/* Dump a table to the error log (for debug purposes)
*/
void tblDump(apr_pool_t *pool, const apr_table_t *tbl, const char *func_name, 
             const char *tbl_name)
{
  char *pbStr;
  apr_pool_t *sub_pool;
apr_pool_create(&sub_pool,pool);
  pbStr = vs_table2str(tbl, sub_pool);
  vsLogInfoMessage(0, "%s%s=[%s]", func_name, tbl_name, pbStr);
  apr_pool_destroy(sub_pool);
}


void testDump(request_rec *req, const char *str)
{
  ptaDirInfo *dir_info = GET_PTA_DIR_INFO(req->per_dir_config);
  if ( strncmp(req->uri, "/protected/java/", 16)==0 ||
       strncmp(req->uri, "/protected-cgi/java/", 20)==0 ) {
      vsLogInfoMessage(0, "testDump...skipping java stuff");
    return;
  }
  vsLogInfoMessage(0, "========== %s ==========", str);
  vsLogInfoMessage(0,"req->uri=%s", IsNullStr(req->uri) );
  vsLogInfoMessage(0, "req->handler=%s", IsNullStr(req->handler) );
  vsLogInfoMessage(0, "dir_info->handler=%s", dir_info ? 
                   IsNullStr(dir_info->handler) : "NULL dir_info!" );
  vsLogInfoMessage(0, "req->method=%s", IsNullStr(req->method) );
  vsLogInfoMessage(0, "req->content_type=%s", IsNullStr(req->content_type) );
  tblDump(req->pool, req->headers_in, "", "req->headers_in");
  tblDump(req->pool, req->headers_out, "", "req->headers_out");
  tblDump(req->pool, req->notes, "", "req->notes");
  vsLogInfoMessage(0, "========================");
}

/* Take a line of name="value" options, and parse it into name and value.
 * Reads from line_buf into name, value_buf.
 * Note: All buffers must already be allocated.
 */
int vsGetNameValue(char *line_buf, char *name_buf, char *value_buf)
{
  int status = 0;
  int quoted = 0;
  char *p, *q;
  do {
    name_buf[0] = value_buf[0] = '\0';
     /* Algorithm:
     * 1. skip space
     * 2. read until space, or '='
     * 3. skip space, '=', or '"'
     * 4. read until space, or '"' (if we got one earlier).
     */

    /* 1. */
    p = line_buf;
    while(*p && apr_isspace(*p)) { p++; }

    /* 2. */
    q = name_buf;
    while(*p && !(apr_isspace(*p) || *p=='=')) { *q = *p; q++; p++; }
    *q = '\0';

    /* 3. */
    while(*p && (apr_isspace(*p) || *p=='=' || (*p=='\"' && quoted==0))) {
      if (*p=='\"') quoted = 1;
      p++; 
    }
    if (*p=='\0') {
      status = -1;
      break;
    }

    /* 4. */
    q = value_buf;
    while(*p && ((quoted && *p!='\"') || 
                 (!quoted && !(apr_isspace(*p) || *p=='\r' || *p=='\n'))))
      { *q = *p; q++; p++; }

    *q = '\0';
  } while(0);
  return status;
}

/* Get the next non-comment, non-blank line from the file.
 * Not using one in val.dll since we can't pass a FILE pointer across dlls.
 */
char *nsscGetNextLine(char *lineBuf, int maxLen, FILE *fp)
{
  char *rc = 0;
  int comment = 0;
  char tmpBuf[PTA_MAX_LINE_LENGTH];
  do {
    rc = fgets(lineBuf, maxLen, fp);
    if (lineBuf[0]=='#' || (sscanf(lineBuf, "%s", tmpBuf) <= 0)) comment = 1;
    else comment = 0;
  } while (rc && comment);
  return rc;
}

/* Read a file of name=value options and place them all in a table. */
int vsAddOptionsToTable(char *optionFile, apr_table_t *tbl)
{
  int status = 0;
  FILE *fp = 0;
  char line_buf[PTA_MAX_LINE_LENGTH];
  char name_buf[PTA_MAX_LINE_LENGTH], value_buf[PTA_MAX_LINE_LENGTH];
  char *read_status;
  do {

    if (!(fp = fopen(optionFile, "r"))) {
      status = VSVAL_ERR_CONFIG_OPEN;
      break;
    }

    /* Read the config file */
    do {
      if ( (read_status = nsscGetNextLine(line_buf, PTA_MAX_LINE_LENGTH, fp)) ) {
        if (vsGetNameValue(line_buf, name_buf, value_buf)!=0) {
          status = -1;
          break;
        }
        vs_table_nvreplace(tbl, name_buf, value_buf);
      }
    } while (read_status != 0 && status==0);
  } while (0);
  if (fp) fclose(fp);
  return status;
}


/* pass it cookieVal in hasc. */
int setCookie(apr_table_t *tbl, char *cookieVal, int delete)
{
  char cookie_str[PTA_LARGE_BUF_MAX];
  vsPTAGetCookieHeader(cookie_str, cookieVal, delete);
  apr_table_set(tbl, "set-cookie", cookie_str); /* nsapi: pblock_nvinsert(..., rq->srvhdrs) */
  return 0;
}


/* Builds table of cookies from incoming header's "Cookie" item. */
apr_table_t *get_cookie_table(request_rec *req)
{
  const char *data = apr_table_get(req->headers_in, "cookie");
  apr_table_t *cookies;
  const char* pair;
  if (!data)
      return NULL;
  cookies = ap_make_table(req->pool, 4);
  while (*data && (pair = ap_getword(req->pool, &data, ';'))) {
    const char *name, *value;
    if ( apr_isspace(*data) ) ++data;
    name = ap_getword(req->pool, &pair, '=');
    while (*pair && (value = ap_getword(req->pool, &pair, '&'))) {
      ap_unescape_url((char *)value);
      ap_table_add(cookies, name, value);
    }
  }
#ifdef DEBUGMSG
  tblDump(req->pool, cookies, "get_cookie_table:", "cookies");
#endif
  return cookies;
}


/* 0 if ok (does not mean we found it)
 * value (or null) in *cookieVal. *cookieVal can't be freed.
 */
int findMyCookie(request_rec *req, char **cookieVal)
{
  int status = 0;
  apr_table_t *cookieTbl = 0;
  char *s;
  do {
    *cookieVal = 0;
    cookieTbl = get_cookie_table(req);
    if (cookieTbl) {
      if (vs_table_findstr(cookieTbl, gCfg.cookieName, &s)) {
#ifdef DEBUGMSG
        gCfg.InfoLog(0, "%s=%s", gCfg.cookieName, s);
#endif
        *cookieVal = ap_pstrdup(req->pool, s);
      }
    }
  } while (0);
  if (cookieTbl) { ap_clear_table(cookieTbl); }
  return status;
}

void printCookies(request_rec *req)
{
  apr_table_t *cookie_table = get_cookie_table(req);
#ifdef DEBUGMSG
  if (cookie_table){
    tblDump(req->pool, cookie_table, "printCookies:", "cookies");
  }
  else {
    gCfg.InfoLog(0, "No cookies");
  }
#endif
}


void* vsSleeperThread(void *ptr)
{
  PTATIME currentTime = 0;
  server_rec *oldSN = 0;
  request_rec *oldRQ = 0;
  char *oldFnName = 0;
  int refreshStatus = 0;
  char *refreshStatusString = 0;
  char buf[PTA_LARGE_BUF_MAX];
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = gCfg.InfoLog;
  while (1) {

    pthread_mutex_lock(&vsCvmLock); /* acquire the critical section lock */
    /* Remember the existing error logging info. */
    vsGetCvmGlobalFn(&oldSN, &oldRQ, &oldFnName);
    vsSetCvmGlobalFn(0, 0, VS_FN_NAME_REFRESH);
    /* See if we have to update all the CRLs based on timer. */
    pta_time(&currentTime);
    if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {
      gCfg.cvmLastUpdate = currentTime;
      /* Re-get all CRLs. */
      if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
         /* Ignore errors, but print an error message. */
         vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_REFRESH, oldRQ->server, 
                  "Problems acquiring CRLs. Some not installed.");
		 /* Also print the last error's cause. */
		 if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
			   sprintf (buf, "Error Code : %d", refreshStatus);
		 }
	     vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_REFRESH, oldRQ->server, buf);
      }
      vsLogInfoMessage(0, "Successfully Refreshed Certs and CRLs");
    }
    /* Put the old error logging info back. */
    vsSetCvmGlobalFn(oldSN, oldRQ, oldFnName);
    /* release the lock */
    pthread_mutex_unlock(&vsCvmLock);
    /* Make sure the sleep is outside the critical section!
     * Sleep 1/3 update time (in ms.)
     */
    usleep(gCfg.cvmUpdateSeconds * 334);    /* nsapi: systhread_sleep() */
  }
}

/* Construct a debugging HTML page showing various request_req items */
void PTAFuncUri(request_rec * req, const char *func_name)
{
  const char *content_type = req->content_type;
  ap_set_content_type(req,"text/html");
  if(req->header_only){
     return ;
  }
  ap_rputs("<HTML>\n", req);
  ap_rputs("<HEAD>\n", req);
  ap_rprintf(req, "<TITLE>%s [%s]</TITLE>\n", func_name, req->uri);
  ap_rputs("</HEAD>\n", req);
  ap_rputs("<BODY>\n", req);
  ap_rprintf(req, "Successfully executed the %s!<P>\n", func_name);
  ap_rputs("<P>\n", req);
  ap_rprintf(req, "handler:%s<P>\n", req->handler);
  ap_rprintf(req, "content-type:%s<P>\n", content_type);
  ap_rprintf(req, "URI:%s<P>\n", req->uri);
  ap_rprintf(req, "unparsed URI:%s\n", req->unparsed_uri);
  ap_rputs("</BODY>\n", req);
  ap_rputs("</HTML>\n", req);
  return ;
}

#define PTA_FUNC_TRACE(SERVER, STR) PTAFuncTrace(SERVER, STR, __FILE__, __LINE__)
void PTAFuncTrace(const server_rec *server, const char *s, const char *srcfile, int lineno)
{
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(server->module_config);

  if ( pta_srv_info->function_trace ) {
    ap_log_error(srcfile, lineno, APLOG_INFO|APLOG_NOERRNO, server, "%s", s);
  }
}

int vsSetGETUrl(char *url, request_rec *r)
{
  char *buf;
  int bufsize = 4 + strlen(url) + 1 + strlen(r->protocol) + 1;
  buf = ap_palloc(r->pool, bufsize);
  ap_snprintf(buf, sizeof(buf), "GET %s %s", url, r->protocol);
  r->uri = url;
  r->method = "GET";
  /* NSW: should content-length be unset in headers_out instead??? */
  ap_table_unset(r->headers_in, "content-length");  /* nsapi: rq->headers */
  /* note: cannot set content-type with ap_table_* routines. */
  r->content_type = "";
  vs_table_nvreplace(r->headers_in, "clf-request", buf);
  return 0;
}

/* sscHash_malloc()'s into outPKCS7, sscT_malloc()'s into outITEMs */
int vsGetPostedData(char **outPKCS7, ITEM *outDigest, ITEM *outCert, 
                    request_rec *req)
{
  int status = 0, tmpStatus;
  char *lenStr;
  const char *method;
  int freeBytes = 0, toRead;
  char *b64Str, *typeStr;
  ITEM b64Item = {0}, postedItem = {0};
  long read_count;
  char buffer[HUGE_STRING_LEN];
  VSVAL_UserCtx ctx = {0};
  char *hascData;
  int algorithm;
  ctx.logFn = gCfg.InfoLog;
  do {
    method = req->method;
    if (method==0 || strcmp(method, "POST")!=0) {
      status = -1;
      break;
    }
    if (!(lenStr = (char *) apr_table_get(req->headers_in, "content-length")) ||
       (lenStr==0) || (strlen(lenStr)==0)) {
      status = -2;
      break;
    }
    if ( !(typeStr = (char *) apr_table_get(req->headers_in, "content-type")) ) {
      typeStr = "";
    }
    toRead = atoi(lenStr);
    if (toRead<0) {
      status = -3;
      break;
    }
    if ( (status = ap_setup_client_block(req, REQUEST_CHUNKED_ERROR) ) ) {
      break;
    }
    if ( !ap_should_client_block(req) ) {
      status = -4;
      break;
    }
    b64Item.data = sscT_malloc(PTA_LARGE_BUF_MAX + toRead);
    if (b64Item.data==0) {
      status = VS_ERR_NO_MEM;
      break;
    }
    freeBytes = PTA_LARGE_BUF_MAX + toRead;
    while (toRead > 0) {

      read_count = ap_get_client_block(req, buffer,
         toRead < (int) sizeof(buffer) ? toRead : sizeof(buffer));
      if (read_count == -1 || read_count == 0) break;
      else toRead -= read_count;
      /* append buffer */
      if (freeBytes <= read_count + 2) {  /* save room for a \n, NULL. */
        freeBytes += 5;
        b64Item.data = sscT_realloc(b64Item.data, b64Item.len + freeBytes);
        if (b64Item.data==0) {
          status = VS_ERR_NO_MEM;
          break;
        }
      }
      memcpy(&b64Item.data[b64Item.len], buffer, read_count);
      b64Item.len += read_count;
      freeBytes -= read_count;
    }
    /* We always have a buffer allocated, even if it's empty. */
    if (b64Item.data) { /* Unless realloc fails. */
      b64Item.data[b64Item.len] = '\0';
    }

  } while (0);
  if (status) return status;
#ifdef DEBUGMSG
  gCfg.InfoLog(0, "read=%d bytes", b64Item.len);
#endif

  /* This will modify our string in place into something that can be
   * deBase64'ed.
   */
  vsPTAParsePost(&b64Str, (char *) b64Item.data, typeStr);
  
  /* For debugging, can read the b64(pkcs7) from here 
   * vsFileRead("/tmp/sha_stuff/a", &tmpItem);
   */

#ifdef DEBUGMSG
  /***  gCfg.InfoLog(0, "b64Item=[%*s]", b64Item.len, b64Item.data);  ***/
#endif
  /* alloc a copy of the base64-encoded pkcs7 that was posted. For CGIs.  */
  if (outPKCS7) {
    *outPKCS7 = sscHash_strdup(b64Str); /* old:  T_strdup() */
  }
  
  tmpStatus = VSVAL_DeBase64Alloc(gCfg.vsValSDK, &ctx, &postedItem.data, (int*)&postedItem.len, b64Str);

#ifdef DEBUGMSG
  gCfg.InfoLog(0, "debase=%d", tmpStatus);
  gCfg.InfoLog(0, "debase len = %d", postedItem.len);
#endif

  /* Free this data since we'll return the debase64'ed data. */
  sscT_free(b64Item.data);

  outDigest->data = sscT_malloc(VSVAL_HASH_MAX_LEN);
  status = VSVAL_ParseDetachedPKCS7(gCfg.vsValSDK, &ctx, postedItem.data, postedItem.len, 
                                 outDigest->data, (int*)&outDigest->len, &algorithm,
                                 &outCert->data, (int*)&outCert->len, (int*)0);


#ifdef DEBUGMSG
  hascData = (char*)sscT_malloc(2*outDigest->len+1);
  gCfg.InfoLog(0, "ParseDetachedPKCS7 st=0x%x = %d", status, status);
  if (hascData) {
/* the following function is commented out for now Bin ZOU
	debugDumpCertItem(gCfg.vsValSDK, &internalCtx, outCert); 
*/
	VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,outDigest->data, outDigest->len, hascData);
	gCfg.InfoLog(0, "hasc(outDigest)=%s", hascData);
	sscT_free((POINTER)hascData);
  }
#endif
  sscT_free(postedItem.data);
  return status;
}

static int include_virtual_uri(request_rec *req, char *uri, int do_headers)
{
  int status;
  request_rec *sub_req = ap_sub_req_lookup_uri(uri, req,NULL);

  /* assbackwards indicates whether or not to generate HTML headers
   * 0=yes, 1=no
   */
  sub_req->assbackwards = do_headers ? 0 : 1;

  status = ap_run_sub_req(sub_req);
  ap_destroy_sub_req(sub_req);
  return status;
}


int PTASendValid(request_rec *req)
{
  int rc = 0, temp =0;
  char buf[PTA_LARGE_BUF_MAX], *postUrl = NULL;
  char * buf1 = NULL;
  apr_pool_t *mypool = NULL;

  /* Send a valid url */
  PTA_FUNC_TRACE(req->server, "PTASendValid");
  do {
    /* A GOOD url. */
    postUrl = (char *) apr_table_get(req->headers_in, "validPost");
#ifdef DEBUGMSG
vsLogError(APLOG_INFO,__LINE__, "PTASendValid", req->server, "postUrl = %s",postUrl);
#endif
    if ( postUrl ) {
      /* If we came from /vsadmin/post, send a redirect page to their url. */
	  ap_set_content_type(req,"text/html");
      if (vsPTAGetRedirectPage(buf, postUrl)) {
        gCfg.InfoLog(0, "get redirect page");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }
      if ( ap_rwrite(buf, strlen(buf), req) < 0 ) {
        gCfg.InfoLog(0, "net write1");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }
      /*  Only do this handler.
       *  Don't run any others since we've just sent the page.
       */
      rc = OK;  /* nsapi: REQ_PROCEED */
      break;
    }
    else {
      /* else we got a cookie authentication. Continue. */

      /* REMOVE LATER */
      if( !ap_is_initial_req(req) ) {  /* nsapi: sn->client */
        /* uh-oh, shouldn't ever be here.  We only restart urls that fail. */
        gCfg.InfoLog(0, "abort1");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }

      apr_pool_create(&mypool, req->pool);
      temp = vsPTARenderPage(&buf1, mypool,req->filename);

      if( temp ){
        gCfg.InfoLog(0, "get redirect page");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }
      if ( ap_rwrite(buf1, strlen(buf1), req) < 0 ) {
        gCfg.InfoLog(0, "net write1");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }

      /* Environment vars for normal page are set up in vsPTACheck(). */
      /* Continue running other matching handlers.
       * Note: using DONE or OK would only do this handler -- not what we want!
       */
      //rc = DECLINED;  /* nsapi: REQ_NOACTION */
      rc = OK;  /* nsapi: REQ_NOACTION */
    }
  } while (0);
  if(mypool)
  {
    apr_pool_destroy(mypool);
    mypool = NULL;
  }
  return rc;
}

int PTASendLogout(request_rec *req)
{
  int rc = 0;
  const char *set_cookie = "";
  /* Send the logout-url. */
  do {
    PTA_FUNC_TRACE(req->server, "PTASendLogout");
    /* If this is not the first time here... */
    if ( !ap_is_initial_req(req) ) {
        /* uh-oh, shouldn't ever be here. */
        gCfg.InfoLog(0, "sendlogout1");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
    }
    /* Setup to use the configured logout-url.
     *   (this shouldn't fail).
     */
    if (vsSetGETUrl(gCfg.logoutUrl, req)) {
      gCfg.InfoLog(0, "set get logout");
      rc = HTTP_INTERNAL_SERVER_ERROR;    /* nsapi: REQ_ABORTED */
      break;
    }

    /* Delete their cookie. */
    setCookie(req->headers_in, "Delete", 1);
    /* No environment vars to setup for logout page. */
    /* and restart the request. */
    vs_table_nvreplace(req->headers_in, "restartRequest", "1");
    /* retrieve the saved set-cookie value (if any) */
    if ( (set_cookie = apr_table_get(req->headers_in, "set-cookie"))!=0 ) {
      apr_table_set(req->headers_out, "set-cookie", set_cookie);
    }
    req->handler = apr_table_get(req->headers_in, "orig-handler");
    ap_set_content_type(req,"text/html");
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "PTASendLogout: req->handler set to '%s'",
                     IsNullStr(req->handler) );
    testDump(req, "PTASendLogout");
#endif
      if(req->header_only){
	return OK;
      }
#ifdef DEBUGMSG
    gCfg.InfoLog(0, "PTASendLogout now calling include_virtual_uri(%s,0)",
                 IsNullStr(req->uri) );
#endif

    /* Continue on to whatever handles the logout url.
     * No javascript vars for logout pages.
     */
    pthread_mutex_unlock(&vsLock); /* release the critical section lock */
    rc = include_virtual_uri(req, req->uri, 0);  /* nsapi: REQ_RESTART */
    pthread_mutex_lock(&vsLock); /* acquire the critical section lock */

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "PTASendLogout back from include_virtual(%s,0) rc=%s",
                 IsNullStr(req->uri), GetApacheStatusName(rc) );
#endif

  } while (0);
  return rc;
}

int PTASendAdmin(request_rec *req)
{
  int rc = 0;
  char *bufPre = "<html><head><title>Admin Operation</title></head>\n"
    "<h2 align=center>Admin Operation Successful</h2><hr>\n";
  char buf[PTA_LARGE_BUF_MAX];
  char *bufEnd = "</body></html>\n";
  char *adminOp = 0;
  VSVAL_UserCtx ctx = {0};
  PTA_FUNC_TRACE(req->server, "PTASendAdmin");
  /* Send the successful admin page. */
  do {
	ap_set_content_type(req,"text/html");
        if(req->header_only)
	  return OK;

    /* Write the page to the client. */
    if (ap_rwrite(bufPre, strlen(bufPre), req) < 0 ) {
      gCfg.InfoLog(0, "admin net write1");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }

    if (vs_table_findstr(req->headers_in, "adminOp", &adminOp)==0) {
      gCfg.InfoLog(0, "Get adminOp");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }

    if (strcmp(adminOp, "reset")==0) {
      sprintf(buf, "Authorization Database Reset");
    }
    else if (strcmp(adminOp, "info")==0) {
      sprintf(buf, "Authorization Database Information");
    }
    else if (strncmp(adminOp, "deny/", 5)==0) {
      sprintf(buf, "Authorization Removed for %s", adminOp + 5);
    }
    else if (strncmp(adminOp, "nodeny/", 7)==0) {
      sprintf(buf, "NO ACTION: %s was not authorized.", adminOp + 7);
    }
    else {
      sprintf(buf, "Unknown Admin Operation.  No action taken.");
    }

    /* Write the page to the client. */
    if (ap_rwrite(buf, strlen(buf), req) < 0 ) {
      gCfg.InfoLog(0, "admin net write2");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    /* Write the page to the client. */
    if (ap_rwrite(bufEnd, strlen(bufEnd), req) < 0 ) {
      gCfg.InfoLog(0, "admin net write3");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    /* Only do this handler.
     * Don't run any others since we've just sent the page.
     */
    rc = OK;  /* nsapi: REQ_PROCEED */
  } while (0);
  return rc;
}

int PTASendLogin(request_rec *req, char *sscStatus)
{
  int rc = 0;
  ITEM hashItem;
  login_page_t oldLoginMS = {0}, oldLoginNS = {0};
  char *buf;
  char hascToSign[PTA_TINY_BUF_MAX], hashOfToSign[PTA_TINY_BUF_MAX];
  unsigned char hashBuf[MAX_DIGEST_LEN];
  client_data_t *clientData;
  PTATIME tm = 0;
  char *browserPreBuf, *browserPostBuf;
  int browserPreLen, browserPostLen;
  char *userAgent = 0, *tmpUrl = 0;
  const char *queryString;
  VSVAL_UserCtx ctx = {0};
  ctx.logFn = gCfg.InfoLog;
  PTA_FUNC_TRACE(req->server, "PTASendLogin");
  do {
    /* REMOVE LATER */
    if( !ap_is_initial_req(req) ) {
      /* uh-oh, shouldn't ever be here.  We only restart urls that fail! */
      gCfg.InfoLog(0, "abort2");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    hashItem.data = hashBuf;
    hashItem.len = 0;
    /* Get a new random piece of data for the client to sign. */
    if (ptaGetValToSign(gCfg.useMD5, hascToSign, hashOfToSign, &hashItem)) {
      gCfg.InfoLog(0, "Get val to sign");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
#ifdef DEBUGMSG
    gCfg.InfoLog(0, "hascToSign=%s", hascToSign);
    gCfg.InfoLog(0, "hashOfToSign=%s", hashOfToSign);
#endif
    /* Over-paranoid? See if there's a duplicate value before inserting. */
    if (sscHashSearch(gCfg.hTableSh, hashItem)) {
      gCfg.InfoLog(0, "Duplicate hash value!");
    }
    /* Put the hash of this in the hash table. (w/ unauthorized bit set.) */
    if ((clientData = sscInitClientData())==0) {
      gCfg.InfoLog(0, "init client data");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    pta_time(&tm);
    clientData->authorized = 0;
    clientData->url = sscHash_strdup(apr_table_get(req->headers_in, "oldUri")); /* old: T_strdup() */
    if (clientData->url==0) {
      gCfg.InfoLog(0, "init client data url malloc");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    /* also handle the query string */
    if ( (queryString = apr_table_get(req->headers_in, "oldQueryString")) ) {
      tmpUrl = clientData->url;
      clientData->url = (char *) sscHash_malloc(strlen(tmpUrl) + strlen(queryString) + 2);  /* old: T_malloc() */
      if (clientData->url) {
        sprintf(clientData->url, "%s?%s", tmpUrl, queryString);
        sscHash_free((unsigned char *) tmpUrl);  /* old: T_free() */
      }
      else {
        clientData->url = tmpUrl; /* use the old one if there's no memory. */
      }
    }
#ifdef DEBUGMSG
    gCfg.InfoLog(0, "olduri=%s", clientData->url);
#endif
    clientData->absolute_timeout = tm + gCfg.absoluteTimeout;
    clientData->inactive_timeout = tm + gCfg.inactiveTimeout;
#ifdef DEBUGMSG
    fprintf(stderr,"gCfg.abs_tmout=%lu gCfg.inac_tmout=%lu\n",
                 gCfg.absoluteTimeout,
                 gCfg.inactiveTimeout);
    fprintf(stderr,"abs_tmout=%lu inac_tmout=%lu\n",
                 clientData->absolute_timeout,
                 clientData->inactive_timeout);
#endif
    sscHashInsert(gCfg.hTableSh, hashItem, clientData);
    /* The login page must be in html. */
    ap_set_content_type(req,"text/html");
    if(req->header_only){
	return OK;
    }
    buf = ap_palloc(req->pool, PTA_LARGE_BUF_MAX);
    if ( buf == 0 ) {
      gCfg.InfoLog(0, "ap_palloc buf for login");
      rc = HTTP_INTERNAL_SERVER_ERROR;
      break;
    }
    /* Get variables: what to sign, etc... */
    if (vsPTAGetJSForLogin(buf, hascToSign, hashOfToSign, sscStatus,
                        gCfg.useMD5 ? "MD5" : "SHA")) {
      gCfg.InfoLog(0, "get js for login");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    /* Reload the login page from disk if we aren't supposed to cache it. */
    if (gCfg.noCacheLogin) {
      /* Save the old one in case there's a problem. */
      oldLoginNS = gCfg.loginValueNS;
      oldLoginMS = gCfg.loginValueMS;

      if (vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueMS = oldLoginMS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginMS);
      }

      if (vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) {
        /* Just use the cached version if there's a problem. */
        gCfg.loginValueNS = oldLoginNS;
      }
      else {
        vsPTAClearLoginVal(&oldLoginNS);
      }
    }
    /* Write the page to the client. */
    userAgent = (char *) apr_table_get(req->headers_in, "user-agent");
    if (userAgent && strstr(userAgent, "MSIE")) {
      /* Microsoft browser page */
      browserPreBuf = (char *) gCfg.loginValueMS.preVars.data;
      browserPreLen = gCfg.loginValueMS.preVars.len;
      browserPostBuf = (char *) gCfg.loginValueMS.postVars.data;
      browserPostLen = gCfg.loginValueMS.postVars.len;
    }
    else {
      /* Netscape (and all others) browser page */
      browserPreBuf = (char *) gCfg.loginValueNS.preVars.data;
      browserPreLen = gCfg.loginValueNS.preVars.len;
      browserPostBuf = (char *) gCfg.loginValueNS.postVars.data;
      browserPostLen = gCfg.loginValueNS.postVars.len;
    }

    /* Part before SSC_VARS */
    if (ap_rwrite(browserPreBuf, browserPreLen, req) < 0 ) {  /* nsapi: net_write(sn->csd, ...) */
      gCfg.InfoLog(0, "net write1");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    if (ap_rwrite(buf, strlen(buf), req) < 0 ) {  /* nsapi: net_write(sn->csd, ...) */
      gCfg.InfoLog(0, "net write2");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    /* Part after SSC_VARS */
    if (ap_rwrite(browserPostBuf, browserPostLen, req) < 0 ) {  /* nsapi: net_write(sn->csd, ...) */
      gCfg.InfoLog(0, "net write3");
      rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }
    rc = OK;  /* nsapi: REQ_PROCEED */
  } while (0);
  return rc;
}

int PTASendError(request_rec *req, char *sscStatus)
{
  int rc = 0;
  char buf[PTA_LARGE_BUF_MAX];
  char *oldUri = 0;
  const char *set_cookie = "";
  PTA_FUNC_TRACE(req->server, "PTASendError");
  do {

    /* If this is not the first time here... */
    if ( !ap_is_initial_req(req) ) {
        /* uh-oh, shouldn't ever be here. */
        gCfg.InfoLog(0, "senderror1");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
    }
    /* Setup to use the configured error-url */
    if (vsSetGETUrl(gCfg.errorUrl, req)) {
      gCfg.InfoLog(0, "setgeturl");
      rc = HTTP_INTERNAL_SERVER_ERROR; /* this shouldn't fail. */  /* nsapi: REQ_ABORTED */
      break;
    }
    /* Delete their cookie.
     * else, when server gets rebooted, no way to stop sending a bad auth.
     */
    setCookie(req->headers_in, "Delete", 1);
    /* retrieve the saved set-cookie value (if any) */
    if ( (set_cookie = apr_table_get(req->headers_in, "set-cookie"))!=0 ) {
      apr_table_set(req->headers_out, "set-cookie", set_cookie);
    }
    /* Setup environment vars for error page. */
    vs_table_nvreplace(req->headers_out, "vs_error", sscStatus);
    if ( (oldUri = (char *) apr_table_get(req->headers_in, "oldUri")) ) {
      /* If oldUri != "", use it. */
      if (oldUri[0]) {
        vs_table_nvreplace(req->headers_out, "vs_url", oldUri);
      }
    }
    /* Add javascript vars for html error pages (if requested). */
    if (gCfg.addErrorJSVars) {
    ap_set_content_type(req,"text/html");
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "PTASendError (using JSVars)");
#endif
      if(req->header_only){
	return OK;
      }
      /* prepend variables: what to sign, etc... */
      if (vsPTAGetJSForError(buf, sscStatus, oldUri ? oldUri : "")) {
        gCfg.InfoLog(0, "add js for error page");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "PTASendError buf=[%s]", buf);
#endif

      if (ap_rwrite(buf, strlen(buf), req) < 0 ) {
        gCfg.InfoLog(0, "net write1 e");
        rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
        break;
      }
    }
    else {
        
      /* If the server thinks the error page is text/plain, force it to html
       */
      if (req->content_type && 
          strcmp(req->content_type, "text/plain")==0) {
         ap_set_content_type(req,"text/html");
      }

#ifdef DEBUGMSG
      gCfg.InfoLog(0,"snark snark %s ", req->content_type);
#endif

      if(req->header_only){
	return OK;
      }
    }

    req->handler = apr_table_get(req->headers_in, "orig-handler");
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "PTASendError: req->handler set to '%s'",
                     IsNullStr(req->handler) );
    testDump(req, "PTASendError");
    gCfg.InfoLog(0, "PTASendError now calling include_virtual_uri(%s,0)",
                 IsNullStr(req->uri) );
#endif
    pthread_mutex_unlock(&vsLock); /* release the critical section lock */
    rc = include_virtual_uri(req, req->uri, 0);  /* nsapi: REQ_RESTART */
    pthread_mutex_lock(&vsLock); /* acquire the critical section lock */

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "PTASendError back from include_virtual(%s,0) rc=%s",
                 IsNullStr(req->uri), GetApacheStatusName(rc) );
#endif


  } while (0);
  return rc;
}
/* This is called by ssc_hash.o (pointed to by gCfg.fnGetRevocationInfo)
 * so we can use the mutex to protect things whenever we need to do a refresh.
 */
int vsApacheApiGetRevocationInfo(ITEM *certItem, int *certStatus,PTATIME *statusExpires, char **userName)
{
  int status = 0, refreshStatus = 0;
  char *refreshStatusString = "";
  /*CERT_OBJ clientCertObj = 0;*/
  PTATIME currentTime;

  server_rec *oldSN, *oldCvmSN;
  request_rec *oldRQ, *oldCvmRQ;
  char *oldFnName, *oldCvmFnName;
  VSVAL_UserCtx ctx = {0};

  char buf[PTA_LARGE_BUF_MAX];

  ctx.logFn = gCfg.InfoLog;
  do {

    /* See if they want us to check CRLs... */
    if (gCfg.noCRLCheck && gCfg.checkOCSP==0) {

      /* If not, just do an expiration time check. */
      /* Does NOT check the entire chain for intermediate CA expiration!!! */

      /* Puts result into certStatus. */
      if ( (status = VSVAL_IsCertExpired(gCfg.vsValSDK, &ctx,
                            certItem->data, certItem->len, certStatus)) ) {
        break;
      }

      *statusExpires = PTA_MAX_UPDATE_TIME;
      *userName = sscT_malloc(PTA_SMALL_BUF_MAX);
      if (*userName!=0)
        VSVAL_CertNamePrintable(gCfg.vsValSDK, &ctx, *userName, PTA_SMALL_BUF_MAX, certItem->data, certItem->len);
      break;
 
    }

    /* Release the SSC lock, get the CVM lock.
     * Remember the existing error logging info.
     */
    vsGetGlobalFn(&oldSN, &oldRQ, &oldFnName);
    pthread_mutex_unlock(&vsLock);
    pthread_mutex_lock(&vsCvmLock);
    vsGetCvmGlobalFn(&oldCvmSN, &oldCvmRQ, &oldCvmFnName);
    vsSetCvmGlobalFn(oldSN, oldRQ, oldFnName);

    /* See if we have to update all the CRLs based on timer. */
    pta_time(&currentTime);
    if (currentTime > (gCfg.cvmLastUpdate + gCfg.cvmUpdateSeconds)) {

      gCfg.cvmLastUpdate = currentTime;

      /* Re-get all CRLs. */
      if (refreshStatus = VSVAL_RefreshCertsCRLs(gCfg.vsValSDK, &ctx, 0)) {
          /* Ignore errors, but print an error message. */
		  vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_REFRESH, oldRQ->server, 
                  "Problems acquiring CRLs. Some not installed.");          
		  /* Also print the last error's cause. */
	      if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
		     sprintf (buf, "Error Code : %d", refreshStatus);
		  }
	      vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_REFRESH, oldRQ->server,buf);
	  }
	}

    /* We'll only count this as an error if *certStatus isn't set.
     * Otherwise, url refresh errors give us an error instead of using
     * a valid crl.
     */
    *certStatus = 0;
	refreshStatus = VSVAL_GetRevocationStatus(gCfg.vsValSDK, &ctx, certItem->data, 
											certItem->len, certStatus, userName);
    if (refreshStatus) {

      if (*certStatus==0) {
        /* Didn't get a cert status. Must return an error. */
        status = refreshStatus;
      }

      /* Log the error for the server admin. (Even if we got a certStatus.) */
	  if (VSVAL_ErrorString(gCfg.vsValSDK, buf, PTA_LARGE_BUF_MAX, refreshStatus, ctx.errorInfo)) {
	     sprintf (buf, "Error Code : %d", buf);
	  }
      vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_REFRESH, oldRQ->server, buf);
    }

    /* Switch the locks back. */
    vsSetCvmGlobalFn(oldCvmSN, oldCvmRQ, oldCvmFnName);
    pthread_mutex_unlock(&vsCvmLock);
    pthread_mutex_lock(&vsLock);
    vsSetGlobalFn(oldSN, oldRQ, oldFnName);

  } while (0); 


#ifdef DEBUGMSG
  gCfg.InfoLog(0, "Revocation cert_status = %d", *certStatus);
#endif

  return status;
}

/* Cleanup function */
static void vsPTACleanup(void *data)
{
  server_rec *server = (server_rec *)data;

  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(server->module_config);

#ifdef DEBUGMSG
    fprintf(stderr, "vsPTACleanup  Begin pid=[%ld]\n", (long) getpid());
    fflush(stderr);
#endif
  sscHashDestroy(pta_srv_info->hash_pool);
  gCfg.hTableSh = 0;
#ifdef DEBUGMSG
    fprintf(stderr, "vsPTACleanup  Done  pid=[%ld]\n", (long) getpid());
    fflush(stderr);
#endif
}

//static ptaModConfigRec *ptaModConfig(server_rec *s)
static ptaModConfig(server_rec *s)
{
  apr_pool_t *pool = s->process->pool;
  ptaModConfigRec *mc;
  void *vmc = NULL;
  apr_pool_userdata_get(&vmc, PTA_MOD_CONFIG_KEY, pool);

  if(vmc){
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, "ptaModConfig", s, "Already initialized!! Leaving from ptaModConfig()");
#endif
    return;
  }
  mc = (ptaModConfigRec *) ap_pcalloc(pool, sizeof(*mc));
  mc->pool = pool;
  mc->pta_init_count = 0;
  mc->htable_size = 12;
  apr_pool_userdata_set(mc, PTA_MOD_CONFIG_KEY, NULL, pool);
  return;
}

static int vsPTAInit(apr_pool_t *pool, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *server)
{
  int status = 0, pluginStatus = 0;
  char *errorString = "";
  char *cookieName = 0;
  char *adminIssuerSerialHasc = 0, *pbStr = 0;
  unsigned int len = 0;
  int volatile x = 0;
  apr_pool_t *sub_pool;
  apr_table_t *tbl;
  ptaSrvInfo *pta_srv_info;
  ptaModConfigRec *mc;
  apr_pool_t *temppool;
  int count_delta = 0;
  int adj_count = 0;

  char *cfg_filename = 0;
  char *file_prefix =  0;
  char *url_prefix =   0;
  char *cache_dir =    0;
  char *intString = 0;
  char *defaultLdap = 0;
  char *httpProxy = 0;
  char *ldapHttpProxy = 0;
  char *ocspUrl = 0;
  int ldapTimeOut = 0;
  char valSDKErrorString[PTA_LARGE_BUF_MAX];
  int error_code;
  int randomBytes=0;
hash_table_t *tmptable = NULL;

  VSVAL_UserCtx ctx = {0};

  temppool = server->process->pool;
  apr_pool_userdata_get(&mc, PTA_MOD_CONFIG_KEY, temppool);

  mc->pta_init_count += 1;

#ifdef DEBUGMSG
  count_delta = (mc->pta_init_count > 2) ? 2 : 0;
  adj_count = mc->pta_init_count - count_delta;

  vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server,
        "vsPTAInit() %d%s %s round pid=[%ld]",
        adj_count,
        (adj_count == 1) ? "st" : 
          (adj_count == 2) ? "nd" :
          (adj_count == 3) ? "rd" : "th",
        (count_delta == 0) ? "init" : "restart",
        (long) getpid());
#endif

  tbl = ap_make_table(pool, 25);
  if (mc->pta_init_count == 1) {
    return OK;
  }

  /* Only do this stuff on the second and subsequent times around) */
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server, "register cleanup func");
#endif
  ap_register_cleanup(pool, server, vsPTACleanup, apr_pool_cleanup_null);
  pta_srv_info = GET_PTA_SRV_INFO(server->module_config);
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server, "Option file name = %s",pta_srv_info->option_file);
#endif

  /* Add our module name and version to the Server's version string */
ap_add_version_component(pool,pta_version);

#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server, "setup hash table");
#endif

  /* Make our hash table. */
  //gCfg.hTableSh = sscHashInit(&pta_srv_info->hash_pool, mc->htable_size);
  tmptable = sscHashInit(&pta_srv_info->hash_pool, mc->htable_size);
  gCfg.hTableSh = tmptable;
  if (gCfg.hTableSh == 0) {
    vsLogError(APLOG_EMERG,__LINE__, VS_FN_NAME_PTA_INIT, server,
        "hash tbl init failed! aborting...");
    exit(APEXIT_INIT);
  }

  /* Since apache uses shl_load( NO_START) our dlinit fn won't be called automatically */
#if defined (HPUX)
	VSVAL_HP_DlInit(0, 1);
#endif

#ifdef DEBUGMSG
  fprintf(stderr, "PTA_LARGE_BUF_MAX  = %d\n", PTA_LARGE_BUF_MAX);
  fprintf(stderr, "PTA_SMALL_BUF_MAX  = %d\n", PTA_SMALL_BUF_MAX);
  fprintf(stderr, "PTA_TINY_BUF_MAX   = %d\n", PTA_TINY_BUF_MAX);
  fprintf(stderr, "PTA_MAX_LINE_LENGTH   = %d\n", PTA_MAX_LINE_LENGTH);
  fprintf(stderr, "MAX_DIGEST_LEN    = %d\n", MAX_DIGEST_LEN);
#endif

vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server, "Calling vsSetGlobalFn");
  vsSetGlobalFn(server, 0, VS_FN_NAME_PTA_INIT);
  do {
    pthread_mutex_init(&vsLock, m_pthread_mutexattr_t); /* Make a critical variable */
    pthread_mutex_init(&vsCvmLock, m_pthread_mutexattr_t); /* Make a critical variable */
    
    /* SETUP THE INFO LOGGER AS THE FIRST THING WE DO!!! */
    if (pta_srv_info->log_info) {
      gCfg.InfoLog = vsLogInfoMessage;
    }
    else {
      gCfg.InfoLog = vsNullLogInfoMessage;
    }
	ctx.logFn = gCfg.InfoLog;

    if (pta_srv_info->debug_wait) x=1;
    while(x);

    /* Read more options from a file. */
    gCfg.optionFile = pta_srv_info->option_file; /* null ok. */
    if (gCfg.optionFile) {
      if (vsAddOptionsToTable(gCfg.optionFile, tbl)) {
        status = VS_ERR_OPTION_FILE;
        break;
      }
    }
#ifdef DEBUGMSG
    tblDump(pool, tbl, "vsPTAInit", "tbl");
#endif

    /* Set up our revocation callback. */
    gCfg.fnGetRevocationInfo = vsApacheApiGetRevocationInfo;


    /* In case they turned on info-logging in the option-file. */
    if (vs_table_value_ison(tbl, "log-info")) gCfg.InfoLog = vsLogInfoMessage;
    else gCfg.InfoLog = vsNullLogInfoMessage;


    if ((status = VSVAL_Init(&gCfg.vsValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
      break;
    }

    gCfg.randomFile = (char*)apr_table_get(tbl, "random-file"); /* null ok. */
    if (gCfg.randomFile != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "random-file", gCfg.randomFile))
		break;

    gCfg.noCRLCheck = vs_table_value_ison(tbl, "no-crl-check");

    // Begin CVM configuration 
    /* Read options from additional config file */
    cfg_filename = (char *) apr_table_get(tbl, "cfg-filename");

    file_prefix = apr_table_get(tbl, "file-prefix");
    if (file_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "file-prefix", file_prefix))
		break;

	url_prefix =  (char*) apr_table_get(tbl, "url-prefix");
    if (url_prefix != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "url-prefix", url_prefix))
		break;

	cache_dir = (char *) apr_table_get(tbl, "cache-dir");
    if (cache_dir != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "cache_dir", cache_dir))
		break;

    
	httpProxy = (char*) apr_table_get(tbl, "http-proxy");
    if (httpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "http-proxy", httpProxy))
		break;

	ldapHttpProxy = (char*) apr_table_get(tbl, "ldap-http-proxy");
    if (ldapHttpProxy != 0)
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ldap-http-proxy", ldapHttpProxy))
		break;


    if (intString = (char*) apr_table_get(tbl, "ldap-timeout")) {
      ldapTimeOut = atoi(intString);
    }
    else {
      ldapTimeOut = PTA_LDAP_TIMEOUT;
    }
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "ldap-timeout", ldapTimeOut))
		break;

    /* Must be done AFTER proxy configuration */
    ocspUrl = (char*) apr_table_get(tbl, "ocsp-url");
	gCfg.checkOCSP = 0;
    if (ocspUrl != 0) {
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "ocsp-url", ocspUrl))
		break;	
	  gCfg.checkOCSP = 1;
	} 

	defaultLdap = (char*) apr_table_get(tbl, "default-ldap");
    if (defaultLdap !=0)
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", defaultLdap);
    else
      status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "default-ldap", "directory.verisign.com");
    if (status != 0)
      break;

    if (vs_table_value_ison(tbl, "no-check-chain")) {
	  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "on");
      gCfg.cvmCheckChain = 0;
    } else {
	  gCfg.cvmCheckChain = 1;
	  status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "no-check-chain", "off");
	}

    if (vs_table_value_ison(tbl, "log-security")) {
      gCfg.cvmLogSecurity = 1;
      gCfg.logSecurity = 1;
    } 

    /* get CRL update frequency. */
    if (intString = (char *) apr_table_get(tbl, "update-seconds")) {
      gCfg.cvmUpdateSeconds = atoi(intString);
    }
    else if (intString = (char *) apr_table_get(tbl, "update-minutes")) {
      gCfg.cvmUpdateSeconds = 60 * atoi(intString);
    }
    else if (intString = (char *) apr_table_get(tbl, "update-hours")) {
      gCfg.cvmUpdateSeconds = 60 * 60 * atoi(intString);
    }
    else {
      gCfg.cvmUpdateSeconds = PTA_MAX_UPDATE_TIME;
    }

	if ( gCfg.cvmUpdateSeconds == 0) {
		status = VS_ERR_INVALID_UPDATE_HOURS;
		break;
	}


    if (!cfg_filename || !file_prefix || !cache_dir || (!url_prefix && !ocspUrl)) {
      status = VSVAL_ERR_OBJ_CONF;
      break;
    }

    /* check params... make sure there's a trailing / */
    if (status = VSVAL_ReadConfigFile(gCfg.vsValSDK, &ctx, cfg_filename)) {
		break;
	}

#ifdef DEBUGMSG
  fprintf(stderr, "mod_pta_2 - done CVM configuration, status - %d", status);
#endif
    // End CVM configuration 

  
/* to be fixed BZOU */
#if defined (SOLARIS)|| (LINUX)//Binit
    /* Start a thread to do the timer-based CRL updates. */
    if ( gCfg.cvmUpdateSeconds < PTA_MAX_UPDATE_TIME ) {
      if ( (error_code = pthread_create(&vsThread, m_pthread_attr_t, vsSleeperThread, m_pthread_addr_t)) ) {
        fprintf(stderr, "Error in creating pthread - %d\n", error_code);
        status = VSVAL_ERR_THREAD;
        break;
      }
    }
#endif

    /* leave shlibName null if not specified. */
    gCfg.shlibName = (char *) apr_table_get(tbl, "shlib-name");
    if (gCfg.shlibName) {
      /* Load the user's authorization plugin. */

#if   defined (WIN32)
      gCfg.dlHandle = LoadLibrary(gCfg.shlibName);
#elif defined (SOLARIS)|| (LINUX)//Binit
      /* Don't do RTLD_LAZY, so we find missing symbols right away. */
      gCfg.dlHandle = dlopen(gCfg.shlibName, RTLD_NOW);
#elif defined (HPUX)
      gCfg.dlHandle = shl_load(gCfg.shlibName, BIND_IMMEDIATE, 0L);
#endif

      if (gCfg.dlHandle==0) {
        status = VS_ERR_SHLIB;
        break;
      }

      /* find the address of function and data objects */
#if   defined (WIN32)
      gCfg.dlInit  = (pFnInit)  GetProcAddress(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) GetProcAddress(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) GetProcAddress(gCfg.dlHandle, "SscFinal");
#elif defined (SOLARIS)|| (LINUX)//Binit
      gCfg.dlInit  = (pFnInit)  dlsym(gCfg.dlHandle, "SscInit");
      gCfg.dlCheck = (pFnCheck) dlsym(gCfg.dlHandle, "SscCheck");
      gCfg.dlFinal = (pFnFinal) dlsym(gCfg.dlHandle, "SscFinal");
#elif defined (HPUX)
      shl_findsym(gCfg.dlHandle, "SscInit",  TYPE_PROCEDURE, &gCfg.dlInit);
      shl_findsym(gCfg.dlHandle, "SscCheck", TYPE_PROCEDURE, &gCfg.dlCheck);
      shl_findsym(gCfg.dlHandle, "SscFinal", TYPE_PROCEDURE, &gCfg.dlFinal);
#endif
    }

    /* MD5 or SHA1? */
    if (vs_table_findmatch(tbl, "digest-alg", "MD5")) { gCfg.useMD5 = 1; }

    /* Leave adminIssuerSerialHasc null if not specified. */
    adminIssuerSerialHasc = (char *) apr_table_get(tbl, "admin-issuer-serial");
    if (adminIssuerSerialHasc) {
      VSVAL_StrToLower(gCfg.vsValSDK, &ctx, adminIssuerSerialHasc); /* same upper/lowercase as bin2hasc. */
      if (VSVAL_Hasc2Bin(gCfg.vsValSDK, &ctx,adminIssuerSerialHasc, gCfg.adminIssuerSerial, &len)) {
        status = VS_ERR_ADMIN_HASC;
        break;
      }
    }

    gCfg.addEnvVars = vs_table_value_ison(tbl, "add-env-vars");
    gCfg.addJSVars = vs_table_value_ison(tbl, "add-js-vars");

    /* note: this may not do what we want. */
    gCfg.addErrorJSVars = vs_table_value_ison(tbl, "add-error-js-vars");


    /* Optional memory saving optimization. Requires login on CRL expiration. */
    gCfg.noSaveCerts = vs_table_value_ison(tbl, "no-save-certs");
    if (gCfg.noSaveCerts && (gCfg.addEnvVars || gCfg.addJSVars)) {
      status = VS_ERR_NO_SAVE_CERTS;
      break;
    }
    gCfg.savePkcs7 = vs_table_value_ison(tbl, "save-pkcs7");
    
    gCfg.protectJavaDirs = vs_table_value_ison(tbl, "protect-java-dirs");

    /* Debugging only !!! */
    gCfg.signText = vs_table_value_ison(tbl, "sign-text");
    gCfg.signCanned = 1;
    gCfg.noSSL = vs_table_value_ison(tbl, "no-ssl");
    /* Set timeouts. */
    gCfg.absoluteTimeout = 
      60 * vs_table_findint(tbl, "absolute-timeout", 60); /* 1 hr. */
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "absolute-timeout", gCfg.absoluteTimeout/60))
		break;
    gCfg.inactiveTimeout = 
      60 * vs_table_findint(tbl, "inactive-timeout", 10); /* 10 min. */

    /* Defaults to 2x absolute timeout. */
    gCfg.garbageTime = 60 *
      vs_table_findint(tbl, "garbage-time", (2 * gCfg.absoluteTimeout) / 60);
	/*set this for sdk */
	if (status = VSVAL_SetIntOpt (gCfg.vsValSDK, &ctx, "garbage-time", gCfg.garbageTime/60))
		break;

    /* login/error pages. */
    if (vs_table_findstr(tbl, "login-page-ms", &(gCfg.loginPageMS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_table_findstr(tbl, "login-page-ns", &(gCfg.loginPageNS))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_table_findstr(tbl, "error-url", &(gCfg.errorUrl))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    if (vs_table_findstr(tbl, "logout-url", &(gCfg.logoutUrl))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }

    /* server-name fqdn. Prevents man-in-the-middle attacks. */
    if (vs_table_findstr(tbl, "server-name", &(gCfg.serverName))==0) {
      status = VS_ERR_MISSING_CONFIG_VAL;
      break;
    }
    else {
      VSVAL_StrToLower(gCfg.vsValSDK, &ctx, gCfg.serverName);
      gCfg.serverNameLen = strlen(gCfg.serverName);
      if (gCfg.serverNameLen >= PTA_SMALL_BUF_MAX) {
        status = VS_ERR_SERVER_NAME;
        break;
      }
      if (status = VSVAL_SetOpt (gCfg.vsValSDK, &ctx, "server-name", gCfg.serverName))
                break;
    }

    gCfg.noCacheLogin = vs_table_value_ison(tbl, "no-cache-login");

    gCfg.noCachePages = vs_table_value_ison(tbl, "no-cache-pages");

    if ( (status = vsPTAReadLoginVal(gCfg.loginPageMS, &(gCfg.loginValueMS))) ) {
      break;
    }
    if ( (status = vsPTAReadLoginVal(gCfg.loginPageNS, &(gCfg.loginValueNS))) ) {
      break;
    }
/*
    if (status = VSVAL_FileRead(gCfg.vsValSDK, &ctx, gCfg.errorPage, &(gCfg.errorPageItem.data), &(gCfg.errorPageItem.len))) {
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO, "vsPTAInit", server, "Reading of error page - status = %d",status);
#endif
      break;
    }
*/

    /* Cookie name/domain. */
    cookieName = (char *) apr_table_get(tbl, "cookie-name");

    if ( (gCfg.cookieName = (char *) sscT_malloc(PTA_LARGE_BUF_MAX))==0 ) {
      status = VS_ERR_NO_MEM;
      break;
    }

    if (cookieName) { strncpy(gCfg.cookieName, cookieName, PTA_LARGE_BUF_MAX); }
    else {

      VSVAL_GenerateRandomBytes (gCfg.vsValSDK, &ctx, &randomBytes, sizeof (int));
      sprintf(gCfg.cookieName, "VeriSignPTA%d", randomBytes);
      
      /* Can't specify cookie-domain w/o a cookie-name.
       * How would all the servers pick the same random id?
       */
      if (apr_table_get(tbl, "cookie-domain")) {
        status = VS_ERR_COOKIE_DOMAIN;
        break;
      }
    }

    /* leave cookieDomain null if not specified. */
    gCfg.cookieDomain = (char *) apr_table_get(tbl, "cookie-domain");

    /* NSAPI inits Hash table here. Apache gets htable size for use later. */
    if (apr_table_get(tbl, "htable-size")) {
      mc->htable_size = atoi(apr_table_get(tbl, "htable-size"));
    }

    /* Call the user init fn */
    if (gCfg.dlInit) {

      /*
       * The pblock_pblock2str function copies all parameters of a specified
       * pblock into a specified string. The function allocates additional
       * non-heap space for the string if needed.
       * Each name-value pair in the string is separated from its neighbor
       * pair by a space and is in the format name="value".
       */
apr_pool_create(&sub_pool,pool);
     // sub_pool = ap_make_sub_pool(pool);
      pbStr = vs_table2str(tbl, sub_pool); /* nsapi: pblock_pblock2str(pb, 0) */
      pluginStatus = (*gCfg.dlInit) (VS_PTA_PLUGIN_DESC, pbStr ? pbStr : "");
      //ap_destroy_pool(sub_pool);  /* nsapi: FREE(pbStr) */
apr_pool_destroy(sub_pool);
      if (pluginStatus) {
        status = VS_ERR_PLUGIN_INIT;
        break;
      }
    }

    /* Print a startup message. */
    gCfg.InfoLog(0, "%s starting", VS_PTA_PLUGIN_DESC);
    vsLogError(APLOG_NOTICE,__LINE__, VS_FN_NAME_PTA_INIT, server, "%s starting", VS_PTA_PLUGIN_DESC);
 
  } while (0);

#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, VS_FN_NAME_PTA_INIT, server,
             "checking final status... value = %d",status);
#endif
  if (status) {
	/* some of the errors might be returned by the validation 
	 * SDK so you need to handle accordingly 
	 */
    
	  if ( status > VS_ERR_BASE && status < VS_ERR_MAX ) {
		sscErrorString(&errorString, status);
	    apr_table_set(tbl, "error", errorString);
		vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_PTA_INIT, server, "%s", errorString);
	  }
	  else
		if (status > VSVAL_ERR_BASE && status < VSVAL_ERR_MAX) {
			VSVAL_ErrorString(gCfg.vsValSDK, valSDKErrorString, VSVAL_BUF_MAX, status, ctx.errorInfo);	
			apr_table_set(tbl, "error", errorString);
			vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_PTA_INIT, server, "%s", valSDKErrorString);
		}
		else {  /* Otherwise errorString is already set. */			
			apr_table_set(tbl, "error", errorString);
			vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_PTA_INIT, server, "%s", errorString);
		}		
    vsLogError(APLOG_ERR,__LINE__, VS_FN_NAME_PTA_INIT, server, "vsPTAInit() Failed!");
  } else {
    vsLogError(APLOG_NOTICE,__LINE__, VS_FN_NAME_PTA_INIT, server, "vsPTAInit() Ok");
  }
  if (status) {
    exit(APEXIT_INIT);  /* nsapi: REQ_ABORTED */
  }
   else 
  {
	return OK;   /* nsapi: REQ_PROCEED */
  }
}

/* Process Per-Directory/Location Creation stuff here */

static void* vsPTA_create_dir_config(apr_pool_t *p, char *path)
{
  ptaDirInfo *dir_info = (ptaDirInfo *) ap_pcalloc(p, sizeof(ptaDirInfo));
  dir_info->handler = NULL;
  return (void *) dir_info;
}

static void* vsPTA_create_srv_config(apr_pool_t *p, server_rec *server)
{
  ptaSrvInfo  *config = ap_pcalloc(p, sizeof(ptaSrvInfo));
  config->option_file = NULL;
  config->log_info = 0;
  config->debug_wait = 0;
  config->hash_pool = 0;
  ptaModConfig(server);
  return (void *) config;
}

/* Fixup handler to set handler to pta-send or let request go through
 * unchanged, depending on whether PTAProtected and value of sscStatus.
 * The original handler is saved so we can restore it to pass along after
 * pta-send does it's work.
 */
int vsPTAFixup(request_rec *req)
{
  char *sscStatus = "";
  ptaDirInfo *dir_info = GET_PTA_DIR_INFO(req->per_dir_config);

  PTA_FUNC_TRACE(req->server, "vsPTAFixup");
  
  if ( !dir_info || !dir_info->handler ) {
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "vsPTAFixup: %s not PTAProtected (ignored)", req->uri);
#endif
    return DECLINED;
  }

  /* If we're here after restarting the request, continue on. */
  if ( !ap_is_initial_req(req) ) {
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "vsPTAFixup: restartRequest is ON");
    /* This message is from send() pass1--> send() pass 2.  Don't remove it. */
    vsLogInfoMessage(0, "returning DECLINED");
#endif
    return DECLINED;  /* nsapi: REQ_PROCEED */
  }

#ifdef DEBUGMSG
  testDump(req, "vsPTAFixup [begin]");
#endif

  /* If there's an sscStatus (other than valid or for admin) present,
   * then we need to force a run of the PTASend handler instead of the
   * default handler.
   * Also, we save the name of the original handler so we can chain to it
   * if necessary after PTASend runs.
   */
  if ( vs_table_findstr(req->headers_in, "sscStatus", &sscStatus) ) {
    if ( strcmp(sscStatus, "valid")==0 &&
         strncmp(req->uri, "/vsadmin/", 9)!=0 ) {
      vsLogInfoMessage(0, "vsPTAFixup: sscStatus valid...letting it through (no-cache)");
      req->no_cache = 1; /* force No Caching for this response */

      apr_table_unset(req->headers_in, "If-Modified-Since"); /* NSW testing! */
      vsLogInfoMessage(0, "returning DECLINED");
//      return DECLINED;   
      return OK;   
    }

#ifdef DEBUGMSG
  vsLogInfoMessage(0, "TEMP req->handler = %s", req->handler);
  vsLogInfoMessage(0, "TEMP dir_info->handler = %s", dir_info->handler);
#endif

    /* It's either a status other than "valid" or it's an /vsadmin request */
    if ( req->handler ) {
      apr_table_set(req->headers_in, "orig-handler", req->handler);
#ifdef DEBUGMSG
      vsLogInfoMessage(0, "vsPTAFixup: req->headers_in->orig-handler set to '%s'", req->handler);
#endif
    }

    req->handler = dir_info->handler;
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "vsPTAFixup: req->handler set to '%s'", req->handler);
#endif
  }

#ifdef DEBUGMSG
  vsLogInfoMessage(0, "returning DECLINED");
#endif
  return DECLINED;
}
//Binit :::: This function maps to x_child_init
static void vsPTAChildInit(apr_pool_t *pool, server_rec *server)
{
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(server->module_config);
#ifdef DEBUGMSG
  vsLogError(APLOG_INFO,__LINE__, "vsPTAChildInit", server, "vsPTAChildInit: pid=[%ld]", (long) getpid());
#endif

  /* Register that we are using the Shared memory hash table */
  sscHashAttach(pta_srv_info->hash_pool);
}

static void vsPTAChildExit(void *data)
{
  server_rec *server = data;
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(server->module_config);

  pthread_mutex_destroy(&vsLock);

#ifdef DEBUGMSG
  fprintf(stderr, "vsPTAChildExit: Begin pid=[%ld]\n", (long) getpid() );
  fflush(stderr);
#endif

  /* Register that we are no longer using the Shared memory hash table */
  //sscHashDetach(pta_srv_info->hash_pool);
  gCfg.hTableSh = 0;

  if (vsThread) { pthread_cancel(vsThread); }

  /* Call the user final fn */
  if (gCfg.dlFinal) { (*gCfg.dlFinal) (); }

  /* Unload the user's authorization plugin. */
#if   defined (WIN32)
  if (gCfg.dlHandle) { FreeLibrary(gCfg.dlHandle); }
#elif defined (SOLARIS)||(LINUX)
  if (gCfg.dlHandle) { dlclose(gCfg.dlHandle); }
#elif defined (HPUX)
  if (gCfg.dlHandle) { shl_unload(gCfg.dlHandle); }
#endif

  sscT_free((unsigned char *) gCfg.cookieName);

  vsPTAClearLoginVal(& gCfg.loginValueMS);
  vsPTAClearLoginVal(& gCfg.loginValueNS);

  VSVAL_Final(gCfg.vsValSDK);

  /*vsValCleanup(0);*/ /* clean up CVM. */
  pthread_mutex_destroy(&vsCvmLock);

#ifdef DEBUGMSG
  fprintf(stderr, "vsPTAChildExit: Done  pid=[%ld]\n", (long) getpid() );
  fflush(stderr);
#endif

}

/* Response handler for sending the login page, redirect to error, etc... */
int vsPTASend(request_rec *req)
{
  int rc;
  char *sscStatus = "";
  int sendNoCache = 1; /* default to true. Remove for regular pages. */
ptaDirInfo *dir_info = GET_PTA_DIR_INFO(req->per_dir_config);
  PTA_FUNC_TRACE(req->server, "vsPTASend");
  
#ifdef DEBUGMSG
    testDump(req, "vsPTASend [begin]");
#endif

#ifdef DEBUGMSG
   req->handler = dir_info->handler;
#endif

  pthread_mutex_lock(&vsLock); /* acquire the critical section lock */

  do {

    vsSetGlobalFn(req->server, req, VS_FN_NAME_PTA_SEND);

    if (vs_table_findstr(req->headers_in, "sscStatus", &sscStatus)==0) {
      gCfg.InfoLog(0, "Error sscStatus = [%s]", sscStatus);
   vsLogError(APLOG_INFO,__LINE__, "vsPTASend", NULL, "Error - Value of scStatus = %s", sscStatus);
      sscStatus = "nullSend";
      rc = OK;
    //  rc = HTTP_INTERNAL_SERVER_ERROR;  /* nsapi: REQ_ABORTED */
      break;
    }

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "sscStatus = %s", sscStatus);
#endif

    if(strcmp(sscStatus, "valid")==0) {

      /* Send a valid url. */
      rc = PTASendValid(req);

    if(! rc)
    {
    }

      /* By default (configurable) we allow normal content to be cached
       * by the browser.
       */
      if (!gCfg.noCachePages) { sendNoCache = 0; }
    }
    else {

      if(strcmp(sscStatus, "login")==0 ||
         strcmp(sscStatus, "expired")==0) {

        /* Send the login page. */
        rc = PTASendLogin(req, sscStatus);

      }
      else if(strcmp(sscStatus, "logout")==0) {
        /* Remove the client cookie and authentication from the hash table. */
        rc = PTASendLogout(req);
      }
      else if(strcmp(sscStatus, "admin")==0) {
        /* Send a page indicating the admin operation was successful. */
        rc = PTASendAdmin(req);
      }
      else {
        /* Send an error page. */
        rc = PTASendError(req,sscStatus);
      }

    }

  } while (0);


  /* Tell the client not to cache any pages. Otherwise on second logout, the
   * client will just show the local page and not send a logout to the server.
   */
  if (sendNoCache) {
    vs_table_nvreplace(req->headers_out, "Pragma", "no-cache");
    /* Some time in the past. */
    vs_table_nvreplace(req->headers_out, "Expires", "Tue, 30 Mar 1999 11:54:01 GMT");
  }

  /* release the lock */
  pthread_mutex_unlock(&vsLock);

#ifdef DEBUGMSG
  testDump(req, "vsPTASend [end]");
#endif
  /* Restore original request handler so it gets run next (if need be) */
  req->handler = apr_table_get(req->headers_in, "orig-handler");
#ifdef DEBUGMSG
  vsLogInfoMessage(0, "vsPTASend: req->handler reset to '%s'",
                   IsNullStr(req->handler) );
#endif

#ifdef DEBUGMSG
  vsLogInfoMessage(0, "vsPTASend: returning %s", GetApacheStatusName(rc));
#endif
  return rc;
}

static int vsPTATestHandler(request_rec *req)
{
  PTA_FUNC_TRACE(req->server, "PTATestHandler");
  PTAFuncUri(req, "PTATestHandler");
  return OK;
}

static int vsPTADumpHashTable(request_rec *req)
{
  sscPrintHashTable(gCfg.hTableSh);
  PTAShowRequest(req, "vsPTADumpHashTable", "Hash Table dumped to log");
  return OK;
}

static int vsPTAResetHashTable(request_rec *req)
{
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(req->server->module_config);

  //gCfg.hTableSh = sscHashReset(pta_srv_info->hash_pool);
  PTAShowRequest(req, "vsPTAResetHashTable", "Hash Table reset");
  sscPrintHashTable(gCfg.hTableSh);
  return OK;
}

int vsAddValidEnvVars(request_rec *req,client_data_t *clientData)
{
  ITEM b64Cert = {0};
  int tmpStatus;
  ITEM pkcs7Item = {0};

  VSVAL_UserCtx ctx={0};
  ctx.logFn = gCfg.InfoLog;
  /* Set auth-user, etc... */
  apr_table_set(req->subprocess_env, "auth-type", "strong"); /* nsapi: rq->vars */

  if (clientData) {

    if (clientData->userName) {
      apr_table_set(req->subprocess_env, "auth-user", clientData->userName);
    }
    
    if (clientData->pkcs7) {
     /* before save the data, remove end of line*/
      pkcs7Item.data = (unsigned char*)clientData->pkcs7;
      pkcs7Item.len = strlen(clientData->pkcs7)+1;
      removeEOL(&pkcs7Item);
      vs_table_nvreplace(req->headers_in, "vs-pkcs7", pkcs7Item.data); /* nsapi: rq->headers */

      if (!gCfg.savePkcs7) {
        sscHash_free((unsigned char *) clientData->pkcs7); /* old: sscT_free() */
        clientData->pkcs7 = 0;
      }
    }
    if (clientData->cert.data &&
        (VSVAL_Base64Alloc(gCfg.vsValSDK, &ctx, &b64Cert.data, clientData->cert.data, clientData->cert.len)==0)) {
      b64Cert.len=strlen((char*)b64Cert.data)+1;
      removeEOL(&b64Cert);      
      apr_table_set(req->subprocess_env, "SSL_CLIENT_CERT", (char *) b64Cert.data); /* auth-cert */
      sscT_free(b64Cert.data);
    }

    tmpStatus = VSUnwrapCertificate(req);

#ifdef DEBUGMSG
    gCfg.InfoLog(0, "unwrap = %d", tmpStatus);
#endif
  }

  return 0;
}
/* Main entry for certificate verification. */
int vsPTACheck(request_rec *req) /* nsapi: NSAPI_PUBLIC */
{

  int status = 0;
  int rc = HTTP_FORBIDDEN;  /* nsapi: REQ_ABORTED */
  char *errorString = "", *newUrl;
  client_data_t *clientData;
  char *uri, *unparsed_uri, *cookieVal, *hascKey=0, *outPKCS7;
  char *queryString = 0;
  char *adminOp = 0, *denyHasc;
  unsigned char *tmpData;
  ITEM outDigest = {0}, outCert = {0};
  int certStatus = 0;
  char *adminOpBuf;

  VSVAL_UserCtx ctx = {0};

  ptaDirInfo *dir_info = GET_PTA_DIR_INFO(req->per_dir_config);
  ptaSrvInfo *pta_srv_info = GET_PTA_SRV_INFO(req->server->module_config);

  PTA_FUNC_TRACE(req->server, "vsPTACheck");

  if ( !dir_info || !dir_info->handler ) {
    /* NSW: may need/want additional sanity checks here */
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "vsPTACheck: %s not PTAProtected (ignored)",
                     IsNullStr(req->uri) );
#endif
    return DECLINED;
  }
//Added by VM/Mahesh during porting to apache2.0
  if(NULL == req->handler)
     req->handler = dir_info->handler;

  /* struct timeval tp; for performance timing. */

  pthread_mutex_lock(&vsLock); /* acquire the critical section lock */
  vsSetGlobalFn(req->server, req, VS_FN_NAME_PTA_CHECK);

#ifdef DEBUGMSG
  testDump(req, "vsPTACheck [begin]");
#endif
  /* If we're here after restarting the request, continue on. */
  if ( !ap_is_initial_req(req) ) {
#ifdef DEBUGMSG
    vsLogInfoMessage(0, "vsPTACheck: restartRequest is ON");
#endif
    /* This message is from send() pass1--> send() pass 2.  Don't remove it. */

    /* release the lock and proceed */
    pthread_mutex_unlock(&vsLock);

#ifdef DEBUGMSG
    vsLogInfoMessage(0, "returning DECLINED");
#endif
    return DECLINED;  /* nsapi: REQ_PROCEED */
  }

  do {

    /* changed to include unparsed_uri for later use */
    if ( ((unparsed_uri = req->unparsed_uri) == 0) || (*unparsed_uri == '\0')||
                ((uri = req->uri) == 0) || (*uri == '\0') ) {
      status = VS_ERR_NO_URI;
      break;
    }

#ifdef DEBUGMSG
    /* printCookies(req); */
#endif

    if (gCfg.protectJavaDirs==0 && strstr(uri, "/java/")) {
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "skipping java uri=%s", uri);
#endif
      pthread_mutex_unlock(&vsLock);
#ifdef DEBUGMSG
      vsLogInfoMessage(0, "vsPTACheck: returning DECLINED");
#endif
      return DECLINED;  /* nsapi: REQ_PROCEED */
    }

    clientData = 0;
    cookieVal = newUrl = 0;

    /* We will use cookieVal to know if we are actually sending a page.
     * To get a page, the user must be presenting a cookie,
     * vsadmin/post sets it and does a redirect.
     */

    /* First, examine the cookie presented. */
    if ((findMyCookie(req, &cookieVal)==0) && cookieVal) {
      
      /* See if the cookie holds a good authentication. */
      certStatus = sscAuthorizeCookie(gCfg.hTableSh, cookieVal, &clientData);
      /* We probably won't use the url in this link since we'll only redirect
       * to this url if they try to go to vsadmin/post incorrectly.
       */

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "found cookie, certStatus=%d", certStatus);
#endif
    }
    else {
#ifdef DEBUGMSG
      gCfg.InfoLog(0, "no cookie presented");
#endif
    }

    if (strncmp(uri, "/vsadmin/", 9)==0) {
      if (certStatus==CS_VALID) {
        /* already authenticated, but requesting a special url */
        /* if requesting /vsadmin/post, why? */
        if (strcmp(uri, "/vsadmin/post")==0) {
          /* send them to the originally requested url. */
          newUrl = clientData->url; /* This clientData from the cookie auth. */
        }
        else {
          /* See if they're the admin, and then handle their request. */
          if (gCfg.adminIssuerSerial && cookieVal &&
              vsPTAIsAdmin(gCfg.adminIssuerSerial, clientData->iSDigest)) {

            if (strcmp(uri, "/vsadmin/reset")==0) {
              gCfg.hTableSh = sscHashReset(pta_srv_info->hash_pool);
              adminOp = "reset";
            }
            else if (strcmp(uri, "/vsadmin/info")==0) {
              adminOp = "info";
            }
            else if (strncmp(uri, "/vsadmin/deny/", 14)==0) {

#ifdef DEBUGMSG
              sscPrintHashTable(gCfg.hTableSh);
#endif

              denyHasc = uri + 14;
#ifdef DEBUGMSG
              gCfg.InfoLog(0, "Delete %s", denyHasc);
#endif
              adminOpBuf = ap_palloc(req->pool, PTA_LARGE_BUF_MAX);
              if (sscHashDeleteISDigest(gCfg.hTableSh, denyHasc)) {
                ap_snprintf(adminOpBuf,PTA_LARGE_BUF_MAX, "deny/%s", denyHasc);
                adminOp = adminOpBuf;
              }
              else {
                ap_snprintf(adminOpBuf,PTA_LARGE_BUF_MAX, "nodeny/%s", denyHasc);
                adminOp = adminOpBuf;
              }

#ifdef DEBUGMSG
              sscPrintHashTable(gCfg.hTableSh);
#endif

            }
          }
          else {
            certStatus = CS_SSC_BAD_ADMIN;
          }
        }
      }
      else {
        /* They didn't present a cookie, or they didn't present a valid
         * cookie -- either way we must authenticate them.
         * This tells later code we used a post to authenticate, not the cookie.
         */
        cookieVal = 0;
        if (strcmp(uri, "/vsadmin/post")==0) {
          /* Allocs memory */
          outPKCS7 = 0;
          if ( (status = vsGetPostedData(&outPKCS7, &outDigest,
                                         &outCert, req)) ) {
#ifdef DEBUGMSG
            gCfg.InfoLog(0, "get=0x%x = %d", status, status);
#endif

            /* In this case we can't save these in the hash table in
             * authorizePost. Free them now.
             */
            sscT_free((unsigned char *) outPKCS7);
            sscT_free((unsigned char *) (outCert.data));

            break;
          }

          /* dup the return value since it's a static buffer. */
          hascKey = (char*)sscT_malloc(outDigest.len*2+1);
		  if (hascKey) {
			  VSVAL_Bin2Hasc (gCfg.vsValSDK, &ctx,outDigest.data, outDigest.len, hascKey);
		  } else {
            /* In this case we can't save these in the hash table in
             * authorizePost. Free them now.
             */
            sscT_free((unsigned char *) outPKCS7);
            sscT_free((unsigned char *) (outCert.data));
            
            status = VS_ERR_NO_MEM;
            break;
          }

#ifdef DEBUGMSG
          gCfg.InfoLog(0, "hascKey=%s", hascKey);
#endif

          /* Now move the Digest and Cert data to shared memory */
          tmpData = (unsigned char *) outDigest.data;
          outDigest.data = sscHash_malloc(outDigest.len);
          memcpy(outDigest.data, tmpData, outDigest.len);
          sscT_free(tmpData);
          tmpData = (unsigned char *) outCert.data;
          outCert.data = sscHash_malloc(outCert.len);
          memcpy(outCert.data, tmpData, outCert.len);
          sscT_free(tmpData);
          if (outDigest.data==0 || outCert.data==0) {
            status = VS_ERR_NO_MEM;
            break;
          }

          /* See if the post holds a good authentication. */
          clientData = 0;
          certStatus = sscAuthorizePost(gCfg.hTableSh, outDigest,
                                       &outCert, outPKCS7, &clientData);

#ifdef DEBUGMSG
      gCfg.InfoLog(0, "sscAuthorizePost() --> certStatus=%d [%s]",
                   certStatus, vsPTACertStatusString(certStatus));
#endif
          if (certStatus==CS_VALID) {
            setCookie(req->headers_out, hascKey, 0);
            newUrl = clientData->url;
          }
          else if (clientData) {
            /* There's an error or expiration, don't redirect to vsadmin/post.
             * Use the original url (this clobbers uri for anyone later).
             */
            uri = clientData->url;
            newUrl = clientData->url;
#ifdef DEBUGMSG
            gCfg.InfoLog(0, "sscAuthorizePost() failed (has clientData)! uri=%s",
                         IsNullStr(uri) );
#endif
          }
          else {
            /* Doesn't work for bad sigs since we stored the url in the 
             * hash table along with the good signature. Can't find it
             * given only the bad hash.
             */
            uri = 0;
            /* Send them to "/".
             * Only needed/used by user plugins that change a bad
             * (!CS_VALID) status to CS_VALID. We must send them somewhere.
             */
            newUrl = "/";
#ifdef DEBUGMSG
            gCfg.InfoLog(0, "sscAuthorizePost() failed! newUrl='%s'", newUrl);
#endif
          }

          sscHash_free(outDigest.data); /* old: sscT_free() */
          /* sscHash_free(outCert.data); This is saved in the hash table --
           * don't free it.
           */
        }
        else {
          /* no access to special urls w/o authentication.
           * Must send login page.
           */
        }
      }
    }
    else if ( (NULL != gCfg.logoutUrl) && (strcmp(uri, gCfg.logoutUrl)==0)) {
      
#ifdef DEBUGMSG
  fprintf(stderr, "vsPTACheck: uri==logoutUrl pid=[%ld]\n", (long) getpid());
#endif

      if (certStatus==CS_VALID || certStatus==CS_SSC_COOKIE_EXPIRED) {

#ifdef DEBUGMSG
  fprintf(stderr, "  calling sscHashDeleteHasc(%s)\n", cookieVal);
#endif
        /* If they are expired, it's better to show them the logout page
         * than error. Log out the user by removing the authentication
         * from the hash table.
         */
        sscHashDeleteHasc(gCfg.hTableSh, cookieVal);

        certStatus = CS_SSC_LOGOUT;
      }
    }

  } while (0);

  if (status) {

    /* Log Errors */
    sscErrorString(&errorString, status);

    /* Log denials? */
    if (gCfg.logSecurity && certStatus) {
      vsLogError(APLOG_NOTICE,__LINE__, VS_FN_NAME_PTA_CHECK, req->server, 
                "Certificate %s for %s", vsPTACertStatusString(certStatus), 
                vsPTAGetUserName(clientData));
    }

    /* And set up to send an error page later. */
    vs_table_nvreplace(req->headers_in, "sscStatus", errorString);
    rc = DECLINED;  /* nsapi: REQ_PROCEED */
  }
  else {

    /* Call out to user plugin.
     * We don't call the plugin if there's no cookie, and status is VALID.
     * In that case, we set a cookie and the plugin will be called on the
     * redirect.
     */
    if (gCfg.dlCheck && !adminOp && (cookieVal || certStatus != CS_VALID)) {
#ifdef DEBUGMSG
//      gCfg.InfoLog(0, "certStatus=%d, calling user plugin gCfg.dlCheck()",
//                   certStatus );
#endif
      if (clientData) {
        certStatus = gCfg.dlCheck(certStatus, uri, 
                                  clientData->cert.data, clientData->cert.len,
                                  clientData->pkcs7, vsPTAGetUserName(clientData));
      }
      else {
        certStatus = gCfg.dlCheck(certStatus, uri, 0, 0, 0, 0);
      }
      
#ifdef DEBUGMSG
        gCfg.InfoLog(0, "gCfg.dlCheck() --> certStatus=%d", certStatus );
#endif
      /* If they changed !valid to valid, must set a cookie. */
      if (certStatus==CS_VALID && !cookieVal) {
        setCookie(req->headers_out, hascKey, 0);
      }
    }
    if (certStatus==CS_VALID && !adminOp) {
      
      /* Set the real url */
      if (newUrl) { 
#ifdef DEBUGMSG
        gCfg.InfoLog(0, "set real url to %s", newUrl);
#endif
        vs_table_nvreplace(req->headers_in, "validPost", newUrl);
      }

      /* need to set up header vars here since we won't have them in Send(). */
      if (cookieVal && gCfg.addEnvVars) {
        vsAddValidEnvVars(req, clientData);
      }

      vs_table_nvreplace(req->headers_in, "sscStatus", "valid");
      /* Not changing uri value.  Just continue. */
//      rc = DECLINED;  /* nsapi: REQ_PROCEED */
 rc = OK;     
    }
    else if (certStatus==CS_VALID && adminOp) {
      vs_table_nvreplace(req->headers_in, "sscStatus", "admin");
      vs_table_nvreplace(req->headers_in, "adminOp", adminOp);
      /* Not changing uri value.  Just continue. */
      rc = DECLINED;  /* nsapi: REQ_PROCEED */
    }
    else {
      
      /* If they were denied, send the login or error page.
       * which one is determined by the status code.
       */

      /* Log denials if it is not a login request */
      if (gCfg.logSecurity && certStatus != 0) {
        vsLogError(APLOG_NOTICE,__LINE__, VS_FN_NAME_PTA_CHECK, req->server, 
                  "Certificate %s for %s", vsPTACertStatusString(certStatus),
                  vsPTAGetUserName(clientData));
      }
      /* Set the status code for the send handler. */
      vs_table_nvreplace(req->headers_in, "oldUri", unparsed_uri ? unparsed_uri : "");

      if (vs_table_findstr(req->headers_in, "query", &queryString)) {
        vs_table_nvreplace(req->headers_in, "oldQueryString", queryString);
      }

      if (certStatus==0) {
        vs_table_nvreplace(req->headers_in, "sscStatus", "login");
      }
      else if (certStatus==CS_SSC_COOKIE_EXPIRED ||
               certStatus==CS_SSC_POST_EXPIRED) {
        vs_table_nvreplace(req->headers_in, "sscStatus", "expired");
      }
      else if (certStatus==CS_SSC_LOGOUT) {
        vs_table_nvreplace(req->headers_in, "sscStatus", "logout");
      }
      else {
        vs_table_nvreplace(req->headers_in, "sscStatus", 
                           vsPTACertStatusString(certStatus));
      }

      /* Go on to our handler. */
      rc = DECLINED; /* nsapi: REQ_PROCEED */
    }
  }

  /* performance timing
   * gettimeofday(&tp, 0);
   * gCfg.InfoLog(0, "tp = %d, %d", tp.tv_sec, tp.tv_usec);
   */
  sscT_free((unsigned char *) hascKey);

  /* release the lock */
  pthread_mutex_unlock(&vsLock);

#ifdef DEBUGMSG
  testDump(req, "vsPTACheck [end]");
#endif

#ifdef DEBUGMSG
  vsLogInfoMessage(0, "vsPTACheck: returning %s", GetApacheStatusName(rc) );
#endif
  return rc;
}

static void PTAShowRequest(request_rec * req, const char *func_name, const char *str)
{
  ap_set_content_type(req,"text/html");
  if(req->header_only){
    return ;
  }
  ap_rputs("<HTML>\n", req);
  ap_rputs("<HEAD>\n", req);
  ap_rprintf(req, "<TITLE>%s [%s]</TITLE>\n", func_name, req->uri);
  ap_rputs("</HEAD>\n", req);
  ap_rputs("<BODY>\n", req);
  ap_rprintf(req, "Successfully executed %s()<P>\n", func_name);
  ap_rputs("<P>\n", req);
  ap_rprintf(req, "handler:%s<P>\n", req->handler);
  ap_rprintf(req, "URI:%s<P>\n", req->uri);
  ap_rprintf(req, "pid = [%ld]\n", (long) getpid());
  ap_rprintf(req, "data = [%s]\n", str);
  ap_rputs("</BODY>\n", req);
  ap_rputs("</HTML>\n", req);
}

/* Process PTAProtect configuration directives here */
static const char * vsPTA_cmd_PTAProtect(cmd_parms *parms, void *mconfig)
{
  ptaDirInfo *dir_info = (ptaDirInfo *) mconfig;
  dir_info->handler = "pta-send";

#ifdef DEBUGMSG
   vsLogError(APLOG_INFO,__LINE__, "PTAProtect", parms->server,
           "PTAProtect  path=%s handler=%s\n",
           IsNullStr(parms->path), IsNullStr(dir_info->handler) );
#endif
  return NULL;
}

/*
static int pta_handler(request_rec *r)
{
   ptaDirInfo *dir_info = GET_PTA_DIR_INFO(r->per_dir_config);
#ifdef DEBUGMSG
   vsLogError(APLOG_INFO, "pta_handler", NULL, "Entered into pta_handler");
   vsLogError(APLOG_INFO, "pta_handler", NULL, "Value of dir_info->handler = %s", dir_info->handler);
   vsLogError(APLOG_INFO, "pta_handler", NULL, "Value of r->handler = %s", r->handler);
#endif

   if( !strcmp(r->handler,"pta-send") || !strcmp(dir_info->handler,"pta-send"))
   {
#ifdef DEBUGMSG
   vsLogError(APLOG_INFO, "pta_handler", NULL, "Calling vsPTASend");
#endif
       return vsPTASend(r);
   } else
   {
#ifdef DEBUGMSG
   vsLogError(APLOG_INFO, "pta_handler", NULL, "Returning OK");
#endif
       return OK;
   }
}
*/

static const pta_handlers[] =
{
  {"pta-send",        vsPTASend        },
  {"pta-test",        vsPTATestHandler },
  {"pta-dumphash",    vsPTADumpHashTable },
  {"pta-reset",       vsPTAResetHashTable },
  {NULL}
};


static const command_rec pta_config_cmds[] =
{
  /* Server wide configuration commands */
  AP_INIT_TAKE1( "option_file",
    vsPTA_set_file_config, NULL,
    RSRC_CONF,
    "option_file value"
  ),
  AP_INIT_RAW_ARGS( "log_info",
    vsPTA_set_flag_config,
    RSRC_CONF,
    TAKE1,
    "Flag to enable generation of certain PTA log messages."
  ),
  AP_INIT_RAW_ARGS( "debug_wait",
    vsPTA_set_flag_config,
    RSRC_CONF,
    TAKE1,
    "Flag to enable looping (wait indefinitely) at PTA startup."
  ),
  AP_INIT_RAW_ARGS( "function_trace",
    vsPTA_set_flag_config,
    RSRC_CONF,
    TAKE1,
    "Flag to enable log output within selected PTA functions."
  ),
  AP_INIT_NO_ARGS( "PTAProtect",
    vsPTA_cmd_PTAProtect,
    ACCESS_CONF | OR_AUTHCFG,
    NO_ARGS,
    "Location directive to enable PTA protection there."
  ),
    {NULL}
};
static void vsPTA_register_hooks(apr_pool_t *p)
{
    ap_hook_post_config(vsPTAInit, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_child_init(vsPTAChildInit, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(vsPTASend, NULL, NULL, APR_HOOK_MIDDLE);
/* Other test handlers */
/*    ap_hook_handler(vsPTATestHandler , NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(vsPTADumpHashTable , NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_handler(vsPTAResetHashTable , NULL, NULL, APR_HOOK_MIDDLE);*/
    ap_hook_fixups(vsPTAFixup, NULL, NULL, APR_HOOK_MIDDLE);
    ap_hook_access_checker(vsPTACheck, NULL, NULL, APR_HOOK_MIDDLE);
}


module AP_MODULE_DECLARE_DATA pta_2_module = {
   STANDARD20_MODULE_STUFF,
   vsPTA_create_dir_config,     /* per dir config creator */
   NULL, 		        /* per dir config merger -- default is to override */
   vsPTA_create_srv_config,     /* server config creator */
   NULL, 		        /* server config merger */
   pta_config_cmds,             /* config directive table */
   vsPTA_register_hooks,
};


