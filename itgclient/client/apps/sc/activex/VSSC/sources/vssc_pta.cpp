#include "stdafx.h"
#include "certmgmt.h"
#include "VSSC_SMIME.h"

extern    DWORD    g_dwAppErr;

BOOL SelectCertForSigning(IVSPTA *pVSPTA,char *szCertIssuerDN,char *szCertSerialNum)
{
	
	HRESULT hr=S_OK;

	IVSSelectedDigID *pSelDigID = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSProfMgmt *pProfMgmt=NULL;


	VARIANT   varBool;
	VARIANT   varUI;
	VARIANT   varNotification;

	VariantInit(&varBool);
	VariantInit(&varUI);
	VariantInit(&varNotification);

	do
	{

			hr = pVSPTA -> get_IVSProfMgmt((IDispatch**) &pProfMgmt );
			CHECK_HRESULT_BREAK

			hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
			CHECK_HRESULT_BREAK

			varBool.vt=VT_BOOL;
			varBool.boolVal=0;

			hr = pPTADllApi->put_HashData(varBool);
			CHECK_HRESULT_BREAK

			hr = pPTADllApi->put_P7Output(varBool);
			CHECK_HRESULT_BREAK

			hr = pPTADllApi->put_ShowSignUI(varBool);
			CHECK_HRESULT_BREAK
			
			varUI.vt=VT_I4;
			varUI.lVal=0;


			hr = pPTADllApi->put_DecryptUI(varUI);
			CHECK_HRESULT_BREAK

			varNotification.vt=VT_BOOL;
			varNotification.boolVal=FALSE;

			hr = pPTADllApi->put_SignNotificationUI(varNotification);
			CHECK_HRESULT_BREAK

			// Get the issuer DN to be set as a cert selection criteria
			if(!SetCertSelectionCriteria(szCertIssuerDN, 
										szCertSerialNum,pVSPTA))
			{
						
						break;
			}


			hr=pProfMgmt->OpenProfile();
			if(hr != S_OK)
			{
				if (hr!=E_CARDALREADYOPEN)
					{
							
							break;
					}
				
			}

			hr = pVSPTA->SelIDForTrans();
			CHECK_HRESULT_BREAK

			// Get certificate context and other details 
			// of the selected digital ID
			hr = pVSPTA->get_IVSSelectedDigID((IDispatch**)&pSelDigID);
			CHECK_HRESULT_BREAK

	}
	while(0);

	VariantClear(&varBool);
	VariantClear(&varUI);
	VariantClear(&varNotification);

	RELEASE_INTERFACE_PTR(pSelDigID)
	RELEASE_INTERFACE_PTR(pPTADllApi)
	RELEASE_INTERFACE_PTR(pProfMgmt)
	
			
	return hr;
}


