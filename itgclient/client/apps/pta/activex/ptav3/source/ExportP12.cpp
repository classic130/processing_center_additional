///		ExportP12.cpp - Export P12 functionality

#include "stdafx.h"
#include "ExportP12.h"
#include "ptaerrs.h"
#include "P12Helper.h"
#include "integrate.h"
#include "MyUniversalInteger.h"
#include "pkcs12macros.h"
#include "utils.h"

#define	HMAC_SHA1_DIGEST_LEN		20
#define	VS_P12_VERSION				3

CExportP12::CExportP12()
{
	m_tbstrPassword = "";
	m_tbstrFriendlyName = "";
	return;
}

CExportP12::~CExportP12()
{
	return;
}


HRESULT		CExportP12::Initialize
(
	const DWORD					i_cdwTypeOfOutput
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
			//	check input parameters
		if ( (PKCS12INFO_FILENAME != i_cdwTypeOfOutput) && (PKCS12INFO_BYTE_BLOB_P12 != i_cdwTypeOfOutput) )
		{
			hResult =	E_P12E_WRONG_TYPE;
			break;
		}

		m_dwTypeOfOutput =	i_cdwTypeOfOutput;

		m_dwInitialized =	1;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::Initialize


HRESULT		CExportP12::SetNumberOfCerts
(
	const DWORD					i_cdwNumberOfCerts
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	check input parameters
		if ( 0 >= i_cdwNumberOfCerts )
		{
			hResult =	E_P12E_ZERO_CERTS_NOT_ALLOWED;
			break;
		}

				//	allocate required memory for the cert blobs and its lengths
		m_dwNumberOfCerts =	i_cdwNumberOfCerts;

		m_pdwCertBlobLen =	new DWORD [m_dwNumberOfCerts];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pdwCertBlobLen)

		m_ppbyteCertBlob =	new BYTE* [m_dwNumberOfCerts];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_ppbyteCertBlob)

		for ( int i = 0; i < m_dwNumberOfCerts; i++ )
		{
			m_ppbyteCertBlob[i] = NULL;
		}

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::SetNumberOfCerts


