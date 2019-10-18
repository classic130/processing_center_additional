/////////////////////////////////////////////////////////////////////////
//pestub implemenation for secure messaging
////////////////////////////////////////////////////////////////////////
#define _WIN32_WINNT 0x0400 

#include "pestub.h"
#include "vssc_global.h"
#include "vsutil.h"
#include "winuser.h"
#include "windows.h"



extern DIRINFO			g_dirInfo;	
extern EMAILDIRINFO	    g_emailInfo; 

extern PESTUBINFO    g_pInfo;



//-----------Define Constant and global variables---------------/

#define        VS_NAME_OPERATION		   operation
#define        VS_CERT_OPERATION           MYCERT
#define        VS_USERCERT_OPERATION       USERCERT

////-------------revocation Status----------------------------

#define       VS_ENC_CERT					0x0001
#define       VS_X509_CERT					0x0002
#define       VS_PKCS_CERT					0x0003
#define       VS_NULL_CERT					0x0004

#define       VS_REVOCATION_CRLDP			0x0000
#define       VS_REVOCATION_OCSP			0x0010

#define       VS_REVOCATION_OCSP_RESPONSE_SERVER 0x0000
#define       VS_REVOCATION_OCSP_RESPONSE_CLIENT 0x0040

#define       VS_REV_STATUS_NOT_REV			0x0000
#define       VS_REV_STATUS_REVOKED			0x0100
#define       VS_REVOCATION_FAILED			0x0300

#define       VS_VALIDATION_TYPE_SERVER		0x0000
#define       VS_VALIDATION_TYPE_CLIENT		0x0400

#define       VS_VALIDATION_SUCCESS			0x0000
#define       VS_VALIDATION_FAILED			0x1000



 


char			szMyName[256],szMyEmalAddress[256];
char            pOutNames[5024],*lpToken=NULL;
unsigned long    dwError, dwRet=0;

char            *szEncodedInfo;
char            szNameInfo[256];




BYTE            *pbMyUserCertificate=NULL,*pbSMIMECertificate=NULL;
DWORD           cbMyUserCertificate=0,cbSMIMECertificate=0;

////////////////Output parameter to sophialite///////////////////
VSAA_NAME      *pOutput;
VSAA_NAME	   *pFinalOutput;

char           buf[8024];

unsigned long GetMyInfo(char * pMyName,char *pEmailAddr);
unsigned long GetSMIMEInfo(char * pUserName,char *pEmailAddr);

unsigned long EncodeVar(char*szNameOREmail,char **szEncodedInfo);
unsigned long DecodePostedVars(char * pInNames);
HRESULT DecodeUserInfo(char *pUserInfo);
unsigned long CreateOutputList(BYTE  *pbData, DWORD cbData);
unsigned long ErrorList();
static VSAA_STATUS MergeLists(const VSAA_NAME inList[],	const VSAA_NAME OutList[],
						VSAA_NAME **FinalList);

