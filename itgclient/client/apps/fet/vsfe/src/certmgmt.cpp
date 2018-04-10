#include "stdafx.h"
#include <shlobj.h>
#include <hlink.h>
#include "global.h"
#include "slist.h"
#include "cryptsup.h"
#include "ptav3.h"
#include "ptadefines.h"
#include "util.h"
#include "certmgmt.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "resource.h"


extern PolicyVars g_LocalPolicy;
extern SafeSettings g_SafeProp;

// Get a certificate from the Host specified in the Policy or from the public site
VOID GetCertificate(VOID)
{
	WCHAR wcUrl[MAX_PATH_LEN];
	TCHAR szUrl[MAX_PATH_LEN];

	// 'szRemoteHost' should contain the Enterprise Server URL 
	if(g_LocalPolicy.szRemoteHost[0] != '\0')
	{
		lstrcpy(szUrl, g_LocalPolicy.szRemoteHost);
		SmartAppendFrontslash(szUrl);
		lstrcat(szUrl, "VSApps/");
		lstrcat(szUrl, DIGID_CENTER);
	}
	else	// Default to public site
		lstrcpy(szUrl, DIGID_CENTER_URL);

	MultiByteToWideChar(CP_ACP, 0, szUrl, -1, wcUrl, sizeof(wcUrl));
	HlinkSimpleNavigateToString(wcUrl, NULL, NULL, NULL, NULL, NULL, HLNF_OPENINNEWWINDOW, NULL);

	return;
}


/*	Selection criteria for selecting certificates using the PTA
	I/P Parameters -
	'bPrompt' - decides whether the certificate selection dialog should
				be shown
	'pVSPTA'  - pointer to the PTA control
	Returns TRUE on success, FALSE on failure
*/
BOOL SetCertSelectionCriteria(BOOL bPrompt, IVSPTA *pVSPTA)
{
	HRESULT hr;
	IVSSrchCrit *pSrchCrit = NULL;
	IVSUIPrefs *pUIPrefs = NULL;
	BOOL bRetVal = FALSE;
	VARIANT var;
	OLECHAR *pIssuerDN = NULL, *pSelSerNum = NULL, *pSelIssuerDN = NULL;
	
	do
	{
		hr = pVSPTA->get_IVSSrchCrit((IDispatch**)&pSrchCrit);
		if(hr != S_OK)
		{
			LogErrorMessage("SetCertSelectionCriteria:get_IVSSrchCrit() failed", hr);
			break;
		}

		if(bPrompt)
		{
			hr = pVSPTA->get_IVSUIPrefs((IDispatch**)&pUIPrefs);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:get_IVSUIPrefs() failed", hr);
				break;
			}

			// no logo?
			var.vt = VT_BSTR;
			var.bstrVal = L"";
			hr = pUIPrefs->put_UILogoUrl(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_UILogoUrl() failed", hr);
				break;
			}
			
			var.vt = VT_BOOL;
			var.boolVal = FALSE;
			hr = pUIPrefs->put_SelID_ShowDefChkBox(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_SelID_ShowDefChkBox() failed", hr);
				break;
			}

			// a search criteria has to be added for the AT_KEYEXCHANGE/AT_SIGNATURE
			//pVSPrefMgmt->put_SrchCrit_KeyType(AT_KEYEXCHANGE/AT_SIGNATURE);

			var.vt = VT_I2;
			var.iVal = EXP_DATE_GREATER_THAN;
			hr = pSrchCrit->put_DateEquality(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_SrchCrit_DateEquality() failed", hr);
				break;
			}

			var.vt = VT_BOOL;
			var.boolVal = FALSE;
			hr = pSrchCrit->put_Renewed(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_CertPref_MarkAsRenewed() failed", hr);
				break;
			}

			DATE Date;
			UDATE uDate;
			ULONG ulFlags = 0;
			GetSystemTime(&uDate.st); 
			VarDateFromUdate(&uDate, ulFlags, &Date);

			hr = pSrchCrit->put_ExpDate(Date);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_SrchCrit_ExpDate() failed", hr);
				break;
			}

			// Set NULL for IssuerDN and SerialNum (clear what was previously set)
			var.vt = VT_BSTR;
			var.bstrVal = L"";
			hr = pSrchCrit->put_IssuerDN(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_IssuerDN() failed", hr);
				break;
			}

			var.vt = VT_BSTR;
			var.bstrVal = L"";
			hr = pSrchCrit->put_SerNum(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_SerNum() failed", hr);
				break;
			}

			pIssuerDN = new OLECHAR [lstrlen(g_LocalPolicy.szIssuerDN) + 1];
			MultiByteToWideChar(CP_ACP, 0, g_LocalPolicy.szIssuerDN, 
				-1, pIssuerDN, lstrlen(g_LocalPolicy.szIssuerDN) + 1);

			var.vt = VT_BSTR;
			var.bstrVal = SysAllocString(pIssuerDN);
			pSrchCrit->put_IssuerDN(var);
			VariantClear(&var);

			bRetVal = TRUE;
		}
		else
		{
			if(!g_SafeProp.pCurrEncrCert)
			{
				LogErrorMessage("SetCertSelectionCriteria() : No encryption cert selected", 0);
				return FALSE;
			}

			pSelIssuerDN = new OLECHAR [lstrlen(g_SafeProp.pCurrEncrCert->szIssuerDN) + 1];
			MultiByteToWideChar(CP_ACP, 0, g_SafeProp.pCurrEncrCert->szIssuerDN, 
				-1, pSelIssuerDN, lstrlen(g_SafeProp.pCurrEncrCert->szIssuerDN) + 1);

			var.vt = VT_BSTR;
			var.bstrVal = SysAllocString(pSelIssuerDN);
			hr = pSrchCrit->put_IssuerDN(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_IssuerDN() failed", hr);
				break;
			}
			VariantClear(&var);

			pSelSerNum = new OLECHAR [lstrlen(g_SafeProp.pCurrEncrCert->szSerialNum) + 1];
			MultiByteToWideChar(CP_ACP, 0, g_SafeProp.pCurrEncrCert->szSerialNum, 
				-1, pSelSerNum, lstrlen(g_SafeProp.pCurrEncrCert->szSerialNum) + 1);

			var.vt = VT_BSTR;
			var.bstrVal = SysAllocString(pSelSerNum);
			hr = pSrchCrit->put_SerNum(var);
			if(hr != S_OK)
			{
				LogErrorMessage("SetCertSelectionCriteria:put_SerNum() failed", hr);
				break;
			}
			VariantClear(&var);

			bRetVal = TRUE;
		}

	} while(0);

	
	if(pSelIssuerDN)
	{
		delete pSelIssuerDN;
		pSelIssuerDN = NULL;
	}

	if(pSelSerNum)
	{
		delete pSelSerNum;
		pSelSerNum = NULL;
	}

	if(pIssuerDN)
	{
		delete pIssuerDN;
		pIssuerDN = NULL;
	}

	if(pUIPrefs)
	{
		pUIPrefs->Release();
		pUIPrefs = NULL;
	}

	if(pSrchCrit)
	{
		pSrchCrit->Release();
		pSrchCrit = NULL;
	}

	return bRetVal;
}


