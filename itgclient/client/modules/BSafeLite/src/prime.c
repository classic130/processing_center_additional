/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */
//#include "aglobal.h"
//#include "algae.h"
//#include "sizes.h"
#include "bsafelite.h"
//#include "cmp.h"
#include "prime.h"
//#include "surrendr.h"

#define SIZE_OF_PRIME_ROSTER     500
#define SIZE_OF_LIST_OF_PRIMES   53
#define SIEVE_INCREMENTS         512    
/* #define SIEVE_STEPS              ((65000 / SIEVE_INCREMENTS)) */
#define SIEVE_STEPS              126

static unsigned char listOfPrimes[SIZE_OF_LIST_OF_PRIMES] = {
    3,   5,   7,  11,  13,  17,  19,  23,  29,  31,
   37,  41,  43,  47,  53,  59,  61,  67,  71,  73,
   79,  83,  89,  97, 101, 103, 107, 109, 113, 127,
  131, 137, 139, 149, 151, 157, 163, 167, 173, 179,
  181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
  239, 241, 251
  };

int ALG_ByteVectorToCMPInt
  (unsigned char *, unsigned int, CMPInt *);
int ALG_GeneratePrimeArray
  (int, unsigned int, unsigned int, unsigned char *, unsigned char *);
int ALG_GeneratePrimeRoster
  (CMPInt *, CMPInt *, unsigned int, unsigned char *);
int ALG_FilterCandidateRoster
  (CMPInt *, CMPInt *, unsigned int, unsigned int, unsigned char *,
    unsigned int, unsigned char *);
int ALG_ComputeInverse (long int, long int prime, long int *);

/* Prime finding routine. Find a prime number based on the randomBlock.
 */
int ALG_PrimeFind
  (randomBlock, primeSizeBits, expo, primeCMP, surrenderContext)
