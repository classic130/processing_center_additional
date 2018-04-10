/* Copyright (C) RSA Data Security, Inc. created 1995.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* Header file for CMP Library.
 */

#if !defined(__CMP_H_)
#define __CMP_H_ 1

/* Include the file containing the function declarations of the T_
     routines (T_memset, T_malloc, etc.).
 */
#ifndef _STD_MEM_FUNCS_
#define _STD_MEM_FUNCS_    1
#endif
#ifndef _STD_ALLOC_FUNCS_
#define _STD_ALLOC_FUNCS_  1
#endif
#include "stdlibrf.h"

/* Definition of a CMPWord, the largest integer on the platform. */
typedef unsigned long CMPWord;

/* Definition of a CMPInt.
 */
typedef struct {
  int  space;      /* number of CMPWords currently allocated for the CMPInt */
  int  length;     /* length, in CMPWords, of the value */
  CMPWord *value;  /* value of the CMPInt, least significant CMPWord first */
} CMPInt;

/* Definition of a CMP_SURRENDER_CTX */
typedef A_SURRENDER_CTX CMP_SURRENDER_CTX;

/* Function definitions
 */

void CMP_Constructor (
  CMPInt *                              /* The CMPInt to be constructed */
);
void CMP_Destructor (
  CMPInt *                                /* The CMPInt to be destroyed */
);

int CMP_OctetStringToCMPInt (
  unsigned char *,                  /* The octet string to be converted */
  unsigned int,                 /* Length of the octet string, in bytes */
  CMPInt *                            /* The CMPInt taking on the value */
  );
int CMP_CMPIntToOctetString (
  CMPInt *,                              /* CMP integer to be converted */
  unsigned int,                       /* maximum number of output bytes */
  unsigned int *,                /* resulting number of bytes in output */
  unsigned char *             /* buffer for octet string representation */
  );
int CMP_CMPIntToFixedLenOctetStr (
  CMPInt *,                              /* CMP integer to be converted */
  unsigned int,      /* fixed length size of the resultint octet string */
  unsigned int,                       /* maximum number of output bytes */
  unsigned int *,                /* resulting number of bytes in output */
  unsigned char *             /* buffer for octet string representation */
  );

int CMP_CMPWordToCMPInt (
  CMPWord,                               /* The CMPWord to be converted */
  CMPInt *                            /* The CMPInt taking on the value */
);
int CMP_PowerOfTwo (
  int,                                        /* The power, or exponent */
  CMPInt *                            /* The CMPInt taking on the value */
);

int CMP_BitLengthOfCMPInt (
  CMPInt *           /* The CMPInt whose bit length is to be determined */
);
int CMP_GetBit (
  int,                         /* The index of the bit to be determined */
  CMPInt *,                /* The CMPInt containing the bit in question */
  int *      /* Pointer to where the routine should drop off the answer */
);
int CMP_SetBit (
  int,                                /* The index of the bit to be set */
  CMPInt *                 /* The CMPInt containing the bit in question */
);
int CMP_ClearBit (
  int,                            /* The index of the bit to be cleared */
  CMPInt *                 /* The CMPInt containing the bit in question */
);

int VS_CMP_Move (
  CMPInt *,                                            /* Source CMPInt */
  CMPInt *                                        /* Destination CMPInt */
);
int VS_CMP_Compare (
  CMPInt *,
  CMPInt *
);
int VS_CMP_AddCMPWord (
  CMPWord,                                             /* The increment */
  CMPInt *                                         /* The base (result) */
);
int VS_CMP_SubtractCMPWord (
  CMPWord,                                             /* The decrement */
  CMPInt *                                         /* The base (result) */
);
int VS_CMP_Add (
  CMPInt *,                                         /* The first addend */
  CMPInt *,                                        /* The second addend */
  CMPInt *                                          /* The sum (result) */
);
int VS_CMP_Subtract (
  CMPInt *,                                              /* The minuend */
  CMPInt *,                                           /* The subtrahend */
  CMPInt *                                   /* The difference (result) */
);
int CMP_Multiply (
  CMPInt *,                                         /* The multiplicand */
  CMPInt *,                                           /* The multiplier */
  CMPInt *                                      /* The product (result) */
);
int CMP_Divide (
  CMPInt *,                                             /* The dividend */
  CMPInt *,                                              /* The divisor */
  CMPInt *,                                    /* The quotient (result) */
  CMPInt *                                    /* The remainder (result) */
);
int CMP_ModularReduce (
  CMPInt *,                                 /* The CMPInt to be reduced */
  CMPInt *,                                              /* The modulus */
  CMPInt *                                /* The reduced value (result) */
);
int CMP_CMPWordModularReduce (
  CMPInt *,                                 /* The CMPInt to be reduced */
  CMPWord,                                       /* The CMPWord modulus */
  CMPWord *                               /* The reduced value (result) */
);
int CMP_ComputeGCD (
  CMPInt *,                                      /* One of the operands */
  CMPInt *,                                        /* The other operand */
  CMPInt *                      /* The greatest common divisor (result) */
);
int CMP_ModAdd (
  CMPInt *,                                         /* The first addend */
  CMPInt *,                                        /* The second addend */
  CMPInt *,                                              /* The modulus */
  CMPInt *                                          /* The sum (result) */
);
int CMP_ModSubtract (
  CMPInt *,                                              /* The minuend */
  CMPInt *,                                           /* The subtrahend */
  CMPInt *,                                              /* The modulus */
  CMPInt *                                   /* The difference (result) */
);
int CMP_ModMultiply (
  CMPInt *,                                         /* The multiplicand */
  CMPInt *,                                           /* The multiplier */
  CMPInt *,                                              /* The modulus */
  CMPInt *                                      /* The product (result) */
);
int CMP_ModInvert (
  CMPInt *,                                /* The CMPInt to be inverted */
  CMPInt *,                                              /* The modulus */
  CMPInt *                                      /* The inverse (result) */
);
int VS_CMP_ModExp (
  CMPInt *,                                                 /* The base */
  CMPInt *,                                             /* The exponent */
  CMPInt *,                                              /* The modulus */
  CMPInt *,                                    /* where the result goes */
  CMP_SURRENDER_CTX *                          /* the surrender context */
);
int VS_CMP_ModExpCRT (
  CMPInt *,                                                 /* The base */
  CMPInt *,                                /* The first prime -- primeP */
  CMPInt *,                               /* The second prime -- primeQ */
  CMPInt *,                    /* The first prime exponent -- exponentP */
  CMPInt *,                   /* The second prime exponent -- exponentQ */
  CMPInt *,                                      /* The CRT coefficient */
  CMPInt *,                                    /* where the result goes */
  CMP_SURRENDER_CTX *                          /* the surrender context */
);

/* Error codes
 */
#define CMP_MEMORY              0x100
#define CMP_INVALID_ADDRESS     0x101
#define CMP_LENGTH              0x102
#define CMP_INVALID_VALUE       0x103
#define CMP_INVALID_ARGUMENT    0x104
#define CMP_INSUFFICIENT_SPACE  0x105
#define CMP_ZERO_DIVIDE         0x106
#define CMP_MODULUS             0x107
#define CMP_RANGE               0x108
#define CMP_NEGATIVE            0x109
#define CMP_DOMAIN              0x10a
#define CMP_INVERSE             0x10b
#define CMP_OUTPUT_LENGTH       0x10c

#endif    /* __CMP_H_ */
