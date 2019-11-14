// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rs232TCPAdaptor.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg dialog


CSettingDlg::CSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingDlg)
	m_strIp = _T("127.0.0.1");
	m_iPort = 5819;
	//}}AFX_DATA_INIT
}


void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingDlg)
	DDX_Control(pDX, CMB_ROUTE, m_cbxRoute);
	DDX_Control(pDX, CMB_MSG, m_cbxMsg);
	DDX_Text(pDX, IDC_IP, m_strIp);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingDlg)
	ON_CBN_SELCHANGE(CMB_MSG, OnSelchangeMsg)
	ON_CBN_SELCHANGE(CMB_ROUTE, OnSelchangeRoute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingDlg message handlers

BOOL CSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbxMsg.AddString ("珠海农行");
	m_cbxMsg.AddString ("海南农行");
	m_cbxMsg.AddString ("深圳招商");
	m_cbxMsg.AddString ("北京银联");
	m_cbxMsg.AddString ("长沙银联");
	m_cbxMsg.AddString ("武汉银联");
	m_cbxMsg.AddString ("沈阳银联");
	m_cbxMsg.SetCurSel (6);
	iMsgType=6;
	m_cbxRoute.AddString ("原包返回");
	m_cbxRoute.AddString ("组报返回");
	m_cbxRoute.AddString ("发送主机");
	m_cbxRoute.SetCurSel (0);
	iRoute=0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingDlg::OnSelchangeMsg() 
{
	// TODO: Add your control notification handler code here
	iMsgType=this->m_cbxMsg.GetCurSel ();
	/*CString str;
	
	m_cbxRoute.GetWindowText (str);
	if(str=="珠海农行")
		iMsgType=1;
	else if(str=="海南农行")
		iMsgType=2;
	else if(str=="深圳招商")
		iMsgType=3;
	else if(str=="北京银联")
		iMsgType=4;
	else if(str=="长沙银联")
		iMsgType=5;
	else if(str=="武汉银联")
		iMsgType=6;*/
}

void CSettingDlg::OnSelchangeRoute() 
{
	// TODO: Add your control notification handler code here
	iRoute=this->m_cbxRoute.GetCurSel ();
}

void CSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	CDialog::OnOK();
}
