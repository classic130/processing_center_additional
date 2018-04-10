// VSPTA.h : Declaration of the CVSPTA

#ifndef __VSPTA_H_
#define __VSPTA_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


#include "..\Include\ptadefines.h"
#include "..\Include\ptaerrs.h"
#include "..\Include\ptacorestructs.h"
#include "..\Include\ptauistructs.h"


#include "..\Include\PtaEngine.h"
#include "..\Include\PtaUI.h"

extern _DWORD		(*SIMDER_MemErase) (_DWORD cbdata, _PBYTE pbdata) ;

#define VSPTA_CLEAN_TBSTR(tbstrString)\
{\
	if ( 0 < tbstrString.length() )\
	{\
		memset ( (void*) ((WCHAR*) tbstrString), 1, (tbstrString.length() * 2) );\
		memset ( (void*) ((CHAR*) tbstrString), 1, (tbstrString.length()) );\
	}\
}
#define MIN_COLOR_DIFF_SATURATION 4


//Friend functions
HRESULT OpenProfCreateFn(POPCTXT pOpCtxt);
HRESULT OpenProfCreateHelpFn(POPCTXT pOpCtxt);
HRESULT OpenProfOpenFn(POPCTXT pOpCtxt);
HRESULT OpenProfOpenHelpFn(POPCTXT pOpCtxt);
HRESULT SelIdFn(POPCTXT pOpCtxt);
HRESULT SelIdHelpFn(POPCTXT pOpCtxt);
HRESULT SignMsgFn(POPCTXT pOpCtxt);
HRESULT SignMsgHelpFn(POPCTXT pOpCtxt);
HRESULT PrevToCreateFn(POPCTXT pOpCtxt);
HRESULT PrevToOpenFn(POPCTXT pOpCtxt);
HRESULT PrevToSelIdFn(POPCTXT pOpCtxt);
HRESULT CancelFn(POPCTXT pOpCtxt);
HRESULT IntroFn(POPCTXT pOpCtxt);
HRESULT PrevToIntroFn(POPCTXT pOpCtxt);
HRESULT IntroDlgFn(POPCTXT pOpCtxt);
HRESULT PasswordCallback ( void* i_pvoidPointer, _VS_CHAR*	o_cszPassword);
HRESULT CreatePasswdFn(POPCTXT pOpCtxt);
HRESULT EnterPasswdFn(POPCTXT pOpCtxt);
HRESULT ChngPasswdFn(POPCTXT pOpCtxt);
HRESULT ChngPasswdHelpFn(POPCTXT pOpCtxt);
HRESULT TimeoutCancelFn(POPCTXT pOpCtxt);
HRESULT TimeoutFn(POPCTXT pOpCtxt);
HRESULT TimeoutHelpFn(POPCTXT pOpCtxt);
HRESULT ExportP12Fn(POPCTXT pOpCtxt);
HRESULT ExportProfileFn(POPCTXT pOpCtxt);
HRESULT ImportProfileFn(POPCTXT pOpCtxt);

// Sasi 05/05/2003
// Friend functions used for GetSecretQuestion, ResetPassword and CreateSecret dialogs
HRESULT GetSecretQuestionFn(POPCTXT pOpCtxt);
HRESULT PrevToGetSecretQuestionFn(POPCTXT pOpCtxt);
HRESULT ResetPasswdFn(POPCTXT pOpCtxt);
HRESULT CreateSecretFn(POPCTXT pOpCtxt);

