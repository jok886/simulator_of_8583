// EncryptorAdap.cpp: implementation of the CEncryptorAdap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "EncryptorAdap.h"
#include "tools.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncryptorAdap::CEncryptorAdap()
{
	iPort=6668;
	strIP="192.168.52.210";
	tmkidx=tpkidx=1;
}

CEncryptorAdap::~CEncryptorAdap()
{
	
}

int CEncryptorAdap::ChangePinFormat(const char *term_en_pin, const char *sid, const char *rnd, const char *tak, char *bank_en_pin)
{
	char cmd[2048];
	int cmdlen;
	char res[2048];
	int reslen;
	char ip[30];
	short port;
	CAsyncSocket conn;
	CTools fmt;
	
	memset(ip,0,sizeof(ip));
	strcpy(ip,strIP);
	port=iPort;	
	
	
	if(!conn.Connect (ip,port))
		return 1;;
	
	
	{
		/*构建命令*/
		memset(cmd,0,sizeof(cmd));
		StruCmd0555In *cmdin=(StruCmd0555In *)cmd;
		
		/*转换密钥的配置*/
		cmdin->cmd[0]=0x05;     
		cmdin->cmd[1]=0x55; 
		cmdin->ickeyindex[0]=0x00;
		cmdin->ickeyindex[1]=0x01;
		cmdin->zmkindex[0]=0x00;     
		cmdin->zmkindex[1]=0x01;  
		cmdin->pinfmt_pre=0x01;     
		cmdin->pinfmt_nxt=0x01;     
		memcpy(cmdin->pik,tak,8);          
		memcpy(cmdin->pinblock,term_en_pin,8); 
		cmdin->divnum=1;          
		cmdin->session_enable=1;      
		memcpy(cmdin->sid,sid,8);
		memcpy(cmdin->rnd,rnd,8);      
		memset(cmdin->acco,0x31,sizeof(cmdin->acco));        
		
		cmdlen=sizeof(StruCmd0555In);
		char tmp[2048];
		memset(tmp,0,sizeof(tmp));
		fmt.AsciiToBcd2(cmd,cmdlen,tmp);
		//cout<<"提交指令是["<<tmp<<"]"<<endl;
		
		if(conn.Send(cmd,cmdlen,0)<=0)
		{
			return 2;
		}
		memset(res,0,sizeof(res));
		reslen=cmdlen;//sizeof(res);
		
		if(conn.Receive (res,reslen,0)<=0)
		{
			return 3;
		}
		
		
		/*分析返回*/
		memset(tmp,0,sizeof(tmp));
		fmt.AsciiToBcd2(res,reslen,tmp);
		//	cout<<"返回的结果是["<<tmp<<"]"<<"长度是["<<reslen<<"]"<<endl;
		
		StruCmd0555Out *resout=(StruCmd0555Out *)res;
		if(resout->code=='E')
		{
			//	cout<<"加密机不能解析的指令:错误码是";
			//	printf("[%02X]\n",resout->pin[0]);
			return 0;
		}
		memcpy(bank_en_pin,resout->pin,8);
	}
	conn.Close ();
	
	return 0;
}

int CEncryptorAdap::GenICAppKey(const char *sid,const char *vector,const char *cmdhead,const char *keyattr, char *resval)
{
	char cmd[2048];
	int cmdlen;
	char res[2048];
	int reslen;
	char ip[30];
	short port;
	CSockConn conn;
	CTools fmt;
	
	memset(ip,0,sizeof(ip));
	strcpy(ip,strIP);
	port=iPort;	
	
	
	if(conn.TCPConnect (ip,port)!=0)
	{
		AfxMessageBox("连接错误!");
		return -1;;
	}
	/**/
	/*构建命令*/
	memset(cmd,0,sizeof(cmd));
	StruCmdb09bIn *cmdin=(StruCmdb09bIn *)cmd;
	
	/*转换密钥的配置*/
	cmdin->cmd[0]=0xb0;     
	cmdin->cmd[1]=0x9b; 
	memset(cmdin->reserver,0x39,sizeof(cmdin->reserver));
	cmdin->tpkindex[0]=tpkidx/256;
	cmdin->tpkindex[1]=tpkidx%256;
	
	cmdin->tmkindex[0]=tmkidx/256;     
	cmdin->tmkindex[1]=tmkidx%256;  
	cmdin->tpklen=0x01;
	cmdin->tmklen=0x01;
	cmdin->tpklenused=0x01;
	cmdin->tpktmpflag=0x00;
	cmdin->divnum_tpk=0x00;
	cmdin->divnum_tmk=0x01;
	
	cmdin->cmdheadlen=0x05;
	cmdin->keypropertylen=0x07;
	cmdin->areacdlen=0x00;
	
	//memset(cmdin->macvector,0x00,sizeof(cmdin->macvector));
	memcpy(cmdin->cmdhead,cmdhead,5);
	memcpy(cmdin->keyproperty ,keyattr,7);
	memcpy(cmdin->macvector,vector,8);
	
	memcpy(cmdin->sid,sid,8); 
	memset(cmdin->areacd,0,sizeof(cmdin->areacd));
	
	cmdlen=sizeof(StruCmdb09bIn);
	char tmp[2048];
	memset(tmp,0,sizeof(tmp));
	fmt.AsciiToBcd2(cmd,cmdlen,tmp);
	//cout<<"提交指令是["<<tmp<<"]"<<endl;
	
	if(conn.TCPSendData (cmd,cmdlen)!=0)
	{
		return -2;
	}
	memset(res,0,sizeof(res));
	reslen=cmdlen;//sizeof(res);
	
	if(conn.TCPReadData (res,reslen)!=0)
	{
		return -3;
	}
	
	
	/*分析返回*/
	memset(tmp,0,sizeof(tmp));
	fmt.AsciiToBcd2(res,reslen,tmp);
	//	cout<<"返回的结果是["<<tmp<<"]"<<"长度是["<<reslen<<"]"<<endl;
	
	StruCmdb09bOut *resout=(StruCmdb09bOut *)res;
	if(resout->code=='E')
	{
		//cout<<"加密机不能解析的指令:错误码是\t";
		//printf("[%02X]\n",resout->len[0]);
		return -2;
	}
	memcpy(resval,resout->data,resout->len[0]*256+resout->len[1]+8);
	//sleep(1);
	
	conn.TCPClose  ();
	
	return resout->len[0]*256+resout->len[1]+8;	
}
