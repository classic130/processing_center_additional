/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Sun Aug 02 12:56:11 1998
 */
/* Compiler settings for mdhcp.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data , no_format_optimization
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

#ifndef __mdhcp_h__
#define __mdhcp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMDhcpScope_FWD_DEFINED__
#define __IMDhcpScope_FWD_DEFINED__
typedef interface IMDhcpScope IMDhcpScope;
#endif 	/* __IMDhcpScope_FWD_DEFINED__ */


#ifndef __IEnumBstr_FWD_DEFINED__
#define __IEnumBstr_FWD_DEFINED__
typedef interface IEnumBstr IEnumBstr;
#endif 	/* __IEnumBstr_FWD_DEFINED__ */


#ifndef __IMDhcpLeaseInfo_FWD_DEFINED__
#define __IMDhcpLeaseInfo_FWD_DEFINED__
typedef interface IMDhcpLeaseInfo IMDhcpLeaseInfo;
#endif 	/* __IMDhcpLeaseInfo_FWD_DEFINED__ */


#ifndef __IEnumMDhcpScopes_FWD_DEFINED__
#define __IEnumMDhcpScopes_FWD_DEFINED__
typedef interface IEnumMDhcpScopes IEnumMDhcpScopes;
#endif 	/* __IEnumMDhcpScopes_FWD_DEFINED__ */


#ifndef __IMDhcp_FWD_DEFINED__
#define __IMDhcp_FWD_DEFINED__
typedef interface IMDhcp IMDhcp;
#endif 	/* __IMDhcp_FWD_DEFINED__ */


#ifndef __IMDhcpScope_FWD_DEFINED__
#define __IMDhcpScope_FWD_DEFINED__
typedef interface IMDhcpScope IMDhcpScope;
#endif 	/* __IMDhcpScope_FWD_DEFINED__ */


#ifndef __IEnumBstr_FWD_DEFINED__
#define __IEnumBstr_FWD_DEFINED__
typedef interface IEnumBstr IEnumBstr;
#endif 	/* __IEnumBstr_FWD_DEFINED__ */


#ifndef __IMDhcpLeaseInfo_FWD_DEFINED__
#define __IMDhcpLeaseInfo_FWD_DEFINED__
typedef interface IMDhcpLeaseInfo IMDhcpLeaseInfo;
#endif 	/* __IMDhcpLeaseInfo_FWD_DEFINED__ */


#ifndef __IEnumMDhcpScopes_FWD_DEFINED__
#define __IEnumMDhcpScopes_FWD_DEFINED__
typedef interface IEnumMDhcpScopes IEnumMDhcpScopes;
#endif 	/* __IEnumMDhcpScopes_FWD_DEFINED__ */


#ifndef __IMDhcp_FWD_DEFINED__
#define __IMDhcp_FWD_DEFINED__
typedef interface IMDhcp IMDhcp;
#endif 	/* __IMDhcp_FWD_DEFINED__ */


#ifndef __MDhcp_FWD_DEFINED__
#define __MDhcp_FWD_DEFINED__

#ifdef __cplusplus
typedef class MDhcp MDhcp;
#else
typedef struct MDhcp MDhcp;
#endif /* __cplusplus */

#endif 	/* __MDhcp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "tapi3if.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMDhcpScope_INTERFACE_DEFINED__
#define __IMDhcpScope_INTERFACE_DEFINED__

