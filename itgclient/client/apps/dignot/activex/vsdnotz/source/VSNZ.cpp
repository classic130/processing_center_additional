// VSNZ.cpp : Implementation of CVSNZ
#include "stdafx.h"
#include <comutil.h>
#include <mshtml.h>
#include "Vsdnotz.h"
#include "ptav3.h"
#include "roamprefs.h"
#include "ptaerrs.h"
#include "vsps_defines.h"
#include "nzuser.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzmacros.h"
#include "nzerrs.h"
#include "nzdefines.h"
#include "VSNZ.h"
#include "ptav3_i.c"
#include "ptadllapi_i.c"
#include "uiprefs_i.c"
#include "nzuiprefs_i.c"
#include "nzapprefs_i.c"
#include "nzdllapi_i.c"
#include "dnzuistructs.h"
#include "DNZUI.h"
#include "nzrecord.h"
#include "nzdatacc.h"


/////////////////////////////////////////////////////////////////////////////
// CVSNZ

HRESULT CVSNZ::FinalConstruct()
{
	IUnknown* pUnkOuter = GetControllingUnknown();

	HRESULT hRes = CoCreateInstance(CLSID_VSPTA, pUnkOuter, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&m_pUnkPta);
	if(hRes != S_OK)
		return hRes;

	return S_OK;	
}


void CVSNZ::FinalRelease()
{
	if(m_pUnkPta)
	{
		m_pUnkPta.Release();
		m_pUnkPta = NULL;
	}
}


STDMETHODIMP CVSNZ::Initialize()
{
	m_bInitialized = TRUE;	

	return S_OK;
}


STDMETHODIMP CVSNZ::Close()
{
	m_bInitialized = FALSE;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_NotarizationServer(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL || newVal.bstrVal == _bstr_t(""))
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrNzServer = newVal.bstrVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_HashAlg(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrHashAlg = newVal.bstrVal;

	// The notarization server supports only 'SHA1' and 'MD5'
	if(_strnicmp(m_UsrSettings.m_bstrHashAlg, "MD5", 3) && 
		_strnicmp(m_UsrSettings.m_bstrHashAlg, "SHA1", 4))
	{
		m_UsrSettings.m_bstrHashAlg = "MD5";
		return E_NZINVALIDALG;
	}

	return S_OK;
}


STDMETHODIMP CVSNZ::put_DisplayDigitalID(VARIANT newVal)
{
	if(newVal.vt != VT_I2)
		return E_NZINVALIDARGS;

	m_UsrSettings.m_dwDisplayDigID = newVal.iVal;

	return S_OK;
}


/*
O/P -	'pVal'	:	The IDispatch pointer of the required interface.
Return -	An hresult indicating success of the operation.
Working -	This function gets the IVSPTA interface. This interface is exposed from
			digital notarization by means of a COM reuse mechanism called aggregation.
			This interface will be used to do crypto, certificate selection operations.
*/
STDMETHODIMP CVSNZ::get_IVSNZPta(IDispatch **pVal)
{
	HRESULT hr = S_OK;
	IVSPTADllApi *pPTADllApi = NULL;
	VARIANT varClientSite;

	VariantInit(&varClientSite);
	
	do
	{
		*pVal = NULL;
		*pVal = (IDispatch*)_GetInterface(IID_IVSPTA);
		if(!*pVal)
		{
			hr = E_NOINTERFACE;
			break;
		}

		// Set the client site for the aggregated PTA. Need to do this because when the PTA 
		// is used in this way it is not contained in the IE activex container so the 
		// 'm_spClientSite' is not set. Here we set the 'm_spClientSite' of the PTA to the 
		// 'm_spClientSite' of the digital notarization control
		(*pVal)->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		if(!pPTADllApi)
		{
			hr = E_NOINTERFACE;
			break;
		}

		varClientSite.vt = VT_UNKNOWN;
		varClientSite.punkVal = m_spClientSite;
	
		hr = pPTADllApi->put_OleClientSite(varClientSite);
		CHECK_HRESULT_BREAK

	}while(0);


	//VariantClear(&varClientSite);

	RELEASE_INTERFACE_PTR(pPTADllApi)

	return hr;
}


/*
O/P -	'pVal'	:	The IDispatch pointer of the required interface.
Return -	An hresult indicating success of the operation.
Working -	This function gets the IID_IVSNZUIPrefs interface. This interface is used to
			set the UI preferences
*/
STDMETHODIMP CVSNZ::get_IVSNZUIPrefs(IDispatch **pVal)
{
	*pVal = (IDispatch*)_GetInterface(IID_IVSNZUIPrefs);
	if(!*pVal)
		return E_NOINTERFACE;  
	
	return S_OK;
}



/*
O/P -	'pVal'	:	The IDispatch pointer of the required interface.
Return -	An hresult indicating success of the operation.
Working -	This function gets the IID_IVSNZAppPrefs interface. This interface is used 
			to set the application preferences
*/
STDMETHODIMP CVSNZ::get_IVSNZAppPrefs(IDispatch **pVal)
{
	*pVal = (IDispatch*)_GetInterface(IID_IVSNZAppPrefs);
	if(!*pVal)
		return E_NOINTERFACE;  
	
	return S_OK;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
STDMETHODIMP CVSNZ::put_CRLLocation(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrCrl = newVal.bstrVal;

	return S_OK;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
STDMETHODIMP CVSNZ::NotarizeDocument(VARIANT *i_pvarDocument, VARIANT *i_pvarUIMask, VARIANT *i_pvarResponseType, VARIANT *o_pvarResponse)
{
	HRESULT hr = S_OK;
	LPTSTR pSelFiles;
	PBYTE pbRecord = NULL, pbEncodedRecord = NULL;
	DWORD dwRecordLen = 0, dwEncodedLen = 0;
	IVSPTA* pVSPta = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	_bstr_t bstrRecord = "", bstrDocument = "";
	VARIANT varAttachedSig, varShowSignUI;

	VariantInit(&varAttachedSig);
	VariantInit(&varShowSignUI);

	do
	{
		if(!i_pvarDocument || !i_pvarUIMask || !i_pvarResponseType || !o_pvarResponse)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_pvarDocument->vt != VT_BSTR || i_pvarUIMask->vt != VT_I2 || i_pvarResponseType->vt != VT_I2)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(i_pvarResponseType->iVal == RT_NZRECORD)
		{
			hr = E_NZTYPENOTSUPPORTED;
			break;
		}
		
		if(i_pvarResponseType->iVal != RT_NZRESPONSE /*&& i_pvarResponseType->iVal != RT_NZRECORD*/)
		{
			hr = E_NZINVALIDRESPTYPE;
			break;
		}

		o_pvarResponse->vt = VT_EMPTY;
		bstrDocument = i_pvarDocument->bstrVal;
		
		pVSPta = (IVSPTA*)_GetInterface(IID_IVSPTA);
		if(!pVSPta)
		{
			hr = E_NOINTERFACE;
			break;
		}

		pVSPta->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		if(!pPTADllApi)
		{
			hr = E_NOINTERFACE;
			break;
		}

		varAttachedSig.vt = VT_BOOL;
		varAttachedSig.boolVal = TRUE;
		hr = pPTADllApi->put_DoAttachedSig(varAttachedSig);
		CHECK_HRESULT_BREAK

		varShowSignUI.vt = VT_BOOL;
		varShowSignUI.boolVal = FALSE;
		hr = pPTADllApi->put_ShowSignUI(varShowSignUI);
		CHECK_HRESULT_BREAK

		pSelFiles = (LPTSTR)bstrDocument;
		
		// Should the main function take in an array instead of just one file ?
		if(bstrDocument == _bstr_t(""))
			hr = _DoDigitalNotarization(pVSPta, NULL, NULL, 0, FALSE, i_pvarUIMask->iVal, (ResponseType)i_pvarResponseType->iVal, FALSE, &pbRecord, &dwRecordLen);
		else
			hr = _DoDigitalNotarization(pVSPta, (LPCTSTR*)&pSelFiles, NULL, 1, FALSE, i_pvarUIMask->iVal, (ResponseType)i_pvarResponseType->iVal, FALSE, &pbRecord, &dwRecordLen);

		CHECK_HRESULT_BREAK

		_Base64Encode((char *)pbRecord, dwRecordLen, NULL, &dwEncodedLen);
		pbEncodedRecord = (PBYTE)malloc(dwEncodedLen + 1);
		CHECK_MEM_BREAK(pbEncodedRecord)

		_Base64Encode((char *)pbRecord, dwRecordLen, (char *)pbEncodedRecord, &dwEncodedLen);
		pbEncodedRecord[dwEncodedLen] = '\0';

		bstrRecord = (char *)pbEncodedRecord;
		o_pvarResponse->vt = VT_BSTR;
		o_pvarResponse->bstrVal = bstrRecord.copy();

	}while(0);

	FREE_MEMORY(pbEncodedRecord)
	FREE_MEMORY(pbRecord)

	VariantClear(&varAttachedSig);
	VariantClear(&varShowSignUI);

	RELEASE_INTERFACE_PTR(pVSPta)
	RELEASE_INTERFACE_PTR(pPTADllApi)
	
	return hr;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
STDMETHODIMP CVSNZ::NotarizeHash(VARIANT *i_pvarHash, VARIANT *i_pvarUIMask, VARIANT *o_pvarResponse)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPta = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	PBYTE pbRecord = NULL, pbEncodedRecord = NULL, pbHashVal = NULL;
	DWORD dwRecordLen = 0, dwEncodedLen = 0, dwHashLen = 0;
	VARIANT varAttachedSig, varShowSignUI;
	_bstr_t bstrRecord = "", bstrHashVal = "";

	VariantInit(&varAttachedSig);
	VariantInit(&varShowSignUI);
	
	do
	{
		if(!i_pvarHash || !i_pvarUIMask || !o_pvarResponse)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_pvarHash->vt != VT_BSTR || i_pvarUIMask->vt != VT_I2)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		bstrHashVal = i_pvarHash->bstrVal;

		if(bstrHashVal == _bstr_t(""))
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(m_UsrSettings.m_bstrHashAlg == _bstr_t(""))
		{
			hr = E_NZNOHASHALG;
			break;
		}

		o_pvarResponse->vt = VT_EMPTY;

		pVSPta = (IVSPTA*)_GetInterface(IID_IVSPTA);
		if(!pVSPta)
		{
			hr = E_NOINTERFACE;
			break;
		}

		pVSPta->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		if(!pPTADllApi)
		{
			hr = E_NOINTERFACE;
			break;
		}

		varAttachedSig.vt = VT_BOOL;
		varAttachedSig.boolVal = TRUE;
		hr = pPTADllApi->put_DoAttachedSig(varAttachedSig);
		CHECK_HRESULT_BREAK

		varShowSignUI.vt = VT_BOOL;
		varShowSignUI.boolVal = FALSE;
		hr = pPTADllApi->put_ShowSignUI(varShowSignUI);
		CHECK_HRESULT_BREAK

		// Decode the base64 encoded hash
		_Base64Decode(bstrHashVal, bstrHashVal.length(), NULL, &dwHashLen);
		pbHashVal = (PBYTE)malloc(dwHashLen);
		CHECK_MEM_BREAK(pbHashVal)

		_Base64Decode(bstrHashVal, bstrHashVal.length(), (char*)pbHashVal, &dwHashLen);

		// Check if the hash algorithm corresponds to the hash length obtained
		if(_strnicmp(m_UsrSettings.m_bstrHashAlg, "MD2", 3) == 0)
		{
			if(dwHashLen != HASH_MD2_LENGTH)
			{
				hr = E_NZINVALIDHASH;
				break;
			}
		}
		else
			if(_strnicmp(m_UsrSettings.m_bstrHashAlg, "MD4", 3) == 0)
			{
				if(dwHashLen != HASH_MD4_LENGTH)
				{
					hr = E_NZINVALIDHASH;
					break;
				}
			}
			else
				if(_strnicmp(m_UsrSettings.m_bstrHashAlg, "MD5", 3) == 0)
				{
					if(dwHashLen != HASH_MD5_LENGTH)
					{
						hr = E_NZINVALIDHASH;
						break;
					}
				}
				else
					if(_strnicmp(m_UsrSettings.m_bstrHashAlg, "SHA1", 4) == 0)
					{
						if(dwHashLen != HASH_SHA1_LENGTH)
						{
							hr = E_NZINVALIDHASH;
							break;
						}
					}
					else
					{
						hr = E_NZINVALIDALG;
						break;
					}

		hr = _DoDigitalNotarization(pVSPta, NULL, &pbHashVal, 1, TRUE, i_pvarUIMask->iVal, RT_NZRESPONSE, FALSE, &pbRecord, &dwRecordLen);
		CHECK_HRESULT_BREAK

		_Base64Encode((char *)pbRecord, dwRecordLen, NULL, &dwEncodedLen);
		pbEncodedRecord = (PBYTE)malloc(dwEncodedLen + 1);
		CHECK_MEM_BREAK(pbEncodedRecord)

		_Base64Encode((char *)pbRecord, dwRecordLen, (char *)pbEncodedRecord, &dwEncodedLen);
		pbEncodedRecord[dwEncodedLen] = '\0';

		bstrRecord = (char *)pbEncodedRecord;
		o_pvarResponse->vt = VT_BSTR;
		o_pvarResponse->bstrVal = bstrRecord.copy();

	}while(0);

	FREE_MEMORY(pbHashVal)
	FREE_MEMORY(pbEncodedRecord)
	FREE_MEMORY(pbRecord)

	VariantClear(&varAttachedSig);
	VariantClear(&varShowSignUI);

	RELEASE_INTERFACE_PTR(pVSPta)
	RELEASE_INTERFACE_PTR(pPTADllApi)

	return hr;
}



/*
I/P -	
O/P -	
Return -	
Working -	
*/
STDMETHODIMP CVSNZ::VerifyNotarizationRecord(VARIANT *i_pvarRecord, VARIANT* i_pvarDocument, VARIANT *i_pvarRecordType, VARIANT *i_pvarUIMask)
{
	HRESULT hr = S_OK;
	_bstr_t bstrRecord = "", bstrDocument = "", bstrErrString = "", bstrErrTitle = "";
	WCHAR *wcErrString = NULL;
	NzDetails NzDetailedInfo;
	CDNZUI* pTheDNZUI = NULL;
	IVSPTA* pVSPTA = NULL;

	NzDetailedInfo.Initialize();

	do
	{
		if(!i_pvarRecord || !i_pvarRecordType || !i_pvarUIMask)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_pvarRecord->vt != VT_BSTR || i_pvarRecordType->vt != VT_I2 || i_pvarUIMask->vt != VT_I2)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(i_pvarRecordType->iVal != NZRECORD_URL && i_pvarRecordType->iVal != NZRECORD_RAW)
		{
			hr = E_INVALIDRECTYPE;
			break;
		}

		bstrRecord = i_pvarRecord->bstrVal;

		if(bstrRecord == _bstr_t(""))
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		// Check if a document against which to verify the notarization record has been
		// passed to us
		if(i_pvarDocument)
		{
			if(i_pvarDocument->vt == VT_BSTR)
				bstrDocument = i_pvarDocument->bstrVal;
		}

		// UIFLAG_SAVE_DOC should always be set if it is a web-verify.
		// Even if it is disabled by the web-page scripts it will be ignored.
		// For Desktop Verification vsdnotz.OpenRecord sets this 
		// member m_boolShowSaveLink flag to false.

		if (m_boolShowSaveLink)
		{
			i_pvarUIMask->iVal = i_pvarUIMask->iVal | UIFLAG_SAVE_DOC;
		}

		hr = _DoRecordVerification(bstrRecord, bstrDocument, (i_pvarRecordType->iVal == NZRECORD_URL ? TRUE : FALSE), m_UsrSettings.m_dwValidationFlags, &NzDetailedInfo);
		CHECK_HRESULT_BREAK

		// Get the PTA pointer
		hr = _InitializePTA(FALSE, &pVSPTA);
		CHECK_HRESULT_BREAK

	}while(0);

	if(i_pvarUIMask->iVal & UIFLAG_VERIFICATION)
	{
		if(hr != S_OK)
		{
			// The document that was notarized is not present at the location specified in the receipt
			// Let calling function decide how to handle this rather than showing error here
			if(hr != E_NZDOCOPENFAILED)
			{
				// Load the message box title first
				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_DNZ_ERROR, &wcErrString) == S_OK)
				{
					bstrErrTitle = wcErrString;
					FREE_MEMORY(wcErrString)
				}

				// Handle some of the specific errors here
				bstrErrString = _HandleError(hr, &NzDetailedInfo);

				if(bstrErrString == _bstr_t(""))
				{
					// Unhandled error code, give a general error message
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VERF_GENERAL_ERR, &wcErrString) == S_OK)
						bstrErrString = wcErrString;
				}

				::MessageBox(GetFocus(), bstrErrString, bstrErrTitle, MB_ICONERROR);
			}
		}
		else
		{
			pTheDNZUI = (CDNZUI*) new (CDNZUI);
			hr = _ShowVerificationUI(pTheDNZUI,pVSPTA, i_pvarUIMask->iVal, &NzDetailedInfo);
		}
	}

	NzDetailedInfo.Clear();

	DELETE_MEMORY(pTheDNZUI);

	FREE_MEMORY(wcErrString)

	_UnInitializePTA(pVSPTA);
	
	return hr;
}



