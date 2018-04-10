// DNZUI.cpp : Implementation of CDNZUI
#include "stdafx.h"
#include <commdlg.h>
#include <winuser.h>
#include <commctrl.h>
#include <comutil.h>
#include "ptav3.h"
#include "notarize.h"
#include "DNZUI.h"
#include "nzerrs.h"
#include "nzutils.h"
#include "nzdefines.h"
#include "ptaerrs.h"
#include "nzmacros.h"

/////////////////////////////////////////////////////////////////////////////
// CDNZUI

HRESULT CDNZUI::Initialize()
{
	return S_OK;
}

HRESULT CDNZUI::Close()
{
	return S_OK;
}

HRESULT CDNZUI::put_UIContext(PUICTXT i_pUICtxt)
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

HRESULT CDNZUI::get_UIContext(PUICTXT o_pUICtxt)
{
	HRESULT retVal = S_OK;
	retVal = _CopyUIContext(o_pUICtxt,m_pUICtxt);
	return retVal;
}

HRESULT CDNZUI::ShowUI(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;
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


HRESULT CDNZUI::BeginUI(POPCTXT pOpCtxt)
{
	HRESULT retVal = S_OK;
	//Store the op context so that other functions can use it.
	m_pOpCtxt = pOpCtxt;

	//Create Modeless dialog box
	m_hDlgWnd = Create(GetActiveWindow());

	if(m_hDlgWnd)
		m_bModeless = TRUE;
	
	return retVal;
}

HRESULT CDNZUI::UpdateUI()
{
	HRESULT retVal = S_OK;
	SendMessage(WM_COMMAND,IDBTN4);
	return retVal;
}

HRESULT CDNZUI::EndUI()
{
	HRESULT retVal = S_OK;
	int nCurrOperation;
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);
	retVal = _DoTearDown(nCurrOperation);
	DestroyWindow();

	m_bModeless = FALSE;

	return retVal;
}

BOOL CDNZUI::IsModelessDlg()
{
	return m_bModeless;
}


BOOL CDNZUI::IsDialogCancelled()
{
	MSG msg;
	if(::PeekMessage(&msg, m_hWnd, 0, 0, PM_REMOVE))
		::IsDialogMessage(m_hWnd, &msg);

	return m_bIsCancelled;
}


VOID CDNZUI::SetCancelled(BOOL i_bIsCancelled)
{
	m_bIsCancelled = i_bIsCancelled;
}


#if 0
HRESULT CDNZUI::ShowMessage(int i_nMessageType)
{
	HRESULT retVal = S_OK;
	_bstr_t tbstrMessageToDisp = "", tbstrMessageTitle = "";
	WCHAR* pwcharMsg = NULL;
	int nMsgId = 0;

	switch(i_nMessageType)
	{
/*	case (E_INVALIDPASSWD & 0x0000FFFF) :
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
*/
		default :
		retVal = E_NZINVALIDARGS;
		nMsgId = 0;
		break;
	}
	
	if(nMsgId)
	{
		if(nMsgId == -1)
			tbstrMessageToDisp = m_tbstrMsgToShow;
		else
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nMsgId,&pwcharMsg);
			if(retVal == S_OK)
			{
				tbstrMessageToDisp = (WCHAR*)(pwcharMsg);
				FREE_MEMORY(pwcharMsg)
			}
		}

		if(retVal == S_OK)
		{	
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_VS_NZ,&pwcharMsg);
			if(retVal == S_OK)
			{
				tbstrMessageTitle = (WCHAR*)(pwcharMsg);
				MessageBox(tbstrMessageToDisp, tbstrMessageTitle, MB_OK|MB_ICONEXCLAMATION);
			}
		}
	}

	FREE_MEMORY(pwcharMsg)
	
	return retVal;
}


HRESULT CDNZUI::ConfirmAction(int i_nActionType)
{
	HRESULT retVal = S_OK;
	int nMsgId = 0;
	_bstr_t tbstrMessageToDisp = "", tbstrMessageTitle = "";
	WCHAR* pwcharMsg = NULL;

	switch(i_nActionType)
	{
	/*case OPEN_PROF_CREATE:
		nMsgId = IDS_CNFRMACTIONCREATE;
		break;

	case CREATE_PROF_DELETE :
		nMsgId = IDS_CNFRMACTIONDELETE;
		break;

	case CREATE_PROF_OPEN :
		nMsgId = IDS_CNFRMACTIONOPEN;
		break;*/

	default :
		retVal = E_NZINVALIDARGS;
		break;
	}

	if(retVal == S_OK)
	{
		if(nMsgId)
		{
			
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nMsgId,&pwcharMsg);
			if(retVal == S_OK)
			{
				tbstrMessageToDisp = (WCHAR*)pwcharMsg;
				FREE_MEMORY(pwcharMsg)
			}
	
			if(retVal == S_OK)
			{	
				retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_VS_NZ,&pwcharMsg);

				if(retVal == S_OK)
				{
					tbstrMessageTitle = (WCHAR*)(pwcharMsg);

					retVal = MessageBox(tbstrMessageToDisp, tbstrMessageTitle, MB_YESNO|MB_ICONQUESTION);
					if(retVal == IDYES)
						retVal = S_OK;
					else
						retVal = E_USERCANCELLED;
				}
			}
		}
	}

	FREE_MEMORY(pwcharMsg)

	return retVal;
}
#endif


LRESULT CDNZUI::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// Subclass the IDC_LABEL7 static control
	m_SaveLink.SubclassWindow(::GetDlgItem(m_hWnd,IDC_LABEL7));
	m_HyperLink.SubclassWindow(::GetDlgItem(m_hWnd, IDC_LABEL8));
	m_ViewLink.SubclassWindow(::GetDlgItem(m_hWnd, IDC_LABEL3_3));


	/*Do the setup*/
	_DoSetup();

	return 1;  // Let the system set the focus
}


