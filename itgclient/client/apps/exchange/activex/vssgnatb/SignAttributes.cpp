// SignAttributes.cpp : Implementation of CSignAttributes
#include "stdafx.h"
#include "SignAtrb.h"
#include "SignAttributes.h"

#include "BitString.h"
#include "IA5String.h"
#include "Sequence.h"
#include "BaseDERCollection.h"
#include "Boolean.h"
#include "UniversalInteger.h"
#include "ObjectIdentifier.h"
#include "TaggedValue.h"
#include "PrintableString.h"

#include <stdio.h>
#include <stdlib.h>
#include <wincrypt.h>

// includes for HostName
#include <mshtml.h>


#define PRECANNED_HEADER "The following data is for authentication purpose only."

CSignAttributes::CSignAttributes()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSignAttributes

STDMETHODIMP CSignAttributes::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ISignAttributes
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (::InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CSignAttributes::put_userCertificate(BSTR newVal)
{
	m_dwErrorCode = S_OK ; // Reset error code

	m_szBase64PKCS7 = _WideToMultiString(newVal) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	_Base64Decode(m_szBase64PKCS7,
					strlen(m_szBase64PKCS7),
					NULL,
					&m_cbPKCS7) ;

	m_pbPKCS7 = (BYTE *) malloc(m_cbPKCS7+1) ;

	_Base64Decode(m_szBase64PKCS7,
					strlen(m_szBase64PKCS7),
					(char *)m_pbPKCS7,
					&m_cbPKCS7) ;

	////////////////////////////////////////////////////////////////////////////
	// Open a Message Handle that will hold the decoded PKCS#7 message
	////////////////////////////////////////////////////////////////////////////

	HCRYPTMSG			hCryptMsg = NULL ;

	if ( (hCryptMsg = CryptMsgOpenToDecode(
					MY_ENCODING_TYPE,
					0,
					0,
					0,
					NULL,
					NULL)) == NULL ) 
	{
		_ShowErrorMessage(GetLastError(), "put_UserCertificate : CryptMsgOpenToDecode for falied") ;
		return m_dwErrorCode ;
	}

	////////////////////////////////////////////////////////////////////////////
	// Update the handle with the DER of the PKCS#7
	////////////////////////////////////////////////////////////////////////////
	if ( !CryptMsgUpdate(
					hCryptMsg,
					m_pbPKCS7,
					m_cbPKCS7,
					TRUE) )
	{
		DWORD temp ;
		temp = GetLastError() ;
		_ShowErrorMessage(temp, "put_UserCertificate : CryptMsgUpdate for PKCS#7 falied") ;
		return m_dwErrorCode ;
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
		_ShowErrorMessage(temp, "put_UserCertificate : CryptMsgGetParam for PKCS#7 falied") ;
		return m_dwErrorCode ;
	}

	// Extract individual certificates (which are in X.509 format) into a 
	// Linked List of Certificate Contexts.

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
			_ShowErrorMessage(temp, "put_UserCertificate : CryptMsgGetParam for Certificate in PKCS#7 falied") ;
			return m_dwErrorCode ;
		}
			
		if ( (pCertContext = CertCreateCertificateContext(
						X509_ASN_ENCODING, 
						EncodedCertInPKCS7, 
						dwEncodedCertInPKCS7)) == NULL )
		{
			DWORD temp ;
			temp = GetLastError() ;
			_ShowErrorMessage(temp, "put_UserCertificate : CertCreateCertificateContext falied") ;
			return m_dwErrorCode ;
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

	m_pCertContextList = pCertContextList ;

	m_dwNumberOfCACerts = dwNumberOfCerts - 1 ; // subtract one for end-entity cert.

	// Determine if the FIRST or the LAST certificate is end-entity certificate.

	// Let us assume that the LAST certificate is indeed the end-entity certificate.
	// If it indeed is, then you should be able to find it in the MY cert store.
	// If you can't find it in MY cert store then just BLINDLY assume that the
	// FIRST cert is the end-entity cert.

	if ( !(m_hCertStore = CertOpenSystemStore(NULL, "MY")) )
   	{
		_ShowErrorMessage(GetLastError(), "put_UserCertificate : CertOpenSystemStore falied") ;
		return m_dwErrorCode ;
	}

	PCCERT_CONTEXT	pSearchCert = NULL ;
	
	if ( (pSearchCert = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							pCertContext->pbCertEncoded,			// This points to the LAST cert
																	// in the linked list.
							pCertContext->cbCertEncoded)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "put_UserCertificate : CertCreateCertificateContext falied") ;
		return m_dwErrorCode ;
	}

	PCCERT_CONTEXT  pCert ;
	BOOL			bEndUserCert_LAST = TRUE ; // By default, assume that the LAST cert in the
											   // PKCS#7/Linked list is the end-user cert.	
	if ( (pCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_PUBLIC_KEY,            // Find type
              &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
              NULL)) == NULL )               // Previous context
	{
		// If you can't find the last cert in the linked list IN the MY cert store,
		// then assume that it's the FIRST cert in the linked List that is the end-user
		// cert and that it is also in the MY cert store.
		bEndUserCert_LAST = FALSE ;
	}

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	if (pCert)
		CertFreeCertificateContext(pCert) ;

/*
	DWORD		dwSearchSubjectDNSize ;
	PCHAR		szSearchSubjectDN = NULL ;

	dwSearchSubjectDNSize = _GetCertSubjectRDN(pSearchCert, NULL) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	szSearchSubjectDN = (LPSTR) malloc(dwSearchSubjectDNSize) ;

	_GetCertSubjectRDN(pSearchCert, szSearchSubjectDN) ;

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	PCCERT_CONTEXT  pCert ;
	BOOL			bEndUserCert_LAST = TRUE ; // By default, assume that the LAST cert in the
											   // PKCS#7/Linked list is the end-user cert.	

	if ( (pCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_SUBJECT_STR_A,       // Find type
              szSearchSubjectDN,             // Name string
              NULL)) == NULL )               // Previous context
	{
		// If you can't find the last cert in the linked list IN the MY cert store,
		// then assume that it's the FIRST cert in the linked List that is the end-user
		// cert and that it is also in the MY cert store.
		bEndUserCert_LAST = FALSE ;
	}

	if (pCert)
		CertFreeCertificateContext(pCert) ;

	if (szSearchSubjectDN)
		free(szSearchSubjectDN) ;
*/

	if ( bEndUserCert_LAST )
	{
		//LAST certificate in the PKCS7 is assumed to be the end-entity certificate.
		m_cbUserCertificate = pCertContext->cbCertEncoded ;
		m_pbUserCertificate = pCertContext->pbCertEncoded ;
	}
	else
	{
		//FIRST certificate in the PKCS7 is assumed to be the end-entity certificate.
		m_cbUserCertificate = m_pCertContextList->pCertContext->cbCertEncoded ;
		m_pbUserCertificate = m_pCertContextList->pCertContext->pbCertEncoded ;
	}

 
	m_szUserCertificate = (LPSTR) malloc(m_cbUserCertificate*2+1) ;

	DWORD		i ;
	CHAR		temp[10] ;

	for ( i = 0 ; i < m_cbUserCertificate ; i++ )
	{
		itoa((int)m_pbUserCertificate[i], temp, 16) ;
		m_szUserCertificate[i*2] = (strlen(temp) == 2) ? temp[0] : '0' ;
		m_szUserCertificate[i*2+1] = (strlen(temp) == 2) ? temp[1] : temp[0] ;
	}
	m_szUserCertificate[m_cbUserCertificate*2] = '\0' ;

	return m_dwErrorCode;
}

STDMETHODIMP CSignAttributes::get_EncUserCertificate(BSTR *pVal)
{
	BSTR		bstrRetVal = _MultiToWideString(m_szUserCertificate) ;
	
	*pVal = bstrRetVal ;

	return S_OK ;
}

STDMETHODIMP CSignAttributes::get_EncUserSMIMECertificate(BSTR *pVal)
{
	if ( !(m_hCertStore = CertOpenSystemStore(NULL, "MY")) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertOpenSystemStore falied") ;
		return m_dwErrorCode ;
	}

	PCCERT_CONTEXT	pSearchCert = NULL ;
	
	if ( (pSearchCert = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							m_pbUserCertificate, 
							m_cbUserCertificate)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertCreateCertificateContext falied") ;
		return m_dwErrorCode ;
	}


	PCCERT_CONTEXT  pSignerCert ;
	if ( (pSignerCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_PUBLIC_KEY,            // Find type
              &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
              NULL)) == NULL )               // Previous context
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertFindCertificateInStore falied") ;
		return m_dwErrorCode ;
	}

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

/*
	DWORD		dwSearchSubjectDNSize ;
	PCHAR		szSearchSubjectDN = NULL ;

	dwSearchSubjectDNSize = _GetCertSubjectRDN(pSearchCert, NULL) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	szSearchSubjectDN = (LPSTR) malloc(dwSearchSubjectDNSize) ;

	_GetCertSubjectRDN(pSearchCert, szSearchSubjectDN) ;

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	if (m_dwErrorCode)
		return m_dwErrorCode ;

	PCCERT_CONTEXT  pSignerCert ;
	if ( (pSignerCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_SUBJECT_STR_A,       // Find type
              szSearchSubjectDN,             // Name string
              NULL)) == NULL )               // Previous context
	{
		_ShowErrorMessage(GetLastError(), "Update : CertFindCertificateInStore falied") ;
		return m_dwErrorCode ;
	}
	if (szSearchSubjectDN)
		free(szSearchSubjectDN) ;
*/

	CHAR							szMessage[] = {"Empty String"} ;
	BYTE							*MessageArray[] = {(unsigned char *)szMessage} ;
	DWORD							MessageSizeArray[1] ;
	MessageSizeArray[0] = strlen(szMessage) ;

	PCCERT_CONTEXT					*MsgCertArray ;
	DWORD							i ;

	PCCERT_CONTEXT_LIST		pTempCertContextList = NULL ;

	MsgCertArray = (PCCERT_CONTEXT *) malloc(sizeof(PCCERT_CONTEXT)*(m_dwNumberOfCACerts+1)) ;

	pTempCertContextList = m_pCertContextList ;

	for ( i = 0 ; i < m_dwNumberOfCACerts+1 ; i++ )
	{
		MsgCertArray[i] = pTempCertContextList->pCertContext ;
		pTempCertContextList = pTempCertContextList->nextCertContext ;
	}

	CRYPT_ALGORITHM_IDENTIFIER		HashAlgorithm ;
	DWORD							HashAlgSize  = sizeof(HashAlgorithm);
	memset(&HashAlgorithm, 0, HashAlgSize) ;	// Init. to zero.

	//HashAlgorithm.pszObjId = szOID_RSA_MD5 ;	// Then set the necessary field.
	HashAlgorithm.pszObjId = szOID_OIWSEC_sha1; //NP  //change the signing algo

	CRYPT_SIGN_MESSAGE_PARA			SigParams ;
	DWORD							SigParamsSize = sizeof(SigParams) ;
	memset(&SigParams, 0, SigParamsSize) ;

	SigParams.cbSize = SigParamsSize ;
	SigParams.dwMsgEncodingType = MY_ENCODING_TYPE ;
	SigParams.pSigningCert = pSignerCert ;
	SigParams.HashAlgorithm = HashAlgorithm ;
	SigParams.cMsgCert = m_dwNumberOfCACerts + 1 ; // add one for end-entity cert.
	SigParams.rgpMsgCert = MsgCertArray;

	CRYPT_ATTRIBUTE		authAttribute[2] ;
	CHAR				sz1OID[] = {"1.2.840.113549.1.9.15"} ; // sMIMECapabilities OID
	CHAR				sz2OID[] = {"1.3.6.1.4.1.311.16.4"} ; // Unknown OID

