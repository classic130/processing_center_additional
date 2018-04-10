#include "roamprefs.h"
#include "roamprefs_i.c"
#include "ptav3_i.c"
#include "vsroamprefswrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSRoamPrefs* RoamPrefs_GetInstance(IVSPTA* pPTA)
{
	IVSRoamPrefs* pRoamPrefs;
	HRESULT hr;

	hr = pPTA->get_IVSRoamPrefs((IDispatch**)&pRoamPrefs);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSRoamPrefs,(void**)&pRoamPrefs);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pRoamPrefs;
}


EXTERN_C unsigned int RoamPrefs_set_NumOfSrvrs(IVSRoamPrefs *pRoamPrefs, short NumOfSrvrs)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pRoamPrefs != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = NumOfSrvrs;
	hr = pRoamPrefs->put_NumOfSrvrs(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear(&vtName);
	return retVal;
}


EXTERN_C short RoamPrefs_get_NumOfSrvrs (IVSRoamPrefs *pRoamPrefs)
{
	HRESULT hr;
	VARIANT varNumOfSrvrs;
	short NumOfSrvrs;

	assert(pRoamPrefs != NULL);

	hr = pRoamPrefs->get_NumOfSrvrs(&varNumOfSrvrs);
	_lastErrCode = hr;

	if(hr!=S_OK)
		NumOfSrvrs = -1;
	else
		if (varNumOfSrvrs.vt != VT_I2)
			NumOfSrvrs = -1;
		else
			NumOfSrvrs = varNumOfSrvrs.iVal;

	VariantClear(&varNumOfSrvrs);

	return NumOfSrvrs;
}

EXTERN_C unsigned int RoamPrefs_set_StorageSrvr(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pRoamPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pRoamPrefs->put_StorageSrvr(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* RoamPrefs_get_StorageSrvr (IVSRoamPrefs *pRoamPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pRoamPrefs != NULL);

	//VariantInit (&var);
	hr = pRoamPrefs->get_StorageSrvr (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int RoamPrefs_set_RoamingServers (IVSRoamPrefs *pRoamPrefs, 
													wchar_t** stringArray, 
													int* nLenArray, int arraySize)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	int nIndx;
	long ix;
	VARIANT vtName;
	VARIANT *varPtr;
	SAFEARRAYBOUND rgsabound[1];
	SAFEARRAY* attrArray;

	assert(pRoamPrefs != NULL);
	assert(stringArray != NULL);
	assert(nLenArray != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_ARRAY|VT_VARIANT|VT_BYREF;

    rgsabound[0].lLbound = 1;
    rgsabound[0].cElements = arraySize;
    attrArray = SafeArrayCreate(VT_VARIANT, 1, rgsabound);
    if (attrArray == NULL)
	{
		_lastErrCode  = VS_GENERIC_ERROR;
		return -1;
	}

	vtName.pparray = &attrArray;
	for (nIndx = 0; nIndx < arraySize; ++nIndx)
	{
		assert (stringArray[nIndx] != NULL);
		varPtr = new VARIANT;
		VariantInit (varPtr);

		varPtr->vt = VT_BSTR;
		varPtr->bstrVal = SysAllocStringLen(stringArray[nIndx],nLenArray[nIndx]);
		ix = nIndx+1;
		SafeArrayPutElement(attrArray, &ix, varPtr);
	}

	hr = pRoamPrefs->put_RoamingSrvrs(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	if (*vtName.pparray != NULL)
		SafeArrayDestroy(*vtName.pparray);
	VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t** RoamPrefs_get_RoamingSrvrs (IVSRoamPrefs *pRoamPrefs, int *noOfElements)
{
	HRESULT hr;
	VARIANT var;
	VARTYPE resultType;
	wchar_t** retVal = NULL;
	long lBound, uBound, nIndx;
	VARIANT* varPtr=NULL;
    	
/*	_bstr_t string1 = "http://www.junk.com";
	_bstr_t string2 = "http://www.foo.com";

	assert(pRoamPrefs != NULL);

	*noOfElements = 2;
	retVal = (wchar_t**)malloc(2*sizeof(wchar_t*));
	retVal[0] = (wchar_t*)string1;
	retVal[1] = (wchar_t*)string2;

  */
	assert(pRoamPrefs != NULL);
	VariantInit (&var);

	hr = pRoamPrefs->get_RoamingSrvrs(&var);
	_lastErrCode = hr;
	
	if ((var.vt == (VT_ARRAY|VT_VARIANT|VT_BYREF)) && (hr == S_OK)) 
	{
		//if (SafeArrayGetVartype (*var.pparray, &resultType) == S_OK) //NOTE : We're not using this function 
														//because it is not present in the oleaut32.lib on a base
														//Win95 OSR2 machine.
		//	if ( resultType != VT_VARIANT) {
		if(!((*(var.pparray))->fFeatures & FADF_VARIANT))
		{
			retVal = NULL;
			goto doneGetRoamSrvrs;
		}
		
		if (SafeArrayGetLBound(*var.pparray, 1, &lBound) != S_OK) { 
			retVal = NULL;
			goto doneGetRoamSrvrs;
		}

		if (SafeArrayGetUBound(*var.pparray, 1, &uBound) != S_OK) { 
			retVal = NULL;
			goto doneGetRoamSrvrs;
		}

		// allocate the array of pointers
		retVal = (wchar_t**)malloc((uBound-lBound) * sizeof (wchar_t*));
		for (nIndx=lBound; nIndx < (lBound+uBound); ++nIndx)
		{
			if (SafeArrayGetElement(*var.pparray, &nIndx, varPtr) == S_OK)
			{
				if (varPtr->vt != VT_BSTR)
				{
				   free(retVal);
				   retVal = NULL;
				   goto doneGetRoamSrvrs;
				}
				retVal[nIndx-lBound] = (wchar_t*)varPtr->bstrVal;
			}
		}
		*noOfElements = uBound - lBound;
	}
	else
	{
		*noOfElements = 0;
		retVal = NULL;
	}

doneGetRoamSrvrs:
	return retVal;
}



EXTERN_C unsigned int RoamPrefs_set_ClientInfo(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pRoamPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pRoamPrefs->put_ClientInfo(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* RoamPrefs_get_ClientInfo (IVSRoamPrefs *pRoamPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pRoamPrefs != NULL);

	//VariantInit (&var);
	hr = pRoamPrefs->get_ClientInfo (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int RoamPrefs_set_ClientInfoSig(IVSRoamPrefs *pRoamPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pRoamPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pRoamPrefs->put_ClientInfoSig(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* RoamPrefs_get_ClientInfoSig (IVSRoamPrefs *pRoamPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pRoamPrefs != NULL);

	//VariantInit (&var);
	hr = pRoamPrefs->get_ClientInfoSig (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}
