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
	int	seqno;		//���	1��...
	int	type;		//����
	int	maxlen;		//��󳤶ȣ����䳤λ��
	int	p_seqno;	//���������
	int	fc_seqno;	//��ʼ���Ʊ������
	int	c_num;		//���Ʊ�����Ŀ
}TMsgFmt;

class CUmspFormat  
{
public:
	CUmspFormat();
	virtual ~CUmspFormat();

private:
	char	szMsg[MSG_MAX_LEN];	//��������
	int	msgLen;			//����ʵ�ʳ���
	int	curPos;			//��ǰ����λ��
	TMsgFmt msgfmt[MSG_MAX_CNT];	//���ĸ�ʽ

	DWORD	error_cd;		//�ڲ��������

};

#endif // !defined(AFX_UMSPFORMAT_H__DE918341_C343_44A3_B7B9_A049ECE121C3__INCLUDED_)