HRESULT CDNZUI::_DoSetup()
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
		switch(m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS))
		{
		case SELFILE_BASE :
			retVal = _SetSelectFileUI();
			break;

		case PROGRESS_BASE :
			retVal = _SetProgressUI();
			break;

		case VERIFYRCPT_BASE :
			retVal = _SetVerifyRcptUI();
			break;

		case ERROR_BASE :
			retVal = _SetErrorUI();
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

HRESULT CDNZUI::_SetDialogDims()
{
	HRESULT retVal = S_OK;
	int nMinDialogSize = 0;

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
		if(m_pUICtxt->nWhichWizardAndUI & DIGNOTREQ_WIZARD_BASE)
		{
			nMinDialogSize = (DLGSIZE_SMALL_CY-DLG_FOOTER_SIZE);
		}
		else
		{
			nMinDialogSize = (DLGSIZE_LARGE_CY-DLG_FOOTER_SIZE);
		}

		if(m_nUISize < nMinDialogSize)
		{
			//Set the window size to the minimum dialog size (for a small dialog box)
			if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, DLGSIZE_SMALL_CY+(rectWindowRect.bottom - rectClientRect.bottom), SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
			m_nCYSet = nMinDialogSize;
		}
		else
		{
			//Set the window size to the calculated size after setting all the UI
			if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, m_nUISize+DLG_FOOTER_SIZE+(rectWindowRect.bottom - rectClientRect.bottom), SWP_NOMOVE|SWP_NOZORDER))
				retVal = E_DLG_SETDIMSFAILED;
			m_nCYSet = m_nUISize+DLG_FOOTER_SIZE;
		}		
	}
	else
	{
		
		if(!SetWindowPos(NULL,0,0,DLGSIZE_SMALL_CX, m_nUISize+DLG_FOOTER_SIZE+rectWindowRect.bottom-rectClientRect.bottom , SWP_NOMOVE|SWP_NOZORDER))
			retVal = E_DLG_SETDIMSFAILED;
	}

	CenterWindow();
	
	return retVal;
}

HRESULT CDNZUI::_SetSeparators()
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

HRESULT CDNZUI::_CreateFonts()
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


	//Create the default underlined text font
	m_hFontDefUndTextFont = _CreateFont(m_pUICtxt->pfontInfoDefaultFonts->dwCharset,
		m_pUICtxt->pfontInfoDefaultFonts->tbstrTextFont, m_nDefTextFontSize, FW_NORMAL, &m_nDefTextFontSize, TRUE);
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

	m_boolFontsSet = TRUE;

	return S_OK;
}

HFONT CDNZUI::_CreateFont(int i_nCharset,_bstr_t& i_tbstrFontName, int i_nFontSize, int i_nFontWeight, int* o_pnActFontHeight, BOOL bIsUnderline)
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
		logFontStruct.lfUnderline = bIsUnderline; 
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


HRESULT CDNZUI::_SetHeader()
{
	HRESULT retVal = S_OK;

	//If the header has already been set, we dont need to do anything.
	if(m_nCurrWiz >= 0)
	{
		return S_OK;
	}

	
	/******** Set the logo **************/
	/*Obtain the logo bitmap*/
	if(m_pUICtxt->tbstrCustLogoUrl.length())
	{
		retVal = _GetBitmap(m_pUICtxt->tbstrCustLogoUrl,&m_hBitmap);
	}
	else
	{
		retVal = _GetBitmap(m_pUICtxt->tbstrDefLogoUrl,&m_hBitmap);
	}

	/*Set the logo bitmap*/
	if(retVal == S_OK)
	{
		SendDlgItemMessage(IDC_HEADER_LOGO,STM_SETIMAGE,IMAGE_BITMAP, (LPARAM)m_hBitmap);
	

		/*Place the bitmap*/
		retVal = _SetField_PlacementInRegion(IDC_HEADER_LOGO,DLGSIZE_CX,BITMAP_MAX_CY,0,HEADER_RIGHT_MARGIN,
			HEADER_TOPBTM_MARGIN,HEADER_TOPBTM_MARGIN,0,DLG_HEADER_SIZE,DLGSIZE_CX,0,RGN_ANCH_TOPRIGHT,
			FLD_XANCH_RIGHT, FLD_YANCH_MIDDLE,NULL,&m_nHeaderSize);
		if(retVal != S_OK)
		{
			_FreeBitmap(m_hBitmap);
			m_hBitmap = NULL;
		}
		else //show the logo
		{
			::ShowWindow(GetDlgItem(IDC_HEADER_LOGO),TRUE);
		}
	}


#ifdef DEBUG
	//For debug purposes if the logo cannot be rendered show the error message box
	if(retVal != S_OK)
	{
		TCHAR tstrErrMsg[1024];
		_stprintf(tstrErrMsg,"Error %d occured while rendering the logo", retVal);
		//MessageBox(tstrErrMsg);
	}
#endif
	
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
		switch(m_pUICtxt->nWhichWizardAndUI & WIZARD_BITS)
		{
		case NO_WIZARD_BASE :
			switch(m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS)
			{
			
			case ERROR_BASE :
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_ERROR_UIELEMENTS)(m_pUICtxt->pvUIElements))->theUIElements.tbstrTitle);
					break;
				}
				

			case SELFILE_BASE :
				if(((PALL_SELFILE_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_SELFILE_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_SELFILE_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
				break;

			case PROGRESS_BASE :
				if(((PALL_PROGRESS_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_PROGRESS_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_PROGRESS_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
	
				break;

			case VERIFYRCPT_BASE :
				if(((PALL_VERIFYRCPT_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle.length())
				{	
					//Set the font and the text for this field
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontCustWizTitleFont,
											((PALL_VERIFYRCPT_UIELEMENTS)(m_pUICtxt->pvUIElements))->theCustUIElements.tbstrTitle);
				
				}
				else
				{
					retVal = _SetField_FontAndText(IDC_HEADER_TITLE,m_hFontDefWizTitleFont,
											((PALL_VERIFYRCPT_UIELEMENTS)(m_pUICtxt->pvUIElements))->theDefUIElements.tbstrTitle);
				}
	
				break;

			default :
				retVal = E_INVALIDFLAGS;
				break;
			}
			//If a custom title is specified use that, or use the default
			
			break;

		case DIGNOTREQ_WIZARD_BASE :
		case VERIFYRCPT_WIZARD_BASE :
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
			retVal = _SetField_PlacementInRegion(IDC_HEADER_TITLE,(DLGSIZE_CX - HEADER_LEFT_MARGIN),
							(m_nHeaderSize - (HEADER_TOPBTM_MARGIN*2)),HEADER_LEFT_MARGIN,0,
							HEADER_TOPBTM_MARGIN,HEADER_TOPBTM_MARGIN,0,m_nHeaderSize,0,0,RGN_ANCH_TOPLEFT,
							FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,NULL);
		}
		

		
	}

	//Set the current wizard
	if(retVal == S_OK)
	{
		m_nCurrWiz = m_pUICtxt->nWhichWizardAndUI & WIZARD_BITS;
	}
	else
	{
		_FreeBitmap(m_hBitmap);
		m_hBitmap = 0;
	}
	return retVal;
}


HRESULT CDNZUI::_SetField_FontAndText(int i_nFieldId, HFONT i_phFont, _bstr_t& i_tbstrText, int i_nTruncWidth, int i_nWidth, int i_nHeight, int i_nTopBtmMargin, int i_nInterCharSpace, int i_nTruncHeight)
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

	//Truncate the height if needed
	if(i_nTruncHeight && fldSize.cy > i_nTruncHeight)
	{
		fldSize.cy = i_nTruncHeight;
	}

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
					//fldSize.cx += CHKBOX_LEFTRIGHTMARGINS;
					
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

		
		if(!lstrcmp(tstrClassName, "Edit") && !(::GetWindowLong(hWnd,GWL_STYLE) & ES_READONLY))
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

HRESULT CDNZUI::_SetField_PlacementInRegion(int i_nFieldId, int i_nFieldMaxWidth, int i_nFieldMaxHeight, int i_nLeftMargin, int i_nRightMargin, int i_nTopMargin, int i_nBottomMargin, 
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
	if(!::GetWindowRect(hwndField,&rectField))
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

HRESULT CDNZUI::_SetButtons()
{
	HRESULT retVal;

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
				0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_RIGHT,FLD_YANCH_MIDDLE,&nBtn1RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn1Fn));

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN2,BTN_MAX_CX,BTN_MAX_CY,0,(BTN_RIGHT_MARGIN*4)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X+nBtn1RegionWidth,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn2Fn));
			}

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN3,BTN_MAX_CX,BTN_MAX_CY,0,BTN_RIGHT_MARGIN
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X+nBtn1RegionWidth+nBtn2RegionWidth
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
				0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_MIDDLE,&nBtn1RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn1Fn));

			// For an ERROR_BASE, PROGRESS_BASE, VERIFYRCPT_BASE we want to show only the 2 rightmost buttons
			if((m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS) == ERROR_BASE || 
				(m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS) == PROGRESS_BASE || 
				(m_pUICtxt->nWhichWizardAndUI & OPERATION_BITS) == VERIFYRCPT_BASE)
				::ShowWindow(GetDlgItem(IDOK), SW_HIDE);
		

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN2,BTN_MAX_CX,BTN_MAX_CY,(BTN_LEFT_MARGIN),(BTN_RIGHT_MARGIN*2)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X+nBtn1RegionWidth,rectDlgSize.bottom - DLG_FOOTER_SIZE,
				RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_MIDDLE,&nBtn2RegionWidth,NULL,(BOOL)(m_pUICtxt->pbtnFns->lpfnBtn2Fn));
			}

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN3,BTN_MAX_CX,BTN_MAX_CY,(BTN_LEFT_MARGIN),(BTN_RIGHT_MARGIN * 2)
				,0,0,BTN_MIN_CX,DLG_FOOTER_SIZE,BTN1_RGN_X+nBtn1RegionWidth+nBtn2RegionWidth
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

