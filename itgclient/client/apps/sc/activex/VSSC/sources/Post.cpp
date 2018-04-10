// Post.cpp: implementation of the CPost class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Post.h"
#include <list>

#define     APPNAME					"VSSC"

#define     VS_HTTP_POST             "POST"
#define     VS_HTTP_GET              "GET"

#define     HTTP_VER				"HTTP/1.0"
#define     HTTP_HEADER             "Content-Type: application/x-www-form-urlencoded\n\r" 


#define     VS_RESPONSE_CONTENT_TYPE "application/x-verisign-cert-resolution"

extern CListUserInfo		*g_pEncryptCertInGM; 
extern DWORD                 g_dwCertTimeOut;
extern DWORD                 g_dwAppErr;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPost::CPost()
{
	m_bstrContentType=VS_RESPONSE_CONTENT_TYPE;
}

CPost::~CPost()
{

}

HRESULT CPost::ResolveName(
						   _bstr_t i_bstrHostName,
						   _bstr_t i_bstrUserInfo,
						   PCERT_RESOLVE_INFO  pCertResolveInfo,
						   PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
						   int  nCertReqCertInfo,
						   CListUserInfo  *o_pUserList
						   )
{
	  DWORD				dwEncodeSize=0,dwSize=0;
	  LPTSTR			pszPostData=NULL;
	  _bstr_t			bstrEncodeUserInfo = "",bstrDownloadData="";
	  BYTE              *pbDownloadData=NULL;

	  hr=S_OK;
	  do
	  {
		 
		  m_nVersion=pCertResolveInfo->nVersion;
		  m_nOperation=pCertResolveInfo->nOperation;
		  
		  hr=CreateCertResolveReq(
								i_bstrUserInfo,
								pCertResolveInfo,  ////CertResolveInfo
								pCertReqCritInfo,  ////CertReqCritInfo
								nCertReqCertInfo,
								&bstrEncodeUserInfo
								);
		  	
		  if(hr!=S_OK)
		  {
			  g_dwAppErr=E_UNABLE_TODO_CERTRESOLVE;
			  break;
		  }

		  dwEncodeSize=bstrEncodeUserInfo.length();
		  pszPostData = (LPTSTR)malloc(dwEncodeSize+VS_MAX_LEN);
		  CHECK_MEM_BREAK(pszPostData)
		   
		  sprintf(pszPostData,"cert_resolution=%s",(TCHAR*)bstrEncodeUserInfo);	


		  DWORD    dwEncodedLen=lstrlen(pszPostData)*3+1;
		  char *pszURLEncode=(char*)malloc(dwEncodedLen);
		  CHECK_MEM_BREAK(pszURLEncode)
			

		  URLEncode(pszPostData,pszURLEncode);
		  _bstr_t          bstrPostData(pszURLEncode);

		  /////FREE MEMORY
		  FREE_MEMORY(pszPostData)
		  FREE_MEMORY(pszURLEncode)
	 

		  #ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "URLDownloadToBuffer-Begin",
												(LPCTSTR) "VSSC", MB_OK );
		  #endif

		  
    	  hr=URLDownloadToBuffer(
								i_bstrHostName,
								bstrPostData,
								&pbDownloadData,
								&dwSize
								);
		  CHECK_HRESULT_BREAK
		
		  #ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "URLDownloadToBuffer-End",
												(LPCTSTR) "VSSC", MB_OK );
		  #endif	  

		
		  #ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "DecodeUserInfo-Begin",
											(LPCTSTR) "VSSC", MB_OK );
		  #endif
		
		  if(m_bstrResponse_ContentType!=m_bstrContentType)
		  {
			  hr=E_INVALID_CERTRESPONSEDATA;
			  break;
		  }
		

		 
		  hr=DecodeCertResolveReq(pbDownloadData,dwSize,o_pUserList);	


		  #ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR) "DecodeUserInfo-End",
											(LPCTSTR) "VSSC", MB_OK );
		  #endif	  
	


		}while(0);

	
		FREE_MEMORY(pszPostData)
        FREE_MEMORY(pbDownloadData)

		return hr;
}


