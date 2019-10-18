/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Aug 20 11:47:16 2002
 */
/* Compiler settings for G:\sbajaj\xenroll.IDL:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __xenroll_h__
#define __xenroll_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICEnroll_FWD_DEFINED__
#define __ICEnroll_FWD_DEFINED__
typedef interface ICEnroll ICEnroll;
#endif 	/* __ICEnroll_FWD_DEFINED__ */


#ifndef __ICEnroll2_FWD_DEFINED__
#define __ICEnroll2_FWD_DEFINED__
typedef interface ICEnroll2 ICEnroll2;
#endif 	/* __ICEnroll2_FWD_DEFINED__ */


#ifndef __ICEnroll3_FWD_DEFINED__
#define __ICEnroll3_FWD_DEFINED__
typedef interface ICEnroll3 ICEnroll3;
#endif 	/* __ICEnroll3_FWD_DEFINED__ */


#ifndef __ICEnroll4_FWD_DEFINED__
#define __ICEnroll4_FWD_DEFINED__
typedef interface ICEnroll4 ICEnroll4;
#endif 	/* __ICEnroll4_FWD_DEFINED__ */


#ifndef __CEnroll_FWD_DEFINED__
#define __CEnroll_FWD_DEFINED__

#ifdef __cplusplus
typedef class CEnroll CEnroll;
#else
typedef struct CEnroll CEnroll;
#endif /* __cplusplus */

#endif 	/* __CEnroll_FWD_DEFINED__ */


#ifndef __CEnroll2_FWD_DEFINED__
#define __CEnroll2_FWD_DEFINED__

#ifdef __cplusplus
typedef class CEnroll2 CEnroll2;
#else
typedef struct CEnroll2 CEnroll2;
#endif /* __cplusplus */

#endif 	/* __CEnroll2_FWD_DEFINED__ */


void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __XENROLLLib_LIBRARY_DEFINED__
#define __XENROLLLib_LIBRARY_DEFINED__

/* library XENROLLLib */
/* [helpstring][version][uuid] */ 






EXTERN_C const IID LIBID_XENROLLLib;

#ifndef __ICEnroll_INTERFACE_DEFINED__
#define __ICEnroll_INTERFACE_DEFINED__

/* interface ICEnroll */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICEnroll;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43F8F288-7A20-11D0-8F06-00C04FC295E1")
    ICEnroll : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createFilePKCS10( 
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [in] */ BSTR wszPKCS10FileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE acceptFilePKCS7( 
            /* [in] */ BSTR wszPKCS7FileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createPKCS10( 
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pPKCS10) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE acceptPKCS7( 
            /* [in] */ BSTR PKCS7) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getCertFromPKCS7( 
            /* [in] */ BSTR wszPKCS7,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumProviders( 
            /* [in] */ long dwIndex,
            /* [in] */ long dwFlags,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumContainers( 
            /* [in] */ long dwIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE freeRequestInfo( 
            /* [in] */ BSTR PKCS7OrPKCS10) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_MyStoreName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_MyStoreName( 
            /* [in] */ BSTR pbstrName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_MyStoreType( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_MyStoreType( 
            /* [in] */ BSTR pbstrType) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_MyStoreFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_MyStoreFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CAStoreName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CAStoreName( 
            /* [in] */ BSTR pbstrName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CAStoreType( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CAStoreType( 
            /* [in] */ BSTR pbstrType) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_CAStoreFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_CAStoreFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RootStoreName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RootStoreName( 
            /* [in] */ BSTR pbstrName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RootStoreType( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RootStoreType( 
            /* [in] */ BSTR pbstrType) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RootStoreFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RootStoreFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RequestStoreName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RequestStoreName( 
            /* [in] */ BSTR pbstrName) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RequestStoreType( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RequestStoreType( 
            /* [in] */ BSTR pbstrType) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_RequestStoreFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_RequestStoreFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ContainerName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ContainerName( 
            /* [in] */ BSTR pbstrContainer) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ProviderName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ProviderName( 
            /* [in] */ BSTR pbstrProvider) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ProviderType( 
            /* [retval][out] */ long __RPC_FAR *pdwType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ProviderType( 
            /* [in] */ long pdwType) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_KeySpec( 
            /* [retval][out] */ long __RPC_FAR *pdw) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_KeySpec( 
            /* [in] */ long pdw) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ProviderFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ProviderFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_UseExistingKeySet( 
            /* [retval][out] */ long __RPC_FAR *fUseExistingKeys) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_UseExistingKeySet( 
            /* [in] */ long fUseExistingKeys) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_GenKeyFlags( 
            /* [retval][out] */ long __RPC_FAR *pdwFlags) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_GenKeyFlags( 
            /* [in] */ long pdwFlags) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_DeleteRequestCert( 
            /* [retval][out] */ long __RPC_FAR *fDelete) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_DeleteRequestCert( 
            /* [in] */ long fDelete) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_WriteCertToCSP( 
            /* [retval][out] */ long __RPC_FAR *fBool) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_WriteCertToCSP( 
            /* [in] */ long fBool) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_SPCFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SPCFileName( 
            /* [in] */ BSTR pbstr) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PVKFileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_PVKFileName( 
            /* [in] */ BSTR pbstr) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HashAlgorithm( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_HashAlgorithm( 
            /* [in] */ BSTR pbstr) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICEnrollVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICEnroll __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICEnroll __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICEnroll __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFilePKCS10 )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [in] */ BSTR wszPKCS10FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptFilePKCS7 )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPKCS10 )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pPKCS10);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptPKCS7 )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromPKCS7 )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumProviders )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long dwFlags,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumContainers )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *freeRequestInfo )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR PKCS7OrPKCS10);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreType )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrContainer);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstrProvider);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderType )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderType )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeySpec )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdw);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeySpec )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdw);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseExistingKeySet )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fUseExistingKeys);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseExistingKeySet )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long fUseExistingKeys);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GenKeyFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GenKeyFlags )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteRequestCert )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fDelete);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteRequestCert )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long fDelete);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToCSP )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToCSP )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SPCFileName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SPCFileName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PVKFileName )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PVKFileName )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgorithm )( 
            ICEnroll __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgorithm )( 
            ICEnroll __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        END_INTERFACE
    } ICEnrollVtbl;

    interface ICEnroll
    {
        CONST_VTBL struct ICEnrollVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICEnroll_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICEnroll_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICEnroll_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICEnroll_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICEnroll_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICEnroll_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICEnroll_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICEnroll_createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)	\
    (This)->lpVtbl -> createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)

#define ICEnroll_acceptFilePKCS7(This,wszPKCS7FileName)	\
    (This)->lpVtbl -> acceptFilePKCS7(This,wszPKCS7FileName)

#define ICEnroll_createPKCS10(This,DNName,Usage,pPKCS10)	\
    (This)->lpVtbl -> createPKCS10(This,DNName,Usage,pPKCS10)

#define ICEnroll_acceptPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> acceptPKCS7(This,PKCS7)

#define ICEnroll_getCertFromPKCS7(This,wszPKCS7,pbstrCert)	\
    (This)->lpVtbl -> getCertFromPKCS7(This,wszPKCS7,pbstrCert)

#define ICEnroll_enumProviders(This,dwIndex,dwFlags,pbstrProvName)	\
    (This)->lpVtbl -> enumProviders(This,dwIndex,dwFlags,pbstrProvName)

#define ICEnroll_enumContainers(This,dwIndex,pbstr)	\
    (This)->lpVtbl -> enumContainers(This,dwIndex,pbstr)

#define ICEnroll_freeRequestInfo(This,PKCS7OrPKCS10)	\
    (This)->lpVtbl -> freeRequestInfo(This,PKCS7OrPKCS10)

#define ICEnroll_get_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_MyStoreName(This,pbstrName)

#define ICEnroll_put_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_MyStoreName(This,pbstrName)

#define ICEnroll_get_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_MyStoreType(This,pbstrType)

#define ICEnroll_put_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_MyStoreType(This,pbstrType)

#define ICEnroll_get_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_MyStoreFlags(This,pdwFlags)

#define ICEnroll_put_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_MyStoreFlags(This,pdwFlags)

#define ICEnroll_get_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_CAStoreName(This,pbstrName)

#define ICEnroll_put_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_CAStoreName(This,pbstrName)

#define ICEnroll_get_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_CAStoreType(This,pbstrType)

#define ICEnroll_put_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_CAStoreType(This,pbstrType)

#define ICEnroll_get_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_CAStoreFlags(This,pdwFlags)

#define ICEnroll_put_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_CAStoreFlags(This,pdwFlags)

#define ICEnroll_get_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RootStoreName(This,pbstrName)

