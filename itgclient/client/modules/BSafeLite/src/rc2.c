/* Copyright (C) RSA Data Security, Inc. created 1987.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#include "global.h"
#include "algae.h"
#include "rc2.h"

#define KSTYPE UINT4

/* ROTATE_LEFT rotates x left n bits, ROTATE_RIGHT rotates x right n bits.
 */
#define ROTATE16_LEFT(x, n)   ( ((x) << (n)) | ( ((UINT2)(x)) >> (16-(n)) ) )
#define ROTATE16_RIGHT(x, n)  ROTATE16_LEFT(x, (16-(n)))

/* Forward and reverse mixing operations.
 */
#define FMIX(a, b, c, d, t, s) { \
  (a) += (t); \
  (w)  = ((d) & (c)) + ((~(d)) & (b)); \
  (a) += (w); \
  (a) = ROTATE16_LEFT ((a), (s)); \
}
#define RMIX(a, b, c, d, t, s) { \
  (a) = ROTATE16_RIGHT ((a), (s)); \
  (a) -= (t + ((d) & (c)) + (~(d) & (b))); \
}

/* Forward and reverse mashing operations.
 */
#define FMASH(a, d, table) (a) += table[ (int)((d) & 0x3f) ];
#define RMASH(a, d, table) (a) -= table[ (int)((d) & 0x3f) ];

/* PI_SUBST is pseudorandom permutation for expanding key */
static unsigned char PI_SUBST[256] = { 
  217,120,249,196, 25,221,181,237, 40,233,253,121, 74,160,216,157,
  198,126, 55,131, 43,118, 83,142, 98, 76,100,136, 68,139,251,162,
   23,154, 89,245,135,179, 79, 19, 97, 69,109,141,  9,129,125, 50,
  189,143, 64,235,134,183,123, 11,240,149, 33, 34, 92,107, 78,130,
   84,214,101,147,206, 96,178, 28,115, 86,192, 20,167,140,241,220,
   18,117,202, 31, 59,190,228,209, 66, 61,212, 48,163, 60,182, 38,
  111,191, 14,218, 70,105,  7, 87, 39,242, 29,155,188,148, 67,  3,
  248, 17,199,246,144,239, 62,231,  6,195,213, 47,200,102, 30,215,
    8,232,234,222,128, 82,238,247,132,170,114,172, 53, 77,106, 42,
  150, 26,210,113, 90, 21, 73,116, 75,159,208, 94,  4, 24,164,236,
  194,224, 65,110, 15, 81,203,204, 36,145,175, 80,161,244,112, 57,
  153,124, 58,133, 35,184,180,122,252,  2, 54, 91, 37, 85,151, 49,
   45, 93,250,152,227,138,146,174,  5,223, 41, 16,103,108,186,201,
  211,  0,230,207,225,158,168, 44, 99, 22,  1, 63, 88,226,137,169,
   13, 56, 52, 27,171, 51,255,176,187, 72, 12, 95,185,177,205, 46,
  197,243,219, 71,229,165,156,119, 10,166, 32,104,254,127,193,173
};

#ifndef RC2_INIT_ASSEMBLY
/* This sets up table from key, limiting the effective search space to
     effectiveKeyBits.
 */
int RC2Init (context, key, effectiveKeyBits)
RC2_CTX *context;                                  /* context with key table */
ITEM *key;                                                        /* RC2 key */
unsigned int effectiveKeyBits;                 /* effective key size in bits */
{
  int i, j;
  unsigned char mask, preTable[128];
  unsigned int effectiveKeyLen;

  if ((key->len < 1) || (key->len > 128))
    return (AE_NOT_SUPPORTED);

  if ((effectiveKeyBits < A_MIN_RC2_EFFECTIVE_KEY_BITS) ||
      (effectiveKeyBits > A_MAX_RC2_EFFECTIVE_KEY_BITS))
    return (AE_NOT_SUPPORTED);

  /* Initialize pre-table with key, then expand key forward using
       pseudorandom permutation.
   */
  T_memcpy ((POINTER)preTable, (POINTER)key->data, key->len);
  for (i = key->len; i < 128; i++)
    preTable[i] = PI_SUBST[(preTable[i - 1] + preTable[i - key->len]) & 0xff];
  
  /* Establish effective key length by masking and expanding back.
   */
  effectiveKeyLen = (effectiveKeyBits + 7) / 8;
  mask = (unsigned char)(0xff >> (7 - ((effectiveKeyBits + 7) % 8)));
  preTable[128 - effectiveKeyLen] = 
    PI_SUBST[preTable[128 - effectiveKeyLen] & mask];
  for (i = 127 - effectiveKeyLen; i >= 0; --i) 
    preTable[i] =
      PI_SUBST[(preTable[i + 1] ^ preTable[i + effectiveKeyLen]) & 0xff];
  
  /* Store byte pre-table in key table.
   */
  for (i = 0, j = 0; i < 64; i++, j += 2)
    context->keyTable[i] = (preTable[j + 1] << 8) + preTable[j];

  T_memset ((POINTER)preTable, 0, sizeof (preTable));
  return (0);
}
#endif /* RC2_INIT_ASSEMBLY */