HRESULT CPost::CreateCertResolveReq(
									_bstr_t i_bstrEmailAddr,
									PCERT_RESOLVE_INFO  pCertResolveInfo,
									PCERT_REQ_CRIT_INFO pCertReqCritInfo[],
									int  nCertReqCertInfo,
									_bstr_t* o_pbstrEncodedCertReqInfo
									)
{
	hr=S_OK;
	TCHAR*		ptcszToken=NULL;
	
	TCHAR*		ptcszSCType = NULL;
	TCHAR*		pszEncodedInfo=NULL;
	TCHAR*      szEmailAddr=NULL;

	_bstr_t		bstrEncodedInfo="";

	do
	{
	
			/*
			 Create the following object 
			NameOREmail  := SEQUENCE {
								
									SEQUENCE{
										Version                 Version
										Operation               Operation
										ReqCrit					ReqCrit
										SCType					IA5String
										emailAddress			IA5String
										SerialNumber            Octet String
										IssuerDN                Octet String
									}
									......
									......
	  					  }
			*/
			
		    CSequence   cseqsCertResolveInfo;

			DWORD       dwSCType=0;

			dwSCType=lstrlen(pCertResolveInfo->pszSCType);
			ptcszSCType=(TCHAR*)malloc(dwSCType+1);
			memcpy(ptcszSCType,(TCHAR*)pCertResolveInfo->pszSCType,dwSCType+1);
			
			if(i_bstrEmailAddr.length()>0 &&nCertReqCertInfo==0)
			{
					
					szEmailAddr=StripSpace(i_bstrEmailAddr);
									
					ptcszToken=_tcstok(szEmailAddr,_T(",;"));
					while(ptcszToken!=NULL)
					{
						CUniversalInteger	uiVersion(1, (_PBYTE)&pCertResolveInfo->nVersion);
						CUniversalInteger	uiOperation(1, (_PBYTE)&pCertResolveInfo->nOperation);
						CUniversalInteger	uiReqCrit(1, (_PBYTE)&pCertResolveInfo->ReqCrit);

						CIA5String ia5SCType(_tcslen(ptcszSCType)* sizeof(TCHAR),
											(unsigned char*)ptcszSCType);

					
						

						CIA5String ia5EmailAddr(_tcslen(ptcszToken)* sizeof(TCHAR),
											(unsigned char*)ptcszToken);
		

						COctetString       oIssuerDN(0,NULL);
						CUniversalInteger  uiSerialNum(0,NULL);


						CBaseDERCollection	cbdcCertResolveInfo;
						cbdcCertResolveInfo=uiVersion+uiOperation+uiReqCrit+ia5SCType+
											ia5EmailAddr+uiSerialNum+oIssuerDN;


						//inner sequence
						CSequence cseqCertResolveInfo;
						cseqCertResolveInfo=cbdcCertResolveInfo;


						CBaseDERCollection cdbcSeqCollection;
						cdbcSeqCollection=cseqCertResolveInfo;
						cseqsCertResolveInfo+=cdbcSeqCollection;
						
						ptcszToken=_tcstok(NULL,_T(",;"));
					}
			}

			
			if(i_bstrEmailAddr.length()==0 &&nCertReqCertInfo!=0)
			{
				for(int i=0;i<nCertReqCertInfo;i++)
				{

						if(pCertReqCritInfo[i]==NULL||
						   pCertReqCritInfo[i]->IssuerDN.cbData==0||
						   pCertReqCritInfo[i]->IssuerDN.pbData==NULL||
						   pCertReqCritInfo[i]->SerialNum.cbData==0||
						   pCertReqCritInfo[i]->SerialNum.pbData==NULL
						   )
						{
							hr=E_INVALID_CERTREQDATA;
							break;

						}

						CUniversalInteger	uiVersion(1, (_PBYTE)&pCertResolveInfo->nVersion);
						CUniversalInteger	uiOperation(1, (_PBYTE)&pCertResolveInfo->nOperation);
						CUniversalInteger	uiReqCrit(1, (_PBYTE)&pCertResolveInfo->ReqCrit);

						CIA5String ia5SCType(_tcslen(ptcszSCType)* sizeof(TCHAR),
											(unsigned char*)ptcszSCType);

					
						CIA5String ia5EmailAddr(lstrlen(pCertReqCritInfo[i]->pszEmailAddr),
							(unsigned char*)pCertReqCritInfo[i]->pszEmailAddr);

						COctetString       oIssuerDN(pCertReqCritInfo[i]->IssuerDN.cbData,
													 pCertReqCritInfo[i]->IssuerDN.pbData);

						CUniversalInteger       uiSerialNum(pCertReqCritInfo[i]->SerialNum.cbData,
													  pCertReqCritInfo[i]->SerialNum.pbData);


						CBaseDERCollection	cbdcCertResolveInfo;
						cbdcCertResolveInfo=uiVersion+uiOperation+uiReqCrit+ia5SCType+ia5EmailAddr+
											uiSerialNum+oIssuerDN;

						//inner sequence
						CSequence cseqCertResolveInfo;
						cseqCertResolveInfo=cbdcCertResolveInfo;


						CBaseDERCollection cdbcSeqCollection;
						cdbcSeqCollection=cseqCertResolveInfo;
						cseqsCertResolveInfo+=cdbcSeqCollection;

				}
			}

			if(cseqsCertResolveInfo.BaseDERBlob->pbData==NULL||
			   cseqsCertResolveInfo.BaseDERBlob->cbData==0)
			{
				hr=E_INVALID_CERTREQDATA;
				break;


			}

			/////encode the DER blob to base64
			DWORD dwB64Size;
			_Base64Encode(
						 (char*)(cseqsCertResolveInfo.BaseDERBlob->pbData),
						 cseqsCertResolveInfo.BaseDERBlob->cbData,
						 NULL,
						 (unsigned int *)&dwB64Size
						 );
			
			pszEncodedInfo= (TCHAR*)malloc(dwB64Size+1);
			CHECK_MEM_BREAK(pszEncodedInfo)
			memset(pszEncodedInfo,0,dwB64Size+1);
		
			_Base64Encode(
						 (char*)(cseqsCertResolveInfo.BaseDERBlob->pbData),
						 cseqsCertResolveInfo.BaseDERBlob->cbData,
						 (char*)pszEncodedInfo,
						 (unsigned int *)&dwB64Size
						 );

			pszEncodedInfo[dwB64Size] = '\0';


			BSTR   BSTREncoded=_MultiToWideString((char*)pszEncodedInfo);
			*o_pbstrEncodedCertReqInfo=BSTREncoded;
			SysFreeString(BSTREncoded);
		
					
	}while(0);

	FREE_MEMORY(szEmailAddr)
	FREE_MEMORY(ptcszSCType)
    FREE_MEMORY(pszEncodedInfo)



	return hr;
}


DWORD CPost::GetUniversalInt(CUniversalInteger *pcuiValue)
{
	//Obtain the version bytes
	unsigned char byteStatus[4];
	for(unsigned int i = 0;i < pcuiValue->cbData; ++i)
		byteStatus[i] = pcuiValue->pbData[i];

	for(unsigned int j=i;j<4; ++j)
		byteStatus[j] = 0x00;
	
	DWORD dwui  = *((_DWORD*)byteStatus);

	return dwui;


}

