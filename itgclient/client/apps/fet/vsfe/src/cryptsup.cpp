// File containing the crypto stuff

#include "stdafx.h"
#include <shlobj.h>
#include <wininet.h>
#include "resource.h"
#include "dlgprocs.h"
#include "slist.h"
#include "cryptsup.h"	// the encryption routines
#include "certmgmt.h"
#include "ptav3.h"
#include "ptadefines.h"
#include "util.h"		// utility fns
#include "global.h" 
#include "safedel.h"
#include "vspmspP.h"
#include "vspmutil.h"
#include "vspmsp.h"
#include "policysup.h"
#include "ptaerrs.h"	// contains error codes which may come to us via the CSP interface
#include "vsps_defines.h"

extern SelectedCERT currSelCert;
extern PolicyVars g_LocalPolicy;
extern SafeSettings g_SafeProp;
extern TCHAR g_szSettingsFile[];
extern TCHAR g_szDecrSettingsFile[];
extern HashInfo g_PasswdHash;
extern BOOL g_bPasswdFail;
extern BOOL g_bVeriSignCSP;

DWORD g_dwProgressRange;


// These fns will be used to do encryption in chunks
STDMETHODIMP EncryptStart(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptPara, PCMSG_STREAM_INFO pStreamInfo,
						  ULONG *EncryptContext, PCERT_CONTEXT pCertContext, ULONG *CryptoError)
{
	// Initialize Enveloped Encode Info
	CMSG_ENVELOPED_ENCODE_INFO EnvelopedEncodeInfo;
	memset(&EnvelopedEncodeInfo, 0, sizeof(CMSG_ENVELOPED_ENCODE_INFO));
	EnvelopedEncodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
	EnvelopedEncodeInfo.hCryptProv = pEncryptPara->hCryptProv;
	EnvelopedEncodeInfo.ContentEncryptionAlgorithm = pEncryptPara->ContentEncryptionAlgorithm;
	EnvelopedEncodeInfo.pvEncryptionAuxInfo = pEncryptPara->pvEncryptionAuxInfo;
	EnvelopedEncodeInfo.cRecipients = 1;
	EnvelopedEncodeInfo.rgpRecipients = &(pCertContext->pCertInfo);

	// Open a message to encode.
	HCRYPTMSG hMsg = NULL;
	hMsg = CryptMsgOpenToEncode(
						MY_ENCODING_TYPE,		// Encoding type
						CMSG_DETACHED_FLAG,		// Flags
						CMSG_ENVELOPED,			// Msg type
						&EnvelopedEncodeInfo,	// Pointer to structure
						NULL,                   // Inner content ObjID.
						pStreamInfo);			// Stream Info

	if(!hMsg)
	{
		*CryptoError = GetLastError();
		
		// for VSCSP mode don't show error msg if user presses CANCEL on the open profile dialog
		if(!(g_bVeriSignCSP && *CryptoError == E_USERCANCELLED))
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);

		LogErrorMessage("EncryptStart:CryptMsgOpenToEncode() failed", *CryptoError);
		return E_UNEXPECTED;
	}

	*EncryptContext = (ULONG)hMsg;
	return S_OK;
}


// Called after EncryptStart() to start streaming the data, can be called multiple times
STDMETHODIMP EncryptUpdate(ULONG EncryptContext, BYTE *EncryptBuf, ULONG EncryptBufSize, ULONG *CryptoError)
{
	if(!CryptMsgUpdate((HCRYPTMSG)EncryptContext, EncryptBuf, EncryptBufSize, FALSE))
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptUpdate:CryptMsgUpdate() failed", *CryptoError);
		CryptMsgClose((HCRYPTMSG)EncryptContext);
		return E_UNEXPECTED;
	}

	return S_OK;
}


// Final call, for the last buffer to be encrypted.
STDMETHODIMP EncryptEnd(ULONG EncryptContext, BYTE *EncryptBuf, ULONG EncryptBufSize, ULONG *CryptoError)
{
	if(!CryptMsgUpdate((HCRYPTMSG)EncryptContext, EncryptBuf, EncryptBufSize, TRUE))
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptEnd:CryptMsgUpdate() failed", *CryptoError);
		CryptMsgClose((HCRYPTMSG)EncryptContext);
		return E_UNEXPECTED;
	}

	CryptMsgClose((HCRYPTMSG)EncryptContext);
	return S_OK;
}


STDMETHODIMP SignStart(PCCERT_CONTEXT pCertContext, LPSTR lpAlgID, PSIGN_CONTEXT *pSignContext, ULONG *CryptoError)
{
	PCRYPT_KEY_PROV_INFO pvData = NULL;
	DWORD cbData, dwKeySpec;
	HRESULT hr = S_OK;
	HCRYPTPROV hCryptProv = NULL;
	HCRYPTMSG hMsg = NULL;
	CRYPT_ALGORITHM_IDENTIFIER HashAlgorithm;
	CMSG_SIGNER_ENCODE_INFO SignerEncodeInfo,SignerEncodeInfoArray[1];
	CMSG_SIGNED_ENCODE_INFO SignedMsgEncodeInfo;
	CERT_BLOB SignerCertBlobArray;
	LPSTR lpszContainerName = NULL, lpszProviderName = NULL;

	do
	{
		if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, NULL, &cbData))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignStart:CertGetCertificateContextProperty() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		pvData = (PCRYPT_KEY_PROV_INFO)malloc(cbData);
		if(!pvData)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("SignStart() : Out of memory", 0);
			hr = E_OUTOFMEMORY;
			break;
		}

		if(!CertGetCertificateContextProperty(pCertContext, CERT_KEY_PROV_INFO_PROP_ID, (void*)pvData,  &cbData))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignStart:CertGetCertificateContextProperty() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		dwKeySpec = pvData->dwKeySpec;

		lpszProviderName = _WideToMultiString(pvData->pwszProvName);
		if(!lpszProviderName)
		{
			LogErrorMessage("SignStart:_WideToMultiString() failed", 0);
			hr = S_FALSE;
			break;
		}

		lpszContainerName = _WideToMultiString(pvData->pwszContainerName);
		if(!lpszContainerName)
		{
			LogErrorMessage("SignStart:_WideToMultiString() failed", 0);
			hr = S_FALSE;
			break;
		}

		if(!CryptAcquireContext(&hCryptProv, lpszContainerName, lpszProviderName, PROV_RSA_FULL, 0))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignStart:CryptAcquireContext() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		memset(&HashAlgorithm, 0, sizeof(HashAlgorithm));
		HashAlgorithm.pszObjId = lpAlgID;
		
		memset(&SignerEncodeInfo, 0, sizeof(CMSG_SIGNER_ENCODE_INFO));
		SignerEncodeInfo.cbSize = sizeof(CMSG_SIGNER_ENCODE_INFO);
		SignerEncodeInfo.pCertInfo = pCertContext->pCertInfo;
		SignerEncodeInfo.hCryptProv = hCryptProv;
		SignerEncodeInfo.dwKeySpec = dwKeySpec;
		SignerEncodeInfo.HashAlgorithm = HashAlgorithm;
		SignerEncodeInfo.pvHashAuxInfo = NULL;
		
		SignerEncodeInfoArray[0] = SignerEncodeInfo;

		SignerCertBlobArray.cbData = pCertContext->cbCertEncoded;
		SignerCertBlobArray.pbData = pCertContext->pbCertEncoded;

		memset(&SignedMsgEncodeInfo, 0, sizeof(CMSG_SIGNED_ENCODE_INFO));
		SignedMsgEncodeInfo.cbSize = sizeof(CMSG_SIGNED_ENCODE_INFO);
		SignedMsgEncodeInfo.cSigners = 1;
		SignedMsgEncodeInfo.rgSigners = SignerEncodeInfoArray;
		SignedMsgEncodeInfo.cCertEncoded = 1;
		SignedMsgEncodeInfo.rgCertEncoded = &SignerCertBlobArray;
		SignedMsgEncodeInfo.rgCrlEncoded = NULL;

		hMsg = CryptMsgOpenToEncode(MY_ENCODING_TYPE, CMSG_DETACHED_FLAG, CMSG_SIGNED, &SignedMsgEncodeInfo, NULL, NULL);
		if(!hMsg)
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignStart:CryptMsgOpenToEncode() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		*pSignContext = (PSIGN_CONTEXT)malloc(sizeof(SIGN_CONTEXT));
		if(!*pSignContext)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("SignStart() : Out of memory", 0);
			hr = E_OUTOFMEMORY;
			break;
		}

		(*pSignContext)->hMsg = hMsg;
		(*pSignContext)->hCryptProv = hCryptProv;

	} while(0);


	if(lpszContainerName)
	{
		free(lpszContainerName);
		lpszContainerName = NULL;
	}

	if(lpszProviderName)
	{
		free(lpszProviderName);
		lpszProviderName = NULL;
	}

	if(pvData)
	{
		free(pvData);
		pvData = NULL;
	}

	return hr;
}


STDMETHODIMP SignUpdate(PSIGN_CONTEXT pSignContext, BYTE *Buffer, ULONG BufferSize, ULONG *CryptoError)
{
	if(!CryptMsgUpdate(pSignContext->hMsg, Buffer, BufferSize, FALSE))
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("SignUpdate:CryptMsgUpdate() failed", *CryptoError);
		return E_UNEXPECTED;
	}

	return S_OK;
}


STDMETHODIMP SignEnd(PSIGN_CONTEXT pSignContext, BYTE *Buffer, ULONG BufferSize, ULONG *CryptoError, 
					 BYTE **Signature, ULONG *pdwSigLength)
{
	HRESULT hr = S_OK;
	*Signature = NULL;

	do
	{
		if(!CryptMsgUpdate(pSignContext->hMsg, Buffer, BufferSize, TRUE))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_DIG_SIG_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignEnd:CryptMsgUpdate() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		if(!CryptMsgGetParam(pSignContext->hMsg, CMSG_CONTENT_PARAM, 0, NULL, pdwSigLength))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignEnd:CryptMsgGetParam() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

		*Signature = (PBYTE)malloc(*pdwSigLength);
		if(!*Signature)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("SignEnd() : Out of memory", 0);
			hr = E_OUTOFMEMORY;
			break;
		}

		if(!CryptMsgGetParam(pSignContext->hMsg, CMSG_CONTENT_PARAM, 0, *Signature, pdwSigLength))
		{
			*CryptoError = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("SignEnd:CryptMsgGetParam() failed", *CryptoError);
			hr = E_UNEXPECTED;
			break;
		}

	} while(0);

	CryptMsgClose(pSignContext->hMsg);
	CryptReleaseContext(pSignContext->hCryptProv, 0);

	free(pSignContext);

	return hr;
}


