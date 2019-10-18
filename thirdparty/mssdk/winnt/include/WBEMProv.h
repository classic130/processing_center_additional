/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 17 12:00:10 1998
 */
/* Compiler settings for wbemprov.idl:
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

#ifndef __wbemprov_h__
#define __wbemprov_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IWbemPropertyProvider_FWD_DEFINED__
#define __IWbemPropertyProvider_FWD_DEFINED__
typedef interface IWbemPropertyProvider IWbemPropertyProvider;
#endif 	/* __IWbemPropertyProvider_FWD_DEFINED__ */


#ifndef __IWbemUnboundObjectSink_FWD_DEFINED__
#define __IWbemUnboundObjectSink_FWD_DEFINED__
typedef interface IWbemUnboundObjectSink IWbemUnboundObjectSink;
#endif 	/* __IWbemUnboundObjectSink_FWD_DEFINED__ */


#ifndef __IWbemEventProvider_FWD_DEFINED__
#define __IWbemEventProvider_FWD_DEFINED__
typedef interface IWbemEventProvider IWbemEventProvider;
#endif 	/* __IWbemEventProvider_FWD_DEFINED__ */


#ifndef __IWbemEventProviderQuerySink_FWD_DEFINED__
#define __IWbemEventProviderQuerySink_FWD_DEFINED__
typedef interface IWbemEventProviderQuerySink IWbemEventProviderQuerySink;
#endif 	/* __IWbemEventProviderQuerySink_FWD_DEFINED__ */


#ifndef __IWbemEventConsumerProvider_FWD_DEFINED__
#define __IWbemEventConsumerProvider_FWD_DEFINED__
typedef interface IWbemEventConsumerProvider IWbemEventConsumerProvider;
#endif 	/* __IWbemEventConsumerProvider_FWD_DEFINED__ */


#ifndef __IWbemProviderInitSink_FWD_DEFINED__
#define __IWbemProviderInitSink_FWD_DEFINED__
typedef interface IWbemProviderInitSink IWbemProviderInitSink;
#endif 	/* __IWbemProviderInitSink_FWD_DEFINED__ */


#ifndef __IWbemProviderInit_FWD_DEFINED__
#define __IWbemProviderInit_FWD_DEFINED__
typedef interface IWbemProviderInit IWbemProviderInit;
#endif 	/* __IWbemProviderInit_FWD_DEFINED__ */


#ifndef __WbemAdministrativeLocator_FWD_DEFINED__
#define __WbemAdministrativeLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class WbemAdministrativeLocator WbemAdministrativeLocator;
#else
typedef struct WbemAdministrativeLocator WbemAdministrativeLocator;
#endif /* __cplusplus */

#endif 	/* __WbemAdministrativeLocator_FWD_DEFINED__ */


#ifndef __WbemAuthenticatedLocator_FWD_DEFINED__
#define __WbemAuthenticatedLocator_FWD_DEFINED__

#ifdef __cplusplus
typedef class WbemAuthenticatedLocator WbemAuthenticatedLocator;
#else
typedef struct WbemAuthenticatedLocator WbemAuthenticatedLocator;
#endif /* __cplusplus */

#endif 	/* __WbemAuthenticatedLocator_FWD_DEFINED__ */


#ifndef __IWbemUnboundObjectSink_FWD_DEFINED__
#define __IWbemUnboundObjectSink_FWD_DEFINED__
typedef interface IWbemUnboundObjectSink IWbemUnboundObjectSink;
#endif 	/* __IWbemUnboundObjectSink_FWD_DEFINED__ */


#ifndef __IWbemPropertyProvider_FWD_DEFINED__
#define __IWbemPropertyProvider_FWD_DEFINED__
typedef interface IWbemPropertyProvider IWbemPropertyProvider;
#endif 	/* __IWbemPropertyProvider_FWD_DEFINED__ */


#ifndef __IWbemEventProvider_FWD_DEFINED__
#define __IWbemEventProvider_FWD_DEFINED__
typedef interface IWbemEventProvider IWbemEventProvider;
#endif 	/* __IWbemEventProvider_FWD_DEFINED__ */


#ifndef __IWbemEventProviderQuerySink_FWD_DEFINED__
#define __IWbemEventProviderQuerySink_FWD_DEFINED__
typedef interface IWbemEventProviderQuerySink IWbemEventProviderQuerySink;
#endif 	/* __IWbemEventProviderQuerySink_FWD_DEFINED__ */


