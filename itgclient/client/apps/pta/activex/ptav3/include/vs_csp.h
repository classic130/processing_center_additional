#ifndef	__VS_CSP_H__
#define	__VS_CSP_H__

#include "..\..\BSafeLite\include\integrate.h"

#define		VSCSP_SWITCH_ALGOS	switch (Algid)\
	{\
		case	CALG_RC2:\
				dwAlgID =	VS_RC2;\
				break;\
		case	CALG_RC4:\
				dwAlgID =	VS_RC4;\
				break;\
		case	CALG_MD2:\
				dwAlgID =	VS_MD2;\
				break;\
		case	CALG_MD5:\
				dwAlgID =	VS_MD5;\
				break;\
		case	CALG_SHA1:\
				dwAlgID =	VS_SHA_1;\
				break;\
		case	AT_KEYEXCHANGE:\
				dwAlgID =	VS_RSA_KEYX;\
				break;\
		case	AT_SIGNATURE:\
				dwAlgID =	VS_RSA_SIGN;\
				break;\
		case	CALG_3DES:\
				dwAlgID =	VS_3DES;\
				break;\
		case	CALG_SSL3_SHAMD5:\
				dwAlgID =	VS_SSL3_SHAMD5;\
				break;\
		default:\
				dwAlgID =	999;\
	}

#define		VSCSP_SWITCH_REV_ALGOS(dwAlgID)	switch (dwAlgID)\
	{\
		case	VS_RC2:\
				Algid =	CALG_RC2;\
				break;\
		case	VS_RC4:\
				Algid =	CALG_RC4;\
				break;\
		case	VS_MD2:\
				Algid =	CALG_MD2;\
				break;\
		case	VS_MD5:\
				Algid =	CALG_MD5;\
				break;\
		case	VS_SHA_1:\
				Algid =	CALG_SHA1;\
				break;\
		case	VS_RSA_KEYX:\
				Algid =	AT_KEYEXCHANGE;\
				break;\
		case	VS_RSA_SIGN:\
				Algid =	AT_SIGNATURE;\
				break;\
		case	VS_3DES:\
				Algid =	CALG_3DES;\
				break;\
		default:\
				Algid =	999;\
	}

void InitCSPGlobalVars ();

/*
 -	CPAcquireContext
 -
 *	Purpose:
 *               The CPAcquireContext function is used to acquire a context
 *               handle to a cryptograghic service provider (CSP).
 *
 *
 *	Parameters:
 *               OUT phProv        -  Handle to a CSP
 *               OUT pszIdentity   -  Pointer to a string which is the
 *                                    identity of the logged on user
 *               IN  dwFlags       -  Flags values
 *               IN  pVTable       -  Pointer to table of function pointers
 *
 *	Returns:
 */
BOOL WINAPI CPAcquireContext
(
	OUT HCRYPTPROV *phProv,
	OUT CHAR *pszIdentity,
	IN DWORD dwFlags,
	IN PVTableProvStruc pVTable
);


/*
 -      CPReleaseContext
 -
 *      Purpose:
 *               The CPReleaseContext function is used to release a
 *               context created by CrytAcquireContext.
 *
 *     Parameters:
 *               IN  phProv        -  Handle to a CSP
 *               IN  dwFlags       -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPReleaseContext
(
	IN HCRYPTPROV hProv,
    IN DWORD dwFlags
);



/*
 -	CPGenKey
 -
 *	Purpose:
 *                Generate cryptographic keys
 *
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      Algid   -  Algorithm identifier
 *               IN      dwFlags -  Flags values
 *               OUT     phKey   -  Handle to a generated key
 *
 *	Returns:
 */
BOOL WINAPI CPGenKey
(
	IN HCRYPTPROV hProv,
    IN int Algid,
    IN DWORD dwFlags,
    OUT HCRYPTKEY * phKey
);


