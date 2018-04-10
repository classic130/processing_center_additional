/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 17 12:07:42 1998
 */
/* Compiler settings for SCardSrv.Idl:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __SCardSrv_h__
#define __SCardSrv_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISCardISO7816_FWD_DEFINED__
#define __ISCardISO7816_FWD_DEFINED__
typedef interface ISCardISO7816 ISCardISO7816;
#endif 	/* __ISCardISO7816_FWD_DEFINED__ */


#ifndef __CSCardISO7816_FWD_DEFINED__
#define __CSCardISO7816_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCardISO7816 CSCardISO7816;
#else
typedef struct CSCardISO7816 CSCardISO7816;
#endif /* __cplusplus */

#endif 	/* __CSCardISO7816_FWD_DEFINED__ */


/* header files for imported files */
#include "SspsIdl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SCardSrv_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Smart Cards Support
//  Copyright (C) Microsoft Corporation, 1996.
//
//
// File: SCardSrv.h
//
//--------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
// Imports
//


//////////////////////////////////////////////////////////////////
//
// Constants and Types
//
#ifndef _NULL_DEFINED
#define _NULL_DEFINED
#endif // !_NULL_DEFINED
#ifndef _NULL_BYTE_DEFINED
#define _NULL_BYTE_DEFINED
#define NULL_BYTE    (0x00)
#endif  // !_NULL_BYTE_DEFINED

//////////////////////////////////////////////////////////////////
//
// ISCardISO7816 Interface Definition
//
#ifndef _LPSCARDISO7816_DEFINED
#define _LPSCARDISO7816_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_SCardSrv_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardSrv_0000_v0_0_s_ifspec;

#ifndef __ISCardISO7816_INTERFACE_DEFINED__
#define __ISCardISO7816_INTERFACE_DEFINED__

/* interface ISCardISO7816 */
/* [unique][helpstring][uuid][object] */ 

typedef /* [unique] */ ISCardISO7816 __RPC_FAR *LPSCARDISO;

typedef /* [unique] */ LPSCARDISO LPSCARDISO7816;