#ifndef RC2_ENCRYPT_ASSEMBLY
/* RC2Encrypt encrypts input into output according to table. (This is a
     single-block operation.)
   Note that the context is a POINTER because it is used abstractly inside
     ECB and CBC "drivers".  Users typically only call the drivers.
 */
void RC2Encrypt (context, output, input)
POINTER context;                                   /* context with key table */
unsigned char *output;                       /* eight-byte output data block */
unsigned char *input;                         /* eight-byte input data block */
{ 
  KSTYPE  a, b, c, d, w;
  KSTYPE  *table = ((RC2_CTX *)context)->keyTable;

  /* Load registers from input.
   */
  a = ((UINT2)input[1] << 8) + input[0];
  b = ((UINT2)input[3] << 8) + input[2];
  c = ((UINT2)input[5] << 8) + input[4];
  d = ((UINT2)input[7] << 8) + input[6];
  
  /* Round 1 (mixing).
   */
  FMIX (a, b, c, d, table[0], 1);
  FMIX (b, c, d, a, table[1], 2);
  FMIX (c, d, a, b, table[2], 3);
  FMIX (d, a, b, c, table[3], 5);

  /* Round 2 (mixing).
   */
  FMIX (a, b, c, d, table[4], 1);
  FMIX (b, c, d, a, table[5], 2);
  FMIX (c, d, a, b, table[6], 3);
  FMIX (d, a, b, c, table[7], 5);

  /* Round 3 (mixing).
   */
  FMIX (a, b, c, d, table[8], 1);
  FMIX (b, c, d, a, table[9], 2);
  FMIX (c, d, a, b, table[10], 3);
  FMIX (d, a, b, c, table[11], 5);

  /* Round 4 (mixing).
   */
  FMIX (a, b, c, d, table[12], 1);
  FMIX (b, c, d, a, table[13], 2);
  FMIX (c, d, a, b, table[14], 3);
  FMIX (d, a, b, c, table[15], 5);

  /* Round 5 (mixing).
   */
  FMIX (a, b, c, d, table[16], 1);
  FMIX (b, c, d, a, table[17], 2);
  FMIX (c, d, a, b, table[18], 3);
  FMIX (d, a, b, c, table[19], 5);

  /* Round 6 (mashing).
   */
  FMASH (a, d, table);
  FMASH (b, a, table);
  FMASH (c, b, table);
  FMASH (d, c, table);
  
  /* Round 7 (mixing).
   */
  FMIX (a, b, c, d, table[20], 1);
  FMIX (b, c, d, a, table[21], 2);
  FMIX (c, d, a, b, table[22], 3);
  FMIX (d, a, b, c, table[23], 5);

  /* Round 8 (mixing).
   */
  FMIX (a, b, c, d, table[24], 1);
  FMIX (b, c, d, a, table[25], 2);
  FMIX (c, d, a, b, table[26], 3);
  FMIX (d, a, b, c, table[27], 5);

  /* Round 9 (mixing).
   */
  FMIX (a, b, c, d, table[28], 1);
  FMIX (b, c, d, a, table[29], 2);
  FMIX (c, d, a, b, table[30], 3);
  FMIX (d, a, b, c, table[31], 5);

  /* Round 10 (mixing).
   */
  FMIX (a, b, c, d, table[32], 1);
  FMIX (b, c, d, a, table[33], 2);
  FMIX (c, d, a, b, table[34], 3);
  FMIX (d, a, b, c, table[35], 5);

  /* Round 11 (mixing).
   */
  FMIX (a, b, c, d, table[36], 1);
  FMIX (b, c, d, a, table[37], 2);
  FMIX (c, d, a, b, table[38], 3);
  FMIX (d, a, b, c, table[39], 5);

  /* Round 12 (mixing).
   */
  FMIX (a, b, c, d, table[40], 1);
  FMIX (b, c, d, a, table[41], 2);
  FMIX (c, d, a, b, table[42], 3);
  FMIX (d, a, b, c, table[43], 5);

  /* Round 13 (mashing).
   */
  FMASH (a, d, table);
  FMASH (b, a, table);
  FMASH (c, b, table);
  FMASH (d, c, table);

  /* Round 14 (mixing).
   */
  FMIX (a, b, c, d, table[44], 1);
  FMIX (b, c, d, a, table[45], 2);
  FMIX (c, d, a, b, table[46], 3);
  FMIX (d, a, b, c, table[47], 5);

  /* Round 15 (mixing).
   */
  FMIX (a, b, c, d, table[48], 1);
  FMIX (b, c, d, a, table[49], 2);
  FMIX (c, d, a, b, table[50], 3);
  FMIX (d, a, b, c, table[51], 5);

  /* Round 16 (mixing).
   */
  FMIX (a, b, c, d, table[52], 1);
  FMIX (b, c, d, a, table[53], 2);
  FMIX (c, d, a, b, table[54], 3);
  FMIX (d, a, b, c, table[55], 5);

  /* Round 17 (mixing).
   */
  FMIX (a, b, c, d, table[56], 1);
  FMIX (b, c, d, a, table[57], 2);
  FMIX (c, d, a, b, table[58], 3);
  FMIX (d, a, b, c, table[59], 5);

  /* Round 18 (mixing).
   */
  FMIX (a, b, c, d, table[60], 1);
  FMIX (b, c, d, a, table[61], 2);
  FMIX (c, d, a, b, table[62], 3);
  FMIX (d, a, b, c, table[63], 5);

  /* Store registers in output.
   */
  output[0] = (unsigned char)a;
  output[1] = (unsigned char)(a >> 8);
  output[2] = (unsigned char)b;
  output[3] = (unsigned char)(b >> 8);
  output[4] = (unsigned char)c;
  output[5] = (unsigned char)(c >> 8);
  output[6] = (unsigned char)d;
  output[7] = (unsigned char)(d >> 8);
}
#endif /* RC2_ENCRYPT_ASSEMBLY */

