// PTAUI.cpp : Implementation of CPTAUI
#include "stdafx.h"
#include "..\Include\PtaUI.h"
#include "..\Include\ptaerrs.h"
#include "..\Include\utils.h"
#include "..\Include\ptadefines.h"
#include "..\Include\langutils.h"

#include <winuser.h>
#include <assert.h>
#include <commctrl.h>


/////////////////////////////////////////////////////////////////////////////
// CPTAUI

HRESULT CPtaUI::Initialize()
{
	return S_OK;
}

HRESULT CPtaUI::Close()
{
	return S_OK;
}

HRESULT CPtaUI::put_UIContext(PUICTXT i_pUICtxt)
{
	HRESULT retVal = S_OK;
	if(m_pUICtxt)
	{
		_FreeUIContext(m_pUICtxt);
		delete(m_pUICtxt);
		m_pUICtxt = NULL;
	}

	if(i_pUICtxt)
	{
		m_pUICtxt = _CreateUIContext();
		retVal = _CopyUIContext(m_pUICtxt,i_pUICtxt);
	}

	return retVal;
}

HRESULT CPtaUI::get_UIContext(PUICTXT o_pUICtxt)
{
	HRESULT retVal = S_OK;
	retVal = _CopyUIContext(o_pUICtxt,m_pUICtxt);
	return retVal;
}

HRESULT CPtaUI::ShowUI(POPCTXT pOpCtxt)
{
	HRESULT retVal;
	//Store the op context so that other functions can use it.
	m_pOpCtxt = pOpCtxt;

	//Call DoModal
	retVal = DoModal();
	
	if(retVal == IDOK)
		retVal = S_OK;

	//Reset the op context
	m_pOpCtxt = NULL;
	return retVal;
}


HRESULT CPtaUI::ShowMessage(int i_nMessageType)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToDisp = "";
	WCHAR wcharMsg[MAX_RES_STRING_SIZE];
	int nMsgId = 0;

	switch(i_nMessageType)
	{
	case (E_INVALIDPASSWD & 0x0000FFFF) :
		nMsgId = IDS_INVALIDPASSWDMSG;
		break;
	case OPEN_PROF_DOES_NOT_EXIST :
		nMsgId = IDS_PROFILEDOESTNOTEXISTMSG;
		break;

	case CREATE_PROF_EXISTS:
		nMsgId = IDS_PROFILEEXISTMSG;
		break;

	case (E_CONFIRMPASSWORDNOMATCH & 0x0000FFFF):
		nMsgId = IDS_CONFIRMPASSWORDNOMATCH;
		break;

	case INSTALLCERT_PROFILE_NOT_CORRECT:
		nMsgId = IDS_INSTALLCERTPROFNOTCORRECT;
		break;

	case (E_PROFLOCKEDOUT & 0x0000FFFF) :
		nMsgId = IDS_PROFLOCKEDOUTMSG;
		break;

	case SHOW_SET_MSG :
		nMsgId = -1;
		break;

	case FILE_EXISTS :
		nMsgId = IDS_FILEEXISTS;
		break;
	
	case INVALID_PATH:
		nMsgId = IDS_INVALID_PATH;
		break;

	case (E_GETSECRET_PROFILEREQD & 0x0000FFFF):
		nMsgId = IDS_GETSECRET_PROFILEREQD;
		break;

	case (E_GETSECRET_PROFDOESNOTEXIST & 0x0000FFFF):
		nMsgId = IDS_GETSECRET_PROFDOESNOTEXIST;
		break;

	case (E_RESETPASSWD_ANSWERPASSWDREQD & 0x0000FFFF):
		nMsgId = IDS_RESETPASSWD_ANSWERPASSWDREQD;
		break;

	case (E_RESETPASSWD_WRONGANSWER & 0x0000FFFF):
		nMsgId = IDS_RESETPASSWD_WRONGANSWER;
		break;

	case (E_RESETPASSWD_PROFLOCKOUT & 0x0000FFFF):
		nMsgId = IDS_RESETPASSWD_PROFLOCKOUT;
		break;

	case (E_CREATESECRET_SECRETREQD & 0x0000FFFF):
		nMsgId = IDS_CREATESECRET_SECRETREQD;
		break;
	}
	
	if(nMsgId)
	{
		if(nMsgId == -1)
			tbstrMessageToDisp = m_tbstrMsgToShow;
		else
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nMsgId,wcharMsg,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrMessageToDisp = (WCHAR*)wcharMsg;
			}
		}

		if(retVal == S_OK)
		{	
			MessageBox(tbstrMessageToDisp, "VeriSign Personal Trust Agent Error", MB_OK|MB_ICONEXCLAMATION);
		}
	}
	
	return retVal;;
}

HRESULT CPtaUI::ConfirmAction(int i_nActionType)
{
	HRESULT retVal = S_OK;
	int nMsgId = 0;
	_bstr_t tbstrMessageToDisp = "";
	WCHAR wcharMsg[MAX_RES_STRING_SIZE];

	switch(i_nActionType)
	{
	case OPEN_PROF_CREATE:
		nMsgId = IDS_CNFRMACTIONCREATE;
		break;

	case CREATE_PROF_DELETE :
		nMsgId = IDS_CNFRMACTIONDELETE;
		break;

	case CREATE_PROF_OPEN :
		nMsgId = IDS_CNFRMACTIONOPEN;
		break;

	case PATH_DOESNOT_EXIST :
		nMsgId = IDS_CNFRMACTIONNEWPATH;
		break;

	default :
		retVal = E_INVALIDARGS;
		break;
	}

	if(retVal == S_OK)
	{
		if(nMsgId)
		{
			
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nMsgId,wcharMsg,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrMessageToDisp = (WCHAR*)wcharMsg;
			}
	
			if(retVal == S_OK)
			{	
				retVal = MessageBox(tbstrMessageToDisp, "VeriSign Personal Trust Agent Confirmation", MB_YESNO|MB_ICONQUESTION);
				if(retVal == IDYES)
					retVal = S_OK;
				else
					retVal = E_USERCANCELLED;
			}
		}
	}
	return retVal;
}

LRESULT CPtaUI::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*Do the setup*/
	_DoSetup();
//#ifndef _DEBUG
	if(m_pUICtxt->bShowTopMost)
		SetWindowPos(HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
	else
		SetWindowPos(HWND_TOP,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
//#endif
	return 1;  // Let the system set the focus
}


HRESULT CPtaUI::_DoSetup()
{
	HRESULT retVal = S_OK;

	
	
	/*Create fonts*/
	if(retVal == S_OK)
	{
		retVal = _CreateFonts();
	}

	/*Set the header*/
	if(retVal == S_OK)
	{
		retVal = _SetHeader();
	}

	if(retVal == S_OK)
	{
		
		/*Set the ui elements depending upon the type of ui*/
		// Sasi 05/05/03
		// Added new case statements to setup ui for GetSecretQuestion, ResetPassword and CreateSecret dialogs
		switch(m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS))
		{
		case OPENPROF_OPEN_BASE :
			retVal = _SetOpenUI(TRUE);
			break;

		case OPENPROF_CREATE_BASE :
			retVal = _SetOpenUI(FALSE);
			break;

		case SELID_BASE :
			retVal = _SetSelectUI();
			break;

		case SIGNMSG_BASE :
			retVal = _SetSignUI();
			break;

		case INTRO_BASE :
			retVal = _SetIntroUI();
			break;

		case CREATEPASSWD_BASE :
			retVal = _SetCreatePasswdUI();
			break;

		case ENTERPASSWD_BASE :
			retVal = _SetEnterPasswdUI();
			break;

		case CHANGEPASSWD_BASE :
			retVal = _SetChangePasswdUI();
			break;

		case IMPORTP12_BASE :
			retVal = _SetImportP12UI();
			break;

		case EXPORTP12_BASE :
			retVal = _SetExportP12UI();
			break;

		case RESETPASSWD_BASE :
			retVal = _SetResetPasswdUI();
			break;

		case CREATESECRET_BASE :
			retVal = _SetCreateSecretUI();
			break;

		case GETSECRETQUESTION_BASE :
			retVal = _SetGetSecretQuestionUI();
			break;

		default :
			retVal =  E_INVALIDFLAGS;
		}
	}

	/*Determine and set the dialog size*/
	retVal = _SetDialogDims();

	/*Set the separators at the correct position*/
	if(retVal == S_OK)
	{
		retVal = _SetSeparators();
	}

	/*Set the buttons*/
	if(retVal == S_OK)
	{
		retVal = _SetButtons();
	}
	
	/*Set the verisign logo*/
	if(retVal == S_OK)
	{
		retVal = _SetVRSNLogo();
	}

	return retVal;
}

