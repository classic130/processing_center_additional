#include "vsprs.h"


VSPRSAttachment * CProxyRecipients::VSPRS_GetAttachmentObj()
{

	PCHAR clearText = NULL;
	FILEINFO *FileInfo = NULL;

	if (mAttachment == NULL) {
		ParseMimeEntity((PBYTE)(const char *)mMsgInfo.Body, 
						mMsgInfo.Body.Length(),
				&clearText, &FileInfo);

		mAttachment = new VSPRSAttachment(FileInfo);
	}

	return mAttachment;
}


const char * CProxyRecipients::VSPRS_GetClearTextFromMIME(PBYTE mimeEntity)
{

	//GetClearText(MsgInfo.szMimeEntity, &pVSmMsgInfo->szBody);
	PCHAR clearText = NULL;
	FILEINFO *FileInfo;
	ParseMimeEntity((PBYTE)mimeEntity, strlen((PCHAR)mimeEntity),
				&clearText, &FileInfo);

	mClearText = (const char *)clearText;
	if (clearText != NULL) free (clearText);

	return (const char *)mClearText;
	
}


const char * CProxyRecipients::VSPRS_GetBody()
{
	// mMsgInfo.Body really has the Mime Body.
	// A MIME Body means that it has Content-Type,
	// Content-Encoding, Content-Dispo, etc.
	// All that is mising is the email-related headers.

	return (VSPRS_GetClearTextFromMIME((unsigned char *)(const char *)mMsgInfo.Body));
}

// Private method.
VSString * CProxyRecipients::GetContent(const char *type, const char *body)
{

	int len = 0;
	// We need to parse the MimeBody to get the content-type.

    VSString str1 = VSString(body).FindString(type);
	if (str1.Length() == 0) return new VSString("");

	VSString str2 = str1;
	VSString str3, str4;
	const char *ptr = NULL;

	
	for (;;) {
			// take a substring.
			str3 = str2.FindString(CRLF);
			if (str3.Length()  == 0) break;
			
			str4 += str2.Left(str2.Length() - str3.Length());
			ptr = str3.GetBuffer();
			if (ptr[2] != '\t') break;
			str2 = ptr +=3; // skips \r\n\t
			str4 += "\n";
	}
	
	
	return new VSString(str4);

	
}

const char * CProxyRecipients::VSPRS_GetBodyContent(VSPRS_BodyType bType)
{

	VSString BCtype;

	switch (bType) {
		case BD_CONTENT_TYPE:			
				BCtype = CONTENT_TYPE; break;
		case BD_CONTENT_XSFER_ENCODING:	
				BCtype = CONTENT_ENCODING; break;
		case BD_CONTENT_DISP:	
				BCtype = CONTENT_DISPOSITION; break;
	}
	FindBody(mMsgInfo.Body, mMsgInfo.BodyContainer);
	return *GetContent(BCtype, mMsgInfo.BodyContainer);
}



void CProxyRecipients::FindBody(VSString &inStr, VSString &outStr)
{

	VSString body, str1, str2;

	if (!mMsgInfo.foundBody) {
		body = inStr;
		// now, get the entire string. By using Right()
		// we have to see if this is a multipart mime.
		VSString  *str3 = GetContent(CONTENT_TYPE, body);
		// Take a substring.
		
		VSString boundary("--");
		char *ptr = NULL;
		if (str3->FindString("Multipart")) {	
			// get the boundary name.
			str1 = str3->FindString("boundary");
			int doubleQ1 = str1.Find('"');
			ptr = str1.GetBuffer();
			ptr += (doubleQ1+1); // skips = and '"'
			str2 = ptr;
			int doubleQ2 = str2.Find('"');
			boundary += str2.Left(doubleQ2);
	
			// assume 1st boundary contains the Body.
			// if Content-Disposition does not say "attachment"
			// we could have an empty Body.
			str1 = body.FindString(boundary);
			// now get to the end of boundary.
			if (str1.Length() != 0) {
				str2 = VSString(str1.FindString(CRLF)).FindString(boundary);
				body = str1.Left(str1.Length() - str2.Length());
				// now find conten-disposition to see if this is attachment.
				str1 = body.FindString(CONTENT_DISPOSITION);
				if (str1.Length() != 0) {
					str2 = str1.FindString(CRLF);
					*str3 = str1.Left(str1.Length() - str2.Length());
					if (str3->FindString("attachment") != NULL)
						//we have an empty body.
						body = "";
				}
				
			}
		} // end if MultiPart
		outStr =body;
		mMsgInfo.foundBody = TRUE;
		delete str3;
	} // end if foundBody
	
	
	return;
}