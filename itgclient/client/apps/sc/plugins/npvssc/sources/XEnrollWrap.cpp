#include "XEnrollWrap.h"
#include "Xenroll_i.c"

#include "global.h"
#include <comdef.h>
#include <assert.h>
#include <stdio.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

EXTERN_C ICEnroll* Enroll_CreateInstance()
{
	ICEnroll* pEnroll;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_CEnroll, NULL, CLSCTX_INPROC_SERVER, IID_ICEnroll,(void**)&pEnroll);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pEnroll;
}

EXTERN_C unsigned int Enroll_set_ProviderType(ICEnroll* pEnroll, DWORD dwProviderType)
{
	HRESULT hr = 0;
	unsigned int retVal = VS_NO_ERROR; 

	assert(pEnroll != NULL); 

	hr = pEnroll->put_ProviderType(dwProviderType); 
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	return retVal;
}

EXTERN_C DWORD Enroll_get_ProviderType(ICEnroll* pEnroll)
{
	HRESULT hr;
	DWORD retVal = -1;

	assert(pEnroll != NULL);

	hr = pEnroll->get_ProviderType(&retVal);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = -1;

	return retVal;
}

EXTERN_C unsigned int Enroll_set_GenKeyFlags(ICEnroll* pEnroll, DWORD dwGenKeyFlags)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pEnroll != NULL);

	hr = pEnroll->put_GenKeyFlags(dwGenKeyFlags);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	return retVal;
}

EXTERN_C DWORD Enroll_get_GenKeyFlags(ICEnroll* pEnroll)
{
	HRESULT hr;
	DWORD retVal = -1;

	assert(pEnroll != NULL);

	hr = pEnroll->get_GenKeyFlags(&retVal);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = -1;

	return retVal;
}

EXTERN_C unsigned int Enroll_set_ProviderName(ICEnroll* pEnroll, wchar_t* pwstrProviderName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	BSTR bstrName;

	assert(pEnroll != NULL);
	assert(pwstrProviderName != NULL);

	bstrName = SysAllocStringLen(pwstrProviderName, nLen);
	hr = pEnroll->put_ProviderName(bstrName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(bstrName);
	return retVal;
}

EXTERN_C wchar_t* Enroll_get_ProviderName(ICEnroll* pEnroll)
{
	HRESULT hr;
	BSTR bstrName;

	assert(pEnroll != NULL);

	hr = pEnroll->get_ProviderName(&bstrName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		bstrName = NULL;

	return (wchar_t*)bstrName;
}

EXTERN_C unsigned int Enroll_set_HashAlgorithm(ICEnroll* pEnroll, wchar_t* pwstrHashAlgorithm, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	BSTR bstrHashAlgorithm;

	assert(pEnroll != NULL);
	assert(pwstrHashAlgorithm != NULL);

	bstrHashAlgorithm = SysAllocStringLen(pwstrHashAlgorithm, nLen);
	hr = pEnroll->put_HashAlgorithm(bstrHashAlgorithm);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(bstrHashAlgorithm);
	return retVal;
}

EXTERN_C wchar_t* Enroll_get_HashAlgorithm(ICEnroll* pEnroll)
{
	HRESULT hr;
	BSTR bstrHashAlgorithm;

	assert(pEnroll != NULL);

	hr = pEnroll->get_HashAlgorithm(&bstrHashAlgorithm);
	_lastErrCode = hr;

	if(hr!=S_OK)
		bstrHashAlgorithm = NULL;

	return (wchar_t*)bstrHashAlgorithm;
}

EXTERN_C unsigned int Enroll_set_KeySpec(ICEnroll* pEnroll, DWORD dwKeySpec)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pEnroll != NULL);

	hr = pEnroll->put_KeySpec(dwKeySpec);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

EXTERN_C DWORD Enroll_get_KeySpec(ICEnroll* pEnroll)
{
	HRESULT hr;
	DWORD dwKeySpec;

	assert(pEnroll != NULL);

	hr = pEnroll->get_KeySpec(&dwKeySpec);
	_lastErrCode = hr;

	if(hr!=S_OK)
		dwKeySpec = -1;

	return dwKeySpec;
}

EXTERN_C unsigned int Enroll_set_DeleteRequestCert(ICEnroll* pEnroll, BOOL boolDeleteCertRequest)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pEnroll != NULL);

	hr = pEnroll->put_DeleteRequestCert(boolDeleteCertRequest);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

