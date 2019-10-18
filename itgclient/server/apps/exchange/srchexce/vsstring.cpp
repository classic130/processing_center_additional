/*
 *
 * $Revision: 1.1.2.1 $
 * $Header: /cvs/itgclient/server/apps/exchange/srchexce/Attic/vsstring.cpp,v 1.1.2.1 2000/03/15 00:13:50 aranade Exp $
 *
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include "vsstring.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>


#define MAX_INT_DIGITS  15  /* number of digits needed to represent largest int */


VSString::VSString (void)
{
	m_pszData = new char[1];
	*m_pszData = '\0';
	m_len = 0;
}


VSString::VSString (const char *s)
{
	if (s == (const char *) NULL)
	{
		m_pszData = new char[1];
		*m_pszData = '\0';
		m_len = 0;
		return;
	}
	else
	{
		m_pszData = new char [(m_len = strlen (s)) + 1];
		memcpy (m_pszData, s, m_len + 1);
	}
}


VSString::~VSString ()
{
	delete [] m_pszData;
}


VSString::VSString (const VSString& s)
{
	m_pszData = new char [s.m_len  + 1];
	memcpy (m_pszData, s.m_pszData, s.m_len);
	m_len = s.m_len;
	m_pszData[m_len] = '\0';
}


VSString& VSString::operator= (const VSString&s)
{
	delete [] m_pszData;
	m_len = s.m_len;
	if (m_len != 0)
	{
		m_pszData = new char [s.m_len + 1];
		memcpy (m_pszData, s.m_pszData, m_len+1);
	}
	else
	{
		m_pszData = new char [1];
		*m_pszData = '\0';
	}
	return *this;
}


E_BOOL VSString::operator== (const char *s) const
{
	if ((m_len == 0) && (s == (const char *) NULL))
    return eTRUE;
	if (s == (const char *) NULL)
    return eFALSE;

	int len = strlen (s);

	if (m_len != len)
    return eFALSE;

	if (memcmp (m_pszData, s, len) == 0)
    return eTRUE;
  else
    return eFALSE;
}


E_BOOL VSString::operator!= (const char *s) const
{
	if (*this == s)
    return eFALSE;
  else
    return eTRUE;
}


VSString& VSString::operator+ (const VSString& s)
{
	VSString *pcsRet = new VSString ();
	pcsRet->m_len = s.m_len + m_len ;
	delete [] pcsRet->m_pszData;
	pcsRet->m_pszData = new char [pcsRet->m_len + 1];

	if (m_len)
		memcpy (pcsRet->m_pszData, m_pszData, m_len);
	if (s.m_len) 
		memcpy (pcsRet->m_pszData+m_len, s.m_pszData, s.m_len+1);
	return *pcsRet;
}


VSString& VSString::operator+ (const char *s)
{
	int len = s == (const char *) NULL ? 0 : strlen (s);
	VSString *pcsRet = new VSString ();
	pcsRet->m_len = len + m_len;

	if (len == 0)
    return *pcsRet;

	delete [] pcsRet->m_pszData;
	pcsRet->m_pszData = new char [pcsRet->m_len + 1];
	memcpy (pcsRet->m_pszData, m_pszData, m_len);
	if (s != (const char *) NULL) 
		memcpy (pcsRet->m_pszData+m_len, s, len+1);
	return *pcsRet;
}


VSString& VSString::operator+= (const char *s)
{
	if ((s != (const char *) NULL) && (*s != '\0'))
	{
		int len = strlen (s);
		char *pszTmp = new char [ len + m_len + 1];
		memcpy (pszTmp, m_pszData, m_len);
		memcpy (pszTmp+m_len, s, len+1);
		delete [] m_pszData;
		m_pszData = pszTmp;
		m_len += len;
	}
	return *this;
}


VSString& VSString::operator+= (const char c)
{
	char *pszTmp = new char [m_len + 2];
	memcpy (pszTmp, m_pszData, m_len);
	pszTmp[m_len] = c;
	pszTmp[m_len+1] = '\0';
	delete [] m_pszData;
	m_pszData = pszTmp;
	m_len++;
	return *this;
}


VSString::operator const char * () const
{
	return m_pszData;
}


char *VSString::GetBuffer (int minlen)
{
	if (minlen > m_len)
	{
		char *ptr = new char [minlen];
		if (m_len != 0)
			memcpy (ptr, m_pszData, m_len);
		delete [] m_pszData;
		m_pszData = ptr;
	}
	return m_pszData;
}


void VSString::ReleaseBuffer (int newlen)
{
	if (newlen == -1)
	{
		m_len = strlen (m_pszData);
	}
	else
	{
		if (newlen > m_len)
		{
			char *ptr = new char [newlen+1];
			m_len = newlen;
			memcpy (ptr, m_pszData, m_len + 1);
			delete [] m_pszData;
			m_pszData = ptr;
		}
	}
}


void VSString::ToUpperCase()
{
  int i = 0;

  for (i=0; i <= m_len; i++)
   m_pszData[i] = toupper (m_pszData[i]); 
}


void VSString::MakeUpper ()
{
  int i = 0;

  for (i=0; i < m_len; i++)
    m_pszData[i] = toupper (m_pszData[i]); 
}


void VSString::MakeLower ()
{
	int i = 0;
	for (i = 0; i < m_len; i++)
		m_pszData[i] = tolower (m_pszData[i]);
}		


const char *VSString::FindString (const char *substring)
{
	if ((m_len == 0) || (substring == (const char *) NULL))
    return (const char *) NULL;
	char *s = strstr (m_pszData, substring);
	return s;
}


int VSString::Find (char c) const
{
  int i;

  for (i=0; i<m_len; i++) {
    if (m_pszData[i] == c)
      return (i);
  }
  return (-1);
}


VSString VSString::Left (int count) const
{
  char *s;
  VSString ts;

  if (count < 0)
    count = 0;
  else if (count > m_len)
    count = m_len;
  s = new char[count + 1];
  memcpy (s, m_pszData, count);
  s[count] = '\0';
  ts.m_pszData = s;
  ts.m_len = count;
  return (ts);
}


VSString VSString::Right (int count) const
{
  char *s;
  VSString ts;

  if (count < 0)
    count = 0;
  else if (count > m_len)
    count = m_len;
  s = new char[count + 1];
  memcpy (s, m_pszData + (m_len - count), count);
  s[count] = '\0';
  ts.m_pszData = s;
  ts.m_len = count;
  return (ts);
}


void VSString::UIntToString(unsigned int x)
{
	char buf[MAX_INT_DIGITS] ;

	sprintf (buf, "%u", x) ;
	delete [] m_pszData ;
	m_len = strlen (buf) ;
	m_pszData = new char [m_len + 1] ;
	memcpy (m_pszData, buf, m_len+1) ;
}


void VSString::IntToString(signed int x)
{
	char buf[MAX_INT_DIGITS] ;

	sprintf (buf, "%d", x) ;
	delete [] m_pszData ;
	m_len = strlen (buf) ;
	m_pszData = new char [m_len + 1] ;
	memcpy (m_pszData, buf, m_len+1) ;
}


void VSString::TruncateString(int len)
{

       if (m_len > len) {
         // clean out the rest
         memset (&m_pszData[len], 0, m_len-len);
         m_len = strlen(m_pszData);
       }
}

