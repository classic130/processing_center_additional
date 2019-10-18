// VSNZ.h : Declaration of the CVSNZ

#ifndef __VSNZ_H_
#define __VSNZ_H_

#include "resource.h"       // main symbols
#include "INzShellExtInit.h"
#include "INzCtxtMenu.h"
#include "DNZUI.h"
#include <atlctl.h>
#include "dnzuistructs.h"

// Which help to show when user click on the help buttons
enum NZHelpType
{
	NZ_RECEIPT,
	NZ_PROGRESS_DONE
};


//Friend functions
HRESULT SelFileFn(POPCTXT pOpCtxt);
HRESULT CancelFn(POPCTXT pOpCtxt);
HRESULT ProgressDoneFn(POPCTXT pOpCtxt);
HRESULT SelFileHelpFn(POPCTXT pOpCtxt);
HRESULT ProgressHelpFn(POPCTXT pOpCtxt);
HRESULT VerifyDoneFn(POPCTXT pOpCtxt);
HRESULT VerifyHelpFn(POPCTXT pOpCtxt);


/////////////////////////////////////////////////////////////////////////////
// CVSNZ
class ATL_NO_VTABLE CVSNZ : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVSNZ, &IID_IVSNZ, &LIBID_VSDNOTZLib>,
	public CComControl<CVSNZ>,
	public IPersistStreamInitImpl<CVSNZ>,
	public IOleControlImpl<CVSNZ>,
	public IOleObjectImpl<CVSNZ>,
	public IOleInPlaceActiveObjectImpl<CVSNZ>,
	public IViewObjectExImpl<CVSNZ>,
	public IOleInPlaceObjectWindowlessImpl<CVSNZ>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CVSNZ>,
	public ISpecifyPropertyPagesImpl<CVSNZ>,
	public IQuickActivateImpl<CVSNZ>,
	public IDataObjectImpl<CVSNZ>,
	public IProvideClassInfo2Impl<&CLSID_VSNZ, NULL, &LIBID_VSDNOTZLib>,
	public CComCoClass<CVSNZ, &CLSID_VSNZ>,
	public INzShellExtInit,
	public INzCtxtMenu,
	public IDispatchImpl<IVSNZUIPrefs, &IID_IVSNZUIPrefs, &LIBID_VSDNOTZLib>,
	public IDispatchImpl<IVSNZAppPrefs, &IID_IVSNZAppPrefs, &LIBID_VSDNOTZLib>,
	public IDispatchImpl<IVSNZDllApi, &IID_IVSNZDllApi, &LIBID_VSDNOTZLib>
{
public:

	CVSNZ()
	{
		m_pUnkPta = NULL;
		m_bInitialized = FALSE;
		m_pSelItems	= NULL;
		m_bstrUAgent = "";
		m_boolShowSaveLink = true;
	}


	~CVSNZ()
	{
		m_pUnkPta = NULL;
		m_bInitialized = FALSE;
		m_bstrUAgent = "";

		RELEASE_INTERFACE_PTR(m_pSelItems)
	}

	HRESULT FinalConstruct();
	void FinalRelease();
	void SetShowSaveLink(bool boolShowSaveLink);

DECLARE_REGISTRY_RESOURCEID(IDR_VSNZ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSNZ)
	COM_INTERFACE_ENTRY(IVSNZ)
//	COM_INTERFACE_ENTRY(IDispatch)
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
	COM_INTERFACE_ENTRY2(IDispatch, IVSNZ)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
	COM_INTERFACE_ENTRY(IVSNZUIPrefs)
	COM_INTERFACE_ENTRY(IVSNZAppPrefs)
	COM_INTERFACE_ENTRY(IVSNZDllApi)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IVSPTA, m_pUnkPta.p)
END_COM_MAP()

DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_PROP_MAP(CVSNZ)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CVSNZ)
	CHAIN_MSG_MAP(CComControl<CVSNZ>)
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
			&IID_IVSNZ,
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

