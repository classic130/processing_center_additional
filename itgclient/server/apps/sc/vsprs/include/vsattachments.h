// vsprs.h: interface for the CProxyRecipient class
//
//////////////////////////////////////////////////////////////////////
///////////VSPRS.h/////////////////
#ifndef VSPRSATTACHMENTS_H
#define VSPRSATTACHMENTS_H

#include <stdio.h>
#include <string.h>

#include "vsstring.h"
#include "charutils.h"
#include "vssmime.h"
#include "pkcs7engine.h"


class VSPRSAttachment 
{
public:

	VSPRSAttachment(FILEINFO *info = NULL) { mHead = info; }
	virtual ~CProxyRecipients();

	char * VSPRSAT_GetName() { return mCurrent->szFileName; }
	unsigned char * VSPRSAT_GetData() { return mCurrent->pbFileData; }
	int	VSPRSAT_GetSize() { return mCurrent->cbFileSize; }

	bool VSPRSAT_IsAttachmentBase64()	{ return base64Attachments; }
	
	void VSPRSAT_Next() { if (mCurrent != NULL) mCurrent = mCurrent->next; } 
	bool VSPRSAT_HasElements() { return ((mCurrent == NULL) ? (false ): (true))); }
	void VSPRSAT_Rewind() { mCurrent = mHead; }

	void VSPRSAT_Base64Attachments();


private:

	bool base64Attachments;

	FILEINFO *mHead;
	FILEINFO *mCurrent;
};

#endif