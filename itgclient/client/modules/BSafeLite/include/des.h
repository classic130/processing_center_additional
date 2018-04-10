/* Copyright (C) RSA Data Security, Inc. created 1991.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _DES_H_
#define _DES_H_ 1


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  UINT4 keyTable[32];
} DES_CTX;

void DESEncryptInit PROTO_LIST ((DES_CTX *, POINTER));
void DESDecryptInit PROTO_LIST ((DES_CTX *, POINTER));
void DES PROTO_LIST ((POINTER, unsigned char *, unsigned char *));

/* deslib.h */
/* Copyright (C) 1993 Eric Young - */

typedef unsigned char des_cblock[8];

#define DES_KEY_SZ 	(sizeof(des_cblock))

/* des_locl.h */
/* Copyright (C) 1993 Eric Young */
/* #include <stdio.h>*/
/* #include "deslib.h" */

#define ITERATIONS 16
#define HALF_ITERATIONS 8

#if (BIG_ENDIAN == 0)
#define c2l(c,l)	{l = *((UINT4 *)c);\
                     (c) += 4;}
#else
#define c2l(c,l)	(l =((UINT4)(*((c)++))), \
			 l|=((UINT4)(*((c)++)))<< 8, \
			 l|=((UINT4)(*((c)++)))<<16, \
			 l|=((UINT4)(*((c)++)))<<24)
#endif

#if (BIG_ENDIAN == 0)
#define l2c(l,c)	{*((UINT4 *)c) = l;\
                     (c) += 4;}
#else
#define l2c(l,c)	(*((c)++)=(unsigned char)(((l)    )&0xff), \
			 *((c)++)=(unsigned char)(((l)>> 8)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>16)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>24)&0xff))
#endif

/* The changes to this macro may help or hinder, depending on the
 * compiler and the achitecture.  gcc2 always seems to do well :-).
 * Inspired by Dana How <how@isl.stanford.edu>
 * DO NOT use the alternative version on machines with 8 byte longs. */

#ifdef ALT_ECB
#define D_ENCRYPT(L,R,S) \
	u=((R^s[S  ])<<2);	\
	t= R^s[S+1]; \
	t=((t>>2)+(t<<30)); \
	L^= \
	*(UINT4 *)(des_SP+0x0100+((t    )&0xfc))+ \
	*(UINT4 *)(des_SP+0x0300+((t>> 8)&0xfc))+ \
	*(UINT4 *)(des_SP+0x0500+((t>>16)&0xfc))+ \
	*(UINT4 *)(des_SP+0x0700+((t>>24)&0xfc))+ \
	*(UINT4 *)(des_SP+       ((u    )&0xfc))+ \
  	*(UINT4 *)(des_SP+0x0200+((u>> 8)&0xfc))+ \
  	*(UINT4 *)(des_SP+0x0400+((u>>16)&0xfc))+ \
 	*(UINT4 *)(des_SP+0x0600+((u>>24)&0xfc));
#else /* original version */
#define D_ENCRYPT(L,R,S)	\
	u=(R^s[S  ]); \
	t=R^s[S+1]; \
	t=((t>>4)+(t<<28)); \
	L^=	des_SPtrans[1][ (int)((t)&0x3f) ]; \
	t >>= 8;\
	L^=	des_SPtrans[3][ (int)((t)&0x3f)]; \
	t >>= 8;\
	L^=	des_SPtrans[5][ (int)((t)&0x3f)]; \
	t >>= 8;\
	L^=	des_SPtrans[7][ (int)((t)&0x3f)]; \
	L^=	des_SPtrans[0][ (int)((u)&0x3f)]; \
	u >>= 8;\
	L^=	des_SPtrans[2][ (int)((u)&0x3f)]; \
	u >>= 8;\
	L^=	des_SPtrans[4][ (int)((u)&0x3f)]; \
	u >>= 8;\
	L^=	des_SPtrans[6][ (int)((u)&0x3f)];
#endif

	/* IP and FP
	 * The problem is more of a geometric problem that random bit fiddling.
	 0  1  2  3  4  5  6  7      62 54 46 38 30 22 14  6
	 8  9 10 11 12 13 14 15      60 52 44 36 28 20 12  4
	16 17 18 19 20 21 22 23      58 50 42 34 26 18 10  2
	24 25 26 27 28 29 30 31  to  56 48 40 32 24 16  8  0

	32 33 34 35 36 37 38 39      63 55 47 39 31 23 15  7
	40 41 42 43 44 45 46 47      61 53 45 37 29 21 13  5
	48 49 50 51 52 53 54 55      59 51 43 35 27 19 11  3
	56 57 58 59 60 61 62 63      57 49 41 33 25 17  9  1

	The output has been subject to swaps of the form
	0 1 -> 3 1 but the odd and even bits have been put into
	2 3    2 0
	different words.  The main trick is to remember that
	t=((l>>size)^r)&(mask);
	r^=t;
	l^=(t<<size);
	can be used to swap and move bits between words.

	So l =  0  1  2  3  r = 16 17 18 19
	        4  5  6  7      20 21 22 23
	        8  9 10 11      24 25 26 27
	       12 13 14 15      28 29 30 31
	becomes (for size == 2 and mask == 0x3333)
	   t =   2^16  3^17 -- --   l =  0  1 16 17  r =  2  3 18 19
		 6^20  7^21 -- --        4  5 20 21       6  7 22 23
		10^24 11^25 -- --        8  9 24 25      10 11 24 25
		14^28 15^29 -- --       12 13 28 29      14 15 28 29

	Thanks for hints from Richard Outerbridge - he told me IP&FP
	could be done in 15 xor, 10 shifts and 5 ands.
	When I finally started to think of the problem in 2D
	I first got ~42 operations without xors.  When I remembered
	how to use xors :-) I got it to its final state.
	*/
#define PERM_OP(a,b,t,n,m)\
   ((t)  = ((((a)>>(n))^(b))&(m)),\
	(b) ^= (t),\
	(a) ^= ((t)<<(n)))

#define IP(l,r,t) \
	PERM_OP(r,l,t, 4,0x0f0f0f0fl); \
	PERM_OP(l,r,t,16,0x0000ffffl); \
	PERM_OP(r,l,t, 2,0x33333333l); \
	PERM_OP(l,r,t, 8,0x00ff00ffl); \
	PERM_OP(r,l,t, 1,0x55555555l);

#define FP(l,r,t) \
	PERM_OP(l,r,t, 1,0x55555555l); \
	PERM_OP(r,l,t, 8,0x00ff00ffl); \
	PERM_OP(l,r,t, 2,0x33333333l); \
	PERM_OP(r,l,t,16,0x0000ffffl); \
	PERM_OP(l,r,t, 4,0x0f0f0f0fl);


#ifdef __cplusplus
}
#endif

#endif
