#ifndef _SmPolicyApi_h_
#define _SmPolicyApi_h_


/*
Copyright (C) 1997-2000, Netegrity, Inc. All rights reserved.

Netegrity, Inc. makes no representations concerning either
the merchantability of this software or the suitability of this
software for any particular purpose. It is provided "as is"
without express or implied warranty of any kind.

SiteMinder Policy API
*/

#include "SmApi.h"

#define SM_POLICY_API_VERSION   0x0400
#define BFSIZE                  1024



/*********************
	Return Statuses
**********************/
enum Sm_PolicyApi_Status_t 
{
	 Sm_PolicyApi_Success                   =  0
	,Sm_PolicyApi_Failure                   = -1
	,Sm_PolicyApi_DuplicateEntry            = -2
	,Sm_PolicyApi_DoesNotExist              = -3
	,Sm_PolicyApi_NotFound                  = -4
	,Sm_PolicyApi_RuleNotFound              = -5
	,Sm_PolicyApi_ResponseNotFound          = -6
	,Sm_PolicyApi_PolicyNotFound            = -7
	,Sm_PolicyApi_RealmNotFound             = -8
	,Sm_PolicyApi_DomainNotFound            = -9
	,Sm_PolicyApi_UserDirNotFound           = -10
	,Sm_PolicyApi_AgentNotFound             = -11
	,Sm_PolicyApi_VendorNotFound            = -12
	,Sm_PolicyApi_SchemeNotFound            = -13
	,Sm_PolicyApi_VendorAttrNotFound        = -14
	,Sm_PolicyApi_VendorMismatch            = -15
	,Sm_PolicyApi_BadArgument               = -16
	,Sm_PolicyApi_InvalidObjectID           = -17
	,Sm_PolicyApi_BadUserSpecification      = -18
	,Sm_PolicyApi_ClassMismatch             = -19
	,Sm_PolicyApi_WrongNumberOfElements     = -20
	,Sm_PolicyApi_BadGroup                  = -21
	,Sm_PolicyApi_GroupNotFound             = -22
	,Sm_PolicyApi_AdminNotFound             = -23
	,Sm_PolicyApi_SchemeIsRequired          = -24
	,Sm_PolicyApi_InvalidHandle             = -25
    ,Sm_PolicyApi_ODBCQuerySchemeNotFound   = -26
	,Sm_PolicyApi_RegSchemeNotFound			= -27


	,Sm_PolicyApi_InvalidOid                = -100					
	,Sm_PolicyApi_NotImplemented            = -101		
	,Sm_PolicyApi_NotSearchable	            = -102	
	,Sm_PolicyApi_NotStorable               = -103		
	,Sm_PolicyApi_NotCollection             = -104	
	,Sm_PolicyApi_NotUnique                 = -105			
	,Sm_PolicyApi_InvalidProp               = -106			
	,Sm_PolicyApi_NotInitted                = -107			
	,Sm_PolicyApi_NoSession                 = -108			
	,Sm_PolicyApi_OidInUseByRealm           = -109		
	,Sm_PolicyApi_OidInUseByRule            = -110		
	,Sm_PolicyApi_OidInUseByAdmin           = -111		
	,Sm_PolicyApi_MissingProperty           = -112		
	,Sm_PolicyApi_GroupMemberName           = -113		
	,Sm_PolicyApi_RadiusIpAddrNotUnique     = -114
	,Sm_PolicyApi_GroupVendor               = -115			
	,Sm_PolicyApi_RadiusRealmNotUnique      = -116	
	,Sm_PolicyApi_RealmFilterNotUnique      = -117
	,Sm_PolicyApi_InvalidCharacters         = -118
	,Sm_PolicyApi_VendorCantBeDeleted       = -119
	,Sm_PolicyApi_ProvNotImplemented        = -120
	,Sm_PolicyApi_ProvNotUnique             = -121
	,Sm_PolicyApi_RealmCantBeUsedInRule     = -122
	,Sm_PolicyApi_OidInUseByCertMap         = -123
	,Sm_PolicyApi_OidInUseBySelfReg         = -124
	,Sm_PolicyApi_OidInUseByUserDirectory   = -125
    ,Sm_PolicyApi_SchemeCantBeDeleted       = -126
    ,Sm_PolicyApi_BasicSchemeUpdate         = -127
    ,Sm_PolicyApi_NonHtmlForm               = -128
    ,Sm_PolicyApi_IllegalRealmOperation     = -129

};

