// PsamCard.cpp: implementation of the CPsamCard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "PsamCard.h"
#include "tools.h"
#include "EncryptorAdap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPsamCard::CPsamCard()
{
	
}

CPsamCard::~CPsamCard()
{
	
}
/*
num	4 |8
*/
char * CPsamCard::GetRnd(int num)
{
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"008400000%1d",num);
	return psamcmd;
}

char * CPsamCard::SelectMF()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"00A40000023F00");
	return psamcmd;
}

char * CPsamCard::SelectDFByName(char *filename)
{
	CTools tls;
	char s[1024];
	int i;
	i=strlen(filename);
	memset(s,0,sizeof(s));
	tls.AsciiToBcd2 (filename,i,s);
	
	/*{{*/
	memset(s,0,sizeof(s));
	strcpy(s,"D15600000145442F4550000000000000");
	i=strlen(s)/2;
	/*}}*/
	
	
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"00A40400%02X%s",i,s);
	return psamcmd;
}

char * CPsamCard::CreateMF()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E0000018FFFFFFFFFFFFFFFF0F04315041592E5359532E4444463031");
	return psamcmd;
}

char * CPsamCard::CreateEFDIR()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00200070004020F0F010F");
	return psamcmd;
}

char * CPsamCard::WriteEFDIR(char * name)
{
	CTools tls;
	char s[1024];
	int i;
	i=strlen(name);
	memset(s,0,sizeof(s));
	tls.AsciiToBcd2 (name,i,s);
	
	/*{{*/
	memset(s,0,sizeof(s));
	strcpy(s,"D15600000145442F4550000000000000");
	i=strlen(s)/2;
	/*}}*/
	
	
	
	memset(psamcmd,0,sizeof(psamcmd));
	
	
	sprintf(psamcmd,"00E20020%02X610D4F%02X%s500450424F43",10+i,i,s);
	
	
	/*{{*/
	
	//	strcpy(psamcmd,"00E200201A61184F10D15600000145442F4550000000000000500450424F43");
	/*}}*/
	
	return psamcmd;
}

char * CPsamCard::CreatePUB()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00200070015000F0F000E");
	return psamcmd;
}

char * CPsamCard::WritePUB(const char *sid)
{
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"00D695000E%020s0101FFFF",sid);
	return psamcmd;
}

char * CPsamCard::CreateDF(const char *name)
{
	CTools tls;
	char s[1024];
	int i;
	i=strlen(name);
	memset(s,0,sizeof(s));
	tls.AsciiToBcd2 (name,i,s);
	/*{{*/
	memset(s,0,sizeof(s));
	strcpy(s,"D15600000145442F4550000000000000");
	i=strlen(s)/2;
	/*}}*/
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"80E00100%02X2F010F00%s",i+4,s);
	
	
	return psamcmd;
}

char * CPsamCard::CreateKeyFile()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00200070001050F0F1000");
	return psamcmd;
}

char * CPsamCard::SimpleAddMK(const char *key)
{
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"80D40000170100000F010F88%032s",key);
	return psamcmd;
}

char * CPsamCard::SimpleAddWK(const char *key)
{
	memset(psamcmd,0,sizeof(psamcmd));
	sprintf(psamcmd,"80D40000170100270F010F88%032s",key);
	return psamcmd;
}

char * CPsamCard::EndMF()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00001023F00");
	return psamcmd;
}

char * CPsamCard::EndDF()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00101022F01");
	return psamcmd;
	
}
/*
使用本函数必须设定卡片主控密钥是88888888888888888888888888888888
AMK	应用主控密钥32HEX
RND	随机数8HEX

*/
char * CPsamCard::LoadAppMK(const char *incmk,const char * amk,const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char mac[8];
	int j;
	unsigned  char tmpbuf[1024];
	unsigned char cmk[16];
	
	/*计算密文:存入TMP*/
	sprintf(tmp,"170100000F010F88%032s",amk);
	memset(cmk,0,sizeof(cmk));
	memset(tmpbuf,0,sizeof(tmpbuf));
	sprintf((char *)tmpbuf,"%032s",incmk);
	tls.Bcd2ToAscii((char *)tmpbuf,32,0,(char *)cmk);
	memset(tmpbuf,0,sizeof(tmpbuf));
	tls.Bcd2ToAscii(tmp,48,0,(char *)tmpbuf);
	tls.Des3((char *)cmk,(char *)tmpbuf,(char *)tmpbuf+48);
	tls.Des3((char *)cmk,(char *)tmpbuf+8,(char *)tmpbuf+48+8);
	tls.Des3((char *)cmk,(char *)tmpbuf+16,(char *)tmpbuf+48+16);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,"84D400001C",10);
	for(j=0;j<24;j++)
	{
		sprintf(tmp+10+j*2,"%02X",*(tmpbuf+48+j));
	}
	//strcat(tmp,"80");
	/*计算MAC*/	
	sprintf((char  *)tmpbuf,"%08s00000000",rnd);
	tls.Bcd2ToAscii ((char *)tmpbuf,16,0,(char *)mac);
	memset(tmpbuf,0,sizeof(tmpbuf));
	tls.Bcd2ToAscii (tmp,strlen(tmp),0,(char *)tmpbuf);
	tls.GenMac (tmpbuf,29,cmk,mac);
	/*生成安全报文*/
	for(j=0;j<4;j++)
	{
		sprintf(tmp+58+j*2,"%02X",*(mac+j));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}
