#include "stdafx.h"
#include "vsprs.h"
#include "certinfo.h"


/////PTA related headers files///////////////

#include "ptav3.h"
#include "ptadllapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"

#define		VS_RC2								26114
#define		VS_RC4								26625
#define		VS_SHA_1							32772
#define		VS_MD2								32769
#define		VS_MD5								32771
#define		VS_RSA_SIGN							9216
#define		VS_RSA_KEYX							41984

#define		RSA_MIN_PAD_LEN						11
#define		VS_MD2_OID							szOID_RSA_MD2
#define		VS_MD5_OID							szOID_RSA_MD5
#define		VS_SHA1_OID							szOID_OIWSEC_sha1

#define		SYMMETRIC_KEY_LENGTH				128

#define		VS_SHA_1							32772

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

extern IVSPTA *pVSPTA;

HRESULT CProxyRecipients::VSPRS_Decrypt(VS_PKCS7_INFO *Pkcs7Info, BYTE **pByteDecBlob, DWORD *dwDecBlobLen)
{
	
	HRESULT		retVal = S_OK;	

	DWORD		SelectedCert = 0;

	LPSTR pSerialNumber = NULL, pIssureDN = NULL;
	bool found = FALSE;

	
	do
	{
		mMsgInfo.SmimeType = MSG_Enc;

		// must be enveloped data.
		if (Pkcs7Info == NULL) {
			retVal = VSPRS_NULL_PTR_EXCEPTION;
			break;
		}
		 
		if(Pkcs7Info->ePKCS7Type != PKCS7_ENVELOPED) {
			retVal = VSPRS_PKCS7_TYPE_IS_NOT_ENVELOPED_MESSAGE_TYPE;
			break;
		}

		/////////////////////////PTA////////////////////////////////////////

		if (!mPtaOpened) {
			if ((retVal=InitPTA()) != S_OK) break;
			mPtaOpened = TRUE;
		}
		

		if ((retVal=SelectCert(Pkcs7Info, &SelectedCert)) != S_OK) break;


		VARIANT   varEncSessionKey,varResult;
   		
		VariantInit(&varEncSessionKey);
		VariantInit(&varResult);

		varEncSessionKey.vt =	VT_ARRAY;
		varEncSessionKey.parray =	SafeArrayCreateVector(VT_UI1, 0, Pkcs7Info->EncryptedDataInfo.pRecipientInfo->EncryptedKey.cbData);
		if ( NULL == varEncSessionKey.parray )
		{
			break;
		}

		memcpy((BYTE*)varEncSessionKey.parray->pvData, Pkcs7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.pbData, 
													Pkcs7Info->EncryptedDataInfo.pRecipientInfo[SelectedCert].EncryptedKey.cbData);


		if ((retVal = pVSPTA->DecryptSessionKey(varEncSessionKey, &varResult)) != S_OK)
			break;
		

		/////////
		BYTE        *pbSessionKey;
		DWORD       dwKeyLen=0;
		

		retVal=SafeArrayAccessData(varResult.parray,(void HUGEP**)&pbSessionKey);
		if(retVal==S_OK)
		{
			
			LONG lBound, uBound;
			SafeArrayGetLBound((SAFEARRAY FAR*)varResult.parray, 1, &lBound);
			SafeArrayGetUBound((SAFEARRAY FAR*)varResult.parray, 1, &uBound);
			dwKeyLen = uBound - lBound + 1;



		}

	

		*dwDecBlobLen=Pkcs7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.cbData;
		*pByteDecBlob=(BYTE *)malloc(*dwDecBlobLen);

		reverse(Pkcs7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.cbData,
			Pkcs7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.pbData);

		reverse(Pkcs7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.cbData,
				Pkcs7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData);

		retVal=DecryptPKCS7BlobWithSessionKey((BYTE*)pbSessionKey,dwKeyLen,
					 Pkcs7Info->EncryptedDataInfo.EncryptedContent.ContentEncryptionAlgID.Parameters.pbData,
					 //NULL,
					 Pkcs7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.pbData,
					 Pkcs7Info->EncryptedDataInfo.EncryptedContent.EncryptedContent.cbData,
					 *pByteDecBlob,
					 dwDecBlobLen
					 );

		if(retVal!=S_OK) break;
		
		SafeArrayUnaccessData(varResult.parray);
		

	    /////////////////////////////////////////////////////////////////////////////

	} while(0);

	//ReleasePTA();


    if (retVal == 0) mCStatus = CS_Dec;

	return (retVal);
}