HRESULT CPtaUI::_SetDialogDims()
{
	HRESULT retVal = S_OK;

	//Obtain the difference between the client rect and 
	//the window rect
	RECT rectWindowRect;
	RECT rectClientRect;

	GetWindowRect(&rectWindowRect);
	GetClientRect(&rectClientRect);

	rectWindowRect.bottom -= rectWindowRect.top;
	rectWindowRect.top = 0;

	rectClientRect.bottom -= rectClientRect.top;
	rectClientRect.top = 0;

	if(m_pUICtxt->nWhichWizardAndUI & WIZARD_BITS) //If this is a wizard
	{
		if(m_pUICtxt->nWhichWizardAndUI  & OPENPROF_BASE ||m_pUICtxt->nWhichWizardAndUI  & INTRO_BASE 
			|| m_pUICtxt->nWhichWizardAndUI  & EXPORTP12_BASE || m_pUICtxt->nWhichWizardAndUI  & GETSECRETQUESTION_BASE) //Since this is a open  make the size equal to the small dialog size
		{
			if(!SetWindowPos(NULL,0,0,(DLGSIZE_SMALL_CX), (DLGSIZE_SMALL_CY)+(rectWindowRect.bottom - rectClientRect.bottom), SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
			m_nCYSet = (DLGSIZE_SMALL_CY);
			
		}
		else if(m_pUICtxt->nWhichWizardAndUI  & SELID_BASE) //This is a select - if the size of the ui so far is less than 
		{													//dlgsmall size then make it equal to dlgsmall size
			if(m_nUISize < (DLGSIZE_SMALL_CY-DLG_FOOTER_SIZE))
			{
				//Set the window size to small
				if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, DLGSIZE_SMALL_CY+(rectWindowRect.bottom - rectClientRect.bottom), SWP_NOMOVE|SWP_NOZORDER))
					retVal = E_DLG_SETDIMSFAILED;
				m_nCYSet = DLGSIZE_SMALL_CY;
			}
			else
			{
				//Set the window size to small
				if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, m_nUISize+DLG_FOOTER_SIZE+(rectWindowRect.bottom - rectClientRect.bottom), SWP_NOMOVE|SWP_NOZORDER))
					retVal = E_DLG_SETDIMSFAILED;
				m_nCYSet = m_nUISize+DLG_FOOTER_SIZE;
			}
			
		}
		
	}
	else
	{
		
		if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, m_nUISize+DLG_FOOTER_SIZE+rectWindowRect.bottom-rectClientRect.bottom , SWP_NOMOVE|SWP_NOZORDER))
			retVal = E_DLG_SETDIMSFAILED;
		/*
		if((m_pUICtxt->nWhichWizardAndUI  & SELID_BASE) &&    //If this is a select id ui and there is more than one cert
			(((PALL_SELID_UIELEMENTS)(m_pUICtxt->pvUIElements))->pCertListHead->pidlistnodeNext != NULL))
		{
			//Set the window size to large
			if(!SetWindowPos(NULL,0,0,DLGSIZE_LARGE_CX, DLGSIZE_LARGE_CY, SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
		}
		else if((m_pUICtxt->nWhichWizardAndUI  & OPENPROF_CREATE_BASE)) //If this is a create ui
		{
			//Set the window size to that for create profile
			if(!SetWindowPos(NULL,0,0,DLGSIZE_CX, DLGSIZE_CREATEPROF_CY, SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
		}
		else if((m_pUICtxt->nWhichWizardAndUI  & OPENPROF_CREATE_BASE)) //If this is a open ui
		{
			//Set the window size to that for create profile
			if(!SetWindowPos(NULL,0,0,DLGSIZE_CX, DLGSIZE_OPENPROF_CY, SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
		}
		else
		{
			//Set the window size to large
			if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, DLGSIZE_SMALL_CY, SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
		}
		*/
	}

	if(m_pUICtxt->nWhichWizardAndUI  & SIGNMSG_BASE)
	{
		PALL_REVWMSG_UIELEMENTS pAllRvwMsgUIElems = (PALL_REVWMSG_UIELEMENTS)m_pUICtxt->pvUIElements;
		SHORT nDlgWidth = 0, nDlgHeight = 0;

		if(pAllRvwMsgUIElems->nSignTransDlgWidth <= 0 || pAllRvwMsgUIElems->nSignTransDlgWidth < DLGSIZE_SMALL_CX)
			nDlgWidth = DLGSIZE_SMALL_CX;
		else
			nDlgWidth = pAllRvwMsgUIElems->nSignTransDlgWidth;

		if(pAllRvwMsgUIElems->nSignTransDlgHeight <= 0 || pAllRvwMsgUIElems->nSignTransDlgHeight < DLGSIZE_LARGE_CY)
			nDlgHeight = DLGSIZE_LARGE_CY;
		else
			nDlgHeight = pAllRvwMsgUIElems->nSignTransDlgHeight;


		if(!SetWindowPos(NULL,0,0,nDlgWidth,nDlgHeight,SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
		m_nCYSet = m_nUISize+DLG_FOOTER_SIZE;
	}

	CenterWindow();
	
	return retVal;
}

HRESULT CPtaUI::_SetSeparators()
{
	HRESULT retVal = S_OK;

	//Obtain the dimension of the dialog box
	RECT rectDlgDims;
	int nDlgHeight;
	int nDlgWidth;

	GetClientRect(&rectDlgDims);
	nDlgHeight = rectDlgDims.bottom - rectDlgDims.top;
	nDlgWidth = rectDlgDims.right - rectDlgDims.left;

	//Set the position of the header separator
	if(!::SetWindowPos(GetDlgItem(IDC_TOP_SEPARATOR),NULL,0,m_nHeaderSize,0,0,
		SWP_NOZORDER|SWP_NOSIZE))
	{
		retVal = E_SEP_SETPOSFAILED;
	}
	else
	{
		//Set the position of the footer separator
		if(!::SetWindowPos(GetDlgItem(IDC_BOTTOM_SEPARATOR),NULL,0,nDlgHeight-DLG_FOOTER_SIZE,0,0,
			SWP_NOZORDER|SWP_NOSIZE))
		{
			retVal = E_SEP_SETPOSFAILED;
		}
	}

	return retVal;
}

HRESULT CPtaUI::_CreateFonts()
{

	if(m_boolFontsSet)
		return S_OK;

	//Obtain the sizes of the title,text and button fonts
	HDC hDC;
	HFONT hFontOrig, hFontDef;

	hDC = GetDC();
	if(!hDC)
	{
		return E_DLG_GETDCFAILED;
	}

	SIZE dlgFontSize;

	hFontDef = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
	
	hFontOrig = (HFONT)::SelectObject(hDC, hFontDef); //do this so that we can measure the size
													  //of the field
	
	if(!GetTextExtentPoint32(hDC,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 52,&dlgFontSize))
	{
		return E_FIELD_GETTEXTEXTENTFAILED;
	}

	hFontDef = (HFONT)::SelectObject(hDC, hFontOrig); //reselect the original font into the field
	m_nDefWizTitleFontSize = m_nCustWizTitleFontSize = (int)(1.2 * dlgFontSize.cy);
	m_nDefUITitleFontSize = m_nCustUITitleFontSize = dlgFontSize.cy;
	m_nDefTextFontSize = m_nCustTextFontSize = dlgFontSize.cy;
	m_nDefBtnFontSize = m_nCustBtnFontSize = dlgFontSize.cy;
	m_nCertInfoFontSize = 13;//CERT_INFO_FONT_SIZE;
	m_nValidityLabelFontSize = CERT_VALIDITYLBL_FONT_SIZE;

	//Create the X and Y multiplier
	lXMult = (double)dlgFontSize.cx / 323.0;
	lYMult = (double)dlgFontSize.cy / 13.0 ; 

	//Create the default wizard title font
	m_hFontDefWizTitleFont = _CreateFont(m_pUICtxt->pfontInfoDefaultFonts->dwCharset,
		m_pUICtxt->pfontInfoDefaultFonts->tbstrTitleFont, m_nDefWizTitleFontSize, FW_BOLD, &m_nDefWizTitleFontSize);
	if(!m_hFontDefWizTitleFont)
		return E_DEFWIZTITLEFONTFAIL;

	//Create the default ui title font
	m_hFontDefUITitleFont = _CreateFont(m_pUICtxt->pfontInfoDefaultFonts->dwCharset,
		m_pUICtxt->pfontInfoDefaultFonts->tbstrTitleFont,m_nDefUITitleFontSize, FW_BOLD, &m_nDefUITitleFontSize);
	if(!m_hFontDefUITitleFont)
		return E_DEFUITITLEFONTFAIL;

	//Create the default text font
	m_hFontDefTextFont = _CreateFont(m_pUICtxt->pfontInfoDefaultFonts->dwCharset,
		m_pUICtxt->pfontInfoDefaultFonts->tbstrTextFont, m_nDefTextFontSize, FW_NORMAL, &m_nDefTextFontSize);
	if(!m_hFontDefTextFont)
		return E_DEFUITEXTFONTFAIL;

	//Create the default button font
	m_hFontDefBtnFont =  _CreateFont(m_pUICtxt->pfontInfoDefaultFonts->dwCharset,
		m_pUICtxt->pfontInfoDefaultFonts->tbstrBtnFont, m_nDefBtnFontSize, FW_NORMAL, &m_nDefBtnFontSize);
	if(!m_hFontDefBtnFont)
		return E_DEFUITITLEFONTFAIL;

	//Create the custom wizard title font
	m_hFontCustWizTitleFont = _CreateFont(m_pUICtxt->pfontInfoCustomFonts->dwCharset,
		m_pUICtxt->pfontInfoCustomFonts->tbstrTitleFont, m_nCustWizTitleFontSize, FW_BOLD, &m_nCustWizTitleFontSize);
	if(!m_hFontCustWizTitleFont)
		return E_CUSTWIZTITLEFONTFAIL;

	//Create the custom ui title font
	m_hFontCustUITitleFont = _CreateFont(m_pUICtxt->pfontInfoCustomFonts->dwCharset,
		m_pUICtxt->pfontInfoCustomFonts->tbstrTitleFont, m_nCustUITitleFontSize, FW_BOLD, &m_nCustUITitleFontSize);
	if(!m_hFontCustUITitleFont)
		return E_CUSTUITITLEFONTFAIL;

	//Create the custom text font
	m_hFontCustTextFont = _CreateFont(m_pUICtxt->pfontInfoCustomFonts->dwCharset,
		m_pUICtxt->pfontInfoCustomFonts->tbstrTextFont, m_nCustTextFontSize, FW_NORMAL, &m_nCustTextFontSize);
	if(!m_hFontCustTextFont)
		return E_CUSTUITEXTFONTFAIL;

	//Create the custom button font
	m_hFontCustBtnFont =  _CreateFont(m_pUICtxt->pfontInfoCustomFonts->dwCharset,
		m_pUICtxt->pfontInfoCustomFonts->tbstrBtnFont, m_nCustBtnFontSize, FW_NORMAL, &m_nCustBtnFontSize);
	if(!m_hFontCustBtnFont)
		return E_CUSTUITITLEFONTFAIL;

	//Create the cert info font
	m_hFontCertInfoFont = _CreateFont(/*ANSI_CHARSET*/m_pUICtxt->pfontInfoDefaultFonts->dwCharset,_bstr_t(CERT_INFO_FONT_NAME),m_nCertInfoFontSize,FW_BOLD,&m_nCertInfoFontSize);
	if(!m_nCertInfoFontSize)
		return E_CERTINFOFONTFAIL;
	m_boolFontsSet = TRUE;

	//Create the cert validity label font
	m_hFontValidityLabelFont = _CreateFont(/*ANSI_CHARSET*/m_pUICtxt->pfontInfoDefaultFonts->dwCharset,_bstr_t(CERT_VALIDITYLBL_FONT_NAME),m_nValidityLabelFontSize,FW_NORMAL,&m_nValidityLabelFontSize);
	if(!m_nValidityLabelFontSize)
		return E_CERTVALIDLITYLBLFONTFAIL ;
	
	m_boolFontsSet = TRUE;

	return S_OK;
}

HFONT CPtaUI::_CreateFont(int i_nCharset,_bstr_t& i_tbstrFontName, int i_nFontSize, int i_nFontWeight, int* o_pnActFontHeight)
{
	LOGFONT logFontStruct;
	HFONT hFontRetVal = NULL;
	BOOL boolDone = FALSE;
	SIZE sizeFontSize;
	HFONT hFontOrig;
	HDC hDC = GetDC();
		
	do
	{
		logFontStruct.lfCharSet = i_nCharset;
		lstrcpy(logFontStruct.lfFaceName, (TCHAR*)i_tbstrFontName);
		logFontStruct.lfHeight =  i_nFontSize;
		logFontStruct.lfWeight = i_nFontWeight;
		logFontStruct.lfWidth = 0; 
		logFontStruct.lfEscapement = 0; 
		logFontStruct.lfOrientation = 0 ; 
		logFontStruct.lfItalic = FALSE; 
		logFontStruct.lfUnderline = FALSE; 
		logFontStruct.lfStrikeOut = FALSE; 
		logFontStruct.lfOutPrecision = 0; 
		logFontStruct.lfClipPrecision = 0; 
		logFontStruct.lfQuality = 0; 
		logFontStruct.lfPitchAndFamily = 0; 
		
		hFontRetVal = CreateFontIndirect(&logFontStruct) ;

		//Calculate the actual height of the font
		hFontOrig = (HFONT)SelectObject(hDC,hFontRetVal);
		GetTextExtentPoint32(hDC,"Temp",4,&sizeFontSize);
		SelectObject(hDC,hFontOrig);

		if(sizeFontSize.cy < i_nFontSize)
		{
			DeleteObject(hFontRetVal);
			i_nFontSize++;
		}
		else
			boolDone = TRUE;
	}while(!boolDone);

	if(o_pnActFontHeight)
		*o_pnActFontHeight = sizeFontSize.cy;

	return hFontRetVal;
}


HRESULT CPtaUI::_SetHeader()
{
	HRESULT retVal = S_OK;
	SHORT nWidth = 0;
	UINT nOperation = 0;

	//If the header has already been set, we dont need to do anything.
	if(m_nCurrWiz >= 0)
		return S_OK;

	nOperation = m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS;

	if(nOperation == SIGNMSG_BASE)
	{

		PALL_REVWMSG_UIELEMENTS pAllRvwMsgUIElems = (PALL_REVWMSG_UIELEMENTS)m_pUICtxt->pvUIElements;
		
		if(pAllRvwMsgUIElems->nSignTransDlgWidth <= 0 || pAllRvwMsgUIElems->nSignTransDlgWidth < DLGSIZE_SMALL_CX)
			nWidth = DLGSIZE_SMALL_CX;
		else
			nWidth = pAllRvwMsgUIElems->nSignTransDlgWidth;
		
		::InvalidateRect(m_hWnd, NULL, TRUE);
	}
	else
		nWidth = DLGSIZE_SMALL_CX;
	
	/*Obtain the logo bitmap*/
	if(m_pUICtxt->tbstrCustLogoUrl.length())
		retVal = _GetBitmap(m_pUICtxt->tbstrCustLogoUrl,&m_hBitmap);
	else
		retVal = _GetBitmap(m_pUICtxt->tbstrDefLogoUrl,&m_hBitmap);

	/*Set the logo bitmap*/
	if(retVal == S_OK)
	{
		// Get dimensions of the header bitmap in order to place it properly on the dialog
		BITMAP bm;
		if(GetObject(m_hBitmap, sizeof(BITMAP), (LPSTR)&bm) == 0)
			retVal = S_FALSE;
		else
		{
			/*Place the bitmap*/
			retVal = _SetField_PlacementInRegion(IDC_HEADER_LOGO,bm.bmWidth,bm.bmHeight,0,HEADER_RIGHT_MARGIN,
				HEADER_TOPBTM_MARGIN,HEADER_TOPBTM_MARGIN,bm.bmWidth,bm.bmHeight+(HEADER_TOPBTM_MARGIN*2),nWidth - bm.bmWidth-HEADER_RIGHT_MARGIN,0,RGN_ANCH_TOPLEFT,
				FLD_XANCH_LEFT, FLD_YANCH_TOP,NULL,&m_nHeaderSize);
		}

		if(retVal == S_OK)
			::ShowWindow(GetDlgItem(IDC_HEADER_LOGO),TRUE);
	}

/*
#ifdef DEBUG
	//For debug purposes if the logo cannot be rendered show the error message box
	if(retVal != S_OK)
	{
		TCHAR tstrErrMsg[1024];
		_stprintf(tstrErrMsg,"Error %d occured while rendering the logo", retVal);
		MessageBox(tstrErrMsg);
	}

#endif
*/	
	if(retVal != S_OK)
	{
		//An error occured while rendering the logo, so we need to 
		//make sure that the header size is correct
		m_nHeaderSize = DLG_HEADER_SIZE;
		retVal = S_OK;
	}

	/******** Set the header ***********/
	if(retVal == S_OK)
	{
		//If the current ui is part of a wizard, the header will contain the
		//wizard title, else it will contain the ui header.
		// Added code to set the proper header for ResetPassword and CreateSecret Dialogs - Sasi 05/05/03
		switch(m_pUICtxt->nWhichWizardAndUI & WIZARD_BITS)
		{
		case NO_WIZARD_BASE :
			switch(m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS)
			{
			case OPENPROF_BASE :
				if(((PALL_OPENPROF_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_OPENPROF_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_OPENPROF_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
				break;

			case SELID_BASE :
				if(((PALL_SELID_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_SELID_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_SELID_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
	
				break;

			case SIGNMSG_BASE :
				if(((PALL_REVWMSG_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_REVWMSG_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_REVWMSG_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
	
				break;

			case CREATEPASSWD_BASE :
				if(((PALL_CREATEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_CREATEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_CREATEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
			break;

			case ENTERPASSWD_BASE :
				if(((PALL_ENTERPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_ENTERPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_ENTERPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
			break;

			case CHANGEPASSWD_BASE :
				if(((PALL_CHANGEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_CHANGEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_CHANGEPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
			break;

			case IMPORTP12_BASE :
				if(((PALL_IMPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_IMPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_IMPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
				break;

			case EXPORTP12_BASE :
				if(((PALL_EXPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_EXPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_EXPORTP12_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
				break;

			case RESETPASSWD_BASE :
				if(((PALL_RESETPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_RESETPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_RESETPASSWD_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
			break;

			case CREATESECRET_BASE :
				if(((PALL_CREATESECRET_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_CREATESECRET_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_CREATESECRET_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
			break;

			default :
				retVal = E_INVALIDFLAGS;
				break;
			}
			//If a custom title is specified use that, or use the default
			
			break;

		case LOGIN_WIZARD_BASE:
		case SIGN_WIZARD_BASE :
		case CREATE_WIZARD_BASE :	
		case IMPORTP12_WIZARD_BASE :
		case EXPORTP12_WIZARD_BASE :
		case EXPORTPROFILE_WIZARD_BASE :
		case IMPORTPROFILE_WIZARD_BASE :
			//If a custom title is specified use that, or use the default
			if(((PALLWIZARDELEMENTS)(m_pUICtxt->pvWizardElems))->theCustWizardElems.tbstrWizTitle.length())
			{
				//Set the font and the text for this field
				retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
										((PALLWIZARDELEMENTS)(m_pUICtxt->pvWizardElems))->theCustWizardElems.tbstrWizTitle);
				
			}
			else
			{
				retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
										((PALLWIZARDELEMENTS)(m_pUICtxt->pvWizardElems))->theDefWizardElems.tbstrWizTitle);
			}
			break;

			

		default :
			retVal = E_INVALIDFLAGS;
			break;
		}

		//Place the header title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_HEADER_TITLE,(nWidth - HEADER_LEFT_MARGIN),
						(m_nHeaderSize - (HEADER_TOPBTM_MARGIN*2)),HEADER_LEFT_MARGIN,0,
						HEADER_TOPBTM_MARGIN,HEADER_TOPBTM_MARGIN,0,m_nHeaderSize,0,0,RGN_ANCH_TOPLEFT,
						FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,NULL);
		}
	}

	//Set the current wizard
	if(retVal == S_OK)
		m_nCurrWiz = m_pUICtxt->nWhichWizardAndUI & WIZARD_BITS;
	
	_FreeBitmap(m_hBitmap);
	m_hBitmap = 0;

	return retVal;
}


HRESULT CPtaUI::_SetField_FontAndText(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth, int i_nWidth, int i_nHeight, int i_nTopBtmMargin, int i_nInterCharSpace)
{
	HDC hDC;
	HWND hWnd;
	HFONT hFontOrig;

	hWnd = GetDlgItem(i_nFieldId);
	if(!hWnd)
	{
		return E_FIELD_GETDLGITEMFAILED;
	}

	hDC = ::GetDC(hWnd);
	if(!hDC)
	{
		return E_FIELD_GETDLGITEMFAILED;
	}

	
	
	//Set the font of the field
	SendDlgItemMessage(i_nFieldId,WM_SETFONT,(WPARAM)i_phFont,TRUE);

	
	//Set the height and length of the field
	SIZE fldSize;	
	hFontOrig = (HFONT)::SelectObject(hDC, i_phFont); //do this so that we can measure the size
														//of the field

	//Set the intercharacer spacing
	if(i_nInterCharSpace)
		SetTextCharacterExtra(hDC,i_nInterCharSpace);

	//Set the text of the field
	if(!SetDlgItemText(i_nFieldId,i_tbstrText))
	{
		return E_FIELD_SETTEXTFAILED;
	}

	
	
	WCHAR wcharLineBreakChars[] = L"\n";
	WCHAR* pwszTempStr, *pwszCurrStr, *pwszOrigStr;
	unsigned int nCurr = 0;
	int nNumOfLines;
	int nCx;
	int nCy;

	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrText.length()+1];
	if(!pwszTempStr)
		return E_FAIL;

	//Copy the string to be rendered into the wchar buffer, 
	//and replace all \n with a \0
	pwszOrigStr = (WCHAR*)i_tbstrText;
	for(unsigned int i=0;i<i_tbstrText.length();++i)
	{
		if(pwszOrigStr[i] != wcharLineBreakChars[0])
		{
			pwszTempStr[i] = ((WCHAR*)i_tbstrText)[i];
		}
		else
		{
			pwszTempStr[i] = 0x0000;
		}
	}
	pwszTempStr[i] = 0x0000;

	nCurr = 0;
	fldSize.cx = nCx = 0;
	fldSize.cy = nCy = 0;
	nNumOfLines = 0;

	do
	{
		pwszCurrStr = pwszTempStr + nCurr;
		if(!GetTextExtentPoint32W(hDC,pwszCurrStr,lstrlenW(pwszCurrStr),&fldSize))
		{
			delete[] pwszTempStr;
			return E_FIELD_GETTEXTEXTENTFAILED;
		}

		if(i_nTruncWidth)
		{
			if(fldSize.cx > i_nTruncWidth)
			{
				nNumOfLines += (int)((fldSize.cx /i_nTruncWidth) + 1 + 1);
				nCx = i_nTruncWidth;
			}
			else
			{
				if(nCx < fldSize.cx)	
					nCx = fldSize.cx;
				nNumOfLines++;
			}
		}
		else
		{
			if(nCx < fldSize.cx)
				nCx = fldSize.cx;
			nNumOfLines ++;
		}

		nCurr+=lstrlenW(pwszCurrStr);
		nCurr++;

	}while(nCurr<i_tbstrText.length());

	fldSize.cx = nCx+1;
	fldSize.cy = (fldSize.cy * nNumOfLines) + 1;

	delete[] pwszTempStr;

	i_phFont = (HFONT)::SelectObject(hDC, hFontOrig); //reselect the original font into the field
	
	//Check if this field is a button - if it is then adjust the size
	TCHAR tstrClassName[MAX_CLASSNAME];
	if(GetClassName(hWnd,tstrClassName,MAX_CLASSNAME))
	{
		if(!lstrcmp(tstrClassName, "Button"))
		{
			LONG longStyle;
			if((longStyle = ::GetWindowLong(hWnd,GWL_STYLE)))
			{
				if(longStyle & BS_CHECKBOX)
				{
					fldSize.cx += CHKBOX_LEFTRIGHTMARGINS;
					
				}
				else
				{
					fldSize.cx += BTN_LEFTRIGHTMARGINS;
					fldSize.cy += BTN_TOPBTMMARGINS;

					if(fldSize.cx < BTN_MIN_CX)
						fldSize.cx = BTN_MIN_CX;
					if(fldSize.cy < BTN_MIN_CY)
						fldSize.cy = BTN_MIN_CY;
				}
			}
			else
			{
				return E_GETCLASSINFOFAILED;
			}
		}

		
		if(!lstrcmp(tstrClassName, "Edit"))
		{
			fldSize.cy += EDIT_TOPBTM_MARGINS;
		}

		//For edit box use the inputted width and height
		if(i_nWidth)
			fldSize.cx = i_nWidth;
		
		if(i_nHeight)
			fldSize.cy = i_nHeight;
			
		
	}
	else
	{
		return E_GETCLASSNAMEFAILED;
	}

	//Add the margins
	fldSize.cy += i_nTopBtmMargin;

	if(!::SetWindowPos(GetDlgItem(i_nFieldId),NULL,0,0,fldSize.cx,fldSize.cy, 
		SWP_NOMOVE|SWP_NOZORDER))
	{
		return E_FIELD_SETDIMSFAILED;
	}

	return S_OK;
}

/*HRESULT CPtaUI::_SetField_FontAndTextWeb(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth, int i_nWidth, int i_nHeight, int i_nTopBtmMargin, int i_nInterCharSpace)
{
	MessageBox("Entering _SetField_FontAndTextWeb", "DebugWindow", MB_OK);

	CComPtr<IWebBrowser2> pWebBrowser;
	GetDlgControl(IDC_WEBBROWSER, IID_IWebBrowser2, (void **) &pWebBrowser);
	CComVariant vtEmpty;
	pWebBrowser->Navigate2(&CComVariant("about://<HTML><body><h1>This</h1> <br> is neat.... </body></head>"),&vtEmpty, 
	&vtEmpty, &vtEmpty, &vtEmpty);
	//pWebBrowser->Navigate2(&CComVariant(L"www.microsoft.com"), &vtEmpty, 
	//&vtEmpty, &vtEmpty, &vtEmpty);
//
//	WCHAR* pwszTempStr, *pwszCurrStr, *pwszOrigStr;
//	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrText.length()+7];
//	pwszOrigStr = (WCHAR*)i_tbstrText;
//	strcat(pwszTempStr, "about:");
//	strcat(pwszTempStr, i_tbstrText);


//	for(unsigned int i=0;i<i_tbstrText.length();++i)
//	{
//		if(pwszOrigStr[i] != wcharLineBreakChars[0])
//		{
//			pwszTempStr[i] = ((WCHAR*)i_tbstrText)[i];
//		}
//		else
//		{
//			pwszTempStr[i] = 0x0000;
//		}
//	}
//	pwszTempStr[i] = 0x0000;
//
//
//	
//	sprintf(pwszTempStr, "about:%s",

	

	//Set the font of the field
	SendDlgItemMessage(i_nFieldId,WM_SETFONT,(WPARAM)i_phFont,TRUE);

	
	//Set the height and length of the field
	SIZE fldSize;	
	hFontOrig = (HFONT)::SelectObject(hDC, i_phFont); //do this so that we can measure the size
														//of the field

	//Set the intercharacer spacing
	if(i_nInterCharSpace)
		SetTextCharacterExtra(hDC,i_nInterCharSpace);

	//Set the text of the field
	if(!SetDlgItemText(i_nFieldId,i_tbstrText))
	{
		return E_FIELD_SETTEXTFAILED;
	}

	
	WCHAR wcharLineBreakChars[] = L"\n";
	WCHAR* pwszTempStr, *pwszCurrStr, *pwszOrigStr;
	unsigned int nCurr = 0;
	int nNumOfLines;
	int nCx;
	int nCy;

	pwszTempStr = (WCHAR*)new WCHAR[i_tbstrText.length()+1];
	if(!pwszTempStr)
		return E_FAIL;

	//Copy the string to be rendered into the wchar buffer, 
	//and replace all \n with a \0
	pwszOrigStr = (WCHAR*)i_tbstrText;
	for(unsigned int i=0;i<i_tbstrText.length();++i)
	{
		if(pwszOrigStr[i] != wcharLineBreakChars[0])
		{
			pwszTempStr[i] = ((WCHAR*)i_tbstrText)[i];
		}
		else
		{
			pwszTempStr[i] = 0x0000;
		}
	}
	pwszTempStr[i] = 0x0000;

	nCurr = 0;
	fldSize.cx = nCx = 0;
	fldSize.cy = nCy = 0;
	nNumOfLines = 0;

	do
	{
		pwszCurrStr = pwszTempStr + nCurr;
		if(!GetTextExtentPoint32W(hDC,pwszCurrStr,lstrlenW(pwszCurrStr),&fldSize))
		{
			delete[] pwszTempStr;
			return E_FIELD_GETTEXTEXTENTFAILED;
		}

		if(i_nTruncWidth)
		{
			if(fldSize.cx > i_nTruncWidth)
			{
				nNumOfLines += (int)((fldSize.cx /i_nTruncWidth) + 1 + 1);
				nCx = i_nTruncWidth;
			}
			else
			{
				if(nCx < fldSize.cx)	
					nCx = fldSize.cx;
				nNumOfLines++;
			}
		}
		else
		{
			if(nCx < fldSize.cx)
				nCx = fldSize.cx;
			nNumOfLines ++;
		}

		nCurr+=lstrlenW(pwszCurrStr);
		nCurr++;

	}while(nCurr<i_tbstrText.length());

	fldSize.cx = nCx+1;
	fldSize.cy = (fldSize.cy * nNumOfLines) + 1;

	delete[] pwszTempStr;

	i_phFont = (HFONT)::SelectObject(hDC, hFontOrig); //reselect the original font into the field
	
	//Check if this field is a button - if it is then adjust the size
	TCHAR tstrClassName[MAX_CLASSNAME];
	if(GetClassName(hWnd,tstrClassName,MAX_CLASSNAME))
	{
		if(!lstrcmp(tstrClassName, "Button"))
		{
			LONG longStyle;
			if((longStyle = ::GetWindowLong(hWnd,GWL_STYLE)))
			{
				if(longStyle & BS_CHECKBOX)
				{
					fldSize.cx += CHKBOX_LEFTRIGHTMARGINS;
					
				}
				else
				{
					fldSize.cx += BTN_LEFTRIGHTMARGINS;
					fldSize.cy += BTN_TOPBTMMARGINS;

					if(fldSize.cx < BTN_MIN_CX)
						fldSize.cx = BTN_MIN_CX;
					if(fldSize.cy < BTN_MIN_CY)
						fldSize.cy = BTN_MIN_CY;
				}
			}
			else
			{
				return E_GETCLASSINFOFAILED;
			}
		}

		
		if(!lstrcmp(tstrClassName, "Edit"))
		{
			fldSize.cy += EDIT_TOPBTM_MARGINS;
		}

		//For edit box use the inputted width and height
		if(i_nWidth)
			fldSize.cx = i_nWidth;
		
		if(i_nHeight)
			fldSize.cy = i_nHeight;
			
		
	}
	else
	{
		return E_GETCLASSNAMEFAILED;
	}

	//Add the margins
	fldSize.cy += i_nTopBtmMargin;

	if(!::SetWindowPos(GetDlgItem(i_nFieldId),NULL,0,0,fldSize.cx,fldSize.cy, 
		SWP_NOMOVE|SWP_NOZORDER))
	{
		return E_FIELD_SETDIMSFAILED;
	}
	return S_OK;
}
*/


HRESULT CPtaUI::_SetField_PlacementInRegion(int i_nFieldId, int i_nFieldMaxWidth, int i_nFieldMaxHeight, int i_nLeftMargin, int i_nRightMargin, int i_nTopMargin, int i_nBottomMargin, 
											int i_nRegionMinWidth, int i_nRegionMinHeight, int i_nRegionX, int i_nRegionY, int i_nRegionAnch, int i_nFieldXAnch, int i_nFieldYAnch,
											int* o_pRegionWidth, int* o_pRegionHeight, BOOL i_boolEnableField)
{
	RECT rectRegion;
	RECT rectField;
	int nRegionTop;
	int nRegionLeft;
	int nFieldTop;
	int nFieldLeft;

	HWND hwndField;
	HDC hDCField;

	hwndField = GetDlgItem(i_nFieldId);
	if(!hwndField)
	{
		return E_FIELD_GETDLGITEMFAILED;
	}

	hDCField = ::GetDC(hwndField);
	if(!hDCField)
	{
		return E_FIELD_GETDCFAILED;
	}

	//Obtain the width and height of the field
	if(!::GetClientRect(hwndField,&rectField))
	{
		return E_FIELD_GETCLIENTRECTFAILED;
	}
	rectField.right = rectField.right  - rectField.left;
	rectField.left = 0;
	rectField.bottom = rectField.bottom  - rectField.top;
	rectField.top = 0;


	//Set the dimension of the field - Clip the field if necessary
	if(rectField.right > i_nFieldMaxWidth)
	{
		rectField.right = i_nFieldMaxWidth;		
	}
	if(rectField.bottom  > i_nFieldMaxHeight)
	{
		rectField.bottom =  i_nFieldMaxHeight ;
	}
	if(!::SetWindowPos(GetDlgItem(i_nFieldId),NULL,0,0,rectField.right ,rectField.bottom
		,SWP_NOZORDER|SWP_NOMOVE))
	{
		return E_FIELD_SETDIMSFAILED;
	}
	
	//Obtain the dimensions of the region
	rectRegion.left = 0;
	rectRegion.right = rectField.right  + i_nLeftMargin + i_nRightMargin;
	if(rectRegion.right  < i_nRegionMinWidth)
	{
		rectRegion.right = i_nRegionMinWidth;
	}

	rectRegion.top = 0;
	rectRegion.bottom = rectField.bottom  + i_nTopMargin + i_nBottomMargin;
	if(rectRegion.bottom  < i_nRegionMinHeight)
	{
		rectRegion.bottom = i_nRegionMinHeight;
	}

	//Obtain the position of the region depending upon the anchor point
	switch(i_nRegionAnch)
	{
	case RGN_ANCH_TOPLEFT:
		nRegionLeft = i_nRegionX;
		nRegionTop = i_nRegionY;
		break;

	case RGN_ANCH_TOPRIGHT:
		nRegionLeft = i_nRegionX - rectRegion.right;
		nRegionTop = i_nRegionY;
		break;

	case RGN_ANCH_BOTTOMLEFT:
		nRegionLeft = i_nRegionX;
		nRegionTop = i_nRegionY - rectRegion.top;
		break;

	case RGN_ANCH_BOTTOMRIGHT:
		nRegionLeft = i_nRegionX - rectRegion.right;
		nRegionTop = i_nRegionY - rectRegion.top;
		break;

	default :
		return E_INVALIDFLAGS;

	}

	//Set the position of the field within the region, depending upon the anchor point
	switch(i_nFieldXAnch)
	{
	case FLD_XANCH_LEFT :
		nFieldLeft = nRegionLeft + i_nLeftMargin;
		break;

	case FLD_XANCH_RIGHT :
		nFieldLeft = nRegionLeft + (rectRegion.right - i_nRightMargin - rectField.right);
		break;

	case FLD_XANCH_MIDDLE :
		nFieldLeft = nRegionLeft + (rectRegion.right/2 - rectField.right/2);
		break;
	}

	switch(i_nFieldYAnch)
	{
		case FLD_YANCH_TOP :
			nFieldTop = nRegionTop + i_nTopMargin;
			break;

		case FLD_YANCH_BOTTOM :
			nFieldTop = nRegionTop + (rectRegion.bottom - i_nBottomMargin - rectField.bottom);
			break;

		case FLD_YANCH_MIDDLE :
			nFieldTop = nRegionTop + (rectRegion.bottom/2 - rectField.bottom/2);
			break;
	}

	if(!::SetWindowPos(hwndField,NULL,nFieldLeft,nFieldTop,0,0,SWP_NOZORDER|SWP_NOSIZE))
	{
		return E_FIELD_SETPOSFAILED;
	}

	//Enable or disable the window
	::EnableWindow(hwndField, i_boolEnableField);

	//Set the output params
	if(o_pRegionWidth) *o_pRegionWidth= rectRegion.right;
	if(o_pRegionHeight) *o_pRegionHeight = rectRegion.bottom;
	return S_OK;
}

HRESULT CPtaUI::_SetButtons()
{
	HRESULT retVal;
	SHORT nWidth = 0, nBtnRgn = 0;
	UINT nOperation = 0;

	nOperation = m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS;
	if(nOperation == SIGNMSG_BASE)
	{
		PALL_REVWMSG_UIELEMENTS pAllRvwMsgUIElems = (PALL_REVWMSG_UIELEMENTS)m_pUICtxt->pvUIElements;

		if(pAllRvwMsgUIElems->nSignTransDlgWidth <= 0 || pAllRvwMsgUIElems->nSignTransDlgWidth < DLGSIZE_SMALL_CX)
			nWidth = DLGSIZE_SMALL_CX;
		else
			nWidth = pAllRvwMsgUIElems->nSignTransDlgWidth;

		nBtnRgn = BTN1_RGN_X + (nWidth - DLGSIZE_CX);
	}
	else
		nBtnRgn = BTN1_RGN_X;

	//Set the text and font of the first button
	retVal = _SetField_FontAndText(IDOK,m_hFontDefBtnFont,m_pUICtxt->pbtnElems->tbstrBtn1Text);

	//Set the text and font of the secod button
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDBTN2,m_hFontDefBtnFont,m_pUICtxt->pbtnElems->tbstrBtn2Text);
	}

	//Set the text and font of the third button
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDBTN3,m_hFontDefBtnFont,m_pUICtxt->pbtnElems->tbstrBtn3Text);
	}

	//Place the buttons
	if(retVal == S_OK)
	{
		RECT rectDlgSize;

		GetClientRect(&rectDlgSize);
		int nBtn1RegionWidth;
		int nBtn2RegionWidth;

		if(m_nCurrWiz > 0)
		{
			retVal = _SetField_PlacementInRegion(IDOK,BTN_MAX_CX,BTN_MAX_CY,0,0,
				0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_RIGHT,FLD_YANCH_MIDDLE,&nBtn1RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn1Fn));

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN2,BTN_MAX_CX,BTN_MAX_CY,0,(BTN_RIGHT_MARGIN*4)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn+nBtn1RegionWidth,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn2Fn));
			}

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN3,BTN_MAX_CX,BTN_MAX_CY,0,BTN_RIGHT_MARGIN
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn+nBtn1RegionWidth+nBtn2RegionWidth
				,rectDlgSize.bottom - DLG_FOOTER_SIZE,RGN_ANCH_TOPLEFT,FLD_XANCH_RIGHT,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn3Fn));
			}

			SendMessage(DM_SETDEFID,IDBTN2);
			SendDlgItemMessage(IDBTN2, WM_SETFOCUS);
			SendDlgItemMessage(IDOK, BM_SETSTYLE,BS_PUSHBUTTON);
			if(!m_boolFocusSet)
			{	
				SendDlgItemMessage(IDBTN2, WM_ACTIVATE, WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}
		else
		{
			retVal = _SetField_PlacementInRegion(IDOK,BTN_MAX_CX,BTN_MAX_CY,(BTN_LEFT_MARGIN),(BTN_RIGHT_MARGIN * 2),
				0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_MIDDLE,&nBtn1RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn1Fn));

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN2,BTN_MAX_CX,BTN_MAX_CY,(BTN_LEFT_MARGIN),(BTN_RIGHT_MARGIN*2)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn+nBtn1RegionWidth,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn2Fn));
			}

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN3,BTN_MAX_CX,BTN_MAX_CY,(BTN_LEFT_MARGIN),(BTN_RIGHT_MARGIN * 2)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,nBtnRgn+nBtn1RegionWidth+nBtn2RegionWidth
				,rectDlgSize.bottom - DLG_FOOTER_SIZE,RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn3Fn));
			}

			::SetWindowPos(GetDlgItem(IDBTN2),GetDlgItem(IDOK),0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
			SendMessage(DM_SETDEFID,IDOK);
			SendDlgItemMessage(IDOK, WM_SETFOCUS);
			SendDlgItemMessage(IDBTN2, BM_SETSTYLE,BS_PUSHBUTTON);

			if(!m_boolFocusSet)
			{
				SendDlgItemMessage(IDBTN2, WM_ACTIVATE, WA_CLICKACTIVE);	
				m_boolFocusSet = TRUE;
			}
		}
		
	}

	return retVal;
}

HRESULT CPtaUI::_SetVRSNLogo()
{
	HRESULT retVal = S_OK;
	HBITMAP hBitmap = NULL;
	BITMAP bm;

	if(m_pUICtxt->tbstrCustAffLogoUrl.length())
		retVal = _GetBitmap(m_pUICtxt->tbstrCustAffLogoUrl, &hBitmap);

	if(!hBitmap)
		hBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_VSLARGE));
	
	if(hBitmap == NULL)
		return S_FALSE;
	
	if(GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm) == 0)
		return S_FALSE;

	//Place the logo
	RECT rectDlgSize;
	GetClientRect(&rectDlgSize);

	::SetWindowPos(GetDlgItem(IDC_VRSN_LOGO),NULL, 0,0, bm.bmWidth, bm.bmHeight, SWP_NOMOVE|SWP_NOZORDER);
	
	retVal = _SetField_PlacementInRegion(IDC_VRSN_LOGO,bm.bmWidth,bm.bmHeight,0,0,
		0,0,VRSNLOGO_X, DLG_FOOTER_SIZE,VRSNLOGO_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE,
		RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,NULL);
	::ShowWindow(GetDlgItem(IDC_VRSN_LOGO), TRUE);

	DeleteObject(hBitmap);
	hBitmap = NULL;
	
   return retVal;
}



HRESULT CPtaUI::_SetOpenUI(BOOL boolIsOpen)
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_OPENPROF_UIELEMENTS pAllOpenProfUIElems = (PALL_OPENPROF_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllOpenProfUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllOpenProfUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllOpenProfUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllOpenProfUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllOpenProfUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllOpenProfUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*6),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for create*/
	if(retVal == S_OK)
	{
		if(!boolIsOpen)
		{
			//Set the text
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
						pAllOpenProfUIElems->tbstrPasswordQuality,UITEXT_MAX_X);
			nUITextHeight = m_nDefTextFontSize;

			//Place the text
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
						(nUITextHeight*4),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
		
		
		}
		else
		{
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		}
	}


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the profile name label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_PROFNAMELBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			

		}
	}

	//Set the profile name edit box
	if(!boolIsOpen || !(pAllOpenProfUIElems->nNumOfProfiles))
	{
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllOpenProfUIElems->tbstrProfName, 
				0,CREATEPROF_PROFNAME_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY,pAllOpenProfUIElems->boolIsUsernameEditable);

				
				::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

			}

			if(!pAllOpenProfUIElems->tbstrProfName.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}
	}
	else
	{
		//Set the profile name list box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_COMBO1, m_hFontCustTextFont,_bstr_t(""), 
				0,CREATEPROF_PROFNAME_EDIT_SIZE-2);

			if(retVal == S_OK)
			{
				retVal = _FillListBox(IDC_COMBO1, m_hFontCustTextFont, pAllOpenProfUIElems->ptbstrProfList, pAllOpenProfUIElems->nNumOfProfiles,
					pAllOpenProfUIElems->tbstrProfName);
			}
			
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_COMBO1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY,pAllOpenProfUIElems->boolIsUsernameEditable);
				

				::ShowWindow(GetDlgItem(IDC_COMBO1),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
			}

			SendDlgItemMessage(IDC_COMBO1, WM_SETFOCUS);
			m_boolFocusSet = TRUE;

		}
	}

	
	if(pAllOpenProfUIElems->boolShowPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_PASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllOpenProfUIElems->tbstrPassword, 
				0,CREATEPROF_PASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

			}

			if(!pAllOpenProfUIElems->tbstrPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		if(!boolIsOpen) //confirm password will be shown only for the create call
		{
			//Set the confirm password label
			if(retVal == S_OK)
			{
				retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_CNFRMPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
				if(retVal == S_OK)
				{
					tbstrTempString = pwszOutBuff;
					//Set the text of the open profile label
					retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefTextFont,tbstrTempString);
					if(retVal == S_OK)
					{
						retVal = _SetField_PlacementInRegion(IDC_LABEL3,DLGSIZE_CX-UI_LEFT_MARGIN,
									(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
									RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
						::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
					}

				}
			}

			//Set the confirm password edit box
				if(retVal == S_OK)
			{
				retVal = _SetField_FontAndText(IDC_EDIT3, m_hFontCustTextFont,pAllOpenProfUIElems->tbstrConfirmPassword, 
					0,CREATEPROF_CNFRMPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_EDIT3,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
								EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_EDIT3),TRUE);
					nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

				}

				if(!pAllOpenProfUIElems->tbstrConfirmPassword.length() && !m_boolFocusSet)
				{
					SendDlgItemMessage(IDC_EDIT3, WM_ACTIVATE,WA_CLICKACTIVE);
					m_boolFocusSet = TRUE;
				}

			}
		}
	}

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CPtaUI::_SetExportP12UI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_EXPORTP12_UIELEMENTS pAllExportP12UIElems = (PALL_EXPORTP12_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllExportP12UIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllExportP12UIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllExportP12UIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllExportP12UIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllExportP12UIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllExportP12UIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for export p12*/
	if(retVal == S_OK)
	{
		//Set the text
		retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
					pAllExportP12UIElems->tbstrPasswordQuality,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;

		//Place the text
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
					(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
					RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 16);
			::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
		}
	}


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff = NULL;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the file name label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_EXPORTP12_FILENAMELBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),UITEXT_LEFT_MARGIN,0,0,0,0,0,0,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
		}
	}

	//Set the file name edit box
	if(pAllExportP12UIElems->boolShowFileName)
	{
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllExportP12UIElems->tbstrKeyFile, 
				0,CREATEPROF_PROFNAME_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UILABEL_SPACE+EDIT_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);

			}

			if(!pAllExportP12UIElems->tbstrKeyFile.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		//Create the browse button
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_BROWSE,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;

				//Set the text of the browse button
				retVal = _SetField_FontAndText(IDBTN4, m_hFontDefBtnFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDBTN4,BTN_MAX_CX,BTN_MAX_CY,0,0,0,0,0,0,
								UILABEL_SPACE+CREATEPROF_PROFNAME_EDIT_SIZE+2*EDIT_SPACE,nNextFieldY-2,
								RGN_ANCH_TOPLEFT,FLD_XANCH_RIGHT,FLD_YANCH_MIDDLE,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDBTN4),TRUE);
					nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);
				}
			}
		}
	}

	
	if(pAllExportP12UIElems->boolShowPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_PASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),UITEXT_LEFT_MARGIN,0,0,0,0,0,0,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllExportP12UIElems->tbstrP12Passwd, 
				0,CREATEPROF_PASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UILABEL_SPACE+EDIT_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllExportP12UIElems->tbstrP12Passwd.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		//Set the confirm password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_CNFRMPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL3,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),UITEXT_LEFT_MARGIN,0,0,0,0,0,0,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		
					::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
				}

			}
		}

		//Set the confirm password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT3, m_hFontCustTextFont,pAllExportP12UIElems->tbstrP12ConfPasswd, 
				0,CREATEPROF_CNFRMPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT3,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UILABEL_SPACE+EDIT_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT3),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllExportP12UIElems->tbstrP12ConfPasswd.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT3, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}
		}
	
	}

	if(NULL != pwszOutBuff)
	{
		free(pwszOutBuff);
		pwszOutBuff = NULL;
	}

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CPtaUI::_SetSelectUI()
{
	HRESULT retVal = S_OK;

	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 4);
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	//ShowWindow(FALSE);

	PALL_SELID_UIELEMENTS pAllSelIDUIElems = (PALL_SELID_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllSelIDUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllSelIDUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllSelIDUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllSelIDUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllSelIDUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;

	

	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					_bstr_t(""),UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}


	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/***Set the cert positions so that OnPaint can create it***/
	m_nCertPosY = nNextFieldY;
	nNextFieldY += CERT_HEIGHT + (HEADER_TOPBTM_MARGIN * 6) ;

	/*** Create the edit list ***/
	if(retVal == S_OK && pAllSelIDUIElems->pCertListHead->pidlistnodeNext != NULL) //More than one cert
	{															//so show the edit box
		//Set the font for the cert list to the default text font
		retVal = _SetField_FontAndText(IDC_LIST_CERTLIST,m_hFontDefTextFont,_bstr_t(""),
			0,CERTLIST_WIDTH,(m_nDefTextFontSize*3)+16);

		//Set the headers
		if(retVal == S_OK)
		{
			retVal = _CreateListCtrlHeaders(IDC_LIST_CERTLIST);	
		}
		
		//Fill the cert list
		if(retVal == S_OK)
		{
			retVal = _FillListCtrl(IDC_LIST_CERTLIST, pAllSelIDUIElems);
		}

		//Place the cert list
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LIST_CERTLIST,CERTLIST_WIDTH,(m_nDefTextFontSize*6),
				CERTLIST_LEFT_MARGIN,CERTLIST_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY, RGN_ANCH_TOPLEFT,
				FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			if(retVal == S_OK)
			{
				::ShowWindow(GetDlgItem(IDC_LIST_CERTLIST),TRUE);
				nNextFieldY += (nThisFieldY+(HEADER_TOPBTM_MARGIN*4));
			}
		}

		SendDlgItemMessage(IDC_LIST_CERTLIST,WM_SETFOCUS);

	}

	/*** Create the set default check box **/
	if(retVal == S_OK && pAllSelIDUIElems->pCertListHead->pidlistnodeNext != NULL && pAllSelIDUIElems->boolShowChkBox)
	{
		if(pAllSelIDUIElems->theCustUIElements.tbstrChkBoxText.length())
		{
			retVal = _SetField_FontAndText(IDC_CHECKBOX,m_hFontCustTextFont,
						pAllSelIDUIElems->theCustUIElements.tbstrChkBoxText,CHKBOX_MAX_X);
			nUITextHeight = m_nCustTextFontSize;
		}
		else
		{
			retVal = _SetField_FontAndText(IDC_CHECKBOX,m_hFontDefTextFont,
						pAllSelIDUIElems->theDefUIElements.tbstrChkBoxText,CHKBOX_MAX_X);
			nUITextHeight = m_nDefTextFontSize;
		}

		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_CHECKBOX,CHKBOX_MAX_X,(nUITextHeight*2),
				CHKBOX_LEFT_MARGIN,CHKBOX_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,RGN_ANCH_TOPLEFT,
				FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);

			if(retVal == S_OK)
			{
				nNextFieldY += nThisFieldY+(HEADER_TOPBTM_MARGIN*3);
				::ShowWindow(GetDlgItem(IDC_CHECKBOX),TRUE);
			}
		}
	}
	
	m_nUISize = nNextFieldY;

	//ShowWindow(TRUE);
	return retVal;
}