// IVSNZ
public:
	
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : VSNZ");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}

	// IVSNZ interface
	STDMETHOD(NotarizeHash)(VARIANT *i_pvarHash, VARIANT *i_pvarUIMask, VARIANT *o_pvarResponse);
	STDMETHOD(AddNZCertificate)(VARIANT *i_pvarCertificate);
	STDMETHOD(put_NotarizationDescription)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_ValidationPreference)(/*[in]*/ VARIANT newVal);
	STDMETHOD(VerifyNotarizationRecord)(VARIANT* i_pvarRecord, VARIANT* i_pvarDocument, VARIANT* i_pvarRecordType,  VARIANT* i_pvarUIMask);
	STDMETHOD(NotarizeDocument)(VARIANT* i_pvarDocument, VARIANT* i_pvarUIMask, VARIANT* i_pvarResponseType, /*[out, retval]*/VARIANT* o_pvarResponse);
	STDMETHOD(get_IVSNZAppPrefs)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSNZUIPrefs)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSNZPta)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(put_DisplayDigitalID)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_HashAlg)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_NotarizationServer)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_CRLLocation)(/*[in]*/ VARIANT newVal);
	STDMETHOD(Close)();
	STDMETHOD(Initialize)();

	// IVSNZUIPrefs interface
	STDMETHOD(put_UILogoUrl)(VARIANT newVal);
	STDMETHOD(put_UISelFileTitle)(VARIANT newVal);
	STDMETHOD(put_UISelFileDescription)(VARIANT newVal);
	STDMETHOD(put_UISelFileHelpUrl)(VARIANT newVal);
	STDMETHOD(put_UIProgressTitle)(VARIANT newVal);
	STDMETHOD(put_UIProgressDescription)(VARIANT newVal);
	STDMETHOD(put_UIProgressHelpUrl)(VARIANT newVal);
	STDMETHOD(put_UIVerifyRcptTitle)(VARIANT newVal);
	STDMETHOD(put_UIVerifyRcptDescription)(VARIANT newVal);
	STDMETHOD(put_UIVerifyRcptHelpUrl)(VARIANT newVal);
	STDMETHOD(put_UIWizardTitle)(/*[in]*/ VARIANT newVal);

	// IVSNZAppPrefs interface
	STDMETHOD(SetApplicationPreference)(VARIANT* in_pvarAppName, VARIANT* in_pvarPrefName, VARIANT* in_pvarPrefValue);
	STDMETHOD(GetApplicationPreference)(VARIANT* in_pvarAppName, VARIANT* in_pvarPrefName, VARIANT* o_pvarPrefType, /*[out,retval]*/VARIANT* o_pvarPrefValue);

	// IVSNZDllApi interface
	STDMETHOD(get_UAgent)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UAgent)(/*[in]*/ VARIANT newVal);

	// IShellExtInit interface
	STDMETHOD(Initialize)(LPCITEMIDLIST pIDFolder, LPDATAOBJECT pDataObj, HKEY hKeyID);

	// IContextMenu interface
	STDMETHOD(QueryContextMenu)(HMENU hMenu,UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
	STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpcmi);
	STDMETHOD(GetCommandString)(UINT idCmd, UINT uFlags, UINT FAR *reserved, LPSTR pszName, UINT cchMax);

private:
	CComPtr<IUnknown> m_pUnkPta;	// Pointer to IUnknown interface of the PTA, used for aggregation
	BOOL m_bInitialized;			// To indicate if 'Initialize() has been called
	CUserSettings m_UsrSettings;	// Holds the current user settings for the UI, PTA, Notarization etc
	LPDATAOBJECT m_pSelItems;		// Used to query the files that are selected by the context menu
	_bstr_t m_bstrUAgent;			// User agent string set from NS plugin or any other application hosting
	bool m_boolShowSaveLink;			// the Activex. For IE the user agent is obtained from the client site