HRESULT CDNZUI::_SetVRSNLogo()
{
	HRESULT retVal;

	//Place the logo
	RECT rectDlgSize;

	GetClientRect(&rectDlgSize);
	
	retVal = _SetField_PlacementInRegion(IDC_VRSN_LOGO,VRSNLOGO_X,VRSNLOGO_Y,0,0,
		0,0,VRSNLOGO_X, DLG_FOOTER_SIZE,VRSNLOGO_RGN_X,rectDlgSize.bottom - DLG_FOOTER_SIZE,
		RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,NULL);
	::ShowWindow(GetDlgItem(IDC_VRSN_LOGO), TRUE);
	
   return retVal;
	
	
}


HRESULT CDNZUI::_SetDigRcpt(int i_nRegionY)
{
	HRESULT retVal;

	//Place the logo
	RECT rectDlgSize;

	GetClientRect(&rectDlgSize);
	
	retVal = _SetField_PlacementInRegion(IDC_DIGRCPT,DLGSIZE_CX,DIGRCPT_Y,0,HEADER_RIGHT_MARGIN,
		0,0,DIGRCPT_X, DIGRCPT_Y,UITITLE_LEFT_MARGIN,i_nRegionY,
		RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,NULL);
	::ShowWindow(GetDlgItem(IDC_DIGRCPT), TRUE);
	
   return retVal;
}


HRESULT CDNZUI::_SetErrorBmp(int i_nRegionY, int i_nRegionHeight)
{
	HRESULT retVal;

	//Place the logo
	RECT rectDlgSize;

	GetClientRect(&rectDlgSize);
	
	retVal = _SetField_PlacementInRegion(IDC_ERROR,DLGSIZE_CX,ERROR_Y,0,HEADER_RIGHT_MARGIN,
		0,0,ERROR_X, i_nRegionHeight,UITITLE_LEFT_MARGIN,i_nRegionY,
		RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,NULL);
	::ShowWindow(GetDlgItem(IDC_ERROR), TRUE);
	
   return retVal;
}

#if 0
HRESULT CDNZUI::_SetRBSLogo(int i_nRegionY)
{
	HRESULT retVal;

	//Place the logo
	RECT rectDlgSize;

	GetClientRect(&rectDlgSize);
	
	retVal = _SetField_PlacementInRegion(IDC_RBS,DLGSIZE_CX,RBSLOGO_Y,0,HEADER_RIGHT_MARGIN,
		0,0,RBSLOGO_X, RBSLOGO_Y,DLGSIZE_CX,i_nRegionY,
		RGN_ANCH_TOPRIGHT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,NULL);
	::ShowWindow(GetDlgItem(IDC_RBS), TRUE);
	
   return retVal;
	
	
}
#endif


HRESULT CDNZUI::_SetSelectFileUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6); 
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	PALL_SELFILE_UIELEMENTS pAllSelFileUIElems = (PALL_SELFILE_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllSelFileUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllSelFileUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllSelFileUIElems->theDefUIElements.tbstrTitle);
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
	if(pAllSelFileUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllSelFileUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;
	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllSelFileUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
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
	//Create the filename label
	WCHAR* pwszOutBuff = NULL;
	_bstr_t tbstrTempString = "";

	//Set the profile name label
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_SELFILE_FILENAMELBL,&pwszOutBuff);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefTextFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL1,DLGSIZE_CX-UI_LEFT_MARGIN,
							(m_nDefTextFontSize),0,0,0,0,0,0,UITEXT_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
			}
		}
	}

	//Set the profile name edit box
	if(retVal == S_OK)
	{
		retVal = _SetField_FontAndText(IDC_EDIT1, m_hFontCustTextFont,pAllSelFileUIElems->tbstrSelectedFile, 
			0,SELFILE_FILENAME_EDIT_SIZE ,m_nCustTextFontSize + EDIT_TOPBTM_MARGINS);
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_EDIT1,DLGSIZE_CX-UI_LEFT_MARGIN-SELFILE_UILABEL_SPACE,
						EDIT_MAX_CY,0,0,0,0,0,0,UITEXT_LEFT_MARGIN+SELFILE_UILABEL_SPACE,nNextFieldY-2,
						RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			::ShowWindow(GetDlgItem(IDC_EDIT1),TRUE);
			

		}


		if(!pAllSelFileUIElems->tbstrSelectedFile.length() && !m_boolFocusSet)
		{
			SendDlgItemMessage(IDC_EDIT1, WM_ACTIVATE,WA_CLICKACTIVE);
			m_boolFocusSet = TRUE;
		}
	}

	if(pwszOutBuff)
	{
		free(pwszOutBuff);
		pwszOutBuff = NULL;
	}

	//Create the Browse Button
	if(retVal == S_OK)
	{
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_BROWSE,&pwszOutBuff);
		if(retVal == S_OK)
		{
			tbstrTempString = pwszOutBuff;
			//Set the text of the open profile label
			retVal = _SetField_FontAndText(IDBTN4,m_hFontDefBtnFont,tbstrTempString);
			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDBTN4,BTN_MAX_CX,BTN_MAX_CY,0,0,
					0,0,0,0,
					UITEXT_LEFT_MARGIN+SELFILE_UILABEL_SPACE+SELFILE_FILENAME_EDIT_SIZE+SELFILE_EDIT_SPACE,
					nNextFieldY-/*4*/2,RGN_ANCH_TOPLEFT,FLD_XANCH_RIGHT,FLD_YANCH_MIDDLE,
					NULL,&nThisFieldY);

				::ShowWindow(GetDlgItem(IDBTN4),TRUE);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);
			}
			

		}
	}

	m_nUISize = nNextFieldY;
	
	return retVal;
}

