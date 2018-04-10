/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Mon Jul 20 08:51:12 1998
 */
/* Compiler settings for certdb.idl:
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

#ifndef __certdb_h__
#define __certdb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEnumCERTDBCOLUMN_FWD_DEFINED__
#define __IEnumCERTDBCOLUMN_FWD_DEFINED__
typedef interface IEnumCERTDBCOLUMN IEnumCERTDBCOLUMN;
#endif 	/* __IEnumCERTDBCOLUMN_FWD_DEFINED__ */


#ifndef __IEnumCERTDBRESULTROW_FWD_DEFINED__
#define __IEnumCERTDBRESULTROW_FWD_DEFINED__
typedef interface IEnumCERTDBRESULTROW IEnumCERTDBRESULTROW;
#endif 	/* __IEnumCERTDBRESULTROW_FWD_DEFINED__ */


#ifndef __IEnumCERTDBNAME_FWD_DEFINED__
#define __IEnumCERTDBNAME_FWD_DEFINED__
typedef interface IEnumCERTDBNAME IEnumCERTDBNAME;
#endif 	/* __IEnumCERTDBNAME_FWD_DEFINED__ */


#ifndef __ICertDBRow_FWD_DEFINED__
#define __ICertDBRow_FWD_DEFINED__
typedef interface ICertDBRow ICertDBRow;
#endif 	/* __ICertDBRow_FWD_DEFINED__ */


#ifndef __ICertDBBackup_FWD_DEFINED__
#define __ICertDBBackup_FWD_DEFINED__
typedef interface ICertDBBackup ICertDBBackup;
#endif 	/* __ICertDBBackup_FWD_DEFINED__ */


#ifndef __ICertDBRestore_FWD_DEFINED__
#define __ICertDBRestore_FWD_DEFINED__
typedef interface ICertDBRestore ICertDBRestore;
#endif 	/* __ICertDBRestore_FWD_DEFINED__ */


#ifndef __ICertDB_FWD_DEFINED__
#define __ICertDB_FWD_DEFINED__
typedef interface ICertDB ICertDB;
#endif 	/* __ICertDB_FWD_DEFINED__ */


#ifndef __CCertDB_FWD_DEFINED__
#define __CCertDB_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCertDB CCertDB;
#else
typedef struct CCertDB CCertDB;
#endif /* __cplusplus */

#endif 	/* __CCertDB_FWD_DEFINED__ */


/* header files for imported files */
#include "wtypes.h"
#include "certbase.h"
#include "oaidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_certdb_0000 */
/* [local] */ 



typedef struct  _CERTDBATTRIBUTE
    {
    WCHAR __RPC_FAR *pwszName;
    WCHAR __RPC_FAR *pwszValue;
    }	CERTDBATTRIBUTE;

typedef struct  _CERTDBEXTENSION
    {
    WCHAR __RPC_FAR *pwszName;
    LONG ExtFlags;
    DWORD cbValue;
    BYTE __RPC_FAR *pbValue;
    }	CERTDBEXTENSION;

#define	CDBENUM_ATTRIBUTES	( 0 )

#define	CDBENUM_EXTENSIONS	( 0x1 )

typedef struct  _CERTDBCOLUMN
    {
    DWORD Type;
    DWORD Index;
    DWORD cbMax;
    WCHAR __RPC_FAR *pwszName;
    WCHAR __RPC_FAR *pwszDisplayName;
    }	CERTDBCOLUMN;



extern RPC_IF_HANDLE __MIDL_itf_certdb_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certdb_0000_v0_0_s_ifspec;

#ifndef __IEnumCERTDBCOLUMN_INTERFACE_DEFINED__
#define __IEnumCERTDBCOLUMN_INTERFACE_DEFINED__

