#ifndef _VSSCTOKENIZER_H
#define _VSSCTOKENIZER_H

#include "vsscstring.h"


enum {
    eTkError=-1,
    eTkNull=0,
    eTkSpecial,
    eTkAtom,
    eTkComment,
    eTkQuotedString,
    eTkDomainLiteral,
    eTkTspecial,
    eTkToken
};


class VSSCTokenizer
{
	 friend class VSSCGroupTokens;
public:
	const VSSCString& GetToken() const;
	int GetType() const;
	void StripDelimiters();
protected:
	VSSCTokenizer(const VSSCString& vsscString);
    VSSCTokenizer(const char* szString);
    virtual ~VSSCTokenizer();
    
    // Quoted strings, comments, and domain literals are parsed
    // identically in RFC822 and RFC1521
    void ParseQuotedString();
    void ParseComment();
    void ParseDomainLiteral();

    // Data members
    const VSSCString m_vsscString; // the input string
    VSSCString m_vsscToken;  // this holds the token
    _DWORD m_dwTokenStart;   
    _DWORD m_dwTokenLength;
    _DWORD m_dwNextStart;
    int m_TkType;

};

class VSSCRfc822Tokenizer : public VSSCTokenizer
{
public:
    VSSCRfc822Tokenizer(const VSSCString& vsscString);
    VSSCRfc822Tokenizer(const char* szString);
    virtual ~VSSCRfc822Tokenizer();
    int Restart();
    int operator ++ (); // prefix increment operator
private:
    void ParseToken();
    void ParseAtom();
};

class VSSCRfc2045Tokenizer : public VSSCTokenizer
{
public:
    VSSCRfc2045Tokenizer(const VSSCString& vsscString);
    VSSCRfc2045Tokenizer(const char* szString);
    virtual ~VSSCRfc2045Tokenizer();
    int Restart();
    int operator ++ (); // prefix increment operator
private:
    void ParseToken();
    void ParseAtom();
};


// Concatenates the tokens into one string.
class VSSCGroupTokens
{
public:
	VSSCGroupTokens(const VSSCString& vsscString);
	virtual ~VSSCGroupTokens();

	const VSSCString& GetTokens() const ;
	void SetFirstToken(const VSSCTokenizer& Tokenizer);
	void ExtendTo(const VSSCTokenizer& Tokenizer);


private:
	int m_nTokensStart;
	int m_nTokensLen;
	VSSCString m_vsscTokens;
	VSSCString m_vsscString;
};

#endif //_VSSCTOKENIZER_H