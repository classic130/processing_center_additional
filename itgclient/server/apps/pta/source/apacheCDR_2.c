/*
$Revision: 1.1.4.1 $
$Header: /cvsroot/gosecure/itgclient/server/apps/pta/source/Attic/apacheCDR_2.c,v 1.1.4.1 2006/04/13 19:11:02 bagrawala Exp $
*/

#include <stdio.h>
#include <string.h>

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"

#include "vsvalsdk.h"

#ifndef SERVER_ERROR
#define SERVER_ERROR        HTTP_INTERNAL_SERVER_ERROR
#endif

void vsLogError(int level, char *func, server_rec *server, char *fmt, ...);
void sscT_free (void *pointer);

typedef struct {
	int use_ssl_name;
	int use_vs_name;
	int use_compat_name;
} apacheCDR_EnvOptions;

typedef struct {
	char *ssl_name;
	char *vs_name;
	char *compat_name;
} apacheCDR_EnvVar;

static const apacheCDR_EnvVar apacheCDR_EnvVarTable[] =
{
  /* ssl/new name             vs/old name                compat name        */
  /* ------------------------ -------------------------- ------------------ */
  {"SSL_CLIENT_CERT",         "VSCERT_CLIENT_CERT", "SSL_CLIENT_CERTIFICATE"},
  {"SSL_CLIENT_I_DN_O",       "VSCERT_ISSUER_ORGANIZATION", "SSL_CLIENT_IO"},
  {"SSL_CLIENT_I_DN_L",       "VSCERT_ISSUER_LOCALITY",     "SSL_CLIENT_IL"},
  {"SSL_CLIENT_I_DN_C",       "VSCERT_ISSUER_COUNTRY",      "SSL_CLIENT_IC"},
  {"SSL_CLIENT_I_DN_CN",      "VSCERT_ISSUER_CN",           "SSL_CLIENT_ICN"},
  {"SSL_CLIENT_I_DN_OU",      "VSCERT_ISSUER_OU1",          "SSL_CLIENT_IOU"},
  {"SSL_CLIENT_S_DN_Email",   "VSCERT_EMAIL",               "SSL_CLIENT_EMAIL"},
  {"SSL_CLIENT_S_DN_CN",      "VSCERT_CN",                  "SSL_CLIENT_CN"},
  {"SSL_CLIENT_S_DN_O",       "VSCERT_ORGANIZATION",        "SSL_CLIENT_O"},
  {"SSL_CLIENT_S_DN_OU",      "VSCERT_OU1",                 "SSL_CLIENT_OU"},
  {"SSL_CLIENT_V_START",      "VSCERT_NOTBEFORE",      "SSL_CLIENT_CERT_START"},
  {"SSL_CLIENT_V_END",        "VSCERT_NOTAFTER",       "SSL_CLIENT_CERT_END"},
  
  /** extensions ***/

  {"SSL_CLIENT_I_DN_OUCOUNT", "VSCERT_ISSUER_OUCOUNT", "SSL_CLIENT_OUCOUNT"},
  {"SSL_CLIENT_I_DN_OUnn",    "VSCERT_ISSUER_OUnn",    "SSL_CLIENT_OUnn"},
  {"SSL_CLIENT_S_DN_ADDRESS", "VSCERT_ADDRESS",        "SSL_CLIENT_ADDRESS"},
  {"SSL_CLIENT_S_DN_OUCOUNT", "VSCERT_OUCOUNT",        "SSL_CLIENT_OUCOUNT"},
  {"SSL_CLIENT_S_DN_OUnn",    "VSCERT_OUnn",           "SSL_CLIENT_OUnn"},
  {"SSL_CLIENT_S_DN_TITLE",   "VSCERT_TITLE",          "SSL_CLIENT_TITLE"},
  {"SSL_CLIENT_S_DN_UNIQUE",  "VSCERT_UNIQUE",         "SSL_CLIENT_UNIQUE"},

  /** v3 extensions **/
  {"SSL_CLIENT_KEYUSAGE",				"VSCERT_EX_KEYUSAGE",				"SSL_CLIENT_KEYUSAGE"},
  {"SSL_CLIENT_EKU",					"VSCERT_EX_EKU",					"SSL_CLIENT_EKU"},
  {"SSL_CLIENT_SAN_DIRNAMECOUNT",		"VSCERT_EX_SAN_DIRNAMECOUNT",		"SSL_CLIENT_SAN_DIRNAMECOUNT"},
  {"SSL_CLIENT_SAN_DIRNAME",			"VSCERT_EX_SAN_DIRNAME1",			"SSL_CLIENT_SAN_DIRNAME"},
  {"SSL_CLIENT_SAN_DIRNAMEnn",			"VSCERT_EX_SAN_DIRNAMEnn",			"SSL_CLIENT_SAN_DIRNAMEnn"},
  {"SSL_CLIENT_SAN_RFC822COUNT",		"VSCERT_EX_SAN_RFC822COUNT",		"SSL_CLIENT_SAN_RFC822COUNT"},
  {"SSL_CLIENT_SAN_RFC822",				"VSCERT_EX_SAN_RFC8221",			"SSL_CLIENT_SAN_RFC822"},
  {"SSL_CLIENT_SAN_RFC822nn",			"VSCERT_EX_SAN_RFC822nn",			"SSL_CLIENT_SAN_RFC822nn"},
  {"SSL_CLIENT_SAN_DNSNAMECOUNT",		"VSCERT_EX_SAN_DNSNAMECOUNT",		"SSL_CLIENT_SAN_DNSNAMECOUNT"},
  {"SSL_CLIENT_SAN_DNSNAME",			"VSCERT_EX_SAN_DNSNAME1",			"SSL_CLIENT_SAN_DNSNAME"},
  {"SSL_CLIENT_SAN_DNSNAMEnn",			"VSCERT_EX_SAN_DNSNAMEnn",			"SSL_CLIENT_SAN_DNSNAMEnn"},
  {"SSL_CLIENT_SAN_URICOUNT",			"VSCERT_EX_SAN_URICOUNT",			"SSL_CLIENT_SAN_URICOUNT"},
  {"SSL_CLIENT_SAN_URI",				"VSCERT_EX_SAN_URI1",				"SSL_CLIENT_SAN_URI"},
  {"SSL_CLIENT_SAN_URInn",				"VSCERT_EX_SAN_URInn",				"SSL_CLIENT_SAN_URInn"},
  {"SSL_CLIENT_SAN_UPNCOUNT",			"VSCERT_EX_SAN_UPNCOUNT",			"SSL_CLIENT_SAN_UPNCOUNT"},
  {"SSL_CLIENT_SAN_UPN",				"VSCERT_EX_SAN_UPN1",				"SSL_CLIENT_SAN_UPN"},
  {"SSL_CLIENT_SAN_UPNnn",				"VSCERT_EX_SAN_UPNnn",				"SSL_CLIENT_SAN_UPNnn"},
  {"SSL_CLIENT_SAN_GUIDCOUNT",			"VSCERT_EX_SAN_GUIDCOUNT",			"SSL_SAN_GUIDCOUNT"},
  {"SSL_CLIENT_SAN_GUID",				"VSCERT_EX_SAN_GUID1",				"SSL_CLIENT_SAN_GUID"},
  {"SSL_CLIENT_SAN_GUIDnn",				"VSCERT_EX_SAN_GUIDnn",				"SSL_CLIENT_SAN_GUIDnn"},
  {"SSL_CLIENT_CDP_DPN_DIRNAMECOUNT",	"VSCERT_EX_CDP_DPN_DIRNAMECOUNT",	"SSL_CLIENT_CDP_DPN_DIRNAMECOUNT"},
  {"SSL_CLIENT_CDP_DPN_DIRNAME",		"VSCERT_EX_CDP_DPN_DIRNAME1",		"SSL_CLIENT_CDP_DPN_DIRNAME"},
  {"SSL_CLIENT_CDP_DPN_DIRNAMEnn",		"VSCERT_EX_CDP_DPN_DIRNAMEnn",      "SSL_CLIENT_CDP_DPN_DIRNAMEnn"},
  {"SSL_CLIENT_CDP_DPN_RFC822COUNT",	"VSCERT_EX_CDP_DPN_RFC822COUNT",    "SSL_CLIENT_CDP_DPN_RFC822COUNT"},
  {"SSL_CLIENT_CDP_DPN_RFC822",			"VSCERT_EX_CDP_DPN_RFC8221",		"SSL_CLIENT_CDP_DPN_RFC822"},
  {"SSL_CLIENT_CDP_DPN_RFC822nn",		"VSCERT_EX_CDP_DPN_RFC822nn",       "SSL_CLIENT_CDP_DPN_RFC822nn"},
  {"SSL_CLIENT_CDP_DPN_DNSNAMECOUNT",	"VSCERT_EX_CDP_DPN_DNSNAMECOUNT",   "SSL_CLIENT_CDP_DPN_DNSNAMECOUNT"},
  {"SSL_CLIENT_CDP_DPN_DNSNAME",		"VSCERT_EX_CDP_DPN_DNSNAME1",		"SSL_CLIENT_CDP_DPN_DNSNAME"},
  {"SSL_CLIENT_CDP_DPN_DNSNAMEnn",		"VSCERT_EX_CDP_DPN_DNSNAMEnn",      "SSL_CLIENT_CDP_DPN_DNSNAMEnn"},
  {"SSL_CLIENT_CDP_DPN_URICOUNT",		"VSCERT_EX_CDP_DPN_URICOUNT",       "SSL_CLIENT_CDP_DPN_URICOUNT"},
  {"SSL_CLIENT_CDP_DPN_URI",			"VSCERT_EX_CDP_DPN_URI1",			"SSL_CLIENT_CDP_DPN_URI"},
  {"SSL_CLIENT_CDP_DPN_URInn",			"VSCERT_EX_CDP_DPN_URInn",			"SSL_CLIENT_CDP_DPN_URInn"},
  {"SSL_CLIENT_CDP_DPN_UPNCOUNT",		"VSCERT_EX_CDP_DPN_UPNCOUNT",       "SSL_CLIENT_CDP_DPN_UPNCOUNT"},
  {"SSL_CLIENT_CDP_DPN_UPN",			"VSCERT_EX_CDP_DPN_UPN1",			"SSL_CLIENT_CDP_DPN_UPN"},
  {"SSL_CLIENT_CDP_DPN_UPNnn",			"VSCERT_EX_CDP_DPN_UPNnn",			"SSL_CLIENT_CDP_DPN_UPNnn"},
  {"SSL_CLIENT_CDP_DPN_GUIDCOUNT",		"VSCERT_EX_CDP_DPN_GUIDCOUNT",      "SSL_CLIENT_CDP_DPN_GUIDCOUNT"},
  {"SSL_CLIENT_CDP_DPN_GUID",			"VSCERT_EX_CDP_DPN_GUID1",			"SSL_CLIENT_CDP_DPN_GUID"},
  {"SSL_CLIENT_CDP_DPN_GUIDnn",			"VSCERT_EX_CDP_DPN_GUIDnn",         "SSL_CLIENT_CDP_DPN_GUIDnn"},
//{"SSL_CLIENT_CDP_REASONS",			"VSCERT_EX_CDP_REASONS",			"SSL_CLIENT_CDP_REASONS"},
  {"SSL_CLIENT_CDP_CRL_DIRNAMECOUNT",	"VSCERT_EX_CDP_CRL_DIRNAMECOUNT",	"SSL_CLIENT_CDP_CRL_DIRNAMECOUNT"},
  {"SSL_CLIENT_CDP_CRL_DIRNAME",		"VSCERT_EX_CDP_CRL_DIRNAME1",		"SSL_CLIENT_CDP_CRL_DIRNAME"},
  {"SSL_CLIENT_CDP_CRL_DIRNAMEnn",		"VSCERT_EX_CDP_CRL_DIRNAMEnn",		"SSL_CLIENT_CDP_CRL_DIRNAMEnn"},
  {"SSL_CLIENT_CDP_CRL_RFC822COUNT",	"VSCERT_EX_CDP_CRL_RFC822COUNT",	"SSL_CLIENT_CDP_CRL_RFC822COUNT"},
  {"SSL_CLIENT_CDP_CRL_RFC822",			"VSCERT_EX_CDP_CRL_RFC8221",		"SSL_CLIENT_CDP_CRL_RFC822"},
  {"SSL_CLIENT_CDP_CRL_RFC822nn",		"VSCERT_EX_CDP_CRL_RFC822nn",		"SSL_CLIENT_CDP_CRL_RFC822nn"},
  {"SSL_CLIENT_CDP_CRL_DNSNAMECOUNT",	"VSCERT_EX_CDP_CRL_DNSNAMECOUNT",	"SSL_CLIENT_CDP_CRL_DNSNAMECOUNT"},
  {"SSL_CLIENT_CDP_CRL_DNSNAME",		"VSCERT_EX_CDP_CRL_DNSNAME1",		"SSL_CLIENT_CDP_CRL_DNSNAME"},
  {"SSL_CLIENT_CDP_CRL_DNSNAMEnn",		"VSCERT_EX_CDP_CRL_DNSNAMEnn",		"SSL_CLIENT_CDP_CRL_DNSNAMEnn"},
  {"SSL_CLIENT_CDP_CRL_URICOUNT",		"VSCERT_EX_CDP_CRL_URICOUNT",		"SSL_CLIENT_CDP_CRL_URICOUNT"},
  {"SSL_CLIENT_CDP_CRL_URI",			"VSCERT_EX_CDP_CRL_URI1",			"SSL_CLIENT_CDP_CRL_URI"},
  {"SSL_CLIENT_CDP_CRL_URInn",			"VSCERT_EX_CDP_CRL_URInn",			"SSL_CLIENT_CDP_CRL_URInn"},
  {"SSL_CLIENT_CDP_CRL_UPNCOUNT",		"VSCERT_EX_CDP_CRL_UPNCOUNT",		"SSL_CLIENT_CDP_CRL_UPNCOUNT"},
  {"SSL_CLIENT_CDP_CRL_UPN",			"VSCERT_EX_CDP_CRL_UPN1",			"SSL_CLIENT_CDP_CRL_UPN"},
  {"SSL_CLIENT_CDP_CRL_UPNnn",			"VSCERT_EX_CDP_CRL_UPNnn",			"SSL_CLIENT_CDP_CRL_UPNnn"},
  {"SSL_CLIENT_CDP_CRL_GUIDCOUNT",		"VSCERT_EX_CDP_CRL_GUIDCOUNT",		"SSL_CLIENT_CDP_CRL_GUIDCOUNT"},
  {"SSL_CLIENT_CDP_CRL_GUID",			"VSCERT_EX_CDP_CRL_GUID1",			"SSL_CLIENT_CDP_CRL_GUID"},
  {"SSL_CLIENT_CDP_CRL_GUIDnn",			"VSCERT_EX_CDP_CRL_GUIDnn",			"SSL_CLIENT_CDP_CRL_GUIDnn"},
  {NULL, NULL, NULL}
};
  
  
/*
 * Similar to apr_table_set, but may set multiple env vars (or none) based upon
 * value of env_options parameter
 */