HRESULT CPtaUI::_SetSignUI()
{
	
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6);
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;
	SHORT nWidth = 0, nHeight = 0, nReadOnlyMaxCy = 0;

	PALL_REVWMSG_UIELEMENTS pAllRvwMsgUIElems = (PALL_REVWMSG_UIELEMENTS)m_pUICtxt->pvUIElements;

	if(pAllRvwMsgUIElems->nSignTransDlgWidth <= 0 || pAllRvwMsgUIElems->nSignTransDlgWidth < DLGSIZE_SMALL_CX)
		nWidth = DLGSIZE_SMALL_CX;
	else
		nWidth = pAllRvwMsgUIElems->nSignTransDlgWidth;

	if(pAllRvwMsgUIElems->nSignTransDlgHeight <= 0 || pAllRvwMsgUIElems->nSignTransDlgHeight < DLGSIZE_LARGE_CY)
		nHeight = DLGSIZE_LARGE_CY;
	else
		nHeight = pAllRvwMsgUIElems->nSignTransDlgHeight;

	if(pAllRvwMsgUIElems->nSignTransDlgHeight <= 0 || pAllRvwMsgUIElems->nSignTransDlgHeight < EDIT_RDONLY_MAX_CY)
		nReadOnlyMaxCy = EDIT_RDONLY_MAX_CY;
	else
		nReadOnlyMaxCy = pAllRvwMsgUIElems->nSignTransDlgHeight;

	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllRvwMsgUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllRvwMsgUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllRvwMsgUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllRvwMsgUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllRvwMsgUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllRvwMsgUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X );
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X ,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	int nEditBoxHeight=0;

	if(nHeight > DLGSIZE_SMALL_CY)
		nEditBoxHeight = nHeight - DLG_FOOTER_SIZE - nNextFieldY - (HEADER_TOPBTM_MARGIN*18);
	else
	{
		if(m_nCurrWiz > 0)
		{
			//If it is a wizard we have to maintain the size of the dialog box as is.
			if(m_nCYSet)
				nEditBoxHeight = m_nCYSet - DLG_FOOTER_SIZE - nNextFieldY - (HEADER_TOPBTM_MARGIN*8);
			else
				nEditBoxHeight = DLGSIZE_SMALL_CY - DLG_FOOTER_SIZE - nNextFieldY - (HEADER_TOPBTM_MARGIN*4);
		}
		else
			nEditBoxHeight = DLGSIZE_SMALL_CY - DLG_FOOTER_SIZE - nNextFieldY - (HEADER_TOPBTM_MARGIN*4);
	}
	//Fix for artf42974 : MPKI | GSWA | New browser session opens during signing transaction on VISTA
	OSVERSIONINFOEX osvi;

	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	GetVersionEx((OSVERSIONINFO *) &osvi);
	//If not Vista
	if ( !(osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0 && osvi.wProductType == VER_NT_WORKSTATION) )
	{
			
		IWebBrowser2* pWebBrowser = NULL;
		HRESULT HRBrowserCreation = 0;
		HRBrowserCreation = CoCreateInstance(CLSID_WebBrowser,NULL,CLSCTX_INPROC_SERVER,IID_IWebBrowser2,(void**)&pWebBrowser);

		if (SUCCEEDED(HRBrowserCreation))
		{
			LPOLESTR lpProgId = NULL;
			_bstr_t tbstrProgId = "";
			RECT rect = {10, 10, 100, 100};
			StringFromIID(IID_IWebBrowser2, &lpProgId);
			tbstrProgId = lpProgId;
			m_pCAxWindow.Create(m_hWnd, rect, tbstrProgId, WS_CHILD|WS_VSCROLL|WS_HSCROLL, 0, IDC_IBROWSER);
			m_pCAxWindow.QueryControl(&pWebBrowser);

			//Set the browser and document up.
			if(retVal == S_OK)
			{
				/// CREATE TEMP FILE
	#if 0
				DWORD pathStrSize = GetTempPath(0,NULL);
				LPTSTR pathStr = new TCHAR[pathStrSize];
	#else
				LPTSTR pathStr = new TCHAR[2*MAX_PATH];
	#endif
				BSTR temp = SysAllocString(L"vspta");
				m_szTempFileName = (TCHAR*)malloc(MAX_PATH);
				char *pStrURLToTempFile = new char[MAX_PATH+9];
				char *pStrMsgToSign = (char *)pAllRvwMsgUIElems->tbstrMsgToSign;

				do
				{
	#if 0
					if ((pathStrSize-1) != GetTempPath(pathStrSize,pathStr))
	#else
					if(GetTempPath(2*MAX_PATH, pathStr) > 2*MAX_PATH)
	#endif			
					{
						retVal = E_COULDNOTGETTEMPPATH;
						break;
					}
					if (GetTempFileName(pathStr,(TCHAR*)temp,GetTickCount()/*random number other than 0*/,m_szTempFileName) ==0)
					{
						retVal = E_COULDNOTGETTEMPFILENAME;
						break;
					}

					// Start CR30483: change file ext from .tmp to .htm
					//example m_szTempFileName = xyz.tmp
					char * tempString = strstr(m_szTempFileName, ".tmp"); 
					//now tempString = ".tmp"

					if (tempString != NULL)
					{
						// make m_szTempFileName = 'xyz\0'					
						m_szTempFileName[tempString - m_szTempFileName] = '\0';
						// add .htm to m_szTempFileName, so m_szTempFileName = "xyz.htm"
						strcat(m_szTempFileName, ".htm");					
						tempString = NULL;
					}
					// End CR30483: change file ext from .tmp to .htm

					HANDLE hFileHandle;
					hFileHandle = CreateFile(m_szTempFileName,
						GENERIC_READ|GENERIC_WRITE,
						0,
						NULL,
						CREATE_ALWAYS,
						FILE_FLAG_WRITE_THROUGH|FILE_ATTRIBUTE_TEMPORARY,// FILE_ATTRIBUTE_NORMAL
						NULL);
					// The file is being deleted in _TeardownSignUI
					if(!hFileHandle)
					{
						retVal = GetLastError();
						retVal = E_COULDNOTCREATETEMPFILE;
						break;
					}

					DWORD dStrLen = lstrlen(pStrMsgToSign);
					char *tempHTMLStr = new char[dStrLen+14];
					sprintf(tempHTMLStr, "<html>%s</html>",pStrMsgToSign);
					dStrLen +=13;
					if (!WriteFile(hFileHandle,(LPCVOID)tempHTMLStr,dStrLen,&dStrLen,NULL))
					{
						retVal = GetLastError();
						retVal = E_FILEWRITEERR;
						break;
					}
					delete tempHTMLStr;

					if (!CloseHandle(hFileHandle))
					{
						retVal = GetLastError();
						retVal = E_FILEWRITEERR;
						break;
					}

					lstrcpy(pStrURLToTempFile,"file:///");
					int len = strlen(m_szTempFileName);
					char *pTempFileName = new char[len+1];
					lstrcpy(pTempFileName,m_szTempFileName);

					// Convert the path from an absolute one
					// to an URL
					for (int i=0; i<len;i++)
					{
						if (!isalpha(pTempFileName[i]))
						{
							if (pTempFileName[i] == ':')
							{
								pTempFileName[i]='|';
							}
							else if (pTempFileName[i]=='\\')
							{
								pTempFileName[i]='/';
							}
						}
					}

					lstrcat(pStrURLToTempFile,pTempFileName);
					delete pTempFileName;
					CComVariant vtEmpty;
					retVal = pWebBrowser->Navigate2(&CComVariant(pStrURLToTempFile),&vtEmpty,   
					&vtEmpty, &vtEmpty, &vtEmpty);
				}
				while(0);
				delete pathStr;
				delete pStrURLToTempFile;
			}

			// And then set up the view and display it
			if (retVal == S_OK)
			{
				::SetWindowPos(GetDlgItem(IDC_IBROWSER),NULL,0,0,nWidth-40,nEditBoxHeight,SWP_NOZORDER|SWP_NOMOVE);
				::SetWindowPos(GetDlgItem(IDC_OUTLINE),NULL,0,0,nWidth-36,nEditBoxHeight+11,SWP_NOZORDER|SWP_NOMOVE);
							
				retVal = _SetField_PlacementInRegion(IDC_IBROWSER,
						nWidth-UITITLE_LEFT_MARGIN,nReadOnlyMaxCy ,// Width and Height
						0,HEADER_LEFT_MARGIN, // left and right margin
						0,0, // top and bottom margin
						0,0, // region min width and height
						UITITLE_LEFT_MARGIN,nNextFieldY, // region X and Y
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP, // region anchor & field X & Y anchor
						NULL,&nThisFieldY);

					/*retVal = _SetField_PlacementInRegion(IDC_IBROWSER,500,
						500 ,0,HEADER_LEFT_MARGIN,0,0,500,500,UITITLE_LEFT_MARGIN,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);*/

				retVal = _SetField_PlacementInRegion(IDC_OUTLINE,
						nWidth-UITITLE_LEFT_MARGIN-5,nReadOnlyMaxCy-5,// Width and Height
						-2,0, // left and right margin
						-8,0, // top and bottom margin
						0,0, // region min width and height
						UITITLE_LEFT_MARGIN,nNextFieldY, // region X and Y
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP, // field X and Y anchor
						NULL,&nThisFieldY);

				::ShowWindow(GetDlgItem(IDC_IBROWSER),TRUE);
				::ShowWindow(GetDlgItem(IDC_OUTLINE),TRUE);
			}
		}
		else
		{
			retVal = _SetField_FontAndText(IDC_EDIT_RDONLY, m_hFontCustTextFont,
			pAllRvwMsgUIElems->tbstrMsgToSign, nWidth-(UITITLE_LEFT_MARGIN*2),nWidth-(UITITLE_LEFT_MARGIN*2),nEditBoxHeight,(m_nCurrWiz>0?0:EDIT_RDONLY_TOPBTM_MARGINS));
			nUITextHeight = m_nCustTextFontSize;
			::SetWindowPos(GetDlgItem(IDC_EDIT_RDONLY),NULL,0,0,nWidth-20,nEditBoxHeight,SWP_NOZORDER|SWP_NOMOVE);
				
			retVal = _SetField_PlacementInRegion(IDC_EDIT_RDONLY,nWidth-UITITLE_LEFT_MARGIN,
						nReadOnlyMaxCy,0,HEADER_LEFT_MARGIN,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);

			::ShowWindow(GetDlgItem(IDC_EDIT_RDONLY),TRUE);
		}
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_EDIT_RDONLY, m_hFontCustTextFont,
		pAllRvwMsgUIElems->tbstrMsgToSign, nWidth-(UITITLE_LEFT_MARGIN*2),nWidth-(UITITLE_LEFT_MARGIN*2),nEditBoxHeight,(m_nCurrWiz>0?0:EDIT_RDONLY_TOPBTM_MARGINS));
		nUITextHeight = m_nCustTextFontSize;
		::SetWindowPos(GetDlgItem(IDC_EDIT_RDONLY),NULL,0,0,nWidth-20,nEditBoxHeight,SWP_NOZORDER|SWP_NOMOVE);
			
		retVal = _SetField_PlacementInRegion(IDC_EDIT_RDONLY,nWidth-UITITLE_LEFT_MARGIN,
					nReadOnlyMaxCy,0,HEADER_LEFT_MARGIN,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
					RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);

		::ShowWindow(GetDlgItem(IDC_EDIT_RDONLY),TRUE);
	}

	nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
	m_nUISize = nNextFieldY;
	return retVal;
}