STDMETHODIMP CVSNZ::put_ValidationPreference(VARIANT newVal)
{
	if(newVal.vt != VT_I2)
		return E_NZINVALIDARGS;

	m_UsrSettings.m_dwValidationFlags = newVal.iVal;

	return S_OK;
}


STDMETHODIMP CVSNZ::put_NotarizationDescription(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_UsrSettings.m_bstrReceiptDescription = newVal.bstrVal;

	return S_OK;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
STDMETHODIMP CVSNZ::AddNZCertificate(VARIANT *i_pvarCertificate)
{
	HRESULT hr = S_OK;
	DWORD dwCertLen = 0;
	PBYTE pbDecodedCert = NULL;
	_bstr_t bstrCertificate = "";
	LPTSTR pStoreName = "CA";

	do
	{
		if(!i_pvarCertificate)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_pvarCertificate->vt != VT_BSTR)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(i_pvarCertificate->bstrVal == NULL)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		bstrCertificate = i_pvarCertificate->bstrVal;

		if(bstrCertificate == _bstr_t(""))
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		// Base64 decode the certificate
		_Base64Decode(bstrCertificate, bstrCertificate.length(), NULL, &dwCertLen);

		pbDecodedCert = (PBYTE)malloc(dwCertLen);
		CHECK_MEM_BREAK(pbDecodedCert)

		_Base64Decode(bstrCertificate, bstrCertificate.length(), (char *)pbDecodedCert, &dwCertLen);

		hr = _AddCertToStore(pStoreName, pbDecodedCert, dwCertLen);
		CHECK_HRESULT_BREAK

	}while(0);

	FREE_MEMORY(pbDecodedCert)

	return hr;
}


/*			----		Private member function of CVSNZ	----			*/


/*
I/P -	'refIID'	:	IID of the interface required.
Return -	IDispatch pointer of the interface required.
Working -	This function returns the IDispatch pointer of the required interface.
*/
IDispatch* CVSNZ::_GetInterface(REFIID i_refIId)
{
	void* pvInterface = NULL;
	QueryInterface(i_refIId, &pvInterface);
	return (IDispatch*)pvInterface;
}


