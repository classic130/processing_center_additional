/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/sc/policymodule/include/Attic/vspmsp.h,v 1.1.2.1 2001/09/06 22:32:17 ajayaram Exp $
 */

/*-----------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1999. All rights reserved.        |
| This is an unpublished work protected as such under copyright law.     |
| This work contains proprietary, confidential, and trade secret         |
| information of VeriSign, Inc.  Use, disclosure or reproduction without |
| the expressed written authorization of VeriSign, Inc.  is prohibited.  |
\-----------------------------------------------------------------------*/


#ifndef _VSPMSP_H_
#define _VSPMSP_H_

#include "vspmutil.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#define VSPM_EXPORT extern __declspec( dllexport )
#else
#define VSPM_EXPORT extern
#endif

/*
#define       VSPM_NOT_FOUND                    0xC006
#define       VSPM_INVALID_TEXT                 0xC007
#define       VSPM_INVALID_T61                  0xC008
#define       VSPM_INVALID_EMAIL                0xC009
#define       VSPM_INVALID_NUMBER               0xC00A
#define       VSPM_INVALID_BASE64               0xC00B
#define       VSPM_INVALID_PHONE                0xC00C
#define       VSPM_INVALID_DATE                 0xC00D
#define       VSPM_INVALID_TYPE                 0xC00E
#define       VSPM_FIELD_REQUIRED               0xC00F
#define       VSPM_FIELD_TOO_SHORT              0xC010
#define       VSPM_FIELD_TOO_LONG               0xC011
#define       VSPM_INVALID_VERSION              0xC012
#define       VSPM_INDEX_OUT_OF_RANGE           0xC013
#define       VSPM_INVALID_FILE_FORMAT          0xC014
#define       VSPM_NOT_SUPPORTED_FILE_FORMAT    0xC015
*/


/* This function opens a configuration file specified by the url
 *
 *   configUrl - IN  - the url of the configuration file. If NULL, use default 
 *                     file:///ecas/onsitedata/config/pmsp.conf
 *   status    - OUT - if the function returns NULL, the return status indicates the failure reas
on
 *   RETURNS   - a VSPM_Descriptor or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Descriptor
        VSPMSP_OpenConfig (
                const char *configUrl,
                VSPM_STATUS *status);


/* This function closes and cleans up the data associated with a previously opened VSPM_Descriptor
 *
 *   pmd - IN  - the descriptor of the policy description or configuration file
 *              
 */

VSPM_EXPORT void
        VSPMSP_Close (
                VSPM_Descriptor pmd);


/* This function returns the version of the policy configuration file
 *
 *   pmd      - IN  - the descriptor of the policy description or configuration file
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT VSPM_Version
        VSPMSP_GetVersionFromDescriptor (
                VSPM_Descriptor pmd,
                VSPM_STATUS *status);


/* This function adds a module name that the policy module service provider
 * will call when VSPMSP_GeneratePolicy function is called
 *
 *   pmd      - IN  - the descriptor of the configuration file
 *   moduleName     - IN  - the pointer to the name of the module
 *   moduleNameLen  - IN  - number of bytes, not including the terminating '\0' char of the length of name
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT void
        VSPMSP_AddModuleToDescriptor (
                VSPM_Descriptor pmd,
                const char * moduleName,
                unsigned int moduleNameLen,
                VSPM_STATUS *status);


/* This function adds a name value pair (NVP) to the policy descriptor
 *
 *   pmd      - IN  - the descriptor of the policy file
 *   name     - IN  - the pointer to the name
 *   nameLen  - IN  - number of bytes, not including the terminating '\0' char of the length of name
 *   value    - IN  - the pointer to the value
 *   valueLen - IN  - number of bytes, not including the terminating '\0' char of the length of value
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 *   RETURNS  - a VSPM_Version or
 *              NULL if an error is encountered
 */

VSPM_EXPORT void
        VSPMSP_AddNVPToDescriptor (
                VSPM_Descriptor pmd,
                const char * name,
                unsigned int nameLen,
                const char * value,
                unsigned int valueLen,
                VSPM_STATUS *status);


/* This function deletes a name value pair (NVP) to the policy descriptor
 *
 *   pmd      - IN  - the descriptor of the policy file
 *   name     - IN  - the pointer to the name
 *   nameLen  - IN  - number of bytes, not including the terminating '\0' char of the length of name
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_DeleteNVPToDescriptor (
                VSPM_Descriptor pmd,
                const char * name,
                unsigned int nameLen,
                VSPM_STATUS *status);


/* This function command the PMSP to generate the custom policy at the given url
 *
 *   cfd      - IN  - the descriptor of the configuration file
 *   templateUrl - IN  - the url path to the policy template
 *   policyUrl - IN  - the url path to the custom policy 
 *   outUrl   - IN  - the pointer to the url of the custom policy
 *   status   - OUT - if the function returns NULL, the return status indicates the failure reason
 */

VSPM_EXPORT void
        VSPMSP_GeneratePolicy (
                VSPM_Descriptor cfd,
                const char * templateUrl,
                const char * policyUrl,
                const char * outUrl,
                VSPM_STATUS *status);

#ifdef  __cplusplus
}
#endif

#endif  /* _VSPMSP_H_ */

