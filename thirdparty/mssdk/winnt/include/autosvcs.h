// Created by Microsoft (R) C/C++ Compiler Version 11.00.0000 (ab807308).
//
// f:\viper\src\comsvcs\sdk\objd\i386\public.tlh
//
// C++ source equivalent of Win32 type library public.tlb
// compiler-generated file created 07/31/98 at 13:55:07 - DO NOT EDIT!

#pragma once
#pragma pack(push, 8)

#include <comdef.h>


//
// User-injected statements
//

struct IObjectContext;
extern "C" HRESULT __cdecl GetObjectContext (IObjectContext** ppInstanceContext);
extern "C" void* __cdecl SafeRef(REFIID rid, IUnknown* pUnk);

#define LIBID_TxCTx LIBID_COMSVCSLib

#ifndef _MTX_NOFORCE_LIBS
#pragma comment(lib, "mtx.lib")
#endif

#define CONTEXT_E_ABORTED                 0x8004E002
#define CONTEXT_E_ABORTING                0x8004E003
#define CONTEXT_E_NOCONTEXT               0x8004E004
#define CONTEXT_E_NOTREGISTERED           0x8004E005
#define CONTEXT_E_SYNCH_TIMEOUT           0x8004E006
#define CONTEXT_E_OLDREF                  0x8004E007
#define CONTEXT_E_ROLENOTFOUND            0x8004E00C
#define CONTEXT_E_NOSECURITY              0x8004E00D
#define CONTEXT_E_WRONGTHREAD             0x8004E00E
#define CONTEXT_E_TMNOTAVAILABLE          0x8004E00F
#define CONTEXT_E_INSUFFICIENTLICENSES    0x8004E020

//
// Forward references and typedefs
//

struct /* coclass */ SecurityCertificate;
struct __declspec(uuid("cafc823b-b441-11d1-b82b-0000f8757e2a"))
/* dual interface */ ISecurityCertificateColl;
struct /* coclass */ SecurityIdentity;
struct __declspec(uuid("cafc823c-b441-11d1-b82b-0000f8757e2a"))
/* dual interface */ ISecurityIdentityColl;
struct /* coclass */ SecurityCallers;
struct __declspec(uuid("cafc823d-b441-11d1-b82b-0000f8757e2a"))
/* dual interface */ ISecurityCallersColl;
struct /* coclass */ SecurityCallContext;
struct __declspec(uuid("cafc823e-b441-11d1-b82b-0000f8757e2a"))
/* dual interface */ ISecurityCallContext;
struct /* coclass */ GetSecurityCallContextAppObject;
struct __declspec(uuid("cafc823f-b441-11d1-b82b-0000f8757e2a"))
/* dual interface */ IGetSecurityCallContext;
struct /* coclass */ Dummy30040732;
struct __declspec(uuid("51372ae0-cae7-11cf-be81-00aa00a2fa25"))
/* interface */ IObjectContext;
struct __declspec(uuid("51372afc-cae7-11cf-be81-00aa00a2fa25"))
/* interface */ IObjectContextActivity;
struct __declspec(uuid("75b52ddb-e8ed-11d1-93ad-00aa00ba3258"))
/* interface */ IObjectContextInfo;
struct __declspec(uuid("401f7922-d32c-11d1-939a-00aa00ba3258"))
/* interface */ IObjectConstruct;
struct __declspec(uuid("04dfd095-e378-11d1-93a2-00aa00ba3258"))
/* interface */ IObjectConstructString;
struct __declspec(uuid("51372aec-cae7-11cf-be81-00aa00a2fa25"))
/* interface */ IObjectControl;
struct __declspec(uuid("51372afd-cae7-11cf-be81-00aa00a2fa25"))
/* interface */ IPlaybackControl;
struct __declspec(uuid("51372aea-cae7-11cf-be81-00aa00a2fa25"))
/* interface */ ISecurityProperty;
typedef enum __MIDL___MIDL_itf_public_0000_0001 Error_Constants;
struct __declspec(uuid("7dc41850-0c31-11d0-8b79-00aa00b8a790"))
/* interface */ ObjectControl;
struct /* coclass */ AppServer;
struct __declspec(uuid("74c08641-cedb-11cf-8b49-00aa00b8a790"))
/* dual interface */ IMTxAS;
struct __declspec(uuid("74c08646-cedb-11cf-8b49-00aa00b8a790"))
/* dual interface */ ObjectContext;
struct __declspec(uuid("e74a7215-014d-11d1-a63c-00a0c911b4e0"))
/* dual interface */ SecurityProperty;
struct __declspec(uuid("19a5a02c-0ac8-11d2-b286-00c04f8ef934"))
/* dual interface */ ContextInfo;
struct /* coclass */ TransactionContext;
struct __declspec(uuid("7999fc21-d3c6-11cf-acab-00a024a55aef"))
/* dual interface */ ITransactionContext;
struct /* coclass */ TransactionContextEx;
struct __declspec(uuid("7999fc22-d3c6-11cf-acab-00a024a55aef"))
/* interface */ ITransactionContextEx;
struct /* coclass */ SharedProperty;
struct __declspec(uuid("2a005c01-a5de-11cf-9e66-00aa00a3f464"))
/* dual interface */ ISharedProperty;
struct /* coclass */ SharedPropertyGroup;
struct __declspec(uuid("2a005c07-a5de-11cf-9e66-00aa00a3f464"))
/* dual interface */ ISharedPropertyGroup;
struct /* coclass */ SharedPropertyGroupManager;
struct __declspec(uuid("2a005c0d-a5de-11cf-9e66-00aa00a3f464"))
/* dual interface */ ISharedPropertyGroupManager;
typedef enum __MIDL___MIDL_itf_public_0000_0002 LockModes;
typedef enum __MIDL___MIDL_itf_public_0000_0003 ReleaseModes;
struct /* coclass */ TrackerServer;
struct __declspec(uuid("413dafb0-bcf4-11d1-861d-0080c729264d"))
/* interface */ IReceiveAppData;
struct __declspec(uuid("ea61e3c1-7c62-11cf-be3f-00aa00a2fa25"))
/* interface */ IAppTrackerAdmin;
struct CAppStatistics;
struct CCLSIDData;
struct __declspec(uuid("b60040e0-bcf3-11d1-861d-0080c729264d"))
/* interface */ IGetAppData;
struct CAppData;
struct /* coclass */ CoMTSEvents;
struct __declspec(uuid("bacedf4d-74ab-11d0-b162-00aa00ba3258"))
/* dual interface */ IMtsEvents;
struct __declspec(uuid("d56c3dc1-8482-11d0-b170-00aa00ba3258"))
/* dual interface */ IMtsEventInfo;
struct /* coclass */ CoMTSLocator;
struct __declspec(uuid("d19b8bfd-7f88-11d0-b16e-00aa00ba3258"))
/* dual interface */ IMTSLocator;
struct /* coclass */ MtsGrp;
struct __declspec(uuid("4b2e958c-0393-11d1-b1ab-00aa00ba3258"))
/* dual interface */ IMtsGrp;

