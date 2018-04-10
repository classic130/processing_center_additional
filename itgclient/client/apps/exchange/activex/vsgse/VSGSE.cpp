// VSGSE.cpp : Implementation of CVSGSE

#include "stdafx.h"
#include "VGSE.h"
#include "VSGSE.h"
#include <windows.h>
#include "vsgseutil.h"


#define  ID_BARNAME  "EncryptSign"


HRESULT CVSGSE:: ReportError(HRESULT hr)
    {
        HLOCAL pMsgBuf = NULL;
    
        // If there's a message associated with this error, report that.
        if (::FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL, hr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &pMsgBuf, 0, NULL)
            > 0)
        {
            AtlReportError(CLSID_VSGSE, (LPCTSTR) pMsgBuf,IID_IVSGSE,hr);
		

        }
    
        // TODO: add some error messages to the string resources and
        // return those if FormatMessage doesn't return anything (not
        // all system errors have associated error messages).
        
        // Free the buffer, which was allocated by FormatMessage.

		if (pMsgBuf != NULL)
				::LocalFree(pMsgBuf);
		
		return hr;
            
        
    }


STDMETHODIMP CVSGSE::get_Alias(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t       bstrAlias=""; 

	hr=m_pProfAdmin.GetAlias(&bstrAlias);
	if(hr!=0)
		goto Quit;

	if(bstrAlias.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrAlias);
	else
		*pVal=NULL;

Quit:
	return hr;
}

STDMETHODIMP CVSGSE::get_DN(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t      bstrDN="";


	hr=m_pProfAdmin.GetDN(&bstrDN);
	if(hr!=0)
		goto Quit;

	if(bstrDN.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrDN);
	else
		*pVal=NULL;

	
Quit:
	return hr;
}

STDMETHODIMP CVSGSE::get_FullName(BSTR *pVal)
{
	
	hr=S_OK;
	_bstr_t    bstrFullName="";

	hr=m_pProfAdmin.GetFullName(&bstrFullName);
	if(hr!=0)
		 goto Quit;

	if(bstrFullName.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrFullName);
	else
		*pVal=NULL;
Quit:
	 return hr;
}

STDMETHODIMP CVSGSE::get_HomeMTA(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t       bstrHomeMTA="";

	hr=m_pProfAdmin.GetHomeMTA(&bstrHomeMTA);
	if(hr!=0)
		goto Quit;

	if(bstrHomeMTA.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrHomeMTA);
	else
		*pVal=NULL;
Quit:
	return hr;
}

STDMETHODIMP CVSGSE::get_ProfileServer(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t     bstrProfileServer;
	hr=m_pProfAdmin.GetHomeServer(&bstrProfileServer);
	if(hr!=0)
		goto Quit;

	if(bstrProfileServer.length()>0)
				*pVal=SysAllocString((wchar_t *)bstrProfileServer);
		else
				*pVal=NULL;

Quit:
	return hr;
}

STDMETHODIMP CVSGSE::get_ExchServer(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t     bstrExchServer;
	hr=m_pProfAdmin.GetExchServer(&bstrExchServer);
	if(hr!=0)
		goto Quit;

	if(bstrExchServer.length()>0)
				*pVal=SysAllocString((wchar_t *)bstrExchServer);
		else
				*pVal=NULL;

Quit:
	return hr;
	
}

STDMETHODIMP CVSGSE::get_RFC822Name(BSTR *pVal)
{
	hr=S_OK;

	_bstr_t       bstrRFC822="";
	hr=m_pProfAdmin.GetRFC822MailBox(&bstrRFC822);
	if(hr!=0)
		goto Quit;

	if(bstrRFC822.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrRFC822);
	else
		*pVal=NULL;

Quit:
	 return hr;
}

STDMETHODIMP CVSGSE::PromptForSelection()
{
	HRESULT    hr=S_OK;
	hr=m_pProfAdmin.PromptProfileSelection();
	if(hr!=0)
		return hr;

	return hr;
}

STDMETHODIMP CVSGSE::put_MailDN(BSTR newVal)
{
	HRESULT    hr=S_OK;
	if(newVal!=NULL)
		m_pProfAdmin.ghbstrMailDN=newVal;

	return hr;
}

