// vsscodeView.cpp : implementation of the CVsscodeView class
//

#include "stdafx.h"
#include "vsscode.h"

#include "vsscodeDoc.h"
#include "vsscodeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVsscodeView

IMPLEMENT_DYNCREATE(CVsscodeView, CView)

BEGIN_MESSAGE_MAP(CVsscodeView, CView)
	//{{AFX_MSG_MAP(CVsscodeView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVsscodeView construction/destruction

CVsscodeView::CVsscodeView()
{
	// TODO: add construction code here

}

CVsscodeView::~CVsscodeView()
{
}

BOOL CVsscodeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CVsscodeView drawing

void CVsscodeView::OnDraw(CDC* pDC)
{
	CVsscodeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CVsscodeView diagnostics

#ifdef _DEBUG
void CVsscodeView::AssertValid() const
{
	CView::AssertValid();
}

void CVsscodeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVsscodeDoc* CVsscodeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVsscodeDoc)));
	return (CVsscodeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVsscodeView message handlers

