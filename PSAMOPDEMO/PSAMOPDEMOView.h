// PSAMOPDEMOView.h : interface of the CPSAMOPDEMOView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSAMOPDEMOVIEW_H__F49D057A_5912_46A8_9B19_1B8E6BEFF093__INCLUDED_)
#define AFX_PSAMOPDEMOVIEW_H__F49D057A_5912_46A8_9B19_1B8E6BEFF093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DisSettingDlg.h"
#include "st340.h"
#include "TestPsamCmdDlg.h"

class CPSAMOPDEMOView : public CListView
{
protected: // create from serialization only
	CPSAMOPDEMOView();
	DECLARE_DYNCREATE(CPSAMOPDEMOView)

// Attributes
public:
	CST340 *st340;
	int iComx;
	CDisSettingDlg *envdlg;
	char res[1024];
	CPSAMOPDEMODoc* GetDocument();
	BOOL bSortAscending;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSAMOPDEMOView)
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
	virtual ~CPSAMOPDEMOView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPSAMOPDEMOView)
	afx_msg void OnSelectMf();
	afx_msg void OnCreateMf();
	afx_msg void OnShutCom1();
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnWriteEfPub();
	afx_msg void OnSetDelay();
	afx_msg void OnCardIn();
	afx_msg void OnCardReset();
	afx_msg void OnCreateAdfKeyFile();
	afx_msg void OnCreateDfApp();
	afx_msg void OnCreateEfCardKey();
	afx_msg void OnCreateEfDir();
	afx_msg void OnCreateEfPub();
	afx_msg void OnPoweroff();
	afx_msg void OnPoweron();
	afx_msg void OnPsamCmd();
	afx_msg void OnWriteAdfWorkKey();
	afx_msg void OnWriteEfDir();
	afx_msg void OnWriteEfMk();
	afx_msg void OnMakeNewCard();
	afx_msg void OnWriteAppMk();
	afx_msg void OnEndCreateAdf();
	afx_msg void OnEndCreateMf();
	afx_msg void OnSettingEnv();
	afx_msg void OnWashCard();
	afx_msg void OnFilllAwk();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();
	afx_msg void OnChangeAwk();
	afx_msg void OnCheckCard();
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
private:
	void RestoreFromHisFile(char *filename);
	void SaveToHisFile(char * filename);
	BOOL SortTextItems(int nCol, BOOL bAscending, int low, int high);
	void CommitRequest(int flag,const char *cmd);
	void AddHistory(char * req,char *res);
};

#ifndef _DEBUG  // debug version in PSAMOPDEMOView.cpp
inline CPSAMOPDEMODoc* CPSAMOPDEMOView::GetDocument()
   { return (CPSAMOPDEMODoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSAMOPDEMOVIEW_H__F49D057A_5912_46A8_9B19_1B8E6BEFF093__INCLUDED_)
