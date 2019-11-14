#if !defined(AFX_DESDLG_H__33D4FA42_A950_4A9E_A75C_FAF49F13C06B__INCLUDED_)
#define AFX_DESDLG_H__33D4FA42_A950_4A9E_A75C_FAF49F13C06B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDesDlg dialog
#include "Des.h"
class CDesDlg : public CDialog
{
// Construction
public:
	CDesDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDesDlg)
	enum { IDD = IDD_des };
	CString	m_key;
	CString	m_src;
	CString	m_tag;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDesDlg)
	afx_msg void OnEncode();
	afx_msg void OnEncry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESDLG_H__33D4FA42_A950_4A9E_A75C_FAF49F13C06B__INCLUDED_)
