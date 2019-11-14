// UmspFinanceDoc.h : interface of the CUmspFinanceDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPFINANCEDOC_H__9BD39606_0FA6_4892_8124_BDCC3E2CEE9D__INCLUDED_)
#define AFX_UMSPFINANCEDOC_H__9BD39606_0FA6_4892_8124_BDCC3E2CEE9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUmspFinanceDoc : public CDocument
{
protected: // create from serialization only
	CUmspFinanceDoc();
	DECLARE_DYNCREATE(CUmspFinanceDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmspFinanceDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUmspFinanceDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUmspFinanceDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMSPFINANCEDOC_H__9BD39606_0FA6_4892_8124_BDCC3E2CEE9D__INCLUDED_)
