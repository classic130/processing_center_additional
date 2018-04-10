#include "stdafx.h"
#include <comutil.h>
#include <wininet.h>
#include <hlink.h>
#include "integrate.h"			// From bsafelite
#include "ptav3.h"
#include "seldigid.h"
#include "notarize.h"
#include "nzutils.h"
#include "nzdefines.h"
#include "nzerrs.h"
#include "ptaerrs.h"
#include "nzmacros.h"
#include "nzdatacc.h"
#include "resource.h"

/*
I/P -	'i_pErrLocation'	:	Function where the error occurred.
		'i_pErrDesc'	:	Description of the error.
		'i_pErrParam'	:	Any parameter which can be added to a formatted 'i_pErrDesc' string
		'i_dwErrCode'	:	An hresult or any Windows error that may have occurred.
Working -	Creates a log file at the location specified by 'VS_NZLOGFILE' and writes a well
			formatted error string. In addition to the above information this function also 
			writes the Windows user and the time when error occurred.
*/
VOID _LogErrorMsg(LPCTSTR i_pErrLocation, LPCTSTR i_pErrDesc, LPCTSTR i_pErrParam, DWORD i_dwErrCode)
{
	// Read registry key to check if error logging is enabled
	HKEY hNzKey = NULL;
	LONG lResult = 0;
	DWORD dwLogError = 0, dwSize = sizeof(dwLogError);

	lResult = RegOpenKeyEx(HKEY_CURRENT_USER, NZ_MAIN_KEY, 0, KEY_QUERY_VALUE, &hNzKey);
	if(lResult != ERROR_SUCCESS)
		return;

	lResult = RegQueryValueEx(hNzKey, NZ_LOG_ERROR, NULL, NULL, (LPBYTE)&dwLogError, &dwSize);
	
	RegCloseKey(hNzKey);
	hNzKey = NULL;

	if(lResult != ERROR_SUCCESS || dwLogError == 0)
		return;

	HANDLE hLogFile = NULL;
	TCHAR szErrString[ERR_STRING_LEN], szUserName[MAX_STRING_LEN], szErrDescription[MAX_STRING_LEN];
	DWORD dwUserName = sizeof(szUserName), dwBytesWritten = 0;
	SYSTEMTIME sysTime;

	do
	{
		hLogFile = CreateFile(VS_NZLOGFILE, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hLogFile == INVALID_HANDLE_VALUE)
			break;

		// Seek to the end of the file
		if(SetFilePointer(hLogFile, 0, NULL, FILE_END) == INVALID_SET_FILE_POINTER)
			break;

		// Get the logged on user name
		if(!GetUserName(szUserName, &dwUserName))
			lstrcpy(szUserName, "default");

		// Get the local time
		GetLocalTime(&sysTime);

		if(i_pErrParam)
			wsprintf(szErrDescription, i_pErrDesc, i_pErrParam);
		else
			lstrcpy(szErrDescription, i_pErrDesc);

		wsprintf(szErrString, "%s - %s : %d:%d,  %d:%d:%d : %s : %x.\r\n", i_pErrLocation, szUserName, sysTime.wHour, sysTime.wMinute, sysTime.wYear, sysTime.wMonth, sysTime.wDay, szErrDescription, i_dwErrCode);

		WriteFile(hLogFile, szErrString, lstrlen(szErrString), &dwBytesWritten, NULL);

	}while(0);

	if(hLogFile && hLogFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle(hLogFile);
		hLogFile = NULL;
	}
	
	return;
}

#if 0
_bstr_t _MapFailInfo(LPNzDetails i_pNotzDetails)
{
	UINT uErrorBit = 0;
	UINT iErrStringId = 0;
	WCHAR *wcErrString = NULL;
	_bstr_t bstrErrString = "";
		
	switch(i_pNotzDetails->dwFailInfo)
	{
		case 1 :
		{
			iErrStringId = IDS_ERRPOLICY;
			break;
		}

		case 2 :
		{
			iErrStringId = IDS_TIMENOTAVAIL;
			break;
		}

		case -1 :
		default :
		{
			if(i_pNotzDetails->bstrStatusMsg != _bstr_t(""))
				return i_pNotzDetails->bstrStatusMsg;

			iErrStringId = IDS_NZSERVER_ERR;
			break;
		}
	}
	

	if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), iErrStringId, &wcErrString) != S_OK)
	{
		_LogErrorMsg("_MapFailInfo().", "Error loading string.", NULL, 0);
		wcErrString = NULL;
	}

	bstrErrString = (wcErrString == NULL) ? _bstr_t("") : wcErrString;

	FREE_MEMORY(wcErrString)

	if(bstrErrString == _bstr_t("") && i_pNotzDetails->bstrStatusMsg != _bstr_t(""))
		bstrErrString = i_pNotzDetails->bstrStatusMsg;

	return bstrErrString;
}
#else
/*
	Compare the error status to the predefined error strings and map them to user friendly error messages.
*/
_bstr_t _MapFailInfo(LPNzDetails i_pNotzDetails)
{
	_bstr_t bstrErrString = "";
	UINT iErrStringId = IDS_NZSERVER_ERR;
	WCHAR *wcErrString = NULL;

	do
	{
		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_ALG))
		{
			iErrStringId = IDS_NZERR_ALG;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_WRONG_FORMAT))
		{
			iErrStringId = IDS_NZERR_WRONG_FORMAT;
			break;
		}


		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_TIME_UNAVAIL))
		{
			iErrStringId = IDS_NZERR_TIME_UNAVAIL;
			break;
		}


		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_POL_INVALID))
		{
			iErrStringId = IDS_ERRPOLICY;
			break;
		}


		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_SIG_FAIL))
		{
			iErrStringId = IDS_NZERR_SIG_FAIL;
			break;
		}
		
		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_CERT_REVOKED))
		{
			iErrStringId = IDS_NZERR_CERT_REVOKED;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_CERT_EXPIRED))
		{
			iErrStringId = IDS_NZERR_CERT_EXPIRED;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_CERT_INVALID))
		{
			iErrStringId = IDS_NZERR_CERT_INVALID;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_CERT_ABSENT))
		{
			iErrStringId = IDS_NZERR_CERT_ABSENT;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_NO_ACCT))
		{
			iErrStringId = IDS_NZERR_NO_ACCT;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_ACCT_INVALID))
		{
			iErrStringId = IDS_NZERR_ACCT_INVALID;
			break;
		}

		if(!lstrcmpi(i_pNotzDetails->bstrStatusMsg, NZERR_LIMIT))
		{
			iErrStringId = IDS_NZERR_LIMIT;
			break;
		}

		// This is an unmapped error
		if(!_strnicmp(i_pNotzDetails->bstrStatusMsg, NZERR_GENERAL, lstrlen(NZERR_GENERAL)))
			return i_pNotzDetails->bstrStatusMsg;

	}while(0);

	if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), iErrStringId, &wcErrString) != S_OK)
	{
		_LogErrorMsg("_MapFailInfo().", "Error loading string.", NULL, 0);
		wcErrString = NULL;
	}

	bstrErrString = (wcErrString == NULL) ? _bstr_t("") : wcErrString;

	FREE_MEMORY(wcErrString)

	if(bstrErrString == _bstr_t("") && i_pNotzDetails->bstrStatusMsg != _bstr_t(""))
		bstrErrString = i_pNotzDetails->bstrStatusMsg;		

	return bstrErrString;
}
#endif



/*
I/P	-	'hInst'	:	Module instance which contains the resource string.
		'wLangId'	:	The language for which the string is needed.
		'nStringID'	:	The ID of the string in the string table.
O/P -	'wstrOutBuf'	:	Contains the string from the string resource.
Return -	An hresult indicating the status of the operation.
Working -	This function loads the string from the appropriate string table. If assumes that 
			the language table exists and the string id is also correct.
*/
HRESULT _LoadStringW(HINSTANCE i_hInst, DWORD i_dwLangId, short i_nStringID, WCHAR** o_wstrOutBuff)
{
	HRSRC hRes;
	HGLOBAL hGlobal;
	PBYTE pbyteStringTable;
	WORD* pdwTempPtr;
	int i;
	WORD wStringLen;

	*o_wstrOutBuff = NULL;

	// Find the string table resource
	hRes = FindResourceEx(i_hInst, RT_STRING, (LPTSTR)(i_nStringID/16+1), (WORD)i_dwLangId);
	if(!hRes)
		return E_FAIL;
	
	// Load the resource
	hGlobal = LoadResource(i_hInst, hRes);
	if(!hGlobal)
		return E_OUTOFMEMORY;

	// Get the string table
	pbyteStringTable = (PBYTE)LockResource(hGlobal);

	// Get to the right string in the string table
	pdwTempPtr = (WORD*)pbyteStringTable;
	wStringLen = 0;
	for(i= 0; i< (i_nStringID % 16) + 1; ++i)
	{
		// Read the length of the string
		pdwTempPtr = pdwTempPtr + wStringLen;
		wStringLen = (WORD)(*pdwTempPtr);
		pdwTempPtr++;
	}

	// Read the string
	*o_wstrOutBuff = (WCHAR*)malloc(sizeof(WCHAR)*(wStringLen + 1));

	if(!*o_wstrOutBuff)
		return E_OUTOFMEMORY;

	memcpy((void*)*o_wstrOutBuff, (void*)pdwTempPtr, sizeof(WCHAR)*wStringLen);
	(*o_wstrOutBuff)[wStringLen] = 0x0000;

	return S_OK;
}


/*
Working -	
*/
DWORD _GetDefaultLangID()
{
	DWORD dwRetVal;

	dwRetVal = GetSystemDefaultLangID();
	if(!_IsLangSupported(dwRetVal))
		dwRetVal= LANG_ENGLISH_US;

	return dwRetVal;
}


/*
I/P -	'i_dwLangID'	:	
Working -	
*/
BOOL _IsLangSupported(DWORD i_dwLangID)
{
	switch(i_dwLangID)
	{
		case LANG_ENGLISH_US :
			return TRUE;

		default :
			return FALSE;
	}
}


