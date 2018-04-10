//+---------------------------------------------------------------------------
//  Copyright (C) 1996, Microsoft Corporation.
//
//  File:       adsdb.h
//
//  Contents:   Definitions for the OLE DB provider for ADSI
//
//----------------------------------------------------------------------------

//
// printer status values
//

#ifdef __cplusplus
extern "C" {
#endif

// Most of the constants have been moved into an enum in adstype.h and
// are available publicly in iads.h. This file has been left here so that
// old references to adsdb.h do not break compiles.

#define DBPROPFLAGS_ADSISEARCH          0x0000C000

#ifdef __cplusplus
}
#endif
