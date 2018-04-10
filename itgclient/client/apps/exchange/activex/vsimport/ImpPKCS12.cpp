// ImpPKCS12.cpp : Implementation of CImpPKCS12
#include "stdafx.h"
#include "ImportPKCS12.h"
#include "ImpPKCS12.h"
#include "Pkcs8.h"
#include <wincrypt.h>

#include <stdio.h>

CImpPKCS12::CImpPKCS12()
{
	m_hCryptProv = NULL ;

	// Generate the UUID to be used as a Key Container Name
	UUID	uuid ;
	UuidCreate(&uuid) ;
	m_pszContainer = (BYTE *) malloc(1024) ;
	UuidToString((UUID *)&uuid, &m_pszContainer) ;

	m_bExportable = TRUE ;
	m_bUserProtected = FALSE ;

	if ( (m_hMyCertStore = CertOpenSystemStore(NULL, "MY")) == NULL )
		m_bMyCertStoreOpen = FALSE ;
	else
		m_bMyCertStoreOpen = TRUE ;

	if ( (m_hCACertStore = CertOpenSystemStore(NULL, "CA")) == NULL )
		m_bCACertStoreOpen = FALSE ;
	else
		m_bCACertStoreOpen = TRUE ;

	m_szCryptographicProvider = _WideToMultiString(MS_DEF_PROV_W) ;
}


CImpPKCS12::~CImpPKCS12()
{
	if ( !m_pszContainer )
		free(m_pszContainer) ;
}

/////////////////////////////////////////////////////////////////////////////
// CImpPKCS12

STDMETHODIMP CImpPKCS12::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IImpPKCS12,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CImpPKCS12::OnDraw(ATL_DRAWINFO& di)
{
/*
	RECT& rc = *(RECT*)di.prcBounds;
	Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);
	DrawText(di.hdcDraw, _T("ATL 2.0"), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
*/
	return S_OK;
}


/*****************************************************************************/
// Import() :	  This method takes a Base 64 encoded PKCS#12 message and imports
//				  it into the CAPI Certificate Store.
//
//  Input :
//	  i_pvarPKCS12 : VARIANT *
//				  The "bstrVal" element of "i_pvarPKCS12" specifies the 
//				  Base64 encoded PKCS#12 message that needs to be imported.
//				  NOT ANY MORE !!!! _ This just has the Base64 encoded PRIVATEKEYBLOB
//	  i_pvarPKCS7 : VARIANT *
//				  The "bstrVal" element of "i_pvarPKCS7" specifies a 
//				  Base64 encoded PKCS#7 message that needs to be associated with
//				  the PRIVATEKEYBLOB. This parameter may contain one or more
//				  certs.
//  Output :
//	  o_pvarStatus : VARIANT *
//                The "boolVal" element of "o_pvarStatus" contains the 
//				  Status of the PKCS#12 and PKCS#7 import operation.
//				  It contains TRUE if Import() method succeeded, otherwise it contains FALSE.
//    o_pvarErrorCode : VARIANT * 
//				  The "lVal" element of "o_pvarErrorCode" contains the Error Code,
//				  if the "boolVal" element of "o_pvarStatus" is FALSE, otherwise, it's value
//				  is indeterminate.
//    o_pvarErrorCodeString : VARIANT * 
//				  The "bstrVal" element of "o_pvarErrorCode" contains the Error Code String,
//				  if the "boolVal" element of "o_pvarStatus" is FALSE, otherwise, it's value
//				  is indeterminate.
//  Returns
//    NONE
/*****************************************************************************/


