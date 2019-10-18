/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _AGLOBAL_H_
#define _AGLOBAL_H_ 1

#ifdef __cplusplus
extern "C" {
#endif

/* The default calling convension is C.  If the application using PASCAL
   calling conversion then CALL_CONV should define as c calling so that
   the application can call the public API accordingly.
 */
#ifndef CALL_CONV
#define CALL_CONV
#endif
  
/* PROTOTYPES should be set to one if and only if the compiler supports
     function argument prototyping.
   The following makes PROTOTYPES default to 1 if it has not already been
     defined as 0 with C compiler flags.
 */
#ifndef PROTOTYPES
#define PROTOTYPES 1
#endif

/* GLOBAL_FUNCTION_POINTERS should be set to 0 if and only if the compiler
   cann't intitialize global or static function pointers like building MAC
   code resource.
 */
#ifndef GLOBAL_FUNCTION_POINTERS
#define GLOBAL_FUNCTION_POINTERS 1
#endif

/* The CMP library may have optimized code. It may require defining the
     following symbols in the compiler flag.

      platform      |   compiler flag
  ------------------|-----------------------
     Intel 16-bit   |  -DINTELx86=1
     Intel 32-bit   |  -DINTELx86i32=1
     DEC Alpha      |  -DCMP_DEC_ALPHA=1
 */

/* INTELx86i32 should be set to 1 if and only if the library is built for
   Intel machine on 32-bit operating systems. For Intel optimized code base,
   either INTELx86i32 or INTELx86 will be defined, but not both.   You are
   not allowed to define both.
   Setting this define causes the assembly language speed-ups to
   by included in the library.
*/
#ifndef INTELx86i32
#define INTELx86i32 0
#endif  

/* INTELx86 should be set to 1 if and only if the machine is Intel base
 */
#ifndef INTELx86
#define INTELx86 0
#endif

/* BIG_ENDIAN defaults to 1 for Macintosh and UNIX where the machine 
   architecture stores the most significant byte in the lowest 
   memory address.
 */
#if INTELx86 || INTELx86i32
#define BIG_ENDIAN 0
#define CAN_FETCH_UNALIGNED 1
#endif

#ifndef BIG_ENDIAN
#define BIG_ENDIAN 1
#endif  

/* CAN_FETCH_UNALIGNED is default to 0 to indicate that the CPU can't fetch
   UNIT4 values from unaligned byte addresses.  This enables speedups
   in the handling of 4 and 8 byte quantities (e.g., in CBC handing).
   Old Sun SPARC chips cannot do this.
 */
#ifndef CAN_FETCH_UNALIGNED
#define CAN_FETCH_UNALIGNED 0
#endif

/* POINTER defines a generic pointer type */
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

/* PROTO_LIST is defined depending on how PROTOTYPES is defined above.
   If using PROTOTYPES, then PROTO_LIST returns the list, otherwise it
     returns an empty list.  
 */
#if PROTOTYPES
#define PROTO_LIST(list) list
#else
#define PROTO_LIST(list) ()
#endif

#ifdef __cplusplus
}
#endif

#endif /* end _GLOBAL_H_ */
