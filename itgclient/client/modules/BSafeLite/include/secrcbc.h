/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _SECRCBC_H_
#define _SECRCBC_H_ 1

/* The modes are defined in the AH header file. */
#include "global.h"
#include "bsafelite.h"
/*#include "bkey.h"*/
/*#include "balgmeth.h"
#include "balg.h"
*/
/*#include "ahchencr.h"*/

#ifdef __cplusplus
extern "C" {
#endif

/* Values for the algaMode field. */
/* Default. For CBC without padding. */
#define MODE_CBC_Pad_0		0  
/* For CBC with padding. */
#define MODE_CBC_Pad_8		1  
/* For BSAFE1 modes with padding and checksum. */
#define MODE_CBC_Pad_16		2

/* Use the THIS_ALG_CBC macro to define the type of object in the
     virtual function prototype.  It defaults to the most base class, but
     derived modules may define the macro to a more derived class before
     including this header file.
 */
#ifndef THIS_ALG_CBC
#define THIS_ALG_CBC struct A_CBC_CTX
#endif

typedef struct A_CBC_CTX {
  unsigned char iv[8];
  unsigned char xorBlock[8];
  unsigned char remainder[16];
  /* remainderLen ranges from 0 to 7 for encrypt and 0 to 16 for decrypt */
  unsigned int remainderLen;
  unsigned int mode;
} A_CBC_CTX;

#ifndef UINT1
#define UINT1 unsigned char
#endif

/* LOAD_8_UNALIGNED	& STORE_8_UNALIGNED
   These macros quickly fetch blocks of 8 bytes.  
   The fetching is performed in either little endian or big endian
   mode, depending on the BIG_ENDIAN define.
   The result is placed into an aligned array of 
   two UINT4s with the low four bytes in the first UINT4.

   Little endian order means the lowest byte address becomes
   the least significant byte, and successive bytes have increasing
   significance.  Big endian order places the most significant
   byte in the lowest memory address.  

   CAN_FETCH_UNALIGNED is set to 1 to indicate that the CPU can fetch
   UNIT4 values from unaligns byte addresses.  This enables speedups
   in the handling of 4 and 8 byte quantities (e.g., in CBC handing).
   Old Sun SPARC chips cannot do this.

   BIG_ENDIAN defaults to 1 for Macintosh and UNIX where the machine 
   architecture stores the most significant byte on the left.  
 */
#if (CAN_FETCH_UNALIGNED == 1)
#define LOAD_8_UNALIGNED(alignedDST, unalignedSRC) \
  { \
    ((UINT4 *)(alignedDST))[0] = ((UINT4 *)(unalignedSRC))[0]; \
    ((UINT4 *)(alignedDST))[1] = ((UINT4 *)(unalignedSRC))[1]; \
  }
#define STORE_8_UNALIGNED(alignedSRC, unalignedDST) \
  { \
    ((UINT4 *)(unalignedDST))[0] = ((UINT4 *)(alignedSRC))[0]; \
    ((UINT4 *)(unalignedDST))[1] = ((UINT4 *)(alignedSRC))[1]; \
  }
#endif
#if (CAN_FETCH_UNALIGNED == 0) && (BIG_ENDIAN != 0)
/* If can't fetch unaliagned and need big endian order */
#define LOAD_8_UNALIGNED(alignedDST, unalignedSRC) \
  { \
    ((UINT4 *)(alignedDST))[0] = ( \
        ((((unsigned char *)(unalignedSRC))[0] & 255) << 24) + \
        ((((unsigned char *)(unalignedSRC))[1] & 255) << 16) + \
        ((((unsigned char *)(unalignedSRC))[2] & 255) <<  8) + \
        ((((unsigned char *)(unalignedSRC))[3] & 255) <<  0) ); \
    ((UINT4 *)(alignedDST))[1] = ( \
        ((((unsigned char *)(unalignedSRC))[4] & 255) << 24) + \
        ((((unsigned char *)(unalignedSRC))[5] & 255) << 16) + \
        ((((unsigned char *)(unalignedSRC))[6] & 255) <<  8) + \
        ((((unsigned char *)(unalignedSRC))[7] & 255) <<  0) ); \
  }
#define STORE_8_UNALIGNED(alignedSRC, unalignedDST) \
  { \
    ((unsigned char *)(unalignedDST))[0] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >> 24 ) & 255); \
    ((unsigned char *)(unalignedDST))[1] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >> 16 ) & 255); \
    ((unsigned char *)(unalignedDST))[2] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >>  8 ) & 255); \
    ((unsigned char *)(unalignedDST))[3] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >>  0 ) & 255); \
    ((unsigned char *)(unalignedDST))[4] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >> 24 ) & 255); \
    ((unsigned char *)(unalignedDST))[5] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >> 16 ) & 255); \
    ((unsigned char *)(unalignedDST))[6] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >>  8 ) & 255); \
    ((unsigned char *)(unalignedDST))[7] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >>  0 ) & 255); \
  }
