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
���ܣ�	��ȡ�̶�����
������
	store	-	�洢���ͣ����ȵ�λ�� 0 ASCII 1 BCD 2 BINARY
	len	-	����

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
���ܣ�	��ȡ�䳤����
������
	vstore	-	���ݴ洢���ͣ����ȵ�λ�� 0 ASCII 1 BCD 2 BINARY 
	lstore	-	����...
	lalign	-	���ȵĶ��뷽ʽ	0 LEFT 1 RIGHT
	maxlen	-	��󳤶�
	len	-	i�䳤λ�� oʵ�ʳ���
*/
