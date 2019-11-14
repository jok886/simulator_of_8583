// yyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yy.h"
#include "yyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYyDlg dialog

CYyDlg::CYyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CYyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CYyDlg)
	m_Times = 10;
	m_log = _T("");
	m_isec = 100;
	m_iport = 5819;
	m_ip = _T("192.168.0.244");
	m_pop = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//dlg=NULL;
}

void CYyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CYyDlg)
	DDX_Control(pDX, cmb_digram, m_digram);
	DDX_Control(pDX, IDC_LIST3, m_lst);
	DDX_Text(pDX, IDC_EDIT1, m_Times);
	DDX_Text(pDX, IDC_EDIT2, m_isec);
	DDX_Text(pDX, edt_port, m_iport);
	DDX_Text(pDX, IDC_EDIT3, m_ip);
	DDX_Text(pDX, IDC_EDIT4, m_pop);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CYyDlg, CDialog)
	//{{AFX_MSG_MAP(CYyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK3, OnOk3)
	ON_CBN_SELCHANGE(cmb_digram, OnSelchangedigram)
	ON_BN_CLICKED(IDOK2, OnOk2)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
	ON_MESSAGE(F,DispInterface)
	ON_MESSAGE(O,ReCure)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYyDlg message handlers

BOOL CYyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//ATM报文
	m_digram.AddString("OEX");
	m_digram.AddString("CWD");
	m_digram.AddString("INQ");
	m_digram.AddString("CHK");
	m_digram.AddString("RQK");
	m_digram.AddString("INT");
	m_digram.AddString("RWT");

	//POS报文
	m_digram.AddString ("POS_1-取款&消费");
	pThread=NULL;
	memset(inData.digram,0,1024);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CYyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CYyDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CYyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int g_time(char * curr_time)
{
    struct tm *tm;
    time_t t;
    time(&t);
    tm=localtime(&t);
    sprintf(curr_time,"%02d%02d%02d",tm->tm_hour,tm->tm_min,tm->tm_sec);
	//AfxMessageBox(curr_time);
    return 0;
}
UINT ThreadProc1(LPVOID lpData)
{
	struct		InData * inData=(struct InData *)lpData;
	char		RcvBuf[1024];
	int			iMsgLen;
	int			iSocket;
	struct		sockaddr_in serv_addr;
	char		begintime[7];
	char		endtime[7];
	int 		j,ij;    
	CString		msg;
	
	char s[3];

	
	g_time( begintime );
	for( ij=1; ij<=inData->times; ij++ ) 
	{
		Sleep(inData->sec);
		if ((iSocket= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			msg.Format ("建立套接字失败！");
			inData->logList.AddHead(msg);
			SendMessage(inData->hWnd ,F,NULL,NULL);
			break;
		}
		int optval=10;
		if(setsockopt(iSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &optval, sizeof(optval)) < 0)
		{
			msg.Format ("set socket error : ");
			closesocket(iSocket);
			inData->logList.AddHead(msg);
			SendMessage(inData->hWnd ,F,NULL,NULL);
			break;
		}
		memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(inData->srvIp);
		serv_addr.sin_port = htons( inData->port );
		if (connect(iSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		{
			msg.Format ("和对等端建立连接出错");
			closesocket(iSocket);
			inData->logList.AddHead(msg);
			SendMessage(inData->hWnd ,F,NULL,NULL);
			break;
		}

		//memset(RcvBuf,0x00,sizeof(RcvBuf));

		//sprintf(RcvBuf,"10000A0002RQK00060000202200000000000000CC" );

		//msg.Format ("[%04d]发送>[%s]",ij, inData->digram);
		msg.Format ("[%04d]发送>[",ij);
		for(int i=0;i<inData->len;i++)
		{
			sprintf(s,"%02X",*(inData->digram+i));
			msg+=s;
		}
		msg+="]";
		inData->logList.AddHead(msg );
		SendMessage(inData->hWnd ,F,NULL,NULL);
		//printf("\nsend buf =[%s]\n", RcvBuf);
		if((iMsgLen = send(iSocket,inData->digram,inData->len,0))<=0)
     		{
			msg.Format ("发送SOCKET失败，错误码为=[%d]",errno);
			inData->logList.AddHead(msg);
			SendMessage(inData->hWnd ,F,NULL,NULL);
			closesocket(iSocket);
			break;
		}
		memset(RcvBuf,0x00,sizeof(RcvBuf));
		iMsgLen=1024;
		if((iMsgLen = recv(iSocket,RcvBuf,iMsgLen,0)) < 0)
		{
	       	msg.Format ("接受SOCKET失败，错误码为=[%d]",errno);
			inData->logList.AddHead(msg);
			SendMessage(inData->hWnd ,F,NULL,NULL);
	       	closesocket(iSocket);
			break;
		}
		msg.Format ("[%04d]接受<[",ij);
		for(i=0;i<iMsgLen;i++)
		{
			sprintf(s,"%02X",*(RcvBuf+i));/*02X*/
			msg+=s;
		}
		msg+="]";
		inData->logList.AddHead(msg);
		SendMessage(inData->hWnd ,F,NULL,NULL);
		j=1;		
		closesocket(iSocket);
		shutdown(iSocket,2);
	}
	g_time( endtime );		
	msg.Format("============进行 [%d]笔交易 开始时间[%s] 结束时间[%s]",ij-1, begintime, endtime );
	inData->logList.AddHead(msg);
	SendMessage(inData->hWnd ,F,NULL,NULL);
	SendMessage(inData->hWnd ,O,NULL,NULL);
	closesocket(iSocket);
	shutdown(iSocket,2);
	return 1;

}


void CYyDlg::OnOK() 
{
	this->GetDlgItem(IDOK3)->EnableWindow(TRUE);
	this->GetDlgItem(IDOK2)->EnableWindow(TRUE);
	this->GetDlgItem(IDOK)->EnableWindow(FALSE);
	if(pThread!=NULL)
	{
		pThread->ResumeThread();
		this->GetDlgItem(IDOK2)->EnableWindow(TRUE);
		return;
	}
	m_lst.InsertString(0, "==========开始新一轮测试=========");
	UpdateData(TRUE);
	inData.sec=m_isec;
	inData.times =m_Times;
	//inData.logList.Empty(); 
	HWND hWnd=this->m_hWnd;
	inData.hWnd=hWnd;
	
	inData.srvIp=m_ip;
	inData.port =m_iport;
	pThread=AfxBeginThread(ThreadProc1,(LPVOID)(&inData));



}

void CYyDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//UpdateData(FALSE);
	//m_lst.AddString(inData.logList.GetHead());
	CDialog::OnTimer(nIDEvent);
}

void CYyDlg::DispInterface()
{
	//memset(inData.digram,30,24);
	int a=inData.logList.GetCount();
	if (a==0)
		return;
	else
	{
		m_lst.InsertString(0,inData.logList.GetHead());
	}
}
void CYyDlg::ReCure()
{
	this->GetDlgItem(IDOK)->EnableWindow(TRUE);
	pThread=NULL;
	this->GetDlgItem(IDOK2)->EnableWindow(FALSE);
	this->GetDlgItem(IDOK3)->EnableWindow(FALSE);

}
void CYyDlg::OnOk3() 
{
	// TODO: Add your control notification handler code here
	if(pThread!=NULL)
	{
		::TerminateThread(pThread->m_hThread,000);
		pThread=NULL;
		m_lst.InsertString(0,"************线程被杀死！");
		this->GetDlgItem(IDOK)->EnableWindow(TRUE);
		this->GetDlgItem(IDOK2)->EnableWindow(FALSE);
	}
	this->GetDlgItem(IDOK3)->EnableWindow(FALSE);
}

void CYyDlg::OnSelchangedigram() 
{
	// TODO: Add your control notification handler code here
	memset(inData.digram,0,1024);
	int nIndex = m_digram.GetCurSel();
	CString rString ;
	m_digram.GetLBText( nIndex, rString );
	if(rString.Left(3)=="RQK")
	{
		//AfxMessageBox("RQK");
		strcpy(inData.digram,"10000A0002RQK00060000202200000000000000CC");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(3)=="CWD")
	{
		//AfxMessageBox("CWD");
		strcpy(inData.digram,"10000A0002CWD00080008202200000000000000O0171::<8371=951::=195==1560500000008359013512517010101091129=000000000000=000000000000=1=183591828FFFFFF19?2<8270=941::=0000000FFFFFFFFFFFFFF3<?>40<5;19>=>>771::<8371=951::=195AAAAAA0=961::=000瀠W`�");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(3)=="OEX")
	{
		//AfxMessageBox("OEX");
		strcpy(inData.digram,"10000A0002OEX00000000000000000000000010C2037");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(3)=="CHK")
	{
		//AfxMessageBox("CHK");
		strcpy(inData.digram,"10000A0002CHK00020001202200000000000000O");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(3)=="INT")
	{
		//AfxMessageBox("INT");
		strcpy(inData.digram,"10000A0002INT00000000000000000000000010SC");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(3)=="RWT")
	{
		//AfxMessageBox("RWT");
		strcpy(inData.digram,"10000A1221RWT00000000000000000000000010S0001000000500000010000000000000000000000000000000000000000000000000000000001000000000000010000000000002222");
		inData.len=strlen(inData.digram);
	}
	else if(rString.Left(5)=="POS_1")
	{
		//AfxMessageBox("POS_1");
		if(dlg.DoModal ()==IDOK)
			memcpy(inData.digram,dlg.asc ,dlg.len/2 );
		//m_iport=5010;
		inData.len =dlg.len/2;
	}
}	

void CYyDlg::OnOk2() 
{
	// TODO: Add your control notification handler code here
	this->GetDlgItem(IDOK2)->EnableWindow(FALSE);
	if(pThread!=NULL)
	{
		pThread->SuspendThread();
		this->GetDlgItem(IDOK2)->EnableWindow(FALSE);
		this->GetDlgItem(IDOK)->EnableWindow(TRUE);
	}
}

void CYyDlg::OnCancel() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CYyDlg::OnSelchangeList3() 
{
	// TODO: Add your control notification handler code here
	m_lst.GetText(m_lst.GetCurSel(),m_pop);
	UpdateData(FALSE);
}

void CYyDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CTranslateDlg dlg;
	dlg.DoModal();
	//接收80号端口的消息，转发到端口
	//1、建立监听端口
		SOCKET               s;    
		struct sockaddr_in   tcpaddr;
		int                  port = 80;

		s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		tcpaddr.sin_family = AF_INET;
		tcpaddr.sin_port = htons(port);    
		tcpaddr.sin_addr.s_addr = htonl(INADDR_ANY);

		bind(s, (SOCKADDR *)&tcpaddr, sizeof(tcpaddr));


}
