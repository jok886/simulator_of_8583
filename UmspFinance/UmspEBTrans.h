// UmspEBTrans.h: interface for the CUmspEBTrans class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPEBTRANS_H__75D43A11_D6A7_403C_863A_E764FA5AAC49__INCLUDED_)
#define AFX_UMSPEBTRANS_H__75D43A11_D6A7_403C_863A_E764FA5AAC49__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commonhead.h"
typedef unsigned char BYTE;
typedef struct _HDSY_TERMINAL_IO_DATA
{
	BYTE	mti;		//*交易信息码
	BYTE	acc[10];	//*主帐户
	float	amount;		//*交易金额
	BYTE	termid[8];	//*终端标记号？？？
	BYTE	mechid[18];	//*商户标记号？？？
	BYTE	feetype;	//缴费类型
	BYTE	pin[8];		//*个人密码
	BYTE	result;		//交易执行结果
}TTermIOData;
typedef struct _HDSY_HOST_IO_DATA
{
	char content[1000];
}THostIOData;
class CUmspEBTrans  
{
public:
	TTermIOData	*pTermIOData;
	int		iLogonStatus;
public:
	int TrsEBMgr(int mode,char * ioData,int &ioLen);
	CUmspEBTrans();
	virtual ~CUmspEBTrans();

private:
	int TrsLogon(int mode,char * ioData,int &ioLen);
	int TrsAccInquire(int mode,char * ioData,int &ioLen);
};

#endif // !defined(AFX_UMSPEBTRANS_H__75D43A11_D6A7_403C_863A_E764FA5AAC49__INCLUDED_)
