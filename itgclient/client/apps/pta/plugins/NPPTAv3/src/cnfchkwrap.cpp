#include "ConfigChk.h"
#include "ConfigChk_i.c"
#include "global.h"
#include <comdef.h>
#include <assert.h>

EXTERN_C HRESULT _lastErrCode;

EXTERN_C IConfigChkr* CnfChk_CreateInstance()
{
	IConfigChkr* pCnfChk;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_ConfigChkr, NULL, CLSCTX_INPROC_SERVER, IID_IConfigChkr,(void**)&pCnfChk);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pCnfChk;
}


EXTERN_C int CnfChk_CheckMSEnhCSP(IConfigChkr* pCfgChk, long* lpResult)
{
	HRESULT hr;
	DWORD retVal = VS_NO_ERROR;

	assert(pCfgChk != NULL);

	
	hr = pCfgChk->CheckMSEnhCSP(lpResult);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	

	return retVal;
}

EXTERN_C int CnfChk_FixEnhCSP(IConfigChkr* pCfgChk, wchar_t* pwstrVer, int nLen, long* lpResult)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varVer;

	assert(pCfgChk != NULL);
	assert(pwstrVer != NULL);

	varVer.vt = VT_BSTR;
	varVer.bstrVal= SysAllocStringLen(pwstrVer, nLen);
	hr = pCfgChk->FixEnhCSP(&varVer, lpResult);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(varVer.bstrVal);
	return retVal;
}

EXTERN_C int CnfChk_GetVersion(IConfigChkr* pCfgChk, wchar_t* pwstrFileName, int nLen, wchar_t** ppwstrVer, long* lpResult)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varFileName;
	VARIANT varVersion;

	assert(pCfgChk != NULL);
	assert(ppwstrVer != NULL);

	varFileName.vt = VT_BSTR;
	varFileName.bstrVal = SysAllocStringLen(pwstrFileName, nLen);

	hr = pCfgChk->GetVersion(&varFileName, &varVersion, lpResult);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	else
	{
		varVersion.vt = VT_BSTR;
		*ppwstrVer = varVersion.bstrVal;
	}

	SysFreeString(varFileName.bstrVal);
	return retVal;
}

EXTERN_C int CnfChk_VerCompare(IConfigChkr* pCfgChk, wchar_t* pwstrVer1, int nVer1Len, wchar_t* pwstrVer2, int nVer2Len, long* lpResult)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varVer1;
	VARIANT varVer2;

	assert(pCfgChk != NULL);
	assert(pwstrVer1 != NULL);
	assert(pwstrVer2 != NULL);

	varVer1.vt = VT_BSTR;
	varVer1.bstrVal= SysAllocStringLen(pwstrVer1, nVer1Len);

	varVer2.vt = VT_BSTR;
	varVer2.bstrVal= SysAllocStringLen(pwstrVer2, nVer2Len);

	hr = pCfgChk->VerCompare(&varVer1, &varVer2, lpResult);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(varVer1.bstrVal);
	SysFreeString(varVer2.bstrVal);

	return retVal;
}