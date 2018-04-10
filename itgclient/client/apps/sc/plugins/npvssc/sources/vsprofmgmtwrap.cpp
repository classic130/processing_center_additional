#include "profmgmt.h"
#include "profmgmt_i.c"
#include "ptav3.h"
#include "vsprofmgmtwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSProfMgmt* ProfMgmt_GetInstance(IVSPTA* pPTA)
{
	IVSProfMgmt* pProfMgmt;
	HRESULT hr;

	hr = pPTA->get_IVSProfMgmt ((IDispatch**)&pProfMgmt);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSProfMgmt,(void**)&pProfMgmt);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pProfMgmt;
}


EXTERN_C unsigned int ProfMgmt_set_PasswdQuality (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_PasswdQuality(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_PasswdQuality (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_PasswdQuality (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}



EXTERN_C unsigned int ProfMgmt_set_PasswdLength (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_PasswdLength(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_PasswdLength (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_PasswdLength (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}


EXTERN_C unsigned int ProfMgmt_set_PasswdTimeOut (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_PasswdTimeOut(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_PasswdTimeOut (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_PasswdTimeOut (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}



EXTERN_C unsigned int ProfMgmt_set_PasswdLockOutTries (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_PasswdLockOutTries(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_PasswdLockOutTries (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_PasswdLockOutTries (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}


EXTERN_C unsigned int ProfMgmt_set_PasswdUnLockPeriod (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_PasswdUnLockPeriod(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_PasswdUnLockPeriod (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_PasswdUnLockPeriod (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}


EXTERN_C unsigned int ProfMgmt_set_OpenProfFlags (IVSProfMgmt *pProfMgmt, int nParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nParam;
	hr = pProfMgmt->put_OpenProfFlags(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_OpenProfFlags (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_OpenProfFlags (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}



EXTERN_C unsigned int ProfMgmt_set_ProfileName (IVSProfMgmt *pProfMgmt, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pProfMgmt->put_ProfileName(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* ProfMgmt_get_ProfileName (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_ProfileName (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int ProfMgmt_set_Password (IVSProfMgmt *pProfMgmt, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pProfMgmt->put_Password(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	VS_PLUGIN_ERASE_BSTR((vtName.bstrVal))
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C unsigned int ProfMgmt_set_SaveLocal (IVSProfMgmt *pProfMgmt, BOOL boolParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_BOOL;
	vtName.boolVal = boolParam;
	hr = pProfMgmt->put_SaveLocal(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_SaveLocal (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_SaveLocal (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BOOL) 
		return var.boolVal;
	else
		return -1;
}


EXTERN_C unsigned int ProfMgmt_set_RoamProfile (IVSProfMgmt *pProfMgmt, BOOL boolParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_BOOL;
	vtName.boolVal = boolParam;
	hr = pProfMgmt->put_RoamProfile(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_RoamProfile (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_RoamProfile (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BOOL) 
		return var.boolVal;
	else
		return -1;
}


EXTERN_C unsigned int ProfMgmt_OpenProfile (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pProfMgmt != NULL);

	hr = pProfMgmt->OpenProfile();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int ProfMgmt_CloseProfile (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pProfMgmt != NULL);

	hr = pProfMgmt->CloseProfile();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C unsigned int ProfMgmt_SaveProfile (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pProfMgmt != NULL);

	hr = pProfMgmt->SaveProfile();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int ProfMgmt_ChangePassword (IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pProfMgmt != NULL);

	hr = pProfMgmt->ChangePassword();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int ProfMgmt_set_IsUsernameEditable(IVSProfMgmt *pProfMgmt, BOOL boolParam)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pProfMgmt != NULL);

	vtName.vt = VT_BOOL;
	vtName.boolVal = boolParam;
	hr = pProfMgmt->put_IsUsernameEditable(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C int ProfMgmt_get_IsUsernameEditable(IVSProfMgmt *pProfMgmt)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pProfMgmt != NULL);

	//VariantInit (&var);
	hr = pProfMgmt->get_IsUsernameEditable(&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BOOL) 
		return var.boolVal;
	else
		return -1;
}
