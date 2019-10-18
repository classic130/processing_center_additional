/* Copyright (C) RSA Data Security, Inc. created 1993.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "bsafelite.h"
#include "sha.h"


/* F, G, H and I are basic SHA functions.
 */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) ((x) ^ (y) ^ (z))
#define H(x, y, z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define I(x, y, z) ((x) ^ (y) ^ (z))

/* ROTATE_LEFT rotates x left n bits.
 */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
 */
#define ROUND(a, b, c, d, e, x, F, k) { \
    (e) += ROTATE_LEFT ((a), 5) + F ((b), (c), (d)) + (x) + k; \
    (b) = ROTATE_LEFT ((b), 30); \
  }
#define FF(a, b, c, d, e, x) ROUND (a, b, c, d, e, x, F, 0x5a827999l);
#define GG(a, b, c, d, e, x) ROUND (a, b, c, d, e, x, G, 0x6ed9eba1l);
#define HH(a, b, c, d, e, x) ROUND (a, b, c, d, e, x, H, 0x8f1bbcdcl);
#define II(a, b, c, d, e, x) ROUND (a, b, c, d, e, x, I, 0xca62c1d6l);
     
static void SHATransform (UINT4 [5], unsigned char [64]);
static void SHAExpand (UINT4 [80]);

void A_SHAInit (A_SHA_CTX *context)
{
  A_SHAInitCommon (&context->commonContext);
}

void A_SHAUpdate (
A_SHA_CTX *context,
unsigned char *partIn,
unsigned int partInLen)
{
  A_SHAUpdateCommon (&context->commonContext, partIn, partInLen, SHATransform);
}

void A_SHAFinal (
A_SHA_CTX *context,
unsigned char digest[A_SHA_DIGEST_LEN])
{
  A_SHAFinalCommon (&context->commonContext, digest, SHATransform);
}

static void SHATransform (
UINT4 state[5],
unsigned char block[64]) 
{
  register UINT4 a = state[0], b = state[1], c = state[2], d = state[3],
    e = state[4];
  UINT4 x[80];

  UINT4FromBigEndian (x, 16, block);
  SHAExpand (x);

  /* Round 1 */
  FF (a, b, c, d, e, x[ 0]);
  FF (e, a, b, c, d, x[ 1]);
  FF (d, e, a, b, c, x[ 2]);
  FF (c, d, e, a, b, x[ 3]);
  FF (b, c, d, e, a, x[ 4]);
  FF (a, b, c, d, e, x[ 5]);
  FF (e, a, b, c, d, x[ 6]);
  FF (d, e, a, b, c, x[ 7]);
  FF (c, d, e, a, b, x[ 8]);
  FF (b, c, d, e, a, x[ 9]);
  FF (a, b, c, d, e, x[10]);
  FF (e, a, b, c, d, x[11]);
  FF (d, e, a, b, c, x[12]);
  FF (c, d, e, a, b, x[13]);
  FF (b, c, d, e, a, x[14]);
  FF (a, b, c, d, e, x[15]);
  FF (e, a, b, c, d, x[16]);
  FF (d, e, a, b, c, x[17]);
  FF (c, d, e, a, b, x[18]);
  FF (b, c, d, e, a, x[19]);

  /* Round 2 */
  GG (a, b, c, d, e, x[20]);
  GG (e, a, b, c, d, x[21]);
  GG (d, e, a, b, c, x[22]);
  GG (c, d, e, a, b, x[23]);
  GG (b, c, d, e, a, x[24]);
  GG (a, b, c, d, e, x[25]);
  GG (e, a, b, c, d, x[26]);
  GG (d, e, a, b, c, x[27]);
  GG (c, d, e, a, b, x[28]);
  GG (b, c, d, e, a, x[29]);
  GG (a, b, c, d, e, x[30]);
  GG (e, a, b, c, d, x[31]);
  GG (d, e, a, b, c, x[32]);
  GG (c, d, e, a, b, x[33]);
  GG (b, c, d, e, a, x[34]);
  GG (a, b, c, d, e, x[35]);
  GG (e, a, b, c, d, x[36]);
  GG (d, e, a, b, c, x[37]);
  GG (c, d, e, a, b, x[38]);
  GG (b, c, d, e, a, x[39]); 

  /* Round 3 */
  HH (a, b, c, d, e, x[40]);
  HH (e, a, b, c, d, x[41]);
  HH (d, e, a, b, c, x[42]);
  HH (c, d, e, a, b, x[43]);
  HH (b, c, d, e, a, x[44]);
  HH (a, b, c, d, e, x[45]);
  HH (e, a, b, c, d, x[46]);
  HH (d, e, a, b, c, x[47]);
  HH (c, d, e, a, b, x[48]);
  HH (b, c, d, e, a, x[49]);
  HH (a, b, c, d, e, x[50]);
  HH (e, a, b, c, d, x[51]);
  HH (d, e, a, b, c, x[52]);
  HH (c, d, e, a, b, x[53]);
  HH (b, c, d, e, a, x[54]);
  HH (a, b, c, d, e, x[55]);
  HH (e, a, b, c, d, x[56]);
  HH (d, e, a, b, c, x[57]);
  HH (c, d, e, a, b, x[58]);
  HH (b, c, d, e, a, x[59]);

  /* Round 4 */
  II (a, b, c, d, e, x[60]);
  II (e, a, b, c, d, x[61]);
  II (d, e, a, b, c, x[62]);
  II (c, d, e, a, b, x[63]);
  II (b, c, d, e, a, x[64]);
  II (a, b, c, d, e, x[65]);
  II (e, a, b, c, d, x[66]);
  II (d, e, a, b, c, x[67]);
  II (c, d, e, a, b, x[68]);
  II (b, c, d, e, a, x[69]);
  II (a, b, c, d, e, x[70]);
  II (e, a, b, c, d, x[71]);
  II (d, e, a, b, c, x[72]);
  II (c, d, e, a, b, x[73]);
  II (b, c, d, e, a, x[74]);
  II (a, b, c, d, e, x[75]);
  II (e, a, b, c, d, x[76]);
  II (d, e, a, b, c, x[77]);
  II (c, d, e, a, b, x[78]);
  II (b, c, d, e, a, x[79]);

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;

  /* Zeroize potentially sensitive information.
   */
  T_memset ((POINTER)x, 0, sizeof (x));
}

/* Expands x[0..15] into x[16..79], according to the recurrence
     x[i] = S1(x[i-3] ^ x[i-8] ^ x[i-14] ^ x[i-16])
 */
static void SHAExpand (UINT4 x[80])
{
  register unsigned int i;
  register UINT4 temp;
  register UINT4 *w = x;

  for (i = 16; i < 80; i++) {
    temp = w[i-3] ^ w[i-8] ^ w[i-14] ^ w[i-16];
    w[i] = ROTATE_LEFT(temp, 1);
  }
}
