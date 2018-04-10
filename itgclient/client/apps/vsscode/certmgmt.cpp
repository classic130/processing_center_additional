#include "stdafx.h"
#include <comutil.h>
#include "propsht.h"
#include "certmgmt.h"
#include "settings.h"
#include "vsserrs.h"
#include "macros.h"
#include "ptav3.h"
#include "ptaiface.h"
#include "resource.h"
#include "DlgCSR.h"
#include "util.h"


HRESULT CreateCSR(VOID)
{
	HRESULT hr = S_OK;
	CRegSettings usrSettings;
	CDlgCSR MyCsrDialog;
	IVSPTA* pVSPTA = NULL;
	VARIANT varSubjectDN, varKeyGenFlag, varHashAlg, varAttributes, varBase64CertReq;
	VARIANT* pVarElement;
	SAFEARRAYBOUND rgsabound[2];
	SAFEARRAY* pAttrArray = NULL;
	WCHAR* wNameValues[2][2] = { {L"2.5.29.15", L"03020138"}, {L"2.5.29.37", L"300A06082B06010505070302"} };
	LONG lIndex[2];

	CoInitialize(NULL);

	VariantInit(&varSubjectDN);
	VariantInit(&varKeyGenFlag);
	VariantInit(&varHashAlg);
	VariantInit(&varAttributes);
	VariantInit(&varBase64CertReq);

	do
	{
		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_ENROLL;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		// Create the PKCS10 now
		varSubjectDN.vt = VT_BSTR;
		varSubjectDN.bstrVal = SysAllocString(L"CN=vsc1enroll");

		varKeyGenFlag.vt = VT_I4;
		varKeyGenFlag.lVal = AT_EXCHANGE_KEY;
		varKeyGenFlag.lVal |= EXPORTABLE_KEY;
		varKeyGenFlag.lVal |= KEY_SIZE_1024;
	
		varHashAlg.vt = VT_I2;

		if(_strnicmp(usrSettings.m_bstrHashAlg, "MD5", 3) == 0)
			varHashAlg.iVal = SCRIPT_HASH_MD5;
		else
			if(_strnicmp(usrSettings.m_bstrHashAlg, "SHA1", 4) == 0)
				varHashAlg.iVal = SCRIPT_HASH_SHA1;
			else
				if(_strnicmp(usrSettings.m_bstrHashAlg, "MD2", 3) == 0)
					varHashAlg.iVal = SCRIPT_HASH_MD2;
				else
				{
					hr = E_VSSCODE_INVALIDALG;
					break;
				}

		// Set up the attributes
		varAttributes.vt = VT_ARRAY | VT_VARIANT | VT_BYREF;

		rgsabound[0].lLbound = 1;
		rgsabound[0].cElements = 2;
		rgsabound[1].lLbound = 1;
		rgsabound[1].cElements = 2;

		pAttrArray = SafeArrayCreate(VT_VARIANT, 2, rgsabound);
		CHECK_MEM_BREAK(pAttrArray)
     
		varAttributes.pparray = &pAttrArray;

		// Put the first name-value pair in the SafeArray
		pVarElement = new VARIANT;
		CHECK_MEM_BREAK(pVarElement)

		pVarElement->vt = VT_BSTR;
		pVarElement->bstrVal = SysAllocString(wNameValues[0][0]);

		lIndex[0] = 1;
		lIndex[1] = 1;

		hr = SafeArrayPutElement(pAttrArray, lIndex, pVarElement);
		CHECK_HRESULT_BREAK

		pVarElement = new VARIANT;
		CHECK_MEM_BREAK(pVarElement)

		pVarElement->vt = VT_BSTR;
		pVarElement->bstrVal = SysAllocString(wNameValues[0][1]);

		lIndex[0] = 1;
		lIndex[1] = 2;

		hr = SafeArrayPutElement(pAttrArray, lIndex, pVarElement);
		CHECK_HRESULT_BREAK

		// Put the second name-value pair in the SafeArray
		pVarElement = new VARIANT;
		CHECK_MEM_BREAK(pVarElement)

		pVarElement->vt = VT_BSTR;
		pVarElement->bstrVal = SysAllocString(wNameValues[1][0]);

		lIndex[0] = 2;
		lIndex[1] = 1;

		hr = SafeArrayPutElement(pAttrArray, lIndex, pVarElement);
		CHECK_HRESULT_BREAK

		pVarElement = new VARIANT;
		CHECK_MEM_BREAK(pVarElement)

		pVarElement->vt = VT_BSTR;
		pVarElement->bstrVal = SysAllocString(wNameValues[1][1]);

		lIndex[0] = 2;
		lIndex[1] = 2;

		hr = SafeArrayPutElement(pAttrArray, lIndex, pVarElement);
		CHECK_HRESULT_BREAK

		hr = pVSPTA->CreateCertReq(&varSubjectDN, &varKeyGenFlag, &varHashAlg, &varAttributes, &varBase64CertReq);
		CHECK_HRESULT_BREAK

		// Display the generated certificate request to the end user
		MyCsrDialog.m_CertOp = CERT_ENROLL;
		hr = MyCsrDialog.SetCSR(varBase64CertReq.bstrVal);
		CHECK_HRESULT_BREAK

		MyCsrDialog.DoModal();

	}while(0);

	UnInitializePTA(pVSPTA);

	VariantClear(&varSubjectDN);
	VariantClear(&varKeyGenFlag);
	VariantClear(&varHashAlg);
	VariantClear(&varBase64CertReq);

	if(pAttrArray != NULL)
	{
		SafeArrayDestroy(pAttrArray);
		pAttrArray = NULL;
	}

	VariantClear(&varAttributes);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("CreateCSR().", "Error creating certificate request.", NULL, hr);

	return hr;
}



