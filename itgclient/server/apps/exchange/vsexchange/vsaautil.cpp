/* $Id: vsaautil.cpp,v 1.1.6.1 2003/06/06 22:46:28 npaul Exp $       */
/* $Revision: 1.1.6.1 $ */

/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

/*--------------------------------------------------------------------\
 This file contains common utility functions used for Automated 
 Authentication modules.

\--------------------------------------------------------------------*/

/* Standard header files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#ifndef WIN32
#include <unistd.h>
#else
#include <windows.h>
#include <process.h>
#include <io.h>
#endif

/* Verisign AA support header files */

#include "vsverify.h"
#include "vsutil.h"
#include "vsaautil.h"

extern FILE    *logFP; // defined in vslog.cpp

/* Function implementation */

void *VSAAUTIL_Malloc( size_t size )
{
    return malloc(size);
}

void *VSAAUTIL_Calloc( size_t num, size_t size )
{
    return calloc(num, size);
}

void *VSAAUTIL_Realloc( void *memblock, size_t size )
{
    return realloc(memblock, size);
}

void VSAAUTIL_Free( void *memblock )
{
    if(memblock) free(memblock);
}

char *VSAAUTIL_Strdup(const char* s)
{
    if(!s) return NULL;

    return strdup(s);
}

int VSAAUTIL_StrCaseCmp(const char *s1, const char *s2)
{
  if ( s1 == NULL && s2 == NULL ) return 0;
  if ( s1 == NULL || s2 == NULL ) return 1;
  if ( strlen(s1) != strlen(s2) ) return 1;

  return VSAAUTIL_StrnCaseCmp(s1, s2, strlen(s1));
}

int VSAAUTIL_StrnCaseCmp(const char *s1, const char *s2, size_t len)
{
  size_t i;
  for ( i=0; i<len; i++, s1++, s2++) {
    if ( *s1 != *s2 ) {
       // add 32 to make *s to the lower case
       if (  ( *s1 >= 'A' && *s1 <= 'Z' && ((*s1 + 32) == *s2) )  ||
             ( *s2 >= 'A' && *s2 <= 'Z' && ((*s2 + 32) == *s1) ) )
          continue;
       else
          return 1;
    }
  }
  return 0; 
}

VSAA_STATUS 
VSAAUTIL_AppendCfgAttrEntry(
   VSAACfgAttrList  **cfgListPtr, 
   const char       *pszValue)
{
    VSAACfgAttrList* tmpEntryPtr, *attrEntryPtr;

    VSAAUTIL_TRACE("VSAAUTIL_AppendCfgAttrEntry()");

    if(!cfgListPtr || !pszValue) {
        return VSAA_INTERNAL_ERROR;
    }

    attrEntryPtr = (VSAACfgAttrList*)VSAAUTIL_Malloc(sizeof(VSAACfgAttrList));
    if(!attrEntryPtr) {
        return VSAA_OUT_OF_MEMORY;
    } else {
        attrEntryPtr->next = NULL;
        attrEntryPtr->pszValue = VSAAUTIL_Strdup(pszValue);
        if(!attrEntryPtr->pszValue) {
            VSAAUTIL_Free(attrEntryPtr);
            return VSAA_OUT_OF_MEMORY;
        }
    }
    
    if(!*cfgListPtr)
        *cfgListPtr = attrEntryPtr;
    else {
        tmpEntryPtr = *cfgListPtr;
        while(tmpEntryPtr->next != NULL)
            tmpEntryPtr = tmpEntryPtr->next;

        tmpEntryPtr->next = attrEntryPtr;        
    }
    
    return VSAA_SUCCESS;
}

VSAA_STATUS 
VSAAUTIL_AppendCfgNVPairEntry(
   VSAACfgNVPairList **cfgListPtr, 
   const char        *pszName,
   const char        *pszValue)
{
    VSAACfgNVPairList* tmpEntryPtr, *attrEntryPtr;

    VSAAUTIL_TRACE("VSAAUTIL_AppendCfgNVPairEntry()");

    if(!cfgListPtr || !pszName || !pszValue) {
        return VSAA_INTERNAL_ERROR;
    }

    attrEntryPtr = (VSAACfgNVPairList*)VSAAUTIL_Malloc(sizeof(VSAACfgNVPairList));
    if(!attrEntryPtr) {
        return VSAA_OUT_OF_MEMORY;
    } else {
        attrEntryPtr->next = NULL;
        attrEntryPtr->pszName = VSAAUTIL_Strdup(pszName);
        if(!attrEntryPtr->pszName) {
            VSAAUTIL_Free(attrEntryPtr);
            return VSAA_OUT_OF_MEMORY;
        }

        attrEntryPtr->pszValue = VSAAUTIL_Strdup(pszValue);
        if(!attrEntryPtr->pszValue) {
            VSAAUTIL_Free(attrEntryPtr->pszName);
            VSAAUTIL_Free(attrEntryPtr);
            return VSAA_OUT_OF_MEMORY;
        }
    }
    
    if(!*cfgListPtr)
        *cfgListPtr = attrEntryPtr;
    else {
        tmpEntryPtr = *cfgListPtr;
        while(tmpEntryPtr->next != NULL)
            tmpEntryPtr = tmpEntryPtr->next;

        tmpEntryPtr->next = attrEntryPtr;        
    }
    
    return VSAA_SUCCESS;
}

