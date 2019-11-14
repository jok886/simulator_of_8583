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
/*转换密码格式：从终端PIN格式到易办事PIN格式*/
int CEncryptorRelate::ToEBPinFormat(const char *ctiPin, char *ebPin)
{

	return 1;
}
/*转换密码格式：从终端PIN格式到POSP PIN格式*/
int CEncryptorRelate::ToPOSPPinFormat(const char *ctiPin, char *pospPin)
{
	return 1;
}
/*计算易办事的MAC*/
int CEncryptorRelate::CalEBMac(const char *src, int len, char *res)
{
	return 1;
}
/*计算POSP的MAC*/
int CEncryptorRelate::CalPOSPMac(const char *src, int len, char *res)
{
	return 1;
}