HRESULT CPtaUI::_SetIntroUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6);
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_INTRODLG_UIELEMENTS pAllIntroDlgUIElems = (PALL_INTRODLG_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllIntroDlgUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllIntroDlgUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllIntroDlgUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllIntroDlgUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllIntroDlgUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X-4);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllIntroDlgUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X-4 );
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X-4 ,
				(nUITextHeight*10),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}


	m_nUISize = nNextFieldY;
	return retVal;

}

HRESULT CPtaUI::_SetCreatePasswdUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_CREATEPASSWD_UIELEMENTS pAllCreatePasswdUIElems = (PALL_CREATEPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllCreatePasswdUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllCreatePasswdUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllCreatePasswdUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllCreatePasswdUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllCreatePasswdUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllCreatePasswdUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for create*/
	/* XXX
	if(retVal == S_OK)
	{
			//Set the text
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
						pAllCreatePasswdUIElems->tbstrPasswordQuality,UITEXT_MAX_X);
			nUITextHeight = m_nDefTextFontSize;

			//Place the text
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
						(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 16);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
	}
	*/


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	
	if(pAllCreatePasswdUIElems->boolShowNewPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPASSWD_NEWPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllCreatePasswdUIElems->tbstrNewPassword, 
				0,CREATEPASSWD_NEWPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllCreatePasswdUIElems->tbstrNewPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		//Set the confirm password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPASSWD_CNFRMPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL3,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
				}

			}
		}

		//Set the confirm password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT3, m_hFontCustTextFont,pAllCreatePasswdUIElems->tbstrConfirmPassword, 
				0,CREATEPASSWD_CNFRMPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT3,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT3),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllCreatePasswdUIElems->tbstrConfirmPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT3, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}
	}
	

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CPtaUI::_SetEnterPasswdUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_ENTERPASSWD_UIELEMENTS pAllEnterPasswdUIElems = (PALL_ENTERPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllEnterPasswdUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllEnterPasswdUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllEnterPasswdUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllEnterPasswdUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllEnterPasswdUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllEnterPasswdUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for create*/
	/* XXX
	if(retVal == S_OK)
	{
			//Set the text
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
						pAllCreatePasswdUIElems->tbstrPasswordQuality,UITEXT_MAX_X);
			nUITextHeight = m_nDefTextFontSize;

			//Place the text
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
						(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 16);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
	}
	*/


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	
	if(pAllEnterPasswdUIElems->boolShowNewPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_ENTERPASSWD_THEPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllEnterPasswdUIElems->tbstrThePassword, 
				0, ENTERPASSWD_THEPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllEnterPasswdUIElems->tbstrThePassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;

							}

		}
	}
	

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CPtaUI::_SetChangePasswdUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_CHANGEPASSWD_UIELEMENTS pAllChngPasswdUIElems = (PALL_CHANGEPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllChngPasswdUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllChngPasswdUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllChngPasswdUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllChngPasswdUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllChngPasswdUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllChngPasswdUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for create*/
	if(retVal == S_OK)
	{
			//Set the text
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
						pAllChngPasswdUIElems->tbstrPasswordQuality,UITEXT_MAX_X);
			nUITextHeight = m_nDefTextFontSize;

			//Place the text
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
						(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 16);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
	}


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the old password label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CHNGPASSWD_OLDPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			

		}
	}

	//Set the old password edit box
	if(pAllChngPasswdUIElems->boolShowOldPassword)
	if(retVal == S_OK)
	{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllChngPasswdUIElems->tbstrOldPassword, 
				0,CHNGPASSWD_OLDPASSWD_EDIT_SIZE,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllChngPasswdUIElems->tbstrOldPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

	}
	
	

	if(pAllChngPasswdUIElems->boolShowNewPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CHANGEPASSWD_NEWPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT3, m_hFontCustTextFont,pAllChngPasswdUIElems->tbstrNewPassword, 
				0,CREATEPROF_PASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT3,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT3),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllChngPasswdUIElems->tbstrNewPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT3, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		//Set the confirm password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_CNFRMPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL3,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
				}

			}
		}

		//Set the confirm password edit box
			if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT4, m_hFontCustTextFont,pAllChngPasswdUIElems->tbstrConfirmPassword, 
				0,CREATEPROF_CNFRMPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT4,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT4),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

			}

			if(!pAllChngPasswdUIElems->tbstrConfirmPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT4, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}
	}
	

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CPtaUI::_SetImportP12UI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 8); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_IMPORTP12_UIELEMENTS pAllImportP12UIElems = (PALL_IMPORTP12_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllImportP12UIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllImportP12UIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllImportP12UIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllImportP12UIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllImportP12UIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllImportP12UIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*2),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}


	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the password label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_PASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			

		}
	}

	//Set the password edit box
	if(retVal == S_OK)
	{
			retVal = _SetField_FontAndText(IDC_EDIT2, m_hFontCustTextFont,pAllImportP12UIElems->tbstrP12Passwd, 
				0,CREATEPROF_CNFRMPASSWORD_EDIT_SIZE,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT2,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT2),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 18);

			}

			SendDlgItemMessage(IDC_EDIT2, WM_ACTIVATE,WA_CLICKACTIVE);
			m_boolFocusSet = TRUE;
		

	}
	
	m_nUISize = nNextFieldY;

	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_SetGetSecretQuestionUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function sets up UI for GetSecretQuestion dialog box. It sets
