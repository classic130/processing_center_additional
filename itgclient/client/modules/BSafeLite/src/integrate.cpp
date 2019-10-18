
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/

#ifdef WIN32
#define _WIN32_WINNT 0x0400
#include "windows.h"
#include "winbase.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "bsafelite.h"
#include "bsafe.h"
#include "md5rand.h"
#include "integrate.h"
#include "md2.h"
#include "md5.h"
#include "sha.h"
#include "rc4.h"
#include "rc2cbc.h"
#include "desedec.h"

// Wasim : Nov 2001, setting the number of blocks to 1 ensures that a new gpool is initialized everytime 
// GenerateRandomBlock() is called. Setting block size to 2600 ensures enough seed data
#ifdef WIN32
	#define POOL_NO_BLOCKS 1
	#define POOL_BLOCK_SIZE 2600
#else
	#define POOL_NO_BLOCKS 128
	#define POOL_BLOCK_SIZE 60
#endif

#ifdef WIN32
	#include "winperf.h"
	#include "winbase.h"
	#include "iostream.h"

typedef BOOL (WINAPI * LPFNCryptAcquireContext)(HCRYPTPROV *phProv, LPCTSTR pszContainer, LPCTSTR pszProvider,
												DWORD dwProvType,  DWORD dwFlags);
typedef BOOL (WINAPI * LPFNCryptGenRandom)(HCRYPTPROV hProv, DWORD dwLen,  BYTE *pbBuffer);
typedef BOOL (WINAPI * LPFNCryptReleaseContext)(HCRYPTPROV hProv, DWORD dwFlags);

HCRYPTPROV g_hCryptProv = NULL;

#endif

static int gRNGInitialized = 0;
static unsigned char *gPool = NULL;
static unsigned int gPoolSize = 0;
static unsigned int gNextBlock = 0;
static void AddRandomPool();
static void MixRandomPool();

#define A_RSA_KEY_GEN_RANDOM_BLOCK_LEN(modulusBits) \
  (4 * (((RSA_PRIME_BITS (modulusBits)) >> 4) + 1))

int GetPseudoRandomSeedData (unsigned char* outSeedData, unsigned int *outSeedLength, unsigned int maxSeedLength);
BOOL EnableDataCollection(char *szObjName, char *szCounterName);
BOOL DisableDataCollection(char *szObjName, char *szCounterName);
BOOL CollectPerfData(char *szObjName, char *szCounterName, DWORD *pdwData);