//
// Smart pointer typedef declarations
//

_COM_SMARTPTR_TYPEDEF(ISecurityCertificateColl, __uuidof(ISecurityCertificateColl));
_COM_SMARTPTR_TYPEDEF(ISecurityIdentityColl, __uuidof(ISecurityIdentityColl));
_COM_SMARTPTR_TYPEDEF(ISecurityCallersColl, __uuidof(ISecurityCallersColl));
_COM_SMARTPTR_TYPEDEF(ISecurityCallContext, __uuidof(ISecurityCallContext));
_COM_SMARTPTR_TYPEDEF(IGetSecurityCallContext, __uuidof(IGetSecurityCallContext));
_COM_SMARTPTR_TYPEDEF(IObjectContext, __uuidof(IObjectContext));
_COM_SMARTPTR_TYPEDEF(IObjectContextActivity, __uuidof(IObjectContextActivity));
_COM_SMARTPTR_TYPEDEF(IObjectContextInfo, __uuidof(IObjectContextInfo));
_COM_SMARTPTR_TYPEDEF(IObjectConstruct, __uuidof(IObjectConstruct));
_COM_SMARTPTR_TYPEDEF(IObjectConstructString, __uuidof(IObjectConstructString));
_COM_SMARTPTR_TYPEDEF(IObjectControl, __uuidof(IObjectControl));
_COM_SMARTPTR_TYPEDEF(IPlaybackControl, __uuidof(IPlaybackControl));
_COM_SMARTPTR_TYPEDEF(ISecurityProperty, __uuidof(ISecurityProperty));
_COM_SMARTPTR_TYPEDEF(ObjectControl, __uuidof(ObjectControl));
_COM_SMARTPTR_TYPEDEF(IMTxAS, __uuidof(IMTxAS));
_COM_SMARTPTR_TYPEDEF(ObjectContext, __uuidof(ObjectContext));
_COM_SMARTPTR_TYPEDEF(SecurityProperty, __uuidof(SecurityProperty));
_COM_SMARTPTR_TYPEDEF(ContextInfo, __uuidof(ContextInfo));
_COM_SMARTPTR_TYPEDEF(ITransactionContext, __uuidof(ITransactionContext));
_COM_SMARTPTR_TYPEDEF(ITransactionContextEx, __uuidof(ITransactionContextEx));
_COM_SMARTPTR_TYPEDEF(ISharedProperty, __uuidof(ISharedProperty));
_COM_SMARTPTR_TYPEDEF(ISharedPropertyGroup, __uuidof(ISharedPropertyGroup));
_COM_SMARTPTR_TYPEDEF(ISharedPropertyGroupManager, __uuidof(ISharedPropertyGroupManager));
_COM_SMARTPTR_TYPEDEF(IReceiveAppData, __uuidof(IReceiveAppData));
_COM_SMARTPTR_TYPEDEF(IAppTrackerAdmin, __uuidof(IAppTrackerAdmin));
_COM_SMARTPTR_TYPEDEF(IGetAppData, __uuidof(IGetAppData));
_COM_SMARTPTR_TYPEDEF(IMtsEvents, __uuidof(IMtsEvents));
_COM_SMARTPTR_TYPEDEF(IMtsEventInfo, __uuidof(IMtsEventInfo));
_COM_SMARTPTR_TYPEDEF(IMTSLocator, __uuidof(IMTSLocator));
_COM_SMARTPTR_TYPEDEF(IMtsGrp, __uuidof(IMtsGrp));

