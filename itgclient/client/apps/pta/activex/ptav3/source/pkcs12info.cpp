// imppkcs12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pkcs12info.h"
#include "pkcs12defines.h"
#include "pkcs12errs.h"
#include "pkcs12macros.h"
#include "simder_all.h"
#include <wincrypt.h> //For OID definitions.
#include "..\..\BSafeLite\include\integrate.h"
#include "md5.h"
#include "md2.h"
#include "sha.h"
#include <math.h>
#include "P12Helper.h"


/*
Function Name : Pkcs12Info
Purpose : Constructor. Takes the pkcs12 or filename containing a pkcs 12 as input and 
		  extracts a p7 and p8 from the p12
Parameters :	i_nParamType - Indicates what the next parameter respresents. Possible values are :
							PKCS12INFO_FILENAME - The i_tbstrPKCS12 param is the location and name of
							of a file containing the PKCS12
							PKCS12INFO_B64ENCP12 - The i_tbstrPKCS12 param is the base64 encoded p12.
				i_tbstrPKCS12 - The name of the file containing the p12 or a base64 encoded p12
				i_tbstrPassword - Password to decrypt the p12
Return : None
*/
Pkcs12Info::Pkcs12Info(int i_nParamType, _bstr_t& i_tbstrPKCS12, _bstr_t& i_tbstrPassword)
{
	BYTE* pbyteP12 = NULL;
	DWORD dwP12Size = 0;
	HRESULT hResult = S_OK;
	BYTE* pbyteAuthSafe = NULL;
	DWORD dwAuthSafeSize = 0;
	BYTE* pbyteDigest = NULL;
	DWORD dwDigestSize = 0;
	BYTE* pbyteSalt = NULL;
	DWORD dwSaltSize = 0;
	DWORD dwDigestAlg = 0;
	DWORD dwIterations = 0;

	/*Initialize the class members*/
	m_dwNumOfCerts = 0;
	m_ppbyteCerts = NULL;
	m_pdwCertSizes = NULL;
	m_pbyteP8 = NULL;
	m_dwP8Size = 0;

	do
	{
		/*Obtain the DER encoded p12*/

		//Get the size of the p12
		switch(i_nParamType)
		{
		case PKCS12INFO_FILENAME :
			hResult = _GetP12FromFile(i_tbstrPKCS12, NULL, &dwP12Size);
			break;

		case PKCS12INFO_B64ENCP12 :
			hResult = _GetP12FromBase64(i_tbstrPKCS12, NULL, &dwP12Size);
			break;

		default :
			hResult = E_INVALIDPARAMS;
			break;
		}

		//Check if hResult is ok
		PKCS12_CHECK_HRESULT

		//Allocate memory
		pbyteP12 = (BYTE*)new BYTE[dwP12Size];
		PKCS12_CHECK_MEMALLOC(pbyteP12)

		//Obtain the p12
		switch(i_nParamType)
		{
		case PKCS12INFO_FILENAME :
			hResult = _GetP12FromFile(i_tbstrPKCS12, pbyteP12, &dwP12Size);
			break;

		case PKCS12INFO_B64ENCP12 :
			hResult = _GetP12FromBase64(i_tbstrPKCS12, pbyteP12, &dwP12Size);
			break;

		default :
			hResult = E_INVALIDPARAMS;
			break;
		}

		//Check if hResult is ok
		PKCS12_CHECK_HRESULT

		/*
		The p12 has the following asn construct
		PFX ::= SEQUENCE {
			version INTEGER {v3(3)}
			authSafe ContentInfo,
			macData MacData OPTIONAL
		}

		The MacData is defined as
		MacData::= SEQUENCE {
			mac	DigestInfo
			macSalt OCTET STRING
			iterations INTEGER DEFAULT 1
		}

		DigestInfo:= SEQUENCE {
			digestAlgorithIdentifier DigestAlgorithmIdentifier
			digest OCTET STRING
		}
		*/

		/*Check P12 integrity*/
		//Obtain the sizes of authSafe, digest value, macSalt
		hResult = _GetIntegrityParams(pbyteP12,dwP12Size,&dwDigestAlg, NULL, &dwAuthSafeSize, NULL, &dwDigestSize, NULL, &dwSaltSize, &dwIterations); 
		PKCS12_CHECK_HRESULT

		//Allocate memory
		pbyteAuthSafe = (BYTE*)new BYTE[dwAuthSafeSize];
		PKCS12_CHECK_MEMALLOC(pbyteAuthSafe)

		pbyteDigest = (BYTE*)new BYTE[dwDigestSize];
		PKCS12_CHECK_MEMALLOC(pbyteDigest)

		pbyteSalt = (BYTE*)new BYTE[dwSaltSize];
		PKCS12_CHECK_MEMALLOC(pbyteSalt)


		//Obtain the authSafe, digest algorithm, digest value, macSalt and iterations
		hResult = _GetIntegrityParams(pbyteP12, dwP12Size, &dwDigestAlg, pbyteAuthSafe, &dwAuthSafeSize, pbyteDigest, &dwDigestSize, pbyteSalt, &dwSaltSize, &dwIterations); 
		PKCS12_CHECK_HRESULT

		//Check for the integrity of the authsafe
		hResult = _CheckIntegrity(i_tbstrPassword, dwDigestAlg, pbyteAuthSafe, dwAuthSafeSize, pbyteSalt, dwSaltSize, dwIterations, pbyteDigest, dwDigestSize);
		PKCS12_CHECK_HRESULT

		/*Obtain the PKCS8*/
		hResult = _GetPrivateKey(i_tbstrPassword, pbyteAuthSafe, dwAuthSafeSize);
		PKCS12_CHECK_HRESULT

		/*Obtain the certs from the p12*/
		hResult = _GetCertsFromAuthSafe(i_tbstrPassword, pbyteAuthSafe, dwAuthSafeSize);
		PKCS12_CHECK_HRESULT


	}while(0);

	/*Free memory*/
	if(pbyteP12)
	{
		delete[] pbyteP12;
		pbyteP12 = NULL;
	}

	if(pbyteAuthSafe)
	{
		delete[] pbyteAuthSafe;
		pbyteAuthSafe = NULL;
	}


	if(pbyteDigest)
	{
		delete[] pbyteDigest;
		pbyteDigest = NULL;
	}


	if(pbyteSalt)
	{
		delete[] pbyteSalt;
		pbyteSalt = NULL;
	}

	if(hResult)
	{
		bInitialized = FALSE;
		m_dwErrCode = hResult;
	}
	else
	{
		bInitialized = TRUE;
		m_dwErrCode = 0;
	}

	return;
}


/*
Function Name : ~Pkcs12Info
Purpose : Destructor

Parameters : None
Return :	Nothing

*/
Pkcs12Info::~Pkcs12Info()
{
	PKCS12_FREE_MEM(m_pbyteP8);
	m_dwP8Size = 0;

	if(m_ppbyteCerts)
	{
		for(unsigned int i=0; i<m_dwNumOfCerts; ++i)
		{
			PKCS12_FREE_MEM(m_ppbyteCerts[i])
			m_ppbyteCerts[i] = NULL;
		}
	}
	PKCS12_FREE_MEM(m_ppbyteCerts);
	m_ppbyteCerts = NULL;

	PKCS12_FREE_MEM(m_pdwCertSizes);
	m_pdwCertSizes = NULL;

	m_dwNumOfCerts = 0;

	bInitialized = FALSE;
}

