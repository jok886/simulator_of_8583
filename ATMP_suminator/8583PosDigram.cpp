// 8583PosDigram.cpp: implementation of the C8583PosDigram class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "pos.h"
#include "8583PosDigram.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C8583PosDigram::C8583PosDigram()
{
	memset(digram,0,sizeof(digram));
	for(int i=0;i<64;i++)
	{
		fld[i]=NULL;
	}
}

C8583PosDigram::~C8583PosDigram()
{
	EmptyDigram();
}

void C8583PosDigram::EmptyDigram()
{
	memset(digram,0,sizeof(digram));
	for(int i=0;i<64;i++)
	{
		if(fld[i]!=NULL)
		{
			free( fld[i]);
		}
		fld[i]=NULL;
	}

}

BOOL C8583PosDigram::SetFldValue(int nIndex, const char *newVal,int iLen)
{
	ClearFld(nIndex);

	fld[nIndex-1]=(char *)malloc(iLen+1);

	memset(fld[nIndex-1],0,iLen+1);

	memcpy(fld[nIndex-1],newVal,iLen);

	return TRUE;
}

BOOL C8583PosDigram::ClearFld(int nIndex)
{
	if(fld[nIndex-1]!=NULL)
		free(fld[nIndex-1]);

	fld[nIndex-1]=NULL;

	return TRUE;
}

int C8583PosDigram::Parse()
{
	int curpos=0;
	//位图
	static int  bmplen[64] = {
		0, 		-1099, 	-6, 	-12, 	0, 		0, 		0, 		0, 		0, 		0,
		-6, 	-6, 	-6, 	-4, 	0, 		0, 		0, 		0, 		0, 		0,
		0, 		-4, 	0, 		0, 		2, 		0, 		0, 		0, 		0, 		0,
		0, 		0, 		0, 		0, 		-1099,	-1999, 	12, 	6, 		2,		0,
		8, 		15, 	0, 		0, 		0, 		0, 		0, 		1999, 	0, 		0,
		0, 		-16, 	0, 		1999, 	0,		0, 		0, 		0, 		0, 		-10,
		-10, 	1999, 	1999, 	-16
	};
	//1-读取报文长度进行验证
		char	tmplen[5];
		int		ilen=0;
		memset(tmplen,0,5);
		//取得十六进制的网控器发送的报文长度,如008E
		memcpy(tmplen,digram+curpos,4);
		sscanf(tmplen,"%4X",&ilen);
			//进制转换
			//ilen+=(itmp/10)*16+(itmp%10);
			//
		if(len!=(ilen+2))	//报文长度不够
			return -1;	
		curpos+=4;
		Len.Format("%s",tmplen);
	//2-提取网控器报文头
		char	tmpNacHead[11];
		memset(tmpNacHead,0,11);
		//取网控器报文头6000000000
		memcpy(tmpNacHead,digram+curpos,10);
		curpos+=10;
		NacHead.Format ("%s",tmpNacHead);
	//3-提取信息码
		char	tmpXXM[5];
		memset(tmpXXM,0,5);
		memcpy(tmpXXM,digram+curpos,4);
		curpos+=4;
		xxm.Format ("%s",tmpXXM);

	//4-读取位元表,分析存在位,纳入数组bmp中
		char	tmpBitmap[17];
		memset(tmpBitmap,0,17);
		memcpy(tmpBitmap,digram+curpos,16);
		curpos+=16;
		Bitmap.Format ("%s",tmpBitmap);

		ParseBitmapToIntArrayEx(bmp,tmpBitmap,16);

	//5-提取存在位
		int tmpfdlen=0,aaa,bascii=0;
		char tmpfdval[1024];
		for(int i=0;i<64;i++)
		{
			if(bmp[i]==1)
			{
				
				if(bmplen[i]!=0)
				{
					if(bmplen[i]<0)
					{
						bascii=0;
					}
					else
					{
						bascii=1;
					}
					aaa=abs(bmplen[i]);
					if(aaa<1099)
					{
						if(bmplen[i]<0)
						{
							tmpfdlen=abs(bmplen[i]);bascii=0;
						}
						else
						{
							tmpfdlen=2*abs(bmplen[i]);bascii=1;
						}
					}
					else
					{
						if(aaa==1099)
						{
							//两位的变长
								//读取两位的长度
								sscanf((digram+curpos),"%2d",&tmpfdlen);
								curpos+=2;
								if(bmplen[i]>0)
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
								sscanf(digram+curpos,"%4d",&tmpfdlen);
								curpos+=4;
								if(bmplen[i]>0)
									tmpfdlen*=2;
								else
								{
									if((tmpfdlen%2)!=0)
										tmpfdlen++;
								}
						}
					}
					memset(tmpfdval,0,1024);
					memcpy(tmpfdval,digram+curpos,tmpfdlen);
					//{{赋值到对应域中,如果是ASCII码则需要转换
						char fldval[1024];int fldlen=0;
						memset(fldval,0,1024);
						if(bascii==1)
							fldlen=HexToAscii(tmpfdval,fldval);
						else
						{
							fldlen=tmpfdlen;
							memcpy(fldval,tmpfdval,fldlen);
						}
						/*fld[i]=new char(fldlen);
						memset(fld[i],0,fldlen);
						memcpy(fld[i],fldval,fldlen);*/
						SetFldValue(i+1,fldval,fldlen);
					//}}
					curpos+=tmpfdlen;
				}
			}
		}
	return 1;
}

int C8583PosDigram::ParseBitmapToIntArrayStd(int *arr, const char *buf, int len)
{
	unsigned char tmp,j;//tempery character
	int i,k;
	for(i=0;i<len;i++)
	{
		j=0x80;
		tmp=*(buf+i);		
		for(k=0;k<8;k++)
		{
			if(tmp&j)
			{	
				//printf("\t%d",i*4+k);
				arr[i*8+k]=1;								
			}
			else
				arr[i*8+k]=0;
			j>>=1;
		}
	}
	return 0;
}
/*
	Extend-bitmap analysis function
	o	arr	-	interget array,size=4*len
	i	buf	-	hex string [0123456789ABCDEF]*
	i	len	-	length of buf
*/
int C8583PosDigram::ParseBitmapToIntArrayEx(int *arr,const char *buf,int len)
{
	unsigned char tmp,j;
	int i,k;
	for(i=0;i<len;i++)
	{
		j=0x08;
		tmp=*(buf+i);
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
				arr[i*4+k]=1;
								
			}
			else
				arr[i*4+k]=0;
			j>>=1;
		}
	}
	return 0;	
}

int C8583PosDigram::HexToAscii(const char *hex, char *res)
{
	int len=0;
	int l=strlen(hex);
	if(l%2==1)
		return -1;
	int j=0,i;int a;
	for(i=0;i<l;i+=2)
	{
		sscanf(hex+i,"%2X",&a);
		res[j]=a;
		j++;
	}
	return j;
}

LPCTSTR C8583PosDigram::GetFldValue(int nIndex)
{
	return fld[nIndex-1];
}
