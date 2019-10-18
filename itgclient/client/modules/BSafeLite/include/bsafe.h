/* Copyright (C) RSA Data Security, Inc. created 1990.  This is an
   unpublished work protected as such under copyright law.  This work
   contains proprietary, confidential, and trade secret information of
   RSA Data Security, Inc.  Use, disclosure or reproduction without the
   express written authorization of RSA Data Security, Inc. is
   prohibited.
 */

#ifndef _BSAFE_H_
#define _BSAFE_H_ 1

#ifndef CALL_CONV
#define CALL_CONV
#endif

#include "atypes.h"

#ifndef _STD_ALLOC_FUNCS_
#define _STD_ALLOC_FUNCS_
#endif

#ifndef _STD_MEM_FUNCS_
#define _STD_MEM_FUNCS_
#endif
#include "stdlibrf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BE_ALGORITHM_ALREADY_SET 0x0200
#define BE_ALGORITHM_INFO 0x0201
#define BE_ALGORITHM_NOT_INITIALIZED 0x0202
#define BE_ALGORITHM_NOT_SET 0x0203
#define BE_ALGORITHM_OBJ 0x0204
#define BE_ALG_OPERATION_UNKNOWN 0x0205
#define BE_ALLOC 0x0206
#define BE_CANCEL 0x0207
#define BE_DATA 0x0208
#define BE_EXPONENT_EVEN 0x0209
#define BE_EXPONENT_LEN 0x020a
#define BE_HARDWARE 0x020b
#define BE_INPUT_DATA 0x020c
#define BE_INPUT_LEN 0x020d
#define BE_KEY_ALREADY_SET 0x020e
#define BE_KEY_INFO 0x020f
#define BE_KEY_LEN 0x0210
#define BE_KEY_NOT_SET 0x0211
#define BE_KEY_OBJ 0x0212
#define BE_KEY_OPERATION_UNKNOWN 0x0213
#define BE_MEMORY_OBJ 0x0214
#define BE_MODULUS_LEN 0x0215
#define BE_NOT_INITIALIZED 0x0216
#define BE_NOT_SUPPORTED 0x0217
#define BE_OUTPUT_LEN 0x0218
#define BE_OVER_32K 0x0219
#define BE_RANDOM_NOT_INITIALIZED 0x021a
#define BE_RANDOM_OBJ 0x021b
#define BE_SIGNATURE 0x021c
#define BE_WRONG_ALGORITHM_INFO 0x021d
#define BE_WRONG_KEY_INFO 0x021e
#define BE_INPUT_COUNT 0x021f
#define BE_OUTPUT_COUNT 0x0220
#define BE_METHOD_NOT_IN_CHOOSER 0x221
#define BE_KEY_WEAK 0x222

typedef POINTER B_KEY_OBJ;
typedef POINTER B_ALGORITHM_OBJ;

typedef int (CALL_CONV *B_INFO_TYPE) PROTO_LIST ((POINTER *));

#ifndef A_MIN_DIGEST_LEN
#define A_MIN_DIGEST_LEN             16
#endif

#ifndef A_MAX_DIGEST_LEN
#define A_MAX_DIGEST_LEN             32
#endif

#ifndef _BUILD_LIBRARY_
typedef char B_ALGORITHM_METHOD;
typedef B_ALGORITHM_METHOD **B_ALGORITHM_CHOOSER;
#endif

/* Version information.
 */
extern char * CALL_CONV BSAFE_VERSION;

/* The key object.
 */
int CALL_CONV B_CreateKeyObject PROTO_LIST ((B_KEY_OBJ *));
void CALL_CONV B_DestroyKeyObject PROTO_LIST ((B_KEY_OBJ *));
int CALL_CONV B_SetKeyInfo PROTO_LIST ((B_KEY_OBJ, B_INFO_TYPE, POINTER));
int CALL_CONV B_GetKeyInfo PROTO_LIST ((POINTER *, B_KEY_OBJ, B_INFO_TYPE));

/* The algorithm object.
 */
int CALL_CONV B_CreateAlgorithmObject PROTO_LIST ((B_ALGORITHM_OBJ *));
void CALL_CONV B_DestroyAlgorithmObject PROTO_LIST ((B_ALGORITHM_OBJ *));
int CALL_CONV B_SetAlgorithmInfo PROTO_LIST
  ((B_ALGORITHM_OBJ, B_INFO_TYPE, POINTER));
int CALL_CONV B_GetAlgorithmInfo PROTO_LIST
  ((POINTER *, B_ALGORITHM_OBJ, B_INFO_TYPE));

unsigned int B_IntegerBits PROTO_LIST ((unsigned char *, unsigned int));

/* Algorithm operations.
 */