/////////////////////////////////////////////////////////////////////////////
// CVSPTA
class ATL_NO_VTABLE CVSPTA : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVSPTA, &IID_IVSPTA, &LIBID_PTAV3Lib>,
	public CComControl<CVSPTA>,
	public IPersistStreamInitImpl<CVSPTA>,
	public IOleControlImpl<CVSPTA>,
	public IOleObjectImpl<CVSPTA>,
	public IOleInPlaceActiveObjectImpl<CVSPTA>,
	public IViewObjectExImpl<CVSPTA>,
	public IOleInPlaceObjectWindowlessImpl<CVSPTA>,
	public ISupportErrorInfo,
	public CComCoClass<CVSPTA, &CLSID_VSPTA>,
	public IDispatchImpl<IVSProfMgmt, &IID_IVSProfMgmt, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSUIPrefs, &IID_IVSUIPrefs, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSCertPrefs, &IID_IVSCertPrefs, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSSrchCrit, &IID_IVSSrchCrit, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSSelectedDigID, &IID_IVSSelectedDigID, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSRoamPrefs, &IID_IVSRoamPrefs, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSPTADllApi, &IID_IVSPTADllApi, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSP12Import, &IID_IVSP12Import, &LIBID_PTAV3Lib>,
	public IDispatchImpl<IVSP12Export, &IID_IVSP12Export, &LIBID_PTAV3Lib>
{
public:
	CVSPTA()
	{
			(*SIMDER_MemErase) =	&EraseMemory;

		m_bInitialized = FALSE;

		/*Create the UI and the engine objects*/
		m_pPtaUI = _CreateUiObject();  //We create it in a separate function
											//in case we want to later plug in third
											//part ui's which will be created differ
											//ently (e.g as a com object)
		m_pPtaEngine = (CPtaEngine*)new CPtaEngine (this);		//The engine object will not be pluggable
		m_boolUserHasSeenMsg = FALSE;
		m_boolIdSatisfiesSrchCrit = FALSE;
		m_tbstrSignature = "";
		m_tbstrCertReq = "";
		m_tbstrCertPref = "";

		m_pAppCtxt = NULL;
		m_pSelectedId = NULL;

		m_spOuterClientSite = NULL;
		nbOfAllowedTags = 55;
		allowedTags = new _bstr_t[nbOfAllowedTags];
		allowedTags[0] =  "HTML";
		allowedTags[1] =  "HEAD";
		allowedTags[2] =  "BODY";
		allowedTags[3] =  "H1";
		allowedTags[4] =  "H2";
		allowedTags[5] =  "H3";
		allowedTags[6] =  "H4";
		allowedTags[7] =  "H5";
		allowedTags[8] =  "H6";
		allowedTags[9] =  "FONT";
		allowedTags[10] = "U";
		allowedTags[11] = "B";
		allowedTags[12] = "I";
		allowedTags[13] = "TABLE";
		allowedTags[14] = "TR";
		allowedTags[15] = "TD";
		allowedTags[16] = "TITLE";
		allowedTags[17] = "UL";
		allowedTags[18] = "LI";
		allowedTags[19] = "OL";
		allowedTags[20] = "P";
		allowedTags[21] = "BR";
		allowedTags[22] = "HR";
		allowedTags[23] = "DT";
		allowedTags[24] = "DD";
		allowedTags[25] = "DL";
		allowedTags[26] = "PRE";
		allowedTags[27] = "BLOCKQUOTE";
		allowedTags[28] = "ADDRESS";
		allowedTags[29] = "TT";
		allowedTags[30] = "EM";
		allowedTags[31] = "STRONG";
		allowedTags[32] = "CODE";
		allowedTags[33] = "TBODY";
		allowedTags[34] = "TFOOT";
		allowedTags[35] = "THEAD";
		allowedTags[36] = "TH";
		allowedTags[37] = "DIR";
		allowedTags[38] = "MENU";
		allowedTags[39] = "DIR";
		allowedTags[40] = "PLAINTEXT";
		allowedTags[41] = "SPACER";
		allowedTags[42] = "ABBR";
		allowedTags[43] = "ACRONYM";
		allowedTags[44] = "S";
		allowedTags[45] = "STRIKE";
		allowedTags[46] = "SMALL";
		allowedTags[47] = "BIG";
		allowedTags[48] = "SUB";
		allowedTags[49] = "SUP";
		allowedTags[50] = "CENTER";
		allowedTags[51] = "CAPTION";
		allowedTags[52] = "COLGROUP";
		allowedTags[53] = "COL";
		allowedTags[54] = "MULTICOL";


		nbOfAllowedAttrs = 29;
		allowedAttrs = new _bstr_t[nbOfAllowedAttrs];
		allowedAttrs[0]="BGCOLOR"; // for HTML
		allowedAttrs[1]="TEXT";
		allowedAttrs[2]="ALIGN";
		allowedAttrs[3]="NOSHADE ";
		allowedAttrs[4]="SIZE";
		allowedAttrs[5]="WIDTH";
		allowedAttrs[6]="VALUE"; // LI / OL
		allowedAttrs[7]="TYPE"; // LI / OL
		allowedAttrs[8]="START";
		allowedAttrs[9]="BORDER";
		allowedAttrs[10]="CELLSPACING";
		allowedAttrs[11]="CELLPADDING";
		allowedAttrs[12]="ROWSPAN";
		allowedAttrs[13]="COLSPAN";
		allowedAttrs[14]="VALIGN";
		allowedAttrs[15]="HEIGHT";
		allowedAttrs[16]="SCOPE";
		allowedAttrs[17]="FACE"; // FONT
		allowedAttrs[18]="COLOR"; // FONT
		allowedAttrs[19]="ID";
		allowedAttrs[20]="BORDERCOLOR";
		allowedAttrs[21]="BORDERCOLORLIGHT";
		allowedAttrs[22]="BORDERCOLORDARK";
		allowedAttrs[23]="CAPTION";
		allowedAttrs[24]="COLS";
		allowedAttrs[25]="RULES";
		allowedAttrs[26]="CHAR";
		allowedAttrs[27]="CELLINDEX";
		allowedAttrs[28]="CHAROFF";



//		forbiddenTags = new _bstr_t[nbOfForbiddenTags];
//		forbiddenTags[0]= "INPUT";
//		forbiddenTags[1]= "LINK";
//		forbiddenTags[2]= "SELECT";
//		forbiddenTags[3]= "OPTION";
//		forbiddenTags[4]= "FRAME";
//		forbiddenTags[5]= "FRAMESET";
//		forbiddenTags[6]= "ILAYER"; 
//		forbiddenTags[7]= "LAYER";
//		forbiddenTags[8]= "TEXTAREA";
//		forbiddenTags[9]= "SPAN";
//		forbiddenTags[10]= "BGSOUND";
//		forbiddenTags[11]= "MARQUEE";
//		forbiddenTags[12]= "META";
//		forbiddenTags[13]= "A";
	}

	~CVSPTA()
	{
		//Free the selected id
/*		m_pPtaEngine->FreeIdList(m_pSelectedId);
		m_pSelectedId = NULL;

		//Free the app context
		_FreeAppCtxt(m_pAppCtxt);
		m_pAppCtxt = NULL;
*/
		Close();

		//Free the ui,engine and the app context
		if(m_pPtaUI)
			_DeleteUiObject(m_pPtaUI);

		if(m_pPtaEngine)
			delete(m_pPtaEngine);
	}		

DECLARE_REGISTRY_RESOURCEID(IDR_VSPTA)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVSPTA)
	COM_INTERFACE_ENTRY(IVSPTA)
//DEL 	COM_INTERFACE_ENTRY(IDispatch)
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
	COM_INTERFACE_ENTRY2(IDispatch, IVSPTA)
	COM_INTERFACE_ENTRY(IVSProfMgmt)
	COM_INTERFACE_ENTRY(IVSUIPrefs)
	COM_INTERFACE_ENTRY(IVSCertPrefs)
	COM_INTERFACE_ENTRY(IVSSrchCrit)
	COM_INTERFACE_ENTRY(IVSSelectedDigID)
	COM_INTERFACE_ENTRY(IVSRoamPrefs)
	COM_INTERFACE_ENTRY(IVSPTADllApi)
	COM_INTERFACE_ENTRY(IVSP12Import)
	COM_INTERFACE_ENTRY(IVSP12Export)
END_COM_MAP()