/*Private functions*/

/*
Function Name : _GetP12FromFile
Purpose : This function reads the P12 from the given filename

Parameters : i_tbstrPKCS12File - The location and name of the file containing the p12
			 o_pbyteP12 - The byte blob containig the P12. If this parameter is NULL, the function
			 returns the expected size of the blob.
			 o_pdwP12Size - The size of the P12 blob.

Return :	E_CREATEFILEFAILED - Failed to open the file containing the p12
			E_GETFILESIZEFAILED - Failed to get the size of the file
			E_READFILEFAILED - Failed to read the contents of the file
			E_NOTENOUGHBYTESREAD - Failed to read all the contents of the file

*/
HRESULT Pkcs12Info::_GetP12FromFile(_bstr_t& i_tbstrPKCS12File, BYTE* o_pbyteP12, DWORD* o_pdwP12Size)
{
	HRESULT hResult = S_OK;
	DWORD dwFileSize = 0;
	HANDLE hFile = NULL;

	do
	{
		/*Open the file*/
		hFile = CreateFile((LPCTSTR)i_tbstrPKCS12File,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,
			0,NULL);
		if(hFile == INVALID_HANDLE_VALUE)
		{
			hResult = E_CREATEFILEFAILED;
			hFile = NULL;
			break;
		}

		/*Get the size of the file*/
		dwFileSize = GetFileSize(hFile,NULL);
		if(dwFileSize == 0xFFFFFFFF)
		{
			hResult = E_GETFILESIZEFAILED;
			break;
		}
		*o_pdwP12Size = dwFileSize;

		/*If the p12 output param is NULL we only want to return the size*/
		if(!o_pbyteP12)
			break;

		/*Read the file and fill in the p12 blob to be outputted*/
		if(!ReadFile(hFile,o_pbyteP12,dwFileSize,o_pdwP12Size,NULL))
		{
			hResult = E_READFILEFAILED;
			break;
		}

		/*Make sure that the number of bytes read is equal to the file size*/
		if(*o_pdwP12Size != dwFileSize)
		{
			hResult = E_NOTENOUGHBYTESREAD;
			break;
		}
		
	}while(0);

	/*Free memory, release handles*/
	if(hFile)
	{
		CloseHandle(hFile);
		hFile = NULL;
	}


	/*Handle error condition*/
	if(hResult != S_OK)
	{
		*o_pdwP12Size = 0;
	}

	return hResult;
}


/*
Function Name : _GetP12FromBase64
Purpose : This function reads the P12 from the provided Base64 Encoded blob

Parameters : i_tbstrB64PKCS12 - The Base64 Encoded p12 blob
			 o_pbyteP12 - The byte blob containig the P12. If this parameter is NULL, the function
			 returns the expected size of the blob.
			 o_pdwP12Size - The size of the P12 blob.

Return : 
*/
HRESULT Pkcs12Info::_GetP12FromBase64(_bstr_t& i_tbstrB64PKCS12, BYTE* o_pbyteP12,DWORD* o_pdwP12Size)
{
	HRESULT hResult = S_OK;
	
	do
	{
	}while(0);

	return hResult;

}


