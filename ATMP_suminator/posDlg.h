// posDlg.h : header file
//

#if !defined(AFX_POSDLG_H__00263A49_42E1_4FCE_9934_3C4B8A9703BF__INCLUDED_)
#define AFX_POSDLG_H__00263A49_42E1_4FCE_9934_3C4B8A9703BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPosDlg dialog

class CPosDlg : public CDialog
{
// Construction
public:
	CPosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPosDlg)
	enum { IDD = IDD_POS_DIALOG };
	CComboBox	m_cbx1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPosDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPosDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSDLG_H__00263A49_42E1_4FCE_9934_3C4B8A9703BF__INCLUDED_)
