/* Copyright (C) RSA Data Security, Inc. created 1992.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _RC4_H_
#define _RC4_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#include "keysize.h"

#if INTELx86i32 == 1
//#define A_RC4Update          A_RC4UpdateI32
//#define RC4_UPDATE_ASSEMBLY  1
#endif
#if INTELx86 == 1
#define A_RC4Update A_RC4Update86
#define A_RC4Init A_RC4Init86
#define A_RC4Final A_RC4Final86
#define A_RC4_CTX A_RC4_86_CTX
#define RC4_INIT_ASSEMBLY  1
#define RC4_UPDATE_ASSEMBLY  1
#define RC4_FINAL_ASSEMBLY  1
#endif

#define MAX_RC4_KEY_LEN   ((BSAFE_MAX_RC4_KEY_SIZE_BITS + 7) / 8)

#if INTELx86 == 0
typedef struct {
  int initialized;
  unsigned int i;
  unsigned int j;
  unsigned char table[256];
} A_RC4_CTX;
#endif
#if INTELx86 == 1
/* Note: structure element names are prefixed with RC4_CTX_ to make sure that
   the inline assembler can identify which structure the element belongs to.
 */
typedef struct {
  unsigned char RC4_86_CTX_table[256];  /* key table, must be first (see *!*...
                                              ... for where this is assumed) */
  unsigned int RC4_86_CTX_byteCount;                         /* byte counter */
  unsigned char RC4_86_CTX_initialized;        /* 1 if initialized, 0 if not */
  unsigned int RC4_86_CTX_ij;            /* Least-sig (first) byte=i, last=j */
} A_RC4_86_CTX;
#endif
void A_RC4Init(A_RC4_CTX *, ITEM *);
int A_RC4Update(A_RC4_CTX *, unsigned char *, unsigned int *, unsigned int,unsigned char *, unsigned int);
int A_RC4Final (A_RC4_CTX *);

#ifdef __cplusplus
}
#endif

#endif