/*
I/P -	'i_pbstrServerPath'	:	Is of the form http(s)://server[:port]/object.
O/P -	'o_pbstrServerName'	:	Is the server name obtained from the input path.
		'o_pbstrServerObject'	:	Is the object obtained from the input path.
		'o_pdwPortNum'	:	Is the port number obtained from the input path. If no port
							number is specified, it is set to 'INTERNET_DEFAULT_HTTP_PORT'
Return -	An hresult indicating the status of the operation.
Working -	This function parses the server path into 3 components, server name, server port
			and server object.
*/
HRESULT _ParseServerPath(const _bstr_t& i_pbstrServerPath, _bstr_t* o_pbstrServerName, _bstr_t* o_pbstrServerObject,
						LPDWORD o_pdwPortNum)
{
	HRESULT hr = S_OK;
	TCHAR* pPath = NULL;
	WCHAR* pwszServerPath = NULL;
	WCHAR pwTemp[2];
	UINT uServerPathLen = 0, uIndex = 0;
	_bstr_t bstrServerName = "", bstrServerObject = "", bstrServerPort = "";

	do
	{
		if(!i_pbstrServerPath || !o_pbstrServerName || !o_pbstrServerObject || !o_pdwPortNum)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_pbstrServerPath == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		*o_pbstrServerName = "";
		*o_pbstrServerObject = "";
		*o_pdwPortNum = INTERNET_DEFAULT_HTTP_PORT;

		pwszServerPath = i_pbstrServerPath.copy();
		uServerPathLen = i_pbstrServerPath.length();

		if(!_wcsnicmp(pwszServerPath, L"http", 4))
		{
			uIndex = 4;

			if(pwszServerPath[uIndex] == L's' || pwszServerPath[uIndex] == L'S')
			{
				*o_pdwPortNum = INTERNET_DEFAULT_HTTPS_PORT;
				uIndex++;
			}

			if(uServerPathLen <= uIndex + 3)
			{
				hr = E_NZINVALIDPATH;
				break;
			}

			if(pwszServerPath[uIndex] != L':' || pwszServerPath[uIndex + 1] != L'/' || pwszServerPath[uIndex + 2] != L'/')
			{
				hr = E_NZINVALIDPATH;
				break;
			}
			
			uIndex += 3;
		}

		// Search for ':' or '/'
		for(UINT i = uIndex; i < uServerPathLen; i++)
		{
			if(pwszServerPath[i] == L':')
				break;

			if(pwszServerPath[i] == L'/')
			{
				bstrServerObject = &pwszServerPath[i + 1];
				break;
			}
			
			pwTemp[0] = pwszServerPath[i];
			pwTemp[1] = NULL;

			bstrServerName += pwTemp;
		}

		if(pwszServerPath[i] == L':')
		{
			for(i++; i < uServerPathLen; i++)
			{
				if(pwszServerPath[i] == L'/')
				{
					bstrServerObject = &pwszServerPath[i + 1];
					break;
				}

				pwTemp[0] = pwszServerPath[i];
				pwTemp[1] = NULL;

				bstrServerPort += pwTemp;
			}
		}

	}while(0);

	if(hr == S_OK)
	{
		*o_pbstrServerName = bstrServerName.copy();
		*o_pbstrServerObject = bstrServerObject.copy();

		if(bstrServerPort != _bstr_t(""))
			*o_pdwPortNum = atoi(bstrServerPort);
	}

	if(pwszServerPath)
	{
		SysFreeString(pwszServerPath);
		pwszServerPath = NULL;
	}

	return hr;
}


/*
I/P -	'i_pDocument'	:	Is the path of document to be hashed. A URL can be specified
							over here.
		'i_pAlgID'	:	Is the algorithm used to hash the document.
O/P -	'o_pbHashVal'	:	Is the result of hashing the document.
		'o_pdwHashValSize'	:	Is the size of the hash value
Return -	An hresult indicating success of the operation.
Working -	This function creates a hash of the document. It uses the bsafelite library to
			generate the hash.
*/
HRESULT _HashDocument(const _bstr_t& i_bstrDocument, const _bstr_t& i_bstrAlgID, const _bstr_t& i_bstrUAgent, 
					  PBYTE* o_pbHashVal, LPDWORD o_pdwHashValSize)
{
	HRESULT hr = S_OK;
	void* pvContext = NULL;
	DWORD dwDataSize = 0, dwAlgID = 0;
	BYTE pbData[MAX_READ_SIZE];

	do
	{
		if(!i_bstrDocument || !i_bstrAlgID || !o_pbHashVal || !o_pdwHashValSize)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_bstrDocument == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		*o_pbHashVal = NULL;
		*o_pdwHashValSize = 0;

		if(!lstrcmpi(i_bstrAlgID, szOID_RSA_MD2))
		{
			dwAlgID = CALG_MD2;
			*o_pdwHashValSize = HASH_MD2_LENGTH;
		}
		else
			if(!lstrcmpi(i_bstrAlgID, szOID_RSA_MD4))
			{
				dwAlgID = CALG_MD4;
				*o_pdwHashValSize = HASH_MD4_LENGTH;
			}
			else
				if(!lstrcmpi(i_bstrAlgID, szOID_RSA_MD5))
				{
					dwAlgID = CALG_MD5;
					*o_pdwHashValSize = HASH_MD5_LENGTH;
				}
				else
					if(!lstrcmpi(i_bstrAlgID, szOID_OIWSEC_sha1))
					{
						dwAlgID = CALG_SHA1;
						*o_pdwHashValSize = HASH_SHA1_LENGTH;
					}
					else
					{
						hr = E_NZINVALIDALG;
						break;
					}

		*o_pbHashVal = (PBYTE)malloc(*o_pdwHashValSize);
		CHECK_MEM_BREAK(*o_pbHashVal)

		// Use the 'CDataObject' class to read the document
		CDataAccess DAccObject;
		hr = DAccObject.Open(i_bstrDocument, ACCESS_READ, i_bstrUAgent);
		CHECK_HRESULT_BREAK

		if(HashBegin(dwAlgID, &pvContext) != 0)
		{
			hr = E_NZHASHBEGINERR;
			break;
		}

		do
		{
			dwDataSize = MAX_READ_SIZE;
			hr = DAccObject.Read(pbData, &dwDataSize);
			CHECK_HRESULT_BREAK

			if(dwDataSize != 0)
			{
				if(HashData(dwAlgID, pvContext, pbData, dwDataSize) != 0)
				{
					hr = E_NZHASHDATAERR;
					break;
				}
			}

		}while(dwDataSize != 0);

		DAccObject.Close();

		CHECK_HRESULT_BREAK

		if(HashEnd(dwAlgID, pvContext, *o_pbHashVal, *o_pdwHashValSize) != 0)
		{
			hr = E_NZHASHENDERR;
			break;
		}

	}while(0);


	return hr;
}


/*
I/P -	
O/P -	
Return -	
Working -	
expected return values :	Success
							Integrity failed
							Cannot construct chain(issuer not found)
							Not trusted(root not found)
							Cert revoked
							Issuer revoked
							CRL not found
							Self signed
*/
HRESULT _DoCertValidation(HCERTSTORE i_hCertStore, BOOL i_bIsRootStore, PCCERT_CONTEXT i_pCertToValidate, DWORD i_dwRevFlags, BOOL i_bChainValidate, _bstr_t& i_bstrRevInfo)
{
	HRESULT hr = S_OK;
	DWORD dwFlags = 0, dwRevFlags = 0, dwLastError = 0;
	PCCERT_CONTEXT pIssuerCert = NULL, pPrevIssuerCert = NULL;
	BOOL bIsRoot = FALSE;

	dwRevFlags = i_dwRevFlags;

	do
	{
		if(!i_hCertStore || !i_pCertToValidate)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(dwRevFlags & REV_OCSP)
		{
			hr = E_NZREVTYPENOTSUPPORTED;
			break;
		}
	
		do
		{
			dwFlags = CERT_STORE_SIGNATURE_FLAG | CERT_STORE_TIME_VALIDITY_FLAG;

			dwLastError = 0;
			pIssuerCert = CertGetIssuerCertificateFromStore(i_hCertStore, i_pCertToValidate, pPrevIssuerCert, &dwFlags);
			pPrevIssuerCert = NULL;

			if(!pIssuerCert)
				dwLastError = GetLastError();
			else
			{
				// Signature does not match
				if((dwFlags & CERT_STORE_SIGNATURE_FLAG) == CERT_STORE_SIGNATURE_FLAG)
				{
					pPrevIssuerCert = pIssuerCert;
					pIssuerCert = NULL;
					continue;
				}

				// Could have found a valid issuer that has expired
				if((dwFlags & CERT_STORE_TIME_VALIDITY_FLAG) == CERT_STORE_TIME_VALIDITY_FLAG)
				{
					pPrevIssuerCert = pIssuerCert;
					pIssuerCert = NULL;
					continue;
				}

				if((dwFlags & CERT_STORE_NO_ISSUER_FLAG) == CERT_STORE_NO_ISSUER_FLAG)
				{
					hr = E_NZNOISSUER;
					break;
				}

				// A valid issuer has been found, see if the subject certificate is on its
				// revocation list
				if(dwRevFlags & (REV_CRL | REV_CRL_ALL))
				{
					hr = _DoCRLCheck(i_hCertStore, pIssuerCert, i_pCertToValidate, i_bstrRevInfo);
					CHECK_HRESULT_BREAK
				}
				
				// Everything okay, validate the issuer if necessary
				if(i_bChainValidate)
				{
					hr = _DoCertValidation(i_hCertStore, i_bIsRootStore, pIssuerCert, (dwRevFlags & REV_CRL_ALL ? dwRevFlags : REV_NONE), i_bChainValidate, i_bstrRevInfo);

					// If this issuer does not chain up see if the next one does
					if(hr != S_OK)
					{
						if(hr == E_NZNOTRUSTED)
						{
							pPrevIssuerCert = pIssuerCert;
							pIssuerCert = NULL;
							continue;
						}
						else
							if(hr == E_NZCERTREVOKED)
								hr = E_NZISSUEREVOKED;
							
						break;
					}
					else
						break;
				}
				else
					break;
			}


			if(dwLastError == E_INVALIDARG)
			{
				hr = E_NZINVALIDARG;
				break;
			}
			else
				if(dwLastError == CRYPT_E_SELF_SIGNED)
				{
					// If the cert is in the ROOT store then chain is validated else we
					// have a self-signed certificate in the intermediate(CA) store
					if(!i_bIsRootStore)
						hr = E_NZSELFSIGNED;

					break;
				}
				else
					if(dwLastError == CRYPT_E_NOT_FOUND)
					{
						// If the current cert store being processed is the CA store then open
						// the ROOT store and try to find the issuer. If current store is the ROOT
						// store then the chain validation has failed.
						if(i_bIsRootStore)
							hr = E_NZNOTRUSTED;
						else
						{
							HCERTSTORE hRootStore = CertOpenSystemStore(NULL, "ROOT");
							if(!hRootStore)
							{
								hr = E_NZOPENSTORERR;
								break;
							}

							hr = _DoCertValidation(hRootStore, TRUE, i_pCertToValidate, dwRevFlags, i_bChainValidate, i_bstrRevInfo);

							CertCloseStore(hRootStore, CERT_CLOSE_STORE_FORCE_FLAG);
						}

						break;
					}
					else
					{
						hr = E_NZCRYPTERR;
						break;
					}

		}while(1);


	}while(0);

	FREE_CERT_CTXT(pIssuerCert)

	if(hr != S_OK)
		_LogErrorMsg("_DoCertValidation().", "Error in signature verification.", NULL, hr);
	
	return hr;
}