STDMETHODIMP CVSGSE::put_ServerName(BSTR newVal)
{

	HRESULT    hr=S_OK;
	if(newVal!=NULL)
		m_pProfAdmin.ghbstrHomeServer=newVal;

	return hr;
}


STDMETHODIMP CVSGSE::AddEncryptSignButton()
{
	hr=m_pProfAdmin.AddEncrypt_SignButton();
	return hr;
}

STDMETHODIMP CVSGSE::get_ProfileName(BSTR *pVal)
{
	hr=S_OK;
	if(!m_pProfAdmin.gLDAPAccess)
	{
		hr=m_pProfAdmin.GetAttributes();
		if(hr!=0)
			goto Quit;
	}
	if(m_pProfAdmin.ghbstrCurrentProfile.length()>0)
		*pVal=SysAllocString((wchar_t *)m_pProfAdmin.ghbstrCurrentProfile);
	else
		*pVal=NULL;

Quit:
	return hr;
}

STDMETHODIMP CVSGSE::put_ProfileName(BSTR newVal)
{
	HRESULT    hr=S_OK;
	
	if(newVal!=NULL)
	{
		m_pProfAdmin.bstrCurrentProfile=newVal;
	}
	else
		return E_FAIL ;

	return hr;
}

STDMETHODIMP CVSGSE::get_EnableCRLDistPoint(short *pVal)
{
    BOOL bResult = TRUE;


	long   err;
	DWORD dwPolicyFlag;
	DWORD dwType=REG_DWORD;
	
	TCHAR szKey[MAXLEN];
	HKEY hRegKey = NULL;

	ULONG lSize = sizeof(DWORD);

	_tcscpy(szKey, _T("SOFTWARE\\Microsoft\\Cryptography\\{7801ebd0-cf4b-11d0-851f-0060979387ea}"));
	
	err=RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey,0,KEY_ALL_ACCESS, &hRegKey);
	
	if(err!= ERROR_SUCCESS) 
		return err;

	err=RegQueryValueEx(hRegKey, _T("PolicyFlags"), NULL, &dwType, 
												( BYTE *)&dwPolicyFlag, &lSize);
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	
	RegCloseKey(hRegKey);

	if(dwPolicyFlag==0x10000)
		*pVal=TRUE;
	else
		*pVal=FALSE;

	return S_OK;
}

