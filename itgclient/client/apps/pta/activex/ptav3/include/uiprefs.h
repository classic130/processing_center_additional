/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jun 23 16:33:08 2003
 */
/* Compiler settings for F:\sasi_062003\itgclient\client\apps\pta\activex\ptav3\Source\uiprefs.idl:
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

#ifndef __uiprefs_h__
#define __uiprefs_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSUIPrefs_FWD_DEFINED__
#define __IVSUIPrefs_FWD_DEFINED__
typedef interface IVSUIPrefs IVSUIPrefs;
#endif 	/* __IVSUIPrefs_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_uiprefs_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_uiprefs_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_uiprefs_0000_v0_0_s_ifspec;

#ifndef __IVSUIPrefs_INTERFACE_DEFINED__
#define __IVSUIPrefs_INTERFACE_DEFINED__

/* interface IVSUIPrefs */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSUIPrefs;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d962f4c0-ddb0-11d3-a428-d1a369ca484f")
    IVSUIPrefs : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Language( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Language( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TitleFont( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TitleFont( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TextFont( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TextFont( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_BtnFont( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_BtnFont( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UILogoUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UILogoUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NewPasswd_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NewPasswd_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NewPasswd_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NewPasswd_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NewPasswd_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NewPasswd_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NewPasswd_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NewPasswd_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NewPasswd_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NewPasswd_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LgnDlg_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LgnDlg_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProf_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProf_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProf_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProf_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProf_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProf_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProf_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProf_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProf_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProf_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_ShowDefChkBox( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_ShowDefChkBox( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_ChkBoxText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_ChkBoxText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SelID_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SelID_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SgnDlg_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SgnDlg_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RvwMsg_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RvwMsg_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RvwMsg_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RvwMsg_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RvwMsg_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RvwMsg_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RvwMsg_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RvwMsg_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RvwMsg_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RvwMsg_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntroDlg_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IntroDlg_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntroDlg_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IntroDlg_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IntroDlg_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IntroDlg_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateNewProf_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateNewProf_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangePasswd_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangePasswd_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangePasswd_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangePasswd_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangePasswd_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangePasswd_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangePasswd_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangePasswd_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ChangePasswd_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ChangePasswd_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout_HelpUrl( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout_HelpUrl( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_EnableTopMostWindow( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignTransDlgWidth( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignTransDlgWidth( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SignTransDlgHeight( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SignTransDlgHeight( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetSecretQuestion_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetSecretQuestion_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetSecretQuestion_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetSecretQuestion_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetSecretQuestion_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetSecretQuestion_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GetSecretQuestion_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_GetSecretQuestion_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResetPasswd_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ResetPasswd_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResetPasswd_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ResetPasswd_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResetPasswd_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ResetPasswd_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ResetPasswd_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ResetPasswd_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateSecret_Title( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateSecret_Title( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateSecret_Text( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateSecret_Text( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateSecret_OKBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateSecret_OKBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CreateSecret_CancelBtnText( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CreateSecret_CancelBtnText( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSUIPrefsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSUIPrefs __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSUIPrefs __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Language )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Language )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TitleFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TitleFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TextFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TextFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BtnFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BtnFont )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UILogoUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UILogoUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewPasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NewPasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewPasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NewPasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewPasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NewPasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewPasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NewPasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NewPasswd_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NewPasswd_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LgnDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LgnDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProf_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProf_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProf_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProf_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProf_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProf_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProf_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProf_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProf_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProf_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_ShowDefChkBox )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_ShowDefChkBox )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_ChkBoxText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_ChkBoxText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SelID_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SelID_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SgnDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SgnDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RvwMsg_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RvwMsg_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RvwMsg_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RvwMsg_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RvwMsg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RvwMsg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RvwMsg_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RvwMsg_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RvwMsg_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RvwMsg_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IntroDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IntroDlg_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IntroDlg_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IntroDlg_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IntroDlg_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IntroDlg_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateNewProf_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CreateNewProf_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangePasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChangePasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangePasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChangePasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangePasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChangePasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangePasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChangePasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ChangePasswd_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ChangePasswd_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Timeout_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Timeout_HelpUrl )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_EnableTopMostWindow )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SignTransDlgWidth )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignTransDlgWidth )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SignTransDlgHeight )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SignTransDlgHeight )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetSecretQuestion_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetSecretQuestion_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetSecretQuestion_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetSecretQuestion_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetSecretQuestion_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetSecretQuestion_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GetSecretQuestion_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_GetSecretQuestion_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResetPasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ResetPasswd_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResetPasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ResetPasswd_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResetPasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ResetPasswd_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ResetPasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ResetPasswd_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateSecret_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CreateSecret_Title )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateSecret_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CreateSecret_Text )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateSecret_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CreateSecret_OKBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_CreateSecret_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_CreateSecret_CancelBtnText )( 
            IVSUIPrefs __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IVSUIPrefsVtbl;

    interface IVSUIPrefs
    {
        CONST_VTBL struct IVSUIPrefsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSUIPrefs_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSUIPrefs_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSUIPrefs_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSUIPrefs_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSUIPrefs_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSUIPrefs_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSUIPrefs_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSUIPrefs_get_Language(This,pVal)	\
    (This)->lpVtbl -> get_Language(This,pVal)

#define IVSUIPrefs_put_Language(This,newVal)	\
    (This)->lpVtbl -> put_Language(This,newVal)

#define IVSUIPrefs_get_TitleFont(This,pVal)	\
    (This)->lpVtbl -> get_TitleFont(This,pVal)

#define IVSUIPrefs_put_TitleFont(This,newVal)	\
    (This)->lpVtbl -> put_TitleFont(This,newVal)

#define IVSUIPrefs_get_TextFont(This,pVal)	\
    (This)->lpVtbl -> get_TextFont(This,pVal)

#define IVSUIPrefs_put_TextFont(This,newVal)	\
    (This)->lpVtbl -> put_TextFont(This,newVal)

#define IVSUIPrefs_get_BtnFont(This,pVal)	\
    (This)->lpVtbl -> get_BtnFont(This,pVal)

#define IVSUIPrefs_put_BtnFont(This,newVal)	\
    (This)->lpVtbl -> put_BtnFont(This,newVal)

#define IVSUIPrefs_get_UILogoUrl(This,pVal)	\
    (This)->lpVtbl -> get_UILogoUrl(This,pVal)

#define IVSUIPrefs_put_UILogoUrl(This,newVal)	\
    (This)->lpVtbl -> put_UILogoUrl(This,newVal)

#define IVSUIPrefs_get_NewPasswd_Title(This,pVal)	\
    (This)->lpVtbl -> get_NewPasswd_Title(This,pVal)

#define IVSUIPrefs_put_NewPasswd_Title(This,newVal)	\
    (This)->lpVtbl -> put_NewPasswd_Title(This,newVal)

#define IVSUIPrefs_get_NewPasswd_Text(This,pVal)	\
    (This)->lpVtbl -> get_NewPasswd_Text(This,pVal)

#define IVSUIPrefs_put_NewPasswd_Text(This,newVal)	\
    (This)->lpVtbl -> put_NewPasswd_Text(This,newVal)

#define IVSUIPrefs_get_NewPasswd_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_NewPasswd_OKBtnText(This,pVal)

#define IVSUIPrefs_put_NewPasswd_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_NewPasswd_OKBtnText(This,newVal)

#define IVSUIPrefs_get_NewPasswd_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_NewPasswd_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_NewPasswd_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_NewPasswd_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_NewPasswd_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_NewPasswd_HelpUrl(This,pVal)

#define IVSUIPrefs_put_NewPasswd_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_NewPasswd_HelpUrl(This,newVal)

#define IVSUIPrefs_get_LgnDlg_Title(This,pVal)	\
    (This)->lpVtbl -> get_LgnDlg_Title(This,pVal)

#define IVSUIPrefs_put_LgnDlg_Title(This,newVal)	\
    (This)->lpVtbl -> put_LgnDlg_Title(This,newVal)

#define IVSUIPrefs_get_OpenProf_Title(This,pVal)	\
    (This)->lpVtbl -> get_OpenProf_Title(This,pVal)

#define IVSUIPrefs_put_OpenProf_Title(This,newVal)	\
    (This)->lpVtbl -> put_OpenProf_Title(This,newVal)

#define IVSUIPrefs_get_OpenProf_Text(This,pVal)	\
    (This)->lpVtbl -> get_OpenProf_Text(This,pVal)

#define IVSUIPrefs_put_OpenProf_Text(This,newVal)	\
    (This)->lpVtbl -> put_OpenProf_Text(This,newVal)

#define IVSUIPrefs_get_OpenProf_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_OpenProf_OKBtnText(This,pVal)

#define IVSUIPrefs_put_OpenProf_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_OpenProf_OKBtnText(This,newVal)

#define IVSUIPrefs_get_OpenProf_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_OpenProf_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_OpenProf_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_OpenProf_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_OpenProf_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_OpenProf_HelpUrl(This,pVal)

#define IVSUIPrefs_put_OpenProf_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_OpenProf_HelpUrl(This,newVal)

#define IVSUIPrefs_get_SelID_Title(This,pVal)	\
    (This)->lpVtbl -> get_SelID_Title(This,pVal)

#define IVSUIPrefs_put_SelID_Title(This,newVal)	\
    (This)->lpVtbl -> put_SelID_Title(This,newVal)

#define IVSUIPrefs_get_SelID_Text(This,pVal)	\
    (This)->lpVtbl -> get_SelID_Text(This,pVal)

#define IVSUIPrefs_put_SelID_Text(This,newVal)	\
    (This)->lpVtbl -> put_SelID_Text(This,newVal)

#define IVSUIPrefs_get_SelID_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_SelID_OKBtnText(This,pVal)

#define IVSUIPrefs_put_SelID_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_SelID_OKBtnText(This,newVal)

#define IVSUIPrefs_get_SelID_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_SelID_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_SelID_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_SelID_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_SelID_ShowDefChkBox(This,pVal)	\
    (This)->lpVtbl -> get_SelID_ShowDefChkBox(This,pVal)

#define IVSUIPrefs_put_SelID_ShowDefChkBox(This,newVal)	\
    (This)->lpVtbl -> put_SelID_ShowDefChkBox(This,newVal)

#define IVSUIPrefs_get_SelID_ChkBoxText(This,pVal)	\
    (This)->lpVtbl -> get_SelID_ChkBoxText(This,pVal)

#define IVSUIPrefs_put_SelID_ChkBoxText(This,newVal)	\
    (This)->lpVtbl -> put_SelID_ChkBoxText(This,newVal)

#define IVSUIPrefs_get_SelID_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_SelID_HelpUrl(This,pVal)

#define IVSUIPrefs_put_SelID_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_SelID_HelpUrl(This,newVal)

#define IVSUIPrefs_get_SgnDlg_Title(This,pVal)	\
    (This)->lpVtbl -> get_SgnDlg_Title(This,pVal)

#define IVSUIPrefs_put_SgnDlg_Title(This,newVal)	\
    (This)->lpVtbl -> put_SgnDlg_Title(This,newVal)

#define IVSUIPrefs_get_RvwMsg_Text(This,pVal)	\
    (This)->lpVtbl -> get_RvwMsg_Text(This,pVal)

#define IVSUIPrefs_put_RvwMsg_Text(This,newVal)	\
    (This)->lpVtbl -> put_RvwMsg_Text(This,newVal)

#define IVSUIPrefs_get_RvwMsg_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_RvwMsg_OKBtnText(This,pVal)

#define IVSUIPrefs_put_RvwMsg_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_RvwMsg_OKBtnText(This,newVal)

#define IVSUIPrefs_get_RvwMsg_Title(This,pVal)	\
    (This)->lpVtbl -> get_RvwMsg_Title(This,pVal)

#define IVSUIPrefs_put_RvwMsg_Title(This,newVal)	\
    (This)->lpVtbl -> put_RvwMsg_Title(This,newVal)

#define IVSUIPrefs_get_RvwMsg_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_RvwMsg_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_RvwMsg_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_RvwMsg_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_RvwMsg_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_RvwMsg_HelpUrl(This,pVal)

#define IVSUIPrefs_put_RvwMsg_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_RvwMsg_HelpUrl(This,newVal)

#define IVSUIPrefs_get_IntroDlg_Title(This,pVal)	\
    (This)->lpVtbl -> get_IntroDlg_Title(This,pVal)

#define IVSUIPrefs_put_IntroDlg_Title(This,newVal)	\
    (This)->lpVtbl -> put_IntroDlg_Title(This,newVal)

#define IVSUIPrefs_get_IntroDlg_Text(This,pVal)	\
    (This)->lpVtbl -> get_IntroDlg_Text(This,pVal)

#define IVSUIPrefs_put_IntroDlg_Text(This,newVal)	\
    (This)->lpVtbl -> put_IntroDlg_Text(This,newVal)

#define IVSUIPrefs_get_IntroDlg_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_IntroDlg_HelpUrl(This,pVal)

#define IVSUIPrefs_put_IntroDlg_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_IntroDlg_HelpUrl(This,newVal)

#define IVSUIPrefs_get_CreateNewProf_Title(This,pVal)	\
    (This)->lpVtbl -> get_CreateNewProf_Title(This,pVal)

#define IVSUIPrefs_put_CreateNewProf_Title(This,newVal)	\
    (This)->lpVtbl -> put_CreateNewProf_Title(This,newVal)

#define IVSUIPrefs_get_ChangePasswd_Title(This,pVal)	\
    (This)->lpVtbl -> get_ChangePasswd_Title(This,pVal)

#define IVSUIPrefs_put_ChangePasswd_Title(This,newVal)	\
    (This)->lpVtbl -> put_ChangePasswd_Title(This,newVal)

#define IVSUIPrefs_get_ChangePasswd_Text(This,pVal)	\
    (This)->lpVtbl -> get_ChangePasswd_Text(This,pVal)

#define IVSUIPrefs_put_ChangePasswd_Text(This,newVal)	\
    (This)->lpVtbl -> put_ChangePasswd_Text(This,newVal)

#define IVSUIPrefs_get_ChangePasswd_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_ChangePasswd_OKBtnText(This,pVal)

#define IVSUIPrefs_put_ChangePasswd_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_ChangePasswd_OKBtnText(This,newVal)

#define IVSUIPrefs_get_ChangePasswd_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_ChangePasswd_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_ChangePasswd_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_ChangePasswd_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_ChangePasswd_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_ChangePasswd_HelpUrl(This,pVal)

#define IVSUIPrefs_put_ChangePasswd_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_ChangePasswd_HelpUrl(This,newVal)

#define IVSUIPrefs_get_Timeout_HelpUrl(This,pVal)	\
    (This)->lpVtbl -> get_Timeout_HelpUrl(This,pVal)

#define IVSUIPrefs_put_Timeout_HelpUrl(This,newVal)	\
    (This)->lpVtbl -> put_Timeout_HelpUrl(This,newVal)

#define IVSUIPrefs_put_EnableTopMostWindow(This,newVal)	\
    (This)->lpVtbl -> put_EnableTopMostWindow(This,newVal)

#define IVSUIPrefs_get_SignTransDlgWidth(This,pVal)	\
    (This)->lpVtbl -> get_SignTransDlgWidth(This,pVal)

#define IVSUIPrefs_put_SignTransDlgWidth(This,newVal)	\
    (This)->lpVtbl -> put_SignTransDlgWidth(This,newVal)

#define IVSUIPrefs_get_SignTransDlgHeight(This,pVal)	\
    (This)->lpVtbl -> get_SignTransDlgHeight(This,pVal)

#define IVSUIPrefs_put_SignTransDlgHeight(This,newVal)	\
    (This)->lpVtbl -> put_SignTransDlgHeight(This,newVal)

#define IVSUIPrefs_get_GetSecretQuestion_Title(This,pVal)	\
    (This)->lpVtbl -> get_GetSecretQuestion_Title(This,pVal)

#define IVSUIPrefs_put_GetSecretQuestion_Title(This,newVal)	\
    (This)->lpVtbl -> put_GetSecretQuestion_Title(This,newVal)

#define IVSUIPrefs_get_GetSecretQuestion_Text(This,pVal)	\
    (This)->lpVtbl -> get_GetSecretQuestion_Text(This,pVal)

#define IVSUIPrefs_put_GetSecretQuestion_Text(This,newVal)	\
    (This)->lpVtbl -> put_GetSecretQuestion_Text(This,newVal)

#define IVSUIPrefs_get_GetSecretQuestion_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_GetSecretQuestion_OKBtnText(This,pVal)

#define IVSUIPrefs_put_GetSecretQuestion_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_GetSecretQuestion_OKBtnText(This,newVal)

#define IVSUIPrefs_get_GetSecretQuestion_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_GetSecretQuestion_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_GetSecretQuestion_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_GetSecretQuestion_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_ResetPasswd_Title(This,pVal)	\
    (This)->lpVtbl -> get_ResetPasswd_Title(This,pVal)

#define IVSUIPrefs_put_ResetPasswd_Title(This,newVal)	\
    (This)->lpVtbl -> put_ResetPasswd_Title(This,newVal)

#define IVSUIPrefs_get_ResetPasswd_Text(This,pVal)	\
    (This)->lpVtbl -> get_ResetPasswd_Text(This,pVal)

#define IVSUIPrefs_put_ResetPasswd_Text(This,newVal)	\
    (This)->lpVtbl -> put_ResetPasswd_Text(This,newVal)

#define IVSUIPrefs_get_ResetPasswd_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_ResetPasswd_OKBtnText(This,pVal)

#define IVSUIPrefs_put_ResetPasswd_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_ResetPasswd_OKBtnText(This,newVal)

#define IVSUIPrefs_get_ResetPasswd_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_ResetPasswd_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_ResetPasswd_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_ResetPasswd_CancelBtnText(This,newVal)

#define IVSUIPrefs_get_CreateSecret_Title(This,pVal)	\
    (This)->lpVtbl -> get_CreateSecret_Title(This,pVal)

#define IVSUIPrefs_put_CreateSecret_Title(This,newVal)	\
    (This)->lpVtbl -> put_CreateSecret_Title(This,newVal)

#define IVSUIPrefs_get_CreateSecret_Text(This,pVal)	\
    (This)->lpVtbl -> get_CreateSecret_Text(This,pVal)

#define IVSUIPrefs_put_CreateSecret_Text(This,newVal)	\
    (This)->lpVtbl -> put_CreateSecret_Text(This,newVal)

#define IVSUIPrefs_get_CreateSecret_OKBtnText(This,pVal)	\
    (This)->lpVtbl -> get_CreateSecret_OKBtnText(This,pVal)

#define IVSUIPrefs_put_CreateSecret_OKBtnText(This,newVal)	\
    (This)->lpVtbl -> put_CreateSecret_OKBtnText(This,newVal)

#define IVSUIPrefs_get_CreateSecret_CancelBtnText(This,pVal)	\
    (This)->lpVtbl -> get_CreateSecret_CancelBtnText(This,pVal)

#define IVSUIPrefs_put_CreateSecret_CancelBtnText(This,newVal)	\
    (This)->lpVtbl -> put_CreateSecret_CancelBtnText(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_Language_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_Language_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_Language_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_Language_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_TitleFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_TitleFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_TitleFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_TitleFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_TextFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_TextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_TextFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_TextFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_BtnFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_BtnFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_BtnFont_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_BtnFont_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_UILogoUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_UILogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_UILogoUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_UILogoUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_NewPasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_NewPasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_NewPasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_NewPasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_NewPasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_NewPasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_NewPasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_NewPasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_NewPasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_NewPasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_NewPasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_NewPasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_NewPasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_NewPasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_NewPasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_NewPasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_NewPasswd_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_NewPasswd_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_NewPasswd_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_NewPasswd_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_LgnDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_LgnDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_LgnDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_LgnDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_OpenProf_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_OpenProf_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_OpenProf_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_OpenProf_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_OpenProf_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_OpenProf_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_OpenProf_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_OpenProf_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_OpenProf_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_OpenProf_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_OpenProf_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_OpenProf_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_OpenProf_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_OpenProf_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_OpenProf_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_OpenProf_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_OpenProf_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_OpenProf_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_OpenProf_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_OpenProf_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_ShowDefChkBox_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_ShowDefChkBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_ShowDefChkBox_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_ShowDefChkBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_ChkBoxText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_ChkBoxText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_ChkBoxText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_ChkBoxText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SelID_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SelID_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SelID_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SelID_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SgnDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SgnDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SgnDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SgnDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_RvwMsg_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_RvwMsg_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_RvwMsg_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_RvwMsg_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_RvwMsg_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_RvwMsg_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_RvwMsg_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_RvwMsg_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_RvwMsg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_RvwMsg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_RvwMsg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_RvwMsg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_RvwMsg_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_RvwMsg_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_RvwMsg_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_RvwMsg_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_RvwMsg_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_RvwMsg_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_RvwMsg_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_RvwMsg_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_IntroDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_IntroDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_IntroDlg_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_IntroDlg_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_IntroDlg_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_IntroDlg_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_IntroDlg_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_IntroDlg_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_IntroDlg_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_IntroDlg_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_IntroDlg_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_IntroDlg_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_CreateNewProf_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_CreateNewProf_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_CreateNewProf_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_CreateNewProf_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ChangePasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ChangePasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ChangePasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ChangePasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ChangePasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ChangePasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ChangePasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ChangePasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ChangePasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ChangePasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ChangePasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ChangePasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ChangePasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ChangePasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ChangePasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ChangePasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ChangePasswd_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ChangePasswd_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ChangePasswd_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ChangePasswd_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_Timeout_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_Timeout_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_Timeout_HelpUrl_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_Timeout_HelpUrl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_EnableTopMostWindow_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_EnableTopMostWindow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SignTransDlgWidth_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SignTransDlgWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SignTransDlgWidth_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SignTransDlgWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_SignTransDlgHeight_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_SignTransDlgHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_SignTransDlgHeight_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_SignTransDlgHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_GetSecretQuestion_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_GetSecretQuestion_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_GetSecretQuestion_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_GetSecretQuestion_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_GetSecretQuestion_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_GetSecretQuestion_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_GetSecretQuestion_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_GetSecretQuestion_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_GetSecretQuestion_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_GetSecretQuestion_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_GetSecretQuestion_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_GetSecretQuestion_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_GetSecretQuestion_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_GetSecretQuestion_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_GetSecretQuestion_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_GetSecretQuestion_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ResetPasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ResetPasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ResetPasswd_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ResetPasswd_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ResetPasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ResetPasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ResetPasswd_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ResetPasswd_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ResetPasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ResetPasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ResetPasswd_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ResetPasswd_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_ResetPasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_ResetPasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_ResetPasswd_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_ResetPasswd_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_CreateSecret_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_CreateSecret_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_CreateSecret_Title_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_CreateSecret_Title_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_CreateSecret_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_CreateSecret_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_CreateSecret_Text_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_CreateSecret_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_CreateSecret_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_CreateSecret_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_CreateSecret_OKBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_CreateSecret_OKBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_get_CreateSecret_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSUIPrefs_get_CreateSecret_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSUIPrefs_put_CreateSecret_CancelBtnText_Proxy( 
    IVSUIPrefs __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSUIPrefs_put_CreateSecret_CancelBtnText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSUIPrefs_INTERFACE_DEFINED__ */


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
