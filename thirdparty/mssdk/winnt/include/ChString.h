/////////////////////////////////////////////////////////////////////////////
//
//
// CHSTRING.h -- Utility library version of MFC CString
//
// Copyright 1998 Microsoft Corporation
//
//
//=================================================================
#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _CHSTRING_H
#define _CHSTRING_H

/////////////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <limits.h>
#include <assert.h>
#include <tchar.h>
#include <polarity.h>
/////////////////////////////////////////////////////////////////////////////

struct _DOUBLE  { BYTE doubleBits[sizeof(double)]; };

/////////////////////////////////////////////////////////////////////////////
// CHString formatting
/////////////////////////////////////////////////////////////////////////////
#define TCHAR_ARG   TCHAR
#define WCHAR_ARG   WCHAR
#define CHAR_ARG    char

#if defined(_68K_) || defined(_X86_)
	#define DOUBLE_ARG  _DOUBLE
#else
	#define DOUBLE_ARG  double
#endif

#define FORCE_ANSI      0x10000
#define FORCE_UNICODE   0x20000

struct CHStringData
{
    long nRefs;
	int nDataLength;
	int nAllocLength;
	TCHAR* data()
		{ return (TCHAR*)(this+1); }
};
/////////////////////////////////////////////////////////////////////////////
class POLARITY CHString
{
    protected:

    	LPTSTR m_pchData;               // pointer to ref counted string data
                        	            // implementation helpers
        CHStringData* GetData() const;  // returns data pointer
	    void Init();
	    void AllocCopy(CHString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
        void AllocBuffer(int nLen);
	    void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);
	    void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data, int nSrc2Len, LPCTSTR lpszSrc2Data);
        void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData);
	    void FormatV(LPCTSTR lpszFormat, va_list argList);
	    void CopyBeforeWrite();
	    void AllocBeforeWrite(int nLen);
	    void Release();
	    static void Release(CHStringData* pData);
        static inline int SafeStrlen(LPCTSTR lpsz)	{ return (lpsz == NULL) ? 0 : lstrlen(lpsz); }

    public:
        // Constructors/Destruction
        CHString();
        CHString(const CHString& stringSrc);
        CHString(TCHAR ch, int nRepeat = 1);
        CHString(LPCSTR lpsz);
        CHString(LPCWSTR lpsz);
        CHString(LPCTSTR lpch, int nLength);
        inline CHString(const unsigned char* lpsz)	{ Init(); *this = (LPCSTR)lpsz; }

        ~CHString();

        // Functions
        void SetAt(int nIndex, TCHAR ch);
        void Empty();    

        // inlines
	    inline int GetLength() const { return GetData()->nDataLength; }
        inline BOOL IsEmpty() const  { return GetData()->nDataLength == 0; }
        inline TCHAR GetAt(int nIndex) const{ assert(nIndex >= 0);
	                                          assert(nIndex < GetData()->nDataLength);
	                                          return m_pchData[nIndex];
                                            }
        inline TCHAR operator[](int nIndex) const{	// same as GetAt
	                                          assert(nIndex >= 0);
	                                          assert(nIndex < GetData()->nDataLength);
	                                          return m_pchData[nIndex];
                                            }
        inline operator LPCTSTR() const 	{ return m_pchData; }
        inline int GetAllocLength() const	    { return GetData()->nAllocLength; }

    // overloaded assignment

        const CHString& operator=(const CHString& stringSrc);
        const CHString& operator=(TCHAR ch);
        const CHString& operator=(LPCSTR lpsz);
	    const CHString& operator=(LPCWSTR lpsz);
        inline const CHString& operator=(const unsigned char* lpsz) { *this = (LPCSTR)lpsz; return *this; }
        inline const CHString& operator=(CHString *p) { *this = p; return *this; }
        #ifdef _UNICODE
            inline const CHString& operator=(char ch){ *this = (TCHAR)ch; return *this; }        
        #endif
        
   // string concatenation
        #ifdef _UNICODE
            inline const CHString& CHString::operator+=(char ch)     { *this += (TCHAR)ch; return *this; }
            inline CHString  operator+(const CHString& string, char ch)	{ return string + (TCHAR)ch; }
            inline CHString  operator+(char ch, const CHString& string)	{ return (TCHAR)ch + string; }
        #endif

        const CHString& operator+=(const CHString& string);
        const CHString& operator+=(TCHAR ch);
	    const CHString& operator+=(LPCTSTR lpsz);

       friend CHString POLARITY WINAPI operator+(const CHString& string1,  const CHString& string2);
	    friend CHString POLARITY WINAPI operator+(const CHString& string, TCHAR ch);
	    friend CHString POLARITY WINAPI operator+(TCHAR ch, const CHString& string);
	    friend CHString POLARITY WINAPI operator+(const CHString& string, LPCTSTR lpsz);
	    friend CHString POLARITY WINAPI operator+(LPCTSTR lpsz, const CHString& string);

	// string comparison
	    int Compare(LPCTSTR lpsz) const;
	    inline int CompareNoCase(LPCTSTR lpsz) const{   // ignore case
                                                return _tcsicmp(m_pchData, lpsz); }   // MBCS/Unicode aware
	    inline int Collate(LPCTSTR lpsz) const{   // NLS aware
                // CHString::Collate is often slower than Compare but is MBSC/Unicode
                //  aware as well as locale-sensitive with respect to sort order.
                                                return _tcscoll(m_pchData, lpsz); }   // locale sensitive

    // Load string from resource file.
        int LoadString(UINT nID, LPTSTR lpszBuf, UINT nMaxBuf);
        BOOL LoadString(UINT nID);

    // Access to string implementation buffer as "C" character array
	    LPTSTR GetBuffer(int nMinBufLength);
	    void ReleaseBuffer(int nNewLength = -1);
	    LPTSTR GetBufferSetLength(int nNewLength);
	    void FreeExtra();

   	// Use LockBuffer/UnlockBuffer to turn refcounting off
        LPTSTR LockBuffer();
        void UnlockBuffer();

   	// searching (return starting index, or -1 if not found)
    // look for a single character match
        int Find(TCHAR ch) const;               // like "C" strchr
        int FindOneOf(LPCTSTR lpszCharSet) const;
        int ReverseFind(TCHAR ch) const;

   	// look for a specific sub-string
        int Find(LPCTSTR lpszSub) const;        // like "C" strstr

   	// upper/lower/reverse conversion
        void MakeUpper();
        void MakeLower();
        void MakeReverse();

        #ifndef _UNICODE
        	// ANSI <-> OEM support (convert string in place)
	        void AnsiToOem();
	        void OemToAnsi();
        #endif

	// simple sub-string extraction
        CHString Mid(int nFirst, int nCount) const;
        CHString Mid(int nFirst) const;
        CHString Left(int nCount) const;
        CHString Right(int nCount) const;

        CHString SpanIncluding(LPCTSTR lpszCharSet) const;
        CHString SpanExcluding(LPCTSTR lpszCharSet) const;

    // trimming whitespace (either side)
        void TrimRight();
        void TrimLeft();
    
    // simple formatting
	    void  __cdecl Format(LPCTSTR lpszFormat, ...);
    // formatting for localization (uses FormatMessage API)
	    void  __cdecl FormatMessage(LPCTSTR lpszFormat, ...);


    #ifndef _NO_BSTR_SUPPORT
	    // OLE BSTR support (use for OLE automation)
	    BSTR AllocSysString() const;
    #endif

};

