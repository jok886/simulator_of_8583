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

extern unsigned char IsBmp1InBmp2(unsigned char * bmp1,unsigned char *bmp2,unsigned char len);
extern void AsciiToBcd(const char *str, unsigned char *hex, int count);
extern unsigned char ToHex(unsigned char c);
extern void BcdToAscii(const char *hex, unsigned char *str, int count);
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
	memset(macData,0,1000);

	memset(strPinKey,0,8);
	memset(strMacKey,0,8);
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
/**/	if(0!=(len%2))
		add1=2;
	else
		add1=1;
	
	strFldVal[index]=(char *)malloc(len+add1);

	memset(strFldVal[index],'0',len+add1);

	memset(strFldVal[index]+len+add1-1,0,1);

	if(abs(*(iAnalyseMap+index))<1099)
		memcpy(strFldVal[index]+add1-1,newVal,len);
	else
		memcpy(strFldVal[index],newVal,len);
/*	memcpy(strFldVal[index],newVal,len+add1-1);*/

	iFldLen[index]=len+add1-1;

	return len+add1-1;
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
	SetFieldValue(38,"00",2);
	//定义报文暂时存放器
		char tmpDigram[2048];
		int  tmpDigramLen=0;
		int  cursor =0;
		memset(tmpDigram,'F',2048);
	//
		ParseBitmap();

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

		sprintf(strDigram,"%04X",tmpDigramLen/2);
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
	/*/检查MAC
		char macRev[8];
		char macICal[8];
		memset(macICal,0,8);
		memset(macRev,0,8);
		memcpy(macRev,digram8583+len-10,8);

		CalMAC(digram8583+1+2+11,len-1-2-11-1-1,macICal);

		if(memcmp(macICal,macRev,8)!=0)
			AfxMessageBox("Mac  错误");
	/*/
	ToInnerDigram(digram8583,len);
	InitAnalyseMap(type);
	curpos=0;
	//0-取出报文开始符
		curpos+=2;
	//1-读取报文长度进行验证
		if(SnapDigramLength()==-1)
			return -1;
	//a-珠海的有卡使用标记31 磁卡
	//	curpos+=2;
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
	iType=type;
