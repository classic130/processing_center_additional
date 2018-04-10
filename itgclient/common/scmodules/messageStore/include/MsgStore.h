#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>


// change this to increase or decrease the messages stored in the store
// The msg store is designed to hold only finite number of messages.

#define NO_OF_MESSAGES	10

#define MAT_OFFSET	sizeof(MSG_ALLOC_TABLE)*NO_OF_MESSAGES

#define INIT_TABLE	"00000000"

#define MSGID_SIZE	6
#define MSGTYPE_SIZE 1

#define MSG_FIELD_SIZE 8

typedef struct _MSG_ALLOC_TABLE{
	char szMsgNo[MSG_FIELD_SIZE + 1];
	char szMsgOffset[MSG_FIELD_SIZE + 1];
	char szMsgSize[MSG_FIELD_SIZE + 1];
}MSG_ALLOC_TABLE;

typedef struct _MESSAGE_INFO	
{
	char szMsgID[MSGID_SIZE + 1];  // randomly generated.
	char szMsgType[MSGTYPE_SIZE + 1]; // type assuming its not greater than 9
	char szMsgSCName[256]; //  email address
	char *szMessage;
}MESSAGE_INFO;

typedef struct _MESSAGE_STORE_HEADER
{
	char szMsgID[MSGID_SIZE + 1];  // randomly generated.
	char szMsgType[MSGTYPE_SIZE + 1]; // type assuming its not greater than 9
	char szMsgSCName[256]; //  email address
}MESSAGE_STORE_HEADER;

typedef struct _SCMSGInfo
{
	char szMsgID[MSGID_SIZE + 1];
	char szFrom[256];
	char szDate[50];
	char szSubject[256];
	char szMsgType[2];
	_SCMSGInfo *next;
}SCMSGInfo;


enum MSG_TYPE { SCM_SIMPLE=1, SCM_SIGNED=2, SCM_ENCRYPTED=3, SCM_SIGNENCRYPT=4};




/////////Creates a Message Container and returns the MessageID
int CreateMessageContainer(char **szMessageID
						   );

//////////Stores the Message Given a MessageID
int StoreMessage(char *szMessageID,
				 char *szMessage,
				 char *szMessageType,
				 char *szSCName);

/////////Returns the MsgInfo given a MessageID
int GetMessageFromStore(char *szMessageID,
			   MESSAGE_INFO *pMsgInfo);

///////Not Implemented
int DeleteMessage(char *szMessageID);


// This function returns a link list of InBox info structures
// nMessages = retrive nMessages from the message store
int GetSCMsgInfo(int nMessages,
				 SCMSGInfo **SCInfo);

int GetNumMessages();



//////Utility functions.

void getRandomString(char *pbData,
					 int len);

void SetLength(char *szLen,
			   unsigned int len);

//if szInput = "From:ajayaram@verisign.com"
// szOutVal = "ajayaram@verisign.com"
void GetValFromStr(char *szInput,
				   char **szOutVal);