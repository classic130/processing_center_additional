/*++ BUILD Version: 0001    // Increment this if a change has global effects

Copyright (c) 1996-1998  Microsoft Corporation

Module Name:

    dsgetdc.h

Abstract:

    This file contains structures, function prototypes, and definitions
    for the DsGetDcName API.

Environment:

    User Mode - Win32

Notes:

--*/


#ifndef _DSGETDC_
#define _DSGETDC_

#if !defined(_DSGETDCAPI_)
#define DSGETDCAPI DECLSPEC_IMPORT
#else
#define DSGETDCAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
// Structure definitions
//

//
// Flags to passed to DsGetDcName
//

#define DS_FORCE_REDISCOVERY            0x00000001

#define DS_DIRECTORY_SERVICE_REQUIRED   0x00000010
#define DS_DIRECTORY_SERVICE_PREFERRED  0x00000020
#define DS_GC_SERVER_REQUIRED           0x00000040
#define DS_PDC_REQUIRED                 0x00000080
#define DS_IP_REQUIRED                  0x00000200
#define DS_KDC_REQUIRED                 0x00000400
#define DS_TIMESERV_REQUIRED            0x00000800
#define DS_WRITABLE_REQUIRED            0x00001000
#define DS_GOOD_TIMESERV_PREFERRED      0x00002000
#define DS_AVOID_SELF                   0x00004000


#define DS_IS_FLAT_NAME                 0x00010000
#define DS_IS_DNS_NAME                  0x00020000

#define DS_RETURN_DNS_NAME              0x40000000
#define DS_RETURN_FLAT_NAME             0x80000000

#define DSGETDC_VALID_FLAGS ( \
            DS_FORCE_REDISCOVERY | \
            DS_DIRECTORY_SERVICE_REQUIRED | \
            DS_DIRECTORY_SERVICE_PREFERRED | \
            DS_GC_SERVER_REQUIRED | \
            DS_PDC_REQUIRED | \
            DS_IP_REQUIRED | \
            DS_KDC_REQUIRED | \
            DS_TIMESERV_REQUIRED | \
            DS_WRITABLE_REQUIRED | \
            DS_GOOD_TIMESERV_PREFERRED | \
            DS_AVOID_SELF | \
            DS_IS_FLAT_NAME | \
            DS_IS_DNS_NAME | \
            DS_RETURN_FLAT_NAME  | \
            DS_RETURN_DNS_NAME )


//
// Structure returned from DsGetDcName
//

typedef struct _DOMAIN_CONTROLLER_INFOA {
    LPSTR DomainControllerName;
    LPSTR DomainControllerAddress;
    ULONG DomainControllerAddressType;
    GUID DomainGuid;
    LPSTR DomainName;
    LPSTR DnsForestName;
    ULONG Flags;
    LPSTR DcSiteName;
    LPSTR ClientSiteName;
} DOMAIN_CONTROLLER_INFOA, *PDOMAIN_CONTROLLER_INFOA;

typedef struct _DOMAIN_CONTROLLER_INFOW {
#ifdef MIDL_PASS
    [string,unique] wchar_t *DomainControllerName;
#else // MIDL_PASS
    LPWSTR DomainControllerName;
#endif // MIDL_PASS
#ifdef MIDL_PASS
    [string,unique] wchar_t *DomainControllerAddress;
#else // MIDL_PASS
    LPWSTR DomainControllerAddress;
#endif // MIDL_PASS
    ULONG DomainControllerAddressType;
    GUID DomainGuid;
#ifdef MIDL_PASS
    [string,unique] wchar_t *DomainName;
#else // MIDL_PASS
    LPWSTR DomainName;
#endif // MIDL_PASS
#ifdef MIDL_PASS
    [string,unique] wchar_t *DnsForestName;
#else // MIDL_PASS
    LPWSTR DnsForestName;
#endif // MIDL_PASS
    ULONG Flags;
#ifdef MIDL_PASS
    [string,unique] wchar_t *DcSiteName;
#else // MIDL_PASS
    LPWSTR DcSiteName;
#endif // MIDL_PASS
#ifdef MIDL_PASS
    [string,unique] wchar_t *ClientSiteName;
#else // MIDL_PASS
    LPWSTR ClientSiteName;
#endif // MIDL_PASS
} DOMAIN_CONTROLLER_INFOW, *PDOMAIN_CONTROLLER_INFOW;

