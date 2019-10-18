/*****************************************************************************/
/* Copyright (C) 1989-1998 Open Systems Solutions, Inc.  All rights reserved.*/
/*****************************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OPEN SYSTEMS SOLUTIONS, INC.
 * AND MAY ONLY BE USED BY DIRECT LICENSEES OF OPEN SYSTEMS SOLUTIONS, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED. */

/*************************************************************************/
/* FILE: @(#)etype.h	6.18  98/04/05			 */
#include <stddef.h>		/* has size_t */
#include "ossdll.h"
#define OSS_SPARTAN_AWARE 3
#ifndef NULL
#define NULL ((void*)0)
#endif
#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(push, ossPacking, 4)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack(1)
#elif defined(__BORLANDC__) && defined(__MSDOS__)
#ifdef _BC31
#pragma option -a-
#else
#pragma option -a1
#endif /* _BC31 */
#elif defined(__BORLANDC__) && defined(__WIN32__)
#pragma option -a4
#elif defined(__IBMC__)
#pragma pack(4)
#elif defined(__WATCOMC__) && defined(__NT__)
#pragma pack(push, 4)
#elif defined(__WATCOMC__) && (defined(__WINDOWS__) || defined(__DOS__))
#pragma pack(push, 1)
#endif /* _MSC_VER && _WIN32 */
#ifdef macintosh
#pragma options align=mac68k
#endif
typedef struct ossGlobal *_oss_qwJ;
typedef unsigned short Etag;
typedef struct efield *_oss_QQ;
typedef struct etype *_oss_q;
typedef struct _oss_jH *_oss_jwJ;
typedef struct eheader *_oss_QjJ;
struct etype {
	long	_oss_Hw;
	size_t	_oss_Q;
	size_t	_oss_QJ;
	char	*_oss_W;
	size_t	_oss_qQ;
	size_t	_oss_Jj;
	unsigned short int _oss_ww;
	unsigned short int _oss_JH;
	unsigned short int _oss_QwJ;
	unsigned short int _oss_WwJ;
	int	_oss_jw;
	unsigned short int _oss_w;
};
struct efield {
	size_t	_oss_qH;
	unsigned short int etype;
	short int	_oss_HwJ;
	unsigned short int _oss_Ww;
	unsigned char	_oss_Qj;
};
struct ConstraintEntry {
	char	_oss_JwJ;
	char	_oss_jQ;
	void	*_oss_j;
};
struct InnerSubtypeEntry {
	char	_oss_QH;
	unsigned char	_oss_H;
	unsigned short	efield;
	unsigned short	_oss_j;
};
struct eValRef {
	char	*_oss_W;
	void	*_oss_wwJ;
	unsigned short	etype;
};
struct eheader {
#if defined(__WATCOMC__) && defined(__DOS__)
	void (*_oss_J)(struct ossGlobal *);
#else
	void (DLL_ENTRY_FPTR *_System _oss_J)(struct ossGlobal *);
#endif /* __WATCOMC__ && __DOS__ */
	long	_oss_WH;
	unsigned short int _oss_JQ;
	unsigned short int _oss_H;
	unsigned short int _oss_HH,
	_oss_wQ;
	unsigned short *_oss_wH;
	_oss_q	_oss_Wj;
	_oss_QQ	_oss_jj;
	void	**_oss_wj;
	unsigned short *_oss_Q;
	struct ConstraintEntry *_oss_w;
	struct InnerSubtypeEntry *_oss_qw;
	void	*_oss_WQ;
	unsigned short int _oss_HQ;
	void	*_oss_Qw;
	unsigned short	_oss_Jw;
};
#if defined(_MSC_VER) && (defined(_WIN32) || defined(WIN32))
#pragma pack(pop, ossPacking)
#elif defined(_MSC_VER) && (defined(_WINDOWS) || defined(_MSDOS))
#pragma pack()
#elif defined(__BORLANDC__) && (defined(__WIN32__) || defined(__MSDOS__))
#pragma option -a.
#elif defined(__IBMC__)
#pragma pack()
#elif defined(__WATCOMC__)
#pragma pack(pop)
#endif /* _MSC_VER && _WIN32 */
#ifdef macintosh
#pragma options align=reset
#endif
