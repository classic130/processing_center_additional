#include "stdafx.h"
#include <comutil.h>
#include <wincrypt.h>
#include "pkcs7engine.h"
#include "macros.h"
#include "vsserrs.h"
#include "basedercollection.h"
#include "basederhierarchy.h"
#include "objectidentifier.h"
#include "null.h"
#include "sequence.h"
#include "set.h"
#include "taggedvalue.h"
#include "universalinteger.h"
#include "propsht.h"
#include "util.h"


HRESULT ParsePKCS7SignedData(const PBYTE i_pbPKCS7Data, const DWORD i_dwPKCS7Data, LPPKCS7SignInfo pPkcs7SignInfo)
{
	HRESULT hr = S_OK;
	BOOL bCertPresent = FALSE, bCRLPresent = FALSE;
	DERTree* pCertPresentDTree = NULL, *pCertPresentEnumDTree = NULL;
	
	do
	{
		if(!i_pbPKCS7Data || !pPkcs7SignInfo)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_dwPKCS7Data == 0)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		pPkcs7SignInfo->Initialize();

		CBaseDERCollection cbdcSignedData(i_dwPKCS7Data, i_pbPKCS7Data);
		CBaseDERHierarchy cbdhSignedData(cbdcSignedData);

		if(cbdhSignedData.dwErrorCode)
		{
			hr = E_VSSCODE_PKCS7DECODERR;
			break;
		}

		// Point to the top level sequence
		DERTree* pSignedDataDTree = &(cbdhSignedData.m_DERTree);
		CHECK_TREE_NODE(pSignedDataDTree, SEQUENCE)

		// Point to the signed data obj id which should have a value of "1.2.840.113549.1.7.2"
		DERTree* pObjIDTree = pSignedDataDTree->rightDERTree;
		CHECK_TREE_NODE(pObjIDTree, OBJECT_IDENTIFIER)

		if(memcmp(pObjIDTree->currentBaseDER->pbData, szOID_RSA_signedData, pObjIDTree->currentBaseDER->cbData) != 0)
		{
			hr = E_VSSCODE_NOTSIGNEDATA;
			break;
		}

		// Parse the signed data
		DERTree* pTagDTree = pObjIDTree->nextDERTree;
		if(!pTagDTree || (pTagDTree->currentBaseDER->Class != CONTEXT_SPECIFIC || pTagDTree->currentBaseDER->Encoding != CONSTRUCTED
			|| pTagDTree->currentBaseDER->TagNumber != 0))
		{
			hr = E_VSSCODE_PARSESIGNDATA;
			break;
		}

		/*
			SignedData ::= SEQUENCE {
			version CMSVersion,
			digestAlgorithms DigestAlgorithmIdentifiers,
			encapContentInfo EncapsulatedContentInfo,
			certificates [0] IMPLICIT CertificateSet OPTIONAL,
			crls [1] IMPLICIT CertificateRevocationLists OPTIONAL,
			signerInfos SignerInfos }
		*/

		// Point to the signed data sequence
		DERTree* pSignedSeqDTree = pTagDTree->rightDERTree;
		CHECK_TREE_NODE(pSignedSeqDTree, SEQUENCE)

		// Point to the version number
		DERTree* pVersionDTree = pSignedSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pVersionDTree, UNIVERSAL_INTEGER)

		// Point to the digest algorithm
		DERTree* pAlgIDSetDTree = pVersionDTree->nextDERTree;
		CHECK_TREE_NODE(pAlgIDSetDTree, SET)

		// Point to the data content (content info sequence)
		DERTree* pDataSeqDTree = pAlgIDSetDTree->nextDERTree;
		CHECK_TREE_NODE(pDataSeqDTree, SEQUENCE)

		// Point to the object id of the content and verify that the content type is 'data'
		DERTree* pDataObjIDTree = pDataSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pDataObjIDTree, OBJECT_IDENTIFIER)

		if(memcmp(pDataObjIDTree->currentBaseDER->pbData, szOID_RSA_data, pDataObjIDTree->currentBaseDER->cbData) != 0)
		{
			hr = E_VSSCODE_CONTENTYPERR;
			break;
		}

		// Check if we have any certificates
		DERTree* pCertSetDTree = pDataSeqDTree->nextDERTree;
		if(pCertSetDTree && (pCertSetDTree->currentBaseDER->Class == CONTEXT_SPECIFIC && pCertSetDTree->currentBaseDER->Encoding == CONSTRUCTED
			&& pCertSetDTree->currentBaseDER->TagNumber == 0))
		{
			bCertPresent = TRUE;

			if(pCertSetDTree->nextDERTree && (pCertSetDTree->nextDERTree->currentBaseDER->Class == CONTEXT_SPECIFIC && pCertSetDTree->nextDERTree->currentBaseDER->Encoding == CONSTRUCTED
			     && pCertSetDTree->nextDERTree->currentBaseDER->TagNumber == 1)) // check for CRLs
					bCRLPresent = TRUE;
		} 
		else 
			if(pCertSetDTree && (pCertSetDTree->currentBaseDER->Class == CONTEXT_SPECIFIC && pCertSetDTree->currentBaseDER->Encoding == CONSTRUCTED
				&& pCertSetDTree->currentBaseDER->TagNumber == 1)) // check for CRLs
					bCRLPresent = TRUE;
	
		if(bCertPresent)
		{
			pCertPresentDTree = pCertSetDTree->rightDERTree;
			pCertPresentEnumDTree = pCertPresentDTree;

			CBaseDERCollection cbdcCertList;

			while(pCertPresentEnumDTree)
			{
				CBaseDERCollection cbdcCertListTemp(pCertPresentEnumDTree->currentBaseDER->BaseDERBlob->cbData,
								pCertPresentEnumDTree->currentBaseDER->BaseDERBlob->pbData);
				cbdcCertList = cbdcCertList + cbdcCertListTemp;

				pCertPresentEnumDTree = pCertPresentEnumDTree->nextDERTree;
			}

			pPkcs7SignInfo->pbCertList = (PBYTE)malloc(cbdcCertList.BaseDERBlob->cbData);
			CHECK_MEM_BREAK(pPkcs7SignInfo->pbCertList)

			pPkcs7SignInfo->dwCertList = cbdcCertList.BaseDERBlob->cbData;
			memcpy(pPkcs7SignInfo->pbCertList, cbdcCertList.BaseDERBlob->pbData, pPkcs7SignInfo->dwCertList);
		}

		DERTree* pCRLPresentDTree = NULL;
		if(bCRLPresent)
		{
			if(pCertPresentDTree)
				pCRLPresentDTree = pCertPresentDTree->nextDERTree;
			else
				pCRLPresentDTree = pDataSeqDTree->nextDERTree;

			pPkcs7SignInfo->pbCrlList = (PBYTE)malloc(pCRLPresentDTree->currentBaseDER->cbData);
			CHECK_MEM_BREAK(pPkcs7SignInfo->pbCrlList)

			pPkcs7SignInfo->dwCrlList = pCRLPresentDTree->currentBaseDER->cbData;
			memcpy(pPkcs7SignInfo->pbCrlList, pCRLPresentDTree->currentBaseDER->pbData, pPkcs7SignInfo->dwCrlList);
		}

		DERTree* pSigInfoDTree = NULL;

		if(!bCertPresent && !bCRLPresent)
			pSigInfoDTree = pDataSeqDTree->nextDERTree;
		else
			if(bCertPresent && bCRLPresent)
				pSigInfoDTree = pCRLPresentDTree->nextDERTree;	// not sure of this
			else
				pSigInfoDTree = pCertSetDTree->nextDERTree;

		CHECK_TREE_NODE(pSigInfoDTree, SET)

		DERTree* pSigInfoPresentDTree = pSigInfoDTree->rightDERTree;

		if(pSigInfoPresentDTree && pSigInfoPresentDTree->currentBaseDER)
		{
			DERTree* pSigInfoEnumDTree = pSigInfoPresentDTree;
			CBaseDERCollection cbdcSigInfoList;

			while(pSigInfoEnumDTree)
			{
				CBaseDERCollection cbdcSigInfoListTemp(pSigInfoEnumDTree->currentBaseDER->BaseDERBlob->cbData,
									pSigInfoEnumDTree->currentBaseDER->BaseDERBlob->pbData);
				cbdcSigInfoList = cbdcSigInfoList + cbdcSigInfoListTemp;
			
				pSigInfoEnumDTree = pSigInfoEnumDTree->nextDERTree;
			}

			pPkcs7SignInfo->pbSignerInfo = (PBYTE)malloc(cbdcSigInfoList.BaseDERBlob->cbData);
			CHECK_MEM_BREAK(pPkcs7SignInfo->pbSignerInfo)

			pPkcs7SignInfo->dwSignerInfo = cbdcSigInfoList.BaseDERBlob->cbData;
			memcpy(pPkcs7SignInfo->pbSignerInfo, cbdcSigInfoList.BaseDERBlob->pbData, pPkcs7SignInfo->dwSignerInfo);
		}

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("ParsePKCS7SignedData().", "Error while parsing PKCS7 signed data.", NULL, hr);

	return hr;
}



