// UmspCliAdap.h: interface for the CUmspCliAdap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UMSPCLIADAP_H__B5FC7D3D_B2A2_4ADE_877B_ED2CB0FC5E4D__INCLUDED_)
#define AFX_UMSPCLIADAP_H__B5FC7D3D_B2A2_4ADE_877B_ED2CB0FC5E4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUmspCliAdap  
{
private:
	
	void InitEnv();
//property
	short	port;			//����CLI��SERVER��IP�˿�
	struct 	sockaddr_in serv_addr;	//SERVER�˵�ַ�ṹ
	struct 	sockaddr_in cli_addr;	//CLI�˵�ַ�ṹ
	
	SOCKET	lst_sock;		//�����׽���
	int  optval, optlen;		//�����׽���������
	struct linger linopt;		//�����׽���������
	char  **addrs;			
	struct hostent *hp;		
public:
	UINT ListenThread(LPVOID pParam);
	CUmspCliAdap();
	virtual ~CUmspCliAdap();

};

#endif // !defined(AFX_UMSPCLIADAP_H__B5FC7D3D_B2A2_4ADE_877B_ED2CB0FC5E4D__INCLUDED_)
