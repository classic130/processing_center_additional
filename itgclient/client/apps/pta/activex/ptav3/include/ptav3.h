/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 02 10:36:21 2003
 */
/* Compiler settings for F:\sasi_063003\itgclient\client\apps\pta\activex\ptav3\source\Ptav3.idl:
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

#ifndef __ptav3_h__
#define __ptav3_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSPTA_FWD_DEFINED__
#define __IVSPTA_FWD_DEFINED__
typedef interface IVSPTA IVSPTA;
#endif 	/* __IVSPTA_FWD_DEFINED__ */


#ifndef __IVSRootsUpdate_FWD_DEFINED__
#define __IVSRootsUpdate_FWD_DEFINED__
typedef interface IVSRootsUpdate IVSRootsUpdate;
#endif 	/* __IVSRootsUpdate_FWD_DEFINED__ */


#ifndef __VSPTA_FWD_DEFINED__
#define __VSPTA_FWD_DEFINED__

#ifdef __cplusplus
typedef class VSPTA VSPTA;
#else
typedef struct VSPTA VSPTA;
#endif /* __cplusplus */

#endif 	/* __VSPTA_FWD_DEFINED__ */


#ifndef __VSROOTS_FWD_DEFINED__
#define __VSROOTS_FWD_DEFINED__

#ifdef __cplusplus
typedef class VSROOTS VSROOTS;
#else
typedef struct VSROOTS VSROOTS;
#endif /* __cplusplus */

#endif 	/* __VSROOTS_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "certprefs.h"
#include "profmgmt.h"
#include "seldigid.h"
#include "srchcrit.h"
#include "uiprefs.h"
#include "roamprefs.h"
#include "ptadllapi.h"
#include "import.h"
#include "export.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_Ptav3_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_Ptav3_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Ptav3_0000_v0_0_s_ifspec;

#ifndef __IVSPTA_INTERFACE_DEFINED__
#define __IVSPTA_INTERFACE_DEFINED__

