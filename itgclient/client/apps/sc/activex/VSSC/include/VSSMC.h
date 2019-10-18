// VSSMC.h : Declaration of the CVSSC

#ifndef __VSSC_H_
#define __VSSC_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


//using namespace std ;
//#include <list>
//typedef list<CAttachInfo *> ATTACH_FILE_INFO;


/////////////////////////////////////////////////////////////////////////////
// CVSSC
class ATL_NO_VTABLE CVSSC : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVSSC, &IID_IVSSC, &LIBID_VSSCLib>,
	public CComControl<CVSSC>,
	public IPersistStreamInitImpl<CVSSC>,
	public IOleControlImpl<CVSSC>,
	public IOleObjectImpl<CVSSC>,
	public IOleInPlaceActiveObjectImpl<CVSSC>,
	public IViewObjectExImpl<CVSSC>,
	public IOleInPlaceObjectWindowlessImpl<CVSSC>,
	public ISupportErrorInfo,
	public IPersistStorageImpl<CVSSC>,
	public ISpecifyPropertyPagesImpl<CVSSC>,
	public IQuickActivateImpl<CVSSC>,
	public IDataObjectImpl<CVSSC>,
	public IProvideClassInfo2Impl<&CLSID_VSSC, NULL, &LIBID_VSSCLib>,
	public CComCoClass<CVSSC, &CLSID_VSSC>,
	public IDispatchImpl<IResolveRcpt, &IID_IResolveRcpt, &LIBID_VSSCLib>,
	public IDispatchImpl<IVSSignerInfo, &IID_IVSSignerInfo, &LIBID_VSSCLib>,
	public IDispatchImpl<IVSSCDllApi, &IID_IVSSCDllApi, &LIBID_VSSCLib>


{
public:
	CVSSC();
	~CVSSC();
	
	
	//Agg
	HRESULT FinalConstruct();
	void FinalRelease();
	CComPtr<IUnknown> m_pUnkObj;

DECLARE_REGISTRY_RESOURCEID(IDR_VSSC)
//Agg
DECLARE_GET_CONTROLLING_UNKNOWN()

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSSC)
	COM_INTERFACE_ENTRY(IVSSC)
	//Del-COM_INTERFACE_ENTRY(IDispatch)
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
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IVSPTA, m_pUnkObj.p)
	COM_INTERFACE_ENTRY2(IDispatch, IVSSC) //Add
	COM_INTERFACE_ENTRY(IResolveRcpt)
	COM_INTERFACE_ENTRY(IVSSignerInfo)
	COM_INTERFACE_ENTRY(IVSSCDllApi)

END_COM_MAP()

BEGIN_PROP_MAP(CVSSC)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CVSSC)
	CHAIN_MSG_MAP(CComControl<CVSSC>)
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
			&IID_IVSSC,
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

// IVSSC
public:

	/*
	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
			return S_OK;
	}
	*/
	

public:
	STDMETHOD(SelectAttachments)(/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(get_CryptStatus)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_Date)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Date)(/*[in]*/ VARIANT newVal);
	
	STDMETHOD(get_GetMsg)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_Body)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Body)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_MsgType)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_MsgType)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_Subject)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_Subject)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_FromInfo)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_FromInfo)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_BccRecipientsInfo)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_BccRecipientsInfo)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_CcRecipientsInfo)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_CcRecipientsInfo)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ToRecipientsInfo)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ToRecipientsInfo)(/*[in]*/ VARIANT newVal);
	
	STDMETHOD(Compose)(/*[in, out]*/ VARIANT* i_pvarAppStatus);
	CPost   m_pPost;

public:
	CListUserInfo::iterator		it,ResolveIter;
	CUserInfo					*pObj;

	_bstr_t						m_bstrCertResolutionURL;
private:
	_bstr_t                     m_bstrURL,m_bstrMethod,m_bstrPostData,m_bstrDownloadData; 

	BOOL						m_bInitialized;
	BOOL						m_bFoundPTAVer;
	BOOL						m_bResolveFirst;
	BOOL						bUseInternetData;
	BOOL                        bDecCert; 

	DWORD						dwSizeSum;
	BYTE						*pbURLContent;	
	
	DECCERT_INFO				*pDecCertInfo;

	CComPtr <IOleClientSite>	m_spOuterClientSite;

private:

	//VSSC_MSGINFO    MsgInfo;
    CMsg            *m_pMsg;   
	
	
	HRESULT         hr;
	BSTR			bstrRetVal;
	
	DWORD			m_dwErrorCode,err ;	
	DWORD           dwMsgType;

	DWORD           dwRetBufferSize;

	BOOL            bComposeCalled;
	
	
	//char            *szBody;
	ATTACH_FILE_INFO			*g_AttachedFiles;	

