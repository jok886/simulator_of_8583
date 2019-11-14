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
�����ʽ:
	NAD+PCB+LEN+DATA1+CKS
   ���У�
       NAD = 00H   DATA1ΪT=1����������
       NAD = 40H   DATA1ΪT=0����������
       NAD = 80H   DATA1Ϊϵͳ��������
 
       PCB = 49H����NAD = 40Hʱ��  DATA1ΪT = 0����������
       PCB = 4FH����NAD = 40Hʱ��  DATA1ΪT = 0���������

       LENΪDATA1�����ݳ��ȣ����ֽ�Ϊ��λ��
       DATA1Ϊ��������
       CHK Ϊ֮ǰ�����������ݵ�����
ϵͳ����
	CLA+INS+P1+P2+P3
	��Ƭ�ϵ�	80+62+00+00+00
	��Ƭ�µ�	80+63+00+00+00
	��Ƭ��λ	80+61+00+00+00
	��鿨Ƭ��λ	80+60+00+00+00
	�����ֽڷ�����ʱ80+6B+N+00+00

ϵͳ����Ӧ��
      80 | 00 | 02 | ST1 | ST2 | CHK|   
      ST1 ST2 = 9000H  ����ִ�������Ƭ��λ��  
      ST1 ST2 = 7001H  ��Ƭû�е�λ  
      ST1 ST2 = 7002H  ���Զ�������  
      ST1 ST2 = 7003H  ����IC��Ӧ��ʱ  
      ST1 ST2 = 7004H  ����PC�����ʱ  
      ST1 ST2 = 700FH  δ֪����  
      N = 0.1ms��������
      CHK Ϊ֮ǰ�����������ݵ�����
******************************************************/

/*****************************************************
����:	��Ƭ�ϵ�.	80+62+00+00+00
����:	
����:		
����:	����
email:	gycommunicate@hotmail.com
����:	20031104
*****************************************************/
int CST340::CardPowerOn()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*����*/
	strcat(tmpcmd,"05");
	/*������*/
	strcat(tmpcmd,"8062000000");
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*���������*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

/*****************************************************
����:	����ͨ�����ڷ���ST340��������.
����:	cmd	�����ִ�
	cmdlen	�����
	reqmsg	ST340������[cmdlen+1]
����:	+	reqmsg�ĳ���
	-0	ʧ��	
����:	����
email:	gycommunicate@hotmail.com
����:	20031104
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
����:	���ͨ�����ڴ�ST340��������Ӧ����.
����:	res	��Ӧ����
����:	0	��Ч����Ӧ����
	-1	��Ч����Ӧ����	
����:	����
email:	gycommunicate@hotmail.com
����:	20031104
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
����:	ST340��ͨѶ��������������Ȼ��ȴ�����
����:	cmd	ʮ�������ַ�����ʾ�Ĵ����͵�����
	res	ʮ�������ַ�����ʾ�Ľ��ܵ���������Ӧ	
����:	0	��Ч����Ӧ����
	*	��Ч����Ӧ����	
����:	����
email:	gycommunicate@hotmail.com
����:	20031104
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
����:	����ST340��ͨѶ������Բ�ͬ���͵�����������Ӧ�����ĵ�ͷ
����:	1	2	3
����:	
*/
char * CST340::GenCmdHead(int flag)
{
	memset(tmphead,0,sizeof(tmphead));
	switch(flag)
	{
	case 1:/*ϵͳ����*/
		strcpy(tmphead,"8000");
		break;
	case 2:/*PSAM��������*/
		strcpy(tmphead,"4049");
		break;
	case 3:/*PSAM�������*/
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
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*����*/
	strcat(tmpcmd,"05");
	/*������*/
	strcat(tmpcmd,"8063000000");
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*���������*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::CardReset()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*����*/
	strcat(tmpcmd,"05");
	/*������*/
	strcat(tmpcmd,"8061000000");
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	int rs=SendCommand(tmpcmd,resmsg);
	if(rs!=0)
	{
		AfxMessageBox("Failed.");
		return -1;
	}
	/*���������*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::CardInCheck()
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*����*/
	strcat(tmpcmd,"05");
	/*������*/
	strcat(tmpcmd,"8060000000");
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*���������*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}

int CST340::SetDelay(int ms)
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(1));
	/*����*/
	strcat(tmpcmd,"05");
	/*������*/
	strcat(tmpcmd,"806B");
	char delay[3];
	sprintf(delay,"%02X",ms);
	strcat(tmpcmd,delay);
	strcat(tmpcmd,"0000");
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	SendCommand(tmpcmd,resmsg);
	/*���������*/
	strcpy(request,tmpcmd);
	strcpy(response,resmsg);
	return 0;
}
/*****************************************************
����:	����PSAM���ĸ�������
����:	psamcmd	ʮ�������ַ�����ʾ�Ĵ����͵�PSAM������
	flag	�������3 ��������2	
����:	0	��Ч����Ӧ����
	*	��Ч����Ӧ����	
����:	����
email:	gycommunicate@hotmail.com
����:	20031104
*****************************************************/
int CST340::PSAMCommand(int flag, const char *psamcmd)
{
	char tmpcmd[256];
	memset(tmpcmd,0,sizeof(tmpcmd));
	/*����ͷ*/
	strcpy(tmpcmd,GenCmdHead(flag));
	/*����*/
	char lenbuf[3];
	sprintf(lenbuf,"%02X",strlen(psamcmd)/2);
	strcat(tmpcmd,lenbuf);
	/*������*/
	strcat(tmpcmd,psamcmd);
	/*��������,������Ӧ*/
	char resmsg[2*MAX_BUF_SIZE];
	memset(resmsg,0,sizeof(resmsg));
	int rs=SendCommand(tmpcmd,resmsg);
	if(rs!=0)
	{
		AfxMessageBox("Failed.");
		return -1;
	}
	/*���������*/
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
