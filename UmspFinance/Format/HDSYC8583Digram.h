// HDSYC8583Digram.h: interface for the HDSYC8583Digram class.
//���ܣ�
//	���8583���ģ��ڲ�ȫ��ʹ��ascii��������HEX�ַ�����
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_)
#define AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//special definanity

#define		MAX_SIZE		2048	//������󳤶�
#define		FLD_NUM			64		//�ֶ���Ŀ

		
#define		FORMAT_SZ_EB	0		//��������,����8583�Ŀ���չ�Ե�����
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
	int		SnapDigramLength(										);//��ȡ����
	
	void	CharToHex		(char c,char *h							);
	int		ToInnerDigram	(const char *newVal,int len				);
	int		InitAnalyseMap	(int type								);
	

//property
	int	iType;
	char	*strDigram			;//����
	int		iDigramLen			;//���ĳ���
	int		iAnalyseMap[FLD_NUM];//���ķ����ο�ͼ 

	char	*strLength			;//���ĳ���
	char	*strDevHead			;//�豸ͷ
	char	*strTransCd			;//������
	char	*strBitmap			;//λԪ��
	char	*strFldVal[FLD_NUM]	;//��ֵ
	int		iFldLen[FLD_NUM]	;//�򳤶�

	unsigned char strPinKey[8]	;
	unsigned char strMacKey[8]	;	

	int		curpos				;//��ǰָ��

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
	void	ResetDigram		(										);//��λ
	int		SetTransCode	(const char * newVal,int len			);
	int		GetBitmap		(char *res								);
	int		GetTransCode	(char *res								);
//method
	void	ClearField		(int index								);//���ָ��λ
	int		Parse			(const char *digram8583,int len,int type);//����8583����
	int		Generate		(char *res,int type					);//����8583����	
	int		GetFieldValue	(int index,char * res					);//ȡindex���ֶ�ֵ
	int		SetFieldValue	(int index,const char *newVal,int len	);//��index���ֶ�ֵ

			HDSYC8583Digram	(										);
	virtual ~HDSYC8583Digram(										);

};

#endif // !defined(AFX_HDSYC8583DIGRAM_H__152D9332_ACB3_40F5_B0AC_8E20A170E442__INCLUDED_)