BEGIN_PROP_MAP(CVSPTA)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_MSG_MAP(CVSPTA)
	CHAIN_MSG_MAP(CComControl<CVSPTA>)
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
			&IID_IVSPTA,
		};
		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (::InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// IVSPTA
public:
	STDMETHOD(get_IsPrivateKeyExportable)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_IsPrivateKeyExportable)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UTF8EncodeMessage)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UTF8EncodeMessage)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_IsTPMAvailable)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(ImportProfile)(VARIANT *in_pvarPassword, VARIANT *in_pvarProfileData);
	STDMETHOD(ExportProfile)(VARIANT *in_pvarPassword, VARIANT in_varFlags, VARIANT *o_pvarProfileInfo);
	STDMETHOD(put_EnableCertForCapi)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_SignDate)(/*[out, retval]*/ DATE *pVal);
	STDMETHOD(put_SignDate)(/*[in]*/ DATE newVal);
	STDMETHOD(DeleteInformationBlob)(/*[in]*/ VARIANT i_varName);
	STDMETHOD(GetInformationBlob)(/*[in]*/ VARIANT i_varName, /*[out, retval]*/ VARIANT* o_pvarValue);
	STDMETHOD(SetInformationBlob)(/*[in]*/ VARIANT i_varName, /*[in]*/ VARIANT i_varValue);
	STDMETHOD(DecryptSessionKey)(/*[in]*/ VARIANT i_varEncryptedSessionKey, /*[out, retval]*/ VARIANT* o_pvarDecryptedSessionKey);
	STDMETHOD(SelIDForTrans)();
	STDMETHOD(SelIDForChallenge)();
	STDMETHOD(Close)();
	STDMETHOD(SignTransaction)(VARIANT* in_pvarMessage, VARIANT* in_pvarAlgID, VARIANT* o_pvarSignature);
	STDMETHOD(SignChallenge)(VARIANT* in_pvarChallenge, VARIANT* in_pvarAlgID, VARIANT* o_pvarSignature);
	STDMETHOD(InstallCert)(VARIANT* in_pvarCert);
	STDMETHOD(CreateCertReq)(VARIANT* in_pvarSubjectDN, VARIANT* in_pvarKeyGenFlag, VARIANT* in_pvarHashAlg, VARIANT* in_pvarAttributes,  /*[out,retval]*/VARIANT *o_pvarB64EncPKCS10);
	STDMETHOD(get_CSPName)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_CSPName)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_IVSRoamPrefs)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSSelectedDigID)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSSrchCrit)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSCertPrefs)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSProfMgmt)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSUIPrefs)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSP12Import)(/*[out, retval]*/ IDispatch* *pVal);
	STDMETHOD(get_IVSP12Export)(/*[out,retval]*/IDispatch **pVal);
	STDMETHOD(get_ProtocolName)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProtocolName)(/*[in]*/ VARIANT newVal);
	STDMETHOD(SignRenewal)( VARIANT* in_pvarAlgID, /*[out,retval]*/VARIANT* o_pvarSignature);
	STDMETHOD(InstallKeyPair)(VARIANT* i_pvarPrivKeyBlob,VARIANT* i_pvarPKCS7Cert);
	STDMETHOD(get_UseDefCertFlag)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UseDefCertFlag)(/*[in]*/ VARIANT newVal);
	STDMETHOD(AppPref_GetPreference)(VARIANT* in_pvarPrefName, VARIANT* in_pvarPrefValue);
	STDMETHOD(AppPref_SetPreference)(VARIANT* in_pvarPrefName, VARIANT* in_pvarPrefVal);
	STDMETHOD(put_ApplicationCreatorWildCard)(VARIANT newVal);
	STDMETHOD(get_ApplicationReadOKDomains)(VARIANT *o_pvarApplicationReadOKDomains);
	STDMETHOD(put_ApplicationReadOKDomains)(VARIANT newVal);
	STDMETHOD(get_ApplicationWriteOKDomains)(VARIANT *o_pvarApplicationWriteOKDomains);
	STDMETHOD(put_ApplicationWriteOKDomains)(VARIANT newVal);
	STDMETHOD(get_AmITheApplicationCreator)(VARIANT *o_pvarIsCreator);
//	STDMETHOD(get_IsThisHostTheApplicationCreator)(VARIANT *i_pvarHostName, VARIANT *o_pvarIsCreator);
	STDMETHOD(Initialize)(VARIANT* in_pvarAppCtxtName, VARIANT* in_pvarUseCapi);
	STDMETHOD(get_AuthDll)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_AuthDll)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfileIssFrndlyName)(VARIANT *pVal);
	STDMETHOD(put_ProfileIssFrndlyName)(VARIANT newVal);
	STDMETHOD(get_ProfileIssUniqueId)(VARIANT *pVal);
	STDMETHOD(put_ProfileIssUniqueId)(VARIANT newVal);
	STDMETHOD(put_AffLogoUrl)(VARIANT newVal);
	STDMETHOD(get_AffLogoUrl)(VARIANT* pVal);
    STDMETHOD(CreatePassword)();
    STDMETHOD(EnterPassword)();
	STDMETHOD(DisableNonRepudiationCertKeyUsage)();



	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

		SetTextAlign(di.hdcDraw, TA_CENTER|TA_BASELINE);
		LPCTSTR pszText = _T("ATL 3.0 : VSPTA");
		TextOut(di.hdcDraw, 
			(rc.left + rc.right) / 2, 
			(rc.top + rc.bottom) / 2, 
			pszText, 
			lstrlen(pszText));

		return S_OK;
	}

// IVSProfMgmt
	STDMETHOD(ProfMgmt_RemoveCertificates)();
	STDMETHOD(ProfMgmt_SaveProfile)();
	STDMETHOD(ProfMgmt_CloseProfile)();
	STDMETHOD(ProfMgmt_OpenProfile)();
	STDMETHOD(get_ProfMgmt_OpenProfFlags)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_OpenProfFlags)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfMgmt_AddApplicationIfItDoesNotExistFlag)(VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_AddApplicationIfItDoesNotExistFlag)(VARIANT newVal);
	STDMETHOD(get_ProfMgmt_ReadOKDomains)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_ReadOKDomains)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_WriteOKDomains)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_WriteOKDomains)(VARIANT pVal);
	STDMETHOD(put_ProfMgmt_ProfileOpenHostWildCard)(VARIANT newVal);
	STDMETHOD(get_ProfMgmt_PasswdQuality)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_PasswdQuality)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_PasswdLength)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_PasswdLength)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_PasswdTimeOut)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_PasswdTimeOut)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_PasswdLockOutTries)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_PasswdLockOutTries)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_PasswdUnLockPeriod)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_PasswdUnLockPeriod)(VARIANT pVal);
	STDMETHOD(get_ProfMgmt_ProfileName)(VARIANT * pVal);
	STDMETHOD(put_ProfMgmt_ProfileName)(VARIANT pVal);
	STDMETHOD(put_ProfMgmt_Password)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfMgmt_RoamProfile)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_RoamProfile)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfMgmt_SaveLocal)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_SaveLocal)(/*[in]*/ VARIANT newVal);
	STDMETHOD(ProfMgmt_ChangePassword)();
	STDMETHOD(get_ProfMgmt_IsUsernameEditable)(VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_IsUsernameEditable)(VARIANT newVal);

