/*** Header file for Import PKCS12 ***/

#ifndef _PKCS12INFO_H
#define _PKCS12INFO_H

#include <comdef.h>
#include "simder_all.h"


class Pkcs12Info
{
private :
	BOOL	bInitialized;
	DWORD	m_dwNumOfCerts; //The number of certificates that were extracted out of the p12
	BYTE**	m_ppbyteCerts;  //An array of byte pointers each pointing to a cert blob
	DWORD*	m_pdwCertSizes; //An array of DWORDs each providing the size of the corresponding
						  //cert in the above array
	BYTE*	m_pbyteP8;	  //The PKCS8 extracted out of the P12
	DWORD	m_dwP8Size;	  //Size of the P8 blob

	HRESULT _GetP12FromFile(_bstr_t& i_tbstrPKCS12File, BYTE* o_pbyteP12, DWORD* o_pdwP12Size);
	HRESULT _GetP12FromBase64(_bstr_t& i_tbstrB64PKCS12, BYTE* o_pbyteP12,DWORD* o_pdwP12Size);
	HRESULT _GetIntegrityParams(BYTE* i_pbyteP12, DWORD i_dwP12Size, DWORD* o_pdwDigestAlg, BYTE* o_pbyteAuthSafe,
									   DWORD* o_pdwAuthSafeSize, BYTE* o_pbyteDigest,DWORD* o_pdwDigestSize, 
									   BYTE* o_pbyteSalt, DWORD* o_pdwSaltSize, DWORD* o_pdwIterations);
	HRESULT _CheckIntegrity(_bstr_t& i_tbstrPassword, DWORD i_dwDigestAlg, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize, 
							BYTE* i_pbyteSalt,DWORD i_dwSaltSize, DWORD i_dwIterations, BYTE* i_pbyteDigest, DWORD i_dwDigestSize);
	HRESULT _GetCertsFromAuthSafe(_bstr_t& i_tbstrPassword, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize);
	HRESULT _GetDecryptionParams(DERTree* i_pdtEncAlgId, BYTE* o_pbyteEncAlg, BYTE* o_pbyteSalt, DWORD* o_pdwSaltSize, DWORD* o_pdwIterations);
	HRESULT _DoRC2CBCDecrypt(BYTE* i_pbyteKey, DWORD dwKeyLen, BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize);
	HRESULT _DecryptP12Blob(BYTE* in_pbyteEncBlob, DWORD i_dwEncBlobSize,_bstr_t& i_tbstrPassword, 
									DERTree* i_pdtEncAlgId, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize);
	HRESULT _GetPrivateKey(_bstr_t& i_tbstrPassword, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize);
	HRESULT _Do3DESDecrypt(BYTE* i_pbyteKey, DWORD dwKeyLen, BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize);
	HRESULT _ExtractCertsFromSafeBags(BYTE* i_pbyteSafeContents, DWORD i_dwSafeContentsSize);

public :
	DWORD m_dwErrCode;
	Pkcs12Info(int i_nParamType, _bstr_t& i_tbstrPKCS12, _bstr_t& i_tbstrPassword); //Constructor
	~Pkcs12Info();

	int get_NumOfCerts();
	int get_CertSize(DWORD dwCertNum);
	HRESULT GetCert(DWORD i_dwCertNum, PBYTE i_pbyteCertBlob);
	HRESULT GetPKCS8(BYTE* i_pbytePKCS8, DWORD* o_pdwPKCS8Size);
};


#endif