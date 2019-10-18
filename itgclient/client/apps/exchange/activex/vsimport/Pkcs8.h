// Pkcs8.h: interface for the CPkcs8 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PKCS8_H__DBFFD862_7E46_11D2_830F_0060B0B32E16__INCLUDED_)
#define AFX_PKCS8_H__DBFFD862_7E46_11D2_830F_0060B0B32E16__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <wincrypt.h>
#include "Mdefs.h"

class CPkcs8  
{
public:
	CPkcs8();
	virtual ~CPkcs8();

	CPkcs8(LPSTR	szBase64PKCS8) ;

	BOOL generatePRIVATEKEYBLOB(CRYPT_PRIVATEKEYBLOB *p_PrivateKeyBlob) ;

	MY_PRIVATEKEYBLOB	m_MyPrivateKeyBlob ;

private :
	void	_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString) ;
	void	_Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize) ;
	void	_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize) ;
	LPSTR	_WideToMultiString(BSTR szwcInputString) ;
	BSTR	_MultiToWideString(LPSTR szInputString) ;
	BOOL	_GetASNInfo(PBYTE input, BYTE *type, DWORD *length, DWORD *numberOfLengthBytes) ;
	BOOL	_myCryptDecodeObject(LPSTR szOID, PCRYPT_MYDER_BLOB pMyDERBlob, PBYTE pOutputStruct) ;
	void	_Reverse(DWORD dwStream, PBYTE pbStream) ;
	BOOL	_decode(short input, DWORD *output) ;

	BOOL	m_bBreakPKCS8 ;
	DWORD	m_cbPRIVATEKEYBLOB ;
	PBYTE	m_pbPRIVATEKEYBLOB ;
};

#endif // !defined(AFX_PKCS8_H__DBFFD862_7E46_11D2_830F_0060B0B32E16__INCLUDED_)
