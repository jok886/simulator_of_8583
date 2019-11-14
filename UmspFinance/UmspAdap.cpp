//////////////////////////////////////////////////////////////////////
// UmspAdap.cpp: implementation of the CUmspAdap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "UmspAdap.h"
#include "commonhead.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CRITICAL_SECTION CUmspAdap::sm_cs;

CUmspAdap::CUmspAdap()
{
	InitEnv();
}

CUmspAdap::~CUmspAdap()
{
	CleanEnv();
	
}
/*监控线程所执行的动作*/
UINT CUmspAdap::ControlThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->ControlWork ();
	return 1;
}
/*交易监听线程所执行的动作*/
UINT CUmspAdap::ListenThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->ListenWork ();
	return 1;
}
/*交易工作线程所执行的动作*/
UINT CUmspAdap::TransThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->TransWork ();
	//交易结束...
	return 1;
}
/*启动监控管理线程，用于并发数的控制*/
CWinThread * CUmspAdap::StartControl()
{
	return AfxBeginThread(CUmspAdap::ControlThread, (LPVOID)this);
}
/*启动交易监听线程，整个服务的开关，负责启动其他的服务线程*/
CWinThread * CUmspAdap::StartListen()
{
	ctlThread=StartControl();
	if(ctlThread!=NULL)
		 lsnThread=AfxBeginThread(CUmspAdap::ListenThread, (LPVOID)this);
	return lsnThread;
}
/*启动交易工作线程，负责交易的事务性处理和相关工作，由交易监听线程启动*/
CWinThread * CUmspAdap::StartTrans()
{
	//return AfxBeginThread(CUmspAdap::TransThread, (LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);	
	return AfxBeginThread(CUmspAdap::TransThread, (LPVOID)this);	
}
/*在创建应用之初，初始化运行环境*/
void CUmspAdap::InitEnv()
{
	trsMaxCount = 30;
	trsCurCount = 0;

	ctlThread=NULL;
	lsnThread=NULL;
	::InitializeCriticalSection (&sm_cs);

	
}

int CUmspAdap::ListenWork()
{
	//定义使用变量
		struct 	sockaddr_in cli_addr;	//客户端地址
		struct 	sockaddr_in serv_addr;	//服务器端地址
		char	alCliIp[20];		
		int	ilAddrlen;		
		SOCKET	ilSockfd;		//监听套接字
		int	optval, optlen;		//套接字属性设置1
		struct linger	linopt;		//2
		char	**addrs;
		struct hostent	*hp;
		int	port;	//监听端口
	//读取环境变量，初始化变量
		port=5566;

		memset ((char *)&cli_addr, 0x00, sizeof(struct sockaddr_in) );
		memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );

		/**********Socket通讯地址初始化********************/
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);
	/*
		监听，如果有交易进来且当前并发进程数目小于最大允许并发线程数目，
		就启动交易线程读取交易报文，分析整合然后开始交易。
	*/