unsigned char *randomBlock;
unsigned int primeSizeBits;
CMPInt *expo;
CMPInt *primeCMP;
A_SURRENDER_CTX *surrenderContext;
{
  int status;
  unsigned char primeRoster[SIZE_OF_PRIME_ROSTER], sieve[SIEVE_INCREMENTS];
  unsigned int i, r, r1, s, testResult, offset, j, k, lowerLim, upperLim;
  int numPrimes = SIZE_OF_LIST_OF_PRIMES;
  unsigned char offsets[SIZE_OF_LIST_OF_PRIMES];
  CMPWord addendum;
  CMPWord remainder;
  CMPInt  gcd_p_1_ee, p_1, unit;

  CMP_Constructor (&p_1);
  CMP_Constructor (&gcd_p_1_ee);
  CMP_Constructor (&unit);

  do {
    /* unit = 1 */
    if ((status = CMP_CMPWordToCMPInt ((CMPWord) 1, &unit)) != 0)
      break;

    /* Create a starting point for the prime from the random block.
         ALG_ByteVectorToCMPInt will produce a starting point exactly
         the same as BigNum based BSAFE. Otherwise, simply use
         CMP_OctetStringToCMPInt.
     */
    if ((status = ALG_ByteVectorToCMPInt
         (randomBlock, primeSizeBits, primeCMP)) != 0)
      break;
/*    if ((status = CMP_OctetStringToCMPInt
         (randomBlock, BITS_TO_LEN (primeSizeBits), primeCMP)) != 0)
      break;
 */
    /* Set two most significant bits
     */
    if ((status = CMP_SetBit (primeSizeBits - 2, primeCMP)) != 0)
      break;
    if ((status = CMP_SetBit (primeSizeBits - 1, primeCMP)) != 0)
      break;

    /* Clear bits beyond primeSizeBits until end of MSW. If you are using
         ALG_ByteVectorToCMPInt, the algorithm is loading up 16 bit words
         into the CMPInt, clear the last bits in the MSByte + 8 bits.
     */
    r = 8;
    r += BITS_TO_LEN (primeSizeBits) * BITS_PER_BYTE;
    r = (r <= (r1 = CMP_BitLengthOfCMPInt (primeCMP))) ? r : r1;
    for (i = primeSizeBits; i < r; ++i)
      if ((status = CMP_ClearBit (i, primeCMP)) != 0)
        break;
    if (status != 0)
      break;

    /* force p to be odd */
    if ((status = CMP_SetBit (0, primeCMP)) != 0)
      break;

    /* clear primeRoster to initialize all positions as possible primes. */
    T_memset ((POINTER)primeRoster, 0, SIZE_OF_PRIME_ROSTER);

    /* Sieve is used to mark the position of plausible primes relative to
         initial candidate computed from random block, ie, primeRoster[i] == 1
         indicates that primeCMP + 2 * i is a composite number.
     */
    lowerLim = 3;
    upperLim = 3 + SIEVE_INCREMENTS;
    for (i = 0; i < SIEVE_STEPS; ++i) {
      /* Create sieve for purposes of eliminating composite numbers
       */
      if ((status = ALG_GeneratePrimeArray
           (numPrimes, lowerLim, upperLim, offsets, sieve)) != 0)
        break;

      for (k = 0; k < SIEVE_INCREMENTS; k += 2) {
        if (sieve[k])
          continue;
        /* sieve based on s */
        s = k + lowerLim;

        if ((status = CMP_CMPWordModularReduce
             (primeCMP, (CMPWord) s, &remainder)) != 0)
        break;

        r = (unsigned int) remainder;
        if ((r & 1) == 1)
          offset = (s - r) / 2;
        else {
          if (r > 0)
            offset = s - r / 2;
          else
            offset = 0;
        }

        /* j = prime + n * s - r is divisible by s,
             so set PrimeRoster[j] = 1
         */
        for (j = offset; j < SIZE_OF_PRIME_ROSTER; j += s)
          primeRoster[j] = 1;
      }
      lowerLim = upperLim;
      upperLim += SIEVE_INCREMENTS;
    }

    /* check for primality of j = prime + 2 * i, where primeRoster[i] = 0
     */
    testResult = 0;
    for (i = 0; i < SIZE_OF_PRIME_ROSTER; i++) {
      do {
        /* accumulate addendum over consecutive 1's in PrimeRoster array
         */
        if (primeRoster[i] > 0) {
          addendum = 0;
          while (primeRoster[i]) { 
            addendum += 2;
            i++;
            if (i == SIZE_OF_PRIME_ROSTER)
              break;
          }
          if (i == SIZE_OF_PRIME_ROSTER) {
             status = AE_NEED_RANDOM;
             break;
          }
          if ((status = VS_CMP_AddCMPWord (addendum, primeCMP)) != 0) 
            break;
        }

        /* set p_1 = p - 1; Can subtract fearlessly since p > 0 */
        if ((status = VS_CMP_Move (primeCMP, &p_1)) != 0)
          break;
        
        if ((status = VS_CMP_SubtractCMPWord ((CMPWord) 1, &p_1)) != 0)
          break;
        if ((status = CMP_ComputeGCD (expo, &p_1, &gcd_p_1_ee)) != 0)
          break;

        /* Enforce constraint that p - 1 and encryption exponent have
             no common factors, ie,  gcd (p - 1, ee) == 1 .
         */
        if (VS_CMP_Compare (&unit, &gcd_p_1_ee))
          break;

        /* check for pseudo primality */
        if ((status = ALG_PseudoPrime
             (primeCMP, &testResult, surrenderContext)) != 0)
          break;
      } while (0);
      if (status != 0)
        break;

      if (testResult != 0)
        break;

      if ((status = VS_CMP_AddCMPWord ((CMPWord) 2, primeCMP)) != 0) 
        break;
    }
    if (status != 0)
      break;
    
    if (!testResult)
      /* Couldn't find a prime with the supplied random block, so ask
           caller to generate another random block and try again. */
      status = AE_NEED_RANDOM;
  } while (0);

  CMP_Destructor (&p_1);
  CMP_Destructor (&gcd_p_1_ee);
  CMP_Destructor (&unit);

  /* Translate any CMP error code into an Algae error code.
   */
  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* Pseudo-primality test.
     If pseudo prime, *testResult = 1, else *testResult = 0.
 */
int ALG_PseudoPrime (proposedPrime, testResult, surrenderContext)
CMPInt *proposedPrime;
unsigned int *testResult;
A_SURRENDER_CTX *surrenderContext;
{
  int status;
  unsigned int i;
  CMPInt smallPrime, fermatValue;

  CMP_Constructor (&smallPrime);
  CMP_Constructor (&fermatValue);
  
  /* Prepare for setting base vector to the small prime.
   */
  for (i = 0; i < 4; ++i) {
    /* Initialize testResult to fail. */
    *testResult = 0;

    /* Fermat test. Compute
         remainder = base ^ proposedPrime mod proposedPrime
         and compare the base to the remainder.
     */
    if ((status = CMP_CMPWordToCMPInt
         ((CMPWord) listOfPrimes[i], &smallPrime)) != 0)
      break;

    if ((status = VS_CMP_ModExp
         (&smallPrime, proposedPrime, proposedPrime, &fermatValue,
          surrenderContext)) != 0)
      break;

   if (VS_CMP_Compare (&fermatValue, &smallPrime) != 0)
      break;

   /* Passed this test, set to succeed. If there are more loops, this will
        be reinitialized to fail. */
   *testResult = 1;
  }

  CMP_Destructor (&smallPrime);
  CMP_Destructor (&fermatValue);

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* Sets sieve so that sieve[i] == 0 iff i + lowerLim is prime;
     Implements Eratosthenes sieve using listOfPrimes.
     Assumptions:
      First call must be made with lowerLim = 3 and upperLim >= biggest prime
       in listOfPrimes;
      lowerLim and UpperLim are odd numbers;
      remains[i] = lowerLim % listOfPrimes;
      upperLim < min (2 ^ 32, p ^ 2) where p = the SIZE_OF_LIST_OF_PRIMES + 1
       prime.
 */   
int ALG_GeneratePrimeArray (searchDepth, lowerLim, upperLim, remainders, sieve)
int searchDepth;
unsigned int lowerLim;
unsigned int upperLim;
unsigned char *remainders;
unsigned char *sieve;
{
  int s, k, range;
  int prime, offset, remainder ;

  /* Initialize sieve so that positions representing odd numbers are enabled
       and corresponding even positions are disabled. 
   */
  range = upperLim - lowerLim;
  for (s = 0; s < range; s = s + 2) {
    sieve[s] = 0;
    sieve[s + 1] = 1;    
  }

  /* if this is first call to routine set remainders array appropriately
   */
  if (lowerLim == 3) {
     remainders[0] = 0;
     for (s = 1; s < searchDepth; ++s)
       remainders[s] = 3;
  }

  /* Walk through sieve array progressively setting positions that represent
       numbers divisible by the s-th odd prime
   */
  for (s = 0; s < searchDepth; ++s) {
    prime     = listOfPrimes[s];
    remainder = remainders[s];
    offset    = (remainder != 0) ? prime - remainder : 0;
    for (k = offset; k < range; k += prime)
      sieve[k] = 1;
    remainders[s] = (unsigned char ) ((range == k) ? 0 : range + prime - k);
  }

  /* If initial call ensure that all prime positions indicate primeness
   */
  if (lowerLim == 3) {
    for (s = 0; s < searchDepth; ++s)
      sieve[listOfPrimes[s] - 3] = 0;
  }
  return (0);
}

/* Uses a two-stage sieving process to produce a list of plausible primes.
   One sieving process is used to generate consecutive primes that in
   turn are used to test the candidate roster.
*/
int ALG_GeneratePrimeRoster (initPos, step, rosterSize, roster)
CMPInt *initPos;
CMPInt *step;
unsigned int rosterSize;
unsigned char *roster;
{
  unsigned char offsets[SIZE_OF_LIST_OF_PRIMES];
  unsigned char sieve[SIEVE_INCREMENTS];
  int numPrimes = SIZE_OF_LIST_OF_PRIMES;
  unsigned int i, lowerLim, upperLim, sieveSize;    	
  int status;

  /* clear primeRoster to initialize all positions as possible primes. */
  T_memset ((POINTER) roster, 0, rosterSize);

  /* Sieve is used to mark the position of plausible primes relative to
       initial candidate computed from random block, ie, primeRoster[i] == 1
       indicates that primeCMP + i * step is a composite number.
   */
  lowerLim  = 3;
  upperLim  = 3 + SIEVE_INCREMENTS;
  sieveSize = SIEVE_INCREMENTS;
  for (i = 0; i < SIEVE_STEPS; ++i) {
    /* Create sieve for purposes of eliminating composite candidate numbers */
    if ((status = ALG_GeneratePrimeArray
         (numPrimes, lowerLim, upperLim, offsets, sieve)) != 0)
      break;

    if ((status = ALG_FilterCandidateRoster
         (initPos, step, lowerLim, sieveSize, sieve, rosterSize, roster)) != 0)
      break;
    lowerLim = upperLim;
    upperLim += SIEVE_INCREMENTS;
  }

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* ALG_FilterCandidateRoster is used as a means of progressively
     sieving through the list of numbers
     start, start + step, start + 2 * step, ..., start + k * step, ...,
     start + step * (rosterSize - 1).
     The sieving set has the representation {test0 + i[0], .., test0 + i[t]}
     where sieveRoster[i[j]] = 0.
     On return, roster[k] has been set to 1 if for some j, test0 + i[j]
     divides start + k * step.
 
     Assumptions
      1) step is twice some prime number and so is prime
         to all other odd primes.
      2) sieveRoster[k] == 0 iff test0 + k is prime.
 
     Suppose we wish to eliminate all the numbers in our candidate
     roster that are not relatively prime to a given prime number s.
     Let k[s] be the smallest index for which start + k[s] * step is
     divisible by s. If j > k[s] and start + j * step is divisible
     by s then it follows by subtraction that (j - k[s]) * step is divisible
     by s. Assumption (1) implies that s divides j - k[s].

     If s divides start then k[s] = 0. Otherwise let r = start % s and
     rho = step % s > 0. Observe start + k[s] * step = 0 mod s, implying
     that k[s] * rho = s - r mod s . Hence k[s] = (s - r) * rho ^ -1 mod s.
     So k[s] is the smallest positive number which satisfies the previous
     equation.
 */
int ALG_FilterCandidateRoster
  (start, step, test0, sieveSize, sieveRoster, rosterSize, roster)
CMPInt *start;
CMPInt *step;
unsigned int test0;
unsigned int sieveSize;
unsigned char *sieveRoster;
unsigned int rosterSize;
unsigned char *roster;
{
  unsigned int j, k;
  int status;
  CMPWord s, remainder, stepRemainder;
  long int inverse;

  for (j = 0; j < sieveSize; j += 2) {
    if (sieveRoster[j])
      continue;

    s = (CMPWord) test0 + (CMPWord) j;
    if ((status = CMP_CMPWordModularReduce (start, s, &remainder)) != 0)
      break;

    if (remainder == 0) {
      k = 0;
    }
    else {
      if ((status = CMP_CMPWordModularReduce
           (step, s, &stepRemainder)) != 0)
        break;

      if ((status = ALG_ComputeInverse
           ((long int) stepRemainder, (long int) s, &inverse)) != 0)
        break;
      k = (unsigned int) ((inverse * (s - remainder)) % s);
    }
    for (; k < rosterSize; k += (unsigned int) s)
      roster[k] = 1;
  }
  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}

/* ALG_ComputeInverse computes rInv, the positive multiplicative inverse
     of r mod prime, ie, rInv * r = 1 mod P and 0 < rInv < prime.
     Assume that 0 < r < prime < sqrt (MAX_CMPWORD) .
     Computes inverse of r by means of extended Euclidean algorithm.
     See Knuth Volume2 for details.
 */
int ALG_ComputeInverse (r, prime, rInv)
long int r;
long int prime; 
long int *rInv;
{
  long int r0, r1, r2, u0, u1, u2, quotient;

  u0 = 0;
  u1 = 1;
  r0 = prime;
  r1 = r;
  quotient  = r0 / r1;
  r2 = r0 % r1;
  u2 = -quotient;
  while (r2 > 0) {
    r0 = r1;
    r1 = r2;
    u0 = u1;
    u1 = u2;
    quotient  = r0 / r1;
    r2 = r0 % r1;
    u2 = u0 - quotient * u1;
  }
  *rInv = (u1 > 0)? u1 : prime + u1;
  return (0);
}

/* Maps byteVector to destInt; Differs from octet to CMPInt routine in
     the way it treats the arithmetic valuation of the byte stream
     Here only to produce the exact same results as BigNum Algae.
 */
int ALG_ByteVectorToCMPInt (byteVector, primeSizeBits, destInt)
unsigned char *byteVector;
unsigned int primeSizeBits;
CMPInt *destInt;
{
  int status, i, halfWords;
  unsigned char *octetString = NULL_PTR;

  halfWords = (int)((primeSizeBits + 15) / 16);

  do {
    octetString = T_malloc ((halfWords * 2) + 1);
    if (octetString == NULL_PTR) {
      status = AE_ALLOC;
      break;
    }

    for (i = 0; i < halfWords * 2; i = i + 2) {
      octetString[(halfWords * 2) - 2 - i] = byteVector[i];
      octetString[(halfWords * 2) - 1 - i] = byteVector[i + 1];
    }

    status = CMP_OctetStringToCMPInt
      (octetString, (halfWords * 2), destInt);
  } while (0);

  if (octetString != NULL_PTR) {
    T_memset (octetString, 0, (halfWords * 2) + 1);
    T_free (octetString);
  }

  if (status == 0)
    return (0);
  return (ALG_ErrorCode (status));
}
