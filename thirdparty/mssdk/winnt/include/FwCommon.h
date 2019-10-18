//=================================================================
//
// FWcommon.h - declaration of Provider Framework common includes and defines
//
// Copyright 1997, 1998 Microsoft Corporation
//
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

// ALWAYS INCLUDE THIS FILE FIRST!

#ifndef _FW_COMMON_H_
#define _FW_COMMON_H_

// move warnings to level four
#pragma warning(4 : 4275 4800 4786 4251)
//	C4275: non DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
//	C4800: forcing bool variable to one or zero, possible performance loss
//	C4786: 'identifier' : identifier was truncated to 'number' characters in the debug information
//	C4251: 'identifier' : class 'type' needs to have dll-interface to export class 'type2'


//************************** WARNING ***************************************
// Microsoft STL collections protect themselves against multi-threaded
// access. We don't want that --- we protect ourselves. This protection
// involves an extra DLL (msvcp50.dll)
// So we trick it into believing that we are compiling single-threaded.
//**************************************************************************

// ALSO, IF WE DO NOT FORCE _CRTIMP TO A NOTHING VALUE, IT
// WILL BE DEFINED TO dlldeclspec(dllimport) WHICH CAUSES THE LINKER
// TO STILL WANT THE _LOCKIT CLASS CONSTRUCTOR AND DESTRUCTOR TO EXIST
// IN THE OUTSIDE WORLD

#ifdef _MT
	#undef _MT
 	#define _CRTIMP
	#include <yvals.h>
 	#undef _CRTIMP
	#define _MT
#endif

// some much used includes
#include <wbemidl.h>

// If USE_POLARITY not defined, some Framedyn.dll symbols may not resolve correctly
// It's a declspec(dllimport/dllexport) issue.
#ifndef USE_POLARITY
#pragma message( "FrameDyn.Dll Warning: USE_POLARITY not defined.  Linker may not be able to resolve all FrameDyn.Dll Symbols." )
#endif

#include <Polarity.h>
#include <AssertBreak.h>
#include <utillib.h>

#endif