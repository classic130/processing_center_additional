#include "import.h"
#include "import_i.c"
#include "p12wrap.h"
#include "ptav3.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSP12Import*	P12Import_GetInstance (IVSPTA* pPTA)
{
	IVSP12Import* pP12Import;
	HRESULT hr;

	hr = pPTA->get_IVSP12Import ((IDispatch**)&pP12Import);		
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pP12Import;
}


unsigned int P12Import_ImportP12 (IVSP12Import* pP12Import, int nType, wchar_t* pwstrP12, int nLen, wchar_t** pwstrSerNum, wchar_t** pwstrIssDN)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtType;
	VARIANT	vtP12;
	VARIANT varIssDN;
	VARIANT varSerNum;

	assert(pP12Import != NULL);

	vtType.vt =	VT_I2;
	vtType.iVal =	nType;

	vtP12.vt =	VT_BSTR;
	vtP12.bstrVal =	SysAllocStringLen (pwstrP12, nLen);

	
	//MessageBox(NULL,"Before calling the import function",NULL,MB_OK);
	hr =	pP12Import->ImportP12 (&vtType, &vtP12, &varSerNum, &varIssDN);
	if(hr == S_OK)
	{
		varIssDN.vt = VT_BSTR;
		*pwstrIssDN = varIssDN.bstrVal;

		varSerNum.vt = VT_BSTR;
		*pwstrSerNum = varSerNum.bstrVal;
	}

	_lastErrCode = hr;

	SysFreeString(vtP12.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}



EXTERN_C IVSP12Export*	P12Export_GetInstance (IVSPTA* pPTA)
{
	IVSP12Export* pP12Export;
	HRESULT hr;

	hr = pPTA->get_IVSP12Export ((IDispatch**)&pP12Export);		
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pP12Export;
}


EXTERN_C unsigned int	P12Export_ExportP12(IVSP12Export* pP12Export, int nOutputType, int nFlags, wchar_t* pwstrFile, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtType;
	VARIANT vtFlags;
	VARIANT	vtFile;

	assert(pP12Export != NULL);

	vtType.vt =	VT_I2;
	vtType.iVal =	nOutputType;

	vtFlags.vt =	VT_I2;
	vtFlags.iVal =	nFlags;

	vtFile.vt =	VT_BSTR;
	vtFile.bstrVal =	SysAllocStringLen (pwstrFile, nLen);

	
	//MessageBox(NULL,"Before calling the import function",NULL,MB_OK);
	hr =	pP12Export->ExportP12 (&vtType, &vtFlags, &vtFile);

	_lastErrCode = hr;

	SysFreeString(vtFile.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C int	P12Export_get_PasswdQuality(IVSP12Export* pP12Export)
{
	HRESULT hr;
	VARIANT var;
	int retVal;

	assert(pP12Export != NULL);

	VariantInit (&var);
	hr = pP12Export->get_PasswdQuality(&var);
	_lastErrCode = hr;

	if((hr==S_OK) && (var.vt == VT_I2))
		retVal =  var.iVal;
	else
		retVal = -1;
	VariantClear (&var);
	return retVal;
}


EXTERN_C unsigned int	P12Export_set_PasswdQuality(IVSP12Export* pP12Export, int newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pP12Export != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = newVal;
	hr = pP12Export->put_PasswdQuality(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int	P12Export_get_PasswdLength(IVSP12Export* pP12Export)
{
	HRESULT hr;
	VARIANT var;
	int retVal;

	assert(pP12Export != NULL);

	VariantInit (&var);
	hr = pP12Export->get_PasswdLength(&var);
	_lastErrCode = hr;

	if((hr==S_OK) && (var.vt == VT_I2))
		retVal =  var.iVal;
	else
		retVal = -1;
	VariantClear (&var);
	return retVal;
}


EXTERN_C unsigned int	P12Export_set_PasswdLength(IVSP12Export* pP12Export, int newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pP12Export != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = newVal;
	hr = pP12Export->put_PasswdLength(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}