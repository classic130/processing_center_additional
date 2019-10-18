#include "vsmimelib.h"


// This function to be moved to VSSC and commented out from here
void CreateEncryptedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  )
{

	//VSSCMessage Msg;
	VSSCMessage *Msg = VSSCMessage :: NewMessage("",0);

	// From
	if(pMsgInfo->szFrom && strlen(pMsgInfo->szFrom) > 1)
	{
		Msg->GetHeaders().GetFrom().SetString(pMsgInfo->szFrom);
	}
	
	// To
	if(pMsgInfo->szTo)
	{
		Msg->GetHeaders().GetTo().SetString(pMsgInfo->szTo);
	}

	// Subject
	if(pMsgInfo->szSubject && strlen(pMsgInfo->szSubject) > 1)
	{
		Msg->GetHeaders().GetSubject().SetString(pMsgInfo->szSubject);
	}

	// Date
	char szDate[256];

	FormatRFC822Date(szDate);
	
	// Remove comment later - testing messages without headers.
	//Msg->GetHeaders().GetDate().SetString(szDate);

	VSSCHeaders& headers = Msg->GetHeaders();

	//application/pkcs7-mime;smime-type=enveloped-data;name=smime.p7m

	// Remove comment later - testing messages without headers.
	
	headers.GetContentType().SetTypeString("application");
	headers.GetContentType().SetSubTypeString("pkcs7-mime");
	headers.GetContentType().SetSMIMEType("enveloped-data");
	/*
	headers.GetContentType().SetName("smime.p7m");
	headers.GetContentTransferEncoding().SetString("base64");
	headers.GetContentDisposition().SetDispTypeString("application");
	headers.GetContentDisposition().SetFileName("smime.p7m");
	*/

	char *szSMIMEEntity = NULL;
	CreateSMIMEEntity(pFileInfo, pBodyInfo, &szSMIMEEntity,false);

	// Use this for encryption.
	// and then add the body.
	// Right now I'm reading from a file.

	

	FILE *fp = NULL;
	fp = fopen("encbase64.txt", "rb");

	fseek(fp, 0, SEEK_END);
	int nSize = ftell(fp);
	rewind(fp);

	char *szCont = (char*)malloc(nSize + 1);
	fread(szCont, 1, nSize, fp);
	szCont[nSize] = '\0';

	fclose(fp);
	Msg->GetBody().SetString(szCont);
	Msg->Assemble();

	VSSCString vsscMsg = Msg->GetString();
	char *szMsgTemp = vsscMsg.GetString();

	WriteToFile(szMsgTemp);

	*szMsg = (char *)malloc(strlen(szMsgTemp) + 1);
	strcpy(*szMsg, szMsgTemp);

}

// This function to be moved to VSSC and commented out from here
void CreateClearSignedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  )
{

	// This can be used when constructed a signed and encrypted message
	// The only change required is not to set the RFC822 headers.

	//VSSCMessage Msg;
	VSSCMessage *Msg = VSSCMessage :: NewMessage("",0);
	// From
	if(pMsgInfo->szFrom && strlen(pMsgInfo->szFrom) > 1)
	{
		Msg->GetHeaders().GetFrom().SetString(pMsgInfo->szFrom);
	}
	
	// To
	if(pMsgInfo->szTo)
	{
		Msg->GetHeaders().GetTo().SetString(pMsgInfo->szTo);
	}

	// Subject
	if(pMsgInfo->szSubject && strlen(pMsgInfo->szSubject) > 1)
	{
		Msg->GetHeaders().GetSubject().SetString(pMsgInfo->szSubject);
	}

	// Date
	char szDate[256];
	FormatRFC822Date(szDate);
	Msg->GetHeaders().GetDate().SetString(szDate);
	//Msg->GetHeaders().GetDate().SetString("Tue, 19 Jun 2001 10:19:17 -0700");

	VSSCHeaders& headers = Msg->GetHeaders();

	headers.GetContentType().SetTypeString("Multipart");
	headers.GetContentType().SetSubTypeString("signed");
	headers.GetContentType().SetProtocol("application/pkcs7-signature");
	headers.GetContentType().SetMicalg("SHA1");
	//headers.GetContentType().SetBoundary("--OutBoudaryAADFSDF");
	headers.GetContentType().CreateBoundary();

	// Create the first outer bodypart
	// This bodypart can be mulitpart.

	VSSCString vsscBodyPart;
	char *szBodyPart = NULL;

	VSSCBodyPart *outerbodyPart1;
	

	// vsscEntityStr is the entity data which should be used for signing or encryption.
	char *szSMIMEEntity = NULL;
	CreateSMIMEEntity(pFileInfo, pBodyInfo, &szSMIMEEntity,false);

	VSSCString vsscEntityStr(szSMIMEEntity);

	outerbodyPart1 = VSSCBodyPart :: NewBodyPart(vsscEntityStr, 0);

	// Now the create the outer second bodypart
	VSSCBodyPart outerbodyPart2;

	VSSCHeaders& headers3 = outerbodyPart2.GetHeaders();

	headers3.GetContentType().SetTypeString("application");
	headers3.GetContentType().SetSubTypeString("pkcs7-signature");
	headers3.GetContentType().SetName("smime.p7s");
	headers3.GetContentTransferEncoding().SetString("base64");
	headers3.GetContentDisposition().SetDispTypeString("attachment");
	headers3.GetContentDisposition().SetFileName("smime.p7s");

	FILE *fp = NULL;
	fp = fopen("base64.txt", "rb");

	fseek(fp, 0, SEEK_END);
	int nSize = ftell(fp);
	rewind(fp);

	char *szCont = (char*)malloc(nSize + 1);
	fread(szCont, 1, nSize, fp);
	szCont[nSize] = '\0';

	fclose(fp);

	outerbodyPart2.GetBody().SetString(szCont);

	Msg->GetBody().AddBodyPart(outerbodyPart1);
	Msg->GetBody().AddBodyPart(&outerbodyPart2);

	Msg->Assemble();

	VSSCString vsscString = Msg->GetString();
	char *szFinalMsg = vsscString.GetString();
	
	WriteToFile(szFinalMsg);

	*szMsg = (char *)malloc(strlen(szFinalMsg) + 1);
	strcpy(*szMsg, szFinalMsg);

}