//
// Type library items
//

struct __declspec(uuid("cafc8240-b441-11d1-b82b-0000f8757e2a"))
SecurityCertificate;
    // [ default ] interface ISecurityCertificateColl
    // interface IDispatch

struct __declspec(uuid("cafc823b-b441-11d1-b82b-0000f8757e2a"))
ISecurityCertificateColl : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        long * plCount ) = 0;
    virtual HRESULT __stdcall get_Item (
        BSTR name,
        VARIANT * pItem ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * ppEnum ) = 0;
};

struct __declspec(uuid("cafc8241-b441-11d1-b82b-0000f8757e2a"))
SecurityIdentity;
    // [ default ] interface ISecurityIdentityColl
    // interface IDispatch

struct __declspec(uuid("cafc823c-b441-11d1-b82b-0000f8757e2a"))
ISecurityIdentityColl : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        long * plCount ) = 0;
    virtual HRESULT __stdcall get_Item (
        BSTR name,
        VARIANT * pItem ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * ppEnum ) = 0;
};

struct __declspec(uuid("cafc8242-b441-11d1-b82b-0000f8757e2a"))
SecurityCallers;
    // [ default ] interface ISecurityCallersColl
    // interface IDispatch

struct __declspec(uuid("cafc823d-b441-11d1-b82b-0000f8757e2a"))
ISecurityCallersColl : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        long * plCount ) = 0;
    virtual HRESULT __stdcall get_Item (
        long lIndex,
        struct ISecurityIdentityColl * * pObj ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * ppEnum ) = 0;
};

struct __declspec(uuid("cafc8243-b441-11d1-b82b-0000f8757e2a"))
SecurityCallContext;
    // [ default ] interface ISecurityCallContext
    // interface IDispatch

struct __declspec(uuid("cafc823e-b441-11d1-b82b-0000f8757e2a"))
ISecurityCallContext : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        long * plCount ) = 0;
    virtual HRESULT __stdcall get_Item (
        BSTR name,
        VARIANT * pItem ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * ppEnum ) = 0;
    virtual HRESULT __stdcall IsCallerInRole (
        BSTR bstrRole,
        VARIANT_BOOL * pfInRole ) = 0;
    virtual HRESULT __stdcall IsSecurityEnabled (
        VARIANT_BOOL * pfIsEnabled ) = 0;
};

struct __declspec(uuid("cafc8244-b441-11d1-b82b-0000f8757e2a"))
GetSecurityCallContextAppObject;
    // [ default ] interface IGetSecurityCallContext
    // interface IDispatch

struct __declspec(uuid("cafc823f-b441-11d1-b82b-0000f8757e2a"))
IGetSecurityCallContext : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetSecurityCallContext (
        struct ISecurityCallContext * * ppObject ) = 0;
};

struct __declspec(uuid("bc427be0-1aa7-11d2-b293-00c04f8ef934"))
Dummy30040732;
    // [ default ] interface IObjectContext
    // interface IObjectContextActivity
    // interface IObjectContextInfo
    // interface IObjectConstruct
    // interface IObjectConstructString
    // interface IObjectControl
    // interface IPlaybackControl
    // interface ISecurityProperty

