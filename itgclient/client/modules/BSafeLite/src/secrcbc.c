/* Copyright (C) RSA Data Security, Inc. created 1995.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "global.h"
#include "algae.h"
#include "secrcbc.h"

void SecretCBCRestart (thisCtx)
A_CBC_CTX *thisCtx;
{
  T_memcpy ((POINTER)thisCtx->xorBlock, (POINTER)thisCtx->iv, 8);
  thisCtx->remainderLen = 0;
}


void SecretCBCInit (thisCtx, iv, mode)
A_CBC_CTX *thisCtx;
unsigned char *iv;
int mode;
{
  T_memcpy ((POINTER)thisCtx->iv, (POINTER)iv, 8);
  T_memcpy ((POINTER)thisCtx->xorBlock, (POINTER)iv, 8);
  thisCtx->remainderLen = 0;
  thisCtx->mode = mode;
}

void SecretCBCIVUpdate (thisCtx, iv)
A_CBC_CTX *thisCtx;
unsigned char *iv;
{
  T_memcpy ((POINTER)thisCtx->iv, (POINTER)iv, 8);
}

