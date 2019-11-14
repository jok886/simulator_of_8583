#if !defined(AFX_TRANSLATEDLG_H__87ACFE87_2AED_4F30_AF32_F3A931297455__INCLUDED_)
#define AFX_TRANSLATEDLG_H__87ACFE87_2AED_4F30_AF32_F3A931297455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TranslateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg dialog

class CTranslateDlg : public CDialog
{
// Construction
public:
	CTranslateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTranslateDlg)
	enum { IDD = IDD_DIALOG1 };
	BOOL	m_bitoa;
	CString	m_tar;
	CString	m_src;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTranslateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTranslateDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSLATEDLG_H__87ACFE87_2AED_4F30_AF32_F3A931297455__INCLUDED_)
