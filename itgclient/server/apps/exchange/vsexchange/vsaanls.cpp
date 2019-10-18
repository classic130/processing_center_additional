/* $Id: vsaanls.cpp,v 1.1.6.1 2003/06/06 22:46:27 npaul Exp $ */
/* $Revision: 1.1.6.1 $*/

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*--------------------------------------------------------------------\
 This file contains common utility functions for National Language 
 Support (NLS).

\--------------------------------------------------------------------*/

/* Standard header files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#ifndef WIN32
#include <unistd.h>
#include <errno.h>
#include <iconv.h>
#else
#include <windows.h>
#include <process.h>
#include <io.h>
#endif

/* Verisign AA support header files */

#include "vsaanls.h"
#include "vsverify.h"
#include "vsutil.h"
#include "vsaautil.h"

/* The following character encoding strings are used by ECAS. We need
   to map these into the encoding or code page identifiers that local
   OS supports.

Language ID	Character_encoding	Character_set	Description
----------------------------------------------------------------------
0			8859-1				iso8859-1		Latin-1(West European)
1.			8859-2				iso8859-2		Latin-2(East European)
2.			8859-3				iso8859-3		Latin-3(South European)
3.			8859-4				iso8859-4		Latin-4(North European)
4.			8859-5				iso8859-5		Cyrillic
5.			8859-6				iso8859-6		Arabic
6.			8859-7				iso8859-7		Greek
7.			8859-8				iso8859-8		Hebrew
8.			8859-9				iso8859-9		Latin-5(Turkish)
9.			8859-10				iso8859-10		Latin-6(Nordic)
10.			iso2022				iso2022			iso2022
11.			KOI8-R				KOI8-R			Korean (???)
12.			eucJP				euc-jp			Japanese EUC
13.			SJIS				Shift_JIS		Japanese Shift JIS
14.			gb2312				gb2312			Simplified Chinese
15.			zh_TW-big5			big5			Traditional Chinese
16.			zh_TW-euc			zh_tw			Traditional Chinese EUC
17.			zh_CN.euc			zh_cn			Simplified Chinese euc
18.			UCS-2				ISO-10646-UCS-2	Unicode (16 bits)
19.			UCS-4				ISO-10646-UCS-4	Unicode (32 bits)
20.			UTF-16				UTF-16			UTF-16
21.			UTF-7				UTF-7			UTF-7

*/

#ifdef WIN32

typedef struct _EncodingMapEntry {
    char *ECASEncoding;
    int  localEncoding;
	char *charset;
	char *description;
} EncodingMapEntry, *EncodingMapEntryPtr;

EncodingMapEntry ENCODING_MAP_TABLE[] = {
	{"UTF-8",   CP_UTF8, "UTF-8", "UTF-8"},
	{"8859-1",  28591, "iso8859-1", "Latin-1(West European)"},
	{"8859-2",  28592, "iso8859-2", "Latin-2(East European)"},
	{"8859-3",  28593, "iso8859-3", "Latin-3(South European)"},
	{"8859-4",  28594, "iso8859-4", "Latin-4(North European)"},
	{"8859-5",  28595, "iso8859-5", "Cyrillic"},
	{"8859-6",  28596, "iso8859-6", "Arabic"},
	{"8859-7",  28597, "iso8859-7", "Greek"},
	{"8859-8",  28598, "iso8859-8", "Hebrew"},
	{"8859-9",  28599, "iso8859-9", "Latin-5(Turkish)"},
	{"8859-10", 28600, "iso8859-10", "Latin-6(Nordic)"},
	{"iso2022",	50225, "iso2022",   "iso2022"},        // there are mapping of iso2002 to all CKJ. We assign it to Korea here. 
	{"KOI8-R",  20866, "KOI8-R",    "Russian"},    // 949 ANSI/OEM - Korean (Unified Hangeul Code); 20866 Russian - KOI8-R 
	{"eucJP",   51932, "euc-jp",    "Japanese EUC"},
	{"SJIS",    932,   "Shift_JIS", "Japanese Shift JIS"},
	{"gb2312",  936,   "gb2312",    "Simplified Chinese"},
	{"zh_TW-big5", 950,   "big5",  "Traditional Chinese"},
	{"zh_TW-euc",  51950, "zh_tw", "Traditional Chinese EUC"},
	{"zh_CN.euc",  51936, "zh_cn", "Simplified Chinese euc"},
	{"ko_KR-euc",  51949, "ko_KR", "Korean EUC"},

	// we choose little endian to match Java and common network assumption
	// 1200 Unicode UCS-2 Little-Endian (BMP of ISO 10646) 
	// 1201 Unicode UCS-2 Big-Endian  

	{"UCS-2", 1201, "ISO-10646-UCS-2", "Unicode (16 bits)"},

	// we choose little endian to match Java and common network assumption
	// 12000 Unicode UCS-4 Little-Endian 
	// 12001 Unicode UCS-4 Big-Endian 

	{"UCS-4",  12001,   "ISO-10646-UCS-4", "Unicode (32 bits)"},
	{"UTF-16", CP_ACP,  "UTF-16",          "UTF-16"}, // unknown
	{"UTF-7",  CP_UTF7, "UTF-7",           "UTF-7"},
	{NULL,     0,       NULL,              NULL}
};