/*
O/P -	'o_pVSPta'	:	Is a pointer to the PTA 'IVSPTA' interface.
Return -	An hresult indicating success of the operation.
Working -	This function obtains a pointer to the main PTA interface, it initializes the
			PTA using settings stored in 'm_UsrSettings' member. This is a helper function
			called to initialize the PTA for crypto operation when notarization is being done
			using the context menu.
*/
HRESULT CVSNZ::_InitializePTA(BOOL i_bDisplayDigID, IVSPTA** o_pVSPta, BOOL bCloseProfile)
{
	HRESULT hr = S_FALSE;
	IVSPTA* pPTA = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSProfMgmt *pIVSProfMgmt = NULL;
	IVSRoamPrefs *pIVSRoamPrefs = NULL;
	IVSSrchCrit *pIVSSrchCrit = NULL;
	IVSUIPrefs *pIVSUIPref = NULL;
	DATE todayDate;
	UDATE todayUDate;
	WCHAR* wcString = NULL;
	_bstr_t bstrErrTitle = "", bstrErrMessage = "";
	UINT uErrString = 0;
	VARIANT varAppName, varHostName, varUseCapi, varProfOpen, varIsRoaming, varIsLocal;
	VARIANT varAttachedSig, varShowSignUI, varClientInfo, varClientInfoSig, varIssuerDN;
	VARIANT varDateFlag, varRenewedFlag, varLogoUrl, varSelIdTitle, varOpenProfTitle;
	VARIANT varLgnDlgTitle, varSignDlgTitle, varSelIDChkBoxText, varLang;

	VariantInit(&varAppName);
	VariantInit(&varHostName);
	VariantInit(&varUseCapi);
	VariantInit(&varProfOpen);
	VariantInit(&varIsRoaming);
	VariantInit(&varIsLocal);
	VariantInit(&varAttachedSig);
	VariantInit(&varShowSignUI);
	VariantInit(&varClientInfo);
	VariantInit(&varClientInfoSig);
	VariantInit(&varIssuerDN);
	VariantInit(&varDateFlag);
	VariantInit(&varRenewedFlag);
	VariantInit(&varLogoUrl);
	VariantInit(&varSelIdTitle);
	VariantInit(&varOpenProfTitle);
	VariantInit(&varLgnDlgTitle);
	VariantInit(&varSignDlgTitle);
	VariantInit(&varSelIDChkBoxText);
	VariantInit(&varLang);
	
	do
	{
		CHECK_NULL_PTR_BREAK(o_pVSPta)

		m_UsrSettings.Dump("CVSNZ::_InitializePTA()");

		pPTA = (IVSPTA*)_GetInterface(IID_IVSPTA);
		if(!pPTA)
		{
			hr = E_NOINTERFACE;
			break;
		}
		
		varAppName.vt = VT_BSTR;
		varAppName.bstrVal = m_UsrSettings.m_bstrAppContext.copy();

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = (SHORT)m_UsrSettings.m_dwCapi;

		hr = pPTA->Initialize(&varAppName, &varUseCapi);

		// If script has called initialize and we end up calling it again, as is the case when 
		// VerifyRecord() is called.
		if(hr == E_INITIALIZED)
		{
			*o_pVSPta = pPTA;
			hr = S_OK;
			break;
		}

		CHECK_HRESULT_BREAK

		hr = pPTA->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		CHECK_HRESULT_BREAK

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = SysAllocString(L"nzclient");

		hr = pPTADllApi->put_HostFQDN(varHostName);
		CHECK_HRESULT_BREAK

		varAttachedSig.vt = VT_BOOL;
		varAttachedSig.boolVal = TRUE;
		hr = pPTADllApi->put_DoAttachedSig(varAttachedSig);
		CHECK_HRESULT_BREAK

		varShowSignUI.vt = VT_BOOL;
		varShowSignUI.boolVal = FALSE;
		hr = pPTADllApi->put_ShowSignUI(varShowSignUI);
		CHECK_HRESULT_BREAK

		if(m_UsrSettings.m_dwCapi == NON_CAPI)
		{
			hr = pPTA->get_IVSProfMgmt((IDispatch**)&pIVSProfMgmt);
			CHECK_HRESULT_BREAK

			varProfOpen.vt = VT_I2;
			varProfOpen.iVal = PROF_OPEN_FLAG;

			if(bCloseProfile)
				pIVSProfMgmt->CloseProfile();

			hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
			if(hr != E_CARDALREADYOPEN)		// For a profile already open we would get this error
				CHECK_HRESULT_BREAK

			if(m_UsrSettings.m_bstrClientInfo != _bstr_t("") && m_UsrSettings.m_bstrClientInfoSig != _bstr_t(""))
			{
				varIsRoaming.vt = VT_BOOL;
				varIsRoaming.boolVal = TRUE;

				hr = pPTA->get_IVSRoamPrefs((IDispatch**)&pIVSRoamPrefs);
				CHECK_HRESULT_BREAK

				varClientInfo.vt = VT_BSTR;
				varClientInfo.bstrVal = m_UsrSettings.m_bstrClientInfo.copy();

				hr = pIVSRoamPrefs->put_ClientInfo(varClientInfo);
				CHECK_HRESULT_BREAK

				varClientInfoSig.vt = VT_BSTR;
				varClientInfoSig.bstrVal = m_UsrSettings.m_bstrClientInfoSig.copy();

				hr = pIVSRoamPrefs->put_ClientInfoSig(varClientInfoSig);
				CHECK_HRESULT_BREAK
			}
			else
			{
				varIsRoaming.vt = VT_BOOL;
				varIsRoaming.boolVal = FALSE;
			}

			hr = pIVSProfMgmt->put_RoamProfile(varIsRoaming);
			CHECK_HRESULT_BREAK
		}

		// If notarization does not support the language used by the PTA then use
		// "English" as language for both of them
		hr = pPTA->get_IVSUIPrefs((IDispatch**)&pIVSUIPref);
		CHECK_HRESULT_BREAK

		hr = pIVSUIPref->get_Language(&varLang);
		CHECK_HRESULT_BREAK

		if(!_IsLangSupported(varLang.iVal))
		{
			varLang.vt = VT_I2;
			varLang.iVal = LANG_ENGLISH_US;

			hr = pIVSUIPref->put_Language(varLang);
			CHECK_HRESULT_BREAK
		}

		if(i_bDisplayDigID)
		{
			// Set some search criteria required by the PTA to display the correct digital ID's
			// and UI preferences
			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_LGNDLG_TITLE, &wcString) == S_OK)
			{
				varLgnDlgTitle.vt = VT_BSTR;
				varLgnDlgTitle.bstrVal = SysAllocString(wcString);

				hr = pIVSUIPref->put_LgnDlg_Title(varLgnDlgTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcString)
			}

			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SELID_TITLE, &wcString) == S_OK)
			{
				varSelIdTitle.vt = VT_BSTR;
				varSelIdTitle.bstrVal = SysAllocString(wcString);

				hr = pIVSUIPref->put_SelID_Title(varSelIdTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcString)
			}

			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_OPENPROF_TITLE, &wcString) == S_OK)
			{
				varOpenProfTitle.vt = VT_BSTR;
				varOpenProfTitle.bstrVal = SysAllocString(wcString);

				hr = pIVSUIPref->put_OpenProf_Title(varOpenProfTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcString)
			}

			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SIGNDLG_TITLE, &wcString) == S_OK)
			{
				varSignDlgTitle.vt = VT_BSTR;
				varSignDlgTitle.bstrVal = SysAllocString(wcString);

				hr = pIVSUIPref->put_SgnDlg_Title(varSignDlgTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcString)
			}

			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SELIDCHKBOX_TEXT, &wcString) == S_OK)
			{
				varSelIDChkBoxText.vt = VT_BSTR;
				varSelIDChkBoxText.bstrVal = SysAllocString(wcString);

				hr = pIVSUIPref->put_SelID_ChkBoxText(varSelIDChkBoxText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcString)
			}

			varLogoUrl.vt = VT_BSTR;
			varLogoUrl.bstrVal = m_UsrSettings.m_bstrLogoUrl.copy();

			hr = pIVSUIPref->put_UILogoUrl(varLogoUrl);
			CHECK_HRESULT_BREAK

			hr = pPTA->get_IVSSrchCrit((IDispatch**)&pIVSSrchCrit);
			CHECK_HRESULT_BREAK

			varDateFlag.vt = VT_I2;
			varDateFlag.iVal = EXP_DATE_FLAG;

			hr = pIVSSrchCrit->put_DateEquality(varDateFlag);
			CHECK_HRESULT_BREAK

			varRenewedFlag.vt = VT_BOOL;
			varRenewedFlag.boolVal = FALSE;

			hr = pIVSSrchCrit->put_Renewed(varRenewedFlag);
			CHECK_HRESULT_BREAK
			
			todayUDate.wDayOfYear = 0;
			GetSystemTime(&todayUDate.st);

			hr = VarDateFromUdate(&todayUDate, 0, &todayDate);
			CHECK_HRESULT_BREAK

			hr = pIVSSrchCrit->put_ExpDate(todayDate);
			CHECK_HRESULT_BREAK

			varIssuerDN.vt = VT_BSTR;
			varIssuerDN.bstrVal = m_UsrSettings.m_bstrSrchCriteria.copy();

			hr = pIVSSrchCrit->put_IssuerDN(varIssuerDN);
			CHECK_HRESULT_BREAK

			if(m_UsrSettings.m_dwDisplayDigID)
				hr = pPTA->SelIDForChallenge();
			else
				hr = pPTA->SelIDForTrans();

			// Handle some special error cases
			if(hr != S_OK)
			{
				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_DNZ_ERROR, &wcString) != S_OK)
					break;
					
				bstrErrTitle = wcString;
				FREE_MEMORY(wcString)

				bstrErrMessage = _HandleError(hr, NULL);

				if(hr == E_VS_STORAGE_CORRUPT)
				{
					::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_ICONERROR);
					break;
				}
				else
					if(hr == E_USERCANCELLED)
						break;

				if(bstrErrMessage == _bstr_t(""))
				{
					// Unhandled error code, give a general error message
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SELID_ERR, &wcString) == S_OK)
					{
						bstrErrMessage = wcString;
						FREE_MEMORY(wcString)

						::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_OK);
					}

					break;
				}

				if(::MessageBox(GetFocus(), bstrErrMessage, bstrErrTitle, MB_YESNO) == IDYES)
				{
					if(hr == E_CERTMATCHBUTEXP)
						LaunchApp(m_UsrSettings.m_bstrRenewalPage);
					else
						LaunchApp(m_UsrSettings.m_bstrEnrollPage);
				}

			}	// if(hr != S_OK)

			CHECK_HRESULT_BREAK

		}	// if(i_bDisplayDigID)

		*o_pVSPta = pPTA;

		hr = S_OK;

	}while(0);

	VariantClear(&varAppName);
	VariantClear(&varHostName);
	VariantClear(&varUseCapi);
	VariantClear(&varProfOpen);
	VariantClear(&varIsRoaming);
	VariantClear(&varIsLocal);
	VariantClear(&varAttachedSig);
	VariantClear(&varShowSignUI);
	VariantClear(&varClientInfo);
	VariantClear(&varClientInfoSig);
	VariantClear(&varIssuerDN);
	VariantClear(&varDateFlag);
	VariantClear(&varRenewedFlag);
	VariantClear(&varLogoUrl);
	VariantClear(&varSelIdTitle);
	VariantClear(&varOpenProfTitle);
	VariantClear(&varLgnDlgTitle);
	VariantClear(&varSignDlgTitle);
	VariantClear(&varSelIDChkBoxText);
	VariantClear(&varLang);
	
	RELEASE_INTERFACE_PTR(pIVSUIPref)
	RELEASE_INTERFACE_PTR(pIVSSrchCrit)
	RELEASE_INTERFACE_PTR(pIVSRoamPrefs)
	RELEASE_INTERFACE_PTR(pIVSProfMgmt)
	RELEASE_INTERFACE_PTR(pPTADllApi)

	if(hr != S_OK)
	{
		_UnInitializePTA(pPTA);
		_LogErrorMsg("CVSNZ::_InitializePTA().", "Error initializing the PTA.", NULL, hr);
	}

	return hr;
}


/*
I/P -	'i_pVSPta'	-	Is a pointer to the PTA 'IVSPTA' interface.
Return -	An hresult indicating success of the operation.
Working -	Uninitialize the PTA interface pointer obtained using the '_InitializePTA()'
			function. 
*/

HRESULT CVSNZ::_UnInitializePTA(IVSPTA* i_pVSPta)
{
	if(!i_pVSPta)
		return E_NZEMPTYARGS;

	i_pVSPta->Close();

	RELEASE_INTERFACE_PTR(i_pVSPta)

	return S_OK;
}