STDMETHODIMP CImpPKCS12::Import(VARIANT * i_pvarPKCS12, VARIANT * i_pvarPKCS7, VARIANT * o_pvarStatus, VARIANT * o_pvarErrorCode, VARIANT * o_pvarErrorCodeString)
{
	try
	{
		if ( i_pvarPKCS12->vt != VT_BSTR )
		{
			_ShowErrorMessage(E_UNEXPECTED, "Import : Invalid VARIANT Type for i_pvarPKCS12") ;
			return(E_UNEXPECTED) ;
		}
		if ( i_pvarPKCS7->vt != VT_BSTR )
		{
			_ShowErrorMessage(E_UNEXPECTED, "Import : Invalid VARIANT Type for i_pvarPKCS7") ;
			return(E_UNEXPECTED) ;
		}

		BOOL			bImportStatus = FALSE ;

		((o_pvarStatus))->vt = VT_BOOL ;

		((o_pvarErrorCode))->vt = VT_I4 ;
		((o_pvarErrorCodeString))->vt = VT_BSTR ;

		if ( !m_bMyCertStoreOpen )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertOpenSystemStore falied for MY") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		if ( !m_bCACertStoreOpen )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertOpenSystemStore falied for CA") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
		
		////////////////////////////////////////////////////////////////////////////
		// Obtain the PKCS#7 DER Blob
		////////////////////////////////////////////////////////////////////////////
		LPSTR			szBase64PKCS7 = NULL ;
		BYTE			*pbPKCS7Blob = NULL ;
		DWORD			cbPKCS7Blob = 0 ;

		szBase64PKCS7 = _WideToMultiString(i_pvarPKCS7->bstrVal) ;

		_Base64Decode(szBase64PKCS7,
						strlen(szBase64PKCS7),
						NULL,
						&cbPKCS7Blob) ;

		if ( (pbPKCS7Blob = (BYTE *) malloc(cbPKCS7Blob+1)) == NULL )
		{
			_ShowErrorMessage(E_UNEXPECTED, "Import : Out of memory.") ;
			((o_pvarStatus))->boolVal = FALSE ;
			return(E_UNEXPECTED) ;
		}

		_Base64Decode(szBase64PKCS7, 
					  strlen(szBase64PKCS7),
					  (PCHAR)pbPKCS7Blob,
					  &cbPKCS7Blob) ;

		//::MessageBox( NULL, (LPCTSTR) m_pszContainer, (LPCTSTR) _T(""), MB_OK | MB_ICONINFORMATION );

		////////////////////////////////////////////////////////////////////////////
		// Obtain the PKCS#8 DER Blob
		////////////////////////////////////////////////////////////////////////////
		LPSTR			szBase64PKCS8 = NULL ;
		BYTE			*pbPKCS8Blob = NULL ;
		DWORD			cbPKCS8Blob = 0 ;

		szBase64PKCS8 = _WideToMultiString(i_pvarPKCS12->bstrVal) ;

		CPkcs8					pkcs8(szBase64PKCS8) ;
		CRYPT_PRIVATEKEYBLOB	privateKeyBlob ;

		if ( !pkcs8.generatePRIVATEKEYBLOB(&privateKeyBlob) )
		{
			_ShowErrorMessage(GetLastError(), "Import : Error encountered while generating the PRIVATEKEYBLOB") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		// Use the value obtained through the ProviderName property to decided
		// which provider is to be associated with the keys that are being imported.

		////////////////////////////////////////////////////////////////////////////
		// Generate a HANDLE for a NEW Key Container identified by m_pszContainer
		////////////////////////////////////////////////////////////////////////////
		if ( !CryptAcquireContext(
					   &m_hCryptProv,			// Address for the handle 
					   (LPCTSTR) m_pszContainer,
					   (LPCTSTR) m_szCryptographicProvider, // Use the provider received through the ProviderName property.
					   PROV_RSA_FULL,			// Specifies the provider type
					   CRYPT_NEWKEYSET) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptAcquireContext falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

/*
		// Check if the bit length of the private/public key is 512 or 1024 and based
		// on that, set the Cryptographic Provider appropriately.

		if ( pkcs8.m_MyPrivateKeyBlob.rsapubkey.bitlen <= 512 )
		{
			////////////////////////////////////////////////////////////////////////////
			// Generate a HANDLE for a NEW Key Container identified by m_pszContainer
			////////////////////////////////////////////////////////////////////////////
			if ( !CryptAcquireContext(
						   &m_hCryptProv,			// Address for the handle 
						   (LPCTSTR) m_pszContainer,
						   (LPCTSTR) "Microsoft Base Cryptographic Provider v1.0", // Use the Base provider
						   PROV_RSA_FULL,			// Specifies the provider type
						   CRYPT_NEWKEYSET) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CryptAcquireContext falied") ;
				((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}
		}
		else
		{
			////////////////////////////////////////////////////////////////////////////
			// Generate a HANDLE for a NEW Key Container identified by m_pszContainer
			////////////////////////////////////////////////////////////////////////////
			if ( !CryptAcquireContext(
						   &m_hCryptProv,			// Address for the handle 
						   (LPCTSTR) m_pszContainer,
						   (LPCTSTR) "Microsoft Enhanced Cryptographic Provider v1.0", // Use the Enhanced provider
						   PROV_RSA_FULL,			// Specifies the provider type
						   CRYPT_NEWKEYSET) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CryptAcquireContext falied") ;
				((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}
		}
*/


		////////////////////////////////////////////////////////////////////////////
		// Import the PRIVATEKEYBLOB into the Key Container.
		////////////////////////////////////////////////////////////////////////////

		// The privateKeyBlob doesn't have a REAL PKCS#12. It's assumed to be of the
		// format PRIVATEKEYBLOB, as understood by CryptImportKey.

		HCRYPTKEY	hSignatureKey = NULL ;

		if ( !CryptImportKey(
						m_hCryptProv,
						privateKeyBlob.pbData,
						privateKeyBlob.cbData,
						0,
						(m_bExportable ? CRYPT_EXPORTABLE : 0) | (m_bUserProtected ? CRYPT_USER_PROTECTED : 0),
						&hSignatureKey) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptImportKey falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#if 0
		////////////////////////////////////////////////////////////////////////////
		// Obtain the PKCS#12 DER Blob
		////////////////////////////////////////////////////////////////////////////
		LPSTR			szBase64PKCS12 = NULL ;
		BYTE			*pbPKCS12Blob = NULL ;
		DWORD			cbPKCS12Blob = 0 ;

		szBase64PKCS12 = _WideToMultiString(i_pvarPKCS12->bstrVal) ;

		_Base64Decode(szBase64PKCS12, 
					  strlen(szBase64PKCS12),
					  NULL,
					  &cbPKCS12Blob) ;

		if ( (pbPKCS12Blob = (BYTE *) malloc(cbPKCS12Blob+1)) == NULL )
		{
			_ShowErrorMessage(E_UNEXPECTED, "Import : Out of memory.") ;
			((o_pvarStatus))->boolVal = FALSE ;
			return(E_UNEXPECTED) ;
		}

		_Base64Decode(szBase64PKCS12, 
					  strlen(szBase64PKCS12),
					  (PCHAR)pbPKCS12Blob,
					  &cbPKCS12Blob) ;

		////////////////////////////////////////////////////////////////////////////
		// Import the PRIVATEKEYBLOB into the Key Container.
		////////////////////////////////////////////////////////////////////////////

		// The pbPKCS12Blob doesn't have a REAL PKCS#12 anymore. It's assumed to be of the
		// format PRIVATEKEYBLOB, as understood by CryptImportKey.

		HCRYPTKEY	hSignatureKey = NULL ;

		if ( !CryptImportKey(
						m_hCryptProv,
						pbPKCS12Blob,
						cbPKCS12Blob,
						0,
						(m_bExportable ? CRYPT_EXPORTABLE : 0) | (m_bUserProtected ? CRYPT_USER_PROTECTED : 0),
						&hSignatureKey) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptImportKey falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif

#if 0
		// This code checks if the m_Exportable flag works or not. If m_Exportable is TRUE then the
		// following function succeeds. If m_Exportable is FALSE, then the following function
		// MUST fail.
		BYTE		junk[10000] ;
		DWORD		dwjunk = 10000 ;
		FILE		*fpSignature = NULL ;

		if ( !CryptExportKey(
						hSignatureKey,
						0,
						PRIVATEKEYBLOB,
						0,
						junk,
						&dwjunk) )
		{

			DWORD tmp ;
			tmp = GetLastError() ;
			_ShowErrorMessage(tmp, "Import : CryptImportKey falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif

		////////////////////////////////////////////////////////////////////////////
		// Open a Message Handle that will hold the decoded PKCS#7 message
		////////////////////////////////////////////////////////////////////////////

		HCRYPTMSG			hCryptMsg = NULL ;

		if ( (hCryptMsg = CryptMsgOpenToDecode(
						CRYPT_ASN_ENCODING | PKCS_7_ASN_ENCODING,
						0,
						0,
						0,
						NULL,
						NULL)) == NULL ) 
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptMsgOpenToDecode for falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		////////////////////////////////////////////////////////////////////////////
		// Update the handle with the DER of the PKCS#7
		////////////////////////////////////////////////////////////////////////////
		if ( !CryptMsgUpdate(
						hCryptMsg,
						pbPKCS7Blob,
						cbPKCS7Blob,
						TRUE) )
		{
			DWORD temp ;
			temp = GetLastError() ;
			_ShowErrorMessage(temp, "Import : CryptMsgUpdate for PKCS#7 falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		DWORD		dwNumberOfCerts = 0 ;
		DWORD		dwNumberOfBytes_For_NumberOfCerts = 4 ;

		////////////////////////////////////////////////////////////////////////////
		// Find the number of Certificates in the PKCS#7 message
		////////////////////////////////////////////////////////////////////////////
		if ( !CryptMsgGetParam(
						hCryptMsg,
						CMSG_CERT_COUNT_PARAM,
						0,
						&dwNumberOfCerts,
						&dwNumberOfBytes_For_NumberOfCerts) )
		{
			DWORD temp ;
			temp = GetLastError() ;
			_ShowErrorMessage(temp, "Import : CryptMsgGetParam for PKCS#7 falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}


		// Extract individual certificates (which are in X.509 format) into a 
		// Linked List of Certificate Contexts.
		// ASSUMPTION : The PKCS#7 message is assumed to be such that the FIRST certificate
		//				is the end-entity certificate and all the intermediate CA certificates
		//				are after it.

		DWORD					certIndex ;
		BOOL					fFirstCert = TRUE ;
		PCCERT_CONTEXT			pCertContext = NULL ;
		PCCERT_CONTEXT_LIST		pCertContextList = NULL, pTmpCertContextList = NULL ;

		for ( certIndex = 0 ; certIndex < dwNumberOfCerts ; certIndex++ )
		{
			BYTE		EncodedCertInPKCS7[10000] ;
			DWORD		dwEncodedCertInPKCS7 = 10000 ;

			if ( !CryptMsgGetParam(
							hCryptMsg,
							CMSG_CERT_PARAM ,
							certIndex,
							EncodedCertInPKCS7,
							&dwEncodedCertInPKCS7) )
			{
				DWORD temp ;
				temp = GetLastError() ;
				_ShowErrorMessage(temp, "Import : CryptMsgGetParam for Certificate in PKCS#7 falied") ;
				((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}
			
			if ( (pCertContext = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							EncodedCertInPKCS7, 
							dwEncodedCertInPKCS7)) == NULL )
			{
				DWORD temp ;
				temp = GetLastError() ;
				_ShowErrorMessage(temp, "Import : CertCreateCertificateContext falied") ;
				((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}

			if ( fFirstCert )
			{
				pCertContextList = (PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)) ;
				pTmpCertContextList = pCertContextList ;
				pCertContextList->pCertContext = pCertContext ; 
				pCertContextList->nextCertContext = NULL ;
				fFirstCert = FALSE ;
			}
			else
			{
				pTmpCertContextList->nextCertContext = (PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)) ;
				pTmpCertContextList = pTmpCertContextList->nextCertContext ;
				pTmpCertContextList->pCertContext = pCertContext ;
				pTmpCertContextList->nextCertContext = NULL ;
			}
		}

		////////////////////////////////////////////////////////////////////////////
		// Add the Certificate Context of the end-entity certificate into MY Certificate Store
		////////////////////////////////////////////////////////////////////////////

		pCertContext = pCertContextList->pCertContext ; // This points to the FIRST certificate in the PKCS#7.
														// This is assumed to be the end-entity certificate.

		if ( !CertAddCertificateContextToStore(
						m_hMyCertStore,
						pCertContext,
						CERT_STORE_ADD_REPLACE_EXISTING,
						&pCertContext) ) 
		{
			_ShowErrorMessage(GetLastError(), "Import : CertAddCertificateContextToStore falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		// VIMP NOTE : The 4th param to CertAddCertificateContextToStore MUST be &pCertContext,
		// otherwise the subsequent CertSetCertificateContextProperty() does not update the
		// right certificate context !!!!

		////////////////////////////////////////////////////////////////////////////
		// Associate the Newly added end-entity Certificate with the NEW Key Container
		// and set it's properties.
		////////////////////////////////////////////////////////////////////////////
		CRYPT_KEY_PROV_INFO CryptKeyProvInfo ;

		CryptKeyProvInfo.pwszContainerName = _MultiToWideString((char *)m_pszContainer) ;

		// Use the value of the ProviderName property to specify what CSP is to be associated
		// with the certificate.

		CryptKeyProvInfo.pwszProvName = _MultiToWideString(m_szCryptographicProvider) ;
/*
		// Check if the bit length of the private/public key is 512 or 1024 and based
		// on that, set the Cryptographic Provider appropriately.

		if ( pkcs8.m_MyPrivateKeyBlob.rsapubkey.bitlen <= 512 )
			CryptKeyProvInfo.pwszProvName = MS_DEF_PROV_W ;
		else
			CryptKeyProvInfo.pwszProvName = MS_ENHANCED_PROV_W ;
*/
		CryptKeyProvInfo.dwProvType = PROV_RSA_FULL ;
		CryptKeyProvInfo.dwFlags = 0 ;
		CryptKeyProvInfo.cProvParam = 0 ;
		CryptKeyProvInfo.rgProvParam = NULL ;
		CryptKeyProvInfo.dwKeySpec = AT_KEYEXCHANGE ;

		if ( !CertSetCertificateContextProperty(
						pCertContext,
						CERT_KEY_PROV_INFO_PROP_ID,
						0,
						&CryptKeyProvInfo) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertSetCertificateContextProperty falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		if ( !CryptSetKeyParam (
						hSignatureKey,
						KP_CERTIFICATE,
						(PBYTE)pCertContext->pbCertEncoded,
						0))
		{
			m_dwErrorCode = GetLastError() ;
			// If the KP_CERTIFICATE flag is not supported by CSP, then ignore it.
			// However, if there is any other error, catch it here.
			// This check is needed because MSFT CSPs don't support this flag.
			if ( m_dwErrorCode != NTE_BAD_TYPE && m_dwErrorCode != NTE_BAD_FLAGS ) 
			{
				_ShowErrorMessage(m_dwErrorCode, "Import : CryptSetKeyParam falied") ;
					((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}
			else
				m_dwErrorCode = 0x00000000 ;
		}

#if 0
		CERT_KEY_CONTEXT	CertKeyContext ;

		CertKeyContext.cbSize = sizeof(CERT_KEY_CONTEXT) ;
		CertKeyContext.hCryptProv = m_hCryptProv ;
		CertKeyContext.dwKeySpec = AT_KEYEXCHANGE ;

		if ( !CertSetCertificateContextProperty(
						pCertContext,
						CERT_KEY_SPEC_PROP_ID,
						0,
						&CertKeyContext) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertSetCertificateContextProperty falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif

#if 0
		// This code set the Enhanced Key Usage property of the certificate 
		BYTE				tmp[1024] ;
		CRYPT_DATA_BLOB		EnhancedKeyUsage ;

		tmp[0] = 0x30 ;
		tmp[1] = 20 ;
			tmp[2] = 0x06 ;
			tmp[3] = 0x08 ;
				tmp[4] = 0x2B ;
				tmp[5] = 0x06 ;
				tmp[6] = 0x01 ;
				tmp[7] = 0x05 ;
				tmp[8] = 0x05 ;
				tmp[9] = 0x07 ;
				tmp[10] = 0x03 ;
				tmp[11] = 0x04 ;
			tmp[12] = 0x06 ;
			tmp[13] = 0x08 ;
				tmp[14] = 0x2B ;
				tmp[15] = 0x06 ;
				tmp[16] = 0x01 ;
				tmp[17] = 0x05 ;
				tmp[18] = 0x05 ;
				tmp[19] = 0x07 ;
				tmp[20] = 0x03 ;
				tmp[21] = 0x02 ;

		EnhancedKeyUsage.cbData = 22 ;
		EnhancedKeyUsage.pbData = (BYTE *) tmp ;

		if ( !CertSetCertificateContextProperty(
						pCertContext,
						CERT_ENHKEY_USAGE_PROP_ID,
						0,
						&EnhancedKeyUsage) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertSetCertificateContextProperty falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif
		PCERT_CONTEXT	pCertContext_EndEntity = NULL ;

		pCertContext_EndEntity = (PCERT_CONTEXT) pCertContext ;


		// _DumpAllCertProperties() ;
		
		////////////////////////////////////////////////////////////////////////////
		// Add CA Certificates into the CA cert store
		////////////////////////////////////////////////////////////////////////////

		pTmpCertContextList = pCertContextList->nextCertContext ;

		for ( certIndex = 0 ; certIndex < dwNumberOfCerts-1 ; certIndex++ )
		{
			pCertContext = pTmpCertContextList->pCertContext ;
			if ( !CertAddCertificateContextToStore(
							m_hCACertStore,
							pCertContext,
							//CERT_STORE_ADD_REPLACE_EXISTING,
							CERT_STORE_ADD_NEW,
							NULL) ) 
			{
				DWORD	dwErrorNumber = GetLastError() ;
				if ( dwErrorNumber != CRYPT_E_EXISTS )
				{					
					_ShowErrorMessage(dwErrorNumber, "Import : CertAddCertificateContextToStore falied for CA Certificate") ;
					((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
					return S_OK ;
				}
			}

			pTmpCertContextList = pTmpCertContextList->nextCertContext ;
		}

		PCERT_CONTEXT	pCertContext_CA = NULL ;

		pCertContext_CA = (PCERT_CONTEXT) pCertContext ;

#if 0
		// This call can be used to verify the digital signature on the end-entity certificate.
		if ( !CryptVerifyCertificateSignature(
						m_hCryptProv,
						X509_ASN_ENCODING,
						pCertContext_EndEntity->pbCertEncoded,
						pCertContext_EndEntity->cbCertEncoded,
						&(pCertContext_CA->pCertInfo->SubjectPublicKeyInfo)) )
		{
			DWORD	tmp ;
			tmp = GetLastError() ;
			_ShowErrorMessage(tmp, "Import : CryptVerifyCertificateSignature falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif


#if 0

		// THIS	COMMENTED PIECE OF CODE IS TO BE USED WHEN THE LAST CERTIFICATE INTHE PKCS#7 CHAIN IS
		// THE END-ENTITY CERTIFICATE AND ALL PREVIOUS CERTS ARE INTERMEDIATE CA CERTIFICATES.

		// pCertContext at this stage has Certificate Context of the end-entity certificate. This 
		// is because, the PKCS#7 is generated in a way such that the top level certificate is
		// placed first and the end-entity certificate is place last.
		// IF THIS IS CHANGES in the PKCS#7, then you have to pick the first cert and assume it as
		// being the end-entity cert.

		////////////////////////////////////////////////////////////////////////////
		// Add the Certificate Context of the end-entity certificate into MY Certificate Store
		////////////////////////////////////////////////////////////////////////////

		if ( !CertAddCertificateContextToStore(
						m_hMyCertStore,
						pCertContext,
						CERT_STORE_ADD_REPLACE_EXISTING,
						&pCertContext) ) 
		{
			_ShowErrorMessage(GetLastError(), "Import : CertAddCertificateContextToStore falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		// VIMP NOTE : The 4th param to CertAddCertificateContextToStore MUST be &pCertContext,
		// otherwise the subsequent CertSetCertificateContextProperty() does not update the
		// right certificate context !!!!

		////////////////////////////////////////////////////////////////////////////
		// Associate the Newly added end-entity Certificate with the NEW Key Container
		// and set it's properties.
		////////////////////////////////////////////////////////////////////////////
		CRYPT_KEY_PROV_INFO CryptKeyProvInfo ;

		CryptKeyProvInfo.pwszContainerName = _MultiToWideString((char *)m_pszContainer) ;
		CryptKeyProvInfo.pwszProvName = MS_ENHANCED_PROV_W ;
		CryptKeyProvInfo.dwProvType = PROV_RSA_FULL ;
		CryptKeyProvInfo.dwFlags = 0 ;
		CryptKeyProvInfo.cProvParam = 0 ;
		CryptKeyProvInfo.rgProvParam = NULL ;
		CryptKeyProvInfo.dwKeySpec = AT_KEYEXCHANGE ;

		if ( !CertSetCertificateContextProperty(
						pCertContext,
						CERT_KEY_PROV_INFO_PROP_ID,
						0,
						&CryptKeyProvInfo) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertSetCertificateContextProperty falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		////////////////////////////////////////////////////////////////////////////
		// Add CA Certificates into the CA cert store
		////////////////////////////////////////////////////////////////////////////
		pTmpCertContextList = pCertContextList ;

		for ( certIndex = 0 ; certIndex < dwNumberOfCerts-1 ; certIndex++ )
		{
			pCertContext = pTmpCertContextList->pCertContext ;
			if ( !CertAddCertificateContextToStore(
							m_hCACertStore,
							pCertContext,
							CERT_STORE_ADD_REPLACE_EXISTING,
							NULL) ) 
			{
				_ShowErrorMessage(GetLastError(), "Import : CertAddCertificateContextToStore falied for CA Certificate") ;
				((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
				return S_OK ;
			}

			pTmpCertContextList = pTmpCertContextList->nextCertContext ;
		}
#endif



#if 0
		CryptKeyProvInfo.dwKeySpec = AT_SIGNATURE ;

		if ( !CertSetCertificateContextProperty(
						pCertContext,
						CERT_KEY_PROV_INFO_PROP_ID,
						0,
						&CryptKeyProvInfo) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CertSetCertificateContextProperty falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif






#if 0
		strcpy((char *)m_pszContainer, "1f9b52a4-7a7a-11d2-830c-0060b0b32e16") ;

		if ( !CryptAcquireContext(
					   &m_hCryptProv,			// Address for the handle 
					   (LPCTSTR) m_pszContainer,
					   (LPCTSTR) "Microsoft Enhanced Cryptographic Provider v1.0", // Use the Enhanced provider
					   PROV_RSA_FULL,			// Specifies the provider type
					   0) )		// Zero allows access to private keys
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptAcquireContext falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		CHAR		szKeyContainerName[100] ;
		DWORD		dwKeyContainerName = 100, i = 0 ;

		if ( !CryptGetProvParam(
						m_hCryptProv,
						PP_CONTAINER,
						(BYTE *)szKeyContainerName,
						&dwKeyContainerName,
						0) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptGetProvParam falied") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

#if 0
		// Handle Signature Key Pairs
		HCRYPTKEY hSignatureKey ;

		if ( !CryptGetUserKey(
						m_hCryptProv,
						AT_SIGNATURE,
						&hSignatureKey) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptGetUserKey falied for AT_SIGNATURE") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		BYTE		pSignatureKeyBlob_private[10000] ;
		DWORD		dwSignatureKeyBlob_private = 10000 ;
		FILE		*fpSignature = NULL ;

		if ( !CryptExportKey(
						hSignatureKey,
						0,
						PRIVATEKEYBLOB,
						0,
						pSignatureKeyBlob_private,
						&dwSignatureKeyBlob_private) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptExportKey falied for AT_SIGNATURE : PrivateKeyBlob") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		if ( (fpSignature = fopen("e:\\temp\\signature.pvk", "wb")) == NULL )
		{
			_ShowErrorMessage(GetLastError(), "Import : Unable to open signature.pvk file") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		fwrite(pSignatureKeyBlob_private, 1, dwSignatureKeyBlob_private, fpSignature) ;

		fclose(fpSignature) ;

		if ( (fpSignature = fopen("e:\\temp\\signature.pvk.dump", "w")) == NULL )
		{
			_ShowErrorMessage(GetLastError(), "Import : Unable to open signature.pvk.dump file") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		for ( i = 0 ; i < dwSignatureKeyBlob_private ; i++ )
		{
			if ( (i % 16) == 0 )
				fprintf(fpSignature, "\n") ;
			fprintf(fpSignature, "0x%02x :", pSignatureKeyBlob_private[i]) ;
		}
		fclose(fpSignature) ;
#endif

		// Handle Exchange Key pairs.
		HCRYPTKEY hExchangeKey ;

		if ( !CryptGetUserKey(
						m_hCryptProv,
						AT_KEYEXCHANGE,
						&hExchangeKey) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptGetUserKey falied for AT_KEYEXCHANGE") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		BYTE		pExchangeKeyBlob_private[10000] ;
		DWORD		dwExchangeKeyBlob_private = 10000 ;

		if ( !CryptExportKey(
						hExchangeKey,
						0,
						PRIVATEKEYBLOB,
						0,
						pExchangeKeyBlob_private,
						&dwExchangeKeyBlob_private) )
		{
			_ShowErrorMessage(GetLastError(), "Import : CryptExportKey falied for AT_KEYEXCHANGE : PrivateKeyBlob") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		FILE *fpExchange ; 

		if ( (fpExchange = fopen("e:\\temp\\exchange.pvk", "wb")) == NULL )
		{
			_ShowErrorMessage(GetLastError(), "Import : Unable to open exchange.pvk file") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		fwrite(pExchangeKeyBlob_private, 1, dwExchangeKeyBlob_private, fpExchange) ;

		fclose(fpExchange) ;

		if ( (fpExchange = fopen("e:\\temp\\exchange.pvk.dump", "w")) == NULL )
		{
			_ShowErrorMessage(GetLastError(), "Import : Unable to open exchange.pvk.dump file") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}

		for ( i = 0 ; i < dwExchangeKeyBlob_private ; i++ )
		{
			if ( (i % 16) == 0 )
				fprintf(fpExchange, "\n") ;
			fprintf(fpExchange, "0x%02x :", pExchangeKeyBlob_private[i]) ;
		}
		fclose(fpExchange) ;


		PMY_PRIVATEKEYBLOB		pMySignatureKeyBlob_private ;
		PMY_PRIVATEKEYBLOB		pMyExchangeKeyBlob_private ;

		// pMySignatureKeyBlob_private = (PMY_PRIVATEKEYBLOB) pSignatureKeyBlob_private ;
		pMyExchangeKeyBlob_private = (PMY_PRIVATEKEYBLOB) pExchangeKeyBlob_private ;
#endif

#if 0
		CRYPT_PKCS12_BLOB	pkcs12Blob ;

		pkcs12Blob.cbData = cbPKCS12Blob ;
		pkcs12Blob.pbData = pbPKCS12Blob ;

		PFX		pfx ;

		if ( !_myCryptDecodeObject(szOID_PKCS12, (PCRYPT_MYDER_BLOB)&pkcs12Blob, (PBYTE) &pfx) )
		{
			_ShowErrorMessage(GetLastError(), "Import : Invalid PFX PDU") ;
			((o_pvarStatus))->boolVal = FALSE ;((o_pvarErrorCode))->lVal = m_dwErrorCode ; ((o_pvarErrorCodeString))->bstrVal = m_bstrErrorCodeString ;
			return S_OK ;
		}
#endif

		((o_pvarStatus))->boolVal = TRUE ;

		((o_pvarErrorCode))->lVal = 0x00000000 ;
		((o_pvarErrorCodeString))->bstrVal = _MultiToWideString((char *)"") ;

		if ( !szBase64PKCS8)
			free(szBase64PKCS8) ;

		return S_OK ;
	}
	catch (...)
	{
		_ShowErrorMessage(E_UNEXPECTED, "Import : CATCH") ;
		return(E_UNEXPECTED) ;
	}
}
 

/*****************************************************************************/
// _ShowErrorMessage :This function shows a message box that displays the error 
//					message corresponding to the errorcode passed to it.
//
// Input :
//	 errorCode : DWORD
//					The error code whose corresponding Error Message is to be shown.
//   szExtraString : LPSTR
//					This string is appended to the Error Message string that corresponds
//					to the error code.
// Output :
//	 NONE
// Returns :
//	 NONE 
/*****************************************************************************/

void CImpPKCS12::_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString)
{
	LPVOID		ErrorMessage ;

	FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			(LPCVOID) NULL,
			errorCode,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &ErrorMessage,
			0,
			NULL) ;

	// Display the string.
	CHAR	temp[1024], temp2[1024] ;
	sprintf(temp, "CImpPKCS12::%s", szExtraString) ;
	sprintf(temp2, "%sError Code : 0x%08x", ErrorMessage, errorCode) ;

#ifdef _DEBUG
	::MessageBox( NULL, (LPCTSTR) temp2, (LPCTSTR) _T(temp), MB_OK | MB_ICONINFORMATION );
#endif

	// Copy Error Information in the 
	m_dwErrorCode = errorCode ;
	m_bstrErrorCodeString = _MultiToWideString((char *)ErrorMessage) ;

	LocalFree( ErrorMessage ) ;
}

/*****************************************************************************/
// _Base64Encode() : Encodes a message in Base64 format. The encoded output contains
//				    a CR-LF sequence after every 76 encoded bytes.
//
//				    Implements RFC 1521 - 5.2 Base64 Content-Transfer Encoding.
//
//  Input :
//	  pInput : PCHAR
//                Contains the input message that is the be encoded.
//	  dwInputSize : DWORD
//				  Specifies the size of the input message.
//  Input/Output :
//	  pOutput : PCHAR
//                Specifies the address where the encoded message is to be copied.
//
//				  If it is specified as NULL, then the output formal parameter, dwOutputSize,
//				  specifies the size of the encoded message, corresponding to the 
//				  input message specified through the formal parameter pInput.
//  Input/Output :
//	  dwOutputSize : DWORD *
//				  Specifies the size of the output encoded message.
//  Returns :
//    NONE
/*****************************************************************************/

void CImpPKCS12::_Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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
				outputPtr[0] = '\n' ;
				outputPtr[1] = '\r' ;
				outputPtr += 2 ;
			}
		}
	}
}

BOOL	_decode(short input, DWORD *output)
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

/*****************************************************************************/
// _Base64Decode() : Decodes a message that is in Base64 format. 
//
//				    Implements RFC 1521 - 5.2 Base64 Content-Transfer Decoding.
//
//  Input :
//	  pInput : PCHAR
//                Contains the input message that is the be decoded.
//	  dwInputSize : DWORD
//				  Specifies the size of the input message.
//  Input/Output :
//	  pOutput : PCHAR
//                Specifies the address where the decoded message is to be copied.
//
//				  If it is specified as NULL, then the output formal parameter, dwOutputSize,
//				  specifies the size of the decoded message, corresponding to the 
//				  input message specified through the formal parameter pInput.
//  Input/Output :
//	  dwOutputSize : DWORD *
//				  Specifies the size of the output decoded message.
//  Returns :
//    NONE
/*****************************************************************************/

void CImpPKCS12::_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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

		free(filteredInputPtr) ;
	}
}

/*****************************************************************************/
// _WideToMultiString() : Converts a Wide Character String to Multi Byte String.
//
//  Input :
//	  szwcInputString : BSTR
//                Contains the Wide Character string
//  Output :
//	  NONE
//  Returns : LPSTR
//				  Returns the Multi Byte String representation of the
//				  input Wide Character String.
/*****************************************************************************/

LPSTR CImpPKCS12::_WideToMultiString(BSTR szwcInputString)
{
	LPSTR	szmbOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szwcInputString == NULL)
		return NULL ;

	// Obtain the size of the Multi Byte string representing szwcInputString.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								NULL,
								0,
								NULL,
								NULL) ;

	// Allocate memory for the Multi Byte String.
	if ( (szmbOutputString = (LPSTR)malloc(dwSize)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "_WideToMultiString : Out of memory") ;
		return(NULL) ;
	}

	// Copy from a Wide Char string to Multi Byte string.
	dwSize = WideCharToMultiByte(CP_ACP,
								WC_COMPOSITECHECK | WC_DEFAULTCHAR,
								szwcInputString,
								-1,
								szmbOutputString,
								dwSize,
								NULL,
								NULL) ;
	if (!dwSize)
	{
		_ShowErrorMessage(GetLastError(), "_WideToMultiString : Unable to convert from Wide Char string to Multi Byte string") ;
		return(NULL) ;
	}

	return szmbOutputString ;
}


/*****************************************************************************/
// _MultiToWideString() : Converts a Multi Byte String to Wide Character String.
//
//  Input :
//	  szInputString : LPSTR
//                Contains the Multi Byte string
//  Output :
//	  NONE
//  Returns : BSTR
//				  Returns the Wide Character String representation of the
//				  input Multi Byte String.
/*****************************************************************************/

BSTR CImpPKCS12::_MultiToWideString(LPSTR szInputString)
{
	BSTR	szwcOutputString = NULL ;
	DWORD	dwSize = 0 ;

	if (szInputString == NULL)
		return NULL ;

	// Obtain size of the wide char UNICODE string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								NULL,
								0) ;

	// Allocate memory for the BSTR (UNICODE string).
	if ( (szwcOutputString = SysAllocStringLen(NULL, dwSize)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "_MultiToWideString : Out of memory") ;
		return(NULL) ;
	}

	// Copy from (and convert) Multi Byte string to Wide Char string.
	dwSize = MultiByteToWideChar(CP_ACP, 
								MB_COMPOSITE, 
								szInputString, 
								-1,
								szwcOutputString,
								dwSize) ;
	if (!dwSize)
	{
		_ShowErrorMessage(GetLastError(), "_MultiToWideString : Unable to convert from Multi Byte string to Wide Char string") ;
		return(NULL) ;
	}

	return szwcOutputString ;
}


BOOL	CImpPKCS12::_GetASNInfo(PBYTE input, BYTE *type, DWORD *length, DWORD *numberOfLengthBytes)
{
	BOOL	retVal = FALSE ;

	*type = INVALID_ASN_TYPE ;

	switch ( input[0] )
	{
		case SEQUENCE :
			*type = SEQUENCE ;

			if ( input[1] & 0x80 )
			{
				int		i, numberOfBytes ;
				DWORD	tmplength ;

				numberOfBytes = input[1] & 0x7F ;

				*length = 0 ;
				for ( i = 0 ; i < numberOfBytes ; i++ )
				{
					tmplength = 0 ;
					tmplength = input[(2+numberOfBytes-1)-i] ;
					tmplength <<= (i*8) ;
					*length |= tmplength ;
				}
				*numberOfLengthBytes = numberOfBytes ;
			}
			else
			{
				*length = input[1] ;
				*numberOfLengthBytes = 0 ;
			}
			retVal = TRUE ;
			break ;

		case UNIVERSAL_INTEGER :
			*type = UNIVERSAL_INTEGER ;
			*length = input[1] ;
			retVal = TRUE ;
			break ;

		default :
			_ShowErrorMessage(E_UNEXPECTED, "_GetASNInfo : Invalid ASN type") ;
			retVal = FALSE ;
			break ;
	}
	return retVal ;
}

BOOL	CImpPKCS12::_myCryptDecodeObject(LPSTR szOID, PCRYPT_MYDER_BLOB pMyDERBlob, PBYTE pOutputStruct)
{
	BOOL	bRetVal = FALSE ;

	if ( strcmp(szOID, szOID_PKCS12) == 0 )
	{
		PPFX		pPFX = NULL ;
		BYTE		ASNtype ;
		DWORD		nolb = 0, dwDEROffset = 0, dwTMP = 0 ;

		pPFX = (PPFX) pOutputStruct ;

		// Check for a SEQUENCE for PFX itself
		if ( !_GetASNInfo(pMyDERBlob->pbData, &ASNtype, &(pPFX->dwPFXDERlength), &nolb) )
		{
			return FALSE ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid PFX PDU") ;
			return FALSE ;
		}

		dwDEROffset = 2 + nolb ;

		// Check for "Version" (UNIVERSAL INTEGER) inside the PFX
		if ( !_GetASNInfo(pMyDERBlob->pbData + dwDEROffset, &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != UNIVERSAL_INTEGER )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid Version inside PFX PDU") ;
			return FALSE ;
		}

		dwDEROffset += 2 + dwTMP - 1 ;
		pPFX->version = pMyDERBlob->pbData[dwDEROffset] ;
		dwDEROffset++ ;

		pPFX->authSafe.pbData = (PBYTE) (pMyDERBlob->pbData + dwDEROffset) ;

		// Check for "ContentInfo" (SEQUENCE) inside the PFX
		if ( !_GetASNInfo((PBYTE)(pPFX->authSafe.pbData), &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid ContenInfo inside PFX PDU") ;
			return FALSE ;
		}

		pPFX->authSafe.cbData = dwTMP ;

		dwDEROffset += 2 + nolb + dwTMP ;

		pPFX->macData.pbData = (PBYTE) (pMyDERBlob->pbData + dwDEROffset) ;

		// Check for "MacData" (SEQUENCE) inside the PFX
		if ( !_GetASNInfo((PBYTE)(pPFX->macData.pbData), &ASNtype, &dwTMP, &nolb) )
		{
			return (E_UNEXPECTED) ;
		}
		if ( ASNtype != SEQUENCE )
		{
			_ShowErrorMessage(GetLastError(), "_myCryptDecodeObject : Invalid MacData inside PFX PDU") ;
			return FALSE ;
		}
		pPFX->macData.cbData = dwTMP ;

		bRetVal = TRUE ;
	}
	else
	{
		_ShowErrorMessage(E_UNEXPECTED, "_myCryptDecodeObject : Invalid szOID") ;
		bRetVal = FALSE ;
	}

	return bRetVal ;
}

STDMETHODIMP CImpPKCS12::get_KeyExportable(BOOL * pVal)
{
	*pVal = m_bExportable ? TRUE : FALSE ;

	return S_OK;
}

STDMETHODIMP CImpPKCS12::put_KeyExportable(BOOL newVal)
{
	m_bExportable = newVal ? TRUE : FALSE ;

	return S_OK;
}

/*****************************************************************************/
// _EnumCerts() : Returns a linked list of all the certificates present in the
//               system cert store.
//  Input :
//	  hCertSore : HCERTSTORE
//                Contains the handle to the system cert store.
//  Output :
//    NONE
//  Returns :
//    PCCERT_CONTEXT_LIST :
//              : Returns a structure of type PCCERT_CONTEXT_LIST that contains
//                the certificate context of all the centificates present in
//                the certificate store. If no certs are present in system cert
//                store, then a NULL is returned.
/*****************************************************************************/

PCCERT_CONTEXT_LIST CImpPKCS12::_EnumCerts(HCERTSTORE hCertStore)
{
    PCCERT_CONTEXT    pPrevCertContext = NULL;
    PCCERT_CONTEXT    pCertContext = NULL;
    BOOL              fTestFlag = FALSE, fFirstCert = TRUE;
	PCCERT_CONTEXT_LIST pCertContextList = NULL, pTmpCertContextList = NULL;

	while(TRUE)
    {
        pCertContext = CertEnumCertificatesInStore(
                       hCertStore,
                       pPrevCertContext);

        if(!pCertContext)
        {
            break;
        }
        else
        {
 			if ( fFirstCert )
			{
				if ( (pCertContextList = (PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)))
																	== NULL )
				{
					::MessageBox(NULL, TEXT("CCryptOperation::_EnumCerts : Error Allocating Memory"), TEXT("CryptOperation"), MB_OK);
					fTestFlag = FALSE;
					break;
				}
				pTmpCertContextList = pCertContextList ;
				pCertContextList->pCertContext = pCertContext ; 
				pCertContextList->nextCertContext = NULL ;
				fFirstCert = FALSE ;
				fTestFlag = TRUE;

			}
			else
			{
				if ( (pTmpCertContextList->nextCertContext = 
										(PCCERT_CONTEXT_LIST) malloc(sizeof(CCERT_CONTEXT_LIST)))
										== NULL )
				{
					::MessageBox(NULL, TEXT("CCryptOperation::_EnumCerts : Error Allocating Memory"), TEXT("CryptOperation"), MB_OK);
					fTestFlag = FALSE;
					break;
				}
				pTmpCertContextList = pTmpCertContextList->nextCertContext ;
				pTmpCertContextList->pCertContext = pCertContext ;
				pTmpCertContextList->nextCertContext = NULL ;
				fTestFlag = TRUE;
			}
        }

        pPrevCertContext = pCertContext;    
    }

    if(FALSE == fTestFlag)
    {
		::MessageBox(NULL, TEXT("CCryptOperation::_EnumCerts : System Certs Not Found"), TEXT("CryptOperation"), MB_OK);
        return NULL;
    }
	else
        return (pCertContextList);
}

void	CImpPKCS12::_DumpAllCertProperties()
{

		PCCERT_CONTEXT_LIST pAllCertContextList = NULL, pTmpCertContextList = NULL ;
		FILE		*fpcertprops = NULL ;
		BYTE		pbData[1024] ;
		DWORD		cbData = 1024 ;
		DWORD		i = 0 ;
		PCERT_CONTEXT	pCertContext = NULL ;

		pAllCertContextList = _EnumCerts(m_hMyCertStore) ;

		fpcertprops = fopen("e:\\temp\\certprops", "wb") ;

		pTmpCertContextList = pAllCertContextList ;
		while(pTmpCertContextList)
		{
			fprintf(fpcertprops, "\n\n") ;

			pCertContext = (PCERT_CONTEXT) pTmpCertContextList->pCertContext ;

			// Get CERT_KEY_PROV_HANDLE_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_KEY_PROV_HANDLE_PROP_ID,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_KEY_PROV_HANDLE_PROP_ID : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_KEY_PROV_HANDLE_PROP_ID : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			// Get CERT_KEY_PROV_INFO_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_KEY_PROV_INFO_PROP_ID,
							pbData,
							&cbData) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_KEY_PROV_INFO_PROP_ID : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_KEY_PROV_INFO_PROP_ID : \n") ;
				PCRYPT_KEY_PROV_INFO pCryptKeyProvInfo = NULL ;

				pCryptKeyProvInfo = (PCRYPT_KEY_PROV_INFO) pbData ;
				fprintf(fpcertprops, "  pwszContainerName : %s\n", _WideToMultiString(pCryptKeyProvInfo->pwszContainerName)) ;
				fprintf(fpcertprops, "  pwszProvName : %s\n", _WideToMultiString(pCryptKeyProvInfo->pwszProvName)) ;
				fprintf(fpcertprops, "  dwProvType : 0x%08x\n", pCryptKeyProvInfo->dwProvType) ;
				fprintf(fpcertprops, "  dwFlags : 0x%08x\n", pCryptKeyProvInfo->dwFlags) ;
				fprintf(fpcertprops, "  cProvParam : 0x%08x\n", pCryptKeyProvInfo->cProvParam) ;

				DWORD j ;
				PCRYPT_KEY_PROV_PARAM pCryptKeyProvParam = NULL ;

				pCryptKeyProvParam = pCryptKeyProvInfo->rgProvParam ;

				for ( j = 0 ; j < pCryptKeyProvInfo->cProvParam  ; j++ )
				{
					fprintf(fpcertprops, "    rgProvParam[%d].dwParam : 0x%08x\n", j, pCryptKeyProvParam->dwParam) ;

					DWORD k = 0 ; 
					fprintf(fpcertprops, "    rgProvParam[%d].pbData :\n", j) ;
					for ( k = 0 ; k < pCryptKeyProvParam->cbData ; k++ )
						fprintf(fpcertprops, "      0x%08x ", (BYTE)pCryptKeyProvParam->pbData[k]) ;
					fprintf(fpcertprops, "\n") ;

					fprintf(fpcertprops, "    rgProvParam[%d].dwFlags : 0x%08x\n", j, pCryptKeyProvParam->dwFlags) ;

					pCryptKeyProvParam++ ;
				}

				fprintf(fpcertprops, "  dwKeySpec : 0x%08x\n", pCryptKeyProvInfo->dwKeySpec) ;
			}

			cbData = 1024 ;
			// Get CERT_SHA1_HASH_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_SHA1_HASH_PROP_ID ,
							pbData,
							&cbData) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_SHA1_HASH_PROP_ID  : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_SHA1_HASH_PROP_ID : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
				{
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
					if ( (i % 16) == 15 )
						fprintf(fpcertprops, "\n  ") ;
				}
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			// Get CERT_MD5_HASH_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_MD5_HASH_PROP_ID ,
							pbData,
							&cbData) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_MD5_HASH_PROP_ID  : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_MD5_HASH_PROP_ID : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
				{
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
					if ( (i % 16) == 15 )
						fprintf(fpcertprops, "\n  ") ;
				}
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			// Get CERT_KEY_CONTEXT_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_KEY_CONTEXT_PROP_ID ,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_KEY_CONTEXT_PROP_ID  : Property not found \n") ;
			}
			else
			{
				PCERT_KEY_CONTEXT	pCertKeyContext = NULL ;
				pCertKeyContext = (PCERT_KEY_CONTEXT) pbData ;

				fprintf(fpcertprops, "CERT_KEY_CONTEXT_PROP_ID : \n") ;
				fprintf(fpcertprops, "  cbSize : 0x%08x\n", pCertKeyContext->cbSize) ;
				fprintf(fpcertprops, "  hCryptProv : 0x%08x\n", (DWORD) pCertKeyContext->hCryptProv) ;
				fprintf(fpcertprops, "  dwKeySpec : 0x%08x\n", pCertKeyContext->dwKeySpec) ;
			}

			cbData = 1024 ;
			// Get CERT_KEY_SPEC_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_KEY_SPEC_PROP_ID ,
							pbData,
							&cbData) )
			{
				_ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_KEY_SPEC_PROP_ID  : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_KEY_SPEC_PROP_ID : \n") ;
				fprintf(fpcertprops, "  dwKeySpec : 0x%08x\n", *((DWORD *)(pbData))) ;
			}

			cbData = 1024 ;
			// Get CERT_ENHKEY_USAGE_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_ENHKEY_USAGE_PROP_ID,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_ENHKEY_USAGE_PROP_ID : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_ENHKEY_USAGE_PROP_ID : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
				{
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
					if ( (i % 16) == 15 )
						fprintf(fpcertprops, "\n  ") ;
				}
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			// Get CERT_CTL_USAGE_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_CTL_USAGE_PROP_ID,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_CTL_USAGE_PROP_ID : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_CTL_USAGE_PROP_ID : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
				{
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
					if ( (i % 16) == 15 )
						fprintf(fpcertprops, "\n  ") ;
				}
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			// Get CERT_FRIENDLY_NAME_PROP_ID property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_FRIENDLY_NAME_PROP_ID ,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_FRIENDLY_NAME_PROP_ID  : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_FRIENDLY_NAME_PROP_ID : \n") ;
				fprintf(fpcertprops, "  %s\n", _WideToMultiString((BSTR)pbData)) ;
			}

			cbData = 1024 ;
			// Get CERT_FIRST_USER_PROP_ID  property
			if ( !CertGetCertificateContextProperty(
							pCertContext,
							CERT_FIRST_USER_PROP_ID  ,
							pbData,
							&cbData) )
			{
				// _ShowErrorMessage(GetLastError(), "Import : CertGetCertificateContextProperty falied for CA Certificate") ;
				fprintf(fpcertprops, "CERT_FIRST_USER_PROP_ID   : Property not found \n") ;
			}
			else
			{
				fprintf(fpcertprops, "CERT_FIRST_USER_PROP_ID  : \n") ;
				fprintf(fpcertprops, "  ") ;
				for ( i = 0 ; i < cbData ; i++ )
				{
					fprintf(fpcertprops, "0x%02x ", (BYTE)pbData[i]) ;
					if ( (i % 16) == 15 )
						fprintf(fpcertprops, "\n  ") ;
				}
				fprintf(fpcertprops, "\n") ;
			}

			cbData = 1024 ;
			pTmpCertContextList = pTmpCertContextList->nextCertContext ;

		}

		fclose(fpcertprops) ;
}



STDMETHODIMP CImpPKCS12::get_ProviderName(BSTR *pVal)
{
	BSTR		bstrRetVal = _MultiToWideString(m_szCryptographicProvider) ;
	
	*pVal = bstrRetVal ;

	return S_OK ;
}

STDMETHODIMP CImpPKCS12::put_ProviderName(BSTR newVal)
{
	if (m_szCryptographicProvider)
		free (m_szCryptographicProvider) ;

	m_szCryptographicProvider = _WideToMultiString(newVal) ;
	return S_OK ;
}

STDMETHODIMP CImpPKCS12::get_KeyUserProtected(BOOL *pVal)
{
	*pVal = m_bUserProtected ? TRUE : FALSE ;

	return S_OK;
}

STDMETHODIMP CImpPKCS12::put_KeyUserProtected(BOOL newVal)
{
	m_bUserProtected = newVal ? TRUE : FALSE ;

	return S_OK;
}
