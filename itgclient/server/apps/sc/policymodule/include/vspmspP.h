/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmspP.h,v 1.1.2.1 2001/09/06 22:32:18 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMSPP_H_
#define _VSPMSPP_H_

#include <vsnvp.h>
#include "vspmutilP.h"
#include "vspmsp.h"
#include "vspmsmp.h"

#define VSPM_INVALID_URL		0xD001
#define VSPM_NOT_SUPPORTED_PROTOCOL	0xD002
#define VSPM_NOT_SUPPORTED_VALUE	0xD003
#define VSPM_INVALID_VALUE		0xD004

#define FILE_PROTOCOL			"file"
#define PROTOCOL_DELIMITER		"://"

#define ECASINSTALL			"ECASINSTALL"

#define DEFAULT_ECAS_INSTALL		"/ecas/onsite/"
#define DEFAULT_POLICY_CONFIG		"config/pmsp.conf"
#define DEFAULT_POLICY_TEMPLATE		"config/policy.onsite.template"

#define VSPM_VERSION_HANDLING		"VERSION_HANDLING"

#define VSPM_DEFAULT			"DEFAULT"
#define VSPM_USE_NEWER			"USE_NEWER"
#define VSPM_USE_CUSTOM			"USE_CUSTOM"
#define VSPM_USE_TEMPLATE		"USE_TEMPLATE"

#define _VSPM_USE_CUSTOM		1
#define _VSPM_USE_TEMPLATE		2
#define _VSPM_USE_NEWER			3

#define VSPM_MODULE_CONTAINER	"Module"

#define VSPM_LIBRARY_ITEM		"libraryName"
#define VSPM_CALLBACK_FUNC_ITEM	"callBackName"

#ifdef __cplusplus
extern "C" {
#endif

VSPM_STATUS parseUrl (const char *url, char **protocol, char **host, char **port, char **res);

VSPM_STATUS openUrl (const char *url, VSContainer **container); 

VSPM_STATUS openFileUrl (const char *pathname, VSContainer **container); 

char * getDefaultPolicyConfigUrl (VSPM_STATUS * status);

char * getDefaultPolicyTemplateUrl (VSPM_STATUS * status);

int getVersionHandling(VSContainer *configCnt, VSPM_STATUS *status);

VSContainer * openPolicy(const char *policyUrl, VSPM_STATUS *status);

VSContainer * openPolicyTemplate(const char *templateUrl, VSPM_STATUS *status);

VSContainer * mergePolicy(VSContainer * configCnt,
                          VSContainer * templateCnt,
                          VSContainer * policyCnt,
                          VSPM_STATUS *status);

VSPM_STATUS invokeModuleCallBack(VSContainer *module, VSContainer *policy);

void writePolicy(const char *outUrl, VSContainer *policyCnt, VSPM_STATUS *status);



#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMSPP_H_ */
