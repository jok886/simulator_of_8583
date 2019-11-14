#if !defined(AFX_MSGVIEWERDLG_H__1AF05BE2_3FA2_482F_99C8_3B0B8331A9AE__INCLUDED_)
#define AFX_MSGVIEWERDLG_H__1AF05BE2_3FA2_482F_99C8_3B0B8331A9AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgViewerDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgViewerDlg dialog
#include "HDSYC8583Digram.h"
class CMsgViewerDlg : public CDialog
{
// Construction
public:
	void FillData();
	HDSYC8583Digram msg;
	CString strHexMsg;
	CMsgViewerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMsgViewerDlg)
	enum { IDD = DLG_VIEW_MSG };
	CListCtrl	m_lstComm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL bInitDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGVIEWERDLG_H__1AF05BE2_3FA2_482F_99C8_3B0B8331A9AE__INCLUDED_)
