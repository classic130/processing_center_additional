// SignAttributes.h : Declaration of the CSignAttributes

#ifndef __SIGNATTRIBUTES_H_
#define __SIGNATTRIBUTES_H_

#ifndef CERT_FIND_EXISTING
#define CERT_COMPARE_EXISTING       13
#define CERT_FIND_EXISTING      (CERT_COMPARE_EXISTING << CERT_COMPARE_SHIFT)
#define CERT_FIND_EXISTING      (CERT_COMPARE_EXISTING << CERT_COMPARE_SHIFT)
#endif

#define		MY_ENCODING_TYPE	(X509_ASN_ENCODING | PKCS_7_ASN_ENCODING)

typedef struct _CCERT_CONTEXT_LIST {
	PCCERT_CONTEXT pCertContext ;
	struct _CCERT_CONTEXT_LIST *nextCertContext ;
} CCERT_CONTEXT_LIST, *PCCERT_CONTEXT_LIST ;

#include "resource.h"       // main symbols

// includes 
#include <atlctl.h> 
#include <comdef.h>

/////////////////////////////////////////////////////////////////////////////
// CSignAttributes
class ATL_NO_VTABLE CSignAttributes : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSignAttributes, &CLSID_SignAttributes>,
	public CComControl<CSignAttributes>,  // Added for HostName 
	public IOleControlImpl<CSignAttributes >, // Added for HostName 
	public IOleObjectImpl<CSignAttributes>, // Added for HostName 
	public IOleInPlaceActiveObjectImpl<CSignAttributes>,// Added for HostName
	public IViewObjectExImpl<CSignAttributes>,// Added for HostName
	public IOleInPlaceObjectWindowlessImpl<CSignAttributes>,// Added for HostName
	public IObjectWithSiteImpl<CSignAttributes>,
	public ISupportErrorInfo,
	public IDispatchImpl<ISignAttributes, &IID_ISignAttributes, &LIBID_SIGNATRBLib>
{
public:

DECLARE_REGISTRY_RESOURCEID(IDR_SIGNATTRIBUTES)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSignAttributes)
	COM_INTERFACE_ENTRY(ISignAttributes)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IOleControl) // Added for HostName 
	COM_INTERFACE_ENTRY(IOleObject)  // Added for HostName 
	COM_INTERFACE_ENTRY(IViewObjectEx) // Added for HostName
	COM_INTERFACE_ENTRY(IViewObject2) // Added for HostName
	COM_INTERFACE_ENTRY(IViewObject)// Added for HostName
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless) // Added for HostName
	COM_INTERFACE_ENTRY(IOleInPlaceObject) // Added for HostName
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)// Added for HostName
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject) // Added for HostName 
END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ISignAttributes
public:
	STDMETHOD(get_SMIMECapabilityBlob)(USHORT *cbSMIMECapabilityBlobSize, /*[out, retval]*/ BYTE *pVal);
	STDMETHOD(get_AuthEncUserSMIMECertificate)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(get_HostName)(/*[out, retval]*/ BSTR *pVal);
//	STDMETHOD(put_HostName)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ChallengePhrase)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ChallengePhrase)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_EncUserSMIMECertificate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_EncUserCertificate)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_userCertificate)(/*[in]*/ BSTR newVal);

	CSignAttributes() ;
	//virtual ~CSignAttributes() ;
private :
	void			_ShowErrorMessage(DWORD errorCode, LPSTR szExtraString) ;
	void			_Base64Decode(PCHAR pInput, DWORD dwInputSize, PCHAR pOutput, DWORD * dwOutputSize) ;
	LPSTR			_WideToMultiString(BSTR szwcInputString) ;
	BSTR			_MultiToWideString(LPSTR szInputString) ;
	DWORD			_GetCertSubjectRDN(PCCERT_CONTEXT pCertContext, LPSTR szSubjectRDN) ;

	BSTR			m_bstrErrorCodeString ;		// Contains the error string corresponding to the error code
	DWORD			m_dwErrorCode ;				// Contains the error code

	LPSTR			m_szBase64PKCS7 ;
	DWORD			m_cbPKCS7 ;
	PBYTE			m_pbPKCS7 ;

	LPSTR			m_szUserCertificate, m_szUserSMIMECertificate ;
	PBYTE			m_pbUserCertificate, m_pbUserSMIMECertificate ;
	DWORD			m_cbUserCertificate, m_cbUserSMIMECertificate ;

	DWORD			m_dwNumberOfCACerts ;

	HCERTSTORE				m_hCertStore ;
	PCCERT_CONTEXT_LIST		m_pCertContextList ;

	LPSTR			m_szAlgorithms ;
	LPSTR			m_ChallengePhrase;

	HRESULT _GetHostName(BSTR *tbstrHostName);
	//HRESULT _GetCertCount(HCERTSTORE hCertStore, PCHAR pszRFC822Name, PCHAR pszSubjectName, PCHAR pszIssuerName, BOOL bIntentedUsageBoth, int *nCount);
	HRESULT _GetCertCount(HCERTSTORE hCertStore, WCHAR* pwszRFC822Name, WCHAR* pwszSubjectName,
		WCHAR* pwszIssuerName, BOOL bIntentedUsageBoth, int *nCount);
};

#endif //__SIGNATTRIBUTES_H_
