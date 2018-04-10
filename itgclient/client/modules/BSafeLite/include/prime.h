/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#ifndef _PRIME_H_
#define _PRIME_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

int ALG_GeneratePrimeRoster
  (CMPInt *, CMPInt *, unsigned int, unsigned char *);
int ALG_PrimeFind
  (unsigned char *, unsigned int, CMPInt *, CMPInt *, A_SURRENDER_CTX *);
int ALG_PseudoPrime
  (CMPInt *, unsigned int *, A_SURRENDER_CTX *);

#ifdef __cplusplus
}
#endif

#endif