#else

typedef struct _EncodingMapEntry {
    char *ECASEncoding;
    char *localEncoding;
	char *charset;
	char *description;
} EncodingMapEntry, *EncodingMapEntryPtr;

#ifdef HPUX

/* The following mapping are derived from /usr/lib/nls/iconv/config.iconv 
   in HPUX. For those encoding that HP doesn't support or there is no 
   information, we comment as "unknown to HP", and the target local encoding 
   is created as close as possible. 
*/

EncodingMapEntry ENCODING_MAP_TABLE[] = {
	{(char *)"UTF-8",   (char *)"utf8", (char *)"UTF-8", (char *)"UTF-8"},
	{(char *)"8859-1",  (char *)"iso81", (char *)"iso8859-1", (char *)"Latin-1(West European)"},
	{(char *)"8859-2",  (char *)"iso82", (char *)"iso8859-2", (char *)"Latin-2(East European)"},
	{(char *)"8859-3",  (char *)"iso83", (char *)"iso8859-3", (char *)"Latin-3(South European)"}, // unknown to HP
	{(char *)"8859-4",  (char *)"iso84", (char *)"iso8859-4", (char *)"Latin-4(North European)"}, // unknown to HP
	{(char *)"8859-5",  (char *)"iso85", (char *)"iso8859-5", (char *)"Cyrillic"},
	{(char *)"8859-6",  (char *)"iso86", (char *)"iso8859-6", (char *)"Arabic"},
	{(char *)"8859-7",  (char *)"iso87", (char *)"iso8859-7", (char *)"Greek"},
	{(char *)"8859-8",  (char *)"iso88", (char *)"iso8859-8", (char *)"Hebrew"},
	{(char *)"8859-9",  (char *)"iso89", (char *)"iso8859-9", (char *)"Latin-5(Turkish)"},
	{(char *)"8859-10", (char *)"iso810", (char *)"iso8859-10", (char *)"Latin-6(Nordic)"}, // unknown to HP
	{(char *)"iso2022",	(char *)"iso2022", (char *)"iso2022",   (char *)"iso2022"},         // unknown to HP
	{(char *)"KOI8-R",  (char *)"cp880",   (char *)"KOI8-R",    (char *)"Russian"},         // unknown to HP; we assign to Russian code page
	{(char *)"eucJP",   (char *)"eucJP",   (char *)"euc-jp",    (char *)"Japanese EUC"},
	{(char *)"SJIS",    (char *)"sjis",    (char *)"Shift_JIS", (char *)"Japanese Shift JIS"},
	{(char *)"gb2312",  (char *)"hp15CN",  (char *)"gb2312",    (char *)"Simplified Chinese"},
	{(char *)"zh_TW-big5", (char *)"big5", (char *)"big5",      (char *)"Traditional Chinese"},
	{(char *)"zh_TW-euc",  (char *)"eucTW", (char *)"zh_tw",     (char *)"Traditional Chinese EUC"},
	{(char *)"zh_CN.euc",  (char *)"eucCN", (char *)"zh_cn",     (char *)"Simplified Chinese euc"}, // unknow to HP
	{(char *)"ko_KR-euc",  (char *)"eucKR", (char *)"ko_KR",     (char *)"Korean EUC"},
	{(char *)"UCS-2",      (char *)"ucs2",  (char *)"ISO-10646-UCS-2", (char *)"Unicode (16 bits)"},
	{(char *)"UCS-4",      (char *)"ucs4",  (char *)"ISO-10646-UCS-4", (char *)"Unicode (32 bits)"},

	{(char *)"UTF-16", (char *)"utf16",  (char *)"UTF-16",         (char *)"UTF-16"},   // unknown to HP
	{(char *)"UTF-7",  (char *)"utf7",   (char *)"UTF-7",          (char *)"UTF-7"},   // unknown to HP
	{NULL,     0,       NULL,              NULL}
};

