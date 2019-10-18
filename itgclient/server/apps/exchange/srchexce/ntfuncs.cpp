/*
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/srchexce/Attic/ntfuncs.cpp,v 1.1.2.1 2000/03/15 00:13:34 aranade Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include <string.h>
#include <stdlib.h>
#include "ntfuncs.h"

/*
 * Temporary implementation for elf_hash. This uses a simple XOR hashing mechanism,
 * should be replaced with something more sensible
 */

unsigned long elf_hash(const char *name)
{
	unsigned long *ptr = (unsigned long *)name ;
	unsigned long tmp = 0 ;
	unsigned int len = strlen(name) ;
	unsigned int i ;
	for( i = 0 ; i < (len / sizeof(unsigned long)) ; i++ )
	{
		tmp = tmp ^ ptr[i] ;
	}
	unsigned int remainder = len - (i* sizeof(unsigned long)) ;
	
	if( remainder )
	{
		unsigned long tmp2 = 0 ;
		char *ptr2 = (char *)&tmp2 ;
		for( i = 0 ; i < remainder ; i++ )
		{
			ptr2[i] = name[len - (remainder - i)] ;
		}
		tmp = tmp ^ tmp2 ;
	}
	if( tmp == (~0UL) ) return 0UL ;
	return tmp ;
}

char *basename(char *path)
{
	static char drive[_MAX_DRIVE +1] ;
	static char dir[_MAX_DIR +1] ;
	static char file[_MAX_FNAME + _MAX_EXT + 1] ;
	static char ext[_MAX_EXT +1] ;
	_splitpath(path, drive, dir, file, ext) ;
	strcat(file, ext) ;
	return file ;
}

#if 0
void T_memset(void *a, int b, unsigned int c)
{
	memset(a,b,c) ;
}

void T_memcpy(void *a, void*b, unsigned int c)
{
	memcpy(a,b,c) ;
}

void T_memmove(void*a, void*b, unsigned int c)
{
	memmove(a,b,c) ;
}

int T_memcmp(void* a, void* b, unsigned int c)
{
	return memcmp(a,b,c) ;
}

void *T_malloc(unsigned int a)
{
	return malloc(a) ;
}

void *T_realloc(void* a, unsigned int b)
{
	return realloc(a,b) ;
}

void T_free(void* a)
{
	free(a) ;
}

void T_strcpy(char * a, char * b)
{
	strcpy(a,b) ;
}

int T_strcmp(char *a, char *b)
{
	return strcmp(a,b) ;
}

unsigned int T_strlen(char * a)
{
	return strlen(a) ;
}
#endif