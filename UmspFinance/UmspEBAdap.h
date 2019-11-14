// UmspEBAdap.h: interface for the CUmspEBAdap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPEBADAP_H__F42183D4_D52C_4899_B5DC_8EFBC6049D81__INCLUDED_)
#define AFX_UMSPEBADAP_H__F42183D4_D52C_4899_B5DC_8EFBC6049D81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "commonhead.h"
/*
	�װ����������ӿ���ʵ�֣���Ҫ��TRANSWORK����������
*/
class CUmspEBAdap:public CUmspAdap
{
private:
	void ShutCliCosket(int s);
	char	EBHostIP[30];		//�װ���ǰ�ýӿ�IP
	short	EBHostPort;		//�װ���ǰ�ýӿ�PORT

public:
	virtual int TransWork();
	CUmspEBAdap();
	virtual ~CUmspEBAdap();

};

#endif // !defined(AFX_UMSPEBADAP_H__F42183D4_D52C_4899_B5DC_8EFBC6049D81__INCLUDED_)
