// Tools.cpp: implementation of the CTools class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "Tools.h"

#include "des.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTools::CTools()
{

}

CTools::~CTools()
{

}
/*常用报文处理工具函数*/
int CTools::Bcd2ToAscii(const char *bcd,int len,int align,char *ascii)
{
	char *tbl="0123456789ABCDEF";
	int i,j;
	char *tmpbuf;
	tmpbuf=(char *) malloc((len+1)*sizeof(char));
	memset(tmpbuf,'0',len+1);
	if((align!=0)&&(len%2)!=0)//右对齐
	{
		memcpy(tmpbuf+1,bcd,len);
	}
	else	//左对齐
	{
		memcpy(tmpbuf,bcd,len);
	}
	for(i=0;i<((len+1)/2);i++)
	{
		for(j=0;j<16;j++)
			if(*(tbl+j)==tmpbuf[2*i])
				break;
		if(j==16)
		{
			free(tmpbuf);
			return -1;
		}
		ascii[i]=j;
		ascii[i] = ascii[i] << 4;
		for(j=0;j<16;j++)
			if(*(tbl+j)==tmpbuf[2*i+1])
				break;
		if(j==16)
		{
			free(tmpbuf);
			return -1;
		}
		ascii[i] += j;
	}	
	free(tmpbuf);
	return (len+1)/2;
};
/*
将0x30转换为"30"
*/
int CTools::AsciiToBcd2(const char *ascii,int len,char *bcd)
{
	char *tbl="0123456789ABCDEF";
	unsigned char t;
	for(int i=0;i<len;i++)
	{
		t=(ascii[i]&(0xf0));
		t=t>>4;
		bcd[2*i]=*(tbl+t);
		t=(ascii[i]&(0x0f));
		bcd[2*i+1]=*(tbl+t);		
	}	
	return (2*len);
};


void CTools::Des3(const char *key, const char *indata, char *res)
{
	unsigned char data[8];
	memset(data,0,sizeof(data));
	CDes des;
	des.EnCode((pbyte) indata,(pbyte) data,(pbyte) key);
	des.DeCode((pbyte) data,(pbyte) data,(pbyte)(key+8));
	des.EnCode((pbyte) data,(pbyte)data,(pbyte) key);
	memcpy(res,data,8);	
}

void CTools::GenSonKey(const char *tmk, const char *sid, char *tak)
{
	int i;
	unsigned char data[8];
	memcpy(data,sid,sizeof(data));
	Des3(tmk,(const char *)data,tak);
	
	/*xor*/
	for(i=0;i<8;i++)
	{
		data[i]^=0xFF;
	}
	
	/**/
	Des3(tmk,(const char *)data,tak+8);
}

void CTools::GenMac(const byte *content, int len, const byte *key, byte *mac)
{
	int i,j,k;
	byte tmp[8];
	CDes des;
	memset(tmp,0,sizeof(tmp));
	byte tmpbuf[1024];
	memset(tmpbuf,0,sizeof(tmpbuf));
	memcpy(tmpbuf,content,len);
	memset(tmpbuf+len,0x80,1);
	j=len/8+(((len%8)==0)?0:1);
	for(i=0;i<j;i++)
	{
		for(k=0;k<8;k++)
		{
			mac[k]^=tmpbuf[i*8+k];
		}
		if(i<j-1)
			des.EnCode(mac,tmp,key);
		else
			Des3((char *)key,(char *)mac,(char *)tmp);
		memcpy(mac,tmp,8);
	}
}

void CTools::UnDes3(const char *key, const char *indata, char *res)
{
	unsigned char data[8];
	memset(data,0,sizeof(data));
	CDes des;
	des.DeCode((pbyte) indata,(pbyte) data,(pbyte) key);
	des.EnCode((pbyte) data,(pbyte) data,(pbyte)(key+8));
	des.DeCode((pbyte) data,(pbyte)data,(pbyte) key);
	memcpy(res,data,8);	
}
