
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |  
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifndef _VSAAUTIL_H_
#define _VSAAUTIL_H_

/* header files */

#include <stdio.h>
#include "vslog.h"
#include "vsutil.h"
#include "vsverify.h"

#ifdef __cplusplus
extern "C" {
#endif

/* common macro */

#define VSAA_LOG_LEVEL_NONE    0
#define VSAA_LOG_LEVEL_SIMPLE  1
#define VSAA_LOG_LEVEL_VERBOSE 2

#define MAX_CFG_NAME_LENGTH       255
#define MAX_CFG_VALUE_LENGTH      1024

#define CFG_NV_DELIMITER          ' '
#define CFG_ATTR_LIST_DELIMITER   ','
#define CFG_COMMENT_MARK          '#'
#define CFG_BEGIN_SINGLE_VALUE    '['
#define CFG_END_SINGLE_VALUE      ']'

#ifndef VSAA_ON
    #define VSAA_ON  ("ON")
    #define VSAA_OFF ("OFF")
#endif

/* common data structures */

typedef int VSAA_BOOL;
#ifndef VSAA_TRUE
    #define VSAA_TRUE  1
    #define VSAA_FALSE 0
#endif

typedef struct {
    char pszName[MAX_CFG_VALUE_LENGTH];
    char pszValue[MAX_CFG_VALUE_LENGTH];
} VSAACfgNVPair, *VSAACfgNVPairPtr;

typedef struct {
    char pszName[MAX_CFG_VALUE_LENGTH];
    char pszValue[MAX_CFG_VALUE_LENGTH];
    int  nValue;
} VSAACfgNVTriple, *VSAACfgNVTriplePtr;

typedef struct _cfg_attr_list {
    char*                  pszValue;
    struct _cfg_attr_list* next;
} VSAACfgAttrList, *VSAACfgAttrListPtr;

typedef struct _cfg_nvpair_list
{
    char*                    pszName;
    char*                    pszValue;
    struct _cfg_nvpair_list* next;
} VSAACfgNVPairList, *VSAACfgNVPairListPtr;

typedef struct _cfg_nvtriple_list
{
    char*                      pszName;
    char*                      pszValue;
    int                        nValue;
    struct _cfg_nvtriple_list* next;
} VSAACfgNVTripleList, *VSAACfgNVTripleListPtr;

/* function prototypes */

#define VSAAUTIL_TRACE(x) VSTRACE(x); 

void *VSAAUTIL_Malloc( size_t size );
void *VSAAUTIL_Calloc( size_t num, size_t size );
void *VSAAUTIL_Realloc( void *memblock, size_t size );
void VSAAUTIL_Free( void *memblock );
char *VSAAUTIL_Strdup(const char* s);
int  VSAAUTIL_StrCaseCmp(const char *s1, const char *s2);
int  VSAAUTIL_StrnCaseCmp(const char *s1, const char *s2, size_t len);

VSAA_STATUS VSAAUTIL_AppendCfgAttrEntry(VSAACfgAttrList **cfgListPtr, const char* pszValue);
VSAA_STATUS VSAAUTIL_AppendCfgNVPairEntry(VSAACfgNVPairList** cfgListPtr, const char* pszName, const char* pszValue);
VSAA_STATUS VSAAUTIL_AppendCfgNVTripleEntry(VSAACfgNVTripleList** cfgListPtr, const char* pszName, const char* pszValue, int n);

void VSAAUTIL_FreeCfgAttrList(VSAACfgAttrList *cfgListPtr);
void VSAAUTIL_FreeCfgNVPairList(VSAACfgNVPairList *cfgListPtr);
void VSAAUTIL_FreeCfgNVTripleList(VSAACfgNVTripleList *cfgListPtr);

void VSAAUTIL_PrintCfgAttrList(FILE *fp, const VSAACfgAttrList *attrListPtr);
void VSAAUTIL_PrintCfgNVPairList(FILE *fp, const VSAACfgNVPairList *attrListPtr);
void VSAAUTIL_PrintCfgNVTripleList(FILE *fp, const VSAACfgNVTripleList *attrListPtr);

int  VSAAUTIL_CountAttr(VSAACfgAttrList* cfgAttrListPtr);
VSAA_STATUS VSAAUTIL_ReadEntryLine(char s[], unsigned int n, FILE *fp);
VSAA_STATUS VSAAUTIL_ExtractAttrNameValues(char** pszName, VSAACfgAttrList** valueListPtr, const char* pszCfg);
const char* VSAAUTIL_FindUserInputValue(const char *pszName, size_t nameLen, const VSAA_NAME userInput[]);
const char* VSAAUTIL_FindFDFAttrName(const char* pszAttr, const VSAACfgNVPairList *mapAttrListPtr);

/* Check whether given attr is contained in the cfgAttrListPtr */
int  VSAAUTIL_Contain(VSAACfgAttrList* cfgAttrListPtr, const char* attr);

VSAACfgAttrList* GetLogHideAttrList(const char* attrListString);

void DumpPublicData(const char *msg, const VSAA_NAME list[], VSAACfgAttrList* hideAttrList);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* _VSAAUTIL_H */
