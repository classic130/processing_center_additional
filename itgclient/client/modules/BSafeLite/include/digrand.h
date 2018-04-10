/* Copyright (C) RSA Data Security, Inc. created 1992.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
   Modified 1995 to improve seeding.
 */

#ifndef _DIGRAND_H_
#define _DIGRAND_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* Use the THIS_DIGEST_RANDOM macro to define the type of object in the
     virtual function prototype.  It defaults to the most base class, but
     derived modules may define the macro to a more derived class before
     including this header file.
 */
#ifndef THIS_DIGEST_RANDOM
#define THIS_DIGEST_RANDOM struct A_DigestRandom
#endif

struct A_DigestRandom;

typedef  void (*DIGESTUPDATE) PROTO_LIST
   ((THIS_DIGEST_RANDOM *, unsigned char *, unsigned int));
typedef void (*DIGESTFINAL) PROTO_LIST
   ((THIS_DIGEST_RANDOM *, unsigned char *));

typedef struct {
  DIGESTUPDATE DigestUpdate;
  DIGESTFINAL DigestFinal;
} A_DigestRandomVTable;

typedef struct A_DigestRandom {
  unsigned int _newSeedToFinalize;	/* True if digest not finalized. */
  unsigned int _lessThanTwoUpdateCalls;  /* Initially 2, decrements to zero. */
  unsigned int _digestLen;			/* Byte len of _state, _oddConstant and _output. */
  unsigned char *_state;            /* State of generator. */
  unsigned char *_oddConstant;      /* Large odd constant to increment state. */
  unsigned char *_output;           /* Current output of digest. */
  unsigned int _outputAvailable;	/* Remaining digest bytes to output. */
  A_DigestRandomVTable *vTable;		/* Interface to digest object. */
} A_DigestRandom;

void A_DigestRandomInit PROTO_LIST
  ((A_DigestRandom *, unsigned int, unsigned char *));
void A_DigestRandomUpdate PROTO_LIST
  ((A_DigestRandom *, unsigned char *, unsigned int));
void A_DigestRandomGenerateBytes PROTO_LIST
  ((A_DigestRandom *, unsigned char *, unsigned int));

#if !GLOBAL_FUNCTION_POINTERS
void A_DigestRandomVTableInit PROTO_LIST
   ((A_DigestRandomVTable *, DIGESTUPDATE, DIGESTFINAL));
#endif

#ifdef __cplusplus
}
#endif

#endif
