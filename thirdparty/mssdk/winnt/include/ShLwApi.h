
/*****************************************************************************\
*                                                                             *
* shlwapi.h - Interface for the Windows light-weight utility APIs             *
*                                                                             *
* Version 1.0                                                                 *
*                                                                             *
* Copyright (c) 1991-1998, Microsoft Corp.      All rights reserved.          *
*                                                                             *
\*****************************************************************************/


#ifndef _INC_SHLWAPI
#define _INC_SHLWAPI

#ifndef NOSHLWAPI

#include <objbase.h>

#ifdef UNIX
typedef interface IInternetSecurityMgrSite IInternetSecurityMgrSite;
typedef interface IInternetSecurityManager IInternetSecurityManager;
typedef interface IInternetHostSecurityManager IInternetHostSecurityManager;
#endif

//
// Define API decoration for direct importing of DLL references.
//
#ifndef WINSHLWAPI
#if !defined(_SHLWAPI_)
#define LWSTDAPI          EXTERN_C DECLSPEC_IMPORT HRESULT STDAPICALLTYPE
#define LWSTDAPI_(type)   EXTERN_C DECLSPEC_IMPORT type STDAPICALLTYPE
#define LWSTDAPIV         EXTERN_C DECLSPEC_IMPORT HRESULT STDAPIVCALLTYPE
#define LWSTDAPIV_(type)  EXTERN_C DECLSPEC_IMPORT type STDAPIVCALLTYPE
#else
#define LWSTDAPI          STDAPI
#define LWSTDAPI_(type)   STDAPI_(type)
#define LWSTDAPIV         STDAPIV
#define LWSTDAPIV_(type)  STDAPIV_(type)
#endif
#endif // WINSHLWAPI

#ifdef _WIN32
#include <pshpack1.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Users of this header may define any number of these constants to avoid
// the definitions of each functional group.
//
//    NO_SHLWAPI_STRFCNS    String functions
//    NO_SHLWAPI_PATH       Path functions
//    NO_SHLWAPI_REG        Registry functions
//    NO_SHLWAPI_STREAM     Stream functions
//    NO_SHLWAPI_GDI        GDI helper functions

#ifndef NO_SHLWAPI_STRFCNS
//
//=============== String Routines ===================================
//

LWSTDAPI_(LPSTR)    StrChrA(LPCSTR lpStart, WORD wMatch);
LWSTDAPI_(LPWSTR)   StrChrW(LPCWSTR lpStart, WCHAR wMatch);
LWSTDAPI_(LPSTR)    StrChrIA(LPCSTR lpStart, WORD wMatch);
LWSTDAPI_(LPWSTR)   StrChrIW(LPCWSTR lpStart, WCHAR wMatch);
LWSTDAPI_(int)      StrCmpNA(LPCSTR lpStr1, LPCSTR lpStr2, int nChar);
LWSTDAPI_(int)      StrCmpNW(LPCWSTR lpStr1, LPCWSTR lpStr2, int nChar);
LWSTDAPI_(int)      StrCmpNIA(LPCSTR lpStr1, LPCSTR lpStr2, int nChar);
LWSTDAPI_(int)      StrCmpNIW(LPCWSTR lpStr1, LPCWSTR lpStr2, int nChar);
LWSTDAPI_(int)      StrCSpnA(LPCSTR lpStr, LPCSTR lpSet);
LWSTDAPI_(int)      StrCSpnW(LPCWSTR lpStr, LPCWSTR lpSet);
LWSTDAPI_(int)      StrCSpnIA(LPCSTR lpStr, LPCSTR lpSet);
LWSTDAPI_(int)      StrCSpnIW(LPCWSTR lpStr, LPCWSTR lpSet);
LWSTDAPI_(LPSTR)    StrDupA(LPCSTR lpSrch);
LWSTDAPI_(LPWSTR)   StrDupW(LPCWSTR lpSrch);
LWSTDAPI_(LPSTR)    StrFormatByteSizeA(DWORD dw, LPSTR szBuf, UINT uiBufSize);
LWSTDAPI_(LPWSTR)   StrFormatByteSizeW(LONGLONG qdw, LPWSTR szBuf, UINT uiBufSize);
LWSTDAPI_(int)      StrFromTimeIntervalA(LPSTR pszOut, UINT cchMax, DWORD dwTimeMS, int digits);
LWSTDAPI_(int)      StrFromTimeIntervalW(LPWSTR pszOut, UINT cchMax, DWORD dwTimeMS, int digits);
LWSTDAPI_(BOOL)     StrIsIntlEqualA(BOOL fCaseSens, LPCSTR lpString1, LPCSTR lpString2, int nChar);
LWSTDAPI_(BOOL)     StrIsIntlEqualW(BOOL fCaseSens, LPCWSTR lpString1, LPCWSTR lpString2, int nChar);
LWSTDAPI_(LPSTR)    StrNCatA(LPSTR psz1, LPCSTR psz2, int cchMax);
LWSTDAPI_(LPWSTR)   StrNCatW(LPWSTR psz1, LPCWSTR psz2, int cchMax);
LWSTDAPI_(LPSTR)    StrPBrkA(LPCSTR psz, LPCSTR pszSet);
LWSTDAPI_(LPWSTR)   StrPBrkW(LPCWSTR psz, LPCWSTR pszSet);
LWSTDAPI_(LPSTR)    StrRChrA(LPCSTR lpStart, LPCSTR lpEnd, WORD wMatch);
LWSTDAPI_(LPWSTR)   StrRChrW(LPCWSTR lpStart, LPCWSTR lpEnd, WCHAR wMatch);
LWSTDAPI_(LPSTR)    StrRChrIA(LPCSTR lpStart, LPCSTR lpEnd, WORD wMatch);
LWSTDAPI_(LPWSTR)   StrRChrIW(LPCWSTR lpStart, LPCWSTR lpEnd, WCHAR wMatch);
LWSTDAPI_(LPSTR)    StrRStrIA(LPCSTR lpSource, LPCSTR lpLast, LPCSTR lpSrch);
LWSTDAPI_(LPWSTR)   StrRStrIW(LPCWSTR lpSource, LPCWSTR lpLast, LPCWSTR lpSrch);
LWSTDAPI_(int)      StrSpnA(LPCSTR psz, LPCSTR pszSet);
LWSTDAPI_(int)      StrSpnW(LPCWSTR psz, LPCWSTR pszSet);
LWSTDAPI_(LPSTR)    StrStrA(LPCSTR lpFirst, LPCSTR lpSrch);
LWSTDAPI_(LPWSTR)   StrStrW(LPCWSTR lpFirst, LPCWSTR lpSrch);
LWSTDAPI_(LPSTR)    StrStrIA(LPCSTR lpFirst, LPCSTR lpSrch);
LWSTDAPI_(LPWSTR)   StrStrIW(LPCWSTR lpFirst, LPCWSTR lpSrch);
LWSTDAPI_(int)      StrToIntA(LPCSTR lpSrc);
LWSTDAPI_(int)      StrToIntW(LPCWSTR lpSrc);
LWSTDAPI_(BOOL)     StrToIntExA(LPCSTR pszString, DWORD dwFlags, int FAR * piRet);
LWSTDAPI_(BOOL)     StrToIntExW(LPCWSTR pszString, DWORD dwFlags, int FAR * piRet);
LWSTDAPI_(BOOL)     StrTrimA(LPSTR psz, LPCSTR pszTrimChars);
LWSTDAPI_(BOOL)     StrTrimW(LPWSTR psz, LPCWSTR pszTrimChars);

LWSTDAPI_(LPWSTR)   StrCatW(LPWSTR psz1, LPCWSTR psz2);
LWSTDAPI_(int)      StrCmpW(LPCWSTR psz1, LPCWSTR psz2);
LWSTDAPI_(int)      StrCmpIW(LPCWSTR psz1, LPCWSTR psz2);
LWSTDAPI_(LPWSTR)   StrCpyW(LPWSTR psz1, LPCWSTR psz2);
LWSTDAPI_(LPWSTR)   StrCpyNW(LPWSTR psz1, LPCWSTR psz2, int cchMax);

LWSTDAPI_(LPWSTR)   StrCatBuffW(LPWSTR pszDest, LPCWSTR pszSrc, int cchDestBuffSize);
LWSTDAPI_(LPSTR)    StrCatBuffA(LPSTR pszDest, LPCSTR pszSrc, int cchDestBuffSize);