#elif defined(AIX)

/* The following mapping are derived from AIX UTF-8 Interexchange
   converter supported lists. For those encoding that AIX doesn't support 
   or there is no  information, we comment as "unknown to AIX", and the 
   target local encoding is created as close as possible. 
*/

EncodingMapEntry ENCODING_MAP_TABLE[] = {
	{"UTF-8",   "UTF-8", "UTF-8", "UTF-8"},
	{"8859-1",  "ISO8859-1", "iso8859-1", "Latin-1(West European)"},
	{"8859-2",  "ISO8859-2", "iso8859-2", "Latin-2(East European)"},
	{"8859-3",  "ISO8859-3", "iso8859-3", "Latin-3(South European)"}, 
	{"8859-4",  "ISO8859-4", "iso8859-4", "Latin-4(North European)"}, 
	{"8859-5",  "ISO8859-5", "iso8859-5", "Cyrillic"},
	{"8859-6",  "ISO8859-6", "iso8859-6", "Arabic"},
	{"8859-7",  "ISO8859-7", "iso8859-7", "Greek"},
	{"8859-8",  "ISO8859-8", "iso8859-8", "Hebrew"},
	{"8859-9",  "ISO8859-9", "iso8859-9", "Latin-5(Turkish)"},
	{"8859-10", "ISO8859-10", "iso8859-10", "Latin-6(Nordic)"}, // unkonwn to AIX
	{"iso2022",	"ISO2022", "iso2022",   "iso2022"},             // unknown to AIX
	{"KOI8-R",  "IBM-866", "KOI8-R",    "Russian"},             // unknown to AIX for UTF-8 conversion
	{"eucJP",   "IBM-eucJP",   "euc-jp",   "Japanese EUC"},
	{"SJIS",    "IBM-932",    "Shift_JIS", "Japanese Shift JIS"},
	{"gb2312",  "IBM-936",    "gb2312",    "Simplified Chinese"},
	{"zh_TW-big5", "big5",  "big5",        "Traditional Chinese"},
	{"zh_TW-euc",  "IBM-eucTW", "zh_tw",   "Traditional Chinese EUC"},
	{"zh_CN.euc",  "IBM-eucCN", "zh_cn",   "Simplified Chinese euc"}, 
	{"ko_KR-euc",  "eucKR",     "ko_KR",   "Korean EUC"},
	{"UCS-2",      "UCS-2",  "ISO-10646-UCS-2", "Unicode (16 bits)"},
	{"UCS-4",      "UCS-4",  "ISO-10646-UCS-4", "Unicode (32 bits)"},
	{"UTF-16",     "UTF-16", "UTF-16",          "UTF-16"},   // unknown to AIX
	{"UTF-7",      "UTF-7",  "UTF-7",           "UTF-7"},   // unknown to AIX
	{NULL,         0,        NULL,              NULL}
};

#endif

#endif

#ifdef WIN32

UINT GetCurrentOSSupportedEncodingName(const char* encoding)
{
	UINT CodePageId = CP_ACP;

	int i = 0;
	do {	
	    if(!VSAAUTIL_StrCaseCmp(ENCODING_MAP_TABLE[i].ECASEncoding, encoding)) {
			CodePageId = ENCODING_MAP_TABLE[i].localEncoding;
			break;
		}
		i ++;
	} while (ENCODING_MAP_TABLE[i].ECASEncoding != NULL);
		
	return CodePageId;
}

