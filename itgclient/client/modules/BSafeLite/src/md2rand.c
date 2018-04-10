/* Copyright (C) RSA Data Security, Inc. created 1994.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* Define this so that the type of the 'this' pointer in the
     virtual functions will be correct for this derived class.
 */
struct A_MD2_RANDOM_CTX;
#define THIS_DIGEST_RANDOM struct A_MD2_RANDOM_CTX

#include "global.h"
#include "algae.h"
#include "md2rand.h"

static void A_MD2RandomDigestUpdate PROTO_LIST
  ((A_MD2_RANDOM_CTX *, unsigned char *, unsigned int));
static void A_MD2RandomDigestFinal PROTO_LIST
  ((A_MD2_RANDOM_CTX *, unsigned char *));

#if !GLOBAL_FUNCTION_POINTERS
static A_DigestRandomVTable V_TABLE;
#else
static A_DigestRandomVTable V_TABLE =
  {A_MD2RandomDigestUpdate, A_MD2RandomDigestFinal};
#endif

void A_MD2RandomInit (context)
A_MD2_RANDOM_CTX *context;
{
  /* Initialize "base class" */
  A_DigestRandomInit
    (&context->digestRandom, A_MD2_DIGEST_LEN, context->state);

  /* Initialize digest algorithm and set vTable.
   */
  A_MD2Init (&context->md2Context);
  context->digestRandom.vTable = &V_TABLE;

#if !GLOBAL_FUNCTION_POINTERS
  A_DigestRandomVTableInit
      (&V_TABLE, A_MD2RandomDigestUpdate, A_MD2RandomDigestFinal);
#endif
}

void A_MD2RandomUpdate (context, input, inputLen)
A_MD2_RANDOM_CTX *context;
unsigned char *input;
unsigned int inputLen;
{
  A_DigestRandomUpdate (&context->digestRandom, input, inputLen);
}

void A_MD2RandomGenerateBytes (context, output, outputLen)
A_MD2_RANDOM_CTX *context;
unsigned char *output;
unsigned int outputLen;
{
  A_DigestRandomGenerateBytes (&context->digestRandom, output, outputLen);
}

static void A_MD2RandomDigestUpdate (context, input, inputLen)
A_MD2_RANDOM_CTX *context;
unsigned char *input;
unsigned int inputLen;
{
  A_MD2Update (&context->md2Context, input, inputLen);
}

static void A_MD2RandomDigestFinal (context, digest)
A_MD2_RANDOM_CTX *context;
unsigned char *digest;
{
  A_MD2Final (&context->md2Context, digest);
}