struct __declspec(uuid("51372ae0-cae7-11cf-be81-00aa00a2fa25"))
IObjectContext : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreateInstance (
        REFGUID rclsid,
        REFGUID riid,
        void * * ppv ) = 0;
    virtual HRESULT __stdcall SetComplete ( ) = 0;
    virtual HRESULT __stdcall SetAbort ( ) = 0;
    virtual HRESULT __stdcall EnableCommit ( ) = 0;
    virtual HRESULT __stdcall DisableCommit ( ) = 0;
    virtual BOOL __stdcall IsInTransaction ( ) = 0;
    virtual BOOL __stdcall IsSecurityEnabled ( ) = 0;
    virtual HRESULT __stdcall IsCallerInRole (
        BSTR bstrRole,
        BOOL * pfIsInRole ) = 0;
};

struct __declspec(uuid("51372afc-cae7-11cf-be81-00aa00a2fa25"))
IObjectContextActivity : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetActivityId (
        GUID * pGUID ) = 0;
};

struct __declspec(uuid("75b52ddb-e8ed-11d1-93ad-00aa00ba3258"))
IObjectContextInfo : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual BOOL __stdcall IsInTransaction ( ) = 0;
    virtual BOOL __stdcall IsSecurityEnabled ( ) = 0;
    virtual HRESULT __stdcall IsCallerInRole (
        BSTR bstrRole,
        BOOL * pfInRole ) = 0;
    virtual HRESULT __stdcall GetTransaction (
        IUnknown * * pptrans ) = 0;
    virtual HRESULT __stdcall GetTransactionId (
        GUID * pGUID ) = 0;
    virtual HRESULT __stdcall GetActivityId (
        GUID * pGUID ) = 0;
    virtual HRESULT __stdcall GetContextId (
        GUID * pGUID ) = 0;
};

struct __declspec(uuid("401f7922-d32c-11d1-939a-00aa00ba3258"))
IObjectConstruct : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall Construct (
        IUnknown * pUnkClassInfo ) = 0;
};

struct __declspec(uuid("04dfd095-e378-11d1-93a2-00aa00ba3258"))
IObjectConstructString : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetConstructString (
        BSTR * sConstructString ) = 0;
};

struct __declspec(uuid("51372aec-cae7-11cf-be81-00aa00a2fa25"))
IObjectControl : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall Activate ( ) = 0;
    virtual void __stdcall Deactivate ( ) = 0;
    virtual BOOL __stdcall CanBePooled ( ) = 0;
};

struct __declspec(uuid("51372afd-cae7-11cf-be81-00aa00a2fa25"))
IPlaybackControl : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall FinalClientRetry ( ) = 0;
    virtual HRESULT __stdcall FinalServerRetry ( ) = 0;
};

struct __declspec(uuid("51372aea-cae7-11cf-be81-00aa00a2fa25"))
ISecurityProperty : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetDirectCreatorSID (
        void * * pSID ) = 0;
    virtual HRESULT __stdcall GetOriginalCreatorSID (
        void * * pSID ) = 0;
    virtual HRESULT __stdcall GetDirectCallerSID (
        void * * pSID ) = 0;
    virtual HRESULT __stdcall GetOriginalCallerSID (
        void * * pSID ) = 0;
    virtual HRESULT __stdcall ReleaseSID (
        void * pSID ) = 0;
};

enum __MIDL___MIDL_itf_public_0000_0001
{
    mtsErrCtxAborted = -2147164158,
    mtsErrCtxAborting = -2147164157,
    mtsErrCtxNoContext = -2147164156,
    mtsErrCtxNotRegistered = -2147164155,
    mtsErrCtxSynchTimeout = -2147164154,
    mtsErrCtxOldReference = -2147164153,
    mtsErrCtxRoleNotFound = -2147164148,
    mtsErrCtxNoSecurity = -2147164147,
    mtsErrCtxWrongThread = -2147164146,
    mtsErrCtxTMNotAvailable = -2147164145
};

struct __declspec(uuid("7dc41850-0c31-11d0-8b79-00aa00b8a790"))
ObjectControl : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall Activate ( ) = 0;
    virtual HRESULT __stdcall Deactivate ( ) = 0;
    virtual HRESULT __stdcall CanBePooled (
        VARIANT_BOOL * pbPoolable ) = 0;
};

struct __declspec(uuid("71e38f91-7e88-11cf-9ede-0080c78b7f89"))
AppServer;
    // [ default ] interface IMTxAS
    // interface ISupportErrorInfo