/* interface IMDhcpScope */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMDhcpScope;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF0DAEF4-A289-11D1-8697-006008B0E5D2")
    IMDhcpScope : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScopeID( 
            /* [retval][out] */ long __RPC_FAR *pID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerID( 
            /* [retval][out] */ long __RPC_FAR *pID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScopeDescription( 
            /* [retval][out] */ BSTR __RPC_FAR *ppAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDhcpScopeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDhcpScope __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDhcpScope __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDhcpScope __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMDhcpScope __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMDhcpScope __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMDhcpScope __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMDhcpScope __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScopeID )( 
            IMDhcpScope __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServerID )( 
            IMDhcpScope __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScopeDescription )( 
            IMDhcpScope __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppAddress);
        
        END_INTERFACE
    } IMDhcpScopeVtbl;

    interface IMDhcpScope
    {
        CONST_VTBL struct IMDhcpScopeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDhcpScope_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDhcpScope_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDhcpScope_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDhcpScope_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMDhcpScope_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMDhcpScope_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMDhcpScope_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMDhcpScope_get_ScopeID(This,pID)	\
    (This)->lpVtbl -> get_ScopeID(This,pID)

#define IMDhcpScope_get_ServerID(This,pID)	\
    (This)->lpVtbl -> get_ServerID(This,pID)

#define IMDhcpScope_get_ScopeDescription(This,ppAddress)	\
    (This)->lpVtbl -> get_ScopeDescription(This,ppAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpScope_get_ScopeID_Proxy( 
    IMDhcpScope __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pID);


void __RPC_STUB IMDhcpScope_get_ScopeID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpScope_get_ServerID_Proxy( 
    IMDhcpScope __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pID);


void __RPC_STUB IMDhcpScope_get_ServerID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpScope_get_ScopeDescription_Proxy( 
    IMDhcpScope __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppAddress);


void __RPC_STUB IMDhcpScope_get_ScopeDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDhcpScope_INTERFACE_DEFINED__ */


#ifndef __IEnumBstr_INTERFACE_DEFINED__
#define __IEnumBstr_INTERFACE_DEFINED__

/* interface IEnumBstr */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEnumBstr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF0DAF03-A289-11D1-8697-006008B0E5D2")
    IEnumBstr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *pAddresses,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumBstrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumBstr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumBstr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumBstr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumBstr __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ BSTR __RPC_FAR *pAddresses,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumBstr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumBstr __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumBstr __RPC_FAR * This,
            /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumBstrVtbl;

    interface IEnumBstr
    {
        CONST_VTBL struct IEnumBstrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumBstr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumBstr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumBstr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumBstr_Next(This,celt,pAddresses,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,pAddresses,pceltFetched)

#define IEnumBstr_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumBstr_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumBstr_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumBstr_Next_Proxy( 
    IEnumBstr __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ BSTR __RPC_FAR *pAddresses,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumBstr_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumBstr_Reset_Proxy( 
    IEnumBstr __RPC_FAR * This);


void __RPC_STUB IEnumBstr_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumBstr_Skip_Proxy( 
    IEnumBstr __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumBstr_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumBstr_Clone_Proxy( 
    IEnumBstr __RPC_FAR * This,
    /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumBstr_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumBstr_INTERFACE_DEFINED__ */


#ifndef __IMDhcpLeaseInfo_INTERFACE_DEFINED__
#define __IMDhcpLeaseInfo_INTERFACE_DEFINED__

/* interface IMDhcpLeaseInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMDhcpLeaseInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF0DAEFD-A289-11D1-8697-006008B0E5D2")
    IMDhcpLeaseInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RequestID( 
            /* [retval][out] */ BSTR __RPC_FAR *ppRequestID) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeaseStartTime( 
            /* [retval][out] */ DATE __RPC_FAR *pTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeaseStartTime( 
            /* [in] */ DATE time) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LeaseStopTime( 
            /* [retval][out] */ DATE __RPC_FAR *pTime) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LeaseStopTime( 
            /* [in] */ DATE time) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddressCount( 
            /* [retval][out] */ long __RPC_FAR *pCount) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ServerAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *ppAddress) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TTL( 
            /* [retval][out] */ long __RPC_FAR *pTTL) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Addresses( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE EnumerateAddresses( 
            /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *pAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDhcpLeaseInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDhcpLeaseInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDhcpLeaseInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestID )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppRequestID);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeaseStartTime )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeaseStartTime )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ DATE time);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LeaseStopTime )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pTime);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LeaseStopTime )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [in] */ DATE time);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddressCount )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pCount);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ServerAddress )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *ppAddress);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TTL )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pTTL);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Addresses )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateAddresses )( 
            IMDhcpLeaseInfo __RPC_FAR * This,
            /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *pAddress);
        
        END_INTERFACE
    } IMDhcpLeaseInfoVtbl;

    interface IMDhcpLeaseInfo
    {
        CONST_VTBL struct IMDhcpLeaseInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDhcpLeaseInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDhcpLeaseInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDhcpLeaseInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDhcpLeaseInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMDhcpLeaseInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMDhcpLeaseInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMDhcpLeaseInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMDhcpLeaseInfo_get_RequestID(This,ppRequestID)	\
    (This)->lpVtbl -> get_RequestID(This,ppRequestID)

#define IMDhcpLeaseInfo_get_LeaseStartTime(This,pTime)	\
    (This)->lpVtbl -> get_LeaseStartTime(This,pTime)

#define IMDhcpLeaseInfo_put_LeaseStartTime(This,time)	\
    (This)->lpVtbl -> put_LeaseStartTime(This,time)

#define IMDhcpLeaseInfo_get_LeaseStopTime(This,pTime)	\
    (This)->lpVtbl -> get_LeaseStopTime(This,pTime)

#define IMDhcpLeaseInfo_put_LeaseStopTime(This,time)	\
    (This)->lpVtbl -> put_LeaseStopTime(This,time)

#define IMDhcpLeaseInfo_get_AddressCount(This,pCount)	\
    (This)->lpVtbl -> get_AddressCount(This,pCount)

#define IMDhcpLeaseInfo_get_ServerAddress(This,ppAddress)	\
    (This)->lpVtbl -> get_ServerAddress(This,ppAddress)

#define IMDhcpLeaseInfo_get_TTL(This,pTTL)	\
    (This)->lpVtbl -> get_TTL(This,pTTL)

#define IMDhcpLeaseInfo_get_Addresses(This,pVariant)	\
    (This)->lpVtbl -> get_Addresses(This,pVariant)

#define IMDhcpLeaseInfo_EnumerateAddresses(This,pAddress)	\
    (This)->lpVtbl -> EnumerateAddresses(This,pAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_RequestID_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppRequestID);


void __RPC_STUB IMDhcpLeaseInfo_get_RequestID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_LeaseStartTime_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pTime);


