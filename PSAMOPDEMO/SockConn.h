// SockConn.h: interface for the CSockConn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKCONN_H__70131A46_F1E3_44BE_8F50_6357BF0B43A6__INCLUDED_)
#define AFX_SOCKCONN_H__70131A46_F1E3_44BE_8F50_6357BF0B43A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*错误码定义*/
#define SOCK_CREATE_ERROR	1
#define SOCK_CONNECT_ERROR	2
#define SOCK_SEND_ERROR		3
#define SOCK_READ_ERROR		4
#define SOCK_INVALID_IP		5
#define SOCK_SETOPT_ERROR	6
#define SOCK_BIND_ERROR		7
#define SOCK_LISTEN_ERROR	8
class CSockConn  
{
public:
	int 	status;
	int	sockfd;
	struct sockaddr_in serv_addr;
	struct timeval	timeval;
public:
	void TCPClose();
	/*客户端SOCK调用*/
	int TCPConnect(const char *hostip,short hostport);
	int TCPSendData(const char *sndbuf,int &sndlen);
	int TCPReadData(char *rcvbuf,int &rcvlen);
	/*服务器端SOCK调用*/
	
	CSockConn();
	virtual ~CSockConn();

};

#endif // !defined(AFX_SOCKCONN_H__70131A46_F1E3_44BE_8F50_6357BF0B43A6__INCLUDED_)
