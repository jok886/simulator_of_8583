// HDSYC8583Digram.cpp: implementation of the HDSYC8583Digram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HDSYC8583Digram.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HDSYC8583Digram::HDSYC8583Digram()
{
	iDigramLen=0;
	curpos=0;
	strDigram=NULL;
	strBitmap=NULL;
	strDevHead=NULL;
	strLength=NULL;
	strTransCd=NULL;
	for(int i=0;i<FLD_NUM;i++)
	{
		iAnalyseMap[i]=0;
		iFldLen[i]=0;
		if(strFldVal[i]!=NULL)
		{
			strFldVal[i]=NULL;
		}
	}
}

HDSYC8583Digram::~HDSYC8583Digram()
{
	ResetDigram();
}
/*
功能：	设置指定域的值。
*/
int HDSYC8583Digram::SetFieldValue(int index, const char *newVal,int len)
{
	ClearField(index);
	int add1=0;
/*	if(0!=(len%2))
		add1=2;
	else*/
		add1=1;
	strFldVal[index]=(char *)malloc(len+add1);

	memset(strFldVal[index],'F',len+add1);

	memset(strFldVal[index]+len+add1-1,0,1);

	memcpy(strFldVal[index],newVal,len);

	iFldLen[index]=len+add1-1;

	return len;
}
/*
功能：	获得指定域的值。
*/
int HDSYC8583Digram::GetFieldValue(int index, char *res)
{
	if(strFldVal[index]!=NULL)
		memcpy(res,strFldVal[index],iFldLen[index]);
	return iFldLen[index];
}

