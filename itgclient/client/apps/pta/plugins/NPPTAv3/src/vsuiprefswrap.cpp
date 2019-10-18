#include "uiprefs.h"
#include "uiprefs_i.c"
#include "ptav3.h"
#include "vsuiprefswrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

IVSUIPrefs* UIPrefs_GetInstance(IVSPTA* pPTA)
{
	IVSUIPrefs* pUIPrefs;
	HRESULT hr;

	hr = pPTA->get_IVSUIPrefs((IDispatch**)&pUIPrefs);
	//hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSUIPrefs,(void**)&pUIPrefs);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pUIPrefs;
}


EXTERN_C unsigned int UIPrefs_set_UILogoUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_UILogoUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* UIPrefs_get_UILogoUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_UILogoUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}




EXTERN_C unsigned int UIPrefs_set_NewPasswd_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_NewPasswd_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* UIPrefs_get_NewPasswd_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_NewPasswd_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int UIPrefs_set_NewPasswd_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_NewPasswd_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_NewPasswd_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_NewPasswd_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int UIPrefs_set_NewPasswd_OKBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_NewPasswd_OKBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_NewPasswd_OKBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_NewPasswd_OKBtnText (&var);
	_lastErrCode = hr;

	if(hr!=S_OK)
		return -1;
	else
	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}


EXTERN_C unsigned int UIPrefs_set_NewPasswd_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_NewPasswd_CancelBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_NewPasswd_CancelBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	VARIANT var;
	int retVal;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_NewPasswd_CancelBtnText (&var);
	_lastErrCode = hr;

	if((hr==S_OK) && (var.vt == VT_I2))
		retVal =  var.iVal;
	else
		retVal = -1;
	VariantClear (&var);
	return retVal;
}



EXTERN_C unsigned int UIPrefs_set_NewPasswd_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_NewPasswd_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_NewPasswd_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_NewPasswd_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_RvwMsg_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_RvwMsg_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_RvwMsg_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_RvwMsg_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}



EXTERN_C unsigned int UIPrefs_set_RvwMsg_OKBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_RvwMsg_OKBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_RvwMsg_OKBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	VARIANT var;
	int retVal;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_RvwMsg_OKBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2) )
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_RvwMsg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_RvwMsg_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}

EXTERN_C wchar_t* UIPrefs_get_RvwMsg_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_RvwMsg_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}




EXTERN_C unsigned int UIPrefs_set_RvwMsg_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;

	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_RvwMsg_CancelBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_RvwMsg_CancelBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	VARIANT var;
	int retVal;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_RvwMsg_CancelBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt==VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}



