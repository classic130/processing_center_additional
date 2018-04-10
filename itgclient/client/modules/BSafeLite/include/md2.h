/* Copyright (C) RSA Data Security, Inc. created 1994.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _MD2_H_
#define _MD2_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

#define A_MD2_DIGEST_LEN 16

typedef struct {
  unsigned char state[16];                                          /* state */
  unsigned char checksum[16];                                    /* checksum */
  unsigned int count;                          /* number of bytes, modulo 16 */
  unsigned char buffer[16];                                  /* input buffer */
} A_MD2_CTX;

void A_MD2Init PROTO_LIST ((A_MD2_CTX *));
void A_MD2Update PROTO_LIST ((A_MD2_CTX *, unsigned char *, unsigned int));
void A_MD2Final PROTO_LIST ((A_MD2_CTX *, unsigned char *));

#ifdef __cplusplus
}
#endif

#endif
