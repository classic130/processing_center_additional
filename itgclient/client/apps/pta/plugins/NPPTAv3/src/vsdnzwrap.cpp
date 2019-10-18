#include "ptav3.h"
#include "vsdnotz.h"
#include "nzdllapi_i.c"
#include "vsdnotz_i.c"
#include "vsdnzwrap.h"
#include "global.h"
#include <comdef.h>
#include <assert.h>

#ifdef _NS6_PTA_
extern HRESULT _lastErrCode;
#else
EXTERN_C HRESULT _lastErrCode;
#endif

#ifdef _NS6_PTA_
extern LPSTR szUAgent;
#else
EXTERN_C LPSTR szUAgent;
#endif


IVSNZ* NZ_CreateInstance()
{
	IVSNZ* pVSNZ;
	HRESULT hr;

	hr = CoCreateInstance(CLSID_VSNZ, NULL, CLSCTX_INPROC_SERVER, IID_IVSNZ,(void**)&pVSNZ);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pVSNZ;
}


IVSPTA* NZ_CreatePTAInstance(IVSNZ* pVSNZ)
{
	IVSPTA* pPTA;
	HRESULT hr;

	assert(pVSNZ != NULL);

	hr = pVSNZ->QueryInterface(IID_IVSPTA, (void **)&pPTA);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pPTA;
}


IVSNZUIPrefs* NZ_UIPrefs_GetInstance(IVSNZ* pVSNZ)
{
	IVSNZUIPrefs* pUIPrefs;
	HRESULT hr;

	assert(pVSNZ != NULL);

	hr = pVSNZ->get_IVSNZUIPrefs((IDispatch**)&pUIPrefs);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pUIPrefs;
}


IVSNZAppPrefs* NZ_AppPrefs_GetInstance(IVSNZ* pVSNZ)
{
	IVSNZAppPrefs* pAppPrefs;
	HRESULT hr;

	assert(pVSNZ != NULL);

	hr = pVSNZ->get_IVSNZAppPrefs((IDispatch**)&pAppPrefs);
	_lastErrCode = hr;

	if(hr != S_OK)
	{
		return NULL;
	}
	else
		return pAppPrefs;
}


