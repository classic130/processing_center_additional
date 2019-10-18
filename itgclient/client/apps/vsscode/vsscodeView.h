// vsscodeView.h : interface of the CVsscodeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSSCODEVIEW_H__6F33FF9C_7187_11D5_8C95_0010830169AF__INCLUDED_)
#define AFX_VSSCODEVIEW_H__6F33FF9C_7187_11D5_8C95_0010830169AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVsscodeView : public CView
{
protected: // create from serialization only
	CVsscodeView();
	DECLARE_DYNCREATE(CVsscodeView)

// Attributes
public:
	CVsscodeDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVsscodeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVsscodeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVsscodeView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in vsscodeView.cpp
inline CVsscodeDoc* CVsscodeView::GetDocument()
   { return (CVsscodeDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSSCODEVIEW_H__6F33FF9C_7187_11D5_8C95_0010830169AF__INCLUDED_)
