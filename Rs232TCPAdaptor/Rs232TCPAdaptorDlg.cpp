// Rs232TCPAdaptorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Rs232TCPAdaptor.h"
#include "Rs232TCPAdaptorDlg.h"

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
// CRs232TCPAdaptorDlg dialog

CRs232TCPAdaptorDlg::CRs232TCPAdaptorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRs232TCPAdaptorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRs232TCPAdaptorDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bInitDlg=TRUE;
	this->strSvrIp ="127.0.0.1";
	this->iSvrPort =5819;
	this->dlg =NULL;if(dlg==NULL)
	{
		dlg= new CMsgViewerDlg;
		dlg->Create (DLG_VIEW_MSG);
	}
	iMsgType=4;
	iRoute=1;
	iThreadCount=0;
}

void CRs232TCPAdaptorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRs232TCPAdaptorDlg)
	DDX_Control(pDX, IDC_EDIT1, m_edt);
	DDX_Control(pDX, IDC_LIST1, m_lstComm);
	DDX_Control(pDX, IDC_MSCOMM3, m_comm);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRs232TCPAdaptorDlg, CDialog)
	//{{AFX_MSG_MAP(CRs232TCPAdaptorDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(MENU_OPEN, OnOpen)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_COMMAND(MENU_CLOSE, OnClose)
	ON_COMMAND(MNU_OPEN2, OnOpen2)
	ON_COMMAND(MENU_OPTION, OnOption)
	ON_COMMAND(MNU_DEBUGSeRIAL, OnDEBUGSeRIAL)
	ON_COMMAND(MNU_ANLYSIS, OnAnlysisBITMAP)
	ON_COMMAND(MENU_TOFILE, OnTofile)
	ON_COMMAND(menu_des, Ondes)
	ON_COMMAND(MENU_SEND_NULL, OnSendNull)
	ON_WM_SHOWWINDOW()
	ON_WM_LBUTTONDOWN()
	ON_WM_CANCELMODE()
	ON_WM_CAPTURECHANGED()
	ON_COMMAND(MENU_OPEN4, OnOpen4)
	ON_COMMAND(MENU_THREAD_TEST, OnThreadTest)
	//}}AFX_MSG_MAP
	ON_MESSAGE(BEGIN_TRANS,OnBeginTrans)
	ON_MESSAGE(AFTER_TRANS_END,OnAfterTransEnd)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRs232TCPAdaptorDlg message handlers

BOOL CRs232TCPAdaptorDlg::OnInitDialog()
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
	//初始化串口

	//初始化列表控件和编辑控件
		CRect rc;
		this->GetWindowRect (&rc);
		m_edt.MoveWindow (0,0,rc.Width()-10,50);
		m_lstComm.MoveWindow (0,60,rc.Width (),rc.Height ()-80);
		bInitDlg=FALSE;
		m_lstComm.SetExtendedStyle
   (m_lstComm.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	
		m_lstComm.InsertColumn (0,"发起端",LVCFMT_CENTER,50);
		m_lstComm.InsertColumn (1,"顺序号",LVCFMT_CENTER,80);
		m_lstComm.InsertColumn (2,"报文内容",LVCFMT_LEFT,350);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRs232TCPAdaptorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRs232TCPAdaptorDlg::OnPaint() 
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
HCURSOR CRs232TCPAdaptorDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CRs232TCPAdaptorDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(!bInitDlg)
	{
		m_edt.MoveWindow (0,0,cx,50);
		m_lstComm.MoveWindow (0,60,cx,cy-60);
	}
}

