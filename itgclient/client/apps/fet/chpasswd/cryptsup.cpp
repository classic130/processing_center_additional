#include "stdafx.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT  0x0400
#endif

#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>
#include "cryptsup.h"


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
		printf("DecryptStart:CryptMsgOpenToDecode() failed, error : %d",
			   *CryptoError);
		return E_UNEXPECTED;
	}

	pDecryptCxt = (PDECRYPT_CONTEXT)malloc(sizeof(DECRYPT_CONTEXT));
	if(!pDecryptCxt)
	{
		printf("DecryptStart() Could not allocate memory");
		return E_UNEXPECTED;
	}
	memset(pDecryptCxt, 0, sizeof(DECRYPT_CONTEXT));

	pDecryptCxt->hMsg			= hMsg;
	pDecryptCxt->bControlCalled	= FALSE;
	*DecryptContext				= (ULONG)pDecryptCxt;

	return S_OK;
}


// Called after DecryptStart() to start streaming the data. Can be called 
// multiple times
STDMETHODIMP DecryptUpdate(ULONG DecryptContext, BYTE *DecryptBuf, 
						   ULONG DecryptBufSize, ULONG *CryptoError)
{
	PDECRYPT_CONTEXT pDecryptContext = (PDECRYPT_CONTEXT)DecryptContext;
	HCRYPTMSG hMsg		= pDecryptContext->hMsg;
	BOOL bControlCalled = pDecryptContext->bControlCalled;

	if(!CryptMsgUpdate(hMsg, DecryptBuf, DecryptBufSize, FALSE))
	{
		*CryptoError = GetLastError();
		printf("DecryptUpdate:CryptMsgUpdate() failed, error %d",
			   *CryptoError);

		CryptMsgClose(hMsg);
		
		if(bControlCalled)
		{
			CryptMsgClose(hMsg);
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
STDMETHODIMP DecryptEnd(ULONG DecryptContext, BYTE *DecryptBuf, 
						ULONG DecryptBufSize, ULONG *CryptoError)
{
	PDECRYPT_CONTEXT pDecryptContext = (PDECRYPT_CONTEXT)DecryptContext;
	HCRYPTMSG hMsg		= pDecryptContext->hMsg;
	BOOL bControlCalled = pDecryptContext->bControlCalled;

	if(!CryptMsgUpdate(hMsg, DecryptBuf, DecryptBufSize, TRUE))
	{
		*CryptoError = GetLastError();
		printf("DecryptEnd:CryptMsgUpdate() failed, error %d",
			   *CryptoError);
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


BOOL InitiateDecrypt(PDECRYPT_CONTEXT pDecryptContext)
{
	BOOL retVal = TRUE;
	ULONG nSize = 0;
	int i = 0;
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

		if(!CryptAcquireContext(&hCryptProv, NULL, NULL,  PROV_RSA_FULL, 
								CRYPT_VERIFYCONTEXT))
		{
			printf("InitiateDecrypt:CryptAcquireContext() 0 failed, error %d", 
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		hMyCertStore = CertOpenSystemStore(hCryptProv, "MY");
		if(!hMyCertStore)
		{
			printf("InitiateDecrypt:CertOpenSystemStore() failed, error %d",
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		pDecryptContext->hCertStore = hMyCertStore;

		// Get the recepient info.
		if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_COUNT_PARAM, 0, &dwReceiptCnt, 
						 &dwSizeReceiptCnt))
		{
			printf("InitiateDecrypt:CryptMsgGetParam() Recipient Count failed, error %d",
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_INFO_PARAM, 0, NULL, &nSize))
		{
			printf("InitiateDecrypt:CryptMsgGetParam() Recipient Info 0 failed, error %d",
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		pReceiptCertInfo = (PCERT_INFO)malloc(nSize);
		if(!pReceiptCertInfo)
		{
			printf("InitiateDecrypt() Could not allocate memory 0");
			retVal = FALSE;
			goto CleanUp;
		}

		for(i = 0; i < (int)dwReceiptCnt; i++)
		{
			if(!CryptMsgGetParam(hMsg, CMSG_RECIPIENT_INFO_PARAM, i, pReceiptCertInfo, 
							 &nSize))
			{
				printf("InitiateDecrypt:CryptMsgGetParam() Recipient Info 1 failed, error %d",
					   GetLastError());
				retVal = FALSE;
				goto CleanUp;
			}

			pReceiptCertContext = CertGetSubjectCertificateFromStore(hMyCertStore, 
										MY_ENCODING_TYPE, pReceiptCertInfo);
			if(pReceiptCertContext)
				break;

			CertFreeCertificateContext(pReceiptCertContext);
			pReceiptCertContext = NULL;
		}

			
		if(i == (int)dwReceiptCnt)
		{
			printf("Could not obtain the Digital ID for decryption");
			retVal = FALSE;
			goto CleanUp;
		}
		
		pDecryptContext->pCertContext = pReceiptCertContext;

		if(!CertGetCertificateContextProperty(pReceiptCertContext, CERT_KEY_PROV_INFO_PROP_ID,
										      NULL, &nSize))
		{
			printf("InitiateDecrypt:CertGetCertificateContextProperty() 0 failed, error %d", 
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		pKeyProv = (PCRYPT_KEY_PROV_INFO)malloc(nSize);
		if(!pKeyProv)
		{
			printf("InitiateDecrypt() Could not allocate memory 1");
			retVal = FALSE;
			goto CleanUp;
		}
		
		if(!CertGetCertificateContextProperty(pReceiptCertContext, CERT_KEY_PROV_INFO_PROP_ID,
										      pKeyProv, &nSize))
		{
			printf("InitiateDecrypt:CertGetCertificateContextProperty() 1 failed, error %d",
				   GetLastError());
			retVal = FALSE;
			goto CleanUp;
		}

		szContainerName = _WideToMultiString(pKeyProv->pwszContainerName);
		szProviderName	= _WideToMultiString(pKeyProv->pwszProvName);

		// Release the previous context
		CryptReleaseContext(hCryptProv, 0);
		hCryptProv = NULL;

		if(!CryptAcquireContext(&hCryptProv, szContainerName, szProviderName , 
							PROV_RSA_FULL, 0))
		{
			printf("InitiateDecrypt:CryptAcquireContext() 1 failed, error %d", 
				   GetLastError());
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
			printf("InitiateDecrypt:CryptMsgControl(), error %d", 
				   GetLastError());
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
		printf("InitiateDecrypt:CryptMessageGetParam() failed, error %d",
			   GetLastError());

	return retVal;
}


BOOL WINAPI StreamOutputCallback(const void *pvArg, BYTE *pbData, DWORD cbData, 
								 BOOL fFinal)
{

	// pvArg will contain the file handle
	ULONG nBytesWritten;

	if(!WriteFile((void *)pvArg, pbData, cbData, &nBytesWritten, NULL))
	{
		DWORD dwErr = GetLastError();
		printf("StreamOutputCallback:WriteFile() failed, error %d", dwErr);
	}

	if(fFinal)
		CloseHandle((void *)pvArg);

	return TRUE;
}


LPSTR _WideToMultiString(BSTR szwcInputString)
{
	LPSTR szmbOutputString = NULL;
	DWORD dwSize = 0;

	if(szwcInputString == NULL)
		return NULL ;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								 szwcInputString, -1, NULL, 0, NULL, NULL) ;

	// Allocate memory for the Multi Byte String.
	if((szmbOutputString = (LPSTR)malloc(dwSize)) == NULL)
	{
		printf("_WideToMultiString : Out of memory");
		return NULL;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString, -1, szmbOutputString,
								dwSize, NULL, NULL);
	if(!dwSize)
	{
		printf("_WideToMultiString : Unable to convert from Wide Char string to Multi Byte string");
		return NULL;
	}

	return szmbOutputString ;
}


BOOL VerifySignatureAndEncryptHash(PBYTE pbData, DWORD dwDataLen, PBYTE pbDetachedSig,
				 DWORD dwSigLen, PBYTE *pbEncodedBlob, DWORD *dwEncodedBlob)
{
	DWORD dwErr, cbHash, cbSignerCertInfo = 0, cbAlgId = 0;
	BYTE *pbHash = NULL, *pbRev = NULL;
	HCRYPTPROV hCryptProv = NULL; 
	PCERT_INFO pSignerCertInfo = NULL;
	HCERTSTORE hTempStore = NULL;
	PCCERT_CONTEXT pSignerCertContext = NULL;
	PCRYPT_ALGORITHM_IDENTIFIER pbAlgId = NULL;
	HCRYPTMSG hMsg = NULL, hMsgEncrypt = NULL;
	BOOL bRetVal = FALSE;
	*pbEncodedBlob = NULL;
	UINT i;

	hMsg = CryptMsgOpenToDecode(MY_ENCODING_TYPE, 0, 0, 0, NULL, NULL);
	if(!hMsg)
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgOpenToDecode() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	if(!CryptMsgUpdate(hMsg, pbDetachedSig, dwSigLen, TRUE))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgUpdate() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, NULL, &cbHash))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 0 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	pbHash = (BYTE *)malloc(cbHash);
	if(!pbHash)
	{
		printf("VerifySignature() Could not allocate memory 0");
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_ENCRYPTED_DIGEST , 0, pbHash, &cbHash))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 1 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, NULL, 
						 &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 2 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	pSignerCertInfo = (PCERT_INFO) malloc(cbSignerCertInfo);
	if(pSignerCertInfo == NULL)
	{
		printf("VerifySignature:Could not allocate memory 1, error : %d");
		goto CleanUp;
	}

	// Get the message certificate information (CERT_INFO structure).
	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_CERT_INFO_PARAM, 0, 
						 pSignerCertInfo, &cbSignerCertInfo))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 3 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	// Open a certificate store in memory using CERT_STORE_PROV_MSG,
	// which initializes it with the certificates from the message.
	hTempStore = CertOpenStore(CERT_STORE_PROV_MSG, MY_ENCODING_TYPE, 
							   NULL, 0, hMsg);
	if(hTempStore == NULL)
	{
		dwErr = GetLastError();
		printf("VerifySignature:CertOpenStore() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}
	
	// Find the signer's certificate in the store.
	pSignerCertContext = CertGetSubjectCertificateFromStore(hTempStore,
							 MY_ENCODING_TYPE, pSignerCertInfo);
	if(pSignerCertContext == NULL)
	{
		dwErr = GetLastError();
		printf("VerifySignature:CertGetSubjectCertificateFromStore() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	if(!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 
							CRYPT_VERIFYCONTEXT))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptAcquireContext() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	HCRYPTKEY Key;
	if(!CryptImportPublicKeyInfo(hCryptProv, X509_ASN_ENCODING, 
			&pSignerCertContext->pCertInfo->SubjectPublicKeyInfo, &Key))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptImportPublicKeyInfo() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	// Get the hash alg from the signature
	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, NULL, 
					 &cbAlgId))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 0 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	pbAlgId = (PCRYPT_ALGORITHM_IDENTIFIER)malloc(cbAlgId);
	if(pbAlgId == NULL)
	{
		printf("VerifySignature:Could not allocate memory 2");
		goto CleanUp;
	}

	if(!CryptMsgGetParam(hMsg, CMSG_SIGNER_HASH_ALGORITHM_PARAM, 0, pbAlgId, 
					 &cbAlgId))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptMsgGetParam() 1 failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	ALG_ID AlgId;
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

	HCRYPTHASH hash;
	if(!CryptCreateHash(hCryptProv, AlgId, NULL, 0, &hash))
	{
		dwErr = GetLastError();
		printf("VerifySignature:CryptCreateHash() failed, error : %d",
			   dwErr);
		goto CleanUp;
	}

	CryptHashData(hash, (BYTE*)pbData, dwDataLen, 0);

	pbRev = (BYTE *)malloc(cbHash);
	if(!pbRev)
	{
		printf("VerifySignature:Could not allocate memory 3");
		goto CleanUp;
	}

	for(i = 0; i < cbHash; i++)
		pbRev[i] = pbHash[cbHash - i - 1];

	if(CryptVerifySignature(hash, pbRev, cbHash, Key, NULL, 0))
	{
		// Now encrypt the hash using the public key in the signature
		CRYPT_ALGORITHM_IDENTIFIER EncryptAlgorithm;
		memset(&EncryptAlgorithm, 0, sizeof(EncryptAlgorithm));

		EncryptAlgorithm.pszObjId = szOID_RSA_RC4;

		CMSG_ENVELOPED_ENCODE_INFO EnvelopedEncodeInfo;
		memset(&EnvelopedEncodeInfo, 0, sizeof(CMSG_ENVELOPED_ENCODE_INFO));
		EnvelopedEncodeInfo.cbSize = sizeof(CMSG_ENVELOPED_ENCODE_INFO);
		EnvelopedEncodeInfo.hCryptProv = hCryptProv;
		EnvelopedEncodeInfo.ContentEncryptionAlgorithm = EncryptAlgorithm;
		EnvelopedEncodeInfo.pvEncryptionAuxInfo = 0;
		EnvelopedEncodeInfo.cRecipients = 1;
		EnvelopedEncodeInfo.rgpRecipients = (PCERT_INFO*)&pSignerCertContext->pCertInfo;

		DWORD dwEncodedLen;
		if(!(dwEncodedLen = CryptMsgCalculateEncodedLength(
							 MY_ENCODING_TYPE, 0, CMSG_ENVELOPED,  
							 &EnvelopedEncodeInfo, NULL, dwDataLen)))          
			printf("Getting cbEncodedBlob length failed.");
		else
		{
			*pbEncodedBlob = (BYTE *)malloc(dwEncodedLen);
			if(!*pbEncodedBlob)
			{
			    printf("Memory allocation for the encoded blob failed.");
				goto CleanUp;
			}
			
			hMsgEncrypt = CryptMsgOpenToEncode(MY_ENCODING_TYPE, 0,                      
								CMSG_ENVELOPED, &EnvelopedEncodeInfo,   
								NULL, NULL);
			if(!hMsgEncrypt)
			{
				dwErr = GetLastError();
				printf("VerifySignature:CryptMsgOpenToEncode() failed, error : %d",
					   dwErr);
				goto CleanUp;
			}

			if(!CryptMsgUpdate(hMsgEncrypt, pbData, dwDataLen, TRUE))
			{
				dwErr = GetLastError();
				printf("VerifySignature:CryptMsgUpdate() 1 failed, error : %d",
					   dwErr);
				goto CleanUp;
			}
		 
			if(!CryptMsgGetParam(hMsgEncrypt, CMSG_CONTENT_PARAM, 0,
							    *pbEncodedBlob, dwEncodedBlob)) 
			{
				dwErr = GetLastError();
				printf("VerifySignature:Could not encode message(), error : %d",
					   dwErr);
				goto CleanUp;
			}
		
			bRetVal = TRUE;
		}
	}
	
CleanUp:
	if(hash)
		CryptDestroyHash(hash);

	if(hMsg)
		CryptMsgClose(hMsg);

	if(hMsgEncrypt)
		CryptMsgClose(hMsgEncrypt);

	if(pbRev)
		free(pbRev);
	
	if(hTempStore)
		CertCloseStore(hTempStore, CERT_CLOSE_STORE_FORCE_FLAG);

	if(pSignerCertInfo)
		free(pSignerCertInfo);
	//CertFreeCertificateContext(pSignerCertContext); gives access violation

	if(hCryptProv)
		CryptReleaseContext(hCryptProv, 0);

	if(pbHash)
		free(pbHash);

	if(pbAlgId)
		free(pbAlgId);

	return bRetVal;
}