// UmspAdap.h: interface for the CUmspAdap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_)
#define AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
	适配器公有部分，需要子类来实现TRANSWORK函数，来实现不同的交易走向，生成应用于
	不同场合的通讯接口。
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
	
	int		igSockfd;		//监听得到的连接套接字	
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
	CWinThread	*lsnThread;		//监听线程
	//CWinThread	*trsThread;		//交易线程
	CWinThread	*ctlThread;		//控制线程
	
	CList <int,int &>csTbl;			//有效的并且还没有使用的套接字类表
	CList <TRS_TBL,TRS_TBL &> curTrsTbl;
private:
	int		trsCurCount;		//已经启动的并发交易数
	int		trsMaxCount;		//允许的最大并发交易数
	
	
};

#endif // !defined(AFX_UMSPADAP_H__AAEC16C7_6418_425D_AB75_5474FF201FFF__INCLUDED_)