// This function to be moved to VSSC and commented out from here
void CreateOpaqueSignedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  )
{

	//VSSCMessage Msg;
	VSSCMessage *Msg = VSSCMessage :: NewMessage("",0);

	// From
	if(pMsgInfo->szFrom && strlen(pMsgInfo->szFrom) > 1)
	{
		Msg->GetHeaders().GetFrom().SetString(pMsgInfo->szFrom);
	}
	
	// To
	if(pMsgInfo->szTo)
	{
		Msg->GetHeaders().GetTo().SetString(pMsgInfo->szTo);
	}

	// Subject
	if(pMsgInfo->szSubject && strlen(pMsgInfo->szSubject) > 1)
	{
		Msg->GetHeaders().GetSubject().SetString(pMsgInfo->szSubject);
	}

	// Date
	char szDate[256];
	FormatRFC822Date(szDate);
	Msg->GetHeaders().GetDate().SetString(szDate);
	//Msg.GetHeaders().GetDate().SetString("Tue, 19 Jun 2001 10:19:17 -0700");

	VSSCHeaders& headers = Msg->GetHeaders();

	//application/pkcs7-mime;smime-type=enveloped-data;name=smime.p7m

	headers.GetContentType().SetTypeString("application");
	headers.GetContentType().SetSubTypeString("pkcs7-mime");
	headers.GetContentType().SetSMIMEType("signed-data");
	headers.GetContentType().SetName("smime.p7m");
	headers.GetContentTransferEncoding().SetString("base64");
	headers.GetContentDisposition().SetDispTypeString("application");
	headers.GetContentDisposition().SetFileName("smime.p7m");

	char *szSMIMEEntity = NULL;
	CreateSMIMEEntity(pFileInfo, pBodyInfo, &szSMIMEEntity,false);

	// Use this for encryption.
	// and then add the body.
	// Right now I'm reading from a file.

	

	FILE *fp = NULL;
	fp = fopen("opqbase64.txt", "rb");

	fseek(fp, 0, SEEK_END);
	int nSize = ftell(fp);
	rewind(fp);

	char *szCont = (char*)malloc(nSize + 1);
	fread(szCont, 1, nSize, fp);
	szCont[nSize] = '\0';

	fclose(fp);
	Msg->GetBody().SetString(szCont);
	Msg->Assemble();

	VSSCString vsscMsg = Msg->GetString();
	char *szMsgTemp = vsscMsg.GetString();

	WriteToFile(szMsgTemp);

	*szMsg = (char *)malloc(strlen(szMsgTemp) + 1);
	strcpy(*szMsg, szMsgTemp);
}