EXTERN_C unsigned int NZ_Initialize (IVSNZ *pVSNZ)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pVSNZ != NULL);

	hr = pVSNZ->Initialize();
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_Close(IVSNZ *pVSNZ)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;

	assert(pVSNZ != NULL);

	hr = pVSNZ->Close();
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_NotarizationServer(IVSNZ *pVSNZ, wchar_t* pwstrServerName, int nServerName)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtServerName;
	
	assert(pVSNZ != NULL);
	assert(pwstrServerName != NULL);

	vtServerName.vt = VT_BSTR;
	vtServerName.bstrVal = SysAllocStringLen(pwstrServerName, nServerName);

	hr = pVSNZ->put_NotarizationServer(vtServerName);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtServerName.bstrVal))
	SysFreeString(vtServerName.bstrVal);
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_HashAlg(IVSNZ *pVSNZ, wchar_t* pwstrHashAlg, int nHashAlg)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtHashAlg;
	
	assert(pVSNZ != NULL);
	assert(pwstrHashAlg != NULL);

	vtHashAlg.vt = VT_BSTR;
	vtHashAlg.bstrVal = SysAllocStringLen(pwstrHashAlg, nHashAlg);

	hr = pVSNZ->put_HashAlg(vtHashAlg);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtHashAlg.bstrVal))
	SysFreeString(vtHashAlg.bstrVal);
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_DisplayDigitalID(IVSNZ *pVSNZ, int nDisplayID)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtDisplayID;
	
	assert(pVSNZ != NULL);
	
	vtDisplayID.vt = VT_I2;
	vtDisplayID.iVal = nDisplayID;

	hr = pVSNZ->put_DisplayDigitalID(vtDisplayID);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_CRLLocation(IVSNZ *pVSNZ, wchar_t* pwstrCrl, int nCrl)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtCrlLoc;
	
	assert(pVSNZ != NULL);
	assert(pwstrCrl != NULL);

	vtCrlLoc.vt = VT_BSTR;
	vtCrlLoc.bstrVal = SysAllocStringLen(pwstrCrl, nCrl);

	hr = pVSNZ->put_CRLLocation(vtCrlLoc);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtCrlLoc.bstrVal))
	SysFreeString(vtCrlLoc.bstrVal);
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_ValidationPref(IVSNZ *pVSNZ, int ValPref)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtValPref;
	
	assert(pVSNZ != NULL);
	
	vtValPref.vt = VT_I2;
	vtValPref.iVal = ValPref;

	hr = pVSNZ->put_ValidationPreference(vtValPref);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_NotarizationDescription(IVSNZ *pVSNZ, wchar_t* pwstrDescription, int nDescription)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtDescription;
	
	assert(pVSNZ != NULL);
	assert(pwstrDescription != NULL);

	vtDescription.vt = VT_BSTR;
	vtDescription.bstrVal = SysAllocStringLen(pwstrDescription, nDescription);

	hr = pVSNZ->put_NotarizationDescription(vtDescription);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtDescription.bstrVal))
	SysFreeString(vtDescription.bstrVal);
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C wchar_t* NZ_NotarizeDocument(IVSNZ *pVSNZ, wchar_t* pwstrDocName, int nDocName, int uiMask, 
									  int ResponseType)
{
	HRESULT hr;
	OLECHAR wcUAgent[1024];
	IVSNZDllApi* pVSNZDllApi = NULL;
	VARIANT varDocument, varUIMask, varResponseType, varResult, varUAgent;

	assert(pVSNZ != NULL);
	assert(pwstrDocName != NULL);

	// Set the user agent that will be used to send any GET requests to web servers
	hr = pVSNZ->QueryInterface(IID_IVSNZDllApi, (void**)&pVSNZDllApi);
	if(hr == S_OK && szUAgent != NULL)
	{
		if(MultiByteToWideChar(CP_ACP, 0, szUAgent, -1, wcUAgent, 1024))
		{
			varUAgent.vt = VT_BSTR;
			varUAgent.bstrVal = SysAllocStringLen(wcUAgent, wcslen(wcUAgent));

			pVSNZDllApi->put_UAgent(varUAgent);
			
			VS_PLUGIN_ERASE_BSTR((varUAgent.bstrVal))
			SysFreeString(varUAgent.bstrVal);
		}
	}
	
	varDocument.vt = VT_BSTR;
	varDocument.bstrVal = SysAllocStringLen(pwstrDocName, nDocName);

	varUIMask.vt = VT_I2;
	varUIMask.iVal = uiMask;

	varResponseType.vt = VT_I2;
	varResponseType.iVal = ResponseType;

	hr = pVSNZ->NotarizeDocument(&varDocument, &varUIMask, &varResponseType, &varResult);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((varDocument.bstrVal))
	SysFreeString(varDocument.bstrVal);

	if(pVSNZDllApi)
	{
		pVSNZDllApi->Release();
		pVSNZDllApi = NULL;
	}

	if(varResult.vt == VT_BSTR) 
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C wchar_t* NZ_NotarizeHash(IVSNZ *pVSNZ, wchar_t* pwstrHash, int nHash, int uiMask)
{
	HRESULT hr;
	VARIANT varHash, varUIMask, varResult;

	assert(pVSNZ != NULL);
	assert(pwstrHash != NULL);

	varHash.vt = VT_BSTR;
	varHash.bstrVal = SysAllocStringLen(pwstrHash, nHash);

	varUIMask.vt = VT_I2;
	varUIMask.iVal = uiMask;

	hr = pVSNZ->NotarizeHash(&varHash, &varUIMask, &varResult);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((varHash.bstrVal))
	SysFreeString(varHash.bstrVal);

	if(varResult.vt == VT_BSTR)
		return (wchar_t*)varResult.bstrVal;
	else
		return (wchar_t*)NULL;
}


EXTERN_C unsigned int NZ_VerifyNotarizationRecord(IVSNZ *pVSNZ, wchar_t* pwstrRecord, int nRecord, wchar_t* pwstrDocument, int nDocument, int RecordType, int UIMask)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtRecord, vtDocument, vtRecordType, vtUIMask, varUAgent;
	OLECHAR wcUAgent[1024];
	IVSNZDllApi* pVSNZDllApi = NULL;
	
	assert(pVSNZ != NULL);
	assert(pwstrRecord != NULL);

	// Set the user agent that will be used to send any GET requests to web servers
	hr = pVSNZ->QueryInterface(IID_IVSNZDllApi, (void**)&pVSNZDllApi);
	if(hr == S_OK && szUAgent != NULL)
	{
		if(MultiByteToWideChar(CP_ACP, 0, szUAgent, -1, wcUAgent, 1024))
		{
			varUAgent.vt = VT_BSTR;
			varUAgent.bstrVal = SysAllocStringLen(wcUAgent, wcslen(wcUAgent));

			pVSNZDllApi->put_UAgent(varUAgent);
			
			VS_PLUGIN_ERASE_BSTR((varUAgent.bstrVal))
			SysFreeString(varUAgent.bstrVal);
		}
	}

	vtRecord.vt = VT_BSTR;
	vtRecord.bstrVal = SysAllocStringLen(pwstrRecord, nRecord);

	vtRecordType.vt = VT_I2;
	vtRecordType.iVal = RecordType;

	vtUIMask.vt = VT_I2;
	vtUIMask.iVal = UIMask;

	if(pwstrDocument == NULL)
		vtDocument.vt = VT_EMPTY;
	else
	{
		vtDocument.vt = VT_BSTR;
		vtDocument.bstrVal = SysAllocStringLen(pwstrDocument, nDocument);
	}
	
	hr = pVSNZ->VerifyNotarizationRecord(&vtRecord, &vtDocument, &vtRecordType, &vtUIMask);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtRecord.bstrVal))
	SysFreeString(vtRecord.bstrVal);

	if(vtDocument.vt == VT_BSTR)
		SysFreeString(vtDocument.bstrVal);

	if(pVSNZDllApi)
	{
		pVSNZDllApi->Release();
		pVSNZDllApi = NULL;
	}
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_AddCertificate(IVSNZ *pVSNZ, wchar_t* pwstrCertificate, int nCertificate)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtCertificate;
	
	assert(pVSNZ != NULL);
	assert(pwstrCertificate != NULL);

	vtCertificate.vt = VT_BSTR;
	vtCertificate.bstrVal = SysAllocStringLen(pwstrCertificate, nCertificate);

	hr = pVSNZ->AddNZCertificate(&vtCertificate);
	_lastErrCode = hr;

	VS_PLUGIN_ERASE_BSTR((vtCertificate.bstrVal))
	SysFreeString(vtCertificate.bstrVal);
	
	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	return retVal;
}


