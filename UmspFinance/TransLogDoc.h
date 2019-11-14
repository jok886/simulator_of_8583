#if !defined(AFX_TRANSLOGDOC_H__1EB21284_4C57_4076_B131_57148968278F__INCLUDED_)
#define AFX_TRANSLOGDOC_H__1EB21284_4C57_4076_B131_57148968278F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransLogDoc.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransLogDoc document

class CTransLogDoc : public CDocument
{
protected:
	CTransLogDoc();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTransLogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransLogDoc)
	public:
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
	protected:
	virtual BOOL OnNewDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTransLogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransLogDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLOGDOC_H__1EB21284_4C57_4076_B131_57148968278F__INCLUDED_)
