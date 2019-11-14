#if !defined(AFX_TESTPSAMCMDDLG_H__E8E20F05_0D04_4457_A389_CAA840814E5A__INCLUDED_)
#define AFX_TESTPSAMCMDDLG_H__E8E20F05_0D04_4457_A389_CAA840814E5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestPsamCmdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestPsamCmdDlg dialog
#include "st340.h"
class CTestPsamCmdDlg : public CDialog
{
// Construction
public:
	CST340 *st340;
	CTestPsamCmdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestPsamCmdDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_cmd;
	int		m_i;
	int		m_iCom;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPsamCmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestPsamCmdDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPSAMCMDDLG_H__E8E20F05_0D04_4457_A389_CAA840814E5A__INCLUDED_)