EXTERN_C unsigned int UIPrefs_set_RvwMsg_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_RvwMsg_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_RvwMsg_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_RvwMsg_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SelID_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_SelID_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_SelID_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_SelID_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SgnDlg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_SgnDlg_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_SgnDlg_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_SgnDlg_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SelID_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_SelID_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_SelID_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_SelID_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SelID_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_SelID_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_SelID_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_SelID_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SelID_OKBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_SelID_OKBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_SelID_OKBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_SelID_OKBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_SelID_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_SelID_CancelBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_SelID_CancelBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_SelID_CancelBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2) )
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_SelID_ChkBoxText(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_SelID_ChkBoxText(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_SelID_ChkBoxText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_SelID_ChkBoxText (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_SelID_ShowDefChkBox (IVSUIPrefs *pUIPrefs, BOOL boolShowDef)
{
	//_bstr_t tempbstr(pwstrName);
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varBox;

	assert(pUIPrefs != NULL);

	varBox.vt = VT_BOOL;
	varBox.boolVal = boolShowDef;
	hr = pUIPrefs->put_SelID_ShowDefChkBox (varBox);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear (&varBox);
	return retVal;
}


EXTERN_C BOOL UIPrefs_get_SelID_ShowDefChkBox (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	BOOL boolShowDef;
	VARIANT varBox;

	assert(pUIPrefs != NULL);

	hr = pUIPrefs->get_SelID_ShowDefChkBox (&varBox);
	_lastErrCode = hr;

	if(hr!=S_OK)
		boolShowDef = -1;
	else
		if (varBox.vt != VT_BOOL)
			boolShowDef = -1;
		else
			boolShowDef = varBox.boolVal;

	VariantClear(&varBox);

	return boolShowDef;
}


EXTERN_C unsigned int UIPrefs_set_LgnDlg_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_LgnDlg_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_LgnDlg_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_LgnDlg_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_OpenProf_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_OpenProf_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_OpenProf_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_OpenProf_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_OpenProf_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_OpenProf_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_OpenProf_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_OpenProf_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_OpenProf_OKBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_OpenProf_OKBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_OpenProf_OKBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_OpenProf_OKBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_OpenProf_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_OpenProf_CancelBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_OpenProf_CancelBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_OpenProf_CancelBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_OpenProf_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_OpenProf_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_OpenProf_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_OpenProf_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_TitleFont(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_TitleFont(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_TitleFont (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_TitleFont (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C unsigned int UIPrefs_set_TextFont(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_TextFont(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_TextFont (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_TextFont (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_BtnFont(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_BtnFont(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_BtnFont (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_BtnFont (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_Language (IVSUIPrefs *pUIPrefs, int nLanguage)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);

	vtName.vt = VT_I2;
	vtName.iVal = nLanguage;
	hr = pUIPrefs->put_Language(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C int UIPrefs_get_Language (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_Language (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_I2) 
		return var.iVal;
	else
		return -1;
}



EXTERN_C unsigned int UIPrefs_set_IntroDlg_Title (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_IntroDlg_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_IntroDlg_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_IntroDlg_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_IntroDlg_Text (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_IntroDlg_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_IntroDlg_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_IntroDlg_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_IntroDlg_HelpUrl (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_IntroDlg_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	VariantClear(&vtName);
	return retVal;
}



EXTERN_C wchar_t* UIPrefs_get_IntroDlg_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_IntroDlg_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C unsigned int UIPrefs_set_CreateNewProf_Title (IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_CreateNewProf_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_CreateNewProf_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_CreateNewProf_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_ChangePasswd_Title(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_ChangePasswd_Title(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_Title (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_ChangePasswd_Title (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_ChangePasswd_Text(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_ChangePasswd_Text(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_Text (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_ChangePasswd_Text (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_ChangePasswd_OKBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_ChangePasswd_OKBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_ChangePasswd_OKBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_ChangePasswd_OKBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_ChangePasswd_CancelBtnText(IVSUIPrefs *pUIPrefs, int nText)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	
	assert(pUIPrefs != NULL);

	VariantInit (&vtName);
	vtName.vt = VT_I2;
	vtName.iVal = nText;
	hr = pUIPrefs->put_ChangePasswd_CancelBtnText(vtName);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;
	
	VariantClear(&vtName);
	return retVal;
}


EXTERN_C int UIPrefs_get_ChangePasswd_CancelBtnText (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT var;

	assert(pUIPrefs != NULL);

	VariantInit (&var);
	hr = pUIPrefs->get_ChangePasswd_CancelBtnText (&var);
	_lastErrCode = hr;

	if( (hr==S_OK) && (var.vt == VT_I2))
		retVal = var.iVal;
	else
		retVal = -1;
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_ChangePasswd_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_ChangePasswd_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_ChangePasswd_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_ChangePasswd_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}

EXTERN_C unsigned int UIPrefs_set_Timeout_HelpUrl(IVSUIPrefs *pUIPrefs, wchar_t* pwstrName, int nLen)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtName;
	//BSTR bstrName;
	assert(pUIPrefs != NULL);
	assert(pwstrName != NULL);

	//VariantInit (&vtName);
	vtName.vt = VT_BSTR;
	vtName.bstrVal = SysAllocStringLen(pwstrName,nLen);
	hr = pUIPrefs->put_Timeout_HelpUrl(vtName);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;
	SysFreeString(vtName.bstrVal);
	//VariantClear(&vtName);
	return retVal;
}


EXTERN_C wchar_t* UIPrefs_get_Timeout_HelpUrl (IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	//BSTR bstrName;
	VARIANT var;

	assert(pUIPrefs != NULL);

	//VariantInit (&var);
	hr = pUIPrefs->get_Timeout_HelpUrl (&var);
	_lastErrCode = hr;

	//if(hr!=S_OK)
	//	bstrName = NULL;

	if (var.vt == VT_BSTR) 
		return (wchar_t*)var.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int UIPrefs_set_EnableTopMost (IVSUIPrefs *pUIPrefs, BOOL boolEnableTopMost)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT varTopMost;

	assert(pUIPrefs != NULL);

	varTopMost.vt = VT_BOOL;
	varTopMost.boolVal = boolEnableTopMost;
	hr = pUIPrefs->put_EnableTopMostWindow (varTopMost);
	_lastErrCode = hr;

	if(hr!=S_OK)
		retVal = VS_GENERIC_ERROR;

	VariantClear (&varTopMost);
	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_SignTransDlgWidth(IVSUIPrefs *pUIPrefs, int nWidth)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtWidth;

	VariantInit(&vtWidth);

	assert(pUIPrefs != NULL);

	vtWidth.vt = VT_I2;
	vtWidth.iVal = nWidth;
	hr = pUIPrefs->put_SignTransDlgWidth(vtWidth);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;

	VariantClear(&vtWidth);

	return retVal;
}


EXTERN_C int UIPrefs_get_SignTransDlgWidth(IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT vtWidth;

	assert(pUIPrefs != NULL);

	hr = pUIPrefs->get_SignTransDlgWidth(&vtWidth);
	_lastErrCode = hr;

	if((hr == S_OK) && (vtWidth.vt == VT_I2))
		retVal = vtWidth.iVal;
	else
		retVal = -1;

	return retVal;
}


EXTERN_C unsigned int UIPrefs_set_SignTransDlgHeight(IVSUIPrefs *pUIPrefs, int nHeight)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtHeight;

	VariantInit(&vtHeight);

	assert(pUIPrefs != NULL);

	vtHeight.vt = VT_I2;
	vtHeight.iVal = nHeight;
	hr = pUIPrefs->put_SignTransDlgHeight(vtHeight);
	_lastErrCode = hr;

	if(hr!=VS_NO_ERROR)
		retVal = hr;

	VariantClear(&vtHeight);

	return retVal;
}


EXTERN_C int UIPrefs_get_SignTransDlgHeight(IVSUIPrefs *pUIPrefs)
{
	HRESULT hr;
	int retVal;
	VARIANT vtHeight;

	assert(pUIPrefs != NULL);

	hr = pUIPrefs->get_SignTransDlgHeight(&vtHeight);
	_lastErrCode = hr;

	if((hr == S_OK) && (vtHeight.vt == VT_I2))
		retVal = vtHeight.iVal;
	else
		retVal = -1;

	return retVal;
}