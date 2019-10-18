/////////////////////////////////////////////////////////////////////////////
//
//  File:           CHSTRARR.H
//
//  Description:    Utility library version of MFC CHStringArray
//
// Copyright 1998 Microsoft Corporation
//
/////////////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _CHStringArray_
#define _CHStringArray_

#include <polarity.h>

class POLARITY CHStringArray 
{
    public:
	    CHStringArray();
	    ~CHStringArray();

        // Attributes
        int GetSize() const 	        { return m_nSize; }
    	int GetUpperBound() const       { return m_nSize-1; }
	    void SetSize(int nNewSize, int nGrowBy = -1);

        // Operations
        // Clean up
    	void FreeExtra();
	    void RemoveAll()            	{ SetSize(0); }

    	// Accessing elements
	    CHString GetAt(int nIndex) const{ assert(nIndex >= 0 && nIndex < m_nSize);
		                                  return m_pData[nIndex]; }

	    void SetAt(int nIndex, LPCTSTR newElement){ 
                                          assert(nIndex >= 0 && nIndex < m_nSize);
		                                  m_pData[nIndex] = newElement; }

	    CHString& ElementAt(int nIndex)	{ assert(nIndex >= 0 && nIndex < m_nSize);
		                                  return m_pData[nIndex]; }


    	// Direct Access to the element data (may return NULL)
    	const CHString* GetData() const	{ return (const CHString*)m_pData; }
	    CHString* GetData()             { return (CHString*)m_pData; }

	    // Potentially growing the array
	    void SetAtGrow(int nIndex, LPCTSTR newElement);
	    int Add(LPCTSTR newElement) 	{ int nIndex = m_nSize;
                                      	  SetAtGrow(nIndex, newElement);
		                                  return nIndex; }
	    int Append(const CHStringArray& src);
	    void Copy(const CHStringArray& src);

	    // overloaded operator helpers
	    CHString operator[](int nIndex) const { return GetAt(nIndex); }
	    CHString& operator[](int nIndex)      { return ElementAt(nIndex); }

	    // Operations that move elements around
	    void InsertAt(int nIndex, LPCTSTR newElement, int nCount = 1);
	    void RemoveAt(int nIndex, int nCount = 1);
	    void InsertAt(int nStartIndex, CHStringArray* pNewArray);

        // Implementation

    protected:
	    CHString* m_pData;      // the actual array of data
	    int m_nSize;            // # of elements (upperBound - 1)
	    int m_nMaxSize;         // max allocated
	    int m_nGrowBy;          // grow amount
                            	// local typedefs for class templates
	    typedef CHString BASE_TYPE;
	    typedef LPCTSTR BASE_ARG_TYPE;
};
////////////////////////////////////////////////////////////////////////////
#endif
