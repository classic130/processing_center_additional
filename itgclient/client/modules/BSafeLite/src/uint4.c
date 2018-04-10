/* Copyright (C) RSA Data Security, Inc. created 1993.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "bsafelite.h"
#include "uint4.h"

/* Encodes x (UINT4) into block (unsigned char), most significant
     byte first.
 */
void UINT4ToBigEndian (block, x, digits)
unsigned char *block;
UINT4 *x;
unsigned int digits;
{
  unsigned int i, j;

  for (i = 0, j = 0; i < digits; i++, j += 4) {
    block[j] = (unsigned char)((x[i] >> 24) & 0xff);
    block[j+1] = (unsigned char)((x[i] >> 16) & 0xff);
    block[j+2] = (unsigned char)((x[i] >> 8) & 0xff);
    block[j+3] = (unsigned char)(x[i] & 0xff);
  }
}

/* Decodes block (unsigned char) into x (UINT4), most significant
     byte first.
 */
void UINT4FromBigEndian (x, digits, block)
UINT4 *x;
unsigned int digits;
unsigned char *block;
{
  unsigned int i, j;

  for (i = 0, j = 0; i < digits; i++, j += 4)
    x[i] = (((UINT4)block[j]) << 24) | (((UINT4)block[j+1]) << 16) |
      (((UINT4)block[j+2]) << 8) | ((UINT4)block[j+3]);
}
