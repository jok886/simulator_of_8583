#if !defined(AFX_LEFTVIEWONE_H__A2B3787A_61E7_4E74_8621_E8AB0A6DEC59__INCLUDED_)
#define AFX_LEFTVIEWONE_H__A2B3787A_61E7_4E74_8621_E8AB0A6DEC59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeftViewOne.h : header file
//

class CPSAMOPDEMODoc;


/////////////////////////////////////////////////////////////////////////////
// CLeftViewOne view

class CLeftViewOne : public CTreeView
{
protected:
	CLeftViewOne();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLeftViewOne)

// Attributes
public:

	CPSAMOPDEMODoc* GetDocument();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftViewOne)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct

	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLeftViewOne();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLeftViewOne)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnFileNew();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CPSAMOPDEMODoc* CLeftView::GetDocument()
{ return (CPSAMOPDEMODoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEWONE_H__A2B3787A_61E7_4E74_8621_E8AB0A6DEC59__INCLUDED_)