#ifndef __IWbemEventConsumerProvider_FWD_DEFINED__
#define __IWbemEventConsumerProvider_FWD_DEFINED__
typedef interface IWbemEventConsumerProvider IWbemEventConsumerProvider;
#endif 	/* __IWbemEventConsumerProvider_FWD_DEFINED__ */


#ifndef __IWbemProviderInitSink_FWD_DEFINED__
#define __IWbemProviderInitSink_FWD_DEFINED__
typedef interface IWbemProviderInitSink IWbemProviderInitSink;
#endif 	/* __IWbemProviderInitSink_FWD_DEFINED__ */


#ifndef __IWbemProviderInit_FWD_DEFINED__
#define __IWbemProviderInit_FWD_DEFINED__
typedef interface IWbemProviderInit IWbemProviderInit;
#endif 	/* __IWbemProviderInit_FWD_DEFINED__ */


/* header files for imported files */
#include "objidl.h"
#include "oleidl.h"
#include "oaidl.h"
#include "wbemcli.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_wbemprov_0000 */
/* [local] */ 

typedef VARIANT WBEM_VARIANT;

typedef /* [string] */ WCHAR __RPC_FAR *WBEM_WSTR;



extern RPC_IF_HANDLE __MIDL_itf_wbemprov_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wbemprov_0000_v0_0_s_ifspec;


#ifndef __WbemProviders_v1_LIBRARY_DEFINED__
#define __WbemProviders_v1_LIBRARY_DEFINED__

/* library WbemProviders_v1 */
/* [uuid] */ 









EXTERN_C const IID LIBID_WbemProviders_v1;

#ifndef __IWbemPropertyProvider_INTERFACE_DEFINED__
#define __IWbemPropertyProvider_INTERFACE_DEFINED__

/* interface IWbemPropertyProvider */
/* [uuid][local][object][restricted] */ 