#define ICEnroll_put_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RootStoreName(This,pbstrName)

#define ICEnroll_get_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RootStoreType(This,pbstrType)

#define ICEnroll_put_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RootStoreType(This,pbstrType)

#define ICEnroll_get_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RootStoreFlags(This,pdwFlags)

#define ICEnroll_put_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RootStoreFlags(This,pdwFlags)

#define ICEnroll_get_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RequestStoreName(This,pbstrName)

#define ICEnroll_put_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RequestStoreName(This,pbstrName)

#define ICEnroll_get_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RequestStoreType(This,pbstrType)

#define ICEnroll_put_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RequestStoreType(This,pbstrType)

#define ICEnroll_get_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RequestStoreFlags(This,pdwFlags)

#define ICEnroll_put_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RequestStoreFlags(This,pdwFlags)

#define ICEnroll_get_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> get_ContainerName(This,pbstrContainer)

#define ICEnroll_put_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> put_ContainerName(This,pbstrContainer)

#define ICEnroll_get_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrProvider)

#define ICEnroll_put_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> put_ProviderName(This,pbstrProvider)

#define ICEnroll_get_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> get_ProviderType(This,pdwType)

#define ICEnroll_put_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> put_ProviderType(This,pdwType)

#define ICEnroll_get_KeySpec(This,pdw)	\
    (This)->lpVtbl -> get_KeySpec(This,pdw)

#define ICEnroll_put_KeySpec(This,pdw)	\
    (This)->lpVtbl -> put_KeySpec(This,pdw)

#define ICEnroll_get_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_ProviderFlags(This,pdwFlags)

#define ICEnroll_put_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_ProviderFlags(This,pdwFlags)

#define ICEnroll_get_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> get_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll_put_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> put_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll_get_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_GenKeyFlags(This,pdwFlags)

#define ICEnroll_put_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_GenKeyFlags(This,pdwFlags)

#define ICEnroll_get_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> get_DeleteRequestCert(This,fDelete)

#define ICEnroll_put_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> put_DeleteRequestCert(This,fDelete)

#define ICEnroll_get_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToCSP(This,fBool)

#define ICEnroll_put_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToCSP(This,fBool)

#define ICEnroll_get_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> get_SPCFileName(This,pbstr)

#define ICEnroll_put_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> put_SPCFileName(This,pbstr)

#define ICEnroll_get_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> get_PVKFileName(This,pbstr)

#define ICEnroll_put_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> put_PVKFileName(This,pbstr)

#define ICEnroll_get_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> get_HashAlgorithm(This,pbstr)

#define ICEnroll_put_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> put_HashAlgorithm(This,pbstr)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_createFilePKCS10_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR DNName,
    /* [in] */ BSTR Usage,
    /* [in] */ BSTR wszPKCS10FileName);


void __RPC_STUB ICEnroll_createFilePKCS10_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_acceptFilePKCS7_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR wszPKCS7FileName);


void __RPC_STUB ICEnroll_acceptFilePKCS7_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_createPKCS10_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR DNName,
    /* [in] */ BSTR Usage,
    /* [retval][out] */ BSTR __RPC_FAR *pPKCS10);


void __RPC_STUB ICEnroll_createPKCS10_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_acceptPKCS7_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR PKCS7);


void __RPC_STUB ICEnroll_acceptPKCS7_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_getCertFromPKCS7_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR wszPKCS7,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);


void __RPC_STUB ICEnroll_getCertFromPKCS7_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_enumProviders_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long dwIndex,
    /* [in] */ long dwFlags,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName);


void __RPC_STUB ICEnroll_enumProviders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_enumContainers_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long dwIndex,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB ICEnroll_enumContainers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll_freeRequestInfo_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR PKCS7OrPKCS10);


void __RPC_STUB ICEnroll_freeRequestInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_MyStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ICEnroll_get_MyStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_MyStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrName);


void __RPC_STUB ICEnroll_put_MyStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_MyStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrType);


void __RPC_STUB ICEnroll_get_MyStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_MyStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrType);


void __RPC_STUB ICEnroll_put_MyStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_MyStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_MyStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_MyStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_MyStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_CAStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ICEnroll_get_CAStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_CAStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrName);


void __RPC_STUB ICEnroll_put_CAStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_CAStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrType);


void __RPC_STUB ICEnroll_get_CAStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_CAStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrType);


void __RPC_STUB ICEnroll_put_CAStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_CAStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_CAStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_CAStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_CAStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RootStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ICEnroll_get_RootStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RootStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrName);


void __RPC_STUB ICEnroll_put_RootStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RootStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrType);


void __RPC_STUB ICEnroll_get_RootStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RootStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrType);


void __RPC_STUB ICEnroll_put_RootStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RootStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_RootStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RootStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_RootStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RequestStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrName);


void __RPC_STUB ICEnroll_get_RequestStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RequestStoreName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrName);


void __RPC_STUB ICEnroll_put_RequestStoreName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RequestStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrType);


void __RPC_STUB ICEnroll_get_RequestStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RequestStoreType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrType);


void __RPC_STUB ICEnroll_put_RequestStoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_RequestStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_RequestStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_RequestStoreFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_RequestStoreFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_ContainerName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer);


void __RPC_STUB ICEnroll_get_ContainerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_ContainerName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrContainer);


void __RPC_STUB ICEnroll_put_ContainerName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_ProviderName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider);


void __RPC_STUB ICEnroll_get_ProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_ProviderName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstrProvider);


void __RPC_STUB ICEnroll_put_ProviderName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_ProviderType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwType);


void __RPC_STUB ICEnroll_get_ProviderType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_ProviderType_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwType);


void __RPC_STUB ICEnroll_put_ProviderType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_KeySpec_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdw);


void __RPC_STUB ICEnroll_get_KeySpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_KeySpec_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdw);


void __RPC_STUB ICEnroll_put_KeySpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_ProviderFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_ProviderFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_ProviderFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_ProviderFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_UseExistingKeySet_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fUseExistingKeys);


void __RPC_STUB ICEnroll_get_UseExistingKeySet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_UseExistingKeySet_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long fUseExistingKeys);


void __RPC_STUB ICEnroll_put_UseExistingKeySet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_GenKeyFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwFlags);


void __RPC_STUB ICEnroll_get_GenKeyFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_GenKeyFlags_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long pdwFlags);


void __RPC_STUB ICEnroll_put_GenKeyFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_DeleteRequestCert_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fDelete);


void __RPC_STUB ICEnroll_get_DeleteRequestCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_DeleteRequestCert_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long fDelete);


void __RPC_STUB ICEnroll_put_DeleteRequestCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_WriteCertToCSP_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fBool);


void __RPC_STUB ICEnroll_get_WriteCertToCSP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_WriteCertToCSP_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ long fBool);


void __RPC_STUB ICEnroll_put_WriteCertToCSP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_SPCFileName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB ICEnroll_get_SPCFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_SPCFileName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstr);


void __RPC_STUB ICEnroll_put_SPCFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_PVKFileName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB ICEnroll_get_PVKFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_PVKFileName_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstr);


void __RPC_STUB ICEnroll_put_PVKFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_get_HashAlgorithm_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB ICEnroll_get_HashAlgorithm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll_put_HashAlgorithm_Proxy( 
    ICEnroll __RPC_FAR * This,
    /* [in] */ BSTR pbstr);


void __RPC_STUB ICEnroll_put_HashAlgorithm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICEnroll_INTERFACE_DEFINED__ */




#ifndef __ICEnroll2_INTERFACE_DEFINED__
#define __ICEnroll2_INTERFACE_DEFINED__

/* interface ICEnroll2 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICEnroll2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("704CA730-C90B-11D1-9BEC-00C04FC295E1")
    ICEnroll2 : public ICEnroll
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addCertTypeToRequest( 
            /* [in] */ BSTR CertType) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addNameValuePairToSignature( 
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_WriteCertToUserDS( 
            /* [retval][out] */ long __RPC_FAR *fBool) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_WriteCertToUserDS( 
            /* [in] */ long fBool) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EnableT61DNEncoding( 
            /* [retval][out] */ long __RPC_FAR *fBool) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_EnableT61DNEncoding( 
            /* [in] */ long fBool) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICEnroll2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICEnroll2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICEnroll2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICEnroll2 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFilePKCS10 )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [in] */ BSTR wszPKCS10FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptFilePKCS7 )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPKCS10 )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pPKCS10);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptPKCS7 )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromPKCS7 )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumProviders )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long dwFlags,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumContainers )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *freeRequestInfo )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7OrPKCS10);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrContainer);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstrProvider);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderType )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeySpec )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdw);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeySpec )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdw);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseExistingKeySet )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fUseExistingKeys);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseExistingKeySet )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long fUseExistingKeys);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GenKeyFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GenKeyFlags )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteRequestCert )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fDelete);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteRequestCert )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long fDelete);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToCSP )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToCSP )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SPCFileName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SPCFileName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PVKFileName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PVKFileName )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgorithm )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgorithm )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addCertTypeToRequest )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR CertType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addNameValuePairToSignature )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToUserDS )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToUserDS )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableT61DNEncoding )( 
            ICEnroll2 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableT61DNEncoding )( 
            ICEnroll2 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        END_INTERFACE
    } ICEnroll2Vtbl;

    interface ICEnroll2
    {
        CONST_VTBL struct ICEnroll2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICEnroll2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICEnroll2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICEnroll2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICEnroll2_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICEnroll2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICEnroll2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICEnroll2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICEnroll2_createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)	\
    (This)->lpVtbl -> createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)

