/////////////vssc_util.cpp////////////////////////

#include "stdafx.h"

HRESULT         hr;
BSTR			bstrRetVal;
BSTR			m_bstrErrorCodeString ;		
DWORD			m_dwErrorCode,err ;	

extern CListUserInfo				*g_pSignerCertInGM;
extern CListUserInfo				*g_pEncryptCertInGM;
extern g_GlobalMemoryManagement		*gp_GMemMgmt;
extern DWORD                        g_dwCertTimeOut;
extern DWORD                        g_dwAppErr;



HRESULT GetSignerCertificate(
							 _bstr_t bstrEmailAddr,
							 _bstr_t m_bstrCertResolutionURL,
							 PCERT_RESOLVE_INFO  pCertResolveInfo,
							 PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
							 int  nCertReqCertInfo,
							 CListUserInfo *i_pUserList
							 )
{
	   CPost				Post;
	   _bstr_t		        bstrResolveUser="",bstrUnResolveUser="";

	   PCERT_REQ_CRIT_INFO *o_pUnResolveCertReqCritInfo=NULL;
	   int                  o_nUnResolvenCertReqCertInfo=0;

	   hr=S_OK;

	   do
	   {

			///////
		    if(pCertResolveInfo->ReqCrit==0)
			{
						hr=Post.FindCertificateByEmailAddr(
															bstrEmailAddr,
															&bstrResolveUser,
															&bstrUnResolveUser,
															i_pUserList,
															g_pSignerCertInGM
															);
						CHECK_HRESULT_BREAK;

						if(bstrUnResolveUser.length()>0)
						{
								hr=Post.ResolveName(
											m_bstrCertResolutionURL,
											bstrUnResolveUser,
											pCertResolveInfo,
											pCertReqCritInfo,
											nCertReqCertInfo,
											i_pUserList
											);
								if(hr!=S_OK)
								{
									g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
									break;
								}
						}



			}
			else
			{
						o_pUnResolveCertReqCritInfo=
										new PCERT_REQ_CRIT_INFO[nCertReqCertInfo];


						 hr=Post.FindCertificateByIssuerDNSerialNum(
															pCertResolveInfo,
															pCertReqCritInfo,
															nCertReqCertInfo,
															o_pUnResolveCertReqCritInfo,
															&o_nUnResolvenCertReqCertInfo,
															i_pUserList,
															g_pSignerCertInGM
															);
	

						CHECK_HRESULT_BREAK;

						if(o_nUnResolvenCertReqCertInfo!=0)
						{
											
								hr=Post.ResolveName(
												m_bstrCertResolutionURL,
												bstrUnResolveUser,
												pCertResolveInfo,
												o_pUnResolveCertReqCritInfo,
												o_nUnResolvenCertReqCertInfo,
												i_pUserList
												);

								if(hr!=S_OK)
								{
									g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
									break;
								}

						}

			}

				
			/////update Global Memory
			Post.AddCertificatesInGM(
									i_pUserList,
									g_pSignerCertInGM
									);

			
	   }
	   while(0);
	   
	   DELETE_MEMORY(o_pUnResolveCertReqCritInfo)

return hr;
}

HRESULT GetEncryptionCertificates(
								  _bstr_t bstrEmailAddr,
								  _bstr_t m_bstrCertResolutionURL,
								  PCERT_RESOLVE_INFO  pCertResolveInfo,
								  PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
								  int  nCertReqCertInfo,
								  CListUserInfo *i_pUserList
								  )
{
	   CPost				Post;
	   _bstr_t		        bstrResolveUser="",bstrUnResolveUser="";

	   PCERT_REQ_CRIT_INFO *o_pUnResolveCertReqCritInfo=NULL;
	   int                  o_nUnResolvenCertReqCertInfo=0;

	   hr=S_OK;

	   do
	   {

			///////
		    if(pCertResolveInfo->ReqCrit==0)
			{
						hr=Post.FindCertificateByEmailAddr(
															bstrEmailAddr,
															&bstrResolveUser,
															&bstrUnResolveUser,
															i_pUserList,
															g_pEncryptCertInGM
															);
						CHECK_HRESULT_BREAK;
						
						if(bstrUnResolveUser.length()>0)
						{
							hr=Post.ResolveName(
										m_bstrCertResolutionURL,
										bstrUnResolveUser,
										pCertResolveInfo,
										pCertReqCritInfo,
										nCertReqCertInfo,
										i_pUserList
										);
							if(hr!=S_OK)
							{
								g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
								break;
							}

						}



			}
			else
			{
						o_pUnResolveCertReqCritInfo=
										new PCERT_REQ_CRIT_INFO[nCertReqCertInfo];


						 hr=Post.FindCertificateByIssuerDNSerialNum(
															pCertResolveInfo,
															pCertReqCritInfo,
															nCertReqCertInfo,
															o_pUnResolveCertReqCritInfo,
															&o_nUnResolvenCertReqCertInfo,
															i_pUserList,
															g_pEncryptCertInGM
															);
	

						CHECK_HRESULT_BREAK;

						if(o_nUnResolvenCertReqCertInfo!=0)
						{
							hr=Post.ResolveName(
										m_bstrCertResolutionURL,
										bstrUnResolveUser,
										pCertResolveInfo,
										o_pUnResolveCertReqCritInfo,
										o_nUnResolvenCertReqCertInfo,
										i_pUserList
										);

							if(hr!=S_OK)
							{
								g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
								break;
							}

						}

			}
				
			/////update Global Memory
			Post.AddCertificatesInGM(
									i_pUserList,
									g_pEncryptCertInGM
									);

			
	   }
	   while(0);
	   ////////
	   DELETE_MEMORY(o_pUnResolveCertReqCritInfo)


return hr;
}

HRESULT GetPRC(
			  _bstr_t bstrEmailAddr,
			  _bstr_t m_bstrCertResolutionURL,
			  PCERT_RESOLVE_INFO  pCertResolveInfo,
			   CListUserInfo *i_pUserList
			  )
{
	   CPost				Post;
	   _bstr_t		        bstrResolveUser="",bstrUnResolveUser="";

	   hr=S_OK;

	   do
	   {

						
						if(bstrEmailAddr.length()>0)
						{
							hr=Post.ResolveName(
										m_bstrCertResolutionURL,
										bstrEmailAddr,
										pCertResolveInfo,
										NULL,
										0,
										i_pUserList
										);
							if(hr!=S_OK)
							{
									g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
									break;
							}

						}



			

			
	   }
	   while(0);
	   

return hr;
}

HRESULT HowToUsePRC(
					CListUserInfo *i_pPRCList,
					DWORD         dwPRCUse,
					PCERT_INFO     *pPRCCertInfo
					)
{
	hr=S_OK;

	CUserInfo		*pObj=NULL;

	VSSC_ENCODED_CERT  EncodedCert;

	memset(&EncodedCert,0,sizeof(VSSC_ENCODED_CERT));

	do
	{

	

				if(i_pPRCList->empty())
				{
					hr=E_PRC_CERTNOTFOUND;
					g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
					break;
				}

				CListUserInfo::iterator		itPRC;
				
				itPRC=i_pPRCList->begin();
				pObj=(*itPRC);

				if(pObj==NULL)
				{
					hr=E_PRC_CERTNOTFOUND;
					g_dwAppErr= E_UNABLE_TODO_CERTRESOLVE;
					break;

				}

				if(pObj->stCertStatusInfo.dwRevocationStatus!=0)
				{
						hr=E_PRC_REVOKED;
						g_dwAppErr=E_REVOKED_OR_EXPIED_CERT;
						break;
			
				}
						
				EncodedCert=pObj->GetEncryptionCert();
				if(EncodedCert.pbData==NULL && EncodedCert.cbData==0)
				{
					hr=E_PRC_CERTNOTFOUND;
					g_dwAppErr= E_UNABLE_TODO_CERTRESOLVE;
					break;
				}
		
				
						
				CCertInfo  PRCCertInfo(EncodedCert.pbData,EncodedCert.cbData);
				*pPRCCertInfo=PRCCertInfo.GetCertInfo();
				if(*pPRCCertInfo==NULL)
				{
					hr=E_PRC_CERTNOTFOUND;
					g_dwAppErr= E_UNABLE_TODO_CERTRESOLVE;
					break;
				}

				

				DECCERT_INFO			DecCertInfo;
				hr=_DecodeCertInfo(*pPRCCertInfo,&DecCertInfo);
				CHECK_HRESULT_BREAK

				SYSTEMTIME      stSysTime;
				DATE			dtDate;

				GetSystemTime(&stSysTime);
				if(!SystemTimeToVariantTime(&stSysTime,&dtDate))
				{
					hr = E_SYSTIMETOVARTIMEFAILED;
					g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
				}
				
				if(!(DecCertInfo.dateEffDate<dtDate &&dtDate <DecCertInfo.dateExpDate))
				{
					hr=E_PRC_EXPIRED;
					g_dwAppErr=E_REVOKED_OR_EXPIED_CERT;
					break;
				}
	}
	while(0);

	return hr;
}