EXTERN_C unsigned int NZ_set_UIPrefs_LogoUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrLogoUrl, int nLogoUrl)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtLogoUrl;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrLogoUrl != NULL);

	vtLogoUrl.vt = VT_BSTR;
	vtLogoUrl.bstrVal = SysAllocStringLen(pwstrLogoUrl, nLogoUrl);

	hr = pNZUIPrefs->put_UILogoUrl(vtLogoUrl);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtLogoUrl.bstrVal);
	
	return retVal;
}


EXTERN_C unsigned int NZ_set_UIPrefs_SelFileTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileTitle, int nSelFileTitle)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtSelFileTitle;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrSelFileTitle != NULL);

	vtSelFileTitle.vt = VT_BSTR;
	vtSelFileTitle.bstrVal = SysAllocStringLen(pwstrSelFileTitle, nSelFileTitle);

	hr = pNZUIPrefs->put_UISelFileTitle(vtSelFileTitle);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtSelFileTitle.bstrVal);
	
	return retVal;
}


EXTERN_C unsigned int NZ_set_UIPrefs_SelFileDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileDesc, int nSelFileDesc)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtSelFileDesc;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrSelFileDesc != NULL);

	vtSelFileDesc.vt = VT_BSTR;
	vtSelFileDesc.bstrVal = SysAllocStringLen(pwstrSelFileDesc, nSelFileDesc);

	hr = pNZUIPrefs->put_UISelFileDescription(vtSelFileDesc);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtSelFileDesc.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_SelFileHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrSelFileHelpUrl, int nSelFileHelpUrl)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtSelFileHelpUrl;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrSelFileHelpUrl != NULL);

	vtSelFileHelpUrl.vt = VT_BSTR;
	vtSelFileHelpUrl.bstrVal = SysAllocStringLen(pwstrSelFileHelpUrl, nSelFileHelpUrl);

	hr = pNZUIPrefs->put_UISelFileHelpUrl(vtSelFileHelpUrl);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtSelFileHelpUrl.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ProgressTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressTitle, int nProgressTitle)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtProgressTitle;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrProgressTitle != NULL);

	vtProgressTitle.vt = VT_BSTR;
	vtProgressTitle.bstrVal = SysAllocStringLen(pwstrProgressTitle, nProgressTitle);

	hr = pNZUIPrefs->put_UIProgressTitle(vtProgressTitle);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtProgressTitle.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ProgressDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressDesc, int nProgressDesc)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtProgressDesc;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrProgressDesc != NULL);

	vtProgressDesc.vt = VT_BSTR;
	vtProgressDesc.bstrVal = SysAllocStringLen(pwstrProgressDesc, nProgressDesc);

	hr = pNZUIPrefs->put_UIProgressDescription(vtProgressDesc);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtProgressDesc.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ProgressHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrProgressHelpUrl, int nProgressHelpUrl)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtProgressHelpUrl;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrProgressHelpUrl != NULL);

	vtProgressHelpUrl.vt = VT_BSTR;
	vtProgressHelpUrl.bstrVal = SysAllocStringLen(pwstrProgressHelpUrl, nProgressHelpUrl);

	hr = pNZUIPrefs->put_UIProgressHelpUrl(vtProgressHelpUrl);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtProgressHelpUrl.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptTitle, int nReceiptTitle)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtReceiptTitle;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrReceiptTitle != NULL);

	vtReceiptTitle.vt = VT_BSTR;
	vtReceiptTitle.bstrVal = SysAllocStringLen(pwstrReceiptTitle, nReceiptTitle);

	hr = pNZUIPrefs->put_UIVerifyRcptTitle(vtReceiptTitle);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtReceiptTitle.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptDesc(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptDesc, int nReceiptDesc)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtReceiptDesc;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrReceiptDesc != NULL);

	vtReceiptDesc.vt = VT_BSTR;
	vtReceiptDesc.bstrVal = SysAllocStringLen(pwstrReceiptDesc, nReceiptDesc);

	hr = pNZUIPrefs->put_UIVerifyRcptDescription(vtReceiptDesc);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtReceiptDesc.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_ReceiptHelpUrl(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrReceiptHelpUrl, int nReceiptHelpUrl)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtReceiptHelpUrl;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrReceiptHelpUrl != NULL);

	vtReceiptHelpUrl.vt = VT_BSTR;
	vtReceiptHelpUrl.bstrVal = SysAllocStringLen(pwstrReceiptHelpUrl, nReceiptHelpUrl);

	hr = pNZUIPrefs->put_UIVerifyRcptHelpUrl(vtReceiptHelpUrl);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtReceiptHelpUrl.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_UIPrefs_WizardTitle(IVSNZUIPrefs* pNZUIPrefs, wchar_t* pwstrWizardTitle, int nWizardTitle)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	VARIANT vtWizardTitle;
	
	assert(pNZUIPrefs != NULL);
	assert(pwstrWizardTitle != NULL);

	vtWizardTitle.vt = VT_BSTR;
	vtWizardTitle.bstrVal = SysAllocStringLen(pwstrWizardTitle, nWizardTitle);

	hr = pNZUIPrefs->put_UIWizardTitle(vtWizardTitle);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtWizardTitle.bstrVal);
	
	return retVal;
}



