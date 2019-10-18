/*
 * File Bsafelite.h: general definitions for bsafelite
 */

#ifndef		__VS_BSAFE_LITE__
#define		__VS_BSAFE_LITE__

typedef unsigned char *POINTER;

/* UINT2 defines a two byte word */
typedef unsigned short int UINT2;

/* UINT4 defines a four byte word */
#ifndef MACHINE64
typedef unsigned long int UINT4;
#else
typedef unsigned int UINT4;
#endif

#ifndef NULL_PTR
#define NULL_PTR ((POINTER)0)
#endif

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) x = *(&x);
#endif

#ifndef CALL_CONV
#define CALL_CONV
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ITEM_
#define _ITEM_ 1
typedef struct {
  unsigned char *data;
  unsigned int len;
} ITEM;
#endif

#ifndef _A_SURRENDER_CTX_
#define _A_SURRENDER_CTX_ 1
typedef struct {
  int (CALL_CONV *Surrender) (POINTER);
  POINTER handle;
  POINTER reserved;
} A_SURRENDER_CTX;
#endif

//typedef struct {
//  ITEM modulus;
//  ITEM publicExponent;
//  ITEM privateExponent;
//  ITEM prime[2];                                            /* prime factors */
//  ITEM primeExponent[2];                      /* exponents for prime factors */
//  ITEM coefficient;                                       /* CRT coefficient */
//} A_PKCS_RSA_PRIVATE_KEY;

//typedef struct {
//  ITEM modulus;
//  ITEM prime[2];                                            /* prime factors */
//  ITEM primeExponent[2];                      /* exponents for prime factors */
//  ITEM coefficient;                                       /* CRT coefficient */
//} A_RSA_CRT_KEY;

//typedef struct {
//  ITEM modulus;                                                   /* modulus */
//  ITEM exponent;                                                 /* exponent */
//} A_RSA_KEY;

//typedef struct {
//  unsigned int modulusBits;
//  ITEM publicExponent;
//} A_RSA_KEY_GEN_PARAMS;


/* Information data structure used by FIPS SHA Random number generator */
//typedef struct {
//ITEM prime;
//ITEM seed;
//} A_SHA_RANDOM_PARAMS;

#ifndef _STD_ALLOC_FUNCS_
#define _STD_ALLOC_FUNCS_
#endif

#ifndef _STD_MEM_FUNCS_
#define _STD_MEM_FUNCS_
#endif


#define AE_CANCEL 0x0001
#define AE_DATA 0x0002
#define AE_EXPONENT_EVEN 0x0003
#define AE_EXPONENT_LEN 0x0004
#define AE_INPUT_DATA 0x0005
#define AE_INPUT_LEN 0x0006
#define AE_MODULUS_LEN 0x0007
#define AE_NEED_RANDOM 0x0008
#define AE_NOT_SUPPORTED 0x0009
#define AE_OUTPUT_LEN 0x000a
#define AE_NOT_INITIALIZED 0x000b
#define AE_KEY_LEN 0x000c
#define AE_KEY_INFO 0x000d
#define AE_SEQUENCE 0x000e
#define AE_PARAMS 0x000f
#define AE_ALLOC 0x0080

unsigned int CALL_CONV A_IntegerBits (unsigned char *, unsigned int);

int CALL_CONV ALG_ErrorCode (int);

#define BSAFE_MAX_RSA_KEY_SIZE_BITS     2048
#define BSAFE_MIN_RSA_KEY_SIZE_BITS     256

#define MAX_RSA_MODULUS_BITS         BSAFE_MAX_RSA_KEY_SIZE_BITS
#define MIN_RSA_MODULUS_BITS         BSAFE_MIN_RSA_KEY_SIZE_BITS

#define BITS_PER_BYTE                8
#define BITS_TO_LEN(modulusBits)     \
  (((modulusBits) + BITS_PER_BYTE - 1) / BITS_PER_BYTE)
#define RSA_PRIME_BITS(modulusBits)  (((modulusBits) + 1) / 2)
#define RSA_PRIME_LEN(modulusBits)   \
  ((RSA_PRIME_BITS (modulusBits) + BITS_PER_BYTE - 1) / BITS_PER_BYTE)

#include <memory.h>
#include <malloc.h>
#include <string.h>
#include "stdlibrf.h"
#include "cmp.h"
#include "cmpspprt.h"

int CheckSurrender (A_SURRENDER_CTX *);
int ALG_ErrorCode (int status);

#ifdef __cplusplus
}
#endif

#endif