#ifndef		__VS_PLUGIN_GLOBAL_H__
#define		__VS_PLUGIN_GLOBAL_H__

#include "..\..\..\..\..\modules\bsafelite\include\integrate.h"

#define		VS_PLUGIN_ERASE_BSTR(bstr)	{\
	int nBstrLen = wcslen ( (const WCHAR*) bstr );\
	EraseMemory ( (unsigned int) (nBstrLen * 2), (PBYTE) bstr );\
}

#define	ALLOC_AND_WSTRING_COPY(dest, source)	{\
	dest = (WCHAR*) nsMemory::Clone((const void*) source, sizeof(WCHAR)*(wcslen(source) + 1) );\
}


#define VS_NO_ERROR 0
#define VS_INVALID_ARG 0x80000001
#define VS_GENERIC_ERROR 0x80000002
#define VS_PLUGIN_NOINST 0x80000003
#define VS_NOT_IMPL 0x80000004
#define VS_XENROLL_NOT_LOADED 0x80000005
#define VS_IMPORT_NOT_LOADED 0x80000006
#define VS_ADDROOTS_NOT_LOADED 0x80000007


#define	NPERR_GENERIC_ERROR	0x80008888

#endif