/* 
 

///////////////// THIS CODE SNIPPET HARDCODES ONLY "SPECIFIC" ALGORITHMS IN S/MIME ATTIBUTES /////

	PBYTE	pbPublicKeyData = NULL ;
	DWORD	dwPublicKeyNumberOfBytes = 0 ;

	pbPublicKeyData = pSignerCert->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData ;

	// Skip over the first SEQ and it's length fields
	if ( pbPublicKeyData[1] & 0x80 )
		pbPublicKeyData += 2 + (pbPublicKeyData[1] & 0x7F) ;
	else
		pbPublicKeyData += 2 ;

	// pbPublicKeyData now points to the BIT STRING tag byte.
	if ( pbPublicKeyData[1] & 0x80 )
		dwPublicKeyNumberOfBytes = pbPublicKeyData[2] ;
	else
		dwPublicKeyNumberOfBytes = pbPublicKeyData[1] ;

	dwPublicKeyNumberOfBytes &= 0xFE ;

	// Now check if the size of public key is 1024 bits. If it is, then it means that the
	// end-user certificate enrollment was done using Enhanced Provider. If such is the case,
	// then use RC2-128 bit algorithm for symmetric encryption, otherwise user RC2-40 bit
	// algorithm for symmetric encryption. Wierd corelation - but that's what we have defined
	// it to be !!
	if ( (dwPublicKeyNumberOfBytes * 8) == 1024 )
		m_dwEncryptionStrength = 128 ;
	else
		m_dwEncryptionStrength = 40 ;

	// Construct the RC2CBC blob
	CUniversalInteger	uiNumberOfBits(2, (_PBYTE)&m_dwEncryptionStrength) ;

	_BYTE				szRC2CBC_OID[] = {"1.2.840.113549.3.2"} ;
	CObjectIdentifier	oidRC2CBC(
									strlen((const char *)szRC2CBC_OID),
									(_PBYTE)szRC2CBC_OID
								 ) ;

	CBaseDERCollection	bdcRC2CBC ;

	bdcRC2CBC = oidRC2CBC + uiNumberOfBits ;

	CSequence			seqRC2CBC(bdcRC2CBC) ;

	// Construct the MD5 blob
	_BYTE				szMD5_OID[] = {"1.2.840.113549.2.5"} ;
	CObjectIdentifier	oidMD5(
									strlen((const char *)szMD5_OID),
									(_PBYTE)szMD5_OID
							  ) ;
	CSequence			seqMD5(oidMD5) ;

	// Construct the MD5WithRSAEncryption blob
	_BYTE				szMD5WithRSAEncryption[] = {"1.2.840.113549.1.1.4"} ;
	CObjectIdentifier	oidMD5WithRSAEncryption(
									strlen((const char *)szMD5WithRSAEncryption),
									(_PBYTE)szMD5WithRSAEncryption
											   ) ;
	CSequence			seqMD5WithRSAEncryption(oidMD5WithRSAEncryption) ;

	// Construct the SHA1WithRSAEncryption blob
	_BYTE				szSHA1WithRSAEncryption[] = {"1.2.840.113549.1.1.5"} ;
	CObjectIdentifier	oidSHA1WithRSAEncryption(
									strlen((const char *)szSHA1WithRSAEncryption),
									(_PBYTE)szSHA1WithRSAEncryption
											    ) ;
	CSequence			seqSHA1WithRSAEncryption(oidSHA1WithRSAEncryption) ;

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	bdcSMIMECapabilitiesSupported = seqRC2CBC + seqMD5 + seqMD5WithRSAEncryption + seqSHA1WithRSAEncryption ;

	CSequence			seqSMIMECapabilitiesSupported(bdcSMIMECapabilitiesSupported) ;
*/

/*

///////////////// THIS CODE SNIPPET HARDCODES ALL KNOWN ALGORITHMS IN S/MIME ATTIBUTES /////

	// Set RC2CBC 40-bits	
	m_dwEncryptionStrength = 40 ;
	CUniversalInteger	uiNumberOfBits40(2, (_PBYTE)&m_dwEncryptionStrength) ;
	CObjectIdentifier	oidRC2CBC40(
									strlen((const char *)szOID_RSA_RC2CBC),
									(_PBYTE)szOID_RSA_RC2CBC
								 ) ;
	CBaseDERCollection	bdcRC2CBC40 ;
	bdcRC2CBC40 = oidRC2CBC40 + uiNumberOfBits40 ;
	CSequence		seqRC2CBC40 ;
	seqRC2CBC40 = bdcRC2CBC40 ;

	// Set RC2CBC 128-bits	
	m_dwEncryptionStrength = 128 ;
	CUniversalInteger	uiNumberOfBits128(2, (_PBYTE)&m_dwEncryptionStrength) ;
	CObjectIdentifier	oidRC2CBC128(
									strlen((const char *)szOID_RSA_RC2CBC),
									(_PBYTE)szOID_RSA_RC2CBC
								 ) ;
	CBaseDERCollection	bdcRC2CBC128 ;
	bdcRC2CBC128 = oidRC2CBC128 + uiNumberOfBits128 ;
	CSequence		seqRC2CBC128 ;
	seqRC2CBC128 = bdcRC2CBC128 ;

	// Set 3DES
	CObjectIdentifier	oid3DES(
									strlen((const char *)szOID_RSA_DES_EDE3_CBC),
									(_PBYTE)szOID_RSA_DES_EDE3_CBC
								 ) ;
	CBaseDERCollection	bdc3DES ;
	bdc3DES = oid3DES ;
	CSequence		seq3DES ;
	seq3DES = bdc3DES ;

	// Set desCBC
	CObjectIdentifier	oidDESCBC(
									strlen((const char *)szOID_OIWSEC_desCBC),
									(_PBYTE)szOID_OIWSEC_desCBC
								 ) ;
	CBaseDERCollection	bdcDESCBC ;
	bdcDESCBC = oidDESCBC ;
	CSequence		seqDESCBC ;
	seqDESCBC = bdcDESCBC ;

	// Set SHA1 with RSA encryption
	CObjectIdentifier	oidSHA1RSA(
									strlen((const char *)szOID_RSA_SHA1RSA),
									(_PBYTE)szOID_RSA_SHA1RSA
							  ) ;
	CSequence		seqSHA1RSA ;
	seqSHA1RSA = oidSHA1RSA ;

	// Set MD5 with RSA encryption
	CObjectIdentifier	oidMD5RSA(
									strlen((const char *)szOID_RSA_MD5RSA),
									(_PBYTE)szOID_RSA_MD5RSA
							  ) ;
	CSequence		seqMD5RSA ;
	seqMD5RSA = oidMD5RSA ;

	// Set MD5
	CObjectIdentifier	oidMD5(
									strlen((const char *)szOID_RSA_MD5),
									(_PBYTE)szOID_RSA_MD5
							  ) ;
	CSequence		seqMD5 ;
	seqMD5 = oidMD5 ;

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	bdcSMIMECapabilitiesSupported = seqRC2CBC40 + seqRC2CBC128 + seq3DES + seqDESCBC +
									seqSHA1RSA + seqMD5RSA +
									seqMD5 ;
*/

