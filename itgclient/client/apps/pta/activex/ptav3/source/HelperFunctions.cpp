#include "stdafx.h"

#include "..\Include\virtualsmartcard.h"
#include "..\include\HelperFunctions.h"
#include "..\include\cspincludes.h"
#include "..\include\cspglobals.h"
#include "..\include\utils.h"

extern CVirtualSmartCard* _gpVirtualSmartCard;
//	#include "globals.h"

//extern	CSP_State*		g_phProv;
//extern	DWORD			g_dwNumberOfCSPHandles;

/*
HRESULT		GetLastNode 
(
	CSP_State**						o_ppCSP
)
{
	HRESULT				hResult				=	E_VS_FAIL;
	DWORD				i;

	while (1)
	{
		*o_ppCSP =	g_phProv;

		for ( i = 0; i < g_dwNumberOfCSPHandles; i ++ )
		{
//			*o_ppCSP =	(*o_ppCSP) -> pNextHandle;
		}

		hResult =	VS_SUCCESS;
	}	//	end		while (1)
	
	return	hResult;
}	//	end		GetLastNode

*/

HRESULT		CheckProv
(
	CSP_State*						i_pCSP
)
{
	if ( NULL == i_pCSP )
	{
		return	E_POINTER;
	}

	if ( sizeof (CSP_State) == i_pCSP -> dwSizeofStruct )
	{
		return	S_OK;
	}
	else
	{
		return	NTE_BAD_UID;
	}
}