#define ICEnroll2_acceptFilePKCS7(This,wszPKCS7FileName)	\
    (This)->lpVtbl -> acceptFilePKCS7(This,wszPKCS7FileName)

#define ICEnroll2_createPKCS10(This,DNName,Usage,pPKCS10)	\
    (This)->lpVtbl -> createPKCS10(This,DNName,Usage,pPKCS10)

#define ICEnroll2_acceptPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> acceptPKCS7(This,PKCS7)

#define ICEnroll2_getCertFromPKCS7(This,wszPKCS7,pbstrCert)	\
    (This)->lpVtbl -> getCertFromPKCS7(This,wszPKCS7,pbstrCert)

#define ICEnroll2_enumProviders(This,dwIndex,dwFlags,pbstrProvName)	\
    (This)->lpVtbl -> enumProviders(This,dwIndex,dwFlags,pbstrProvName)

#define ICEnroll2_enumContainers(This,dwIndex,pbstr)	\
    (This)->lpVtbl -> enumContainers(This,dwIndex,pbstr)

#define ICEnroll2_freeRequestInfo(This,PKCS7OrPKCS10)	\
    (This)->lpVtbl -> freeRequestInfo(This,PKCS7OrPKCS10)

#define ICEnroll2_get_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_MyStoreName(This,pbstrName)

#define ICEnroll2_put_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_MyStoreName(This,pbstrName)

#define ICEnroll2_get_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_MyStoreType(This,pbstrType)

#define ICEnroll2_put_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_MyStoreType(This,pbstrType)

#define ICEnroll2_get_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_MyStoreFlags(This,pdwFlags)

#define ICEnroll2_put_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_MyStoreFlags(This,pdwFlags)

#define ICEnroll2_get_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_CAStoreName(This,pbstrName)

#define ICEnroll2_put_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_CAStoreName(This,pbstrName)

#define ICEnroll2_get_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_CAStoreType(This,pbstrType)

#define ICEnroll2_put_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_CAStoreType(This,pbstrType)

#define ICEnroll2_get_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_CAStoreFlags(This,pdwFlags)

#define ICEnroll2_put_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_CAStoreFlags(This,pdwFlags)

#define ICEnroll2_get_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RootStoreName(This,pbstrName)

#define ICEnroll2_put_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RootStoreName(This,pbstrName)

#define ICEnroll2_get_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RootStoreType(This,pbstrType)

#define ICEnroll2_put_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RootStoreType(This,pbstrType)

#define ICEnroll2_get_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RootStoreFlags(This,pdwFlags)

#define ICEnroll2_put_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RootStoreFlags(This,pdwFlags)

#define ICEnroll2_get_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RequestStoreName(This,pbstrName)

#define ICEnroll2_put_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RequestStoreName(This,pbstrName)

#define ICEnroll2_get_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RequestStoreType(This,pbstrType)

#define ICEnroll2_put_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RequestStoreType(This,pbstrType)

#define ICEnroll2_get_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RequestStoreFlags(This,pdwFlags)

#define ICEnroll2_put_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RequestStoreFlags(This,pdwFlags)

#define ICEnroll2_get_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> get_ContainerName(This,pbstrContainer)

#define ICEnroll2_put_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> put_ContainerName(This,pbstrContainer)

#define ICEnroll2_get_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrProvider)

#define ICEnroll2_put_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> put_ProviderName(This,pbstrProvider)

#define ICEnroll2_get_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> get_ProviderType(This,pdwType)

#define ICEnroll2_put_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> put_ProviderType(This,pdwType)

#define ICEnroll2_get_KeySpec(This,pdw)	\
    (This)->lpVtbl -> get_KeySpec(This,pdw)

#define ICEnroll2_put_KeySpec(This,pdw)	\
    (This)->lpVtbl -> put_KeySpec(This,pdw)

#define ICEnroll2_get_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_ProviderFlags(This,pdwFlags)

#define ICEnroll2_put_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_ProviderFlags(This,pdwFlags)

#define ICEnroll2_get_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> get_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll2_put_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> put_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll2_get_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_GenKeyFlags(This,pdwFlags)

#define ICEnroll2_put_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_GenKeyFlags(This,pdwFlags)

#define ICEnroll2_get_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> get_DeleteRequestCert(This,fDelete)

#define ICEnroll2_put_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> put_DeleteRequestCert(This,fDelete)

#define ICEnroll2_get_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToCSP(This,fBool)

#define ICEnroll2_put_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToCSP(This,fBool)

#define ICEnroll2_get_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> get_SPCFileName(This,pbstr)

#define ICEnroll2_put_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> put_SPCFileName(This,pbstr)

#define ICEnroll2_get_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> get_PVKFileName(This,pbstr)

#define ICEnroll2_put_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> put_PVKFileName(This,pbstr)

#define ICEnroll2_get_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> get_HashAlgorithm(This,pbstr)

#define ICEnroll2_put_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> put_HashAlgorithm(This,pbstr)


#define ICEnroll2_addCertTypeToRequest(This,CertType)	\
    (This)->lpVtbl -> addCertTypeToRequest(This,CertType)

#define ICEnroll2_addNameValuePairToSignature(This,Name,Value)	\
    (This)->lpVtbl -> addNameValuePairToSignature(This,Name,Value)

#define ICEnroll2_get_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToUserDS(This,fBool)

#define ICEnroll2_put_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToUserDS(This,fBool)

#define ICEnroll2_get_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> get_EnableT61DNEncoding(This,fBool)

#define ICEnroll2_put_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> put_EnableT61DNEncoding(This,fBool)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_addCertTypeToRequest_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [in] */ BSTR CertType);


void __RPC_STUB ICEnroll2_addCertTypeToRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_addNameValuePairToSignature_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [in] */ BSTR Name,
    /* [in] */ BSTR Value);


void __RPC_STUB ICEnroll2_addNameValuePairToSignature_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_get_WriteCertToUserDS_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fBool);


void __RPC_STUB ICEnroll2_get_WriteCertToUserDS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_put_WriteCertToUserDS_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [in] */ long fBool);


void __RPC_STUB ICEnroll2_put_WriteCertToUserDS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_get_EnableT61DNEncoding_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fBool);


void __RPC_STUB ICEnroll2_get_EnableT61DNEncoding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll2_put_EnableT61DNEncoding_Proxy( 
    ICEnroll2 __RPC_FAR * This,
    /* [in] */ long fBool);


void __RPC_STUB ICEnroll2_put_EnableT61DNEncoding_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICEnroll2_INTERFACE_DEFINED__ */



#ifndef __ICEnroll3_INTERFACE_DEFINED__
#define __ICEnroll3_INTERFACE_DEFINED__