void CreateSMIMEEntity(FILEINFO *pFileInfo,
				  ENTITYINFO *pBodyInfo,
				  char **szSMIMEEntity,
				  bool bDropHeaders)
{
	VSSCMessage *pSmpMsg = VSSCMessage :: NewMessage("",0);
	SimpleMessage smMsg(pSmpMsg);

	VSSCMessage *pMultiMsg = VSSCMessage :: NewMessage("", 0);
	MultipartMessage mpMsg(pMultiMsg);
	VSSCString vsscEntityStr;
	
	mpMsg.SetTypeStr("Multipart");
	mpMsg.SetSubTypeStr("mixed");
	//mpMsg.CreateBoundary();
	//mpMsg.SetBoundary("--boundary");
	mpMsg.SetDefaultFields();
	BodyPart part;


	if(pFileInfo)
	{
		
		
		// Add the body to be displayed as the first bodypart

		if(pBodyInfo->szType && strlen(pBodyInfo->szType) > 1)
		{
			part.SetTypeStr(pBodyInfo->szType);
		}
		
		if(pBodyInfo->szSubType && strlen(pBodyInfo->szSubType) > 1)
		{
			part.SetSubTypeStr(pBodyInfo->szSubType);
		}
		
		if(pBodyInfo->szCte && strlen(pBodyInfo->szCte) > 1)
		{
			part.SetCteStr(pBodyInfo->szCte);
		}

		if(pBodyInfo->szCharset && strlen(pBodyInfo->szCharset) > 1)
		{
			part.SetCharset(pBodyInfo->szCharset);
		}
		
		if(pBodyInfo->szBody)
		{
			part.SetBody(pBodyInfo->szBody);
		}

		mpMsg.AddBodyPart(part);

		FILEINFO *pFileInfoTemp = pFileInfo;
		
		while(pFileInfoTemp)
		{


			if(pFileInfoTemp->szType && strlen(pFileInfoTemp->szType) > 1)
			{
				part.SetTypeStr(pFileInfoTemp->szType);
			}
			
			if(pFileInfoTemp->szSubType && strlen(pFileInfoTemp->szSubType) > 1)
			{
				part.SetSubTypeStr(pFileInfoTemp->szSubType);
			}
			
			if(pFileInfoTemp->szCte && strlen(pFileInfoTemp->szCte) > 1)
			{
				part.SetCteStr(pFileInfoTemp->szCte);
			}

			if(pFileInfoTemp->szCharset && strlen(pFileInfoTemp->szCharset) > 1)
			{
				part.SetCharset(pFileInfoTemp->szCharset);
			}

			//filepartheaders.GetContentDisposition().SetDispTypeString("attachment");
			part.SetContentDispType("attachment");

			if(pFileInfoTemp->szFileName && strlen(pFileInfoTemp->szFileName) > 0)
			{
				part.SetDispFileName(pFileInfoTemp->szFileName);
			}
			
			char *szFileCont = NULL;
			if(pFileInfoTemp->szFileName != NULL)
			{
				if(pFileInfoTemp->pbFileData && pFileInfoTemp->cbFileSize)
				{
					szFileCont = (char *)malloc(pFileInfoTemp->cbFileSize + 1);
					memcpy(szFileCont, pFileInfoTemp->pbFileData, pFileInfoTemp->cbFileSize);
					szFileCont[pFileInfoTemp->cbFileSize] = '\0';
					part.SetBody(szFileCont);
					if(szFileCont)
						free(szFileCont);
				}
				else
				{
					part.SetBody("");
				}
			}
			
			mpMsg.AddBodyPart(part);

			pFileInfoTemp = pFileInfoTemp->next;

			// Need to prepare a bodyparts get the string and then and to a bodypart, parse it and
			// then add this bodypart to the main message. 

		}
		
		mpMsg.Assemble();
		vsscEntityStr = mpMsg.GetString();
		
	}
	else // No attachments create a simple entity for the body as the first bodypart
	{
		if(bDropHeaders == _FALSE)
		{
			if(pBodyInfo->szType && strlen(pBodyInfo->szType) > 1)
			{
				smMsg.SetTypeStr(pBodyInfo->szType);
			}
			
			if(pBodyInfo->szSubType && strlen(pBodyInfo->szSubType) > 1)
			{
				smMsg.SetSubTypeStr(pBodyInfo->szSubType);
			}
			
			if(pBodyInfo->szCte && strlen(pBodyInfo->szCte) > 1)
			{
				smMsg.SetCteStr(pBodyInfo->szCte);
			}

			if(pBodyInfo->szCharset && strlen(pBodyInfo->szCharset) > 1)
			{
				smMsg.SetCharset(pBodyInfo->szCharset);
			}
			
		}
		if(pBodyInfo->szBody)
		{
			smMsg.SetBody(pBodyInfo->szBody);
		}
		
		smMsg.Assemble();
		vsscEntityStr = smMsg.GetString();
		
	}
	
	char *szEntity = vsscEntityStr.GetString();
	*szSMIMEEntity = (char *)malloc(strlen(szEntity) + 1);
	strcpy(*szSMIMEEntity, szEntity);


	return;
}






bool ParseMessage(char *szMessage, 
					MSGINFO *MsgInfo)
{
	VSSCMessage *msg = VSSCMessage :: NewMessage(szMessage, 0);
	msg->Parse();
	memset(MsgInfo, 0, sizeof(MSGINFO) );
	
	int nType = eUnknown;

	//// Determine the type of the message.
	/// BUGBUG - the type of the message should be determined by looking into PKCS7 blob
	// The best possible way is to get the type of the message from the server.
	///////////////////////////////
	
	VSSCString vsscHeaders = msg->GetHeaders().GetString();
	char* szHeaders = vsscHeaders.GetString();

	if(strlen(szHeaders) == 0)
	{
		//bantu....
		//nType = eBantu;

	}

	int nTypeTmp = msg->GetHeaders().GetContentType().GetType();
	int nSubTypeTmp =  msg->GetHeaders().GetContentType().GetSubType();
	VSSCString vsscSubtype = msg->GetHeaders().GetContentType().GetSubTypeString();
	int nRet = eUnknown;
	VSSCString vsscStr;

	if(nTypeTmp == VSSCEnumMime :: eTypeMultipart && nSubTypeTmp == VSSCEnumMime :: eSubtypeSigned)
	{
		nType = eClearSigned;
		
	}
	else if(nTypeTmp == VSSCEnumMime :: eTypeApplication && 
		(VSSCStrcasecmp(vsscSubtype, "pkcs7-mime") == 0 ||
			VSSCStrcasecmp(vsscSubtype, "x-pkcs7-mime") == 0 ))
	{
		vsscStr = msg->GetHeaders().GetContentType().GetSMIMEType();
		if(VSSCStrcasecmp(vsscStr, "enveloped-data") == 0)
		{
			nType = eEncrypted;
		}
		else if(VSSCStrcasecmp(vsscStr, "signed-data") == 0)
		{
			nType = eOpaqueSigned;
		}
	}
	else
	{
		nType = eUnknown;
	}
	
	///////////////////////


	if(nType == eEncrypted)
	{
		MsgInfo->eMimeType = VSSC_ENVELOPED;
	}	
	else if(nType == eClearSigned)
	{
		MsgInfo->eMimeType = VSSC_SIGNED;
	}
	else if(nType == eOpaqueSigned)
	{
		MsgInfo->eMimeType = VSSC_OPAQUE;
	}
	else
	{
		MsgInfo->eMimeType = VSSC_OTHER;
	}

	if(nType == eEncrypted)
	{
		if(!ParseEncMessage(msg, MsgInfo))
		{
			return false;
		}
	}
	else if(nType == eClearSigned)
	{
		if(!ParseSignedMessage(msg, MsgInfo))
		{
			return false;
		}
	}
	else if(nType == eOpaqueSigned)
	{
		if(!ParseOpaqueSignedMessage(msg, MsgInfo))
		{
			return false;
		}
	}

	return true;
}


