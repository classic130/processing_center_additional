#include "srchcrit.h"
#include "srchcrit_i.c"
#include "ptav3_i.c"
#include "vssrchcritwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSSrchCrit* SrchCrit_GetInstance(IVSPTA* pPTA)
{
	IVSSrchCrit* pSrchCrit;
	HRESULT hr;

	hr = pPTA->get_IVSSrchCrit((IDispatch**)&pSrchCrit);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSSrchCrit,(void**)&pSrchCrit);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pSrchCrit;
}

EXTERN_C unsigned int SrchCrit_set_IssuerDN (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_IssuerDN(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* SrchCrit_get_IssuerDN (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_IssuerDN(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int SrchCrit_set_SubjectDN (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_SubjectDN(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* SrchCrit_get_SubjectDN (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_SubjectDN(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int SrchCrit_set_SerNum (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_SerNum(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* SrchCrit_get_SerNum (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_SerNum(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int SrchCrit_set_Email (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_Email(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* SrchCrit_get_Email (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_Email(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int SrchCrit_set_ExtOID (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_ExtOID(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}




EXTERN_C wchar_t* SrchCrit_get_ExtOID (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_ExtOID(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int SrchCrit_set_ExtVal (IVSSrchCrit *pSrchCritObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pSrchCritObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pSrchCritObj->put_ExtVal(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* SrchCrit_get_ExtVal (IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSrchCritObj != NULL);

	//VariantInit (&var);
	hr = pSrchCritObj->get_ExtVal(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  unsigned int SrchCrit_set_EffDate(IVSSrchCrit *pSrchCritObj, DATE effDate)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->put_EffDate(effDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C  DATE SrchCrit_get_EffDate(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	DATE effDate;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_EffDate(&effDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		effDate = -1;

	return effDate;
}


EXTERN_C  unsigned int SrchCrit_set_ExpDate(IVSSrchCrit *pSrchCritObj, DATE expDate)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->put_ExpDate(expDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C  DATE SrchCrit_get_ExpDate(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	DATE expDate;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_ExpDate(&expDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		expDate = -1;

	return expDate;
}


EXTERN_C  unsigned int SrchCrit_set_DateEquality(IVSSrchCrit *pSrchCritObj, short wDateEq)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varEquality;

	assert(pSrchCritObj != NULL);

	varEquality.vt = VT_I2;
	varEquality.iVal = wDateEq;
	hr = pSrchCritObj->put_DateEquality(varEquality);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear (&varEquality);
	return retVal;
}

EXTERN_C  short SrchCrit_get_DateEquality(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	short wDateEq;
	VARIANT varEq;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_DateEquality(&varEq);
	_lastErrCode = hr;

	if(hr!=S_OK)
		wDateEq = -1;
	else
		if (varEq.vt != VT_I2)
			wDateEq = -1;
		else
			wDateEq = varEq.iVal;

	VariantClear(&varEq);

	return wDateEq;
}


EXTERN_C  unsigned int SrchCrit_set_Renewed(IVSSrchCrit *pSrchCritObj, BOOL boolRenewed)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varRenewed;

	assert(pSrchCritObj != NULL);

	varRenewed.vt = VT_BOOL;
	varRenewed.boolVal = boolRenewed;
	hr = pSrchCritObj->put_Renewed(varRenewed);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear(&varRenewed);

	return retVal;
}

EXTERN_C  BOOL SrchCrit_get_Renewed(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	BOOL boolRenewed;
	VARIANT varRenewed;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_Renewed(&varRenewed);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolRenewed = -1;
	else
		if(varRenewed.vt != VT_BOOL)
			boolRenewed = -1;
		else
			boolRenewed = varRenewed.boolVal;

	VariantClear (&varRenewed);

	return boolRenewed;
}


EXTERN_C  unsigned int SrchCrit_set_KeyUsage(IVSSrchCrit *pSrchCritObj, short keyUsage)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varUsage;

	assert(pSrchCritObj != NULL);

	varUsage.vt = VT_I2;
	varUsage.iVal = keyUsage;
	hr = pSrchCritObj->put_KeyUsage(varUsage);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear(&varUsage);
	return retVal;
}

EXTERN_C  short SrchCrit_get_KeyUsage(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	short keyUsage;
	VARIANT varUsage;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_KeyUsage(&varUsage);
	_lastErrCode = hr;

	if(hr!=S_OK)
		keyUsage = -1;
	else
		if (varUsage.vt != VT_I2)
			keyUsage = -1;
		else
			keyUsage = varUsage.iVal;

	VariantClear (&varUsage);

	return keyUsage;
}

EXTERN_C  unsigned int SrchCrit_set_KeySize(IVSSrchCrit *pSrchCritObj, short keySize)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varSize;

	assert(pSrchCritObj != NULL);

	varSize.vt = VT_I2;
	varSize.iVal = keySize;
	hr = pSrchCritObj->put_KeySize(varSize);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear (&varSize);
	return retVal;
}

EXTERN_C  short SrchCrit_get_KeySize(IVSSrchCrit *pSrchCritObj)
{
	HRESULT hr;
	short keySize;
	VARIANT varSize;

	assert(pSrchCritObj != NULL);

	hr = pSrchCritObj->get_KeySize(&varSize);
	_lastErrCode = hr;

	if(hr!=S_OK)
		keySize = -1;
	else
		if (varSize.vt != VT_I2)
			keySize = -1;
		else
			keySize = varSize.iVal;

	return keySize;
}