/* interface IVSPTA */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSPTA;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6F7864F8-DB33-11D3-8166-0060B0F885E6")
    IVSPTA : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            VARIANT __RPC_FAR *in_pvarAppCtxtName,
            VARIANT __RPC_FAR *in_pvarUseCapi) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppPref_SetPreference( 
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AppPref_GetPreference( 
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSUIPrefs( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSProfMgmt( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSCertPrefs( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSSrchCrit( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSSelectedDigID( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSRoamPrefs( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CSPName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CSPName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateCertReq( 
            VARIANT __RPC_FAR *i_pvarSubjectDN,
            VARIANT __RPC_FAR *i_pvarKeyGenFlag,
            VARIANT __RPC_FAR *i_pvarHashAlg,
            VARIANT __RPC_FAR *i_pvarAttributes,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarB64EncPKCS10) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InstallCert( 
            VARIANT __RPC_FAR *in_pvarCert) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignChallenge( 
            VARIANT __RPC_FAR *in_pvarChallenge,
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignTransaction( 
            VARIANT __RPC_FAR *in_pvarMessage,
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelIDForTrans( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelIDForChallenge( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProtocolName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProtocolName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SignRenewal( 
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InstallKeyPair( 
            VARIANT __RPC_FAR *i_pvarPrivKeyBlob,
            VARIANT __RPC_FAR *i_pvarPKCS7Cert) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UseDefCertFlag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UseDefCertFlag( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AuthDll( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AuthDll( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileIssFrndlyName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileIssFrndlyName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileIssUniqueId( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileIssUniqueId( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSP12Import( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DecryptSessionKey( 
            /* [in] */ VARIANT i_varEncryptedSessionKey,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarDecryptedSessionKey) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInformationBlob( 
            /* [in] */ VARIANT i_varName,
            /* [in] */ VARIANT i_varValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInformationBlob( 
            /* [in] */ VARIANT i_varName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DeleteInformationBlob( 
            /* [in] */ VARIANT i_varName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IVSP12Export( 
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AffLogoUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AffLogoUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ApplicationCreatorWildCard( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ApplicationReadOKDomains( 
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationReadOKDomains) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ApplicationReadOKDomains( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ApplicationWriteOKDomains( 
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationWriteOKDomains) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ApplicationWriteOKDomains( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AmITheApplicationCreator( 
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarIsCreator) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignDate( 
            /* [retval][out] */ DATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignDate( 
            /* [in] */ DATE newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableCertForCapi( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreatePassword( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnterPassword( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsTPMAvailable( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UTF8EncodeMessage( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UTF8EncodeMessage( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSPTAVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSPTA __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSPTA __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSPTA __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarAppCtxtName,
            VARIANT __RPC_FAR *in_pvarUseCapi);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppPref_SetPreference )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AppPref_GetPreference )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarPrefName,
            VARIANT __RPC_FAR *in_pvarPrefValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSUIPrefs )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSProfMgmt )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSCertPrefs )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSSrchCrit )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSSelectedDigID )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSRoamPrefs )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CSPName )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CSPName )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateCertReq )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarSubjectDN,
            VARIANT __RPC_FAR *i_pvarKeyGenFlag,
            VARIANT __RPC_FAR *i_pvarHashAlg,
            VARIANT __RPC_FAR *i_pvarAttributes,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarB64EncPKCS10);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstallCert )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarCert);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SignChallenge )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarChallenge,
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SignTransaction )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarMessage,
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IVSPTA __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelIDForTrans )( 
            IVSPTA __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelIDForChallenge )( 
            IVSPTA __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProtocolName )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProtocolName )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SignRenewal )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *in_pvarAlgID,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InstallKeyPair )( 
            IVSPTA __RPC_FAR * This,
            VARIANT __RPC_FAR *i_pvarPrivKeyBlob,
            VARIANT __RPC_FAR *i_pvarPKCS7Cert);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UseDefCertFlag )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UseDefCertFlag )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AuthDll )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AuthDll )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileIssFrndlyName )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileIssFrndlyName )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileIssUniqueId )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileIssUniqueId )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSP12Import )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DecryptSessionKey )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT i_varEncryptedSessionKey,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarDecryptedSessionKey);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInformationBlob )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT i_varName,
            /* [in] */ VARIANT i_varValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInformationBlob )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT i_varName,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DeleteInformationBlob )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT i_varName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IVSP12Export )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AffLogoUrl )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AffLogoUrl )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ApplicationCreatorWildCard )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ApplicationReadOKDomains )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationReadOKDomains);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ApplicationReadOKDomains )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ApplicationWriteOKDomains )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationWriteOKDomains);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ApplicationWriteOKDomains )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AmITheApplicationCreator )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *o_pvarIsCreator);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SignDate )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ DATE __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignDate )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ DATE newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableCertForCapi )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreatePassword )( 
            IVSPTA __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnterPassword )( 
            IVSPTA __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsTPMAvailable )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UTF8EncodeMessage )( 
            IVSPTA __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UTF8EncodeMessage )( 
            IVSPTA __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IVSPTAVtbl;

    interface IVSPTA
    {
        CONST_VTBL struct IVSPTAVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSPTA_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSPTA_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSPTA_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSPTA_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSPTA_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSPTA_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSPTA_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSPTA_Initialize(This,in_pvarAppCtxtName,in_pvarUseCapi)	\
    (This)->lpVtbl -> Initialize(This,in_pvarAppCtxtName,in_pvarUseCapi)

#define IVSPTA_AppPref_SetPreference(This,in_pvarPrefName,in_pvarPrefVal)	\
    (This)->lpVtbl -> AppPref_SetPreference(This,in_pvarPrefName,in_pvarPrefVal)

#define IVSPTA_AppPref_GetPreference(This,in_pvarPrefName,in_pvarPrefValue)	\
    (This)->lpVtbl -> AppPref_GetPreference(This,in_pvarPrefName,in_pvarPrefValue)

#define IVSPTA_get_IVSUIPrefs(This,pVal)	\
    (This)->lpVtbl -> get_IVSUIPrefs(This,pVal)

#define IVSPTA_get_IVSProfMgmt(This,pVal)	\
    (This)->lpVtbl -> get_IVSProfMgmt(This,pVal)

#define IVSPTA_get_IVSCertPrefs(This,pVal)	\
    (This)->lpVtbl -> get_IVSCertPrefs(This,pVal)

#define IVSPTA_get_IVSSrchCrit(This,pVal)	\
    (This)->lpVtbl -> get_IVSSrchCrit(This,pVal)

#define IVSPTA_get_IVSSelectedDigID(This,pVal)	\
    (This)->lpVtbl -> get_IVSSelectedDigID(This,pVal)

#define IVSPTA_get_IVSRoamPrefs(This,pVal)	\
    (This)->lpVtbl -> get_IVSRoamPrefs(This,pVal)

#define IVSPTA_get_CSPName(This,pVal)	\
    (This)->lpVtbl -> get_CSPName(This,pVal)

#define IVSPTA_put_CSPName(This,newVal)	\
    (This)->lpVtbl -> put_CSPName(This,newVal)

#define IVSPTA_CreateCertReq(This,i_pvarSubjectDN,i_pvarKeyGenFlag,i_pvarHashAlg,i_pvarAttributes,o_pvarB64EncPKCS10)	\
    (This)->lpVtbl -> CreateCertReq(This,i_pvarSubjectDN,i_pvarKeyGenFlag,i_pvarHashAlg,i_pvarAttributes,o_pvarB64EncPKCS10)

#define IVSPTA_InstallCert(This,in_pvarCert)	\
    (This)->lpVtbl -> InstallCert(This,in_pvarCert)

#define IVSPTA_SignChallenge(This,in_pvarChallenge,in_pvarAlgID,o_pvarSignature)	\
    (This)->lpVtbl -> SignChallenge(This,in_pvarChallenge,in_pvarAlgID,o_pvarSignature)

#define IVSPTA_SignTransaction(This,in_pvarMessage,in_pvarAlgID,o_pvarSignature)	\
    (This)->lpVtbl -> SignTransaction(This,in_pvarMessage,in_pvarAlgID,o_pvarSignature)

#define IVSPTA_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IVSPTA_SelIDForTrans(This)	\
    (This)->lpVtbl -> SelIDForTrans(This)

#define IVSPTA_SelIDForChallenge(This)	\
    (This)->lpVtbl -> SelIDForChallenge(This)

#define IVSPTA_get_ProtocolName(This,pVal)	\
    (This)->lpVtbl -> get_ProtocolName(This,pVal)

#define IVSPTA_put_ProtocolName(This,newVal)	\
    (This)->lpVtbl -> put_ProtocolName(This,newVal)

#define IVSPTA_SignRenewal(This,in_pvarAlgID,o_pvarSignature)	\
    (This)->lpVtbl -> SignRenewal(This,in_pvarAlgID,o_pvarSignature)

#define IVSPTA_InstallKeyPair(This,i_pvarPrivKeyBlob,i_pvarPKCS7Cert)	\
    (This)->lpVtbl -> InstallKeyPair(This,i_pvarPrivKeyBlob,i_pvarPKCS7Cert)

#define IVSPTA_get_UseDefCertFlag(This,pVal)	\
    (This)->lpVtbl -> get_UseDefCertFlag(This,pVal)

#define IVSPTA_put_UseDefCertFlag(This,newVal)	\
    (This)->lpVtbl -> put_UseDefCertFlag(This,newVal)

#define IVSPTA_get_AuthDll(This,pVal)	\
    (This)->lpVtbl -> get_AuthDll(This,pVal)

#define IVSPTA_put_AuthDll(This,newVal)	\
    (This)->lpVtbl -> put_AuthDll(This,newVal)

#define IVSPTA_get_ProfileIssFrndlyName(This,pVal)	\
    (This)->lpVtbl -> get_ProfileIssFrndlyName(This,pVal)

#define IVSPTA_put_ProfileIssFrndlyName(This,newVal)	\
    (This)->lpVtbl -> put_ProfileIssFrndlyName(This,newVal)

#define IVSPTA_get_ProfileIssUniqueId(This,pVal)	\
    (This)->lpVtbl -> get_ProfileIssUniqueId(This,pVal)

#define IVSPTA_put_ProfileIssUniqueId(This,newVal)	\
    (This)->lpVtbl -> put_ProfileIssUniqueId(This,newVal)

#define IVSPTA_get_IVSP12Import(This,pVal)	\
    (This)->lpVtbl -> get_IVSP12Import(This,pVal)

#define IVSPTA_DecryptSessionKey(This,i_varEncryptedSessionKey,o_pvarDecryptedSessionKey)	\
    (This)->lpVtbl -> DecryptSessionKey(This,i_varEncryptedSessionKey,o_pvarDecryptedSessionKey)

#define IVSPTA_SetInformationBlob(This,i_varName,i_varValue)	\
    (This)->lpVtbl -> SetInformationBlob(This,i_varName,i_varValue)

#define IVSPTA_GetInformationBlob(This,i_varName,o_pvarValue)	\
    (This)->lpVtbl -> GetInformationBlob(This,i_varName,o_pvarValue)

#define IVSPTA_DeleteInformationBlob(This,i_varName)	\
    (This)->lpVtbl -> DeleteInformationBlob(This,i_varName)

#define IVSPTA_get_IVSP12Export(This,pVal)	\
    (This)->lpVtbl -> get_IVSP12Export(This,pVal)

#define IVSPTA_get_AffLogoUrl(This,pVal)	\
    (This)->lpVtbl -> get_AffLogoUrl(This,pVal)

#define IVSPTA_put_AffLogoUrl(This,newVal)	\
    (This)->lpVtbl -> put_AffLogoUrl(This,newVal)

#define IVSPTA_put_ApplicationCreatorWildCard(This,newVal)	\
    (This)->lpVtbl -> put_ApplicationCreatorWildCard(This,newVal)

#define IVSPTA_get_ApplicationReadOKDomains(This,o_pvarApplicationReadOKDomains)	\
    (This)->lpVtbl -> get_ApplicationReadOKDomains(This,o_pvarApplicationReadOKDomains)

#define IVSPTA_put_ApplicationReadOKDomains(This,newVal)	\
    (This)->lpVtbl -> put_ApplicationReadOKDomains(This,newVal)

#define IVSPTA_get_ApplicationWriteOKDomains(This,o_pvarApplicationWriteOKDomains)	\
    (This)->lpVtbl -> get_ApplicationWriteOKDomains(This,o_pvarApplicationWriteOKDomains)

#define IVSPTA_put_ApplicationWriteOKDomains(This,newVal)	\
    (This)->lpVtbl -> put_ApplicationWriteOKDomains(This,newVal)

#define IVSPTA_get_AmITheApplicationCreator(This,o_pvarIsCreator)	\
    (This)->lpVtbl -> get_AmITheApplicationCreator(This,o_pvarIsCreator)

#define IVSPTA_get_SignDate(This,pVal)	\
    (This)->lpVtbl -> get_SignDate(This,pVal)

#define IVSPTA_put_SignDate(This,newVal)	\
    (This)->lpVtbl -> put_SignDate(This,newVal)

#define IVSPTA_put_EnableCertForCapi(This,newVal)	\
    (This)->lpVtbl -> put_EnableCertForCapi(This,newVal)

#define IVSPTA_CreatePassword(This)	\
    (This)->lpVtbl -> CreatePassword(This)

#define IVSPTA_EnterPassword(This)	\
    (This)->lpVtbl -> EnterPassword(This)

#define IVSPTA_get_IsTPMAvailable(This,pVal)	\
    (This)->lpVtbl -> get_IsTPMAvailable(This,pVal)

#define IVSPTA_get_UTF8EncodeMessage(This,pVal)	\
    (This)->lpVtbl -> get_UTF8EncodeMessage(This,pVal)

#define IVSPTA_put_UTF8EncodeMessage(This,newVal)	\
    (This)->lpVtbl -> put_UTF8EncodeMessage(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_Initialize_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarAppCtxtName,
    VARIANT __RPC_FAR *in_pvarUseCapi);


void __RPC_STUB IVSPTA_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_AppPref_SetPreference_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPrefName,
    VARIANT __RPC_FAR *in_pvarPrefVal);


void __RPC_STUB IVSPTA_AppPref_SetPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_AppPref_GetPreference_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarPrefName,
    VARIANT __RPC_FAR *in_pvarPrefValue);


