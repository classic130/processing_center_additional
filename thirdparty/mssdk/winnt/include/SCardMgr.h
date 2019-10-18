/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 17 12:07:41 1998
 */
/* Compiler settings for SCardMgr.Idl:
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

#ifndef __SCardMgr_h__
#define __SCardMgr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISCard_FWD_DEFINED__
#define __ISCard_FWD_DEFINED__
typedef interface ISCard ISCard;
#endif 	/* __ISCard_FWD_DEFINED__ */


#ifndef __ISCardDatabase_FWD_DEFINED__
#define __ISCardDatabase_FWD_DEFINED__
typedef interface ISCardDatabase ISCardDatabase;
#endif 	/* __ISCardDatabase_FWD_DEFINED__ */


#ifndef __ISCardLocate_FWD_DEFINED__
#define __ISCardLocate_FWD_DEFINED__
typedef interface ISCardLocate ISCardLocate;
#endif 	/* __ISCardLocate_FWD_DEFINED__ */


#ifndef __CSCard_FWD_DEFINED__
#define __CSCard_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCard CSCard;
#else
typedef struct CSCard CSCard;
#endif /* __cplusplus */

#endif 	/* __CSCard_FWD_DEFINED__ */


#ifndef __CSCardDatabase_FWD_DEFINED__
#define __CSCardDatabase_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCardDatabase CSCardDatabase;
#else
typedef struct CSCardDatabase CSCardDatabase;
#endif /* __cplusplus */

#endif 	/* __CSCardDatabase_FWD_DEFINED__ */


#ifndef __CSCardLocate_FWD_DEFINED__
#define __CSCardLocate_FWD_DEFINED__

#ifdef __cplusplus
typedef class CSCardLocate CSCardLocate;
#else
typedef struct CSCardLocate CSCardLocate;
#endif /* __cplusplus */

#endif 	/* __CSCardLocate_FWD_DEFINED__ */


/* header files for imported files */
#include "SspsIdl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SCardMgr_0000 */
/* [local] */ 

//+-------------------------------------------------------------------------
//
//  Microsoft Smart Card Support
//  Copyright (C) Microsoft Corporation, 1996.
//
// File: SCardMgr.h
//
//--------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////
//
// Imports
//




//////////////////////////////////////////////////////////////////
//
// Types and Constants
//
#ifndef _NULL_DEFINED
#define _NULL_DEFINED
#endif // !_NULL_DEFINED
#ifndef _HSCARD_DEFINED
#define _HSCARD_DEFINED
typedef /* [public] */ LONG HSCARD;

#endif // !_HSCARD_DEFINED
#ifndef _LPHSCARD_DEFINED
#define _LPHSCARD_DEFINED
typedef /* [unique] */ HSCARD __RPC_FAR *PHSCARD;

typedef /* [unique] */ HSCARD __RPC_FAR *LPHSCARD;

#endif // !_LPHSCARD_DEFINED
#ifndef _HSCARDCONTEXT_DEFINED
#define _HSCARDCONTEXT_DEFINED
typedef /* [public] */ LONG HSCARDCONTEXT;

#endif // !_HSCARDCONTEXT_DEFINED
#ifndef _LPHSCARDCONTEXT_DEFINED
#define _LPHSCARDCONTEXT_DEFINED
typedef /* [unique] */ __RPC_FAR *PHSCARDCONTEXT;

typedef /* [unique] */ __RPC_FAR *LPHSCARDCONTEXT;

#endif // !_LPHSCARDCONTEXT_DEFINED
#ifndef _SCARD_SHARE_MODES_DEFINED
#define _SCARD_SHARE_MODES_DEFINED
typedef /* [version][v1_enum][helpstring] */ 
enum tagSCARD_SHARE_MODES
    {	EXCLUSIVE	= 1,
	SHARED	= 2
    }	SCARD_SHARE_MODES;

#endif // !_SCARD_SHARE_MODES_DEFINED
#ifndef _SCARD_DISPOSITIONS_DEFINED
#define _SCARD_DISPOSITIONS_DEFINED
typedef /* [version][v1_enum][helpstring] */ 
enum tagSCARD_DISPOSITIONS
    {	LEAVE	= 0,
	RESET	= 1,
	UNPOWER	= 2,
	EJECT	= 3
    }	SCARD_DISPOSITIONS;