static int  bmplen[][64] =
{
	 {
		0, 		-1099, 	-6, 	-12, 	0, 		0, 		0, 		0, 		0, 		0,
		-6, 	-6, 	-6, 	-4, 	0, 		0, 		0, 		0, 		0, 		0,
		0, 		-4, 	0, 		0, 		2, 		0, 		0, 		0, 		0, 		0,
		0, 		0, 		0, 		0, 		-1099,	-1999, 	12, 	6, 		2,		0,
		8, 		15, 	0, 		0, 		0, 		0, 		0, 		1999, 	0, 		0,
		0, 		-16, 	0, 		1999, 	0,		0, 		0, 		0, 		0, 		-10,
		-10, 	1999, 	1999, 	-16
	},
	{
		0, 		-1099, 	-6, 	-12, 	0, 		0, 		0, 		0, 		0, 		0,
		-6, 	-6, 	-6, 	-4, 	0, 		0, 		0, 		0, 		0, 		0,
		0, 		-4, 	0, 		0, 		2, 		0, 		0, 		0, 		0, 		0,
		0, 		0, 		0, 		0, 		-1099,	-1999, 	12, 	6, 		2,		0,
		8, 		15, 	0, 		0, 		0, 		0, 		0, 		1999, 	0, 		0,
		0, 		-16, 	0, 		1999, 	0,		0, 		0, 		0, 		0, 		-10,
		-10, 	1999, 	1999, 	-16
	},
	{
	/*1	2	3	4	5	6	7	8	9	0*/
	8,	-1099,	-6,	-12,	-12,	-12,	-10,	-8,	-8,	-8,
	-6,	-6,	-8,	-4,	-4,	-4,	-4,	-4,	-3,	-3,
	-3,	-3,	-3,	-3,	-2,	-2,	-1,	-8,	-8,	-8,
	-8,	-11,	-11,	-28,	-1099,	-1999,	12,	6,	2,	3,
	8,	15,	40,	1099,	1099,	1999,	1999,	1999,	3,	3,
	3,	8,	-16,	1099,	1999,	1999,	1999,	1999,	1999,	1999,
	1999,	1999,	1999,	8
	},
	{/*1	2	3	4	5	6	7	8	9	10bj*/
	8,	-1099,	-6,	-12,	0,	0,	0,	0,	0,	0,
	-6,	-6,	-4,	-4,	-4,	0,	0,	0,	0,	0,
	0,	-3,	0,	0,	-2,	-2,	0,	0,	0,	0,
	0,	-1099,	0,	0,	-1099,	-1999,	12,	6,	2,	0,
	8,	15,	0,	1099,	0,	0,	0,	-1999,	3,	0,
	0,	8,	-16,	1999,	0,	0,	0,	0,	0,	-1999,
	-1999,	1999,	1999,	8	
	},
	{/*1	2	3,	4,	5	6	7	8	9	10*/
	8,	-1099,	-6,	-12,	0,	0,	-10,	0,	0,	0,
	-6,	-6,	-4,	-4,	-4,	0,	0,	-4,	0,	0,
	0,	-3,	0,	-3,	-2,	0,	0,	0,	0,	0,
	0,	0,	1099,	0,	-1099,	-1999,	 12,	 8, 	2, 	0,
	8, 	15, 	0, 	0, 	0, 	0, 	0,  	1999,	 3, 	0,
	0, 	8, 	0, 	1999,	0,	0,	0,	0,	0,	 -1,
	0,	0,	-6, 	8
	},
	{
		/*武汉*/
	/*1	2	3,	4,	5	6	7	8	9	10*/
	0,	-1099,	-6,	-12,	0,	0,	0,	0,	0,	0,
	-6,	-6,	-4,	-4,	0,	0,	0,	0,	0,	0,
	0,	-3,	0,	-3,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	-1999,	-1999,	 12,	 6, 	2, 	0,
	8, 	0, 	18, 	-1999, 	0, 	0, 	0,  	0,	 3, 	0,
	0, 	8, 	0, 	0,	0,	0,	0,	0,	0,	1999,
	1999,	1999,	1999, 	4
	}	,
	{	
		/*shenyang*/
	/*1	2	3,	4,	5	6	7	8	9	10*/
	0,	-1099,	-6,	-12,	0,	0,	0,	0,	0,	0,
	-6,	-6,	-4,	-4,	-4,	0,	0,	0,	0,	0,
	0,	-3,	0,	-3,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	-1099,	-1999,	 12,	 6, 	2, 	0,
	8, 	15, 	18, 	1099, 	0, 	0, 	0,  	0,	 3, 	0,
	0, 	8, 	0, 	1999,	0,	0,	0,	0,	0,	1999,
	1999,	1999,	1999, 	4
	},
	{
		/*福建*/
	/*1	2	3,	4,	5	6	7	8	9	10*/
	0,	-1099,	-6,	-12,	0,	0,	0,	0,	0,	0,
	-6,	-6,	-4,	-4,	-4,	0,	0,	0,	0,	0,
	0,	-3,	0,	-3,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	-1099,	-1999,	 12,	 6, 	2, 	0,
	8, 	15, 	18, 	1099, 	0, 	0, 	0,  	0,	 3, 	0,
	0, 	8, 	0, 	1999,	0,	0,	0,	0,	0,	1999,
	1999,	1999,	1999, 	4
	}
};	
	int *tmp=NULL;
	switch(type)
	{
	case FORMAT_GD_POS:
		tmp=&bmplen[FORMAT_GD_POS][0];
		break;	
	case FORMAT_AZ_ST360:
		tmp=&bmplen[FORMAT_AZ_ST360][0];
		break;
	case 3:
		tmp=&bmplen[3][0];
		break;
	case 4:
		tmp=&bmplen[4][0];
		break;
	case 5:
		tmp=&bmplen[5][0];
		break;
	case 6:
		tmp=&bmplen[6][0];
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
#if 0
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
	//2	len	11	head
	//xxm....    d63   
	//8mac
	if(iFldLen[63])
		CalMAC(res+13,j-13-8,res+j-8)/**/;
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
			
		if(iDigramLen!=2*(ilen+5))	//报文长度不够
			return -1;	
		curpos+=4;
		return ilen;
}