bool ParseEncMessage(VSSCMessage *msg,
					   MSGINFO *MsgInfo)
{

	// Get the Message headers as a string
	VSSCHeaders headers = msg->GetHeaders();
	VSSCString vsscHeaders = headers.GetString();

	char *szHeaders = vsscHeaders.GetString();
	MsgInfo->szMsgHeadersStrRep = (char *)malloc(strlen(szHeaders) + 1);
	if(!MsgInfo->szMsgHeadersStrRep)
	{
		return false;
	}
	strcpy(MsgInfo->szMsgHeadersStrRep, szHeaders);
	

	SimpleMessage EncMsg(msg);

	// Fill the MsgInfo structure
	
	// From
	VSSCString vsscFrom = EncMsg.GetFrom();
	strcpy(MsgInfo->szFrom, vsscFrom.GetString());

	// To
	VSSCString vsscTo = EncMsg.GetTo();
	char *szTo = vsscTo.GetString();

	if(szTo != NULL && strlen(szTo) > 0)
	{
		MsgInfo->szTo = (char *)malloc(strlen(szTo) + 1);
		strcpy(MsgInfo->szTo, szTo);
	}

	// Cc
	VSSCString vsscCc = EncMsg.GetCc();
	char *szCc = vsscCc.GetString();

	if(szCc != NULL && strlen(szCc) > 0)
	{
		MsgInfo->szCC = (char *)malloc(strlen(szCc) + 1);
		strcpy(MsgInfo->szCC, szCc);
	}


	// Bcc
	VSSCString vsscBcc = EncMsg.GetBcc();
	char *szBcc = vsscBcc.GetString();

	if(szBcc != NULL && strlen(szBcc) > 0)
	{
		MsgInfo->szBCC = (char *)malloc(strlen(szBcc) + 1);
		strcpy(MsgInfo->szBCC, szBcc);
	}


	// Date
	VSSCString vsscDate = EncMsg.GetDate();
	char *szDate = vsscDate.GetString();

	if(szDate != NULL && strlen(szDate) > 0)
	{
		strcpy(MsgInfo->szDate, szDate);
	}

	// Subject
	VSSCString vsscSubject = EncMsg.GetSubject();
	char *szSubject = vsscSubject.GetString();

	if(szSubject != NULL && strlen(szSubject) > 0)
	{
		strcpy(MsgInfo->szSubject, szSubject);
	}

	// Type
	VSSCString vsscType = EncMsg.GetTypeStr();
	char *szType = vsscType.GetString();

	if(szType != NULL && strlen(szType) > 0)
	{
		strcpy(MsgInfo->szType, szType);
	}


	// SubType

	VSSCString vsscSubType = EncMsg.GetSubTypeStr();
	char *szSubType = vsscSubType.GetString();

	if(szSubType != NULL && strlen(szSubType) > 0)
	{
		strcpy(MsgInfo->szSubType, szSubType);
	}


	// Mime Entity 
	// This is available only in case clear signed message


	// PKCS7 which is nothing but the body of this message
	VSSCString vsscBody = EncMsg.GetBody();
	char *szBody = vsscBody.GetString();

	if(szBody != NULL && strlen(szBody) > 0)
	{
		MsgInfo->szPKCS7 = (char*)malloc(strlen(szBody) + 1);
		strcpy(MsgInfo->szPKCS7, szBody);
	}
	return true;
}