/* interface ICEnroll3 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICEnroll3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C28C2D95-B7DE-11D2-A421-00C04F79FE8E")
    ICEnroll3 : public ICEnroll2
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InstallPKCS7( 
            /* [in] */ BSTR PKCS7) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetSupportedKeySpec( 
            /* [retval][out] */ long __RPC_FAR *pdwKeySpec) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetKeyLen( 
            /* [in] */ long fMin,
            /* [in] */ long fExchange,
            /* [retval][out] */ long __RPC_FAR *pdwKeySize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE EnumAlgs( 
            /* [in] */ long dwIndex,
            /* [in] */ long algClass,
            /* [retval][out] */ long __RPC_FAR *pdwAlgID) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetAlgName( 
            /* [in] */ long algID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ReuseHardwareKeyIfUnableToGenNew( 
            /* [in] */ long fReuseHardwareKeyIfUnableToGenNew) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ReuseHardwareKeyIfUnableToGenNew( 
            /* [retval][out] */ long __RPC_FAR *fReuseHardwareKeyIfUnableToGenNew) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_HashAlgID( 
            /* [in] */ long HashAlgID) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_HashAlgID( 
            /* [retval][out] */ long __RPC_FAR *HashAlgID) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_LimitExchangeKeyToEncipherment( 
            /* [in] */ long fLimitExchangeKeyToEncipherment) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_LimitExchangeKeyToEncipherment( 
            /* [retval][out] */ long __RPC_FAR *fLimitExchangeKeyToEncipherment) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_EnableSMIMECapabilities( 
            /* [in] */ long fEnableSMIMECapabilities) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_EnableSMIMECapabilities( 
            /* [retval][out] */ long __RPC_FAR *fEnableSMIMECapabilities) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICEnroll3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICEnroll3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICEnroll3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICEnroll3 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFilePKCS10 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [in] */ BSTR wszPKCS10FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptFilePKCS7 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPKCS10 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pPKCS10);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptPKCS7 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromPKCS7 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumProviders )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long dwFlags,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumContainers )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *freeRequestInfo )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7OrPKCS10);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrContainer);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstrProvider);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderType )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeySpec )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdw);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeySpec )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdw);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseExistingKeySet )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fUseExistingKeys);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseExistingKeySet )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fUseExistingKeys);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GenKeyFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GenKeyFlags )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteRequestCert )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fDelete);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteRequestCert )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fDelete);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToCSP )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToCSP )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SPCFileName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SPCFileName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PVKFileName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PVKFileName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgorithm )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgorithm )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addCertTypeToRequest )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR CertType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addNameValuePairToSignature )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToUserDS )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToUserDS )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableT61DNEncoding )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableT61DNEncoding )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstallPKCS7 )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICEnroll3 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSupportedKeySpec )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwKeySpec);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetKeyLen )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fMin,
            /* [in] */ long fExchange,
            /* [retval][out] */ long __RPC_FAR *pdwKeySize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumAlgs )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long algClass,
            /* [retval][out] */ long __RPC_FAR *pdwAlgID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlgName )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long algID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReuseHardwareKeyIfUnableToGenNew )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fReuseHardwareKeyIfUnableToGenNew);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReuseHardwareKeyIfUnableToGenNew )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fReuseHardwareKeyIfUnableToGenNew);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgID )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long HashAlgID);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgID )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *HashAlgID);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LimitExchangeKeyToEncipherment )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fLimitExchangeKeyToEncipherment);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LimitExchangeKeyToEncipherment )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fLimitExchangeKeyToEncipherment);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableSMIMECapabilities )( 
            ICEnroll3 __RPC_FAR * This,
            /* [in] */ long fEnableSMIMECapabilities);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableSMIMECapabilities )( 
            ICEnroll3 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fEnableSMIMECapabilities);
        
        END_INTERFACE
    } ICEnroll3Vtbl;

    interface ICEnroll3
    {
        CONST_VTBL struct ICEnroll3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICEnroll3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICEnroll3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICEnroll3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICEnroll3_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICEnroll3_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICEnroll3_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICEnroll3_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICEnroll3_createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)	\
    (This)->lpVtbl -> createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)

#define ICEnroll3_acceptFilePKCS7(This,wszPKCS7FileName)	\
    (This)->lpVtbl -> acceptFilePKCS7(This,wszPKCS7FileName)

#define ICEnroll3_createPKCS10(This,DNName,Usage,pPKCS10)	\
    (This)->lpVtbl -> createPKCS10(This,DNName,Usage,pPKCS10)

#define ICEnroll3_acceptPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> acceptPKCS7(This,PKCS7)

#define ICEnroll3_getCertFromPKCS7(This,wszPKCS7,pbstrCert)	\
    (This)->lpVtbl -> getCertFromPKCS7(This,wszPKCS7,pbstrCert)

#define ICEnroll3_enumProviders(This,dwIndex,dwFlags,pbstrProvName)	\
    (This)->lpVtbl -> enumProviders(This,dwIndex,dwFlags,pbstrProvName)

#define ICEnroll3_enumContainers(This,dwIndex,pbstr)	\
    (This)->lpVtbl -> enumContainers(This,dwIndex,pbstr)

#define ICEnroll3_freeRequestInfo(This,PKCS7OrPKCS10)	\
    (This)->lpVtbl -> freeRequestInfo(This,PKCS7OrPKCS10)

#define ICEnroll3_get_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_MyStoreName(This,pbstrName)

#define ICEnroll3_put_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_MyStoreName(This,pbstrName)

#define ICEnroll3_get_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_MyStoreType(This,pbstrType)

#define ICEnroll3_put_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_MyStoreType(This,pbstrType)

#define ICEnroll3_get_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_MyStoreFlags(This,pdwFlags)

#define ICEnroll3_put_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_MyStoreFlags(This,pdwFlags)

#define ICEnroll3_get_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_CAStoreName(This,pbstrName)

#define ICEnroll3_put_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_CAStoreName(This,pbstrName)

#define ICEnroll3_get_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_CAStoreType(This,pbstrType)

#define ICEnroll3_put_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_CAStoreType(This,pbstrType)

#define ICEnroll3_get_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_CAStoreFlags(This,pdwFlags)

#define ICEnroll3_put_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_CAStoreFlags(This,pdwFlags)

#define ICEnroll3_get_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RootStoreName(This,pbstrName)

#define ICEnroll3_put_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RootStoreName(This,pbstrName)

#define ICEnroll3_get_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RootStoreType(This,pbstrType)

#define ICEnroll3_put_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RootStoreType(This,pbstrType)

#define ICEnroll3_get_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RootStoreFlags(This,pdwFlags)

#define ICEnroll3_put_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RootStoreFlags(This,pdwFlags)

#define ICEnroll3_get_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RequestStoreName(This,pbstrName)

#define ICEnroll3_put_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RequestStoreName(This,pbstrName)

#define ICEnroll3_get_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RequestStoreType(This,pbstrType)

#define ICEnroll3_put_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RequestStoreType(This,pbstrType)

#define ICEnroll3_get_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RequestStoreFlags(This,pdwFlags)

#define ICEnroll3_put_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RequestStoreFlags(This,pdwFlags)

#define ICEnroll3_get_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> get_ContainerName(This,pbstrContainer)

#define ICEnroll3_put_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> put_ContainerName(This,pbstrContainer)

#define ICEnroll3_get_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrProvider)

#define ICEnroll3_put_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> put_ProviderName(This,pbstrProvider)

#define ICEnroll3_get_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> get_ProviderType(This,pdwType)

#define ICEnroll3_put_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> put_ProviderType(This,pdwType)

#define ICEnroll3_get_KeySpec(This,pdw)	\
    (This)->lpVtbl -> get_KeySpec(This,pdw)

#define ICEnroll3_put_KeySpec(This,pdw)	\
    (This)->lpVtbl -> put_KeySpec(This,pdw)

#define ICEnroll3_get_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_ProviderFlags(This,pdwFlags)

#define ICEnroll3_put_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_ProviderFlags(This,pdwFlags)

#define ICEnroll3_get_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> get_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll3_put_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> put_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll3_get_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_GenKeyFlags(This,pdwFlags)

#define ICEnroll3_put_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_GenKeyFlags(This,pdwFlags)

#define ICEnroll3_get_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> get_DeleteRequestCert(This,fDelete)

#define ICEnroll3_put_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> put_DeleteRequestCert(This,fDelete)

#define ICEnroll3_get_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToCSP(This,fBool)

#define ICEnroll3_put_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToCSP(This,fBool)

#define ICEnroll3_get_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> get_SPCFileName(This,pbstr)

#define ICEnroll3_put_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> put_SPCFileName(This,pbstr)

#define ICEnroll3_get_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> get_PVKFileName(This,pbstr)

#define ICEnroll3_put_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> put_PVKFileName(This,pbstr)

#define ICEnroll3_get_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> get_HashAlgorithm(This,pbstr)

#define ICEnroll3_put_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> put_HashAlgorithm(This,pbstr)


#define ICEnroll3_addCertTypeToRequest(This,CertType)	\
    (This)->lpVtbl -> addCertTypeToRequest(This,CertType)

#define ICEnroll3_addNameValuePairToSignature(This,Name,Value)	\
    (This)->lpVtbl -> addNameValuePairToSignature(This,Name,Value)

#define ICEnroll3_get_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToUserDS(This,fBool)

#define ICEnroll3_put_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToUserDS(This,fBool)

#define ICEnroll3_get_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> get_EnableT61DNEncoding(This,fBool)

#define ICEnroll3_put_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> put_EnableT61DNEncoding(This,fBool)