BOOL InitiateDecrypt(PDECRYPT_CONTEXT pDecryptContext)
{
	BOOL retVal = TRUE;
	ULONG nSize = 0;
	int i = 0;
	DWORD dwErr = 0;
	HCRYPTMSG hMsg = pDecryptContext->hMsg;

	if(CryptMsgGetParam(hMsg, CMSG_ENVELOPE_ALGORITHM_PARAM, 0, NULL, &nSize))
	{
		HCERTSTORE hMyCertStore		= NULL;
		PCERT_INFO pReceiptCertInfo = NULL;
		ULONG nSize					= 0;
		DWORD dwReceiptCnt			= 0, dwSizeReceiptCnt = sizeof(DWORD);
		PCCERT_CONTEXT pReceiptCertContext = NULL;
		HCRYPTPROV hCryptProv		= NULL;
		PCRYPT_KEY_PROV_INFO pKeyProv = NULL;
		LPSTR szContainerName = NULL, szProviderName = NULL;

		if(!CryptAcquireContext(&hCryptProv, NULL, NULL,  PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CryptAcquireContext() failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		hMyCertStore = CertOpenSystemStore(hCryptProv, "MY");
		if(!hMyCertStore)
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CertOpenSystemStore() failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		pDecryptContext->hCertStore = hMyCertStore;

		// Get the recepient info.
		if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_COUNT_PARAM, 0, &dwReceiptCnt, &dwSizeReceiptCnt))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CryptMsgGetParam() Recipient Count failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_INFO_PARAM, 0, NULL, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CryptMsgGetParam() Recipient Info failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		pReceiptCertInfo = (PCERT_INFO)malloc(nSize);
		if(!pReceiptCertInfo)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt(): Out of memory", 0);
			retVal = FALSE;
			goto CleanUp;
		}

		for(i = 0; i < (int)dwReceiptCnt; i++)
		{
			if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_INFO_PARAM, i, pReceiptCertInfo, &nSize))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("InitiateDecrypt:CryptMsgGetParam() Recipient Info failed", dwErr);
				retVal = FALSE;
				goto CleanUp;
			}

			pReceiptCertContext = CertGetSubjectCertificateFromStore(hMyCertStore, MY_ENCODING_TYPE, pReceiptCertInfo);
			if(pReceiptCertContext)
				break;

			CertFreeCertificateContext(pReceiptCertContext);
			pReceiptCertContext = NULL;
		}
			
		if(i == (int)dwReceiptCnt)
		{
			DisplayMessage(GetFocus(), IDS_DIGID_ABSENT, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:Could not obtain the Digital ID for decryption", 0);
			retVal = FALSE;
			goto CleanUp;
		}
		
		pDecryptContext->pCertContext = pReceiptCertContext;

		// Check if the Certificate used for decryption is present in the list of certs in 
		// the metadata file. Needed to insure that a malicious user has not replaced the 
		// 'metadata' file and is now trying to decrypt files
		if(!VerifyCert(pReceiptCertContext))
		{
			DisplayMessage(GetFocus(), IDS_INVALID_USER, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:The metadata file may have been replaced. Cannot continue decryption", 0);
			retVal = FALSE;
			goto CleanUp;
		}

		if(!CertGetCertificateContextProperty(pReceiptCertContext, CERT_KEY_PROV_INFO_PROP_ID,
										      NULL, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CertGetCertificateContextProperty() failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
		if(!pKeyProv)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:Out of memory", 0);
			retVal = FALSE;
			goto CleanUp;
		}
		
		if(!CertGetCertificateContextProperty(pReceiptCertContext, CERT_KEY_PROV_INFO_PROP_ID,
										      pKeyProv, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CertGetCertificateContextProperty() failed", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		szContainerName = _WideToMultiString(pKeyProv->pwszContainerName);
		szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);

		// Release the previous context
		CryptReleaseContext(hCryptProv, 0);
		hCryptProv = NULL;

		if(!CryptAcquireContext(&hCryptProv, szContainerName, szProviderName, PROV_RSA_FULL, 0))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitiateDecrypt:CryptAcquireContext() failed",  dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

		pDecryptContext->hCryptProv = hCryptProv;

		CMSG_CTRL_DECRYPT_PARA DecryptParam;
		memset(&DecryptParam, 0, sizeof(CMSG_CTRL_DECRYPT_PARA));
		DecryptParam.cbSize		= sizeof(CMSG_CTRL_DECRYPT_PARA);
		DecryptParam.hCryptProv = hCryptProv;
		DecryptParam.dwKeySpec	= pKeyProv->dwKeySpec;
		DecryptParam.dwRecipientIndex = i;

		// Decrypt the enveloped message.
		if(!CryptMsgControl(hMsg, 0, CMSG_CTRL_DECRYPT, &DecryptParam))
		{   
			dwErr = GetLastError();

 			if(g_bVeriSignCSP)
 			{
 				if(dwErr == E_VS_INVALID_INFO_BLOB)
 					MessageBox(GetFocus(), "This file may have been encrypted with a profile which is not open currently. Please close the Safe and open it using the right profile.", "Safe", MB_OK | MB_ICONINFORMATION);
 				else
 					if(dwErr != E_USERCANCELLED)
 						DisplayMessage(GetFocus(), IDS_DECRYPT_ERR, MB_OK | MB_ICONERROR);
 			}
 			else
				DisplayMessage(GetFocus(), IDS_DECRYPT_ERR, MB_OK | MB_ICONERROR);

			LogErrorMessage("InitiateDecrypt:CryptMsgControl()", dwErr);
			retVal = FALSE;
			goto CleanUp;
		}

CleanUp:
		if(!retVal && pReceiptCertContext)
			CertFreeCertificateContext(pReceiptCertContext);

		if(!retVal && hCryptProv)
			CryptReleaseContext(hCryptProv, 0);

		if(!retVal && hMyCertStore)
			CertCloseStore(hMyCertStore, CERT_CLOSE_STORE_FORCE_FLAG);

		if(pReceiptCertInfo)
			free(pReceiptCertInfo);

		if(pKeyProv)
			free(pKeyProv);

		if(szContainerName)
			free(szContainerName);

		if(szProviderName)
			free(szProviderName);
	}
	else
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("InitiateDecrypt:CryptMessageGetParam() failed", dwErr);
	}

	return retVal;
}


// These fns will be used to do decryption in chunks
STDMETHODIMP DecryptStart(PCRYPT_DECRYPT_MESSAGE_PARA pDecryptPara, ULONG *DecryptContext,
						  PCMSG_STREAM_INFO pStreamInfo, ULONG *CryptoError)
{
	HCRYPTMSG hMsg = NULL;
	PDECRYPT_CONTEXT pDecryptCxt;

	hMsg = CryptMsgOpenToDecode(
			   MY_ENCODING_TYPE,		// Encoding type
			   CMSG_DETACHED_FLAG, 		// Flags
			   0,						// Message type (get from msg.)
			   NULL,					// Cryptographic provider
			   NULL,					// Recipient info
			   pStreamInfo);			// Stream info

	if(!hMsg)
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("DecryptStart:CryptMsgOpenToDecode() failed", *CryptoError);
		return E_UNEXPECTED;
	}

	pDecryptCxt = (PDECRYPT_CONTEXT)malloc(sizeof(DECRYPT_CONTEXT));
	if(!pDecryptCxt)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("DecryptStart : Out of memory", 0);
		return E_UNEXPECTED;
	}

	memset(pDecryptCxt, 0, sizeof(DECRYPT_CONTEXT));

	pDecryptCxt->hMsg			= hMsg;
	pDecryptCxt->bControlCalled	= FALSE;
	*DecryptContext				= (ULONG)pDecryptCxt;

	return S_OK;
}


// Called after DecryptStart() to start streaming the data. Can be called multiple times
STDMETHODIMP DecryptUpdate(ULONG DecryptContext, BYTE *DecryptBuf, ULONG DecryptBufSize, ULONG *CryptoError)
{
	PDECRYPT_CONTEXT pDecryptContext = (PDECRYPT_CONTEXT)DecryptContext;
	HCRYPTMSG hMsg		= pDecryptContext->hMsg;
	BOOL bControlCalled = pDecryptContext->bControlCalled;

	if(!CryptMsgUpdate(hMsg, DecryptBuf, DecryptBufSize, FALSE))
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("DecryptUpdate:CryptMsgUpdate() failed", *CryptoError);

		CryptMsgClose(hMsg);
		
		if(bControlCalled)
		{
			CertFreeCertificateContext(pDecryptContext->pCertContext);
			CryptReleaseContext(pDecryptContext->hCryptProv, 0);
			CertCloseStore(pDecryptContext->hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
			free(pDecryptContext);
		}

		return E_UNEXPECTED;
	}

	if(!bControlCalled)
	{
		pDecryptContext->bControlCalled = TRUE;

		if(!InitiateDecrypt(pDecryptContext))
		{
			CryptMsgClose(hMsg);
			free(pDecryptContext);
			return E_UNEXPECTED;
		}
	}

	return S_OK;
}


// Final call, for the last buffer to be decrypted.
STDMETHODIMP DecryptEnd(ULONG DecryptContext, BYTE *DecryptBuf, ULONG DecryptBufSize, ULONG *CryptoError)
{
	PDECRYPT_CONTEXT pDecryptContext = (PDECRYPT_CONTEXT)DecryptContext;
	HCRYPTMSG hMsg		= pDecryptContext->hMsg;
	BOOL bControlCalled = pDecryptContext->bControlCalled;

	if(!CryptMsgUpdate(hMsg, DecryptBuf, DecryptBufSize, TRUE))
	{
		*CryptoError = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("DecryptEnd:CryptMsgUpdate() failed", *CryptoError);
		CryptMsgClose(hMsg);
		return E_UNEXPECTED;
	}

	if(!bControlCalled)
	{
		pDecryptContext->bControlCalled = TRUE;

		if(!InitiateDecrypt(pDecryptContext))
		{
			CryptMsgClose(hMsg);
			free(pDecryptContext);
			return E_UNEXPECTED;
		}
	}

	CryptMsgClose(hMsg);
	CertFreeCertificateContext(pDecryptContext->pCertContext);
	CryptReleaseContext(pDecryptContext->hCryptProv, 0);
	CertCloseStore(pDecryptContext->hCertStore, CERT_CLOSE_STORE_FORCE_FLAG);
	free(pDecryptContext);

	return S_OK;
}


// Called before starting 'encryption' operation, initialises the encryption alg
InitStatus InitEncryptParams(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptParam)
{
	DWORD dwErr = 0;
	HCRYPTPROV hCryptProv = NULL;
	PCRYPT_KEY_PROV_INFO pKeyProv = NULL;
	ULONG nSize = 0;
	LPSTR szContainerName = NULL, szProviderName = NULL;

	if(!currSelCert.pCertContext)
		return FAILED;

	do
	{
		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  NULL, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitEncryptParams:CertGetCertificateContextProperty() failed", dwErr);
			break;
		}

		pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
		if(!pKeyProv)
		{
			DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
			LogErrorMessage("InitEncryptParams() : Out of memory", 0);
			break;
		}
		
		if(!CertGetCertificateContextProperty(currSelCert.pCertContext, CERT_KEY_PROV_INFO_PROP_ID,
											  pKeyProv, &nSize))
		{
			dwErr = GetLastError();
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitEncryptParams:CertGetCertificateContextProperty() failed", dwErr);
			break;
		}
			
		szContainerName = _WideToMultiString(pKeyProv->pwszContainerName);
		szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);

		if(CryptAcquireContext(&hCryptProv, NULL, szProviderName, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			memset(pEncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));

			CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm;
			memset(&EncryptAlgorithm, 0, sizeof(EncryptAlgorithm));

			if(!strnicmp(g_LocalPolicy.EncryptionAlg, "RC2", 3))
			{
				EncryptAlgorithm.pszObjId = szOID_RSA_RC2CBC;

				TCHAR szBits[16];
				int iBits;
				for(int j = 0, i = 4; g_LocalPolicy.EncryptionAlg[i] != ' '; i++ , j++)
					szBits[j] = g_LocalPolicy.EncryptionAlg[i];

				szBits[j] = '\0';
				iBits = atoi(szBits);

				// Set the no of bits for RC2
				pEncryptParam->pvEncryptionAuxInfo = malloc(2 * sizeof(DWORD));
				if(!(pEncryptParam->pvEncryptionAuxInfo))
				{
					DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
					LogErrorMessage("InitEncryptParams() : Out of memory", 0);
					return FAILED;
				}

				DWORD *dwAuxInfo = (DWORD *)pEncryptParam->pvEncryptionAuxInfo;
				dwAuxInfo[0] = 2 * sizeof(DWORD);
				dwAuxInfo[1] = iBits;
			}
			else
				if(!strnicmp(g_LocalPolicy.EncryptionAlg, "RC4", 3))
					EncryptAlgorithm.pszObjId = szOID_RSA_RC4;
				else
					if(!lstrcmpi(g_LocalPolicy.EncryptionAlg, "RC5"))
						EncryptAlgorithm.pszObjId = szOID_RSA_RC5_CBCPad;
					else
						if(!lstrcmpi(g_LocalPolicy.EncryptionAlg, "DES-56 bits"))
							EncryptAlgorithm.pszObjId = szOID_OIWSEC_desCBC;
						else
							if(!lstrcmpi(g_LocalPolicy.EncryptionAlg, "3DES-168 bits"))
								EncryptAlgorithm.pszObjId = szOID_RSA_DES_EDE3_CBC;
			
			pEncryptParam->cbSize = sizeof(CRYPT_ENCRYPT_MESSAGE_PARA);
			pEncryptParam->dwMsgEncodingType = MY_ENCODING_TYPE;
			pEncryptParam->ContentEncryptionAlgorithm = EncryptAlgorithm;

			pEncryptParam->hCryptProv = hCryptProv;
		}
		else
		{
			dwErr = GetLastError();
			hCryptProv = NULL;
			DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
			LogErrorMessage("InitEncryptParams:CryptAcquireContext() failed", dwErr);
			break;
		}

	} while(0);

	if(pKeyProv)
	{
		free(pKeyProv);
		pKeyProv = NULL;
	}

	if(szContainerName)
	{
		free(szContainerName);
		szContainerName = NULL;
	}

	if(szProviderName)
	{
		free(szProviderName);
		szProviderName = NULL;
	}

	return (hCryptProv ? OKAY : FAILED);
}


	
BOOL DeinitEncryptParams(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptParam)
{
	if(pEncryptParam->pvEncryptionAuxInfo)
	{
		free(pEncryptParam->pvEncryptionAuxInfo);
		pEncryptParam->pvEncryptionAuxInfo = NULL;
	}

	if(pEncryptParam->hCryptProv)
	{
		CryptReleaseContext(pEncryptParam->hCryptProv, 0);
		pEncryptParam->hCryptProv = NULL;
	}

	return TRUE;
}


