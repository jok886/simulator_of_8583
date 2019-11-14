// ST340.cpp: implementation of the CST340 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "ST340.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CST340::CST340(int comnum)
{
	bActive=comx.Open (comnum,9600);
	memset(request,0,sizeof(request));
	memset(response,0,sizeof(response));
}

CST340::~CST340()
{
	comx.Close ();
}
/******************************************************
命令格式:
	NAD+PCB+LEN+DATA1+CKS
   其中：
       NAD = 00H   DATA1为T=1的命令数据
       NAD = 40H   DATA1为T=0的命令数据
       NAD = 80H   DATA1为系统命令数据
 
       PCB = 49H（当NAD = 40H时）  DATA1为T = 0的输入命令
       PCB = 4FH（当NAD = 40H时）  DATA1为T = 0的输出命令

       LEN为DATA1的数据长度（以字节为单位）
       DATA1为命令内容
       CHK 为之前所有命令数据的异或和
系统命令
	CLA+INS+P1+P2+P3
	卡片上电	80+62+00+00+00
	卡片下电	80+63+00+00+00
	卡片复位	80+61+00+00+00
	检查卡片到位	80+60+00+00+00
	设置字节发送延时80+6B+N+00+00

系统命令应答：
      80 | 00 | 02 | ST1 | ST2 | CHK|   
      ST1 ST2 = 9000H  正常执行命令（或卡片到位）  
      ST1 ST2 = 7001H  卡片没有到位  
      ST1 ST2 = 7002H  非自定义命令  
      ST1 ST2 = 7003H  接收IC卡应答超时  
      ST1 ST2 = 7004H  接收PC机命令超时  
      ST1 ST2 = 700FH  未知错误  
      N = 0.1ms的整数倍
      CHK 为之前所有命令数据的异或和
******************************************************/

/*****************************************************
功能:	卡片上电.	80+62+00+00+00
参数:	
返回:		
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
int CST340::CardPowerOn()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*长度*/
	strcat(tmpcmd,"05");
	/*命令体*/
	strcat(tmpcmd,"8062000000");
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*分析命令返回*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

/*****************************************************
功能:	生成通过串口发往ST340的请求报文.
参数:	cmd	命令字串
	cmdlen	命令长度
	reqmsg	ST340请求报文[cmdlen+1]
返回:	+	reqmsg的长度
	-0	失败	
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
int CST340::GenRequestMsg(const unsigned char *cmd,int cmdlen,unsigned char * reqmsg)
{
	int i;
	memcpy(reqmsg,cmd,cmdlen);
	*(reqmsg+cmdlen)=0;
	for(i=0;i<cmdlen;i++)
	{
		*(reqmsg+cmdlen)^=*(reqmsg+i);
		//printf("%02X\n",*(reqmsg+cmdlen));
	}
	
	return (cmdlen+1);
}
/*****************************************************
功能:	检查通过串口从ST340发来的响应报文.
参数:	res	响应报文
返回:	0	有效的响应报文
	-1	无效的响应报文	
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
int CST340::CheckResponseMsg(const unsigned char *res, int reslen)
{
	int i;
	unsigned char chk=0;
	for(i=0;i<reslen-1;i++)
		chk^=*(res+i);
	if(*(res+reslen-1)==chk)
		return 0;
	return -1;
}
/*****************************************************
功能:	ST340的通讯函数，发送命令然后等待返回
参数:	cmd	十六进制字符串表示的待发送的命令
	res	十六进制字符串表示的接受到的命令响应	
返回:	0	有效的响应报文
	*	无效的响应报文	
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
int CST340::SendCommand(const char *cmd, char *res)
{
	int i,j,err;
	byte  reqmsg[MAX_BUF_SIZE],tmp[MAX_BUF_SIZE],resmsg[MAX_BUF_SIZE];

	memset(request,0,sizeof(request));
	memset(response,0,sizeof(response));

	err=0;
	i=strlen(cmd);
	CTools tls;
	tls.Bcd2ToAscii(cmd,i,0,(char *)reqmsg);
	GenRequestMsg(reqmsg,i/2,tmp);


	comx.SendData((char *)tmp,i/2+1);

	//Sleep(1000);

	byte *ttt=resmsg;
jjj:
	i=comx.ReadData(ttt,1024);
	if(i==0)
	{	
		err++;
		if(err>1000)
		{
			return -1;/**/
		}
		Sleep(1);
		goto jjj;
	}
	ttt+=i;
	if(CheckResponseMsg(resmsg,ttt-resmsg)!=0)
	{
		err++;
		if(err>1000)
			return -1;/**/
		Sleep(1);
		goto jjj;
	}
	for(j=0;j<ttt-resmsg-1;j++)
	{
		sprintf(res+j*2,"%02X",*(resmsg+j));
	}
	return 0;
}
/*
功能:	按照ST340的通讯规则针对不同类型的命令生成响应请求报文的头
参数:	1	2	3
返回:	
*/
char * CST340::GenCmdHead(int flag)
{
	memset(tmphead,0,sizeof(tmphead));
	switch(flag)
	{
	case 1:/*系统命令*/
		strcpy(tmphead,"8000");
		break;
	case 2:/*PSAM输入命令*/
		strcpy(tmphead,"4049");
		break;
	case 3:/*PSAM输出命令*/
		strcpy(tmphead,"404F");
		break;
	default:
		break;
	}
	return tmphead;
}

int CST340::CardPowerDown()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*长度*/
	strcat(tmpcmd,"05");
	/*命令体*/
	strcat(tmpcmd,"8063000000");
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*分析命令返回*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::CardReset()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*长度*/
	strcat(tmpcmd,"05");
	/*命令体*/
	strcat(tmpcmd,"8061000000");
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	int rs=SendCommand(tmpcmd,resmsg);
	if(rs!=0)
	{
		AfxMessageBox("Failed.");
		return -1;
	}
	/*分析命令返回*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::CardInCheck()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*长度*/
	strcat(tmpcmd,"05");
	/*命令体*/
	strcat(tmpcmd,"8060000000");
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*分析命令返回*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::SetDelay(int ms)
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*长度*/
	strcat(tmpcmd,"05");
	/*命令体*/
	strcat(tmpcmd,"806B");
	char delay[3];
	sprintf(delay,"%02X",ms);
	strcat(tmpcmd,delay);
	strcat(tmpcmd,"0000");
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*分析命令返回*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}
/*****************************************************
功能:	发送PSAM卡的各类命令
参数:	psamcmd	十六进制字符串表示的待发送的PSAM卡命令
	flag	输出命令3 输入命令2	
返回:	0	有效的响应报文
	*	无效的响应报文	
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
int CST340::PSAMCommand(int flag, const char *psamcmd)
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*命令头*/
	strcpy(tmpcmd,GenCmdHead(flag));
	/*长度*/
	char lenbuf[3];
	sprintf(lenbuf,"%02X",strlen(psamcmd)/2);
	strcat(tmpcmd,lenbuf);
	/*命令体*/
	strcat(tmpcmd,psamcmd);
	/*发出命令,接收响应*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	int rs=SendCommand(tmpcmd,resmsg);
	if(rs!=0)
	{
		AfxMessageBox("Failed.");
		return -1;
	}
	/*分析命令返回*/
/*	CString strtmp;
	strtmp.Format ("%s=%s",tmpcmd,resmsg);
	AfxMessageBox(strtmp);*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

char * CST340::GetRequest()
{
	return request;
}

char * CST340::GetResponse()
{
	return response;
}
