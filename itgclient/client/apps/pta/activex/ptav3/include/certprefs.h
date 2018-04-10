/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 06 15:51:26 2003
 */
/* Compiler settings for F:\gswa_v6_0\itgclient\client\apps\pta\activex\ptav3\source\certprefs.idl:
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

#ifndef __certprefs_h__
#define __certprefs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSCertPrefs_FWD_DEFINED__
#define __IVSCertPrefs_FWD_DEFINED__
typedef interface IVSCertPrefs IVSCertPrefs;
#endif 	/* __IVSCertPrefs_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_certprefs_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_certprefs_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certprefs_0000_v0_0_s_ifspec;

#ifndef __IVSCertPrefs_INTERFACE_DEFINED__
#define __IVSCertPrefs_INTERFACE_DEFINED__

/* interface IVSCertPrefs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSCertPrefs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d962f4c1-ddb0-11d3-a428-d1a369ca484f")
    IVSCertPrefs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertSerNum( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertSerNum( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertIssDN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertIssDN( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertFrndlyName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertFrndlyName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertLogoUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertLogoUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertDispString( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertDispString( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertTextureUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertTextureUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MarkAsRenewed( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MarkAsRenewed( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetPreference( 
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetPreference( 
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSCertPrefsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSCertPrefs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSCertPrefs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertSerNum )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertSerNum )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertIssDN )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertIssDN )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertFrndlyName )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertFrndlyName )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertLogoUrl )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertLogoUrl )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertDispString )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertDispString )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertTextureUrl )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertTextureUrl )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MarkAsRenewed )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MarkAsRenewed )( 
            IVSCertPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPreference )( 
            IVSCertPrefs __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPreference )( 
            IVSCertPrefs __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue);
        
        END_INTERFACE
    } IVSCertPrefsVtbl;

    interface IVSCertPrefs
    {
        CONST_VTBL struct IVSCertPrefsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSCertPrefs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSCertPrefs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSCertPrefs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSCertPrefs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSCertPrefs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSCertPrefs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSCertPrefs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSCertPrefs_get_CertSerNum(This,pVal)	\
    (This)->lpVtbl -> get_CertSerNum(This,pVal)

#define IVSCertPrefs_put_CertSerNum(This,newVal)	\
    (This)->lpVtbl -> put_CertSerNum(This,newVal)

#define IVSCertPrefs_get_CertIssDN(This,pVal)	\
    (This)->lpVtbl -> get_CertIssDN(This,pVal)

#define IVSCertPrefs_put_CertIssDN(This,newVal)	\
    (This)->lpVtbl -> put_CertIssDN(This,newVal)

#define IVSCertPrefs_get_CertFrndlyName(This,pVal)	\
    (This)->lpVtbl -> get_CertFrndlyName(This,pVal)

#define IVSCertPrefs_put_CertFrndlyName(This,newVal)	\
    (This)->lpVtbl -> put_CertFrndlyName(This,newVal)

#define IVSCertPrefs_get_CertLogoUrl(This,pVal)	\
    (This)->lpVtbl -> get_CertLogoUrl(This,pVal)

#define IVSCertPrefs_put_CertLogoUrl(This,newVal)	\
    (This)->lpVtbl -> put_CertLogoUrl(This,newVal)

#define IVSCertPrefs_get_CertDispString(This,pVal)	\
    (This)->lpVtbl -> get_CertDispString(This,pVal)

#define IVSCertPrefs_put_CertDispString(This,newVal)	\
    (This)->lpVtbl -> put_CertDispString(This,newVal)

#define IVSCertPrefs_get_CertTextureUrl(This,pVal)	\
    (This)->lpVtbl -> get_CertTextureUrl(This,pVal)

#define IVSCertPrefs_put_CertTextureUrl(This,newVal)	\
    (This)->lpVtbl -> put_CertTextureUrl(This,newVal)

#define IVSCertPrefs_get_MarkAsRenewed(This,pVal)	\
    (This)->lpVtbl -> get_MarkAsRenewed(This,pVal)

#define IVSCertPrefs_put_MarkAsRenewed(This,newVal)	\
    (This)->lpVtbl -> put_MarkAsRenewed(This,newVal)

#define IVSCertPrefs_SetPreference(This,in_pvarPrefName,in_pvarPrefValue)	\
    (This)->lpVtbl -> SetPreference(This,in_pvarPrefName,in_pvarPrefValue)

#define IVSCertPrefs_GetPreference(This,in_pvarPrefName,in_pvarPrefValue)	\
    (This)->lpVtbl -> GetPreference(This,in_pvarPrefName,in_pvarPrefValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertSerNum_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertSerNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertSerNum_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertSerNum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertIssDN_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertIssDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertIssDN_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertIssDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertFrndlyName_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertFrndlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertFrndlyName_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertFrndlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertLogoUrl_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertLogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertLogoUrl_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertLogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertDispString_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertDispString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertDispString_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertDispString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_CertTextureUrl_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_CertTextureUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_CertTextureUrl_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_CertTextureUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_get_MarkAsRenewed_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSCertPrefs_get_MarkAsRenewed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_put_MarkAsRenewed_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSCertPrefs_put_MarkAsRenewed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_SetPreference_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPrefName,
    VARIANT __RPC_FAR *in_pvarPrefValue);


void __RPC_STUB IVSCertPrefs_SetPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSCertPrefs_GetPreference_Proxy( 
    IVSCertPrefs __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPrefName,
    VARIANT __RPC_FAR *in_pvarPrefValue);


void __RPC_STUB IVSCertPrefs_GetPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSCertPrefs_INTERFACE_DEFINED__ */


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
