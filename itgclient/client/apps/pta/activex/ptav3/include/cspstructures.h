#ifndef		__VS_CSP_STRUCTURES__
#define		__VS_CSP_STRUCTURES__

#include "stdafx.h"
#include <initguid.h>

//#include	"..\..\ProtectedStorage\ProtectedStorage.h"

#include "mangleduiprefs.h"
#include "mangledprofmgmt.h"
#include "mangledcertprefs.h"
#include "mangledsrchcrit.h"
#include "mangledseldigid.h"
#include "mangledroamprefs.h"
#include	"ptav3.h"
#include	"vspta.h"
#include "bsafelite.h"
#include "integrate.h"
#include "VSCSP_Macros.h"
#include "cspincludes.h"
//#include "tss_all.h"
#include "vs_tss.h"

//#include	"globals.h"



class	CSP_HashParam
{
	public:
//	void*					phHash;
		int						nHashAlgID;
		void*					pvoidContext;

		BYTE*					pbDataHash;
		DWORD					dwDataHashLength;

		DWORD					dwHashObjectStatus;

		DWORD					dwIsEmpty;

		CSP_HashParam*			pNext;
		CSP_HashParam*			pBack;

		VS_TSS_Hash*			pVSTSSHash;

		CSP_HashParam ()
		{
//			phHash		=	NULL;
			nHashAlgID			=	9999;
			pvoidContext		=	NULL;

			pbDataHash			=	NULL;
			dwDataHashLength	=	0;

			dwHashObjectStatus	=	HASH_OBJECT_NOT_CREATED;

			dwIsEmpty			=	1;

			pNext				=	NULL;
			pBack				=	NULL;
		}

		~CSP_HashParam()
		{
			VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbDataHash, dwDataHashLength)

			pvoidContext		=	NULL;
			nHashAlgID			=	9999;

			dwHashObjectStatus	=	HASH_OBJECT_NOT_CREATED;

			pNext				=	NULL;
			pBack				=	NULL;
		}
};

//		struct	_CSP_HashParam*	pNextHandle;
/*
	public:
		CSP_HashParam ()
		{
			phHash		=	NULL;
			nHashAlgID	=	9999;
			pNext		=	NULL;
			pBack		=	NULL;
		}

		~CSP_HashParam() {}

		void	getHashAlgID ( int*	o_pnHashAlgID )
		{
			*o_pnHashAlgID =	nHashAlgID;
			return;
		}

		void	setHashAlgID ( const int	i_cnHashAlgID )
		{
			nHashAlgID =	i_cnHashAlgID;
			return;
		}

		void	getHashObjPtr	( void**	o_ppvoidHash )
		{
			*o_ppvoidHash =	phHash;
			return;
		}

		void	getNextPtr ( CSP_HashParam**	o_ppNext )
		{
			*o_ppNext =	pNext;
			return;
		}

		void	setBackPtr ( const CSP_HashParam*	i_cpNode )
		{
			pBack =	(CSP_HashParam*) i_cpNode;
			return;
		}

		void	AddNode ( const CSP_HashParam*	i_cpNode )
		{
			pNext =	(CSP_HashParam*) i_cpNode;
			i_cpNode -> setBackPtr (this);
			return;
		}
};
*/

class	CSP_KeyParam
{
	public:
		ITEM					itemKey;
		BYTE*					pbyteCorrPublicKey;
		DWORD					dwCorrPublicKeyLen;
//		A_RSA_KEY				RSA_PublicKey;
//		A_RSA_KEY				RSA_PrivateKey;

		DWORD					dwExportable;
		DWORD					dwAlgID;
		DWORD					dwBlockLen;
		DWORD					dwKeyLenBits;
		DWORD					dwEffectiveKeyLen;
		BYTE*					pbyteSalt;
		DWORD					dwSaltLength;
		BYTE*					pbyteInitVector;
		DWORD					dwInitVectorLength;
		DWORD					dwPadding;
		DWORD					dwPermissions;
		DWORD					dwCypherModes;
		DWORD					dwModeBits;

		BOOL					boolEncryptionStarted;
		BOOL					boolEncryptionEnded;
		BOOL					boolDecryptionStarted;
		BOOL					boolDecryptionEnded;
		BOOL					boolHashStarted;
		BOOL					boolHashEnded;

		void*					pvoidRC4_Context;
		void*					pvoidRC2_Context;
		void*					pvoidRSA_Context;
		void*					pvoid3DES_Context;  // added new RSA context for 3DES encryption/decryption

		CSP_KeyParam*			pNext;
		CSP_KeyParam*			pBack;

		//	new variables added for TPM suppport
		VS_TSS_Key*				pVSTSSKey;
		VS_TSS_Data*			pVSTSSData;