/*
Function Name : _GetIntegrityParams
Purpose : This function obtains all the parameters required to check the integrity of the p12

Parameters :	i_pbyteP12 - The p12 blob
				i_dwP12Size - The size of the p12 blob
				o_pdwDigestAlg - Identifier indicating the hash algorithm used to do the 
								 HMAC integrity check. Values could be IMPP12_MD2, IMPP12_MD5, 
								 IMPP12_SHA
				o_pbyteAuthSafe - The BER encoded Authenticated Safe blob whose integrity is to be checked. 
								  If this param is NULL, the size required to hold the blob is returned.
				o_pdwAuthSafeSize - The size of the authSafe blob
				o_pbyteDigest - The HMAC digest of the authSafe blob.If this param
								is NULL, the size required to hold the blob is returned.
				o_pdwDigestSize - The size of the Digest blob
				o_pbyteSalt - The salt blob used to compute the key for the HMAC operation. If this 
							  param	is NULL, the size required to hold the blob is returned.
				o_pdwSaltSize - The size of the salt blob
				o_pdwIterations - The number of iterations used while computing the key for the HMAC 
								  operation.

Return :	E_INVALIDP12 - The p12 format is invalid
			E_INVALIDP12_WRONGVER - The version of the P12 is not supported
			E_INVALIDP12_WRONGAUTHSAFETYPE - The ASN.1 tag of the authSafe object is invalid
			E_INVALIDP12_WRONGAUTHSAFECONTENT - The ASN.1 tag of the authSafe Content object is invalid
			E_INVALIDP12_WRONGBERENCAUTHENTICATEDSAFE - The ASN.1 tag of the BER Encoding of the AuthenticatedSafe 
														object is invalid
			E_INVALIDP12_INVALIDMACDATA - The ASN.1 tag of the MacData object is invalid
			E_INVALIDP12_INVALIDMAC - The ASN.1 tag of the Mac object is invalid
			E_INVALIDP12_INVALIDMACALGID - The ASN.1 tag of the AlgId object is invalid
			E_INVALIDP12_INVALIDHASHALG - The ASN.1 tag of the HashAlg OID object is invalid
			E_INVALIDP12_INVALIDDIGEST - The ASN.1 tag of the Digest is invalid
			E_INVALIDP12_INVALIDSALT - The ASN.1 tag of the Salt is invalid
			E_INVALIDP12_INVALIDITERS - The ASN.1 tag of the Iterations is invalid
			
			
			  
*/
HRESULT Pkcs12Info::_GetIntegrityParams(BYTE* i_pbyteP12, DWORD i_dwP12Size, DWORD* o_pdwDigestAlg, BYTE* o_pbyteAuthSafe,
									   DWORD* o_pdwAuthSafeSize, BYTE* o_pbyteDigest,DWORD* o_pdwDigestSize, 
									   BYTE* o_pbyteSalt, DWORD* o_pdwSaltSize, DWORD* o_pdwIterations)
{
	HRESULT hResult = S_OK;
	
	do
	{
		/*
		The p12 has the following asn construct
		PFX ::= SEQUENCE {
			version INTEGER {v3(3)}
			authSafe ContentInfo,
			macData MacData OPTIONAL
		}

		ContentInfo := SEQUENCE {
										contentType contentType;
										content [0] EXPLICIT CONTENTS.&Type((Contents)(@contentType)) OPTIONAL
								}

		The content in the above sequence is an OCTET STRING which represents the BER encoding of an AuthenticatedSafe,
		which is defined as

		AuthenticatedSafe ::= SEQUENCE of ContentInfo
		*/
		CBaseDERCollection cbdcP12(i_dwP12Size, i_pbyteP12);
		CBaseDERHierarchy cbdhP12(cbdcP12);
		if ( 0 != cbdhP12.dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}
		

		//Did the decode work?
		if(cbdhP12.dwErrorCode)
		{
			hResult = E_INVALIDP12;
			break;
		}


		/*Check the version of the P12*/
		DERTree* pdtVersion = NULL;
		DWORD dwVersion = 0 ;

		pdtVersion = cbdhP12.m_DERTree.rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtVersion, E_INVALIDP12)


		if(pdtVersion->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			hResult = E_INVALIDP12;
			break;
		}

		memcpy(&dwVersion,pdtVersion->currentBaseDER->pbData,pdtVersion->currentBaseDER->cbData);
		if(dwVersion != P12_VERSION)
		{
			hResult = E_INVALIDP12_WRONGVER;
			break;
		}

		/*Obtain the size of the authSafe contents*/
		DERTree* pdtAuthSafe = NULL;
		DERTree* pdtAuthSafeType = NULL;
		DERTree* pdtAuthSafeContent = NULL;
		DERTree* pdtBEREncAuthenticatedSafe = NULL;

		//First obtain the AuthSafe SEQUENCE
		pdtAuthSafe = pdtVersion->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtAuthSafe, E_INVALIDP12)

		if(pdtAuthSafe->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGAUTHSAFE;
			break;
		}

		//Obtain and check the AuthSafe Type
		pdtAuthSafeType = pdtAuthSafe->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtAuthSafeType, E_INVALIDP12)

		if(pdtAuthSafeType->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGAUTHSAFETYPE;
			break;
		}

		if(lstrcmp((LPCTSTR)pdtAuthSafeType->currentBaseDER->pbData,szOID_RSA_data))
		{
			hResult = E_INVALIDP12_WRONGAUTHSAFETYPE;
			break;
		}

		//Obtain the AuthSafe Content
		pdtAuthSafeContent = pdtAuthSafeType->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtAuthSafeContent, E_INVALIDP12)

		if(pdtAuthSafeContent->currentBaseDER->Type != IMPLICIT)
		{
			hResult = E_INVALIDP12_WRONGAUTHSAFECONTENT;
			break;
		}

		//Obtain the OCTET STRING that forms the ClientInfo Data. This is the
		//BER Encoded AuthenticatedSafe object
		pdtBEREncAuthenticatedSafe = pdtAuthSafeContent->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtBEREncAuthenticatedSafe, E_INVALIDP12)
		
		if(pdtBEREncAuthenticatedSafe->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_WRONGBERENCAUTHENTICATEDSAFE;
			break;
		}

		*o_pdwAuthSafeSize = pdtBEREncAuthenticatedSafe->currentBaseDER->cbData;

		/*Obtain the Digest Alg and Digest Size from the MacData*/
		/*
		The MacData is defined as
		MacData::= SEQUENCE {
			mac	DigestInfo
			macSalt OCTET STRING
			iterations INTEGER DEFAULT 1
		}
		*/

		DERTree* pdtMacData = NULL;
		DERTree* pdtMac = NULL;
		DERTree* pdtAlgId = NULL;
		DERTree* pdtAlgIdOID = NULL;
		DERTree* pdtDigest = NULL;

		//Obtain the MacData Sequence
		pdtMacData = pdtAuthSafe->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtMacData, E_INVALIDP12)

		if(pdtMacData->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_INVALIDMACDATA;
			break;
		}

		//Obtain the MAC
		pdtMac = pdtMacData->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtMacData, E_INVALIDP12)

		if(pdtMac->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_INVALIDMAC;
			break;
		}
		
		//Obtain the Algorithm Identifier in the Mac
		pdtAlgId = pdtMac->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtMacData, E_INVALIDP12)

		if(pdtAlgId->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_INVALIDMACALGID;
			break;
		}


		//Obtain the OID of the Algorithm Identifier and determine the 
		//hash alg to be used for the HMAC
		pdtAlgIdOID = pdtAlgId->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtAlgIdOID, E_INVALIDP12)

		if(!lstrcmp((LPCTSTR)pdtAlgIdOID->currentBaseDER->pbData, szOID_OIWSEC_sha1))
		{
			*o_pdwDigestAlg = IMPP12_SHA;
		}
		else if(!lstrcmp((LPCTSTR)pdtAlgIdOID->currentBaseDER->pbData, szOID_RSA_MD2))
		{
			*o_pdwDigestAlg = IMPP12_MD2;
		}
		else if(!lstrcmp((LPCTSTR)pdtAlgIdOID->currentBaseDER->pbData, szOID_RSA_MD5))
		{
			*o_pdwDigestAlg = IMPP12_MD5;
		}
		else
		{
			hResult = E_INVALIDP12_INVALIDHASHALG;
			break;
		}

		//Obtain the Digest Size
		pdtDigest = pdtAlgId->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtDigest, E_INVALIDP12)

		if(pdtDigest->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_INVALIDDIGEST;
			break;
		}

		*o_pdwDigestSize = pdtDigest->currentBaseDER->cbData;

		/*Obtain the Salt Size*/
		DERTree* pdtSalt = NULL;

		pdtSalt = pdtMac->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtSalt, E_INVALIDP12)

		if(pdtSalt->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_INVALIDSALT;
			break;
		}

		*o_pdwSaltSize = pdtSalt->currentBaseDER->cbData;

		/*Obtain the number of iterations*/
		DERTree* pdtIters = NULL;
		pdtIters = pdtSalt->nextDERTree;

		if(!pdtIters)
			*o_pdwIterations = 1; //Default value
		else
		{
			if(pdtIters->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				hResult = E_INVALIDP12_INVALIDITERS;
				break;
			}
			memcpy(o_pdwIterations,pdtIters->currentBaseDER->pbData,pdtIters->currentBaseDER->cbData);
		}

		/*Fill in the AuthenticatedSafe, Digest and Salt Blobs*/
		if(o_pbyteAuthSafe)
			memcpy(o_pbyteAuthSafe,
			pdtBEREncAuthenticatedSafe->currentBaseDER->pbData,
			pdtBEREncAuthenticatedSafe->currentBaseDER->cbData); //Do this so that we donot get the OCTET STRING bytes reversed

		if(o_pbyteDigest)
			memcpy(o_pbyteDigest,
			pdtDigest->currentBaseDER->pbData,
			pdtDigest->currentBaseDER->cbData);
	
		if(o_pbyteSalt)
			memcpy(o_pbyteSalt,
			pdtSalt->currentBaseDER->pbData,
			pdtSalt->currentBaseDER->cbData);



	}while(0);

	return hResult;

}


