#include "stdafx.h"
#include <comutil.h>
#include "ptav3.h"
#include "notarize.h"
#include "DNZUI.h"
#include "nzerrs.h"
#include "nzutils.h"
#include "nzdefines.h"
#include "ptaerrs.h"
#include "nzmacros.h"
#include "nzdatacc.h"
#include "shlink.h"


	
CHLink::CHLink()
{
		m_colorUnvisited = RGB(0,0,255); 
		m_colorVisited = RGB(128,0,128);
		m_colorVisiting = RGB(255, 0, 0);
		m_bVisited = FALSE;
		m_bVisiting = FALSE;
		m_hFont = NULL;
		m_hLinkCursor = NULL;                 // No cursor as yet
		m_bstrLink = "";
		m_tbstrDocumentTitle = "";
		m_tbstrDocument = "";
		m_tbstrUserAgent = "";
		m_pbRecordData = NULL;
		m_dwRecordDataLen = 0;
		m_boolSaveLinkPresent = false;

		TCHAR szWinDir[MAX_PATH];
		GetWindowsDirectory(szWinDir, MAX_PATH);

		lstrcat(szWinDir, "\\winhlp32.exe");
		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = LoadLibrary(szWinDir);
		if(hModule) 
		{
			HCURSOR hHandCursor = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			if(hHandCursor)
				m_hLinkCursor = CopyCursor(hHandCursor);

			FreeLibrary(hModule);
		}
}

void CHLink::SetLinkText(LPCTSTR szLink) 
{      
		m_bstrLink = szLink;   
}

void CHLink::SetDocumentTitle(_bstr_t i_tbstrDocumentTitle)
{
		m_tbstrDocumentTitle = i_tbstrDocumentTitle;
}

void CHLink::SetDocument(_bstr_t i_tbstrDocument)
{
		m_tbstrDocument = i_tbstrDocument;
}

void CHLink::SetUserAgent(_bstr_t i_tbstrUserAgent)
{
		m_tbstrUserAgent = i_tbstrUserAgent;
}

void CHLink::SetRecordData(BYTE* i_pbRecordData)
{
		m_pbRecordData = i_pbRecordData;
}

void CHLink::SetRecordDataLen(DWORD i_dwRecordDataLen)
{
		m_dwRecordDataLen = i_dwRecordDataLen;
}

void CHLink::SetSaveLinkPresent(bool i_boolSaveLinkPresent)
{
		m_boolSaveLinkPresent = i_boolSaveLinkPresent;
}

LRESULT CHLink::OnDestroy(UINT, WPARAM, LPARAM, BOOL&)
{
      if(m_hFont) 
		  DeleteObject( m_hFont );      

	  return 0;   
}

LRESULT CHLink::OnMouseMove(UINT, WPARAM wParam, LPARAM, BOOL&)
{
		m_bVisiting = TRUE;
		::SetCursor(m_hLinkCursor);
		Invalidate();

		return 0;
}

LRESULT CHLink::OnCommand(UINT, WPARAM wParam, LPARAM, BOOL&) 
{
		int code = HIWORD(wParam);
		if(code == STN_CLICKED || code == STN_DBLCLK)
		{
			if(m_bstrLink != _bstr_t(""))
			{
				 if((int)ShellExecute(*this, _T("open"), m_bstrLink, NULL, NULL, SW_SHOWNORMAL) > 32)
				 {
					m_bVisited = TRUE;   // return codes > 32 => success
					Invalidate();         
				 }
			}
			else if ((m_pbRecordData != NULL) && (m_dwRecordDataLen > 0) 
					&& (m_tbstrDocument != _bstr_t("")))
			{
				if (_SaveReceiptAndDocument() == S_OK)
				{
					m_bVisited = TRUE;
					Invalidate();
				}
			}
			else if (m_tbstrDocument != _bstr_t(""))
			{
				if (_ViewOriginalDocument() == S_OK)
				{
					m_bVisited = TRUE;
					Invalidate();
				}
			}
		}      
		
		return 0;   
}

LRESULT CHLink::OnCtlColor(UINT, WPARAM wParam, LPARAM, BOOL&) 
{
		HBRUSH hBr = NULL;

		if(!m_hFont)
		{            
			LOGFONT lf;
            GetObject(GetFont(), sizeof(lf), &lf);
            lf.lfUnderline = TRUE;
            m_hFont = CreateFontIndirect( &lf );         
		}
        
		HDC hDC = (HDC)wParam;         
		SelectObject(hDC, m_hFont);

		if(m_bVisiting)
		{
			SetTextColor( hDC, m_colorVisiting);
			m_bVisiting = FALSE;
		}
		else
			SetTextColor(hDC, m_bVisited ? m_colorVisited : m_colorUnvisited);
		
        SetBkMode(hDC, TRANSPARENT);
        hBr = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

		return (LRESULT)hBr;   
}
	
