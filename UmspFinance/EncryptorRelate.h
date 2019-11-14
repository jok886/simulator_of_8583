// EncryptorRelate.h: interface for the CEncryptorRelate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCRYPTORRELATE_H__A330F09C_68A9_40D5_886E_A4081DFFD646__INCLUDED_)
#define AFX_ENCRYPTORRELATE_H__A330F09C_68A9_40D5_886E_A4081DFFD646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEncryptorRelate  
{
public:
	int CalPOSPMac(const char * src,int len,char *res);
	int CalEBMac(const char * src,int len,char * res);
	int ToPOSPPinFormat(const char *ctiPin, char *pospPin);
	int ToEBPinFormat(const char * ctiPin,char * ebPin);
	CEncryptorRelate();
	virtual ~CEncryptorRelate();

};

#endif // !defined(AFX_ENCRYPTORRELATE_H__A330F09C_68A9_40D5_886E_A4081DFFD646__INCLUDED_)
