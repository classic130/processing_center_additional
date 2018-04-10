/*
 * $Revision: 1.2 $
 * $Header: /cvs/itgclient/server/apps/exchange/srchexce/vsstring.h,v 1.2 2000/03/16 02:49:00 mwilson Exp $
 *
 */


#ifndef __cplusplus
#error "This file requires a C++ compiler"
#endif

/*--------------------------------------------------------------------\
| Copyright  (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSSTRING_H
#define _VSSTRING_H

//#include "vsglobal.h"
//#include "vsobject.h"

typedef enum { eFALSE=0, eTRUE=1} E_BOOL ;


class VSString 
{
public:
  // Constructors
	VSString (void);
	VSString (const char *s);
	VSString (const VSString& s);			// copy constructor
	VSString::~VSString();

  // Operators
	VSString&    operator= (const VSString & s);
	E_BOOL       operator== (const char *s) const;
	E_BOOL       operator!= (const char *s) const;
	VSString&    operator+ (const char *s);
	VSString&    operator+= (const char *s);
	VSString&    operator+= (const char c);
	VSString&    operator+ (const VSString& s);
	             operator const char* () const;

  // Assorted Methods
	const char  *FindString (const char *substring);
	VSString     Left (int count) const;
	VSString     Right (int count) const;
	int          Find (char c) const;
	char        *GetBuffer (int minlen=0);
	void         ReleaseBuffer (int newlen=-1);
	unsigned int Length () const { return m_len; } ;
  void         ToUpperCase();
	void         MakeUpper();
	void         MakeLower();
	void         TruncateString (int len);
	void		Replace(char a, char b); // Replaces all occurences of 'a' with 'b'

  // These methods convert the number to a string
  // and replace whatever was in the VSString
	void         UIntToString (unsigned int x);
	void         IntToString (signed int x);

protected:
	char        *m_pszData;
	int          m_len;

};

// For backward compatibility, define TString to be VSString

#define TString VSString


#endif