EXTERN_C DWORD Enroll_get_DeleteRequestCert(ICEnroll* pEnroll)
{
	HRESULT hr;
	BOOL boolDeleteCertRequest;

	assert(pEnroll != NULL);

	hr = pEnroll->get_DeleteRequestCert(&boolDeleteCertRequest);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolDeleteCertRequest = FALSE;

	return boolDeleteCertRequest;
}

EXTERN_C unsigned int Enroll_set_WriteCertToCSP(ICEnroll* pEnroll, BOOL boolWriteCertToCSP)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pEnroll != NULL);

	hr = pEnroll->put_WriteCertToCSP(boolWriteCertToCSP);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}

EXTERN_C DWORD Enroll_get_WriteCertToCSP(ICEnroll* pEnroll)
{
	HRESULT hr;
	BOOL boolWriteCertToCSP;

	assert(pEnroll != NULL);

	hr = pEnroll->get_WriteCertToCSP(&boolWriteCertToCSP);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolWriteCertToCSP = FALSE;

	return boolWriteCertToCSP;
}

EXTERN_C wchar_t* Enroll_enumProvider(ICEnroll* pEnroll, DWORD dwIndex, DWORD dwFlags)
{
	HRESULT hr;
	BSTR bstrProvider;

	assert(pEnroll != NULL);

	hr = pEnroll->enumProviders(dwIndex, dwFlags,&bstrProvider);
	_lastErrCode = hr;

	if(hr!=S_OK)
		bstrProvider = NULL;

	return (wchar_t*)bstrProvider;
}

EXTERN_C wchar_t* Enroll_createPKCS10(ICEnroll* pEnroll, wchar_t* pwstrDN, int nDNLen, wchar_t* pwstrUsage, int nUsageLen)
{
	HRESULT hr = 0;
	BSTR bstrPCKS10 = NULL;
	BSTR bstrDN;
	BSTR bstrUsage;

	assert(pEnroll != NULL);

	bstrDN = SysAllocStringLen(pwstrDN, nDNLen);
	bstrUsage = SysAllocStringLen(pwstrUsage, nUsageLen);

	try
	{
		hr = pEnroll->createPKCS10(bstrDN, bstrUsage, &bstrPCKS10);
		_lastErrCode = hr;
	}
	catch(...)
	{
		BSTR bstrProvName = NULL;
		pEnroll->get_ProviderName(&bstrProvName);
		if(!bstrProvName)
		{
			hr = _lastErrCode = E_UNEXPECTED;
		}
		else
		{
			_bstr_t temp("Microsoft Enhanced Cryptographic Provider v1.0");
			//temp = bstrProvName;
			if(bstrProvName == temp)
			{
				DWORD flags;  
				pEnroll->get_GenKeyFlags(&flags);
				if(flags & 0x04000000)
					hr = _lastErrCode = 0x80009009;
				else
					hr = _lastErrCode = E_UNEXPECTED;
			}
			SysFreeString(bstrProvName);
		}
	}
	if(hr!=S_OK)
		bstrPCKS10 = NULL;

	return (wchar_t*)bstrPCKS10;
}

EXTERN_C unsigned int Enroll_acceptPKCS7(ICEnroll* pEnroll, wchar_t* pwstrPKCS7, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	BSTR bstrPKCS7;

	assert(pEnroll != NULL);
	assert(pwstrPKCS7 != NULL);

	bstrPKCS7 = SysAllocStringLen(pwstrPKCS7, nLen);
	hr = pEnroll->acceptPKCS7(bstrPKCS7);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(bstrPKCS7);
	return retVal;
}

