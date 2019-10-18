/* Copyright (C) RSA Data Security, Inc. created 1992.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "aglobal.h"

#ifndef _ATYPES_H_
#define _ATYPES_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif

#ifndef _A_SURRENDER_CTX_
#define _A_SURRENDER_CTX_ 1
typedef struct {
  int (CALL_CONV *Surrender) PROTO_LIST ((POINTER));
  POINTER handle;
  POINTER reserved;
} A_SURRENDER_CTX;
#endif

typedef unsigned char *A_DES_KEY;                          /* 8-byte DES key */

typedef unsigned char *A_DES_CBC_PARAMS;                        /* 8-byte IV */

typedef struct {
  unsigned char *key;                                      /* 8-byte DES key */
  unsigned char *inputWhitener;                     /* 8-byte input whitener */
  unsigned char *outputWhitener;                   /* 8-byte output whitener */
} A_DESX_KEY;

typedef struct {
  ITEM prime;                                                       /* prime */
  ITEM base;                                                         /* base */
  unsigned int exponentBits;
} A_DH_KEY_AGREE_PARAMS;

typedef struct {
  unsigned int primeBits;
  unsigned int exponentBits;
} A_DH_PARAM_GEN_PARAMS;

typedef struct {
  unsigned int primeBits;
  unsigned int subPrimeBits;
} A_PQG_PARAM_GEN_PARAMS;

typedef struct {
  ITEM prime;                                                   /* prime (p) */
  ITEM subPrime;                                            /* sub prime (q) */
  ITEM base;                                                     /* base (g) */
} A_PQG_PARAMS;

typedef A_PQG_PARAMS A_DSA_PARAMS;

typedef struct {
  ITEM modulus;
  ITEM publicExponent;
  ITEM privateExponent;
  ITEM prime[2];                                            /* prime factors */
  ITEM primeExponent[2];                      /* exponents for prime factors */
  ITEM coefficient;                                       /* CRT coefficient */
} A_PKCS_RSA_PRIVATE_KEY;

typedef unsigned char *A_RC2_KEY;                          /* 8-byte RC2 key */

typedef struct {
  unsigned int effectiveKeyBits;
  unsigned char *iv;
} A_RC2_CBC_PARAMS;

typedef struct {
  unsigned int effectiveKeyBits;
} A_RC2_ECB_PARAMS;

typedef struct {
  unsigned int version;
  unsigned int rounds;
  unsigned int wordSizeInBits;
  unsigned char *iv;
} A_RC5_CBC_PARAMS;

typedef struct {
  ITEM modulus;
  ITEM prime[2];                                            /* prime factors */
  ITEM primeExponent[2];                      /* exponents for prime factors */
  ITEM coefficient;                                       /* CRT coefficient */
} A_RSA_CRT_KEY;

typedef struct {
  ITEM modulus;                                                   /* modulus */
  ITEM exponent;                                                 /* exponent */
} A_RSA_KEY;

typedef struct {
  unsigned int modulusBits;
  ITEM publicExponent;
} A_RSA_KEY_GEN_PARAMS;

typedef struct {
  ITEM y;                                                /* public component */
  A_DSA_PARAMS params;                              /* parameters (p, q, g) */
} A_DSA_PUBLIC_KEY;

typedef struct {
  ITEM x;                                               /* private component */
  A_DSA_PARAMS params;                              /* parameters (p, q, g) */
} A_DSA_PRIVATE_KEY;

/* Information data structure used by FIPS SHA Random number generator */
typedef struct {
ITEM prime;
ITEM seed;
} A_SHA_RANDOM_PARAMS;

#ifdef __cplusplus
}
#endif

#endif
