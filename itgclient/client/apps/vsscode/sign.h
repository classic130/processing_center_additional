#ifndef __VS_SIGN_
#define __VS_SIGN_

HRESULT SignFile(LPTimeSettings i_pTimeSettings);
HRESULT OnlySignFile(LPTimeSettings i_pTimeSettings);
HRESULT GetSignatureFileName(_bstr_t& i_bstrImageFileName, const _bstr_t& i_bstrCodeType, _bstr_t& o_bstrSignFile);
HRESULT GetPKCS7Length(PBYTE i_pbData, DWORD i_dwData, LPDWORD o_pdwPKCS7Size);

#endif // __VS_SIGN_