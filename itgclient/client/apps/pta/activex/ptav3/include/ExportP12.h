///		ExportP12.h

#ifndef		__PTA_EXPORT_P12__
#define		__PTA_EXPORT_P12__


#include <comdef.h>
#include "simder_all.h"
#include "FindPrimes.h"
#include "pkcs12defines.h"

#define		P12E_ITERATION_COUNT		2000


class	CExportP12
{
private:
	DWORD				m_dwInitialized;

	DWORD				m_dwNumberOfCerts;

	BYTE**				m_ppbyteCertBlob;
	DWORD*				m_pdwCertBlobLen;

	BYTE*				m_pbytePrivateKeyBlob;
	DWORD				m_dwPrivateKeyBlobLen;

	BYTE*				m_pbytePublicKeyBlob;
	DWORD				m_dwPublicKeyBlobLen;

	DWORD				m_dwTypeOfOutput;

	BYTE*				m_pbyteSalt;
	DWORD				m_dwSaltLen;

	BYTE*				m_pbyteCertsSalt;
	DWORD				m_dwCertsSaltLen;

	BYTE*				m_pbyteHMACSalt;
	DWORD				m_dwHMACSaltLen;

	DWORD				m_dwIterationCount;
	DWORD				m_dwCertsIterationCount;
	DWORD				m_dwHMACIterationCount;

	DWORD				m_dwEncryptionAlgo;
	
	BYTE*				m_pbyteAuthBagDigest;
	DWORD				m_dwAuthBagDigestLen;

	DWORD				m_dwAuthBagDigestAlgo;

	_bstr_t				m_tbstrPassword;

	BYTE*				m_pbyteEncryptedP8;
	DWORD				m_dwEncryptedP8Len;
	DWORD				m_dwEncryptedP8AllocatedLen;

	BYTE*				m_pbyteEncryptedCerts;
	DWORD				m_dwEncryptedCertsLen;
	DWORD				m_dwEncryptedCertsAllocatedLen;

	DWORD				m_dwEncryptedDataVersion;

	BYTE*				m_pbyteKey;
	DWORD				m_dwKeyLen;

	BYTE*				m_pbyteKeyForCerts;
	DWORD				m_dwKeyForCertsLen;

	BYTE*				m_pbyteIV;
	DWORD				m_dwIVLen;

	BYTE*				m_pbyteIVForCerts;
	DWORD				m_dwIVForCertsLen;

	BYTE*				m_pbyteHMACDigest;
	DWORD				m_dwHMACDigestLen;

	BYTE*				m_pbyteHMACKey;
	DWORD				m_dwHMACKeyLen;

	DWORD				m_dwHMACHashAlgo;

	_bstr_t				m_tbstrFriendlyName;


	CSequence			m_CSeqP8;
	CSequence			m_CSeqEncodedP8;
	CSequence			m_CSeqShroudedP8;
	CSequence			m_CSeqAuthSafePrivateKey;
	CSequence			m_CSeqCerts;
	CSequence			m_CSeqEncryptedCerts;
	CSequence			m_CSeqAuthSafe;
	CSequence			m_CSeqAuthSafeWithOID;
	CSequence			m_CSeqMACData;
	CSequence			m_CSeqP12;

	A_RSA_KEY			m_RSAKey_PrivateKey;
	A_RSA_KEY			m_RSAKey_PublicKey;

public:
	CExportP12();
	~CExportP12();

	HRESULT		Initialize
	(
		const DWORD					i_cdwTypeOfOutput
	);

	HRESULT		SetNumberOfCerts
	(
		const DWORD					i_cdwNumberOfCerts
	);

	HRESULT		SetCertBlob
	(
		const DWORD					i_cdwCertNumber,
		const BYTE*					i_cpbyteCertBlob,
		const DWORD					i_cdwCertBlobLen
	);

	HRESULT		SetKey
	(
		const BYTE*					i_cpbytePrivateKeyBlob,
		const DWORD					i_cdwPrivateKeyBlobLen,
		const BYTE*					i_cpbytePublicKeyBlob,
		const DWORD					i_cdwPublicKeyBlobLen
	);

	HRESULT		SetPassword
	(
		const _bstr_t				i_ctbstrPassword
	);

	HRESULT		SetFriendlyName
	(
		_bstr_t						i_tbstrFriendlyName
	);

	HRESULT		GetP12ByteBlob
	(
		DWORD*						o_pdwP12Len,
		BYTE**						o_ppbyteP12
	);


private:
	HRESULT		m_InitIntegrityParams ();

	HRESULT		m_EncodeP8 ();

	HRESULT		m_EncryptKeyBlob ();

	HRESULT		m_EncryptCertBlob ();

	HRESULT		m_CreateShroudedP8 ();

	HRESULT		m_CreateAuthSafePrivateKey ();

	HRESULT		m_EncodeCerts ();

	HRESULT		m_CreateAuthSafeWithOID ();

	HRESULT		m_PutCertsInOctetStrings ();

	HRESULT		m_CreateMACDataSequence ();

	HRESULT		m_GetHMACDigest ();

	HRESULT		m_CreateP12 ();


};


#endif