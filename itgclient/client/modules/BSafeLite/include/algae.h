/* Copyright (C) RSA Data Security, Inc. created 1992.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _ALGAE_H_
#define _ALGAE_H_ 1

#ifndef CALL_CONV
#define CALL_CONV
#endif

#include "atypes.h"

#ifndef _STD_ALLOC_FUNCS_
#define _STD_ALLOC_FUNCS_
#endif

#ifndef _STD_MEM_FUNCS_
#define _STD_MEM_FUNCS_
#endif
#include "stdlibrf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define AE_CANCEL 0x0001
#define AE_DATA 0x0002
#define AE_EXPONENT_EVEN 0x0003
#define AE_EXPONENT_LEN 0x0004
#define AE_INPUT_DATA 0x0005
#define AE_INPUT_LEN 0x0006
#define AE_MODULUS_LEN 0x0007
#define AE_NEED_RANDOM 0x0008
#define AE_NOT_SUPPORTED 0x0009
#define AE_OUTPUT_LEN 0x000a
#define AE_NOT_INITIALIZED 0x000b
#define AE_KEY_LEN 0x000c
#define AE_KEY_INFO 0x000d
#define AE_SEQUENCE 0x000e
#define AE_PARAMS 0x000f
#define AE_ALLOC 0x0080

unsigned int CALL_CONV A_IntegerBits PROTO_LIST
  ((unsigned char *, unsigned int));

int CALL_CONV ALG_ErrorCode PROTO_LIST ((int));

#ifdef __cplusplus
}
#endif

#endif
