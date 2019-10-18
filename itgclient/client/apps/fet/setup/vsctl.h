
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Sat Apr 01 14:56:30 2000
 */
/* Compiler settings for vsctl.idl:
    Os (OptLev=s), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __vsctl_h__
#define __vsctl_h__

/* Forward Declarations */ 

#ifndef __Ivsctrl_FWD_DEFINED__
#define __Ivsctrl_FWD_DEFINED__
typedef interface Ivsctrl Ivsctrl;
#endif 	/* __Ivsctrl_FWD_DEFINED__ */


#ifndef __vsctrl_FWD_DEFINED__
#define __vsctrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class vsctrl vsctrl;
#else
typedef struct vsctrl vsctrl;
#endif /* __cplusplus */

#endif 	/* __vsctrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_vsctl_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_vsctl_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_vsctl_0000_v0_0_s_ifspec;

#ifndef __Ivsctrl_INTERFACE_DEFINED__
#define __Ivsctrl_INTERFACE_DEFINED__

/* interface Ivsctrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_Ivsctrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C67604D-91A2-11D3-8C1B-0010830169AF")
    Ivsctrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetEnterpriseServer( 
            BSTR __MIDL_0011) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IvsctrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            Ivsctrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            Ivsctrl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            Ivsctrl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            Ivsctrl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            Ivsctrl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            Ivsctrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            Ivsctrl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEnterpriseServer )( 
            Ivsctrl __RPC_FAR * This,
            BSTR __MIDL_0011);
        
        END_INTERFACE
    } IvsctrlVtbl;

    interface Ivsctrl
    {
        CONST_VTBL struct IvsctrlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define Ivsctrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define Ivsctrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define Ivsctrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define Ivsctrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define Ivsctrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define Ivsctrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define Ivsctrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define Ivsctrl_SetEnterpriseServer(This,__MIDL_0011)	\
    (This)->lpVtbl -> SetEnterpriseServer(This,__MIDL_0011)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Ivsctrl_SetEnterpriseServer_Proxy( 
    Ivsctrl __RPC_FAR * This,
    BSTR __MIDL_0011);


void __RPC_STUB Ivsctrl_SetEnterpriseServer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __Ivsctrl_INTERFACE_DEFINED__ */



#ifndef __VSCTLLib_LIBRARY_DEFINED__
#define __VSCTLLib_LIBRARY_DEFINED__

/* library VSCTLLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VSCTLLib;

EXTERN_C const CLSID CLSID_vsctrl;

#ifdef __cplusplus

class DECLSPEC_UUID("6C67604E-91A2-11D3-8C1B-0010830169AF")
vsctrl;
#endif
#endif /* __VSCTLLib_LIBRARY_DEFINED__ */

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