/*

///////////////// THIS CODE SNIPPET ADD ONLY "SELECTED" ALGORITHMS IN S/MIME ATTIBUTES /////

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	CHAR	seps[10] ;
	PCHAR	token = NULL, tmpContent = NULL ;
	DWORD	dwAlgorithms = strlen(m_szAlgorithms) ;
	DWORD	dwIndex = 0, dwIncrement = 0 ;

	seps[0] = ',' ;
	seps[1] = '\0' ;

	tmpContent = m_szAlgorithms ;

	while(dwIndex < dwAlgorithms)
	{
		if ( (token = strtok(tmpContent, seps)) == NULL )
			break ;

		if ( strncmp(token, "RC2-40", 100) == 0 )
		{
			// Add RC2CBC 40-bits	
			DWORD dwEncryptionStrength = 40 ;
			CUniversalInteger	uiNumberOfBits40(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC40(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC40 ;
			bdcRC2CBC40 = oidRC2CBC40 + uiNumberOfBits40 ;
			CSequence		seqRC2CBC40 ;
			seqRC2CBC40 = bdcRC2CBC40 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC40 ;
		}
		else if ( strncmp(token, "RC2-128", 100) == 0 )
		{
			// Add RC2CBC 128-bits	
			DWORD dwEncryptionStrength = 128 ;
			CUniversalInteger	uiNumberOfBits128(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC128(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC128 ;
			bdcRC2CBC128 = oidRC2CBC128 + uiNumberOfBits128 ;
			CSequence		seqRC2CBC128 ;
			seqRC2CBC128 = bdcRC2CBC128 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC128 ;
		}
		else if ( strncmp(token, "DES", 100) == 0 )
		{
			// Add desCBC
			CObjectIdentifier	oidDESCBC(
											strlen((const char *)szOID_OIWSEC_desCBC),
											(_PBYTE)szOID_OIWSEC_desCBC
										 ) ;
			CBaseDERCollection	bdcDESCBC ;
			bdcDESCBC = oidDESCBC ;
			CSequence		seqDESCBC ;
			seqDESCBC = bdcDESCBC ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqDESCBC ;
		}
		else if ( strncmp(token, "3DES", 100) == 0 )
		{
			// Add 3DES
			CObjectIdentifier	oid3DES(
											strlen((const char *)szOID_RSA_DES_EDE3_CBC),
											(_PBYTE)szOID_RSA_DES_EDE3_CBC
										 ) ;
			CBaseDERCollection	bdc3DES ;
			bdc3DES = oid3DES ;
			CSequence		seq3DES ;
			seq3DES = bdc3DES ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seq3DES ;
		}
		else if ( strncmp(token, "MD5", 100) == 0 )
		{
			// Add MD5
			CObjectIdentifier	oidMD5(
											strlen((const char *)szOID_RSA_MD5),
											(_PBYTE)szOID_RSA_MD5
										 ) ;
			CBaseDERCollection	bdcMD5 ;
			bdcMD5 = oidMD5 ;
			CSequence		seqMD5 ;
			seqMD5 = bdcMD5 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5 ;
		}
		else if ( strncmp(token, "MD4", 100) == 0 )
		{
			// Add MD4
			CObjectIdentifier	oidMD4(
											strlen((const char *)szOID_RSA_MD4),
											(_PBYTE)szOID_RSA_MD4
										 ) ;
			CBaseDERCollection	bdcMD4 ;
			bdcMD4 = oidMD4 ;
			CSequence		seqMD4 ;
			seqMD4 = bdcMD4 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD4 ;
		}
		else if ( strncmp(token, "MD2", 100) == 0 )
		{
			// Add MD2
			CObjectIdentifier	oidMD2(
											strlen((const char *)szOID_RSA_MD2),
											(_PBYTE)szOID_RSA_MD2
										 ) ;
			CBaseDERCollection	bdcMD2 ;
			bdcMD2 = oidMD2 ;
			CSequence		seqMD2 ;
			seqMD2 = bdcMD2 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD2 ;
		}
		else if ( strncmp(token, "SHA1RSA", 100) == 0 )
		{
			// Add SHA1RSA
			CObjectIdentifier	oidSHA1RSA(
											strlen((const char *)szOID_RSA_SHA1RSA),
											(_PBYTE)szOID_RSA_SHA1RSA
										 ) ;
			CBaseDERCollection	bdcSHA1RSA ;
			bdcSHA1RSA = oidSHA1RSA ;
			CSequence		seqSHA1RSA ;
			seqSHA1RSA = bdcSHA1RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1RSA ;
		}
		else if ( strncmp(token, "MD5RSA", 100) == 0 )
		{
			// Add MD5RSA
			CObjectIdentifier	oidMD5RSA(
											strlen((const char *)szOID_RSA_MD5RSA),
											(_PBYTE)szOID_RSA_MD5RSA
										 ) ;
			CBaseDERCollection	bdcMD5RSA ;
			bdcMD5RSA = oidMD5RSA ;
			CSequence		seqMD5RSA ;
			seqMD5RSA = bdcMD5RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5RSA ;
		}
		else
		{
			 return CRYPT_E_UNKNOWN_ALGO ;
		}

		dwIncrement = strlen(token) + 1 ;
		dwIndex += dwIncrement ;
		tmpContent += dwIncrement ;
	}
*/

	// Determine which CSP is associated with the Signing Certificate

	DWORD					dwCryptKeyProvInfo = 0 ;
	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						NULL,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	PCHAR	buff = (PCHAR) malloc(dwCryptKeyProvInfo) ;

	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						buff,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	CRYPT_KEY_PROV_INFO	*pCryptKeyProvInfo ;

	pCryptKeyProvInfo = (CRYPT_KEY_PROV_INFO *)buff ;

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	PCHAR	szProviderName = _WideToMultiString(pCryptKeyProvInfo->pwszProvName) ;
	PCHAR	szContainerName = _WideToMultiString(pCryptKeyProvInfo->pwszContainerName) ;

	HCRYPTPROV	hCryptProv = NULL ;
	
	//if ( !CryptAcquireContext(
	//						&hCryptProv,
	//						szContainerName,
	//						szProviderName,
  	//						PROV_RSA_FULL,
	//						0) )

    if ( !CryptAcquireContextW(
							&hCryptProv,
							pCryptKeyProvInfo->pwszContainerName,
							pCryptKeyProvInfo->pwszProvName,
							PROV_RSA_FULL,
							0) ) /////NP

	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CryptAcquireContext falied") ;
		return m_dwErrorCode ;
	}

	DWORD		dwFlags = 0, dwDataLen = 0, dwBits = 0, dwNameLen ;
	BYTE		pbData[1000], *ptr = NULL ;
	CHAR		szName[100], *pszAlgType = NULL ;
	ALG_ID		aiAlgid ;
	// Enumerate the supported algorithms.
	for(i=0 ; ; i++) 
	{
		// Set the CRYPT_FIRST flag the first time through the loop.
		if(i == 0) 
		{
			dwFlags = CRYPT_FIRST;
		} else 
		{
			dwFlags = 0;
		}

		// Retrieve information about an algorithm.
		dwDataLen = 1000;
		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &dwDataLen, dwFlags)) 
		{
			if(GetLastError() == ERROR_NO_MORE_ITEMS) 
			{
				// Exit the loop.
				break;
			}
			else 
			{
				_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CryptGetProvParam falied : Error reading algorithm") ;
				return m_dwErrorCode ;
			}
		}

		// Extract algorithm information from 'pbData' buffer.
		ptr = pbData;
		aiAlgid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		dwNameLen = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		strncpy(szName, (const char *)ptr,dwNameLen);

		// Determine algorithm type.
		switch(GET_ALG_CLASS(aiAlgid)) 
		{
			case ALG_CLASS_DATA_ENCRYPT: 
						pszAlgType = "Encrypt  ";
						break;
			case ALG_CLASS_HASH:	 
						pszAlgType = "Hash     ";
						break;
			case ALG_CLASS_KEY_EXCHANGE: 
						pszAlgType = "Exchange ";
						break;
			case ALG_CLASS_SIGNATURE:	 
						pszAlgType = "Signature";
						break;
			default:			 
						pszAlgType = "Unknown  ";
		}

		CHAR		szAlgorithm[1000] ;

		sprintf(szAlgorithm, "%s-%d", szName, dwBits) ;

		if ( strcmp(szAlgorithm, "RC2-40") == 0 )
		{
			// Add RC2CBC 40-bits	
			DWORD dwEncryptionStrength = 40 ;
			CUniversalInteger	uiNumberOfBits40(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC40(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC40 ;
			bdcRC2CBC40 = oidRC2CBC40 + uiNumberOfBits40 ;
			CSequence		seqRC2CBC40 ;
			seqRC2CBC40 = bdcRC2CBC40 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC40 ;
		}
		else if ( strcmp(szAlgorithm, "RC2-128") == 0 )
		{
			// Add RC2CBC 128-bits	
			DWORD dwEncryptionStrength = 128 ;
			CUniversalInteger	uiNumberOfBits128(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC128(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC128 ;
			bdcRC2CBC128 = oidRC2CBC128 + uiNumberOfBits128 ;
			CSequence		seqRC2CBC128 ;
			seqRC2CBC128 = bdcRC2CBC128 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC128 ;
		}
		else if ( strcmp(szAlgorithm, "DES-56") == 0 )
		{
			// Add desCBC
			CObjectIdentifier	oidDESCBC(
											strlen((const char *)szOID_OIWSEC_desCBC),
											(_PBYTE)szOID_OIWSEC_desCBC
										 ) ;
			CBaseDERCollection	bdcDESCBC ;
			bdcDESCBC = oidDESCBC ;
			CSequence		seqDESCBC ;
			seqDESCBC = bdcDESCBC ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqDESCBC ;
		}
		else if ( strcmp(szAlgorithm, "3DES-168") == 0 )
		{
			// Add 3DES
			CObjectIdentifier	oid3DES(
											strlen((const char *)szOID_RSA_DES_EDE3_CBC),
											(_PBYTE)szOID_RSA_DES_EDE3_CBC
										 ) ;
			CBaseDERCollection	bdc3DES ;
			bdc3DES = oid3DES ;
			CSequence		seq3DES ;
			seq3DES = bdc3DES ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seq3DES ;
		}
		else if ( strcmp(szAlgorithm, "MD5-128") == 0 )
		{
			// Add MD5
			CObjectIdentifier	oidMD5(
											strlen((const char *)szOID_RSA_MD5),
											(_PBYTE)szOID_RSA_MD5
										 ) ;
			CBaseDERCollection	bdcMD5 ;
			bdcMD5 = oidMD5 ;
			CSequence		seqMD5 ;
			seqMD5 = bdcMD5 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5 ;
		}
		else if ( strcmp(szAlgorithm, "MD4-128") == 0 )
		{
			// Add MD4
			CObjectIdentifier	oidMD4(
											strlen((const char *)szOID_RSA_MD4),
											(_PBYTE)szOID_RSA_MD4
										 ) ;
			CBaseDERCollection	bdcMD4 ;
			bdcMD4 = oidMD4 ;
			CSequence		seqMD4 ;
			seqMD4 = bdcMD4 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD4 ;
		}
		else if ( strcmp(szAlgorithm, "MD2-128") == 0 )
		{
			// Add MD2
			CObjectIdentifier	oidMD2(
											strlen((const char *)szOID_RSA_MD2),
											(_PBYTE)szOID_RSA_MD2
										 ) ;
			CBaseDERCollection	bdcMD2 ;
			bdcMD2 = oidMD2 ;
			CSequence		seqMD2 ;
			seqMD2 = bdcMD2 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD2 ;
		}
		else if ( strcmp(szAlgorithm, "SHA-1-160") == 0 )
		{
			// Add SHA-1
			CObjectIdentifier	oidSHA1(
											strlen((const char *)szOID_OIWSEC_sha1),
											(_PBYTE)szOID_OIWSEC_sha1
										 ) ;
			CBaseDERCollection	bdcSHA1 ;
			bdcSHA1 = oidSHA1 ;
			CSequence		seqSHA1 ;
			seqSHA1 = bdcSHA1 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1 ;
		}
		else if ( (strcmp(szAlgorithm, "RSA_KEYX-1024") == 0) || (strcmp(szAlgorithm, "RSA_KEYX-512") == 0)
				||(strcmp(szAlgorithm, "RSA_KEYX-2048") == 0))
		{
			// Add SHA1RSA
			CObjectIdentifier	oidSHA1RSA(
											strlen((const char *)szOID_RSA_SHA1RSA),
											(_PBYTE)szOID_RSA_SHA1RSA
										 ) ;
			CBaseDERCollection	bdcSHA1RSA ;
			bdcSHA1RSA = oidSHA1RSA ;
			CSequence		seqSHA1RSA ;
			seqSHA1RSA = bdcSHA1RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1RSA ;

			// Add MD5RSA
			CObjectIdentifier	oidMD5RSA(
											strlen((const char *)szOID_RSA_MD5RSA),
											(_PBYTE)szOID_RSA_MD5RSA
										 ) ;
			CBaseDERCollection	bdcMD5RSA ;
			bdcMD5RSA = oidMD5RSA ;
			CSequence		seqMD5RSA ;
			seqMD5RSA = bdcMD5RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5RSA ;
		}
	}

	CSequence			seqSMIMECapabilitiesSupported(bdcSMIMECapabilitiesSupported) ;

	DWORD				cbEncoded ;
	PBYTE				pbEncoded ;

	pbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->pbData ;
	cbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->cbData ;

/*
	BYTE				pbEncoded[1024] ;
	DWORD				cbEncoded = 1024 ; 

	//SEQUENCE
	pbEncoded[0] = 0x30 ;
	pbEncoded[1] = 54 ;
		// SEQUENCE
		pbEncoded[2] = 0x30 ;
		pbEncoded[3] = 0x0E ;
			// OID - rc2CBC
			pbEncoded[4] = 0x06 ;
			pbEncoded[5] = 0x08 ;
				pbEncoded[6] = 0x2A ;
				pbEncoded[7] = 0x86 ;
				pbEncoded[8] = 0x48 ;
				pbEncoded[9] = 0x86 ;
				pbEncoded[10] = 0xF7 ;
				pbEncoded[11] = 0x0D ;
				pbEncoded[12] = 0x03 ;
				pbEncoded[13] = 0x02 ;
			pbEncoded[14] = 0x02 ;
			pbEncoded[15] = 0x02 ;
				pbEncoded[16] = 0x00 ;

				PBYTE	pbPublicKeyData = NULL ;
				DWORD	dwPublicKeyNumberOfBytes = 0 ;

				pbPublicKeyData = pSignerCert->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData ;

				// Skip over the first SEQ and it's length fields
				if ( pbPublicKeyData[1] & 0x80 )
					pbPublicKeyData += 2 + (pbPublicKeyData[1] & 0x7F) ;
				else
					pbPublicKeyData += 2 ;

				// pbPublicKeyData now points to the BIT STRING tag byte.
				if ( pbPublicKeyData[1] & 0x80 )
					dwPublicKeyNumberOfBytes = pbPublicKeyData[2] ;
				else
					dwPublicKeyNumberOfBytes = pbPublicKeyData[1] ;

				dwPublicKeyNumberOfBytes &= 0xFE ;

				// Now check if the size of public key is 1024 bits. If it is, then it means that the
				// end-user certificate enrollment was done using Enhanced Provider. If such is the case,
				// then use RC2-128 bit algorithm for symmetric encryption, otherwise user RC2-40 bit
				// algorithm for symmetric encryption. Wierd corelation - but that's what we have defined
				// it to be !!
				if ( (dwPublicKeyNumberOfBytes * 8) == 1024 )
					m_dwSymEncryptionBits = 128 ;
				else
					m_dwSymEncryptionBits = 40 ;

				pbEncoded[17] = (BYTE)m_dwSymEncryptionBits ;
		// SEQUENCE
		pbEncoded[18] = 0x30 ;
		pbEncoded[19] = 0x0A ;
			// OID - md5
			pbEncoded[20] = 0x06 ;
			pbEncoded[21] = 0x08 ;
				pbEncoded[22] = 0x2A ;
				pbEncoded[23] = 0x86 ;
				pbEncoded[24] = 0x48 ;
				pbEncoded[25] = 0x86 ;
				pbEncoded[26] = 0xF7 ;
				pbEncoded[27] = 0x0D ;
				pbEncoded[28] = 0x02 ;
				pbEncoded[29] = 0x05 ;
		// SEQUENCE
		pbEncoded[30] = 0x30 ;
		pbEncoded[31] = 0x0B ;
			// OID - md5withRSAEncryption
			pbEncoded[32] = 0x06 ;
			pbEncoded[33] = 0x09 ;
				pbEncoded[34] = 0x2A ;
				pbEncoded[35] = 0x86 ;
				pbEncoded[36] = 0x48 ;
				pbEncoded[37] = 0x86 ;
				pbEncoded[38] = 0xF7 ;
				pbEncoded[39] = 0x0D ;
				pbEncoded[40] = 0x01 ;
				pbEncoded[41] = 0x01 ;
				pbEncoded[42] = 0x04 ;
		// SEQUENCE
		pbEncoded[43] = 0x30 ;
		pbEncoded[44] = 0x0B ;
			// OID - sha1withRSAEncryption
			pbEncoded[45] = 0x06 ;
			pbEncoded[46] = 0x09 ;
				pbEncoded[47] = 0x2A ;
				pbEncoded[48] = 0x86 ;
				pbEncoded[49] = 0x48 ;
				pbEncoded[50] = 0x86 ;
				pbEncoded[51] = 0xF7 ;
				pbEncoded[52] = 0x0D ;
				pbEncoded[53] = 0x01 ;
				pbEncoded[54] = 0x01 ;
				pbEncoded[55] = 0x05 ;

	cbEncoded = 56 ;
*/



	BYTE		pbEncoded2[5000], reversed[1024] ;
	DWORD		cbEncoded2, derSize ;

	derSize = pSignerCert->pCertInfo->Issuer.cbData +
			  2 +
			  pSignerCert->pCertInfo->SerialNumber.cbData ;

	// SEQUENCE
	pbEncoded2[0] = 0x30 ;
	pbEncoded2[1] = 0x82 ;
	pbEncoded2[2] = (BYTE)((derSize & 0x0000FF00) >> 8) ;
	pbEncoded2[3] = (BYTE)(derSize & 0x000000FF) ;
		// Issuer DN
		memcpy(pbEncoded2+4, pSignerCert->pCertInfo->Issuer.pbData, pSignerCert->pCertInfo->Issuer.cbData) ;
		// End-user certificate serial number
		pbEncoded2[4+pSignerCert->pCertInfo->Issuer.cbData] = 0x02 ;
		pbEncoded2[4+pSignerCert->pCertInfo->Issuer.cbData+1] = (unsigned char) pSignerCert->pCertInfo->SerialNumber.cbData ;
			for ( i = 0 ; i < pSignerCert->pCertInfo->SerialNumber.cbData ; i++ )
				reversed[pSignerCert->pCertInfo->SerialNumber.cbData-i-1] = pSignerCert->pCertInfo->SerialNumber.pbData[i] ;
			memcpy(pbEncoded2+4 + pSignerCert->pCertInfo->Issuer.cbData+2, reversed, pSignerCert->pCertInfo->SerialNumber.cbData) ;

	cbEncoded2 = 4 +
				 pSignerCert->pCertInfo->Issuer.cbData +
				 2 +
				 pSignerCert->pCertInfo->SerialNumber.cbData ;
				 
	CRYPT_ATTR_BLOB		authAttrBlob, authAttrBlob2 ;

	authAttrBlob.cbData = cbEncoded ;
	authAttrBlob.pbData = pbEncoded ;

	authAttrBlob2.cbData = cbEncoded2 ;
	authAttrBlob2.pbData = pbEncoded2 ;

	authAttribute[0].pszObjId = sz1OID ; // sMIMECapabilities OID
	authAttribute[0].cValue = 1 ;
	authAttribute[0].rgValue = &authAttrBlob ;

	authAttribute[1].pszObjId = sz2OID ; // Unknown OID
	authAttribute[1].cValue = 1 ;
	authAttribute[1].rgValue = &authAttrBlob2 ;

	SigParams.cAuthAttr = 2 ;
	SigParams.rgAuthAttr = authAttribute ;

	// Get the size of the output SignedBlob.
	DWORD    cbSignedMessageBlob = NULL ;

	if ( !CryptSignMessage(
          &SigParams,            // Signature parameters
          FALSE,                 // Not detached
          1,                     // Number of messages
          (const BYTE **)MessageArray,          // Messages to be signed
          MessageSizeArray,      // Size of messages
          NULL,                  // Buffer for signed msg
          &cbSignedMessageBlob) ) // Size of buffer
	{
		_ShowErrorMessage(GetLastError(), "Update : CryptSignMessage falied") ;
		return m_dwErrorCode ;
	}

	// Allocate memory for the signed blob.
	BYTE	*pbSignedMessageBlob ;
	pbSignedMessageBlob = (BYTE*)malloc(cbSignedMessageBlob) ;
	memset(pbSignedMessageBlob, 49, cbSignedMessageBlob) ;

	// Get the SignedMessageBlob.
	if ( !CryptSignMessage(
          &SigParams,            // Signature parameters
          FALSE,                 // Not detached
          1,                     // Number of messages
          (const BYTE **)MessageArray,          // Messages to be signed
          MessageSizeArray,      // Size of messages
          pbSignedMessageBlob,   // Buffer for signed msg
          &cbSignedMessageBlob) ) // Size of buffer
	{
		_ShowErrorMessage(GetLastError(), "Update : CryptSignMessage falied") ;
		return m_dwErrorCode ;
	}

	m_cbUserSMIMECertificate = cbSignedMessageBlob ;
	m_pbUserSMIMECertificate = pbSignedMessageBlob ;

	CHAR		temp[10] ;
	m_szUserSMIMECertificate = (LPSTR) malloc(m_cbUserSMIMECertificate*2+1) ;

	for ( i = 0 ; i < m_cbUserSMIMECertificate ; i++ )
	{
		itoa((int)m_pbUserSMIMECertificate[i], temp, 16) ;
		m_szUserSMIMECertificate[i*2] = (strlen(temp) == 2) ? temp[0] : '0' ;
		m_szUserSMIMECertificate[i*2+1] = (strlen(temp) == 2) ? temp[1] : temp[0] ;
	}
	m_szUserSMIMECertificate[m_cbUserSMIMECertificate*2] = '\0' ;

	BSTR		bstrRetVal = _MultiToWideString(m_szUserSMIMECertificate) ;
	
	*pVal = bstrRetVal ;

	return S_OK ;
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

LPSTR CSignAttributes::_WideToMultiString(BSTR szwcInputString)
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

BSTR CSignAttributes::_MultiToWideString(LPSTR szInputString)
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

void CSignAttributes::_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize)
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

void CSignAttributes::_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString)
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
	sprintf(temp, "CSignAttributes::%s", szExtraString) ;
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
// _GetCertSubjectRDN() : Gets the RDN of the "Subject" for a 
//               certificate present in the system certificate store.
//  Input :
//	  pCertContext : PCCERT_CONTEXT
//				 Contains a certificate context that is to be used to 
//			     display the subject RDN. 
//  Output :
//    szSubjectRDN : LPSTR
//				 Contains the address where the RDN of the "Subject" is to be copied.
//				 If this parameter is specified as NULL, then the function returns
//				 the size of Subject RDN string. This function assumes that memory
//				 has been allocated for the szSubjectRDN formal parameter.
//  Returns :
//				 If the szSubjectRDN formal parameter is NULL then this function
//				 return the size of the Subject RDN string. Otherwise, on successful
//				 completion, this function should return 0. If this function fails
//				 then it returns -1.
/*****************************************************************************/
/*****
The call to this function has been commented.This function returned the szSubjectRDN 
in char*. It is good to change it to return the value into wchar 
****/

DWORD CSignAttributes::_GetCertSubjectRDN(PCCERT_CONTEXT pCertContext, LPSTR szSubjectRDN)
{
	CERT_NAME_BLOB    NameBlob;
	DWORD             dwSize = NULL;
    LPSTR             pszSubjectName;
	

    NameBlob = pCertContext->pCertInfo->Subject;

    // Call CertNameToStr to get the Subject RDN string length.
     dwSize = CertNameToStr(
             MY_ENCODING_TYPE,     // Encoding type
             &NameBlob,            // CERT_NAME_BLOB
             CERT_SIMPLE_NAME_STR, // Type
             NULL,                 // Place to return string
             dwSize);              // Size of string (chars), 
                                   //   including zero terminator.

	


    if(dwSize <= 1) // This function always returns a null char 
                    //   (0), so the minimum count returned will 
                    //   be 1, even if nothing got converted.
    {
		m_dwErrorCode = GetLastError() ;
        return -1;
    }

	if (szSubjectRDN == NULL)
	{
		return dwSize ;
	}

    // Allocate memory for the returned string.
    pszSubjectName = (LPSTR)malloc(dwSize);
    if(!pszSubjectName)
	{
		m_dwErrorCode = GetLastError() ;
		return -1;
	}

    // Call CertNameToStr to get the string.
    dwSize = CertNameToStr(
             MY_ENCODING_TYPE,     // Encoding type
             &NameBlob,            // CERT_NAME_BLOB
             CERT_SIMPLE_NAME_STR, // Type
             pszSubjectName,       // Place to return string
             dwSize);              // Size of string (chars)

    if(dwSize <= 1)
    {
		m_dwErrorCode = GetLastError() ;
        return -1;
    }

	strcpy(szSubjectRDN, pszSubjectName) ;

	free(pszSubjectName);

	return dwSize ;
}

/*
STDMETHODIMP CSignAttributes::put_EncryptionStrength(long newVal)
{
	if ( newVal == 40 || newVal == 128 )
	{
		m_dwEncryptionStrength = newVal ;
		return S_OK;
	}
	else
	{
		return S_FALSE ;
	}
}

STDMETHODIMP CSignAttributes::put_HashAlgorithm(BSTR newVal)
{
	if ( wcscmp(newVal, L"MD2") == 0 )
	{
		strcpy(m_szHashAlgorithm, szOID_RSA_MD2) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"MD4") == 0 )
	{
		strcpy(m_szHashAlgorithm, szOID_RSA_MD4) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"MD5") == 0 )
	{
		strcpy(m_szHashAlgorithm, szOID_RSA_MD5) ;
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}

STDMETHODIMP CSignAttributes::put_AsymmetricEncryptionAlgorithm(BSTR newVal)
{
	if ( wcscmp(newVal, L"RSA") == 0 )
	{
		strcpy(m_szASymmetricEncryptionAlgorithm, szOID_RSA_RSA) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"MD2RSA") == 0 )
	{
		strcpy(m_szASymmetricEncryptionAlgorithm, szOID_RSA_MD2RSA) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"MD4RSA") == 0 )
	{
		strcpy(m_szASymmetricEncryptionAlgorithm, szOID_RSA_MD4RSA) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"MD5RSA") == 0 )
	{
		strcpy(m_szASymmetricEncryptionAlgorithm, szOID_RSA_MD5RSA) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"SHA1RSA") == 0 )
	{
		strcpy(m_szASymmetricEncryptionAlgorithm, szOID_RSA_SHA1RSA) ;
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}

STDMETHODIMP CSignAttributes::put_SymmetricEncryptionAlgorithm(BSTR newVal)
{
	if ( wcscmp(newVal, L"RC2CBC") == 0 )
	{
		strcpy(m_szSymmetricEncryptionAlgorithm, szOID_RSA_RC2CBC) ;
		return S_OK ;
	}
	else if ( wcscmp(newVal, L"RC4") == 0 )
	{
		strcpy(m_szSymmetricEncryptionAlgorithm, szOID_RSA_RC4) ;
		return S_OK ;
	}
	else
	{
		return S_FALSE ;
	}
}
*/

/*
STDMETHODIMP CSignAttributes::get_Algorithms(BSTR *pVal)
{
	BSTR		bstrRetVal = _MultiToWideString(m_szAlgorithms) ;
	
	*pVal = bstrRetVal ;

	return S_OK ;
}


STDMETHODIMP CSignAttributes::put_Algorithms(BSTR newVal)
{
	m_szAlgorithms = (LPSTR) _WideToMultiString(newVal) ;

	LPSTR	szTmpAlgorithms = (LPSTR) _WideToMultiString(newVal) ;

	CHAR	seps[10] ;
	PCHAR	token = NULL, tmpContent = NULL ;
	DWORD	dwAlgorithms = strlen(szTmpAlgorithms) ;
	DWORD	dwIndex = 0, dwIncrement = 0 ;

	seps[0] = ',' ;
	seps[1] = '\0' ;

	tmpContent = szTmpAlgorithms ;

	while(dwIndex < dwAlgorithms)
	{
		if ( (token = strtok(tmpContent, seps)) == NULL )
			break ;

		if ( (strncmp(token, "RC2-40", 100) != 0) &&
			 (strncmp(token, "RC2-128", 100) != 0) &&
			 (strncmp(token, "DES", 100) != 0) &&
			 (strncmp(token, "3DES", 100) != 0) &&
			 (strncmp(token, "MD5", 100) != 0) &&
			 (strncmp(token, "MD4", 100) != 0) &&
			 (strncmp(token, "MD2", 100) != 0) &&
			 (strncmp(token, "SHA1RSA", 100) != 0) &&
			 (strncmp(token, "MD5RSA", 100) != 0) )
		{
			 return CRYPT_E_UNKNOWN_ALGO ;
		}
		dwIncrement = strlen(token) + 1 ;
		dwIndex += dwIncrement ;
		tmpContent += dwIncrement ;
	}

	return S_OK ;
}
*/

STDMETHODIMP CSignAttributes::get_ChallengePhrase(BSTR *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CSignAttributes::put_ChallengePhrase(BSTR newVal)
{
	m_ChallengePhrase = _WideToMultiString(newVal);
	return S_OK;
}

HRESULT CSignAttributes::_GetHostName(BSTR *tbstrHostName)
{
	HRESULT retVal = S_OK;

	BSTR bstrHostName;
	CComPtr <IOleContainer>		spContainer;

	if(m_spClientSite)
	{
		m_spClientSite->GetContainer (&spContainer);

		CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spDoc (spContainer);
		CComPtr <IHTMLLocation> spHtmlLocation;

		if (spDoc)
		{
			spDoc->get_location (&spHtmlLocation);

			spHtmlLocation->get_hostname (&bstrHostName);
			
			*tbstrHostName		=	bstrHostName;
		}
		else
			retVal = E_FAIL;
	}

	return retVal;
}

/*
STDMETHODIMP CSignAttributes::get_HostName(BSTR *tbstrHostName)
{
	HRESULT retVal = S_OK;

	BSTR bstrHostName;
	CComPtr <IOleContainer>		spContainer;

	if(m_spClientSite)
	{
		//::MessageBox( NULL, "Inside HostName", "HostName", MB_OK | MB_ICONINFORMATION );
		m_spClientSite->GetContainer (&spContainer);

		CComQIPtr<IHTMLDocument2, &IID_IHTMLDocument2> spDoc (spContainer);
		CComPtr <IHTMLLocation> spHtmlLocation;

		if (spDoc)
		{
			spDoc->get_location (&spHtmlLocation);

			spHtmlLocation->get_hostname (&bstrHostName);

			//::MessageBoxW( NULL, bstrHostName, L"HostName", MB_OK | MB_ICONINFORMATION );
			
			*tbstrHostName	=	bstrHostName;
		}
		else
			retVal = E_FAIL;
	}

	return retVal;

}

STDMETHODIMP CSignAttributes::put_HostName(BSTR newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
*/

STDMETHODIMP CSignAttributes::get_AuthEncUserSMIMECertificate(BSTR *pVal)
{
	
	if ( !(m_hCertStore = CertOpenSystemStore(NULL, "MY")) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertOpenSystemStore falied") ;
		return m_dwErrorCode ;
	}

	PCCERT_CONTEXT	pSearchCert = NULL ;
	
	if ( (pSearchCert = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							m_pbUserCertificate, 
							m_cbUserCertificate)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertCreateCertificateContext falied") ;
		return m_dwErrorCode ;
	}


	PCCERT_CONTEXT  pSignerCert ;
	if ( (pSignerCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_PUBLIC_KEY,            // Find type
              &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
              NULL)) == NULL )               // Previous context
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertFindCertificateInStore falied") ;
		return m_dwErrorCode ;
	}

	if (pSearchCert)
		CertFreeCertificateContext(pSearchCert) ;

	CHAR							szMessage[] = {"Empty String"} ;
	DWORD							MessageSizeArray[1] ;
	CHAR							szStringToBeSigned[512];
	
	BSTR bstrHostName = NULL;
	HRESULT hr = S_OK;

	
	//::MessageBox( NULL, szStringToBeSigned, "StringTobeSigned", MB_OK | MB_ICONINFORMATION );

	hr = _GetHostName(&bstrHostName);

	if(hr != S_OK)
	{
		::MessageBox( NULL, "HostNameFailed", "SignAttributes", MB_OK | MB_ICONINFORMATION );
		
	}
		
	PCHAR szHostName = _WideToMultiString(bstrHostName);
	//::MessageBox( NULL, szTemp, "SignAttributes", MB_OK | MB_ICONINFORMATION );

	strcpy(szStringToBeSigned, szHostName);
	strcat(szStringToBeSigned,m_ChallengePhrase);
	strcat(szStringToBeSigned, PRECANNED_HEADER);

	BYTE			*MessageArray[] = { (unsigned char *)szStringToBeSigned };

	MessageSizeArray[0] = strlen(szStringToBeSigned) ;

   
	PCCERT_CONTEXT					*MsgCertArray ;
	DWORD							i ;

	PCCERT_CONTEXT_LIST		pTempCertContextList = NULL ;

	MsgCertArray = (PCCERT_CONTEXT *) malloc(sizeof(PCCERT_CONTEXT)*(m_dwNumberOfCACerts+1)) ;

	pTempCertContextList = m_pCertContextList ;

	for ( i = 0 ; i < m_dwNumberOfCACerts+1 ; i++ )
	{
		MsgCertArray[i] = pTempCertContextList->pCertContext ;
		pTempCertContextList = pTempCertContextList->nextCertContext ;
	}

	CRYPT_ALGORITHM_IDENTIFIER		HashAlgorithm ;
	DWORD							HashAlgSize  = sizeof(HashAlgorithm);
	memset(&HashAlgorithm, 0, HashAlgSize) ;	// Init. to zero.
    //HashAlgorithm.pszObjId = szOID_RSA_MD5 ;	// Then set the necessary field.
	HashAlgorithm.pszObjId = szOID_OIWSEC_sha1;//NP  //change the signing algo to SHA-1


	CRYPT_SIGN_MESSAGE_PARA			SigParams ;
	DWORD							SigParamsSize = sizeof(SigParams) ;
	memset(&SigParams, 0, SigParamsSize) ;

	SigParams.cbSize = SigParamsSize ;
	SigParams.dwMsgEncodingType = MY_ENCODING_TYPE ;
	SigParams.pSigningCert = pSignerCert ;
	SigParams.HashAlgorithm = HashAlgorithm ;
	SigParams.cMsgCert = m_dwNumberOfCACerts + 1 ; // add one for end-entity cert.
	SigParams.rgpMsgCert = MsgCertArray;

	CRYPT_ATTRIBUTE		authAttribute[2] ;
	CHAR				sz1OID[] = {"1.2.840.113549.1.9.15"} ; // sMIMECapabilities OID
	CHAR				sz2OID[] = {"1.3.6.1.4.1.311.16.4"} ; // Unknown OID
	DWORD					dwCryptKeyProvInfo = 0 ;
	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						NULL,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	PCHAR	buff = (PCHAR) malloc(dwCryptKeyProvInfo) ;

	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						buff,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	CRYPT_KEY_PROV_INFO	*pCryptKeyProvInfo ;

	pCryptKeyProvInfo = (CRYPT_KEY_PROV_INFO *)buff ;

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	PCHAR	szProviderName = _WideToMultiString(pCryptKeyProvInfo->pwszProvName) ;
	PCHAR	szContainerName = _WideToMultiString(pCryptKeyProvInfo->pwszContainerName) ;

	HCRYPTPROV	hCryptProv = NULL ;
	if ( !CryptAcquireContext(
							&hCryptProv,
							szContainerName,
							szProviderName,
							PROV_RSA_FULL,
							0) )
	{
		_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CryptAcquireContext falied") ;
		return m_dwErrorCode ;
	}

	DWORD		dwFlags = 0, dwDataLen = 0, dwBits = 0, dwNameLen ;
	BYTE		pbData[1000], *ptr = NULL ;
	CHAR		szName[100], *pszAlgType = NULL ;
	ALG_ID		aiAlgid ;
	// Enumerate the supported algorithms.
	for(i=0 ; ; i++) 
	{
		// Set the CRYPT_FIRST flag the first time through the loop.
		if(i == 0) 
		{
			dwFlags = CRYPT_FIRST;
		} else 
		{
			dwFlags = 0;
		}

		// Retrieve information about an algorithm.
		dwDataLen = 1000;
		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &dwDataLen, dwFlags)) 
		{
			if(GetLastError() == ERROR_NO_MORE_ITEMS) 
			{
				// Exit the loop.
				break;
			}
			else 
			{
				_ShowErrorMessage(GetLastError(), "get_EncUserSMIMECertificate : CryptGetProvParam falied : Error reading algorithm") ;
				return m_dwErrorCode ;
			}
		}

		// Extract algorithm information from 'pbData' buffer.
		ptr = pbData;
		aiAlgid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		dwNameLen = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		strncpy(szName, (const char *)ptr,dwNameLen);

		// Determine algorithm type.
		switch(GET_ALG_CLASS(aiAlgid)) 
		{
			case ALG_CLASS_DATA_ENCRYPT: 
						pszAlgType = "Encrypt  ";
						break;
			case ALG_CLASS_HASH:	 
						pszAlgType = "Hash     ";
						break;
			case ALG_CLASS_KEY_EXCHANGE: 
						pszAlgType = "Exchange ";
						break;
			case ALG_CLASS_SIGNATURE:	 
						pszAlgType = "Signature";
						break;
			default:			 
						pszAlgType = "Unknown  ";
		}

		CHAR		szAlgorithm[1000] ;

		sprintf(szAlgorithm, "%s-%d", szName, dwBits) ;

		if ( strcmp(szAlgorithm, "RC2-40") == 0 )
		{
			// Add RC2CBC 40-bits	
			DWORD dwEncryptionStrength = 40 ;
			CUniversalInteger	uiNumberOfBits40(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC40(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC40 ;
			bdcRC2CBC40 = oidRC2CBC40 + uiNumberOfBits40 ;
			CSequence		seqRC2CBC40 ;
			seqRC2CBC40 = bdcRC2CBC40 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC40 ;
		}
		else if ( strcmp(szAlgorithm, "RC2-128") == 0 )
		{
			// Add RC2CBC 128-bits	
			DWORD dwEncryptionStrength = 128 ;
			CUniversalInteger	uiNumberOfBits128(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC128(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC128 ;
			bdcRC2CBC128 = oidRC2CBC128 + uiNumberOfBits128 ;
			CSequence		seqRC2CBC128 ;
			seqRC2CBC128 = bdcRC2CBC128 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC128 ;
		}
		else if ( strcmp(szAlgorithm, "DES-56") == 0 )
		{
			// Add desCBC
			CObjectIdentifier	oidDESCBC(
											strlen((const char *)szOID_OIWSEC_desCBC),
											(_PBYTE)szOID_OIWSEC_desCBC
										 ) ;
			CBaseDERCollection	bdcDESCBC ;
			bdcDESCBC = oidDESCBC ;
			CSequence		seqDESCBC ;
			seqDESCBC = bdcDESCBC ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqDESCBC ;
		}
		else if ( strcmp(szAlgorithm, "3DES-168") == 0 )
		{
			// Add 3DES
			CObjectIdentifier	oid3DES(
											strlen((const char *)szOID_RSA_DES_EDE3_CBC),
											(_PBYTE)szOID_RSA_DES_EDE3_CBC
										 ) ;
			CBaseDERCollection	bdc3DES ;
			bdc3DES = oid3DES ;
			CSequence		seq3DES ;
			seq3DES = bdc3DES ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seq3DES ;
		}
		else if ( strcmp(szAlgorithm, "MD5-128") == 0 )
		{
			// Add MD5
			CObjectIdentifier	oidMD5(
											strlen((const char *)szOID_RSA_MD5),
											(_PBYTE)szOID_RSA_MD5
										 ) ;
			CBaseDERCollection	bdcMD5 ;
			bdcMD5 = oidMD5 ;
			CSequence		seqMD5 ;
			seqMD5 = bdcMD5 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5 ;
		}
		else if ( strcmp(szAlgorithm, "MD4-128") == 0 )
		{
			// Add MD4
			CObjectIdentifier	oidMD4(
											strlen((const char *)szOID_RSA_MD4),
											(_PBYTE)szOID_RSA_MD4
										 ) ;
			CBaseDERCollection	bdcMD4 ;
			bdcMD4 = oidMD4 ;
			CSequence		seqMD4 ;
			seqMD4 = bdcMD4 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD4 ;
		}
		else if ( strcmp(szAlgorithm, "MD2-128") == 0 )
		{
			// Add MD2
			CObjectIdentifier	oidMD2(
											strlen((const char *)szOID_RSA_MD2),
											(_PBYTE)szOID_RSA_MD2
										 ) ;
			CBaseDERCollection	bdcMD2 ;
			bdcMD2 = oidMD2 ;
			CSequence		seqMD2 ;
			seqMD2 = bdcMD2 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD2 ;
		}
		else if ( strcmp(szAlgorithm, "SHA-1-160") == 0 )
		{
			// Add SHA-1
			CObjectIdentifier	oidSHA1(
											strlen((const char *)szOID_OIWSEC_sha1),
											(_PBYTE)szOID_OIWSEC_sha1
										 ) ;
			CBaseDERCollection	bdcSHA1 ;
			bdcSHA1 = oidSHA1 ;
			CSequence		seqSHA1 ;
			seqSHA1 = bdcSHA1 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1 ;
		}
		else if ( (strcmp(szAlgorithm, "RSA_KEYX-1024") == 0) || (strcmp(szAlgorithm, "RSA_KEYX-512") == 0) )
		{
			// Add SHA1RSA
			CObjectIdentifier	oidSHA1RSA(
											strlen((const char *)szOID_RSA_SHA1RSA),
											(_PBYTE)szOID_RSA_SHA1RSA
										 ) ;
			CBaseDERCollection	bdcSHA1RSA ;
			bdcSHA1RSA = oidSHA1RSA ;
			CSequence		seqSHA1RSA ;
			seqSHA1RSA = bdcSHA1RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1RSA ;

			// Add MD5RSA
			CObjectIdentifier	oidMD5RSA(
											strlen((const char *)szOID_RSA_MD5RSA),
											(_PBYTE)szOID_RSA_MD5RSA
										 ) ;
			CBaseDERCollection	bdcMD5RSA ;
			bdcMD5RSA = oidMD5RSA ;
			CSequence		seqMD5RSA ;
			seqMD5RSA = bdcMD5RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5RSA ;
		}
	}

	CSequence			seqSMIMECapabilitiesSupported(bdcSMIMECapabilitiesSupported) ;

	DWORD				cbEncoded ;
	PBYTE				pbEncoded ;

	pbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->pbData ;
	cbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->cbData ;
	BYTE		pbEncoded2[5000], reversed[1024] ;
	DWORD		cbEncoded2, derSize ;

	derSize = pSignerCert->pCertInfo->Issuer.cbData +
			  2 +
			  pSignerCert->pCertInfo->SerialNumber.cbData ;

	// SEQUENCE
	pbEncoded2[0] = 0x30 ;
	pbEncoded2[1] = 0x82 ;
	pbEncoded2[2] = (BYTE)((derSize & 0x0000FF00) >> 8) ;
	pbEncoded2[3] = (BYTE)(derSize & 0x000000FF) ;
		// Issuer DN
		memcpy(pbEncoded2+4, pSignerCert->pCertInfo->Issuer.pbData, pSignerCert->pCertInfo->Issuer.cbData) ;
		// End-user certificate serial number
		pbEncoded2[4+pSignerCert->pCertInfo->Issuer.cbData] = 0x02 ;
		pbEncoded2[4+pSignerCert->pCertInfo->Issuer.cbData+1] = (unsigned char) pSignerCert->pCertInfo->SerialNumber.cbData ;
			for ( i = 0 ; i < pSignerCert->pCertInfo->SerialNumber.cbData ; i++ )
				reversed[pSignerCert->pCertInfo->SerialNumber.cbData-i-1] = pSignerCert->pCertInfo->SerialNumber.pbData[i] ;
			memcpy(pbEncoded2+4 + pSignerCert->pCertInfo->Issuer.cbData+2, reversed, pSignerCert->pCertInfo->SerialNumber.cbData) ;

	cbEncoded2 = 4 +
				 pSignerCert->pCertInfo->Issuer.cbData +
				 2 +
				 pSignerCert->pCertInfo->SerialNumber.cbData ;
				 
	CRYPT_ATTR_BLOB		authAttrBlob, authAttrBlob2 ;

	authAttrBlob.cbData = cbEncoded ;
	authAttrBlob.pbData = pbEncoded ;

	authAttrBlob2.cbData = cbEncoded2 ;
	authAttrBlob2.pbData = pbEncoded2 ;

	authAttribute[0].pszObjId = sz1OID ; // sMIMECapabilities OID
	authAttribute[0].cValue = 1 ;
	authAttribute[0].rgValue = &authAttrBlob ;

	authAttribute[1].pszObjId = sz2OID ; // Unknown OID
	authAttribute[1].cValue = 1 ;
	authAttribute[1].rgValue = &authAttrBlob2 ;

	SigParams.cAuthAttr = 2 ;
	SigParams.rgAuthAttr = authAttribute ;

	// Get the size of the output SignedBlob.
	DWORD    cbSignedMessageBlob = NULL ;

	if ( !CryptSignMessage(
          &SigParams,            // Signature parameters
          FALSE,                 // Not detached
          1,                     // Number of messages
          (const BYTE **)MessageArray,          // Messages to be signed
          MessageSizeArray,      // Size of messages
          NULL,                  // Buffer for signed msg
          &cbSignedMessageBlob) ) // Size of buffer
	{
		_ShowErrorMessage(GetLastError(), "Update : CryptSignMessage falied") ;
		return m_dwErrorCode ;
	}

	// Allocate memory for the signed blob.
	BYTE	*pbSignedMessageBlob ;
	pbSignedMessageBlob = (BYTE*)malloc(cbSignedMessageBlob) ;
	memset(pbSignedMessageBlob, 49, cbSignedMessageBlob) ;

	// Get the SignedMessageBlob.
	if ( !CryptSignMessage(
          &SigParams,            // Signature parameters
          FALSE,                 // Not detached
          1,                     // Number of messages
          (const BYTE **)MessageArray,          // Messages to be signed
          MessageSizeArray,      // Size of messages
          pbSignedMessageBlob,   // Buffer for signed msg
          &cbSignedMessageBlob) ) // Size of buffer
	{
		_ShowErrorMessage(GetLastError(), "Update : CryptSignMessage falied") ;
		return m_dwErrorCode ;
	}

	m_cbUserSMIMECertificate = cbSignedMessageBlob ;
	m_pbUserSMIMECertificate = pbSignedMessageBlob ;

	CHAR		temp[10] ;
	m_szUserSMIMECertificate = (LPSTR) malloc(m_cbUserSMIMECertificate*2+1) ;

	for ( i = 0 ; i < m_cbUserSMIMECertificate ; i++ )
	{
		itoa((int)m_pbUserSMIMECertificate[i], temp, 16) ;
		m_szUserSMIMECertificate[i*2] = (strlen(temp) == 2) ? temp[0] : '0' ;
		m_szUserSMIMECertificate[i*2+1] = (strlen(temp) == 2) ? temp[1] : temp[0] ;
	}
	m_szUserSMIMECertificate[m_cbUserSMIMECertificate*2] = '\0' ;

	BSTR		bstrRetVal = _MultiToWideString(m_szUserSMIMECertificate) ;
	
	*pVal = bstrRetVal ;

	return S_OK;
}

//HRESULT CSignAttributes::_GetCertCount(HCERTSTORE hCertStore, PCHAR pszRFC822Name, PCHAR pszSubjectName, PCHAR pszIssuerName, BOOL bIntentedUsageBoth,int *nCount)
HRESULT CSignAttributes::_GetCertCount(HCERTSTORE hCertStore, WCHAR* pwszRFC822Name, 
									   WCHAR* pwszSubjectName, WCHAR* pwszIssuerName, BOOL bIntentedUsageBoth,int *nCount)

{
	
	m_dwErrorCode = S_OK ;

	PCCERT_CONTEXT  pCertContext=NULL;  
	//char pszNameString[256];
	WCHAR pwszNameString[256];
	int count = 0;

	while(pCertContext= CertEnumCertificatesInStore(
			hCertStore,
			pCertContext))
	{
		
		if(CertGetNameStringW(
		   pCertContext,
		   CERT_NAME_EMAIL_TYPE,
		   0,
		   NULL,
		   pwszNameString,
		   128))
		{
		   
		   if(wcscmp(pwszRFC822Name,pwszNameString)==0)
		   {
					
			   		if(CertGetNameStringW(
					   pCertContext,
					   CERT_NAME_RDN_TYPE,
					   0,
					   NULL,
					   pwszNameString,
					   256))
					{
						
						if(wcscmp(pwszSubjectName,pwszNameString)==0)
						{
				   			if(CertGetNameStringW(
						    pCertContext,
							CERT_NAME_RDN_TYPE,
							CERT_NAME_ISSUER_FLAG,
							NULL,
							pwszNameString,
							256))
							{
								if(wcscmp(pwszIssuerName,pwszNameString)==0)
								{

									//count ++;
									DWORD cbData;
									PBYTE pvData;

									if(!(CertGetCertificateContextProperty(
									pCertContext, 
									CERT_FRIENDLY_NAME_PROP_ID, 
									NULL, 
									&cbData)) )
									{
										 continue;
									}
									if(!(pvData = (PBYTE)malloc(cbData)))
									  {
											_ShowErrorMessage(GetLastError(), "_GetCertCount: allocation failed") ;
											return m_dwErrorCode ;
									  }
										  
									  if(!(CertGetCertificateContextProperty(
										  pCertContext,
										  CERT_FRIENDLY_NAME_PROP_ID,
										  pvData, 
										  &cbData)))
									  {
											 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetCertificateContextProperty falied") ;
											return m_dwErrorCode ;
									  }
									  else
									  {
										 WCHAR *pwszTemp = NULL;
										 pwszTemp = wcschr((WCHAR *)pvData, L'#');
										 if(pwszTemp)
										 {
											 BOOL bUsage;
											BYTE pbUsage;
											DWORD dwBytes = 1;

											//CRYPT_DATA_BLOB  Friendly_Name_Blob={256,szUsage};
											
											bUsage = CertGetIntendedKeyUsage(
												X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
												pCertContext->pCertInfo,
												&pbUsage,
												dwBytes);
											if(!bUsage)
												continue;
											
											if(bIntentedUsageBoth == TRUE)
											{

												if(pbUsage == (CERT_DIGITAL_SIGNATURE_KEY_USAGE | CERT_KEY_ENCIPHERMENT_KEY_USAGE) )
												{
													 count ++;
												}
											}
											else
											{
												if(pbUsage == CERT_KEY_ENCIPHERMENT_KEY_USAGE)
												{
													count ++;
												}
											}
										 }
									  }
								}
										

							}
							else
							{
									 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
									return m_dwErrorCode ;
							}

						}

					}
					else
					{
							 _ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
							return m_dwErrorCode ;
					}
		   }



			   
		}
		else
		{
			_ShowErrorMessage(GetLastError(), "_GetCertCount : CertGetName falied") ;
			return m_dwErrorCode ;
		}

	}
	if(pCertContext)
	{
		CertFreeCertificateContext(pCertContext);
	}

	*nCount = count;
	return m_dwErrorCode;

}

// Start Add: Infosys : CR27993
/*****************************************************************************/
// get_SMIMECapabilityBlob() : Creates SMIME capability ASN1 encoded blob. This
//							   is required for setting the security properties.
//							   SMIME Capabilities specify the algorithm supported 
//							   by the CSP to which the certificate belongs.
//
//  Input/Output :
//	  cbSMIMECapabilityBlobSize : USHORT *
//				  While input specifies the size available for the output blob.
//                Specifies the actual number of bytes written in the output blob.
//				  If it is zero the SMIME capability blob could not be created.
//	  pVal : BYTE *
//				  SMIME Capability Blob is written into this.
//  Returns :
//    S_OK, MAPI Error Code
/*****************************************************************************/

STDMETHODIMP CSignAttributes::get_SMIMECapabilityBlob(USHORT *cbSMIMECapabilityBlobSize, BYTE *pVal)
{
	// Get the details for the certificate used.
	// Open the certificate store
	if ( !(m_hCertStore = CertOpenSystemStore(NULL, "MY")) )
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CertOpenSystemStore falied") ;
		return m_dwErrorCode ;
	}

	// Create Certificate context, the values of m_pbUserCertificate and m_cbUserCertificate
	// are already set by an earlier call to put_userCertificate.
	PCCERT_CONTEXT	pSearchCert = NULL ;
	
	if ( (pSearchCert = CertCreateCertificateContext(
							X509_ASN_ENCODING, 
							m_pbUserCertificate, 
							m_cbUserCertificate)) == NULL )
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CertCreateCertificateContext falied") ;
		return m_dwErrorCode ;
	}

	// Validate that the certificate is present in the certificate store.
	PCCERT_CONTEXT  pSignerCert ;

	if ( (pSignerCert = CertFindCertificateInStore(
              m_hCertStore,				     // Store handle
              MY_ENCODING_TYPE,              // Encoding type
              0,                             // Not used
              CERT_FIND_PUBLIC_KEY,            // Find type
              &pSearchCert->pCertInfo->SubjectPublicKeyInfo,					 // Name string
              NULL)) == NULL )               // Previous context
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CertFindCertificateInStore falied") ;
		return m_dwErrorCode ;
	}

	// Search is successful free the context variable for search
	if (pSearchCert)
	{
		CertFreeCertificateContext(pSearchCert) ;
	}

	HRESULT hr = S_OK;

	// Size of structure required for key provider info data
	DWORD					dwCryptKeyProvInfo = 0 ;

	// Get information about the CSP using two subsequent calls
	// Get the size of buffer to be allocated
	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						NULL,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	PCHAR	buff = (PCHAR) malloc(dwCryptKeyProvInfo) ;
	
	// Get the buffer containg CSP information
	if ( !CertGetCertificateContextProperty(
						pSignerCert,
						CERT_KEY_PROV_INFO_PROP_ID,
						buff,
						&dwCryptKeyProvInfo) )
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CertGetCertificateContextProperty falied") ;
		return m_dwErrorCode ;
	}

	// Typecast the buffer data to CSP information structure.
	CRYPT_KEY_PROV_INFO	*pCryptKeyProvInfo ;

	pCryptKeyProvInfo = (CRYPT_KEY_PROV_INFO *)buff ;

	CBaseDERCollection	bdcSMIMECapabilitiesSupported ;

	PCHAR	szProviderName = _WideToMultiString(pCryptKeyProvInfo->pwszProvName) ;
	PCHAR	szContainerName = _WideToMultiString(pCryptKeyProvInfo->pwszContainerName) ;

	HCRYPTPROV	hCryptProv = NULL ;

	// Get handle to the provider.
	if ( !CryptAcquireContext(
							&hCryptProv,
							szContainerName,
							szProviderName,
							PROV_RSA_FULL,
							0) )
	{
		_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CryptAcquireContext falied") ;
		return m_dwErrorCode ;
	}

	DWORD		dwFlags = 0, dwDataLen = 0, dwBits = 0, dwNameLen ;
	BYTE		pbData[1000], *ptr = NULL ;
	CHAR		szName[100], *pszAlgType = NULL ;
	ALG_ID		aiAlgid ;

	// Enumerate the algorithms supported by CSP.
	for(int i=0 ; ; i++) 
	{
		// Set the CRYPT_FIRST flag the first time through the loop.
		if(i == 0) 
		{
			dwFlags = CRYPT_FIRST;
		} else 
		{
			dwFlags = 0;
		}

		// Retrieve information about an algorithm.
		dwDataLen = 1000;
		if(!CryptGetProvParam(hCryptProv, PP_ENUMALGS, pbData, &dwDataLen, dwFlags)) 
		{
			if(GetLastError() == ERROR_NO_MORE_ITEMS) 
			{
				// Exit the loop.
				break;
			}
			else 
			{
				_ShowErrorMessage(GetLastError(), "get_SMIMECapabilityBlob : CryptGetProvParam falied : Error reading algorithm") ;
				return m_dwErrorCode ;
			}
		}

		// Extract algorithm information from 'pbData' buffer.
		ptr = pbData;
		aiAlgid = *(ALG_ID *)ptr;
		ptr += sizeof(ALG_ID);
		dwBits = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		dwNameLen = *(DWORD *)ptr;
		ptr += sizeof(DWORD);
		strncpy(szName, (const char *)ptr,dwNameLen);

		// Determine algorithm type.
		switch(GET_ALG_CLASS(aiAlgid)) 
		{
			case ALG_CLASS_DATA_ENCRYPT: 
						pszAlgType = "Encrypt  ";
						break;
			case ALG_CLASS_HASH:	 
						pszAlgType = "Hash     ";
						break;
			case ALG_CLASS_KEY_EXCHANGE: 
						pszAlgType = "Exchange ";
						break;
			case ALG_CLASS_SIGNATURE:	 
						pszAlgType = "Signature";
						break;
			default:			 
						pszAlgType = "Unknown  ";
		}

		CHAR		szAlgorithm[1000] ;

		sprintf(szAlgorithm, "%s-%d", szName, dwBits) ;

		// Create data specific to the algorithm type found and append it to the 
		// supported algorithm list.
		if ( strcmp(szAlgorithm, "RC2-40") == 0 )
		{
			// Add RC2CBC 40-bits	
			DWORD dwEncryptionStrength = 40 ;
			CUniversalInteger	uiNumberOfBits40(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC40(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC40 ;
			bdcRC2CBC40 = oidRC2CBC40 + uiNumberOfBits40 ;
			CSequence		seqRC2CBC40 ;
			seqRC2CBC40 = bdcRC2CBC40 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC40 ;
		}
		else if ( strcmp(szAlgorithm, "RC2-128") == 0 )
		{
			// Add RC2CBC 128-bits	
			DWORD dwEncryptionStrength = 128 ;
			CUniversalInteger	uiNumberOfBits128(2, (_PBYTE)&dwEncryptionStrength) ;
			CObjectIdentifier	oidRC2CBC128(
											strlen((const char *)szOID_RSA_RC2CBC),
											(_PBYTE)szOID_RSA_RC2CBC
										 ) ;
			CBaseDERCollection	bdcRC2CBC128 ;
			bdcRC2CBC128 = oidRC2CBC128 + uiNumberOfBits128 ;
			CSequence		seqRC2CBC128 ;
			seqRC2CBC128 = bdcRC2CBC128 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqRC2CBC128 ;
		}
		else if ( strcmp(szAlgorithm, "DES-56") == 0 )
		{
			// Add desCBC
			CObjectIdentifier	oidDESCBC(
											strlen((const char *)szOID_OIWSEC_desCBC),
											(_PBYTE)szOID_OIWSEC_desCBC
										 ) ;
			CBaseDERCollection	bdcDESCBC ;
			bdcDESCBC = oidDESCBC ;
			CSequence		seqDESCBC ;
			seqDESCBC = bdcDESCBC ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqDESCBC ;
		}
		else if ( strcmp(szAlgorithm, "3DES-168") == 0 )
		{
			// Add 3DES
			CObjectIdentifier	oid3DES(
											strlen((const char *)szOID_RSA_DES_EDE3_CBC),
											(_PBYTE)szOID_RSA_DES_EDE3_CBC
										 ) ;
			CBaseDERCollection	bdc3DES ;
			bdc3DES = oid3DES ;
			CSequence		seq3DES ;
			seq3DES = bdc3DES ;
			// Add 3DES at the beginning of list of encryption algorithms. artf39000
			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported % seq3DES ;
		}
		else if ( strcmp(szAlgorithm, "MD5-128") == 0 )
		{
			// Add MD5
			CObjectIdentifier	oidMD5(
											strlen((const char *)szOID_RSA_MD5),
											(_PBYTE)szOID_RSA_MD5
										 ) ;
			CBaseDERCollection	bdcMD5 ;
			bdcMD5 = oidMD5 ;
			CSequence		seqMD5 ;
			seqMD5 = bdcMD5 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5 ;
		}
		else if ( strcmp(szAlgorithm, "MD4-128") == 0 )
		{
			// Add MD4
			CObjectIdentifier	oidMD4(
											strlen((const char *)szOID_RSA_MD4),
											(_PBYTE)szOID_RSA_MD4
										 ) ;
			CBaseDERCollection	bdcMD4 ;
			bdcMD4 = oidMD4 ;
			CSequence		seqMD4 ;
			seqMD4 = bdcMD4 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD4 ;
		}
		else if ( strcmp(szAlgorithm, "MD2-128") == 0 )
		{
			// Add MD2
			CObjectIdentifier	oidMD2(
											strlen((const char *)szOID_RSA_MD2),
											(_PBYTE)szOID_RSA_MD2
										 ) ;
			CBaseDERCollection	bdcMD2 ;
			bdcMD2 = oidMD2 ;
			CSequence		seqMD2 ;
			seqMD2 = bdcMD2 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD2 ;
		}
		else if ( strcmp(szAlgorithm, "SHA-1-160") == 0 )
		{
			// Add SHA-1
			CObjectIdentifier	oidSHA1(
											strlen((const char *)szOID_OIWSEC_sha1),
											(_PBYTE)szOID_OIWSEC_sha1
										 ) ;
			CBaseDERCollection	bdcSHA1 ;
			bdcSHA1 = oidSHA1 ;
			CSequence		seqSHA1 ;
			seqSHA1 = bdcSHA1 ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1 ;
		}
		else if ( (strcmp(szAlgorithm, "RSA_KEYX-1024") == 0) || (strcmp(szAlgorithm, "RSA_KEYX-512") == 0) )
		{
			// Add SHA1RSA
			CObjectIdentifier	oidSHA1RSA(
											strlen((const char *)szOID_RSA_SHA1RSA),
											(_PBYTE)szOID_RSA_SHA1RSA
										 ) ;
			CBaseDERCollection	bdcSHA1RSA ;
			bdcSHA1RSA = oidSHA1RSA ;
			CSequence		seqSHA1RSA ;
			seqSHA1RSA = bdcSHA1RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqSHA1RSA ;

			// Add MD5RSA
			CObjectIdentifier	oidMD5RSA(
											strlen((const char *)szOID_RSA_MD5RSA),
											(_PBYTE)szOID_RSA_MD5RSA
										 ) ;
			CBaseDERCollection	bdcMD5RSA ;
			bdcMD5RSA = oidMD5RSA ;
			CSequence		seqMD5RSA ;
			seqMD5RSA = bdcMD5RSA ;

			bdcSMIMECapabilitiesSupported = bdcSMIMECapabilitiesSupported + seqMD5RSA ;
		}
	}

	// Create ASN1 encoded blob from the Capabilities string
	CSequence			seqSMIMECapabilitiesSupported(bdcSMIMECapabilitiesSupported) ;
	DWORD				cbEncoded ;
	PBYTE				pbEncoded ;

	pbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->pbData ;
	cbEncoded = seqSMIMECapabilitiesSupported.BaseDERBlob->cbData ;

	// Check if the maximum size available for the buffer is less then the actual data length
	// then reset it to reflect actual length of data written into the buffer.
	if (*cbSMIMECapabilityBlobSize > cbEncoded)
	{
		// Return the size of memory to be allocated
		*cbSMIMECapabilityBlobSize = cbEncoded;
	}
	
	// Copy the data blob
	memcpy (pVal, pbEncoded, *cbSMIMECapabilityBlobSize);
	
	return S_OK;
}
// End Add: Infosys : CR27993