/*
I/P -	'i_pVSPta'	:	Is the pointer to the PTA interface. It is passed to the 'CNotarization'
						class which uses it to perform the signature.
		'i_bstrDocument'	:	Is the document to be notarized. It can be in the form of 
								a URL. If no document is specified this function will prompt
								the user to select a document.
		'i_dwUIMask'	:	Decides what type of UI has to be displayed while the document
							is being notarized. UI flags are specified by the 'UIFLAG_' mask
		'i_rType'	:	Decides what type of data will be returned in the 'o_pbRecord' parameter.
						Possible values are taken from the 'ResponseType' enum.
O/P -	'o_pbRecord'	:	Will hold the response returned by the notarization server or
							the notarization record.
		'o_pdwRecordLen'	:	Is the length of data in 'o_pbRecord'.
Return -	An hresult indicating success of the operation.
Working -	This is a common function called from the activex method and from the context
			menu interface to perform a digital notarization operation. It uses the 
			CNotarization class to create, send and verify a notarization request. It uses
			the CNotarizationRecord class to create a record if necessary. This function
			assumes that 'm_UsrSettings' member variable has been initialized by using the
			activex methods or by reading the data from the registry(for context menu).
*/
HRESULT CVSNZ::_DoDigitalNotarization(IVSPTA* i_pVSPta, LPCTSTR* pSelFiles, PBYTE* i_pbHashValues, 
									  const UINT nToNotarize, const BOOL i_bUseHash, 
									  const DWORD i_dwUIMask, const ResponseType i_rType, const BOOL i_bCreateReceipt,
									  PBYTE* o_pbRecords, LPDWORD o_pdwRecordLengths)
{
	HRESULT hr = S_OK;
	NzRequest NotzRequest;
	NzResponse NotzResponse;
	NzDetails NotzDetails;
	CDataAccess DAccObject;
	_bstr_t tbstrDocToNotarize = "", bstrStatusString = "", bstrReceiptFile = "";
	_bstr_t bstrCaption = "", bstrReceiptDescription = "", tbstrUserAgent = "";
	WCHAR *wcString = NULL;
	CDNZUI* pTheDNZUI = NULL;
	PUICTXT pTheUICtxt = NULL;
	POPCTXT pTheOpCtxt = NULL;
	LPCTSTR *pFilesToNotarize = NULL;
	LPCTSTR pSelectedFile = NULL;
	UINT nDataToNotarize = 0;
	PBYTE pbEncodedRecord = NULL;
	DWORD dwEncodedLen = 0;

	NotzRequest.Initialize();
	NotzResponse.Initialize();
	NotzDetails.Initialize();

	do
	{
		if(!i_pVSPta || !o_pbRecords || !o_pdwRecordLengths)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(m_UsrSettings.m_bstrNzServer == _bstr_t(""))
		{
			hr = E_NZNOSERVER;
			break;
		}

		if(!i_bUseHash)
			pFilesToNotarize = pSelFiles;

		nDataToNotarize = nToNotarize;
	
		pTheDNZUI = (CDNZUI*) new (CDNZUI);

		if(!nToNotarize && !i_bUseHash)		// Call code that will display the select file ui
		{
			hr = _GetNotarizationDocument(i_pVSPta, pTheDNZUI, tbstrDocToNotarize, i_dwUIMask);
			CHECK_HRESULT_BREAK

			pSelectedFile = (LPCTSTR)tbstrDocToNotarize;
			pFilesToNotarize = &pSelectedFile;

			nDataToNotarize = 1;
		}

		// Get the user agent string
		_GetUserAgentString(&tbstrUserAgent);
		
		// Show the progress UI
		if(i_dwUIMask & UIFLAG_PROGRESS)
		{
			pTheOpCtxt = (POPCTXT) new (OPCTXT);
			hr = _BeginProgressUI(i_pVSPta,pTheDNZUI,pTheOpCtxt, !nToNotarize); 
			CHECK_HRESULT_BREAK
		}

		// Create the 2 objects which are going to do most of the work
		CNotarization NzObject(i_pVSPta);
		CNotarizationRecord NzRecordObject;
		
		for(UINT i = 0; i < nDataToNotarize; i++)
		{
			if(i_bCreateReceipt)
			{
				// First determine if the user will be able to create a receipt file in the current
				// folder, if not do not proceed with notarization as this will unnecessarily comsume
				// a notarization. Later on we can ask user for alternative receipt location
				hr = GetReceiptFileName(pFilesToNotarize[i], &bstrReceiptFile);
				CHECK_HRESULT_BREAK
			}
			
			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 10, IDS_CREATE_REQ);
				CHECK_HRESULT_BREAK

				if(pTheDNZUI->IsDialogCancelled())
				{
					hr = E_USERCANCELLED;
					break;
				}
			}

			bstrReceiptDescription = m_UsrSettings.m_bstrReceiptDescription;

			if(!i_bUseHash)
			{
				NotzDetails.bstrNzDocumentName = pFilesToNotarize[i];

				// If a description has not been provided to us via the script or registry 
				// set the description as the last component of the file path.
				if(bstrReceiptDescription == _bstr_t(""))
				{
					UINT iFileLen = 0;
					LPCTSTR lpFileName = NULL;
					
					lpFileName = pFilesToNotarize[i];
					iFileLen = lstrlen(lpFileName);

					int j = 0;
					int skipEndSlashIndex = iFileLen - 1;

					for (j = iFileLen - 1; j >= 0; j--)
					{
						if ((lpFileName[j] == '/' )|| (lpFileName[j] == '\\'))
						{
							continue;
						}
						else
						{
							break;
						}
					}
					skipEndSlashIndex = j;

					for(INT i = skipEndSlashIndex; i >= 0; i--)
					{
						if(lpFileName[i] == '/' || lpFileName[i] == '\\')
						{
							char *pcszDesc;

							pcszDesc = (char *) malloc ((skipEndSlashIndex - i + 1) * sizeof(char));
							memset(pcszDesc, 0, skipEndSlashIndex - i + 1);
							memcpy(pcszDesc, &lpFileName[i+1], skipEndSlashIndex-i);
							bstrReceiptDescription = pcszDesc;
							break;
						}
					}
				}
			}

			if(i_bUseHash)
				hr = NzObject.CreateNotarizationRequest("", i_pbHashValues[i], bstrReceiptDescription, m_UsrSettings.m_bstrHashAlg, tbstrUserAgent, &NotzRequest);
			else
				hr = NzObject.CreateNotarizationRequest(pFilesToNotarize[i], NULL, bstrReceiptDescription, m_UsrSettings.m_bstrHashAlg, tbstrUserAgent, &NotzRequest);

			CHECK_HRESULT_BREAK

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 25, IDS_CREATE_REQ);
				CHECK_HRESULT_BREAK
			}

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 30, IDS_SIGN_REQ);
				CHECK_HRESULT_BREAK

				if(pTheDNZUI->IsDialogCancelled())
				{
					hr = E_USERCANCELLED;
					break;
				}
			}

			hr = NzObject.SignNotarizationRequest(m_UsrSettings.m_bstrHashAlg, &NotzRequest);
			CHECK_HRESULT_BREAK

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 50, IDS_SIGN_REQ);
				CHECK_HRESULT_BREAK
			}

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 60, IDS_SEND_REQ); 
				CHECK_HRESULT_BREAK

				if(pTheDNZUI->IsDialogCancelled())
				{
					hr = E_USERCANCELLED;
					break;
				}
			}

			hr = NzObject.SendNotarizationRequest(m_UsrSettings.m_bstrNzServer, &NotzRequest, &NotzResponse);
			CHECK_HRESULT_BREAK

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 70, IDS_SEND_REQ); 
				CHECK_HRESULT_BREAK
			}

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 80, IDS_VERIFY_RESP); 
				CHECK_HRESULT_BREAK

				if(pTheDNZUI->IsDialogCancelled())
				{
					hr = E_USERCANCELLED;
					break;
				}
			}

			if(i_bUseHash)
				hr = NzObject.VerifyNotarizationResponse("", i_pbHashValues[i], &NotzResponse, m_UsrSettings.m_dwValidationFlags, m_UsrSettings.m_bstrCrl, tbstrUserAgent, &NotzDetails);
			else
				hr = NzObject.VerifyNotarizationResponse(pFilesToNotarize[i], NULL, &NotzResponse, m_UsrSettings.m_dwValidationFlags, m_UsrSettings.m_bstrCrl, tbstrUserAgent, &NotzDetails);

			CHECK_HRESULT_BREAK

			// Update the progress UI
			if(i_dwUIMask & UIFLAG_PROGRESS)
			{
				hr = _UpdateProgressUI(pTheDNZUI, 100, IDS_VERIFY_RESP); 
				CHECK_HRESULT_BREAK

				if(pTheDNZUI->IsDialogCancelled())
				{
					hr = E_USERCANCELLED;
					break;
				}
			}

			// Check if the nonce values in the request and the response are the same
			if(NotzRequest.dwNzNonce != NotzDetails.dwNonce)
			{
				hr = E_NZINVALIDNONCE;
				break;
			}

			if(memcmp(NotzRequest.pbNzNonce, NotzDetails.pbNonce, NotzDetails.dwNonce) != 0)
			{
				hr = E_NZINVALIDNONCE;
				break;
			}

			// Check if the policy values in the request and the response are the same
			if(NotzDetails.dwAuthDocPolicy != (DWORD)lstrlen(AUTHDOC_POLICY_OID))
			{
				hr = E_NZINVALIDPOLICY;
				break;
			}

			if(memcmp(NotzDetails.pbAuthDocPolicy, AUTHDOC_POLICY_OID, NotzDetails.dwAuthDocPolicy) != 0)
			{
				hr = E_NZINVALIDPOLICY;
				break;
			}

			// Create a notarization record (receipt) using the CNotarizationRecord class if the caller
			// wants the record, else just return the notarization server response
			if(i_rType == RT_NZRESPONSE)
			{
				o_pbRecords[i] = (PBYTE)malloc(NotzResponse.dwNzResponse);
				CHECK_MEM_BREAK(o_pbRecords[i])

				o_pdwRecordLengths[i] = NotzResponse.dwNzResponse;
				memcpy(o_pbRecords[i], NotzResponse.pbNzResponse, o_pdwRecordLengths[i]);
			}
			else
			{
				// Should not come here as we do not support the 'RT_NZRECORD' from version 1.0.0.3 on
				hr = NzRecordObject.CreateNotarizationRecord(pFilesToNotarize[i], bstrReceiptDescription, NotzDetails.bstrNzRequestor, NotzResponse, &o_pbRecords[i], &o_pdwRecordLengths[i]);
				CHECK_HRESULT_BREAK
			}

			if(i_bCreateReceipt)
			{
				// Base64 encode the response, the response is the data returned by the notarization server
				_Base64Encode((char *)o_pbRecords[i], o_pdwRecordLengths[i], NULL, &dwEncodedLen);
				pbEncodedRecord = (PBYTE)malloc(dwEncodedLen + 1);
				CHECK_MEM_BREAK(pbEncodedRecord)

				_Base64Encode((char *)o_pbRecords[i], o_pdwRecordLengths[i], (char *)pbEncodedRecord, &dwEncodedLen);
				pbEncodedRecord[dwEncodedLen] = '\0';

				NotzDetails.bstrNzDocumentName = bstrReceiptFile;

				hr = DAccObject.Open(bstrReceiptFile, ACCESS_WRITE, "");
				CHECK_HRESULT_BREAK

				hr = DAccObject.Write(pbEncodedRecord, dwEncodedLen);
				CHECK_HRESULT_BREAK

				DAccObject.Close();

				FREE_MEMORY(pbEncodedRecord)
			}

			NotzDetails.Clear();
			NotzRequest.Clear();
			NotzResponse.Clear();

		}	// end for()

		if(hr == E_USERCANCELLED)
			break;

		bstrStatusString = _HandleError(hr, &NotzDetails);
		if(bstrStatusString == _bstr_t(""))
		{
			// Unhandled error code, get a general error message
			if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_NZ_GENERAL_ERR, &wcString) == S_OK)
			{
				bstrStatusString = wcString;
				FREE_MEMORY(wcString)
			}
		}

		if((i_dwUIMask == (UIFLAG_PROGRESS | UIFLAG_COMPLETE)) || 
		   (i_dwUIMask == UIFLAG_PROGRESS && hr != S_OK))
		{
			if(hr != S_OK)
				_ShowErrorUI(pTheDNZUI, bstrStatusString);
			else
			{
				// If a receipt file was created then update the status string to indicate that
				if(i_bCreateReceipt)
				{
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_NZ_RCPT, &wcString) == S_OK)
					{
						bstrStatusString += _bstr_t(" ");
						bstrStatusString += wcString;
						FREE_MEMORY(wcString)
					}

					_EndProgressUI(pTheDNZUI, bstrStatusString, pTheOpCtxt);
				}
				else
					_EndProgressUI(pTheDNZUI, bstrStatusString, pTheOpCtxt);
			}

			break;
		}
		
		if(i_dwUIMask == UIFLAG_PROGRESS)
		{
			_EndProgressUI(pTheDNZUI, bstrStatusString, pTheOpCtxt, FALSE);
			break;
		}

		// At this point no UI is been displayed, so first create a progress UI 
		// then modify that UI context to an error UI(this is a round about way of passing the 
		// UI context information from the progress UI to the error UI).
		// Finally show the UI
		if(i_dwUIMask == UIFLAG_COMPLETE || hr != S_OK)
		{
			pTheUICtxt = _CreateUIContext();
			CHECK_MEM_BREAK(pTheUICtxt)

			if(_SetUICtxtForProgress(i_pVSPta, pTheUICtxt, FALSE, TRUE) != S_OK)
				break;

			pTheOpCtxt = (POPCTXT) new (OPCTXT);
			CHECK_MEM_BREAK(pTheOpCtxt)

			pTheOpCtxt->pOParams = NULL;
			pTheOpCtxt->pvTheNotUIObj = pTheDNZUI;
			pTheOpCtxt->pvTheVNZObj = this;
			pTheOpCtxt->nWizardAndUIs = ERROR_BASE; //PROGRESS_BASE; 17 May 2001

			if(pTheDNZUI->put_UIContext(pTheUICtxt) != S_OK)
				break;

			if(hr != S_OK)
			{
				_ShowErrorUI(pTheDNZUI, bstrStatusString);
				//CHECK_HRESULT_BREAK		17 May 2001
			}
		
			pTheDNZUI->ShowUI(pTheOpCtxt);

			break;
		}
		
	}while(0);

	NotzDetails.Clear();
	NotzRequest.Clear();
	NotzResponse.Clear();

	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	DELETE_MEMORY(pTheDNZUI)
	DELETE_MEMORY(pTheOpCtxt)

	FREE_MEMORY(pbEncodedRecord)
	FREE_MEMORY(wcString)

	DAccObject.Close();
	
	if(hr != S_OK)
		_LogErrorMsg("_DoDigitalNotarization().", "Error occured during notarization.", NULL, hr);

	return hr;
}