#define ICEnroll3_InstallPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> InstallPKCS7(This,PKCS7)

#define ICEnroll3_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define ICEnroll3_GetSupportedKeySpec(This,pdwKeySpec)	\
    (This)->lpVtbl -> GetSupportedKeySpec(This,pdwKeySpec)

#define ICEnroll3_GetKeyLen(This,fMin,fExchange,pdwKeySize)	\
    (This)->lpVtbl -> GetKeyLen(This,fMin,fExchange,pdwKeySize)

#define ICEnroll3_EnumAlgs(This,dwIndex,algClass,pdwAlgID)	\
    (This)->lpVtbl -> EnumAlgs(This,dwIndex,algClass,pdwAlgID)

#define ICEnroll3_GetAlgName(This,algID,pbstr)	\
    (This)->lpVtbl -> GetAlgName(This,algID,pbstr)

#define ICEnroll3_put_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)	\
    (This)->lpVtbl -> put_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)

#define ICEnroll3_get_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)	\
    (This)->lpVtbl -> get_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)

#define ICEnroll3_put_HashAlgID(This,HashAlgID)	\
    (This)->lpVtbl -> put_HashAlgID(This,HashAlgID)

#define ICEnroll3_get_HashAlgID(This,HashAlgID)	\
    (This)->lpVtbl -> get_HashAlgID(This,HashAlgID)

#define ICEnroll3_put_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)	\
    (This)->lpVtbl -> put_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)

#define ICEnroll3_get_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)	\
    (This)->lpVtbl -> get_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)

#define ICEnroll3_put_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)	\
    (This)->lpVtbl -> put_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)

#define ICEnroll3_get_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)	\
    (This)->lpVtbl -> get_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_InstallPKCS7_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ BSTR PKCS7);


void __RPC_STUB ICEnroll3_InstallPKCS7_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_Reset_Proxy( 
    ICEnroll3 __RPC_FAR * This);


void __RPC_STUB ICEnroll3_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_GetSupportedKeySpec_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pdwKeySpec);


void __RPC_STUB ICEnroll3_GetSupportedKeySpec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_GetKeyLen_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long fMin,
    /* [in] */ long fExchange,
    /* [retval][out] */ long __RPC_FAR *pdwKeySize);


void __RPC_STUB ICEnroll3_GetKeyLen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_EnumAlgs_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long dwIndex,
    /* [in] */ long algClass,
    /* [retval][out] */ long __RPC_FAR *pdwAlgID);


void __RPC_STUB ICEnroll3_EnumAlgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_GetAlgName_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long algID,
    /* [retval][out] */ BSTR __RPC_FAR *pbstr);


void __RPC_STUB ICEnroll3_GetAlgName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_put_ReuseHardwareKeyIfUnableToGenNew_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long fReuseHardwareKeyIfUnableToGenNew);


void __RPC_STUB ICEnroll3_put_ReuseHardwareKeyIfUnableToGenNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_get_ReuseHardwareKeyIfUnableToGenNew_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fReuseHardwareKeyIfUnableToGenNew);


void __RPC_STUB ICEnroll3_get_ReuseHardwareKeyIfUnableToGenNew_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_put_HashAlgID_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long HashAlgID);


void __RPC_STUB ICEnroll3_put_HashAlgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_get_HashAlgID_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *HashAlgID);


void __RPC_STUB ICEnroll3_get_HashAlgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_put_LimitExchangeKeyToEncipherment_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long fLimitExchangeKeyToEncipherment);


void __RPC_STUB ICEnroll3_put_LimitExchangeKeyToEncipherment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_get_LimitExchangeKeyToEncipherment_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fLimitExchangeKeyToEncipherment);


void __RPC_STUB ICEnroll3_get_LimitExchangeKeyToEncipherment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_put_EnableSMIMECapabilities_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [in] */ long fEnableSMIMECapabilities);


void __RPC_STUB ICEnroll3_put_EnableSMIMECapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll3_get_EnableSMIMECapabilities_Proxy( 
    ICEnroll3 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *fEnableSMIMECapabilities);


void __RPC_STUB ICEnroll3_get_EnableSMIMECapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICEnroll3_INTERFACE_DEFINED__ */



#ifndef __ICEnroll4_INTERFACE_DEFINED__
#define __ICEnroll4_INTERFACE_DEFINED__



/* interface ICEnroll4 */
/* [object][oleautomation][dual][helpstring][uuid] */ 


