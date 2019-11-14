#if !defined(AFX_SETTINGDLG_H__96837DD5_AB39_497D_84CE_04EDC9E57417__INCLUDED_)
#define AFX_SETTINGDLG_H__96837DD5_AB39_497D_84CE_04EDC9E57417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog

class CSettingDlg : public CDialog
{
// Construction
public:
	CSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettingDlg)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_cbxRoute;
	CComboBox	m_cbxMsg;
	CString	m_strIp;
	int		m_iPort;
	//}}AFX_DATA
	int iMsgType;
	int iRoute;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeMsg();
	afx_msg void OnSelchangeRoute();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__96837DD5_AB39_497D_84CE_04EDC9E57417__INCLUDED_)