//	Returns cert issuer DN in a format similar to that returned by PTA
LPTSTR GetCertIssuerDN(PCERT_INFO pCertInfo)
{
	CERT_NAME_BLOB NameBlob;
	DWORD dwSize = 0, dwError = 0;
	LPTSTR lpIssuerDN = NULL;
	//LPTSTR lpFormattedDN = NULL;

	if(!pCertInfo)
		return NULL;

	NameBlob = pCertInfo->Issuer;

    // Call CertNameToStr to get the Subject RDN string length.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, 
						   NULL, dwSize);

	// This function always returns a null char (0), so the minimum count returned 
	// will be 1, even if nothing got converted.
    if(dwSize <= 1) 
	{
		dwError = GetLastError();
		LogErrorMessage("GetCertIssuerDN() : CertNameToStr() failed", dwError);
        return NULL;
	}

    // Allocate memory for the returned string.
    lpIssuerDN = (LPTSTR)malloc((dwSize + 1) * sizeof(TCHAR));
    if(!lpIssuerDN)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("GetCertIssuerDN() : Out of memory", 0);
		return NULL;
	}
	
    // Call CertNameToStr to get the string.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, 
						   lpIssuerDN, dwSize);

    if(dwSize <= 1)
	{
		dwError = GetLastError();
		LogErrorMessage("GetCertIssuerDN() : CertNameToStr() failed", dwError);
		free(lpIssuerDN);
        return NULL;
	}

	return lpIssuerDN;

/*    
	// new PTA format is different from old one
	// Strip only quotes from the issuer dn 
	if((lpFormattedDN = (LPTSTR)malloc(sizeof(TCHAR)*(lstrlen(lpIssuerDN) + 1))) == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("GetCertIssuerDN() : Out of memory", 0);
		free(lpIssuerDN);
		return NULL;
	}
	else
	{
		for(int i = 0, j = 0; i <lstrlen(lpIssuerDN); i++)
		{
			if(lpIssuerDN[i] != '"')
			{
				lpFormattedDN[j] = lpIssuerDN[i];
				j++;
			}
		}

		lpFormattedDN[j] = '\0';
	}

	free(lpIssuerDN);
	return lpFormattedDN;*/
}


//	Returns cert serial number in a format similar to that returned by PTA
LPTSTR GetCertSerNum(PCERT_INFO pCertInfo)
{
	CRYPT_INTEGER_BLOB SerialNumberBlob ;
	DWORD dwSerialNumber = 0;
	PBYTE SerialNumber ;
	LPTSTR lpSerNum;

	if(!pCertInfo)
		return NULL;

    SerialNumberBlob = pCertInfo->SerialNumber;
	dwSerialNumber = SerialNumberBlob.cbData;
	
	if((SerialNumber = (PBYTE)malloc(dwSerialNumber)) == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("GetCertSerNum() : Out of memory", 0);
		return NULL;
	}
	else
	{
		// Reverse the bytes
		unsigned int i;
		for (i = 0; i < dwSerialNumber; i++)
			SerialNumber[dwSerialNumber-1-i] = SerialNumberBlob.pbData[i] ;

		if((lpSerNum = (LPTSTR)malloc(((dwSerialNumber*2)+1)*sizeof(TCHAR))) == NULL)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("GetCertSerNum() : Out of memory", 0);
			free(SerialNumber);
			return NULL;
		}
		else
		{
			for(i = 0; i < dwSerialNumber; i++)
				sprintf((lpSerNum)+(i*2), "%02x", (unsigned char)SerialNumber[i]) ;
			
			free(SerialNumber);
		}
	}

	return lpSerNum;
}