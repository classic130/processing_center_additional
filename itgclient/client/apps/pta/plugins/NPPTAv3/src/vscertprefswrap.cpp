#include "certprefs.h"
#include "certprefs_i.c"
#include "vscertprefswrap.h"
#include "ptav3.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSCertPrefs* CertPrefs_GetInstance(IVSPTA* pPTA)
{
	IVSCertPrefs* pCertPrefs;
	HRESULT hr;

	hr = pPTA->get_IVSCertPrefs ((IDispatch**)&pCertPrefs);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSCertPrefs,(void**)&pCertPrefs);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pCertPrefs;
}



EXTERN_C  unsigned int CertPrefs_set_CertSerNum(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

//	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertSerNum(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
//	VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertSerNum(IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertSerNum(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  unsigned int CertPrefs_set_CertFrndlyName(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertFrndlyName(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertFrndlyName(IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertFrndlyName(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  unsigned int CertPrefs_set_CertIssDN(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertIssDN(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertIssDN(IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertIssDN(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  unsigned int CertPrefs_set_CertLogoUrl(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertLogoUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertLogoUrl(IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertLogoUrl(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C  unsigned int CertPrefs_set_CertDispString(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertDispString(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertDispString (IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertDispString(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C  unsigned int CertPrefs_set_CertTextureUrl(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pCertPrefsObj->put_CertTextureUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertTextureUrl (IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);

	//VariantInit (&var);
	hr = pCertPrefsObj->get_CertTextureUrl(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C  unsigned int CertPrefs_set_MarkAsRenewed (IVSCertPrefs* pCertPrefsObj, BOOL boolMarkAsRenewed)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	int retVal = VS_NO_ERROR;
	VARIANT varMark;

	assert(pCertPrefsObj != NULL);

	varMark.vt = VT_BOOL;
	varMark.boolVal = boolMarkAsRenewed;
	hr = pCertPrefsObj->put_MarkAsRenewed(varMark);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear(&varMark);
	return retVal;
}

EXTERN_C  BOOL CertPrefs_get_MarkAsRenewed(IVSCertPrefs* pCertPrefsObj)
{
	HRESULT hr;
	BOOL boolMarkAsRenewed;
	VARIANT varMark;

	assert(pCertPrefsObj != NULL);

	hr = pCertPrefsObj->get_MarkAsRenewed(&varMark);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolMarkAsRenewed = -1;
	else
		if (varMark.vt != VT_BOOL)
			boolMarkAsRenewed = -1;
		else
			boolMarkAsRenewed = varMark.boolVal;

	VariantClear(&varMark);
	return boolMarkAsRenewed;
}

EXTERN_C  unsigned int CertPrefs_set_CertPreference(IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen, wchar_t* pwstrVal, int nValLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName, vtVal;
	//BSTR bstrName;
	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);
	assert(pwstrVal != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	vtVal.vt = VT_BSTR;
	vtVal.bstrVal = SysAllocStringLen(pwstrVal, nValLen);

	hr = pCertPrefsObj->SetPreference(&vtName, &vtVal);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	SysFreeString(vtVal.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* CertPrefs_get_CertPreference (IVSCertPrefs* pCertPrefsObj, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT vtName;
	VARIANT var;

	assert(pCertPrefsObj != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	//VariantInit (&var);
	hr = pCertPrefsObj->GetPreference(&vtName, &var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;
	SysFreeString ( vtName.bstrVal);

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}