//						the title and text for this dialog and places the required controls properly.
//						this dialog takes user name of the profile as input
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_SetGetSecretQuestionUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_GETSECRETQUESTION_UIELEMENTS pAllGetSecretQuestionUIElems = (PALL_GETSECRETQUESTION_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllGetSecretQuestionUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllGetSecretQuestionUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllGetSecretQuestionUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllGetSecretQuestionUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllGetSecretQuestionUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllGetSecretQuestionUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	//nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

	/*Creaete the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the profile name label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_PROFNAMELBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			

		}
	}

	//Set the profile name edit box
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllGetSecretQuestionUIElems->tbstrProfName, 
			0,CREATEPROF_PROFNAME_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
						EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY,TRUE);

			
			::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

		}

		if(!pAllGetSecretQuestionUIElems->tbstrProfName.length() && !m_boolFocusSet)
		{
			SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
			m_boolFocusSet = TRUE;
		}

	}
	
	m_nUISize = nNextFieldY;

	return retVal;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_SetResetPasswdUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function sets up UI for Password Reset dialog box. It sets
//						the title and text for this dialog and places the required controls properly.
//						This dialog displays secret question associated with the user's
//						roaming profile and asks the user to enter the answer for the secret
//						question and new password.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_SetResetPasswdUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_RESETPASSWD_UIELEMENTS pAllResetPasswdUIElems = (PALL_RESETPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllResetPasswdUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllResetPasswdUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllResetPasswdUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllResetPasswdUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllResetPasswdUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllResetPasswdUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*3),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Set the password requirement text for create*/
	if(retVal == S_OK)
	{
			//Set the text
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefTextFont,
						pAllResetPasswdUIElems->tbstrPasswordQuality,UITEXT_MAX_X);
			nUITextHeight = m_nDefTextFontSize;

			//Place the text
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,UITEXT_MAX_X,
						(nUITextHeight*5),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
	}


	/*Create the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the secret question label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RESETPASSWD_SECQUESLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;

			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL5, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL5,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL5),TRUE);
			}

		}
	}

	//Set the secret question
	if(retVal == S_OK)
	{

		retVal = _SetField_FontAndText(IDC_LABEL6, m_hFontCustTextFont,pAllResetPasswdUIElems->tbstrSecretQuestion, UITEXT_MAX_X - UILABEL_SPACE);
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL6,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
						//EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
						(nUITextHeight*2),0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			::ShowWindow(GetDlgItem(IDC_LABEL6),TRUE);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

		}

	}
	
	
	//Set the secret answer label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RESETPASSWD_SECANSWERLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			
		}
	}

	//Set the secret answer edit box
	if(retVal == S_OK)
	{
			retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllResetPasswdUIElems->tbstrSecretAnswer, 
				0,CREATESECRET_SECANSWER_EDIT_SIZE,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

			}

			if(!pAllResetPasswdUIElems->tbstrSecretAnswer.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

	}
	
	

	if(pAllResetPasswdUIElems->boolShowNewPassword)
	{
		//Set the password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RESETPASSWD_NEWPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL2,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
				}

			}
		}

		//Set the password edit box
		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT3, m_hFontCustTextFont,pAllResetPasswdUIElems->tbstrNewPassword, 
				0,CREATEPROF_PASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT3,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT3),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

			}

			if(!pAllResetPasswdUIElems->tbstrNewPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT3, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}

		//Set the confirm password label
		if(retVal == S_OK)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_CREATEPROF_CNFRMPASSWDLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrTempString = pwszOutBuff;
				//Set the text of the open profile label
				retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefTextFont,tbstrTempString);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL3,DLGSIZE_CX-UI_LEFT_MARGIN,
								(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
				}

			}
		}

		//Set the confirm password edit box
			if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_EDIT4, m_hFontCustTextFont,pAllResetPasswdUIElems->tbstrConfirmPassword, 
				0,CREATEPROF_CNFRMPASSWORD_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_EDIT4,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
							EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_EDIT4),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);

			}

			if(!pAllResetPasswdUIElems->tbstrConfirmPassword.length() && !m_boolFocusSet)
			{
				SendDlgItemMessage(IDC_EDIT4, WM_ACTIVATE,WA_CLICKACTIVE);
				m_boolFocusSet = TRUE;
			}

		}
	}
	

	m_nUISize = nNextFieldY;

	return retVal;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_SetCreateSecretUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function sets up UI for Create Secret dialog. It sets
//						the title and text for this dialog and places the required controls properly.
//						This dialog prompts the user to enter the secret question and 
//						answer to be associated with user's roaming profile.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_SetCreateSecretUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_CREATESECRET_UIELEMENTS pAllCreateSecretUIElems = (PALL_CREATESECRET_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllCreateSecretUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllCreateSecretUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllCreateSecretUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllCreateSecretUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllCreateSecretUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X-4);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllCreateSecretUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X-4);
		nUITextHeight = m_nDefTextFontSize;
	}

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X-4,
				(nUITextHeight*10),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 3);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Create the labels and input fields*/
	WCHAR* pwszOutBuff;
	_bstr_t tbstrTempString;
	pwszOutBuff= (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);

	//Set the secret question label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RESETPASSWD_SECQUESLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;

			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL5, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL5,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL5),TRUE);
			}

		}
	}

	//Set the secret question edit box
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_EDIT5, m_hFontCustTextFont,pAllCreateSecretUIElems->tbstrSecretQuestion, 
			0,CREATESECRET_SECQUES_EDIT_SIZE,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_EDIT5,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
						EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			::ShowWindow(GetDlgItem(IDC_EDIT5),TRUE);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

		}

		if(!pAllCreateSecretUIElems->tbstrSecretQuestion.length() && !m_boolFocusSet)
		{
			SendDlgItemMessage(IDC_EDIT5, WM_ACTIVATE,WA_CLICKACTIVE);
			m_boolFocusSet = TRUE;
		}

	}
	
	
	//Set the secret answer label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RESETPASSWD_SECANSWERLBL,pwszOutBuff,MAX_RES_STRING_SIZE);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UI_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
			
		}
	}

	//Set the secret answer edit box
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllCreateSecretUIElems->tbstrSecretAnswer, 
			0,CREATESECRET_SECANSWER_EDIT_SIZE,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-UILABEL_SPACE,
						EDIT_MAX_CY,0,0,0,0,0,0,UI_LEFT_MARGIN+UILABEL_SPACE,nNextFieldY-2,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);

		}

		if(!pAllCreateSecretUIElems->tbstrSecretAnswer.length() && !m_boolFocusSet)
		{
			SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
			m_boolFocusSet = TRUE;
		}

	}
	

	m_nUISize = nNextFieldY;

	return retVal;
}

LRESULT CPtaUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT retVal = S_OK;	
	
	if(m_pUICtxt->nWhichWizardAndUI & SELID_BASE)
	{
		retVal = _DisplayCert();
		_ShowTransparentBitmap(IDC_CERT_LOGO);
	}
	
	//Set the verisign logo
	_ShowTransparentBitmap(IDC_VRSN_LOGO);

	_ShowTransparentBitmap(IDC_HEADER_LOGO);

	bHandled = FALSE;
	return 0;

}

LRESULT CPtaUI::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT retVal = 0;
	if(m_pUICtxt->nWhichWizardAndUI & SELID_BASE)
	{
		DWORD dwCtrlID;
		dwCtrlID = ::GetDlgCtrlID((HWND)lParam);
		switch(dwCtrlID)
		{
		case IDC_LABEL2:
			SetTextCharacterExtra(HDC(wParam),CERT_COMMONNAME_INTERCHARSPACE);
			SetBkMode((HDC)wParam,TRANSPARENT);
			retVal = (LRESULT)m_hTextureBrush;
		case IDC_LABEL3 :
			SetTextCharacterExtra(HDC(wParam),CERT_VALIDITYLBL_INTERCHARSPACE);
		case IDC_LABEL5:
		case IDC_LABEL4 :
		case IDC_LABEL1 :
			SetBkMode((HDC)wParam,TRANSPARENT);
			retVal = (LRESULT)m_hTextureBrush;
			break;
		}
	}

	return retVal;
}

