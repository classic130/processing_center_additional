/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "global.h"
#include "algae.h"
#include "md5.h"

#ifndef __MD5_TRANS_ASSEMBLY
/* Constants for MD5Transform routine.
 */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static void MD5Transform PROTO_LIST ((UINT4 [4], unsigned char [64]));
static void Decode PROTO_LIST ((UINT4 *, unsigned char *, unsigned int));
#endif /* __MD5_TRANS_ASSEMBLY */

static void Encode PROTO_LIST ((unsigned char *, UINT4 *, unsigned int));

#ifdef __MD5_TRANS_ASSEMBLY
/* If the assembly version exists, it is external to this source code
     file, so take out the static declarator.
 */
void MD5Transform PROTO_LIST ((UINT4 [4], unsigned char [64]));
#endif /* __MD5_TRANS_ASSEMBLY */

#ifndef __MD5_TRANS_ASSEMBLY
/* F, G, H and I are basic MD5 functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
   Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
  }
#endif /* __MD5_TRANS_ASSEMBLY */

/* MD5 initialization. Begins an MD5 operation, writing a new context.
 */
void A_MD5Init (context)
A_MD5_CTX *context;
{
  context->count[0] = context->count[1] = 0;

  /* Load magic initialization constants.
   */
  context->state[0] = 0x67452301l;
  context->state[1] = 0xefcdab89l;
  context->state[2] = 0x98badcfel;
  context->state[3] = 0x10325476l;
}

/* MD5 block update operation. Continues an MD5 message-digest
     operation, processing another message block, and updating the
     context.
 */
