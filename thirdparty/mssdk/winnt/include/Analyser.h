//
// analyser.h -- query analysis support.
//
// Copyright 1998 Microsoft Corporation
//
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __WBEM_ANALYSER__H_
#define __WBEM_ANALYSER__H_

#include <windows.h>
#include <stdio.h>
#include <wbemidl.h>

#include <GenLex.h>
#include <SQLLex.h>
#include <SQL_1.h>       // SQL level 1 tokens and expressions  
#include <chstring.h>
#include <chstrarr.h>
#include <comdef.h>
#include <vector>
//#define INTERNAL    // Internal pointer is returned. Do not delete. Lifetime
//                    // is limited to that of the object.
//#define ACQUIRE     // The function acquires the pointer --- the caller may
//                    // never delete it, the object will do it.
#define DELETE_ME 
//-----------------------------


class CQueryAnalyser
{
public:
    static HRESULT WINAPI GetNecessaryQueryForProperty(
                                       IN SQL_LEVEL_1_RPN_EXPRESSION* pExpr,
                                       IN LPCWSTR wszPropName,
                                DELETE_ME SQL_LEVEL_1_RPN_EXPRESSION*& pNewExpr);
    static HRESULT WINAPI GetValuesForProp(SQL_LEVEL_1_RPN_EXPRESSION* pExpr,
                            LPCWSTR wszPropName, CHStringArray& awsVals);
    // overloaded version in case client wants to use vector of _bstr_t's:
    static HRESULT WINAPI GetValuesForProp(SQL_LEVEL_1_RPN_EXPRESSION* pExpr,
                            LPCWSTR wszPropName, std::vector<_bstr_t>& vectorVals);

protected:
    static BOOL WINAPI IsTokenAboutProperty(
                                       IN SQL_LEVEL_1_TOKEN& Token,
                                       IN LPCWSTR wszPropName);
    static void WINAPI AppendQueryExpression(
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pDest,
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pSource);
    static HRESULT WINAPI AndQueryExpressions(
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pFirst,
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pSecond,
                                OUT SQL_LEVEL_1_RPN_EXPRESSION* pNew);
    static HRESULT WINAPI OrQueryExpressions(
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pFirst,
                                IN SQL_LEVEL_1_RPN_EXPRESSION* pSecond,
                                OUT SQL_LEVEL_1_RPN_EXPRESSION* pNew);
};
    
#endif
