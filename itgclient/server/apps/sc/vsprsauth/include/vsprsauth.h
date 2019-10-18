#ifndef _VS_PRSAUTH_DEFINES_
#define _VS_PRSAUTH_DEFINES_

#include <windows.h>
#include <comdef.h>


/****** UI Messages ***/
#define OPEN_PROF_DOES_NOT_EXIST 0x00000103
#define OPEN_PROF_CREATE 0x00000104
#define CREATE_PROF_DELETE 0x00000202
#define CREATE_PROF_OPEN 0x00000203
#define CREATE_PROF_EXISTS 0x00000204

/******** Generic return codes ***/
#define VS_OK		1
#define VS_ERROR	0

/******** HRESULTS *******/
#define E_USERCANCELLED 0x80001067
#define E_INVALIDPASSWD 0x80002000
#define E_PROFLOCKEDOUT 0x8000108E

#endif