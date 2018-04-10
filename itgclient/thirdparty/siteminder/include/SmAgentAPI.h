#ifndef _SmAgentApi_h_
#define _SmAgentApi_h_

/*
Copyright (C) 1997-2000, Netegrity, Inc. All rights reserved.

Netegrity, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

SiteMinder Agent API
*/

#include "SmApi.h"


/*
** API version
*/
#define SM_AGENTAPI_VERSION						0x0400	/* 0xMmNn; Mm = major version, Nn = minor version */


/*
** Function return codes
*/
#define SM_AGENTAPI_NOCONNECTION				-3
#define SM_AGENTAPI_TIMEOUT						-2
#define SM_AGENTAPI_FAILURE						-1
#define SM_AGENTAPI_SUCCESS						0
#define SM_AGENTAPI_YES							1
#define SM_AGENTAPI_NO							2
#define SM_AGENTAPI_CHALLENGE					3


/*
** Size definitions
*/
#define SM_AGENTAPI_SIZE_OID					64
#define SM_AGENTAPI_SIZE_URL					4096
#define SM_AGENTAPI_SIZE_NAME					256
#define SM_AGENTAPI_SIZE_USERNAME				256
#define SM_AGENTAPI_SIZE_USERPW					4096
#define SM_AGENTAPI_SIZE_CERTDN					1024
#define SM_AGENTAPI_SIZE_SESSIONSPEC			2048
#define SM_AGENTAPI_SIZE_SERVICEINFO			512


/*
** Attributes
*/

/* Well-known attributes returned as part of successful login */
#define SM_AGENTAPI_ATTR_AUTH_DIR_OID			151
#define SM_AGENTAPI_ATTR_AUTH_DIR_NAME			213
#define SM_AGENTAPI_ATTR_AUTH_DIR_SERVER		214
#define SM_AGENTAPI_ATTR_AUTH_DIR_NAMESPACE		215
#define SM_AGENTAPI_ATTR_USERMSG				216
#define SM_AGENTAPI_ATTR_USERDN					218
#define SM_AGENTAPI_ATTR_USERUNIVERSALID		152
#define SM_AGENTAPI_ATTR_IDENTITYSPEC			156


typedef struct Sm_AgentApi_Attribute_s
{
	long	nAttributeId;
	long	nAttributeTTL;
	long	nAttributeFlags;
	char	lpszAttributeOid[SM_AGENTAPI_SIZE_OID];
	long	nAttributeLen;
	char*	lpszAttributeValue;
} Sm_AgentApi_Attribute_t;


/* function prototypes */