/*
功能：	按照字段的值和AnalyseMap的内容，生成8583报文！
*/
int HDSYC8583Digram::Generate(char *res,int type)
{
	InitAnalyseMap(type);
	//定义报文暂时存放器
		char tmpDigram[2048];
		int  tmpDigramLen=0;
		int  cursor =0;
		memset(tmpDigram,'F',2048);

	//写入设备头
		cursor+=WriteDeviceHead(tmpDigram+cursor);

	//写入信息码
		cursor+=WriteTransCode(tmpDigram+cursor);

	//遍历位域，生成位图，并写入报文暂时存放器
		int tmpPos=cursor;
		cursor+=WriteBitmap(tmpDigram+cursor);
		cursor+=WriteAllFldVal(tmpDigram+cursor);
		WriteBitmap(tmpDigram+tmpPos);
		tmpDigramLen=cursor;

	//清空报文容器
		ClearDigram();//7024040000C10003

	//存储到报文容器
		strDigram=(char *)malloc(sizeof(char)*(tmpDigramLen+5));
		memset(strDigram,0,sizeof(char)*(tmpDigramLen+5));

		sprintf(strDigram,"%04d",tmpDigramLen/2);
		memcpy(strDigram+4,tmpDigram,tmpDigramLen);
		SetLengthHead(strDigram,4);
		iDigramLen=tmpDigramLen+4;	

	//返回给目标
		return ToOutDigram(res);
}
/*
功能：	解析指定内容指定长度指定类型的报文;
*/
int HDSYC8583Digram::Parse(const char *digram8583, int len,int type)
{
	ToInnerDigram(digram8583,len);
	InitAnalyseMap(type);
	//1-读取报文长度进行验证
		if(SnapDigramLength()==-1)
			return -1;
	//2-提取网控器报文头
		SnapDeviceHead();

	//3-提取信息码
		SnapTransCode();

	//4-读取位元表,分析存在位,纳入数组bmp中
		SnapBitmap();

		ParseBitmap();

	//5-提取存在位
		SnapAllFieldValue();
	
	
	return 0;
}
/*
功能：将本类实例中的所有相关字段，清空，置零
*/
void HDSYC8583Digram::ResetDigram()
{
	iDigramLen=0;
	curpos=0;
	if(strDigram!=NULL)
	{
		free(strDigram);
		strDigram=NULL;
	}
	if(strBitmap!=NULL)
	{
		free(strBitmap);
		strBitmap=NULL;
	}
	if(strTransCd!=NULL)
	{
		free(strTransCd);
		strTransCd=NULL;
	}
	if(strLength!=NULL)
	{
		free(strLength);
		strLength=NULL;
	}
	if(strDevHead!=NULL)
	{
		free(strDevHead);
		strDevHead=NULL;
	}
	for(int i=0;i<FLD_NUM;i++)
	{
		iAnalyseMap[i]=0;
		iFldLen[i]=0;
		if(strFldVal[i]!=NULL)
		{
			free(strFldVal[i]);
			strFldVal[i]=NULL;
		}
	}
}
/*
功能：清空指定字段的值
*/
void HDSYC8583Digram::ClearField(int index)
{
	if(strFldVal[index]!=NULL)
	{
		free(strFldVal[index]);
		strFldVal[index]=NULL;
		iFldLen[index]=0;
	}
}
/*
功能：按照子类型初始化分析图
*/
int HDSYC8583Digram::InitAnalyseMap(int type)
{
/*
	10000-BCD
	00000-ASCII
*/
static int  bmplen[][64] =
{
	 {/*深圳银联办事易*/
		0, 	-1099, 	-6, 	-12, 	0, 	0, 	0, 	0,	0, 	0,
		-6, 	-6, 	-4, 	-4, 	0, 	0, 	0, 	-4, 	0, 	0,
		0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0, 	0,
		0, 	0, 	0,	0, 	-1099,	-1999, 	12, 	0, 	2,	3,
		8, 	0, 	18, 	-1999, 	1099, 	0, 	0, 	1999, 	3,	0,
		0, 	8, 	0, 	0, 	0,	0, 	0, 	0, 	0, 	1999,
		1, 	1999, 	1999, 	4
	},
	{/*深圳银联POSP*/
		0, 		-1099, 	-6, 	-12, 	0, 		0, 		0, 		0, 		0, 		0,
		-6, 	-6, 	-6, 	-4, 	0, 		0, 		0, 		0, 		0, 		0,
		0, 		-4, 	0, 		0, 		2, 		0, 		0, 		0, 		0, 		0,
		0, 		0, 		0, 		0, 		-1099,	-1999, 	12, 	6, 		2,		0,
		8, 		15, 	0, 		0, 		0, 		0, 		0, 		1999, 	0, 		0,
		0, 		-16, 	0, 		1999, 	0,		0, 		0, 		0, 		0, 		-10,
		-10, 	1999, 	1999, 	-16
	}	
};	
	int *tmp=NULL;
	switch(type)
	{
	case FORMAT_SZ_EB:
		tmp=&bmplen[FORMAT_SZ_EB][0];
		break;	
	case FORMAT_SZ_POSP:
		tmp=&bmplen[FORMAT_SZ_POSP][0];
		break;
	default:
		tmp=NULL;
	}
	if(tmp==NULL)
		return -1;
	for(int j=0;j<FLD_NUM;j++)
		*(iAnalyseMap+j)=*(tmp+j);
	return type;	
}
/*
将接受处理的报文转换成内部的十六进制报文，即只含有0-9 A-F
*/
int HDSYC8583Digram::ToInnerDigram(const char *newVal,int len)
{
#if 1
	char tag[2];
	int curpos=0;
	if(strDigram!=NULL)
	{
		free(strDigram);
		strDigram=NULL;
	}
	strDigram=(char *)malloc(sizeof(char)*(2*len+1));
	memset(strDigram,0,(2*len+1)*sizeof(char));

	for(int i=0;i<len;i++)
	{
		memset(tag,0,2);
		CharToHex(newVal[i],tag);
		memcpy(strDigram+curpos,tag,2);
		curpos+=2;
	}
	iDigramLen=curpos;
#else
	strDigram=(char *)malloc(sizeof(char)*(len+1));
	memset(strDigram,0,len+1);
	iDigramLen=strlen(newVal);
	strcpy(strDigram,newVal);
#endif
	return curpos;
}