HRESULT CPost::DecodeCertResolveReq(
									BYTE*i_pbDownloadData,
									DWORD dwDataLen,
									CListUserInfo  *m_pUserList
									)
{
	_bstr_t             bstrInit(_T(""));

	char				*pszBuf=NULL;
	DWORD				cbDecodedUserInfo=0;
	PBYTE				pbDecodedUserInfo=NULL;

		
	hr=S_OK;

	do
	{
		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR)"_Base64Decode -Begin",
													(LPCTSTR) "VSSC", MB_OK );
		#endif
		
		_Base64Decode(
					 (char*)i_pbDownloadData,
					 dwDataLen,
					 NULL,	
					 &cbDecodedUserInfo
					 );

		pbDecodedUserInfo = (BYTE *) malloc(cbDecodedUserInfo);
		CHECK_MEM_BREAK(pbDecodedUserInfo)

		_Base64Decode(
					 (char*)i_pbDownloadData,
					 dwDataLen,
					 (char *)pbDecodedUserInfo,
					 &cbDecodedUserInfo
					 );

		#ifdef	_VSSC_MSG_BOX_
			::MessageBox ( NULL, (LPCTSTR)"_Base64Decode -End",
													(LPCTSTR) "VSSC", MB_OK );
		#endif

		
	
		CBaseDERCollection     cbdcUserInfo(cbDecodedUserInfo,pbDecodedUserInfo);
		CBaseDERHierarchy	   cbdhUserInfo(cbdcUserInfo);
		if(cbdhUserInfo.dwErrorCode == 0xFFFFFFFF)
		{
			hr=E_INVALID_CERTRESPONSEDATA;
			break;
		}

		FREE_MEMORY(pbDecodedUserInfo)

		

		DERTree *dtUserInfo = &(cbdhUserInfo.m_DERTree);
		CHECK_TREE_NODE(dtUserInfo,SEQUENCE)

		DERTree *dtUserInfoSeq=dtUserInfo->rightDERTree;
		CListUserInfo::iterator it;
		

		do
		{
				
					CHECK_TREE_NODE(dtUserInfoSeq,SEQUENCE)

					/*
						UserInfo ::= SEQUENCE {
								Version                 Version,
								Operation               Operation,
								ReqCrit					ReqCrit,
								SCType                  IA5String,
								emailAddress			IA5String,
								SerialNumber            Integer,
								IssuerDN                Octet String,

								status					Status,
								resolutionBlob			ResolutionBlob,
								additionalInfo			OCTET STRING
						}
					*/

					CERT_REQ_RESPONSE_INFO     stCertReqResponseInfo;
					memset(&stCertReqResponseInfo,0,sizeof(CERT_REQ_RESPONSE_INFO));
					stCertReqResponseInfo.bstrEmailAddr=bstrInit;
					stCertReqResponseInfo.bstrIssuerDN=bstrInit;
					stCertReqResponseInfo.bstrSCType=bstrInit;
					stCertReqResponseInfo.bstrSeialNum=bstrInit;


					////Getting uiVersion from Seq
					DERTree *dtuiVersion = dtUserInfoSeq->rightDERTree;
					//Make sure that the derblob in the dtuiVersion of type universal integer
					CHECK_TREE_NODE(dtuiVersion,UNIVERSAL_INTEGER)
					CUniversalInteger* pcuiVersion = (CUniversalInteger*)dtuiVersion->currentBaseDER;
					stCertReqResponseInfo.dwVersion=GetUniversalInt(pcuiVersion);

					////Getting uiOperation from Seq
					DERTree *dtuiOpration = dtuiVersion->nextDERTree;
					//Make sure that the derblob in the dtuiOperation of type universal integer
					CHECK_TREE_NODE(dtuiOpration,UNIVERSAL_INTEGER)
					
					CUniversalInteger* pcuiOperation = (CUniversalInteger*)dtuiOpration->currentBaseDER;
					stCertReqResponseInfo.dwOperation=GetUniversalInt(pcuiOperation);

					////Getting uiReqCrit from Seq
					DERTree *dtuiReqCrit=dtuiOpration->nextDERTree;
					//Make sure that the derblob in the dtuiReqCrit of type universal integer
					CHECK_TREE_NODE(dtuiReqCrit,UNIVERSAL_INTEGER)
					CUniversalInteger* pcuiReqCrit = (CUniversalInteger*)dtuiReqCrit->currentBaseDER;
					stCertReqResponseInfo.dwReqCrit=GetUniversalInt(pcuiReqCrit);

					if(m_nVersion!=stCertReqResponseInfo.dwVersion ||
						m_nOperation!=stCertReqResponseInfo.dwOperation)
					{
						hr=E_INVALID_CERTRESPONSEDATA;
						break;
					}

					////Getting IA5SCType from Seq
					DERTree *dtIA5SCType=dtuiReqCrit->nextDERTree;
					//Make sure that the derblob in the dtIA5SCType of type IA5_STRING
					CHECK_TREE_NODE(dtIA5SCType,IA5_STRING)
					CIA5String* ia5SCType = (CIA5String*)dtIA5SCType->currentBaseDER;

					pszBuf=(char*)malloc(ia5SCType->cbData+1);
					CHECK_MEM_BREAK(pszBuf)

					memcpy(pszBuf,ia5SCType->pbData,ia5SCType->cbData);
					pszBuf[ia5SCType->cbData]='\0';
					stCertReqResponseInfo.bstrSCType=pszBuf;
					FREE_MEMORY(pszBuf);
			

					////Getting E-mail from Seq
					DERTree *dtia5Email = dtIA5SCType->nextDERTree;
					//Make sure that the derblob in the dtEMAIl of type IA5 String
					CHECK_TREE_NODE(dtia5Email,IA5_STRING)
					CIA5String* ia5Email = (CIA5String*)dtia5Email->currentBaseDER;

					pszBuf=(char*)malloc(ia5Email->cbData+1);
					CHECK_MEM_BREAK(pszBuf)

					memcpy(pszBuf,ia5Email->pbData,ia5Email->cbData);
					pszBuf[ia5Email->cbData]='\0';
					stCertReqResponseInfo.bstrEmailAddr=pszBuf;
					FREE_MEMORY(pszBuf)


					////Getting SerialNum from Seq
					DERTree *dtuiSerialNum=dtia5Email->nextDERTree;
					//Make sure that the derblob in the dtOCSerialNum of type UNIVERSAL_INTEGER
					CHECK_TREE_NODE(dtuiSerialNum,UNIVERSAL_INTEGER)
					
                    /*
					CUniversalInteger* pcuiSerialNum = (CUniversalInteger*)dtuiSerialNum->currentBaseDER;
					CRYPT_INTEGER_BLOB   ibSerialNumber;
					_bstr_t				bstrSerialNum="";

					if(pcuiSerialNum->pbData!=NULL && pcuiSerialNum->cbData!=0)
					{
						ibSerialNumber.pbData=pcuiSerialNum->pbData;
						ibSerialNumber.cbData=pcuiSerialNum->cbData;
						hr = _GetCertSerNum(ibSerialNumber,&bstrSerialNum);
					}
					stCertReqResponseInfo.bstrSeialNum=bstrSerialNum;
					*/
		
			
					////Getting IssuerDN from Seq
					DERTree *dtOCIssuerDN=dtuiSerialNum->nextDERTree;
					//Make sure that the derblob in the dtOCIssuerDN of type OCTET_STRING
					CHECK_TREE_NODE(dtOCIssuerDN,OCTET_STRING)

                    /*
					COctetString* pcocIssuerDN = (COctetString*)dtOCIssuerDN->currentBaseDER;
					_bstr_t   bstrIssuerDN="";
					if(pcocIssuerDN->pbData!=NULL && pcocIssuerDN->cbData!=0)
					{
						//Get the cert issuer dn
						CERT_NAME_BLOB    nbIssuerDN;
						nbIssuerDN.pbData=pcocIssuerDN->pbData;
						nbIssuerDN.cbData=pcocIssuerDN->cbData;

						hr = _GetNameFromBlob(nbIssuerDN,&bstrIssuerDN);
					}
					stCertReqResponseInfo.bstrIssuerDN=	bstrIssuerDN;
					*/

				
					////Getting uiStatus from Seq
					DERTree *dtuiStatus = dtOCIssuerDN->nextDERTree;
					//Make sure that the derblob in the dtuiStatus of type universal integer
					CHECK_TREE_NODE(dtuiStatus,UNIVERSAL_INTEGER)
					
					CUniversalInteger* pcuiStatus = (CUniversalInteger*)dtuiStatus->currentBaseDER;

					//Obtain the version bytes
					unsigned char byteStatus[4];
					for(unsigned int i = 0;i < pcuiStatus->cbData; ++i)
						byteStatus[i] = pcuiStatus->pbData[i];

					for(unsigned int j=i;j<4; ++j)
						byteStatus[j] = 0x00;
					
					stCertReqResponseInfo.dwStatus = *((_DWORD*)byteStatus);
					

					////Getting Cert from Seq
					DERTree *dtosUserCert = dtuiStatus->nextDERTree;
					//Make sure that the derblob in the dtosUserCert of type universal Octet String
					CHECK_TREE_NODE(dtosUserCert,OCTET_STRING)


					DERTree *dtAddtionalInfo = dtosUserCert->nextDERTree;
					//Make sure that the derblob in the dtAddtionalInfo of type Octet String
					CHECK_TREE_NODE(dtAddtionalInfo,OCTET_STRING)
					
	
                    hr=AnalyzeResolutionBlob(
											&stCertReqResponseInfo,
											dtosUserCert->currentBaseDER->pbData,
											dtosUserCert->currentBaseDER->cbData,
											dtAddtionalInfo->currentBaseDER->pbData,
											dtAddtionalInfo->currentBaseDER->cbData,
											m_pUserList
											);

					if(hr!=S_OK)
						break;

     				dtUserInfoSeq=dtUserInfoSeq->nextDERTree;

		
		}
		while(dtUserInfoSeq!=NULL);

    }
    while(0);

	///////////
	FREE_MEMORY(pbDecodedUserInfo)
	FREE_MEMORY(pszBuf)
    
	return hr;

}