#else // UNIX

const char* GetCurrentOSSupportedEncodingName(const char* encoding)
{
	const char* encodingAlias = encoding;

#if defined(HPUX) || defined(AIX)
	int i = 0;
	do {	
	    if(!VSAAUTIL_StrCaseCmp(ENCODING_MAP_TABLE[i].ECASEncoding, encoding)) {
			encodingAlias = ENCODING_MAP_TABLE[i].localEncoding;
			break;
		}
		i ++;
	} while (ENCODING_MAP_TABLE[i].ECASEncoding != NULL);
#endif
	
	return encodingAlias;
}

#endif

int NativeToUTF8(char** utfStr, const char* nativeStr, const char* nativeCode)
{
    return CodeConvert(utfStr, UTF8_CODE, nativeStr, nativeCode);
}

int UTF8ToNative(char** nativeStr, const char* utfStr, const char* nativeCode)
{
    return CodeConvert(nativeStr, nativeCode, utfStr, UTF8_CODE);
}

/* This routine handles code set conversion from one code set to another.
   The common use is UTF-8 conversion to other code set. 
   
   It is not always true that any two code sets can convert to each other. 
   Only those related can be converted, such as big5 to GB which describes 
   the same language. In Unix, the all allowed conversion are given in 
   /usr/lib/nls/iconv. Each directory represents one conversion. If a 
   conversion from A to B (A_B) can not be found in the directory, it will
   try to find under /usr/lib/nls/loc/iconvTable. If such a conversion method
   cannot be found in either place, the conversion is not supported in the
   platform.
*/
int CodeConvert(char** toStr, const char * toCode, const char* fromStr, const char* fromCode)
{
    int rc = 0;

    if(fromStr == NULL || toStr == NULL || fromCode == NULL || toCode == NULL) return (-1);
    *toStr = NULL;

    /* handle utf-8 to utf-8 converstion */
    if ( !strcmp(toCode, fromCode) && !strcmp(toCode, UTF8_CODE) ) {
      *toStr = (char *)malloc(strlen(fromStr) + 1);
      if (*toStr == NULL) 
        rc = errno;
      strcpy(*toStr, fromStr);
      return rc;
    }

#ifndef WIN32
    char *convBuffer = NULL;

    const char *fromLocalCode = GetCurrentOSSupportedEncodingName(fromCode);
    const char *toLocalCode = GetCurrentOSSupportedEncodingName(toCode);
    VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char *)"Source data encoding [%s] becomes [%s]; target encoding [%s] becomes [%s]", fromCode, fromLocalCode, toCode, toLocalCode);

    iconv_t conversionDiscriptor = iconv_open(toLocalCode, fromLocalCode);

    do {
        if (conversionDiscriptor == (iconv_t) -1) {
            rc = errno;
            if(rc == 0) rc = 1; 
            VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char*)"Failed to open data encoding conversion descriptor from %s to %s, error (%d)", fromLocalCode, toLocalCode, rc);
            break;
        }
    
        size_t inputLen = strlen(fromStr);
        int convSize = inputLen * 3 + 1;
        convBuffer = (char *)malloc(convSize);
        if (convBuffer == NULL) {
            rc = errno;
            break;
        }
    
        memset(convBuffer, 0, convSize);
        char *outPtr = convBuffer;
        size_t outLen = convSize;
   
        /* If iconv() encounters a character in the input
           buffer that is legal but for which an identical
           character does not exist in the target codeset,
           iconv() maps this character to a pre-defined
           character, called the "galley character" that is
           defined at the time of table generation. 

           iconv() updates the variables pointed to by the
           arguments to reflect the extent of conversion, and
           returns the number of non-identical conversions performed.  
           If the entire string in the input buffer is converted, 
           the value pointed to by inbytesleft is zero.  If an error 
           occurs, iconv() returns (size_t)-1 and sets errno to
           indicate the error.
         */

        int ic = 0; // the number of non-identical conversions performed

