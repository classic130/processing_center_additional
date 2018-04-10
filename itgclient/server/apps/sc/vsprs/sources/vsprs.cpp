///////////////////////////////////////////////////////////////////////////////
//																			 //
//	File Name		:	VSPS_Macros.h										 //
//																			 //
//	Description		:	VeriSign Proxy Recipient API for Secure Guaranteed	 //
//                      Messaging Service.                                   //   
//																			 //
//	Date			:	Feb 27, 2000										 //
//																			 //
//	Author			:	Isaac Liu     										 //
//																			 //
//																			 //
//	Change Log		:	Ajay												 //
//			- Changed function VSPRS_DecryptVerifySMIMEMessage()			 //
//			  to fix bug related to _bstr_t and large messages				 //
//																			 //	
//			- Ramakant 11/01/2001											 //
//			  Changed functions to incorporate new VSSC parameter
//			   pvarAppStatus
//			- Ramakant 11/06/2001
//				- Changed the VSPRSInfo structure to make it a pointer		
//				instead of a copy. Made changes to reflect those changes	
//			    - Fixed a bug related to zero byte attachments 
//////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "vsprs.h"
#include "certinfo.h"


/////PTA related headers files///////////////

#include "ptav3.h"
#include "ptadllapi.h"
#include "ptaerrs.h"
#include "ptadefines.h"

#define		VS_SHA_1							32772

#define MY_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)


#include "VSSC_i.c"
#include "VSSC.h"

extern IVSPTA *pVSPTA;
extern IVSSC *pVSSC;
extern IVSSCDllApi *pVSSCDllApi;

CProxyRecipients::CProxyRecipients (VSPRSInfo *proxyInfo)
{

	if (proxyInfo != NULL) CopyProxyInfo(proxyInfo);
	mReEncrypted = mRoaming = FALSE;
	mMsgInfo.SmimeType = MSG_None;
	
	mCStatus = CS_None;
	mAttachment = NULL;

	return;
}


CProxyRecipients::~CProxyRecipients ()
{
	
	
	Release(); // releases all interfaces used. i.e PTA, VSSC.
	
	return;
}

HRESULT CProxyRecipients::VSPRS_Initialize(VSPRSInfo *proxyInfo,VARIANT* i_pvarAppStatus)
{

	HRESULT retVal = S_OK;

	if (proxyInfo != NULL)
		CopyProxyInfo(proxyInfo);

	// check if we are doing encryption or decrypption.
	if (proxyInfo->UseEncCert == YES) 
		  VSPRS_SetReEncrypted(TRUE);

	  
	if (proxyInfo->Roaming == YES) 
		  VSPRS_SetRoaming(TRUE);

	do {
	  // check if we have a valid info inside the VSPRSInfo struct.
	  if ((retVal = ValidateProxyInfo()) != S_OK) break;

	 
	  if (( retVal = InitPTA(i_pvarAppStatus)) != 0) break;

	} while (0);
	return retVal;
}

