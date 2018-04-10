/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996  Microsoft Corporation

Module Name:

    ntdsapi.h

Abstract:

    This file contains structures, function prototypes, and definitions
    for public NTDS APIs other than directory interfaces like LDAP.

Environment:

    User Mode - Win32

Notes:

--*/


#ifndef _NTDSAPI_H_
#define _NTDSAPI_H_

#include <schedule.h>

#if !defined(_NTDSAPI_)
#define NTDSAPI DECLSPEC_IMPORT
#else
#define NTDSAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Data definitions                                                     //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#ifdef MIDL_PASS
typedef GUID UUID;
typedef void * RPC_AUTH_IDENTITY_HANDLE;
typedef void VOID;
#endif

typedef enum
{
    // unknown name type
    DS_UNKNOWN_NAME = 0,

    // eg: CN=Spencer Katt,OU=Users,DC=Engineering,DC=Widget,DC=Com
    DS_FQDN_1779_NAME = 1,

    // eg: Engineering\SpencerK
    // Domain-only version includes trailing '\\'.
    DS_NT4_ACCOUNT_NAME = 2,

    // Probably "Spencer Katt" but could be something else.  I.e. The
    // display name is not necessarily the defining RDN.
    DS_DISPLAY_NAME = 3,

    // obsolete - see #define later
    // DS_DOMAIN_SIMPLE_NAME = 4,

    // obsolete - see #define later
    // DS_ENTERPRISE_SIMPLE_NAME = 5,

    // String-ized GUID as returned by IIDFromString().
    // eg: {4fa050f0-f561-11cf-bdd9-00aa003a77b6}
    DS_UNIQUE_ID_NAME = 6,

    // eg: engineering.widget.com/software/spencer katt
    // Domain-only version includes trailing '/'.
    DS_CANONICAL_NAME = 7,

    // eg: spencerk@engineering.widget.com
    DS_USER_PRINCIPAL_NAME = 8,

    // Same as DS_CANONICAL_NAME except that rightmost '/' is
    // replaced with '\n' - even in domain-only case.
    // eg: engineering.widget.com/software\nspencer katt
    DS_CANONICAL_NAME_EX = 9,

    // eg: www/www.widget.com@widget.com - generalized service principal
    // names.
    DS_SERVICE_PRINCIPAL_NAME = 10

} DS_NAME_FORMAT;

// Map old name formats to closest new format so that old code builds
// against new headers w/o errors and still gets (almost) correct result.

#define DS_DOMAIN_SIMPLE_NAME       DS_USER_PRINCIPAL_NAME
#define DS_ENTERPRISE_SIMPLE_NAME   DS_USER_PRINCIPAL_NAME

typedef enum
{
    DS_NAME_NO_FLAGS = 0x0,

    // Perform a syntactical mapping at the client (if possible) without
    // going out on the wire.  Returns DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING
    // if a purely syntactical mapping is not possible.
    DS_NAME_FLAG_SYNTACTICAL_ONLY = 0x1

} DS_NAME_FLAGS;

typedef enum
{
    DS_NAME_NO_ERROR = 0,

    // Generic processing error.
    DS_NAME_ERROR_RESOLVING = 1,

    // Couldn't find the name at all - or perhaps caller doesn't have
    // rights to see it.
    DS_NAME_ERROR_NOT_FOUND = 2,

    // Input name mapped to more than one output name.
    DS_NAME_ERROR_NOT_UNIQUE = 3,

    // Input name found, but not the associated output format.
    // Can happen if object doesn't have all the required attributes.
    DS_NAME_ERROR_NO_MAPPING = 4,

    // Unable to resolve entire name, but was able to determine which
    // domain object resides in.  Thus DS_NAME_RESULT_ITEM?.pDomain
    // is valid on return.
    DS_NAME_ERROR_DOMAIN_ONLY = 5,

    // Unable to perform a purely syntactical mapping at the client
    // without going out on the wire.
    DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING = 6

} DS_NAME_ERROR;

#define DS_NAME_LEGAL_FLAGS (DS_NAME_FLAG_SYNTACTICAL_ONLY)

typedef enum {

    // "paulle-nec.ntwksta.ms.com"
    DS_SPN_DNS_HOST = 0,

    // "cn=paulle-nec,ou=computers,dc=ntwksta,dc=ms,dc=com"
    DS_SPN_DN_HOST = 1,

    // "paulle-nec"
    DS_SPN_NB_HOST = 2,

    // "ntdev.ms.com"
    DS_SPN_DOMAIN = 3,

    // "ntdev"
    DS_SPN_NB_DOMAIN = 4,

    // "cn=anRpcService,cn=RPC Services,cn=system,dc=ms,dc=com"
    // "cn=aWsService,cn=Winsock Services,cn=system,dc=ms,dc=com"
    // "cn=aService,dc=itg,dc=ms,dc=com"
    // "www.ms.com", "ftp.ms.com", "ldap.ms.com"
    // "products.ms.com"
    DS_SPN_SERVICE = 5

} DS_SPN_NAME_TYPE;

typedef enum {                          // example:
        DS_SPN_ADD_SPN_OP = 0,          // add SPNs
        DS_SPN_REPLACE_SPN_OP = 1,      // set all SPNs
        DS_SPN_DELETE_SPN_OP = 2        // Delete SPNs
} DS_SPN_WRITE_OP;

typedef struct
{
    DWORD                   status;     // DS_NAME_ERROR
#ifdef MIDL_PASS
    [string,unique] CHAR    *pDomain;   // DNS domain
    [string,unique] CHAR    *pName;     // name in requested format
#else
    LPSTR                   pDomain;    // DNS domain
    LPSTR                   pName;      // name in requested format
#endif

} DS_NAME_RESULT_ITEMA, *PDS_NAME_RESULT_ITEMA;

typedef struct
{
    DWORD                   cItems;     // item count
#ifdef MIDL_PASS
    [size_is(cItems)] PDS_NAME_RESULT_ITEMA rItems;
#else
    PDS_NAME_RESULT_ITEMA    rItems;    // item array
#endif

} DS_NAME_RESULTA, *PDS_NAME_RESULTA;