HRESULT  CProxyRecipients::DecryptSignature(PCERT_INFO   pSignerCertInfo, BYTE *pbSignature,
									   DWORD dwSignature, BYTE **pbHash, DWORD *dwHash)
{

	HRESULT				hr;
	A_RSA_KEY			RSA_Enc_PublicKey;
	void*				pContext;
	int                 nResult; 

	BYTE				*pbPaddedHash = NULL;
	DWORD				dwPaddedHash = 0;

	BYTE				*pbUnPaddedHash = NULL;
	DWORD				dwUnPaddedHash = 0;

	hr=GetRSAKeyFromKeyInfo(pSignerCertInfo->SubjectPublicKeyInfo,&RSA_Enc_PublicKey);
	if(hr!=S_OK)
	{
		//Fails
	}

	nResult=RSADataBegin(&RSA_Enc_PublicKey,(void**) &pContext);
	if(nResult!=0)
	{
		//Fails
		return E_FAIL;
	}
	
	pbPaddedHash = (BYTE*)malloc(dwSignature);
	dwPaddedHash =  dwSignature;

	reverse(dwSignature, pbSignature);
	nResult= RSADataUpdate(pContext,pbSignature,dwSignature,pbPaddedHash, 
					(unsigned int*)&dwPaddedHash);
	if(nResult!=0)
	{
		//Fails
		return E_FAIL;
	}
	nResult =	RSADataEnd(pContext);
	if(nResult!=0)
	{
		//Fails
		return E_FAIL;
	}

	if(UnPadDataForVerify(pbPaddedHash,dwPaddedHash,&pbUnPaddedHash,&dwUnPaddedHash) != S_OK)
	{
		return E_FAIL;
	}

	nResult =	GetDataFromSequence(pbUnPaddedHash,dwUnPaddedHash,VS_SHA_1,
						pbHash,dwHash);

	if (pbPaddedHash) free(pbPaddedHash);
	if (pbUnPaddedHash) delete(pbUnPaddedHash);

	return S_OK;
}

HRESULT CProxyRecipients::MyHashData(int i_nHashAlg,BYTE  *pInputData, DWORD InputDataLength,
										  BYTE	**pbyteHash,DWORD   *pdwHashLength)
{
	
		void*		pvHashCtxt;
		int			nResult;

		HRESULT		hr = S_OK;


		if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
		{
			//HashBegin Fail
			return -1 ;
		}

	    nResult=HashData(i_nHashAlg,pvHashCtxt,(unsigned char*) pInputData,
						(unsigned int) InputDataLength	);
		if (nResult!=0 )
		{
			// HashData Function fail
			return -1;
		}
		
		//Allocate memory for the hash algorithm
		switch(i_nHashAlg)
		{
		case HASH_SHA1 :
			*pdwHashLength = 20;
			*pbyteHash = new BYTE[20];
			break;

		case HASH_MD2 :
		case HASH_MD5:
			*pdwHashLength = 16;
			*pbyteHash = new BYTE[16];
			break;

		default :
			//retVal = E_INVALIDFLAGS;
			break;
		}

		if(HashEnd(i_nHashAlg,pvHashCtxt,(unsigned char*)*pbyteHash,*pdwHashLength) == -1)
		{
			return -1;
		}
		

		return hr;
}

