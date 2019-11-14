// Tools.h: interface for the CTools class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLS_H__D6423921_CD3D_4E5D_873F_30999F45B70A__INCLUDED_)
#define AFX_TOOLS_H__D6423921_CD3D_4E5D_873F_30999F45B70A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
typedef unsigned char* pbyte;
typedef unsigned char byte;
class CTools  
{
public:
	void UnDes3(const char *key,const char * indata,char * res);
	void GenMac(const byte *content, int len, const byte *key, byte *mac);
	void GenSonKey(const char * tmk,const char * sid,char * tak);
	void Des3(const char *key,const char * indata,char * res);
	int Bcd2ToAscii(const char *bcd,int len,int align,char *ascii);
	int AsciiToBcd2(const char *ascii,int len,char *bcd);
	CTools();
	virtual ~CTools();

};

#endif // !defined(AFX_TOOLS_H__D6423921_CD3D_4E5D_873F_30999F45B70A__INCLUDED_)