/*
Function Name : _CheckIntegrity
Purpose : This function checks the integrity of the authSafe. It computes the HMAC key from the password, salt 
		  and iterations. It then computes the HMAC digest and compares it with the given digest to determine the 
		  integrity of the authSafe blob

Parameters :	i_tbstrPassword - The integrity password. The HMAC key will be calculated from this password,
								  the salt and the iterations.
				i_dwDigestAlg - The digest algorithm used to calculate the HMAC
				i_pbyteAuthSafe - The authSafe blob whose integrity is to be checked. The HMAC digest of this blob 
								  will be computed.
				i_dwAuthSafeSize - The size of the authSafe blob
				i_pbyteSalt - The salt blob used to compute the key for the HMAC operation. 
				i_pdwSaltSize - The size of the salt blob
				i_pdwIterations - The number of iterations used while computing the key for the HMAC 
								  operation.
				i_pbyteDigest - The HMAC digest with which the computed digest is to be compared.
				i_pdwDigestSize - The size of the Digest blob

				
Return :		S_OK - Integrity check succeeded.
				E_INTEGRITY_FAIL - Integrity check failed

*/
HRESULT Pkcs12Info::_CheckIntegrity(_bstr_t& i_tbstrPassword, DWORD i_dwDigestAlg, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize, BYTE* i_pbyteSalt,
									DWORD i_dwSaltSize, DWORD i_dwIterations, BYTE* i_pbyteDigest, DWORD i_dwDigestSize)
{
	HRESULT hResult = S_OK;
	BYTE* pbyteHMACKey = NULL;
	DWORD dwHMACKeySize = 0;
	BYTE* pbyteHMACDigest = NULL;

	do
	{
		/*Obtain the HMAC Key*/
		hResult = _GetHMACKey(i_tbstrPassword, i_pbyteSalt, i_dwSaltSize, i_dwIterations, NULL, &dwHMACKeySize);
		PKCS12_CHECK_HRESULT 

		pbyteHMACKey = (PBYTE)new BYTE[dwHMACKeySize];
		PKCS12_CHECK_MEMALLOC(pbyteHMACKey)

		hResult = _GetHMACKey(i_tbstrPassword, i_pbyteSalt, i_dwSaltSize, i_dwIterations, pbyteHMACKey, &dwHMACKeySize);

		/*Obtain the HMAC Digest*/
		pbyteHMACDigest = (PBYTE)new BYTE[i_dwDigestSize];
		PKCS12_CHECK_MEMALLOC(pbyteHMACDigest)

		hResult = _GetHMACDigest(i_pbyteAuthSafe,i_dwAuthSafeSize, i_dwDigestAlg, pbyteHMACKey,dwHMACKeySize, pbyteHMACDigest);
		PKCS12_CHECK_HRESULT 


		/*Compare the digests*/
		for(DWORD i=0;i<i_dwDigestSize;++i)
		{
			if(i_pbyteDigest[i] != pbyteHMACDigest[i])
			{
				hResult = E_INTEGRITY_FAIL;
				i = i_dwDigestSize;
			}
		}
		PKCS12_CHECK_HRESULT 


	}while(0);

	PKCS12_FREE_MEM(pbyteHMACKey)
	PKCS12_FREE_MEM(pbyteHMACDigest)

	return hResult;
}


/*
Function Name : _GetCertsFromAuthSafe
Purpose : This function extracts the certitificates from the authenticated safe object and 
		  stores them in the array of certificates private data member.

Parameters :	i_tbstrPassword - The password for decrypting the encrypted contents
				i_pbyteAuthSafe - The Authenticated Safe from which the certs are to be retrieved
				i_dwAuthSafeSize - The size of the buffer in bytes. 
			
				
Return :		S_OK - Operation succeeded.
				

*/

HRESULT Pkcs12Info::_GetCertsFromAuthSafe(_bstr_t& i_tbstrPassword, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize)
{
	HRESULT hResult = S_OK;
	BYTE* pbyteDecP12Blob = NULL;
	DWORD dwDecP12BlobSize = 0;

	do
	{

		CBaseDERCollection cbdcAuthSafe(i_dwAuthSafeSize, i_pbyteAuthSafe);
		CBaseDERHierarchy cbdhAuthSafe(cbdcAuthSafe);
		if ( 0 != cbdhAuthSafe.dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}


		//Did the decode work?
		if(cbdhAuthSafe.dwErrorCode)
		{
			hResult = E_INVALIDP12;
			break;
		}

		if(cbdhAuthSafe.m_DERTree.currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGAUTHTNTCDSAFE;
			break;
		}

		/*AuthenticatedSafe ::= SEQUENCE of ContentInfo*/
		/*Navigate to the second contentInfo structure in the authenticatedSafe sequence - This is the one
		that contains the certs*/
		DERTree* pdtCertsContentInfo = NULL;
		DERTree* pdtShrPKCS8ContentInfo = NULL;

		pdtShrPKCS8ContentInfo = cbdhAuthSafe.m_DERTree.rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtShrPKCS8ContentInfo, E_INVALIDP12)

		pdtCertsContentInfo = pdtShrPKCS8ContentInfo->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtCertsContentInfo, E_INVALIDP12)

		if(pdtCertsContentInfo->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGCERTSCI;
			break;
		}

		
		/*
		The type of this contentinfo should be EncryptedData.
		The content field of this contentinfo contains an instance of the EncryptedData structure
		defined in PKCS7 as follows :
		EncryptedData ::= SEQUENCE {
				  version Version,
				  encryptedContentInfo EncryptedContentInfo 
				  }

		and EncryptedContentInfo is defined as
		EncryptedContentInfo ::= SEQUENCE {
				  contentType ContentType,
				  contentEncryptionAlgorithm
					ContentEncryptionAlgorithmIdentifier,
				  encryptedContent
					[0] IMPLICIT EncryptedContent OPTIONAL }

		For the P12 the contentType in the EncryptedContentInfo should be data and the 
		ContentEncryptionAlgorithmIdentifier provides the algorithm, salt and iterations to be used
		to obtain the key and iv to be used for decryption.

		*/

		/*Obtain the contentEncryptionAlgorithm structure*/

		//First obtain the type of the certs content info and ensure that it is EncryptedData
		DERTree* pdtCertsContentInfoType = NULL;

		pdtCertsContentInfoType = pdtCertsContentInfo->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtCertsContentInfoType, E_INVALIDP12)

		if(pdtCertsContentInfoType->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGCERTSCITYPE;
			break;
		}

		if(lstrcmp((LPCTSTR)pdtCertsContentInfoType->currentBaseDER->pbData, szOID_RSA_encryptedData))
		{
			hResult = E_INVALIDP12_WRONGCERTSCITYPE;
			break;
		}


		//Obtain the content from the certs content info
		DERTree* pdtCertsContentInfoContent = NULL;

		pdtCertsContentInfoContent = pdtCertsContentInfoType->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtCertsContentInfoContent, E_INVALIDP12)

		if(pdtCertsContentInfoContent->currentBaseDER->Type != IMPLICIT )
		{
			hResult = E_INVALIDP12_WRONGCERTSCICONTENT;
			break;
		}

		//Now obtain the value encoded in the content field of the certs contentinfo object.
		//This is the encryptedData object
		DERTree* pdtEncryptedData = NULL;

		pdtEncryptedData = pdtCertsContentInfoContent->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncryptedData, E_INVALIDP12)
		
		if(pdtEncryptedData->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCDATA;
			break;
		}

		//Now obtain the version number of the EncryptedData object
		DERTree* pdtEncDataVer = NULL;
		pdtEncDataVer = pdtEncryptedData->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncDataVer, E_INVALIDP12)
		
		if(pdtEncDataVer->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			hResult = E_INVALIDP12_WRONGENCDATAVER;
			break;
		}

		DWORD dwEncDataVer = 0;
		memcpy(&dwEncDataVer, pdtEncDataVer->currentBaseDER->pbData,pdtEncDataVer->currentBaseDER->cbData );

		if(dwEncDataVer != 0)
		{
			hResult = E_INVALIDP12_WRONGENCDATAVER;
			break;
		}

		//Next obtain the encryptedContentInfo object
		DERTree* pdtEncCI = NULL;
		pdtEncCI = pdtEncDataVer->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncCI, E_INVALIDP12)
		
		if(pdtEncCI->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCCI;
			break;
		}

		//Next obtain the encryptedContentInfo object's content type and ensure that it is data
		DERTree* pdtEncCIType = NULL;
		pdtEncCIType = pdtEncCI->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncCIType, E_INVALIDP12)
		
		if(pdtEncCIType->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGENCCITYPE;
			break;
		} 

		if(lstrcmp((LPCTSTR)pdtEncCIType->currentBaseDER->pbData, szOID_RSA_data))
		{
			hResult = E_INVALIDP12_WRONGENCCITYPE;
			break;
		}

		//Finally obtain the encryptionAlgorithmIdentifier
		DERTree* pdtEncAlgId = NULL;
		pdtEncAlgId = pdtEncCIType->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncAlgId, E_INVALIDP12)
		
		if(pdtEncAlgId->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCALGID;
			break;
		} 


		/*Obtain the encrypted blob*/
		
		//Obtain the encryptedContent Tag ([0] Tag)
		//The pbData of pdtEncContent points to the actual encrypted blob
		DERTree* pdtEncContent = NULL;
		pdtEncContent  = pdtEncAlgId->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncContent, E_INVALIDP12)
		
		if(	pdtEncContent->currentBaseDER->Class != CONTEXT_SPECIFIC ||
			pdtEncContent->currentBaseDER->Encoding != PRIMITIVE)
		{
			hResult = E_INVALIDP12_WRONGENCCONTENT;
			break;
		}


		/*Decrypt this data using the password and the contentEncryptionAlgorithm*/
		dwDecP12BlobSize = pdtEncContent->currentBaseDER->cbData;
		pbyteDecP12Blob = (PBYTE) new BYTE[dwDecP12BlobSize];
		PKCS12_CHECK_MEMALLOC(pbyteDecP12Blob)

		hResult = _DecryptP12Blob(pdtEncContent->currentBaseDER->pbData, pdtEncContent->currentBaseDER->cbData, 
									i_tbstrPassword, pdtEncAlgId, pbyteDecP12Blob, &dwDecP12BlobSize);

		PKCS12_CHECK_HRESULT