bool ParseOpaqueSignedMessage(VSSCMessage *msg,
							  MSGINFO *MsgInfo)
{
	// Get the Message headers as a string
	VSSCHeaders headers = msg->GetHeaders();
	VSSCString vsscHeaders = headers.GetString();

	char *szHeaders = vsscHeaders.GetString();
	MsgInfo->szMsgHeadersStrRep = (char *)malloc(strlen(szHeaders) + 1);
	if(!MsgInfo->szMsgHeadersStrRep)
	{
		return false;
	}
	strcpy(MsgInfo->szMsgHeadersStrRep, szHeaders);
	

	SimpleMessage OpqMsg(msg);

	// Fill the MsgInfo structure
	
	// From
	VSSCString vsscFrom = OpqMsg.GetFrom();
	strcpy(MsgInfo->szFrom, vsscFrom.GetString());

	// To
	VSSCString vsscTo = OpqMsg.GetTo();
	char *szTo = vsscTo.GetString();

	if(szTo != NULL && strlen(szTo) > 0)
	{
		MsgInfo->szTo = (char *)malloc(strlen(szTo) + 1);
		strcpy(MsgInfo->szTo, szTo);
	}

	// Cc
	VSSCString vsscCc = OpqMsg.GetCc();
	char *szCc = vsscCc.GetString();

	if(szCc != NULL && strlen(szCc) > 0)
	{
		MsgInfo->szCC = (char *)malloc(strlen(szCc) + 1);
		strcpy(MsgInfo->szCC, szCc);
	}


	// Bcc
	VSSCString vsscBcc = OpqMsg.GetBcc();
	char *szBcc = vsscBcc.GetString();

	if(szBcc != NULL && strlen(szBcc) > 0)
	{
		MsgInfo->szBCC = (char *)malloc(strlen(szBcc) + 1);
		strcpy(MsgInfo->szBCC, szBcc);
	}


	// Date
	VSSCString vsscDate = OpqMsg.GetDate();
	char *szDate = vsscDate.GetString();

	if(szDate != NULL && strlen(szDate) > 0)
	{
		strcpy(MsgInfo->szDate, szDate);
	}

	// Subject
	VSSCString vsscSubject = OpqMsg.GetSubject();
	char *szSubject = vsscSubject.GetString();

	if(szSubject != NULL && strlen(szSubject) > 0)
	{
		strcpy(MsgInfo->szSubject, szSubject);
	}

	// Type
	VSSCString vsscType = OpqMsg.GetTypeStr();
	char *szType = vsscType.GetString();

	if(szType != NULL && strlen(szType) > 0)
	{
		strcpy(MsgInfo->szType, szType);
	}


	// SubType

	VSSCString vsscSubType = OpqMsg.GetSubTypeStr();
	char *szSubType = vsscSubType.GetString();

	if(szSubType != NULL && strlen(szSubType) > 0)
	{
		strcpy(MsgInfo->szSubType, szSubType);
	}


	// Mime Entity 
	// This is available only in case clear signed message


	// PKCS7 which is nothing but the body of this message
	VSSCString vsscBody = OpqMsg.GetBody();
	char *szBody = vsscBody.GetString();

	if(szBody != NULL && strlen(szBody) > 0)
	{
		MsgInfo->szPKCS7 = (char*)malloc(strlen(szBody) + 1);
		strcpy(MsgInfo->szPKCS7, szBody);
	}
	return true;

}


bool ParseSignedMessage(VSSCMessage *msg,
					   MSGINFO *MsgInfo)
{
	
	

	// Get the Message headers as a string
	VSSCHeaders headers = msg->GetHeaders();
	VSSCString vsscHeaders = headers.GetString();
	char *szHeaders = vsscHeaders.GetString();

	MsgInfo->szMsgHeadersStrRep = (char *)malloc(strlen(szHeaders) + 1);
	if(!MsgInfo->szMsgHeadersStrRep)
	{
		return false;
	}
	strcpy(MsgInfo->szMsgHeadersStrRep, szHeaders);
	

	MultipartMessage SignedMsg(msg);

	// Fill the RFC822 headers.
		// From
	VSSCString vsscFrom = SignedMsg.GetFrom();
	strcpy(MsgInfo->szFrom, vsscFrom.GetString());

	// To
	VSSCString vsscTo = SignedMsg.GetTo();
	char *szTo = vsscTo.GetString();

	if(szTo != NULL && strlen(szTo) > 0)
	{
		MsgInfo->szTo = (char *)malloc(strlen(szTo) + 1);
		strcpy(MsgInfo->szTo, szTo);
	}

	// Cc
	VSSCString vsscCc = SignedMsg.GetCc();
	char *szCc = vsscCc.GetString();

	if(szCc != NULL && strlen(szCc) > 0)
	{
		MsgInfo->szCC = (char *)malloc(strlen(szCc) + 1);
		strcpy(MsgInfo->szCC, szCc);
	}


	// Bcc
	VSSCString vsscBcc = SignedMsg.GetBcc();
	char *szBcc = vsscBcc.GetString();

	if(szBcc != NULL && strlen(szBcc) > 0)
	{
		MsgInfo->szBCC = (char *)malloc(strlen(szBcc) + 1);
		strcpy(MsgInfo->szBCC, szBcc);
	}


	// Date
	VSSCString vsscDate = SignedMsg.GetDate();
	char *szDate = vsscDate.GetString();

	if(szDate != NULL && strlen(szDate) > 0)
	{
		strcpy(MsgInfo->szDate, szDate);
	}

	// Subject
	VSSCString vsscSubject = SignedMsg.GetSubject();
	char *szSubject = vsscSubject.GetString();

	if(szSubject != NULL && strlen(szSubject) > 0)
	{
		strcpy(MsgInfo->szSubject, szSubject);
	}

	// Type
	VSSCString vsscType = SignedMsg.GetTypeStr();
	char *szType = vsscType.GetString();

	if(szType != NULL && strlen(szType) > 0)
	{
		strcpy(MsgInfo->szType, szType);
	}


	// SubType

	VSSCString vsscSubType = SignedMsg.GetSubTypeStr();
	char *szSubType = vsscSubType.GetString();

	if(szSubType != NULL && strlen(szSubType) > 0)
	{
		strcpy(MsgInfo->szSubType, szSubType);
	}

	int nBodyPart = SignedMsg.GetNumofBodyParts();

	// Signed message should have 2 body parts always.
	if(nBodyPart != 2)
	{
		return false;
	}

	// From the 1st body part we fill the szMimeEntity
	BodyPart FirstPart;
	SignedMsg.GetBodyPart(0, FirstPart);

	// Note we need entity here
	VSSCString vsscEntity = FirstPart.GetEntityStr();
	char *szEntity = vsscEntity.GetString();
	MsgInfo->szMimeEntity = (char*)malloc(strlen(szEntity) + 1);
	strcpy(MsgInfo->szMimeEntity, szEntity);

	// From the 2nd body part we fill the szPKCS7
	BodyPart SecondPart;
	SignedMsg.GetBodyPart(1, SecondPart);

	// Note we need the body here
	VSSCString vsscPKCS7 = SecondPart.GetBody();
	char *szPKCS7 = vsscPKCS7.GetString();
	MsgInfo->szPKCS7 = (char *)malloc(strlen(szPKCS7) + 1);
	strcpy(MsgInfo->szPKCS7, szPKCS7);

	return true;
}