HRESULT CreateDocSisPKCS7Sig(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
							 const _bstr_t& i_bstrHashAlg, PBYTE* o_ppbDocSisPkcs7Sig, LPDWORD o_pdwDocSisPkcs7Sig)
{
	HRESULT hr = S_OK;
	PBYTE pbCertList = NULL, pbSignerInfoList = NULL;
	DWORD dwCertList = 0, dwSignerInfoList = 0;

	do
	{
		if(!o_ppbDocSisPkcs7Sig || !o_pdwDocSisPkcs7Sig)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		*o_ppbDocSisPkcs7Sig = NULL;
		*o_pdwDocSisPkcs7Sig = 0;

		// Get a list of all certs that will be put in the final PKCS#7
		hr = GetCertList(i_pkcsSignInfoImageFile, i_pkcsSignInfoSignature, &pbCertList, &dwCertList);
		CHECK_HRESULT_BREAK

		// Get a list of all signer infos that will be put in the final PKCS#7
		hr = GetSignerInfoList(i_pkcsSignInfoImageFile, i_pkcsSignInfoSignature, &pbSignerInfoList, &dwSignerInfoList);
		CHECK_HRESULT_BREAK

		// All the information is available, now create the DOCSIS PKCS#7

		/* First create the alg obj which looks like
					SEQUENCE {
							OBJECT IDENTIFIER sha1 (1.3.14.3.2.26)
							NULL
						}
		*/

		// Setup the hash alg
		CNull cnullObj;
		CBaseDERCollection cbdcAlgId;

		if(_strnicmp(i_bstrHashAlg, "MD5", 3) == 0)
		{
			CObjectIdentifier cobjidAlgId(lstrlen(szOID_RSA_MD5), (PBYTE)szOID_RSA_MD5);
			cbdcAlgId = cobjidAlgId + cnullObj;
		}
		else
			if(_strnicmp(i_bstrHashAlg, "MD2", 3) == 0)
			{
				CObjectIdentifier cobjidAlgId(lstrlen(szOID_RSA_MD2), (PBYTE)szOID_RSA_MD2);
				cbdcAlgId = cobjidAlgId + cnullObj;
			}
			else
				if(_strnicmp(i_bstrHashAlg, "SHA1", 4) == 0)
				{
					CObjectIdentifier cobjidAlgId(lstrlen(szOID_OIWSEC_sha1), (PBYTE)szOID_OIWSEC_sha1);
					cbdcAlgId = cobjidAlgId + cnullObj;
				}
				else
				{
					hr = E_VSSCODE_INVALIDALG;
					break;
				}
		
		CSequence cseqDigestAlg(cbdcAlgId);

		// Construct the set of algorithms, we have only one alg in the set
		CBaseDERCollection cbdcDigestAlgorithms;
		cbdcDigestAlgorithms = cseqDigestAlg;
		CSet csetDigestAlgorithms(cbdcDigestAlgorithms);

		/* Construct the content info
					SEQUENCE {
							contentType contentType;
							content [0] EXPLICIT CONTENTS.&Type((Contents)(@contentType)) OPTIONAL
						}
		*/
		CObjectIdentifier cobjidData(lstrlen(szOID_RSA_data), (PBYTE)szOID_RSA_data);
		CBaseDERCollection cbdcContentInfo;
		cbdcContentInfo = cobjidData;
		CSequence cseqContentInfo(cbdcContentInfo);

		// Construct the certificate chain
		CDERBlob cderblobCerts(dwCertList, pbCertList);
		CBaseDER cbasederCerts(cderblobCerts);

		CTaggedValue ctvCertChain(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, /*false, */cbasederCerts);

		/* Create the SignerInfos object defined as
					CHOICE {
						SET OF SignerInfo,
						SEQUENCE OF SignerInfo
					}

			We will choose a set
		*/

		CBaseDERCollection cbdcSignerInfos(dwSignerInfoList, pbSignerInfoList);
		CSet csetSignerInfos(cbdcSignerInfos);


		/* Create the signed data content  which is defined as
		SignedData := SEQUENCE {
							version INTEGER,
							digestAlgorithms DigestAlgorithmIdentifiers,
							conentInfo ContentInfo,
							certificates CHOICE {
										certSet [0] IMPLICIT ExtendedCertificatesAndCertificates
										certSequence [2] IMPLICIT Certificates
									} OPTIONAL,
							signerInfos SignerInfos
						}
							
		*/
		BYTE byteVer = 0x01;
		CUniversalInteger cuiVersion(sizeof(BYTE),(PBYTE)&byteVer);

		CBaseDERCollection cbdcSignedData;
		cbdcSignedData = cuiVersion + csetDigestAlgorithms + cseqContentInfo + ctvCertChain + csetSignerInfos;
		CSequence cseqSignedData(cbdcSignedData);

		/* Finally create the signed data pkcs7 which looks like this
					SEQUENCE {
							OBJECT IDENTIFIER signedData (1.2.840.113549.1.7.2)
							[0] {
								signedData
							}
						}
		*/

		CObjectIdentifier cobjidSignedData(lstrlen(szOID_RSA_signedData), (PBYTE)szOID_RSA_signedData);
	
		CTaggedValue ctvSignedDataContent(CONTEXT_SPECIFIC, CONSTRUCTED, 0, false, /*false,*/ *(cseqSignedData.BaseDERBlob));

		CBaseDERCollection cbdcPkcs7SignedData;
		cbdcPkcs7SignedData = cobjidSignedData + ctvSignedDataContent;

		CSequence seqPkcs7SignedData;
		seqPkcs7SignedData = cbdcPkcs7SignedData;

		*o_ppbDocSisPkcs7Sig = (PBYTE)malloc(seqPkcs7SignedData.BaseDERBlob->cbData);
		CHECK_MEM_BREAK(*o_ppbDocSisPkcs7Sig)

		*o_pdwDocSisPkcs7Sig = seqPkcs7SignedData.BaseDERBlob->cbData;
		memcpy(*o_ppbDocSisPkcs7Sig, seqPkcs7SignedData.BaseDERBlob->pbData, *o_pdwDocSisPkcs7Sig);
		
	}while(0);

	FREE_MEMORY(pbCertList)
	FREE_MEMORY(pbSignerInfoList)

	if(hr != S_OK)
		_LogErrorMsg("CreateDocSisPKCS7Sig().", "Error creating PKCS#7.", NULL, hr);

	return hr;
}