#ifndef HPUX
        if ((ic = iconv(conversionDiscriptor, &fromStr, &inputLen, &outPtr, &outLen )) != 0) {
#else
        if ((ic = iconv(conversionDiscriptor, (char **)&fromStr, &inputLen, &outPtr, &outLen)) != 0) {
#endif
          if(ic != -1 && inputLen == 0) {
              VSAA_Log(VS_LOG_ALERT, __LINE__, __FILE__, (char*)"Some non-identical conversions performed from %s to %s, count =%d", fromLocalCode, toLocalCode, ic);
          } else {
              rc = errno?errno:EINVAL;
              VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char*)"Failed to convert data encoding from %s to %s, error (%x), errno=%d, input bytes left=%d", fromLocalCode, toLocalCode, rc, errno, inputLen);
              break;
          }
        }

        outPtr = convBuffer;
        *toStr = outPtr;
    } while (0);

    if(conversionDiscriptor >= 0) iconv_close(conversionDiscriptor);
    if(rc != 0) {
        if(convBuffer != NULL) free(convBuffer);
    }

#else

	LPWSTR lpFromWideCharStr = NULL;
	LPSTR lpToMultiByteStr = NULL;

	do {
		UINT fromCodePage = GetCurrentOSSupportedEncodingName(fromCode);
		VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char *)"Source data encoding code page: %d", fromCodePage);

		int wOutLen = strlen(fromStr) * 3;
		lpFromWideCharStr = (LPWSTR)malloc(wOutLen*sizeof(WCHAR));
		if(lpFromWideCharStr == NULL) {
			rc = VSAA_OUT_OF_MEMORY; break;
		}

		int bytes = MultiByteToWideChar(
			fromCodePage,         // code page
			0,                    // character-type options
			(LPCSTR)fromStr,      // string to map
			-1,                   // number of bytes in string; -1 means that input is nul terminated string
			lpFromWideCharStr,    // wide-character buffer
			wOutLen               // size of buffer
			);

		if(bytes == 0) {
			rc = VSAA_INTERNAL_ERROR;			
			break;
		} 

		UINT toCodePage = GetCurrentOSSupportedEncodingName(toCode);
		VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char *)"Target encoding code page: %d", toCodePage);

		int outLen = strlen(fromStr) * 3;
		LPSTR lpToMultiByteStr = (LPSTR)malloc(outLen);
		if(lpToMultiByteStr == NULL) {
			rc = VSAA_OUT_OF_MEMORY; break;
		}
		bytes = WideCharToMultiByte(
			toCodePage,        // code page
			0,                 // performance and mapping flags
			(LPCWSTR)lpFromWideCharStr,   // wide-character string
			bytes,             // number of chars in string
			lpToMultiByteStr,  // buffer for new string
			outLen,            // size of buffer
			NULL,              // default for unmappable chars
			NULL               // set when default char used
			);

		if(bytes == 0) {
			rc = VSAA_INTERNAL_ERROR;
			break;
		} 
		
		*toStr = lpToMultiByteStr;		
	} while (0);

	if(rc != 0 && rc != VSAA_OUT_OF_MEMORY) {
		if(lpFromWideCharStr != NULL) free(lpFromWideCharStr);
		if(lpToMultiByteStr != NULL) free(lpToMultiByteStr);

		rc = VSAA_INTERNAL_ERROR;
		DWORD err = GetLastError();
		switch (err) {
		case ERROR_INSUFFICIENT_BUFFER:
			VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char *)"Data encoding conversion: Insufficient output buffer");			 
			break;
		case ERROR_INVALID_FLAGS:
			VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char *)"Data encoding conversion: Invalid conversion flag");
			break;		
		case ERROR_INVALID_PARAMETER:
			VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char *)"Data encoding conversion: Invalid data or code page input");
			break;		
		case ERROR_NO_UNICODE_TRANSLATION:
			VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char *)"The given encoding conversion to UTF-8 is not supported.");
			break;		
		default:
			VSAA_Log(VS_LOG_ERROR, __LINE__, __FILE__, (char *)"Data encoding conversion: unknown.");
			break;		
		}
	}
	
#endif

   return rc;
}