typedef struct
{
    DWORD                   status;     // DS_NAME_ERROR
#ifdef MIDL_PASS
    [string,unique] WCHAR   *pDomain;   // DNS domain
    [string,unique] WCHAR   *pName;     // name in requested format
#else
    LPWSTR                  pDomain;    // DNS domain
    LPWSTR                  pName;      // name in requested format
#endif

} DS_NAME_RESULT_ITEMW, *PDS_NAME_RESULT_ITEMW;

typedef struct
{
    DWORD                   cItems;     // item count
#ifdef MIDL_PASS
    [size_is(cItems)] PDS_NAME_RESULT_ITEMW rItems;
#else
    PDS_NAME_RESULT_ITEMW    rItems;    // item array
#endif

} DS_NAME_RESULTW, *PDS_NAME_RESULTW;

#ifdef UNICODE
#define DS_NAME_RESULT DS_NAME_RESULTW
#define PDS_NAME_RESULT PDS_NAME_RESULTW
#define DS_NAME_RESULT_ITEM DS_NAME_RESULT_ITEMW
#define PDS_NAME_RESULT_ITEM PDS_NAME_RESULT_ITEMW
#else
#define DS_NAME_RESULT DS_NAME_RESULTA
#define PDS_NAME_RESULT PDS_NAME_RESULTA
#define DS_NAME_RESULT_ITEM DS_NAME_RESULT_ITEMA
#define PDS_NAME_RESULT_ITEM PDS_NAME_RESULT_ITEMA
#endif

// Public replication option flags

// ********************
// Replica Sync flags
// ********************

// Perform this operation asynchronously.
// Required when using DS_REPSYNC_ALL_SOURCES
#define DS_REPSYNC_ASYNCHRONOUS_OPERATION 0x00000001

// Writeable replica.  Otherwise, read-only.
#define DS_REPSYNC_WRITEABLE              0x00000002

// This is a periodic sync request as scheduled by the admin.
#define DS_REPSYNC_PERIODIC               0x00000004

// Use inter-site messaging
#define DS_REPSYNC_INTERSITE_MESSAGING    0x00000008

// Sync from all sources.
#define DS_REPSYNC_ALL_SOURCES            0x00000010

// Sync starting from scratch (i.e., at the first USN).
#define DS_REPSYNC_FULL                   0x00000020

// This is a notification of an update that was marked urgent.
#define DS_REPSYNC_URGENT                 0x00000040

// Don't discard this synchronization request, even if a similar
// sync is pending.
#define DS_REPSYNC_NO_DISCARD             0x00000080

// Sync even if link is currently disabled.
#define DS_REPSYNC_FORCE                  0x00000100




// ********************
// Replica Add flags
// ********************

// Perform this operation asynchronously.
#define DS_REPADD_ASYNCHRONOUS_OPERATION 0x00000001

// Create a writeable replica.  Otherwise, read-only.
#define DS_REPADD_WRITEABLE               0x00000002

// Sync the NC from this source when the DSA is started.
#define DS_REPADD_INITIAL                 0x00000004

// Sync the NC from this source periodically, as defined by the
// schedule passed in the preptimesSync argument.
#define DS_REPADD_PERIODIC                0x00000008

// Sync from the source DSA via an Intersite Messaging Service (ISM) transport
// (e.g., SMTP) rather than native DS RPC.
#define DS_REPADD_INTERSITE_MESSAGING     0x00000010

// Don't replicate the NC now -- just save enough state such that we
// know to replicate it later.
#define DS_REPADD_ASYNCHRONOUS_REPLICA     0x00000020

// Disable notification-based synchronization for the NC from this source.
// This is expected to be a temporary state; the similar flag
// DS_REPADD_NEVER_NOTIFY should be used if the disable is to be more permanent.
#define DS_REPADD_DISABLE_NOTIFICATION     0x00000040

// Disable periodic synchronization for the NC from this source
#define DS_REPADD_DISABLE_PERIODIC         0x00000080

// Use compression when replicating.  Saves message size (e.g., network
// bandwidth) at the expense of extra CPU overhead at both the source and
// destination servers.
#define DS_REPADD_USE_COMPRESSION          0x00000100

// Do not request change notifications from this source.  When this flag is
// set, the source will not notify the destination when changes occur.
// Recommended for all intersite replication, which may occur over WAN links.
// This is expected to be a more or less permanent state; the similar flag
// DS_REPADD_DISABLE_NOTIFICATION should be used if notifications are to be
// disabled only temporarily.
#define DS_REPADD_NEVER_NOTIFY             0x00000200



// ********************
// Replica Delete flags
// ********************

// Perform this operation asynchronously.
#define DS_REPDEL_ASYNCHRONOUS_OPERATION 0x00000001

// The replica being deleted is writeable.
#define DS_REPDEL_WRITEABLE               0x00000002

// Replica is a mail-based replica
#define DS_REPDEL_INTERSITE_MESSAGING     0x00000004

// Ignore any error generated by contacting the source to tell it to scratch
// this server from its Reps-To for this NC.
#define DS_REPDEL_IGNORE_ERRORS           0x00000008

// Do not contact the source telling it to scratch this server from its
// Rep-To for this NC.  Otherwise, if the link is RPC-based, the source will
// be contacted.
#define DS_REPDEL_LOCAL_ONLY              0x00000010

// Delete all the objects in the NC
// "No source" is incompatible with (and rejected for) writeable NCs.  This is
// valid only for read-only NCs, and then only if the NC has no source.  This
// can occur when the NC has been partially deleted (in which case the KCC
// periodically calls the delete API with the "no source" flag set).
#define DS_REPDEL_NO_SOURCE               0x00000020

// Allow deletion of read-only replica even if it sources
// other read-only replicas.
#define DS_REPDEL_REF_OK                  0x00000040

// ********************
// Replica Modify flags
// ********************

// Perform this operation asynchronously.
#define DS_REPMOD_ASYNCHRONOUS_OPERATION  0x00000001

// The replica is writeable.
#define DS_REPMOD_WRITEABLE               0x00000002