HRESULT CProxyRecipients::GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, A_RSA_KEY* o_pTheKey)
{
	HRESULT retVal = S_OK;

	o_pTheKey->modulus.data = o_pTheKey->exponent.data = NULL;
	
	CBaseDERCollection cbdcTheKeySeq(i_CertPublicKeyInfo.PublicKey.cbData, i_CertPublicKeyInfo.PublicKey.pbData);
	CBaseDERHierarchy cbdhTheKeySeq(cbdcTheKeySeq);
	DERTree* pdtTheKeySeq = &cbdhTheKeySeq.m_DERTree;
	if(!pdtTheKeySeq && pdtTheKeySeq->currentBaseDER->Type != SEQUENCE)
	{
		retVal = -1;
	}
	else
	{
		/*Get the modulus*/
		DERTree* pdtTheMod = pdtTheKeySeq->rightDERTree;
		if(!pdtTheMod && pdtTheMod->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = -1;
		}
		else
		{
			PBYTE pbyteRawData;

			o_pTheKey->modulus.len = pdtTheMod->currentBaseDER->cbData;
			o_pTheKey->modulus.data = new BYTE[o_pTheKey->modulus.len];

			pbyteRawData = pdtTheMod->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheMod->currentBaseDER->BaseDERBlob->cbData - pdtTheMod->currentBaseDER->cbData);

			if(*pbyteRawData)
				memcpy(o_pTheKey->modulus.data, pbyteRawData,o_pTheKey->modulus.len);
			else if(o_pTheKey->modulus.len > 1)
			{
				o_pTheKey->modulus.len --;
				memcpy(o_pTheKey->modulus.data, pbyteRawData+1,o_pTheKey->modulus.len);
			}
			else
				retVal = -1;

		}

		/*Get the exponent*/
		DERTree* pdtTheExp;
		if(retVal == S_OK)
		{
			pdtTheExp = pdtTheMod->nextDERTree;
			if(!pdtTheExp && pdtTheExp->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				retVal = E_INVALIDASNKEYENC;
			}
			else
			{
				PBYTE pbyteRawData;

				o_pTheKey->exponent.len = pdtTheExp->currentBaseDER->cbData;
				o_pTheKey->exponent.data = new BYTE[o_pTheKey->exponent.len];

				pbyteRawData = pdtTheExp->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheExp->currentBaseDER->BaseDERBlob->cbData - pdtTheExp->currentBaseDER->cbData);
				if(*pbyteRawData)
					memcpy(o_pTheKey->exponent.data, pbyteRawData,o_pTheKey->exponent.len);
				else if(o_pTheKey->exponent.len > 1)
				{
					o_pTheKey->exponent.len --;
					memcpy(o_pTheKey->exponent.data, pbyteRawData+1,o_pTheKey->exponent.len);
				}
				else
					retVal = -1;
			}

		}
	}

	return retVal;
}