/*
 These values are used to identify the structures that are allocated/freed
 by the API implementation
*/
enum Sm_PolicyApi_Structs_t  
{
	 Sm_PolicyApi_NULL_ID               = 0
	,Sm_PolicyApi_Rule_ID               = 1
	,Sm_PolicyApi_Policy_ID             = 2
	,Sm_PolicyApi_Realm_ID              = 3
	,Sm_PolicyApi_Response_ID           = 4
	,Sm_PolicyApi_UserDir_ID            = 5
	,Sm_PolicyApi_Agent_ID              = 6
	,Sm_PolicyApi_Domain_ID             = 7
	,Sm_PolicyApi_PolicyLink_ID         = 8
	,Sm_PolicyApi_ResponseAttr_ID       = 9
	,Sm_PolicyApi_User_ID               = 10
	,Sm_PolicyApi_Scheme_ID             = 11
	,Sm_PolicyApi_Admin_ID              = 12
	,Sm_PolicyApi_Group_ID              = 13
    ,Sm_PolicyApi_ODBCQueryScheme_ID    = 14
};

/*
 These values are used to identify the properties that can by get/set/removed 
 by the API
*/
enum Sm_PolicyApi_Objects_t 
{
	 Sm_PolicyApi_NULL_Domain_Prop      = 0
	,Sm_PolicyApi_Rule_Prop             = 1		/* Domain */
	,Sm_PolicyApi_RuleGroup_Prop        = 2	    /* Domain */
	,Sm_PolicyApi_Policy_Prop           = 3		/* Domain */
	,Sm_PolicyApi_Realm_Prop            = 4		/* Domain */
	,Sm_PolicyApi_ResponseGroup_Prop    = 5     /* Domain */
	,Sm_PolicyApi_Response_Prop         = 6		/* Domain */
	,Sm_PolicyApi_UserDir_Prop          = 7		/* Global or Domain */
	,Sm_PolicyApi_Scheme_Prop           = 8		/* Global */
	,Sm_PolicyApi_Agent_Prop            = 9		/* Global */
	,Sm_PolicyApi_AgentGroup_Prop       = 10	/* Global  */
	,Sm_PolicyApi_Domain_Prop           = 11	/* Global */
	,Sm_PolicyApi_Admins_Prop           = 12	/* Global or Domain */
    ,Sm_PolicyApi_ODBCQueryScheme_Prop  = 13    /* Global */
};

enum Sm_PolicyApi_Groups_t 
{
	 Sm_PolicyApi_NULL_Group_Prop       = 0
	,Sm_PolicyApi_Rule_Group_Prop       = 1
	,Sm_PolicyApi_Response_Group_Prop   = 2
	,Sm_PolicyApi_Agent_Group_Prop      = 3
};

enum Sm_PolicyApi_ManagementCommands_t
{
	 Sm_PolicyApi_ManagementCommand_FlushAll            = 1		/* no data field required */
	,Sm_PolicyApi_ManagementCommand_FlushUsers          = 2		/* no data field required */
	,Sm_PolicyApi_ManagementCommand_FlushRealms         = 3		/* no data field required */
    ,Sm_PolicyApi_ManagementCommand_ChangeDynamicKeys   = 4		/* no data field required */
	,Sm_PolicyApi_ManagementCommand_ChangePersistentKey = 5		/* data field may conatain optional key value */
	,Sm_PolicyApi_ManagementCommand_ChangeSessionKey    = 6     /* data field may contain optional key value */
};


// admin rights
enum Sm_PolicyApi_AdminRights_t
{
	 Sm_PolicyApi_AdminRights_ManageAllDomains	            = 0x01
	,Sm_PolicyApi_AdminRights_ManageObjects	                = 0x02
	,Sm_PolicyApi_AdminRights_ManageUsers		            = 0x04
	,Sm_PolicyApi_AdminRights_ManageKeys                    = 0x08
    ,Sm_PolicyApi_AdminRights_ManagePasswordPolicy          = 0x08
	,Sm_PolicyApi_AdminRights_ManageReports		            = 0x10
};


