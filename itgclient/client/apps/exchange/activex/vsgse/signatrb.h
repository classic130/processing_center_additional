
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Tue Aug 29 10:03:05 2000
 */
/* Compiler settings for signatrb.idl:
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

#ifndef __signatrb_h__
#define __signatrb_h__

/* Forward Declarations */ 

#ifndef __ISignAttributes_FWD_DEFINED__
#define __ISignAttributes_FWD_DEFINED__
typedef interface ISignAttributes ISignAttributes;
#endif 	/* __ISignAttributes_FWD_DEFINED__ */


#ifndef __SignAttributes_FWD_DEFINED__
#define __SignAttributes_FWD_DEFINED__

#ifdef __cplusplus
typedef class SignAttributes SignAttributes;
#else
typedef struct SignAttributes SignAttributes;
#endif /* __cplusplus */

#endif 	/* __SignAttributes_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISignAttributes_INTERFACE_DEFINED__
#define __ISignAttributes_INTERFACE_DEFINED__

/* interface ISignAttributes */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISignAttributes;


#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("71C6919D-F9C0-11D2-8344-0060B0B32E16")
    ISignAttributes : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_userCertificate( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncUserCertificate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncUserSMIMECertificate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;


// Start Add: Infosys : CR27993
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChallengePhrase( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChallengePhrase( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AuthEncUserSMIMECertificate( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SMIMECapabilityBlob( 
            USHORT __RPC_FAR *cbSMIMECapabilityBlobSize,
            /* [retval][out] */ BYTE __RPC_FAR *pVal) = 0;

// End Add: Infosys : CR27993
    };
    
#else 	/* C style interface */

    typedef struct ISignAttributesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISignAttributes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISignAttributes __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISignAttributes __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_userCertificate )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncUserCertificate )( 
            ISignAttributes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncUserSMIMECertificate )( 
            ISignAttributes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);

// Start Add : Infosys : CR27993
		/* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChallengePhrase )( 
            ISignAttributes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChallengePhrase )( 
            ISignAttributes __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AuthEncUserSMIMECertificate )( 
            ISignAttributes __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SMIMECapabilityBlob )( 
            ISignAttributes __RPC_FAR * This,
            USHORT __RPC_FAR *cbSMIMECapabilityBlobSize,
            /* [retval][out] */ BYTE __RPC_FAR *pVal);

// End Add : Infosys : CR27993
        
        END_INTERFACE
    } ISignAttributesVtbl;

    interface ISignAttributes
    {
        CONST_VTBL struct ISignAttributesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISignAttributes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISignAttributes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISignAttributes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISignAttributes_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISignAttributes_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISignAttributes_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISignAttributes_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISignAttributes_put_userCertificate(This,newVal)	\
    (This)->lpVtbl -> put_userCertificate(This,newVal)

#define ISignAttributes_get_EncUserCertificate(This,pVal)	\
    (This)->lpVtbl -> get_EncUserCertificate(This,pVal)

#define ISignAttributes_get_EncUserSMIMECertificate(This,pVal)	\
    (This)->lpVtbl -> get_EncUserSMIMECertificate(This,pVal)

// Start Add : Infosys : CR27993
#define ISignAttributes_get_ChallengePhrase(This,pVal)	\
    (This)->lpVtbl -> get_ChallengePhrase(This,pVal)

#define ISignAttributes_put_ChallengePhrase(This,newVal)	\
    (This)->lpVtbl -> put_ChallengePhrase(This,newVal)

#define ISignAttributes_get_AuthEncUserSMIMECertificate(This,pVal)	\
    (This)->lpVtbl -> get_AuthEncUserSMIMECertificate(This,pVal)

#define ISignAttributes_get_SMIMECapabilityBlob(This,cbSMIMECapabilityBlobSize,pVal)	\
    (This)->lpVtbl -> get_SMIMECapabilityBlob(This,cbSMIMECapabilityBlobSize,pVal)

// End Add : Infosys : CR27993

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignAttributes_put_userCertificate_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignAttributes_put_userCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignAttributes_get_EncUserCertificate_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISignAttributes_get_EncUserCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignAttributes_get_EncUserSMIMECertificate_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISignAttributes_get_EncUserSMIMECertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);

// Start Add : Infosys : CR27993

/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignAttributes_get_ChallengePhrase_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISignAttributes_get_ChallengePhrase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ISignAttributes_put_ChallengePhrase_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ISignAttributes_put_ChallengePhrase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignAttributes_get_AuthEncUserSMIMECertificate_Proxy( 
    ISignAttributes __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISignAttributes_get_AuthEncUserSMIMECertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISignAttributes_get_SMIMECapabilityBlob_Proxy( 
    ISignAttributes __RPC_FAR * This,
    USHORT __RPC_FAR *cbSMIMECapabilityBlobSize,
    /* [retval][out] */ BYTE __RPC_FAR *pVal);


void __RPC_STUB ISignAttributes_get_SMIMECapabilityBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);

// End Add : Infosys : CR27993

#endif 	/* __ISignAttributes_INTERFACE_DEFINED__ */



#ifndef __SIGNATRBLib_LIBRARY_DEFINED__
#define __SIGNATRBLib_LIBRARY_DEFINED__

/* library SIGNATRBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SIGNATRBLib;

EXTERN_C const CLSID CLSID_SignAttributes;

#ifdef __cplusplus

class DECLSPEC_UUID("71C6919E-F9C0-11D2-8344-0060B0B32E16")
SignAttributes;
#endif
#endif /* __SIGNATRBLib_LIBRARY_DEFINED__ */

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


