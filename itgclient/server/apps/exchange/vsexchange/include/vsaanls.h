
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSAANLS_H_
#define _VSAANLS_H_

/* header files */

#ifdef __cplusplus
extern "C" {
#endif

#define UTF8_CODE                 "UTF-8"

/* Non-ASCII data conversion functions */
int CodeConvert(char** toStr, const char * toCode, const char* fromStr, const char* fromCode);
int NativeToUTF8(char** utfStr, const char* nativeStr, const char* nativeCodePage);
int UTF8ToNative(char** nativeStr, const char* utfStr, const char* nativeCodePage);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _VSAANLS_H */
