/* Copyright (C) RSA Data Security, Inc. created 1992.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
   Modified 1995 to improve seeding.
 */

#include "global.h"
#include "algae.h"
#include "digrand.h"

/* For BSafe 3.0 we changed the method for seeding the
   generator and for incrementing the state after each
   time we generate new random bytes.  For backward
   compatibility, if only one call is made to RandomUpdate,
   then the generated bytes will be the same as before.

   The new behavior is to set the initial state to be the digest of
   all seed	bytes seen before the first Generate call, and
   if more than one RandomUpdate call has been made, then the 
   Generate call will advance the state by adding a large odd
   constant instead of simply adding one as was done previously.

   When seed bytes are provided after calls to Generate, then
   the new state is the Digest(State || seed_bytes), where
   State is the value of the current state when the first
   seed_bytes are provided.  Subsequent seed_bytes are appended.
*/
#if !GLOBAL_FUNCTION_POINTERS
void A_DigestRandomVTableInit (vTable, update, final)
A_DigestRandomVTable *vTable;
DIGESTUPDATE update;
DIGESTFINAL final;
{
  vTable->DigestUpdate = update;
  vTable->DigestFinal = final;
}
#endif

/* Calling routine must initialize the digest algorithm and set
   digestRandom->vTable.
   The digestLen is the length of the output of the digest algorithm (i.e. 16).
   state must point to an unsigned char * array of 3 * digestLen.
 */
void A_DigestRandomInit (digestRandom, digestLen, state)
A_DigestRandom *digestRandom;
unsigned int digestLen;
unsigned char *state;
{
  digestRandom->_outputAvailable = 0;
  digestRandom->_digestLen = digestLen;
  digestRandom->_newSeedToFinalize = 0;
  digestRandom->_lessThanTwoUpdateCalls = 2;

  digestRandom->_state = state;
  digestRandom->_output = state + digestLen;
  digestRandom->_oddConstant = digestRandom->_output + digestLen;
  /* The digest function has not been initialized, so we */
  /* cannot comput the odd constant in this routine. */

  T_memset ((POINTER)digestRandom->_state, 0, digestLen);
}

void A_DigestRandomUpdate (digestRandom, input, inputLen)
A_DigestRandom *digestRandom;
unsigned char *input;
unsigned int inputLen;
{
  /* Create the odd constant if this is the first call. */
  /* To support digests of various lengths, the constant */
  /* is based on the digest of the null string. */
  /* We have to do this here because the digest object */
  /* was not initialized when A_DigestRandomInit was called. */
  if (digestRandom->_lessThanTwoUpdateCalls == 2)
  {
    (*digestRandom->vTable->DigestUpdate) (digestRandom, NULL_PTR, 0);
    (*digestRandom->vTable->DigestFinal) (digestRandom, digestRandom->_oddConstant);
	digestRandom->_oddConstant[digestRandom->_digestLen-1] |= 1;
  }

  /* Decrement call counter and stick at zero. */
  if (digestRandom->_lessThanTwoUpdateCalls	> 0)
    --(digestRandom->_lessThanTwoUpdateCalls);

  if (  (digestRandom->_lessThanTwoUpdateCalls == 0)
     && (digestRandom->_newSeedToFinalize == 0) )
  { /* In non-compatible mode, chain in the */
    /* current state if necessary. */
    (*digestRandom->vTable->DigestUpdate) (digestRandom, 
                                           digestRandom->_state, 
                                           digestRandom->_digestLen);
  }
  (*digestRandom->vTable->DigestUpdate) (digestRandom, input, inputLen);
  digestRandom->_newSeedToFinalize = 1;
}

void A_DigestRandomGenerateBytes (digestRandom, output, outputLen)
A_DigestRandom *digestRandom;
unsigned char *output;
unsigned int outputLen;
{
  unsigned int available, x;
  int i;

  if (digestRandom->_newSeedToFinalize)
  {
    digestRandom->_newSeedToFinalize = 0;
	digestRandom->_outputAvailable = 0;
    (*digestRandom->vTable->DigestFinal) (digestRandom, digestRandom->_state);
  }
  
  available = digestRandom->_outputAvailable;

  while (outputLen > available) {
    T_memcpy
      ((POINTER)output,
       (POINTER)&digestRandom->_output[digestRandom->_digestLen-available],
       available);
    output += available;
    outputLen -= available;

    /* generate new output */
    (*digestRandom->vTable->DigestUpdate)
       (digestRandom, digestRandom->_state, digestRandom->_digestLen);
    (*digestRandom->vTable->DigestFinal) (digestRandom, digestRandom->_output);
    available = digestRandom->_digestLen;

    /* increment state */
    if (digestRandom->_lessThanTwoUpdateCalls)
	{  /* Do old algorithm of adding one in a funny way. */
      for (i = 0; ((unsigned int)i) < digestRandom->_digestLen; i++)
        if (digestRandom->_state[digestRandom->_digestLen-1-i]++)
          break;
    } else
	{  /* Add large constant to state. */
      for (x = 0, i = digestRandom->_digestLen - 1 ; i >= 0 ; --i)
	  {
        x = digestRandom->_state[i] 
            + digestRandom->_oddConstant[i] + (x >> 8);
		digestRandom->_state[i] = (unsigned char) (x & 255);
	  }
	}
  }

  T_memcpy 
    ((POINTER)output,
     (POINTER)&digestRandom->_output[digestRandom->_digestLen-available],
     outputLen);
  digestRandom->_outputAvailable = available - outputLen;
}