struct __declspec(uuid("74c08641-cedb-11cf-8b49-00aa00b8a790"))
IMTxAS : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetObjectContext (
        struct ObjectContext * * ppContext ) = 0;
    virtual HRESULT __stdcall SafeRef (
        VARIANT vRefIn,
        VARIANT * pvRefOut ) = 0;
};

struct __declspec(uuid("74c08646-cedb-11cf-8b49-00aa00b8a790"))
ObjectContext : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreateInstance (
        BSTR bstrProgID,
        VARIANT * pObject ) = 0;
    virtual HRESULT __stdcall SetComplete ( ) = 0;
    virtual HRESULT __stdcall SetAbort ( ) = 0;
    virtual HRESULT __stdcall EnableCommit ( ) = 0;
    virtual HRESULT __stdcall DisableCommit ( ) = 0;
    virtual HRESULT __stdcall IsInTransaction (
        VARIANT_BOOL * pbIsInTx ) = 0;
    virtual HRESULT __stdcall IsSecurityEnabled (
        VARIANT_BOOL * pbIsEnabled ) = 0;
    virtual HRESULT __stdcall IsCallerInRole (
        BSTR bstrRole,
        VARIANT_BOOL * pbInRole ) = 0;
    virtual HRESULT __stdcall get_Count (
        long * plCount ) = 0;
    virtual HRESULT __stdcall get_Item (
        BSTR name,
        VARIANT * pItem ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * ppEnum ) = 0;
    virtual HRESULT __stdcall get_Security (
        struct SecurityProperty * * ppSecurityProperty ) = 0;
    virtual HRESULT __stdcall get_ContextInfo (
        struct ContextInfo * * ppContextInfo ) = 0;
};

struct __declspec(uuid("e74a7215-014d-11d1-a63c-00a0c911b4e0"))
SecurityProperty : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetDirectCallerName (
        BSTR * bstrUserName ) = 0;
    virtual HRESULT __stdcall GetDirectCreatorName (
        BSTR * bstrUserName ) = 0;
    virtual HRESULT __stdcall GetOriginalCallerName (
        BSTR * bstrUserName ) = 0;
    virtual HRESULT __stdcall GetOriginalCreatorName (
        BSTR * bstrUserName ) = 0;
};

struct __declspec(uuid("19a5a02c-0ac8-11d2-b286-00c04f8ef934"))
ContextInfo : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall IsInTransaction (
        VARIANT_BOOL * pbIsInTx ) = 0;
    virtual HRESULT __stdcall IsSecurityEnabled (
        VARIANT_BOOL * pbIsEnabled ) = 0;
    virtual HRESULT __stdcall IsCallerInRole (
        BSTR bstrRole,
        VARIANT_BOOL * pbInRole ) = 0;
    virtual HRESULT __stdcall GetTransaction (
        IUnknown * * ppTx ) = 0;
    virtual HRESULT __stdcall GetTransactionId (
        BSTR * pbstrTxId ) = 0;
    virtual HRESULT __stdcall GetActivityId (
        BSTR * pbstrActivityId ) = 0;
    virtual HRESULT __stdcall GetContextId (
        BSTR * pbstrCtxId ) = 0;
};

struct __declspec(uuid("7999fc25-d3c6-11cf-acab-00a024a55aef"))
TransactionContext;
    // [ default ] interface ITransactionContext

struct __declspec(uuid("7999fc21-d3c6-11cf-acab-00a024a55aef"))
ITransactionContext : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreateInstance (
        BSTR pszProgId,
        VARIANT * pObject ) = 0;
    virtual HRESULT __stdcall Commit ( ) = 0;
    virtual HRESULT __stdcall Abort ( ) = 0;
};

struct __declspec(uuid("5cb66670-d3d4-11cf-acab-00a024a55aef"))
TransactionContextEx;
    // [ default ] interface ITransactionContextEx

struct __declspec(uuid("7999fc22-d3c6-11cf-acab-00a024a55aef"))
ITransactionContextEx : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreateInstance (
        REFGUID rclsid,
        REFGUID riid,
        void * * pObject ) = 0;
    virtual HRESULT __stdcall Commit ( ) = 0;
    virtual HRESULT __stdcall Abort ( ) = 0;
};

struct __declspec(uuid("2a005c05-a5de-11cf-9e66-00aa00a3f464"))
SharedProperty;
    // [ default ] interface ISharedProperty

struct __declspec(uuid("2a005c01-a5de-11cf-9e66-00aa00a3f464"))
ISharedProperty : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Value (
        VARIANT * pVal ) = 0;
    virtual HRESULT __stdcall put_Value (
        VARIANT pVal ) = 0;
};

