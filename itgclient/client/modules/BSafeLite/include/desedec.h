/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _DESEDEC_H_
#define _DESEDEC_H_ 1

#include "des.h"
#include "secrcbc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define A_DES_EDE3_CBC_MAX_OUT_LEN(inputLen) ((((inputLen) + 7) / 8) * 8)
#define A_DES_EDE3_CBC_BLOCK_LEN 8

typedef struct {
  DES_CTX desContext1;                                  /* DES context for k1*/
  DES_CTX desContext2;                                  /* DES context for k2*/
  DES_CTX desContext3;                                  /* DES context for k3*/
} DES_EDE3_CTX;

typedef struct A_DES_EDE3_CBC_CTX {
  A_CBC_CTX cbc;
  DES_EDE3_CTX desEDE3Context;
} A_DES_EDE3_CBC_CTX;

void A_DES_EDE3_CBCEncryptInit PROTO_LIST
  ((A_DES_EDE3_CBC_CTX *, unsigned char *, unsigned char *, int));
int A_DES_EDE3_CBCEncryptUpdate PROTO_LIST
  ((A_DES_EDE3_CBC_CTX *, unsigned char *, unsigned int*, unsigned int,
    unsigned char *, unsigned int));
int A_DES_EDE3_CBCEncryptFinal PROTO_LIST ((A_DES_EDE3_CBC_CTX *));

void A_DES_EDE3_CBCDecryptInit PROTO_LIST
  ((A_DES_EDE3_CBC_CTX *, unsigned char *, unsigned char *, int));
int A_DES_EDE3_CBCDecryptUpdate PROTO_LIST
  ((A_DES_EDE3_CBC_CTX *, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int));
int A_DES_EDE3_CBCDecryptFinal PROTO_LIST
  ((A_DES_EDE3_CBC_CTX *, unsigned char *, unsigned int *, unsigned int));

void DES_EDE PROTO_LIST ((POINTER, unsigned char *, unsigned char *));

#ifdef __cplusplus
}
#endif

#endif