//	9/28/2001	- Changed function VSPRS_DecryptVerifySMIMEMessage()	//
//			  to fix bug related to _bstr_t and large messages			//
HRESULT CProxyRecipients::VSPRS_DecryptVerifySMIMEMessage(VARIANT* i_pvarAppStatus)
{

	HRESULT retVal = S_OK;
	//DWORD       dwDecBlobLen=0, signType = 0;
	//BYTE		*pByteDecBlob = NULL;
	//PCHAR		szBody = NULL;
	//SMIMETYPE	smimeType;
	//VSPRS_MSGINFO mMsgInfo;
	//VS_PKCS7_INFO pkcs7Info;

	do {

		VARIANT pvarSMIMEMsg;

		//VariantClear(&pvarSMIMEMsg);

        // use _bstr_t for string conversion.
	    //_bstr_t bstrTmp;
		const char *bstrTmp;
		pvarSMIMEMsg.vt = VT_BSTR;
		//pvarSMIMEMsg.bstrVal = SysAllocString((bstrTmp = (const char *)mVSPRSInfo.EncryptedMIMEMessage));
		bstrTmp = (const char *)mpVSPRSInfo->EncryptedMIMEMessage;
		pvarSMIMEMsg.bstrVal = _MultiToWideString((char *)bstrTmp);
		
		// set this field to let VSSC know that the data is not encoded
		VARIANT valbURLencodedData;
		valbURLencodedData.vt = VT_BOOL;
		valbURLencodedData.boolVal = false;

		pVSSC->put_URLEncodeData(valbURLencodedData);

		// this indicates which components to use to do the ASN decoding
		VARIANT	valbUseSimder;
		valbUseSimder.vt = VT_BOOL;
		valbUseSimder.boolVal = false;

		pVSSC->put_UseSimder(valbUseSimder);
		
		retVal = pVSSC->Decompose(&pvarSMIMEMsg, i_pvarAppStatus);
		
		// free this memory imediately as it might be really big
		VariantClear(&pvarSMIMEMsg);
		
		// check whether the decompose worked correctly
		if (retVal  != 0)
			break;

		SetMsgInfo();  // set up To, From, Subject, Name, etc.

		if (mReEncrypted) {
			// Handle Re-Encryption.
			if ((retVal = HandleReEncryption(i_pvarAppStatus)) != 0)
				break;
		}

	} while (0);
	return retVal;
}





