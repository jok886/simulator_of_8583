#if !defined(AFX_ANALYSISDLG_H__BD57406F_C215_456D_A498_A076B5373A0E__INCLUDED_)
#define AFX_ANALYSISDLG_H__BD57406F_C215_456D_A498_A076B5373A0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnalysisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg dialog

class CAnalysisDlg : public CDialog
{
// Construction
public:
	BOOL IsBitExsit(int index);
	void SetBit(int index);
	CAnalysisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnalysisDlg)
	enum { IDD = IDD_bitmap };
	int		m_iBitsNum;
	CString	m_strParams;
	CString	m_strResult;

	//}}AFX_DATA
	unsigned char *hexData;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalysisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnalysisDlg)
	afx_msg void OnGen();
	afx_msg void OnParsel();
	afx_msg void OnChangeBits();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALYSISDLG_H__BD57406F_C215_456D_A498_A076B5373A0E__INCLUDED_)
