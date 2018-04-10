///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_Platforms.h									 //
//																			 //
//	Description		:	The file contains the platform specific variable	 //
//						types.												 //
//																			 //
//	Date			:	Sept 13, 1999										 //
//																			 //
//	Author			:	Anand Abhyankar										 //
//																			 //
///////////////////////////////////////////////////////////////////////////////
#ifndef	__PROTECTED_STORAGE_PLATFORMS_H__
#define	__PROTECTED_STORAGE_PLATFORMS_H__

#if PLATFORM==VSPS_WIN32
	typedef		HRESULT			_VS_LONG;
	typedef		WCHAR			_VS_CHAR;
//	typedef		WCHAR			_VS_WCHAR;
	typedef		unsigned char	_VS_BYTE;
	typedef		unsigned int	_VS_DWORD;
	typedef		unsigned short	_VS_WORD;
	typedef		BOOL			_VS_BOOL;
#endif


	//	the strings functions
#if PLATFORM==VSPS_WIN32
#define			_VS_strlenW		::lstrlenW
//#define			_VS_strcpyW		::lstrcpyW
//#define			_VS_strcatW		::lstrcatW

//#define			_VS_memcpy		VS_memcpy
//#define			_VS_memcmp		VS_memcmp

#define			_VS_memcpy		memcpy
#define			_VS_memcmp		memcmp

#endif

#endif