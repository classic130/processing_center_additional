// VSGSE.h : Declaration of the CVSGSE

#ifndef __VSGSE_H_
#define __VSGSE_H_


#include "resource.h"       // main symbols
#include <atlctl.h>

/////////////////////////////////////////////////////////////////////////////
// CVSGSE
class ATL_NO_VTABLE CVSGSE : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVSGSE, &IID_IVSGSE, &LIBID_VGSELib>,
	public CComControl<CVSGSE>,
	public IPersistStreamInitImpl<CVSGSE>,
	public IOleControlImpl<CVSGSE>,
	public IOleObjectImpl<CVSGSE>,
	public IOleInPlaceActiveObjectImpl<CVSGSE>,
	public IViewObjectExImpl<CVSGSE>,
	public IOleInPlaceObjectWindowlessImpl<CVSGSE>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CVSGSE>,
	public IPersistStorageImpl<CVSGSE>,
	public ISpecifyPropertyPagesImpl<CVSGSE>,
	public IQuickActivateImpl<CVSGSE>,
	public IDataObjectImpl<CVSGSE>,
	public IProvideClassInfo2Impl<&CLSID_VSGSE, NULL, &LIBID_VGSELib>,
//	public IProvideClassInfo2Impl<&CLSID_VSGSE, &DIID__IVSGSEEvents, &LIBID_VGSELib>,
	//public IPropertyNotifySinkCP<CVSGSE>,
	public CComCoClass<CVSGSE, &CLSID_VSGSE>
{
public:
	CVSGSE()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VSGSE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSGSE)
	COM_INTERFACE_ENTRY(IVSGSE)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CVSGSE)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CVSGSE)
//	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CVSGSE)
	CHAIN_MSG_MAP(CComControl<CVSGSE>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IVSGSE,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			//if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

public:
	CProfAdmin      m_pProfAdmin;




private:
	HRESULT         hr;
	BSTR			bstrRetVal;


	DWORD			m_dwErrorCode ;	



private:

	HRESULT          ReportError(HRESULT hr);
	


// IVSGSE
public:
	STDMETHOD(get_LastName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FirstName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SetDefaultCertFlag)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_SetDefaultCertFlag)(/*[in]*/ short newVal);

	STDMETHOD(put_SetEFSCertificate)(/*[in]*/ short newVal);
	STDMETHOD(get_ExchServer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CertSerialNum)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_RenewCert)(/*[in]*/ short newVal);
	STDMETHOD(get_Explode_DN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_CharEncodingInfo)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_CharEncodingInfo)(/*[in]*/ short newVal);
	STDMETHOD(put_CertFriendlyName)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_PKCS7)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ExchangeVerString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_UserDN)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_UserDN)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ADServerInfoList)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ADServerInfoList)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ADServerInfo)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ADServerInfo)(/*[in]*/short newVal);
	STDMETHOD(get_ExchangeVer)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_ExchangeVer)(/*[in]*/ short newVal);
	STDMETHOD(get_CAInfo)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_CAInfo)(/*[in]*/ short newVal);
	STDMETHOD(UpdateClientExt)();
	STDMETHOD(get_EnableCRLDistPoint)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_EnableCRLDistPoint)(/*[in]*/ short newVal);
	STDMETHOD(get_ProfileName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ProfileName)(/*[in]*/ BSTR newVal);
	STDMETHOD(AddEncryptSignButton)();
	

	
	STDMETHOD(put_ServerName)(/*[in]*/ BSTR newVal);
	STDMETHOD(put_MailDN)(/*[in]*/ BSTR newVal);
	STDMETHOD(PromptForSelection)();
	STDMETHOD(get_RFC822Name)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ProfileServer)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_HomeMTA)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FullName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DN)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Alias)(/*[out, retval]*/ BSTR *pVal);
    STDMETHOD(get_UserPrincipalName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_IsUserMemberOfAdminGroup)(/*[out, retval]*/ BSTR *pVal);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		return S_OK;
	}
};

#endif //__VSGSE_H_
