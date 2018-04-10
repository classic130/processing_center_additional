// vsscodeDoc.h : interface of the CVsscodeDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSSCODEDOC_H__6F33FF9A_7187_11D5_8C95_0010830169AF__INCLUDED_)
#define AFX_VSSCODEDOC_H__6F33FF9A_7187_11D5_8C95_0010830169AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVsscodeDoc : public CDocument
{
protected: // create from serialization only
	CVsscodeDoc();
	DECLARE_DYNCREATE(CVsscodeDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVsscodeDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVsscodeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CVsscodeDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSSCODEDOC_H__6F33FF9A_7187_11D5_8C95_0010830169AF__INCLUDED_)