HRESULT GetCertList(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
					PBYTE* o_ppbCertList, LPDWORD o_pdwCertList)
{
	HRESULT hr = S_OK;
	LPMyCertInfo pImageFileSignerInfo = NULL, pTempSignerInfo = NULL, pCertInfo = NULL;
	BOOL bCertsMatch = FALSE;

	do
	{
		if(!o_ppbCertList || !o_pdwCertList)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		*o_ppbCertList = NULL;
		*o_pdwCertList = NULL;

		// Get all the signer infos from the image file
		hr = GetSignerInfo(i_pkcsSignInfoImageFile.pbSignerInfo, i_pkcsSignInfoImageFile.dwSignerInfo, &pImageFileSignerInfo);
		CHECK_HRESULT_BREAK

		// This is the list that will contain all the certs that have to go in the final PKCS#7
		CBaseDERCollection cbdcCertList;

		// This is the current list of certs
		CBaseDERCollection cbdcImageCertList(i_pkcsSignInfoImageFile.dwCertList, i_pkcsSignInfoImageFile.pbCertList);

		// Some certs have to be removed from the current list
		if(pImageFileSignerInfo->pNext)
		{
			// If there are more than one Signer's of the ImageFile, then remove all the certs
			// from the image file list except the certs corresponding to the first signer
			LPMyCertInfo pEnumImageFileSignerInfo = pImageFileSignerInfo->pNext;
		
			CBaseDERHierarchy cbdhImageCertList(cbdcImageCertList);

			if(cbdhImageCertList.dwErrorCode)
			{
				hr = E_VSSCODE_CERTINFODECODERR;
				break;
			}

			DERTree* pCertInfoDTree = &(cbdhImageCertList.m_DERTree);
			if(!pCertInfoDTree)
			{
				hr = E_VSSCODE_NOCERTINFO;
				break;
			}

			while(pCertInfoDTree)
			{
				hr = ParseX509Cert(pCertInfoDTree->currentBaseDER->pbData, pCertInfoDTree->currentBaseDER->cbData, &pCertInfo);
				CHECK_HRESULT_BREAK

				// Check if this cert info is there in any of the signer info, if present do
				// not add it in the O/P
				bCertsMatch = FALSE;
				while(pEnumImageFileSignerInfo)
				{
					if((pEnumImageFileSignerInfo->dwIssuerDN == pCertInfo->dwIssuerDN) &&
					   (pEnumImageFileSignerInfo->dwSerialNumber == pCertInfo->dwSerialNumber))
					{
						if((memcmp(pEnumImageFileSignerInfo->pbIssuerDN, pCertInfo->pbIssuerDN, pCertInfo->dwIssuerDN) == 0) &&
						   (memcmp(pEnumImageFileSignerInfo->pbSerialNumber, pCertInfo->pbSerialNumber, pCertInfo->dwSerialNumber) == 0))
						{
							bCertsMatch = TRUE;
							break;
						}
						else
							bCertsMatch = FALSE;
					}
					else
						bCertsMatch = FALSE;

					pEnumImageFileSignerInfo = pEnumImageFileSignerInfo->pNext;
				}

				// If the current cert is not there in any of the signer info list add it to
				// the list of O/P certs
				if(bCertsMatch == FALSE)
				{
					CBaseDERCollection cbdcTempCertList(pCertInfoDTree->currentBaseDER->BaseDERBlob->cbData,
								pCertInfoDTree->currentBaseDER->BaseDERBlob->pbData);
					cbdcCertList = cbdcCertList + cbdcTempCertList;
				}

				pCertInfoDTree = pCertInfoDTree->nextDERTree;

				// Reinitialize the Signer cert info pointer
				pEnumImageFileSignerInfo = pImageFileSignerInfo->pNext;

				FREE_CERT_INFO(pCertInfo)
			}
		}
		else
			cbdcCertList = cbdcImageCertList;

		// Add the certificate from the PTA signature to the output cert list
		CBaseDERCollection cbdcPTASignature(i_pkcsSignInfoSignature.dwCertList, i_pkcsSignInfoSignature.pbCertList);
		cbdcCertList = cbdcCertList + cbdcPTASignature;

		*o_ppbCertList = (PBYTE)malloc(cbdcCertList.BaseDERBlob->cbData);
		CHECK_MEM_BREAK(*o_ppbCertList)

		*o_pdwCertList = cbdcCertList.BaseDERBlob->cbData;
		memcpy(*o_ppbCertList, cbdcCertList.BaseDERBlob->pbData, *o_pdwCertList);
		
	}while(0);

	while(pImageFileSignerInfo)
	{
		pTempSignerInfo = pImageFileSignerInfo->pNext;
		
		FREE_CERT_INFO(pImageFileSignerInfo)

		pImageFileSignerInfo = pTempSignerInfo;
	}

	FREE_CERT_INFO(pCertInfo)

	if(hr != S_OK)
		_LogErrorMsg("GetCertList().", "Error obtaining certificate list.", NULL, hr);

	return hr;
}



