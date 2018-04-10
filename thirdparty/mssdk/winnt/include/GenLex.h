//***************************************************************************
//
//  GENLEX.H
//
//  Generic lexer framework classes.
//
//  Copyright 1998 Microsoft Corporation
//
//***************************************************************************

#ifndef _GENLEX_H_
#define _GENLEX_H_

#include <..\include\Polarity.h>

class CGenLexSource
{
public:
    virtual wchar_t NextChar() = 0;
        // Return 0 on end-of-input
    virtual void Pushback(wchar_t) = 0;
    virtual void Reset() = 0;
};

class CTextLexSource : public CGenLexSource
{
    wchar_t *m_pSrcBuf;
    wchar_t *m_pStart;

public:
    CTextLexSource(wchar_t *pSrc) { m_pSrcBuf = m_pStart = pSrc; }
        // Binds directly to <pSrc> buffer, but doesn't delete it.

    wchar_t NextChar() { return *m_pSrcBuf++ ? m_pSrcBuf[-1] : 0; }
    void Pushback(wchar_t) { --m_pSrcBuf; }
    void Reset() { m_pSrcBuf = m_pStart; }
};


#pragma pack(2)
struct LexEl
{
    wchar_t cFirst, cLast;
    WORD wGotoState;
    WORD wReturnTok;
    WORD wInstructions;
};
#pragma pack()


// Lexer driver instructions

#define GLEX_ACCEPT      0x1            // Add the char to the token
#define GLEX_CONSUME     0x2            // Consume the char without adding to token
#define GLEX_PUSHBACK    0x4            // Place the char back in the source buffer for next token
#define GLEX_NOT         0x8            // A match occurs if the char is NOT the one specified
#define GLEX_LINEFEED    0x10               // Increase the source linecount
#define GLEX_RETURN      0x20               // Return the indicated token to caller
#define GLEX_ANY         wchar_t(0xFFFF)    // Any character
#define GLEX_EMPTY       wchar_t(0xFFFE)    // When subrange is not specified

class POLARITY CGenLexer
{
    wchar_t    *m_pTokenBuf;
    int         m_nCurrentLine;
    int         m_nCurBufSize;
    CGenLexSource   *m_pSrc;
    LexEl           *m_pTable;
    
public:
    CGenLexer(LexEl *pTbl, CGenLexSource *pSrc);
    
   ~CGenLexer(); 
    int NextToken();
        // Returns 0 on end of input.

    wchar_t* GetTokenText() { return m_pTokenBuf; }
    int GetLineNum() { return m_nCurrentLine; }
    void Reset();
};

#endif