#ifdef DEBUG
		FILE* fp;
		fp = (FILE*)fopen("p12certs.bin","wb"); 
		for(unsigned int i=0;i<dwDecP12BlobSize; ++i)
		{
			fprintf(fp,"%c",pbyteDecP12Blob[i]);
		}
		fclose(fp);
#endif


		/*Obtain the certificates from the decrypted blob*/
		hResult = _ExtractCertsFromSafeBags(pbyteDecP12Blob, dwDecP12BlobSize);
		PKCS12_CHECK_HRESULT


	}while(0);

	PKCS12_FREE_MEM(pbyteDecP12Blob)

	return hResult;
}


HRESULT Pkcs12Info::_DecryptP12Blob(BYTE* in_pbyteEncBlob, DWORD i_dwEncBlobSize,_bstr_t& i_tbstrPassword, 
									DERTree* i_pdtEncAlgId, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize)
{
	HRESULT hResult = S_OK;
	BYTE byteAlg = 0;
	BYTE* pbyteSalt = NULL;
	DWORD dwSaltSize = 0;
	DWORD dwIterations = 0;
	BYTE* pbyteKey = NULL;
	BYTE* pbyteIV = NULL;

	do
	{
		/*Obtain the algorithm, salt and iteration to be used for decryption*/
		hResult = _GetDecryptionParams(i_pdtEncAlgId, &byteAlg, NULL, &dwSaltSize, &dwIterations);
		PKCS12_CHECK_HRESULT

		pbyteSalt = (BYTE*)new BYTE[dwSaltSize];
		PKCS12_CHECK_MEMALLOC(pbyteSalt)

		hResult = _GetDecryptionParams(i_pdtEncAlgId, &byteAlg, pbyteSalt, &dwSaltSize, &dwIterations);
		PKCS12_CHECK_HRESULT


		/*Obtain the key to be used for decryption from the password, salt and
		iteration*/
		/*Obtain the iv to be used for decryption from the password,salt and iteration*/
		/*Perform the decryption*/
		switch(byteAlg)
		{
			case ID_40BIT_RC2CBC :
				pbyteKey = new BYTE[RC2CBC_40BIT_KEYSIZE];
				PKCS12_CHECK_MEMALLOC(pbyteKey)

				hResult = _DoP12KeyGen(i_tbstrPassword,pbyteSalt, dwSaltSize, dwIterations,ID_ENCKEY,pbyteKey,RC2CBC_40BIT_KEYSIZE);
				PKCS12_CHECK_HRESULT

				pbyteIV = new BYTE[RC2CBC_IVSIZE];
				PKCS12_CHECK_MEMALLOC(pbyteIV)

				hResult = _DoP12KeyGen(i_tbstrPassword,pbyteSalt, dwSaltSize, dwIterations,ID_IV,pbyteIV,RC2CBC_IVSIZE);
				PKCS12_CHECK_HRESULT

				hResult = _DoRC2CBCDecrypt(pbyteKey, RC2CBC_40BIT_KEYSIZE, pbyteIV, in_pbyteEncBlob, i_dwEncBlobSize, o_pbyteDecBlob, o_pdwDecP12BlobSize);
				PKCS12_CHECK_HRESULT

				break;

			case ID_3DES :
				pbyteKey = new BYTE[DES3_KEYSIZE];
				PKCS12_CHECK_MEMALLOC(pbyteKey)

				hResult = _DoP12KeyGen(i_tbstrPassword,pbyteSalt, dwSaltSize, dwIterations,ID_ENCKEY,pbyteKey,DES3_KEYSIZE);
				PKCS12_CHECK_HRESULT

				hResult = _SetParity(pbyteKey, DES3_KEYSIZE);
				PKCS12_CHECK_HRESULT

				pbyteIV = new BYTE[DES3_IVSIZE]; 
				PKCS12_CHECK_MEMALLOC(pbyteIV)

				hResult = _DoP12KeyGen(i_tbstrPassword,pbyteSalt, dwSaltSize, dwIterations,ID_IV,pbyteIV,DES3_IVSIZE);
				PKCS12_CHECK_HRESULT

				hResult = _Do3DESDecrypt(pbyteKey, DES3_KEYSIZE, pbyteIV, in_pbyteEncBlob, i_dwEncBlobSize, o_pbyteDecBlob, o_pdwDecP12BlobSize);
				PKCS12_CHECK_HRESULT

				break;

		}
		PKCS12_CHECK_HRESULT

	}while(0);

	PKCS12_FREE_MEM(pbyteSalt)
	PKCS12_FREE_MEM(pbyteKey)
	PKCS12_FREE_MEM(pbyteIV)

	return hResult;
}


