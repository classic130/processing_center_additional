/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 06 15:51:21 2003
 */
/* Compiler settings for F:\gswa_v6_0\itgclient\client\apps\pta\activex\ptav3\source\roamprefs.idl:
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

#ifndef __roamprefs_h__
#define __roamprefs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSRoamPrefs_FWD_DEFINED__
#define __IVSRoamPrefs_FWD_DEFINED__
typedef interface IVSRoamPrefs IVSRoamPrefs;
#endif 	/* __IVSRoamPrefs_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_roamprefs_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_roamprefs_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_roamprefs_0000_v0_0_s_ifspec;

#ifndef __IVSRoamPrefs_INTERFACE_DEFINED__
#define __IVSRoamPrefs_INTERFACE_DEFINED__

/* interface IVSRoamPrefs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSRoamPrefs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d962f4c4-ddb0-11d3-a428-d1a369ca484f")
    IVSRoamPrefs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NumOfSrvrs( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NumOfSrvrs( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RoamingSrvrs( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RoamingSrvrs( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StorageSrvr( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StorageSrvr( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClientInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ClientInfoSig( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ClientInfoSig( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSRoamPrefsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSRoamPrefs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSRoamPrefs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NumOfSrvrs )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NumOfSrvrs )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RoamingSrvrs )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RoamingSrvrs )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StorageSrvr )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StorageSrvr )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientInfo )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClientInfo )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientInfoSig )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClientInfoSig )( 
            IVSRoamPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IVSRoamPrefsVtbl;

    interface IVSRoamPrefs
    {
        CONST_VTBL struct IVSRoamPrefsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSRoamPrefs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSRoamPrefs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSRoamPrefs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSRoamPrefs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSRoamPrefs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSRoamPrefs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSRoamPrefs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSRoamPrefs_get_NumOfSrvrs(This,pVal)	\
    (This)->lpVtbl -> get_NumOfSrvrs(This,pVal)

#define IVSRoamPrefs_put_NumOfSrvrs(This,newVal)	\
    (This)->lpVtbl -> put_NumOfSrvrs(This,newVal)

#define IVSRoamPrefs_get_RoamingSrvrs(This,pVal)	\
    (This)->lpVtbl -> get_RoamingSrvrs(This,pVal)

#define IVSRoamPrefs_put_RoamingSrvrs(This,newVal)	\
    (This)->lpVtbl -> put_RoamingSrvrs(This,newVal)

#define IVSRoamPrefs_get_StorageSrvr(This,pVal)	\
    (This)->lpVtbl -> get_StorageSrvr(This,pVal)

#define IVSRoamPrefs_put_StorageSrvr(This,newVal)	\
    (This)->lpVtbl -> put_StorageSrvr(This,newVal)

#define IVSRoamPrefs_get_ClientInfo(This,pVal)	\
    (This)->lpVtbl -> get_ClientInfo(This,pVal)

#define IVSRoamPrefs_put_ClientInfo(This,newVal)	\
    (This)->lpVtbl -> put_ClientInfo(This,newVal)

#define IVSRoamPrefs_get_ClientInfoSig(This,pVal)	\
    (This)->lpVtbl -> get_ClientInfoSig(This,pVal)

#define IVSRoamPrefs_put_ClientInfoSig(This,newVal)	\
    (This)->lpVtbl -> put_ClientInfoSig(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_get_NumOfSrvrs_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSRoamPrefs_get_NumOfSrvrs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_put_NumOfSrvrs_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSRoamPrefs_put_NumOfSrvrs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_get_RoamingSrvrs_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSRoamPrefs_get_RoamingSrvrs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_put_RoamingSrvrs_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSRoamPrefs_put_RoamingSrvrs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_get_StorageSrvr_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSRoamPrefs_get_StorageSrvr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_put_StorageSrvr_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSRoamPrefs_put_StorageSrvr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_get_ClientInfo_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSRoamPrefs_get_ClientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_put_ClientInfo_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSRoamPrefs_put_ClientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_get_ClientInfoSig_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSRoamPrefs_get_ClientInfoSig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSRoamPrefs_put_ClientInfoSig_Proxy( 
    IVSRoamPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSRoamPrefs_put_ClientInfoSig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSRoamPrefs_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
