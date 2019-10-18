#include "stdafx.h"
#include "..\Include\vscapi.h"
#include "..\Include\utils.h"

BOOL WINAPI VS_CertFreeCertificateContext(PCCERT_CONTEXT pCertContext)
{
		delete[] pCertContext->pbCertEncoded;

		if(pCertContext->pCertInfo)
		{
			freecertinfo(pCertContext->pCertInfo); 
			free(pCertContext->pCertInfo);
			/*
			delete[] pCertContext->pCertInfo->Issuer.pbData;
			
			delete[] pCertContext->pCertInfo->IssuerUniqueId.pbData;
			
			delete[] pCertContext->pCertInfo->SerialNumber.pbData;
			
			delete[] pCertContext->pCertInfo->SignatureAlgorithm.Parameters.pbData;
			
			delete[] pCertContext->pCertInfo->SignatureAlgorithm.pszObjId;
			
			delete[] pCertContext->pCertInfo->Subject.pbData;
			
			delete[] pCertContext->pCertInfo->SubjectUniqueId.pbData;
			
			delete[] pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.pbData;
			
			delete[] pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId;
			
			delete[] pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData;

			
			for(unsigned int i =0 ;i < pCertContext->pCertInfo->cExtension; ++i)
			{
				delete[] pCertContext->pCertInfo->rgExtension[i].pszObjId;
				
				delete[] pCertContext->pCertInfo->rgExtension[i].Value.pbData;
			}

			delete[] pCertContext->pCertInfo->rgExtension;

			delete pCertContext->pCertInfo;*/
		}

		
		delete ((PCERT_CONTEXT)pCertContext);
		return 1;
}