BEGIN_EVENTSINK_MAP(CRs232TCPAdaptorDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CRs232TCPAdaptorDlg)
	ON_EVENT(CRs232TCPAdaptorDlg, IDC_MSCOMM3, 1 /* OnComm */, OnCommMscomm3, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CRs232TCPAdaptorDlg::OnCommMscomm3() 
{
	// TODO: Add your control notification handler code here
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
    CString strtemp;
    if(m_comm.GetCommEvent()==2) //事件值为2表示接收缓冲区内有字符
    {             ////////以下你可以根据自己的通信协议加入处理代码
		//Sleep(1000);
		int i=0;
		i=m_comm.GetInBufferCount ();
      	variant_inp=m_comm.GetInput(); //读缓冲区
        safearray_inp=(COleSafeArray)variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
        len=safearray_inp.GetOneDimSize(); //得到有效数据长度
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
        for(k=0;k<len;k++) //将数组转换为Cstring型变量
        {
            BYTE bt=*(char*)(rxdata+k); //字符型
            strtemp.Format("%02X",bt); //将字符送入临时变量strtemp存放
			strEdt+=strtemp;
        }
		if(CheckMsgFormat(strEdt))
		{	
			m_lstComm.InsertItem (0,"P");
			CString t;
			t.Format ("%d",m_lstComm.GetItemCount ());
			m_lstComm.SetItemText (0,1,t);
			m_lstComm.SetItemText (0,2,strEdt);
			//转发到
			SendMessage(BEGIN_TRANS);
		}
    }
	
    UpdateData(FALSE); //更新编辑框内容
}

void CRs232TCPAdaptorDlg::OnOpen() 
{
		if(m_comm.GetPortOpen())
			m_comm.SetPortOpen(FALSE);

		m_comm.SetCommPort(1); //选择com1
		if( !m_comm.GetPortOpen())
			m_comm.SetPortOpen(TRUE);//打开串口
		else
			AfxMessageBox("cannot open serial port");

		m_comm.SetSettings("9600,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 

		m_comm.SetInputMode (1); //1：表示以二进制方式检取数据
		m_comm.SetRThreshold(1); 
		//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_comm.SetInputLen(0); //设置当前接收区数据长度为0
		m_comm.GetInput();//先预读缓冲区以清除残留数据
}

void CRs232TCPAdaptorDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos=
		m_lstComm.GetFirstSelectedItemPosition ();
	int idx=
		m_lstComm.GetNextSelectedItem (pos);
	m_edt.SetWindowText (m_lstComm.GetItemText (idx,2));
	*pResult = 0;
}

BOOL CRs232TCPAdaptorDlg::CheckMsgFormat(CString msg)
{
/**/	CString s,l,content,e,c;
	int len;
	if(msg.GetLength ()<=6)
		return FALSE;
	s=msg.Left (2);
	if(s!="02")
		return FALSE;
	l=msg.Mid(2,4);
	sscanf(l,"%d",&len);
	if(msg.GetLength ()!=2*(len+5))
		return FALSE;
	e=msg.Mid (2*(len+3),2);
	if(e!="03")
		return FALSE;
	c=msg.Right (2);
	//校验码
	return TRUE;
}

UINT TransThread(LPVOID lpData)
{
	//分析入口参数
		//1、主机IP与PORT
		//2、发往主机的消息
		//3、发往串口的地址
		//4、处理完毕后的通知窗口

	struct _IO_DATA_ * ioData=(struct _IO_DATA_ *)lpData;
	
	//开始转发
	int			iMsgLen;
	int			iSocket;
	struct		sockaddr_in serv_addr;
	//上送主机
	if ((iSocket= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		AfxMessageBox("建立套接字失败");
		return 1;
	}
	int optval=10;
	if(setsockopt(iSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &optval, sizeof(optval)) < 0)
	{
		AfxMessageBox("设置套接字失败");
		return 1;
	}
	memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ioData->ip );
	serv_addr.sin_port = htons(ioData->port );
	if (connect(iSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{
		AfxMessageBox ("连接主机出错");
		return 1;
	}

	if((iMsgLen = send(iSocket,ioData->msgSnd ,ioData->lenSnd ,0))<=0)
	{
		AfxMessageBox("发送SOCKET失败");
		closesocket(iSocket);
		return 1;
	}
	//接收主机返回
	memset(ioData->msgRev,0x00,sizeof(ioData->msgRev));
	iMsgLen=1024;
	if((ioData->lenRev=recv(iSocket,ioData->msgRev,iMsgLen,0))< 0)
	{
		AfxMessageBox("接受SOCKET失败");
		closesocket(iSocket);
		return 1;	
	}	
	closesocket(iSocket);
	shutdown(iSocket,2);
	SendMessage(ioData->Wnd ,AFTER_TRANS_END,0,0);
	return 1;
}
void CRs232TCPAdaptorDlg::OnBeginTrans ()
{
	if(iRoute==3)
	{
		CString strMsg;
		strMsg=strEdt.Mid(2,strEdt.GetLength ()-6);
		strEdt.Empty ();
		memset(&ioData,0,sizeof(ioData));
		AsciiToBcd(strMsg,ioData.msgSnd,strMsg.GetLength ());
		ioData.lenSnd =strMsg.GetLength ()/2;

		ioData.Wnd =this->m_hWnd ;
		memset(ioData.ip,0,sizeof(ioData.ip ));
		strcpy(ioData.ip,this->strSvrIp );
		//ioData.ip.Format ("%s",this->strSvrIp );
		ioData.port =this->iSvrPort ;
		AfxBeginThread(TransThread,(LPVOID)(&ioData));
	}
	else
		this->OnAfterTransEnd ();
	return ;
}

void CRs232TCPAdaptorDlg::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(dlg==NULL)
	{
		dlg= new CMsgViewerDlg;
		dlg->Create (DLG_VIEW_MSG);
	}
	CString str;
	m_edt.GetWindowText (str);
	dlg->msg.ResetDigram();//ClearDigram ()
	dlg->msg.Parse (str,str.GetLength (),iMsgType);
	//memset(gen8583,0,sizeof(gen8583));
	//ilen=dlg->msg.Generate((char *)gen8583,4,"623E40808AC18411");//dlg->msg.Generate ((char *)gen8583,4);
	dlg->FillData ();
	dlg->ShowWindow (SW_NORMAL);//DoModal ();
	*pResult = 0;
}
void CRs232TCPAdaptorDlg::AsciiToBcd(const char *str, char *hex, int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        hex[i] = ((str[i * 2] <= 0x39) ? str[i * 2] - 0x30 
                                       : str[i * 2] - 0x41 + 10);
        hex[i] = hex[i] << 4;
        hex[i] += ((str[i * 2 + 1] <= 0x39) ? str[i * 2 + 1] - 0x30
                                       : str[i * 2 + 1] - 0x41 + 10);
    }
}

void CRs232TCPAdaptorDlg::BcdToAscii(const char *hex, char *str, int count)
{
   int i;
	unsigned char t;
    for(i=0;i<count;i++)
    {
		t=(hex[i]&(0xf0));
		t=t>>4;
        str[2*i]=ToHex(t );
		t=(hex[i]&(0x0f));
		str[2*i+1]=ToHex(t);		
    }
}

char CRs232TCPAdaptorDlg::ToHex(char c)
{
	char tmp1=c;
	if(tmp1<=9 && tmp1>=0)
		tmp1+='0';
	else if(tmp1<=15 && tmp1>=10)
		tmp1+='A'-10;
	else
		tmp1='0';
	return tmp1;
}

void CRs232TCPAdaptorDlg::Sta360(CByteArray &buf, CByteArray &res)
{
	BYTE	/*bcdl[2],*/jym;
	res.Add (0x02);
	int len=buf.GetSize ();
/*	bcdl[0]=((len/100)/10)*16+((len/100)%10);
	bcdl[1]=((len%100)/10)*16+((len%100)%10);
	res.Add (bcdl[0]);
	res.Add (bcdl[1]);
	jym=bcdl[0]^bcdl[1];*/
	jym=0;
	for(int i=0;i<len;i++) 
	{
		res.Add(buf.GetAt (i));
		jym ^= buf.GetAt (i);
	}
	res.Add(0x03);
	jym ^= 0x03;
	res.Add(jym);
	res.SetSize (len+3);
}

int CRs232TCPAdaptorDlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata,lowhexdata;
	int hexdatalen=0;
	int len=str.GetLength();
	if (len%2 ==1)
	{
		str+="0";len++;
	}
	senddata.SetSize(len/2);
	for(int i=0;i<len;i+=2)
	{
		char lstr=str[i+1],hstr=str[i];
		hexdata=ConvertHexChar(hstr);
		lowhexdata=ConvertHexChar(lstr);
		hexdata=hexdata*16+lowhexdata;
		senddata[hexdatalen]=(char)hexdata;
		hexdatalen++;
	}
	return hexdatalen;
}