HRESULT GetSignerInfo(PBYTE i_pbSignerInfo, DWORD i_dwSignerInfo, LPMyCertInfo* o_ppCertInfo)
{
	HRESULT hr = S_OK;
	LPMyCertInfo pCertInfoPtr = NULL, pCurrentCertInfo = NULL;

	do
	{
		if(!i_pbSignerInfo || !o_ppCertInfo)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_dwSignerInfo == 0)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		*o_ppCertInfo = NULL;

		CBaseDERCollection cbdcImageSigners(i_dwSignerInfo, i_pbSignerInfo);
		CBaseDERHierarchy cbdhImageSigners(cbdcImageSigners);

		if(cbdhImageSigners.dwErrorCode)
		{
			hr = E_VSSCODE_SIGNERINFODECODERR;			
			break;
		}

		DERTree* pSigInfoDTree = &(cbdhImageSigners.m_DERTree);

		if(!pSigInfoDTree)
		{
			hr = E_VSSCODE_NOSIGNERINFO;
			break;
		}


		while(pSigInfoDTree)
		{
			hr = ParseSignerInfo(pSigInfoDTree->currentBaseDER->BaseDERBlob->pbData, 
							pSigInfoDTree->currentBaseDER->BaseDERBlob->cbData, &pCurrentCertInfo);
			CHECK_HRESULT_BREAK

			if(pCertInfoPtr == NULL)
			{
				*o_ppCertInfo = pCurrentCertInfo;
				pCertInfoPtr = pCurrentCertInfo;
			}
			else
			{
				pCertInfoPtr->pNext = pCurrentCertInfo;
				pCertInfoPtr = pCurrentCertInfo;
			}
			
			pSigInfoDTree = pSigInfoDTree->nextDERTree;
		}

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("GetSignerInfo().", "Error obtaining signer information.", NULL, hr);

	return hr;
}