#ifdef UNICODE
#define DOMAIN_CONTROLLER_INFO DOMAIN_CONTROLLER_INFOW
#define PDOMAIN_CONTROLLER_INFO PDOMAIN_CONTROLLER_INFOW
#else
#define DOMAIN_CONTROLLER_INFO DOMAIN_CONTROLLER_INFOA
#define PDOMAIN_CONTROLLER_INFO PDOMAIN_CONTROLLER_INFOA
#endif // !UNICODE

//
// Values for DomainControllerAddressType
//

#define DS_INET_ADDRESS    1
#define DS_NETBIOS_ADDRESS 2

//
// Values for returned Flags
//

#define DS_PDC_FLAG            0x00000001    // DC is PDC of Domain
#define DS_GC_FLAG             0x00000004    // DC is a GC of forest
#define DS_DS_FLAG             0x00000010    // DC supports a DS
#define DS_KDC_FLAG            0x00000020    // DC is running KDC service
#define DS_TIMESERV_FLAG       0x00000040    // DC is running time service
#define DS_CLOSEST_FLAG        0x00000080    // DC is in closest site to client
#define DS_WRITABLE_FLAG       0x00000100    // DC has a writable DS
#define DS_GOOD_TIMESERV_FLAG  0x00000200    // DC is running time service (and has clock hardware)
#define DS_PING_FLAGS          0x0000FFFF    // Flags returned on ping

#define DS_DNS_CONTROLLER_FLAG 0x20000000    // DomainControllerName is a DNS name
#define DS_DNS_DOMAIN_FLAG     0x40000000    // DomainName is a DNS name
#define DS_DNS_FOREST_FLAG     0x80000000    // DnsForestName is a DNS name


//
// Function Prototypes
//

DSGETDCAPI
DWORD
WINAPI
DsGetDcNameA(
    IN LPCSTR ComputerName OPTIONAL,
    IN LPCSTR DomainName OPTIONAL,
    IN GUID *DomainGuid OPTIONAL,
    IN LPCSTR SiteName OPTIONAL,
    IN ULONG Flags,
    OUT PDOMAIN_CONTROLLER_INFOA *DomainControllerInfo
);

DSGETDCAPI
DWORD
WINAPI
DsGetDcNameW(
    IN LPCWSTR ComputerName OPTIONAL,
    IN LPCWSTR DomainName OPTIONAL,
    IN GUID *DomainGuid OPTIONAL,
    IN LPCWSTR SiteName OPTIONAL,
    IN ULONG Flags,
    OUT PDOMAIN_CONTROLLER_INFOW *DomainControllerInfo
);

#ifdef UNICODE
#define DsGetDcName DsGetDcNameW
#else
#define DsGetDcName DsGetDcNameA
#endif // !UNICODE

DSGETDCAPI
DWORD
WINAPI
DsGetSiteNameA(
    IN LPCSTR ComputerName OPTIONAL,
    OUT LPSTR *SiteName
);

DSGETDCAPI
DWORD
WINAPI
DsGetSiteNameW(
    IN LPCWSTR ComputerName OPTIONAL,
    OUT LPWSTR *SiteName
);

#ifdef UNICODE
#define DsGetSiteName DsGetSiteNameW
#else
#define DsGetSiteName DsGetSiteNameA
#endif // !UNICODE


DSGETDCAPI
DWORD
WINAPI
DsValidateSubnetNameW(
    IN LPCWSTR SubnetName
);

DSGETDCAPI
DWORD
WINAPI
DsValidateSubnetNameA(
    IN LPCSTR SubnetName
);

#ifdef UNICODE
#define DsValidateSubnetName DsValidateSubnetNameW
#else
#define DsValidateSubnetName DsValidateSubnetNameA
#endif // !UNICODE


//
// Only include if winsock2.h has been included
//
#ifdef _WINSOCK2API_
DWORD
WINAPI
DsAddressToSiteNamesW(
    IN LPCWSTR ComputerName OPTIONAL,
    IN DWORD EntryCount,
    IN PSOCKET_ADDRESS SocketAddresses,
    OUT LPWSTR **SiteNames
    );

DWORD
WINAPI
DsAddressToSiteNamesA(
    IN LPCSTR ComputerName OPTIONAL,
    IN DWORD EntryCount,
    IN PSOCKET_ADDRESS SocketAddresses,
    OUT LPSTR **SiteNames
    );
#endif // _WINSOCK2API_

#ifdef UNICODE
#define DsAddressToSiteNames DsAddressToSiteNamesW
#else
#define DsAddressToSiteNames DsAddressToSiteNamesA
#endif // !UNICODE

#ifdef __cplusplus
}
#endif

#endif // _DSGETDC_