// ********************
// Replica Modify fields
// ********************

#define DS_REPMOD_UPDATE_FLAGS             0x00000001
#define DS_REPMOD_UPDATE_ADDRESS           0x00000002
#define DS_REPMOD_UPDATE_SCHEDULE          0x00000004
#define DS_REPMOD_UPDATE_RESULT            0x00000008
#define DS_REPMOD_UPDATE_TRANSPORT         0x00000010

// ********************
// Update Refs fields
// ********************

// Perform this operation asynchronously.
#define DS_REPUPD_ASYNCHRONOUS_OPERATION  0x00000001

// The replica being deleted is writeable.
#define DS_REPUPD_WRITEABLE               0x00000002

// Add a reference
#define DS_REPUPD_ADD_REFERENCE           0x00000004

// Remove a reference
#define DS_REPUPD_DELETE_REFERENCE        0x00000008



//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Prototypes                                                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// DSBind takes two optional input parameters which identify whether the
// caller found a domain controller themselves via DsGetDcName or whether
// a domain controller should be found using default parameters.
// Behavior of the possible combinations are outlined below.
//
// DomainControllerAddress(value), DnsDomainName(NULL)
//
//      The value for DomainControllerAddress is assumed to have been
//      obtained via DsGetDcName (i.e. Field with the same name in a
//      DOMAIN_CONTROLLER_INFO struct on return from DsGetDcName call.)
//      The client is bound to the domain controller at this address.
//
// DomainControllerAddress(value), DnsDomainName(value)
//
//      Illegal combination - call is failed.
//
// DomainControllerAddress(NULL), DnsDomainName(NULL)
//
//      DsBind will attempt to find to a global catalog and fail if one
//      can not be found.
//
// DomainControllerAddress(NULL), DnsDomainName(value)
//
//      DsBind will attempt to find a domain controller for the domain
//      identified by DnsDomainName and fail if one can not be found.

#define NEW_DSBIND_SEMANTICS 1

NTDSAPI
DWORD
WINAPI
DsBindW(
    WCHAR           *DomainControllerAddress,   // in, optional
    WCHAR           *DnsDomainName,             // in, optional
    HANDLE          *phDS);

NTDSAPI
DWORD
WINAPI
DsBindA(
    CHAR            *DomainControllerAddress,   // in, optional
    CHAR            *DnsDomainName,             // in, optional
    HANDLE          *phDS);

#ifdef UNICODE
#define DsBind DsBindW
#else
#define DsBind DsBindA
#endif

NTDSAPI
DWORD
WINAPI
DsBindWithCredW(
    WCHAR           *DomainControllerAddress,   // in, optional
    WCHAR           *DnsDomainName,             // in, optional
    RPC_AUTH_IDENTITY_HANDLE AuthIdentity,     // in, optional
    HANDLE          *phDS);

NTDSAPI
DWORD
WINAPI
DsBindWithCredA(
    CHAR            *DomainControllerAddress,   // in, optional
    CHAR            *DnsDomainName,             // in, optional
    RPC_AUTH_IDENTITY_HANDLE AuthIdentity,     // in, optional
    HANDLE          *phDS);

#ifdef UNICODE
#define DsBindWithCred DsBindWithCredW
#else
#define DsBindWithCred DsBindWithCredA
#endif

//
// DsUnBind
//

NTDSAPI
DWORD
WINAPI
DsUnBindW(
    HANDLE          *phDS);             // in

NTDSAPI
DWORD
WINAPI
DsUnBindA(
    HANDLE          *phDS);             // in

#ifdef UNICODE
#define DsUnBind DsUnBindW
#else
#define DsUnBind DsUnBindA
#endif

//
// DsMakePasswordCredentials
//
// This function constructs a credential structure which is suitable for input
// to the DsBindWithCredentials function, or the ldap_open function (winldap.h)
// The credential must be freed using DsFreeCredential.
//
// None of the input parameters may be present indicating a null, default
// credential.  Otherwise the username must be present.  If the domain or
// password are null, they default to empty strings.  The domain name may be
// null when the username is fully qualified, for example UPN format.
//

NTDSAPI
DWORD
WINAPI
DsMakePasswordCredentialsW(
    LPWSTR User,
    LPWSTR Domain,
    LPWSTR Password,
    RPC_AUTH_IDENTITY_HANDLE *pAuthIdentity
    );

NTDSAPI
DWORD
WINAPI
DsMakePasswordCredentialsA(
    LPSTR User,
    LPSTR Domain,
    LPSTR Password,
    RPC_AUTH_IDENTITY_HANDLE *pAuthIdentity
    );

#ifdef UNICODE
#define DsMakePasswordCredentials DsMakePasswordCredentialsW
#else
#define DsMakePasswordCredentials DsMakePasswordCredentialsA
#endif

NTDSAPI
VOID
WINAPI
DsFreePasswordCredentials(
    RPC_AUTH_IDENTITY_HANDLE AuthIdentity
    );

#define DsFreePasswordCredentialsW DsFreePasswordCredentials
#define DsFreePasswordCredentialsA DsFreePasswordCredentials

//
// DsCrackNames
//

NTDSAPI
DWORD
WINAPI
DsCrackNamesW(
    HANDLE              hDS,                // in
    DS_NAME_FLAGS       flags,              // in
    DS_NAME_FORMAT      formatOffered,      // in
    DS_NAME_FORMAT      formatDesired,      // in
    DWORD               cNames,             // in
    LPWSTR              *rpNames,           // in
    PDS_NAME_RESULTW    *ppResult);         // out

NTDSAPI
DWORD
WINAPI
DsCrackNamesA(
    HANDLE              hDS,                // in
    DS_NAME_FLAGS       flags,              // in
    DS_NAME_FORMAT      formatOffered,      // in
    DS_NAME_FORMAT      formatDesired,      // in
    DWORD               cNames,             // in
    LPSTR               *rpNames,           // in
    PDS_NAME_RESULTA    *ppResult);         // out

#ifdef UNICODE
#define DsCrackNames DsCrackNamesW
#else
#define DsCrackNames DsCrackNamesA
#endif

//
// DsFreeNameResult
//

