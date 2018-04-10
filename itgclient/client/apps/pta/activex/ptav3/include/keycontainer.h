#ifndef		__VS_PTA_KEY_CONTAINER_H__
#define		__VS_PTA_KEY_CONTAINER_H__

#define		VS_CSP_KEY_EXISTS						1234	//	same flag used for both CSPs
#define		VS_CSP_KEY_EXPORTABLE					2345	//	same flag used for both CSPs

typedef struct	_CSP_PubKeyHash
{
	DWORD				dwExists;
	DWORD				dwExportable;
	BYTE				pbytePubKeyHash [20];
}	CSP_PubKeyHash;

typedef struct	_CSP_Key_Container
{
	CSP_PubKeyHash		structXchg;
	CSP_PubKeyHash		structSign;
}	CSP_Key_Container;

typedef	struct	_RSA_Context
{
	DWORD				dwSizeOfStruct;
	DWORD				dwRemainder;
	void*				pContext;
}	RSA_Context;

/*
typedef	struct	_VS_TPM_CSP_CONTAINER_KEY_
{
	DWORD				dwExchangeKeyExists;
	UUID				uuidExchangeKeyUUID;
	BYTE*				pbyteExchangePublicKey;
	DWORD				dwExchangeKeyExportable;
	UUID				uuidExchangeWrappingKeyUUID;
	DWORD				dwSigningKeyExists;
	UUID				uuidSigningKeyUUID;
	BYTE*				pbyteSigningPublicKey;
	DWORD				dwSigningKeyExportable;
	UUID				uuidSigningWrappingKeyUUID;
}	VS_TPM_CSP_Container;
*/

typedef	struct	_VS_TPM_CSP_CONTAINER_KEY_
{
	DWORD				dwKeyExists;
	DWORD				dwKeyExportable;
	DWORD				dwKeyLength;
	UUID				uuidKeyUUID;
//	UUID				uuidWrappingKeyUUID;
}	VS_TPM_CSP_Key_Container;

typedef	struct	_VS_TPM_CSP_CONTAINER_
{
	VS_TPM_CSP_Key_Container	structExchangeKey;
	VS_TPM_CSP_Key_Container	structSignatureKey;
	BYTE*						pbyteExchangePublicKey;
	DWORD						dwExchangePubKeyLen;
	BYTE*						pbyteSigningPublicKey;
	DWORD						dwSignaturePubKeyLen;
}	VS_TPM_CSP_Container;



#endif