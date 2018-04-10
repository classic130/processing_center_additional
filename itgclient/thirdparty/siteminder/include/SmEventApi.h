#ifndef _SmEventApi_h_
#define _SmEventApi_h_

/*
Copyright (C) 1997-2000, Netegrity, Inc. All rights reserved.

Netegrity, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

SiteMinder Event Provider Server API
*/

#include "SmApi.h"

/*
// Category types
*/

enum SmLog_t
{
	 SmLog_Access = 1
	,SmLog_Obj = 2
    ,SmLog_System = 3
	,SmLog_EMS = 4
};


/*
// Access log categories
*/

enum SmLogAccessCat_t
{
	 SmLogAccessCat_Auth = 1
	,SmLogAccessCat_Az = 2
	,SmLogAccessCat_Admin = 3
	,SmLogAccessCat_Affiliate = 4
};


/*
// Access log events
*/

enum SmLogAccessEvent_t
{
	 SmLogAccessEvent_AuthAccept = 1
	,SmLogAccessEvent_AuthReject = 2
	,SmLogAccessEvent_AuthAttempt = 3
	,SmLogAccessEvent_AuthChallenge = 4
	,SmLogAccessEvent_AzAccept = 5
	,SmLogAccessEvent_AzReject = 6
	,SmLogAccessEvent_AdminLogin = 7
	,SmLogAccessEvent_AdminLogout = 8
	,SmLogAccessEvent_AdminReject = 9
	,SmLogAccessEvent_AuthLogout = 10
	,SmLogAccessEvent_ValidateAccept = 11
	,SmLogAccessEvent_ValidateReject = 12
	,SmLogAccessEvent_Visit = 13
};


/*
// Object log categories
*/

enum SmLogObjCat_t
{
	 SmLogObjCat_Auth = 1
	,SmLogObjCat_Agent = 2
	,SmLogObjCat_AgentGroup = 3
	,SmLogObjCat_Domain = 4
	,SmLogObjCat_Policy = 5
	,SmLogObjCat_PolicyLink = 6
	,SmLogObjCat_Realm = 7
	,SmLogObjCat_Response = 8
	,SmLogObjCat_ResponseAttr = 9
	,SmLogObjCat_ResponseGroup = 10
	,SmLogObjCat_Root = 11
	,SmLogObjCat_Rule = 12
	,SmLogObjCat_RuleGroup = 13
	,SmLogObjCat_Scheme= 14
	,SmLogObjCat_UserDirectory = 15
	,SmLogObjCat_UserPolicy = 16
	,SmLogObjCat_Vendor = 17
	,SmLogObjCat_VendorAttr = 18
	,SmLogObjCat_Admin = 19
	,SmLogObjCat_AuthAzMap = 20
	,SmLogObjCat_CertMap = 21
	,SmLogObjCat_ODBCQuery = 22
	,SmLogObjCat_SelfReg = 23
	,SmLogObjCat_PasswordPolicy = 24
	,SmLogObjCat_KeyManagement = 25
	,SmLogObjCat_AgentKey = 26
	,SmLogObjCat_ManagementCommand = 27
	,SmLogObjCat_RootConfig = 28
};


/*
// Object log events
*/

enum SmLogObjEvent_t
{
	 SmLogObjEvent_Create = 1
	,SmLogObjEvent_Update = 2
	,SmLogObjEvent_UpdateField = 3
	,SmLogObjEvent_Delete = 4
	,SmLogObjEvent_Login = 5
	,SmLogObjEvent_Logout = 6
	,SmLogObjEvent_LoginReject = 7
    ,SmLogObjEvent_FlushAll = 8
    ,SmLogObjEvent_FlushUser = 9
    ,SmLogObjEvent_FlushUsers = 10
    ,SmLogObjEvent_FlushRealms = 11
    ,SmLogObjEvent_ChangeDynamicKeys = 12
    ,SmLogObjEvent_ChangePersistentKey = 13
    ,SmLogObjEvent_ChangeDisabledUserState = 14
    ,SmLogObjEvent_ChangeUserPassword = 15
    ,SmLogObjEvent_FailedLoginAttemptsCount = 16
	,SmLogObjEvent_ChangeSessionKey= 17
};