NTDSAPI
void
WINAPI
DsFreeNameResultW(
    DS_NAME_RESULTW *pResult);          // in

NTDSAPI
void
WINAPI
DsFreeNameResultA(
    DS_NAME_RESULTA *pResult);          // in

#ifdef UNICODE
#define DsFreeNameResult DsFreeNameResultW
#else
#define DsFreeNameResult DsFreeNameResultA
#endif

// ==========================================================
// DSMakeSpn -- client call to create SPN for a service to which it wants to
// authenticate.
// This name is then passed to "pszTargetName" of InitializeSecurityContext().
//
// Notes:
// If the service name is a DNS host name, or canonical DNS service name
// e.g. "www.ms.com", i.e., caller resolved with gethostbyname, then instance
// name should be NULL.
// Realm is host name minus first component, unless it is in the exception list
//
// If the service name is NetBIOS machine name, then instance name should be
// NULL
// Form must be <domain>\<machine>
// Realm will be <domain>
//
// If the service name is that of a replicated service, where each replica has
// its own account (e.g., with SRV records) then the caller must supply the
// instance name then realm name is same as ServiceName
//
// If the service name is a DN, then must also supply instance name
// (DN could be name of service object (incl RPC or Winsock), name of machine
// account, name of domain object)
// then realm name is domain part of the DN
//
// If the service name is NetBIOS domain name, then must also supply instance
// name; realm name is domain name
//
// If the service is named by an IP address -- then use referring service name
// as service name
//
//  ServiceClass - e.g. "http", "ftp", "ldap", GUID
//  ServiceName - DNS or DN; assumes we can compute domain from service name
//  InstanceName OPTIONAL- DNS name of host for instance of service
//  InstancePort - port number for instance (0 if default)
//  Referrer OPTIONAL- DNS name of host that gave this referral
//  pcSpnLength - in -- max length IN CHARACTERS of principal name;
//                out -- actual
//                Length includes terminator
//  pszSPN - server principal name
//
// If buffer is not large enough, ERROR_BUFFER_OVERFLOW is returned and the
// needed length is returned in pcSpnLength.
//
//

NTDSAPI
DWORD
WINAPI
DsMakeSpnW(
    LPWSTR ServiceClass,
    LPWSTR ServiceName,
    LPWSTR InstanceName,
    USHORT InstancePort,
    LPWSTR Referrer,
    DWORD *pcSpnLength,
    LPWSTR pszSpn
);

NTDSAPI
DWORD
WINAPI
DsMakeSpnA(
    LPSTR ServiceClass,
    LPSTR ServiceName,
    LPSTR InstanceName,
    USHORT InstancePort,
    LPSTR Referrer,
    DWORD *pcSpnLength,
    LPSTR pszSpn
);

#ifdef UNICODE
#define DsMakeSpn DsMakeSpnW
#else
#define DsMakeSpn DsMakeSpnA
#endif

// ==========================================================
// DsGetSPN -- server's call to gets SPNs for a service name by which it is
// known to clients. N.B.: there may be more than one name by which clients
// know it the SPNs are then passed to DsAddAccountSpn to register them in
// the DS
//
//      IN SpnNameType eType,
//      IN LPCTSTR ServiceClass,
// kind of service -- "http", "ldap", "ftp", etc.
//      IN LPCTSTR ServiceName OPTIONAL,
// name of service -- DN or DNS; not needed for host-based
//      IN USHORT InstancePort,
// port number (0 => default) for instances
//      IN USHORT cInstanceNames,
// count of extra instance names and ports (0=>use gethostbyname)
//      IN LPCTSTR InstanceNames[] OPTIONAL,
// extra instance names (not used for host names)
//      IN USHORT InstancePorts[] OPTIONAL,
// extra instance ports (0 => default)
//      IN OUT PULONG pcSpn,    // count of SPNs
//      IN OUT LPTSTR * prpszSPN[]
// a bunch of SPNs for this service; free with DsFreeSpnArray

NTDSAPI
DWORD
WINAPI
DsGetSpnA(
    DS_SPN_NAME_TYPE ServiceType,
    LPSTR ServiceClass,
    LPSTR ServiceName,
    USHORT InstancePort,
    USHORT cInstanceNames,
    LPSTR *pInstanceNames,
    USHORT *pInstancePorts,
    DWORD *pcSpn,
    LPSTR **prpszSpn
    );

NTDSAPI
DWORD
WINAPI
DsGetSpnW(
    DS_SPN_NAME_TYPE ServiceType,
    LPWSTR ServiceClass,
    LPWSTR ServiceName,
    USHORT InstancePort,
    USHORT cInstanceNames,
    LPWSTR *pInstanceNames,
    USHORT *pInstancePorts,
    DWORD *pcSpn,
    LPWSTR **prpszSpn
    );

#ifdef UNICODE
#define DsGetSpn DsGetSpnW
#else
#define DsGetSpn DsGetSpnA
#endif

// ==========================================================
// DsFreeSpnArray() -- Free array returned by DsGetSpn{A,W}

NTDSAPI
void
WINAPI
DsFreeSpnArrayA(
    DWORD cSpn,
    LPSTR *rpszSpn
    );

NTDSAPI
void
WINAPI
DsFreeSpnArrayW(
    DWORD cSpn,
    LPWSTR *rpszSpn
    );

#ifdef UNICODE
#define DsFreeSpnArray DsFreeSpnArrayW
#else
#define DsFreeSpnArray DsFreeSpnArrayA
#endif