/*
 -	CPDeriveKey
 -
 *	Purpose:
 *                Derive cryptographic keys from base data
 *
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      Algid      -  Algorithm identifier
 *               IN      hHash      -  Handle to hash 
 *               IN      dwFlags    -  Flags values
 *               OUT     phKey      -  Handle to a generated key
 *
 *	Returns:
 */
BOOL WINAPI CPDeriveKey
(
	IN HCRYPTPROV hProv,
    IN int Algid,
    IN HCRYPTHASH hHash,
    IN DWORD dwFlags,
    OUT HCRYPTKEY * phKey
);



/*
 -	CPDestroyKey
 -
 *	Purpose:
 *                Destroys the cryptographic key that is being referenced
 *                with the hKey parameter
 *
 *
 *	Parameters:
 *               IN      hProv  -  Handle to a CSP
 *               IN      hKey   -  Handle to a key
 *
 *	Returns:
 */
BOOL WINAPI CPDestroyKey
(
	IN HCRYPTPROV hProv,
	IN HCRYPTKEY hKey
);



/*
 -	CPSetKeyParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a key
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      hKey    -  Handle to a key
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetKeyParam
(
	IN HCRYPTPROV hProv,
    IN HCRYPTKEY hKey,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD dwFlags
);



/*
 -	CPGetKeyParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a key
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      hKey       -  Handle to a key
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPGetKeyParam
(
	IN HCRYPTPROV hProv,
    IN HCRYPTKEY hKey,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD *pdwDataLen,
    IN DWORD dwFlags
);



/*
 -	CPSetProvParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a provider
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetProvParam
(
	IN HCRYPTPROV hProv,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD dwFlags
);



/*
 -	CPGetProvParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a provider
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPGetProvParam
(
	IN HCRYPTPROV hProv,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD *pdwDataLen,
    IN DWORD dwFlags
);




/*
 -	CPSetHashParam
 -
 *	Purpose:
 *                Allows applications to customize various aspects of the
 *                operations of a hash
 *
 *	Parameters:
 *               IN      hProv   -  Handle to a CSP
 *               IN      hHash   -  Handle to a hash
 *               IN      dwParam -  Parameter number
 *               IN      pbData  -  Pointer to data
 *               IN      dwFlags -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPSetHashParam
(
	IN HCRYPTPROV hProv,
	IN HCRYPTHASH hHash,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD dwFlags
);



/*
 -	CPGetHashParam
 -
 *	Purpose:
 *                Allows applications to get various aspects of the
 *                operations of a hash
 *
 *	Parameters:
 *               IN      hProv      -  Handle to a CSP
 *               IN      hHash      -  Handle to a hash
 *               IN      dwParam    -  Parameter number
 *               IN      pbData     -  Pointer to data
 *               IN      pdwDataLen -  Length of parameter data
 *               IN      dwFlags    -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPGetHashParam
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash,
    IN DWORD dwParam,
    IN BYTE *pbData,
    IN DWORD *pdwDataLen,
    IN DWORD dwFlags
);



/*
 -	CPExportKey
 -
 *	Purpose:
 *                Export cryptographic keys out of a CSP in a secure manner
 *
 *
 *	Parameters:
 *               IN  hProv      - Handle to the CSP user
 *               IN  hKey       - Handle to the key to export
 *               IN  hPubKey    - Handle to the exchange public key value of
 *                                the destination user
 *               IN  dwBlobType - Type of key blob to be exported
 *               IN  dwFlags -    Flags values
 *               OUT pbData -     Key blob data
 *               OUT pdwDataLen - Length of key blob in bytes
 *
 *	Returns:
 */
BOOL WINAPI CPExportKey
(
	IN HCRYPTPROV hProv,
    IN HCRYPTKEY hKey,
    IN HCRYPTKEY hPubKey,
    IN DWORD dwBlobType,
    IN DWORD dwFlags,
    OUT BYTE *pbData,
    OUT DWORD *pdwDataLen
);



