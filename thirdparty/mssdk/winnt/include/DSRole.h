/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1997-1998 Microsoft Corporation

Module Name:

    dsrole.h

Abstract:

    This module contains the public interfaces to configure the network roles of workstations,
    servers, and DCs



Author:

    Mac McLain  (MacM)          09-April-1997

Revision History:

--*/

#ifndef __DSROLE_H__
#define __DSROLE_H__

#ifdef __cplusplus
extern "C" {
#endif

//
// Data structures for configuring the role of a Dc in a domain
//

typedef ULONG DSROLE_SERVEROP_HANDLE;

//
// Status of an existing operation
//
typedef struct _DSROLE_SERVEROP_STATUS {

    LPWSTR CurrentOperationDisplayString;
    ULONG OperationStatus;

} DSROLE_SERVEROP_STATUS, *PDSROLE_SERVEROP_STATUS;

//
// where:
// CurrentOperationDisplayString is a displayable status of the current operation.  For example:
//       Locating a domain controller for the domain BRIDGE.NTDEV.MICROSOFT.COM
//       Replicating Ds Data from parent domain controller FRANK.BRIDGE.NTDEV.MICROSOFT.COM
//       Configuring KDC service to autostart
//

//
// Status returned from a GetOperationResults call
//
typedef struct _DSROLE_SERVEROP_RESULTS {

    ULONG OperationStatus;
    LPWSTR OperationStatusDisplayString;
    LPWSTR ServerInstalledSite;
    ULONG OperationResultsFlags;

} DSROLE_SERVEROP_RESULTS, *PDSROLE_SERVEROP_RESULTS;

//
// where:
// OperationStatus is the status code returned from the operation.
// OperationStatusDisplayString is a displayable status of the current operation.  For example:
//       Successfully installed a domain controller for the domain BRIDGE.NTDEV.MICROSOFT.COM
//       Failed to create the trust between BRIDGE.NTDEV.MICROSOFT.COM and
//          FRANK.BRIDGE.NTDEV.MICROSOFT.COM because the trust object already exists on the parent
// ServerInstalledSite is where the site the server was installed in is returned
// OperationResultsFlags is where any flags are returned determine any specifics about the results
//
//


//
// Operation states
//

#define DSROLE_CRITICAL_OPERATIONS_COMPLETED    0x00000001

//
// Operation results flags
//
#define DSROLE_NON_FATAL_ERROR_OCCURRED         0x00000001

//
// Determines the role of DC following a demotion
//
typedef enum _DSROLE_SERVEROP_DEMOTE_ROLE {

    DsRoleServerStandalone = 0,
    DsRoleServerMember

} DSROLE_SERVEROP_DEMOTE_ROLE, *PDSROLE_SERVEROP_DEMOTE_ROLE;


//
// Valid options for various DsRole apis
//
#define DSROLE_DC_PARENT_TRUST_EXISTS       0x00000001
#define DSROLE_DC_ROOT_TRUST_EXISTS         0x00000001
#define DSROLE_DC_DELETE_PARENT_TRUST       0x00000002
#define DSROLE_DC_DELETE_ROOT_TRUST         0x00000002
#define DSROLE_DC_ALLOW_DC_REINSTALL        0x00000004
#define DSROLE_DC_ALLOW_DOMAIN_REINSTALL    0x00000008
#define DSROLE_DC_TRUST_AS_ROOT             0x00000010
#define DSROLE_DC_DOWNLEVEL_UPGRADE         0x00000020
#define DSROLE_DC_FORCE_TIME_SYNC           0x00000040
#define DSROLE_DC_CREATE_TRUST_AS_REQUIRED  0x00000080
#define DSROLE_DC_DELETE_SYSVOL_PATH        0x00000100

//
// Options to be used for fixing up a domain controller
//
#define DSROLE_DC_FIXUP_ACCOUNT             0x00000001
#define DSROLE_DC_FIXUP_ACCOUNT_PASSWORD    0x00000002
#define DSROLE_DC_FIXUP_ACCOUNT_TYPE        0x00000004
#define DSROLE_DC_FIXUP_TIME_SERVICE        0x00000008
#define DSROLE_DC_FIXUP_DC_SERVICES         0x00000010
#define DSROLE_DC_FIXUP_FORCE_SYNC          0x00000020
#define DSROLE_DC_FIXUP_SYNC_LSA_POLICY     0x00000040
#define DSROLE_DC_FIXUP_TIME_SYNC           0x00000080

//
// Domain information
//
typedef enum _DSROLE_MACHINE_ROLE {

    DsRole_RoleStandaloneWorkstation,
    DsRole_RoleMemberWorkstation,
    DsRole_RoleStandaloneServer,
    DsRole_RoleMemberServer,
    DsRole_RoleBackupDomainController,
    DsRole_RolePrimaryDomainController
} DSROLE_MACHINE_ROLE;


//
// Previous server state
//
typedef enum _DSROLE_SERVER_STATE {

    DsRoleServerUnknown = 0,
    DsRoleServerPrimary,
    DsRoleServerBackup

} DSROLE_SERVER_STATE, *PDSROLE_SERVER_STATE;


typedef enum _DSROLE_PRIMARY_DOMAIN_INFO_LEVEL {

    DsRolePrimaryDomainInfoBasic = 1,
    DsRoleUpgradeStatus

} DSROLE_PRIMARY_DOMAIN_INFO_LEVEL;


//
// Flags to be used with the PRIMARY_DOMAIN_INFO_LEVEL structures below
//
#define DSROLE_PRIMARY_DS_RUNNING           0x00000001
#define DSROLE_PRIMARY_DS_MIXED_MODE        0x00000002

#define DSROLE_PRIMARY_DOMAIN_GUID_PRESENT  0x01000000

#define DSROLE_UPGRADE_IN_PROGRESS          0x00000001


//
// Structure that correspond to the DSROLE_PRIMARY_DOMAIN_INFO_LEVEL
//
typedef struct _DSROLE_PRIMARY_DOMAIN_INFO_BASIC {

    DSROLE_MACHINE_ROLE MachineRole;
    ULONG Flags;
    LPWSTR DomainNameFlat;
    LPWSTR DomainNameDns;
    LPWSTR DomainTreeName;
    GUID DomainGuid;

} DSROLE_PRIMARY_DOMAIN_INFO_BASIC, *PDSROLE_PRIMARY_DOMAIN_INFO_BASIC;

typedef struct _DSROLE_UPGRADE_STATUS_INFO {

    ULONG OperationState;
    DSROLE_SERVER_STATE PreviousServerState;

} DSROLE_UPGRADE_STATUS_INFO, *PDSROLE_UPGRADE_STATUS_INFO;

//
// Flags returned by DsRoleDnsNameToFlatName
//
#define DSROLE_FLATNAME_DEFAULT     0x00000001
#define DSROLE_FLATNAME_UPGRADE     0x00000002

//
// Type of the domain name to be modified
//
typedef enum _DSROLE_DOMAIN_NAME_FORMAT {

    DsRoleDomainNameFlat = 1

} DSROLE_DOMAIN_NAME_FORMAT, *PDSROLE_DOMAIN_NAME_FORMAT;


//
// General routines
//
VOID
WINAPI
DsRoleFreeMemory(
    IN PVOID    Buffer
    );

//
// Ds setup apis
//
DWORD
WINAPI
DsRoleGetDefaultDnsName(
    IN  LPCWSTR lpServer OPTIONAL,
    OUT LPWSTR *lpDefaultDnsName
    );

DWORD
WINAPI
DsRoleDnsNameToFlatName(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  LPCWSTR lpDnsName,
    OUT LPWSTR *lpFlatName,
    OUT PULONG  lpStatusFlag
    );


DWORD
WINAPI
DsRoleDcAsDc(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  LPCWSTR lpDnsDomainName,
    IN  LPCWSTR lpFlatDomainName,
    IN  LPCWSTR lpDomainAdminPassword OPTIONAL,
    IN  LPCWSTR lpSiteName, OPTIONAL
    IN  LPCWSTR lpDsDatabasePath,
    IN  LPCWSTR lpDsLogPath,
    IN  LPCWSTR lpSystemVolumeRootPath,
    IN  LPCWSTR lpParentDnsDomainName OPTIONAL,
    IN  LPCWSTR lpParentServer OPTIONAL,
    IN  LPCWSTR lpAccount OPTIONAL,
    IN  LPCWSTR lpPassword OPTIONAL,
    IN  ULONG Options,
    OUT DSROLE_SERVEROP_HANDLE *DsOperationHandle
    );

DWORD
WINAPI
DsRoleDcAsReplica(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  LPCWSTR lpDnsDomainName,
    IN  LPCWSTR lpReplicaServer,
    IN  LPCWSTR lpSiteName, OPTIONAL
    IN  LPCWSTR lpDsDatabasePath,
    IN  LPCWSTR lpDsLogPath,
    IN  LPCWSTR lpSystemVolumeRootPath,
    IN  LPCWSTR lpAccount OPTIONAL,
    IN  LPCWSTR lpPassword OPTIONAL,
    IN  ULONG Options,
    OUT DSROLE_SERVEROP_HANDLE *DsOperationHandle
    );

DWORD
WINAPI
DsRoleDemoteDc(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  LPCWSTR lpDnsDomainName OPTIONAL,
    IN  DSROLE_SERVEROP_DEMOTE_ROLE ServerRole,
    IN  LPCWSTR lpAccount OPTIONAL,
    IN  LPCWSTR lpPassword OPTIONAL,
    IN  ULONG Options,
    IN  BOOL fLastDcInDomain,
    IN  LPCWSTR lpDomainAdminPassword OPTIONAL,
    OUT DSROLE_SERVEROP_HANDLE *DsOperationHandle
    );

DWORD
WINAPI
DsRoleGetDcOperationProgress(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  DSROLE_SERVEROP_HANDLE DsOperationHandle,
    OUT PDSROLE_SERVEROP_STATUS *ServerOperationStatus
    );

DWORD
WINAPI
DsRoleGetDcOperationResults(
    IN  LPCWSTR lpServer OPTIONAL,
    IN  DSROLE_SERVEROP_HANDLE DsOperationHandle,
    OUT PDSROLE_SERVEROP_RESULTS *ServerOperationResults
    );

DWORD
WINAPI
DsRoleGetPrimaryDomainInformation(
    IN LPCWSTR lpServer OPTIONAL,
    IN DSROLE_PRIMARY_DOMAIN_INFO_LEVEL InfoLevel,
    OUT PBYTE *Buffer );

DWORD
WINAPI
DsRoleFixDc(
    IN LPCWSTR lpServer,
    IN LPCWSTR lpFixupServer, OPTIONAL
    IN LPCWSTR lpAccount, OPTIONAL
    IN LPCWSTR lpPassword, OPTIONAL
    IN ULONG Options,
    OUT PULONG CompletedOperations,
    OUT PULONG FailedOperation
    );

DWORD
WINAPI
DsRoleModifyDomainName(
    IN LPCWSTR lpServer,
    IN LPCWSTR lpDomainName,
    IN DSROLE_DOMAIN_NAME_FORMAT DomainNameFormat,
    IN LPCWSTR lpAccount, OPTIONAL
    IN LPCWSTR lpPassword OPTIONAL
    );

#ifdef __cplusplus
}
#endif

#endif // __DSROLE_H__