/*******************************************************************/
VSAA_STATUS ProcessEntries(VSAA_NAME anInput[], VSAA_NAME **panOutput)
/*******************************************************************/
{
	//Test(anInput,panOutput);

    int    OprCode=-1;

	
	/*
	#ifdef _DEBUG
    char szMessage [256];
    wsprintf (szMessage, "Please attach a debbuger to the process 0x%X (%s) and click OK",
              GetCurrentProcessId(), "sophia");
    MessageBox(NULL, szMessage, "CGI Debug Time!",
               MB_OK|MB_SERVICE_NOTIFICATION);
    #endif 
	*/
	

	PestubInit();




	if( !strcmp(anInput[0].pszName, "operation") )
	{
		if( !strcmp(anInput[0].pszValue, "MyResolution") )
		{		
			OprCode=1; //To resolve my email address and cert


		}

		if( !strcmp(anInput[0].pszValue, "SMIMEResolution") )
		{		
			OprCode=2; //To resolve other's email address and cert

		}


		if( !strcmp(anInput[0].pszValue, "Compose") )
		{		
			OprCode=3; // to Compose SMIME message

		}

		if( !strcmp(anInput[0].pszValue, "decompose") )
		{		
			OprCode=4; // to read SMIME message

		}

		if( !strcmp(anInput[0].pszValue, "inbox") )
		{		
			OprCode=5; // Summary Info message

		}

		if( !strcmp(anInput[0].pszValue, "composepage") )
		{		
			OprCode=6; // to call compose pages

		}
		
	}

	switch(OprCode)
	{
		case 1:
				//strcpy(szNameInfo,"npaul,ajayram,abhay");
				//EncodeVar(szNameInfo,&szEncodedInfo);
				//DecodePostedVars(szEncodedInfo);

			    DecodePostedVars(anInput[2].pszValue);
				dwRet=GetMyInfo(pOutNames,(char *)szMyEmalAddress);
				if(dwRet!=0)
				{
				    	ErrorList();
						*(panOutput)=pOutput;
						return VSAA_SUCCESS;

				}



				
		break;

		case 2:
				

			    //strcpy(szNameInfo,"npaul@verisign.com,ajayaram@verisign.com,abhay@verisign.com");
				//EncodeVar(szNameInfo,&szEncodedInfo);
				//DecodePostedVars(szEncodedInfo);
			    
			    DecodePostedVars(anInput[2].pszValue);
				dwRet=GetSMIMEInfo(pOutNames,(char *)szMyEmalAddress);
				
				if(dwRet!=0)
				{
					 ErrorList();
					 *(panOutput)=pOutput;
					 return VSAA_SUCCESS;

				}

				//DecodeUserInfo(pOutput[0].pszValue);
		break;

		case 3:
				dwRet=StoreMsgAndSend(anInput,&pOutput);
				if(dwRet!=0)
				 {
					 ErrorList();
					 *(panOutput)=pOutput;
					 return VSAA_SUCCESS;

				 }

		break;

		case 4: dwRet=GetMsg(anInput,&pOutput);
				if(dwRet!=0)
				 {
					 ErrorList();
					 *(panOutput)=pOutput;
					 return VSAA_SUCCESS;

				 }

		break;

		case 5:
				 dwRet=GetInBoxSummary(anInput,&pOutput);
				 if(dwRet!=0)
				 {
					 ErrorList();
					 *(panOutput)=pOutput;
					 return VSAA_SUCCESS;

				 }


		break;
	
	
	}

	MergeLists(anInput,pOutput,&pFinalOutput);
	//	*(panOutput)=pOutput;

	*(panOutput)=pFinalOutput;
		

	return VSAA_SUCCESS;
}