HRESULT Pkcs12Info::_GetDecryptionParams(DERTree* i_pdtEncAlgId, BYTE* o_pbyteEncAlg, BYTE* o_pbyteSalt, DWORD* o_pdwSaltSize, DWORD* o_pdwIterations)
{
	HRESULT hResult = S_OK;

	do
	{
		/*
		The encryption algorithm identifier object for the P12 is defined as 
		SEQUENCE {  
					algorithm OBJECT IDENTIFIER,
					parameters ANY DEFINED BY ALGORITHM OPTIONAL 
				 }
		where parameters is defined as
		SEQUENCE {
			salt OCTET STRING
			iterations INTEGER
		}
		*/
		/*Frist get the object identifier of the encryption algorithm and from that determine
		the encryption algorithm*/
		DERTree* pdtAlgObjId = i_pdtEncAlgId->rightDERTree;

		PKCS12_CHECK_FOR_NULL (pdtAlgObjId, E_INVALIDP12)


		if(pdtAlgObjId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGENCALGOBJID;
			break;
		}

		if(!lstrcmp((LPCTSTR)pdtAlgObjId->currentBaseDER->pbData, szOID_PBE_SHA_40RC2CBC))
		{
			*o_pbyteEncAlg = ID_40BIT_RC2CBC;
		}
		else if(!lstrcmp((LPCTSTR)pdtAlgObjId->currentBaseDER->pbData, szOID_PBE_SHA_3KEY_3DES))
		{
			*o_pbyteEncAlg = ID_3DES;
		}
		else
		{
			hResult = E_ENCALG_NOTSUPPORTED;
			break;
		}

		/*Next get the Salt*/

		//First obtain the encryption algorithm object's parameter structure
		DERTree* pdtEncAlgParam = pdtAlgObjId->nextDERTree;
		
		PKCS12_CHECK_FOR_NULL (pdtAlgObjId, E_INVALIDP12)


		if(pdtEncAlgParam->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCALGPARAM;
			break;
		}

		//Next obtain the salt value
		DERTree* pdtEncAlgSalt = pdtEncAlgParam->rightDERTree;
		
		PKCS12_CHECK_FOR_NULL (pdtEncAlgSalt, E_INVALIDP12)


		if(pdtEncAlgSalt->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_WRONGENCALGSALT;
			break;
		}

		*o_pdwSaltSize = pdtEncAlgSalt->currentBaseDER->cbData;

		if(o_pbyteSalt)
		{
			memcpy(o_pbyteSalt,
			pdtEncAlgSalt->currentBaseDER->pbData,
			pdtEncAlgSalt->currentBaseDER->cbData);
		}

		/*Obtain the number of iterations*/
		DERTree* pdtEncAlgIter = pdtEncAlgSalt->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncAlgIter, E_INVALIDP12)


		if(pdtEncAlgIter->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			hResult = E_INVALIDP12_WRONGENCALGITER;
			break;
		}

		memcpy(o_pdwIterations,pdtEncAlgIter->currentBaseDER->pbData,pdtEncAlgIter->currentBaseDER->cbData);


	}while(0);

	return hResult;
}

HRESULT Pkcs12Info::_DoRC2CBCDecrypt(BYTE* i_pbyteKey, DWORD dwKeyLen, BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize)
{
	HRESULT hResult = S_OK;
	void* pvoidCtxt = NULL;
	DWORD dwResidual = 0;

	do
	{
		ITEM itemKey;
		itemKey.len = dwKeyLen;
		itemKey.data = i_pbyteKey;

		if(SymDecryptDataBegin(SYM_RC2_CBC,&itemKey,dwKeyLen*8,&pvoidCtxt,i_pbyteIV,1))
		{
			hResult = E_RC2CBC_SYMDECBEGINFAIL;
			break;
		}

		if(SymDecryptDataUpdate(pvoidCtxt, i_pbyteEncBlob, i_dwEncBlobSize,o_pbyteDecBlob,(unsigned int*)o_pdwDecP12BlobSize))
		{
			hResult = E_RC2CBC_SYMDECUPDATEFAIL;
			break;
		}

		dwResidual = i_dwEncBlobSize - (*o_pdwDecP12BlobSize);
		if(SymDecryptDataEnd(pvoidCtxt,o_pbyteDecBlob+(*o_pdwDecP12BlobSize),(unsigned int*)&dwResidual))
		{
			hResult = E_RC2CBC_SYMDECENDFAIL;
			break;
		}
		(*o_pdwDecP12BlobSize) += dwResidual;
		pvoidCtxt = NULL;

	}while(0);

	return hResult;
}