/*
I/P -	
O/P -
Return -	
Working -	
*/
HRESULT CVSNZ::_DoRecordVerification(const _bstr_t i_bstrRecord, const _bstr_t i_bstrAltDocument, const BOOL i_bUrl, 
									 const DWORD i_dwValidationFlags, LPNzDetails o_NzDetailedInfo)
{
	HRESULT hr = S_OK;
	_bstr_t bstrDocument = "", bstrDocToVerify = "", bstrDescription = "", tbstrUAgent = "";
	NzResponse NzResp;
	ResponseType RespType;
	CNotarizationRecord NzRecordObj;
	CNotarization NzObject(NULL);
	CDataAccess DAReadObject;

	NzResp.Initialize();
	
	do
	{
		if(!i_bstrRecord || !o_NzDetailedInfo || !i_bstrAltDocument)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_bstrRecord == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		// Get the user agent string
		_GetUserAgentString(&tbstrUAgent);

		o_NzDetailedInfo->Initialize();

		o_NzDetailedInfo->tbstrUserAgent = tbstrUAgent;

		// Use the Record class to read the record
		hr = NzRecordObj.OpenNotarizationRecord(i_bstrRecord, i_bUrl, tbstrUAgent, o_NzDetailedInfo);
		CHECK_HRESULT_BREAK

		hr = NzRecordObj.GetNotarizationResponse(&NzResp);
		CHECK_HRESULT_BREAK

		hr = NzRecordObj.GetNotarizedDescription(&bstrDescription);
		CHECK_HRESULT_BREAK

		hr = NzRecordObj.GetRecordType(&RespType);
		CHECK_HRESULT_BREAK

		if(RespType == RT_NZRECORD)
		{
			// Document name in the receipt file
			hr = NzRecordObj.GetNotarizedDocument(&bstrDocument);
			CHECK_HRESULT_BREAK

			bstrDocToVerify = bstrDocument;

			// Set the document name that we are verifying the receipt with
			o_NzDetailedInfo->bstrNzDocumentName = bstrDocToVerify;

			// Check if the 'document' contained in the receipt exists, it yes use it else use
			// the document name passed in 'i_bstrDocument'
			hr = DAReadObject.Open(bstrDocToVerify, ACCESS_READ, tbstrUAgent);
			if(hr == E_NZDOCOPENFAILED)
			{
				if(i_bstrAltDocument == _bstr_t(""))
					break;

				bstrDocToVerify = i_bstrAltDocument;
				o_NzDetailedInfo->bstrNzDocumentName = bstrDocToVerify;
			}
			else
				if(hr != S_OK)
					break;		// some other error occurred

			DAReadObject.Close();
		}
		else 
		{
			if(i_bstrAltDocument == _bstr_t(""))
			{
				hr = E_NZDOCOPENFAILED;
				break;
			}

			//bstrDocument = i_bstrAltDocument;
			bstrDocToVerify = i_bstrAltDocument;
			o_NzDetailedInfo->bstrNzDocumentName = bstrDocToVerify;
		}
		
		hr = NzObject.VerifyNotarizationResponse(bstrDocToVerify, NULL, &NzResp, i_dwValidationFlags, m_UsrSettings.m_bstrCrl, tbstrUAgent, o_NzDetailedInfo);
		CHECK_HRESULT_BREAK

		// Set the 'bstrNzDocumentName' to the 'Description' if we have a description, else set it
		// to the 'DocumentPath'
		/*if(bstrDescription != _bstr_t(""))
			o_NzDetailedInfo->bstrNzDocumentName = bstrDescription;
		else
			o_NzDetailedInfo->bstrNzDocumentName = bstrDocument;*/
	}while(0);

	NzResp.Clear();

	if(hr != S_OK)
		_LogErrorMsg("_DoRecordVerification().", "Error occured during verification.", NULL, hr);

	return hr;
}



HRESULT CVSNZ::_GetNotarizationDocument(IVSPTA* i_pPTA, CDNZUI* pTheDNZUI, _bstr_t& i_bstrDocument, DWORD i_dwUIMask)
{
	HRESULT hr = S_OK;
	PUICTXT pTheUICtxt = NULL;
	POPCTXT pTheOpCtxt = NULL;

	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)
	
		hr = _SetUICtxtForSelect(i_pPTA, pTheUICtxt, i_dwUIMask);
		CHECK_HRESULT_BREAK

		pTheOpCtxt = new OPCTXT;
		CHECK_MEM_BREAK(pTheOpCtxt)
		
		pTheOpCtxt->pvTheNotUIObj = (void*)pTheDNZUI;
		if(i_dwUIMask & UIFLAG_PROGRESS)
			pTheOpCtxt->nWizardAndUIs = DIGNOTREQ_WIZARD_BASE | SELFILE_BASE | PROGRESS_BASE;
		else
			pTheOpCtxt->nWizardAndUIs = NO_WIZARD_BASE | SELFILE_BASE;
		pTheOpCtxt->pOParams = (POPARAMS)new OPARAMS;
		CHECK_MEM_BREAK(pTheOpCtxt->pOParams)
		pTheOpCtxt->pOParams->tbstrSelFile = "";

		hr = pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK
		hr = pTheDNZUI->ShowUI(pTheOpCtxt);
		CHECK_HRESULT_BREAK

		i_bstrDocument = pTheOpCtxt->pOParams->tbstrSelFile;

	}while(0);

	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	if(pTheOpCtxt)
	{
		DELETE_MEMORY(pTheOpCtxt->pOParams)
	}
	DELETE_MEMORY(pTheOpCtxt)

	return hr;
}



HRESULT CVSNZ::_SetUICtxtForStatus(IVSPTA* i_pPTA, PUICTXT pTheUICtxt)
{
	HRESULT hr = S_OK;

	return hr;
}


HRESULT CVSNZ::_SetUICtxtForSelect(IVSPTA* i_pPTA, PUICTXT pTheUICtxt, DWORD i_dwUIMask)
{
	HRESULT hr = S_OK;
	WCHAR* pwcharBtnText = NULL;
	WCHAR* pwcharUIStrings = NULL;
	IVSUIPrefs* pPTAUIPRefs = NULL;
	VARIANT varLang;
	VARIANT varFontName;

	do
	{

		//Get the language that is set from the PTA
		hr = i_pPTA->QueryInterface(IID_IVSUIPrefs, (void **)&(pPTAUIPRefs));
		CHECK_HRESULT_BREAK

		hr = pPTAUIPRefs->get_Language(&varLang);
		CHECK_HRESULT_BREAK

		//Set the default language
		pTheUICtxt->nDefLangId = varLang.iVal;

		if(!_IsLangSupported(pTheUICtxt->nDefLangId))
			pTheUICtxt->nDefLangId = LANG_ENGLISH_US;
		
		//Set the UI to be shown
		pTheUICtxt->nWhichWizardAndUI = 0;
		pTheUICtxt->nWhichWizardAndUI = SELFILE_BASE;
		if(i_dwUIMask & UIFLAG_PROGRESS) //If we need to show the progress bar then this has to be wizard
		{
			pTheUICtxt->nWhichWizardAndUI &= (NO_WIZARD_BASE |OPERATION_BITS |FLAG_BITS);
			pTheUICtxt->nWhichWizardAndUI |= DIGNOTREQ_WIZARD_BASE;
		}

		//Set the button text
		pTheUICtxt->pbtnElems = new BTNELEMS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnElems)
		if(i_dwUIMask & UIFLAG_PROGRESS)
		{
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_PREV,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn1Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_NEXT,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CANCEL,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

		}
		else
		{
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_SELECT,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn1Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CANCEL,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_HELP,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

		}

		CHECK_HRESULT_BREAK

		//Set the button functions
		pTheUICtxt->pbtnFns = new BTNFNS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnFns)
		if(i_dwUIMask & UIFLAG_PROGRESS)
		{
			pTheUICtxt->pbtnFns->lpfnBtn1Fn = NULL;
			pTheUICtxt->pbtnFns->lpfnBtn2Fn = SelFileFn;
			pTheUICtxt->pbtnFns->lpfnBtn3Fn = CancelFn;
		}
		else
		{
			pTheUICtxt->pbtnFns->lpfnBtn1Fn = SelFileFn;
			pTheUICtxt->pbtnFns->lpfnBtn2Fn = CancelFn;
			pTheUICtxt->pbtnFns->lpfnBtn3Fn = SelFileHelpFn;
		}
		
		//Set the custom font info
		pTheUICtxt->pfontInfoCustomFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoCustomFonts)
		
		pTheUICtxt->pfontInfoCustomFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the default font info
		pTheUICtxt->pfontInfoDefaultFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoDefaultFonts)
		
		pTheUICtxt->pfontInfoDefaultFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the UI elements
		pTheUICtxt->pvUIElements = (void*)new ALL_SELFILE_UIELEMENTS;
		((PALL_SELFILE_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrTitle = m_UsrSettings.m_bstrSelFileTitle;
		((PALL_SELFILE_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrText = m_UsrSettings.m_bstrSelFileDescription;

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_SELFILE_TITLE,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		((PALL_SELFILE_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrTitle = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_SELFILE_TEXT,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		((PALL_SELFILE_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		//Set the Wizard title if necessary
		if(i_dwUIMask & UIFLAG_PROGRESS)
		{
			pTheUICtxt->pvWizardElems = new ALL_CREATENOTREQ_WIZARDELEMENTS;
			((PALL_CREATENOTREQ_WIZARDELEMENTS)pTheUICtxt->pvWizardElems)->theCustWizardElems.tbstrWizTitle = m_UsrSettings.m_bstrDigNotWizTitle; 
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CREATENOTREQ_WIZTITLE,&pwcharUIStrings);
			CHECK_HRESULT_BREAK
			((PALL_CREATENOTREQ_WIZARDELEMENTS)pTheUICtxt->pvWizardElems)->theDefWizardElems.tbstrWizTitle = pwcharUIStrings; 
		}

		//Set the logo urls
		pTheUICtxt->tbstrDefLogoUrl = "";
		pTheUICtxt->tbstrCustLogoUrl = m_UsrSettings.m_bstrLogoUrl;

	}while(0);

	FREE_MEMORY(pwcharBtnText)
	FREE_MEMORY(pwcharUIStrings)

	RELEASE_INTERFACE_PTR(pPTAUIPRefs)

	return hr;
}

HRESULT SelFileFn(POPCTXT pOpCtxt)
{
	PALL_SELFILE_UIELEMENTS pTheSelFileUIElems = NULL;
	PUICTXT pTheUICtxt = NULL; 
	HRESULT hr = S_OK;
	WCHAR *wcErrString = NULL;
	_bstr_t bstrErrTitle = "", bstrErrString = "";
	CDataAccess DAReadObject;

	do
	{
		//Get current ui context
		pTheUICtxt = (PUICTXT) new (UICTXT);
		CHECK_MEM_BREAK(pTheUICtxt)

		hr = ((CDNZUI*)pOpCtxt->pvTheNotUIObj)->get_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		pTheSelFileUIElems = (PALL_SELFILE_UIELEMENTS)pTheUICtxt->pvUIElements;

		//Make sure that a file has been selected.
		if(pTheSelFileUIElems->tbstrSelectedFile.length() == 0)
			break;
		else
		{
			// Check if the filename is valid, if not give error msg
			hr = DAReadObject.Open(pTheSelFileUIElems->tbstrSelectedFile);
			if(hr != S_OK)
			{
				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_ERROR, &wcErrString) == S_OK)
				{
					bstrErrTitle = wcErrString;
					FREE_MEMORY(wcErrString)
				}

				if(hr == E_NZDOCOPENFAILED)
				{
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SELFILE_ERR, &wcErrString) == S_OK)
					{
						bstrErrString = wcErrString;
						FREE_MEMORY(wcErrString)
					}
				}
				else
				{
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_SELFILE_ERR2, &wcErrString) == S_OK)
					{
						bstrErrString = wcErrString;
						FREE_MEMORY(wcErrString)
					}
				}

				::MessageBox(GetFocus(), bstrErrString, bstrErrTitle, MB_ICONERROR);

				break;
			}
		}

		//Store the selected file
		pOpCtxt->pOParams->tbstrSelFile = pTheSelFileUIElems->tbstrSelectedFile;

		//Break down the UI
		hr = ((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
		CHECK_HRESULT_BREAK

	}while(0);

	DAReadObject.Close();
	
	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)

	return S_OK;
}

