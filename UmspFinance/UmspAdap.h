// UmspAdap.h: interface for the CUmspAdap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_)
#define AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	���������в��֣���Ҫ������ʵ��TRANSWORK��������ʵ�ֲ�ͬ�Ľ�����������Ӧ����
	��ͬ���ϵ�ͨѶ�ӿڡ�
*/
typedef struct _THREAD_CONTROL_TBL_
{
	DWORD	dwThreadID;
	int	cliSocket;
}TRS_TBL;
class CUmspAdap  
{
public:
	CWinThread *  StartControl();
	CWinThread *  StartTrans();
	CWinThread *  StartListen();

	CUmspAdap();
	virtual ~CUmspAdap();
	
	int		igSockfd;		//�����õ��������׽���	
	static CRITICAL_SECTION sm_cs;

protected:
	virtual int TransWork()=0;
private:
	void CleanEnv();
	int ControlWork();
	int ListenWork();
	static UINT ControlThread(LPVOID pData);
	static UINT TransThread(LPVOID pData);
	static UINT ListenThread(LPVOID pData);
	void InitEnv();
public:
	void StopListen();
	CWinThread	*lsnThread;		//�����߳�
	//CWinThread	*trsThread;		//�����߳�
	CWinThread	*ctlThread;		//�����߳�
	
	CList <int,int &>csTbl;			//��Ч�Ĳ��һ�û��ʹ�õ��׽������
	CList <TRS_TBL,TRS_TBL &> curTrsTbl;
private:
	int		trsCurCount;		//�Ѿ������Ĳ���������
	int		trsMaxCount;		//�������󲢷�������
	
	
};

#endif // !defined(AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_)