/*
 -	CPImportKey
 -
 *	Purpose:
 *                Import cryptographic keys
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the CSP user
 *               IN  pbData    -  Key blob data
 *               IN  dwDataLen -  Length of the key blob data
 *               IN  hPubKey   -  Handle to the exchange public key value of
 *                                the destination user
 *               IN  dwFlags   -  Flags values
 *               OUT phKey     -  Pointer to the handle to the key which was
 *                                Imported
 *
 *	Returns:
 */
BOOL WINAPI CPImportKey
(
	IN HCRYPTPROV hProv,
    IN CONST BYTE *pbData,
    IN DWORD dwDataLen,
    IN HCRYPTKEY hPubKey,
    IN DWORD dwFlags,
    OUT HCRYPTKEY *phKey
);



/*
 -	CPEncrypt
 -
 *	Purpose:
 *                Encrypt data
 *
 *
 *	Parameters:
 *               IN  hProv         -  Handle to the CSP user
 *               IN  hKey          -  Handle to the key
 *               IN  hHash         -  Optional handle to a hash
 *               IN  Final         -  Boolean indicating if this is the final
 *                                    block of plaintext
 *               IN  dwFlags       -  Flags values
 *               IN OUT pbData     -  Data to be encrypted
 *               IN OUT pdwDataLen -  Pointer to the length of the data to be
 *                                    encrypted
 *               IN dwBufLen       -  Size of Data buffer
 *
 *	Returns:
 */
BOOL WINAPI CPEncrypt
(
	IN HCRYPTPROV hProv,
    IN HCRYPTKEY hKey,
	IN HCRYPTHASH hHash,
	IN BOOL Final,
    IN DWORD dwFlags,
    IN OUT BYTE *pbData,
    IN OUT DWORD *pdwDataLen,
    IN DWORD dwBufLen
);



/*
 -	CPDecrypt
 -
 *	Purpose:
 *                Decrypt data
 *
 *
 *	Parameters:
 *               IN  hProv         -  Handle to the CSP user
 *               IN  hKey          -  Handle to the key
 *               IN  hHash         -  Optional handle to a hash
 *               IN  Final         -  Boolean indicating if this is the final
 *                                    block of ciphertext
 *               IN  dwFlags       -  Flags values
 *               IN OUT pbData     -  Data to be decrypted
 *               IN OUT pdwDataLen -  Pointer to the length of the data to be
 *                                    decrypted
 *
 *	Returns:
 */
BOOL WINAPI CPDecrypt
(
	IN HCRYPTPROV hProv,
    IN HCRYPTKEY hKey,
    IN HCRYPTHASH hHash,
    IN BOOL Final,
    IN DWORD dwFlags,
    IN OUT BYTE *pbData,
    IN OUT DWORD *pdwDataLen
);



/*
 -	CPCreateHash
 -
 *	Purpose:
 *                initate the hashing of a stream of data
 *
 *
 *	Parameters:
 *               IN  hUID    -  Handle to the user identifcation
 *               IN  Algid   -  Algorithm identifier of the hash algorithm
 *                              to be used
 *               IN  hKey    -  Optional key for MAC algorithms
 *               IN  dwFlags -  Flags values
 *               OUT pHash   -  Handle to hash object
 *
 *	Returns:
 */
BOOL WINAPI CPCreateHash
(
	IN HCRYPTPROV hProv,
    IN int Algid,
    IN HCRYPTKEY hKey,
    IN DWORD dwFlags,
    OUT HCRYPTHASH *phHash
);



/*
 -	CPHashData
 -
 *	Purpose:
 *                Compute the cryptograghic hash on a stream of data
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *               IN  pbData    -  Pointer to data to be hashed
 *               IN  dwDataLen -  Length of the data to be hashed
 *               IN  dwFlags   -  Flags values
 *               IN  pdwMaxLen -  Maximum length of the data stream the CSP
 *                                module may handle
 *
 *	Returns:
 */
BOOL WINAPI CPHashData
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash,
    IN CONST BYTE *pbData,
    IN DWORD dwDataLen,
    IN DWORD dwFlags
);