#ifndef RC2_DECRYPT_ASSEMBLY
/* RC2Decrypt decrypts input into output according to table. (This is a
     single-block operation.)
   Note that the context is a POINTER because it is used abstractly inside
     ECB and CBC "drivers".  Users typically only call the drivers.
 */
void RC2Decrypt (context, output, input)
POINTER context;                                   /* context with key table */
unsigned char *output;                       /* eight-byte output data block */
unsigned char *input;                         /* eight-byte input data block */
{ 
  KSTYPE a, b, c, d, *table = ((RC2_CTX *)context)->keyTable;

  /* Load registers from input.
   */
  a = ((UINT2)input[1] << 8) + input[0];
  b = ((UINT2)input[3] << 8) + input[2];
  c = ((UINT2)input[5] << 8) + input[4];
  d = ((UINT2)input[7] << 8) + input[6];
  
  /* Round 1 (mixing).
   */
  RMIX (d, a, b, c, table[63], 5);
  RMIX (c, d, a, b, table[62], 3);
  RMIX (b, c, d, a, table[61], 2);
  RMIX (a, b, c, d, table[60], 1);

  /* Round 2 (mixing).
   */
  RMIX (d, a, b, c, table[59], 5);
  RMIX (c, d, a, b, table[58], 3);
  RMIX (b, c, d, a, table[57], 2);
  RMIX (a, b, c, d, table[56], 1);

  /* Round 3 (mixing).
   */
  RMIX (d, a, b, c, table[55], 5);
  RMIX (c, d, a, b, table[54], 3);
  RMIX (b, c, d, a, table[53], 2);
  RMIX (a, b, c, d, table[52], 1);

  /* Round 4 (mixing).
   */
  RMIX (d, a, b, c, table[51], 5);
  RMIX (c, d, a, b, table[50], 3);
  RMIX (b, c, d, a, table[49], 2);
  RMIX (a, b, c, d, table[48], 1);

  /* Round 5 (mixing).
   */
  RMIX (d, a, b, c, table[47], 5);
  RMIX (c, d, a, b, table[46], 3);
  RMIX (b, c, d, a, table[45], 2);
  RMIX (a, b, c, d, table[44], 1);

  /* Round 6 (mashing).
   */
  RMASH (d, c, table);
  RMASH (c, b, table);
  RMASH (b, a, table);
  RMASH (a, d, table);
  
  /* Round 7 (mixing).
   */
  RMIX (d, a, b, c, table[43], 5);
  RMIX (c, d, a, b, table[42], 3);
  RMIX (b, c, d, a, table[41], 2);
  RMIX (a, b, c, d, table[40], 1);

  /* Round 8 (mixing).
   */
  RMIX (d, a, b, c, table[39], 5);
  RMIX (c, d, a, b, table[38], 3);
  RMIX (b, c, d, a, table[37], 2);
  RMIX (a, b, c, d, table[36], 1);

  /* Round 9 (mixing).
   */
  RMIX (d, a, b, c, table[35], 5);
  RMIX (c, d, a, b, table[34], 3);
  RMIX (b, c, d, a, table[33], 2);
  RMIX (a, b, c, d, table[32], 1);

  /* Round 10 (mixing).
   */
  RMIX (d, a, b, c, table[31], 5);
  RMIX (c, d, a, b, table[30], 3);
  RMIX (b, c, d, a, table[29], 2);
  RMIX (a, b, c, d, table[28], 1);

  /* Round 11 (mixing).
   */
  RMIX (d, a, b, c, table[27], 5);
  RMIX (c, d, a, b, table[26], 3);
  RMIX (b, c, d, a, table[25], 2);
  RMIX (a, b, c, d, table[24], 1);

  /* Round 12 (mixing).
   */
  RMIX (d, a, b, c, table[23], 5);
  RMIX (c, d, a, b, table[22], 3);
  RMIX (b, c, d, a, table[21], 2);
  RMIX (a, b, c, d, table[20], 1);

  /* Round 13 (mashing).
   */
  RMASH (d, c, table);
  RMASH (c, b, table);
  RMASH (b, a, table);
  RMASH (a, d, table);

  /* Round 14 (mixing).
   */
  RMIX (d, a, b, c, table[19], 5);
  RMIX (c, d, a, b, table[18], 3);
  RMIX (b, c, d, a, table[17], 2);
  RMIX (a, b, c, d, table[16], 1);

  /* Round 15 (mixing).
   */
  RMIX (d, a, b, c, table[15], 5);
  RMIX (c, d, a, b, table[14], 3);
  RMIX (b, c, d, a, table[13], 2);
  RMIX (a, b, c, d, table[12], 1);

  /* Round 16 (mixing).
   */
  RMIX (d, a, b, c, table[11], 5);
  RMIX (c, d, a, b, table[10], 3);
  RMIX (b, c, d, a, table[9], 2);
  RMIX (a, b, c, d, table[8], 1);

  /* Round 17 (mixing).
   */
  RMIX (d, a, b, c, table[7], 5);
  RMIX (c, d, a, b, table[6], 3);
  RMIX (b, c, d, a, table[5], 2);
  RMIX (a, b, c, d, table[4], 1);

  /* Round 18 (mixing).
   */
  RMIX (d, a, b, c, table[3], 5);
  RMIX (c, d, a, b, table[2], 3);
  RMIX (b, c, d, a, table[1], 2);
  RMIX (a, b, c, d, table[0], 1);

  /* Store registers in output.
   */
  output[0] = (unsigned char)a;
  output[1] = (unsigned char)(a >> 8);
  output[2] = (unsigned char)b;
  output[3] = (unsigned char)(b >> 8);
  output[4] = (unsigned char)c;
  output[5] = (unsigned char)(c >> 8);
  output[6] = (unsigned char)d;
  output[7] = (unsigned char)(d >> 8);
}
#endif /* RC2_DECRYPT_ASSEMBLY */
