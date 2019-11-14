#if !defined(AFX_MSGDETAILDLG_H__3F46D157_F8C6_45B1_903A_EC756E5A2F34__INCLUDED_)
#define AFX_MSGDETAILDLG_H__3F46D157_F8C6_45B1_903A_EC756E5A2F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDetailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgDetailDlg dialog
#include "..\\HDSYC8583Digram.h"
class CMsgDetailDlg : public CDialog
{
// Construction
public:
	void FillData();
	CMsgDetailDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgDetailDlg)
	enum { IDD = IDD_DIALOG2 };
	CListCtrl	m_lstComm;
	//}}AFX_DATA
	BOOL bInitDlg;
	HDSYC8583Digram msg;
	CString strHexMsg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgDetailDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDETAILDLG_H__3F46D157_F8C6_45B1_903A_EC756E5A2F34__INCLUDED_)