BOOL SelectCertForDecryption(IVSPTA *pVSPTA,VS_PKCS7_INFO *vsspiPKCS7Info,
							 VSSC_CERT_RDN_INFO *CertRDNInfo ,DWORD *pdwSelectedCert)
{
	
	HRESULT		hr=S_OK;
	VARIANT		varBool;
	VARIANT		varUI;
	VARIANT     VarNotification;
	VARIANT     varSubjectDN;
	VARIANT     varIssuerDN;
	VARIANT     varSerialNum;


	IVSSelectedDigID *pSelDigID = NULL;
	IVSPTADllApi *pPTADllApi = NULL;
	IVSProfMgmt *pProfMgmt=NULL;



	LPSTR		pszSerialNumber=NULL,pszIssureDN=NULL;

	VariantInit(&varBool);
	VariantInit(&varUI);
	VariantInit(&VarNotification);
	VariantInit(&varSubjectDN);
	VariantInit(&varIssuerDN);
	VariantInit(&varSerialNum);

	ZeroMemory(CertRDNInfo,sizeof(VSSC_CERT_RDN_INFO));

	do
	{
			hr = pVSPTA -> get_IVSProfMgmt((IDispatch**) &pProfMgmt );
			CHECK_HRESULT_BREAK

			hr = pVSPTA->QueryInterface(IID_IVSPTADllApi, (void **) &(pPTADllApi));
			CHECK_HRESULT_BREAK
		
			varBool.vt=VT_BOOL;
			varBool.boolVal=0;

			hr = pPTADllApi->put_HashData(varBool);
			CHECK_HRESULT_BREAK

			hr = pPTADllApi->put_P7Output(varBool);
			CHECK_HRESULT_BREAK

			hr = pPTADllApi->put_ShowSignUI(varBool);
			CHECK_HRESULT_BREAK

			varUI.vt=VT_I4;
			varUI.lVal=0;
			hr = pPTADllApi->put_DecryptUI(varUI);
			CHECK_HRESULT_BREAK
		
			VarNotification.vt=VT_BOOL;
			VarNotification.boolVal=FALSE;

			hr = pPTADllApi->put_SignNotificationUI(VarNotification);
			CHECK_HRESULT_BREAK

			hr=pProfMgmt->OpenProfile();
			if(hr != S_OK)
			{
				if (hr!=E_CARDALREADYOPEN)
					{
							
							break;
					}
				
			}

			for(int i=0;i<vsspiPKCS7Info->EncryptedDataInfo.nRecipientInfos;i++)
			{

					pszSerialNumber=Enc_GetCertSerNum(&vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[i]);
					pszIssureDN=Enc_GetCertIssuerDN(&vsspiPKCS7Info->EncryptedDataInfo.pRecipientInfo[i]);

					// Get the issuer DN to be set as a cert selection criteria
					if(!SetCertSelectionCriteria(pszIssureDN, 
												pszSerialNumber,pVSPTA))
					   break;

					FREE_MEMORY(pszSerialNumber)
					FREE_MEMORY(pszIssureDN)

					hr = pVSPTA->SelIDForTrans();
					if(hr == S_OK)
					{
						*pdwSelectedCert=i;
						// Get certificate context and other details 
						// of the selected digital ID
						hr = pVSPTA->get_IVSSelectedDigID((IDispatch**)&pSelDigID);
						if(hr == S_OK)
						{
							
							hr=pSelDigID->get_SubjectDN(&varSubjectDN);
							CHECK_HRESULT_BREAK
							CertRDNInfo->bstrSubjectDN=varSubjectDN.bstrVal;
							
							/*
							_bstr_t   bstrTmp=CertRDNInfo->bstrSubjectDN.copy();
							
							wchar_t   *pwcRDN=NULL;
							wchar_t	  *pwcEmail=NULL;
							////Fix
							wchar_t   *pwcFind=L" E=" ;////Space before E=
							int        nwcFind=wcslen(pwcFind);
							pwcRDN=wcstok(bstrTmp,L";");
							while(pwcRDN!=NULL)
							{
								if(wcsncmp(pwcRDN,pwcFind,nwcFind)==0)
								{
									int nwcRDN=wcslen(pwcRDN);
									pwcEmail=(wchar_t *)malloc(nwcRDN+nwcFind+5);
									CHECK_MEM_BREAK(pwcEmail)
									
									memset(pwcEmail,0,nwcRDN+nwcFind+5);
									wcscpy(pwcEmail,pwcRDN+nwcFind);
									
									_bstr_t  bstrEmailTmp(pwcEmail);
									CertRDNInfo->bstrEmailID=bstrEmailTmp.copy();
									
									break;
								}

								pwcRDN=wcstok(NULL,L";");
							}
							//FREE_MEMORY(pwcEmail);
							*/

							char *pszSubjectDN=_WideToMultiString(varSubjectDN.bstrVal);
							CHECK_MEM_BREAK(pszSubjectDN)
							char *pszToken=NULL;
							char *pszFind=" E=";
							char *pszEmail=NULL;

							pszToken=strtok(pszSubjectDN,";");
							while(pszToken!=NULL)
							{
								if(strncmp(pszToken,pszFind,strlen(pszFind))==0)
								{
									int   nszFind=strlen(pszFind);
									int nszToken=strlen(pszToken);

									pszEmail=(char*)malloc(nszToken+nszFind+1);
									strcpy(pszEmail,pszToken+nszFind);
									_bstr_t  bstrEmailTmp(pszEmail);
									CertRDNInfo->bstrEmailID=bstrEmailTmp;
									break;

								}
								pszToken=strtok(NULL,";");
							}
							FREE_MEMORY(pszEmail);
							FREE_MEMORY(pszSubjectDN);

							hr=pSelDigID->get_IssuerDN(&varIssuerDN);
							CHECK_HRESULT_BREAK
							CertRDNInfo->bstrIssuerDN=varIssuerDN.bstrVal;

							hr=pSelDigID->get_SerNum(&varSerialNum);
							CHECK_HRESULT_BREAK
							CertRDNInfo->bstrSerialNum=varSerialNum.bstrVal;

							break;
						}
						
						
					}
					else
					{
						if(hr==E_USERCANCELLED)
										break;
					}

					
					
			}

			

	}
	while(0);

	VariantClear(&varBool);
	VariantClear(&varUI);
	VariantClear(&VarNotification);
	VariantClear(&varSubjectDN);
	VariantClear(&varIssuerDN);
	VariantClear(&varSerialNum);


	RELEASE_INTERFACE_PTR(pSelDigID)
	RELEASE_INTERFACE_PTR(pPTADllApi)
	RELEASE_INTERFACE_PTR(pProfMgmt)

	FREE_MEMORY(pszIssureDN)
    FREE_MEMORY(pszSerialNumber)
			
	return hr;
}

