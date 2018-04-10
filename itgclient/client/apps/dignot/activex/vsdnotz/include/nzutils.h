#ifndef __NZUTILS_H
#define __NZUTILS_H
#include "dnzuistructs.h"

// Flags used for revocation checking and chain validation
#define	REV_NONE		0x00000000
#define	REV_CRL			0x00000001
#define	REV_CRL_ALL		0x00000002
#define	REV_OCSP		0x00000004
#define CHAIN_VALIDATE	0x00000008


#define MY_ENCODING_TYPE (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)

#define VS_MAIN_KEY				(TEXT("Software\\VeriSign, Inc."))
#define NZ_MAIN_KEY				(TEXT("Software\\VeriSign, Inc.\\Notarization"))
#define NZ_LOG_ERROR			(TEXT("LogError"))


// Error strings returned by our Notarization server in the status information. These will be mapped to user
// friendly error strings by the client. Note: these strings will have to sync with the server's strings
// Nov, 07 2001
#define		NZERR_ALG				"unrecognized or unsupported Algorithm Identifier"
#define		NZERR_WRONG_FORMAT		"the data submitted has the wrong format"
#define		NZERR_TIME_UNAVAIL		"the TSA time source is not available"
#define		NZERR_POL_INVALID		"the requested TSA policy is not supported by the TSA"
#define		NZERR_SIG_FAIL			"signature verification failed for the request"
#define		NZERR_CERT_REVOKED		"the requestor certificate has been revoked"
#define		NZERR_CERT_EXPIRED		"the requestor certificate is expired"
#define		NZERR_CERT_INVALID		"the requestor certificate is invalid"
#define		NZERR_CERT_ABSENT		"the requestor certificate is not found by the server"
#define		NZERR_NO_ACCT			"the requestor does not have a timstamp account"
#define		NZERR_ACCT_INVALID		"the account status for the requestor is invalid"
#define		NZERR_LIMIT				"the requestor account has reached the authorized limit"
#define		NZERR_GENERAL			"failure code from server"


#define FREE_CERT_CTXT(pCertCtxt){\
	if(pCertCtxt)\
	{\
		CertFreeCertificateContext(pCertCtxt);\
		pCertCtxt = NULL;\
	}\
}

#define FREE_CRL_CTXT(pCrlCtxt){\
	if(pCrlCtxt)\
	{\
		CertFreeCRLContext(pCrlCtxt);\
		pCrlCtxt = NULL;\
	}\
}


// This is the structure which gets passed to the function that does the certificate chain
// validation and verification.
typedef struct
{
	HRESULT hr;					// Result of the verification operation
	_bstr_t bstrRevInfo;			// Location of CRL
	DWORD dwValidationFlags;	// What type of chain validation and revocation to perform

}VerifyInfo, *LPVerifyInfo;


