/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#include "bsafe.h"
#include "bsafelite.h"
#include "rsa.h"
/* RSA encryption/decryption with full exponent.
 */

static int ALG_RSA 
  (A_RSA_CTX *, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, A_SURRENDER_CTX *);

/* Initializes the RSA process, constructing and setting CMPInt elements
     and allocating memory in context. If you call this routine, you
     must call ALG_RSAContextDestroy before exiting.
 */
int ALG_RSAInit(A_RSA_CTX *context, A_RSA_KEY *key)
{
  int status;

  CMP_Constructor (&context->modulus);
  CMP_Constructor (&context->exponent);
  context->input = NULL_PTR;

  do {
    /* Convert modulus to CMP representation. */
    if ((status = CMP_OctetStringToCMPInt
        (key->modulus.data, key->modulus.len, &context->modulus)) != 0)
      break;

    /* Convert exponent to CMP representation. */
    if ((status = CMP_OctetStringToCMPInt
         (key->exponent.data, key->exponent.len, &context->exponent)) != 0)
      break;

    /* Set the block update blockLen to be big enough to hold the modulus. */
    context->blockLen = BITS_TO_LEN
      (CMP_BitLengthOfCMPInt (&context->modulus));

    /* Allocate space for the input block, as big as the modulus. */
    context->input = T_malloc (context->blockLen);
    if (context->input == NULL_PTR) {
      status = AE_ALLOC;
      break;
    }
    
    context->inputLen = 0;
  } while (0);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* Update the RSA process, if there is enough data, call ALG_RSA to
     perform the ModExp, if not, simply add it to the input buffer.
 */
int ALG_RSAUpdate
  (A_RSA_CTX *context,
unsigned char *partOut,
unsigned int *partOutLen,
unsigned int maxPartOutLen,
unsigned char *partIn,
unsigned int partInLen,
A_SURRENDER_CTX *surrenderContext)
{
  int status;
  unsigned int partialLen, localPartOutLen;

  /* Initialize partOutLen to zero. */
  *partOutLen = 0;

  if (context->inputLen + partInLen < context->blockLen) {
    /* Not enough to encrypt - just accumulate.
     */
    T_memcpy
      ((POINTER)(context->input + context->inputLen), (POINTER)partIn,
       partInLen);
    context->inputLen += partInLen;
    return (0);
  }

  if (context->inputLen > 0) {
    /* Need to accumulate the rest of the block bytes into the input and
         encrypt from there (otherwise it's OK to encrypt straight from
         the partIn).
     */
    partialLen = context->blockLen - context->inputLen;
    T_memcpy
      ((POINTER)(context->input + context->inputLen), (POINTER)partIn,
       partialLen);
    partIn    += partialLen;
    partInLen -= partialLen;

    if ((status = ALG_RSA
         (context, partOut, &localPartOutLen, maxPartOutLen, context->input,
          surrenderContext)) != 0)
      return (ALG_ErrorCode (status));
    (*partOutLen) += localPartOutLen;
    partOut       += localPartOutLen;
    maxPartOutLen -= localPartOutLen;
  }

  /* Encrypt as many blocks of input as provided.
   */
  while (partInLen >= context->blockLen) {
    if ((status = ALG_RSA
         (context, partOut, &localPartOutLen, maxPartOutLen, partIn,
          surrenderContext)) != 0)
      return (ALG_ErrorCode (status));

    partIn        += context->blockLen;
    partInLen     -= context->blockLen;
    (*partOutLen) += localPartOutLen;
    partOut       += localPartOutLen;
    maxPartOutLen -= localPartOutLen;
  }
  
  /* Copy remaining input bytes to the context's input buffer.
   */
  T_memcpy
    ((POINTER)context->input, partIn, context->inputLen = partInLen);
  return (0);
}

/* Finalize the RSA process, check to make sure there is no more data
     waiting in the input buffer.
 */
int ALG_RSAFinal(A_RSA_CTX *context)
{
  if (context->inputLen != 0)
    return (AE_INPUT_LEN);

  /* Restart context to accumulate a new block. */
  context->inputLen = 0;
  return (0);
}

/* There is enough data in the input data block, perform the ModExp. Input
     length is context->blockLen.
 */
static int ALG_RSA (
A_RSA_CTX *context,
unsigned char *output,
unsigned int *outputLen,
unsigned int maxOutputLen,
unsigned char *input,
A_SURRENDER_CTX *surrenderContext)
{
  int status;
  unsigned int modulusLen;
  CMPInt cmpInputBuffer;
  CMPInt cmpOutputBuffer;

  CMP_Constructor (&cmpOutputBuffer);
  CMP_Constructor (&cmpInputBuffer);

  do {
    if ((*outputLen = context->blockLen) > maxOutputLen) {
      status = AE_OUTPUT_LEN;
      break;
    }

    /* Convert input to CMPInt representation. */
    if ((status = CMP_OctetStringToCMPInt
         (input, context->blockLen, &cmpInputBuffer)) != 0)
      break;

    /* Exponentiate. */
    if ((status = VS_CMP_ModExp
         (&cmpInputBuffer, &context->exponent, &context->modulus,
          &cmpOutputBuffer, surrenderContext)) != 0)
      break;

    /* Convert back to an octet string. At this point, the result is a
         cryptographic data unit, not a math unit. The buffer to return
         must be the same size as the modulus, so if the actual value
         of the cmpOutputBuffer is smaller, pad with leading zeros.
     */
    modulusLen = BITS_TO_LEN (CMP_BitLengthOfCMPInt (&context->modulus));
    if ((status = CMP_CMPIntToFixedLenOctetStr
         (&cmpOutputBuffer, modulusLen, maxOutputLen, outputLen,
          output)) != 0)
      break;
  } while (0);

  CMP_Destructor (&cmpInputBuffer);
  CMP_Destructor (&cmpOutputBuffer);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* Destroy the CMPInt's and free up the memory of context.
 */
void ALG_RSAContextDestroy (A_RSA_CTX *context)
{
  CMP_Destructor (&context->modulus);
  CMP_Destructor (&context->exponent);

  if (context->input != NULL_PTR) {
    T_memset ((POINTER)(context->input), 0, context->blockLen);
    T_free (context->input);
  }
}
