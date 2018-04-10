#include <ctype.h>
#include "vssctoken.h"


_BOOL ISSPECIAL(int ch)
{
	if( ch == '(' 
		|| ch == ')'
		|| ch == '<'
		|| ch == '>'
		|| ch == '@'
		|| ch == ','
		|| ch == ';'
		|| ch == ':'
		|| ch == '\\'
		|| ch == '"'
		|| ch == '.'
		|| ch == '['
		|| ch == ']'
		)
	{
		return _TRUE;
	}
	else
	{
		return _FALSE;
	}

}

_BOOL ISTSPECIAL(int ch)
{
	if(	ch == '(' 
		|| ch == ')'
		|| ch == '<'
		|| ch == '>'
		|| ch == '@'
		|| ch == ','
		|| ch == ';'
		|| ch == ':'
		|| ch == '\\'
		|| ch == '"'
		|| ch == '['
		|| ch == ']'
		|| ch == '?'
		|| ch == '/'
		|| ch == '='
		)
	{
		return _TRUE;
	}
	else
	{
		return _FALSE;
	}

}

VSSCTokenizer :: VSSCTokenizer(const VSSCString& vsscString) 
				:m_vsscString(vsscString)
{
	m_dwTokenStart = 0;
    m_dwTokenLength = 0;
    m_dwNextStart = 0;
    m_TkType = eTkError;
}

VSSCTokenizer :: VSSCTokenizer(const char* szString) 
				:m_vsscString(szString)
{
	m_dwTokenStart = 0;
    m_dwTokenLength = 0;
    m_dwNextStart = 0;
    m_TkType = eTkError;
}

VSSCTokenizer::~VSSCTokenizer()
{
}


int VSSCTokenizer :: GetType() const
{
	return m_TkType;
}
const VSSCString& VSSCTokenizer :: GetToken() const
{
	return m_vsscToken;
}



// Remove the delimeters in the token string.
// For example : [boundary] is the token before and would be boundary after
void VSSCTokenizer :: StripDelimiters()
{
	// Length should atleast be 1
	if(m_dwTokenLength < 2)
	{
		return;
	}

	// const ref -- avoids copy on write when using operator[]
	const VSSCString Token = m_vsscToken;
	switch(m_TkType)
	{
	case eTkQuotedString:
		// Starting case
		if(Token[0] == '"')
		{
			m_vsscToken = m_vsscToken.ParseString(1);
			m_dwTokenStart ++;
			m_dwTokenLength --;
		}
		//ending case
		//if(m_dwTokenLength > 0 && Token[m_dwTokenLength - 1] == '"')
		if(m_dwTokenLength > 0 && Token[m_dwTokenLength] == '"')
		{
			m_vsscToken = m_vsscToken.ParseString(0, m_dwTokenLength - 1);
			m_dwTokenLength --;
		}
		break;
	case eTkDomainLiteral:
		// Starting case
		if(Token[0] == '[')
		{
			m_vsscToken = m_vsscToken.ParseString(1);
			m_dwTokenStart ++;
			m_dwTokenLength --;
		}
		//ending case
		if(m_dwTokenLength > 0 && Token[m_dwTokenLength - 1] == ']')
		{
			m_vsscToken = m_vsscToken.ParseString(0, m_dwTokenLength - 1);
			m_dwTokenLength --;
		}
		break;
	case eTkComment:
		// Starting case
		if(Token[0] == '(')
		{
			m_vsscToken = m_vsscToken.ParseString(1);
			m_dwTokenStart ++;
			m_dwTokenLength --;
		}
		//ending case
		if(m_dwTokenLength > 0 && Token[m_dwTokenLength - 1] == ')')
		{
			m_vsscToken = m_vsscToken.ParseString(0, m_dwTokenLength - 1);
			m_dwTokenLength --;
		}
		break;
	}

}


// In all the Parse functions below it is assumed that the 
// the starting character of these lexical tokens have been 
// already detected. These parsing functions finds the end
// of such tokens.
void VSSCTokenizer :: ParseQuotedString()
{
	_DWORD dwPos = m_dwTokenStart;
	while(1)
	{
		++dwPos;
		// check we are using more than what we should
		if(dwPos >= m_vsscString.Length())
		{
			m_dwTokenStart = 0;
			m_vsscToken = "";
			m_dwNextStart = dwPos;
			m_TkType = eTkError;
			break;
		}
		else if(m_vsscString[dwPos] == '\\')
		{
			++dwPos; // increment if it is a quoted char
			// check we are using more than what we should
			if(dwPos >= m_vsscString.Length())
			{
				m_dwTokenStart = 0;
				m_vsscToken = "";
				m_dwNextStart = dwPos;
				m_TkType = eTkError;
				break;
			}

		}
		else if(m_vsscString[dwPos] == '"')
		{
			// End of Quoted string
			++dwPos;
			m_dwTokenLength = dwPos - m_dwTokenStart;
			m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, m_dwTokenLength);
			m_dwNextStart = dwPos;
			break;

		}
	}
}
			