HRESULT CPtaUI::_CreateCertRect(HDC hDC,int i_nCertRectX,int i_nCertRectY)
{
	POINT rectPts[2];

	rectPts[0].x = i_nCertRectX;
	rectPts[0].y = i_nCertRectY;
	rectPts[1].x = rectPts[0].x + CERT_WIDTH;
	rectPts[1].y = rectPts[0].y+ CERT_HEIGHT;

	if(!DPtoLP(hDC,rectPts,2))
		return E_DPTOLPFAILED;

	if(!RoundRect(hDC,rectPts[0].x,rectPts[0].y,rectPts[1].x,rectPts[1].y,CERT_ARC_SIZE,CERT_ARC_SIZE)) 
	{
		return E_CERT_ROUNDRECTFAILED;
	}

	return S_OK;

}

HRESULT CPtaUI::_DisplayCert()
{
	HRESULT retVal = S_OK;
			
	PALL_SELID_UIELEMENTS pAllSelIDUIElems = (PALL_SELID_UIELEMENTS)m_pUICtxt->pvUIElements;
	PIDLISTNODE pidListNodeCurrSelect;
	HDC hDC;

	//Obtain a pointer to the currently selected cert node
	if(retVal == S_OK)
	{
		pidListNodeCurrSelect = pAllSelIDUIElems->pCertListHead;
		for(int i=0;i<pAllSelIDUIElems->nSelectedIDFromList;++i)
			pidListNodeCurrSelect = pidListNodeCurrSelect->pidlistnodeNext;
		
		//Obtain the cert logo
		_FreeBitmap(m_hCertBitmap);
		m_hCertBitmap = NULL;
		if(pidListNodeCurrSelect->pAuxCertInfo->tbstrLogoUrl.length())
			retVal = _GetBitmap(pidListNodeCurrSelect->pAuxCertInfo->tbstrLogoUrl,&m_hCertBitmap);

#ifdef DEBUG
		if(retVal != S_OK)
		{
			TCHAR tstrErrMsg[1024];
			_stprintf(tstrErrMsg,"Error %d occured while obtaining the cert logo", retVal);
			//MessageBox(tstrErrMsg);
		}
#endif
		retVal = S_OK;
	}

	//Obtain the texture brush
	if(retVal == S_OK)
	{
		if(m_hTextureBrush)
		{
			DeleteObject(m_hTextureBrush);
			m_hTextureBrush = NULL;
		}

		if(pidListNodeCurrSelect->pAuxCertInfo->tbstrTextureUrl.length())
		{
			HBITMAP hTextureBitmap;
			retVal = _GetBitmap(pidListNodeCurrSelect->pAuxCertInfo->tbstrTextureUrl,&hTextureBitmap);
			if(retVal == S_OK)
			{
				m_hTextureBrush = CreatePatternBrush(hTextureBitmap);
				if(!m_hTextureBrush)
				{
					retVal = E_CREATEPATTERNBRUSH_FAILED;
					m_hTextureBrush = CreateSolidBrush(RGB(255,255,255));
				}
				_FreeBitmap(hTextureBitmap);
			}
			else
			{
				m_hTextureBrush = CreateSolidBrush(RGB(255,255,255));
				if(!m_hTextureBrush)
					retVal = E_CREATESOLIDBRUSH_FAILED;
			}
		}
		else
		{

			m_hTextureBrush = CreateSolidBrush(RGB(255,255,255));
			if(!m_hTextureBrush)
					retVal = E_CREATESOLIDBRUSH_FAILED;
		}
		
#ifdef DEBUG
		if(retVal != S_OK)
		{
			TCHAR tstrErrMsg[1024];
			_stprintf(tstrErrMsg,"Error %d occured while obtaining the texture", retVal);
			//MessageBox(tstrErrMsg);
		}
#endif
		retVal = S_OK;
	}


	//Set the cert logo
	if(retVal == S_OK)
	{
		if(m_hCertBitmap)
		{
			SendDlgItemMessage(IDC_CERT_LOGO,STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)m_hCertBitmap);
	
			/*Place the cert logo*/
			retVal = _SetField_PlacementInRegion(IDC_CERT_LOGO,CERT_WIDTH-(2*CERT_ARC_SIZE),CERT_HEIGHT-CERT_INFO_SPACE,CERT_LOGO_LEFT_MARGIN
				,0,CERT_LOGO_TOP_MARGIN,0,0,0,CERT_LEFT_MARGIN,m_nCertPosY,RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT, FLD_YANCH_TOP,NULL,NULL);
			if(retVal == S_OK)
				::ShowWindow(GetDlgItem(IDC_CERT_LOGO),TRUE);
		}
	}

	//Set the cert friendly name
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_LABEL1,m_hFontCustWizTitleFont,pidListNodeCurrSelect->pAuxCertInfo->tbstrFrndlyName,
			(int)CERT_FRNDLYNAME_MAX_X);

		//Place the friendly name
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL1,(int)CERT_FRNDLYNAME_MAX_X,CERT_HEIGHT-CERT_INFO_SPACE,0,CERT_FRNDLYNAME_RIGHT_MARGIN
				,CERT_FRNDLYNAME_TOP_MARGIN,0,0,0,CERT_LEFT_MARGIN+CERT_WIDTH,m_nCertPosY,RGN_ANCH_TOPRIGHT,FLD_XANCH_RIGHT,FLD_YANCH_TOP,NULL,NULL);

			if(retVal == S_OK)
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
		}

	}
	
	int nNextFieldY = m_nCertPosY + (CERT_HEIGHT - CERT_INFO_SPACE - 30);
	int nThisFieldY = 0;

	//Set the display string
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_LABEL5,m_hFontCustWizTitleFont,pidListNodeCurrSelect->pAuxCertInfo->tbstrDispString,
			CERT_WIDTH,0,0,0,0);

		//Place the friendly name
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL5,CERT_WIDTH,
					(CERT_HEIGHT- CERT_INFO_SPACE - 30),0,0
					,0,0,CERT_WIDTH,0,CERT_LEFT_MARGIN,nNextFieldY,RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_TOP,NULL,NULL);

			if(retVal == S_OK)
				::ShowWindow(GetDlgItem(IDC_LABEL5),TRUE);
		}

	}

	nNextFieldY = m_nCertPosY + (CERT_HEIGHT - CERT_INFO_SPACE);
	nThisFieldY = 0;

	//Set the validity label
	if(retVal == S_OK)
	{
		_bstr_t tbstrValidityLabel;
		WCHAR* pwszTemp;

		//Obtain the validity label
		pwszTemp = (WCHAR*)new WCHAR[MAX_RES_STRING_SIZE];

		if(!pwszTemp)
		{
			retVal = E_FAIL;
		}
		else
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_VALIDITYLBL,pwszTemp,MAX_RES_STRING_SIZE);
			if(retVal == S_OK)
			{
				tbstrValidityLabel = pwszTemp;

				retVal = _SetField_FontAndText(IDC_LABEL3,m_hFontValidityLabelFont,tbstrValidityLabel,0,0,0,0,CERT_VALIDITYLBL_INTERCHARSPACE);

				
				if(retVal == S_OK)
				{
					//Place the validity label
					retVal =_SetField_PlacementInRegion(IDC_LABEL3,CERT_VALIDITYLBL_MAX_X,CERT_VALIDITYLBL_MAX_Y,CERT_VALIDITYLBL_LEFT_MARGIN,0,
						0,0,0,m_nValidityLabelFontSize,CERT_LEFT_MARGIN,nNextFieldY,RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,
						NULL,&nThisFieldY);
					if(retVal == S_OK)
					{
						nNextFieldY += (nThisFieldY + 1);
						::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
					}
				}

			}

			delete[] pwszTemp;
		}

	}

	
	//Set the validity dates
	if(retVal == S_OK)
	{
		_bstr_t tbstrDateStr;
		_bstr_t tbstrValidityDates;

		retVal = _FormatDate(pidListNodeCurrSelect->pDecCertInfo->dateEffDate, &tbstrDateStr);
		if(retVal == S_OK)
		{
			tbstrValidityDates = tbstrDateStr;
			retVal = _FormatDate(pidListNodeCurrSelect->pDecCertInfo->dateExpDate, &tbstrDateStr);
			if(retVal == S_OK)
			{
				tbstrValidityDates = tbstrValidityDates + L" - " + tbstrDateStr; 

				//Place the validity date string
				retVal = _SetField_FontAndText(IDC_LABEL4,m_hFontCertInfoFont,tbstrValidityDates,
					CERT_VALIDITY_MAX_X);
				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(IDC_LABEL4,CERT_VALIDITY_MAX_X,
					(CERT_HEIGHT-(nNextFieldY-m_nCertPosY)),CERT_VALIDITY_LEFT_MARGIN,CERT_VALIDITY_RIGHT_MARGIN
					,0,0,0,0,CERT_LEFT_MARGIN,nNextFieldY,RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);

					if(retVal == S_OK)
					{
						::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
						nNextFieldY += (nThisFieldY + (HEADER_TOPBTM_MARGIN));
					}
			
				}
			}

		}
	}


	//Set the cert common name
	if(retVal == S_OK)
	{
		//Obtain the cert common name
		_bstr_t tbstrCertCN = "";
		_bstr_t tbstrCertCNUpperCase;
		retVal = _GetCertCN(pidListNodeCurrSelect->pDecCertInfo->tbstrSubjectDN,&tbstrCertCN);
		
		if(retVal == E_NOCNFOUND)
		{
			tbstrCertCN = "Digital ID";
			retVal = S_OK;
		}
		
		tbstrCertCNUpperCase = CharUpper((LPTSTR)tbstrCertCN);

		if(retVal == S_OK)
		{
			retVal = _SetField_FontAndText(IDC_LABEL2,m_hFontCertInfoFont,tbstrCertCNUpperCase,
				CERT_COMMONNAME_MAX_X,0,0,0,CERT_COMMONNAME_INTERCHARSPACE);

			//Place the cert common name
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL2,CERT_COMMONNAME_MAX_X,
					(CERT_HEIGHT-(nNextFieldY-m_nCertPosY)-5),CERT_COMMONNAME_LEFT_MARGIN,CERT_COMMONNAME_RIGHT_MARGIN
					,0,0,0,0,CERT_LEFT_MARGIN,nNextFieldY,RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,NULL);

				if(retVal == S_OK)
					::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
			}
		}

	}
	

	//Create the cert rectangles		
	if(retVal == S_OK)
	{
		//First make the window invisible so that the rectangle does not flicker
		
		PAINTSTRUCT paintStruct;
		RECT certRect;
		certRect.left = CERT_LEFT_MARGIN;
		certRect.top = m_nCertPosY;
		certRect.right = certRect.left + CERT_WIDTH + 2;
		certRect.bottom = certRect.top + CERT_HEIGHT + 2;

	
		if(!InvalidateRect(&certRect),FALSE)
			retVal = E_INVALIDATERECTFAILED;
		
		hDC = BeginPaint(&paintStruct);

		if(!SelectObject(hDC,GetStockObject(BLACK_BRUSH)))
			retVal = E_CERT_SELECTBLACKBRUSH_FAILED;
		else
		{
			retVal = _CreateCertRect(hDC,CERT_LEFT_MARGIN+2,m_nCertPosY+2);

			if(retVal == S_OK)
			{
				retVal = _CreateCertRect(hDC,CERT_LEFT_MARGIN+1,m_nCertPosY+1);

				if(retVal == S_OK)
				{
					if(!SelectObject(hDC,m_hTextureBrush))
						retVal = E_CERT_SELECTTEXTUREBRUSH_FAILED;
					else
					{
						retVal = _CreateCertRect(hDC,CERT_LEFT_MARGIN,m_nCertPosY);
					}
				}
			}
		}
		EndPaint(&paintStruct);

	}
	

	//Free memory if required
	if(retVal != S_OK)
	{
		DeleteObject(m_hTextureBrush);
		m_hTextureBrush = NULL;
	}

	_FreeBitmap(m_hCertBitmap);
	m_hCertBitmap = NULL;
	
	return retVal;

}

HRESULT CPtaUI::_CreateListCtrlHeaders(int i_nListCtrlId)
{
	HRESULT retVal = S_OK;

	//Create the columns
	HWND hwndCtrlWnd = GetDlgItem(i_nListCtrlId);

	ListView_SetExtendedListViewStyle(hwndCtrlWnd,LVS_EX_FULLROWSELECT );

	retVal = _AddColHeader(hwndCtrlWnd,IDS_CERTLIST_CNCOL_HEAD,CERTLIST_COMMONNAME_COL_WIDTH,0);
	
	if(retVal == S_OK)
	{
		if(m_pUICtxt->pfontInfoCustomFonts->tbstrTextFont == m_pUICtxt->pfontInfoDefaultFonts->tbstrTextFont) 
		{									//only if the default font which we will render the edit box in can be used to render custom strings we will show the friendly name, which is a custom string
			retVal = _AddColHeader(hwndCtrlWnd,IDS_CERTLIST_FNCOL_HEAD,CERTLIST_FRNDLYNAME_COL_WIDTH,1);
		}

		if(retVal == S_OK)
		{
			retVal = _AddColHeader(hwndCtrlWnd,IDS_CERTLIST_EXPIRES_HEAD,CERTLIST_EXPIRES_COL_WIDTH,2);
		}
		
	}

	return retVal;
}

HRESULT CPtaUI::_AddColHeader(HWND i_nhwndCtrlWnd, int i_nColHeaderName,int i_nColHeaderWidth,int i_nColHeaderNum)
{
	HRESULT retVal = S_OK;
	WCHAR* pwszColHeader;
	_bstr_t tbstrColHeader;
	LVCOLUMN lvColumn;

	pwszColHeader = (WCHAR*)new WCHAR[MAX_RES_STRING_SIZE];
	if(!pwszColHeader)
		return E_FAIL;

	//Add columns
	lvColumn.mask = LVCF_TEXT | LVCF_WIDTH;
	lvColumn.cx = i_nColHeaderWidth;

	retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,i_nColHeaderName,
		pwszColHeader,MAX_RES_STRING_SIZE);
	
	if(retVal == S_OK)
	{
		tbstrColHeader = pwszColHeader;
		lvColumn.pszText = (TCHAR*)tbstrColHeader;

		if(ListView_InsertColumn(i_nhwndCtrlWnd, i_nColHeaderNum, &lvColumn) == -1)
			retVal = E_INSERTCOLFAILED;
	}
	delete[] pwszColHeader;
	return retVal;
}