HRESULT		CExportP12::SetCertBlob
(
	const DWORD					i_cdwCertNumber,
	const BYTE*					i_cpbyteCertBlob,
	const DWORD					i_cdwCertBlobLen
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	check input parameters
		if ( (m_dwNumberOfCerts < i_cdwCertNumber) || (0 > i_cdwCertNumber) )
		{
			hResult =	E_P12E_CANNOT_SET_CERT;
			break;
		}
		if ( 0 >= i_cdwCertBlobLen )
		{
			hResult =	E_P12E_CERT_LEN_ZERO;
			break;
		}

				//	add the cert blob and its length in the array
		m_pdwCertBlobLen[i_cdwCertNumber] = i_cdwCertBlobLen;
		m_ppbyteCertBlob[i_cdwCertNumber] = new BYTE [i_cdwCertBlobLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY((m_ppbyteCertBlob[i_cdwCertNumber]))

		::memcpy
		(
			(void*) m_ppbyteCertBlob[i_cdwCertNumber],
			(const void *) i_cpbyteCertBlob,
			i_cdwCertBlobLen
		);

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::SetCertBlob


HRESULT		CExportP12::SetKey
(
		const BYTE*					i_cpbytePrivateKeyBlob,
		const DWORD					i_cdwPrivateKeyBlobLen,
		const BYTE*					i_cpbytePublicKeyBlob,
		const DWORD					i_cdwPublicKeyBlobLen
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	check input parameters
		if ( 0 >= i_cdwPrivateKeyBlobLen || 0 >= i_cdwPublicKeyBlobLen)
		{
			hResult =	E_P12E_KEY_LEN_ZERO;
			break;
		}

		if ( NULL == i_cpbytePrivateKeyBlob || NULL == i_cpbytePublicKeyBlob )
		{
			hResult =	E_P12E_KEY_NULL;
			break;
		}

				//	store the private key in the data members
		m_dwPrivateKeyBlobLen =	i_cdwPrivateKeyBlobLen;
		m_pbytePrivateKeyBlob = new BYTE [i_cdwPrivateKeyBlobLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbytePrivateKeyBlob)

		::memcpy
		(
			(void*) m_pbytePrivateKeyBlob,
			(const void *) i_cpbytePrivateKeyBlob,
			i_cdwPrivateKeyBlobLen
		);

		hResult =	GetKeyFromBlob
					(
						m_pbytePrivateKeyBlob,
						m_dwPrivateKeyBlobLen,
						&m_RSAKey_PrivateKey
					);
		PKCS12_CHECK_HRESULT

				//	store the public key in the data members
		m_dwPublicKeyBlobLen =	i_cdwPublicKeyBlobLen;
		m_pbytePublicKeyBlob = new BYTE [i_cdwPublicKeyBlobLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbytePublicKeyBlob)

		::memcpy
		(
			(void*) m_pbytePublicKeyBlob,
			(const void *) i_cpbytePublicKeyBlob,
			i_cdwPublicKeyBlobLen
		);

		hResult =	GetKeyFromBlob
					(
						m_pbytePublicKeyBlob,
						m_dwPublicKeyBlobLen,
						&m_RSAKey_PublicKey
					);
		PKCS12_CHECK_HRESULT
		
		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::SetPrivateKey


HRESULT		CExportP12::SetPassword
(
	const _bstr_t					i_ctbstrPassword
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
		m_tbstrPassword =	i_ctbstrPassword;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::SetPassword



HRESULT		CExportP12::SetFriendlyName
(
	_bstr_t						i_tbstrFriendlyName
)
{
	if ( 0 < ::strlen(i_tbstrFriendlyName) )
	{
		m_tbstrFriendlyName =	i_tbstrFriendlyName;
	}

	return	S_OK;
}	//	end		HRESULT		CExportP12::SetFriendlyName


HRESULT		CExportP12::m_InitIntegrityParams ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	the random salt is 20 bytes. so allocate memory
//		m_dwSaltLen			=	20;
		m_dwSaltLen			=	8;
		m_dwCertsSaltLen	=	8;
		m_dwHMACSaltLen		=	20;
		
		m_pbyteSalt =	new BYTE [m_dwSaltLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteSalt)

		m_pbyteCertsSalt = new BYTE [m_dwCertsSaltLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteCertsSalt)

		m_pbyteHMACSalt = new BYTE [m_dwHMACSaltLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteHMACSalt)

					//	generate random salt
		hResult =	GenerateRandomBlock
					(
						m_pbyteSalt,
						m_dwSaltLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_INIT_PARAM;
			break;
		}

					//	generate random salt
		hResult =	GenerateRandomBlock
					(
						m_pbyteCertsSalt,
						m_dwCertsSaltLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_INIT_PARAM;
			break;
		}

					//	generate random salt
		hResult =	GenerateRandomBlock
					(
						m_pbyteHMACSalt,
						m_dwHMACSaltLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_INIT_PARAM;
			break;
		}

			//	set iteration count
		m_dwIterationCount		=	P12E_ITERATION_COUNT;
		m_dwCertsIterationCount	=	P12E_ITERATION_COUNT;
		m_dwHMACIterationCount	=	P12E_ITERATION_COUNT;

				//	set the encryption algorithm to 3-DES
		m_dwEncryptionAlgo =	ID_3DES;

				//	the encrypted data version = 0
		m_dwEncryptedDataVersion = 0;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_InitIntegrityParams ()


HRESULT		CExportP12::m_EncryptKeyBlob ()
{
	HRESULT				hResult				=	E_FAIL;

	ITEM				itemKey;

	void*				pvoidContext		=	NULL;

	DWORD				dwResidual			=	0;

	do
	{
					//	allocate memory for the key
		m_dwKeyLen =	DES3_KEYSIZE;
		m_pbyteKey =	new BYTE[m_dwKeyLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteKey)

					//	generate the key
		hResult =	_DoP12KeyGen
					(
						m_tbstrPassword,
						m_pbyteSalt,
						m_dwSaltLen,
						m_dwIterationCount,
						ID_ENCKEY,
						m_pbyteKey,
						m_dwKeyLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_KEY_GEN;
			break;
		}

		hResult =	_SetParity
					(
						m_pbyteKey,
						m_dwKeyLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_KEY_GEN;
			break;
		}

					// allocate memory for the IV
		m_dwIVLen =	DES3_IVSIZE;
		m_pbyteIV = new BYTE[m_dwIVLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteIV)

					//	generate the IV
		hResult =	_DoP12KeyGen
					(
						m_tbstrPassword,
						m_pbyteSalt,
						m_dwSaltLen,
						m_dwIterationCount,
						ID_IV,
						m_pbyteIV,
						m_dwIVLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_IV_GEN;
			break;
		}

		itemKey.len = m_dwKeyLen;
		itemKey.data = m_pbyteKey;

		hResult =	SymEncryptDataBegin
					(
						SYM_3DES,
						&itemKey,
						m_dwKeyLen * 8,
						&pvoidContext,
						m_pbyteIV,
						1
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_ENCRYPTION;
		}

		m_dwEncryptedP8Len = (m_CSeqEncodedP8.BaseDERBlob)->cbData * 2;
		m_dwEncryptedP8AllocatedLen = m_dwEncryptedP8Len;
		m_pbyteEncryptedP8 = new BYTE [m_dwEncryptedP8Len];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteEncryptedP8)


		hResult =	SymEncryptDataUpdate
					(
						pvoidContext,
						(m_CSeqEncodedP8.BaseDERBlob)->pbData,
						(m_CSeqEncodedP8.BaseDERBlob)->cbData,
						m_pbyteEncryptedP8,
						(unsigned int *) &m_dwEncryptedP8Len
					);

		dwResidual = m_dwEncryptedP8AllocatedLen - m_dwEncryptedP8Len;

		hResult =	SymEncryptDataEnd
					(
						pvoidContext,
						&(m_pbyteEncryptedP8 [m_dwEncryptedP8Len]),
						(unsigned int *) &dwResidual
					);

		m_dwEncryptedP8Len += dwResidual;
		
		hResult =	S_OK;
	}	while (0);

	pvoidContext =	NULL;

	return	hResult;
}	//	end		HRESULT		CExportP12::m_EncryptKeyBlob ()


HRESULT		CExportP12::m_CreateShroudedP8 ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	encode the salt and the iteration
		COctetString			CmosSalt (m_dwSaltLen, m_pbyteSalt);
		//CMyUniversalInteger		CmuiIteration (sizeof(DWORD), (BYTE*) &m_dwIterationCount);
		CMyUniversalInteger		CmuiIteration (m_dwIterationCount);

				//	put salt and iteration in the sequence
		CSequence				CSeqSaltIteration;
		CSeqSaltIteration +=	CmosSalt;
		CSeqSaltIteration +=	CmuiIteration;

				//	encode the 3DES OID
				//	although P12 supports a choice of algo, we are using ONLY 3DES
		CObjectIdentifier		COid3DES ( strlen((const char*) szOID_PBE_SHA_3KEY_3DES), (unsigned char*) szOID_PBE_SHA_3KEY_3DES );

				//	put the 3DES algo OID and the salt-iteration seq in the outer sequence
		CSequence				CSeqAlgoSaltIteration;
		CSeqAlgoSaltIteration +=	COid3DES;
		CSeqAlgoSaltIteration +=	CSeqSaltIteration;

				//	encode encrypted p8 blob
		COctetString			CmosEncryptedP8 ( m_dwEncryptedP8Len, m_pbyteEncryptedP8 );

				//	put the algo-salt-iteration seq and the encrypted p8 in the outer sequence
		CSequence				CSeqAlgoSaltIterationEncP8;
		CSeqAlgoSaltIterationEncP8 +=	CSeqAlgoSaltIteration;
		CSeqAlgoSaltIterationEncP8 +=	CmosEncryptedP8;

				//	encode the shrouded p8 OID
		CObjectIdentifier		COidShroudedP8 ( strlen((const char*) szOID_P12_BAGTYPE_SHRP8), (unsigned char*) szOID_P12_BAGTYPE_SHRP8 );

				//	put the algo-salt-iteration-encP8 sequence in the tagged value
		CTaggedValue			CtvAlgoSaltIterationEncP8(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CSeqAlgoSaltIterationEncP8.BaseDERBlob));

		m_CSeqShroudedP8 +=	COidShroudedP8;
		m_CSeqShroudedP8 +=	CtvAlgoSaltIterationEncP8;

		
		CSet				CsetExtensions;
		CSequence			CSeqKeyUsage;

		CObjectIdentifier		COidKeyID ( strlen((const char*) szOID_PKCS_12_LOCAL_KEY_ID), (unsigned char*) szOID_PKCS_12_LOCAL_KEY_ID);

		BYTE				pbyteKeyID[4];
		pbyteKeyID[0] = 01;
		pbyteKeyID[1] = 00;
		pbyteKeyID[2] = 00;
		pbyteKeyID[3] = 00;

		COctetString			CmosKeyID ( 4, pbyteKeyID );
		CSet					CsetKeyID;
		CsetKeyID +=	CmosKeyID;

		CSeqKeyUsage +=	COidKeyID;
		CSeqKeyUsage +=	CsetKeyID;

		CObjectIdentifier		COidFriendlyName ( strlen((const char*) szOID_PKCS_12_FRIENDLY_NAME_ATTR), (unsigned char*) szOID_PKCS_12_FRIENDLY_NAME_ATTR);
//		_bstr_t					tbstrFriendlyName = "{50950814-256C-11D5-89C2-0010B552D687}";

		CBMPString				CbmpstrFriendlyName
								(
									::strlen(m_tbstrFriendlyName),
									(BYTE*) (WCHAR*) m_tbstrFriendlyName
								);

		CSet					CsetFriendlyName;
		CsetFriendlyName +=	CbmpstrFriendlyName;

		CSequence				CSeqFriendlyName;
		CSeqFriendlyName +=	COidFriendlyName;
		CSeqFriendlyName +=	CsetFriendlyName;

/*
									NO NEED TO PUT IN THE PROVIDER NAME



		CObjectIdentifier		COidProvName ( strlen((const char*) szOID_PKCS_12_KEY_PROVIDER_NAME_ATTR), (unsigned char*) szOID_PKCS_12_KEY_PROVIDER_NAME_ATTR);
		_bstr_t					tbstrProvName = "Microsoft Enhanced Cryptographic Provider v1.0";
		CBMPString				CbmpstrProvName
								(
									::strlen(tbstrProvName),
									(BYTE*) (WCHAR*) tbstrProvName
								);

		CSet					CsetProvName;
		CsetProvName +=	CbmpstrProvName;

		CSequence				CSeqProvName;
		CSeqProvName +=	COidProvName;
		CSeqProvName +=	CsetProvName;
		
*/

		CsetExtensions +=	CSeqKeyUsage;
		CsetExtensions +=	CSeqFriendlyName;
//		CsetExtensions +=	CSeqProvName;


		m_CSeqShroudedP8 +=	CsetExtensions;
		

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_CreateShroudedP8 ()


HRESULT		CExportP12::m_CreateAuthSafePrivateKey ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	put the shrouded sequence inside another sequence
		CSequence				CSeqShroudedP8OuterSeq;
		CSeqShroudedP8OuterSeq	+=	m_CSeqShroudedP8;

				//	the sequence is then put in an octet string
		COctetString			CmosShroudedP8 ( (CSeqShroudedP8OuterSeq.BaseDERBlob) -> cbData, (CSeqShroudedP8OuterSeq.BaseDERBlob) -> pbData );

				//	put the octet string in the tagged value
		CTaggedValue			CtvShroudedP8(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CmosShroudedP8.BaseDERBlob));

				//	create an OID for the rsa data
		CObjectIdentifier		COidRSAData ( strlen((const char*) szOID_RSA_data), (unsigned char*) szOID_RSA_data );

		m_CSeqAuthSafePrivateKey +=	COidRSAData;
		m_CSeqAuthSafePrivateKey +=	CtvShroudedP8;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_CreateAuthSafePrivateKey ()


HRESULT		CExportP12::m_EncodeCerts ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	encode the salt and the iteration
		COctetString			CmosSalt (m_dwCertsSaltLen, m_pbyteCertsSalt);
		//CMyUniversalInteger		CmuiIteration (sizeof(DWORD), (BYTE*) &m_dwCertsIterationCount);
		CMyUniversalInteger		CmuiIteration (m_dwCertsIterationCount);

				//	put salt and iteration in the sequence
		CSequence				CSeqSaltIteration;
		CSeqSaltIteration +=	CmosSalt;
		CSeqSaltIteration +=	CmuiIteration;

				//	encode the 40 bit RC2 CBC OID
		CObjectIdentifier		COid40RC2CBC ( strlen((const char*) szOID_PBE_SHA_40RC2CBC), (unsigned char*) szOID_PBE_SHA_40RC2CBC );

				//	put the 3DES algo OID and the salt-iteration seq in the outer sequence
		CSequence				CSeqAlgoSaltIteration;
		CSeqAlgoSaltIteration +=	COid40RC2CBC;
		CSeqAlgoSaltIteration +=	CSeqSaltIteration;

				//	encode RSA data OID
		CObjectIdentifier		COidRSAData ( strlen((const char*) szOID_RSA_data), (unsigned char*) szOID_RSA_data);

/*				//	put the encrypted certs blob in an octet string
		COctetString			CmosEncryptedCerts (m_dwEncryptedCertsLen, m_pbyteEncryptedCerts);*/

				//	put the encrypted certs in a DER Blob
		CDERBlob				CdbEncryptedCerts (m_dwEncryptedCertsLen, m_pbyteEncryptedCerts);

				//	and the octet string in a tagged value
		CTaggedValue			CtvEncryptedCerts(CONTEXT_SPECIFIC, PRIMITIVE, 0, false, CdbEncryptedCerts);

				//	put the above sequence and the RSA data oid in the outer sequence
		CSequence				CSeqRSAAlgoSaltIterationCerts;
		CSeqRSAAlgoSaltIterationCerts +=	COidRSAData;
		CSeqRSAAlgoSaltIterationCerts +=	CSeqAlgoSaltIteration;
		CSeqRSAAlgoSaltIterationCerts +=	CtvEncryptedCerts;

				//	encode the encrypted data version
		//CMyUniversalInteger		CmuiEncryptedDataVersion (sizeof(DWORD), (BYTE*) &m_dwEncryptedDataVersion);
		CMyUniversalInteger		CmuiEncryptedDataVersion (m_dwEncryptedDataVersion);

				//	put the encrypted data version andthe above generated sequence (CSeqRSAAlgoSaltIterationCerts) in
				//	outer sequence
		CSequence				CSeqVerRSAAlgoSaltIterationCerts;
		CSeqVerRSAAlgoSaltIterationCerts +=	CmuiEncryptedDataVersion;
		CSeqVerRSAAlgoSaltIterationCerts +=	CSeqRSAAlgoSaltIterationCerts;

				//	encode the above sequence as a tagged value
		CTaggedValue			CtvVerRSAAlgoSaltIterationCerts(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CSeqVerRSAAlgoSaltIterationCerts.BaseDERBlob));

				//	encode the RSA Encrypted data OID
		CObjectIdentifier		COidRSAEncryptedData ( strlen((const char*) szOID_RSA_encryptedData), (unsigned char*) szOID_RSA_encryptedData);

				//	put the RSA Encrypted data and the tagged value created above
				//	in an outer sequence
		m_CSeqEncryptedCerts +=	COidRSAEncryptedData;
		m_CSeqEncryptedCerts +=	CtvVerRSAAlgoSaltIterationCerts;

		
		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_EncodeCerts ()