void __RPC_STUB IMDhcpLeaseInfo_get_LeaseStartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_put_LeaseStartTime_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [in] */ DATE time);


void __RPC_STUB IMDhcpLeaseInfo_put_LeaseStartTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_LeaseStopTime_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pTime);


void __RPC_STUB IMDhcpLeaseInfo_get_LeaseStopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_put_LeaseStopTime_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [in] */ DATE time);


void __RPC_STUB IMDhcpLeaseInfo_put_LeaseStopTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_AddressCount_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pCount);


void __RPC_STUB IMDhcpLeaseInfo_get_AddressCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_ServerAddress_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *ppAddress);


void __RPC_STUB IMDhcpLeaseInfo_get_ServerAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_TTL_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pTTL);


void __RPC_STUB IMDhcpLeaseInfo_get_TTL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_get_Addresses_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IMDhcpLeaseInfo_get_Addresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IMDhcpLeaseInfo_EnumerateAddresses_Proxy( 
    IMDhcpLeaseInfo __RPC_FAR * This,
    /* [retval][out] */ IEnumBstr __RPC_FAR *__RPC_FAR *pAddress);


void __RPC_STUB IMDhcpLeaseInfo_EnumerateAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDhcpLeaseInfo_INTERFACE_DEFINED__ */


#ifndef __IEnumMDhcpScopes_INTERFACE_DEFINED__
#define __IEnumMDhcpScopes_INTERFACE_DEFINED__

