// EncryptorRelate.cpp: implementation of the CEncryptorRelate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "EncryptorRelate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncryptorRelate::CEncryptorRelate()
{

}

CEncryptorRelate::~CEncryptorRelate()
{

}
/*ת�������ʽ�����ն�PIN��ʽ���װ���PIN��ʽ*/
int CEncryptorRelate::ToEBPinFormat(const char *ctiPin, char *ebPin)
{

	return 1;
}
/*ת�������ʽ�����ն�PIN��ʽ��POSP PIN��ʽ*/
int CEncryptorRelate::ToPOSPPinFormat(const char *ctiPin, char *pospPin)
{
	return 1;
}
/*�����װ��µ�MAC*/
int CEncryptorRelate::CalEBMac(const char *src, int len, char *res)
{
	return 1;
}
/*����POSP��MAC*/
int CEncryptorRelate::CalPOSPMac(const char *src, int len, char *res)
{
	return 1;
}
