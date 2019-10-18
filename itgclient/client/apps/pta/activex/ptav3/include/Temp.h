// Temp.h: Definition of the Temp class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEMP_H__F1432F84_DDA9_11D3_A428_D1A369CA484F__INCLUDED_)
#define AFX_TEMP_H__F1432F84_DDA9_11D3_A428_D1A369CA484F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Temp

class Temp : 
	public IDispatchImpl<ITemp, &IID_ITemp, &LIBID_PTAV3Lib>, 
	public IDispatchImpl<ITempInt2, &IID_ITempInt2, &LIBID_PTAV3Lib>, 
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<Temp,&CLSID_Temp>
{
public:
	Temp() {}
BEGIN_COM_MAP(Temp)
	COM_INTERFACE_ENTRY2(IDispatch, ITemp)
	COM_INTERFACE_ENTRY(ITemp)
	COM_INTERFACE_ENTRY(ITempInt2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(Temp) 
// Remove the comment from the line above if you don't want your object to 
// support aggregation. 

DECLARE_REGISTRY_RESOURCEID(IDR_Temp)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITemp

// ITempInt2
public:
};

#endif // !defined(AFX_TEMP_H__F1432F84_DDA9_11D3_A428_D1A369CA484F__INCLUDED_)
