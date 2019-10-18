/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 06 15:51:25 2003
 */
/* Compiler settings for F:\gswa_v6_0\itgclient\client\apps\pta\activex\ptav3\source\ptadllapi.idl:
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

#ifndef __ptadllapi_h__
#define __ptadllapi_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSPTADllApi_FWD_DEFINED__
#define __IVSPTADllApi_FWD_DEFINED__
typedef interface IVSPTADllApi IVSPTADllApi;
#endif 	/* __IVSPTADllApi_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ptadllapi_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_ptadllapi_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ptadllapi_0000_v0_0_s_ifspec;

#ifndef __IVSPTADllApi_INTERFACE_DEFINED__
#define __IVSPTADllApi_INTERFACE_DEFINED__

/* interface IVSPTADllApi */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSPTADllApi;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a453a978-2054-11d4-8175-0060b0f885e6")
    IVSPTADllApi : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostFQDN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HostFQDN( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Protocol( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedIDCertContext( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DoAttachedSig( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DoAttachedSig( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowSignUI( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowSignUI( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OleClientSite( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OleClientSite( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HashData( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HashData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_P7Output( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_P7Output( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignNotificationUI( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignNotificationUI( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DecryptUI( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DecryptUI( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ShowSelIDUI( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ShowSelIDUI( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportProfile( 
            VARIANT __RPC_FAR *in_pvarPassword,
            VARIANT in_varFlags,
            VARIANT __RPC_FAR *o_pvarProfileInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ImportProfile( 
            VARIANT __RPC_FAR *in_pvarPassword,
            VARIANT __RPC_FAR *in_pvarProfileData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreatePassword( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnterPassword( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSPTADllApiVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSPTADllApi __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSPTADllApi __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostFQDN )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostFQDN )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Protocol )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Protocol )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedIDCertContext )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DoAttachedSig )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DoAttachedSig )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowSignUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowSignUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OleClientSite )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OleClientSite )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashData )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashData )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_P7Output )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_P7Output )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SignNotificationUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignNotificationUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DecryptUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DecryptUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ShowSelIDUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ShowSelIDUI )( 
            IVSPTADllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportProfile )( 
            IVSPTADllApi __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPassword,
            VARIANT in_varFlags,
            VARIANT __RPC_FAR *o_pvarProfileInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ImportProfile )( 
            IVSPTADllApi __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPassword,
            VARIANT __RPC_FAR *in_pvarProfileData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreatePassword )( 
            IVSPTADllApi __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnterPassword )( 
            IVSPTADllApi __RPC_FAR * This);
        
        END_INTERFACE
    } IVSPTADllApiVtbl;

    interface IVSPTADllApi
    {
        CONST_VTBL struct IVSPTADllApiVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSPTADllApi_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSPTADllApi_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSPTADllApi_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSPTADllApi_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSPTADllApi_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSPTADllApi_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSPTADllApi_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSPTADllApi_get_HostFQDN(This,pVal)	\
    (This)->lpVtbl -> get_HostFQDN(This,pVal)

#define IVSPTADllApi_put_HostFQDN(This,newVal)	\
    (This)->lpVtbl -> put_HostFQDN(This,newVal)

#define IVSPTADllApi_get_Protocol(This,pVal)	\
    (This)->lpVtbl -> get_Protocol(This,pVal)

#define IVSPTADllApi_put_Protocol(This,newVal)	\
    (This)->lpVtbl -> put_Protocol(This,newVal)

#define IVSPTADllApi_get_SelectedIDCertContext(This,pVal)	\
    (This)->lpVtbl -> get_SelectedIDCertContext(This,pVal)

#define IVSPTADllApi_get_DoAttachedSig(This,pVal)	\
    (This)->lpVtbl -> get_DoAttachedSig(This,pVal)

#define IVSPTADllApi_put_DoAttachedSig(This,newVal)	\
    (This)->lpVtbl -> put_DoAttachedSig(This,newVal)

#define IVSPTADllApi_get_ShowSignUI(This,pVal)	\
    (This)->lpVtbl -> get_ShowSignUI(This,pVal)

#define IVSPTADllApi_put_ShowSignUI(This,newVal)	\
    (This)->lpVtbl -> put_ShowSignUI(This,newVal)

#define IVSPTADllApi_get_OleClientSite(This,pVal)	\
    (This)->lpVtbl -> get_OleClientSite(This,pVal)

#define IVSPTADllApi_put_OleClientSite(This,newVal)	\
    (This)->lpVtbl -> put_OleClientSite(This,newVal)

#define IVSPTADllApi_get_HashData(This,pVal)	\
    (This)->lpVtbl -> get_HashData(This,pVal)

#define IVSPTADllApi_put_HashData(This,newVal)	\
    (This)->lpVtbl -> put_HashData(This,newVal)

#define IVSPTADllApi_get_P7Output(This,pVal)	\
    (This)->lpVtbl -> get_P7Output(This,pVal)

#define IVSPTADllApi_put_P7Output(This,newVal)	\
    (This)->lpVtbl -> put_P7Output(This,newVal)

#define IVSPTADllApi_get_SignNotificationUI(This,pVal)	\
    (This)->lpVtbl -> get_SignNotificationUI(This,pVal)

#define IVSPTADllApi_put_SignNotificationUI(This,newVal)	\
    (This)->lpVtbl -> put_SignNotificationUI(This,newVal)

#define IVSPTADllApi_get_DecryptUI(This,pVal)	\
    (This)->lpVtbl -> get_DecryptUI(This,pVal)

#define IVSPTADllApi_put_DecryptUI(This,newVal)	\
    (This)->lpVtbl -> put_DecryptUI(This,newVal)

#define IVSPTADllApi_get_ShowSelIDUI(This,pVal)	\
    (This)->lpVtbl -> get_ShowSelIDUI(This,pVal)

#define IVSPTADllApi_put_ShowSelIDUI(This,newVal)	\
    (This)->lpVtbl -> put_ShowSelIDUI(This,newVal)

#define IVSPTADllApi_ExportProfile(This,in_pvarPassword,in_varFlags,o_pvarProfileInfo)	\
    (This)->lpVtbl -> ExportProfile(This,in_pvarPassword,in_varFlags,o_pvarProfileInfo)

#define IVSPTADllApi_ImportProfile(This,in_pvarPassword,in_pvarProfileData)	\
    (This)->lpVtbl -> ImportProfile(This,in_pvarPassword,in_pvarProfileData)

#define IVSPTADllApi_CreatePassword(This)	\
    (This)->lpVtbl -> CreatePassword(This)

#define IVSPTADllApi_EnterPassword(This)	\
    (This)->lpVtbl -> EnterPassword(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_HostFQDN_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_HostFQDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_HostFQDN_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_HostFQDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_Protocol_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_Protocol_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_SelectedIDCertContext_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_SelectedIDCertContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_DoAttachedSig_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_DoAttachedSig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_DoAttachedSig_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_DoAttachedSig_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_ShowSignUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_ShowSignUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_ShowSignUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_ShowSignUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_OleClientSite_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_OleClientSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_OleClientSite_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_OleClientSite_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_HashData_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_HashData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_HashData_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_HashData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_P7Output_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_P7Output_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_P7Output_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_P7Output_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_SignNotificationUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_SignNotificationUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_SignNotificationUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_SignNotificationUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_DecryptUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_DecryptUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_DecryptUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_DecryptUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_get_ShowSelIDUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTADllApi_get_ShowSelIDUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_put_ShowSelIDUI_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTADllApi_put_ShowSelIDUI_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_ExportProfile_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPassword,
    VARIANT in_varFlags,
    VARIANT __RPC_FAR *o_pvarProfileInfo);


void __RPC_STUB IVSPTADllApi_ExportProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_ImportProfile_Proxy( 
    IVSPTADllApi __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPassword,
    VARIANT __RPC_FAR *in_pvarProfileData);


void __RPC_STUB IVSPTADllApi_ImportProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_CreatePassword_Proxy( 
    IVSPTADllApi __RPC_FAR * This);


void __RPC_STUB IVSPTADllApi_CreatePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTADllApi_EnterPassword_Proxy( 
    IVSPTADllApi __RPC_FAR * This);


void __RPC_STUB IVSPTADllApi_EnterPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSPTADllApi_INTERFACE_DEFINED__ */


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
