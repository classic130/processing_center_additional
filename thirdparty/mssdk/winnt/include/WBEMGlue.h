//=================================================================
//
// WBEMGLUE.H - Implementation of WBEM Glue classes
//
// Copyright 1997, 1998 Microsoft Corporation
//
//=================================================================

#if _MSC_VER > 1000
#pragma once
#endif

#undef PURE
#define PURE {return (ULONG)E_NOTIMPL;}
typedef LPVOID * PPVOID;

#include <wbemidl.h>
#include <map>
#include <provider.h>

#ifndef _WbemGlue_H_Included
#define _WbemGlue_H_Included

#define	DEFAULT_NAMESPACE_WCHAR	L"Root\\CimV2"
#define	DEFAULT_NAMESPACE		_T("Root\\CimV2")
#define STATICINIT_MUTEX		_T("CWBEMPROVIDERGLUE")

typedef std::map<CHString, DWORD> STRING2DWORD;

class POLARITY CWbemProviderGlue : public IWbemServices, public IWbemProviderInit
{

 public:
	// Public Static functions
	// these are for use by implementors of Framework based providers

	// "short circuits" for accessing other providers
	static HRESULT WINAPI GetAllInstances( LPCSTR pszProviderName, TRefPointerCollection<CInstance>* pList, LPCSTR pszNamespace, MethodContext*  pMethodContext );
	static HRESULT WINAPI GetAllInstancesAsynch( LPCSTR pszProviderName, Provider* pRequester, LPProviderInstanceCallback pCallback, LPCSTR pszNamespace, MethodContext*  pMethodContext, void* pUserData );
	static HRESULT WINAPI GetAllDerivedInstances( LPCSTR pszBaseClassName, 
									     TRefPointerCollection<CInstance>* pList, 
										 MethodContext*  pMethodContext, 
										 LPCSTR pszNamespace = NULL);
	static HRESULT WINAPI GetInstanceByPath( LPCSTR pszObjectPath, CInstance** ppInstance, MethodContext* pMethodContext = NULL );
	static HRESULT WINAPI GetInstancesByQuery( LPCSTR query, TRefPointerCollection<CInstance>* pList, MethodContext*  pMethodContext,	LPCSTR	pszNamespace = NULL);
	static HRESULT WINAPI GetEmptyInstance( LPCSTR pszProviderName, CInstance** ppInstance, LPCSTR pszNamespace = NULL);
	static HRESULT WINAPI FillInstance( CInstance* ppInstance, LPCSTR pszNamespace = NULL );

	// determine whether one class is derived from another
	static bool  WINAPI IsDerivedFrom(LPCSTR pszBaseClassName, LPCSTR pszDerivedClassName, MethodContext* pMethodContext, LPCSTR pszNamespace = NULL );

	// logging in and out of framework
	// each framework based DLL must log in and out with these functions
	// preferably in DllMain and DllCanUnloadNow
	static BOOL WINAPI FrameworkLoginDLL(const CHString& name);
	static BOOL WINAPI FrameworkLogoffDLL(const CHString& name);

	////////////////////////////////////////////////////////////////////////////////////
	// note: the following public functions are necessary to allow COM communication  //
	//		 with CIMOM.  Provider Implementors will not need to call these.          //
	////////////////////////////////////////////////////////////////////////////////////

 #ifndef NO_BASEINTERFACE_FUNCS

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;
    STDMETHOD_(ULONG, AddRef)(THIS) ;
    STDMETHOD_(ULONG, Release)(THIS) ;
#endif

   virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ LPWSTR pszUser,
            /* [in] */ LONG lFlags,
            /* [in] */ LPWSTR pszNamespace,
            /* [in] */ LPWSTR pszLocale,
            /* [in] */ IWbemServices __RPC_FAR *pNamespace,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemProviderInitSink __RPC_FAR *pInitSink);


    STDMETHOD(CreateInstanceEnumAsync)(THIS_
            /* [in] */ BSTR Class,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
        );
    
    STDMETHOD(GetObjectAsync)( THIS_
            BSTR ObjectPath, 
            long lFlags, 
            IWbemContext __RPC_FAR *pCtx, 
            IWbemObjectSink __RPC_FAR *pResponseHandler);
    
    STDMETHOD(ExecQueryAsync)(THIS_
            /* [in] */ BSTR QueryLanguage,
            /* [in] */ BSTR Query,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
    );
    
    STDMETHOD(PutInstanceAsync)( THIS_
            /* [in] */ IWbemClassObject __RPC_FAR *pInst,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
    );
    
    STDMETHOD(DeleteInstanceAsync)(
            /* [in] */ BSTR ObjectPath,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
    );

    STDMETHOD(ExecMethodAsync)(BSTR, BSTR, long, IWbemContext*, IWbemClassObject*,
        IWbemObjectSink*);


 // Unsupported service methods
 // ===========================

    STDMETHOD(OpenNamespace)(THIS_
            BSTR Namespace, 
            long lFlags,  
            IWbemContext __RPC_FAR *pCtx,
            IWbemServices __RPC_FAR *__RPC_FAR *ppWorkingNamespace, 
            IWbemCallResult __RPC_FAR *__RPC_FAR *ppResult)
	{ return E_NOTIMPL; }
    

    STDMETHOD(PutClass)(IWbemClassObject __RPC_FAR *pObject, long lFlags, IWbemContext __RPC_FAR *pCtx, IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
         {return E_NOTIMPL;}

    STDMETHOD(PutClassAsync)( 
            /* [in] */ IWbemClassObject __RPC_FAR *pObject,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
    )
         {return E_NOTIMPL;}

    STDMETHOD(DeleteClass)(  
            /* [in] */ BSTR Class,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
         {return E_NOTIMPL;}

    STDMETHOD(DeleteClassAsync)( 
            /* [in] */ BSTR Class,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
         {return E_NOTIMPL;}

    STDMETHOD(CreateClassEnum)(
            /* [in] */ BSTR Superclass,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum
        )
         {return E_NOTIMPL;}

    STDMETHOD(CreateClassEnumAsync)(
            /* [in] */ BSTR Superclass,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler
        )
         {return E_NOTIMPL;}



    STDMETHOD(PutInstance)(
            /* [in] */ IWbemClassObject __RPC_FAR *pInst,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult
        )
         {return E_NOTIMPL;}


    STDMETHOD(DeleteInstance)(
            /* [in] */ BSTR ObjectPath,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [unique][in][out] */ IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult
    )
         {return E_NOTIMPL;}

    STDMETHOD(CancelAsyncRequest)(THIS_ long lAsyncRequestHandle)
         {return E_NOTIMPL;}

    STDMETHOD(CancelAsyncCall)(IWbemObjectSink __RPC_FAR *pSink)
         {return E_NOTIMPL;}

    STDMETHOD(CreateInstanceEnum)(
            /* [in] */ BSTR Class,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum
    )
         {return E_NOTIMPL;}
  
    STDMETHOD(ExecQuery)(
            /* [in] */ BSTR QueryLanguage,
            /* [in] */ BSTR Query,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum
    )
         {return E_NOTIMPL;}

    STDMETHOD(QueryObjectSink)(long lFlags, IWbemObjectSink __RPC_FAR *__RPC_FAR *ppResponseHandler)
         {return E_NOTIMPL;}


    STDMETHOD(GetObject)( BSTR ObjectPath, long lFlags, IWbemContext __RPC_FAR *pCtx, IWbemClassObject __RPC_FAR *__RPC_FAR *ppObject, IWbemCallResult __RPC_FAR *__RPC_FAR *ppCallResult)
         {return E_NOTIMPL;}

    STDMETHOD(ExecNotificationQuery)( 
            /* [in] */ BSTR QueryLanguage,
            /* [in] */ BSTR Query,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [out] */ IEnumWbemClassObject __RPC_FAR *__RPC_FAR *ppEnum)
       {return E_NOTIMPL;}
        
        
    STDMETHOD(ExecNotificationQueryAsync)( 
            /* [in] */ BSTR QueryLanguage,
            /* [in] */ BSTR Query,
            /* [in] */ long lFlags,
            /* [in] */ IWbemContext __RPC_FAR *pCtx,
            /* [in] */ IWbemObjectSink __RPC_FAR *pResponseHandler)
       {return E_NOTIMPL;}
        
    STDMETHOD(ExecMethod)(BSTR, BSTR, long, IWbemContext*, IWbemClassObject*,
        IWbemClassObject**, IWbemCallResult**)
       {return E_NOTIMPL;}

	CWbemProviderGlue( );
	~CWbemProviderGlue(); // Destructor

	// used by the provider base class - you probably will never need to call this directly
	static IWbemServices* WINAPI GetNamespaceConnection( BSTR NameSpace );
	// each provider class must log in and out with these in their constructors and destructors
	// this is done for you in the base class
	static void WINAPI FrameworkLogin( const CHString& name, Provider* pProvider, LPCSTR pszNameSpace );
	static void WINAPI FrameworkLogoff( const CHString& name, LPCSTR pszNameSpace );

	static void WINAPI IncrementObjectCount(void);
	static void WINAPI DecrementObjectCount(void);
	
 private:
	static HRESULT WINAPI GetInstancesFromCIMOM(const CHString& strProviderName, 
										 TRefPointerCollection<CInstance>*	pList,
										 IWbemServices*                     piService,
										 MethodContext*                      pMethodContext);
	static HRESULT WINAPI GetInstanceFromCIMOM(	LPCSTR			pszObjectPath,
										LPCSTR			pszNameSpace,
										MethodContext*	pMethodContext,
										CInstance**		ppInstance );	

	void FlushAll(void);

	//static IWbemServices* ConnectToNamespace( BSTR NameSpace );

	static IWbemServices* WINAPI SearchMapForNamespace( BSTR NameSpace );
	static IWbemServices* WINAPI AddNamespaceToMap( BSTR NameSpace, IWbemServices* pWbemServices );
	static void WINAPI ClearNamespaceMap( void );

	static Provider* WINAPI SearchMapForProvider( const CHString& ProviderName, const CHString& strNamespace );
	static Provider* WINAPI AddProviderToMap( const CHString& ProviderName, const CHString& strNamespace, Provider* pProvider );

	static void WINAPI LockProviderMap( void );
	static void WINAPI UnlockProviderMap( void );
	static void WINAPI LockNamespaceMap( void );
	static void WINAPI UnlockNamespaceMap( void );

	static void WINAPI Init( void );
	static void WINAPI UnInit( void );
	static HANDLE WINAPI GetStaticMutex( void );

	static void WINAPI GetComputerName( CHString& strComputerName );
	
	static long	m_lRefCount; 
	static long	s_lInstances; // instances of CWbemGlue
	CHString	m_strNamespace;

	static long	s_lObjects; // number of objects out there - class factories, mostly.
	static STRING2DWORD	s_providersmap;
	static STRING2DWORD	s_wbemservicesmap;
	static CRITICAL_SECTION	s_csProviderMap;
	static CRITICAL_SECTION	s_csNamespaceMap;
};

inline void CWbemProviderGlue::LockProviderMap( void )
{
	EnterCriticalSection( &s_csProviderMap );
}

inline void CWbemProviderGlue::UnlockProviderMap( void )
{
	LeaveCriticalSection( &s_csProviderMap );
}

inline void CWbemProviderGlue::LockNamespaceMap( void )
{
	EnterCriticalSection( &s_csNamespaceMap );
}

inline void CWbemProviderGlue::UnlockNamespaceMap( void )
{
	LeaveCriticalSection( &s_csNamespaceMap );
}
        
class POLARITY CWbemGlueFactory : public IClassFactory
{
 protected:
	long		m_lRefCount;

 public:
        CWbemGlueFactory(void);
        ~CWbemGlueFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CWbemGlueFactory *PCWbemGlueFactory;

#endif
