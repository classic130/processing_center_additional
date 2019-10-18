// ConfigChkr.h : Declaration of the CConfigChkr

#ifndef __CONFIGCHKR_H_
#define __CONFIGCHKR_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CConfigChkr
class ATL_NO_VTABLE CConfigChkr : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IConfigChkr, &IID_IConfigChkr, &LIBID_CONFIGCHKLib>,
	public CComControl<CConfigChkr>,
	public IPersistStreamInitImpl<CConfigChkr>,
	public IOleControlImpl<CConfigChkr>,
	public IOleObjectImpl<CConfigChkr>,
	public IOleInPlaceActiveObjectImpl<CConfigChkr>,
	public IViewObjectExImpl<CConfigChkr>,
	public IOleInPlaceObjectWindowlessImpl<CConfigChkr>,
	public IPersistStorageImpl<CConfigChkr>,
	public ISpecifyPropertyPagesImpl<CConfigChkr>,
	public IQuickActivateImpl<CConfigChkr>,
	public IDataObjectImpl<CConfigChkr>,
	public IProvideClassInfo2Impl<&CLSID_ConfigChkr, NULL, &LIBID_CONFIGCHKLib>,
	public CComCoClass<CConfigChkr, &CLSID_ConfigChkr>
{
public:
	CConfigChkr()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CONFIGCHKR)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CConfigChkr)
	COM_INTERFACE_ENTRY(IConfigChkr)
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
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CConfigChkr)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CConfigChkr)
	CHAIN_MSG_MAP(CComControl<CConfigChkr>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IConfigChkr
public:
	STDMETHOD(CheckKeyGen)(VARIANT* i_pvarProvName, VARIANT* i_pvarKeyFlags, /*[out,retval]*/ VARIANT* o_pvarResult );
	STDMETHOD(ChkWindowsLogin)(long* o_lResult);
	STDMETHOD(FixEnhCSP)(VARIANT* i_pvarEnhCSPVer, /*[out,retval]*/long* o_plRetVal);
	STDMETHOD(CheckMSEnhCSP)(/*[out.retval]*/ long* o_lRetVal);
	STDMETHOD(VerCompare)(VARIANT* i_pvarVer1, VARIANT* i_pvarVer2, /*[out,retval]*/ long* o_plResult);
	STDMETHOD(GetVersion)(VARIANT* i_pvarFile, VARIANT* o_pvarVersion, /*[out,retval]*/ long* o_lResult);
	
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
#if 0
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : ConfigChkr");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));
#endif
		return S_OK;
	}

private :
	LPSTR GetVer(LPSTR szFileName);
	LPSTR CConfigChkr::_WideToMultiString(BSTR szwcInputString);
	BSTR CConfigChkr::_MultiToWideString(LPSTR szInputString);

	long CConfigChkr::_CompareVersion(LPSTR szVer1, LPSTR szVer2);
	BOOL CheckFileName (LPSTR pFileName);
};

#endif //__CONFIGCHKR_H_
