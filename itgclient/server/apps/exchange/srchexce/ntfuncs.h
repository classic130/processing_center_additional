/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/srchexce/Attic/ntfuncs.h,v 1.1.2.1 2000/03/15 00:13:35 aranade Exp $
 */

 /*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _NTFUNCS_H_
#define _NTFUNCS_H_

#ifndef __cplusplus
#error This file needs a C++ compiler
#endif

#ifndef WIN32
#error This file should be used only in an NT environment.
#endif

extern unsigned long elf_hash(const char *name) ;
extern char *basename(char *path) ;

#if 0
extern "C" {

void T_memset(void *, int, unsigned int);
void T_memcpy(void *, void*, unsigned int);
void T_memmove(void*, void*, unsigned int);
int T_memcmp(void*, void*, unsigned int);
void *T_malloc(unsigned int);
void *T_realloc(void*, unsigned int);
void T_free(void*);
void T_strcpy(char *, char *);
int T_strcmp(char *, char *);
unsigned int T_strlen(char *);

} ;

#endif
#endif/*_NTFUNCS_H_*/