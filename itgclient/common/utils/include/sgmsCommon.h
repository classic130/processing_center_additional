#ifndef _SGMSCOMMON_
#define _SGMSCOMMON_

#include <windows.h>
#include <wincrypt.h>
#include <time.h>
#include "integrate.h"
#include "simder_all.h"
#include "certinfo.h"

#define		RSA_MIN_PAD_LEN						11


void _Base64Encode(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);


void _Base64EncodeCRLF(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);

void _Base64EncodeLF(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);

void _Base64EncodeCR(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);

void _Base64EncodeNOLF(char* pInput,
				   unsigned int dwInputSize,
				   char* pOutput,
				   unsigned int * dwOutputSize);



void reverse(unsigned int size,
			 unsigned char *input);

void _Base64Decode(PCHAR pInput,
				   DWORD dwInputSize,
				   PCHAR pOutput,
				   DWORD * dwOutputSize);

BOOL _decode(short input,
			 DWORD *output);

PCHAR	StripSpace(PCHAR input);

/////// BSAFE CRYPTO

int VSBSafeEncrypt(int i_nAlgId,
				   ITEM* i_pRCKey,
				   int i_nEffectiveKeyLen, // i_nEffectiveKeyLen is in bits.
				   unsigned char *initVector, 
				   unsigned char *pbData,
				   unsigned int *dwDataLen,
				   unsigned int dwBufLen
				   );

// nKeySize is in Bytes
int VSBSafeGenSessionKey(int nKeySize,
						 ITEM *i_pRCKey );

int GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO *i_CertPublicKeyInfo,
						 A_RSA_KEY* o_pTheKey);

int VSBSafePublicKeyEncrypt(CERT_PUBLIC_KEY_INFO *i_CertPublicKeyInfo,
							unsigned char *pbSymKey,
							unsigned int dwSymKey,
							unsigned char **pbEncData,
							unsigned int *dwEncData);

int PadDataForEncryption
(
	A_RSA_KEY			RSA_Enc_PublicKey,
	const BYTE*			i_cpbyteData,
	const DWORD			i_cdwDataLen,
	BYTE**				o_ppbytePaddedData,
	DWORD*				o_pdwPaddedDataLen
);


BYTE* _WideToMultiByte(BSTR szwcInputString, DWORD *dwLength);
LPSTR  _WideToMultiString(BSTR szwcInputString);
BSTR  _MultiToWideString(LPSTR szInputString);

PCHAR	URLDecode(PCHAR input);
BOOL	URLEncode(PCHAR szInput, PCHAR szOutput);


////Server
int
AnsiToUnicodeString(
    LPSTR pAnsi,
    LPWSTR pUnicode,
    DWORD StringLength
    );


int
UnicodeToAnsiString(
    LPWSTR pUnicode,
    LPSTR pAnsi,
    DWORD StringLength
    );


LPWSTR
AllocateUnicodeString(
    LPSTR  pAnsiString
    );

void
FreeUnicodeString(
    LPWSTR  pUnicodeString
    );

int Hascii2Bin(PCHAR hasc,
			   PCHAR *OutBuf,
			   int *OutLen);

void getRandomString(BYTE *pbData,
					 int len);




#endif // _SGMSCOMMON_