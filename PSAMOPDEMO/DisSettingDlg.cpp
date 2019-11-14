// DisSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "DisSettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisSettingDlg dialog


CDisSettingDlg::CDisSettingDlg(CWnd* pParent /*=NULL*/)
: CDialog(CDisSettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDisSettingDlg)
	m_strIp = _T("100.100.50.214");
	m_iPort = 6668;
	m_strAmk = _T("88888888888888888888888888888888");
	m_strCmk = _T("88888888888888888888888888888888");
	m_strSid = _T("1234567890123456");
	m_iTtkidx = 1;
	m_iTmkidx = 1;
	m_iComx = 1;
	m_strCmk2 = _T("88888888888888888888888888888888");
	m_strAmk2 = _T("88888888888888888888888888888888");
	m_iTmkVer = 0;
	m_iTmkGrp = 0;
	m_iTtkGrp = 0;
	m_iTtkVer = 0;
	//}}AFX_DATA_INIT
}


void CDisSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDisSettingDlg)
	DDX_Text(pDX, EDT_ENCRYPTOR_IP, m_strIp);
	DDV_MaxChars(pDX, m_strIp, 40);
	DDX_Text(pDX, EDT_ENCRYPTOR_PORT, m_iPort);
	DDV_MinMaxInt(pDX, m_iPort, 0, 60000);
	DDX_Text(pDX, EDT_PSAM_AMK, m_strAmk);
	DDV_MaxChars(pDX, m_strAmk, 32);
	DDX_Text(pDX, EDT_PSAM_CMK, m_strCmk);
	DDV_MaxChars(pDX, m_strCmk, 32);
	DDX_Text(pDX, EDT_PSAM_SID, m_strSid);
	DDV_MaxChars(pDX, m_strSid, 16);
	DDX_Text(pDX, EDT_ENCRYPTOR_TTK_IND, m_iTtkidx);
	DDV_MinMaxInt(pDX, m_iTtkidx, 0, 10);
	DDX_Text(pDX, EDT_ENCRYPTOR_TMK_IND, m_iTmkidx);
	DDV_MinMaxInt(pDX, m_iTmkidx, 0, 10);
	DDX_Text(pDX, EDT_COMX, m_iComx);
	DDV_MinMaxInt(pDX, m_iComx, 1, 9);
	DDX_Text(pDX, EDT_PSAM_CMK2, m_strCmk2);
	DDV_MaxChars(pDX, m_strCmk2, 32);
	DDX_Text(pDX, EDT_PSAM_AMK2, m_strAmk2);
	DDV_MaxChars(pDX, m_strAmk2, 32);
	DDX_Text(pDX, EDT_ENCRYPTOR_TMK_VER, m_iTmkVer);
	DDV_MinMaxInt(pDX, m_iTmkVer, 0, 2);
	DDX_Text(pDX, EDT_ENCRYPTOR_TMK_GRP, m_iTmkGrp);
	DDV_MinMaxInt(pDX, m_iTmkGrp, 0, 31);
	DDX_Text(pDX, EDT_ENCRYPTOR_TTK_GRP, m_iTtkGrp);
	DDV_MinMaxInt(pDX, m_iTtkGrp, 0, 31);
	DDX_Text(pDX, EDT_ENCRYPTOR_TTK_VER, m_iTtkVer);
	DDV_MinMaxInt(pDX, m_iTtkVer, 0, 2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDisSettingDlg, CDialog)
//{{AFX_MSG_MAP(CDisSettingDlg)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDisSettingDlg message handlers
extern CEncryptorAdap enadap;
void CDisSettingDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(m_strCmk!=m_strCmk2)
	{
		AfxMessageBox("CMK输入不一致.");
		return ;
	}
	if(m_strAmk!=m_strAmk2)
	{
		AfxMessageBox("AMK输入不一致.");
		return ;
	}
	m_strCmk.MakeUpper();
	m_strAmk.MakeUpper ();
	enadap.strIP =this->m_strIp ;
	enadap.iPort =this->m_iPort ;
	enadap.tmkidx =this->m_iTmkidx ;
	enadap.tpkidx =this->m_iTtkidx ;
}

void CDisSettingDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	UpdateData();
	if(m_strCmk!=m_strCmk2)
	{
		AfxMessageBox("CMK输入不一致.");
		return ;
	}
	if(m_strAmk!=m_strAmk2)
	{
		AfxMessageBox("AMK输入不一致.");
		return ;
	}
	enadap.strIP =this->m_strIp ;
	enadap.iPort =this->m_iPort ;
	enadap.tmkidx =this->m_iTmkidx ;
	enadap.tpkidx =this->m_iTtkidx ;
	CDialog::OnOK();
}

BOOL CDisSettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CenterWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
