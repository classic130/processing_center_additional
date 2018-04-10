/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
#include "bsafe.h"
#include "bsafelite.h"
#include "rsakeygn.h"
#include "prime.h"

static int ALG_RSAParameters(A_RSA_KEY_GEN_CTX *, CMPInt *,  CMPInt *);
static int ALG_SetRSAKeyGenResult(CMPInt *, CMPInt *, A_RSA_KEY_GEN_CTX *, A_PKCS_RSA_PRIVATE_KEY *);

/* Initialize the RSA key generating process, constructing and setting
     CMPInt elements of the context. If you call this routine, you
     must call ALG_RSAKeyGenContextDestroy before exiting.
 */
int ALG_RSAKeyGenInit (A_RSA_KEY_GEN_CTX *context,A_RSA_KEY_GEN_PARAMS *params)
{
  int status, lsBit;

  CMP_Constructor (&context->cmpModulus);
  CMP_Constructor (&context->cmpCoefficient);
  CMP_Constructor (&context->cmpPublicExponent);
  CMP_Constructor (&context->cmpPrivateExponent);
  CMP_Constructor (&context->cmpPrime1);
  CMP_Constructor (&context->cmpPrime2);
  CMP_Constructor (&context->cmpExponentP);
  CMP_Constructor (&context->cmpExponentQ);

  context->resultBuffer = NULL_PTR;
  context->modulusBits = params->modulusBits;

  do {
    /* Copy public exponent into CMPInt */
    if ((status = CMP_OctetStringToCMPInt
         (params->publicExponent.data, params->publicExponent.len,
          &context->cmpPublicExponent)) != 0)
      break;

    /* Check that the public exponent is in bounds and odd.
     */
    if (CMP_BitLengthOfCMPInt (&context->cmpPublicExponent) >=
        (int)context->modulusBits) {
      status = AE_EXPONENT_LEN;
      break;
    }

    if ((status = CMP_GetBit
         (0, &context->cmpPublicExponent, &lsBit)) != 0)
      break;
    if (lsBit == 0) {
      status = AE_EXPONENT_EVEN;
      break;
    }
  } while (0);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* This generates an RSA keypair of size modulusBits with the fixed
     publicExponent, pointing result to the resulting integers.  The
     resulting integer data is in the context, so that the values must be
     copied before the context is zeroized.
   All integers are unsigned canonical byte arrays with the most significant
     byte first.
   The randomBlock is of length randomBlockLen returned by RSAKeyGenQuery.
   This assumes that the modulusBits size was checked by RSAKeyGenQuery.
 */
int ALG_RSAKeyGen (A_RSA_KEY_GEN_CTX  *context,
A_PKCS_RSA_PRIVATE_KEY **result,
unsigned char *randomBlock,
A_SURRENDER_CTX *surrenderContext)
{
  CMPInt *cmpPrimeP, *cmpPrimeQ;
  int status;
  unsigned int primeSizeBits, primeWords;

  /* prime size is half modulus size
   */
  primeSizeBits = RSA_PRIME_BITS (context->modulusBits);
  primeWords = (primeSizeBits / 16) + 1;

  /* Fish for cmpPrime1 and cmpPrime2 that are compatible with supplied
       publicExponent.
     The randomBlock holds random bytes for two primes.
   */
  do {
    if ((status = ALG_PrimeFind
         (randomBlock, primeSizeBits, &context->cmpPublicExponent,
          &context->cmpPrime1, surrenderContext)) != 0)
      break;

    /* should add (primeSizeBits + 7) / 8 to randomBlock, for now, make
         sure it behaves same as old algae. */
    if ((status = ALG_PrimeFind
         (randomBlock + (2 * primeWords),
          context->modulusBits - primeSizeBits,
          &context->cmpPublicExponent, &context->cmpPrime2,
          surrenderContext)) != 0)
      break;

    /* Set cmpPrimeP to the larger of cmpPrime1 and cmpPrime2 and set
         cmpPrimeQ to the smaller.
     */
    if (VS_CMP_Compare (&context->cmpPrime1, &context->cmpPrime2) > 0) {
      cmpPrimeP = &context->cmpPrime1;
      cmpPrimeQ = &context->cmpPrime2;
    }
    else {
      cmpPrimeP = &context->cmpPrime2;
      cmpPrimeQ = &context->cmpPrime1;
    }

    /* Check the surrender function before following calculations. */
    if ((status = CheckSurrender (surrenderContext)) != 0)
      break;

    /* Calculate the rest of the key components */
    if ((status = ALG_RSAParameters 
         (context, cmpPrimeP, cmpPrimeQ)) != 0)
      break;

    /* Copy key components into canonical buffers which are at the
         end of the context.
     */
    *result = &context->result;
    if ((status = ALG_SetRSAKeyGenResult
         (cmpPrimeP, cmpPrimeQ, context, *result)) != 0)
      break;
  } while (0);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* This routine takes publicExponent, primeP and primeQ and computes the
     rest of the RSA keypair parameters.
 */
static int ALG_RSAParameters (
A_RSA_KEY_GEN_CTX *context,
CMPInt *primeP,
CMPInt *primeQ)
{
  int status;
  CMPInt phiOfModulus;

  /* Construct the CMPInt variable */
  CMP_Constructor (&phiOfModulus);

  do {
    /* modulus = p * q */
    if ((status = CMP_Multiply (primeP, primeQ, &context->cmpModulus)) != 0) 
      break;

    /*  Find p - 1 and q - 1
     */
    if ((status = VS_CMP_SubtractCMPWord ((CMPWord)1, primeP)) != 0)
      break;
    if ((status = VS_CMP_SubtractCMPWord ((CMPWord)1, primeQ)) != 0)
      break;

    /* phi = phi (modulus), where phi = Euler totient function,
         See Knuth Vol 2 */
    if ((status = CMP_Multiply (primeP, primeQ, &phiOfModulus)) != 0) 
      break;

    /* compute decryption exponent */
    if ((status = CMP_ModInvert
         (&context->cmpPublicExponent, &phiOfModulus,
          &context->cmpPrivateExponent)) != 0)
      break;

    /* calc exponentP = inv (publicExponent) [mod (p - 1)]
         and exponentQ = inv (publicExponent) [mod (q - 1)]
     */
    if ((status = CMP_ModularReduce
         (&context->cmpPrivateExponent, primeP,
          &context->cmpExponentP)) != 0)
      break;
    if ((status = CMP_ModularReduce
         (&context->cmpPrivateExponent, primeQ,
          &context->cmpExponentQ)) != 0)
      break;

    /* Restore p and q; q++ & p++ */
    if ((status = VS_CMP_AddCMPWord ((CMPWord)1, primeP)) != 0)
      break;
    if ((status = VS_CMP_AddCMPWord ((CMPWord)1, primeQ)) != 0)
      break;

    /* calculate coefficient = (inv (Q) [modP]) */
    if ((status = CMP_ModInvert
         (primeQ, primeP, &context->cmpCoefficient)) != 0)
      break;
  } while (0);

  CMP_Destructor (&phiOfModulus);

  if (status == 0)
    return (0);
  if (status == CMP_INVERSE)
    return (AE_NEED_RANDOM);
  return (ALG_ErrorCode (status));
}

/* Put the elements of the RSA key into a private key struct.
 */
static int ALG_SetRSAKeyGenResult (
CMPInt *cmpPrimeP,
CMPInt *cmpPrimeQ,
A_RSA_KEY_GEN_CTX *context,
A_PKCS_RSA_PRIVATE_KEY *result)
{
  int status;
  unsigned int primeLen, modulusLen;

  modulusLen = BITS_TO_LEN (context->modulusBits) + 1;
  primeLen   = RSA_PRIME_LEN (context->modulusBits) + 1;
  context->bufSize = (3 * modulusLen + 5 * primeLen) *
    sizeof (unsigned char);

  do {
    context->resultBuffer = (unsigned char *) T_malloc (context->bufSize);
    if (context->resultBuffer == NULL_PTR) {
      status = AE_ALLOC;
      break;
    }

    /* Set up data pointers using locations in resultBuffer array
     */
    result->modulus.data          = context->resultBuffer;
    result->publicExponent.data   = result->modulus.data + modulusLen;
    result->privateExponent.data  = result->publicExponent.data + modulusLen;
    result->prime[0].data         = result->privateExponent.data + modulusLen;
    result->prime[1].data         = result->prime[0].data + primeLen;
    result->primeExponent[0].data = result->prime[1].data + primeLen;
    result->primeExponent[1].data = result->primeExponent[0].data + primeLen;
    result->coefficient.data      = result->primeExponent[1].data + primeLen;

    if ((status = CMP_CMPIntToOctetString
         (&context->cmpModulus, modulusLen, &result->modulus.len,
          result->modulus.data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (&context->cmpPublicExponent, modulusLen,
          &result->publicExponent.len, result->publicExponent.data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (&context->cmpPrivateExponent, modulusLen,
          &result->privateExponent.len, result->privateExponent.data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (cmpPrimeP, primeLen, &result->prime[0].len,
          result->prime[0].data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (cmpPrimeQ, primeLen, &result->prime[1].len,
          result->prime[1].data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (&context->cmpExponentP, primeLen, &result->primeExponent[0].len,
          result->primeExponent[0].data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (&context->cmpExponentQ, primeLen, &result->primeExponent[1].len,
          result->primeExponent[1].data)) != 0)
      break;
    if ((status = CMP_CMPIntToOctetString
         (&context->cmpCoefficient, primeLen, &result->coefficient.len,
          result->coefficient.data)) != 0)
      break;
  } while (0);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* Destroy the CMPInt elements of the context.
 */
void ALG_RSAKeyGenContextDestroy (A_RSA_KEY_GEN_CTX *context)
{
  CMP_Destructor (&context->cmpModulus);
  CMP_Destructor (&context->cmpCoefficient);
  CMP_Destructor (&context->cmpPublicExponent);
  CMP_Destructor (&context->cmpPrivateExponent);
  CMP_Destructor (&context->cmpPrime1);
  CMP_Destructor (&context->cmpPrime2);
  CMP_Destructor (&context->cmpExponentP);
  CMP_Destructor (&context->cmpExponentQ);

  if (context->resultBuffer != NULL_PTR) {
    T_memset ((POINTER)(context->resultBuffer), 0, context->bufSize);
    T_free (context->resultBuffer);
  }

  return;
}