HRESULT _DecodeCertInfo(PCERT_INFO i_pCertInfo, PDECCERT_INFO io_pDecCertInfo)
{



	HRESULT retVal = S_OK;
	
	

	/*Get the cert issuer dn*/
	retVal = _GetNameFromBlob(i_pCertInfo->Issuer, &io_pDecCertInfo->bstrIssuerDN);

	/*Get the cert subject dn*/
	if(retVal == S_OK)
	{
		retVal = _GetNameFromBlob(i_pCertInfo->Subject, &io_pDecCertInfo->bstrSubjectDN);
	}

	/*Get the cert serial number*/
	if(retVal == S_OK)
	{
		retVal = _GetCertSerNum(i_pCertInfo->SerialNumber, &io_pDecCertInfo->bstrSerNum);
	}

	/*Get the key size*/
	if(retVal == S_OK)
	{
		A_RSA_KEY theRSAKey;
		retVal = GetRSAKeyFromKeyInfo(&i_pCertInfo->SubjectPublicKeyInfo,&theRSAKey);
		if(retVal == S_OK)
		{
			io_pDecCertInfo->nKeySize = theRSAKey.modulus.len * 8; //in bits
		}
		delete[] theRSAKey.modulus.data;
		delete[] theRSAKey.exponent.data;
	}

	/*Get the cert effective*/
	if(retVal == S_OK)
	{
		retVal = _GetDateFromFileTime(i_pCertInfo->NotBefore, &io_pDecCertInfo->dateEffDate);
	}

	/*Get the cert expiration date*/
	if(retVal == S_OK)
	{
		retVal = _GetDateFromFileTime(i_pCertInfo->NotAfter, &io_pDecCertInfo->dateExpDate);
	}

	return retVal;
}


HRESULT _GetNameFromBlob(CERT_NAME_BLOB& i_TheNameBlob, _bstr_t* o_ptbstrName)
{
	HRESULT retVal = S_OK;
	DWORD   dwSize = NULL;
	TCHAR*	tstrName = NULL;

    dwSize = MyCertNameToStr(MY_ENCODING_TYPE, &i_TheNameBlob, 
							 CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, NULL, dwSize);

    if(dwSize <= 1)		// This function always returns a null char (0), so the minimum count returned will 
						// be 1, even if nothing got converted
        return E_CERTNAMETOSTRFAILED;

	// Allocate memory for the returned string
    tstrName = new TCHAR[dwSize+1];
    if(!(tstrName))
		return E_FAIL;

    dwSize = MyCertNameToStr(MY_ENCODING_TYPE, &i_TheNameBlob,
						     CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG, tstrName, dwSize);              // Size of string (chars)

    if(dwSize <= 1)
        retVal =  E_CERTNAMETOSTRFAILED;

	if(retVal == S_OK)
		*o_ptbstrName = tstrName;
	else
		*o_ptbstrName = "";

	delete[] tstrName;

	return retVal;
}


HRESULT _GetCertSerNum(CRYPT_INTEGER_BLOB& i_SerialNumber, _bstr_t* o_ptbstrSerNum)
{
	DWORD				dwSerialNumber = NULL;
	PBYTE				SerialNumber = NULL;
	HRESULT				retVal = S_OK;
	TCHAR*				tstrSerNum = NULL;

    
	dwSerialNumber = i_SerialNumber.cbData;
	
	if((SerialNumber = new BYTE[dwSerialNumber]) == NULL)
	{
		retVal = E_FAIL;
	}
	else
	{
		//Reverse the bytes
		unsigned int i ;
		for ( i = 0 ; i < dwSerialNumber ; i++ )
			SerialNumber[dwSerialNumber-1-i] = (i_SerialNumber.pbData)[i] ;

		if((tstrSerNum = new TCHAR[(dwSerialNumber*2)+1]) == NULL)
		{
			retVal = E_FAIL;
		}
		else
		{
			_bstr_t temp("%02x");

			for ( i = 0 ; i < dwSerialNumber ; i++ )
			{
				wsprintf((tstrSerNum)+(i*2), (TCHAR*)temp, (unsigned char)SerialNumber[i]) ;
			}
			
			*o_ptbstrSerNum = tstrSerNum;
			delete[] tstrSerNum;

		}

		delete[] SerialNumber;
	}
	return retVal;
}

HRESULT _GetDateFromFileTime(FILETIME& i_ftTheFileTime, DATE* o_pDate)
{
	HRESULT retVal = S_OK;
	
	SYSTEMTIME      stSysTime;

	if(!FileTimeToSystemTime(&i_ftTheFileTime,&stSysTime))
	{
		retVal = E_FILETIMETOSYSTIMEFAILED;
	}
	else
	{
		if(!SystemTimeToVariantTime(&stSysTime,o_pDate))
		{
			retVal = E_SYSTIMETOVARTIMEFAILED;
		}
	}

	return retVal;
}

