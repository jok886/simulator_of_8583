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
	//定义变量
		char pstr[MSG_MAX_LEN];
		int	recv_len;
		//int i,flag;
		//TRS_TBL	curTrs;
		int iSocket,cliSockfd;
		int optval;
		struct 	sockaddr_in serv_addr;	//服务器端地址
		int iMsgLen;
	//初始化应用环境
		memset(pstr,0,sizeof(pstr));
	//接收监听线程获取的终端进入的套接字
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
	//接收终端发起的交易请求报文		
		recv_len=recv(cliSockfd,pstr,MSG_MAX_LEN,0);
		if (recv_len <= 0)
		{
			//umspDebug( "从SOCKET接收数据错len=[%d] errno=[%d]", recv_len, errno );
			//alarm( 0 );
			CString msgStr;
			msgStr.Format ("Read Client Socket Error:[%03d]",cliSockfd);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			return -1;
		}
	//进行请求报文分析和上送主机的交易请求报文的构建，等此类事情....
		CUmspEBTrans curTrans;		
		curTrans.TrsEBMgr (0,pstr,recv_len);
		//msg.Generate (pstr,0,"2000000001800008");
	//连接主机通讯，发出交易请求
		if ((iSocket= socket(AF_INET, SOCK_STREAM, 0)) < 0) 
		{
			//msg.Format ("建立套接字失败！");
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
			//msg.Format ("和对等端建立连接出错");
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
	//等待主机返回报文
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
	//分析主机返回报文,构建终端响应报文
		curTrans.TrsEBMgr (1,pstr,iMsgLen);
	//响应终端
		recv_len=send(cliSockfd,pstr,iMsgLen,0);
		if (recv_len <= 0)
		{
			CString msgStr;
			msgStr.Format ("Response Client socket Err:[%03d]",iSocket);
			MessageBox(NULL,msgStr,"Error: ",MB_OK);
			ShutCliCosket(cliSockfd);
			return -1;
		}
	//退出交易线程
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