void __RPC_STUB IVSPTA_AppPref_GetPreference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSUIPrefs_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSUIPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSProfMgmt_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSProfMgmt_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSCertPrefs_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSCertPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSSrchCrit_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSSrchCrit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSSelectedDigID_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSSelectedDigID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSRoamPrefs_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSRoamPrefs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_CSPName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_CSPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_CSPName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_CSPName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_CreateCertReq_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarSubjectDN,
    VARIANT __RPC_FAR *i_pvarKeyGenFlag,
    VARIANT __RPC_FAR *i_pvarHashAlg,
    VARIANT __RPC_FAR *i_pvarAttributes,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarB64EncPKCS10);


void __RPC_STUB IVSPTA_CreateCertReq_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_InstallCert_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarCert);


void __RPC_STUB IVSPTA_InstallCert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SignChallenge_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarChallenge,
    VARIANT __RPC_FAR *in_pvarAlgID,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);


void __RPC_STUB IVSPTA_SignChallenge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SignTransaction_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarMessage,
    VARIANT __RPC_FAR *in_pvarAlgID,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);


void __RPC_STUB IVSPTA_SignTransaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_Close_Proxy( 
    IVSPTA __RPC_FAR * This);


void __RPC_STUB IVSPTA_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SelIDForTrans_Proxy( 
    IVSPTA __RPC_FAR * This);