//
//	Sasi May 05, 2003		Start
//
	STDMETHOD(ProfMgmt_ResetPassword)();

//
//	Sasi May 05, 2003		End
//

//
//	Sasi Jun 05, 2003		Start
//

	STDMETHOD(get_ProfMgmt_Email)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_Email)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfMgmt_LastName)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_LastName)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_ProfMgmt_FirstName)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_ProfMgmt_FirstName)(/*[in]*/ VARIANT newVal);

//
//	Sasi Jun 05, 2003		End
//

	
// IVSUIPrefs
	STDMETHOD(get_UIPref_Language)(VARIANT * pVal);
	STDMETHOD(put_UIPref_Language)(VARIANT pVal);
	STDMETHOD(get_UIPref_TitleFont)(VARIANT * pVal);
	STDMETHOD(put_UIPref_TitleFont)(VARIANT pVal);
	STDMETHOD(get_UIPref_TextFont)(VARIANT * pVal);
	STDMETHOD(put_UIPref_TextFont)(VARIANT pVal);
	STDMETHOD(get_UIPref_BtnFont)(VARIANT * pVal);
	STDMETHOD(put_UIPref_BtnFont)(VARIANT pVal);
	STDMETHOD(get_UIPref_UILogoUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_UILogoUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_NewPasswd_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_NewPasswd_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_NewPasswd_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_NewPasswd_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_NewPasswd_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_NewPasswd_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_NewPasswd_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_NewPasswd_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_NewPasswd_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_NewPasswd_HelpUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_LgnDlg_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_LgnDlg_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_OpenProf_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_OpenProf_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_OpenProf_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_OpenProf_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_OpenProf_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_OpenProf_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_OpenProf_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_OpenProf_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_OpenProf_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_OpenProf_HelpUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_ShowDefChkBox)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_ShowDefChkBox)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_ChkBoxText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_ChkBoxText)(VARIANT pVal);
	STDMETHOD(get_UIPref_SelID_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SelID_HelpUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_SgnDlg_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_SgnDlg_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_RvwMsg_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_RvwMsg_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_RvwMsg_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_RvwMsg_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_RvwMsg_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_RvwMsg_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_RvwMsg_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_RvwMsg_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_RvwMsg_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_RvwMsg_HelpUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_IntroDlg_Title)(VARIANT *pVal);
	STDMETHOD(put_UIPref_IntroDlg_Title)(VARIANT newVal);
	STDMETHOD(get_UIPref_IntroDlg_Text)(VARIANT *pVal);
	STDMETHOD(put_UIPref_IntroDlg_Text)(VARIANT newVal);
	STDMETHOD(get_UIPref_IntroDlg_HelpUrl)(VARIANT *pVal);
	STDMETHOD(put_UIPref_IntroDlg_HelpUrl)(VARIANT newVal);
	STDMETHOD(get_UIPref_CreateNewProf_Title)(VARIANT *pVal);
	STDMETHOD(put_UIPref_CreateNewProf_Title)(VARIANT newVal);
	STDMETHOD(get_UIPref_CreatePasswd_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_CreatePasswd_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_CreatePasswd_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_CreatePasswd_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_CreatePasswd_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_CreatePasswd_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_CreatePasswd_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_CreatePasswd_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_EnterPasswd_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_EnterPasswd_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_EnterPasswd_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_EnterPasswd_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_EnterPasswd_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_EnterPasswd_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_EnterPasswd_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_EnterPasswd_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_ChangePasswd_Title)(VARIANT * pVal);
	STDMETHOD(put_UIPref_ChangePasswd_Title)(VARIANT pVal);
	STDMETHOD(get_UIPref_ChangePasswd_Text)(VARIANT * pVal);
	STDMETHOD(put_UIPref_ChangePasswd_Text)(VARIANT pVal);
	STDMETHOD(get_UIPref_ChangePasswd_OKBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_ChangePasswd_OKBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_ChangePasswd_CancelBtnText)(VARIANT * pVal);
	STDMETHOD(put_UIPref_ChangePasswd_CancelBtnText)(VARIANT pVal);
	STDMETHOD(get_UIPref_ChangePasswd_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_ChangePasswd_HelpUrl)(VARIANT pVal);
	STDMETHOD(get_UIPref_Timeout_HelpUrl)(VARIANT * pVal);
	STDMETHOD(put_UIPref_Timeout_HelpUrl)(VARIANT pVal);
	STDMETHOD(put_UIPref_EnableTopMostWindow)(VARIANT newVal);
	STDMETHOD(get_UIPref_SignTransDlgWidth)(VARIANT *pVal);
	STDMETHOD(put_UIPref_SignTransDlgWidth)(VARIANT newVal);
	STDMETHOD(get_UIPref_SignTransDlgHeight)(VARIANT *pVal);
	STDMETHOD(put_UIPref_SignTransDlgHeight)(VARIANT newVal);