HRESULT CPtaUI::_FillListCtrl(int i_nListCtrlId, PALL_SELID_UIELEMENTS i_pAllSelIDUIElems)
{
	HRESULT retVal = S_OK;
	PIDLISTNODE pCurrNode = i_pAllSelIDUIElems->pCertListHead;
	int nItem = 0;
	int nSubItem = 0;
	HWND hwndListCtrl = GetDlgItem(i_nListCtrlId);
	_bstr_t tbstrItemText = "";

	while(pCurrNode != NULL && retVal == S_OK)
	{
		//Fill the common name of the cert
		retVal = _GetCertCN(pCurrNode->pDecCertInfo->tbstrSubjectDN,&tbstrItemText);
		if(retVal == S_OK)
		{
			retVal = _AddItemInListCtrl(hwndListCtrl,nItem,nSubItem,tbstrItemText);
			if(retVal == S_OK)
				nSubItem++;
		}

		//Fill the friendly name if the default font can support the custom language
		if(retVal == S_OK)
		{
			if(m_pUICtxt->pfontInfoCustomFonts->tbstrTextFont == m_pUICtxt->pfontInfoDefaultFonts->tbstrTextFont) 
			{
				retVal = _AddItemInListCtrl(hwndListCtrl,nItem,nSubItem,pCurrNode->pAuxCertInfo->tbstrFrndlyName);
				if(retVal == S_OK)
					nSubItem++;
			}
		}

		//Add the cert expiration date
		if(retVal == S_OK)
		{
			retVal = _FormatDate(pCurrNode->pDecCertInfo->dateExpDate,&tbstrItemText);
			if(retVal == S_OK)
			{
				retVal = _AddItemInListCtrl(hwndListCtrl,nItem,nSubItem,tbstrItemText);
				if(retVal == S_OK)
					nSubItem++;
			}
		}

		pCurrNode = pCurrNode->pidlistnodeNext;
		nItem++;
		nSubItem = 0;

	}

	//Set the selected cert
	ListView_SetItemState(hwndListCtrl, i_pAllSelIDUIElems->nSelectedIDFromList, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	
	return retVal;
}

HRESULT CPtaUI::_AddItemInListCtrl(HWND i_hwndListCtrl,int i_nItem,int i_nSubItem,_bstr_t& i_tbstrItemText)
{
	HRESULT retVal = S_OK;
	LVITEM lvItem;

	//Insert items
	lvItem.iItem = i_nItem;
	lvItem.iSubItem = i_nSubItem;
	lvItem.state = 0;//LVIS_SELECTED|LVIS_FOCUSED;
	lvItem.stateMask = 0;//LVIS_SELECTED|LVIS_FOCUSED;
	lvItem.lParam = i_nItem;
	lvItem.pszText = i_tbstrItemText;
	if(i_nSubItem) //If this is a subitem
	{
		lvItem.mask = LVIF_TEXT;
		if(!ListView_SetItem(i_hwndListCtrl, &lvItem))
			retVal = E_SETITEMFAILED;
	}
	else //If this is an item
	{
		lvItem.mask = LVIF_TEXT | LVIF_STATE | LVIF_DI_SETITEM|LVIF_PARAM;
		if(ListView_InsertItem(i_hwndListCtrl, &lvItem) == -1)
			retVal = E_INSERTITEMFAILED;
	}
	
			
	return retVal;
}

LRESULT CPtaUI::OnItemchangedList_CertList(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLISTVIEW pnmv;
	pnmv = (LPNMLISTVIEW)pnmh;
	HRESULT retVal = S_OK;
	if(ListView_GetItemState(GetDlgItem(IDC_LIST_CERTLIST), pnmv->iItem, LVIS_SELECTED) == LVIS_SELECTED)
	{
		PALL_SELID_UIELEMENTS pAllSelIDUIElems;
		pAllSelIDUIElems = (PALL_SELID_UIELEMENTS)m_pUICtxt->pvUIElements;
		pAllSelIDUIElems->nSelectedIDFromList = pnmv->lParam;
		retVal = _DisplayCert();
		_ShowTransparentBitmap(IDC_CERT_LOGO);
	}
	bHandled = FALSE;
	return 0;
}

LRESULT CPtaUI::OnBtn1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Store parameters
	retVal = _StoreParams();

	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	//Change cursor to sand clock
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

	//Call the handler function
	if(retVal == S_OK)
		retVal = m_pUICtxt->pbtnFns->lpfnBtn1Fn(m_pOpCtxt);

	//Change cursor pointer
	hCursor = LoadCursor(NULL, IDC_ARROW);
	if(hCursor)
		SetCursor(hCursor);

	//DoTeardown
	retVal2 = _DoTearDown(nCurrOperation);

	//If everything is ok
	if(retVal == S_OK && retVal2 == S_OK && m_pUICtxt)
	{	
		//DoSetup
		retVal = _DoSetup();
	}

	//If things are not ok or if there is no ui context to display
	if(retVal != S_OK || retVal2 != S_OK || !m_pUICtxt)
	{
		EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
		
}

LRESULT CPtaUI::OnBtn2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	

	//Store parameters
	retVal = _StoreParams();
	
	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	//Change cursor to sand clock
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

	//Call the handler function
	if(retVal == S_OK)
		retVal = m_pUICtxt->pbtnFns->lpfnBtn2Fn(m_pOpCtxt);

	//Change cursor pointer
	hCursor = LoadCursor(NULL, IDC_ARROW);
	if(hCursor)
		SetCursor(hCursor);

	//DoTeardown
	retVal2 = _DoTearDown(nCurrOperation);

	//If everything is ok
	if(retVal == S_OK && retVal2 == S_OK && m_pUICtxt)
	{	
		//DoSetup
		retVal = _DoSetup();
	}

	//If things are not ok
	if(retVal != S_OK || retVal2 != S_OK || !m_pUICtxt)
	{
		EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}

LRESULT CPtaUI::OnBtn3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Store parameters
	retVal = _StoreParams();

	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	//Call the handler function
	if(retVal == S_OK)
		retVal = m_pUICtxt->pbtnFns->lpfnBtn3Fn(m_pOpCtxt);

	//Change cursor pointer
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

	//DoTeardown
	retVal2 = _DoTearDown(nCurrOperation);

	//Change cursor pointer
	hCursor = LoadCursor(NULL, IDC_ARROW);
	if(hCursor)
		SetCursor(hCursor);

	//If everything is ok
	if(retVal == S_OK && retVal2 == S_OK && m_pUICtxt)
	{	
		//DoSetup
		retVal = _DoSetup();
	}

	//If things are not ok
	if(retVal != S_OK || retVal2 != S_OK || !m_pUICtxt)
	{
		//End Dialog
		EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}


LRESULT CPtaUI::OnBtn4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	int nCurrOperation;

	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	if(nCurrOperation == EXPORTP12_BASE)
	{
		retVal = _DoBrowse();
	}

	return retVal;
}


LRESULT CPtaUI::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Store parameters
	retVal = _StoreParams();

	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	//Call the handler function
	if(retVal == S_OK)
	{
		if(m_nCurrWiz > 0)
			retVal = m_pUICtxt->pbtnFns->lpfnBtn3Fn(m_pOpCtxt);
		else
			retVal = m_pUICtxt->pbtnFns->lpfnBtn2Fn(m_pOpCtxt);
	}

	//Change cursor pointer
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

	//DoTeardown
	retVal2 = _DoTearDown(nCurrOperation);

	//Change cursor pointer
	hCursor = LoadCursor(NULL, IDC_ARROW);
	if(hCursor)
		SetCursor(hCursor);

	//If everything is ok
	if(retVal == S_OK && retVal2 == S_OK && m_pUICtxt)
	{	
		//DoSetup
		retVal = _DoSetup();
	}

	//If things are not ok
	if(retVal != S_OK || retVal2 != S_OK || !m_pUICtxt)
	{
		//End Dialog
		EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}

HRESULT CPtaUI::_StoreParams()
{
	HRESULT retVal = S_OK;

	//Depending upon the ui type, store the parameters

	// Sasi 05/05/03
	// Added new case statements for storing parameters in GetSecretQuestion, 
	// ResetPassword and CreateSecret dialogs
	switch((m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS|FLAG_BITS)))
	{
		case OPENPROF_OPEN_BASE :
			retVal = _StoreOpenUIParams(TRUE);
			break;

		case OPENPROF_CREATE_BASE :
			retVal = _StoreOpenUIParams(FALSE);
			break;

		case SELID_BASE :
			retVal = _StoreSelectUIParams();
			break;

		case SIGNMSG_BASE :
			retVal = _StoreSignUIParams();
			break;

		case INTRO_BASE :
			break;

		case CREATEPASSWD_BASE :
			retVal = _StoreCreatePasswdParams();
			break;

		case ENTERPASSWD_BASE :
			retVal = _StoreEnterPasswdParams();
			break;

		case CHANGEPASSWD_BASE :
			retVal = _StoreChangePasswdParams();
			break;

		case IMPORTP12_BASE :
			retVal = _StoreImportP12Params();
			break;

		case EXPORTP12_BASE:
			retVal = _StoreExportP12Params();
			break;

		case GETSECRETQUESTION_BASE :
			retVal = _StoreGetSecretQuestionUIParams();
			break;

		case RESETPASSWD_BASE :
			retVal = _StoreResetPasswdParams();
			break;

		case CREATESECRET_BASE :
			retVal = _StoreCreateSecretParams();
			break;

		default :
			retVal =  E_INVALIDFLAGS;
	}
	return retVal;
}

HRESULT CPtaUI::_DoTearDown(int i_nCurrOperation)
{
	HRESULT retVal = S_OK;

	m_boolFocusSet = FALSE;

	retVal = _TeardownVRSNLogo();

	//Tear down the separators
	if(!m_pUICtxt)
		retVal = _TeardownSeparator();

	//Tear down the ui
	if(retVal == S_OK)
	{
		
		/*Set the ui elements depending upon the type of ui*/

		// Sasi 05/05/03
		// Added new case statements for destroying GetSecretQuestion, 
		// ResetPassword and CreateSecret dialogs
		switch(i_nCurrOperation)
		{
		case OPENPROF_OPEN_BASE :
			retVal = _TeardownOpenUI(TRUE);
			break;

		case OPENPROF_CREATE_BASE :
			retVal = _TeardownOpenUI(FALSE);
			break;

		case SELID_BASE :
			retVal = _TeardownSelectUI();
			break;

		case SIGNMSG_BASE :
			retVal = _TeardownSignUI();
			break;

		case INTRO_BASE :
			retVal = _TeardownIntroUI();
			break;

		case CREATEPASSWD_BASE :
			retVal = _TeardownCreatePasswdUI();
			break;

		case ENTERPASSWD_BASE :
			retVal = _TeardownEnterPasswdUI();
			break;

		case CHANGEPASSWD_BASE :
			retVal = _TeardownChngPasswdUI();
			break;

		case IMPORTP12_BASE :
			retVal = _TeardownImportP12UI();
			break;
		
		case EXPORTP12_BASE :
			retVal = _TeardownExportP12UI();
			break;

		case GETSECRETQUESTION_BASE :
			retVal = _TeardownGetSecretQuestionUI();
			break;

		case RESETPASSWD_BASE :
			retVal = _TeardownResetPasswdUI();
			break;

		case CREATESECRET_BASE :
			retVal = _TeardownCreateSecretUI();
			break;

		default :
			retVal =  E_INVALIDFLAGS;
		}
		
	}

	/*Teardown the header*/
	if(retVal == S_OK)
	{
		retVal = _TeardownHeader();
	}

	/*Teardown the fonts*/
	if(retVal == S_OK && !m_pUICtxt)
	{
		retVal = _TeardownFonts();
	}


	return retVal;
}

HRESULT CPtaUI::_StoreOpenUIParams(BOOL boolIsOpen)
{
	HRESULT retVal = S_OK;
	PALL_OPENPROF_UIELEMENTS pAllOpenProfUIElems;

	pAllOpenProfUIElems = (PALL_OPENPROF_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the username parameter
	if(!boolIsOpen || ((PALL_OPENPROF_UIELEMENTS)m_pUICtxt->pvUIElements)->nNumOfProfiles == 0)
	{
		retVal = _GetDlgItemText(IDC_EDIT1,&(pAllOpenProfUIElems->tbstrProfName));
	}
	else
	{
		retVal = _GetCurrListItem(IDC_COMBO1, &(pAllOpenProfUIElems->tbstrProfName));
	}

	if(retVal == S_OK)
	{
		//Get the password param
		retVal = _GetDlgItemText(IDC_EDIT2,&(pAllOpenProfUIElems->tbstrPassword));
		if(!boolIsOpen) //Only if this is a create, we will obtain the confirm password
		{
			if(retVal == S_OK)
			{
				//Get the cofirm password param
				retVal = _GetDlgItemText(IDC_EDIT3,&(pAllOpenProfUIElems->tbstrConfirmPassword));
			}
		}
		else
		{
			pAllOpenProfUIElems->tbstrConfirmPassword = "";
		}
	}
	return retVal;
}

HRESULT CPtaUI::_StoreCreatePasswdParams()
{
	HRESULT retVal = S_OK;
	PALL_CREATEPASSWD_UIELEMENTS pAllCreatePasswdUIElems;

	pAllCreatePasswdUIElems = (PALL_CREATEPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	if(retVal == S_OK)
	{
		//Get the password param XXX
		retVal = _GetDlgItemText(IDC_EDIT2,&(pAllCreatePasswdUIElems->tbstrNewPassword));
		if(retVal == S_OK)
		{
			//Get the cofirm password param
			retVal = _GetDlgItemText(IDC_EDIT3,&(pAllCreatePasswdUIElems->tbstrConfirmPassword));
		}
	}
	return retVal;
}

HRESULT CPtaUI::_StoreEnterPasswdParams()
{
	HRESULT retVal;
	PALL_ENTERPASSWD_UIELEMENTS pAllEnterPasswdUIElems;

	pAllEnterPasswdUIElems = (PALL_ENTERPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	retVal = _GetDlgItemText(IDC_EDIT2,&(pAllEnterPasswdUIElems->tbstrThePassword));

	return(retVal);
}

HRESULT CPtaUI::_StoreChangePasswdParams()
{
	HRESULT retVal = S_OK;
	PALL_CHANGEPASSWD_UIELEMENTS pAllChngPasswdUIElems;

	pAllChngPasswdUIElems = (PALL_CHANGEPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the oldpassword
	retVal = _GetDlgItemText(IDC_EDIT2,&(pAllChngPasswdUIElems->tbstrOldPassword));
	
	if(retVal == S_OK)
	{
		//Get the password param
		retVal = _GetDlgItemText(IDC_EDIT3,&(pAllChngPasswdUIElems->tbstrNewPassword));
		if(retVal == S_OK)
		{
			//Get the cofirm password param
			retVal = _GetDlgItemText(IDC_EDIT4,&(pAllChngPasswdUIElems->tbstrConfirmPassword));
		}
	}
	return retVal;
}

HRESULT CPtaUI:: _StoreImportP12Params()
{
	HRESULT retVal = S_OK;
	PALL_IMPORTP12_UIELEMENTS pAllImportP12UIElems;

	pAllImportP12UIElems = (PALL_IMPORTP12_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the password
	retVal = _GetDlgItemText(IDC_EDIT2,&(pAllImportP12UIElems->tbstrP12Passwd));
	
	return retVal;
}

HRESULT CPtaUI::_StoreExportP12Params()
{
	HRESULT retVal = S_OK;
	PALL_EXPORTP12_UIELEMENTS pAllExportP12UIElems;

	pAllExportP12UIElems = (PALL_EXPORTP12_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the filename parameter
	if(pAllExportP12UIElems->boolShowFileName)
		retVal = _GetDlgItemText(IDC_EDIT1,&(pAllExportP12UIElems->tbstrKeyFile));
	
	if(retVal == S_OK)
	{
		//Get the password param
		retVal = _GetDlgItemText(IDC_EDIT2,&(pAllExportP12UIElems->tbstrP12Passwd));
		if(retVal == S_OK)
		{
			//Get the cofirm password param
			retVal = _GetDlgItemText(IDC_EDIT3,&(pAllExportP12UIElems->tbstrP12ConfPasswd));
		}
	
	}
	return retVal;
}


HRESULT CPtaUI::_StoreSelectUIParams()
{
	HRESULT retVal = S_OK;
	PALL_SELID_UIELEMENTS pAllSelIDUIElems;

	pAllSelIDUIElems = (PALL_SELID_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the Check box state
	pAllSelIDUIElems->nChkBoxState = IsDlgButtonChecked(IDC_CHECKBOX);
	
	return retVal;
}

HRESULT CPtaUI::_StoreSignUIParams()
{
	HRESULT retVal = S_OK;

	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_StoreGetSecretQuestionUIParams
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function gets the profile name from CreateSecret dialog
//						and stores it in a global variable.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_StoreGetSecretQuestionUIParams()
{
	HRESULT retVal = S_OK;
	PALL_GETSECRETQUESTION_UIELEMENTS pAllGetSecretQuestionUIElems;

	pAllGetSecretQuestionUIElems = (PALL_GETSECRETQUESTION_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the username parameter
	retVal = _GetDlgItemText(IDC_EDIT1,&(pAllGetSecretQuestionUIElems->tbstrProfName));

	return retVal;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_StoreResetPasswdParams
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function gets the secret answer and new password from
//						ResetPassword dialog and stores them in global variables.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_StoreResetPasswdParams()
{
	HRESULT retVal = S_OK;
	PALL_RESETPASSWD_UIELEMENTS pAllResetPasswdUIElems;

	pAllResetPasswdUIElems = (PALL_RESETPASSWD_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the secret answer
	retVal = _GetDlgItemText(IDC_EDIT1,&(pAllResetPasswdUIElems->tbstrSecretAnswer));
	
	if(retVal == S_OK)
	{
		//Get the password param
		retVal = _GetDlgItemText(IDC_EDIT3,&(pAllResetPasswdUIElems->tbstrNewPassword));
		if(retVal == S_OK)
		{
			//Get the cofirm password param
			retVal = _GetDlgItemText(IDC_EDIT4,&(pAllResetPasswdUIElems->tbstrConfirmPassword));
		}
	}
	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_StoreCreateSecretParams
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function gets the secret question and answer from
//						CreateSecret dialog and stores them in global variables.
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_StoreCreateSecretParams()
{
	HRESULT retVal = S_OK;
	PALL_CREATESECRET_UIELEMENTS pAllCreateSecretUIElems;

	pAllCreateSecretUIElems = (PALL_CREATESECRET_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	//Get the secret question
	retVal = _GetDlgItemText(IDC_EDIT5,&(pAllCreateSecretUIElems->tbstrSecretQuestion));
	
	if(retVal == S_OK)
	{
		//Get the secret answer
		retVal = _GetDlgItemText(IDC_EDIT1,&(pAllCreateSecretUIElems->tbstrSecretAnswer));
	}
	return retVal;
}

HRESULT CPtaUI::_GetDlgItemText(int i_nDlgItemId, _bstr_t* o_ptbstrDlgItemText)
{
	HRESULT retVal = S_OK;
	BSTR bstrDlgItemText;
	int nDlgItemTextLen;
	HWND hwndDlgItem = GetDlgItem(i_nDlgItemId);

	nDlgItemTextLen = ::GetWindowTextLength(hwndDlgItem);
	if(!nDlgItemTextLen)
	{
		*o_ptbstrDlgItemText = "";
	}
	else
	{
		bstrDlgItemText = SysAllocStringLen(NULL,nDlgItemTextLen+1);
		if(!bstrDlgItemText)
		{
			retVal = E_FAIL;
		}
		else
		{
			if(!GetDlgItemText(i_nDlgItemId,bstrDlgItemText))
			{
				retVal = E_GETDLGITEMTEXTFAILED;
			}
			else
			{
				bstrDlgItemText[nDlgItemTextLen] = L'\0';
				*o_ptbstrDlgItemText = bstrDlgItemText;
			}

			//Zero the memory before destroying the Text
			if(retVal == S_OK)
			{
				//memset(bstrDlgItemText, 0, (*o_ptbstrDlgItemText).length()*2);
				EraseMemory((unsigned int)(*o_ptbstrDlgItemText).length()*2, (unsigned char*)bstrDlgItemText);
				
			}

			SysFreeString(bstrDlgItemText);
		}
	}
	return retVal;
}

HRESULT CPtaUI::_TeardownSeparator()
{
	m_nCYSet = 0;
	return S_OK;
}

HRESULT CPtaUI::_TeardownOpenUI(BOOL boolIsOpen)
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	if(!boolIsOpen)
	{
		::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
		::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	}
	else
	{
		//Delete all the strings from the combo box
		SendDlgItemMessage(IDC_COMBO1, CB_RESETCONTENT, NULL, NULL);
		::ShowWindow(GetDlgItem(IDC_COMBO1),FALSE);
	}
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT1),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownCreatePasswdUI()
{

	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT4),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownEnterPasswdUI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownChngPasswdUI()
{

		HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT4),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownImportP12UI()
{

	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}


HRESULT CPtaUI::_TeardownExportP12UI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT1),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	::ShowWindow(GetDlgItem(IDBTN4),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownSelectUI()
{
	HRESULT retVal = S_OK;

	//ShowWindow(FALSE);
	//Set the ui size to 0
	m_nUISize = 0;

	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_CHECKBOX),FALSE);
	
	//Make the cert invisible
	RECT certRect;
	certRect.left = CERT_LEFT_MARGIN;
	certRect.top = m_nCertPosY;
	certRect.right = certRect.left + CERT_WIDTH + 2;
	certRect.bottom = certRect.top + CERT_HEIGHT + 2;

	
	if(!InvalidateRect(&certRect),FALSE)
		retVal = E_INVALIDATERECTFAILED;

	::ShowWindow(GetDlgItem(IDC_CERT_LOGO), FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL5),FALSE); 


	//Free the bitmaps
	_FreeBitmap(m_hCertBitmap);
	DeleteObject(m_hTextureBrush);
	m_hCertBitmap = NULL;
	m_hTextureBrush = NULL;

	//Remove all the entries from the cert list
	ListView_DeleteAllItems(GetDlgItem(IDC_LIST_CERTLIST));
	for(int i=0;i<3;++i)
		ListView_DeleteColumn(GetDlgItem(IDC_LIST_CERTLIST),0);

	::ShowWindow(GetDlgItem(IDC_LIST_CERTLIST),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	//ShowWindow(TRUE);
	return retVal;
}

HRESULT CPtaUI::_TeardownSignUI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	if (!DeleteFile(m_szTempFileName))
	{
		delete m_szTempFileName;
		m_szTempFileName = NULL;
	}	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_IBROWSER),FALSE);	
	::ShowWindow(GetDlgItem(IDC_EDIT_RDONLY),FALSE);	
	::ShowWindow(GetDlgItem(IDC_OUTLINE),FALSE);	
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownIntroUI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	::ShowWindow(GetDlgItem(IDC_UI_TEXT), FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	m_nUISize = 0;

	return retVal;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_TeardownGetSecretQuestionUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function closes the GetSecretQuestion dialog. 
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_TeardownGetSecretQuestionUI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_EDIT1),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_TeardownResetPasswdUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function closes the ResetPassword dialog. 
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_TeardownResetPasswdUI()
{

		HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	::ShowWindow(GetDlgItem(IDC_EDIT3),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL3),FALSE);
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_LABEL4),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT1),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL2),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT4),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL5),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL6),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}



///////////////////////////////////////////////////////////////////////////////
//
//	Function Name	:	_TeardownCreateSecretUI
//
//	Parameters
//
//	Return Values	:
//		S_OK if the function succeeds
//
//	Description		:	This function closes the CreateSecret dialog. 
//
//  REV HISTORY
//  Date           Author           Desc
//  ----           ------           ----
// 05-05-03        Sasi             Created.
///////////////////////////////////////////////////////////////////////////////
HRESULT CPtaUI::_TeardownCreateSecretUI()
{

		HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	//Make the labels and edit boxes invisible
	::ShowWindow(GetDlgItem(IDC_EDIT1),FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT5),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1),FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL5),FALSE);
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CPtaUI::_TeardownHeader()
{
	HRESULT retVal = S_OK;

	m_nCurrWiz = -1;

	//Make the header invisible
	::ShowWindow(GetDlgItem(IDC_HEADER_LOGO),FALSE);

	//Free the bitmap
	_FreeBitmap(m_hBitmap);
	m_hBitmap = 0;

	return retVal;
}

