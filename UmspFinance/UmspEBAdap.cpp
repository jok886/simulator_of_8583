// UmspEBAdap.cpp: implementation of the CUmspEBAdap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "UmspEBAdap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmspEBAdap::CUmspEBAdap()
{
	memset(EBHostIP,0,sizeof(EBHostIP));

	CWinApp *pApp=AfxGetApp();
	CString ip=pApp->GetProfileString("EB","IP","127.0.0.1");
	memcpy(EBHostIP,ip,ip.GetLength ());
	EBHostPort=pApp->GetProfileInt ("EB","PORT",5819);


}

CUmspEBAdap::~CUmspEBAdap()
{
	CWinApp *pApp=AfxGetApp();
	pApp->WriteProfileString( "EB","IP",EBHostIP);
	pApp->WriteProfileInt ("EB","PORT",EBHostPort);
}

int CUmspEBAdap::TransWork()
{	
	//�������
		char pstr[MSG_MAX_LEN];
		int	recv_len;
		//int i,flag;
		//TRS_TBL	curTrs;
		int iSocket,cliSockfd;
		int optval;
		struct 	sockaddr_in serv_addr;	//�������˵�ַ
		int iMsgLen;
	//��ʼ��Ӧ�û���
		memset(pstr,0,sizeof(pstr));
	//���ռ����̻߳�ȡ���ն˽�����׽���
		::EnterCriticalSection (&sm_cs);
		/*	flag=0;
			for(i=0;i<curTrsTbl.GetCount ();i++)
			{
				curTrs=curTrsTbl.GetAt (curTrsTbl.FindIndex (i));
				if(curTrs.dwThreadID ==::GetCurrentThreadId ())
				{
					cliSockfd=curTrs.cliSocket;
					flag=1;
				}
				break;
			}
			if(flag==0)
			{
				::LeaveCriticalSection (&sm_cs);
				AfxMessageBox("Cannot Find Suiltable Socket to use!");
				MessageBox(NULL,"Err MSg","Cannot Find Suiltable Socket to use!",MB_OK);
				return -1;
			}
			cliSockfd=igSockfd;*/
			
			cliSockfd=csTbl.RemoveHead ();
		::LeaveCriticalSection (&sm_cs);
	//�����ն˷���Ľ���������		
		recv_len=recv(cliSockfd,pstr,MSG_MAX_LEN,0);
		if (recv_len <= 0)
		{
			//umspDebug( "��SOCKET�������ݴ�len=[%d] errno=[%d]", recv_len, errno );
			//alarm( 0 );
			CString msgStr;
			msgStr.Format ("Read Client Socket Error:[%03d]",cliSockfd);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			return -1;
		}
	//���������ķ��������������Ľ��������ĵĹ������ȴ�������....
		CUmspEBTrans curTrans;		
		curTrans.TrsEBMgr (0,pstr,recv_len);
		//msg.Generate (pstr,0,"2000000001800008");
	//��������ͨѶ��������������
		if ((iSocket= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			//msg.Format ("�����׽���ʧ�ܣ�");
			//inData->logList.AddHead(msg);
			//SendMessage(inData->hWnd ,F,NULL,NULL);
			CString msgStr;
			msgStr.Format ("Create Host socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			return -1;
		}
		optval=30;
		if(setsockopt(iSocket, SOL_SOCKET, SO_SNDTIMEO, (char *) &optval, sizeof(optval)) < 0)
		{
			//msg.Format ("set socket error : ");
			CString msgStr;
			msgStr.Format ("Set Host socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			closesocket(iSocket);
			return -1;
		}
		memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = inet_addr(EBHostIP);
		serv_addr.sin_port = htons(EBHostPort);
		if (connect(iSocket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		{
			//msg.Format ("�ͶԵȶ˽������ӳ���");
			CString msgStr;
			msgStr.Format ("Connet Host socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			closesocket(iSocket);
			return -1;
		}		
		if((iMsgLen = send(iSocket,pstr,recv_len,0))<=0)
     		{
			CString msgStr;
			msgStr.Format ("Send Host socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			closesocket(iSocket);
			return -1;
		}
	//�ȴ��������ر���
		memset(pstr,0,sizeof(pstr));
		iMsgLen=MSG_MAX_LEN;
		if((iMsgLen = recv(iSocket,pstr,iMsgLen,0)) < 0)
		{
	       		CString msgStr;
			msgStr.Format ("Receive Host socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
	       		closesocket(iSocket);
			return -1;
		}	
		closesocket(iSocket);
	//�����������ر���,�����ն���Ӧ����
		curTrans.TrsEBMgr (1,pstr,iMsgLen);
	//��Ӧ�ն�
		recv_len=send(cliSockfd,pstr,iMsgLen,0);
		if (recv_len <= 0)
		{
			CString msgStr;
			msgStr.Format ("Response Client socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			return -1;
		}
	//�˳������߳�
		ShutCliCosket(cliSockfd);
		return 1;
}

void CUmspEBAdap::ShutCliCosket(int s)
{
	DWORD dw=::GetCurrentThreadId ();
	::PostThreadMessage (ctlThread->m_nThreadID ,MSG_TRS_THREAD_END,dw,dw);
	closesocket(s);
	shutdown(s,2);
}