unsigned long GetMyInfo(char * pMyName,char *szMyEmailAddr)
{

	BOOL     resStatus=FALSE;

	long	dwStatus;
	CSequence    seqOutput;

	dwRet=0;

	CertResolutionInit();
	EmailResolutionInit();
   
	lpToken=strtok(pMyName,",");
	while(lpToken!=NULL)
	{

		    /*
			dwRet = EmailResolution(lpToken, &szMyEmailAddr);
			if(dwRet != 0)
			{
				
			}

			*/
			resStatus=TRUE;
			dwStatus= 0x0002;

			dwError = MyCertResolution(lpToken,(unsigned int *)&cbMyUserCertificate, &pbMyUserCertificate);
			if(dwError!=0)
			{
				dwStatus=0x0000;
			}

			///////Setting Addtion bits for Verification and Chain Validation Status
			///REV TYPE
			if(g_pInfo.RevocationType==0)//CRLDP
				dwStatus =dwStatus |VS_REVOCATION_CRLDP;
			else
				dwStatus =dwStatus |VS_REVOCATION_OCSP;

			///REV STATUS
			if(g_pInfo.RevocationStatus==0)//not revoked
				dwStatus=dwStatus |VS_REV_STATUS_NOT_REV;

			if(g_pInfo.RevocationStatus==1)
				dwStatus=dwStatus|VS_REV_STATUS_REVOKED;

			if(g_pInfo.RevocationStatus==2)
				dwStatus=dwStatus|VS_REVOCATION_FAILED;

			////Validation Type
			if(g_pInfo.ChainValidateType==0)
				dwStatus=dwStatus|VS_VALIDATION_TYPE_SERVER;

			if(g_pInfo.ChainValidateType==1)
				dwStatus=dwStatus|VS_VALIDATION_TYPE_CLIENT;

			if(g_pInfo.ChainValidateStatus==0)
				dwStatus=dwStatus | VS_VALIDATION_SUCCESS;
			else
				dwStatus=dwStatus|VS_VALIDATION_FAILED;




			////////Build ASN sequence
	
			CIA5String  ia5EmailID(strlen(lpToken),(unsigned char *)lpToken);
					
			CUniversalInteger	uiStatus(2, (_PBYTE)&dwStatus) ;
			COctetString       oUserCertificate(cbMyUserCertificate,pbMyUserCertificate);
			COctetString       oAddtionInfo(0,NULL);
			
			CBaseDERCollection  cbdcUserInfo;
			cbdcUserInfo=ia5EmailID+uiStatus+oUserCertificate+oAddtionInfo;

			CSequence 	cseqUserInfo;
			cseqUserInfo=cbdcUserInfo;
			seqOutput+=cseqUserInfo;
			/////////

			cbMyUserCertificate=0;
			if(pbMyUserCertificate!=NULL)
				free(pbMyUserCertificate);

			lpToken=strtok(NULL,",");
	}

	///////Encode and Create output list///////////////////////

	dwRet=CreateOutputList(seqOutput.BaseDERBlob->pbData,seqOutput.BaseDERBlob->cbData);
	if(dwRet!=0)
		return -1;
	
	return dwRet;
}

unsigned long GetSMIMEInfo(char * pUserName,char *szUserEmailAddr)
{

	BOOL         resStatus=FALSE;
	CSequence    seqOutput;

	char     szUserName[1024];
	
	long	 dwStatus ;

	dwError=0;
	CertResolutionInit();
	EmailResolutionInit();

	strcpy(szUserName,pUserName);
   
	lpToken=strtok(szUserName,",");
	while(lpToken!=NULL)
	{
			
		    /*
			dwError = EmailResolution(lpToken, &szUserEmailAddr);
			if(dwError != 0)
			{
				//EmailResolution failed
				//lpToken=strtok(NULL,",");
				//continue;
			}
			*/

			resStatus=TRUE;

			if(g_pInfo.UserSMIMECert==1)
			{
				dwError = UserCertResolution(lpToken,(unsigned int *)&cbSMIMECertificate, &pbSMIMECertificate);
				if(dwError==0)
					dwStatus=VS_ENC_CERT; //SMIME Attribute Signed PKCS#7
				else
					dwStatus=0x0000;//can't resolve
			}
			if(g_pInfo.UserSMIMECert==2)
			{
				dwError = MyCertResolution(lpToken,(unsigned int *)&cbSMIMECertificate, &pbSMIMECertificate);
				if(dwError==0)
					dwStatus=VS_X509_CERT; //X.509
				else
					dwStatus=0x0000;//can't resolve
	
			}


			///////Setting Addtion bits for Verification and Chain Validation Status
			///REV TYPE
			if(g_pInfo.RevocationType==0)//CRLDP
				dwStatus =dwStatus |VS_REVOCATION_CRLDP;
			else
				dwStatus =dwStatus |VS_REVOCATION_OCSP;

			///REV STATUS
			if(g_pInfo.RevocationStatus==0)//not revoked
				dwStatus=dwStatus |VS_REV_STATUS_NOT_REV;

			if(g_pInfo.RevocationStatus==1)
				dwStatus=dwStatus|VS_REV_STATUS_REVOKED;

			if(g_pInfo.RevocationStatus==2)
				dwStatus=dwStatus|VS_REVOCATION_FAILED;

			////Validation Type
			if(g_pInfo.ChainValidateType==0)
				dwStatus=dwStatus|VS_VALIDATION_TYPE_SERVER;

			if(g_pInfo.ChainValidateType==1)
				dwStatus=dwStatus|VS_VALIDATION_TYPE_CLIENT;

			if(g_pInfo.ChainValidateStatus==0)
				dwStatus=dwStatus | VS_VALIDATION_SUCCESS;
			else
				dwStatus=dwStatus|VS_VALIDATION_FAILED;



			////////Build ASN sequence
			CIA5String  ia5EmailID(strlen(lpToken),(unsigned char *)lpToken);
		
			

			CUniversalInteger	uiStatus(2, (_PBYTE)&dwStatus) ;
			COctetString       pOpaqueSignedPkcs7(cbSMIMECertificate,pbSMIMECertificate);
			COctetString       oAddtionInfo(0,NULL);
			//------------
			CBaseDERCollection  cdbcUserInfo;
			cdbcUserInfo=ia5EmailID+uiStatus+pOpaqueSignedPkcs7+oAddtionInfo;

			CSequence 	cSeqUserInfo;
			cSeqUserInfo=cdbcUserInfo;
			seqOutput+=cSeqUserInfo;
			/////////
				

			cbSMIMECertificate=0;
			if(pbSMIMECertificate)
			{
					free(pbSMIMECertificate);
					pbSMIMECertificate=NULL;

			}


			lpToken=strtok(NULL,",");
	}

	///////Encode and Create Output List ///////////////////////
	if(seqOutput.cbData!=0)
	{
		dwError=CreateOutputList(seqOutput.BaseDERBlob->pbData,seqOutput.BaseDERBlob->cbData);
		if(dwError!=0)
			return dwError;
	}
	return dwError;


}