HRESULT CPost::URLDownloadToBuffer(
								   _bstr_t i_bstrURL,
								   _bstr_t i_bstrPostVars,
									BYTE** o_pbDownloadData,
									DWORD *dwDataLen
									)
{
	  hr=S_OK;
	
	  int				nCounter;
	  BOOL				bRet=FALSE;
	  DWORD				dwSize=0,dwDownloaded=0,dwSizeSum=0,dwOpenFlags=0,dwURLSize=0;			

	  /////fixed size
	  _TCHAR			szHostName[VS_MAX_LEN],szScheme[VS_MAX_LEN],szUrlPath[VS_MAX_LEN],
						szFormMethod[VS_MAX_LEN];


	  BYTE				*pbURLContent=NULL,*pbHolding=NULL,*pbData=NULL;
      LPTSTR			pszCanonicalizeUrl=NULL; 
	  
	  _bstr_t           bstrCanonicalizeUrl,bstrDownloadData="";
		
	  URL_COMPONENTS	uc;
      HINTERNET			m_hInternetSession=NULL,m_hHttpConnection=NULL,m_hHttpReq=NULL;
	  

	  do
	  {

				 dwURLSize=i_bstrURL.length()*2;
				 pszCanonicalizeUrl=(LPTSTR)malloc(dwURLSize);
				 CHECK_MEM_BREAK(pszCanonicalizeUrl)
				 
				 memset(pszCanonicalizeUrl,0,dwURLSize);
				 bRet=InternetCanonicalizeUrl(
										i_bstrURL,pszCanonicalizeUrl,
										&dwURLSize,//ICU_ENCODE_SPACES_ONLY 
										ICU_BROWSER_MODE 
										);


				  CHECK_WININET_BOOL_BREAK
				  
				  ZeroMemory(&uc, sizeof(uc));
				  uc.dwStructSize = sizeof(uc);

				  uc.lpszScheme=szScheme;
				  uc.dwSchemeLength=sizeof(szScheme);

				  uc.lpszHostName = szHostName;
				  uc.dwHostNameLength = sizeof(szHostName);

				  uc.lpszUrlPath=szUrlPath;
				  uc.dwUrlPathLength=sizeof(szUrlPath);


				  bRet=InternetCrackUrl(
										pszCanonicalizeUrl,
										dwURLSize,
										ICU_DECODE,
										&uc
										);
				  CHECK_WININET_BOOL_BREAK
				  
				  if(uc.nScheme==INTERNET_SCHEME_HTTP)
						dwOpenFlags=INTERNET_FLAG_RELOAD|INTERNET_FLAG_NO_CACHE_WRITE;
				  
				  /*
				  if(uc.nScheme==INTERNET_SCHEME_HTTPS)
					  dwOpenFlags=INTERNET_FLAG_SECURE |INTERNET_FLAG_IGNORE_CERT_CN_INVALID |
					  INTERNET_FLAG_IGNORE_CERT_DATE_INVALID|INTERNET_FLAG_NO_CACHE_WRITE; 
				  */
				  
				  if(uc.nScheme==INTERNET_SCHEME_HTTPS)
					  dwOpenFlags=INTERNET_FLAG_SECURE |INTERNET_FLAG_NO_CACHE_WRITE; 



				  if(i_bstrPostVars.length()>0)
				  {
					dwSize=i_bstrPostVars.length();
				    _tcscpy(szFormMethod,VS_HTTP_POST);
				  }
				  else
				  {
					  dwSize=0;
					  _tcscpy(szFormMethod,VS_HTTP_GET);
				  }
				  

				  m_hInternetSession = ::InternetOpen(
													  APPNAME,
													  INTERNET_OPEN_TYPE_PRECONFIG,
													  NULL,
													  NULL,
													  0);
				  if (m_hInternetSession == NULL)
				  {
					
					hr=E_INETOPEN_ERR;
					break;
				  }

				  m_hHttpConnection=::InternetConnect(
													 m_hInternetSession,
													 uc.lpszHostName,
													 uc.nPort,
													 NULL,
													 NULL,
													 INTERNET_SERVICE_HTTP,
													 0,
													 (DWORD )this
													 );
					
				  
				  if(m_hHttpConnection==NULL)
				  {
										
					hr=E_INETCONNECT_ERR;
					break;
				  }


				  m_hHttpReq=HttpOpenRequest(
											 m_hHttpConnection,
											 szFormMethod,
											 uc.lpszUrlPath,
											 NULL,NULL,NULL,
											 dwOpenFlags,
											 0
											 );
				  if(m_hHttpReq==NULL)
				  {
										
					hr=E_INETOPENREQ_ERR;
					break;
				  }
					  
				  	
				  LPTSTR headers=HTTP_HEADER; 
				  DWORD  dwHeaderSize=_tcslen(headers)*sizeof(TCHAR);
				  DWORD  dwError=0;				  
 
				  
				  bRet=HttpAddRequestHeaders(
											m_hHttpReq,
											headers,
											dwHeaderSize,
											HTTP_ADDREQ_FLAG_REPLACE |HTTP_ADDREQ_FLAG_ADD 
											);
				  

				  CHECK_WININET_BOOL_BREAK
				 
				  bRet=HttpSendRequest(
									  m_hHttpReq,
									  NULL,
									  0,
									  (TCHAR*)i_bstrPostVars,
									  dwSize
									  );
				  if(!bRet)
				  {
						  dwError=GetLastError();
						  switch(dwError)
						  {
						  case ERROR_INTERNET_SEC_CERT_CN_INVALID:
							  hr=E_INETCERT_CN_INVALID;
							  break;

						  case ERROR_INTERNET_INVALID_CA:
							  hr=E_INETINVALID_CA;
							  break;
						  case ERROR_INTERNET_SEC_CERT_DATE_INVALID:
							  hr=E_INETCERT_DATE_INVALID;
							  break;
							
						  }
							
				  }

				  CHECK_WININET_BOOL_BREAK	


				  //////
				  DWORD dwStatus=0,dwStatusSize=0;

				  HttpQueryInfo(m_hHttpReq, HTTP_QUERY_FLAG_NUMBER | 
							HTTP_QUERY_STATUS_CODE, &dwStatus, &dwStatusSize, NULL);

				  switch (dwStatus)
				  {
						case HTTP_STATUS_PROXY_AUTH_REQ:
							//Proxy Authentication Required
							// Insert code to set strUsername and strPassword.
							//InternetSetOption(hResourceHandle, INTERNET_OPTION_PROXY_USERNAME, 
							//				  strUsername, strlen(strUsername)+1);
							//InternetSetOption(hResourceHandle, INTERNET_OPTION_PROXY_PASSWORD, 
							//				  strPassword, strlen(strPassword)+1);

							hr=E_INETSTATUS_PROXY_AUTH_REQ;
							
							
							break;
						case HTTP_STATUS_DENIED:
							//Server Authentication Required
							// Insert code to set strUsername and strPassword.
							//InternetSetOption(hResourceHandle, INTERNET_OPTION_USERNAME, 
							//				  strUsername, strlen(strUsername)+1);
							//InternetSetOption(hResourceHandle, INTERNET_OPTION_PASSWORD, 
							//				  strPassword, strlen(strPassword)+1);

							hr=E_INETSTATUS_SERVER_AUTH_REQ;
							
							
							
							break;
						case HTTP_STATUS_BAD_REQUEST:
							 hr=E_INETSTATUS_BAD_REQUEST;
							 
							 break;
                        case HTTP_STATUS_NOT_FOUND:
							 hr=E_INETSTATUS_NOT_FOUND;
							 
							 break;
						case HTTP_STATUS_BAD_METHOD://405
							 hr=E_NETSTATUS_STATUS_BAD_METHOD;
							 
							 break;
						case HTTP_STATUS_SERVER_ERROR: 
							 hr=E_INETSTATUS_SERVER_ERROR;
							 break;

				  }

				  /////fix size
				  char   szContentType[VS_MAX_LEN];
				  DWORD  dwContentLen=VS_MAX_LEN;

				  bRet=HttpQueryInfo(m_hHttpReq, HTTP_QUERY_CONTENT_TYPE,
								(LPVOID)szContentType, &dwContentLen, NULL);

				  if(!bRet)
				  {		
					hr=E_WININET_ERR;
						
				  }

				  m_bstrResponse_ContentType=szContentType;
					  
				  ////////////////reading of data//////////
				  // This loop handles reading the data.  
				  do
					{
					try_again:
					// The call to InternetQueryDataAvailable determines the amount of 
					// data available to download.
					if (!InternetQueryDataAvailable(m_hHttpReq,&dwSize,0,0))
					{
						if (GetLastError()== ERROR_IO_PENDING)
						{
							nCounter = 0;
							
							while(GetLastError()==ERROR_IO_PENDING)
							{
								nCounter++;
								if (nCounter==2000)
								break;
								InternetQueryDataAvailable(m_hHttpReq,&dwSize,0,0);
							}
							goto try_again;
						}
						
						hr=E_INETQUERY_DATA_ERR;
						break;
					}
					else
					{
						
						// Check the size of the remaining data.  If it is zero, break.
							if (dwSize == 0)
								goto End;

						// Allocates a buffer of the size returned by InternetQueryDataAvailable
						pbData = (PBYTE)malloc(dwSize);
						CHECK_MEM_BREAK(pbData)
						memset(pbData,0,dwSize);

						// Reads the data from the HINTERNET handle.
						if(!InternetReadFile(m_hHttpReq,(LPVOID)pbData,dwSize,&dwDownloaded))
						{
							if (GetLastError()== ERROR_IO_PENDING)
							{
								nCounter = 0;
								
								while(GetLastError()==ERROR_IO_PENDING)
								{
									nCounter++;
								}
								goto keep_going;
							}
							
							hr=E_INETREAD_DATA_ERR;

							FREE_MEMORY(pbData)
							break;
						}
						else
						{

						keep_going:
							if (dwSize == 0)
								break;
							
							// Allocates the holding buffer
							pbHolding = (PBYTE)malloc(dwSizeSum + dwDownloaded);
							CHECK_MEM_BREAK(pbHolding)
							memset(pbHolding,0,dwSizeSum + dwDownloaded);
							
							// Checks if there has been any data written to the textbox
							if (dwSizeSum != 0)
							{
								memcpy(pbHolding,pbURLContent,dwSizeSum);
								FREE_MEMORY(pbURLContent)
							}
							else
							{
								memset(pbHolding,0,dwSizeSum + dwDownloaded);
							}

							memcpy(pbHolding+dwSizeSum,pbData, dwDownloaded );
							dwSizeSum = dwSizeSum + dwDownloaded ;

							pbURLContent = (PBYTE)malloc(dwSizeSum);
							CHECK_MEM_BREAK(pbURLContent)
							memset(pbURLContent,0,dwSizeSum);

							memcpy(pbURLContent,pbHolding,dwSizeSum);
						
							FREE_MEMORY(pbHolding)
                            FREE_MEMORY(pbData)

						}
					}
				}
				while(TRUE);

		}while(0);

End:
	if(pbURLContent!=NULL)
	{
		*o_pbDownloadData=(BYTE*)malloc(dwSizeSum);
		if(*o_pbDownloadData!=NULL)
		{
			memset(*o_pbDownloadData,0,dwSizeSum);
			memcpy(*o_pbDownloadData,pbURLContent,dwSizeSum);
			*dwDataLen=dwSizeSum;

			FREE_MEMORY(pbURLContent)
		}


	}

	FREE_MEMORY(pszCanonicalizeUrl)

	if(m_hHttpReq!=NULL)
		InternetCloseHandle(m_hHttpReq);

	if(m_hInternetSession!=NULL)
		InternetCloseHandle(m_hInternetSession);

	return hr;
}