#if defined(unix)
extern "C" {
#endif

/************************************************************************************************
**                                General Functions
************************************************************************************************/

/*
** Init the Agent API
**
** Return values:
**		SM_AGENTAPI_SUCCESS
**		SM_AGENTAPI_FAILURE
*/

/*
** server ports
*/
#define SM_AGENTAPI_AZ_SERVER					0		/* authorization server */
#define SM_AGENTAPI_AUTH_SERVER					1		/* authentication server */
#define SM_AGENTAPI_ACCT_SERVER					2		/* accounting server */

typedef struct Sm_AgentApi_Server_s
{
	char	lpszIpAddr[SM_AGENTAPI_SIZE_NAME];		/* server IP address */
	long	nConnMin;				/* number of initial connections */
	long	nConnMax;				/* number of max connections */
	long	nConnStep;				/* number of connections to allocate when out of connections */
	long	nTimeout;				/* connection timeout in seconds */
	long	nPort[3];				/* server ports, 0 = none */
	void*	pHandle[3];				/* reserved, must be NULL */
} Sm_AgentApi_Server_t;


typedef struct Sm_AgentApi_Init_s
{
	long	nVersion;				/* must be SM_AGENTAPI_VERSION */
	char	lpszHostName[SM_AGENTAPI_SIZE_NAME];		/* agent name as defined in SiteMinder (case sensitive!) */
	char	lpszSharedSecret[SM_AGENTAPI_SIZE_NAME];	/* agent shared secret as defined in SiteMinder (case sensitive!) */
	long	nFailover;				/* 1 = yes, 0 - no */
	long	nNumServers;			/* size of the server definition array */
	Sm_AgentApi_Server_t*	pServers;				/* array of server definition structures */
} Sm_AgentApi_Init_t;


int SM_EXTERN Sm_AgentApi_Init (
	const Sm_AgentApi_Init_t* pInitStruct,
	void** ppHandle);


/*
** Uninit the Agent API
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_SUCCESS
**		SM_AGENTAPI_FAILURE
*/

int SM_EXTERN Sm_AgentApi_UnInit (
	void** ppHandle);


/*
** Is resource protected?
**
**
** *** Note: lpszAgent must be zero initialized ***
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
*/

typedef struct Sm_AgentApi_ResourceContext_s
{
	char	lpszAgent[SM_AGENTAPI_SIZE_NAME];
	char	lpszServer[SM_AGENTAPI_SIZE_NAME];
	char	lpszAction[SM_AGENTAPI_SIZE_NAME];
	char	lpszResource[SM_AGENTAPI_SIZE_URL];
} Sm_AgentApi_ResourceContext_t;


typedef struct Sm_AgentApi_Realm_s
{
	char	lpszDomainOid[SM_AGENTAPI_SIZE_OID];
	char	lpszRealmOid[SM_AGENTAPI_SIZE_OID];
	char	lpszRealmName[SM_AGENTAPI_SIZE_NAME];
	long	nRealmCredentials;
	char	lpszFormLocation[SM_AGENTAPI_SIZE_URL];
} Sm_AgentApi_Realm_t;


int SM_EXTERN Sm_AgentApi_IsProtected (
	const void* pHandle,
	const char* lpszClientIpAddr,
	const Sm_AgentApi_ResourceContext_t* pResourceContext,
	Sm_AgentApi_Realm_t* pRealm);


/*
** Get management commands
**
** NOTE: lpszData must be zero-initialized prior to use
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
*/

/* get pending agent commands; no data required */
#define SM_AGENTAPI_MANAGEMENT_GET_AGENT_COMMANDS	1

/* report agent-specific info; data = agent info */
#define SM_AGENTAPI_MANAGEMENT_SET_AGENT_INFO		3

/* agent commands returned as attributes */
#define SM_AGENTAPI_AFFILIATE_KEY_UPDATE		189   /* attribute data = name of affiliate agent */
#define SM_AGENTAPI_AGENT_KEY_UPDATE_NEXT		190   /* attribute data = binary 24 bytes */
#define SM_AGENTAPI_AGENT_KEY_UPDATE_LAST		191   /* attribute data = binary 24 bytes */
#define SM_AGENTAPI_AGENT_KEY_UPDATE_CURRENT	192   /* attribute data = binary 24 bytes */
#define SM_AGENTAPI_AGENT_KEY_UPDATE_PERSISTENT	193   /* attribute data = binary 24 bytes */
#define SM_AGENTAPI_CACHE_FLUSH_ALL				194   /* no data */
#define SM_AGENTAPI_CACHE_FLUSH_ALL_USERS		195   /* no data */
#define SM_AGENTAPI_CACHE_FLUSH_THIS_USER		196   /* attribute data = DirectoryOid + "/" + UserDN */
#define SM_AGENTAPI_CACHE_FLUSH_ALL_REALMS		197   /* no data */
#define SM_AGENTAPI_CACHE_FLUSH_THIS_REALM		198   /* attribute data = Realm OID */


typedef struct Sm_AgentApi_ManagementContext_s
{
	long	nCommand;
	char	lpszData[SM_AGENTAPI_SIZE_NAME];
} Sm_AgentApi_ManagementContext_t;


int SM_EXTERN Sm_AgentApi_DoManagement (
	const void* pHandle,
	Sm_AgentApi_ManagementContext_t* pManagementContext,
	long* pNumAttributes,
	Sm_AgentApi_Attribute_t** ppAttributes);


/************************************************************************************************
**                                Session Management Functions
************************************************************************************************/

/*
** Session login or session validation
**
** Session login (session spec not specified). Policy server attempts to authenticate credentials.
**
**   If session id is specified, it will be used as the session id in case authentication succeeds;
**   Otherwise a new session id will be generated.
**
**
** Session relogin (session spec specified). Policy server attempts to validate session spec.
**
**   If session id is specified, it will be validated against session spec.
**   If ip address is specified, it will be validated against session spec.
**
** NOTE: Unused fields in the user credentials structure must be zero initialized.
**
** This function always returns the following attributes:
**
** SM_AGENTAPI_ATTR_AUTH_DIR_OID
** SM_AGENTAPI_ATTR_AUTH_DIR_NAME
** SM_AGENTAPI_ATTR_AUTH_DIR_SERVER
** SM_AGENTAPI_ATTR_AUTH_DIR_NAMESPACE
** SM_AGENTAPI_ATTR_USERMSG
** SM_AGENTAPI_ATTR_USERDN
** SM_AGENTAPI_ATTR_USERUNIVERSALID
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
**		SM_AGENTAPI_CHALLENGE
*/

typedef struct Sm_AgentApi_UserCredentials_s
{
	long	nChallengeReason;
	char	lpszUsername[SM_AGENTAPI_SIZE_USERNAME];
	char	lpszPassword[SM_AGENTAPI_SIZE_USERPW];
	char	lpszCertUserDN[SM_AGENTAPI_SIZE_CERTDN];
	char	lpszCertIssuerDN[SM_AGENTAPI_SIZE_CERTDN];
	long	nCertBinaryLen;
	char*	lpszCertBinary;
} Sm_AgentApi_UserCredentials_t;


typedef struct Sm_AgentApi_Session_s
{
	long	nReason;
	long	nIdleTimeout;
	long	nMaxTimeout;
	long	nCurrentServerTime;
	long	nSessionStartTime;
	long	nSessionLastTime;
	char	lpszSessionId[SM_AGENTAPI_SIZE_OID];
	char	lpszSessionSpec[SM_AGENTAPI_SIZE_SESSIONSPEC];
} Sm_AgentApi_Session_t;


int SM_EXTERN Sm_AgentApi_Login (
	const void* pHandle,
	const char* lpszClientIpAddr,								/* optional */
	const Sm_AgentApi_ResourceContext_t* pResourceContext,
	const Sm_AgentApi_Realm_t* pRealm,
	const Sm_AgentApi_UserCredentials_t* pUserCredentials,
	Sm_AgentApi_Session_t* pSession,
	long* pNumAttributes,
	Sm_AgentApi_Attribute_t** ppAttributes);


/*
** Logout
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
*/

int SM_EXTERN Sm_AgentApi_Logout (
	const void* pHandle,
	const char* lpszClientIpAddr,								/* optional */
	const Sm_AgentApi_Session_t* pSession);

	
/*
** Is user authorized to access a resource?
**
** The updated session spec is returned in the session structure.
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
*/

int SM_EXTERN Sm_AgentApi_Authorize (
	const void* pHandle,
	const char* lpszClientIpAddr,								/* optional */
	const char* lpszTransactionId,								/* optional */
	const Sm_AgentApi_ResourceContext_t* pResourceContext,
	const Sm_AgentApi_Realm_t* pRealm,
	Sm_AgentApi_Session_t* pSession,
	long* pNumAttributes,
	Sm_AgentApi_Attribute_t** ppAttributes);


/*
** Audit authorizations out of agent cache.
**
** The updated session spec is returned in the session structure.
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
*/

int SM_EXTERN Sm_AgentApi_Audit (
	const void* pHandle,
	const char* lpszClientIpAddr,								/* optional */
	const char* lpszTransactionId,								/* optional */
	const Sm_AgentApi_ResourceContext_t* pResourceContext,
	const Sm_AgentApi_Realm_t* pRealm,							/* realm oid and domain oid must be set */
	Sm_AgentApi_Session_t* pSession);


/*
** Update response attributes when authenticating or authorizing out of agent cache
**
** When specifying request attributes, zero initialize each attribute structure
** then set the 'lpszAttributeOid' field. Use the same field to map the response
** attributes to requested attributes - not all attributes may be updated.
**
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_YES
**		SM_AGENTAPI_NO
*/

int SM_EXTERN Sm_AgentApi_UpdateAttributes (
	const void* pHandle,
	const char* lpszClientIpAddr,								/* optional */
	const char* lpszTransactionId,								/* optional */
	const Sm_AgentApi_ResourceContext_t* pResourceContext,
	const Sm_AgentApi_Realm_t* pRealm,
	const Sm_AgentApi_Session_t* pSession,
	long nNumReqAttributes,
	Sm_AgentApi_Attribute_t* pReqAttributes,
	long* pRespNumAttributes,
	Sm_AgentApi_Attribute_t** ppRespAttributes);
	

/************************************************************************************************
**                                Secure Tunnel Functions
************************************************************************************************/

/*
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_NO (server doesn't support this operation)
**		SM_AGENTAPI_YES (response is available)
*/

/* service response data and status message returned as attributes */
#define SM_AGENTAPI_ATTR_STATUS_MESSAGE			158
#define SM_AGENTAPI_ATTR_SERVICE_DATA			164

typedef struct Sm_AgentApi_TunnelServiceRequest_s
{
	char	lpszLibrary[SM_AGENTAPI_SIZE_NAME];
	char	lpszFunction[SM_AGENTAPI_SIZE_NAME];
	char	lpszParameter[SM_AGENTAPI_SIZE_SERVICEINFO];
	long	nLength;
	void*	pData;
} Sm_AgentApi_TunnelServiceRequest_t;


int SM_EXTERN Sm_AgentApi_Tunnel (
	const void* pHandle,
	const int nServer,
	const char* lpszClientIpAddr,								/* optional */
	const char* lpszTransactionId,								/* optional */
	const Sm_AgentApi_ResourceContext_t* pResourceContext,		/* optional */
	const Sm_AgentApi_TunnelServiceRequest_t* pServiceRequest,
	long* pRespNumAttributes,
	Sm_AgentApi_Attribute_t** ppRespAttributes);


/* get the size of the largest buffer accepted by SmTunnel */

long SM_EXTERN Sm_AgentApi_GetMaxTunnelBufSize (void);


/************************************************************************************************
**                                Helper Functions
************************************************************************************************/

/* free the attributes */

void SM_EXTERN Sm_AgentApi_FreeAttributes (
  const long nNumAttributes,
  const Sm_AgentApi_Attribute_t* pAttributes);


/*
** Make certificate hash. Current implementation requires nCertHashLen >= 20
**
** Return values:
**		SM_AGENTAPI_SUCCESS
**		SM_AGENTAPI_FAILURE
*/

#define SM_AGENTAPI_CERT_HASH_SIZE 20

int SM_EXTERN Sm_AgentApi_MakeCertificateHash (
	const unsigned char* pCertificateData,
	const long nCertLen,
	unsigned char* pCertHash,
	const long nCertHashLen);

/*
** Get agent configuration
**
** Return values:
**		SM_AGENTAPI_SUCCESS
**		SM_AGENTAPI_FAILURE
*/
int SM_EXTERN Sm_AgentApi_GetConfig (
	Sm_AgentApi_Init_t* pInit,
	const char *lpszAgentName,
	const char *lpszPath);

/************************************************************************************************
**                                Private Functions (NOT SUPPORTED)
************************************************************************************************/

/*
** Return values:
**		SM_AGENTAPI_NOCONNECTION
**		SM_AGENTAPI_FAILURE
**		SM_AGENTAPI_TIMEOUT
**		SM_AGENTAPI_NO (server doesn't support this operation)
**		SM_AGENTAPI_YES (response is available)
*/

int SM_EXTERN Sm_AgentApi_Transact (
	const void* pHandle,
	const int nServer,
	long* pNumBytes,
	char* pBuffer);

/* get the size of the largest buffer accepted by SmTransact */

long SM_EXTERN Sm_AgentApi_GetMaxTransactBufSize (void);

#if defined(unix)
}
#endif

#endif