void A_MD5Update (context, input, inputLen)
A_MD5_CTX *context;
unsigned char *input;                                         /* input block */
unsigned int inputLen;                              /* length of input block */
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
    context->count[1]++;
  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible.
   */
  if (inputLen >= partLen) {

    /* avoid unnecessary memory copy if context buffer was empty */
    if (partLen < 64) {
      T_memcpy ((POINTER)&context->buffer[index], (POINTER)input, partLen);
      MD5Transform (context->state, context->buffer);
      i = partLen;
    }
    else
      i = 0;
  
    for (; i + 63 < inputLen; i += 64)
      MD5Transform (context->state, &input[i]);
    
    index = 0;
  }
  else
    i = 0;
  
  /* Buffer remaining input */
  T_memcpy ((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
     the message digest and zeroizing the context.
   Assume digest buffer is at least A_MD5_DIGEST_LEN.
 */
void A_MD5Final (context, digest)
A_MD5_CTX *context;
unsigned char *digest;
{
  unsigned char bits[8], pad[64];
  unsigned int index, padLen;

  /* Save number of bits */
  Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64.
   */
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  T_memset ((POINTER)pad, 0, padLen);
  pad[0] = 0x80;
  A_MD5Update (context, pad, padLen);

  /* Append length (before padding) */
  A_MD5Update (context, bits, 8);

  /* Store state in digest */
  Encode (digest, context->state, 16);

  /* Restart the context. */
  A_MD5Init (context);
}

#ifndef __MD5_TRANS_ASSEMBLY
/* MD5 basic transformation. Transforms state based on block.
 */
static void MD5Transform (state, block)
UINT4 state[4];
unsigned char block[64];
{
  UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  Decode (x, block, 64);

  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11, 0xd76aa478l); /* 1 */
  FF (d, a, b, c, x[ 1], S12, 0xe8c7b756l); /* 2 */
  FF (c, d, a, b, x[ 2], S13, 0x242070dbl); /* 3 */
  FF (b, c, d, a, x[ 3], S14, 0xc1bdceeel); /* 4 */
  FF (a, b, c, d, x[ 4], S11, 0xf57c0fafl); /* 5 */
  FF (d, a, b, c, x[ 5], S12, 0x4787c62al); /* 6 */
  FF (c, d, a, b, x[ 6], S13, 0xa8304613l); /* 7 */
  FF (b, c, d, a, x[ 7], S14, 0xfd469501l); /* 8 */
  FF (a, b, c, d, x[ 8], S11, 0x698098d8l); /* 9 */
  FF (d, a, b, c, x[ 9], S12, 0x8b44f7afl); /* 10 */
  FF (c, d, a, b, x[10], S13, 0xffff5bb1l); /* 11 */
  FF (b, c, d, a, x[11], S14, 0x895cd7bel); /* 12 */
  FF (a, b, c, d, x[12], S11, 0x6b901122l); /* 13 */
  FF (d, a, b, c, x[13], S12, 0xfd987193l); /* 14 */
  FF (c, d, a, b, x[14], S13, 0xa679438el); /* 15 */
  FF (b, c, d, a, x[15], S14, 0x49b40821l); /* 16 */

  /* Round 2 */
  GG (a, b, c, d, x[ 1], S21, 0xf61e2562l); /* 17 */
  GG (d, a, b, c, x[ 6], S22, 0xc040b340l); /* 18 */
  GG (c, d, a, b, x[11], S23, 0x265e5a51l); /* 19 */
  GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aal); /* 20 */
  GG (a, b, c, d, x[ 5], S21, 0xd62f105dl); /* 21 */
  GG (d, a, b, c, x[10], S22,  0x2441453l); /* 22 */
  GG (c, d, a, b, x[15], S23, 0xd8a1e681l); /* 23 */
  GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8l); /* 24 */
  GG (a, b, c, d, x[ 9], S21, 0x21e1cde6l); /* 25 */
  GG (d, a, b, c, x[14], S22, 0xc33707d6l); /* 26 */
  GG (c, d, a, b, x[ 3], S23, 0xf4d50d87l); /* 27 */
  GG (b, c, d, a, x[ 8], S24, 0x455a14edl); /* 28 */
  GG (a, b, c, d, x[13], S21, 0xa9e3e905l); /* 29 */
  GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8l); /* 30 */
  GG (c, d, a, b, x[ 7], S23, 0x676f02d9l); /* 31 */
  GG (b, c, d, a, x[12], S24, 0x8d2a4c8al); /* 32 */

  /* Round 3 */
  HH (a, b, c, d, x[ 5], S31, 0xfffa3942l); /* 33 */
  HH (d, a, b, c, x[ 8], S32, 0x8771f681l); /* 34 */
  HH (c, d, a, b, x[11], S33, 0x6d9d6122l); /* 35 */
  HH (b, c, d, a, x[14], S34, 0xfde5380cl); /* 36 */
  HH (a, b, c, d, x[ 1], S31, 0xa4beea44l); /* 37 */
  HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9l); /* 38 */
  HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60l); /* 39 */
  HH (b, c, d, a, x[10], S34, 0xbebfbc70l); /* 40 */
  HH (a, b, c, d, x[13], S31, 0x289b7ec6l); /* 41 */
  HH (d, a, b, c, x[ 0], S32, 0xeaa127fal); /* 42 */
  HH (c, d, a, b, x[ 3], S33, 0xd4ef3085l); /* 43 */
  HH (b, c, d, a, x[ 6], S34,  0x4881d05l); /* 44 */
  HH (a, b, c, d, x[ 9], S31, 0xd9d4d039l); /* 45 */
  HH (d, a, b, c, x[12], S32, 0xe6db99e5l); /* 46 */
  HH (c, d, a, b, x[15], S33, 0x1fa27cf8l); /* 47 */
  HH (b, c, d, a, x[ 2], S34, 0xc4ac5665l); /* 48 */

  /* Round 4 */
  II (a, b, c, d, x[ 0], S41, 0xf4292244l); /* 49 */
  II (d, a, b, c, x[ 7], S42, 0x432aff97l); /* 50 */
  II (c, d, a, b, x[14], S43, 0xab9423a7l); /* 51 */
  II (b, c, d, a, x[ 5], S44, 0xfc93a039l); /* 52 */
  II (a, b, c, d, x[12], S41, 0x655b59c3l); /* 53 */
  II (d, a, b, c, x[ 3], S42, 0x8f0ccc92l); /* 54 */
  II (c, d, a, b, x[10], S43, 0xffeff47dl); /* 55 */
  II (b, c, d, a, x[ 1], S44, 0x85845dd1l); /* 56 */
  II (a, b, c, d, x[ 8], S41, 0x6fa87e4fl); /* 57 */
  II (d, a, b, c, x[15], S42, 0xfe2ce6e0l); /* 58 */
  II (c, d, a, b, x[ 6], S43, 0xa3014314l); /* 59 */
  II (b, c, d, a, x[13], S44, 0x4e0811a1l); /* 60 */
  II (a, b, c, d, x[ 4], S41, 0xf7537e82l); /* 61 */
  II (d, a, b, c, x[11], S42, 0xbd3af235l); /* 62 */
  II (c, d, a, b, x[ 2], S43, 0x2ad7d2bbl); /* 63 */
  II (b, c, d, a, x[ 9], S44, 0xeb86d391l); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  
  /* Zeroize sensitive information.
   */
  T_memset ((POINTER)x, 0, sizeof (x));
}
#endif /* __MD5_TRANS_ASSEMBLY */

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
     a multiple of 4.
 */
static void Encode (output, input, len)
unsigned char *output;
UINT4 *input;
unsigned int len;
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

#ifndef __MD5_TRANS_ASSEMBLY
/* Decodes input (unsigned char) into output (UINT4). Assumes len is
     a multiple of 4.
 */
static void Decode (output, input, len)
UINT4 *output;
unsigned char *input;
unsigned int len;
{
  unsigned int i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
      (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}
#endif /* __MD5_TRANS_ASSEMBLY */
