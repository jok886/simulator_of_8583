//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES
#if !defined(AFX_COMMANDDLG_H__6C5B4723_690F_4650_AA81_F35ABE7B3CE7__INCLUDED_)
#define AFX_COMMANDDLG_H__6C5B4723_690F_4650_AA81_F35ABE7B3CE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommandDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog

class CCommandDlg : public CDialog
{
// Construction
public:
	CCommandDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommandDlg)
	enum { IDD = IDD_COMMOND_DIALOG };
	CListCtrl	m_lstResult;
	CString	m_strCommand;
	CString	m_strRespond;
	CMSComm	m_Comm;
	//}}AFX_DATA
	int is,ic;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommandDlg)
	afx_msg void OnOnCommMscomm3();
	virtual BOOL OnInitDialog();
	afx_msg void OnAddCommand();
	afx_msg void OnSendCommand();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SendCommand();
	char ConvertHexChar(char ch);
	int String2Hex(CString str, CByteArray &senddata);
	BOOL CheckMsgFormat(CString msg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDDLG_H__6C5B4723_690F_4650_AA81_F35ABE7B3CE7__INCLUDED_)
