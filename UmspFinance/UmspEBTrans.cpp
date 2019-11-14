// UmspEBTrans.cpp: implementation of the CUmspEBTrans class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "UmspEBTrans.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmspEBTrans::CUmspEBTrans()
{
	iLogonStatus=0;
	pTermIOData=NULL;
}

CUmspEBTrans::~CUmspEBTrans()
{

}
/*��֯�װ��µ�ǩ�����ױ��ģ����ǩ������*/
int CUmspEBTrans::TrsLogon(int mode,char * ioData,int &ioLen)
{
	HDSYC8583Digram msg;
	switch(mode)
	{
	case 0://���ͽ���֮ǰ�Ĵ���
		msg.ResetDigram ();
		//����ǩ����������
			msg.InitAnalyseMap(0);
			msg.SetDevHead ("6000000001",10);
			msg.SetTransCode ("0800",4);
			msg.SetFieldValue (3-1,"960000",6);
			msg.SetFieldValue (40-1,"303031",6);
			msg.SetFieldValue (41-1,"3030303030303031",16);
			msg.SetFieldValue (61-1,"30",2);
			ioLen=msg.Generate (ioData,0);
		break;
	case 1://�յ���Ӧ֮��Ĵ���
		break;
	default:
		break;
	}
	return 1;
}

int CUmspEBTrans::TrsAccInquire(int mode,char * ioData,int &ioLen)
{
	HDSYC8583Digram msg;
	switch(mode)
	{
	case 0://���ͽ���֮ǰ�Ĵ���
		msg.ResetDigram ();
		//����ǩ����������
			msg.InitAnalyseMap(0);
			msg.SetDevHead ("6000000001",10);
			msg.SetTransCode ("0100",4);
			msg.SetFieldValue (2-1,"9999999999999999999",19);
			msg.SetFieldValue (3-1,"310000",6);
			msg.SetFieldValue (40-1,"303031",6);
			msg.SetFieldValue (41-1,"3030303030303031",16);
			msg.SetFieldValue (49-1,"313536",6);
			msg.SetFieldValue (52-1,"3030303030303031",16);
			msg.SetFieldValue (64-1,"30303030",8);
			ioLen=msg.Generate (ioData,0);
		break;
	case 1://�յ���Ӧ֮��Ĵ���
		iLogonStatus=1;
		break;
	default:
		break;
	}
	return 1;
}
/*�����ն������ģ�ȷ���������ͣ�������Ӧ���״����������Ӧ��������*/
int CUmspEBTrans::TrsEBMgr(int mode,char * ioData,int &ioLen)
{
	//�����ն˵������ģ�
	int iTrsType;
		if(mode==0)
		{
			if(ioLen<sizeof(TTermIOData))
				return -1;
			pTermIOData=(TTermIOData *)ioData;
			iTrsType=pTermIOData->mti;
		}
		else
		{
			if(memcmp(ioData+7,"\x08\x00",2)==0)
				iTrsType=0;
			else
				iTrsType=2;
		}
		switch(iTrsType)
		{
		case 0://ǩ��
			TrsLogon(mode,ioData,ioLen);
			break;
		case 1://�ɷѲ�ѯ
			break;
		case 2://����ѯ
			TrsAccInquire(mode,ioData,ioLen);
			break;
		case 3://�ɷ�
			break;
		default:
			return -1;
			break;
		}

	return 1;
}
