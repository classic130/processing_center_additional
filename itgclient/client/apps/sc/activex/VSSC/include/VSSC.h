
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0279 */
/* at Thu Aug 30 13:35:09 2001
 */
/* Compiler settings for H:\work\itgclient\client\apps\sc\activex\VSSC\sources\VSSC.idl:
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

#ifndef __VSSC_h__
#define __VSSC_h__

/* Forward Declarations */ 

#ifndef __IVSSC_FWD_DEFINED__
#define __IVSSC_FWD_DEFINED__
typedef interface IVSSC IVSSC;
#endif 	/* __IVSSC_FWD_DEFINED__ */


#ifndef __IResolveRcpt_FWD_DEFINED__
#define __IResolveRcpt_FWD_DEFINED__
typedef interface IResolveRcpt IResolveRcpt;
#endif 	/* __IResolveRcpt_FWD_DEFINED__ */


#ifndef __IVSSignerInfo_FWD_DEFINED__
#define __IVSSignerInfo_FWD_DEFINED__
typedef interface IVSSignerInfo IVSSignerInfo;
#endif 	/* __IVSSignerInfo_FWD_DEFINED__ */


#ifndef __IVSSCDllApi_FWD_DEFINED__
#define __IVSSCDllApi_FWD_DEFINED__
typedef interface IVSSCDllApi IVSSCDllApi;
#endif 	/* __IVSSCDllApi_FWD_DEFINED__ */


#ifndef __VSSC_FWD_DEFINED__
#define __VSSC_FWD_DEFINED__

#ifdef __cplusplus
typedef class VSSC VSSC;
#else
typedef struct VSSC VSSC;
#endif /* __cplusplus */

#endif 	/* __VSSC_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IVSSC_INTERFACE_DEFINED__
#define __IVSSC_INTERFACE_DEFINED__