void __RPC_STUB IVSPTA_SelIDForTrans_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SelIDForChallenge_Proxy( 
    IVSPTA __RPC_FAR * This);


void __RPC_STUB IVSPTA_SelIDForChallenge_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_ProtocolName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_ProtocolName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ProtocolName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ProtocolName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SignRenewal_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *in_pvarAlgID,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarSignature);


void __RPC_STUB IVSPTA_SignRenewal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_InstallKeyPair_Proxy( 
    IVSPTA __RPC_FAR * This,
    VARIANT __RPC_FAR *i_pvarPrivKeyBlob,
    VARIANT __RPC_FAR *i_pvarPKCS7Cert);


void __RPC_STUB IVSPTA_InstallKeyPair_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_UseDefCertFlag_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_UseDefCertFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_UseDefCertFlag_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_UseDefCertFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_AuthDll_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_AuthDll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_AuthDll_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_AuthDll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_ProfileIssFrndlyName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_ProfileIssFrndlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ProfileIssFrndlyName_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ProfileIssFrndlyName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_ProfileIssUniqueId_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_ProfileIssUniqueId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ProfileIssUniqueId_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ProfileIssUniqueId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSP12Import_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSP12Import_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_DecryptSessionKey_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT i_varEncryptedSessionKey,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarDecryptedSessionKey);