void VSSCTokenizer :: ParseDomainLiteral()	
{
	_DWORD dwPos = m_dwTokenStart;
	while(1)
	{
		++dwPos;
		// check we are using more than what we should
		if(dwPos >= m_vsscString.Length())
		{
			m_dwTokenStart = 0;
			m_vsscToken = "";
			m_dwNextStart = dwPos;
			m_TkType = eTkError;
			break;
		}
		else if(m_vsscString[dwPos] == '\\')
		{
			++dwPos; // increment if it is a quoted char
			// check we are using more than what we should
			if(dwPos >= m_vsscString.Length())
			{
				m_dwTokenStart = 0;
				m_vsscToken = "";
				m_dwNextStart = dwPos;
				m_TkType = eTkError;
				break;
			}

		}
		else if(m_vsscString[dwPos] == ']')
		{
			// End of Domain Literal
			++dwPos;
			m_dwTokenLength = dwPos - m_dwTokenStart;
			m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, m_dwTokenLength);
			m_dwNextStart = dwPos;
			break;

		}
	}

}

void VSSCTokenizer :: ParseComment()
{
	_DWORD dwPos = m_dwTokenStart;
	int count = 1; // to take of the nested comments.
	while(1)
	{
		++dwPos;
		// check we are using more than what we should
		if(dwPos >= m_vsscString.Length())
		{
			m_dwTokenStart = 0;
			m_vsscToken = "";
			m_dwNextStart = dwPos;
			m_TkType = eTkError;
			break;
		}
		else if(m_vsscString[dwPos] == '\\')
		{
			++dwPos; // increment if it is a quoted char
			// check we are using more than what we should
			if(dwPos >= m_vsscString.Length())
			{
				m_dwTokenStart = 0;
				m_vsscToken = "";
				m_dwNextStart = dwPos;
				m_TkType = eTkError;
				break;
			}

		}
		else if(m_vsscString[dwPos] == ')')
		{
			--count;
			if(count == 0)
			{
				// End of Domain Literal
				++dwPos;
				m_dwTokenLength = dwPos - m_dwTokenStart;
				m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, m_dwTokenLength);
				m_dwNextStart = dwPos;
				break;
			}

		}
		else if(m_vsscString[dwPos] == '(')
		{
			++count;
		}
	}

}

VSSCRfc822Tokenizer :: VSSCRfc822Tokenizer(const VSSCString& vsscString)
: VSSCTokenizer(vsscString)
{
	ParseToken();	
}

VSSCRfc822Tokenizer :: VSSCRfc822Tokenizer(const char* szString)
: VSSCTokenizer(szString)
{
	ParseToken();
}


VSSCRfc822Tokenizer :: ~VSSCRfc822Tokenizer()
{

}

void VSSCRfc822Tokenizer :: ParseToken()
{
    // Assume the field body has already been extracted.  That is, we don't
    // have to watch for the end of the field body or folding.  We just
    // treat any CRs or LFs as white space.
    m_dwTokenStart = m_dwNextStart;
    m_dwTokenLength = 0;
    m_TkType = eTkNull;
    if (m_dwTokenStart >= m_vsscString.Length()) {
        return;
    }
    // Skip leading space.  Also, since control chars are not permitted
    // in atoms, skip these, too.
    while (1) {
        if (m_dwTokenStart >= m_vsscString.Length()) {
            return;
        }
        int ch = m_vsscString[m_dwTokenStart];
        if (!isspace(ch) && !iscntrl(ch)) {
            break;
        }
        ++m_dwTokenStart;
    }
    char ch = m_vsscString[m_dwTokenStart];
    // Quoted string
    if (ch == '"') {
        m_TkType = eTkQuotedString;
        ParseQuotedString();
    }
    // Comment
    else if (ch == '(') {
        m_TkType = eTkComment;
        ParseComment();
    }
    // Domain literal
    else if (ch == '[') {
        m_TkType = eTkDomainLiteral;
        ParseDomainLiteral();
    }
    // Special
    else if (ISSPECIAL(ch)) {
        m_TkType = eTkSpecial;
        m_dwTokenLength = 1;
        m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, 1);
        m_dwNextStart = m_dwTokenStart + 1;
    }
    // Atom
    else {
        m_TkType = eTkAtom;
        ParseAtom();
    }
    
}

void VSSCRfc822Tokenizer :: ParseAtom()
{
	_DWORD dwPos = m_dwTokenStart;

	while(1)
	{
		++dwPos;
		char ch = (dwPos < m_vsscString.Length()) ? m_vsscString[dwPos] : (char) 0;
		if( dwPos >= m_vsscString.Length() 
			|| isspace(ch)
			|| iscntrl(ch)
			|| ISSPECIAL(ch)
			)
		{
			m_dwTokenLength = dwPos - m_dwTokenStart;
			m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, m_dwTokenLength);
			m_dwNextStart = dwPos;
			break;
		}
	}

}


