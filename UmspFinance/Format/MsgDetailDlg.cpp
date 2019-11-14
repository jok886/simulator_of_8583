// MsgDetailDlg.cpp : implementation file
//

#include "stdafx.h"
#include "format.h"
#include "MsgDetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgDetailDlg dialog


CMsgDetailDlg::CMsgDetailDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgDetailDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgDetailDlg)
	//}}AFX_DATA_INIT
	bInitDlg=TRUE;
}


void CMsgDetailDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgDetailDlg)
	DDX_Control(pDX, IDC_LIST1, m_lstComm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgDetailDlg, CDialog)
	//{{AFX_MSG_MAP(CMsgDetailDlg)
	ON_WM_SIZE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgDetailDlg message handlers

void CMsgDetailDlg::FillData()
{
	char rs[1024];
	m_lstComm.DeleteAllItems ();
	m_lstComm.InsertItem (0,"NAN");
	memset(rs,0,1024);
	m_lstComm.SetItemText (0,1,"报文起始码");
	m_lstComm.SetItemText (0,2,"02");

	m_lstComm.InsertItem (1,"NAN");
	memset(rs,0,1024);
	msg.GetLengthHead (rs);
	m_lstComm.SetItemText (1,1,"长度");
	m_lstComm.SetItemText (1,2,rs);

	m_lstComm.InsertItem (2,"NAN");
	memset(rs,0,1024);
	msg.GetDeviceHead (rs);
	m_lstComm.SetItemText (2,1,"网控器头");
	m_lstComm.SetItemText (2,2,rs);

	m_lstComm.InsertItem (3,"NAN");
	memset(rs,0,1024);
	msg.GetTransCode (rs);
	m_lstComm.SetItemText (3,1,"信息码");
	m_lstComm.SetItemText (3,2,rs);

	m_lstComm.InsertItem (4,"NAN");
	memset(rs,0,1024);
	msg.GetBitmap (rs);
	m_lstComm.SetItemText (4,1,"位元表");
	m_lstComm.SetItemText (4,2,rs);
	//64个域
	CString num,des;
	for(int i=1;i<=64;i++)
	{
		num.Format ("%02d",i);
		m_lstComm.InsertItem (i+4,num);
		if(msg.IsExistDomin (i))
			des="+";
		else
			des="-";
		m_lstComm.SetItemText (i+4,1,des);
		memset(rs,0,1024);
		msg.GetFieldValue (i-1,rs);
		m_lstComm.SetItemText (i+4,2,rs);
	}
	//
	m_lstComm.InsertItem (66+3,"NAN");
	m_lstComm.SetItemText (66+3,1,"报文结束码");
	m_lstComm.SetItemText (66+3,2,"03");
	m_lstComm.InsertItem (67+3,"NAN");
	m_lstComm.SetItemText (67+3,1,"校验码");
	m_lstComm.SetItemText (67+3,2,"**");

	m_lstComm.InsertItem (0,"NAN");
	m_lstComm.SetItemText (0,1,"密码明文");
	memset(rs,0,1024);
	msg.GetPassword(rs);
	m_lstComm.SetItemText (0,2,rs);
}

BOOL CMsgDetailDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
		CRect rc;
		this->GetWindowRect (&rc);
		m_lstComm.MoveWindow (0,0,rc.Width ()-10,rc.Height ()-30);
		bInitDlg=FALSE;
		m_lstComm.SetExtendedStyle
   (m_lstComm.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		m_lstComm.InsertColumn (0,"8583域号",LVCFMT_CENTER,80);
		m_lstComm.InsertColumn (1,"简要说明",LVCFMT_LEFT,180);
		m_lstComm.InsertColumn (2,"域内容",LVCFMT_LEFT,200);

	FillData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMsgDetailDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(!bInitDlg)
	{
		m_lstComm.MoveWindow (0,0,cx,cy);
	}
}

void CMsgDetailDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CString s1,s2;
	int icount=m_lstComm.GetItemCount ();
	int ipiv=0;
	while(ipiv<icount)
	{
		s1=m_lstComm.GetItemText (ipiv,0);
		s2=m_lstComm.GetItemText (ipiv,1);
		if(s1=="NAN" )
		{
			ipiv++;continue;
		}
		else if(s2.GetAt (0)=='+')
		{
			ipiv++;continue;
		}
		else 
		{
			m_lstComm.DeleteItem (ipiv);
			icount--;
		}
	}
	*pResult = 0;
}