HRESULT CPost::AnalyzeResolutionBlob(
									 CERT_REQ_RESPONSE_INFO     *pstCertReqResponseInfo,
									 BYTE *pbResolutionBlob,DWORD cbResolutionBlob,
									 BYTE *pbAddtionalInfo,DWORD cbAddtionalInfo,
									 CListUserInfo  *pUserList
									 )

{

	hr=S_OK;

	PCERT_INFO			pCertInfo=NULL;
	CUserInfo     *objUserInfo=new CUserInfo(
												pstCertReqResponseInfo
											);

	time(&objUserInfo->m_lLastDownloadTime);

	CheckCertStatus(pstCertReqResponseInfo->dwStatus,
							&objUserInfo->stCertStatusInfo);

	
	
	if(pbResolutionBlob==NULL&&cbResolutionBlob==0)
	{
		////BUG Check VALID FLAG----objUserInfo->bExpValid=TRUE;
		if(pstCertReqResponseInfo->dwOperation==0)
						objUserInfo->AddSignerCert(NULL,0);
		if(pstCertReqResponseInfo->dwOperation==1)
						objUserInfo->AddEncryptCert(NULL,0);

		pUserList->insert(pUserList->end(),objUserInfo);
				
	}
	else
	{
		    if(pstCertReqResponseInfo->dwOperation==0)
			{
						//MYRESOLUTION 
						objUserInfo->AddSignerCert(pbResolutionBlob,cbResolutionBlob);
						CCertInfo  ResolveSignerInfo(pbResolutionBlob,cbResolutionBlob);
						pCertInfo=ResolveSignerInfo.GetCertInfo();
												
					
			}
			if(pstCertReqResponseInfo->dwOperation==1)
			{
				if(objUserInfo->stCertStatusInfo.dwResolutionTypeBit &VS_ENC_CERT_SIGNED_PKCS7)
				{
								
					VS_PKCS7_INFO vsspiPKCS7InfoS;
					ParsePKCS7Data(pbResolutionBlob,cbResolutionBlob,&vsspiPKCS7InfoS);
					// must be signed data.
					if(vsspiPKCS7InfoS.ePKCS7Type != PKCS7_SIGNED)
					{
							hr=E_INVALID_PKCS7;
					}


					VS_CERT_BLOB EndEntityCertBlob;
					GetEndEntityCert(vsspiPKCS7InfoS.SignedDataInfo.CertificateSet,&EndEntityCertBlob);

					objUserInfo->AddEncryptCert(EndEntityCertBlob.pbData,EndEntityCertBlob.cbData);

					CCertInfo  CertInfo(EndEntityCertBlob.pbData,EndEntityCertBlob.cbData);
					pCertInfo=CertInfo.GetCertInfo();
					
					
					
					
				}
				else
				{
					if(objUserInfo->stCertStatusInfo.dwResolutionTypeBit & VS_ENC_CERT_X509_CERT)
					{
						objUserInfo->AddEncryptCert(pbResolutionBlob,cbResolutionBlob);
						CCertInfo  CertInfo(pbResolutionBlob,cbResolutionBlob);
						pCertInfo=CertInfo.GetCertInfo();
					
						
					}
					else
					{
						objUserInfo->AddEncryptCert(NULL,0);
					}
					

				}
			}
	

		if(pCertInfo)			
		{
	
				hr=_DecodeCertInfo(pCertInfo,&objUserInfo->DecCertInfo);
				//CHECK_HRESULT_BREAK

				if(pCertInfo)
						freecertinfo(pCertInfo);

				objUserInfo->stCertReqResponseInfo.bstrIssuerDN=
												objUserInfo->DecCertInfo.bstrIssuerDN;
					
				objUserInfo->stCertReqResponseInfo.bstrSeialNum=
													objUserInfo->DecCertInfo.bstrSerNum;

				
				if(!CheckCertExpDate(
									objUserInfo->DecCertInfo.dateEffDate,
									objUserInfo->DecCertInfo.dateExpDate
									))
						objUserInfo->stCertStatusInfo.bIsExpired=TRUE;
				else
						objUserInfo->stCertStatusInfo.bIsExpired=FALSE;
						pUserList->insert(pUserList->end(),objUserInfo);
		}

	
	}

	
	
	
	FREE_MEMORY(pCertInfo)

	return hr;

}

