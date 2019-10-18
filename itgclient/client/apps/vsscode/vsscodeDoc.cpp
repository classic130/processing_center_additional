// vsscodeDoc.cpp : implementation of the CVsscodeDoc class
//

#include "stdafx.h"
#include "vsscode.h"

#include "vsscodeDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVsscodeDoc

IMPLEMENT_DYNCREATE(CVsscodeDoc, CDocument)

BEGIN_MESSAGE_MAP(CVsscodeDoc, CDocument)
	//{{AFX_MSG_MAP(CVsscodeDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVsscodeDoc construction/destruction

CVsscodeDoc::CVsscodeDoc()
{
	// TODO: add one-time construction code here

}

CVsscodeDoc::~CVsscodeDoc()
{
}

BOOL CVsscodeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CVsscodeDoc serialization

void CVsscodeDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CVsscodeDoc diagnostics

#ifdef _DEBUG
void CVsscodeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVsscodeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CVsscodeDoc commands
