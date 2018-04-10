/* Copyright (C) RSA Data Security, Inc. created 1987.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
//#include "global.h"
//#include "algae.h"
#include "bsafelite.h"
#include "rc4.h"

#ifndef RC4_INIT_ASSEMBLY

void A_RC4Init (context, key)
A_RC4_CTX *context;
ITEM *key;
{
  unsigned char *table;
  unsigned char *keyPtr;
  unsigned int ti, tk, tj;
  unsigned int i, j, k;
  unsigned int keyLen;

  /* Initialize indices.
   */
  context->i = context->j = 0;
  context->initialized = 1;

  table = context->table;
  keyLen = key->len;
  keyPtr = key->data;

  /* Initialize table.
   */
  for (i = 0; i < 256; i++)
    table[i] = (unsigned char)i;

  /* Permute table according to key.
   */
  i = j = k = 0;
  while (i < 256) {
    ti = table[i];
    tk = keyPtr[k];
    j += tk;
    j += ti;
    j &= 255;
    tj = table[j];
    ++k;
    ++i;
    table[i-1] = tj;
    table[j] = ti;
    if (k == keyLen)
      k = 0;
  }
}
#endif  /* End conditional inclusion of A_RC4Init c-code */

#ifndef RC4_UPDATE_ASSEMBLY
int A_RC4Update (context, output, outputLen, maxOutputLen, input, inputLen)
A_RC4_CTX *context;
unsigned char *output;
unsigned int *outputLen;
unsigned int maxOutputLen;
unsigned char *input;
unsigned int inputLen;
{
  unsigned char *table, ti, tj;
  unsigned int i, j;
  unsigned char *pOutput, *pInput, *pLastInput;
  
  if (maxOutputLen < inputLen)
    return (AE_OUTPUT_LEN);
  
  if (! context->initialized)
    return (AE_NOT_INITIALIZED);

  if ((*outputLen = inputLen) <= 0)
    return (0);
  
  i = context->i;
  j = context->j;
  table = context->table;
  pOutput = output;
  pInput = input;
  pLastInput = &(input[inputLen-1]);

  while (pInput <= pLastInput) {
    i = (i + 1) & 255;
    ti = table[i];
    j = (j + ti) & 255;
    tj = table[j];
    table[i] = tj;
    table[j] = ti;
    tj = (tj + ti) & 255;
    tj = table[tj];
    *pOutput++ = *pInput++ ^ tj;
  }
  
  *outputLen = inputLen;
  
  /* Restore indices.
   */
  context->i = i;
  context->j = j;
  
  return (0);
}
#endif /* End conditional inclusion of A_RC4Update c-code */

#ifndef RC4_FINAL_ASSEMBLY

int A_RC4Final (context)
A_RC4_CTX *context;
{
  if (! context->initialized)
    return (AE_NOT_INITIALIZED);

  context->initialized = 0;
  return (0);
}
#endif /* End conditional inclusion of A_RC4Final c-code */

