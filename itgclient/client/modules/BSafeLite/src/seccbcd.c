/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#include "global.h"
#include "algae.h"
#include "secrcbc.h"

/* For now, assume that all ciphers use 8 byte blocks. */
#define CIPHER_BLOCK_LEN 8


/* On first call, it is assumed that *remainderLen is zero.
   The remainder buffer should be at least 16 bytes long
   to handle future 128 bit cipher block lengths.
   For CBC_Pad mode, we must hold on to the last 8 bytes so
   we can strip out the padding if the client calls CBCPadFinal.
   In non-padding modes, we can decrypt each block of 8 bytes
   as we are given them.  Non-padding has mode == BUFFER_8_BYTES.
   Returns AE_OUTPUT_LEN, AE_NOT_INITIALIZED, or 0.
 */
int SecretCBCDecryptUpdate
  (cbcCtx, algCtx, SecretDecrypt, output, outputLen, maxOutputLen,
   input, inputLen)
A_CBC_CTX *cbcCtx;
POINTER algCtx;
SECRET_CRYPT SecretDecrypt;
unsigned char *output;
unsigned int *outputLen;
unsigned int maxOutputLen;
unsigned char *input;
unsigned int inputLen;
{
  unsigned int partialLen, totalLen;
  UINT4 inputBuffer[2];
  int i;
  unsigned char *p, *q;
  unsigned int minToBuffer, maxToBuffer;
  UINT4  localBuffer[2];  /* 8 bytes of aligned storage. */


  if (cbcCtx->mode == MODE_CBC_Pad_0) {
	minToBuffer = 0;
  } else if (cbcCtx->mode == MODE_CBC_Pad_8) {
	minToBuffer = 1;
  } else if (cbcCtx->mode == MODE_CBC_Pad_16) {
	minToBuffer = 1 + CIPHER_BLOCK_LEN;
  } else {
    *outputLen = 0;
    return (AE_NOT_INITIALIZED);
  }
  maxToBuffer = CIPHER_BLOCK_LEN - 1 + minToBuffer;

  /* Can assume that 0 <= remainderLen <= maxToBuffer. */

  /* Figure out how many blocks we will output. */
  totalLen = cbcCtx->remainderLen + inputLen;
  if (totalLen >= minToBuffer) {
    *outputLen = ((totalLen - minToBuffer) / CIPHER_BLOCK_LEN) * CIPHER_BLOCK_LEN;
  } else {
    *outputLen = 0;
  }

  /* Check that we have enough room. */
  if (*outputLen > maxOutputLen) {
    *outputLen = 0;  /* Indicate that nothing was produced. */
    return (AE_OUTPUT_LEN);
  }

  if (inputLen == 0) {
  	return (0);
  }

  /* Can assume that inputLen > 0. */
  /* Can assume that there is room for all required output.  */
  /* Can assume that 0 <= remainderLen <= maxToBuffer. */

  /* Output required blocks made up of remainder bytes */
  /* and possibly some input bytes. */
  /* This loop will be executed at most twice. */
  while ((cbcCtx->remainderLen > 0) &&
         (cbcCtx->remainderLen + inputLen > maxToBuffer))
  {
  	  /* Fill up the remainder buffer if necessary. */
	  if (cbcCtx->remainderLen < CIPHER_BLOCK_LEN) {
		  partialLen = CIPHER_BLOCK_LEN - cbcCtx->remainderLen;
	      /* Can assume that inputLen >= partialLen, since  */
		  /* remainderLen + inputLen > maxToBuffer, and */
		  /* maxToBuffer >= CIPHER_BLOCK_LEN - 1 */
		  p = cbcCtx->remainder + cbcCtx->remainderLen;
		  q = input;
		  i = partialLen;
		  while (--i >= 0)  {
		    *p++ = *q++;
		    }
		  input += partialLen;
		  inputLen -= partialLen;
		  cbcCtx->remainderLen = CIPHER_BLOCK_LEN;
	  }    

	  /* Output a block */
	  (*SecretDecrypt) (algCtx, (UINT1 *)localBuffer, cbcCtx->remainder);
	  localBuffer[0] ^= ((UINT4 *) cbcCtx->xorBlock)[0]; 
	  localBuffer[1] ^= ((UINT4 *) cbcCtx->xorBlock)[1];
	  STORE_8_UNALIGNED(localBuffer, output);
	  ((UINT4 *) cbcCtx->xorBlock)[0] = ((UINT4 *) cbcCtx->remainder)[0];
	  ((UINT4 *) cbcCtx->xorBlock)[1] = ((UINT4 *) cbcCtx->remainder)[1];
	  output += CIPHER_BLOCK_LEN;
	  cbcCtx->remainderLen -= CIPHER_BLOCK_LEN;

	  /* Shuffle down remainder.*/
	  /* This assumes that sizeof(cbcCtx->remainder) == 16 */
	  ((UINT4 *) cbcCtx->remainder)[0] = ((UINT4 *) cbcCtx->remainder)[2];
	  ((UINT4 *) cbcCtx->remainder)[1] = ((UINT4 *) cbcCtx->remainder)[4];
  }

  /* Can assume that remainderLen == 0, or. */
  /*  that remainderLen + inputLen <= maxToBuffer */
  /*    and remainderLen > 0 */
  /* The inputLen might now be less than maxToBuffer. */
  /* Can assume that there is room for all required output.  */

  /* Now decrypt the bulk of the input with CBC xor'ing. */
  while (inputLen > maxToBuffer) {
    /* Save the input as the next XOR in case input == output. */
    LOAD_8_UNALIGNED(inputBuffer, input);
    (*SecretDecrypt) (algCtx, (UINT1 *)localBuffer, (UINT1 *)inputBuffer);
    localBuffer[0] ^= ((UINT4 *) cbcCtx->xorBlock)[0]; 
    localBuffer[1] ^= ((UINT4 *) cbcCtx->xorBlock)[1]; 
	STORE_8_UNALIGNED(localBuffer, output);
    ((UINT4 *) cbcCtx->xorBlock)[0] = inputBuffer[0];
    ((UINT4 *) cbcCtx->xorBlock)[1] = inputBuffer[1];
    output += CIPHER_BLOCK_LEN;
    input += CIPHER_BLOCK_LEN;
    inputLen -= CIPHER_BLOCK_LEN;
  }

  /* Can assume that minToBuffer <= cbcCtx->remainder + inputLen
     and cbcCtx->remainder + inputLen <= maxToBuffer.
     Copy rest of input to the remainder buffer.
   */
  p = cbcCtx->remainder + cbcCtx->remainderLen;
  q = input;
  i = inputLen;
  while (--i >= 0)  {
    *p++ = *q++;
    }
  cbcCtx->remainderLen += inputLen;
  /* On exit, minToBuffer <= remainderLen <= maxToBuffer. */
  return (0);
}