//
//	Sasi May 07, 2003		Start
//
	STDMETHOD(get_UIPref_CreateSecret_CancelBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_CreateSecret_CancelBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_CreateSecret_OKBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_CreateSecret_OKBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_CreateSecret_Text)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_CreateSecret_Text)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_CreateSecret_Title)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_CreateSecret_Title)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_ResetPasswd_CancelBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_ResetPasswd_CancelBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_ResetPasswd_OKBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_ResetPasswd_OKBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_ResetPasswd_Text)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_ResetPasswd_Text)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_ResetPasswd_Title)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_ResetPasswd_Title)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_GetSecretQuestion_CancelBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_GetSecretQuestion_CancelBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_GetSecretQuestion_OKBtnText)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_GetSecretQuestion_OKBtnText)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_GetSecretQuestion_Text)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_GetSecretQuestion_Text)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_UIPref_GetSecretQuestion_Title)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_UIPref_GetSecretQuestion_Title)(/*[in]*/ VARIANT newVal);

//
//	Sasi May 07, 2003		End
//
	

// IVSCertPrefs
	STDMETHOD(get_CertPref_CertSerNum)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertSerNum)(VARIANT pVal);
	STDMETHOD(get_CertPref_CertIssDN)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertIssDN)(VARIANT pVal);
	STDMETHOD(get_CertPref_CertFrndlyName)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertFrndlyName)(VARIANT pVal);
	STDMETHOD(get_CertPref_CertLogoUrl)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertLogoUrl)(VARIANT pVal);
	STDMETHOD(get_CertPref_CertDispString)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertDispString)(VARIANT pVal);
	STDMETHOD(get_CertPref_CertTextureUrl)(VARIANT * pVal);
	STDMETHOD(put_CertPref_CertTextureUrl)(VARIANT pVal);
	STDMETHOD(get_CertPref_MarkAsRenewed)(VARIANT * pVal);
	STDMETHOD(put_CertPref_MarkAsRenewed)(VARIANT pVal);
	STDMETHOD(CertPref_SetPreference)(VARIANT * in_pvarPrefName, VARIANT * in_pvarPrefValue);
	STDMETHOD(CertPref_GetPreference)(VARIANT * in_pvarPrefName, VARIANT * in_pvarPrefValue);



// IVSSrchCrit
	STDMETHOD(get_SrchCrit_IssuerDN)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_IssuerDN)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_SubjectDN)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_SubjectDN)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_Email)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_Email)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_SerNum)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_SerNum)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_ExpDate)(DATE * pVal);
	STDMETHOD(put_SrchCrit_ExpDate)(DATE pVal);
	STDMETHOD(get_SrchCrit_EffDate)(DATE * pVal);
	STDMETHOD(put_SrchCrit_EffDate)(DATE pVal);
	STDMETHOD(get_SrchCrit_DateEquality)(VARIANT* pVal);
	STDMETHOD(put_SrchCrit_DateEquality)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_Renewed)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_Renewed)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_KeyUsage)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_KeyUsage)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_KeySize)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_KeySize)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_ExtOID)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_ExtOID)(VARIANT pVal);
	STDMETHOD(get_SrchCrit_ExtVal)(VARIANT * pVal);
	STDMETHOD(put_SrchCrit_ExtVal)(VARIANT pVal);

//IVSSelectedDigID
	STDMETHOD(get_SelectedDigID_TextureUrl)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_LogoUrl)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_FrndlyName)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_PubKeySHA1)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_PubKeyMD5)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_Renewed)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_KeySize)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_KeyUsage)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_EffDate)(/*[out, retval]*/ DATE *pVal);
	STDMETHOD(get_SelectedDigID_ExpDate)(/*[out, retval]*/ DATE *pVal);
	STDMETHOD(get_SelectedDigID_SerNum)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_SubjectDN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_SelectedDigID_IssuerDN)(/*[out, retval]*/ VARIANT *pVal);
	
//IVSRoamPrefs
	STDMETHOD(get_RoamPrefs_NumOfSrvrs)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_RoamPrefs_NumOfSrvrs)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_RoamPrefs_RoamingSrvrs)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_RoamPrefs_RoamingSrvrs)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_RoamPrefs_StorageSrvr)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_RoamPrefs_StorageSrvr)(/*[in]*/ VARIANT newVal);
	STDMETHOD(put_RoamPrefs_ClientInfo)(VARIANT newVal);
	STDMETHOD(get_RoamPrefs_ClientInfo)(VARIANT* pVal);
	STDMETHOD(put_RoamPrefs_ClientInfoSig)(VARIANT newVal);
	STDMETHOD(get_RoamPrefs_ClientInfoSig)(VARIANT* pVal);

//PTA Dll Api
	STDMETHOD(get_PTADllApi_HostFQDN)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_HostFQDN)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_Protocol)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_Protocol)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_SelectedIDCertContext)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(get_PTADllApi_DoAttachedSig)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_DoAttachedSig)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_ShowSignUI)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_ShowSignUI)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_OleClientSite)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_OleClientSite)(/*[in]*/ VARIANT newVal);

//
//	Anand	Dec 13, 2000		Start
//
	STDMETHOD(get_PTADllApi_DecryptUI)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_DecryptUI)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_SignNotificationUI)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_SignNotificationUI)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_P7Output)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_P7Output)(/*[in]*/ VARIANT newVal);
	STDMETHOD(get_PTADllApi_HashData)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_HashData)(/*[in]*/ VARIANT newVal);
//
//	Anand	Dec 13, 2000		End
//

	//
	// Sameer Oct 25 2001	Start
	//
	STDMETHOD(get_PTADllApi_ShowSelIDUI)(/*[out, retval]*/ VARIANT *pVal);
	STDMETHOD(put_PTADllApi_ShowSelIDUI)(/*[in]*/ VARIANT newVal);
	//
	// Sameer Oct 25 2001	End
	//

//PTA P12 Import
	STDMETHOD(P12Import_ImportP12)(VARIANT *in_pvarParamType, VARIANT* in_pvarPararmVal,VARIANT* o_pvarImportedIDSerNum, VARIANT* o_pvarImportedIDIssDN);

//PTA P12 Export
	STDMETHOD(P12Export_ExportP12)(VARIANT *in_pvarOutputType, VARIANT* in_pvarFlags, VARIANT* io_pvarP12OrFileName);
	STDMETHOD(get_P12Export_PasswdQuality)(VARIANT * pVal);
	STDMETHOD(put_P12Export_PasswdQuality)(VARIANT newVal);
	STDMETHOD(get_P12Export_PasswdLength)(VARIANT * pVal);
	STDMETHOD(put_P12Export_PasswdLength)(VARIANT newVal);