VSAA_STATUS 
VSAAUTIL_AppendCfgNVTripleEntry(
   VSAACfgNVTripleList  **cfgListPtr, 
   const char           *pszName,
   const char           *pszValue,
   int                  n)
{
    VSAACfgNVTripleList* tmpEntryPtr, *attrEntryPtr;

    VSAAUTIL_TRACE("VSAAUTIL_AppendCfgNVTripleEntry()");

    if(!cfgListPtr) {
        return VSAA_INTERNAL_ERROR;
    }

    attrEntryPtr = (VSAACfgNVTripleList*)VSAAUTIL_Malloc(sizeof(VSAACfgNVTripleList));
    if(!attrEntryPtr) 
        return VSAA_OUT_OF_MEMORY;
    else {
        attrEntryPtr->next = NULL;
        attrEntryPtr->pszName = VSAAUTIL_Strdup(pszName);
        if(!attrEntryPtr->pszName) {
            VSAAUTIL_Free(attrEntryPtr);
            return VSAA_OUT_OF_MEMORY;
        }

        attrEntryPtr->pszValue = VSAAUTIL_Strdup(pszValue);
        if(!attrEntryPtr->pszValue) {
            VSAAUTIL_Free(attrEntryPtr->pszName);
            VSAAUTIL_Free(attrEntryPtr);
            return VSAA_OUT_OF_MEMORY;
        }

        attrEntryPtr->nValue = n;
    }
    
    if(!*cfgListPtr)
        *cfgListPtr = attrEntryPtr;
    else {
        tmpEntryPtr = *cfgListPtr;
        while(tmpEntryPtr->next != NULL)
            tmpEntryPtr = tmpEntryPtr->next;

        tmpEntryPtr->next = attrEntryPtr;        
    }
    
    return VSAA_SUCCESS;
}

void
VSAAUTIL_FreeCfgAttrList(VSAACfgAttrList *cfgListPtr)
{
    VSAACfgAttrList *tmpListPtr = cfgListPtr;
    while(tmpListPtr != NULL) {
        cfgListPtr = tmpListPtr->next;
        VSAAUTIL_Free(tmpListPtr->pszValue);
        VSAAUTIL_Free(tmpListPtr);
        tmpListPtr = cfgListPtr;
    }
}

void
VSAAUTIL_FreeCfgNVPairList(VSAACfgNVPairList *cfgListPtr)
{
    VSAACfgNVPairList *tmpListPtr = cfgListPtr;
    while(tmpListPtr != NULL) {
        cfgListPtr = tmpListPtr->next;
        VSAAUTIL_Free(tmpListPtr->pszName);
        VSAAUTIL_Free(tmpListPtr->pszValue);
        VSAAUTIL_Free(tmpListPtr);
        tmpListPtr = cfgListPtr;
    }
}

void
VSAAUTIL_FreeCfgNVTripleList(VSAACfgNVTripleList *cfgListPtr)
{
    VSAACfgNVTripleList *tmpListPtr = cfgListPtr;
    while(tmpListPtr != NULL) {
        cfgListPtr = tmpListPtr->next;
        VSAAUTIL_Free(tmpListPtr->pszName);
        VSAAUTIL_Free(tmpListPtr->pszValue);
        VSAAUTIL_Free(tmpListPtr);
        tmpListPtr = cfgListPtr;
    }
}

/* assume pszCfg has been trimmed */