#endif // !_SCARD_DISPOSITIONS_DEFINED
#ifndef _SCARD_STATES_DEFINED
#define _SCARD_STATES_DEFINED
typedef /* [version][v1_enum][helpstring] */ 
enum tagSCARD_STATES
    {	ABSENT	= 1,
	PRESENT	= 2,
	SWALLOWED	= 3,
	POWERED	= 4,
	NEGOTIABLEMODE	= 5,
	SPECIFICMODE	= 6
    }	SCARD_STATES;

#endif // !_SCARD_STATES_DEFINED
#ifndef _SCARD_PROTOCOLS_DEFINED
#define _SCARD_PROTOCOLS_DEFINED
typedef /* [version][v1_enum][helpstring] */ 
enum tagSCARD_PROTOCOLS
    {	T0	= 0x1,
	T1	= 0x2,
	RAW	= 0xff
    }	SCARD_PROTOCOLS;

#endif // !_SCARD_PROTOCOLS_DEFINED
#ifndef _SCARD_INFO
#define _SCARD_INFO
typedef /* [version][helpstring] */ struct  tagSCARDINFO
    {
    HSCARD hCard;
    HSCARDCONTEXT hContext;
    SCARD_PROTOCOLS ActiveProtocol;
    SCARD_SHARE_MODES ShareMode;
    LONG hwndOwner;
    LONG lpfnConnectProc;
    LONG lpfnCheckProc;
    LONG lpfnDisconnectProc;
    }	SCARDINFO;

#define _LPSCARDINFO
typedef /* [unique] */ SCARDINFO __RPC_FAR *PSCARDINFO;

typedef /* [unique] */ SCARDINFO __RPC_FAR *LPSCARDINFO;

#endif //_SCARD_INFO

//////////////////////////////////////////////////////////////////
//
// ISCard Interface
//
#ifndef _LPSCARD_DEFINED
#define _LPSCARD_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0000_v0_0_s_ifspec;

#ifndef __ISCard_INTERFACE_DEFINED__
#define __ISCard_INTERFACE_DEFINED__

/* interface ISCard */
/* [unique][version][helpstring][uuid][object] */ 

typedef /* [unique] */ ISCard __RPC_FAR *LPSCARD;

typedef /* [unique] */ LPSCARD LPSMARTCARD;