void HDSYC8583Digram::CharToHex(char c, char *h)
{
	char *c2h_tab="0123456789ABCDEF";
	unsigned char t=c;
	memset(h,c2h_tab[((t&0xf0)/16)],1);
	memset(h+1,c2h_tab[((t&0x0f))],1);
}

int HDSYC8583Digram::ToOutDigram(char *res)
{
	int t=0,j=0;
	if((iDigramLen%2)!=0)
		return -1;	//内部处理错误
	for(int i=0;i<iDigramLen;i+=2)
	{
		sscanf(strDigram+i,"%2X",&t);
		memset(res+j,t,1);
		j++;
	}
	return j;
}





int HDSYC8583Digram::SnapDigramLength()
{
	int		ilen=0;
	strLength=(char *)malloc(sizeof(char)*5);
	memset(strLength,0,sizeof(char)*5);
	//取得十六进制的网控器发送的报文长度,如008E
	memcpy(strLength,strDigram+curpos,4);
	sscanf(strLength,"%4d",&ilen);
		
	if(iDigramLen!=2*(ilen+2))	//报文长度不够
		return -1;	
	curpos+=4;
	return ilen;
}

int HDSYC8583Digram::SnapDeviceHead()
{
	strDevHead=(char *)malloc(sizeof(char)*11);
	memset(strDevHead,0,sizeof(char)*11);
	//取网控器报文头6000000000
	memcpy(strDevHead,strDigram+curpos,10);
	curpos+=10;
	return 10;
}

int HDSYC8583Digram::SnapTransCode()
{
		strTransCd=(char *)malloc(sizeof(char)*5);
		memset(strTransCd,0,sizeof(char)*5);
		memcpy(strTransCd,strDigram+curpos,4);
		curpos+=4;
		return 4;
}

int HDSYC8583Digram::SnapBitmap()
{
	strBitmap=(char *)malloc(sizeof(char)*17);
	memset(strBitmap,0,sizeof(char)*17);
	memcpy(strBitmap,strDigram+curpos,16);
	curpos+=16;
	return 16;
}

int HDSYC8583Digram::ParseBitmap()
{
	unsigned char tmp,j;
	int i,k;
	for(i=0;i<16;i++)
	{
		j=0x08;
		tmp=*(strBitmap+i);
		if(tmp<'0'||tmp>'F'||(tmp>'9'&&tmp<'A'))
		{
			return -1;		//invalid bitmap;
		}
		else
		{
			if(tmp<='9'&&tmp>='0')
				tmp-=0x30;
			else
				tmp-=0x37;
		}
		for(k=0;k<4;k++)
		{
			if(tmp&j)
			{
				iFldLen[i*4+k]=1;
								
			}
			else
				iFldLen[i*4+k]=0;
			j>>=1;
		}
	}
	return 0;	
}

int HDSYC8583Digram::SnapAllFieldValue()
{
	int tmpfdlen=0,aaa,bascii=0;
		char tmpfdval[1024];
		for(int i=0;i<FLD_NUM;i++)
		{
			if(iFldLen[i]==1)
			{
				
				if(iAnalyseMap[i]!=0)
				{
					if(iAnalyseMap[i]<0)
					{
						bascii=0;
					}
					else
					{
						bascii=1;
					}
					aaa=abs(iAnalyseMap[i]);
					if(aaa<1099)
					{
						if(iAnalyseMap[i]<0)
						{
							tmpfdlen=abs(iAnalyseMap[i]);
							if(tmpfdlen%2 !=0)
								curpos++;
						}
						else
						{
							tmpfdlen=2*abs(iAnalyseMap[i]);
						}
					}
					else
					{
						if(aaa==1099)
						{
							//两位的变长
								//读取两位的长度
								sscanf((strDigram+curpos),"%2d",&tmpfdlen);
								curpos+=2;
								if(iAnalyseMap[i]>0)
									tmpfdlen*=2;
								else
								{
									if((tmpfdlen%2)!=0)
										tmpfdlen++;
								}
						}
						else if(aaa==1999)
						{
							//三位的变长
							//读取两位的长度
								sscanf(strDigram+curpos,"%4d",&tmpfdlen);
								curpos+=4;
								if(iAnalyseMap[i]>0)
									tmpfdlen*=2;
								else
								{
									if((tmpfdlen%2)!=0)
										tmpfdlen++;
								}
						}
					}
					memset(tmpfdval,0,1024);

					memcpy(tmpfdval,strDigram+curpos,tmpfdlen);
					//{{赋值到对应域中
						SetFieldValue(i,tmpfdval,tmpfdlen);
					//}}
					curpos+=tmpfdlen;
				}
			}
		}
		return curpos;
}