CONNET_AGAIN:
	//建立监听套接字
		ilSockfd= socket(PF_INET, SOCK_STREAM, 0);
		if (ilSockfd == -1)
		{
			//umspDebug("创建SOCKET错误!Retcode=[%d] errno=[%d]\n",ilSockfd,errno);
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}
	//设置套接字属性
		optlen = sizeof( optval ) ;
		optval = 1;
		if(setsockopt(ilSockfd, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)) < 0)
		{
			//umspDebug("set socket error! errno=[%d]", errno );
			closesocket(ilSockfd);
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}
		linopt.l_onoff = 1;
		linopt.l_linger = 0;
		if(setsockopt(ilSockfd, SOL_SOCKET, SO_LINGER, (LPSTR ) &linopt, sizeof(linopt)) < 0)
		{
			//umspDebug("set socket error! errno=[%d]", errno );
			closesocket(ilSockfd);
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}
	//绑定套接字，并开始监听
		if ( bind(ilSockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr) ) == -1)
		{
			//umspDebug("bind socket error! errno=[%d]", errno );
			closesocket( ilSockfd );
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}

		if (listen(ilSockfd,5) == -1)
		{
			//umspDebug(" listen error! errno=[%d]", errno );
			closesocket (ilSockfd);
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}
	//大循环，如果有连接进入就启动交易线程开始工作，否则循环
	while(1)
	{	
		//等待连接
 			ilAddrlen = sizeof(struct sockaddr_in);
			//::EnterCriticalSection (&sm_cs);
				igSockfd  = accept(ilSockfd,(struct sockaddr*)&cli_addr, &ilAddrlen);
				if ( igSockfd == -1)
				{
					//umspDebug(" accept error! Retcode=[%d] error=[%d]",igSockfd, errno);
					//sleep(SLEEP_SECONDS);
					continue;
				}
			//::LeaveCriticalSection (&sm_cs);
		//获取接入主机的IP地址，用于控制终端的进入
			hp = gethostbyaddr( (char *) &cli_addr.sin_addr, sizeof(struct in_addr),cli_addr.sin_family);
			addrs = hp->h_addr_list;
			strcpy( alCliIp, inet_ntoa(*(struct in_addr *)&cli_addr.sin_addr));
		//检查当前并发交易线程数，如果小于允许数，则启动交易线程
			//StartTrans();
			//StartControl();
			::PostThreadMessage (ctlThread->m_nThreadID ,MSG_START_TRANS,igSockfd,igSockfd);
			
	}	
	//结束...
	return 1;
}
int CUmspAdap::ControlWork()
{
	CWinThread *trsThread;
/*	if(trsCurCount<trsMaxCount)
		trsThread=StartTrans ();
	if(trsThread!=NULL)
	{
		trsCurCount++;
		DWORD dw=WaitForSingleObject(trsThread->m_hThread ,INFINITE);
		switch(dw)
		{
		case WAIT_TIMEOUT:
			trsThread->ExitInstance ();
			trsCurCount--;
			break;
		case WAIT_OBJECT_0:
			trsCurCount--;
			break;
		case WAIT_ABANDONED:
			trsCurCount--;
			break;
		default:
			break;
		}
	}
	return 1;*/
	
	TRS_TBL	curTrs;
	int i;
	MSG msg;
	while(::GetMessage (&msg,NULL,0,0)>0)
	{
		switch(msg.message )
		{
		case MSG_START_TRANS:
			if(trsCurCount<trsMaxCount)
			{	
				curTrs.cliSocket =msg.wParam ;
				csTbl.AddHead (curTrs.cliSocket);
				trsThread=StartTrans ();
				if(trsThread!=NULL)
				{
					curTrs.cliSocket =msg.wParam ;
					curTrs.dwThreadID =trsThread->m_nThreadID ;
					curTrsTbl.AddHead (curTrs);
					trsCurCount++;
					//trsThread->ResumeThread ();
				}
			}
			else
			{//超过最大连接数，关掉套接字
				closesocket(igSockfd);
			}
			break;
		case MSG_TRS_THREAD_END:
			for(i=0;i<curTrsTbl.GetCount ();i++)
			{
				curTrs=curTrsTbl.GetAt (curTrsTbl.FindIndex (i));
				if(curTrs.dwThreadID ==msg.wParam )
				{
					curTrsTbl.RemoveAt (curTrsTbl.FindIndex (i));
					trsCurCount--;
				}
			}
			break;
		case MSG_END_ALL_TRANS:
			//停掉所有进程
			while (!curTrsTbl.IsEmpty())
			{
				curTrs=curTrsTbl.RemoveHead ();
				::PostThreadMessage (curTrs.dwThreadID ,WM_QUIT,0,0);
				trsCurCount--;
			}
			::PostQuitMessage (6819);
			break;
		default:
			break;
		}
	}
	return 1;

}

void CUmspAdap::CleanEnv()
{
	//::TerminateThread (lsnThread->m_hThread ,9999);
	if(lsnThread!=NULL)
		::PostThreadMessage(lsnThread->m_nThreadID ,WM_QUIT,0,0);
	if(ctlThread!=NULL)
		::PostThreadMessage (ctlThread->m_nThreadID ,MSG_END_ALL_TRANS,0,0);

}

void CUmspAdap::StopListen()
{
	CleanEnv();
/*	DWORD dw=WaitForSingleObject(lsnThread->m_hThread ,20);
	switch(dw)
	{
	case WAIT_TIMEOUT:
		::TerminateThread (lsnThread->m_hThread,6819);
		break;
	case WAIT_OBJECT_0:
		break;
	case WAIT_ABANDONED:
		break;
	default:
		break;
	}*/
}