// This is called when file/folder is dropped on the Safe. The fn recursively copies
// the files and directories into the Destination folder. The original files are 
// "securely deleted"

// 'szDestFolder' - Folder on which "drop" is done
// 'szSource'	  - The source of the drop. can be a directory or file. if directory then
//					fn will recurse
CopyError EncryptAll(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptParam, PTCHAR szDestFolder, PTCHAR szSource)
{
	DWORD dwFattr = 0, dwErr = 0;
	TCHAR szDestination[MAX_PATH_LEN], szSearchPath[MAX_PATH_LEN], szTempFile[MAX_PATH_LEN];
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], *pBSlash = NULL;
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	UINT Action;
	BOOL bFilesPresent = FALSE;

	if(szDestFolder[0] == '\0' || szSource[0] == '\0')
		return skip;

	// Check if 'szSource' is a directory. If it is then process its contents also
	dwFattr = GetFileAttributes(szSource);
	if(dwFattr & FILE_ATTRIBUTE_DIRECTORY)
	{
		ShowWindow(g_hAnimateDlg, SW_HIDE);
		EncryptStatus Stat = CanEncrypt(szSource);
		ShowWindow(g_hAnimateDlg, SW_SHOWNORMAL);
		if(Stat != SUCCESS)
			return (Stat == CANCEL ? cancel : skip);

		// Construct destination dir
		pBSlash = strrchr(szSource, '\\');
		if(!pBSlash)
			return badparams;

		lstrcpy(szDestination, szDestFolder);
		lstrcat(szDestination, pBSlash);

		// Check if the directory already exists
		hFind = FindFirstFile(szDestination, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			// Folder already exists.  
			FindClose(hFind);
			
			// If the folder contains only the 'fileinfo' with all files in it in the DECRYPTED 
			// state don't prompt for overwrite, this is bocs all files in this folder have been
			// decrypted, the folder has been retained just bcos it contains the fileinfo file 
			// to show the list of recently decrypted files. Delete the folder when the Safe is locked
			if(IsFolderPresent(szDestination))
			{
				if(g_bPrompt)
					Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_REPLACE), GetActiveWindow(), 
											(DLGPROC)ReplaceConfirm, (LONG)szDestination);
				else
					Action = IDB_YESTOALL;

				switch(Action)
				{
					case IDB_YESTOALL:
						g_bPrompt = FALSE;  // don't prompt now on
						// Fall through code
					case IDOK:
						break;

					case IDCANCEL:
						return cancel;

					case IDB_NO:
						return skip;
				}
			}
		}
		else
		{
			// create the destination dir, no security params for now
			if(g_LocalPolicy.EncryptMethod != INPLACE)
			{
				if(!CreateDirectory(szDestination, NULL))
				{
					dwErr = GetLastError();
					LoadString(g_hInst, IDS_DIR_CREATE_ERR, szMsg, MAX_MSG_LEN);
					wsprintf(szFmt, szMsg, szDestination);
					MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
					wsprintf(szMsg, "EncryptAll:CreateDirectory() \'%s\' failed", szDestination);
					LogErrorMessage(szMsg, dwErr);
					FindClose(hFind);
					return createdirerr;
				}
			}
		}

		// For each file in the source directory do the encryption. Get all the files
		lstrcpy(szSearchPath, szSource);
		lstrcat(szSearchPath, "\\*.*");

		hFind = FindFirstFile(szSearchPath, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			do
			{
				// Ignore "." and ".."
				if(!lstrcmpi(wfd.cFileName, ".") || !lstrcmpi(wfd.cFileName, ".."))
					continue;

				bFilesPresent = TRUE;

				// For all other files/directories call EncryptAll() again, first construct
				// the complete source path
				lstrcpy(szSearchPath, szSource);
				lstrcat(szSearchPath, "\\");
				lstrcat(szSearchPath, wfd.cFileName);

 				CopyError retVal = EncryptAll(pEncryptParam, szDestination, szSearchPath);
				switch(retVal)
				{
					// Only handle 'cancel for now' for all other errors continue with the next file/dir
					case cancel:
						FindClose(hFind);
						return cancel;
					default:
						break;
				}
			}
			while(FindNextFile(hFind, &wfd));

			FindClose(hFind);
			
			// Now delete the source directory. the dir must be empty
			// Remove the directory only if it originally contained some files. If it did not 
			// contain any files to start with then dont remove it
			if(bFilesPresent)
				if(!RemoveDirectory(szSource))
					return remdirerr;

			return okay;
		}
		else
			return fferror;
	}
	else
	{
		// Encrypt the source file and copy it to the destination. Delete the source file securely
		// Construct destination file
		pBSlash = strrchr(szSource, '\\');
		if(!pBSlash)
			return badparams;

		lstrcpy(szDestination, szDestFolder);
		lstrcat(szDestination, pBSlash);
		
		// Check if destination file exists
		if(g_LocalPolicy.EncryptMethod == INPLACE)
		{
			lstrcpy(szTempFile, szSource);
			lstrcat(szTempFile, ".enc");
		}
		else
			lstrcpy(szTempFile, szDestination);


		hFind = FindFirstFile(szTempFile, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			// File already exists
			FindClose(hFind);
		
			if(g_bPrompt)
				Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_REPLACE), GetActiveWindow(), 
								   (DLGPROC)ReplaceConfirm, (LONG)szTempFile);
			else
				Action = IDB_YESTOALL;

			switch(Action)
			{
				case IDB_YESTOALL:
					g_bPrompt = FALSE;  // don't prompt now on
					// Fall through code
				case IDOK:
					break;

				case IDCANCEL:
					return cancel;

				case IDB_NO:
					return skip;
			}
		}

		EncryptStatus Stat = EncryptAndSignFile(pEncryptParam, szSource, szDestination);
 		if(Stat != SUCCESS)
			return (Stat == CANCEL ? cancel : skip);

		return okay;
	} // else (file)
}



// Called from the drop target handler or the context menu handler
BOOL EncryptDroppedItems(HWND hWndDrop, HDROP hSourceFiles, const PTCHAR szDestFolder)
{
	if(szDestFolder[0] == '\0' || hSourceFiles == NULL)
		return FALSE;

	if(!PasswordPrompt(ENCRYPT))
		return FALSE;

	g_bPrompt = TRUE;  // Always set this to TRUE initially

	TCHAR szFileDropped[MAX_PATH_LEN];
	UINT nFileCnt = DragQueryFile(hSourceFiles, -1, NULL, 0);
	UINT i = 0;
	DWORD dwAttr = 0;

	// Initialize the encryption params
	CRYPT_ENCRYPT_MESSAGE_PARA EncryptParam;
	memset(&EncryptParam, 0, sizeof(CRYPT_ENCRYPT_MESSAGE_PARA));
	InitStatus stat = InitEncryptParams(&EncryptParam);

	// Doing a renewal, return
 	if(stat == RENEW || stat == NO_MATCHES)
		return TRUE;

	if(stat == FAILED)
		return FALSE;

	CreateAnimateDlg(hWndDrop, 1);
	g_bEncryptErrPrompt = TRUE;
	g_bReadErrPrompt	= TRUE;
	g_bFilterErrPrompt	= TRUE;

	while(i < nFileCnt)
	{
		szFileDropped[0] = '\0';
		DragQueryFile(hSourceFiles, i++, szFileDropped, sizeof(szFileDropped));
		if(szFileDropped[0] == '\0')
			break;

		// Moves the file/directory recursively into folder 'szDestFolder' the original file 
		// is "securely deleted"
		dwAttr = GetFileAttributes(szFileDropped);
		CopyError retVal = EncryptAll(&EncryptParam, szDestFolder, szFileDropped);

		// Only handle 'cancel for now' for all other errors continue with the next file/dir
		if(retVal == cancel)
			break;
		else
			if(retVal == okay)
			{
				// Tell the Explorer view that a 'Folder' was deleted bcos of encryption and 
				// was added under the Safe hierarchy
				if(dwAttr & FILE_ATTRIBUTE_DIRECTORY)
				{
					SHChangeNotify(SHCNE_RMDIR, SHCNF_PATH, szFileDropped, NULL);

					// This is not working, when a Folder is added the '+' sign
					// doesnt appear on the Safe, might have to do CShellFolder::NotifyViews()
					// Check code of the SampView
					//SHChangeNotify(SHCNE_MKDIR, SHCNF_PATH, szDestFolder, NULL);
				}
			}

	} // end while

	DestroyAnimateDlg();
	DeinitEncryptParams(&EncryptParam);
	return TRUE;
}