EXTERN_C const IID IID_ICEnroll4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1F1188A-2EB5-4A80-841B-7E729A356D90")
    ICEnroll4 : public ICEnroll3
    {
    public:
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_PrivateKeyArchiveCertificate( 
            /* [in] */ BSTR pbstrCert) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_PrivateKeyArchiveCertificate( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ThumbPrint( 
            /* [in] */ BSTR pbstrThumbPrint) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ThumbPrint( 
            /* [retval][out] */ BSTR __RPC_FAR *pbstrThumbPrint) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE binaryToString( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strBinary,
            /* [retval][out] */ BSTR __RPC_FAR *pstrEncoded) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE stringToBinary( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strEncoded,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addExtensionToRequest( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addAttributeToRequest( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addNameValuePairToRequest( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE resetExtensions( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE resetAttributes( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createRequest( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strDNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pstrRequest) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createFileRequest( 
            /* [in] */ long Flags,
            /* [in] */ BSTR strDNName,
            /* [in] */ BSTR strUsage,
            /* [in] */ BSTR strRequestFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE acceptResponse( 
            /* [in] */ BSTR strResponse) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE acceptFileResponse( 
            /* [in] */ BSTR strResponseFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getCertFromResponse( 
            /* [in] */ BSTR strResponse,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCert) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getCertFromFileResponse( 
            /* [in] */ BSTR strResponseFileName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCert) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createPFX( 
            /* [in] */ BSTR strPassword,
            /* [retval][out] */ BSTR __RPC_FAR *pstrPFX) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE createFilePFX( 
            /* [in] */ BSTR strPassword,
            /* [in] */ BSTR strPFXFileName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE setPendingRequestInfo( 
            /* [in] */ long lRequestID,
            /* [in] */ BSTR strCADNS,
            /* [in] */ BSTR strCAName,
            /* [in] */ BSTR strFriendlyName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE enumPendingRequest( 
            /* [in] */ long lIndex,
            /* [in] */ long lDesiredProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarProperty) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE removePendingRequest( 
            /* [in] */ BSTR strThumbprint) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetKeyLenEx( 
            /* [in] */ long lSizeSpec,
            /* [in] */ long lKeySpec,
            /* [retval][out] */ long __RPC_FAR *pdwKeySize) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE InstallPKCS7Ex( 
            /* [in] */ BSTR PKCS7,
            /* [retval][out] */ long __RPC_FAR *plCertInstalled) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addCertTypeToRequestEx( 
            /* [in] */ long lType,
            /* [in] */ BSTR bstrOIDOrName,
            /* [in] */ long lMajorVersion,
            /* [in] */ long fMinorVersion,
            /* [in] */ long lMinorVersion) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE getProviderType( 
            /* [in] */ BSTR strProvName,
            /* [retval][out] */ long __RPC_FAR *plProvType) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_SignerCertificate( 
            /* [in] */ BSTR rhs) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_ClientId( 
            /* [in] */ long plClientId) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_ClientId( 
            /* [retval][out] */ long __RPC_FAR *plClientId) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE addBlobPropertyToCertificate( 
            /* [in] */ long lPropertyId,
            /* [in] */ long lReserved,
            /* [in] */ BSTR bstrProperty) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE resetBlobProperties( void) = 0;
        
        virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE put_IncludeSubjectKeyID( 
            /* [in] */ long pfInclude) = 0;
        
        virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE get_IncludeSubjectKeyID( 
            /* [retval][out] */ long __RPC_FAR *pfInclude) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICEnroll4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICEnroll4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICEnroll4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ICEnroll4 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFilePKCS10 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [in] */ BSTR wszPKCS10FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptFilePKCS7 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7FileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPKCS10 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR DNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pPKCS10);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptPKCS7 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromPKCS7 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR wszPKCS7,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumProviders )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long dwFlags,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumContainers )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *freeRequestInfo )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7OrPKCS10);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MyStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MyStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CAStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CAStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RootStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RootStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrName);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrName);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RequestStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RequestStoreFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ContainerName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrContainer);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ContainerName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrContainer);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrProvider);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrProvider);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwType);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeySpec )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdw);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeySpec )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdw);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProviderFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProviderFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseExistingKeySet )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fUseExistingKeys);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseExistingKeySet )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fUseExistingKeys);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GenKeyFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwFlags);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GenKeyFlags )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pdwFlags);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteRequestCert )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fDelete);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteRequestCert )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fDelete);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToCSP )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToCSP )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SPCFileName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SPCFileName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PVKFileName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PVKFileName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgorithm )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgorithm )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addCertTypeToRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR CertType);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addNameValuePairToSignature )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR Name,
            /* [in] */ BSTR Value);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteCertToUserDS )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteCertToUserDS )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableT61DNEncoding )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fBool);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableT61DNEncoding )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fBool);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstallPKCS7 )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            ICEnroll4 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSupportedKeySpec )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pdwKeySpec);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetKeyLen )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fMin,
            /* [in] */ long fExchange,
            /* [retval][out] */ long __RPC_FAR *pdwKeySize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumAlgs )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long dwIndex,
            /* [in] */ long algClass,
            /* [retval][out] */ long __RPC_FAR *pdwAlgID);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlgName )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long algID,
            /* [retval][out] */ BSTR __RPC_FAR *pbstr);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReuseHardwareKeyIfUnableToGenNew )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fReuseHardwareKeyIfUnableToGenNew);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReuseHardwareKeyIfUnableToGenNew )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fReuseHardwareKeyIfUnableToGenNew);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HashAlgID )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long HashAlgID);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HashAlgID )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *HashAlgID);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LimitExchangeKeyToEncipherment )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fLimitExchangeKeyToEncipherment);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LimitExchangeKeyToEncipherment )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fLimitExchangeKeyToEncipherment);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableSMIMECapabilities )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long fEnableSMIMECapabilities);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EnableSMIMECapabilities )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *fEnableSMIMECapabilities);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PrivateKeyArchiveCertificate )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrCert);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PrivateKeyArchiveCertificate )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ThumbPrint )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR pbstrThumbPrint);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ThumbPrint )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pbstrThumbPrint);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *binaryToString )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strBinary,
            /* [retval][out] */ BSTR __RPC_FAR *pstrEncoded);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stringToBinary )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strEncoded,
            /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addExtensionToRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addAttributeToRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addNameValuePairToRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strValue);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *resetExtensions )( 
            ICEnroll4 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *resetAttributes )( 
            ICEnroll4 __RPC_FAR * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strDNName,
            /* [in] */ BSTR Usage,
            /* [retval][out] */ BSTR __RPC_FAR *pstrRequest);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFileRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long Flags,
            /* [in] */ BSTR strDNName,
            /* [in] */ BSTR strUsage,
            /* [in] */ BSTR strRequestFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptResponse )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strResponse);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *acceptFileResponse )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strResponseFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromResponse )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strResponse,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getCertFromFileResponse )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strResponseFileName,
            /* [retval][out] */ BSTR __RPC_FAR *pstrCert);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createPFX )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strPassword,
            /* [retval][out] */ BSTR __RPC_FAR *pstrPFX);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *createFilePFX )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strPassword,
            /* [in] */ BSTR strPFXFileName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setPendingRequestInfo )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long lRequestID,
            /* [in] */ BSTR strCADNS,
            /* [in] */ BSTR strCAName,
            /* [in] */ BSTR strFriendlyName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *enumPendingRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long lIndex,
            /* [in] */ long lDesiredProperty,
            /* [retval][out] */ VARIANT __RPC_FAR *pvarProperty);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *removePendingRequest )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strThumbprint);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetKeyLenEx )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long lSizeSpec,
            /* [in] */ long lKeySpec,
            /* [retval][out] */ long __RPC_FAR *pdwKeySize);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstallPKCS7Ex )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR PKCS7,
            /* [retval][out] */ long __RPC_FAR *plCertInstalled);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addCertTypeToRequestEx )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long lType,
            /* [in] */ BSTR bstrOIDOrName,
            /* [in] */ long lMajorVersion,
            /* [in] */ long fMinorVersion,
            /* [in] */ long lMinorVersion);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getProviderType )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR strProvName,
            /* [retval][out] */ long __RPC_FAR *plProvType);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignerCertificate )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ BSTR rhs);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ClientId )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long plClientId);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ClientId )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *plClientId);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *addBlobPropertyToCertificate )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long lPropertyId,
            /* [in] */ long lReserved,
            /* [in] */ BSTR bstrProperty);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *resetBlobProperties )( 
            ICEnroll4 __RPC_FAR * This);
        
        /* [propput][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IncludeSubjectKeyID )( 
            ICEnroll4 __RPC_FAR * This,
            /* [in] */ long pfInclude);
        
        /* [propget][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IncludeSubjectKeyID )( 
            ICEnroll4 __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pfInclude);
        
        END_INTERFACE
    } ICEnroll4Vtbl;

    interface ICEnroll4
    {
        CONST_VTBL struct ICEnroll4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICEnroll4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICEnroll4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICEnroll4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICEnroll4_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICEnroll4_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICEnroll4_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICEnroll4_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICEnroll4_createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)	\
    (This)->lpVtbl -> createFilePKCS10(This,DNName,Usage,wszPKCS10FileName)

#define ICEnroll4_acceptFilePKCS7(This,wszPKCS7FileName)	\
    (This)->lpVtbl -> acceptFilePKCS7(This,wszPKCS7FileName)

#define ICEnroll4_createPKCS10(This,DNName,Usage,pPKCS10)	\
    (This)->lpVtbl -> createPKCS10(This,DNName,Usage,pPKCS10)

#define ICEnroll4_acceptPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> acceptPKCS7(This,PKCS7)

#define ICEnroll4_getCertFromPKCS7(This,wszPKCS7,pbstrCert)	\
    (This)->lpVtbl -> getCertFromPKCS7(This,wszPKCS7,pbstrCert)

#define ICEnroll4_enumProviders(This,dwIndex,dwFlags,pbstrProvName)	\
    (This)->lpVtbl -> enumProviders(This,dwIndex,dwFlags,pbstrProvName)

#define ICEnroll4_enumContainers(This,dwIndex,pbstr)	\
    (This)->lpVtbl -> enumContainers(This,dwIndex,pbstr)

#define ICEnroll4_freeRequestInfo(This,PKCS7OrPKCS10)	\
    (This)->lpVtbl -> freeRequestInfo(This,PKCS7OrPKCS10)

#define ICEnroll4_get_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_MyStoreName(This,pbstrName)

#define ICEnroll4_put_MyStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_MyStoreName(This,pbstrName)

#define ICEnroll4_get_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_MyStoreType(This,pbstrType)

#define ICEnroll4_put_MyStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_MyStoreType(This,pbstrType)

#define ICEnroll4_get_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_MyStoreFlags(This,pdwFlags)

#define ICEnroll4_put_MyStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_MyStoreFlags(This,pdwFlags)

#define ICEnroll4_get_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_CAStoreName(This,pbstrName)

#define ICEnroll4_put_CAStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_CAStoreName(This,pbstrName)

#define ICEnroll4_get_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_CAStoreType(This,pbstrType)

#define ICEnroll4_put_CAStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_CAStoreType(This,pbstrType)

#define ICEnroll4_get_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_CAStoreFlags(This,pdwFlags)

#define ICEnroll4_put_CAStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_CAStoreFlags(This,pdwFlags)

#define ICEnroll4_get_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RootStoreName(This,pbstrName)

#define ICEnroll4_put_RootStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RootStoreName(This,pbstrName)

#define ICEnroll4_get_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RootStoreType(This,pbstrType)

#define ICEnroll4_put_RootStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RootStoreType(This,pbstrType)

#define ICEnroll4_get_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RootStoreFlags(This,pdwFlags)

#define ICEnroll4_put_RootStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RootStoreFlags(This,pdwFlags)

#define ICEnroll4_get_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> get_RequestStoreName(This,pbstrName)

#define ICEnroll4_put_RequestStoreName(This,pbstrName)	\
    (This)->lpVtbl -> put_RequestStoreName(This,pbstrName)

#define ICEnroll4_get_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> get_RequestStoreType(This,pbstrType)

#define ICEnroll4_put_RequestStoreType(This,pbstrType)	\
    (This)->lpVtbl -> put_RequestStoreType(This,pbstrType)

#define ICEnroll4_get_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_RequestStoreFlags(This,pdwFlags)

#define ICEnroll4_put_RequestStoreFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_RequestStoreFlags(This,pdwFlags)

#define ICEnroll4_get_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> get_ContainerName(This,pbstrContainer)

#define ICEnroll4_put_ContainerName(This,pbstrContainer)	\
    (This)->lpVtbl -> put_ContainerName(This,pbstrContainer)

#define ICEnroll4_get_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> get_ProviderName(This,pbstrProvider)

#define ICEnroll4_put_ProviderName(This,pbstrProvider)	\
    (This)->lpVtbl -> put_ProviderName(This,pbstrProvider)

#define ICEnroll4_get_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> get_ProviderType(This,pdwType)

#define ICEnroll4_put_ProviderType(This,pdwType)	\
    (This)->lpVtbl -> put_ProviderType(This,pdwType)

#define ICEnroll4_get_KeySpec(This,pdw)	\
    (This)->lpVtbl -> get_KeySpec(This,pdw)

#define ICEnroll4_put_KeySpec(This,pdw)	\
    (This)->lpVtbl -> put_KeySpec(This,pdw)

#define ICEnroll4_get_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_ProviderFlags(This,pdwFlags)

#define ICEnroll4_put_ProviderFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_ProviderFlags(This,pdwFlags)

#define ICEnroll4_get_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> get_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll4_put_UseExistingKeySet(This,fUseExistingKeys)	\
    (This)->lpVtbl -> put_UseExistingKeySet(This,fUseExistingKeys)

#define ICEnroll4_get_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> get_GenKeyFlags(This,pdwFlags)

#define ICEnroll4_put_GenKeyFlags(This,pdwFlags)	\
    (This)->lpVtbl -> put_GenKeyFlags(This,pdwFlags)

#define ICEnroll4_get_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> get_DeleteRequestCert(This,fDelete)

#define ICEnroll4_put_DeleteRequestCert(This,fDelete)	\
    (This)->lpVtbl -> put_DeleteRequestCert(This,fDelete)

#define ICEnroll4_get_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToCSP(This,fBool)

#define ICEnroll4_put_WriteCertToCSP(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToCSP(This,fBool)

#define ICEnroll4_get_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> get_SPCFileName(This,pbstr)

#define ICEnroll4_put_SPCFileName(This,pbstr)	\
    (This)->lpVtbl -> put_SPCFileName(This,pbstr)

#define ICEnroll4_get_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> get_PVKFileName(This,pbstr)

#define ICEnroll4_put_PVKFileName(This,pbstr)	\
    (This)->lpVtbl -> put_PVKFileName(This,pbstr)

#define ICEnroll4_get_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> get_HashAlgorithm(This,pbstr)

#define ICEnroll4_put_HashAlgorithm(This,pbstr)	\
    (This)->lpVtbl -> put_HashAlgorithm(This,pbstr)


#define ICEnroll4_addCertTypeToRequest(This,CertType)	\
    (This)->lpVtbl -> addCertTypeToRequest(This,CertType)

#define ICEnroll4_addNameValuePairToSignature(This,Name,Value)	\
    (This)->lpVtbl -> addNameValuePairToSignature(This,Name,Value)

#define ICEnroll4_get_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> get_WriteCertToUserDS(This,fBool)

#define ICEnroll4_put_WriteCertToUserDS(This,fBool)	\
    (This)->lpVtbl -> put_WriteCertToUserDS(This,fBool)

#define ICEnroll4_get_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> get_EnableT61DNEncoding(This,fBool)

#define ICEnroll4_put_EnableT61DNEncoding(This,fBool)	\
    (This)->lpVtbl -> put_EnableT61DNEncoding(This,fBool)


#define ICEnroll4_InstallPKCS7(This,PKCS7)	\
    (This)->lpVtbl -> InstallPKCS7(This,PKCS7)

#define ICEnroll4_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define ICEnroll4_GetSupportedKeySpec(This,pdwKeySpec)	\
    (This)->lpVtbl -> GetSupportedKeySpec(This,pdwKeySpec)

#define ICEnroll4_GetKeyLen(This,fMin,fExchange,pdwKeySize)	\
    (This)->lpVtbl -> GetKeyLen(This,fMin,fExchange,pdwKeySize)

#define ICEnroll4_EnumAlgs(This,dwIndex,algClass,pdwAlgID)	\
    (This)->lpVtbl -> EnumAlgs(This,dwIndex,algClass,pdwAlgID)

#define ICEnroll4_GetAlgName(This,algID,pbstr)	\
    (This)->lpVtbl -> GetAlgName(This,algID,pbstr)

#define ICEnroll4_put_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)	\
    (This)->lpVtbl -> put_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)

#define ICEnroll4_get_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)	\
    (This)->lpVtbl -> get_ReuseHardwareKeyIfUnableToGenNew(This,fReuseHardwareKeyIfUnableToGenNew)

#define ICEnroll4_put_HashAlgID(This,HashAlgID)	\
    (This)->lpVtbl -> put_HashAlgID(This,HashAlgID)

#define ICEnroll4_get_HashAlgID(This,HashAlgID)	\
    (This)->lpVtbl -> get_HashAlgID(This,HashAlgID)

#define ICEnroll4_put_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)	\
    (This)->lpVtbl -> put_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)

#define ICEnroll4_get_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)	\
    (This)->lpVtbl -> get_LimitExchangeKeyToEncipherment(This,fLimitExchangeKeyToEncipherment)

#define ICEnroll4_put_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)	\
    (This)->lpVtbl -> put_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)

#define ICEnroll4_get_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)	\
    (This)->lpVtbl -> get_EnableSMIMECapabilities(This,fEnableSMIMECapabilities)


#define ICEnroll4_put_PrivateKeyArchiveCertificate(This,pbstrCert)	\
    (This)->lpVtbl -> put_PrivateKeyArchiveCertificate(This,pbstrCert)

#define ICEnroll4_get_PrivateKeyArchiveCertificate(This,pbstrCert)	\
    (This)->lpVtbl -> get_PrivateKeyArchiveCertificate(This,pbstrCert)

#define ICEnroll4_put_ThumbPrint(This,pbstrThumbPrint)	\
    (This)->lpVtbl -> put_ThumbPrint(This,pbstrThumbPrint)

#define ICEnroll4_get_ThumbPrint(This,pbstrThumbPrint)	\
    (This)->lpVtbl -> get_ThumbPrint(This,pbstrThumbPrint)

#define ICEnroll4_binaryToString(This,Flags,strBinary,pstrEncoded)	\
    (This)->lpVtbl -> binaryToString(This,Flags,strBinary,pstrEncoded)

#define ICEnroll4_stringToBinary(This,Flags,strEncoded,pstrBinary)	\
    (This)->lpVtbl -> stringToBinary(This,Flags,strEncoded,pstrBinary)

#define ICEnroll4_addExtensionToRequest(This,Flags,strName,strValue)	\
    (This)->lpVtbl -> addExtensionToRequest(This,Flags,strName,strValue)

#define ICEnroll4_addAttributeToRequest(This,Flags,strName,strValue)	\
    (This)->lpVtbl -> addAttributeToRequest(This,Flags,strName,strValue)

#define ICEnroll4_addNameValuePairToRequest(This,Flags,strName,strValue)	\
    (This)->lpVtbl -> addNameValuePairToRequest(This,Flags,strName,strValue)

#define ICEnroll4_resetExtensions(This)	\
    (This)->lpVtbl -> resetExtensions(This)

#define ICEnroll4_resetAttributes(This)	\
    (This)->lpVtbl -> resetAttributes(This)

#define ICEnroll4_createRequest(This,Flags,strDNName,Usage,pstrRequest)	\
    (This)->lpVtbl -> createRequest(This,Flags,strDNName,Usage,pstrRequest)

#define ICEnroll4_createFileRequest(This,Flags,strDNName,strUsage,strRequestFileName)	\
    (This)->lpVtbl -> createFileRequest(This,Flags,strDNName,strUsage,strRequestFileName)

#define ICEnroll4_acceptResponse(This,strResponse)	\
    (This)->lpVtbl -> acceptResponse(This,strResponse)

#define ICEnroll4_acceptFileResponse(This,strResponseFileName)	\
    (This)->lpVtbl -> acceptFileResponse(This,strResponseFileName)

#define ICEnroll4_getCertFromResponse(This,strResponse,pstrCert)	\
    (This)->lpVtbl -> getCertFromResponse(This,strResponse,pstrCert)

#define ICEnroll4_getCertFromFileResponse(This,strResponseFileName,pstrCert)	\
    (This)->lpVtbl -> getCertFromFileResponse(This,strResponseFileName,pstrCert)

#define ICEnroll4_createPFX(This,strPassword,pstrPFX)	\
    (This)->lpVtbl -> createPFX(This,strPassword,pstrPFX)

#define ICEnroll4_createFilePFX(This,strPassword,strPFXFileName)	\
    (This)->lpVtbl -> createFilePFX(This,strPassword,strPFXFileName)

#define ICEnroll4_setPendingRequestInfo(This,lRequestID,strCADNS,strCAName,strFriendlyName)	\
    (This)->lpVtbl -> setPendingRequestInfo(This,lRequestID,strCADNS,strCAName,strFriendlyName)

#define ICEnroll4_enumPendingRequest(This,lIndex,lDesiredProperty,pvarProperty)	\
    (This)->lpVtbl -> enumPendingRequest(This,lIndex,lDesiredProperty,pvarProperty)

#define ICEnroll4_removePendingRequest(This,strThumbprint)	\
    (This)->lpVtbl -> removePendingRequest(This,strThumbprint)

#define ICEnroll4_GetKeyLenEx(This,lSizeSpec,lKeySpec,pdwKeySize)	\
    (This)->lpVtbl -> GetKeyLenEx(This,lSizeSpec,lKeySpec,pdwKeySize)

#define ICEnroll4_InstallPKCS7Ex(This,PKCS7,plCertInstalled)	\
    (This)->lpVtbl -> InstallPKCS7Ex(This,PKCS7,plCertInstalled)

#define ICEnroll4_addCertTypeToRequestEx(This,lType,bstrOIDOrName,lMajorVersion,fMinorVersion,lMinorVersion)	\
    (This)->lpVtbl -> addCertTypeToRequestEx(This,lType,bstrOIDOrName,lMajorVersion,fMinorVersion,lMinorVersion)

#define ICEnroll4_getProviderType(This,strProvName,plProvType)	\
    (This)->lpVtbl -> getProviderType(This,strProvName,plProvType)

#define ICEnroll4_put_SignerCertificate(This,rhs)	\
    (This)->lpVtbl -> put_SignerCertificate(This,rhs)

#define ICEnroll4_put_ClientId(This,plClientId)	\
    (This)->lpVtbl -> put_ClientId(This,plClientId)

#define ICEnroll4_get_ClientId(This,plClientId)	\
    (This)->lpVtbl -> get_ClientId(This,plClientId)

#define ICEnroll4_addBlobPropertyToCertificate(This,lPropertyId,lReserved,bstrProperty)	\
    (This)->lpVtbl -> addBlobPropertyToCertificate(This,lPropertyId,lReserved,bstrProperty)

#define ICEnroll4_resetBlobProperties(This)	\
    (This)->lpVtbl -> resetBlobProperties(This)

#define ICEnroll4_put_IncludeSubjectKeyID(This,pfInclude)	\
    (This)->lpVtbl -> put_IncludeSubjectKeyID(This,pfInclude)

#define ICEnroll4_get_IncludeSubjectKeyID(This,pfInclude)	\
    (This)->lpVtbl -> get_IncludeSubjectKeyID(This,pfInclude)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_put_PrivateKeyArchiveCertificate_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR pbstrCert);


void __RPC_STUB ICEnroll4_put_PrivateKeyArchiveCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_get_PrivateKeyArchiveCertificate_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrCert);


void __RPC_STUB ICEnroll4_get_PrivateKeyArchiveCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_put_ThumbPrint_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR pbstrThumbPrint);


void __RPC_STUB ICEnroll4_put_ThumbPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_get_ThumbPrint_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pbstrThumbPrint);


void __RPC_STUB ICEnroll4_get_ThumbPrint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_binaryToString_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strBinary,
    /* [retval][out] */ BSTR __RPC_FAR *pstrEncoded);