int CALL_CONV B_RandomInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_RandomUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, A_SURRENDER_CTX *));
int CALL_CONV B_GenerateRandomBytes PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, A_SURRENDER_CTX *));

int CALL_CONV B_DigestInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_DigestUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, A_SURRENDER_CTX *));
int CALL_CONV B_DigestFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    A_SURRENDER_CTX *));

int CALL_CONV B_EncryptInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_EncryptUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int, B_ALGORITHM_OBJ, A_SURRENDER_CTX *));
int CALL_CONV B_EncryptFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    B_ALGORITHM_OBJ, A_SURRENDER_CTX *));

int CALL_CONV B_DecryptInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_DecryptUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int, B_ALGORITHM_OBJ, A_SURRENDER_CTX *));
int CALL_CONV B_DecryptFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    B_ALGORITHM_OBJ, A_SURRENDER_CTX *));

int CALL_CONV B_EncodeInit PROTO_LIST ((B_ALGORITHM_OBJ));
int CALL_CONV B_EncodeUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int));
int CALL_CONV B_EncodeFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int));

int CALL_CONV B_DecodeInit PROTO_LIST ((B_ALGORITHM_OBJ));
int CALL_CONV B_DecodeUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int));
int CALL_CONV B_DecodeFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int));

int CALL_CONV B_SignInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_SignUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, A_SURRENDER_CTX *));
int CALL_CONV B_SignFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    B_ALGORITHM_OBJ, A_SURRENDER_CTX *));

int CALL_CONV B_VerifyInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_VerifyUpdate PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, A_SURRENDER_CTX *));
int CALL_CONV B_VerifyFinal PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int, B_ALGORITHM_OBJ,
    A_SURRENDER_CTX *));

int CALL_CONV B_KeyAgreeInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_KeyAgreePhase1 PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    B_ALGORITHM_OBJ, A_SURRENDER_CTX *));
int CALL_CONV B_KeyAgreePhase2 PROTO_LIST
  ((B_ALGORITHM_OBJ, unsigned char *, unsigned int *, unsigned int,
    unsigned char *, unsigned int, A_SURRENDER_CTX *));
 
int CALL_CONV B_GenerateInit PROTO_LIST
  ((B_ALGORITHM_OBJ, B_ALGORITHM_CHOOSER, A_SURRENDER_CTX *));
int CALL_CONV B_GenerateKeypair PROTO_LIST
  ((B_ALGORITHM_OBJ, B_KEY_OBJ, B_KEY_OBJ, B_ALGORITHM_OBJ,
    A_SURRENDER_CTX *));
int CALL_CONV B_GenerateParameters PROTO_LIST
  ((B_ALGORITHM_OBJ, B_ALGORITHM_OBJ, B_ALGORITHM_OBJ, A_SURRENDER_CTX *));


/* Information for BSAFE 1.x-compatible encryption algorithms.
 */
#define B_BSAFE1_PAD 1
#define B_BSAFE1_PAD_CHECKSUM 2
#define B_BSAFE1_RAW 3

typedef struct {
  int encryptionType;                /* encryption type: B_BSAFE1_PAD, etc. */
} B_BSAFE1_ENCRYPTION_PARAMS;

typedef struct {
  unsigned char *key;                              /* pointer to 8-byte key */
  unsigned int effectiveKeyBits;                     /* effective key length */
} B_RC2_BSAFE1_PARAMS_KEY;

/* Information for password-based encryption (PBE) algorithms.
 */
typedef struct {
  unsigned char *salt;                                        /* salt value */
  unsigned int iterationCount;                           /* iteration count */
} B_PBE_PARAMS;

typedef struct {
  unsigned int effectiveKeyBits;                     /* effective key length */
  unsigned char *salt;                                        /* salt value */
  unsigned int iterationCount;                           /* iteration count */
} B_RC2_PBE_PARAMS;

/* Information for MAC algorithm.
 */
typedef struct {
  unsigned int macLen;                               /* length of MAC value */
} B_MAC_PARAMS;

/* Information for RC4 with MAC algorithm.
 */
typedef struct {
  ITEM salt;                                         /* variable-length salt */
  unsigned int macLen;                        /* length to use for MAC value */
} B_RC4_WITH_MAC_PARAMS;

/* Information for DSA parameter generation
 */
typedef struct {
  unsigned int primeBits;
} B_DSA_PARAM_GEN_PARAMS;

/* How a digest algorithm is specified in a signature scheme.
 */
typedef struct {
  B_INFO_TYPE digestInfoType;
  POINTER digestInfoParams;
} B_DIGEST_SPECIFIER;

/* Information for Secret sharing algorithm
 */
