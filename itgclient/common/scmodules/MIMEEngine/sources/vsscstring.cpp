#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "vsscstring.h"

#define VSSC_MIN(a,b) ((a) <= (b) ? (a) : (b))
#define VSSC_MAX(a,b) ((a) >= (b) ? (a) : (b))


// Allocate buffer whose size is a power of 2
static char* mem_alloc(_DWORD* aSize)
{
    
    // minimum size is 16
    _DWORD size = 16;
    while (size < *aSize)
	{
        size <<= 1;
    }
    *aSize = 0;
    char* buf = new char[size];
    if (buf != 0)
	{
        *aSize = size;
    }
    return buf;
}

static int myStrcasecmp(const char* s1, _DWORD len1, const char* s2,
    _DWORD len2)
{
    
    _DWORD len = VSSC_MIN(len1, len2);
    for (_DWORD i=0; i < len; ++i) {
        int c1 = tolower(s1[i]);
        int c2 = tolower(s2[i]);
        if (c1 < c2) {
            return -1;
        }
        else if (c1 > c2) {
            return 1;
        }
    }
    if (len1 < len2) {
        return -1;
    }
    else if (len1 > len2) {
        return 1;
    }
    return 0;
}


static int myStrCmp(const char* s1, _DWORD len1, const char* s2, _DWORD len2)
{
    
    _DWORD len = VSSC_MIN(len1, len2);
    for (_DWORD i=0; i < len; ++i) {
        if (s1[i] < s2[i]) {
            return -1;
        }
        else if (s1[i] > s2[i]) {
            return 1;
        }
    }
    if (len1 < len2) {
        return -1;
    }
    else if (len1 > len2) {
        return 1;
    }
    return 0;
}



inline void mem_free(char* szBuf)
{
    
    if (szBuf != 0) {
        delete [] szBuf;
    }
}

/*
// does a memcmp given the len and the str.
static int myStrCmp(const char *szStr1, _DWORD len1, const char *szStr2, _DWORD len2)
{
	if(len1 < len2)
		return -1;
	if(len1 > len2)
		return 1;
	_DWORD len = VSSC_MIN(len1, len2);
	
	int nRet;
	nRet = memcmp(szStr1, szStr2, len);

	return nRet;

}
*/

VSSCStringCount :: ~VSSCStringCount()  // destructor
{
		if(m_pszData)
			delete m_pszData;
}


VSSCStringCount :: VSSCStringCount()
{
	m_dwSize = 0;
	m_pszData = NULL;
	m_nRefCount = 1;
	_DWORD size = 1;
	char* szBuffer = mem_alloc(&size);
	if(szBuffer)
	{
		m_dwSize = size;
		m_pszData = szBuffer;
	}

}

// It takes the ownership of the buffer passed.
VSSCStringCount :: VSSCStringCount(char *szString, _DWORD nSize)
{
	m_dwSize = nSize;
	m_pszData = szString;
	m_nRefCount = 1;
	
}

//Definition of VSSCString Class

VSSCStringCount* VSSCString :: _IncrementRef(VSSCStringCount* Ref)
{
		Ref->m_nRefCount++;
		return Ref;
}

void VSSCString :: _delete_StringCount(VSSCStringCount* count)
{
	if(count == 0)
		return;

	--count->m_nRefCount;
    if (count->m_nRefCount == 0) {
        delete count;
    }
}

bool VSSCString :: _IsShared(VSSCStringCount* pStringCount)
{
	if(pStringCount->m_nRefCount > 1)
		return true;
	else
		return false;

}

void VSSCString::_copy()
{
    if (_IsShared(m_StringCount)) {
        _DWORD size = m_dwLen + 1;
        char* newBuf = mem_alloc(&size);

        if (newBuf != 0) {
            char* to = newBuf;
            const char* from = m_StringCount->m_pszData + m_dwStart;
            //mem_copy(from, mLength, to);

			memcpy(to, from, m_dwLen);
            to[m_dwLen] = 0;

            VSSCStringCount* scStrCount = new VSSCStringCount(newBuf, size);
            if (scStrCount) 
			{
                _delete_StringCount(m_StringCount);
                m_StringCount = scStrCount;
                m_dwStart = 0;
            }
            else /* if (rep == 0) */ {
                mem_free(newBuf);
                m_dwLen = 0;
            }
        }
        else /* if (newBuf == 0) */ {
            m_dwLen = 0;
        }
    }
}

