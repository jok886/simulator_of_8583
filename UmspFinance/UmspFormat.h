// UmspFormat.h: interface for the CUmspFormat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPFORMAT_H__DE918341_C343_44A3_B7B9_A049ECE121C3__INCLUDED_)
#define AFX_UMSPFORMAT_H__DE918341_C343_44A3_B7B9_A049ECE121C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commonhead.h"
typedef struct _HDSY_MSG_FORMAT_
{
	int	seqno;		//序号	1－...
	int	type;		//类型
	int	maxlen;		//最大长度，最大变长位数
	int	p_seqno;	//父报文序号
	int	fc_seqno;	//起始控制报文序号
	int	c_num;		//控制报文数目
}TMsgFmt;

class CUmspFormat  
{
public:
	CUmspFormat();
	virtual ~CUmspFormat();

private:
	char	szMsg[MSG_MAX_LEN];	//报文内容
	int	msgLen;			//报文实际长度
	int	curPos;			//当前处理位置
	TMsgFmt msgfmt[MSG_MAX_CNT];	//报文格式

	DWORD	error_cd;		//内部错误代码

};

#endif // !defined(AFX_UMSPFORMAT_H__DE918341_C343_44A3_B7B9_A049ECE121C3__INCLUDED_)