/* interface IEnumCERTDBCOLUMN */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_IEnumCERTDBCOLUMN;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("a1acf010-5538-11d1-9bdb-00c04fb683fa")
    IEnumCERTDBCOLUMN : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBCOLUMN __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumCERTDBCOLUMNVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBCOLUMN __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This,
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumCERTDBCOLUMN __RPC_FAR * This,
            /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum);
        
        END_INTERFACE
    } IEnumCERTDBCOLUMNVtbl;

    interface IEnumCERTDBCOLUMN
    {
        CONST_VTBL struct IEnumCERTDBCOLUMNVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumCERTDBCOLUMN_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumCERTDBCOLUMN_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumCERTDBCOLUMN_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumCERTDBCOLUMN_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumCERTDBCOLUMN_Skip(This,celt,pielt)	\
    (This)->lpVtbl -> Skip(This,celt,pielt)

#define IEnumCERTDBCOLUMN_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumCERTDBCOLUMN_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumCERTDBCOLUMN_Next_Proxy( 
    IEnumCERTDBCOLUMN __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ CERTDBCOLUMN __RPC_FAR *rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumCERTDBCOLUMN_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBCOLUMN_Skip_Proxy( 
    IEnumCERTDBCOLUMN __RPC_FAR * This,
    /* [in] */ LONG celt,
    /* [out] */ LONG __RPC_FAR *pielt);


void __RPC_STUB IEnumCERTDBCOLUMN_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBCOLUMN_Reset_Proxy( 
    IEnumCERTDBCOLUMN __RPC_FAR * This);


void __RPC_STUB IEnumCERTDBCOLUMN_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBCOLUMN_Clone_Proxy( 
    IEnumCERTDBCOLUMN __RPC_FAR * This,
    /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumCERTDBCOLUMN_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumCERTDBCOLUMN_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_certdb_0108 */
/* [local] */ 

typedef struct  _CERTDBRESULTCOLUMN
    {
    DWORD Type;
    DWORD Index;
    BYTE __RPC_FAR *pbValue;
    DWORD cbValue;
    }	CERTDBRESULTCOLUMN;

typedef struct  _CERTDBRESULTROW
    {
    DWORD rowid;
    DWORD ccol;
    CERTDBRESULTCOLUMN __RPC_FAR *acol;
    }	CERTDBRESULTROW;



extern RPC_IF_HANDLE __MIDL_itf_certdb_0108_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certdb_0108_v0_0_s_ifspec;

#ifndef __IEnumCERTDBRESULTROW_INTERFACE_DEFINED__
#define __IEnumCERTDBRESULTROW_INTERFACE_DEFINED__

/* interface IEnumCERTDBRESULTROW */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_IEnumCERTDBRESULTROW;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d40179b4-5f88-11d1-9bdc-00c04fb683fa")
    IEnumCERTDBRESULTROW : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBRESULTROW __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReleaseResultRow( 
            /* [in] */ ULONG celt,
            /* [out][in] */ CERTDBRESULTROW __RPC_FAR *rgelt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumCERTDBRESULTROWVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBRESULTROW __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReleaseResultRow )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out][in] */ CERTDBRESULTROW __RPC_FAR *rgelt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This,
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumCERTDBRESULTROW __RPC_FAR * This,
            /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum);
        
        END_INTERFACE
    } IEnumCERTDBRESULTROWVtbl;

    interface IEnumCERTDBRESULTROW
    {
        CONST_VTBL struct IEnumCERTDBRESULTROWVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumCERTDBRESULTROW_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumCERTDBRESULTROW_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumCERTDBRESULTROW_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumCERTDBRESULTROW_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumCERTDBRESULTROW_ReleaseResultRow(This,celt,rgelt)	\
    (This)->lpVtbl -> ReleaseResultRow(This,celt,rgelt)

#define IEnumCERTDBRESULTROW_Skip(This,celt,pielt)	\
    (This)->lpVtbl -> Skip(This,celt,pielt)

#define IEnumCERTDBRESULTROW_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumCERTDBRESULTROW_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumCERTDBRESULTROW_Next_Proxy( 
    IEnumCERTDBRESULTROW __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ CERTDBRESULTROW __RPC_FAR *rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumCERTDBRESULTROW_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBRESULTROW_ReleaseResultRow_Proxy( 
    IEnumCERTDBRESULTROW __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out][in] */ CERTDBRESULTROW __RPC_FAR *rgelt);


