// AddDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Format.h"
#include "AddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAddDlg dialog


CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAddDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAddDlg)
	m_disp = _T("");
	m_exist = _T("");
	m_gen = _T("");
	m_len = _T("");
	m_name = _T("");
	m_read = _T("");
	m_type = _T("");
	m_write = _T("");
	//}}AFX_DATA_INIT
	phWnd=NULL;
}


void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAddDlg)
	DDX_Text(pDX, IDC_EDIT_disp, m_disp);
	DDX_Text(pDX, IDC_EDIT_exist, m_exist);
	DDX_Text(pDX, IDC_EDIT_gen, m_gen);
	DDX_Text(pDX, IDC_EDIT_len, m_len);
	DDX_Text(pDX, IDC_EDIT_name, m_name);
	DDX_Text(pDX, IDC_EDIT_read, m_read);
	DDX_Text(pDX, IDC_EDIT_type, m_type);
	DDX_Text(pDX, IDC_EDIT_write, m_write);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialog)
	//{{AFX_MSG_MAP(CAddDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddDlg message handlers

void CAddDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CAddDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData();
	if(phWnd==NULL)
		return;
	::SendMessage(phWnd,5819+WM_USER,0,0);
	//CDialog::OnOK();
}

void CAddDlg::SetP(HWND hWnd)
{
	phWnd=hWnd;
}
