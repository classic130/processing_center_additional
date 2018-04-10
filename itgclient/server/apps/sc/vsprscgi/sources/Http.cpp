// Http.cpp: implementation of the Http class.
//
//////////////////////////////////////////////////////////////////////
//
// System Includes
//

#define INC_OLE2
#include <windows.h>
//
// CRunTime Includes
//

#include <stdlib.h>
#include <limits.h>
#include <io.h>
#include <stdio.h>
#include <winbase.h>
#include <userenv.h>

//#include <atl11\atlbase.h>
#include<atlbase.h>

#include "Http.h"
#include "vsstring.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CHttp::CHttp()
{
	PHTTPVARS	currentHttpVar ;
	DWORD		dwQueryString = 0 ;

	currentHttpVar = _hvAllHttpVars = NULL ;
	_bFirstVar = TRUE ;
	_VarCount = 0 ;
	_szQueryString = NULL ;
	_szContentString = NULL ;

	///////////////////////////////////////////////////////
	// First handle HTTP variables set using the GET method
	///////////////////////////////////////////////////////

	if ( (_szQueryString = getenv("QUERY_STRING")) == NULL)
	{
		// If you come here then it means that the Query String was empty
		_bQueryString = FALSE ;
	}

	_bQueryString = TRUE ;

	PCHAR	tmpQueryString = NULL, token = NULL, szVarName, szVarValue ;
	CHAR	seps[10] ;
	DWORD	i = 0, dwVarName = 0, dwVarValue = 0 ;

	seps[0] = '&' ;
	seps[1] = '\0' ;

	if ( _szQueryString )
	{
		tmpQueryString = _szQueryString ;
		dwQueryString = strlen(_szQueryString) ;

		while ( (DWORD)(tmpQueryString-_szQueryString) <= dwQueryString )
		{
			dwVarName = dwVarValue = 0 ;

			token = strtok(tmpQueryString, seps) ;
			if (token == NULL)
				break ;

			dwVarName = strchr(tmpQueryString, '=')-tmpQueryString ;
			szVarName = (PCHAR) new char[dwVarName+1];
			strncpy(szVarName, tmpQueryString, dwVarName) ;
			szVarName[dwVarName] = '\0' ;
			szVarName = URLDecodeAlloc(szVarName) ;

			if ( _bFirstVar == TRUE )
			{
				_hvAllHttpVars = (PHTTPVARS) new char[sizeof(HTTPVARS)];
				_hvAllHttpVars->name = szVarName ;
				dwVarValue = strlen(tmpQueryString+dwVarName+1) ;
				szVarValue = (PCHAR) new char[dwVarValue+1];
				strcpy(szVarValue, tmpQueryString+dwVarName+1) ;
				szVarValue = URLDecodeAlloc(szVarValue) ;
				_hvAllHttpVars->value = szVarValue ;
				_hvAllHttpVars->next = NULL ;

				currentHttpVar = _hvAllHttpVars ;
				_VarCount++ ;
				_bFirstVar = FALSE ;
			}
			else
			{
				currentHttpVar->next = (PHTTPVARS) new char[sizeof(HTTPVARS)];
				currentHttpVar = currentHttpVar->next ;
				currentHttpVar->next = NULL ;
				currentHttpVar->name = szVarName ;
				dwVarValue = strlen(tmpQueryString+dwVarName+1) ;
				szVarValue = (PCHAR) new char[dwVarValue+1];
				strcpy(szVarValue, tmpQueryString+dwVarName+1) ;
				szVarValue = URLDecodeAlloc(szVarValue) ;
				currentHttpVar->value = szVarValue ;
				_VarCount++ ;
			}
			tmpQueryString += dwVarName+2+dwVarValue ;
		}
	}

	PHTTPVARS tmphvars = _hvAllHttpVars ;

	///////////////////////////////////////////////////////
	// Now handle the variables set using the POST method
	///////////////////////////////////////////////////////


	PCHAR   pBuffer=NULL;
	DWORD	dwContentLength=0;

	pBuffer=getenv("CONTENT_LENGTH");
	

	if(pBuffer!=NULL)
		dwContentLength = atoi(pBuffer) ;

	PCHAR	tmpContentString = NULL ;

	
	if ( dwContentLength == 0 )
	{
		_bContentString = FALSE ;
		return ;
	}

	_bContentString = TRUE ;

	if ( dwContentLength )
	{
		_szContentString = (PCHAR)new char[dwContentLength+1] ;

		fread(_szContentString, 1, dwContentLength, stdin) ;
		_szContentString[dwContentLength] = '\0' ;

		
		tmpContentString = _szContentString ;

		while ( (DWORD)(tmpContentString-_szContentString) <= dwContentLength )
		{

			dwVarName = dwVarValue = 0 ;

			token = strtok(tmpContentString, seps) ;
			if (token == NULL)
				break ;

			dwVarName = strchr(tmpContentString, '=')-tmpContentString ;
			szVarName = (PCHAR) new char[dwVarName+1] ;
			strncpy(szVarName, tmpContentString, dwVarName) ;
			szVarName[dwVarName] = '\0' ;
			szVarName = URLDecodeAlloc(szVarName) ;

			if ( _bFirstVar == TRUE )
			{
				_hvAllHttpVars = (PHTTPVARS) new char[sizeof(HTTPVARS)] ;
				_hvAllHttpVars->name = szVarName ;
				dwVarValue = strlen(tmpContentString+dwVarName+1) ;
				szVarValue = (PCHAR) new char[(dwVarValue+1)] ;
				strcpy(szVarValue, tmpContentString+dwVarName+1) ;
				szVarValue = URLDecodeAlloc(szVarValue) ;
				_hvAllHttpVars->value = szVarValue ;
				_hvAllHttpVars->next = NULL ;

				currentHttpVar = _hvAllHttpVars ;
				_VarCount++ ;
				_bFirstVar = FALSE ;
			}
			else
			{
				currentHttpVar->next = (PHTTPVARS) new char[sizeof(HTTPVARS)] ;
				currentHttpVar = currentHttpVar->next ;
				currentHttpVar->next = NULL ;
				currentHttpVar->name = szVarName ;

				dwVarValue = strlen(tmpContentString+dwVarName+1) ;
				szVarValue = (PCHAR) new char[(dwVarValue+1)] ;
				strcpy(szVarValue, tmpContentString+dwVarName+1) ;
				szVarValue = URLDecodeAlloc(szVarValue) ;
				currentHttpVar->value = szVarValue ;

				_VarCount++ ;
			}
			tmpContentString += dwVarName+2+dwVarValue ;
		}
	}
}