LWSTDAPI_(BOOL)     ChrCmpIA(WORD w1, WORD w2);
LWSTDAPI_(BOOL)     ChrCmpIW(WCHAR w1, WCHAR w2);

LWSTDAPI_(int)      wvnsprintfA(LPSTR lpOut, int cchLimitIn, LPCSTR lpFmt, va_list arglist);
LWSTDAPI_(int)      wvnsprintfW(LPWSTR lpOut, int cchLimitIn, LPCWSTR lpFmt, va_list arglist);
LWSTDAPIV_(int)     wnsprintfA(LPSTR lpOut, int cchLimitIn, LPCSTR lpFmt, ...);
LWSTDAPIV_(int)     wnsprintfW(LPWSTR lpOut, int cchLimitIn, LPCWSTR lpFmt, ...);

LWSTDAPI_(HINSTANCE) MLLoadLibraryA(LPCSTR lpLibFileName, HANDLE hFile, DWORD dwFlags, LPCSTR lpComponent, BOOL bCrossCodePage);
LWSTDAPI_(HINSTANCE) MLLoadLibraryW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags, LPCWSTR lpComponent, BOOL bCrossCodePage);
#ifdef UNICODE
#define MLLoadLibrary  MLLoadLibraryW
#else
#define MLLoadLibrary  MLLoadLibraryA
#endif // !UNICODE
LWSTDAPI_(LANGID) MLGetUILanguage(void);

#define StrIntlEqNA( s1, s2, nChar) StrIsIntlEqualA( TRUE, s1, s2, nChar)
#define StrIntlEqNW( s1, s2, nChar) StrIsIntlEqualW( TRUE, s1, s2, nChar)
#define StrIntlEqNIA(s1, s2, nChar) StrIsIntlEqualA(FALSE, s1, s2, nChar)
#define StrIntlEqNIW(s1, s2, nChar) StrIsIntlEqualW(FALSE, s1, s2, nChar)

LWSTDAPI StrRetToStrA(struct _STRRET *pstr, const UNALIGNED struct _ITEMIDLIST *pidl, LPSTR *ppsz);
LWSTDAPI StrRetToStrW(struct _STRRET *pstr, const UNALIGNED struct _ITEMIDLIST *pidl, LPWSTR *ppsz);
#ifdef UNICODE
#define StrRetToStr  StrRetToStrW
#else
#define StrRetToStr  StrRetToStrA
#endif // !UNICODE
LWSTDAPI StrRetToBufA(struct _STRRET *pstr, const UNALIGNED struct _ITEMIDLIST *pidl, LPSTR pszBuf, UINT cchBuf);
LWSTDAPI StrRetToBufW(struct _STRRET *pstr, const UNALIGNED struct _ITEMIDLIST *pidl, LPWSTR pszBuf, UINT cchBuf);
#ifdef UNICODE
#define StrRetToBuf  StrRetToBufW
#else
#define StrRetToBuf  StrRetToBufA
#endif // !UNICODE

// helper to duplicate a string using the task allocator

LWSTDAPI SHStrDupA(LPCSTR psz, WCHAR **ppwsz);
LWSTDAPI SHStrDupW(LPCWSTR psz, WCHAR **ppwsz);
#ifdef UNICODE
#define SHStrDup  SHStrDupW
#else
#define SHStrDup  SHStrDupA
#endif // !UNICODE



#ifdef UNICODE
#define StrChr                  StrChrW
#define StrRChr                 StrRChrW
#define StrChrI                 StrChrIW
#define StrRChrI                StrRChrIW
#define StrCmpN                 StrCmpNW
#define StrCmpNI                StrCmpNIW
#define StrStr                  StrStrW
#define StrStrI                 StrStrIW
#define StrDup                  StrDupW
#define StrRStrI                StrRStrIW
#define StrCSpn                 StrCSpnW
#define StrCSpnI                StrCSpnIW
#define StrSpn                  StrSpnW
#define StrToInt                StrToIntW
#define StrPBrk                 StrPBrkW
#define StrToIntEx              StrToIntExW
#define StrFromTimeInterval     StrFromTimeIntervalW
#define StrIntlEqN              StrIntlEqNW
#define StrIntlEqNI             StrIntlEqNIW
#define StrFormatByteSize       StrFormatByteSizeW
#define StrNCat                 StrNCatW
#define StrTrim                 StrTrimW
#define StrCatBuff              StrCatBuffW
#define ChrCmpI                 ChrCmpIW
#define wvnsprintf              wvnsprintfW
#define wnsprintf               wnsprintfW
#define MLLoadLibrary           MLLoadLibraryW


#else
#define StrChr                  StrChrA
#define StrRChr                 StrRChrA
#define StrChrI                 StrChrIA
#define StrRChrI                StrRChrIA
#define StrCmpN                 StrCmpNA
#define StrCmpNI                StrCmpNIA
#define StrStr                  StrStrA
#define StrStrI                 StrStrIA
#define StrDup                  StrDupA
#define StrRStrI                StrRStrIA
#define StrCSpn                 StrCSpnA
#define StrCSpnI                StrCSpnIA
#define StrSpn                  StrSpnA
#define StrToInt                StrToIntA
#define StrPBrk                 StrPBrkA
#define StrToIntEx              StrToIntExA
#define StrFromTimeInterval     StrFromTimeIntervalA
#define StrIntlEqN              StrIntlEqNA
#define StrIntlEqNI             StrIntlEqNIA
#define StrFormatByteSize       StrFormatByteSizeA
#define StrNCat                 StrNCatA
#define StrTrim                 StrTrimA
#define StrCatBuff              StrCatBuffA
#define ChrCmpI                 ChrCmpIA
#define wvnsprintf              wvnsprintfA
#define wnsprintf               wnsprintfA
#define MLLoadLibrary           MLLoadLibraryA
#endif


// Backward compatible to NT's non-standard naming (strictly
// for comctl32)
//
LWSTDAPI_(BOOL)     IntlStrEqWorkerA(BOOL fCaseSens, LPCSTR lpString1, LPCSTR lpString2, int nChar);
LWSTDAPI_(BOOL)     IntlStrEqWorkerW(BOOL fCaseSens, LPCWSTR lpString1, LPCWSTR lpString2, int nChar);

#define IntlStrEqNA( s1, s2, nChar) IntlStrEqWorkerA( TRUE, s1, s2, nChar)
#define IntlStrEqNW( s1, s2, nChar) IntlStrEqWorkerW( TRUE, s1, s2, nChar)
#define IntlStrEqNIA(s1, s2, nChar) IntlStrEqWorkerA(FALSE, s1, s2, nChar)
#define IntlStrEqNIW(s1, s2, nChar) IntlStrEqWorkerW(FALSE, s1, s2, nChar)

#ifdef UNICODE
#define IntlStrEqN              IntlStrEqNW
#define IntlStrEqNI             IntlStrEqNIW
#else
#define IntlStrEqN              IntlStrEqNA
#define IntlStrEqNI             IntlStrEqNIA
#endif

#define SZ_CONTENTTYPE_HTMLA       "text/html"
#define SZ_CONTENTTYPE_HTMLW       L"text/html"
#define SZ_CONTENTTYPE_CDFA        "application/x-cdf"
#define SZ_CONTENTTYPE_CDFW        L"application/x-cdf"

#ifdef UNICODE
#define SZ_CONTENTTYPE_HTML     SZ_CONTENTTYPE_HTMLW
#define SZ_CONTENTTYPE_CDF      SZ_CONTENTTYPE_CDFW
#else
#define SZ_CONTENTTYPE_HTML     SZ_CONTENTTYPE_HTMLA
#define SZ_CONTENTTYPE_CDF      SZ_CONTENTTYPE_CDFA
#endif

#define PathIsHTMLFileA(pszPath)     PathIsContentTypeA(pszPath, SZ_CONTENTTYPE_HTMLA)
#define PathIsHTMLFileW(pszPath)     PathIsContentTypeW(pszPath, SZ_CONTENTTYPE_HTMLW)

// Flags for StrToIntEx
#define STIF_DEFAULT        0x00000000L
#define STIF_SUPPORT_HEX    0x00000001L


#define StrCatA                 lstrcatA
#define StrCmpA                 lstrcmpA
#define StrCmpIA                lstrcmpiA
#define StrCpyA                 lstrcpyA
#define StrCpyNA                lstrcpynA


