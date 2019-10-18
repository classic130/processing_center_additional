/* Copyright (C) RSA Data Security, Inc. created 1991.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* Use the THIS_ALG_CBC macro to define the type of object in the
     virtual function prototype.  It defaults to the most base class, but
     derived modules may define the macro to a more derived class before
     including this header file.
 */
struct A_RC2_CBC_CTX;
#define THIS_ALG_CBC struct A_RC2_CBC_CTX

#include "global.h"
#include "algae.h"
#include "rc2cbc.h"

/* Returns 0, AE_NOT_SUPPORTED.
 */
int A_RC2_CBCEncryptInit (thisCtx, key, params, mode)
A_RC2_CBC_CTX *thisCtx;
ITEM *key;
A_RC2_CBC_PARAMS *params;
int mode;
{
  int status;

  if ((status = RC2Init (&thisCtx->rc2Context, key, params->effectiveKeyBits))
      != 0)
    return (status);

  SecretCBCInit (thisCtx, params->iv, mode);
  return (0);
}

/* Returns AE_OUTPUT_LEN, 0.
 */
int A_RC2_CBCEncryptUpdate
  (thisCtx, partOut, partOutLen, maxPartOutLen, partIn, partInLen)
A_RC2_CBC_CTX *thisCtx;
unsigned char *partOut;
unsigned int *partOutLen;
unsigned int maxPartOutLen;
unsigned char *partIn;
unsigned int partInLen;
{
  return (SecretCBCEncryptUpdate
          (thisCtx, (POINTER)&thisCtx->rc2Context, RC2Encrypt, partOut,
           partOutLen, maxPartOutLen, partIn, partInLen));
}

/* Returns AE_INPUT_LEN, 0.
 */
int A_RC2_CBCEncryptFinal (thisCtx)
A_RC2_CBC_CTX *thisCtx;
{
  return (SecretCBCEncryptFinal (thisCtx));
}