public:
	STDMETHOD(put_UseSimder)(/*[in]*/ VARIANT newVal);
	STDMETHOD(ResolveProxyRecipCert)(VARIANT *in_pvarEmailInfo,VARIANT *o_pvarAppStatus,VARIANT *in_pvarStatus);
	STDMETHOD(put_URLEncodeData)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_ShowSelIDUI)(/*[in]*/ VARIANT newVal);
	HRESULT InstalledPTAVer(char*szPTAver);
	STDMETHOD(get_IsCertExpired)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_ChainValidationStatus)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_RevocationStatus)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_InstalledPTAVer)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_SupportedPTAVer)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AllowDecryption)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AddSMIMECapabilities)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_UsePKCS7Certificate)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_SerialNumber)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_Issuer_DN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(ClearAll)(/*[in]*/ VARIANT* i_pvarMode, /*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(get_MessageTimeOut)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_MessageTimeOut)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_CertificateTimeOut)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_CertificateTimeOut)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_SCType)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_SCType)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AddSenderRecipientInfo)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_OpaqueSign)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AddMIMEHeader)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AddRFC822Header)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_AddSignerCertificate)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_IVSSCResolveInfo)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(GetAttachFileContent)(VARIANT* in_pvarFileName,/*[in, out]*/ VARIANT* i_pvarAppStatus, /*[out,retval]*/VARIANT* o_pvarFileContent);
	STDMETHOD(get_HostProtocol)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_HostProtocol)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_HostFQDN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_HostFQDN)(/*[in]*/ VARIANT newVal);
	HRESULT GetSignerCertProps();
	STDMETHOD(get_SubjectValidTo)(/*[out, retval]*/ DATE *pVal);
	STDMETHOD(get_SubjectValidFrom)(/*[out, retval]*/ DATE *pVal);
	STDMETHOD(get_SubjectSerialNumber)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_IssuerDN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SubjectDN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SubjectCN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_IVSSignerInfo)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(SelectedAttachmentSize)(VARIANT* in_pvarFileName,/*[in, out]*/ VARIANT* i_pvarAppStatus, /*[out,retval]*/VARIANT* o_pvarFileSize);
	STDMETHOD(ChangeVarType)(VARIANT* in_pvarByteArray,VARIANT* in_pvarType, /*[out,retval]*/VARIANT* o_pvarOutputType);
	
	STDMETHOD(get_InternetData)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_InternetDataSize)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UseInternetData)(/*[in]*/ VARIANT newVal);
	STDMETHOD(InternetSendRequest)(/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(InternetInitialize)(VARIANT *in_pvarURL,VARIANT *in_pvarMethod,VARIANT *in_pvarPostData,/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(get_MsgBlobSize)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_MsgObjID)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(StoreAll)(VARIANT *i_pModeType,/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(Initialize)(VARIANT *i_pMsgObjID,VARIANT *i_pMode,/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(get_Status)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UseProxyRecipCert)(/*[in]*/ VARIANT newVal);
	STDMETHOD(Next)();
	STDMETHOD(First)();
	STDMETHOD(get_Recipient_Count)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_EmailAddress)(/*[out, retval]*/ VARIANT *pVal);


	STDMETHOD(Decompose)(/*[in]*/ VARIANT* i_pvarSMIMEMsg, /*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(get_IVSSCPTA)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(put_CertResolveURL)(/*[in]*/ VARIANT newVal);
	STDMETHOD(SMIMECertificateResolution)(/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(CertificateResolution)(VARIANT* in_pvarEmailInfo,/*[in, out]*/ VARIANT* i_pvarAppStatus);
	STDMETHOD(put_MsgPostData)(/*[in]*/ VARIANT newVal);
	STDMETHOD(SaveAttachment)(VARIANT *pFileName, VARIANT *pStatus);
	STDMETHOD(get_AttachedFileList)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UnSelectAttachments)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_SelectedAttachments)(/*[out, retval]*/ VARIANT *pVal);


private:
	HRESULT _GetHostAndProtocol(_bstr_t& tbstrHostName, _bstr_t& tbstrProtocolName);
	HRESULT CheckEnv(short nCheck);
	IDispatch* _GetInterface(REFIID i_refIId);
	void _SetErrorInfo(HRESULT hresultErr);


	void SetComposeMode();

};

#endif //__VSSC_H_
