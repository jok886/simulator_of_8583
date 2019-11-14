#if !defined(AFX_ADDDLG_H__A5F4F130_4A80_43F6_9F4E_E5C5DB4D45C2__INCLUDED_)
#define AFX_ADDDLG_H__A5F4F130_4A80_43F6_9F4E_E5C5DB4D45C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddDlg dialog

class CAddDlg : public CDialog
{
// Construction
public:
	void SetP(HWND hWnd);
	CAddDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_disp;
	CString	m_exist;
	CString	m_gen;
	CString	m_len;
	CString	m_name;
	CString	m_read;
	CString	m_type;
	CString	m_write;
	//}}AFX_DATA
	HWND phWnd;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddDlg)
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDDLG_H__A5F4F130_4A80_43F6_9F4E_E5C5DB4D45C2__INCLUDED_)