// These defines are used in the Sm_PolicyApi_AddUsersToPolicy call
// Bit 0x01 determines if user policy excludes 'users', rather than includes
#define Sm_PolicyApiPolicyFlags_Exclude_Mask	0x01
#define Sm_PolicyApiPolicyFlags_Exclude_No	    0x00
#define Sm_PolicyApiPolicyFlags_Exclude_Yes	    0x01

// Bit 0x02 determines if user policy is recursive (this is applicable to object classes that can be nested)
#define Sm_PolicyApiPolicyFlags_Recursive_Mask	0x02
#define Sm_PolicyApiPolicyFlags_Recursive_No	0x00
#define Sm_PolicyApiPolicyFlags_Recursive_Yes	0x02

/*********************
	Structures
**********************/

/* Rule */
typedef struct Sm_PolicyApi_Rule_s 
{
	int					        iStructId;
    char                        pszOid[BFSIZE];
	char				        pszName[BFSIZE];
	char				        pszDesc[BFSIZE];
	char 				        pszRealmName[BFSIZE];	
	char				        pszAction[BFSIZE];
	char				        pszResource[2*BFSIZE];
	bool				        bAllowAccess;
	bool				        bRegularExpression;
	char				        pszActiveExpr[BFSIZE];
	bool				        bIsEnabled;
	struct Sm_PolicyApi_Rule_s*	next;
} Sm_PolicyApi_Rule_t;

/* Policy */
typedef struct Sm_PolicyApi_Policy_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	char				            pszActiveExpr[BFSIZE];
	bool				            bIsEnabled;
	char				            pszIPAddress[BFSIZE];
	struct Sm_PolicyApi_Policy_s*	next;
} Sm_PolicyApi_Policy_t;


/* Realm */
typedef struct Sm_PolicyApi_Realm_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	char				            pszResourceFilter[BFSIZE];
	char				            pszAgentName[BFSIZE];
	char				            pszSchemeName[BFSIZE];
	char				            pszParentRealmName[BFSIZE];
	char				            pszAzUserDirName[BFSIZE];
	char				            pszRegSchemeName[BFSIZE];
    bool				            bProcessAuthEvents;
	bool				            bProcessAzEvents;
	bool				            bProtectAll;
	int					            nMaxTimeout;
	int					            nIdleTimeout;
    bool    			            bSyncAudit;
	struct Sm_PolicyApi_Realm_s*	next;

} Sm_PolicyApi_Realm_t;

/* Response */
typedef struct Sm_PolicyApi_Response_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
    char                            pszVendor[BFSIZE];
	struct Sm_PolicyApi_Response_s*	next;
} Sm_PolicyApi_Response_t;

/* UserDir */
typedef struct Sm_PolicyApi_UserDir_s 
{
	int					iStructId;
    char                pszOid[BFSIZE];
	char				pszName[BFSIZE];
	char				pszDesc[BFSIZE];
	char				pszNamespace[BFSIZE];
	char				pszServer[BFSIZE];
	char				pszSearchRoot[BFSIZE];
	char				pszUserLookupStart[BFSIZE];
	char				pszUserLookupEnd[BFSIZE];
	char				pszUsername[BFSIZE];
	char				pszPassword[BFSIZE];
	int					nSearchResults;
	int					nSearchScope;
	int					nSearchTimeout;
	bool				bSecureConnection;
	bool    			bRequireCredentials;
	char				pszDisabledAttr[BFSIZE];
	char				pszUniversalIDAttr[BFSIZE];
    char                pszODBCQueryScheme[BFSIZE];
	char				pszAnonymousId[BFSIZE];
	char				pszPasswordData[BFSIZE];
    char                pszPasswordAttribute[BFSIZE];
	char				pszEmailAddressAttr[BFSIZE];
	char				pszChallengeRespAttr[BFSIZE];

	struct Sm_PolicyApi_UserDir_s*	next;
} Sm_PolicyApi_UserDir_t;