VSAA_STATUS 
VSAAUTIL_ExtractAttrNameValues(
    char**                 pszName, 
    VSAACfgAttrList**      valueListPtr,
    const char*            pszCfg)
{
    VSAA_STATUS status = VSAA_SUCCESS;
    
    int   i, l;
    char pszValue[MAX_CFG_VALUE_LENGTH];
    const char *pszValueBegin, *pszValueEnd;
    VSAACfgAttrList *tmpListPtr = NULL, *tmpListCurrPtr = NULL, *attrEntryPtr = NULL;

    VSAAUTIL_TRACE("VSAAUTIL_ExtractAttrNameValues()");

    if(pszName == NULL || valueListPtr == NULL)
        return VSAA_INTERNAL_ERROR;

    *pszName = NULL;
    *valueListPtr = NULL;

    if(pszCfg == NULL || *pszCfg == 0)
        return status;

    l = strlen(pszCfg);

    i = 0;
    while(pszCfg[i] && !isspace(pszCfg[i++]));

    /* If only a name is given without value, just get name and return. */
         
    if(!isspace(pszCfg[i-1])) {
        *pszName = (char*) VSAAUTIL_Strdup(pszCfg);
        if(!*pszName)
            status = VSAA_OUT_OF_MEMORY;
        
        return status;
    }

    *pszName = (char*) VSAAUTIL_Malloc(i);
    if(!*pszName)
        return VSAA_OUT_OF_MEMORY;
    else {
        strncpy(*pszName, pszCfg, i-1);
        (*pszName)[i-1] = 0;
    }
    
    /* find all values */

    pszValueBegin = pszCfg + i;

    do {
        while(isspace(*pszValueBegin)) 
            pszValueBegin++;

        if(*pszValueBegin == CFG_BEGIN_SINGLE_VALUE) {
            
            pszValueEnd = pszValueBegin;
            do {
                pszValueEnd = strchr(pszValueEnd, CFG_END_SINGLE_VALUE);            
                if(pszValueEnd == NULL) {
                                        
                    VSAAUTIL_Free(*pszName);
                    VSAAUTIL_FreeCfgAttrList(tmpListPtr);
                    return VSAA_BAD_CONFIG_FILE;

                } else if(pszValueEnd[1] == 0 || isspace(pszValueEnd[1])) {

                    strncpy(pszValue, pszValueBegin+1, pszValueEnd-pszValueBegin-1);
                    pszValue[pszValueEnd-pszValueBegin-1] = 0;

                    VSAAUTIL_AppendCfgAttrEntry(&tmpListPtr, pszValue);
                    pszValueBegin = pszValueEnd + 1;
                    break;

                } else 
                    pszValueEnd ++;
            } while(*pszValueEnd != 0);

        } else if(*pszValueBegin) {
            
            pszValueEnd = pszValueBegin;
            while(*pszValueEnd && !isspace(*pszValueEnd)) 
                pszValueEnd++;
            
            strncpy(pszValue, pszValueBegin, pszValueEnd-pszValueBegin);
            pszValue[pszValueEnd-pszValueBegin] = 0;

            VSAAUTIL_AppendCfgAttrEntry(&tmpListPtr, pszValue);
                    
            pszValueBegin = pszValueEnd;            

        }
    } while(*pszValueBegin);

    *valueListPtr = tmpListPtr;

    return VSAA_SUCCESS;
}

int  
VSAAUTIL_Contain(VSAACfgAttrList* cfgAttrListPtr, const char* attr)
{
    if(attr == NULL || cfgAttrListPtr == NULL)
        return 0;

    while(cfgAttrListPtr != NULL && cfgAttrListPtr->pszValue != NULL && *cfgAttrListPtr->pszValue != 0) {
        if(!strcmp(cfgAttrListPtr->pszValue, attr))
            return 1;
        
        cfgAttrListPtr = cfgAttrListPtr->next;
    }

    return 0;
}

int
VSAAUTIL_CountAttr(VSAACfgAttrList* cfgAttrListPtr)
{
    int cnt = 0;
    while(cfgAttrListPtr != NULL && cfgAttrListPtr->pszValue != NULL && *cfgAttrListPtr->pszValue != 0) {
        cnt ++;
        cfgAttrListPtr = cfgAttrListPtr->next;
    }

    return cnt;
}

VSAA_STATUS
VSAAUTIL_ReadEntryLine(
    char         s[],
    unsigned int n,
    FILE         *fp)
{
    int i, l, k;
    char *tmpBuf;
    
    if(n <= 0 || !fp) {
        s[0] = 0;
        return VSAA_SUCCESS;
    }

    s[0] = 0;

    if(fgets(s, n, fp)) {
        tmpBuf = s;
        l = n;
        do {
            i = strlen(tmpBuf);
            if(tmpBuf[i-1] != '\n' && !feof(fp)) {
                return VSAA_ERR_CFG_FILE_LINE_TOO_LONG;
            } else {
                k = i-2;
                while(k>=0 && isspace(tmpBuf[k])) k--;
                if(k>=0 && tmpBuf[k] == '\\') {
                    tmpBuf = &tmpBuf[k];
                    l -= k+1;
                    fgets(tmpBuf, l, fp);
                } else {
                    break;
                }
            }
        } while(l>0);            
    }

    return VSAA_SUCCESS;
}

