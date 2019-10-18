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
struct A_DES_EDE3_CBC_CTX;
#define THIS_ALG_CBC struct A_DES_EDE3_CBC_CTX

#include "global.h"
#include "algae.h"
#include "desedec.h"

/* key must be 24 bytes key and 8 bytes iv
*/
void A_DES_EDE3_CBCEncryptInit (thisCtx, key, iv, mode)
A_DES_EDE3_CBC_CTX *thisCtx;
unsigned char *key;
unsigned char *iv;
int mode;
{
  DESEncryptInit (&thisCtx->desEDE3Context.desContext1, (POINTER)key);
  DESDecryptInit (&thisCtx->desEDE3Context.desContext2, (POINTER)(key + 8));
  DESEncryptInit (&thisCtx->desEDE3Context.desContext3, (POINTER)(key + 16));

  /* call parent class to initialize */
  SecretCBCInit (thisCtx, iv, mode);
}

/* Returns AE_OUTPUT_LEN, 0.
 */
int A_DES_EDE3_CBCEncryptUpdate
  (thisCtx, partOut, partOutLen, maxPartOutLen, partIn, partInLen)
A_DES_EDE3_CBC_CTX *thisCtx;
unsigned char *partOut;
unsigned int *partOutLen;
unsigned int maxPartOutLen;
unsigned char *partIn;
unsigned int partInLen;
{
  return (SecretCBCEncryptUpdate
          (thisCtx, (POINTER)&thisCtx->desEDE3Context, DES_EDE, partOut,
           partOutLen, maxPartOutLen, partIn, partInLen));
}

/* Returns AE_INPUT_LEN, 0.
 */
int A_DES_EDE3_CBCEncryptFinal (thisCtx)
A_DES_EDE3_CBC_CTX *thisCtx;
{
  return (SecretCBCEncryptFinal (thisCtx));
}
