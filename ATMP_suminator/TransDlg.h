#if !defined(AFX_TRANSDLG_H__CC0F2EB6_0E64_4960_8406_558FBDAFAC67__INCLUDED_)
#define AFX_TRANSDLG_H__CC0F2EB6_0E64_4960_8406_558FBDAFAC67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TransDlg.h : header file
//
#include "HDSYC8583Digram.h"
/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog
#include "OptionDlg.h"
#include "8583PosDigram.h"
#define PARSLE (WM_USER+5819)
#define TEST_HDSY (WM_USER+5820)
struct InData
{
	HWND	hWnd;

	char	digram[1024];

	int		len;

	SOCKET	s,sListen;
};
class CTransDlg : public CDialog
{
// Construction
public:
	HDSYC8583Digram posDigram;
	void InitDisplay();
	char ToHex(char c);
	COptionDlg *dlg;
	CString title;
	struct InData inData;
	CTransDlg(CWnd* pParent = NULL);   // standard constructor

	void AsciiToBcd(const char * str, char *hex, int count);

	void BcdToAscii(const char * str, char *hex, int count);
// Dialog Data
	//{{AFX_DATA(CTransDlg)
	enum { IDD = DLG_POSINFO };
	CString	m_digramhex;
	CString	m_strPrompt;
	BOOL	m_Write;
	CString	m_strMy;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransDlg)
	afx_msg void OnExit();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnOption();
	afx_msg void OnLstn();
	afx_msg void OnPars();
	afx_msg void OnDisconnect();
	afx_msg void OnGenerate();
	afx_msg void OnSetfocusFldX();
	afx_msg void OnCheck1();
	afx_msg void OnSend();
	afx_msg void OnChangeFld01();
	//}}AFX_MSG
	afx_msg void ParsleDigram();
	afx_msg void CCCCC();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRANSDLG_H__CC0F2EB6_0E64_4960_8406_558FBDAFAC67__INCLUDED_)
