// ST340.h: interface for the CST340 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ST340_H__AA72C769_02B6_40F8_BEBF_72923FE5D20A__INCLUDED_)
#define AFX_ST340_H__AA72C769_02B6_40F8_BEBF_72923FE5D20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*****************************************************
功能:	奥尊公司发卡器ST340的封装.
要素:	ST340<->PC通讯协议
作者:	高勇
email:	gycommunicate@hotmail.com
日期:	20031104
*****************************************************/
#include "Serial.h"
#include "Tools.h"
typedef unsigned char byte;
#define MAX_BUF_SIZE	10240
class CST340
{
private:
	
	char request[1024];
	char response[1024];

	char * GenCmdHead(int flag);
	int SendCommand(const char *cmd,char * res);
	int CheckResponseMsg(const unsigned char *res,int reslen);
	int GenRequestMsg(const unsigned char *cmd,int cmdlen, unsigned char * reqmsg);

	CSerial comx;
	char tmphead[256];
public:
	BOOL bActive;
	char * GetResponse();
	char * GetRequest();
	int PSAMCommand(int flag,const char *psamcmd);
	int SetDelay(int ms);
	int CardInCheck();
	int CardReset();
	int CardPowerDown();
	int CardPowerOn();
	CST340(int comnum);
	virtual ~CST340();
protected:
};

#endif // !defined(AFX_ST340_H__AA72C769_02B6_40F8_BEBF_72923FE5D20A__INCLUDED_)