HRESULT		AddHashNode
(
	CSP_State*						i_pCSP,
	CSP_HashParam*					i_pHash
)
{
	HRESULT							hResult				=	E_FAIL;

	CSP_HashParam*					pHash				=	NULL;

	while (1)
	{
				//	check if first hash object for this CSP context
		if ( NULL == i_pCSP -> pHashParam )
		{
			i_pCSP -> pHashParam =	i_pHash;
			i_pHash -> pBack =	NULL;
			i_pHash -> pNext =	NULL;
		}
		else
		{
				//	traverse the linked list till the end
			pHash =	i_pCSP -> pHashParam;

			while ( NULL != pHash -> pNext )
			{
				pHash =	pHash -> pNext;
			}
			pHash -> pNext =	i_pHash;
			i_pHash -> pBack =	pHash;
		}

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		AddHashNode


HRESULT		CheckHashNode
(
	const	CSP_State*				i_cpCSP,
	const	CSP_HashParam*			i_cpHash
)
{
	CSP_HashParam*		pHash;
	int					nFound		=	0;

	if ( NULL == i_cpCSP -> pHashParam )
	{
		nFound =	0;
	}
	else
	{
		pHash =	i_cpCSP -> pHashParam;

		while ( NULL != pHash )
		{
			if ( i_cpHash == pHash )
			{
				nFound =	1;
				break;
			}
			else
			{
				pHash =	pHash -> pNext;
			}
		}
	}

	if ( 1 == nFound )
	{
		return	S_OK;
	}
	else
	{
		return	NTE_BAD_HASH;
	}
}	//	end		CheckHashNode


HRESULT		DeleteHashNode
(
	CSP_State*						i_pCSP,
	CSP_HashParam*					i_pHash
)
{
	CSP_HashParam*		pHash		=	NULL;
	int					nDeleted	=	0;

	CSP_HashParam*		pHashBefore	=	NULL;
	CSP_HashParam*		pHashAfter	=	NULL;


	if ( NULL == i_pCSP -> pHashParam )
	{
		nDeleted =	0;
	}
	else
	{
		pHash =	i_pCSP -> pHashParam;

		while ( NULL != pHash )
		{
			if ( i_pHash == pHash )
			{
				pHashBefore	=	pHash -> pBack;
				pHashAfter	=	pHash -> pNext;

					//	check if this is the last node. in that case the pHashAfter is NULL
				if ( NULL != pHashAfter )
				{
					pHashAfter -> pBack		=	pHashBefore;
				}

					//	check if this is the first node. in that case the pHashBefore is NULL
				if ( NULL != pHashBefore )
				{
					pHashBefore -> pNext	=	pHashAfter;
				}

					//	if the first node is deleted then also make the CSP -> hash pointer = pHashAfter
					//	if this is the only node then pHashAfte is NULL
				if ( pHash == i_pCSP -> pHashParam )
				{
					i_pCSP -> pHashParam =	pHashAfter;
				}

				delete	pHash;
				pHash =	NULL;

				nDeleted =	1;
				break;
			}
			else
			{
				pHash =	pHash -> pNext;
			}
		}
	}

	if ( 1 == nDeleted )
	{
		return	S_OK;
	}
	else
	{
		return	NTE_BAD_HASH;
	}
}	//	end		DeleteHashNode


void	DeleteHashChain
(
	CSP_State*						i_pCSP
)
{
	CSP_HashParam*					pHash				=	NULL;
	CSP_HashParam*					pHashNext			=	NULL;

	pHash =	i_pCSP -> pHashParam;

	while ( NULL != pHash )
	{
		pHashNext =	pHash -> pNext;
		delete	pHash;
		pHash =	pHashNext;
	}

	return;
}


HRESULT		AddKeyNode
(
	CSP_State*						i_pCSP,
	CSP_KeyParam*					i_pKey
)
{
	HRESULT							hResult				=	E_FAIL;

	CSP_KeyParam*					pKey				=	NULL;

	while (1)
	{
				//	check if first key object for this CSP context
		if ( NULL == i_pCSP -> pKeyParam )
		{
			i_pCSP -> pKeyParam =	i_pKey;
			i_pKey -> pBack =	NULL;
			i_pKey -> pNext =	NULL;
		}
		else
		{
				//	traverse the linked list till the end
			pKey =	i_pCSP -> pKeyParam;

			while ( NULL != pKey -> pNext )
			{
				pKey =	pKey -> pNext;
			}
			pKey -> pNext =	i_pKey;
			i_pKey -> pBack = pKey;
		}

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		AddKeyNode


HRESULT		CheckKeyNode
(
	const	CSP_State*				i_cpCSP,
	const	CSP_KeyParam*			i_cpKey
)
{
	CSP_KeyParam*		pKey;
	int					nFound		=	0;

	if ( NULL == i_cpCSP -> pKeyParam )
	{
		nFound =	0;
	}
	else
	{
		pKey =	i_cpCSP -> pKeyParam;

		while ( NULL != pKey )
		{
			if ( i_cpKey == pKey )
			{
				nFound =	1;
				break;
			}
			else
			{
				pKey =	pKey -> pNext;
			}
		}
	}

	if ( 1 == nFound )
	{
		return	S_OK;
	}
	else
	{
		return	NTE_BAD_KEY;
	}
}	//	end		CheckKeyNode


HRESULT		DeleteKeyNode
(
	CSP_State*						i_pCSP,
	CSP_KeyParam*					i_pKey
)
{
	CSP_KeyParam*		pKey		=	NULL;
	int					nDeleted	=	0;

	CSP_KeyParam*		pKeyBefore	=	NULL;
	CSP_KeyParam*		pKeyAfter	=	NULL;


	if ( NULL == i_pCSP -> pKeyParam )
	{
		nDeleted =	0;
	}
	else
	{
		pKey =	i_pCSP -> pKeyParam;

		while ( NULL != pKey )
		{
			if ( i_pKey == pKey )
			{
				pKeyBefore	=	pKey -> pBack;
				pKeyAfter	=	pKey -> pNext;

					//	check if this is the last node. in that case the pKeyAfter is NULL
				if ( NULL != pKeyAfter )
				{
					pKeyAfter -> pBack		=	pKeyBefore;
				}

					//	check if this is the first node. in that case the pKeyBefore is NULL
				if ( NULL != pKeyBefore )
				{
					pKeyBefore -> pNext	=	pKeyAfter;
				}

					//	if the first node is deleted then also make the CSP -> key pointer = pKeyAfter
					//	if this is the only node then pKeyAfter is NULL
				if ( pKey == i_pCSP -> pKeyParam )
				{
					i_pCSP -> pKeyParam =	pKeyAfter;
				}

				delete	pKey;
				pKey =	NULL;

				nDeleted =	1;
				break;
			}
			else
			{
				pKey =	pKey -> pNext;
			}
		}
	}

	if ( 1 == nDeleted )
	{
		return	S_OK;
	}
	else
	{
		return	NTE_BAD_KEY;
	}
}	//	end		DeleteKeyNode


void	DeleteKeyChain
(
	CSP_State*						i_pCSP
)
{
	CSP_KeyParam*					pKey				=	NULL;
	CSP_KeyParam*					pKeyNext			=	NULL;

	pKey =	i_pCSP -> pKeyParam;

	while ( NULL != pKey )
	{
		pKeyNext =	pKey -> pNext;
		delete	pKey;
		pKey =	pKeyNext;
	}

	return;
}





/*

HRESULT		AddNode
(
	const	CSP_State*				i_cpCSP
)
{
	HRESULT				hResult				=	E_VS_FAIL;
	CSP_State*			pCSP				=	NULL;
	DWORD				i;

	while (1)
	{
		pCSP =	g_phProv;

		for ( i = 0; i < g_dwNumberOfCSPHandles; i++ )
		{
//			pCSP =	pCSP -> pNextHandle;
		}

//		pCSP -> pNextHandle = (CSP_State*) i_cpCSP;
		g_dwNumberOfCSPHandles ++;

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	return	hResult;
}	//	end		AddNode
*/


HRESULT		CheckIfKeyExists
(
	CSP_State*			i_pCSP,
	CVirtualSmartCard*	i_pVSmartCard,
	const DWORD			i_cdwAlgID,
	CSP_Key_Container*	o_pstructContainer
)
{
	HRESULT						hResult				=	E_FAIL;

	BOOL						boolSuccessFlag		=	FALSE;

	BYTE*						pbyteContainerContents	=	NULL;
	DWORD						dwContainerContentsLen	=	0;

	_bstr_t						tbstrContainerName;

	while (1)
	{
		tbstrContainerName = i_pCSP -> pszNameOfContainer;

					//	get the info blob
		hResult =	i_pVSmartCard -> VSM_GetInformationBlob
					(
						tbstrContainerName,
						NULL,
						&dwContainerContentsLen
					);
		VSCSP_CHECK_HRESULT_AND_BREAK

		pbyteContainerContents =	new BYTE [dwContainerContentsLen];
		CHECK_ALLOCATED_MEMORY (pbyteContainerContents)

		hResult =	i_pVSmartCard -> VSM_GetInformationBlob
					(
						tbstrContainerName,
						pbyteContainerContents,
						&dwContainerContentsLen
					);

		memcpy
		(
			(void*)	o_pstructContainer,
			(const void*) pbyteContainerContents,
			dwContainerContentsLen
		);

		switch ( i_cdwAlgID )
		{
			case	VS_RSA_KEYX:
				if ( VS_CSP_KEY_EXISTS != (o_pstructContainer -> structXchg).dwExists )
				{
					hResult =	NTE_NO_KEY;
					break;
				}

				boolSuccessFlag =	TRUE;
				break;

			case	VS_RSA_SIGN:
				if ( VS_CSP_KEY_EXISTS != (o_pstructContainer -> structSign).dwExists )
				{
					hResult =	NTE_NO_KEY;
					break;
				}

				boolSuccessFlag =	TRUE;
				break;

			default:
				hResult =	NTE_BAD_ALGID;
				break;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteContainerContents, dwContainerContentsLen)
//	VSPTA_CLEAN_TBSTR(tbstrContainerName)

	return	hResult;
}	//	end		HRESULT		CheckIfKeyExists

HRESULT		CheckIfContainerExists
(
	CSP_State*			i_pCSP,
	CVirtualSmartCard*	i_pVSmartCard
)
{
	HRESULT						hResult				=	E_FAIL;

//	BYTE*						pbyteData			=	NULL;
	DWORD						dwDataLen			=	0;

	_bstr_t						tbstrContainerName;

	while (1)
	{
		tbstrContainerName =	i_pCSP -> pszNameOfContainer;

					//	check if the container exists
					//
					//	passing NULL for the pbData will return the required length
					//	in dwData. If the container does not exists then an error
					//	will be returned.
					//	since we are interested in knowing if the container exists and not
					//	the actual contents we will not allocate memory and make second
					//	call to this function
		hResult =	i_pVSmartCard -> VSM_GetInformationBlob
					(
						tbstrContainerName,
						NULL,
						&dwDataLen
					);
		if ( VS_SUCCESS != hResult )
		{
			hResult =	NTE_BAD_KEYSET;
			break;
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

//	VSPTA_CLEAN_TBSTR(tbstrContainerName)

	return	hResult;
}


HRESULT		ExportSessionKey
(
	CSP_State*						i_cpCSP,
	const CSP_KeyParam*				i_cpKey,
	CSP_KeyParam*					i_pPubKey,
	BYTE**							o_ppbyteKey,
	DWORD*							o_pdwKeyLen
)
{
	HRESULT						hResult						=	E_FAIL;

	BLOBHEADER					structBlobHeader;

	DWORD						algid;

	BYTE*						pbyteEncryptedKey			=	NULL;
	DWORD						dwEncryptedKeyLen			=	0;

	CVirtualSmartCard*			pVSmartCard					=	NULL;

	void*						pvoidContext				=	NULL;

	while (1)
	{
			//	create the blobheader structure
		structBlobHeader.bType		=	SIMPLEBLOB;
		structBlobHeader.bVersion	=	CUR_BLOB_VERSION;
		structBlobHeader.reserved	=	0;
		structBlobHeader.aiKeyAlg	=	i_cpKey -> dwAlgID;

		algid						=	CALG_RSA_KEYX;

		hResult =	GetVSC
					(
						i_cpCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT_AND_BREAK

		if ( VS_TPM_CSP == i_cpCSP -> dwCSPName )
		{
			hResult =	pVSmartCard -> VSTPM_EncryptDecryptBegin
						(
							i_pPubKey -> pVSTSSKey,
							&(i_pPubKey -> pVSTSSData)
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSTPM_Encrypt
						(
							i_pPubKey -> pVSTSSData,
							(i_cpKey -> itemKey).data,
							(i_cpKey -> itemKey).len,
							NULL,
							&dwEncryptedKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			pbyteEncryptedKey =	new BYTE [dwEncryptedKeyLen];
			CHECK_ALLOCATED_MEMORY (pbyteEncryptedKey)

			hResult =	pVSmartCard -> VSTPM_Encrypt
						(
							i_pPubKey -> pVSTSSData,
							(i_cpKey -> itemKey).data,
							(i_cpKey -> itemKey).len,
							pbyteEncryptedKey,
							&dwEncryptedKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSTPM_EncryptDecryptEnd
						(
							i_pPubKey -> pVSTSSData
						);
			VSCSP_CHECK_HRESULT_AND_BREAK
		}
		else
		{
			hResult =	pVSmartCard -> VSM_EncryptBegin
						(
							i_pPubKey -> pbyteCorrPublicKey,
							i_pPubKey -> dwCorrPublicKeyLen,
							&pvoidContext
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSM_EncryptUpdate
						(
							pvoidContext,
							TRUE,
							(i_cpKey -> itemKey).data,
							(i_cpKey -> itemKey).len,
							NULL,
							&dwEncryptedKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			pbyteEncryptedKey =	new BYTE [dwEncryptedKeyLen];
			CHECK_ALLOCATED_MEMORY (pbyteEncryptedKey)

			hResult =	pVSmartCard -> VSM_EncryptUpdate
						(
							pvoidContext,
							TRUE,
							(i_cpKey -> itemKey).data,
							(i_cpKey -> itemKey).len,
							pbyteEncryptedKey,
							&dwEncryptedKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSM_EncryptEnd
						(
							pvoidContext
						);
			VSCSP_CHECK_HRESULT_AND_BREAK
		}

		*o_pdwKeyLen =	dwEncryptedKeyLen + sizeof (BLOBHEADER) + sizeof (ALG_ID);
		*o_ppbyteKey =	new BYTE [*o_pdwKeyLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteKey)

		memcpy
		(
			(void*) (*o_ppbyteKey),
			(const void*) &structBlobHeader,
			sizeof (BLOBHEADER)
		);

		memcpy
		(
			(void*) &((*o_ppbyteKey) [sizeof (BLOBHEADER)]),
			(const void*) &algid,
			sizeof (ALG_ID)
		);

#if 1
		// Wasim : May 16, 2002. Reversing the encrypted session key before returning. Put it in the 
		// correct byte order. This was done bcos we discovered that decrypting data was failing when
		// encryption was done by a CSP other that VeriSign CSP. A similar fix has been done in ImportSessionKey()
		// for the same reason.
		PBYTE pbRevEncKey = NULL;
		DWORD dwRevEncKeyLen = dwEncryptedKeyLen;
		pbRevEncKey = new BYTE [dwRevEncKeyLen];
		for ( DWORD z = 0; z < dwRevEncKeyLen; z++ )
		{
			pbRevEncKey [z] =	pbyteEncryptedKey [ dwRevEncKeyLen - z - 1];
		}

#endif

		memcpy
		(
			(void*) &((*o_ppbyteKey) [sizeof (BLOBHEADER) + sizeof (ALG_ID)]),
			(const void*) /*pbyteEncryptedKey*/pbRevEncKey,
			/*dwEncryptedKeyLen*/dwRevEncKeyLen
		);

		VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbRevEncKey, dwRevEncKeyLen)

		hResult =	VS_SUCCESS;
		break;
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbyteEncryptedKey, dwEncryptedKeyLen)


	return	hResult;
}

HRESULT		ExportPublicKey
(
	CSP_State*						i_cpCSP,
	const CSP_KeyParam*				i_cpKey,
	BYTE**							o_ppbyteKey,
	DWORD*							o_pdwKeyLen
)
{
	HRESULT						hResult						=	E_FAIL;

	BLOBHEADER					structBlobHeader;
	RSAPUBKEY					structRSA_PubKey;

	CVirtualSmartCard*			pVSmartCard					=	NULL;

	BYTE*						pbyteKey					=	NULL;
	DWORD						dwKeyLen					=	0;
	BYTE*						pbyteRevKey					=	NULL;
	DWORD						dwRevKeyLen					=	0;


	DWORD						Algid						=	999;

	A_RSA_KEY					RSA_PubKey;

	DWORD						dwModulusLen				=	0;
	BYTE*						pbyteModulus				=	NULL;

	while (1)
	{
		hResult =	GetVSC
					(
						i_cpCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT_AND_BREAK

		structBlobHeader.bType		=	PUBLICKEYBLOB;		//	0x06
		structBlobHeader.bVersion	=	CUR_BLOB_VERSION;	//	0x02
		structBlobHeader.reserved	=	0;
//		structBlobHeader.aiKeyAlg	=	Algid;
		structBlobHeader.aiKeyAlg	=	i_cpKey -> dwAlgID;


		if ( VS_TPM_CSP == i_cpCSP -> dwCSPName )
		{
			hResult =	(i_cpKey -> pVSTSSKey) -> GetModulus
						(
							&dwModulusLen,
							&pbyteModulus
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			structRSA_PubKey.magic		=	0x31415352;			//	public key - "RSA1"
			structRSA_PubKey.bitlen		=	dwModulusLen * 8;	//	key len
			structRSA_PubKey.pubexp		=	65537;	//	TBD check if this is true

			dwRevKeyLen =	dwModulusLen;
			pbyteRevKey	=	new BYTE [dwRevKeyLen];
			CHECK_ALLOCATED_MEMORY (pbyteRevKey)

			for (DWORD x = 0; x < dwRevKeyLen; x++ )
			{
				pbyteRevKey [x] = (pbyteModulus) [dwRevKeyLen - x - 1];
			}
		}
		else
		{
						//	get the public key from the smart card
			hResult =	pVSmartCard -> VSM_ExportKey
						(
							i_cpKey -> pbyteCorrPublicKey,
							i_cpKey -> dwCorrPublicKeyLen,
							0,			//	IGNORED
							NULL,		//	IGNORED
							0,			//	IGNORED
							VS_CSP_EXPORT_PUBLIC_KEY,
							NULL,
							&dwKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

						//	allocate memory for the public key
			pbyteKey =	new BYTE [dwKeyLen];
			CHECK_ALLOCATED_MEMORY (pbyteKey)

						//	get the public key from the smart card
			hResult =	pVSmartCard -> VSM_ExportKey
						(
							i_cpKey -> pbyteCorrPublicKey,
							i_cpKey -> dwCorrPublicKeyLen,
							0,			//	IGNORED
							NULL,		//	IGNORED
							0,			//	IGNORED
							VS_CSP_EXPORT_PUBLIC_KEY,
							pbyteKey,
							&dwKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	GetKeyFromBlob
						(
							pbyteKey,
							dwKeyLen,
							&RSA_PubKey
						);
			VSCSP_CHECK_HRESULT_AND_BREAK


			structRSA_PubKey.magic		=	0x31415352;			//	public key - "RSA1"
			structRSA_PubKey.bitlen		=	(RSA_PubKey.modulus).len * 8;	//	key len
			structRSA_PubKey.pubexp		=	65537;	//	TBD check if this is true

			dwRevKeyLen =	(structRSA_PubKey.bitlen / 8);
			pbyteRevKey	=	new BYTE [dwRevKeyLen];
			CHECK_ALLOCATED_MEMORY (pbyteRevKey)

			for (DWORD x = 0; x < dwRevKeyLen; x++ )
			{
				pbyteRevKey [x] = ((RSA_PubKey.modulus).data) [dwRevKeyLen - x - 1];
			}
		}

		*o_pdwKeyLen =	sizeof (BLOBHEADER) + sizeof (RSAPUBKEY) + (structRSA_PubKey.bitlen / 8);
		*o_ppbyteKey =	new BYTE [*o_pdwKeyLen];
		CHECK_ALLOCATED_MEMORY (*o_ppbyteKey)

		memcpy
		(
			(void*) *o_ppbyteKey,
			(const void*) &structBlobHeader,
			sizeof (BLOBHEADER)
		);

		memcpy
		(
			(void*) &((*o_ppbyteKey)[sizeof (BLOBHEADER)]),
			(const void*) &structRSA_PubKey,
			sizeof ( RSAPUBKEY)
		);

		memcpy
		(
			(void*) &((*o_ppbyteKey)[sizeof (BLOBHEADER) + sizeof (RSAPUBKEY)]),
			pbyteRevKey,
			dwRevKeyLen
		);

		hResult =	VS_SUCCESS;
		break;
	}

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKey, dwKeyLen)
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevKey, dwRevKeyLen)
	//VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteModulus, dwModulusLen)
	return	hResult;
}

HRESULT		ImportSessionKey
(
	CSP_State*						i_cpCSP,
	CSP_KeyParam*					i_pPubKey,
	const BYTE*						i_cpbyteKey,
	const DWORD						i_cdwKeyLen,
	CSP_KeyParam**					o_ppKey
)
{
	HRESULT						hResult						=	E_FAIL;
	DWORD						nResult						=	999;
	DWORD						dwEncKeyLen					=	0;
	DWORD						dwDecKeyLen					=	0;
	CVirtualSmartCard*			pVSmartCard					=	NULL;
	void*						pvoidContext				=	NULL;
	BLOBHEADER					structBlobHeader;

	BYTE*						pbyteEncKey					=	NULL;

	while (1)
	{
		memcpy
		(
			(void*) &structBlobHeader,
			(const void*) i_cpbyteKey,
			sizeof (BLOBHEADER)
		);

		hResult =	GetVSC
					(
						i_cpCSP,
						&pVSmartCard
					);
		VSCSP_CHECK_HRESULT_AND_BREAK

		dwEncKeyLen =	i_cdwKeyLen - sizeof (BLOBHEADER) - sizeof (DWORD);

		(*o_ppKey) -> itemKey.data	=	new BYTE [dwEncKeyLen];
		CHECK_ALLOCATED_MEMORY ((*o_ppKey) -> itemKey.data)

		(*o_ppKey) -> itemKey.len =	dwEncKeyLen;
		dwDecKeyLen =	dwEncKeyLen;

		pbyteEncKey =	(BYTE*)&(i_cpbyteKey [sizeof (BLOBHEADER) + sizeof ( ALG_ID)]);


		
#if 1
		// Wasim : May 16, 2002. Reversing the encrypted session key. Put it in the 
		// correct byte order. This was done bcos we discovered that decrypting data was failing when
		// encryption was done by a CSP other that VeriSign CSP. A similar fix has been done in ExportSessionKey()
		// for the same reason.
		PBYTE pbRevEncKey = NULL;
		DWORD dwRevEncKeyLen = dwEncKeyLen;
		pbRevEncKey = new BYTE [dwRevEncKeyLen];
		for ( DWORD z = 0; z < dwRevEncKeyLen; z++ )
		{
			pbRevEncKey [z] =	pbyteEncKey [ dwRevEncKeyLen - z - 1];
		}


#endif

		if ( VS_TPM_CSP == i_cpCSP -> dwCSPName )
		{
			hResult =	pVSmartCard -> VSTPM_EncryptDecryptBegin
						(
							i_pPubKey -> pVSTSSKey,
							&(i_pPubKey -> pVSTSSData)
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSTPM_Decrypt
						(
							i_pPubKey -> pVSTSSData,
							/*pbyteEncKey*/pbRevEncKey,
							/*dwEncKeyLen*/dwRevEncKeyLen,
							(*o_ppKey) -> itemKey.data,
							&dwDecKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	pVSmartCard -> VSTPM_EncryptDecryptEnd
						(
							i_pPubKey -> pVSTSSData
						);
			VSCSP_CHECK_HRESULT_AND_BREAK
		}
		else
		{
			nResult =	pVSmartCard -> VSM_DecryptBegin
						( 
							i_pPubKey -> pbyteCorrPublicKey,
							i_pPubKey -> dwCorrPublicKeyLen,
							(void**) &(pvoidContext)
						);
			VSCSP_CHECK_NRESULT
				
			nResult =	pVSmartCard -> VSM_DecryptUpdate
						(
							(void*) pvoidContext,
							TRUE,
							/*pbyteEncKey*/pbRevEncKey,
							/*dwEncKeyLen*/dwRevEncKeyLen,
							(*o_ppKey) -> itemKey.data,
							&dwDecKeyLen
						);
			VSCSP_CHECK_NRESULT;

			nResult =	pVSmartCard -> VSM_DecryptEnd
						(
							pvoidContext
						);
			VSCSP_CHECK_NRESULT
		}

		((*o_ppKey) -> itemKey).len = dwDecKeyLen;
		(*o_ppKey) -> dwAlgID		=	structBlobHeader.aiKeyAlg;

		if ( CALG_RC4 == structBlobHeader.aiKeyAlg )
			(*o_ppKey) -> dwBlockLen	=	0;
		else
			(*o_ppKey) -> dwBlockLen	=	VS_CSP_DEFAULT_BLOCK_LENGTH;

		(*o_ppKey) -> dwCypherModes	=	VS_CSP_DEFAULT_CYPHER_MODES;
		(*o_ppKey) -> dwModeBits	=	0;
		(*o_ppKey) -> dwKeyLenBits	=	dwDecKeyLen * 8;	//	Anand		March 26, 2001
		(*o_ppKey) -> dwPadding		=	PKCS5_PADDING;
		(*o_ppKey) -> dwPermissions			=	CRYPT_DECRYPT | CRYPT_ENCRYPT | CRYPT_EXPORT | CRYPT_READ | CRYPT_WRITE;

		if ( VS_RC2 == structBlobHeader.aiKeyAlg )
		{
				//	this parameter is used only if its a rc2 key
			(*o_ppKey) -> dwEffectiveKeyLen		=	dwDecKeyLen * 8;	//	Anand		March 26, 2001
		}
		else
		{
			(*o_ppKey) -> dwEffectiveKeyLen		=	0;
		}

		(*o_ppKey) -> dwInitVectorLength		=	VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
		(*o_ppKey) -> pbyteInitVector =	new BYTE [(*o_ppKey) -> dwInitVectorLength];
		CHECK_ALLOCATED_MEMORY ((*o_ppKey) -> pbyteInitVector)
		::memcpy
		(
			(void*) (*o_ppKey) -> pbyteInitVector,
			(const void*) VS_CSP_DEFAULT_INIT_VECTOR,
			VS_CSP_DEFAULT_BLOCK_LENGTH / 8
		);

		VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(pbRevEncKey, dwRevEncKeyLen)

		hResult =	VS_SUCCESS;
		break;
	}

	return	hResult;
}

HRESULT		ImportPublicKey
(
	CSP_State*						i_cpCSP,
	const BYTE*						i_cpbyteKey,
	const DWORD						i_cdwKeyLen,
	const DWORD						i_cdwFlags,
	CSP_KeyParam**					o_ppKey
)
{
	HRESULT						hResult						=	E_FAIL;

	BLOBHEADER					structBlobHeader;
	RSAPUBKEY					structRSA_PubKey;

	CVirtualSmartCard*			pVSmartCard					=	NULL;

	BYTE*						pbyteKey					=	NULL;
	DWORD						dwKeyLen					=	0;
	BYTE*						pbyteRevKey					=	NULL;
	DWORD						dwRevKeyLen					=	0;

	DWORD						Algid						=	999;

	A_RSA_KEY					RSA_PubKey;

	DWORD						dwKeyType					=	0;

	unsigned char f4Data[3] = {0x01, 0x00, 0x01 };

	while (1)
	{
		memcpy
		(
			(void*) &structBlobHeader,
			(const void*) i_cpbyteKey,
			sizeof (BLOBHEADER)
		);

		memcpy
		(
			(void*) &structRSA_PubKey,
			(const void*) &(i_cpbyteKey[sizeof (BLOBHEADER)]),
			sizeof ( RSAPUBKEY)
		);

		(RSA_PubKey.modulus).len =	(structRSA_PubKey.bitlen / 8);
		(RSA_PubKey.modulus).data =	new BYTE [(RSA_PubKey.modulus).len];
		CHECK_ALLOCATED_MEMORY ((RSA_PubKey.modulus).data)
		pbyteRevKey	=	new BYTE [(RSA_PubKey.modulus).len];
		CHECK_ALLOCATED_MEMORY (pbyteRevKey)
		dwRevKeyLen	=	(RSA_PubKey.modulus).len;

		memcpy
		(
			(void*) pbyteRevKey,
			(const void*) &(i_cpbyteKey[sizeof (BLOBHEADER) + sizeof (RSAPUBKEY)]),
			(RSA_PubKey.modulus).len
		);
		
		for (DWORD x = 0; x < (RSA_PubKey.modulus).len; x++ )
		{
			((RSA_PubKey.modulus).data) [x] = pbyteRevKey [(RSA_PubKey.modulus).len - x - 1];
		}

		if ( PUBLICKEYBLOB != structBlobHeader.bType )
		{
			hResult =	NTE_BAD_TYPE;
			break;
		}
		
		if ( CUR_BLOB_VERSION != structBlobHeader.bVersion )
		{
			hResult =	NTE_BAD_VER;
			break;
		}

		if ( 0 != structBlobHeader.reserved)
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

		if ( 0x31415352 != structRSA_PubKey.magic )
		{
			hResult =	NTE_BAD_DATA;
			break;
		}

		if ( 65537 != structRSA_PubKey.pubexp )	//	TBD check if this is true
		{
			hResult =	NTE_BAD_ALGID;
			break;
		}
		(RSA_PubKey.exponent).len =	3;
		(RSA_PubKey.exponent).data =	new BYTE [(RSA_PubKey.exponent).len];
		CHECK_ALLOCATED_MEMORY ((RSA_PubKey.exponent).data)
		memcpy
		(
			(void*) (RSA_PubKey.exponent).data,
			(const void*) f4Data,
			(RSA_PubKey.exponent).len
		);
	
		(*o_ppKey) -> dwAlgID		=	structBlobHeader.aiKeyAlg;
		(*o_ppKey) -> dwBlockLen	=	VS_CSP_DEFAULT_BLOCK_LENGTH;
		(*o_ppKey) -> dwCypherModes	=	VS_CSP_DEFAULT_CYPHER_MODES;
		(*o_ppKey) -> dwModeBits	=	0;
		(*o_ppKey) -> dwKeyLenBits	=	i_cdwFlags >> 16;
		(*o_ppKey) -> dwPermissions	=	CRYPT_DECRYPT | CRYPT_ENCRYPT | CRYPT_EXPORT | CRYPT_READ | CRYPT_WRITE;
		(*o_ppKey) -> dwSaltLength  =	0;
		(*o_ppKey) -> dwPadding		=	PKCS5_PADDING;
		(*o_ppKey) -> dwInitVectorLength  =	  VS_CSP_DEFAULT_BLOCK_LENGTH / 8;
		(*o_ppKey) -> pbyteInitVector	  =	  new BYTE [(*o_ppKey) -> dwInitVectorLength];
		CHECK_ALLOCATED_MEMORY ((*o_ppKey) -> pbyteInitVector)
		::memcpy
		(
			(void*) (*o_ppKey) -> pbyteInitVector,
			(const void*) VS_CSP_DEFAULT_INIT_VECTOR,
			VS_CSP_DEFAULT_BLOCK_LENGTH / 8
		);

		if ( VS_TPM_CSP == i_cpCSP -> dwCSPName )
		{
			dwKeyType =	TSS_KEY_TYPE_LEGACY;

/*
			(*o_ppKey) -> pVSTSSKey =	new (VS_TSS_Key)
										(
											i_cpCSP -> pVSTSSContext,
											(const DWORD) dwKeyType,
											(RSA_PubKey.modulus).len,
											(RSA_PubKey.modulus).data,
											&hResult
										);
*/

		}
		else
		{
			hResult =	GetBlobFromKey
						(
							&RSA_PubKey,
							&pbyteKey,
							&dwKeyLen
						);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult =	GetVSC
				(
					i_cpCSP,
					&pVSmartCard
				);
			VSCSP_CHECK_HRESULT_AND_BREAK

			hResult = pVSmartCard -> VSM_ImportKey
					  ( pbyteKey,
						dwKeyLen,
 						NULL,
						0,
						0,
						0,
						0,
						NULL,
						&((*o_ppKey) -> dwCorrPublicKeyLen)
					  );
			VSCSP_CHECK_HRESULT_AND_BREAK

			(*o_ppKey) ->  pbyteCorrPublicKey =	new BYTE [(*o_ppKey) -> dwCorrPublicKeyLen];
			CHECK_ALLOCATED_MEMORY (((*o_ppKey) ->  pbyteCorrPublicKey))

			hResult = pVSmartCard -> VSM_ImportKey
					  ( pbyteKey,
						dwKeyLen,
						NULL,
						0,
						0,
						0,
						0,
						(*o_ppKey) ->  pbyteCorrPublicKey,
						&((*o_ppKey) -> dwCorrPublicKeyLen)
					  );
			VSCSP_CHECK_HRESULT_AND_BREAK
		}

		hResult =	VS_SUCCESS;
		break;
	}	//	end		while (1)

	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteRevKey, dwRevKeyLen)
	VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteKey, dwKeyLen)

	return	hResult;
}

HRESULT		GetVSC
(
	CSP_State*						i_pCSP,
	CVirtualSmartCard**				o_ppVSC
)
{
	HRESULT				hResult		=	E_FAIL;
	CSP_KeyParam*		pclassKey	=	NULL;

	while (1)
	{
		if ( VS_TPM_CSP == i_pCSP -> dwCSPName )
		{
			//	its the TPM CSP call
			if ( NULL == _gpVirtualSmartCard )
			{
					//	if the virtual smart card is NOT created then create one
				_gpVirtualSmartCard =	new	CVirtualSmartCard;

				//	NOTE: in old PTA the ProfMgmp_OpenProfile () call will
				//	create the virtual smart card and will also do lots of
				//	initialization etc. for the time being we are not doing
				//	all those steps. we will add them later if required.
			}

				//	either the virtual smart card is created or it already
				//	existed... in anyways give that pointer out
			*o_ppVSC = _gpVirtualSmartCard;

			//	NOTE: since this is just a CSP at the moment we are not
			//	going to fill the exchange/signature key pairs and other
			//	details for the container...
			//
			//	NOT sure if it will be required.
			//	if its required then add that code similar to whats there
			//	in the PTA CSP case.
		}
		else
		{
				//	its the PTA CSP or just the PTA
			if ( NULL == _gpVirtualSmartCard )
			{

				hResult =	(i_pCSP -> pIProfMgmt) -> ProfMgmt_OpenProfile ();
				if ( VS_SUCCESS != hResult )
				{
					if ( E_CARDALREADYOPEN != hResult )
					{
						return	hResult;
					}
				}
			}

			*o_ppVSC = _gpVirtualSmartCard;

			// If container name is NULL then the public keys don't exist so can't
			// fill the structures
			if ( NULL != i_pCSP -> pszNameOfContainer )
			{
					//	check if both the corresponding pub key hashes are NULL
					//
					//	NOTE: if only one is NULL then it means that one of the keys is missing. i.e. teh container
					//			contains only one key
					//			if we try to load both the keys again just because one of them is NULL
					//			then decrypt/encrypt becomes very slow.
					//
				if ( (NULL == i_pCSP -> pbyteCorrSignPublicKey) && (NULL == i_pCSP -> pbyteCorrXchgPublicKey) )
				{
						//	create a new instance of the key class
					pclassKey =	new (CSP_KeyParam);
					CHECK_ALLOCATED_MEMORY (pclassKey)

					pclassKey -> dwAlgID =	VS_RSA_SIGN;

					hResult =	(*o_ppVSC) -> VSM_GetUserKeyHandle
								(
									i_pCSP -> pszNameOfContainer,
									pclassKey -> dwAlgID,
									&(pclassKey -> dwKeyLenBits),
									&(pclassKey -> dwExportable),
									NULL,
									&(pclassKey -> dwCorrPublicKeyLen)
								);
					VSCSP_CHECK_HRESULT_AND_BREAK

					pclassKey -> pbyteCorrPublicKey =	new BYTE [pclassKey -> dwCorrPublicKeyLen];
					CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteCorrPublicKey)

					hResult =	(*o_ppVSC) -> VSM_GetUserKeyHandle
								(
									i_pCSP -> pszNameOfContainer,
									pclassKey -> dwAlgID,
									&(pclassKey -> dwKeyLenBits),
									&(pclassKey -> dwExportable),
									pclassKey -> pbyteCorrPublicKey,
									&(pclassKey -> dwCorrPublicKeyLen)
								);
					if ( VS_SUCCESS == hResult )
					{
						i_pCSP -> dwCorrSignPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
						i_pCSP -> pbyteCorrSignPublicKey =	new BYTE [i_pCSP -> dwCorrSignPublicKeyLen];
						CHECK_ALLOCATED_MEMORY (i_pCSP -> pbyteCorrSignPublicKey)

						memcpy
						(
							(void*) i_pCSP -> pbyteCorrSignPublicKey,
							(const void*) pclassKey -> pbyteCorrPublicKey,
							i_pCSP -> dwCorrSignPublicKeyLen
						);
					}

						//	create a new instance of the key class
		//			pclassKey1 =	new (CSP_KeyParam);
		//			CHECK_ALLOCATED_MEMORY (pclassKey1)

					pclassKey -> dwAlgID =	VS_RSA_KEYX;

					hResult =	(*o_ppVSC) -> VSM_GetUserKeyHandle
								(
									i_pCSP -> pszNameOfContainer,
									pclassKey -> dwAlgID,
									&(pclassKey -> dwKeyLenBits),
									&(pclassKey -> dwExportable),
									NULL,
									&(pclassKey -> dwCorrPublicKeyLen)
								);
					VSCSP_CHECK_HRESULT_AND_BREAK

					pclassKey -> pbyteCorrPublicKey =	new BYTE [pclassKey -> dwCorrPublicKeyLen];
					CHECK_ALLOCATED_MEMORY (pclassKey -> pbyteCorrPublicKey)

					hResult =	(*o_ppVSC) -> VSM_GetUserKeyHandle
								(
									i_pCSP -> pszNameOfContainer,
									pclassKey -> dwAlgID,
									&(pclassKey -> dwKeyLenBits),
									&(pclassKey -> dwExportable),
									pclassKey -> pbyteCorrPublicKey,
									&(pclassKey -> dwCorrPublicKeyLen)
								);
					if ( VS_SUCCESS == hResult )
					{
						i_pCSP -> dwCorrXchgPublicKeyLen =	pclassKey -> dwCorrPublicKeyLen;
						i_pCSP -> pbyteCorrXchgPublicKey =	new BYTE [i_pCSP -> dwCorrXchgPublicKeyLen];
						CHECK_ALLOCATED_MEMORY (i_pCSP -> pbyteCorrXchgPublicKey)

						memcpy
						(
							(void*) i_pCSP -> pbyteCorrXchgPublicKey,
							(const void*) pclassKey -> pbyteCorrPublicKey,
							i_pCSP -> dwCorrXchgPublicKeyLen
						);
					}
				}	//	end		if ( (NULL == i_pCSP -> pbyteCorrSignPublicKey) && (NULL == i_pCSP -> pbyteCorrXchgPublicKey) )
			}
			else
			{
				i_pCSP -> dwCorrSignPublicKeyLen =	0;
				i_pCSP -> pbyteCorrSignPublicKey =	NULL;

				i_pCSP -> dwCorrXchgPublicKeyLen =	0;
				i_pCSP -> pbyteCorrXchgPublicKey =	NULL;
			}
		}

		hResult =	VS_SUCCESS;
		break;
	}

	return	hResult;
}
