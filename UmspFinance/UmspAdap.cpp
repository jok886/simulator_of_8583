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
/*����߳���ִ�еĶ���*/
UINT CUmspAdap::ControlThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->ControlWork ();
	return 1;
}
/*���׼����߳���ִ�еĶ���*/
UINT CUmspAdap::ListenThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->ListenWork ();
	return 1;
}
/*���׹����߳���ִ�еĶ���*/
UINT CUmspAdap::TransThread(LPVOID pData)
{
	CUmspAdap *me=(CUmspAdap *)pData;
	me->TransWork ();
	//���׽���...
	return 1;
}
/*������ع����̣߳����ڲ������Ŀ���*/
CWinThread * CUmspAdap::StartControl()
{
	return AfxBeginThread(CUmspAdap::ControlThread, (LPVOID)this);
}
/*�������׼����̣߳���������Ŀ��أ��������������ķ����߳�*/
CWinThread * CUmspAdap::StartListen()
{
	ctlThread=StartControl();
	if(ctlThread!=NULL)
		 lsnThread=AfxBeginThread(CUmspAdap::ListenThread, (LPVOID)this);
	return lsnThread;
}
/*�������׹����̣߳������׵������Դ������ع������ɽ��׼����߳�����*/
CWinThread * CUmspAdap::StartTrans()
{
	//return AfxBeginThread(CUmspAdap::TransThread, (LPVOID)this,THREAD_PRIORITY_NORMAL,0,CREATE_SUSPENDED);	
	return AfxBeginThread(CUmspAdap::TransThread, (LPVOID)this);	
}
/*�ڴ���Ӧ��֮������ʼ�����л���*/
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
	//����ʹ�ñ���
		struct 	sockaddr_in cli_addr;	//�ͻ��˵�ַ
		struct 	sockaddr_in serv_addr;	//�������˵�ַ
		char	alCliIp[20];		
		int	ilAddrlen;		
		SOCKET	ilSockfd;		//�����׽���
		int	optval, optlen;		//�׽�����������1
		struct linger	linopt;		//2
		char	**addrs;
		struct hostent	*hp;
		int	port;	//�����˿�
	//��ȡ������������ʼ������
		port=5566;

		memset ((char *)&cli_addr, 0x00, sizeof(struct sockaddr_in) );
		memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );

		/**********SocketͨѶ��ַ��ʼ��********************/
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		serv_addr.sin_port = htons(port);
	/*
		����������н��׽����ҵ�ǰ����������ĿС������������߳���Ŀ��
		�����������̶߳�ȡ���ױ��ģ���������Ȼ��ʼ���ס�
	*/
CONNET_AGAIN:
	//���������׽���
		ilSockfd= socket(PF_INET, SOCK_STREAM, 0);
		if (ilSockfd == -1)
		{
			//umspDebug("����SOCKET����!Retcode=[%d] errno=[%d]\n",ilSockfd,errno);
			//sleep(SLEEP_SECONDS);
			goto  CONNET_AGAIN;
		}
	//�����׽�������
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
	//���׽��֣�����ʼ����
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
	//��ѭ������������ӽ�������������߳̿�ʼ����������ѭ��
	while(1)
	{	
		//�ȴ�����
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
		//��ȡ����������IP��ַ�����ڿ����ն˵Ľ���
			hp = gethostbyaddr( (char *) &cli_addr.sin_addr, sizeof(struct in_addr),cli_addr.sin_family);
			addrs = hp->h_addr_list;
			strcpy( alCliIp, inet_ntoa(*(struct in_addr *)&cli_addr.sin_addr));
		//��鵱ǰ���������߳��������С���������������������߳�
			//StartTrans();
			//StartControl();
			::PostThreadMessage (ctlThread->m_nThreadID ,MSG_START_TRANS,igSockfd,igSockfd);
			
	}	
	//����...
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
			{//����������������ص��׽���
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
			//ͣ�����н���
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