EXTERN_C const IID IID_ISCardISO7816;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53B6AA68-3F56-11D0-916B-00AA00C18068")
    ISCardISO7816 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppendRecord( 
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EraseBinary( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExternalAuthenticate( 
            /* [defaultvalue][in] */ BYTE byAlgorithmRef,
            /* [defaultvalue][in] */ BYTE bySecretRef,
            /* [defaultvalue][in] */ LPBYTEBUFFER pChallenge,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetChallenge( 
            /* [defaultvalue][in] */ LONG lBytesExpected,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lBytesToGet,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetResponse( 
            /* [defaultvalue][in] */ BYTE byP1,
            /* [defaultvalue][in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lDataLength,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InternalAuthenticate( 
            /* [defaultvalue][in] */ BYTE byAlgorithmRef,
            /* [defaultvalue][in] */ BYTE bySecretRef,
            /* [in] */ LPBYTEBUFFER pChallenge,
            /* [defaultvalue][in] */ LONG lReplyBytes,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ManageChannel( 
            /* [defaultvalue][in] */ BYTE byChannelState,
            /* [defaultvalue][in] */ BYTE byChannel,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PutData( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadBinary( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadRecord( 
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [in] */ BYTE byRefCtrl,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFile( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetDefaultClassId( 
            /* [in] */ BYTE byClass) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateBinary( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UpdateRecord( 
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Verify( 
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteBinary( 
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WriteRecord( 
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISCardISO7816Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISCardISO7816 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISCardISO7816 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppendRecord )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EraseBinary )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExternalAuthenticate )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byAlgorithmRef,
            /* [defaultvalue][in] */ BYTE bySecretRef,
            /* [defaultvalue][in] */ LPBYTEBUFFER pChallenge,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChallenge )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ LONG lBytesExpected,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lBytesToGet,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetResponse )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byP1,
            /* [defaultvalue][in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lDataLength,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InternalAuthenticate )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byAlgorithmRef,
            /* [defaultvalue][in] */ BYTE bySecretRef,
            /* [in] */ LPBYTEBUFFER pChallenge,
            /* [defaultvalue][in] */ LONG lReplyBytes,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ManageChannel )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byChannelState,
            /* [defaultvalue][in] */ BYTE byChannel,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutData )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadBinary )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadRecord )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [in] */ BYTE byRefCtrl,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectFile )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [defaultvalue][in] */ LONG lBytesToRead,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDefaultClassId )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byClass);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateBinary )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UpdateRecord )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Verify )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [defaultvalue][in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteBinary )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [in] */ BYTE byP1,
            /* [in] */ BYTE byP2,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteRecord )( 
            ISCardISO7816 __RPC_FAR * This,
            /* [defaultvalue][in] */ BYTE byRecordId,
            /* [defaultvalue][in] */ BYTE byRefCtrl,
            /* [in] */ LPBYTEBUFFER pData,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        END_INTERFACE
    } ISCardISO7816Vtbl;

    interface ISCardISO7816
    {
        CONST_VTBL struct ISCardISO7816Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISCardISO7816_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISCardISO7816_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISCardISO7816_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISCardISO7816_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISCardISO7816_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISCardISO7816_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISCardISO7816_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISCardISO7816_AppendRecord(This,byRefCtrl,pData,ppCmd)	\
    (This)->lpVtbl -> AppendRecord(This,byRefCtrl,pData,ppCmd)

#define ISCardISO7816_EraseBinary(This,byP1,byP2,pData,ppCmd)	\
    (This)->lpVtbl -> EraseBinary(This,byP1,byP2,pData,ppCmd)

#define ISCardISO7816_ExternalAuthenticate(This,byAlgorithmRef,bySecretRef,pChallenge,ppCmd)	\
    (This)->lpVtbl -> ExternalAuthenticate(This,byAlgorithmRef,bySecretRef,pChallenge,ppCmd)

#define ISCardISO7816_GetChallenge(This,lBytesExpected,ppCmd)	\
    (This)->lpVtbl -> GetChallenge(This,lBytesExpected,ppCmd)

#define ISCardISO7816_GetData(This,byP1,byP2,lBytesToGet,ppCmd)	\
    (This)->lpVtbl -> GetData(This,byP1,byP2,lBytesToGet,ppCmd)

#define ISCardISO7816_GetResponse(This,byP1,byP2,lDataLength,ppCmd)	\
    (This)->lpVtbl -> GetResponse(This,byP1,byP2,lDataLength,ppCmd)

#define ISCardISO7816_InternalAuthenticate(This,byAlgorithmRef,bySecretRef,pChallenge,lReplyBytes,ppCmd)	\
    (This)->lpVtbl -> InternalAuthenticate(This,byAlgorithmRef,bySecretRef,pChallenge,lReplyBytes,ppCmd)

#define ISCardISO7816_ManageChannel(This,byChannelState,byChannel,ppCmd)	\
    (This)->lpVtbl -> ManageChannel(This,byChannelState,byChannel,ppCmd)

#define ISCardISO7816_PutData(This,byP1,byP2,pData,ppCmd)	\
    (This)->lpVtbl -> PutData(This,byP1,byP2,pData,ppCmd)

#define ISCardISO7816_ReadBinary(This,byP1,byP2,lBytesToRead,ppCmd)	\
    (This)->lpVtbl -> ReadBinary(This,byP1,byP2,lBytesToRead,ppCmd)

#define ISCardISO7816_ReadRecord(This,byRecordId,byRefCtrl,lBytesToRead,ppCmd)	\
    (This)->lpVtbl -> ReadRecord(This,byRecordId,byRefCtrl,lBytesToRead,ppCmd)

#define ISCardISO7816_SelectFile(This,byP1,byP2,pData,lBytesToRead,ppCmd)	\
    (This)->lpVtbl -> SelectFile(This,byP1,byP2,pData,lBytesToRead,ppCmd)

#define ISCardISO7816_SetDefaultClassId(This,byClass)	\
    (This)->lpVtbl -> SetDefaultClassId(This,byClass)

#define ISCardISO7816_UpdateBinary(This,byP1,byP2,pData,ppCmd)	\
    (This)->lpVtbl -> UpdateBinary(This,byP1,byP2,pData,ppCmd)

#define ISCardISO7816_UpdateRecord(This,byRecordId,byRefCtrl,pData,ppCmd)	\
    (This)->lpVtbl -> UpdateRecord(This,byRecordId,byRefCtrl,pData,ppCmd)

#define ISCardISO7816_Verify(This,byRefCtrl,pData,ppCmd)	\
    (This)->lpVtbl -> Verify(This,byRefCtrl,pData,ppCmd)

#define ISCardISO7816_WriteBinary(This,byP1,byP2,pData,ppCmd)	\
    (This)->lpVtbl -> WriteBinary(This,byP1,byP2,pData,ppCmd)

#define ISCardISO7816_WriteRecord(This,byRecordId,byRefCtrl,pData,ppCmd)	\
    (This)->lpVtbl -> WriteRecord(This,byRecordId,byRefCtrl,pData,ppCmd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_AppendRecord_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byRefCtrl,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_AppendRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_EraseBinary_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [defaultvalue][in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_EraseBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_ExternalAuthenticate_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byAlgorithmRef,
    /* [defaultvalue][in] */ BYTE bySecretRef,
    /* [defaultvalue][in] */ LPBYTEBUFFER pChallenge,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_ExternalAuthenticate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_GetChallenge_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ LONG lBytesExpected,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_GetChallenge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_GetData_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [defaultvalue][in] */ LONG lBytesToGet,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_GetResponse_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byP1,
    /* [defaultvalue][in] */ BYTE byP2,
    /* [defaultvalue][in] */ LONG lDataLength,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_GetResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_InternalAuthenticate_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byAlgorithmRef,
    /* [defaultvalue][in] */ BYTE bySecretRef,
    /* [in] */ LPBYTEBUFFER pChallenge,
    /* [defaultvalue][in] */ LONG lReplyBytes,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_InternalAuthenticate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_ManageChannel_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byChannelState,
    /* [defaultvalue][in] */ BYTE byChannel,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_ManageChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_PutData_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_PutData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_ReadBinary_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [defaultvalue][in] */ LONG lBytesToRead,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_ReadBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_ReadRecord_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byRecordId,
    /* [in] */ BYTE byRefCtrl,
    /* [defaultvalue][in] */ LONG lBytesToRead,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_ReadRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_SelectFile_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [defaultvalue][in] */ LPBYTEBUFFER pData,
    /* [defaultvalue][in] */ LONG lBytesToRead,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_SelectFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_SetDefaultClassId_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byClass);


void __RPC_STUB ISCardISO7816_SetDefaultClassId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_UpdateBinary_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_UpdateBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_UpdateRecord_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byRecordId,
    /* [defaultvalue][in] */ BYTE byRefCtrl,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_UpdateRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_Verify_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byRefCtrl,
    /* [defaultvalue][in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_Verify_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_WriteBinary_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [in] */ BYTE byP1,
    /* [in] */ BYTE byP2,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_WriteBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardISO7816_WriteRecord_Proxy( 
    ISCardISO7816 __RPC_FAR * This,
    /* [defaultvalue][in] */ BYTE byRecordId,
    /* [defaultvalue][in] */ BYTE byRefCtrl,
    /* [in] */ LPBYTEBUFFER pData,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCardISO7816_WriteRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISCardISO7816_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SCardSrv_0112 */
/* [local] */ 

#endif //!_LPSCARDISO7816_DEFINED

//////////////////////////////////////////////////////////////////
//
// SCardSrv Type Library
//


extern RPC_IF_HANDLE __MIDL_itf_SCardSrv_0112_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardSrv_0112_v0_0_s_ifspec;


#ifndef __SCardSrvLib_LIBRARY_DEFINED__
#define __SCardSrvLib_LIBRARY_DEFINED__

/* library SCardSrvLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SCardSrvLib;

EXTERN_C const CLSID CLSID_CSCardISO7816;

#ifdef __cplusplus

class DECLSPEC_UUID("53B6AA6C-3F56-11D0-916B-00AA00C18068")
CSCardISO7816;
#endif
#endif /* __SCardSrvLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
