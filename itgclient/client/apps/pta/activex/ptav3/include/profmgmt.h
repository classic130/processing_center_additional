/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jun 23 16:33:09 2003
 */
/* Compiler settings for F:\sasi_062003\itgclient\client\apps\pta\activex\ptav3\Source\profmgmt.idl:
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

#ifndef __profmgmt_h__
#define __profmgmt_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IVSProfMgmt_FWD_DEFINED__
#define __IVSProfMgmt_FWD_DEFINED__
typedef interface IVSProfMgmt IVSProfMgmt;
#endif 	/* __IVSProfMgmt_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_profmgmt_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_profmgmt_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_profmgmt_0000_v0_0_s_ifspec;

#ifndef __IVSProfMgmt_INTERFACE_DEFINED__
#define __IVSProfMgmt_INTERFACE_DEFINED__

/* interface IVSProfMgmt */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVSProfMgmt;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8304ffe0-ddad-11d3-a428-444553540000")
    IVSProfMgmt : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReadOKDomains( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReadOKDomains( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_WriteOKDomains( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_WriteOKDomains( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswdQuality( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswdQuality( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswdLength( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswdLength( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswdTimeOut( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswdTimeOut( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswdLockOutTries( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswdLockOutTries( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PasswdUnLockPeriod( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PasswdUnLockPeriod( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenProfile( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseProfile( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Password( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SaveLocal( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SaveLocal( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RoamProfile( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_RoamProfile( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OpenProfFlags( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OpenProfFlags( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveProfile( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangePassword( void) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileOpenHostWildCard( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AddApplicationIfItDoesNotExistFlag( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AddApplicationIfItDoesNotExistFlag( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsUsernameEditable( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsUsernameEditable( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ResetPassword( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveCertificates( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FirstName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FirstName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LastName( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LastName( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Email( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Email( 
            /* [in] */ VARIANT newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVSProfMgmtVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVSProfMgmt __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVSProfMgmt __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReadOKDomains )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReadOKDomains )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_WriteOKDomains )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_WriteOKDomains )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswdQuality )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswdQuality )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswdLength )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswdLength )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswdTimeOut )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswdTimeOut )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswdLockOutTries )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswdLockOutTries )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_PasswdUnLockPeriod )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_PasswdUnLockPeriod )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProfileName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenProfile )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseProfile )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Password )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SaveLocal )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SaveLocal )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RoamProfile )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_RoamProfile )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_OpenProfFlags )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_OpenProfFlags )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveProfile )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangePassword )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProfileOpenHostWildCard )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_AddApplicationIfItDoesNotExistFlag )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_AddApplicationIfItDoesNotExistFlag )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IsUsernameEditable )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_IsUsernameEditable )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassword )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveCertificates )( 
            IVSProfMgmt __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FirstName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FirstName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LastName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_LastName )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Email )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Email )( 
            IVSProfMgmt __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        END_INTERFACE
    } IVSProfMgmtVtbl;

    interface IVSProfMgmt
    {
        CONST_VTBL struct IVSProfMgmtVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVSProfMgmt_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVSProfMgmt_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVSProfMgmt_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVSProfMgmt_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVSProfMgmt_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVSProfMgmt_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVSProfMgmt_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVSProfMgmt_get_ReadOKDomains(This,pVal)	\
    (This)->lpVtbl -> get_ReadOKDomains(This,pVal)

#define IVSProfMgmt_put_ReadOKDomains(This,newVal)	\
    (This)->lpVtbl -> put_ReadOKDomains(This,newVal)

#define IVSProfMgmt_get_WriteOKDomains(This,pVal)	\
    (This)->lpVtbl -> get_WriteOKDomains(This,pVal)

#define IVSProfMgmt_put_WriteOKDomains(This,newVal)	\
    (This)->lpVtbl -> put_WriteOKDomains(This,newVal)

#define IVSProfMgmt_get_PasswdQuality(This,pVal)	\
    (This)->lpVtbl -> get_PasswdQuality(This,pVal)

#define IVSProfMgmt_put_PasswdQuality(This,newVal)	\
    (This)->lpVtbl -> put_PasswdQuality(This,newVal)

#define IVSProfMgmt_get_PasswdLength(This,pVal)	\
    (This)->lpVtbl -> get_PasswdLength(This,pVal)

#define IVSProfMgmt_put_PasswdLength(This,newVal)	\
    (This)->lpVtbl -> put_PasswdLength(This,newVal)

#define IVSProfMgmt_get_PasswdTimeOut(This,pVal)	\
    (This)->lpVtbl -> get_PasswdTimeOut(This,pVal)

#define IVSProfMgmt_put_PasswdTimeOut(This,newVal)	\
    (This)->lpVtbl -> put_PasswdTimeOut(This,newVal)

#define IVSProfMgmt_get_PasswdLockOutTries(This,pVal)	\
    (This)->lpVtbl -> get_PasswdLockOutTries(This,pVal)

#define IVSProfMgmt_put_PasswdLockOutTries(This,newVal)	\
    (This)->lpVtbl -> put_PasswdLockOutTries(This,newVal)

#define IVSProfMgmt_get_PasswdUnLockPeriod(This,pVal)	\
    (This)->lpVtbl -> get_PasswdUnLockPeriod(This,pVal)

#define IVSProfMgmt_put_PasswdUnLockPeriod(This,newVal)	\
    (This)->lpVtbl -> put_PasswdUnLockPeriod(This,newVal)

#define IVSProfMgmt_get_ProfileName(This,pVal)	\
    (This)->lpVtbl -> get_ProfileName(This,pVal)

#define IVSProfMgmt_put_ProfileName(This,newVal)	\
    (This)->lpVtbl -> put_ProfileName(This,newVal)

#define IVSProfMgmt_OpenProfile(This)	\
    (This)->lpVtbl -> OpenProfile(This)

#define IVSProfMgmt_CloseProfile(This)	\
    (This)->lpVtbl -> CloseProfile(This)

#define IVSProfMgmt_put_Password(This,newVal)	\
    (This)->lpVtbl -> put_Password(This,newVal)

#define IVSProfMgmt_get_SaveLocal(This,pVal)	\
    (This)->lpVtbl -> get_SaveLocal(This,pVal)

#define IVSProfMgmt_put_SaveLocal(This,newVal)	\
    (This)->lpVtbl -> put_SaveLocal(This,newVal)

#define IVSProfMgmt_get_RoamProfile(This,pVal)	\
    (This)->lpVtbl -> get_RoamProfile(This,pVal)

#define IVSProfMgmt_put_RoamProfile(This,newVal)	\
    (This)->lpVtbl -> put_RoamProfile(This,newVal)

#define IVSProfMgmt_get_OpenProfFlags(This,pVal)	\
    (This)->lpVtbl -> get_OpenProfFlags(This,pVal)

#define IVSProfMgmt_put_OpenProfFlags(This,newVal)	\
    (This)->lpVtbl -> put_OpenProfFlags(This,newVal)

#define IVSProfMgmt_SaveProfile(This)	\
    (This)->lpVtbl -> SaveProfile(This)

#define IVSProfMgmt_ChangePassword(This)	\
    (This)->lpVtbl -> ChangePassword(This)

#define IVSProfMgmt_put_ProfileOpenHostWildCard(This,newVal)	\
    (This)->lpVtbl -> put_ProfileOpenHostWildCard(This,newVal)

#define IVSProfMgmt_get_AddApplicationIfItDoesNotExistFlag(This,pVal)	\
    (This)->lpVtbl -> get_AddApplicationIfItDoesNotExistFlag(This,pVal)

#define IVSProfMgmt_put_AddApplicationIfItDoesNotExistFlag(This,newVal)	\
    (This)->lpVtbl -> put_AddApplicationIfItDoesNotExistFlag(This,newVal)

#define IVSProfMgmt_get_IsUsernameEditable(This,pVal)	\
    (This)->lpVtbl -> get_IsUsernameEditable(This,pVal)

#define IVSProfMgmt_put_IsUsernameEditable(This,newVal)	\
    (This)->lpVtbl -> put_IsUsernameEditable(This,newVal)

#define IVSProfMgmt_ResetPassword(This)	\
    (This)->lpVtbl -> ResetPassword(This)

#define IVSProfMgmt_RemoveCertificates(This)	\
    (This)->lpVtbl -> RemoveCertificates(This)

#define IVSProfMgmt_get_FirstName(This,pVal)	\
    (This)->lpVtbl -> get_FirstName(This,pVal)

#define IVSProfMgmt_put_FirstName(This,newVal)	\
    (This)->lpVtbl -> put_FirstName(This,newVal)

#define IVSProfMgmt_get_LastName(This,pVal)	\
    (This)->lpVtbl -> get_LastName(This,pVal)

#define IVSProfMgmt_put_LastName(This,newVal)	\
    (This)->lpVtbl -> put_LastName(This,newVal)

#define IVSProfMgmt_get_Email(This,pVal)	\
    (This)->lpVtbl -> get_Email(This,pVal)

#define IVSProfMgmt_put_Email(This,newVal)	\
    (This)->lpVtbl -> put_Email(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_ReadOKDomains_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_ReadOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_ReadOKDomains_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_ReadOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_WriteOKDomains_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_WriteOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_WriteOKDomains_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_WriteOKDomains_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_PasswdQuality_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_PasswdQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_PasswdQuality_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_PasswdQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_PasswdLength_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_PasswdLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_PasswdLength_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_PasswdLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_PasswdTimeOut_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_PasswdTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_PasswdTimeOut_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_PasswdTimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_PasswdLockOutTries_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_PasswdLockOutTries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_PasswdLockOutTries_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_PasswdLockOutTries_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_PasswdUnLockPeriod_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_PasswdUnLockPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_PasswdUnLockPeriod_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_PasswdUnLockPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_ProfileName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_ProfileName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_OpenProfile_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_OpenProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_CloseProfile_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_CloseProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_Password_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_Password_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_SaveLocal_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_SaveLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_SaveLocal_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_SaveLocal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_RoamProfile_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_RoamProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_RoamProfile_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_RoamProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_OpenProfFlags_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_OpenProfFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_OpenProfFlags_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_OpenProfFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_SaveProfile_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_SaveProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_ChangePassword_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_ChangePassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_ProfileOpenHostWildCard_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_ProfileOpenHostWildCard_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_AddApplicationIfItDoesNotExistFlag_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_AddApplicationIfItDoesNotExistFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_AddApplicationIfItDoesNotExistFlag_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_AddApplicationIfItDoesNotExistFlag_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_IsUsernameEditable_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_IsUsernameEditable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_IsUsernameEditable_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_IsUsernameEditable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_ResetPassword_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_ResetPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_RemoveCertificates_Proxy( 
    IVSProfMgmt __RPC_FAR * This);


void __RPC_STUB IVSProfMgmt_RemoveCertificates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_FirstName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_FirstName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_FirstName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_FirstName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_LastName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_LastName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_LastName_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_LastName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_get_Email_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IVSProfMgmt_get_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVSProfMgmt_put_Email_Proxy( 
    IVSProfMgmt __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IVSProfMgmt_put_Email_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVSProfMgmt_INTERFACE_DEFINED__ */


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