/* Returns AE_INPUT_LEN, AE_OUTPUT_LEN, 0.
 */
int SecretCBCDecryptFinal
  (cbcCtx, algCtx, SecretDecrypt, output, outputLen, maxOutputLen)
A_CBC_CTX *cbcCtx;
POINTER algCtx;
SECRET_CRYPT SecretDecrypt;
unsigned char *output;
unsigned int *outputLen;
unsigned int maxOutputLen;
{
  int status = 0;
  UINT4  localBuffer[2];  /* 8 bytes of aligned storage. */

  do {
	  *outputLen = 0;
	  if (cbcCtx->remainderLen == 0)
      break;
	
	  if (cbcCtx->remainderLen > maxOutputLen) {
	    status = AE_OUTPUT_LEN;
      break;
	  }
	  if (cbcCtx->remainderLen != 8 && cbcCtx->remainderLen != 16) {
	    status = AE_INPUT_LEN;
      break;
	  }
	  *outputLen = cbcCtx->remainderLen;

	  (*SecretDecrypt) (algCtx, (UINT1 *)localBuffer, cbcCtx->remainder);
	  localBuffer[0] ^= ((UINT4 *) cbcCtx->xorBlock)[0]; 
	  localBuffer[1] ^= ((UINT4 *) cbcCtx->xorBlock)[1]; 
      STORE_8_UNALIGNED(localBuffer, output);
	  output += 8;

	  if (cbcCtx->remainderLen == 16) {
	    (*SecretDecrypt) (algCtx, (UINT1 *)localBuffer, cbcCtx->remainder + 8);
	    localBuffer[0] ^= ((UINT4 *) cbcCtx->remainder)[0]; 
	    localBuffer[1] ^= ((UINT4 *) cbcCtx->remainder)[1]; 
        STORE_8_UNALIGNED(localBuffer, output);
		/* output += 8; */
		}
  } while (0);
  SecretCBCRestart (cbcCtx);
  return (status);
}