HRESULT CDNZUI::_SetProgressUI()
{
	HRESULT retVal = S_OK;

	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 4);
	int nThisFieldY;
	int nUITitleHeight;
	int nUITextHeight;

	
	PALL_PROGRESS_UIELEMENTS pAllProgressUIElems = (PALL_PROGRESS_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllProgressUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllProgressUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllProgressUIElems->theDefUIElements.tbstrTitle);
			nUITitleHeight = m_nDefUITitleFontSize;
		}

		//Place the ui title
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_UI_TITLE,UITITLE_MAX_X,
				nUITitleHeight,UITITLE_LEFT_MARGIN,UITITLE_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN*4);
			::ShowWindow(GetDlgItem(IDC_UI_TITLE),TRUE);
		}

	}

	//Set the text
	if(pAllProgressUIElems->theCustUIElements.tbstrText.length())
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
					pAllProgressUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);
		nUITextHeight = m_nCustTextFontSize;	

	}
	else
	{
		retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
					pAllProgressUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		nUITextHeight = m_nDefTextFontSize;
	}


	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,UITEXT_MAX_X,
				(nUITextHeight*10),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,(nUITextHeight*2),0,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
		nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	/*Creaete progress fields*/
 	if(pAllProgressUIElems->nCompletedPercent)
	{
		//retVal = SendDlgItemMessage(IDC_PROGRESS1,PBM_SETPOS,(WPARAM)pAllProgressUIElems->nCompletedPercent);
		SendDlgItemMessage(IDC_PROGRESS1,PBM_SETPOS,(WPARAM)pAllProgressUIElems->nCompletedPercent);
		
		nUITextHeight = m_nCustTextFontSize;

		//Place progress bar
		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_PROGRESS1,UIPROG_MAX_X ,
					(nUITextHeight*2),UIPROG_LEFT_MARGIN,UIPROG_RIGHT_MARGIN,0,0,0,0,0,nNextFieldY,
					RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 6);
			::ShowWindow(GetDlgItem(IDC_PROGRESS1),TRUE);
		}
		
	}

	m_nUISize = nNextFieldY;

	return retVal;
}

HRESULT CDNZUI::_SetVerifyRcptUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6);
	int nThisFieldY;
	int nUITitleHeight;

	m_hTextureBrush = CreateSolidBrush(RGB(255,255,255));
	if(!m_hTextureBrush)
		return E_FAIL;

	PALL_VERIFYRCPT_UIELEMENTS pAllVerifyRcptUIElems = (PALL_VERIFYRCPT_UIELEMENTS)m_pUICtxt->pvUIElements;
	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		//Set the text of the ui title
		if(pAllVerifyRcptUIElems->theCustUIElements.tbstrTitle.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontCustUITitleFont,
					pAllVerifyRcptUIElems->theCustUIElements.tbstrTitle);
			nUITitleHeight = m_nCustUITitleFontSize;

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TITLE, m_hFontDefUITitleFont,
					pAllVerifyRcptUIElems->theDefUIElements.tbstrTitle);
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

	if(retVal == S_OK)
	{
		retVal = _SetDigRcpt(nNextFieldY);
	}

	m_nReceiptDisplayPos = nNextFieldY;

	_ShowReceiptDetails();

	nNextFieldY += DIGRCPT_Y;

	m_nUISize = nNextFieldY;

	return retVal;
}


HRESULT CDNZUI::_SetErrorUI()
{
	HRESULT retVal = S_OK;
	int nNextFieldY = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 8); 
	int nThisFieldY;
	//int nUITitleHeight;
	int nUITextHeight;

	PALL_ERROR_UIELEMENTS pAllErrorUIElems = (PALL_ERROR_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	// Set the text
	retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
				pAllErrorUIElems->theUIElements.tbstrText,ERROR_TEXT_MAX_X );
	nUITextHeight = m_nDefTextFontSize;

	//Place the text
	if(retVal == S_OK)
	{
		retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,ERROR_TEXT_MAX_X ,
				(nUITextHeight*4),UITEXT_LEFT_MARGIN,UITEXT_RIGHT_MARGIN,0,0,0,(nUITextHeight*4),ERROR_TEXT_X,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_MIDDLE,NULL,&nThisFieldY);
		
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
	}

	// Set the placement for the error bitmap, it is rendered in OnPaint()
	_SetErrorBmp(nNextFieldY, (nUITextHeight*4));

	nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 8);
	m_nUISize = nNextFieldY;

	return retVal;
}