void vs_table_CDR_env_set(apr_table_t *tbl, const char *name, const char *value, apacheCDR_EnvOptions env_options)
{
  int i;
  const apacheCDR_EnvVar	*cdr_env = 0;

  for (i=0; apacheCDR_EnvVarTable[i].ssl_name != 0 ; i++) {
    if ( strcmp(apacheCDR_EnvVarTable[i].ssl_name, name) == 0 ) {
      cdr_env = &apacheCDR_EnvVarTable[i];
      if ( env_options.use_ssl_name == 1) {
        apr_table_set(tbl, name, value);
      }
      if ( env_options.use_vs_name == 1) {
        apr_table_set(tbl, cdr_env->vs_name, value);       
      }
      if ( env_options.use_compat_name == 1) {
        apr_table_set(tbl, cdr_env->compat_name, value);
      }
      return;
    }
  }
  fprintf(stderr, " vs_table_CDR_env_set: %s not found\n",
          name ? name : "(null)");
  fflush(stderr);
}


/*
 * Similar to apr_table_set, but sets {varname}nn values
 * Replaces {nn} found in the name with stringified value of the nn arg.
 * note: only works for nn in the range 0...99
 */
void vs_table_nn_set(apr_table_t *tbl, const char *name, int nn, const char *value)
{
  int i;
  char *tmp_name;
  char *snn;

  tmp_name = strdup(name);
  snn = strstr(tmp_name, "nn");
  if ( snn != 0 && nn >= 0 && nn <= 99 ) {
    sprintf(snn, "%d", nn);
  }
  apr_table_set(tbl, tmp_name, value);
  free(tmp_name);
}

