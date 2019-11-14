// HDSYC8583Digram.h: interface for the HDSYC8583Digram class.
//功能：
//	打解8583报文；内部全部使用ascii码描述的HEX字符串。
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_)
#define AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//special definanity

#define		MAX_SIZE		2048	//报文最大长度
#define		FLD_NUM			64		//字段数目

		
#define		FORMAT_SZ_EB	0		//报文类型,鉴于8583的可扩展性的衍生
#define		FORMAT_SZ_POSP	1	
	
#include "..\Des.h"
class HDSYC8583Digram  
{
private:
	int WriteAllFldValByBmp(char * obj);
	int SetLengthHead(const char *,int len);
	int SetBitmap(int index);
	int WriteCertainFieldVal(char *obj,int index);
	int ClearBitmap(int index);
	int WriteAllFldVal(char *obj);
	int WriteBitmap(char *obj);
	int WriteTransCode(char *obj);
	int WriteDeviceHead(char *obj);
	void ClearDigram();
	int SnapAllFieldValue();
	int ParseBitmap();
	int SnapBitmap();
	int	SnapTransCode();
	int		SnapDeviceHead	(										);
	int		SnapDigramLength(										);//获取长度
	
	void	CharToHex		(char c,char *h							);
	int		ToInnerDigram	(const char *newVal,int len				);
	int		InitAnalyseMap	(int type								);
	

//property
	int	iType;
	char	*strDigram			;//报文
	int		iDigramLen			;//报文长度
	int		iAnalyseMap[FLD_NUM];//报文分析参考图 

	char	*strLength			;//报文长度
	char	*strDevHead			;//设备头
	char	*strTransCd			;//交易码
	char	*strBitmap			;//位元表
	char	*strFldVal[FLD_NUM]	;//域值
	int		iFldLen[FLD_NUM]	;//域长度

	unsigned char strPinKey[8]	;
	unsigned char strMacKey[8]	;	

	int		curpos				;//当前指针

private :int ToOutDigram(char *res);
	int CalMAC(const char * src,int len,char * res);
	char macData[1000];
	char * GetDateTime();
	void FillFldByTrnCd();
public:	
	int GetPassword(char *res);
	int ReplyGenerate(const char *digram8583, int len,int type,char * res);
	int		SetBitmap		(const char * newVal,int len			);
	int Generate(char * res,int type,char * bmp);
	BOOL IsExistDomin(int iIndex);
	int GetLengthHead(char * res);
	int GetDeviceHead(char *res);
	int		SetDevHead		(const char * newVal,int len			);
	void	ResetDigram		(										);//复位
	int		SetTransCode	(const char * newVal,int len			);
	int		GetBitmap		(char *res								);
	int		GetTransCode	(char *res								);
//method
	void	ClearField		(int index								);//清除指定位
	int		Parse			(const char *digram8583,int len,int type);//解析8583报文
	int		Generate		(char *res,int type					);//生成8583报文	
	int		GetFieldValue	(int index,char * res					);//取index号字段值
	int		SetFieldValue	(int index,const char *newVal,int len	);//设index号字段值

			HDSYC8583Digram	(										);
	virtual ~HDSYC8583Digram(										);

};

#endif // !defined(AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_)