/*	Selection criteria for selecting certificates using the PTA
	I/P Parameters -
	'bPrompt' - decides whether the certificate selection dialog should
				be shown
	'pVSPTA'  - pointer to the PTA control
	Returns TRUE on success, FALSE on failure
*/
BOOL SetCertSelectionCriteria(char *szCertIssuerDN, char *szCertSerialNum, IVSPTA *pVSPTA)
{
	HRESULT hr;
	IVSSrchCrit *pSrchCrit = NULL;
	VARIANT var;
	OLECHAR *pSelSerNum = NULL, *pSelIssuerDN = NULL;
	
	hr = pVSPTA->get_IVSSrchCrit((IDispatch**)&pSrchCrit);
	if(hr != S_OK)
		return (FALSE);

	pSelIssuerDN = new OLECHAR [lstrlen(szCertIssuerDN) + 1];
	MultiByteToWideChar(CP_ACP, 0, szCertIssuerDN, 
		-1, pSelIssuerDN, lstrlen(szCertIssuerDN) + 1);

	var.vt = VT_BSTR;
	var.bstrVal = SysAllocString(pSelIssuerDN);
	hr = pSrchCrit->put_IssuerDN(var);
	if(hr != S_OK)
		return (FALSE);

	VariantClear(&var);

	pSelSerNum = new OLECHAR [lstrlen(szCertSerialNum) + 1];
	MultiByteToWideChar(CP_ACP, 0, szCertSerialNum, 
		-1, pSelSerNum, lstrlen(szCertSerialNum) + 1);

	var.vt = VT_BSTR;
	var.bstrVal = SysAllocString(pSelSerNum);
	hr = pSrchCrit->put_SerNum(var);
	if(hr != S_OK)
		return (FALSE);

	VariantClear(&var);

	DELETE_MEMORY(pSelIssuerDN)
	DELETE_MEMORY(pSelSerNum)
	
	RELEASE_INTERFACE_PTR(pSrchCrit)
	
	return TRUE;
}


