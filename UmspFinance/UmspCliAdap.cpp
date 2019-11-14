// UmspCliAdap.cpp: implementation of the CUmspCliAdap class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UmspFinance.h"
#include "UmspCliAdap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUmspCliAdap::CUmspCliAdap()
{

}

CUmspCliAdap::~CUmspCliAdap()
{

}
/*
	初始化参数和本类的运行环境
*/
void CUmspCliAdap::InitEnv()
{
	port=5819;	
	memset ((char *)&cli_addr, 0x00, sizeof(struct sockaddr_in) );
	memset ((char *)&serv_addr, 0x00, sizeof(struct sockaddr_in) );
}

UINT CUmspCliAdap::ListenThread(LPVOID pParam)
{
	return 0;
}