struct __declspec(uuid("2a005c0b-a5de-11cf-9e66-00aa00a3f464"))
SharedPropertyGroup;
    // [ default ] interface ISharedPropertyGroup

struct __declspec(uuid("2a005c07-a5de-11cf-9e66-00aa00a3f464"))
ISharedPropertyGroup : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreatePropertyByPosition (
        int Index,
        VARIANT_BOOL * fExists,
        struct ISharedProperty * * ppProp ) = 0;
    virtual HRESULT __stdcall get_PropertyByPosition (
        int Index,
        struct ISharedProperty * * ppProperty ) = 0;
    virtual HRESULT __stdcall CreateProperty (
        BSTR name,
        VARIANT_BOOL * fExists,
        struct ISharedProperty * * ppProp ) = 0;
    virtual HRESULT __stdcall get_Property (
        BSTR name,
        struct ISharedProperty * * ppProperty ) = 0;
};

struct __declspec(uuid("2a005c11-a5de-11cf-9e66-00aa00a3f464"))
SharedPropertyGroupManager;
    // [ default ] interface ISharedPropertyGroupManager

struct __declspec(uuid("2a005c0d-a5de-11cf-9e66-00aa00a3f464"))
ISharedPropertyGroupManager : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall CreatePropertyGroup (
        BSTR name,
        long * dwIsoMode,
        long * dwRelMode,
        VARIANT_BOOL * fExists,
        struct ISharedPropertyGroup * * ppGroup ) = 0;
    virtual HRESULT __stdcall get_Group (
        BSTR name,
        struct ISharedPropertyGroup * * ppGroup ) = 0;
    virtual HRESULT __stdcall get__NewEnum (
        IUnknown * * retval ) = 0;
};

enum __MIDL___MIDL_itf_public_0000_0002
{
    LockSetGet = 0,
    LockMethod = 1
};

enum __MIDL___MIDL_itf_public_0000_0003
{
    Standard = 0,
    Process = 1
};

struct __declspec(uuid("72516db0-be9a-11d1-861f-0080c729264d"))
TrackerServer;
    // [ default ] interface IReceiveAppData
    // interface IGetAppData

struct __declspec(uuid("413dafb0-bcf4-11d1-861d-0080c729264d"))
IReceiveAppData : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall Register (
        LPWSTR pAppGuid,
        struct IAppTrackerAdmin * tracker,
        unsigned long * pidApp,
        unsigned long * pPushRate ) = 0;
    virtual HRESULT __stdcall PushAppData (
        unsigned long idApp,
        struct CAppStatistics appData,
        unsigned long nCLSIDs,
        struct CCLSIDData * clsids ) = 0;
    virtual HRESULT __stdcall Unregister (
        unsigned long idApp ) = 0;
};

struct __declspec(uuid("ea61e3c1-7c62-11cf-be3f-00aa00a2fa25"))
IAppTrackerAdmin : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall SetPushRate (
        unsigned long PushRate ) = 0;
    virtual HRESULT __stdcall TrackerServerShutDown ( ) = 0;
    virtual HRESULT __stdcall Ping ( ) = 0;
};

struct CAppStatistics
{
    unsigned long m_cTotalCalls;
    unsigned long m_cTotalInstances;
    unsigned long m_cTotalClasses;
    unsigned long m_cCallsPerSecond;
};

struct CCLSIDData
{
    GUID m_clsid;
    unsigned long m_cReferences;
    unsigned long m_cBound;
    unsigned long m_cPooled;
    unsigned long m_cInCall;
    unsigned long m_dwRespTime;
    unsigned long m_cCallsCompleted;
    unsigned long m_cCallsFailed;
};

struct __declspec(uuid("b60040e0-bcf3-11d1-861d-0080c729264d"))
IGetAppData : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall SetPushRate (
        unsigned long dwPushRate ) = 0;
    virtual HRESULT __stdcall GetApps (
        unsigned long * nApps,
        struct CAppData * * aAppData ) = 0;
    virtual HRESULT __stdcall GetAppData (
        unsigned long idApp,
        unsigned long * nCLSIDs,
        struct CCLSIDData * * aAppData ) = 0;
    virtual HRESULT __stdcall GetCLSIDData (
        unsigned long idApp,
        GUID clsid,
        struct CCLSIDData * * ppAppData ) = 0;
    virtual HRESULT __stdcall Shutdown ( ) = 0;
};

struct CAppData
{
    unsigned long m_idApp;
    short m_szAppGuid[40];
    struct CAppStatistics m_AppStatistics;
};