EncryptStatus EncryptAndSignFile(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptParam, LPCSTR lpSourceFile, LPCSTR lpDestFile)
{
	if(lpSourceFile[0] == '\0' || lpDestFile[0] == '\0')
		return SKIP;

	// Set the filename being copied
	TCHAR *pBSlash = NULL, szMsg[MAX_MSG_LEN], szFmt[MAX_MSG_LEN];
	TCHAR szToSign[MAX_PATH_LEN];
	DWORD dwErr = 0;
	pBSlash = strrchr(lpSourceFile, '\\');
	if(!pBSlash || !(pBSlash + 1))
		return SKIP;

	SetDlgItemText(g_hAnimateDlg, IDC_FILE_NAME, pBSlash + 1);

	// Construct the From .... To ... string
	TCHAR szTemp[MAX_PATH_LEN], szFromTo[MAX_MSG_LEN], szFrom[MAX_MSG_LEN], szTo[MAX_MSG_LEN];
	lstrcpy(szTemp, lpSourceFile);
	pBSlash = strrchr(szTemp, '\\');
	*pBSlash = '\0';

	LoadString(g_hInst, IDS_FROM, szFrom, MAX_MSG_LEN);
	LoadString(g_hInst, IDS_TO, szTo, MAX_MSG_LEN);

	if(g_LocalPolicy.EncryptMethod == INPLACE)
		wsprintf(szFromTo, "%s \'%s\' %s \'%s", szFrom, szTemp, szTo, szTemp);
	else
	{
		wsprintf(szFromTo, "%s \'%s\' %s \'%s", szFrom, szTemp, szTo, g_szExtTitle);

		lstrcpy(szTemp, &lpDestFile[lstrlen(g_szStoragePath) + 1]);
		pBSlash = strrchr(szTemp, '\\');
		if(pBSlash)
		{
			*pBSlash = '\0';
			lstrcat(szFromTo, "\\");
			lstrcat(szFromTo, szTemp);
		}
	}

	lstrcat(szFromTo, "\'");

	SetDlgItemText(g_hAnimateDlg, IDC_FROM_TO, szFromTo);

	HANDLE hReadFile = CreateFile(lpSourceFile, GENERIC_READ, FILE_SHARE_READ, NULL, 
								  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpSourceFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EncryptAndSignFile:CreateFile() for \'%s\' failed", lpSourceFile);
		LogErrorMessage(szMsg, dwErr);
		return SKIP;
	}

	DWORD dwFileSize = GetFileSize(hReadFile, NULL);
	g_dwProgressRange = dwFileSize / MAX_READ_SIZE;

	// File size less than MAX_READ_SIZE
	if(g_dwProgressRange == 0)
		g_dwProgressRange = 1;
	
	DWORD dwRange = g_dwProgressRange;

	// Check if signatures are to be done and can be done
	BYTE KeyUsageBits;
	BOOL bSigKeyUsage = FALSE;
	if(CertGetIntendedKeyUsage(X509_ASN_ENCODING, currSelCert.pCertContext->pCertInfo, &KeyUsageBits, 1))
	{
		if(KeyUsageBits & CERT_DIGITAL_SIGNATURE_KEY_USAGE)
			bSigKeyUsage = TRUE;
	}

	if(g_LocalPolicy.bSignatureReqd && bSigKeyUsage)
		dwRange += g_dwProgressRange;

	if(g_LocalPolicy.bSecureDelete)
		dwRange += g_dwProgressRange;

	CloseHandle(hReadFile);

	HWND hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);
	SendMessage(hWndBar, PBM_SETRANGE32, 0, dwRange);
	SendMessage(hWndBar, PBM_SETPOS, 0, 0);
	SendMessage(hWndBar, PBM_SETSTEP, 1, 0);

	EncryptStatus Stat = EncryptFile(pEncryptParam, lpSourceFile, lpDestFile);

	if(Stat != SUCCESS)
		return (Stat == CANCEL ? CANCEL : SKIP);
	
	// Sign the file and put the signature at the end
	if(g_LocalPolicy.EncryptMethod == INPLACE)
	{
		lstrcpy(szToSign, lpSourceFile);
		lstrcat(szToSign, ".enc");
	}
	else
		lstrcpy(szToSign, lpDestFile);

	SignUpdateFile(szToSign);

	if(g_LocalPolicy.EncryptMethod != INPLACE)
		WriteInfoFile(szToSign);

	return SUCCESS;
}



EncryptStatus EncryptFile(PCRYPT_ENCRYPT_MESSAGE_PARA pEncryptParam, LPCSTR lpSourceFile, LPCSTR lpDestFile)
{
	TCHAR szSourceFile[MAX_PATH_LEN], cDestFile[MAX_PATH_LEN], szDestDir[MAX_PATH_LEN], *pStr = NULL;
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], cReadBuf[MAX_READ_SIZE];
	HANDLE hReadFile = NULL, hWriteFile = NULL;
	HWND hWndBar;
	EncryptStatus Status;
	DWORD dwErr = 0, dwBytesWritten = 0, dwStrLen = 0, dwFileSize = 0;
	DWORD dwBytesRead, dwTotalBytesRead = 0, dwCurrProgressPos = 0;
	ULONG EncryptContext, CryptoError;
	
	if(lpSourceFile[0] == '\0' || lpDestFile[0] == '\0')
		return SKIP;

	Status = CanEncrypt(lpSourceFile);
	if(Status != SUCCESS)
		return Status;

	lstrcpy(cDestFile, lpDestFile);
	if(g_LocalPolicy.EncryptMethod == INPLACE)
	{
		// in place encryption in taking place. create a temp. dest file in which
		// the encrypted contents will be placed.
		if(!GetTemporaryFile(cDestFile))
		{
			DisplayMessage(GetFocus(), IDS_TEMP_FILE_ERR, MB_OK | MB_ICONERROR);
			return SKIP;
		}
	}

	// Open for exclusive access.
	hReadFile = CreateFile(lpSourceFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		if(dwErr == ERROR_SHARING_VIOLATION)
		{
			LoadString(g_hInst, IDS_SHARE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, lpSourceFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "EncryptFile:File \'%s\' is in use by another application.", lpSourceFile);
			LogErrorMessage(szMsg, dwErr);
		}
		else
		{
			LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, lpSourceFile);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "EncryptFile:CreateFile() for \'%s\' failed", lpSourceFile);
			LogErrorMessage(szMsg, dwErr);
		}

		if(g_LocalPolicy.EncryptMethod == INPLACE)
			DeleteFile(cDestFile);	// delete the temp file
			
		return SKIP;
	}

	// Check if the destination dir exist. It may not exist for the case of encrypt at logoff. 
	// If so create it.
	lstrcpy(szDestDir, cDestFile);
	pStr = strrchr(szDestDir, '\\');
	if(!pStr)
		return SKIP;

	*pStr = '\0';

	if(CreateRecursiveDirectory(szDestDir) != S_OK)
	{
		LoadString(g_hInst, IDS_DIR_CREATE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, szDestDir);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EncryptFile() : Unable to create destination directory : \'%s\'", szDestDir);
		LogErrorMessage(szMsg, 0);
		CloseHandle(hReadFile);
		return SKIP;
	}

	hWriteFile = CreateFile(cDestFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hWriteFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, cDestFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EncryptFile:CreateFile() for \'%s\' failed", cDestFile);
		LogErrorMessage(szMsg, dwErr);
		CloseHandle(hReadFile);
		return SKIP;
	}

	CMSG_STREAM_INFO StreamInfo;
	memset(&StreamInfo, 0, sizeof(CMSG_STREAM_INFO));
	StreamInfo.cbContent = GetFileSize(hReadFile, NULL);
	StreamInfo.pfnStreamOutput = StreamOutputCallback;
	StreamInfo.pvArg = &hWriteFile;

	// In the 'hWriteFile' store information of the original file in a header before the 
	// PKCS#7 enveloped data. This header will include the original location of the file, 
	// the original size, date created, date modified, and the length of the encrypted file. 
	// This length will be the offset of the signature. 

	// 4 bytes indicating offset of signature
	SetFilePointer(hWriteFile, sizeof(DWORD), NULL, FILE_BEGIN);

	// the original location
	dwStrLen = lstrlen(lpSourceFile);
	WriteFile(hWriteFile, (void *)&dwStrLen, sizeof(DWORD), &dwBytesWritten, NULL);
	WriteFile(hWriteFile, (void *)lpSourceFile, lstrlen(lpSourceFile), &dwBytesWritten, NULL);
	
	// the original size
	dwFileSize = GetFileSize(hReadFile, NULL);
	WriteFile(hWriteFile, (void *)&dwFileSize, sizeof(DWORD), &dwBytesWritten, NULL);

	BY_HANDLE_FILE_INFORMATION fad;
	GetFileInformationByHandle(hReadFile, &fad);
	
	// the creation date
	WriteFile(hWriteFile, (void *)&fad.ftCreationTime, 2*sizeof(DWORD), &dwBytesWritten, NULL);

	// the modified date
	WriteFile(hWriteFile, (void *)&fad.ftLastWriteTime, 2*sizeof(DWORD), &dwBytesWritten, NULL);

	// the accessed date
	WriteFile(hWriteFile, (void *)&fad.ftLastAccessTime, 2*sizeof(DWORD), &dwBytesWritten, NULL);

	if(!g_LogOn_Off)
		hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);
	
	// now the encrypted data will be written
	dwFileSize = GetFileSize(hReadFile, NULL);

	Status = CRYPTFAIL;

	if(EncryptStart(pEncryptParam, &StreamInfo, &EncryptContext, currSelCert.pCertContext, &CryptoError) == S_OK)
	{
		while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
		{
			// Cancel button was pressed on the Animate dlg
			if(g_bCancelled)
			{
				g_bCancelled = FALSE;
				Status = CANCEL;
				break;
			}

			if(!g_LogOn_Off)
			{
				if(dwCurrProgressPos < g_dwProgressRange)
				{
					SendMessage(hWndBar, PBM_STEPIT, 0, 0);
					dwCurrProgressPos++;
				}

				ScanUserInput();
			}

			dwTotalBytesRead += dwBytesRead;

			if(dwTotalBytesRead == dwFileSize)
			{
				if(EncryptEnd(EncryptContext, (BYTE *)cReadBuf, dwBytesRead, &CryptoError) == S_OK)
					Status = SUCCESS;

				break;
			}

			if(EncryptUpdate(EncryptContext, (BYTE *)cReadBuf, dwBytesRead, &CryptoError) != S_OK)
				break;
		}
	}

	if(hWriteFile != NULL)
	{
		CloseHandle(hWriteFile);
		hWriteFile = NULL;
	}

 	if(Status != SUCCESS)
		DeleteFile(cDestFile);
	else
	{
		// Open the 'hWriteFile' again. It was closed in the Stream Callback, write the file 
		// length at the beginning of the file, this is used to find out whether signature is 
		// appended at end of file by using the length info
		hWriteFile = CreateFile(cDestFile, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
								FILE_ATTRIBUTE_ARCHIVE, NULL);
		dwFileSize = GetFileSize(hWriteFile, NULL);
		WriteFile(hWriteFile, (void *)&dwFileSize, sizeof(DWORD), &dwBytesWritten, NULL);
		CloseHandle(hWriteFile);
	}

	CloseHandle(hReadFile);

	if(Status == SUCCESS)
	{
		SecureDelete((LPTSTR)lpSourceFile);

		// copy the temp file to source file,
		if(g_LocalPolicy.EncryptMethod == INPLACE)
		{
			// Rename source file to .enc, first delete the .enc file just in case it is 
			// already present otherwise the MoveFile() would fail
			lstrcpy(szSourceFile, lpSourceFile);
			lstrcat(szSourceFile, ".enc");

			DeleteFile(szSourceFile);
			MoveFile(cDestFile, szSourceFile);	
		}
	}

	return Status;
}



