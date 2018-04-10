/* Copyright (C) RSA Data Security, Inc. created 1994.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _RSAKEYGN_H_
#define _RSAKEYGN_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* Need randomBlock to hold bytes for two prime numbers, each of
     length RSA_PRIME_BITS (modulusBits). Previous BSAFE versions
     relied on 16 bit words. In order to remain compatible, the
     following definition looks funny. */
#define A_RSA_KEY_GEN_RANDOM_BLOCK_LEN(modulusBits) \
  (4 * (((RSA_PRIME_BITS (modulusBits)) >> 4) + 1))

typedef struct {
  unsigned int modulusBits;
  CMPInt cmpModulus;
  CMPInt cmpPublicExponent;
  CMPInt cmpPrivateExponent;
  CMPInt cmpPrime1;
  CMPInt cmpPrime2;
  CMPInt cmpExponentP;
  CMPInt cmpExponentQ;
  CMPInt cmpCoefficient;
  A_PKCS_RSA_PRIVATE_KEY result;
  unsigned char *resultBuffer;           
  int bufSize;
} A_RSA_KEY_GEN_CTX;

int ALG_RSAKeyGenInit(A_RSA_KEY_GEN_CTX *, A_RSA_KEY_GEN_PARAMS *);
void ALG_RSAKeyGenContextDestroy(A_RSA_KEY_GEN_CTX *);
int ALG_RSAKeyGen(A_RSA_KEY_GEN_CTX  *, A_PKCS_RSA_PRIVATE_KEY **, 
                  unsigned char *, A_SURRENDER_CTX *);

#ifdef __cplusplus
}
#endif

#endif
