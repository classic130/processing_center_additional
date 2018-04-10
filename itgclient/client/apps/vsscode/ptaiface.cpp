#include "stdafx.h"
#include <comutil.h>
#include "certmgmt.h"
#include "settings.h"
#include "ptav3.h"
#include "ptav3_i.c"
#include "ptadllapi_i.c"
#include "ptaiface.h"
#include "vsserrs.h"
#include "macros.h"
#include "propsht.h"
#include "util.h"
#include "resource.h"


HRESULT InitializePTA(CRegSettings& i_usrSettings, IVSPTA** o_pVSPTA)
{
	HRESULT hr = S_OK;
	IVSProfMgmt *pIVSProfMgmt = NULL;
	IVSRoamPrefs *pIVSRoamPrefs = NULL;
	IVSSrchCrit *pIVSSrchCrit = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSUIPrefs *pIVSUIPref = NULL;
	WCHAR* wcTempStr = NULL;
	_bstr_t tbstrTemp = "";
	
	VARIANT varAppName, varUseCapi, varProfOpen, varIsRoaming, varClientInfo, varClientInfoSig;
	VARIANT varHostName, varDateFlag, varRenewedFlag, varIssuerDN, varPasswdQuality, varPasswdLength;
	VARIANT varPasswdTimeout, varPasswdTries, varPasswdUnlockPeriod, varOpenProfText, varSelIDText;
	VARIANT varShowDefIDBox, varShowSignUI, varNewPasswdText, varSignTitle, varWizTitle, varText;
	DATE todayDate;
	UDATE todayUDate;

	VariantInit(&varAppName);
	VariantInit(&varUseCapi);
	VariantInit(&varProfOpen);
	VariantInit(&varIsRoaming);
	VariantInit(&varClientInfo);
	VariantInit(&varClientInfoSig);
	VariantInit(&varHostName);
	VariantInit(&varDateFlag);
	VariantInit(&varRenewedFlag);
	VariantInit(&varPasswdQuality);
	VariantInit(&varPasswdLength);
	VariantInit(&varPasswdTimeout);
	VariantInit(&varPasswdTries);
	VariantInit(&varPasswdUnlockPeriod);
	VariantInit(&varOpenProfText);
	VariantInit(&varSelIDText);
	VariantInit(&varShowDefIDBox);
	VariantInit(&varShowSignUI);
	VariantInit(&varNewPasswdText);
	VariantInit(&varSignTitle);
	VariantInit(&varWizTitle);
	VariantInit(&varText);

	do
	{
		CHECK_NULL_PTR_BREAK(o_pVSPTA)

		hr = CoCreateInstance(CLSID_VSPTA, NULL, CLSCTX_INPROC_SERVER, IID_IVSPTA,(void**)o_pVSPTA);
		CHECK_HRESULT_BREAK

		varAppName.vt = VT_BSTR;
		varAppName.bstrVal = i_usrSettings.m_bstrAppContext.copy();

		varUseCapi.vt = VT_I2;

		// Ignore registry setting for the CAPI/NON-CAPI mode, bcos the code has not been tested much for
		// CAPI mode
		varUseCapi.iVal = 0;		//varUseCapi.iVal = (SHORT)i_usrSettings.m_dwCapi;

		hr = (*o_pVSPTA)->Initialize(&varAppName, &varUseCapi);
		CHECK_HRESULT_BREAK

		hr = (*o_pVSPTA)->QueryInterface(IID_IVSPTADllApi, (void **)&(pPTADllApi));
		CHECK_HRESULT_BREAK

		varHostName.vt = VT_BSTR;
		varHostName.bstrVal = SysAllocString(L"codesigning");

		hr = pPTADllApi->put_HostFQDN(varHostName);
		CHECK_HRESULT_BREAK

		hr = (*o_pVSPTA)->get_IVSProfMgmt((IDispatch**)&pIVSProfMgmt);
		CHECK_HRESULT_BREAK

		hr = (*o_pVSPTA)->get_IVSUIPrefs((IDispatch**)&pIVSUIPref);
		CHECK_HRESULT_BREAK

		// Set roaming preferences if present only for non-capi mode
		if(varUseCapi.iVal == 0)
		{
			if(i_usrSettings.m_bstrClientInfo != _bstr_t("") && i_usrSettings.m_bstrClientInfoSig != _bstr_t(""))
			{
				varIsRoaming.vt = VT_BOOL;
				varIsRoaming.boolVal = TRUE;

				hr = (*o_pVSPTA)->get_IVSRoamPrefs((IDispatch**)&pIVSRoamPrefs);
				CHECK_HRESULT_BREAK

				varClientInfo.vt = VT_BSTR;
				varClientInfo.bstrVal = i_usrSettings.m_bstrClientInfo.copy();

				hr = pIVSRoamPrefs->put_ClientInfo(varClientInfo);
				CHECK_HRESULT_BREAK

				varClientInfoSig.vt = VT_BSTR;
				varClientInfoSig.bstrVal = i_usrSettings.m_bstrClientInfoSig.copy();

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

		switch(i_usrSettings.m_CertOp)
		{
			// If enrolling or importing a cert, password requirements need to be set
			case CERT_IMPORT:
			case CERT_ENROLL:
			{
				varPasswdQuality.vt = VT_I2;
				varPasswdQuality.iVal = (SHORT)i_usrSettings.m_dwPasswordQuality;

				hr = pIVSProfMgmt->put_PasswdQuality(varPasswdQuality);
				CHECK_HRESULT_BREAK

				varPasswdLength.vt = VT_I2;
				varPasswdLength.iVal = (SHORT)i_usrSettings.m_dwPasswordLength;

				hr = pIVSProfMgmt->put_PasswdLength(varPasswdLength);
				CHECK_HRESULT_BREAK

				varPasswdTimeout.vt = VT_I2;
				varPasswdTimeout.iVal = (SHORT)i_usrSettings.m_dwPasswordTimeout;

				hr = pIVSProfMgmt->put_PasswdTimeOut(varPasswdTimeout);
				CHECK_HRESULT_BREAK

				varPasswdTries.vt = VT_I2;
				varPasswdTries.iVal = (SHORT)i_usrSettings.m_dwPasswordTries;

				hr = pIVSProfMgmt->put_PasswdLockOutTries(varPasswdTries);
				CHECK_HRESULT_BREAK
				
				varPasswdUnlockPeriod.vt = VT_I2;
				varPasswdUnlockPeriod.iVal = (SHORT)i_usrSettings.m_dwPasswordUnlockPeriod;

				hr = pIVSProfMgmt->put_PasswdUnLockPeriod(varPasswdUnlockPeriod);
				CHECK_HRESULT_BREAK

				varProfOpen.vt = VT_I2;
				varProfOpen.iVal = PROF_OPEN_OR_CREATE;

				hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
				CHECK_HRESULT_BREAK

				// Set the new password text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_NEW_PASSWD_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varNewPasswdText.vt = VT_BSTR;
				varNewPasswdText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_NewPasswd_Text(varNewPasswdText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				break;
			}

			case CERT_SIGNONLY:
			case CERT_COSIGN:
			{
				varProfOpen.vt = VT_I2;
				varProfOpen.iVal = PROF_OPEN;

				hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
				CHECK_HRESULT_BREAK

				// Set search criteria for the certificate selection
				hr = (*o_pVSPTA)->get_IVSSrchCrit((IDispatch**)&pIVSSrchCrit);
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
				varIssuerDN.bstrVal = i_usrSettings.m_bstrSrchCriteria.copy();

				hr = pIVSSrchCrit->put_IssuerDN(varIssuerDN);
				CHECK_HRESULT_BREAK

				varShowSignUI.vt = VT_BOOL;
				varShowSignUI.boolVal = FALSE;

				hr = pPTADllApi->put_ShowSignUI(varShowSignUI);
				CHECK_HRESULT_BREAK

				// Put the UI prefs for co-signature or signature
				if(i_usrSettings.m_CertOp == CERT_COSIGN)
					hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_COSIGN_TITLE, &wcTempStr);
				else
					hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_SIGN_TITLE, &wcTempStr);

				CHECK_HRESULT_BREAK
					
				tbstrTemp = wcTempStr;

				varSignTitle.vt = VT_BSTR;
				varSignTitle.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_LgnDlg_Title(varSignTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				break;
			}

			case CERT_INSTALL:
			{
				// need to set the cert logo url and friendly name?

				varProfOpen.vt = VT_I2;
				varProfOpen.iVal = PROF_OPEN;

				hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
				CHECK_HRESULT_BREAK

				// Set the open profile text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_INSTALL_CERT_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varOpenProfText.vt = VT_BSTR;
				varOpenProfText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_OpenProf_Text(varOpenProfText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				break;
			}

			case CERT_EXPORT:
			{
				varProfOpen.vt = VT_I2;
				varProfOpen.iVal = PROF_OPEN;

				hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
				CHECK_HRESULT_BREAK

				// Set the open profile text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_EXPORT_PROF_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varOpenProfText.vt = VT_BSTR;
				varOpenProfText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_OpenProf_Text(varOpenProfText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				// Set the select ID text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_EXPORT_SELID_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varSelIDText.vt = VT_BSTR;
				varSelIDText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_SelID_Text(varSelIDText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				// Do not show the default ID check box
				varShowDefIDBox.vt = VT_BOOL;
				varShowDefIDBox.boolVal = FALSE;

				hr = pIVSUIPref->put_SelID_ShowDefChkBox(varShowDefIDBox);
				CHECK_HRESULT_BREAK

				break;
			}

			case PROF_CHANGE_PASSWD:
			{
				varProfOpen.vt = VT_I2;
				varProfOpen.iVal = PROF_OPEN;

				hr = pIVSProfMgmt->put_OpenProfFlags(varProfOpen);
				CHECK_HRESULT_BREAK

				// Set the change password wizard title
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_CHPASS_WIZ_TITLE, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varWizTitle.vt = VT_BSTR;
				varWizTitle.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_LgnDlg_Title(varWizTitle);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				// Set the change password open profile text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_CHPASS_PROF_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varOpenProfText.vt = VT_BSTR;
				varOpenProfText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_OpenProf_Text(varOpenProfText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				// Set the change password text
				hr = LoadStringW(AfxGetInstanceHandle(), _GetDefaultLangID(), IDS_CHPASS_TEXT, &wcTempStr);
				CHECK_HRESULT_BREAK

				tbstrTemp = wcTempStr;

				varText.vt = VT_BSTR;
				varText.bstrVal = tbstrTemp;

				hr = pIVSUIPref->put_ChangePasswd_Text(varText);
				CHECK_HRESULT_BREAK

				FREE_MEMORY(wcTempStr)

				varPasswdQuality.vt = VT_I2;
				varPasswdQuality.iVal = (SHORT)i_usrSettings.m_dwPasswordQuality;

				hr = pIVSProfMgmt->put_PasswdQuality(varPasswdQuality);
				CHECK_HRESULT_BREAK

				varPasswdLength.vt = VT_I2;
				varPasswdLength.iVal = (SHORT)i_usrSettings.m_dwPasswordLength;

				hr = pIVSProfMgmt->put_PasswdLength(varPasswdLength);
				CHECK_HRESULT_BREAK

				break;
			}

			CHECK_HRESULT_BREAK

		}	// end switch

		
	}while(0);

	VariantClear(&varAppName);
	VariantClear(&varUseCapi);
	VariantClear(&varProfOpen);
	VariantClear(&varIsRoaming);
	VariantClear(&varClientInfo);
	VariantClear(&varClientInfoSig);
	VariantClear(&varHostName);
	VariantClear(&varDateFlag);
	VariantClear(&varRenewedFlag);
	VariantClear(&varIssuerDN);
	VariantClear(&varPasswdQuality);
	VariantClear(&varPasswdLength);
	VariantClear(&varPasswdTimeout);
	VariantClear(&varPasswdTries);
	VariantClear(&varPasswdUnlockPeriod);
	VariantClear(&varOpenProfText);
	VariantClear(&varSelIDText);
	VariantClear(&varShowDefIDBox);
	VariantClear(&varShowSignUI);
	VariantClear(&varNewPasswdText);
	VariantClear(&varSignTitle);
	VariantClear(&varWizTitle);
	VariantClear(&varText);

	RELEASE_INTERFACE_PTR(pIVSProfMgmt)
	RELEASE_INTERFACE_PTR(pIVSRoamPrefs)
	RELEASE_INTERFACE_PTR(pIVSSrchCrit)
	RELEASE_INTERFACE_PTR(pPTADllApi)
	RELEASE_INTERFACE_PTR(pIVSUIPref)

	FREE_MEMORY(wcTempStr)
	
	if(hr != S_OK)
	{
		UnInitializePTA(*o_pVSPTA);
		*o_pVSPTA = NULL;
		_LogErrorMsg("InitializePTA().", "Error initializing the PTA.", NULL, hr);
	}

	return hr;
}



HRESULT UnInitializePTA(IVSPTA* i_pVSPTA)
{
	if(!i_pVSPTA)
		return E_VSSCODE_EMPTYARGS;

	i_pVSPTA->Close();

	RELEASE_INTERFACE_PTR(i_pVSPTA)
	
	return S_OK;
}