typedef struct {
  unsigned int threshold;                                 /* share threshold */
} B_SECRET_SHARING_PARAMS;

/* Key Info Types.
 */
int CALL_CONV KI_8Byte PROTO_LIST ((POINTER *));
int CALL_CONV KI_24Byte PROTO_LIST ((POINTER *));
int CALL_CONV KI_DES8 PROTO_LIST ((POINTER *));
int CALL_CONV KI_DES8Strong PROTO_LIST ((POINTER *));
int CALL_CONV KI_DES24Strong PROTO_LIST ((POINTER *));
int CALL_CONV KI_DESX PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSAPrivate PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSAPrivateBER PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSAPublic PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSAPublicBER PROTO_LIST ((POINTER *));
int CALL_CONV KI_Item PROTO_LIST ((POINTER *));
int CALL_CONV KI_PKCS_RSAPrivate PROTO_LIST ((POINTER *));
int CALL_CONV KI_PKCS_RSAPrivateBER PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSA_PKIXPrivate PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSA_PKIXPrivateBER PROTO_LIST ((POINTER *));

int CALL_CONV KI_DSA_PKIXPublic PROTO_LIST ((POINTER *));
int CALL_CONV KI_DSA_PKIXPublicBER PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSAPrivate PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSAPublic PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSAPublicBER PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSA_CRT PROTO_LIST ((POINTER *));

/* Key Info Types for BSAFE 1.x Support.
 */
int CALL_CONV KI_DES_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV KI_DESX_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV KI_RC2WithBSAFE1Params PROTO_LIST ((POINTER *));
int CALL_CONV KI_RC2_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSAPrivateBSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV KI_RSAPublicBSAFE1 PROTO_LIST ((POINTER *));

/* Algorithm Info Types.
 */
int CALL_CONV AI_BSSecretSharing PROTO_LIST ((POINTER *));
int CALL_CONV AI_CBC_IV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_CBC_IV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_CBCPadPEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_EDE3_CBC_IV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_EDE3_CBCPadIV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_EDE3_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_DES_CBCPadIV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DESX_CBC_IV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DESX_CBCPadIV8 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DESX_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_DHKeyAgree PROTO_LIST ((POINTER *));
int CALL_CONV AI_DHKeyAgreeBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_DHParamGen PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSA PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSA_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSAKeyGen PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSAParamGen PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSAWithSHA1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DSAWithSHA1_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_HMAC PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2 PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2Random PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithDES_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithDES_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithRC2_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithRC2_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithRSAEncryption PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2WithRSAEncryptionBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD2_PEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5 PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5Random PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithDES_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithDES_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithRC2_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithRC2_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithRSAEncryption PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithRSAEncryptionBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithXOR PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5WithXOR_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD5_PEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_OIW_DSAWithSHA1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_OIW_DSAWithSHA1_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKIX_DSA PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKIX_DSA_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKIX_DSAWithSHA1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKIX_DSAWithSHA1_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPrivate PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPrivateBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPrivatePEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPublic PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPublicBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_PKCS_RSAPublicPEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC2_CBC PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC2_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC2_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC2_CBCPadPEM PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC4 PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC4WithMAC PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC4WithMAC_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC4_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC5_CBC PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC5_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_RFC1113Recode PROTO_LIST ((POINTER *));
int CALL_CONV AI_RSAKeyGen PROTO_LIST ((POINTER *));
int CALL_CONV AI_RSAPrivate PROTO_LIST ((POINTER *));
int CALL_CONV AI_RSAPublic PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1_BER PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1WithDES_CBCPad PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1WithDES_CBCPadBER PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1WithRSAEncryption PROTO_LIST ((POINTER *));
int CALL_CONV AI_SHA1WithRSAEncryptionBER PROTO_LIST ((POINTER *));
/* We recommend that customers use AI_X962Random_V0 instead */
/* of AI_SHA1Random because future releases of BSAFE may */
/* change the behavior of AI_SHA1Random to match the */
/* algorithm by that name in JSAFE. */
int CALL_CONV AI_SHA1Random PROTO_LIST ((POINTER *));
int CALL_CONV AI_X962Random_V0 PROTO_LIST ((POINTER *));

/* Algorithm Info Types for BSAFE 1.x Support.
 */
int CALL_CONV AI_DES_CBC_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_DESX_CBC_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_MAC PROTO_LIST ((POINTER *));
int CALL_CONV AI_MD PROTO_LIST ((POINTER *));
int CALL_CONV AI_RC2_CBC_BSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_RSAPrivateBSAFE1 PROTO_LIST ((POINTER *));
int CALL_CONV AI_RSAPublicBSAFE1 PROTO_LIST ((POINTER *));

