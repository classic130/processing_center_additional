/* SCCSID: inc/cssmdefs.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.26 8/12/98 19:10:25 */
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

#ifndef _CSSMDEFS_H
#define _CSSMDEFS_H

#ifndef KEY_RECOVERY
#define KEY_RECOVERY
#endif

#ifndef CSSM_PRIVILEGE
#define CSSM_PRIVILEGE
#endif

#ifndef CSSM_INTEGRITY
#define CSSM_INTEGRITY
#endif

#ifndef CSSM_TRACE
#define CSSM_TRACE
#endif

#ifdef CSSM_TRACE
#define DO_TRACE
#define BINARY_TRACE
#endif

// The following #define must match the CERTDIR variable in
// the top level makefile (on AIX and Win32)
// If CERTDIR = REALCERTDIR, then #define REAL_CERTS
// Else #define DEV_CERTS (or nothing)

#define REAL_CERTS
//#define DEV_CERTS

#endif /* _CSSMDEFS_H */