int HDSYC8583Digram::GetTransCode(char *res)
{
	if(strTransCd!=NULL)
	{
		memcpy(res,strTransCd,strlen(strTransCd));
		return strlen(strTransCd);
	}
	else
		return -1;

}

int HDSYC8583Digram::GetBitmap(char *res)
{
	if(strBitmap!=NULL)
	{
		memcpy(res,strBitmap,strlen(strBitmap));
		return strlen(strBitmap);
	}
	else
		return -1;

}

int HDSYC8583Digram::SetTransCode(const char *newVal, int len)
{
	if(strTransCd!=NULL)
	{
		free(strTransCd);
		strTransCd=NULL;
	}
	if(len==0)
		return 0;
		int add1=0;
	if(0!=(len%2))
		add1=2;
	else
		add1=1;
	strTransCd=(char *)malloc(sizeof(char)*(len+add1));
	memset(strTransCd,'0',sizeof(char)*(len+add1));
	memset(strTransCd+sizeof(char)*(len+add1-1),0,sizeof(char)*(1));
	memcpy(strTransCd,newVal,sizeof(char)*(len));
	return len;
}

int HDSYC8583Digram::SetBitmap(const char *newVal, int len)
{
	if(strBitmap!=NULL)
	{
		free(strBitmap);
		strBitmap=NULL;
	}
	if(len==0)
		return 0;
	strBitmap=(char *)malloc(sizeof(char)*(len+1));
	memset(strBitmap,0,sizeof(char)*(len+1));
	memcpy(strBitmap,newVal,sizeof(char)*(len));
	return len;
}

int HDSYC8583Digram::SetDevHead(const char *newVal, int len)
{
	if(strDevHead!=NULL)
	{
		free(strDevHead);
		strDevHead=NULL;
	}
	if(len==0)
		return 0;
	int add1=0;
	if(0!=(len%2))
		add1=2;
	else
		add1=1;
	strDevHead=(char *)malloc(len+add1);
	memset(strDevHead,'F',(len+add1));
	memset(strDevHead+len+add1-1,0,1);
	memcpy(strDevHead,newVal,len);
	
	return (len+add1-1);
}

void HDSYC8583Digram::ClearDigram()
{
	if(strDigram!=NULL)
	{
		free(strDigram);
		strDigram=NULL;
	}
	iDigramLen=0;
}

int HDSYC8583Digram::WriteDeviceHead(char *obj)
{
	int i=0;
	if(strDevHead!=NULL)
	{
		i=strlen(strDevHead);
		if(i==0)
			return 0;
		memcpy(obj,strDevHead,i);
		return i;
	}
	return 0;
}

int HDSYC8583Digram::WriteTransCode(char *obj)
{
	int i=0;
	if(strTransCd!=NULL)
	{
		i=strlen(strTransCd);
		if(i==0)
			return 0;
		memcpy(obj,strTransCd,i);
		return i;
	}
	return 0;
}