STDMETHODIMP CVSGSE::put_EnableCRLDistPoint(short newVal)
{
	BOOL bResult = TRUE;

	long   err;
	DWORD dwPolicyFlag;
	DWORD dwCRLDPCheck=0; 
	
	CHAR szKey[MAXLEN];
	CHAR szKeyValue[MAXLEN];
	CHAR pSysDir[MAXLEN];
	
	HKEY hRegKey = NULL;

    DWORD dwType=REG_DWORD, dwDisposition = 0 ;
	ULONG lSize = sizeof(DWORD);


	/*---------------CRLEnable  -----------------------*/
	_tcscpy(szKey, _T("SOFTWARE\\VeriSign\\GSE"));

	err = RegCreateKeyEx(
					HKEY_CURRENT_USER,
					szKey,
					0,
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hRegKey,
					&dwDisposition) ;
	 
	if ( dwDisposition == NULL || err != ERROR_SUCCESS )
	{
		return err ;
	}

	
	dwCRLDPCheck=newVal;

	err=RegSetValueEx(hRegKey, _T("CRLDPCheck"), 0, REG_DWORD, 
												(CONST BYTE *)&dwCRLDPCheck, sizeof(DWORD));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	RegCloseKey(hRegKey);

	_tcscpy(szKey, _T("SOFTWARE\\Microsoft\\Cryptography\\{7801ebd0-cf4b-11d0-851f-0060979387ea}"));
	err = RegCreateKeyEx(
					HKEY_LOCAL_MACHINE,
					szKey,
					0,
					NULL,
					REG_OPTION_NON_VOLATILE,
					KEY_ALL_ACCESS,
					NULL,
					&hRegKey,
					&dwDisposition) ;
	 
	if ( dwDisposition == NULL || err != ERROR_SUCCESS )
	{
		return err ;
	}

	if(newVal==1)
		dwPolicyFlag=0x00010000;
	else
		dwPolicyFlag=0xFFFEFFFF;

	err=RegSetValueEx(hRegKey, _T("PolicyFlags"), 0, REG_DWORD, 
												(CONST BYTE *)&dwPolicyFlag, sizeof(DWORD));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	RegCloseKey(hRegKey);


	// To Get install Path for extension DLL--------------------
	_tcscpy(szKey, _T("SOFTWARE\\VeriSign\\GSE"));
	err=RegOpenKeyEx(HKEY_CURRENT_USER, szKey,0,KEY_ALL_ACCESS, &hRegKey);
	
	if(err!= ERROR_SUCCESS) 
		return err;

	DWORD dwTypeExt=REG_SZ;
	DWORD dwLenExt=MAXLEN;

	err=RegQueryValueEx(hRegKey, _T("ExtInstallPath"), NULL, &dwTypeExt, 
												( BYTE *)&pSysDir,&dwLenExt);
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	
	RegCloseKey(hRegKey);


	//make the registry setting to register the exchange extensions
	_tcscpy(szKey, _T("Software\\Microsoft\\Exchange\\Client\\Extensions"));

	err=RegOpenKeyEx(
					HKEY_LOCAL_MACHINE,
					szKey,
					0,
					KEY_ALL_ACCESS, 
					&hRegKey
					);
	if(err!= ERROR_SUCCESS) 
		return err;


	strcpy(szKeyValue,"4.0;");
	strcat(szKeyValue,pSysDir);
	strcat(szKeyValue,"\\VSGSEEXT.dll");
	strcat(szKeyValue,";1;01111111111110;1100000;");


	//_tcscpy(szKeyValue, _T("4.0;D:\\WINNT40s\\SYSTEM32\\VSCRLCHECK.dll;1;01111111111110;1100000;"));

	err=RegSetValueEx(hRegKey, _T("GSE Extensions"), 0, REG_SZ, 
												(CONST BYTE *)&szKeyValue, strlen(szKeyValue));
	if(err!=ERROR_SUCCESS)
	{
		return err;
	}
	RegCloseKey(hRegKey);
	return S_OK;

}

STDMETHODIMP CVSGSE::UpdateClientExt()
{
	hr=S_OK;

	hr=m_pProfAdmin.UpdateClientExt();
	if(hr!=0)
		return hr;
	return hr;
}

STDMETHODIMP CVSGSE::get_CAInfo(short *pVal)
{

	return S_OK;
}

STDMETHODIMP CVSGSE::put_CAInfo(short newVal)
{

	m_pProfAdmin.gh_CAInfo=newVal;

	return S_OK;
}

STDMETHODIMP CVSGSE::get_ExchangeVer(short *pVal)
{
	hr=S_OK;
	if(!m_pProfAdmin.ghVer)
	{
		hr=m_pProfAdmin.FindExchVer(m_pProfAdmin.ghbstrCurrentProfile);
		if(hr!=S_OK)
		{
			return hr;
		}
	}
	
	*pVal=m_pProfAdmin.ghExchVer;
	return hr;
}

STDMETHODIMP CVSGSE::put_ExchangeVer(short newVal)
{

	m_pProfAdmin.ghExch_UpdateVer=newVal;
	return S_OK;
}

STDMETHODIMP CVSGSE::get_ADServerInfo(short *pVal)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CVSGSE::put_ADServerInfo(short newVal)
{
	
    m_pProfAdmin.ghADServerInfo=newVal;
	return hr;
	
}

STDMETHODIMP CVSGSE::get_ADServerInfoList(BSTR *pVal)
{
	// TODO: Add your implementation code here
	return S_OK;
}

STDMETHODIMP CVSGSE::put_ADServerInfoList(BSTR newVal)
{
	HRESULT    hr=S_OK;
	m_pProfAdmin.ghbstrADServerInfoList=newVal;

	return hr;

	
}