// Called from DoOpen() for a file
DecryptStatus DoDecrypt(LPCTSTR szSourceFile, LPCTSTR szDestFile)
{
	// If the destination folder doesn't exist create it, if not possible to create prompt 
	// the user for selecting destination directory
	TCHAR szDestPath[MAX_PATH_LEN], szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], *pBSlash = NULL;
	TCHAR cReadBuf[MAX_READ_SIZE];
	DWORD dwErr = 0, dwBytesRead = 0, dwLengthToSkip = 0, dwSignOffset = 0, dwCurrOffset = 0;
	DWORD dwCurrProgressPos = 0;
	DecryptStatus Stat = DECR_FAIL;
	FILETIME ftDateCreated, ftDateModified, ftDateAccessed;
	HANDLE hWriteFile = NULL, hFind = NULL;
	WIN32_FIND_DATA wfd;
	UINT Action;
	CMSG_STREAM_INFO StreamInfo;
	ULONG ulCryptoError, ulDecryptContext;
	HWND hWndBar;


	if(szSourceFile[0] == '\0' || szDestFile[0] == '\0')
		return Stat;

	if(_strnicmp(szSourceFile, szDestFile, lstrlen(szDestFile)))
	{
		if(!CreateDestFolder(szDestFile, szDestPath))
			return Stat;
	}
	else
		lstrcpy(szDestPath, szDestFile);

	// Check if the file already exists out of the Safe
	if(!g_LogOn_Off)
	{
		hFind = FindFirstFile(szDestPath, &wfd);
		if(hFind != INVALID_HANDLE_VALUE)
		{
			// File already exists
			FindClose(hFind);

			if(g_bPrompt)
				Action = DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_REPLACE), GetActiveWindow(), 
								   (DLGPROC)ReplaceConfirm, (LONG)szDestPath);
			else
				Action = IDB_YESTOALL;

			switch(Action)
			{
				case IDB_YESTOALL:
					g_bPrompt = FALSE;  // don't prompt now on
					// Fall through code
				case IDOK:
					break;

				case IDCANCEL:
					return DECR_CANCEL;

				case IDB_NO:
					return DECR_SKIP;
			}
		}
	} // if(!g_LogOn_Off)


	HANDLE hReadFile = CreateFile(szSourceFile, GENERIC_READ, FILE_SHARE_READ, NULL, 
								  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, szSourceFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "DoDecrypt:CreateFile() for \'%s\' failed", szSourceFile);
		LogErrorMessage(szMsg, dwErr);
		return Stat;
	}

	hWriteFile = CreateFile(szDestPath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 
							FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hWriteFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, szDestPath);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "DoDecrypt:CreateFile() for \'%s\' failed", szDestFile);
		LogErrorMessage(szMsg, dwErr);
		CloseHandle(hReadFile);
		return Stat;
	}

	// In the 'hReadFile' skip over the header information before the PKCS#7 enveloped data. 
	// This header will include the original location of the file, the original size, date 
	// created, date modified, offset of signature

	// the first DWORD contains the length of the encrypted file, then the original file path 
	// to this add DWORDS for (original size + time created + time modified + time accessed)
	ReadFile(hReadFile, &dwSignOffset, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hReadFile, &dwLengthToSkip, sizeof(DWORD), &dwBytesRead, NULL);
	dwCurrOffset = SetFilePointer(hReadFile, dwLengthToSkip + sizeof(DWORD), NULL, FILE_CURRENT);

	// Set the 'file time' attributes of the decrypted file to the ones which were there 
	// before the file was encrypted. 
	ReadFile(hReadFile, (void *)&ftDateCreated, 2*sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hReadFile, (void *)&ftDateModified, 2*sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hReadFile, (void *)&ftDateAccessed, 2*sizeof(DWORD), &dwBytesRead, NULL);

	dwCurrOffset += 6*sizeof(DWORD);

	SetFileTime(hWriteFile, &ftDateCreated, &ftDateAccessed, &ftDateModified);
	
	memset(&StreamInfo, 0, sizeof(CMSG_STREAM_INFO));
	StreamInfo.cbContent		= GetFileSize(hReadFile, NULL);
	StreamInfo.pfnStreamOutput	= StreamOutputCallback;
	StreamInfo.pvArg			= &hWriteFile;

	if(!g_LogOn_Off)
		hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);
	
	// First param is ptr to 'PCRYPT_DECRYPT_MESSAGE_PARA' don't know what to pass
	if(DecryptStart(NULL, &ulDecryptContext, &StreamInfo, &ulCryptoError) == S_OK)
	{
		while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
		{
			if(!g_LogOn_Off)
			{
				if(dwCurrProgressPos < g_dwProgressRange)
				{
					SendMessage(hWndBar, PBM_STEPIT, 0, 0);
					dwCurrProgressPos++;
				}
				ScanUserInput();
			}

			if(g_bCancelled)
			{
				g_bCancelled = FALSE;
				Stat = DECR_CANCEL;
				break;
			}

			dwCurrOffset += dwBytesRead;

			if(dwCurrOffset < dwSignOffset)
			{
				if(DecryptUpdate(ulDecryptContext, (BYTE *)cReadBuf, dwBytesRead, &ulCryptoError) != S_OK)
					break;
			}
			else
			{
				dwBytesRead -= (dwCurrOffset - dwSignOffset);

				if(DecryptEnd(ulDecryptContext, (BYTE *)cReadBuf, dwBytesRead, &ulCryptoError) == S_OK)
					Stat = DECR_OK;

				break;
			}
		}
	}

	if(!g_LogOn_Off)
	{
		while(dwCurrProgressPos < g_dwProgressRange)
		{
			SendMessage(hWndBar, PBM_STEPIT, 0, 0);
			dwCurrProgressPos++;
		}
	}

	if(hWriteFile != NULL)
	{
		CloseHandle(hWriteFile);
		hWriteFile = NULL;
	}
	
	if(Stat != DECR_OK)
		DeleteFile(szDestPath);

	CloseHandle(hReadFile);
	return Stat;
}


BOOL SignUpdateFile(LPCSTR lpszFileToSign)
{
	LPBYTE pbDetachedSig;
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN];
	DWORD dwSigLength = 0, dwBytesWritten = 0, dwErr = 0;
	HANDLE hWriteFile = NULL;
	BYTE KeyUsageBits;

	if(lpszFileToSign[0] == '\0')
		return FALSE;

	if(!g_LocalPolicy.bSignatureReqd)
		return TRUE;

	// Also check if the current certificate can be used for signing, this is because we enable
	// the sign check box only if the cert has the signature key usage.
	if(CertGetIntendedKeyUsage(X509_ASN_ENCODING, currSelCert.pCertContext->pCertInfo, &KeyUsageBits, 1))
	{
		if(!(KeyUsageBits & CERT_DIGITAL_SIGNATURE_KEY_USAGE))
			return TRUE;
	}
	else
		return TRUE;


	dwSigLength = SignFile(lpszFileToSign, &pbDetachedSig);
	if(dwSigLength > 0)
	{
		// Write the sig at the end of the file
		hWriteFile = CreateFile(lpszFileToSign, GENERIC_WRITE, FILE_SHARE_READ, NULL, 
								OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hWriteFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, lpszFileToSign);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "SignUpdateFile:CreateFile() for \'%s\' failed", lpszFileToSign);
			LogErrorMessage(szMsg, dwErr);
			return TRUE;
		}

		SetFilePointer(hWriteFile, 0, NULL, FILE_END);
		WriteFile(hWriteFile, pbDetachedSig, dwSigLength, &dwBytesWritten, NULL);
		CloseHandle(hWriteFile);
		free(pbDetachedSig);
		return TRUE;
	}
	else
		return FALSE;
}


// Does a detached signature on the contents of 'lpFileToSign' return value contains the 
// length of signature
DWORD SignFile(LPCSTR lpFileToSign, PBYTE *pbDetachedSig)
{
	HWND hWndBar;
	PSIGN_CONTEXT pSignContext = NULL;
	BOOL bRetVal = FALSE;
	HANDLE hReadFile = NULL;
	TCHAR cReadBuf[MAX_READ_SIZE], *pHashAlg = NULL, szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], *pStr = NULL;
	DWORD dwBytesRead, dwCurrOffset = 0, dwCurrProgressPos = 0, dwFileSize = 0, dwErr = 0, dwDetachedSigLen = 0;

	*pbDetachedSig = NULL; 

	if(lpFileToSign[0] == '\0')
		return FALSE;

	do
	{
		hReadFile = CreateFile(lpFileToSign, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
							   FILE_ATTRIBUTE_ARCHIVE, NULL);
		if(hReadFile == INVALID_HANDLE_VALUE)
		{
			dwErr = GetLastError();
			LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, lpFileToSign);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
			wsprintf(szMsg, "SignFile:CreateFile() for \'%s\' failed", lpFileToSign);
			LogErrorMessage(szMsg, dwErr);
			break;
		}

		if(!g_LogOn_Off)
			hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);

		if(!lstrcmpi(g_LocalPolicy.HashAlg, "SHA-1"))
			pHashAlg = szOID_OIWSEC_sha1;
		else
			if(!lstrcmpi(g_LocalPolicy.HashAlg, "MD2"))
				pHashAlg = szOID_RSA_MD2;
			else
				if(!lstrcmpi(g_LocalPolicy.HashAlg, "MD4"))
					pHashAlg = szOID_RSA_MD4;
				else
					if(!lstrcmpi(g_LocalPolicy.HashAlg, "MD5"))
						pHashAlg = szOID_RSA_MD5;

		if(g_hAnimateDlg)
			ShowWindow(g_hAnimateDlg, SW_SHOWNORMAL);

		if(SignStart(currSelCert.pCertContext, pHashAlg, &pSignContext, &dwErr) != S_OK)
			break;

		dwFileSize = GetFileSize(hReadFile, NULL);

		while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
		{
			dwCurrOffset += dwBytesRead;

			if(!g_LogOn_Off)
			{
				if(dwCurrProgressPos < g_dwProgressRange)
				{
					SendMessage(hWndBar, PBM_STEPIT, 0, 0);
					dwCurrProgressPos++;
				}

				// Even if user presses cancel cannot cancel the operation now as we have 
				// already deleted the original file
				ScanUserInput();
			}

			if(dwCurrOffset < dwFileSize)
			{
				if(SignUpdate(pSignContext, (PBYTE)cReadBuf, dwBytesRead, &dwErr) != S_OK)
					break;
			}
			else
			{
				if(SignEnd(pSignContext, (PBYTE)cReadBuf, dwBytesRead, &dwErr, pbDetachedSig, 
						   &dwDetachedSigLen) != S_OK)
					break;

				bRetVal = TRUE;
				break;
			}
		}

	} while(0);


	if(hReadFile)
	{
		CloseHandle(hReadFile);
		hReadFile = NULL;
	}

	if(!bRetVal)
	{
		pStr = strrchr(lpFileToSign, '\\');
		LoadString(g_hInst, IDS_SIGN_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, pStr + 1);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "SignFile:Could not Sign File \'%s\'", pStr + 1);
		LogErrorMessage(szMsg, 0);
	}

	return dwDetachedSigLen;
}



