// Http.cpp: implementation of the Http class.
//
//////////////////////////////////////////////////////////////////////

#include "Http.h"
#include <stdlib.h>
#include <stdio.h>

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
			szVarName = (PCHAR) malloc(dwVarName+1) ;
			strncpy(szVarName, tmpQueryString, dwVarName) ;
			szVarName[dwVarName] = '\0' ;
			szVarName = HTMLDecode(szVarName) ;

			if ( _bFirstVar == TRUE )
			{
				_hvAllHttpVars = (PHTTPVARS) malloc(sizeof(HTTPVARS)) ;
				_hvAllHttpVars->name = szVarName ;
				dwVarValue = strlen(tmpQueryString+dwVarName+1) ;
				szVarValue = (PCHAR) malloc(dwVarValue+1) ;
				strcpy(szVarValue, tmpQueryString+dwVarName+1) ;
				szVarValue = HTMLDecode(szVarValue) ;
				_hvAllHttpVars->value = szVarValue ;
				_hvAllHttpVars->next = NULL ;

				currentHttpVar = _hvAllHttpVars ;
				_VarCount++ ;
				_bFirstVar = FALSE ;
			}
			else
			{
				currentHttpVar->next = (PHTTPVARS) malloc(sizeof(HTTPVARS)) ;
				currentHttpVar = currentHttpVar->next ;
				currentHttpVar->next = NULL ;
				currentHttpVar->name = szVarName ;
				dwVarValue = strlen(tmpQueryString+dwVarName+1) ;
				szVarValue = (PCHAR) malloc(dwVarValue+1) ;
				strcpy(szVarValue, tmpQueryString+dwVarName+1) ;
				szVarValue = HTMLDecode(szVarValue) ;
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
		_szContentString = (PCHAR)malloc(dwContentLength+1) ;

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
			szVarName = (PCHAR) malloc(dwVarName+1) ;
			strncpy(szVarName, tmpContentString, dwVarName) ;
			szVarName[dwVarName] = '\0' ;
			szVarName = HTMLDecode(szVarName) ;

			if ( _bFirstVar == TRUE )
			{
				_hvAllHttpVars = (PHTTPVARS) malloc(sizeof(HTTPVARS)) ;
				_hvAllHttpVars->name = szVarName ;
				dwVarValue = strlen(tmpContentString+dwVarName+1) ;
				szVarValue = (PCHAR) malloc(dwVarValue+1) ;
				strcpy(szVarValue, tmpContentString+dwVarName+1) ;
				szVarValue = HTMLDecode(szVarValue) ;
				_hvAllHttpVars->value = szVarValue ;
				_hvAllHttpVars->next = NULL ;

				currentHttpVar = _hvAllHttpVars ;
				_VarCount++ ;
				_bFirstVar = FALSE ;
			}
			else
			{
				currentHttpVar->next = (PHTTPVARS) malloc(sizeof(HTTPVARS)) ;
				currentHttpVar = currentHttpVar->next ;
				currentHttpVar->next = NULL ;
				currentHttpVar->name = szVarName ;

				dwVarValue = strlen(tmpContentString+dwVarName+1) ;
				szVarValue = (PCHAR) malloc(dwVarValue+1) ;
				strcpy(szVarValue, tmpContentString+dwVarName+1) ;
				szVarValue = HTMLDecode(szVarValue) ;
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
		free(tmpVar) ;
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
			szRetVarVal = (PCHAR) malloc(strlen(tmpVar->value)+1) ;
			strcpy(szRetVarVal, tmpVar->value) ;

			break ;
		}

		tmpVar = tmpVar->next ;
	}

	return szRetVarVal ;
}

PCHAR	CHttp::HTMLDecode(PCHAR input)
{
	PCHAR	szDecodedString = NULL ;
	DWORD	inputIndex = 0, outputIndex = 0 ;

	szDecodedString = (PCHAR) malloc(strlen(input)+1) ;
	
	while(input[inputIndex] != NULL )
	{
		if ( input[inputIndex] != '%' )
			szDecodedString[outputIndex++] = input[inputIndex++] ;
		else
		{
			inputIndex++ ;

			CHAR	szTmp[4], tmpChar ;
			szTmp[0] = input[inputIndex++] ;
			szTmp[1] = input[inputIndex++] ;
			szTmp[2] = '\0' ;
			sscanf(szTmp, "%x", &tmpChar) ;
			szDecodedString[outputIndex++] = tmpChar ;
		}
	}
	szDecodedString[outputIndex] = '\0' ;

/*
	if ( input )
		free (input) ;
*/
	return(szDecodedString) ;
}