HRESULT CVSNZ::_BeginProgressUI(IVSPTA* i_pPTA,CDNZUI* i_pTheDNZUI,POPCTXT pTheOpCtxt, BOOL i_bShowFileSelectUI)
{
	HRESULT hr = S_OK;
	PUICTXT pTheUICtxt = NULL;
	
	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)
	
		hr = _SetUICtxtForProgress(i_pPTA, pTheUICtxt, i_bShowFileSelectUI, FALSE);
		CHECK_HRESULT_BREAK

		
		pTheOpCtxt->pvTheNotUIObj = (void*)i_pTheDNZUI;
		pTheOpCtxt->pvTheVNZObj = this;

		if(i_bShowFileSelectUI)
			pTheOpCtxt->nWizardAndUIs = DIGNOTREQ_WIZARD_BASE | SELFILE_BASE | PROGRESS_BASE;
		else
			pTheOpCtxt->nWizardAndUIs = NO_WIZARD_BASE | PROGRESS_BASE;
		pTheOpCtxt->pOParams = (POPARAMS)new OPARAMS;
		CHECK_MEM_BREAK(pTheOpCtxt->pOParams)

		hr = i_pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK
		hr = i_pTheDNZUI->BeginUI(pTheOpCtxt);
		CHECK_HRESULT_BREAK

	}while(0);

	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	
	return hr;
}

HRESULT CVSNZ::_UpdateProgressUI(CDNZUI* i_pTheDNZUI, int i_nPercentComplete, int i_nStringID)
{
	HRESULT hr = S_OK;
	PUICTXT pTheUICtxt = NULL;
	PALL_PROGRESS_UIELEMENTS pTheProgressUI;
	WCHAR* pwcharUIStrings = NULL;

	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)

		hr = i_pTheDNZUI->get_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		pTheProgressUI = (PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements;
		//pTheProgressUI->nCompletedPercent = i_nPercentComplete;

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,i_nStringID,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		pTheProgressUI->theDefUIElements.tbstrText = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		/*//Format the progress text
		TCHAR* tcharProgressText = new TCHAR[lstrlen((TCHAR*)pTheProgressUI->theDefUIElements.tbstrText)+4];
		CHECK_MEM_BREAK(tcharProgressText)
		wsprintf(tcharProgressText, (LPCTSTR)(TCHAR*)pTheProgressUI->theDefUIElements.tbstrText,i_nPercentComplete);
		pTheProgressUI->theDefUIElements.tbstrText = tcharProgressText;
		FREE_MEMORY(tcharProgressText)*/
		
		pTheProgressUI->nCompletedPercent = i_nPercentComplete;

		hr = i_pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		hr = i_pTheDNZUI->UpdateUI();
		CHECK_HRESULT_BREAK

	}while(0);
	
	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	FREE_MEMORY(pwcharUIStrings)
	return hr;
}


HRESULT CVSNZ::_EndProgressUI(CDNZUI* i_pTheDNZUI, _bstr_t i_bstrErrString, POPCTXT pTheOpCtxt,
							  BOOL i_bShowModal)
{
	HRESULT hr = S_OK;
	PUICTXT pTheUICtxt = NULL;
	PALL_PROGRESS_UIELEMENTS pTheProgressUI;
	WCHAR* pwcharBtnText = NULL;

	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)

		hr = i_pTheDNZUI->get_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		// End the modeless dialog box
		hr = i_pTheDNZUI->EndUI();
		CHECK_HRESULT_BREAK

		if(!i_bShowModal)
			break;

		pTheProgressUI = (PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements;

		pTheProgressUI->theDefUIElements.tbstrText = i_bstrErrString;

		// If error has occurred then set the custom ui element to the error
		if(i_bstrErrString != _bstr_t(""))
			pTheProgressUI->theCustUIElements.tbstrText = i_bstrErrString;
	
		pTheProgressUI->nCompletedPercent = 100;
		
		if(pTheOpCtxt->nWizardAndUIs & DIGNOTREQ_WIZARD_BASE)
		{
			pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressDoneFn;
			pTheUICtxt->pbtnFns->lpfnBtn3Fn = ProgressHelpFn;
		}
		else
		{
			pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressDoneFn;
			pTheUICtxt->pbtnFns->lpfnBtn3Fn = ProgressHelpFn;
		}

		// Change the button 2 text from 'cancel' to 'done'
		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_DONE,&pwcharBtnText);
		CHECK_HRESULT_BREAK

		pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
		FREE_MEMORY(pwcharBtnText)

		hr = i_pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		hr = i_pTheDNZUI->ShowUI(pTheOpCtxt);
		CHECK_HRESULT_BREAK

	}while(0);
	
	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	FREE_MEMORY(pwcharBtnText)

	if(pTheOpCtxt)
	{
		DELETE_MEMORY(pTheOpCtxt->pOParams)
	}
	
	return hr;
}




HRESULT CVSNZ::_ShowErrorUI(CDNZUI* i_pTheDNZUI, _bstr_t i_bstrErrString)
{
	HRESULT hr = S_OK;
	BOOL bIsModeless = FALSE;
	PUICTXT pTheUICtxt = NULL;
	POPCTXT pTheOpCtxt = NULL;
	WCHAR* pwcharUIStrings = NULL, *pwcharBtnText;

	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)

		hr = i_pTheDNZUI->get_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		// If the current UI is modeless then end it
		if(i_pTheDNZUI->IsModelessDlg())
		{
			bIsModeless = TRUE;
			hr = i_pTheDNZUI->EndUI();
			CHECK_HRESULT_BREAK
		}

		// Delete elements of the current UI context which are not required
		_FreeUIElements(pTheUICtxt);

		// Set the button text
		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_DONE,&pwcharBtnText);
		CHECK_HRESULT_BREAK

		pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
		FREE_MEMORY(pwcharBtnText)

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_HELP,&pwcharBtnText);
		CHECK_HRESULT_BREAK

		pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
		FREE_MEMORY(pwcharBtnText)

		// Set the button functions
		pTheUICtxt->pbtnFns->lpfnBtn2Fn = ErrorDoneFn;
		pTheUICtxt->pbtnFns->lpfnBtn3Fn = ErrorHelpFn;
		pTheUICtxt->pbtnFns->lpfnBtn1Fn = NULL;

		pTheUICtxt->nWhichWizardAndUI = NO_WIZARD_BASE | ERROR_BASE;

		// Set the UI elements
		pTheUICtxt->pvUIElements = (void*)new ALL_ERROR_UIELEMENTS;

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_ERROR,&pwcharUIStrings);
		CHECK_HRESULT_BREAK

		((PALL_ERROR_UIELEMENTS)pTheUICtxt->pvUIElements)->theUIElements.tbstrTitle = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		((PALL_ERROR_UIELEMENTS)pTheUICtxt->pvUIElements)->theUIElements.tbstrText = i_bstrErrString;

		hr = i_pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK

		if(bIsModeless)
		{
			// 17 May 2001
			// Set an operation context is set over here, so that the ErrorHelpFn works as desired
			pTheOpCtxt = (POPCTXT) new (OPCTXT);
			CHECK_MEM_BREAK(pTheOpCtxt)

			pTheOpCtxt->pOParams = NULL;
			pTheOpCtxt->pvTheNotUIObj = i_pTheDNZUI;
			pTheOpCtxt->nWizardAndUIs = ERROR_BASE;
			pTheOpCtxt->pvTheVNZObj = this;

			hr = i_pTheDNZUI->ShowUI(pTheOpCtxt);
			CHECK_HRESULT_BREAK
		}

	}while(0);

	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheOpCtxt)
	DELETE_MEMORY(pTheUICtxt)

	return hr;
}