/* interface IVSSC */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSSC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5E8B9E1-D217-11D4-A21E-001083023D07")
    IVSSC : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Compose( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ToRecipientsInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ToRecipientsInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CcRecipientsInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CcRecipientsInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BccRecipientsInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BccRecipientsInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FromInfo( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FromInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Subject( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Subject( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MsgType( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MsgType( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Body( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Body( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetMsg( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Date( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Date( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CryptStatus( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectAttachments( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelectedAttachments( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UnSelectAttachments( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AttachedFileList( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveAttachment( 
            VARIANT __RPC_FAR *pFileName,
            VARIANT __RPC_FAR *pStatus) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MsgPostData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CertificateResolution( 
            VARIANT __RPC_FAR *in_pvarEmailInfo) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SMIMECertificateResolution( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertResolveURL( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSSCPTA( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Decompose( 
            /* [in] */ VARIANT __RPC_FAR *i_pvarSMIMEMsg,
            /* [out][in] */ VARIANT __RPC_FAR *i_pvarStatusType) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyRecipCert( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseProxyRecipCert( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            VARIANT __RPC_FAR *i_pMsgObjID,
            VARIANT __RPC_FAR *i_pMode) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetMode( 
            VARIANT __RPC_FAR *i_pModeType) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MsgObjID( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MsgBlobSize( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InternetInitialize( 
            VARIANT __RPC_FAR *in_pvarURL,
            VARIANT __RPC_FAR *in_pvarMethod,
            VARIANT __RPC_FAR *in_pvarPostData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InternetSendRequest( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseInternetData( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InternetDataSize( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InternetData( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeVarType( 
            VARIANT __RPC_FAR *in_pvarByteArray,
            VARIANT __RPC_FAR *in_pvarType,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarOutputType) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectedAttachmentSize( 
            VARIANT __RPC_FAR *in_pvarFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileSize) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSSignerInfo( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSSCResolveInfo( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddSignerCertificate( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddRFC822Header( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddMIMEHeader( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpaqueSign( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddSenderRecipientInfo( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SCType( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SCType( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CertificateTimeOut( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CertificateTimeOut( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MessageTimeOut( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MessageTimeOut( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearAll( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UsePKCS7Certificate( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddSMIMECapabilities( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSSCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSSC __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSSC __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSSC __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Compose )( 
            IVSSC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ToRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ToRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CcRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CcRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BccRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BccRecipientsInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FromInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FromInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Subject )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Subject )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MsgType )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MsgType )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Body )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Body )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetMsg )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Date )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Date )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CryptStatus )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectAttachments )( 
            IVSSC __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelectedAttachments )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UnSelectAttachments )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AttachedFileList )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveAttachment )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *pFileName,
            VARIANT __RPC_FAR *pStatus);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MsgPostData )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CertificateResolution )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarEmailInfo);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SMIMECertificateResolution )( 
            IVSSC __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertResolveURL )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSSCPTA )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Decompose )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT __RPC_FAR *i_pvarSMIMEMsg,
            /* [out][in] */ VARIANT __RPC_FAR *i_pvarStatusType);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyRecipCert )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseProxyRecipCert )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pMsgObjID,
            VARIANT __RPC_FAR *i_pMode);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMode )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pModeType);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MsgObjID )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MsgBlobSize )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InternetInitialize )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarURL,
            VARIANT __RPC_FAR *in_pvarMethod,
            VARIANT __RPC_FAR *in_pvarPostData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InternetSendRequest )( 
            IVSSC __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseInternetData )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InternetDataSize )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_InternetData )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeVarType )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarByteArray,
            VARIANT __RPC_FAR *in_pvarType,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarOutputType);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectedAttachmentSize )( 
            IVSSC __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileSize);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSSignerInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSSCResolveInfo )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddSignerCertificate )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddRFC822Header )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddMIMEHeader )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpaqueSign )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddSenderRecipientInfo )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SCType )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SCType )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CertificateTimeOut )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CertificateTimeOut )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MessageTimeOut )( 
            IVSSC __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MessageTimeOut )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearAll )( 
            IVSSC __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UsePKCS7Certificate )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddSMIMECapabilities )( 
            IVSSC __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IVSSCVtbl;

    interface IVSSC
    {
        CONST_VTBL struct IVSSCVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSSC_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSSC_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSSC_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSSC_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSSC_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSSC_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSSC_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSSC_Compose(This)	\
    (This)->lpVtbl -> Compose(This)

#define IVSSC_get_ToRecipientsInfo(This,pVal)	\
    (This)->lpVtbl -> get_ToRecipientsInfo(This,pVal)

#define IVSSC_put_ToRecipientsInfo(This,newVal)	\
    (This)->lpVtbl -> put_ToRecipientsInfo(This,newVal)

#define IVSSC_get_CcRecipientsInfo(This,pVal)	\
    (This)->lpVtbl -> get_CcRecipientsInfo(This,pVal)

#define IVSSC_put_CcRecipientsInfo(This,newVal)	\
    (This)->lpVtbl -> put_CcRecipientsInfo(This,newVal)

#define IVSSC_get_BccRecipientsInfo(This,pVal)	\
    (This)->lpVtbl -> get_BccRecipientsInfo(This,pVal)

#define IVSSC_put_BccRecipientsInfo(This,newVal)	\
    (This)->lpVtbl -> put_BccRecipientsInfo(This,newVal)

#define IVSSC_get_FromInfo(This,pVal)	\
    (This)->lpVtbl -> get_FromInfo(This,pVal)

#define IVSSC_put_FromInfo(This,newVal)	\
    (This)->lpVtbl -> put_FromInfo(This,newVal)

#define IVSSC_get_Subject(This,pVal)	\
    (This)->lpVtbl -> get_Subject(This,pVal)

#define IVSSC_put_Subject(This,newVal)	\
    (This)->lpVtbl -> put_Subject(This,newVal)

#define IVSSC_get_MsgType(This,pVal)	\
    (This)->lpVtbl -> get_MsgType(This,pVal)

#define IVSSC_put_MsgType(This,newVal)	\
    (This)->lpVtbl -> put_MsgType(This,newVal)

#define IVSSC_get_Body(This,pVal)	\
    (This)->lpVtbl -> get_Body(This,pVal)

#define IVSSC_put_Body(This,newVal)	\
    (This)->lpVtbl -> put_Body(This,newVal)

#define IVSSC_get_GetMsg(This,pVal)	\
    (This)->lpVtbl -> get_GetMsg(This,pVal)

#define IVSSC_get_Date(This,pVal)	\
    (This)->lpVtbl -> get_Date(This,pVal)

#define IVSSC_put_Date(This,newVal)	\
    (This)->lpVtbl -> put_Date(This,newVal)

#define IVSSC_get_CryptStatus(This,pVal)	\
    (This)->lpVtbl -> get_CryptStatus(This,pVal)

#define IVSSC_SelectAttachments(This)	\
    (This)->lpVtbl -> SelectAttachments(This)

#define IVSSC_get_SelectedAttachments(This,pVal)	\
    (This)->lpVtbl -> get_SelectedAttachments(This,pVal)

#define IVSSC_put_UnSelectAttachments(This,newVal)	\
    (This)->lpVtbl -> put_UnSelectAttachments(This,newVal)

#define IVSSC_get_AttachedFileList(This,pVal)	\
    (This)->lpVtbl -> get_AttachedFileList(This,pVal)

#define IVSSC_SaveAttachment(This,pFileName,pStatus)	\
    (This)->lpVtbl -> SaveAttachment(This,pFileName,pStatus)

#define IVSSC_put_MsgPostData(This,newVal)	\
    (This)->lpVtbl -> put_MsgPostData(This,newVal)

#define IVSSC_CertificateResolution(This,in_pvarEmailInfo)	\
    (This)->lpVtbl -> CertificateResolution(This,in_pvarEmailInfo)

#define IVSSC_SMIMECertificateResolution(This)	\
    (This)->lpVtbl -> SMIMECertificateResolution(This)

#define IVSSC_put_CertResolveURL(This,newVal)	\
    (This)->lpVtbl -> put_CertResolveURL(This,newVal)

#define IVSSC_get_IVSSCPTA(This,pVal)	\
    (This)->lpVtbl -> get_IVSSCPTA(This,pVal)

#define IVSSC_Decompose(This,i_pvarSMIMEMsg,i_pvarStatusType)	\
    (This)->lpVtbl -> Decompose(This,i_pvarSMIMEMsg,i_pvarStatusType)

#define IVSSC_put_ProxyRecipCert(This,newVal)	\
    (This)->lpVtbl -> put_ProxyRecipCert(This,newVal)

#define IVSSC_put_UseProxyRecipCert(This,newVal)	\
    (This)->lpVtbl -> put_UseProxyRecipCert(This,newVal)

#define IVSSC_Initialize(This,i_pMsgObjID,i_pMode)	\
    (This)->lpVtbl -> Initialize(This,i_pMsgObjID,i_pMode)

#define IVSSC_SetMode(This,i_pModeType)	\
    (This)->lpVtbl -> SetMode(This,i_pModeType)

#define IVSSC_get_MsgObjID(This,pVal)	\
    (This)->lpVtbl -> get_MsgObjID(This,pVal)

#define IVSSC_get_MsgBlobSize(This,pVal)	\
    (This)->lpVtbl -> get_MsgBlobSize(This,pVal)

#define IVSSC_InternetInitialize(This,in_pvarURL,in_pvarMethod,in_pvarPostData)	\
    (This)->lpVtbl -> InternetInitialize(This,in_pvarURL,in_pvarMethod,in_pvarPostData)

#define IVSSC_InternetSendRequest(This)	\
    (This)->lpVtbl -> InternetSendRequest(This)

#define IVSSC_put_UseInternetData(This,newVal)	\
    (This)->lpVtbl -> put_UseInternetData(This,newVal)

#define IVSSC_get_InternetDataSize(This,pVal)	\
    (This)->lpVtbl -> get_InternetDataSize(This,pVal)

#define IVSSC_get_InternetData(This,pVal)	\
    (This)->lpVtbl -> get_InternetData(This,pVal)

#define IVSSC_ChangeVarType(This,in_pvarByteArray,in_pvarType,o_pvarOutputType)	\
    (This)->lpVtbl -> ChangeVarType(This,in_pvarByteArray,in_pvarType,o_pvarOutputType)

#define IVSSC_SelectedAttachmentSize(This,in_pvarFileName,o_pvarFileSize)	\
    (This)->lpVtbl -> SelectedAttachmentSize(This,in_pvarFileName,o_pvarFileSize)

#define IVSSC_get_IVSSignerInfo(This,pVal)	\
    (This)->lpVtbl -> get_IVSSignerInfo(This,pVal)

#define IVSSC_get_IVSSCResolveInfo(This,pVal)	\
    (This)->lpVtbl -> get_IVSSCResolveInfo(This,pVal)

#define IVSSC_put_AddSignerCertificate(This,newVal)	\
    (This)->lpVtbl -> put_AddSignerCertificate(This,newVal)

#define IVSSC_put_AddRFC822Header(This,newVal)	\
    (This)->lpVtbl -> put_AddRFC822Header(This,newVal)

#define IVSSC_put_AddMIMEHeader(This,newVal)	\
    (This)->lpVtbl -> put_AddMIMEHeader(This,newVal)

#define IVSSC_put_OpaqueSign(This,newVal)	\
    (This)->lpVtbl -> put_OpaqueSign(This,newVal)

#define IVSSC_put_AddSenderRecipientInfo(This,newVal)	\
    (This)->lpVtbl -> put_AddSenderRecipientInfo(This,newVal)

#define IVSSC_get_SCType(This,pVal)	\
    (This)->lpVtbl -> get_SCType(This,pVal)

#define IVSSC_put_SCType(This,newVal)	\
    (This)->lpVtbl -> put_SCType(This,newVal)

#define IVSSC_get_CertificateTimeOut(This,pVal)	\
    (This)->lpVtbl -> get_CertificateTimeOut(This,pVal)

#define IVSSC_put_CertificateTimeOut(This,newVal)	\
    (This)->lpVtbl -> put_CertificateTimeOut(This,newVal)

#define IVSSC_get_MessageTimeOut(This,pVal)	\
    (This)->lpVtbl -> get_MessageTimeOut(This,pVal)

#define IVSSC_put_MessageTimeOut(This,newVal)	\
    (This)->lpVtbl -> put_MessageTimeOut(This,newVal)

#define IVSSC_ClearAll(This)	\
    (This)->lpVtbl -> ClearAll(This)

#define IVSSC_put_UsePKCS7Certificate(This,newVal)	\
    (This)->lpVtbl -> put_UsePKCS7Certificate(This,newVal)

#define IVSSC_put_AddSMIMECapabilities(This,newVal)	\
    (This)->lpVtbl -> put_AddSMIMECapabilities(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_Compose_Proxy( 
    IVSSC __RPC_FAR * This);


void __RPC_STUB IVSSC_Compose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_ToRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_ToRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_ToRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_ToRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_CcRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_CcRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_CcRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_CcRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_BccRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_BccRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_BccRecipientsInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_BccRecipientsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_FromInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_FromInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_FromInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_FromInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_Subject_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_Subject_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_Subject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_MsgType_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_MsgType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_MsgType_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_MsgType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_Body_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_Body_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_Body_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_Body_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_GetMsg_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_GetMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_Date_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_Date_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_Date_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_Date_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_CryptStatus_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_CryptStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_SelectAttachments_Proxy( 
    IVSSC __RPC_FAR * This);


void __RPC_STUB IVSSC_SelectAttachments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_SelectedAttachments_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_SelectedAttachments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_UnSelectAttachments_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_UnSelectAttachments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_AttachedFileList_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_AttachedFileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_SaveAttachment_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *pFileName,
    VARIANT __RPC_FAR *pStatus);


void __RPC_STUB IVSSC_SaveAttachment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_MsgPostData_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_MsgPostData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_CertificateResolution_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarEmailInfo);


void __RPC_STUB IVSSC_CertificateResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_SMIMECertificateResolution_Proxy( 
    IVSSC __RPC_FAR * This);


void __RPC_STUB IVSSC_SMIMECertificateResolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_CertResolveURL_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_CertResolveURL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_IVSSCPTA_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_IVSSCPTA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_Decompose_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT __RPC_FAR *i_pvarSMIMEMsg,
    /* [out][in] */ VARIANT __RPC_FAR *i_pvarStatusType);