EXTERN_C const IID IID_ISCard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1461AAC3-6810-11D0-918F-00AA00C18068")
    ISCard : public IDispatch
    {
    public:
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Atr( 
            /* [retval][out] */ LPBYTEBUFFER __RPC_FAR *ppAtr) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_CardHandle( 
            /* [retval][out] */ HSCARD __RPC_FAR *pHandle) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Context( 
            /* [retval][out] */ HSCARDCONTEXT __RPC_FAR *pContext) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [retval][out] */ SCARD_PROTOCOLS __RPC_FAR *pProtocol) = 0;
        
        virtual /* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ SCARD_STATES __RPC_FAR *pStatus) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachByHandle( 
            /* [in] */ HSCARD hCard) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AttachByReader( 
            /* [in] */ BSTR bstrReaderName,
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode = EXCLUSIVE,
            /* [defaultvalue][in] */ SCARD_PROTOCOLS PrefProtocol = T0) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Detach( 
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition = LEAVE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LockSCard( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReAttach( 
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode = EXCLUSIVE,
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS InitState = LEAVE) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Transaction( 
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnlockSCard( 
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition = LEAVE) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISCardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISCard __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISCard __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISCard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISCard __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISCard __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISCard __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISCard __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Atr )( 
            ISCard __RPC_FAR * This,
            /* [retval][out] */ LPBYTEBUFFER __RPC_FAR *ppAtr);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CardHandle )( 
            ISCard __RPC_FAR * This,
            /* [retval][out] */ HSCARD __RPC_FAR *pHandle);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Context )( 
            ISCard __RPC_FAR * This,
            /* [retval][out] */ HSCARDCONTEXT __RPC_FAR *pContext);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Protocol )( 
            ISCard __RPC_FAR * This,
            /* [retval][out] */ SCARD_PROTOCOLS __RPC_FAR *pProtocol);
        
        /* [helpstring][propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            ISCard __RPC_FAR * This,
            /* [retval][out] */ SCARD_STATES __RPC_FAR *pStatus);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AttachByHandle )( 
            ISCard __RPC_FAR * This,
            /* [in] */ HSCARD hCard);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AttachByReader )( 
            ISCard __RPC_FAR * This,
            /* [in] */ BSTR bstrReaderName,
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
            /* [defaultvalue][in] */ SCARD_PROTOCOLS PrefProtocol);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Detach )( 
            ISCard __RPC_FAR * This,
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockSCard )( 
            ISCard __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReAttach )( 
            ISCard __RPC_FAR * This,
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS InitState);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Transaction )( 
            ISCard __RPC_FAR * This,
            /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockSCard )( 
            ISCard __RPC_FAR * This,
            /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition);
        
        END_INTERFACE
    } ISCardVtbl;

    interface ISCard
    {
        CONST_VTBL struct ISCardVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISCard_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISCard_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISCard_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISCard_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISCard_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISCard_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISCard_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISCard_get_Atr(This,ppAtr)	\
    (This)->lpVtbl -> get_Atr(This,ppAtr)

#define ISCard_get_CardHandle(This,pHandle)	\
    (This)->lpVtbl -> get_CardHandle(This,pHandle)

#define ISCard_get_Context(This,pContext)	\
    (This)->lpVtbl -> get_Context(This,pContext)

#define ISCard_get_Protocol(This,pProtocol)	\
    (This)->lpVtbl -> get_Protocol(This,pProtocol)

#define ISCard_get_Status(This,pStatus)	\
    (This)->lpVtbl -> get_Status(This,pStatus)

#define ISCard_AttachByHandle(This,hCard)	\
    (This)->lpVtbl -> AttachByHandle(This,hCard)

#define ISCard_AttachByReader(This,bstrReaderName,ShareMode,PrefProtocol)	\
    (This)->lpVtbl -> AttachByReader(This,bstrReaderName,ShareMode,PrefProtocol)

#define ISCard_Detach(This,Disposition)	\
    (This)->lpVtbl -> Detach(This,Disposition)

#define ISCard_LockSCard(This)	\
    (This)->lpVtbl -> LockSCard(This)

#define ISCard_ReAttach(This,ShareMode,InitState)	\
    (This)->lpVtbl -> ReAttach(This,ShareMode,InitState)

#define ISCard_Transaction(This,ppCmd)	\
    (This)->lpVtbl -> Transaction(This,ppCmd)

#define ISCard_UnlockSCard(This,Disposition)	\
    (This)->lpVtbl -> UnlockSCard(This,Disposition)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ISCard_get_Atr_Proxy( 
    ISCard __RPC_FAR * This,
    /* [retval][out] */ LPBYTEBUFFER __RPC_FAR *ppAtr);


void __RPC_STUB ISCard_get_Atr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ISCard_get_CardHandle_Proxy( 
    ISCard __RPC_FAR * This,
    /* [retval][out] */ HSCARD __RPC_FAR *pHandle);


void __RPC_STUB ISCard_get_CardHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ISCard_get_Context_Proxy( 
    ISCard __RPC_FAR * This,
    /* [retval][out] */ HSCARDCONTEXT __RPC_FAR *pContext);


void __RPC_STUB ISCard_get_Context_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ISCard_get_Protocol_Proxy( 
    ISCard __RPC_FAR * This,
    /* [retval][out] */ SCARD_PROTOCOLS __RPC_FAR *pProtocol);


void __RPC_STUB ISCard_get_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget][id] */ HRESULT STDMETHODCALLTYPE ISCard_get_Status_Proxy( 
    ISCard __RPC_FAR * This,
    /* [retval][out] */ SCARD_STATES __RPC_FAR *pStatus);


void __RPC_STUB ISCard_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_AttachByHandle_Proxy( 
    ISCard __RPC_FAR * This,
    /* [in] */ HSCARD hCard);


void __RPC_STUB ISCard_AttachByHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_AttachByReader_Proxy( 
    ISCard __RPC_FAR * This,
    /* [in] */ BSTR bstrReaderName,
    /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
    /* [defaultvalue][in] */ SCARD_PROTOCOLS PrefProtocol);


