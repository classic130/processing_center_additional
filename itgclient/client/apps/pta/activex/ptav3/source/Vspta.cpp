// VSPTA.cpp : Implementation of CVSPTA


#include "stdafx.h"
#include "langutils.h"
#include "ptadefines.h"

/////////////////////////////////////////////////////////////////////////////
// CVSPTA

//Includes
#include "..\Include\mangleduiprefs.h"
#include "..\Include\mangledprofmgmt.h"
#include "..\Include\mangledcertprefs.h"
#include "..\Include\mangledsrchcrit.h"
#include "..\Include\mangledseldigid.h" 
#include "..\Include\mangledroamprefs.h"
#include "..\Include\mangledptadllapi.h" 
#include "..\include\mangledimport.h"
#include "..\include\mangledexport.h"

#include "..\Include\Ptav3.h"
#include "..\Include\VSPTA.h"

#include "..\Include\VirtualSmartCard.h"

#include "..\Include\utils.h"
#include "..\Include\cspincludes.h" 
#include "..\Include\cspglobals.h"  
#include "certinfo.h"
#include "..\Include\csputil.h"

#include <mshtml.h>
#include <wingdi.h>
#include <hlink.h>
#include <wininet.h>
#include <assert.h>

//Globals
extern CVirtualSmartCard* _gpVirtualSmartCard;
extern CVSPTA* _gpCurrPTA;
extern BOOL _gboolOpenedWithPassword;
extern PSRCHCRIT _gpSrchCrit;

typedef HRESULT (*LPFNGetUsernamePasswd)(VARIANT*, VARIANT*, VARIANT*, VARIANT*, VARIANT*, VARIANT*); 
typedef HRESULT (*LPFNProcessEvent )(VARIANT*);

/*******************************************************/
/*******************************************************/
/*
			IVSPTA methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::Initialize(VARIANT *in_pvarAppCtxtName, VARIANT *in_pvarUseCapi)
{
	int retVal = S_OK;
	_bstr_t tbstrProtocolName;
	_bstr_t tbstrHostName;
	_bstr_t tbstrOpenedProfile;

	/*Input validation*/
	if(!in_pvarAppCtxtName || !in_pvarUseCapi)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	if(in_pvarAppCtxtName->vt != VT_BSTR || in_pvarUseCapi->vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}


	/*Check if we have already been initialized*/
    // since we now allow appctxtname to be set through initialize.
	
	/*
	if(m_bInitialized)
	{
		retVal = E_INITIALIZED;
		_SetErrorInfo(E_INITIALIZED);
		return retVal;
	}
    */

		//Initialize the UI
	if((retVal = m_pPtaUI->Initialize()) != S_OK)
	{
		//Set the error info object. Note - Uncomment set error info if we 
		//return non standard errors.
		//_SetErrorInfo(retVal);
		return retVal;
	}

	//Tell the engine to use capi or non capi
	if((retVal= m_pPtaEngine->Initialize(in_pvarUseCapi->iVal)) != S_OK)
	{
		//Set the error info object 
		//_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get the hostname and the protocol.*/
	tbstrHostName = "";
	tbstrProtocolName = "";
	if((retVal=_GetHostAndProtocol(tbstrHostName, tbstrProtocolName)) != S_OK)
	{
		return retVal; //Note we dont set the err info because the only erro return values 
					   //is the standard E_FAIL
	}

	/*If smart card is open, tell the smartcard that the application has changed*/
/*	if(_gpVirtualSmartCard && tbstrHostName.length() && !in_pvarUseCapi->iVal)
	{
		retVal = _ChangeSmartCardHost((BSTR)tbstrHostName, in_pvarAppCtxtName->bstrVal);
		if(retVal != S_OK)
		{
			//_SetErrorInfo();
			return retVal;
		}
	}
	
*/
	/*Create the app context object*/
	m_pAppCtxt = _CreateAppCtxt();
	if(!m_pAppCtxt)
	{
		return(E_APPCTXTFAILED);
	}

	
	//Save the application context name, hostname, protocolname
	m_pAppCtxt->tbstrAppCtxtName = in_pvarAppCtxtName->bstrVal;
	m_pAppCtxt->tbstrProtocolName = tbstrProtocolName;
	m_pAppCtxt->tbstrHostName = tbstrHostName;
	
	//Convert to lower
	_bstr_t tbstrTemp = m_pAppCtxt->tbstrHostName.copy();
	CharLowerBuff((LPTSTR)tbstrTemp,lstrlen((LPCTSTR)tbstrTemp));
	m_pAppCtxt->tbstrHostName = (LPTSTR)tbstrTemp;


	switch ( in_pvarUseCapi->iVal )
	{
		case 0:
			m_pAppCtxt->nIsCapi	= 0;
			m_pAppCtxt->dwIsTPM = 0;
			break;
		case 1:
			m_pAppCtxt->nIsCapi	= 1;
			m_pAppCtxt->dwIsTPM = 0;
			break;
		case 2:
			m_pAppCtxt->dwIsTPM = 1;
			m_pAppCtxt->nIsCapi	= 0;
			break;
		default:
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
	}
	
	/*Obtain the saved search criteria*/
	retVal = _RestoreSrchCrit();
	
	m_bInitialized = TRUE;

	//	launch update
	{
	

		CoInitialize (NULL);
		
		const CLSID CLSID_NaviClientUpdate = {0xD6C740D2,0x8983,0x4B6E,{0xA4,0x9D,0x85,0xA2,0x31,0x5F,0x92,0x9D}};
		const IID IID_INaviClientUpdate = {0x376B4C53,0x9E73,0x4B6E,{0xA4,0xD6,0x79,0x5A,0x78,0xFB,0x1A,0x11}};

		IDispatch * install = 0;
		if(SUCCEEDED(CoCreateInstance(CLSID_NaviClientUpdate, 0, CLSCTX_LOCAL_SERVER , IID_INaviClientUpdate, (LPVOID *)&install)))
		{

			HRESULT hr = 0;
			_variant_t avarParams[1];
			avarParams[0] = _variant_t("PTA");
			DISPPARAMS params = { avarParams, NULL, 1, 0 };

			hr = install->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, 0, 0, 0);
			install->Release();
		}

		CoUninitialize ();

	}


//	if(!_gpCurrPTA)
//		_gpCurrPTA = this;
	
	return retVal;
}


STDMETHODIMP CVSPTA::AppPref_SetPreference(VARIANT *in_pvarPrefName, VARIANT *in_pvarPrefVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!in_pvarPrefName || !in_pvarPrefVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	if(in_pvarPrefName->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;

	}

	/*Check if we are initialized and we have an app context and a profile is opened*/
	/*Check if a profile is opened*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
/*
	bool allowed = IsThisDomainAllowedToWrite(m_pAppCtxt->tbstrHostName);

	bool allowedApplication = IsThisDomainAllowedToWriteThisApplication(m_pAppCtxt->tbstrHostName);

	if (allowed && allowedApplication)
	{
	*/
	/*Tell the smart card to save the app preference*/
	retVal = _gpVirtualSmartCard->VSM_SetAppPreference(in_pvarPrefName->bstrVal, in_pvarPrefVal, m_pAppCtxt->theOpenProfParams.nFlag & CREATE_APP_IF_NOT_EXIST);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
//		return retVal;
	}
/*
	}
	else
	{
		_SetErrorInfo(E_HOSTBAD);
		retVal = E_HOSTBAD;
	}
*/
	return retVal;
}

STDMETHODIMP CVSPTA::AppPref_GetPreference(VARIANT *in_pvarPrefName, VARIANT *o_pvarPrefValue)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!in_pvarPrefName || !o_pvarPrefValue)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	if(in_pvarPrefName->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;

	}

	/*Check if we are initialized and we have an app context and a profile is opened.*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
/*
	bool allowed = IsThisDomainAllowedToRead(m_pAppCtxt->tbstrHostName);

	bool allowedApplication = IsThisDomainAllowedToReadThisApplication(m_pAppCtxt->tbstrHostName);

	if (allowed && allowedApplication)
	{
	*/
		/*Tell smart card to get the app preference*/
	retVal = _gpVirtualSmartCard->VSM_GetAppPreference(in_pvarPrefName->bstrVal, o_pvarPrefValue);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
//			return retVal;
	}
/*
	}
	else
	{
		_SetErrorInfo(E_HOSTBAD);
		retVal = E_HOSTBAD;
	}
*/

	return retVal;
}

STDMETHODIMP CVSPTA::get_AmITheApplicationCreator(VARIANT *o_pvarIsCreator)
{

	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!o_pvarIsCreator)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and a profile is opened.*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	bool isCreator;
	retVal = _gpVirtualSmartCard->AmITheApplicationCreator(&isCreator);
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	o_pvarIsCreator->vt = VT_BOOL;
	o_pvarIsCreator->boolVal = isCreator;

	return retVal;

}

/*
STDMETHODIMP CVSPTA::get_IsThisHostTheApplicationCreator(VARIANT* i_pvarHostName, VARIANT *o_pvarIsCreator)
{

	HRESULT retVal = S_OK;

	//	Input validation
	if(!i_pvarHostName || !o_pvarIsCreator)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	if(i_pvarHostName->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;

	}

	//	Check if we are initialized and we have an app context and a profile is opened.
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	bool isCreator;
	retVal = _gpVirtualSmartCard->IsThisHostTheApplicationCreator(i_pvarHostName->bstrVal, &isCreator);
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	o_pvarIsCreator->vt = VT_BOOL;
	o_pvarIsCreator->boolVal = isCreator;

	return retVal;

}
*/

/*
bool CVSPTA::IsThisDomainAllowedToRead(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowed = false;
	_bstr_t tbstrProfileOpenHostName = "";

	retVal = _gpVirtualSmartCard->get_VSM_ProfileOpenHostName(&tbstrProfileOpenHostName);

	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return allowed;
	}
	if (i_tbstrHostName != tbstrProfileOpenHostName)
	{		
		_bstr_t* pbstrReadOKDomains;
		DWORD    dwNumOfReadOKDomains;

		retVal = _gpVirtualSmartCard->get_VSM_ReadOKDomains(&pbstrReadOKDomains, &dwNumOfReadOKDomains);
		
		if (retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			return allowed;
		}

		for (unsigned int i = 0; i < dwNumOfReadOKDomains; i++)
		{
			if (pbstrReadOKDomains[i] == i_tbstrHostName)
			{
				allowed = true;
				break;
			}
		}
	}
	else
	{
		allowed = true;
	}
	return allowed;
}

bool CVSPTA::IsThisDomainAllowedToWrite(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowed = false;
	_bstr_t tbstrProfileOpenHostName = "";

	retVal = _gpVirtualSmartCard->get_VSM_ProfileOpenHostName(&tbstrProfileOpenHostName);

	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return allowed;
	}
	if (i_tbstrHostName != tbstrProfileOpenHostName)
	{		
		_bstr_t* pbstrWriteOKDomains;
		DWORD    dwNumOfWriteOKDomains;

		retVal = _gpVirtualSmartCard->get_VSM_WriteOKDomains(&pbstrWriteOKDomains, &dwNumOfWriteOKDomains);
		
		if (retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			return allowed;
		}

		for (unsigned int i = 0; i < dwNumOfWriteOKDomains; i++)
		{
			if (pbstrWriteOKDomains[i] == i_tbstrHostName)
			{
				allowed = true;
				break;
			}
		}
	}
	else
	{
		allowed = true;
	}
	return allowed;
}

bool CVSPTA::IsThisDomainAllowedToReadThisApplication(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowedApplication = false;
		
	_bstr_t* pbstrApplicationReadOKDomains;
	DWORD    dwNumOfApplicationReadOKDomains;

	retVal = _gpVirtualSmartCard->get_VSM_ApplicationReadOKDomains(&pbstrApplicationReadOKDomains, &dwNumOfApplicationReadOKDomains);
		
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		if (retVal == E_VS_INVALID_APP)
		{	
			allowedApplication = true;
			return allowedApplication;
		}
	}

	for (unsigned int i = 0; i < dwNumOfApplicationReadOKDomains; i++)
	{
		if (pbstrApplicationReadOKDomains[i] == i_tbstrHostName)
		{
			allowedApplication = true;
			break;
		}
	}

	return allowedApplication;
}

bool CVSPTA::IsThisDomainAllowedToWriteThisApplication(const _bstr_t i_tbstrHostName)
{

	HRESULT retVal = S_OK;

	bool allowedApplication = false;
		
	_bstr_t* pbstrApplicationWriteOKDomains;
	DWORD    dwNumOfApplicationWriteOKDomains;

	retVal = _gpVirtualSmartCard->get_VSM_ApplicationWriteOKDomains(&pbstrApplicationWriteOKDomains, &dwNumOfApplicationWriteOKDomains);
		
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		if (retVal == E_VS_INVALID_APP)
		{	
			allowedApplication = true;
			return allowedApplication;
		}
	}

	for (unsigned int i = 0; i < dwNumOfApplicationWriteOKDomains; i++)
	{
		if (pbstrApplicationWriteOKDomains[i] == i_tbstrHostName)
		{
			allowedApplication = true;
			break;
		}
	}

	return allowedApplication;
}
*/

STDMETHODIMP CVSPTA::get_CSPName(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_CAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->tbstrCSPName.copy();
	return retVal;
}

STDMETHODIMP CVSPTA::put_CSPName(VARIANT newVal)
{
	int retVal;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_CAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Save the CSPName in the app context.
	m_pAppCtxt->tbstrCSPName = newVal.bstrVal;

	return S_OK;
}

STDMETHODIMP CVSPTA::get_ProtocolName(VARIANT *pVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CVSPTA::put_ProtocolName(VARIANT newVal)
{
	return E_NOTIMPL;
}

STDMETHODIMP CVSPTA::SignRenewal( VARIANT* in_pvarAlgID, VARIANT* o_pvarSignature)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToSign = "";

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarAlgID || !o_pvarSignature)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	/*Check the types of the input params*/
	if(in_pvarAlgID->vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Make sure that the protocol is https*/
	//if((m_pAppCtxt->tbstrProtocolName != _bstr_t("https:")) && (m_pAppCtxt->tbstrProtocolName != _bstr_t("https")))
	//	return E_HTTPSREQD;

	/*Setup the sign challenge parmeters*/
	switch(in_pvarAlgID->iVal)
	{
		case SCRIPT_HASH_MD2 :
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			break;
		case SCRIPT_HASH_MD5 :
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			break;
		case SCRIPT_HASH_SHA1 :
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			break;
		case SCRIPT_HASH_MD2_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
			break;
		case SCRIPT_HASH_MD5_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
			break;
		case SCRIPT_HASH_SHA1_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
			break;
		default:
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
	}

	//Create the challenge to be signed - TODO
	tbstrMessageToSign = "Renew Digital ID";
	m_pAppCtxt->theSignMsgParams.nMsgToSignSize = tbstrMessageToSign.length() * sizeof(CHAR);
	m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = (BYTE*)(CHAR*)tbstrMessageToSign;  

	/*Do the operation*/
	retVal = _DoOperation(LOGIN_WIZARD_BASE, SIGNMSG_BASE);
	
	m_pAppCtxt->theSignMsgParams.nMsgToSignSize = 0;
	m_pAppCtxt->theSignMsgParams.nAlgId = 0;

	m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = NULL;

	o_pvarSignature->vt = VT_BSTR;
	o_pvarSignature->bstrVal = m_tbstrSignature.copy();
	m_tbstrSignature = "";

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}

//	VSPTA_CLEAN_TBSTR(tbstrMessageToSign)

	return retVal;
}

STDMETHODIMP CVSPTA::InstallKeyPair(VARIANT* in_pvarPrivKeyBlob,VARIANT* in_pvarCert)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	//For now this feature will be supported only in non capi mode
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarCert)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	/*Check the types of the input params*/
	if(in_pvarCert->vt != VT_BSTR || in_pvarPrivKeyBlob->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Setup the install cert param*/
	m_pAppCtxt->theInstallCertParams.tbstrCertToInstall = in_pvarCert->bstrVal;
	m_pAppCtxt->theInstallCertParams.tbstrKeyToImport = in_pvarPrivKeyBlob->bstrVal;
	m_pAppCtxt->theInstallCertParams.boolAlsoImportKey = TRUE;
	
	/*Do the operation*/
	if(retVal == S_OK)
	{
		retVal = _DoOperation(NO_WIZARD_BASE, INSTALLCERT_BASE);
		
	}
	else if(retVal = E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	return retVal;
}

STDMETHODIMP CVSPTA::CreateCertReq(VARIANT *in_pvarSubjectDN, VARIANT *in_pvarKeyGenFlag, VARIANT *in_pvarHashAlg, VARIANT *in_pvarAttributes, VARIANT *o_pvarB64EncPKCS10 )
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToSign = "";

	/*Check if we are initialized and we have an app context*/
	//Note for now this feature is only supported for non capi mode
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarSubjectDN|| !in_pvarKeyGenFlag|| !in_pvarHashAlg ||!in_pvarAttributes || !o_pvarB64EncPKCS10)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	/*Check the types of the input params*/
	if((in_pvarSubjectDN->vt != VT_BSTR) || in_pvarHashAlg->vt != VT_I2 || in_pvarKeyGenFlag->vt != VT_I4)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Setup the create cert request params*/
	m_pAppCtxt->theCreateCertReqParams.tbstrSubjectDN = in_pvarSubjectDN->bstrVal;
	switch(in_pvarHashAlg->iVal)
	{
	case SCRIPT_HASH_MD2 :
		m_pAppCtxt->theCreateCertReqParams.nHashAlg = HASH_MD2;
		break;
	case SCRIPT_HASH_MD5 :
		m_pAppCtxt->theCreateCertReqParams.nHashAlg = HASH_MD5;
		break;
	case SCRIPT_HASH_SHA1 :
		m_pAppCtxt->theCreateCertReqParams.nHashAlg = HASH_SHA1;
		break;
	default:
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
	m_pAppCtxt->theCreateCertReqParams.dwKeyGenFlags = in_pvarKeyGenFlag->lVal;


	if(in_pvarAttributes->vt == (VT_ARRAY|VT_VARIANT|VT_BYREF))
	{
		/*Extract the elements of the array.*/
		
		//First obtain and make sure that the array has only two dimensions
		int nDims = SafeArrayGetDim(*(in_pvarAttributes->pparray));
		if(nDims != 2)
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
		}

		//Now obtain the number of elements in each dimension and make sure that the second dimension
		//has a bound of 2
		LONG nNumOfElemsInDim1;
		LONG nNumOfElemsInDim2;

		retVal = SafeArrayGetUBound(*(in_pvarAttributes->pparray), 1, &nNumOfElemsInDim1);
		if(retVal != S_OK)
		{
			_SetErrorInfo(E_SAFEARRAYGETUBOUNDFAILED);
			return E_SAFEARRAYGETUBOUNDFAILED;
		}
		//nNumOfElemsInDim1++;

		retVal = SafeArrayGetUBound(*(in_pvarAttributes->pparray), 2, &nNumOfElemsInDim2);
		if(retVal != S_OK)
		{
			_SetErrorInfo(E_SAFEARRAYGETUBOUNDFAILED);
			return E_SAFEARRAYGETUBOUNDFAILED;
		}
		//nNumOfElemsInDim2++;

		if(nNumOfElemsInDim1 != 2)
		{
			_SetErrorInfo(E_INVALIDARGS);
			return E_INVALIDARGS;
		}

		//Now extract the elements
		m_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs = (_bstr_t*)new _bstr_t[nNumOfElemsInDim1];
		m_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals = (_bstr_t*)new _bstr_t[nNumOfElemsInDim1];
		m_pAppCtxt->theCreateCertReqParams.nNumOfAttributes = nNumOfElemsInDim1;

		retVal = _ExtractBstrsFromArray(*(in_pvarAttributes->pparray), 1, nNumOfElemsInDim1, m_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs);
		if(retVal == S_OK)
		{
			retVal = _ExtractBstrsFromArray(*(in_pvarAttributes->pparray), 2, nNumOfElemsInDim2,m_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals);
		}

		
		
	}
	else if(in_pvarAttributes->vt != VT_EMPTY)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Do the operation*/
	if(retVal == S_OK)
	{
		retVal = _DoOperation(NO_WIZARD_BASE, CREATECERTREQ_BASE);
		if(retVal == S_OK)
		{
			o_pvarB64EncPKCS10->vt = VT_BSTR;
			o_pvarB64EncPKCS10->bstrVal = m_tbstrCertReq.copy();
		}

	}

	delete[] m_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs; 
	m_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs = NULL;
	delete[] m_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals; 
	m_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals = NULL;
	
	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}

//	VSPTA_CLEAN_TBSTR(tbstrMessageToSign)
	
	return retVal;
}

STDMETHODIMP CVSPTA::InstallCert(VARIANT *in_pvarCert)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	//For now this feature will be supported only in non capi mode
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarCert)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	/*Check the types of the input params*/
	if(in_pvarCert->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Setup the install cert param*/
	m_pAppCtxt->theInstallCertParams.tbstrCertToInstall = in_pvarCert->bstrVal;
	
	
	/*Do the operation*/
	if(retVal == S_OK)
	{
		retVal = _DoOperation(NO_WIZARD_BASE, INSTALLCERT_BASE);
		
	}
	else if(retVal = E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	return retVal;

}

STDMETHODIMP CVSPTA::SignChallenge(VARIANT *in_pvarChallenge, VARIANT *in_pvarAlgID, VARIANT* o_pvarSignature)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToSign = "";

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarChallenge || !in_pvarAlgID || !o_pvarSignature)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	/*Check the types of the input params*/
	if((in_pvarChallenge->vt != VT_BSTR) || in_pvarAlgID->vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Make sure that the protocol is https*/
	if((m_pAppCtxt->tbstrProtocolName != _bstr_t("https:")) && (m_pAppCtxt->tbstrProtocolName != _bstr_t("https")))
		return E_HTTPSREQD;

	/*Setup the sign challenge parmeters*/
	switch(in_pvarAlgID->iVal)
	{
		case SCRIPT_HASH_MD2 :
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
			break;
		case SCRIPT_HASH_MD5 :
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
			break;
		case SCRIPT_HASH_SHA1 :
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
			break;
		case SCRIPT_HASH_MD2_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
			break;
		case SCRIPT_HASH_MD5_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
			break;
		case SCRIPT_HASH_SHA1_WITHAUTHATTR:
			m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
			m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
			break;

		default:
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
	}

	if(in_pvarChallenge->vt == VT_BSTR)
	{
		//Create the challenge to be signed - TODO
		tbstrMessageToSign = in_pvarChallenge->bstrVal;
		retVal = _CreateChallengeToBeSigned(tbstrMessageToSign,NULL, &(m_pAppCtxt->theSignMsgParams.nMsgToSignSize) );
		if(retVal == S_OK)
		{
			m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = new BYTE[m_pAppCtxt->theSignMsgParams.nMsgToSignSize];
			if(!m_pAppCtxt->theSignMsgParams.pbyteMsgToSign)
				retVal = E_FAIL;
			else
			{
				retVal = _CreateChallengeToBeSigned(tbstrMessageToSign,m_pAppCtxt->theSignMsgParams.pbyteMsgToSign, &(m_pAppCtxt->theSignMsgParams.nMsgToSignSize));
			}
		}
		
	}
	else 
	{
		//Extract the information from the vt array
	}

	/*Do the operation*/
	retVal = _DoOperation(LOGIN_WIZARD_BASE, SIGNMSG_BASE);
	
	m_pAppCtxt->theSignMsgParams.nMsgToSignSize = 0;
	m_pAppCtxt->theSignMsgParams.nAlgId = 0;

	delete[] m_pAppCtxt->theSignMsgParams.pbyteMsgToSign;
	m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = NULL;

	o_pvarSignature->vt = VT_BSTR;
	o_pvarSignature->bstrVal = m_tbstrSignature.copy();
	m_tbstrSignature = "";

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}

//	VSPTA_CLEAN_TBSTR(tbstrMessageToSign)

	return retVal;
}

STDMETHODIMP CVSPTA::SignTransaction(VARIANT *in_pvarMessage, VARIANT *in_pvarAlgID, VARIANT* o_pvarSignature)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToSign = "";
	PBYTE pbMessageToSign = NULL;
	DWORD dwMessageToSign = 0;

	do
	{

		/*Check if we are initialized and we have an app context*/
		retVal = _CheckEnvironment(CHECK_INIT);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			return retVal;
		}

		if(!in_pvarMessage || !in_pvarAlgID || !o_pvarSignature)
		{	
			retVal = E_EMPTYARGS;
			_SetErrorInfo(E_EMPTYARGS);
			return retVal;
		}	

		/*Check the types of the input params*/
		if((in_pvarMessage->vt != VT_BSTR) && (in_pvarMessage->vt != (VT_ARRAY | VT_UI1)))
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
		}

		/*Setup the sign transaction parmeters*/
		switch(in_pvarAlgID->iVal)
		{
			case SCRIPT_HASH_MD2 :
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
				break;
			case SCRIPT_HASH_MD5 :
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
				break;
			case SCRIPT_HASH_SHA1 :
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = FALSE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
				break;
			case SCRIPT_HASH_MD2_WITHAUTHATTR:
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD2;
				break;
			case SCRIPT_HASH_MD5_WITHAUTHATTR:
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_MD5;
				break;
			case SCRIPT_HASH_SHA1_WITHAUTHATTR:
				m_pAppCtxt->theSignMsgParams.boolAddAuthAttr = TRUE;
				m_pAppCtxt->theSignMsgParams.nAlgId = HASH_SHA1;
				break;
			default:
				retVal = E_INVALIDARGS;
				_SetErrorInfo(E_INVALIDARGS);
				return retVal;
		}

		if(in_pvarMessage->vt == VT_BSTR)
		{
			tbstrMessageToSign = in_pvarMessage->bstrVal;

			// ### BEGIN HTML Validation
			CComPtr<IHTMLDocument2> pHTMLDoc;
			HRESULT hresult = S_OK;
		
			hresult = CoCreateInstance(CLSID_HTMLDocument,NULL,CLSCTX_ALL,IID_IHTMLDocument2,(void **) &pHTMLDoc);

			if (SUCCEEDED(hresult ))
			{
				SAFEARRAY *sfArray;
				BSTR bstr = SysAllocString(OLESTR("some string"));

				// BEGIN create _SOMETHING_ in the document
					sfArray = SafeArrayCreateVector(VT_VARIANT, 0, 1); // Creates a new one-dimensional array
					VARIANT *param;
					hresult = SafeArrayAccessData(sfArray,(LPVOID*) & param);
					param->vt = VT_BSTR;
					param->bstrVal = (BSTR)tbstrMessageToSign;
					hresult = SafeArrayUnaccessData(sfArray);
					hresult = pHTMLDoc->write(sfArray);
					sfArray = NULL;
				// END create something in the doc,

				// Below : get the HTML Body Element from the Document.
				CComPtr<IHTMLElement> pHTMLE;
				if(FAILED( pHTMLDoc->get_body(&pHTMLE))) 
				{
					retVal=E_HTMLMSG_LOAD;
					break;
				}

				_bstr_t bstr1;
				// If this isn't called, IE 4.0 will crash on Win98
				// (might crash on other Win platforms as well.
				if(FAILED( pHTMLE->get_innerHTML((BSTR*)&bstr1)))
				{
					retVal=E_HTMLMSG_LOAD;
					break;
				}

				CComBSTR tempCBSTR((LPCOLESTR)tbstrMessageToSign);
				if(FAILED( retVal = pHTMLE->put_innerHTML(tempCBSTR)))
				{
					// IGNORE THIS ERROR - THIS IS USUALLY CAUSED BY A MSHTML.DLL BUG
					// on windows 98, where the put_innerHTML returns the error code
					// 0x8000000a  
					// HOWEVER - The error code appears to be meaningless,
					// as the rest of the code after this executes without any problems.
					// Because of that, I've commented out the break here.
					// - Ryan D'Silva

					//retVal=E_HTMLMSG_LOAD;
					//break;
				}

				if(FAILED( pHTMLE->get_innerHTML((BSTR*)&bstr1)))
				{
					retVal=E_HTMLMSG_LOAD;
					break;
				}


				if (FAILED(retVal =_TestHTMLDocument(pHTMLDoc)))
				{
					break;	
				}

				// ### END HTML Validation
			}
			else
			{
				// In this case, we're probably dealing with IE 3.02
			}

			m_pAppCtxt->theSignMsgParams.nMsgToSignSize = lstrlen((TCHAR*)tbstrMessageToSign);
			m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = (BYTE*)(CHAR*)tbstrMessageToSign;  

			// Check if message needs to be UTF-8 encoded
			if(m_pAppCtxt->theSignMsgParams.boolUTF8EncodeMsgToSign) 
			{
				int nMessageLen = tbstrMessageToSign.length();
				// the utf8 encoded data will be atmost 3 times the length of unicode data
				int nUTF8DataLen = nMessageLen * 3;
				m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign = new BYTE[nUTF8DataLen];

				if(m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign == NULL)
				{
					retVal = E_OUTOFMEMORY;
					break;
				}

				// UTF-8 encode input data
				int bytes = WideCharToMultiByte(
					CP_UTF8,
					0,
					tbstrMessageToSign,
					nMessageLen,
					(char *) m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign,
					nUTF8DataLen,
					NULL,
					NULL
					);

				if(bytes == 0) {
					delete[] m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign;
					m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign = NULL;
					m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = NULL;
					retVal=E_UTF8_ENCODING_FAILED;
					break;
				} 

				m_pAppCtxt->theSignMsgParams.nUTF8MsgToSignSize = bytes;

			}
		}
		else 
		{
			//Extract the information from the vt array
			retVal = SafeArrayAccessData(in_pvarMessage->parray, (void HUGEP**)&pbMessageToSign);
			if(retVal == S_OK)
			{
				LONG lBound, uBound;
				SafeArrayGetLBound((SAFEARRAY FAR*)in_pvarMessage->parray, 1, &lBound);
				SafeArrayGetUBound((SAFEARRAY FAR*)in_pvarMessage->parray, 1, &uBound);
				dwMessageToSign = uBound - lBound + 1;

				m_pAppCtxt->theSignMsgParams.nMsgToSignSize = dwMessageToSign;
				m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = pbMessageToSign;
			}

		}

		/*Do the operation*/
		if(retVal == S_OK)
		{
			retVal = _DoOperation(SIGN_WIZARD_BASE, SIGNMSG_BASE);
		}

		m_pAppCtxt->theSignMsgParams.nMsgToSignSize = 0;
		m_pAppCtxt->theSignMsgParams.nAlgId = 0;
		if(m_pAppCtxt->theSignMsgParams.boolUTF8EncodeMsgToSign) 
		{
			delete[] m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign;
			m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign = NULL;
		} 

		m_pAppCtxt->theSignMsgParams.pbyteMsgToSign = NULL;

		if(pbMessageToSign)
		{
			SafeArrayUnaccessData(in_pvarMessage->parray);
		}

		o_pvarSignature->vt = VT_BSTR;
		o_pvarSignature->bstrVal = m_tbstrSignature.copy();
		m_tbstrSignature = "";

		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			return retVal;
		}

	//	VSPTA_CLEAN_TBSTR(tbstrMessageToSign)
	}
	while (0);
	
	return retVal;
}




////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_TestHTMLDocument()
//  Purpose:
//		Tests the HTMLDocument2 for a variety of restrictions.
//  
//  Parameters:
//		[*i_pHTMLDocument] :
//  
//  Returns:	HRESULT
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	081901	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_TestHTMLDocument(IHTMLDocument2 *i_pHTMLDocument)
{
	HRESULT retVal=S_OK;

	do
	{	
		long length=0;
		CComPtr<IHTMLElementCollection> pHTMLElemColl,hec1,hec2,hec3,hec4,hec5,hec6,hec7,hec8;
		CComPtr<IHTMLFramesCollection2> pHTMLFrameColl;
		CComPtr<IHTMLStyleSheetsCollection> pHTMLStyleSheetsColl;
		CComPtr<IHTMLElement> pHTMLEBody;

		if(FAILED( i_pHTMLDocument->get_body(&pHTMLEBody))) 
		{
			retVal=E_HTMLMSG_LOAD;
			break;
		}

		// Do a preemptive check for the following elements.
		i_pHTMLDocument->get_scripts(&pHTMLElemColl);
		if (FAILED(pHTMLElemColl->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_SCRIPTS;
			break;
		}
		i_pHTMLDocument->get_embeds(&hec1);
		if (FAILED(hec1->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_EMBEDS;
			break;
		}
		i_pHTMLDocument->get_forms(&hec2);
		if (FAILED(hec2->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_FORMS;
			break;
		}
		i_pHTMLDocument->get_frames(&pHTMLFrameColl);
 		if (FAILED(pHTMLFrameColl->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_FRAMES;
			break;
		}
		i_pHTMLDocument->get_images(&hec3);
		if (FAILED(hec3->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_IMAGES;
			break;
		}
		i_pHTMLDocument->get_applets(&hec4);
		if (FAILED(hec4->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_APPLETS;
			break;
		}
		i_pHTMLDocument->get_plugins(&hec5);
		if (FAILED(hec5->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_PLUGINS;
			break;
		}
		i_pHTMLDocument->get_styleSheets(&pHTMLStyleSheetsColl);
		if (FAILED(pHTMLStyleSheetsColl->get_length(&length)) || length>0)
		{
			retVal=E_HTMLMSG_STYLESHEETS;
			break;
		}

		// Check colors.
		// get the default foreground and background colors for this doc
		VARIANT fgColor, bgColor;
		i_pHTMLDocument->get_bgColor(&bgColor);
		i_pHTMLDocument->get_fgColor(&fgColor);


		htmlDocFGColor = _variant_t(fgColor);
		// check if the default colors are differenciable.
		if (!_IsColorDifferenceNoticeable(htmlDocFGColor,_variant_t(bgColor)))
		{
			retVal = E_HTMLMSG_DEFAULTCOLORDIFF;
			break;
		}


		// Now check elements one by one.
		CComPtr<IUnknown> pUnk;
		CComPtr<IHTMLElementCollection> pAllHTMLElemColl;

		// Get all the elements in this document.
		i_pHTMLDocument->get_all(&pAllHTMLElemColl);

		// query for the collection
		//disp->QueryInterface(IID_IHTMLElementCollection,(void **) &pAllHTMLElemColl);

 		CComPtr<IEnumVARIANT> pNewEnum;
		VARIANT varElement;

		// get the ENUMERATIOn from the collection
		if (pAllHTMLElemColl!=NULL && SUCCEEDED(pAllHTMLElemColl->get__newEnum(&pUnk)) && pUnk != NULL)
		{
			// get the EnumVARIANT which points to the HTML Elements in the collection.
			retVal = pUnk->QueryInterface(IID_IEnumVARIANT,(void**)&pNewEnum);
			if(retVal != S_OK)
			{
				retVal = E_HTMLMSG_LOAD;
				break;
			}
			
			CComPtr<IHTMLElement> pElement;
			CComBSTR tagName;

			// Go through the enumeration
			if (retVal = pNewEnum->Next(1, &varElement, NULL) == S_OK)
			{
				// get the IHTMLElement
				varElement.pdispVal->QueryInterface(IID_IHTMLElement,(void**)&pElement);
				if (pElement)
				{
					pElement->get_tagName(&tagName);
					// check each elements recursively

					if ( (FAILED(retVal = _CheckElement(pElement, bgColor))))
					{
						break;
					}
				}
				else
				{
					retVal = E_HTMLMSG_LOAD;
				}

				// and then clear the VARIANT for recycling.
				VariantClear(&varElement);
				pElement = NULL;
			}
		}
		else
		{
			retVal = E_HTMLMSG_LOAD;
		}
	// retVal might or might not be S_OK here.
	} while(0);

	return retVal;
}

////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_TagNotAllowed()
//  Purpose:
//		Check if this tag is allowed by the HTML Signing
//  
//  Parameters:
//		[*tagName] :
//  
//  Returns:	bool
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	100501	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
bool CVSPTA::_TagNotAllowed(CComBSTR *tagName)
{
	tagName->ToUpper();
	_bstr_t currentTag = (*tagName);
	bool tagNotAllowed=true;
	
	for (int i=0;i<nbOfAllowedTags;i++)
	{
		if (currentTag == allowedTags[i])
		{
			tagNotAllowed = false;
			break;
		}
	}

	return tagNotAllowed; // false if this is ok..
}



////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_IsAttributeOk()
//  Purpose:
//		Check if this attribute is allowed by the HTML Signing
//  
//  Parameters:
//		[*tagName] :
//  
//  Returns:	bool
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	100501	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
bool CVSPTA::_IsAttributeOk(char *attrName)
{
	bool attrAllowed=false;
	CComBSTR  tempCBSTR(attrName);
	tempCBSTR.ToUpper();
	_bstr_t currentAttr = tempCBSTR;
	
	for (int i=0;i<nbOfAllowedAttrs;i++)
	{
		if (currentAttr == allowedAttrs[i])
		{
			attrAllowed = true;
			break;
		}
	}

	return attrAllowed; // false if this is ok..
}


////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_AttributeNotAllowed()
//  Purpose:
//		Checks if the attributes of the text have an attribute that isn't on the 
//		"allowedAttributes" list.
//  
//  Parameters:
//		[*tagName] :
//  
//  Returns:	bool
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	110501	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
bool CVSPTA::_AttributeNotAllowed(CComBSTR *innerText)
{
//	This is broken up into 2 state machines
//	The first one gets past the tag name, and the second state machine parses all the 
//	attribute names.


	int length=0;	
    char *innerTextChars = NULL;
	length = innerText->Length();
	if (length > 0)
	{
		innerTextChars = new char[length+1];
		memset(innerTextChars, 0, length+1);
		WideCharToMultiByte(CP_ACP, 0, (BSTR) (*innerText), length, innerTextChars,
		length+1, NULL, NULL);
	
		int state =1, i=0;
		bool keepGoing = true;
		char charToSkip = ' ';

		// first state machine
		while(i<length && keepGoing)
		{
			switch (state )
			{
				case 1: // skip whitespaces
					{
						if (!isspace(innerTextChars[i])) // if we're at the end of the spaces
						{
							state++;
						}
						else
						{
							i++;
						}

					}
				break;
				case 2: // looking for "<" entry point
					{
						if (innerTextChars[i] == '<') // if we're at the end of the entry point
						{
							i++;
							state++;
						}
						else
						{    // there is no "<" sign.
							delete []innerTextChars;		
							return false;
						}

					}
				break;
				case 3: // looking for characters
					{
						if (!isalnum(innerTextChars[i]) ) // if we're at the end of the characters
						{
							state++;
						}
						else
						{
							i++;
						}
					}
				break;
				case 4: // looking for spaces
					{
						if (!isspace(innerTextChars[i])) // if we're at the end of the spaces again
						{
							// now pointing at the first attribute, or the ">"
							keepGoing = false;
						}
						else
						{
							i++;
						}
					}
				break;
				default: // anything else is just wrong.
					delete []innerTextChars;		
					return true; // shouldn't be here.
				break;
			}
		}
		// Now past the initial tag 
		// upcoming format [name  =  "value"] ">"
		//i--; // set up the pointer to it's previous position.
		char *attrName=0;
		int beginAttr=0;
		keepGoing = true;
		state =1;
		bool lookForEndQuote = false;
		char quoteMark='"';

		// second state machine - Attributes.
		while(i<length  && keepGoing)
		{	
			
			switch (state )
			{
				case 1: // looking for spaces
					{
						if (!isspace(innerTextChars[i])) // if we're at the end of the spaces
						{
							state =2;
						}
						else
						{
							i++;
						}
					}
				break;
				case 2: // looking for end of tag
					{
						if (innerTextChars[i] == '>') // if we're at the end of the tag
						{
							delete []innerTextChars;		
							return false; // no bad attributes found.
						}
						else
						{
							state=3;
						}
					}
				break;
				case 3: // looking for beginning of attribute
					{
						state = 4;
						beginAttr=i;
					}
				break;
				case 4: // looking for end of attribute
					{
						if (!isalnum(innerTextChars[i]))
						{
							//check Attribute...
							int attrLen = i-beginAttr;
							char *attr=new char[i-beginAttr+1];
							for (int j=0;j<attrLen;j++)
							{
								attr[j]=innerTextChars[beginAttr+j];
							}
							attr[j]='\0'; // terminate the attribute string.
							if (_IsAttributeOk(attr))
							{
								delete []attr;
								state ++;
							}
							else
							{
								delete []attr;
								delete []innerTextChars;		
								return true;
							}
						}
						else
						{
							i++;
						}
					}
				break;
				case 5: // looking for "="
					{
						if (!isspace(innerTextChars[i])) // if we're at the end of the spaces
						{
							state++;
						}
						else
						{
							i++;
						}
					}
				break;
				case 6: // looking for "="
					{
						if (innerTextChars[i] == '=') // if we find the "=" sign
						{
							i++;
							state++;
						}
						else
						{
							delete []innerTextChars;		
							return true; // invalid HTML - no "=" after an attribute name?
						}
					}
				break;
				case 7: // looking for end of spaces
					{
						if (!isspace(innerTextChars[i])) // if we're at the end of the spaces
						{
							state++;
						}
						else
						{
							i++;
						}
					}
				break;
				case 8: // looking for "\""
					{
						if (innerTextChars[i] == '"'    ||   innerTextChars[i] == '\'' ) // if we're at the end of the spaces
						{
							lookForEndQuote = true;
							quoteMark=innerTextChars[i];
							i++;
						}
						state++;
					}
				break;
				case 9: // looking for end of value
					{
						// look for any sign of an end..
						if (lookForEndQuote)
						{
							if (innerTextChars[i] != quoteMark)
							{
								i++;
							}
							else
							{
								i++;
								state=1;
							}
						}
						else
						{
							if (isspace(innerTextChars[i]) || innerTextChars[i] == '>')
							{
								state=1; // jump back to beginning..
							}
							else
							{
								i++;
							}
						}
					}
				break;
				default: // looking for spaces
					{
						delete []innerTextChars;		
						return false;
					}
				break;
			}
		
		}
	}	

	delete []innerTextChars;		
	return false;
}



////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_CheckElement()
//  Purpose:
//		Traverses down the elements in the HTML document recursively.
//		for a color scheme which might obfuscate 
//		text.
//
//  Parameters:
//		[*i_pHTMLElem] :
//		[bgColor] :
//  
//  Returns:	HRESULT
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	081901	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_CheckElement(IHTMLElement *i_pHTMLElem, _variant_t i_pvarBgColor)
{
	_bstr_t p_bstrFgColorAttrName("color");
	_bstr_t p_bstrBgColorAttrName("bgcolor");
	//BSTR innerText;
	CComPtr<IHTMLStyle> pHTMLStyle;
	_variant_t p_FgColorVal;
	_variant_t p_BgColorVal;
	_variant_t p_StyleFgColorVal;
	_variant_t p_StyleBgColorVal;
	CComBSTR id, tag, innerText;
	CComPtr<IDispatch> disp; 
	CComPtr<IHTMLElementCollection> pHTMLElemColl;
	CComPtr<IUnknown> pUnk;
	HRESULT retVal=S_OK;

	do
	{
		i_pHTMLElem->get_tagName(&tag);

		// do check for tag type
		if (_TagNotAllowed((CComBSTR*) &tag))
		{
			retVal = E_HTMLMSG_BADTAG;
			break;
		}

		i_pHTMLElem->get_outerHTML(&innerText);

		if (_AttributeNotAllowed((CComBSTR*) &innerText))
		{
			retVal = E_HTMLMSG_BADTAG;
			break;
		}

		////////////  NOTE ////////////////

		// FONTs and TABLEs. Currently, FONT attributes don't apply inside a table when a font
		// is simply wrapped around it. 
		// This is according to the HTML spec.
		// On the chance that this changes (i.e. wrapping a table in a font tag actually affects the table)
		// the checking below should be changed to add one more check,
		// and the checkelement should pass in it's the fg color recursively so that the checks can be 
		// run on it in the successive nested tags.

		// Color diff. checking.
		// get bg color specified by the tag
		if ((SUCCEEDED(i_pHTMLElem->getAttribute(p_bstrBgColorAttrName,0,&p_BgColorVal)) 
			&& ( (p_BgColorVal.vt != VT_NULL) && (SysStringLen(p_BgColorVal.bstrVal)>5) )))
		{ 
			// def_fg vs new bg
			if (!_IsColorDifferenceNoticeable(htmlDocFGColor, p_BgColorVal))
			{
				retVal = E_HTMLMSG_COLORDIFF;
				break;
			}
			// get fg
			if ((SUCCEEDED(i_pHTMLElem->getAttribute(p_bstrFgColorAttrName,0,&p_FgColorVal)))
				&& (p_FgColorVal.vt != VT_NULL) && (SysStringLen(p_FgColorVal.bstrVal)>5) )
			{
				// new fg vs new bg
				if (! _IsColorDifferenceNoticeable(p_FgColorVal,p_BgColorVal)) 
				{
					retVal = E_HTMLMSG_COLORDIFF;
					break;
				}
			}
			// make sure the new background color is passed on.
			i_pvarBgColor = p_BgColorVal;
		}
		else
		{
			// get fg
			if ((SUCCEEDED(i_pHTMLElem->getAttribute(p_bstrFgColorAttrName,0,&p_FgColorVal)))
				&& (p_FgColorVal.vt != VT_NULL) && (SysStringLen(p_FgColorVal.bstrVal)>5) )
			{
				// new fg vs old bg
				if (! _IsColorDifferenceNoticeable(p_FgColorVal,i_pvarBgColor)) 
				{
					retVal = E_HTMLMSG_COLORDIFF;
					break;
				}
			}

		}

		

		// check for the STYLE tag. eg.
		// <h1 ALIGN="center" STYLE="background: #000080;">Invisible text</h1>
		VARIANT_BOOL caseSensitive = 0; 
		VARIANT_BOOL success=0;
		if (SUCCEEDED(i_pHTMLElem->removeAttribute(L"STYLE",caseSensitive,&success)) && success !=0)
		{
				retVal = E_HTMLMSG_STYLESHEETS;
				break;
		}

		// Explore the child tags.
		i_pHTMLElem->get_children(&disp);

		// query for the collection
		CComPtr<IHTMLElementCollection> childHTMLElemColl;
		disp->QueryInterface(IID_IHTMLElementCollection,(void **) &childHTMLElemColl);

 		CComPtr<IEnumVARIANT> pNewEnum;
		VARIANT varElement;

		// get the ENUMERATIOn from the collection
		if (childHTMLElemColl!=NULL && SUCCEEDED(childHTMLElemColl->get__newEnum(&pUnk)) && pUnk != NULL)
		{
			// get the EnumVARIANT which points to the HTML Elements in the collection.
			retVal = pUnk->QueryInterface(IID_IEnumVARIANT,(void**)&pNewEnum);
			if(retVal != S_OK)
			{
				retVal = E_HTMLMSG_LOAD;
				break;
			}
			
			CComPtr<IHTMLElement> pElement;
			CComBSTR tagName;

			// Go through the enumeration
			while (retVal = pNewEnum->Next(1, &varElement, NULL) == S_OK)
			{
				// get the IHTMLElement
				varElement.pdispVal->QueryInterface(IID_IHTMLElement,(void**)&pElement);
				if (pElement)
				{
					pElement->get_tagName(&tagName);
					// check each elements recursively

					if ( (FAILED(retVal = _CheckElement(pElement, i_pvarBgColor))))
					{
						break;
					}
				}
				else
				{
					retVal = E_HTMLMSG_LOAD;
				}

				// and then clear the VARIANT for recycling.
				VariantClear(&varElement);
				pElement = NULL;
			}
		}
	}	
	while(0);

	return retVal;
}


////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_IsColorDifferenceNoticeable()
//  Purpose:
//		Verifies that the Color Difference betwwen the foreground and background 
//		colors is great enough to be noticeable by someone with a 256 color display.
//  
//  Parameters:
//		[i_varForeGroundColor] :
//		[i_varBackGroundColor] :
//  
//  Returns:	boolean
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	081701	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
boolean	CVSPTA::_IsColorDifferenceNoticeable(_variant_t i_varForeGroundColor, _variant_t i_varBackGroundColor)
{
	if ( (i_varForeGroundColor.vt == VT_NULL) || (i_varBackGroundColor.vt == VT_NULL) )
	{
		return false;
	}
	//MessageBox("Got to the color diff check","Debug");

	long fgColor = _RGBStrtoLong((char*)( (_bstr_t) i_varForeGroundColor) );
	long bgColor = _RGBStrtoLong((char*)( (_bstr_t) i_varBackGroundColor) );
	// NOTE : the color difference graph was changed.
	// Old deltas were 20 and 83 respectively. The Old slope was 4
	// NEW Deltas are 63 and 127. The New slope is 4

	//MessageBox("Got past the RGBStrToLong ","Debug");
	// the darker the background is, the more difference (delta) is needed for the foreground
	// If the background is pure black (0,0,0 or 000000) the delta between the background and foreground 
	// has to be 127*3
	// if background is white (255,255,255 or ffffff) the delta only needs be 63*3

	// the derivative of that graph is 4 (sloping up as the background color darkens).

	// The DARKER it is -  the more delta is needed.

	//###	slope is 1/4

	//  |*****************/ .... 127
	//  |**************/
	//  |***********/                  Delta needed per color component 
	//  |*******/                      to differentiate between colors
	//  |****/ .......... 63           NOT TO SCALE
	//  |
	//  |-------------------------
	//      -- Darkness ++
	//   white  ---------> black
	// all delta's above the line (the stars)  are allowed.



	// this gets the background's 'darkness' .
	int delta =0;
	// 765 is == 255*3
	int darkness = 765 - (((bgColor&0xff0000)>>16) + ((bgColor&0x00ff00)>>8) + (bgColor&0x0000ff));
	// eg. for white, it would be 0 and for black, it would be 765

	// this gets in the delta required per color component for this background
	//### new delta 189 = 63 * 3

	// and the total delta is 

	delta = darkness/4 + 189;

	// this calculates the delta for the 2 colors passed in
	int redColDiff = abs((fgColor&0xff0000) - (bgColor&0xff0000)) >> 16;
	int greenColDiff = abs((fgColor&0x00ff00) - (bgColor&0x00ff00)) >> 8;
	int blueColDiff = abs((fgColor&0x0000ff) - (bgColor&0x0000ff));

	int colorDiffSaturation = redColDiff + greenColDiff + blueColDiff;

	// and finally it returns the result
	return (colorDiffSaturation > delta); 
	// if colorDiff is greater than delta - return true
}



////////////////////////////////////////////////////////////////////////////////////////
//  CVSPTA::_RGBStrtoLong()
//  Purpose:
//		Converts a 6 character Hex String (the RGB code for a color in this case) to 
//		a 'long' value.
//  
//  Parameters:
//		[*i_rgbStr] :
//  
//  Returns:	long
//  
//  Change Log
//		Author					MMDDYY	Description
//		--------------------	------	------------------------------------------------
//		Ryan D'Silva        	081701	Initial Version
//  
//		
////////////////////////////////////////////////////////////////////////////////////////
long CVSPTA::_RGBStrtoLong(char *i_rgbStr)
{
	long rgbVal=0;
	int nibble=0;	
	if (i_rgbStr)
	{
		while( !(isxdigit(*i_rgbStr)) )
		{
			i_rgbStr++;
		}
		while ( (*i_rgbStr) && isxdigit(*i_rgbStr) )
		{
			nibble = *i_rgbStr++ - '0';
			if (nibble > 9)
			{	
				nibble -= 7;
			}
			rgbVal <<=4;
			rgbVal |= (nibble & 0x0f);
		}
	}
	return rgbVal;
}




STDMETHODIMP CVSPTA::Close()
{
	HRESULT retVal = S_OK;

	if(m_bInitialized)
	{
		m_bInitialized = FALSE;

//		if(_gpCurrPTA == this)
//			_gpCurrPTA = NULL;

		/*Save the search criteria, to maintain state*/
		retVal = _SaveSrchCrit();
		if(retVal != S_OK)
		{
			return retVal;
		}

		/*Tell the engine to destroy the selected certificate context*/
		if(m_pPtaEngine->FreeIdList(m_pSelectedId) != S_OK)
		{
			return (E_FAIL);
		}
		m_pSelectedId = NULL;

		/*Destroy the app context*/
		if(_FreeAppCtxt(m_pAppCtxt) != VS_OK)
		{
			return(E_FAIL);
		}

		m_pAppCtxt = NULL;

		/*Close the engine*/
		retVal = m_pPtaEngine->Close();
		if(retVal != S_OK)
		{
			return retVal;
		}

		/*Close the UI*/
		retVal = m_pPtaUI->Close();
		if(retVal != S_OK)
		{
			return retVal;
		}

		if(m_spOuterClientSite)
		{
			m_spOuterClientSite.Release();
			m_spOuterClientSite = NULL;
		}
	}

	return retVal;
}

STDMETHODIMP CVSPTA::SelIDForChallenge()
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Do the operation*/
	retVal = _DoOperation(LOGIN_WIZARD_BASE, (SELID_BASE));
	if(retVal == E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}
	else if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	return retVal;
}

STDMETHODIMP CVSPTA::SelIDForTrans()
{
	HRESULT retVal = S_OK; 

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Do the operation*/
	retVal = _DoOperation(SIGN_WIZARD_BASE, (SELID_BASE));
	if(retVal == E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}
	else if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_UseDefCertFlag(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theSrchCrit.boolUseDefault;
	return retVal;
}

STDMETHODIMP CVSPTA::put_UseDefCertFlag(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Save the CSPName in the app context.
	m_pAppCtxt->theSrchCrit.boolUseDefault = (BOOL)newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_AuthDll(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->tbstrAuthDll.copy();
	return retVal;
}

STDMETHODIMP CVSPTA::put_AuthDll(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Save the auth dll name
	m_pAppCtxt->tbstrAuthDll = newVal.bstrVal;

	/*Try to load this dll*/
	m_pAppCtxt->hModAuthDll = LoadLibrary(m_pAppCtxt->tbstrAuthDll);
	if(!m_pAppCtxt->hModAuthDll)
	{
		m_pAppCtxt->tbstrAuthDll = "";
		retVal = E_AUTHDLLNOTPRESENT;
		_SetErrorInfo(retVal);
	}
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_IVSUIPrefs(IDispatch **pVal)
{
	// Get a pointer to the IVSUIPrefs interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSUIPrefs);
	if(!*pVal)
		return E_NOINTERFACE;  
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSProfMgmt(IDispatch **pVal)
{
	// Get a pointer to the IVSUIProfMgmt interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSProfMgmt);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSCertPrefs(IDispatch **pVal)
{
	// Get a pointer to the IVSUIPrefs interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSCertPrefs);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSSrchCrit(IDispatch **pVal)
{
	// Get a pointer to the IVSSrchCrit interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSSrchCrit);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSSelectedDigID(IDispatch **pVal)
{
	// Get a pointer to the IVSelectedDigID interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSSelectedDigID);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}


STDMETHODIMP CVSPTA::get_IVSRoamPrefs(IDispatch **pVal)
{
	// Get a pointer to the IVSRoamPrefs interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSRoamPrefs);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSP12Import(IDispatch **pVal)
{
	// Get a pointer to the IVSRoamPrefs interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSP12Import);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_IVSP12Export(IDispatch **pVal)
{
	// Get a pointer to the IVSRoamPrefs interface and return it.
	*pVal = (IDispatch*)GetInterface(IID_IVSP12Export);
	if(!*pVal)
		return E_NOINTERFACE;
	return S_OK;
}

STDMETHODIMP CVSPTA::get_ProfileIssFrndlyName(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
		/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the profile name form the Virtual Smart Card */
		retVal = _gpVirtualSmartCard->get_VSM_ProfileIssFrndlyName(pVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);

		}
	}
	else
	{
		/*Get the profile name*/
		pVal->vt = VT_BSTR;
		pVal->bstrVal = m_pAppCtxt->tbstrProfileIssFrndlyName.copy();
	}

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfileIssFrndlyName(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

		/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		retVal = _gpVirtualSmartCard->put_VSM_ProfileIssFrndlyName(&newVal);

	}

	//Save the profile issuer friendly name
	m_pAppCtxt->tbstrProfileIssFrndlyName = newVal.bstrVal;

	retVal = S_OK;

	return retVal;

}

STDMETHODIMP CVSPTA::get_ProfileIssUniqueId(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->tbstrProfileIssUniqueId.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfileIssUniqueId(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Save the profile issuer friendly name
	m_pAppCtxt->tbstrProfileIssUniqueId = newVal.bstrVal;

	
	return retVal;
}

STDMETHODIMP CVSPTA::CreatePassword()
{
	HRESULT retVal = S_OK;

	retVal = _DoOperation(NO_WIZARD_BASE, CREATEPASSWD_BASE);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
	}

	return retVal;
}

STDMETHODIMP CVSPTA::EnterPassword()
{
	HRESULT retVal = S_OK;

	retVal = _DoOperation(NO_WIZARD_BASE, ENTERPASSWD_BASE);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
	}

	return retVal;
}

//Begin Telia Bug Fix
STDMETHODIMP CVSPTA::DisableNonRepudiationCertKeyUsage()
{
	HRESULT retVal = S_OK;

	retVal = m_pPtaEngine->DoDisableNRKeyUsage(m_pAppCtxt->theSrchCrit, m_pAppCtxt->tbstrAppCtxtName);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
	}

	return retVal;
}
//End Telia Bug Fix

/*******************************************************/
/*******************************************************/
/*
			IVSProfMgmt methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::ProfMgmt_OpenProfile()
{
	HRESULT retVal = S_OK;


	/*Check if we are initialized and we have an app context and this is
	non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	/*Check if a profile is open or not*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		_SetErrorInfo(E_CARDALREADYOPEN);
		return E_CARDALREADYOPEN;
	}

	/*Do the operation*/
	retVal = _DoOperation(NO_WIZARD_BASE, (m_pAppCtxt->theOpenProfParams.nFlag & OPERATION_BITS));
	if(retVal == E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}
	else if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	

	return retVal;
}

STDMETHODIMP CVSPTA::ProfMgmt_CloseProfile()
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context and this is
	non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Close the smart card*/
	retVal = _gpVirtualSmartCard->VSM_Close();

	delete _gpVirtualSmartCard;
	_gpVirtualSmartCard = NULL;
	_gboolOpenedWithPassword = TRUE;

	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_ReadOKDomains(VARIANT *o_pvarReadOKDomains)
{
	HRESULT			retVal				= S_OK;
	_bstr_t*		pbstrReadOKDomains;
	DWORD			nNumOfReadOKDomains = 0;
	SAFEARRAY*		psa;

	/*Input validation*/
	if(!o_pvarReadOKDomains)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the list of read ok domains from the smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_ReadOKDomains(&pbstrReadOKDomains, &nNumOfReadOKDomains);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}
		else
		{

			long ix[1];

			SAFEARRAYBOUND rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = nNumOfReadOKDomains;
			psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

			for (unsigned int i = 0; i < nNumOfReadOKDomains; i++) {
			
				VARIANT var;
				ix[0] = i;

				var.vt = VT_BSTR;
				var.bstrVal = (pbstrReadOKDomains[i]).copy();
				SafeArrayPutElement(psa, ix, &var);
				VariantClear(&var);
			}

			o_pvarReadOKDomains->vt = VT_ARRAY|VT_VARIANT;
			o_pvarReadOKDomains->parray = psa;	

			retVal = S_OK;
		}
	}
	else
	{
		//A profile is not open. Return the read ok domain from our storage
		retVal = VariantCopy(o_pvarReadOKDomains,&(m_pAppCtxt->theOpenProfParams.theCreateParams.varReadOKDomains));
	}

	
	return retVal;

}

STDMETHODIMP CVSPTA::put_ProfMgmt_ReadOKDomains(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the domains that are allowed to read the profile.*/
		retVal = _gpVirtualSmartCard->put_VSM_ReadOKDomains(&newVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}
	else
	{
		//A profile is not open. Store the read ok domains in the open profile parameter structure
		retVal = VariantCopy(&(m_pAppCtxt->theOpenProfParams.theCreateParams.varReadOKDomains), &newVal);
		retVal = S_OK;
	}

	

	return retVal;


}

STDMETHODIMP CVSPTA::get_ProfMgmt_WriteOKDomains(VARIANT *o_pvarWriteOKDomains)
{
	HRESULT			retVal				= S_OK;
	_bstr_t*		pbstrWriteOKDomains;
	DWORD			nNumOfWriteOKDomains = 0;
	SAFEARRAY*		psa;

	/*Input validation*/
	if(!o_pvarWriteOKDomains)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the list of Write ok domains from the smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_WriteOKDomains(&pbstrWriteOKDomains, &nNumOfWriteOKDomains);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}
		else
		{

			long ix[1];

			SAFEARRAYBOUND rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = nNumOfWriteOKDomains;
			psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

			for (unsigned int i = 0; i < nNumOfWriteOKDomains; i++) {
			
				VARIANT var;
				ix[0] = i;

				var.vt = VT_BSTR;
				var.bstrVal = (pbstrWriteOKDomains[i]).copy();
				SafeArrayPutElement(psa, ix, &var);
				VariantClear(&var);
			}

			o_pvarWriteOKDomains->vt = VT_ARRAY|VT_VARIANT;
			o_pvarWriteOKDomains->parray = psa;	

			retVal = S_OK;
		}
	}
	else
	{
		//A profile is not open. Return the Write ok domain from our storage
		retVal = VariantCopy(o_pvarWriteOKDomains,&(m_pAppCtxt->theOpenProfParams.theCreateParams.varWriteOKDomains));
	}

	
	return retVal;

}


STDMETHODIMP CVSPTA::put_ProfMgmt_WriteOKDomains(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the domains that are allowed to write the profile.*/
		retVal = _gpVirtualSmartCard->put_VSM_WriteOKDomains(&newVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}
	else
	{
		//A profile is not open. Store the write ok domains in the open profile parameter structure
		retVal = VariantCopy(&(m_pAppCtxt->theOpenProfParams.theCreateParams.varWriteOKDomains), &newVal);
		retVal = S_OK;
	}


	return retVal;

}


STDMETHODIMP CVSPTA::put_ProfMgmt_ProfileOpenHostWildCard(VARIANT newVal)
{

	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Tell the Virtual Smart Card the new wild-card character.*/
	retVal = _gpVirtualSmartCard->put_VSM_ProfileOpenHostWildCard(newVal.bstrVal);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
	}

	return retVal;

}

STDMETHODIMP CVSPTA::put_ApplicationCreatorWildCard(VARIANT newVal)
{

	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if (retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Tell the Virtual Smart Card the new wild-card for the application creator.*/
	retVal = _gpVirtualSmartCard->put_VSM_ApplicationCreatorWildCard(newVal.bstrVal);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
	}

	return retVal;

}

STDMETHODIMP CVSPTA::get_ApplicationReadOKDomains(VARIANT *o_pvarApplicationReadOKDomains)
{
	HRESULT			retVal				= S_OK;
	_bstr_t*		pbstrApplicationReadOKDomains;
	DWORD			nNumOfApplicationReadOKDomains = 0;
	SAFEARRAY*		psa;

	/*Input validation*/
	if(!o_pvarApplicationReadOKDomains)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the list of read ok domains from the smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_ApplicationReadOKDomains(&pbstrApplicationReadOKDomains, &nNumOfApplicationReadOKDomains);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}
		else
		{

			long ix[1];

			SAFEARRAYBOUND rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = nNumOfApplicationReadOKDomains;
			psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

			for (unsigned int i = 0; i < nNumOfApplicationReadOKDomains; i++) {
			
				VARIANT var;
				ix[0] = i;

				var.vt = VT_BSTR;
				var.bstrVal = (pbstrApplicationReadOKDomains[i]).copy();
				SafeArrayPutElement(psa, ix, &var);
				VariantClear(&var);
			}

			o_pvarApplicationReadOKDomains->vt = VT_ARRAY|VT_VARIANT;
			o_pvarApplicationReadOKDomains->parray = psa;	

			retVal = S_OK;
		}
	}
	
	return retVal;

}

STDMETHODIMP CVSPTA::put_ApplicationReadOKDomains(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the domains that are allowed to read the profile.*/
		retVal = _gpVirtualSmartCard->put_VSM_ApplicationReadOKDomains(&newVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}

	return retVal;

}

STDMETHODIMP CVSPTA::get_ApplicationWriteOKDomains(VARIANT *o_pvarApplicationWriteOKDomains)
{
	HRESULT			retVal				= S_OK;
	_bstr_t*		pbstrApplicationWriteOKDomains;
	DWORD			nNumOfApplicationWriteOKDomains = 0;
	SAFEARRAY*		psa;

	/*Input validation*/
	if(!o_pvarApplicationWriteOKDomains)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the list of read ok domains from the smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_ApplicationWriteOKDomains(&pbstrApplicationWriteOKDomains, &nNumOfApplicationWriteOKDomains);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}
		else
		{

			long ix[1];

			SAFEARRAYBOUND rgsabound[1];
			rgsabound[0].lLbound = 0;
			rgsabound[0].cElements = nNumOfApplicationWriteOKDomains;
			psa = SafeArrayCreate(VT_BSTR, 1, rgsabound);

			for (unsigned int i = 0; i < nNumOfApplicationWriteOKDomains; i++) {
			
				VARIANT var;
				ix[0] = i;

				var.vt = VT_BSTR;
				var.bstrVal = (pbstrApplicationWriteOKDomains[i]).copy();
				SafeArrayPutElement(psa, ix, &var);
				VariantClear(&var);
			}

			o_pvarApplicationWriteOKDomains->vt = VT_ARRAY|VT_VARIANT;
			o_pvarApplicationWriteOKDomains->parray = psa;	

			retVal = S_OK;
		}
	}
	
	return retVal;

}

STDMETHODIMP CVSPTA::put_ApplicationWriteOKDomains(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the domains that are allowed to read the profile.*/
		retVal = _gpVirtualSmartCard->put_VSM_ApplicationWriteOKDomains(&newVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}

	return retVal;

}

STDMETHODIMP CVSPTA::get_ProfMgmt_PasswdQuality(VARIANT* pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality;
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_PasswdQuality(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	/*retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
	retVal = S_OK;*/ //Not doing this because in change password the profile may be open.

	/*Store the password quality*/
	m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = newVal.iVal;
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_PasswdLength(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_PasswdLength(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	/*retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
	retVal = S_OK;*/ //Not doing this because in change password this property is specified.

	/*Store password Length.*/
	m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_PasswdTimeOut(VARIANT * pVal)
{
	HRESULT retVal = S_OK;
	short nPasswdTimeOut;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the password TimeOut from the virtual smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_PasswdTimeOut(&nPasswdTimeOut);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}
	else
	{
		//A profile is not open. Return the info from our storage
		nPasswdTimeOut = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordTimeOut;
		retVal = S_OK;
	}


	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = nPasswdTimeOut;
	
	return retVal;

}

STDMETHODIMP CVSPTA::put_ProfMgmt_PasswdTimeOut(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the password TimeOut.*/
		retVal = _gpVirtualSmartCard->put_VSM_PasswdTimeOut(newVal.iVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);

		}

	}
	else
	{
		// Modified the code to allow zero timeout value - Sasi 06/03/03
		if(newVal.iVal >= 0)
		{
			//A profile is not open. Store the password timeout val in the open prof params
			m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordTimeOut = newVal.iVal ;
			retVal = S_OK;
		}
		else
		{
			retVal = E_NOTIMPL; //Do not implement 0 timeout for the web pages.
		}
	}


	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_PasswdLockOutTries(VARIANT * pVal)
{
	HRESULT retVal = S_OK;
	short nPasswdLockOutTries;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the password TimeOut from the virtual smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_PasswdLockOutTries(&nPasswdLockOutTries);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}
	else
	{
		//A profile is not open. Return the info from our storage
		nPasswdLockOutTries = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLockOutTries;
	}

	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = nPasswdLockOutTries;
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_PasswdLockOutTries(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the password TimeOut.*/
		retVal = _gpVirtualSmartCard->put_VSM_PasswdLockOutTries(newVal.iVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);

		}

	}
	else //A profile is not open
	{
		//A profile is not open. Store the password timeout val in the open prof params
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLockOutTries = newVal.iVal ;
		retVal = S_OK;
	}

	return retVal; 
}

STDMETHODIMP CVSPTA::get_ProfMgmt_PasswdUnLockPeriod(VARIANT * pVal)
{
	HRESULT retVal = S_OK;
	short nPasswdUnLockPeriod;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the password unlock period from the virtual smart card*/
		retVal = _gpVirtualSmartCard->get_VSM_PasswdUnLockPeriod(&nPasswdUnLockPeriod);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
		}

	}
	else
	{
		//A profile is not open. Return the info from our storage
		nPasswdUnLockPeriod = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordUnlockPeriod;
	}

	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = nPasswdUnLockPeriod;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_PasswdUnLockPeriod(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Tell the Virtual Smart Card the password unlock period.*/
		retVal = _gpVirtualSmartCard->put_VSM_PasswdUnLockPeriod(newVal.iVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);

		}

	}
	else
	{
		//A profile is not open. Store the password timeout val in the open prof params
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordUnlockPeriod = newVal.iVal ;
		retVal = S_OK;
	}

	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_ProfileName(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Find out if a profile has been opened*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //A profile is open.
	{
		/*Get the profile name form the Virtual Smart Card */
		retVal = _gpVirtualSmartCard->get_VSM_ProfileName(pVal);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);

		}

	}
	else
	{
		/*Get the profile name*/
		pVal->vt = VT_BSTR;
		pVal->bstrVal = m_pAppCtxt->theOpenProfParams.tbstrProfName.copy();
	}

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_ProfileName(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
	retVal = S_OK;

	/*Store profile name.*/
	m_pAppCtxt->theOpenProfParams.tbstrProfName = newVal.bstrVal;


	return retVal;

}

/* NOTE - There is no property for getting the password for
security reasons*/

STDMETHODIMP CVSPTA::put_ProfMgmt_Password(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
	else
		retVal = S_OK;

	/*Store password.*/
	m_pAppCtxt->theOpenProfParams.tbstrPassword = newVal.bstrVal;
	m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = newVal.bstrVal;
	m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_SaveLocal(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get the permanent save option*/
	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->theOpenProfParams.boolSaveLocal;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_SaveLocal(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
	retVal = S_OK;


	/*Store permanent save option*/
	m_pAppCtxt->theOpenProfParams.boolSaveLocal = newVal.boolVal;


	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_RoamProfile(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get the roaming preference*/
	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->theOpenProfParams.boolRoamProfile;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_RoamProfile(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal; 
	}

#if 0	// removed this check bcos if the card was opened then the client info was
		// not getting set, this was bcos if we try to install certificates after opening
		// a profile it was not allowing
	/*Make sure that a profile is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}
#endif

	retVal = S_OK;


	/*Store roaming flag.*/
	m_pAppCtxt->theOpenProfParams.boolRoamProfile = newVal.boolVal;


	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_OpenProfFlags(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theOpenProfParams.nFlag;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_OpenProfFlags(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if (newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
 
	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK) //profile is already open
	{
		retVal = E_CARDALREADYOPEN ;
		_SetErrorInfo(retVal);
		return (retVal);
	}

	retVal = S_OK;


	/*Store open profile flags.*/
	m_pAppCtxt->theOpenProfParams.nFlag = newVal.iVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_ProfMgmt_AddApplicationIfItDoesNotExistFlag(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Set the value to be outputted.
	pVal->vt = VT_BOOL;
	pVal->boolVal = (m_pAppCtxt->theOpenProfParams.nFlag & CREATE_APP_IF_NOT_EXIST)? true:false;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_AddApplicationIfItDoesNotExistFlag(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if (newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a profile is already open.
	  This is the opposite of what we check for OpenProfFlags. */
	retVal = _CheckEnvironment(CHECK_PROF);

	if(retVal != S_OK) //profile is not open
	{
		_SetErrorInfo(retVal);
		return (retVal);
	}

	/*Store open profile flags.*/
	if (newVal.boolVal)
	{
		m_pAppCtxt->theOpenProfParams.nFlag = m_pAppCtxt->theOpenProfParams.nFlag | CREATE_APP_IF_NOT_EXIST;
	}
	else
	{
		m_pAppCtxt->theOpenProfParams.nFlag = m_pAppCtxt->theOpenProfParams.nFlag & (!CREATE_APP_IF_NOT_EXIST);
	}
	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_IsUsernameEditable(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get the roaming preference*/
	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable;

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_IsUsernameEditable(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal; 
	}


	retVal = S_OK;


	/*Store roaming flag.*/
	m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable = newVal.boolVal;


	return retVal;
}

/*******************************************************/
/*******************************************************/
/*
			IVSUIPrefs methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::get_UIPref_Language(VARIANT * pVal)
{
	HRESULT retVal;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
	
	/*Check if we have a valid appcontext and if we are initialized*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Set the returned value
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.wLangID;
	
	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_Language(VARIANT newVal)
{
	HRESULT retVal, retVal2;
	retVal = retVal2 = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*script will specify the language - check if we support the language. If we dont, we set
	the error object. In this case the return value will be that the language is not supported. 
	Then we try to load the fonts for this language. Only if we obtain the font, 
	we change the current language.*/
	
	/*If the new language is 0, then set it to the default language*/
	if(!newVal.iVal)
		newVal.iVal = _GetDefaultLangID();

	/*Set the language id*/
	if(m_pAppCtxt->theUIPrefs.wLangID != newVal.iVal)
	{
		/*Get the fonts for the title, text and button, that support this language*/
		retVal2 = _GetFonts(newVal.iVal, m_pAppCtxt->theUIPrefs.tbstrTitleFont, m_pAppCtxt->theUIPrefs.tbstrTextFont,
								m_pAppCtxt->theUIPrefs.tbstrBtnFont);
		if(retVal2 != S_OK)
		{
			_SetErrorInfo(retVal2);
			return retVal2;
		}

		/*Check if the language is supported. Even if the language is not supported, 
		we still save the lang id, because we can still render the customized strings
		in this language, provided fonts for this language is available on the system. 
		However we will return an error, that we donot support this language*/
		if(!_IsLangSupported(newVal.iVal))
		{
			//We donot support this language
			_SetErrorInfo(E_LANGNOTSUPPORTED);
			retVal =  E_LANGNOTSUPPORTED;

			//Since we do not support this language, we change all the default 
			//strings into the default language
			m_pAppCtxt->theDefUIPrefs.wLangID = _GetDefaultLangID();
			if(!_InitializeDefUiPrefs(m_pAppCtxt->theDefUIPrefs))
			{
				return E_FAIL;
			}

			//However we try to render these default strings in the same font
			//as the custom strings, provided those fonts support the default
			//language
			if(_DoesFontSupportCharset(m_pAppCtxt->theUIPrefs.tbstrTitleFont,
				_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
			{
				m_pAppCtxt->theDefUIPrefs.tbstrTitleFont = m_pAppCtxt->theUIPrefs.tbstrTitleFont;
			}

			if(_DoesFontSupportCharset(m_pAppCtxt->theUIPrefs.tbstrTextFont,
				_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
			{
				m_pAppCtxt->theDefUIPrefs.tbstrTextFont = m_pAppCtxt->theUIPrefs.tbstrTextFont;
			}

			if(_DoesFontSupportCharset(m_pAppCtxt->theUIPrefs.tbstrBtnFont,
				_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
			{
				m_pAppCtxt->theDefUIPrefs.tbstrBtnFont = m_pAppCtxt->theUIPrefs.tbstrBtnFont;
			}


			
		}
		else
		{
			//Since the language is supported, we will render all the default
			//strings in this language - so we will change the default langauge
			m_pAppCtxt->theDefUIPrefs.wLangID = newVal.iVal;
			_InitializeDefUiPrefs(m_pAppCtxt->theDefUIPrefs);
		}

		m_pAppCtxt->theUIPrefs.wLangID = newVal.iVal;		
	}
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_TitleFont(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title font
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrTitleFont.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_TitleFont(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrFontName = "";

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	tbstrFontName = newVal.bstrVal ;

	/*Check if this font is available on the system and it supports the current language*/
	if(!_IsFontAvailable(tbstrFontName))
	{
		_SetErrorInfo(E_FONTNOTAVAILABLE);
		return (E_FONTNOTAVAILABLE);
	}

	if(!_DoesFontSupportCharset(tbstrFontName, _GetCharset(m_pAppCtxt->theUIPrefs.wLangID)))
	{
		_SetErrorInfo(E_FONTDOESNOTSUPPORTLANG);
		return E_FONTDOESNOTSUPPORTLANG;
	}

	//Set the font property
	m_pAppCtxt->theUIPrefs.tbstrTitleFont = tbstrFontName;

	//If this font supports the default language, change the default strings font
	if(_DoesFontSupportCharset(tbstrFontName,_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
	{
		m_pAppCtxt->theDefUIPrefs.tbstrTitleFont = tbstrFontName;
	}
	return retVal;


}

STDMETHODIMP CVSPTA::get_UIPref_TextFont(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text font
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrTextFont.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_TextFont(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrFontName = "";

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	tbstrFontName = newVal.bstrVal ;

	/*Check if this font is available on the system and it supports the current language*/
	if(!_IsFontAvailable(tbstrFontName))
	{
		_SetErrorInfo(E_FONTNOTAVAILABLE);
		return (E_FONTNOTAVAILABLE);
	}

	if(!_DoesFontSupportCharset(tbstrFontName, _GetCharset(m_pAppCtxt->theUIPrefs.wLangID)))
	{
		_SetErrorInfo(E_FONTDOESNOTSUPPORTLANG);
		return E_FONTDOESNOTSUPPORTLANG;
	}

	//Set the font property
	m_pAppCtxt->theUIPrefs.tbstrTextFont = tbstrFontName;

	//If this font supports the default language, change the default strings font
	if(_DoesFontSupportCharset(tbstrFontName,_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
	{
		m_pAppCtxt->theDefUIPrefs.tbstrTextFont = tbstrFontName;
	}

	return retVal;


}


STDMETHODIMP CVSPTA::get_UIPref_BtnFont(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the button font
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrBtnFont.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_BtnFont(VARIANT newVal)
{
		HRESULT retVal = S_OK;
	_bstr_t tbstrFontName = "";

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	tbstrFontName = newVal.bstrVal ;

	/*Check if this font is available on the system and it supports the current language*/
	if(!_IsFontAvailable(tbstrFontName))
	{
		_SetErrorInfo(E_FONTNOTAVAILABLE);
		return (E_FONTNOTAVAILABLE);
	}

	if(!_DoesFontSupportCharset(tbstrFontName, _GetCharset(m_pAppCtxt->theUIPrefs.wLangID)))
	{
		_SetErrorInfo(E_FONTDOESNOTSUPPORTLANG);
		return E_FONTDOESNOTSUPPORTLANG;
	}

	//Set the font property
	m_pAppCtxt->theUIPrefs.tbstrBtnFont = tbstrFontName;

	//If this font supports the default language, change the default strings font
	if(_DoesFontSupportCharset(tbstrFontName,_GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID)))
	{
		m_pAppCtxt->theDefUIPrefs.tbstrBtnFont = tbstrFontName;
	}

	return retVal;


}


STDMETHODIMP CVSPTA::get_UIPref_UILogoUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the logo url of the ui
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrUILogoUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_UILogoUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the UI Logo Url property
	m_pAppCtxt->theUIPrefs.tbstrUILogoUrl = newVal.bstrVal;

	return retVal;


}


STDMETHODIMP CVSPTA::get_UIPref_NewPasswd_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the new password title
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_NewPasswd_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the New password title property
	m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_NewPasswd_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text to be displayed in the new password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Text.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_NewPasswd_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the New password text property
	m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_NewPasswd_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText;

	return retVal;
	
}

STDMETHODIMP CVSPTA::put_UIPref_NewPasswd_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_NewPasswd_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nNewPasswd_CancelBtnText;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_NewPasswd_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nNewPasswd_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_NewPasswd_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the new password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrNewPasswd_HelpUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_NewPasswd_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the New password dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrNewPasswd_HelpUrl = newVal.bstrVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_LgnDlg_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the logon dialog title
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrLgnDlg_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_LgnDlg_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the login dialog title property
	m_pAppCtxt->theUIPrefs.tbstrLgnDlg_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_OpenProf_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrOpenProf_Title.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_OpenProf_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile title property
	m_pAppCtxt->theUIPrefs.tbstrOpenProf_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_OpenProf_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrOpenProf_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_OpenProf_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile text property
	m_pAppCtxt->theUIPrefs.tbstrOpenProf_Text = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_OpenProf_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_OpenProf_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_OpenProf_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nOpenProf_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_OpenProf_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nOpenProf_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_OpenProf_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the new password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrOpenProf_HelpUrl.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_OpenProf_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrOpenProf_HelpUrl = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the select id dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrSelID_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_SelID_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the select id title property
	m_pAppCtxt->theUIPrefs.tbstrSelID_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the select id dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrSelID_Text.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_SelID_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the select id text property
	m_pAppCtxt->theUIPrefs.tbstrSelID_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nSelID_OKBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_SelID_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nSelID_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_SelID_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_ShowDefChkBox(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	
	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the show def check box flag
	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->theUIPrefs.boolSelID_ShowDefChkBox;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_SelID_ShowDefChkBox(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	if(newVal.vt != VT_BOOL)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	
	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the show check box flag
	m_pAppCtxt->theUIPrefs.boolSelID_ShowDefChkBox = newVal.boolVal ;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_ChkBoxText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the check box text of the select id dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrSelID_ChkBoxText.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_SelID_ChkBoxText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the check box text
	m_pAppCtxt->theUIPrefs.tbstrSelID_ChkBoxText = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_SelID_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the select id dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrSelID_HelpUrl.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_SelID_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the select id dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrSelID_HelpUrl = newVal.bstrVal;

	return retVal;

}


STDMETHODIMP CVSPTA::get_UIPref_SgnDlg_Title(VARIANT * pVal)
{
HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the sign dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrSgnDlg_Title.copy();

	return retVal;}

STDMETHODIMP CVSPTA::put_UIPref_SgnDlg_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the sign dialog title property
	m_pAppCtxt->theUIPrefs.tbstrSgnDlg_Title = newVal.bstrVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_RvwMsg_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the review message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_RvwMsg_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the review message title property
	m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_RvwMsg_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the review message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_RvwMsg_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the revw message text property
	m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_RvwMsg_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_RvwMsg_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText = newVal.iVal;

	return retVal;
}



STDMETHODIMP CVSPTA::get_UIPref_RvwMsg_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nRvwMsg_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_RvwMsg_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nRvwMsg_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_RvwMsg_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the revw message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrRvwMsg_HelpUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_RvwMsg_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the select id dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrRvwMsg_HelpUrl = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_IntroDlg_Title(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the review message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_IntroDlg_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the review message title property
	m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Title = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_IntroDlg_Text(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the review message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_IntroDlg_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the revw message text property
	m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Text = newVal.bstrVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_IntroDlg_HelpUrl(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the revw message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrIntroDlg_HelpUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_IntroDlg_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the select id dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrIntroDlg_HelpUrl = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreateNewProf_Title(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the review message dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrCreateDlg_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreateNewProf_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the review message title property
	m_pAppCtxt->theUIPrefs.tbstrCreateDlg_Title = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_CreatePasswd_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Title.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_CreatePasswd_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile title property
	m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_EnterPasswd_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Title.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_EnterPasswd_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile title property
	m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ChangePasswd_Title(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Title.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_ChangePasswd_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile title property
	m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreatePasswd_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_CreatePasswd_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile text property
	m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Text = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_CreatePasswd_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nCreatePasswd_OKBtnText;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_CreatePasswd_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nCreatePasswd_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreatePasswd_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nCreatePasswd_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreatePasswd_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the cancel button text
	m_pAppCtxt->theUIPrefs.nCreatePasswd_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_EnterPasswd_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_EnterPasswd_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile text property
	m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Text = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_EnterPasswd_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nEnterPasswd_OKBtnText;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_EnterPasswd_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nEnterPasswd_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_EnterPasswd_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nEnterPasswd_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_EnterPasswd_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the cancel button text
	m_pAppCtxt->theUIPrefs.nEnterPasswd_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ChangePasswd_Text(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the open profile dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Text.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_ChangePasswd_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile text property
	m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Text = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_UIPref_ChangePasswd_OKBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText;

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_ChangePasswd_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ChangePasswd_CancelBtnText(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nChangePasswd_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_ChangePasswd_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nChangePasswd_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ChangePasswd_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the new password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrChangePasswd_HelpUrl.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_ChangePasswd_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrChangePasswd_HelpUrl = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_Timeout_HelpUrl(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the help url of the new password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrTimeOut_HelpUrl.copy();

	return retVal;

}

STDMETHODIMP CVSPTA::put_UIPref_Timeout_HelpUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the open profile dialog help url property
	m_pAppCtxt->theUIPrefs.tbstrTimeOut_HelpUrl = newVal.bstrVal;

	return retVal;
}


STDMETHODIMP CVSPTA::put_UIPref_EnableTopMostWindow(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	if(newVal.vt != VT_BOOL)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	// Set the show top most flag
	m_pAppCtxt->theUIPrefs.boolShowTopMost = newVal.boolVal ;

	return retVal;
}


/*******************************************************/
/*******************************************************/
/*
			IVSCertPrefs methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::get_CertPref_CertSerNum (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the cert serial number*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theCertIdentifier.tbstrCertSerNum;

	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertSerNum(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the serial number search criteria
	m_pAppCtxt->theCertIdentifier.tbstrCertSerNum = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_CertPref_CertIssDN (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the cert serial number*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theCertIdentifier.tbstrCertIssDN;

	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertIssDN(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the serial number search criteria
	m_pAppCtxt->theCertIdentifier.tbstrCertIssDN = newVal.bstrVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_CertPref_CertFrndlyName (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_FRNDLYNAME;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, GETCERTPREF_BASE);
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_tbstrCertPref.copy();
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertFrndlyName(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_FRNDLYNAME;
	m_pAppCtxt->theCertPrefParams.tbstrPrefVal = newVal.bstrVal;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, SETCERTPREF_BASE);
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_CertPref_CertLogoUrl (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_LOGOURL;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, GETCERTPREF_BASE);
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_tbstrCertPref.copy();
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertLogoUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_LOGOURL;
	m_pAppCtxt->theCertPrefParams.tbstrPrefVal = newVal.bstrVal;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, SETCERTPREF_BASE);
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_CertPref_CertDispString (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
		
	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_DISPSTRING;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE,GETCERTPREF_BASE);
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_tbstrCertPref.copy();
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertDispString(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_DISPSTRING;
	m_pAppCtxt->theCertPrefParams.tbstrPrefVal = newVal.bstrVal;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, SETCERTPREF_BASE);
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_CertPref_CertTextureUrl (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
		

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_TEXTUREURL;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, GETCERTPREF_BASE);
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_tbstrCertPref.copy();
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_CertTextureUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_TEXTUREURL;
	m_pAppCtxt->theCertPrefParams.tbstrPrefVal = newVal.bstrVal;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, SETCERTPREF_BASE);
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_CertPref_MarkAsRenewed (VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
		
	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_RENEWED;

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, GETCERTPREF_BASE);
	
	pVal->vt = VT_BOOL;
	pVal->boolVal = FALSE;
	if(m_tbstrCertPref.length())
	{
		if(m_tbstrCertPref != _bstr_t("0"))
			pVal->boolVal = TRUE;
	}
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_CertPref_MarkAsRenewed(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the parameters*/
	m_pAppCtxt->theCertPrefParams.tbstrPrefName = CERTPREF_RENEWED;
	if(newVal.boolVal)
		m_pAppCtxt->theCertPrefParams.tbstrPrefVal = "1";
	else
		m_pAppCtxt->theCertPrefParams.tbstrPrefVal = "0";

	/*Get the cert friendly name*/
	retVal = _DoOperation(NO_WIZARD_BASE, SETCERTPREF_BASE);
	
	
	return retVal;
}

STDMETHODIMP CVSPTA::CertPref_SetPreference(VARIANT * in_pvarPrefName, VARIANT * in_pvarPrefValue)
{
	return E_NOTIMPL;
}

STDMETHODIMP CVSPTA::CertPref_GetPreference(VARIANT * in_pvarPrefName, VARIANT * out_pvarPrefValue)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!in_pvarPrefName || !out_pvarPrefValue)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}
		
	/*Check if we are initialized and we have an app context and a profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	return E_NOTIMPL;

}

/*******************************************************/
/*******************************************************/
/*
			IVSSrchCrit methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::get_SrchCrit_IssuerDN(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the issuer dn search criteria
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theSrchCrit.tbstrIssuerDN.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_IssuerDN(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the issuer dn search criteria
	m_pAppCtxt->theSrchCrit.tbstrIssuerDN = newVal.bstrVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_SrchCrit_SubjectDN(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the subject dn search criteria
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theSrchCrit.tbstrSubjectDN.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_SubjectDN(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the subject dn search criteria
	m_pAppCtxt->theSrchCrit.tbstrSubjectDN = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_Email(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the email search criteria
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theSrchCrit.tbstrEmail.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_Email(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the email search criteria
	m_pAppCtxt->theSrchCrit.tbstrEmail = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_SerNum(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the serial number search criteria
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theSrchCrit.tbstrSerNum.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_SerNum(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the serial number search criteria
	m_pAppCtxt->theSrchCrit.tbstrSerNum = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_ExpDate(DATE * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the exp. date search criteria
	*pVal = m_pAppCtxt->theSrchCrit.dateExpDate;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_ExpDate(DATE newVal)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the expiration date search criteria
	m_pAppCtxt->theSrchCrit.dateExpDate = newVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_EffDate(DATE * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the eff date search criteria
	*pVal = m_pAppCtxt->theSrchCrit.dateEffDate;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_EffDate(DATE newVal)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the effective date search criteria
	m_pAppCtxt->theSrchCrit.dateEffDate = newVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_DateEquality(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the date equality search criteria
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theSrchCrit.nDateEquality;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_DateEquality(VARIANT newVal)
{
	HRESULT retVal = S_OK;


	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	//Set the  date equality search criteria
	m_pAppCtxt->theSrchCrit.nDateEquality = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_Renewed(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the renewed search criteria
	pVal->vt = VT_BOOL;
	pVal->boolVal  = m_pAppCtxt->theSrchCrit.boolRenewed;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_Renewed(VARIANT newVal)
{
	HRESULT retVal = S_OK;


	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}


	//Set the renewed search criteria
	m_pAppCtxt->theSrchCrit.boolRenewed = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_KeyUsage(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the key usage search criteria
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theSrchCrit.nKeyUsage;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_KeyUsage(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	//Set the key usage search criteria
	m_pAppCtxt->theSrchCrit.nKeyUsage = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_KeySize(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the key size search criteria
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theSrchCrit.nKeySize;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_KeySize(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Input Validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	//Set the key size search criteria
	m_pAppCtxt->theSrchCrit.nKeySize = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SrchCrit_ExtOID(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the ext oid search criteria
	_variant_t tvarRetVar;

	tvarRetVar = m_pAppCtxt->theSrchCrit.tvarExtOID;
	*pVal = tvarRetVar.Detach();
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_SrchCrit_ExtOID(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the search criteria
	m_pAppCtxt->theSrchCrit.tvarExtOID = newVal;

	return retVal;

}

STDMETHODIMP CVSPTA::get_SrchCrit_ExtVal(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the ext val search criteria
	_variant_t tvarRetVar;

	tvarRetVar = m_pAppCtxt->theSrchCrit.tvarExtVal;
	*pVal = tvarRetVar.Detach();
	
	return retVal;

}

STDMETHODIMP CVSPTA::put_SrchCrit_ExtVal(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT))
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the search criteria
	m_pAppCtxt->theSrchCrit.tvarExtVal = newVal;

	return retVal;
}



/*******************************************************/
/*******************************************************/
/*
			IVSSelectedDigID methods and properties
*/
/*******************************************************/
/*******************************************************/
STDMETHODIMP CVSPTA::get_SelectedDigID_IssuerDN(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the issuer dn*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pDecCertInfo->tbstrIssuerDN.copy();

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_SubjectDN(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the subject dn*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pDecCertInfo->tbstrSubjectDN.copy();

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_SerNum(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the serial number*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pDecCertInfo->tbstrSerNum.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::get_SelectedDigID_FrndlyName(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the friendly name*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pAuxCertInfo->tbstrFrndlyName.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::get_SelectedDigID_LogoUrl(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the logo url*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pAuxCertInfo->tbstrLogoUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::get_SelectedDigID_TextureUrl(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the texture url*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pSelectedId->pAuxCertInfo->tbstrTextureUrl.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::get_SelectedDigID_ExpDate(DATE *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the expiration date*/
	*pVal = m_pSelectedId->pDecCertInfo->dateExpDate;

	return retVal;

}


STDMETHODIMP CVSPTA::get_SelectedDigID_EffDate(DATE *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the effective date*/
	*pVal = m_pSelectedId->pDecCertInfo->dateEffDate;

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_KeyUsage(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the key usage*/
	pVal->vt = VT_I2;
	pVal->iVal = m_pSelectedId->pDecCertInfo->nKeyUsage;

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_KeySize(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the key size*/
	pVal->vt = VT_I2;
	pVal->iVal = m_pSelectedId->pDecCertInfo->nKeySize;

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_Renewed(VARIANT *pVal)
{
	HRESULT retVal = S_OK;
	
	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Return the renewed flag*/
	pVal->vt = VT_BOOL;
	pVal->boolVal  = m_pSelectedId->pAuxCertInfo->boolRenewed;

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_PubKeyMD5(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Tell the engine to create the md5 hash of the cert*/
	unsigned char byteHashVal[HASH_MD5_LENGTH];
	retVal = m_pPtaEngine->CreateCertHash(m_pSelectedId->pCertContext, VS_MD5, byteHashVal);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Convert the cert into ascii hex*/
	_bstr_t tbstrAscHexMD5 = "";
	if(!BytesToAscHex(byteHashVal, HASH_MD5_LENGTH, tbstrAscHexMD5))
	{
		return(E_FAIL);
	}

//	VSPTA_CLEAN_TBSTR(tbstrAscHexMD5)

	return retVal;
}


STDMETHODIMP CVSPTA::get_SelectedDigID_PubKeySHA1(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and if an id is selected*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF|CHECK_SELID);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Tell the engine to create the md5 hash of the cert*/
	unsigned char byteHashVal[HASH_SHA1_LENGTH];
	retVal = m_pPtaEngine->CreateCertHash(m_pSelectedId->pCertContext, VS_SHA_1, byteHashVal);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Convert the cert into ascii hex*/
	_bstr_t tbstrAscHexSHA1 = "";
	if(!BytesToAscHex(byteHashVal, HASH_SHA1_LENGTH, tbstrAscHexSHA1))
	{
		return(E_FAIL);
	}

//	VSPTA_CLEAN_TBSTR(tbstrAscHexSHA1)

	return retVal;
}

/*******************************************************/
/*******************************************************/
/*
			IVSRoamingPrefs methods and properties
*/
/*******************************************************/
/*******************************************************/
STDMETHODIMP CVSPTA::get_RoamPrefs_NumOfSrvrs(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theRoamingParams.nNumOfRoamingSrvrs;


	return retVal;
}

STDMETHODIMP CVSPTA::put_RoamPrefs_NumOfSrvrs(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)	
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a card is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		retVal = E_CARDALREADYOPEN;
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Remember this property*/
	m_pAppCtxt->theRoamingParams.nNumOfRoamingSrvrs = newVal.iVal ;

	return S_OK;
}

STDMETHODIMP CVSPTA::get_RoamPrefs_RoamingSrvrs(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVSPTA::put_RoamPrefs_RoamingSrvrs(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != (VT_ARRAY|VT_VARIANT|VT_BYREF))	
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a card is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		retVal = E_CARDALREADYOPEN;
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Extract the bstrs from the variant*/
	//First obtain and make sure that the array has only one dimension
	int nDims = SafeArrayGetDim(*(newVal.pparray));
	if(nDims != 1)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	//Now obtain the number of elements in each dimension and make sure that the second dimension
	//has a bound of 2
	LONG nNumOfElemsInDim1;

	retVal = SafeArrayGetUBound(*(newVal.pparray), 1, &nNumOfElemsInDim1);
	if(retVal != S_OK)
	{
		_SetErrorInfo(E_SAFEARRAYGETUBOUNDFAILED);
		return E_SAFEARRAYGETUBOUNDFAILED;
	}

	if(nNumOfElemsInDim1 != m_pAppCtxt->theRoamingParams.nNumOfRoamingSrvrs)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}
	
	//Now extract the elements
	m_pAppCtxt->theRoamingParams.ptbstrRoamingSrvrs = (_bstr_t*)new _bstr_t[nNumOfElemsInDim1];
	

	retVal = _ExtractBstrsFromArray(*(newVal.pparray), 1, nNumOfElemsInDim1, m_pAppCtxt->theRoamingParams.ptbstrRoamingSrvrs);
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_RoamPrefs_StorageSrvr(VARIANT *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVSPTA::put_RoamPrefs_StorageSrvr(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)	
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS); 
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Make sure that a card is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		retVal = E_CARDALREADYOPEN;
		_SetErrorInfo(retVal);
		return retVal;
	}
	retVal = S_OK;

	m_pAppCtxt->theRoamingParams.tbstrStorageSrvr = newVal.bstrVal;

	return retVal;
}

/*******************************************************/
/*******************************************************/
/*
			IVSPTADllApi methods and properties
*/
/*******************************************************/
/*******************************************************/
STDMETHODIMP CVSPTA::get_PTADllApi_HostFQDN(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->tbstrHostName.copy();
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_HostFQDN(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	if(!m_bInitialized)
	{
		retVal = E_NOTINITIALIZED;
		_SetErrorInfo(retVal);
		return retVal;
	}


	_bstr_t tbstrHostName = newVal.bstrVal;

	/*If smart card is open, tell the smartcard that the application has changed*/
	if(_gpVirtualSmartCard && tbstrHostName.length())
	{
		retVal = _ChangeSmartCardHost((BSTR)tbstrHostName, m_pAppCtxt->tbstrAppCtxtName);
		if(retVal != S_OK)
		{
			//_SetErrorInfo();
			return retVal;
		}
	}
	
	m_pAppCtxt->tbstrHostName = newVal.bstrVal;

	//Convert to lower
	_bstr_t tbstrTemp = m_pAppCtxt->tbstrHostName.copy();
	CharLowerBuff((LPTSTR)tbstrTemp,lstrlen((LPCTSTR)tbstrTemp));
	m_pAppCtxt->tbstrHostName = (LPTSTR)tbstrTemp;


	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_Protocol(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->tbstrProtocolName.copy();
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_Protocol(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->tbstrProtocolName = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_SelectedIDCertContext(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	retVal = m_pPtaEngine->GetSelIDCertContext(m_pSelectedId->pCertContext, pVal);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_DoAttachedSig(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolIsAttached;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_DoAttachedSig(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolIsAttached = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_ShowSignUI(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolShowUI;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_ShowSignUI(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolShowUI = newVal.boolVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_PTADllApi_OleClientSite(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}


	if(m_spOuterClientSite)
	{
		pVal->vt = VT_UNKNOWN;
		retVal = m_spOuterClientSite->QueryInterface(IID_IUnknown, (void**)&(pVal->punkVal));
	}
	else
		retVal = E_FAIL;

	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_OleClientSite(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_UNKNOWN || newVal.punkVal == NULL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	newVal.punkVal->QueryInterface(IID_IOleClientSite, (void**)&m_spOuterClientSite);
	return retVal;
}

//
//	Anand	Dec 13, 2000		Start
//
STDMETHODIMP CVSPTA::get_PTADllApi_HashData(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolHashData ;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_HashData(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolHashData = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_P7Output(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolP7Output;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_P7Output(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolP7Output = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_SignNotificationUI(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolSignNotificationUI;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_SignNotificationUI(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolSignNotificationUI = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_DecryptUI(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_I4;
	pVal->lVal = m_pAppCtxt->dwDecryptUI;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_DecryptUI(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_I4)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->dwDecryptUI = newVal.lVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_PTADllApi_ShowSelIDUI(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->boolShowSelIDUI;
	return retVal;
}

STDMETHODIMP CVSPTA::put_PTADllApi_ShowSelIDUI(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->boolShowSelIDUI = newVal.boolVal;

	return retVal;
}

STDMETHODIMP CVSPTA::DecryptSessionKey(VARIANT i_varEncryptedSessionKey, VARIANT* o_pvarDecryptedSessionKey)
{
	HRESULT retVal = S_OK;

	BYTE*	pbyteEncryptedData = NULL;
	DWORD	dwEncryptedDataLen;
	BYTE*	pbyteDecryptedData = NULL;
	DWORD	dwDecryptedDataLen;

	int		nMsgBox;

	do
	{
		/*Check if we are initialized and we have an app context*/
		retVal = _CheckEnvironment(CHECK_INIT);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			return retVal;
		}

		if(NULL == o_pvarDecryptedSessionKey)
		{	
			retVal = E_EMPTYARGS;
			_SetErrorInfo(E_EMPTYARGS);
			return retVal;
		}	

		/*Check the types of the input params*/
		if(i_varEncryptedSessionKey.vt != VT_ARRAY)
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			return retVal;
		}

		//Extract the information from the vt array
		retVal = SafeArrayAccessData(i_varEncryptedSessionKey.parray, (void HUGEP**)&pbyteEncryptedData);
		if(retVal == S_OK)
		{
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)i_varEncryptedSessionKey.parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)i_varEncryptedSessionKey.parray, 1, &uBound);
			dwEncryptedDataLen = uBound - lBound + 1;

			(m_pAppCtxt->theDecryptMsgParams).nMsgToDecryptSize = dwEncryptedDataLen;
			(m_pAppCtxt->theDecryptMsgParams).pbyteMsgToDecrypt = pbyteEncryptedData;
		}
		else
		{
			break;
		}

			//	if the UI mode is set to notification then pop a message box
		if (DECRYPT_NOTIFICATION == m_pAppCtxt -> dwDecryptUI)
		{
			nMsgBox = ::MessageBox(NULL, (m_pAppCtxt -> theUIPrefs).tbstrDecryptNotificationUI, "VeriSign Personal Trust Agent", MB_OK);
			if ( IDCANCEL == nMsgBox )
			{
					//	the user canceled the operation so return error
				retVal = E_USERCANCELLED;
				break;
			}
		}

				//	decrypt the session key
		retVal =	m_pPtaEngine -> DecryptData
					(
						_gpVirtualSmartCard,			//	the global smart card pointer
						(m_pAppCtxt->theDecryptMsgParams).pbyteMsgToDecrypt,
						(m_pAppCtxt->theDecryptMsgParams).nMsgToDecryptSize,
						m_pSelectedId,					// the selected ID
						&pbyteDecryptedData,
						&dwDecryptedDataLen
					);
		if (S_OK != retVal)
		{
			break;
		}

		o_pvarDecryptedSessionKey->vt =	VT_ARRAY;
		o_pvarDecryptedSessionKey->parray =	SafeArrayCreateVector(VT_UI1, 0, dwDecryptedDataLen);
		if ( NULL == o_pvarDecryptedSessionKey->parray )
		{
			retVal = E_UNEXPECTED;
			break;
		}

		memcpy((BYTE*)o_pvarDecryptedSessionKey->parray->pvData, pbyteDecryptedData, dwDecryptedDataLen);

	}	while (0);

	if (NULL != pbyteDecryptedData)
	{
		delete [] pbyteDecryptedData;
	}

	return retVal;
}

STDMETHODIMP CVSPTA::SetInformationBlob(VARIANT i_varName, VARIANT i_varValue)
{
	HRESULT				retVal				=	E_FAIL;

	_bstr_t				tbstrName			=	"";
	
	BYTE*				pbyteValue			=	NULL;
	DWORD				dwValueLen			=	0;

	do
	{
		/*Input validation*/
		if(i_varName.vt != VT_BSTR || i_varValue.vt != VT_ARRAY)
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			break;
		}

		tbstrName =	i_varName.bstrVal;

		/*Check if we are initialized and we have an app context and a profile is opened*/
		/*Check if a profile is opened*/
		retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			break;
		}

					//	this function will delete the information blob
					//	if it exists and will return error if it does
					//	exists.
					//
					//	call this function and ignore the error.
					//	in short delete the information blob if it exists
		retVal =	_gpVirtualSmartCard -> VSM_DeleteInformationBlob
					(
						tbstrName
					);

		//Extract the information from the vt array
		retVal = SafeArrayAccessData(i_varValue.parray, (void HUGEP**)&pbyteValue);
		if(retVal == S_OK)
		{
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)i_varValue.parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)i_varValue.parray, 1, &uBound);
			dwValueLen = uBound - lBound + 1;
		}
		else
		{
			break;
		}

					//	set the informaiton blob
		retVal =	_gpVirtualSmartCard -> VSM_SetInformationBlob
					(
						tbstrName,
						pbyteValue,
						dwValueLen
					);
		if ( S_OK != retVal )
		{
			break;
		}

		retVal =	S_OK;
	}	while (0);

	if ( NULL != pbyteValue )
	{
		delete [] pbyteValue;
	}

	return	retVal;
}

STDMETHODIMP CVSPTA::GetInformationBlob(VARIANT i_varName, VARIANT *o_pvarValue)
{
	HRESULT				retVal				=	E_FAIL;

	BYTE*				pbyteData			=	NULL;
	DWORD				dwDataLen			=	0;

	_bstr_t				tbstrName			=	"";
	
	do
	{
		/*Input validation*/
		if( NULL == o_pvarValue )
		{
			retVal = E_EMPTYARGS;
			_SetErrorInfo(E_EMPTYARGS);
			break;
		}

		if(i_varName.vt != VT_BSTR)
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			break;
		}

		tbstrName = i_varName.bstrVal;

		/*Check if we are initialized and we have an app context and a profile is opened*/
		/*Check if a profile is opened*/
		retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			break;
		}

			//	allocate 1000 bytes of memory assuming that the length of the info blob value will be
			//	less than 1000
			//	if this assumption is wrong then we will reallocate.
		dwDataLen =	1000;
		pbyteData = (BYTE*) ::malloc (dwDataLen);
		if ( NULL == pbyteData )
		{
			retVal = E_OUTOFMEMORY;
			break;
		}
	
					//	get the information blob
		retVal =	_gpVirtualSmartCard -> VSM_GetInformationBlob
					(
						tbstrName,
						pbyteData,
						&dwDataLen
					);
		if(retVal != S_OK)
		{
			if ( ERROR_MORE_DATA == retVal )
			{
					//	if the allocated buffer is not enough then delete it and
					//	allocate with the required size
				delete [] pbyteData;
				pbyteData = (BYTE*) ::malloc (dwDataLen);
				if ( NULL == pbyteData )
				{
					retVal =	E_OUTOFMEMORY;
					break;
				}

							//	get the information blob
				retVal =	_gpVirtualSmartCard -> VSM_GetInformationBlob
							(
								tbstrName,
								pbyteData,
								&dwDataLen
							);
				if(retVal != S_OK)
				{
					_SetErrorInfo(retVal);
					break;
				}
			}
			else
			{
				_SetErrorInfo(retVal);
				break;
			}
		}

				//	copy the information blob data in the out variant
		o_pvarValue -> vt =	VT_ARRAY;
		o_pvarValue -> parray =	SafeArrayCreateVector(VT_UI1, 0, dwDataLen);
		if ( NULL == o_pvarValue -> parray )
		{
			retVal = E_UNEXPECTED;
			break;
		}

		memcpy((BYTE*)o_pvarValue -> parray -> pvData, pbyteData, dwDataLen);

		retVal =	S_OK;
	} while (0);

	if ( NULL != pbyteData )
	{
		delete [] pbyteData;
	}

	return	retVal;
}


STDMETHODIMP CVSPTA::DeleteInformationBlob(VARIANT i_varName)
{
	HRESULT				retVal				=	E_FAIL;

	_bstr_t				tbstrName			=	"";

	do
	{
		/*Input validation*/
		if(i_varName.vt != VT_BSTR)
		{
			retVal = E_INVALIDARGS;
			_SetErrorInfo(E_INVALIDARGS);
			break;
		}

		tbstrName =	i_varName.bstrVal;

		/*Check if we are initialized and we have an app context and a profile is opened*/
		/*Check if a profile is opened*/
		retVal = _CheckEnvironment(CHECK_INIT|CHECK_PROF);
		if(retVal != S_OK)
		{
			_SetErrorInfo(retVal);
			break;
		}

					//	this function will delete the information blob
		retVal =	_gpVirtualSmartCard -> VSM_DeleteInformationBlob
					(
						tbstrName
					);
		if ( S_OK != retVal )
		{
			break;
		}

		retVal =	S_OK;
	}	while (0);

	return	retVal;
}

//
//	Anand	Dec 13, 2000		End
//

STDMETHODIMP CVSPTA::put_AffLogoUrl(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Check the sanity of the affiliate logo url
	_bstr_t tbstrAffLogoUrl = newVal.bstrVal;
	retVal = _CheckAffLogoUrlSanity(tbstrAffLogoUrl);
	if(retVal != S_OK)
		return retVal;

	//Set the affiliate Logo Url property
	m_pAppCtxt->theUIPrefs.tbstrAffLogoUrl = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_AffLogoUrl(VARIANT* pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the affiliate logo url
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrAffLogoUrl.copy();

	return retVal;
}

/*******************************************************/
/*******************************************************/
/*
			IVSP12Import methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::P12Import_ImportP12(VARIANT *in_pvarParamType, VARIANT* in_pvarParamVal, VARIANT* o_pvarImportedIDSerNum, VARIANT* o_pvarImportedIDIssDN)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	//For now this feature will be supported only in non capi mode
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarParamType)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	if(!in_pvarParamVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check the types of the input params*/
	if(in_pvarParamType->vt != VT_I2 || in_pvarParamVal->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Setup the install cert param*/
	m_pAppCtxt->theImportP12Params.nKeyFileOrBlob= in_pvarParamType->iVal;
	m_pAppCtxt->theImportP12Params.tbstrKeyFileOrBlob= in_pvarParamVal->bstrVal;
	

	/*Do the operation*/
	if(retVal == S_OK)
	{
		retVal = _DoOperation(IMPORTP12_WIZARD_BASE, IMPORTP12_BASE);
		
	}
	else if(retVal = E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
		return retVal;
	}
	else
	{
		//Set the serial number and issuer dn of the imported cert
		o_pvarImportedIDSerNum->vt = VT_BSTR;
		o_pvarImportedIDSerNum->bstrVal = m_pAppCtxt->theImportP12Params.tbstrSerNum.copy();

		o_pvarImportedIDIssDN->vt = VT_BSTR;
		o_pvarImportedIDIssDN->bstrVal = m_pAppCtxt->theImportP12Params.tbstrIssDN.copy();
	}
	
	return retVal;
}


/*******************************************************/
/*******************************************************/
/*
			IVSP12Export methods and properties
*/
/*******************************************************/
/*******************************************************/

STDMETHODIMP CVSPTA::P12Export_ExportP12(VARIANT *in_pvarOutputType, VARIANT* in_pvarFlags, VARIANT* io_pvarP12OrFileName)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	//For now this feature will be supported only in non capi mode
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!in_pvarOutputType || !io_pvarP12OrFileName)
	{	
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}	

	
	/*Check the types of the input params*/
	if(in_pvarOutputType->vt != VT_I2 || io_pvarP12OrFileName->vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Setup the export p12 param*/
	m_pAppCtxt->theExportP12Params.nKeyFileOrBlob= in_pvarOutputType->iVal;
	m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob= io_pvarP12OrFileName->bstrVal;
	if(m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob.length() != 0)
		m_pAppCtxt->theExportP12Params.boolShowFileName = FALSE;
	else
		m_pAppCtxt->theExportP12Params.boolShowFileName = TRUE;

	/*Do the operation*/
	if(retVal == S_OK)
	{
		retVal = _DoOperation(EXPORTP12_WIZARD_BASE, EXPORTP12_BASE);
		
	}
	else if(retVal = E_PROFCREATED)
	{
		//Set the operation performed parameter
		retVal = S_OK;
	}

	if(retVal != S_OK)
	{	
		_SetErrorInfo(retVal);
	}
	
	return retVal;
}


STDMETHODIMP CVSPTA::get_P12Export_PasswdQuality(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theExportP12Params.nPasswordQuality;
	
	return retVal;
}

STDMETHODIMP CVSPTA::put_P12Export_PasswdQuality(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	/*Store the password quality*/
	m_pAppCtxt->theExportP12Params.nPasswordQuality = newVal.iVal;
	
	return retVal;
}

STDMETHODIMP CVSPTA::get_P12Export_PasswdLength(VARIANT * pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Set the value to be outputted.
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theExportP12Params.nPasswordLength;

	return retVal;
}

STDMETHODIMP CVSPTA::put_P12Export_PasswdLength(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	/*Store password Length.*/
	m_pAppCtxt->theExportP12Params.nPasswordLength = newVal.iVal;

	return retVal;
}

/*******************************************************/
/*******************************************************/
/*
			Private members of CVSPTA
*/
/*******************************************************/
/*******************************************************/

//This function gets the required interface
//Input :	IID of the interface required
//Output :	IDispatch pointer of the interface required.

IDispatch* CVSPTA::GetInterface(REFIID refIid)
{
	void* pvoidInterface;
	QueryInterface(refIid,&pvoidInterface);
	return (IDispatch*)pvoidInterface;
}



/*******************************************************/
/************** AppContext Init and Destroy ************/
/*******************************************************/


//This function creates a new app context and initializes it.
//Input		: none
//Output	: pointer to the new app ctxt. NULL if an error occurs.	
//			:	

PAPPCTXT CVSPTA::_CreateAppCtxt()
{
	PAPPCTXT pAppCtxt;

	pAppCtxt = new(APPCTXT);
	if(!pAppCtxt)
		return NULL;

	pAppCtxt->tbstrAppCtxtName = "";
	pAppCtxt->tbstrHostName = "";
	pAppCtxt->tbstrProtocolName = "";
	pAppCtxt->tbstrCSPName = "";
	pAppCtxt->tbstrAuthDll = "";
	pAppCtxt->hModAuthDll = NULL;
	pAppCtxt->tbstrProfileIssFrndlyName = "";
	pAppCtxt->tbstrProfileIssUniqueId = "";
	pAppCtxt->nIsCapi = FALSE;
	pAppCtxt->boolIsAttached = FALSE;
	pAppCtxt->boolShowUI = TRUE;
//	Sameer	Oct 25, 2001		Start
//

	pAppCtxt->boolShowSelIDUI = TRUE;

//
//	Sameer	Oct 25, 2001		End
//

	pAppCtxt->boolCapiCert = TRUE;

	_InitializeCertIdentifier(pAppCtxt->theCertIdentifier);
	_InitializeSrchCrit(pAppCtxt->theSrchCrit);
	_InitializeOpenParams(pAppCtxt->theOpenProfParams);
	_InitializeSelIDParams(pAppCtxt->theSelIdParams);
	_InitializeSignParams(pAppCtxt->theSignMsgParams);
	_InitializeCreateCertReqParams(pAppCtxt->theCreateCertReqParams);
	_InitializeInstallCertParams(pAppCtxt->theInstallCertParams);
	_InitializeSetCertPrefParams(pAppCtxt->theCertPrefParams);
	_InitializeRoamingParams(pAppCtxt->theRoamingParams);
	_InitializeCreatePasswdParams(pAppCtxt->theCreatePasswdParams);
	_InitializeEnterPasswdParams(pAppCtxt->theEnterPasswdParams);
	_InitializeChangePasswdParams(pAppCtxt->theChangePasswdParams);
	_InitializeImportP12Params(pAppCtxt->theImportP12Params);
	_InitializeExportP12Params(pAppCtxt->theExportP12Params);

//
//	Anand	Dec 13, 2000		Start
//
	_InitializeDecryptParams (pAppCtxt -> theDecryptMsgParams);

//	Sasi	May 05, 2003		Start
//
	_InitializeGetSecretQuestionParams(pAppCtxt->theGetSecretQuestionParams);
	_InitializeResetPasswdParams(pAppCtxt->theResetPasswdParams);
	_InitializeCreateSecretParams(pAppCtxt->theCreateSecretParams);

//	Sasi	May 05, 2003		End
//
	pAppCtxt -> boolHashData = TRUE;
	pAppCtxt -> boolP7Output = TRUE;
	pAppCtxt -> boolSignNotificationUI = FALSE;
	pAppCtxt -> dwDecryptUI = DECRYPT_NOTIFICATION;
//
//	Anand	Dec 13, 2000		End
//

	if(!_InitializeUiPrefs(pAppCtxt->theUIPrefs))
	{
		delete(pAppCtxt);
		pAppCtxt = NULL;
	}

	//Initialize the default ui preferences
	pAppCtxt->theDefUIPrefs.wLangID = _GetDefaultLangID();

	if(!_InitializeDefUiPrefs(pAppCtxt->theDefUIPrefs))
	{
		delete(pAppCtxt);
		pAppCtxt = NULL;
	}

	return pAppCtxt;
}

//This function initializes the certificate identifier
//Input		:	The certificate identifier to initialize	
//Output	:	none

void CVSPTA::_InitializeCertIdentifier(CERTIDENTIFIER& theCertIdentifier)
{
	theCertIdentifier.tbstrCertIssDN = "";
	theCertIdentifier.tbstrCertSerNum = "";
	return;
}

//This function initializes the search criteria
//Input		:	The search criteria to initialize	
//Output	:	none

void CVSPTA::_InitializeSrchCrit(SRCHCRIT& theSrchCrit)
{
	theSrchCrit.boolRenewed = FALSE;
	theSrchCrit.tbstrEmail = "";
	theSrchCrit.tvarExtOID.Clear();
	theSrchCrit.tvarExtVal.Clear();
	theSrchCrit.tbstrIssuerDN = "";
	theSrchCrit.tbstrSerNum = "";
	theSrchCrit.tbstrSubjectDN = "";
	theSrchCrit.dateEffDate = 0;
	theSrchCrit.dateExpDate = 0;
	theSrchCrit.nDateEquality = 0;
	theSrchCrit.nKeySize = 0;
	theSrchCrit.nKeyUsage = 0;
	theSrchCrit.boolUseDefault = TRUE;
	return;
}

void CVSPTA::_InitializeOpenParams(OPENPROFPARAMS& i_OpenProfParams)
{
	i_OpenProfParams.boolRoamProfile = FALSE;
	i_OpenProfParams.boolSaveLocal = TRUE;
	i_OpenProfParams.nFlag = OPENPROF_OPEN_ALWAYS;
	i_OpenProfParams.tbstrPassword = "";
	i_OpenProfParams.tbstrConfirmPassword = "";
	i_OpenProfParams.nPasswordUsageFlag = DONOT_USE_PASSWORD;
	i_OpenProfParams.tbstrProfName = "";
	i_OpenProfParams.boolIsUsernameEditable = TRUE;
	i_OpenProfParams.theCreateParams.nPasswordLength = PASSWDLENGTH_DEF_MIN;
	i_OpenProfParams.theCreateParams.nPasswordQuality = PASSWDQUAL_ANYPASSWDOK;
	i_OpenProfParams.theCreateParams.nPasswordTimeOut = PASSWDTIMEOUT_DEF;
	i_OpenProfParams.theCreateParams.nPasswordLockOutTries = PASSWDLOCKOUTTRIES_DEF;
	i_OpenProfParams.theCreateParams.nPasswordUnlockPeriod = PASSWDUNLOCKPERIOD_DEF;

	// Sasi 05/05/03
	// initialize the variable that indicates whether password reset feature is supported or not
	i_OpenProfParams.boolSupportResetPasswd = FALSE; 

	i_OpenProfParams.tbstrFirstName = "";
	i_OpenProfParams.tbstrLastName = "";
	i_OpenProfParams.tbstrEmail = "";

	return;
}

void CVSPTA::_InitializeSignParams(SIGNMSGPARAMS& i_SignMsgParams)
{
	i_SignMsgParams.nAlgId = VS_SHA_1;
	i_SignMsgParams.nMsgToSignSize = 0;
	i_SignMsgParams.pbyteMsgToSign = NULL;
	i_SignMsgParams.boolAddAuthAttr = FALSE;
	i_SignMsgParams.dateSignDate = 0;

	i_SignMsgParams.boolUTF8EncodeMsgToSign = FALSE;
	i_SignMsgParams.nUTF8MsgToSignSize = 0;
	i_SignMsgParams.pbyteUTF8MsgToSign = NULL;

	return;
}

//
//	Anand	Dec 15, 2000		Start
//
void CVSPTA::_InitializeDecryptParams(DECRYPTMSGPARAMS& i_DecryptMsgParams)
{
	i_DecryptMsgParams.nMsgToDecryptSize = 0;
	i_DecryptMsgParams.nMsgToDecryptSize = NULL;

	return;
}
//
//	Anand	Dec 15, 2000		End
//

void CVSPTA::_InitializeCreateCertReqParams(CREATECERTREQPARAMS& i_CertReqParams)
{
	i_CertReqParams.tbstrSubjectDN = "";
	i_CertReqParams.nHashAlg = 0;
	i_CertReqParams.dwKeyGenFlags = 0;
	i_CertReqParams.nNumOfAttributes = 0;
	i_CertReqParams.ptbstrAttrOIDs = NULL;
	i_CertReqParams.ptbstrAttrVals = NULL;
}

void CVSPTA::_InitializeInstallCertParams(INSTALLCERTPARAMS& i_theInstallCertParams)
{
	i_theInstallCertParams.dwKeyGenFlags = KEY_ENCRYPTION;
	i_theInstallCertParams.boolAlsoImportKey = FALSE;
	i_theInstallCertParams.tbstrKeyToImport = "";
	i_theInstallCertParams.tbstrCertToInstall = "";
}

void CVSPTA::_InitializeSetCertPrefParams(SETCERTPREFPARAMS& i_theCertPrefParams)
{
	i_theCertPrefParams.tbstrPrefName = "";
	i_theCertPrefParams.tbstrPrefVal = "";
}

void CVSPTA::_InitializeRoamingParams(ROAMPARAMS& i_theRoamingParams)
{
	i_theRoamingParams.nNumOfRoamingSrvrs = 0;
	i_theRoamingParams.tbstrStorageSrvr = "";
	i_theRoamingParams.ptbstrRoamingSrvrs = NULL;
	i_theRoamingParams.tbstrClientInfo = "";
	i_theRoamingParams.tbstrClientInfoSig = "";
	i_theRoamingParams.boolRoamInfoChanged = FALSE;
	i_theRoamingParams.boolRoamingResetFeature = FALSE;
}

void CVSPTA::_InitializeCreatePasswdParams(CREATEPASSWDPARAMS& i_theCreatePasswdParams)
{
	i_theCreatePasswdParams.tbstrNewPasswd = "";
	i_theCreatePasswdParams.tbstrConfPasswd = "";
	i_theCreatePasswdParams.boolUseNewPasswd = FALSE;
}

void CVSPTA::_InitializeEnterPasswdParams(ENTERPASSWDPARAMS& i_theEnterPasswdParams)
{
	i_theEnterPasswdParams.tbstrThePasswd = "";
	i_theEnterPasswdParams.boolUseNewPasswd = FALSE;
}

void CVSPTA::_InitializeChangePasswdParams(CHANGEPASSWDPARAMS& i_theChangePasswdParams)
{
	i_theChangePasswdParams.boolUseOldPasswd = FALSE;
	i_theChangePasswdParams.tbstrConfPasswd = "";
	i_theChangePasswdParams.boolUseNewPasswd = FALSE;
	i_theChangePasswdParams.tbstrNewPasswd = "";
	i_theChangePasswdParams.tbstrOldPasswd = "";
}

void CVSPTA::_InitializeSelIDParams(SELIDPARAMS& i_theSelIdParams)
{
	i_theSelIdParams.boolUseDefCert = TRUE;
	i_theSelIdParams.boolMarkAsDefault = FALSE; 
}

void CVSPTA::_InitializeImportP12Params(IMPORTP12PARAMS& i_theImportP12Params)
{
	i_theImportP12Params.nKeyFileOrBlob = 0;
	i_theImportP12Params.tbstrKeyFileOrBlob = "";
	i_theImportP12Params.tbstrP12Passwd = "";
	i_theImportP12Params.tbstrIssDN = "";
	i_theImportP12Params.tbstrSerNum = "";
}

void CVSPTA::_InitializeExportP12Params(EXPORTP12PARAMS& i_theExportP12Params)
{
	i_theExportP12Params.nKeyFileOrBlob = 0;
	i_theExportP12Params.tbstrKeyFileOrBlob = "";
	i_theExportP12Params.tbstrP12Passwd = "";
	i_theExportP12Params.tbstrP12ConfPasswd = "";
	i_theExportP12Params.nPasswordQuality = PASSWDQUAL_ANYPASSWDOK;
	i_theExportP12Params.nPasswordLength = PASSWDLENGTH_DEF_MIN;
	i_theExportP12Params.boolShowFileName = TRUE;
	i_theExportP12Params.boolUsePasswd = FALSE;
}

//
//	Sasi	May 05, 2003		Start
//
void CVSPTA::_InitializeGetSecretQuestionParams(GETSECRETQUESTIONPARAMS& i_theGetSecretQuestionParams)
{
	i_theGetSecretQuestionParams.tbstrProfName = "";
}

void CVSPTA::_InitializeResetPasswdParams(RESETPASSWDPARAMS& i_theResetPasswdParams)
{
	i_theResetPasswdParams.tbstrConfPasswd = "";
	i_theResetPasswdParams.boolUseNewPasswd = FALSE;
	i_theResetPasswdParams.tbstrNewPasswd = "";
	i_theResetPasswdParams.tbstrSecretAnswer = "";
}

void CVSPTA::_InitializeCreateSecretParams(CREATESECRETPARAMS& i_theCreateSecretParams)
{
	i_theCreateSecretParams.tbstrProfName = "";
	i_theCreateSecretParams.tbstrSecretQuestion = "";
	i_theCreateSecretParams.tbstrSecretAnswer = "";
	i_theCreateSecretParams.pVirtualSmartCard = NULL;
}
//
//	Sasi	May 05, 2003		End
//

//This function initializes the UI preferences
//Input		:	The UI Preferences to initialize	
//Output	:	S_OK - success
//			:	E_LANGNOTSUPPORTED	- Language is not supported
//			:	E_NOFONT			- No fonts were found for this language

BOOL CVSPTA::_InitializeUiPrefs(UIPREF& theUIPrefs)
{

	/*This is sample code to load strings from the resources
	HRESULT retVal = S_OK;
	WCHAR* wstrTemp;
	wstrTemp = (WCHAR*)malloc(sizeof(WCHAR)*MAX_RES_STRING_SIZE);
	
	theUIPrefs.boolSelID_ShowDefChkBox = TRUE;
	theUIPrefs.tbstrLgnDlg_LogoUrl = "";
	
    retVal = _LoadStringW(_Module.m_hInst, wLangId, IDS_LGNDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return retVal;
	}
	theUIPrefs.tbstrLgnDlg_Title = wstrTemp;

	LoadString(_Module.m_hInst,IDS_LGNDLG_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrLgnDlg_Title = tstrTemp;

	LoadString(_Module.m_hInst,IDS_CANCEL,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrNewPasswd_CancelBtnText = tstrTemp;
	theUIPrefs.tbstrOpenProf_CancelBtnText = tstrTemp;
	theUIPrefs.tbstrRvwMsg_CancelBtnText = tstrTemp;
	theUIPrefs.tbstrSelID_CancelBtnText = tstrTemp;

	theUIPrefs.tbstrNewPasswd_LogoUrl = "";

	LoadString(_Module.m_hInst,IDS_OK,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrNewPasswd_OKBtnText = tstrTemp;
	theUIPrefs.tbstrOpenProf_OKBtnText = tstrTemp;
	theUIPrefs.tbstrRvwMsg_OKBtnText = tstrTemp;
	theUIPrefs.tbstrSelID_OKBtnText = tstrTemp;

	LoadString(_Module.m_hInst,IDS_NEWPASSWD_TEXT,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrNewPasswd_Text = tstrTemp;

	LoadString(_Module.m_hInst,IDS_NEWPASSWD_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrNewPasswd_Title = tstrTemp;

	LoadString(_Module.m_hInst,IDS_OPENPROF_TEXT,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrOpenProf_Text = tstrTemp;

	LoadString(_Module.m_hInst,IDS_OPENPROF_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrOpenProf_Title = tstrTemp;

	LoadString(_Module.m_hInst,IDS_RVWMSG_TEXT,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrRvwMsg_Text = tstrTemp;

	LoadString(_Module.m_hInst,IDS_RVWMSG_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrRvwMsg_Title = tstrTemp;

	LoadString(_Module.m_hInst,IDS_SELID_TEXT,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrSelID_Text = tstrTemp;

	LoadString(_Module.m_hInst,IDS_SELID_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrSelID_Title = tstrTemp;

	LoadString(_Module.m_hInst,IDS_SELID_CHKBOXTEXT,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrSelID_ChkBoxText = tstrTemp;

	theUIPrefs.tbstrSgnDlg_LogoUrl = "";
	
	LoadString(_Module.m_hInst,IDS_SGNDLG_TITLE,tstrTemp, MAX_RES_STRING_SIZE);
	theUIPrefs.tbstrSgnDlg_Title = tstrTemp;
	*/

	/*Get the default language*/	
	theUIPrefs.wLangID = _GetDefaultLangID();

	theUIPrefs.boolSelID_ShowDefChkBox = TRUE;
	theUIPrefs.tbstrUILogoUrl = "";
	theUIPrefs.tbstrAffLogoUrl = "";

	
	theUIPrefs.tbstrLgnDlg_Title = "";
	
	theUIPrefs.nNewPasswd_CancelBtnText = 0;
	theUIPrefs.nOpenProf_CancelBtnText = 0;
	theUIPrefs.nRvwMsg_CancelBtnText = 0;
	theUIPrefs.nSelID_CancelBtnText = 0;
	theUIPrefs.nCreatePasswd_CancelBtnText = 0;
	theUIPrefs.nEnterPasswd_CancelBtnText = 0;
	theUIPrefs.nChangePasswd_CancelBtnText = 0;
	theUIPrefs.nImpP12_CancelBtnText = 0;
	theUIPrefs.nExpP12_CancelBtnText = 0;

//
//	Sasi	May 05, 2003		Start
//
	theUIPrefs.nGetSecretQuestion_CancelBtnText = 0;
	theUIPrefs.nResetPasswd_CancelBtnText = 0;
	theUIPrefs.nCreateSecret_CancelBtnText = 0;
//
//	Sasi	May 05, 2003		End
//
	theUIPrefs.nNewPasswd_OKBtnText = 0;
	theUIPrefs.nOpenProf_OKBtnText = 0;
	theUIPrefs.nRvwMsg_OKBtnText = 0;
	theUIPrefs.nSelID_OKBtnText = 0;
	theUIPrefs.nCreatePasswd_OKBtnText = 0;
	theUIPrefs.nEnterPasswd_OKBtnText = 0;
	theUIPrefs.nChangePasswd_OKBtnText = 0;
	theUIPrefs.nTimeOut_OKBtnText = 0;
	theUIPrefs.nImpP12_OKBtnText = 0;
	theUIPrefs.nExpP12_OKBtnText = 0;

//
//	Sasi	May 05, 2003		Start
//
	theUIPrefs.nGetSecretQuestion_OKBtnText = 0;
	theUIPrefs.nResetPasswd_OKBtnText = 0;
	theUIPrefs.nCreateSecret_OKBtnText = 0;
//
//	Sasi	May 05, 2003		End
//

	theUIPrefs.tbstrNewPasswd_Text = "";
	theUIPrefs.tbstrNewPasswdNoProf_Text = "";
	theUIPrefs.tbstrNewPasswd_Title = "";

	theUIPrefs.tbstrOpenProf_Text = "";
	theUIPrefs.tbstrOpenProf_Title = "";

	theUIPrefs.tbstrRvwMsg_Text = "";
	theUIPrefs.tbstrRvwMsg_Title = "";

	theUIPrefs.tbstrCreatePasswd_Text = "";
	theUIPrefs.tbstrCreatePasswd_Title = "";

	theUIPrefs.tbstrEnterPasswd_Text = "";
	theUIPrefs.tbstrEnterPasswd_Title = "";

	theUIPrefs.tbstrChangePasswd_Text = "";
	theUIPrefs.tbstrChangePasswd_Title = "";

	theUIPrefs.tbstrTimeOut_Text = "";
	theUIPrefs.tbstrTimeOut_Title = "";

	theUIPrefs.tbstrSelID_Text = "";
	theUIPrefs.tbstrSelID_Title = "";
	theUIPrefs.tbstrSelID_ChkBoxText = "";

	theUIPrefs.tbstrImpP12_Text = "";
	theUIPrefs.tbstrImpP12_Title = "";
	
	theUIPrefs.tbstrExpP12_Text = "";
	theUIPrefs.tbstrExpP12_Title = "";

	theUIPrefs.tbstrSgnDlg_Title = "";

	theUIPrefs.tbstrCreateDlg_Title = "";
	theUIPrefs.tbstrIntroDlg_Title = "";
	theUIPrefs.tbstrIntroDlg_Text = "";
	theUIPrefs.tbstrImpDlg_Title = "";
	theUIPrefs.tbstrExpDlg_Title = "";

//
//	Sasi	May 05, 2003		Start
//
	theUIPrefs.tbstrGetSecretQuestion_Text = "";
	theUIPrefs.tbstrGetSecretQuestion_Title = "";

	theUIPrefs.tbstrResetPasswd_Text = "";
	theUIPrefs.tbstrResetPasswd_Title = "";

	theUIPrefs.tbstrCreateSecret_Text = "";
	theUIPrefs.tbstrCreateSecret_Title = "";
//
//	Sasi	May 05, 2003		End
//

	//Set the fonts
	theUIPrefs.tbstrTitleFont = "";
	theUIPrefs.tbstrTextFont = "";
	theUIPrefs.tbstrBtnFont = "";

//
//	Anand	Dec 15, 2000		Start
//
	theUIPrefs.tbstrSignNotificationUI = "";
	theUIPrefs.tbstrDecryptNotificationUI = "";
//
//	Anand	Dec 15, 2000		End
//

	theUIPrefs.tbstrExpProfileDlg_Title = "";
	theUIPrefs.tbstrImpProfileDlg_Title = "";
	theUIPrefs.boolShowTopMost = FALSE;

	if(_GetFonts(theUIPrefs.wLangID, theUIPrefs.tbstrTitleFont, theUIPrefs.tbstrTextFont, theUIPrefs.tbstrBtnFont) != S_OK)
	{
		//We should never reach here, because we should be able to find atleast
		//one font that supports the system language or english, depending
		//upon m_dwLangID
		theUIPrefs.wLangID = 0;
		return 0;
	}

	theUIPrefs.nSignTransDlgWidth = 0;
	theUIPrefs.nSignTransDlgHeight = 0;

	return 1;
}

BOOL CVSPTA::_InitializeDefUiPrefs(UIPREF& theUIPrefs)
{

	HRESULT retVal;
	WCHAR* wstrTemp;
	wstrTemp = (WCHAR*)malloc(sizeof(WCHAR)*MAX_RES_STRING_SIZE);
	

	
	theUIPrefs.boolSelID_ShowDefChkBox = TRUE;

	//Default logo url
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_DEFLOGOURL,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	//theUIPrefs.tbstrUILogoUrl = wstrTemp;
	theUIPrefs.tbstrUILogoUrl = "";
	theUIPrefs.tbstrAffLogoUrl = "";
	
	//Default logon wizard title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_LGNDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrLgnDlg_Title = wstrTemp;
	
	//Default ok and cancel button text ids
	theUIPrefs.nNewPasswd_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nOpenProf_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nRvwMsg_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nSelID_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nCreatePasswd_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nEnterPasswd_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nChangePasswd_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nTimeOut_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nImpP12_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nExpP12_CancelBtnText = IDS_CANCEL;
//
//	Sasi	May 05, 2003		Start
//
	theUIPrefs.nGetSecretQuestion_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nResetPasswd_CancelBtnText = IDS_CANCEL;
	theUIPrefs.nCreateSecret_CancelBtnText = IDS_CANCEL;
//
//	Sasi	May 05, 2003		End
//

	theUIPrefs.nNewPasswd_OKBtnText = IDS_CREATE;
	theUIPrefs.nOpenProf_OKBtnText = IDS_OPEN;
	theUIPrefs.nRvwMsg_OKBtnText = IDS_SIGN;
	theUIPrefs.nSelID_OKBtnText = IDS_SELECT;
	theUIPrefs.nCreatePasswd_OKBtnText = IDS_OK;
	theUIPrefs.nEnterPasswd_OKBtnText = IDS_OK;
	theUIPrefs.nChangePasswd_OKBtnText = IDS_CHANGE;
	theUIPrefs.nTimeOut_OKBtnText = IDS_UNLOCK;
	theUIPrefs.nImpP12_OKBtnText = IDS_IMPORT;
	theUIPrefs.nExpP12_OKBtnText = IDS_EXPORT;
//
//	Sasi	May 05, 2003		Start
//
	theUIPrefs.nGetSecretQuestion_OKBtnText = IDS_OPEN;
	theUIPrefs.nResetPasswd_OKBtnText = IDS_RESET;
	theUIPrefs.nCreateSecret_OKBtnText = IDS_CREATE;
//
//	Sasi	May 05, 2003		End
//


	//Default new password title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_NEWPASSWD_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrNewPasswd_Title = wstrTemp;
	
	//Default new password text when profile name is specified
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_NEWPASSWD_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrNewPasswd_Text = wstrTemp;
	
	//Default new password text when profile name is not specified
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_NEWPASSWDNOPROF_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrNewPasswdNoProf_Text = wstrTemp;
	
	//Default open profile text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_OPENPROF_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrOpenProf_Text = wstrTemp;	

	//Default open profile title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_OPENPROF_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrOpenProf_Title = wstrTemp;
	

	//Default review message text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_RVWMSG_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrRvwMsg_Text = wstrTemp;
	

	//Default review message title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_RVWMSG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrRvwMsg_Title = wstrTemp;
	
	//Default create password text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CREATEPASSWD_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrCreatePasswd_Text  = wstrTemp;

	//Default enter password text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_ENTERPASSWD_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrEnterPasswd_Text  = wstrTemp;
	
	//Default change password text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CHANGEPASSWD_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrChangePasswd_Text  = wstrTemp;
	
	//Default create password title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CREATEPASSWD_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrCreatePasswd_Title = wstrTemp;

	//Default enter password title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_ENTERPASSWD_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrEnterPasswd_Title = wstrTemp;

	//Default change password title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CHANGEPASSWD_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrChangePasswd_Title = wstrTemp;
	
	//Default timeout text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_TIMEOUT_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrTimeOut_Text  = wstrTemp;
	

	//Default timeout title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_TIMEOUT_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrTimeOut_Title = wstrTemp;
	
	//Default select id text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SELID_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSelID_Text = wstrTemp;
	

	//Default sel id title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SELID_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSelID_Title = wstrTemp;
	
	//Default check box text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SELID_CHKBOXTEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSelID_ChkBoxText = wstrTemp;
	
	//Default check box text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SELID_CHKBOXTEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSelID_ChkBoxText = wstrTemp;
	
	//Default Import P12 text
	retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_IMPORT_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrImpP12_Text  = wstrTemp;
	
	//Default Export P12 text
	retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_EXPORT_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrExpP12_Text  = wstrTemp;
	
	//Default Import P12 title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_IMPORT_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrImpP12_Title = wstrTemp;
	
	//Default Export P12 title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_EXPORT_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrExpP12_Title = wstrTemp;
	
	//Default sign dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SGNDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSgnDlg_Title  = wstrTemp;
	

	//Default create dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CREATEDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrCreateDlg_Title  = wstrTemp;
	

	//Default intro dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_INTRODLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrIntroDlg_Title  = wstrTemp;


	//Default intro dialog text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_INTRODLG_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrIntroDlg_Text  = wstrTemp;

	//Default import dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_IMPORTDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrImpDlg_Title  = wstrTemp;

	//Default export dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_EXPORTDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrExpDlg_Title  = wstrTemp;
//
//	Anand	Dec 15, 2000		Start
//
	//Default sign notification ui
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_SIGNATURE_NOTIFICATION,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrSignNotificationUI  = wstrTemp;

	//Default decrypt notification ui
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_DECRYPT_NOTIFICATION,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrDecryptNotificationUI  = wstrTemp;
//
//	Anand	Dec 15, 2000		End
//

	//Default export profile dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_EXPORTPROFDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrExpProfileDlg_Title  = wstrTemp;

	//Default import profile dialog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_IMPORTPROFDLG_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrImpProfileDlg_Title  = wstrTemp;

//
//	Sasi	May 05, 2003		Start
//
	//Default get secret question dialog text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_GETSECRETQUESTION_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrGetSecretQuestion_Text = wstrTemp;	

	//Default get secret question dilog title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_GETSECRETQUESTION_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrGetSecretQuestion_Title = wstrTemp;

	//Default reset password text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_RESETPASSWD_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrResetPasswd_Text  = wstrTemp;
	

	//Default reset password title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_RESETPASSWD_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrResetPasswd_Title = wstrTemp;
	

	//Default create secret text
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CREATESECRET_TEXT,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrCreateSecret_Text  = wstrTemp;
	

	//Default create secret title
    retVal = _LoadStringW(_Module.m_hInst, theUIPrefs.wLangID, IDS_CREATESECRET_TITLE,wstrTemp, MAX_RES_STRING_SIZE);
	if(retVal != S_OK)
	{
		free(wstrTemp);
		return 0;
	}
	theUIPrefs.tbstrCreateSecret_Title = wstrTemp;
//
//	Sasi	May 05, 2003		End
//
	
	//Set the fonts
	theUIPrefs.tbstrTitleFont = "";
	theUIPrefs.tbstrTextFont = "";
	theUIPrefs.tbstrBtnFont = "";

	if(_GetFonts(theUIPrefs.wLangID, theUIPrefs.tbstrTitleFont, theUIPrefs.tbstrTextFont, theUIPrefs.tbstrBtnFont) != S_OK)
	{
		//We should never reach here, because we should be able to find atleast
		//one font that supports the system language or english, depending
		//upon m_dwLangID
		theUIPrefs.wLangID = 0;
		return 0;
	}

	free(wstrTemp);

	theUIPrefs.nSignTransDlgWidth = 0;
	theUIPrefs.nSignTransDlgHeight = 0;

	return 1;
}

WORD CVSPTA::_GetDefaultLangID()
{
	WORD wRetVal;
	wRetVal = GetSystemDefaultLangID();
		// get corresponding language id defined in the resource string table
	wRetVal = _GetMatchingStringTableLangId(wRetVal);

	if(!_IsLangSupported(wRetVal))
		wRetVal= VS_LANG_ENGLISH_US;
	return wRetVal;
}
	
HRESULT CVSPTA::_GetFonts(WORD wLangID, _bstr_t& tbstrTitleFont, _bstr_t& tbstrTextFont, _bstr_t& tbstrBtnFont)
{
	int nCharset;
	BOOL boolMSSFSupport, boolArialSupport, boolSystemSupport, boolAnySupport, boolGUISupport;
	_bstr_t tbstrFontName = "";


	/* Get the Code page for this language */
	nCharset = _GetCharset(wLangID);
	if(nCharset == -1)
		return E_FAIL;
	
	
	/*Find out what fonts are supported*/
	boolMSSFSupport = boolArialSupport = boolSystemSupport = boolAnySupport = boolGUISupport = FALSE;
	_WhatFontsSupported(nCharset, boolMSSFSupport, boolArialSupport, boolSystemSupport, boolGUISupport, boolAnySupport, tbstrFontName);
	
	if(!boolAnySupport)
		return E_NOFONT;

	/*Set the appropriate fonts*/
	if(boolMSSFSupport)
	{
		tbstrTextFont = "MS Sans Serif";
		tbstrTitleFont = "MS Sans Serif";
		tbstrBtnFont = "MS Sans Serif";
	}
	else if(boolArialSupport)
	{
		tbstrTextFont = "Arial";
		tbstrTitleFont = "Arial";
		tbstrBtnFont = "Arial";
	}
	else if(boolGUISupport)
	{
		tbstrTextFont = tbstrFontName;
		tbstrTitleFont = tbstrFontName;
		tbstrBtnFont = tbstrFontName;
	}
	else if(boolSystemSupport)
	{
		tbstrTextFont = "System";
		tbstrTitleFont = "System";
		tbstrBtnFont = "System";
	}
	else
	{
		tbstrTextFont = tbstrFontName;
		tbstrTitleFont = tbstrFontName;
		tbstrBtnFont = tbstrFontName;
	}

	//if(boolArialSupport)
	//	tbstrTitleFont = "Arial";

	return S_OK;
}

//This function frees the app context
//Input : Pointer to the app context to be freed
//Output :	VS_OK = Success
//		 :	VS_ERROR = Generic error

int CVSPTA::_FreeAppCtxt(PAPPCTXT in_pAppCtxt)
{
	int retVal = VS_OK;

	//An input of NULL is also ok.
	if(in_pAppCtxt)
	{
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theCreatePasswdParams).tbstrNewPasswd)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theCreatePasswdParams).tbstrConfPasswd)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theEnterPasswdParams).tbstrThePasswd)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theChangePasswdParams).tbstrConfPasswd)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theChangePasswdParams).tbstrNewPasswd)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theChangePasswdParams).tbstrOldPasswd)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrConfirmPassword)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrPassword)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrProfName)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theInstallCertParams).tbstrKeyToImport)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrFirstName)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrLastName)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theOpenProfParams).tbstrEmail)

//
//	Sasi	May 05, 2003		Start
//		
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theGetSecretQuestionParams).tbstrProfName)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theResetPasswdParams).tbstrConfPasswd)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theResetPasswdParams).tbstrNewPasswd)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theResetPasswdParams).tbstrSecretAnswer)

		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theCreateSecretParams).tbstrSecretQuestion)
		VSPTA_CLEAN_TBSTR((in_pAppCtxt -> theCreateSecretParams).tbstrSecretAnswer)
//
//	Sasi	May 05, 2003		End
//
		
		if(in_pAppCtxt->theSignMsgParams.pbyteMsgToSign)
		{
			delete(in_pAppCtxt->theSignMsgParams.pbyteMsgToSign);
		}
		if(in_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs)
			delete[] (in_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs);
		if(in_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals)
			delete[] (in_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals);

		if(in_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign)
			delete[] (in_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign);

		delete(in_pAppCtxt);
	}
	return retVal;
}



/*******************************************************/
/*** Environment detection and handling functions ******/
/*******************************************************/
HRESULT CVSPTA::_GetHostAndProtocol(_bstr_t& tbstrHostName, _bstr_t& tbstrProtocolName)
{
	HRESULT retVal = S_OK;

	BSTR bstrHostName;
	BSTR bstrProtocolName;
	CComPtr <IOleContainer>		spContainer;
	CComPtr <IOleClientSite>	spCurrClientSite = NULL;

	if(m_spClientSite)
	{
		spCurrClientSite = m_spClientSite;
	}
	else if(m_spOuterClientSite)
	{
		spCurrClientSite = m_spOuterClientSite;
	}

	if(spCurrClientSite)
	{
		spCurrClientSite->GetContainer (&spContainer);

		CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spDoc (spContainer);
		CComPtr <IHTMLLocation> spHtmlLocation;

		if (spDoc)
		{
			spDoc->get_location (&spHtmlLocation);

			spHtmlLocation->get_hostname (&bstrHostName);
			spHtmlLocation->get_protocol (&bstrProtocolName);

			tbstrHostName		=	bstrHostName;
			tbstrProtocolName	=	bstrProtocolName;
		}
		else
			retVal = E_FAIL;
	}


	return retVal;
}


//This function saves the search criteria in global memory
//Input		:  hResultErr = the error code
//Output	:	none

HRESULT CVSPTA::_SaveSrchCrit()
{
	if(m_pAppCtxt)
	{
		_gpSrchCrit = (PSRCHCRIT)new(SRCHCRIT);
		if(!_gpSrchCrit)
			return E_OUTOFMEMORY;

		_InitializeSrchCrit(*_gpSrchCrit);
		*_gpSrchCrit = m_pAppCtxt->theSrchCrit;
	}
	return S_OK;

}


//This function restores the search criteria from the globally saved one
//Input		:  none
//Output	:  E_FAIL - if failure
//			:  S_OK  - for success.

HRESULT CVSPTA::_RestoreSrchCrit()
{
	if(_gpSrchCrit)
	{
		m_pAppCtxt->theSrchCrit = *_gpSrchCrit;
		delete(_gpSrchCrit);
		_gpSrchCrit = NULL;
	}

	return S_OK;
}



//This function changes the smart card host
//Input		:	bstrHostName - host name
//			:	bstrAppCtxtName - App context name
//Output	:  E_FAIL - if failure
//			:  S_OK  - for success.

HRESULT CVSPTA::_ChangeSmartCardHost(BSTR bstrHostName, BSTR bstrAppCtxtName)
{
	HRESULT hrVSCRetVal;
	HRESULT retVal = S_OK;

	hrVSCRetVal = _gpVirtualSmartCard->VSM_ChangeHost(bstrHostName, bstrAppCtxtName);

	/*If the smart card needs to be closed, free the smart card object*/
	switch(hrVSCRetVal)
	{
	
	case E_HOSTBAD : //This host is not allowed access to the smart card
	case E_APPCTXTBAD : //The app context is not right
		//We need to close the smartcard
		retVal = _gpVirtualSmartCard->VSM_Close();
		delete(_gpVirtualSmartCard);
		_gpVirtualSmartCard = NULL;
		_gboolOpenedWithPassword = TRUE;

		//We also need to delete the search criteria
		if(_gpSrchCrit)
		{
			delete(_gpSrchCrit);
			_gpSrchCrit = NULL;
		}

		break;

	case S_OK :
		//Everything looks fine - dont need to do anything
		break;

	default: //Dont know how to handle it - signal a generic failure
		retVal = E_FAIL;
		break;

	}

	return retVal;
}


//This function checks the environment
//Input		:  nWhatToCheck - What to check
//Output	:  E_NOTINITIALIZED - the PTA is not initialized
//			:  E_CARDNOTOPEN  - the Card is not open
//			:  E_CARDOPENCHECKERROR - An error occured while checking if the card is open.

HRESULT CVSPTA::_CheckEnvironment(short nCheckWhat)
{
	if(nCheckWhat & CHECK_INIT)
	{
		if(!m_bInitialized || !m_pAppCtxt)
			return E_NOTINITIALIZED;

		if(!m_pAppCtxt->tbstrHostName.length())
			return E_NOTINITIALIZED;
	}

	if(nCheckWhat & CHECK_PROF)
	{
		if(!m_pAppCtxt->nIsCapi)
		{
			//If capi flag is set then it means the profile
			//is always open.
			if(!_gpVirtualSmartCard)
				return E_CARDNOTOPEN;
		}
	}

	if(nCheckWhat & CHECK_SELID)
	{
		if(!m_pSelectedId)
			return E_IDNOTSELECTED;
	}

	if(nCheckWhat & CHECK_NONCAPI_MODE)
	{
		/*Check if this is capi or not*/
		if(m_pAppCtxt->nIsCapi)
		{
			return  E_NONCAPIMODEONLY;
		}

	}

	if(nCheckWhat & CHECK_CAPI_MODE)
	{
		/*Check if this is capi or not*/
		if(!m_pAppCtxt->nIsCapi)
		{
			return  E_CAPIMODEONLY;
		}

	}

	_gpCurrPTA = this;

	return S_OK;
}


/*******************************************************/
/************** Error Handleing ************************/
/*******************************************************/


//This creates the error object and sets its description
//Input		:  hResultErr = the error code
//Output	:	none
void CVSPTA::_SetErrorInfo(HRESULT hresultErr)
{
	TCHAR tstrErrStringBuff[MAX_ERR_DESC_SIZE]; 
	_bstr_t tbstrErrStringBuff("");
	int nErrStringId;

	//Get the error string id for the hresult
	switch(hresultErr)
	{
	case E_INITIALIZED :
		nErrStringId = IDS_ERR_INITIALIZED;
		break;
	
	case E_EMPTYARGS :
		nErrStringId = IDS_ERR_EMPTYARGS;
		break;

	case E_INVALIDFLAGS :
		nErrStringId = IDS_ERR_INVALIDFLAGS;
		break;

	case E_INVALIDARGS :
		nErrStringId = IDS_ERR_INVALIDARGS;
		break;

	case E_NOTINITIALIZED :
		nErrStringId = IDS_ERR_NOTINITIALIZED ;
		break;

	case E_CARDNOTOPEN :
		nErrStringId = IDS_ERR_CARDNOTOPEN;
		break;

	
	case E_CARDALREADYOPEN :
		nErrStringId = IDS_ERR_CARDALREADYOPEN;
		break;

	case E_IDNOTSELECTED :
		nErrStringId = IDS_ERR_IDNOTSELECTED;
		break;

	case E_CAPIMODEONLY :
		nErrStringId = IDS_ERR_CAPIMODEONLY ;
		break;

	case E_NONCAPIMODEONLY :
		nErrStringId = IDS_ERR_NONCAPIMODEONLY ;
		break;


	case E_LANGNOTSUPPORTED :
		nErrStringId = IDS_ERR_LANGNOTSUPPORTED;
		break;

	case E_NOFONT :
		nErrStringId = IDS_ERR_NOFONT;
		break;

	case E_FONTNOTAVAILABLE :
		nErrStringId = IDS_ERR_FONTNOTAVAILABLE;
		break;

	case E_FONTDOESNOTSUPPORTLANG :
		nErrStringId = IDS_ERR_FONTDOESNOTSUPPORTLANG;
		break;
	case E_INVALIDVALUE :
		nErrStringId = IDS_ERR_INVALIDVALUE;
		break;

	default :
		nErrStringId = 0;
		break;
	}

	if(nErrStringId)
	{
		//Get the error string from the string table
		LoadString(_Module.m_hInst, nErrStringId, tstrErrStringBuff, MAX_ERR_DESC_SIZE);

		//Convert it from ascii to unicode
		tbstrErrStringBuff = tstrErrStringBuff;

		ICreateErrorInfo* pCreateErrInfo;
		CreateErrorInfo(&pCreateErrInfo);
		pCreateErrInfo->SetDescription(tbstrErrStringBuff);
		SetErrorInfo(0,(IErrorInfo*)pCreateErrInfo);
		pCreateErrInfo->Release();
	}
	

	return;

}


/*
//This function frees the provided data structure 
//Input	 : Pointer to the data structure to be freed
//Output :	VS_OK = Success
//		 :	VS_ERROR = Generic error

int CVSPTA::_FreeDataStructure(short inWhichDS, void* in_pDataStructure)
{
	PCERTIDENTIFIER pCertIdentifier;
	PSRCHCRIT pSrchCrit;
	PUIPREF pUiPref;
	int retVal = VS_OK;

	if(in_pDataStructure)
	{
		switch(inWhichDS)
		{
		case ID_CERTIDENTIFIER :
			pCertIdentifier = (PCERTIDENTIFIER)in_pDataStructure;
			delete(pCertIdentifier);
			break;

		case ID_SRCHCRIT :
			pSrchCrit = (PSRCHCRIT)in_pDataStructure;
			delete(pSrchCrit);
			break;

		case ID_UIPREF :
			pUiPref = (PUIPREF)in_pDataStructure;
			delete(pUiPref);
			break;

		default :
			retVal = VS_ERROR;
			break;

		}

	}
	
	return retVal;
}
*/

HRESULT CVSPTA::_DoOperation(int i_nWhichWizard, int i_nEndOperation)
{
	HRESULT retVal = S_OK;
	
	OPCTXT theOpCtxt;
	int nNumOfProfiles = 0;
	BOOL boolParamFlagsChanged = FALSE;

	VARIANT	varComparisonContainerName;
	int		nContainerNameCmp = 0;
	_bstr_t	tbstr1 = "";
	_bstr_t	tbstr2 = "";

	/*Determine which wizad and uis are to be shown*/
	//Prepare the operation context
	theOpCtxt.pCertListHead = NULL;
	theOpCtxt.ptbstrProfiles = NULL;
	theOpCtxt.pbytePublicKeyId = NULL;
	theOpCtxt.pbytePrivKeyBlob = NULL;
	theOpCtxt.dwPrivKeyBlobSize = 0;
	theOpCtxt.dwPublicKeyIdSize =0;
	theOpCtxt.tbstrSmartCardName = "";
	theOpCtxt.nNumOfProfiles = 0;
	theOpCtxt.nSelectedIdNum =0;
	theOpCtxt.pOParams = new (OPARAMS);
	theOpCtxt.pOParams->pSelectedId = m_pSelectedId;
	theOpCtxt.pOParams->pVirtualSmartCard = _gpVirtualSmartCard;
	theOpCtxt.pOParams->tbstrCertReq = "";
	theOpCtxt.pOParams->tbstrSignature = "";
	theOpCtxt.boolFromUI = FALSE;
	theOpCtxt.boolSignMsgSeen = FALSE;
	theOpCtxt.boolIntroSeen = FALSE;
	theOpCtxt.boolOpenedWithPassword = _gboolOpenedWithPassword;
	theOpCtxt.pvThePtaObj = (void*)this;
	
	retVal = _DetermineWizAndUIs(theOpCtxt, i_nWhichWizard, i_nEndOperation); 

	/*If a ui is to be shown*/
	if(retVal == S_OK)
	{
		if(theOpCtxt.nWizardAndUIs & OPERATION_BITS)
		{
			PUICTXT pUICtxt;

			pUICtxt = _CreateUIContext();
			if(!pUICtxt)
				retVal = E_FAIL;
			else
			{
				/*If there is only one operation to be performed, then set the wizard
				to none*/
				DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

				//First if this is a login wizard then unmask the sign bit so that
				//it doesnt get counted as an operation in the wizard.
				int nWizardAndUIs = theOpCtxt.nWizardAndUIs;
				if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
					nWizardAndUIs &= (~SIGNMSG_BASE);

				//If the ID selection UI has been turned off, then unmask the select id bit so that it does not 
				//get counted as an operation
				if((!m_pAppCtxt->boolShowSelIDUI) && (nWizardAndUIs && SELID_BASE))
				{
					nWizardAndUIs &= (~SELID_BASE);
				}

				if(!_MoreThanOneUI(nWizardAndUIs))
					dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

				
				/*Obtain the context for the first ui*/
				retVal = _InitializeUIContext(pUICtxt,(theOpCtxt.nWizardAndUIs & dwMaskBits),
					_GetFirstUIAndWizard(theOpCtxt.nWizardAndUIs), theOpCtxt.ptbstrProfiles, theOpCtxt.nNumOfProfiles,theOpCtxt.pCertListHead, theOpCtxt.nSelectedIdNum, theOpCtxt.boolOpenedWithPassword);

				if(retVal == S_OK)
				{
					/*Set the ui context*/
					retVal = m_pPtaUI->put_UIContext(pUICtxt);
					
					/*Show the ui*/
					if(retVal == S_OK)
					{
						retVal = m_pPtaUI->ShowUI(&theOpCtxt);
					}
					
				}

				_FreeUIContext(pUICtxt);
				delete (pUICtxt);
			}
		}
	}

	/*Persist the output params*/
	if(retVal == S_OK)
	{
		if(!m_pAppCtxt->dwIsTPM && !m_pAppCtxt->nIsCapi && (!_gpVirtualSmartCard) || (_gpVirtualSmartCard && theOpCtxt.pOParams->pVirtualSmartCard && _gpVirtualSmartCard != theOpCtxt.pOParams->pVirtualSmartCard))
		{
			delete(_gpVirtualSmartCard);
			_gboolOpenedWithPassword = TRUE;
			_gpVirtualSmartCard = theOpCtxt.pOParams->pVirtualSmartCard;
			_gboolOpenedWithPassword = theOpCtxt.boolOpenedWithPassword;
		}

		if((!m_pSelectedId) || (m_pSelectedId && m_pSelectedId != theOpCtxt.pOParams->pSelectedId))
		{
			m_pPtaEngine->FreeIdList(m_pSelectedId);
			m_pSelectedId = theOpCtxt.pOParams->pSelectedId;
		}

		m_tbstrSignature = theOpCtxt.pOParams->tbstrSignature;
		m_tbstrCertReq = theOpCtxt.pOParams->tbstrCertReq;
		m_tbstrCertPref = theOpCtxt.pOParams->tbstrCertPref;


			//	in the TPM case even if a new ID is selected, the virtual smart card
			//	still remembers the old container name etc.
			//	so inside this if statement all this information will be udpated.
		if ( m_pAppCtxt->dwIsTPM && _gpVirtualSmartCard )
		{
			retVal =	_gpVirtualSmartCard -> get_VSM_ProfileName (&varComparisonContainerName);
			if (retVal == S_OK )
			{
				tbstr1 = varComparisonContainerName.bstrVal;
				if (theOpCtxt.pOParams->pSelectedId)
				{
					if (theOpCtxt.pOParams->pSelectedId->pAuxCertInfo)
					{
						tbstr2 = theOpCtxt.pOParams->pSelectedId->pAuxCertInfo->tbstrContainerName;
						nContainerNameCmp = ::strcmp
											(
												(char*) tbstr1,
												(char*) tbstr2
											);
						if (nContainerNameCmp)
						{
							delete _gpVirtualSmartCard;

							_gpVirtualSmartCard = new CVirtualSmartCard;

							retVal =	_gpVirtualSmartCard -> VSM_TPMInitialize
										(
											tbstr2,
											VS_TPM_CONTAINER_OPEN,
											this
										);
							if ( S_OK != retVal )
							{
								return	retVal;
							}

							if ( _gpVirtualSmartCard->VSM_IsPasswdEntered() == 0) {
								retVal = (this)->EnterPassword();
								//VS_CHECK_HRESULT
							}
						}
					}
				}
			}
		}
	}
	else if(retVal == E_PROFCREATED)
	{
		//If a profile has been created we will save it globally. This becomes the 
		//currently open profile
		if((!_gpVirtualSmartCard) || (_gpVirtualSmartCard && _gpVirtualSmartCard != theOpCtxt.pOParams->pVirtualSmartCard))
		{
			delete(_gpVirtualSmartCard);
			_gboolOpenedWithPassword = TRUE;
			_gpVirtualSmartCard = theOpCtxt.pOParams->pVirtualSmartCard;
			_gboolOpenedWithPassword = theOpCtxt.boolOpenedWithPassword;
		}

	}
	else
	{
		if(theOpCtxt.pOParams->pVirtualSmartCard != _gpVirtualSmartCard)
		{
			delete(theOpCtxt.pOParams->pVirtualSmartCard);
			theOpCtxt.pOParams->pVirtualSmartCard = NULL;
		}
		if(theOpCtxt.pOParams->pSelectedId != m_pSelectedId)
		{
			m_pPtaEngine->FreeIdList(theOpCtxt.pOParams->pSelectedId);
		}
	}

	/*Free memory*/
	delete(theOpCtxt.pOParams);
	if(theOpCtxt.pCertListHead)
		m_pPtaEngine->FreeIdList(theOpCtxt.pCertListHead);
	if(theOpCtxt.ptbstrProfiles)
		m_pPtaEngine->FreeLocalProfilesList(theOpCtxt.ptbstrProfiles);
	if(theOpCtxt.pbytePublicKeyId)
		delete [] theOpCtxt.pbytePublicKeyId;

	if ( NULL != theOpCtxt.pbytePrivKeyBlob )
	{
		EraseMemory ( (unsigned int) theOpCtxt.dwPrivKeyBlobSize , (unsigned char*) theOpCtxt.pbytePrivKeyBlob );
		delete []	theOpCtxt.pbytePrivKeyBlob;
		theOpCtxt.pbytePrivKeyBlob =	NULL;
		theOpCtxt.dwPrivKeyBlobSize = 0;
	}

	return retVal; 
}


HRESULT CVSPTA::_DetermineWizAndUIs(OPCTXT& io_theOpCtxt, int i_nWhichWizard, int i_nEndOperation)
{
	HRESULT retVal = S_OK;
	BOOL boolParamFlagsChanged = FALSE;
	_bstr_t tbstrOrigPasswd = "";
	_bstr_t tbstrOrigConfPasswd = "";

	io_theOpCtxt.nWizardAndUIs = i_nWhichWizard;
	
	switch(i_nEndOperation)
	{

	case IMPORTPROFILE_BASE :
		retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrImportProfile(io_theOpCtxt);
		}
		break;

	case EXPORTPROFILE_BASE :
		retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrExportProfile(io_theOpCtxt);
		}
		break;
		
	case SIGNMSG_BASE : //The end operation is a sign message base
		//First try to select an id
		retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, SELID_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrSignMsg(io_theOpCtxt);
		}
		break;		
		
		
	case SELID_BASE :
		//First try to open a profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, OPENPROF_BASE);
	
		if(retVal == S_OK)
		{
			/*Determine if we need to show the select id ui*/
			retVal = _ShowOrSelectId(io_theOpCtxt);
		}
		break;

	case SETCERTPREF_BASE :
		//First try to open a profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrSetCertPref(io_theOpCtxt);
		}
		break;

	case GETCERTPREF_BASE :
		//First try to open a profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrGetCertPref(io_theOpCtxt);
		}
		break;

	case CREATECERTREQ_BASE :
		//First try to open a profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK || retVal == E_PROFCREATED)
		{
			/*Create the cert request*/
			retVal = _ShowOrCreateCertReq(io_theOpCtxt);
		}
		break;


	case INSTALLCERT_BASE :
		//First try to open a  profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			/*Install the cert*/
			retVal = _ShowOrInstallCert(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				io_theOpCtxt.boolFromUI = FALSE;
				io_theOpCtxt.nWizardAndUIs = 0;
				retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, INSTALLCERT_BASE);
			}
		}
		break;

	case CREATEPASSWD_BASE :
		// XXX retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, CREATEPASSWD_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrCreatePasswd(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd = "";
				m_pAppCtxt->theCreatePasswdParams.boolUseNewPasswd = FALSE;

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, CREATEPASSWD_BASE);
			}
		}
		break;

	case ENTERPASSWD_BASE :
		// XXX retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, CREATEPASSWD_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrEnterPasswd(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd = "";
				m_pAppCtxt->theEnterPasswdParams.boolUseNewPasswd = FALSE;

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, ENTERPASSWD_BASE);
			}
		}
		break;

	case CHANGEPASSWD_BASE :
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard,OPENPROF_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrChangePasswd(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd = "";
				m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = "";
				m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd = FALSE;

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, CHANGEPASSWD_BASE);
			}
		}
		break;

	case IMPORTP12_BASE :
		//First try to open a  profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK || retVal == E_PROFCREATED)
		{
			/*Install the cert*/
			retVal = _ShowOrImportP12(io_theOpCtxt, &boolParamFlagsChanged);
		}
		break;

	case EXPORTP12_BASE :
		//First try to open a  profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, SELID_BASE);
		if(retVal == S_OK)
		{
			/*Install the cert*/
			retVal = _ShowOrExportP12(io_theOpCtxt, &boolParamFlagsChanged);
		}
		break;

	case OPENPROF_BASE :
		
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, INTRO_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrOpenProf(io_theOpCtxt, &boolParamFlagsChanged);

			//If the param flags have changed, we need to call the above function again
			//to get determine if a ui needs to be shown with the new flags.
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				io_theOpCtxt.boolFromUI = FALSE;
				io_theOpCtxt.nWizardAndUIs = 0;
				if(m_pAppCtxt->theOpenProfParams.nFlag & OPENPROF_CREATE_ONLY)
				{
					tbstrOrigPasswd = m_pAppCtxt->theOpenProfParams.tbstrPassword;
					m_pAppCtxt->theOpenProfParams.tbstrPassword = "";
					tbstrOrigConfPasswd = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
					m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
				}

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, OPENPROF_BASE);

				if(m_pAppCtxt->theOpenProfParams.nFlag & OPENPROF_CREATE_ONLY)
				{
					m_pAppCtxt->theOpenProfParams.tbstrPassword= tbstrOrigPasswd;
					m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = tbstrOrigConfPasswd;
				}
			}
			else if(retVal == E_CREATESECRET)	
			{
				// Sasi 05/05/03
				// if secret question and answer are needed (for new roaming profile), then
				// we need to prompt the user to enter that info in the create secret dialog
				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, CREATESECRET_BASE);
			}
		}
	
		break;		

	case INTRO_BASE :
		if((!io_theOpCtxt.pOParams->pVirtualSmartCard) && (!m_pAppCtxt->hModAuthDll) && (m_pAppCtxt->theOpenProfParams.nFlag & CREATE_BASE) && 
			!io_theOpCtxt.boolIntroSeen)
		{
			io_theOpCtxt.nWizardAndUIs |= INTRO_BASE;
		}
		
		break;
				// Sasi 05/05/03
				// Show password reset dialog, if user wants to reset profile password
	case RESETPASSWD_BASE :
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard,GETSECRETQUESTION_BASE);
		if(retVal == S_OK)
		{
			retVal = _ShowOrResetPasswd(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer = "";
				m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = "";
				m_pAppCtxt->theResetPasswdParams.boolUseNewPasswd = FALSE;

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, RESETPASSWD_BASE);
			}
		}
		break;

				// Sasi 05/05/03
				// Show dialog to retrieve secret question associated with user's roaming profile
	case GETSECRETQUESTION_BASE :
		if(retVal == S_OK)
		{
			retVal = _ShowOrGetSecretQuestion(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				io_theOpCtxt.boolFromUI = FALSE;
				io_theOpCtxt.nWizardAndUIs = 0;

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, GETSECRETQUESTION_BASE);
			}
		}
		break;

				// Sasi 05/05/03
				// Show dialog to the user to input secret question and answer associated with user's roaming profile
	case CREATESECRET_BASE :
		if(retVal == S_OK)
		{
			retVal = _ShowOrCreateSecret(io_theOpCtxt, &boolParamFlagsChanged);
			if(retVal == S_OK && boolParamFlagsChanged)
			{
				m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion = "";
				m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer = "";

				retVal = _DetermineWizAndUIs(io_theOpCtxt, i_nWhichWizard, CREATESECRET_BASE);
			}
		}
		break;

	case REMOVECERTIFICATES_BASE :
		//First try to open a profile
		retVal = _DetermineWizAndUIs(io_theOpCtxt,i_nWhichWizard, OPENPROF_BASE);
		if(retVal == S_OK)
		{
			/*Remove the certs from CAPI store*/
			retVal = _ShowOrRemoveCertificates(io_theOpCtxt);
		}
		break;
	}

//	VSPTA_CLEAN_TBSTR(tbstrOrigPasswd)
//	VSPTA_CLEAN_TBSTR(tbstrOrigConfPasswd)
	return retVal;
	
}

HRESULT CVSPTA::_ShowOrOpenProf(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	//If this is a capi mode, we do not need to open any profile
	if(m_pAppCtxt->nIsCapi || m_pAppCtxt -> dwIsTPM)
		return retVal;
	
	//Get the list of profiles on this machine.
	if(!io_theOpCtxt.ptbstrProfiles)
		m_pPtaEngine->GetLocalProfilesList(m_pAppCtxt->tbstrAppCtxtName, &(io_theOpCtxt.ptbstrProfiles), io_theOpCtxt.nNumOfProfiles);

	//If a profile is already open, we donot need to show the ui.
	if(io_theOpCtxt.pOParams->pVirtualSmartCard)
	{
		return retVal;
	}

	
	if(m_pAppCtxt->theOpenProfParams.nFlag & OPEN_BASE) //Is it an open operation.
	{
		if(m_pAppCtxt->hModAuthDll)
		{
			retVal = _OpenProfWithAuthDll(io_theOpCtxt, o_pboolParamFlagsChanged);
		}
		else
		{
			retVal = _OpenProfWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);
		}
		
	}
	
	else if(m_pAppCtxt->theOpenProfParams.nFlag & CREATE_BASE)
	{
		if(m_pAppCtxt->hModAuthDll)
		{
			retVal = _CreateProfWithAuthDll(io_theOpCtxt, o_pboolParamFlagsChanged);
		}
		else
		{
			retVal = _CreateProfWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);
		}


	}

	else if(m_pAppCtxt->theOpenProfParams.nFlag & DELETE_BASE) //If this is a delete operation
	{
		if((!m_pAppCtxt->theOpenProfParams.tbstrProfName.length()))
		{
			//If the profile name is not specified, we need to show the ui.
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_DELETE_BASE;
			return retVal;
		}

		/*Try to delete the profile*/
		retVal = _HandleDeleteProfile(&(io_theOpCtxt.ptbstrProfiles),&(io_theOpCtxt.nNumOfProfiles));
		if(retVal == S_OK)
		{
			if(m_pAppCtxt->theOpenProfParams.nFlag & RECREATE_BASE)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_CREATE_ONLY;
				*o_pboolParamFlagsChanged = TRUE;
			}
		}

	}
	else
		retVal = E_INVALIDFLAGS;

	return retVal;

}

HRESULT CVSPTA::_ShowOrSelectId(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;
	
	if(!io_theOpCtxt.pOParams->pSelectedId) //If a id is not selected
	{
		//Check if a profile is open
		if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi) && !(m_pAppCtxt->dwIsTPM))
		{
			//A profile is not open. So obviously a cert has not been selected.
			//So we need to show the ui.
			io_theOpCtxt.nWizardAndUIs |= SELID_BASE;
		}
		else
		{
			//Try to get a list of certs that match the criteria if required.
			if(!io_theOpCtxt.pCertListHead)
				retVal = m_pPtaEngine->GetMatchingCerts(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->tbstrAppCtxtName, m_pAppCtxt->theSrchCrit, &(io_theOpCtxt.pCertListHead));
		
			if(retVal == S_OK) 
			{
				if(io_theOpCtxt.pCertListHead && io_theOpCtxt.pCertListHead->pidlistnodeNext != NULL) //If we have more than one matching cert
															 //we need to show the select id ui
				{
					io_theOpCtxt.nWizardAndUIs |= SELID_BASE;
				}
				else //If we have only one ui, then we need to show the cert select ui, only if it is the
					 //login wizard or the export p12 wizard and if the select id ui has not been turned off.
				{
					if((((io_theOpCtxt.nWizardAndUIs  & WIZARD_BITS) == LOGIN_WIZARD_BASE) ||
						((io_theOpCtxt.nWizardAndUIs  & WIZARD_BITS) == EXPORTP12_WIZARD_BASE)) &&
						m_pAppCtxt->boolShowSelIDUI)
						io_theOpCtxt.nWizardAndUIs  |= SELID_BASE;
					else //We will not show this cert, so set the opctxt
					{
						io_theOpCtxt.pOParams->pSelectedId  = m_pPtaEngine->CopyCert(io_theOpCtxt.pCertListHead);
						m_boolIdSatisfiesSrchCrit = TRUE;
					}
				}
			}
		}
	}
	else if(io_theOpCtxt.pOParams->pSelectedId && !m_boolIdSatisfiesSrchCrit)
	{
		io_theOpCtxt.nWizardAndUIs |= SELID_BASE;
	}
	else if(io_theOpCtxt.pOParams->pSelectedId && !m_boolUserHasSeenMsg && 
		(((io_theOpCtxt.nWizardAndUIs & WIZARD_BITS)  == LOGIN_WIZARD_BASE) ||
		 ((io_theOpCtxt.nWizardAndUIs & WIZARD_BITS)  == EXPORTP12_WIZARD_BASE))) //if a id is selected but the user has not seen it
	{																						//and this is the login wizard or export wizard
		io_theOpCtxt.nWizardAndUIs |= SELID_BASE;
	}
	else
	{
		//An id has been selected. Does it need to be marked as default?
		if(m_pAppCtxt->theSelIdParams.boolMarkAsDefault)
		{
			m_pPtaEngine->SetDefaultCert(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->tbstrAppCtxtName, io_theOpCtxt.pOParams->pSelectedId->pDecCertInfo->tbstrIssuerDN,
				io_theOpCtxt.pOParams->pSelectedId->pDecCertInfo->tbstrSerNum);
		}
	}
	
	return retVal;
}

HRESULT CVSPTA::_ShowOrSetCertPref(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;
	if(io_theOpCtxt.pOParams->pVirtualSmartCard || m_pAppCtxt->nIsCapi || m_pAppCtxt->dwIsTPM)
	{
		retVal = _HandleSetCertPref(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theCertIdentifier, 
			m_pAppCtxt->theCertPrefParams.tbstrPrefName, m_pAppCtxt->theCertPrefParams.tbstrPrefVal);
	}
	else
		io_theOpCtxt.nWizardAndUIs |= SETCERTPREF_BASE;

	return retVal;
}

HRESULT CVSPTA::_ShowOrGetCertPref(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;
	if(io_theOpCtxt.pOParams->pVirtualSmartCard || m_pAppCtxt->nIsCapi || m_pAppCtxt->dwIsTPM)
	{
		retVal = _HandleGetCertPref(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theCertIdentifier, 
			m_pAppCtxt->theCertPrefParams.tbstrPrefName, &(io_theOpCtxt.pOParams->tbstrCertPref));
	}
	else
		io_theOpCtxt.nWizardAndUIs |= SETCERTPREF_BASE;

	return retVal;
}


HRESULT CVSPTA::_ShowOrSignMsg(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;
	int		nMsgBox;

	//
	//	Anand	Dec 15, 2000
	//
	//	Added the do loop.
	//
	do
	{
		//If user has seen the message to be signed, or if this is the login wizard
		// we do not need to show the ui - or if a trusted application has turned off
		// the ui, we do not need to show the ui.
		if(io_theOpCtxt.boolSignMsgSeen || (io_theOpCtxt.nWizardAndUIs & LOGIN_WIZARD_BASE) || !m_pAppCtxt->boolShowUI)
		{
			//
			//	Anand	Dec 15, 2000
			//
			//	Added this if condition.
			//	if a trusted application has turned off the ui and has set the notification ON
			//	then show the message to the user.
			//
			if ( (TRUE == m_pAppCtxt -> boolSignNotificationUI) && (FALSE == m_pAppCtxt->boolShowUI) )
			{
				nMsgBox = ::MessageBox(NULL, (m_pAppCtxt -> theUIPrefs).tbstrSignNotificationUI, "VeriSign Personal Trust Agent", MB_OK);
				if ( IDCANCEL == nMsgBox )
				{
						//	the user canceled the operation so return error
					retVal = E_USERCANCELLED;
					break;
				}
			}

			//If we have a cert selected, and if we have a message to sign, we can do a
			//signature
			if(io_theOpCtxt.pOParams->pSelectedId && m_pAppCtxt->theSignMsgParams.pbyteMsgToSign)
			{
				retVal = _HandleSign(io_theOpCtxt.pOParams->pVirtualSmartCard, io_theOpCtxt.pOParams->pSelectedId, &(io_theOpCtxt.pOParams->tbstrSignature));
			}
			else
			{
				io_theOpCtxt.nWizardAndUIs |= SIGNMSG_BASE; //We need to do the sign operation
			}
		}
		else
		{
			//We need to show a ui
			io_theOpCtxt.nWizardAndUIs |= SIGNMSG_BASE;

		}
	}	while (0);

	return retVal;
}

HRESULT CVSPTA::_ShowOrCreateCertReq(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;

	//If a profile is not open then we cannot create a cert request

	if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi) && !(m_pAppCtxt->dwIsTPM))
	{
		io_theOpCtxt.nWizardAndUIs |= CREATECERTREQ_BASE;
	}

/*
	if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
	{
		if ( m_pAppCtxt->dwIsTPM )
		{
			io_theOpCtxt.nWizardAndUIs = ENTERPASSWD_BASE;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= CREATECERTREQ_BASE;
		}
	}
*/
	else if (m_pAppCtxt->nIsCapi)
		retVal = E_NOTIMPL;
	else
	{
		//Handle the creation of the cert request
		PBYTE pbytePubKeyIdentifier;
		DWORD dwPubKeyIdentifierHash;
		// 
		// Modified by - Infosys Technologies Ltd. 
		// Change Request - CR#21529
		// Description - Change the function signature to accomodate the bIsPrivateKeyExportable flag. 
		// CR#21529 - Begin
		// Date Modified - July 3, 2004
		retVal = m_pPtaEngine->CreateCertReq(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theCreateCertReqParams.tbstrSubjectDN, m_pAppCtxt->theCreateCertReqParams.dwKeyGenFlags,
			m_pAppCtxt->theCreateCertReqParams.nHashAlg, m_pAppCtxt->theCreateCertReqParams.nNumOfAttributes, m_pAppCtxt->theCreateCertReqParams.ptbstrAttrOIDs,
			m_pAppCtxt->theCreateCertReqParams.ptbstrAttrVals, &(io_theOpCtxt.pOParams->tbstrCertReq),&pbytePubKeyIdentifier, &dwPubKeyIdentifierHash, m_pAppCtxt->theCreateCertReqParams.bIsPrivateKeyExportable);
                 // CR# 21529 Modification Ends
		//Remember the profile name associated with this public key
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->Remember_PubKey_SmartCardKeyType_Assoc(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theCreateCertReqParams.dwKeyGenFlags, pbytePubKeyIdentifier,dwPubKeyIdentifierHash);
		}
	}
	return retVal;
}

HRESULT CVSPTA::_ShowOrInstallCert(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;

	/*Decode the pkcs7 and obtain a list of certs to install*/
	if(retVal == S_OK && !io_theOpCtxt.pCertListHead)
	{
		retVal = m_pPtaEngine->DecodePKCS7AndGetCerts(m_pAppCtxt->theInstallCertParams.tbstrCertToInstall,
			&(io_theOpCtxt.pCertListHead));

		/*Obtain the public key identifier from the public key*/
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(
				(io_theOpCtxt.pCertListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo),
				NULL,&io_theOpCtxt.dwPublicKeyIdSize);
			if(retVal == S_OK)
			{
				io_theOpCtxt.pbytePublicKeyId = new BYTE[io_theOpCtxt.dwPublicKeyIdSize];
				if(!io_theOpCtxt.pbytePublicKeyId)
					retVal = E_FAIL;
				else
				{
					retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(
								io_theOpCtxt.pCertListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo,
								io_theOpCtxt.pbytePublicKeyId ,&io_theOpCtxt.dwPublicKeyIdSize );
				}
			}
		}

	}

	/*Decode the P8 and obtain the private key to install, if needed*/
	if(retVal == S_OK && !io_theOpCtxt.pbytePrivKeyBlob && m_pAppCtxt->theInstallCertParams.boolAlsoImportKey)
	{
		retVal = m_pPtaEngine->DecodePKCS8AndGetPrivKey(m_pAppCtxt->theInstallCertParams.tbstrKeyToImport,
			&(io_theOpCtxt.pbytePrivKeyBlob), &io_theOpCtxt.dwPrivKeyBlobSize);
	}

	//If we havent already then we need to decode the install cert pkcs7
	//and obtain the name of the profile in which to install the cert
	if((io_theOpCtxt.tbstrSmartCardName.length() == 0) 
		&& !(m_pAppCtxt->nIsCapi) /*&& !(m_pAppCtxt->dwIsTPM)*/)
	{
		

		/*Obtain the name of the smart card to open from the public key identifier*/
		if(retVal == S_OK)
		{ 
			m_pPtaEngine->Restore_PubKey_SmartCardKeyType_Assoc
				(
				 io_theOpCtxt.pbytePublicKeyId,
				 io_theOpCtxt.dwPublicKeyIdSize,
				 &io_theOpCtxt.tbstrSmartCardName,
				 &m_pAppCtxt->theInstallCertParams.dwKeyGenFlags
				);
		}
		else
		{
			delete[] io_theOpCtxt.pbytePublicKeyId;
			io_theOpCtxt.pbytePublicKeyId = NULL;
			io_theOpCtxt.pbytePublicKeyId = NULL;
		}

		
	}
	
	//If a smart card is open make sure that it is the correct one
	//True if it is VSMode || TMPmode && !CAPImode
	//if the below existing doesn't work use ..
	if(retVal == S_OK && (io_theOpCtxt.pOParams->pVirtualSmartCard || m_pAppCtxt->dwIsTPM) && !(m_pAppCtxt->nIsCapi))
//	if(retVal == S_OK && io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
	{
		
		//Make sure that this virtual smart card is the same as the 
		//one in which the public key was created.
		if(retVal == S_OK)
		{
			if ( io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->dwIsTPM) )
			{
				retVal =	io_theOpCtxt.pOParams->pVirtualSmartCard->VSM_IsPrivKeyAvailable
					(
						io_theOpCtxt.pbytePublicKeyId, 
						io_theOpCtxt.dwPublicKeyIdSize
					);
			}

			if(!m_pAppCtxt->theInstallCertParams.boolAlsoImportKey && retVal == E_KEYDOESNOTEXIST)
			{
				retVal = E_INSTALLCERTWRONGPROFILE;

				//This profile was not the one in which the public key was created
				if(io_theOpCtxt.boolFromUI)
				{
					retVal = m_pPtaUI->ShowMessage(INSTALLCERT_PROFILE_NOT_CORRECT);
					io_theOpCtxt.pOParams->pVirtualSmartCard->VSM_Close();
					delete io_theOpCtxt.pOParams->pVirtualSmartCard;
					io_theOpCtxt.pOParams->pVirtualSmartCard = NULL;

					//Smart card is not open we need to come back later
					io_theOpCtxt.nWizardAndUIs |= INSTALLCERT_BASE;	

					*o_pboolParamFlagsChanged = TRUE;

					retVal = S_OK;
				}
			}
			else if(m_pAppCtxt->theInstallCertParams.boolAlsoImportKey || retVal == S_OK) //We have the right smart card
			{
				retVal =	S_OK;
				/*Install the private key if needed*/
				if(m_pAppCtxt->theInstallCertParams.boolAlsoImportKey)
				{
					if(io_theOpCtxt.pbytePrivKeyBlob)
					{
						retVal = m_pPtaEngine->InstallPrivKey(io_theOpCtxt.pOParams->pVirtualSmartCard,
							io_theOpCtxt.pbytePrivKeyBlob, io_theOpCtxt.dwPrivKeyBlobSize, io_theOpCtxt.pbytePublicKeyId);
					}
					else 
						retVal = E_NOPRIVKEYBLOB;
				}

				/*Install the certificate*/
				unsigned int nCertNum = 0xffffffff;
				if(retVal == S_OK && !(m_pAppCtxt->dwIsTPM))
				{
					retVal = m_pPtaEngine->InstallCerts(io_theOpCtxt.pOParams->pVirtualSmartCard,
						io_theOpCtxt.pCertListHead, &nCertNum);
				}

				/*Make this installation capi compliant*/
				if(retVal == S_OK && m_pAppCtxt->boolCapiCert)
				{
					if (m_pAppCtxt->dwIsTPM)
					{
						retVal = m_pPtaEngine->MakeCapiCompliantCertInstall(io_theOpCtxt.pOParams->pVirtualSmartCard,
							io_theOpCtxt.pCertListHead, io_theOpCtxt.pbytePublicKeyId,
							io_theOpCtxt.dwPublicKeyIdSize,(BYTE)(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&KEYTYPE_BASE),
							((BOOL)(!(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&EXPORTABLE_BASE))), m_pAppCtxt->theOpenProfParams.boolRoamProfile,
							m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, nCertNum, io_theOpCtxt.tbstrSmartCardName);
					}
					else
					{
						retVal = m_pPtaEngine->MakeCapiCompliantCertInstall(io_theOpCtxt.pOParams->pVirtualSmartCard,
							io_theOpCtxt.pCertListHead, io_theOpCtxt.pbytePublicKeyId,
							io_theOpCtxt.dwPublicKeyIdSize,(BYTE)(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&KEYTYPE_BASE),
							((BOOL)(!(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&EXPORTABLE_BASE))), m_pAppCtxt->theOpenProfParams.boolRoamProfile,
							m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, nCertNum, _bstr_t(""));
					}
				}

				/*Forget about this pending cert*/
				if(retVal == S_OK)
				{
					
					/*Erase the association*/
					if(retVal == S_OK)
					{ 
						m_pPtaEngine->Delete_PubKey_Assoc
							(
							 io_theOpCtxt.pbytePublicKeyId,
							 io_theOpCtxt.dwPublicKeyIdSize 
							);
					}

				}
			}
		}
		
	}
	
	if(retVal == S_OK && !io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi) &&!(m_pAppCtxt->dwIsTPM))
	{
		/*Extract the user name from the smart card name*/
		if(retVal == S_OK)
		{
			BSTR bstrSmartCardName;
			BSTR bstrUserName;
			BSTR bstrPath;
			BSTR bstrApContext;

			bstrSmartCardName = io_theOpCtxt.tbstrSmartCardName.copy();
			
			//m_pAppCtxt->theOpenProfParams.tbstrProfName = "";

			//Now extract the profile name
			retVal = ParseProfile_Path_Name(bstrSmartCardName,&bstrUserName,&bstrPath,&bstrApContext);
			if(retVal == S_OK)
			{
                         // Wasim : Nov 2001, fixed bug related to the browser hanging if the user tries to pickup the
			 // ID more than once. The bug is bcos we remove the association from the registry which maps
			 // the pending certificate to the profile name. So the profile name is NULL when user picks up
			 // an ID which is already installed.
				if(_bstr_t(bstrUserName) != _bstr_t(""))
				{
				    if(m_pAppCtxt->theOpenProfParams.tbstrProfName != _bstr_t(bstrUserName))
				    {
					m_pAppCtxt->theOpenProfParams.tbstrProfName = bstrUserName;
					*o_pboolParamFlagsChanged = TRUE;
				    }
				}
			}
			
			SysFreeString(bstrSmartCardName);
			SysFreeString(bstrUserName);
			SysFreeString(bstrPath);
			SysFreeString(bstrApContext);

		}

		//Smart card is not open we need to come back later
		io_theOpCtxt.nWizardAndUIs |= INSTALLCERT_BASE;	
	}

	return retVal;
}

HRESULT CVSPTA::_ShowOrCreatePasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsCreated)
{
	HRESULT retVal = S_OK;
	
	do
	{
		/*If a profile is open and try to change the password*/
		if(io_theOpCtxt.pOParams->pVirtualSmartCard)
		{
			if(m_pAppCtxt->hModAuthDll)
			{
				// XXX
				assert(0);
				// retVal = _ChangePasswdWithAuthDll(io_theOpCtxt, o_pboolParamFlagsChanged);
			}
			else
			{
				retVal = _CreatePasswdWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsCreated);
			}

			
			if(retVal != S_OK)
				break;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
		}
		
	}while(0);

//	VSPTA_CLEAN_TBSTR(tbstrMessageToDisplay)
//	VSPTA_CLEAN_TBSTR(tbstrPasswdQualString)

	return retVal;
}

HRESULT CVSPTA::_ShowOrEnterPasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsCreated)
{
	HRESULT retVal = S_OK;
	
	do
	{
		/*If a profile is open and try to change the password*/
		if(io_theOpCtxt.pOParams->pVirtualSmartCard)
		{
			if(m_pAppCtxt->hModAuthDll)
			{
				// XXX
				assert(0);
				// retVal = _ChangePasswdWithAuthDll(io_theOpCtxt, o_pboolParamFlagsChanged);
			}
			else
			{
				retVal = _EnterPasswdWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsCreated);
			}

			
			if(retVal != S_OK)
				break;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= ENTERPASSWD_BASE;
		}
		
	}while(0);

//	VSPTA_CLEAN_TBSTR(tbstrMessageToDisplay)
//	VSPTA_CLEAN_TBSTR(tbstrPasswdQualString)

	return retVal;
}

HRESULT CVSPTA::_ShowOrChangePasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	do
	{
		/*If a profile is open and try to change the password*/
		if(io_theOpCtxt.pOParams->pVirtualSmartCard)
		{
			if(m_pAppCtxt->hModAuthDll)
			{
				retVal = _ChangePasswdWithAuthDll(io_theOpCtxt, o_pboolParamFlagsChanged);
			}
			else
			{
				retVal = _ChangePasswdWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);
			}

			
			if(retVal != S_OK)
				break;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
		}
		
	}while(0);

//	VSPTA_CLEAN_TBSTR(tbstrMessageToDisplay)
//	VSPTA_CLEAN_TBSTR(tbstrPasswdQualString)

	return retVal;
}


HRESULT CVSPTA::_ShowOrExportProfile(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;

	do
	{
		//If a profile is not open then we cannot export profile data
		if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
		{
			io_theOpCtxt.nWizardAndUIs |= EXPORTPROFILE_BASE;
		}
		else if (m_pAppCtxt->nIsCapi)
			retVal = E_NOTIMPL;
		else
		{
			retVal = m_pPtaEngine->ExportProfile(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theExportProfileParams.nExportProfileFlags,
												m_pAppCtxt->theExportProfileParams.pbProfilePasswd, m_pAppCtxt->theExportProfileParams.nProfilePasswd,
												m_pAppCtxt->theExportProfileParams.tbstrProfileData);

		}		
	}while(0);

	return retVal;
}


HRESULT CVSPTA::_ShowOrImportProfile(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;

	do
	{
		//If a profile is not open then we cannot export profile data
		if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
		{
			io_theOpCtxt.nWizardAndUIs |= IMPORTPROFILE_BASE;
		}
		else if (m_pAppCtxt->nIsCapi)
			retVal = E_NOTIMPL;
		else
		{
			retVal = m_pPtaEngine->ImportProfile(io_theOpCtxt.pOParams->pVirtualSmartCard, m_pAppCtxt->theImportProfileParams.pbProfilePasswd, 
												m_pAppCtxt->theImportProfileParams.nProfilePasswd, m_pAppCtxt->theImportProfileParams.tbstrProfileData);
		}		
	}while(0);

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ShowOrGetSecretQuestion
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function retrieves secret question correspoding to user'
//						roaming profile.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ShowOrGetSecretQuestion(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	//If this is a local profile, we do not need to retrieve any secret question
	if(!m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		return E_RESETFEATURE_NOT_SUPPORTED;
	
	if(!m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion.length())
	{
		retVal = _GetSecretQuestionWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);
	}

	return retVal;

}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ShowOrResetPasswd
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function resets password for user's roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ShowOrResetPasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	do
	{
		/*If secret question is present, try to reset the password*/
		if(m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion.length())
		{
			retVal = _ResetPasswdWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);
			
			if(retVal != S_OK)
				break;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
		}
		
	}while(0);


	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ShowOrCreateSecret
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function takes secret question and answer from the user and stores
//						it along with user's roaming profile.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ShowOrCreateSecret(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	do
	{
		/*Check if profile is created */
		if(m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard)
		{

			retVal = _CreateSecretWithPTAAuth(io_theOpCtxt, o_pboolParamFlagsChanged);

			if(retVal != S_OK)
				break;
		}
		else
		{
			io_theOpCtxt.nWizardAndUIs |= CREATESECRET_BASE;
		}
		
	}while(0);


	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ShowOrRemoveCertificates
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function enumerates the certificates from the profile and
//						removes them from CAPI store.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-26-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ShowOrRemoveCertificates(OPCTXT& io_theOpCtxt)
{
	HRESULT retVal = S_OK;

	do
	{
		if(m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		{
			//If a profile is not open then we cannot get the certs from the profile
			if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
			{
				io_theOpCtxt.nWizardAndUIs |= REMOVECERTIFICATES_BASE;
			}
			else
			{
				retVal = m_pPtaEngine->RemoveCertsInProfileFromCapiStore(io_theOpCtxt.pOParams->pVirtualSmartCard);

			}
		} 
		else
			retVal = E_NOTIMPL;

	}while(0);

	return retVal;
}


HRESULT CVSPTA::_CreatePasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";


	do
	{
		retVal = _HandleCreatePasswd(io_theOpCtxt.pOParams->pVirtualSmartCard, io_theOpCtxt.boolOpenedWithPassword);

		switch(retVal)
		{
		case E_INVALIDPASSWD_PASSWDREQD :
			//We need to show the ui because we need a password
			io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
			retVal = S_OK;
			break;

		case E_INVALIDPASSWD_NOPASSWDREQD :
		case E_INVALIDPASSWD_LESSTHANMINLENGTH :
		case E_INVALIDPASSWD_NOTNUMERICONLY :
		case E_INVALIDPASSWD_INVALIDCHARS :
		case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
		case E_INVALIDPASSWD_NONUMATBEGIN :
		case E_INVALIDPASSWD_NONUMATEND :
			if(io_theOpCtxt.boolFromUI)
			{
				m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd = "";

				//Create the string to be displayed 
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					tbstrMessageToDisplay = wstrTemp;
				}

				if(retVal == S_OK)
				{
					retVal = _GetPasswdQualityString(&tbstrPasswdQualString);
				}

				if(retVal == S_OK)
				{
					tbstrMessageToDisplay += tbstrPasswdQualString;

					//Display it.
					VARIANT varMsgToDisplay;
					varMsgToDisplay.vt = VT_BSTR;
					varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

					retVal = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
				}

				if(retVal == S_OK)
				{
					retVal = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
					io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
				}
			}

			break;

		case E_CONFIRMPASSWORDNOMATCH :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
				m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
			}
			break;
		
		case E_INVALIDPASSWD :
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
			break;

		case E_PROFLOCKEDOUT :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
			}
			break;

		default :
			break;

		}

	}while(0);
	
	return retVal;
}

HRESULT CVSPTA::_EnterPasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";


	do
	{
		retVal = _HandleEnterPasswd(io_theOpCtxt.pOParams->pVirtualSmartCard, io_theOpCtxt.boolOpenedWithPassword);

		switch(retVal)
		{
		case E_INVALIDPASSWD_PASSWDREQD :
			//We need to show the ui because we need a password
			io_theOpCtxt.nWizardAndUIs |= ENTERPASSWD_BASE;
			retVal = S_OK;
			break;

		case E_INVALIDPASSWD_NOPASSWDREQD :
		case E_INVALIDPASSWD_LESSTHANMINLENGTH :
		case E_INVALIDPASSWD_NOTNUMERICONLY :
		case E_INVALIDPASSWD_INVALIDCHARS :
		case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
		case E_INVALIDPASSWD_NONUMATBEGIN :
		case E_INVALIDPASSWD_NONUMATEND :
			if(io_theOpCtxt.boolFromUI)
			{
				m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd = "";

				//Create the string to be displayed 
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					tbstrMessageToDisplay = wstrTemp;
				}

				if(retVal == S_OK)
				{
					retVal = _GetPasswdQualityString(&tbstrPasswdQualString);
				}

				if(retVal == S_OK)
				{
					tbstrMessageToDisplay += tbstrPasswdQualString;

					//Display it.
					VARIANT varMsgToDisplay;
					varMsgToDisplay.vt = VT_BSTR;
					varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

					retVal = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
				}

				if(retVal == S_OK)
				{
					retVal = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
					io_theOpCtxt.nWizardAndUIs |= ENTERPASSWD_BASE;
				}
			}

			break;
 		/* XXX
		case E_CONFIRMPASSWORDNOMATCH :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CREATEPASSWD_BASE;
				m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
			}
			break;
		*/
		case E_INVALIDPASSWD :
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= ENTERPASSWD_BASE;
			break;

		case E_PROFLOCKEDOUT :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= ENTERPASSWD_BASE;
			}
			break;

		default :
			break;

		}

	}while(0);
	
	return retVal;
}

HRESULT CVSPTA::_ChangePasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";


	do
	{
		retVal = _HandleChangePasswd(io_theOpCtxt.pOParams->pVirtualSmartCard, io_theOpCtxt.boolOpenedWithPassword);

		switch(retVal)
		{
		case E_INVALIDPASSWD_PASSWDREQD :
			//We need to show the ui because we need a password
			io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			retVal = S_OK;
			break;

		case E_INVALIDPASSWD_NOPASSWDREQD :
		case E_INVALIDPASSWD_LESSTHANMINLENGTH :
		case E_INVALIDPASSWD_NOTNUMERICONLY :
		case E_INVALIDPASSWD_INVALIDCHARS :
		case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
		case E_INVALIDPASSWD_NONUMATBEGIN :
		case E_INVALIDPASSWD_NONUMATEND :
			if(io_theOpCtxt.boolFromUI)
			{
				m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = "";

				//Create the string to be displayed 
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					tbstrMessageToDisplay = wstrTemp;
				}

				if(retVal == S_OK)
				{
					retVal = _GetPasswdQualityString(&tbstrPasswdQualString);
				}

				if(retVal == S_OK)
				{
					tbstrMessageToDisplay += tbstrPasswdQualString;

					//Display it.
					VARIANT varMsgToDisplay;
					varMsgToDisplay.vt = VT_BSTR;
					varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

					retVal = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
				}

				if(retVal == S_OK)
				{
					retVal = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
					io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
				}
			}

			break;
		case E_CONFIRMPASSWORDNOMATCH :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
				m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
			}
			break;

		case E_INVALIDPASSWD :
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			break;

		case E_PROFLOCKEDOUT :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			}
			break;

		default :
			break;

		}

	}while(0);
	
	return retVal;
}

HRESULT CVSPTA::_ChangePasswdWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	VARIANT varUsername;
	VARIANT varOrigPasswd;
	VARIANT varPasswd;
	VARIANT varAppCtxt;
	VARIANT varPasswordQuality;
	VARIANT varPurpose;
	LPFNGetUsernamePasswd pfnGetUsernamePasswd = NULL;
	LPFNProcessEvent pfnProcessEvent = NULL;
	BSTR bstrUserName = NULL; 
	BSTR bstrPath = NULL;
	BSTR bstrApContext = NULL;

	/*Get the username and the password for the new profile*/
	varPurpose.vt = VT_I2;
	varPurpose.iVal = AUTHDLL_CHANGEPASSWD;
	varAppCtxt.vt = VT_BSTR;
	varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
	varPasswordQuality.vt = VT_EMPTY;
	varOrigPasswd.vt = VT_EMPTY;
	varPasswd.vt = VT_EMPTY;	

	do 
	{
		//Get the username from the virtual smartcard
		retVal = io_theOpCtxt.pOParams->pVirtualSmartCard->get_VSM_ProfileName(&varUsername);
		if(retVal != S_OK)
			break;

		retVal = ParseProfile_Path_Name(varUsername.bstrVal,&bstrUserName,&bstrPath,&bstrApContext); 
		if(varUsername.bstrVal)
			SysFreeString(varUsername.bstrVal);
		varUsername.bstrVal = bstrUserName;

		pfnGetUsernamePasswd = (LPFNGetUsernamePasswd)GetProcAddress(m_pAppCtxt->hModAuthDll,"GetUsernamePasswd");
		if(!pfnGetUsernamePasswd)
		{
			retVal = E_GETPROCADDRFAILED;
			break;
		}

		pfnProcessEvent = (LPFNProcessEvent)GetProcAddress(m_pAppCtxt->hModAuthDll,"ProcessEvent");
		if(!pfnProcessEvent)
		{
			retVal = E_GETPROCADDRFAILED;
			break;
		}

		retVal = pfnGetUsernamePasswd(&varPurpose, &varAppCtxt, &varPasswordQuality, &varUsername, &varPasswd, &varOrigPasswd);
		if(retVal != S_OK)
			break;

		//Obtain the original password
		if(varOrigPasswd.vt == VT_BSTR)
		{
			m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd = varOrigPasswd.bstrVal;
			
		}
		else if(varOrigPasswd.vt == VT_ARRAY)
		{
			PBYTE pbytePasswordHash;
			long lLBound;
			long lUBound;
			long lSize;

			if(SafeArrayGetDim(varOrigPasswd.parray) != 1)
			{
				retVal = E_AUTHDLL_INVALIDDIMS;
				break;
			}
			
			retVal = SafeArrayGetLBound(varOrigPasswd.parray, 1,&lLBound);
			if(retVal != S_OK)
				break;
			
			retVal = SafeArrayGetUBound(varOrigPasswd.parray,1, &lUBound);
			if(retVal != S_OK)
				break;

			lSize = lUBound - lLBound + 1;
			retVal = SafeArrayAccessData(varOrigPasswd.parray, (void HUGEP**)&(pbytePasswordHash));
			if(retVal != S_OK)
				break;

			if(!BytesToAscHex(pbytePasswordHash,lSize,m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd))
			{
				retVal = E_FAIL;
				break;
			}
				
			
		}
		else
		{
			retVal = E_INVALIDARGS;
			break;
		}

		
		if(retVal != S_OK)
				break;

		//Obtain the new password
		if(varPasswd.vt == VT_BSTR)
		{
			m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = varPasswd.bstrVal;
			
		}
		else if(varPasswd.vt == VT_ARRAY)
		{
			PBYTE pbytePasswordHash;
			long lLBound;
			long lUBound;
			long lSize;

			if(SafeArrayGetDim(varPasswd.parray) != 1)
			{
				retVal = E_AUTHDLL_INVALIDDIMS;
				break;
			}
			
			retVal = SafeArrayGetLBound(varPasswd.parray, 1,&lLBound);
			if(retVal != S_OK)
				break;
			
			retVal = SafeArrayGetUBound(varPasswd.parray,1, &lUBound);
			if(retVal != S_OK)
				break;

			lSize = lUBound - lLBound + 1;
			retVal = SafeArrayAccessData(varPasswd.parray, (void HUGEP**)&(pbytePasswordHash));
			if(retVal != S_OK)
				break;

			if(!BytesToAscHex(pbytePasswordHash,lSize,m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd))
			{
				retVal = E_FAIL;
				break;
			}
				
			
		}
		else
		{
			retVal = E_INVALIDARGS;
			break;
		}

		if(retVal != S_OK)
				break;

		m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd  = m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd ;
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = PASSWDQUAL_OPTIONALPASS;
		m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd = TRUE;
	
			
		/*Try to create the profile*/
		retVal = _HandleChangePasswd(io_theOpCtxt.pOParams->pVirtualSmartCard, io_theOpCtxt.boolOpenedWithPassword);
	
		VARIANT varEvent;
		varEvent.vt = VT_I2;

		switch(retVal)
		{
		case E_INVALIDPASSWD_PASSWDREQD :
			//We need to show the ui because we need a password
			//io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			*o_pboolParamFlagsChanged = TRUE;
			retVal = S_OK;
			break;		

		case E_INVALIDPASSWD :
			//retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			//io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			varEvent.iVal = retVal & 0x0000FFFF;
			retVal = pfnProcessEvent(&varEvent);
			*o_pboolParamFlagsChanged = TRUE;
			retVal = S_OK;
		
			break;

		case E_PROFLOCKEDOUT :
			//if(io_theOpCtxt.boolFromUI)
			//{
			//	retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			//	io_theOpCtxt.nWizardAndUIs |= CHANGEPASSWD_BASE;
			//}
			varEvent.iVal = retVal & 0x0000FFFF;
			retVal = pfnProcessEvent(&varEvent);
			*o_pboolParamFlagsChanged = TRUE;
			retVal = S_OK;

			break;

		default :
			break;

		}

		if(retVal != S_OK)
			break;
				
	}while(0);

	m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = varPasswordQuality.iVal;

	
	if(varUsername.bstrVal)
	{
		SysFreeString(varUsername.bstrVal);
	}

	if(varOrigPasswd.vt == VT_BSTR && varOrigPasswd.bstrVal)
	{
		SysFreeString(varOrigPasswd.bstrVal);
	}

	if(varOrigPasswd.vt == VT_ARRAY && varOrigPasswd.parray)
	{
		SafeArrayDestroy(varOrigPasswd.parray);
	}
	
	if(varPasswd.vt == VT_BSTR && varPasswd.bstrVal)
	{
		SysFreeString(varPasswd.bstrVal);
	}

	if(varPasswd.vt == VT_ARRAY && varPasswd.parray)
	{
		SafeArrayDestroy(varPasswd.parray);
	}
	
	if(varAppCtxt.bstrVal)
	{
		SysFreeString(varAppCtxt.bstrVal);
	}

	if(bstrUserName )
	{
		SysFreeString(bstrUserName );
	}

	if(bstrPath)
	{
		SysFreeString(bstrPath);
	}

	if(bstrApContext)
	{
		SysFreeString(bstrApContext);
	}
	
		
	return retVal;
}

HRESULT CVSPTA::_ShowOrImportP12(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	
	//Make sure that a smart card is open
	if(io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
	{
		/*Decode the pkcs12 and obtain the keys and a list of certs to install*/		
		retVal = m_pPtaEngine->DecodePKCS12_GetPrivKeyAndCerts(m_pAppCtxt->theImportP12Params.nKeyFileOrBlob,
			m_pAppCtxt->theImportP12Params.tbstrKeyFileOrBlob,
			m_pAppCtxt->theImportP12Params.tbstrP12Passwd,
			&(io_theOpCtxt.pbytePrivKeyBlob),
			&(io_theOpCtxt.dwPrivKeyBlobSize),
			&(io_theOpCtxt.pCertListHead));

		if(retVal == E_INVALIDPASSWD)
		{
			//The password is invalid. If we are coming from the ui then give the 
			//user some feedback and try again.
			if(m_pAppCtxt->theImportP12Params.tbstrP12Passwd.length() != 0)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			}
			retVal = S_OK;
		}		
		
	}
	else if(!io_theOpCtxt.pOParams->pVirtualSmartCard && !(m_pAppCtxt->nIsCapi))
	{
		//Smart card is not open we need to come back later
		io_theOpCtxt.nWizardAndUIs |= IMPORTP12_BASE;	
	}


	if(retVal == S_OK && io_theOpCtxt.pbytePrivKeyBlob && io_theOpCtxt.pCertListHead)
	{
		/*Obtain the public key identifier from the public key*/
		retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(
				(io_theOpCtxt.pCertListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo),
				NULL,&io_theOpCtxt.dwPublicKeyIdSize);
		if(retVal == S_OK)
		{
			io_theOpCtxt.pbytePublicKeyId = new BYTE[io_theOpCtxt.dwPublicKeyIdSize];
			if(!io_theOpCtxt.pbytePublicKeyId)
				retVal = E_FAIL;
			else
			{
				retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(
							io_theOpCtxt.pCertListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo,
							io_theOpCtxt.pbytePublicKeyId ,&io_theOpCtxt.dwPublicKeyIdSize );
			}
		}

		/* Store Public Key Identifier in the profile */
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->ImportPublicKey(
						io_theOpCtxt.pCertListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo,
						io_theOpCtxt.pOParams->pVirtualSmartCard );
			
		}


		/*Install the private key*/
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->InstallPrivKey(io_theOpCtxt.pOParams->pVirtualSmartCard,
						io_theOpCtxt.pbytePrivKeyBlob, io_theOpCtxt.dwPrivKeyBlobSize, io_theOpCtxt.pbytePublicKeyId);
			
		}

		/*Install the certificate*/
		unsigned int nCertNum = 0xffffffff;
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->InstallCerts(io_theOpCtxt.pOParams->pVirtualSmartCard,
				io_theOpCtxt.pCertListHead, &nCertNum);
		}

		/*Make this installation capi compliant*/
		if(retVal == S_OK)
		{
			/*First delete the certificate entry from the registry because in MakeCAPICompliantCertInstall()
			  we do not install an already existing cert*/
			retVal = m_pPtaEngine->DeleteCertFromCAPI(io_theOpCtxt.pCertListHead);

			if(retVal == S_OK && m_pAppCtxt->boolCapiCert)
				retVal = m_pPtaEngine->MakeCapiCompliantCertInstall(io_theOpCtxt.pOParams->pVirtualSmartCard,
					io_theOpCtxt.pCertListHead, io_theOpCtxt.pbytePublicKeyId,
					io_theOpCtxt.dwPublicKeyIdSize,(BYTE)(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&KEYTYPE_BASE),
					((BOOL)(!(m_pAppCtxt->theInstallCertParams.dwKeyGenFlags&EXPORTABLE_BASE))), m_pAppCtxt->theOpenProfParams.boolRoamProfile,
					m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, nCertNum, _bstr_t(""));
		}

		/*Set the selected id issuerdn and serial numbers to that of the current id*/
		m_pAppCtxt->theImportP12Params.tbstrSerNum = io_theOpCtxt.pCertListHead->pDecCertInfo->tbstrSerNum;
		m_pAppCtxt->theImportP12Params.tbstrIssDN = io_theOpCtxt.pCertListHead->pDecCertInfo->tbstrIssuerDN;

	}
	else if (retVal == S_OK)
	{
		io_theOpCtxt.nWizardAndUIs |= IMPORTP12_BASE;
	}


	return retVal;
}

HRESULT CVSPTA::_ShowOrExportP12(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";
	_bstr_t tbstrPathName = "";
	WIN32_FIND_DATA findData;
	HANDLE hFindFile = NULL;
	
	
	do
	{

		//Make sure that an id is selected
		if(!io_theOpCtxt.pOParams->pSelectedId)
		{
			//ID has not been selected - we need to come back later
			io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;	
			break;
		}

		//Check if the password and the confirm password match
		if(m_pAppCtxt->theExportP12Params.tbstrP12Passwd != m_pAppCtxt->theExportP12Params.tbstrP12ConfPasswd)
		{
			m_pPtaUI->ShowMessage(E_CONFIRMPASSWORDNOMATCH & 0x0000FFFF);
			m_pAppCtxt->theExportP12Params.tbstrP12ConfPasswd = "";
			io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
			break;
		}

		/*An id has been selected - now find out if we have the filename and the password (the password may be empty)*/
		if(m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob.length() == 0 || (m_pAppCtxt->theExportP12Params.tbstrP12Passwd.length() == 0 && !m_pAppCtxt->theExportP12Params.boolUsePasswd))
		{
			//We dont have the filename or we dont have the password - come back
			io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;	
			break;
		}

		GetPathFromFileName(m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob, &tbstrPathName);

		/*Check if the specified path for the file is valid*/
		if(!IsValidPath(m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob))
		{
			m_pPtaUI->ShowMessage(INVALID_PATH);
			io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
			m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob = "";
			break;
		}

		/*Check if the specified path for the file exists*/
		if(tbstrPathName.length() > 2)	// not a root dir
		{
			if((hFindFile = FindFirstFile((LPCTSTR)tbstrPathName, &findData)) == INVALID_HANDLE_VALUE)
			{
				if(m_pPtaUI->ConfirmAction(PATH_DOESNOT_EXIST) != S_OK)
				{
					//Donot create a new path
					io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
					m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob = "";
					break;
				}
			}
			if(hFindFile)
				FindClose(hFindFile);
			hFindFile = NULL;
		}
		
		/*Make sure that the file does not exist*/
		if((hFindFile = FindFirstFile((LPCTSTR)m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob, &findData)) != INVALID_HANDLE_VALUE)
		{
			//File Exists - we cannot overwrite
			m_pPtaUI->ShowMessage(FILE_EXISTS);
			m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob = "";
			io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
			break;
		}

		//Check if the password matches the sanity criteria
		int nTempQuality;
		int nTempLength;
		nTempQuality = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality;
		nTempLength = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength;
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = m_pAppCtxt->theExportP12Params.nPasswordQuality;
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength = m_pAppCtxt->theExportP12Params.nPasswordLength;
		retVal = _CheckPasswordSanity(m_pAppCtxt->theExportP12Params.tbstrP12Passwd);
		switch(retVal)
		{
			case E_INVALIDPASSWD_PASSWDREQD :
				//We need to show the ui because we need a password
				io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
				break;

			case E_INVALIDPASSWD_NOPASSWDREQD :
			case E_INVALIDPASSWD_LESSTHANMINLENGTH :
			case E_INVALIDPASSWD_NOTNUMERICONLY :
			case E_INVALIDPASSWD_INVALIDCHARS :
			case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
			case E_INVALIDPASSWD_NONUMATBEGIN :
			case E_INVALIDPASSWD_NONUMATEND :
				if(io_theOpCtxt.boolFromUI)
				{
					m_pAppCtxt->theExportP12Params.tbstrP12Passwd = "";
					m_pAppCtxt->theExportP12Params.tbstrP12ConfPasswd  = "";

					  // Use a new variable to store return values in this case statement 
					  // so that it doesn't	change the original return value
					HRESULT retValNew = S_OK;
				
					//Create the string to be displayed 
					retValNew = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
					if(retValNew == S_OK)
					{
						tbstrMessageToDisplay = wstrTemp;
					}

					if(retValNew == S_OK)
					{
						retValNew = _GetPasswdQualityString(&tbstrPasswdQualString);
					}

					if(retValNew == S_OK)
					{
						tbstrMessageToDisplay += tbstrPasswdQualString;

						//Display it.
						VARIANT varMsgToDisplay;
						varMsgToDisplay.vt = VT_BSTR;
						varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

						retValNew = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
					}

					if(retValNew == S_OK)
					{
						retValNew = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
						io_theOpCtxt.nWizardAndUIs |= EXPORTP12_BASE;
					}
				
					if(retValNew == E_FAIL)
						retVal = E_FAIL;
				}

				break;

			default:
				if(retVal != S_OK)
					retVal = E_FAIL;
			
		}
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = nTempQuality;
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength = nTempLength;
		
		if(retVal != S_OK)
		{
			if(retVal != E_FAIL)
				retVal = S_OK;
			break;
		}

		//We have all the information needed. Tell the engine to export the p12
		retVal = m_pPtaEngine->ExportP12(io_theOpCtxt.pOParams->pVirtualSmartCard,m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob,m_pAppCtxt->theExportP12Params.tbstrP12Passwd,io_theOpCtxt.pOParams->pSelectedId); 
		if(retVal != S_OK)
			break;
			
		
	}while(0);

	if(hFindFile)
		FindClose(hFindFile);

	return retVal;
}

HRESULT CVSPTA::_InitializeUIContext(PUICTXT io_pUICtxt, int i_nWhichWizardAndUIs, int i_nOperation, _bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles, PIDLISTNODE i_pCertListHead, int i_nSelectedIdNum, BOOL i_boolOpenedWithPassword)
{
	HRESULT retVal;
	int pos;

	io_pUICtxt->nWhichWizardAndUI = (i_nWhichWizardAndUIs & (WIZARD_BITS | i_nOperation));
	if(!(i_nWhichWizardAndUIs & IMPORTP12_WIZARD_BASE) && (i_nOperation & INTRO_BASE || i_nOperation & CREATE_BASE || i_nOperation & CREATESECRET_BASE)) //For the intro screen and the create screen we use the create wizard
	{
		io_pUICtxt->nWhichWizardAndUI &= (OPERATION_BITS | FLAG_BITS);
		io_pUICtxt->nWhichWizardAndUI |= CREATE_WIZARD_BASE;
	}

	
	/*Store the button text and functions*/
	io_pUICtxt->pbtnElems = new (BTNELEMS);
	io_pUICtxt->pbtnFns = new(BTNFNS);
	
	//Get the position of this ui in the wizard
	pos = _GetOperationPosInWizard(i_nOperation,(i_nWhichWizardAndUIs & OPERATION_BITS));
	if(pos == POS_UNKNOWN)
		return E_OPERATIONPOSUNKNOWN;

	retVal = _GetButtonTextAndFns(io_pUICtxt->pbtnElems, io_pUICtxt->pbtnFns, i_nOperation, pos); 
	if(retVal != S_OK)
		return retVal;

	/*Set the font information*/
	if((io_pUICtxt->pfontInfoCustomFonts = _CreateFontStruct(FONTS_CUSTOM)) == NULL)
	{
		return E_FAIL;
	}

	if((io_pUICtxt->pfontInfoDefaultFonts = _CreateFontStruct(FONTS_DEFAULT)) == NULL)
	{
		return E_FAIL;
	}
	
	/*Set the logo urls*/
	io_pUICtxt->tbstrDefLogoUrl = m_pAppCtxt->theDefUIPrefs.tbstrUILogoUrl;
	io_pUICtxt->tbstrCustLogoUrl = m_pAppCtxt->theUIPrefs.tbstrUILogoUrl;
	io_pUICtxt->tbstrDefAffLogoUrl = m_pAppCtxt->theDefUIPrefs.tbstrAffLogoUrl;
	io_pUICtxt->tbstrCustAffLogoUrl = m_pAppCtxt->theUIPrefs.tbstrAffLogoUrl;

	/*Set the wizard information*/
	retVal = _SetWizardElems((io_pUICtxt->nWhichWizardAndUI & WIZARD_BITS), &(io_pUICtxt->pvWizardElems));
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	/*Set the ui elements*/
	retVal = _SetUIElems((i_nOperation & (OPERATION_BITS|FLAG_BITS)), &(io_pUICtxt->pvUIElements), i_ptbstrProfiles, i_nNumOfProfiles, i_pCertListHead, i_nSelectedIdNum, i_boolOpenedWithPassword);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Set the default language*/
	io_pUICtxt->nDefLangId = m_pAppCtxt->theDefUIPrefs.wLangID;

	// Set the window position
	io_pUICtxt->bShowTopMost = m_pAppCtxt->theUIPrefs.boolShowTopMost;
	return retVal;

}


int CVSPTA::_GetOperationPosInWizard(int nOperation, int nOperationsInWizard)
{
	switch(nOperation & (OPERATION_BITS|FLAG_BITS))
	{
	case OPENPROF_CREATE_BASE :
		if(nOperationsInWizard & IMPORTP12_BASE)
			return POS_MIDDLE_PREV_INTRO;
		if(nOperationsInWizard & INTRO_BASE)
			return POS_LAST_PREV_INTRO;
		return POS_SOLO;
		break;

	case OPENPROF_OPEN_BASE :
		//Can only be the first or solo
		if(nOperationsInWizard & SELID_BASE && m_pAppCtxt->boolShowSelIDUI)
		{
			return POS_FIRST;
		}
		if(nOperationsInWizard & CHANGEPASSWD_BASE)
  		{
  			return POS_FIRST;
  		}
		if(nOperationsInWizard & IMPORTP12_BASE)
		{
			return POS_FIRST;
		}
		if(nOperationsInWizard & EXPORTP12_BASE)
		{
			return POS_FIRST;
		}
		if(nOperationsInWizard & EXPORTPROFILE_BASE)
		{
			return POS_FIRST;
		}
		return POS_SOLO;
		break;

	case CREATEPASSWD_BASE :
		return POS_SOLO;

	case ENTERPASSWD_BASE :
		return POS_SOLO;

	case CHANGEPASSWD_BASE :
		if(nOperationsInWizard & OPENPROF_BASE)
		{
			if(m_pAppCtxt->theOpenProfParams.nFlag & OPEN_BASE)
				return POS_LAST_PREV_OPEN;
			else
				return POS_LAST_PREV_CREATE;
		}
		return POS_SOLO;
		break;

	case SELID_BASE :
		if(nOperationsInWizard & SIGNMSG_BASE || nOperationsInWizard & EXPORTP12_BASE)
		{
			if((nOperationsInWizard & OPENPROF_BASE))
			{
				if(m_pAppCtxt->theOpenProfParams.nFlag & OPEN_BASE)
					return POS_MIDDLE_PREV_OPEN; //In the middle - open profile is the previous one
				else if(m_pAppCtxt->theOpenProfParams.nFlag & CREATE_BASE)
					return POS_MIDDLE_PREV_CREATE;
			}	
			
			return POS_FIRST;
		}
		
		//Sign message ui or export ui is not in the wizard - so the select can be
		//the last one or solo
		if(nOperationsInWizard & OPENPROF_BASE)
		{
			if(m_pAppCtxt->theOpenProfParams.nFlag & OPEN_BASE)
				return POS_LAST_PREV_OPEN; //In the middle - open profile is the previous one
			else if(m_pAppCtxt->theOpenProfParams.nFlag & CREATE_BASE)
				return POS_LAST_PREV_CREATE;
		}
		
		return POS_SOLO;
		break;

	case SIGNMSG_BASE :
		//Can only be the last or solo
		if(nOperationsInWizard & SELID_BASE )
			return POS_LAST_PREV_SEL;
		else if(nOperationsInWizard & OPENPROF_BASE)
			return POS_LAST_PREV_OPEN;
		return POS_SOLO;

	case INTRO_BASE :
		return POS_FIRST;

	case IMPORTP12_BASE :
		if(nOperationsInWizard & OPENPROF_BASE)
		{
			if(m_pAppCtxt->theOpenProfParams.nFlag & OPEN_BASE)
				return POS_LAST_PREV_OPEN;
			else
				return POS_LAST_PREV_CREATE;
		}
		return POS_SOLO;
		break;

	case EXPORTP12_BASE :
		if(nOperationsInWizard & SELID_BASE)
		{
			return POS_LAST_PREV_SEL;
		}
		return POS_SOLO;
		break;

	case GETSECRETQUESTION_BASE :
		//Can only be the first or solo
		if(nOperationsInWizard & RESETPASSWD_BASE)
  		{
  			return POS_FIRST;
  		}
		return POS_SOLO;
		break;

	case RESETPASSWD_BASE :
		if(nOperationsInWizard & GETSECRETQUESTION_BASE)
		{
			return POS_LAST_PREV_GETSECRETQUESTION;
		}
		return POS_SOLO;
		break;

	case CREATESECRET_BASE :
		return POS_LAST_PREV_CREATE;
		break;

	default:
		return POS_UNKNOWN;
	}

	return POS_UNKNOWN;
}

HRESULT CVSPTA::_GetButtonTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPos)
{
	WORD wLangId;
	WCHAR* pwszOutBuff;
	HRESULT retVal;

	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);
	wLangId = m_pAppCtxt->theDefUIPrefs.wLangID ;

	switch(i_nPos)
	{
	case POS_FIRST :
		retVal = _GetPosFirstBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, pwszOutBuff, wLangId);
		break;

	case POS_SOLO :
		retVal = _GetPosSoloBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, pwszOutBuff, wLangId);
		break;

	case POS_MIDDLE_PREV_OPEN :
		retVal = _GetPosMiddleBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, OPENPROF_OPEN_BASE, pwszOutBuff, wLangId);
		break;

	case POS_MIDDLE_PREV_CREATE :
		retVal = _GetPosMiddleBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, OPENPROF_CREATE_BASE, pwszOutBuff, wLangId);
		break;

	case POS_MIDDLE_PREV_INTRO :
		retVal = _GetPosMiddleBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, INTRO_BASE, pwszOutBuff, wLangId);
		break;

	case POS_LAST_PREV_SEL :
		retVal = _GetPosLastBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, SELID_BASE,pwszOutBuff, wLangId);
		break;

	case POS_LAST_PREV_INTRO:
		retVal = _GetPosLastBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, INTRO_BASE,pwszOutBuff, wLangId);
		break;

	case POS_LAST_PREV_CREATE :
		retVal = _GetPosLastBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, OPENPROF_CREATE_BASE, pwszOutBuff, wLangId);
		break;

	case POS_LAST_PREV_OPEN :
		retVal = _GetPosLastBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, OPENPROF_OPEN_BASE, pwszOutBuff, wLangId);
		break;

	case POS_LAST_PREV_GETSECRETQUESTION :
		retVal = _GetPosLastBtnTextAndFns(o_pBtnElems,o_pBtnFns,i_nOperation, GETSECRETQUESTION_BASE, pwszOutBuff, wLangId);
		break;

	}

	free(pwszOutBuff);
	return retVal;
}

HRESULT CVSPTA::_GetPosFirstBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, WCHAR* i_pwszBuff, WORD i_wLangId)
{
	HRESULT retVal;
	int i_nBtn1TextId;
	int i_nBtn2TextId;
	int i_nBtn3TextId;

	switch(i_nOperation & (OPERATION_BITS | FLAG_BITS))
	{
		case OPENPROF_OPEN_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = OpenProfOpenFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case OPENPROF_CREATE_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = OpenProfCreateFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case SELID_BASE :
			if(i_nOperation & LOGIN_WIZARD_BASE)
			{
				if(m_pAppCtxt->theUIPrefs.nSelID_OKBtnText)
					i_nBtn1TextId = m_pAppCtxt->theUIPrefs.nSelID_OKBtnText;
				else
					i_nBtn1TextId = IDS_LOGIN;

				if(m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText)
					i_nBtn2TextId = m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText;
				else
					i_nBtn2TextId = m_pAppCtxt->theDefUIPrefs.nSelID_CancelBtnText;

				i_nBtn3TextId = IDS_HELP;
				o_pBtnFns->lpfnBtn1Fn = SelIdFn;
				o_pBtnFns->lpfnBtn2Fn = CancelFn;
				o_pBtnFns->lpfnBtn3Fn = SelIdHelpFn;
			}
			else
			{
				i_nBtn1TextId = IDS_PREV;
				i_nBtn2TextId = IDS_NEXT;
				i_nBtn3TextId = IDS_CANCEL;
				o_pBtnFns->lpfnBtn1Fn = NULL;
				o_pBtnFns->lpfnBtn2Fn = SelIdFn;
				o_pBtnFns->lpfnBtn3Fn = CancelFn;
			}
						
			break;

		case INTRO_BASE:
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = IntroFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case IMPORTP12_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = ImportP12Fn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;
		
		case EXPORTP12_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = ExportP12Fn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case EXPORTPROFILE_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = ExportProfileFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case IMPORTPROFILE_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			o_pBtnFns->lpfnBtn2Fn = ImportProfileFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		case GETSECRETQUESTION_BASE :
			i_nBtn1TextId = IDS_PREV;
			i_nBtn2TextId = IDS_NEXT;
			i_nBtn3TextId = IDS_CANCEL;
			o_pBtnFns->lpfnBtn1Fn = NULL;	// previous button is disabled
			o_pBtnFns->lpfnBtn2Fn = GetSecretQuestionFn;
			o_pBtnFns->lpfnBtn3Fn = CancelFn;
			break;

		default :
			retVal = E_INVALIDFLAGS;
	}
	
	//Load the text for the first button
	retVal = _LoadStringW(_Module.m_hInst,i_wLangId,i_nBtn1TextId,i_pwszBuff,MAX_RES_STRING_SIZE);
	if(retVal == S_OK)
	{
		//Set the text and fn for the first button
		o_pBtnElems->tbstrBtn1Text = i_pwszBuff;
		
		//Load the text for the second button
		retVal = _LoadStringW(_Module.m_hInst,i_wLangId,i_nBtn2TextId,i_pwszBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			//Set the text and the functions for the second button
			o_pBtnElems->tbstrBtn2Text = i_pwszBuff;
		
			if(retVal == S_OK)
			{
				//Load the text for the second button.
				retVal = _LoadStringW(_Module.m_hInst,i_wLangId,i_nBtn3TextId,i_pwszBuff,MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					//Set the text and function for the second button.
					o_pBtnElems->tbstrBtn3Text = i_pwszBuff;
				}
			}
		}
	}


	return retVal;
}

HRESULT CVSPTA::_GetPosSoloBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, WCHAR* i_pwszBuff, WORD i_wLangId)
{
	HRESULT retVal;

	//Depending upon the operation determine the string ids for the
	//ok and cancel buttons and set the function pointers for the
	//ok and help functions
	int nOkBtnTextId, nCancelBtnTextId;
	switch(i_nOperation & (OPERATION_BITS | FLAG_BITS))
	{
	case OPENPROF_CREATE_BASE :
		if(m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nNewPasswd_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nNewPasswd_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nNewPasswd_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nNewPasswd_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = OpenProfCreateFn;
			
		o_pBtnFns->lpfnBtn3Fn = OpenProfCreateHelpFn;

		break;

	case CREATEPASSWD_BASE :
		if(m_pAppCtxt->theUIPrefs.nCreatePasswd_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nCreatePasswd_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nCreatePasswd_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nCreatePasswd_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nCreatePasswd_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nCreatePasswd_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = CreatePasswdFn;
			
		// o_pBtnFns->lpfnBtn3Fn = CreatePasswdHelpFn;
		o_pBtnFns->lpfnBtn3Fn = NULL; // assign the function once after it is implemented

		break;

	case ENTERPASSWD_BASE :
		if(m_pAppCtxt->theUIPrefs.nEnterPasswd_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nEnterPasswd_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nEnterPasswd_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nEnterPasswd_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nEnterPasswd_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nEnterPasswd_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = EnterPasswdFn;
			
		// o_pBtnFns->lpfnBtn3Fn = CreatePasswdHelpFn;
		o_pBtnFns->lpfnBtn3Fn = NULL; // assign the function once after it is implemented

		break;

	case CHANGEPASSWD_BASE :
		if(m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nChangePasswd_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nChangePasswd_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nChangePasswd_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nChangePasswd_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = ChngPasswdFn;
			
		o_pBtnFns->lpfnBtn3Fn = ChngPasswdHelpFn;

		break;

	case OPENPROF_OPEN_BASE :
		if(m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nOpenProf_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nNewPasswd_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nOpenProf_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nOpenProf_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = OpenProfOpenFn;
			
		o_pBtnFns->lpfnBtn3Fn = OpenProfOpenHelpFn;
		break;

	case SELID_BASE :
		if(m_pAppCtxt->theUIPrefs.nSelID_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nSelID_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nSelID_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nSelID_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nSelID_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = SelIdFn;

		o_pBtnFns->lpfnBtn3Fn = SelIdHelpFn;
		
		
		break;

	case SIGNMSG_BASE :
		if(m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nRvwMsg_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nRvwMsg_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nRvwMsg_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nRvwMsg_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = SignMsgFn;

		o_pBtnFns->lpfnBtn3Fn = SignMsgHelpFn;

		break;

	case IMPORTP12_BASE :
		if(m_pAppCtxt->theUIPrefs.nImpP12_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nImpP12_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nImpP12_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nImpP12_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nImpP12_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nImpP12_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = ImportP12Fn;

		o_pBtnFns->lpfnBtn3Fn = ImportP12HelpFn;

		break;

	case EXPORTP12_BASE :
		if(m_pAppCtxt->theUIPrefs.nExpP12_OKBtnText)
			nOkBtnTextId = m_pAppCtxt->theUIPrefs.nExpP12_OKBtnText;
		else
			nOkBtnTextId = m_pAppCtxt->theDefUIPrefs.nExpP12_OKBtnText;

		if(m_pAppCtxt->theUIPrefs.nExpP12_CancelBtnText)
			nCancelBtnTextId = m_pAppCtxt->theUIPrefs.nExpP12_CancelBtnText;
		else
			nCancelBtnTextId = m_pAppCtxt->theDefUIPrefs.nExpP12_CancelBtnText;

		o_pBtnFns->lpfnBtn1Fn = ExportP12Fn;

		o_pBtnFns->lpfnBtn3Fn = ExportP12HelpFn;

		break;

	default :
		return E_INVALIDFLAGS;

	
	}

	//Set the text of the ok button
	retVal = _LoadStringW(_Module.m_hInst,i_wLangId,nOkBtnTextId,i_pwszBuff,MAX_RES_STRING_SIZE);
	if(retVal == S_OK)
	{
		o_pBtnElems->tbstrBtn1Text = i_pwszBuff;

		//Set the text and function of the cancel button
		retVal = _LoadStringW(_Module.m_hInst,i_wLangId,nCancelBtnTextId,i_pwszBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			o_pBtnElems->tbstrBtn2Text = i_pwszBuff;
			o_pBtnFns->lpfnBtn2Fn = CancelFn;

			//Set the text for the help button
			// XXX 
			retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_HELP,i_pwszBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				o_pBtnElems->tbstrBtn3Text = i_pwszBuff;
			}
		}
	}

	return retVal;
}


HRESULT CVSPTA::_GetPosMiddleBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPrevOp, WCHAR* i_pwszBuff, WORD i_wLangId)
{
	HRESULT retVal;

	//Load the text for the first button
	retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_PREV,i_pwszBuff,MAX_RES_STRING_SIZE);
	if(retVal == S_OK)
	{
		//Set the text and fn for the first button
		o_pBtnElems->tbstrBtn1Text = i_pwszBuff;
		switch(i_nPrevOp & (OPERATION_BITS | FLAG_BITS))
		{
		case OPENPROF_CREATE_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToCreateFn;
			break;

		case OPENPROF_OPEN_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToOpenFn;
			break;

		case INTRO_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToIntroFn;
			break;

		case GETSECRETQUESTION_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToGetSecretQuestionFn;
			break;
		default :
			return E_INVALIDFLAGS;

		}

		//Load the text for the second button
		if((i_nOperation & SELID_BASE) && (i_nOperation & LOGIN_WIZARD_BASE))
		{
			if(m_pAppCtxt->theUIPrefs.nSelID_OKBtnText)
				retVal = _LoadStringW(_Module.m_hInst,i_wLangId,m_pAppCtxt->theUIPrefs.nSelID_OKBtnText,i_pwszBuff,MAX_RES_STRING_SIZE);
			else
				retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_LOGIN,i_pwszBuff,MAX_RES_STRING_SIZE);
		}
		else
		{
			retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_NEXT,i_pwszBuff,MAX_RES_STRING_SIZE);
		}

		if(retVal == S_OK)
		{
			//Set the text and the functions for the second button
			o_pBtnElems->tbstrBtn2Text = i_pwszBuff;
			if((i_nPrevOp & (OPERATION_BITS | FLAG_BITS)) == INTRO_BASE)
				o_pBtnFns->lpfnBtn2Fn = OpenProfCreateFn;
			else
				o_pBtnFns->lpfnBtn2Fn = SelIdFn;

			if(retVal == S_OK)
			{
				//Load the text for the third button.
				retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_CANCEL,i_pwszBuff,MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					//Set the text and function for the second button.
					o_pBtnElems->tbstrBtn3Text = i_pwszBuff;
					o_pBtnFns->lpfnBtn3Fn = CancelFn;
				}
			}
		}
	}

	return retVal;
	
}

HRESULT CVSPTA::_GetPosLastBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPrevOp, WCHAR* i_pwszBuff, WORD i_wLangId)
{
	HRESULT retVal;

	//Load the text for the first button
	retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_PREV,i_pwszBuff,MAX_RES_STRING_SIZE);
	if(retVal == S_OK)
	{
		//Set the text and fn for the first button
		o_pBtnElems->tbstrBtn1Text = i_pwszBuff;
		switch(i_nPrevOp)
		{
		case OPENPROF_CREATE_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToCreateFn;
			break;

		case OPENPROF_OPEN_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToOpenFn;
			break;

		case SELID_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToSelIdFn;
			break;

		case INTRO_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToIntroFn;
			break;

		case GETSECRETQUESTION_BASE :
			o_pBtnFns->lpfnBtn1Fn = PrevToGetSecretQuestionFn;
			break;

		default :
			return E_INVALIDFLAGS;

		}

		//Load the text id for the second button and the set the
		//functions for the second and the third button.
		int nBtnTextId;
		switch(i_nOperation & (OPERATION_BITS | FLAG_BITS))
		{
		case SELID_BASE :
			if(m_pAppCtxt->theUIPrefs.nSelID_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nSelID_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nSelID_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = SelIdFn;
			break;

		case SIGNMSG_BASE :
			if(m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nRvwMsg_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nRvwMsg_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = SignMsgFn;
			break;

		case OPENPROF_CREATE_BASE :
			if(m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nNewPasswd_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = OpenProfCreateFn;
			break;

		case CHANGEPASSWD_BASE :
			if(m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nChangePasswd_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nChangePasswd_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = ChngPasswdFn;
			break;

		case IMPORTP12_BASE :
			if(m_pAppCtxt->theUIPrefs.nImpP12_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nImpP12_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nImpP12_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = ImportP12Fn;
			break;

		case EXPORTP12_BASE :
			if(m_pAppCtxt->theUIPrefs.nExpP12_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nExpP12_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nExpP12_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = ExportP12Fn;
			break;

		case GETSECRETQUESTION_BASE :
			if(m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nNewPasswd_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nNewPasswd_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = GetSecretQuestionFn;
			break;

		case RESETPASSWD_BASE :
			if(m_pAppCtxt->theUIPrefs.nResetPasswd_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nResetPasswd_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nResetPasswd_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = ResetPasswdFn;
			break;

		case CREATESECRET_BASE :
			if(m_pAppCtxt->theUIPrefs.nCreateSecret_OKBtnText)
				nBtnTextId = m_pAppCtxt->theUIPrefs.nCreateSecret_OKBtnText;
			else
				nBtnTextId = m_pAppCtxt->theDefUIPrefs.nCreateSecret_OKBtnText;
			o_pBtnFns->lpfnBtn2Fn = CreateSecretFn;
			o_pBtnFns->lpfnBtn1Fn = NULL;
			break;

		default :
			return E_INVALIDARGS;

		}
		
		//Set the strings for the second and the third button
		retVal = _LoadStringW(_Module.m_hInst,i_wLangId,nBtnTextId,i_pwszBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			//Set the text and the functions for the second button
			o_pBtnElems->tbstrBtn2Text = i_pwszBuff;

			//Load the text for the third button.
			retVal = _LoadStringW(_Module.m_hInst,i_wLangId,IDS_CANCEL,i_pwszBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				//Set the text and function for the second button.
				o_pBtnElems->tbstrBtn3Text = i_pwszBuff;
				o_pBtnFns->lpfnBtn3Fn = CancelFn;
			}
	
		}
	}

	return retVal;

}


HRESULT CVSPTA::_HandleCreateProfile(_bstr_t** io_pptbstrProfiles, int* io_npNumOfProfiles, CVirtualSmartCard** o_ppVirtualSmartCard)
{

	HRESULT retVal = S_OK;

	/*Make sure that the profile is not in the list of profiles, otherwise return profile exists*/
	for(int i=0; i<(*io_npNumOfProfiles); ++i)
	{
		if((*io_pptbstrProfiles)[i] == m_pAppCtxt->theOpenProfParams.tbstrProfName)
			return E_PROFEXISTS;
	}

	// Change the OK button to next if we are creating a roaming profile and need to specify secret question and answer
	if(m_pAppCtxt->theOpenProfParams.boolRoamProfile)
	{
		// Check if roaming server information has been changed. If it is changed, then we need
		// to query the roaming server again to see if the server supports reset password feature
		// We will do this query only when roaming info is changed (or set at the first time)
		if(m_pAppCtxt->theRoamingParams.boolRoamInfoChanged)
		{
			CVirtualSmartCard* pVirtualSmartCard = new CVirtualSmartCard ;
			BOOL	bResetPasswd;

			retVal = pVirtualSmartCard->VSM_IsResetPasswdSupported(m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &bResetPasswd);

			if(retVal == S_OK)
			{
				m_pAppCtxt->theRoamingParams.boolRoamingResetFeature = bResetPasswd;
				m_pAppCtxt->theRoamingParams.boolRoamInfoChanged = FALSE;
			}
			else 
			{
				delete pVirtualSmartCard;
				return retVal;
			}

			delete pVirtualSmartCard;
		}

		// check if password reset feature is supported
		if(m_pAppCtxt->theRoamingParams.boolRoamingResetFeature == TRUE)
			m_pAppCtxt->theDefUIPrefs.nNewPasswd_OKBtnText = IDS_NEXT;

	}

	/*If password is required and the password should not be used return password required*/
	if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality != PASSWDQUAL_REQUIRENOPASS &&
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag == DONOT_USE_PASSWORD)
	{
		return E_INVALIDPASSWD_PASSWDREQD;
	}

	/*If password is not required and this is a roaming configuration, return invalid password requirement
	error*/
	if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS &&
		m_pAppCtxt->theOpenProfParams.boolRoamProfile)
	{
		return E_ROAM_REQDNOPASSWD_INVALID;
	}

	/*If password is not required and the password is set return password not required */
	if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS &&
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag != DONOT_USE_PASSWORD)
	{
		return E_INVALIDPASSWD_NOPASSWDREQD;
	}

	/*We have a profile name and the appropriate passwords*/

	/*Check if the password and confirm passwords are the same*/
	if(m_pAppCtxt->theOpenProfParams.tbstrPassword != m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword)
		return E_CONFIRMPASSWORDNOMATCH;
	
	/*Check the password sanity*/
	retVal = _CheckPasswordSanity(m_pAppCtxt->theOpenProfParams.tbstrPassword);

	// Get the Profile Suffix for creating the profile.
	if (!(m_pAppCtxt->tbstrProfileIssFrndlyName) || 
		 (m_pAppCtxt->tbstrProfileIssFrndlyName == (_bstr_t)""))
	{
		m_pAppCtxt->tbstrProfileIssFrndlyName = m_pAppCtxt->tbstrAppCtxtName;
	}	
	/*Obtain the name of the profile file to be created*/
	_bstr_t tbstrProfileName;
	VARIANT varWhichSmartCard;
	
	if(retVal == S_OK)
	{
		if(!m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		{
//			retVal = m_pPtaEngine->GetProfileFilePathAndName(m_pAppCtxt->tbstrAppCtxtName,m_pAppCtxt->theOpenProfParams.tbstrProfName,&tbstrProfileName);
			retVal = m_pPtaEngine->GetProfileFilePathAndName(m_pAppCtxt->tbstrProfileIssFrndlyName, m_pAppCtxt->theOpenProfParams.tbstrProfName,&tbstrProfileName);
		}
		else
		{

			/*retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrAppCtxtName, m_pAppCtxt->theOpenProfParams.tbstrProfName, 
							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.nNumOfRoamingSrvrs,
							m_pAppCtxt->theRoamingParams.ptbstrRoamingSrvrs, m_pAppCtxt->theRoamingParams.tbstrStorageSrvr, &varWhichSmartCard);*/
			
//			retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrAppCtxtName, m_pAppCtxt->theOpenProfParams.tbstrProfName, 
//							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &varWhichSmartCard);
			retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrProfileIssFrndlyName, m_pAppCtxt->theOpenProfParams.tbstrProfName, 
							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &varWhichSmartCard);

		}
	}


	/*Call the smart card initialize, which will in turn create that profile*/
	CVirtualSmartCard* pVirtualSmartCard = NULL;
	if(retVal == S_OK)
	{

		// Sasi 05/06/03
		// Check if it is roaming or local profile. If it is local then we will create the profile. 
		// Also in case of new roaming that supports password reset feature, we will create the profile 
		// and reserve name with roaming server only first time. In this case, we will store the roaming profile
		// along with secret question and answer later (when profile is saved).
		// The following code will be executed only once if you are using new roaming server
		if (!m_pAppCtxt->theOpenProfParams.boolRoamProfile ||
				!m_pAppCtxt->theOpenProfParams.boolSupportResetPasswd	)			
		{

			pVirtualSmartCard = new CVirtualSmartCard;

			if(!pVirtualSmartCard)
				return E_OUTOFMEMORY;

			
			VARIANT varPassword;
			VARIANT varAppCtxt;
			VARIANT varProfileIssFrndlyName;
			VARIANT varAppHostName;
			VARIANT varPasswdTimeOut;
			VARIANT varPasswdLockoutTries;
			VARIANT varPasswdUnlockPerod;

			if(!m_pAppCtxt->theOpenProfParams.boolRoamProfile)
			{
				varWhichSmartCard.vt = VT_BSTR;
				varWhichSmartCard.bstrVal = tbstrProfileName.copy();
			}

			if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
			{
				varPassword.vt = VT_EMPTY;
			}
			else
			{
				varPassword.vt = VT_BSTR;
				varPassword.bstrVal = m_pAppCtxt->theOpenProfParams.tbstrPassword.copy();
			}

			varAppCtxt.vt = VT_BSTR;
			varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
			varProfileIssFrndlyName.vt = VT_BSTR;
			varProfileIssFrndlyName.bstrVal = m_pAppCtxt->tbstrProfileIssFrndlyName.copy();
			varAppHostName.vt = VT_BSTR;
			varAppHostName.bstrVal = m_pAppCtxt->tbstrHostName.copy();
			varPasswdTimeOut.vt = VT_I2;
			varPasswdTimeOut.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordTimeOut;
			varPasswdLockoutTries.vt = VT_I2;
			varPasswdLockoutTries.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLockOutTries;
			varPasswdUnlockPerod.vt = VT_I2;
			varPasswdUnlockPerod.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordUnlockPeriod;

			retVal = pVirtualSmartCard->VSM_Initialize
				(&varWhichSmartCard,&varPassword,&varAppCtxt,
				 &varProfileIssFrndlyName,&varAppHostName,&varPasswdTimeOut,
				 &varPasswdLockoutTries,&varPasswdUnlockPerod, 
				 PasswordCallback, (void*) this
				);	//	TIMEOUT

			if(varWhichSmartCard.vt == VT_BSTR)
			{
				SysFreeString(varWhichSmartCard.bstrVal);
			}
			if(varPassword.vt == VT_BSTR)
			{
				//Zero the memory before destroying the Text
				if(retVal == S_OK)
				{
					//memset(varPassword.bstrVal, 0, m_pAppCtxt->theOpenProfParams.tbstrPassword.length()*2);
					EraseMemory((unsigned int)m_pAppCtxt->theOpenProfParams.tbstrPassword.length()*2, (unsigned char*)varPassword.bstrVal);
					
				}

				SysFreeString(varPassword.bstrVal);
			}
			SysFreeString(varAppCtxt.bstrVal);
			SysFreeString(varProfileIssFrndlyName.bstrVal);
			SysFreeString(varAppHostName.bstrVal);

			// Sasi 05/06/03
			// check if password reset feature is supported by roaming server. This function needs to be called
			// only after calling VSM_Initialize
			if(retVal == S_OK && m_pAppCtxt->theOpenProfParams.boolRoamProfile)
				retVal = pVirtualSmartCard->get_VSM_ResetPasswordFeature( &m_pAppCtxt->theOpenProfParams.boolSupportResetPasswd);
		}
	}

	if(retVal == S_OK)
	{
		// Return the profile only if it is either local or if the roaming server doesn't support password reset feature
		if( !m_pAppCtxt->theOpenProfParams.boolRoamProfile 
			|| !m_pAppCtxt->theOpenProfParams.boolSupportResetPasswd)
		{

			*o_ppVirtualSmartCard = pVirtualSmartCard;
			//Add this profile name to the list of profile and bump up the
			//num of profiles.
		}
		else 
		{
			if(m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion.length() 
				&& m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer.length())
			{
				// update profile with secret question and answer. This info will be sent to roaming server
				// when the profile is saved.
				m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard->put_VSM_RoamProfSecretQuestion(m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion);
				m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard->put_VSM_RoamProfSecretAnswer(m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer);

				// We got secret question and answer, now we can return the profile.
				*o_ppVirtualSmartCard = m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard;

			}
			else
			{
				// We still need secret question and answer before we can finish the profile creation.
				// Save the profile in global variable since we need to use the same roaming session to store the
				// roaming data at the end.
				if( NULL != pVirtualSmartCard )
				{
					pVirtualSmartCard->put_VSM_RoamProfFirstName(m_pAppCtxt->theOpenProfParams.tbstrFirstName);
					pVirtualSmartCard->put_VSM_RoamProfLastName(m_pAppCtxt->theOpenProfParams.tbstrLastName);
					pVirtualSmartCard->put_VSM_RoamProfEmail(m_pAppCtxt->theOpenProfParams.tbstrEmail);

					m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard = pVirtualSmartCard;
				}

				retVal = E_CREATESECRET;
			}
		}
	}
	else
	{
		delete pVirtualSmartCard;
		//Delete the file that may have been created
		//m_pPtaEngine->
	}

//	VSPTA_CLEAN_TBSTR(tbstrProfileName)

	return retVal;
}

HRESULT CVSPTA::_HandleOpenProfile(_bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles, CVirtualSmartCard** o_ppVirtualSmartCard)
{
	
	HRESULT retVal = S_OK;
	BOOL boolOpenRemote = FALSE;

	/*Make sure that the profile is in the list of profiles, otherwise return profile exists*/
	retVal = E_PROFDOESNOTEXIST;

	for(int i=0; i<i_nNumOfProfiles; ++i)
	{
		if((i_ptbstrProfiles)[i] == m_pAppCtxt->theOpenProfParams.tbstrProfName)
			retVal = S_OK;
	}

	/*If we didnt find a profile, check if roaming is enabled*/
	if(retVal == E_PROFDOESNOTEXIST && m_pAppCtxt->theOpenProfParams.boolRoamProfile)
	{
		if(m_pAppCtxt->theOpenProfParams.tbstrProfName.length())
		{
			retVal = S_OK;
			boolOpenRemote = TRUE;
		}
		
	}

	// Get the Profile Suffix for opening the profile.
	if (!(m_pAppCtxt->tbstrProfileIssFrndlyName) || 
		 (m_pAppCtxt->tbstrProfileIssFrndlyName == (_bstr_t)""))
	{
		m_pAppCtxt->tbstrProfileIssFrndlyName = m_pAppCtxt->tbstrAppCtxtName;
	}

	/*Obtain the name of the profile file to be opened*/
	_bstr_t tbstrProfileName;
	VARIANT varWhichSmartCard;
	if(retVal == S_OK)
	{
		if(!boolOpenRemote)
		{
			retVal = m_pPtaEngine->GetProfileFilePathAndName(m_pAppCtxt->tbstrProfileIssFrndlyName,m_pAppCtxt->theOpenProfParams.tbstrProfName,&tbstrProfileName);
		}
		else
		{
			/*retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrAppCtxtName, m_pAppCtxt->theOpenProfParams.tbstrProfName, 
							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.nNumOfRoamingSrvrs,
							m_pAppCtxt->theRoamingParams.ptbstrRoamingSrvrs, m_pAppCtxt->theRoamingParams.tbstrStorageSrvr, &varWhichSmartCard);*/

			retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrProfileIssFrndlyName, m_pAppCtxt->theOpenProfParams.tbstrProfName, 
							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.tbstrClientInfo,
							m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &varWhichSmartCard);

		}
	}

	/*Call the smart card open, which will inturn open that profile*/
	CVirtualSmartCard* pVirtualSmartCard = NULL;
	if(retVal == S_OK)
	{
		pVirtualSmartCard = new CVirtualSmartCard;

		VARIANT varPassword;
		VARIANT varAppCtxt;
		VARIANT varProfileIssFrndlyName;
		VARIANT varAppHostName;
		VARIANT varPasswdTimeOut;
	
		if(!boolOpenRemote)
		{
			varWhichSmartCard.vt = VT_BSTR;
			varWhichSmartCard.bstrVal = tbstrProfileName.copy();
		}
		
		//if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
		if(m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag  == DONOT_USE_PASSWORD)
		{
			varPassword.vt = VT_EMPTY;
		}
		else
		{
			varPassword.vt = VT_BSTR;
			varPassword.bstrVal = m_pAppCtxt->theOpenProfParams.tbstrPassword.copy();
		
		}

		varAppCtxt.vt = VT_BSTR;
		varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
		varProfileIssFrndlyName.vt = VT_BSTR;
		varProfileIssFrndlyName.bstrVal = m_pAppCtxt->tbstrProfileIssFrndlyName.copy();
		varAppHostName.vt = VT_BSTR;
		varAppHostName.bstrVal = m_pAppCtxt->tbstrHostName.copy();
		varPasswdTimeOut.vt = VT_I2;
		varPasswdTimeOut.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordTimeOut;

		retVal = pVirtualSmartCard->VSM_Open(&varWhichSmartCard,&varPassword,&varAppCtxt,
			&varProfileIssFrndlyName,&varAppHostName,&varPasswdTimeOut, m_pAppCtxt->theOpenProfParams.nFlag & CREATE_APP_IF_NOT_EXIST,
			PasswordCallback, (void*) this);	//	TIMEOUT

		if(!boolOpenRemote)
		{
			SysFreeString(varWhichSmartCard.bstrVal);
		}

		if(varPassword.vt == VT_BSTR)
		{			
		
			//Zero the memory before destroying the Text
			if(retVal == S_OK)
			{
				//memset(varPassword.bstrVal, 0, m_pAppCtxt->theOpenProfParams.tbstrPassword.length()*2);
				EraseMemory(m_pAppCtxt->theOpenProfParams.tbstrPassword.length()*2, (unsigned char*)varPassword.bstrVal);
			}

			SysFreeString(varPassword.bstrVal);

		}

		SysFreeString(varAppCtxt.bstrVal);
		SysFreeString(varAppHostName.bstrVal);
		SysFreeString(varProfileIssFrndlyName.bstrVal);
	}

#if 1
	// Make registry entries for all certs in this profile, if they
	// don't exist already. This is to enable certificates which are 
	// there in the local/roaming profile to be used by CAPI applications
	// from any machine
	if(retVal == S_OK)
	{
		_InstallCertsLocally(pVirtualSmartCard);			
	}
#endif

	if(retVal == S_OK)
	{
		*o_ppVirtualSmartCard = pVirtualSmartCard;

	}
	else
	{
		delete(pVirtualSmartCard);
		if(retVal == E_VS_INVALID_APP)
			retVal = E_PROFDOESNOTEXIST;
		if(retVal == E_INVALIDPASSWD && (m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag  == DONOT_USE_PASSWORD
			|| !m_pAppCtxt->theOpenProfParams.tbstrPassword.length()))
			retVal = E_INVALIDPASSWD_PASSWDREQD;
	}

//	VSPTA_CLEAN_TBSTR(tbstrProfileName)

	return retVal;
}


// Assuming that in a profile the first certificate is a MY store 
// certificate, then come the intermediate CA certs and then again
// the next set of MY and CA certs
HRESULT CVSPTA::_InstallCertsLocally(CVirtualSmartCard* i_pVirtualSmartCard)
{
	HRESULT retVal = S_OK;	
	BOOL boolDone = FALSE, bCertChainComplete = FALSE;
	int nCertNum = 0, nCertNumMY = 0;
	PIDLISTNODE pidListNodeCurr = NULL;
	PIDLISTNODE pidListNode = NULL, pidListHead = NULL;
	_bstr_t tbstrStorePref = CERTPREF_STORE;
	_bstr_t tbstrStoreVal = "";

	/*Till we've found the last cert*/
	do
	{
		pidListNode = m_pPtaEngine->NewCert();
		pidListNode->pCertContext = new CERT_CONTEXT;	

		/*Obtain cert blobs from the smart card*/
		retVal = i_pVirtualSmartCard->VSM_GetCert(nCertNum, NULL, &(pidListNode->pCertContext->cbCertEncoded));
		if(retVal == S_OK)
		{
			retVal = m_pPtaEngine->_GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrStorePref, &tbstrStoreVal);
			if(retVal == S_OK)
			{
				if(tbstrStoreVal == _bstr_t("MY"))
				{
					if(bCertChainComplete)
					{
						// A leaf cert was already found, 
						retVal = _MakeCertRegistryEntry(i_pVirtualSmartCard, pidListHead, nCertNumMY);

						m_pPtaEngine->FreeIdList(pidListHead);
						pidListHead = NULL;
						pidListNodeCurr = NULL;
					}

					nCertNumMY = nCertNum;
					bCertChainComplete = TRUE;
				}

				if(retVal != S_OK)
					break;

				// Get the cert 
				pidListNode->pCertContext->pbCertEncoded = new BYTE[pidListNode->pCertContext->cbCertEncoded];
				retVal = i_pVirtualSmartCard->VSM_GetCert(nCertNum, pidListNode->pCertContext->pbCertEncoded, &(pidListNode->pCertContext->cbCertEncoded));

				/*Create a cert info from this cert blob*/
				CCertInfo theCertInfo(pidListNode->pCertContext->pbCertEncoded,pidListNode->pCertContext->cbCertEncoded);
				pidListNode->pCertContext->pCertInfo = theCertInfo.GetCertInfo();

				if(pidListNodeCurr)
				{
					pidListNodeCurr->pidlistnodeNext = pidListNode;
					pidListNode = NULL;
					pidListNodeCurr = pidListNodeCurr->pidlistnodeNext;
					pidListNodeCurr->pidlistnodeNext = NULL;
				}
				else
				{
					pidListHead = pidListNode;
					pidListNodeCurr = pidListHead;
					pidListNodeCurr->pidlistnodeNext = NULL;
					pidListNode = NULL;
				}

				nCertNum++;
			}
			else
			{
				// Cert pref ie. MY or CA does not exist, cannot decide
				// how to call MakeCapiCompliantCertInstall(), break
				boolDone = TRUE;
			}
		}
		else if (retVal == E_CERTNOTFOUND)
		{
			boolDone = TRUE;
			if(!nCertNum)	// No certs have been found
				retVal = E_CERTNOTFOUND;
			else
			{
				// Last list of certs
				retVal = _MakeCertRegistryEntry(i_pVirtualSmartCard, pidListHead, nCertNumMY);
			}
		}
		else
		{
			boolDone = TRUE;
		}

	} while(!boolDone);

	if(pidListHead)
	{
		m_pPtaEngine->FreeIdList(pidListHead);
	}

	if(pidListNode)
	{
		//pidListNode->pidlistnodeNext = NULL;
		//m_pPtaEngine->FreeIdList(pidListNode);
		delete[] pidListNode->pCertContext;
		delete[] pidListNode;
	}

	return retVal;
}


HRESULT CVSPTA::_MakeCertRegistryEntry(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE pidListHead, unsigned int nCertNum)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrContainerNamePref = CERTPREF_CONTAINER_NAME;
	_bstr_t tbstrContainerNamePrefVal;
	BYTE *pbytePublicKeyId = NULL;
	DWORD dwPublicKeyIdSize, dwKeyType;
	BOOL bIsKeyExportable;

	retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(pidListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo, NULL, &dwPublicKeyIdSize);
	if(retVal == S_OK)
	{
		pbytePublicKeyId = new BYTE[dwPublicKeyIdSize];
		
		retVal = m_pPtaEngine->GetPubKeyIdentifierFromPubKey(pidListHead->pCertContext->pCertInfo->SubjectPublicKeyInfo,
									pbytePublicKeyId ,&dwPublicKeyIdSize);
		if(retVal == S_OK)
		{
			// Get the "ContainerName" cert preference, this will map to the container
			// structure so that we can get information about key existence and key usage
			retVal = m_pPtaEngine->_GetVSCapiCertPref(i_pVirtualSmartCard, nCertNum, tbstrContainerNamePref, &tbstrContainerNamePrefVal);

			if(retVal == S_OK)
			{
				// Now from the container name get information blob
				// regarding the key properties
				BYTE* pbyteContainerContents = NULL;
				DWORD dwContainerContentsLen = 0;
				retVal = i_pVirtualSmartCard->VSM_GetInformationBlob(tbstrContainerNamePrefVal, NULL, &dwContainerContentsLen);

				if(retVal == S_OK)
				{
					pbyteContainerContents = new BYTE [dwContainerContentsLen];

					retVal = i_pVirtualSmartCard->VSM_GetInformationBlob(tbstrContainerNamePrefVal, pbyteContainerContents, &dwContainerContentsLen);
					
					if(retVal == S_OK)
					{
						CSP_Key_Container* pstructContainer = (CSP_Key_Container*)pbyteContainerContents;

						// see which key in this container corresponds to this 
						// public key hash
						if((pstructContainer->structXchg).dwExists == VS_CSP_KEY_EXISTS)
						{
							if(!memcmp((pstructContainer->structXchg).pbytePubKeyHash, pbytePublicKeyId ,dwPublicKeyIdSize))
							{
								dwKeyType = KEY_ENCRYPTION;
								bIsKeyExportable = (pstructContainer->structXchg).dwExportable;
							}
						}

						if((pstructContainer->structSign).dwExists == VS_CSP_KEY_EXISTS)
						{
							if(!memcmp((pstructContainer->structSign).pbytePubKeyHash, pbytePublicKeyId ,dwPublicKeyIdSize))
							{
								dwKeyType = KEY_SIGNATURE;
								bIsKeyExportable = (pstructContainer->structSign).dwExportable;
							}
						}

						if(m_pAppCtxt->boolCapiCert)
							retVal = m_pPtaEngine->MakeCapiCompliantCertInstall(i_pVirtualSmartCard, pidListHead, 
										pbytePublicKeyId ,dwPublicKeyIdSize, (BYTE)dwKeyType, bIsKeyExportable, m_pAppCtxt->theOpenProfParams.boolRoamProfile,
										m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, -1, 
										tbstrContainerNamePrefVal);
					}

					delete[] pbyteContainerContents;
				}
			}
		}

		delete[] pbytePublicKeyId;
	}

	return retVal;
}

HRESULT CVSPTA::_HandleDeleteProfile(_bstr_t** o_pptbstrProfiles, int* o_pnNumOfProfiles)
{
	return S_OK;
}

HRESULT CVSPTA::_HandleSign(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE i_pSelectedId, _bstr_t* o_ptbstrSignature)
{
	HRESULT retVal = S_OK;

	/*Call the engine to create the signature*/
	if(m_pAppCtxt->theSignMsgParams.boolUTF8EncodeMsgToSign && m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign)
		retVal = m_pPtaEngine->SignData(i_pVirtualSmartCard, m_pAppCtxt->theSignMsgParams.pbyteUTF8MsgToSign, m_pAppCtxt->theSignMsgParams.nUTF8MsgToSignSize, 
			m_pAppCtxt->theSignMsgParams.nAlgId, i_pSelectedId, m_pAppCtxt->boolIsAttached, m_pAppCtxt->boolHashData, m_pAppCtxt->boolP7Output, m_pAppCtxt->theSignMsgParams.boolAddAuthAttr, m_pAppCtxt->theSignMsgParams.dateSignDate, o_ptbstrSignature);
	else
		retVal = m_pPtaEngine->SignData(i_pVirtualSmartCard, m_pAppCtxt->theSignMsgParams.pbyteMsgToSign, m_pAppCtxt->theSignMsgParams.nMsgToSignSize, 
			m_pAppCtxt->theSignMsgParams.nAlgId, i_pSelectedId, m_pAppCtxt->boolIsAttached, m_pAppCtxt->boolHashData, m_pAppCtxt->boolP7Output, m_pAppCtxt->theSignMsgParams.boolAddAuthAttr, m_pAppCtxt->theSignMsgParams.dateSignDate, o_ptbstrSignature);

	// RYAN - Delete the temporary file created before this.
	
	return retVal;

}

HRESULT CVSPTA:: _HandleCreatePasswd(CVirtualSmartCard* i_pVirtualSmartCard, BOOL i_boolOpenedWithPassword)
{
	HRESULT retVal = S_OK;

	do
	{
		if(!(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd.length()))
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}

		/*If password is required and the password should not be used return password required*/
		/* XXX
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality != PASSWDQUAL_REQUIRENOPASS &&
			m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd == FALSE)
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}
		*/

		/*If password is not required and the password is set return password not required */
		/* XXX
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
		{
			m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = "";
			m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = "";
		}
		*/


		/*Check if the password and confirm passwords are the same*/
		if(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd != m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd )
		{
			retVal =  E_CONFIRMPASSWORDNOMATCH;
			break;
		}
		
		/*Check the password sanity*/
		/*
		retVal = _CheckPasswordSanity(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;
			*/

		/*If its ok, set the password*/
		retVal = i_pVirtualSmartCard->VSM_CreatePasswd(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;
	

	}while(0);

	return retVal;
}

HRESULT CVSPTA:: _HandleEnterPasswd(CVirtualSmartCard* i_pVirtualSmartCard, BOOL i_boolOpenedWithPassword)
{
	HRESULT retVal = S_OK;

	do
	{
		if(!(m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd.length()))
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}

		/*If password is required and the password should not be used return password required*/
		/* XXX
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality != PASSWDQUAL_REQUIRENOPASS &&
			m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd == FALSE)
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}
		*/

		/*If password is not required and the password is set return password not required */
		/* XXX
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
		{
			m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = "";
			m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = "";
		}
		*/


		/*Check if the password and confirm passwords are the same*/
		if(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd != m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd )
		{
			retVal =  E_CONFIRMPASSWORDNOMATCH;
			break;
		}
		
		/*Check the password sanity*/
		/*
		retVal = _CheckPasswordSanity(m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;
			*/

		/*If its ok, set the password*/
		retVal = i_pVirtualSmartCard->VSM_EnterPasswd(m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd);
		if(retVal != S_OK)
			break;
	

	}while(0);

	return retVal;
}

HRESULT CVSPTA:: _HandleChangePasswd(CVirtualSmartCard* i_pVirtualSmartCard, BOOL i_boolOpenedWithPassword)
{
	HRESULT retVal = S_OK;

	do
	{
		if(!(m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd.length()) && !i_boolOpenedWithPassword)
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}

		/*If password is required and the password should not be used return password required*/
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality != PASSWDQUAL_REQUIRENOPASS &&
			m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd == FALSE)
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
			break;
		}

		/*If password is not required and the password is set return password not required */
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
		{
			m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = "";
			m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = "";
		}


		/*Check if the password and confirm passwords are the same*/
		if(m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd != m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd )
		{
			retVal =  E_CONFIRMPASSWORDNOMATCH;
			break;
		}
		
		/*Check the password sanity*/
		retVal = _CheckPasswordSanity(m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;

		/*If its ok, change the password*/
		retVal = i_pVirtualSmartCard->VSM_ChangePasswd(m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd, m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;
	

	}while(0);

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_HandleResetPasswd
//
//	Parameters
//				o_ppVirtualSmartCard - Output parameter containing pointer to opened profile
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function resets roaming profile password and re-opens the profile
//						with new password.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA:: _HandleResetPasswd(CVirtualSmartCard** o_ppVirtualSmartCard)
{
	HRESULT retVal = S_OK;

	do
	{
		if( !(m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer.length()) )
		{
			retVal = E_RESETPASSWD_ANSWERPASSWDREQD;
			break;
		}

		/*If password is not required and the password is set return password not required */
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
		{
			m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd = "";
			m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = "";
		}


		/*Check if the password and confirm passwords are the same*/
		if(m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd != m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd )
		{
			retVal =  E_CONFIRMPASSWORDNOMATCH;
			break;
		}
		
		/*Check the password sanity*/
		retVal = _CheckPasswordSanity(m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd);
		if(retVal != S_OK)
			break;


		CVirtualSmartCard	*pVirtualSmartCard = NULL;
		pVirtualSmartCard = new CVirtualSmartCard;

		if(!pVirtualSmartCard)
			return E_OUTOFMEMORY;

		// Check if roaming server information has been changed. If it is changed, then we need
		// to query the roaming server again to see if the server supports reset password feature
		// We will do this query only when roaming info is changed (or set at the first time)
		if(m_pAppCtxt->theRoamingParams.boolRoamInfoChanged)
		{
			BOOL	bResetPasswd;

			retVal = pVirtualSmartCard->VSM_IsResetPasswdSupported(m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &bResetPasswd);

			if(retVal == S_OK)
			{
				m_pAppCtxt->theRoamingParams.boolRoamingResetFeature = bResetPasswd;
				m_pAppCtxt->theRoamingParams.boolRoamInfoChanged = FALSE;
			}
			else 
			{
				delete pVirtualSmartCard;
				return retVal;
			}

		}

		if(m_pAppCtxt->theRoamingParams.boolRoamingResetFeature == FALSE)
		{
			retVal = E_RESETFEATURE_NOT_SUPPORTED;
			delete pVirtualSmartCard;
			break;
		}


		// Get the Profile Suffix
		if (!(m_pAppCtxt->tbstrProfileIssFrndlyName) || 
			 (m_pAppCtxt->tbstrProfileIssFrndlyName == (_bstr_t)""))
		{
			m_pAppCtxt->tbstrProfileIssFrndlyName = m_pAppCtxt->tbstrAppCtxtName;
		}	

		VARIANT varWhichSmartCard;

		retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrProfileIssFrndlyName, m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName, 
						m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &varWhichSmartCard);

		if(retVal == S_OK)
		{

			// Get Secret Question corresponding to user's profile from Roaming Server
			retVal = pVirtualSmartCard->VSM_ResetPassword(&varWhichSmartCard, m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer, m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd);

			if( retVal == S_OK )
			{
				// reopen smart card with user name and password
				VARIANT varPassword;
				VARIANT varAppCtxt;
				VARIANT varProfileIssFrndlyName;
				VARIANT varAppHostName;
				VARIANT varPasswdTimeOut;

				m_pAppCtxt->theOpenProfParams.tbstrProfName = m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName;
				m_pAppCtxt->theOpenProfParams.tbstrPassword = m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd;

				varPassword.vt = VT_BSTR;
				varPassword.bstrVal = m_pAppCtxt->theOpenProfParams.tbstrPassword.copy();

				varAppCtxt.vt = VT_BSTR;
				varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
				varProfileIssFrndlyName.vt = VT_BSTR;
				varProfileIssFrndlyName.bstrVal = m_pAppCtxt->tbstrProfileIssFrndlyName.copy();
				varAppHostName.vt = VT_BSTR;
				varAppHostName.bstrVal = m_pAppCtxt->tbstrHostName.copy();
				varPasswdTimeOut.vt = VT_I2;
				varPasswdTimeOut.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordTimeOut;

				retVal = pVirtualSmartCard->VSM_Open(&varWhichSmartCard,&varPassword,&varAppCtxt,
					&varProfileIssFrndlyName,&varAppHostName,&varPasswdTimeOut, m_pAppCtxt->theOpenProfParams.nFlag & CREATE_APP_IF_NOT_EXIST,
					PasswordCallback, (void*) this);	//	TIMEOUT

			}

			SysFreeString(varWhichSmartCard.bstrVal);
		}

		if(retVal == S_OK)
		{
			*o_ppVirtualSmartCard  = pVirtualSmartCard;
		}
		else
		{
			delete pVirtualSmartCard;
		}


	}while(0);

	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_HandleGetSecretQuestion
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function retrieves secret question corresponding to user's
//						roaming profile from the roaming server.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA:: _HandleGetSecretQuestion()
{
	HRESULT retVal = S_OK;

	do
	{

		if(m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		{

			CVirtualSmartCard	*pVirtualSmartCard = NULL;
			pVirtualSmartCard = new CVirtualSmartCard;

			if(!pVirtualSmartCard)
				return E_OUTOFMEMORY;


			// Check if roaming server information has been changed. If it is changed, then we need
			// to query the roaming server again to see if the server supports reset password feature
			// We will do this query only when roaming info is changed (or set at the first time)
			if(m_pAppCtxt->theRoamingParams.boolRoamInfoChanged)
			{
				BOOL	bResetPasswd;

				retVal = pVirtualSmartCard->VSM_IsResetPasswdSupported(m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &bResetPasswd);

				if(retVal == S_OK)
				{
					m_pAppCtxt->theRoamingParams.boolRoamingResetFeature = bResetPasswd;
					m_pAppCtxt->theRoamingParams.boolRoamInfoChanged = FALSE;
				}
				else 
				{
					delete pVirtualSmartCard;
					return retVal;
				}

			}

			if(m_pAppCtxt->theRoamingParams.boolRoamingResetFeature == FALSE)
			{
				retVal = E_RESETFEATURE_NOT_SUPPORTED;
				delete pVirtualSmartCard;
				break;
			}

			if( !(m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName.length()) )
			{
				retVal = E_GETSECRET_PROFILEREQD;
				delete pVirtualSmartCard;
				break;
			}


			// Get the Profile Suffix
			if (!(m_pAppCtxt->tbstrProfileIssFrndlyName) || 
				 (m_pAppCtxt->tbstrProfileIssFrndlyName == (_bstr_t)""))
			{
				m_pAppCtxt->tbstrProfileIssFrndlyName = m_pAppCtxt->tbstrAppCtxtName;
			}	

			VARIANT varWhichSmartCard;

			retVal = m_pPtaEngine->GetRoamingProfileParams(m_pAppCtxt->tbstrProfileIssFrndlyName, m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName, 
							m_pAppCtxt->tbstrProfileIssUniqueId, m_pAppCtxt->theRoamingParams.tbstrClientInfo, m_pAppCtxt->theRoamingParams.tbstrClientInfoSig, &varWhichSmartCard);

			if(retVal == S_OK)
			{

				// Get Secret Question corresponding to user's profile from Roaming Server
				retVal = pVirtualSmartCard->VSM_GetSecretQuestion(&varWhichSmartCard, m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion);

				if( retVal == S_OK && !m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion.length())
					retVal = E_GETSECRET_PROFDOESNOTEXIST;

				SysFreeString(varWhichSmartCard.bstrVal);

			}

			delete pVirtualSmartCard;
		}
		else
		{
			// Cannot reset password for local profiles
			retVal = E_RESETFEATURE_NOT_SUPPORTED;

		}

	}while(0);

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_HandleCreateSecret
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function checks secret question and answer to see if
//						they are not blank.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-06-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA:: _HandleCreateSecret()
{
	HRESULT retVal = S_OK;

	do
	{
		if( !(m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion.length()) || !(m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer.length()))
		{
			retVal = E_CREATESECRET_SECRETREQD;
			break;
		}


	}while(0);

	return retVal;
}

int CVSPTA::_GetFirstUIAndWizard(int i_nWizardAndUIs)
{
	int nRetVal;
	

	nRetVal = i_nWizardAndUIs & OPERATION_BITS; //Get the uis to be shown

	// XXX operations bits ran out!
	if ((nRetVal != CREATEPASSWD_BASE) && (nRetVal != ENTERPASSWD_BASE)) {
		nRetVal = ((-nRetVal) & nRetVal); //Find the least significant 1
	}

	if(nRetVal & OPENPROF_BASE)
		nRetVal = nRetVal | (i_nWizardAndUIs & FLAG_BITS);
	nRetVal |= (i_nWizardAndUIs & WIZARD_BITS);
	return nRetVal;
}

int CVSPTA::_MoreThanOneUI(int i_nWizardAndUIs)
{
	i_nWizardAndUIs &= OPERATION_BITS;
	if((~((-i_nWizardAndUIs)&i_nWizardAndUIs)) & i_nWizardAndUIs)
		return TRUE;
	else
		 return FALSE;
}

int CVSPTA::_GetLastUIAndWizard(int i_nWizardAndUIs)
{
	int nRetVal;
	nRetVal = i_nWizardAndUIs & OPERATION_BITS; //Get the uis to be shown

	//Get the last ui
	if ((nRetVal == CREATEPASSWD_BASE) || (nRetVal == ENTERPASSWD_BASE)) {
		return(nRetVal);
	}

	if(nRetVal & IMPORTPROFILE_BASE && nRetVal & EXPORTPROFILE_BASE)
	{
		nRetVal &= IMPORTPROFILE_BASE;
		return nRetVal;
	}

	if(nRetVal & EXPORTPROFILE_BASE)
		nRetVal &= EXPORTPROFILE_BASE;
	if(nRetVal & SETCERTPREF_BASE)
		nRetVal &= SETCERTPREF_BASE;
	if(nRetVal & IMPORTP12_BASE)
		nRetVal &= IMPORTP12_BASE;
	if(nRetVal & EXPORTP12_BASE)
		nRetVal &= EXPORTP12_BASE;
	if(nRetVal & GETCERTPREF_BASE)
		nRetVal &= GETCERTPREF_BASE;
	if(nRetVal & SIGNMSG_BASE)
		nRetVal &= SIGNMSG_BASE;
	if(nRetVal & SELID_BASE)
		nRetVal &= SELID_BASE;
	if(nRetVal & CHANGEPASSWD_BASE)
		nRetVal &= CHANGEPASSWD_BASE;
	if(nRetVal & CREATECERTREQ_BASE)
		nRetVal &= CREATECERTREQ_BASE ;
	if(nRetVal & INSTALLCERT_BASE)
		nRetVal &= INSTALLCERT_BASE;
	if(nRetVal & CREATESECRET_BASE)
		nRetVal &= CREATESECRET_BASE;
	if(nRetVal & REMOVECERTIFICATES_BASE)
		nRetVal &= REMOVECERTIFICATES_BASE ;
	if(nRetVal & OPENPROF_BASE)
		nRetVal &= OPENPROF_BASE;
	   // DON'T change this order. It is very important
	if(nRetVal & RESETPASSWD_BASE)
		nRetVal &= RESETPASSWD_BASE;
	if(nRetVal & GETSECRETQUESTION_BASE)
		nRetVal &= GETSECRETQUESTION_BASE;
	
	return nRetVal;
}

HRESULT CVSPTA::_OpenProfCreateFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt); // ###

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		//If a profile has been opened, and it is not the same as 
		//the one specified by the user
		if(i_pOpCtxt->pOParams->pVirtualSmartCard && 
			(((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrProfName != m_pAppCtxt->theOpenProfParams.tbstrProfName))
		{
			/*Close the current profile and set the profile name to empty*/
			delete(i_pOpCtxt->pOParams->pVirtualSmartCard);		
			i_pOpCtxt->pOParams->pVirtualSmartCard = NULL;
			m_pAppCtxt->theOpenProfParams.tbstrProfName = "";

			/*Free the list of certs stored in the context*/
			m_pPtaEngine->FreeIdList(i_pOpCtxt->pCertListHead);
			i_pOpCtxt->pCertListHead = NULL;

			//Set the selected cert to null
			m_pPtaEngine->FreeIdList(i_pOpCtxt->pOParams->pSelectedId);
			i_pOpCtxt->pOParams->pSelectedId = NULL;
		}
		else if ((((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrProfName == m_pAppCtxt->theOpenProfParams.tbstrProfName))
		{
			//Set the selected cert to null
			m_pPtaEngine->FreeIdList(i_pOpCtxt->pOParams->pSelectedId);
			i_pOpCtxt->pOParams->pSelectedId = NULL;
		}

		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		if(((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->boolShowPassword)
			m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;
		else
			m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = DONOT_USE_PASSWORD;

		//Set the username and password
		m_pAppCtxt->theOpenProfParams.tbstrProfName = ((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrProfName;
		m_pAppCtxt->theOpenProfParams.tbstrPassword = ((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrPassword;
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = ((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrConfirmPassword;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- OPENPROF_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | OPENPROF_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					//If the ID selection UI has been turned off, then unmask the select id bit so that it does not 
					//get counted as an operation
					if((!m_pAppCtxt->boolShowSelIDUI) && (nWizardAndUIs && SELID_BASE))
					{	
						nWizardAndUIs &= (~SELID_BASE);
					}
					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
							((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}


HRESULT CVSPTA::_OpenProfOpenHelpFn(POPCTXT i_pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrOpenProf_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrOpenProf_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrOpenProf_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;
}


HRESULT CVSPTA::_OpenProfCreateHelpFn(POPCTXT i_pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrNewPasswd_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrNewPasswd_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrNewPasswd_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;

}

HRESULT CVSPTA::_CreatePasswdFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		//Set the username and password
		m_pAppCtxt->theCreatePasswdParams.boolUseNewPasswd = TRUE;
		m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd = ((PALL_CREATEPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrNewPassword;
		m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd = ((PALL_CREATEPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrConfirmPassword;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- CREATEPASSWD_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | CREATEPASSWD_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_CREATEPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrNewPassword = m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd;
							((PALL_CREATEPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}

HRESULT CVSPTA::_EnterPasswdFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		m_pAppCtxt->theEnterPasswdParams.boolUseNewPasswd = TRUE;
		m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd = ((PALL_ENTERPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrThePassword;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- ENTERPASSWD_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | CREATEPASSWD_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_ENTERPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrThePassword = m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}

HRESULT CVSPTA::_ChngPasswdFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		//Set the username and password
		m_pAppCtxt->theChangePasswdParams.boolUseOldPasswd = TRUE;
		m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd = TRUE;
		m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd = ((PALL_CHANGEPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrOldPassword;
		m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd = ((PALL_CHANGEPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrNewPassword;
		m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd = ((PALL_CHANGEPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrConfirmPassword;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- CHANGEPASSWD_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | CHANGEPASSWD_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_CHANGEPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrOldPassword = m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd;
							((PALL_CHANGEPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrNewPassword = m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd;
							((PALL_CHANGEPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}

HRESULT CVSPTA::_ImportP12Fn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		//Obtain the parameters from the current ui

		//Set the p12 password
		m_pAppCtxt->theImportP12Params.tbstrP12Passwd = ((PALL_IMPORTP12_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrP12Passwd;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- IMPORTP12_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | IMPORTP12_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_IMPORTP12_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrP12Passwd = m_pAppCtxt->theImportP12Params.tbstrP12Passwd;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}

HRESULT CVSPTA::_ExportP12Fn(POPCTXT i_pOpCtxt)
{
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	
	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		
		//Set other op context parameters
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		m_boolIdSatisfiesSrchCrit = TRUE;
		m_boolUserHasSeenMsg = TRUE;
		
		//Set the filename and password information
		m_pAppCtxt->theExportP12Params.boolUsePasswd = TRUE;
		m_pAppCtxt->theExportP12Params.tbstrP12Passwd = ((PALL_EXPORTP12_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrP12Passwd;
		m_pAppCtxt->theExportP12Params.tbstrP12ConfPasswd = ((PALL_EXPORTP12_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrP12ConfPasswd;
		m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob = ((PALL_EXPORTP12_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrKeyFile;
		

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- SIGNMSG_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | EXPORTP12_BASE | i_pOpCtxt->nWizardAndUIs);


		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = 	nOrigWizAndUIs;


	}

	_FreeUIContext(pCurrUICtxt);
		
	
	return retVal;
}


HRESULT CVSPTA::_ExportProfileFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;

	return retVal;
}

HRESULT CVSPTA::_ImportProfileFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;

	return retVal;
}


HRESULT CVSPTA::_ChngPasswdHelpFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrChangePasswd_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrChangePasswd_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrChangePasswd_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;

}


HRESULT CVSPTA::_ImportP12HelpFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrImpP12_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrImpP12_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrImpP12_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;

}

HRESULT CVSPTA::_ExportP12HelpFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrExpP12_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrExpP12_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrExpP12_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;

}

HRESULT CVSPTA::_SelIdFn(POPCTXT i_pOpCtxt)
{
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);
	
	
	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		//If an id is selected, delete it.
		if(i_pOpCtxt->pOParams->pSelectedId)
		{
			m_pPtaEngine->FreeIdList(i_pOpCtxt->pOParams->pSelectedId);
		}

		//Obtain the selected id
		i_pOpCtxt->pOParams->pSelectedId = ((PALL_SELID_UIELEMENTS)(pCurrUICtxt->pvUIElements))->pCertListHead;
		for(int i=0;i<((PALL_SELID_UIELEMENTS)(pCurrUICtxt->pvUIElements))->nSelectedIDFromList; ++i)
		{
			i_pOpCtxt->pOParams->pSelectedId = i_pOpCtxt->pOParams->pSelectedId->pidlistnodeNext;
		}
		i_pOpCtxt->pOParams->pSelectedId = m_pPtaEngine->CopyCert(i_pOpCtxt->pOParams->pSelectedId);
		i_pOpCtxt->nSelectedIdNum = i;

		//Set other op context parameters
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		m_boolIdSatisfiesSrchCrit = TRUE;
		m_boolUserHasSeenMsg = TRUE;
		
		if(((PALL_SELID_UIELEMENTS)(pCurrUICtxt->pvUIElements))->nChkBoxState == BST_CHECKED)
			m_pAppCtxt->theSelIdParams.boolMarkAsDefault = TRUE;
		else
			m_pAppCtxt->theSelIdParams.boolMarkAsDefault = FALSE;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- SELID_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | SELID_BASE | i_pOpCtxt->nWizardAndUIs);

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_SELID_UIELEMENTS)(pUICtxt->pvUIElements))->nSelectedIDFromList = ((PALL_SELID_UIELEMENTS)(pCurrUICtxt->pvUIElements))->nSelectedIDFromList;
						}
						
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}
	
	_FreeUIContext(pCurrUICtxt);
	

	i_pOpCtxt->nWizardAndUIs = 	nOrigWizAndUIs;
	
	return retVal;
}


HRESULT CVSPTA::_SelIdHelpFn(POPCTXT i_pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrSelID_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrSelID_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrSelID_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;
}

HRESULT CVSPTA::_SignMsgFn(POPCTXT i_pOpCtxt)
{
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	
	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		
		//Set other op context parameters
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		m_boolIdSatisfiesSrchCrit = TRUE;
		m_boolUserHasSeenMsg = TRUE;
		
		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- SIGNMSG_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | SIGNMSG_BASE | i_pOpCtxt->nWizardAndUIs);


		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = 	nOrigWizAndUIs;


	}

	_FreeUIContext(pCurrUICtxt);
		
	
	return retVal;
}

HRESULT CVSPTA::_SignMsgHelpFn(POPCTXT i_pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrRvwMsg_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrRvwMsg_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrRvwMsg_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;
}

HRESULT CVSPTA::_IntroFn(POPCTXT i_pOpCtxt)
{
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;
	_bstr_t tbstrOrigPassword = "";
	_bstr_t tbstrOrigConfPasswd;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	
	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		
		//Set other op context parameters
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolIntroSeen = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		tbstrOrigPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
		tbstrOrigConfPasswd = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
		m_pAppCtxt->theOpenProfParams.tbstrPassword = "";
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		m_pAppCtxt->theOpenProfParams.tbstrPassword = tbstrOrigPassword ;
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = tbstrOrigConfPasswd;

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- INTRO_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | INTRO_BASE | i_pOpCtxt->nWizardAndUIs);


		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = 	nOrigWizAndUIs;


	}

	_FreeUIContext(pCurrUICtxt);

//	VSPTA_CLEAN_TBSTR(tbstrOrigPassword)
//	VSPTA_CLEAN_TBSTR(tbstrOrigConfPasswd)
	
	return retVal;
}


HRESULT CVSPTA::_IntroDlgHelpFn(POPCTXT i_pOpCtxt)
{
	HRESULT retVal = S_OK;

	if(m_pAppCtxt->theUIPrefs.tbstrIntroDlg_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrIntroDlg_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrIntroDlg_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_GetSecretQuestionFn
//
//	Parameters
//				i_pOpCtxt: Input - contains operation context
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function creates UI for get secret question operation
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_GetSecretQuestionFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt); // ###

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;


		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;

		//Set the username and password
		m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName = ((PALL_GETSECRETQUESTION_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrProfName;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- GETSECRETQUESTION_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | GETSECRETQUESTION_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					//If the ID selection UI has been turned off, then unmask the select id bit so that it does not 
					//get counted as an operation
					if((!m_pAppCtxt->boolShowSelIDUI) && (nWizardAndUIs && SELID_BASE))
					{	
						nWizardAndUIs &= (~SELID_BASE);
					}
					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ResetPasswdFn
//
//	Parameters
//				i_pOpCtxt: Input - contains operation context
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function creates UI for password reset operation
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ResetPasswdFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		//Set the username and password
		m_pAppCtxt->theResetPasswdParams.boolUseNewPasswd = TRUE;
		m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer = ((PALL_RESETPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrSecretAnswer;
		m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd = ((PALL_RESETPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrNewPassword;
		m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = ((PALL_RESETPASSWD_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrConfirmPassword;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- RESETPASSWD_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | RESETPASSWD_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, 0);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_RESETPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrSecretAnswer = m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer;
							((PALL_RESETPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrNewPassword = m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd;
							((PALL_RESETPASSWD_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_CreateSecretFn
//
//	Parameters
//				i_pOpCtxt: Input - contains operation context
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function creates UI for create secret operation
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_CreateSecretFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;

		
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->nWizardAndUIs = 0;
		
		//Set the username and password
		m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion = ((PALL_CREATESECRET_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrSecretQuestion;
		m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer = ((PALL_CREATESECRET_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrSecretAnswer;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((~(-operation) & origUIs) | operation | newUIs | flags))
		nOrigWizAndUIs = (((~(- CREATESECRET_BASE)) & (nOrigWizAndUIs &OPERATION_BITS)) | CREATESECRET_BASE | i_pOpCtxt->nWizardAndUIs | (nOrigWizAndUIs & FLAG_BITS));

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();

				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*If there is only one operation to be performed, then set the wizard
					to none*/
					DWORD dwMaskBits = WIZARD_BITS|OPERATION_BITS|FLAG_BITS;

					//First if this is a login wizard then unmask the sign bit so that
					//it doesnt get counted as an operation in the wizard.
					int nWizardAndUIs = nOrigWizAndUIs;
					if((nWizardAndUIs & LOGIN_WIZARD_BASE) && (nWizardAndUIs && SIGNMSG_BASE))
						nWizardAndUIs &= (~SIGNMSG_BASE);

					
					if(!_MoreThanOneUI(nWizardAndUIs))
						dwMaskBits =  (OPERATION_BITS | FLAG_BITS);

					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs & dwMaskBits,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles, i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, 0);

					if(retVal == S_OK)
					{
						/*If the ui to be shown is the same as the current ui, set the
						other parameters*/
					
						if(pUICtxt->nWhichWizardAndUI == pCurrUICtxt->nWhichWizardAndUI)
						{
							((PALL_CREATESECRET_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrSecretQuestion = m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion;
							((PALL_CREATESECRET_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrSecretAnswer = m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer;
						}
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}

		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;

	}

	_FreeUIContext(pCurrUICtxt);
	delete pCurrUICtxt;


	return retVal;

}

HRESULT CVSPTA::_PrevToCreateFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;
	CVirtualSmartCard* pVSOrigSmartCard;
	PIDLISTNODE pOrigSelectedCert;
	_bstr_t tbstrOrigProfName;
	_bstr_t tbstrOrigPassword;
	_bstr_t tbstrOrigConfirmPassword;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		//Save the original operation context and open profile parameters
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		pVSOrigSmartCard = i_pOpCtxt->pOParams->pVirtualSmartCard;
		pOrigSelectedCert = i_pOpCtxt->pOParams->pSelectedId;
		tbstrOrigProfName = m_pAppCtxt->theOpenProfParams.tbstrProfName;
		tbstrOrigPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
		tbstrOrigConfirmPassword = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
		
		//Set the op context
		i_pOpCtxt->boolFromUI = FALSE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		i_pOpCtxt->pOParams->pSelectedId = NULL;
		i_pOpCtxt->pOParams->pVirtualSmartCard = NULL;
		
		//If the current ui is a select ui then remember the currently selected cert
		if(pCurrUICtxt->nWhichWizardAndUI & SELID_BASE)
			i_pOpCtxt->nSelectedIdNum = ((PALL_SELID_UIELEMENTS)(pCurrUICtxt->pvUIElements))->nSelectedIDFromList;

		//Set the username and password
		m_pAppCtxt->theOpenProfParams.tbstrProfName = "";
		m_pAppCtxt->theOpenProfParams.tbstrPassword = "";
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- OPENPROF_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | OPENPROF_BASE | i_pOpCtxt->nWizardAndUIs);

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						//Pickle the ui context
						((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrProfName = tbstrOrigProfName;
						((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrPassword = tbstrOrigPassword; 
						((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrConfirmPassword = tbstrOrigConfirmPassword; 

						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs ;
		i_pOpCtxt->pOParams->pVirtualSmartCard = pVSOrigSmartCard ;
		i_pOpCtxt->pOParams->pSelectedId = pOrigSelectedCert ;
		m_pAppCtxt->theOpenProfParams.tbstrProfName = tbstrOrigProfName ;
		m_pAppCtxt->theOpenProfParams.tbstrPassword = tbstrOrigPassword;


	}

	_FreeUIContext(pCurrUICtxt);

//	VSPTA_CLEAN_TBSTR(tbstrOrigProfName)
//	VSPTA_CLEAN_TBSTR(tbstrOrigPassword)
//	VSPTA_CLEAN_TBSTR(tbstrOrigConfirmPassword)

	return retVal;
}

HRESULT CVSPTA::_PrevToIntroFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;
	_bstr_t tbstrOrigProfName;
	_bstr_t tbstrOrigPassword;
	_bstr_t tbstrOrigConfirmPassword;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		//Save the original operation context and open profile parameters
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		tbstrOrigProfName = m_pAppCtxt->theOpenProfParams.tbstrProfName;
		tbstrOrigPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
		tbstrOrigConfirmPassword = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
		
		//Set the op context
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolIntroSeen= FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		

		//Set the username and password
		m_pAppCtxt->theOpenProfParams.tbstrProfName = "";
		m_pAppCtxt->theOpenProfParams.tbstrPassword = "";
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- INTRO_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | INTRO_BASE | i_pOpCtxt->nWizardAndUIs);

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs ;
		m_pAppCtxt->theOpenProfParams.tbstrProfName = tbstrOrigProfName ;
		m_pAppCtxt->theOpenProfParams.tbstrPassword = tbstrOrigPassword;
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = tbstrOrigConfirmPassword;

	}

	_FreeUIContext(pCurrUICtxt);

//	VSPTA_CLEAN_TBSTR(tbstrOrigProfName)
//	VSPTA_CLEAN_TBSTR(tbstrOrigPassword)
//	VSPTA_CLEAN_TBSTR(tbstrOrigConfirmPassword)

	return retVal;

}

HRESULT CVSPTA::_PrevToSelIdFn(POPCTXT i_pOpCtxt)
{
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;
	PIDLISTNODE pidOrigSelectedCert;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	
	/*Set the op context*/
	if(retVal == S_OK)
	{
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		pidOrigSelectedCert = i_pOpCtxt->pOParams->pSelectedId;
		
		//Set other op context parameters
		i_pOpCtxt->boolFromUI = TRUE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		i_pOpCtxt->pOParams->pSelectedId = NULL;

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- SELID_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | SELID_BASE | i_pOpCtxt->nWizardAndUIs);

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);

			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs;
		i_pOpCtxt->pOParams->pSelectedId = pidOrigSelectedCert ;

	}

	_FreeUIContext(pCurrUICtxt);
	

	i_pOpCtxt->nWizardAndUIs = 	nOrigWizAndUIs;
	
	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_PrevToGetSecretQuestionFn
//
//	Parameters
//				i_pOpCtxt: Input - contains operation context
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function creates UI when user clicks on previous button 
//						to go to get secret question dialog.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_PrevToGetSecretQuestionFn(POPCTXT i_pOpCtxt)
{
	/*Obtain the ui context of the current ui*/
	PUICTXT pCurrUICtxt;
	HRESULT retVal = S_OK;
	int nOrigWizAndUIs;
	_bstr_t tbstrOrigProfName;
	_bstr_t tbstrOrigSecretQuestion;

	pCurrUICtxt = _CreateUIContext();
	retVal = m_pPtaUI->get_UIContext(pCurrUICtxt);

	/*Set the op context*/
	if(retVal == S_OK)
	{
		//Save the original operation context and get profile parameters
		nOrigWizAndUIs = i_pOpCtxt->nWizardAndUIs;
		tbstrOrigProfName = m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName;
		tbstrOrigSecretQuestion = m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion;
		
		//Set the op context
		i_pOpCtxt->boolFromUI = FALSE;
		i_pOpCtxt->boolSignMsgSeen = FALSE;
		i_pOpCtxt->nWizardAndUIs = 0;
		

		//Set the username and clear the secret question
		m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName = "";
		m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion = "";

		/*Determine which uis to show*/
		retVal = _DetermineWizAndUIs((*i_pOpCtxt), (nOrigWizAndUIs & WIZARD_BITS), _GetLastUIAndWizard(nOrigWizAndUIs));

		//Reset the original wizard and uis according to this formula -
		// ((!(-operation) & origUIs) | operation | newUIs))
		nOrigWizAndUIs = ((~(- GETSECRETQUESTION_BASE) & (nOrigWizAndUIs &OPERATION_BITS)) | GETSECRETQUESTION_BASE | i_pOpCtxt->nWizardAndUIs);

		if(retVal == S_OK)
		{
			/*If a ui is to be shown*/
			if(i_pOpCtxt->nWizardAndUIs & OPERATION_BITS)
			{
				PUICTXT pUICtxt;

				pUICtxt = _CreateUIContext();
				if(!pUICtxt)
					retVal = E_FAIL;
				else
				{
					/*Obtain the context for the first ui*/
					retVal = _InitializeUIContext(pUICtxt,nOrigWizAndUIs,
						_GetFirstUIAndWizard(i_pOpCtxt->nWizardAndUIs), i_pOpCtxt->ptbstrProfiles, i_pOpCtxt->nNumOfProfiles,i_pOpCtxt->pCertListHead, i_pOpCtxt->nSelectedIdNum, i_pOpCtxt->boolOpenedWithPassword);

					if(retVal == S_OK)
					{
						//Pickle the ui context
						((PALL_GETSECRETQUESTION_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrProfName = tbstrOrigProfName;

						/*Set the ui context*/
						retVal = m_pPtaUI->put_UIContext(pUICtxt);		
					}

					_FreeUIContext(pUICtxt);
					delete (pUICtxt);
				}
			}
			else
			{
				m_pPtaUI->put_UIContext(NULL);
			}
		}
		else
		{
			m_pPtaUI->put_UIContext(NULL);
		}


		i_pOpCtxt->nWizardAndUIs = nOrigWizAndUIs ;
		m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName = tbstrOrigProfName ;
		m_pAppCtxt->theResetPasswdParams.tbstrProfName = "";
		m_pAppCtxt->theResetPasswdParams.tbstrSecretQuestion = "";

	}

	_FreeUIContext(pCurrUICtxt);


	return retVal;
}

HRESULT CVSPTA::_CancelFn(POPCTXT i_pOpCtxt)
{
	//Make the ui context equal to null
	m_pPtaUI->put_UIContext(NULL);
	return E_USERCANCELLED;
}



HRESULT OpenProfCreateFn(POPCTXT pOpCtxt)
{
	/*Call the internal pta function*/
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_OpenProfCreateFn(pOpCtxt);
}

HRESULT OpenProfCreateHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_OpenProfCreateHelpFn(pOpCtxt);
}


HRESULT OpenProfOpenFn(POPCTXT pOpCtxt)
{
	/*Call the internal pta function*/
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_OpenProfCreateFn(pOpCtxt);
}

HRESULT OpenProfOpenHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_OpenProfOpenHelpFn(pOpCtxt);
}


HRESULT CreatePasswdFn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_CreatePasswdFn(pOpCtxt);
}

HRESULT EnterPasswdFn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_EnterPasswdFn(pOpCtxt);
}

HRESULT ChngPasswdFn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ChngPasswdFn(pOpCtxt);
}



HRESULT ChngPasswdHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ChngPasswdHelpFn(pOpCtxt);
}


HRESULT ImportP12Fn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ImportP12Fn(pOpCtxt);
}

HRESULT ImportP12HelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ImportP12HelpFn(pOpCtxt);
}

HRESULT SelIdFn(POPCTXT pOpCtxt)
{
	/*Call the internal pta function*/
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_SelIdFn(pOpCtxt);
}


HRESULT SelIdHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_SelIdHelpFn(pOpCtxt);
}


HRESULT SignMsgFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_SignMsgFn(pOpCtxt);
}

HRESULT ExportP12Fn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ExportP12Fn(pOpCtxt);
}

HRESULT ExportP12HelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ExportP12HelpFn(pOpCtxt);
}

HRESULT IntroFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_IntroFn(pOpCtxt);
}

HRESULT SignMsgHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_SignMsgHelpFn(pOpCtxt);
}


HRESULT GetSecretQuestionFn(POPCTXT pOpCtxt)
{
	/*Call the internal pta function*/
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_GetSecretQuestionFn(pOpCtxt);
}

HRESULT ResetPasswdFn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ResetPasswdFn(pOpCtxt);
}

HRESULT CreateSecretFn(POPCTXT pOpCtxt)
{
	//	Call the internal pta function
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_CreateSecretFn(pOpCtxt);
}

HRESULT PrevToCreateFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_PrevToCreateFn(pOpCtxt);
}

HRESULT PrevToOpenFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_PrevToCreateFn(pOpCtxt);
}

HRESULT PrevToIntroFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_PrevToIntroFn(pOpCtxt);
}

HRESULT PrevToSelIdFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_PrevToSelIdFn(pOpCtxt);
}

HRESULT PrevToGetSecretQuestionFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_PrevToGetSecretQuestionFn(pOpCtxt);
}

HRESULT CancelFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_CancelFn(pOpCtxt);
}


HRESULT IntroDlgFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_IntroDlgHelpFn(pOpCtxt);
}


HRESULT ExportProfileFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ExportProfileFn(pOpCtxt);
}


HRESULT ImportProfileFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_ImportProfileFn(pOpCtxt);
}


PFONTSINFO CVSPTA::_CreateFontStruct(short i_nWhichFonts)
{
	PFONTSINFO pFontsInfoRetVal;

	pFontsInfoRetVal = new (FONTSINFO);
	if(!pFontsInfoRetVal)
		return NULL;

	switch(i_nWhichFonts)
	{
	case FONTS_CUSTOM :
		pFontsInfoRetVal->dwCharset = _GetCharset(m_pAppCtxt->theUIPrefs.wLangID);
		pFontsInfoRetVal->tbstrBtnFont = m_pAppCtxt->theUIPrefs.tbstrBtnFont;
		pFontsInfoRetVal->tbstrTextFont = m_pAppCtxt->theUIPrefs.tbstrTextFont;
		pFontsInfoRetVal->tbstrTitleFont = m_pAppCtxt->theUIPrefs.tbstrTitleFont;
		break;

	case FONTS_DEFAULT :
		pFontsInfoRetVal->dwCharset = _GetCharset(m_pAppCtxt->theDefUIPrefs.wLangID);
		pFontsInfoRetVal->tbstrBtnFont = m_pAppCtxt->theDefUIPrefs.tbstrBtnFont;
		pFontsInfoRetVal->tbstrTextFont = m_pAppCtxt->theDefUIPrefs.tbstrTextFont;
		pFontsInfoRetVal->tbstrTitleFont = m_pAppCtxt->theDefUIPrefs.tbstrTitleFont;
		break;
	}

	return pFontsInfoRetVal;
}

HRESULT CVSPTA::_SetWizardElems(int i_nWhichWizard, void** o_ppvWizUIElements)
{
	HRESULT retVal = S_OK;

	if(i_nWhichWizard == NO_WIZARD_BASE)
	{
		*o_ppvWizUIElements = NULL;
		return S_OK;
	}

	*o_ppvWizUIElements = (void*)new (ALLWIZARDELEMENTS);
	if(! *o_ppvWizUIElements)
	{
		return E_FAIL;
	}
	
	/*Depending upon the wizard, allocate the wizard data structure, and set
	the appropriate strings*/
	switch(i_nWhichWizard)
	{
	case LOGIN_WIZARD_BASE :
		((PALL_LOGIN_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrLgnDlg_Title;
		((PALL_LOGIN_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrLgnDlg_Title;
		break;

	case SIGN_WIZARD_BASE :
		((PALL_SIGN_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrSgnDlg_Title;
		((PALL_SIGN_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrSgnDlg_Title;
		break;

	case CREATE_WIZARD_BASE :
		((PALL_CREATE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrCreateDlg_Title;
		((PALL_CREATE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrCreateDlg_Title;
		break;

	case IMPORTP12_WIZARD_BASE :
		((PALL_IMPORT_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrImpDlg_Title;
		((PALL_IMPORT_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrImpDlg_Title;
		break;

	case EXPORTP12_WIZARD_BASE :
		((PALL_EXPORT_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrExpDlg_Title;
		((PALL_EXPORT_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrExpDlg_Title;
		break;

	case IMPORTPROFILE_WIZARD_BASE :
		((PALL_IMPORTPROFILE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrExpProfileDlg_Title;
		((PALL_IMPORTPROFILE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrExpProfileDlg_Title;
		break;

	case EXPORTPROFILE_WIZARD_BASE :
		((PALL_EXPORTPROFILE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theDefWizardElems.tbstrWizTitle = m_pAppCtxt->theDefUIPrefs.tbstrExpProfileDlg_Title;
		((PALL_EXPORTPROFILE_WIZARDELEMENTS)(*o_ppvWizUIElements))->theCustWizardElems.tbstrWizTitle = m_pAppCtxt->theUIPrefs.tbstrExpProfileDlg_Title;
		break;

	default :
		retVal = E_INVALIDWIZARDFLAG;
		break;
	}

	return retVal;
}


HRESULT CVSPTA::_SetUIElems(int i_nWhichUI, void** o_ppvUIElements, _bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles, PIDLISTNODE i_pCertListHead, int i_nSelectedIdNum, BOOL i_boolOpenedWithPassword )
{
	HRESULT retVal = S_OK;
	int nCriteriaNum = 1;
	int nTempQuality;
	int nTempLength;
	//WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	//TCHAR tstrTemp[MAX_RES_STRING_SIZE];
			
	/*Depending upon the operation, allocate the right structure and
	fill it with the correct string*/
	switch(i_nWhichUI)
	{
	case OPENPROF_OPEN_BASE :
		*o_ppvUIElements = (void*)new(ALL_OPENPROF_UIELEMENTS);
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrProfName = m_pAppCtxt->theOpenProfParams.tbstrProfName;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->ptbstrProfList = i_ptbstrProfiles;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->nNumOfProfiles = i_nNumOfProfiles;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrPassword = ""; //Do not set the password when the ui is to be shown
		//if(m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag == DONOT_USE_PASSWORD)
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = FALSE;
		else
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = TRUE;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrOpenProf_Title;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrOpenProf_Title;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrOpenProf_Text;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrOpenProf_Text;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolIsUsernameEditable = m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable;
		break;

	case OPENPROF_CREATE_BASE :
		*o_ppvUIElements = (void*)new(ALL_OPENPROF_UIELEMENTS);
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrProfName = m_pAppCtxt->theOpenProfParams.tbstrProfName;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->ptbstrProfList = i_ptbstrProfiles;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->nNumOfProfiles = i_nNumOfProfiles;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword;
		switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = FALSE;
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = TRUE;
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = TRUE;
			retVal = _GetPasswdQualityString(&(((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}

		
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrNewPasswd_Title;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Title;
		if(i_nNumOfProfiles)
		{
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrNewPasswd_Text;
		}
		else
		{
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrNewPasswdNoProf_Text;
		}
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrNewPasswd_Text;
		((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolIsUsernameEditable = m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable;
		break;

	case CREATEPASSWD_BASE :
		*o_ppvUIElements = (void*)new(ALL_CREATEPASSWD_UIELEMENTS);
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrNewPassword = m_pAppCtxt->theCreatePasswdParams.tbstrNewPasswd;
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theCreatePasswdParams.tbstrConfPasswd;
		
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;

		/*
		switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = FALSE;
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			retVal = _GetPasswdQualityString(&(((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}
		*/
		
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrCreatePasswd_Title;
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Title;
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrCreatePasswd_Text;
		((PALL_CREATEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrCreatePasswd_Text;
		break;

	case ENTERPASSWD_BASE :
		*o_ppvUIElements = (void*)new(ALL_ENTERPASSWD_UIELEMENTS);
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrThePassword = m_pAppCtxt->theEnterPasswdParams.tbstrThePasswd;
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;

		/*
		switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = FALSE;
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			retVal = _GetPasswdQualityString(&(((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}
		*/
		
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrEnterPasswd_Title;
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Title;
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrEnterPasswd_Text;
		((PALL_ENTERPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrEnterPasswd_Text;
		break;

	case CHANGEPASSWD_BASE :
		*o_ppvUIElements = (void*)new(ALL_CHANGEPASSWD_UIELEMENTS);
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrOldPassword = m_pAppCtxt->theChangePasswdParams.tbstrOldPasswd;
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrNewPassword = m_pAppCtxt->theChangePasswdParams.tbstrNewPasswd;
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theChangePasswdParams.tbstrConfPasswd;
		
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowOldPassword = i_boolOpenedWithPassword;

		switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = FALSE;
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			retVal = _GetPasswdQualityString(&(((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}

		
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrChangePasswd_Title;
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Title;
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrChangePasswd_Text;
		((PALL_CHANGEPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrChangePasswd_Text;
		break;

	case SELID_BASE :
		*o_ppvUIElements = (void*)new(ALL_SELID_UIELEMENTS);
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->pCertListHead = i_pCertListHead;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->nSelectedIDFromList = i_nSelectedIdNum;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->boolShowChkBox = m_pAppCtxt->theUIPrefs.boolSelID_ShowDefChkBox;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrSelID_Title;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrSelID_Title;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrSelID_Text;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrSelID_Text;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrChkBoxText = m_pAppCtxt->theDefUIPrefs.tbstrSelID_ChkBoxText;
		((PALL_SELID_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrChkBoxText = m_pAppCtxt->theUIPrefs.tbstrSelID_ChkBoxText;
		break;

	case SIGNMSG_BASE :
		*o_ppvUIElements = (void*)new(ALL_REVWMSG_UIELEMENTS);
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->tbstrMsgToSign = (CHAR*)m_pAppCtxt->theSignMsgParams.pbyteMsgToSign;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrRvwMsg_Title;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Title;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrRvwMsg_Text;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrRvwMsg_Text;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->nSignTransDlgWidth = m_pAppCtxt->theUIPrefs.nSignTransDlgWidth;
		((PALL_REVWMSG_UIELEMENTS)(*o_ppvUIElements))->nSignTransDlgHeight = m_pAppCtxt->theUIPrefs.nSignTransDlgHeight;

		break;

	case INTRO_BASE :
		*o_ppvUIElements = (void*)new(ALL_INTRODLG_UIELEMENTS);
		((PALL_INTRODLG_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrIntroDlg_Title;
		((PALL_INTRODLG_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Title;
		((PALL_INTRODLG_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrIntroDlg_Text;
		((PALL_INTRODLG_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrIntroDlg_Text;
		break;

	case IMPORTP12_BASE :
		*o_ppvUIElements = (void*)new(ALL_IMPORTP12_UIELEMENTS);
		((PALL_IMPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrP12Passwd = m_pAppCtxt->theImportP12Params.tbstrP12Passwd;
		((PALL_IMPORTP12_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrImpP12_Title;
		((PALL_IMPORTP12_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrImpP12_Title;
		((PALL_IMPORTP12_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrImpP12_Text;
		((PALL_IMPORTP12_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrImpP12_Text;
		break;

	case EXPORTP12_BASE :
		*o_ppvUIElements = (void*)new(ALL_EXPORTP12_UIELEMENTS);
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrP12Passwd = m_pAppCtxt->theExportP12Params.tbstrP12Passwd;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrP12ConfPasswd = m_pAppCtxt->theExportP12Params.tbstrP12ConfPasswd;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrKeyFile = m_pAppCtxt->theExportP12Params.tbstrKeyFileOrBlob;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->boolShowFileName =  m_pAppCtxt->theExportP12Params.boolShowFileName;
		switch(m_pAppCtxt->theExportP12Params.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = FALSE;
			((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_OPENPROF_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = TRUE;
			((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->boolShowPassword = TRUE;

			nTempQuality = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality;
			nTempLength = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength;
			m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = m_pAppCtxt->theExportP12Params.nPasswordQuality;
			m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength = m_pAppCtxt->theExportP12Params.nPasswordLength;
			retVal = _GetPasswdQualityString(&(((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = nTempQuality;
			m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength = nTempLength;
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}

		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrExpP12_Title;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrExpP12_Title;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrExpP12_Text;
		((PALL_EXPORTP12_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrExpP12_Text;
		break;
	

	case GETSECRETQUESTION_BASE :
		*o_ppvUIElements = (void*)new(ALL_GETSECRETQUESTION_UIELEMENTS);
		((PALL_GETSECRETQUESTION_UIELEMENTS)(*o_ppvUIElements))->tbstrProfName = m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName;
		((PALL_GETSECRETQUESTION_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrGetSecretQuestion_Title;
		((PALL_GETSECRETQUESTION_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Title;
		((PALL_GETSECRETQUESTION_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrGetSecretQuestion_Text;
		((PALL_GETSECRETQUESTION_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Text;
		break;

	case RESETPASSWD_BASE :
		*o_ppvUIElements = (void*)new(ALL_RESETPASSWD_UIELEMENTS);
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrSecretQuestion = m_pAppCtxt->theResetPasswdParams.tbstrSecretQuestion;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrSecretAnswer = m_pAppCtxt->theResetPasswdParams.tbstrSecretAnswer;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrNewPassword = m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrConfirmPassword = m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd;
		
		switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
		{
		case PASSWDQUAL_REQUIRENOPASS:
			((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = FALSE;
			((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality = "";
			break;

		case PASSWDQUAL_OPTIONALPASS :
			((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			break;

		case PASSWDQUAL_ANYPASSWDOK :
		case PASSWDQUAL_NUMERICONLY :
		case  PASSWDQUAL_ALPHANUMERIC:
			((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->boolShowNewPassword = TRUE;
			retVal = _GetPasswdQualityString(&(((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->tbstrPasswordQuality) );
			break;

		default:
			retVal = E_INVALIDFLAGS;
			break;
		}

		
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrResetPasswd_Title;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Title;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrResetPasswd_Text;
		((PALL_RESETPASSWD_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Text;
		break;

	case CREATESECRET_BASE :
		*o_ppvUIElements = (void*)new(ALL_CREATESECRET_UIELEMENTS);
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->tbstrSecretQuestion = m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion;
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->tbstrSecretAnswer = m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer;
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrCreateSecret_Title;
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Title;
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrCreateSecret_Text;
		((PALL_CREATESECRET_UIELEMENTS)(*o_ppvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Text;
		break;

	default :
		retVal = E_INVALIDUIFLAG;
		break;
	}

	return retVal;

}

HRESULT CVSPTA::_CheckPasswordSanity(_bstr_t& i_tbstrPassword)
{
	HRESULT retVal = S_OK;

	//Check if the given password matches the password requirement
	switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
	{
	case PASSWDQUAL_REQUIRENOPASS :
		if(i_tbstrPassword.length() != 0) //This should never be true
			retVal = E_INVALIDPASSWD_NOPASSWDREQD;
		break;

	case PASSWDQUAL_OPTIONALPASS:
		//Any type of password is ok - so dont even bother checking anything.
		//Only check that it is non null if it is a roaming profile
		if(!i_tbstrPassword.length() && m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		{
			retVal = E_INVALIDPASSWD_PASSWDREQD;
		}
		break;

	case PASSWDQUAL_ANYPASSWDOK :
		//Just make sure that the length restrictions are met
		if(i_tbstrPassword.length() < (unsigned int)m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
		{
			if(i_tbstrPassword.length())
				retVal = E_INVALIDPASSWD_LESSTHANMINLENGTH;
			else
				retVal = E_INVALIDPASSWD_PASSWDREQD;
		}
		break;

	case PASSWDQUAL_NUMERICONLY :
		//Make sure that the length restrictions are met
		if(i_tbstrPassword.length() < (unsigned int)m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
		{
			if(i_tbstrPassword.length())
				retVal = E_INVALIDPASSWD_LESSTHANMINLENGTH;
			else
				retVal = E_INVALIDPASSWD_PASSWDREQD;
		}
		else
		{
			//Make sure that the password has only numbers
			WORD* pwCharTypes;
			pwCharTypes = new WORD[i_tbstrPassword.length()+1];
			if(!GetStringTypeEx(m_pAppCtxt->theDefUIPrefs.wLangID,CT_CTYPE1,(LPTSTR)i_tbstrPassword,
					-1,pwCharTypes))
					retVal = E_GETSTRINGTYPEFAILED;
			else
			{
				for(unsigned int i=0;i<i_tbstrPassword.length();++i)
				{
					if(!(pwCharTypes[i] & C1_DIGIT))
						retVal = E_INVALIDPASSWD_NOTNUMERICONLY;
				}
				
			}
			delete[] pwCharTypes;
		}
		break;

	case PASSWDQUAL_ALPHANUMERIC:
		//Make sure that the length restrictions are met
		if(i_tbstrPassword.length() < (unsigned int)m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
		{
			if(i_tbstrPassword.length())
				retVal = E_INVALIDPASSWD_LESSTHANMINLENGTH;
			else
				retVal = E_INVALIDPASSWD_PASSWDREQD;
		}
		else
		{
			//Count the number of numeric characters in the password
			WORD* pwCharTypes;
			int nNumOfDigits = 0;
			pwCharTypes = (WORD*)new WORD[i_tbstrPassword.length()+1];
			if(!GetStringTypeEx(m_pAppCtxt->theDefUIPrefs.wLangID,CT_CTYPE1,(LPTSTR)i_tbstrPassword,
					-1,pwCharTypes))
					retVal = E_GETSTRINGTYPEFAILED;
			else
			{
				for(unsigned int i=0;i<i_tbstrPassword.length();++i)
				{
					if(!(pwCharTypes[i] & (C1_ALPHA|C1_DIGIT|C1_PUNCT)))
						retVal = E_INVALIDPASSWD_INVALIDCHARS;
					else if((pwCharTypes[i] & C1_DIGIT))
					{
						nNumOfDigits++;
					}
				}
				

				//Make sure that the number of numeric characters matches the minimum required
				if(nNumOfDigits < ((m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_NOOFNUM_BASE) >> 8)) 
				{
					retVal = E_INVALIDPASSWD_LESSTHANMINNOOFNUM;
				}
				else
				{
					switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_POSOFNUM_BASE)
					{
					case PASSWDQUAL_ALPHANUMERIC_NOPOSREQS :
						break;

					case PASSWDQUAL_ALPHANUMERIC_NUMNOTATBEGIN :
						if(pwCharTypes[0] & C1_DIGIT)
							retVal = E_INVALIDPASSWD_NONUMATBEGIN;
						break;

					case PASSWDQUAL_ALPHANUMERIC_NUMNOTATEND :
					if(pwCharTypes[i_tbstrPassword.length() - 1] & C1_DIGIT)
						retVal = E_INVALIDPASSWD_NONUMATEND;
					break;


					case PASSWDQUAL_ALPHANUMERIC_NUMNOTATBEGINEND :
						if(pwCharTypes[0] & C1_DIGIT)
							retVal = E_INVALIDPASSWD_NONUMATBEGIN;
						else if(pwCharTypes[i_tbstrPassword.length() - 1] & C1_DIGIT)
							retVal = E_INVALIDPASSWD_NONUMATEND;
						break;
					}
				}

				delete[] pwCharTypes;
			}		
		}
		break;
	}

	return retVal;
}

HRESULT CVSPTA::_ExtractBstrsFromArray(SAFEARRAY* i_pSafeArray, int i_nDims, int i_nNumOfElemsInDim,_bstr_t* o_ptbstrBstrArr)
{
	HRESULT retVal = S_OK;
	LONG lIndices[2];

	lIndices[1] = i_nDims;
	VARIANT varElem;
	for(int i=1;i<=i_nNumOfElemsInDim;++i)
	{
		lIndices[0] = i;
		SafeArrayGetElement(i_pSafeArray,lIndices,(void*)&varElem);
		o_ptbstrBstrArr[i-1] = varElem.bstrVal;
	}
	return retVal;

}

HRESULT CVSPTA::get_VirtualSmartCardPtr(CVirtualSmartCard** o_ppVirtualSmartCard)
{
	*o_ppVirtualSmartCard = _gpVirtualSmartCard;
	return S_OK;
}

HRESULT CVSPTA::_CreateChallengeToBeSigned(_bstr_t& i_tbstrChallenge,PBYTE o_pbyteMessage, int* o_pnMsgToSignSize)
{
	HRESULT retVal = S_OK;
	PBYTE pbyteCurr = o_pbyteMessage;

	if(!o_pbyteMessage)
	{
		*o_pnMsgToSignSize = _bstr_t(PRECANNED_HEADER).length() + (i_tbstrChallenge.length()/2) + m_pAppCtxt->tbstrHostName.length();
	}
	else
	{
		_bstr_t tbstrPrecannedHeader(PRECANNED_HEADER);
		
		/*Copy the precanned header*/
		memcpy(pbyteCurr, (CHAR*)tbstrPrecannedHeader, tbstrPrecannedHeader.length());
		pbyteCurr = pbyteCurr+tbstrPrecannedHeader.length();

		/*Convert the challenge from ascii to hex*/
		if(!AscHexToBytes(i_tbstrChallenge, pbyteCurr))
			retVal = E_ASCHEXTTOBYTESFAILED;
		else
			pbyteCurr += (i_tbstrChallenge.length()/2);

		/*Copy the fqdn*/
		if(retVal == S_OK)
		{
			memcpy(pbyteCurr, (PBYTE)(CHAR*)m_pAppCtxt->tbstrHostName, m_pAppCtxt->tbstrHostName.length());
		}

//		VSPTA_CLEAN_TBSTR(tbstrPrecannedHeader)
	}

	return retVal;
}

HRESULT CVSPTA::_HandleSetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, CERTIDENTIFIER& i_theCertIdentifier, 
			_bstr_t& i_tbstrPrefName, _bstr_t i_tbstrPrefVal)
{
	HRESULT retVal = S_OK;
	
	/*Call the engine to perform this operation*/
	retVal = m_pPtaEngine->SetCertPref(i_pVirtualSmartCard,i_theCertIdentifier.tbstrCertIssDN, i_theCertIdentifier.tbstrCertSerNum,
		i_tbstrPrefName, i_tbstrPrefVal);
	return retVal;
}

HRESULT CVSPTA::_HandleGetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, CERTIDENTIFIER& i_theCertIdentifier, 
			_bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal)
{
	HRESULT retVal = S_OK;
	/*Call the engine to perform this operation*/
	retVal = m_pPtaEngine->GetCertPref(i_pVirtualSmartCard,i_theCertIdentifier.tbstrCertIssDN, i_theCertIdentifier.tbstrCertSerNum,
		i_tbstrPrefName, o_ptbstrPrefVal);
	return retVal;
}



HRESULT CVSPTA::_OpenProfWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	BOOL boolOrigPasswdUsage;

	//We need a password to open the profile
	/*if(!io_theOpCtxt.boolFromUI)
	{
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;
	}*/

	//If only one profile is found on the machine and the script has not specified 
	//a profile name try to open this profile.
	if((!m_pAppCtxt->theOpenProfParams.tbstrProfName.length()))
	{
		if(io_theOpCtxt.nNumOfProfiles== 1)
		{
			m_pAppCtxt->theOpenProfParams.tbstrProfName = io_theOpCtxt.ptbstrProfiles[0];
		}
		else if(io_theOpCtxt.nNumOfProfiles > 1)
		{	//If more than one profile is found then we need to show the ui.
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
			return retVal;
		}
		else if(io_theOpCtxt.nNumOfProfiles == 0 && m_pAppCtxt->theOpenProfParams.boolRoamProfile)
		{
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
			return retVal;
		}
		
	}

	//If we are not coming from the ui then before we want to try and open without a password
	//If we get an invalid password, then we want to try and show a ui. If we are coming from
	//the ui then we want to try and open the profile with the supplied password. If the password
	//is invalide we will return an error.
	if(!io_theOpCtxt.boolFromUI)
	{
		boolOrigPasswdUsage = m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag;
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = DONOT_USE_PASSWORD;
	}

	
	/*Try to open the profile*/
	retVal = _HandleOpenProfile(io_theOpCtxt.ptbstrProfiles, io_theOpCtxt.nNumOfProfiles, &(io_theOpCtxt.pOParams->pVirtualSmartCard));

	if(!io_theOpCtxt.boolFromUI)
	{
		/*if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
			m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = DONOT_USE_PASSWORD ;
		else 
			m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;*/
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = boolOrigPasswdUsage;
	}
	
	//Handle the return code
	switch(retVal)
	{
	case E_INVALIDPASSWD_PASSWDREQD :
		//If the script specified not to use the password then we need to return an
		//error or else we need to ask for the password i.e. show a ui.
		if(io_theOpCtxt.boolFromUI || m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality != PASSWDQUAL_REQUIRENOPASS)
		{
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
			retVal = S_OK;
		}
		break;

	case E_INVALIDPASSWD :
		retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
		io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
		break;

	case E_PROFLOCKEDOUT :
		if(io_theOpCtxt.boolFromUI)
		{
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
		}
		break;

	case E_PROFDOESNOTEXIST :
		//Since the profile does not exist, depending upon the flag we want to either
		//return an error or try to create the profile.
		switch(m_pAppCtxt->theOpenProfParams.nFlag)
		{
		case OPENPROF_OPEN_ONLY :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(OPEN_PROF_DOES_NOT_EXIST);
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
			}
			break;

		case OPENPROF_OPEN_ALWAYS:
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ConfirmAction(OPEN_PROF_CREATE);

			}
			else
			{
				retVal = S_OK;
			}
			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_CREATE_ONLY;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
				retVal = S_OK;
			}
			
			break;
		
		
		default :
			break;
		}

	case S_OK :
		//Profile has been opened. Record if it is opened with or without a password
		//if(m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag  == DONOT_USE_PASSWORD)
		if(!io_theOpCtxt.boolFromUI || m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag  == DONOT_USE_PASSWORD)
			io_theOpCtxt.boolOpenedWithPassword = FALSE;
		else
			io_theOpCtxt.boolOpenedWithPassword = TRUE;
		break;

	default:
			break;

	}	

	return retVal;
}


HRESULT CVSPTA::_OpenProfWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	VARIANT varAppCtxt;
	VARIANT varUsername;
	VARIANT varPasswd;
	VARIANT varPurpose;
	VARIANT varPasswdQuality;
	LPFNGetUsernamePasswd pfnGetUsernamePasswd = NULL;
	LPFNProcessEvent pfnProcessEvent = NULL;
	
	/*Obtain the profile name and password from the auth dll*/
	varPurpose.vt = VT_I2;
	varPurpose.iVal = AUTHDLL_OPENPROF;
	varAppCtxt.vt = VT_BSTR;
	varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
	varPasswdQuality.vt = VT_EMPTY;
	varPasswd.vt = VT_EMPTY;
	varUsername.vt = VT_BSTR;
	varUsername.bstrVal = m_pAppCtxt->theOpenProfParams.tbstrProfName.copy();

	pfnGetUsernamePasswd = (LPFNGetUsernamePasswd)GetProcAddress(m_pAppCtxt->hModAuthDll,"GetUsernamePasswd");
	if(!pfnGetUsernamePasswd)
	{
		retVal = E_GETPROCADDRFAILED;
	}

	pfnProcessEvent = (LPFNProcessEvent)GetProcAddress(m_pAppCtxt->hModAuthDll,"ProcessEvent");
	if(!pfnProcessEvent)
	{
		retVal = E_GETPROCADDRFAILED;
	}

	if(retVal == S_OK)
	{
		retVal = pfnGetUsernamePasswd(&varPurpose, &varAppCtxt, &varPasswdQuality, &varUsername, &varPasswd, NULL);
	}
	
	if(retVal == S_OK)
	{
		if(varPasswd.vt == VT_BSTR)
		{
			m_pAppCtxt->theOpenProfParams.tbstrPassword = varPasswd.bstrVal;
		}
		else if(varPasswd.vt == VT_ARRAY)
		{
			PBYTE pbytePasswordHash;
			long lLBound;
			long lUBound;
			long lSize;

			if(SafeArrayGetDim(varPasswd.parray) != 1)
				retVal = E_AUTHDLL_INVALIDDIMS;
			
			if(retVal == S_OK)
			{
				retVal = SafeArrayGetLBound(varPasswd.parray, 1,&lLBound);
			}
				
			if(retVal == S_OK)
			{
				retVal = SafeArrayGetUBound(varPasswd.parray,1, &lUBound);
			}

			if(retVal == S_OK)
			{
				lSize = lUBound - lLBound + 1;
				retVal = SafeArrayAccessData(varPasswd.parray, (void HUGEP**)&(pbytePasswordHash));
			}

			if(retVal == S_OK)
			{
				if(!BytesToAscHex(pbytePasswordHash,lSize,m_pAppCtxt->theOpenProfParams.tbstrPassword))
					retVal = E_FAIL;
			}
				
			
		}
		else
		{
			retVal = E_INVALIDARGS;
		}

	}
	
	if(retVal == S_OK)
	{
		m_pAppCtxt->theOpenProfParams.tbstrProfName = varUsername.bstrVal;
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;
	}
	

	if(retVal == S_OK)
	{
		retVal = _HandleOpenProfile(io_theOpCtxt.ptbstrProfiles, io_theOpCtxt.nNumOfProfiles, &(io_theOpCtxt.pOParams->pVirtualSmartCard));
	}

	VARIANT varEvent;
	varEvent.vt = VT_I2;

		//Handle the return code
	switch(retVal)
	{
	case E_INVALIDPASSWD_PASSWDREQD :
		//If the script specified not to use the password then we need to return an
		//error or else we need to ask for the password i.e. show a ui.
		//io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
		//retVal = S_OK;
		*o_pboolParamFlagsChanged = TRUE;
		retVal = S_OK;
		break;

	case E_INVALIDPASSWD :
		//TODO : Ask the auth dll to show some message.
		//retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
		varEvent.iVal = retVal & 0x0000FFFF;
		retVal = pfnProcessEvent(&varEvent);

		//io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
		*o_pboolParamFlagsChanged = TRUE;
		retVal = S_OK;
		break;

	case E_PROFLOCKEDOUT :
		//TODO : Ask the auth dll to show some message.
		//retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
		varEvent.iVal = retVal & 0x0000FFFF;
		retVal = pfnProcessEvent(&varEvent);

		//io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
		*o_pboolParamFlagsChanged = TRUE;
		retVal = S_OK;
		break;

	case E_PROFDOESNOTEXIST :
		//Since the profile does not exist, depending upon the flag we want to either
		//return an error or try to create the profile.
		switch(m_pAppCtxt->theOpenProfParams.nFlag)
		{
		case OPENPROF_OPEN_ONLY :
			//TODO : Ask the auth dll to show some message.
			//retVal = m_pPtaUI->ShowMessage(OPEN_PROF_DOES_NOT_EXIST);
			varEvent.iVal = OPEN_PROF_DOES_NOT_EXIST;
			retVal = pfnProcessEvent(&varEvent);

			//io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
			*o_pboolParamFlagsChanged = TRUE;
			retVal = S_OK;
			break;

		case OPENPROF_OPEN_ALWAYS:
			//TODO : Ask the auth dll to show some message.
			//retVal = m_pPtaUI->ConfirmAction(OPEN_PROF_CREATE);
			varEvent.iVal = OPEN_PROF_CREATE;
			retVal = pfnProcessEvent(&varEvent);

			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_CREATE_ONLY;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_OPEN_BASE;
				retVal = S_OK;
			}
			
			break;
		
		
		default :
			break;
		}

	case S_OK :
		//Profile has been opened. Record if it is opened with or without a password
		//if(m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag  == DONOT_USE_PASSWORD)
		io_theOpCtxt.boolOpenedWithPassword = TRUE;
		break;

	default:
			break;

	}	

	if(varUsername.bstrVal)
	{
		SysFreeString(varUsername.bstrVal);
	}

	if(varPasswd.vt == VT_BSTR && varPasswd.bstrVal)
	{
		SysFreeString(varPasswd.bstrVal);
	}

	if(varPasswd.vt == VT_ARRAY && varPasswd.parray)
	{
		SafeArrayDestroy(varPasswd.parray);
	}
	
	if(varAppCtxt.bstrVal)
	{
		SysFreeString(varAppCtxt.bstrVal);
	}

	return retVal;
}

HRESULT CVSPTA::_CreateProfWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];

	if((!m_pAppCtxt->theOpenProfParams.tbstrProfName.length()))
	{
		//If the profile name is not specified, we need to show the ui.
		io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
		return retVal;
	}
	
	/*Try to create the profile*/
	retVal = _HandleCreateProfile(&(io_theOpCtxt.ptbstrProfiles),&(io_theOpCtxt.nNumOfProfiles), &(io_theOpCtxt.pOParams->pVirtualSmartCard));
	switch(retVal)
	{

	case S_OK :
		//A profile has been created. This means we will not show anymore uis
		//io_theOpCtxt.nWizardAndUIs = 0;
		if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality == PASSWDQUAL_REQUIRENOPASS)
			io_theOpCtxt.boolOpenedWithPassword = FALSE;
		else
			io_theOpCtxt.boolOpenedWithPassword = TRUE;
		retVal = E_PROFCREATED;
		break;

	case E_INVALIDPASSWD_PASSWDREQD :
		//We need to show the ui because we need a password
		io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
		retVal = S_OK;
		break;

	case E_INVALIDPASSWD_NOPASSWDREQD :
	case E_INVALIDPASSWD_LESSTHANMINLENGTH :
	case E_INVALIDPASSWD_NOTNUMERICONLY :
	case E_INVALIDPASSWD_INVALIDCHARS :
	case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
	case E_INVALIDPASSWD_NONUMATBEGIN :
	case E_INVALIDPASSWD_NONUMATEND :
		if(io_theOpCtxt.boolFromUI)
		{
			m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
			m_pAppCtxt->theOpenProfParams.tbstrPassword  = "";

			//Create the string to be displayed 
			retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrMessageToDisplay = wstrTemp;
			}

			if(retVal == S_OK)
			{
				retVal = _GetPasswdQualityString(&tbstrPasswdQualString);
			}

			if(retVal == S_OK)
			{
				tbstrMessageToDisplay += tbstrPasswdQualString;

				//Display it.
				VARIANT varMsgToDisplay;
				varMsgToDisplay.vt = VT_BSTR;
				varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

				retVal = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
			}

			if(retVal == S_OK)
			{
				retVal = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
			}
		}

		break;
	case E_CONFIRMPASSWORDNOMATCH :
		if(io_theOpCtxt.boolFromUI)
		{
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
			m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = "";
		}
		break;

	case E_PROFEXISTS : //Profile exists
		switch(m_pAppCtxt->theOpenProfParams.nFlag)
		{
		case OPENPROF_CREATE_ONLY :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(CREATE_PROF_EXISTS);
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
			}
			break;
	
		case OPENPROF_CREATE_ALWAYS :
			//Try to delete and then recreate the profile.
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ConfirmAction(CREATE_PROF_DELETE);
			}
			else
			{
				retVal = S_OK;
			}

			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_DELETE_RECREATE;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
				retVal = S_OK;
			}
			
			break;

		case OPENPROF_CREATE_OR_OPEN:
			//Try to open the profile
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ConfirmAction(CREATE_PROF_OPEN);
			}
			else
			{
				retVal = S_OK;
			}

			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_OPEN_ONLY;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
				retVal = S_OK;
			}
			
			break;

		default:
			break;
			
		}

	}

//	VSPTA_CLEAN_TBSTR(tbstrPasswdQualString)

	return retVal;
}

HRESULT CVSPTA::_CreateProfWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged) 
{
	HRESULT retVal = S_OK;
	VARIANT varUsername;
	VARIANT varPasswd;
	VARIANT varAppCtxt;
	VARIANT varPasswordQuality;
	VARIANT varPurpose;
	LPFNGetUsernamePasswd pfnGetUsernamePasswd = NULL;
	LPFNProcessEvent pfnProcessEvent = NULL;

	/*Get the username and the password for the new profile*/
	varPurpose.vt = VT_I2;
	varPurpose.iVal = AUTHDLL_CREATEPROF;
	varAppCtxt.vt = VT_BSTR;
	varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
	varPasswordQuality.vt = VT_I2;
	varPasswordQuality.iVal = m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality;

	varUsername.vt = VT_BSTR;
	varUsername.bstrVal = m_pAppCtxt->theOpenProfParams.tbstrProfName.copy();
	varPasswd.vt = VT_EMPTY;	

	pfnGetUsernamePasswd = (LPFNGetUsernamePasswd)GetProcAddress(m_pAppCtxt->hModAuthDll,"GetUsernamePasswd");
	if(!pfnGetUsernamePasswd)
	{
		retVal = E_GETPROCADDRFAILED;
	}

	pfnProcessEvent = (LPFNProcessEvent)GetProcAddress(m_pAppCtxt->hModAuthDll,"ProcessEvent");
	if(!pfnProcessEvent)
	{
		retVal = E_GETPROCADDRFAILED;
	}

	if(retVal == S_OK)
	{
 			retVal = pfnGetUsernamePasswd(&varPurpose, &varAppCtxt, &varPasswordQuality, &varUsername, &varPasswd, NULL);
	}

	if(retVal == S_OK)
	{
		if(varPasswd.vt == VT_BSTR)
		{
			m_pAppCtxt->theOpenProfParams.tbstrPassword = varPasswd.bstrVal;
			
		}
		else if(varPasswd.vt == VT_ARRAY)
		{
			PBYTE pbytePasswordHash;
			long lLBound;
			long lUBound;
			long lSize;

			if(SafeArrayGetDim(varPasswd.parray) != 1)
				retVal = E_AUTHDLL_INVALIDDIMS;
			
			if(retVal == S_OK)
			{
				retVal = SafeArrayGetLBound(varPasswd.parray, 1,&lLBound);
			}
				
			if(retVal == S_OK)
			{
				retVal = SafeArrayGetUBound(varPasswd.parray,1, &lUBound);
			}

			if(retVal == S_OK)
			{
				lSize = lUBound - lLBound + 1;
				retVal = SafeArrayAccessData(varPasswd.parray, (void HUGEP**)&(pbytePasswordHash));
			}

			if(retVal == S_OK)
			{
				if(!BytesToAscHex(pbytePasswordHash,lSize,m_pAppCtxt->theOpenProfParams.tbstrPassword))
					retVal = E_FAIL;
			}
				
			
		}
		else
		{
			retVal = E_INVALIDARGS;
		}

	}

	if(retVal == S_OK)
	{
		m_pAppCtxt->theOpenProfParams.tbstrConfirmPassword = m_pAppCtxt->theOpenProfParams.tbstrPassword;
		m_pAppCtxt->theOpenProfParams.tbstrProfName = varUsername.bstrVal;
		m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = PASSWDQUAL_OPTIONALPASS;
		m_pAppCtxt->theOpenProfParams.nPasswordUsageFlag = ~DONOT_USE_PASSWORD;
	}
		
	/*Try to create the profile*/
	if(retVal == S_OK)
	{
		retVal = _HandleCreateProfile(&(io_theOpCtxt.ptbstrProfiles),&(io_theOpCtxt.nNumOfProfiles), &(io_theOpCtxt.pOParams->pVirtualSmartCard));
		if(retVal == S_OK)
		{
			io_theOpCtxt.boolOpenedWithPassword = TRUE;
		}
	}
	
	VARIANT varEvent;
	varEvent.vt = VT_I2;

	switch(retVal)
	{

	case S_OK :
		//A profile has been created. This means we will not show anymore uis
		//io_theOpCtxt.nWizardAndUIs = 0;
		io_theOpCtxt.boolOpenedWithPassword = TRUE;
		retVal = E_PROFCREATED;
		break;

	case E_INVALIDPASSWD_PASSWDREQD :
		//We need to show the ui because we need a password
		//io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
		*o_pboolParamFlagsChanged = TRUE;
		retVal = S_OK;
		break;


	case E_PROFEXISTS : //Profile exists
		switch(m_pAppCtxt->theOpenProfParams.nFlag)
		{
		case OPENPROF_CREATE_ONLY :	
			//retVal = m_pPtaUI->ShowMessage(CREATE_PROF_EXISTS);
			varEvent.iVal = CREATE_PROF_EXISTS;
			retVal = pfnProcessEvent(&varEvent);

			//io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
			*o_pboolParamFlagsChanged = TRUE;
			retVal = S_OK;
		
			break;
	
		case OPENPROF_CREATE_ALWAYS :
			//Try to delete and then recreate the profile.
			//retVal = m_pPtaUI->ConfirmAction(CREATE_PROF_DELETE);
			varEvent.iVal = CREATE_PROF_DELETE;
			retVal = pfnProcessEvent(&varEvent);

			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_DELETE_RECREATE;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				//io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
				//retVal = S_OK;
				*o_pboolParamFlagsChanged = TRUE;
				retVal = S_OK;
			}
			
			break;

		case OPENPROF_CREATE_OR_OPEN:
			//Try to open the profile
			//retVal = m_pPtaUI->ConfirmAction(CREATE_PROF_OPEN);
			varEvent.iVal = CREATE_PROF_OPEN;
			retVal = pfnProcessEvent(&varEvent);

			if(retVal == S_OK)
			{
				m_pAppCtxt->theOpenProfParams.nFlag = OPENPROF_OPEN_ONLY;
				*o_pboolParamFlagsChanged = TRUE;
			}
			else
			{
				//io_theOpCtxt.nWizardAndUIs |= OPENPROF_CREATE_BASE;
				//retVal = S_OK;
				*o_pboolParamFlagsChanged = TRUE;
				retVal = S_OK;
			}
			
			break;

		default:
			break;
			
		}

	}

	m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality = varPasswordQuality.iVal;

	if(varUsername.bstrVal)
	{
		SysFreeString(varUsername.bstrVal);
	}

	if(varPasswd.vt == VT_BSTR && varPasswd.bstrVal)
	{
		SysFreeString(varPasswd.bstrVal);
	}

	if(varPasswd.vt == VT_ARRAY && varPasswd.parray)
	{
		SafeArrayDestroy(varPasswd.parray);
	}
	
	if(varAppCtxt.bstrVal)
	{
		SysFreeString(varAppCtxt.bstrVal);
	}

	return retVal;
}

///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_GetSecretQuestionWithPTAAuth
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function retrieves secret question corresponding to user's roaming profile
//						from the roaming server
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_GetSecretQuestionWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;

	/*Try to get the profile*/
	retVal = _HandleGetSecretQuestion();

	//Handle the return code
	switch(retVal)
	{
	case E_GETSECRET_PROFILEREQD :
		io_theOpCtxt.nWizardAndUIs |= GETSECRETQUESTION_BASE;
		retVal = S_OK;
		if(io_theOpCtxt.boolFromUI)
		{
			retVal = m_pPtaUI->ShowMessage(E_GETSECRET_PROFILEREQD & 0x0000FFFF);
		}
		break;

	case E_GETSECRET_PROFDOESNOTEXIST :
		if(io_theOpCtxt.boolFromUI)
		{
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= GETSECRETQUESTION_BASE;
		}
		break;

	case S_OK:
			break;

	default:
			break;

	}

	return retVal;
	
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_ResetPasswdWithPTAAuth
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function resets password for user's roaming profile
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_ResetPasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;
	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	_bstr_t tbstrMessageToDisplay = "";
	_bstr_t tbstrPasswdQualString = "";


	do
	{
		if((!m_pAppCtxt->theResetPasswdParams.tbstrProfName.length()))
		{
			//If the profile name is not specified, we need to show the ui.
			m_pAppCtxt->theResetPasswdParams.tbstrProfName = m_pAppCtxt->theGetSecretQuestionParams.tbstrProfName;
			m_pAppCtxt->theResetPasswdParams.tbstrSecretQuestion = m_pAppCtxt->theGetSecretQuestionParams.tbstrSecretQuestion;
			io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
			return retVal;
		}

		retVal = _HandleResetPasswd(&(io_theOpCtxt.pOParams->pVirtualSmartCard));

		switch(retVal)
		{
		case E_RESETPASSWD_WRONGANSWER :
			//We need to show the ui because we need a password/answer
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
			}
			break;

		case E_RESETPASSWD_ANSWERPASSWDREQD :
			//We need to show the ui because we need a password/answer
			if(io_theOpCtxt.boolFromUI)
			{
				m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = "";

				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
			}
			break;

		case E_INVALIDPASSWD_NOPASSWDREQD :
		case E_INVALIDPASSWD_LESSTHANMINLENGTH :
		case E_INVALIDPASSWD_NOTNUMERICONLY :
		case E_INVALIDPASSWD_INVALIDCHARS :
		case E_INVALIDPASSWD_LESSTHANMINNOOFNUM :
		case E_INVALIDPASSWD_NONUMATBEGIN :
		case E_INVALIDPASSWD_NONUMATEND :
			if(io_theOpCtxt.boolFromUI)
			{
				m_pAppCtxt->theResetPasswdParams.tbstrNewPasswd = "";
				m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = "";

				//Create the string to be displayed 
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWDQUALERRINTRO,wstrTemp, MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					tbstrMessageToDisplay = wstrTemp;
				}

				if(retVal == S_OK)
				{
					retVal = _GetPasswdQualityString(&tbstrPasswdQualString);
				}

				if(retVal == S_OK)
				{
					tbstrMessageToDisplay += tbstrPasswdQualString;

					//Display it.
					VARIANT varMsgToDisplay;
					varMsgToDisplay.vt = VT_BSTR;
					varMsgToDisplay.bstrVal = tbstrMessageToDisplay;

					retVal = m_pPtaUI->put_NextMessageToShow(&varMsgToDisplay);
				}

				if(retVal == S_OK)
				{
					retVal = m_pPtaUI->ShowMessage(SHOW_SET_MSG);
					io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
				}
			}

			break;
		case E_CONFIRMPASSWORDNOMATCH :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
				m_pAppCtxt->theResetPasswdParams.tbstrConfPasswd = "";
			}
			break;

		case E_INVALIDPASSWD :
			retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
			io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
			break;

		case E_RESETPASSWD_PROFLOCKOUT :
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= RESETPASSWD_BASE;
			}
			break;

		default :
			break;

		}

	}while(0);
	
	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_CreateSecretWithPTAAuth
//
//	Parameters
//				io_theOpCtxt: I/O - contains operation context
//				o_pboolParamFlagsChanged: Output parameter - indicates if new operation flags are added
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function check the secret question and answer to see if they 
//						are not blank.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CVSPTA::_CreateSecretWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged)
{
	HRESULT retVal = S_OK;

	do
	{
		if((!m_pAppCtxt->theCreateSecretParams.tbstrProfName.length()))
		{
			//If the profile name is not specified, we need to show the ui.
			m_pAppCtxt->theCreateSecretParams.tbstrProfName = m_pAppCtxt->theOpenProfParams.tbstrProfName;
			io_theOpCtxt.nWizardAndUIs |= CREATESECRET_BASE;
			return retVal;
		}

		retVal = _HandleCreateSecret();

			// Check if we got all the info that we need to create a roaming profile
		if(retVal == S_OK)
		{

			// update profile with secret question and answer. This info will be sent to roaming server
			// when the profile is saved.
			m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard->put_VSM_RoamProfSecretQuestion(m_pAppCtxt->theCreateSecretParams.tbstrSecretQuestion);
			m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard->put_VSM_RoamProfSecretAnswer(m_pAppCtxt->theCreateSecretParams.tbstrSecretAnswer);

			// Store the smartcard pointer in io_theOpCtxt structure in order for other operations to proceed
			io_theOpCtxt.pOParams->pVirtualSmartCard = m_pAppCtxt->theCreateSecretParams.pVirtualSmartCard;
		}

		switch(retVal)
		{
		case E_CREATESECRET_SECRETREQD :
			//We need to show the ui because we need a password
			if(io_theOpCtxt.boolFromUI)
			{
				retVal = m_pPtaUI->ShowMessage(retVal & 0x0000FFFF);
				io_theOpCtxt.nWizardAndUIs |= CREATESECRET_BASE;
			}

			break;

		default :
			break;

		}


	}while(0);
	
	return retVal;
}

STDMETHODIMP CVSPTA::ProfMgmt_SaveProfile()
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context and this is
	non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE|CHECK_PROF);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Save the smart card*/
	retVal = _gpVirtualSmartCard->VSM_Save(); 

	return retVal;
}


HRESULT PasswordCallback (void* i_pvoidPTAObj, void* i_pvoidPointer, _VS_CHAR*	o_cszPassword)
{
	HRESULT retVal = S_OK;
	CVSPTA* pThePTAObj = (CVSPTA*)i_pvoidPTAObj;
	int nUIToShow = *((int*)i_pvoidPointer);
	//retVal = pThePTAObj->_PasswordCallback(nUIToShow, o_cszPassword);
	retVal = _gpCurrPTA->_PasswordCallback(nUIToShow, o_cszPassword);
	return	retVal;
}


STDMETHODIMP CVSPTA::ProfMgmt_ChangePassword()
{
	HRESULT retVal = S_OK;
	
	/*Check if we are initialized and this is non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	m_pAppCtxt->theChangePasswdParams.boolUseNewPasswd = m_pAppCtxt->theChangePasswdParams.boolUseOldPasswd = FALSE;

	retVal = _DoOperation(LOGIN_WIZARD_BASE,CHANGEPASSWD_BASE);

	return retVal;
}


HRESULT CVSPTA::_PasswordCallback (int i_nUIToShow, _VS_CHAR*	o_cszPassword)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrTimeoutPasswd = "";

	/*CPtaUI thePtaUI;
	PUICTXT pUICtxt = NULL;
	OPCTXT theOpCtxt;
	theOpCtxt.pOParams = new (OPARAMS);
	theOpCtxt.pOParams->tbstrTimeOutPasswd = "";
	theOpCtxt.pvThePTAUIObj = (void*)&thePtaUI;
	theOpCtxt.pvThePtaObj = (void*)this;*/

	do
	{
		if ( NULL == _gpVirtualSmartCard )
		{
			retVal =	E_OPT_FAILED_DUE_TO_TIMEOUT;
			break;
		}

		/*If the profile has been opened without a password then we just return an empty string*/
		if(!_gboolOpenedWithPassword)
		{
			memcpy
			(
				(BYTE*)o_cszPassword,			
				(const BYTE*)L"",
				sizeof (_VS_CHAR)
			);		
			break;
		}

		if(m_pAppCtxt->hModAuthDll)
		{
			retVal = _SetPasswdWithAuthDll(i_nUIToShow, &tbstrTimeoutPasswd);
		}
		else
		{
			retVal = _SetPasswdWithPTAAuth(i_nUIToShow, &tbstrTimeoutPasswd);
		}

		if(retVal != S_OK)
			break;


		/*Extract the password and return it*/
		memcpy
		(
			(BYTE*)o_cszPassword,			
			//(const BYTE*)(WCHAR*)theOpCtxt.pOParams->tbstrTimeOutPasswd,
			//(theOpCtxt.pOParams->tbstrTimeOutPasswd.length() + 1) * sizeof (_VS_CHAR)
			(const BYTE*)(WCHAR*)tbstrTimeoutPasswd,
			(tbstrTimeoutPasswd.length() + 1) * sizeof (_VS_CHAR)
		);		

	}while(0);

	
	return retVal;

}

HRESULT CVSPTA::_SetPasswdWithPTAAuth(int i_nUIToShow, _bstr_t* o_ptbstrTimeoutPasswd)
{
	HRESULT retVal = S_OK;
	
	CPtaUI thePtaUI;
	PUICTXT pUICtxt = NULL;
	OPCTXT theOpCtxt;
	theOpCtxt.pOParams = new (OPARAMS);
	theOpCtxt.pOParams->tbstrTimeOutPasswd = "";
	theOpCtxt.pvThePTAUIObj = (void*)&thePtaUI;
	theOpCtxt.pvThePtaObj = (void*)this;

	do
	{
		/*Create a new ui context*/
		pUICtxt = _CreateUIContext();
		if(!pUICtxt)
		{
			retVal = E_FAIL;
			break;
		}

		/*Initialize the ui context*/
		int nOrigOKBtnText;
		int nOrigDefOKBtnText;
		bool boolOrigIsUsernameEditable;

		nOrigOKBtnText = m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText;
		nOrigDefOKBtnText = m_pAppCtxt->theDefUIPrefs.nOpenProf_OKBtnText;
		boolOrigIsUsernameEditable = m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable;

		m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText = m_pAppCtxt->theUIPrefs.nTimeOut_OKBtnText;
		m_pAppCtxt->theDefUIPrefs.nOpenProf_OKBtnText = m_pAppCtxt->theDefUIPrefs.nTimeOut_OKBtnText;
		m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable = FALSE;

		retVal = _InitializeUIContext(pUICtxt, OPENPROF_OPEN_BASE, OPENPROF_OPEN_BASE, NULL , 0 , NULL, 0, 0);
		if(retVal!= S_OK)
			break;

		m_pAppCtxt->theUIPrefs.nOpenProf_OKBtnText = nOrigOKBtnText;
		m_pAppCtxt->theDefUIPrefs.nOpenProf_OKBtnText = nOrigDefOKBtnText;
		m_pAppCtxt->theOpenProfParams.boolIsUsernameEditable = boolOrigIsUsernameEditable;

		/*Pickle the ui context for timeout and the profile name*/
		VARIANT varProfPathName;
		BSTR bstrProfName;
		BSTR bstrAppCtxtName;
		BSTR bstrPath;

		retVal = _gpVirtualSmartCard->get_VSM_ProfileName(&varProfPathName);
		if(retVal!= S_OK)
			break;

		retVal = ParseProfile_Path_Name
		(
			_bstr_t(varProfPathName.bstrVal),
			&bstrProfName,
			&bstrPath,
			&bstrAppCtxtName
		);
		if(retVal!= S_OK)
			break;

		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrProfName = bstrProfName;
		SysFreeString(varProfPathName.bstrVal);
		SysFreeString(bstrProfName);
		SysFreeString(bstrPath);
		SysFreeString(bstrAppCtxtName);

		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->tbstrPassword = ""; //Do not set the password when the ui is to be shown
		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->boolShowPassword = TRUE;

		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle = m_pAppCtxt->theDefUIPrefs.tbstrTimeOut_Title;
		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle = m_pAppCtxt->theUIPrefs.tbstrTimeOut_Title;
		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->theDefUIElements.tbstrText = m_pAppCtxt->theDefUIPrefs.tbstrTimeOut_Text;
		((PALL_OPENPROF_UIELEMENTS)(pUICtxt->pvUIElements))->theCustUIElements.tbstrText = m_pAppCtxt->theUIPrefs.tbstrTimeOut_Text;

		pUICtxt->pbtnFns->lpfnBtn1Fn = TimeoutFn;
		pUICtxt->pbtnFns->lpfnBtn2Fn = TimeoutCancelFn;
		pUICtxt->pbtnFns->lpfnBtn3Fn = TimeoutHelpFn;

		retVal = thePtaUI.put_UIContext(pUICtxt);
		if(retVal != S_OK)
			break;

		/*Show the ui*/
		if(!i_nUIToShow)
		{
			retVal = thePtaUI.ShowUI(&theOpCtxt);
		}
		else
		{
			retVal = thePtaUI.ShowMessage(i_nUIToShow);
		}
		

		if(retVal == E_PASSWORDPROVIDED)
			retVal = S_OK;

		if(retVal != S_OK)
			break;

		*o_ptbstrTimeoutPasswd = theOpCtxt.pOParams->tbstrTimeOutPasswd;

	}while(0);

	if(pUICtxt)
		_FreeUIContext(pUICtxt);

	delete (theOpCtxt.pOParams);

	return retVal;
}

HRESULT CVSPTA::_SetPasswdWithAuthDll(int i_nUIToShow, _bstr_t* o_ptbstrTimeoutPasswd)
{
	HRESULT retVal = S_OK;
	VARIANT varUsername;
	VARIANT varPasswd;
	VARIANT varAppCtxt;
	VARIANT varPasswordQuality;
	VARIANT varPurpose;
	LPFNGetUsernamePasswd pfnGetUsernamePasswd = NULL;
	LPFNProcessEvent pfnProcessEvent = NULL;
	BSTR bstrUserName = NULL; 
	BSTR bstrPath = NULL;
	BSTR bstrApContext = NULL;

	/*Get the username and the password for the new profile*/
	varPurpose.vt = VT_I2;
	varPurpose.iVal = AUTHDLL_UNLOCK;
	varAppCtxt.vt = VT_BSTR;
	varAppCtxt.bstrVal = m_pAppCtxt->tbstrAppCtxtName.copy();
	varPasswordQuality.vt = VT_EMPTY;
	varPasswd.vt = VT_EMPTY;	
	
	do
	{
		//Get the username from the virtual smartcard
		retVal = _gpVirtualSmartCard->get_VSM_ProfileName(&varUsername);
		if(retVal != S_OK)
			break;

		retVal = ParseProfile_Path_Name(varUsername.bstrVal,&bstrUserName,&bstrPath,&bstrApContext); 
		if(varUsername.bstrVal)
			SysFreeString(varUsername.bstrVal);
		varUsername.bstrVal = bstrUserName;

		pfnGetUsernamePasswd = (LPFNGetUsernamePasswd)GetProcAddress(m_pAppCtxt->hModAuthDll,"GetUsernamePasswd");
		if(!pfnGetUsernamePasswd)
		{
			retVal = E_GETPROCADDRFAILED;
			break;
		}

		pfnProcessEvent = (LPFNProcessEvent)GetProcAddress(m_pAppCtxt->hModAuthDll,"ProcessEvent");
		if(!pfnProcessEvent)
		{
			retVal = E_GETPROCADDRFAILED;
			break;
		}

		if(i_nUIToShow)
		{
			VARIANT varEvent;
			varEvent.vt = VT_I2;
			varEvent.iVal = i_nUIToShow;
			retVal = pfnProcessEvent(&varEvent);
		}
		else
		{
			retVal = pfnGetUsernamePasswd(&varPurpose, &varAppCtxt, &varPasswordQuality, &varUsername, &varPasswd, NULL);
			if(retVal != S_OK)
				break;

			//Obtain the original password
			if(varPasswd.vt == VT_BSTR)
			{
				*o_ptbstrTimeoutPasswd = varPasswd.bstrVal;
				
			}
			else if(varPasswd.vt == VT_ARRAY)
			{
				PBYTE pbytePasswordHash;
				long lLBound;
				long lUBound;
				long lSize;

				if(SafeArrayGetDim(varPasswd.parray) != 1)
				{
					retVal = E_AUTHDLL_INVALIDDIMS;
					break;
				}
				
				retVal = SafeArrayGetLBound(varPasswd.parray, 1,&lLBound);
				if(retVal != S_OK)
					break;
				
				retVal = SafeArrayGetUBound(varPasswd.parray,1, &lUBound);
				if(retVal != S_OK)
					break;

				lSize = lUBound - lLBound + 1;
				retVal = SafeArrayAccessData(varPasswd.parray, (void HUGEP**)&(pbytePasswordHash));
				if(retVal != S_OK)
					break;

				if(!BytesToAscHex(pbytePasswordHash,lSize,(*o_ptbstrTimeoutPasswd)))
				{
					retVal = E_FAIL;
					break;
				}
					
				
			}
			else
			{
				retVal = E_INVALIDARGS;
				break;
			}

		}

	}while(0);

	if(varUsername.bstrVal)
	{
		SysFreeString(varUsername.bstrVal);
	}

	
	if(varPasswd.vt == VT_BSTR && varPasswd.bstrVal)
	{
		SysFreeString(varPasswd.bstrVal);
	}

	if(varPasswd.vt == VT_ARRAY && varPasswd.parray)
	{
		SafeArrayDestroy(varPasswd.parray);
	}
	
	if(varAppCtxt.bstrVal)
	{
		SysFreeString(varAppCtxt.bstrVal);
	}

	if(bstrUserName )
	{
		SysFreeString(bstrUserName );
	}

	if(bstrPath)
	{
		SysFreeString(bstrPath);
	}

	if(bstrApContext)
	{
		SysFreeString(bstrApContext);
	}
	

	return retVal;
}

HRESULT TimeoutCancelFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_TimeoutCancelFn(pOpCtxt);
}

HRESULT TimeoutFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_TimeoutFn(pOpCtxt);
}

HRESULT TimeoutHelpFn(POPCTXT pOpCtxt)
{
	return ((CVSPTA*)(pOpCtxt->pvThePtaObj))->_TimeoutHelpFn(pOpCtxt);
}

HRESULT CVSPTA::_TimeoutCancelFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = E_USERCANCELLED;
	return retVal;
}

HRESULT CVSPTA::_TimeoutFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;
	PUICTXT pCurrUICtxt= NULL;
	

	do
	{
		pCurrUICtxt = _CreateUIContext();
		retVal = ((CPtaUI*)(pOpCtxt->pvThePTAUIObj))->get_UIContext(pCurrUICtxt);
		if(retVal != S_OK)
			break;

		pOpCtxt->pOParams->tbstrTimeOutPasswd = ((PALL_OPENPROF_UIELEMENTS)(pCurrUICtxt->pvUIElements))->tbstrPassword;
		retVal = E_PASSWORDPROVIDED;
	}while(0);

	if(pCurrUICtxt)
	{
		_FreeUIContext(pCurrUICtxt);
		delete(pCurrUICtxt);
	}

	return retVal;
}

HRESULT CVSPTA::_TimeoutHelpFn(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;
	
	if(m_pAppCtxt->theUIPrefs.tbstrTimeOut_HelpUrl != _bstr_t(""))
		HlinkSimpleNavigateToString(m_pAppCtxt->theUIPrefs.tbstrTimeOut_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);
	else
		HlinkSimpleNavigateToString(m_pAppCtxt->theDefUIPrefs.tbstrTimeOut_HelpUrl, NULL, NULL, 
									NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return retVal;
}

HRESULT CVSPTA::put_RoamPrefs_ClientInfo(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)	
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

#if 0	// removed this check bcos if the card was opened then the client info was
		// not getting set, this was bcos if we try to install certificates after opening
		// a profile it was not allowing
	/*Make sure that a card is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		retVal = E_CARDALREADYOPEN;
		_SetErrorInfo(retVal);
		return retVal;
	}
#endif

	retVal = S_OK;

	m_pAppCtxt->theRoamingParams.tbstrClientInfo = newVal.bstrVal;

	// Sasi 05/29/03
	// Whenever roaming server info is changed, we need to query the server again
	// to find out if the server support reset password feature
	m_pAppCtxt->theRoamingParams.boolRoamInfoChanged = TRUE;

	return retVal;
}

HRESULT CVSPTA::get_RoamPrefs_ClientInfo(VARIANT* pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theRoamingParams.tbstrClientInfoSig.copy();
	return retVal;
}

HRESULT CVSPTA::put_RoamPrefs_ClientInfoSig(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)	
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

#if 0	// removed this check bcos if the card was opened then the client info was
		// not getting set, this was bcos if we try to install certificates after opening
		// a profile it was not allowing
	/*Make sure that a card is not already open*/
	retVal = _CheckEnvironment(CHECK_PROF);
	if(retVal == S_OK)
	{
		retVal = E_CARDALREADYOPEN;
		_SetErrorInfo(retVal);
		return retVal;
	}
#endif

	retVal = S_OK;

	m_pAppCtxt->theRoamingParams.tbstrClientInfoSig = newVal.bstrVal;

	// Sasi 05/29/03
	// Whenever roaming server info is changed, we need to query the server again
	// to find out if the server support reset password feature
	m_pAppCtxt->theRoamingParams.boolRoamInfoChanged = TRUE;

	return retVal;
}

HRESULT CVSPTA::get_RoamPrefs_ClientInfoSig(VARIANT* pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theRoamingParams.tbstrClientInfoSig.copy();
	return retVal;
}

HRESULT CVSPTA::_CheckAffLogoUrlSanity(_bstr_t& i_tbstrAffLogoUrl)
{
	HRESULT retVal = S_OK;
	TCHAR* ptszUrl = (TCHAR*)i_tbstrAffLogoUrl;
	TCHAR* ptszScheme = NULL;
	TCHAR* ptszHost = NULL;
	URL_COMPONENTS urlComps;
	memset((void*)&urlComps,0,sizeof(URL_COMPONENTS));
	urlComps.dwStructSize = sizeof(URL_COMPONENTS);
	urlComps.dwSchemeLength = 1;
	urlComps.lpszScheme = NULL;
	urlComps.dwHostNameLength = 1;
	urlComps.lpszHostName = NULL;
	
	do
	{
		if(InternetCrackUrl(ptszUrl,lstrlen(ptszUrl),0,&urlComps))
		{
			ptszScheme = new TCHAR[urlComps.dwSchemeLength + 1];
			lstrcpyn(ptszScheme,urlComps.lpszScheme,urlComps.dwSchemeLength+1);
			ptszScheme[urlComps.dwSchemeLength] = '\0';

			ptszHost = new TCHAR[urlComps.dwHostNameLength + 1];
			lstrcpyn(ptszHost,urlComps.lpszHostName,urlComps.dwHostNameLength+1);
			ptszHost[urlComps.dwHostNameLength] = '\0';

		}
		else
		{
			retVal = E_INVALIDURL;
			break;
		}

		if(lstrcmp(ptszScheme,"http") && lstrcmp(ptszScheme,"https"))
		{
			retVal = E_INVALIDURL;
			break;
		}

		if(lstrcmp(ptszHost+lstrlen(ptszHost)-lstrlen(".verisign.com"),".verisign.com"))
		{
			retVal = E_INVALIDURL;
			break;
		}

	}while(0);

	if(ptszScheme)
		delete ptszScheme;
	if(ptszHost)
		delete ptszHost;

	return retVal;
}

STDMETHODIMP CVSPTA::get_SignDate(DATE *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the signature date and time
	*pVal = m_pAppCtxt->theSignMsgParams.dateSignDate;

	return retVal;
}

STDMETHODIMP CVSPTA::put_SignDate(DATE newVal)
{
	HRESULT retVal = S_OK;

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the date and time for the auth attr of the signature
	m_pAppCtxt->theSignMsgParams.dateSignDate = newVal;

	return retVal;
}

STDMETHODIMP CVSPTA::put_EnableCertForCapi(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	
	//Save the flag in the app context.
	m_pAppCtxt->boolCapiCert = newVal.iVal;

	return S_OK;
}


STDMETHODIMP CVSPTA::ExportProfile(VARIANT *in_pvarPassword, VARIANT in_varFlags, VARIANT *o_pvarB64EncProfileData)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrProfileData = "";
	PBYTE pbPassword = NULL;
	DWORD dwPassword = 0;

	do
	{
		retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
		if(retVal != S_OK)
			break;

		if(!in_pvarPassword || !o_pvarB64EncProfileData)
		{	
			retVal = E_EMPTYARGS;
			break;
		}

		/*Check the types of the input params*/
		if(in_pvarPassword->vt != (VT_ARRAY | VT_UI1) || in_varFlags.vt != VT_I2)
		{
			retVal = E_INVALIDARGS;
			break;
		}

		//Extract the information from the vt array
		retVal = SafeArrayAccessData(in_pvarPassword->parray, (void HUGEP**)&pbPassword);
		if(retVal == S_OK)
		{
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)in_pvarPassword->parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)in_pvarPassword->parray, 1, &uBound);
			dwPassword = uBound - lBound + 1;

			m_pAppCtxt->theExportProfileParams.nProfilePasswd = dwPassword;
			m_pAppCtxt->theExportProfileParams.pbProfilePasswd = pbPassword;
		}
		else
			break;

		if(dwPassword == 0)
		{
			retVal = E_INVALIDPASSWD;
			break;
		}

		m_pAppCtxt->theExportProfileParams.nExportProfileFlags = in_varFlags.iVal;
		
		retVal = _DoOperation(EXPORTPROFILE_WIZARD_BASE, EXPORTPROFILE_BASE);

		if(retVal == S_OK)
		{
			o_pvarB64EncProfileData->vt = VT_BSTR;
			o_pvarB64EncProfileData->bstrVal = m_pAppCtxt->theExportProfileParams.tbstrProfileData.copy();
		}

	}while(0);

	if(pbPassword)
		SafeArrayUnaccessData(in_pvarPassword->parray);

	if(retVal != S_OK)
		_SetErrorInfo(retVal);

	return retVal;
}



STDMETHODIMP CVSPTA::ImportProfile(VARIANT *in_pvarPassword, VARIANT *in_pvarProfileData)
{
	HRESULT retVal = S_OK;
	PBYTE pbPassword = NULL;
	DWORD dwPassword = 0;

	do
	{
		retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
		if(retVal != S_OK)
			break;

		if(!in_pvarPassword || !in_pvarProfileData)
		{	
			retVal = E_EMPTYARGS;
			break;
		}

		/*Check the types of the input params*/
		if(in_pvarPassword->vt != (VT_ARRAY | VT_UI1) || in_pvarProfileData->vt != VT_BSTR)
		{
			retVal = E_INVALIDARGS;
			break;
		}

		//Extract the information from the vt array
		retVal = SafeArrayAccessData(in_pvarPassword->parray, (void HUGEP**)&pbPassword);
		if(retVal == S_OK)
		{
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)in_pvarPassword->parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)in_pvarPassword->parray, 1, &uBound);
			dwPassword = uBound - lBound + 1;

			m_pAppCtxt->theImportProfileParams.nProfilePasswd = dwPassword;
			m_pAppCtxt->theImportProfileParams.pbProfilePasswd = pbPassword;
		}
		else
			break;

		if(dwPassword == 0)
		{
			retVal = E_INVALIDPASSWD;
			break;
		}

		m_pAppCtxt->theImportProfileParams.tbstrProfileData = in_pvarProfileData->bstrVal;
		
		retVal = _DoOperation(IMPORTPROFILE_WIZARD_BASE, IMPORTPROFILE_BASE);

	}while(0);

	if(pbPassword)
		SafeArrayUnaccessData(in_pvarPassword->parray);

	if(retVal != S_OK)
		_SetErrorInfo(retVal);

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_SignTransDlgWidth(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nSignTransDlgWidth;

	return retVal;
}


STDMETHODIMP CVSPTA::put_UIPref_SignTransDlgWidth(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	RECT rcWorkArea;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	if(!SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0))
	{
		retVal = E_SYSPARAMSERR;
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(newVal.iVal <= 0) 
	{
		m_pAppCtxt->theUIPrefs.nSignTransDlgWidth = 0;
	
		retVal = E_INVALID_WIDTH;
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(newVal.iVal > rcWorkArea.right)
	{
		m_pAppCtxt->theUIPrefs.nSignTransDlgWidth = rcWorkArea.right;
	
		retVal = E_INVALID_WIDTH;
		_SetErrorInfo(retVal);
		return retVal;
	}

	m_pAppCtxt->theUIPrefs.nSignTransDlgWidth = newVal.iVal;  

	return S_OK;
}


STDMETHODIMP CVSPTA::get_UIPref_SignTransDlgHeight(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nSignTransDlgHeight;

	return retVal;
}


STDMETHODIMP CVSPTA::put_UIPref_SignTransDlgHeight(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	RECT rcWorkArea;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(!SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&rcWorkArea, 0))
	{
		retVal = E_SYSPARAMSERR;
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(newVal.iVal <= 0)
	{
		m_pAppCtxt->theUIPrefs.nSignTransDlgHeight = 0;

		retVal = E_INVALID_HEIGHT;
		_SetErrorInfo(retVal);
		return retVal;
	}

	if(newVal.iVal > rcWorkArea.bottom)
	{
		m_pAppCtxt->theUIPrefs.nSignTransDlgHeight = rcWorkArea.bottom;

		retVal = E_INVALID_HEIGHT;
		_SetErrorInfo(retVal);
		return retVal;
	}

	m_pAppCtxt->theUIPrefs.nSignTransDlgHeight = newVal.iVal;

	return S_OK;
}

STDMETHODIMP CVSPTA::get_IsTPMAvailable(VARIANT *pVal)
{
	// Check if IBM TSS is present. If it is not present, then check for Infineon TSS
	HMODULE hModIBMTSS = NULL;

	// Check dependency dlls for IBM TSS first. This check is done to avoid the warning dialog that 
	// is displayed when trying to load vs_ibmtss.dll with one of the dependency dlls missing. Otherwise,
	// it will show "Unable to locate dll ..." dialog
	BOOL boolDependencyDlls = FALSE;
	if(::LoadLibrary("tcpatrace.dll") && ::LoadLibrary("calltcs.dll") && ::LoadLibrary("getpin.dll") && ::LoadLibrary("tcpaps.dll"))
		boolDependencyDlls = TRUE;

	if(boolDependencyDlls)
		hModIBMTSS = ::LoadLibrary("vs_ibmtss.dll");

	BOOL	boolInfineon = FALSE;
	if(NULL == hModIBMTSS)
	{
		_CheckForInfineonTPM( &boolInfineon );

		pVal->vt = VT_BOOL;

		if(boolInfineon == TRUE)
			pVal->boolVal = true;
		else
			pVal->boolVal = false;
	}
	else
	{
		pVal->vt = VT_BOOL;
		pVal->boolVal = true;
	}

	return S_OK;
}

STDMETHODIMP CVSPTA::ProfMgmt_ResetPassword()
{
	HRESULT retVal = S_OK;
	
	/*Check if we are initialized and this is non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	retVal = _DoOperation(LOGIN_WIZARD_BASE,RESETPASSWD_BASE);

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_GetSecretQuestion_Title(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the get secret question dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_GetSecretQuestion_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the get secret question title property
	m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_GetSecretQuestion_Text(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the get secret question dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Text.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_GetSecretQuestion_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the get secret question text property
	m_pAppCtxt->theUIPrefs.tbstrGetSecretQuestion_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_GetSecretQuestion_OKBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nGetSecretQuestion_OKBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_GetSecretQuestion_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nGetSecretQuestion_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_GetSecretQuestion_CancelBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nGetSecretQuestion_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_GetSecretQuestion_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted Cancel button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the cancel button text
	m_pAppCtxt->theUIPrefs.nGetSecretQuestion_CancelBtnText = newVal.iVal;

	return retVal;
}


STDMETHODIMP CVSPTA::get_UIPref_ResetPasswd_Title(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the reset password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_ResetPasswd_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the reset password title property
	m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ResetPasswd_Text(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the reset password dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Text.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_ResetPasswd_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the reset password text property
	m_pAppCtxt->theUIPrefs.tbstrResetPasswd_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ResetPasswd_OKBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nResetPasswd_OKBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_ResetPasswd_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nResetPasswd_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_ResetPasswd_CancelBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nResetPasswd_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_ResetPasswd_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted Cancel button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the cancel button text
	m_pAppCtxt->theUIPrefs.nResetPasswd_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreateSecret_Title(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the title of the create secret dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Title.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreateSecret_Title(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the create secret title property
	m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Title = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreateSecret_Text(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the text of the create secret dialog box
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Text.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreateSecret_Text(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	//Set the Create Secret text property
	m_pAppCtxt->theUIPrefs.tbstrCreateSecret_Text = newVal.bstrVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreateSecret_OKBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the ok button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nCreateSecret_OKBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreateSecret_OKBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted OK button text range*/
	if(newVal.iVal < IDS_OK || newVal.iVal >IDS_YES)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the ok button text
	m_pAppCtxt->theUIPrefs.nCreateSecret_OKBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::get_UIPref_CreateSecret_CancelBtnText(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	//Obtain the identifier of the text for the cancel button
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theUIPrefs.nCreateSecret_CancelBtnText;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UIPref_CreateSecret_CancelBtnText(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		_SetErrorInfo(E_INVALIDARGS);
		return E_INVALIDARGS;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Make sure the identifier is in the accepted Cancel button text range*/
	if(newVal.iVal < IDS_CANCEL || newVal.iVal >IDS_NO)
	{
		_SetErrorInfo(E_INVALIDVALUE);
		return E_INVALIDVALUE;
	}

	//Set the cancel button text
	m_pAppCtxt->theUIPrefs.nCreateSecret_CancelBtnText = newVal.iVal;

	return retVal;
}

STDMETHODIMP CVSPTA::ProfMgmt_RemoveCertificates()
{
	HRESULT retVal = S_OK;
	
	/*Check if we are initialized and this is non capi mode*/
	retVal = _CheckEnvironment(CHECK_INIT | CHECK_NONCAPI_MODE);

	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	retVal = _DoOperation(NO_WIZARD_BASE,REMOVECERTIFICATES_BASE);

	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_FirstName(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get user's first name*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theOpenProfParams.tbstrFirstName.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_FirstName(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Store user's first name.*/
	m_pAppCtxt->theOpenProfParams.tbstrFirstName = newVal.bstrVal;


	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_LastName(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get user's last name*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theOpenProfParams.tbstrLastName.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_LastName(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Store user's last name.*/
	m_pAppCtxt->theOpenProfParams.tbstrLastName = newVal.bstrVal;


	return retVal;
}

STDMETHODIMP CVSPTA::get_ProfMgmt_Email(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context and that a  profile is open*/
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	/*Get user's e-mail*/
	pVal->vt = VT_BSTR;
	pVal->bstrVal = m_pAppCtxt->theOpenProfParams.tbstrEmail.copy();

	return retVal;
}

STDMETHODIMP CVSPTA::put_ProfMgmt_Email(VARIANT newVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_BSTR)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	/*Store user's e-mail.*/
	m_pAppCtxt->theOpenProfParams.tbstrEmail = newVal.bstrVal;


	return retVal;
}

STDMETHODIMP CVSPTA::get_UTF8EncodeMessage(VARIANT *pVal)
{
	HRESULT retVal = S_OK;


	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	pVal->vt = VT_BOOL;
	pVal->boolVal = m_pAppCtxt->theSignMsgParams.boolUTF8EncodeMsgToSign;

	return retVal;
}

STDMETHODIMP CVSPTA::put_UTF8EncodeMessage(VARIANT newVal)
{
	HRESULT retVal = S_OK;
	
	if(newVal.vt != VT_BOOL)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}


	m_pAppCtxt->theSignMsgParams.boolUTF8EncodeMsgToSign = newVal.boolVal;

	return retVal;
}


/* Modified By: Infosys Technologies Ltd.
   CR#21080: This CR relates to changing the current implementation of storing 
   string "fragments" for dynamically creating password string to storing complete
   strings in the resource table. This would eliminate the grammatical errors that
   occur in other languages due to string fragmentation.

   As an approach to solve this problem, the function "_GetPasswdQualityString" has
   been re-written to read the complete strings (instead of fragments). 


    Modification Log
	Version		Date			Author				Description
-------------------------------------------------------------------------------------------------------------------------------
	1.01		18-Jun-2004		Infosys 
								Technologies		CR#21080: Replaced statement fragments
								Ltd.				with complete strings.
-------------------------------------------------------------------------------------------------------------------------------
*/


//   CR#21080 - Begin

HRESULT CVSPTA::_GetPasswdQualityString(_bstr_t* o_ptbstrPasswdQualString)
{
	HRESULT retVal = S_OK;

	WCHAR wstrTemp[MAX_RES_STRING_SIZE];
	TCHAR tstrTemp[MAX_RES_STRING_SIZE];

	// Perform checks based on the password quality preferences chosen by the user
	switch(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_PASSWDTYPE_BASE)
	{
		case PASSWDQUAL_ANYPASSWDOK :
			// In this case, we need to load the generic string for password quality from
			// the resource string table.
			if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
			{
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ANY,wstrTemp, MAX_RES_STRING_SIZE);

				if(retVal == S_OK)
				{
					_bstr_t tbstrTemp(wstrTemp);
					wsprintf(tstrTemp, tbstrTemp, m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength);
					*o_ptbstrPasswdQualString += tstrTemp;
				}
			}
			break;

		case PASSWDQUAL_NUMERICONLY :
			// If the password is numeric only, then load the appropriate string.
			if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
			{
				retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_NUMERIC,wstrTemp, MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					_bstr_t tbstrTemp(wstrTemp);
					// Replace the %ds with the correct values.
					wsprintf(tstrTemp, tbstrTemp, m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength);
					*o_ptbstrPasswdQualString += tstrTemp;
				}
			}
			break;

		case  PASSWDQUAL_ALPHANUMERIC:
			// Check if there are any restrictions for the minimum length of password
			// If yes, then we need to do further checking for the character positions in the password.
			if(m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength)
			{
				// Find the number of numbers that should be present in the password
				int nNumOfNums = (m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_NOOFNUM_BASE) >> 8;
				// Find the position of numbers within the password as per the 
				// password policy, e.g. policy could prohibit the user from adding numeric characters
				// at the beginning and end of the password.
				int nPosOfNums = (m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordQuality & PASSWDQUAL_POSOFNUM_BASE);

				
				// Following conditional statements pick up complete statment strings based on 
				// the password policy regarding the location of numeric characters.
				if(nPosOfNums == PASSWDQUAL_ALPHANUMERIC_NUMNOTATBEGIN)
				{
					retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ALPHANUMERIC_NUMLEN_NOTATBEGIN,wstrTemp, MAX_RES_STRING_SIZE);
				}
				else if(nPosOfNums == PASSWDQUAL_ALPHANUMERIC_NUMNOTATEND)
				{
					retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ALPHANUMERIC_NUMLEN_NOTATEND,wstrTemp, MAX_RES_STRING_SIZE);
				}
				else if(nPosOfNums == PASSWDQUAL_ALPHANUMERIC_NUMNOTATBEGINEND)
				{
					retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ALPHANUMERIC_NUMLEN_NOTATBEGINEND,wstrTemp, MAX_RES_STRING_SIZE);
				}
				else if (nNumOfNums)
				{
					// If the control reaches here, it means that there is no restriction enforced
					// on the position of numeric characters within the password. Therefore,
					// we display a generic string for alphanumeric password with number of numeric 
					// characters to be displayed.
					retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ALPHANUMERIC_NUMLEN,wstrTemp, MAX_RES_STRING_SIZE);
				}
				else
				{
					// If the control reaches here, it means that the password quality would be "Alphanumeric Only".
					retVal = _LoadStringW(_Module.m_hInst, m_pAppCtxt->theDefUIPrefs.wLangID, IDS_PASSWORD_ALPHANUMERIC,wstrTemp, MAX_RES_STRING_SIZE);
				}
				if(retVal == S_OK)
				{
					_bstr_t tbstrTemp(wstrTemp);

					// Replace the %ds (escape sequences) with the correct values.
					wsprintf(tstrTemp, tbstrTemp, m_pAppCtxt->theOpenProfParams.theCreateParams.nPasswordLength, nNumOfNums);
					*o_ptbstrPasswdQualString += tstrTemp;
				}			
			}
			break;
		default:
			retVal = E_INVALIDFLAGS;
			break;
	}

	return retVal;
}


// Modified by - Infosys Technologies Ltd. 
// Change Request - CR#21529
// Description - This CR relates to making the private key non-exportable. The following methods form a
// partial implementation for the same. These get and set methods are used to get and set
// the PrivateKeyExportable flag which indicates whether the private key has been marked as 
// exportable or non-exportable by the administrator.
// CR#21529 Begin
// Date Modified - July 5, 2004

STDMETHODIMP CVSPTA::get_IsPrivateKeyExportable(VARIANT *pVal)
{
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(!pVal)
	{
		retVal = E_EMPTYARGS;
		_SetErrorInfo(E_EMPTYARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context*/
	retVal = _CheckEnvironment(CHECK_INIT);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}
	
	//Obtain the help url of the new password dialog box
	pVal->vt = VT_I2;
	pVal->iVal = m_pAppCtxt->theCreateCertReqParams.bIsPrivateKeyExportable;

	return retVal;
}

STDMETHODIMP CVSPTA::put_IsPrivateKeyExportable(VARIANT newVal)
{
	
	HRESULT retVal = S_OK;

	/*Input validation*/
	if(newVal.vt != VT_I2)
	{
		retVal = E_INVALIDARGS;
		_SetErrorInfo(E_INVALIDARGS);
		return retVal;
	}

	/*Check if we are initialized and we have an app context */
	retVal = _CheckEnvironment(CHECK_INIT|CHECK_NONCAPI_MODE);
	if(retVal != S_OK)
	{
		_SetErrorInfo(retVal);
		return retVal;
	}

	m_pAppCtxt->theCreateCertReqParams.bIsPrivateKeyExportable = (BOOL) newVal.iVal;

	return retVal;
}
//   CR#21529 - End

/* 
  This function checks if Infineon TSS is installed on the client machine or not.
*/
HRESULT CVSPTA::_CheckForInfineonTPM(BOOL* boolExists)
{

	HRESULT hr  = S_OK;

	const CLSID CLSID_TCPAContext = {0xFBCD9C1A,0x72CB,0x47BB,{0x99,0xDD,0x23,0x17,0x55,0x14,0x91,0xDE}};
	IUnknown * pContext = NULL;

	*boolExists = FALSE;

	if(SUCCEEDED(CoCreateInstance(CLSID_TCPAContext, 0, CLSCTX_ALL , __uuidof(IUnknown), (LPVOID *) &pContext)))
	{
		*boolExists = TRUE;
		pContext->Release();
	}

	return hr;
}
