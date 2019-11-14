#if !defined(AFX_BCDTOASCDLG_H__4658827F_0BA0_422C_8127_E46CF9DF9AE7__INCLUDED_)
#define AFX_BCDTOASCDLG_H__4658827F_0BA0_422C_8127_E46CF9DF9AE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BcdToAscDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBcdToAscDlg dialog

class CBcdToAscDlg : public CDialog
{
// Construction
public:
	CBcdToAscDlg(CWnd* pParent = NULL);   // standard constructor

	void AsciiToBcd(const char * str, char *hex, int count);
// Dialog Data
	//{{AFX_DATA(CBcdToAscDlg)
	enum { IDD = IDD_DIALOG2 };
	CString	m_bcd;
	//}}AFX_DATA
	char hex[2048];
	char asc[1024];
	int len;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBcdToAscDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBcdToAscDlg)
	afx_msg void OnChangebcd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCDTOASCDLG_H__4658827F_0BA0_422C_8127_E46CF9DF9AE7__INCLUDED_)