HRESULT CDNZUI::_ShowReceiptDetails()
{
	HRESULT retVal = S_OK;
	WCHAR* pwstrTemp = NULL;
	TCHAR* tstrTemp = NULL;
	_bstr_t tbstrTemp = "";
	int nNextFieldY = m_nReceiptDisplayPos + (HEADER_TOPBTM_MARGIN*4);
	int nThisFieldY, nIdString, nStaticId;

	PALL_VERIFYRCPT_UIELEMENTS pAllVerifyRcptUIElems = (PALL_VERIFYRCPT_UIELEMENTS)m_pUICtxt->pvUIElements;

	// Loading the receipt heading
	retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_TITLE, &pwstrTemp);
	if(retVal == S_OK)
	{
		tbstrTemp = pwstrTemp;

		retVal = _SetField_FontAndText(IDC_LABEL1, m_hFontDefWizTitleFont,tbstrTemp);

		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL1,UITITLE_MAX_X,
				m_nDefWizTitleFontSize+5,0,0,10,0,DIGRCPT_X,m_nDefWizTitleFontSize,UITITLE_LEFT_MARGIN,nNextFieldY,
				RGN_ANCH_TOPLEFT,FLD_XANCH_MIDDLE,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
			::ShowWindow(GetDlgItem(IDC_LABEL1),TRUE);
		}
		
		if(pwstrTemp)
		{
			free(pwstrTemp);
			pwstrTemp = NULL;
		}
	}

	if(retVal == S_OK)
	{
		// Loading the receipt description
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_DESC, &pwstrTemp);
		if(retVal == S_OK)
		{
			tbstrTemp = pwstrTemp;
			retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,tbstrTemp,DIGRCPT_X -35,0,0,0,0,m_nDefTextFontSize*2);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_UI_TEXT,DIGRCPT_X-30,
					m_nDefTextFontSize*2,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
					RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 4);
				::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
			}

			if(pwstrTemp)
			{
				free(pwstrTemp);
				pwstrTemp = NULL;
			}
		}
	}

	int nLabelWidth = 0;
	if(retVal == S_OK)
	{
		// Loading the 'for'
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_FOR, &pwstrTemp);
		if(retVal == S_OK)
		{
			tbstrTemp = pwstrTemp;			
					
			retVal = _SetField_FontAndText(IDC_LABEL2, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL2,DIGRCPT_X-30,
								m_nDefUITitleFontSize+5,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,&nLabelWidth,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL2),TRUE);
			}
		
			if(pwstrTemp)
			{
				free(pwstrTemp);
				pwstrTemp = NULL;
			}
		}
	}

	if(retVal == S_OK)
	{
		// Loading the value corresponding to 'for'
		tbstrTemp = pAllVerifyRcptUIElems->tbstrWhoNotarized;
		
		
		retVal = _SetField_FontAndText(IDC_LABEL2_1, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X-35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize);

		if(retVal == S_OK)
		{
			retVal = _SetField_PlacementInRegion(IDC_LABEL2_1,DIGRCPT_X-30-nLabelWidth,
							m_nDefUITitleFontSize,20+nLabelWidth,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
			::ShowWindow(GetDlgItem(IDC_LABEL2_1),TRUE);
		}
	
		
	}

	if(retVal == S_OK)
	{
		// Loading the 'document'
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_DOC, &pwstrTemp);
		if(retVal == S_OK)
		{
			tbstrTemp = pwstrTemp;
			
			retVal = _SetField_FontAndText(IDC_LABEL3, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL3,DIGRCPT_X-30,
								m_nDefUITitleFontSize+5,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL3),TRUE);
			}
		
			if(pwstrTemp)
			{
				free(pwstrTemp);
				pwstrTemp = NULL;
			}
		}
	}

	
	if(retVal == S_OK)
	{

		
		// Loading the 'document' value
		tbstrTemp = pAllVerifyRcptUIElems->tbstrNotarizedDocumentTitle;

		m_ViewLink.SetDocumentTitle(pAllVerifyRcptUIElems->tbstrNotarizedDocumentTitle);
		m_ViewLink.SetDocument(pAllVerifyRcptUIElems->tbstrNotarizedDocument);
		m_ViewLink.SetUserAgent(pAllVerifyRcptUIElems->tbstrUserAgent);
		
		// If the record data is NULL the link to Save Document and Receipt will not be shown on the UI.
		// So set this flag to tell the ViewLink object to display the correct view document error-message.
		if ((pAllVerifyRcptUIElems->pbRecordData == NULL) 
			|| (pAllVerifyRcptUIElems->dwRecordDataLen == 0))
		{
			m_ViewLink.SetSaveLinkPresent(false);
		}
		else
		{
			m_ViewLink.SetSaveLinkPresent(true);
		}

		char *pcszDoc = pAllVerifyRcptUIElems->tbstrNotarizedDocument;

		if ((_tcslen(pcszDoc) > 5) &&
			((_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".txt") == 0)
			|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".doc") == 0)
			|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".htm") == 0)
			|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 5], ".html") == 0)
			|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".xls") == 0)
			|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".pdf") == 0)))
		{

	//		retVal = _SetField_FontAndText(IDC_LABEL3_3, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize*2);
			retVal = _SetField_FontAndText(IDC_LABEL3_3, m_hFontDefUndTextFont,tbstrTemp,DIGRCPT_X -35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize*2);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL3_3,DIGRCPT_X-30-nLabelWidth,
								m_nDefUITitleFontSize*2,20+nLabelWidth,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
				::ShowWindow(GetDlgItem(IDC_LABEL3_3),TRUE);
			}
		}
		else
		{
			retVal = _SetField_FontAndText(IDC_LABEL3_4, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize*2);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL3_4,DIGRCPT_X-30-nLabelWidth,
								m_nDefUITitleFontSize*2,20+nLabelWidth,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
				::ShowWindow(GetDlgItem(IDC_LABEL3_4),TRUE);
			}
		}
	}

	if(retVal == S_OK)
	{
		// Loading the 'date'
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_DATE, &pwstrTemp);
		if(retVal == S_OK)
		{
			tbstrTemp = pwstrTemp;
			
			
			retVal = _SetField_FontAndText(IDC_LABEL4, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4,DIGRCPT_X-30,
								m_nDefUITitleFontSize+5,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL4),TRUE);
			}
		
		
			if(pwstrTemp)
			{
				free(pwstrTemp);
				pwstrTemp = NULL;
			}
		}
	}


	if(retVal == S_OK)
	{
		// Loading the 'date' value
		
			tbstrTemp = pAllVerifyRcptUIElems->tbstrDateCreated;
							
			retVal = _SetField_FontAndText(IDC_LABEL4_1, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL4_1,DIGRCPT_X-30-nLabelWidth,
								m_nDefUITitleFontSize,20+nLabelWidth,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
				::ShowWindow(GetDlgItem(IDC_LABEL4_1),TRUE);
			}
			
	}

	if(retVal == S_OK)
	{
		// Loading the 'time'
		retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,IDS_RECEIPT_TIME, &pwstrTemp);
		if(retVal == S_OK)
		{
			tbstrTemp = pwstrTemp;
			
			retVal = _SetField_FontAndText(IDC_LABEL5, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL5,DIGRCPT_X-30,
								m_nDefUITitleFontSize+5,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				::ShowWindow(GetDlgItem(IDC_LABEL5),TRUE);
			}
		
			FREE_MEMORY(pwstrTemp)
		}
	}

	if(retVal == S_OK)
	{
		// Loading the 'time' value
		
			tbstrTemp = pAllVerifyRcptUIElems->tbstrTimeCreated;
			
			retVal = _SetField_FontAndText(IDC_LABEL5_1, m_hFontDefUITitleFont,tbstrTemp,DIGRCPT_X -35-nLabelWidth,0,0,0,0,m_nDefUITitleFontSize);

			if(retVal == S_OK)
			{
				retVal = _SetField_PlacementInRegion(IDC_LABEL5_1,DIGRCPT_X-30,
								m_nDefUITitleFontSize,20+nLabelWidth,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
				nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 5);
				::ShowWindow(GetDlgItem(IDC_LABEL5_1),TRUE);
			}
		
	
	}

	if(retVal == S_OK)
	{
		if(pAllVerifyRcptUIElems->nRcptVerificationResult == VERIFY_CORRECT && pAllVerifyRcptUIElems->nDocumentIntegrityResult == INTEGRITY_CORRECT)
		{
			// Show the valid or invalid bitmaps			
			retVal = _SetField_PlacementInRegion(IDC_VALIDBMP,DIGRCPT_X,
							DIGRCPT_Y,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
			::ShowWindow(GetDlgItem(IDC_VALIDBMP),TRUE);

			retVal = _SetField_PlacementInRegion(IDC_VALIDRBS,DIGRCPT_X,
							DIGRCPT_Y,0,0,0,0,0,0,UITITLE_LEFT_MARGIN+DIGRCPT_X-100,m_nReceiptDisplayPos+DIGRCPT_Y - 100,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,NULL);
			::ShowWindow(GetDlgItem(IDC_VALIDRBS),TRUE);
		}
		else
		{
			retVal = _SetField_PlacementInRegion(IDC_INVALIDBMP,DIGRCPT_X,
							DIGRCPT_Y,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY-HEADER_TOPBTM_MARGIN,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
			nNextFieldY += nThisFieldY - HEADER_TOPBTM_MARGIN;
			::ShowWindow(GetDlgItem(IDC_INVALIDBMP),TRUE);

		/*	retVal = _SetField_PlacementInRegion(IDC_INVALIDRBS,DIGRCPT_X,
							DIGRCPT_Y,0,0,0,0,0,0,UITITLE_LEFT_MARGIN+DIGRCPT_X-100,m_nReceiptDisplayPos+DIGRCPT_Y - 100,
							RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,NULL);
			::ShowWindow(GetDlgItem(IDC_INVALIDRBS),TRUE);*/
		}
	}

	if(retVal == S_OK)
	{
		// Load the 'details' string or the error string depending on the receipt verification and
		// document integrity status
		if(pAllVerifyRcptUIElems->nRcptVerificationResult == VERIFY_CORRECT && pAllVerifyRcptUIElems->nDocumentIntegrityResult == INTEGRITY_CORRECT)
		{
			nStaticId = IDC_LABEL7;
			nIdString = IDS_RECEIPT_SAVE;

			m_SaveLink.SetDocumentTitle(pAllVerifyRcptUIElems->tbstrNotarizedDocumentTitle);
			m_SaveLink.SetDocument(pAllVerifyRcptUIElems->tbstrNotarizedDocument);
			m_SaveLink.SetRecordData(pAllVerifyRcptUIElems->pbRecordData);
			m_SaveLink.SetRecordDataLen(pAllVerifyRcptUIElems->dwRecordDataLen);
			m_SaveLink.SetUserAgent(pAllVerifyRcptUIElems->tbstrUserAgent);

			// If the record data is NULL don't show the link to Save Document and Receipt, the record data will
			// be NULL when the user does not pass in the UIFLAG_SAVE_DOC flag while doing verification or if
			// there is some error in reading the record.
			if ((pAllVerifyRcptUIElems->pbRecordData == NULL) 
				|| (pAllVerifyRcptUIElems->dwRecordDataLen == 0))
				nIdString = -1;	
		}
		else
		{
			nStaticId = IDC_LABEL6;

			if(pAllVerifyRcptUIElems->nRcptVerificationResult == VERIFY_INCORRECT)
				nIdString = IDS_RECEIPT_VERIFY_ERR;
			else
				nIdString = IDS_RECEIPT_INTEGRITY_ERR;

			m_HyperLink.SetLinkText("");
		}

		if(nIdString != -1)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nIdString, &pwstrTemp);
			if(retVal == S_OK)
			{
				tbstrTemp = pwstrTemp;

				if(nIdString == IDS_RECEIPT_SAVE)
					retVal = _SetField_FontAndText(nStaticId, m_hFontDefUndTextFont,tbstrTemp,DIGRCPT_X -35);

				else
					retVal = _SetField_FontAndText(nStaticId, m_hFontDefTextFont,tbstrTemp,DIGRCPT_X -120,0,0,0,0,m_nDefTextFontSize*2);

				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(nStaticId,DIGRCPT_X-30,
								m_nDefTextFontSize*2,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
								RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
					::ShowWindow(GetDlgItem(nStaticId),TRUE);
				}

				FREE_MEMORY(pwstrTemp)
			}
		}

	}       // if(retVal == S_OK)


	if(retVal == S_OK)
	{

		if(pAllVerifyRcptUIElems->nRcptVerificationResult == VERIFY_CORRECT && pAllVerifyRcptUIElems->nDocumentIntegrityResult == INTEGRITY_CORRECT)
		{
			nStaticId = IDC_LABEL8;
			nIdString = IDS_RECEIPT_DETAILS;

			m_HyperLink.SetLinkText(pAllVerifyRcptUIElems->tbstrTmpHtmlFile);

			// If the html file is NULL don't show the link to the Web Service, the html file will
			// NULL when the user does not pass in the UIFLAG_WEB_LINK flag while doing verification or if
			// there is some error in constructing the html file
			if(pAllVerifyRcptUIElems->tbstrTmpHtmlFile == _bstr_t(""))
				nIdString = -1;	

		}
		else
		{
			nIdString = -1;
		}

		if(nIdString != -1)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nIdString, &pwstrTemp);
			if(retVal == S_OK)
			{
				tbstrTemp = pwstrTemp;
	
				retVal = _SetField_FontAndText(nStaticId, m_hFontDefUndTextFont,tbstrTemp,DIGRCPT_X -35);

				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(nStaticId,DIGRCPT_X-30,
									m_nDefTextFontSize*2,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
									RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
					::ShowWindow(GetDlgItem(nStaticId),TRUE);
				}

				FREE_MEMORY(pwstrTemp)
			}
		}

	}	// if(retVal == S_OK)

