#if !defined(AFX_TRANSLOGVIEW_H__0F1F9235_0F05_4E5C_8741_E0B031A04761__INCLUDED_)
#define AFX_TRANSLOGVIEW_H__0F1F9235_0F05_4E5C_8741_E0B031A04761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransLogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTransLogView view

class CTransLogView : public CListView
{
protected:
	CTransLogView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CTransLogView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransLogView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTransLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CTransLogView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLOGVIEW_H__0F1F9235_0F05_4E5C_8741_E0B031A04761__INCLUDED_)