HRESULT CHLink::_SaveReceiptAndDocument()
{
		HRESULT hr = S_OK;

		CDataAccess DAccObject, DAWriteDocObject, DAWriteRecObject;
		BYTE pbReadBuffer[MAX_READ_SIZE];
		DWORD dwReadBuffer = 0, dwBytesRead = 0;
		_bstr_t tbstrDestinationDirectory = "";
		_bstr_t tbstrDocumentDestination = "";
		_bstr_t tbstrReceiptDestination = "";

		WCHAR *pwstrTemp1 = NULL;
		WCHAR *pwstrTemp2 = NULL;
		WCHAR *pwstrTemp3 = NULL;

		bool boolSrcAndDestAreSame = false;

		do
		{
			_bstr_t tbstrExtension = _bstr_t("");
			_bstr_t tbstrDocumentDestination = _bstr_t("");
			char *pcszExtension;
			char *pcszFilter = NULL;
			int dwFilterLength = 0;

			hr = _GetDocumentExtension(m_tbstrDocument, &tbstrExtension);
			CHECK_HRESULT_BREAK

			if (tbstrExtension != _bstr_t(""))
			{
				pcszExtension = (char *) tbstrExtension;
				dwFilterLength = lstrlen(pcszExtension) * 2 + 3;
				pcszFilter = (char *)malloc (dwFilterLength * sizeof(char));
				memset(pcszFilter, 0, dwFilterLength);

				memcpy(pcszFilter, (void *)"(", 1);
				memcpy(pcszFilter + 1, pcszExtension, lstrlen(pcszExtension));
				memcpy(pcszFilter + 1 + lstrlen(pcszExtension), ")", 1);
				memcpy(pcszFilter + 1 + lstrlen(pcszExtension) + 2, pcszExtension, lstrlen(pcszExtension));
			}

			hr = _SelectOpenOrSaveFile(SELECT_SAVE, GetFocus(), IDS_SAVE_DOC, pcszFilter, dwFilterLength, m_tbstrDocumentTitle, &tbstrDocumentDestination);
			CHECK_HRESULT_BREAK

			// Are the source document and the saving destination locations the same.
			boolSrcAndDestAreSame = _IsSourceAndDestinationSame(m_tbstrDocument, tbstrDocumentDestination);

			if (!boolSrcAndDestAreSame)
			{
				hr = DAWriteDocObject.Open(tbstrDocumentDestination, ACCESS_OVERWRITE);
				CHECK_HRESULT_BREAK
	
				// Get the record
				hr = DAccObject.Open(m_tbstrDocument, ACCESS_READ, m_tbstrUserAgent);
				CHECK_HRESULT_BREAK

				do
				{
					dwReadBuffer = sizeof(pbReadBuffer);
					hr = DAccObject.Read(pbReadBuffer, &dwReadBuffer);
					CHECK_HRESULT_BREAK

					if(dwReadBuffer == 0)
						break;
	
					hr = DAWriteDocObject.Write(pbReadBuffer, dwReadBuffer);
					CHECK_HRESULT_BREAK
	
					dwBytesRead += dwReadBuffer;
	
				} while (dwReadBuffer != 0);
				
				CHECK_HRESULT_BREAK
			}

			tbstrReceiptDestination = tbstrDocumentDestination + _bstr_t(".rcpt");

			hr = DAWriteRecObject.Open(tbstrReceiptDestination, ACCESS_OVERWRITE);
			CHECK_HRESULT_BREAK
	
			hr = DAWriteRecObject.Write(m_pbRecordData, m_dwRecordDataLen);
			CHECK_HRESULT_BREAK

			hr = _LoadStringW(_Module.m_hInst,_GetDefaultLangID(), IDS_DOCSAVED_MESG, &pwstrTemp1);
			CHECK_HRESULT_BREAK

			hr = _LoadStringW(_Module.m_hInst,_GetDefaultLangID(), IDS_RCPTSAVED_MESG, &pwstrTemp2);
			CHECK_HRESULT_BREAK

			hr = _LoadStringW(_Module.m_hInst,_GetDefaultLangID(), IDS_SAVEDMESG_TITLE, &pwstrTemp3);
			CHECK_HRESULT_BREAK

			_bstr_t tbstrTemp1 = pwstrTemp1;
			_bstr_t tbstrTemp2 = pwstrTemp2;
			_bstr_t tbstrTemp3 = pwstrTemp3;

			_bstr_t tbstrMessage = _bstr_t(tbstrTemp1) + tbstrDocumentDestination + _bstr_t("\n") +
								   _bstr_t(tbstrTemp2) + tbstrReceiptDestination;

			_bstr_t tbstrTitle = _bstr_t(tbstrTemp3);
	
			::MessageBox(GetFocus(), tbstrMessage, tbstrTitle, MB_OK);

			
		} while (0);

		if (!boolSrcAndDestAreSame)
		{
			DAccObject.Close();
			DAWriteDocObject.Close();
		}
		DAWriteRecObject.Close();

		FREE_MEMORY(pwstrTemp1)
		FREE_MEMORY(pwstrTemp2)
		FREE_MEMORY(pwstrTemp3)

		return hr;
}