//Public members not available to the script
	HRESULT get_VirtualSmartCardPtr(CVirtualSmartCard** o_ppVirtualSmartCard);

/*---------------------------------------------------------------------------
***********************End of public section*******************************
------------------------------------------------------------------------------*/

private:
	PFONTSINFO _CreateFontStruct(short i_nWhichFonts);
	int		_GetFirstUIAndWizard(int i_nWizardAndUIs);
	int		_MoreThanOneUI(int i_nWizardAndUIs);
	int		_GetLastUIAndWizard(int i_nWizardAndUIs);
	// RYAN
	long	_RGBStrtoLong(char *i_rgbStr);
	boolean	_IsColorDifferenceNoticeable(_variant_t i_varForeGroundColor, _variant_t i_varBackGroundColor);
	HRESULT _CheckElement(IHTMLElement *i_pHTMLElem, _variant_t p_varBgColor);
	bool _TagNotAllowed(CComBSTR *tagName);
	bool _AttributeNotAllowed(CComBSTR *tagName);
	HRESULT	_TestHTMLDocument(IHTMLDocument2 *i_pHTMLDocument);
	HRESULT	_ValidateHTMLMessage(_bstr_t *i_pbstrHTMLMessage);
	bool	_IsAttributeOk(char *attrName);

	HRESULT _ShowOrOpenProf(OPCTXT& o_theOpctxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrSelectId(OPCTXT& o_theOpCtxt);
	HRESULT _ShowOrSignMsg(OPCTXT& io_theOpCtxt);
	HRESULT _ShowOrSetCertPref(OPCTXT& io_theOpCtxt);
	HRESULT _ShowOrGetCertPref(OPCTXT& io_theOpCtxt);
	HRESULT _ShowOrCreateCertReq(OPCTXT& io_theOpCtxt);
	HRESULT _ShowOrInstallCert(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrCreatePasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrEnterPasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrChangePasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrImportP12(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrExportP12(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrExportProfile(OPCTXT& io_theOpCtxt);
	HRESULT _ShowOrImportProfile(OPCTXT& io_theOpCtxt);

// Sasi 05/05/2003  Start

	HRESULT _ShowOrGetSecretQuestion(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrResetPasswd(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ShowOrCreateSecret(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);

// Sasi 05/05/2003  End

// Sasi 05/26/2003  Start

	HRESULT _ShowOrRemoveCertificates(OPCTXT& io_theOpCtxt);

// Sasi 05/26/2003  End


	HRESULT _HandleCreateProfile(_bstr_t** io_pptbstrProfiles, int* io_npNumOfProfiles, CVirtualSmartCard** o_pVirtualSmartCard);
	HRESULT _HandleOpenProfile(_bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles, CVirtualSmartCard** o_ppVirtualSmartCard);
	HRESULT _InstallCertsLocally(CVirtualSmartCard* i_pVirtualSmartCard);
	HRESULT _MakeCertRegistryEntry(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE pidListHead, unsigned int nCertNum);
	HRESULT _HandleCreatePasswd(CVirtualSmartCard* i_pVirtualSmartCard,BOOL i_boolOpenedWithPassword);
	HRESULT _HandleEnterPasswd(CVirtualSmartCard* i_pVirtualSmartCard,BOOL i_boolOpenedWithPassword);
	HRESULT _HandleChangePasswd(CVirtualSmartCard* i_pVirtualSmartCard,BOOL i_boolOpenedWithPassword);
	HRESULT _HandleSetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, CERTIDENTIFIER& i_theCertIdentifier, 
			_bstr_t& i_tbstrPrefName, _bstr_t i_tbstrPrefVal);
	HRESULT _HandleGetCertPref(CVirtualSmartCard* i_pVirtualSmartCard, CERTIDENTIFIER& theCertIdentifier, 
			_bstr_t& i_tbstrPrefName, _bstr_t* o_ptbstrPrefVal);
	HRESULT _HandleDeleteProfile(_bstr_t** o_pptbstrProfiles, int* o_pnNumOfProfiles);
	HRESULT _HandleSign(CVirtualSmartCard* i_pVirtualSmartCard, PIDLISTNODE i_pSelectedId, _bstr_t* o_ptbstrSignature);

// Sasi 05/05/2003  Start

	HRESULT _HandleGetSecretQuestion();
	HRESULT _HandleResetPasswd(CVirtualSmartCard** o_ppVirtualSmartCard);
	HRESULT _HandleCreateSecret();

// Sasi 05/05/2003  End


	HRESULT _GetPosLastBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPrevOp, WCHAR* i_pwszBuff, WORD i_wLangId);
	HRESULT _GetPosMiddleBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPrevOp, WCHAR* i_pwszBuff, WORD i_wLangId);
	HRESULT _GetPosSoloBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, WCHAR* i_pwszBuff, WORD i_wLangId);
	HRESULT _GetPosFirstBtnTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, WCHAR* i_pwszBuff, WORD i_wLangId);
	HRESULT _GetButtonTextAndFns(PBTNELEMS o_pBtnElems, PBTNFNS o_pBtnFns, int i_nOperation, int i_nPos);
	int _GetOperationPosInWizard(int nOperation, int nWizard);
	HRESULT _DoOperation(int i_nWhichWizard, int i_nEndOperation);
	HRESULT _DetermineWizAndUIs(OPCTXT& io_theOpCtxt, int i_nWhichWizard, int i_nEndOperation);
	HRESULT _OpenProfWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _OpenProfWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _CreateProfWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _CreateProfWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _CreatePasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _EnterPasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ChangePasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ChangePasswdWithAuthDll(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _SetPasswdWithAuthDll(int i_nUIToShow, _bstr_t* o_ptbstrTimeoutPasswd);
	HRESULT _SetPasswdWithPTAAuth(int i_nUIToShow, _bstr_t* o_ptbstrTimeoutPasswd);

// Sasi 05/05/2003  Start

	HRESULT _GetSecretQuestionWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _ResetPasswdWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);
	HRESULT _CreateSecretWithPTAAuth(OPCTXT& io_theOpCtxt, BOOL* o_pboolParamFlagsChanged);

// Sasi 05/05/2003  End

	HRESULT _InitializeUIContext(PUICTXT io_pUICtxt, int i_nWhichWizardAndUIs, int i_nOperation, _bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles,PIDLISTNODE i_pCertListHead, int i_nSelectedIdNum, BOOL i_boolOpenedWithPassword);
	void _InitializeOpenParams(OPENPROFPARAMS& i_OpenProfParams);
	void _InitializeSignParams(SIGNMSGPARAMS& i_SignMsgParams);
	void _InitializeCreateCertReqParams(CREATECERTREQPARAMS& i_CertReqParams);
	void _InitializeInstallCertParams(INSTALLCERTPARAMS& i_theInstallCertParams);
	void _InitializeSetCertPrefParams(SETCERTPREFPARAMS& i_theCertPrefParams);
	void _InitializeRoamingParams(ROAMPARAMS& i_theRoamingParams);
	void _InitializeSelIDParams(SELIDPARAMS& i_theSelIdParams);
	void _InitializeCreatePasswdParams(CREATEPASSWDPARAMS& i_theCreatePasswdParams);
	void _InitializeEnterPasswdParams(ENTERPASSWDPARAMS& i_theEnterPasswdParams);
	void _InitializeChangePasswdParams(CHANGEPASSWDPARAMS& i_theChangePasswdParams);
	void _InitializeImportP12Params(IMPORTP12PARAMS& i_theImportP12Params);
	void _InitializeExportP12Params(EXPORTP12PARAMS& i_theExportP12Params);

// Sasi 05/05/2003  Start

	void _InitializeGetSecretQuestionParams(GETSECRETQUESTIONPARAMS& i_theGetSecretQuestionParams);
	void _InitializeResetPasswdParams(RESETPASSWDPARAMS& i_theResetPasswdParams);
	void _InitializeCreateSecretParams(CREATESECRETPARAMS& i_theCreateSecretParams);

// Sasi 05/05/2003  End

//
//	Anand	Dec 15, 2000		Start
//
	void _InitializeDecryptParams(DECRYPTMSGPARAMS& i_DecryptMsgParams);
//
//	Anand	Dec 15, 2000		End
//

	HRESULT _ExtractBstrsFromArray(SAFEARRAY* i_pSafeArray, int i_nDims,int i_nNumOfElemsInDim, _bstr_t* o_ptbstrBstrArr);
	HRESULT _SetWizardElems(int i_nWhichWizard, void** o_ppvWizUIElements);
	HRESULT _SetUIElems(int i_nWhichUI, void** o_ppvUIElements, _bstr_t* i_ptbstrProfiles, int i_nNumOfProfiles, PIDLISTNODE i_pCertListHead, int i_nSelectedIdNum, BOOL i_boolOpenedWithPassword  );
	HRESULT _CheckPasswordSanity(_bstr_t& i_tbstrPassword);

	HRESULT _OpenProfCreateFn(POPCTXT pOpCtxt);
	HRESULT _SelIdFn(POPCTXT i_pOpCtxt);
	HRESULT _SelIdHelpFn(POPCTXT i_pOpCtxt);
	HRESULT _OpenProfOpenHelpFn(POPCTXT i_pOpCtxt);
	HRESULT _OpenProfCreateHelpFn(POPCTXT i_pOpCtxt);
	HRESULT _SignMsgFn(POPCTXT i_pOpCtxt);
	HRESULT _SignMsgHelpFn(POPCTXT i_pOpCtxt);
	HRESULT _IntroFn(POPCTXT i_pOpCtxt);
	HRESULT _PrevToCreateFn(POPCTXT i_pOpCtxt);
	HRESULT _PrevToIntroFn(POPCTXT i_pOpCtxt);
	HRESULT _PrevToSelIdFn(POPCTXT i_pOpCtxt);
	HRESULT _IntroDlgHelpFn(POPCTXT i_pOpCtxt);
	HRESULT _CancelFn(POPCTXT i_pOpCtxt);
	HRESULT _CreatePasswdFn(POPCTXT pOpCtxt);
	HRESULT _EnterPasswdFn(POPCTXT pOpCtxt);
	HRESULT _ChngPasswdFn(POPCTXT pOpCtxt);
	HRESULT _ChngPasswdHelpFn(POPCTXT pOpCtxt);
	HRESULT _ImportP12Fn(POPCTXT pOpCtxt);
	HRESULT _ImportP12HelpFn(POPCTXT pOpCtxt);
	HRESULT _ExportP12Fn(POPCTXT i_pOpCtxt);
	HRESULT _ExportP12HelpFn(POPCTXT pOpCtxt);
	HRESULT _PasswordCallback (int i_nUIToShow, _VS_CHAR*	o_cszPassword); 
	HRESULT _TimeoutCancelFn(POPCTXT pOpCtxt);
	HRESULT _TimeoutFn(POPCTXT pOpCtxt);
	HRESULT _TimeoutHelpFn(POPCTXT pOpCtxt);
	HRESULT _ExportProfileFn(POPCTXT pOpCtxt);
	HRESULT _ImportProfileFn(POPCTXT pOpCtxt);

// Sasi 05/05/2003  Start

	HRESULT _GetSecretQuestionFn(POPCTXT pOpCtxt);
	HRESULT _PrevToGetSecretQuestionFn(POPCTXT i_pOpCtxt);
	HRESULT _ResetPasswdFn(POPCTXT pOpCtxt);
	HRESULT _CreateSecretFn(POPCTXT pOpCtxt);

// Sasi 05/05/2003  End

	HRESULT _CreateChallengeToBeSigned(_bstr_t& i_tbstrChallenge,PBYTE o_pbyteMessage, int* o_pnMsgToSignSize);
	HRESULT _GetPasswdQualityString(_bstr_t* o_ptbstrPasswdQualString);

	friend HRESULT OpenProfCreateFn(POPCTXT pOpCtxt);
	friend HRESULT OpenProfCreateHelpFn(POPCTXT pOpCtxt);
	friend HRESULT OpenProfOpenFn(POPCTXT pOpCtxt);
	friend HRESULT OpenProfOpenHelpFn(POPCTXT pOpCtxt);
	friend HRESULT SelIdFn(POPCTXT pOpCtxt);
	friend HRESULT SelIdHelpFn(POPCTXT pOpCtxt);
	friend HRESULT SignMsgFn(POPCTXT pOpCtxt);
	friend HRESULT SignMsgHelpFn(POPCTXT pOpCtxt);
	friend HRESULT PrevToCreateFn(POPCTXT pOpCtxt);
	friend HRESULT PrevToOpenFn(POPCTXT pOpCtxt);
	friend HRESULT PrevToSelIdFn(POPCTXT pOpCtxt);
	friend HRESULT CancelFn(POPCTXT pOpCtxt);
	friend HRESULT IntroFn(POPCTXT pOpCtxt);
	friend HRESULT PrevToIntroFn(POPCTXT pOpCtxt);
	friend HRESULT IntroDlgFn(POPCTXT pOpCtxt);
	friend HRESULT PasswordCallback (void* i_pvoidPTAObj, void* i_pvoidPointer, _VS_CHAR*	o_cszPassword);
	friend HRESULT CreatePasswdFn(POPCTXT pOpCtxt);
	friend HRESULT EnterPasswdFn(POPCTXT pOpCtxt);
	friend HRESULT ChngPasswdFn(POPCTXT pOpCtxt);
	friend HRESULT ChngPasswdHelpFn(POPCTXT pOpCtxt);
	friend HRESULT TimeoutCancelFn(POPCTXT pOpCtxt);
	friend HRESULT TimeoutFn(POPCTXT pOpCtxt);
	friend HRESULT TimeoutHelpFn(POPCTXT pOpCtxt);
	friend HRESULT ImportP12Fn(POPCTXT pOpCtxt);
	friend HRESULT ImportP12HelpFn(POPCTXT pOpCtxt);
	friend HRESULT ExportP12Fn(POPCTXT pOpCtxt);
	friend HRESULT ExportP12HelpFn(POPCTXT pOpCtxt);
	friend HRESULT ExportProfileFn(POPCTXT pOpCtxt);
	friend HRESULT ImportProfileFn(POPCTXT pOpCtxt);

// Sasi 05/05/2003  Start

	friend HRESULT GetSecretQuestionFn(POPCTXT pOpCtxt);
	friend HRESULT GetSecretQuestionHelpFn(POPCTXT pOpCtxt);
	friend HRESULT PrevToGetSecretQuestionFn(POPCTXT pOpCtxt);
	friend HRESULT ResetPasswdFn(POPCTXT pOpCtxt);
	friend HRESULT ResetPasswdHelpFn(POPCTXT pOpCtxt);
	friend HRESULT CreateSecretFn(POPCTXT pOpCtxt);
	friend HRESULT CreateSecretHelpFn(POPCTXT pOpCtxt);

// Sasi 05/05/2003  End
	
	/**********************************************************
	************************Members****************************
	***********************************************************/
	bool m_bInitialized;
	CPtaUI* m_pPtaUI;
	CPtaEngine* m_pPtaEngine;
	PAPPCTXT m_pAppCtxt;
	PIDLISTNODE m_pSelectedId;
	BOOL m_boolUserHasSeenMsg;
	BOOL m_boolIdSatisfiesSrchCrit;
	_bstr_t m_tbstrSignature;
	_bstr_t m_tbstrCertReq;
	_bstr_t m_tbstrCertPref;
//	_bstr_t *forbiddenTags;
	_bstr_t *allowedTags;
	_bstr_t *allowedAttrs;
	int nbOfAllowedTags;
	int nbOfAllowedAttrs;
	_variant_t htmlDocFGColor;
	
	/**********************************************************
	************************Methods****************************
	***********************************************************/
	
	IDispatch* GetInterface(REFIID refIid);
	void _SetErrorInfo(HRESULT hresultErr);
	HRESULT _GetHostAndProtocol(_bstr_t& tbstrHostName, _bstr_t& tbstrProtocolName);
	HRESULT _RestoreSrchCrit();
	HRESULT _CheckAffLogoUrlSanity(_bstr_t& i_tbstrAffLogoUrl);
	
	PAPPCTXT _CreateAppCtxt();
	int _InitializeUiPrefs(UIPREF& theUIPrefs);
	BOOL _InitializeDefUiPrefs(UIPREF& theUIPrefs);
	void _InitializeSrchCrit(SRCHCRIT& theSrchCrit);
	void _InitializeCertIdentifier(CERTIDENTIFIER& theCertIdentifier);
	HRESULT _GetFonts(WORD wLangID, _bstr_t& tbstrTitleFont, _bstr_t& tbstrTextFont, _bstr_t& tbstrBtnFont);
	WORD _GetDefaultLangID();
	int _FreeAppCtxt(PAPPCTXT in_pAppCtxt);
	HRESULT _CheckEnvironment(short nCheckWhat);
	HRESULT _ChangeSmartCardHost(BSTR bstrHostName, BSTR bstrAppCtxtName);
//	bool IsThisDomainAllowedToRead(const _bstr_t i_tbstrHostName);
//	bool IsThisDomainAllowedToWrite(const _bstr_t i_tbstrHostName);
//	HRESULT IsThisDomainAllowedToReadThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication);
//	HRESULT IsThisDomainAllowedToWriteThisApplication(const _bstr_t i_tbstrHostName, bool *o_pboolAllowedApplication);

	HRESULT _SaveSrchCrit();

	HRESULT _CheckForInfineonTPM(BOOL* boolExists);

	CComPtr <IOleClientSite> m_spOuterClientSite;
	
	

	//int _FreeDataStructure(short inWhichDS, void* in_pDataStructure);

	//This function creates a ui object
	CPtaUI* _CreateUiObject()
	{
		return (CPtaUI*)new(CPtaUI);
	}

	int _DeleteUiObject(CPtaUI* in_pPtaUiObj)
	{
		delete(in_pPtaUiObj);
		return 1;
	}

	

};




#endif //__VSPTA_H_