int CALL_CONV B_EncodeDigestInfo PROTO_LIST
  ((unsigned char *, unsigned int *, unsigned int, ITEM *, unsigned char *,
    unsigned int));
int CALL_CONV B_DecodeDigestInfo PROTO_LIST
  ((ITEM *, ITEM *, unsigned char *, unsigned int));

/* Algorithm methods for use in the algorithm chooser.
 */
extern B_ALGORITHM_METHOD CALL_CONV AM_DES_CBC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DES_CBC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DES_EDE3_CBC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DES_EDE3_CBC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DESX_CBC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DESX_CBC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_DH_KEY_AGREE;
extern B_ALGORITHM_METHOD CALL_CONV AM_DH_PARAM_GEN;
extern B_ALGORITHM_METHOD CALL_CONV AM_DSA_KEY_GEN;
extern B_ALGORITHM_METHOD CALL_CONV AM_DSA_PARAM_GEN;
extern B_ALGORITHM_METHOD CALL_CONV AM_DSA_SIGN;
extern B_ALGORITHM_METHOD CALL_CONV AM_DSA_VERIFY;
extern B_ALGORITHM_METHOD CALL_CONV AM_MAC;
extern B_ALGORITHM_METHOD CALL_CONV AM_MAC_86_2X;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD2;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD2_RANDOM;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD2_RANDOM_2X;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD5;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD5_RANDOM;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD5_RANDOM_2X;
extern B_ALGORITHM_METHOD CALL_CONV AM_MD;
extern B_ALGORITHM_METHOD CALL_CONV AM_PKIX_DSA_VERIFY;
extern B_ALGORITHM_METHOD CALL_CONV AM_PKIX_DSA_SIGN;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC2_CBC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC2_CBC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_WITH_MAC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_WITH_MAC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_WITH_MAC_DECRYPT_86_2X;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC4_WITH_MAC_ENCRYPT_86_2X;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC5_CBC_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RC5_CBC_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_CRT_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_CRT_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_CRT_DECRYPT_BLIND;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_CRT_ENCRYPT_BLIND;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_DECRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_ENCRYPT;
extern B_ALGORITHM_METHOD CALL_CONV AM_RSA_KEY_GEN;
extern B_ALGORITHM_METHOD CALL_CONV AM_SHA;
extern B_ALGORITHM_METHOD CALL_CONV AM_SHA_RANDOM;

/* If the compiler doesn't support global data initialization for
   function pointers, you should compile your application with
   GLOBAL_FUNCTION_POINTERS defined as 0 and call the appropriate AM_ Init
   function for the corresponding AM_.  By default, GLOBAL_FUNCTION_POINTERS
   is defined as 1.
 */
#if !GLOBAL_FUNCTION_POINTERS
void CALL_CONV BSAFE_VERSIONInit PROTO_LIST ((void));
void CALL_CONV AM_DES_CBCDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_DES_CBCEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_DES_EDE3_CBCDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_DES_EDE3_CBCEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_DESX_CBCDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_DESX_CBCEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_DHKeyAgreeInit PROTO_LIST ((void));
void CALL_CONV AM_DHParamGenInit PROTO_LIST ((void));
void CALL_CONV AM_DSAKeyGenInit PROTO_LIST ((void));
void CALL_CONV AM_DSAParamGenInit PROTO_LIST ((void));
void CALL_CONV AM_DSASignInit PROTO_LIST ((void));
void CALL_CONV AM_DSAVerifyInit PROTO_LIST ((void));
void CALL_CONV AM_MACInit PROTO_LIST ((void));
void CALL_CONV AM_MD2Init PROTO_LIST ((void));
void CALL_CONV AM_MD2RandomInit PROTO_LIST ((void));
void CALL_CONV AM_MD5Init PROTO_LIST ((void));
void CALL_CONV AM_MD5RandomInit PROTO_LIST ((void));
void CALL_CONV AM_MDInit PROTO_LIST ((void));
void CALL_CONV AM_HMACInit PROTO_LIST ((void));
void CALL_CONV AM_RC2_CBCDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC2_CBCEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC4EncryptDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC4WithMacEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC4WithMacDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC5_CBCDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RC5_CBCEncryptInit PROTO_LIST ((void));
void CALL_CONV AM_RSA_CRTEncryptDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RSAEncryptDecryptInit PROTO_LIST ((void));
void CALL_CONV AM_RSAKeyGenInit PROTO_LIST ((void));
void CALL_CONV AM_SHAInit PROTO_LIST ((void));
void CALL_CONV AM_SHARandomInit PROTO_LIST ((void));
#endif

#ifdef __cplusplus
}
#endif

#endif /* end _BSAFE_H_ */