void __RPC_STUB ICEnroll4_binaryToString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_stringToBinary_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strEncoded,
    /* [retval][out] */ BSTR __RPC_FAR *pstrBinary);


void __RPC_STUB ICEnroll4_stringToBinary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_addExtensionToRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strName,
    /* [in] */ BSTR strValue);


void __RPC_STUB ICEnroll4_addExtensionToRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_addAttributeToRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strName,
    /* [in] */ BSTR strValue);


void __RPC_STUB ICEnroll4_addAttributeToRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_addNameValuePairToRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strName,
    /* [in] */ BSTR strValue);


void __RPC_STUB ICEnroll4_addNameValuePairToRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_resetExtensions_Proxy( 
    ICEnroll4 __RPC_FAR * This);


void __RPC_STUB ICEnroll4_resetExtensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_resetAttributes_Proxy( 
    ICEnroll4 __RPC_FAR * This);


void __RPC_STUB ICEnroll4_resetAttributes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_createRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strDNName,
    /* [in] */ BSTR Usage,
    /* [retval][out] */ BSTR __RPC_FAR *pstrRequest);


void __RPC_STUB ICEnroll4_createRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_createFileRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long Flags,
    /* [in] */ BSTR strDNName,
    /* [in] */ BSTR strUsage,
    /* [in] */ BSTR strRequestFileName);