HRESULT CProxyRecipients::HandleReEncryption(VARIANT* i_pvarAppStatus)
{
	HRESULT retVal = S_OK;

	VARIANT varVSSC;

	do {

		////// Setting From
		VariantInit(&varVSSC);
		
		////From - This should be from PRC, the SYSTEM.
	
		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString((PCHAR)(const char*)mpVSPRSInfo->SSCEmail);
		pVSSC->put_FromInfo(varVSSC);
		VariantClear(&varVSSC);


		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString((PCHAR)(const char*)mpVSPRSInfo->ReEncryptEmail);
		pVSSC->put_ToRecipientsInfo(varVSSC);
		VariantClear(&varVSSC);
		
		// Encryption Requires SMIME Cert Ressolution.
		
		if ((retVal= pVSSC->SMIMECertificateResolution(i_pvarAppStatus))!= 0)
			break;
		

		// Get Subject
		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString((PCHAR)(const char*)mpVSPRSInfo->SSCSubject);
		pVSSC->put_Subject(varVSSC);
		VariantClear(&varVSSC);

		//VariantInit(&varVSSC);
		varVSSC.vt= VT_BSTR;
		varVSSC.bstrVal=_MultiToWideString((PCHAR)(const char*)mMsgInfo.Body);
		pVSSC->put_Body(varVSSC);
		VariantClear(&varVSSC);

		//VariantInit(&varVSSC);
		varVSSC.vt= VT_I2;
		varVSSC.iVal=MSG_Enc;
		pVSSC->put_MsgType(varVSSC);
		VariantClear(&varVSSC);
		
		if ((retVal=pVSSC->Compose(i_pvarAppStatus)) != 0)
			break;

		

		//VariantInit(&varVSSC);
		pVSSC->get_GetMsg(&varVSSC);

		mMsgInfo.ReEncryptedContent = (const char *)_WideToMultiString(varVSSC.bstrVal);

		// set correct status. 
		switch(mMsgInfo.SmimeType) {
			case MSG_Sign:	mCStatus = CS_VerReEnc;
							break;
			case MSG_Enc:	mCStatus = CS_DecReEnc;
							break;
			case MSG_SignEnc:	mCStatus = CS_DecVerReEnc;
							break;
			default:	break;
		}

	} while (0);

	return retVal;

} 
void CProxyRecipients::SetMsgInfo()
{

	VARIANT msgType;

	//VariantClear(&msgType);
	VariantInit(&msgType);
	
	// Get Input mime type i.e signed, opaqued signed, signed-encypted, etc.
	pVSSC->get_MsgType(&msgType);

	
	// Set the appropriate output response.
	switch(msgType.iVal) {
		case 1:	mMsgInfo.SmimeType = MSG_Sign;
				mCStatus = CS_Ver;
				break;

		case 2: mMsgInfo.SmimeType = MSG_Enc;
				mCStatus = CS_Dec;
				break;

		case 3: mMsgInfo.SmimeType = MSG_SignEnc;
				mCStatus = CS_DecVer;
				break;

		default:	mMsgInfo.SmimeType = MSG_None;
					mCStatus = CS_None;
	}

	// Get From
	VARIANT   varTmp;
	
	
	//VariantClear(&varTmp);
	VariantInit(&varTmp);

	pVSSC->get_FromInfo(&varTmp);
	mMsgInfo.From = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get To
	VariantClear(&varTmp);
	pVSSC->get_ToRecipientsInfo(&varTmp);
	mMsgInfo.To = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get Subject
	VariantClear(&varTmp);
	pVSSC->get_Subject(&varTmp);
	mMsgInfo.Subject = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get Date
	VariantClear(&varTmp);
	pVSSC->get_Date(&varTmp);
	mMsgInfo.Date = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get CC
	VariantClear(&varTmp);
	pVSSC->get_CcRecipientsInfo(&varTmp);
	mMsgInfo.Cc = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get BCC
	VariantClear(&varTmp);
	pVSSC->get_BccRecipientsInfo(&varTmp);
	mMsgInfo.Bcc = (const char *)_WideToMultiString(varTmp.bstrVal);

	// Get Body
	VariantClear(&varTmp);
	pVSSC->get_Body(&varTmp);
	mMsgInfo.Body = (const char *)_WideToMultiString(varTmp.bstrVal);


}



 VSPRSAttachment * CProxyRecipients::VSPRS_GetAttachmentObj(VARIANT* i_pvarAppStatus)
{

	HRESULT retVal = S_OK;

	
	FILEINFO *pCurrent =NULL;
	FILEINFO *pNode = NULL;
	FILEINFO *pHead = NULL;
	DWORD pcBufLen = 0;
	VARIANT    varFileList;
	VARIANT   varTmp,varContent;

	do {
	  if (mAttachment == NULL) {
		
		//VariantClear(&varFileList);
        /////Comma separated fileName
		if ((retVal=pVSSC->get_AttachedFileList(&varFileList)) != S_OK)
			break;

		// chck if we have attachments.
		if (varFileList.bstrVal == NULL) break;

		char *pFileList=_WideToMultiString(varFileList.bstrVal);

		
		

		char *szFileName=strtok(pFileList,",");
		while(szFileName!=NULL)
		{

				
				pNode = (FILEINFO *) malloc(sizeof(FILEINFO));
				memset(pNode, 0, sizeof(FILEINFO));
				
				
				strcpy(pNode->szFileName, szFileName);


				//VariantClear(&varTmp);
				//VariantClear(&varContent);

				varTmp.vt=VT_BSTR;
				varTmp.bstrVal=_MultiToWideString(szFileName);

				if ((retVal=pVSSCDllApi->GetAttachFileContent(&varTmp,i_pvarAppStatus,&varContent)) != S_OK)
					break;

				pcBufLen = varContent.parray->rgsabound[0].cElements;

				pNode->cbFileSize = pcBufLen;

				szFileName=strtok(NULL,",");
				
				// make sure that file has more than zero bytes
				if ( pcBufLen > 0 )
				{
			
					pNode->pbFileData = new BYTE[pcBufLen]; //Allocate a buffer to store the data

					if(pNode->pbFileData != NULL)
					{
						memset(pNode->pbFileData, 0, pcBufLen);
						void * pArrayData;

						//Obtain safe pointer to the array
						SafeArrayAccessData(varContent.parray,&pArrayData);

						//Copy the bitmap into our buffer
						memcpy(pNode->pbFileData, pArrayData, pcBufLen);

						//Unlock the variant data
						SafeArrayUnaccessData(varContent.parray);


					} // end
				}

				if (pHead == NULL && pCurrent == NULL) {
					pHead = pNode; 
					pCurrent = pHead;
				
				}
				else {
					pCurrent->next = pNode;
					pCurrent = pNode;					
				}
				
				pCurrent->next = NULL;

		} // end While

		if (retVal != S_OK) break;
		mAttachment = new VSPRSAttachment(pHead);
	  }

	} while (0); // 
	
	// Caller should check if NULL ptr is returned.
	// Indicates error.
	if (retVal)
		mAttachment = NULL;

	return mAttachment;
}