HRESULT		CExportP12::m_CreateAuthSafeWithOID ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	put the 2 sequences in the auth safe sequence
		m_CSeqAuthSafe +=	m_CSeqAuthSafePrivateKey;
		m_CSeqAuthSafe +=	m_CSeqEncryptedCerts;

				//	put the auth safe in an octet string and then into a tagged value
		COctetString			CmosAuthSafe ( (m_CSeqAuthSafe.BaseDERBlob) -> cbData, (m_CSeqAuthSafe.BaseDERBlob) -> pbData );
		CTaggedValue			CtvAuthSafe(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CmosAuthSafe.BaseDERBlob));

				//	the RSA data OID
		CObjectIdentifier		COidRSAData ( strlen((const char*) szOID_RSA_data), (unsigned char*) szOID_RSA_data );

				//	create the sequence with the RSA data OID and the auth Safe
		m_CSeqAuthSafeWithOID +=	COidRSAData;
		m_CSeqAuthSafeWithOID +=	CtvAuthSafe;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_CreateAuthSafe ()


HRESULT		CExportP12::m_EncryptCertBlob ()
{
	HRESULT				hResult				=	E_FAIL;

	ITEM				itemKey;

	void*				pvoidContext		=	NULL;

	DWORD				dwResidual			=	0;
	
	do
	{
					//	allocate memory for the key
		m_dwKeyForCertsLen =	RC2CBC_40BIT_KEYSIZE;
		m_pbyteKeyForCerts =	new BYTE[m_dwKeyForCertsLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteKeyForCerts)

					//	generate the key
		hResult =	_DoP12KeyGen
					(
						m_tbstrPassword,
						m_pbyteCertsSalt,
						m_dwCertsSaltLen,
						m_dwCertsIterationCount,
						ID_ENCKEY,
						m_pbyteKeyForCerts,
						m_dwKeyForCertsLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_KEY_GEN;
			break;
		}

					// allocate memory for the IV
		m_dwIVForCertsLen =	RC2CBC_IVSIZE;
		m_pbyteIVForCerts = new BYTE[m_dwIVForCertsLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteIVForCerts)

					//	generate the IV
		hResult =	_DoP12KeyGen
					(
						m_tbstrPassword,
						m_pbyteCertsSalt,
						m_dwCertsSaltLen,
						m_dwCertsIterationCount,
						ID_IV,
						m_pbyteIVForCerts,
						m_dwIVForCertsLen
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_IV_GEN;
			break;
		}

		itemKey.len = m_dwKeyForCertsLen;
		itemKey.data = m_pbyteKeyForCerts;
		
		hResult =	SymEncryptDataBegin
					(
						SYM_RC2_CBC,
						&itemKey,
						m_dwKeyForCertsLen * 8,
						&pvoidContext,
						m_pbyteIVForCerts,
						1
					);
		if ( S_OK != hResult )
		{
			hResult =	E_P12E_ENCRYPTION;
		}

		m_dwEncryptedCertsLen = (m_CSeqCerts.BaseDERBlob)->cbData * 2;
		m_dwEncryptedCertsAllocatedLen = m_dwEncryptedCertsLen;
		m_pbyteEncryptedCerts = new BYTE [m_dwEncryptedCertsLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteEncryptedCerts)


		hResult =	SymEncryptDataUpdate
					(
						pvoidContext,
						(m_CSeqCerts.BaseDERBlob)->pbData,
						(m_CSeqCerts.BaseDERBlob)->cbData,
						m_pbyteEncryptedCerts,
						(unsigned int *) &m_dwEncryptedCertsLen
					);

		dwResidual = m_dwEncryptedCertsAllocatedLen - m_dwEncryptedCertsLen;

		hResult =	SymEncryptDataEnd
					(
						pvoidContext,
						&(m_pbyteEncryptedCerts [m_dwEncryptedCertsLen]),
						(unsigned int *) &dwResidual
					);

		m_dwEncryptedCertsLen += dwResidual;
		
		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_EncryptCertBlob ()


HRESULT		CExportP12::m_PutCertsInOctetStrings ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
		for ( int i = 0; i < m_dwNumberOfCerts; i ++ )
		{
			CObjectIdentifier		COidCertBagType ( strlen((const char*) szOID_P12_BAGTYPE_CERT), (unsigned char*) szOID_P12_BAGTYPE_CERT );
			CObjectIdentifier		COidX509Cert ( strlen((const char*) szOID_X509_CERT), (unsigned char*) szOID_X509_CERT );

			COctetString			CmosCert (m_pdwCertBlobLen[i], m_ppbyteCertBlob[i]);

			CTaggedValue			CtvCert(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CmosCert.BaseDERBlob));

			CSequence				CSeqCert;
			CSeqCert +=	COidX509Cert;
			CSeqCert +=	CtvCert;

			CTaggedValue			CtvOIDCert(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, *(CSeqCert.BaseDERBlob));

			CSequence				CSeqOIDCert;
			CSeqOIDCert +=	COidCertBagType;
			CSeqOIDCert +=	CtvOIDCert;


			CSet				CsetExtensions;
			CSequence			CSeqKeyUsage;

			CObjectIdentifier		COidKeyID ( strlen((const char*) szOID_PKCS_12_LOCAL_KEY_ID), (unsigned char*) szOID_PKCS_12_LOCAL_KEY_ID);

			BYTE				pbyteKeyID[4];
			pbyteKeyID[0] = 01;
			pbyteKeyID[1] = 00;
			pbyteKeyID[2] = 00;
			pbyteKeyID[3] = 00;

			COctetString			CmosKeyID ( 4, pbyteKeyID );
			CSet					CsetKeyID;
			CsetKeyID +=	CmosKeyID;

			CSeqKeyUsage +=	COidKeyID;
			CSeqKeyUsage +=	CsetKeyID;

			CsetExtensions +=	CSeqKeyUsage;
			
			CSeqOIDCert +=	CsetExtensions;


			m_CSeqCerts +=	CSeqOIDCert;
		}	//	end		for ( int i = 0; i < m_dwNumberOfCerts; i ++ )

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_PutCertsInOctetStrings ()


HRESULT		CExportP12::m_CreateMACDataSequence ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
				//	the SHA1 will be used for the HMAC digest
				//	so create a OID
		CObjectIdentifier		COidSHA1 ( strlen((const char*) szOID_OIWSEC_sha1), (unsigned char*) szOID_OIWSEC_sha1);

				//	and put it into a sequence
		CSequence				CSeqSHA1;
		CSeqSHA1 +=	COidSHA1;

		CNull					CnlTemp;
		CSeqSHA1 +=	CnlTemp;

				//	put the digest into an octet string
		COctetString			CmosHMACDigest (m_dwHMACDigestLen, m_pbyteHMACDigest);

				//	put the above sequence and the digest octet string in an outer sequence
		CSequence				CSeqSHA1Digest;
		CSeqSHA1Digest +=	CSeqSHA1;
		CSeqSHA1Digest +=	CmosHMACDigest;

				//	put the HMAC salt in an octet string and the HMAC iteration
				//	count in an universal integer
		COctetString			CmosHMACSalt (m_dwHMACSaltLen, m_pbyteHMACSalt);
		//CMyUniversalInteger		CmuiIteration (sizeof(DWORD), (BYTE*) &m_dwHMACIterationCount);
		CMyUniversalInteger		CmuiIteration (m_dwHMACIterationCount);

		m_CSeqMACData +=	CSeqSHA1Digest;
		m_CSeqMACData +=	CmosHMACSalt;
		m_CSeqMACData +=	CmuiIteration;
		
		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_CreateMACDataSequence ()


HRESULT		CExportP12::m_GetHMACDigest ()
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
		hResult =	_GetHMACKey
					(
						m_tbstrPassword,
						m_pbyteHMACSalt,
						m_dwHMACSaltLen,
						m_dwHMACIterationCount,
						NULL,
						&m_dwHMACKeyLen
					);
		PKCS12_CHECK_HRESULT

		m_pbyteHMACKey = new BYTE [m_dwHMACKeyLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteHMACKey)

		hResult =	_GetHMACKey
					(
						m_tbstrPassword,
						m_pbyteHMACSalt,
						m_dwHMACSaltLen,
						m_dwHMACIterationCount,
						m_pbyteHMACKey,
						&m_dwHMACKeyLen
					);
		PKCS12_CHECK_HRESULT

		m_dwHMACDigestLen =	HMAC_SHA1_DIGEST_LEN;
		m_pbyteHMACDigest = new BYTE[m_dwHMACDigestLen];
		P12_EXP_CHECK_ALLOCATED_MEMORY(m_pbyteHMACDigest)

		m_dwHMACHashAlgo =	IMPP12_SHA;

		hResult =	_GetHMACDigest
					(
						(m_CSeqAuthSafe.BaseDERBlob) -> pbData,
						(m_CSeqAuthSafe.BaseDERBlob) -> cbData,
						m_dwHMACHashAlgo,
						m_pbyteHMACKey,
						m_dwHMACKeyLen,
						m_pbyteHMACDigest
					);
		PKCS12_CHECK_HRESULT

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_GetHMACDigest ()


HRESULT		CExportP12::m_CreateP12 ()
{
	HRESULT				hResult				=	E_FAIL;
	DWORD				dwVersion			=	VS_P12_VERSION;
	BYTE				byteVersion			=	0x03;

	do
	{
//		CMyUniversalInteger		CmuiVersion (1, (BYTE*) &byteVersion);
		//CMyUniversalInteger		CmuiVersion (sizeof (DWORD), (BYTE*) &dwVersion);
		CMyUniversalInteger		CmuiVersion (dwVersion);

		m_CSeqP12 +=	CmuiVersion;
		m_CSeqP12 +=	m_CSeqAuthSafeWithOID;
		m_CSeqP12 +=	m_CSeqMACData;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_CreateP12 ()


HRESULT		CExportP12::GetP12ByteBlob
(
		DWORD*						o_pdwP12Len,
		BYTE**						o_ppbyteP12
)
{
	HRESULT				hResult				=	E_FAIL;

	do
	{
		hResult =	m_InitIntegrityParams ();
		PKCS12_CHECK_HRESULT

		hResult =	CreateP8
					(
						m_RSAKey_PrivateKey,
						m_RSAKey_PublicKey,
						&m_CSeqP8
					);
		PKCS12_CHECK_HRESULT

		hResult =	m_EncodeP8 ();
		PKCS12_CHECK_HRESULT

		hResult =	m_EncryptKeyBlob ();
		PKCS12_CHECK_HRESULT

		hResult =	m_CreateShroudedP8 ();
		PKCS12_CHECK_HRESULT

		hResult =	m_CreateAuthSafePrivateKey ();
		PKCS12_CHECK_HRESULT

		hResult =	m_PutCertsInOctetStrings ();
		PKCS12_CHECK_HRESULT

		hResult =	m_EncryptCertBlob ();
		PKCS12_CHECK_HRESULT

		hResult =	m_EncodeCerts ();
		PKCS12_CHECK_HRESULT
		
		hResult =	m_CreateAuthSafeWithOID ();
		PKCS12_CHECK_HRESULT

		hResult =	m_GetHMACDigest ();
		PKCS12_CHECK_HRESULT

		hResult =	m_CreateMACDataSequence ();
		PKCS12_CHECK_HRESULT

		hResult =	m_CreateP12 ();
		PKCS12_CHECK_HRESULT

		*o_pdwP12Len =	(m_CSeqP12.BaseDERBlob) -> cbData;
		*o_ppbyteP12 =	new BYTE [*o_pdwP12Len];
		P12_EXP_CHECK_ALLOCATED_MEMORY(*o_ppbyteP12)

		::memcpy (*o_ppbyteP12, (m_CSeqP12.BaseDERBlob) -> pbData, *o_pdwP12Len);

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::GetP12Sequence


HRESULT		CExportP12::m_EncodeP8 ()
{
	HRESULT				hResult				=	E_FAIL;

	DWORD				dwVersion			=	0;

	do
	{
				//	encode the version as a universal integer
		//CMyUniversalInteger		CuiVersion ( sizeof (DWORD), (BYTE*) &dwVersion );
		CMyUniversalInteger		CuiVersion ( dwVersion );

				//	create objects for the RSA_RSA oid and NULL
		CObjectIdentifier		COidRSARSA ( strlen((const char*) szOID_RSA_RSA), (unsigned char*) szOID_RSA_RSA);
		CNull					CnlNull;

				//	put them into a sequence
		CSequence				CSeqOidNull;
		CSeqOidNull +=	COidRSARSA;
		CSeqOidNull +=	CnlNull;

				//	put the p8 sequence in an octet string
		COctetString			CmosP8 ( (m_CSeqP8.BaseDERBlob)->cbData, (m_CSeqP8.BaseDERBlob)->pbData );

				//	put the version, above generated sequence and the octet string p8 in an outer sequence
		m_CSeqEncodedP8 +=	CuiVersion;
		m_CSeqEncodedP8 +=	CSeqOidNull;
		m_CSeqEncodedP8 +=	CmosP8;

		hResult =	S_OK;
	}	while (0);

	return	hResult;
}	//	end		HRESULT		CExportP12::m_EncodeP8 ()