HRESULT CPtaUI::_TeardownFonts()
{
	HRESULT retVal = S_OK;
	
	//Delete all the fonts
	DeleteObject((HFONT)m_hFontDefWizTitleFont);
	m_hFontDefWizTitleFont = NULL;

	DeleteObject((HFONT)m_hFontDefUITitleFont);
	m_hFontDefUITitleFont = NULL;

	DeleteObject((HFONT)m_hFontDefTextFont);
	m_hFontDefTextFont = NULL;

	DeleteObject((HFONT)m_hFontDefBtnFont);
	m_hFontDefBtnFont = NULL;
	
	DeleteObject((HFONT)m_hFontCustWizTitleFont);
	m_hFontCustWizTitleFont = NULL;

	DeleteObject((HFONT)m_hFontCustUITitleFont);
	m_hFontCustUITitleFont = NULL;

	DeleteObject((HFONT)m_hFontCustTextFont);
	m_hFontCustTextFont = NULL;

	DeleteObject((HFONT)m_hFontCustBtnFont);
	m_hFontCustBtnFont = NULL;

	DeleteObject((HFONT)m_hFontCertInfoFont);
	m_hFontCertInfoFont = NULL;

	DeleteObject((HFONT)m_hFontValidityLabelFont);
	m_hFontValidityLabelFont = NULL;

	m_boolFontsSet = FALSE;
	return retVal;
}

HRESULT CPtaUI::_FillListBox(int i_nListField, HFONT i_hFontTextFont, _bstr_t* i_ptbstrList, int i_nNumOfElems, _bstr_t& i_tbstrCurrSel)
{
	HRESULT retVal = S_OK;

	do
	{
		//Set the font of the field
		SendDlgItemMessage(i_nListField,WM_SETFONT,(WPARAM)i_hFontTextFont,TRUE);

		//Fill the list
		for(int i=0;i<i_nNumOfElems;++i)
		{
			SendDlgItemMessage(i_nListField, CB_ADDSTRING,NULL,(LPARAM)(LPCTSTR)i_ptbstrList[i]);
		}

		SendDlgItemMessage(i_nListField, CB_INSERTSTRING,i_nNumOfElems,(LPARAM)(LPCTSTR)OTHER_PROFNAME_STRING);

		//Set the current selection
		if(i_tbstrCurrSel.length())
		{
			SendDlgItemMessage(i_nListField, WM_SETTEXT,0, (LPARAM)(LPCSTR)i_tbstrCurrSel);
		}
		else
		{
			SendDlgItemMessage(i_nListField, CB_SETCURSEL, (WPARAM)0, NULL);
		}

	}while(0);
	return retVal;
}

HRESULT CPtaUI::_GetCurrListItem(int i_nListField, _bstr_t* o_ptbstrSelectedItem)
{
	HRESULT retVal = S_OK;
	CHAR* pszSelectedItem = NULL;
	int nSelectedItemSize;

	do
	{
		
		nSelectedItemSize = SendDlgItemMessage(i_nListField, WM_GETTEXTLENGTH, NULL, NULL);
		if(nSelectedItemSize == CB_ERR)
			nSelectedItemSize = 0;

		pszSelectedItem = (CHAR*)new CHAR[nSelectedItemSize+1];
		if(!pszSelectedItem)
		{
			retVal = E_FAIL;
			break;
		}
		
		SendDlgItemMessage(i_nListField, WM_GETTEXT, nSelectedItemSize+1, (LPARAM)pszSelectedItem);
		pszSelectedItem[nSelectedItemSize] = '\0';

		*o_ptbstrSelectedItem = pszSelectedItem;

	}while(0);

	delete[] pszSelectedItem;
	return retVal;
}

HRESULT CPtaUI::_TeardownVRSNLogo()
{
	::ShowWindow(GetDlgItem(IDC_VRSN_LOGO), FALSE);
	
	/*RECT rectDlgSize;

	GetClientRect(&rectDlgSize);

	HBITMAP hBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_VSLARGE));
	BITMAP     bm;   

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

	RECT rectBitmap;
	rectBitmap.left = VRSNLOGO_RGN_X;
	rectBitmap.top = rectDlgSize.bottom - DLG_FOOTER_SIZE + (DLG_FOOTER_SIZE/2 - bm.bmHeight/2);
	rectBitmap.right = VRSNLOGO_RGN_X + bm.bmWidth; 
	rectBitmap.bottom = rectBitmap.top + bm.bmHeight;
	
	DeleteObject(hBitmap);

	InvalidateRect(&rectBitmap);*/
	return S_OK;
}

HRESULT CPtaUI::put_NextMessageToShow(VARIANT* i_pvarMsgToShow)
{
	HRESULT retVal = S_OK;

	m_tbstrMsgToShow = i_pvarMsgToShow->bstrVal;

	return retVal;
}


HRESULT CPtaUI::_ShowTransparentBitmap(LONG i_ResourceId)
{
	HBITMAP hBitmap = NULL;
	HRESULT retVal = S_OK;
	HDC hdc = ::GetDC(GetDlgItem(i_ResourceId));
	BITMAP     bm;   
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT      ptSize;
	
	if(i_ResourceId == IDC_CERT_LOGO)
	{
		PALL_SELID_UIELEMENTS pAllSelIDUIElems = (PALL_SELID_UIELEMENTS)m_pUICtxt->pvUIElements;
		PIDLISTNODE pidListNodeCurrSelect;

		pidListNodeCurrSelect = pAllSelIDUIElems->pCertListHead;
		for(int i=0;i<pAllSelIDUIElems->nSelectedIDFromList;++i)
			pidListNodeCurrSelect = pidListNodeCurrSelect->pidlistnodeNext;
		
		//Obtain the cert logo
		if(pidListNodeCurrSelect->pAuxCertInfo->tbstrLogoUrl.length())
			retVal = _GetBitmap(pidListNodeCurrSelect->pAuxCertInfo->tbstrLogoUrl,&hBitmap);
	}
	else
		if(i_ResourceId == IDC_VRSN_LOGO)
		{
			if(m_pUICtxt->tbstrCustAffLogoUrl.length())
				retVal = _GetBitmap(m_pUICtxt->tbstrCustAffLogoUrl, &hBitmap);

			if(!hBitmap)
				hBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(IDB_VSLARGE));
		}
		else
			if(i_ResourceId == IDC_HEADER_LOGO)
			{
				if(m_pUICtxt->tbstrCustLogoUrl.length())
					retVal = _GetBitmap(m_pUICtxt->tbstrCustLogoUrl, &hBitmap);
				else
					retVal = _GetBitmap(m_pUICtxt->tbstrDefLogoUrl, &hBitmap);
			}

	if(hBitmap == NULL)
		return retVal;

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hBitmap);   // Select the bitmap

	GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;            // Get width of bitmap
	ptSize.y = bm.bmHeight;           // Get height of bitmap
	DPtoLP(hdcTemp, &ptSize, 1);      // Convert from device
		                              // to logical points

	// Create some DCs to hold temporary data.
	hdcBack   = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem    = CreateCompatibleDC(hdc);
	hdcSave   = CreateCompatibleDC(hdc);
   
	// Create a bitmap for each DC. DCs are required for a number of
	// GDI functions.   
	
	// Monochrome DC
	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
   
	// Monochrome DC
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	// Each DC must select a bitmap object to store pixel data.
	bmBackOld   = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP)SelectObject(hdcSave, bmSave);
	
	// Set proper mapping mode.
	SetMapMode(hdcTemp, GetMapMode(hdc));
   
	// Save the bitmap sent here, because it will be overwritten.
	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC to the color.
	// contained in the parts of the bitmap that should be transparent
	cColor = SetBkColor(hdcTemp, RGB(191, 191, 191));

	// Create the object mask for the bitmap by performing a BitBlt
	// from the source bitmap to a monochrome bitmap.
	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	// Set the background color of the source DC back to the original
	// color.
	SetBkColor(hdcTemp, cColor);

	// Create the inverse of the object mask.
	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0,
          NOTSRCCOPY);
   
	// Copy the background of the main DC to the destination.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, 0,0, /*VRSNLOGO_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE + (DLG_FOOTER_SIZE/2 - bm.bmHeight/2),*/
          SRCCOPY);   
	
	// Mask out the places where the bitmap will be placed.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
   
	// Mask out the transparent colored pixels on the bitmap.
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

	// XOR the bitmap with the background on the destination DC.
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
   
	// Copy the destination to the screen.
	BitBlt(hdc, 0,0,/*VRSNLOGO_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE + (DLG_FOOTER_SIZE/2 - bm.bmHeight/2),*/ptSize.x, ptSize.y, hdcMem, 0, 0,
          SRCCOPY);
	
	// Place the original bitmap back into the bitmap sent here.
    BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Delete the memory bitmaps.
   DeleteObject(SelectObject(hdcBack, bmBackOld));
   DeleteObject(SelectObject(hdcObject, bmObjectOld));
   DeleteObject(SelectObject(hdcMem, bmMemOld));
   DeleteObject(SelectObject(hdcSave, bmSaveOld));   
   
   // Delete the memory DCs.
   DeleteDC(hdcMem);   
   DeleteDC(hdcBack);   
   DeleteDC(hdcObject);
   DeleteDC(hdcSave);   
   DeleteDC(hdcTemp);

   DeleteObject(hBitmap);

   return retVal;
}



HRESULT CPtaUI::_DoBrowse(BOOL i_boolSaveFile)
{
	HRESULT hr = S_OK;
	_bstr_t tbstrFile = "";

	hr = _SelectFile(GetFocus(), IDS_FILEFILTER, i_boolSaveFile, &tbstrFile);

	if(hr == S_OK)
		::SetWindowText(GetDlgItem(IDC_EDIT1),tbstrFile);

	return hr;
}


HRESULT CPtaUI::_SelectFile(HWND hParent, UINT idOFFilter, BOOL i_boolSaveFile, _bstr_t* o_ptbstrSelFile)
{
	HRESULT hr = S_OK;
	OPENFILENAME theFileName;
	TCHAR szFileName[2*MAX_PATH];
	_bstr_t tbstrFilter = "", tbstrTitle = "";
	WCHAR* pwszTempBuf = NULL;
	TCHAR* tcharFilter = NULL;

	*o_ptbstrSelFile = "";

	do
	{
		if(idOFFilter == 0)
		{
			hr = E_EMPTYARGS;
			break;
		}

		memset(&theFileName,0,sizeof(OPENFILENAME));
		lstrcpy(szFileName, "");
		theFileName.lStructSize = sizeof(OPENFILENAME);
		theFileName.hwndOwner = hParent;
		theFileName.lpstrFile = szFileName;
		theFileName.nMaxFile = 2*MAX_PATH;

		pwszTempBuf = (WCHAR*)malloc(sizeof(WCHAR) * MAX_RES_STRING_SIZE);
		if(!pwszTempBuf)
		{
			hr = E_OUTOFMEMORY;
			break;
		}

		hr = _LoadStringW(_Module.m_hInst, m_pUICtxt->nDefLangId, idOFFilter, pwszTempBuf, MAX_RES_STRING_SIZE);
		if(hr != S_OK)
			break;

		tbstrFilter = pwszTempBuf;
		tcharFilter =  (TCHAR*) malloc(lstrlen((CHAR*)tbstrFilter) + 6);
		if(!tcharFilter)
		{
			hr = E_OUTOFMEMORY;
			break;
		}

		lstrcpy(tcharFilter,(CHAR*)tbstrFilter);
		memcpy(tcharFilter+lstrlen((CHAR*)tbstrFilter),(BYTE*)"\0*.*\0\0",6);
		theFileName.lpstrFilter = (CHAR*)tcharFilter;

		theFileName.nFilterIndex = 1;
		theFileName.lpstrFileTitle = NULL;
		theFileName.nMaxFileTitle = 0;

		theFileName.lpstrInitialDir = NULL;
	
		if(i_boolSaveFile)
		{
			theFileName.Flags = OFN_HIDEREADONLY;

			if(!GetSaveFileName(&theFileName))
			{
				hr = E_GETSAVEFILERR;
				break;
			}
		}
		else
		{
			theFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if(!GetOpenFileName(&theFileName))
			{
				hr = E_GETOPENFILERR;
				break;
			}
		}

		*o_ptbstrSelFile = theFileName.lpstrFile;

	}while(0);

	if(pwszTempBuf)
	{
		free(pwszTempBuf);
		pwszTempBuf = NULL;
	}

	if(tcharFilter)
	{
		free(tcharFilter);
		tcharFilter = NULL;
	}

	return hr;
}
