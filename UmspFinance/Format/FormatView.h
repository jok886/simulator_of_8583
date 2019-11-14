// FormatView.h : interface of the CFormatView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMATVIEW_H__0593FBCE_653D_4C9F_A655_7894ADCBDF18__INCLUDED_)
#define AFX_FORMATVIEW_H__0593FBCE_653D_4C9F_A655_7894ADCBDF18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "AddDlg.h"
#include "MsgDetailDlg.h"

#define ADDITEM (5819+WM_USER)
#define TRS_MSG_UPDATE (5820+WM_USER)

typedef struct _HDSY_CLI_MSG_
{
	HWND	hWnd;
	int	sock;
	char	ip[40];
	char	msg[1024];
}CliMsg;

class CFormatView : public CListView
{
protected: // create from serialization only
	CFormatView();
	DECLARE_DYNCREATE(CFormatView)

// Attributes
public:
	CFormatDoc* GetDocument();
	
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatView)
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
	virtual ~CFormatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormatView)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdd();
	afx_msg void OnDel();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdate();
	afx_msg void OnStartService();
	afx_msg void OnUpdateStartService(CCmdUI* pCmdUI);
	afx_msg void OnStopService();
	afx_msg void OnUpdateStopService(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg void AddItem();
	afx_msg void OnUpdateList();
	DECLARE_MESSAGE_MAP()
private:
	BOOL bHost;
	BOOL bSortAscending;


	static CliMsg cliMsg;

	BOOL bEnable;
	CWinThread *thdListen;
	CAddDlg *dlg;

	
	CMsgDetailDlg *msgdlg;

	void GyInit();
	BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
};

#ifndef _DEBUG  // debug version in FormatView.cpp
inline CFormatDoc* CFormatView::GetDocument()
   { return (CFormatDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATVIEW_H__0593FBCE_653D_4C9F_A655_7894ADCBDF18__INCLUDED_)
