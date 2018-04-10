// vsprs.h: interface for the CProxyRecipient class
//
//////////////////////////////////////////////////////////////////////
///////////VSPRS.h/////////////////
#ifndef VSPRSATTACHMENTS_H
#define VSPRSATTACHMENTS_H

#include <stdio.h>
#include <string.h>
#include <windows.h>

#include "vsstring.h"
#include "sgmscommon.h"
//#include "charutils.h"
#include "vsmimelib.h"



class VSPRSAttachment 
{
public:

	VSPRSAttachment(FILEINFO *info = NULL) { mbase64Attachments = FALSE; mHead = info; mCurrent = mHead;}
	virtual ~VSPRSAttachment() {}; // shoud call the FILEINFO destroy here.
								// wait for Ajaj.

	char * VSPRSAT_GetName() { return mCurrent->szFileName; }
	unsigned char * VSPRSAT_GetData() { return mCurrent->pbFileData; }
	int	VSPRSAT_GetSize() { return mCurrent->cbFileSize; }

	bool VSPRSAT_IsAttachmentBase64()	{ return mbase64Attachments; }
	
	void VSPRSAT_Next() { if (mCurrent != NULL) mCurrent = mCurrent->next; } 
	bool VSPRSAT_HasElements() { return ((mCurrent == NULL) ? (FALSE ): (TRUE)); }
	void VSPRSAT_Rewind() { mCurrent = mHead; }

	void VSPRSAT_Base64Attachments();

	


private:

	bool mbase64Attachments;

	FILEINFO *mHead;
	FILEINFO *mCurrent;
};

#endif