HRESULT DecodeUserInfo(char *pUserInfo)
{
	
	PBYTE				pbDecodedUserInfo;
	DWORD				cbDecodedUserInfo;

	PCERT_INFO          pSignCert=NULL,pEncCert=NULL;

	HRESULT             hr=S_OK;
	

	_Base64Decode(pUserInfo,strlen(pUserInfo),NULL,	&cbDecodedUserInfo);

	pbDecodedUserInfo = (BYTE *) malloc(cbDecodedUserInfo);
	if(pbDecodedUserInfo==NULL)
	{
		hr=E_OUTOFMEMORY;
		return hr;
			
	}

	_Base64Decode(pUserInfo,strlen(pUserInfo),(char *)pbDecodedUserInfo,
														&cbDecodedUserInfo) ;
	

	
	CBaseDERCollection     cbdcUserInfo(cbDecodedUserInfo,pbDecodedUserInfo);
	CBaseDERHierarchy	   cbdhUserInfo(cbdcUserInfo);

	if(cbdhUserInfo.dwErrorCode == 0xFFFFFFFF)
	{
		hr=E_FAIL;
		return hr;
	}


	DERTree *dtUserInfo = &(cbdhUserInfo.m_DERTree);

	if(dtUserInfo->currentBaseDER->Type != SEQUENCE)
	{
		hr=E_FAIL;
		return hr;
	}

	DERTree *dtUserInfoSeq=dtUserInfo->rightDERTree;


	do
	{
				if(!dtUserInfoSeq && dtUserInfoSeq->currentBaseDER->Type != SEQUENCE)
				{
					hr=E_FAIL;
					break;
				}

				/*
					UserInfo ::= SEQUENCE {
					PrintableString		FullName,
					PrintableString		Email-ID,
					UniversalInteger    iStatus
					OctetString         Certificate
					}
				*/

				

				//Getting FullName From Seq
				DERTree *dtFullName = dtUserInfoSeq->rightDERTree;
				//Make sure that the derblob in the dtFullName of type Printable String
				if(!dtFullName || dtFullName->currentBaseDER->Type != PRINTABLE_STRING)
				{
					hr=E_FAIL;
					break;
				}

				CPrintableString* cpsFullName = (CPrintableString*)dtFullName->currentBaseDER;
				
				char   FullName[256];
				sprintf(FullName,"%s", (cpsFullName->pbData));


				////Getting E-mail from Seq
				DERTree *dtEmail = dtFullName->nextDERTree;
				//Make sure that the derblob in the dtEMAIl of type Printable String
				if(!dtEmail || dtEmail->currentBaseDER->Type != PRINTABLE_STRING)
				{
					hr=E_FAIL;
					break;
				}

				CPrintableString* cpsEmail = (CPrintableString*)dtEmail->currentBaseDER;

				char   Email[256];
				sprintf(Email,"%s", (cpsEmail->pbData));


				////Getting uiStatus from Seq
				DERTree *dtuiStatus = dtEmail->nextDERTree;
				//Make sure that the derblob in the dtuiStatus of type universal integer
				if(!dtuiStatus || dtuiStatus->currentBaseDER->Type != UNIVERSAL_INTEGER)
				{
					hr=E_FAIL;
					break;
				}

				CUniversalInteger* pcuiStatus = (CUniversalInteger*)dtuiStatus->currentBaseDER;

				//Obtain the version bytes
				unsigned char byteStatus[4];
				for(unsigned int i = 0;i < pcuiStatus->cbData; ++i)
					byteStatus[i] = pcuiStatus->pbData[i];

				for(unsigned int j=i;j<4; ++j)
					byteStatus[j] = 0x00;
				
				DWORD dwStatus  = *((_DWORD*)byteStatus);

				if( dwStatus & VS_X509_CERT)
							 dwStatus=VS_X509_CERT;





				////Getting Cert from Seq
				DERTree *dtosUserCert = dtuiStatus->nextDERTree;
				//Make sure that the derblob in the dtuiStatus of type universal integer
				if(!dtosUserCert || dtosUserCert->currentBaseDER->Type != OCTET_STRING)
				{
					hr=E_FAIL;
					break;
				}

				if(dtosUserCert->currentBaseDER->cbData==0)
								 dtosUserCert->currentBaseDER->pbData=NULL;


				dtUserInfoSeq=dtUserInfoSeq->nextDERTree;

	
	}
	while(dtUserInfoSeq!=NULL);


	///////////
	if(pbDecodedUserInfo!=NULL)
				free(pbDecodedUserInfo);


	return hr;


}

