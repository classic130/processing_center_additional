#ifndef __VS_P12_HELPER_H__
#define	__VS_P12_HELPER_H__

#include <comdef.h>
#include "simder_all.h"


typedef struct _HMACCtxt {
	int nHashAlg;
	DWORD dwKeySize;
	BYTE* pbyteKey;
	BYTE* pbyteDigest;
	void* pvoidDigestCtxt;
} HMACCtxt;


static unsigned char odd_parity[256]={
  1,  1,  2,  2,  4,  4,  7,  7,  8,  8, 11, 11, 13, 13, 14, 14,
 16, 16, 19, 19, 21, 21, 22, 22, 25, 25, 26, 26, 28, 28, 31, 31,
 32, 32, 35, 35, 37, 37, 38, 38, 41, 41, 42, 42, 44, 44, 47, 47,
 49, 49, 50, 50, 52, 52, 55, 55, 56, 56, 59, 59, 61, 61, 62, 62,
 64, 64, 67, 67, 69, 69, 70, 70, 73, 73, 74, 74, 76, 76, 79, 79,
 81, 81, 82, 82, 84, 84, 87, 87, 88, 88, 91, 91, 93, 93, 94, 94,
 97, 97, 98, 98,100,100,103,103,104,104,107,107,109,109,110,110,
112,112,115,115,117,117,118,118,121,121,122,122,124,124,127,127,
128,128,131,131,133,133,134,134,137,137,138,138,140,140,143,143,
145,145,146,146,148,148,151,151,152,152,155,155,157,157,158,158,
161,161,162,162,164,164,167,167,168,168,171,171,173,173,174,174,
176,176,179,179,181,181,182,182,185,185,186,186,188,188,191,191,
193,193,194,194,196,196,199,199,200,200,203,203,205,205,206,206,
208,208,211,211,213,213,214,214,217,217,218,218,220,220,223,223,
224,224,227,227,229,229,230,230,233,233,234,234,236,236,239,239,
241,241,242,242,244,244,247,247,248,248,251,251,253,253,254,254};


int HMACBegin(int i_nDigestAlg,BYTE* i_pbyteHMACKey,int i_dwHMACKeySize,void** pvoidCtxt);
int HMACData(void* i_pvoidCtxt, BYTE* i_pbyteData, DWORD i_dwDataSize);
int HMACFinal(void* i_pvoidCtxt, BYTE* o_pbyteHMACDigest);


HRESULT _DoP12KeyGen(_bstr_t& i_tbstrPassword, BYTE* i_pbyteSalt, DWORD i_dwSaltSize, DWORD i_dwIterations, BYTE i_byteID,
							BYTE* o_pbyteKey, DWORD i_dwKeySize);
HRESULT _CatToFillBuffer(BYTE* i_pbyteBuffer,DWORD i_dwBufferSize,BYTE* i_pbyteFiller,DWORD i_dwFillerSize);
HRESULT _GetHMACKey(_bstr_t& i_tbstrPassword, BYTE* i_pbyteSalt, DWORD i_dwSaltSize, DWORD i_dwIterations, 
							BYTE* o_pbyteKey, DWORD* o_pdwKeySize);
HRESULT _GetHMACDigest(BYTE* i_pbyteAuthSafe,DWORD i_dwAuthSafeSize, DWORD i_dwDigestAlg, BYTE* i_pbyteHMACKey,DWORD i_dwHMACKeySize, BYTE* o_pbyteHMACDigest);
HRESULT _SetParity(BYTE* i_pbyteKey, DWORD i_dwKeySize);


DWORD		CreateP8
(
	A_RSA_KEY			i_RSA_PrivateKey,
	A_RSA_KEY			i_RSA_PublicKey,
	CSequence*			o_pCSeqP8
);


DWORD		PutKeyInSequence
(
	A_PKCS_RSA_PRIVATE_KEY			i_sRSA_PrivateKey,
	CSequence*						io_pCSeqPrivateKey
);

#endif