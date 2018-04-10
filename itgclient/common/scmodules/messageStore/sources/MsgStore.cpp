#include "MsgStore.h"

int CreateMessageContainer(
						   char **szMessageID
						   )
{

	FILE *fMsgStore = NULL;

	fMsgStore = fopen("Msg.Store", "a+");

	if(fMsgStore == NULL)
	{
		printf("File open failed\n");
		return -1;
	}
	fclose(fMsgStore);


	// Binary mode is very important to handle CRLF in the message.
	fMsgStore = fopen("Msg.Store", "rb+"); 

	if(fMsgStore == NULL)
	{
		printf("File open failed\n");
		return -1;
	}

	int nFileSize = 0;

	fseek(fMsgStore, 0, SEEK_END) ;

	nFileSize = ftell(fMsgStore);

	MESSAGE_INFO msgHeader;

	memset(&msgHeader, 0, sizeof(MESSAGE_INFO));
	rewind(fMsgStore);

	char szMsgID[MSGID_SIZE + 1];

	getRandomString(szMsgID, MSGID_SIZE);


	// New file
	if(nFileSize == 0)
	{
		int nInitialize = 0;

		MSG_ALLOC_TABLE msgAllocInit;

		// Initialize the MAT
		strcpy(msgAllocInit.szMsgNo, INIT_TABLE);
		strcpy(msgAllocInit.szMsgOffset, INIT_TABLE);
		strcpy(msgAllocInit.szMsgSize, INIT_TABLE);

				
		for(int i = 0; i < NO_OF_MESSAGES; i++)
		{
			fprintf(fMsgStore, "%s %s %s ", msgAllocInit.szMsgNo, msgAllocInit.szMsgOffset,
				msgAllocInit.szMsgSize);
		}

		//nFileSize = ftell(fMsgStore);
		
		
		strcpy(msgHeader.szMsgID, szMsgID);
		fprintf(fMsgStore,"%s %s", msgHeader.szMsgID, "1"); // Intially the message type is set to SIMPLE

		//nFileSize = ftell(fMsgStore);

		fseek(fMsgStore, 0, SEEK_SET);
		//int temp1 = ftell(fMsgStore);
		int nOffset = MAT_OFFSET;

		SetLength(msgAllocInit.szMsgOffset, nOffset);
		
		msgAllocInit.szMsgNo[7] = '1';

		// Message Size

		SetLength(msgAllocInit.szMsgSize, MSGID_SIZE + MSGTYPE_SIZE + 1); // 1 for space


		fprintf(fMsgStore, "%s %s %s ", msgAllocInit.szMsgNo, msgAllocInit.szMsgOffset,
				msgAllocInit.szMsgSize);
		//nFileSize = ftell(fMsgStore);

		fclose(fMsgStore);		
			
		*szMessageID = (char *)malloc(strlen(msgHeader.szMsgID) + 1);

		strcpy(*szMessageID, msgHeader.szMsgID);
		
	
	}

	else
	{

		MSG_ALLOC_TABLE *msgAlloc, *msgAllocStart;

		msgAlloc = msgAllocStart = NULL;

		msgAlloc = (MSG_ALLOC_TABLE*)malloc(sizeof(MSG_ALLOC_TABLE) * NO_OF_MESSAGES);

		msgAllocStart = msgAlloc;

		for(int i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
		{
			fscanf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
				msgAlloc->szMsgSize);
		}

		msgAlloc = msgAllocStart;
		int nMsgNo = 0;
		for(i =0; i < NO_OF_MESSAGES; i++, msgAlloc++ )
		{
			
			nMsgNo = atoi(msgAlloc->szMsgNo);
			if(nMsgNo == 0)
				break;
		}

		if(i == NO_OF_MESSAGES)
		{
			printf("\nMessage Store overflow\n");
			return -1;
		}
		msgAlloc--;

		int nMsgOffset = atoi(msgAlloc->szMsgOffset);
		int nMsgSize = atoi(msgAlloc->szMsgSize);

		// go to the beginning of the file
		fseek(fMsgStore, 0, SEEK_SET);

		int nTotal = nMsgOffset + nMsgSize  ; 

		fseek(fMsgStore, nTotal, SEEK_CUR );
		//fseek(fMsgStore, 0, SEEK_END);
		//fseek(fMsgStore, 1, SEEK_CUR);

		//nFileSize = ftell(fMsgStore);

		// Assumption - there will be no duplication of messageID - in other words
		// duplication of messageid is not accounted for.

		// BUGBUG change this to use the randomly generate string.
		strcpy(msgHeader.szMsgID, szMsgID);

		fprintf(fMsgStore,"%s %s", msgHeader.szMsgID, "1"); //Intially the message type is set to SIMPLE

		//nFileSize = ftell(fMsgStore);

		msgAlloc++;

		// Message #
		SetLength(msgAlloc->szMsgNo, i+1);
				
		// Message Size.
		SetLength(msgAlloc->szMsgSize, MSGID_SIZE + MSGTYPE_SIZE + 1); // 1 for space

		// Message Offset
		SetLength(msgAlloc->szMsgOffset, nTotal );


		msgAlloc = msgAllocStart;

		fseek(fMsgStore, 0, SEEK_SET);

		//nFileSize = ftell(fMsgStore);

		for(i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
		{
			fprintf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
				msgAlloc->szMsgSize);
		}

		fclose(fMsgStore);		
			
		*szMessageID = (char *)malloc(strlen(msgHeader.szMsgID) + 1);

		strcpy(*szMessageID, msgHeader.szMsgID);
		

	}


	return 0;
}