HRESULT CPost::FindCertificateByEmailAddr(
									_bstr_t i_bstrEmailAddr,
									_bstr_t* o_pbstrResolveUser,
								    _bstr_t* o_pbstrUnResolveUser,
									CListUserInfo *o_pFoundUserList,
									CListUserInfo	*g_pCertInGM
									)
{
	hr=S_OK;

	BOOL        bResolve=FALSE;
	long         m_lCurrentTime;


	TCHAR*		ptcszToken=NULL;
	TCHAR*		ptcszEmailAddr = NULL;
	_bstr_t     bstrResolveUser="",bstrUnResolveUser="";

	do
	{
		if (g_pCertInGM->empty())
		{
			    *o_pbstrUnResolveUser=i_bstrEmailAddr;
				break;
		}

		time(&m_lCurrentTime);

		if(i_bstrEmailAddr.length()>0)
		{
				ptcszEmailAddr = (TCHAR*)malloc(i_bstrEmailAddr.length()+1);
				CHECK_MEM_BREAK(ptcszEmailAddr)
        
				memset(ptcszEmailAddr,0,i_bstrEmailAddr.length());
				memcpy(ptcszEmailAddr,(TCHAR*)i_bstrEmailAddr,i_bstrEmailAddr.length());
				ptcszEmailAddr[i_bstrEmailAddr.length()]=_T('\0');

				ptcszToken=_tcstok(ptcszEmailAddr,_T(",;"));
				while(ptcszToken!=NULL)
				{
					bResolve=FALSE;
					_bstr_t  bstrToken(ptcszToken);

					for (it =  g_pCertInGM->begin(); it != g_pCertInGM->end(); ++it)
					{
						pObj=(*it);
						if(pObj->stCertReqResponseInfo.bstrEmailAddr==bstrToken)
						{
							
							if((m_lCurrentTime - pObj->m_lLastDownloadTime)<g_dwCertTimeOut)
							{
								CUserInfo		*pAddedObj=new CUserInfo;
								*pAddedObj=*pObj;
								o_pFoundUserList->insert(o_pFoundUserList->end(),pAddedObj);
								bstrResolveUser+=pObj->stCertReqResponseInfo.bstrEmailAddr;
								bstrResolveUser+=_T(",");
								bResolve=TRUE;
								break;
							}
							else
							{
								g_pCertInGM->erase(it);
								break;
							}


						}

						  
					}

					if(!bResolve)	
					{
						bstrUnResolveUser+=bstrToken;
						bstrUnResolveUser+=_T(",");
					}

					ptcszToken=_tcstok(NULL,_T(",;"));
					
				}

				

				*o_pbstrResolveUser=bstrResolveUser;
				*o_pbstrUnResolveUser=bstrUnResolveUser;

		}

		
	}while(0);

	FREE_MEMORY(ptcszEmailAddr)

	return hr;
}