/*
 * Similar to apr_table_set, but sets OUnn values for multiple env vars (or none)
 * based upon value of env_options parameter
 * Note: If nn==1, then it will simply set {env_varname} as found in the table,
 * with a lookup based solely on {env_varname}_OU
 * if nn>=2 then it will set {varname}_OUnn as found in the table, by replacing
 * {nn} in the tablewith the stringified value of the nn parameter.
 */
void vs_table_CDR_env_nn_set(apr_table_t *tbl, const char *name, const char *value,
                             int nn, apacheCDR_EnvOptions env_options)
{
  int i;
  const apacheCDR_EnvVar *cdr_env = 0;
  char *tmp_name;
  char *snn;

  tmp_name = strdup(name);

  if ( nn == 1 ) {
    /* strip off any trailing nn from tmp_name */
    snn = strstr(tmp_name, "nn");
    if ( snn != 0 ) {
      *snn = '\0';
    }
    vs_table_CDR_env_set(tbl, tmp_name, value, env_options);
    free(tmp_name);
    return;
  }

  for (i=0; apacheCDR_EnvVarTable[i].ssl_name != 0 ; i++) {
    if ( strcmp(apacheCDR_EnvVarTable[i].ssl_name, name) == 0 ) {
      cdr_env = &apacheCDR_EnvVarTable[i];
      if ( env_options.use_ssl_name == 1) {
        vs_table_nn_set(tbl, cdr_env->ssl_name, nn, value);
      }
      if ( env_options.use_vs_name == 1) {
        vs_table_nn_set(tbl, cdr_env->vs_name, nn, value);
      }
      if ( env_options.use_compat_name == 1) {
        vs_table_nn_set(tbl, cdr_env->compat_name, nn, value);
      }
      free(tmp_name);
      return;
    }
  }
  free(tmp_name);
  fprintf(stderr, " vs_table_CDR_env_set: %s not found\n",
          name ? name : "(null)");
  fflush(stderr);
}