/*********************************************************************************************************
 * Function DoRSAKeyGen ()
 * This function can be used generate the RSA key pair.
 *
 * parameters : nKeySize : the desired key strength
 *
 * outputs:     pRSAPrivKey: the RSA private key
 *              pRSAPubKey : the RSA public key
 *               .
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int DoRSAKeyGen(int nKeySize, A_RSA_KEY* pRSAPrivKey,A_RSA_KEY* pRSAPubKey)
{
	unsigned int contextLen;
	unsigned int randomBlockLen;
	unsigned int modulusBits = nKeySize;	//	Anand 1024;
	A_RSA_KEY_GEN_CTX context;
	A_RSA_KEY_GEN_PARAMS	keygenParams;
	unsigned char f4Data[3] = {0x01, 0x00, 0x01 } ;
	unsigned char* randomBlock;
	A_PKCS_RSA_PRIVATE_KEY* pLocalRSAPrivKey;
	randomBlockLen =  A_RSA_KEY_GEN_RANDOM_BLOCK_LEN (modulusBits);
	contextLen = sizeof (A_RSA_KEY_GEN_CTX);

	//Create the context
	keygenParams.modulusBits = nKeySize;	///	Anand	512;
	keygenParams.publicExponent.data = f4Data;
	keygenParams.publicExponent.len = 3;

	ALG_RSAKeyGenInit((A_RSA_KEY_GEN_CTX *)&context, (A_RSA_KEY_GEN_PARAMS *)&keygenParams);

	int nRetVal = 0;
	do
	{
		//Get random block
		randomBlock = (unsigned char*)malloc(sizeof(char)*randomBlockLen );
		GenerateRandomBlock(randomBlock,randomBlockLen);

		//Do key gen
		nRetVal = ALG_RSAKeyGen(&context,&pLocalRSAPrivKey,randomBlock,NULL);	
	}while(nRetVal != 0);

	//Extract public and private keys
	
	pRSAPubKey->modulus.data = (unsigned char*)malloc(sizeof(unsigned char)* pLocalRSAPrivKey->modulus.len);
	memcpy(pRSAPubKey->modulus.data,pLocalRSAPrivKey->modulus.data,(sizeof(unsigned char)*pLocalRSAPrivKey->modulus.len));
	pRSAPubKey->modulus.len = pLocalRSAPrivKey->modulus.len;

	pRSAPubKey->exponent.data = (unsigned char*)malloc(sizeof(unsigned char)* pLocalRSAPrivKey->publicExponent.len);
	memcpy(pRSAPubKey->exponent.data,pLocalRSAPrivKey->publicExponent.data,(sizeof(unsigned char)*pLocalRSAPrivKey->publicExponent.len));
	pRSAPubKey->exponent.len = pLocalRSAPrivKey->publicExponent.len;

	pRSAPrivKey->modulus.data = (unsigned char*)malloc(sizeof(unsigned char)* pLocalRSAPrivKey->modulus.len);
	memcpy(pRSAPrivKey->modulus.data,pLocalRSAPrivKey->modulus.data,(sizeof(unsigned char)*pLocalRSAPrivKey->modulus.len));
	pRSAPrivKey->modulus.len = pLocalRSAPrivKey->modulus.len;

	pRSAPrivKey->exponent.data = (unsigned char*)malloc(sizeof(unsigned char)* pLocalRSAPrivKey->privateExponent.len);
	memcpy(pRSAPrivKey->exponent.data,pLocalRSAPrivKey->privateExponent.data,(sizeof(unsigned char)*pLocalRSAPrivKey->privateExponent.len));
	pRSAPrivKey->exponent.len = pLocalRSAPrivKey->privateExponent.len;

	
	//Destroy the context
	ALG_RSAKeyGenContextDestroy(&context);

	return 0;
}



/*********************************************************************************************************
 * Function RSADataBegin ()
 * This function can be used the initialize the RSA operation (encrypt/decrypt depending on the key)
 * Generally the call is followed by calls (possibly multiple to RSADataUpdate and a call to 
 * RSADataEnd
 *
 * parameters : RSAKey : RSA key object
 *
 * output:      o_ppvoidContext : the RSA operation context, it is allocated within this function and needs to 
 *                                be passed in future calls to RSADataUpdate and RSADataEnd (where it is freed).
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int RSADataBegin ( A_RSA_KEY* RSAKey, void** o_ppvoidContext )
{
	int status = 0;

	do 
	{	
		*o_ppvoidContext = T_malloc(sizeof(A_RSA_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		status = ALG_RSAInit ((A_RSA_CTX*)*o_ppvoidContext, RSAKey);
	}while(0);

	return status;
}


/*********************************************************************************************************
 * Function RSADataUpdate ()
 * This function is called to encrypt/decrypt data. For large data, this function
 * can be called multiple times. 
 *
 * parameters : voidContext : the RSA operation context, it is allocated in the RSADataBegin function
 *              plainText : the data that is to be operated upon
 *              plainTextSize: the size of plainText
 * output:      encText : the data after RSA operation
 *              plainTextSize: the size of encText
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int RSADataUpdate ( void* pvoidContext, unsigned char* plainText, unsigned int plainTextSize, unsigned char* encText, unsigned int* encTextSize)
{
	int status = 0;

	status = ALG_RSAUpdate((A_RSA_CTX*)pvoidContext,encText,encTextSize,*encTextSize, plainText, plainTextSize,NULL);

	return	status;
}


/*********************************************************************************************************
 * Function RSADataEnd ()
 * This function is called after (multiple) call(s) to RSADataUpdate(). 
 *
 * parameters : pvoidContext : the RSA operation context, it is allocated in RSADataBegin()
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/

int RSADataEnd ( void* pvoidContext )
{
	int status;
	
	status = ALG_RSAFinal((A_RSA_CTX*)pvoidContext );

	//Destroy the context
	ALG_RSAContextDestroy ((A_RSA_CTX*)pvoidContext);

	if (pvoidContext != NULL_PTR) {
		T_free(pvoidContext);
		pvoidContext = NULL;
	}

	return status;
}


/*********************************************************************************************************
 * Function HashBegin ()
 * This function can be used the initialize the hashing operation. 
 * Generally the call is followed by calls (possibly multiple to HashData and a call to HashEnd
 *
 * parameters : nAlgId can be HASH_SHA1, HASH_MD2, HASH_MD5
 *
 * outputs:     o_ppvoidContext : the hash context, it is allocated within this function and needs to 
 *                                be passed in future calls to HashData and HashEnd (where it is freed).
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int	HashBegin  ( int nAlgId, void** o_ppvoidContext)
{
	int status=0;

	switch (nAlgId)
	{
	case HASH_SHA1:
		*o_ppvoidContext = T_malloc(sizeof(A_SHA_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		A_SHAInit ((A_SHA_CTX*)*o_ppvoidContext);
		break;
	
	case HASH_MD2:
		*o_ppvoidContext = T_malloc(sizeof(A_MD2_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		A_MD2Init ((A_MD2_CTX*)*o_ppvoidContext);
		break;

	case HASH_MD5:
		*o_ppvoidContext = T_malloc(sizeof(A_MD5_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		A_MD5Init ((A_MD5_CTX*)*o_ppvoidContext);
		break;

	default: 
		status = -1;
		break;
	}
	return	status;
}



/*********************************************************************************************************
 * Function HashData ()
 * This function is called to update the data that is to be hashed. For large data, this function
 * can be called multiple times. The final hash value is returned in HashEnd()
 *
 * parameters : nAlgId can be HASH_SHA1, HASH_MD2, HASH_MD5
 *              voidContext : the hash context, it is allocated in the HashBegin function
 *              inData : the data that is to be hashed
 *              inDataSize: the size of inData
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/

int HashData(int nAlgId, void* pvoidContext, unsigned char* inData, unsigned int inDataSize) //, unsigned char* outHashVal)
{	
	int status = 0;

	switch (nAlgId)
	{
	case HASH_SHA1:
		A_SHAUpdate ((A_SHA_CTX*)pvoidContext, inData, inDataSize);
		break;
	
	case HASH_MD2:
		A_MD2Update ((A_MD2_CTX*)pvoidContext, inData, inDataSize);
		break;

	case HASH_MD5:
		A_MD5Update ((A_MD5_CTX*)pvoidContext, inData, inDataSize);
		break;

	default: 
		status = -1;
		break;

	}

	return status;
}


/*********************************************************************************************************
 * Function HashEnd ()
 * This function is called after (multiple) call(s) to HashUpdate(). The hash value is returned 
 * in this call and the hash context is freed.
 *
 * parameters : nAlgId can be HASH_SHA1, HASH_MD2, HASH_MD5
 *              pvoidContext : the hash context, it is allocated in HashBegin()
 * 
 * outputs:     outHashVal: buffer for the hash value, should be equal to at least 16/20 bytes 
 *                          depending on the algorithm
 *              nBufferSize: size of outHashVal
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/

int HashEnd (int nAlgId, void* pvoidContext, unsigned char* outHashVal, int nBufferSize)
{	
	int status = 0;
	switch (nAlgId)
	{
	case HASH_SHA1:
		if (nBufferSize < A_SHA_DIGEST_LEN)
		{
			status = -1;
			break;
		}
		A_SHAFinal ((A_SHA_CTX*)pvoidContext, outHashVal);
		break;
	
	case HASH_MD2:
		if (nBufferSize < A_MD2_DIGEST_LEN)
		{
			status = -1; 
			break;
		}
		A_MD2Final ((A_MD2_CTX*)pvoidContext, outHashVal);
		break;

	case HASH_MD5:
		if (nBufferSize < A_MD5_DIGEST_LEN)
		{
			status = -1; 
			break;
		}
		A_MD5Final ((A_MD5_CTX*)pvoidContext, outHashVal);
		break;

	default: 
		status = -1;
		break;
	}

	if (pvoidContext != NULL) {
		T_free (pvoidContext);
		pvoidContext = NULL;
	}

	return	status;
}


/*********************************************************************************************************
 * Function SymEncryptDataBegin ()
 * This function can be used the initialize a symmetric encryption operation
 * Generally the call is followed by calls (possibly multiple to SymEncryptDataUpdate and a call 
 * to SymEncryptDataEnd
 *
 * parameters : nAlgId: can be SYM_RC2_CBC or RC4
 *                      if nAlgId is RC4 the parameter iv should be NULL.
 *              iv: the initialization vector, only valid if nAlgId is SYM_RC2_CBC
 *                  should be at least 8 bytes in length. The same iv needs to be passed
 *                  at the time of decryption
 *				nEffectiveKeyLen: length of the symmetric key
 *              toPad : 1 - BSafeLite will add padding
 *                      0 - BsafeLite ignores any padding, the data to encrypt needs to be multiple of 8
 *
 * outputs:     o_ppvoidContext : the encryption context, it is allocated within this function and needs to 
 *                                be passed in future calls to SymEncryptDataUpdate and a call 
 *                                to SymEncryptDataEndData (where it is freed).
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymEncryptDataBegin ( int i_nAlgId, ITEM* i_pRCKey, int i_nEffectiveKeyLen, void** o_ppvoidContext, unsigned char *iv, unsigned int toPad )
{
	int status=0;
	unsigned char initVector[8];
	A_RC2_CBC_PARAMS rc2Params;

	switch (i_nAlgId)
	{

	case SYM_RC2_CBC:
		if ((toPad != 0) && (toPad != 1)) {
			status = -1;
			break;
		}

		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_RC2_CBC_CTX));
		if ( ((VS_SYM_CTX*)*o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
	     
		T_memcpy(initVector, iv, 8);
		rc2Params.effectiveKeyBits = i_nEffectiveKeyLen;
		rc2Params.iv = (unsigned char*)initVector;
		if (toPad == 1) 
			A_RC2_CBCEncryptInit ((A_RC2_CBC_CTX*)(((VS_SYM_CTX*)*o_ppvoidContext)->algoContext), i_pRCKey, &rc2Params, MODE_CBC_Pad_8);
		else
			A_RC2_CBCEncryptInit ((A_RC2_CBC_CTX*)(((VS_SYM_CTX*)*o_ppvoidContext)->algoContext), i_pRCKey, &rc2Params, MODE_CBC_Pad_0);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		((VS_SYM_CTX*)*o_ppvoidContext)->remainder = 0;
		((VS_SYM_CTX*)*o_ppvoidContext)->boolPadding = toPad;
		break;

	case SYM_3DES:
		if ((toPad != 0) && (toPad != 1)) {
			status = -1;
			break;
		}

		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_DES_EDE3_CBC_CTX));
		if ( ((VS_SYM_CTX*)*o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
	     
		T_memcpy(initVector, iv, 8);

		if (toPad == 1) 
			A_DES_EDE3_CBCEncryptInit ((A_DES_EDE3_CBC_CTX*)(((VS_SYM_CTX*)*o_ppvoidContext)->algoContext), i_pRCKey->data, iv, MODE_CBC_Pad_8);
		else
			A_DES_EDE3_CBCEncryptInit ((A_DES_EDE3_CBC_CTX*)(((VS_SYM_CTX*)*o_ppvoidContext)->algoContext), i_pRCKey->data, iv, MODE_CBC_Pad_0);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		((VS_SYM_CTX*)*o_ppvoidContext)->remainder = 0;
		((VS_SYM_CTX*)*o_ppvoidContext)->boolPadding = toPad;
		break;

	case SYM_RC4:
		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_RC4_CTX));
		if ( ((VS_SYM_CTX*)o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
		A_RC4Init ((A_RC4_CTX*)(((VS_SYM_CTX*)*o_ppvoidContext)->algoContext), i_pRCKey);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		((VS_SYM_CTX*)*o_ppvoidContext)->remainder = 0;
		break;

	default:
		status = -1;
		break;
	}

	return status;
}


/*********************************************************************************************************
 * Function SymEncryptDataUpdate ()
 * This function is called to update the data that is to be encrypted. For large data, this function
 * can be called multiple times. 
 *
 * parameters : i_pvoidContext : the encryption context, it is allocated in the SymEncryptDataBegin function
 *              inData : the data that is to be encrypted
 *              inDataSize: the size of inData
 *              *outDataSize : should contain the maximum size for the encrypted data
 *
 * outputs    : outData : the encrypted Data
 *              *outDataSize : contains the size of the encrypted data
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymEncryptDataUpdate 
(
	void* i_pvoidContext, 
	unsigned char* inData, 
	unsigned int inDataSize, 
	unsigned char* outData, 
	unsigned int* outDataSize
)
{
	int status=0;

	switch (((VS_SYM_CTX*)i_pvoidContext)->algorithm)
	{
  	case SYM_RC2_CBC:
		((VS_SYM_CTX*)i_pvoidContext)->remainder = (((VS_SYM_CTX*)i_pvoidContext)->remainder + inDataSize) % 8;
		status = A_RC2_CBCEncryptUpdate ((A_RC2_CBC_CTX*)(((VS_SYM_CTX*)i_pvoidContext)->algoContext), outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

  	case SYM_3DES:
		((VS_SYM_CTX*)i_pvoidContext)->remainder = (((VS_SYM_CTX*)i_pvoidContext)->remainder + inDataSize) % 8;
		status = A_DES_EDE3_CBCEncryptUpdate ((A_DES_EDE3_CBC_CTX*)(((VS_SYM_CTX*)i_pvoidContext)->algoContext), outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

	case SYM_RC4:
		status = A_RC4Update ((A_RC4_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

	default:
		status = -1;
		break;
	}

	return status;
}

/*********************************************************************************************************
 * Function SymEncryptDataEnd ()
 * This function is called end the symmetric encryption operation. This might return some residual 
 * encrypted data that was not returned at time of the updates (SYM_RC2_CBC)
 *
 * parameters : i_pvoidContext : the encryption context, it is allocated in the SymEncryptDataBegin function
 *              *outDataSize : should contain the maximum size for the encrypted data
 *
 * outputs    : outData : the encrypted Data
 *              *outDataSize : contains the size of the encrypted data
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymEncryptDataEnd (void* i_pvoidContext, unsigned char* outData, unsigned int* outDataSize )
{
	int status=0;
	unsigned char finalBuffer[8];
	unsigned int padLen;

	switch (((VS_SYM_CTX*)i_pvoidContext)->algorithm)
	{
  	case SYM_RC2_CBC:
		if ( ((VS_SYM_CTX*)i_pvoidContext)->boolPadding == 1) {
		   /* do the padding and get the final output*/
		   padLen = 8 - ((VS_SYM_CTX*)i_pvoidContext)->remainder;
		   T_memset ((POINTER)finalBuffer, padLen, padLen);

		    status = A_RC2_CBCEncryptUpdate ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, 
			   	  outData, outDataSize, 
				  *outDataSize, finalBuffer, padLen);
		    if (status != 0)
   			   break;
		} else {
			/* application chooses to do padding */
			if ( ((VS_SYM_CTX*)i_pvoidContext)->remainder != 0) {
				/* data was not multiple of 8 so return error */
				status = -1;
				break;
			}
			else {
				*outDataSize = 0;
			}
		}
		((VS_SYM_CTX*)i_pvoidContext)->remainder = 0;
		status = A_RC2_CBCEncryptFinal ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		break;

  	case SYM_3DES:
		if ( ((VS_SYM_CTX*)i_pvoidContext)->boolPadding == 1) {
		   /* do the padding and get the final output*/
		   padLen = 8 - ((VS_SYM_CTX*)i_pvoidContext)->remainder;
		   T_memset ((POINTER)finalBuffer, padLen, padLen);

		    status = A_DES_EDE3_CBCEncryptUpdate ((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, 
			   	  outData, outDataSize, 
				  *outDataSize, finalBuffer, padLen);
		    if (status != 0)
   			   break;
		} else {
			/* application chooses to do padding */
			if ( ((VS_SYM_CTX*)i_pvoidContext)->remainder != 0) {
				/* data was not multiple of 8 so return error */
				status = -1;
				break;
			}
			else {
				*outDataSize = 0;
			}
		}
		((VS_SYM_CTX*)i_pvoidContext)->remainder = 0;
		status = A_DES_EDE3_CBCEncryptFinal ((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		break;
	
	case SYM_RC4:
		status = A_RC4Final ((A_RC4_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		break;

	default:
		status = -1;
		break;
	}

	if (((VS_SYM_CTX*)i_pvoidContext)->algoContext) {
		T_free(((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		((VS_SYM_CTX*)i_pvoidContext)->algoContext = NULL;
	}

	if (i_pvoidContext != NULL) {
		T_free (i_pvoidContext);
		i_pvoidContext = NULL;
	}
	return status;
}



/*********************************************************************************************************
 * Function SymDecryptDataBegin ()
 * This function can be used the initialize a symmetric decryption operation
 * Generally the call is followed by calls (possibly multiple to SymDecryptDataUpdate and a call 
 * to SymDecryptDataEnd
 *
 * parameters : nAlgId: can be SYM_RC2_CBC SYM_3DES or RC4
 *                      if nAlgId is RC4 the parameter iv should be NULL.
 *              iv: the initialization vector, only valid if nAlgId is SYM_RC2_CBC or SYM_3DES
 *                  should be at least 8 bytes in length. The same iv needs to be passed
 *                  as the one passed during encryption.
 *				nEffectiveKeyLen: length of the symmetric key
 *
 * outputs:     o_ppvoidContext : the decryption context, it is allocated within this function and needs to 
 *                                be passed in future calls to SymDecryptDataUpdate and a call 
 *                                to SymDecryptDataEndData (where it is freed).
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymDecryptDataBegin ( int i_nAlgId, ITEM* i_pRCKey, int i_nEffectiveKeyLen, void** o_ppvoidContext, unsigned char *iv, unsigned int toPad )
{
	int status=0;
	unsigned char initVector[8];
	A_RC2_CBC_PARAMS rc2Params;

	switch (i_nAlgId)
	{
	case SYM_RC2_CBC:
		if ((toPad != 0) && (toPad != 1)) {
			status = -1;
			break;
		}
		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_RC2_CBC_CTX));
		if ( ((VS_SYM_CTX*)*o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
		T_memcpy(initVector, iv, 8);
		rc2Params.effectiveKeyBits = i_nEffectiveKeyLen;
		rc2Params.iv = (unsigned char*)initVector;
		if (toPad == 0)
			A_RC2_CBCDecryptInit ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)*o_ppvoidContext)->algoContext, i_pRCKey, &rc2Params, MODE_CBC_Pad_0);
		else
			A_RC2_CBCDecryptInit ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)*o_ppvoidContext)->algoContext, i_pRCKey, &rc2Params, MODE_CBC_Pad_8);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		((VS_SYM_CTX*)*o_ppvoidContext)->boolPadding = toPad;
		break;


	case SYM_3DES :
		if ((toPad != 0) && (toPad != 1)) {
			status = -1;
			break;
		}
		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_DES_EDE3_CBC_CTX));
		if ( ((VS_SYM_CTX*)*o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
		
		T_memcpy(initVector, iv, 8);

		if (toPad == 0)
			 A_DES_EDE3_CBCDecryptInit((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)*o_ppvoidContext)->algoContext, i_pRCKey->data, iv, MODE_CBC_Pad_0);
		else
			 A_DES_EDE3_CBCDecryptInit((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)*o_ppvoidContext)->algoContext, i_pRCKey->data, iv, MODE_CBC_Pad_8);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		((VS_SYM_CTX*)*o_ppvoidContext)->boolPadding = toPad;
		break;

	case SYM_RC4:
		*o_ppvoidContext = T_malloc(sizeof(VS_SYM_CTX));
		if (*o_ppvoidContext == NULL)
		{
			status = -1;
			break;
		}
		((VS_SYM_CTX*)*o_ppvoidContext)->algoContext = T_malloc(sizeof(A_RC4_CTX));
		if ( ((VS_SYM_CTX*)*o_ppvoidContext)->algoContext == NULL )
		{
			status = -1;
			break;
		}
		A_RC4Init ((A_RC4_CTX*)((VS_SYM_CTX*)*o_ppvoidContext)->algoContext, i_pRCKey);
		((VS_SYM_CTX*)*o_ppvoidContext)->algorithm = i_nAlgId;
		break;

	default:
		status = -1;
		break;
	}

	return status;
}


/*********************************************************************************************************
 * Function SymDecryptDataUpdate ()
 * This function is called to update the data that is to be decrypted. For large data, this function
 * can be called multiple times. 
 *
 * parameters : i_pvoidContext : the decryption context, it is allocated in the SymDecryptDataBegin function
 *              inData : the data that is to be decrypted
 *              inDataSize: the size of inData
 *              *outDataSize : should contain the maximum size for the decrypted data
 *
 * outputs    : outData : the decrypted Data
 *              *outDataSize : contains the size of the decrypted data
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymDecryptDataUpdate 
(
	void* i_pvoidContext, 
	unsigned char* inData, 
	unsigned int inDataSize, 
	unsigned char* outData, 
	unsigned int* outDataSize
)
{
	int status=0;

	switch (((VS_SYM_CTX*)i_pvoidContext)->algorithm)
	{
  	case SYM_RC2_CBC:
		status = A_RC2_CBCDecryptUpdate ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

	case SYM_3DES:
		status = A_DES_EDE3_CBCDecryptUpdate((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

	case SYM_RC4:
		status = A_RC4Update ((A_RC4_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, outData, outDataSize, *outDataSize, inData, inDataSize);
		break;

	default:
		status = -1;
		break;
	}

	return status;
}


/*********************************************************************************************************
 * Function SymDecryptDataEnd ()
 * This function is called end the symmetric decryption operation. This might return some residual 
 * decrypted data that was not returned at time of the updates (SYM_RC2_CBC or SYM_3DES)
 *
 * parameters : i_pvoidContext : the decryption context, it is allocated in the SymDecryptDataBegin function
 *              *outDataSize : should contain the maximum size for the decrypted data
 *
 * outputs    : outData : the decrypted Data
 *              *outDataSize : contains the size of the decrypted data
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymDecryptDataEnd (void* i_pvoidContext, 	unsigned char* outData, unsigned int* outDataSize)
{
	int status=0;
	
	unsigned char finalBuffer[16], *padBuffer;
    unsigned int padLen, localPartOutLen, i, maxOutDataSize;

	switch (((VS_SYM_CTX*)i_pvoidContext)->algorithm)
	{
  	case SYM_RC2_CBC:
		status = A_RC2_CBCDecryptFinal ((A_RC2_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, finalBuffer, &localPartOutLen, sizeof(finalBuffer));
		if (((VS_SYM_CTX*)i_pvoidContext)->boolPadding == 0)
		{
			/* application is doing the un-padding */
			if (localPartOutLen != 0)
				status = -1;

			*outDataSize = 0;
			break;
		}

		if (localPartOutLen == 8)
			padBuffer = finalBuffer;
		else if (localPartOutLen == 16)
			padBuffer = finalBuffer + 8;

		/* Check that padding is one 1 to eight 8's.
		*/
		if ((padLen = (unsigned int)padBuffer[7]) == 0 || padLen > 8)
			{ status = -1; break;}
		for (i = 8 - padLen; i < 8; i++) {
			if ((unsigned int)padBuffer[i] != padLen)
				{ status = -1; goto CleanUp;}
		}

		maxOutDataSize = *outDataSize;
	    if ((*outDataSize = localPartOutLen - padLen) > maxOutDataSize)
			{ status = -1; break;}
		T_memcpy ((POINTER)outData, (POINTER)finalBuffer, *outDataSize);
		T_memset ((POINTER)finalBuffer, 0, sizeof (finalBuffer));


		break;

	case SYM_3DES:
		status = A_DES_EDE3_CBCDecryptFinal ((A_DES_EDE3_CBC_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext, finalBuffer, &localPartOutLen, sizeof(finalBuffer));
		if (((VS_SYM_CTX*)i_pvoidContext)->boolPadding == 0)
		{
			/* application is doing the un-padding */
			if (localPartOutLen != 0)
				status = -1;

			*outDataSize = 0;
			break;
		}

		if (localPartOutLen == 8)
			padBuffer = finalBuffer;
		else if (localPartOutLen == 16)
			padBuffer = finalBuffer + 8;

		/* Check that padding is one 1 to eight 8's.
		*/
		if ((padLen = (unsigned int)padBuffer[7]) == 0 || padLen > 8)
			{ status = -1; break;}
		for (i = 8 - padLen; i < 8; i++) {
			if ((unsigned int)padBuffer[i] != padLen)
				{ status = -1; goto CleanUp;}
		}

		maxOutDataSize = *outDataSize;
	    if ((*outDataSize = localPartOutLen - padLen) > maxOutDataSize)
			{ status = -1; break;}
		T_memcpy ((POINTER)outData, (POINTER)finalBuffer, *outDataSize);
		T_memset ((POINTER)finalBuffer, 0, sizeof (finalBuffer));


		break;

	case SYM_RC4:
		status = A_RC4Final ((A_RC4_CTX*)((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		break;

	default:
		status = -1;
		break;
	}

CleanUp:
	if (((VS_SYM_CTX*)i_pvoidContext)->algoContext) {
		T_free(((VS_SYM_CTX*)i_pvoidContext)->algoContext);
		((VS_SYM_CTX*)i_pvoidContext)->algoContext = NULL;
	}
	if (i_pvoidContext != NULL) {
		T_free (i_pvoidContext);
		i_pvoidContext = NULL;
	}
	return status;
}
  


/*********************************************************************************************************
 * Function GenerateRandomBlock ()
 * This function is called to generate a random string of bytes of the specified length
 *
 * parameters : in_pcharRandBlock : the pointer to memory
 *              in_pRandBlockLen : contains the size of random data to be generated
 *
 * outputs    : in_pcharRandBlock : the random number
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int GenerateRandomBlock(unsigned char* in_pcharRandBlock, unsigned int in_nRandBlockLen)
{

	unsigned int status;

	A_MD5_RANDOM_CTX randomContext;
	unsigned int randomSeedLen;
	unsigned char randomSeed[POOL_BLOCK_SIZE];

	do 
	{
		A_MD5RandomInit (&randomContext);

		status = GetPseudoRandomSeedData(randomSeed, &randomSeedLen, POOL_BLOCK_SIZE);
		if (status != 0)
		{
			randomSeedLen = POOL_BLOCK_SIZE;
			break;
		}
        A_MD5RandomUpdate (&randomContext, randomSeed, randomSeedLen);
		A_MD5RandomGenerateBytes (&randomContext, in_pcharRandBlock, in_nRandBlockLen);
	}while(0);

	if (status == 0)
		return 0;
	else 
		return -1;
}


/*********************************************************************************************************
 * Function GetPseudoRandomSeedData ()
 * This function is called to generate seed data for random number generation. This is done by getting
 * current system information from the operating system.
 *
 * parameters : maxSeedLen : the length of desired seed data
 *              outSeedData: pointer to memory for seed data
 *
 * outputs    : outSeedData: the seed dtaa
 *              outSeedLength: the length of generated seed data 
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int GetPseudoRandomSeedData (unsigned char* outSeedData, unsigned int *outSeedLength, unsigned int maxSeedLength)
{
	int status=0;
	    
	do 
	{		
		if (maxSeedLength != POOL_BLOCK_SIZE)
		{
			status = -1;
			break;
		}
		if (gRNGInitialized==0 || gNextBlock >= gPoolSize )
			AddRandomPool();

		// if the random number initialization failed
		if (gRNGInitialized==0)
		{
			status = -1;
			break;		
		}
		
		T_memcpy ((void*)outSeedData, (void*)(gPool+(gNextBlock*POOL_BLOCK_SIZE)), POOL_BLOCK_SIZE); 
		*outSeedLength = POOL_BLOCK_SIZE;
		gNextBlock++;
	} while (0);
	
	return status;
}


#if 0
static void AddRandomPool()
{
	int status=0;

	// initialize or reset the random number globals.	    
    gRNGInitialized = 1;
	gNextBlock = 0;
	gPoolSize = POOL_NO_BLOCKS;

	/* need to allocate memory for the global pool if necessary */
	if (gPool == NULL)
	{
		gPool = (unsigned char*)malloc((POOL_NO_BLOCKS*POOL_BLOCK_SIZE) + 256);
		if (gPool == NULL)
		{
			gRNGInitialized = 0;
			return;
		}
	}
	else
		T_memset(gPool, 0, POOL_NO_BLOCKS*POOL_BLOCK_SIZE);

#ifdef WIN32
	OSVERSIONINFO osvi;
	unsigned int bWinNT=0;
	unsigned int nRound = 0;
	DWORD currentSize, bufferSize, minimumSize;
	bufferSize = gPoolSize*POOL_BLOCK_SIZE;
	minimumSize = gPoolSize*POOL_BLOCK_SIZE;

	unsigned char *perfData9x, *collectionPointer;
	//time_t long_time;
	DWORD dwTickTime;

	/* this is for NT only */
	PPERF_DATA_BLOCK perfDataNT = NULL;    
	void *sha1Handle;
	unsigned int nInBlockSize;
	unsigned int nInRounds;
	unsigned char* ptrInBuf;
	unsigned char* ptrOutBuf;
	unsigned int oldSize=0;
	unsigned char* oldPtr=NULL;


    /* get the OS version */
	osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
	status = GetVersionEx (&osvi);
	if (status == 0)
		{status = -1; gRNGInitialized = 0; return;}
	else
		status = 0;
	if( osvi.dwPlatformId == VER_PLATFORM_WIN32_NT )
		bWinNT = 1;
	else 
		if (osvi.dwPlatformId != VER_PLATFORM_WIN32_WINDOWS)
			{status=-1; gRNGInitialized = 0; return;}

#endif
#ifdef SOLARIS 
    FILE *gMic_fp = NULL;
    int              bufferSize = gPoolSize*POOL_BLOCK_SIZE;
#endif 

	do {		

#ifdef WIN32
		if ( bWinNT == 1)
		{
			//cout << "\n the OS is Win NT \n";
			/* used only for Windows NT */

			/* Keep track of the current size in a separate variable, in
			* case the call returns ERROR_MORE_DATA but modifies bufferSize.
			*/

			/* phase 1: get the data */

			//cout << "\ncurrent size = " << currentSize;

			oldSize = 0;
			oldPtr = NULL;
			do 
			{
				bufferSize = 50000;
				currentSize = bufferSize;
				perfDataNT = (PPERF_DATA_BLOCK) malloc (bufferSize + 256);
				if (perfDataNT == (PPERF_DATA_BLOCK)NULL_PTR)
				{
					status = -1; break;
				}
				while ((status = RegQueryValueEx (HKEY_PERFORMANCE_DATA, "2 4", 
					NULL, NULL,( LPBYTE) perfDataNT, &bufferSize)) == ERROR_MORE_DATA) 
				{
					currentSize += 20000;
					//cout << "\ncurrent size = " << currentSize;
					bufferSize = currentSize;
					perfDataNT = (PPERF_DATA_BLOCK) realloc (perfDataNT, bufferSize + 256);    
					if (perfDataNT == (PPERF_DATA_BLOCK)NULL_PTR)
					{
						status = -1; break;
					}
				}

				RegCloseKey (HKEY_PERFORMANCE_DATA);

				if (status == -1)
					break;

				if (oldPtr ==NULL)
				{
					oldPtr = (unsigned char*)perfDataNT;
					oldSize = bufferSize;
				} else {
					oldPtr = (unsigned char*)realloc(oldPtr, oldSize+bufferSize);
					T_memcpy((void*)(oldPtr+oldSize), perfDataNT, bufferSize);
					free (perfDataNT);
					perfDataNT = NULL;
					oldSize += bufferSize;
				}	

			} while (oldSize < minimumSize);

			if (status != 0) {
			  break;
			}
			 
			if ( oldSize < minimumSize)
			{
				status = -1;
				break;
			}			
		}
		else
		{
			//cout << "\nthe os is Win9x";
			oldSize = 2*bufferSize;
			currentSize = bufferSize;
			/* Win 9x stuff here */
			//perfData9x = (unsigned char*)malloc(bufferSize + 256);
			//if (perfData9x == NULL)
			//	{status = -1; break;}

			perfData9x = (unsigned char*)malloc(oldSize+256);
			if (perfData9x == NULL)
				{status = -1; break;}
			// get the performance data
			collectionPointer = perfData9x;
			//cout << "\ncurrent size = " << currentSize;
			EnableDataCollection ( "KERNEL", "CPUUsage" );
			EnableDataCollection ( "VMM", "cpgCommit" );
			EnableDataCollection ( "VFAT", "BReadsSec" );
			EnableDataCollection ( "VMM", "cDiscards" );
			EnableDataCollection ( "VMM", "cPageFaults" );


			while ((collectionPointer - perfData9x) < oldSize)
			{
				CollectPerfData ( "KERNEL", "CPUUsage", (DWORD*)collectionPointer);
				collectionPointer+= sizeof(DWORD);
				//CollectPerfData ( "VMM", "cpgCommit", (DWORD*)collectionPointer);
				//collectionPointer+= sizeof(DWORD);
				CollectPerfData ( "VFAT", "BReadsSec", (DWORD*)collectionPointer);
				collectionPointer+= sizeof(DWORD);
				//CollectPerfData ( "VMM", "cpgCommit", (DWORD*)collectionPointer);
				//collectionPointer+= sizeof(DWORD);
				CollectPerfData ( "VMM", "cPageFaults", (DWORD*)collectionPointer);
				collectionPointer+= sizeof(DWORD);
				//time( &long_time ); 
				dwTickTime = GetTickCount();
				T_memcpy((void*)collectionPointer, (void*)&dwTickTime, sizeof(dwTickTime));
				collectionPointer+= sizeof(dwTickTime);
			}

			DisableDataCollection ( "KERNEL", "CPUUsage" );
			DisableDataCollection ( "VMM", "cpgCommit" );
			DisableDataCollection ( "VFAT", "BReadsSec" );
			DisableDataCollection ( "VMM", "cpgCommit" );
			DisableDataCollection ( "VMM", "cPageFaults" );
			oldPtr = perfData9x;	
		}

		/* phase 2, hash the data and put it in gPool */
		/* give bufferSize*20/minimumSize blocks to SHA1, each will return 20 bytes */
		nInBlockSize = (oldSize*20)/minimumSize;
		nInRounds = minimumSize/20;
		ptrInBuf = (unsigned char*)oldPtr;
		ptrOutBuf = gPool;

		for (nRound=0; nRound < nInRounds; ++nRound)
		{
			if ( HashBegin (HASH_SHA1, &sha1Handle ) == -1)
				{status = -1; break;}
			if (HashData (HASH_SHA1, sha1Handle, ptrInBuf, nInBlockSize) == -1)
				{status = -1; break;}
			if (HashEnd (HASH_SHA1, sha1Handle, ptrOutBuf, 20) == -1)
				{status = -1; break;}
			ptrInBuf += (nInBlockSize-2);
			ptrOutBuf += 20;
		}
		if (oldPtr != NULL)
			free (oldPtr);
		if (status != 0)
			break;
#endif
#ifdef SOLARIS
		if ((gMic_fp = fopen ("/dev/audio", "r")) == NULL) {
			status = -1; break;
		}

		if (fread (gPool, sizeof (unsigned char), bufferSize, gMic_fp) == 0) {
			status = -1; break;
		}
		fclose(gMic_fp);
#endif 

	} while(0);

	if (status == -1)
	{
		gRNGInitialized = 0;
		gPoolSize = 0;
	}

	return;
		
}
#else
static void AddRandomPool()
{
	int status=0;

	// initialize or reset the random number globals.	    
    gRNGInitialized = 1;
	gNextBlock = 0;
	gPoolSize = POOL_NO_BLOCKS;

	/* need to allocate memory for the global pool if necessary */
	if (gPool == NULL)
	{
		gPool = (unsigned char*)malloc(POOL_NO_BLOCKS*POOL_BLOCK_SIZE);
		if (gPool == NULL)
		{
			gRNGInitialized = 0;
			return;
		}
	}
	else
		T_memset(gPool, 0, POOL_NO_BLOCKS*POOL_BLOCK_SIZE);

#ifdef WIN32
	HMODULE hModAdvapiDll = NULL;
	LPFNCryptGenRandom lpfnGenRndm = NULL;
	LPFNCryptAcquireContext lfpnAcquireCtxt = NULL;
	LPFNCryptReleaseContext lpfnReleaseCtxt = NULL;
	GUID guid;
	BOOL bUseGuid = FALSE;
	DWORD dwGuidLen = 0, dwRndmNumSize = 0;
	UINT nRound = 0;
	PBYTE pbRandom = NULL;
	PBYTE ptrRandomData = NULL;
	PBYTE ptrGPool = NULL;
	void *sha1Handle = NULL;
#endif

#ifdef SOLARIS 
    FILE *gMic_fp = NULL;
    int              bufferSize = gPoolSize*POOL_BLOCK_SIZE;
#endif 

	do {		

#ifdef WIN32

		// Get a guid/uuid from the system, if this fails then do not return error, the guid will not be used
		// in getting the random pool in this case
		if (CoCreateGuid(&guid) == S_OK)
			bUseGuid = TRUE;

		hModAdvapiDll = LoadLibrary("advapi32.dll");
		if (hModAdvapiDll == NULL) {
			status = -1; break;
		}

		lpfnGenRndm = (LPFNCryptGenRandom)GetProcAddress(hModAdvapiDll, "CryptGenRandom");
		if (lpfnGenRndm == NULL) {
			status = -1; break;
		}

		lfpnAcquireCtxt = (LPFNCryptAcquireContext)GetProcAddress(hModAdvapiDll, "CryptAcquireContextA");
		if (lfpnAcquireCtxt == NULL) {
			status = -1; break;
		}

		lpfnReleaseCtxt = (LPFNCryptReleaseContext)GetProcAddress(hModAdvapiDll, "CryptReleaseContext");
		if (lpfnReleaseCtxt == NULL) {
			status = -1; break;
		}

		// Do not do the acquire context everytime as it is take a long time on Win95 and Winnt
		// Not releasing the 'g_hCryptProv' anywhere!
		if(g_hCryptProv == NULL)
		{
			if (!lfpnAcquireCtxt(&g_hCryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
				status = -1; break;
			}
		}

		pbRandom = (PBYTE)malloc(POOL_BLOCK_SIZE);
		if (!pbRandom) {
			status = -1; break;
		}

		if(bUseGuid == TRUE)
		{
			ptrRandomData = pbRandom;
			memcpy(ptrRandomData, &(guid.Data1), sizeof(guid.Data1));
			dwGuidLen = sizeof(guid.Data1);
			ptrRandomData += sizeof(guid.Data1);

			memcpy(ptrRandomData, &(guid.Data2), sizeof(guid.Data2));
			dwGuidLen += sizeof(guid.Data2);
			ptrRandomData += sizeof(guid.Data2);

			memcpy(ptrRandomData, &(guid.Data3), sizeof(guid.Data3));
			dwGuidLen += sizeof(guid.Data3);
			ptrRandomData += sizeof(guid.Data3);

			memcpy(ptrRandomData, &(guid.Data4), sizeof(guid.Data4));
			dwGuidLen += sizeof(guid.Data4);
			ptrRandomData += sizeof(guid.Data4);

			dwRndmNumSize = POOL_BLOCK_SIZE - dwGuidLen;
		}
		else
		{
			dwRndmNumSize = POOL_BLOCK_SIZE;
			dwGuidLen = 0;
		}

		if (!lpfnGenRndm(g_hCryptProv, dwRndmNumSize, pbRandom + dwGuidLen)) {
			status = -1; break;
		}

		// Hash the data and put it in the gpool
		ptrRandomData = pbRandom;
		ptrGPool = gPool;
		for (nRound=0; nRound < POOL_BLOCK_SIZE/20; nRound++)
		{
			if ( HashBegin (HASH_SHA1, &sha1Handle ) == -1)
				{status = -1; break;}
			if (HashData (HASH_SHA1, sha1Handle, ptrRandomData, 20) == -1)
				{status = -1; break;}
			if (HashEnd (HASH_SHA1, sha1Handle, ptrGPool, 20) == -1)
				{status = -1; break;}
			ptrRandomData += 20;
			ptrGPool += 20;
		}

#endif

#ifdef SOLARIS
		if ((gMic_fp = fopen ("/dev/audio", "r")) == NULL) {
			status = -1; break;
		}

		if (fread (gPool, sizeof (unsigned char), bufferSize, gMic_fp) == 0) {
			status = -1; break;
		}
		fclose(gMic_fp);
#endif 

	} while(0);

	if (status == -1)
	{
		gRNGInitialized = 0;
		gPoolSize = 0;
	}

#ifdef WIN32
	if (pbRandom)
	{
		free(pbRandom);
		pbRandom = NULL;
	}

#endif

	return;
		
}
#endif


/*********************************************************************************************************
 * Function EnableDataCollection ()
 * This function is called to enable collection of a specific system data, by initializing the 
 * appropriate counter in the Win95/98 registry
 * 
 * parameters : szObjName : the name of system object e.g. KERNEL
 *              szCounterName: the name of the specific counter e.g. CPUUsage
 *            
 * 
 * Return values : TRUE : success
 *                 FALSE: on error.
 *********************************************************************************************************/
BOOL EnableDataCollection(char *szObjName, char *szCounterName)
   {
    HKEY hOpen;
    DWORD cbData;
    DWORD dwType;
    LPBYTE pByte;
    DWORD rc;
    char *szCounterData;
    BOOL bSuccess = TRUE;

    if ( (rc = RegOpenKeyEx(HKEY_DYN_DATA,"PerfStats\\StartStat", 0,
                           KEY_READ, &hOpen)) == ERROR_SUCCESS)
    {
      // concatenate the object and couter key names
      szCounterData = (char*)malloc(lstrlen(szObjName) + lstrlen(szCounterName) + 2);
      wsprintf(szCounterData, "%s\\%s", szObjName, szCounterName);

      // query to get data size
      if ( (rc = RegQueryValueEx(hOpen,szCounterData,NULL,&dwType,
             NULL, &cbData )) == ERROR_SUCCESS )
      {
         pByte = (LPBYTE)malloc(cbData);

         // query the performance start key to initialize performance data
         // query the start key to initialize performance data
         rc = RegQueryValueEx(hOpen,szCounterData,NULL,&dwType, pByte,
                              &cbData );
         // at this point we don't do anything with the data
         //  free up resources
         free(pByte);
      }
      else
         bSuccess = FALSE;

      RegCloseKey(hOpen);
      free(szCounterData);
    }
    else
      bSuccess = FALSE;

    return bSuccess;
   }


/*********************************************************************************************************
 * Function CollectPerfData ()
 * This function is called to collect specific system data, by querying the 
 * appropriate counter in the Win95/98 registry
 * 
 * parameters : szObjName : the name of system object e.g. KERNEL
 *              szCounterName: the name of the specific counter e.g. CPUUsage
 *
 * outputs : pdwData: the current value of the specific counter
 *            
 * 
 * Return values : TRUE : success
 *                 FALSE: on error.
 *********************************************************************************************************/
BOOL CollectPerfData(char *szObjName, char *szCounterName, DWORD *pdwData)
   {
    HKEY hOpen;
    DWORD dwType;
    DWORD cbData;
    char *szCounterData;
    DWORD rc;
    BOOL bSuccess = TRUE;

    // concatenate the object and counter keys
    szCounterData = (char*)malloc(lstrlen(szObjName) + lstrlen(szCounterName) + 2);
    wsprintf(szCounterData, "%s\\%s", szObjName, szCounterName);

    // open performance data key
    if ( (rc = RegOpenKeyEx(HKEY_DYN_DATA,"PerfStats\\StatData", 0,
         KEY_READ, &hOpen)) == ERROR_SUCCESS)
    {
      cbData = sizeof(DWORD);
      // retrieve performance data which is of size of DWORD
      rc=RegQueryValueEx(hOpen,szCounterData,0,&dwType,
            (LPBYTE)pdwData,&cbData );

      // let the caller know if it worked or not
      bSuccess = rc == ERROR_SUCCESS;
      RegCloseKey(hOpen);
    }
    else
      bSuccess = FALSE;

    // free the resources
    free(szCounterData);
    return bSuccess;
   }

/*********************************************************************************************************
 * Function DisableDataCollection ()
 * This function is called to disable collection of a specific system data, by setting the 
 * appropriate counter in the Win95/98 registry
 * 
 * parameters : szObjName : the name of system object e.g. KERNEL
 *              szCounterName: the name of the specific counter e.g. CPUUsage
 *            
 * 
 * Return values : TRUE : success
 *                 FALSE: on error.
 *********************************************************************************************************/
BOOL DisableDataCollection(char *szObjName, char *szCounterName)
   {
    HKEY hOpen;
    LPBYTE pByte;
    DWORD cbData;
    DWORD dwType;
    DWORD rc;
    char *szCounterData;
    BOOL bSuccess = TRUE;

    if ( (rc = RegOpenKeyEx(HKEY_DYN_DATA,"PerfStats\\StopStat", 0,
                           KEY_READ, &hOpen)) == ERROR_SUCCESS)
    {
      // concatenate the object and couter key names
      szCounterData = (char*)malloc(lstrlen(szObjName) + lstrlen(szCounterName) + 2);
      wsprintf(szCounterData, "%s\\%s", szObjName, szCounterName);

      // query to get data size
      if ( (rc = RegQueryValueEx(hOpen,szCounterData,NULL,&dwType,
            NULL, &cbData )) == ERROR_SUCCESS )
      {
         pByte = (LPBYTE)malloc(cbData);

         // query the performance start key to initialize performance data
         // query the start key to initialize performance data
         rc = RegQueryValueEx(hOpen,szCounterData,NULL,&dwType, pByte,
                              &cbData );
         // at this point we don't do anything with the data
         // free up resources
         free(pByte);

      }
      else
         bSuccess = FALSE;

      RegCloseKey(hOpen);
      free(szCounterData);
    }
    else
      bSuccess = FALSE;

    return bSuccess;
   }


/* Returns 0, AE_CANCEL.
 */

int CheckSurrender (A_SURRENDER_CTX *surrenderContext)
{
  if (surrenderContext == (A_SURRENDER_CTX *)NULL_PTR)
    return (0);

  if ((*surrenderContext->Surrender) (surrenderContext->handle))
    return (AE_CANCEL);
  return (0);
}




int ALG_ErrorCode (int status)
{
  switch (status) {
    case CMP_MEMORY:
      return (AE_ALLOC);
    case CMP_MODULUS:
      return (AE_MODULUS_LEN);
    case CMP_RANGE:
      return (AE_INPUT_DATA);
    case CMP_DOMAIN:
      return (AE_INPUT_DATA);
    case CMP_ZERO_DIVIDE:
      return (AE_INPUT_DATA);
    case CMP_NEGATIVE:
      return (AE_INPUT_DATA);
    case CMP_INSUFFICIENT_SPACE:
      return (AE_INPUT_DATA);
    case CMP_INVERSE:
      return (AE_INPUT_DATA);
    case CMP_INVALID_ARGUMENT:
    case CMP_INVALID_ADDRESS:
    case CMP_INVALID_VALUE:
    case CMP_LENGTH:
      return (AE_INPUT_DATA);
    case CMP_OUTPUT_LENGTH:
      return (AE_OUTPUT_LEN);
    default:
      return (status);
  }
}


unsigned int EraseMemory ( unsigned int dwMemoryBlockSize, PBYTE pbyteMemoryBlock )
{
	if ( (pbyteMemoryBlock == NULL) || (0 > dwMemoryBlockSize) )
		return	-1;

	::memset ( (void*) pbyteMemoryBlock, '0', dwMemoryBlockSize );
	return 0;
}
