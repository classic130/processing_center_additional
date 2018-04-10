/*++

Copyright (c) 1996  Microsoft Corporation

Module Name:

    sporder.h

Abstract:

    This header prototypes the 32-Bit Windows functions that are used
    to change the order or WinSock2 transport service providers and
    name space providers.

Revision History:

--*/

#ifdef __cplusplus
extern "C" {
#endif

int
WSPAPI
WSCWriteProviderOrder (
    IN LPDWORD lpwdCatalogEntryId,
    IN DWORD dwNumberOfEntries
    );

int
WSPAPI
WSCWriteNameSpaceOrder (
    IN LPGUID lpProviderId,
    IN DWORD dwNumberOfEntries
    );

#ifdef __cplusplus
}
#endif