DecryptStatus DecryptAll(LPCTSTR lpszToDecrypt)
{
	TCHAR szFileInfo[MAX_PATH_LEN], szFileName[MAX_PATH_LEN], *pStr = NULL;
	TCHAR szSearchPath[MAX_PATH_LEN], szOrigLocation[MAX_PATH_LEN], szOrigValue[MAX_PATH_LEN];
	WIN32_FIND_DATA wfd;
	HANDLE hFind = NULL;
	BY_HANDLE_FILE_INFORMATION fad;
	DecryptStatus Stat = DECR_FAIL;

	if(lpszToDecrypt[0] == '\0')
		return Stat;

	DWORD dwFattr = GetFileAttributes(lpszToDecrypt);
	if(dwFattr & FILE_ATTRIBUTE_DIRECTORY)
	{
		// For each file in the source directory do the decryption, get all the files
		lstrcpy(szSearchPath, lpszToDecrypt);
		lstrcat(szSearchPath, "\\*.*");

		hFind = FindFirstFile(szSearchPath, &wfd);
		do
		{
			// ignore "." , ".." and fileinfo
			if(!lstrcmpi(wfd.cFileName, ".")  || !lstrcmpi(wfd.cFileName, "..") ||
			   !lstrcmpi(wfd.cFileName, "fileinfo"))
				continue;

			// for all other files/directories call DecryptAll() again, first construct the complete source path
			lstrcpy(szSearchPath, lpszToDecrypt);
			lstrcat(szSearchPath, "\\");
			lstrcat(szSearchPath, wfd.cFileName);

			Stat = DecryptAll(szSearchPath);
			if(Stat == DECR_CANCEL)
			{
				FindClose(hFind);
				return Stat;
			}
		}
		while(FindNextFile(hFind, &wfd));

		FindClose(hFind);
	}
	else
	{	// Get filename and path of fileinfo file
		strcpy(szFileInfo, lpszToDecrypt);

		pStr = strrchr(szFileInfo, '\\');
		if(!pStr || !(pStr + 1))
			return Stat;

		strcpy(szFileName, pStr + 1);
		strcpy(pStr + 1, "fileinfo");
		
		GetPrivateProfileString(szFileName, "OrigLocation", "default", szOrigLocation, 
								MAX_PATH_LEN, szFileInfo);

		// Fileinfo file does not exist, create it
		if(!lstrcmpi(szOrigLocation, "default"))
			WriteInfoFile(lpszToDecrypt);

		GetPrivateProfileString(szFileName, "OrigLocation", "default", szOrigLocation, 
								MAX_PATH_LEN, szFileInfo);

		// The file is present in Safe
		if(lstrcmpi(szOrigLocation, "default") != 0)
		{
			SetAnimateDlgText(lpszToDecrypt, szOrigLocation);
			Stat = DecryptAndVerifyFile(lpszToDecrypt, szOrigLocation, TRUE);
			if(Stat == DECR_OK)
			{
				// mark the status of the file as out of Safe '1' = DECRYPTED
				WritePrivateProfileString(szFileName, "Status", "1", szFileInfo);

				// update the 'date created' field in the fileinfo, this
				// is displayed in the 'decrypted view'
				HANDLE hFile = CreateFile(szOrigLocation, GENERIC_READ, FILE_SHARE_READ, NULL, 
										  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);

				GetFileInformationByHandle(hFile, &fad);
				CloseHandle(hFile);

				sprintf(szOrigValue, "%u", fad.ftCreationTime.dwLowDateTime);
				WritePrivateProfileString(szFileName, "DateCreatedLow", szOrigValue, szFileInfo);

				sprintf(szOrigValue, "%u", fad.ftCreationTime.dwHighDateTime);
				WritePrivateProfileString(szFileName, "DateCreatedHigh", szOrigValue, szFileInfo);

				// Delete the file in Safe
				DeleteFile(lpszToDecrypt);
			}
		}
	}

	return Stat;
}


DecryptStatus DecryptAndVerifyFile(LPCTSTR lpszLocInSafe, LPCTSTR lpszLocOutOfSafe, BOOL bVerify)
{
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], *pBSlash = NULL;
	DWORD dwErr = 0, dwFileSize = 0, dwRange = 0, dwSigOffset = 0, dwBytesRead = 0;
	HWND hWndBar = NULL;
	HANDLE hReadFile = NULL;

	if(lpszLocInSafe[0] == '\0' || lpszLocOutOfSafe[0] == '\0')
		return DECR_FAIL;

	hReadFile = CreateFile(lpszLocInSafe, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
						   FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszLocInSafe);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "DecryptAndVerifyFile:CreateFile() for \'%s\' failed", lpszLocInSafe);
		LogErrorMessage(szMsg, dwErr);
		return DECR_FAIL;
	}

	dwFileSize = GetFileSize(hReadFile, NULL);
	g_dwProgressRange = dwFileSize / MAX_READ_SIZE;

	// File size less than MAX_READ_SIZE
	if(g_dwProgressRange == 0)
		g_dwProgressRange = 1;

	dwRange = g_dwProgressRange;

	ReadFile(hReadFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

	// Check if Signature present at the end of file
	if(bVerify)
		if(dwSigOffset != dwFileSize)
			dwRange += g_dwProgressRange;
	
	CloseHandle(hReadFile);

	hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);
	SendMessage(hWndBar, PBM_SETRANGE32, 0, dwRange);
	SendMessage(hWndBar, PBM_SETPOS, 0, 0);
	SendMessage(hWndBar, PBM_SETSTEP, 1, 0);

	if(bVerify)
	{
		// Verify the signature
		SigStatus Stat = VerifySignature(lpszLocInSafe);
		if(Stat == SIG_INVALID || Stat == SIG_GEN_FAIL)
		{
			pBSlash = strrchr(lpszLocInSafe, '\\');
			LoadString(g_hInst, IDS_VERIFY_FAIL, szMsg, MAX_MSG_LEN);
			wsprintf(szFmt, szMsg, pBSlash + 1);
			MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONINFORMATION);
			wsprintf(szMsg, "DecryptAndVerifyFile:Signature verification for file \'%s\' failed", pBSlash + 1);
			LogErrorMessage(szMsg, 0);
		}

		if(Stat == SIG_CANCEL)
			return DECR_CANCEL;
	}

	// Decrypt the file. Put the file back in original location
	DecryptStatus Stat = DoDecrypt(lpszLocInSafe, lpszLocOutOfSafe);
	if(Stat == DECR_CANCEL || Stat == DECR_SKIP)
		return Stat;

	if(Stat == DECR_FAIL)
	{
		pBSlash = strrchr(lpszLocInSafe, '\\');
		LoadString(g_hInst, IDS_DECRYPT_FAIL, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, pBSlash + 1);
		wsprintf(szMsg, "DecryptAndVerifyFile:Cannot decrypt file \'%s\'", pBSlash + 1);
		LogErrorMessage(szMsg, 0);
		return Stat;
	}

	return Stat;
}


// Verify the signature present at the end of 'lpszFile'
SigStatus VerifySignature(LPCSTR lpszFile)
{
	HANDLE hReadFile = NULL;
	DWORD dwErr = 0, dwCurrProgressPos = 0, dwSigOffset = 0, dwBytesRead = 0, dwFileSize = 0, dwCurrOffset = 0;
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN];

	if(lpszFile[0] == '\0')
		return SIG_GEN_FAIL;

	hReadFile = CreateFile(lpszFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 
						   FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hReadFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "VerifySignature:CreateFile() for \'%s\' failed", lpszFile);
		LogErrorMessage(szMsg, dwErr);
		return SIG_GEN_FAIL;
	}

	// The DWORD at the beginning of the file contains the offset of the signature
	ReadFile(hReadFile, (LPVOID)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

	SetFilePointer(hReadFile, dwSigOffset, NULL, FILE_BEGIN);

	dwFileSize = GetFileSize(hReadFile, NULL);

	// No Signature present at the end of file
	if(dwSigOffset == 0 || dwSigOffset >= dwFileSize)
	{
		CloseHandle(hReadFile);
		return NO_SIG;
	}

	BYTE *pbDetachedSig;
	UINT cbDetachedSig = dwFileSize - dwSigOffset;
	
	pbDetachedSig = (BYTE *)malloc(cbDetachedSig);
	if(!pbDetachedSig)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature() : Out of memory", 0);
		return SIG_GEN_FAIL;
	}
	
	ReadFile(hReadFile, (LPVOID)pbDetachedSig, cbDetachedSig, &dwBytesRead, NULL);

	// Decode the msg to get the hash from it
	DWORD cbHash = 0, cbSignerCertInfo = 0, cbAlgId = 0;
	BYTE *pbHash = NULL, *pbRev = NULL;
	SigStatus StatSig = SIG_GEN_FAIL;
	HCRYPTPROV hCryptProv = NULL; 
	PCERT_INFO pSignerCertInfo = NULL;
	HCERTSTORE hTempStore = NULL;
	PCCERT_CONTEXT pSignerCertContext = NULL;
	PCRYPT_ALGORITHM_IDENTIFIER pbAlgId = NULL;
	HCRYPTMSG hMsg = NULL;
	HCRYPTKEY Key;
	HCRYPTHASH hash;
	ALG_ID AlgId;
	TCHAR cReadBuf[MAX_READ_SIZE];
	UINT i;
	HWND hWndBar;

	hMsg = CryptMsgOpenToDecode(MY_ENCODING_TYPE, 0, 0, 0, NULL, NULL);
	if(!hMsg)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgOpenToDecode() failed.", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgUpdate(hMsg, pbDetachedSig, cbDetachedSig, TRUE))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgUpdate() failed.", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, NULL, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pbHash = (BYTE *)malloc(cbHash);
	if(!pbHash)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature() : Out of memory", 0);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, pbHash, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, NULL, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pSignerCertInfo = (PCERT_INFO) malloc(cbSignerCertInfo);
	if(pSignerCertInfo == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature() : Out of memory", 0);
		goto CleanUp;
	}

	// Get the message certificate information (CERT_INFO structure).
	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, pSignerCertInfo, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	// Open a certificate store in memory using CERT_STORE_PROV_MSG, which initializes it 
	// with the certificates from the message.
	hTempStore = CertOpenStore(CERT_STORE_PROV_MSG, MY_ENCODING_TYPE, NULL, 0, hMsg);
	if(hTempStore == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CertOpenStore() failed.", dwErr);
		goto CleanUp;
	}
	
	// Find the signer's certificate in the store.
	pSignerCertContext = CertGetSubjectCertificateFromStore(hTempStore, MY_ENCODING_TYPE, pSignerCertInfo);
	if(pSignerCertContext == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CertGetSubjectCertificateFromStore() failed.", dwErr);
		goto CleanUp;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptAcquireContext() failed.", dwErr);
		goto CleanUp;
	}

	if(!CryptImportPublicKeyInfo(hCryptProv, X509_ASN_ENCODING, &pSignerCertContext->pCertInfo->SubjectPublicKeyInfo, 
								 &Key))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptImportPublicKeyInfo() failed.", dwErr);
		goto CleanUp;
	}

	// Get the hash alg from the signature
	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, NULL, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pbAlgId = (PCRYPT_ALGORITHM_IDENTIFIER)malloc(cbAlgId);
	if(pbAlgId == NULL)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("VerifySignature : Out of memory", 0);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, pbAlgId, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD2))
		AlgId = CALG_MD2;
	else
		if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD4))
			AlgId = CALG_MD4;
		else
			if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD5))
				AlgId = CALG_MD5;
			else
				if(!lstrcmpi(pbAlgId->pszObjId, szOID_OIWSEC_sha1))
					AlgId = CALG_SHA1;

	if(!CryptCreateHash(hCryptProv, AlgId, NULL, 0, &hash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifySignature:CryptCreateHash() failed", dwErr);
		goto CleanUp;
	}

	SetFilePointer(hReadFile, 0, NULL, FILE_BEGIN);

	dwCurrOffset = 0;

	if(!g_LogOn_Off)
		hWndBar = GetDlgItem(g_hAnimateDlg, IDC_PROGRESS);

	while(ReadFile(hReadFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		// Cancel button was pressed on the Animate dlg
		if(g_bCancelled)
		{
			g_bCancelled = FALSE;
			StatSig = SIG_CANCEL;
			goto CleanUp;
		}

		if(!g_LogOn_Off)
		{
			if(dwCurrProgressPos < g_dwProgressRange)
			{
				SendMessage(hWndBar, PBM_STEPIT, 0, 0);
				dwCurrProgressPos++;
			}

			ScanUserInput();
		}

		dwCurrOffset += dwBytesRead;

		if(dwCurrOffset >= dwSigOffset)
			dwBytesRead -= (dwCurrOffset - dwSigOffset);
	
		CryptHashData(hash, (BYTE*)cReadBuf, dwBytesRead, 0);

		if(dwCurrOffset >= dwSigOffset)
			break;
	}

	if(!g_LogOn_Off)
	{
		while(dwCurrProgressPos < g_dwProgressRange)
		{
			SendMessage(hWndBar, PBM_STEPIT, 0, 0);
			dwCurrProgressPos++;
		}
	}

	pbRev = (BYTE *)malloc(cbHash);
	if(!pbRev)
	{
		DisplayMessage(GetFocus(), IDS_NO_MEMORY, MB_OK);
		LogErrorMessage("VerifySignature : Out of memory", 0);
		goto CleanUp;
	}

	for(i = 0; i < cbHash; i++)
		pbRev[i] = pbHash[cbHash - i - 1];

	if(CryptVerifySignature(hash, pbRev, cbHash, Key, NULL, 0))
		StatSig = SIG_VALID;
	else
		StatSig = SIG_INVALID;

CleanUp:
	if(hash)
		CryptDestroyHash(hash);

	if(hMsg)
		CryptMsgClose(hMsg);

	if(pbRev)
		free(pbRev);
	
	if(hTempStore)
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);

	if(pSignerCertInfo)
		free(pSignerCertInfo);
	
	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(pbDetachedSig)
		free(pbDetachedSig);

	if(pbHash)
		free(pbHash);

	if(pbAlgId)
		free(pbAlgId);

	if(hReadFile)
		CloseHandle(hReadFile);

	return StatSig;
}