HRESULT Pkcs12Info::_GetPrivateKey(_bstr_t& i_tbstrPassword, BYTE* i_pbyteAuthSafe, DWORD i_dwAuthSafeSize)
{
	HRESULT hResult = S_OK;
	do
	{
		CBaseDERCollection cbdcAuthSafe(i_dwAuthSafeSize, i_pbyteAuthSafe);
		CBaseDERHierarchy cbdhAuthSafe(cbdcAuthSafe);
		if ( 0 != cbdhAuthSafe.dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}


		//Did the decode work?
		if(cbdhAuthSafe.dwErrorCode)
		{
			hResult = E_INVALIDP12;
			break;
		}

		if(cbdhAuthSafe.m_DERTree.currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGAUTHTNTCDSAFE;
			break;
		}

		/*AuthenticatedSafe ::= SEQUENCE of ContentInfo*/
		/*Navigate to the first contentInfo structure in the authenticatedSafe sequence - 
		This is the one that contains the private key as a shroudedPKCS8*/
		DERTree* pdtShrPKCS8ContentInfo = NULL;

		pdtShrPKCS8ContentInfo = cbdhAuthSafe.m_DERTree.rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtShrPKCS8ContentInfo, E_INVALIDP12)

		if(pdtShrPKCS8ContentInfo->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGSHRP8CI;
			break;
		}

		/*Obtain the type of the shroudedP8 content info and confirm that it is 
		of type data*/
		DERTree* pdtShrPKCS8ContentInfoType = pdtShrPKCS8ContentInfo->rightDERTree;
		
		PKCS12_CHECK_FOR_NULL (pdtShrPKCS8ContentInfoType, E_INVALIDP12)

		if(pdtShrPKCS8ContentInfoType->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGSHRP8CITYPE;
			break;
		}
		
		if(lstrcmp((LPCTSTR)pdtShrPKCS8ContentInfoType->currentBaseDER->pbData, szOID_RSA_data))
		{
			hResult = E_INVALIDP12_WRONGSHRP8CITYPE;
			break;
		}

		/*Obtain the contents of the content info. These contents are a SafeBag*/
		DERTree* pdtShrPKCS8ContentInfoCtnt = pdtShrPKCS8ContentInfoType->nextDERTree;
		
		PKCS12_CHECK_FOR_NULL (pdtShrPKCS8ContentInfoCtnt, E_INVALIDP12)

		if(pdtShrPKCS8ContentInfoCtnt->currentBaseDER->Type != IMPLICIT)
		{
			hResult = E_INVALIDP12_WRONGSHRP8CICTNT;
			break;
		}

		/*Obtain the Value of the Contents from the contentinfo*/
		DERTree* pdtShrPKCS8ContentInfoCtntVal = pdtShrPKCS8ContentInfoCtnt->rightDERTree;
		
		PKCS12_CHECK_FOR_NULL (pdtShrPKCS8ContentInfoCtntVal, E_INVALIDP12)

		if(pdtShrPKCS8ContentInfoCtntVal->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_WRONGSHRP8CICTNT;
			break;
		}

		/*This octet string represents a SafeContents object which is defined as
		SafeContents = SEQUENCE of SafeBag
		SafeBag = SEQUENCE {
			bagId OBJECT IDENTIFIER
			bagValue [0] EXPLICIT
			bagAttributes SET Of PKCS12Attribute OPTIONAL
		}

		For a shroudedP8 Bag Type the SafeBag object's bagValue is an
		encrypted private key info object defined in PKCS8 as follows 

		EncryptedPrivateKeyInfo ::= SEQUENCE {
				encryptionAlgorithm EncryptionAlgorithmIdentifier,
				encryptedData EncryptedData 
				}

		*/

		/*Parse the octet string value to obtain the SafeContents*/
		CBaseDERCollection cbdcSafeContents(pdtShrPKCS8ContentInfoCtntVal->currentBaseDER->cbData,
							pdtShrPKCS8ContentInfoCtntVal->currentBaseDER->pbData);


		CBaseDERHierarchy cbdhSafeContents(cbdcSafeContents);
		if ( 0 != cbdhSafeContents.dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}


		//Did the decode work?
		if(cbdhSafeContents.dwErrorCode)
		{
			hResult = E_INVALIDP12;
			break;
		}

		if(cbdhSafeContents.m_DERTree.currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGSAFECTNTS;
			break;
		}

		/*Obtain the ShroudedP8 SafeBag*/
		DERTree* pdtShrP8SafeBag = cbdhSafeContents.m_DERTree.rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtShrP8SafeBag, E_INVALIDP12)

		if(pdtShrP8SafeBag->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGSHRP8SAFEBAGE;
			break;
		}

		/*Obtain this safe bag's id and ensure that it is of type ShroudedP8*/
		DERTree* pdtShrP8SafeBagId = pdtShrP8SafeBag->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtShrP8SafeBagId, E_INVALIDP12)

		if(pdtShrP8SafeBagId->currentBaseDER->Type != OBJECT_IDENTIFIER)
		{
			hResult = E_INVALIDP12_WRONGSHRP8SAFEBAGID;
			break;
		}

		if(lstrcmp((LPCTSTR)pdtShrP8SafeBagId->currentBaseDER->pbData, szOID_P12_BAGTYPE_SHRP8))
		{
			hResult = E_INVALIDP12_WRONGSHRP8SAFEBAGID;
			break;
		}

		/*Obtain the safe bag value*/
		DERTree* pdtShrP8SafeBagVal = pdtShrP8SafeBagId->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtShrP8SafeBagVal, E_INVALIDP12)

		if(pdtShrP8SafeBagVal->currentBaseDER->Type != IMPLICIT)
		{
			hResult = E_INVALIDP12_WRONGSHRP8SAFEBAGVAL;
			break;
		}

		/*This value is the EncryptedPrivateKeyInfo object. Get this object*/
		DERTree* pdtEncPrivKeyInfo = pdtShrP8SafeBagVal->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncPrivKeyInfo, E_INVALIDP12)

		if(pdtEncPrivKeyInfo->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCPRIVKEYINFO;
			break;
		}

		/*Obtain the encryption algorith identifier*/
		DERTree* pdtEncAlgId = pdtEncPrivKeyInfo->rightDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncAlgId, E_INVALIDP12)

		if(pdtEncAlgId->currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGENCALGID;
			break;
		}

		/*Obtain the encrypted data*/
		DERTree* pdtEncData = pdtEncAlgId->nextDERTree;
		PKCS12_CHECK_FOR_NULL (pdtEncData, E_INVALIDP12)

		if(pdtEncData->currentBaseDER->Type != OCTET_STRING)
		{
			hResult = E_INVALIDP12_WRONGENCALGID;
			break;
		}

		/*Decrypt this encrypted data using the password and the EncryptionAlgorithmIdentifier*/
		m_dwP8Size  = pdtEncData->currentBaseDER->cbData;
		m_pbyteP8 = (PBYTE) new BYTE[m_dwP8Size ];
		PKCS12_CHECK_MEMALLOC(m_pbyteP8)

		hResult = _DecryptP12Blob(pdtEncData->currentBaseDER->pbData,
					pdtEncData->currentBaseDER->cbData, 
					i_tbstrPassword, pdtEncAlgId, m_pbyteP8, &m_dwP8Size);

		PKCS12_CHECK_HRESULT

#ifdef DEBUG
		FILE* fp;
		fp = (FILE*)fopen("p12privkey.bin","wb"); 
		for(unsigned int i=0;i<m_dwP8Size; ++i)
		{
			fprintf(fp,"%c",m_pbyteP8[i]);
		}
		fclose(fp);
#endif


	}while(0);

	return hResult;
}

HRESULT Pkcs12Info::_Do3DESDecrypt(BYTE* i_pbyteKey, DWORD dwKeyLen, BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize)
{
	HRESULT hResult = S_OK;
	void* pvoidCtxt = NULL;
	DWORD dwResidual = 0;

	do
	{
		ITEM itemKey;
		itemKey.len = dwKeyLen;
		itemKey.data = i_pbyteKey;

		if(SymDecryptDataBegin(SYM_3DES,&itemKey,dwKeyLen*8,&pvoidCtxt,i_pbyteIV,1))
		{
			hResult = E_3DES_SYMDECBEGINFAIL;
			break;
		}

		if(SymDecryptDataUpdate(pvoidCtxt, i_pbyteEncBlob, i_dwEncBlobSize,o_pbyteDecBlob,(unsigned int*)o_pdwDecP12BlobSize))
		{
			hResult = E_3DES_SYMDECUPDATEFAIL; 
			break;
		}

		dwResidual = i_dwEncBlobSize - (*o_pdwDecP12BlobSize);
		if(SymDecryptDataEnd(pvoidCtxt,o_pbyteDecBlob+(*o_pdwDecP12BlobSize),(unsigned int*)&dwResidual))
		{
			hResult = E_3DES_SYMDECENDFAIL;
			break;
		}
		(*o_pdwDecP12BlobSize) += dwResidual;
		pvoidCtxt = NULL;

	}while(0);

	return hResult;
}


