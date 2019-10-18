//
// Polarity.h -- properly map __declspec( dllexport ) or import
//
// Copyright 1998 Microsoft Corporation
//
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

// If we are building a the  DLL then define the 
// class as exporteded otherwise its imported
// ============================================
#ifndef POLARITY_HEADERFILE_IS_INCLUDED
#define POLARITY_HEADERFILE_IS_INCLUDED
#pragma message( "Including Polarity.h..." )

#ifdef USE_POLARITY
  #ifdef BUILDING_DLL
   #pragma message( "Building static library or DLL..." )
   #define POLARITY __declspec( dllexport )
  #else 
   #pragma message( "Building Provider..." )
   #define POLARITY __declspec( dllimport )
  #endif
 #else
  #define POLARITY
  #pragma message( "NO Polarity...")
 #endif
#endif