int VSUnwrapCertificate(request_rec *req)
{

  VSVAL_SDK *cpmValSDK;
  VSVAL_UserCtx ctx={0};
  VSVAL_CertFields *certDetails=0;

  int i;                   /* miscellaneous counter/index */
  int status = 0;
  char *certB64 = NULL;
  char buff[1000], buff2[1000], buff3[1000];
  apacheCDR_EnvOptions env_options = {1,1,1}; /* NSW: needs to be a struct populated from req SSL */
  char tmpBuff[12]; /* temporary storage for converting counts to strings */

  certB64 = (char *) apr_table_get(req->subprocess_env, "SSL_CLIENT_CERT"); /* nsapi: rq->vars auth-cert */
  if (!certB64) {
#ifdef DEBUG
    vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
               "Client certificate not found");
#endif
    return SERVER_ERROR;  /* nsapi: REQ_ABORTED */
  }


  vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_CERT", certB64, env_options);
  vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_CERT", certB64, env_options);

#ifdef DEBUG
  vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server, "got here ");
#endif

  do {

		  if ((status = VSVAL_Init(&cpmValSDK, &ctx, VAL_SDK_CURRENT_VERSION))) {
#ifdef DEBUG
			vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
						"VSVAL_Init returned non-zero %d", status);
#endif
			break;
		  }	

		  if ((status = VSVAL_ParseB64Cert(cpmValSDK, &ctx, &certDetails, certB64))) {
#ifdef DEBUG
			vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					   "VSVAL_ParseB64Cert returned non-zero %d", status);
