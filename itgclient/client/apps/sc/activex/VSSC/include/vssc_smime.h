///////////VSSC_SMIME.h/////////////////
#ifndef VSSC_SMIME_H
#define VSSC_SMIME_H




HRESULT  CreatePKCS7(VSSC_SIGN_MESSAGE_PARA *pvsscSignMsgPara,char **pszSignedData64);

HRESULT MsgHashToBeSigned(VSSC_HASH_MESSAGE_PARA   *pMsgHashParam,
					  AUTHATTRIB *paaAuthAttrib,BYTE **pbHashData,DWORD *dwHashLen);

HRESULT  VSSC_VerifyMessageSignature(
									 MSGINFO MsgInfo,
									 CMsg *pCMsg,
									 VS_PKCS7_INFO *vsspiPKCS7InfoS
									 );
HRESULT  VSSC_DecryptMessage(IVSPTA *pVSPTA,DWORD MsgType,
							 CMsg *pCMsg,VS_PKCS7_INFO *vsspiPKCS7Info);



///////bSafeLite////////////////
HRESULT  VSSC_SymDecryptData(int i_AlgID,BYTE* i_pbyteKey, DWORD dwKeyLen, BYTE* i_pbyteIV, BYTE* i_pbyteEncBlob, DWORD i_dwEncBlobSize, BYTE* o_pbyteDecBlob, DWORD* o_pdwDecP12BlobSize);

HRESULT  VSSC_DecryptSignature(int i_AlgID, PCERT_INFO   pSignerCertInfo, BYTE *pbSignature, DWORD dwSignature, BYTE **pbHash,
						  DWORD *dwHash);	

HRESULT	 UnPadDataForVerify(const BYTE*	i_cpbyteData,const DWORD i_cdwDataLen,
								BYTE**	o_ppbyteUnPaddedData,DWORD*	o_pdwUnPaddedDataLen);

HRESULT ParsePKCS7(MSGINFO MsgInfo ,BOOL bUseSimder, VS_PKCS7_INFO *vsspiPKCS7Info);

///////New mime Engine
HRESULT VSSC_CreateSignedMessage(IVSPTA *pVSPTA,CMsg *pMsg);

HRESULT VSSC_CreateEncryptedMessage(CMsg *pMsg); 




#endif