HRESULT	CProxyRecipients::UnPadDataForVerify(const BYTE*	i_cpbyteData,const DWORD	i_cdwDataLen,
						   BYTE**	o_ppbyteUnPaddedData,DWORD*	o_pdwUnPaddedDataLen)
{
	HRESULT						hResult						=	E_FAIL;

	DWORD						dwBlockLength				=	0;
	DWORD						dwLengthOfPadding			=	0;
	DWORD						dwNumOfFFs					=	0;

	BOOL						boolSuccessFlag				=	TRUE;

	while (1)
	{
		//	check if the length of the data is equal to the length of the modulus of the key
		//
		//	this is the block length for assymetric operations
		/* Need to pass the modulus as an input
		if ( i_cdwDataLen != (RSA_Verify_PublicKey.modulus).len )
		{
			hResult =	E_FAIL;
			break;
		}
		*/

		//
		//	the padding is of the form
		//	0x00 0x01 0xFF....0xFF 0x00
		//

				//	check the 0x00
		if ( 0x00 != i_cpbyteData [0] )
		{
			hResult =	E_FAIL;
			break;
		}

				//	check the 0x01
		if ( 0x01 != i_cpbyteData [1] )
		{
			hResult =	E_FAIL;
			break;
		}

				//	get the number of 0xFF
		while ( 0x00 != i_cpbyteData [2 + dwNumOfFFs] )
		{
			if ( 0xFF != i_cpbyteData [2 + dwNumOfFFs] )
			{
				hResult =	E_FAIL;
				boolSuccessFlag =	FALSE;
				break;
			}

			dwNumOfFFs ++;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	calculate the total length of padding. it should be atleast 11 bytes. if its less
			//	then return error
		dwLengthOfPadding =	dwNumOfFFs + 3; // not sure why we are getting extra 16 unwanted bytes
		if ( RSA_MIN_PAD_LEN > dwLengthOfPadding )
		{
			hResult =	E_FAIL;
			break;
		}

		*o_pdwUnPaddedDataLen =	i_cdwDataLen - dwLengthOfPadding ;

			//	allocate memory
		*o_ppbyteUnPaddedData =	new BYTE [*o_pdwUnPaddedDataLen];
		//CHECK_ALLOCATED_MEMORY (*o_ppbyteUnPaddedData)

				//	copy data into out buffer
		memcpy
		(
			(void*) *o_ppbyteUnPaddedData,
			(const void*) &(i_cpbyteData [dwLengthOfPadding]),
			*o_pdwUnPaddedDataLen
		);

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}

HRESULT  CProxyRecipients::GetDataFromSequence(const BYTE* i_cpbyteDataInSequence,const DWORD	i_cdwDataLenInSequence,
	const DWORD			i_cdwAlgID,	BYTE** 	o_ppbyteData,DWORD*	o_pdwDataLen)
{
	HRESULT						hResult						=	E_FAIL;

	_DERTree*					pstructDataSequence			=	NULL;
	_DERTree*					pstructAlgoID				=	NULL;
	_DERTree*					pstructObjectId				=	NULL;
	_DERTree*					pstructData					=	NULL;

	CHAR						szAlgoID [MAX_PATH];
	int							nStrCmp						=	999;

//	CSequence*					pCSeqAlgoID					=	NULL;
//	CObjectIdentifier*			pCoiAlgoID					=	NULL;

	while (1)
	{
			//	copy the data in sequence in a temp base DER collection
		CBaseDERCollection	CbdcData ( (_DWORD) i_cdwDataLenInSequence, (_BYTE*) i_cpbyteDataInSequence );

			//	copy the collection into a hierarchy
		CBaseDERHierarchy	CbdhData ( CbdcData );

		pstructDataSequence =	&(CbdhData.m_DERTree);
		if ( NULL != pstructDataSequence )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructDataSequence -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	this will point to the algo sequence
		pstructAlgoID =	pstructDataSequence -> rightDERTree;
		if ( NULL != pstructAlgoID )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructAlgoID -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}
				//	this will point to the object identifier
		pstructObjectId =	pstructAlgoID -> rightDERTree;
		if ( NULL != pstructObjectId )
		{
					//	check if its a object identifier
			if ( OBJECT_IDENTIFIER != ( (pstructObjectId -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	copy the object identifier into the string
		memcpy
		(
			(void*) szAlgoID,
			(const void*) (pstructObjectId -> currentBaseDER) -> pbData,
			(pstructObjectId -> currentBaseDER) -> cbData
		);

		szAlgoID [ (pstructObjectId -> currentBaseDER) -> cbData ] =	NULL;

		switch ( i_cdwAlgID )
		{
			case	VS_SHA_1:
				nStrCmp =	lstrcmp ( szAlgoID, VS_SHA1_OID );
				break;

			case	VS_MD2:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD2_OID );
				break;

			case	VS_MD5:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD5_OID );
				break;

			default:
				break;
		}

		if ( 0 != nStrCmp )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

				//	this will point to the data OCTET STRING
		pstructData =	pstructAlgoID -> nextDERTree;
		if ( NULL != pstructData )
		{
					//	check if its a octet string
			if ( OCTET_STRING != ( (pstructData -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	allocate memory for the data
		*o_pdwDataLen =	(pstructData -> currentBaseDER) -> cbData;
		*o_ppbyteData =	new BYTE [*o_pdwDataLen];
		

				//	copy the data into the out buffer
		memcpy
		(
			(void*) *o_ppbyteData,
			(const void*) (pstructData -> currentBaseDER) -> pbData,
			*o_pdwDataLen
		);
			
		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	

LPTSTR CProxyRecipients::GetCertIssuerDN(VS_RECIPIENT_INFO *pCertInfo)
{
	CERT_NAME_BLOB NameBlob;
	DWORD dwSize = 0, dwError;
	LPTSTR lpIssuerDN = NULL;
	LPTSTR lpFormattedDN = NULL;

	if(!pCertInfo)
		return NULL;

	NameBlob.cbData = pCertInfo->Issuer.cbData;
	NameBlob.pbData=  pCertInfo->Issuer.pbData;

    // Call CertNameToStr to get the Subject RDN string length.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
		      CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, NULL, dwSize);

	// This function always returns a null char (0), so the minimum count returned 
	// will be 1, even if nothing got converted.
    if(dwSize <= 1) 
	{
		dwError = GetLastError();
		return NULL;
	}

    // Allocate memory for the returned string.
    lpIssuerDN = (LPTSTR)malloc((dwSize + 1) * sizeof(TCHAR));
    if(!lpIssuerDN)
	{
		return NULL;
	}
	
    // Call CertNameToStr to get the string.
    dwSize = CertNameToStr(MY_ENCODING_TYPE, &NameBlob,
			  CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, lpIssuerDN, dwSize);

    if(dwSize <= 1)
	{
		dwError = GetLastError();
	
		free(lpIssuerDN);
        return NULL;
	}
    
	// new PTA format is different from old one
	// Strip only quotes from the issuer dn 
	if((lpFormattedDN = (LPTSTR)malloc(sizeof(TCHAR)*(lstrlen(lpIssuerDN) + 1))) == NULL)
	{
		free(lpIssuerDN);
		return NULL;
	}
	else
	{
		for(int i = 0, j = 0; i <lstrlen(lpIssuerDN); i++)
		{
			if(lpIssuerDN[i] != '"')
			{
				lpFormattedDN[j] = lpIssuerDN[i];
				j++;
			}
		}

		lpFormattedDN[j] = '\0';
	}

	free(lpIssuerDN);
	return lpFormattedDN;

}

LPTSTR CProxyRecipients::GetCertSerNum(VS_RECIPIENT_INFO *pCertInfo)
{
	CRYPT_INTEGER_BLOB SerialNumberBlob ;
	DWORD dwSerialNumber = 0;
	PBYTE SerialNumber ;
	LPTSTR lpSerNum;

	if(!pCertInfo)
		return NULL;

    SerialNumberBlob.cbData = pCertInfo->SerialNumber.cbData;
	SerialNumberBlob.pbData=  pCertInfo->SerialNumber.pbData;
	dwSerialNumber = SerialNumberBlob.cbData;
	
	if((SerialNumber = (PBYTE)malloc(dwSerialNumber)) == NULL)
	{
		
		return NULL;
	}
	else
	{
		// Reverse the bytes
		unsigned int i;
		for (i = 0; i < dwSerialNumber; i++)
			SerialNumber[dwSerialNumber-1-i] = SerialNumberBlob.pbData[i] ;

		if((lpSerNum = (LPTSTR)malloc(((dwSerialNumber*2)+1)*sizeof(TCHAR))) == NULL)
		{
			free(SerialNumber);
			return NULL;
		}
		else
		{
			for(i = 0; i < dwSerialNumber; i++)
				sprintf((lpSerNum)+(i*2), "%02x", (unsigned char)SerialNumber[i]) ;
			
			free(SerialNumber);
		}
	}

	return lpSerNum;

}

HRESULT CProxyRecipients::DecryptPKCS7BlobWithSessionKey(BYTE* i_pbyteKey, DWORD dwKeyLen,
				  BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize,
				  BYTE* o_pbyteDecBlob, DWORD* o_pdwDecBlobSize)
{
	HRESULT hResult = S_OK;
	void* pvoidCtxt = NULL;
	DWORD dwResidual = 0;
	ITEM itemKey;

	itemKey.len = dwKeyLen;
	itemKey.data=(unsigned char *)malloc(dwKeyLen);

	do
	{
		

		memcpy(itemKey.data , i_pbyteKey,dwKeyLen);
		//////Tell Bsafelite to strip off padding
		if(SymDecryptDataBegin(SYM_RC2_CBC,&itemKey,dwKeyLen*8,&pvoidCtxt,i_pbyteIV,1))
		{
			hResult = -1;
			break;
		}

		if(SymDecryptDataUpdate(pvoidCtxt, i_pbyteEncBlob, i_dwEncBlobSize,
			o_pbyteDecBlob,(unsigned int*)o_pdwDecBlobSize))
		{
			hResult = -1;
			break;
		}

		dwResidual = i_dwEncBlobSize - (*o_pdwDecBlobSize);
		if(SymDecryptDataEnd(pvoidCtxt,o_pbyteDecBlob+(*o_pdwDecBlobSize),
			(unsigned int*)&dwResidual))
		{
			hResult = -1;
			break;
		}
		(*o_pdwDecBlobSize) += dwResidual;
		pvoidCtxt = NULL;

		

	}while(0);

	if (itemKey.data != NULL) free(itemKey.data);

	return hResult;
}


HRESULT CProxyRecipients::VSPRS_Encrypt(ITEM **iEncCerts, ITEM *iDataToBeEncrypted, ITEM *outBlob)
{

	HRESULT rc = S_OK;
	
	unsigned char *pbBuffer = NULL;
	PCERT_INFO			pEncCertInfo;

	do {


		// Do this for just 1 enc cert.
		if (iEncCerts == NULL || iDataToBeEncrypted == NULL) {
			rc = VSPRS_NULL_PTR_EXCEPTION;
			break;
		}

		CCertInfo encCertInfo(iEncCerts[0]->data, iEncCerts[0]->len);

		// Step 1. Create sufficient memory.
		DWORD dwCount = 0, dwTemp = 0;
		dwTemp=iDataToBeEncrypted->len;
		if(dwTemp % 8 == 0)
		{
			dwCount = dwTemp + 8;
		}
		else
		{
			dwCount = dwTemp + (8 - dwTemp%8);
		}
		pbBuffer = (BYTE *)malloc(dwCount);
		if (pbBuffer != NULL)
		{
			memcpy(pbBuffer, iDataToBeEncrypted->data, dwCount);
		}

		DWORD  dwDataLen=dwTemp;
		ITEM i_pRCKey;

		unsigned char initVector[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

		if ((rc = VSBSafeGenSessionKey(16, &i_pRCKey)) != S_OK) break;

		if ((rc =  VSBSafeEncrypt(SYM_RC2_CBC,
				   &i_pRCKey,
				   128,
				   initVector, 
				   pbBuffer,
				   (unsigned int*)&dwDataLen,
				   dwCount
				   )) != S_OK) break;


		unsigned char *pbEncData;
		unsigned int dwEncData;
	
		pEncCertInfo = encCertInfo.GetCertInfo();

		if ((rc = VSBSafePublicKeyEncrypt(&pEncCertInfo->SubjectPublicKeyInfo,
						i_pRCKey.data,
						i_pRCKey.len,
						&pbEncData,
						&dwEncData
						)) != S_OK) break;
		///////////////////prepare pkcs7//////////////////////////
		
		char szObjId[512];
		

		VS_ENCRYPTED_CONTENT_INFO EncryptedContentData;
	//	EncryptedContentData.EncryptedContent.cbData = dwCount;
		EncryptedContentData.EncryptedContent.cbData = dwDataLen;
		EncryptedContentData.EncryptedContent.pbData = (unsigned char*)pbBuffer;


		strcpy(szObjId, szOID_RSA_RC2CBC);
	//	strcpy(szObjId, szOID_RSA_DES_EDE3_CBC);


		//EncryptedContentData.ContentEncryptionAlgID.pszObjId = szObjId;
		EncryptedContentData.ContentEncryptionAlgID.pszObjId =(char *)malloc(strlen(szObjId)+1);
		if(EncryptedContentData.ContentEncryptionAlgID.pszObjId==NULL)
		{
			return -1;
		}

		strcpy(EncryptedContentData.ContentEncryptionAlgID.pszObjId,szObjId);

		EncryptedContentData.ContentEncryptionAlgID.Parameters.cbData = 8;
		EncryptedContentData.ContentEncryptionAlgID.Parameters.pbData = initVector;


		PVS_RECIPIENT_INFO pRecipientInfo[1];
		//PVS_RECIPIENT_INFO pRecipientInfo[2];

		VS_RECIPIENT_INFO RecipientInfo ;
		VS_RECIPIENT_INFO RecipientInfo1 ;


		RecipientInfo.Issuer.cbData = pEncCertInfo->Issuer.cbData;
		RecipientInfo.Issuer.pbData = pEncCertInfo->Issuer.pbData;

		RecipientInfo.SerialNumber.cbData = pEncCertInfo->SerialNumber.cbData;
		RecipientInfo.SerialNumber.pbData = pEncCertInfo->SerialNumber.pbData;

		RecipientInfo.EncryptedKey.cbData = dwEncData;
		RecipientInfo.EncryptedKey.pbData = (unsigned char*)pbEncData; //skip simpleblob headers



		strcpy(szObjId, szOID_RSA_RSA);

		RecipientInfo.KeyEncryptionAlgID.pszObjId  =(char *)malloc(strlen(szObjId)+1);
		if(RecipientInfo.KeyEncryptionAlgID.pszObjId==NULL)
		{
			return -1;
		}

		strcpy(RecipientInfo.KeyEncryptionAlgID.pszObjId,szObjId); 

		/// for second recipient
		RecipientInfo1.Issuer.cbData = pEncCertInfo->Issuer.cbData;
		RecipientInfo1.Issuer.pbData = pEncCertInfo->Issuer.pbData;

		RecipientInfo1.SerialNumber.cbData = pEncCertInfo->SerialNumber.cbData;
		RecipientInfo1.SerialNumber.pbData = pEncCertInfo->SerialNumber.pbData;

		
		RecipientInfo1.EncryptedKey.cbData = dwEncData;
		RecipientInfo1.EncryptedKey.pbData = (unsigned char*)pbEncData; //skip simpleblob headers


		strcpy(szObjId, szOID_RSA_RSA);

		RecipientInfo1.KeyEncryptionAlgID.pszObjId  =(char *)malloc(strlen(szObjId)+1);
		if(RecipientInfo1.KeyEncryptionAlgID.pszObjId==NULL)
		{
			return -1;
		}

		strcpy(RecipientInfo1.KeyEncryptionAlgID.pszObjId,szObjId); 



		pRecipientInfo[0] = &RecipientInfo;
		//pRecipientInfo[1] = &RecipientInfo1;


		CreateEnvelopedData(&EncryptedContentData,
							pRecipientInfo,
							//2,
							1,
							(char **)&outBlob->data);

		 outBlob->len = strlen((char *)outBlob->data);


		

	} while (0);
	

	return rc;
}
