/* SCCSID: inc/cssm.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.4 8/12/98 19:10:18 */
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

#ifndef _CSSM_H
#define _CSSM_H    

#include "cssmdefs.h"
#include "cssmtype.h"

#ifndef RUNTIME_CSSM_SYMBOL_RESOLUTION
#include "cssmapi.h"
#endif

#include "cssmerr.h"

/* Version 1.2.0.X */
#define CSSM_MAJOR 1 /* Major version # */
#define CSSM_MINOR 20 /* Minor version # */

#define CSSM_CAPABILITY_VERSION     0x0120              

#endif