struct __declspec(uuid("bacedf4e-74ab-11d0-b162-00aa00ba3258"))
CoMTSEvents;
    // [ default ] interface IMtsEvents
    // interface IMtsEventInfo

struct __declspec(uuid("bacedf4d-74ab-11d0-b162-00aa00ba3258"))
IMtsEvents : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_PackageName (
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall get_PackageGuid (
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall PostEvent (
        VARIANT * vEvent ) = 0;
    virtual HRESULT __stdcall get_FireEvents (
        VARIANT_BOOL * pVal ) = 0;
    virtual HRESULT __stdcall GetProcessID (
        long * id ) = 0;
};

struct __declspec(uuid("d56c3dc1-8482-11d0-b170-00aa00ba3258"))
IMtsEventInfo : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Names (
        IUnknown * * pUnk ) = 0;
    virtual HRESULT __stdcall get_DisplayName (
        BSTR * sDisplayName ) = 0;
    virtual HRESULT __stdcall get_EventID (
        BSTR * sGuidEventID ) = 0;
    virtual HRESULT __stdcall get_Count (
        long * lCount ) = 0;
    virtual HRESULT __stdcall get_Value (
        BSTR sKey,
        VARIANT * pVal ) = 0;
};

struct __declspec(uuid("d19b8bfe-7f88-11d0-b16e-00aa00ba3258"))
CoMTSLocator;
    // [ default ] interface IMTSLocator

struct __declspec(uuid("d19b8bfd-7f88-11d0-b16e-00aa00ba3258"))
IMTSLocator : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall GetEventDispatcher (
        IUnknown * * pUnk ) = 0;
};

struct __declspec(uuid("4b2e958d-0393-11d1-b1ab-00aa00ba3258"))
MtsGrp;
    // [ default ] interface IMtsGrp

struct __declspec(uuid("4b2e958c-0393-11d1-b1ab-00aa00ba3258"))
IMtsGrp : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_Count (
        long * pVal ) = 0;
    virtual HRESULT __stdcall Item (
        long lIndex,
        IUnknown * * ppUnkDispatcher ) = 0;
    virtual HRESULT __stdcall Refresh ( ) = 0;
};

//
// Named GUID constants initializations
//

extern "C" const GUID __declspec(selectany) LIBID_COMSVCSLib =
    {0x8b297b5f,0x86e2,0x11d1,{0x99,0x7f,0x00,0xc0,0x4f,0xbb,0xb3,0x45}};
