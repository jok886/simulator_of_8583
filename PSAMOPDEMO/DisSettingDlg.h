#if !defined(AFX_DISSETTINGDLG_H__8E9DC8D7_FE58_464F_AD10_4B02D5879379__INCLUDED_)
#define AFX_DISSETTINGDLG_H__8E9DC8D7_FE58_464F_AD10_4B02D5879379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DisSettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDisSettingDlg dialog
#include "EncryptorAdap.h"
class CDisSettingDlg : public CDialog
{
// Construction
public:
	CDisSettingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDisSettingDlg)
	enum { IDD = IDD_DIALOG2 };
	CString	m_strIp;
	int		m_iPort;
	CString	m_strAmk;
	CString	m_strCmk;
	CString	m_strSid;
	int		m_iTtkidx;
	int		m_iTmkidx;
	int		m_iComx;
	CString	m_strCmk2;
	CString	m_strAmk2;
	int		m_iTmkVer;
	int		m_iTmkGrp;
	int		m_iTtkGrp;
	int		m_iTtkVer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisSettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDisSettingDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISSETTINGDLG_H__8E9DC8D7_FE58_464F_AD10_4B02D5879379__INCLUDED_)
