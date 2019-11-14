// SockConn.cpp: implementation of the CSockConn class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "SockConn.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSockConn::CSockConn()
{
	status=0;	/*不可用*/
	sockfd=-1;
	memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in));
	timeval.tv_sec=2;
	timeval.tv_usec=0;
}
CSockConn::~CSockConn()
{
	if(sockfd>0)
		closesocket(sockfd);
}
int CSockConn::TCPConnect(const char *hostip,short hostport)
{	
	/*建立套接字*/
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		return SOCK_CREATE_ERROR;
	}
	/*指定服务器IP地址和端口*/
	memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
 	serv_addr.sin_family = AF_INET;
 	/*if(inet_pton(AF_INET,hostip,&serv_addr.sin_addr)<=0)
 		return SOCK_INVALID_IP;replaced by the line above*/
 	serv_addr.sin_addr.s_addr = inet_addr(hostip);
 	serv_addr.sin_port = htons(hostport);
 	/*建立连接*/
 	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
  	{
         	return SOCK_CONNECT_ERROR;
  	}
  	/*if(setsockopt(sockfd,SOL_SOCKET,SO_RCVTIMEO,&timeval,sizeof(timeval))<0)
  		return SOCK_SETOPT_ERROR;
  	if(setsockopt(sockfd,SOL_SOCKET,SO_SNDTIMEO,&timeval,sizeof(timeval))<0)
  		return SOCK_SETOPT_ERROR;*/
  	status=1;/*已连接*/
	return 0;
}
int CSockConn::TCPSendData(const char *sndbuf,int &sndlen)
{
	int ret;
	if(sockfd<0)
	{
		return SOCK_CREATE_ERROR;
	}
	if(status<1)
		return SOCK_CONNECT_ERROR;
	if((ret=send(sockfd,sndbuf,sndlen,0))<0)
	{
		return SOCK_SEND_ERROR;	
	}
	sndlen=ret;
	return 0;
}
int CSockConn::TCPReadData(char *rcvbuf,int &rcvlen)
{
	int ret;
	if(sockfd<0)
	{
		return SOCK_CREATE_ERROR;
	}
	if(status<1)
		return SOCK_CONNECT_ERROR;
	if((ret=recv(sockfd,rcvbuf,rcvlen,0))<0)
	{
		return SOCK_READ_ERROR;
	}
	rcvlen=ret;
	return 0;
}
//DEL int CSockConn::TCPBind(short lsnport)
//DEL {
//DEL 	int  optval, optlen;
//DEL 	status=0;
//DEL 	/*建立套接字*/
//DEL 	sockfd=socket(AF_INET, SOCK_STREAM, 0);
//DEL 	if(sockfd<0)
//DEL 	{
//DEL 		return SOCK_CREATE_ERROR;
//DEL 	}
//DEL 	/*指定服务器IP地址和端口*/
//DEL 	serv_addr.sin_family = AF_INET;
//DEL 	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
//DEL 	serv_addr.sin_port = htons(lsnport);
//DEL 	
//DEL 	optlen = sizeof( optval ) ;
//DEL 	optval = 1;
//DEL 	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *) &optval, sizeof(optval)) < 0)
//DEL 	{
//DEL 		return SOCK_SETOPT_ERROR;
//DEL 	}
//DEL 	if ( bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr) ) == -1)
//DEL 	{
//DEL 		return SOCK_BIND_ERROR;
//DEL 	}
//DEL 
//DEL 	if (listen(sockfd,5) == -1)
//DEL 	{
//DEL 		return SOCK_LISTEN_ERROR;
//DEL 	}
//DEL 	status=1;
//DEL 	return 0;
//DEL }

//DEL int CSockConn::TCPWaitConnect(struct sockaddr* cli_addr, socklen_t *len)
//DEL {
//DEL 	int insockfd;
//DEL 	if(status<1)
//DEL 		return SOCK_CONNECT_ERROR;
//DEL 	insockfd=accept(sockfd,cli_addr, len);
//DEL 	if ( insockfd == -1)
//DEL 	{
//DEL 		return -1;
//DEL 	}
//DEL 	return insockfd;
//DEL }

void CSockConn::TCPClose()
{
	if(sockfd>0)
	{
		closesocket(sockfd);
	}
}