		CSP_KeyParam ()
		{
//			pbyteKey				=	NULL;
			pNext					=	NULL;
			pBack					=	NULL;

			dwExportable			=	999;
			dwAlgID					=	999;
			dwBlockLen				=	999;
			dwKeyLenBits			=	999;
			dwEffectiveKeyLen		=	999;
			pbyteSalt				=	NULL;
			dwSaltLength			=	999;
			pbyteInitVector			=	NULL;
			dwInitVectorLength		=	999;
			dwPadding				=	999;
			dwPermissions			=	999;
			dwCypherModes			=	999;
			dwModeBits				=	999;

			boolEncryptionStarted	=	FALSE;
			boolEncryptionEnded		=	FALSE;
			boolDecryptionStarted	=	FALSE;
			boolDecryptionEnded		=	FALSE;
			boolHashStarted			=	FALSE;
			boolHashEnded			=	FALSE;

			itemKey.data			=	NULL;
			itemKey.len				=	0;
			
			pbyteCorrPublicKey		=	NULL;
			dwCorrPublicKeyLen		=	0;

//			pbyteCorrSignPublicKey	=	NULL;
//			dwCorrSignPublicKeyLen	=	0;
		}

		~CSP_KeyParam () 
		{
//			pbyteKey				=	NULL;
			pNext					=	NULL;
			pBack					=	NULL;

			dwExportable			=	999;
			dwAlgID					=	999;
			dwBlockLen				=	999;
			dwKeyLenBits			=	999;
			dwEffectiveKeyLen		=	999;
			VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteSalt, dwSaltLength)
//			dwSaltLength			=	999;
			VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteInitVector, dwInitVectorLength)
//			dwInitVectorLength		=	999;
			dwPadding				=	999;
			dwPermissions			=	999;
			dwCypherModes			=	999;
			dwModeBits				=	999;

			boolEncryptionStarted	=	FALSE;
			boolEncryptionEnded		=	FALSE;
			boolDecryptionStarted	=	FALSE;
			boolDecryptionEnded		=	FALSE;
			boolHashStarted			=	FALSE;
			boolHashEnded			=	FALSE;

			VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE(itemKey.data, itemKey.len)
//			itemKey.len				=	0;
			
			VSCSP_CHECK_FOR_NULL_ERASE_AND_DELETE (pbyteCorrPublicKey, dwCorrPublicKeyLen)
//			dwCorrPublicKeyLen		=	0;

//			pbyteCorrSignPublicKey	=	NULL;
//			dwCorrSignPublicKeyLen	=	0;
		}

/*		void	getKeyObjPtr ( void**	o_ppvoidKey )
		{
			*o_ppvoidKey =	phKey;
			return;
		}

		void	getKeyParam	( DWORD*	o_pdwKeyParam )
		{
			*o_pdwKeyParam =	dwKeyParam;
			return;
		}

		void	setKeyParam	( const DWORD	i_cdwKeyParam )
		{
			dwKeyParam =	i_cdwKeyParam;
			return;
		}

		void	getNextPtr ( CSP_KeyParam**	o_ppNext )
		{
			*o_ppNext =	pNext;
			return;
		}*/
};

//	this structure will store all the state information about the CSP
//
//	the next pointer will enable to maintain a linked list of these structures.
//	this way a single application can have multiple handles for the CSP
typedef struct	_CSP_State
{
	DWORD					dwCSPName;						//	The name of the CSP. We are housing
															//	2 CSPs in the same dll. During the
															//	CPAcquireContext call the OS will give
															//	us the name of the CSP.

	DWORD					dwSizeofStruct;
	CHAR*					pszNameOfContainer;
//	CComObject<CVSPTA>*		pCVSPTAInst;					//	the PTA instance. the CSP will always communicate
															//	with the PS thru the PTA

	IVSPTA*					pIPTA;
	IVSProfMgmt*			pIProfMgmt;


	CSP_HashParam*			pHashParam;
	CSP_KeyParam*			pKeyParam;

	VTableProvStruc*		pVTable;

	BYTE*					pbyteCorrSignPublicKey;
	DWORD					dwCorrSignPublicKeyLen;

	BYTE*					pbyteCorrXchgPublicKey;
	DWORD					dwCorrXchgPublicKeyLen;
	BOOL					bPvtKeyAccess;					// Set to FALSE when you
															// use CRYPT_VERIFY_CONTEXT
//	CSP_State*				pNext;
//	CSP_State*				pBack;

//	VS_TPM_CSP_Container	structTPMContainer;
//	UUID					uuidUserRootKey;
//	_bstr_t					tbstrUserRootPassword;

	VS_TSS_Context*			pVSTSSContext;

}	CSP_State;


typedef struct	_CSP_AlgoInfo
{
	PROV_ENUMALGS		pEnumAlgs [8];
	int					nIndex;
}	CSP_AlgoInfo;

typedef struct	_CSP_ExAlgoInfo
{
	PROV_ENUMALGS_EX	pEnumAlgsEx [8];
	int					nIndex;
}	CSP_ExAlgoInfo;

typedef struct	_TPM_CSP_AlgoInfo
{
	PROV_ENUMALGS		pEnumAlgs [5];
	int					nIndex;
}	TPM_CSP_AlgoInfo;

typedef struct	_TPM_CSP_ExAlgoInfo
{
	PROV_ENUMALGS_EX	pEnumAlgsEx [5];
	int					nIndex;
}	TPM_CSP_ExAlgoInfo;


/*
typedef struct	_CSP_PubKeyHash
{
	DWORD				dwPubKeyAlgo;
	DWORD				dwExportable;
	BYTE				pbytePubKeyHash [20];
}	CSP_PubKeyHash;

typedef struct	_CSP_Key_Container
{
	CSP_PubKeyHash		structXchg;
	CSP_PubKeyHash		structSign;
}	CSP_Key_Container;
*/

#endif