VOID _LogErrorMsg(LPCTSTR i_pErrLocation, LPCTSTR i_pErrDesc, LPCTSTR i_pErrParam, DWORD i_dwErrCode);
VOID _ShowErrorMsg();
HRESULT _CreateTempFile(_bstr_t* o_pbstrTempFilePath);
HRESULT _GetSelIDName(IVSPTA* i_pVSPta, _bstr_t* o_pbstrCertName);
HRESULT _GetCertCN(PCERT_INFO i_pCertInfo, _bstr_t* o_pbstrCertName);
HRESULT _LoadStringW(HINSTANCE i_hInst, DWORD i_dwLangId, short i_nStringID, WCHAR** o_wstrOutBuff);
DWORD _GetDefaultLangID();
BOOL _IsLangSupported(DWORD i_dwLangID);
HRESULT _ParseServerPath(const _bstr_t& i_bstrServerPath, _bstr_t* o_pbstrServerName, _bstr_t* o_pbstrServerObject, LPDWORD o_pdwPortNum);
HRESULT _GetFormattedTime(const PBYTE i_pbGeneralizedTime, const DWORD i_dwGeneralizedTime, SYSTEMTIME *NzFormattedSysTime);
HRESULT _HashDocument(const _bstr_t& i_bstrDocument, const _bstr_t& i_bstrAlgID, const _bstr_t& i_bstrUserAgent, PBYTE* o_pbHashVal, LPDWORD o_pdwHashValSize);
HRESULT _VerifyAttachedSignature(const PBYTE i_pbSignature, const DWORD i_dwSignature, const DWORD i_dwValidateFlags, const _bstr_t& i_bstrRevocationInfo, PBYTE *o_pbDecodedMsg, DWORD *o_pdwDecodedMsg, _bstr_t* o_pbstrCertCN);
HRESULT _DoCertValidation(HCERTSTORE i_hCertStore, BOOL i_bIsRootStore, PCCERT_CONTEXT i_pCertToValidate, DWORD i_dwFlags, BOOL i_bChainValidate, _bstr_t& i_bstrRevInfo);
HRESULT _DoCRLCheck(const HCERTSTORE i_hCertStore, PCCERT_CONTEXT i_pIssuerCertCtxt, PCCERT_CONTEXT i_pSubjectCertCtxt, _bstr_t& i_bstrRevInfo);
PCCERT_CONTEXT WINAPI _GetSignerCertificate(void *pvVerifyArg, DWORD dwCertEncodingType, PCERT_INFO pSignerId, HCERTSTORE hMsgCertStore);
HRESULT _AddCertToStore(LPCTSTR i_pStore, const BYTE* i_pbCertificate, const DWORD i_dwCertLen);
VOID _Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, LPDWORD dwOutputSize);
VOID _Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, LPDWORD dwOutputSize);
BOOL _decode(short input, DWORD *output);
PUICTXT _CreateUIContext();
HRESULT _CopyUIContext(PUICTXT o_pUICtxtDest, PUICTXT i_pUICtxtSrc);
void _FreeUIContext(PUICTXT i_pUICtxt);
void _FreeUIElements(PUICTXT i_pUICtxt);
HRESULT _GetBitmap(_bstr_t& tbstrBmpUrl, HBITMAP* o_phBitmap);
HRESULT _FreeBitmap(HBITMAP i_hBitmap);
int _GetCharset(WORD wLangID);
BOOL _IsDataTextOnly(LCID locale, BYTE* pbData, DWORD cbData);
HRESULT _FormatDate(LCID locale, SYSTEMTIME st, _bstr_t* o_ptbstrFormattedDate);
HRESULT _FormatTime(LCID locale, SYSTEMTIME st, _bstr_t* o_ptbstrFormattedTime);
VOID LaunchApp(const _bstr_t& i_bstrApp);
_bstr_t _MapFailInfo(LPNzDetails i_pNotzDetails);
HRESULT _SelectOpenOrSaveFile(int selectType, HWND hParent, UINT idOFTitle, char* pcszFilter, int dwFilterLength, _bstr_t i_tbstrInitialFileName, _bstr_t* o_ptbstrSelFile);
VOID reverseit(PBYTE pbData, DWORD dwData);
BOOL IsBase64Encoded(LPBYTE pbData, DWORD dwData);
HRESULT GetReceiptFileName(const _bstr_t& i_bstrFileToNotarize, _bstr_t* o_pbstrReceiptFileName);
HRESULT _GetDocumentExtension(_bstr_t i_tbstrDocument, _bstr_t* o_tbstrExtension);
bool _IsSourceAndDestinationSame(_bstr_t  m_tbstrDocument, _bstr_t tbstrDocumentDestination);
HRESULT _GetDispProperty(IDispatch* pDisp, UINT uIDName, VARTYPE vt, LPVARIANT pVar);
HRESULT _GetProperty(IDispatch* pDisp, UINT uIDName, VARTYPE vt, LPVARIANT pVar);
HRESULT _GetDISPID(IDispatch* pDisp, UINT uIDName, DISPID* pDispId);
BOOL	myStrStr(char *str, char *pattern);

#endif	// __NZUTILS_H