/* ODBC Query */
typedef struct Sm_PolicyApi_ODBCQueryScheme_s
{
    int         iStructId;
    char        pszOid[BFSIZE];
	char		pszName[BFSIZE];
	char		pszDesc[BFSIZE];
	char		pszQueryEnumerate[BFSIZE];
	char		pszQueryGetObjInfo[BFSIZE];
	char		pszQueryLookup[BFSIZE];
	char		pszQueryInitUser[BFSIZE];
	char		pszQueryAuthenticateUser[BFSIZE];
	char		pszQueryGetUserProp[BFSIZE];
	char		pszQuerySetUserProp[BFSIZE];
	char		pszQueryGetUserProps[BFSIZE];
	char		pszQueryLookupUser[BFSIZE];
	char		pszQueryGetGroups[BFSIZE];
	char		pszQueryIsGroupMember[BFSIZE];
	char		pszQueryGetGroupProp[BFSIZE];
	char		pszQuerySetGroupProp[BFSIZE];
	char		pszQueryGetGroupProps[BFSIZE];
	char		pszQueryLookupGroup [BFSIZE];
	char		pszQuerySetPassword [BFSIZE];
    struct      Sm_PolicyApi_ODBCQueryScheme_s* next;

} Sm_PolicyApi_ODBCQueryScheme_t;

/* Agent */
typedef struct Sm_PolicyApi_Agent_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	char				            pszIpAddr[BFSIZE];
	char				            pszSecret[BFSIZE];
    char                            pszVendor[BFSIZE];
	int					            nRealmHintAttrId;
	struct Sm_PolicyApi_Agent_s*	next;
} Sm_PolicyApi_Agent_t;

/* Domain */
typedef struct Sm_PolicyApi_Domain_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	struct Sm_PolicyApi_Domain_s*	next;
} Sm_PolicyApi_Domain_t;

/* PolicyLink */
typedef struct Sm_PolicyApi_PolicyLink_s 
{
	int					                iStructId;
    char                                pszOid[BFSIZE];
    char                                pszRealm[BFSIZE];
	char				                pszRule[BFSIZE];
	char				                pszResponse[BFSIZE];
	struct Sm_PolicyApi_PolicyLink_s*	next;
} Sm_PolicyApi_PolicyLink_t;

/* Response Attributes */
typedef struct Sm_PolicyApi_ResponseAttr_s 
{
	int                                 iStructId;
    char                                pszOid[BFSIZE];
	char				                pszName[BFSIZE];
	char                                pszValue[BFSIZE];
	int					                iTTL;
	int					                iFlags;
    struct Sm_PolicyApi_ResponseAttr_s* next;
} Sm_PolicyApi_ResponseAttr_t;
	
/* Scheme */
typedef struct Sm_PolicyApi_Scheme_s 
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	int					            nLevel;
	char				            pszLib[BFSIZE];
	char				            pszParam[BFSIZE];
	char				            pszSecret[BFSIZE];
	bool				            bIsTemplate;
	bool				            bIsUsedbyAdmin;
    Sm_Api_SchemeType_t             nType;
    bool                            bAllowSaveCreds;
    bool                            bIsRadius;
    bool                            bIgnorePwCheck;
	struct Sm_PolicyApi_Scheme_s*	next;
} Sm_PolicyApi_Scheme_t;

/* Users */
typedef struct Sm_PolicyApi_User_s 
{
	int					iStructId;
	char				pszPath[BFSIZE];
	char				pszClass[BFSIZE];
	int					nFlags;
	struct Sm_PolicyApi_User_s*	next;
} Sm_PolicyApi_User_t;

/* Admins */
typedef struct Sm_PolicyApi_Admin_s
{
	int					            iStructId;
    char                            pszOid[BFSIZE];
	char				            pszName[BFSIZE];
	char				            pszDesc[BFSIZE];
	char				            pszPassword[BFSIZE];
	char				            pszUserDirName[BFSIZE];
	char				            pszSchemeName[BFSIZE];
    Sm_PolicyApi_AdminRights_t      nRights;
	struct Sm_PolicyApi_Admin_s*	next;
} Sm_PolicyApi_Admin_t;