/*
APPMK	应用主控密钥32HEX
AWK	应用加密密钥
RND	随机数8HEX
*/
char * CPsamCard::LoadAppWK(const char *appMK, const char *awk, const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char mac[8];
	int j;
	unsigned  char tmpbuf[1024];
	unsigned char amk[16];
	
	/*计算密文:存入TMP*/
	sprintf(tmp,"170100270F010F88%032s",awk);
	memset(amk,0,sizeof(amk));
	tls.Bcd2ToAscii(appMK,32,0,(char *)amk);
	tls.Bcd2ToAscii(tmp,48,0,(char *)tmpbuf);
	tls.Des3((char *)amk,(char *)tmpbuf,(char *)tmpbuf+48);
	tls.Des3((char *)amk,(char *)tmpbuf+8,(char *)tmpbuf+48+8);
	tls.Des3((char *)amk,(char *)tmpbuf+16,(char *)tmpbuf+48+16);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,"84D400001C",10);
	for(j=0;j<24;j++)
	{
		sprintf(tmp+10+j*2,"%02X",*(tmpbuf+48+j));
	}
	//strcat(tmp,"80");
	/*计算MAC*/	
	sprintf((char  *)tmpbuf,"%08s00000000",rnd);
	tls.Bcd2ToAscii ((char *)tmpbuf,16,0,(char *)mac);
	memset(tmpbuf,0,sizeof(tmpbuf));
	tls.Bcd2ToAscii (tmp,strlen(tmp),0,(char *)tmpbuf);
	tls.GenMac (tmpbuf,29,amk,mac);
	/*生成安全报文*/
	for(j=0;j<4;j++)
	{
		sprintf(tmp+58+j*2,"%02X",*(mac+j));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}

char * CPsamCard::CreateEnKeyFile()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"80E00200070001C50F0F1000");
	return psamcmd;
}

CEncryptorAdap enadap;
char * CPsamCard::EnLoadAWK(const char *sid,const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char _sid[8],_cmdhead[5],_rnd[8],_keyattr[8],resval[32];
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%016s",sid);
	tls.Bcd2ToAscii(tmp,16,0,(char *)_sid);
	
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"84D400001C");
	tls.Bcd2ToAscii(tmp,10,0,(char *)_cmdhead);
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%08s00000000",rnd);
	tls.Bcd2ToAscii(tmp,16,0,(char *)_rnd);
	
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"0100270F010F88");
	tls.Bcd2ToAscii(tmp,14,0,(char *)_keyattr);
	
	/*与加密机通讯*/
	memset(resval,0,sizeof(resval));
	if(enadap.GenICAppKey((char *)_sid,(char *)_rnd,(char *)_cmdhead,(char *)_keyattr,(char *)resval)!=32)
		return NULL;
	/*生成安全报文*/
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"84D400001C");
	for(int i=0;i<28;i++)
	{
		sprintf(tmp+10+i*2,"%02X",*(resval+i));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}

char * CPsamCard::ReadPub()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"00B000000E");
	return psamcmd;
}
/*
cmk	传输密钥
tmp	应用密钥
sid	卡片标记号
rnd	随机数
*/
char * CPsamCard::EnLoadAWKLocal(const char *tmk, const char *cmk, const char *sid, const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char mac[8];
	int j;
	unsigned  char tmpbuf[1024];
	char amk[33];
	
	/*计算awk*/
	memset(amk,0,sizeof(amk));
	char _tmk[16],_sid[16],_amk[16];
	memset(_tmk,0,sizeof(_tmk));
	memset(_sid,0,sizeof(_sid));
	memset(_amk,0,sizeof(_amk));
	tls.Bcd2ToAscii (tmk,32,0,_tmk);
	tls.Bcd2ToAscii (sid,16,0,_sid);
	tls.GenSonKey (_tmk,_sid,_amk);
	tls.AsciiToBcd2 (_amk,16,amk);
	
	/*计算密文:存入TMP*/
	sprintf(tmp,"170100270F010F88%032s",amk);
	memset(amk,0,sizeof(amk));
	tls.Bcd2ToAscii(cmk,32,0,(char *)amk);
	tls.Bcd2ToAscii(tmp,48,0,(char *)tmpbuf);
	tls.Des3((char *)amk,(char *)tmpbuf,(char *)tmpbuf+48);
	tls.Des3((char *)amk,(char *)tmpbuf+8,(char *)tmpbuf+48+8);
	tls.Des3((char *)amk,(char *)tmpbuf+16,(char *)tmpbuf+48+16);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,"84D400001C",10);
	for(j=0;j<24;j++)	
	{
		sprintf(tmp+10+j*2,"%02X",*(tmpbuf+48+j));	
	}
	//strcat(tmp,"80");
	/*计算MAC*/	
	sprintf((char  *)tmpbuf,"%08s00000000",rnd);
	tls.Bcd2ToAscii ((char *)tmpbuf,16,0,(char *)mac);
	memset(tmpbuf,0,sizeof(tmpbuf));
	tls.Bcd2ToAscii (tmp,strlen(tmp),0,(char *)tmpbuf);
	tls.GenMac (tmpbuf,29,(unsigned char *)amk,mac);
	/*生成安全报文*/
	for(j=0;j<4;j++)
	{
		sprintf(tmp+58+j*2,"%02X",*(mac+j));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}