/*	if(retVal == S_OK)
	{
		nStaticId = IDC_LABEL9;
		nIdString = IDS_RECEIPT_VIEW;

		m_ViewLink.SetDocumentTitle(pAllVerifyRcptUIElems->tbstrNotarizedDocumentTitle);
		m_ViewLink.SetDocument(pAllVerifyRcptUIElems->tbstrNotarizedDocument);
		m_ViewLink.SetUserAgent(pAllVerifyRcptUIElems->tbstrUserAgent);

		// If the show view document flag is FALSE don't show the link to View Document
		if (pAllVerifyRcptUIElems->boolShowViewDocumentLink == FALSE)
			nIdString = -1;	

		if(nIdString != -1)
		{
			retVal = _LoadStringW(_Module.m_hInst,m_pUICtxt->nDefLangId,nIdString, &pwstrTemp);
			if(retVal == S_OK)
			{
				tbstrTemp = pwstrTemp;
	
				retVal = _SetField_FontAndText(nStaticId, m_hFontDefUndTextFont,tbstrTemp,DIGRCPT_X -35);

				if(retVal == S_OK)
				{
					retVal = _SetField_PlacementInRegion(nStaticId,DIGRCPT_X-30,
									m_nDefTextFontSize*2,20,0,0,0,0,0,UITITLE_LEFT_MARGIN,nNextFieldY,
									RGN_ANCH_TOPLEFT,FLD_XANCH_LEFT,FLD_YANCH_TOP,NULL,&nThisFieldY);
					nNextFieldY += nThisFieldY + (HEADER_TOPBTM_MARGIN * 2);
					::ShowWindow(GetDlgItem(nStaticId),TRUE);
				}

				FREE_MEMORY(pwstrTemp)
			}
		}

	}	// if(retVal == S_OK)
*/
	return retVal;
}


