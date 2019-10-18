/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "global.h"
#include "algae.h"
#include "secrcbc.h"

/* On first call, it is assumed that *remainderLen is zero.
   Returns AE_OUTPUT_LEN, 0.
 */
int SecretCBCEncryptUpdate
  (thisCtx, algCtx, SecretEncrypt, output, outputLen, maxOutputLen,
   input, inputLen)
A_CBC_CTX *thisCtx;
POINTER algCtx;
SECRET_CRYPT SecretEncrypt;
unsigned char *output;
unsigned int *outputLen;
unsigned int maxOutputLen;
unsigned char *input;
unsigned int inputLen;
{
  unsigned int partialLen, totalLen;
  int i;
  unsigned char *p, *q;
  UINT4  localBuffer[2];  /* 8 bytes of aligned storage. */

  totalLen = thisCtx->remainderLen + inputLen;

  /* Output length will be all available 8-byte blocks.
   */
  if ((*outputLen = 8 * (totalLen / 8)) > maxOutputLen)
    return (AE_OUTPUT_LEN);
  
  if (totalLen < 8) {
    /* Not enough to encrypt, just accumulate into remainder.
     */
	p = thisCtx->remainder + thisCtx->remainderLen;
	q = input;
	i = inputLen;
	while (i-- > 0)  {
	  *p++ = *q++;
      }
    thisCtx->remainderLen = totalLen;
    
    return (0);
  }
  
  /* Accumulate enough bytes from input into remainder to encrypt the
       remainder.
   */
  p = thisCtx->remainder + thisCtx->remainderLen;
  q = input;
  i = partialLen = 8 - thisCtx->remainderLen;
  while (i-- > 0)  {
    *p++ = *q++;
     }
  ((UINT4 *)thisCtx->remainder)[0] ^= ((UINT4 *)thisCtx->xorBlock)[0];
  ((UINT4 *)thisCtx->remainder)[1] ^= ((UINT4 *)thisCtx->xorBlock)[1];

  /* Encrypt in place */
  (*SecretEncrypt) (algCtx, (UINT1 *)localBuffer, thisCtx->remainder);
  ((UINT4 *)thisCtx->xorBlock)[0] = localBuffer[0];
  ((UINT4 *)thisCtx->xorBlock)[1] = localBuffer[1];
  STORE_8_UNALIGNED(localBuffer, output);
  thisCtx->remainderLen = 0;
  input += partialLen;
  inputLen -= partialLen;
  output += 8;

  /* Now encrypt the bulk of the input.
   */
  while (inputLen >= 8) {
    LOAD_8_UNALIGNED(localBuffer, input);
    localBuffer[0] ^= ((UINT4 *)thisCtx->xorBlock)[0];
    localBuffer[1] ^= ((UINT4 *)thisCtx->xorBlock)[1];
    /* Encrypt in place */
    (*SecretEncrypt) (algCtx, (UINT1 *)localBuffer, (UINT1 *)localBuffer);
    ((UINT4 *)thisCtx->xorBlock)[0] = localBuffer[0];
    ((UINT4 *)thisCtx->xorBlock)[1] = localBuffer[1];
    STORE_8_UNALIGNED(localBuffer, output);
 	input += 8;
    inputLen -= 8;
    output += 8;
  }

  /* inputLen is now < 8, so copy input to remainder.
   */
  p = thisCtx->remainder;
  q = input;
  i = inputLen;
  while (i-- > 0)  {
    *p++ = *q++;
    }
  thisCtx->remainderLen = inputLen;
   
  return (0);
}

/* This just ensures that *remainderLen is zero.
   Returns AE_INPUT_LEN, 0.
 */
int SecretCBCEncryptFinal (thisCtx)
A_CBC_CTX *thisCtx;
{
  int status = 0;

  if (thisCtx->remainderLen != 0)
    status = AE_INPUT_LEN;
  
  SecretCBCRestart (thisCtx);
  return (status);
}
