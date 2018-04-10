/* Copyright (C) RSA Data Security, Inc. created 1993.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _KEY_SIZE_H_
#define _KEY_SIZE_H_ 1

//#ifdef __cplusplus
//extern "C" {
//#endif

#ifndef BSAFE_EXPORT_VERSION
/* Domestic, unrestricted key sizes */
#define BSAFE_MAX_RSA_KEY_SIZE_BITS     2048
#define BSAFE_MIN_RSA_KEY_SIZE_BITS     256

#define BSAFE_MAX_RC2_KEY_SIZE_BITS     1024
#define BSAFE_MIN_RC2_KEY_SIZE_BITS     1

#define BSAFE_MAX_RC4_KEY_SIZE_BITS     2048
#define BSAFE_MIN_RC4_KEY_SIZE_BITS     8

#else  /* BSAFE_EXPORT_VERSION */
/* international, restricted key sizes */
#define BSAFE_MAX_RSA_KEY_SIZE_BITS     512
#define BSAFE_MIN_RSA_KEY_SIZE_BITS     256

#define BSAFE_MAX_RC2_KEY_SIZE_BITS     40
#define BSAFE_MIN_RC2_KEY_SIZE_BITS     1

#define BSAFE_MAX_RC4_KEY_SIZE_BITS     40
#define BSAFE_MIN_RC4_KEY_SIZE_BITS     8

#endif  /* BSAFE_EXPORT_VERSION */

#define BSAFE_MAX_DH_KEY_SIZE_BITS      BSAFE_MAX_RSA_KEY_SIZE_BITS
#define BSAFE_MIN_DH_KEY_SIZE_BITS      BSAFE_MIN_RSA_KEY_SIZE_BITS

#define BSAFE_MAX_DSA_KEY_SIZE_BITS     BSAFE_MAX_RSA_KEY_SIZE_BITS
#define BSAFE_MIN_DSA_KEY_SIZE_BITS     512

//#ifdef _cplusplus
//}
//#endif

#endif