/* interface IEnumMDhcpScopes */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEnumMDhcpScopes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF0DAF09-A289-11D1-8697-006008B0E5D2")
    IEnumMDhcpScopes : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ IMDhcpScope __RPC_FAR *__RPC_FAR *ppScopes,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [retval][out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMDhcpScopesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumMDhcpScopes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumMDhcpScopes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumMDhcpScopes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumMDhcpScopes __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ IMDhcpScope __RPC_FAR *__RPC_FAR *ppScopes,
            /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumMDhcpScopes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumMDhcpScopes __RPC_FAR * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumMDhcpScopes __RPC_FAR * This,
            /* [retval][out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnum);
        
        END_INTERFACE
    } IEnumMDhcpScopesVtbl;

    interface IEnumMDhcpScopes
    {
        CONST_VTBL struct IEnumMDhcpScopesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMDhcpScopes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMDhcpScopes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMDhcpScopes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMDhcpScopes_Next(This,celt,ppScopes,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppScopes,pceltFetched)

#define IEnumMDhcpScopes_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMDhcpScopes_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumMDhcpScopes_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumMDhcpScopes_Next_Proxy( 
    IEnumMDhcpScopes __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ IMDhcpScope __RPC_FAR *__RPC_FAR *ppScopes,
    /* [full][out][in] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumMDhcpScopes_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMDhcpScopes_Reset_Proxy( 
    IEnumMDhcpScopes __RPC_FAR * This);


void __RPC_STUB IEnumMDhcpScopes_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMDhcpScopes_Skip_Proxy( 
    IEnumMDhcpScopes __RPC_FAR * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumMDhcpScopes_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumMDhcpScopes_Clone_Proxy( 
    IEnumMDhcpScopes __RPC_FAR * This,
    /* [retval][out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnum);


void __RPC_STUB IEnumMDhcpScopes_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMDhcpScopes_INTERFACE_DEFINED__ */


#ifndef __IMDhcp_INTERFACE_DEFINED__
#define __IMDhcp_INTERFACE_DEFINED__

/* interface IMDhcp */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMDhcp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DF0DAEF1-A289-11D1-8697-006008B0E5D2")
    IMDhcp : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Scopes( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE EnumerateScopes( 
            /* [out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnumMDhcpScopes) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RequestAddress( 
            /* [in] */ long ScopeID,
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ long NumAddresses,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppLeaseResponse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenewAddress( 
            /* [in] */ long ScopeID,
            /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pRenewRequest,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppRenewResponse) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReleaseAddress( 
            /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pReleaseRequest) = 0;
        
        virtual /* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE CreateLeaseInfo( 
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ DWORD dwNumAddresses,
            /* [in] */ LPWSTR __RPC_FAR *ppAddresses,
            /* [in] */ LPWSTR pRequestID,
            /* [in] */ LPWSTR pServerAddress,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateLeaseInfoFromVariant( 
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ VARIANT vAddresses,
            /* [in] */ BSTR pRequestID,
            /* [in] */ BSTR pServerAddress,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMDhcpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMDhcp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMDhcp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMDhcp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Scopes )( 
            IMDhcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVariant);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumerateScopes )( 
            IMDhcp __RPC_FAR * This,
            /* [out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnumMDhcpScopes);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestAddress )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ long ScopeID,
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ long NumAddresses,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppLeaseResponse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RenewAddress )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ long ScopeID,
            /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pRenewRequest,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppRenewResponse);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseAddress )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pReleaseRequest);
        
        /* [helpstring][hidden][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLeaseInfo )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ DWORD dwNumAddresses,
            /* [in] */ LPWSTR __RPC_FAR *ppAddresses,
            /* [in] */ LPWSTR pRequestID,
            /* [in] */ LPWSTR pServerAddress,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateLeaseInfoFromVariant )( 
            IMDhcp __RPC_FAR * This,
            /* [in] */ DATE LeaseStartTime,
            /* [in] */ DATE LeaseStopTime,
            /* [in] */ VARIANT vAddresses,
            /* [in] */ BSTR pRequestID,
            /* [in] */ BSTR pServerAddress,
            /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest);
        
        END_INTERFACE
    } IMDhcpVtbl;

    interface IMDhcp
    {
        CONST_VTBL struct IMDhcpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMDhcp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMDhcp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMDhcp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMDhcp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMDhcp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMDhcp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMDhcp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMDhcp_get_Scopes(This,pVariant)	\
    (This)->lpVtbl -> get_Scopes(This,pVariant)

#define IMDhcp_EnumerateScopes(This,ppEnumMDhcpScopes)	\
    (This)->lpVtbl -> EnumerateScopes(This,ppEnumMDhcpScopes)

#define IMDhcp_RequestAddress(This,ScopeID,LeaseStartTime,LeaseStopTime,NumAddresses,ppLeaseResponse)	\
    (This)->lpVtbl -> RequestAddress(This,ScopeID,LeaseStartTime,LeaseStopTime,NumAddresses,ppLeaseResponse)

#define IMDhcp_RenewAddress(This,ScopeID,pRenewRequest,ppRenewResponse)	\
    (This)->lpVtbl -> RenewAddress(This,ScopeID,pRenewRequest,ppRenewResponse)

#define IMDhcp_ReleaseAddress(This,pReleaseRequest)	\
    (This)->lpVtbl -> ReleaseAddress(This,pReleaseRequest)

#define IMDhcp_CreateLeaseInfo(This,LeaseStartTime,LeaseStopTime,dwNumAddresses,ppAddresses,pRequestID,pServerAddress,ppReleaseRequest)	\
    (This)->lpVtbl -> CreateLeaseInfo(This,LeaseStartTime,LeaseStopTime,dwNumAddresses,ppAddresses,pRequestID,pServerAddress,ppReleaseRequest)

#define IMDhcp_CreateLeaseInfoFromVariant(This,LeaseStartTime,LeaseStopTime,vAddresses,pRequestID,pServerAddress,ppReleaseRequest)	\
    (This)->lpVtbl -> CreateLeaseInfoFromVariant(This,LeaseStartTime,LeaseStopTime,vAddresses,pRequestID,pServerAddress,ppReleaseRequest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMDhcp_get_Scopes_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVariant);


void __RPC_STUB IMDhcp_get_Scopes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_EnumerateScopes_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [out] */ IEnumMDhcpScopes __RPC_FAR *__RPC_FAR *ppEnumMDhcpScopes);


void __RPC_STUB IMDhcp_EnumerateScopes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_RequestAddress_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [in] */ long ScopeID,
    /* [in] */ DATE LeaseStartTime,
    /* [in] */ DATE LeaseStopTime,
    /* [in] */ long NumAddresses,
    /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppLeaseResponse);