int StoreMessage(char *szMessageID,
				 char *szMessage,
				 char *szMessageType,
				 char *szSCName)
{

	FILE *fMsgStore = NULL;
	MSG_ALLOC_TABLE *MsgAllocTb = NULL;

	//int nTell;

	// Binary mode is very important to handle CRLF in the message.
	fMsgStore = fopen("Msg.Store", "rb+");
	if(fMsgStore == NULL)
	{
		printf("\nFailed to open the Message Store\n");
		return -1;
	}

	// Read the Msg Allocation Table

	MSG_ALLOC_TABLE *msgAlloc, *msgAllocStart;

	msgAlloc = msgAllocStart = NULL;

	msgAlloc = (MSG_ALLOC_TABLE*)malloc(sizeof(MSG_ALLOC_TABLE) * NO_OF_MESSAGES);

	msgAllocStart = msgAlloc;

	for(int i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
	{
		fscanf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
			msgAlloc->szMsgSize);
	}

	msgAlloc = msgAllocStart;

	unsigned int nMsgNo = 0;
	unsigned int nMsgOffset = 0;
	unsigned int nMsgSize = 0;
	char szSearchID[7];
	char szType[2];

//	int nTell;
	// Search for the MessageID and store the message.
	for(i =0; i < NO_OF_MESSAGES; i++, msgAlloc++ )
	{
		
		nMsgNo = atoi(msgAlloc->szMsgNo);
		if(nMsgNo == 0)
			break;
		nMsgOffset = atoi(msgAlloc->szMsgOffset);
		nMsgSize = atoi(msgAlloc->szMsgSize);

		fseek(fMsgStore, nMsgOffset, SEEK_SET);

		//nTell = ftell(fMsgStore);
		fscanf(fMsgStore, "%s %s", szSearchID, szType );
		
		int ntemptell = ftell(fMsgStore); // needed for the below function.

		// Go back and overwrite the MessageType with the value passed in
		// I'm overwriting the SearchID as it is easier to move around the File pointer

		fseek(fMsgStore, -(long)(ntemptell-nMsgOffset), SEEK_CUR);

		//nTell = ftell(fMsgStore);

		if(strcmp(szSearchID, szMessageID) == NULL)
		{
			fprintf(fMsgStore, "%s %s", szSearchID, szMessageType );
		}
		else
		{
			fprintf(fMsgStore, "%s %s", szSearchID, szType );
		}


		//nTell = ftell(fMsgStore);

		
		fseek(fMsgStore, 0, SEEK_END);
		
		//nTell = ftell(fMsgStore);

		if(strcmp(szSearchID, szMessageID) == NULL)
		{
			
			fprintf(fMsgStore, " %s %s ", szSCName, szMessage);

			/*
			char szSpace[] = " ";
			fwrite(szSpace, strlen(szSpace), 1, fMsgStore);
			fwrite(szSCName, strlen(szSCName), 1, fMsgStore);
			fwrite(szSpace, strlen(szSpace), 1, fMsgStore);
			fwrite(szMessage, strlen(szMessage), 1, fMsgStore);
			fwrite(szSpace, strlen(szSpace), 1, fMsgStore);
			*/
			

			//nTell = ftell(fMsgStore);

			//nMsgSize = nTell - (nMsgSize + nMsgOffset) + nMsgSize;

			// calculate the new offset and size
			nMsgSize = nMsgSize + strlen(szSCName) + strlen(szMessage) + 3; // 3 spaces.
			SetLength(msgAlloc->szMsgSize, nMsgSize);

			break;
		}

	}

	if(i == NO_OF_MESSAGES)
	{
		printf("\nMessageID not found\n");
		fclose(fMsgStore);
		return -1;
	}

	// commit the MAT

	msgAlloc = msgAllocStart;

	fseek(fMsgStore, 0, SEEK_SET);

	for(i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
	{
		fprintf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
			msgAlloc->szMsgSize);
	}
	//nTell = ftell(fMsgStore);

	fclose(fMsgStore);


	return 0;


}


