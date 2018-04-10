/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 04 19:53:41 1998
 */
/* Compiler settings for SCardDat.Idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __SCardDat_h__
#define __SCardDat_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ByteBuffer_FWD_DEFINED__
#define __ByteBuffer_FWD_DEFINED__

#ifdef __cplusplus
typedef class ByteBuffer ByteBuffer;
#else
typedef struct ByteBuffer ByteBuffer;
#endif /* __cplusplus */

#endif 	/* __ByteBuffer_FWD_DEFINED__ */


#ifndef __CSCardTypeConv_FWD_DEFINED__
#define __CSCardTypeConv_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCardTypeConv CSCardTypeConv;
#else
typedef struct CSCardTypeConv CSCardTypeConv;
#endif /* __cplusplus */

#endif 	/* __CSCardTypeConv_FWD_DEFINED__ */


#ifndef __CSCardCmd_FWD_DEFINED__
#define __CSCardCmd_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCardCmd CSCardCmd;
#else
typedef struct CSCardCmd CSCardCmd;
#endif /* __cplusplus */

#endif 	/* __CSCardCmd_FWD_DEFINED__ */


/* header files for imported files */
#include "sspsidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SCardDat_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Smart Card Support
//  Copyright (C) Microsoft Corporation, 1996.
//
//
// File: SCardDat.h
//
//--------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
// Imports
//

//////////////////////////////////////////////////////////////////
//
// SCardDat Type Library
//


extern RPC_IF_HANDLE __MIDL_itf_SCardDat_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardDat_0000_v0_0_s_ifspec;


#ifndef __SCardDatLib_LIBRARY_DEFINED__
#define __SCardDatLib_LIBRARY_DEFINED__

/* library SCardDatLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SCardDatLib;

EXTERN_C const CLSID CLSID_ByteBuffer;

#ifdef __cplusplus

class DECLSPEC_UUID("E126F8FF-A7AF-11D0-B88A-00C04FD424B9")
ByteBuffer;
#endif

EXTERN_C const CLSID CLSID_CSCardTypeConv;

#ifdef __cplusplus

class DECLSPEC_UUID("53B6AA67-3F56-11D0-916B-00AA00C18068")
CSCardTypeConv;
#endif

EXTERN_C const CLSID CLSID_CSCardCmd;

#ifdef __cplusplus

class DECLSPEC_UUID("D5778AE7-43DE-11D0-9171-00AA00C18068")
CSCardCmd;
#endif
#endif /* __SCardDatLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