LRESULT CDNZUI::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	HRESULT retVal = S_OK;	
	PAINTSTRUCT paintStruct;
	RECT rect;

	PALL_VERIFYRCPT_UIELEMENTS pAllVerifyRcptUIElems = (PALL_VERIFYRCPT_UIELEMENTS)m_pUICtxt->pvUIElements;

	if(m_pUICtxt->nWhichWizardAndUI & VERIFYRCPT_BASE)
	{
		rect.left = UITITLE_LEFT_MARGIN;
		rect.top = m_nReceiptDisplayPos;
		rect.right = DIGRCPT_X ;
		rect.bottom = DIGRCPT_Y;

		InvalidateRect(&rect, FALSE);

		HDC hDc = BeginPaint(&paintStruct);

		_DisplayLogo(IDC_DIGRCPT, IDB_DIGRCPT);

		_ShowReceiptDetails();

		if(pAllVerifyRcptUIElems->nRcptVerificationResult == VERIFY_CORRECT && pAllVerifyRcptUIElems->nDocumentIntegrityResult == INTEGRITY_CORRECT)
			_DisplayLogo(IDC_VALIDRBS, IDB_VALIDRBS);
		/*else
			_DisplayLogo(IDC_INVALIDRBS, IDB_INVALIDRBS);*/

		EndPaint(&paintStruct);
	}
	else 
		if(m_pUICtxt->nWhichWizardAndUI & ERROR_BASE)
		{
			rect.left = UITITLE_LEFT_MARGIN;
			rect.top = m_nHeaderSize + (HEADER_TOPBTM_MARGIN * 6);;
			rect.right = ERROR_X ;
			rect.bottom = ERROR_Y;

			InvalidateRect(&rect, FALSE);

			HDC hDc = BeginPaint(&paintStruct);

			_DisplayLogo(IDC_ERROR, IDB_ERROR);

			EndPaint(&paintStruct);
		}
		else
			bHandled = FALSE;

	//Set the verisign logo
	_DisplayLogo(IDC_VRSN_LOGO, IDB_VSLARGE);

	return 0;
}


LRESULT CDNZUI::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT retVal = 0;

	if(m_pUICtxt->nWhichWizardAndUI & VERIFYRCPT_BASE)
	{
		DWORD dwCtrlID;
		dwCtrlID = ::GetDlgCtrlID((HWND)lParam);
		switch(dwCtrlID)
		{
			case IDC_UI_TEXT :
			case IDC_LABEL1 :
			case IDC_LABEL2 :
			case IDC_LABEL2_1:
			case IDC_LABEL3 :
//			case IDC_LABEL3_3:
			case IDC_LABEL3_4:
			case IDC_LABEL4 :
			case IDC_LABEL4_1:
			case IDC_LABEL5 :
			case IDC_LABEL5_1:
			case IDC_LABEL6 :
			{
				SetBkMode((HDC)wParam,TRANSPARENT);
				retVal = (LRESULT)m_hTextureBrush;
				break;
			}
		}

		if ((dwCtrlID == IDC_LABEL7) || (dwCtrlID == IDC_LABEL8) || (dwCtrlID == IDC_LABEL3_3))
			bHandled = FALSE;
	}
	
	return retVal;
}



LRESULT CDNZUI::OnBtn1(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
		if(m_bModeless)
			DestroyWindow();
		else
			EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
		
}

LRESULT CDNZUI::OnBtn2(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
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
		if(m_bModeless)
			DestroyWindow();
		else
			EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}

LRESULT CDNZUI::OnBtn3(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Store parameters
	retVal = _StoreParams();

	//Change cursor pointer
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	//Call the handler function
	if(retVal == S_OK)
		retVal = m_pUICtxt->pbtnFns->lpfnBtn3Fn(m_pOpCtxt);
	
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
		//End Dialog
		if(m_bModeless)
			DestroyWindow();
		else
			EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}


LRESULT CDNZUI::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Store parameters
	retVal = _StoreParams();

	//Change cursor pointer
	HCURSOR hCursor = LoadCursor(NULL, IDC_WAIT);
	if(hCursor)
		SetCursor(hCursor);

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
		//End Dialog
		if(m_bModeless)
			DestroyWindow();
		else
			EndDialog((retVal2==S_OK?retVal:retVal2));
	}

	return retVal;
}

LRESULT CDNZUI::OnBtn4(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	HRESULT retVal = S_OK;
	HRESULT retVal2 = S_OK;
	int nCurrOperation;

	//Save the current operation
	nCurrOperation = m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS | FLAG_BITS);

	if(nCurrOperation == SELFILE_BASE)
	{
		retVal = _DoBrowse();
	}
	else if(nCurrOperation == PROGRESS_BASE)
	{
		PALL_PROGRESS_UIELEMENTS pAllProgressUIElems = (PALL_PROGRESS_UIELEMENTS)(m_pUICtxt->pvUIElements);
		
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),FALSE);
		//Set the text
		if(pAllProgressUIElems->theCustUIElements.tbstrText.length())
		{
			retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontCustTextFont,
						pAllProgressUIElems->theCustUIElements.tbstrText, UITEXT_MAX_X);

		}
		else
		{
			retVal = _SetField_FontAndText(IDC_UI_TEXT, m_hFontDefTextFont,
						pAllProgressUIElems->theDefUIElements.tbstrText,UITEXT_MAX_X);
		}
		::ShowWindow(GetDlgItem(IDC_UI_TEXT),TRUE);
		SendDlgItemMessage(IDC_UI_TEXT,WM_PAINT);

		SendDlgItemMessage(IDC_PROGRESS1,PBM_SETPOS,(WPARAM)((PALL_PROGRESS_UIELEMENTS)(m_pUICtxt->pvUIElements))->nCompletedPercent);
	}

	return retVal;
}