/*
// System log categories
*/

enum SmLogSystemCat_t
{
     SmLogSystemCat_Auth = 1
    ,SmLogSystemCat_Acct = 2
    ,SmLogSystemCat_Az = 3
    ,SmLogSystemCat_Admin = 4
    ,SmLogSystemCat_System = 5
};

/*
// System log events
*/

enum SmLogSystemEvent_t
{
	 SmLogSystemEvent_ServerInit = 1
	,SmLogSystemEvent_ServerInitFail = 2
	,SmLogSystemEvent_ServerUp = 3
	,SmLogSystemEvent_ServerDown = 4
	,SmLogSystemEvent_LogFileOpenFail = 5
	,SmLogSystemEvent_AgentInfo = 6
	,SmLogSystemEvent_AgentConnectionStart = 7
	,SmLogSystemEvent_AgentConnectionFail = 8
	,SmLogSystemEvent_AgentConnectionEnd = 9
	,SmLogSystemEvent_DbConnect = 10
	,SmLogSystemEvent_DbConnectFail = 11
	,SmLogSystemEvent_LdapConnect = 12
	,SmLogSystemEvent_LdapConnectFail = 13
    ,SmLogSystemEvent_AmbiguousResourceMatch= 14
    ,SmLogSystemEvent_AmbiguousRadiusMatch= 15
    ,SmLogSystemEvent_AgentHeartbeat = 16
    ,SmLogSystemEvent_ServerHeartbeat = 17
};

/*
// EMS categories
*/

enum SmLogEmsCat_t
{
	 SmLogEmsCat_DirectoryAdmin = 100     /* Administrator command */
	,SmLogEmsCat_DirectoryUser = 200      /* End-user (self-reg) */
	,SmLogEmsCat_DirectorySession = 300	  /* Session event */
	,SmLogEmsCat_EventPreprocess = 400	  /* Workflow preprocess event */
	,SmLogEmsCat_EventPostprocess = 500	  /* Workflow postprocess event */
};


/*
// EMS log events
*/

enum SmLogEmsEvent_t
{
	 /* User events */
	SmLogEmsEvent_CreateUser = 101
	,SmLogEmsEvent_DeleteUser = 102
	,SmLogEmsEvent_ModifyUser = 103
	,SmLogEmsEvent_AssignUserRole = 104
	,SmLogEmsEvent_RemoveUserRole = 105
	,SmLogEmsEvent_EnableUser = 106
	,SmLogEmsEvent_DisableUser = 107
	,SmLogEmsEvent_SetUserDisabledState = 108
	,SmLogEmsEvent_AddUserToGroup = 109
	,SmLogEmsEvent_RemoveUserFromGroup = 110

	 /* Organization events */
	,SmLogEmsEvent_CreateOrg = 201
	,SmLogEmsEvent_DeleteOrg = 202
	,SmLogEmsEvent_ModifyOrg = 203

	 /* Role events */
	,SmLogEmsEvent_CreateRole = 301
	,SmLogEmsEvent_DeleteRole = 302
	,SmLogEmsEvent_ModifyRole = 303

	/* Resource Events: For internal use only */
	,SmLogEmsEvent_CreateResource = 401
	,SmLogEmsEvent_DeleteResource = 402
	,SmLogEmsEvent_ModifyResource = 403
	,SmLogEmsEvent_AssignResourceRole = 404
	,SmLogEmsEvent_RemoveResourceRole = 405

	/* Session events */
	,SmLogEmsEvent_Login = 501
	,SmLogEmsEvent_Logout = 502
	,SmLogEmsEvent_LoginFail = 503
	,SmLogEmsEvent_SessionTimeout = 505
	,SmLogEmsEvent_AuthFail = 506

