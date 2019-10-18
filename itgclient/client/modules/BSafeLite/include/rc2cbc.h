/* Copyright (C) RSA Data Security, Inc. created 1991.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _RC2CBC_H_
#define _RC2CBC_H_ 1

#include "rc2.h"
#include "secrcbc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define A_RC2_CBC_MAX_OUT_LEN(inputLen) ((((inputLen) + 7) / 8) * 8)
#define A_RC2_CBC_BLOCK_LEN 8


typedef struct A_RC2_CBC_CTX {
  A_CBC_CTX cbc;
  RC2_CTX rc2Context;
} A_RC2_CBC_CTX;

int A_RC2_CBCEncryptInit PROTO_LIST
  ((A_RC2_CBC_CTX *, ITEM *, A_RC2_CBC_PARAMS *, int));
int A_RC2_CBCEncryptUpdate PROTO_LIST
  ((A_RC2_CBC_CTX *, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int));
int A_RC2_CBCEncryptFinal PROTO_LIST ((A_RC2_CBC_CTX *));
int A_RC2_CBCDecryptInit PROTO_LIST
  ((A_RC2_CBC_CTX *, ITEM *, A_RC2_CBC_PARAMS *, int));
int A_RC2_CBCDecryptUpdate PROTO_LIST
  ((A_RC2_CBC_CTX *, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int));
int A_RC2_CBCDecryptFinal PROTO_LIST
  ((A_RC2_CBC_CTX *, unsigned char *, unsigned int *, unsigned int));

#ifdef __cplusplus
}
#endif

#endif
