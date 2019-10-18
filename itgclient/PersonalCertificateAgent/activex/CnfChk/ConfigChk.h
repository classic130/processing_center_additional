/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 29 16:04:40 2006
 */
/* Compiler settings for .\ConfigChk.idl:
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

#ifndef __ConfigChk_h__
#define __ConfigChk_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IConfigChkr_FWD_DEFINED__
#define __IConfigChkr_FWD_DEFINED__
typedef interface IConfigChkr IConfigChkr;
#endif 	/* __IConfigChkr_FWD_DEFINED__ */


#ifndef __ConfigChkr_FWD_DEFINED__
#define __ConfigChkr_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConfigChkr ConfigChkr;
#else
typedef struct ConfigChkr ConfigChkr;
#endif /* __cplusplus */

#endif 	/* __ConfigChkr_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IConfigChkr_INTERFACE_DEFINED__
#define __IConfigChkr_INTERFACE_DEFINED__

/* interface IConfigChkr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IConfigChkr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("08F04138-8DFC-11D2-80E9-006008B066EE")
    IConfigChkr : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetVersion( 
            VARIANT __RPC_FAR *i_pvarFile,
            VARIANT __RPC_FAR *o_pvarVersion,
            /* [retval][out] */ long __RPC_FAR *o_lResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE VerCompare( 
            VARIANT __RPC_FAR *i_pvarVer1,
            VARIANT __RPC_FAR *i_pvarVer2,
            /* [retval][out] */ long __RPC_FAR *o_plResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckMSEnhCSP( 
            /* [retval][out] */ long __RPC_FAR *o_lRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FixEnhCSP( 
            VARIANT __RPC_FAR *i_pvarEnhCSPVer,
            /* [retval][out] */ long __RPC_FAR *o_plRetVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChkWindowsLogin( 
            /* [retval][out] */ long __RPC_FAR *o_lResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckKeyGen( 
            VARIANT __RPC_FAR *i_pvarProvName,
            VARIANT __RPC_FAR *i_pvarKeyFlags,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigChkrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConfigChkr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConfigChkr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConfigChkr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IConfigChkr __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IConfigChkr __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IConfigChkr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IConfigChkr __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersion )( 
            IConfigChkr __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarFile,
            VARIANT __RPC_FAR *o_pvarVersion,
            /* [retval][out] */ long __RPC_FAR *o_lResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *VerCompare )( 
            IConfigChkr __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarVer1,
            VARIANT __RPC_FAR *i_pvarVer2,
            /* [retval][out] */ long __RPC_FAR *o_plResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckMSEnhCSP )( 
            IConfigChkr __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *o_lRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *FixEnhCSP )( 
            IConfigChkr __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarEnhCSPVer,
            /* [retval][out] */ long __RPC_FAR *o_plRetVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChkWindowsLogin )( 
            IConfigChkr __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *o_lResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckKeyGen )( 
            IConfigChkr __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarProvName,
            VARIANT __RPC_FAR *i_pvarKeyFlags,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarResult);
        
        END_INTERFACE
    } IConfigChkrVtbl;

    interface IConfigChkr
    {
        CONST_VTBL struct IConfigChkrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigChkr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigChkr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigChkr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigChkr_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IConfigChkr_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IConfigChkr_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IConfigChkr_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IConfigChkr_GetVersion(This,i_pvarFile,o_pvarVersion,o_lResult)	\
    (This)->lpVtbl -> GetVersion(This,i_pvarFile,o_pvarVersion,o_lResult)

#define IConfigChkr_VerCompare(This,i_pvarVer1,i_pvarVer2,o_plResult)	\
    (This)->lpVtbl -> VerCompare(This,i_pvarVer1,i_pvarVer2,o_plResult)

#define IConfigChkr_CheckMSEnhCSP(This,o_lRetVal)	\
    (This)->lpVtbl -> CheckMSEnhCSP(This,o_lRetVal)

#define IConfigChkr_FixEnhCSP(This,i_pvarEnhCSPVer,o_plRetVal)	\
    (This)->lpVtbl -> FixEnhCSP(This,i_pvarEnhCSPVer,o_plRetVal)

#define IConfigChkr_ChkWindowsLogin(This,o_lResult)	\
    (This)->lpVtbl -> ChkWindowsLogin(This,o_lResult)

#define IConfigChkr_CheckKeyGen(This,i_pvarProvName,i_pvarKeyFlags,o_pvarResult)	\
    (This)->lpVtbl -> CheckKeyGen(This,i_pvarProvName,i_pvarKeyFlags,o_pvarResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_GetVersion_Proxy( 
    IConfigChkr __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarFile,
    VARIANT __RPC_FAR *o_pvarVersion,
    /* [retval][out] */ long __RPC_FAR *o_lResult);


void __RPC_STUB IConfigChkr_GetVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_VerCompare_Proxy( 
    IConfigChkr __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarVer1,
    VARIANT __RPC_FAR *i_pvarVer2,
    /* [retval][out] */ long __RPC_FAR *o_plResult);


void __RPC_STUB IConfigChkr_VerCompare_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_CheckMSEnhCSP_Proxy( 
    IConfigChkr __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *o_lRetVal);


void __RPC_STUB IConfigChkr_CheckMSEnhCSP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_FixEnhCSP_Proxy( 
    IConfigChkr __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarEnhCSPVer,
    /* [retval][out] */ long __RPC_FAR *o_plRetVal);


void __RPC_STUB IConfigChkr_FixEnhCSP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_ChkWindowsLogin_Proxy( 
    IConfigChkr __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *o_lResult);


void __RPC_STUB IConfigChkr_ChkWindowsLogin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IConfigChkr_CheckKeyGen_Proxy( 
    IConfigChkr __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarProvName,
    VARIANT __RPC_FAR *i_pvarKeyFlags,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarResult);


void __RPC_STUB IConfigChkr_CheckKeyGen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigChkr_INTERFACE_DEFINED__ */



#ifndef __CONFIGCHKLib_LIBRARY_DEFINED__
#define __CONFIGCHKLib_LIBRARY_DEFINED__

/* library CONFIGCHKLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CONFIGCHKLib;

EXTERN_C const CLSID CLSID_ConfigChkr;

#ifdef __cplusplus

class DECLSPEC_UUID("08F04139-8DFC-11D2-80E9-006008B066EE")
ConfigChkr;
#endif
#endif /* __CONFIGCHKLib_LIBRARY_DEFINED__ */

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