HRESULT CPost::FindCertificateByIssuerDNSerialNum
									(
									PCERT_RESOLVE_INFO  i_pCertResolveInfo,
									PCERT_REQ_CRIT_INFO i_pCertReqCritInfo[],
									int  i_nCertReqCertInfo,
									PCERT_REQ_CRIT_INFO o_pCertReqCritInfo[],
									int  *o_nCertReqCertInfo,
									CListUserInfo *o_pFoundUserList,
									CListUserInfo	*g_pCertInGM
									)
{
	hr=S_OK;

	BOOL         bResolve=FALSE;
	long         m_lCurrentTime;
	int          n_UnResolveCert=0;


	do
	{


		if (g_pCertInGM->empty())
		{
			for(int i=0;i<i_nCertReqCertInfo;i++)    
					o_pCertReqCritInfo[i]=i_pCertReqCritInfo[i];

			*o_nCertReqCertInfo=i_nCertReqCertInfo;
			break;
		}

		

		time(&m_lCurrentTime);
		
		if(i_pCertReqCritInfo!=NULL && i_nCertReqCertInfo!=0)
		{
		
			for (int i=0;i<i_nCertReqCertInfo;i++)
			{

				/////Get Serail Number
				_bstr_t				 bstrSerialNum="";
				if(i_pCertReqCritInfo[i]->SerialNum.pbData!=NULL 
						&& i_pCertReqCritInfo[i]->SerialNum.pbData!=0)
				{
					CRYPT_INTEGER_BLOB   ibSerialNumber;
					ibSerialNumber.pbData=i_pCertReqCritInfo[i]->SerialNum.pbData;
					ibSerialNumber.cbData=i_pCertReqCritInfo[i]->SerialNum.cbData;

					hr = _GetCertSerNum(ibSerialNumber,&bstrSerialNum);
				}
				/////Get IssuerDN
				_bstr_t   bstrIssuerDN="";
				if(i_pCertReqCritInfo[i]->IssuerDN.pbData!=NULL &&
					i_pCertReqCritInfo[i]->IssuerDN.cbData!=0)
				{
						/*Get the cert issuer dn*/
						CERT_NAME_BLOB    nbIssuerDN;
						nbIssuerDN.pbData=i_pCertReqCritInfo[i]->IssuerDN.pbData;
						nbIssuerDN.cbData=i_pCertReqCritInfo[i]->IssuerDN.cbData;

						hr = _GetNameFromBlob(nbIssuerDN,&bstrIssuerDN);
				}


				for (it =  g_pCertInGM->begin(); it != g_pCertInGM->end(); ++it)
					{
						pObj=(*it);
						if(pObj->stCertReqResponseInfo.bstrIssuerDN==bstrIssuerDN
							&& pObj->stCertReqResponseInfo.bstrSeialNum==bstrSerialNum)
						{
							
							if((m_lCurrentTime - pObj->m_lLastDownloadTime)<g_dwCertTimeOut)
							{
								CUserInfo		*pAddedObj=new CUserInfo;
								*pAddedObj=*pObj;

								o_pFoundUserList->insert(o_pFoundUserList->end(),pAddedObj);

								bResolve=TRUE;
								break;
							}
							else
							{
								g_pCertInGM->erase(it);
								break;
							}


						}

						  
					}

				if(!bResolve)
				{
					o_pCertReqCritInfo[n_UnResolveCert]=i_pCertReqCritInfo[i];
					n_UnResolveCert++;
				}

			}
			*o_nCertReqCertInfo=n_UnResolveCert;

		}

	}while(0);

	


	return hr;
}