STDMETHODIMP CVSGSE::get_UserDN(BSTR *pVal)
{
	hr=S_OK;
	_bstr_t     bstrUserDN="";

	hr=m_pProfAdmin.GetUserDN(&bstrUserDN);
	if(hr!=0)
		goto Quit;

	if(bstrUserDN.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrUserDN);
	else
		*pVal=NULL;

Quit:
	return hr;
}

STDMETHODIMP CVSGSE::put_UserDN(BSTR newVal)
{

	HRESULT    hr=S_OK;
	if(newVal!=NULL)
		m_pProfAdmin.ghbstrMailDN=newVal;
	return hr;
}



STDMETHODIMP CVSGSE::get_ExchangeVerString(BSTR *pVal)
{
	hr=S_OK;


	if(!m_pProfAdmin.ghVer)
	{
		hr=m_pProfAdmin.FindExchVer(m_pProfAdmin.ghbstrCurrentProfile);
		if(hr!=S_OK)
			return hr;
	}

	if(m_pProfAdmin.ghbstrExchVerStr.length()>0)
		*pVal=SysAllocString((wchar_t *)m_pProfAdmin.ghbstrExchVerStr);
	else
		*pVal=NULL;

	return S_OK;
}


STDMETHODIMP CVSGSE::put_PKCS7(BSTR newVal)
{
	hr=m_pProfAdmin.VerifyCertChain(newVal);
	return hr;
}

STDMETHODIMP CVSGSE::get_UserPrincipalName(BSTR *pVal)
{
	_bstr_t      bstrupn="";
	hr=S_OK;

	hr=m_pProfAdmin.GetUserPrincipalName(&bstrupn);
	if(hr!=0)
		 goto Quit;

	if(bstrupn.length()>0)
		*pVal=SysAllocString((wchar_t *)bstrupn);
	else
		*pVal=NULL;

Quit:
	 return hr;
}

STDMETHODIMP CVSGSE::get_IsUserMemberOfAdminGroup(BSTR *pVal)
{
	
	hr=S_OK;
	BOOL bResult = FALSE;

	hr = m_pProfAdmin.IsUserMemberOfAdminGroup(&bResult);
	if (bResult == TRUE)
	{
		bstrRetVal = _MultiToWideString("1");	
	}
	else {
		bstrRetVal = _MultiToWideString("0");
	}
		
    *pVal = SysAllocString(bstrRetVal);
	SysFreeString(bstrRetVal);

	return hr;
}


STDMETHODIMP CVSGSE::put_CertFriendlyName(BSTR newVal)
{
	hr = S_OK;
	
	hr=m_pProfAdmin.CertFriendlyName(newVal);
	return hr;
}