void __RPC_STUB IVSSC_Decompose_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_ProxyRecipCert_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_ProxyRecipCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_UseProxyRecipCert_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_UseProxyRecipCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_Initialize_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pMsgObjID,
    VARIANT __RPC_FAR *i_pMode);


void __RPC_STUB IVSSC_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_SetMode_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pModeType);


void __RPC_STUB IVSSC_SetMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_MsgObjID_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_MsgObjID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_MsgBlobSize_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_MsgBlobSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_InternetInitialize_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarURL,
    VARIANT __RPC_FAR *in_pvarMethod,
    VARIANT __RPC_FAR *in_pvarPostData);


void __RPC_STUB IVSSC_InternetInitialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_InternetSendRequest_Proxy( 
    IVSSC __RPC_FAR * This);


void __RPC_STUB IVSSC_InternetSendRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_UseInternetData_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_UseInternetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_InternetDataSize_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_InternetDataSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_InternetData_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_InternetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_ChangeVarType_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarByteArray,
    VARIANT __RPC_FAR *in_pvarType,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarOutputType);


void __RPC_STUB IVSSC_ChangeVarType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_SelectedAttachmentSize_Proxy( 
    IVSSC __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarFileName,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileSize);


void __RPC_STUB IVSSC_SelectedAttachmentSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_IVSSignerInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_IVSSignerInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_IVSSCResolveInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_IVSSCResolveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_AddSignerCertificate_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_AddSignerCertificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_AddRFC822Header_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_AddRFC822Header_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_AddMIMEHeader_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_AddMIMEHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_OpaqueSign_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_OpaqueSign_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_AddSenderRecipientInfo_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_AddSenderRecipientInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_SCType_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_SCType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_SCType_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_SCType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_CertificateTimeOut_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_CertificateTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_CertificateTimeOut_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_CertificateTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSC_get_MessageTimeOut_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSC_get_MessageTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_MessageTimeOut_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_MessageTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSC_ClearAll_Proxy( 
    IVSSC __RPC_FAR * This);