bool ParseMimeEntity(unsigned char* pbMimeEntity,
					 unsigned int cbMimeEntity,
					 ENTITYINFO *pBodyInfo,
					 FILEINFO **pFileInfo)
{

		
	FILEINFO *START, *pPrev, *pCurrent;
	START = pCurrent = pPrev = NULL ;
	*pFileInfo = NULL;

	char *szEntity = (char *)malloc(cbMimeEntity + 1);

	if(szEntity == NULL)
	{
		return false;
	}
	memcpy(szEntity, pbMimeEntity, cbMimeEntity);
	szEntity[cbMimeEntity] = '\0';
	
	VSSCBodyPart *msgEntity = VSSCBodyPart :: NewBodyPart(szEntity, 0);
	msgEntity->Parse();

	VSSCString vsscBodyTBD;
	char *szBodyTBD = NULL;
	if(msgEntity->GetHeaders().GetContentType().GetType() == VSSCEnumMime :: eTypeMultipart)
	{
		// Note: The body entity will always will be present if no body is entered 
		// in the message. This body entity will have NULL szBody.
		
		//VSSCMessage *msgInside = VSSCMessage :: NewMessage(szEntity, 0);
		VSSCBodyPart *msgInside = VSSCBodyPart :: NewBodyPart(szEntity, 0);
		msgInside->Parse();
		MultipartMessage MultipartInsideMsg(msgInside);

		// If bodypart is greater than 1 then we might have attachments.
		int nBdParts = MultipartInsideMsg.GetNumofBodyParts();

		// Find out if the first body part is multipart/alternative 
		BodyPart PartInside;
		MultipartInsideMsg.GetBodyPart(0, PartInside);


		if(VSSCStrcasecmp(PartInside.GetTypeStr(), "multipart") == 0 &&
			VSSCStrcasecmp(PartInside.GetSubTypeStr(), "alternative") == 0)
		{

	
			
			VSSCString vsscInsideEntity = PartInside.GetEntityStr();
			//VSSCMessage *msgInside = VSSCMessage :: NewMessage(vsscInsideEntity, 0);
			VSSCBodyPart *msgInside = VSSCBodyPart :: NewBodyPart(vsscInsideEntity, 0);
			msgInside->Parse();
			MultipartMessage MultipartInsideMsg(msgInside);

			
			int nBdParts = MultipartInsideMsg.GetNumofBodyParts();

			// Get the first body part which is usually text/plain
			// Right now we will return the first assuming it is text/plain always
			// Later will we add logic to determine the type and also may be
			// the list of content types available. 
			BodyPart PartInside;
			MultipartInsideMsg.GetBodyPart(0, PartInside);
			VSSCString vsscType = PartInside.GetTypeStr();
			VSSCString vsscSubType = PartInside.GetSubTypeStr();
			VSSCString vsscCharSet = PartInside.GetCharset();
			VSSCString vsscCte = PartInside.GetCteStr();

			strcpy(pBodyInfo->szType, vsscType.GetString());
			strcpy(pBodyInfo->szSubType, vsscSubType.GetString());
			strcpy(pBodyInfo->szCharset, vsscCharSet.GetString());
			strcpy(pBodyInfo->szCte, vsscCte.GetString());

			vsscBodyTBD = PartInside.GetBody();
			szBodyTBD = vsscBodyTBD.GetString();


		}
		else // The body of this body part is the body to be displayed.
		{
			VSSCString vsscType = PartInside.GetTypeStr();
			VSSCString vsscSubType = PartInside.GetSubTypeStr();

			vsscBodyTBD = PartInside.GetBody();
			szBodyTBD = vsscBodyTBD.GetString();

			
		}

		// Get the attachments.
		if(nBdParts > 1)
		{
			BodyPart PartAttach;
			for(int i = 1; i < nBdParts; i++)
			{
				
				MultipartInsideMsg.GetBodyPart(i, PartAttach);

				VSSCString vsscDispType = PartAttach.GetContentDispType();
				char *szDispType = vsscDispType.GetString();

				// Look for attachments if DispType = attachment
				// Assumption is that if there are attachments then there is 
				// Content-Dispostion with attachment as fieldbody.
				// Right now we are not considering the "inline" type.
				if(VSSCStrcasecmp(vsscDispType, "attachment") == 0)
				{

					// File Name
					VSSCString vsscDispFile = PartAttach.GetDispFileName();
					char *szDispFile = vsscDispFile.GetString();

					// File Content
					VSSCString vsscFileCont = PartAttach.GetBody();
					char *szFileCont = vsscFileCont.GetString();

					// Transfer encoding
					VSSCString vsscCte = PartAttach.GetCteStr();
					char *szCte = vsscCte.GetString();

					// Type
					VSSCString vsscType = PartAttach.GetTypeStr();
					char *szType = vsscType.GetString();

					// SubType
					VSSCString vsscSubType = PartAttach.GetSubTypeStr();
					char *szSubType = vsscSubType.GetString();

					// Charset
					VSSCString vsscCharset = PartAttach.GetCharset();
					char *szCharset = vsscCharset.GetString();

					
					pCurrent = (FILEINFO*)malloc(sizeof(FILEINFO));
					memset(pCurrent, 0, sizeof(FILEINFO));
					if(pPrev != 0)
					{
						pPrev->next = pCurrent;
					}

					pCurrent->next = NULL;
					pPrev = pCurrent;
					

					if(START == NULL)
					{
						START = pCurrent;
					}

					if(szCte != NULL && strlen(szCte) > 0)
					{
						strcpy(pCurrent->szCte, szCte);
					}

					if(szDispFile != NULL && strlen(szDispFile) > 0)
					{
						strcpy(pCurrent->szFileName, szDispFile);
					}


					if(szFileCont != NULL && strlen(szFileCont) > 0)
					{
						pCurrent->cbFileSize = strlen(szFileCont);

						// This check is for Zero Attachment Size
						// The minimum size after parse will be 2 for \r\n
						if(pCurrent->cbFileSize == 2)
						{
							if(szFileCont[0] == '\r' && szFileCont[1] == '\n')
							{
								pCurrent->cbFileSize = 0;
								pCurrent->pbFileData = NULL;
							}
							
						}
						else
						{
							pCurrent->pbFileData = (unsigned char*)malloc(strlen(szFileCont));
							memcpy(pCurrent->pbFileData, szFileCont, strlen(szFileCont));
						}
					}

					if(szType !=NULL && strlen(szType) > 0)
					{
						strcpy(pCurrent->szType, szType);
					}

					if(szSubType !=NULL && strlen(szSubType) > 0)
					{
						strcpy(pCurrent->szSubType, szSubType);
					}

					if(szCharset != NULL && strlen(szCharset) > 0)
					{
						strcpy(pCurrent->szCharset, szCharset);
					}
					
	
				}

			}

		}

		// Change
		if(msgEntity)
		{
			delete msgEntity;
		}
	}
	else
	{
		SimpleMessage Msg(msgEntity);

		VSSCString vsscType = Msg.GetTypeStr();
		VSSCString vsscSubType = Msg.GetSubTypeStr();
		VSSCString vsscCharSet = Msg.GetCharset();
		VSSCString vsscCte = Msg.GetCteStr();

		strcpy(pBodyInfo->szType, vsscType.GetString());
		strcpy(pBodyInfo->szSubType, vsscSubType.GetString());
		strcpy(pBodyInfo->szCharset, vsscCharSet.GetString());
		strcpy(pBodyInfo->szCte, vsscCte.GetString());

		vsscBodyTBD = Msg.GetBody();
		szBodyTBD = vsscBodyTBD.GetString();

	}

	pBodyInfo->szBody = (char *)malloc(strlen(szBodyTBD) + 1);
	strcpy(pBodyInfo->szBody, szBodyTBD);

	if(szEntity)
		free(szEntity);

	*pFileInfo = START;


	return true;
}