void __RPC_STUB ISCard_AttachByReader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_Detach_Proxy( 
    ISCard __RPC_FAR * This,
    /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition);


void __RPC_STUB ISCard_Detach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_LockSCard_Proxy( 
    ISCard __RPC_FAR * This);


void __RPC_STUB ISCard_LockSCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_ReAttach_Proxy( 
    ISCard __RPC_FAR * This,
    /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
    /* [defaultvalue][in] */ SCARD_DISPOSITIONS InitState);


void __RPC_STUB ISCard_ReAttach_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_Transaction_Proxy( 
    ISCard __RPC_FAR * This,
    /* [out][in] */ LPSCARDCMD __RPC_FAR *ppCmd);


void __RPC_STUB ISCard_Transaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCard_UnlockSCard_Proxy( 
    ISCard __RPC_FAR * This,
    /* [defaultvalue][in] */ SCARD_DISPOSITIONS Disposition);


void __RPC_STUB ISCard_UnlockSCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISCard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SCardMgr_0112 */
/* [local] */ 

#endif // !_LPSCARD_DEFINED

//////////////////////////////////////////////////////////////////
//
// ISCardDatabase Interface
//
#ifndef _LPSCARDDATABASE_DEFINED
#define _LPSCARDDATABASE_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0112_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0112_v0_0_s_ifspec;

#ifndef __ISCardDatabase_INTERFACE_DEFINED__
#define __ISCardDatabase_INTERFACE_DEFINED__

/* interface ISCardDatabase */
/* [unique][version][helpstring][uuid][object] */ 

typedef /* [unique] */ ISCardDatabase __RPC_FAR *LPSCARDDATABASE;