/* PRRemove
// verify sig, compare IDN, SN for the signature on the entire file as well
// as on the signatures on the IDN and SN of each signing/encryption cert
// Create the POLICY_FILE
BOOL VerifyPassword(VOID)
{
	TCHAR *pStr = NULL;
	BOOL bRetVal = TRUE;
	g_bPasswdFail = TRUE;

	if(g_szSettingsFile[0] == '\0' || g_szDecrSettingsFile[0] == '\0')
		return FALSE;

	// '0' for decrypt
	if(!EncrDecrFileUsingPasswd(g_szSettingsFile, g_szDecrSettingsFile, 0))
		return FALSE;

	if(!VerifyDecryptDataFile())
		return FALSE;

	g_bPasswdFail = FALSE;
	return TRUE;
}
*/


// verify sig, compare IDN, SN for the signature on the entire file as well as on the 
// signatures on the IDN and SN of each signing/encryption cert, also create the POLICY_FILE
BOOL VerifyPassword(VOID)
{
	TCHAR *pStr = NULL;
	BOOL bRetVal = TRUE;

	g_bPasswdFail = TRUE;

	if(g_szSettingsFile[0] == '\0' || g_szDecrSettingsFile[0] == '\0')
		return FALSE;

	// Just copy the 'g_szSettingsFile' to 'g_szDecrSettingsFile' since there is no password now
	if(!CopyFile(g_szSettingsFile, g_szDecrSettingsFile, FALSE))
		return FALSE;

	if(!VerifyDecryptDataFile())
		return FALSE;

	g_bPasswdFail = FALSE;
	return TRUE;
}

BOOL VerifyDecryptDataFile(VOID)
{
	// Verify the signature on the 'decrdatafile'
	DWORD dwErr = 0;
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], cReadBuf[MAX_READ_SIZE];
	TCHAR szIssuerDN[MAX_MSG_LEN], szSerialNum[MAX_MSG_LEN];
	int i;
	ALG_ID AlgId;
	PBYTE pbHash = NULL, pbRev = NULL, pbSig = NULL;
	HCRYPTKEY Key;
	DWORD cbHash, cbSignerCertInfo = 0, cbAlgId = 0, dwSigLen = 0;
	DWORD dwCurrOffset = 0, totSize = 0, dwCertsOffset = 0, dwLen = 0;
	DWORD dwSigOffset = 0, dwPolicyFileOffset = 0, dwFileSize = 0, dwBytesRead = 0;
	HCRYPTPROV hCryptProv = NULL; 
	PCERT_INFO pSignerCertInfo = NULL;
	HCERTSTORE hTempStore = NULL;
	PCCERT_CONTEXT pSignerCertContext = NULL;
	PCRYPT_ALGORITHM_IDENTIFIER pbAlgId = NULL;
	HCRYPTMSG hMsg = NULL;
	HCRYPTHASH hash;
	BOOL bRetVal = FALSE;
	LPTSTR lpIssuer = NULL, lpSerial = NULL;
	
	if(g_szDecrSettingsFile[0] == '\0')
		return FALSE;
		
	HANDLE hDecrDataFile = CreateFile(g_szDecrSettingsFile, GENERIC_READ, 0, NULL, 
									  OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDecrDataFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, g_szDecrSettingsFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "VerifyDecryptDataFile:CreateFile() for \'%s\' failed", g_szDecrSettingsFile);
		LogErrorMessage(szMsg, dwErr);
		hDecrDataFile = NULL;
		goto CleanUp;
	}

	// 1st DWORD in decrdatafile contain the offset of the signature
	ReadFile(hDecrDataFile, (PBYTE)&dwSigOffset, sizeof(DWORD), &dwBytesRead, NULL);

	dwFileSize = GetFileSize(hDecrDataFile, NULL);

	if(dwSigOffset == 0 || dwSigOffset >= dwFileSize)
	{
		DisplayMessage(GetFocus(), IDS_SETTINGS_READ_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:Signature offset is 0 or greater than file size.", 0);
		goto CleanUp;
	}

	dwSigLen = dwFileSize - dwSigOffset;
	pbSig = (PBYTE)malloc(dwSigLen);

	SetFilePointer(hDecrDataFile, dwSigOffset, NULL, FILE_BEGIN);

	// Read the signature
	ReadFile(hDecrDataFile, pbSig, dwSigLen, &dwBytesRead, NULL);

	// Verify the Signature, get the IDN and SN and compare it with the IDN and SN
	// of the currently selected Encryption certificate
	hMsg = CryptMsgOpenToDecode(MY_ENCODING_TYPE, 0, 0, 0, NULL, NULL);
	if(!hMsg)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgOpenToDecode() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgUpdate(hMsg, pbSig, dwSigLen, TRUE))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgUpdate() failed", dwErr);
		goto CleanUp;
	}
	
	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, NULL, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pbRev = (BYTE *)malloc(cbHash);
	
	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, pbRev, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, NULL, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pSignerCertInfo = (PCERT_INFO)malloc(cbSignerCertInfo);

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, pSignerCertInfo, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}
	
	hTempStore = CertOpenStore(CERT_STORE_PROV_MSG, MY_ENCODING_TYPE, NULL, 0, hMsg);
	if(hTempStore == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CertOpenStore() failed", dwErr);
		goto CleanUp;
	}

	pSignerCertContext = CertGetSubjectCertificateFromStore(hTempStore, MY_ENCODING_TYPE, pSignerCertInfo);
	if(pSignerCertContext == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CertGetSubjectCertificateFromStore() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptAcquireContext() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptImportPublicKeyInfo(hCryptProv, X509_ASN_ENCODING, &pSignerCertContext->pCertInfo->SubjectPublicKeyInfo, &Key))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptImportPublicKeyInfo() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, NULL, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}
	
	pbAlgId = (PCRYPT_ALGORITHM_IDENTIFIER)malloc(cbAlgId);

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, pbAlgId, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD2))
		AlgId = CALG_MD2;
	else
		if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD4))
			AlgId = CALG_MD4;
		else
			if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD5))
				AlgId = CALG_MD5;
			else
				if(!lstrcmpi(pbAlgId->pszObjId, szOID_OIWSEC_sha1))
					AlgId = CALG_SHA1;

	// Reverse the hash
	pbHash = (PBYTE)malloc(cbHash);
	for(i = 0; i < (int)cbHash; i++)
		pbHash[cbHash - i - 1] = pbRev[i];

	if(!CryptCreateHash(hCryptProv, AlgId, NULL, 0, &hash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:CryptCreateHash() failed", dwErr);
		goto CleanUp;
	}
		
	SetFilePointer(hDecrDataFile, 0, NULL, FILE_BEGIN);
	while(ReadFile(hDecrDataFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		dwCurrOffset += dwBytesRead;

		if(dwCurrOffset >= dwSigOffset)
			dwBytesRead -= (dwCurrOffset - dwSigOffset);

		totSize += dwBytesRead;
	
		CryptHashData(hash, (BYTE*)cReadBuf, dwBytesRead, 0);

		if(dwCurrOffset >= dwSigOffset)
			break;
	}

	if(!CryptVerifySignature(hash, pbHash, cbHash, Key, NULL, 0))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_SETTINGS_VERF_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:Invalid Signature on the metadata file", dwErr);
		goto CleanUp;
	}
	
	// Compare the Serial Num and Issuer DN of the certificate used to sign the 'dfedecrdata' 
	// file with the SN and IDN present in it, skip over the settings
	SetFilePointer(hDecrDataFile, 18*sizeof(DWORD), NULL, FILE_BEGIN);

	// Serial Num
	ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, szSerialNum, dwLen, &dwBytesRead, NULL);
	szSerialNum[dwLen] = '\0';

	// Issuer DN
	ReadFile(hDecrDataFile, (PBYTE)&dwLen, sizeof(DWORD), &dwBytesRead, NULL);
	ReadFile(hDecrDataFile, szIssuerDN, dwLen, &dwBytesRead, NULL);
	szIssuerDN[dwLen] = '\0';

	lpIssuer = GetCertIssuerDN(pSignerCertInfo);
	if(!lpIssuer)
		goto CleanUp;

	lpSerial = GetCertSerNum(pSignerCertInfo);
	if(!lpSerial)
		goto CleanUp;

	if(lstrcmpi(szSerialNum, lpSerial) != 0 || lstrcmpi(szIssuerDN, lpIssuer) != 0)
	{
		DisplayMessage(GetFocus(), IDS_SETTINGS_VERF_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDecryptDataFile:Could not compare the IDN and SN of certificate present in metadata file with the certificate used to sign the file itself.", 0);
		goto CleanUp;
	}

	bRetVal = TRUE;

CleanUp:
	if(hDecrDataFile)
		CloseHandle(hDecrDataFile);

	if(pbSig)
		free(pbSig);

	if(hMsg)
		CryptMsgClose(hMsg);

	if(pbRev)
		free(pbRev);

	if(pSignerCertInfo)
		free(pSignerCertInfo);

	if(hTempStore)
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);

	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(pbAlgId)
		free(pbAlgId);

	if(pbHash)
		free(pbHash);

	if(hash)
		CryptDestroyHash(hash);

	if(lpIssuer)
		free(lpIssuer);

	if(lpSerial)
		free(lpSerial);

	if(!bRetVal)
		DeleteFile(g_szDecrSettingsFile);

	return bRetVal;
}


