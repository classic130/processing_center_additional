/*++

Copyright (C) 1995-1998 Microsoft Corporation

Module Name:

    loadperf.h

Abstract:

    Header file for the Performance Monitor counter string installation
    and removal functions.

Revision History

    16-Nov-95   Created (a-robw)

--*/

#ifndef _LOADPERF_H_
#define _LOADPERF_H_

// function prototypes for perf counter name string load & unload functions
// provided in LOADPERF.DLL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LOADPERF__
#define LOADPERF_FUNCTION   LONG __stdcall
#else
#define LOADPERF_FUNCTION   __declspec(dllimport) LONG __stdcall
#endif

LOADPERF_FUNCTION
LoadPerfCounterTextStringsA (
    IN  LPSTR   lpCommandLine,
    IN  BOOL    bQuietModeArg
);

LOADPERF_FUNCTION
LoadPerfCounterTextStringsW (
    IN  LPWSTR  lpCommandLine,
    IN  BOOL    bQuietModeArg
);

LOADPERF_FUNCTION
UnloadPerfCounterTextStringsW (
    IN  LPWSTR  lpCommandLine,
    IN  BOOL    bQuietModeArg
);

LOADPERF_FUNCTION
UnloadPerfCounterTextStringsA (
    IN  LPSTR   lpCommandLine,
    IN  BOOL    bQuietModeArg
);

#ifdef UNICODE
#define LoadPerfCounterTextStrings      LoadPerfCounterTextStringsW
#define UnloadPerfCounterTextStrings    UnloadPerfCounterTextStringsW
#else
#define LoadPerfCounterTextStrings      LoadPerfCounterTextStringsA
#define UnloadPerfCounterTextStrings    UnloadPerfCounterTextStringsA
#endif


#ifdef __cplusplus
}
#endif


#endif // _LOADPERF_H_
