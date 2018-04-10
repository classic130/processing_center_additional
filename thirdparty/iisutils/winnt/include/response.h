/********************************************************************************
* Name:			response.h
* Description:  A response modelled as a linked list.
* DLL Location:	c:\winnt\system32\iisutils\response.h
*********************************************************************************/

#ifndef _RESPONSE
#define _RESPONSE

#define WIN32_LEAN_AN_MEAN
#include <windows.h>
#include <httpfilt.h>

#include "iisutils.h"
#include "debug.h"
#include "mem.h"

/********************************************************************************/

typedef struct _RESPINFO {
					LPSTR		lpszResponse;
					DWORD		cbRespSize;
					struct		_RESPINFO *pBack;
					struct		_RESPINFO *pForward;
					} RESPINFO, *PRESPINFO;

typedef struct _RESPONSE {
					DWORD		cbTotalRespSize;
					PRESPINFO	pRespListHead;
					}  RESPONSE, *PRESPONSE;

/********************************************************************************/
extern PRESPONSE Response_New(VOID);
extern VOID Response_Cleanup(PRESPONSE pResponse);
extern PRESPINFO Response_Append(PRESPONSE pResponse, LPSTR lpsResp, DWORD cbSize);
extern PRESPINFO Response_Prepend(PRESPONSE pResponse, LPSTR lpsResp, DWORD cbSize);
extern BOOL Response_Write(PHTTP_FILTER_CONTEXT pFC, PRESPONSE pResp);
extern BOOL Response_Dump(PRESPONSE pResp);
extern PRESPINFO Response_InitEntry(PRESPONSE pResp, PRESPINFO pEntry, LPSTR lpsResp, DWORD cbRespSize);
extern LPSTR Response_Compact(PHTTP_FILTER_CONTEXT pFC, PRESPONSE pResp);

#endif