	/* Password control */
	,SmLogEmsEvent_PasswordModify = 601
	,SmLogEmsEvent_PasswordMustChange = 602

	/* Admin Role events: For internal use only */
	,SmLogEmsEvent_CreateAdminRole = 701
	,SmLogEmsEvent_DeleteAdminRole = 702
	,SmLogEmsEvent_ModifyAdminRole = 703
	,SmLogEmsEvent_AssignAdminRole = 704
	,SmLogEmsEvent_RemoveAdminRole = 705

	/* Managed Organization Events: For internal use only */
	,SmLogEmsEvent_AddManagedOrg = 721
	,SmLogEmsEvent_RemoveManagedOrg = 722

	 /* Group events */
	,SmLogEmsEvent_CreateGroup = 801
	,SmLogEmsEvent_DeleteGroup = 802
	,SmLogEmsEvent_ModifyGroup = 803
	,SmLogEmsEvent_AssignGroupRole = 804
	,SmLogEmsEvent_RemoveGroupRole = 805
	,SmLogEmsEvent_AddGroupToGroup = 806
	,SmLogEmsEvent_RemoveGroupFromGroup = 807

	/* Generic object events */
	,SmLogEmsEvent_CreateObject = 901
	,SmLogEmsEvent_DeleteObject = 902
	,SmLogEmsEvent_ModifyObject = 903
	,SmLogEmsEvent_AssignObjectRole = 904
	,SmLogEmsEvent_RemoveObjectRole = 905
	,SmLogEmsEvent_AddObjectToGroup = 906
	,SmLogEmsEvent_RemoveObjectFromGroup = 907
};


/*
// Data structures
*/

typedef struct SmLog_Access_s
{
	long nVersion;
	long nCurrentTime;
	Sm_Api_Reason_t nReason;
	char* szAgentName;
	char* szSessionId;
	char* szClientIp;
	char* szUserName;
	char* szDomainOid;
	char* szRealmName;
	char* szRealmOid;
	char* szAuthDirName;
	char* szAuthDirServer;
	char* szAuthDirNamespace;
	char* szServer;
	char* szResource;
	char* szAction;
	char* szTransactionId;
	char* szStatusMsg;
} SmLog_Access_t;


typedef struct SmLog_Obj_s
{
	long nVersion;
	long nCurrentTime;
	char* szUserName;
	char* szSessionId;
	char* szDomainOid;
	char* szObjName;
	char* szObjOid;
	char* szFieldDesc;
    char* szStatusMsg;
} SmLog_Obj_t;


typedef struct SmLog_System_s
{
	long nVersion;
	long nCurrentTime;
	char* szName;
	char* szIpAddress;
	int nIpPort;
	char* szMsg;
} SmLog_System_t;


typedef struct SmLog_EMS_s
{
	long nVersion;
	long nCurrentTime;
	char* szUserName;
	char* szSessionId;
	char* szDirName;
	char* szObjName;
	char* szObjPath;
	char* szObjClass;
	char* szOrgName;
	char* szRoleName;
	char* szFieldDesc;
	char* szStatusMsg;
} SmLog_EMS_t;

/*
// Event API provider interface
*/

#define Sm_EventProviderApi_Init_FuncName      "SmEventInit"
#define Sm_EventProviderApi_Release_FuncName   "SmEventRelease"
#define Sm_EventProviderApi_Record_FuncName    "SmEventRecord"

typedef int (SM_EXTERN *Sm_EventProviderApi_Init_t) (void);

typedef void (SM_EXTERN *Sm_EventProviderApi_Release_t) (void);

typedef void (SM_EXTERN *Sm_EventProviderApi_Record_t) (
   int nCategoryType,
   int nCategory, 
   int nEventId,
   const void *pData);

#endif

