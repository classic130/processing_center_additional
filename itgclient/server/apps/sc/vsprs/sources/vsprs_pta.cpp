///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_Macros.h										 //
//																			 //
//	Description		:	VeriSign Proxy Recipient API for Secure Guaranteed	 //
//                      Messaging Service.                                   //   
//																			 //
//	Date			:	Feb 27, 2000										 //
//																			 //
//	Author			:	Isaac Liu     										 //
//																			 //
//																			 //
//	Change Log		:	- Ramakant 11/01/2001								
//					  Changed functions to incorporate new VSSC parameter
//					  pvarAppStatus
//						- Ramakant 11/06/2001						
//						- Changed the VSPRSInfo structure to make it a pointer	
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vsprs.h"

/////PTA related headers files///////////////

#include "ptav3.h"
#include "ptadllapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"

const IID IID_IVSPTADllApi = {0xa453a978,0x2054,0x11d4,{0x81,0x75,0x00,0x60,0xb0,0xf8,0x85,0xe6}};
const IID IID_IVSPTA = {0x6F7864F8,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const IID IID_IVSRootsUpdate = {0x50E71FEA,0x2234,0x11d4,{0x8D,0x73,0x00,0x60,0xB0,0xFC,0x06,0x37}};


const IID LIBID_PTAV3Lib = {0x6F7864EC,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const CLSID CLSID_VSPTA = {0x6F7864F9,0xDB33,0x11D3,{0x81,0x66,0x00,0x60,0xB0,0xF8,0x85,0xE6}};


const CLSID CLSID_VSROOTS = {0x50E71FEB,0x2234,0x11d4,{0x8D,0x73,0x00,0x60,0xB0,0xFC,0x06,0x37}};

/////VSSC related headers files///////////////

#include "VSSC_i.c"
#include "VSSC.h"

//SelectedCERT currSelCert;

IVSPTA *pVSPTA = NULL;
IVSPTADllApi *pPTADllApi = NULL;
IVSSelectedDigID *pSelDigID = NULL;
IVSUIPrefs* pUIPrefs = NULL;
IVSProfMgmt *pProfMgmt=NULL;
IVSRoamPrefs *pIVSRoamPrefs=NULL;

// VSSC 
IVSSC *pVSSC = NULL;
IVSSCDllApi *pVSSCDllApi = NULL;


HRESULT CProxyRecipients::InitPTA(VARIANT* i_pvarAppStatus)
{
	HRESULT hr=S_OK;
	VARIANT varBool, varUI, varAppName, varHostName, varUseCapi, varProfileName, varAuthDLL;
    VARIANT	varVSSC, varIsRoaming,varClientInfo,varClientInfoSig;


	// use _bstr_t for string conversion.
	_bstr_t bstrTmp;

	varBool.vt=VT_BOOL;
	varBool.boolVal=0;

	varUI.vt=VT_I4;
	varUI.lVal=0;
	
	CoInitialize(NULL);

	do {
		if ((hr = CoCreateInstance(CLSID_VSSC, NULL, CLSCTX_INPROC_SERVER, 
			IID_IVSSC,(void**)&pVSSC)) != S_OK) {
			break;
		}
		// get PTA interface. set some properties for
		// not showing UI, etc.
		
		hr = pVSSC->QueryInterface(IID_IVSSCDllApi, (void**)&pVSSCDllApi);
		if(hr!=S_OK)
			return hr;
		
		hr = pVSSC->QueryInterface(IID_IVSPTA, (void**)&pVSPTA);
		if(hr!=S_OK)
			return hr;

		VARIANT   varInit,varPName,varHName;

		varInit.vt=VT_I2;
		varInit.iVal=0;

		hr=pVSSC->Initialize(&varInit,&varInit,i_pvarAppStatus);
		if(hr!=S_OK)
			return hr;



		varHName.vt = VT_BSTR;
		varHName.bstrVal = SysAllocString(L"localhost");

		pVSSCDllApi->put_HostFQDN(varHName);
		
		varPName.vt = VT_BSTR;
		varPName.bstrVal = SysAllocString(L"http");

		pVSSCDllApi->put_HostProtocol(varPName);
	
		varAppName.vt = VT_BSTR;
		//varAppName.bstrVal = SysAllocString(L"VSSC2");

		varAppName.bstrVal = SysAllocString((bstrTmp = (const char *)mpVSPRSInfo->PTAApplication));

		varProfileName.vt = VT_BSTR;
		varProfileName.bstrVal = SysAllocString((bstrTmp = (const char *)mpVSPRSInfo->PTAProfile));

		varAuthDLL.vt = VT_BSTR;
		varAuthDLL.bstrVal = SysAllocString((bstrTmp = (const char *)mpVSPRSInfo->AuthDLL));

		varUseCapi.vt = VT_I2;
		varUseCapi.iVal = FALSE;	// '1' Use CAPI = YES

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = L"localhost";

		if ((hr = pVSPTA->Initialize(&varAppName, &varUseCapi)) != S_OK)
			break;
	
		if ((hr = pVSPTA -> get_IVSUIPrefs ((IDispatch**) &pUIPrefs )) != S_OK)
			break;

		if ((hr = pVSPTA -> get_IVSProfMgmt((IDispatch**) &pProfMgmt )) != S_OK)
			break;
		
		if ((hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi))) != S_OK)
			break;

		if ((hr = pPTADllApi->put_HostFQDN(varHostName)) != S_OK)
			break;

		// tell it which profile to use.
		if ((hr=pProfMgmt->put_ProfileName(varProfileName)) != S_OK) break;

		// Set the auth dll.
		if ((hr = pVSPTA->put_AuthDll(varAuthDLL)) != S_OK) break;

		if ((hr = pPTADllApi->put_HashData(varBool)) != S_OK) break;
		
		if ((hr = pPTADllApi->put_P7Output(varBool)) != S_OK) break;

		if ((hr = pPTADllApi->put_ShowSignUI(varBool)) != S_OK) break;
	
		if ((hr = pPTADllApi->put_DecryptUI(varUI)) != S_OK) break;
	
		// Setting supported PTA versions
                VariantInit(&varVSSC);
                varVSSC.vt= VT_BSTR;
                varVSSC.bstrVal=_MultiToWideString((PCHAR)(const char *)mpVSPRSInfo->SupportedPTAVersions);
                hr=pVSSC->put_SupportedPTAVer(varVSSC);
                if(hr!=S_OK)
                        return hr;
                VariantClear(&varVSSC);

		VariantClear(&varBool);
		varBool.vt=VT_BOOL;
		varBool.boolVal=FALSE;

		// Check if we need to set certificate resolution to PKCS7
		if (mpVSPRSInfo->CertResSource == YES) {
			varBool.boolVal=TRUE;
		}
			
		if ((hr = pVSSC->put_UsePKCS7Certificate(varBool)) != S_OK) break;

		// Certificate Resolution URL for verifying signatures.
		////// Setting VSSC
		VariantInit(&varVSSC);
		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString(
				(PCHAR)(const char *)mpVSPRSInfo->CertResolutionURL);
		hr=pVSSC->put_CertResolveURL(varVSSC);
		if(hr!=S_OK)
			return hr;

		VariantClear(&varVSSC);
		
		// Certificate SC type Information
		VariantInit(&varVSSC);
		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString(
				(PCHAR)(const char *)mpVSPRSInfo->SCType);
		hr=pVSSC->put_SCType(varVSSC);
		if(hr!=S_OK)
			return hr;

		VariantClear(&varVSSC);

		VariantClear(&varBool);
		varBool.vt=VT_BOOL;
		varBool.boolVal=FALSE;

		if ((hr = pPTADllApi->put_SignNotificationUI(varBool)) != S_OK) break;
	

		if(mRoaming)
		{
			// Set roaming properties
			varIsRoaming.vt = VT_BOOL;
			varIsRoaming.boolVal = TRUE;

			hr = pVSPTA->get_IVSRoamPrefs((IDispatch**)&pIVSRoamPrefs);
			if(hr!=S_OK)
				break;

			varClientInfo.vt = VT_BSTR;
			varClientInfo.bstrVal = _MultiToWideString(
				(PCHAR)(const char *)mpVSPRSInfo->ClientInfo);

			hr = pIVSRoamPrefs->put_ClientInfo(varClientInfo);
			if(hr!=S_OK)
				break;

			varClientInfoSig.vt = VT_BSTR;
			varClientInfoSig.bstrVal = _MultiToWideString(
				(PCHAR)(const char *)mpVSPRSInfo->ClientInfoSig);

			hr = pIVSRoamPrefs->put_ClientInfoSig(varClientInfoSig);
			if(hr!=S_OK)
				break;
		}
		else {
				varIsRoaming.vt = VT_BOOL;
				varIsRoaming.boolVal = FALSE;

		}

	

		hr = pProfMgmt->put_RoamProfile(varIsRoaming);
		if(hr!=S_OK)
			break;
	

	} while (0);

	VariantClear(&varAppName);
	VariantClear(&varProfileName);
	VariantClear(&varAuthDLL);
	VariantClear(&varVSSC);
	VariantClear(&varClientInfo);
	VariantClear(&varClientInfoSig);

	return hr;

}

HRESULT  CProxyRecipients::Release()
{

	

	if(pPTADllApi)
	{
		pPTADllApi->Release();
		pPTADllApi = NULL;
	}

	if(pVSPTA)
	{
		pVSPTA->Release();
		pVSPTA = NULL;
	}

	if (pVSSCDllApi)
	{
		pVSSCDllApi->Release();
		pVSSCDllApi = NULL;
	}

	if (pVSSC)
	{
		pVSSC->Release();
		pVSSC = NULL;
	}
	CoUninitialize();

	return S_OK;


}