void __RPC_STUB IEnumCERTDBRESULTROW_ReleaseResultRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBRESULTROW_Skip_Proxy( 
    IEnumCERTDBRESULTROW __RPC_FAR * This,
    /* [in] */ LONG celt,
    /* [out] */ LONG __RPC_FAR *pielt);


void __RPC_STUB IEnumCERTDBRESULTROW_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBRESULTROW_Reset_Proxy( 
    IEnumCERTDBRESULTROW __RPC_FAR * This);


void __RPC_STUB IEnumCERTDBRESULTROW_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBRESULTROW_Clone_Proxy( 
    IEnumCERTDBRESULTROW __RPC_FAR * This,
    /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumCERTDBRESULTROW_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumCERTDBRESULTROW_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_certdb_0110 */
/* [local] */ 

typedef struct  _CERTDBNAME
    {
    WCHAR __RPC_FAR *pwszName;
    }	CERTDBNAME;



extern RPC_IF_HANDLE __MIDL_itf_certdb_0110_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certdb_0110_v0_0_s_ifspec;

#ifndef __IEnumCERTDBNAME_INTERFACE_DEFINED__
#define __IEnumCERTDBNAME_INTERFACE_DEFINED__

/* interface IEnumCERTDBNAME */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_IEnumCERTDBNAME;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2bc6b980-31d8-11d1-a5c7-0080c79bbd92")
    IEnumCERTDBNAME : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBNAME __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumCERTDBNAMEVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEnumCERTDBNAME __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEnumCERTDBNAME __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEnumCERTDBNAME __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Next )( 
            IEnumCERTDBNAME __RPC_FAR * This,
            /* [in] */ ULONG celt,
            /* [out] */ CERTDBNAME __RPC_FAR *rgelt,
            /* [out] */ ULONG __RPC_FAR *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Skip )( 
            IEnumCERTDBNAME __RPC_FAR * This,
            /* [in] */ LONG celt,
            /* [out] */ LONG __RPC_FAR *pielt);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEnumCERTDBNAME __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clone )( 
            IEnumCERTDBNAME __RPC_FAR * This,
            /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum);
        
        END_INTERFACE
    } IEnumCERTDBNAMEVtbl;

    interface IEnumCERTDBNAME
    {
        CONST_VTBL struct IEnumCERTDBNAMEVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumCERTDBNAME_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumCERTDBNAME_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumCERTDBNAME_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumCERTDBNAME_Next(This,celt,rgelt,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,rgelt,pceltFetched)

#define IEnumCERTDBNAME_Skip(This,celt,pielt)	\
    (This)->lpVtbl -> Skip(This,celt,pielt)

#define IEnumCERTDBNAME_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumCERTDBNAME_Clone(This,ppenum)	\
    (This)->lpVtbl -> Clone(This,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumCERTDBNAME_Next_Proxy( 
    IEnumCERTDBNAME __RPC_FAR * This,
    /* [in] */ ULONG celt,
    /* [out] */ CERTDBNAME __RPC_FAR *rgelt,
    /* [out] */ ULONG __RPC_FAR *pceltFetched);


void __RPC_STUB IEnumCERTDBNAME_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBNAME_Skip_Proxy( 
    IEnumCERTDBNAME __RPC_FAR * This,
    /* [in] */ LONG celt,
    /* [out] */ LONG __RPC_FAR *pielt);


void __RPC_STUB IEnumCERTDBNAME_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBNAME_Reset_Proxy( 
    IEnumCERTDBNAME __RPC_FAR * This);


void __RPC_STUB IEnumCERTDBNAME_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumCERTDBNAME_Clone_Proxy( 
    IEnumCERTDBNAME __RPC_FAR * This,
    /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB IEnumCERTDBNAME_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumCERTDBNAME_INTERFACE_DEFINED__ */


#ifndef __ICertDBRow_INTERFACE_DEFINED__
#define __ICertDBRow_INTERFACE_DEFINED__

/* interface ICertDBRow */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_ICertDBRow;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("434a1410-31da-11d1-a5c7-0080c79bbd92")
    ICertDBRow : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BeginTransaction( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CommitTransaction( 
            /* [in] */ BOOL fCommit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRequestId( 
            /* [out] */ DWORD __RPC_FAR *pReqId) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProperty( 
            /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD cbProp,
            /* [in] */ const BYTE __RPC_FAR *pbProp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProperty( 
            /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ DWORD __RPC_FAR *pcbProp,
            /* [out] */ BYTE __RPC_FAR *pbProp) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetExtension( 
            /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
            /* [in] */ DWORD dwExtFlags,
            /* [in] */ DWORD cbValue,
            /* [in] */ const BYTE __RPC_FAR *pbValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetExtension( 
            /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
            /* [out] */ DWORD __RPC_FAR *pdwExtFlags,
            /* [out][in] */ DWORD __RPC_FAR *pcbValue,
            /* [out] */ BYTE __RPC_FAR *pbValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CopyRequestNames( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumCertDBName( 
            /* [in] */ DWORD dwFlags,
            /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertDBRowVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertDBRow __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertDBRow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BeginTransaction )( 
            ICertDBRow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CommitTransaction )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ BOOL fCommit);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRequestId )( 
            ICertDBRow __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pReqId);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProperty )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
            /* [in] */ DWORD dwFlags,
            /* [in] */ DWORD cbProp,
            /* [in] */ const BYTE __RPC_FAR *pbProp);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProperty )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
            /* [in] */ DWORD dwFlags,
            /* [out][in] */ DWORD __RPC_FAR *pcbProp,
            /* [out] */ BYTE __RPC_FAR *pbProp);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetExtension )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
            /* [in] */ DWORD dwExtFlags,
            /* [in] */ DWORD cbValue,
            /* [in] */ const BYTE __RPC_FAR *pbValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExtension )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
            /* [out] */ DWORD __RPC_FAR *pdwExtFlags,
            /* [out][in] */ DWORD __RPC_FAR *pcbValue,
            /* [out] */ BYTE __RPC_FAR *pbValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CopyRequestNames )( 
            ICertDBRow __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumCertDBName )( 
            ICertDBRow __RPC_FAR * This,
            /* [in] */ DWORD dwFlags,
            /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum);
        
        END_INTERFACE
    } ICertDBRowVtbl;

    interface ICertDBRow
    {
        CONST_VTBL struct ICertDBRowVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertDBRow_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertDBRow_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertDBRow_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertDBRow_BeginTransaction(This)	\
    (This)->lpVtbl -> BeginTransaction(This)

#define ICertDBRow_CommitTransaction(This,fCommit)	\
    (This)->lpVtbl -> CommitTransaction(This,fCommit)

#define ICertDBRow_GetRequestId(This,pReqId)	\
    (This)->lpVtbl -> GetRequestId(This,pReqId)

#define ICertDBRow_SetProperty(This,pwszPropName,dwFlags,cbProp,pbProp)	\
    (This)->lpVtbl -> SetProperty(This,pwszPropName,dwFlags,cbProp,pbProp)

#define ICertDBRow_GetProperty(This,pwszPropName,dwFlags,pcbProp,pbProp)	\
    (This)->lpVtbl -> GetProperty(This,pwszPropName,dwFlags,pcbProp,pbProp)

#define ICertDBRow_SetExtension(This,pwszExtensionName,dwExtFlags,cbValue,pbValue)	\
    (This)->lpVtbl -> SetExtension(This,pwszExtensionName,dwExtFlags,cbValue,pbValue)

#define ICertDBRow_GetExtension(This,pwszExtensionName,pdwExtFlags,pcbValue,pbValue)	\
    (This)->lpVtbl -> GetExtension(This,pwszExtensionName,pdwExtFlags,pcbValue,pbValue)

#define ICertDBRow_CopyRequestNames(This)	\
    (This)->lpVtbl -> CopyRequestNames(This)

#define ICertDBRow_EnumCertDBName(This,dwFlags,ppenum)	\
    (This)->lpVtbl -> EnumCertDBName(This,dwFlags,ppenum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertDBRow_BeginTransaction_Proxy( 
    ICertDBRow __RPC_FAR * This);


void __RPC_STUB ICertDBRow_BeginTransaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_CommitTransaction_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ BOOL fCommit);


void __RPC_STUB ICertDBRow_CommitTransaction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_GetRequestId_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pReqId);


