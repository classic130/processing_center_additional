#ifndef CRYPTSUP_H
#define CRYPTSUP_H


#define MY_ENCODING_TYPE   (PKCS_7_ASN_ENCODING | CRYPT_ASN_ENCODING)

typedef struct _DECRYPT_CONTEXT
{
	HCRYPTMSG hMsg;
	BOOL bControlCalled;	// indicates whether CryptMsgControl() has been called
	HCRYPTPROV hCryptProv;
	PCCERT_CONTEXT pCertContext;
	HCERTSTORE hCertStore;
}DECRYPT_CONTEXT, *PDECRYPT_CONTEXT;


BOOL InitiateDecrypt(PDECRYPT_CONTEXT);
STDMETHODIMP DecryptStart(PCRYPT_DECRYPT_MESSAGE_PARA ,ULONG *, 
						  PCMSG_STREAM_INFO, ULONG *);
STDMETHODIMP DecryptUpdate(ULONG ,BYTE *, ULONG, ULONG *);
STDMETHODIMP DecryptEnd(ULONG , BYTE *, ULONG , ULONG *);

BOOL VerifySignatureAndEncryptHash(PBYTE, DWORD, PBYTE, DWORD, 
								   PBYTE*, DWORD*);

BOOL WINAPI StreamOutputCallback(const void*, BYTE*, DWORD, BOOL);

LPSTR _WideToMultiString(BSTR);

#endif	// CRYPTSUP_H