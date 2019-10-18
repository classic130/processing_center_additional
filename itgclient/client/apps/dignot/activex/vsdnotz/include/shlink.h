// Class that implements a hyperlink static control
#ifndef __SHLINK_H_
#define __SHLINK_H_

#include "nzdatacc.h"
#include "nzmacros.h"

class CHLink : public CWindowImpl<CHLink>
{
public :
	DECLARE_WND_SUPERCLASS( _T("HLink"), _T("Static") )   
		
	CHLink();

	void SetLinkText(LPCTSTR szLink);
	void SetDocumentTitle(_bstr_t i_tbstrDocumentTitle);
	void SetDocument(_bstr_t i_tbstrDocument);
	void SetUserAgent(_bstr_t i_tbstrUserAgent);
	void SetRecordData(BYTE* i_pbRecordData);
	void SetRecordDataLen(DWORD i_dwRecordDataLen);
	void SetSaveLinkPresent(bool i_boolSaveLinkPresent);

	BEGIN_MSG_MAP(CHLink)
	  MESSAGE_HANDLER( WM_MOUSEMOVE, OnMouseMove )
      // uses message reflection: WM_* comes back as OCM_*
      MESSAGE_HANDLER( OCM_COMMAND, OnCommand )
      MESSAGE_HANDLER( OCM_CTLCOLORSTATIC, OnCtlColor )
      MESSAGE_HANDLER( WM_DESTROY, OnDestroy ) // not a reflected message
      DEFAULT_REFLECTION_HANDLER()   
	END_MSG_MAP()

	LRESULT OnDestroy(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT OnMouseMove(UINT, WPARAM wParam, LPARAM, BOOL&);
	LRESULT OnCommand(UINT, WPARAM wParam, LPARAM, BOOL&);
	LRESULT OnCtlColor(UINT, WPARAM wParam, LPARAM, BOOL&);

private:   
	COLORREF m_colorUnvisited;   
	COLORREF m_colorVisited;
	COLORREF m_colorVisiting;
	BOOL m_bVisited, m_bVisiting;
	HFONT m_hFont;   
	_bstr_t m_bstrLink;
	_bstr_t m_tbstrDocumentTitle;
	_bstr_t m_tbstrDocument;
	_bstr_t m_tbstrUserAgent;
	BYTE* m_pbRecordData;
	DWORD m_dwRecordDataLen;
	BOOL m_boolSaveLinkPresent;
	HCURSOR m_hLinkCursor;

	HRESULT _SaveReceiptAndDocument();
	HRESULT _ViewOriginalDocument();

};

#endif	// __SHLINK_H_