EXTERN_C unsigned int NZ_set_ApplicationPref(IVSNZAppPrefs* pNZAppPref, wchar_t* pwstrAppName, int nAppName, wchar_t* pwstrPrefName,
											 int nPrefName, int PrefType, wchar_t* pwstrPrefValue, int nPrefValue)
{
	HRESULT hr;
	unsigned int retVal = VS_NO_ERROR;
	int PreferenceValue;
	VARIANT vtAppName, vtPrefName, vtPrefValue;

	assert(pNZAppPref != NULL);
	assert(pwstrAppName != NULL);
	assert(pwstrPrefName != NULL);
	assert(pwstrPrefValue != NULL);

	vtAppName.vt = VT_BSTR;
	vtAppName.bstrVal = SysAllocStringLen(pwstrAppName, nAppName);

	vtPrefName.vt = VT_BSTR;
	vtPrefName.bstrVal = SysAllocStringLen(pwstrPrefName, nPrefName);

	//If the value to be set is an integer convert 'd' to an integer. The type of
	//value to be set in determined by 'PrefType' (0 = integer, 1 = string)
	if(PrefType == 0)
	{
		PreferenceValue = _wtoi(pwstrPrefValue);
		vtPrefValue.vt = VT_I2;
		vtPrefValue.iVal = PreferenceValue;
	}
	else
	{
		vtPrefValue.vt = VT_BSTR;
		vtPrefValue.bstrVal = SysAllocStringLen(pwstrPrefValue, nPrefValue);
	}

	hr = pNZAppPref->SetApplicationPreference(&vtAppName, &vtPrefName, &vtPrefValue);
	_lastErrCode = hr;

	if(hr != S_OK)
		retVal = VS_GENERIC_ERROR;

	SysFreeString(vtAppName.bstrVal);
	SysFreeString(vtPrefName.bstrVal);

	if(PrefType != 0)
		SysFreeString(vtPrefValue.bstrVal);

	return retVal;
}