EXTERN_C const IID IID_IWbemPropertyProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE61E841-65BC-11d0-B6BD-00AA003240C7")
    IWbemPropertyProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ long lFlags,
            /* [in] */ BSTR strLocale,
            /* [in] */ BSTR strClassMapping,
            /* [in] */ BSTR strInstMapping,
            /* [in] */ BSTR strPropMapping,
            /* [out] */ VARIANT __RPC_FAR *pvValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PutProperty( 
            /* [in] */ long lFlags,
            /* [in] */ BSTR strLocale,
            /* [in] */ BSTR strClassMapping,
            /* [in] */ BSTR strInstMapping,
            /* [in] */ BSTR strPropMapping,
            /* [in] */ VARIANT __RPC_FAR *pvValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemPropertyProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemPropertyProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemPropertyProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemPropertyProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            IWbemPropertyProvider __RPC_FAR * This,
            /* [in] */ long lFlags,
            /* [in] */ BSTR strLocale,
            /* [in] */ BSTR strClassMapping,
            /* [in] */ BSTR strInstMapping,
            /* [in] */ BSTR strPropMapping,
            /* [out] */ VARIANT __RPC_FAR *pvValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PutProperty )( 
            IWbemPropertyProvider __RPC_FAR * This,
            /* [in] */ long lFlags,
            /* [in] */ BSTR strLocale,
            /* [in] */ BSTR strClassMapping,
            /* [in] */ BSTR strInstMapping,
            /* [in] */ BSTR strPropMapping,
            /* [in] */ VARIANT __RPC_FAR *pvValue);
        
        END_INTERFACE
    } IWbemPropertyProviderVtbl;

    interface IWbemPropertyProvider
    {
        CONST_VTBL struct IWbemPropertyProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemPropertyProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemPropertyProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemPropertyProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemPropertyProvider_GetProperty(This,lFlags,strLocale,strClassMapping,strInstMapping,strPropMapping,pvValue)	\
    (This)->lpVtbl -> GetProperty(This,lFlags,strLocale,strClassMapping,strInstMapping,strPropMapping,pvValue)

#define IWbemPropertyProvider_PutProperty(This,lFlags,strLocale,strClassMapping,strInstMapping,strPropMapping,pvValue)	\
    (This)->lpVtbl -> PutProperty(This,lFlags,strLocale,strClassMapping,strInstMapping,strPropMapping,pvValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemPropertyProvider_GetProperty_Proxy( 
    IWbemPropertyProvider __RPC_FAR * This,
    /* [in] */ long lFlags,
    /* [in] */ BSTR strLocale,
    /* [in] */ BSTR strClassMapping,
    /* [in] */ BSTR strInstMapping,
    /* [in] */ BSTR strPropMapping,
    /* [out] */ VARIANT __RPC_FAR *pvValue);


void __RPC_STUB IWbemPropertyProvider_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWbemPropertyProvider_PutProperty_Proxy( 
    IWbemPropertyProvider __RPC_FAR * This,
    /* [in] */ long lFlags,
    /* [in] */ BSTR strLocale,
    /* [in] */ BSTR strClassMapping,
    /* [in] */ BSTR strInstMapping,
    /* [in] */ BSTR strPropMapping,
    /* [in] */ VARIANT __RPC_FAR *pvValue);


void __RPC_STUB IWbemPropertyProvider_PutProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemPropertyProvider_INTERFACE_DEFINED__ */


#ifndef __IWbemUnboundObjectSink_INTERFACE_DEFINED__
#define __IWbemUnboundObjectSink_INTERFACE_DEFINED__

/* interface IWbemUnboundObjectSink */
/* [uuid][object][restricted] */ 


EXTERN_C const IID IID_IWbemUnboundObjectSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e246107b-b06e-11d0-ad61-00c04fd8fdff")
    IWbemUnboundObjectSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IndicateToConsumer( 
            /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
            /* [in] */ long lNumObjects,
            /* [size_is][in] */ IWbemClassObject __RPC_FAR *__RPC_FAR *apObjects) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemUnboundObjectSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemUnboundObjectSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemUnboundObjectSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemUnboundObjectSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IndicateToConsumer )( 
            IWbemUnboundObjectSink __RPC_FAR * This,
            /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
            /* [in] */ long lNumObjects,
            /* [size_is][in] */ IWbemClassObject __RPC_FAR *__RPC_FAR *apObjects);
        
        END_INTERFACE
    } IWbemUnboundObjectSinkVtbl;

    interface IWbemUnboundObjectSink
    {
        CONST_VTBL struct IWbemUnboundObjectSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemUnboundObjectSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemUnboundObjectSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemUnboundObjectSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemUnboundObjectSink_IndicateToConsumer(This,pLogicalConsumer,lNumObjects,apObjects)	\
    (This)->lpVtbl -> IndicateToConsumer(This,pLogicalConsumer,lNumObjects,apObjects)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemUnboundObjectSink_IndicateToConsumer_Proxy( 
    IWbemUnboundObjectSink __RPC_FAR * This,
    /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
    /* [in] */ long lNumObjects,
    /* [size_is][in] */ IWbemClassObject __RPC_FAR *__RPC_FAR *apObjects);


void __RPC_STUB IWbemUnboundObjectSink_IndicateToConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemUnboundObjectSink_INTERFACE_DEFINED__ */


#ifndef __IWbemEventProvider_INTERFACE_DEFINED__
#define __IWbemEventProvider_INTERFACE_DEFINED__

/* interface IWbemEventProvider */
/* [uuid][object][restricted] */ 


EXTERN_C const IID IID_IWbemEventProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e245105b-b06e-11d0-ad61-00c04fd8fdff")
    IWbemEventProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ProvideEvents( 
            /* [in] */ IWbemObjectSink __RPC_FAR *pSink,
            /* [in] */ long lFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemEventProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemEventProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemEventProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemEventProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ProvideEvents )( 
            IWbemEventProvider __RPC_FAR * This,
            /* [in] */ IWbemObjectSink __RPC_FAR *pSink,
            /* [in] */ long lFlags);
        
        END_INTERFACE
    } IWbemEventProviderVtbl;

    interface IWbemEventProvider
    {
        CONST_VTBL struct IWbemEventProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemEventProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemEventProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemEventProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemEventProvider_ProvideEvents(This,pSink,lFlags)	\
    (This)->lpVtbl -> ProvideEvents(This,pSink,lFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemEventProvider_ProvideEvents_Proxy( 
    IWbemEventProvider __RPC_FAR * This,
    /* [in] */ IWbemObjectSink __RPC_FAR *pSink,
    /* [in] */ long lFlags);


void __RPC_STUB IWbemEventProvider_ProvideEvents_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemEventProvider_INTERFACE_DEFINED__ */


#ifndef __IWbemEventProviderQuerySink_INTERFACE_DEFINED__
#define __IWbemEventProviderQuerySink_INTERFACE_DEFINED__

/* interface IWbemEventProviderQuerySink */
/* [uuid][object][restricted] */ 


EXTERN_C const IID IID_IWbemEventProviderQuerySink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("580acaf8-fa1c-11d0-ad72-00c04fd8fdff")
    IWbemEventProviderQuerySink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE NewQuery( 
            /* [in] */ unsigned long dwId,
            /* [in] */ WBEM_WSTR wszQueryLanguage,
            /* [in] */ WBEM_WSTR wszQuery) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelQuery( 
            /* [in] */ unsigned long dwId) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemEventProviderQuerySinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemEventProviderQuerySink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemEventProviderQuerySink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemEventProviderQuerySink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NewQuery )( 
            IWbemEventProviderQuerySink __RPC_FAR * This,
            /* [in] */ unsigned long dwId,
            /* [in] */ WBEM_WSTR wszQueryLanguage,
            /* [in] */ WBEM_WSTR wszQuery);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelQuery )( 
            IWbemEventProviderQuerySink __RPC_FAR * This,
            /* [in] */ unsigned long dwId);
        
        END_INTERFACE
    } IWbemEventProviderQuerySinkVtbl;

    interface IWbemEventProviderQuerySink
    {
        CONST_VTBL struct IWbemEventProviderQuerySinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemEventProviderQuerySink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemEventProviderQuerySink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemEventProviderQuerySink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemEventProviderQuerySink_NewQuery(This,dwId,wszQueryLanguage,wszQuery)	\
    (This)->lpVtbl -> NewQuery(This,dwId,wszQueryLanguage,wszQuery)

#define IWbemEventProviderQuerySink_CancelQuery(This,dwId)	\
    (This)->lpVtbl -> CancelQuery(This,dwId)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemEventProviderQuerySink_NewQuery_Proxy( 
    IWbemEventProviderQuerySink __RPC_FAR * This,
    /* [in] */ unsigned long dwId,
    /* [in] */ WBEM_WSTR wszQueryLanguage,
    /* [in] */ WBEM_WSTR wszQuery);


void __RPC_STUB IWbemEventProviderQuerySink_NewQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IWbemEventProviderQuerySink_CancelQuery_Proxy( 
    IWbemEventProviderQuerySink __RPC_FAR * This,
    /* [in] */ unsigned long dwId);


void __RPC_STUB IWbemEventProviderQuerySink_CancelQuery_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemEventProviderQuerySink_INTERFACE_DEFINED__ */


#ifndef __IWbemEventConsumerProvider_INTERFACE_DEFINED__
#define __IWbemEventConsumerProvider_INTERFACE_DEFINED__

/* interface IWbemEventConsumerProvider */
/* [uuid][object][restricted] */ 


EXTERN_C const IID IID_IWbemEventConsumerProvider;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e246107a-b06e-11d0-ad61-00c04fd8fdff")
    IWbemEventConsumerProvider : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE FindConsumer( 
            /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
            /* [out] */ IWbemUnboundObjectSink __RPC_FAR *__RPC_FAR *ppConsumer) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemEventConsumerProviderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemEventConsumerProvider __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemEventConsumerProvider __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemEventConsumerProvider __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FindConsumer )( 
            IWbemEventConsumerProvider __RPC_FAR * This,
            /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
            /* [out] */ IWbemUnboundObjectSink __RPC_FAR *__RPC_FAR *ppConsumer);
        
        END_INTERFACE
    } IWbemEventConsumerProviderVtbl;

    interface IWbemEventConsumerProvider
    {
        CONST_VTBL struct IWbemEventConsumerProviderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemEventConsumerProvider_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemEventConsumerProvider_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemEventConsumerProvider_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemEventConsumerProvider_FindConsumer(This,pLogicalConsumer,ppConsumer)	\
    (This)->lpVtbl -> FindConsumer(This,pLogicalConsumer,ppConsumer)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemEventConsumerProvider_FindConsumer_Proxy( 
    IWbemEventConsumerProvider __RPC_FAR * This,
    /* [in] */ IWbemClassObject __RPC_FAR *pLogicalConsumer,
    /* [out] */ IWbemUnboundObjectSink __RPC_FAR *__RPC_FAR *ppConsumer);


void __RPC_STUB IWbemEventConsumerProvider_FindConsumer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemEventConsumerProvider_INTERFACE_DEFINED__ */


#ifndef __IWbemProviderInitSink_INTERFACE_DEFINED__
#define __IWbemProviderInitSink_INTERFACE_DEFINED__

/* interface IWbemProviderInitSink */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWbemProviderInitSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1be41571-91dd-11d1-aeb2-00c04fb68820")
    IWbemProviderInitSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetStatus( 
            /* [in] */ LONG lStatus,
            /* [in] */ LONG lFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemProviderInitSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemProviderInitSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemProviderInitSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemProviderInitSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStatus )( 
            IWbemProviderInitSink __RPC_FAR * This,
            /* [in] */ LONG lStatus,
            /* [in] */ LONG lFlags);
        
        END_INTERFACE
    } IWbemProviderInitSinkVtbl;

    interface IWbemProviderInitSink
    {
        CONST_VTBL struct IWbemProviderInitSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemProviderInitSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemProviderInitSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemProviderInitSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemProviderInitSink_SetStatus(This,lStatus,lFlags)	\
    (This)->lpVtbl -> SetStatus(This,lStatus,lFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemProviderInitSink_SetStatus_Proxy( 
    IWbemProviderInitSink __RPC_FAR * This,
    /* [in] */ LONG lStatus,
    /* [in] */ LONG lFlags);


void __RPC_STUB IWbemProviderInitSink_SetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemProviderInitSink_INTERFACE_DEFINED__ */


#ifndef __IWbemProviderInit_INTERFACE_DEFINED__
#define __IWbemProviderInit_INTERFACE_DEFINED__

/* interface IWbemProviderInit */
/* [uuid][object] */ 


EXTERN_C const IID IID_IWbemProviderInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1be41572-91dd-11d1-aeb2-00c04fb68820")
    IWbemProviderInit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [unique][in] */ LPWSTR wszUser,
            /* [in] */ LONG lFlags,
            /* [in] */ LPWSTR wszNamespace,
            /* [unique][in] */ LPWSTR wszLocale,
            /* [in] */ IWbemServices __RPC_FAR *pNamespace,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemProviderInitSink __RPC_FAR *pInitSink) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWbemProviderInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IWbemProviderInit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IWbemProviderInit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IWbemProviderInit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IWbemProviderInit __RPC_FAR * This,
            /* [unique][in] */ LPWSTR wszUser,
            /* [in] */ LONG lFlags,
            /* [in] */ LPWSTR wszNamespace,
            /* [unique][in] */ LPWSTR wszLocale,
            /* [in] */ IWbemServices __RPC_FAR *pNamespace,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemProviderInitSink __RPC_FAR *pInitSink);
        
        END_INTERFACE
    } IWbemProviderInitVtbl;

    interface IWbemProviderInit
    {
        CONST_VTBL struct IWbemProviderInitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWbemProviderInit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWbemProviderInit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWbemProviderInit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWbemProviderInit_Initialize(This,wszUser,lFlags,wszNamespace,wszLocale,pNamespace,pCtx,pInitSink)	\
    (This)->lpVtbl -> Initialize(This,wszUser,lFlags,wszNamespace,wszLocale,pNamespace,pCtx,pInitSink)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IWbemProviderInit_Initialize_Proxy( 
    IWbemProviderInit __RPC_FAR * This,
    /* [unique][in] */ LPWSTR wszUser,
    /* [in] */ LONG lFlags,
    /* [in] */ LPWSTR wszNamespace,
    /* [unique][in] */ LPWSTR wszLocale,
    /* [in] */ IWbemServices __RPC_FAR *pNamespace,
    /* [in] */ IWbemContext __RPC_FAR *pCtx,
    /* [in] */ IWbemProviderInitSink __RPC_FAR *pInitSink);


void __RPC_STUB IWbemProviderInit_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWbemProviderInit_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WbemAdministrativeLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("cb8555cc-9128-11d1-ad9b-00c04fd8fdff")
WbemAdministrativeLocator;
#endif

EXTERN_C const CLSID CLSID_WbemAuthenticatedLocator;

#ifdef __cplusplus

class DECLSPEC_UUID("cd184336-9128-11d1-ad9b-00c04fd8fdff")
WbemAuthenticatedLocator;
#endif
#endif /* __WbemProviders_v1_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_wbemprov_0147 */
/* [local] */ 

typedef 
enum tag_WBEM_EXTRA_RETURN_CODES
    {	WBEM_S_INITIALIZED	= 0,
	WBEM_S_LIMITED_SERVICE	= 0x43001,
	WBEM_S_INDIRECTLY_UPDATED	= WBEM_S_LIMITED_SERVICE + 1,
	WBEM_E_RETRY_LATER	= 0x80043001,
	WBEM_E_RESOURCE_CONTENTION	= WBEM_E_RETRY_LATER + 1
    }	WBEM_EXTRA_RETURN_CODES;

typedef 
enum tag_WBEM_PROVIDER_FLAGS
    {	WBEM_FLAG_OWNER_UPDATE	= 0x10000
    }	WBEM_PROVIDER_FLAGS;



extern RPC_IF_HANDLE __MIDL_itf_wbemprov_0147_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_wbemprov_0147_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