int GetMessageFromStore(char *szMessageID,
			   MESSAGE_INFO *pMsgInfo)
{
	char szGetMsg[100000] ;

	FILE *fMsgStore = NULL;
	MSG_ALLOC_TABLE *MsgAllocTb = NULL;


	// Binary mode is very important to handle CRLF in the message.
	fMsgStore = fopen("Msg.Store", "rb");
	if(fMsgStore == NULL)
	{
		printf("\nFailed to open the Message Store\n");
		return -1;
	}

	// Read the Msg Allocation Table

	MSG_ALLOC_TABLE *msgAlloc, *msgAllocStart;

	msgAlloc = msgAllocStart = NULL;

	msgAlloc = (MSG_ALLOC_TABLE*)malloc(sizeof(MSG_ALLOC_TABLE) * NO_OF_MESSAGES);

	msgAllocStart = msgAlloc;

	for(int i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
	{
		fscanf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
			msgAlloc->szMsgSize);
	}

	msgAlloc = msgAllocStart;

	unsigned int nMsgNo = 0;
	unsigned int nMsgOffset = 0;
	unsigned int nMsgSize = 0;
	char szSearchID[7];
	char szType[2];
//	int nTell;

		
	// Search for the MessageID and Get the Message.
	for(i =0; i < NO_OF_MESSAGES; i++, msgAlloc++ )
	{
		
		nMsgNo = atoi(msgAlloc->szMsgNo);
		if(nMsgNo == 0)
		{
			printf("Message not found\n");
			fclose(fMsgStore);
			return -1;
		}
		nMsgOffset = atoi(msgAlloc->szMsgOffset);
		nMsgSize = atoi(msgAlloc->szMsgSize);

		fseek(fMsgStore, nMsgOffset, SEEK_SET);

		//nTell = ftell(fMsgStore);
		fscanf(fMsgStore, "%s %s", szSearchID, szType );
		
		//fseek(fMsgStore, 0, SEEK_END);
		
		//nTell = ftell(fMsgStore);
		fseek(fMsgStore, 1, SEEK_CUR); //skip the space.
		//nTell = ftell(fMsgStore);

		if(strcmp(szSearchID, szMessageID) == NULL)
		{
			
			int nSize = MSGID_SIZE + MSGTYPE_SIZE + 1 ;
			int nActualSize = nMsgSize - nSize - 2; // the end space of the message is not needed

			//fscanf(fMsgStore, " %s %s ", szSCName, szGetMsg); // For consistency with write I'm also reading SCName
			fread(szGetMsg, (nActualSize), 1, fMsgStore);
			szGetMsg[nActualSize] = '\0';

			//nTell = ftell(fMsgStore);

			// remove the SCName from the message
			
			char szSCName[256];
			
			
			for(int i=0; szGetMsg[i]; i++)
			{
				if(szGetMsg[i] == ' ')
					break;
				szSCName[i] = szGetMsg[i];
			}
			szSCName[i] = '\0';
			i++;
			char *szMessageStart = &szGetMsg[i];

			pMsgInfo->szMessage = (char *) malloc(strlen(szMessageStart) + 1);

			
			
			// Fill the MESSAGEINFO structure.
			strcpy(pMsgInfo->szMessage,  szMessageStart);
			strcpy(pMsgInfo->szMsgType, szType);
			strcpy(pMsgInfo->szMsgID, szMessageID);
			strcpy(pMsgInfo->szMsgSCName, szSCName);


			break;
		}

	}

	if(i == NO_OF_MESSAGES)
	{
		printf("\nMessageID not found\n");
		fclose(fMsgStore);
		return -1;
	}

	return 0;


}

