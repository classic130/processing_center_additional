/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jun 18 10:26:58 1999
 */
/* Compiler settings for ImportPKCS12.idl:
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

#ifndef __ImportPKCS12_h__
#define __ImportPKCS12_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IImpPKCS12_FWD_DEFINED__
#define __IImpPKCS12_FWD_DEFINED__
typedef interface IImpPKCS12 IImpPKCS12;
#endif 	/* __IImpPKCS12_FWD_DEFINED__ */


#ifndef __ImpPKCS12_FWD_DEFINED__
#define __ImpPKCS12_FWD_DEFINED__

#ifdef __cplusplus
typedef class ImpPKCS12 ImpPKCS12;
#else
typedef struct ImpPKCS12 ImpPKCS12;
#endif /* __cplusplus */

#endif 	/* __ImpPKCS12_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IImpPKCS12_INTERFACE_DEFINED__
#define __IImpPKCS12_INTERFACE_DEFINED__

/* interface IImpPKCS12 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IImpPKCS12;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B1D475FD-75CD-11D2-8301-0060B0B32E16")
    IImpPKCS12 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Import( 
            VARIANT __RPC_FAR *i_pvarPKCS12,
            VARIANT __RPC_FAR *i_pvarPKCS7,
            VARIANT __RPC_FAR *o_pvarStatus,
            VARIANT __RPC_FAR *o_pvarErrorCode,
            VARIANT __RPC_FAR *o_pvarErrorCodeString) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyExportable( 
            /* [retval][out] */ BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyExportable( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProviderName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProviderName( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IImpPKCS12Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IImpPKCS12 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IImpPKCS12 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Import )( 
            IImpPKCS12 __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarPKCS12,
            VARIANT __RPC_FAR *i_pvarPKCS7,
            VARIANT __RPC_FAR *o_pvarStatus,
            VARIANT __RPC_FAR *o_pvarErrorCode,
            VARIANT __RPC_FAR *o_pvarErrorCodeString);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeyExportable )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeyExportable )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderName )( 
            IImpPKCS12 __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IImpPKCS12Vtbl;

    interface IImpPKCS12
    {
        CONST_VTBL struct IImpPKCS12Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IImpPKCS12_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IImpPKCS12_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IImpPKCS12_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IImpPKCS12_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IImpPKCS12_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IImpPKCS12_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IImpPKCS12_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IImpPKCS12_Import(This,i_pvarPKCS12,i_pvarPKCS7,o_pvarStatus,o_pvarErrorCode,o_pvarErrorCodeString)	\
    (This)->lpVtbl -> Import(This,i_pvarPKCS12,i_pvarPKCS7,o_pvarStatus,o_pvarErrorCode,o_pvarErrorCodeString)

#define IImpPKCS12_get_KeyExportable(This,pVal)	\
    (This)->lpVtbl -> get_KeyExportable(This,pVal)

#define IImpPKCS12_put_KeyExportable(This,newVal)	\
    (This)->lpVtbl -> put_KeyExportable(This,newVal)

#define IImpPKCS12_get_ProviderName(This,pVal)	\
    (This)->lpVtbl -> get_ProviderName(This,pVal)

#define IImpPKCS12_put_ProviderName(This,newVal)	\
    (This)->lpVtbl -> put_ProviderName(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IImpPKCS12_Import_Proxy( 
    IImpPKCS12 __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarPKCS12,
    VARIANT __RPC_FAR *i_pvarPKCS7,
    VARIANT __RPC_FAR *o_pvarStatus,
    VARIANT __RPC_FAR *o_pvarErrorCode,
    VARIANT __RPC_FAR *o_pvarErrorCodeString);


void __RPC_STUB IImpPKCS12_Import_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImpPKCS12_get_KeyExportable_Proxy( 
    IImpPKCS12 __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *pVal);


void __RPC_STUB IImpPKCS12_get_KeyExportable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImpPKCS12_put_KeyExportable_Proxy( 
    IImpPKCS12 __RPC_FAR * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IImpPKCS12_put_KeyExportable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IImpPKCS12_get_ProviderName_Proxy( 
    IImpPKCS12 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IImpPKCS12_get_ProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IImpPKCS12_put_ProviderName_Proxy( 
    IImpPKCS12 __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IImpPKCS12_put_ProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IImpPKCS12_INTERFACE_DEFINED__ */



#ifndef __IMPORTPKCS12Lib_LIBRARY_DEFINED__
#define __IMPORTPKCS12Lib_LIBRARY_DEFINED__

/* library IMPORTPKCS12Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_IMPORTPKCS12Lib;

EXTERN_C const CLSID CLSID_ImpPKCS12;

#ifdef __cplusplus

class DECLSPEC_UUID("B1D475FE-75CD-11D2-8301-0060B0B32E16")
ImpPKCS12;
#endif
#endif /* __IMPORTPKCS12Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