/*
I/P -	
O/P -	
Return -	
Working -	
*/
HRESULT _DoCRLCheck(const HCERTSTORE i_hCertStore, PCCERT_CONTEXT i_pIssuerCertCtxt, PCCERT_CONTEXT i_pSubjectCertCtxt, _bstr_t& i_bstrRevInfo)
{
	HRESULT hr = S_OK;
	PCERT_INFO pSubjectCertInfo = NULL;
	PCERT_EXTENSION pCertCDPExt = NULL;
	PCCRL_CONTEXT pPrevCrlCtxt = NULL, pCurrCrlCtxt = NULL, pAddedCrlCtxt = NULL;
	PCRL_INFO rgpCrlInfo[1];
	PCRL_DIST_POINTS_INFO pCrlDPInfo = NULL;
	DWORD dwFlags = 0, dwLastError = 0, dwSize = 0, dwReadBuffer = 0, dwCRLSize = 0;
	CDataAccess DAReadObject, DAWriteObject;
	BYTE pbReadBuffer[MAX_READ_SIZE], *pbCRL = NULL;
	_bstr_t bstrCDPath = "", bstrTempFile = "";

	do
	{
		if(!i_hCertStore || !i_pIssuerCertCtxt || !i_pSubjectCertCtxt)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		pSubjectCertInfo = i_pSubjectCertCtxt->pCertInfo;

		if(!pSubjectCertInfo)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		do
		{
			dwFlags = CERT_STORE_SIGNATURE_FLAG | CERT_STORE_TIME_VALIDITY_FLAG;

			// Get the CRL for this particular issuer
			pCurrCrlCtxt = CertGetCRLFromStore(i_hCertStore, i_pIssuerCertCtxt, pPrevCrlCtxt, &dwFlags);
			pPrevCrlCtxt = NULL;

			if(!pCurrCrlCtxt)
				break;

			// Check whether the signature matches
			if((dwFlags & CERT_STORE_SIGNATURE_FLAG) == CERT_STORE_SIGNATURE_FLAG)
			{
				pPrevCrlCtxt = pCurrCrlCtxt;
				pCurrCrlCtxt = NULL;
				continue;
			}

			// Check whether the CRL is within the validity period
			if((dwFlags & CERT_STORE_TIME_VALIDITY_FLAG) == CERT_STORE_TIME_VALIDITY_FLAG)
			{
				pPrevCrlCtxt = pCurrCrlCtxt;
				pCurrCrlCtxt = NULL;
				continue;
			}

			// If both signature and time match then we have found a valid CRL
			break;

		}while(1);

		if(pCurrCrlCtxt)
		{
			rgpCrlInfo[0] = pCurrCrlCtxt->pCrlInfo;

			// We have a valid CRL, check the revocation status of the subject cert
			if(!CertVerifyCRLRevocation(MY_ENCODING_TYPE, pSubjectCertInfo, 1, rgpCrlInfo))
				hr = E_NZCERTREVOKED;

			break;
		}
		else
		{
			// Try to get the CDP from the subject certificate
			pCertCDPExt = CertFindExtension(szOID_CRL_DIST_POINTS, pSubjectCertInfo->cExtension, pSubjectCertInfo->rgExtension);

			if(!pCertCDPExt)
			{
				// If no CDP present in the certificate use the revocation info passed
				bstrCDPath = i_bstrRevInfo;
			}
			else
			{
				if(!CryptDecodeObject(MY_ENCODING_TYPE, szOID_CRL_DIST_POINTS, pCertCDPExt->Value.pbData, pCertCDPExt->Value.cbData, CRYPT_DECODE_NOCOPY_FLAG, NULL, &dwSize))
				{
					hr = E_NZCRYPTDECODERR;
					break;
				}

				pCrlDPInfo = (PCRL_DIST_POINTS_INFO)malloc(dwSize);
				CHECK_MEM_BREAK(pCrlDPInfo)

				if(!CryptDecodeObject(MY_ENCODING_TYPE, szOID_CRL_DIST_POINTS, pCertCDPExt->Value.pbData, pCertCDPExt->Value.cbData, CRYPT_DECODE_NOCOPY_FLAG, pCrlDPInfo, &dwSize))
				{
					hr = E_NZCRYPTDECODERR;
					break;
				}
				
				if(!(pCrlDPInfo->cDistPoint))
				{
					hr = E_NZCDPABSENT;
					break;
				}

				// Take the first CDP from the array
				if(pCrlDPInfo->rgDistPoint->DistPointName.dwDistPointNameChoice != CRL_DIST_POINT_FULL_NAME)
				{
					hr = E_NZCDPABSENT;
					break;
				}

				if(!(pCrlDPInfo->rgDistPoint->DistPointName.FullName.cAltEntry))
				{
					hr = E_NZCDPABSENT;
					break;
				}

				// Take the first name from the array, see whether the name is in the form of a URL
				if(pCrlDPInfo->rgDistPoint->DistPointName.FullName.rgAltEntry->dwAltNameChoice != CERT_ALT_NAME_URL)
				{
					hr = E_NZCDPABSENT;
					break;
				}
								
				bstrCDPath = pCrlDPInfo->rgDistPoint->DistPointName.FullName.rgAltEntry->pwszURL;
			}			

			if(!bstrCDPath)
			{
				hr = E_NZCDPABSENT;
				break;
			}

			if(bstrCDPath == _bstr_t(""))
			{
				hr = E_NZCDPABSENT;
				break;
			}

			// Create a temporary file in which the CRL will be written
			hr = _CreateTempFile(&bstrTempFile);
			CHECK_HRESULT_BREAK

			hr = DAWriteObject.Open(bstrTempFile, ACCESS_OVERWRITE);
			CHECK_HRESULT_BREAK

			// Fetch the CRL
			hr = DAReadObject.Open(bstrCDPath);
			CHECK_HRESULT_BREAK

			do
			{
				dwReadBuffer = sizeof(pbReadBuffer);
				hr = DAReadObject.Read(pbReadBuffer, &dwReadBuffer);
				CHECK_HRESULT_BREAK

				if(dwReadBuffer == 0)
					break;

				hr = DAWriteObject.Write(pbReadBuffer, dwReadBuffer);
				CHECK_HRESULT_BREAK

				dwCRLSize += dwReadBuffer;
		
			}while(dwReadBuffer != 0);

			CHECK_HRESULT_BREAK

			DAReadObject.Close();
			DAWriteObject.Close();

			// Now read the CRL in memory
			pbCRL = (PBYTE)malloc(dwCRLSize);
			CHECK_MEM_BREAK(pbCRL)

			hr = DAReadObject.Open(bstrTempFile);
			CHECK_HRESULT_BREAK

			dwCRLSize = 0;

			do
			{
				dwReadBuffer = sizeof(pbReadBuffer);
				hr = DAReadObject.Read(pbReadBuffer, &dwReadBuffer);
				CHECK_HRESULT_BREAK

				memcpy(pbCRL + dwCRLSize, pbReadBuffer, dwReadBuffer);
				dwCRLSize += dwReadBuffer;

			}while(dwReadBuffer != 0);

			DAReadObject.Close();

			CHECK_HRESULT_BREAK

			CertAddEncodedCRLToStore(i_hCertStore, MY_ENCODING_TYPE, pbCRL, dwCRLSize, CERT_STORE_ADD_NEWER, &pAddedCrlCtxt);
			if(!pAddedCrlCtxt)
			{
				hr = E_NZADDCRLERR;
				break;
			}
			
			rgpCrlInfo[0] = pAddedCrlCtxt->pCrlInfo;

			// We have a valid CRL, check the revocation status of the subject cert
			if(!CertVerifyCRLRevocation(MY_ENCODING_TYPE, pSubjectCertInfo, 1, rgpCrlInfo))
				hr = E_NZCERTREVOKED;				
		}

	}while(0);


	DAReadObject.Close();
	DAWriteObject.Close();

	// Delete the temporary CRL file
	if(bstrTempFile != _bstr_t(""))
		DeleteFile(bstrTempFile);

	FREE_CRL_CTXT(pCurrCrlCtxt)
	FREE_CRL_CTXT(pAddedCrlCtxt)

	FREE_MEMORY(pCrlDPInfo)
	FREE_MEMORY(pbCRL)

	if(hr == E_NZINETOPENERR || hr == E_NZINETCONNECTERR || hr == E_NZINETREQUESTERR || 
		hr == E_NZINETSENDERR || hr == E_NZINETQUERYERR || hr == E_NZINETBADSTAT || hr == E_NZINETREADERR)
	   hr = E_NZCDPFETCH;

	return hr;
}


/*
O/P -	'o_pbstrTempFilePath'	:	Is the name of the temporary file.
Return -	An hresult indicating the status of the operation.
Working -	This function tries to create a temporary file.
*/
HRESULT _CreateTempFile(_bstr_t* o_pbstrTempFilePath)
{
	HRESULT hr = S_OK;
	TCHAR szTempPath[MAX_FILE_PATH], szTempFile[MAX_FILE_PATH];
	HANDLE hFind = NULL;

	do
	{
		if(!o_pbstrTempFilePath)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		*o_pbstrTempFilePath = "";

		if(!GetTempPath(sizeof(szTempPath), szTempPath))
		{
			//_LogErrorMsg()
			hr = E_NZTEMPFILERR;
			break;
		}

		if(!GetTempFileName(szTempPath, "vsdnz", 0, szTempFile))
		{
			//_LogErrorMsg()
			hr = E_NZTEMPFILERR;
			break;
		}

	}while(0);

	if(hr == S_OK)
		*o_pbstrTempFilePath = szTempFile;

	return hr;
}



