#ifndef _VSSC_MSGSTORE_H_
#define _VSSC_MSGSTORE_H_

#include "pestub.h"

typedef struct
{
	char    szSMTPServerName[256];
	int     UserSMIMECert;
	int     RevocationType;
	int     RevocationStatus;
	int     ChainValidateType;
	int     ChainValidateStatus;

	
}PESTUBINFO;



unsigned long StoreMsgAndSend(VSAA_NAME anInput[],VSAA_NAME **panOutput);
HRESULT GetInBoxSummary(VSAA_NAME anInput[],VSAA_NAME **panOutput );
HRESULT GetMsg(VSAA_NAME anInput[],VSAA_NAME **pOutList);

HRESULT SendBySMTP(char *szServer,char *szFrom,char *szTo,char * szCc,char *pSMIMEMessage);
BOOL	URLEncode(PCHAR szInput, PCHAR szOutput);
PCHAR	URLDecode(PCHAR input);


#endif