/*
 -	CPHashSessionKey
 -
 *	Purpose:
 *                Compute the cryptograghic hash on a key object.
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *               IN  hKey      -  Handle to a key object
 *               IN  dwFlags   -  Flags values
 *
 *	Returns:
 *               CRYPT_FAILED
 *               CRYPT_SUCCEED
 */
BOOL WINAPI CPHashSessionKey
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash,
    IN HCRYPTKEY hKey,
    IN DWORD dwFlags
);


/*
 -	CPDestoryHash
 -
 *	Purpose:
 *                Destory the hash object
 *
 *
 *	Parameters:
 *               IN  hProv     -  Handle to the user identifcation
 *               IN  hHash     -  Handle to hash object
 *
 *	Returns:
 */
BOOL WINAPI CPDestroyHash
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash
);



/*
 -	CPSignHash
 -
 *	Purpose:
 *                Create a digital signature from a hash
 *
 *
 *	Parameters:
 *               IN  hProv        -  Handle to the user identifcation
 *               IN  hHash        -  Handle to hash object
 *               IN  Algid        -  Algorithm identifier of the signature
 *                                   algorithm to be used
 *               IN  sDescription -  Description of data to be signed
 *               IN  dwFlags      -  Flags values
 *               OUT pbSignture   -  Pointer to signature data
 *               OUT dwHashLen    -  Pointer to the len of the signature data
 *
 *	Returns:
 */
BOOL WINAPI CPSignHash
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash,
    IN DWORD dwKeySpec,
    IN LPCWSTR sDescription,
    IN DWORD dwFlags,
    OUT BYTE *pbSignature,
    OUT DWORD *pdwSigLen
);


/*
 -	CPVerifySignature
 -
 *	Purpose:
 *                Used to verify a signature against a hash object
 *
 *
 *	Parameters:
 *               IN  hProv        -  Handle to the user identifcation
 *               IN  hHash        -  Handle to hash object
 *               IN  pbSignture   -  Pointer to signature data
 *               IN  dwSigLen     -  Length of the signature data
 *               IN  hPubKey      -  Handle to the public key for verifying
 *                                   the signature
 *               IN  Algid        -  Algorithm identifier of the signature
 *                                   algorithm to be used
 *               IN  sDescription -  Description of data to be signed
 *               IN  dwFlags      -  Flags values
 *
 *	Returns:
 */
BOOL WINAPI CPVerifySignature
(
	IN HCRYPTPROV hProv,
    IN HCRYPTHASH hHash,
    IN CONST BYTE *pbSignature,
    IN DWORD dwSigLen,
    IN HCRYPTKEY hPubKey,
    IN LPCWSTR sDescription,
    IN DWORD dwFlags
);




/*
 -	CPGenRandom
 -
 *	Purpose:
 *                Used to fill a buffer with random bytes
 *
 *
 *	Parameters:
 *               IN  hProv      -  Handle to the user identifcation
 *               OUT pbBuffer   -  Pointer to the buffer where the random
 *                                 bytes are to be placed
 *               IN  dwLen      -  Number of bytes of random data requested
 *
 *	Returns:
 */
BOOL WINAPI CPGenRandom
(
	IN HCRYPTPROV hProv,
    IN DWORD dwLen,
    IN OUT BYTE *pbBuffer
);


/*
 -	CPGetUserKey
 -
 *	Purpose:
 *                Gets a handle to a permanent user key
 *
 *
 *	Parameters:
 *               IN  hProv      -  Handle to the user identifcation
 *               IN  dwKeySpec  -  Specification of the key to retrieve
 *               OUT phUserKey  -  Pointer to key handle of retrieved key
 *
 *	Returns:
 */
BOOL WINAPI CPGetUserKey
(
	IN HCRYPTPROV hProv,
    IN DWORD dwKeySpec,
    OUT HCRYPTKEY *phUserKey
);


#endif