#if !defined(AFX_REDIRECTDLG_H__0D7DF1DC_25E1_4571_BC46_DBF8BCC05465__INCLUDED_)
#define AFX_REDIRECTDLG_H__0D7DF1DC_25E1_4571_BC46_DBF8BCC05465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReDirectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReDirectDlg dialog

class CReDirectDlg : public CDialog
{
// Construction
public:
	void CreateCliSocket();
	void CreateLstnSocket();
	CReDirectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CReDirectDlg)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReDirectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReDirectDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REDIRECTDLG_H__0D7DF1DC_25E1_4571_BC46_DBF8BCC05465__INCLUDED_)