void __RPC_STUB ICEnroll4_createFileRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_acceptResponse_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strResponse);


void __RPC_STUB ICEnroll4_acceptResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_acceptFileResponse_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strResponseFileName);


void __RPC_STUB ICEnroll4_acceptFileResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_getCertFromResponse_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strResponse,
    /* [retval][out] */ BSTR __RPC_FAR *pstrCert);


void __RPC_STUB ICEnroll4_getCertFromResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_getCertFromFileResponse_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strResponseFileName,
    /* [retval][out] */ BSTR __RPC_FAR *pstrCert);


void __RPC_STUB ICEnroll4_getCertFromFileResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_createPFX_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strPassword,
    /* [retval][out] */ BSTR __RPC_FAR *pstrPFX);


void __RPC_STUB ICEnroll4_createPFX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_createFilePFX_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strPassword,
    /* [in] */ BSTR strPFXFileName);


void __RPC_STUB ICEnroll4_createFilePFX_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_setPendingRequestInfo_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long lRequestID,
    /* [in] */ BSTR strCADNS,
    /* [in] */ BSTR strCAName,
    /* [in] */ BSTR strFriendlyName);


void __RPC_STUB ICEnroll4_setPendingRequestInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_enumPendingRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long lIndex,
    /* [in] */ long lDesiredProperty,
    /* [retval][out] */ VARIANT __RPC_FAR *pvarProperty);


void __RPC_STUB ICEnroll4_enumPendingRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_removePendingRequest_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strThumbprint);


void __RPC_STUB ICEnroll4_removePendingRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_GetKeyLenEx_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long lSizeSpec,
    /* [in] */ long lKeySpec,
    /* [retval][out] */ long __RPC_FAR *pdwKeySize);


void __RPC_STUB ICEnroll4_GetKeyLenEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_InstallPKCS7Ex_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR PKCS7,
    /* [retval][out] */ long __RPC_FAR *plCertInstalled);


void __RPC_STUB ICEnroll4_InstallPKCS7Ex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_addCertTypeToRequestEx_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long lType,
    /* [in] */ BSTR bstrOIDOrName,
    /* [in] */ long lMajorVersion,
    /* [in] */ long fMinorVersion,
    /* [in] */ long lMinorVersion);


void __RPC_STUB ICEnroll4_addCertTypeToRequestEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_getProviderType_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR strProvName,
    /* [retval][out] */ long __RPC_FAR *plProvType);


void __RPC_STUB ICEnroll4_getProviderType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_put_SignerCertificate_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ BSTR rhs);


void __RPC_STUB ICEnroll4_put_SignerCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_put_ClientId_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long plClientId);


void __RPC_STUB ICEnroll4_put_ClientId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_get_ClientId_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *plClientId);


void __RPC_STUB ICEnroll4_get_ClientId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_addBlobPropertyToCertificate_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long lPropertyId,
    /* [in] */ long lReserved,
    /* [in] */ BSTR bstrProperty);


void __RPC_STUB ICEnroll4_addBlobPropertyToCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_resetBlobProperties_Proxy( 
    ICEnroll4 __RPC_FAR * This);


void __RPC_STUB ICEnroll4_resetBlobProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_put_IncludeSubjectKeyID_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [in] */ long pfInclude);


void __RPC_STUB ICEnroll4_put_IncludeSubjectKeyID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget][id] */ HRESULT STDMETHODCALLTYPE ICEnroll4_get_IncludeSubjectKeyID_Proxy( 
    ICEnroll4 __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pfInclude);


void __RPC_STUB ICEnroll4_get_IncludeSubjectKeyID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICEnroll4_INTERFACE_DEFINED__ */







EXTERN_C const CLSID CLSID_CEnroll;

#ifdef __cplusplus

class DECLSPEC_UUID("43F8F289-7A20-11D0-8F06-00C04FC295E1")
CEnroll;
#endif

EXTERN_C const CLSID CLSID_CEnroll2;

#ifdef __cplusplus

class DECLSPEC_UUID("127698E4-E730-4E5C-A2B1-21490A70C8A1")
CEnroll2;
#endif
#endif /* __XENROLLLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
