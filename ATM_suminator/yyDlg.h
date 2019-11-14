// yyDlg.h : header file
//

#if !defined(AFX_YYDLG_H__F9530DFB_70DB_4718_B343_679AED14CF1C__INCLUDED_)
#define AFX_YYDLG_H__F9530DFB_70DB_4718_B343_679AED14CF1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CYyDlg dialog
#include "TranslateDlg.h"
#include "BcdToAscDlg.h"
#define F (WM_USER+5819)
#define O (WM_USER+5818)
struct InData
{
	HWND	hWnd;
	int		times;
	int		sec;
	
	CStringList logList;

	char	digram[1024];
	int		len;

	CString	srvIp;
	short	port;
};
class CYyDlg : public CDialog
{
// Construction
public:
	CYyDlg(CWnd* pParent = NULL);	// standard constructor
// Dialog Data
	//{{AFX_DATA(CYyDlg)
	enum { IDD = IDD_YY_DIALOG };
	CComboBox	m_digram;
	CListBox	m_lst;
	int		m_Times;
	CString	m_log;
	int		m_isec;
	UINT	m_iport;
	CString	m_ip;
	CString	m_pop;
	//}}AFX_DATA
struct InData inData;
CBcdToAscDlg dlg;
CWinThread *pThread;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CYyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOk3();
	afx_msg void OnSelchangedigram();
	afx_msg void OnOk2();
	afx_msg void OnCancel();
	afx_msg void OnSelchangeList3();
	afx_msg void OnButton1();
	//}}AFX_MSG
	afx_msg void DispInterface();
	afx_msg void ReCure();
	DECLARE_MESSAGE_MAP()
private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YYDLG_H__F9530DFB_70DB_4718_B343_679AED14CF1C__INCLUDED_)