HRESULT CProxyRecipients::ValidateProxyInfo()
{
	HRESULT retVal = S_OK;

	do {
		
		if (mpVSPRSInfo->PTAProfile.Length() == 0) {
			retVal = VSPRS_OPEN_PTA_FAILED;
			break;
		}
		if (mpVSPRSInfo->PTAApplication.Length() == 0) {
			retVal = VSPRS_INVALID_PTA_APPLICATION;
			break;
		}
		if (mpVSPRSInfo->EncryptedMIMEMessage.Length() == 0) {
			retVal = VSPRS_INVALID_EML_MESSAGE;
			break;
		}
		if ((mpVSPRSInfo->UseEncCert == YES) && 
			((mpVSPRSInfo->ReEncryptEmail.Length() == 0) ||
			  mpVSPRSInfo->CertResolutionURL.Length() ==0)) {
			retVal = VSPRS_MISSING_REENCRYPT_PARMS;
			break;
		}
		if (mpVSPRSInfo->ClientInfo.Length() == 0 ||
			mpVSPRSInfo->ClientInfoSig.Length() == 0) {
			retVal = VSPRS_MISSING_ROAMING_CLIENT_INFO;
			break;
		}
		if (mpVSPRSInfo->SSCEmail.Length() == 0) {
			retVal = VSPRS_MISSING_SSC_EMAIL;
			break;
		}
	} while (0);
	return retVal;
}





void CProxyRecipients::CopyProxyInfo(VSPRSInfo *prsInfo)
{


	
	if (prsInfo != NULL) {

		/*mVSPRSInfo.PTAProfile = prsInfo->PTAProfile;             // input: required to open PTA profile
		mVSPRSInfo.PTAPassword = prsInfo->PTAPassword;          // input: required to open PTA profile
		mVSPRSInfo.PTAApplication = prsInfo->PTAApplication;         // input: required to open PTA profile
		mVSPRSInfo.PassWordTimeOut = prsInfo->PassWordTimeOut;        // input: required to open PTA profile
		mVSPRSInfo.EncryptedMIMEMessage = prsInfo->EncryptedMIMEMessage;   // input: encrypted MIME message in EML format.
		mVSPRSInfo.AuthDLL = prsInfo->AuthDLL;				  // input: Auth DLL for PTA to bypass the UI.
		mVSPRSInfo.ReEncryptEmail = prsInfo->ReEncryptEmail;			      // input: this is the end-user cert used to encrypt
		mVSPRSInfo.UseEncCert= prsInfo->UseEncCert;	
		mVSPRSInfo.Base64Attachment = prsInfo->Base64Attachment;	
		
		mVSPRSInfo.ClientInfo = prsInfo->ClientInfo;	
		mVSPRSInfo.ClientInfoSig = prsInfo->ClientInfoSig;
		mVSPRSInfo.Roaming = prsInfo->Roaming;

		mVSPRSInfo.CertResolutionURL = prsInfo->CertResolutionURL;
		mVSPRSInfo.SSCEmail = prsInfo->SSCEmail;
		mVSPRSInfo.SSCSubject = prsInfo->SSCSubject;
		mVSPRSInfo.SCType = prsInfo->SCType;

		mVSPRSInfo.CertResSource = prsInfo->CertResSource;*/

		mpVSPRSInfo = prsInfo;
	}
		
	
	return;
}

