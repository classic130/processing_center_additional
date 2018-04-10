/* Copyright (C) RSA Data Security, Inc. created 1995.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

/* Routines supplied by the implementor.
 */
#ifndef CALL_CONV
#define CALL_CONV
#endif

#if 0
/* memory manipulation
*/
#ifdef _STD_MEM_FUNCS_
void CALL_CONV T_memset (POINTER, int, unsigned int);
void CALL_CONV T_memcpy (POINTER, POINTER, unsigned int);
void CALL_CONV T_memmove (POINTER, POINTER, unsigned int);
int CALL_CONV T_memcmp (POINTER, POINTER, unsigned int);
#endif

/* memory allocation
*/
#ifdef _STD_ALLOC_FUNCS_
POINTER CALL_CONV T_malloc (unsigned int);
POINTER CALL_CONV T_realloc (POINTER, unsigned int);
void CALL_CONV T_free (POINTER);
#endif

/* string manipulation functions
*/
#ifdef _STD_STRING_FUNCS_
void CALL_CONV T_strcpy (char *, char *);
int CALL_CONV T_strcmp (char *, char *);
unsigned int CALL_CONV T_strlen (char *);
#endif

/* standard Time functions
 */
#ifdef _STD_TIME_FUNCS_
void CALL_CONV T_time (UINT4 *);
#endif

#endif

#define T_memset memset
#define T_memcpy memcpy
#define T_malloc malloc
#define T_free free
#define T_memmove memmove