bool ParseHeaders(char *szHeaders,
				  MSGINFO *MsgInfo)
{
	// Could have used VSSCHeaders directly 
	VSSCMessage *msg = VSSCMessage :: NewMessage(szHeaders, 0);
	msg->Parse();

	SimpleMessage OpqMsg(msg);

	// Fill the MsgInfo structure
	
	// From
	VSSCString vsscFrom = OpqMsg.GetFrom();
	strcpy(MsgInfo->szFrom, vsscFrom.GetString());

	// To
	VSSCString vsscTo = OpqMsg.GetTo();
	char *szTo = vsscTo.GetString();

	if(szTo != NULL && strlen(szTo) > 0)
	{
		MsgInfo->szTo = (char *)malloc(strlen(szTo) + 1);
		strcpy(MsgInfo->szTo, szTo);
	}

	// Cc
	VSSCString vsscCc = OpqMsg.GetCc();
	char *szCc = vsscCc.GetString();

	if(szCc != NULL && strlen(szCc) > 0)
	{
		MsgInfo->szCC = (char *)malloc(strlen(szCc) + 1);
		strcpy(MsgInfo->szCC, szCc);
	}


	// Bcc
	VSSCString vsscBcc = OpqMsg.GetBcc();
	char *szBcc = vsscBcc.GetString();

	if(szBcc != NULL && strlen(szBcc) > 0)
	{
		MsgInfo->szBCC = (char *)malloc(strlen(szBcc) + 1);
		strcpy(MsgInfo->szBCC, szBcc);
	}


	// Date
	VSSCString vsscDate = OpqMsg.GetDate();
	char *szDate = vsscDate.GetString();

	if(szDate != NULL && strlen(szDate) > 0)
	{
		strcpy(MsgInfo->szDate, szDate);
	}

	// Subject
	VSSCString vsscSubject = OpqMsg.GetSubject();
	char *szSubject = vsscSubject.GetString();

	if(szSubject != NULL && strlen(szSubject) > 0)
	{
		strcpy(MsgInfo->szSubject, szSubject);
	}

	return true;
}


