// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__35B13B78_3F33_4860_82F2_F2B20F6D7C60__INCLUDED_)
#define AFX_MAINFRM_H__35B13B78_3F33_4860_82F2_F2B20F6D7C60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commonhead.h"

#define TRAY_ICON_MSG (WM_USER+1000)

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BOOL	bStartButtonEnable;
private:	
	void DelTrayICon();
	void AddTrayICon();
	
	CUmspEBAdap *adapEB;
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnStart();
	afx_msg void OnEnd();
	afx_msg void OnClose();
	afx_msg void OnMenuSelect(UINT , UINT, HMENU );
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnTrayIconClick(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__35B13B78_3F33_4860_82F2_F2B20F6D7C60__INCLUDED_)
