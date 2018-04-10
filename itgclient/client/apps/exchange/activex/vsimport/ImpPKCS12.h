// ImpPKCS12.h : Declaration of the CImpPKCS12

#ifndef __IMPPKCS12_H_
#define __IMPPKCS12_H_

#include "resource.h"       // main symbols
#include "Mdefs.h"


typedef struct _CCERT_CONTEXT_LIST {
	PCCERT_CONTEXT pCertContext ;
	struct _CCERT_CONTEXT_LIST *nextCertContext ;
} CCERT_CONTEXT_LIST, *PCCERT_CONTEXT_LIST ;


#if 0
typedef		struct _DIGESTALGORITHMIDENTIFIER {
	DWORD			length ;
	PBYTE			palgorithmIdentifier ;	// OBJECT IDENTIFIER

} DIGESTALGORITHMIDENTIFIER, *PDIGESTALGORITHMIDENTIFIER ;

typedef		struct	_DIGESTINFO {
	DWORD			length ;
	PDIGESTALGORITHMIDENTIFIER	pdigestAlgorithm ;
	PBYTE			pdigest ;	// OCTET STRING
} DIGESTINFO, *PDIGESTINFO ;

typedef		struct	_MACDATA {
	DWORD			length ;
	PDIGESTINFO		psafeMac ;
	PBYTE			pmacSalt ;	// OCTET STRING
} MACDATA, *PMACDATA ;

typedef		struct _PCONTENTTYPE {
	DWORD			length ;
	PBYTE			palgorithmIdentifier ; // // OBJECT IDENTIFIER
} CONTENTTYPE, *PCONTENTTYPE ;

typedef		struct	_CONTENTINFO {
	DWORD			length ;
	PCONTENTTYPE	pcontenttype ;
	PBYTE			pcontent ;	// [0] EXPLICIT ANY DEFINED BY contentType OPTIONAL
} CONTENTINFO, *PCONTENTINFO ;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImpPKCS12
class ATL_NO_VTABLE CImpPKCS12 : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CImpPKCS12, &CLSID_ImpPKCS12>,
	public CComControl<CImpPKCS12>,
	public IDispatchImpl<IImpPKCS12, &IID_IImpPKCS12, &LIBID_IMPORTPKCS12Lib>,
	public IProvideClassInfo2Impl<&CLSID_ImpPKCS12, NULL, &LIBID_IMPORTPKCS12Lib>,
	public IPersistStreamInitImpl<CImpPKCS12>,
	public IPersistStorageImpl<CImpPKCS12>,
	public IQuickActivateImpl<CImpPKCS12>,
	public IOleControlImpl<CImpPKCS12>,
	public IOleObjectImpl<CImpPKCS12>,
	public IOleInPlaceActiveObjectImpl<CImpPKCS12>,
	public IViewObjectExImpl<CImpPKCS12>,
	public IOleInPlaceObjectWindowlessImpl<CImpPKCS12>,
	public IDataObjectImpl<CImpPKCS12>,
	public ISupportErrorInfo,
	public ISpecifyPropertyPagesImpl<CImpPKCS12>,
	public IObjectSafetyImpl<CImpPKCS12, INTERFACESAFE_FOR_UNTRUSTED_CALLER>
{
public:
	CImpPKCS12() ;
	~CImpPKCS12() ;

DECLARE_REGISTRY_RESOURCEID(IDR_IMPPKCS12)
DECLARE_NOT_AGGREGATABLE(CImpPKCS12)

BEGIN_COM_MAP(CImpPKCS12)
	COM_INTERFACE_ENTRY(IImpPKCS12)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IMPL(IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject2, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IViewObject, IViewObjectEx)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleInPlaceObject, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL_IID(IID_IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY_IMPL(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY_IMPL(IOleControl)
	COM_INTERFACE_ENTRY_IMPL(IOleObject)
	COM_INTERFACE_ENTRY_IMPL(IQuickActivate)
	COM_INTERFACE_ENTRY_IMPL(IPersistStorage)
	COM_INTERFACE_ENTRY_IMPL(IPersistStreamInit)
	COM_INTERFACE_ENTRY_IMPL(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY_IMPL(IDataObject)
	COM_INTERFACE_ENTRY(IObjectSafety)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

BEGIN_PROPERTY_MAP(CImpPKCS12)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	PROP_PAGE(CLSID_StockColorPage)
END_PROPERTY_MAP()


BEGIN_MSG_MAP(CImpPKCS12)
	MESSAGE_HANDLER(WM_PAINT, OnPaint)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
END_MSG_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IViewObjectEx
	STDMETHOD(GetViewStatus)(DWORD* pdwStatus)
	{
		ATLTRACE(_T("IViewObjectExImpl::GetViewStatus\n"));
		*pdwStatus = VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE;
		return S_OK;
	}

// IImpPKCS12
public:
	STDMETHOD(get_KeyUserProtected)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_KeyUserProtected)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_ProviderName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ProviderName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_KeyExportable)(/*[out, retval]*/ BOOL *pVal);
	STDMETHOD(put_KeyExportable)(/*[in]*/ BOOL newVal);
	STDMETHOD(Import)(VARIANT *i_pvarPKCS12, VARIANT *i_pvarPKCS7, VARIANT *o_pvarStatus, VARIANT * o_pvarErrorCode, VARIANT * o_pvarErrorCodeString);
	HRESULT OnDraw(ATL_DRAWINFO& di);

private :
	void	_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString) ;
	void	_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize) ;
	void	_Base64Encode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize) ;
	LPSTR	_WideToMultiString(BSTR szwcInputString) ;
	BSTR	_MultiToWideString(LPSTR szInputString) ;
	BOOL	_GetASNInfo(PBYTE input, BYTE *type, DWORD *length, DWORD *numberOfLengthBytes) ;
	BOOL	_myCryptDecodeObject(LPSTR szOID, PCRYPT_MYDER_BLOB pMyDERBlob, PBYTE pOutputStruct) ;
	PCCERT_CONTEXT_LIST _EnumCerts(HCERTSTORE hCertStore) ;
	void	_DumpAllCertProperties() ;

	HCRYPTPROV		m_hCryptProv ;
	BYTE			*m_pszContainer ;
	BOOL			m_bExportable ;
	BOOL			m_bUserProtected ;  // flag to allow user to protect private key
	HCERTSTORE		m_hMyCertStore ;	// Handle to MY Cert store.
	BOOL			m_bMyCertStoreOpen ; // Tells if the MY cert store was opened successfully
	HCERTSTORE		m_hCACertStore ;	// Handle to CA Cert store.
	BOOL			m_bCACertStoreOpen ; // Tells if the CA cert store was opened successfully
	BSTR			m_bstrErrorCodeString ; // Contains the error string corresponding to the error code
	DWORD			m_dwErrorCode ;		 // Contains the error code
	PCHAR			m_szCryptographicProvider ;
};

#endif //__IMPPKCS12_H_