char CRs232TCPAdaptorDlg::ConvertHexChar(char ch)
{
	if((ch>='0')&&(ch<='9'))
		return ch-0x30;
	else if((ch>='A')&&(ch<='F'))
		return ch-'A'+10;
	else if((ch>='a')&&(ch<='f'))
		return ch-'a'+10;
	else 
		return (0);
}

void CRs232TCPAdaptorDlg::OnClose() 
{
		if(m_comm.GetPortOpen())
			m_comm.SetPortOpen(FALSE);

		m_comm.SetCommPort(1); //选择com1
		if(m_comm.GetPortOpen())
			m_comm.SetPortOpen(FALSE);//打开串口
		m_comm.SetCommPort(2); //选择com1
		if(m_comm.GetPortOpen())
			m_comm.SetPortOpen(FALSE);//打开串口
}
void CRs232TCPAdaptorDlg::OnAfterTransEnd ()
{
	char msgRev1[2048];
	CByteArray hexdata,resdata;
	memset(msgRev1,0,2048);
	if(iRoute==3)//接收主机返回
	{
		BcdToAscii(ioData.msgRev ,msgRev1,ioData.lenRev );
		m_lstComm.InsertItem (0,"H");
		CString t;t.Format ("%d",m_lstComm.GetItemCount ());
		m_lstComm.SetItemText (0,1,t);
		m_lstComm.SetItemText (0,2,msgRev1);
		String2Hex(msgRev1,hexdata); 
	}
	else if(iRoute==1)//原报文返回
	{
		strcpy(msgRev1,strEdt);
		strEdt.Empty ();
		m_lstComm.InsertItem (0,"H");
		CString t;t.Format ("%d",m_lstComm.GetItemCount ());
		m_lstComm.SetItemText (0,1,t);
		m_lstComm.SetItemText (0,2,msgRev1);
		String2Hex(msgRev1,hexdata); 
	}
	else if(iRoute==2)//自主返回
	{	
		//dlg->msg.SetBitmap (,16);CString str;
		CString str;
		str=strEdt;
		strEdt.Empty ();
		memset(gen8583,0,sizeof(gen8583));
		dlg->msg.ResetDigram();//ClearDigram ()
		int len=dlg->msg.ReplyGenerate (str,str.GetLength (),iMsgType,(char *)gen8583);
		CByteArray ba;
		memcpy(msgRev1,"02",2);
		BcdToAscii((const char *)gen8583,msgRev1+2,len);
		memcpy(msgRev1+2+2*len,"03EF",4);
		m_lstComm.InsertItem (0,"H");
		CString t;
		t.Format ("%d",m_lstComm.GetItemCount ());
		m_lstComm.SetItemText (0,1,t);
		//m_lstComm.SetItemText (0,2,msgRev1);
		for( int i=0;i<len;i++)
			ba.Add (gen8583[i]);
		this->Sta360 (ba,hexdata);
		{
			memset(msgRev1,0,sizeof(msgRev1));
			int len=hexdata.GetSize ();
			for(int i=0;i<len;i++) 
			{
				sprintf(msgRev1+2*i,"%02X",hexdata.GetAt (i));
			}			
			m_lstComm.SetItemText (0,2,msgRev1);
		}
	}
	//返回给POS机
	m_comm.SetOutput(COleVariant(hexdata));
	UpdateData(FALSE);
}



void CRs232TCPAdaptorDlg::OnOpen2() 
{
	if(m_comm.GetPortOpen())
		m_comm.SetPortOpen(FALSE);

	m_comm.SetCommPort(2); //选择com2
	if( !m_comm.GetPortOpen())
		m_comm.SetPortOpen(TRUE);//打开串口
	else
		AfxMessageBox("cannot open serial port");

	m_comm.SetSettings("9600,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 

	m_comm.SetInputMode (1); //1：表示以二进制方式检取数据
	m_comm.SetRThreshold(1); 
	//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_comm.SetInputLen(0); //设置当前接收区数据长度为0
	m_comm.GetInput();//先预读缓冲区以清除残留数据
}

void CRs232TCPAdaptorDlg::OnOption() 
{
	// TODO: Add your command handler code here
	//int iMsgType;
	//int iROute;
	CSettingDlg dlg;
	if(dlg.DoModal ()==IDOK)
	{
		iMsgType=dlg.iMsgType ;
		iRoute=dlg.iRoute+1;
		this->strSvrIp =dlg.m_strIp ;
		this->iSvrPort =dlg.m_iPort ;
	}
	else
	{
		
	}
}

void CRs232TCPAdaptorDlg::OnDEBUGSeRIAL() 
{
	CCommandDlg comDlg;
	comDlg.DoModal ();
}
#include "AnalysisDlg.h"
void CRs232TCPAdaptorDlg::OnAnlysisBITMAP() 
{
	// TODO: Add your command handler code here
	CAnalysisDlg dlg;
	dlg.DoModal ();
}

void CRs232TCPAdaptorDlg::OnTofile() 
{
	CListCtrl *theCtrl=&m_lstComm;
	int rows=theCtrl->GetItemCount ();
	int cols=theCtrl->GetHeaderCtrl ()->GetItemCount ();
	CString tmpStr;
	CFile fp;
	CFileDialog fDlg(FALSE,"htm","MsgLog");
	if(fDlg.DoModal ()==IDCANCEL)
	{	
		return;
	}
	tmpStr=fDlg.GetFileName ();
	if(!fp.Open (tmpStr,CFile::modeCreate|CFile::modeWrite))
		return;
	CString strHead;
	strHead.Format ("<html>\n\t<head>\n\t\t<title>Transaction Message Log</title>\n\t</head>\n<body>\n\t<table border=1 >");
	fp.Write (strHead,strHead.GetLength());
	CString strRowH;
	strRowH.Format ("\n\t\t<tr>");
	for(int i=0;i<rows;i++)
	{
		fp.Write (strRowH,strRowH.GetLength ());
 		for(int j=0;j<cols;j++)
		{
			fp.Write ("<td>",4);
			tmpStr=theCtrl->GetItemText(i,j);
			fp.Write (tmpStr,tmpStr.GetLength ());
			fp.Write("</td>",5);
		}
		fp.Write ("</tr>",5);
	}
	
	CString strTail;
	strTail.Format ("\n\t</table>\n</html>");
	fp.Write (strTail,strTail.GetLength ());
	fp.Close ();
	m_lstComm.DeleteAllItems ();
}
#include "DesDlg.h"
void CRs232TCPAdaptorDlg::Ondes() 
{
	// TODO: Add your command handler code here
	CDesDlg dlg;
	dlg.DoModal();
}

void CRs232TCPAdaptorDlg::OnSendNull() 
{
	// TODO: Add your command handler code here
	CByteArray hexdata;
	hexdata.Add('0');
	m_comm.SetOutput(COleVariant(hexdata));
}

void CRs232TCPAdaptorDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
//	if(bShow)
//		OnOpen2();
//	else
//		OnClose();

}

void CRs232TCPAdaptorDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	OnOpen2();
	CDialog::OnLButtonDown(nFlags, point);
}

void CRs232TCPAdaptorDlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void CRs232TCPAdaptorDlg::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
	
	CDialog::OnCaptureChanged(pWnd);
}

void CRs232TCPAdaptorDlg::OnOpen4() 
{
	if(m_comm.GetPortOpen())
		m_comm.SetPortOpen(FALSE);

	m_comm.SetCommPort(4); //选择com2
	if( !m_comm.GetPortOpen())
		m_comm.SetPortOpen(TRUE);//打开串口
	else
		AfxMessageBox("cannot open serial port");

	m_comm.SetSettings("9600,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 

	m_comm.SetInputMode (1); //1：表示以二进制方式检取数据
	m_comm.SetRThreshold(1); 
	//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
	m_comm.SetInputLen(0); //设置当前接收区数据长度为0
	m_comm.GetInput();//先预读缓冲区以清除残留数据
}
UINT TestThread(LPVOID pData)
{
	int *i=(int *) pData;
	(*i)++;
		Sleep(INFINITE);

	return 1;
}
void CRs232TCPAdaptorDlg::OnThreadTest() 
{
	CString str;
	for(int i=0;i<5000;i++)
	{
		AfxBeginThread(TestThread,&iThreadCount,0,0,0,0);	
		str.Format ("%d",iThreadCount);
		m_edt.SetWindowText (str);
	}
}