HRESULT CPost::AddCertificatesInGM(CListUserInfo *i_pUserList,CListUserInfo	*g_pCertInGM)
{

	  hr=S_OK;
	  BOOL                          bFoundUser=FALSE;
	  CListUserInfo::iterator		iter;
	  CUserInfo						*pUserObj;


	  for (iter =  i_pUserList->begin(); iter != i_pUserList->end(); ++iter)
		{
			pUserObj=(*iter);

			if(pUserObj->stCertStatusInfo.bIsExpired ||
				pUserObj->stCertStatusInfo.dwRevocationStatus==01)
				continue;

			for (it =  g_pCertInGM->begin(); it != g_pCertInGM->end(); ++it)
			{
					pObj=(*it);

					if(pUserObj->stCertReqResponseInfo.bstrIssuerDN==
					   pObj->stCertReqResponseInfo.bstrIssuerDN &&
					   pUserObj->stCertReqResponseInfo.bstrSeialNum==
					   pObj->stCertReqResponseInfo.bstrSeialNum)
					{
						bFoundUser=TRUE;
						break;
				
					}
     		}


			CUserInfo		*pAddedObj=NULL;//(*pUserObj);
			if(!bFoundUser)
			{
				    
					pAddedObj=new CUserInfo;

					*pAddedObj=*pUserObj;

					g_pCertInGM->insert(g_pCertInGM->end(),pAddedObj);
			}
	  }
	  return hr;
}