HRESULT CHLink::_ViewOriginalDocument()
{
		HRESULT hr = S_OK;

/*
		CDataAccess DAccObject, DAWriteDocObject;
		BYTE pbReadBuffer[MAX_READ_SIZE];
		DWORD dwReadBuffer = 0, dwBytesRead = 0;
		_bstr_t bstrTempFile = "";
*/

		do
		{

/*
			// Create the file in which the document will be written
			hr = _CreateTempFile(&bstrTempFile);
			CHECK_HRESULT_BREAK

			hr = DAWriteDocObject.Open(bstrTempFile, ACCESS_OVERWRITE);
			CHECK_HRESULT_BREAK

			// Get the record
			hr = DAccObject.Open(m_tbstrDocument, ACCESS_READ, m_tbstrUserAgent);
			CHECK_HRESULT_BREAK

			do
			{
				dwReadBuffer = sizeof(pbReadBuffer);
				hr = DAccObject.Read(pbReadBuffer, &dwReadBuffer);
				CHECK_HRESULT_BREAK

				if(dwReadBuffer == 0)
					break;

				hr = DAWriteDocObject.Write(pbReadBuffer, dwReadBuffer);
				CHECK_HRESULT_BREAK

				dwBytesRead += dwReadBuffer;

			} while (dwReadBuffer != 0);
			
			CHECK_HRESULT_BREAK

			DAccObject.Close();
			DAWriteDocObject.Close();

*/
			char *pcszDoc = m_tbstrDocument;
/*
			char *pcszDoc = m_tbstrDocument;
			if (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".exe") == 0)
			{
				WCHAR *pwcErrorString = NULL;
				_bstr_t tbstrErrorString;
*/
				/*
				WCHAR *pwcErrorTitle = NULL;
				_bstr_t tbstrErrorTitle;

				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VIEW_EXE_ERR, &pwcErrorTitle) == S_OK)
				{
					tbstrErrorTitle = pwcErrorTitle;
					FREE_MEMORY(pwcErrorTitle);
				}
				else
				{
					break;
				}
				*/
/*
				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VIEW_EXE_ERR, &pwcErrorString) == S_OK)
				{
					tbstrErrorString = pwcErrorString;
					FREE_MEMORY(pwcErrorString);
				}
				else
				{
					break;
				}

				MessageBox(tbstrErrorString, NULL, MB_OK|MB_ICONEXCLAMATION);
				hr = E_FAIL;
			}
			
			CHECK_HRESULT_BREAK

			if ((_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".bat") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".com") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".cmd") == 0))
			{
				int retVal = (int)ShellExecute(GetFocus(), _T("open"), "NotePad.exe", m_tbstrDocument, NULL, SW_SHOWNORMAL);
				if (retVal <= 32)
				{
					hr = E_FAIL;
				}
			}
			else
			{
				int retVal = (int)ShellExecute(GetFocus(), _T("open"), m_tbstrDocument, NULL, NULL, SW_SHOWNORMAL);
				if (retVal <= 32)
				{
					int retVal2 = (int)ShellExecute(GetFocus(), _T("open"), "NotePad.exe", m_tbstrDocument, NULL, SW_SHOWNORMAL);
					if (retVal2 <= 32)
					{
						hr = E_FAIL;
					}
				}
			}
*/
			if ((_tcslen(pcszDoc) > 5) &&
				((_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".txt") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".doc") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".htm") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 5], ".html") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".xls") == 0)
				|| (_stricmp(&pcszDoc[_tcslen(pcszDoc) - 4], ".pdf") == 0)))
			{
				int retVal = (int)ShellExecute(GetFocus(), _T("open"), m_tbstrDocument, NULL, NULL, SW_SHOWNORMAL);
				if (retVal <= 32)
				{
					hr = E_FAIL;
				}
			}
			else
			{
				WCHAR *pwcErrorString = NULL;
				_bstr_t tbstrErrorString;
			
				WCHAR *pwcErrorTitle = NULL;
				_bstr_t tbstrErrorTitle;

				if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VIEWDOC_ERR_TITLE, &pwcErrorTitle) == S_OK)
				{
					tbstrErrorTitle = pwcErrorTitle;
					FREE_MEMORY(pwcErrorTitle);
				}
				else
				{
					break;
				}

				if (m_boolSaveLinkPresent)
				{
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VIEWDOC_WEB_ERR, &pwcErrorString) == S_OK)
					{
						tbstrErrorString = pwcErrorString;
						FREE_MEMORY(pwcErrorString);
					}
					else
					{
						break;
					}
				}
				else
				{
					if(_LoadStringW(_Module.m_hInst, _GetDefaultLangID(), IDS_VIEWDOC_APP_ERR, &pwcErrorString) == S_OK)
					{
						tbstrErrorString = pwcErrorString;
						FREE_MEMORY(pwcErrorString);
					}
					else
					{
						break;
					}
				}
				MessageBox(tbstrErrorString, tbstrErrorTitle, MB_OK|MB_ICONEXCLAMATION);
				hr = E_FAIL;
			}
		} while (0);

//		DAccObject.Close();
//		DAWriteDocObject.Close();

		return hr;

}