#endif
#if (CAN_FETCH_UNALIGNED == 0) && (BIG_ENDIAN == 0)
/* If can't fetch unaliagned and need little endian order */
#define LOAD_8_UNALIGNED(alignedDST, unalignedSRC) \
  { \
    ((UINT4 *)(alignedDST))[0] = ( \
        ((((unsigned char *)(unalignedSRC))[0] & 255) <<  0) + \
        ((((unsigned char *)(unalignedSRC))[1] & 255) <<  8) + \
        ((((unsigned char *)(unalignedSRC))[2] & 255) << 16) + \
        ((((unsigned char *)(unalignedSRC))[3] & 255) << 24) ); \
    ((UINT4 *)(alignedDST))[1] = ( \
        ((((unsigned char *)(unalignedSRC))[4] & 255) <<  0) + \
        ((((unsigned char *)(unalignedSRC))[5] & 255) <<  8) + \
        ((((unsigned char *)(unalignedSRC))[6] & 255) << 16) + \
        ((((unsigned char *)(unalignedSRC))[7] & 255) << 24) ); \
  }
#define STORE_8_UNALIGNED(alignedSRC, unalignedDST) \
  { \
    ((unsigned char *)(unalignedDST))[0] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >>  0 ) & 255); \
    ((unsigned char *)(unalignedDST))[1] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >>  8 ) & 255); \
    ((unsigned char *)(unalignedDST))[2] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >> 16 ) & 255); \
    ((unsigned char *)(unalignedDST))[3] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[0] >> 24 ) & 255); \
    ((unsigned char *)(unalignedDST))[4] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >>  0 ) & 255); \
    ((unsigned char *)(unalignedDST))[5] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >>  8 ) & 255); \
    ((unsigned char *)(unalignedDST))[6] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >> 16 ) & 255); \
    ((unsigned char *)(unalignedDST))[7] = \
	  (UINT1)(( ((UINT4 *)(alignedSRC))[1] >> 24 ) & 255); \
  }
#endif

typedef void (*SECRET_CRYPT) PROTO_LIST
  ((POINTER, unsigned char *, unsigned char *));

void SecretCBCRestart PROTO_LIST ((THIS_ALG_CBC *));
void SecretCBCInit PROTO_LIST ((THIS_ALG_CBC *, unsigned char *, int));
void SecretCBCIVUpdate PROTO_LIST ((A_CBC_CTX *, unsigned char *iv));

int SecretCBCEncryptUpdate PROTO_LIST
  ((THIS_ALG_CBC *, POINTER, SECRET_CRYPT, unsigned char *,
    unsigned int *, unsigned int, unsigned char *, unsigned int));
int SecretCBCEncryptFinal PROTO_LIST ((THIS_ALG_CBC *));

int SecretCBCDecryptUpdate PROTO_LIST
  ((THIS_ALG_CBC *, POINTER, SECRET_CRYPT, unsigned char *,
    unsigned int *, unsigned int, unsigned char *, unsigned int));
int SecretCBCDecryptFinal PROTO_LIST
  ((THIS_ALG_CBC *, POINTER, SECRET_CRYPT, unsigned char *,
    unsigned int *, unsigned int));

#ifdef __cplusplus
}
#endif

#endif
