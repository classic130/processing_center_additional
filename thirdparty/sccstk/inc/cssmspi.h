/* SCCSID: inc/cssmspi.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.7 8/12/98 19:10:22 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * Copyright (c) 1995, 1996, 1997 Intel Corporation. All rights reserved.
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _CSSMSPI_H
#define _CSSMSPI_H    

#include "cssmtype.h"
#include "cssmcspi.h"
#include "cssmdli.h"
#include "cssmcli.h"
#include "cssmtpi.h"

#ifdef KEY_RECOVERY
#include "cssmkrspi.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct cssm_module_funcs {
    CSSM_SERVICE_TYPE ServiceType;
    union {
        void *ServiceFuncs;
        CSSM_SPI_CSP_FUNCS_PTR CspFuncs;
        CSSM_SPI_DL_FUNCS_PTR DlFuncs;
        CSSM_SPI_CL_FUNCS_PTR ClFuncs;
        CSSM_SPI_TP_FUNCS_PTR TpFuncs;
#ifdef KEY_RECOVERY
        CSSM_SPI_KRSP_FUNCS_PTR KrspFuncs;
#endif
    };
} CSSM_MODULE_FUNCS, *CSSM_MODULE_FUNCS_PTR;

/* Structure for passing handle information to addins */
typedef struct cssm_handleinfo {
    uint32 SubServiceID;
    uint32 SessionFlags;
    CSSM_NOTIFY_CALLBACK Callback;
    uint32 ApplicationContext;
} CSSM_HANDLEINFO, *CSSM_HANDLEINFO_PTR;

typedef struct cssm_registration_info {
    /* Loading, Unloading and Event Notifications */
    CSSM_RETURN (CSSMAPI *Initialize) (CSSM_MODULE_HANDLE Handle,
                                       uint32 VerMajor,
                                       uint32 VerMinor);
    CSSM_RETURN (CSSMAPI *Terminate) (CSSM_MODULE_HANDLE Handle);
    CSSM_RETURN (CSSMAPI *EventNotify) (CSSM_MODULE_HANDLE Handle,
                                        const CSSM_EVENT_TYPE Event,
                                        const uint32 Param);
    CSSM_MODULE_INFO_PTR (CSSMAPI *GetModuleInfo) 
                                              (CSSM_MODULE_HANDLE ModuleHandle,
                                               CSSM_SERVICE_MASK ServiceMask,
                                               uint32 SubserviceID,
                                               CSSM_INFO_LEVEL InfoLevel);
    CSSM_RETURN (CSSMAPI *FreeModuleInfo) (CSSM_MODULE_HANDLE ModuleHandle,  
                                           CSSM_MODULE_INFO_PTR ModuleInfo);
    CSSM_BOOL ThreadSafe;
    uint32 ServiceSummary;
    uint32 NumberOfServiceTables;
    CSSM_MODULE_FUNCS_PTR Services;
} CSSM_REGISTRATION_INFO, *CSSM_REGISTRATION_INFO_PTR;

#ifndef RUNTIME_CSSM_SYMBOL_RESOLUTION
CSSM_RETURN CSSMAPI CSSM_RegisterServices (
                             const CSSM_GUID_PTR GUID,
                             const CSSM_REGISTRATION_INFO_PTR FunctionTable,
                             CSSM_SPI_MEMORY_FUNCS_PTR UpcallTable,
                             void *Reserved);

CSSM_RETURN CSSMAPI CSSM_DeregisterServices (const CSSM_GUID_PTR GUID);

CSSM_HANDLEINFO_PTR CSSMAPI CSSM_GetHandleInfo(CSSM_HANDLE hModule);
#endif
                            
#ifdef __cplusplus
}
#endif

#endif