int VSSCRfc822Tokenizer :: operator ++ ()
{
	ParseToken();
	return m_TkType;

}

int VSSCRfc822Tokenizer :: Restart()
{
	m_dwNextStart = 0;
	ParseToken();
	return m_TkType;

}


// Implementation for VSSCRfc2045Tokenizer

VSSCRfc2045Tokenizer :: VSSCRfc2045Tokenizer(const VSSCString& vsscString)
: VSSCTokenizer(vsscString)
{
	ParseToken();	
}

VSSCRfc2045Tokenizer :: VSSCRfc2045Tokenizer(const char* szString)
: VSSCTokenizer(szString)
{
	ParseToken();
}


VSSCRfc2045Tokenizer :: ~VSSCRfc2045Tokenizer()
{

}

void VSSCRfc2045Tokenizer :: ParseToken()
{
    // Assume the field body has already been extracted.  That is, we don't
    // have to watch for the end of the field body or folding.  We just
    // treat any CRs or LFs as white space.
    m_dwTokenStart = m_dwNextStart;
    m_dwTokenLength = 0;
    m_TkType = eTkNull;
    if (m_dwTokenStart >= m_vsscString.Length()) {
        return;
    }
    // Skip leading space.  Also, since control chars are not permitted
    // in atoms, skip these, too.
    while (1) {
        if (m_dwTokenStart >= m_vsscString.Length()) {
            return;
        }
        int ch = m_vsscString[m_dwTokenStart];
        if (!isspace(ch) && !iscntrl(ch)) {
            break;
        }
        ++m_dwTokenStart;
    }
    char ch = m_vsscString[m_dwTokenStart];
    // Quoted string
    if (ch == '"') {
        m_TkType = eTkQuotedString;
        ParseQuotedString();
    }
    // Comment
    else if (ch == '(') {
        m_TkType = eTkComment;
        ParseComment();
    }
    // Domain literal
    else if (ch == '[') {
        m_TkType = eTkDomainLiteral;
        ParseDomainLiteral();
    }
    // Special
    else if (ISTSPECIAL(ch)) {
        m_TkType = eTkTspecial;
        m_dwTokenLength = 1;
        m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, 1);
        m_dwNextStart = m_dwTokenStart + 1;
    }
    // Atom
    else {
        m_TkType = eTkToken;
        ParseAtom();
    }
    
}

void VSSCRfc2045Tokenizer :: ParseAtom()
{
	_DWORD dwPos = m_dwTokenStart;

	while(1)
	{
		++dwPos;
		char ch = (dwPos < m_vsscString.Length()) ? m_vsscString[dwPos] : (char) 0;
		if( dwPos >= m_vsscString.Length() 
			|| isspace(ch)
			|| iscntrl(ch)
			|| ISTSPECIAL(ch)
			)
		{
			m_dwTokenLength = dwPos - m_dwTokenStart;
			m_vsscToken = m_vsscString.ParseString(m_dwTokenStart, m_dwTokenLength);
			m_dwNextStart = dwPos;
			break;
		}
	}

}


int VSSCRfc2045Tokenizer :: operator ++ ()
{
	ParseToken();
	return m_TkType;

}

int VSSCRfc2045Tokenizer :: Restart()
{
	m_dwNextStart = 0;
	ParseToken();
	return m_TkType;

}



///////////Implementation for VSSCGroupTokens class


VSSCGroupTokens :: VSSCGroupTokens(const VSSCString& vsscString)
:m_vsscString(vsscString)
{
	m_nTokensStart = 0;
	m_nTokensLen = 0;
}

VSSCGroupTokens :: ~VSSCGroupTokens()
{

}


const VSSCString& VSSCGroupTokens:: GetTokens() const 
{
	return m_vsscTokens;
}

void VSSCGroupTokens :: SetFirstToken(const VSSCTokenizer& Tokenizer)
{
	switch (Tokenizer.GetType()) {
    case eTkError:
    case eTkNull:
        m_nTokensStart  = Tokenizer.m_dwTokenStart;
        m_nTokensLen = 0;
        break;
    case eTkComment:
    case eTkDomainLiteral:
    case eTkQuotedString:
    case eTkSpecial:
    case eTkAtom:
    case eTkTspecial:
    case eTkToken:
        m_nTokensStart  = Tokenizer.m_dwTokenStart;
        m_nTokensLen = Tokenizer.m_dwTokenLength;
        break;
    }
	m_vsscTokens = m_vsscString.ParseString(m_nTokensStart, m_nTokensLen);
}


void VSSCGroupTokens :: ExtendTo(const VSSCTokenizer& Tokenizer)
{
	if(Tokenizer.m_dwTokenStart < m_nTokensStart)
		return;
	m_nTokensLen = Tokenizer.m_dwTokenStart - m_nTokensStart;
	m_vsscTokens = m_vsscString.ParseString(m_nTokensStart, m_nTokensLen);
}

				  