EXTERN_C const IID IID_ISCardDatabase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1461AAC8-6810-11D0-918F-00AA00C18068")
    ISCardDatabase : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetProviderCardId( 
            /* [in] */ BSTR bstrCardName,
            /* [retval][out] */ LPGUID __RPC_FAR *ppguidProviderId) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListCardInterfaces( 
            /* [in] */ BSTR bstrCardName,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppInterfaceGuids) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListCards( 
            /* [defaultvalue][in] */ LPBYTEBUFFER pAtr,
            /* [defaultvalue][in] */ LPSAFEARRAY pInterfaceGuids,
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppCardNames) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListReaderGroups( 
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaderGroups) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ListReaders( 
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaders) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISCardDatabaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISCardDatabase __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISCardDatabase __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISCardDatabase __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProviderCardId )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ BSTR bstrCardName,
            /* [retval][out] */ LPGUID __RPC_FAR *ppguidProviderId);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListCardInterfaces )( 
            ISCardDatabase __RPC_FAR * This,
            /* [in] */ BSTR bstrCardName,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppInterfaceGuids);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListCards )( 
            ISCardDatabase __RPC_FAR * This,
            /* [defaultvalue][in] */ LPBYTEBUFFER pAtr,
            /* [defaultvalue][in] */ LPSAFEARRAY pInterfaceGuids,
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppCardNames);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListReaderGroups )( 
            ISCardDatabase __RPC_FAR * This,
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaderGroups);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ListReaders )( 
            ISCardDatabase __RPC_FAR * This,
            /* [defaultvalue][lcid][in] */ long localeId,
            /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaders);
        
        END_INTERFACE
    } ISCardDatabaseVtbl;

    interface ISCardDatabase
    {
        CONST_VTBL struct ISCardDatabaseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISCardDatabase_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISCardDatabase_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISCardDatabase_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISCardDatabase_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISCardDatabase_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISCardDatabase_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISCardDatabase_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISCardDatabase_GetProviderCardId(This,bstrCardName,ppguidProviderId)	\
    (This)->lpVtbl -> GetProviderCardId(This,bstrCardName,ppguidProviderId)

#define ISCardDatabase_ListCardInterfaces(This,bstrCardName,ppInterfaceGuids)	\
    (This)->lpVtbl -> ListCardInterfaces(This,bstrCardName,ppInterfaceGuids)

#define ISCardDatabase_ListCards(This,pAtr,pInterfaceGuids,localeId,ppCardNames)	\
    (This)->lpVtbl -> ListCards(This,pAtr,pInterfaceGuids,localeId,ppCardNames)

#define ISCardDatabase_ListReaderGroups(This,localeId,ppReaderGroups)	\
    (This)->lpVtbl -> ListReaderGroups(This,localeId,ppReaderGroups)

#define ISCardDatabase_ListReaders(This,localeId,ppReaders)	\
    (This)->lpVtbl -> ListReaders(This,localeId,ppReaders)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardDatabase_GetProviderCardId_Proxy( 
    ISCardDatabase __RPC_FAR * This,
    /* [in] */ BSTR bstrCardName,
    /* [retval][out] */ LPGUID __RPC_FAR *ppguidProviderId);


void __RPC_STUB ISCardDatabase_GetProviderCardId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardDatabase_ListCardInterfaces_Proxy( 
    ISCardDatabase __RPC_FAR * This,
    /* [in] */ BSTR bstrCardName,
    /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppInterfaceGuids);


void __RPC_STUB ISCardDatabase_ListCardInterfaces_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardDatabase_ListCards_Proxy( 
    ISCardDatabase __RPC_FAR * This,
    /* [defaultvalue][in] */ LPBYTEBUFFER pAtr,
    /* [defaultvalue][in] */ LPSAFEARRAY pInterfaceGuids,
    /* [defaultvalue][lcid][in] */ long localeId,
    /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppCardNames);


void __RPC_STUB ISCardDatabase_ListCards_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardDatabase_ListReaderGroups_Proxy( 
    ISCardDatabase __RPC_FAR * This,
    /* [defaultvalue][lcid][in] */ long localeId,
    /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaderGroups);


void __RPC_STUB ISCardDatabase_ListReaderGroups_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardDatabase_ListReaders_Proxy( 
    ISCardDatabase __RPC_FAR * This,
    /* [defaultvalue][lcid][in] */ long localeId,
    /* [retval][out] */ LPSAFEARRAY __RPC_FAR *ppReaders);


void __RPC_STUB ISCardDatabase_ListReaders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISCardDatabase_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SCardMgr_0114 */
/* [local] */ 

#endif // !_LPSCARDDATABASE_DEFINED

//////////////////////////////////////////////////////////////////
//
// ISCardLocate Interface
//
#ifndef _LPSCARDLOCATE_DEFINED
#define _LPSCARDLOCATE_DEFINED


extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0114_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0114_v0_0_s_ifspec;

#ifndef __ISCardLocate_INTERFACE_DEFINED__
#define __ISCardLocate_INTERFACE_DEFINED__

/* interface ISCardLocate */
/* [unique][version][helpstring][uuid][object] */ 

typedef /* [unique] */ ISCardLocate __RPC_FAR *LPSCARDLOCATE;

typedef /* [unique] */ LPSCARDLOCATE LPSCARDLOC;


EXTERN_C const IID IID_ISCardLocate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1461AACD-6810-11D0-918F-00AA00C18068")
    ISCardLocate : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConfigureCardGuidSearch( 
            /* [in] */ LPSAFEARRAY pCardGuids,
            /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames = 0,
            /* [defaultvalue][in] */ BSTR bstrTitle = L"",
            /* [defaultvalue][in] */ LONG lFlags = 1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConfigureCardNameSearch( 
            /* [in] */ LPSAFEARRAY pCardNames,
            /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames = 0,
            /* [defaultvalue][in] */ BSTR bstrTitle = L"",
            /* [defaultvalue][in] */ LONG lFlags = 1) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FindCard( 
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
            /* [defaultvalue][in] */ SCARD_PROTOCOLS Protocols,
            /* [defaultvalue][in] */ LONG lFlags,
            /* [retval][out] */ LPSCARDINFO __RPC_FAR *ppCardInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISCardLocateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISCardLocate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISCardLocate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISCardLocate __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConfigureCardGuidSearch )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ LPSAFEARRAY pCardGuids,
            /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames,
            /* [defaultvalue][in] */ BSTR bstrTitle,
            /* [defaultvalue][in] */ LONG lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConfigureCardNameSearch )( 
            ISCardLocate __RPC_FAR * This,
            /* [in] */ LPSAFEARRAY pCardNames,
            /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames,
            /* [defaultvalue][in] */ BSTR bstrTitle,
            /* [defaultvalue][in] */ LONG lFlags);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindCard )( 
            ISCardLocate __RPC_FAR * This,
            /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
            /* [defaultvalue][in] */ SCARD_PROTOCOLS Protocols,
            /* [defaultvalue][in] */ LONG lFlags,
            /* [retval][out] */ LPSCARDINFO __RPC_FAR *ppCardInfo);
        
        END_INTERFACE
    } ISCardLocateVtbl;

    interface ISCardLocate
    {
        CONST_VTBL struct ISCardLocateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISCardLocate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISCardLocate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISCardLocate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISCardLocate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISCardLocate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISCardLocate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISCardLocate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISCardLocate_ConfigureCardGuidSearch(This,pCardGuids,pGroupNames,bstrTitle,lFlags)	\
    (This)->lpVtbl -> ConfigureCardGuidSearch(This,pCardGuids,pGroupNames,bstrTitle,lFlags)

#define ISCardLocate_ConfigureCardNameSearch(This,pCardNames,pGroupNames,bstrTitle,lFlags)	\
    (This)->lpVtbl -> ConfigureCardNameSearch(This,pCardNames,pGroupNames,bstrTitle,lFlags)

#define ISCardLocate_FindCard(This,ShareMode,Protocols,lFlags,ppCardInfo)	\
    (This)->lpVtbl -> FindCard(This,ShareMode,Protocols,lFlags,ppCardInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardLocate_ConfigureCardGuidSearch_Proxy( 
    ISCardLocate __RPC_FAR * This,
    /* [in] */ LPSAFEARRAY pCardGuids,
    /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames,
    /* [defaultvalue][in] */ BSTR bstrTitle,
    /* [defaultvalue][in] */ LONG lFlags);


void __RPC_STUB ISCardLocate_ConfigureCardGuidSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardLocate_ConfigureCardNameSearch_Proxy( 
    ISCardLocate __RPC_FAR * This,
    /* [in] */ LPSAFEARRAY pCardNames,
    /* [defaultvalue][in] */ LPSAFEARRAY pGroupNames,
    /* [defaultvalue][in] */ BSTR bstrTitle,
    /* [defaultvalue][in] */ LONG lFlags);


void __RPC_STUB ISCardLocate_ConfigureCardNameSearch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ISCardLocate_FindCard_Proxy( 
    ISCardLocate __RPC_FAR * This,
    /* [defaultvalue][in] */ SCARD_SHARE_MODES ShareMode,
    /* [defaultvalue][in] */ SCARD_PROTOCOLS Protocols,
    /* [defaultvalue][in] */ LONG lFlags,
    /* [retval][out] */ LPSCARDINFO __RPC_FAR *ppCardInfo);


void __RPC_STUB ISCardLocate_FindCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISCardLocate_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SCardMgr_0116 */
/* [local] */ 

#define CB_SCARDINFO     (sizeof(SCARDINFO))
#endif // !_LPSCARDLOCATE_DEFINED

//////////////////////////////////////////////////////////////////
//
// SCardMgr Type Library
//


extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0116_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SCardMgr_0116_v0_0_s_ifspec;


#ifndef __SCardMgrLib_LIBRARY_DEFINED__
#define __SCardMgrLib_LIBRARY_DEFINED__

/* library SCardMgrLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SCardMgrLib;

EXTERN_C const CLSID CLSID_CSCard;

#ifdef __cplusplus

class DECLSPEC_UUID("1461AAC7-6810-11D0-918F-00AA00C18068")
CSCard;
#endif

EXTERN_C const CLSID CLSID_CSCardDatabase;

#ifdef __cplusplus

class DECLSPEC_UUID("1461AACC-6810-11D0-918F-00AA00C18068")
CSCardDatabase;
#endif

EXTERN_C const CLSID CLSID_CSCardLocate;

#ifdef __cplusplus

class DECLSPEC_UUID("1461AAD1-6810-11D0-918F-00AA00C18068")
CSCardLocate;
#endif
#endif /* __SCardMgrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long __RPC_FAR *, unsigned long            , LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long __RPC_FAR *, LPSAFEARRAY __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
