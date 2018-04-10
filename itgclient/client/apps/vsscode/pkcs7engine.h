#ifndef __VS_PKCS7_ENGINE_
#define __VS_PKCS7_ENGINE_


#define CHECK_TREE_NODE(pNode, NodeType){\
	if(pNode == NULL)\
	{\
		hr = E_VSSCODE_INVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER == NULL)\
	{\
		hr = E_VSSCODE_INVALIDNODE;\
		break;\
	}\
	if(pNode->currentBaseDER->Type != NodeType)\
	{\
		hr = E_VSSCODE_INVALIDNODE;\
		break;\
	}\
}


typedef struct
{
	PBYTE pbCertList;		// all the certificates that are present in the signature
	DWORD dwCertList;
	
	PBYTE pbCrlList;		// all the CRL's present in the signature
	DWORD dwCrlList;
	
	PBYTE pbSignerInfo;		// all the signer info's present in the signature
	DWORD dwSignerInfo;

public:
	VOID Initialize();
	VOID Clear();

}PKCS7SignInfo, *LPPKCS7SignInfo;


typedef struct tagMyCertInfo
{
	PBYTE pbIssuerDN;
	DWORD dwIssuerDN;

	PBYTE pbSerialNumber;
	DWORD dwSerialNumber;

	struct tagMyCertInfo* pNext;

}MyCertInfo, *LPMyCertInfo;


HRESULT ParsePKCS7SignedData(const PBYTE i_pbPKCS7Data, const DWORD i_dwPKCS7Data, LPPKCS7SignInfo pPkcs7SignInfo);
HRESULT CreateDocSisPKCS7Sig(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
							 const _bstr_t& i_bstrHashAlg, PBYTE* o_ppbDocSisPkcs7Sig, LPDWORD o_pdwDocSisPkcs7Sig);
HRESULT GetCertList(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
					PBYTE* o_ppbCertList, LPDWORD o_pdwCertList);
HRESULT GetSignerInfo(PBYTE i_pbSignerInfo, DWORD i_dwSignerInfo, LPMyCertInfo* o_ppCertInfo);

HRESULT GetSignerInfoList(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
						  PBYTE* o_ppbSignerInfoList, LPDWORD o_pdwSignerInfoList);
HRESULT ParseSignerInfo(PBYTE i_pbSignerDataDerBlob, DWORD i_dwSignerDataDerBlob, LPMyCertInfo* o_ppCertInfo);
HRESULT ParseX509Cert(PBYTE i_pbCertificateDerBlob, DWORD i_dwCertificateDerBlob, LPMyCertInfo* o_ppCertInfo);

#endif	//	__VS_PKCS7_ENGINE_