void __RPC_STUB IVSPTA_DecryptSessionKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_SetInformationBlob_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT i_varName,
    /* [in] */ VARIANT i_varValue);


void __RPC_STUB IVSPTA_SetInformationBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_GetInformationBlob_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT i_varName,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarValue);


void __RPC_STUB IVSPTA_GetInformationBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_DeleteInformationBlob_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT i_varName);


void __RPC_STUB IVSPTA_DeleteInformationBlob_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IVSP12Export_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ IDispatch __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IVSP12Export_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_AffLogoUrl_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_AffLogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_AffLogoUrl_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_AffLogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ApplicationCreatorWildCard_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ApplicationCreatorWildCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_ApplicationReadOKDomains_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationReadOKDomains);


void __RPC_STUB IVSPTA_get_ApplicationReadOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ApplicationReadOKDomains_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ApplicationReadOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_ApplicationWriteOKDomains_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarApplicationWriteOKDomains);


void __RPC_STUB IVSPTA_get_ApplicationWriteOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_ApplicationWriteOKDomains_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_ApplicationWriteOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_AmITheApplicationCreator_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *o_pvarIsCreator);


void __RPC_STUB IVSPTA_get_AmITheApplicationCreator_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_SignDate_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ DATE __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_SignDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_SignDate_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ DATE newVal);