VSSCString ::~VSSCString()
{
    
    _delete_StringCount(m_StringCount);
    m_StringCount = 0;
}

VSSCString :: VSSCString()
{
	m_dwLen = 0;
	m_dwStart = 0;
	m_StringCount = NULL;
	m_StringCount = new VSSCStringCount;
}

VSSCString :: VSSCString(const char *szString)
{
	m_dwStart = 0;
	m_dwLen = 0;
	m_StringCount = NULL;
	m_StringCount = new VSSCStringCount;
	_DWORD len = szString ? strlen(szString) : 0;

	//change
	//if(m_StringCount)
	if(len > 0)
	{
		_replace(0, m_dwLen, szString, len);
	}

}

VSSCString :: VSSCString(const char* szString, _DWORD nLen)
{
	m_dwStart = 0;
	m_dwLen = 0;
	m_StringCount = NULL;
	m_StringCount = new VSSCStringCount;
	if(m_StringCount)
	{
		_replace(0, m_dwLen, szString, nLen);
	}
}

VSSCString :: VSSCString(const VSSCString& vsscString, _DWORD dwPos, _DWORD dwLen)
{
	_DWORD Pos = VSSC_MIN(dwPos, vsscString.m_dwLen);
	_DWORD Len = VSSC_MIN(dwLen, vsscString.m_dwLen - Pos);
	if(Len > 0)
	{
		m_dwStart = vsscString.m_dwStart + Pos;
		m_dwLen = Len;
		m_StringCount = _IncrementRef(vsscString.m_StringCount);
	}
	else // create a new object with defaults.
	{
		m_dwStart = 0;
		m_dwLen = 0;
		m_StringCount = new VSSCStringCount;
	}
}

VSSCString& VSSCString :: assign(const VSSCString& vsscString, _DWORD dwPos, _DWORD dwLen)
{
	_DWORD pos = VSSC_MIN(dwPos, vsscString.m_dwLen);
    _DWORD len = VSSC_MIN(dwLen, vsscString.m_dwLen - pos);

	// If both points to the same StringCount
    if (m_StringCount == vsscString.m_StringCount) {
        m_dwStart = vsscString.m_dwStart + pos;
        m_dwLen = len;
    }
    else
	{
        _delete_StringCount(m_StringCount);
        m_StringCount = _IncrementRef(vsscString.m_StringCount);
         m_dwStart = vsscString.m_dwStart + pos;
        m_dwLen = len;
    }
    return *this;

}

VSSCString& VSSCString :: assign(const VSSCString& vsscString)
{
	if(this != &vsscString)
	{
		assign(vsscString, 0, vsscString.m_dwLen);
	}
	return *this;

}

VSSCString& VSSCString :: assign(const char* szString, _DWORD dwLen)
{
	_replace(0, m_dwLen, szString, dwLen);
	return *this;
}

VSSCString& VSSCString :: assign(const char* szString)
{
	_replace(0, m_dwLen, szString, strlen(szString));
	return *this;

}

VSSCString& VSSCString :: Concatenate(const VSSCString& vsscString, _DWORD dwPos, _DWORD dwLen)
{
	// both the StringCount == NULL return this
	if(m_StringCount == NULL || vsscString.m_StringCount == NULL)
	{
		return *this;
	}

	_DWORD pos = VSSC_MIN(dwPos, vsscString.m_dwLen);
	_DWORD len = VSSC_MIN(dwLen, vsscString.m_dwLen - pos);

	if(vsscString.m_StringCount == m_StringCount)
	{
		VSSCString vsscTemp(vsscString);
		_replace(m_dwLen, 0, &vsscTemp.m_StringCount->m_pszData[vsscTemp.m_dwStart + pos], len);
	}
	else
	{
		_replace(m_dwLen, 0, &vsscString.m_StringCount->m_pszData[vsscString.m_dwStart + pos], len);
	}
	return *this;

}

