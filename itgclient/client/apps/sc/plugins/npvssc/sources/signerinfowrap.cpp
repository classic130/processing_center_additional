#include "vssc.h"
#include "signerinfowrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

EXTERN_C HRESULT _lastErrCode;


EXTERN_C IVSSignerInfo* SignerInfo_GetInstance(IVSSC *pVSSC)
{
	IVSSignerInfo* pVSSignerInfo;
	HRESULT hr;

	hr = pVSSC->QueryInterface(IID_IVSSignerInfo, (void **)&pVSSignerInfo);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pVSSignerInfo;
}

EXTERN_C wchar_t* get_SignerInfo_SubjectCN(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	VARIANT var;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_SubjectCN(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}


EXTERN_C wchar_t* get_SignerInfo_SubjectDN(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	VARIANT var;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_SubjectDN(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* get_SignerInfo_IssuerDN(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	VARIANT var;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_IssuerDN(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* get_SignerInfo_SubjectSerialNumber(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	VARIANT var;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_SubjectSerialNumber(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C DATE get_SignerInfo_SubjectValidFrom(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	DATE expDate;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_SubjectValidFrom(&expDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		expDate = -1;

	return expDate;

}

EXTERN_C DATE get_SignerInfo_SubjectValidTo(IVSSignerInfo *pVSSignerInfo)
{
	HRESULT hr;
	DATE expDate;

	assert(pVSSignerInfo != NULL);

	hr = pVSSignerInfo->get_SubjectValidTo(&expDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		expDate = -1;

	return expDate;
}