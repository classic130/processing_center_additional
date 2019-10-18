/* Copyright (C) RSA Data Security, Inc. created 1995.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* This file contains routines that perform vector multiplication.
 */
#include "bsafelite.h"
#include "cmp.h"
#include "cmppriv.h"
#include "cmpspprt.h"

/* vectorB = (scaler * vectorA) + vectorB
     Begin vectorA at the indexA'th CMPWord and continue for lengthA CMPWords.
     Begin vectorB at the indexB'th CMPWord.
 */
void CMP_VectorMultiply (
CMPWord scaler,
CMPInt *vectorA,
int indexA,
int lengthA,
CMPInt *vectorB,
int indexB)
{
  int  loopCount;
  register CMPWord carry, lowProd, highProd, *valueA, *valueB;

  valueA = &(CMP_PINT_WORD (vectorA, indexA));
  valueB = &(CMP_PINT_WORD (vectorB, indexB));

  /* Initialize carry to 0. */
  carry = (CMPWord)0;

  for (loopCount = 0; loopCount < lengthA; ++loopCount) {
    /* Inner product:
         (highProd, lowProd) =
               scaler * valueA[loopCount] + valueB[loopCount] + carry
         Then set valueB[loopCount] to lowProd and carry (for the next
         iteration) to highProd.
     */
    CMP_MULT_HIGHLOW (scaler, valueA[loopCount], lowProd, highProd)
    lowProd += valueB[loopCount];
    if (lowProd < valueB[loopCount])
      highProd++;
    lowProd += carry;
    if (lowProd < carry)
      highProd++;
    carry = highProd;

    valueB[loopCount] = lowProd;
  }

  /* loopCount now = lengthA. */
  valueB[loopCount] += carry;

  /* If adding in the final carry leads to a carry itself, then propagate.
   */
  if (valueB[loopCount] < carry) {
    loopCount++;
    while (valueB[loopCount] == CMP_WORD_MASK)
        valueB[loopCount++] = 0;
    valueB[loopCount]++;
  }
  return;
}

/* Square each element of vectorA, adding the result to two elements
     of vectorB. This is used in squaring two CMPInt's.
 */
void CMP_AddInTrace (CMPInt *vectorA,CMPInt *vectorB)
{
  int indexA, indexB;
  register CMPWord carry, lowProd, highProd, *valueA, *valueB;

  valueA = CMP_PINT_VALUE (vectorA);
  valueB = CMP_PINT_VALUE (vectorB);
  carry = (CMPWord)0;

  /* Square one word of vectorA, then add the resulting two words to
       two words from montSquare. This should never overflow.
   */
  for (indexA = 0, indexB = 0;
       indexA < CMP_PINT_LENGTH (vectorA);
       ++indexA, indexB += 2) {
    CMP_SQUARE_HIGHLOW (valueA[indexA], lowProd, highProd)

    lowProd += valueB[indexB];
    if (lowProd < valueB[indexB])
      highProd++;

    lowProd += carry;
    if (lowProd < carry)
      highProd++;

    highProd += valueB[indexB + 1];
    carry = (highProd < valueB[indexB + 1]) ? 1 : 0;

    valueB[indexB] = lowProd;
    valueB[indexB + 1] = highProd;
  }
  if (carry == 0)
    return;

  /* Propagate carry.
   */
  while (valueB[indexB] == CMP_WORD_MASK)
    valueB[indexB++] = 0;
  valueB[indexB]++;
  return;
}