DWORD MyCertNameToStr(DWORD dwCertEncodingType, PCERT_NAME_BLOB pName, DWORD dwStrType,
					  LPTSTR psz, DWORD csz)
{
	if ( NULL == pName )
		return 0;

	// Only support for these for now
	if ( ( CERT_X500_NAME_STR | CERT_NAME_STR_SEMICOLON_FLAG ) != dwStrType )
		return 0;

	CBaseDERCollection cbdcCertName( pName->cbData, pName->pbData );
	CBaseDERHierarchy cbdhCertName( cbdcCertName );
	DERTree* dtCertNameInfo = &cbdhCertName.m_DERTree, *dtSet = NULL, *dtSequence = NULL;
	DERTree *dtObjID = NULL, *dtObjIDValue = NULL;
	BYTE *pbData = NULL, *pbValueData = NULL;
	DWORD cbData = 0, cbValueData = 0, dwTotalRdnLen = 0;
	TCHAR szLabel[MAX_PATH];
	
	// Confirm we have a SEQUENCE
	if ( NULL == dtCertNameInfo || SEQUENCE != dtCertNameInfo->currentBaseDER->Type )
		return 0;

	if ( NULL != psz && 0 < csz)
		psz[0] = '\0';

	// Construct the o=;ou=...
	dtSet = dtCertNameInfo->rightDERTree;
	
	while ( NULL != dtSet )
	{
		// Make sure that it is a set
		if ( SET != dtSet->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		// Make sure that it is a sequence
		dtSequence = dtSet->rightDERTree;
		if ( NULL == dtSequence || SEQUENCE != dtSequence->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		// Make sure that it is a object ID.
		dtObjID = dtSequence->rightDERTree;
		if ( NULL == dtObjID || OBJECT_IDENTIFIER != dtObjID->currentBaseDER->Type )
		{
			dwTotalRdnLen = 0;
			break;
		}

		pbData = dtObjID->currentBaseDER->pbData;
		cbData = dtObjID->currentBaseDER->cbData;

		// Value of the Object ID
		dtObjIDValue = dtObjID->nextDERTree;

		if ( NULL == dtObjIDValue )
		{
			dwTotalRdnLen = 0;
			break;
		}

		pbValueData = dtObjIDValue->currentBaseDER->pbData;
		cbValueData = dtObjIDValue->currentBaseDER->cbData;

		if ( !strnicmp((const char*)pbData, szOID_COMMON_NAME, cbData) )
		{
			lstrcpy(szLabel, "CN=");
			dwTotalRdnLen += 3;
		}
		else
		  if ( !strnicmp((const char*)pbData, szOID_COUNTRY_NAME, cbData) )
		  {
		 	  lstrcpy(szLabel, "C=");
			  dwTotalRdnLen += 2;
		  }
		  else
			if ( !strnicmp((const char*)pbData, szOID_ORGANIZATION_NAME, cbData) )
			{
				lstrcpy(szLabel, "O=");
				dwTotalRdnLen += 2;
			}
			else
			  if ( !strnicmp((const char*)pbData, szOID_ORGANIZATIONAL_UNIT_NAME, cbData) )
			  {
				  lstrcpy(szLabel, "OU=");
				  dwTotalRdnLen += 3;
			  }
			  else
				if ( !strnicmp((const char*)pbData, szOID_TITLE, cbData) )
				{
					lstrcpy(szLabel, "T=");
					dwTotalRdnLen += 2;
				}
				else
				  if( !strnicmp((const char*)pbData, szOID_LOCALITY_NAME, cbData) )
				  {
					 lstrcpy(szLabel, "L=");
					 dwTotalRdnLen += 2;
				  }
				  else
				    if( !strnicmp((const char*)pbData, szOID_RSA_emailAddr, cbData) )
					{
						lstrcpy(szLabel, "E=");
						dwTotalRdnLen += 2;
					}
					else
					{
						// We don't support this RDN
						dtSet = dtSet->nextDERTree;
						continue;
					}
		
		dwTotalRdnLen += cbValueData;

		// Copy the value of this OID into the O/P string
		if ( NULL != psz && 0 < csz )
		{
			if ( psz[0] != '\0' )
				dwTotalRdnLen += 2;		// For ';' and 'space'

			
			// Check if enough space is left in the string to copy this OID value
			// 'dwSize' includes the NULL terminating character
			if ( csz - 1 >= dwTotalRdnLen )
			{
				if ( psz[0] != '\0' )
					lstrcat(psz, "; ");

				lstrcat(psz, szLabel);
				UINT len = lstrlen(psz);
				strncpy(&psz[len], (const char*)pbValueData, cbValueData);
				psz[len + cbValueData] = '\0';
			}
			else
			{
				psz[0] = '\0';
				dwTotalRdnLen = 0;
				break;
			}
		}
		else
		{
			if ( NULL != dtSet->nextDERTree )
				dwTotalRdnLen += 2;		// For ';' and 'space'
		}

		dtSet = dtSet->nextDERTree;
	}	// while ( NULL != dtSet )

	return dwTotalRdnLen + 1;
}


HRESULT VSSC_HashData(int i_nHashAlg,BYTE  *pInputData, DWORD InputDataLength,
										  BYTE	**pbyteHash,DWORD   *pdwHashLength)
{
	
		void*		pvHashCtxt;
		int			nResult;

		hr=S_OK;

		if(HashBegin(i_nHashAlg, &pvHashCtxt) == -1)
		{
			hr=E_HASH_BEGIN_FAILED;
			return hr ;
		}

	    nResult=HashData(i_nHashAlg,pvHashCtxt,(unsigned char*) pInputData,
						(unsigned int) InputDataLength	);
		if (nResult!=0 )
		{
			hr=E_HASH_DATA_FAILED;
			return hr;
		}
		
		//Allocate memory for the hash algorithm
		switch(i_nHashAlg)
		{
		case HASH_SHA1 :
			*pdwHashLength = 20;
			*pbyteHash=(BYTE *)malloc(20);
			break;

		case HASH_MD2 :
		case HASH_MD5:
			*pdwHashLength = 16;
			*pbyteHash = (BYTE *)malloc(16);
			break;

		default :
			//hr = E_INVALIDFLAGS;
			break;
		}

		if(HashEnd(i_nHashAlg,pvHashCtxt,(unsigned char*)*pbyteHash,*pdwHashLength) == -1)
		{
			hr=E_HASH_END_FAILED;
			return hr;
		}
			
		return hr;
}

bool GetEndEntityCert(VS_CERT_BLOB CertSet, PVS_CERT_BLOB EndEntityCert)
{
	CBaseDERCollection cbdcCertSet(CertSet.cbData, CertSet.pbData);

	CBaseDERHierarchy cbdhCertSet(cbdcCertSet);
	if(cbdhCertSet.dwErrorCode == 0xFFFFFFFF)
	{
		return false;
	}

	DERTree* dtCertSeq = &cbdhCertSet.m_DERTree;
	
	//DERTree *dtCertSeqPrev;

	DERTree *dtCertSeqPrev=NULL;

	//End Entity cert is the last one.
	while(dtCertSeq)
	{
		dtCertSeqPrev = dtCertSeq;
		dtCertSeq = dtCertSeq->nextDERTree;
	}
	
	EndEntityCert->cbData = dtCertSeqPrev->currentBaseDER->BaseDERBlob->cbData;
	EndEntityCert->pbData = (unsigned char*)malloc(EndEntityCert->cbData);
	memcpy(EndEntityCert->pbData, dtCertSeqPrev->currentBaseDER->BaseDERBlob->pbData, EndEntityCert->cbData);
	
	return true;
}

HRESULT	UnPadDataForVerify(const BYTE*	i_cpbyteData,const DWORD	i_cdwDataLen,
						   BYTE**	o_ppbyteUnPaddedData,DWORD*	o_pdwUnPaddedDataLen)
{
	HRESULT						hResult						=	E_FAIL;


	DWORD						dwLengthOfPadding			=	0;
	DWORD						dwNumOfFFs					=	0;

	BOOL						boolSuccessFlag				=	TRUE;

	while (1)
	{
		//	check if the length of the data is equal to the length of the modulus of the key
		//
		//	this is the block length for assymetric operations
		/* Need to pass the modulus as an input
		if ( i_cdwDataLen != (RSA_Verify_PublicKey.modulus).len )
		{
			hResult =	E_FAIL;
			break;
		}
		*/

		//
		//	the padding is of the form
		//	0x00 0x01 0xFF....0xFF 0x00
		//

				//	check the 0x00
		if ( 0x00 != i_cpbyteData [0] )
		{
			hResult =	E_FAIL;
			break;
		}

				//	check the 0x01
		if ( 0x01 != i_cpbyteData [1] )
		{
			hResult =	E_FAIL;
			break;
		}

				//	get the number of 0xFF
		while ( 0x00 != i_cpbyteData [2 + dwNumOfFFs] )
		{
			if ( 0xFF != i_cpbyteData [2 + dwNumOfFFs] )
			{
				hResult =	E_FAIL;
				boolSuccessFlag =	FALSE;
				break;
			}

			dwNumOfFFs ++;
		}

		if ( FALSE == boolSuccessFlag )
		{
			break;
		}

			//	calculate the total length of padding. it should be atleast 11 bytes. if its less
			//	then return error
		dwLengthOfPadding =	dwNumOfFFs + 3; // not sure why we are getting extra 16 unwanted bytes
		if ( RSA_MIN_PAD_LEN > dwLengthOfPadding )
		{
			hResult =	E_FAIL;
			break;
		}

		*o_pdwUnPaddedDataLen =	i_cdwDataLen - dwLengthOfPadding ;

			//	allocate memory
		*o_ppbyteUnPaddedData =	new BYTE [*o_pdwUnPaddedDataLen];
		//CHECK_ALLOCATED_MEMORY (*o_ppbyteUnPaddedData)

				//	copy data into out buffer
		memcpy
		(
			(void*) *o_ppbyteUnPaddedData,
			(const void*) &(i_cpbyteData [dwLengthOfPadding]),
			*o_pdwUnPaddedDataLen
		);

		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	




HRESULT  GetDataFromSequence(const BYTE* i_cpbyteDataInSequence,const DWORD	i_cdwDataLenInSequence,
	const DWORD			i_cdwAlgID,	BYTE** 	o_ppbyteData,DWORD*	o_pdwDataLen)
{
	HRESULT						hResult						=	E_FAIL;

	_DERTree*					pstructDataSequence			=	NULL;
	_DERTree*					pstructAlgoID				=	NULL;
	_DERTree*					pstructObjectId				=	NULL;
	_DERTree*					pstructData					=	NULL;

	CHAR						szAlgoID [MAX_PATH];
	int							nStrCmp						=	999;

//	CSequence*					pCSeqAlgoID					=	NULL;
//	CObjectIdentifier*			pCoiAlgoID					=	NULL;

	while (1)
	{
			//	copy the data in sequence in a temp base DER collection
		CBaseDERCollection	CbdcData ( (_DWORD) i_cdwDataLenInSequence, (_BYTE*) i_cpbyteDataInSequence );

			//	copy the collection into a hierarchy
		CBaseDERHierarchy	CbdhData ( CbdcData );

		pstructDataSequence =	&(CbdhData.m_DERTree);
		if ( NULL != pstructDataSequence )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructDataSequence -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	this will point to the algo sequence
		pstructAlgoID =	pstructDataSequence -> rightDERTree;
		if ( NULL != pstructAlgoID )
		{
					//	check if its a sequence
			if ( SEQUENCE != ( (pstructAlgoID -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}
				//	this will point to the object identifier
		pstructObjectId =	pstructAlgoID -> rightDERTree;
		if ( NULL != pstructObjectId )
		{
					//	check if its a object identifier
			if ( OBJECT_IDENTIFIER != ( (pstructObjectId -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	copy the object identifier into the string
		memcpy
		(
			(void*) szAlgoID,
			(const void*) (pstructObjectId -> currentBaseDER) -> pbData,
			(pstructObjectId -> currentBaseDER) -> cbData
		);

		szAlgoID [ (pstructObjectId -> currentBaseDER) -> cbData ] =	NULL;

		switch ( i_cdwAlgID )
		{
			case	VS_SHA_1:
				nStrCmp =	lstrcmp ( szAlgoID, VS_SHA1_OID );
				break;

			case	VS_MD2:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD2_OID );
				break;

			case	VS_MD5:
				nStrCmp =	lstrcmp ( szAlgoID, VS_MD5_OID );
				break;

			default:
				break;
		}

		if ( 0 != nStrCmp )
		{
			hResult =	NTE_BAD_SIGNATURE;
			break;
		}

				//	this will point to the data OCTET STRING
		pstructData =	pstructAlgoID -> nextDERTree;
		if ( NULL != pstructData )
		{
					//	check if its a octet string
			if ( OCTET_STRING != ( (pstructData -> currentBaseDER) -> Type ) )
			{
				hResult =	NTE_BAD_SIGNATURE;
				break;
			}
		}

				//	allocate memory for the data
		*o_pdwDataLen =	(pstructData -> currentBaseDER) -> cbData;
		*o_ppbyteData =	new BYTE [*o_pdwDataLen];
		

				//	copy the data into the out buffer
		memcpy
		(
			(void*) *o_ppbyteData,
			(const void*) (pstructData -> currentBaseDER) -> pbData,
			*o_pdwDataLen
		);
			
		hResult =	S_OK;
		break;
	}	//	end		while (1)

	return	hResult;
}	
/*
HRESULT GetRSAKeyFromKeyInfo(CERT_PUBLIC_KEY_INFO& i_CertPublicKeyInfo, A_RSA_KEY* o_pTheKey)
{
	HRESULT retVal = S_OK;

	o_pTheKey->modulus.data = o_pTheKey->exponent.data = NULL;
	
	CBaseDERCollection cbdcTheKeySeq(i_CertPublicKeyInfo.PublicKey.cbData, i_CertPublicKeyInfo.PublicKey.pbData);
	CBaseDERHierarchy cbdhTheKeySeq(cbdcTheKeySeq);
	DERTree* pdtTheKeySeq = &cbdhTheKeySeq.m_DERTree;
	if(!pdtTheKeySeq && pdtTheKeySeq->currentBaseDER->Type != SEQUENCE)
	{
		retVal = -1;
	}
	else
	{
		//*Get the modulus
		DERTree* pdtTheMod = pdtTheKeySeq->rightDERTree;
		if(!pdtTheMod && pdtTheMod->currentBaseDER->Type != UNIVERSAL_INTEGER)
		{
			retVal = -1;
		}
		else
		{
			PBYTE pbyteRawData;

			o_pTheKey->modulus.len = pdtTheMod->currentBaseDER->cbData;
			o_pTheKey->modulus.data = new BYTE[o_pTheKey->modulus.len];

			pbyteRawData = pdtTheMod->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheMod->currentBaseDER->BaseDERBlob->cbData - pdtTheMod->currentBaseDER->cbData);

			if(*pbyteRawData)
				memcpy(o_pTheKey->modulus.data, pbyteRawData,o_pTheKey->modulus.len);
			else if(o_pTheKey->modulus.len > 1)
			{
				o_pTheKey->modulus.len --;
				memcpy(o_pTheKey->modulus.data, pbyteRawData+1,o_pTheKey->modulus.len);
			}
			else
				retVal = -1;

		}

		//Get the exponent
		DERTree* pdtTheExp;
		if(retVal == S_OK)
		{
			pdtTheExp = pdtTheMod->nextDERTree;
			if(!pdtTheExp && pdtTheExp->currentBaseDER->Type != UNIVERSAL_INTEGER)
			{
				retVal = E_INVALIDASNKEYENC;
			}
			else
			{
				PBYTE pbyteRawData;

				o_pTheKey->exponent.len = pdtTheExp->currentBaseDER->cbData;
				o_pTheKey->exponent.data = new BYTE[o_pTheKey->exponent.len];

				pbyteRawData = pdtTheExp->currentBaseDER->BaseDERBlob->pbData + 
									(pdtTheExp->currentBaseDER->BaseDERBlob->cbData - pdtTheExp->currentBaseDER->cbData);
				if(*pbyteRawData)
					memcpy(o_pTheKey->exponent.data, pbyteRawData,o_pTheKey->exponent.len);
				else if(o_pTheKey->exponent.len > 1)
				{
					o_pTheKey->exponent.len --;
					memcpy(o_pTheKey->exponent.data, pbyteRawData+1,o_pTheKey->exponent.len);
				}
				else
					retVal = -1;
			}

		}
	}

	return retVal;
}
*/


HRESULT  AddRFC822Header(VSSCMessage *Msg,CMsg *pCMsg)
{
	HRESULT hr=S_OK;

	do
	{
		if(pCMsg->m_bstrFrom.length() > 0)
		{
			Msg->GetHeaders().GetFrom().SetString((TCHAR*)pCMsg->m_bstrFrom);
		}
		
		// To
		if(pCMsg->m_bstrTo.length()>0)
		{
			Msg->GetHeaders().GetTo().SetString((TCHAR*)pCMsg->m_bstrTo);
		}

		// Cc
		if(pCMsg->m_bstrCc.length()>0)
		{
			Msg->GetHeaders().GetCc().SetString((TCHAR*)pCMsg->m_bstrCc);
		}

		// Bcc
		if(pCMsg->m_bstrBcc.length()>0)
		{
			Msg->GetHeaders().GetBcc().SetString((TCHAR*)pCMsg->m_bstrBcc);
		}


			// Date
		char szDate[256];
		FormatRFC822Date(szDate);
				  
		Msg->GetHeaders().GetDate().SetString(szDate);


		// Subject
		if(pCMsg->m_bstrSubject.length()> 0)
		{
			Msg->GetHeaders().GetSubject().SetString((TCHAR*)pCMsg->m_bstrSubject);
		}
	}
	while(0);

	return hr;

}


HRESULT GetMsgHeader(MSGINFO *MsgInfo,CMsg *pCMsg)
{
	int i=0;
	HRESULT		hr=S_OK;
	

	do
	{
		/////From
		if(strlen(MsgInfo->szFrom)>0)
		{
			
			pCMsg->m_bstrFrom=MsgInfo->szFrom;
		}
		
		/////To
		////strip <>

		if(MsgInfo->szTo)
		{
			//char *TmpBuf=strdup(MsgInfo->szTo);
			char *TmpBuf=(char*)malloc(strlen(MsgInfo->szTo)+1);
			strcpy(TmpBuf,MsgInfo->szTo);

			while(MsgInfo->szTo[i])
			{
				if(MsgInfo->szTo[i] == '<' || MsgInfo->szTo[i] == '>')
					TmpBuf[i] = ' ' ;
				else
					TmpBuf[i] = MsgInfo->szTo[i];
				i++;
			}
			TmpBuf[i] = '\0';
			
			
			pCMsg->m_bstrTo=TmpBuf;

			FREE_MEMORY(TmpBuf);
		}

		/////Cc
		if(MsgInfo->szCC)
		{
			
			pCMsg->m_bstrCc=MsgInfo->szCC;
		}
		
		/////Bcc
		if(MsgInfo->szBCC)
		{
			
			pCMsg->m_bstrBcc=MsgInfo->szBCC;
		}
		

		if(strlen(MsgInfo->szSubject)>0)
		{
			
			pCMsg->m_bstrSubject=MsgInfo->szSubject;
		}
		if(strlen(MsgInfo->szDate)>0)
		{
			
			pCMsg->m_bstrDate=MsgInfo->szDate;
		}

	}
	while(0);

	return hr;

}

HRESULT  FormatMIMEEntityForSigning(CMsg *pCMsg,char **szSMIMEEntity)
{
	HRESULT		   hr=S_OK;
	ENTITYINFO     BodyInfo;
	bool		   bDropHeader=false;

	do
	{
		
		memset(&BodyInfo,0,sizeof(ENTITYINFO));

		strcpy(BodyInfo.szType,"TEXT");
		strcpy(BodyInfo.szSubType,"Plain");
		strcpy(BodyInfo.szCte,"7bit");
		BodyInfo.szBody =(TCHAR*)pCMsg->m_bstrBody;

		if(pCMsg->m_bstrAttachFileNameList.length()>0 ||
							pCMsg->m_FILEINFO_AttachFileInfoList!=NULL)
		{
			hr=GetAttachments(
								pCMsg->m_bstrAttachFileNameList,
								&pCMsg->m_FILEINFO_AttachFileInfoList
							 );
			if(hr!=S_OK)
			{
				g_dwAppErr=E_UNABLE_TO_ATTACH;
				break;
			}
		}


		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "CreateSMIMEEntity-Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif	


		if(!pCMsg->m_bOpaqueSign)
		{
			// vsscEntityStr is the entity data which should be used for signing or encryption.
			CreateSMIMEEntity(
							 pCMsg->m_FILEINFO_AttachFileInfoList,
							 &BodyInfo,
							 szSMIMEEntity,
							 FALSE
							 );
			if(*szSMIMEEntity==NULL)
			{
				hr=E_OUTOFMEMORY;
				break;
			}
		}
		else
		{
			if(pCMsg->m_FILEINFO_AttachFileInfoList!=NULL)
			{
				// vsscEntityStr is the entity data which should be used for signing or encryption.
				CreateSMIMEEntity(
								  pCMsg->m_FILEINFO_AttachFileInfoList,
								  &BodyInfo,
								  szSMIMEEntity,
								  FALSE
								  );
				if(*szSMIMEEntity==NULL)
				{
					hr=E_OUTOFMEMORY;
					
					break;
				}

			}
			else
			{
			
				if(pCMsg->m_bAddMIMEHeader)
					bDropHeader=false;
				else
				    bDropHeader=true;

				// vsscEntityStr is the entity data which should be used for signing or encryption.
				CreateSMIMEEntity(
								  pCMsg->m_FILEINFO_AttachFileInfoList,
								  &BodyInfo,
								  szSMIMEEntity,
								  bDropHeader
								  );
				if(*szSMIMEEntity==NULL)
				{
					hr=E_OUTOFMEMORY;
					
					break;
				}

			}

		}
	}while(0);

	return hr;

}


void ParseFileList(char *szFileTitle, char *szFileList, FILEINFO *pFileInfo,
				   ATTACH_FILE_INFO	*pAttachedFiles,char **szOutputFileList, BOOL& bDuplicate)
{

	bDuplicate = FALSE;

		// check if it contains multiple files. If more than one file is selected
		// file tile will be blank. If only one file is selected, it needs to be handled
	    // in a different way
	if(strcmp(szFileTitle,"") != 0) {
			// only one file was selected
		if(CheckForDuplicateFile(szFileTitle, pFileInfo,pAttachedFiles)) {
			bDuplicate = TRUE;
			return;
		}

		int len = strlen(szFileList);
		*szOutputFileList = (char *)malloc(len+1);
		memset(*szOutputFileList,0,len+1);
		memcpy(*szOutputFileList,szFileList,len);		
		return;
	}


      // user selected multiple files. File list will be of the format:
	  // directoryname\0filename1\0filename2\0....filenamen\0\0

	  // get directory name (upto first NULL character)
	char *szDirectory;
	int directoryLen = strlen(szFileList);
	szDirectory = (char *)malloc(directoryLen+2);
	memset(szDirectory,0,directoryLen+2);
	memcpy(szDirectory,szFileList,directoryLen);	
	szDirectory[directoryLen] = '\\';

	int offset = directoryLen;
	int outputLen = 0;

	// find out the total length of file names including directory name
	while(true) 
	{

		if(memcmp(szFileList + offset, "\0\0", 2) == 0)
			break;


		if(CheckForDuplicateFile(szFileList + offset + 1, pFileInfo,pAttachedFiles)) {
			bDuplicate = TRUE;
			offset += strlen(szFileList + offset + 1) + 1;
			continue;
		}

		outputLen += directoryLen + 1 + strlen( szFileList + offset + 1) + 1;

		offset += strlen(szFileList + offset + 1) + 1;

	}


	*szOutputFileList = (char *)malloc(outputLen + 1);
	memset(*szOutputFileList, 0, outputLen + 1);

	// construct comma separated file list with full path name
	offset = directoryLen;
	while(true) 
	{

		if(memcmp(szFileList + offset, "\0\0", 2) == 0)
			break;

		if(CheckForDuplicateFile(szFileList + offset + 1, pFileInfo,pAttachedFiles)) {
			offset += strlen(szFileList + offset + 1) + 1;
			continue;
		}

		strcat(*szOutputFileList, szDirectory);
		strcat(*szOutputFileList, szFileList + offset + 1);
		strcat(*szOutputFileList, ",");

		offset += strlen(szFileList + offset + 1) + 1;

	}
	free(szDirectory);
}

BOOL CheckForDuplicateFile(
						   char *szFile,
						   FILEINFO *pFileInfo,
						   ATTACH_FILE_INFO *pAttachedFiles
						   )
{


	CAttachInfo *pInsAttachInfo;
	ATTACH_FILE_INFO::iterator i;

	 // check if there are any attached files already
	if(szFile == NULL)
		return FALSE;

	/////////////////
	for (i =  pAttachedFiles->begin(); i != pAttachedFiles->end(); ++i)
	{
			if (pAttachedFiles->empty())
					break;
				
			pInsAttachInfo=(*i);
			if(pInsAttachInfo->m_bstrFileName==_bstr_t(szFile))
			{
				return TRUE;
				
			}
       
	}


	FILEINFO *pTmpFileInfo = pFileInfo;

	while(pTmpFileInfo)
	{
	
		if(_bstr_t(szFile) == _bstr_t(pTmpFileInfo->szFileName))
		{
			return TRUE;
			
		}

		pTmpFileInfo = pTmpFileInfo->next;
	}

	return FALSE;
}

void GetFileName(char *szPathName,char**szFileName)
{
	
	   char *szTmpFileName=(char*)malloc(lstrlen(szPathName)+1);
	   *szFileName=(char*)malloc(lstrlen(szPathName)+1);

	   lstrcpy(szTmpFileName,szPathName);
	   		
	   char *last=strrchr(szTmpFileName,'\\');
	   int   offset;

	   offset=last-szTmpFileName+1;

	   lstrcpy(*szFileName,szTmpFileName+offset);

	   FREE_MEMORY(szTmpFileName)

}


HRESULT  GetAttachments(char *szFileList,FILEINFO **o_pFileInfo)
{
	HRESULT hr=S_OK;
	
	
	FILE *fp = NULL;
	unsigned int nFileSize=0;
	char *szFileData = NULL;

	unsigned int dwEncodedSize=0;
	char *szEncodedFileData = NULL;

	char *szFileName=NULL;
	char *szFileNameList=NULL;

	

	FILEINFO *pFileInfo, *pFileInfoPrev, *START,*pTempFileInfo=NULL ;

	//FILEINFO *poutFileInfo, *poutFileInfoPrev, *outSTART;
	pFileInfo = pFileInfoPrev = START = NULL;
	//poutFileInfo = poutFileInfoPrev = outSTART = NULL;
		
	if(*o_pFileInfo != NULL)
	{
		
		START = *o_pFileInfo;
		pTempFileInfo = *o_pFileInfo;

		while(pTempFileInfo)
		{
			pFileInfoPrev = pTempFileInfo;
			pTempFileInfo = pTempFileInfo->next;
		}
	}

	if(lstrlen(szFileList)==0)
		goto End;

	//szFileNameList=strdup(szFileList);
	szFileNameList=(char*)malloc(strlen(szFileList)+1);
	memset(szFileNameList,0,strlen(szFileList)+1);
	memcpy(szFileNameList,szFileList,strlen(szFileList));
	szFileNameList[strlen(szFileList)]='\0';

	szFileName=strtok(szFileNameList,",");
		
	
	while(szFileName!= NULL)
	{
		fp = fopen(szFileName, "rb");
		if(fp == NULL)
		{			
			hr=HRESULT_FROM_WIN32(GetLastError());
			
			break;
		}
		fseek(fp, 0, SEEK_END);
		nFileSize = ftell(fp);
		rewind(fp);

		if(nFileSize!=0)
		{
			szFileData = (char *)malloc(nFileSize);
			memset(szFileData,0,nFileSize);
			fread(szFileData, 1, nFileSize, fp);
		}
		fclose(fp);

		if(szFileData!=NULL && nFileSize!=0)
		{
			_Base64Encode((char*)szFileData, nFileSize, NULL, &dwEncodedSize);
			szEncodedFileData = (char*)malloc(dwEncodedSize + 1);

			if(szEncodedFileData==NULL)
			{
				hr=E_OUTOFMEMORY;
				
			}
			
			
			_Base64Encode((char *)szFileData, nFileSize, szEncodedFileData, &dwEncodedSize);
			szEncodedFileData[dwEncodedSize] = '\0';

			if(szFileData!=NULL)
					free(szFileData);
		}


		/////Fixed size  
		char  szFileNameOnly[256];
		//char *szTmpFileName=strdup(szFileName);

		char *szTmpFileName=(char*)malloc(strlen(szFileName)+1);
		memset(szTmpFileName,0,strlen(szFileName));
		memcpy(szTmpFileName,szFileName,strlen(szFileName));
		szTmpFileName[strlen(szFileName)]='\0';

		
		char *last=strrchr(szTmpFileName,'\\');
		int offset;

		offset=last-szTmpFileName+1;
		strcpy(szFileNameOnly,szTmpFileName+offset);
		FREE_MEMORY(szTmpFileName)
		///////
				


		if(START == NULL)
		{
			pFileInfo = (FILEINFO*)malloc(sizeof(FILEINFO));
			memset(pFileInfo, 0, sizeof(FILEINFO));
			

			//strcpy(pFileInfo->szFileName, szFileName);

			strcpy(pFileInfo->szFileName, szFileNameOnly);	
			strcpy(pFileInfo->szType, "Text");	
			strcpy(pFileInfo->szSubType, "Plain");	
			strcpy(pFileInfo->szCte, "base64");
			
			if(szEncodedFileData!=NULL,dwEncodedSize!=0)
			{
				pFileInfo->cbFileSize = dwEncodedSize;
				pFileInfo->pbFileData = (unsigned char *)malloc(dwEncodedSize);
				memset(pFileInfo->pbFileData, 0, dwEncodedSize);
				memcpy(pFileInfo->pbFileData, szEncodedFileData, dwEncodedSize);
			}
			else
			{
				pFileInfo->cbFileSize = dwEncodedSize;
				pFileInfo->pbFileData = NULL;

			}

			pFileInfo->next = NULL;
			START = pFileInfoPrev = pFileInfo;
			
		}
		else
		{
			pFileInfo = (FILEINFO*)malloc(sizeof(FILEINFO));
			memset(pFileInfo, 0, sizeof(FILEINFO));
			

			//strcpy(pFileInfo->szFileName, szFileName);
			
			strcpy(pFileInfo->szFileName, szFileNameOnly);
			strcpy(pFileInfo->szType, "Text");	
			strcpy(pFileInfo->szSubType, "Plain");	
			strcpy(pFileInfo->szCte, "base64");


			if(szEncodedFileData!=NULL,dwEncodedSize!=0)
			{
				pFileInfo->cbFileSize = dwEncodedSize;
				pFileInfo->pbFileData = (unsigned char *)malloc(dwEncodedSize);
				memset(pFileInfo->pbFileData,0, dwEncodedSize);
				memcpy(pFileInfo->pbFileData, szEncodedFileData, dwEncodedSize);
			}
			else
			{
				pFileInfo->cbFileSize = dwEncodedSize;
				pFileInfo->pbFileData = NULL;

			}
			
			pFileInfo->next = NULL;
			pFileInfoPrev->next = pFileInfo;
			pFileInfoPrev = pFileInfo;
			
		}

		szFileName=strtok(NULL,",");
		if(szEncodedFileData!=NULL)
				free(szEncodedFileData);
		

	}

End:

		*o_pFileInfo=START;

	FREE_MEMORY(szFileNameList)

	return hr;
}

HRESULT  GM_PutMsgHeader(CMsg *pCMsg)
{

	HRESULT hr=S_OK;

	void    *g_pHeadres;
	char	*szHeaders;


	do
	{
		VSSCMessage *Msg = VSSCMessage :: NewMessage("",0);
				
		hr=AddRFC822Header(Msg,pCMsg);
		Msg->Assemble();

		CHECK_HRESULT_BREAK
	
		VSSCHeaders& headers = Msg->GetHeaders();
		VSSCString vsscHeaders = headers.GetString();
		szHeaders = vsscHeaders.GetString();
	
		DWORD  dwLen=strlen(szHeaders)+1;

		hr=gp_GMemMgmt->VS_AllocateMemory(
								(BYTE *)&(pCMsg->m_iMsgObjID),
								sizeof(int),
								VSSC_MESSAGE_HEADER,
								dwLen,
								&g_pHeadres
								);
		CHECK_HRESULT_BREAK

		memcpy(g_pHeadres,szHeaders,dwLen);

	}
	while(0);

	return hr;


}

HRESULT  GM_GetMsgHeader(CMsg *pCMsg)
{
	hr=S_OK;
	DWORD	  o_pdwMemBlobLen=0;
	void     *o_ppvoidMemory;
	_bstr_t  bstrMsgHeader;

	do
	{
		
			hr=gp_GMemMgmt->VS_GetMemoryBlob(
									(BYTE*)&pCMsg->m_iMsgObjID,
									sizeof(int),
									VSSC_MESSAGE_HEADER,
									&o_pdwMemBlobLen,
									&o_ppvoidMemory
									);	
			CHECK_HRESULT_BREAK
					
			//////parse the headers
			VSSCMessage *msg = VSSCMessage :: NewMessage((char*)o_ppvoidMemory, 0);
			msg->Parse();
			

			SimpleMessage SMsg(msg);
					// From
			VSSCString vsscFrom = SMsg.GetFrom();
			char *szFrom = vsscFrom.GetString();

			if(szFrom != NULL && strlen(szFrom) > 0)
			{
				bstrMsgHeader=szFrom;
				pCMsg->m_bstrFrom=bstrMsgHeader.copy();
				
			}
			

			// To
			VSSCString vsscTo = SMsg.GetTo();
			char *szTo = vsscTo.GetString();

			if(szTo != NULL && strlen(szTo) > 0)
			{
				bstrMsgHeader=szTo;
				pCMsg->m_bstrTo=bstrMsgHeader.copy();
				
			}

			// Cc
			VSSCString vsscCc = SMsg.GetCc();
			char *szCc = vsscCc.GetString();

			if(szCc != NULL && strlen(szCc) > 0)
			{
				bstrMsgHeader=szCc;
				pCMsg->m_bstrCc=bstrMsgHeader.copy();
				
			}

			// Bcc
			VSSCString vsscBcc = SMsg.GetBcc();
			char *szBcc = vsscBcc.GetString();

			if(szBcc != NULL && strlen(szBcc) > 0)
			{
				bstrMsgHeader=szBcc;
				pCMsg->m_bstrBcc=bstrMsgHeader.copy();
				
			}


			// Date
			VSSCString vsscDate = SMsg.GetDate();
			char *szDate = vsscDate.GetString();

			if(szDate != NULL && strlen(szDate) > 0)
			{
				bstrMsgHeader=szDate;
				pCMsg->m_bstrDate=bstrMsgHeader.copy();
				
			}

			// Subject
			VSSCString vsscSubject = SMsg.GetSubject();
			char *szSubject = vsscSubject.GetString();

			if(szSubject != NULL && strlen(szSubject) > 0)
			{
				bstrMsgHeader=szSubject;
				pCMsg->m_bstrSubject=bstrMsgHeader.copy();
				
			}

				


	}
	while(0);

	return hr;

}

HRESULT  GM_PutMsgBody(CMsg *pCMsg)
{

	HRESULT hr=S_OK;
	void    *g_pBody;
	do
	{
		if(pCMsg->m_bstrBody.length()>0)
		{
	
			DWORD  dwLen=pCMsg->m_bstrBody.length()+1;
			hr=gp_GMemMgmt->VS_AllocateMemory(
								(BYTE *)&(pCMsg->m_iMsgObjID),
								sizeof(int),
								VSSC_MESSAGE_BODY,
								dwLen,
								&g_pBody
								);
			CHECK_HRESULT_BREAK
			memcpy(g_pBody,(TCHAR*)pCMsg->m_bstrBody,dwLen);
		}

	}
	while(0);

	return hr;


}

HRESULT  GM_GetMsgBody(CMsg *pCMsg)
{
	hr=S_OK;
	DWORD	  dwMemBlobLen=0;
	void     *pvoidMemory;
	
	do
	{
		
			hr=gp_GMemMgmt->VS_GetMemoryBlob(
									(BYTE*)&pCMsg->m_iMsgObjID,
									sizeof(int),
									VSSC_MESSAGE_BODY,
									&dwMemBlobLen,
									&pvoidMemory
									);	
			if(hr==E_MEMORY_BLOB_TYPE_NOT_FOUND)
			{
				hr=S_OK;
				pCMsg->m_bstrBody="";
				break;
			}

			CHECK_HRESULT_BREAK
              
			pCMsg->m_bstrBody=_MultiToWideString((char*)pvoidMemory);
		

	}
	while(0);

	return hr;

}
HRESULT  GM_PutMsgAttFileNames(CMsg *pCMsg,ATTACH_FILE_INFO*pInsertAttInfo)
{
	HRESULT hr=S_OK;

	void    *g_pAttFileNames;
	
	CAttachInfo *pAttachInfo;
    ATTACH_FILE_INFO::iterator i;

	_bstr_t        bstrFormatInfo;
    _bstr_t        bstrAttInfo;
	

	do
	{
		if(pInsertAttInfo==NULL)
			break;


		if (!pInsertAttInfo->empty())
			{

			   bstrFormatInfo="";
			   bstrAttInfo="";
			   
			   for (i =  pInsertAttInfo->begin(); i != pInsertAttInfo->end(); ++i)
				{

					pAttachInfo=(*i);
									

					bstrAttInfo+=pAttachInfo->m_bstrPathName;
					bstrAttInfo+=_bstr_t(L",");

					
				}

			    DWORD dwLen=bstrAttInfo.length()+1;
				hr=gp_GMemMgmt->VS_AllocateMemory(
									(BYTE *)&(pCMsg->m_iMsgObjID),
									sizeof(int),
									VSSC_MESSAGE_ATT_FILE_NAMES,
									dwLen,
									&g_pAttFileNames
									);
				CHECK_HRESULT_BREAK
				memcpy(g_pAttFileNames,(TCHAR*)bstrAttInfo,dwLen);
 	   
			   
			}

		/////////

	}
	while(0);

	return hr;


}
HRESULT  GM_GetMsgAttFileNames(CMsg *pCMsg,ATTACH_FILE_INFO*pInsertAttInfo)
{
	hr=S_OK;

	////fixed size 



	TCHAR*		ptcszToken=NULL;
	TCHAR*		ptcszBuffer = NULL;
	
	
	DWORD	  dwMemBlobLen=0;
	void      *pvoidMemory=NULL;

	CAttachInfo       *pAttInfo=NULL;
	
	do
	{
		
			hr=gp_GMemMgmt->VS_GetMemoryBlob(
									(BYTE*)&pCMsg->m_iMsgObjID,
									sizeof(int),
									VSSC_MESSAGE_ATT_FILE_NAMES,
									&dwMemBlobLen,
									&pvoidMemory
									);	
			if(hr==E_MEMORY_BLOB_TYPE_NOT_FOUND)
			{
				hr=S_OK;
				pCMsg->m_bstrAttachFileNameList="";
				break;
			}

			CHECK_HRESULT_BREAK

            

			ptcszBuffer = (TCHAR*)malloc(_tcslen((TCHAR*)pvoidMemory)+1);
			CHECK_MEM_BREAK(ptcszBuffer)
            
			memset(ptcszBuffer,0,_tcslen((TCHAR*)pvoidMemory)+1);
			memcpy(ptcszBuffer,(TCHAR*)pvoidMemory,_tcslen((TCHAR*)pvoidMemory));
			ptcszBuffer[_tcslen((TCHAR*)pvoidMemory)]=_T('\0');

			FILE *stream = NULL;
				
			ptcszToken=_tcstok(ptcszBuffer,_T(","));
			while(ptcszToken!=NULL)
			{
				
					//sscanf((TCHAR*)ptcszToken,"%s %s %d",szPathName,
					//	szFileName,&dwFileSize);

					pAttInfo=new CAttachInfo;

					stream = fopen((TCHAR*)ptcszToken, "rb");
					if(stream==NULL)
					{
						hr=HRESULT_FROM_WIN32(GetLastError());
						break;
					}
					fseek(stream, 0, SEEK_END);
					pAttInfo->m_dwFileSize = ftell(stream);
					rewind(stream);
					fclose(stream);

					pAttInfo->m_bstrPathName=ptcszToken;

					/////Find Name 
					char  szFileNameOnly[MAX_PATH];
					char *szTmpFileName=(char*)malloc(strlen(ptcszToken)+1);
					CHECK_MEM_BREAK(szTmpFileName)

					strcpy(szTmpFileName,ptcszToken);
					char *last=strrchr(szTmpFileName,'\\');
					int offset;
					offset=last-szTmpFileName+1;
					strcpy(szFileNameOnly,szTmpFileName+offset);
					pAttInfo->m_bstrFileName=szFileNameOnly;
														
					pInsertAttInfo->insert(pInsertAttInfo->begin(),pAttInfo);
					ptcszToken=_tcstok(NULL,_T(","));
			}


	}
	while(0);

	//FREE_MEMORY(pvoidMemory)
	FREE_MEMORY(ptcszBuffer)

	return hr;

}

HRESULT  GM_PutMsgEntity(CMsg *pCMsg)
{
	hr=S_OK;
	void     *g_pMIMEEntity;
	char     *szSMIMEEntity=NULL;

	do
	{

		if(pCMsg->m_bstrBody.length()>0 ||pCMsg->m_FILEINFO_AttachFileInfoList!=NULL)
		{
			//////Format  Body and Attachment in MIME Entity
			ENTITYINFO     BodyInfo;
			memset(&BodyInfo,0,sizeof(ENTITYINFO));

			strcpy(BodyInfo.szType,"TEXT");
			strcpy(BodyInfo.szSubType,"Plain");
			strcpy(BodyInfo.szCte,"7bit");
			if(pCMsg->m_bstrBody.length()>0)
				BodyInfo.szBody=(TCHAR*)pCMsg->m_bstrBody;

			if(!pCMsg->m_ReplyAddAttachment)
			{
				if(pCMsg->m_FILEINFO_AttachFileInfoList!=NULL)
				{
						freeFileInfo(pCMsg->m_FILEINFO_AttachFileInfoList);
						pCMsg->m_FILEINFO_AttachFileInfoList=NULL;
				}		

			}
	
			CreateSMIMEEntity(pCMsg->m_FILEINFO_AttachFileInfoList, &BodyInfo, &szSMIMEEntity,FALSE);

			DWORD   dwLen=strlen(szSMIMEEntity)+1;
		
			hr=gp_GMemMgmt->VS_AllocateMemory(
									(BYTE *)&(pCMsg->m_iMsgObjID),
									sizeof(int),
									VSSC_MESSAGE_ENTITY,
									dwLen,
									&g_pMIMEEntity
									);
			CHECK_HRESULT_BREAK

			memcpy(g_pMIMEEntity,szSMIMEEntity,dwLen);

			FREE_MEMORY(szSMIMEEntity);
		}

	}while(0);

	return hr;
}
HRESULT  GM_GetMsgEntity(CMsg *pCMsg)
{
	hr=S_OK;
	DWORD	  dwMemBlobLen=0;
	void      *pvoidMemory;

	BOOL      bRet=FALSE;

	do
	{

			hr=gp_GMemMgmt->VS_GetMemoryBlob(
									(BYTE*)&pCMsg->m_iMsgObjID,
									sizeof(int),
									VSSC_MESSAGE_ENTITY,
									&dwMemBlobLen,
									&pvoidMemory
									);	
			if(hr==E_MEMORY_BLOB_TYPE_NOT_FOUND)
			{
				hr=S_OK;
				pCMsg->m_bstrBody="";
				pCMsg->m_FILEINFO_AttachFileInfoList=NULL;
				break;
			}

			CHECK_HRESULT_BREAK
              

			ENTITYINFO     BodyInfo;
			memset(&BodyInfo,0,sizeof(ENTITYINFO));

			bRet=ParseMimeEntity((unsigned char*)pvoidMemory,dwMemBlobLen,&BodyInfo,
											&pCMsg->m_FILEINFO_AttachFileInfoList);
			if(!bRet)
				break;


			pCMsg->m_bstrBody=_MultiToWideString(BodyInfo.szBody);



	}
	while(0);

	return hr;

}

void TimetToFileTime( time_t t, LPFILETIME pft )
{
    LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
    pft->dwLowDateTime = (DWORD) ll;
    pft->dwHighDateTime = ll >>32;
}

BOOL CheckCertExpDate(DATE  dateEffDate,DATE dateExpDate)
{

	SYSTEMTIME      stSysTime;
	FILETIME        ftCertTimeOut;

	DATE			dtPlusCertTimeOut;
	time_t          tCertTimeout;

	time(&tCertTimeout);
	tCertTimeout+=g_dwCertTimeOut;
	
	TimetToFileTime(tCertTimeout,&ftCertTimeOut);
	
	if(!FileTimeToSystemTime(&ftCertTimeOut,&stSysTime))
	{
		return FALSE;
	}
	
	
	if(!SystemTimeToVariantTime(&stSysTime,&dtPlusCertTimeOut))
	{
		return FALSE;
	}

	
	if((dateEffDate<dtPlusCertTimeOut && dtPlusCertTimeOut<dateExpDate))
	{
		return TRUE;	
		
	}
	else
	{
		return FALSE;
	}

	
}
/*
	CheckCertStatus 
	return Value
				0-could not perform the resolution operation
				1-valid Certficates
				2-Revoked certificate
*/
int CheckCertStatus(DWORD dwStatus,CERT_STATUS_INFO *pstCertStatusInfo)
{
	int       nResult=0;

 
	/*
	Status ::= BIT STRING {
	resolutionType		(0-3),
	revocationType		(4-5),
	revocationSubType	(6-7),
	revocationStatus	(8-9),
	chainValidationType	(10-11),
	chainvalidationStatus	(12-13) 
	}
	*/

	
	pstCertStatusInfo->dwResolutionTypeBit=dwStatus & 0x000F;
	/*
		(0-3) bits
		0000	Could not perform User Certificate Resolution operation.
		0001	Found Encryption Certificate Signed PKCS #7
		0010	Found Signing Certificate X.509
		0011	Found Signing Certificate PKCS #7 with intermediate CA Certificates
		xxxx	All higher values are for future use
	*/
	if(pstCertStatusInfo->dwResolutionTypeBit==0)
	{
		//return 0;
	}

	pstCertStatusInfo->dwRevocationTypeBit=dwStatus & 0x0030;
	pstCertStatusInfo->dwRevocationTypeBit=pstCertStatusInfo->dwRevocationTypeBit >> 4;
	/*
		(4-5)bits
		00	CRLDP based revocation checking was performed on the certificate
			returned through the resolutionBlob field.
		01	OCSP based revocation checking was performed from the Server side
	*/

	if(pstCertStatusInfo->dwRevocationTypeBit==VS_REVOCATION_TYPE_OCSP)
	{
			pstCertStatusInfo->dwRevocationSubTypeBit= dwStatus & 0x00C0;
			pstCertStatusInfo->dwRevocationSubTypeBit=pstCertStatusInfo->dwRevocationSubTypeBit>>6;
	}

	/*
		(6-7) bits
		00	OCSP request was initiated from Server side and the OCSP response was
			parsed to determine if the certificate was revoked or not. In this 
			case, the revocationStatus bit field indicates if certificate was
			revoked or not.
		01	OCSP request was initiated from Server side and the OCSP response is
			present in the additionalInfo field of UserCertificateResponse.
			It is assumed that the client needs to verify the OCSP response. The
			client has hardcoded in it the Root Certificate which the OCSP Signing
			certificate chains to.
	*/
	 pstCertStatusInfo->dwRevocationStatusBit= dwStatus & 0x0300;
	 pstCertStatusInfo->dwRevocationStatusBit=pstCertStatusInfo->dwRevocationStatusBit>>8;	
	/*
		(8-9) bits
		00	Certificate not revoked
		01	Certificiate revoked
		11	Could not determine if certificate is revoked or not	
	*/

	//Revocation is done on Server Side with CRLDP
	if(pstCertStatusInfo->dwRevocationTypeBit == VS_REVOCATION_TYPE_CRLDP)
	{
		if((pstCertStatusInfo->dwRevocationStatusBit == VS_REV_STATUS_NOT_REV))
							pstCertStatusInfo->dwRevocationStatus=0;
		if(pstCertStatusInfo->dwRevocationStatusBit == VS_REV_STATUS_REVOKED)
							pstCertStatusInfo->dwRevocationStatus=1;

		if(pstCertStatusInfo->dwRevocationStatusBit == VS_REV_STATUS_FAILED)
							pstCertStatusInfo->dwRevocationStatus=2;

	}
   
	/////Revocation is done on Server with OCSP
	if(pstCertStatusInfo->dwRevocationTypeBit == VS_REVOCATION_TYPE_OCSP)
	{
		if(pstCertStatusInfo->dwRevocationSubTypeBit == VS_REVOCATION_SUBTYPE_SERVER)
		{
			if((pstCertStatusInfo->dwRevocationStatusBit == VS_REV_STATUS_NOT_REV))
							pstCertStatusInfo->dwRevocationStatus=0;

			if(pstCertStatusInfo->dwRevocationStatusBit	== VS_REV_STATUS_REVOKED)
							pstCertStatusInfo->dwRevocationStatus=1;

			if(pstCertStatusInfo->dwRevocationStatusBit == VS_REV_STATUS_FAILED)
								pstCertStatusInfo->dwRevocationStatus=2;
		}

		if(pstCertStatusInfo->dwRevocationSubTypeBit == VS_REVOCATION_SUBTYPE_CLIENT)
		{
			//use pbAddtionalInfo variable having OCSP Response
			pstCertStatusInfo->dwRevocationStatus=NO_PARSE_OCSP_RESPONSE;

		}

	}

		
	
	pstCertStatusInfo->dwChainValidateTypeBit=dwStatus & 0x0C00;
	pstCertStatusInfo->dwChainValidateTypeBit=pstCertStatusInfo->dwChainValidateTypeBit>>10;
	/*
		(10-11) bits
		This bit field should be looked at only if chainValidationType is
		set to 00.
		00	Chain Validation performed on Server
		01	Chain Validation needs to be performed on Client
	*/
	pstCertStatusInfo->dwChainValidateStatusBit=dwStatus & 0x3000;
	pstCertStatusInfo->dwChainValidateStatusBit=pstCertStatusInfo->dwChainValidateStatusBit>>12;
	/*
		(12-13) bits
		00	Chain was successfully validated
		01	Chain validation failed
	*/

		/////Chain Validation is done on Server Just Checking for Status
	if(pstCertStatusInfo->dwChainValidateTypeBit == VS_CHAIN_VALIDATE_TYPE_SERVER)
	{
		if((pstCertStatusInfo->dwChainValidateStatusBit == VS_CHAIN_VALIDATE_SUCCESS))
						pstCertStatusInfo->dwChainValidationStatus=0;
		if(pstCertStatusInfo->dwChainValidateStatusBit == VS_CHAIN_VALIDATE_FAILED)
						pstCertStatusInfo->dwChainValidationStatus=1;

	}
	/////Chain Validation needs to be done from Client side 
	if(pstCertStatusInfo->dwChainValidateTypeBit == VS_CHAIN_VALIDATE_TYPE_CLIENT)
	{
		pstCertStatusInfo->dwChainValidationStatus=NO_CHAIN_VALIDATE_ONCLIENT;
	
	}

	return nResult;

}
void FreeCertList(CListUserInfo	*pCertList)
{
	CUserInfo *     pObj;
	CListUserInfo::iterator		it;

	if(pCertList!=NULL)
	{

		for (it = pCertList->begin();
						it != pCertList->end(); ++it)
			{
					pObj=(*it);
					DELETE_MEMORY(pObj)
			}

			if(!pCertList->empty())
						pCertList->clear();
	}

}

HRESULT GetVers(char *szFileName, char *szVer)
{
	   HRESULT hr=S_OK;
	   DWORD dwArg;
	   DWORD err; 
       DWORD dwInfoSize = GetFileVersionInfoSize(szFileName, &dwArg);

       if(0 == dwInfoSize)
       {                 
           err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

      
	   BYTE* lpBuff= (BYTE *)malloc(dwInfoSize);

       if(!lpBuff)
       {
            err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

       if(0 == GetFileVersionInfo(szFileName, 0, dwInfoSize, lpBuff))
       {
          err= GetLastError();
		  return HRESULT_FROM_WIN32(err);
       }

       VS_FIXEDFILEINFO *vInfo;

       UINT uInfoSize;

       if(0 == VerQueryValue(lpBuff, TEXT("\\"),
               (LPVOID*)&vInfo,
               &uInfoSize))
       {
           
           free(lpBuff) ;
		   err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
           
       }

       if(0 == uInfoSize)
       {
           
           free(lpBuff) ;
           err= GetLastError();
		   return HRESULT_FROM_WIN32(err);
       }

	   char buf[10];

	   lstrcpy(szVer,"");

	   _itoa(HIWORD(vInfo->dwFileVersionMS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(LOWORD(vInfo->dwFileVersionMS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(HIWORD(vInfo->dwFileVersionLS),buf,10);
	   lstrcat(szVer, buf);

	   _itoa(LOWORD(vInfo->dwFileVersionLS),buf,10);
	   lstrcat(szVer, buf);
    
	   if (lpBuff)
			free(lpBuff) ;

	   return hr;

}

void freeAttachInfo(ATTACH_FILE_INFO	*pAttachedFiles)
{

	CAttachInfo *pAttachInfo;
	ATTACH_FILE_INFO::iterator i;

	if(pAttachedFiles!=NULL)
	{
		if (!pAttachedFiles->empty())
		{
		
			for (i =  pAttachedFiles->begin();
									i != pAttachedFiles->end(); ++i)
			{
				pAttachInfo=(*i);
				DELETE_MEMORY(pAttachInfo)
			
      
			}
		}
	}

}