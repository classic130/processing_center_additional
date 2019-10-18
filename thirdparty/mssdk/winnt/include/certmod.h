/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Mon Jul 20 08:51:14 1998
 */
/* Compiler settings for certmod.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data , no_format_optimization
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __certmod_h__
#define __certmod_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICertManageModule_FWD_DEFINED__
#define __ICertManageModule_FWD_DEFINED__
typedef interface ICertManageModule ICertManageModule;
#endif 	/* __ICertManageModule_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ICertManageModule_INTERFACE_DEFINED__
#define __ICertManageModule_INTERFACE_DEFINED__

/* interface ICertManageModule */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICertManageModule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("e7d7ad42-bd3d-11d1-9a4d-00c04fc297eb")
    ICertManageModule : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCopyright( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrCopyRight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFileVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrFileVersion) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProductVersion( 
            /* [retval][out] */ BSTR __RPC_FAR *pstrProductVersion) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ const BSTR strConfig) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertManageModuleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertManageModule __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertManageModule __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertManageModule __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICertManageModule __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICertManageModule __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICertManageModule __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICertManageModule __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            ICertManageModule __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            ICertManageModule __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCopyright )( 
            ICertManageModule __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCopyRight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFileVersion )( 
            ICertManageModule __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrFileVersion);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProductVersion )( 
            ICertManageModule __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pstrProductVersion);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Configure )( 
            ICertManageModule __RPC_FAR * This,
            /* [in] */ const BSTR strConfig);
        
        END_INTERFACE
    } ICertManageModuleVtbl;

    interface ICertManageModule
    {
        CONST_VTBL struct ICertManageModuleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertManageModule_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertManageModule_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertManageModule_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertManageModule_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICertManageModule_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICertManageModule_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICertManageModule_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICertManageModule_GetName(This,pstrName)	\
    (This)->lpVtbl -> GetName(This,pstrName)

#define ICertManageModule_GetDescription(This,pstrDescription)	\
    (This)->lpVtbl -> GetDescription(This,pstrDescription)

#define ICertManageModule_GetCopyright(This,pstrCopyRight)	\
    (This)->lpVtbl -> GetCopyright(This,pstrCopyRight)

#define ICertManageModule_GetFileVersion(This,pstrFileVersion)	\
    (This)->lpVtbl -> GetFileVersion(This,pstrFileVersion)

#define ICertManageModule_GetProductVersion(This,pstrProductVersion)	\
    (This)->lpVtbl -> GetProductVersion(This,pstrProductVersion)

#define ICertManageModule_Configure(This,strConfig)	\
    (This)->lpVtbl -> Configure(This,strConfig)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertManageModule_GetName_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrName);


void __RPC_STUB ICertManageModule_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertManageModule_GetDescription_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrDescription);


void __RPC_STUB ICertManageModule_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertManageModule_GetCopyright_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrCopyRight);


void __RPC_STUB ICertManageModule_GetCopyright_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertManageModule_GetFileVersion_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrFileVersion);


void __RPC_STUB ICertManageModule_GetFileVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertManageModule_GetProductVersion_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pstrProductVersion);


void __RPC_STUB ICertManageModule_GetProductVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertManageModule_Configure_Proxy( 
    ICertManageModule __RPC_FAR * This,
    /* [in] */ const BSTR strConfig);


void __RPC_STUB ICertManageModule_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertManageModule_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