/*
 * Find the name-value pair with matching pszName in the input
 * Return NULL if not found
 */

const char*
VSAAUTIL_FindUserInputValue(
    const char      *pszName, 
    size_t          nameLen,
	const VSAA_NAME userInput[])
{
	int i;

	for (i=0; userInput[i].pszName != NULL; i++)
	{
		if (nameLen == strlen(userInput[i].pszName))
		{
			if (!strncmp(pszName, userInput[i].pszName, nameLen)) /* if equal */
				return userInput[i].pszValue;           /* return the value */
		}
	}
	return NULL;
}

const char* 
VSAAUTIL_FindFDFAttrName(
    const char              *pszAttr, 
    const VSAACfgNVPairList *mapAttrListPtr)
{
    VSAAUTIL_TRACE("VSAAUTIL_FindFDFAttrName()");

    if (!pszAttr || !*pszAttr) {
        return NULL;
    }

    while(mapAttrListPtr != NULL && *mapAttrListPtr->pszValue) {
        if( VSAAUTIL_StrCaseCmp(mapAttrListPtr->pszValue, pszAttr) == 0 )
            return mapAttrListPtr->pszName;
        
        mapAttrListPtr = mapAttrListPtr->next;
    }

    return NULL;
}

void
VSAAUTIL_PrintCfgAttrList(
    FILE                  *fp, 
    const VSAACfgAttrList *attrListPtr)
{
    int i = 0;

    if(fp) {
        while(attrListPtr && attrListPtr->pszValue) {
            if(i == 0)
                VS_DataLog((char *)"CFG     %s ", attrListPtr->pszValue);
            else
                VS_DataLog((char *)" %s ", attrListPtr->pszValue);

            attrListPtr = attrListPtr->next;
            i++;
        }
        VS_DataLog((char *)"\n");
    }
}

void
VSAAUTIL_PrintCfgNVPairList(
    FILE                    *fp, 
    const VSAACfgNVPairList *attrListPtr)
{
    if(fp) {
        while(attrListPtr && attrListPtr->pszName) {
            VS_DataLog((char *)"CFG     %s %s\n", attrListPtr->pszName, attrListPtr->pszValue);
            attrListPtr = attrListPtr->next;
        }
    }
}

void
VSAAUTIL_PrintCfgNVTripleList(
    FILE                      *fp, 
    const VSAACfgNVTripleList *attrListPtr)
{
    if(fp) {
        while(attrListPtr && attrListPtr->pszName) {
            VS_DataLog((char *)"CFG     %s %s %d\n", attrListPtr->pszName, attrListPtr->pszValue, attrListPtr->nValue);
            attrListPtr = attrListPtr->next;
        }
    }
}

VSAACfgAttrList*
GetLogHideAttrList(const char* attrListString)
{
    char* next = NULL;
    char* attr = NULL, *head = NULL;
   
    VSAACfgAttrList* attrListPtr = NULL;

    if( attrListString != NULL   && 
        strlen(attrListString) > 0
      ) 
    {
        attr = (char*)strdup(attrListString);
        if(attr == NULL) {
            return NULL;
        }

        head = attr;

        do {
            next = strchr(attr, CFG_ATTR_LIST_DELIMITER);
            if(next != NULL) {
                *next = 0;
                next ++;
            } 
            VSAAUTIL_AppendCfgAttrEntry(&attrListPtr, attr);
            attr = next;
        } while(attr != NULL);

        free(head);
    }

    return attrListPtr;
}

void DumpPublicData(const char *msg, const VSAA_NAME list[], VSAACfgAttrList* hideAttrList)
{
    int i;
    char fakeString[1024]="";
    int  len = 0;
    time_t now = time(NULL);
    
    if ((list == NULL) || (logFP == NULL))
        return;
    VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char*)"%s at %s", msg, ctime(&now));
    for (i=0; list[i].pszName; i++)
    {
        if(!VSAAUTIL_Contain(hideAttrList, list[i].pszName)) {
            VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char *)"%s=[%s]", list[i].pszName,
                list[i].pszValue);
        } else {
            // fake string only print four *
            len = 4;
            memset(fakeString, '*', len);
            fakeString[len] = 0;
            VSAA_Log(VS_LOG_DEBUG, __LINE__, __FILE__, (char *)"%s=[%s]", list[i].pszName, fakeString);
        }
    }
}
