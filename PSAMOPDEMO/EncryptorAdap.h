// EncryptorAdap.h: interface for the CEncryptorAdap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCRYPTORADAP_H__0212B76C_D7B3_465E_AF4C_EE9A25176C59__INCLUDED_)
#define AFX_ENCRYPTORADAP_H__0212B76C_D7B3_465E_AF4C_EE9A25176C59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char u8;
typedef struct 
{
	u8 cmd[2];		//05 55	
	u8 ickeyindex[2];	//0001
	u8 zmkindex[2];		//0001
	u8 pinfmt_pre;		//0x01
	u8 pinfmt_nxt;		//0x01
	u8 pik[8];		//tak
	u8 pinblock[8];		//enpin
	u8 divnum;		//0x01-0x03
	u8 session_enable;	//0x01
	u8 sid[8];		//sid
	u8 rnd[8];		//rnd
	u8 acco[19];		//all 0x00
} StruCmd0555In;

typedef struct
{
	u8 code;
	u8 pin[8];
}StruCmd0555Out;

typedef struct 
{
	u8 cmd[2];		//b0 9b
	u8 reserver[8];		//...
	u8 tpkindex[2];		//0001
	u8 tmkindex[2];		//0001
	
	u8 tpklen;		//0x01 128 0x00 64
	u8 tmklen;		//
	u8 tpklenused;		//0x01 0x00
	u8 tpktmpflag;		//0x00
	u8 divnum_tpk;		//0x01-0x03
	u8 divnum_tmk;		//0x01-0x03
	
	u8 cmdheadlen;
	u8 keypropertylen;
	u8 areacdlen;
	
	u8 macvector[8];
	u8 sid[8];		//sid
	
	u8 cmdhead[5];
	u8 keyproperty[7];
	
	
	u8 areacd[8];		
} StruCmdb09bIn;

typedef struct
{
	u8 code;
	u8 reserver[8];
	u8 len[2];
	u8 data[2048];
}StruCmdb09bOut;



typedef struct
{
	u8	cmd[2];					//5a

	u8	ttkdivnum;				//0 1 2 3
	u8	ttkver;					//ttk版本
	u8	ttkgrp[2];				//ttk组号
	u8	ttkidx[2];				//ttk索引
	u8	ttkdivcnt[16*3];		//ttk离散因子

	u8	tmkdivnum;				//0 1 2 3
	u8	tmkver;					//tmk版本
	u8	tmkgrp[2];				//tmk组号
	u8	tmkidx[2];				//tmk索引
	u8	tmkdivcnt[16*3];		//tmk离散因子

	u8	key_head_len[2];		//离散密钥前缀长度/2
	u8	key_head_cnt[1024];		//离散密钥前缀
	u8	key_tail_len[2];		//离散密钥后缀长度/2
	u8	key_tail_cnt[1024];		//离散密钥后缀

	u8	mac_vector[16];			//mac初始化向量
	u8	mac_head_len[2];		//mac前缀长度/2
	u8	mac_head_cnt[1024];		//mac前缀

}StruCmd565AIn;
typedef struct
{
	u8	rsp[2];					//response code
	u8	errcd[2];				//err code
	u8	endata[1024];			//endata
	u8	mac[8];					//mac
}StruCmd565AOut;

#include "SockConn.h"
class CEncryptorAdap  
{
public:
	int GenICAppKey(const char *sid,const char *vector,const char *cmdhead,const char *keyattr, char *resval);
	CString strIP;
	int iPort;
	int tmkidx,tpkidx;
	int ChangePinFormat(const char * term_en_pin,const char * sid,const char * rnd,const char * tak,char * bank_en_pin);
	CEncryptorAdap();
	virtual ~CEncryptorAdap();
	
};

#endif // !defined(AFX_ENCRYPTORADAP_H__0212B76C_D7B3_465E_AF4C_EE9A25176C59__INCLUDED_)