STDMETHODIMP CVSGSE::get_CharEncodingInfo(short *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CVSGSE::put_CharEncodingInfo(short newVal)
{
	m_pProfAdmin.ncharEncodingInfo=newVal;
	return S_OK;
}



STDMETHODIMP CVSGSE::get_Explode_DN(VARIANT *pVal)
{

	SAFEARRAY*		psa;


	SAFEARRAYBOUND rgsabound[1];

	rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = m_pProfAdmin.nNumOfDNAttrs;
	psa = SafeArrayCreate(VT_VARIANT, 1, rgsabound);

			
			for (unsigned int i =0;
						i<m_pProfAdmin.nNumOfDNAttrs; i++)
			{

				_bstr_t      bstrRDN="";

				bstrRDN+=m_pProfAdmin.ptbstrDNAttrs[m_pProfAdmin.nNumOfDNAttrs-i-1];
				bstrRDN+=L"=";
				if(m_pProfAdmin.ncharEncodingInfo==1)
					bstrRDN+=L"<0C>";

				bstrRDN+=L"\"";
				bstrRDN+=m_pProfAdmin.ptbstrDNVals[m_pProfAdmin.nNumOfDNAttrs-i-1];
				bstrRDN+=L"\"";

							
				long ix[1];

				VARIANT var;
				ix[0] = i;

				var.vt = VT_BSTR;
				var.bstrVal = bstrRDN.copy();

				SafeArrayPutElement(psa, ix, &var);
				VariantClear(&var);
			}

		    


			pVal->vt = VT_ARRAY|VT_VARIANT;
			pVal->parray = psa;	

			return S_OK;
}

STDMETHODIMP CVSGSE::put_RenewCert(short newVal)
{
	m_pProfAdmin.bRenewCert=newVal;
	return S_OK;
}

STDMETHODIMP CVSGSE::put_SetEFSCertificate(short newVal)
{
	
	m_pProfAdmin.bSetEFSCert=newVal;
	return S_OK;
}

STDMETHODIMP CVSGSE::get_CertSerialNum(BSTR *pVal)
{
	hr=S_OK;
	if(m_pProfAdmin.gLDAPAccess)
	{
		if(m_pProfAdmin.m_bstrSerialNum.length()>0)
			*pVal=SysAllocString((wchar_t *)m_pProfAdmin.m_bstrSerialNum);
		else
			*pVal=NULL;
	}
	else
		*pVal=NULL;

	return hr;
}


// Start Add: Infosys : CR27993
/*****************************************************************************/
// get_SetDefaultCertFlag() : Retrieves the current value of nSetDefaultCertFlag,
//							  This flag specifies whether the certificate issued is
//							  to be made default for Signing, Encryption or Both
//
//  Input/Output :
//	  pVal : SHORT *
//			Short pointer to the variable where flag value will be retrieved.
//  Returns :
//    S_OK
/*****************************************************************************/

STDMETHODIMP CVSGSE::get_SetDefaultCertFlag(short *pVal)
{
	*pVal = m_pProfAdmin.nSetDefaultCertFlag;
	return S_OK;
}

/*****************************************************************************/
// put_SetDefaultCertFlag() : Sets the value of nSetDefaultCertFlag,
//							  This flag specifies whether the certificate issued is
//							  to be made default for Signing, Encryption or Both
//
//  Input/Output :
//	  newVal : SHORT
//			Contains value to be assigned to the flag.
//  Returns :
//    S_OK
/*****************************************************************************/

STDMETHODIMP CVSGSE::put_SetDefaultCertFlag(short newVal)
{
	m_pProfAdmin.nSetDefaultCertFlag = newVal;
	return S_OK;
}
// End Add : Infosys : CR27993

// Start Add : Infosys : CR21346
/*****************************************************************************/
// get_FirstName() : Gets the value of user first name "givenName" from the LDAP 
//					 directory. Invokes cProfAdmin functions to inturn to scan 
//					 through the LDAp directory parameters and get the required one.
//
// Output :
//	  pVal : BSTR *
//			Contains the retrieved value user First Name.
// Returns :
//    S_OK, error code
/*****************************************************************************/

STDMETHODIMP CVSGSE::get_FirstName(BSTR *pVal)
{
	// Initialise the value of return variable
	hr = S_OK;
	_bstr_t    bstrFirstName = "";

	// Invoke CProfAdmin method to retrieve the value.
	hr = m_pProfAdmin.GetUserFirstName(&bstrFirstName);
	if ( hr != S_OK )
	{
		return hr;
	}
	
	if ( bstrFirstName.length() > 0 )
	{
		*pVal = SysAllocString((wchar_t *)bstrFirstName);
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

/*****************************************************************************/
// get_LastName() : Gets the value of user first name "sn" from the LDAP directory.
//					Invokes cProfAdmin functions to inturn to scan through the LDAP
//				    directory parameters and get the required one.
//
// Output :
//	  pVal : BSTR *
//			Contains the retrieved value of user last name.
// Returns :
//    S_OK, error code
/*****************************************************************************/

STDMETHODIMP CVSGSE::get_LastName(BSTR *pVal)
{
	// TODO: Add your implementation code here
	// Initialise the value of return variable
	hr = S_OK;
	_bstr_t    bstrLastName = "";

	// Invoke CProfAdmin method to retrieve the value.
	hr = m_pProfAdmin.GetUserLastName(&bstrLastName);
	if ( hr != S_OK )
	{
		return hr;
	}
	
	if ( bstrLastName.length() > 0 )
	{
		*pVal = SysAllocString((wchar_t *)bstrLastName);
	}
	else
	{
		*pVal = NULL;
	}

	return S_OK;
}

// End Add : Infosys : CR21346>>>>>>> 1.17.12.1
