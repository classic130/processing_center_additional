/* SCCSID: inc/ibmtp2.h, dss_cdsa_fwk, fwk_rel3, dss_980811 1.5 8/12/98 19:14:15 */
/*
 * (C) COPYRIGHT International Business Machines Corp. 1996, 1997
 * All Rights Reserved
 * Licensed Materials - Property of IBM
 *
 * US Government Users Restricted Rights - Use, duplication or
 * disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 */

#ifndef _IBMTP2_H
#define _IBMTP2_H

// includes

#include "cssm.h"


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* IBMTP constants */

static const char*
IBMTP_NAME = "IBM Trust Policy Module";

#if defined (WIN32) || defined (OS2)
static const char*
IBMTP_FILENAME = "ibmtp.dll";
#endif /* WIN32 || OS2 */

#if defined (AIX4) || defined (HPUX) || defined (SOLARIS)
static const char*
IBMTP_FILENAME = "ibmtp.so";
#endif /* AIX4 || HPUX || SOLARIS */

static const uint32
IBMTP_SUBSERVICEID = 0;

/* {B6A22253-04FF-11d1-BBCB-08005AB942C5} */
static CSSM_GUID
IBMTP_GUID = { 0xb6a22253, 0x4ff, 0x11d1, { 0xbb, 0xcb, 0x8, 0x0, 0x5a, 0xb9, 0x42, 0xc5 } };

static const uint32
IBMTP_MAJOR_VERSION = 1;

static const uint32
IBMTP_MINOR_VERSION = 0;


#define IBMTP2_THREADSAFE     (CSSM_TRUE)
#define IBMTP2_NUMSUBSERVICE  (1)



/********************************************************************************
 IBM TP module certificate verification policies
 Four kinds of certificates (or extensions) are supported:
    X509 Certificates  ( default one to be used)
    SET  Certificates
    Entrust Certificates
    Netscape Certificates
 ********************************************************************************/

// IBM TP module certificate verification policies
// Four kinds of certificates (or extensions) are supported:
//    X509 Certificates  ( default one to be used)
//    SET  Certificates
//    Entrust Certificates
//    Netscape Certificates

#define IBMTP_NUMBER_POLICY_IDENTIFIER  4

static unsigned char IBMTP_X509_POLICY_FIELD_OID_DATA[] = {0x06, 0x07, 0x2a, 0x87, 0x67, 0x01, 0x02, 0x01, 0x01}; 
static unsigned IBMTP_X509_POLICY_FIELD_OID_LENGTH = sizeof(IBMTP_X509_POLICY_FIELD_OID_DATA);
static unsigned char IBMTP_X509_POLICY_FIELD_VALUE[] = "IBMTP X509 Policy Identifier";
static unsigned IBMTP_X509_POLICY_FIELD_VALUE_LENGTH = sizeof(IBMTP_X509_POLICY_FIELD_VALUE);

static unsigned char IBMTP_SET_POLICY_FIELD_OID_DATA[] = {0x06, 0x07, 0x2a, 0x87, 0x67, 0x01, 0x02, 0x01, 0x02}; 
static unsigned IBMTP_SET_POLICY_FIELD_OID_LENGTH = sizeof(IBMTP_SET_POLICY_FIELD_OID_DATA);
static unsigned char IBMTP_SET_POLICY_FIELD_VALUE[] = "IBMTP SET Policy Identifier";
static unsigned IBMTP_SET_POLICY_FIELD_VALUE_LENGTH = sizeof(IBMTP_SET_POLICY_FIELD_VALUE);

static unsigned char IBMTP_ENTRUST_POLICY_FIELD_OID_DATA[] = {0x06, 0x07, 0x2a, 0x87, 0x67, 0x01, 0x02, 0x01, 0x03}; 
static unsigned IBMTP_ENTRUST_POLICY_FIELD_OID_LENGTH = sizeof(IBMTP_ENTRUST_POLICY_FIELD_OID_DATA);
static unsigned char IBMTP_ENTRUST_POLICY_FIELD_VALUE[] = "IBMTP Entrust Policy Identifier";
static unsigned IBMTP_ENTRUST_POLICY_FIELD_VALUE_LENGTH = sizeof(IBMTP_ENTRUST_POLICY_FIELD_VALUE);

static unsigned char IBMTP_NETSCAPE_POLICY_FIELD_OID_DATA[] = {0x06, 0x07, 0x2a, 0x87, 0x67, 0x01, 0x02, 0x01, 0x04}; 
static unsigned IBMTP_NETSCAPE_POLICY_FIELD_OID_LENGTH = sizeof(IBMTP_NETSCAPE_POLICY_FIELD_OID_DATA);
static unsigned char IBMTP_NETSCAPE_POLICY_FIELD_VALUE[] = "IBMTP Netscape Policy Identifier";
static unsigned IBMTP_NETSCAPE_POLICY_FIELD_VALUE_LENGTH = sizeof(IBMTP_NETSCAPE_POLICY_FIELD_VALUE);

const static CSSM_FIELD IBMTP_X509_POLICY_IDENTIFIER = {
   {IBMTP_X509_POLICY_FIELD_OID_LENGTH, IBMTP_X509_POLICY_FIELD_OID_DATA}, 
   {IBMTP_X509_POLICY_FIELD_VALUE_LENGTH, IBMTP_X509_POLICY_FIELD_VALUE}
};
  
const static CSSM_FIELD IBMTP_SET_POLICY_IDENTIFIER = { 
   {IBMTP_SET_POLICY_FIELD_OID_LENGTH, IBMTP_SET_POLICY_FIELD_OID_DATA},
   {IBMTP_SET_POLICY_FIELD_VALUE_LENGTH, IBMTP_SET_POLICY_FIELD_VALUE}
};
  
const static CSSM_FIELD IBMTP_ENTRUST_POLICY_IDENTIFIER = { 
   {IBMTP_ENTRUST_POLICY_FIELD_OID_LENGTH, IBMTP_ENTRUST_POLICY_FIELD_OID_DATA},
   {IBMTP_ENTRUST_POLICY_FIELD_VALUE_LENGTH, IBMTP_ENTRUST_POLICY_FIELD_VALUE}
};
  
const static CSSM_FIELD IBMTP_NETSCAPE_POLICY_IDENTIFIER = { 
   {IBMTP_NETSCAPE_POLICY_FIELD_OID_LENGTH, IBMTP_NETSCAPE_POLICY_FIELD_OID_DATA},
   {IBMTP_NETSCAPE_POLICY_FIELD_VALUE_LENGTH, IBMTP_NETSCAPE_POLICY_FIELD_VALUE}
};


#ifdef __cplusplus
}
#endif /* __cplusplus */
  

#endif /* _IBMTP2_H */
