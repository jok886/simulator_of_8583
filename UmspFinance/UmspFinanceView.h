// UmspFinanceView.h : interface of the CUmspFinanceView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPFINANCEVIEW_H__DE46067E_EF4A_49E6_9433_254170702435__INCLUDED_)
#define AFX_UMSPFINANCEVIEW_H__DE46067E_EF4A_49E6_9433_254170702435__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CUmspFinanceView : public CListView
{
protected: // create from serialization only
	CUmspFinanceView();
	DECLARE_DYNCREATE(CUmspFinanceView)

// Attributes
public:
	CUmspFinanceDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmspFinanceView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUmspFinanceView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CUmspFinanceView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in UmspFinanceView.cpp
inline CUmspFinanceDoc* CUmspFinanceView::GetDocument()
   { return (CUmspFinanceDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMSPFINANCEVIEW_H__DE46067E_EF4A_49E6_9433_254170702435__INCLUDED_)
