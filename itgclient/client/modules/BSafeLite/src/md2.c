/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "global.h"
#include "algae.h"
#include "md2.h"

static void MD2Transform PROTO_LIST
  ((unsigned char [16], unsigned char [16], unsigned char [16]));

/* Permutation of 0..255 constructed from the digits of pi. It gives a
   "random" nonlinear byte substitution operation.
 */
static unsigned char PI_SUBST[256] = {
  41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6,
  19, 98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188,
  76, 130, 202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24,
  138, 23, 229, 18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251,
  245, 142, 187, 47, 238, 122, 169, 104, 121, 145, 21, 178, 7, 63,
  148, 194, 16, 137, 11, 34, 95, 33, 128, 127, 93, 154, 90, 144, 50,
  39, 53, 62, 204, 231, 191, 247, 151, 3, 255, 25, 48, 179, 72, 165,
  181, 209, 215, 94, 146, 42, 172, 86, 170, 198, 79, 184, 56, 210,
  150, 164, 125, 182, 118, 252, 107, 226, 156, 116, 4, 241, 69, 157,
  112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230, 45, 168, 2, 27,
  96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64, 126, 15,
  85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
  234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65,
  129, 77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123,
  8, 12, 189, 177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233,
  203, 213, 254, 59, 0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228,
  166, 119, 114, 248, 235, 117, 75, 10, 49, 68, 80, 180, 143, 237,
  31, 26, 219, 153, 141, 51, 159, 17, 131, 20
};

/* MD2 initialization. Begins an MD2 operation, writing a new context.
 */
void A_MD2Init (context)
A_MD2_CTX *context;
{
  T_memset ((POINTER)context, 0, sizeof (*context));
}

/* MD2 block update operation. Continues an MD2 message-digest
     operation, processing another message block, and updating the
     context.
 */
void A_MD2Update (context, input, inputLen)
A_MD2_CTX *context;
unsigned char *input;                                         /* input block */
unsigned int inputLen;                              /* length of input block */
{
  unsigned int i, index, partLen;

  /* Update number of bytes mod 16 */
  index = context->count;
  context->count = (index + inputLen) & 0xf;
  
  partLen = 16 - index;

  /* Transform as many times as possible.
    */
  if (inputLen >= partLen) {
    T_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
    MD2Transform (context->state, context->checksum, context->buffer);

    for (i = partLen; i + 15 < inputLen; i += 16)
      MD2Transform (context->state, context->checksum, &input[i]);

    index = 0;
  }
  else
    i = 0;
  
  /* Buffer remaining input */
  T_memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD2 finalization. Ends an MD2 message-digest operation, writing the
     message digest and zeroizing the context.
   Assume digest buffer is at least A_MD2_DIGEST_LEN.
 */
void A_MD2Final (context, digest)
A_MD2_CTX *context;
unsigned char *digest;
{
  unsigned char pad[16];
  unsigned int index, padLen;

  /* Pad out to multiple of 16.
   */
  index = context->count;
  padLen = 16 - index;
  T_memset ((POINTER)pad, padLen, padLen);
  A_MD2Update (context, pad, padLen);

  /* Extend with checksum */
  A_MD2Update (context, context->checksum, 16);
  
  /* Store state in digest */
  T_memcpy ((POINTER)digest, (POINTER)context->state, 16);
  
  /* Restart the context. */
  A_MD2Init (context);
}

/* MD2 basic transformation. Transforms state and updates checksum
     based on block.
 */
static void MD2Transform (state, checksum, block)
unsigned char state[16];
unsigned char checksum[16];
unsigned char block[16];
{
  unsigned int i, j, t;
  unsigned char x[48];
  
  /* Form encryption block from state, block, state ^ block.
   */
  T_memcpy ((POINTER)x, (POINTER)state, 16);
  T_memcpy ((POINTER)x+16, (POINTER)block, 16);
  for (i = 0; i < 16; i++)
    x[i+32] = state[i] ^ block[i];
  
  /* Encrypt block (18 rounds).
   */
  t = 0;
  for (i = 0; i < 18; i++) {
    for (j = 0; j < 48; j++)
      t = x[j] ^= PI_SUBST[t];
    t = (t + i) & 0xff;
  }

  /* Save new state */
  T_memcpy ((POINTER)state, (POINTER)x, 16);

  /* Update checksum.
   */
  t = checksum[15];
  for (i = 0; i < 16; i++)
    t = checksum[i] ^= PI_SUBST[block[i] ^ t];

  /* Zeroize sensitive information.
   */
  T_memset ((POINTER)x, 0, sizeof (x));
}

