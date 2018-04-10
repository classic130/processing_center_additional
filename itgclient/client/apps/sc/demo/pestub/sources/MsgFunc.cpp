//////////////////Message Store/////////////////
#include "vssc_global.h"

#define DEFAULT_PORT		  25
#define DEFAULT_PROTO		  SOCK_STREAM   // TCP

#define VS_COMMA              ","

extern PESTUBINFO    g_pInfo;





unsigned long StoreMsgAndSend(VSAA_NAME anInput[],VSAA_NAME **panOutput)
{
	char *szMsgID = NULL;
	char *szTo=NULL,*pMessage=NULL;
	

	VSAA_NAME *pOutput=NULL;

	int   size=0;

	PestubInit();

	size=strlen(anInput[3].pszValue)+1;
	szTo=(char *)malloc(size);

	strcpy(szTo,anInput[3].pszValue);


    size=strlen(anInput[5].pszValue)+1;
	pMessage=(char*)malloc(size);

	strcpy(pMessage,anInput[5].pszValue);
	pMessage[size]='\0';



	SendBySMTP(g_pInfo.szSMTPServerName,anInput[2].pszValue,anInput[3].pszValue,anInput[4].pszValue,
		anInput[5].pszValue);

	CreateMessageContainer(&szMsgID);
	//2-From,3-To,4-Cc,5-Message,6-Msgtype
	
	
	StoreMessage(szMsgID, pMessage , anInput[6].pszValue, anInput[2].pszValue);


			///////build the output list
	pOutput = (VSAA_NAME *)calloc(2, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}

	/////First element//////////////////
	pOutput[0].pszName = strdup("Recipients");
	if (pOutput[0].pszName == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	pOutput[0].pszValue = strdup(szTo);
	if (pOutput[0].pszValue == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	///////2th element/////////////////
	pOutput[1].pszName=NULL;
	pOutput[1].pszValue=NULL;



	/*
	if(szTo!=NULL)
			free(szTo);

	if(pMessage!=NULL)
			free(pMessage);

   */

	*(panOutput)=pOutput;

	return 0;

}


HRESULT GetInBoxSummary(VSAA_NAME anInput[],VSAA_NAME **pOutList)
{

	int NumMsg=0;
	char  *MsgID[]={"MSGID1","MSGID2","MSGID3","MSGID4","MSGID5","MSGID6","MSGID7","MSGID8","MSGID9","MSGID10"};
	char  *szSender[]={"SENDER1","SENDER2","SENDER3","SENDER4","SENDER5","SENDER6","SENDER7","SENDER8","SENDER9","SENDER10"};
	char  *szDate[]={"DATE1","DATE2","DATE3","DATE4","DATE5","DATE6","DATE7","DATE8","DATE9","DATE10"};
	char  *szSubject[]={"SUBJECT1","SUBJECT2","SUBJECT3","SUBJECT4","SUBJECT5","SUBJECT6","SUBJECT7","SUBJECT8","SUBJECT9","SUBJECT10"};
	char  *szMsgType[]={"MSGTYPE1","MSGTYPE2","MSGTYPE3","MSGTYPE4","MSGTYPE5","MSGTYPE6","MSGTYPE7","MSGTYPE8","MSGTYPE9","MSGTYPE10"};

	char buffer[256];
	VSAA_NAME *pOutput;

	int iRet=0;

	SCMSGInfo *SCInfo;


	NumMsg=GetNumMessages();
	if(NumMsg==0)
				return -1;

	iRet=GetSCMsgInfo(NumMsg,&SCInfo);
	if(iRet==-1)
				return -1;


	pOutput = (VSAA_NAME *)calloc(NumMsg*5+1, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}

    int j=0;
	for(int i=0;i<NumMsg*5;i=i+5)
	{
		
		///1
		pOutput[i].pszName = strdup(MsgID[j]);
		if (pOutput[i].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}
	

		pOutput[i].pszValue = strdup(SCInfo->szMsgID);
		if (pOutput[i].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}
		////2
		
		pOutput[i+1].pszName = strdup(szSender[j]);
		if (pOutput[i+1].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}
	
		/////strip <>from sender 
		/*
		int k = 0;
		while(SCInfo->szSender[k])
		{
			if(SCInfo->szSender[k] == '>' || SCInfo->szSender[k] == '<')
				SCInfo->szSender[k] = ' ';
			k++;
		}
		*/

	    strcpy(buffer,SCInfo->szFrom);
	

		pOutput[i+1].pszValue = strdup(buffer);
		if (pOutput[i+1].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}


		///////////3

		pOutput[i+2].pszName = strdup(szDate[j]);
		if (pOutput[i+2].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}
	

		pOutput[i+2].pszValue = strdup(SCInfo->szDate);
		if (pOutput[i+2].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}

		/////////4

		pOutput[i+3].pszName = strdup(szSubject[j]);
		if (pOutput[i+3].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}
	

		pOutput[i+3].pszValue = strdup(SCInfo->szSubject);
		if (pOutput[i+3].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}

		////////5

		pOutput[i+4].pszName = strdup(szMsgType[j]);
		if (pOutput[i+4].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}
	

		pOutput[i+4].pszValue = strdup(SCInfo->szMsgType);
		if (pOutput[i+4].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}

		SCInfo=SCInfo->next;
		j++;
	}

	///////nth element make it Null/////////////////
	pOutput[i].pszName=NULL;
	pOutput[i].pszValue=NULL;


	*(pOutList)=pOutput;
	
return 0;		
}

HRESULT GetMsg(VSAA_NAME anInput[],VSAA_NAME **pOutList)
{
	VSAA_NAME *pOutput;

	char   szMsgID[256];
	MESSAGE_INFO MsgInfo;

	char *  lpToken=NULL;
	char *  szMessage=NULL;
//	char *  szSubject;
//	char    szFrom[256],szTo[256],szDate[256];
//	char    szSMIME[8024];

	int     Ret=0;

	strcpy(szMsgID,anInput[2].pszValue);

	memset(&MsgInfo, 0, sizeof(MESSAGE_INFO));
	Ret=GetMessageFromStore(szMsgID, &MsgInfo);
	if(Ret==-1)
	{
		return -1;
	}

	szMessage=(char *)malloc(strlen(MsgInfo.szMessage)*3+1);
	if(szMessage==NULL)
	{
		return -1;
	}

	URLEncode(MsgInfo.szMessage,szMessage);
	pOutput = (VSAA_NAME *)calloc(3, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}
	/////Msg
	pOutput[0].pszName = strdup("MSG");
	if (pOutput[0].pszName == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	pOutput[0].pszValue = strdup(szMessage);
	if (pOutput[0].pszValue == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	///////MsgType
	pOutput[1].pszName = strdup("MSGTYPE");
	if (pOutput[1].pszName == NULL)
	{
		Release(&pOutput);
		return -1;
	}

	pOutput[1].pszValue = strdup(MsgInfo.szMsgType);
	if (pOutput[1].pszValue == NULL)
	{
		Release(&pOutput);
		return -1;
	}


	pOutput[2].pszName=NULL;
	pOutput[2].pszValue=NULL;
	
	*(pOutList)=pOutput;

	
	if(szMessage!=NULL)
		free(szMessage);


	return 0;
}

/*
HRESULT GetInBoxSummary(VSAA_NAME anInput[],VSAA_NAME **pOutList)
{

	const int NUMMSG=2;
	char  *MsgHeader[]={"MSG1","MSG2","MSG3","MSG4","MSG5"};

	char  szMsg[8024];

	VSAA_NAME *pOutput;

	SCMSGInfo *SCInfo;
	GetSCMsgInfo(NUMMSG,&SCInfo);


	pOutput = (VSAA_NAME *)calloc(NUMMSG+1, sizeof(VSAA_NAME));
	if (pOutput == NULL)
	{
		return -1;
	}


	for(int i=0;i<NUMMSG;i++)
	{
		ZeroMemory(szMsg,8024);
		
		strcat(szMsg,SCInfo->szMsgID);
		strcat(szMsg,VS_COMMA);

		strcat(szMsg,SCInfo->szSender);
		strcat(szMsg,VS_COMMA);

		strcat(szMsg,SCInfo->szDate);
		strcat(szMsg,VS_COMMA);

		strcat(szMsg,SCInfo->szSubject);
		strcat(szMsg,VS_COMMA);

		strcat(szMsg,SCInfo->szMsgType);
		
		
		pOutput[i].pszName = strdup(MsgHeader[i]);
		if (pOutput[i].pszName == NULL)
		{
			Release(&pOutput);
			return -1;
		}

		//pOutput[i].pszValue=(char *)calloc(1,strlen(szMsg)+1);
		//strcpy(pOutput[i].pszValue,szMsg);

		pOutput[i].pszValue = strdup(szMsg);
		if (pOutput[i].pszValue == NULL)
		{
			Release(&pOutput);
			return -1;
		}

		
		SCInfo=SCInfo->next;

	}

	///////nth element make it Null/////////////////
	pOutput[i].pszName=NULL;
	pOutput[i].pszValue=NULL;


	*(pOutList)=pOutput;





	
return 0;		
}
*/

HRESULT SendBySMTP(char *szServer,char *szFrom,char *szTo,char * szCc,char *pSMIMEMessage)
{
	HRESULT hr=S_OK;

	char Buffer[256];
	char *server_name= "localhost";
	unsigned short port = DEFAULT_PORT;
	int retval, loopflag=0,err=0;
	int loopcount,maxloop=-1;

	int socket_type = DEFAULT_PROTO;
	struct sockaddr_in server;
	struct hostent *hp;
	WSADATA wsaData;
	SOCKET  conn_socket;

	char    szTmpTo[1024];


	if (WSAStartup(0x101,&wsaData) == SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
	}
	//
	// Attempt to detect if we should call gethostbyname() or
	// gethostbyaddr()

	if (szServer!=NULL) {   /* server address is a name */
		hp = gethostbyname(szServer);
	}
	//else  { /* Convert nnn.nnn address to a usable one */
	
	//	addr = inet_addr(server_name);
	//	hp = gethostbyaddr((char *)&addr,4,AF_INET);
	//}

	if (hp == NULL ) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
	}

	//
	// Copy the resolved information into the sockaddr_in structure
	//
	memset(&server,0,sizeof(server));
	memcpy(&(server.sin_addr),hp->h_addr,hp->h_length);
	server.sin_family = hp->h_addrtype;
	server.sin_port = htons(port);

	conn_socket = socket(AF_INET,socket_type,0); /* Open a socket */
	if (conn_socket <0 ) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
	}

	if (connect(conn_socket,(struct sockaddr*)&server,sizeof(server))
		== SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
	}

	// cook up a string to send
	//
	char    local_host[80];
	loopcount =0;
	while(1) {
		gethostname( local_host, 80 );
		wsprintf(Buffer,"Hello to %s\r\n",local_host);
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}
		

		retval = recv(conn_socket,Buffer,sizeof (Buffer),0 );
		if (retval == SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
		}


		/////////////Mail From
		wsprintf(Buffer,"MAIL From: <%s>\r\n",szFrom);
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}
		

		retval = recv(conn_socket,Buffer,sizeof (Buffer),0 );
		if (retval == SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
		}

		////////////Mail To

		char * lpTo=NULL;

		strcpy(szTmpTo,szTo);

		lpTo=strtok(szTmpTo,",");
		while(lpTo!=NULL)
		{

			wsprintf(Buffer,"RCPT TO: <%s>\r\n" ,lpTo);
			retval = send(conn_socket,Buffer,sizeof(Buffer),0);
			if (retval == SOCKET_ERROR) {
				err=WSAGetLastError();
				WSACleanup();
				return  HRESULT_FROM_WIN32(err);
			}
		

			retval = recv(conn_socket,Buffer,sizeof (Buffer),0 );
			if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
			WSACleanup();
			return  HRESULT_FROM_WIN32(err);
			}

			lpTo=strtok(NULL,",");
		}

		/////////////////Data////////////////
		strcpy(Buffer,"DATA\r\n");
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}
		

		retval = recv(conn_socket,Buffer,sizeof (Buffer),0 );
		if (retval == SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
		}

		retval = send(conn_socket,pSMIMEMessage,strlen(pSMIMEMessage),0);
		if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}
		
		
		//////////End 
		strcpy(Buffer,"\r\n.\r\n");
		retval = send(conn_socket,Buffer,sizeof(Buffer),0);
		if (retval == SOCKET_ERROR) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}
		

		retval = recv(conn_socket,Buffer,sizeof (Buffer),0 );
		if (retval == SOCKET_ERROR) {
		err=WSAGetLastError();
		WSACleanup();
		return  HRESULT_FROM_WIN32(err);
		}


		if (retval == 0) {
			err=WSAGetLastError();
		    WSACleanup();
		    return  HRESULT_FROM_WIN32(err);
		}

		if (!loopflag){
				break;
		}
		else {
			if ( (loopcount >= maxloop) && (maxloop >0) )
				break;
		}
	}
	closesocket(conn_socket);
	WSACleanup();




