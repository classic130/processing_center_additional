#ifndef _VSMIMELIB
#define _VSMIMELIB

#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <string.h>
#include <stdio.h>

#include "vsscstring.h"
#include "vsscmessage.h"
#include "vsscbody.h"
#include "simplemsg.h"
#include "vsscbody.h"
#include "vsscbodypart.h"
#include "multipartmsg.h"
#include "vsscenum.h"


enum SMIMETYPE{VSSC_SIGNED,VSSC_ENVELOPED,VSSC_OPAQUE, VSSC_OTHER};

typedef struct _MSGINFO
{
	char szFrom[256];
	char *szTo;
	char *szCC;
	char *szBCC;
	char szDate[50];
	char szSubject[256];
	char szType[256];
	char szSubType[256];
	char *szMsgHeadersStrRep;
	char *szMimeEntity;
	char *szPKCS7;
	SMIMETYPE eMimeType;
} MSGINFO;

typedef struct _FILEINFO
{
	char szFileName[256];
	char szType[256];
	char szSubType[256];
	char szCharset[256];
	char szCte[256];
	unsigned int cbFileSize;
	unsigned char *pbFileData;
	_FILEINFO *next;
}FILEINFO;

typedef struct _ENTITYINFO
{
	char szType[256];
	char szSubType[256];
	char szCharset[256];
	char szCte[256];
	char *szBody;
}ENTITYINFO;


void CreateSMIMEEntity(FILEINFO *pFileInfo,
				  ENTITYINFO *pBodyInfo,
				  char **szSMIMEEntity,bool bDropHeaders);

// This function to be moved to VSSC and commented out from here

void WriteToFile(char *szFinalMsg);
void CreateClearSignedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  );

// This function to be moved to VSSC and commented out from here
void CreateOpaqueSignedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  );

// This function to be moved to VSSC and commented out from here
void CreateEncryptedMessage(MSGINFO *pMsgInfo,
						  FILEINFO *pFileInfo,
						  ENTITYINFO *pBodyInfo,
						  char **szMsg
						  );


bool ParseMessage(char *szMessage, 
					MSGINFO *MsgInfo);
		
bool ParseEncMessage(VSSCMessage *msg,
					   MSGINFO *MsgInfo);

bool ParseSignedMessage(VSSCMessage *msg,
					   MSGINFO *pMsgInfo);

bool ParseOpaqueSignedMessage(VSSCMessage *msg,
							  MSGINFO *pMsgInfo);

bool ParseSignedMessageStr(char *szMessage,
					   MSGINFO *MsgInfo);

bool ParseOpaqueSignedMessageStr(char *szMessage,
							  MSGINFO *MsgInfo);

// EnityInfo contains the info related to type,subtype,cte and charset of the body
// which is to be displayed.
bool ParseMimeEntity(unsigned char* pbMimeEntity,
					 unsigned int cbMimeEntity,
					 ENTITYINFO *pBodyInfo,
					 FILEINFO **pFileInfo);

bool ParseHeaders(char *szHeaders,
				  MSGINFO *pMsgInfo);


// This is used in case of encrypted and signed message.
bool IsSignedEntity(unsigned char *pbMimeEntity,
			  unsigned int cbMimeEntity,
			  int* nRetType);



int _GetMsgType(unsigned char *pbMimeEntity,
			  unsigned int cbMimeEntity);

void FormatRFC822Date(
					  char *szRFC822Date
					  );

void freeMsgInfo(MSGINFO *pMsgInfo);

void freeFileInfo(FILEINFO *pFileInfo);

#endif // _VSMIMELIB