HRESULT Pkcs12Info::_ExtractCertsFromSafeBags(BYTE* i_pbyteSafeContents, DWORD i_dwSafeContentsSize)
{
	HRESULT hResult = S_OK;
	DWORD dwNumOfCerts = 0;
	DWORD* pdwCertSizes = NULL;
	BYTE** ppbyteCerts = NULL;

	do
	{
		CBaseDERCollection cbdcSafeContents(i_dwSafeContentsSize, i_pbyteSafeContents);
		CBaseDERHierarchy cbdhSafeContents(cbdcSafeContents);
		if ( 0 != cbdhSafeContents.dwErrorCode )
		{
			hResult =	E_VS_FAIL;
			break;
		}


		//Did the decode work?
		if(cbdhSafeContents.dwErrorCode)
		{
			hResult = E_INVALIDP12;
			break;
		}

		if(cbdhSafeContents.m_DERTree.currentBaseDER->Type != SEQUENCE)
		{
			hResult = E_INVALIDP12_WRONGCERTSAFECNTNTS;
			break;
		}

		/*Determine the number of safebags(certs) in the safe contents*/
		DERTree* pdtSafeBag = cbdhSafeContents.m_DERTree.rightDERTree;
		while(pdtSafeBag)
		{
			dwNumOfCerts++;
			pdtSafeBag = pdtSafeBag->nextDERTree;
		}

		if(!dwNumOfCerts)
		{
			hResult = E_NOCERTS_INP12;
			break;
		}

		/*Allocate memory*/
		ppbyteCerts  = (BYTE**)new PBYTE[dwNumOfCerts];
		PKCS12_CHECK_MEMALLOC(ppbyteCerts )
		memset(ppbyteCerts ,0, sizeof(PBYTE) * dwNumOfCerts);

		pdwCertSizes = new DWORD[dwNumOfCerts];
		PKCS12_CHECK_MEMALLOC(pdwCertSizes)

		/*Now obtain each cert*/
		pdtSafeBag = cbdhSafeContents.m_DERTree.rightDERTree;
		for(unsigned int i=0; i < dwNumOfCerts; ++i)
		{
			pdwCertSizes[i] = 0;

			if(pdtSafeBag->currentBaseDER->Type != SEQUENCE)
			{
				hResult = E_INVALIDP12_WRONGSAFEBAG;
				break;
			}

			/*Obtain the OID of the SafeBag Type*/
			DERTree* pdtSafeBagOID = pdtSafeBag->rightDERTree;
			PKCS12_CHECK_FOR_NULL (pdtSafeBagOID, E_INVALIDP12)

			if(pdtSafeBagOID->currentBaseDER->Type != OBJECT_IDENTIFIER)
			{
				hResult = E_INVALIDP12_WRONGSAFEBAGOID;
				break;
			}

			if(lstrcmp((LPCTSTR)pdtSafeBagOID->currentBaseDER->pbData, szOID_P12_BAGTYPE_CERT))
			{
				hResult = E_INVALIDP12_WRONGSAFEBAGOID;
				break;
			}

			/*Obtain the value of this safe bag*/
			DERTree* pdtSafeBagVal = pdtSafeBagOID->nextDERTree;
			PKCS12_CHECK_FOR_NULL (pdtSafeBagVal, E_INVALIDP12)

			if(pdtSafeBagVal->currentBaseDER->Type != IMPLICIT)
			{
				hResult = E_INVALIDP12_WRONGSAFEBAGVAL;
				break;
			}

			/*The value of the safe bag contains a sequence containing an oid 
			specifying the type of certificate (x509 and the actual cert)*/
			/*Obtain the CertSafeBag*/
			DERTree* pdtCertSafeBag = pdtSafeBagVal->rightDERTree;
			PKCS12_CHECK_FOR_NULL (pdtCertSafeBag, E_INVALIDP12)

			if(pdtCertSafeBag->currentBaseDER->Type != SEQUENCE)
			{
				hResult = E_INVALIDP12_WRONGCERTSAFEBAG;
				break;
			}

			/*Obtain the object identifier in the cert safe bag and ensure
			that it specifies an x509 cert*/
			DERTree* pdtCertSafeBagOID = pdtCertSafeBag->rightDERTree;

			PKCS12_CHECK_FOR_NULL (pdtCertSafeBagOID, E_INVALIDP12)

			if(pdtCertSafeBagOID->currentBaseDER->Type != OBJECT_IDENTIFIER)
			{
				hResult = E_INVALIDP12_WRONGCERTSAFEBAGOID;
				break;
			}

			if(lstrcmp((LPCTSTR)pdtCertSafeBagOID->currentBaseDER->pbData, szOID_X509_CERT))
			{
				hResult = E_INVALIDP12_WRONGCERTSAFEBAGOID;
				break;
			}

			/*Obtain the value of the cert safe bag*/
			DERTree* pdtCertSafeBagVal = pdtCertSafeBagOID->nextDERTree;
			PKCS12_CHECK_FOR_NULL (pdtCertSafeBagVal, E_INVALIDP12)

			if(pdtCertSafeBagVal->currentBaseDER->Type != IMPLICIT)
			{
				hResult = E_INVALIDP12_WRONGCERTSAFEBAGVAL;
				break;
			}


			/*Obtain the actual cert which is encoded as an OCTET STRING in the 
			bag value*/
			DERTree* pdtCert = pdtCertSafeBagVal->rightDERTree;
			PKCS12_CHECK_FOR_NULL (pdtCert, E_INVALIDP12)

			if(pdtCert->currentBaseDER->Type != OCTET_STRING)
			{
				hResult = E_INVALIDP12_WRONGCERT;
				break;
			}

			/*Allocate memory to store the cert blob*/
			pdwCertSizes[i] = pdtCert->currentBaseDER->cbData;
			ppbyteCerts [i] = (BYTE*) new BYTE[pdwCertSizes[i]];
			PKCS12_CHECK_MEMALLOC(ppbyteCerts [i])

			/*Store the cert blob*/
			memcpy(ppbyteCerts [i],
					pdtCert->currentBaseDER->pbData,
					pdwCertSizes[i]);

			/*Move on to the next cert*/
			pdtSafeBag = pdtSafeBag->nextDERTree;
		}

		PKCS12_CHECK_HRESULT

	}while(0);

	if(hResult == S_OK)
	{
		m_dwNumOfCerts = dwNumOfCerts;
		m_pdwCertSizes = pdwCertSizes;
		m_ppbyteCerts = ppbyteCerts;
	}
	else
	{
		if(ppbyteCerts)
		{
			for(unsigned int i=0;i<dwNumOfCerts;++i)
			{
				PKCS12_FREE_MEM(ppbyteCerts[i])
				ppbyteCerts[i] = NULL;			
			}
		}
		PKCS12_FREE_MEM(ppbyteCerts)
		ppbyteCerts = NULL;
		
		PKCS12_FREE_MEM(pdwCertSizes);
		pdwCertSizes = NULL;
		dwNumOfCerts = 0;
	}

	return hResult;
}

int Pkcs12Info::get_NumOfCerts()
{
	if(bInitialized)
		return m_dwNumOfCerts;
	else 
		return 0;
}

int Pkcs12Info::get_CertSize(DWORD dwCertNum)
{
	if(bInitialized)
	{
		return m_pdwCertSizes[dwCertNum];
	}
	else
		return 0;
}

HRESULT Pkcs12Info::GetCert(DWORD i_dwCertNum, PBYTE i_pbyteCertBlob)
{
	if(!i_pbyteCertBlob)
		return E_INVALIDPARAMS;

	memcpy(i_pbyteCertBlob, m_ppbyteCerts[i_dwCertNum], m_pdwCertSizes[i_dwCertNum]);
	return S_OK;
}

HRESULT Pkcs12Info::GetPKCS8(BYTE* i_pbytePKCS8, DWORD* o_pdwPKCS8Size)
{
	*o_pdwPKCS8Size = m_dwP8Size;
	if(!i_pbytePKCS8)
	{
		return S_OK;
	}

	memcpy(i_pbytePKCS8,m_pbyteP8,m_dwP8Size);

	return S_OK;

	
}