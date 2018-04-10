#include "vssc.h"
#include "vssc_i.c"
#include "vsscwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>
#include <stdlib.h>

EXTERN_C HRESULT _lastErrCode;

EXTERN_C IVSSC* VSSC_CreateInstance()
{
	IVSSC* pVSSC;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_VSSC, NULL, CLSCTX_INPROC_SERVER, IID_IVSSC,(void**)&pVSSC);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pVSSC;
}

EXTERN_C wchar_t* get_VSSC_ToRecipientsInfo(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_ToRecipientsInfo (&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C unsigned int set_VSSC_ToRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{

	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_ToRecipientsInfo(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}

EXTERN_C wchar_t* get_VSSC_CcRecipientsInfo(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_CcRecipientsInfo(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C unsigned int set_VSSC_CcRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_CcRecipientsInfo(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}


EXTERN_C wchar_t* get_VSSC_BccRecipientsInfo(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;

	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_BccRecipientsInfo(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C unsigned int set_VSSC_BccRecipientsInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_BccRecipientsInfo(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C wchar_t* get_VSSC_FromInfo(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;

	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_FromInfo(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

EXTERN_C unsigned int set_VSSC_FromInfo(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_FromInfo(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}





EXTERN_C wchar_t* get_VSSC_Subject(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_Subject(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


	
}

EXTERN_C unsigned int set_VSSC_Subject(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_Subject(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C wchar_t* get_VSSC_Body(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_Body(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

EXTERN_C unsigned int set_VSSC_Body(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_Body(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C wchar_t* get_VSSC_Date(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_Date(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

EXTERN_C unsigned int set_VSSC_Date(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_Date(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C wchar_t* get_VSSC_SelectedAttachments(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_SelectedAttachments(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

EXTERN_C unsigned int set_VSSC_UnSelectAttachments(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_UnSelectAttachments(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}


EXTERN_C wchar_t* get_VSSC_GetMsg(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_GetMsg(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}

/*
EXTERN_C wchar_t* get_VSSC_DecryptMsg(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;

	assert(pVSSC != NULL);

	hr = pVSSC->get_DecryptMsg(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}
*/

EXTERN_C wchar_t* get_VSSC_AttachedFileList(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_AttachedFileList(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;


}


EXTERN_C unsigned int set_VSSC_MsgPostData(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_MsgPostData(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C unsigned int set_VSSC_CertResolveURL(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_CertResolveURL(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

EXTERN_C short get_VSSC_MsgType(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_MsgType (&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;

}

EXTERN_C unsigned int set_VSSC_MsgType(IVSSC *pVSSC, short newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = newVal;

	hr = pVSSC->put_MsgType(vtName);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}

EXTERN_C unsigned int get_VSSC_CryptStatus(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_CryptStatus(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.lVal;
	else
		return -1;
}


EXTERN_C unsigned int VSSC_Compose(IVSSC *pVSSC, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);

	hr = pVSSC->Compose(&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	
	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}
	


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}

EXTERN_C unsigned int VSSC_SelectAttachments(IVSSC *pVSSC, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);

	hr = pVSSC->SelectAttachments(&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}
	


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}

EXTERN_C short VSSC_SaveAttachment(IVSSC *pVSSC, wchar_t* pFileName, int nLen, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	
	VARIANT varResult, var1;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);


	assert(pVSSC != NULL);
	assert(pFileName != NULL);
	VariantInit(&var1);
	VariantInit(&varResult);
	
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(pFileName,nLen);
	varResult.vt = VT_I2;
	varResult.iVal = 0;

	hr = pVSSC->SaveAttachment(&var1,&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;
}


EXTERN_C unsigned int VSSC_CertificateResolution(IVSSC *pVSSC, wchar_t* in_pvarEmailInfo, int nLen, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	
	VARIANT var1;
	VariantInit(&var1);

	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);
	assert(in_pvarEmailInfo != NULL);
	VariantInit(&var1);
		
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(in_pvarEmailInfo,nLen);

	hr = pVSSC->CertificateResolution(&var1, &varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}



EXTERN_C unsigned int VSSC_SMIMECertificateResolution(IVSSC *pVSSC, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	
	assert(pVSSC != NULL);
	
	hr = pVSSC->SMIMECertificateResolution(&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;
}


EXTERN_C short VSSC_Decompose(IVSSC *pVSSC, wchar_t* i_pvarSMIMEMsg, int nLen, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	
	VARIANT varResult, var1;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);
	assert(i_pvarSMIMEMsg != NULL);
	VariantInit(&var1);
	VariantInit(&varResult);
		
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(i_pvarSMIMEMsg,nLen);
	varResult.vt = VT_I2;
	varResult.iVal = 0;

	hr = pVSSC->Decompose(&var1,&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;

}



EXTERN_C unsigned int VSSC_Initialize(IVSSC *pVSSC, int i_pMsgObjID, short i_pMode, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var1, var2;
	VARIANT varAppStatus;

	assert(pVSSC != NULL);
	VariantInit(&var1);
	VariantInit(&var2);
	VariantInit(&varAppStatus);

		
	var1.vt = VT_I4;
	var1.iVal = i_pMsgObjID;
	var2.vt = VT_I2;
	var2.iVal = i_pMode;

	
	hr = pVSSC->Initialize(&var1, &var2, &varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	
	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}
	

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;


}

EXTERN_C unsigned int VSSC_StoreAll(IVSSC *pVSSC, short i_pModeType, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var2;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);


	assert(pVSSC != NULL);
	VariantInit(&var2);
		
	var2.vt = VT_I2;
	var2.iVal = i_pModeType;
	
	hr = pVSSC->StoreAll(&var2, &varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;


}


EXTERN_C unsigned int set_VSSC_UseProxyRecipCert(IVSSC *pVSSC, int newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_I2;
	var.iVal = newVal;

	hr = pVSSC->put_UseProxyRecipCert(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;



}


EXTERN_C unsigned int VSSC_InternetInitialize(IVSSC *pVSSC, wchar_t* in_pvarURL, int nLen1,
											  wchar_t* in_pvarMethod, int nLen2,
											  wchar_t* in_pvarPostData, int nLen3, wchar_t** ppwstrErrString)
{
	HRESULT hr;
 	unsigned int retVal = VS_NO_ERROR;
	VARIANT var1, var2, var3;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);
	assert(in_pvarURL != NULL);
	assert(in_pvarMethod != NULL);
	assert(in_pvarPostData != NULL);
	VariantInit(&var1);
	VariantInit(&var2);
	VariantInit(&var3);
	
	
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(in_pvarURL,nLen1);

	var2.vt = VT_BSTR;
	var2.bstrVal = SysAllocStringLen(in_pvarMethod,nLen2);

	var3.vt = VT_BSTR;
	var3.bstrVal = SysAllocStringLen(in_pvarPostData,nLen3);

	hr = pVSSC->InternetInitialize(&var1,&var2,&var3, &varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}

EXTERN_C unsigned int VSSC_InternetSendRequest(IVSSC *pVSSC, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);

	assert(pVSSC != NULL);
		
	
	hr = pVSSC->InternetSendRequest(&varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;


}


EXTERN_C unsigned int get_VSSC_MsgObjID(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_MsgObjID(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.iVal;
	else
		return -1;
}

EXTERN_C unsigned int get_VSSC_MsgBlobSize(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_MsgBlobSize(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.lVal;
	else
		return -1;

}

EXTERN_C unsigned int get_VSSC_InternetDataSize(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_InternetDataSize(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I4) 
		return varResult.lVal;
	else
		return -1;

}

EXTERN_C unsigned int set_VSSC_UseInternetData(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_UseInternetData(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

/*
EXTERN_C wchar_t* get_VSSC_InternetDataAsString(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VARIANT var1;
	VARIANT varResult;

	assert(pVSSC != NULL);

	hr = pVSSC->get_InternetData(&varResult);
	_lastErrCode = hr;

	var.vt = VT_I2;
	var.iVal = 8;
	//if (varResult.vt == VT_ARRAY )
	if (1)
	{
		//return varResult.iVal;
		hr = pVSSC->ChangeVarType(&varResult, &var, &var1);
		
	}
	else
		return (wchar_t*)NULL;



	if (var1.vt == VT_BSTR) 
		return (wchar_t*)var1.bstrVal;
	else
		return (wchar_t*)NULL;

}
*/

EXTERN_C BYTE* get_VSSC_InternetData(IVSSC *pVSSC, int *nLen)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);
	BYTE *pbByte = NULL;

	assert(pVSSC != NULL);

	hr = pVSSC->get_InternetData(&varResult);
	_lastErrCode = hr;

	if(varResult.vt == (VT_ARRAY|VT_UI1))  // (OLE SAFEARRAY)
	{
       
		 void * pArrayData;
		 //Obtain safe pointer to the array
		 SafeArrayAccessData(varResult.parray,&pArrayData);
		 int nLength = varResult.parray->rgsabound[0].cElements;
		 *nLen = nLength;
		 pbByte = (BYTE *)malloc(nLength);
		 memcpy(pbByte, pArrayData, nLength);
		 return pbByte;

         
	}
	else
	{
		return (BYTE*)NULL;
	}

	/*

	if (varResult == VT_ARRAY | VT_UI1) 
	{
		return (BYTE*)varResult.bstrVal;
	}
	else
	{
		return (BYTE*)NULL;
	}
	*/

	
}

EXTERN_C unsigned int VSSC_SelectedAttachmentSize(IVSSC *pVSSC, wchar_t* in_pvarFileName, int nLenString, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	
	VARIANT var1, varResult;
	VARIANT varAppStatus;
	VariantInit(&varAppStatus);
	VariantInit(&varResult);
	VariantInit(&var1);

	assert(pVSSC != NULL);
	assert(in_pvarFileName != NULL);

		
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(in_pvarFileName,nLenString);

	hr = pVSSC->SelectedAttachmentSize(&var1, &varAppStatus, &varResult);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}

	if (varResult.vt == VT_I4)
	{
		retVal = varResult.lVal;
		return retVal;
	}
	else
		return -1;
}


EXTERN_C unsigned int set_VSSC_AddSignerCertificate(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;

	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddSignerCertificate(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}

/*
EXTERN_C unsigned int set_VSSC_AddAuthAttributes(IVSSC *pVSSC, BOOL newVal)
{
		HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddAuthAttributes(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;


}
*/

EXTERN_C unsigned int set_VSSC_AddRFC822Header(IVSSC *pVSSC, BOOL newVal)
{
		HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddRFC822Header(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C unsigned int set_VSSC_AddMIMEHeader(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddMIMEHeader(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C unsigned int set_VSSC_OpaqueSign(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_OpaqueSign(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C unsigned int set_VSSC_AddSenderRecipientInfo(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddSenderRecipientInfo(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int set_VSSC_SCType(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_SCType(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
	
}

EXTERN_C wchar_t* get_VSSC_SCType(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	hr = pVSSC->get_SCType(&var);
	_lastErrCode = hr;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;

}

EXTERN_C unsigned int set_VSSC_CertificateTimeOut(IVSSC *pVSSC, short newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = newVal;

	hr = pVSSC->put_CertificateTimeOut(vtName);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}

EXTERN_C short get_VSSC_CertificateTimeOut(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_CertificateTimeOut(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;

}

EXTERN_C unsigned int set_VSSC_MessageTimeOut(IVSSC *pVSSC, short newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = newVal;

	hr = pVSSC->put_MessageTimeOut(vtName);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C short get_VSSC_MessageTimeOut(IVSSC *pVSSC)
{
	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_MessageTimeOut(&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;
}

EXTERN_C unsigned int VSSC_ClearAll(IVSSC *pVSSC, short newVal, wchar_t** ppwstrErrString)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	VARIANT varAppStatus;
	VariantInit(&varAppStatus);


	assert(pVSSC != NULL);
	var.iVal = newVal;

	hr = pVSSC->ClearAll(&var, &varAppStatus);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));

	_itow(varAppStatus.lVal, pwstrTemp, 16);

	*ppwstrErrString = SysAllocString(pwstrTemp);

	if(pwstrTemp)
	{
		free(pwstrTemp);
	}


	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;

}



EXTERN_C unsigned int set_VSSC_UsePKCS7Certificate(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_UsePKCS7Certificate(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}

EXTERN_C unsigned int set_VSSC_AllowDecryption(IVSSC *pVSSC, short newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = newVal;

	hr = pVSSC->put_AllowDecryption(vtName);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}

EXTERN_C unsigned int set_VSSC_AddSMIMECapabilities(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_AddSMIMECapabilities(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}


EXTERN_C unsigned int set_VSSC_ShowSelIDUI(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_ShowSelIDUI(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int set_VSSC_SupportedPTAVer(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	VariantInit(&vtName);

	assert(pVSSC != NULL);
	assert(pwstrnewVal != NULL);

	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);

	hr = pVSSC->put_SupportedPTAVer(vtName);
	_lastErrCode = hr;

	SysFreeString(vtName.bstrVal);
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}



EXTERN_C short get_VSSC_InstalledPTAVer(IVSSC *pVSSC)
{

	HRESULT hr;
	VARIANT varResult;
	VariantInit(&varResult);

	assert(pVSSC != NULL);
	
	hr = pVSSC->get_InstalledPTAVer (&varResult);
	_lastErrCode = hr;

	if (varResult.vt == VT_I2) 
		return varResult.iVal;
	else
		return -1;

}


EXTERN_C unsigned int set_VSSC_URLEncodeData(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_URLEncodeData(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}



EXTERN_C unsigned int VSSC_ResolveProxyRecipCert(IVSSC *pVSSC, wchar_t* pwstrnewVal, int nLen, wchar_t** ppwstrErrString, wchar_t** ppwstrStatusString)
{

	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var1, var2;
	VARIANT varAppStatus;

	assert(pVSSC != NULL);
	VariantInit(&var1);
	VariantInit(&var2);
	VariantInit(&varAppStatus);

		
	var1.vt = VT_BSTR;
	var1.bstrVal = SysAllocStringLen(pwstrnewVal,nLen);
	
	hr = pVSSC->ResolveProxyRecipCert(&var1, &varAppStatus, &var2);
	_lastErrCode = hr;

	wchar_t* pwstrTemp = NULL;
	wchar_t* pwstrStatus = NULL;

	pwstrTemp = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));
	_itow(varAppStatus.lVal, pwstrTemp, 16);
	*ppwstrErrString = SysAllocString(pwstrTemp);

	pwstrStatus = (wchar_t*)malloc(ERROR_STRING_LEN * sizeof(wchar_t));
	_itow(varAppStatus.lVal, pwstrStatus, 16);
	*ppwstrStatusString = SysAllocString(pwstrStatus);


	if(pwstrTemp)
	{
		free(pwstrTemp);
	}

	if(pwstrStatus)
	{
		free(pwstrStatus);
	}
	

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	return retVal;


}


EXTERN_C unsigned int set_VSSC_UseSimder(IVSSC *pVSSC, BOOL newVal)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT var;
	VariantInit(&var);

	assert(pVSSC != NULL);

	var.vt = VT_BOOL;
	var.iVal = newVal;

	hr = pVSSC->put_UseSimder(var);
	_lastErrCode = hr;
	
	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;

}