void __RPC_STUB IVSSC_ClearAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_UsePKCS7Certificate_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_UsePKCS7Certificate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSC_put_AddSMIMECapabilities_Proxy( 
    IVSSC __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSC_put_AddSMIMECapabilities_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSSC_INTERFACE_DEFINED__ */


#ifndef __IResolveRcpt_INTERFACE_DEFINED__
#define __IResolveRcpt_INTERFACE_DEFINED__

/* interface IResolveRcpt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IResolveRcpt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("18865332-716F-11D5-A251-001083023D07")
    IResolveRcpt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EmailAddress( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Recipient_Count( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE First( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Next( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Issuer_DN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SerialNumber( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResolveRcptVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResolveRcpt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResolveRcpt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResolveRcpt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IResolveRcpt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IResolveRcpt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IResolveRcpt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IResolveRcpt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EmailAddress )( 
            IResolveRcpt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Recipient_Count )( 
            IResolveRcpt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *First )( 
            IResolveRcpt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IResolveRcpt __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            IResolveRcpt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Issuer_DN )( 
            IResolveRcpt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SerialNumber )( 
            IResolveRcpt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        END_INTERFACE
    } IResolveRcptVtbl;

    interface IResolveRcpt
    {
        CONST_VTBL struct IResolveRcptVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResolveRcpt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResolveRcpt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResolveRcpt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResolveRcpt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IResolveRcpt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IResolveRcpt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IResolveRcpt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IResolveRcpt_get_EmailAddress(This,pVal)	\
    (This)->lpVtbl -> get_EmailAddress(This,pVal)

#define IResolveRcpt_get_Recipient_Count(This,pVal)	\
    (This)->lpVtbl -> get_Recipient_Count(This,pVal)

#define IResolveRcpt_First(This)	\
    (This)->lpVtbl -> First(This)

#define IResolveRcpt_Next(This)	\
    (This)->lpVtbl -> Next(This)

#define IResolveRcpt_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#define IResolveRcpt_get_Issuer_DN(This,pVal)	\
    (This)->lpVtbl -> get_Issuer_DN(This,pVal)

#define IResolveRcpt_get_SerialNumber(This,pVal)	\
    (This)->lpVtbl -> get_SerialNumber(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_get_EmailAddress_Proxy( 
    IResolveRcpt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IResolveRcpt_get_EmailAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_get_Recipient_Count_Proxy( 
    IResolveRcpt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IResolveRcpt_get_Recipient_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_First_Proxy( 
    IResolveRcpt __RPC_FAR * This);


void __RPC_STUB IResolveRcpt_First_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_Next_Proxy( 
    IResolveRcpt __RPC_FAR * This);


void __RPC_STUB IResolveRcpt_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_get_Status_Proxy( 
    IResolveRcpt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IResolveRcpt_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_get_Issuer_DN_Proxy( 
    IResolveRcpt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IResolveRcpt_get_Issuer_DN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IResolveRcpt_get_SerialNumber_Proxy( 
    IResolveRcpt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IResolveRcpt_get_SerialNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResolveRcpt_INTERFACE_DEFINED__ */


#ifndef __IVSSignerInfo_INTERFACE_DEFINED__
#define __IVSSignerInfo_INTERFACE_DEFINED__

/* interface IVSSignerInfo */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSSignerInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8110D64-8608-11D5-A257-001083023D07")
    IVSSignerInfo : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubjectCN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubjectDN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IssuerDN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubjectSerialNumber( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubjectValidFrom( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SubjectValidTo( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSSignerInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSSignerInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSSignerInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubjectCN )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubjectDN )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IssuerDN )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubjectSerialNumber )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubjectValidFrom )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SubjectValidTo )( 
            IVSSignerInfo __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        END_INTERFACE
    } IVSSignerInfoVtbl;

    interface IVSSignerInfo
    {
        CONST_VTBL struct IVSSignerInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSSignerInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSSignerInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSSignerInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSSignerInfo_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSSignerInfo_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSSignerInfo_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSSignerInfo_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSSignerInfo_get_SubjectCN(This,pVal)	\
    (This)->lpVtbl -> get_SubjectCN(This,pVal)

#define IVSSignerInfo_get_SubjectDN(This,pVal)	\
    (This)->lpVtbl -> get_SubjectDN(This,pVal)

#define IVSSignerInfo_get_IssuerDN(This,pVal)	\
    (This)->lpVtbl -> get_IssuerDN(This,pVal)

#define IVSSignerInfo_get_SubjectSerialNumber(This,pVal)	\
    (This)->lpVtbl -> get_SubjectSerialNumber(This,pVal)

#define IVSSignerInfo_get_SubjectValidFrom(This,pVal)	\
    (This)->lpVtbl -> get_SubjectValidFrom(This,pVal)

#define IVSSignerInfo_get_SubjectValidTo(This,pVal)	\
    (This)->lpVtbl -> get_SubjectValidTo(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_SubjectCN_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_SubjectCN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_SubjectDN_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_SubjectDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_IssuerDN_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_IssuerDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_SubjectSerialNumber_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_SubjectSerialNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_SubjectValidFrom_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_SubjectValidFrom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSignerInfo_get_SubjectValidTo_Proxy( 
    IVSSignerInfo __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IVSSignerInfo_get_SubjectValidTo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSSignerInfo_INTERFACE_DEFINED__ */


#ifndef __IVSSCDllApi_INTERFACE_DEFINED__
#define __IVSSCDllApi_INTERFACE_DEFINED__

/* interface IVSSCDllApi */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSSCDllApi;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8110D67-8608-11D5-A257-001083023D07")
    IVSSCDllApi : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostFQDN( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HostFQDN( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HostProtocol( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HostProtocol( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAttachFileContent( 
            VARIANT __RPC_FAR *in_pvarFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileContent) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSSCDllApiVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSSCDllApi __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSSCDllApi __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostFQDN )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostFQDN )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_HostProtocol )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_HostProtocol )( 
            IVSSCDllApi __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAttachFileContent )( 
            IVSSCDllApi __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarFileName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileContent);
        
        END_INTERFACE
    } IVSSCDllApiVtbl;

    interface IVSSCDllApi
    {
        CONST_VTBL struct IVSSCDllApiVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSSCDllApi_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSSCDllApi_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSSCDllApi_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSSCDllApi_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSSCDllApi_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSSCDllApi_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSSCDllApi_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSSCDllApi_get_HostFQDN(This,pVal)	\
    (This)->lpVtbl -> get_HostFQDN(This,pVal)

#define IVSSCDllApi_put_HostFQDN(This,newVal)	\
    (This)->lpVtbl -> put_HostFQDN(This,newVal)

#define IVSSCDllApi_get_HostProtocol(This,pVal)	\
    (This)->lpVtbl -> get_HostProtocol(This,pVal)

#define IVSSCDllApi_put_HostProtocol(This,newVal)	\
    (This)->lpVtbl -> put_HostProtocol(This,newVal)

#define IVSSCDllApi_GetAttachFileContent(This,in_pvarFileName,o_pvarFileContent)	\
    (This)->lpVtbl -> GetAttachFileContent(This,in_pvarFileName,o_pvarFileContent)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSCDllApi_get_HostFQDN_Proxy( 
    IVSSCDllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSCDllApi_get_HostFQDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSCDllApi_put_HostFQDN_Proxy( 
    IVSSCDllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSCDllApi_put_HostFQDN_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSSCDllApi_get_HostProtocol_Proxy( 
    IVSSCDllApi __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSSCDllApi_get_HostProtocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSSCDllApi_put_HostProtocol_Proxy( 
    IVSSCDllApi __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSSCDllApi_put_HostProtocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSSCDllApi_GetAttachFileContent_Proxy( 
    IVSSCDllApi __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarFileName,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarFileContent);


void __RPC_STUB IVSSCDllApi_GetAttachFileContent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSSCDllApi_INTERFACE_DEFINED__ */



#ifndef __VSSCLib_LIBRARY_DEFINED__
#define __VSSCLib_LIBRARY_DEFINED__

/* library VSSCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_VSSCLib;

EXTERN_C const CLSID CLSID_VSSC;

#ifdef __cplusplus

class DECLSPEC_UUID("C5E8B9E2-D217-11D4-A21E-001083023D07")
VSSC;
#endif
#endif /* __VSSCLib_LIBRARY_DEFINED__ */

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


