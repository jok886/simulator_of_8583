// TestPsamCmdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "TestPsamCmdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestPsamCmdDlg dialog


CTestPsamCmdDlg::CTestPsamCmdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestPsamCmdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestPsamCmdDlg)
	m_cmd = _T("");
	m_i = 2;
	m_iCom = 1;
	//}}AFX_DATA_INIT
	st340=NULL;
}


void CTestPsamCmdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestPsamCmdDlg)
	DDX_Text(pDX, IDC_EDIT1, m_cmd);
	DDX_Text(pDX, IDC_EDIT2, m_i);
	DDV_MinMaxInt(pDX, m_i, 1, 3);
	DDX_Text(pDX, EDT_COMX, m_iCom);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestPsamCmdDlg, CDialog)
	//{{AFX_MSG_MAP(CTestPsamCmdDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestPsamCmdDlg message handlers

void CTestPsamCmdDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(st340==NULL)
	UpdateData();
	{
		st340=new CST340(m_iCom);
		st340->CardReset ();
		st340->SetDelay(10);
	}
	if(m_i>1&&m_i<4)
		st340->PSAMCommand (m_i,m_cmd);
}

void CTestPsamCmdDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(st340!=NULL)
	{
		delete st340;
		st340=NULL;
	}
	CDialog::OnCancel();
}