// ==========================================================
// DsCrackSpn() -- parse an SPN into the ServiceClass,
// ServiceName, and InstanceName (and InstancePort) pieces.
// An SPN is passed in, along with a pointer to the maximum length
// for each piece and a pointer to a buffer where each piece should go.
// On exit, the maximum lengths are updated to the actual length for each piece
// and the buffer contain the appropriate piece. The InstancePort is 0 if not
// present.
//
// DWORD DsCrackSpn(
//      IN LPTSTR pszSPN,               // the SPN to parse
//      IN OUT PUSHORT pcServiceClass,  // input -- max length of ServiceClass;
//                                         output -- actual length
//      OUT LPCTSTR ServiceClass,       // the ServiceClass part of the SPN
//      IN OUT PUSHORT pcServiceName,   // input -- max length of ServiceName;
//                                         output -- actual length
//      OUT LPCTSTR ServiceName,        // the ServiceName part of the SPN
//      IN OUT PUSHORT pcInstance,      // input -- max length of ServiceClass;
//                                         output -- actual length
//      OUT LPCTSTR InstanceName,  // the InstanceName part of the SPN
//      OUT PUSHORT InstancePort          // instance port
//
// Note: lengths are in characters; all string lengths include terminators
// All arguments except pszSpn are optional.
//

NTDSAPI
DWORD
WINAPI
DsCrackSpnA(
    LPSTR pszSpn,
    DWORD *pcServiceClass,
    LPSTR ServiceClass,
    DWORD *pcServiceName,
    LPSTR ServiceName,
    DWORD *pcInstanceName,
    LPSTR InstanceName,
    USHORT *pInstancePort
    );

NTDSAPI
DWORD
WINAPI
DsCrackSpnW(
    LPWSTR pszSpn,
    DWORD *pcServiceClass,
    LPWSTR ServiceClass,
    DWORD *pcServiceName,
    LPWSTR ServiceName,
    DWORD *pcInstanceName,
    LPWSTR InstanceName,
    USHORT *pInstancePort
    );

#ifdef UNICODE
#define DsCrackSpn DsCrackSpnW
#else
#define DsCrackSpn DsCrackSpnA
#endif


// ==========================================================
// DsWriteAccountSpn -- set or add SPNs for an account object
// Usually done by service itself, or perhaps by an admin.
//
// This call is RPC'd to the DC where the account object is stored, so it can
// securely enforce policy on what SPNs are allowed on the account. Direct LDAP
// writes to the SPN property are not allowed -- all writes must come through
// this RPC call. (Reads via // LDAP are OK.)
//
// The account object can be a machine accout, or a service (user) account.
//
// If called by the service to register itself, it can most easily get
// the names by calling DsGetSpn with each of the names that
// clients can use to find the service.
//
// IN SpnWriteOp eOp,                   // set, add
// IN LPCTSTR   pszAccount,             // DN of account to which to add SPN
// IN int       cSPN,                   // count of SPNs to add to account
// IN LPCTSTR   rpszSPN[]               // SPNs to add to altSecID property

NTDSAPI
DWORD
WINAPI
DsWriteAccountSpnA(
    HANDLE hDS,
    DS_SPN_WRITE_OP Operation,
    LPSTR pszAccount,
    DWORD cSpn,
    LPSTR *rpszSpn
    );

NTDSAPI
DWORD
WINAPI
DsWriteAccountSpnW(
    HANDLE hDS,
    DS_SPN_WRITE_OP Operation,
    LPWSTR pszAccount,
    DWORD cSpn,
    LPWSTR *rpszSpn
    );

#ifdef UNICODE
#define DsWriteAccountSpn DsWriteAccountSpnW
#else
#define DsWriteAccountSpn DsWriteAccountSpnA
#endif

// I_DsMapDraErrorToWin32
// Convert internal DRA codes to Win32

NTDSAPI
DWORD
WINAPI
I_DsMapDraErrorToWin32(
    DWORD DraError
    );

// DsReplicaSync.  The server that this call is executing on is called the
// destination.  The destination's naming context will be brought up to date
// with respect to a source system.  The source system is identified by the
// uuid.  The uuid is that of the source system's "NTDS Settings" object.
// The destination system must already be configured such that the source
// system is one of the systems from which it recieves replication data
// ("replication from"). This is usually done automatically by the KCC.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC to synchronize.
//      puuidSourceDRA (SZ)
//          objectGuid of DSA with which to synchronize the replica.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more flags
//   RETURNS: WIN32 STATUS

NTDSAPI
DWORD
WINAPI
DsReplicaSyncA(
    HANDLE hDS,
    LPSTR NameContext,
    UUID *pUuidDsaSrc,
    ULONG Options
    );

NTDSAPI
DWORD
WINAPI
DsReplicaSyncW(
    HANDLE hDS,
    LPWSTR NameContext,
    UUID *pUuidDsaSrc,
    ULONG Options
    );

#ifdef UNICODE
#define DsReplicaSync DsReplicaSyncW
#else
#define DsReplicaSync DsReplicaSyncA
#endif

// DsReplicaAdd
//
/*
Description:
   This call is executed on the destination.  It causes the destination to
   add a "replication from" reference to the indicated source system.

The source server is identified by string name, not uuid as with Sync.
The DsaSrcAddress parameter is the transport specific address of the source
DSA, usually its guid-based dns name.  The guid in the guid-based dns name is
the object-guid of that server's ntds-dsa (settings) object.

Arguments:

    pNC (IN) - NC for which to add the replica.  The NC record must exist
        locally as either an object (instantiated or not) or a reference
        phantom (i.e., a phantom with a guid).

    pSourceDsaDN (IN) - DN of the source DSA's ntdsDsa object.  Required if
        ulOptions includes DS_REPADD_ASYNCHRONOUS_REPLICA; ignored otherwise.

    pTransportDN (IN) - DN of the interSiteTransport object representing the
        transport by which to communicate with the source server.  Required if
        ulOptions includes INTERSITE_MESSAGING; ignored otherwise.

    pszSourceDsaAddress (IN) - Transport-specific address of the source DSA.

    pSchedule (IN) - Schedule by which to replicate the NC from this
        source in the future.

    ulOptions (IN) - flags
    RETURNS: WIN32 STATUS
*/

NTDSAPI
DWORD
WINAPI
DsReplicaAddA(
    HANDLE hDS,
    LPSTR NameContext,
    LPSTR SourceDsaDn,
    LPSTR TransportDn,
    LPSTR SourceDsaAddress,
    PSCHEDULE pSchedule,
    DWORD Options
    );

