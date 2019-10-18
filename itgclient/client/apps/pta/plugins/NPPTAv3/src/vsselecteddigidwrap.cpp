#include "seldigid.h"
#include "seldigid_i.c"
#include "ptav3.h"
#include "vsselecteddigidwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSSelectedDigID* SelectedDigID_GetInstance(IVSPTA* pPTA)
{
	IVSSelectedDigID* pSelectedDigID;
	HRESULT hr;

	hr = pPTA->get_IVSSelectedDigID((IDispatch**)&pSelectedDigID);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSSelectedDigID,(void**)&pSelectedDigID);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pSelectedDigID;
}


EXTERN_C wchar_t* SelectedDigID_get_IssuerDN (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_IssuerDN(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* SelectedDigID_get_SubjectDN (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_SubjectDN(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* SelectedDigID_get_SerNum (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_SerNum(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* SelectedDigID_get_FrndlyName (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_FrndlyName(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* SelectedDigID_get_LogoUrl (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_LogoUrl(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* SelectedDigID_get_TextureUrl (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_TextureUrl(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  DATE SelectedDigID_get_ExpDate(IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	DATE expDate;

	assert(pSelectedDigID != NULL);

	hr = pSelectedDigID->get_ExpDate(&expDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		expDate = -1;

	return expDate;
}


EXTERN_C  DATE SelectedDigID_get_EffDate(IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	DATE effDate;

	assert(pSelectedDigID != NULL);

	hr = pSelectedDigID->get_EffDate(&effDate);
	_lastErrCode = hr;

	if(hr!=S_OK)
		effDate = -1;

	return effDate;
}


EXTERN_C  BOOL SelectedDigID_get_Renewed(IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	BOOL boolRenewed;
	VARIANT varRenewed;

	assert(pSelectedDigID != NULL);

	hr = pSelectedDigID->get_Renewed(&varRenewed);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolRenewed = -1;
	else
		if (varRenewed.vt != VT_BOOL)
			boolRenewed = -1;
		else
			boolRenewed = varRenewed.boolVal;

	VariantClear(&varRenewed);

	return boolRenewed;
}

EXTERN_C  short SelectedDigID_get_KeyUsage(IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	short keyUsage;
	VARIANT varUsage;

	assert(pSelectedDigID != NULL);

	hr = pSelectedDigID->get_KeyUsage(&varUsage);
	_lastErrCode = hr;

	if(hr!=S_OK)
		keyUsage = -1;
	else
		if (varUsage.vt != VT_I2)
			keyUsage = -1;
		else
			keyUsage = varUsage.iVal;

	VariantClear(&varUsage);

	return keyUsage;
}

EXTERN_C  short SelectedDigID_get_KeySize(IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	short keySize;
	VARIANT varSize;

	assert(pSelectedDigID != NULL);

	hr = pSelectedDigID->get_KeySize(&varSize);
	_lastErrCode = hr;

	if(hr!=S_OK)
		keySize = -1;
	else
		if (varSize.vt != VT_I2)
			keySize = -1;
		else
			keySize = varSize.iVal;

	VariantClear (&varSize);

	return keySize;
}


EXTERN_C wchar_t* SelectedDigID_get_PubKeyMD5 (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_PubKeyMD5(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C wchar_t* SelectedDigID_get_PubKeySHA1 (IVSSelectedDigID *pSelectedDigID)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pSelectedDigID != NULL);

	//VariantInit (&var);
	hr = pSelectedDigID->get_PubKeySHA1 (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}