#endif
			break;	
		  }

		  /* for all non null values, throw into name values in table */
		  if (certDetails->issuerOrganization) { 
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_I_DN_O", certDetails->issuerOrganization, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_I_DN_O", certDetails->issuerOrganization, env_options);
		  }
		  if (certDetails->issuerLocality) { 
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_I_DN_L", certDetails->issuerLocality, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_I_DN_L", certDetails->issuerLocality, env_options);
		  }
		  if (certDetails->issuerCountry) { 
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_I_DN_C", certDetails->issuerCountry, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_I_DN_C", certDetails->issuerCountry, env_options);
		  }
		  if (certDetails->issuerCommonName) { 
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_I_DN_CN", certDetails->issuerCommonName, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_I_DN_CN", certDetails->issuerCommonName, env_options);	  
}
		  sprintf(tmpBuff, "%d", certDetails->issuerOrgUnitCount);
		  vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_I_DN_OUCOUNT",
                       tmpBuff, env_options);
		   vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_I_DN_OUCOUNT",
                       tmpBuff, env_options);

		  if (certDetails->issuerOrgUnitCount && certDetails->issuerOrganizationUnits) {
			/* for each of them, create name = ouN, value = value */
			for (i = 0 ; i < certDetails->issuerOrgUnitCount; i++) {
			  vs_table_CDR_env_nn_set(req->subprocess_env, "SSL_CLIENT_I_DN_OUnn",
			    certDetails->issuerOrganizationUnits[i], i+1, env_options);
			  vs_table_CDR_env_nn_set(req->headers_in, "SSL_CLIENT_I_DN_OUnn",
			    certDetails->issuerOrganizationUnits[i], i+1, env_options);
			}
		  }

		  if (certDetails->emailAddress) { 
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_Email", certDetails->emailAddress, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_Email", certDetails->emailAddress, env_options);

		  }
		  if (certDetails->commonName) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_CN", certDetails->commonName, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_CN", certDetails->commonName, env_options);
		  }
		  if (certDetails->organization) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_O", certDetails->organization, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_O", certDetails->organization, env_options);
		  }
		  if (certDetails->title) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_TITLE", certDetails->title, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_TITLE", certDetails->title, env_options);
		  }
		  if (certDetails->notBefore) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_V_START", certDetails->notBefore, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_V_START", certDetails->notBefore, env_options);
		  }
		  if (certDetails->notAfter) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_V_END", certDetails->notAfter, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_V_END", certDetails->notAfter, env_options);
		  }
		  if (certDetails->uniqueID) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_UNIQUE", certDetails->uniqueID, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_UNIQUE", certDetails->uniqueID, env_options);
		  }
		  if (certDetails->address) {
			vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_ADDRESS", certDetails->address, env_options);
			vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_ADDRESS", certDetails->address, env_options);
		  }
		  sprintf(tmpBuff, "%d", certDetails->orgUnitCount);
		  vs_table_CDR_env_set(req->subprocess_env, "SSL_CLIENT_S_DN_OUCOUNT",
							   tmpBuff, env_options);
		  vs_table_CDR_env_set(req->headers_in, "SSL_CLIENT_S_DN_OUCOUNT",
							   tmpBuff, env_options);

		#ifdef DEBUG
		  vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					 "about to OUs");
		#endif
		  if (certDetails->orgUnitCount && certDetails->organizationUnits) {
			/* for each of them, create name = ouN, value = value */
			for (i = 0 ; i < certDetails->orgUnitCount; i++) {
			  vs_table_CDR_env_nn_set(req->subprocess_env, "SSL_CLIENT_S_DN_OUnn",
			    certDetails->organizationUnits[i], i+1, env_options);
			  vs_table_CDR_env_nn_set(req->headers_in, "SSL_CLIENT_S_DN_OUnn",
			    certDetails->organizationUnits[i], i+1, env_options);
			}
		  }

		#ifdef DEBUG
		  if (certDetails->commonName)
			vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					   "CN :%s:", certDetails->commonName);
		  if (certDetails->emailAddress)
			vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					   "email :%s", certDetails->emailAddress);
		#endif

