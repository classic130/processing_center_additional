
#ifdef __cplusplus
extern "C" {
  /* This allows for C++ inclusion/use of this header file */
#endif

#ifndef _CVMGLOBAL_H_
#define _CVMGLOBAL_H_ 1
#include "limits.h"

#ifdef SOLARIS
		#pragma ident "@(#)VeriSign Certificate Validation Module 7.2 19/10/2007"     
#else
#ifdef HPUX
		#pragma VERSIONID "@(#)VeriSign Certificate Validation Module 7.2 19/10/2007" 
#endif
#endif


#define CVM_LARGE_BUF_MAX 4096
#define NSAPI_DESCR "VeriSign Certificate Validation Module Plugin, Version 7.2"
#define FILTER_DESCRIPTION "VeriSign Certificate Validation Module Filter, Version 7.2"
#define APACHE_CVM_DESCRIPTION "VeriSign Certificate Validation Module, Version 7.2"
#define APACHE_LOG_DESCRIPTION "VeriSign CVM 7.2"

#define VSVAL_CVM_ERR_BASE 9900	
#define VSVAL_CVM_OS_VERSION                  (VSVAL_CVM_ERR_BASE + 1)
#define VSVAL_CVM_ERR_MAX                         (VSVAL_CVM_ERR_BASE + 2)


#define CVM_MAX_UPDATE_TIME INT_MAX
#define CVM_LDAP_TIMEOUT 120
#define CVM_LDAP_HTTP_CGI "cgi-bin/ldappost.exe"


/* Fix for CR29977 - Begin */
#define NO_CHECK_CHAIN_USAGE_WARNING "Warning : Found usage of no-check-chain, please change your configuration to use check-chain"
/* Fix for CR29977 - End */
typedef unsigned long int CVMTIME;

void cvm_time (CVMTIME *theTime);
void cvm_make_newline_null(char *str);
int cvmCfgStringIsOn(const char *value);
void (* cvmGlobalInfoLog) (char *fmt, ...);
#ifdef __cplusplus
}
#endif
/* end of C wrapper for C++ */

#endif /*  _CVMGLOBAL_H_ */
