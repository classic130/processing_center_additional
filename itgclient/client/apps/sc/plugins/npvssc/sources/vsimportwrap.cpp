#include "VSImport.h"
#include "VSImport.c"
#include "VSImportWrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IImpPKCS12* Import_CreateInstance()
{
	IImpPKCS12* pImport;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_ImpPKCS12, NULL, CLSCTX_INPROC_SERVER, IID_IImpPKCS12,(void**)&pImport);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pImport;
}

EXTERN_C unsigned int Import_Import(IImpPKCS12* pImport, wchar_t* pwstrPKCS12, int nPKCS12Len, wchar_t* pwstrPKCS7, int nPKCS7Len, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varPKCS7;
	VARIANT varPKCS12;
	VARIANT varStatus;
	VARIANT varErrCode;
	VARIANT varErrString;

	assert(pImport != NULL);
	assert(pwstrPKCS7 != NULL);
	assert(pwstrPKCS12 != NULL);
	assert(ppwstrErrString != NULL);

	varPKCS7.vt = VT_BSTR;
	varPKCS7.bstrVal = SysAllocStringLen((OLECHAR *)pwstrPKCS7, nPKCS7Len);

	varPKCS12.vt = VT_BSTR;
	varPKCS12.bstrVal = SysAllocStringLen((OLECHAR *)pwstrPKCS12, nPKCS12Len);


	varStatus.vt = VT_BOOL;
	varErrCode.vt = VT_I4;
	varErrString.vt = VT_BSTR;

	hr = pImport->Import(&varPKCS12, &varPKCS7, &varStatus, &varErrCode, &varErrString);
	_lastErrCode = hr;
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	else
	{
		varStatus.vt = VT_BOOL;
		if(!varStatus.boolVal)
		{
			varErrString.vt = VT_BSTR;
			*ppwstrErrString = varErrString.bstrVal;
			retVal = varErrCode.lVal;
		}
		else
		{
			
			retVal = VS_NO_ERROR;
		}
	}
	VS_PLUGIN_ERASE_BSTR((varPKCS12.bstrVal))
	SysFreeString(varPKCS12.bstrVal);
	VS_PLUGIN_ERASE_BSTR((varPKCS7.bstrVal))
	SysFreeString(varPKCS7.bstrVal);
	return retVal;
}

EXTERN_C unsigned int Import_set_KeyExportable(IImpPKCS12* pImport, long lKeyExp)
{
	HRESULT hr = 0;
	unsigned int retVal = VS_NO_ERROR; 

	assert(pImport != NULL); 

	hr = pImport->put_KeyExportable(lKeyExp); 
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	return retVal;
}

EXTERN_C long Import_get_KeyExportable(IImpPKCS12* pImport)
{
	HRESULT hr;
	int retVal = -1;

	assert(pImport != NULL);

	hr = pImport->get_KeyExportable(&retVal);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = -1;

	return retVal;
}

EXTERN_C unsigned int Import_set_ProviderName (IImpPKCS12* pImport, wchar_t* pwstProviderName, int nLen)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	BSTR bstrName;

	assert(pImport != NULL);
	assert(pwstProviderName != NULL);

	bstrName = SysAllocStringLen(pwstProviderName,nLen);
	hr = pImport->put_ProviderName(bstrName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(bstrName);
	return retVal;
}

EXTERN_C wchar_t* Import_get_ProviderName (IImpPKCS12* pImport)
{
	HRESULT hr;
	BSTR bstrName;

	assert(pImport != NULL);

	hr = pImport->get_ProviderName(&bstrName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		bstrName = NULL;

	return (wchar_t*)bstrName;
}
