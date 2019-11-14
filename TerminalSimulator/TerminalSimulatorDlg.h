// TerminalSimulatorDlg.h : header file
//

#if !defined(AFX_TERMINALSIMULATORDLG_H__9EC11A8E_703E_460D_9586_2408605F732D__INCLUDED_)
#define AFX_TERMINALSIMULATORDLG_H__9EC11A8E_703E_460D_9586_2408605F732D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTerminalSimulatorDlg dialog
typedef unsigned char BYTE;
typedef struct _HDSY_TERMINAL_IO_DATA
{
	BYTE	mti;		//*交易信息码
	BYTE	acc[10];	//*主帐户
	float	amount;		//*交易金额
	BYTE	termid[8];	//*终端标记号？？？
	BYTE	mechid[18];	//*商户标记号？？？
	BYTE	feetype;	//缴费类型
	BYTE	pin[8];		//*个人密码
	BYTE	result;		//交易执行结果
}TTermIOData;

class CTerminalSimulatorDlg : public CDialog
{
// Construction
public:
	CTerminalSimulatorDlg(CWnd* pParent = NULL);	// standard constructor
	

	TTermIOData termIOData;
// Dialog Data
	//{{AFX_DATA(CTerminalSimulatorDlg)
	enum { IDD = IDD_TERMINALSIMULATOR_DIALOG };
	CString m_strAcc ;
	CString m_hexFeeType;
	float m_fAmount;
	CString m_strMechNo ;
	CString m_strNote ;
	CString m_strPin ;
	CString m_hexRes ;
	CString	m_strTermID;
	CComboBox m_cbxTransType;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerminalSimulatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTerminalSimulatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeTranstype();
	afx_msg void OnChangeAmount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void HexToAsc(CString hex,unsigned char * asc);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERMINALSIMULATORDLG_H__9EC11A8E_703E_460D_9586_2408605F732D__INCLUDED_)