unsigned long ErrorList()
{
	///////build the output list
	pOutput = (VSAA_NAME *)calloc(2, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}

	pOutput[0].pszName = strdup("ResolveNames");
	if (pOutput[0].pszName == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	pOutput[0].pszValue = strdup("error");
	if (pOutput[0].pszValue == NULL)
	{
		Release(&pOutput);
		return -1;
	}
	
	///////2th element/////////////////
	pOutput[1].pszName=NULL;
	pOutput[1].pszValue=NULL;
	return 0;
}


unsigned long CreateOutputList(BYTE  *pbData, DWORD cbData)
{
	char     *pszB64;

	///////Encode the data///////////////////////
	unsigned int dwB64Size;
	_Base64Encode((char*)pbData,cbData,NULL,&dwB64Size);
	pszB64 = new char[dwB64Size+1];
	if(!pszB64)
		return -1;
	else
	{
		_Base64Encode((char*)pbData,cbData,pszB64,&dwB64Size);
		pszB64[dwB64Size] = '\0';
		
	}

	///////build the output list
	pOutput = (VSAA_NAME *)calloc(2, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}

	/////First element//////////////////
	pOutput[0].pszName = strdup("ResolveNames");
	if (pOutput[0].pszName == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	pOutput[0].pszValue = strdup(pszB64);
	if (pOutput[0].pszValue == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	///////2th element/////////////////
	pOutput[1].pszName=NULL;
	pOutput[1].pszValue=NULL;

	if(pszB64!=NULL)
			free(pszB64);

	return 0;
}

unsigned long EncodeVar(char*szNameOREmail,char **szEncodedInfo)
{
char * lpToken=NULL;
	
	/*
	 Create the following object 
	NameOREmail  := SEQUENCE {
						
						    SEQUENCE{
								CIA5String 	NameOREmail1,
							}
							......
							......
	  			  }
	*/

	CSequence   cseqsNameOREmail;
		
	lpToken=strtok(szNameOREmail,",");
	while(lpToken!=NULL)
	{
	
		CIA5String ia5NameOREmail(strlen(lpToken),(unsigned char*)lpToken);
		CBaseDERCollection	cbdcNameOREmail;
		cbdcNameOREmail=ia5NameOREmail;

		//inner sequence
		CSequence cseqNameOREmail;
		cseqNameOREmail=cbdcNameOREmail;


		CBaseDERCollection cdbcSeqCollection;
		cdbcSeqCollection=cseqNameOREmail;
		
		cseqsNameOREmail+=cdbcSeqCollection;
		

		lpToken=strtok(NULL,",");
	}

	
	

	/////encode the DER blob to base64
	DWORD dwB64Size;
	_Base64Encode((char*)(cseqsNameOREmail.BaseDERBlob->pbData),cseqsNameOREmail.BaseDERBlob->cbData,
		NULL,(unsigned int *)&dwB64Size);
	*szEncodedInfo = new char[dwB64Size+1];

	memset(*szEncodedInfo,0,dwB64Size+1);

	if(!*szEncodedInfo)
		return -1;
	else
	{
		_Base64Encode((char*)(cseqsNameOREmail.BaseDERBlob->pbData),cseqsNameOREmail.BaseDERBlob->cbData,
			*szEncodedInfo,(unsigned int *)&dwB64Size);

		(*szEncodedInfo)[dwB64Size] = '\0';
		
	}

	return S_OK;

}
unsigned long DecodePostedVars(char * pInNames)
{
	
	/*
	PBYTE             m_pbNames;
	DWORD             m_cbNames;

	_Base64Decode(pInNames,
					strlen(pInNames),
					NULL,
					&m_cbNames) ;

	m_pbNames = (BYTE *) malloc(m_cbNames+1);
	

	strcpy(pOutNames,"");
	
	_Base64Decode(pInNames,
					strlen(pInNames),
					(char *)m_pbNames,
					&m_cbNames) ;

	CBaseDERCollection     cBasedc(m_cbNames,m_pbNames);
	CBaseDERHierarchy		cbdHier(cBasedc);
	char    buffer[256];

	DERTree *ptrDERTree = &(cbdHier.m_DERTree);
	ptrDERTree=ptrDERTree->rightDERTree;

	while( ptrDERTree != NULL)
	{
		sprintf(buffer,"%s", (ptrDERTree->currentBaseDER->pbData));
		strcat(pOutNames,buffer);
		ptrDERTree = ptrDERTree->nextDERTree;
		if(ptrDERTree!=NULL)
				strcat(pOutNames,",");
			
	}

	pOutNames[m_cbNames+1]='\0';

	


	  unsigned int byteLen = 2;
	  CUniversalInteger cuiLen(1,(unsigned char*)&byteLen);

	  CUniversalInteger pcuiStatus = cuiLen;

	  //Obtain the version bytes
	  unsigned char byteStatus[4];
      for(unsigned int i = 0;i < pcuiStatus.cbData; ++i)
		byteStatus[i] = pcuiStatus.pbData[i];

	  for(unsigned int j=i;j<4; ++j)
		byteStatus[j] = 0x00;
	
	  DWORD dwStatus  = *((_DWORD*)byteStatus);

	  */




	ZeroMemory(pOutNames,sizeof(pOutNames));

	PBYTE				pbDecodedUserInfo;
	DWORD				cbDecodedUserInfo;

	HRESULT             hr=S_OK;
	

	_Base64Decode(pInNames,strlen(pInNames),NULL,	&cbDecodedUserInfo);

	pbDecodedUserInfo = (BYTE *) malloc(cbDecodedUserInfo+1);
	if(pbDecodedUserInfo==NULL)
	{
		hr=E_OUTOFMEMORY;
		return hr;
			
	}

	_Base64Decode(pInNames,strlen(pInNames),(char *)pbDecodedUserInfo,
														&cbDecodedUserInfo) ;
	

	
	CBaseDERCollection     cbdcUserInfo(cbDecodedUserInfo,pbDecodedUserInfo);
	CBaseDERHierarchy	   cbdhUserInfo(cbdcUserInfo);

	if(cbdhUserInfo.dwErrorCode == 0xFFFFFFFF)
	{
		hr=E_FAIL;
		return hr;
	}


	DERTree *dtUserInfo = &(cbdhUserInfo.m_DERTree);

	if(dtUserInfo->currentBaseDER->Type != SEQUENCE)
	{
		hr=E_FAIL;
		return hr;
	}

	DERTree *dtUserInfoSeq = dtUserInfo->rightDERTree;
	
	do
	{
		if(!dtUserInfoSeq && dtUserInfoSeq->currentBaseDER->Type != SEQUENCE)
				{
					hr=E_FAIL;
					break;
				}

				/*
					UserInfo ::= SEQUENCE {
					IA5String		Email,
					}
				*/

				

				//Getting Email From Seq
				DERTree *dtEmail = dtUserInfoSeq->rightDERTree;
				//Make sure that the derblob in the dtFullName of type Printable String
				if(!dtEmail || dtEmail->currentBaseDER->Type != IA5_STRING)
				{
					hr=E_FAIL;
					break;
				}

				CIA5String* ia5Email = (CIA5String*)dtEmail->currentBaseDER;
				
				char   szEmail[256];
				sprintf(szEmail,"%s", (ia5Email->pbData));
				strcat(pOutNames,szEmail);
				strcat(pOutNames,",");

		dtUserInfoSeq=dtUserInfoSeq->nextDERTree;
	}
    while(dtUserInfoSeq!=NULL);

	return hr;

}

/*******************************************************************/
void FreeEntries(VSAA_NAME **anInput)
/*******************************************************************/
{
	Release(anInput);

}


static VSAA_STATUS MergeLists(const VSAA_NAME inList[],	const VSAA_NAME OutList[],
						VSAA_NAME **FinalList)
{
	VSAA_STATUS status = VSAA_SUCCESS;
	VSAA_NAME *all = NULL;
	size_t i, j, l;
	size_t inListSize = Entries(inList) - 1;
	size_t OutListSize = Entries(OutList) - 1;

	/* Allocate spaces for all needed structures */
	all = (VSAA_NAME *) calloc(inListSize + OutListSize + 1, sizeof(VSAA_NAME));
	if (all == NULL)
		return status;

	/* first, copy all entries from inList list to all list */
	for (i=0; i<inListSize; i++)
	{
		
		all[i].pszName  = strdup(inList[i].pszName);
		all[i].pszValue = strdup(inList[i].pszValue);
	}

	if (OutList)
	{
	/* Now, merge the addList to all list */
		for (j=0; j<OutListSize; j++)
		{
			/* Search through the inList list to find matched name */
			for (l=0; l<inListSize; l++)
			{
				if (!strcmp(all[l].pszName, OutList[j].pszName))
				{
					if (all[l].pszValue)
						free(all[l].pszValue);
					/* Override existing value */
					all[l].pszValue = strdup(OutList[j].pszValue);
					break;
				}
			}
			if (l >= inListSize) /* if no duplicate name */
			{
				all[i].pszName  = strdup(OutList[j].pszName);
				all[i].pszValue = strdup(OutList[j].pszValue);
				i++;
			}
		}
	}

	/* Null out the last pair */
	all[i].pszName = NULL;
	all[i].pszValue = NULL;

	*FinalList = all;

	return status;
}


