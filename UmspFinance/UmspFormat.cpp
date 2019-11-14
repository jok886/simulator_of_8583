// UmspFormat.cpp: implementation of the CUmspFormat class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "UmspFormat.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmspFormat::CUmspFormat()
{

}

CUmspFormat::~CUmspFormat()
{

}
/*
功能：	读取固定报文
参数：
	store	-	存储类型（长度单位） 0 ASCII 1 BCD 2 BINARY
	len	-	长度

*/
//DEL int CUmspFormat::ReadFIXLENMsg(unsigned char store, int len,char *res)
//DEL {
//DEL 	int	len_in_bytes;
//DEL 	switch(store)
//DEL 	{
//DEL 	case 0x00:
//DEL 		len_in_bytes=len;
//DEL 		break;
//DEL 	case 0x01:
//DEL 		len_in_bytes=(len+1)/2;
//DEL 		break;
//DEL 	case 0x02:
//DEL 		len_in_bytes=(len+7)/8;
//DEL 		break;
//DEL 	default:
//DEL 		len_in_bytes=0;
//DEL 		break;
//DEL 	}
//DEL 	if(curPos+len_in_bytes>msgLen)
//DEL 	{
//DEL 		error_cd = ERRCD_MSG_UNRECOGNIZE; 
//DEL 		return -1;
//DEL 	}
//DEL 	memcpy(res,szMsg+curPos,len_in_bytes);
//DEL 	curPos+=len_in_bytes;
//DEL }
/*
功能：	读取变长报文
参数：
	vstore	-	内容存储类型（长度单位） 0 ASCII 1 BCD 2 BINARY 
	lstore	-	长度...
	lalign	-	长度的对齐方式	0 LEFT 1 RIGHT
	maxlen	-	最大长度
	len	-	i变长位数 o实际长度
*/