char * CPsamCard::UpdateAWKLocal(const char *tmk, const char *cmk, const char *sid, const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char mac[8];
	int j;
	unsigned  char tmpbuf[1024];
	char amk[33];
	
	/*计算awk*/
	memset(amk,0,sizeof(amk));
	char _tmk[16],_sid[16],_amk[16];
	memset(_tmk,0,sizeof(_tmk));
	memset(_sid,0,sizeof(_sid));
	memset(_amk,0,sizeof(_amk));
	tls.Bcd2ToAscii (tmk,32,0,_tmk);
	tls.Bcd2ToAscii (sid,16,0,_sid);
	tls.GenSonKey (_tmk,_sid,_amk);
	tls.AsciiToBcd2 (_amk,16,amk);
	
	/*计算密文:存入TMP*/
	sprintf(tmp,"170100270F010F88%032s",amk);
	memset(amk,0,sizeof(amk));
	tls.Bcd2ToAscii(cmk,32,0,(char *)amk);
	tls.Bcd2ToAscii(tmp,48,0,(char *)tmpbuf);
	tls.Des3((char *)amk,(char *)tmpbuf,(char *)tmpbuf+48);
	tls.Des3((char *)amk,(char *)tmpbuf+8,(char *)tmpbuf+48+8);
	tls.Des3((char *)amk,(char *)tmpbuf+16,(char *)tmpbuf+48+16);
	memset(tmp,0,sizeof(tmp));
	memcpy(tmp,"84D407011C",10);
	for(j=0;j<24;j++)
	{
		sprintf(tmp+10+j*2,"%02X",*(tmpbuf+48+j));
	}
	//strcat(tmp,"80");
	/*计算MAC*/	
	sprintf((char  *)tmpbuf,"%08s00000000",rnd);
	tls.Bcd2ToAscii ((char *)tmpbuf,16,0,(char *)mac);
	memset(tmpbuf,0,sizeof(tmpbuf));
	tls.Bcd2ToAscii (tmp,strlen(tmp),0,(char *)tmpbuf);
	tls.GenMac (tmpbuf,29,(unsigned char *)amk,mac);
	/*生成安全报文*/
	for(j=0;j<4;j++)
	{
		sprintf(tmp+58+j*2,"%02X",*(mac+j));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}

char * CPsamCard::UpdateAWK(const char *sid, const char *rnd)
{
	CTools tls;
	char tmp[1024];
	unsigned char _sid[8],_cmdhead[5],_rnd[8],_keyattr[8],resval[32];
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%016s",sid);
	tls.Bcd2ToAscii(tmp,16,0,(char *)_sid);
	
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"84D407011C");
	tls.Bcd2ToAscii(tmp,10,0,(char *)_cmdhead);
	
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%08s00000000",rnd);
	tls.Bcd2ToAscii(tmp,16,0,(char *)_rnd);
	
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"0100270F010F88");
	tls.Bcd2ToAscii(tmp,14,0,(char *)_keyattr);
	
	/*与加密机通讯*/
	memset(resval,0,sizeof(resval));
	if(enadap.GenICAppKey((char *)_sid,(char *)_rnd,(char *)_cmdhead,(char *)_keyattr,(char *)resval)!=32)
		return NULL;
	/*生成安全报文*/
	memset(tmp,0,sizeof(tmp));
	strcpy(tmp,"84D407011C");
	for(int i=0;i<28;i++)
	{
		sprintf(tmp+10+i*2,"%02X",*(resval+i));
	}
	/*返回结果*/
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,tmp);
	return psamcmd;
}

char * CPsamCard::InitDes()
{
	memset(psamcmd,0,sizeof(psamcmd));
	strcpy(psamcmd,"801A2701083132333435363738");
	return psamcmd;
}