/*
I/P -	'i_pbSignature'	:	Is the attached signature to be verified.
		'i_dwSignature'	:	Is the length of the attached signature.
		'i_dwValidateFlags'	:	Are the flags which specify whether chain validation is to be 
								done and what kind of revocation checking is required. See the 
								'REV_' flags.
O/P -	'o_pbDecodedMsg'	:	Is the data that was signed.
		'o_pdwDecodedMsg'	:	Length of the data that was signed.
		'o_pbstrCertCN'	:	Common name of the certificate used for signing the data.
Return -	An hresult indicating the status of the operation.
Working -	This function uses CAPI to do signature verification. It also does chain validation
			and revocation checking depending on 'i_dwValidateFlags'. For this purpose it uses
			the '_GetSignerCertificate()' function.
*/
HRESULT _VerifyAttachedSignature(const PBYTE i_pbSignature, const DWORD i_dwSignature, const DWORD i_dwValidateFlags, const _bstr_t& i_bstrRevocationInfo, PBYTE *o_pbDecodedMsg, DWORD *o_pdwDecodedMsg, _bstr_t* o_pbstrCertCN)
{
	HRESULT hr = S_OK;
	CRYPT_VERIFY_MESSAGE_PARA VerifyParams;
	HCRYPTPROV hCryptProv = NULL;
	DWORD dwLastError = 0;
	VerifyInfo CertVerfInfo;
	PCCERT_CONTEXT pSignerCert = NULL;

	do
	{
		if(i_pbSignature == NULL || o_pbDecodedMsg == NULL || o_pdwDecodedMsg == NULL || 
		   o_pbstrCertCN == NULL)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_dwSignature == 0)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		*o_pbDecodedMsg = NULL;
		*o_pdwDecodedMsg = 0;

		if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			dwLastError = GetLastError();
			hr = E_NZCRYPTCONTEXT;
			break;
		}

		CertVerfInfo.hr = S_OK;
		CertVerfInfo.bstrRevInfo = i_bstrRevocationInfo;
		CertVerfInfo.dwValidationFlags = i_dwValidateFlags;

		memset(&VerifyParams, 0, sizeof(VerifyParams));
		VerifyParams.cbSize = sizeof(VerifyParams);
		VerifyParams.dwMsgAndCertEncodingType = MY_ENCODING_TYPE;
		VerifyParams.hCryptProv = hCryptProv;

		if(i_dwValidateFlags == 0)
			VerifyParams.pfnGetSignerCertificate = (PFN_CRYPT_GET_SIGNER_CERTIFICATE) NULL;
		else
			VerifyParams.pfnGetSignerCertificate = (PFN_CRYPT_GET_SIGNER_CERTIFICATE) _GetSignerCertificate;

		VerifyParams.pvGetArg = &CertVerfInfo;

		if(!CryptVerifyMessageSignature(&VerifyParams, 0, i_pbSignature, i_dwSignature, NULL, o_pdwDecodedMsg, NULL))
		{
			dwLastError = GetLastError();
			_LogErrorMsg("_VerifyAttachedSignature().", "Error verifying server signature.", NULL, dwLastError);
			hr = E_NZSIGVERIFYERR;
			break;
		}

		*o_pbDecodedMsg = (PBYTE) malloc(*o_pdwDecodedMsg);
		CHECK_MEM_BREAK(*o_pbDecodedMsg)

		if(!CryptVerifyMessageSignature(&VerifyParams, 0, i_pbSignature, i_dwSignature, *o_pbDecodedMsg, o_pdwDecodedMsg, &pSignerCert))
		{
			dwLastError = GetLastError();
			_LogErrorMsg("_VerifyAttachedSignature().", "Error verifying server signature.", NULL, dwLastError);
			hr = E_NZSIGVERIFYERR;
			break;
		}

	}while(0);

	if(hr == E_NZSIGVERIFYERR)		// either CAPI error has occured or our chain validation
	{								// function has returned some error
		if(CertVerfInfo.hr != S_OK)
			hr = CertVerfInfo.hr;
	}
	else
	{
		// Get the certificate Common Name if all succeeds
		_GetCertCN(pSignerCert->pCertInfo, o_pbstrCertCN);
	}

	FREE_CERT_CTXT(pSignerCert)

	if(hCryptProv)
	{
		CryptReleaseContext(hCryptProv, 0);
		hCryptProv = NULL;
	}

	return hr;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
PCCERT_CONTEXT WINAPI _GetSignerCertificate(void *pvVerifyArg, DWORD dwCertEncodingType,
										    PCERT_INFO pSignerId, HCERTSTORE hMsgCertStore)
{
	PCCERT_CONTEXT	pSignerCertCtxt = NULL, pCurrCertCtxt = NULL, pPrevCertCtxt = NULL;
	HCERTSTORE hCAStore = NULL;
	HRESULT hr = S_OK;
	LPVerifyInfo pCertVerfInfo;
	DWORD dwRevFlags = 0;
	BOOL bChainValidate = FALSE;

	do
	{
		if(pSignerId == NULL || hMsgCertStore == NULL || !pvVerifyArg)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		pCertVerfInfo = (LPVerifyInfo)pvVerifyArg;

		bChainValidate = (pCertVerfInfo->dwValidationFlags & CHAIN_VALIDATE) ? TRUE : FALSE;
		dwRevFlags = (pCertVerfInfo->dwValidationFlags & ~CHAIN_VALIDATE);

		pSignerCertCtxt = CertGetSubjectCertificateFromStore(hMsgCertStore, dwCertEncodingType, pSignerId);
		if(!pSignerCertCtxt)
		{
			hr = E_NZGETSUBJECTERR;
			break;
		}

		// Add the certificates in 'hMsgCertStore' except for the subject in the 'CA' store 
		// if not already present
		hCAStore = CertOpenSystemStore(NULL, "CA");
		if(!hCAStore)
		{
			hr = E_NZOPENCASTORERR;
			break;
		}

		pCurrCertCtxt = CertEnumCertificatesInStore(hMsgCertStore, pPrevCertCtxt);
		while(pCurrCertCtxt)
		{
			if(!CertCompareCertificate(MY_ENCODING_TYPE, pCurrCertCtxt->pCertInfo, pSignerCertCtxt->pCertInfo))
				CertAddCertificateContextToStore(hCAStore, pCurrCertCtxt, CERT_STORE_ADD_USE_EXISTING, NULL);

			pPrevCertCtxt = pCurrCertCtxt;
			pCurrCertCtxt = CertEnumCertificatesInStore(hMsgCertStore, pPrevCertCtxt);
		}

		hr = _DoCertValidation(hCAStore, FALSE, pSignerCertCtxt, dwRevFlags, bChainValidate, pCertVerfInfo->bstrRevInfo);

	}while(0);
	
	if(hCAStore)
	{
		CertCloseStore(hCAStore, CERT_CLOSE_STORE_FORCE_FLAG);
		hCAStore = NULL;
	}

	if(hr != S_OK)
	{
		pCertVerfInfo->hr = hr;
		return NULL;
	}
	else
	{
		pCertVerfInfo->hr = S_OK;
		return pSignerCertCtxt;
	}
}


/*
I/P -	'i_pVSPta'	:	Pointer to the PTA interface. This is used to get the Selected Digital ID
						interface which will give the SubjectDN of the currently selected cert.
O/P -	'o_pbstrCertName'	:	Common name of the certificate.
Return -	An hresult indicating the status of the operation.
Working -	Gets the Common Name (CN) of the currently selected certificate. Returns the entire
			Subject DN if the CN is not present.
*/
HRESULT _GetSelIDName(IVSPTA* i_pVSPta, _bstr_t* o_pbstrCertName)
{
	HRESULT hr = S_OK;
	IVSSelectedDigID *pSelDigID = NULL;
	VARIANT varSubjectDN;
	WCHAR* pwszSubjectDN = NULL, *pwCurrCN = NULL, *pwOldCN = NULL, pwTemp[2];
	DWORD dwSubjectDNLen = 0;

	VariantInit(&varSubjectDN);

	do
	{
		if(!i_pVSPta || !o_pbstrCertName)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		*o_pbstrCertName = "";

		hr = i_pVSPta->get_IVSSelectedDigID((LPDISPATCH*)&pSelDigID);
		CHECK_HRESULT_BREAK

		hr = pSelDigID->get_SubjectDN(&varSubjectDN);
		CHECK_HRESULT_BREAK

		pwszSubjectDN = varSubjectDN.bstrVal;
		dwSubjectDNLen = SysStringLen(pwszSubjectDN);

		// Get the 'leaf' CommonName(CN)
		pwCurrCN = wcsstr(pwszSubjectDN, L"CN=");
		if(!pwCurrCN)
		{
			*o_pbstrCertName = varSubjectDN.bstrVal; // If no CN return the entire subject DN
			break;
		}

		while(pwCurrCN)
		{
			pwOldCN = pwCurrCN;
			pwCurrCN = wcsstr(pwCurrCN + 3, L"CN=");
		}

		pwOldCN += 3;

		while(*pwOldCN != L';' && *pwOldCN != '\0')
		{
			pwTemp[0] = *pwOldCN;
			pwTemp[1] = NULL;

			*o_pbstrCertName += pwTemp;

			pwOldCN++;
		}

	}while(0);

	RELEASE_INTERFACE_PTR(pSelDigID)

	VariantClear(&varSubjectDN);

	return hr;
}


