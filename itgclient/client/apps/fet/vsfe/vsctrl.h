// vsctrl.h : Declaration of the Cvsctrl

#ifndef __VSCTRL_H_
#define __VSCTRL_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// Cvsctrl
class ATL_NO_VTABLE Cvsctrl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<Ivsctrl, &IID_Ivsctrl, &LIBID_VSCTLLib>,
	public CComControl<Cvsctrl>,
	public IPersistStreamInitImpl<Cvsctrl>,
	public IOleControlImpl<Cvsctrl>,
	public IOleObjectImpl<Cvsctrl>,
	public IOleInPlaceActiveObjectImpl<Cvsctrl>,
	public IViewObjectExImpl<Cvsctrl>,
	public IOleInPlaceObjectWindowlessImpl<Cvsctrl>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<Cvsctrl>,
	public ISpecifyPropertyPagesImpl<Cvsctrl>,
	public IQuickActivateImpl<Cvsctrl>,
	public IDataObjectImpl<Cvsctrl>,
	public IProvideClassInfo2Impl<&CLSID_vsctrl, NULL, &LIBID_VSCTLLib>,

	public CComCoClass<Cvsctrl, &CLSID_vsctrl>
{
public:
	Cvsctrl()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VSCTRL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(Cvsctrl)
	COM_INTERFACE_ENTRY(Ivsctrl)
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
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)

END_COM_MAP()

BEGIN_PROP_MAP(Cvsctrl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(Cvsctrl)
	CHAIN_MSG_MAP(CComControl<Cvsctrl>)
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
			&IID_Ivsctrl,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// Ivsctrl
public:
	STDMETHOD(SetFetContextInformation)(BSTR bstrAppContext, BSTR bstrClientInfo, BSTR bstrClientInfoSig);
	STDMETHOD(SetEnterpriseServer)(BSTR);
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : vsctrl");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}
	
};

#endif //__VSCTRL_H_
