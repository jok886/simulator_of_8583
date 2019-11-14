// ReDirectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yy.h"
#include "ReDirectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReDirectDlg dialog


CReDirectDlg::CReDirectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReDirectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReDirectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReDirectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReDirectDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReDirectDlg, CDialog)
	//{{AFX_MSG_MAP(CReDirectDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReDirectDlg message handlers

void CReDirectDlg::OnOK() 
{
	//监听80号端口，转发IIS的监听端口808
	/**********Socket通讯地址初始化********************/
/*	CString str;
	struct		sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(80);

	int ilSockfd,igSockfd;
	ilSockfd= socket(PF_INET, SOCK_STREAM, 0);
	if (ilSockfd == -1)
	{
		str.Format("创建SOCKET错误!Retcode=[%d] errno=[%d]\n",ilSockfd,errno);
		AfxMessageBox(str);
		return;
	}
	int ilPid;
	int iRet;
	int  optval, optlen;
	optlen = sizeof( optval ) ;
	optval = 1;
	if(setsockopt(ilSockfd, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)) < 0)
	{
		str.Format("set socket error! errno=[%d]", errno );
		closesocket(ilSockfd);
		AfxMessageBox(str);
		return;
	}

	struct linger linopt;
	char  **addrs;
	struct hostent *hp;

	int i,fd;
	int proc_count;
	int proc_max;
	int cpid;
	int status;
	

	int ilAddrlen;
	
	linopt.l_onoff = 1;
	linopt.l_linger = 0;
	if(setsockopt(ilSockfd, SOL_SOCKET, SO_LINGER, (void *) &linopt, sizeof(linopt)) < 0)
	{
		str.Format("set socket error! errno=[%d]", errno );
		close(ilSockfd);
		AfxMessageBox(str);
		return;
	}
 	ilAddrlen = sizeof(struct sockaddr_in);
	if ( bind(ilSockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr) ) == -1)
	{
		str.Format("bind socket error! errno=[%d]", errno );
		close( ilSockfd );
		AfxMessageBox(str);
		return;
	}

	if (listen(ilSockfd,5) == -1)
	{
		str.Format(" listen error! errno=[%d]", errno );
		close (ilSockfd);
		AfxMessageBox(str);
		return;
	}

	struct 	sockaddr_in cli_addr;	//客户端地址
	

	while(1)
	{
		ilAddrlen = sizeof(cli_addr);
		igSockfd  = accept(ilSockfd,(struct sockaddr*)&cli_addr, &ilAddrlen);
		if ( igSockfd == -1)
		{
			str.Format(" accept error! Retcode=[%d] error=[%d]",igSockfd, errno);
			AfxMessageBox(str);
			continue;
		}
		str.Format("建立连接请求成功");
		AfxMessageBox(str);
		hp = gethostbyaddr( (char *) &cli_addr.sin_addr, sizeof(struct in_addr),cli_addr.sin_family);
		addrs = hp->h_addr_list;
		

		
		
		}
	}*/
}
/*
void CReDirectDlg::CreateLstnSocket()
{

}

void CReDirectDlg::CreateCliSocket()
{

}
*/