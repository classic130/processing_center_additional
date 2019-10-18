#include "ptav3.h"
#include "ptav3_i.c"
#include "vsptawrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSPTA* PTA_CreateInstance()
{
	IVSPTA* pPTA;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSPTA,(void**)&pPTA);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pPTA;
}


EXTERN_C unsigned int PTA_Initialize (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, int intVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VARIANT vtCSP;
	//BSTR bstrName;
	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	
	vtCSP.vt = VT_I2;
	vtCSP.iVal = intVal;
	hr = pPTA->Initialize(&vtName, &vtCSP);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int PTA_Close (IVSPTA *pPTA)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pPTA != NULL);

	hr = pPTA->Close();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}



EXTERN_C unsigned int PTA_set_AppPreference (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, wchar_t* pwstrNameB, int nLenB)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VARIANT vtVal;
	//BSTR bstrName;
	assert(pPTA != NULL);
	assert(pwstrName != NULL);
	assert(pwstrNameB != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	vtVal.vt = VT_BSTR;
	vtVal.bstrVal = SysAllocStringLen(pwstrNameB,nLenB);

	
	hr = pPTA->AppPref_SetPreference(&vtName, &vtVal);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtName.bstrVal))
	SysFreeString(vtName.bstrVal);
	VS_PLUGIN_ERASE_BSTR((vtVal.bstrVal))
	SysFreeString(vtVal.bstrVal);
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C wchar_t* PTA_get_AppPreference (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	
	VARIANT vtName;
	VARIANT var;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	
	hr = pPTA->AppPref_GetPreference (&vtName, &var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;
	VS_PLUGIN_ERASE_BSTR((vtName.bstrVal))
	SysFreeString(vtName.bstrVal);

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int PTA_set_CSPName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_CSPName(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C wchar_t* PTA_get_CSPName (IVSPTA *pPTA)
{
	HRESULT hr;
	
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_CSPName (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int PTA_InstallCert (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->InstallCert(&vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int PTA_SelectIDForTrans (IVSPTA *pPTA)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pPTA != NULL);

	hr = pPTA->SelIDForTrans();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}



EXTERN_C unsigned int PTA_SelectIDForChallenge (IVSPTA *pPTA)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pPTA != NULL);

	hr = pPTA->SelIDForChallenge();
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}



EXTERN_C wchar_t* PTA_SignTransaction (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, short nHashAlg)
{
	HRESULT hr;
	
	VARIANT varResult, var1, var2;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);
	VariantInit(&var1);
	VariantInit(&var2);
	VariantInit(&varResult);
	
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(pwstrName,nLen);
	var2.vt = VT_I2;
	var2.iVal = nHashAlg;

	hr = pPTA->SignTransaction (&var1, &var2, &varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_BSTR) 
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C wchar_t* PTA_SignChallenge (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, short nHashAlg)
{
	HRESULT hr;
	
	VARIANT varResult, var1, var2;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);
	VariantInit(&var1);
	VariantInit(&var2);
	VariantInit(&varResult);
	
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(pwstrName,nLen);
	var2.vt = VT_I2;
	var2.iVal = nHashAlg;

	hr = pPTA->SignChallenge (&var1, &var2, &varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_BSTR) 
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C wchar_t* PTA_CreateCertReq (IVSPTA *pPTA,wchar_t* subjectDN, int subjectDNLen, 
				                     int KeyAttributes, int HashAlg, wchar_t** attributes, int *nLenArray,
									 int noOfEntries)
{
	 HRESULT hr;
	 VARIANT var1, var2, var3, var4, varResult;
	 int nIndx;
	 long ix[2];
	 SAFEARRAYBOUND rgsabound[2];
	 SAFEARRAY* attrArray;
	 VARIANT *varPtr;
	
	 assert(pPTA != NULL);
	 assert(subjectDN != NULL);
	 assert(attributes != NULL);
	 assert(nLenArray != NULL);

	 VariantInit(&var1);
	 VariantInit(&var2);
	 VariantInit(&var3);
	 VariantInit(&var4);
	 VariantInit(&varResult);
	 if ((noOfEntries%2) != 0)
	 {
		 _lastErrCode = VS_GENERIC_ERROR;
		 return (wchar_t*)NULL;
	 }
	 
	 var1.vt = VT_BSTR;
     var1.bstrVal = SysAllocStringLen(subjectDN,subjectDNLen);
     var2.vt = VT_I4;
	 var2.lVal = KeyAttributes;
	 var3.vt = VT_I2;
	 var3.iVal = HashAlg;
	 var4.vt = VT_ARRAY|VT_VARIANT|VT_BYREF;
     

     rgsabound[0].lLbound = 1;
     rgsabound[0].cElements = noOfEntries/2;
     rgsabound[1].lLbound = 1;
     rgsabound[1].cElements = 2;
     attrArray = SafeArrayCreate(VT_VARIANT, 2, rgsabound);
     if (attrArray == NULL)
	 {
		_lastErrCode = VS_GENERIC_ERROR;
		return (wchar_t*)NULL;
	 }
	 var4.pparray = &attrArray;

	 for (nIndx = 0; nIndx < noOfEntries; nIndx=nIndx+2)
	 {
	 	assert (attributes[nIndx] != NULL);
		assert (attributes[nIndx+1] != NULL);
		varPtr = new VARIANT;
		VariantInit (varPtr);
		varPtr->vt = VT_BSTR;
		varPtr->bstrVal = SysAllocStringLen(attributes[nIndx],nLenArray[nIndx]);
		ix[0] = nIndx/2+1;
		ix[1] = 1;
        SafeArrayPutElement(attrArray, ix, varPtr);
		varPtr = new VARIANT;
		VariantInit (varPtr);
		varPtr->vt = VT_BSTR;
		varPtr->bstrVal = SysAllocStringLen(attributes[nIndx+1],nLenArray[nIndx+1]);
		ix[1] = 2;
        SafeArrayPutElement(attrArray, ix, varPtr);
	 }
     hr = pPTA->CreateCertReq (&var1, &var2, &var3, &var4, &varResult);
	 _lastErrCode = hr;


	VariantClear (&var1);
	VariantClear(&var2);
    VariantClear(&var3);
	if (*var4.pparray != NULL)
		SafeArrayDestroy(*var4.pparray);
    VariantClear(&var4);

	if (varResult.vt == VT_BSTR) 
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int PTA_set_ProtocolName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_ProtocolName(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C wchar_t* PTA_get_ProtocolName (IVSPTA *pPTA)
{
	HRESULT hr;
	
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_ProtocolName (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C wchar_t* PTA_SignRenewal (IVSPTA *pPTA, short nHashAlg)
{
	HRESULT hr;
	
	VARIANT varResult, var;

	assert(pPTA != NULL);
	VariantInit(&var);
	VariantInit(&varResult);
	
	var.vt = VT_I2;
	var.iVal = nHashAlg;

	hr = pPTA->SignRenewal (&var, &varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_BSTR) 
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int PTA_InstallKeyPair (IVSPTA *pPTA, wchar_t* pwstrName, int nLen, wchar_t* pkcs7, int pkcs7len)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VARIANT varpkcs7;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);
	assert(pkcs7 != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	varpkcs7.vt = VT_BSTR;
	varpkcs7.bstrVal = SysAllocStringLen(pkcs7,pkcs7len);


	hr = pPTA->InstallKeyPair(&vtName, &varpkcs7);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtName.bstrVal))
	SysFreeString(vtName.bstrVal);
	VS_PLUGIN_ERASE_BSTR((varpkcs7.bstrVal))
	SysFreeString(varpkcs7.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}


EXTERN_C unsigned int PTA_set_UserDefCertFlag (IVSPTA *pPTA,short shortFlag)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = shortFlag;

	hr = pPTA->put_UseDefCertFlag(vtName);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C short PTA_get_UserDefCertFlag (IVSPTA *pPTA)
{
	HRESULT hr;
	VARIANT varResult;

	assert(pPTA != NULL);
	
	hr = pPTA->get_UseDefCertFlag (&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;
}


EXTERN_C unsigned int PTA_set_AuthDll (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_AuthDll(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C wchar_t* PTA_get_AuthDll (IVSPTA *pPTA)
{
	HRESULT hr;
	
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_AuthDll (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int PTA_set_ProfileIssFrndlyName (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_ProfileIssFrndlyName(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C wchar_t* PTA_get_ProfileIssFrndlyName (IVSPTA *pPTA)
{
	HRESULT hr;
	
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_ProfileIssFrndlyName (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C unsigned int PTA_set_ProfileIssUniqueId (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_ProfileIssUniqueId(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C wchar_t* PTA_get_ProfileIssUniqueId (IVSPTA *pPTA)
{
	HRESULT hr;
	
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_ProfileIssUniqueId (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int PTA_set_AffLogoUrl (IVSPTA *pPTA, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pPTA != NULL);
	assert(pwstrName != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);

	hr = pPTA->put_AffLogoUrl(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C wchar_t* PTA_get_AffLogoUrl(IVSPTA *pPTA)
{
	HRESULT hr;
	VARIANT var;

	assert(pPTA != NULL);
	
	hr = pPTA->get_AffLogoUrl(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int PTA_set_EnableCertForCapi(IVSPTA *pPTA, BOOL boolEnableForCapi)
{
	HRESULT hr;
	int retVal = VS_NO_ERROR;
	VARIANT varEnable;

	assert(pPTA != NULL);

	varEnable.vt = VT_BOOL;
	varEnable.boolVal = boolEnableForCapi;
	hr = pPTA->put_EnableCertForCapi(varEnable);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear(&varEnable);
	return retVal;
}