void __RPC_STUB ICertDBRow_GetRequestId_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_SetProperty_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
    /* [in] */ DWORD dwFlags,
    /* [in] */ DWORD cbProp,
    /* [in] */ const BYTE __RPC_FAR *pbProp);


void __RPC_STUB ICertDBRow_SetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_GetProperty_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszPropName,
    /* [in] */ DWORD dwFlags,
    /* [out][in] */ DWORD __RPC_FAR *pcbProp,
    /* [out] */ BYTE __RPC_FAR *pbProp);


void __RPC_STUB ICertDBRow_GetProperty_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_SetExtension_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
    /* [in] */ DWORD dwExtFlags,
    /* [in] */ DWORD cbValue,
    /* [in] */ const BYTE __RPC_FAR *pbValue);


void __RPC_STUB ICertDBRow_SetExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_GetExtension_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszExtensionName,
    /* [out] */ DWORD __RPC_FAR *pdwExtFlags,
    /* [out][in] */ DWORD __RPC_FAR *pcbValue,
    /* [out] */ BYTE __RPC_FAR *pbValue);


void __RPC_STUB ICertDBRow_GetExtension_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_CopyRequestNames_Proxy( 
    ICertDBRow __RPC_FAR * This);


void __RPC_STUB ICertDBRow_CopyRequestNames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBRow_EnumCertDBName_Proxy( 
    ICertDBRow __RPC_FAR * This,
    /* [in] */ DWORD dwFlags,
    /* [out] */ IEnumCERTDBNAME __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB ICertDBRow_EnumCertDBName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertDBRow_INTERFACE_DEFINED__ */


#ifndef __ICertDBBackup_INTERFACE_DEFINED__
#define __ICertDBBackup_INTERFACE_DEFINED__

/* interface ICertDBBackup */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_ICertDBBackup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("40d78e50-d33b-11d1-8641-00aa00615092")
    ICertDBBackup : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDBFileList( 
            /* [out][in] */ DWORD __RPC_FAR *pcwcList,
            /* [out] */ WCHAR __RPC_FAR *pwszzList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLogFileList( 
            /* [out][in] */ DWORD __RPC_FAR *pcwcList,
            /* [out] */ WCHAR __RPC_FAR *pwszzList) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE NextInList( 
            /* [out][in] */ const WCHAR __RPC_FAR *__RPC_FAR *ppwsz) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenFile( 
            /* [in] */ const WCHAR __RPC_FAR *pwszFile,
            /* [out] */ ULARGE_INTEGER __RPC_FAR *pliSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadFile( 
            /* [out][in] */ DWORD __RPC_FAR *pcb,
            /* [out] */ BYTE __RPC_FAR *pb) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CloseFile( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TruncateLog( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertDBBackupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertDBBackup __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertDBBackup __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertDBBackup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDBFileList )( 
            ICertDBBackup __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcwcList,
            /* [out] */ WCHAR __RPC_FAR *pwszzList);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLogFileList )( 
            ICertDBBackup __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcwcList,
            /* [out] */ WCHAR __RPC_FAR *pwszzList);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NextInList )( 
            ICertDBBackup __RPC_FAR * This,
            /* [out][in] */ const WCHAR __RPC_FAR *__RPC_FAR *ppwsz);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenFile )( 
            ICertDBBackup __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszFile,
            /* [out] */ ULARGE_INTEGER __RPC_FAR *pliSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadFile )( 
            ICertDBBackup __RPC_FAR * This,
            /* [out][in] */ DWORD __RPC_FAR *pcb,
            /* [out] */ BYTE __RPC_FAR *pb);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseFile )( 
            ICertDBBackup __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TruncateLog )( 
            ICertDBBackup __RPC_FAR * This);
        
        END_INTERFACE
    } ICertDBBackupVtbl;

    interface ICertDBBackup
    {
        CONST_VTBL struct ICertDBBackupVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertDBBackup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertDBBackup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertDBBackup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertDBBackup_GetDBFileList(This,pcwcList,pwszzList)	\
    (This)->lpVtbl -> GetDBFileList(This,pcwcList,pwszzList)

#define ICertDBBackup_GetLogFileList(This,pcwcList,pwszzList)	\
    (This)->lpVtbl -> GetLogFileList(This,pcwcList,pwszzList)

#define ICertDBBackup_NextInList(This,ppwsz)	\
    (This)->lpVtbl -> NextInList(This,ppwsz)

#define ICertDBBackup_OpenFile(This,pwszFile,pliSize)	\
    (This)->lpVtbl -> OpenFile(This,pwszFile,pliSize)

#define ICertDBBackup_ReadFile(This,pcb,pb)	\
    (This)->lpVtbl -> ReadFile(This,pcb,pb)

#define ICertDBBackup_CloseFile(This)	\
    (This)->lpVtbl -> CloseFile(This)

#define ICertDBBackup_TruncateLog(This)	\
    (This)->lpVtbl -> TruncateLog(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertDBBackup_GetDBFileList_Proxy( 
    ICertDBBackup __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcwcList,
    /* [out] */ WCHAR __RPC_FAR *pwszzList);


void __RPC_STUB ICertDBBackup_GetDBFileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_GetLogFileList_Proxy( 
    ICertDBBackup __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcwcList,
    /* [out] */ WCHAR __RPC_FAR *pwszzList);


void __RPC_STUB ICertDBBackup_GetLogFileList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_NextInList_Proxy( 
    ICertDBBackup __RPC_FAR * This,
    /* [out][in] */ const WCHAR __RPC_FAR *__RPC_FAR *ppwsz);


void __RPC_STUB ICertDBBackup_NextInList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_OpenFile_Proxy( 
    ICertDBBackup __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszFile,
    /* [out] */ ULARGE_INTEGER __RPC_FAR *pliSize);


void __RPC_STUB ICertDBBackup_OpenFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_ReadFile_Proxy( 
    ICertDBBackup __RPC_FAR * This,
    /* [out][in] */ DWORD __RPC_FAR *pcb,
    /* [out] */ BYTE __RPC_FAR *pb);


void __RPC_STUB ICertDBBackup_ReadFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_CloseFile_Proxy( 
    ICertDBBackup __RPC_FAR * This);


void __RPC_STUB ICertDBBackup_CloseFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDBBackup_TruncateLog_Proxy( 
    ICertDBBackup __RPC_FAR * This);


void __RPC_STUB ICertDBBackup_TruncateLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertDBBackup_INTERFACE_DEFINED__ */


#ifndef __ICertDBRestore_INTERFACE_DEFINED__
#define __ICertDBRestore_INTERFACE_DEFINED__

/* interface ICertDBRestore */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_ICertDBRestore;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3fd24140-d33b-11d1-8641-00aa00615092")
    ICertDBRestore : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Restore( 
            /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir,
            /* [in] */ BOOL fIncremental) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertDBRestoreVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertDBRestore __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertDBRestore __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertDBRestore __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Restore )( 
            ICertDBRestore __RPC_FAR * This,
            /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir,
            /* [in] */ BOOL fIncremental);
        
        END_INTERFACE
    } ICertDBRestoreVtbl;

    interface ICertDBRestore
    {
        CONST_VTBL struct ICertDBRestoreVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertDBRestore_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertDBRestore_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertDBRestore_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertDBRestore_Restore(This,pwszRestoreDir,fIncremental)	\
    (This)->lpVtbl -> Restore(This,pwszRestoreDir,fIncremental)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertDBRestore_Restore_Proxy( 
    ICertDBRestore __RPC_FAR * This,
    /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir,
    /* [in] */ BOOL fIncremental);


void __RPC_STUB ICertDBRestore_Restore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertDBRestore_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_certdb_0118 */
/* [local] */ 

#define	CDBBACKUP_INCREMENTAL	( 0x1 )

#define	CDBBACKUP_KEEPOLDLOGS	( 0x2 )

#define	CDBBACKUP_VALID	( 0x3 )



extern RPC_IF_HANDLE __MIDL_itf_certdb_0118_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_certdb_0118_v0_0_s_ifspec;

#ifndef __ICertDB_INTERFACE_DEFINED__
#define __ICertDB_INTERFACE_DEFINED__

/* interface ICertDB */
/* [unique][helpstring][local][uuid][object] */ 


EXTERN_C const IID IID_ICertDB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("481b1b3c-23e0-11d1-9bd6-00c04fb683fa")
    ICertDB : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ BOOL fReadOnly,
            /* [in] */ DWORD cSession,
            /* [in] */ const WCHAR __RPC_FAR *pwszDBFile,
            /* [in] */ const WCHAR __RPC_FAR *pwszLogDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszSystemDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszTempDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ShutDown( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenRow( 
            /* [in] */ BOOL fReadOnly,
            /* [in] */ DWORD ReqId,
            /* [in] */ const WCHAR __RPC_FAR *pwszSerialNumber,
            /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRow( 
            /* [in] */ DWORD ReqId,
            /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenView( 
            /* [in] */ DWORD ccvr,
            /* [in] */ const CERTVIEWRESTRICTION __RPC_FAR *acvr,
            /* [in] */ DWORD ccolOut,
            /* [in] */ const DWORD __RPC_FAR *acolOut,
            /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumCertDBColumn( 
            /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenBackup( 
            /* [in] */ LONG Flags,
            /* [out] */ ICertDBBackup __RPC_FAR *__RPC_FAR *ppBackup) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OpenRestore( 
            /* [out] */ ICertDBRestore __RPC_FAR *__RPC_FAR *ppRestore) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDefaultColumnSet( 
            /* [in] */ DWORD iColumnSetDefault,
            /* [in] */ DWORD cColumnIds,
            /* [out] */ DWORD __RPC_FAR *pcColumnIds,
            /* [ref][out] */ DWORD __RPC_FAR *pColumnIds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICertDBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICertDB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICertDB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ BOOL fReadOnly,
            /* [in] */ DWORD cSession,
            /* [in] */ const WCHAR __RPC_FAR *pwszDBFile,
            /* [in] */ const WCHAR __RPC_FAR *pwszLogDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszSystemDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszTempDir,
            /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShutDown )( 
            ICertDB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRow )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ BOOL fReadOnly,
            /* [in] */ DWORD ReqId,
            /* [in] */ const WCHAR __RPC_FAR *pwszSerialNumber,
            /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRow )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ DWORD ReqId,
            /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenView )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ DWORD ccvr,
            /* [in] */ const CERTVIEWRESTRICTION __RPC_FAR *acvr,
            /* [in] */ DWORD ccolOut,
            /* [in] */ const DWORD __RPC_FAR *acolOut,
            /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumCertDBColumn )( 
            ICertDB __RPC_FAR * This,
            /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenBackup )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ LONG Flags,
            /* [out] */ ICertDBBackup __RPC_FAR *__RPC_FAR *ppBackup);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenRestore )( 
            ICertDB __RPC_FAR * This,
            /* [out] */ ICertDBRestore __RPC_FAR *__RPC_FAR *ppRestore);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDefaultColumnSet )( 
            ICertDB __RPC_FAR * This,
            /* [in] */ DWORD iColumnSetDefault,
            /* [in] */ DWORD cColumnIds,
            /* [out] */ DWORD __RPC_FAR *pcColumnIds,
            /* [ref][out] */ DWORD __RPC_FAR *pColumnIds);
        
        END_INTERFACE
    } ICertDBVtbl;

    interface ICertDB
    {
        CONST_VTBL struct ICertDBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICertDB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICertDB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICertDB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICertDB_Open(This,fReadOnly,cSession,pwszDBFile,pwszLogDir,pwszSystemDir,pwszTempDir,pwszRestoreDir)	\
    (This)->lpVtbl -> Open(This,fReadOnly,cSession,pwszDBFile,pwszLogDir,pwszSystemDir,pwszTempDir,pwszRestoreDir)

#define ICertDB_ShutDown(This)	\
    (This)->lpVtbl -> ShutDown(This)

#define ICertDB_OpenRow(This,fReadOnly,ReqId,pwszSerialNumber,pprow)	\
    (This)->lpVtbl -> OpenRow(This,fReadOnly,ReqId,pwszSerialNumber,pprow)

#define ICertDB_GetRow(This,ReqId,pprow)	\
    (This)->lpVtbl -> GetRow(This,ReqId,pprow)

#define ICertDB_OpenView(This,ccvr,acvr,ccolOut,acolOut,ppenum)	\
    (This)->lpVtbl -> OpenView(This,ccvr,acvr,ccolOut,acolOut,ppenum)

#define ICertDB_EnumCertDBColumn(This,ppenum)	\
    (This)->lpVtbl -> EnumCertDBColumn(This,ppenum)

#define ICertDB_OpenBackup(This,Flags,ppBackup)	\
    (This)->lpVtbl -> OpenBackup(This,Flags,ppBackup)

#define ICertDB_OpenRestore(This,ppRestore)	\
    (This)->lpVtbl -> OpenRestore(This,ppRestore)

#define ICertDB_GetDefaultColumnSet(This,iColumnSetDefault,cColumnIds,pcColumnIds,pColumnIds)	\
    (This)->lpVtbl -> GetDefaultColumnSet(This,iColumnSetDefault,cColumnIds,pcColumnIds,pColumnIds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE ICertDB_Open_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ BOOL fReadOnly,
    /* [in] */ DWORD cSession,
    /* [in] */ const WCHAR __RPC_FAR *pwszDBFile,
    /* [in] */ const WCHAR __RPC_FAR *pwszLogDir,
    /* [in] */ const WCHAR __RPC_FAR *pwszSystemDir,
    /* [in] */ const WCHAR __RPC_FAR *pwszTempDir,
    /* [in] */ const WCHAR __RPC_FAR *pwszRestoreDir);


void __RPC_STUB ICertDB_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_ShutDown_Proxy( 
    ICertDB __RPC_FAR * This);


void __RPC_STUB ICertDB_ShutDown_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_OpenRow_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ BOOL fReadOnly,
    /* [in] */ DWORD ReqId,
    /* [in] */ const WCHAR __RPC_FAR *pwszSerialNumber,
    /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow);


