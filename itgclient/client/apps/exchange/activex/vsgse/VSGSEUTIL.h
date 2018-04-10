#ifndef _VSGSE_UTIL_HEADER
#define _VSGSE_UTIL_HEADER

#include "stdafx.h"
#include "ProfAdmin.h"

void	_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString) ;
LPSTR	_WideToMultiString(BSTR szwcInputString) ;
BSTR	_MultiToWideString(LPSTR szInputString) ;


HRESULT	_GetCertCount(HCERTSTORE hCertStore, WCHAR* pwszRFC822Name,WCHAR* pwszSubjectName, WCHAR* pwszIssuerName, FRDLYNAMETYPE eType, int *nCount);
HRESULT	_SetFriendlyName(HCERTSTORE hCertStore,	PBYTE pbUserCertificate, DWORD cbUserCertificate );
HRESULT	_SetEFSCertificate(HCERTSTORE hCertStore,	PBYTE pbUserCertificate, DWORD cbUserCertificate );
HRESULT _GetCertSerNum(CRYPT_INTEGER_BLOB & i_SerialNumber, _bstr_t & o_bstrSerNum);
	
void	_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize);
BOOL	_decode(short input, DWORD *output);
HRESULT _ParseDNIntoComponents(_bstr_t& i_tbstrSubjectDN, int* o_pnNumOfDNAttrs,
								_bstr_t** o_pptbstrDNAttrs, _bstr_t** o_pptbstrDNVals);


PSID    GetMySid(void) ;
PCHAR   EncodeSid(PSID pMySid) ;

void ObjecSidEncode(BYTE *pbSid, char **szMySid);
int	 BytesToAscHex(unsigned char* pbVal, int nValSize, char *szVal);
LPVOID AllocateTokenInfoBuffer(HANDLE hToken,TOKEN_INFORMATION_CLASS InfoClass,
    DWORD *dwSize);

#ifdef	_VS_LOG_MSG_
int VSGSE_Log(BOOL bFileExist,wchar_t *format,	...);
void ShowErrorMsg(DWORD errorCode, LPSTR szExtraString);
#endif
#endif