// TerminalSimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TerminalSimulator.h"
#include "TerminalSimulatorDlg.h"

#include <afxsock.h>


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
// CTerminalSimulatorDlg dialog

CTerminalSimulatorDlg::CTerminalSimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTerminalSimulatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTerminalSimulatorDlg)
	m_strAcc = _T("");
	m_hexFeeType = _T("");
	m_fAmount = 0.0f;
	m_strMechNo = _T("");
	m_strNote = _T("");
	m_strPin = _T("");
	m_hexRes = _T("");
	m_strTermID = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTerminalSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTerminalSimulatorDlg)
	DDX_Text(pDX, EDT_ACC, m_strAcc);
	DDV_MaxChars(pDX, m_strAcc, 20);
	DDX_Text(pDX, EDT_FEETYPE, m_hexFeeType);
	DDV_MaxChars(pDX, m_hexFeeType, 2);
	DDX_Text(pDX, EDT_AMOUNT, m_fAmount);
	DDV_MinMaxFloat(pDX, m_fAmount, 0.f, 100000.0f);
	DDX_Text(pDX, EDT_MECHNO, m_strMechNo);
	DDV_MaxChars(pDX, m_strMechNo, 18);
	DDX_Text(pDX, EDT_NOTE, m_strNote);
	DDX_Text(pDX, EDT_PIN, m_strPin);
	DDV_MaxChars(pDX, m_strPin, 8);
	DDX_Text(pDX, EDT_RESULT, m_hexRes);
	DDV_MaxChars(pDX, m_hexRes, 2);
	DDX_Text(pDX, EDT_TERMID, m_strTermID);
	DDV_MaxChars(pDX, m_strTermID, 8);
	DDX_Control(pDX, CMB_TRANSTYPE, m_cbxTransType);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTerminalSimulatorDlg, CDialog)
	//{{AFX_MSG_MAP(CTerminalSimulatorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(CMB_TRANSTYPE, OnSelchangeTranstype)
	ON_EN_CHANGE(EDT_AMOUNT, OnChangeAmount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTerminalSimulatorDlg message handlers

BOOL CTerminalSimulatorDlg::OnInitDialog()
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
	m_cbxTransType.AddString ("签到");
	m_cbxTransType.AddString ("缴费查询");
	m_cbxTransType.AddString ("余额查询");
	m_cbxTransType.AddString ("缴费");
	m_cbxTransType.SetCurSel (0);
	termIOData.mti=2;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTerminalSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTerminalSimulatorDlg::OnPaint() 
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
HCURSOR CTerminalSimulatorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTerminalSimulatorDlg::OnOK() 
{
	memset((char *)&termIOData,0,sizeof(termIOData));
	// 取得用户输入值
	UpdateData(TRUE);
	HexToAsc(m_strAcc,termIOData.acc);
	termIOData.amount =m_fAmount;
	HexToAsc(m_hexFeeType,&termIOData.feetype);
	memcpy(termIOData.mechid,m_strMechNo,m_strMechNo.GetLength ());
	termIOData.mti = m_cbxTransType.GetCurSel ();
	HexToAsc(m_strPin,termIOData.pin);
	termIOData.result =0;
	memcpy(termIOData.termid,m_strTermID,m_strTermID.GetLength ());

	//连接主机通讯，发出交易请求
		SOCKET iSocket;
		char pstr[2094];
		int optval;
		struct 	sockaddr_in serv_addr;
		int recv_len=sizeof(termIOData);
		memset(pstr,0,sizeof(pstr));
		memcpy(pstr,(unsigned char *)&termIOData,recv_len);

		if ((iSocket= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			return ;
		}
		optval=30;
		if(setsockopt(iSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &optval, sizeof(optval)) < 0)
		{
			closesocket(iSocket);
			return ;
		}
		memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		serv_addr.sin_port = htons(5566);
		if (connect(iSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		{
			closesocket(iSocket);
			return ;
		}		
		if((recv_len = send(iSocket,pstr,recv_len,0))<=0)
     		{
			closesocket(iSocket);
			return;
		}
	//等待主机返回报文
		memset(pstr,0,sizeof(pstr));
		if((recv_len = recv(iSocket,pstr,8019,0)) < 0)
		{
	       		closesocket(iSocket);
			return ;
		}	
		closesocket(iSocket);
	//获取结果
		TTermIOData *rs=(TTermIOData*)pstr;
		if(rs->result==0x00)
			m_hexRes="CG";
		else
			m_hexRes="SB";
	UpdateData(FALSE);
}

void CTerminalSimulatorDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CTerminalSimulatorDlg::OnSelchangeTranstype() 
{
	// TODO: Add your control notification handler code here
	termIOData.mti = m_cbxTransType.GetCurSel ();
}

void CTerminalSimulatorDlg::HexToAsc(CString hex,unsigned char *asc)
{
	int iLen=hex.GetLength ();
	char pstr[1204];
	memset(pstr,0,sizeof(pstr));
	memcpy(pstr,hex,iLen);
	unsigned char t;
	for(int i=0,j=0;i<iLen;i+=2)
	{
		sscanf(pstr+i,"%02X",&t);
		memset(asc+j,t,1);
		j++;
	}
}

void CTerminalSimulatorDlg::OnChangeAmount() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();

}
