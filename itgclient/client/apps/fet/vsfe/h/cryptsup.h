#ifndef CRYPTSUP_H
#define CRYPTSUP_H


typedef struct _DECRYPT_CONTEXT
{
	HCRYPTMSG hMsg;
	BOOL bControlCalled;	// indicates whether CryptMsgControl() has been called
	HCRYPTPROV hCryptProv;
	PCCERT_CONTEXT pCertContext;
	HCERTSTORE hCertStore;
}DECRYPT_CONTEXT, *PDECRYPT_CONTEXT;


typedef struct _SIGN_CONTEXT
{
	HCRYPTMSG hMsg;
	HCRYPTPROV hCryptProv;
}SIGN_CONTEXT, *PSIGN_CONTEXT;


enum InitStatus
{
	OKAY,		// initialization of Encryption/Signing parameters success
	FAILED,		// initialization failed
	RENEW,		// cert is absent/expired it is being obtained/renewed
	NO_MATCHES
};

enum EncryptStatus
{
	ROOT_DIR,	// trying to encrypt a root dir "c:\", "d:\" directory, this is not allowed
	SYS_DIR,	// trying to encrypt a system directory, this is not allowed
	IN_SYS_DIR,	// trying to encrypt a file/directory in the system dir, not allowed
	HIDDEN,		// attribute 'hidden'
	READONLY,	//		     'read only'
	SYSTEM,		//			 'system'
	TEMPORARY,	//			 'temporary'
	SUCCESS,	// encryption is allowed
	CANCEL,		// the entire encryption operation is cancelled
	SKIP,		// skip the encryption for this file/dir
	CRYPTFAIL	// crypto operation failed
};

enum DecryptStatus
{
	DECR_OK,	 // decryption (and/or signature verification) succeeded
	DECR_FAIL,	 // failed
	DECR_CANCEL, // the operation was cancelled by the user
	DECR_SKIP    // decryption of one file was skipped by user
};

enum SigStatus
{
	NO_SIG,			// no signature present in file
	SIG_VALID,		// signature is valid
	SIG_INVALID,	// signature is invalid
	SIG_GEN_FAIL,	// some crypto operation failed or out of memory or file op error
	SIG_CANCEL		// the verification was cancelled by the user
};

enum CopyError
{
	badparams,
	createdirerr,
	remdirerr,
	fferror,
	moveerr,
	skip,
	cancel,
	okay
};


STDMETHODIMP EncryptStart(PCRYPT_ENCRYPT_MESSAGE_PARA, PCMSG_STREAM_INFO, 
						  ULONG *, PCERT_CONTEXT, ULONG *);
STDMETHODIMP EncryptUpdate(ULONG, BYTE *, ULONG, ULONG *);
STDMETHODIMP EncryptEnd(ULONG, BYTE *, ULONG , ULONG *);

STDMETHODIMP SignStart(PCCERT_CONTEXT, LPSTR, PSIGN_CONTEXT*, 
					   ULONG *);
STDMETHODIMP SignUpdate(PSIGN_CONTEXT, BYTE *, ULONG, ULONG *);
STDMETHODIMP SignEnd(PSIGN_CONTEXT, BYTE *, ULONG, ULONG *,
					 BYTE **, ULONG *);

BOOL InitiateDecrypt(PDECRYPT_CONTEXT);
STDMETHODIMP DecryptStart(PCRYPT_DECRYPT_MESSAGE_PARA ,ULONG *, 
						  PCMSG_STREAM_INFO, ULONG *);
STDMETHODIMP DecryptUpdate(ULONG ,BYTE *, ULONG, ULONG *);
STDMETHODIMP DecryptEnd(ULONG , BYTE *, ULONG , ULONG *);

InitStatus InitEncryptParams(PCRYPT_ENCRYPT_MESSAGE_PARA);
BOOL DeinitEncryptParams(PCRYPT_ENCRYPT_MESSAGE_PARA);

CopyError EncryptAll(PCRYPT_ENCRYPT_MESSAGE_PARA, PTCHAR, PTCHAR);
BOOL EncryptDroppedItems(HWND, HDROP, const PTCHAR);
EncryptStatus EncryptAndSignFile(PCRYPT_ENCRYPT_MESSAGE_PARA, LPCSTR, LPCSTR);
EncryptStatus EncryptFile(PCRYPT_ENCRYPT_MESSAGE_PARA, LPCSTR, LPCSTR);
BOOL EncrDecrFileUsingPasswd(LPCTSTR, LPCTSTR, BOOL);

DecryptStatus DoDecrypt(LPCTSTR szSourceFile, LPCTSTR szDestFile);
BOOL SignUpdateFile(LPCSTR);
DWORD SignFile(LPCSTR, PBYTE *);

DecryptStatus DecryptAll(LPCTSTR);
DecryptStatus DecryptAndVerifyFile(LPCTSTR, LPCTSTR, BOOL);
SigStatus VerifySignature(LPCSTR);
BOOL VerifyDetachedSig(PBYTE, DWORD, PBYTE, DWORD);
BOOL VerifySigList(VOID);
BOOL VerifyCert(PCCERT_CONTEXT);

BOOL VerifyPassword(VOID);
BOOL VerifyDecryptDataFile(VOID);

DWORD HashData(LPBYTE, DWORD, PBYTE *);

BOOL WINAPI StreamOutputCallback(const void*, BYTE*, DWORD, BOOL);

#endif	// CRYPTSUP_H