VSSCString& VSSCString :: Concatenate(const VSSCString& vsscString)
{
	return Concatenate(vsscString, 0, vsscString.m_dwLen);
}

VSSCString& VSSCString :: Concatenate(const char* szString, _DWORD dwLen)
{
	if(szString)
	{
		_replace(m_dwLen, 0, szString, dwLen);
	}
    return *this;

}


VSSCString& VSSCString :: Concatenate(const char* szString)
{
	_replace(m_dwLen, 0, szString, strlen(szString));
    return *this;

}


VSSCString VSSCString :: ParseString(_DWORD nPos, _DWORD nLen) const
{
	_DWORD pos = VSSC_MIN(nPos, m_dwLen);
	_DWORD len = VSSC_MIN(nLen, m_dwLen - pos);
	return VSSCString(*this, pos, len);
		 
}


_DWORD VSSCString :: Length() const
{
	return m_dwLen;
}

char* VSSCString :: GetStartPos() const
{
	return &m_StringCount->m_pszData[m_dwStart];
}

char* VSSCString :: GetString()
{
	if(_IsShared(m_StringCount))
	{
		VSSCString *mythis = (VSSCString *)this; // why not use this directly instead of mythis
									// answer: a non-const member function on a const object
		mythis->_copy();
		//*this->_copy();
	}
	else
	{
		m_StringCount->m_pszData[m_dwStart + m_dwLen] = 0;
	}
	return &m_StringCount->m_pszData[m_dwStart];

}

const char& VSSCString :: GetCharAt(_DWORD dwPos) const
{
	static char ch = 0;
	if ( dwPos < m_dwLen )
	{
		return GetStartPos()[dwPos];
	}
	else
	{
		//log error
		return ch; // undefined.
	}

}

char& VSSCString :: GetCharAt(_DWORD dwPos)
{
	static char ch = 0;
	if ( dwPos < m_dwLen )
	{
		return (char&)GetString()[dwPos];
	}
	else
	{
		//log error
		return ch; // undefined.
	}

}

// Implementation for overloaded operators.

VSSCString& VSSCString :: operator = (const char* szString)
{
	return assign(szString);
	
}

VSSCString& VSSCString :: operator = (const VSSCString& vsscString)
{
	return assign(vsscString);
}

VSSCString& VSSCString :: operator += (const VSSCString& vsscString)
{
	return Concatenate(vsscString);

}

VSSCString& VSSCString :: operator += (const char* szString)
{
	return Concatenate(szString);

}

const char& VSSCString :: operator [] (_DWORD dwPos) const
{
	return GetCharAt(dwPos);
}
char& VSSCString :: operator [] (_DWORD dwPos)
{
	return GetCharAt(dwPos);
}

    

VSSCString operator + (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	VSSCString vsscTemp(vsscString1);
	vsscTemp.Concatenate(vsscString2);
	return vsscTemp;
}

VSSCString operator + (const char* szString1, const VSSCString& vsscString2)
{
	VSSCString vsscTemp(szString1);
	vsscTemp.Concatenate(vsscString2);
	return vsscTemp;

}

_BOOL operator == (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet == 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator == (const VSSCString& vsscString1, const char* szString)
{
	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet == 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator == (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet == 0)
		return _TRUE;
	else
		return _FALSE;
	
}

_BOOL operator != (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet == 0)
		return _FALSE;
	else
		return _TRUE;

}

_BOOL operator != (const VSSCString& vsscString1, const char* szString)
{
	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet == 0)
		return _FALSE;
	else
		return _TRUE;

}

_BOOL operator != (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet == 0)
		return _FALSE;
	else
		return _TRUE;

}