/*
I/P -	'i_pCertInfo'	:	Certificate information from which the Common Name is to be obtained.
O/P -	'o_pbstrCertName'	:	Common name of the certificate.
Return -	An hresult indicating the status of the operation.
Working -	Uses CAPI to get the Subject DN present in the 'i_pCertInfo'. Parses the Subject DN
			for the CN. If no CN is present returns the entire Subject DN.
*/
HRESULT _GetCertCN(PCERT_INFO i_pCertInfo, _bstr_t* o_pbstrCertName)
{
	HRESULT hr = S_OK;
	DWORD dwSize = 0;
	TCHAR *pszSubjectDN = NULL, *pCurrCN = NULL, *pOldCN = NULL;
	WCHAR pwTemp[2];

	do
	{
		if(!i_pCertInfo || !o_pbstrCertName)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		*o_pbstrCertName = "";

		dwSize = CertNameToStr(MY_ENCODING_TYPE, &i_pCertInfo->Subject, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG,
							   NULL, dwSize);
		if(dwSize < 1)
		{
			hr = E_NZCERTNAMETOSTRERR;
			break;
		}

		pszSubjectDN = (TCHAR*)malloc((dwSize + 1) * sizeof(TCHAR));
		CHECK_MEM_BREAK(pszSubjectDN)

		dwSize = CertNameToStr(MY_ENCODING_TYPE, &i_pCertInfo->Subject, CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG,
							   pszSubjectDN, dwSize);
		if(dwSize < 1)
		{
			hr = E_NZCERTNAMETOSTRERR;
			break;
		}

		// Get the 'leaf' CommonName(CN)
		pCurrCN = strstr(pszSubjectDN, "CN=");
		if(!pCurrCN)
		{
			*o_pbstrCertName = pszSubjectDN; // If no CN return the entire subject DN
			break;
		}

		while(pCurrCN)
		{
			pOldCN = pCurrCN;
			pCurrCN = strstr(pCurrCN + 3, "CN=");
		}

		pOldCN += 3;

		while(*pOldCN != ';' && *pOldCN != '\0')
		{
			pwTemp[0] = *pOldCN;
			pwTemp[1] = NULL;

			*o_pbstrCertName += pwTemp;

			pOldCN++;
		}

	}while(0);

	FREE_MEMORY(pszSubjectDN)

	//if(hr != S_OK)
		//_LogErrorMsg()

	return hr;
}


/*
I/P -	'i_pbGeneralizedTime'	:	Is the generalized time as returned by the notarization
									server. For more information regarding the format of the 
									time refer to the RFC for timestamping service. The general
									syntax is : YYYYMMDDhhmmss[.s...]Z
		'i_dwGeneralizedTime'	:	Length of the generalized time.
O/P -	'o_pGenTime'	:	The generalized time split up into the YYYY, MM, DD ...
Return -	An hresult indicating the status of the operation.
Working -	This function returns the year, month, date etc in the 'o_pGenTime' structure. It 
			assumes that the length is at least 14 bytes. Does not return fraction of second
			information.
*/
HRESULT _GetFormattedTime(const PBYTE i_pbGeneralizedTime, const DWORD i_dwGeneralizedTime, SYSTEMTIME *NzFormattedSysTime)
{
	HRESULT hr = S_OK;

	do
	{
		CHECK_NULL_PTR_BREAK(i_pbGeneralizedTime)
		CHECK_NULL_PTR_BREAK(NzFormattedSysTime)

		if(i_dwGeneralizedTime == 0 || i_dwGeneralizedTime < 14)
		{
			hr = E_INVALIDGENTIME;
			break;
		}

		memset(NzFormattedSysTime, 0, sizeof(SYSTEMTIME));

		NzFormattedSysTime->wYear = 0;
		NzFormattedSysTime->wYear += (i_pbGeneralizedTime[0] - 0x30) * 1000;
		NzFormattedSysTime->wYear += (i_pbGeneralizedTime[1] - 0x30) * 100;
		NzFormattedSysTime->wYear += (i_pbGeneralizedTime[2] - 0x30) * 10;
		NzFormattedSysTime->wYear += (i_pbGeneralizedTime[3] - 0x30);

		NzFormattedSysTime->wMonth = 0;
		NzFormattedSysTime->wMonth += (i_pbGeneralizedTime[4] - 0x30) * 10;
		NzFormattedSysTime->wMonth += (i_pbGeneralizedTime[5] - 0x30);

		NzFormattedSysTime->wDay = 0;
		NzFormattedSysTime->wDay += (i_pbGeneralizedTime[6] - 0x30) * 10;
		NzFormattedSysTime->wDay += (i_pbGeneralizedTime[7] - 0x30);

		NzFormattedSysTime->wHour = 0;
		NzFormattedSysTime->wHour += (i_pbGeneralizedTime[8] - 0x30) * 10;
		NzFormattedSysTime->wHour += (i_pbGeneralizedTime[9] - 0x30);

		NzFormattedSysTime->wMinute = 0;
		NzFormattedSysTime->wMinute += (i_pbGeneralizedTime[10] - 0x30) * 10;
		NzFormattedSysTime->wMinute += (i_pbGeneralizedTime[11] - 0x30);

		NzFormattedSysTime->wSecond = 0;
		NzFormattedSysTime->wSecond += (i_pbGeneralizedTime[12] - 0x30) * 10;
		NzFormattedSysTime->wSecond += (i_pbGeneralizedTime[13] - 0x30);	
	
	}while(0);

	return hr;
}


/*
I/P -	
O/P -	
Return -	
Working -	
*/
HRESULT _AddCertToStore(LPCTSTR i_pStore, const BYTE* i_pbCertificate, const DWORD i_dwCertLen)
{
	HRESULT hr = S_OK;
	HCERTSTORE hCertStore = NULL;
	DWORD dwLastError = 0;

	do
	{
		if(!i_pStore || !i_pbCertificate)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		if(i_dwCertLen == 0)
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		if(lstrcmpi(i_pStore, "CA") && lstrcmpi(i_pStore, "MY") && lstrcmpi(i_pStore, "ROOT"))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		hCertStore = CertOpenSystemStore(NULL, i_pStore);
		if(!hCertStore)
		{
			dwLastError = GetLastError();
			hr = E_NZOPENSTORERR;
			break;
		}

		if(!CertAddEncodedCertificateToStore(hCertStore, MY_ENCODING_TYPE, i_pbCertificate, 
											 i_dwCertLen, CERT_STORE_ADD_NEW, NULL))
		{
			dwLastError = GetLastError();
			if(dwLastError != CRYPT_E_EXISTS)
			{
				hr = E_NZADDCERTERR;
				break;
			}
		}

	}while(0);

	if(hCertStore)
	{
		CertCloseStore(hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
		hCertStore = NULL;
	}

	//if(hr != S_OK)
		//_LogErrorMsg()

	return hr;
}


VOID LaunchApp(const _bstr_t& i_bstrApp)
{
	if(!i_bstrApp)
		return;

	if(i_bstrApp == _bstr_t(""))
		return;

	ShellExecute(GetFocus(), NULL, i_bstrApp, NULL, NULL, SW_SHOWNORMAL);
}

VOID _Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	char _encode[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
					'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
				    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
				    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'} ;


	if ( pOutput == NULL )
	{
		*dwOutputSize = !(dwInputSize % 3) ? (dwInputSize/3)*4 : ((dwInputSize/3)*4) + 4 ;
		*dwOutputSize += (*dwOutputSize / 76)*2 ; // Includes '\n' '\r' after 76 chars in encoded output.
	}
	else
	{
		DWORD		remainingSize, seventySixCount ;
		PCHAR		inputPtr, outputPtr ;

		remainingSize = dwInputSize ;
		inputPtr = pInput ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;
		seventySixCount = 0 ;

		while((int)remainingSize > 0)
		{
			if (remainingSize == 1)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 16 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = '=' ;
				outputPtr[3] = '=' ;
			}
			else if(remainingSize == 2)
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = '=' ;
			}
			else
			{
				DWORD tmp ;
				tmp = 0x000000FF & inputPtr[0] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[1] ;
				tmp = tmp << 8 ;
				tmp |= 0x000000FF & inputPtr[2] ;

				outputPtr[0] = _encode[((tmp & 0x00FC0000) >> 18)] ;
				outputPtr[1] = _encode[((tmp & 0x0003F000) >> 12)] ;
				outputPtr[2] = _encode[((tmp & 0x00000FC0) >> 6)] ;
				outputPtr[3] = _encode[(tmp & 0x0000003F)] ;
			}
			*dwOutputSize += 4 ;
			seventySixCount += 4 ;
			remainingSize -= 3 ;
			inputPtr += 3 ;
			outputPtr += 4 ;

			// Check if '\n' \r' sequence is necessary.
			if ( seventySixCount >= 76 )
			{
				seventySixCount = 0 ;
				*dwOutputSize += 2 ;
#if 0
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
#else
				outputPtr[0] = '\r' ;
				outputPtr[1] = '\n' ;
#endif
				outputPtr += 2 ;
			}
		}
	}

}


