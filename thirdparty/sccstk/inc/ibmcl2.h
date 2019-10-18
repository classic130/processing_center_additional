/* SCCSID: inc/ibmcl2.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.4 8/12/98 19:14:14 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _IBMCL_H_
#define _IBMCL_H_

// includes

#include "cssm.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* IBMCL constants */

static const char*
IBMCL_NAME = "IBM Certificate Library Module";

#if defined (WIN32) || defined (OS2)
static const char*
IBMCL_FILENAME = "ibmcl.dll";
#endif /* WIN32 || OS2 */

#if defined (AIX4) || defined (HPUX) || defined (SOLARIS)
static const char*
IBMCL_FILENAME = "ibmcl.so";
#endif /* AIX4 || HPUX || SOLARIS */

static const uint32
IBMCL_SUBSERVICEID = 0;

/* {B6A22252-04FF-11d1-BBCB-08005AB942C5} */
static const CSSM_GUID
IBMCL_GUID = { 0xb6a22252, 0x4ff, 0x11d1, { 0xbb, 0xcb, 0x8, 0x0, 0x5a, 0xb9, 0x42, 0xc5 } };

static const uint32
IBMCL_MAJOR_VERSION = 1;

static const uint32
IBMCL_MINOR_VERSION = 0;


#define IBMCL2_THREADSAFE     (CSSM_TRUE)
#define IBMCL2_NUMSUBSERVICE  (1)


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* _IBMCL_H_ */