int HDSYC8583Digram::WriteBitmap(char *obj)
{
	int i=0;
	if(strBitmap!=NULL)
	{
		i=strlen(strBitmap);
		if(i*4==FLD_NUM)
			memcpy(obj,strBitmap,i);
		else
			memset(obj,0,FLD_NUM/4);
	}
	else
	{
		strBitmap=(char *)malloc(FLD_NUM/4+1);
		memset(strBitmap,0,FLD_NUM/4+1);
		memset(strBitmap,'0',FLD_NUM/4);
		memcpy(obj,strBitmap,FLD_NUM/4);
	}
	return (FLD_NUM/4);	
}

int HDSYC8583Digram::WriteAllFldVal(char *obj)
{
	int len=0;
	for(int i=0;i<FLD_NUM;i++)
	{
		if((strFldVal[i]==NULL)||(iFldLen[i]==0))
		{
			ClearBitmap(i);
			continue;
		}
		else
		{
			SetBitmap(i);	
			len+=WriteCertainFieldVal(obj+len,i);
		}		
	}
	return len;
}

int HDSYC8583Digram::SetBitmap(int index)
{
	int i=index/4;
	int j=index%4;
	if(strBitmap==NULL)
		return -1;
	unsigned char c=*(strBitmap+i);
	unsigned char x=0x08;
	x=x>>j;
	if(c<='9'&&c>='0')
		c=c-'0';
	else
		c=c-'A'+10;
	c=c|x;
	if(c<=9&&c>=0)
		c+='0';
	else
		c+='A'-10;
	*(strBitmap+i)=c;
	return 1;
}

int HDSYC8583Digram::ClearBitmap(int index)
{
	int i=index/4;
	int j=index%4;
	if(strBitmap==NULL)
		return -1;
	unsigned char c=*(strBitmap+i);
	unsigned char x=0x08;
	x=x>>j;
	x=~x;
	if(c<='9'&&c>='0')
		c=c-'0';
	else
		c=c-'A'+10;
	c=c&x;
	if(c<=9&&c>=0)
		c+='0';
	else
		c+='A'-10;
	*(strBitmap+i)=c;
	return 1;
}

int HDSYC8583Digram::WriteCertainFieldVal(char *obj, int index)
{
	int len=0;int lll=0;
	if(strFldVal[index]==NULL||iFldLen[index]==0)
		return 0;
	if(abs(iAnalyseMap[index])<1099)
	{
		//定长
		if(iFldLen[index]%2!=0)
		{
			memcpy(obj+len,"0",1);
			len++;
		}
		memcpy(obj+len,strFldVal[index],iFldLen[index]);
		len+=iFldLen[index];
	}
	else if(abs(iAnalyseMap[index])==1099)
	{
		//两位变长
		if(iAnalyseMap[index]>0)
			lll=iFldLen[index]/2;
		else
			lll=iFldLen[index];

		sprintf(obj,"%02d",lll);
		len+=2;
		memcpy(obj+len,strFldVal[index],iFldLen[index]);
		len+=iFldLen[index];
	}
	else if(abs(iAnalyseMap[index])==1999)
	{
		//三位变长
		if(iAnalyseMap[index]<0)
			lll=iFldLen[index]/2;
		else
			lll=iFldLen[index];
		sprintf(obj,"%04d",iFldLen[index]/2);
		len+=4;
		memcpy(obj+len,strFldVal[index],iFldLen[index]);
		len+=iFldLen[index];
	}
	return len;
}

int HDSYC8583Digram::GetDeviceHead(char *res)
{
	if(strDevHead!=NULL)
	{
		memcpy(res,strDevHead,strlen(strDevHead));
		return strlen(strDevHead);
	}
	else
		return -1;
}

int HDSYC8583Digram::GetLengthHead(char *res)
{
	if(strLength!=NULL)
	{
		memcpy(res,strLength,strlen(strLength));
		return strlen(strLength);
	}
	else
		return -1;
}

int HDSYC8583Digram::SetLengthHead(const char *newVal, int len)
{
	if(strLength!=NULL)
	{
		free(strLength);
		strLength=NULL;
	}
	if(len==0)
		return 0;
	strLength=(char *)malloc(len+1);
	memset(strLength,0,(len+1));
	memcpy(strLength,newVal,len);
	return len;
}




