
/*--------------------------------------------------------------------\
| Copyright (C) VeriSign, Inc. created 1998. All rights reserved.     |
| This is an unpublished work protected as such under copyright law.  |
| This work contains proprietary, confidential, and trade secret      |
| information of VeriSign, Inc.  Use, disclosure or reproduction      |
| without the expressed written authorization of VeriSign, Inc.       |
| is prohibited.                                                      |
\--------------------------------------------------------------------*/


#ifndef LITE_INC
#define LITE_INC

#define BYTE unsigned char
#define PBYTE BYTE*

#include "atypes.h"
#include "bsafelite.h"
#include "rsakeygn.h"
#include "rsa.h"
#include "sha.h"
#include "rc4.h"
#include "rc2cbc.h"

/* the hash algorithms */
#define HASH_SHA1   32772       /* hash using SHA 1 */
#define HASH_MD2	32769       /* hash using MD 2 */
#define HASH_MD5	32771       /* hash using MD 5 */

/* the symmetric encryption algorithms available */
#define SYM_RC2_CBC 26114      /* RC2 encryption in CBC mode */
#define SYM_RC4     26625      /* RC4 encryption */
#define SYM_3DES	26636	   /* Triple DES with 3 independent keys*/


typedef struct VS_SYM_CTX {
  void* algoContext;
  unsigned int algorithm;
  unsigned int remainder;
  unsigned int boolPadding;
} VS_SYM_CTX;


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
int DoRSAKeyGen(int nKeySize, A_RSA_KEY* pRSAPrivKey,A_RSA_KEY* pRSAPubKey);

/*  Incremental functions to operate the data using RSA key */

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
int RSADataBegin (A_RSA_KEY* RSAKey, void** pvoidContext);

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
int RSADataUpdate 
(
    void* pvoidContext, 
	unsigned char* plainText, 
	unsigned int plainTextSize, 
	unsigned char* encText, 
	unsigned int* encTextSize
);

/*********************************************************************************************************
 * Function RSADataEnd ()
 * This function is called after (multiple) call(s) to RSADataUpdate(). 
 *
 * parameters : pvoidContext : the RSA operation context, it is allocated in RSADataBegin()
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int RSADataEnd ( void* pvoidContext );


/* Incremental functions to hash data using either SHA, MD2, MD5 algorithms */

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
int	HashBegin (int nAlgId, void** o_ppvoidContext );

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
int HashData (int nAlgId, void* pvoidContext, unsigned char* inData, unsigned int inDataSize);


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
int HashEnd (int nAlgId, void* pvoidContext, unsigned char* outHashVal, int bufferSize);

/*  Incremental functions to encrypt the data using symmetric key algorithms viz. RC2, RC4 */
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
int SymEncryptDataBegin (int i_nAlgId, ITEM* i_pRCKey, int i_nEffectiveKeyLen, void** o_ppvoidContext, unsigned char *initVector, unsigned int toPad);


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
	unsigned int *outDataSize
);

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
int SymEncryptDataEnd (void* i_pvoidContext, unsigned char* outData, unsigned int *outDataSize);

/*  Incremental functions to decrypt the data using symmetric key algorithms viz. RC2, RC4 */
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
 *              toPad : 1 - BSafeLite will strip off padding/0 BsafeLite ignores any padding
 *
 * outputs:     o_ppvoidContext : the decryption context, it is allocated within this function and needs to 
 *                                be passed in future calls to SymDecryptDataUpdate and a call 
 *                                to SymDecryptDataEndData (where it is freed).
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int SymDecryptDataBegin (int i_nAlgId, ITEM* i_pRCKey, int i_nEffectiveKeyLen, void** o_ppvoidContext, unsigned char *initVector, unsigned int toPad);

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
	unsigned int *outDataSize
);

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
int SymDecryptDataEnd 
(
	void* i_pvoidContext,
	unsigned char* outData, 
	unsigned int *outDataSize	
);



/* Function to generate random numbers */
/*********************************************************************************************************
 * Function GenerateRandomBlock ()
 * This function is called to generate a random string of bytes of the specified length
 *
 * parameters : in_pcharRandBlock : the pointer to memory
 *              in_pRandBlockLen : contains the size random data to be generated
 *
 * outputs    : in_pcharRandBlock : the random number
 *            
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
int GenerateRandomBlock(unsigned char* in_pcharRandBlock, unsigned int in_nRandBlockLen);


/* Function to zero out the memory */
/*********************************************************************************************************
 * Function EraseMemory ()
 * This function is called to zero out a block of memory. the implementation of this function
 * can later be changed to erase the memory securely as per standards.
 *
 * parameters : dwMemoryBlockSize : the length of the byte array
 *              pbyteMemoryBlock : the pointer to the block of memory to be zeroed
 *
 * 
 * Return values : 0 : success
 *                 -1: on error.
 *********************************************************************************************************/
unsigned int EraseMemory ( unsigned int dwMemoryBlockSize, PBYTE pbyteMemoryBlock );

#endif