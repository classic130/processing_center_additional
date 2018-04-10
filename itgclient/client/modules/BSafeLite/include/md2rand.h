/* Copyright (C) RSA Data Security, Inc. created 1994.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _MD2RAND_H_
#define _MD2RAND_H_ 1

#include "digrand.h"
#include "md2.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct A_MD2_RANDOM_CTX {
  A_DigestRandom digestRandom;                               /* "base class" */
  
  unsigned char state[3 * A_MD2_DIGEST_LEN];
  A_MD2_CTX md2Context;
} A_MD2_RANDOM_CTX;

void A_MD2RandomInit PROTO_LIST ((A_MD2_RANDOM_CTX *));
void A_MD2RandomUpdate PROTO_LIST
  ((A_MD2_RANDOM_CTX *, unsigned char *, unsigned int));
void A_MD2RandomGenerateBytes PROTO_LIST
  ((A_MD2_RANDOM_CTX *, unsigned char *, unsigned int));

#ifdef __cplusplus
}
#endif

#endif