int GetSCMsgInfo(int nMessages,
				 SCMSGInfo **SCInfo)
{
	char szGetMsg[100000] ;

	FILE *fMsgStore = NULL;
	MSG_ALLOC_TABLE *MsgAllocTb = NULL;
	
	SCMSGInfo *START = NULL;
	SCMSGInfo *pSCMsgLinkList = NULL;
	SCMSGInfo *pPrevSCMsg = NULL;

	char szSeps[] = "\r\n";

	


	// Binary mode is very important to handle CRLF in the message.
	fMsgStore = fopen("Msg.Store", "rb");
	if(fMsgStore == NULL)
	{
		printf("\nFailed to open the Message Store\n");
		return -1;
	}

	// Read the Msg Allocation Table

	MSG_ALLOC_TABLE *msgAlloc, *msgAllocStart;

	msgAlloc = msgAllocStart = NULL;

	msgAlloc = (MSG_ALLOC_TABLE*)malloc(sizeof(MSG_ALLOC_TABLE) * NO_OF_MESSAGES);

	msgAllocStart = msgAlloc;

	for(int i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
	{
		fscanf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
			msgAlloc->szMsgSize);
	}

	msgAlloc = msgAllocStart;

	unsigned int nMsgNo = 0;
	unsigned int nMsgOffset = 0;
	unsigned int nMsgSize = 0;
	char szSearchID[7];
	char szType[2];
//	int nTell;

	int nNumMessages = GetNumMessages();
	if(nMessages > nNumMessages)
	{
		nMessages = nNumMessages;
	}
	// Search for the MessageID and Get the Message.
	for(i =0; i < NO_OF_MESSAGES && i < nMessages; i++, msgAlloc++ )
	{
		
		nMsgNo = atoi(msgAlloc->szMsgNo);
		if(nMsgNo == 0)
		{
			printf("No Messages found\n");
			fclose(fMsgStore);
			return -1;
		}
		nMsgOffset = atoi(msgAlloc->szMsgOffset);
		nMsgSize = atoi(msgAlloc->szMsgSize);

		fseek(fMsgStore, nMsgOffset, SEEK_SET);

		//nTell = ftell(fMsgStore);
		fscanf(fMsgStore, "%s %s", szSearchID, szType );
		
		//fseek(fMsgStore, 0, SEEK_END);
		
		//nTell = ftell(fMsgStore);
		fseek(fMsgStore, 1, SEEK_CUR); //skip the space.
		//nTell = ftell(fMsgStore);

	
		// Construct the link list
		
		pSCMsgLinkList = (SCMSGInfo*)calloc(1, sizeof(SCMSGInfo));
		if(i == 0)
		{
			START = pSCMsgLinkList;
			pPrevSCMsg = pSCMsgLinkList;
		}


		int nSize = MSGID_SIZE + MSGTYPE_SIZE + 1 ;
		int nActualSize = nMsgSize - nSize - 2; // the end space of the message is not needed

		//fscanf(fMsgStore, " %s %s ", szSCName, szGetMsg); // For consistency with write I'm also reading SCName
		fread(szGetMsg, (nActualSize), 1, fMsgStore);
		szGetMsg[nActualSize] = '\0';

		//nTell = ftell(fMsgStore);

		// remove the SCName from the message
		
		char szSCName[256];
		
		
		for(int j=0; szGetMsg[j]; j++)
		{
			if(szGetMsg[j] == ' ')
				break;
			szSCName[j] = szGetMsg[j];
		}
		szSCName[j] = '\0';
		j++;
		
		char *szMessageStart = &szGetMsg[j];

		// To not used
		char *szFrom, *szTo, *szDate, *szSubject;
		szFrom = szTo = szDate = szSubject = NULL;

		szFrom = strtok(szMessageStart, szSeps);
		szTo = strtok(NULL, szSeps);
		szDate = strtok(NULL, szSeps);
		szSubject = strtok(NULL, szSeps);

		char  *szFromVal, *szDateVal, *szSubVal;
		szFromVal = szDateVal = szSubVal = NULL;

		GetValFromStr(szFrom, &szFromVal);
		GetValFromStr(szDate, &szDateVal);
		GetValFromStr(szSubject, &szSubVal);

		// Strip down unneccessary stuff to display from the date.
		char *szDateShown;
		szDateShown = strstr(szDateVal, ",");
		szDateShown ++ ; // Skip ","
		szDateShown ++; // skip " "
		
		char szDateLast[20];
		int i = 0;
		int count = 0;
		while (szDateShown)
		{
			szDateLast[i] = *szDateShown;
			if(*szDateShown == ' ')
			{
				count ++; 
				
			}
			if( count == 3)
				break;
			
			szDateShown ++;
			i++;
		}
		szDateLast[i] = '\0';
	
		strcpy(pSCMsgLinkList->szMsgID, szSearchID);
		strcpy(pSCMsgLinkList->szMsgType, szType);
		strcpy(pSCMsgLinkList->szFrom, szFromVal);
		strcpy(pSCMsgLinkList->szDate, szDateLast);
		strcpy(pSCMsgLinkList->szSubject, szSubVal);

		if(szFromVal)
			free(szFromVal);
		if(szDateVal)
			free(szDateVal);
		if(szSubVal)
			free(szSubVal);

		if(i == 0)
		{
			pSCMsgLinkList->next = NULL;
		}
		else
		{
			pPrevSCMsg->next = pSCMsgLinkList;
			pPrevSCMsg = pSCMsgLinkList;
			pSCMsgLinkList->next = NULL;
		}

		

	}

	if(i == NO_OF_MESSAGES)
	{
		printf("\n Message store overflow\n");
		fclose(fMsgStore);
		return -1;
	}
	*SCInfo = START;

	return 0;

}