#define StrToLong               StrToInt
#define StrNCmp                 StrCmpN
#define StrNCmpI                StrCmpNI
#define StrNCpy                 StrCpyN
#define StrCatN                 StrNCat

#ifdef UNICODE
#define StrCat                  StrCatW
#define StrCmp                  StrCmpW
#define StrCmpI                 StrCmpIW
#define StrCpy                  StrCpyW
#define StrCpyN                 StrCpyNW
#define StrCatBuff              StrCatBuffW
#else
#define StrCat                  lstrcatA
#define StrCmp                  lstrcmpA
#define StrCmpI                 lstrcmpiA
#define StrCpy                  lstrcpyA
#define StrCpyN                 lstrcpynA
#define StrCatBuff              StrCatBuffA
#endif


#endif //  NO_SHLWAPI_STRFCNS


#ifndef NO_SHLWAPI_PATH

//
//=============== Path Routines ===================================
//

LWSTDAPI_(LPSTR)    PathAddBackslashA(LPSTR pszPath);
LWSTDAPI_(LPWSTR)   PathAddBackslashW(LPWSTR pszPath);
LWSTDAPI_(BOOL)     PathAddExtensionA(LPSTR pszPath, LPCSTR pszExt);
LWSTDAPI_(BOOL)     PathAddExtensionW(LPWSTR pszPath, LPCWSTR pszExt);
LWSTDAPI_(BOOL)     PathAppendA(LPSTR pszPath, LPCSTR pMore);
LWSTDAPI_(BOOL)     PathAppendW(LPWSTR pszPath, LPCWSTR pMore);
LWSTDAPI_(LPSTR)    PathBuildRootA(LPSTR szRoot, int iDrive);
LWSTDAPI_(LPWSTR)   PathBuildRootW(LPWSTR szRoot, int iDrive);
LWSTDAPI_(BOOL)     PathCanonicalizeA(LPSTR pszBuf, LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathCanonicalizeW(LPWSTR pszBuf, LPCWSTR pszPath);
LWSTDAPI_(LPSTR)    PathCombineA(LPSTR szDest, LPCSTR lpszDir, LPCSTR lpszFile);
LWSTDAPI_(LPWSTR)   PathCombineW(LPWSTR szDest, LPCWSTR lpszDir, LPCWSTR lpszFile);
LWSTDAPI_(BOOL)     PathCompactPathA(HDC hDC, LPSTR pszPath, UINT dx);
LWSTDAPI_(BOOL)     PathCompactPathW(HDC hDC, LPWSTR pszPath, UINT dx);
LWSTDAPI_(BOOL)     PathCompactPathExA(LPSTR pszOut, LPCSTR pszSrc, UINT cchMax, DWORD dwFlags);
LWSTDAPI_(BOOL)     PathCompactPathExW(LPWSTR pszOut, LPCWSTR pszSrc, UINT cchMax, DWORD dwFlags);
LWSTDAPI_(int)      PathCommonPrefixA(LPCSTR pszFile1, LPCSTR pszFile2, LPSTR achPath);
LWSTDAPI_(int)      PathCommonPrefixW(LPCWSTR pszFile1, LPCWSTR pszFile2, LPWSTR achPath);
LWSTDAPI_(BOOL)     PathFileExistsA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathFileExistsW(LPCWSTR pszPath);
LWSTDAPI_(LPSTR)    PathFindExtensionA(LPCSTR pszPath);
LWSTDAPI_(LPWSTR)   PathFindExtensionW(LPCWSTR pszPath);
LWSTDAPI_(LPSTR)    PathFindFileNameA(LPCSTR pszPath);
LWSTDAPI_(LPWSTR)   PathFindFileNameW(LPCWSTR pszPath);
LWSTDAPI_(LPSTR)    PathFindNextComponentA(LPCSTR pszPath);
LWSTDAPI_(LPWSTR)   PathFindNextComponentW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathFindOnPathA(LPSTR pszPath, LPCSTR * ppszOtherDirs);
LWSTDAPI_(BOOL)     PathFindOnPathW(LPWSTR pszPath, LPCWSTR * ppszOtherDirs);
LWSTDAPI_(LPSTR)    PathGetArgsA(LPCSTR pszPath);
LWSTDAPI_(LPWSTR)   PathGetArgsW(LPCWSTR pszPath);
LWSTDAPI_(LPCSTR)   PathFindSuffixArrayA(LPCSTR pszPath, const LPCSTR *apszSuffix, int iArraySize);
LWSTDAPI_(LPCWSTR)  PathFindSuffixArrayW(LPCWSTR pszPath, const LPCWSTR *apszSuffix, int iArraySize);
STDAPI_(BOOL)       PathIsLFNFileSpecW(LPCTSTR lpName);
STDAPI_(BOOL)       PathIsLFNFileSpecA(LPCTSTR lpName);

LWSTDAPI_(UINT)     PathGetCharTypeA(UCHAR ch);
LWSTDAPI_(UINT)     PathGetCharTypeW(WCHAR ch);

// Return flags for PathGetCharType
#define GCT_INVALID             0x0000
#define GCT_LFNCHAR             0x0001
#define GCT_SHORTCHAR           0x0002
#define GCT_WILD                0x0004
#define GCT_SEPARATOR           0x0008

LWSTDAPI_(int)      PathGetDriveNumberA(LPCSTR pszPath);
LWSTDAPI_(int)      PathGetDriveNumberW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsDirectoryA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsDirectoryW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsDirectoryEmptyA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsDirectoryEmptyW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsFileSpecA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsFileSpecW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsPrefixA(LPCSTR pszPrefix, LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsPrefixW(LPCWSTR pszPrefix, LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsRelativeA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsRelativeW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsRootA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsRootW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsSameRootA(LPCSTR pszPath1, LPCSTR pszPath2);
LWSTDAPI_(BOOL)     PathIsSameRootW(LPCWSTR pszPath1, LPCWSTR pszPath2);
LWSTDAPI_(BOOL)     PathIsUNCA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsUNCW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsUNCServerA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsUNCServerW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsUNCServerShareA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsUNCServerShareW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsContentTypeA(LPCSTR pszPath, LPCSTR pszContentType);
LWSTDAPI_(BOOL)     PathIsContentTypeW(LPCWSTR pszPath, LPCWSTR pszContentType);
LWSTDAPI_(BOOL)     PathIsURLA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathIsURLW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathMakePrettyA(LPSTR pszPath);
LWSTDAPI_(BOOL)     PathMakePrettyW(LPWSTR pszPath);
LWSTDAPI_(BOOL)     PathMatchSpecA(LPCSTR pszFile, LPCSTR pszSpec);
LWSTDAPI_(BOOL)     PathMatchSpecW(LPCWSTR pszFile, LPCWSTR pszSpec);
LWSTDAPI_(int)      PathParseIconLocationA(LPSTR pszIconFile);
LWSTDAPI_(int)      PathParseIconLocationW(LPWSTR pszIconFile);
LWSTDAPI_(void)     PathQuoteSpacesA(LPSTR lpsz);
LWSTDAPI_(void)     PathQuoteSpacesW(LPWSTR lpsz);
LWSTDAPI_(BOOL)     PathRelativePathToA(LPSTR pszPath, LPCSTR pszFrom, DWORD dwAttrFrom, LPCSTR pszTo, DWORD dwAttrTo);
LWSTDAPI_(BOOL)     PathRelativePathToW(LPWSTR pszPath, LPCWSTR pszFrom, DWORD dwAttrFrom, LPCWSTR pszTo, DWORD dwAttrTo);
LWSTDAPI_(void)     PathRemoveArgsA(LPSTR pszPath);
LWSTDAPI_(void)     PathRemoveArgsW(LPWSTR pszPath);
LWSTDAPI_(LPSTR)    PathRemoveBackslashA(LPSTR pszPath);
LWSTDAPI_(LPWSTR)   PathRemoveBackslashW(LPWSTR pszPath);
LWSTDAPI_(void)     PathRemoveBlanksA(LPSTR pszPath);
LWSTDAPI_(void)     PathRemoveBlanksW(LPWSTR pszPath);
LWSTDAPI_(void)     PathRemoveExtensionA(LPSTR pszPath);
LWSTDAPI_(void)     PathRemoveExtensionW(LPWSTR pszPath);
LWSTDAPI_(BOOL)     PathRemoveFileSpecA(LPSTR pszPath);
LWSTDAPI_(BOOL)     PathRemoveFileSpecW(LPWSTR pszPath);
LWSTDAPI_(BOOL)     PathRenameExtensionA(LPSTR pszPath, LPCSTR pszExt);
LWSTDAPI_(BOOL)     PathRenameExtensionW(LPWSTR pszPath, LPCWSTR pszExt);
LWSTDAPI_(BOOL)     PathSearchAndQualifyA(LPCSTR pszPath, LPSTR pszBuf, UINT cchBuf);
LWSTDAPI_(BOOL)     PathSearchAndQualifyW(LPCWSTR pszPath, LPWSTR pszBuf, UINT cchBuf);
LWSTDAPI_(void)     PathSetDlgItemPathA(HWND hDlg, int id, LPCSTR pszPath);
LWSTDAPI_(void)     PathSetDlgItemPathW(HWND hDlg, int id, LPCWSTR pszPath);
LWSTDAPI_(LPSTR)    PathSkipRootA(LPCSTR pszPath);
LWSTDAPI_(LPWSTR)   PathSkipRootW(LPCWSTR pszPath);
LWSTDAPI_(void)     PathStripPathA(LPSTR pszPath);
LWSTDAPI_(void)     PathStripPathW(LPWSTR pszPath);
LWSTDAPI_(BOOL)     PathStripToRootA(LPSTR pszPath);
LWSTDAPI_(BOOL)     PathStripToRootW(LPWSTR pszPath);
LWSTDAPI_(void)     PathUnquoteSpacesA(LPSTR lpsz);
LWSTDAPI_(void)     PathUnquoteSpacesW(LPWSTR lpsz);
LWSTDAPI_(BOOL)     PathMakeSystemFolderA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathMakeSystemFolderW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathUnmakeSystemFolderA(LPCSTR pszPath);
LWSTDAPI_(BOOL)     PathUnmakeSystemFolderW(LPCWSTR pszPath);
LWSTDAPI_(BOOL)     PathIsSystemFolderA(LPCSTR pszPath, DWORD dwAttrb);
LWSTDAPI_(BOOL)     PathIsSystemFolderW(LPCWSTR pszPath, DWORD dwAttrb);
LWSTDAPI_(void)     PathUndecorateA(LPSTR  pszPath);
LWSTDAPI_(void)     PathUndecorateW(LPWSTR pszPath);


#ifdef UNICODE
#define PathAddBackslash        PathAddBackslashW
#define PathAddExtension        PathAddExtensionW
#define PathAppend              PathAppendW
#define PathBuildRoot           PathBuildRootW
#define PathCanonicalize        PathCanonicalizeW
#define PathCombine             PathCombineW
#define PathCompactPath         PathCompactPathW
#define PathCompactPathEx       PathCompactPathExW
#define PathCommonPrefix        PathCommonPrefixW
#define PathFileExists          PathFileExistsW
#define PathFindExtension       PathFindExtensionW
#define PathFindFileName        PathFindFileNameW
#define PathFindNextComponent   PathFindNextComponentW
#define PathFindOnPath          PathFindOnPathW
#define PathGetArgs             PathGetArgsW
#define PathGetCharType         PathGetCharTypeW
#define PathGetDriveNumber      PathGetDriveNumberW
#define PathIsDirectory         PathIsDirectoryW
#define PathIsDirectoryEmpty    PathIsDirectoryEmptyW
#define PathIsFileSpec          PathIsFileSpecW
#define PathIsPrefix            PathIsPrefixW
#define PathIsRelative          PathIsRelativeW
#define PathIsRoot              PathIsRootW
#define PathIsSameRoot          PathIsSameRootW
#define PathIsUNC               PathIsUNCW
#define PathIsUNCServer         PathIsUNCServerW
#define PathIsUNCServerShare    PathIsUNCServerShareW
#define PathIsContentType       PathIsContentTypeW
#define PathIsHTMLFile          PathIsHTMLFileW
#define PathIsURL               PathIsURLW
#define PathMakePretty          PathMakePrettyW
#define PathMatchSpec           PathMatchSpecW
#define PathParseIconLocation   PathParseIconLocationW
#define PathQuoteSpaces         PathQuoteSpacesW
#define PathRelativePathTo      PathRelativePathToW
#define PathRemoveArgs          PathRemoveArgsW
#define PathRemoveBackslash     PathRemoveBackslashW
#define PathRemoveBlanks        PathRemoveBlanksW
#define PathRemoveExtension     PathRemoveExtensionW
#define PathRemoveFileSpec      PathRemoveFileSpecW
#define PathRenameExtension     PathRenameExtensionW
#define PathSearchAndQualify    PathSearchAndQualifyW
#define PathSetDlgItemPath      PathSetDlgItemPathW
#define PathSkipRoot            PathSkipRootW
#define PathStripPath           PathStripPathW
#define PathStripToRoot         PathStripToRootW
#define PathUnquoteSpaces       PathUnquoteSpacesW
#define PathMakeSystemFolder    PathMakeSystemFolderW
#define PathUnmakeSystemFolder  PathUnmakeSystemFolderW
#define PathIsSystemFolder      PathIsSystemFolderW
#define PathFindSuffixArray     PathFindSuffixArrayW
#define PathIsLFNFileSpec       PathIsLFNFileSpecW
#define PathUndecorate          PathUndecorateW
#else
#define PathAddBackslash        PathAddBackslashA
#define PathAddExtension        PathAddExtensionA
#define PathAppend              PathAppendA
#define PathBuildRoot           PathBuildRootA
#define PathCanonicalize        PathCanonicalizeA
#define PathCombine             PathCombineA
#define PathCompactPath         PathCompactPathA
#define PathCompactPathEx       PathCompactPathExA
#define PathCommonPrefix        PathCommonPrefixA
#define PathFileExists          PathFileExistsA
#define PathFindExtension       PathFindExtensionA
#define PathFindFileName        PathFindFileNameA
#define PathFindNextComponent   PathFindNextComponentA
#define PathFindOnPath          PathFindOnPathA
#define PathGetArgs             PathGetArgsA
#define PathGetCharType         PathGetCharTypeA
#define PathGetDriveNumber      PathGetDriveNumberA
#define PathIsDirectory         PathIsDirectoryA
#define PathIsDirectoryEmpty    PathIsDirectoryEmptyA
#define PathIsFileSpec          PathIsFileSpecA
#define PathIsPrefix            PathIsPrefixA
#define PathIsRelative          PathIsRelativeA
#define PathIsRoot              PathIsRootA
#define PathIsSameRoot          PathIsSameRootA
#define PathIsUNC               PathIsUNCA
#define PathIsUNCServer         PathIsUNCServerA
#define PathIsUNCServerShare    PathIsUNCServerShareA
#define PathIsContentType       PathIsContentTypeA
#define PathIsHTMLFile          PathIsHTMLFileA
#define PathIsURL               PathIsURLA
#define PathMakePretty          PathMakePrettyA
#define PathMatchSpec           PathMatchSpecA
#define PathParseIconLocation   PathParseIconLocationA
#define PathQuoteSpaces         PathQuoteSpacesA
#define PathRelativePathTo      PathRelativePathToA
#define PathRemoveArgs          PathRemoveArgsA
#define PathRemoveBackslash     PathRemoveBackslashA
#define PathRemoveBlanks        PathRemoveBlanksA
#define PathRemoveExtension     PathRemoveExtensionA
#define PathRemoveFileSpec      PathRemoveFileSpecA
#define PathRenameExtension     PathRenameExtensionA
#define PathSearchAndQualify    PathSearchAndQualifyA
#define PathSetDlgItemPath      PathSetDlgItemPathA
#define PathSkipRoot            PathSkipRootA
#define PathStripPath           PathStripPathA
#define PathStripToRoot         PathStripToRootA
#define PathUnquoteSpaces       PathUnquoteSpacesA
#define PathMakeSystemFolder    PathMakeSystemFolderA
#define PathUnmakeSystemFolder  PathUnmakeSystemFolderA
#define PathIsSystemFolder      PathIsSystemFolderA
#define PathFindSuffixArray     PathFindSuffixArrayA
#define PathIsLFNFileSpec       PathIsLFNFileSpecA
#define PathUndecorate          PathUndecorateA
#endif

typedef enum {
    URL_SCHEME_INVALID     = -1,
    URL_SCHEME_UNKNOWN     =  0,
    URL_SCHEME_FTP,
    URL_SCHEME_HTTP,
    URL_SCHEME_GOPHER,
    URL_SCHEME_MAILTO,
    URL_SCHEME_NEWS,
    URL_SCHEME_NNTP,
    URL_SCHEME_TELNET,
    URL_SCHEME_WAIS,
    URL_SCHEME_FILE,
    URL_SCHEME_MK,
    URL_SCHEME_HTTPS,
    URL_SCHEME_SHELL,
    URL_SCHEME_SNEWS,
    URL_SCHEME_LOCAL,
    URL_SCHEME_JAVASCRIPT,
    URL_SCHEME_VBSCRIPT,
    URL_SCHEME_ABOUT,
    URL_SCHEME_RES,
    URL_SCHEME_MAXVALUE
} URL_SCHEME;

typedef enum {
    URL_PART_NONE       = 0,
    URL_PART_SCHEME     = 1,
    URL_PART_HOSTNAME,
    URL_PART_USERNAME,
    URL_PART_PASSWORD,
    URL_PART_PORT
} URL_PART;

typedef enum {
    URLIS_URL,
    URLIS_OPAQUE,
    URLIS_NOHISTORY,
    URLIS_FILEURL,
    URLIS_APPLIABLE,
} URLIS;

#define URL_UNESCAPE                    0x10000000
#define URL_ESCAPE_UNSAFE               0x20000000
#define URL_WININET_COMPATIBILITY       0x80000000
#define URL_DONT_ESCAPE_EXTRA_INFO      0x02000000
#define URL_DONT_UNESCAPE_EXTRA_INFO    URL_DONT_ESCAPE_EXTRA_INFO
#define URL_BROWSER_MODE                URL_DONT_ESCAPE_EXTRA_INFO
#define URL_ESCAPE_SPACES_ONLY          0x04000000
#define URL_DONT_SIMPLIFY               0x08000000
#define URL_NO_META                     URL_DONT_SIMPLIFY
#define URL_UNESCAPE_INPLACE            0x00100000
#define URL_CONVERT_IF_DOSPATH          0x00200000
#define URL_UNESCAPE_HIGH_ANSI_ONLY     0x00400000
#define URL_INTERNAL_PATH               0x00800000  // Will escape #'s in paths
#define URL_FILE_USE_PATHURL            0x00010000

#define URL_PARTFLAG_KEEPSCHEME         0x00000001

#define URL_APPLY_DEFAULT               0x00000001
#define URL_APPLY_GUESSSCHEME           0x00000002
#define URL_APPLY_GUESSFILE             0x00000004
#define URL_APPLY_FORCEAPPLY            0x00000008


LWSTDAPI_(int)          UrlCompareA(LPCSTR psz1, LPCSTR psz2, BOOL fIgnoreSlash);
LWSTDAPI_(int)          UrlCompareW(LPCWSTR psz1, LPCWSTR psz2, BOOL fIgnoreSlash);
LWSTDAPI                UrlCombineA(LPCSTR pszBase, LPCSTR pszRelative, LPSTR pszCombined, LPDWORD pcchCombined, DWORD dwFlags);
LWSTDAPI                UrlCombineW(LPCWSTR pszBase, LPCWSTR pszRelative, LPWSTR pszCombined, LPDWORD pcchCombined, DWORD dwFlags);
LWSTDAPI                UrlCanonicalizeA(LPCSTR pszUrl, LPSTR pszCanonicalized, LPDWORD pcchCanonicalized, DWORD dwFlags);
LWSTDAPI                UrlCanonicalizeW(LPCWSTR pszUrl, LPWSTR pszCanonicalized, LPDWORD pcchCanonicalized, DWORD dwFlags);
LWSTDAPI_(BOOL)         UrlIsOpaqueA(LPCSTR pszURL);
LWSTDAPI_(BOOL)         UrlIsOpaqueW(LPCWSTR pszURL);
LWSTDAPI_(BOOL)         UrlIsNoHistoryA(LPCSTR pszURL);
LWSTDAPI_(BOOL)         UrlIsNoHistoryW(LPCWSTR pszURL);
#define                 UrlIsFileUrlA(pszURL) UrlIsA(pszURL, URLIS_FILEURL)
#define                 UrlIsFileUrlW(pszURL) UrlIsW(pszURL, URLIS_FILEURL)
LWSTDAPI_(BOOL)         UrlIsA(LPCSTR pszUrl, URLIS UrlIs);
LWSTDAPI_(BOOL)         UrlIsW(LPCWSTR pszUrl, URLIS UrlIs);
LWSTDAPI_(LPCSTR)       UrlGetLocationA(LPCSTR psz1);
LWSTDAPI_(LPCWSTR)      UrlGetLocationW(LPCWSTR psz1);
LWSTDAPI                UrlUnescapeA(LPSTR pszUrl, LPSTR pszUnescaped, LPDWORD pcchUnescaped, DWORD dwFlags);
LWSTDAPI                UrlUnescapeW(LPWSTR pszUrl, LPWSTR pszUnescaped, LPDWORD pcchUnescaped, DWORD dwFlags);
LWSTDAPI                UrlEscapeA(LPCSTR pszUrl, LPSTR pszEscaped, LPDWORD pcchEscaped, DWORD dwFlags);
LWSTDAPI                UrlEscapeW(LPCWSTR pszUrl, LPWSTR pszEscaped, LPDWORD pcchEscaped, DWORD dwFlags);
LWSTDAPI                UrlCreateFromPathA(LPCSTR pszPath, LPSTR pszUrl, LPDWORD pcchUrl, DWORD dwFlags);
LWSTDAPI                UrlCreateFromPathW(LPCWSTR pszPath, LPWSTR pszUrl, LPDWORD pcchUrl, DWORD dwFlags);
LWSTDAPI                PathCreateFromUrlA(LPCSTR pszUrl, LPSTR pszPath, LPDWORD pcchPath, DWORD dwFlags);
LWSTDAPI                PathCreateFromUrlW(LPCWSTR pszUrl, LPWSTR pszPath, LPDWORD pcchPath, DWORD dwFlags);
LWSTDAPI                UrlHashA(LPCSTR pszUrl, LPBYTE pbHash, DWORD cbHash);
LWSTDAPI                UrlHashW(LPCWSTR pszUrl, LPBYTE pbHash, DWORD cbHash);
LWSTDAPI                UrlGetPartW(LPCWSTR pszIn, LPWSTR pszOut, LPDWORD pcchOut, DWORD dwPart, DWORD dwFlags);
LWSTDAPI                UrlGetPartA(LPCSTR pszIn, LPSTR pszOut, LPDWORD pcchOut, DWORD dwPart, DWORD dwFlags);
LWSTDAPI                UrlApplySchemeA(LPCSTR pszIn, LPSTR pszOut, LPDWORD pcchOut, DWORD dwFlags);
LWSTDAPI                UrlApplySchemeW(LPCWSTR pszIn, LPWSTR pszOut, LPDWORD pcchOut, DWORD dwFlags);
LWSTDAPI                HashData(LPBYTE pbData, DWORD cbData, LPBYTE pbHash, DWORD cbHash);

#ifdef UNICODE
#define UrlCompare              UrlCompareW
#define UrlCombine              UrlCombineW
#define UrlCanonicalize         UrlCanonicalizeW
#define UrlIsOpaque             UrlIsOpaqueW
#define UrlIsFileUrl            UrlIsFileUrlW
#define UrlGetLocation          UrlGetLocationW
#define UrlUnescape             UrlUnescapeW
#define UrlEscape               UrlEscapeW
#define UrlCreateFromPath       UrlCreateFromPathW
#define PathCreateFromUrl       PathCreateFromUrlW
#define UrlHash                 UrlHashW
#define UrlGetPart              UrlGetPartW
#define UrlApplyScheme          UrlApplySchemeW
#define UrlIs                   UrlIsW
#else //!UNICODE
#define UrlCompare              UrlCompareA
#define UrlCombine              UrlCombineA
#define UrlCanonicalize         UrlCanonicalizeA
#define UrlIsOpaque             UrlIsOpaqueA
#define UrlIsFileUrl            UrlIsFileUrlA
#define UrlGetLocation          UrlGetLocationA
#define UrlUnescape             UrlUnescapeA
#define UrlEscape               UrlEscapeA
#define UrlCreateFromPath       UrlCreateFromPathA
#define PathCreateFromUrl       PathCreateFromUrlA
#define UrlHash                 UrlHashA
#define UrlGetPart              UrlGetPartA
#define UrlApplyScheme          UrlApplySchemeA
#define UrlIs                   UrlIsA
#endif //UNICODE

#define UrlEscapeSpaces(pszUrl, pszEscaped, pcchEscaped)        UrlCanonicalize(pszUrl, pszEscaped, pcchEscaped, URL_ESCAPE_SPACES_ONLY |URL_DONT_ESCAPE_EXTRA_INFO )
#define UrlUnescapeInPlace(pszUrl, dwFlags)                     UrlUnescape(pszUrl, NULL, NULL, dwFlags | URL_UNESCAPE_INPLACE)



#endif //  NO_SHLWAPI_PATH



#ifndef NO_SHLWAPI_REG
//
//=============== Registry Routines ===================================
//

// SHDeleteEmptyKey mimics RegDeleteKey as it behaves on NT.
// SHDeleteKey mimics RegDeleteKey as it behaves on Win95.

LWSTDAPI_(DWORD)    SHDeleteEmptyKeyA(HKEY hkey, LPCSTR pszSubKey);
LWSTDAPI_(DWORD)    SHDeleteEmptyKeyW(HKEY hkey, LPCWSTR pszSubKey);
LWSTDAPI_(DWORD)    SHDeleteKeyA(HKEY hkey, LPCSTR pszSubKey);
LWSTDAPI_(DWORD)    SHDeleteKeyW(HKEY hkey, LPCWSTR pszSubKey);


// These functions open the key, get/set/delete the value, then close
// the key.

LWSTDAPI_(DWORD)    SHDeleteValueA(HKEY hkey, LPCSTR pszSubKey, LPCSTR pszValue);
LWSTDAPI_(DWORD)    SHDeleteValueW(HKEY hkey, LPCWSTR pszSubKey, LPCWSTR pszValue);
LWSTDAPI_(DWORD)    SHGetValueA(HKEY hkey, LPCSTR pszSubKey, LPCSTR pszValue, LPDWORD pdwType, void *pvData, LPDWORD pcbData);
LWSTDAPI_(DWORD)    SHGetValueW(HKEY hkey, LPCWSTR pszSubKey, LPCWSTR pszValue, LPDWORD pdwType, void *pvData, LPDWORD pcbData);
LWSTDAPI_(DWORD)    SHSetValueA(HKEY hkey, LPCSTR pszSubKey, LPCSTR pszValue, DWORD dwType, LPCVOID pvData, DWORD cbData);
LWSTDAPI_(DWORD)    SHSetValueW(HKEY hkey, LPCWSTR pszSubKey, LPCWSTR pszValue, DWORD dwType, LPCVOID pvData, DWORD cbData);

// These functions work just like RegQueryValueEx, except if the
// data type is REG_EXPAND_SZ, then these will go ahead and expand
// out the string.  *pdwType will always be massaged to REG_SZ
// if this happens.  REG_SZ values are also guaranteed to be null
// terminated.

LWSTDAPI_(DWORD)    SHQueryValueExA(HKEY hkey, LPCSTR pszValue, LPDWORD pdwReserved, LPDWORD pdwType, void *pvData, LPDWORD pcbData);
LWSTDAPI_(DWORD)    SHQueryValueExW(HKEY hkey, LPCWSTR pszValue, LPDWORD pdwReserved, LPDWORD pdwType, void *pvData, LPDWORD pcbData);

// Enumeration functions support.

LWSTDAPI_(LONG)     SHEnumKeyExA(HKEY hkey, DWORD dwIndex, LPSTR pszName, LPDWORD pcchName);
LWSTDAPI_(LONG)     SHEnumKeyExW(HKEY hkey, DWORD dwIndex, LPWSTR pszName, LPDWORD pcchName);
LWSTDAPI_(LONG)     SHEnumValueA(HKEY hkey, DWORD dwIndex, LPSTR pszValueName, LPDWORD pcchValueName, LPDWORD pdwType, void *pvData, LPDWORD pcbData);
LWSTDAPI_(LONG)     SHEnumValueW(HKEY hkey, DWORD dwIndex, LPWSTR pszValueName, LPDWORD pcchValueName, LPDWORD pdwType, void *pvData, LPDWORD pcbData);
LWSTDAPI_(LONG)     SHQueryInfoKeyA(HKEY hkey, LPDWORD pcSubKeys, LPDWORD pcchMaxSubKeyLen, LPDWORD pcValues, LPDWORD pcchMaxValueNameLen);
LWSTDAPI_(LONG)     SHQueryInfoKeyW(HKEY hkey, LPDWORD pcSubKeys, LPDWORD pcchMaxSubKeyLen, LPDWORD pcValues, LPDWORD pcchMaxValueNameLen);

// recursive key copy
LWSTDAPI_(DWORD)     SHCopyKeyA(HKEY hkeySrc, LPCSTR   szSrcSubKey, HKEY hkeyDest, DWORD fReserved);
LWSTDAPI_(DWORD)     SHCopyKeyW(HKEY hkeySrc, LPCWSTR wszSrcSubKey, HKEY hkeyDest, DWORD fReserved);

#ifdef UNICODE
#define SHDeleteEmptyKey      SHDeleteEmptyKeyW
#define SHDeleteKey           SHDeleteKeyW
#define SHDeleteValue         SHDeleteValueW
#define SHGetValue            SHGetValueW
#define SHSetValue            SHSetValueW
#define SHQueryValueEx        SHQueryValueExW
#define SHEnumKeyEx           SHEnumKeyExW
#define SHEnumValue           SHEnumValueW
#define SHQueryInfoKey        SHQueryInfoKeyW
#define SHCopyKey             SHCopyKeyW
#else
#define SHDeleteEmptyKey      SHDeleteEmptyKeyA
#define SHDeleteKey           SHDeleteKeyA
#define SHDeleteValue         SHDeleteValueA
#define SHGetValue            SHGetValueA
#define SHSetValue            SHSetValueA
#define SHQueryValueEx        SHQueryValueExA
#define SHEnumKeyEx           SHEnumKeyExA
#define SHEnumValue           SHEnumValueA
#define SHQueryInfoKey        SHQueryInfoKeyA
#define SHCopyKey             SHCopyKeyA
#endif


//////////////////////////////////////////////
// User Specific Registry Access Functions
//////////////////////////////////////////////

//
// Type definitions.
//

typedef enum
{
    SHREGDEL_DEFAULT = 0x00000000,       // Delete's HKCU, or HKLM if HKCU is not found.
    SHREGDEL_HKCU    = 0x00000001,       // Delete HKCU only
    SHREGDEL_HKLM    = 0x00000010,       // Delete HKLM only.
    SHREGDEL_BOTH    = 0x00000011,       // Delete both HKCU and HKLM.
} SHREGDEL_FLAGS;

typedef enum
{
    SHREGENUM_DEFAULT = 0x00000000,       // Enumerates HKCU or HKLM if not found.
    SHREGENUM_HKCU    = 0x00000001,       // Enumerates HKCU only
    SHREGENUM_HKLM    = 0x00000010,       // Enumerates HKLM only.
    SHREGENUM_BOTH    = 0x00000011,       // Enumerates both HKCU and HKLM without duplicates.
                                          // This option is NYI.
} SHREGENUM_FLAGS;

#define     SHREGSET_HKCU           0x00000001       // Write to HKCU if empty.
#define     SHREGSET_FORCE_HKCU     0x00000002       // Write to HKCU.
#define     SHREGSET_HKLM           0x00000004       // Write to HKLM if empty.
#define     SHREGSET_FORCE_HKLM     0x00000008       // Write to HKLM.
#define     SHREGSET_DEFAULT        (SHREGSET_FORCE_HKCU | SHREGSET_HKLM)          // Default is SHREGSET_FORCE_HKCU | SHREGSET_HKLM.

typedef HANDLE HUSKEY;  // HUSKEY is a Handle to a User Specific KEY.
typedef HUSKEY *PHUSKEY;

LWSTDAPI_(LONG)        SHRegCreateUSKeyA(LPCSTR pszPath, REGSAM samDesired, HUSKEY hRelativeUSKey, PHUSKEY phNewUSKey, DWORD dwFlags);
LWSTDAPI_(LONG)        SHRegCreateUSKeyW(LPCWSTR pwzPath, REGSAM samDesired, HUSKEY hRelativeUSKey, PHUSKEY phNewUSKey, DWORD dwFlags);
LWSTDAPI_(LONG)        SHRegOpenUSKeyA(LPCSTR pszPath, REGSAM samDesired, HUSKEY hRelativeUSKey, PHUSKEY phNewUSKey, BOOL fIgnoreHKCU);
LWSTDAPI_(LONG)        SHRegOpenUSKeyW(LPCWSTR pwzPath, REGSAM samDesired, HUSKEY hRelativeUSKey, PHUSKEY phNewUSKey, BOOL fIgnoreHKCU);
LWSTDAPI_(LONG)        SHRegQueryUSValueA(HUSKEY hUSKey, LPCSTR pszValue, LPDWORD pdwType, void *pvData, LPDWORD pcbData, BOOL fIgnoreHKCU, void *pvDefaultData, DWORD dwDefaultDataSize);
LWSTDAPI_(LONG)        SHRegQueryUSValueW(HUSKEY hUSKey, LPCWSTR pwzValue, LPDWORD pdwType, void *pvData, LPDWORD pcbData, BOOL fIgnoreHKCU, void *pvDefaultData, DWORD dwDefaultDataSize);
LWSTDAPI_(LONG)        SHRegWriteUSValueA(HUSKEY hUSKey, LPCSTR pszValue, DWORD dwType, const void *pvData, DWORD cbData, DWORD dwFlags);
LWSTDAPI_(LONG)        SHRegWriteUSValueW(HUSKEY hUSKey, LPCWSTR pwzValue, DWORD dwType, const void *pvData, DWORD cbData, DWORD dwFlags);
LWSTDAPI_(LONG)        SHRegDeleteUSValueA(HUSKEY hUSKey, LPCSTR pszValue, SHREGDEL_FLAGS delRegFlags);
LWSTDAPI_(LONG)        SHRegDeleteEmptyUSKeyW(HUSKEY hUSKey, LPCWSTR pwzSubKey, SHREGDEL_FLAGS delRegFlags);
LWSTDAPI_(LONG)        SHRegDeleteEmptyUSKeyA(HUSKEY hUSKey, LPCSTR pszSubKey, SHREGDEL_FLAGS delRegFlags);
LWSTDAPI_(LONG)        SHRegDeleteUSValueW(HUSKEY hUSKey, LPCWSTR pwzValue, SHREGDEL_FLAGS delRegFlags);
LWSTDAPI_(LONG)        SHRegEnumUSKeyA(HUSKEY hUSKey, DWORD dwIndex, LPSTR pszName, LPDWORD pcchName, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegEnumUSKeyW(HUSKEY hUSKey, DWORD dwIndex, LPWSTR pwzName, LPDWORD pcchName, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegEnumUSValueA(HUSKEY hUSkey, DWORD dwIndex, LPSTR pszValueName, LPDWORD pcchValueName, LPDWORD pdwType, void *pvData, LPDWORD pcbData, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegEnumUSValueW(HUSKEY hUSkey, DWORD dwIndex, LPWSTR pszValueName, LPDWORD pcchValueName, LPDWORD pdwType, void *pvData, LPDWORD pcbData, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegQueryInfoUSKeyA(HUSKEY hUSKey, LPDWORD pcSubKeys, LPDWORD pcchMaxSubKeyLen, LPDWORD pcValues, LPDWORD pcchMaxValueNameLen, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegQueryInfoUSKeyW(HUSKEY hUSKey, LPDWORD pcSubKeys, LPDWORD pcchMaxSubKeyLen, LPDWORD pcValues, LPDWORD pcchMaxValueNameLen, SHREGENUM_FLAGS enumRegFlags);
LWSTDAPI_(LONG)        SHRegCloseUSKey(HUSKEY hUSKey);


// These calls are equal to an SHRegOpenUSKey, SHRegQueryUSValue, and then a SHRegCloseUSKey.
LWSTDAPI_(LONG)        SHRegGetUSValueA(LPCSTR pszSubKey, LPCSTR pszValue, LPDWORD pdwType, void * pvData, LPDWORD pcbData, BOOL fIgnoreHKCU, void *pvDefaultData, DWORD dwDefaultDataSize);
LWSTDAPI_(LONG)        SHRegGetUSValueW(LPCWSTR pwzSubKey, LPCWSTR pwzValue, LPDWORD pdwType, void * pvData, LPDWORD pcbData, BOOL fIgnoreHKCU, void *pvDefaultData, DWORD dwDefaultDataSize);
LWSTDAPI_(LONG)        SHRegSetUSValueA(LPCSTR pszSubKey, LPCSTR pszValue, DWORD dwType, const void *pvData, DWORD cbData, DWORD dwFlags);
LWSTDAPI_(LONG)        SHRegSetUSValueW(LPCWSTR pwzSubKey, LPCWSTR pwzValue, DWORD dwType, const void *pvData, DWORD cbData, DWORD dwFlags);
LWSTDAPI_(int)         SHRegGetIntW(HKEY hk, LPCWSTR pwzKey, int iDefault);

#ifdef UNICODE
#define SHRegCreateUSKey        SHRegCreateUSKeyW
#define SHRegOpenUSKey          SHRegOpenUSKeyW
#define SHRegQueryUSValue       SHRegQueryUSValueW
#define SHRegWriteUSValue       SHRegWriteUSValueW
#define SHRegDeleteUSValue      SHRegDeleteUSValueW
#define SHRegDeleteEmptyUSKey   SHRegDeleteEmptyUSKeyW
#define SHRegEnumUSKey          SHRegEnumUSKeyW
#define SHRegEnumUSValue        SHRegEnumUSValueW
#define SHRegQueryInfoUSKey     SHRegQueryInfoUSKeyW
#define SHRegGetUSValue         SHRegGetUSValueW
#define SHRegSetUSValue         SHRegSetUSValueW
#define SHRegGetInt             SHRegGetIntW
#else
#define SHRegCreateUSKey        SHRegCreateUSKeyA
#define SHRegOpenUSKey          SHRegOpenUSKeyA
#define SHRegQueryUSValue       SHRegQueryUSValueA
#define SHRegWriteUSValue       SHRegWriteUSValueA
#define SHRegDeleteUSValue      SHRegDeleteUSValueA
#define SHRegDeleteEmptyUSKey   SHRegDeleteEmptyUSKeyA
#define SHRegEnumUSKey          SHRegEnumUSKeyA
#define SHRegEnumUSValue        SHRegEnumUSValueA
#define SHRegQueryInfoUSKey     SHRegQueryInfoUSKeyA
#define SHRegGetUSValue         SHRegGetUSValueA
#define SHRegSetUSValue         SHRegSetUSValueA
#endif

LWSTDAPI_(BOOL) SHRegGetBoolUSValueA(LPCSTR pszSubKey, LPCSTR pszValue, BOOL fIgnoreHKCU, BOOL fDefault);
LWSTDAPI_(BOOL) SHRegGetBoolUSValueW(LPCWSTR pszSubKey, LPCWSTR pszValue, BOOL fIgnoreHKCU, BOOL fDefault);

#ifdef UNICODE
#define SHRegGetBoolUSValue SHRegGetBoolUSValueW
#else
#define SHRegGetBoolUSValue SHRegGetBoolUSValueA
#endif

//
//  Association APIs
//
//  these APIs are to assist in accessing the data in HKCR
//  getting the Command strings and exe paths
//  for different verbs and extensions are simplified this way
//


enum {
    ASSOCF_DEFAULTTOUNKNOWN      = 0x00000001,  //  if no association, use "Unknown" key
    ASSOCF_EXE_VERIFYPATH        = 0x00000002,  //  verify that the path to exe exists
    ASSOCF_EXT_ISPATH            = 0x00000004,  //  pszExt is a path to use
    ASSOCF_EXT_NOPROGIDREMAP     = 0x00000008,  //  pszExt should be used without looking for the ProgId
    ASSOCF_SET_USEEXPAND         = 0x00000010,  //  strings have environment vars and need REG_EXPAND_SZ
    ASSOCF_SET_SUBSTENV          = 0x00000020,  //  attempt to use std env if they match...
    ASSOCF_NOFIXUPS              = 0x00000040,  //  Assoc APIs will attempt to fix errors if found
    ASSOCF_REMAPRUNDLL           = 0x00000080,  //  actually gets info about rundlls target if applicable

};

typedef enum {
    ASSOCSTR_COMMAND      = 1,  //  shell\verb\command string
    ASSOCSTR_EXECUTABLE,        //  the executable part of command string
    ASSOCSTR_FRIENDLYNAME,      //  friendly name of executable
    ASSOCSTR_SHELLNEWCLASS,     //  class under extension if shellnew key matches
    ASSOCSTR_NOOPEN,            //  noopen value
    ASSOCSTR_DESCRIPTION,       //  default value of progid, file type description
    ASSOCSTR_MAXSTR             //  last item in enum...
} ASSOCSTR;

typedef enum {
    APPSTR_EXECUTABLE     = 1,  //  the full path to the app
    APPSTR_PATH,                //  path to search for when running app
    APPSTR_FRIENDLYNAME,        //  the friendly name of the executable
    APPSTR_MAXSTR
} APPSTR;

LWSTDAPI AssocGetStringByKeyA(DWORD dwFlags, ASSOCSTR assocstr, HKEY hkeyId, LPCSTR pszVerb, LPSTR *ppszOut);
LWSTDAPI AssocGetStringByKeyW(DWORD dwFlags, ASSOCSTR assocstr, HKEY hkeyId, LPCWSTR pszVerb, LPWSTR *ppszOut);
#ifdef UNICODE
#define AssocGetStringByKey  AssocGetStringByKeyW
#else
#define AssocGetStringByKey  AssocGetStringByKeyA
#endif // !UNICODE
LWSTDAPI AssocGetStringByExtA(DWORD dwFlags, ASSOCSTR assocstr, LPCSTR pszExt, LPCSTR pszVerb, LPSTR *ppszOut);
LWSTDAPI AssocGetStringByExtW(DWORD dwFlags, ASSOCSTR assocstr, LPCWSTR pszExt, LPCWSTR pszVerb, LPWSTR *ppszOut);
#ifdef UNICODE
#define AssocGetStringByExt  AssocGetStringByExtW
#else
#define AssocGetStringByExt  AssocGetStringByExtA
#endif // !UNICODE
LWSTDAPI AssocOpenKeyByExtA(DWORD dwFlags, LPCSTR pszExt, HKEY *phkeyId);
LWSTDAPI AssocOpenKeyByExtW(DWORD dwFlags, LPCWSTR pszExt, HKEY *phkeyId);
#ifdef UNICODE
#define AssocOpenKeyByExt  AssocOpenKeyByExtW
#else
#define AssocOpenKeyByExt  AssocOpenKeyByExtA
#endif // !UNICODE
LWSTDAPI AssocAppGetStringByKeyA(DWORD dwFlags, APPSTR appstr, HKEY hkeyApp, LPSTR *ppszOut);
LWSTDAPI AssocAppGetStringByKeyW(DWORD dwFlags, APPSTR appstr, HKEY hkeyApp, LPWSTR *ppszOut);
#ifdef UNICODE
#define AssocAppGetStringByKey  AssocAppGetStringByKeyW
#else
#define AssocAppGetStringByKey  AssocAppGetStringByKeyA
#endif // !UNICODE
LWSTDAPI AssocAppGetStringByAppA(DWORD dwFlags, APPSTR appstr, LPCSTR pszApp, LPSTR *ppszOut);
LWSTDAPI AssocAppGetStringByAppW(DWORD dwFlags, APPSTR appstr, LPCWSTR pszApp, LPWSTR *ppszOut);
#ifdef UNICODE
#define AssocAppGetStringByApp  AssocAppGetStringByAppW
#else
#define AssocAppGetStringByApp  AssocAppGetStringByAppA
#endif // !UNICODE
LWSTDAPI AssocAppOpenKeyByAppA(DWORD dwFlags, LPCSTR pszApp, HKEY *phkeyApp);
LWSTDAPI AssocAppOpenKeyByAppW(DWORD dwFlags, LPCWSTR pszApp, HKEY *phkeyApp);
#ifdef UNICODE
#define AssocAppOpenKeyByApp  AssocAppOpenKeyByAppW
#else
#define AssocAppOpenKeyByApp  AssocAppOpenKeyByAppA
#endif // !UNICODE
LWSTDAPI AssocSetCommandByKeyA(DWORD dwFlags, HKEY hkey, LPCSTR pszVerb, LPCSTR pszExe, LPCSTR pszArgs);
LWSTDAPI AssocSetCommandByKeyW(DWORD dwFlags, HKEY hkey, LPCWSTR pszVerb, LPCWSTR pszExe, LPCWSTR pszArgs);
#ifdef UNICODE
#define AssocSetCommandByKey  AssocSetCommandByKeyW
#else
#define AssocSetCommandByKey  AssocSetCommandByKeyA
#endif // !UNICODE
LWSTDAPI AssocSetCommandByExtA(DWORD dwFlags, LPCSTR pszExt, LPCSTR pszVerb, LPCSTR pszExe, LPCSTR pszArgs);
LWSTDAPI AssocSetCommandByExtW(DWORD dwFlags, LPCWSTR pszExt, LPCWSTR pszVerb, LPCWSTR pszExe, LPCWSTR pszArgs);
#ifdef UNICODE
#define AssocSetCommandByExt  AssocSetCommandByExtW
#else
#define AssocSetCommandByExt  AssocSetCommandByExtA
#endif // !UNICODE


#endif //  NO_SHLWAPI_REG



#ifndef NO_SHLWAPI_STREAM
//
//=============== Stream Routines ===================================
//

LWSTDAPI_(struct IStream *) SHOpenRegStreamA(HKEY hkey, LPCSTR pszSubkey, LPCSTR pszValue, DWORD grfMode);
LWSTDAPI_(struct IStream *) SHOpenRegStreamW(HKEY hkey, LPCWSTR pszSubkey, LPCWSTR pszValue, DWORD grfMode);
#ifdef UNICODE
#define SHOpenRegStream  SHOpenRegStreamW
#else
#define SHOpenRegStream  SHOpenRegStreamA
#endif // !UNICODE

LWSTDAPI SHCreateStreamOnFileA(LPCSTR pszFile, DWORD grfMode, struct IStream **ppstm);
LWSTDAPI SHCreateStreamOnFileW(LPCWSTR pszFile, DWORD grfMode, struct IStream **ppstm);
#ifdef UNICODE
#define SHCreateStreamOnFile  SHCreateStreamOnFileW
#else
#define SHCreateStreamOnFile  SHCreateStreamOnFileA
#endif // !UNICODE



#endif // NO_SHLWAPI_STREAM



#if (_WIN32_IE >= 0x0500)

// SHAutoComplete
//      hwndEdit - HWND of editbox, ComboBox or ComboBoxEx.
//      dwReserved - Flags that aren't used yet.  Pass 0 for now.
//
//    Caller needs to have called CoInitialize() or OleInitialize()
//    and cannot call CoUninit/OleUninit until after
//    WM_DESTROY on hwndEdit.
LWSTDAPI SHAutoComplete(HWND hwndEdit, DWORD dwReserved);

#endif

#ifndef NO_SHLWAPI_GDI
//
//====== GDI helper functions  ================================================
//

LWSTDAPI_(HPALETTE) SHCreateShellPalette(HDC hdc);

#if (_WIN32_IE >= 0x0500)

LWSTDAPI_(void)     ColorRGBToHLS(COLORREF clrRGB, WORD* pwHue, WORD* pwLuminance, WORD* pwSaturation);
LWSTDAPI_(COLORREF) ColorHLSToRGB(WORD wHue, WORD wLuminance, WORD wSaturation);
LWSTDAPI_(COLORREF) ColorAdjustLuma(COLORREF clrRGB, int n, BOOL fScale);


#endif  // _WIN32_IE >= 0x0500

#endif // NO_SHLWAPI_GDI


//
//====== DllGetVersion  =======================================================
//

typedef struct _DllVersionInfo
{
        DWORD cbSize;
        DWORD dwMajorVersion;                   // Major version
        DWORD dwMinorVersion;                   // Minor version
        DWORD dwBuildNumber;                    // Build number
        DWORD dwPlatformID;                     // DLLVER_PLATFORM_*
} DLLVERSIONINFO;

// Platform IDs for DLLVERSIONINFO
#define DLLVER_PLATFORM_WINDOWS         0x00000001      // Windows 95
#define DLLVER_PLATFORM_NT              0x00000002      // Windows NT

//
// The caller should always GetProcAddress("DllGetVersion"), not
// implicitly link to it.
//

typedef HRESULT (CALLBACK* DLLGETVERSIONPROC)(DLLVERSIONINFO *);

// DllInstall (to be implemented by self-installing DLLs)
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine);


#ifdef __cplusplus
}
#endif

#ifdef _WIN32
#include <poppack.h>
#endif

#endif


#endif  // _INC_SHLWAPI

