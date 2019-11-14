// 8583PosDigram.h: interface for the C8583PosDigram class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_8583POSDIGRAM_H__044E6FF9_9362_4184_8097_DB51AA5DC791__INCLUDED_)
#define AFX_8583POSDIGRAM_H__044E6FF9_9362_4184_8097_DB51AA5DC791__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class C8583PosDigram  
{
private:
	int ParseBitmapToIntArrayStd(int *arr,const char * buf,int len);
	int ParseBitmapToIntArrayEx(int *arr,const char *buf,int len);
	char *fld[64];
	int				bmp[64];

	
public:
	//16进制ascii的报文
	char   digram[4096];
	int				len;
	CString xxm,NacHead,Bitmap,Len;

public:
	LPCTSTR GetFldValue(int nIndex);
	int HexToAscii(const char *hex,char *res);
	int Parse();
	BOOL ClearFld(int nIndex);
	BOOL SetFldValue(int nIndex,const char *newVal,int iLen);
	void EmptyDigram();
	C8583PosDigram();
	virtual ~C8583PosDigram();

};

#endif // !defined(AFX_8583POSDIGRAM_H__044E6FF9_9362_4184_8097_DB51AA5DC791__INCLUDED_)