// Returns # of messages in Message Store.
int GetNumMessages()
{
	FILE *fMsgStore = NULL;
	MSG_ALLOC_TABLE *MsgAllocTb = NULL;


	// Binary mode is very important to handle CRLF in the message.
	fMsgStore = fopen("Msg.Store", "rb");
	if(fMsgStore == NULL)
	{
		printf("\nFailed to open the Message Store\n");
		return -1;
	}

	// Read the Msg Allocation Table

	MSG_ALLOC_TABLE *msgAlloc, *msgAllocStart;

	msgAlloc = msgAllocStart = NULL;

	msgAlloc = (MSG_ALLOC_TABLE*)malloc(sizeof(MSG_ALLOC_TABLE) * NO_OF_MESSAGES);

	msgAllocStart = msgAlloc;

	for(int i = 0; i < NO_OF_MESSAGES; i++, msgAlloc++)
	{
		fscanf(fMsgStore, "%s %s %s ", msgAlloc->szMsgNo, msgAlloc->szMsgOffset,
			msgAlloc->szMsgSize);
	}

	msgAlloc = msgAllocStart;

	unsigned int nMsgNo = 0;

	
	// Search for the MessageID and Get the Message.
	for(i =0; i < NO_OF_MESSAGES; i++, msgAlloc++ )
	{
		
		nMsgNo = atoi(msgAlloc->szMsgNo);
		if(nMsgNo == 0)
		{
			printf("Message not found\n");
			fclose(fMsgStore);
			break;
		}
	}
	if(fMsgStore)
		fclose(fMsgStore);
	return i;
}




// Converts the int to ASCII and writes to the char array appropriately.
// if len = 25 and szLen = "00000000" the result is "00000025"
void SetLength(char *szLen,
			   unsigned int len
			   )
{
	
	char szBuff[MSG_FIELD_SIZE + 1];
	unsigned int lenString = 0 ;
	unsigned int ConstLen = MSG_FIELD_SIZE - 1; 	 // strlen - 1 index into an array is always -1

	itoa(len, szBuff, 10);

	lenString = strlen(szBuff);


	for(; lenString > 0;lenString--,ConstLen--)
	{
		szLen[ConstLen] = szBuff[lenString - 1] ;
	}

}

void getRandomString(char *pbData,
					 int len)
{
	unsigned int dwRand;
	char szRand[256];
	int i = 0;
	int count = 0;
	srand( (unsigned)time( NULL ) );

	while(1)
	{
		dwRand = rand();
		itoa(dwRand,szRand,10);

		while(szRand[i])
		{
			if(count == len)
			{
				pbData[len] = '\0';
				return;
			}
			pbData[count] = szRand[i];
			i ++;
			count ++;

		}
		i = 0;
	}

}


//if szInput = "From:ajayaram@verisign.com"
// szOutVal = "ajayaram@verisign.com"
void GetValFromStr(char *szInput,
				   char **szOutVal)
{
	char *szTemp = NULL;
	szTemp = (char *)malloc(strlen(szInput) + 1);
	for( int i =0; szInput[i]; i++)
	{
		if(szInput[i] == ':')
			break;
	}
	i++;

	for(int j=0; szInput[i]; i++, j++)
	{
		szTemp[j] = szInput[i];
	}
	szTemp[j] = '\0';

	*szOutVal = (char *)malloc(strlen(szTemp) + 1);
	strcpy(*szOutVal, szTemp);

	if(szTemp)
		free(szTemp);

}

