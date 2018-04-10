#ifndef		__VS_CSP_INCLUDES__
#define		__VS_CSP_INCLUDES__

#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0400
#endif

#undef UNICODE					// ## Not Yet
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <wincrypt.h>
#include <winnt.h>

#include "VS_TSS.h"

//#include "..\stdafx.h"

#define		PROV_MATCH								1
#define		PROV_DOES_NOT_MATCH						0

#define		HASH_SHA1_LENGTH						20
#define		HASH_MD5_LENGTH							16
#define		HASH_MD2_LENGTH							16
#define		HASH_SSL3_SHAMD5						HASH_SHA1_LENGTH + 	HASH_MD5_LENGTH

#define		HASH_OBJECT_NOT_CREATED					0
#define		HASH_OBJECT_CREATED						1
#define		HASH_OBJECT_CLOSED						2
#define		HASH_SSL3_SHAMD5						HASH_SHA1_LENGTH + 	HASH_MD5_LENGTH

#endif