return hr;
}


BOOL	URLEncode(PCHAR szInput, PCHAR szOutput)
{
	DWORD	dwInput = strlen(szInput) ;
	DWORD	i, j ;

	for ( j = 0, i = 0 ; i < dwInput ; i++ )
	{
		if ( szInput[i] == '\n' ||
			 szInput[i] == '\r' ||
			 szInput[i] == '\t' ||
			 szInput[i] == '\"' ||
			 szInput[i] == '\'' ||

			// szInput[i] == ' ' ||

			 szInput[i] == ',' ||
			 szInput[i] == ';' ||
			 szInput[i] == ':' ||
			 szInput[i] == '@' ||
			 szInput[i] == '.' ||
			 szInput[i] == '\\' ||
			 szInput[i] == '|' ||
			 szInput[i] == '<' ||
			 szInput[i] == '>' ||
			 szInput[i] == '{' ||
			 szInput[i] == '}' ||
			 szInput[i] == '(' ||
			 szInput[i] == ')' ||
			 szInput[i] == '[' ||
			 szInput[i] == ']' ||
			 szInput[i] == '-' ||
			 szInput[i] == '_' ||
			 szInput[i] == '=' ||
			 szInput[i] == '+' ||
			 szInput[i] == '/' ||
			 szInput[i] == '$' ||
			 szInput[i] == '#' ||
			 szInput[i] == '`' ||
			 szInput[i] == '~' ||
			 szInput[i] == '!' ||
			 szInput[i] == '*' )
		{
			CHAR	tmp[4] ;
			itoa((int)szInput[i], tmp, 16) ;

			szOutput[j] = '%' ;

			if( strlen(tmp) == 1 )
			{
				szOutput[j+1] = '0' ;
				szOutput[j+2] = tmp[0] ;
			}
			else
			{
				memcpy(szOutput+j+1, tmp, 2) ;
			} 

			j += 3 ;
		}
		else
		{
			if(szInput[i] == ' ')
			{
				szOutput[j]='+';
			}
			else
			{
				szOutput[j] = szInput[i] ;
			}
			j++ ;

		}
	}

	szOutput[j] = '\0' ;

	return TRUE ;
}

PCHAR	URLDecode(PCHAR input)
{
	PCHAR	szDecodedString = NULL ;
	DWORD	inputIndex = 0, outputIndex = 0 ;

	szDecodedString = (PCHAR) malloc(strlen(input)+1) ;
	

	while(input[inputIndex] != NULL )
	{
		if ( input[inputIndex] != '%' )
		{
			if(input[inputIndex]=='+')
			{
				szDecodedString[outputIndex++] = ' ';
				inputIndex++;
			}
			else
			{
				szDecodedString[outputIndex++] = input[inputIndex++] ;
			}
			
		}
		else
		{

			inputIndex++ ;
			CHAR	szTmp[4], tmpChar ;
			szTmp[0] = input[inputIndex++] ;
			szTmp[1] = input[inputIndex++] ;
			szTmp[2] = '\0' ;
			sscanf(szTmp, "%x", &tmpChar) ;
			szDecodedString[outputIndex++] = tmpChar ;
		}
	}
	szDecodedString[outputIndex] = '\0' ;

/*
	if ( input )
		free (input) ;
*/
	return(szDecodedString) ;
}