NTDSAPI
DWORD
WINAPI
DsReplicaAddW(
    HANDLE hDS,
    LPWSTR NameContext,
    LPWSTR SourceDsaDn,
    LPWSTR TransportDn,
    LPWSTR SourceDsaAddress,
    PSCHEDULE pSchedule,
    DWORD Options
    );

#ifdef UNICODE
#define DsReplicaAdd DsReplicaAddW
#else
#define DsReplicaAdd DsReplicaAddA
#endif

// DsReplicaDel
//
// The server that this call is executing on is the destination.  The call
// causes the destination to remove a "replication from" reference to the
// indicated source server.
// The source server is identified by string name, not uuid as with Sync.
// The DsaSrc parameter is the transport specific address of the source DSA,
// usually its guid-based dns name.  The guid in the guid-based dns name is
// the object-guid of that server's ntds-dsa (settings) object.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which to delete a source.
//      pszSourceDRA (SZ)
//          DSA for which to delete the source.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more flags
//   RETURNS: WIN32 STATUS

NTDSAPI
DWORD
WINAPI
DsReplicaDelA(
    HANDLE hDS,
    LPSTR NameContext,
    LPSTR DsaSrc,
    ULONG Options
    );

NTDSAPI
DWORD
WINAPI
DsReplicaDelW(
    HANDLE hDS,
    LPWSTR NameContext,
    LPWSTR DsaSrc,
    ULONG Options
    );

#ifdef UNICODE
#define DsReplicaDel DsReplicaDelW
#else
#define DsReplicaDel DsReplicaDelA
#endif

// DsReplicaModify
//
//
//  Modify a source for a given naming context
//
//  The value must already exist.
//
//  Either the UUID or the address may be used to identify the current value.
//  If a UUID is specified, the UUID will be used for comparison.  Otherwise,
//  the address will be used for comparison.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which the Reps-From should be modified.
//      puuidSourceDRA (UUID *)
//          Invocation-ID of the referenced DRA.  May be NULL if:
//            . ulModifyFields does not include DS_REPMOD_UPDATE_ADDRESS and
//            . pmtxSourceDRA is non-NULL.
//      puuidTransportObj (UUID *)
//          objectGuid of the transport by which replication is to be performed
//          Ignored if ulModifyFields does not include
//          DS_REPMOD_UPDATE_TRANSPORT.
//      pszSourceDRA (SZ)
//          DSA for which the reference should be added or deleted.  Ignored if
//          puuidSourceDRA is non-NULL and ulModifyFields does not include
//          DS_REPMOD_UPDATE_ADDRESS.
//      prtSchedule (REPLTIMES *)
//          Periodic replication schedule for this replica.  Ignored if
//          ulModifyFields does not include DS_REPMOD_UPDATE_SCHEDULE.
//      ulReplicaFlags (ULONG)
//          Flags to set for this replica.  Ignored if ulModifyFields does not
//          include DS_REPMOD_UPDATE_FLAGS.
//      ulModifyFields (ULONG)
//          Fields to update.  One or more of the following bit flags:
//              UPDATE_ADDRESS
//                  Update the MTX_ADDR associated with the referenced server.
//              UPDATE_SCHEDULE
//                  Update the periodic replication schedule associated with
//                  the replica.
//              UPDATE_FLAGS
//                  Update the flags associated with the replica.
//              UPDATE_TRANSPORT
//                  Update the transport associated with the replica.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more of the following:
//              DS_REPMOD_ASYNCHRONOUS_OPERATION
//                  Perform this operation asynchronously.
//   RETURNS: WIN32 STATUS

NTDSAPI
DWORD
WINAPI
DsReplicaModifyA(
    HANDLE hDS,
    LPSTR NameContext,
    UUID *pUuidSourceDsa,
    LPSTR TransportDn,
    LPSTR SourceDsaAddress,
    PSCHEDULE pSchedule,
    DWORD ReplicaFlags,
    DWORD ModifyFields,
    DWORD Options
    );

NTDSAPI
DWORD
WINAPI
DsReplicaModifyW(
    HANDLE hDS,
    LPWSTR NameContext,
    UUID *pUuidSourceDsa,
    LPWSTR TransportDn,
    LPWSTR SourceDsaAddress,
    PSCHEDULE pSchedule,
    DWORD ReplicaFlags,
    DWORD ModifyFields,
    DWORD Options
    );

#ifdef UNICODE
#define DsReplicaModify DsReplicaModifyW
#else
#define DsReplicaModify DsReplicaModifyA
#endif

// DsReplicaUpdateRefs
//
// In this case, the RPC is being executed on the "source" of destination-sourc
// replication relationship.  This function tells the source that it no longer
// supplies replication information to the indicated destination system.
// Add or remove a target server from the Reps-To property on the given NC.
// Add/remove a reference given the DSNAME of the corresponding NTDS-DSA
// object.
//
//  PARAMETERS:
//      pNC (DSNAME *)
//          Name of the NC for which the Reps-To should be modified.
//      DsaDest (SZ)
//          Network address of DSA for which the reference should be added
//          or deleted.
//      pUuidDsaDest (UUID *)
//          Invocation-ID of DSA for which the reference should be added
//          or deleted.
//      ulOptions (ULONG)
//          Bitwise OR of zero or more of the following:
//              DS_REPUPD_ASYNC_OP
//                  Perform this operation asynchronously.
//              DS_REPUPD_ADD_REFERENCE
//                  Add the given server to the Reps-To property.
//              DS_REPUPD_DEL_REFERENCE
//                  Remove the given server from the Reps-To property.
//          Note that ADD_REF and DEL_REF may be paired to perform
//          "add or update".
//
//   RETURNS: WIN32 STATUS

NTDSAPI
DWORD
WINAPI
DsReplicaUpdateRefsA(
    HANDLE hDS,
    LPSTR NameContext,
    LPSTR DsaDest,
    UUID *pUuidDsaDest,
    ULONG Options
    );

NTDSAPI
DWORD
WINAPI
DsReplicaUpdateRefsW(
    HANDLE hDS,
    LPWSTR NameContext,
    LPWSTR DsaDest,
    UUID *pUuidDsaDest,
    ULONG Options
    );