extern "C" const GUID __declspec(selectany) CLSID_SecurityCertificate =
    {0xcafc8240,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) IID_ISecurityCertificateColl =
    {0xcafc823b,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_SecurityIdentity =
    {0xcafc8241,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) IID_ISecurityIdentityColl =
    {0xcafc823c,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_SecurityCallers =
    {0xcafc8242,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) IID_ISecurityCallersColl =
    {0xcafc823d,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_SecurityCallContext =
    {0xcafc8243,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) IID_ISecurityCallContext =
    {0xcafc823e,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_GetSecurityCallContextAppObject =
    {0xcafc8244,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) IID_IGetSecurityCallContext =
    {0xcafc823f,0xb441,0x11d1,{0xb8,0x2b,0x00,0x00,0xf8,0x75,0x7e,0x2a}};
extern "C" const GUID __declspec(selectany) CLSID_Dummy30040732 =
    {0xbc427be0,0x1aa7,0x11d2,{0xb2,0x93,0x00,0xc0,0x4f,0x8e,0xf9,0x34}};
extern "C" const GUID __declspec(selectany) IID_IObjectContext =
    {0x51372ae0,0xcae7,0x11cf,{0xbe,0x81,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_IObjectContextActivity =
    {0x51372afc,0xcae7,0x11cf,{0xbe,0x81,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_IObjectContextInfo =
    {0x75b52ddb,0xe8ed,0x11d1,{0x93,0xad,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IObjectConstruct =
    {0x401f7922,0xd32c,0x11d1,{0x93,0x9a,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IObjectConstructString =
    {0x04dfd095,0xe378,0x11d1,{0x93,0xa2,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IObjectControl =
    {0x51372aec,0xcae7,0x11cf,{0xbe,0x81,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_IPlaybackControl =
    {0x51372afd,0xcae7,0x11cf,{0xbe,0x81,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_ISecurityProperty =
    {0x51372aea,0xcae7,0x11cf,{0xbe,0x81,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_ObjectControl =
    {0x7dc41850,0x0c31,0x11d0,{0x8b,0x79,0x00,0xaa,0x00,0xb8,0xa7,0x90}};
extern "C" const GUID __declspec(selectany) CLSID_AppServer =
    {0x71e38f91,0x7e88,0x11cf,{0x9e,0xde,0x00,0x80,0xc7,0x8b,0x7f,0x89}};
extern "C" const GUID __declspec(selectany) IID_IMTxAS =
    {0x74c08641,0xcedb,0x11cf,{0x8b,0x49,0x00,0xaa,0x00,0xb8,0xa7,0x90}};
extern "C" const GUID __declspec(selectany) IID_ObjectContext =
    {0x74c08646,0xcedb,0x11cf,{0x8b,0x49,0x00,0xaa,0x00,0xb8,0xa7,0x90}};
extern "C" const GUID __declspec(selectany) IID_SecurityProperty =
    {0xe74a7215,0x014d,0x11d1,{0xa6,0x3c,0x00,0xa0,0xc9,0x11,0xb4,0xe0}};
extern "C" const GUID __declspec(selectany) IID_ContextInfo =
    {0x19a5a02c,0x0ac8,0x11d2,{0xb2,0x86,0x00,0xc0,0x4f,0x8e,0xf9,0x34}};
extern "C" const GUID __declspec(selectany) CLSID_TransactionContext =
    {0x7999fc25,0xd3c6,0x11cf,{0xac,0xab,0x00,0xa0,0x24,0xa5,0x5a,0xef}};
extern "C" const GUID __declspec(selectany) IID_ITransactionContext =
    {0x7999fc21,0xd3c6,0x11cf,{0xac,0xab,0x00,0xa0,0x24,0xa5,0x5a,0xef}};
extern "C" const GUID __declspec(selectany) CLSID_TransactionContextEx =
    {0x5cb66670,0xd3d4,0x11cf,{0xac,0xab,0x00,0xa0,0x24,0xa5,0x5a,0xef}};
extern "C" const GUID __declspec(selectany) IID_ITransactionContextEx =
    {0x7999fc22,0xd3c6,0x11cf,{0xac,0xab,0x00,0xa0,0x24,0xa5,0x5a,0xef}};
extern "C" const GUID __declspec(selectany) CLSID_SharedProperty =
    {0x2a005c05,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) IID_ISharedProperty =
    {0x2a005c01,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) CLSID_SharedPropertyGroup =
    {0x2a005c0b,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) IID_ISharedPropertyGroup =
    {0x2a005c07,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) CLSID_SharedPropertyGroupManager =
    {0x2a005c11,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) IID_ISharedPropertyGroupManager =
    {0x2a005c0d,0xa5de,0x11cf,{0x9e,0x66,0x00,0xaa,0x00,0xa3,0xf4,0x64}};
extern "C" const GUID __declspec(selectany) CLSID_TrackerServer =
    {0x72516db0,0xbe9a,0x11d1,{0x86,0x1f,0x00,0x80,0xc7,0x29,0x26,0x4d}};
extern "C" const GUID __declspec(selectany) IID_IReceiveAppData =
    {0x413dafb0,0xbcf4,0x11d1,{0x86,0x1d,0x00,0x80,0xc7,0x29,0x26,0x4d}};
extern "C" const GUID __declspec(selectany) IID_IAppTrackerAdmin =
    {0xea61e3c1,0x7c62,0x11cf,{0xbe,0x3f,0x00,0xaa,0x00,0xa2,0xfa,0x25}};
extern "C" const GUID __declspec(selectany) IID_IGetAppData =
    {0xb60040e0,0xbcf3,0x11d1,{0x86,0x1d,0x00,0x80,0xc7,0x29,0x26,0x4d}};
extern "C" const GUID __declspec(selectany) CLSID_CoMTSEvents =
    {0xbacedf4e,0x74ab,0x11d0,{0xb1,0x62,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IMtsEvents =
    {0xbacedf4d,0x74ab,0x11d0,{0xb1,0x62,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IMtsEventInfo =
    {0xd56c3dc1,0x8482,0x11d0,{0xb1,0x70,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) CLSID_CoMTSLocator =
    {0xd19b8bfe,0x7f88,0x11d0,{0xb1,0x6e,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IMTSLocator =
    {0xd19b8bfd,0x7f88,0x11d0,{0xb1,0x6e,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) CLSID_MtsGrp =
    {0x4b2e958d,0x0393,0x11d1,{0xb1,0xab,0x00,0xaa,0x00,0xba,0x32,0x58}};
extern "C" const GUID __declspec(selectany) IID_IMtsGrp =
    {0x4b2e958c,0x0393,0x11d1,{0xb1,0xab,0x00,0xaa,0x00,0xba,0x32,0x58}};


#pragma pack(pop)