HRESULT ParseSignerInfo(PBYTE i_pbSignerDataDerBlob, DWORD i_dwSignerDataDerBlob, LPMyCertInfo* o_ppCertInfo)
{
	HRESULT hr = S_OK;

	do
	{
		if(!i_pbSignerDataDerBlob || !o_ppCertInfo)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_dwSignerDataDerBlob == 0)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		*o_ppCertInfo = NULL;

		CBaseDERCollection cbdcSignerInfo(i_dwSignerDataDerBlob, i_pbSignerDataDerBlob);
		CBaseDERHierarchy cbdhSignerData(cbdcSignerInfo);

		if(cbdhSignerData.dwErrorCode)
		{
			hr = E_VSSCODE_SIGNERINFODECODERR;
			break;
		}

		// Point to the signer info sequence
		DERTree* pSigInfoDTree = &(cbdhSignerData.m_DERTree);
		CHECK_TREE_NODE(pSigInfoDTree, SEQUENCE)

		// Point to the version number
		DERTree* pVersion = pSigInfoDTree->rightDERTree;
		CHECK_TREE_NODE(pVersion, UNIVERSAL_INTEGER)

		// Point to the issuerDN, serialNo sequence
		DERTree* pIssDNSNSeqDTree = pVersion->nextDERTree;
		CHECK_TREE_NODE(pIssDNSNSeqDTree, SEQUENCE)

		DERTree* pIssuerDTree = pIssDNSNSeqDTree->rightDERTree;
		CHECK_TREE_NODE(pIssuerDTree, SEQUENCE)

		DERTree* pSerialNumDTree = pIssuerDTree->nextDERTree;
		CHECK_TREE_NODE(pSerialNumDTree, UNIVERSAL_INTEGER)

		*o_ppCertInfo = (LPMyCertInfo)malloc(sizeof(MyCertInfo));
		CHECK_MEM_BREAK(*o_ppCertInfo)

		(*o_ppCertInfo)->pNext = NULL;

		// Copy the issuerDN
		(*o_ppCertInfo)->pbIssuerDN = (PBYTE)malloc(pIssuerDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK((*o_ppCertInfo)->pbIssuerDN)

		(*o_ppCertInfo)->dwIssuerDN = pIssuerDTree->currentBaseDER->cbData;
		memcpy((*o_ppCertInfo)->pbIssuerDN, pIssuerDTree->currentBaseDER->pbData, (*o_ppCertInfo)->dwIssuerDN);

		// Copy the serialNum
		(*o_ppCertInfo)->pbSerialNumber = (PBYTE)malloc(pSerialNumDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK((*o_ppCertInfo)->pbSerialNumber)

		(*o_ppCertInfo)->dwSerialNumber = pSerialNumDTree->currentBaseDER->cbData;
		memcpy((*o_ppCertInfo)->pbSerialNumber, pSerialNumDTree->currentBaseDER->pbData, (*o_ppCertInfo)->dwSerialNumber);

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("ParseSignerInfo().", "Error parsing signer information.", NULL, hr);

	return hr;
}


HRESULT ParseX509Cert(PBYTE i_pbCertificateDerBlob, DWORD i_dwCertificateDerBlob, LPMyCertInfo* o_ppCertInfo)
{
	HRESULT hr = S_OK;

	do
	{
		if(!i_pbCertificateDerBlob || !o_ppCertInfo)
		{
			hr = E_VSSCODE_EMPTYARGS;
			break;
		}

		if(i_dwCertificateDerBlob == 0)
		{
			hr = E_VSSCODE_INVALIDARGS;
			break;
		}

		*o_ppCertInfo = NULL;

		CBaseDERCollection cbdcCertInfo(i_dwCertificateDerBlob, i_pbCertificateDerBlob);
		CBaseDERHierarchy cbdhCertInfo(cbdcCertInfo);

		if(cbdhCertInfo.dwErrorCode)
		{
			hr = E_VSSCODE_CERTINFODECODERR;
			break;
		}

		// Point to the cert info sequence
		DERTree* pCertInfoDTree = &(cbdhCertInfo.m_DERTree);
		CHECK_TREE_NODE(pCertInfoDTree, SEQUENCE)

		DERTree* pSerNumDTree = NULL;

		// Point to the version tag
		DERTree* pVersionTagDTree = pCertInfoDTree->rightDERTree;
		if(!pVersionTagDTree || (pVersionTagDTree->currentBaseDER->Class != CONTEXT_SPECIFIC || pVersionTagDTree->currentBaseDER->Encoding != CONSTRUCTED
			|| pVersionTagDTree->currentBaseDER->TagNumber != 0))
			pSerNumDTree = pVersionTagDTree;	// The version tag is absent
		else
			pSerNumDTree = pVersionTagDTree->nextDERTree;

		// Check the serial number
		CHECK_TREE_NODE(pSerNumDTree, UNIVERSAL_INTEGER)

		// Point to the AlgID sequence
		DERTree* pAlgIDSeqDTree = pSerNumDTree->nextDERTree;
		CHECK_TREE_NODE(pAlgIDSeqDTree, SEQUENCE)

		// Point to the issuer DN
		DERTree* pIssuerDNDTree = pAlgIDSeqDTree->nextDERTree;
		CHECK_TREE_NODE(pIssuerDNDTree, SEQUENCE)

		// Copy the serial number and issuer DN now
		*o_ppCertInfo = (LPMyCertInfo)malloc(sizeof(MyCertInfo));
		(*o_ppCertInfo)->pNext = NULL;

		(*o_ppCertInfo)->pbSerialNumber = (PBYTE)malloc(pSerNumDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK((*o_ppCertInfo)->pbSerialNumber)

		(*o_ppCertInfo)->dwSerialNumber = pSerNumDTree->currentBaseDER->cbData;
		memcpy((*o_ppCertInfo)->pbSerialNumber, pSerNumDTree->currentBaseDER->pbData, (*o_ppCertInfo)->dwSerialNumber);

		(*o_ppCertInfo)->pbIssuerDN = (PBYTE)malloc(pIssuerDNDTree->currentBaseDER->cbData);
		CHECK_MEM_BREAK((*o_ppCertInfo)->pbIssuerDN)

		(*o_ppCertInfo)->dwIssuerDN = pIssuerDNDTree->currentBaseDER->cbData;
		memcpy((*o_ppCertInfo)->pbIssuerDN, pIssuerDNDTree->currentBaseDER->pbData, (*o_ppCertInfo)->dwIssuerDN);

	}while(0);

	if(hr != S_OK)
		_LogErrorMsg("ParseX509Cert().", "Error parsing certificate.", NULL, hr);

	return hr;
}


HRESULT GetSignerInfoList(PKCS7SignInfo& i_pkcsSignInfoImageFile, PKCS7SignInfo& i_pkcsSignInfoSignature, 
						  PBYTE* o_ppbSignerInfoList, LPDWORD o_pdwSignerInfoList)
{
	HRESULT hr = S_OK;

	do
	{
		CBaseDERCollection cbdcImageFile(i_pkcsSignInfoImageFile.dwSignerInfo, i_pkcsSignInfoImageFile.pbSignerInfo);
		CBaseDERHierarchy cbdhImageFile(cbdcImageFile);

		if(cbdhImageFile.dwErrorCode)
		{
			hr = E_VSSCODE_SIGNERINFODECODERR;
			break;
		}

		DERTree* pImageFileDTree = &(cbdhImageFile.m_DERTree);

		if(!pImageFileDTree)
		{
			hr = E_VSSCODE_NOSIGNERINFO;
			break;
		}

		CBaseDERCollection cbdcPTASignature(i_pkcsSignInfoSignature.dwSignerInfo, i_pkcsSignInfoSignature.pbSignerInfo);
		CBaseDERHierarchy cbdhPTASignature(cbdcPTASignature);

		if(cbdhPTASignature.dwErrorCode)
		{
			hr = E_VSSCODE_SIGNERINFODECODERR;
			break;
		}

		DERTree* pPTASigDTree = &(cbdhPTASignature.m_DERTree);

		if(!pPTASigDTree)
		{
			hr = E_VSSCODE_NOSIGNERINFO;
			break;
		}

		// Get the first signer infos from each of the collection
		CBaseDERCollection cbdcOutSignerInfo;
		CBaseDERCollection cbdcImageFileTemp(pImageFileDTree->currentBaseDER->BaseDERBlob->cbData,
									pImageFileDTree->currentBaseDER->BaseDERBlob->pbData);
		CBaseDERCollection cbdcPTASigTemp(pPTASigDTree->currentBaseDER->BaseDERBlob->cbData,
									pPTASigDTree->currentBaseDER->BaseDERBlob->pbData);

		cbdcOutSignerInfo = cbdcImageFileTemp + cbdcPTASigTemp;

		*o_ppbSignerInfoList = (PBYTE)malloc(cbdcOutSignerInfo.BaseDERBlob->cbData);
		CHECK_MEM_BREAK(*o_ppbSignerInfoList)

		*o_pdwSignerInfoList = cbdcOutSignerInfo.BaseDERBlob->cbData;
		memcpy(*o_ppbSignerInfoList, cbdcOutSignerInfo.BaseDERBlob->pbData, *o_pdwSignerInfoList);
		
	}while(0);


	if(hr != S_OK)
		_LogErrorMsg("GetSignerInfoList().", "Error obtaining signer information.", NULL, hr);

	return hr;
}


VOID PKCS7SignInfo::Initialize()
{
	pbCertList = NULL;
	dwCertList = 0;

	pbCrlList = NULL;
	dwCrlList = 0;

	pbSignerInfo = NULL;
	dwSignerInfo = 0;
}


VOID PKCS7SignInfo::Clear()
{
	FREE_MEMORY(pbCertList)
	dwCertList = 0;

	FREE_MEMORY(pbCrlList)
	dwCrlList = 0;

	FREE_MEMORY(pbSignerInfo)
	dwSignerInfo = 0;
}