#ifdef UNICODE
#define DsReplicaUpdateRefs DsReplicaUpdateRefsW
#else
#define DsReplicaUpdateRefs DsReplicaUpdateRefsA
#endif

NTDSAPI
DWORD
WINAPI
DsRemoveDsServerW(
    HANDLE  hDs,             // in
    LPWSTR  ServerDN,        // in
    LPWSTR  DomainDN,        // in,  optional
    BOOL   *fLastDcInDomain, // out, optional
    BOOL    fCommit          // in
    );

NTDSAPI
DWORD
WINAPI
DsRemoveDsServerA(
    HANDLE  hDs,              // in
    LPSTR   ServerDN,         // in
    LPSTR   DomainDN,         // in,  optional
    BOOL   *fLastDcInDomain,  // out, optional
    BOOL    fCommit           // in
    );

#ifdef UNICODE
#define DsRemoveDsServer DsRemoveDsServerW
#else
#define DsRemoveDsServer DsRemoveDsServerA
#endif

NTDSAPI
DWORD
WINAPI
DsRemoveDsDomainW(
    HANDLE  hDs,               // in
    LPWSTR  DomainDN           // in
    );

NTDSAPI
DWORD
WINAPI
DsRemoveDsDomainA(
    HANDLE  hDs,               // in
    LPSTR   DomainDN           // in
    );

#ifdef UNICODE
#define DsRemoveDsDomain DsRemoveDsDomainW
#else
#define DsRemoveDsDomain DsRemoveDsDomainA
#endif

NTDSAPI
DWORD
WINAPI
DsListSitesA(
    HANDLE              hDs,            // in
    PDS_NAME_RESULTA    *ppSites);      // out

NTDSAPI
DWORD
WINAPI
DsListSitesW(
    HANDLE              hDs,            // in
    PDS_NAME_RESULTW    *ppSites);      // out

#ifdef UNICODE
#define DsListSites DsListSitesW
#else
#define DsListSites DsListSitesA
#endif

NTDSAPI
DWORD
WINAPI
DsListServersInSiteA(
    HANDLE              hDs,            // in
    LPSTR               site,           // in
    PDS_NAME_RESULTA    *ppServers);    // out

NTDSAPI
DWORD
WINAPI
DsListServersInSiteW(
    HANDLE              hDs,            // in
    LPWSTR              site,           // in
    PDS_NAME_RESULTW    *ppServers);    // out

#ifdef UNICODE
#define DsListServersInSite DsListServersInSiteW
#else
#define DsListServersInSite DsListServersInSiteW
#endif

NTDSAPI
DWORD
WINAPI
DsListDomainsInSiteA(
    HANDLE              hDs,            // in
    LPSTR               site,           // in
    PDS_NAME_RESULTA    *ppDomains);    // out

NTDSAPI
DWORD
WINAPI
DsListDomainsInSiteW(
    HANDLE              hDs,            // in
    LPWSTR              site,           // in
    PDS_NAME_RESULTW    *ppDomains);    // out

#ifdef UNICODE
#define DsListDomainsInSite DsListDomainsInSiteW
#else
#define DsListDomainsInSite DsListDomainsInSiteA
#endif

NTDSAPI
DWORD
WINAPI
DsListServersForDomainInSiteA(
    HANDLE              hDs,            // in
    LPSTR               domain,         // in
    LPSTR               site,           // in
    PDS_NAME_RESULTA    *ppServers);    // out

NTDSAPI
DWORD
WINAPI
DsListServersForDomainInSiteW(
    HANDLE              hDs,            // in
    LPWSTR              domain,         // in
    LPWSTR              site,           // in
    PDS_NAME_RESULTW    *ppServers);    // out

#ifdef UNICODE
#define DsListServersForDomainInSite DsListServersForDomainInSiteW
#else
#define DsListServersForDomainInSite DsListServersForDomainInSiteA
#endif

// Define indices for DsListInfoForServer return data.  Check status
// for each field as a given value may not be present.

#define DS_LIST_DSA_OBJECT_FOR_SERVER       0
#define DS_LIST_DNS_HOST_NAME_FOR_SERVER    1
#define DS_LIST_ACCOUNT_OBJECT_FOR_SERVER   2

NTDSAPI
DWORD
WINAPI
DsListInfoForServerA(
    HANDLE              hDs,            // in
    LPSTR               server,         // in
    PDS_NAME_RESULTA    *ppInfo);       // out

NTDSAPI
DWORD
WINAPI
DsListInfoForServerW(
    HANDLE              hDs,            // in
    LPWSTR              server,         // in
    PDS_NAME_RESULTW    *ppInfo);       // out

#ifdef UNICODE
#define DsListInfoForServer DsListInfoForServerW
#else
#define DsListInfoForServer DsListInfoForServerA
#endif

// Define indices for DsListRoles return data.  Check status for
// each field as a given value may not be present.

#define DS_ROLE_SCHEMA_OWNER                0
#define DS_ROLE_DOMAIN_OWNER                1
#define DS_ROLE_PDC_OWNER                   2
#define DS_ROLE_RID_OWNER                   3

NTDSAPI
DWORD
WINAPI
DsListRolesA(
    HANDLE              hDs,            // in
    PDS_NAME_RESULTA    *ppRoles);      // out

NTDSAPI
DWORD
WINAPI
DsListRolesW(
    HANDLE              hDs,            // in
    PDS_NAME_RESULTW    *ppRoles);      // out

#ifdef UNICODE
#define DsListRoles DsListRolesW
#else
#define DsListRoles DsListRolesA
#endif

// Definitions required for DsMapSchemaGuid routines.

#define DS_SCHEMA_GUID_NOT_FOUND            0
#define DS_SCHEMA_GUID_ATTR                 1
#define DS_SCHEMA_GUID_ATTR_SET             2
#define DS_SCHEMA_GUID_CLASS                3
#define DS_SCHEMA_GUID_CONTROL_RIGHT        4

typedef struct
{
    GUID                    guid;       // mapped GUID
    DWORD                   guidType;   // DS_SCHEMA_GUID_* value
#ifdef MIDL_PASS
    [string,unique] CHAR    *pName;     // might be NULL
#else
    LPSTR                   pName;      // might be NULL
#endif

} DS_SCHEMA_GUID_MAPA, *PDS_SCHEMA_GUID_MAPA;

