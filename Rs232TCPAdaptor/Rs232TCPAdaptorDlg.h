// Rs232TCPAdaptorDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_RS232TCPADAPTORDLG_H__3C2A18E1_62A0_4FE5_B1F1_836716682CA6__INCLUDED_)
#define AFX_RS232TCPADAPTORDLG_H__3C2A18E1_62A0_4FE5_B1F1_836716682CA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRs232TCPAdaptorDlg dialog
#define BEGIN_TRANS (WM_USER+5819)
#include "MsgViewerDlg.h"
#include "SettingDlg.h"
#include "CommandDlg.h"
#define AFTER_TRANS_END (WM_USER+5555)
struct _IO_DATA_
{
	char	ip[128];
	short	port;
	char	msgSnd[1024];
	int		lenSnd;
	char	msgRev[1024];
	int		lenRev;
	HWND	Wnd;
};
class CRs232TCPAdaptorDlg : public CDialog
{
// Construction
public:
	CRs232TCPAdaptorDlg(CWnd* pParent = NULL);	// standard constructor
	struct _IO_DATA_ ioData;
	unsigned char gen8583[2048];
	int iMsgType,iRoute;
	int ilen;
	CMsgViewerDlg *dlg;

	int iThreadCount;
// Dialog Data
	//{{AFX_DATA(CRs232TCPAdaptorDlg)
	enum { IDD = IDD_RS232TCPADAPTOR_DIALOG };
	CEdit	m_edt;
	CListCtrl	m_lstComm;
	CMSComm	m_comm;

	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRs232TCPAdaptorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRs232TCPAdaptorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCommMscomm3();
	afx_msg void OnOpen();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClose();
	afx_msg void OnOpen2();
	afx_msg void OnOption();
	afx_msg void OnDEBUGSeRIAL();
	afx_msg void OnAnlysisBITMAP();
	afx_msg void OnTofile();
	afx_msg void Ondes();
	afx_msg void OnSendNull();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnCancelMode();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnOpen4();
	afx_msg void OnThreadTest();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	afx_msg void OnBeginTrans();
	afx_msg void OnAfterTransEnd();
	DECLARE_MESSAGE_MAP()
private:
	char ConvertHexChar(char ch);
	int String2Hex(CString str, CByteArray &senddata);
	void Sta360(CByteArray &buf, CByteArray &res);
	char ToHex(char c);
	void BcdToAscii(const char * hex, char *str, int count);
	BOOL CheckMsgFormat(CString msg);
	void AsciiToBcd(const char *str, char *hex, int count);
	BOOL bInitDlg;
	CString strEdt;
	CString strSvrIp;
	short	iSvrPort;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232TCPADAPTORDLG_H__3C2A18E1_62A0_4FE5_B1F1_836716682CA6__INCLUDED_)
