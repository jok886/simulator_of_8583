// PsamCard.h: interface for the CPsamCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSAMCARD_H__5401F217_6662_4B85_B9E1_19B056CC0815__INCLUDED_)
#define AFX_PSAMCARD_H__5401F217_6662_4B85_B9E1_19B056CC0815__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CPsamCard  
{
private:
	char psamcmd[1024];
public:
	char * InitDes();
	char * UpdateAWK(const char *sid,const char *rnd);
	char * UpdateAWKLocal(const char *tmk, const char *cmk, const char *sid, const char *rnd);
	char * EnLoadAWKLocal(const char *tmk,const char *tpk,const char *sid,const char *rnd);
	char * ReadPub();
	char * EnLoadAWK(const char *sid, const char *rnd);
	char * CreateEnKeyFile();
	char * LoadAppWK(const char *appMK,const char * awk,const char *rnd);
	char * LoadAppMK(const char *cmk,const char * amk,const char *rnd);
	char * EndDF();
	char * EndMF();
	char * SimpleAddWK(const char * key);
	char * SimpleAddMK(const char * key);
	char * CreateKeyFile();
	char * CreateDF(const char * name);
	char * WritePUB(const char *sid);
	char * CreatePUB();
	char * WriteEFDIR(char * name);
	char * CreateEFDIR();
	char * CreateMF();
	char * SelectDFByName(char *filename);
	char * SelectMF();
	char * GetRnd(int num);
	CPsamCard();
	virtual ~CPsamCard();
	
};

#endif // !defined(AFX_PSAMCARD_H__5401F217_6662_4B85_B9E1_19B056CC0815__INCLUDED_)