#ifdef DEBUG
		  vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					 "about to Extensions");

		/* KeyUsage Extension */
		if (certDetails->v3Extensions.vsKeyUsage.szKeyUsage)
			vsLogError(APLOG_WARNING, "VSUnwrapCertificate", req->server,
					   "KeyUsage :%s:", certDetails->v3Extensions.vsKeyUsage.szKeyUsage);
#endif


		if(certDetails->v3Extensions.vsKeyUsage.szKeyUsage)
		{
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_KEYUSAGE", certDetails->v3Extensions.vsKeyUsage.szKeyUsage, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_KEYUSAGE", certDetails->v3Extensions.vsKeyUsage.szKeyUsage, env_options);
		}

		/* Extended Key Usage Extension */
		if(certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage)
		{
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_EKU", certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_EKU", certDetails->v3Extensions.vsExtendedKeyUsage.szExtendedKeyUsage, env_options);

		}

		/* SubjectAltNames */
	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_DIRNAMECOUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_DIRNAMECOUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_DIRNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDirectoryNameCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_DIRNAMEnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_DIRNAMEnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDirectoryName[i], i+1, env_options);
			}
		}

	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_RFC822COUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_RFC822COUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_RFC822n, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nRFC822NameCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_RFC822nn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_RFC822nn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szRFC822Name[i], i+1, env_options);
			}
		}

	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_DNSNAMECOUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_DNSNAMECOUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_DNSNAMEn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nDNSNameCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_DNSNAMEnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_DNSNAMEnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szDNSName[i], i+1, env_options);
			}
		}

	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_URICOUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_URICOUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_URIn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nUniformResourceIdentifierCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_URInn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_URInn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szUniformResourceIdentifier[i], i+1, env_options);
			}
		}

	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_UPNCOUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_UPNCOUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_UPNn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameUPNCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_UPNnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_UPNnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameUPN[i], i+1, env_options);
			}
		}

	    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount);
		vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_SAN_GUIDCOUNT", tmpBuff, env_options);
		vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_SAN_GUIDCOUNT", tmpBuff, env_options);
		if(certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount && 
			certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID)
		{
			/* for each of them, create name = SSL_CLIENT_SAN_GUIDn, value = value */
			for (i = 0 ; i < certDetails->v3Extensions.vsSubjectAltName.GeneralNames.nOtherNameGUIDCount; i++) {
				vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_SAN_GUIDnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID[i], i+1, env_options);
				vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_SAN_GUIDnn", 
					certDetails->v3Extensions.vsSubjectAltName.GeneralNames.szOtherNameGUID[i], i+1, env_options);
			}
		}


		/* CDP Extension: FullName */
		if(certDetails->v3Extensions.vsCDP.nDPNamePresent)
		{
		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_DIRNAMECOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_DIRNAMECOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDirectoryNameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_DIRNAMEnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_DIRNAMEnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szDirectoryName[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_RFC822COUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_RFC822COUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nRFC822NameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_RFC822nn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_RFC822nn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szRFC822Name[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_DNSNAMECOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_DNSNAMECOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nDNSNameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_DNSNAMEnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_DNSNAMEnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szDNSName[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_URICOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_URICOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nUniformResourceIdentifierCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_URInn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_URInn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szUniformResourceIdentifier[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_UPNCOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_UPNCOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameUPNCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_UPNnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_UPNnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameUPN[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_GUIDCOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_DPN_GUIDCOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_DPN_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.distributionPointName.nOtherNameGUIDCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_DPN_GUIDnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_DPN_GUIDnn", 
						certDetails->v3Extensions.vsCDP.distributionPointName.szOtherNameGUID[i], i+1, env_options);
				}
			}
		}
		
		/* CDP Extension: ReasonFlags */
/*
		if(certDetails->v3Extensions.vsCDP.szReasonFlags)
		{
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_REASONS", certDetails->v3Extensions.vsCDP.szReasonFlags, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_REASONS", certDetails->v3Extensions.vsCDP.szReasonFlags, env_options);
		}
*/
		/* CDP Extension: cRLIssuer */
		if(certDetails->v3Extensions.vsCDP.nCRLIssuerPresent)
		{
		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_DIRNAMECOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_DIRNAMECOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_DIRNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDirectoryNameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_DIRNAMEnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_DIRNAMEnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szDirectoryName[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_RFC822COUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_RFC822COUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_RFC822n, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nRFC822NameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_RFC822nn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_RFC822nn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szRFC822Name[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_DNSNAMECOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_DNSNAMECOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_DNSNAMEn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nDNSNameCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_DNSNAMEnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_DNSNAMEnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szDNSName[i], i+1, env_options);
				}

			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_URICOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_URICOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_URIn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nUniformResourceIdentifierCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_URInn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_URInn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szUniformResourceIdentifier[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_UPNCOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_UPNCOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_UPNn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameUPNCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_UPNnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_UPNnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameUPN[i], i+1, env_options);
				}
			}

		    sprintf(tmpBuff, "%d", certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount);
			vs_table_CDR_env_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_GUIDCOUNT", tmpBuff, env_options);
			vs_table_CDR_env_set (req->headers_in, "SSL_CLIENT_CDP_CRL_GUIDCOUNT", tmpBuff, env_options);
			if(certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount && 
				certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID)
			{
				/* for each of them, create name = SSL_CLIENT_CDP_CRL_GUIDn, value = value */
				for (i = 0 ; i < certDetails->v3Extensions.vsCDP.cRLIssuerName.nOtherNameGUIDCount; i++) {
					vs_table_CDR_env_nn_set (req->subprocess_env, "SSL_CLIENT_CDP_CRL_GUIDnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID[i], i+1, env_options);
					vs_table_CDR_env_nn_set (req->headers_in, "SSL_CLIENT_CDP_CRL_GUIDnn", 
						certDetails->v3Extensions.vsCDP.cRLIssuerName.szOtherNameGUID[i], i+1, env_options);
				}
			}
		}


  } while (0);


  /* clean up */
  VSVAL_FreeCertFields (cpmValSDK, certDetails);
  VSVAL_Final ( cpmValSDK );

  return DONE;  /* nsapi: REQ_PROCEED */
}