void __RPC_STUB IMDhcp_RequestAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_RenewAddress_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [in] */ long ScopeID,
    /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pRenewRequest,
    /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppRenewResponse);


void __RPC_STUB IMDhcp_RenewAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_ReleaseAddress_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [in] */ IMDhcpLeaseInfo __RPC_FAR *pReleaseRequest);


void __RPC_STUB IMDhcp_ReleaseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][hidden][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_CreateLeaseInfo_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [in] */ DATE LeaseStartTime,
    /* [in] */ DATE LeaseStopTime,
    /* [in] */ DWORD dwNumAddresses,
    /* [in] */ LPWSTR __RPC_FAR *ppAddresses,
    /* [in] */ LPWSTR pRequestID,
    /* [in] */ LPWSTR pServerAddress,
    /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest);


void __RPC_STUB IMDhcp_CreateLeaseInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMDhcp_CreateLeaseInfoFromVariant_Proxy( 
    IMDhcp __RPC_FAR * This,
    /* [in] */ DATE LeaseStartTime,
    /* [in] */ DATE LeaseStopTime,
    /* [in] */ VARIANT vAddresses,
    /* [in] */ BSTR pRequestID,
    /* [in] */ BSTR pServerAddress,
    /* [retval][out] */ IMDhcpLeaseInfo __RPC_FAR *__RPC_FAR *ppReleaseRequest);


void __RPC_STUB IMDhcp_CreateLeaseInfoFromVariant_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMDhcp_INTERFACE_DEFINED__ */



#ifndef __MDHCPLib_LIBRARY_DEFINED__
#define __MDHCPLib_LIBRARY_DEFINED__

/* library MDHCPLib */
/* [helpstring][version][uuid] */ 








EXTERN_C const IID LIBID_MDHCPLib;

EXTERN_C const CLSID CLSID_MDhcp;

#ifdef __cplusplus

class DECLSPEC_UUID("DF0DAEF2-A289-11D1-8697-006008B0E5D2")
MDhcp;
#endif
#endif /* __MDHCPLib_LIBRARY_DEFINED__ */

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