VOID _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
{
	if ( pOutput == NULL )
	{
		PCHAR	filteredInputPtr ;
		int		i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		*dwOutputSize = filteredCounter ;
		*dwOutputSize = (*dwOutputSize/4)*3 ;

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
		free(filteredInputPtr) ;
	}
	else
	{
		DWORD		remainingSize ;
		PCHAR		inputPtr, outputPtr, filteredInputPtr ;
		int			i, filteredCounter = 0 ;

		filteredInputPtr = (PCHAR) malloc(dwInputSize) ;
		for ( i = 0 ; i < (int)dwInputSize ; i++ )
		{
			DWORD	tmp ;
			if (_decode(pInput[i], &tmp))
			{
				filteredInputPtr[filteredCounter] = pInput[i] ;
				filteredCounter++ ;
			}
		}

		// remainingSize = dwInputSize ;
		remainingSize = filteredCounter ;
		inputPtr = filteredInputPtr ;
		outputPtr = pOutput ;
		*dwOutputSize = 0 ;

		while((int)remainingSize > 0)
		{
			DWORD tmp, tmpout ;

			_decode(inputPtr[0], &tmpout) ;
			tmp = tmpout ;

			_decode(inputPtr[1], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			_decode(inputPtr[2], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;
				
			_decode(inputPtr[3], &tmpout) ;
			tmp = tmp << 6 ;
			tmp |= tmpout ;

			if ( inputPtr[2] == '=' && inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				*dwOutputSize += 1 ;
			}
			else if ( inputPtr[3] == '=' )
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				*dwOutputSize += 2 ;
			}
			else
			{
				outputPtr[0] = (char)((tmp & 0x00FF0000) >> 16) ;
				outputPtr[1] = (char)((tmp & 0x0000FF00) >> 8) ;
				outputPtr[2] = (char)((tmp & 0x000000FF)) ;
				*dwOutputSize += 3 ;
			}

			remainingSize -= 4 ;
			inputPtr += 4 ;
			outputPtr += 3 ;
		}

		EraseMemory ( (unsigned int) dwInputSize, (unsigned char*) filteredInputPtr );
		free(filteredInputPtr) ;
	}
}


BOOL _decode(short input, DWORD *output)
{
	if ( input >= 'A' && input <= 'Z' )
	{
		*output = input - 'A' ;
		return TRUE ;
	}
	else if ( input >= 'a' && input <= 'z' )
	{
		*output = input - 'a' + 26 ;
		return TRUE ;
	}
	else if ( input >= '1' && input <= '9' )
	{
		*output = input - '1' + 26 + 27 ;
		return TRUE ;
	}
	else if ( input == '0' )
	{
		*output = 26 + 26 ;
		return TRUE ;
	}
	else if ( input == '+' )
	{
		*output = 62 ;
		return TRUE ;
	}
	else if (input == '/' )
	{
		*output = 63 ;
		return TRUE ;
	}
	else if (input == '=' )
	{
		*output = 0 ;
		return TRUE ;
	}
	else
	{
		*output = 0 ;
		return FALSE ;
	}
}

/*
	I/P - None
*/
PUICTXT _CreateUIContext()
{
	PUICTXT pNewUICtxt;

	pNewUICtxt = (PUICTXT)new(UICTXT);
	pNewUICtxt->pbtnElems = NULL;
	pNewUICtxt->pbtnFns = NULL;
	pNewUICtxt->pfontInfoCustomFonts = NULL;
	pNewUICtxt->pfontInfoDefaultFonts = NULL;
	pNewUICtxt->pvUIElements = NULL;
	pNewUICtxt->pvWizardElems = NULL;
	pNewUICtxt->pvReserved = NULL;
	return pNewUICtxt;
}

/*
I/P 
o_pUICtxtDest - The destination context
i_pUICtxtSrc - The source context
*/
HRESULT _CopyUIContext(PUICTXT o_pUICtxtDest, PUICTXT i_pUICtxtSrc)
{
	HRESULT retVal = S_OK;

	o_pUICtxtDest->nWhichWizardAndUI = i_pUICtxtSrc->nWhichWizardAndUI;
	
	if(i_pUICtxtSrc->pbtnElems)
	{
		o_pUICtxtDest->pbtnElems = new(BTNELEMS);
		if(!(o_pUICtxtDest->pbtnElems))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pbtnElems) = *(i_pUICtxtSrc->pbtnElems);
	}

	if(i_pUICtxtSrc->pbtnFns && retVal == S_OK)
	{
		o_pUICtxtDest->pbtnFns = new(BTNFNS);
		if(!(o_pUICtxtDest->pbtnFns))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pbtnFns) = *(i_pUICtxtSrc->pbtnFns);
	}

	if(i_pUICtxtSrc->pfontInfoCustomFonts && retVal == S_OK)
	{
		o_pUICtxtDest->pfontInfoCustomFonts = new(FONTSINFO);
		if(!(o_pUICtxtDest->pfontInfoCustomFonts))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pfontInfoCustomFonts) = *(i_pUICtxtSrc->pfontInfoCustomFonts);
	}

	if(i_pUICtxtSrc->pfontInfoDefaultFonts && retVal == S_OK)	
	{
		o_pUICtxtDest->pfontInfoDefaultFonts  = new(FONTSINFO);
		if(!(o_pUICtxtDest->pfontInfoDefaultFonts))
			retVal = E_FAIL;
		else
			*(o_pUICtxtDest->pfontInfoDefaultFonts) = *(i_pUICtxtSrc->pfontInfoDefaultFonts);
	}

	o_pUICtxtDest->tbstrDefLogoUrl = i_pUICtxtSrc->tbstrDefLogoUrl;
	o_pUICtxtDest->tbstrCustLogoUrl = i_pUICtxtSrc->tbstrCustLogoUrl;

	if(i_pUICtxtSrc->pvUIElements && retVal == S_OK)		
	{
		switch(i_pUICtxtSrc->nWhichWizardAndUI & (~WIZARD_BITS))
		{
		case ERROR_BASE:
			o_pUICtxtDest->pvUIElements = (void*)new(ALL_ERROR_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_ERROR_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_ERROR_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case SELFILE_BASE:
			o_pUICtxtDest->pvUIElements = (void*)new(ALL_SELFILE_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_SELFILE_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_SELFILE_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

	
		case PROGRESS_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_PROGRESS_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_PROGRESS_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_PROGRESS_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		case VERIFYRCPT_BASE :
			o_pUICtxtDest->pvUIElements  = (void*)new(ALL_VERIFYRCPT_UIELEMENTS);
			if(!(o_pUICtxtDest->pvUIElements))
				retVal = E_FAIL;
			else
				(*(PALL_VERIFYRCPT_UIELEMENTS)(o_pUICtxtDest->pvUIElements)) = (*(PALL_VERIFYRCPT_UIELEMENTS)(i_pUICtxtSrc->pvUIElements));
			break;

		default :
			retVal = E_INVALIDUIFLAG;
			break;
		}
	}
	
	if(i_pUICtxtSrc->pvWizardElems && retVal == S_OK)
	{
		o_pUICtxtDest->pvWizardElems = (void*)new (ALLWIZARDELEMENTS);
		if(!(o_pUICtxtDest->pvWizardElems))
				retVal = E_FAIL;
		else	
			(*(PALLWIZARDELEMENTS)(o_pUICtxtDest->pvWizardElems)) = (*(PALLWIZARDELEMENTS)(i_pUICtxtSrc->pvWizardElems));		
	}
	
	o_pUICtxtDest->nDefLangId = i_pUICtxtSrc->nDefLangId;
	return retVal;
}


/*
I/P i_pUICtxt - The context that should be freed.
*/
void _FreeUIContext(PUICTXT i_pUICtxt)
{
	if(i_pUICtxt)
	{
		_FreeUIElements(i_pUICtxt);

		if(i_pUICtxt->pfontInfoCustomFonts)
		{
			delete(i_pUICtxt->pfontInfoCustomFonts);
			i_pUICtxt->pfontInfoCustomFonts = NULL;
		}

		if(i_pUICtxt->pfontInfoDefaultFonts)
		{
			delete(i_pUICtxt->pfontInfoDefaultFonts);
			i_pUICtxt->pfontInfoDefaultFonts = NULL;
		}

#if 1
		if(i_pUICtxt->pbtnFns)
		{
			delete i_pUICtxt->pbtnFns;
			i_pUICtxt->pbtnFns = NULL;
		}

		if(i_pUICtxt->pbtnElems)
		{
			delete i_pUICtxt->pbtnElems;
			i_pUICtxt->pbtnElems = NULL;
		}
#endif

	}

	return;
}

/*
I/P i_pUICtxt - The context that should be freed.
*/
void _FreeUIElements(PUICTXT i_pUICtxt)
{
	if(i_pUICtxt)
	{
		if(i_pUICtxt->pvUIElements)
		{
			switch(i_pUICtxt->nWhichWizardAndUI & (~WIZARD_BITS))
			{
			case SELFILE_BASE :
				delete((PALL_SELFILE_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

		
			case PROGRESS_BASE :
				delete((PALL_PROGRESS_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case VERIFYRCPT_BASE :
				delete((PALL_VERIFYRCPT_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			case ERROR_BASE :
				delete((PALL_ERROR_UIELEMENTS)i_pUICtxt->pvUIElements);
				break;

			default :
				break;
			}
			i_pUICtxt->pvUIElements = NULL;
		}

		if(i_pUICtxt->pvWizardElems)
		{
			delete((PALLWIZARDELEMENTS)i_pUICtxt->pvWizardElems);
			i_pUICtxt->pvWizardElems = NULL;
		}
	}

	return;
}


/*
	I/P :
	tbstrBmpUrl - The Url of the bitmap to be retrieved
	o_phBitmap -  The handle of the bitmap
*/
HRESULT _GetBitmap(_bstr_t& tbstrBmpUrl, HBITMAP* o_phBitmap)
{
	HRESULT retVal = S_OK;
	
	_bstr_t temp = "VeriSign Web Access Control";

	if(InternetAttemptConnect(0) == ERROR_SUCCESS)
	{
		HINTERNET hInternet;

		//Initialize
		if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
			NULL,NULL,INTERNET_FLAG_FROM_CACHE )) == NULL) 
		{
			DWORD err;
			err = GetLastError();
			retVal = E_INTERNETOPENERR;
			
		}
		else
		{
			//Try to connect to szURL
			HINTERNET hInternetURL;
			temp = tbstrBmpUrl;
			if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
			{
				DWORD err;
				err = GetLastError();
				if(err == ERROR_FILE_NOT_FOUND)
				{
					retVal = S_OK;

					//File is not in the cache, try to get it from the network
					InternetCloseHandle(hInternet);
					if((hInternet =  InternetOpen((TCHAR*)temp, INTERNET_OPEN_TYPE_PRECONFIG,
					NULL,NULL,0)) == NULL) 
					{
						DWORD err;
						err = GetLastError();
						retVal = E_INTERNETOPENERR;
					}
					else
					{
						if((hInternetURL = InternetOpenUrl(hInternet,(TCHAR*)temp,NULL, -1L,0,0)) == NULL)
						{
							retVal = E_INTERNETOPENURLERR;		
						}
					}
				}
				else
				{
					retVal = E_INTERNETOPENURLERR;
				}
			}

			if(retVal == S_OK)
			{
				//Write the data to a file
				DWORD dwbytesReadSize;
				BYTE buffer[128];
				DWORD dwSize;
				TCHAR* tstrTempPath;
				TCHAR* tstrLogoFile;

				//Get the temporary path name
				if((dwSize = GetTempPath(0,NULL)) == 0)
				{
					retVal = E_COULDNOTGETTEMPPATH;
				}
				else
				{
					tstrTempPath = (TCHAR*)malloc(dwSize + sizeof(TCHAR));
					if(!tstrTempPath)
					{
						retVal = -1;
					}
					else
					{
						if((dwSize = GetTempPath(dwSize,tstrTempPath)) == 0)
						{
							retVal = E_COULDNOTGETTEMPPATH;
						}
						else
						{
							tstrLogoFile = (TCHAR*)malloc(MAX_PATH);

							temp = _T("vspta");
							//Get the temporary file name
							if(GetTempFileName(tstrTempPath,(TCHAR*)temp,0,tstrLogoFile) == 0)
							{
								retVal = E_COULDNOTGETTEMPFILENAME;
							}
							else
							{
								//Create a file to store the data in
								HANDLE hFileHandle;
								hFileHandle = CreateFile(tstrLogoFile,GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL, NULL);
								if(!hFileHandle)
									retVal = E_COULDNOTCREATETEMPFILE;

								//Store the data in this file
								do
								{
									if(!InternetReadFile(hInternetURL,(LPVOID)buffer,128,&dwbytesReadSize))
									{
										retVal = E_INTERNETREADERR;
										break;
									}
									else if(dwbytesReadSize)
									{
										if(!WriteFile(hFileHandle,buffer,dwbytesReadSize,&dwbytesReadSize,NULL))
										{
											retVal = E_FILEWRITEERR;
											break;
										}
									}

								}while(dwbytesReadSize != 0);

								CloseHandle(hFileHandle);

								//Now create a bitmap handle
								*o_phBitmap = (HBITMAP)LoadImage(NULL,tstrLogoFile,IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
								if(! *o_phBitmap)
									retVal = GetLastError();

								//Delete the file
								DeleteFile(tstrLogoFile);
							}

							free(tstrLogoFile);
						}

						free(tstrTempPath);
					}
				}
				
				InternetCloseHandle(hInternetURL);
			}

			InternetCloseHandle(hInternet);
		}

	}
	else
		retVal = E_INTERNETATTEMPTERR;
	return retVal;
}

/*
	I/P 
	i_hBitmap - The handle of the bitmap to be freed.
*/
HRESULT _FreeBitmap(HBITMAP i_hBitmap)
{
	if(i_hBitmap)
		DeleteObject(i_hBitmap);
	return S_OK;
}


int _GetCharset(WORD wLangID)
{
	/*Get the code page for this language*/
	TCHAR tcharTemp[7];
	if(!GetLocaleInfo(wLangID,LOCALE_IDEFAULTANSICODEPAGE,tcharTemp, 7))
	{
		return -1;
	}

	/*Get the charset that supports this code page*/
	CHARSETINFO CharSetInfo;
	if(!TranslateCharsetInfo((DWORD*)_ttoi(tcharTemp),&CharSetInfo, TCI_SRCCODEPAGE))
		return -1;

	return CharSetInfo.ciCharset;

}

/*
Determines if the data is text only
*/
BOOL _IsDataTextOnly(LCID locale, BYTE* pbData, DWORD cbData)
{
	BOOL bIsTextOnly = TRUE;
	WORD* pwCharTypes;
	pwCharTypes = new WORD[cbData+1];
	if(GetStringTypeEx(locale,CT_CTYPE1,(LPCTSTR)pbData,cbData,pwCharTypes))
	{
		for(unsigned int i=0;i<cbData;++i)
		{
			if(!(pwCharTypes[i] & (C1_ALPHA | C1_UPPER | C1_LOWER | C1_DIGIT | 
									C1_SPACE | C1_PUNCT | C1_BLANK | C1_XDIGIT | 
									C1_ALPHA)))
			{
				bIsTextOnly = FALSE;
				break;
			}
		}
		
	}
	delete[] pwCharTypes;
	return bIsTextOnly;
}

/*
	Formats the date
*/
HRESULT _FormatDate(LCID locale, SYSTEMTIME st, _bstr_t* o_ptbstrFormattedDate)
{
	HRESULT retVal = S_OK;

	TCHAR* ptszFormattedDate;
	int nFormattedDateSize;
	if((nFormattedDateSize = GetDateFormat(locale,0,&st,"d MMMM yyyy",NULL,0)) == 0)
		retVal = E_GETDATEFORMATSIZEFAILED;
	else
	{
		ptszFormattedDate = (TCHAR*)new TCHAR[nFormattedDateSize];
		if(!ptszFormattedDate)
			retVal =  E_FAIL;
		else
		{
			if((nFormattedDateSize = GetDateFormat(locale,0,&st,"d MMMM yyyy",ptszFormattedDate,nFormattedDateSize)) == 0)
				retVal = E_GETDATEFORMATFAILED;
			else
			{
				*o_ptbstrFormattedDate = ptszFormattedDate;
			}
			delete[] ptszFormattedDate;
		}
	}

	return retVal;
}


HRESULT _FormatTime(LCID locale, SYSTEMTIME st, _bstr_t* o_ptbstrFormattedTime)
{
	HRESULT retVal = S_OK;

	TCHAR* ptszFormattedTime;
	int nFormattedTimeSize;
	if((nFormattedTimeSize = GetTimeFormat(locale,LOCALE_NOUSEROVERRIDE,&st,NULL,NULL,0)) == 0)
		retVal = E_GETTIMEFORMATSIZEFAILED;
	else
	{
		ptszFormattedTime = (TCHAR*)new TCHAR[nFormattedTimeSize];
		if(!ptszFormattedTime)
			retVal = E_FAIL;
		else
		{
			if((nFormattedTimeSize = GetTimeFormat(locale,LOCALE_NOUSEROVERRIDE,&st,NULL,ptszFormattedTime,nFormattedTimeSize)) == 0)
				retVal = E_GETTIMEFORMATFAILED;
			else
			{
				*o_ptbstrFormattedTime = ptszFormattedTime;
				*o_ptbstrFormattedTime += " (GMT)";
			}

			delete[] ptszFormattedTime;
		}
	}

	return retVal;
}


HRESULT _SelectOpenOrSaveFile(int selectType, HWND hParent, UINT idOFTitle, char* pcszFilter, int dwFilterLength, _bstr_t i_tbstrInitialFileName, _bstr_t* o_ptbstrSelFile)
{
	HRESULT hr = S_OK;
	OPENFILENAME theOpenFileName;
	TCHAR szFileName[MAX_FILE_SIZE];
	_bstr_t tbstrFilter = "", tbstrTitle = "";
	WCHAR* pwcharFilter = NULL, *pwcharTitle = NULL;
	TCHAR* tcharFilter = NULL;

	*o_ptbstrSelFile = "";

	do
	{
		if(idOFTitle == 0)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		memset(&theOpenFileName,0,sizeof(OPENFILENAME));
		lstrcpy(szFileName, (char *)i_tbstrInitialFileName);
		theOpenFileName.lStructSize = sizeof(OPENFILENAME);
		theOpenFileName.hwndOwner = hParent;
		theOpenFileName.lpstrFile = szFileName;
		theOpenFileName.nMaxFile = MAX_FILE_SIZE;

		hr = _LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_FILEFILTER, &pwcharFilter);
		CHECK_HRESULT_BREAK

		tbstrFilter = pwcharFilter;
		tcharFilter =  (TCHAR*) malloc(lstrlen((CHAR*)tbstrFilter) + 6);
		CHECK_MEM_BREAK(tcharFilter)

		lstrcpy(tcharFilter,(CHAR*)tbstrFilter);
		memcpy(tcharFilter+lstrlen((CHAR*)tbstrFilter),(BYTE*)"\0*.*\0\0",6);


		if ((pcszFilter != NULL) && (dwFilterLength != 0))
		{
			char *tcharFullFilter;
			int sizeOfFullFilter = (dwFilterLength + 1 + lstrlen((char *)tbstrFilter) + 6) * sizeof(char);
			tcharFullFilter = (char *) malloc (sizeOfFullFilter);
			memset((void *)tcharFullFilter, 0, sizeOfFullFilter);
			
			memcpy(tcharFullFilter, pcszFilter, dwFilterLength);
			memcpy(tcharFullFilter + dwFilterLength + 1, tcharFilter, lstrlen((CHAR*)tbstrFilter) + 6);

			theOpenFileName.lpstrFilter = (char *) tcharFullFilter;
		}
		else
		{
			theOpenFileName.lpstrFilter = (CHAR*)tcharFilter;
		}
		theOpenFileName.nFilterIndex = 1;
		theOpenFileName.lpstrFileTitle = NULL;
		theOpenFileName.nMaxFileTitle = 0;

		hr = _LoadStringW(_Module.m_hInst, _GetDefaultLangID() ,idOFTitle, &pwcharTitle);
		CHECK_HRESULT_BREAK

		tbstrTitle = pwcharTitle;
		theOpenFileName.lpstrTitle = (CHAR*)tbstrTitle;

		theOpenFileName.lpstrInitialDir = NULL;
		if (selectType == SELECT_OPEN)
		{
			theOpenFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if(!GetOpenFileName(&theOpenFileName))
			{
				DWORD dwErr;
				dwErr = CommDlgExtendedError();
				_LogErrorMsg("_SelectOpenOrSaveFile().", "GetOpenFileName() api failed.", NULL, dwErr);
				hr = E_NZGETOPENFILERR;
				break;
			}

		}
		else if (selectType == SELECT_SAVE)
		{
			theOpenFileName.Flags = OFN_OVERWRITEPROMPT;

			if(!GetSaveFileName(&theOpenFileName))
			{
				DWORD dwErr;
				dwErr = CommDlgExtendedError();
				_LogErrorMsg("_SelectOpenOrSaveFile().", "GetSaveFileName() api failed.", NULL, dwErr);
				hr = E_NZGETSAVEFILERR;
				break;
			}

		}
		*o_ptbstrSelFile = theOpenFileName.lpstrFile;

	}while(0);

	FREE_MEMORY(pwcharTitle)
	FREE_MEMORY(pwcharFilter)
	FREE_MEMORY(tcharFilter)

	return hr;
}


VOID reverseit(PBYTE pbData, DWORD dwData)
{
	if(!pbData || !dwData)
		return;

	BYTE pbTemp;
	for(UINT i = 0; i < dwData/2; i++)
	{
		pbTemp = pbData[i];
		pbData[i] = pbData[dwData - i - 1];
		pbData[dwData - i - 1] = pbTemp;
	}
}


BOOL IsBase64Encoded(LPBYTE pbData, DWORD dwData)
{
	DWORD dwDecode = 0;

	if(pbData == NULL || dwData == 0)
		return FALSE;

	for(UINT i = 0; i < dwData; i++)
	{
		if(_decode(pbData[i], &dwDecode))
			continue;
		else
			if(pbData[i] == '\r' || pbData[i] == '\n')
				continue;
			else
				return FALSE;
	}

	return TRUE;
}



/*
I/P -	
O/P -	
Return -	An hresult indicating the status of the operation.
Working -	This function construct a receipt file name from the name of the file to notarize and
			also determines if the receipt file can be created. If the receipt file is already
			present the function adds a prefix to the file (eg 'Version (1) of ..', 'Version (2) of ..' and so on) 
			and check if such a file can be created.
*/
HRESULT GetReceiptFileName(const _bstr_t& i_bstrFileToNotarize, _bstr_t* o_pbstrReceiptFileName)
{
	HRESULT hr = S_OK;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA wfd;
	_bstr_t bstrReceiptFile = "";
	WCHAR *pwFileToNotarize = NULL;
//	WCHAR *pwszReceiptIndex[2];
	DWORD dwFileToNotarize = 0;
	CDataAccess DAccObject;

	do
	{
		if(!i_bstrFileToNotarize || !o_pbstrReceiptFileName)
		{
			hr = E_NZEMPTYARGS;
			break;
		}		

		*o_pbstrReceiptFileName = "";

		if(i_bstrFileToNotarize == _bstr_t(""))
		{
			hr = E_NZINVALIDARGS;
			break;
		}

		hFind = FindFirstFile(i_bstrFileToNotarize, &wfd);
		if(hFind == INVALID_HANDLE_VALUE)
		{
			hr = E_NZDOCFINDERR;
			break;
		}
		else
		{
			FindClose(hFind);
			hFind = INVALID_HANDLE_VALUE;
		}

		bstrReceiptFile = i_bstrFileToNotarize;
		bstrReceiptFile += ".rcpt";

//		pwszReceiptIndex[0] = L'2';
//		pwszReceiptIndex[1] = NULL;

		int dwRcptIndex = 2;

		do
		{
			hFind = FindFirstFile(bstrReceiptFile, &wfd);
			if(hFind == INVALID_HANDLE_VALUE)
			{
				// Found a receipt file which does not exist, see if we can create the file on end
				// users machine
				hr = DAccObject.Open(bstrReceiptFile, ACCESS_WRITE);
				if(hr == E_NZDOCNOACCESS)
					hr = E_NZRCPTCREATERR;

				CHECK_HRESULT_BREAK

				DAccObject.Close();

				// Delete this file as it will be created again later.
				DeleteFile(bstrReceiptFile);

				break;
			}
			else
			{
				// Receipt file exists, try again
				FindClose(hFind);
				hFind = INVALID_HANDLE_VALUE;

				pwFileToNotarize = i_bstrFileToNotarize.copy();
				dwFileToNotarize = i_bstrFileToNotarize.length();

				for(INT i = dwFileToNotarize - 1; i >= 0; i--)
				{
					if(pwFileToNotarize[i] == L'\\')
					{
						pwFileToNotarize[i] = NULL;
						break;
					}
				}
				

				bstrReceiptFile = pwFileToNotarize;
				bstrReceiptFile += "\\";
				bstrReceiptFile += "Version (";
//				bstrReceiptFile += pwszReceiptIndex;
				char buffer[10];
				_itoa(dwRcptIndex, buffer, 10);
				bstrReceiptFile += buffer;
				bstrReceiptFile += ") of ";
				bstrReceiptFile += &pwFileToNotarize[i + 1];
				bstrReceiptFile += ".rcpt";
//				(pwszReceiptIndex[0])++;
				dwRcptIndex++;
			}

		}while(1);

		if(hr == S_OK)
			*o_pbstrReceiptFileName = bstrReceiptFile;
	
	}while(0);

	if(hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		hFind = INVALID_HANDLE_VALUE;
	}

	SYS_FREE_MEMORY(pwFileToNotarize)

	return hr;
}

HRESULT _GetDocumentExtension(_bstr_t i_tbstrDocument, _bstr_t* o_tbstrExtension)
{

	HRESULT hr = S_OK;

	char *pcszDocument = (char *) i_tbstrDocument;

	int startIndex = -1;

	if (!_tcsncicmp(pcszDocument, "http://", lstrlen("http://")))
	{
		startIndex = lstrlen("http://");
	}
	else if (!_tcsncicmp(pcszDocument, "https://", lstrlen("https://")))
	{
		startIndex = lstrlen("https://");
	}
	else
	{
		int lastDot = -1;
		int lastSlash = 0;
		// search for the last occurence of "/" or "\"in pcszDocument.
		for (int i = 0; i < lstrlen(pcszDocument); i++)
		{
			if ((pcszDocument[i] == '/') || (pcszDocument[i] == '\\'))
			{
				lastSlash = i;
			}
		}
		// search for the last dot after the last slash..
		for (int j = lastSlash; j < lstrlen(pcszDocument); j++)
		{
			if (pcszDocument[j] == '.')
			{
				lastDot = j;
			}
		}
		// if the pcszDocument char-array ends in a "." treat as if no dot.
		if (lastDot == (lstrlen(pcszDocument) - 1))
		{
			lastDot = -1;
		}
		if (lastDot >= 0)
		{
			*o_tbstrExtension = _bstr_t("*") + _bstr_t(&pcszDocument[lastDot]);
		}
		else
		{
			*o_tbstrExtension = _bstr_t("");
		}
	}
	if (startIndex > 0)
	{
		// search for the last slash.
		int lastSlash = startIndex - 1;
		int lastDot = -1;

		for (int i = startIndex; i < lstrlen(pcszDocument); i++)
		{
			if ((pcszDocument[i] == '/') || (pcszDocument[i] == '\\'))
			{
				lastSlash = i;
			}
		}
		// if there are no more slashes or if the http/s url ends with a slash.
		if ((lastSlash == (startIndex - 1)) || (lastSlash == lstrlen(pcszDocument)))
		{
			*o_tbstrExtension = _bstr_t("");
		}
		else
		{
			// search for the lastDot after the slash.
			for (int j = lastSlash; j < lstrlen(pcszDocument); j++)
			{
				if (pcszDocument[j] == '.')
				{
					lastDot = j;
				}
			}
			// if "." is the last character then treat as if no "."
			if (lastDot == (lstrlen(pcszDocument) - 1))
			{
				lastDot = -1;
			}
			
			if (lastDot >= 0)
			{
				*o_tbstrExtension = _bstr_t("*") + _bstr_t(&pcszDocument[lastDot]);
			}
			else
			{
				*o_tbstrExtension = _bstr_t("");
			}
		}
	}

	return hr;
}

bool _IsSourceAndDestinationSame(_bstr_t m_tbstrDocument, _bstr_t tbstrDocumentDestination)
{

	char *pcszDoc = (char *) m_tbstrDocument;
	char *pcszDocDest = (char *) tbstrDocumentDestination;
 
	int startIndexDoc = 0;
	if (!_tcsncicmp(pcszDoc, "file://", lstrlen("file://")))
	{
		startIndexDoc += lstrlen("file://");
	}

	int startIndexDocDest = 0;
	if (!_tcsncicmp(pcszDocDest, "file://", lstrlen("file://")))
	{
		startIndexDocDest += lstrlen("file://");
	}

	if (!lstrcmpi(&pcszDoc[startIndexDoc], &pcszDocDest[startIndexDocDest]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

HRESULT _GetDispProperty(IDispatch* pDisp, UINT uIDName, VARTYPE vt, LPVARIANT pVar)
{
	HRESULT hr = S_OK;
	
	do
	{
		if(!pDisp|| !pVar)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		hr = _GetProperty(pDisp, uIDName, vt, pVar);
		CHECK_HRESULT_BREAK

		if(pVar->vt != vt)
		{
			::VariantClear(pVar);
			hr = E_FAIL;
			break;
		}

	}while(0);

	return hr;
}


HRESULT _GetProperty(LPDISPATCH pDisp, UINT uIDName, VARTYPE vt, LPVARIANT pVar)
{
	HRESULT hr = S_OK;
	DISPID id = 0;
    EXCEPINFO excep;
    UINT uArgErr;
    DISPPARAMS dispparams = {0,0,0,0};

	do
	{
		if(!pDisp || !pVar)
		{
			hr = E_NZEMPTYARGS;
			break;
		}

		// Map the property name to a dispid.
		hr = _GetDISPID(pDisp, uIDName, &id);
		CHECK_HRESULT_BREAK

		VariantInit(pVar);
		pVar->vt = vt;

		// Get the property
		hr = pDisp->Invoke(id, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_PROPERTYGET, &dispparams, pVar, 
						   &excep, &uArgErr);

	}while(0);

	return hr;
}



HRESULT _GetDISPID(IDispatch* pDisp, UINT uIDName, DISPID* pDispId)
{
	OLECHAR aOleCh[MAX_STRING_LEN];
    OLECHAR * pOleCh = aOleCh;  
    CHAR ach[MAX_STRING_LEN];
    INT cch;
	HRESULT hr = S_OK;

	do
	{
		cch = LoadString(_Module.m_hInst, uIDName, ach, MAX_STRING_LEN);
		if(!cch)
		{
			hr = E_FAIL;
			break;
		}

		// convert the ANSI string to wide
		cch = MultiByteToWideChar(CP_ACP, 0, ach, -1, aOleCh, MAX_STRING_LEN);
	    if(!cch)
        {
			hr = E_FAIL;
			break;
		}

		// map the string name to a dispid
		hr = pDisp->GetIDsOfNames(IID_NULL, &pOleCh, 1, LOCALE_SYSTEM_DEFAULT, pDispId);

	}while(0);

	return hr;
}


BOOL	myStrStr(char *str, char *pattern)
{
	int i = 0;

	if ((str == NULL) || (pattern == NULL))
	{
		return false;
	}

	int strLength = lstrlen(str);
	int patternLength = lstrlen(pattern);

	for (i = 0; i < (strLength - patternLength + 1); i++)
	{
		int j = 0;
		for (j = i; j < (i + patternLength); j++)
		{	
			if (str[j] != pattern[j - i])
			{
				break;
			}
		}
		if (j == (i + patternLength))
		{
			return true;
		}
	}
	return false;
}

#if 0
		DWORD dwBytesWritten;
		HANDLE hTemp = CreateFile("c:\\temp\\sig.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS,
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		
		WriteFile(hTemp, i_pbSignature, i_dwSignature, &dwBytesWritten, NULL);

		CloseHandle(hTemp);
#endif