bool IsSignedEntity(unsigned char *pbMimeEntity,
			  unsigned int cbMimeEntity,
			  int* nRetType)
{
	char *szEntity = (char*)malloc(cbMimeEntity + 1);
	memcpy(szEntity, pbMimeEntity, cbMimeEntity);
	szEntity[cbMimeEntity] = '\0';

	VSSCBodyPart *BodyPart = VSSCBodyPart :: NewBodyPart(szEntity, 0);
	BodyPart->Parse();

	SimpleMessage smMsg(BodyPart);

	int nType = smMsg.GetMsgType();

	*nRetType = nType;

	if(nType == eOpaqueSigned)
	{
		return true;
	}
	else if(nType == eClearSigned)
	{
		return true;
	}
	else
	{
		return false;
	}

}

int _GetMsgType(unsigned char *pbMimeEntity,
			  unsigned int cbMimeEntity)
{
	char *szEntity = (char*)malloc(cbMimeEntity + 1);
	memcpy(szEntity, pbMimeEntity, cbMimeEntity);
	szEntity[cbMimeEntity] = '\0';

	VSSCBodyPart *BodyPart = VSSCBodyPart :: NewBodyPart(szEntity, 0);
	BodyPart->Parse();

	if(szEntity)
	{
		free(szEntity);
	}

	VSSCString vsscHeaders = BodyPart->GetHeaders().GetString();
	char *szString = vsscHeaders.GetString();
	if(!szString || strlen(szString) == 0)
	{
		return eNoHeaders;
	}

	SimpleMessage smMsg(BodyPart);

	int nType = smMsg.GetMsgType();

	

	return nType;
	
}


void WriteToFile(char *szFinalMsg)
{
	FILE *stream;

	stream = fopen("test.eml", "w+");

	if(stream == NULL)
	{
		printf("File open failed \n");
		return  ;
	}

	

	//int len = fprintf(stream,"%s", szFinalstr);
	char *szTempMessage = NULL;
	szTempMessage = szFinalMsg;

	while(*szFinalMsg)
	{
		if(*szFinalMsg != '\r')
			fwrite(szFinalMsg, sizeof(char), 1, stream);
		szFinalMsg++;
	}

	//fprintf(stream,"%s%s", szHeader, szMIMEEntity);
	fclose(stream);
	 

}


void FormatRFC822Date(
					  char *szRFC822Date
					  )
{
	struct tm tmLocalTime;
	time_t tCurrentTime;

	time(&tCurrentTime);
	tmLocalTime = *localtime(&tCurrentTime);

	struct _timeb tstruct;
	_ftime( &tstruct );

	//Wed, 6 Dec 2000 10:28:55
	char szDate[128];

	strftime (szDate, 128,"%a, %d %b %Y %H:%M:%S", 
           localtime ((const time_t *) &tCurrentTime));

	char szUTC[10];
	char szHour[4];
	int timezoneSeconds = tstruct.timezone;
	int timezoneHour = timezoneSeconds/60; //  Ex (480/60 = 8)
	
	itoa(timezoneHour, szHour, 10);

	//-0800
	strcpy(szUTC, " -0");
	strcat(szUTC, szHour);
	strcat(szUTC, "00");

	
	//Wed, 6 Dec 2000 10:28:55 -0800
	strcat(szDate, szUTC);
	strcpy(szRFC822Date, szDate);
	

}

void freeMsgInfo(MSGINFO *pMsgInfo)
{
	if(!pMsgInfo)
	{
		return;
	}

	if(pMsgInfo->szTo)
	{
		free(pMsgInfo->szTo);
		pMsgInfo->szTo = NULL;
	}
	if(pMsgInfo->szCC)
	{
		free(pMsgInfo->szCC);
		pMsgInfo->szCC = NULL;
	}
	if(pMsgInfo->szBCC)
	{
		free(pMsgInfo->szBCC);
		pMsgInfo->szBCC = NULL;
	}
	if(pMsgInfo->szMimeEntity)
	{
		free(pMsgInfo->szMimeEntity);
		pMsgInfo->szMimeEntity = NULL;
	}
	if(pMsgInfo->szMsgHeadersStrRep)
	{
		free(pMsgInfo->szMsgHeadersStrRep);
		pMsgInfo->szMsgHeadersStrRep = NULL;
	}

	if(pMsgInfo->szPKCS7)
	{
		free(pMsgInfo->szPKCS7);
		pMsgInfo->szPKCS7 = NULL;
	}
}


void freeFileInfo(FILEINFO *pFileInfo)
{
	if(!pFileInfo)
	{
		return;
	}

	FILEINFO *pFileInfoCurrent = pFileInfo;
	FILEINFO *pFileInfoNext = NULL;

	while(pFileInfoCurrent)
	{
		pFileInfoNext = pFileInfoCurrent->next;

		if(pFileInfoCurrent->pbFileData)
		{
			free(pFileInfoCurrent->pbFileData);
		}

		free(pFileInfoCurrent);
		pFileInfoCurrent = pFileInfoNext;

	}

}


bool ParseOpaqueSignedMessageStr(char *szMessage,
							  MSGINFO *MsgInfo)
{
	VSSCMessage *msg = VSSCMessage :: NewMessage(szMessage, 0);
	msg->Parse();

	bool bRet = ParseOpaqueSignedMessage(msg, MsgInfo);
	
	return bRet;

	
}

bool ParseSignedMessageStr(char *szMessage,
					   MSGINFO *MsgInfo)
{
	
	VSSCMessage *msg = VSSCMessage :: NewMessage(szMessage, 0);
	msg->Parse();

	bool bRet = ParseSignedMessage(msg, MsgInfo);

	return bRet;
	
}