EXTERN_C wchar_t* NZ_get_ApplicationPref(IVSNZAppPrefs* pNZAppPref, wchar_t* pwstrAppName, int nAppName, wchar_t* pwstrPrefName, int nPrefName)
{
	HRESULT hr;
	VARIANT vtAppName, vtPrefName, vtPrefType, vtResult;

	assert(pNZAppPref != NULL);
	assert(pwstrAppName != NULL);
	assert(pwstrPrefName != NULL);

	vtAppName.vt = VT_BSTR;
	vtAppName.bstrVal = SysAllocStringLen(pwstrAppName, nAppName);

	vtPrefName.vt = VT_BSTR;
	vtPrefName.bstrVal = SysAllocStringLen(pwstrPrefName, nPrefName);

	hr = pNZAppPref->GetApplicationPreference(&vtAppName, &vtPrefName, &vtPrefType, &vtResult);
	_lastErrCode = hr;

	SysFreeString(vtAppName.bstrVal);
	SysFreeString(vtPrefName.bstrVal);

	if(vtResult.vt == VT_BSTR) 
		return (wchar_t*)vtResult.bstrVal;
	else
		if(vtResult.vt == VT_I2)
		{
			wchar_t wstrPref[32];

			// Convert the result to a BSTR
			_itow(vtResult.iVal, wstrPref, 10);

			vtResult.vt = VT_BSTR;
			vtResult.bstrVal = SysAllocString(wstrPref);

			return (wchar_t*)vtResult.bstrVal;
		}
		else
			return (wchar_t*)NULL;

	return NULL;
}