HRESULT InstallCert(VOID)
{
	HRESULT hr = S_OK;
	CRegSettings usrSettings;
	_bstr_t tbstrCert = "";
	VARIANT varCertToInstall;
	IVSPTA* pVSPTA = NULL;
	CDlgCSR MyCsrDialog;
	int nRetDlg = -1;

	CoInitialize(NULL);

	VariantInit(&varCertToInstall);

	do
	{
		// Get the base64 encoded certificate from the user
		MyCsrDialog.m_CertOp = CERT_INSTALL;
		nRetDlg = MyCsrDialog.DoModal();

		if(nRetDlg == IDCANCEL)
		{
			hr = E_VSSCODE_CANCELLED;
			break;
		}

		if(nRetDlg != IDOK)
		{
			hr = E_VSSCODE_DLGERR;
			break;
		}

		hr = MyCsrDialog.GetCertificate(tbstrCert);
		CHECK_HRESULT_BREAK

		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_INSTALL;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		varCertToInstall.vt = VT_BSTR;
		varCertToInstall.bstrVal = tbstrCert.copy();

		hr = pVSPTA->InstallCert(&varCertToInstall);
		CHECK_HRESULT_BREAK

	}while(0);

	UnInitializePTA(pVSPTA);

	VariantClear(&varCertToInstall);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("InstallCert().", "Error occured during certificate install.", NULL, hr);

	return hr;
}


HRESULT ImportCert(VOID)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPTA = NULL;
	IVSP12Import* pP12Import = NULL;
	CRegSettings usrSettings;
	VARIANT varInputType, varFileName, varSerialNum, varIssuerDN;
	_bstr_t* ptbstrSelFile = NULL;
	DWORD dwNumFiles = 0;

	CoInitialize(NULL);

	VariantInit(&varInputType);
	VariantInit(&varFileName);
	VariantInit(&varSerialNum);
	VariantInit(&varIssuerDN);

	do
	{
		//  Get the file name from which to import the certificate
		hr = GetOpenFileNames(IDS_OPEN_PFX_TITLE, IDS_PFX_FILTER, FALSE, &ptbstrSelFile, &dwNumFiles);
		CHECK_HRESULT_BREAK

		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_IMPORT;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		hr = pVSPTA->get_IVSP12Import((IDispatch**)&pP12Import);
		CHECK_HRESULT_BREAK

		varInputType.vt = VT_I2;
		varInputType.iVal = 1;

		varFileName.vt = VT_BSTR;
		varFileName.bstrVal = (*ptbstrSelFile).copy();

		hr = pP12Import->ImportP12(&varInputType, &varFileName, &varSerialNum, &varIssuerDN);
		CHECK_HRESULT_BREAK

	}while(0);

	VariantClear(&varInputType);
	VariantClear(&varFileName);
	VariantClear(&varSerialNum);
	VariantClear(&varIssuerDN);

	if(ptbstrSelFile)
	{
		delete ptbstrSelFile;
		ptbstrSelFile = NULL;
	}

	RELEASE_INTERFACE_PTR(pP12Import)

	UnInitializePTA(pVSPTA);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("ImportCert().", "Error occured while importing the certificate.", NULL, hr);

	return hr;
}


HRESULT ExportCert(VOID)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPTA = NULL;
	IVSP12Export *pP12Export = NULL;
	CRegSettings usrSettings;
	VARIANT varOutputType, varFlags, varFileName;

	CoInitialize(NULL);

	VariantInit(&varOutputType);
	VariantInit(&varFlags);
	VariantInit(&varFileName);

	do
	{
		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = CERT_EXPORT;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		hr = pVSPTA->get_IVSP12Export((IDispatch**)&pP12Export);
		CHECK_HRESULT_BREAK

		varOutputType.vt = VT_I2;
		varOutputType.iVal = 1;

		varFileName.vt = VT_BSTR;
		varFileName.bstrVal = NULL;

		hr = pP12Export->ExportP12(&varOutputType, &varFlags, &varFileName);
		CHECK_HRESULT_BREAK

	}while(0);

	VariantClear(&varOutputType);
	VariantClear(&varFlags);
	VariantClear(&varFileName);

	RELEASE_INTERFACE_PTR(pP12Export)

	UnInitializePTA(pVSPTA);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("ExportCert().", "Error occured while exporting the certificate.", NULL, hr);

	return hr;
}


HRESULT ChangePassword(VOID)
{
	HRESULT hr = S_OK;
	IVSPTA* pVSPTA = NULL;
	CRegSettings usrSettings;
	IVSProfMgmt *pIVSProfMgmt = NULL;

	CoInitialize(NULL);

	do
	{
		// Get user settings from the registry
		hr = usrSettings.Read();
		CHECK_HRESULT_BREAK

		usrSettings.m_CertOp = PROF_CHANGE_PASSWD;

		// Initialize PTA with the user settings and get a pointer to PTA interface
		hr = InitializePTA(usrSettings, &pVSPTA);
		CHECK_HRESULT_BREAK

		hr = pVSPTA->get_IVSProfMgmt((IDispatch**)&pIVSProfMgmt);
		CHECK_HRESULT_BREAK

		hr = pIVSProfMgmt->ChangePassword();
		CHECK_HRESULT_BREAK

		hr = pIVSProfMgmt->SaveProfile();
		CHECK_HRESULT_BREAK

		hr = pIVSProfMgmt->CloseProfile();
		CHECK_HRESULT_BREAK

	}while(0);

	RELEASE_INTERFACE_PTR(pIVSProfMgmt)

	UnInitializePTA(pVSPTA);

	CoUninitialize();

	if(hr != S_OK)
		_LogErrorMsg("ChangePassword().", "Error occured while changing the password.", NULL, hr);

	return hr;
}