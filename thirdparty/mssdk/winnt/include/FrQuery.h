//
// FRQuery.h -- query support classes
//
// Copyright 1998 Microsoft Corporation
//
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _FRAMEWORK_QUERY_H_
#define _FRAMEWORK_QUERY_H_
#include <sql_1.h>
#include <comdef.h>
#include <vector>

class POLARITY CFrameworkQuery
{
	public:
		CFrameworkQuery();
		~CFrameworkQuery();

		// Finds out if a particular field was requested by the query.  Only 
		// meaningful if we are in ExecQueryAsync and the query has been 
		// sucessfully parsed.
		bool IsPropertyRequired(const CHString& propName);

		// Gets the class name from the query.  Only meaningful if we are
		// in ExecQueryAsync and the query has been sucessfully parsed.
		BSTR GetQueryClassName(void);

		// This is a very cool routine.  Given a property name, it will return all the values
		// that the query requests in a CHStringArray.
		// Select * from win32_directory where drive = "C:" GetValuesForProp(L"Drive") -> C:
		// Where Drive = "C:" or Drive = "D:" GetValuesForProp(L"Drive") -> C:, D:
		// Where Path = "\DOS" GetValuesForProp(L"Drive") -> (empty)
		// Where Drive <> "C:" GetValuesForProp(L"Drive") -> (empty)
		HRESULT GetValuesForProp(LPCWSTR wszPropName, CHStringArray& achNames);
        // Here's an overloaded version in case client wants to pass in a vector of _bstr_t's
        HRESULT GetValuesForProp(LPCWSTR wszPropName, std::vector<_bstr_t>& vectorNames);

		// Returns a list of all the properties specified in the select statement.
		// If * is specified as one of the fields, it is returned in the same way as all
		// other properties.
		void GetRequiredProperties(CHStringArray &saProperties);

		// Boolean indicating if all properties are being requested.
		bool AllPropertiesAreRequired(void);

		// Boolean indicating if only the key properties are required.
		bool KeysOnly(void) { return m_bKeysOnly; }

		// Moves the values into the member variables.  Should never be called by users.
		HRESULT CFrameworkQuery::Init(BSTR bstrQueryFormat, BSTR bstrQuery, long lFlags);

		// Initializes the KeysOnly data member.  Should never be called by users.
		void Init2(IWbemClassObject *IClass);

	private:
		SQL_LEVEL_1_RPN_EXPRESSION *m_pLevel1RPNExpression;
		bool m_bKeysOnly;

};

#endif