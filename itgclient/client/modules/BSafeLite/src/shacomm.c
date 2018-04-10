/* Copyright (C) RSA Data Security, Inc. created 1993.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "bsafelite.h"
#include "shacomm.h"

/* SHA initialization. Begins an SHA operation, writing a new context.
 */
void A_SHAInitCommon (A_SHA_COMM_CTX *context)
{
  context->count[0] = context->count[1] = 0;

  /* Load magic initialization constants.
   */
  context->state[0] = 0x67452301l;
  context->state[1] = 0xefcdab89l;
  context->state[2] = 0x98badcfel;
  context->state[3] = 0x10325476l;
  context->state[4] = 0xc3d2e1f0l;
}

/* SHA block update operation. Continues an SHA message-digest
     operation, processing another message block, and updating the
     context.
 */
void A_SHAUpdateCommon (
A_SHA_COMM_CTX *context,
unsigned char *partIn,
unsigned int partInLen,
A_SHA_TRANSFORM *Transform)
{
  unsigned int bufferLen;

  /* Compute length of buffer */
  bufferLen = (unsigned int)(context->count[1] & 0x3f);

  /* Update number of bytes */
  if ((context->count[1] += partInLen) < partInLen)
    context->count[0]++;

  /* If previous input in buffer, buffer new input and transform if
       possible.
   */
  if (bufferLen > 0 && bufferLen + partInLen >= 64) {
    T_memcpy
      ((POINTER)context->buffer+bufferLen, (POINTER)partIn, 64-bufferLen);
    partIn += (64-bufferLen);
    partInLen -= (64-bufferLen);
    (*Transform) (context->state, context->buffer);
    bufferLen = 0;
  }

  /* Transform directly from input.
   */
  while (partInLen >= 64) {
    (*Transform) (context->state, partIn);
    partIn += 64;
    partInLen -= 64;
  }

  /* Buffer remaining input */
  T_memcpy ((POINTER)(context->buffer+bufferLen), (POINTER)partIn, partInLen);
}

/* SHA finalization. Ends an SHA message-digest operation, writing
     the message digest and zeroizing the context.
 */
void A_SHAFinalCommon (
A_SHA_COMM_CTX *context,
unsigned char digest[A_SHA_DIGEST_LEN],
A_SHA_TRANSFORM *Transform)
{
  UINT4 bitCount[2];
  unsigned char pad[72];
  unsigned int padLen;

  /* Compute padding: 80 00 00 ... 00 00 <bit count>
   */
  padLen = 64 - (unsigned int)(context->count[1] & 0x3f);
  if (padLen <= 8)
    padLen += 64;
  pad[0] = 0x80;
  T_memset ((POINTER)(pad+1), 0, padLen-7);
  bitCount[0] = (context->count[0] << 3) | (context->count[1] >> 29);
  bitCount[1] = context->count[1] << 3;
  UINT4ToBigEndian (pad+padLen-8, bitCount, 2);

  /* Digest padding */
  A_SHAUpdateCommon (context, pad, padLen, Transform);

  /* Store digest */
  UINT4ToBigEndian (digest, context->state, 5);

  /* Restart the context */
  A_SHAInitCommon (context);
}
