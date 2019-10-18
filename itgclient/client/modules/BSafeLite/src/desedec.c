/* Copyright (C) RSA Data Security, Inc. created 1991.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#include "global.h"
#include "algae.h"
#include "desedec.h"

#define THE_DES_EDE3_CONTEXT ((DES_EDE3_CTX *)desedeCtx)

void DES_EDE (desedeCtx, out, in)
POINTER desedeCtx;
unsigned char *out;
unsigned char *in;
{
  DES ((POINTER)&THE_DES_EDE3_CONTEXT->desContext1, out, in);
  DES ((POINTER)&THE_DES_EDE3_CONTEXT->desContext2, out, out);
  DES ((POINTER)&THE_DES_EDE3_CONTEXT->desContext3, out, out);
}