typedef struct
{
    GUID                    guid;       // mapped GUID
    DWORD                   guidType;   // DS_SCHEMA_GUID_* value
#ifdef MIDL_PASS
    [string,unique] WCHAR   *pName;     // might be NULL
#else
    LPWSTR                  pName;      // might be NULL
#endif

} DS_SCHEMA_GUID_MAPW, *PDS_SCHEMA_GUID_MAPW;

NTDSAPI
DWORD
WINAPI
DsMapSchemaGuidsA(
    HANDLE                  hDs,            // in
    DWORD                   cGuids,         // in
    GUID                    *rGuids,        // in
    DS_SCHEMA_GUID_MAPA     **ppGuidMap);   // out

NTDSAPI
VOID
WINAPI
DsFreeSchemaGuidMapA(
    PDS_SCHEMA_GUID_MAPA    pGuidMap);      // in

NTDSAPI
DWORD
WINAPI
DsMapSchemaGuidsW(
    HANDLE                  hDs,            // in
    DWORD                   cGuids,         // in
    GUID                    *rGuids,        // in
    DS_SCHEMA_GUID_MAPW     **ppGuidMap);   // out
    
NTDSAPI
VOID
WINAPI
DsFreeSchemaGuidMapW(
    PDS_SCHEMA_GUID_MAPW    pGuidMap);      // in

#ifdef UNICODE
#define DS_SCHEMA_GUID_MAP DS_SCHEMA_GUID_MAPW
#define PDS_SCHEMA_GUID_MAP PDS_SCHEMA_GUID_MAPW
#define DsMapSchemaGuids DsMapSchemaGuidsW
#define DsFreeSchemaGuidMap DsFreeSchemaGuidMapW
#else
#define DS_SCHEMA_GUID_MAP DS_SCHEMA_GUID_MAPA
#define PDS_SCHEMA_GUID_MAP PDS_SCHEMA_GUID_MAPA
#define DsMapSchemaGuids DsMapSchemaGuidsA
#define DsFreeSchemaGuidMap DsFreeSchemaGuidMapA
#endif

typedef struct
{
#ifdef MIDL_PASS
    [string,unique] CHAR    *NetbiosName;           // might be NULL
    [string,unique] CHAR    *DnsHostName;           // might be NULL
    [string,unique] CHAR    *SiteName;              // might be NULL
    [string,unique] CHAR    *ComputerObjectName;    // might be NULL
    [string,unique] CHAR    *ServerObjectName;      // might be NULL
#else
    LPSTR                   NetbiosName;            // might be NULL
    LPSTR                   DnsHostName;            // might be NULL
    LPSTR                   SiteName;               // might be NULL
    LPSTR                   ComputerObjectName;     // might be NULL
    LPSTR                   ServerObjectName;       // might be NULL
#endif
    BOOL                    fIsPdc;
    BOOL                    fDsEnabled;

} DS_DOMAIN_CONTROLLER_INFO_1A, *PDS_DOMAIN_CONTROLLER_INFO_1A;

typedef struct
{
#ifdef MIDL_PASS
    [string,unique] WCHAR   *NetbiosName;           // might be NULL
    [string,unique] WCHAR   *DnsHostName;           // might be NULL
    [string,unique] WCHAR   *SiteName;              // might be NULL
    [string,unique] WCHAR   *ComputerObjectName;    // might be NULL
    [string,unique] WCHAR   *ServerObjectName;      // might be NULL
#else
    LPWSTR                  NetbiosName;            // might be NULL
    LPWSTR                  DnsHostName;            // might be NULL
    LPWSTR                  SiteName;               // might be NULL
    LPWSTR                  ComputerObjectName;     // might be NULL
    LPWSTR                  ServerObjectName;       // might be NULL
#endif
    BOOL                    fIsPdc;
    BOOL                    fDsEnabled;

} DS_DOMAIN_CONTROLLER_INFO_1W, *PDS_DOMAIN_CONTROLLER_INFO_1W;

NTDSAPI
DWORD
WINAPI
DsGetDomainControllerInfoA(
    HANDLE                          hDs,            // in
    LPSTR                           DomainName,     // in
    DWORD                           InfoLevel,      // in
    DWORD                           *pcOut,         // out
    VOID                            **ppInfo);      // out

NTDSAPI
DWORD
WINAPI
DsGetDomainControllerInfoW(
    HANDLE                          hDs,            // in
    LPWSTR                          DomainName,     // in
    DWORD                           InfoLevel,      // in
    DWORD                           *pcOut,         // out
    VOID                            **ppInfo);      // out

NTDSAPI
VOID
WINAPI
DsFreeDomainControllerInfoA(
    DWORD                           InfoLevel,      // in 
    DWORD                           cInfo,          // in
    VOID                            *pInfo);        // in

NTDSAPI
VOID
WINAPI
DsFreeDomainControllerInfoW(
    DWORD                           InfoLevel,      // in 
    DWORD                           cInfo,          // in
    VOID                            *pInfo);        // in

#ifdef UNICODE
#define DS_DOMAIN_CONTROLLER_INFO_1 DS_DOMAIN_CONTROLLER_INFO_1W
#define PDS_DOMAIN_CONTROLLER_INFO_1 PDS_DOMAIN_CONTROLLER_INFO_1W
#define DsGetDomainControllerInfo DsGetDomainControllerInfoW
#define DsFreeDomainControllerInfo DsFreeDomainControllerInfoW
#else
#define DS_DOMAIN_CONTROLLER_INFO_1 DS_DOMAIN_CONTROLLER_INFO_1A
#define PDS_DOMAIN_CONTROLLER_INFO_1 PDS_DOMAIN_CONTROLLER_INFO_1A
#define DsGetDomainControllerInfo DsGetDomainControllerInfoA
#define DsFreeDomainControllerInfo DsFreeDomainControllerInfoA
#endif

#ifdef __cplusplus
}
#endif

#endif // _NTDSAPI_H_
