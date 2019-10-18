#include "vssc.h"
#include "resolvercptwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

EXTERN_C HRESULT _lastErrCode;


//EXTERN_C IResolveRcpt* ResolveRcpt_GetInstance(IVSSC *pVSSC)
EXTERN_C IResolveRcpt* ResolveRcpt_GetInstance(IVSSC *pVSSC)
{
	IResolveRcpt* pResolveRcpt;
	HRESULT hr;

	//hr = pVSSC->get_IVSResolveRcpt((IDispatch**)&pResolveRcpt);
	hr = pVSSC->QueryInterface(IID_IResolveRcpt, (void **)&pResolveRcpt);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pResolveRcpt;
}

EXTERN_C wchar_t* get_ResolveRcpt_EmailAddress(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT var;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->get_EmailAddress(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

EXTERN_C short get_ResolveRcpt_Recipient_Count(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT varResult;

	assert(pResolveRcpt != NULL);
	
	hr = pResolveRcpt->get_Recipient_Count(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;


}


EXTERN_C unsigned int get_ResolveRcpt_Status(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT varResult;

	assert(pResolveRcpt != NULL);
	
	hr = pResolveRcpt->get_Status(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.iVal;
	else
		return -1;
}

EXTERN_C wchar_t* get_ResolveRcpt_IssuerDN(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT var;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->get_Issuer_DN(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C wchar_t* get_ResolveRcpt_SerialNumber(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT var;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->get_SerialNumber(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C unsigned int ResolveRcpt_First(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->First();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}

EXTERN_C unsigned int ResolveRcpt_Next(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->Next();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}

EXTERN_C int get_ResolveRcpt_RevocationStatus(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pResolveRcpt != NULL);
	
	hr = pResolveRcpt->get_RevocationStatus(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.lVal;
	else
		return -1;

}

EXTERN_C int get_ResolveRcpt_ChainValidationStatus(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pResolveRcpt != NULL);
	
	hr = pResolveRcpt->get_ChainValidationStatus(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.lVal;
	else
		return -1;


}

EXTERN_C BOOL get_ResolveRcpt_IsCertExpired(IResolveRcpt *pResolveRcpt)
{
	HRESULT hr;
	VARIANT var;

	assert(pResolveRcpt != NULL);

	hr = pResolveRcpt->get_IsCertExpired(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BOOL) 
		return var.bVal;
	else
		return false;


}