inline BOOL operator==(const CHString& s1, const CHString& s2)  { return s1.Compare(s2) == 0; }
inline BOOL operator==(const CHString& s1, LPCTSTR s2)      	{ return s1.Compare(s2) == 0; }

inline BOOL operator!=(const CHString& s1, const CHString& s2)	{ return s1.Compare(s2) != 0; }
inline BOOL operator!=(const CHString& s1, LPCTSTR s2)      	{ return s1.Compare(s2) != 0; }

inline BOOL operator<(const CHString& s1, const CHString& s2)   { return s1.Compare(s2) < 0; }
inline BOOL operator<(const CHString& s1, LPCTSTR s2)       	{ return s1.Compare(s2) < 0; }

inline BOOL operator>(const CHString& s1, const CHString& s2)	{ return s1.Compare(s2) > 0; }
inline BOOL operator>(const CHString& s1, LPCTSTR s2)       	{ return s1.Compare(s2) > 0; }

inline BOOL operator<=(const CHString& s1, const CHString& s2)	{ return s1.Compare(s2) <= 0; }
inline BOOL operator<=(const CHString& s1, LPCTSTR s2)      	{ return s1.Compare(s2) <= 0; }

inline BOOL operator>=(const CHString& s1, const CHString& s2)	{ return s1.Compare(s2) >= 0; }
inline BOOL operator>=(const CHString& s1, LPCTSTR s2)      	{ return s1.Compare(s2) >= 0; }

const CHString& afxGetEmptyCHString();

#define afxEmptyCHString afxGetEmptyCHString()

#endif
