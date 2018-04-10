#ifndef _VSSCSTRING_H
#define _VSSCSTRING_H


/*
#define _DWORD	unsigned long
#define _BYTE	unsigned char*
#define _BOOL	bool
#define _TRUE	true
#define _FALSE	false
*/

#include "datatypes.h"

class VSSCStringCount
{
private:
	char *m_pszData;  // contains the string
	_DWORD m_nRefCount;  // ref count of the string.
	_DWORD m_dwSize; // size of the string
	friend class VSSCString;

public:
	VSSCStringCount(char *szString, _DWORD nSize); 
	VSSCStringCount();

	~VSSCStringCount();  // destructor
	
};


class VSSCString
{
private:
	VSSCStringCount *m_StringCount;
	_DWORD m_dwStart;
	_DWORD m_dwLen;

	void _delete_StringCount(VSSCStringCount* count);
	VSSCStringCount* _IncrementRef(VSSCStringCount* Ref);
	void _replace(_DWORD aPos1, _DWORD aLen1, const char* aBuf,
					_DWORD aLen2);
	bool _IsShared(VSSCStringCount* pStringCount);

	// Copies the inside string.. if its shared we decrement the count of the strcount allocate
	// new strcount make the String object point to this new StrCount object
	// doing this helps us to call the destructor properly and no need to worry about freeing this
	// returned string later.
	void _copy();



public:
	VSSCString();
	VSSCString(const VSSCString& vsscString, _DWORD dwPos = 0, _DWORD dwLen = 0xFFFFFFFF); // copy constructor
	VSSCString(const char *szString);
	VSSCString(const char* szString, _DWORD nLen);

	virtual ~VSSCString();

	void ToUpper();
	void ToLower();

	// Returns a string that contains atmost nLen characters starting at nStart.
	// It always returns less characters than available in the superstring.
	VSSCString ParseString(_DWORD nPos = 0, _DWORD nLen = 0xFFFFFFFF) const;

	// Assign functions
	VSSCString& assign(const VSSCString& vsscString);
    VSSCString& assign(const VSSCString& vsscString, _DWORD dwPos, _DWORD dwLen);
    VSSCString& assign(const char* szString, _DWORD dwLen);
    VSSCString& assign(const char* szString);

	// Concatenate functions
	VSSCString& Concatenate(const VSSCString& vsscString);
    VSSCString& Concatenate(const VSSCString& vsscString, _DWORD dwPos, _DWORD dwLen);
    VSSCString& Concatenate(const char* szString, _DWORD dwLen);
    VSSCString& Concatenate(const char* szString);

	//. Returns the character at position dwPos in the string's
    //. contents. The non-const version returns an lvalue that may be
    //. assigned to. Note that the non-const version always assumes that the
    //. contents will be modified and therefore always copies a shared
    //. internal buffer before it returns.
	const char& GetCharAt(_DWORD dwPos) const;
    char& GetCharAt(_DWORD dwPos);

  

	// Returns the substring given a String.
	VSSCString FindSubstr(char *szString);	
	VSSCString FindSubstr(VSSCString& vsscString);

	// Gets the length of the String
	_DWORD Length() const;
	
	// Gets Pointer to the character at m_dwStart 
	char* GetStartPos() const;

	// Returns the string.
	//const char *GetString() const; // I want this but gives compilation problem with _IsShared since it does not allow accessing non_const from a const member.
	 char *GetString() ;
		
	// Overloaded operators
	VSSCString& operator = (const VSSCString& vsscString);
    VSSCString& operator = (const char* szString);
	
	VSSCString& operator += (const VSSCString& vsscString);
	VSSCString& operator += (const char* szString);

	//. Note that the non-const version always assumes that the contents
    //. will be modified and therefore always copies a shared internal
    //. buffer before it returns.
	const char& operator [] (_DWORD dwPos) const;
    char& operator [] (_DWORD dwPos);



    

};

// These operators are implemented as functions as char* can also be used on left
// hand side of the operator.

VSSCString operator + (const VSSCString& vsscString1, const VSSCString& vsscString2);
VSSCString operator + (const char* szString1, const VSSCString& vsscString2);

_BOOL operator == (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator == (const VSSCString& vsscString1, const char* szString);
_BOOL operator == (const char* szString, const VSSCString& vsscString2);

_BOOL operator != (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator != (const VSSCString& vsscString1, const char* szString);
_BOOL operator != (const char* szString, const VSSCString& vsscString2);

_BOOL operator < (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator < (const VSSCString& vsscString1, const char* szString);
_BOOL operator < (const char* szString, const VSSCString& vsscString2);

_BOOL operator > (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator > (const VSSCString& vsscString1, const char* szString);
_BOOL operator > (const char* szString, const VSSCString& vsscString2);

_BOOL operator <= (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator <= (const VSSCString& vsscString1, const char* szString);
_BOOL operator <= (const char* szString, const VSSCString& vsscString2);

_BOOL operator >= (const VSSCString& vsscString1, const VSSCString& vsscString2);
_BOOL operator >= (const VSSCString& vsscString1, const char* szString);
_BOOL operator >= (const char* szString, const VSSCString& vsscString2);


int VSSCStrcasecmp(const VSSCString& vsscString1, const VSSCString& vsscString2);
int VSSCStrcasecmp(const VSSCString& vsscString1, const char* szString);
int VSSCStrcasecmp(const char* szString, const VSSCString& vsscString2);

int VSSCStrncasecmp(const VSSCString& vsscString1, const VSSCString& vsscString2,
						_DWORD aLen);

int VSSCStrncasecmp(const VSSCString& vsscString1, const char* szString, _DWORD dwLen);
int VSSCStrncasecmp(const char* szString, const VSSCString& vsscString2, _DWORD dwLen);

// Not Implemented
int VSSCStrcmp(const VSSCString& vsscString1, const VSSCString& vsscString2);
int VSSCStrcmp(const VSSCString& vsscString, const char* szString);
int VSSCStrcmp(const char* szString, const VSSCString& vsscString);

int VSSCStrncmp(const VSSCString& vsscString1, const VSSCString& vsscString2, _DWORD dwLen);
int VSSCStrncmp(const VSSCString& vsscString, const char* szString, _DWORD dwLen);
int VSSCStrncmp(const char* szString, const VSSCString& vsscString, _DWORD dwLen);

void VSSCStrcpy(VSSCString& vsscStringDest, const VSSCString& vsscStringSrc);
void VSSCStrcpy(VSSCString& vsscStringDest, const char* szStringSrc);
void VSSCStrcpy(char* szStringDest, const VSSCString& vsscStringSrc);

void VSSCStrncpy(VSSCString& vsscStringDest, const VSSCString& vsscStringSrc, _DWORD dwLen);
void VSSCStrncpy(VSSCString& vsscStringDest, const char* szStringSrc, _DWORD dwLen);
void VSSCStrncpy(char* szStringDest, const VSSCString& vsscStringSrc, _DWORD dwLen);




// Implement the following first Constructors and the = operators first.



#endif // VSSCSTRING_H
	

