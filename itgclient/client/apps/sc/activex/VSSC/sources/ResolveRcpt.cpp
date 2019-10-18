// ResolveRcpt.cpp : Implementation of CVSSCApp and DLL registration.

#include "stdafx.h"
//#include "VSSC.h"
#include "ResolveRcpt.h"

/////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CResolveRcpt::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IResolveRcpt,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	} 
	return S_FALSE;
}