/* Groups */
typedef struct Sm_PolicyApi_Group_s 
{
	int					iStructId;
    char                pszOid[BFSIZE];
	char				pszName[BFSIZE];
	char				pszDesc[BFSIZE];
    char                pszVendor[BFSIZE];
	struct Sm_PolicyApi_Group_s*	next;
} Sm_PolicyApi_Group_t;

/* Management Command */
typedef struct Sm_PolicyApi_ManagementCommand_s 
{
	Sm_PolicyApi_ManagementCommands_t			iCommand;
	char										pszData[BFSIZE];
} Sm_PolicyApi_ManagementCommand_t;


/*********************
	Functions
**********************/

#if defined(unix)
extern "C" {
#endif

/* 
  Login:
  This function has to be the first function called by the API user. 
*/
int SM_EXTERN Sm_PolicyApi_Login (
		void** pHandle,
		int    nCheckCreds,
		const char*  pszUserName,
        const char*  pszPassword,
        const char*  pszClientIP,
        char*  pszUserMsg,
        char*  pszErrMsg);

/*
 Logout:
 This function has to be the last function that is called by the API
 Failure to call this function will result in a memory leak
*/
int SM_EXTERN Sm_PolicyApi_Logout (void* pHandle);

/*
 This function should be called to free up the memory that is 
 allocated by the API.
*/
int SM_EXTERN Sm_PolicyApi_FreeMemory(void* pMem);

/*
 Frees up the memory used for string arrays that are allocated by
 the API.
*/
int SM_EXTERN Sm_PolicyApi_FreeStringArray(
		char* pszStringArray[]);



/* Domain Objects */

/* Rules */

/* Add a Rule and associates the rule with a domain */
int SM_EXTERN Sm_PolicyApi_AddRule (
		void* pHandle,
		const char* szDomainName,
		Sm_PolicyApi_Rule_t* pStructRule,
		bool bUpdate);

/* Deletes a Rule */
int SM_EXTERN Sm_PolicyApi_DeleteRule (
		void* pHandle, 
		const char* szRuleName, 
        const char* szRealmName,
		const char* szDomainName);

/* Get the Contents of a Rule */
int SM_EXTERN Sm_PolicyApi_GetRule (
		void* pHandle,
		const char* szRuleName,
		const char* szRealmName,
		const char* szDomainName,
		Sm_PolicyApi_Rule_t** ppstructRule);

/* Policies */

/* Add a Policy and associates the rule with a domain */
int SM_EXTERN Sm_PolicyApi_AddPolicy (
		void* pHandle, 
		const char* szDomainName,
		Sm_PolicyApi_Policy_t* pStructPolicy,
		bool bUpdate);

/*
 Deletes a Policy
 Note: deletes all related PolicyLinks and User Policies
*/
int SM_EXTERN Sm_PolicyApi_DeletePolicy (
		void* pHandle, 
		const char* szPolicyName, 
		const char* szDomainName);

/* Get the contents of a Policy */
int SM_EXTERN Sm_PolicyApi_GetPolicy (
		void* pHandle,
		const char* szPolicyName,
		const char* szDomainName,
		Sm_PolicyApi_Policy_t** ppstructPolicy);

/* PolicyLink */

/* Adds a PolicyLink to a Policy */
int SM_EXTERN Sm_PolicyApi_AddPolicyLink (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		Sm_PolicyApi_PolicyLink_t *pstructPolicyLink);

/* Deletes a PolicyLink */
int SM_EXTERN Sm_PolicyApi_RemoveRuleFromPolicy (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
        const char* szRealmName,
		const char* szRuleName);

/* For the specified Policy and Domain, return all of the PolicyLinks */
int SM_EXTERN Sm_PolicyApi_GetPolicyLinks (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		Sm_PolicyApi_PolicyLink_t** ppstructPolicyLink);

/* Change the Response part of a particular PolicyLink */
int SM_EXTERN Sm_PolicyApi_SetResponseInPolicyLink (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		Sm_PolicyApi_PolicyLink_t* ppstructPolicyLink);


/* Users */

/*
 Adds Users to a Policy.  Can only add one User(can be 
 an aggregate) at a time
*/
int SM_EXTERN Sm_PolicyApi_AddUsersToPolicy (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		const char* szUserDirName,
		const char* szUsers,
		int   iPolicyFlags);

/*
 Remove Users from a Policy. Can only remove one User
 (can be an aggregate) at a time
*/
int SM_EXTERN Sm_PolicyApi_RemoveUsersFromPolicy (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		const char* szUserDirName,
		const char* szUsers);

/* Get a list of Users who belong to a Policy */
int SM_EXTERN Sm_PolicyApi_GetPolicyUsers (
		void* pHandle,
		const char* szDomainName,
		const char* szPolicyName,
		const char* szUserDirName,
		Sm_PolicyApi_User_t **ppStructUsers);

/* Realms */

/* Adds a Realm and associate it with a Domain */
int SM_EXTERN Sm_PolicyApi_AddRealm (
		void* pHandle,
		const char* szDomainName,
		Sm_PolicyApi_Realm_t* pStructRealm,
		bool bUpdate);
/*
 Deletes a Realm
 Note: Can't delete a Realm if any existing Rules are linked
*/
int SM_EXTERN Sm_PolicyApi_DeleteRealm (
		void* pHandle, 
		const char* szRealmName, 
		const char* szDomainName);

/* Get the contents of a Realm */
int SM_EXTERN Sm_PolicyApi_GetRealm (
		void* pHandle,
		const char* szRealmName,
		const char* szDomainName,
		Sm_PolicyApi_Realm_t** ppstructRealm);

/* Flush Realm */
int SM_EXTERN Sm_PolicyApi_FlushRealm (
		void* pHandle,
		const char* szRealmName,
		const char* szDomainName);

/* Responses */

/* creates a Response and associates it with a Domain */
int SM_EXTERN Sm_PolicyApi_AddResponse (
		void* pHandle,
		const char* szDomainName,
		Sm_PolicyApi_Response_t* pStructResponse,
		bool bUpdate);

/*
 Deletes a Response
 Note: deletes any related Response Attributes
*/
int SM_EXTERN Sm_PolicyApi_DeleteResponse (
		void* pHandle, 
		const char* szResponseName, 
		const char* szDomainName);

/* Get the contents of a Response */
int SM_EXTERN Sm_PolicyApi_GetResponse (
		void* pHandle,
		const char* szResponseName,
		const char* szDomainName,
		Sm_PolicyApi_Response_t** ppstructResponse);

/* Response Attributes */

/* Creates a Response Attribute and associates it with a Response */
int SM_EXTERN Sm_PolicyApi_AddResponseAttr (
		void* pHandle,
		const char* szResponseName,
		const char* szDomainName,
		Sm_PolicyApi_ResponseAttr_t* pstructResponseAttr);

/*
 Deletes a Response Attribute
 NOTE: the attribute name and the attribute value have to match 
 in order for the delete to happen.
*/
int SM_EXTERN Sm_PolicyApi_RemoveResponseAttr (
		void* pHandle,
		const char* szResponseName,
		const char* szDomainName,
		Sm_PolicyApi_ResponseAttr_t* pstructResponseAttr);

/* Get the Response Attributes that belong to a Response */
int SM_EXTERN Sm_PolicyApi_GetResponseAttrs (
		void* pHandle,
		const char* szResponseName,
		const char* szDomainName,
		Sm_PolicyApi_ResponseAttr_t** ppstructResponseAttr);

/* Global Objects */

/* User Directory */

/* Create ODBC Query object */
int SM_EXTERN Sm_PolicyApi_CreateODBCQueryScheme (
		void* pHandle,
		Sm_PolicyApi_ODBCQueryScheme_t* pstructODBCQueryScheme,
		bool bUpdate);

/* Delete ODBC Query object */
int SM_EXTERN Sm_PolicyApi_DeleteODBCQueryScheme (
		void* pHandle,
		const char* szODBCQuerySchemeName);

/* Get ODBC Query object contents*/
int SM_EXTERN Sm_PolicyApi_GetODBCQueryScheme (
		void* pHandle,
        const char* szODBCQuerySchemeName,
		Sm_PolicyApi_ODBCQueryScheme_t** pstructODBCQueryScheme);


/* Create a User Directory object */
int SM_EXTERN Sm_PolicyApi_CreateUserDir (
		void* pHandle,
		Sm_PolicyApi_UserDir_t* pstructUserDir,
		bool bUpdate);

/*
 Delete a User Directory
 Note: Removes Directory Users from Policies
*/
int SM_EXTERN Sm_PolicyApi_DeleteUserDir (
		void* pHandle,
		const char* szUserDirName);

/* Get a User Dir object's contents */
int SM_EXTERN Sm_PolicyApi_GetUserDir (
		void* pHandle,
		const char* szUserDirName,
		Sm_PolicyApi_UserDir_t** ppstructUserDir);

/* Associate an existing User Dir with a Domain */ 
int SM_EXTERN Sm_PolicyApi_AddUserDirToDomain(
		void* pHandle,
		const char* szUserDirName,
		const char* szDomainName);

/* Disassociate an existing User Dir with a Domain */
int SM_EXTERN Sm_PolicyApi_RemoveUserDirFromDomain(
		void* pHandle,
		const char* szUserDirName,
		const char* szDomainName);

/* Retrieve the search order of User Dirs for a Domain */
int SM_EXTERN Sm_PolicyApi_GetUserDirSearchOrder(
		void* pHandle,
		const char* szDomainName,
		char** pszArray[]);

/* Set the search order of User Dirs for a Domain */
int SM_EXTERN Sm_PolicyApi_SetUserDirSearchOrder(
		void* pHandle,
		const char* szDomainName,
		char* pszArray[]);

/* Agent */

/* Create an Agent */
int SM_EXTERN Sm_PolicyApi_AddAgent (
		void* pHandle,
		Sm_PolicyApi_Agent_t* pstructAgent,
		bool bUpdate);

/*
 Deletes an Agent
 Note: Can't delete if there are any Realms linked to the Agent 
*/
int SM_EXTERN Sm_PolicyApi_DeleteAgent (
		void* pHandle,
		const char* szAgentName);

/* Get the contents of an Agent object */
int SM_EXTERN Sm_PolicyApi_GetAgent (
		void* pHandle,
		const char* szAgentName,
		Sm_PolicyApi_Agent_t** ppstructAgent);

/* AgentCommand */

/* Domain */

/* Create a Domain */
int SM_EXTERN Sm_PolicyApi_AddDomain (
		void* pHandle, 
		Sm_PolicyApi_Domain_t* pstructDomain,
		bool bUpdate);

/* Delete a domain.  
 Note: Also deletes its children (Rules,Responses,Realms,Policies) */
int SM_EXTERN Sm_PolicyApi_DeleteDomain (
		void* pHandle,
		const char* szDomainName);

/* Get the contents of a Domain object */
int SM_EXTERN Sm_PolicyApi_GetDomain (
		void* pHandle,
		const char* szDomainName,
		Sm_PolicyApi_Domain_t** ppstructDomain);

/* Scheme */

/* Create a Scheme */
int SM_EXTERN Sm_PolicyApi_AddScheme (
		void* pHandle, 
		Sm_PolicyApi_Scheme_t* pstructScheme,
		bool bUpdate);

/* Delete a Scheme.  */
int SM_EXTERN Sm_PolicyApi_DeleteScheme (
		void* pHandle,
		const char* szSchemeName);

/* Get the contents of a Scheme object */
int SM_EXTERN Sm_PolicyApi_GetScheme (
		void* pHandle,
		const char* szSchemeName,
		Sm_PolicyApi_Scheme_t** ppstructScheme);


/* Admin */

/* Create an Admin */
int SM_EXTERN Sm_PolicyApi_AddAdmin (
		void* pHandle, 
		Sm_PolicyApi_Admin_t* pstructAdmin,
		bool bUpdate);

/* Delete an Admin.  */
int SM_EXTERN Sm_PolicyApi_DeleteAdmin (
		void* pHandle,
		const char* szAdminName);

/* Get the contents of a Admin object */
int SM_EXTERN Sm_PolicyApi_GetAdmin (
		void* pHandle,
		const char* szAdminName,
		Sm_PolicyApi_Admin_t** ppstructAdmin);

/* Associate an existing Admin with a Domain  */
int SM_EXTERN Sm_PolicyApi_AddAdminToDomain(
		void* pHandle,
		const char* szAdminName,
		const char* szDomainName);

/* Disassociate an existing Admin with a Domain  */
int SM_EXTERN Sm_PolicyApi_RemoveAdminFromDomain(
		void* pHandle,
		const char* szAdminName,
		const char* szDomainName);


/* used for getting the names of the objects contained within the domain */
int SM_EXTERN Sm_PolicyApi_GetDomainObjectNames (
		void* pHandle,
		const char* szDomainName,
		Sm_PolicyApi_Objects_t propId,
		char** pszArray[]);

/*
 Capable of retrieving the names of the Global objects contained
 in the Sm_PolicyApi_Objects_t enumeration
*/
int SM_EXTERN Sm_PolicyApi_GetGlobalObjectNames (
		void* pHandle,
		Sm_PolicyApi_Objects_t propId,
		char** pszArray[]);

/* Users */

/* Returns a list of all Users */
int SM_EXTERN Sm_PolicyApi_GetDirectoryContents (
		void* pHandle,
		const char* szUserDirName,
		Sm_PolicyApi_User_t** ppStructUsers);

/* Groups */

/* Creates a new Group of any type (rule, response, agent) */
int SM_EXTERN Sm_PolicyApi_AddGroup (
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szDomainName,
		Sm_PolicyApi_Group_t* pStructGroup,
		bool bUpdate);

/* Deletes a Group of any type (rule, response, agent) */
int SM_EXTERN Sm_PolicyApi_DeleteGroup (
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szDomainName,
		const char* szGroupName);

/* Deletes a Group of any type (rule, response, agent) */
int SM_EXTERN Sm_PolicyApi_GetGroup (
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szGroupName,
		const char* szDomainName,
		Sm_PolicyApi_Group_t** ppStructGroup);

int SM_EXTERN Sm_PolicyApi_GetGroupNames(
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szGroupName,
		const char* szDomainName,
		char** pszArray[]);

int SM_EXTERN Sm_PolicyApi_AddToGroup(
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szGroupName,
		const char* szItemName,
		const char* szDomainName,
        const char* szRealmName="");

int SM_EXTERN Sm_PolicyApi_RemoveFromGroup(
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szGroupName,
		const char* szItemName,
		const char* szDomainName,
        const char* szRealmName="");

int SM_EXTERN Sm_PolicyApi_IsGroup(
		void* pHandle,
		Sm_PolicyApi_Groups_t dwGroup,
		const char* szName,
		const char* szDomainName,
		bool* bIsGroup);


/* Management Command */
int SM_EXTERN Sm_PolicyApi_ManagementCommand (
		void* pHandle,
		Sm_PolicyApi_ManagementCommand_t* pstructManagementCommand);

int SM_EXTERN Sm_PolicyApi_RenameObject(
		void* pHandle,
        const char* szOId,
        const char* szNewName);

/* User Management */
int SM_EXTERN Sm_PolicyApi_SetDisableUserState (
		void* pHandle,
		const char* pszUserDirName,
        const char* pszUserDN,
        Sm_Api_DisabledReason_t nDisabledReason,
        char* pszErrMsg);

int SM_EXTERN Sm_PolicyApi_GetDisableUserState (
		void* pHandle,
		const char* pszUserDirName,
        const char* pszUserDN,
        Sm_Api_DisabledReason_t *nDisabledReason,
        char* pszErrMsg);

int SM_EXTERN Sm_PolicyApi_SetPassword (
		void* pHandle,
		const char* pszUserDirName,
        const char* pszUserDN,
		const char* pszPassword,
        char* pszErrMsg);

int SM_EXTERN Sm_PolicyApi_FlushUser (
		void* pHandle,
		const char* pszUserDirName,
        const char* pszUserDN,
        char* pszErrMsg);


#if defined(unix)
}
#endif

#endif