BOOL EncrDecrFileUsingPasswd(LPCTSTR lpszSourceFile, LPCTSTR lpszDestFile, BOOL bEncrypt)
{
	TCHAR szFmt[MAX_MSG_LEN], szMsg[MAX_MSG_LEN], cReadBuf[MAX_READ_SIZE];
	DWORD dwBytesRead = 0, dwBytesWritten = 0, dwErr = 0, dwTotalBytesRead = 0, dwReadFileSize = 0;
	BOOL bFinal = FALSE, bRetVal = FALSE;
	HANDLE hSrcFile = NULL, hDestFile = NULL;
	HCRYPTKEY  hSymCryptKey = NULL;
	HCRYPTPROV hCryptProv   = NULL;
	HCRYPTHASH hCryptHash   = NULL;

	if(lpszSourceFile[0] == '\0' || lpszDestFile[0] == '\0')
		return FALSE;

	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptFileUsingPasswd:CryptAcquireContext() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hCryptHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptFileUsingPasswd:CryptCreateHash() failed", dwErr);
		goto CleanUp;
	}
	
	if(!CryptHashData(hCryptHash, g_PasswdHash.pbHash, g_PasswdHash.dwLen, 0))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptFileUsingPasswd:CryptHashData() failed", dwErr);
		goto CleanUp;
	}
	
	// Generate the symmetric key.
	if(!CryptDeriveKey(hCryptProv, CALG_RC4, hCryptHash, 0,&hSymCryptKey))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("EncryptFileUsingPasswd:CryptDeriveKey() failed", dwErr);
		goto CleanUp;
	}

	hSrcFile = CreateFile(lpszSourceFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hSrcFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_READ_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszSourceFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EncryptFileUsingPasswd:CreateFile() for \'%s\' failed", lpszSourceFile);
		LogErrorMessage(szMsg, dwErr);
		hSrcFile = NULL;
		goto CleanUp;
	}

	hDestFile = CreateFile(lpszDestFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_ARCHIVE, NULL);
	if(hDestFile == INVALID_HANDLE_VALUE)
	{
		dwErr = GetLastError();
		LoadString(g_hInst, IDS_WRITE_FILE_ERR, szMsg, MAX_MSG_LEN);
		wsprintf(szFmt, szMsg, lpszDestFile);
		MessageBox(GetFocus(), szFmt, "Safe", MB_OK | MB_ICONERROR);
		wsprintf(szMsg, "EncryptFileUsingPasswd:CreateFile() for \'%s\' failed", lpszDestFile);
		LogErrorMessage(szMsg, dwErr);
		hDestFile = NULL;
		goto CleanUp;
	}

	dwReadFileSize = GetFileSize(hSrcFile, NULL);
	while(ReadFile(hSrcFile, cReadBuf, MAX_READ_SIZE, &dwBytesRead, NULL))
	{
		dwTotalBytesRead += dwBytesRead;
		if(dwTotalBytesRead == dwReadFileSize)
			bFinal = TRUE;

		if(bEncrypt)
		{
			if(!CryptEncrypt(hSymCryptKey, 0, bFinal, 0, (PBYTE)cReadBuf, &dwBytesRead, MAX_READ_SIZE))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("EncryptFileUsingPasswd:CryptEncrypt() failed", dwErr);
				goto CleanUp;
			}
		}
		else
		{
			if(!CryptDecrypt(hSymCryptKey, 0, bFinal, 0, (PBYTE)cReadBuf, &dwBytesRead))
			{
				dwErr = GetLastError();
				DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
				LogErrorMessage("EncryptFileUsingPasswd:CryptDecrypt() failed", dwErr);
				goto CleanUp;
			}
		}

		WriteFile(hDestFile, cReadBuf, dwBytesRead, &dwBytesWritten, NULL);

		if(bFinal)
		{
			bRetVal = TRUE;
			break;
		}
	}

CleanUp:
	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(hCryptHash)
		CryptDestroyHash(hCryptHash);

	if(hSymCryptKey)
		CryptDestroyKey(hSymCryptKey);

	if(hSrcFile)
		CloseHandle(hSrcFile);

	if(hDestFile)
		CloseHandle(hDestFile);

	return bRetVal;
}


// pvArg will contain the file handle
BOOL WINAPI StreamOutputCallback(const void *pvArg, BYTE *pbData, DWORD cbData, BOOL fFinal)
{
	ULONG nBytesWritten;
	DWORD dwErr = 0;
	HANDLE *hFile = NULL;

	if(!pvArg)
		return FALSE;

	hFile = (HANDLE*)(pvArg);
	
	if(!(*hFile))
		return FALSE;

	if(!WriteFile(*hFile, pbData, cbData, &nBytesWritten, NULL))
	{
		dwErr = GetLastError();
		LogErrorMessage("StreamOutputCallback:WriteFile() failed", dwErr);
	}

	if(fFinal)
	{
		CloseHandle(*hFile);
		*hFile = NULL;
	}

	return TRUE;
}



// Verify the signatures on the IDN and SN for all the Encryption and Signing certs
BOOL VerifySigList(VOID)
{
	LPCertDetails pCert = NULL;
	TCHAR szToVerify[2048];

	pCert = g_SafeProp.pCurrEncrCert;
	if(pCert)
	{
		lstrcpy(szToVerify, pCert->szSerialNum);
		lstrcat(szToVerify, pCert->szIssuerDN);
		if(!VerifyDetachedSig((PBYTE)szToVerify, lstrlen(szToVerify), pCert->Signature, pCert->dwSigLen))
			return FALSE;
	}

	pCert = g_SafeProp.pOldEncrCerts;
	while(pCert)
	{
		lstrcpy(szToVerify, pCert->szSerialNum);
		lstrcat(szToVerify, pCert->szIssuerDN);
		if(!VerifyDetachedSig((PBYTE)szToVerify, lstrlen(szToVerify), pCert->Signature, pCert->dwSigLen))
			return FALSE;

		pCert = pCert->pNext;
	}

	return TRUE;
}


BOOL VerifyDetachedSig(PBYTE pbDataToVerify, DWORD dwLenToVerify, PBYTE pbDetachedSig, DWORD dwSigLen)
{
	DWORD dwErr = 0;
	int i;
	ALG_ID AlgId;
	PBYTE pbHash = NULL, pbRev = NULL;
	HCRYPTKEY Key;
	DWORD cbHash, cbSignerCertInfo = 0, cbAlgId = 0;
	HCRYPTPROV hCryptProv = NULL; 
	PCERT_INFO pSignerCertInfo = NULL;
	HCERTSTORE hTempStore = NULL;
	PCCERT_CONTEXT pSignerCertContext = NULL;
	PCRYPT_ALGORITHM_IDENTIFIER pbAlgId = NULL;
	HCRYPTMSG hMsg = NULL;
	HCRYPTHASH hash;
	BOOL bRetVal = FALSE;
		
	hMsg = CryptMsgOpenToDecode(MY_ENCODING_TYPE, 0, 0, 0, NULL, NULL);
	if(!hMsg)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgOpenToDecode() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgUpdate(hMsg, pbDetachedSig, dwSigLen, TRUE))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgUpdate() failed", dwErr);
		goto CleanUp;
	}
	
	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, NULL, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pbRev = (BYTE *)malloc(cbHash);
	
	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, pbRev, &cbHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, NULL, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	pSignerCertInfo = (PCERT_INFO)malloc(cbSignerCertInfo);

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, pSignerCertInfo, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}
	
	hTempStore = CertOpenStore(CERT_STORE_PROV_MSG, MY_ENCODING_TYPE, NULL, 0, hMsg);
	if(hTempStore == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CertOpenStore() failed", dwErr);
		goto CleanUp;
	}

	pSignerCertContext = CertGetSubjectCertificateFromStore(hTempStore, MY_ENCODING_TYPE, pSignerCertInfo);
	if(pSignerCertContext == NULL)
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CertGetSubjectCertificateFromStore() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptAcquireContext() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptImportPublicKeyInfo(hCryptProv, X509_ASN_ENCODING, &pSignerCertContext->pCertInfo->SubjectPublicKeyInfo, 
								 &Key))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptImportPublicKeyInfo() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, NULL, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}
	
	pbAlgId = (PCRYPT_ALGORITHM_IDENTIFIER)malloc(cbAlgId);

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, pbAlgId, &cbAlgId))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptMsgGetParam() failed", dwErr);
		goto CleanUp;
	}

	if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD2))
		AlgId = CALG_MD2;
	else
		if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD4))
			AlgId = CALG_MD4;
		else
			if(!lstrcmpi(pbAlgId->pszObjId, szOID_RSA_MD5))
				AlgId = CALG_MD5;
			else
				if(!lstrcmpi(pbAlgId->pszObjId, szOID_OIWSEC_sha1))
					AlgId = CALG_SHA1;

	// Reverse the hash
	pbHash = (PBYTE)malloc(cbHash);
	for(i = 0; i < (int)cbHash; i++)
		pbHash[cbHash - i - 1] = pbRev[i];

	if(!CryptCreateHash(hCryptProv, AlgId, NULL, 0, &hash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("VerifyDetachedSig:CryptCreateHash() failed", dwErr);
		goto CleanUp;
	}
		
	CryptHashData(hash, (BYTE*)pbDataToVerify, dwLenToVerify, 0);

	if(!CryptVerifySignature(hash, pbHash, cbHash, Key, NULL, 0))
	{
		dwErr = GetLastError();
		LogErrorMessage("VerifyDetachedSig:CryptVerifySignature() failed", dwErr);
		goto CleanUp;
	}

	bRetVal = TRUE;

CleanUp:
	if(hMsg)
		CryptMsgClose(hMsg);

	if(pbRev)
		free(pbRev);

	if(pSignerCertInfo)
		free(pSignerCertInfo);

	if(hTempStore)
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);

	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(pbAlgId)
		free(pbAlgId);

	if(pbHash)
		free(pbHash);

	if(hash)
		CryptDestroyHash(hash);

	return bRetVal;
}


BOOL VerifyCert(PCCERT_CONTEXT pCertCxt)
{
	LPCertDetails pCert = NULL;
	TCHAR szIssuerDN[MAX_MSG_LEN], szSerialNum[MAX_MSG_LEN];
	LPTSTR lpIssuer = NULL, lpSerial = NULL;

	lpIssuer = GetCertIssuerDN(pCertCxt->pCertInfo);
	if(!lpIssuer)
		return FALSE;

	lstrcpy(szIssuerDN, lpIssuer);
	free(lpIssuer);

	lpSerial = GetCertSerNum(pCertCxt->pCertInfo);
	if(!lpSerial)
		return FALSE;

	lstrcpy(szSerialNum, lpSerial);
	free(lpSerial);

	pCert = g_SafeProp.pCurrEncrCert;
		
	if(pCert)
	{
		if(!lstrcmpi(pCert->szIssuerDN, szIssuerDN) && !lstrcmpi(pCert->szSerialNum, szSerialNum))
			return TRUE;
	}
	else
		return TRUE;	// if no encryption cert present return success
					    
	pCert = g_SafeProp.pOldEncrCerts;
	while(pCert)
	{
		if(!lstrcmpi(pCert->szIssuerDN, szIssuerDN) && !lstrcmpi(pCert->szSerialNum, szSerialNum))
			return TRUE;

		pCert = pCert->pNext;
	}

	return FALSE;
}


DWORD HashData(LPBYTE pbData, DWORD dwDataLen, PBYTE *pHashVal)
{
	HCRYPTPROV hCryptProv   = NULL;
	HCRYPTHASH hCryptHash   = NULL;
	DWORD dwHashLen = 0, dwErr = 0, dwLen = 0;

	*pHashVal = NULL;

	if(!CryptAcquireContext(&hCryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("HashData:CryptAcquireContext() failed", dwErr);
		goto CleanUp;
	}

	if(!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hCryptHash))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("HashData:CryptCreateHash() failed", dwErr);
		goto CleanUp;
	}
	
	if(!CryptHashData(hCryptHash, pbData, dwDataLen, 0))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("HashData:CryptHashData() failed", dwErr);
		goto CleanUp;
	}

	dwLen = sizeof(DWORD);
	if(!CryptGetHashParam(hCryptHash, HP_HASHSIZE, (PBYTE)&dwHashLen, &dwLen, 0))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("HashData:CryptHashData() failed", dwErr);
		goto CleanUp;
	}

	*pHashVal = (PBYTE)malloc(dwHashLen);

	dwLen = dwHashLen;
	if(!CryptGetHashParam(hCryptHash, HP_HASHVAL, (PBYTE)*pHashVal, &dwLen, 0))
	{
		dwErr = GetLastError();
		DisplayMessage(GetFocus(), IDS_CRYPT_ERR, MB_OK | MB_ICONERROR);
		LogErrorMessage("HashData:CryptHashData() failed", dwErr);
		goto CleanUp;
	}

CleanUp:
	if(hCryptHash)
		CryptDestroyHash(hCryptHash);

	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	return dwHashLen;
}
