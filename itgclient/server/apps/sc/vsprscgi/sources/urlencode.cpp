/*
 * $Revision: 1.1.8.2 $
 * $Header: /cvs/itgclient/server/apps/sc/vsprscgi/sources/urlencode.cpp,v 1.1.8.2 2001/09/12 00:21:03 npaul Exp $
 */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1997. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "urlenode.h"

char* URLEncodeAlloc(const unsigned char* buffer, int n)
{
  int           length = 0;
  const int	BUFSIZE = 64;
  int           size = BUFSIZE;

  char*         escaped;
  const char*         hex = "0123456789ABCDEF";
  const unsigned char *unescaped;

  unescaped = buffer;
  escaped   = (char *)calloc(size+1,sizeof(char));

  if (!buffer || n==0) return "";

  *escaped = NULL;

  while(buffer - unescaped < n){

    if(length+3 > size){
      size+=BUFSIZE;
      escaped = (char *)realloc(escaped, size+1);
    }

    if(!escaped)
      return NULL;

    if ((*buffer >= 'a' && *buffer <= 'z') ||
        (*buffer >= 'A' && *buffer <= 'Z') ||
        (*buffer >= '0' && *buffer <= '9'))
    {
      escaped[length++] = *buffer;

    }
    else if (*buffer == ' ')
    {
      escaped[length++] = '+';
    }
    else
    {
      escaped[length++] = '%';
      escaped[length++] = hex[((unsigned char)*buffer) >> 4];
      escaped[length++] = hex[((unsigned char)*buffer) & 15];
    }
    escaped[length] = NULL;
    ++buffer;
  }
  return(escaped);
}

char* URLEncodeAlloc2(const unsigned char* buffer, int n)
{
  int           length = 0;
  const int     BUFSIZE = 64;
  int           size = BUFSIZE;

  char*         escaped;
  const char*         hex = "0123456789ABCDEF";
  const unsigned char *unescaped;

  unescaped = buffer;
  escaped   = (char *)calloc(size+1,sizeof(char));

  if (!buffer || n==0) return "";

  *escaped = NULL;

  while(buffer - unescaped < n){

    if(length+3 > size){
      size+=BUFSIZE;
      escaped = (char *)realloc(escaped, size+1);
    }

    if(!escaped)
      return NULL;

    if ((*buffer >= 'a' && *buffer <= 'z') ||
        (*buffer >= 'A' && *buffer <= 'Z') ||
        (*buffer >= '0' && *buffer <= '9'))
    {
      escaped[length++] = *buffer;

    }
//    else if (*buffer == ' ')
//    {
//      escaped[length++] = '+';
//    }
    else
    {
      escaped[length++] = '#';
      escaped[length++] = hex[((unsigned char)*buffer) >> 4];
      escaped[length++] = hex[((unsigned char)*buffer) & 15];
    }
    escaped[length] = NULL;
    ++buffer;
  }
  return(escaped);
}

int URLDecodeAlloc(const char *pszBuf, unsigned char **pbOutputBuf, int *pnOutputBufLen)
{
  unsigned char *pbOut ;
  int nbytesIn = strlen(pszBuf) + 1;
  char pszTmp[3] ;
  int nTmp ;
  char c ;
  int i, j ;
  pbOut = (unsigned char *)malloc(nbytesIn +1) ; // worst case scenario
  for( i = 0, j=0 ; i < nbytesIn ; i++, j++ )
  {
    switch(pszBuf[i] )
    {
    case '+' :
      pbOut[j] = ' ' ;
      break ;
    case '%':
      if( pszBuf[i+1] == '%' )
      {
        i++ ;
        pbOut[j] = pszBuf[i] ;
        break ;
      }
      pszTmp[0] = pszBuf[i+1] ;
      pszTmp[1] = pszBuf[i+2] ;
      pszTmp[2] = '\0' ;
      if( sscanf(pszTmp, "%x", &nTmp) != 1 ) return -1 ;
      pbOut[j] = (unsigned char)nTmp ;
      i += 2 ;
      break ;
    default:
      pbOut[j] = pszBuf[i] ;
      break ;
    }
  }
  *pbOutputBuf = pbOut ;
  *pnOutputBufLen = j ;
  return i ;
}

int URLDecodeAlloc2(const char *pszBuf, unsigned char **pbOutputBuf, int *pnOutputBufLen)
{
  unsigned char *pbOut ;
  int nbytesIn = strlen(pszBuf) + 1;
  char pszTmp[3] ;
  int nTmp ;
  char c ;
  int i, j ;
  pbOut = (unsigned char *)malloc(nbytesIn +1) ; // worst case scenario
  for( i = 0, j=0 ; i < nbytesIn ; i++, j++ )
  {
    switch(pszBuf[i] )
    {
    case '+' :
      pbOut[j] = ' ' ;
      break ;
    case '#':
      if( pszBuf[i+1] == '%' )
      {
        i++ ;
        pbOut[j] = pszBuf[i] ;
        break ;
      }
      pszTmp[0] = pszBuf[i+1] ;
      pszTmp[1] = pszBuf[i+2] ;
      pszTmp[2] = '\0' ;
      if( sscanf(pszTmp, "%x", &nTmp) != 1 ) return -1 ;
      pbOut[j] = (unsigned char)nTmp ;
      i += 2 ;
      break ;
    default:
      pbOut[j] = pszBuf[i] ;
      break ;
    }
  }
  *pbOutputBuf = pbOut ;
  *pnOutputBufLen = j ;
  return i ;
}