PCCERT_CONTEXT WINAPI VS_CertDuplicateCertificateContext(IN PCCERT_CONTEXT i_pCertContext)
{
	PCERT_CONTEXT outCertContext = NULL;

	if(i_pCertContext)
	{
		outCertContext = new CERT_CONTEXT;
	
		outCertContext->cbCertEncoded = i_pCertContext->cbCertEncoded;
		outCertContext->dwCertEncodingType = i_pCertContext->dwCertEncodingType;
		outCertContext->hCertStore = i_pCertContext->hCertStore;
		outCertContext->pbCertEncoded = new BYTE[i_pCertContext->cbCertEncoded];
		memcpy(outCertContext->pbCertEncoded,i_pCertContext->pbCertEncoded,
			i_pCertContext->cbCertEncoded);

		if(i_pCertContext->pCertInfo)
		{
			outCertContext->pCertInfo = (PCERT_INFO)malloc(sizeof(CERT_INFO));
			memset(outCertContext->pCertInfo,0,sizeof(CERT_INFO));

			outCertContext->pCertInfo->cExtension = i_pCertContext->pCertInfo->cExtension;
			outCertContext->pCertInfo->dwVersion = i_pCertContext->pCertInfo->dwVersion;
			
			outCertContext->pCertInfo->Issuer.cbData = i_pCertContext->pCertInfo->Issuer.cbData;
			mallocandcpy(outCertContext->pCertInfo->Issuer.pbData, i_pCertContext->pCertInfo->Issuer.pbData, i_pCertContext->pCertInfo->Issuer.cbData);
			
			outCertContext->pCertInfo->IssuerUniqueId.cbData  = i_pCertContext->pCertInfo->IssuerUniqueId.cbData;
			outCertContext->pCertInfo->IssuerUniqueId.cUnusedBits   = i_pCertContext->pCertInfo->IssuerUniqueId.cUnusedBits;
			mallocandcpy(outCertContext->pCertInfo->IssuerUniqueId.pbData,i_pCertContext->pCertInfo->IssuerUniqueId.pbData,
				 i_pCertContext->pCertInfo->IssuerUniqueId.cbData);
	
			outCertContext->pCertInfo->NotAfter = i_pCertContext->pCertInfo->NotAfter;
			outCertContext->pCertInfo->NotBefore = i_pCertContext->pCertInfo->NotBefore;

			outCertContext->pCertInfo->SerialNumber.cbData = i_pCertContext->pCertInfo->SerialNumber.cbData;
			mallocandcpy(outCertContext->pCertInfo->SerialNumber.pbData, i_pCertContext->pCertInfo->SerialNumber.pbData, i_pCertContext->pCertInfo->SerialNumber.cbData);

			outCertContext->pCertInfo->SignatureAlgorithm.Parameters.cbData = i_pCertContext->pCertInfo->SignatureAlgorithm.Parameters.cbData;
			mallocandcpy(outCertContext->pCertInfo->SignatureAlgorithm.Parameters.pbData,i_pCertContext->pCertInfo->SignatureAlgorithm.Parameters.pbData, 
				i_pCertContext->pCertInfo->SignatureAlgorithm.Parameters.cbData);

			mallocandcpy((BYTE*&)outCertContext->pCertInfo->SignatureAlgorithm.pszObjId, (BYTE*)i_pCertContext->pCertInfo->SignatureAlgorithm.pszObjId, strlen(i_pCertContext->pCertInfo->SignatureAlgorithm.pszObjId)+1);

			outCertContext->pCertInfo->Subject.cbData = i_pCertContext->pCertInfo->Subject.cbData;
			mallocandcpy(outCertContext->pCertInfo->Subject.pbData,i_pCertContext->pCertInfo->Subject.pbData, i_pCertContext->pCertInfo->Subject.cbData);
	
			outCertContext->pCertInfo->SubjectUniqueId.cbData  = i_pCertContext->pCertInfo->SubjectUniqueId.cbData;
			outCertContext->pCertInfo->SubjectUniqueId.cUnusedBits   = i_pCertContext->pCertInfo->SubjectUniqueId.cUnusedBits;
			mallocandcpy(outCertContext->pCertInfo->SubjectUniqueId.pbData,i_pCertContext->pCertInfo->SubjectUniqueId.pbData,
				 i_pCertContext->pCertInfo->SubjectUniqueId.cbData);

			outCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.cbData = i_pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.cbData;
			mallocandcpy(outCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.pbData,
				 i_pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.pbData,
				 i_pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.Parameters.cbData);
	
			mallocandcpy((BYTE*&)outCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId,
				 (BYTE*)i_pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId,
				 strlen(i_pCertContext->pCertInfo->SubjectPublicKeyInfo.Algorithm.pszObjId)+1);
	
			outCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData  = i_pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData;
			outCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cUnusedBits   = i_pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cUnusedBits;
			mallocandcpy(outCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData,
				 i_pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.pbData,
				 i_pCertContext->pCertInfo->SubjectPublicKeyInfo.PublicKey.cbData);
	
			outCertContext->pCertInfo->rgExtension = (PCERT_EXTENSION)malloc(sizeof(CERT_EXTENSION) * outCertContext->pCertInfo->cExtension);
			for(unsigned int i =0 ;i < outCertContext->pCertInfo->cExtension; ++i)
			{
				outCertContext->pCertInfo->rgExtension[i].fCritical = i_pCertContext->pCertInfo->rgExtension[i].fCritical;
				mallocandcpy((BYTE*&)outCertContext->pCertInfo->rgExtension[i].pszObjId,
					 (BYTE*)i_pCertContext->pCertInfo->rgExtension[i].pszObjId,
					 strlen(i_pCertContext->pCertInfo->rgExtension[i].pszObjId) + 1);
				
				outCertContext->pCertInfo->rgExtension[i].Value.cbData = i_pCertContext->pCertInfo->rgExtension[i].Value.cbData;
				mallocandcpy(outCertContext->pCertInfo->rgExtension[i].Value.pbData ,
					 i_pCertContext->pCertInfo->rgExtension[i].Value.pbData,
					 i_pCertContext->pCertInfo->rgExtension[i].Value.cbData);
		
			}
		}

	}
	

	return outCertContext;
}