_BOOL operator < (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet < 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator < (const VSSCString& vsscString1, const char* szString)
{

	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet < 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator < (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet < 0)
		return _TRUE;
	else
		return _FALSE;

}


_BOOL operator > (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet > 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator > (const VSSCString& vsscString1, const char* szString)
{
	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet > 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator > (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet > 0)
		return _TRUE;
	else
		return _FALSE;
}


_BOOL operator <= (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet <= 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator <= (const VSSCString& vsscString1, const char* szString)
{

	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet <= 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator <= (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet <= 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator >= (const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	
	if(nRet >= 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator >= (const VSSCString& vsscString1, const char* szString)
{
	int len1 = vsscString1.Length();
	int len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet >= 0)
		return _TRUE;
	else
		return _FALSE;

}

_BOOL operator >= (const char* szString, const VSSCString& vsscString2)
{
	int len1 = szString ? strlen(szString) : 0;
	int len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	int nRet = myStrCmp(szStr1, len1, szStr2, len2);
	if(nRet >= 0)
		return _TRUE;
	else
		return _FALSE;
}







// This is the most important function. Its the backbone for all the functions.
// This function is used to 
//		1.append to a string, if needed memory is deallocated and allocated
//		2.replace a string, if needed memory is deallocated and allocated
//		3.replace part of the string. 
// Replaces "aLen1" of characters starting from "aPos1" with "aLen2" characters from "aBuf"

/////////////Examples for replcae function which calls _replace /////////////////////
//	a += 'a'; // Data = VerisignAja
//	a.replace(2, 7, "XYXZFFF", 7); // Data = VeXYXZFFFja
//	a.replace(2, 4, "XYXZFFF", 3); // Data = VeXYXignAja
//  a.replace(2, 4, "XYXZFFF", 7); // Data = VeXYXZFFFgnAja - In this case we are replacing 4 characters with 7 characters.
								   // It takes care by shifting the extra 3 bytes to the right before replacing the 7 characters.


void VSSCString :: _replace(_DWORD aPos1, _DWORD aLen1, const char* aBuf,
    _DWORD aLen2)
{
    
    _DWORD pos1 = VSSC_MIN(aPos1, m_dwLen);
    _DWORD len1 = VSSC_MIN(aLen1, m_dwLen - pos1);
    //DW_ASSERT(m_dwStart + m_dwLen - len1 < ((_DWORD)-1) - aLen2);
    _DWORD len2 = VSSC_MIN(aLen2, ((_DWORD)-1) - (m_dwStart + m_dwLen - len1));
    _DWORD i;
    char* to;
    const char* from;
    _DWORD newLen = (m_dwLen - len1) + len2;
    // Is new string empty?
    if (newLen == 0 || aBuf == 0) {
        _DWORD size = 4;
        char* newBuf = mem_alloc(&size);
      //  DW_ASSERT(newBuf != 0);
        if (newBuf != 0) {
            newBuf[0] = 0;
            VSSCStringCount* rep = new VSSCStringCount(newBuf, size);
            //DW_ASSERT(rep != 0);
            if (rep != 0) {
                _delete_StringCount(m_StringCount);
                m_StringCount = rep;
                m_dwStart = 0;
                m_dwLen = newLen;
            }
        }
    }
    // Is buffer shared?  Is buffer too small?
    else if (_IsShared(m_StringCount) || newLen >= m_StringCount->m_dwSize) {
        _DWORD size = newLen + 1;
        char* newBuf = mem_alloc(&size);
        //DW_ASSERT(newBuf != 0);
        if (newBuf != 0) {
            to = newBuf;
            from = m_StringCount->m_pszData + m_dwStart;
            for (i=0; i < pos1; ++i) *to++ = *from++;
            from = aBuf;
            for (i=0; i < len2; ++i) *to++ = *from++;
            from = m_StringCount->m_pszData + m_dwStart + pos1 + len1;
            for (i=0; i < m_dwLen - pos1 - len1; ++i) *to++ = *from++;
            *to = 0;
            VSSCStringCount* rep = new VSSCStringCount(newBuf, size);
            //DW_ASSERT(rep != 0);
            if (rep != 0) {
                _delete_StringCount(m_StringCount);
                m_StringCount = rep;
                m_dwStart = 0;
                m_dwLen = newLen;
            }
        }
    }
    // Is the replacement smaller than the replaced?
    else if (len2 < len1) {
        to = m_StringCount->m_pszData + m_dwStart + pos1;
        from = aBuf;
        for (i=0; i < len2; ++i) *to++ = *from++;
        from = m_StringCount->m_pszData + m_dwStart + pos1 + len1;
        for (i=0; i < m_dwLen - pos1 - len1; ++i) *to++ = *from++;
        *to = 0;
        m_dwLen = newLen;
    }
    // Is there enough room at end of buffer?
    else if (m_dwStart + newLen < m_StringCount->m_dwSize) {
        to = m_StringCount->m_pszData + m_dwStart + newLen;
        from = m_StringCount->m_pszData + m_dwStart + m_dwLen - 1;
        *to-- = 0;
        for (i=0; i < m_dwLen-pos1-len1; ++i) *to-- = *from--;
        from = aBuf + (len2 - 1);
        for (i=0; i < len2; ++i) *to-- = *from--;
        m_dwLen = newLen;
    }
    // Is there enough room at beginning of buffer?
    else if (len2 - len1 <= m_dwStart) {
        to = m_StringCount->m_pszData + m_dwStart - (len2 - len1);
        from = m_StringCount->m_pszData + m_dwStart;
        for (i=0; i < pos1; ++i) *to++ = *from++;
        from = aBuf;
        for (i=0; i < len2; ++i) *to++ = *from++;
        m_dwStart -= len2 - len1;
        m_dwLen = newLen;
    }
    // There's enough room, but we must move characters.
    else {
        to = m_StringCount->m_pszData + newLen;
        from = m_StringCount->m_pszData + m_dwStart + m_dwLen - 1;
        *to-- = 0;
        for (i=0; i < m_dwLen-pos1-len1; ++i) *to-- = *from--;
        to = m_StringCount->m_pszData;
        from = m_StringCount->m_pszData + m_dwStart;
        for (i=0; i < pos1; ++i) *to++ = *from++;
        from = aBuf;
        for (i=0; i < len2; ++i) *to++ = *from++;
        m_dwStart = 0;
        m_dwLen = newLen;
    }
}



// Non Member functions
int VSSCStrcasecmp(const VSSCString& vsscString1, const VSSCString& vsscString2)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	return myStrcasecmp(szStr1, len1, szStr2, len2);
	
}

int VSSCStrcasecmp(const VSSCString& vsscString1, const char* szString)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = szString ? strlen(szString) : 0;
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	return  myStrcasecmp(szStr1, len1, szStr2, len2);
}

int VSSCStrcasecmp(const char* szString, const VSSCString& vsscString2)
{
	_DWORD len1 = szString ? strlen(szString) : 0;
	_DWORD len2 = vsscString2.Length();

	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	return myStrcasecmp(szStr1, len1, szStr2, len2);
	
}

int VSSCStrncasecmp(const VSSCString& vsscString1, const VSSCString& vsscString2,
						_DWORD dwLen)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = vsscString2.Length();
	
	len1 = VSSC_MIN(len1, dwLen);
	len2 = VSSC_MIN(len2, dwLen);
	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = vsscString2.GetStartPos();
	return myStrcasecmp(szStr1, len1, szStr2, len2);

}

int VSSCStrncasecmp(const VSSCString& vsscString1, const char* szString, _DWORD dwLen)
{
	_DWORD len1 = vsscString1.Length();
	_DWORD len2 = szString ? strlen(szString) : 0;
	len1 = VSSC_MIN(len1, dwLen);
	len2 = VSSC_MIN(len2, dwLen);

	const char *szStr1 = vsscString1.GetStartPos();
	const char *szStr2 = szString;

	return  myStrcasecmp(szStr1, len1, szStr2, len2);

}
int VSSCStrncasecmp(const char* szString, const VSSCString& vsscString2, _DWORD dwLen)
{
	 _DWORD len1 = szString ? strlen(szString) : 0;
	 _DWORD len2 = vsscString2.Length();
	
	len1 = VSSC_MIN(len1, dwLen);
	len2 = VSSC_MIN(len2, dwLen);
	const char *szStr1 = szString;
	const char *szStr2 = vsscString2.GetStartPos();

	return myStrcasecmp(szStr1, len1, szStr2, len2);
}