HRESULT CDNZUI::_StoreParams()
{
	HRESULT retVal = S_OK;

	//Depending upon the ui type, store the parameters
	switch((m_pUICtxt->nWhichWizardAndUI & (OPERATION_BITS|FLAG_BITS)))
	{
		case SELFILE_BASE :
			retVal = _StoreSelectFileParams();
			break;

		case PROGRESS_BASE :
			retVal = _StoreProgressParams();
			break;

		case VERIFYRCPT_BASE :
			retVal = _StoreVerifyRcptParams();
			break;

		case ERROR_BASE :
			break;

		default :
			retVal =  E_INVALIDFLAGS;
	}
	return retVal;
}

HRESULT CDNZUI::_DoTearDown(int i_nCurrOperation)
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
		switch(i_nCurrOperation)
		{
		case SELFILE_BASE :
			retVal = _TeardownSelectFileUI();
			break;

		case PROGRESS_BASE :
			retVal = _TeardownProgressUI();
			break;

		case VERIFYRCPT_BASE :
			retVal = _TeardownVerifyRcptUI();
			break;

		case ERROR_BASE :
			retVal = _TeardownErrorUI();
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

HRESULT CDNZUI::_StoreSelectFileParams()
{
	HRESULT retVal = S_OK;
	PALL_SELFILE_UIELEMENTS pAllSelFileUIElems;

	pAllSelFileUIElems = (PALL_SELFILE_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	/*Obtain and store the input params*/
	retVal = _GetDlgItemText(IDC_EDIT1,&(pAllSelFileUIElems->tbstrSelectedFile));
	
	return retVal;
}

HRESULT CDNZUI::_StoreProgressParams()
{
	HRESULT retVal = S_OK;
	PALL_PROGRESS_UIELEMENTS pAllProgressUIElems;

	pAllProgressUIElems = (PALL_PROGRESS_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	/*Obtain and store the input params*/
	//TODO
	
	return retVal;
}

HRESULT CDNZUI:: _StoreVerifyRcptParams()
{
	HRESULT retVal = S_OK;
	PALL_VERIFYRCPT_UIELEMENTS pAllVerifyRcptUIElems;

	pAllVerifyRcptUIElems = (PALL_VERIFYRCPT_UIELEMENTS)m_pUICtxt->pvUIElements;
	
	
	return retVal;
}


HRESULT CDNZUI::_TeardownSeparator()
{
	m_nCYSet = 0;
	return S_OK;
}

HRESULT CDNZUI::_TeardownSelectFileUI()
{
	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	//Make all the widgets in this UI invisible
	::ShowWindow(GetDlgItem(IDBTN4), FALSE);
	::ShowWindow(GetDlgItem(IDC_EDIT1), FALSE);
	::ShowWindow(GetDlgItem(IDC_LABEL1), FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT), FALSE);

	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to hide the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}

HRESULT CDNZUI::_TeardownProgressUI()
{

	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	//Make all the widgets in this UI invisible
	::ShowWindow(GetDlgItem(IDC_PROGRESS1), FALSE);
	::ShowWindow(GetDlgItem(IDC_UI_TEXT), FALSE);

	

	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	return retVal;
}


HRESULT CDNZUI::_TeardownErrorUI()
{

	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	//Make all the widgets in this UI invisible
	::ShowWindow(GetDlgItem(IDC_UI_TEXT), FALSE);
	::ShowWindow(GetDlgItem(IDC_ERROR), FALSE);

	return retVal;
}

HRESULT CDNZUI::_TeardownVerifyRcptUI()
{

	HRESULT retVal = S_OK;

	//Set the ui size to 0
	m_nUISize = 0;
	
	
	//Make all the widgets in this UI invisible
	//TODO

	if(m_nCurrWiz>0) //This is a wizard based ui, so we need to show the ui title
	{
		::ShowWindow(GetDlgItem(IDC_UI_TITLE),FALSE);
	}

	if(m_hTextureBrush)
	{
		DeleteObject(m_hTextureBrush);
		m_hTextureBrush = NULL;
	}

	return retVal;
}


HRESULT CDNZUI::_TeardownHeader()
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

HRESULT CDNZUI::_TeardownFonts()
{
	HRESULT retVal = S_OK;
	
	//Delete all the fonts
	DeleteObject((HFONT)m_hFontDefWizTitleFont);
	m_hFontDefWizTitleFont = NULL;

	DeleteObject((HFONT)m_hFontDefUITitleFont);
	m_hFontDefUITitleFont = NULL;

	DeleteObject((HFONT)m_hFontDefTextFont);
	m_hFontDefTextFont = NULL;
	
	DeleteObject((HFONT)m_hFontDefUndTextFont);
	m_hFontDefUndTextFont= NULL;
	

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


	m_boolFontsSet = FALSE;
	return retVal;
}


HRESULT CDNZUI::_TeardownVRSNLogo()
{
	::ShowWindow(GetDlgItem(IDC_VRSN_LOGO), FALSE);
	
	return S_OK;
}

HRESULT CDNZUI::put_NextMessageToShow(VARIANT* i_pvarMsgToShow)
{
	HRESULT retVal = S_OK;

	m_tbstrMsgToShow = i_pvarMsgToShow->bstrVal;

	return retVal;
}

HRESULT CDNZUI::_DisplayLogo(int i_nContainer, int i_nBitmap)
{
	HDC hdc = ::GetDC(GetDlgItem(i_nContainer));
	//HDC hdc = GetDC();

	//PAINTSTRUCT paintStruct;

	RECT rectDlgSize;

	GetClientRect(&rectDlgSize);
	
	HBITMAP hBitmap;
	BITMAP     bm;   
	COLORREF   cColor;
	HBITMAP    bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP    bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC        hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;   
	POINT      ptSize;

	hBitmap = LoadBitmap(_Module.m_hInst, MAKEINTRESOURCE(i_nBitmap));

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
	//cColor = SetBkColor(hdcTemp, RGB(0, 128, 0));
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

   return 0;

}


HRESULT CDNZUI::_DoBrowse()
{
	HRESULT hr = S_OK;
	_bstr_t tbstrOpenFile = "";

	hr = _SelectOpenOrSaveFile(SELECT_OPEN, GetFocus(), IDS_FILEOPEN, NULL, 0, _bstr_t(""), &tbstrOpenFile);

	if(hr == S_OK)
		::SetWindowText(GetDlgItem(IDC_EDIT1),tbstrOpenFile);

	return hr;
}


HRESULT CDNZUI::_GetDlgItemText(int i_nDlgItemId, _bstr_t* o_ptbstrDlgItemText)
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
				memset(bstrDlgItemText, 0, (*o_ptbstrDlgItemText).length()*2);
				//EraseMemory((unsigned int)(*o_ptbstrDlgItemText).length()*2, (unsigned char*)bstrDlgItemText);
				
			}

			SysFreeString(bstrDlgItemText);
		}
	}
	return retVal;
}

