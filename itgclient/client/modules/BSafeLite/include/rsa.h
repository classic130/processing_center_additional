/* Copyright (C) RSA Data Security, Inc. created 1994.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#ifndef _RSA_H_
#define _RSA_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* Note, these are only valid after a call to A_RSAInit.
 */
#define A_RSA_BLOCK_LEN(context) ((context)->blockLen)
#define A_RSA_MAX_OUTPUT_LEN(context, inputLen)\
  (inputLen) + (((inputLen) % (context)->blockLen) ?\
                (context)->blockLen - ((inputLen) % (context)->blockLen) : 0)

typedef struct {
  unsigned int blockLen;          /* total size for the block to be computed */
  unsigned char *input;
  unsigned int inputLen;
  CMPInt modulus;
  CMPInt exponent;
} A_RSA_CTX;

int ALG_RSAInit (A_RSA_CTX *, A_RSA_KEY *);
void ALG_RSAContextDestroy (A_RSA_CTX *);
int ALG_RSAUpdate (A_RSA_CTX *, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int, A_SURRENDER_CTX *);
int ALG_RSAFinal (A_RSA_CTX *);

#ifdef __cplusplus
}
#endif

#endif