private:
	// Private methods
	IDispatch* _GetInterface(REFIID i_refIId);

	HRESULT _CanNotarizeDocument();
	HRESULT _NotarizeDocuments();
	HRESULT _DoDigitalNotarization(IVSPTA* i_pVSPta, LPCTSTR* pSelFiles, PBYTE* i_pbHashValues, const UINT nToNotarize, const BOOL i_bUseHash, const DWORD i_dwUIMask, const ResponseType i_rType, const BOOL i_bCreateReceipt, PBYTE* o_pbRecords, LPDWORD o_pdwRecordLengths);
	HRESULT _DoRecordVerification(const _bstr_t i_bstrRecord, const _bstr_t i_bstrDocument, const BOOL i_bUrl, const DWORD i_dwValidationFlags, LPNzDetails o_NzDetailedInfo);

	HRESULT _InitializePTA(BOOL i_bDisplayDigID, IVSPTA** o_pVSPta, BOOL bCloseProfile = FALSE);
	HRESULT _UnInitializePTA(IVSPTA* i_pVSPta);
	HRESULT _GetNotarizationDocument(IVSPTA* i_pPTA,CDNZUI* pTheDNZUI, _bstr_t& i_bstrDocument, DWORD i_dwUIMask);
	HRESULT _SetUICtxtForSelect(IVSPTA* i_pPTA, PUICTXT pTheUICtxt, DWORD i_dwUIMask);
	HRESULT _SetUICtxtForStatus(IVSPTA* i_pPTA, PUICTXT pTheUICtxt);
	HRESULT _BeginProgressUI(IVSPTA* i_pPTA,CDNZUI* i_pTheDNZUI,POPCTXT pTheOpCtxt, BOOL i_bShowFileSelectUI);
	HRESULT _UpdateProgressUI(CDNZUI* i_pTheDNZUI, int i_nPercentComplete, int i_nStringID);
	HRESULT _EndProgressUI(CDNZUI* i_pTheDNZUI, _bstr_t i_bstrErrString, POPCTXT pTheOpCtxt, BOOL i_bShowModal = TRUE);
	HRESULT _SetUICtxtForProgress(IVSPTA* i_pPTA, PUICTXT pTheUICtxt, BOOL i_bShowFileSelectUI, BOOL i_bUseAsStatusUI);
	HRESULT _ShowVerificationUI(CDNZUI* i_pTheDNZUI, IVSPTA* i_pPTA, DWORD i_dwUIMask, NzDetails* i_pNzDetailedInfo);
	HRESULT _ShowErrorUI(CDNZUI* i_pTheDNZUI, _bstr_t i_bstrErrString);
	HRESULT _SetUICtxtForVeirfication(IVSPTA* i_pPTA, PUICTXT i_pTheUICtxt, DWORD i_dwUIMask, LPCTSTR i_pTmpHtmlFile, NzDetails* i_pNzDetailedInfo);
	HRESULT _GetUserAgentString(_bstr_t* o_pbstrUserAgent);
	//_bstr_t _GetNotarizedMsgIfText(LCID locale, _bstr_t bstrNzDocumentName);
	VOID ShowHelp(NZHelpType nzHelpType);

	// Friend functions
	friend HRESULT SelFileFn(POPCTXT pOpCtxt);
	friend HRESULT SelFileHelpFn(POPCTXT pOpCtxt);
	friend HRESULT CancelFn(POPCTXT pOpCtxt);
	friend HRESULT ProgressDoneFn(POPCTXT pOpCtxt);
	friend HRESULT ProgressCancelFn(POPCTXT pOpCtxt);
	friend HRESULT ProgressHelpFn(POPCTXT pOpCtxt);
	friend HRESULT VerifyDoneFn(POPCTXT pOpCtxt);
	friend HRESULT VerifyHelpFn(POPCTXT pOpCtxt);
	friend HRESULT ErrorDoneFn(POPCTXT pOpCtxt);
	friend HRESULT ErrorHelpFn(POPCTXT pOpCtxt);

};

#define	POST_DATA1	"<HTML> <HEAD> <TITLE>Receipt - VeriSign Digital Notarization Services</TITLE> </HEAD> <BODY> <FORM NAME=\"DigitalNotarization\" METHOD=\"post\" ACTION=\"https://"
#define POST_DATA2	"/verify-cgi/tsVerifyStep1\"> <INPUT TYPE=\"hidden\" NAME=\"tstoken\" VALUE=\""
#define POST_DATA3	"\"> <INPUT TYPE=\"hidden\" NAME=\"form_file\" VALUE=\"../fdf/verifyStep1.fdf\"> <INPUT TYPE=\"hidden\" NAME=\"html_file\" VALUE=\"../htmldocs/notarization/verifyStep1.html\"> </FORM>"
#define POST_DATA4  "<SCRIPT LANGUAGE=\"JavaScript\"> document.DigitalNotarization.submit(); </SCRIPT> </BODY> </HTML>"

#endif //__VSNZ_H_