void __RPC_STUB ICertDB_OpenRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_GetRow_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ DWORD ReqId,
    /* [out] */ ICertDBRow __RPC_FAR *__RPC_FAR *pprow);


void __RPC_STUB ICertDB_GetRow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_OpenView_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ DWORD ccvr,
    /* [in] */ const CERTVIEWRESTRICTION __RPC_FAR *acvr,
    /* [in] */ DWORD ccolOut,
    /* [in] */ const DWORD __RPC_FAR *acolOut,
    /* [out] */ IEnumCERTDBRESULTROW __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB ICertDB_OpenView_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_EnumCertDBColumn_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [out] */ IEnumCERTDBCOLUMN __RPC_FAR *__RPC_FAR *ppenum);


void __RPC_STUB ICertDB_EnumCertDBColumn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_OpenBackup_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ LONG Flags,
    /* [out] */ ICertDBBackup __RPC_FAR *__RPC_FAR *ppBackup);


void __RPC_STUB ICertDB_OpenBackup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_OpenRestore_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [out] */ ICertDBRestore __RPC_FAR *__RPC_FAR *ppRestore);


void __RPC_STUB ICertDB_OpenRestore_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE ICertDB_GetDefaultColumnSet_Proxy( 
    ICertDB __RPC_FAR * This,
    /* [in] */ DWORD iColumnSetDefault,
    /* [in] */ DWORD cColumnIds,
    /* [out] */ DWORD __RPC_FAR *pcColumnIds,
    /* [ref][out] */ DWORD __RPC_FAR *pColumnIds);


void __RPC_STUB ICertDB_GetDefaultColumnSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICertDB_INTERFACE_DEFINED__ */



#ifndef __CERTDBLib_LIBRARY_DEFINED__
#define __CERTDBLib_LIBRARY_DEFINED__

/* library CERTDBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CERTDBLib;

EXTERN_C const CLSID CLSID_CCertDB;

#ifdef __cplusplus

class DECLSPEC_UUID("4795978c-23e0-11d1-9bd6-00c04fb683fa")
CCertDB;
#endif
#endif /* __CERTDBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