HRESULT CVSNZ::_SetUICtxtForProgress(IVSPTA* i_pPTA, PUICTXT pTheUICtxt, BOOL i_bShowFileSelectUI,
									 BOOL i_bUseAsStatusUI)
{
	HRESULT hr = S_OK;
	WCHAR* pwcharBtnText = NULL;
	WCHAR* pwcharUIStrings = NULL;
	IVSUIPrefs* pPTAUIPRefs = NULL;
	VARIANT varLang;
	VARIANT varFontName;

	do
	{

		//Get the language that is set from the PTA
		hr = i_pPTA->QueryInterface(IID_IVSUIPrefs, (void **)&(pPTAUIPRefs));
		CHECK_HRESULT_BREAK

		hr = pPTAUIPRefs->get_Language(&varLang);
		CHECK_HRESULT_BREAK

		//Set the default language
		pTheUICtxt->nDefLangId = varLang.iVal;

		if(!_IsLangSupported(pTheUICtxt->nDefLangId))
			pTheUICtxt->nDefLangId = LANG_ENGLISH_US;
		
		//Set the UI to be shown
		pTheUICtxt->nWhichWizardAndUI = 0;
		pTheUICtxt->nWhichWizardAndUI = PROGRESS_BASE;
		if(i_bShowFileSelectUI) //If the select file was shown then this has to be wizard
		{
			//pTheUICtxt->nWhichWizardAndUI &= (NO_WIZARD_BASE |OPERATION_BITS |FLAG_BITS);
			pTheUICtxt->nWhichWizardAndUI |= DIGNOTREQ_WIZARD_BASE;
		}

		//Set the button functions
		pTheUICtxt->pbtnFns = new BTNFNS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnFns)
		pTheUICtxt->pbtnFns->lpfnBtn1Fn = NULL;
		pTheUICtxt->pbtnFns->lpfnBtn2Fn = NULL;
		pTheUICtxt->pbtnFns->lpfnBtn3Fn = ProgressHelpFn;

		//Set the button text
		pTheUICtxt->pbtnElems = new BTNELEMS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnElems)
		if(i_bShowFileSelectUI)
		{
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_PREV,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn1Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			if(i_bUseAsStatusUI)
			{
				hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_DONE,&pwcharBtnText);
				CHECK_HRESULT_BREAK

				pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressDoneFn;
			}
			else
			{
				hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CANCEL,&pwcharBtnText);
				CHECK_HRESULT_BREAK

				pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressCancelFn;
			}

			pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_HELP,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

		}
		else
		{
			/*hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_DONE,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn1Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)*/

			if(i_bUseAsStatusUI)
			{
				hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_DONE,&pwcharBtnText);
				CHECK_HRESULT_BREAK

				pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressDoneFn;
			}
			else
			{
				hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CANCEL,&pwcharBtnText);
				CHECK_HRESULT_BREAK

				pTheUICtxt->pbtnFns->lpfnBtn2Fn = ProgressCancelFn;
			}

			pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)

			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_HELP,&pwcharBtnText);
			CHECK_HRESULT_BREAK

			pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
			FREE_MEMORY(pwcharBtnText)
		}

		CHECK_HRESULT_BREAK
	
		//Set the custom font info
		pTheUICtxt->pfontInfoCustomFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoCustomFonts)
		
		pTheUICtxt->pfontInfoCustomFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the default font info
		pTheUICtxt->pfontInfoDefaultFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoDefaultFonts)
		
		pTheUICtxt->pfontInfoDefaultFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the UI elements
		pTheUICtxt->pvUIElements = (void*)new ALL_PROGRESS_UIELEMENTS;
		((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrTitle = m_UsrSettings.m_bstrProgressTitle;
		((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrText = m_UsrSettings.m_bstrProgressDescription;

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_PROGRESS_TITLE,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrTitle = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		if(i_bUseAsStatusUI)
		{
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_NZ_COMPLETE2,&pwcharUIStrings);
			CHECK_HRESULT_BREAK
		}
		else
		{
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_PROGRESS_TEXT,&pwcharUIStrings);
			CHECK_HRESULT_BREAK
		}

		((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		if(i_bUseAsStatusUI)
		{
			((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->nCompletedPercent = 0;
		}
		else
		{
			//Format the progress text
			TCHAR* tcharProgressText = new TCHAR[lstrlen((TCHAR*)((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText)+4];
			CHECK_MEM_BREAK(tcharProgressText)
			wsprintf(tcharProgressText, (LPCTSTR)(TCHAR*)((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText,0);
			((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText = tcharProgressText;
			DELETE_MEMORY(tcharProgressText)

			((PALL_PROGRESS_UIELEMENTS)pTheUICtxt->pvUIElements)->nCompletedPercent = 2;
		}
		
		//Set the Wizard title if necessary
		if(i_bShowFileSelectUI)
		{
			pTheUICtxt->pvWizardElems = new ALL_CREATENOTREQ_WIZARDELEMENTS;
			((PALL_CREATENOTREQ_WIZARDELEMENTS)pTheUICtxt->pvWizardElems)->theCustWizardElems.tbstrWizTitle = m_UsrSettings.m_bstrDigNotWizTitle; 
			hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CREATENOTREQ_WIZTITLE,&pwcharUIStrings);
			CHECK_HRESULT_BREAK
			((PALL_CREATENOTREQ_WIZARDELEMENTS)pTheUICtxt->pvWizardElems)->theDefWizardElems.tbstrWizTitle = pwcharUIStrings; 
		}

		//Set the logo urls
		pTheUICtxt->tbstrDefLogoUrl = "";
		pTheUICtxt->tbstrCustLogoUrl = m_UsrSettings.m_bstrLogoUrl;

	}while(0);

	FREE_MEMORY(pwcharBtnText)
	FREE_MEMORY(pwcharUIStrings)

	RELEASE_INTERFACE_PTR(pPTAUIPRefs)

	return hr;
}

HRESULT CVSNZ::_ShowVerificationUI(CDNZUI* pTheDNZUI, IVSPTA* i_pPTA, DWORD i_dwUIMask, NzDetails* i_pNzDetailedInfo) 
{
	HRESULT hr = S_OK;
	PUICTXT pTheUICtxt = NULL;
	POPCTXT pTheOpCtxt = NULL;
	_bstr_t bstrTmpHtmlFile = "", bstrServerName = "", bstrServerObject = "";
	DWORD dwPortNum = 0, dwEncodedLen = 0;
	CDataAccess DAWriteObject;
	PBYTE pbEncodedToken = NULL;
	BOOL boolShowSaveDocumentLink = FALSE;
	BOOL boolShowViewDocumentLink = FALSE;
		
	do
	{
		pTheUICtxt = _CreateUIContext();
		CHECK_MEM_BREAK(pTheUICtxt)

		if(i_dwUIMask & UIFLAG_WEB_LINK)
		{
			do
			{
				// Parse the server path to get the notarization server name to be put in the html file
				hr = _ParseServerPath(m_UsrSettings.m_bstrNzServer, &bstrServerName, &bstrServerObject, &dwPortNum);
				CHECK_HRESULT_BREAK

				// Create a temporary html file containing data to be posted to the notarization server
				hr = _CreateTempFile(&bstrTmpHtmlFile);
				CHECK_HRESULT_BREAK

				// Rename the '.tmp' to '.htm'
				if(!MoveFile(bstrTmpHtmlFile, bstrTmpHtmlFile + ".htm"))
				{
					hr = E_NZDOCMOVERR;
					break;
				}

				bstrTmpHtmlFile += ".htm";

				hr = DAWriteObject.Open(bstrTmpHtmlFile, ACCESS_OVERWRITE);
				CHECK_HRESULT_BREAK

				hr = DAWriteObject.Write((LPBYTE)POST_DATA1, lstrlen(POST_DATA1));
				CHECK_HRESULT_BREAK

				hr = DAWriteObject.Write((PBYTE)(TCHAR*)bstrServerName, bstrServerName.length());
				CHECK_HRESULT_BREAK

				hr = DAWriteObject.Write((LPBYTE)POST_DATA2, lstrlen(POST_DATA2));
				CHECK_HRESULT_BREAK

				// Base64 encode the token
				_Base64Encode((char *)i_pNzDetailedInfo->pbTimeStampToken, i_pNzDetailedInfo->dwTimeStampToken, NULL, &dwEncodedLen);
				pbEncodedToken = (PBYTE)malloc(dwEncodedLen + 1);
				CHECK_MEM_BREAK(pbEncodedToken)

				_Base64Encode((char *)i_pNzDetailedInfo->pbTimeStampToken, i_pNzDetailedInfo->dwTimeStampToken, (char *)pbEncodedToken, &dwEncodedLen);
				pbEncodedToken[dwEncodedLen] = '\0';

				hr = DAWriteObject.Write(pbEncodedToken, dwEncodedLen);
				CHECK_HRESULT_BREAK

				hr = DAWriteObject.Write((LPBYTE)POST_DATA3, lstrlen(POST_DATA3));
				CHECK_HRESULT_BREAK

				hr = DAWriteObject.Write((LPBYTE)POST_DATA4, lstrlen(POST_DATA4));
				CHECK_HRESULT_BREAK

				DAWriteObject.Close();
			}while(0);
	
			// If failed to create a temporary html file to post to web service then do not fail the entire
			// verification process
			if(hr != S_OK)
				bstrTmpHtmlFile = "";
		}
		else
			bstrTmpHtmlFile = "";
	

		hr = _SetUICtxtForVeirfication(i_pPTA, pTheUICtxt, i_dwUIMask, bstrTmpHtmlFile, i_pNzDetailedInfo);
		CHECK_HRESULT_BREAK

		pTheOpCtxt = new OPCTXT;
		CHECK_MEM_BREAK(pTheOpCtxt)
		
		pTheOpCtxt->pvTheNotUIObj = (void*)pTheDNZUI;
		pTheOpCtxt->nWizardAndUIs = NO_WIZARD_BASE | VERIFYRCPT_BASE;
		pTheOpCtxt->pvTheVNZObj = this;
		pTheOpCtxt->pOParams = NULL;
		
		hr = pTheDNZUI->put_UIContext(pTheUICtxt);
		CHECK_HRESULT_BREAK
		hr = pTheDNZUI->ShowUI(pTheOpCtxt);
		CHECK_HRESULT_BREAK

	}while(0);

	if((i_dwUIMask & UIFLAG_WEB_LINK) && bstrTmpHtmlFile != _bstr_t(""))
		DeleteFile(bstrTmpHtmlFile);

	_FreeUIContext(pTheUICtxt);
	DELETE_MEMORY(pTheUICtxt)
	if(pTheOpCtxt)
	{
		DELETE_MEMORY(pTheOpCtxt->pOParams)
	}
	DELETE_MEMORY(pTheOpCtxt)

	FREE_MEMORY(pbEncodedToken)

	return hr;
	
}

HRESULT CVSNZ::_SetUICtxtForVeirfication(IVSPTA* i_pPTA, PUICTXT pTheUICtxt, DWORD i_dwUIMask, 
										 LPCTSTR i_pTmpHtmlFile, NzDetails* i_pNzDetailedInfo) 
{
	HRESULT hr = S_OK;
	WCHAR* pwcharBtnText = NULL;
	WCHAR* pwcharUIStrings = NULL;
	IVSUIPrefs* pPTAUIPRefs = NULL;
	VARIANT varLang;
	VARIANT varFontName;

	do
	{

		//Get the language that is set from the PTA
		hr = i_pPTA->QueryInterface(IID_IVSUIPrefs, (void **)&(pPTAUIPRefs));
		CHECK_HRESULT_BREAK

		hr = pPTAUIPRefs->get_Language(&varLang);
		CHECK_HRESULT_BREAK

		//Set the default language
		pTheUICtxt->nDefLangId = varLang.iVal;

		if(!_IsLangSupported(pTheUICtxt->nDefLangId))
			pTheUICtxt->nDefLangId = LANG_ENGLISH_US;
		
		//Set the UI to be shown
		pTheUICtxt->nWhichWizardAndUI = 0;
		pTheUICtxt->nWhichWizardAndUI = VERIFYRCPT_BASE;
		
		//Set the button text
		pTheUICtxt->pbtnElems = new BTNELEMS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnElems)
	
		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CLOSE,&pwcharBtnText);
		CHECK_HRESULT_BREAK

		//pTheUICtxt->pbtnElems->tbstrBtn1Text = pwcharBtnText;
		//FREE_MEMORY(pwcharBtnText)

		//hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_CANCEL,&pwcharBtnText);
		//CHECK_HRESULT_BREAK

		pTheUICtxt->pbtnElems->tbstrBtn2Text = pwcharBtnText;
		FREE_MEMORY(pwcharBtnText)

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_HELP,&pwcharBtnText);
		CHECK_HRESULT_BREAK

		pTheUICtxt->pbtnElems->tbstrBtn3Text = pwcharBtnText;
		FREE_MEMORY(pwcharBtnText)

		//Set the button functions
		pTheUICtxt->pbtnFns = new BTNFNS;
		CHECK_MEM_BREAK(pTheUICtxt->pbtnFns)
		
		pTheUICtxt->pbtnFns->lpfnBtn1Fn = NULL;
		pTheUICtxt->pbtnFns->lpfnBtn2Fn = VerifyDoneFn;
		pTheUICtxt->pbtnFns->lpfnBtn3Fn = VerifyHelpFn;
		
		//Set the custom font info
		pTheUICtxt->pfontInfoCustomFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoCustomFonts)
		
		pTheUICtxt->pfontInfoCustomFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoCustomFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the default font info
		pTheUICtxt->pfontInfoDefaultFonts = new FONTSINFO;
		CHECK_MEM_BREAK(pTheUICtxt->pfontInfoDefaultFonts)
		
		pTheUICtxt->pfontInfoDefaultFonts->dwCharset = _GetCharset(pTheUICtxt->nDefLangId);
		
		hr=pPTAUIPRefs->get_TitleFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTitleFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);
		
		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrTextFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		hr=pPTAUIPRefs->get_TextFont(&varFontName);
		CHECK_HRESULT_BREAK
		pTheUICtxt->pfontInfoDefaultFonts->tbstrBtnFont = varFontName.bstrVal;
		SysFreeString(varFontName.bstrVal);

		//Set the UI elements
		pTheUICtxt->pvUIElements = (void*)new ALL_VERIFYRCPT_UIELEMENTS;
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrTitle = m_UsrSettings.m_bstrVerifyRcptTitle;
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->theCustUIElements.tbstrText = m_UsrSettings.m_bstrVerifyRcptDescription;

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_VERFYRCPT_TITLE,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrTitle = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)

		hr = _LoadStringW(_Module.m_hInst,pTheUICtxt->nDefLangId,IDS_VERFYRCPTTXT_TEXT,&pwcharUIStrings);
		CHECK_HRESULT_BREAK
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->theDefUIElements.tbstrText = pwcharUIStrings;
		FREE_MEMORY(pwcharUIStrings)
		
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrNotarizedDocumentTitle = i_pNzDetailedInfo->bstrDescription;
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrNotarizedDocument = i_pNzDetailedInfo->bstrNzDocumentName;
		//((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrNotarizedMsg = _GetNotarizedMsgIfText(pTheUICtxt->nDefLangId,i_pNzDetailedInfo->bstrNzDocumentName);

		if (i_dwUIMask & UIFLAG_SAVE_DOC)
		{
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->pbRecordData = i_pNzDetailedInfo->pbRawRecordData;
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->dwRecordDataLen = i_pNzDetailedInfo->dwRawRecordDataLen;
		}
		else
		{
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->pbRecordData = NULL;
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->dwRecordDataLen = 0;
		}

		if (i_dwUIMask & UIFLAG_VIEW_DOC)
		{
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->boolShowViewDocumentLink = TRUE;
		}
		else 
		{
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->boolShowViewDocumentLink = FALSE;
		}

		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrUserAgent = i_pNzDetailedInfo->tbstrUserAgent;

		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrNotary = i_pNzDetailedInfo->bstrNzAuthorityName;
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->nRcptVerificationResult = VERIFY_CORRECT;
		((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrWhoNotarized = i_pNzDetailedInfo->bstrNzRequestor;
		if(i_pNzDetailedInfo->bDocumentModified)
		{
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrTmpHtmlFile = "";
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->nDocumentIntegrityResult = INTEGRITY_INCORRECT;
		}
		else
		{
			// Set the temporary file containing html to be posted to the notarization server
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrTmpHtmlFile = i_pTmpHtmlFile;
			((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->nDocumentIntegrityResult = INTEGRITY_CORRECT;
		}

		hr = _FormatDate(pTheUICtxt->nDefLangId, i_pNzDetailedInfo->NzFormattedSysTime, &((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrDateCreated);
		CHECK_HRESULT_BREAK

		hr = _FormatTime(pTheUICtxt->nDefLangId, i_pNzDetailedInfo->NzFormattedSysTime, &((PALL_VERIFYRCPT_UIELEMENTS)pTheUICtxt->pvUIElements)->tbstrTimeCreated);
		CHECK_HRESULT_BREAK

		//Set the logo urls
		pTheUICtxt->tbstrDefLogoUrl = "";
		pTheUICtxt->tbstrCustLogoUrl = m_UsrSettings.m_bstrLogoUrl;

	}while(0);

	FREE_MEMORY(pwcharBtnText)
	FREE_MEMORY(pwcharUIStrings)

	RELEASE_INTERFACE_PTR(pPTAUIPRefs)

	return hr;
}

#if 0
_bstr_t CVSNZ::_GetNotarizedMsgIfText(LCID locale, _bstr_t i_bstrDocument) 
{
	_bstr_t tbstrRetVal = "";
	CDataAccess DAccObject; 
	BYTE pbData[MAX_READ_SIZE + 1];
	DWORD cbData = MAX_READ_SIZE;
	HRESULT hr;

	do
	{
		hr = DAccObject.Open(i_bstrDocument);
		CHECK_HRESULT_BREAK

		do
		{
			cbData = MAX_READ_SIZE;
			hr = DAccObject.Read(pbData, &cbData);
			CHECK_HRESULT_BREAK

			if(cbData != 0)
			{
				if(! _IsDataTextOnly(locale, pbData, cbData))
				{
					tbstrRetVal = "";
					break;
				}

				pbData[cbData] = '\0';

				tbstrRetVal = tbstrRetVal + _bstr_t((TCHAR*)pbData);
			}

		}while(cbData != 0);

		DAccObject.Close();
	
	}while(0);

	return tbstrRetVal;
}
#endif


VOID CVSNZ::ShowHelp(NZHelpType nzHelpType)
{
	_bstr_t bstrHelpUrl = "";

	switch(nzHelpType)
	{
		case NZ_RECEIPT:
		{
			bstrHelpUrl = m_UsrSettings.m_bstrVerifyRcptHelpUrl;
			break;
		}

		case NZ_PROGRESS_DONE:
		{
			bstrHelpUrl = m_UsrSettings.m_bstrProgressHelpUrl;
			break;
		}
	}

	LaunchApp(bstrHelpUrl);
}


/*
	Return the user agent string obtained from the 'm_spClientSite'. This variable is the IOleClientSite
	interface of the container. If the container is other that IE then this method may not work. In that case
	return the user agent which may have been set via the dll api interface.
*/
HRESULT CVSNZ::_GetUserAgentString(_bstr_t* o_pbstrUserAgent)
{
	HRESULT hr = S_OK;
	IServiceProvider* pISP = NULL;
	IDispatch* pDisp = NULL, *pDispScript = NULL, *pDispNavigator = NULL;
	VARIANT varProperty;

	VariantInit(&varProperty);

	do
	{
		if(!o_pbstrUserAgent)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		*o_pbstrUserAgent = "";

		// Check if the user agent can be obtained from 'm_spClientSite'
		if(m_spClientSite != NULL)
		{
			// Get the service provider from clientsite
			hr = m_spClientSite->QueryInterface(IID_IServiceProvider, (void **)&pISP);
			CHECK_HRESULT_BREAK
		
			pISP->QueryService(SID_SContainerDispatch, IID_IDispatch, (void**)&pDisp);
			CHECK_HRESULT_BREAK

			// From the dispatch obtained, get the "Script" property
			hr = _GetDispProperty(pDisp, IDS_SCRIPT, VT_DISPATCH, &varProperty);
			CHECK_HRESULT_BREAK

			pDispScript = varProperty.pdispVal;

			// From the script obtained, get the "navigator" property
			hr = _GetDispProperty(pDispScript, IDS_NAVIGATOR, VT_DISPATCH, &varProperty);
			CHECK_HRESULT_BREAK

			pDispNavigator = varProperty.pdispVal;

			// From the navigator obtained, get the "user agent" property
			hr = _GetDispProperty(pDispNavigator, IDS_UAGENT, VT_BSTR, &varProperty);
			CHECK_HRESULT_BREAK

			*o_pbstrUserAgent = varProperty.bstrVal;

			VariantClear(&varProperty);
		}

	}while(0);

	if(o_pbstrUserAgent)
	{
		if(*o_pbstrUserAgent == _bstr_t(""))
		{
			// Check if the dll api has set it!
			if(m_bstrUAgent != _bstr_t(""))
				*o_pbstrUserAgent = m_bstrUAgent.copy();
		}
	}

	RELEASE_INTERFACE_PTR(pDispNavigator)
	RELEASE_INTERFACE_PTR(pDispScript)
	RELEASE_INTERFACE_PTR(pDisp)
	RELEASE_INTERFACE_PTR(pISP)

	_LogErrorMsg("CVSZN::_GetUserAgentString().", *o_pbstrUserAgent, NULL, hr);

	return S_OK;	// Always return S_OK
}



HRESULT CancelFn(POPCTXT pOpCtxt)
{
	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
	return E_USERCANCELLED;
}


HRESULT ProgressCancelFn(POPCTXT pOpCtxt)
{
	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->SetCancelled(TRUE);

	return E_USERCANCELLED;
}

HRESULT ProgressDoneFn(POPCTXT pOpCtxt)
{
	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
	return S_OK;
}

HRESULT SelFileHelpFn(POPCTXT pOpCtxt)
{
	return S_OK;
}

HRESULT ProgressHelpFn(POPCTXT pOpCtxt)
{
	((CVSNZ*)pOpCtxt->pvTheVNZObj)->ShowHelp(NZ_PROGRESS_DONE);
	return S_OK;
}

HRESULT VerifyDoneFn(POPCTXT pOpCtxt)
{

	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
	return S_OK;
}

HRESULT VerifyHelpFn(POPCTXT pOpCtxt)
{
	((CVSNZ*)pOpCtxt->pvTheVNZObj)->ShowHelp(NZ_RECEIPT);
	return S_OK;
}

HRESULT ErrorDoneFn(POPCTXT pOpCtxt)
{
	((CDNZUI*)pOpCtxt->pvTheNotUIObj)->put_UIContext(NULL);
	return S_OK;
}

HRESULT ErrorHelpFn(POPCTXT pOpCtxt)
{
	((CVSNZ*)pOpCtxt->pvTheVNZObj)->ShowHelp(NZ_PROGRESS_DONE);	// same help as in case of 'progress help'
	return S_OK;
}


STDMETHODIMP CVSNZ::get_UAgent(VARIANT *pVal)
{
	if(!pVal)
		return E_NZEMPTYARGS;

	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_bstrUAgent.copy();

	return S_OK;
}

STDMETHODIMP CVSNZ::put_UAgent(VARIANT newVal)
{
	if(newVal.vt != VT_BSTR)
		return E_NZINVALIDARGS;

	if(newVal.bstrVal == NULL)
		return E_NZEMPTYARGS;

	m_bstrUAgent = newVal.bstrVal;

	return S_OK;
}

void CVSNZ::SetShowSaveLink(bool boolShowSaveLink)
{
	m_boolShowSaveLink = boolShowSaveLink;
}

#if 0
		DWORD dwBytesWritten, dwEncodedLen;
		BYTE *pbEncodedRecord;

		_Base64Encode((char *)NzResp.pbNzResponse, NzResp.dwNzResponse, NULL, &dwEncodedLen);
		pbEncodedRecord = (PBYTE)malloc(dwEncodedLen + 1);
		
		_Base64Encode((char *)NzResp.pbNzResponse, NzResp.dwNzResponse, (char *)pbEncodedRecord, &dwEncodedLen);
		pbEncodedRecord[dwEncodedLen] = '\0';

		HANDLE hTemp = CreateFile("c:\\temp\\rcpt.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, pbEncodedRecord, dwEncodedLen, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif
