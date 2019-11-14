// CommandDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rs232tcpadaptor.h"
#include "CommandDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg dialog


CCommandDlg::CCommandDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommandDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommandDlg)
	m_strCommand = _T("");
	m_strRespond = _T("");
	//}}AFX_DATA_INIT
	is=0;
	ic=0;
}


void CCommandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommandDlg)
	DDX_Control(pDX, IDC_LIST1, m_lstResult);
	DDX_Text(pDX, IDC_COMMAND, m_strCommand);
	DDX_Text(pDX, IDC_RESPOND, m_strRespond);
	DDX_Control(pDX, IDC_MSCOMM3, m_Comm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommandDlg, CDialog)
	//{{AFX_MSG_MAP(CCommandDlg)
	ON_BN_CLICKED(BTN_ADD, OnAddCommand)
	ON_BN_CLICKED(BTN_SEND, OnSendCommand)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommandDlg message handlers

BEGIN_EVENTSINK_MAP(CCommandDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CCommandDlg)
	ON_EVENT(CCommandDlg, IDC_MSCOMM3, 1 /* OnComm */, OnOnCommMscomm3, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CCommandDlg::OnOnCommMscomm3() 
{
	VARIANT variant_inp;
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; 
    CString strtemp;
    if(m_Comm.GetCommEvent()==2 && ic==0) //事件值为2表示接收缓冲区内有字符
    {             ////////以下你可以根据自己的通信协议加入处理代码
		//Sleep(1000);
		int i=0;
		i=m_Comm.GetInBufferCount ();
      	variant_inp=m_Comm.GetInput(); //读缓冲区
        safearray_inp=(COleSafeArray)variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
        len=safearray_inp.GetOneDimSize(); //得到有效数据长度
        for(k=0;k<len;k++)
            safearray_inp.GetElement(&k,rxdata+k);//转换为BYTE型数组
        for(k=0;k<len;k++) //将数组转换为Cstring型变量
        {
            BYTE bt=*(char*)(rxdata+k); //字符型
            strtemp.Format("%02X",bt); //将字符送入临时变量strtemp存放
		m_strRespond+=strtemp;
        }
	if(CheckMsgFormat(m_strRespond))
	{	
		m_lstResult.SetItemText (is,2,m_strRespond);
		is++;
		SendCommand();
		UpdateData(FALSE); //更新编辑框内容			
	}
    }
	
}

BOOL CCommandDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_lstResult.SetExtendedStyle
   (m_lstResult.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
		
		m_lstResult.InsertColumn (0,"序号",LVCFMT_CENTER,20);
		m_lstResult.InsertColumn (1,"命令",LVCFMT_CENTER,300);
		m_lstResult.InsertColumn (2,"响应",LVCFMT_LEFT,350);



			if(m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(FALSE);

		m_Comm.SetCommPort(1); //选择com1
		if( !m_Comm.GetPortOpen())
			m_Comm.SetPortOpen(TRUE);//打开串口
		else
			AfxMessageBox("cannot open serial port");

		m_Comm.SetSettings("9600,n,8,1"); //波特率9600，无校验，8个数据位，1个停止位 

		m_Comm.SetInputMode (1); //1：表示以二进制方式检取数据
		m_Comm.SetRThreshold(1); 
		//参数1表示每当串口接收缓冲区中有多于或等于1个字符时将引发一个接收数据的OnComm事件
		m_Comm.SetInputLen(0); //设置当前接收区数据长度为0
		m_Comm.GetInput();//先预读缓冲区以清除残留数据
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CCommandDlg::OnAddCommand() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	int idx=m_lstResult.GetItemCount ();
	CString title;title.Format ("%d",idx);
	m_lstResult.InsertItem (idx,title);
	m_lstResult.SetItemText (idx,1,m_strCommand);
}

void CCommandDlg::OnSendCommand() 
{
	// TODO: Add your control notification handler code here
	is=0;ic=1;
		m_Comm.GetInput();//先预读缓冲区以清除残留数据
		m_Comm.GetInput();//先预读缓冲区以清除残留数据
		ic=0;
	SendCommand();
}

void CCommandDlg::SendCommand()
{
	//i
	CString s;
	if(is>=m_lstResult.GetItemCount ())
		return;
	s=m_lstResult.GetItemText (is,1);
	CByteArray hexdata;
	int len=String2Hex(s,hexdata); 
	m_lstResult.SetSelectionMark (is);
	m_strRespond.Empty ();
	m_Comm.SetOutput(COleVariant(hexdata));
}
int CCommandDlg::String2Hex(CString str, CByteArray &senddata)
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

char CCommandDlg::ConvertHexChar(char ch)
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
BOOL CCommandDlg::CheckMsgFormat(CString msg)
{
/*	CString s,l,content,e,c;
	int len;
	if (msg.IsEmpty ())
		return FALSE;
	len=msg.GetAt(0);
	if(msg.GetLength ()!=len)
		return FALSE;
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
	if (msg.Right (2)!="0D")
		return FALSE;*/
	return TRUE;
}

void CCommandDlg::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos=
		m_lstResult.GetFirstSelectedItemPosition ();
	int idx=
		m_lstResult.GetNextSelectedItem (pos);
	m_strCommand= (m_lstResult.GetItemText (idx,1));
	m_strRespond= (m_lstResult.GetItemText (idx,2));
	UpdateData(FALSE);
	*pResult = 0;
}