int HDSYC8583Digram::SnapDeviceHead()
{
	/*
	strDevHead=(char *)malloc(sizeof(char)*23);
	memset(strDevHead,0,sizeof(char)*23);
	//取网控器报文头6000000000
	//memcpy(strDevHead,strDigram+curpos,10);curpos+=10;return 10;
	memcpy(strDevHead,strDigram+curpos,22);curpos+=22;return 22;*/
		strDevHead=(char *)malloc(sizeof(char)*11);
	memset(strDevHead,0,sizeof(char)*11);
	//取网控器报文头6000000000
	//memcpy(strDevHead,strDigram+curpos,10);curpos+=10;return 10;
	memcpy(strDevHead,strDigram+curpos,10);curpos+=10;return 10;
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
					if(tmpfdlen+curpos>iDigramLen)
					{		
						AfxMessageBox("不认识的报文格式");
						return 0;
					}
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
//#if 0
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
//#endif
//	SetDevHead("6000000000602100000000",22);
//	memcpy(obj,strDevHead,22);
//	return 22;
	
}

int HDSYC8583Digram::WriteTransCode(char *obj)
{
#if 1
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
#else
	if(memcmp(this->strTransCd ,"0200",4)==0)
	{
		SetTransCode("0210",4);
		memcpy(obj,strTransCd,4);
	}
	return 4;
#endif
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
		memcpy(obj,strFldVal[index],strlen(strFldVal[index]));
		len=strlen(strFldVal[index]);
	}
	else if(abs(iAnalyseMap[index])==1099)
	{
		//两位变长;
		if(iAnalyseMap[index]<0)
			lll=strlen(strFldVal[index]);
		else
			lll=strlen(strFldVal[index])/2;

		//if(iFldLen[index]%2!=0)
		//	lll--;

		sprintf(obj,"%02d",lll);
		len+=2;
		memcpy(obj+len,strFldVal[index],strlen(strFldVal[index]));
		len+=strlen(strFldVal[index]);
	}
	else if(abs(iAnalyseMap[index])==1999)
	{
		//三位变长
		if(iAnalyseMap[index]<0)
			lll=strlen(strFldVal[index]);
		else
			lll=strlen(strFldVal[index])/2;
		//if(iFldLen[index]%2!=0)
			//lll--;
		sprintf(obj,"%04d",lll);
		len+=4;
		memcpy(obj+len,strFldVal[index],strlen(strFldVal[index]));
		len+=strlen(strFldVal[index]);
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



BOOL HDSYC8583Digram::IsExistDomin(int iIndex)
{
	return (iFldLen[iIndex-1]!=0);
}

int HDSYC8583Digram::Generate(char *res, int type, char *bmp)
{
	InitAnalyseMap(type);
	//
		FillFldByTrnCd();
	//设置BITMAP,并分析之	623E40808AC18411
		SetBitmap(bmp,strlen(bmp));
		ParseBitmap();
	//定义报文暂时存放器，并初始化
		char tmpDigram[2048];
		int  tmpDigramLen=0;
		int  cursor =0;
		memset(tmpDigram,0,2048);
	//写入设备头
		cursor+=WriteDeviceHead(tmpDigram+cursor);

	//写入信息码
		cursor+=WriteTransCode(tmpDigram+cursor);

	//分辨存在位，遍历位域，并写入报文暂时存放器
		cursor+=WriteBitmap(tmpDigram+cursor);
		cursor+=WriteAllFldValByBmp(tmpDigram+cursor);
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

int HDSYC8583Digram::WriteAllFldValByBmp(char *obj)
{
	int len=0;
	for(int i=0;i<FLD_NUM;i++)
	{
		if(iFldLen[i]==0||iAnalyseMap[i]==0)
			continue;
		if(strFldVal[i]==NULL)
		{
			int l;
			char buf[412];
			memset(buf,'0',412);
			if(iAnalyseMap[i]<0)
			{
				l=abs(iAnalyseMap[i]);
			}
			else
				l=2*abs(iAnalyseMap[i]);
			if(l>1000)
				l=8;
			SetFieldValue(i,buf,l);
		}
		len+=WriteCertainFieldVal(obj+len,i);
	}
	return len;
}

void HDSYC8583Digram::FillFldByTrnCd()
{
	if(iType==4)
	{
		if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"31",2)==0)//查询
		{			
			SetTransCode("0210",4);
			SetBitmap("623E40808AC18411",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);
			SetFieldValue(53,"3030313031364430303030303039393939393943303030303030303030303031",64);
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"38",2)==0)//查止付
		{
			SetBitmap("623E40808AC18011",16);
			SetTransCode("0210",4);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);
		}
		else if(memcmp(strTransCd,"0100",4)==0 && memcmp(strFldVal[2],"28",2)==0)//预授权
		{
			SetTransCode("0110",4);
			SetBitmap("723E40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"09",2)==0)//消费
		{
			SetTransCode("0210",4);
			SetBitmap("723E40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);//主帐号
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"18",2)==0)//预授权完成
		{
			SetTransCode("0210",4);
			SetBitmap("723E40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"20",2)==0)//消费/预授权完成撤消
		{
			SetTransCode("0110",4);
			SetBitmap("723A40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0100",4)==0 && memcmp(strFldVal[2],"18",2)==0)//预授权取消
		{
			SetTransCode("0110",4);
			SetBitmap("723A40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0420",4)==0 )//自动冲正
		{
			SetTransCode("0430",4);
			SetBitmap("723A40808AC08011",16);
			SetFieldValue(38,"3030",4);	
			SetFieldValue(63,"3838383838383838",16);	
			
		}
		else if(memcmp(strTransCd,"0520",4)==0&&memcmp(strFldVal[2],"94",2)==0 )//结算
		{
			SetTransCode("0530",4);
			SetBitmap("222001008AC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(23,"001",3);
			SetFieldValue(47,"303033303030303030313131313131303034303030303030303030313131303034303030303030303030323334",90);		
		}
		else if(memcmp(strTransCd,"0303",4)==0)//参数下载
		{
			SetTransCode("0313",4);
			SetBitmap("0200000002C10011",16);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"303230313132333435363032313233343537",36);//卡类型
			SetFieldValue(63,"3838383838383838",16);
		}
	}
	else if(iType==5)		//武汉方面
	{
		if(memcmp(strTransCd,"0100",4)==0 && memcmp(strFldVal[2],"31",2)==0)//查询
		{			
			SetTransCode("0110",4);
			SetBitmap("703801000A908001",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);
			SetFieldValue(53,"3030313031364430303030303039393939393943303030303030303030303031",64);
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"10",2)==0)//预授权输入
		{
			SetBitmap("623E40808AC18011",16);
			SetTransCode("0210",4);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);
		}
		else if(memcmp(strTransCd,"0100",4)==0 && memcmp(strFldVal[2],"30",2)==0)//预授权
		{
			SetTransCode("0110",4);
			SetBitmap("703801000E908001",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"00",2)==0)//消费
		{
			SetTransCode("0210",4);
			SetBitmap("703801000E908001",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);//主帐号
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"00",2)==0)//预授权完成
		{
			SetTransCode("0210",4);
			SetBitmap("703801000E908001",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0200",4)==0 && memcmp(strFldVal[2],"02",2)==0)//消费/预授权完成撤消
		{
			SetTransCode("0110",4);
			SetBitmap("723A40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0100",4)==0 && memcmp(strFldVal[2],"18",2)==0)//预授权取消
		{
			SetTransCode("0110",4);
			SetBitmap("723A40808EC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime(),4);
			SetFieldValue(14,GetDateTime()+4,4);
			SetFieldValue(37,"3030303030303031",16);//授权码
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"3031323334",10);		
		}
		else if(memcmp(strTransCd,"0420",4)==0 )//自动冲正
		{
			SetTransCode("0430",4);
			SetBitmap("723A40808AC08011",16);
			SetFieldValue(38,"3030",4);	
			SetFieldValue(63,"3838383838383838",16);	
			
		}
		else if(memcmp(strTransCd,"0520",4)==0&&memcmp(strFldVal[2],"94",2)==0 )//结算
		{
			SetTransCode("0530",4);
			SetBitmap("222001008AC18013",16);
			if(strFldVal[34]!=NULL)
				SetFieldValue(1,strFldVal[34],16);
			SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(23,"001",3);
			SetFieldValue(47,"303033303030303030313131313131303034303030303030303030313131303034303030303030303030323334",90);		
		}
		else if(memcmp(strTransCd,"0303",4)==0)//参数下载
		{
			SetTransCode("0313",4);
			SetBitmap("0200000002C10011",16);
			SetFieldValue(38,"3030",4);
			SetFieldValue(47,"303230313132333435363032313233343537",36);//卡类型
			SetFieldValue(63,"3838383838383838",16);
		}

	}
	else if(iType==3) //beijing
	{
		//设置返回时间
			//SetFieldValue(6,GetDateTime()+4,10);
			SetFieldValue(11,GetDateTime()+4+4,6);
			SetFieldValue(12,GetDateTime()+4,4);
			SetFieldValue(13,GetDateTime()+2,4);
			SetFieldValue(14,GetDateTime()+4,4);
		//填充BITMAP和交易码
		struct good 
		{
			int  type;
			char *mti;
			char *proc;
			char *bitmap;
			char *inbmp;
			char *rmti;
			char *de601;
			char *de603;
		}trnMsg[]=
		{
	{0,	"0210",	"31",	"603C00810AD08C11",	"2020048000C08011",	"0200",	"01",	NULL},/*inquire*/
	
	{1,	"0210",	"00",	"703E00810ED08813",	"3020048000C08011",	"0200",	"22",	NULL},/*sale*/
	{2,	"0410",	"00",	"703E00810AD08811",	"3020048002C08011",	"0400",	"22",	NULL},/*reve_sale*/
	{3,	"0210",	"20",	"703E00810ED08813",	"3020048008C08019",	"0200",	"23",	NULL},/*sale_void*/
	{4,	"0410",	"20",	"703E00810AD08811",	"3020048002C08019",	"0400",	"23",	NULL},/*reve_sale_void*/

	{5,	"0230",	"20",	"703E00810AD08813",	"3020048008C0801B",	"0220",	"25",	NULL},/*refund*/

	{6,	"0110",	"03",	"703E00810ED08813",	"3020048000C08011",	"0100",	"10",	NULL},/*preauth*/
	{7,	"0410",	"03",	"703E00810ED08813",	"3020048002C08011",	"0400",	"10",	NULL},/*reve_preauth*/
	{8,	"0110",	"20",	"703E00810ED08813",	"3020048004C08019",	"0100",	"11",	NULL},/*preauth_void*/
	{9,	"0410",	"20",	"703E00810ED08813",	"7020048006C08019",	"0400",	"11",	NULL},/*reve_preauth_void*/
	
	{10,	"0210",	"00",	"703E00810ED08813",	"3020048004C08019",	"0200",	"20",	NULL},/*preauthfinished*/
	{11,	"0410",	"00",	"703E00810ED08813",	"3020048006C08019",	"0400",	"20",	NULL},/*reve_preauthfinished*/	
	{12,	"0210",	"20",	"703E00810ED08813",	"3020048008C08019",	"0200",	"21",	NULL},/*preauthfinishedvoid*/	
	{13,	"0410",	"20",	"703E00810ED08813",	"3020048002C08019",	"0400",	"21",	NULL},/*reve_preauthfinishedvoid*/
	
	{14,	"0230",	"00",	"703E00810ED08813",	"7020048000C00013",	"0220",	"30",	NULL},/*settle*/

	{15,	"0230",	"00",	"703E00810ED08813",	"7020048000C00013",	"0220",	"32",	NULL},/*settleadjust*/
							     
	{16,	"0810",	"00",	"003800010AC00014",	"0020000000C00012",	"0800",	"00",	"001"},/*logi*/
	{17,	"0830",	"20",	"003800010AC00010",	"0020000000C00010",	"0820",	"00",	"002"},/*logo*/

	{18,	"0510",	"20",	"003A000108C18012",	"0020000000C18012",	"0500",	"00",	"201"},/*sets*/

	{19,	"0330",	"20",	"003800010AC10010",	"0020000000C10010",	"0320",	"00",	"20"},/*202/201*//*sends*/

	{20,	"0330",	"00",	"0000000000000000",	"2020048000C08011",	"0320",	"**",	"***"},/*sendsnotice*/	
	
	{21,	"0810",	"20",	"001800000AC00014",	"0000000000C00010",	"0800",	"00",	"36"},/*360/361*//*passpara*/

	{22,	"0830",	"00",	"0018000002C00010",	"0000000000C00010",	"0820",	"00",	"301"},/*respondtest*/

	{23,	"0830",	"20",	"0018000002C00014",	"0000000000C00014",	"0820",	"00",	"362"},/*passstuts*/

	{24,	"0000",	"00",	"0000000000000000",	"0000000000000000",	"0000",	"**",	"***"},/*NULL*/
			
		};
		char *p[]=
		{
			/*人民币卡	China Union Pay		*/"CUP",
			/*威士卡	VISA			*/"VIS",
			/*万事达卡	Master Card		*/"MCC",
			/*JCB卡	JCB				*/"JCB",
			/*大来卡	Dinner Club		*/"DCC",
			/*运通卡	American Express	*/"AMX"
		};
		static int irand=0;
		char buf[126];
		memset(buf,0x33,126);
		for(int jj=0;jj<3;jj++)
		{
			buf[jj*2]=((*(p[irand%6]+jj))&0xf0) >>4;
			buf[jj*2+1]=((*(p[irand%6]+jj))&0x0f) ;
		}
		for(jj=0;jj<6;jj++)
		{
			char tt[17]="0123456789ABCDEF";
			buf[jj]=tt[buf[jj]];
		}

		SetFieldValue(62,buf,126);
		if (irand>100)
			irand=0;
		else
			irand++;
		for(int i=0;i<sizeof(trnMsg)/sizeof(struct good);i++)
		{
			if (strFldVal[2]!=NULL)
			{
				if((memcmp(strTransCd,trnMsg[i].rmti,4)==0) && (memcmp(strFldVal[2],trnMsg[i].proc,2)==0))
				{
					if(strFldVal[59]==NULL)
					{
						AfxMessageBox("60域没有填");
						return;
					}
					if(memcmp(strFldVal[59],trnMsg[i].de601,strlen(trnMsg[i].de601))!=0)
					{
						if(memcmp(trnMsg[i].de601,"**",1)!=0)
							continue;
					}
					break;
				}
			}
			else if(memcmp(strTransCd,trnMsg[i].rmti,4)==0)
			{
				if(trnMsg[i].de603!=NULL&&(strFldVal[59]+8)!=NULL)
				{
					if(memcmp(strFldVal[59]+8,trnMsg[i].de603,strlen(trnMsg[i].de603))!=0)
					{
						if(memcmp(trnMsg[i].de603,"***",1)!=0)
							continue;
					}
				}
				break;
			}
		}
		/*pos应该根据本地方指定的作出响应	ref	报文格式-报文头-处理要求*/
			//0	无处理要求		strDevHead[15]='0';
					
			//1	下传终端参数		strDevHead[15]='1';
			//2	上传终端状态信息	strDevHead[15]='2';
			//3	重新签到		strDevHead[15]='3';
				//strDevHead[15]='0'+(irand%4);
		//检查上送报文必填域
			unsigned char inb[8],ob[8];
			memset(inb,0,8);
			memset(ob,0,9);
			if(i>=sizeof(trnMsg)/sizeof(struct good))
				return;
			AsciiToBcd(trnMsg[i].inbmp,inb,8);
			AsciiToBcd(strBitmap,ob,8);
			int iNotRet=IsBmp1InBmp2(inb,ob,8);
			CString strMsg;
			if(iNotRet!=0)
			{
				strMsg.Format("第[%d]为必须填写的域，此时没有上送",iNotRet);
				AfxMessageBox(strMsg);
			}

		//填充返回交易码和必须填的报文
			SetTransCode(trnMsg[i].mti,strlen(trnMsg[i].mti));
			SetBitmap(trnMsg[i].bitmap,strlen(trnMsg[i].bitmap));


		/*针对具体的交易填充不同的返回报文*/
		switch(trnMsg[i].type)
		{
		case 0://余额查询
			//响应码
			SetFieldValue(38,"3030",4);
			//54域
			//SetFieldValue(53,"3130303231353644303030303030303939393939",40);
			SetFieldValue(53,"3130303231353643303030303030303939393939",40);
			break;
		case 1://消费交易
			//响应码
			SetFieldValue(38,"3030",4);
			//交易金额
			SetFieldValue(3,"000000100000",12);
			if ((strFldVal[34]!=NULL)&&(strlen(strFldVal[34])>=15))
			{
				unsigned int i=0;
				for(i;i<strlen(strFldVal[34]);i++)
					if(*(strFldVal[34]+i)=='D')
						break;
				SetFieldValue(1,strFldVal[34],i);
			}
			break;
		case 2://消费冲正交易
			//响应码
			SetFieldValue(38,"3030",4);
			//SetFieldValue(38,"3936",4);
			//SetFieldValue(38,"3938",4);
			//SetFieldValue(38,"4130",4);
			break;
		case 3:	//消费撤消
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 4://消费撤消冲正交易
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 5://退货
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 6://预授权
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 7://预授权冲正
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 8://预授权撤消
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 9://预授权撤消冲正
			//响应码
			SetFieldValue(38,"3030",4);			
			break;
		case 10://预授权完成
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 11://预授权完成冲正
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 12://预授权完成撤消
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 13://预授权完成撤消冲正
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 14://结算
			//响应码
			SetFieldValue(38,"3030",4);
			
			break;
		case 15://结算调整
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 16://如果是签到交易		
			//响应码
			SetFieldValue(38,"3030",4);
			//下传PINKEY MACKEY 12 12  8 4   8 4
			{
				unsigned char masterKey[8];
				//unsigned char pinKey[8];
				//unsigned char macKey[8];
				unsigned char nullBuf[16];
				memset(nullBuf,0,16);
				memset(masterKey,0x31,8);

				memset(strPinKey,0x31,8);
				memset(strMacKey,0x32,8);

				CDes des;
				des.EnCode (nullBuf,nullBuf,strPinKey);
				des.EnCode (nullBuf+8,nullBuf+8,strMacKey);
				des.EnCode (strPinKey,strPinKey,masterKey);
				des.EnCode (strMacKey,strMacKey,masterKey);

				unsigned char de62[24];
				memset(de62,0,24);
				memcpy(de62,strPinKey,8);
				memcpy(de62+8,nullBuf,4);
				memcpy(de62+8+4,strMacKey,8);
				memcpy(de62+8+4+8,nullBuf+8,4);

				char ascde62[48];
				memset(ascde62,0,48);
				for(int i=0;i<24;i++)
				{
					char tt[17]="0123456789ABCDEF";
					ascde62[2*i]=tt[(de62[i]&0xf0)>>4];
					ascde62[2*i+1]=tt[(de62[i]&0x0f)];					
				}

				SetFieldValue(61,ascde62,48);
			}
				memset(strPinKey,0x31,8);
				memset(strMacKey,0x32,8);
			break;
		case 17://签退
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 18://批结算
			//响应码
			SetFieldValue(38,"3030",4);
			*(strFldVal[47]+30)='1';
			//*(strFldVal[47]+27)+=1;
			*(strFldVal[47]+61)='1';

			//SetFieldValue(47,"30303030303030",10);
			break;
		case 19://批上送
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 20://批上送通知交易
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 21://参数传递
			/*pos应该根据本地方指定的作出响应	ref	报文格式-报文头-处理要求*/
			//0	无处理要求		strDevHead[15]='0';
					
			//1	下传终端参数		strDevHead[15]='1';
			//2	上传终端状态信息	strDevHead[15]='2';
			//3	重新签到		strDevHead[15]='3';
				strDevHead[15]='0'+3;
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		case 22://回响测试
			//响应码
			SetFieldValue(38,"3030",4);
			/*pos应该根据本地方指定的作出响应	ref	报文格式-报文头-处理要求*/
			//0	无处理要求		strDevHead[15]='0';
					
			//1	下传终端参数		strDevHead[15]='1';
			//2	上传终端状态信息	strDevHead[15]='2';
			//3	重新签到		strDevHead[15]='3';
				strDevHead[15]='0'+2;
			break;
		case 23://状态上送
			/*pos应该根据本地方指定的作出响应	ref	报文格式-报文头-处理要求*/
			//0	无处理要求		strDevHead[15]='0';
					
			//1	下传终端参数		strDevHead[15]='1';
			//2	上传终端状态信息	strDevHead[15]='2';
			//3	重新签到		strDevHead[15]='3';
				strDevHead[15]='0'+1;
			//响应码
			SetFieldValue(38,"3030",4);
			break;
		default:
			break;
		}
		
		char bit37[24+1];
		char bit38[12+1];
		memset(bit37,0,25);
		memset(bit38,0,13);
		memset(bit37,0x33,24);
		memset(bit38,0x33,12);
		bit37[23]+=irand%7;
		bit38[11]+=irand%7;
		SetFieldValue(36,bit37,strlen(bit37));
		SetFieldValue(37,bit38,strlen(bit38));/**/
		if ((strFldVal[34]!=NULL)&&(strlen(strFldVal[34])>=15))
		{
			unsigned int i=0;
			for(i;i<strlen(strFldVal[34]);i++)
				if(*(strFldVal[34]+i)=='D')
					break;
			SetFieldValue(1,strFldVal[34],i);
		}
	}

}

char * HDSYC8583Digram::GetDateTime()
{
	static char curr_time[28];
	memset(curr_time,0,28);
	struct tm *tm;
	time_t t;
	time(&t);
	tm=localtime(&t);
	sprintf(curr_time,"%04d%02d%02d%02d%02d%02d",tm->tm_year +1900,tm->tm_mon+1 ,tm->tm_mday ,tm->tm_hour,tm->tm_min,tm->tm_sec);
	//AfxMessageBox(curr_time);
	return curr_time;
}

int HDSYC8583Digram::ReplyGenerate(const char *recv, int len,int type,char * res)
{
	//解析接收到的报文
		this->Parse (recv,len,type);
	//根据接受到的报文组织返回报文
		FillFldByTrnCd();
	//分析BITMAP
		ParseBitmap();
	//定义报文暂时存放器，并初始化
		char tmpDigram[2048];
		int  tmpDigramLen=0;
		int  cursor =0;
		memset(tmpDigram,0,2048);
	//写入设备头
		cursor+=WriteDeviceHead(tmpDigram+cursor);

	//写入信息码
		cursor+=WriteTransCode(tmpDigram+cursor);

	//分辨存在位，遍历位域，并写入报文暂时存放器
		cursor+=WriteBitmap(tmpDigram+cursor);
		cursor+=WriteAllFldValByBmp(tmpDigram+cursor);
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

int HDSYC8583Digram::GetPassword(char *res)
{
	unsigned char key[8];
	unsigned char rs[16];
	unsigned char ind[8];
	if(strFldVal[51]!=NULL&&strlen(strFldVal[51])>=16)
	{
		memset(ind,0,8);
		memset(rs,0,9);
		memset(key,0x31,8);
		AsciiToBcd(strFldVal[51],ind,8);
		CDes des;
		des.DeCode (ind,rs,key);
	}
	else
	{
		memset(rs,0x20,8);
	}
	memcpy(res,rs,8);
	BcdToAscii(res,rs,8);
	memcpy(res,rs,16);
	return 16;
}
int HDSYC8583Digram::CalMAC(const char *src, int len, char *rs)
{
	unsigned char md[1024];
	unsigned char res[8];
	memset(res,0,8);
	memcpy(res,rs,8);
	memset(md,0,1024);
	memcpy(md,src,len);
	int l=(len/8+1)*8;
	//^
	for(int i=0;i<8;i++)
	{
		for(int j=1;j<l/8;j++)
		{
			md[i]^=md[i+j*8];
		}
	}
	
	CDes des;
	//unsigned char key[8];//strMacKey
	//memset(key,0x31,8);
	//展开
		char mdtmp[8];
		memcpy(mdtmp,md,8);
		BcdToAscii(mdtmp,md,8);
	//DES
	des.EnCode (md,res,strMacKey);
	//^
	for(i=0;i<8;i++)
	{
		md[i]=md[8+i]^res[i];
	}
	//DES
	des.EnCode (md,res,strMacKey);
	//展开
		memcpy(mdtmp,res,8);
		BcdToAscii(mdtmp,md,8);
	//取8字节作为MAC值
	memcpy(res,md,8);
	memcpy(rs,res,8);
	return 8;
}