void __RPC_STUB IVSPTA_put_SignDate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_EnableCertForCapi_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_EnableCertForCapi_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_CreatePassword_Proxy( 
    IVSPTA __RPC_FAR * This);


void __RPC_STUB IVSPTA_CreatePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSPTA_EnterPassword_Proxy( 
    IVSPTA __RPC_FAR * This);


void __RPC_STUB IVSPTA_EnterPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_IsTPMAvailable_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_IsTPMAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSPTA_get_UTF8EncodeMessage_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSPTA_get_UTF8EncodeMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSPTA_put_UTF8EncodeMessage_Proxy( 
    IVSPTA __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSPTA_put_UTF8EncodeMessage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSPTA_INTERFACE_DEFINED__ */


#ifndef __IVSRootsUpdate_INTERFACE_DEFINED__
#define __IVSRootsUpdate_INTERFACE_DEFINED__

/* interface IVSRootsUpdate */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSRootsUpdate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("50E71FEA-2234-11d4-8D73-0060B0FC0637")
    IVSRootsUpdate : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateStandardTrustProfile( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateVerisignTrustProfile( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSRootsUpdateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSRootsUpdate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSRootsUpdate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSRootsUpdate __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSRootsUpdate __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSRootsUpdate __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSRootsUpdate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSRootsUpdate __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IVSRootsUpdate __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateStandardTrustProfile )( 
            IVSRootsUpdate __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateVerisignTrustProfile )( 
            IVSRootsUpdate __RPC_FAR * This);
        
        END_INTERFACE
    } IVSRootsUpdateVtbl;

    interface IVSRootsUpdate
    {
        CONST_VTBL struct IVSRootsUpdateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSRootsUpdate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSRootsUpdate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSRootsUpdate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSRootsUpdate_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSRootsUpdate_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSRootsUpdate_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSRootsUpdate_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSRootsUpdate_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IVSRootsUpdate_CreateStandardTrustProfile(This)	\
    (This)->lpVtbl -> CreateStandardTrustProfile(This)

#define IVSRootsUpdate_CreateVerisignTrustProfile(This)	\
    (This)->lpVtbl -> CreateVerisignTrustProfile(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSRootsUpdate_Initialize_Proxy( 
    IVSRootsUpdate __RPC_FAR * This);


void __RPC_STUB IVSRootsUpdate_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSRootsUpdate_CreateStandardTrustProfile_Proxy( 
    IVSRootsUpdate __RPC_FAR * This);


void __RPC_STUB IVSRootsUpdate_CreateStandardTrustProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSRootsUpdate_CreateVerisignTrustProfile_Proxy( 
    IVSRootsUpdate __RPC_FAR * This);


void __RPC_STUB IVSRootsUpdate_CreateVerisignTrustProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSRootsUpdate_INTERFACE_DEFINED__ */



#ifndef __PTAV3Lib_LIBRARY_DEFINED__
#define __PTAV3Lib_LIBRARY_DEFINED__

/* library PTAV3Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PTAV3Lib;

EXTERN_C const CLSID CLSID_VSPTA;

#ifdef __cplusplus

class DECLSPEC_UUID("6F7864F9-DB33-11D3-8166-0060B0F885E6")
VSPTA;
#endif

EXTERN_C const CLSID CLSID_VSROOTS;

#ifdef __cplusplus

class DECLSPEC_UUID("50E71FEB-2234-11d4-8D73-0060B0FC0637")
VSROOTS;
#endif
#endif /* __PTAV3Lib_LIBRARY_DEFINED__ */

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
