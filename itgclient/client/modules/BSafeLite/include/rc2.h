/* Copyright (C) RSA Data Security, Inc. created 1991.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _RC2_H_
#define _RC2_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include "keysize.h"

#define A_MAX_RC2_EFFECTIVE_KEY_BITS   BSAFE_MAX_RC2_KEY_SIZE_BITS
#define A_MIN_RC2_EFFECTIVE_KEY_BITS   BSAFE_MIN_RC2_KEY_SIZE_BITS

typedef struct {
  UINT4 keyTable[64];
} RC2_CTX;

int RC2Init PROTO_LIST ((RC2_CTX *, ITEM *, unsigned int));
void RC2Encrypt PROTO_LIST ((POINTER, unsigned char *, unsigned char *));
void RC2Decrypt PROTO_LIST ((POINTER, unsigned char *, unsigned char *));

#ifdef __cplusplus
}
#endif

#endif
