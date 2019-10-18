/* Copyright (C) RSA Data Security, Inc. created 1995.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* This file contatins function prototypes for various support routines.
     Any source code that includes this header file should also include
     cmp.h first.
 */

#if !defined(__CMPSPPRT_H_)
#define __CMPSPPRT_H_ 1

int VS_CMP_GetOffsetOfMSB (
  CMPInt *,                      /* The CMPInt whose MSB is of interest */
  int *            /* Pointer to where the routine will drop the answer */
);
int VS_CMP_ShiftLeftByCMPWords (
  int,                                 /* Number of words to shift left */
  CMPInt *                                           /* CMPInt to shift */
  );
int VS_CMP_ShiftRightByCMPWords (
  int,                                /* Number of words to shift right */
  CMPInt *                                           /* CMPInt to shift */
  );  
int VS_CMP_ShiftLeftByBits (
  int,                                  /* Number of bits to shift left */
  CMPInt *                                           /* CMPInt to shift */
);
int VS_CMP_ShiftRightByBits (
  int,                                 /* Number of bits to shift right */
  CMPInt *                                           /* CMPInt to shift */
);
int VS_CMP_RecomputeLength (
  int,                                                  /* Target index */
  CMPInt *                     /* The CMPInt whose length is recomputed */
  );
int VS_CMP_AddInPlace (
  CMPInt *,                                            /* The increment */
  CMPInt *                                         /* The base (result) */
);
int VS_CMP_SubtractInPlace (
  CMPInt *,                                            /* The decrement */
  CMPInt *                                                  /* The base */
);
int CMP_ComputeExtendedGCD (
  CMPInt *,                                        /* The first operand */
  CMPInt *,                                       /* The second operand */
  CMPInt *,                /* Coefficient of the first operand (result) */
  CMPInt *,               /* Coefficient of the second operand (result) */
  CMPInt *                      /* The greatest common divisor (result) */
);
int CMP_ConvertToMont (
  CMPInt *,                               /* The CMPInt to be converted */
  CMPInt *,                                              /* The modulus */
  CMPInt *                    /* The Montgomery representation (result) */
  );
int CMP_ConvertFromMont (
  CMPInt *,                   /* The value in Montgomery representation */
  CMPInt *,                                              /* The modulus */
  CMPWord,                                                   /* n0Prime */
  CMPInt *                             /* The converted CMPInt (result) */
  );
int CMP_MontSquare (
  CMPInt *,                       /* The Montgomery value to be squared */
  CMPInt *,                                              /* The modulus */
  CMPWord,                                                   /* n0Prime */
  CMPInt *                            /* The Montgomery square (result) */
);
int CMP_MontProduct (
  CMPInt *,                              /* The Montgomery multiplicand */
  CMPInt *,                                /* The Montgomery multiplier */
  CMPInt *,                                              /* The modulus */
  CMPWord,                                                   /* n0Prime */
  CMPInt *                           /* The Montgomery product (result) */
);
int CMP_ComputeMontCoeff (
  CMPInt *,                                              /* The modulus */
  CMPWord *                                         /* n0Prime (result) */
);
void CMP_VectorMultiply (
  CMPWord,                                                /* The scaler */
  CMPInt *,                                                  /* vectorA */
  int,                                            /* index into vectorA */
  int,                                             /* length of vectorA */
  CMPInt *,                                                  /* vectorB */
  int                                             /* index into vectorB */
);
void CMP_AddInTrace (
  CMPInt *,                                                  /* vectorA */
  CMPInt *                                                   /* vectorB */
);

/* Macros for multiplying and squaring two CMPWords, then either keeping
     both the high and low CMPWord result, or simply keeping the low
     CMPWord result.
 */
#if CMP_DEC_ALPHA == 1
#include <c_asm.h>
#define CMP_MULT_LOW(a , b, lowProd) {\
  lowProd = asm ("mulq %a0, %a1, %v0", a, b);\
  }

#define CMP_MULT_HIGHLOW(a , b, lowProd, highProd) {\
  lowProd  = asm ("mulq %a0, %a1, %v0", a, b);\
  highProd = asm ("umulh %a0, %a1, %v0", a, b);\
  }

#define CMP_SQUARE_HIGHLOW(a, lowProd, highProd) {\
  lowProd  = asm ("mulq %a0, %a0, %v0", a);\
  highProd = asm ("umulh %a0, %a0, %v0", a);\
  }

#else   /* CMP_DEC_ALPHA */
#define CMP_MULT_LOW(a , b, lowProd) {\
  CMPWord mixProd;\
  CMPWord lowWordA, lowWordB, highWordA, highWordB;\
  lowWordA  = CMP_LOW_WORD (a);\
  lowWordB  = CMP_LOW_WORD (b);\
  highWordA = CMP_HIGH_WORD (a);\
  highWordB = CMP_HIGH_WORD (b);\
  lowProd   = lowWordA * lowWordB;\
  mixProd   = lowWordA * highWordB + highWordA * lowWordB;\
  mixProd <<= CMP_HALF_WORD_SIZE;\
  lowProd  += mixProd;\
  }

#define CMP_MULT_HIGHLOW(a , b, lowProd, highProd) {\
  CMPWord a1b0, a0b1, mixProd;\
  CMPWord lowWordA, lowWordB, highWordA, highWordB;\
  lowWordA  = CMP_LOW_WORD (a);\
  lowWordB  = CMP_LOW_WORD (b);\
  highWordA = CMP_HIGH_WORD (a);\
  highWordB = CMP_HIGH_WORD (b);\
  lowProd   = lowWordA * lowWordB;\
  highProd  = highWordA * highWordB;\
  a0b1      = lowWordA * highWordB;\
  a1b0      = lowWordB * highWordA;\
  mixProd   = a0b1 + a1b0;\
  if (mixProd < a0b1) highProd += CMP_SQRT_RADIX ;\
  highProd += CMP_HIGH_WORD (mixProd);\
  mixProd <<= CMP_HALF_WORD_SIZE;\
  lowProd  += mixProd;\
  if (lowProd < mixProd) highProd++;\
  }

#define CMP_SQUARE_HIGHLOW(a, lowProd, highProd) {\
  CMPWord a0a1, mixProd;\
  CMPWord lowHalfA, highHalfA;\
  lowHalfA  = CMP_LOW_WORD (a);\
  highHalfA = CMP_HIGH_WORD (a);\
  lowProd   = lowHalfA * lowHalfA;\
  highProd  = highHalfA * highHalfA;\
  a0a1      = lowHalfA * highHalfA;\
  mixProd   = a0a1 << 1;\
  if (mixProd < a0a1) highProd += CMP_SQRT_RADIX ;\
  highProd += CMP_HIGH_WORD (mixProd);\
  mixProd <<= CMP_HALF_WORD_SIZE;\
  lowProd  += mixProd;\
  if (lowProd < mixProd) highProd++;\
}
#endif    /* CMP_DEC_ALPHA */

#endif    /* __CMPSPPRT_H_ */
