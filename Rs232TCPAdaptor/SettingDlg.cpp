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
	m_cbxMsg.AddString ("�麣ũ��");
	m_cbxMsg.AddString ("����ũ��");
	m_cbxMsg.AddString ("��������");
	m_cbxMsg.AddString ("��������");
	m_cbxMsg.AddString ("��ɳ����");
	m_cbxMsg.AddString ("�人����");
	m_cbxMsg.AddString ("��������");
	m_cbxMsg.SetCurSel (6);
	iMsgType=6;
	m_cbxRoute.AddString ("ԭ������");
	m_cbxRoute.AddString ("�鱨����");
	m_cbxRoute.AddString ("��������");
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
	if(str=="�麣ũ��")
		iMsgType=1;
	else if(str=="����ũ��")
		iMsgType=2;
	else if(str=="��������")
		iMsgType=3;
	else if(str=="��������")
		iMsgType=4;
	else if(str=="��ɳ����")
		iMsgType=5;
	else if(str=="�人����")
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
