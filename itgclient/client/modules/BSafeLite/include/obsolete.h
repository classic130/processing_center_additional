/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _OBSOLETE_H_
#define _OBSOLETE_H_

#ifndef T_CALL
#define T_CALL
#endif

/* These algorithm methods are here fore backward compatible to
   BSAFE version before 2.5.
 */
#define AM_DH_KEY_AGREE_86 AM_DH_KEY_AGREE
#define AM_DH_PARAM_GEN_86 AM_DH_PARAM_GEN
#define AM_MAC_86 AM_MAC
#define AM_RC4_DECRYPT_86 AM_RC4_DECRYPT
#define AM_RC4_ENCRYPT_86 AM_RC4_ENCRYPT
#define AM_RC4_WITH_MAC_DECRYPT_86 AM_RC4_WITH_MAC_DECRYPT
#define AM_RC4_WITH_MAC_ENCRYPT_86 AM_RC4_WITH_MAC_ENCRYPT
#define AM_RSA_CRT_DECRYPT_86 AM_RSA_CRT_DECRYPT
#define AM_RSA_CRT_ENCRYPT_86 AM_RSA_CRT_ENCRYPT
#define AM_RSA_ENCRYPT_86 AM_RSA_ENCRYPT
#define AM_RSA_DECRYPT_86 AM_RSA_DECRYPT
#define AM_RSA_KEY_GEN_86 AM_RSA_KEY_GEN

#define AM_RSA_CRT_DECRYPT_68 AM_RSA_CRT_DECRYPT
#define AM_RSA_CRT_ENCRYPT_68 AM_RSA_CRT_ENCRYPT
#define AM_DH_KEY_AGREE_68 AM_DH_KEY_AGREE
#define AM_DH_PARAM_GEN_68 AM_DH_PARAM_GEN
#define AM_RSA_DECRYPT_68 AM_RSA_DECRYPT
#define AM_RSA_ENCRYPT_68 AM_RSA_ENCRYPT
#define AM_RSA_KEY_GEN_68 AM_RSA_KEY_GEN

/* The default AM's do not buffer bytes unnecessarily. */
#define AM_DES_CBC_ENCRYPT_NO_PAD  AM_DES_CBC_ENCRYPT 
#define AM_DES_CBC_DECRYPT_NO_PAD  AM_DES_CBC_DECRYPT

#endif