CHttp::~CHttp()
{
	PHTTPVARS	tmpVar, nextVar ;

	tmpVar = _hvAllHttpVars ;

	while ( tmpVar )
	{
		nextVar = tmpVar->next ;
		delete tmpVar;
		tmpVar = nextVar ;
	}
}


PCHAR CHttp::getVar(PCHAR szVarName)
{
	PHTTPVARS	tmpVar ;
	PCHAR		szRetVarVal = NULL ;

	tmpVar = _hvAllHttpVars ;

	while ( tmpVar )
	{
		if ( strcmp(tmpVar->name, szVarName) == 0 )
		{
			szRetVarVal = (PCHAR) new char[strlen(tmpVar->value)+1];
			strcpy(szRetVarVal, tmpVar->value) ;

			break ;
		}

		tmpVar = tmpVar->next ;
	}

	return szRetVarVal ;
}

PCHAR CHttp::URLDecodeAlloc(const char *pszBuf)
{
  unsigned char *pbOut ;
  int nbytesIn = strlen(pszBuf) + 1;
  char pszTmp[3] ;
  int nTmp ;
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
      if( sscanf(pszTmp, "%x", &nTmp) != 1 ) return NULL ;
      pbOut[j] = (unsigned char)nTmp ;
      i += 2 ;
      break ;
    default:
      pbOut[j] = pszBuf[i] ;
      break ;
    }
  }
  
  return (PCHAR)pbOut;
}

PCHAR CHttp::URLEncodeAlloc(const unsigned char* buffer, int n)
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

void CHttp::PostError(PCHAR szFDFfile, DWORD dwErrorCode, DWORD dwWinErrorCode, PCHAR szOperation)
{
	printf ("Content-Type: text/plain\n") ;
	printf ("Pragma: no cache\n") ;
	printf ("Expires: -1\n") ;
	printf ("Cache-control: no cache\n\n\n") ;

	sprintf(_szErrorString, "<HTML>\n") ;

	sprintf(_szErrorString, "%s<HEAD>\n", _szErrorString) ;

	sprintf(_szErrorString, "%s<SCRIPT Language=JavaScript>\n", _szErrorString) ;
	sprintf(_szErrorString, "%s<!--\n", _szErrorString) ;

	sprintf(_szErrorString, "%s  self.location=\"../softbounce.exe?", _szErrorString) ;
	sprintf(_szErrorString, "%sform_file=%s&", _szErrorString, szFDFfile) ;
	sprintf(_szErrorString, "%serrorCode=%08x&", _szErrorString, dwErrorCode) ;
	sprintf(_szErrorString, "%swinerrorcode=%08x&", _szErrorString, dwWinErrorCode) ;
	sprintf(_szErrorString, "%soperation=%s&", _szErrorString, szOperation) ;
	sprintf(_szErrorString, "%sshowError=\" ;\n", _szErrorString) ;

	sprintf(_szErrorString, "%s-->\n", _szErrorString) ;
	sprintf(_szErrorString, "%s</SCRIPT>\n", _szErrorString) ;

	sprintf(_szErrorString, "%s</HEAD>\n", _szErrorString) ;

	sprintf(_szErrorString, "%s<BODY>\n", _szErrorString) ;
	sprintf(_szErrorString, "%s</BODY>\n", _szErrorString) ;
	sprintf(_szErrorString, "%s</HTML>\n", _szErrorString) ;

	printf ("<HTML>\n") ;
	printf ("<BODY>\n") ;
	printf("%s", _szErrorString) ;
	printf ("</BODY>\n") ;
	printf ("</HTML>\n") ;
	
}
