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
#define		FORMAT_GD_POS	0		//��������,����8583�Ŀ���չ�Ե�����
#define		FORMAT_GD_ATMP	1
#define		FORMAT_AZ_ST360	2
#define		FORMAT_MASTER	2		

class HDSYC8583Digram  
{
private:
	int ParseBitmap();
	int SetLengthHead(const char *,int len);
	int WriteCertainFieldVal(char *obj,int index);
	int ClearBitmap(int index);
	int SetBitmap(int index);
	int WriteAllFldVal(char *obj);
	int WriteBitmap(char *obj);
	int WriteTransCode(char *obj);
	int WriteDeviceHead(char *obj);
	void ClearDigram();
	int SnapAllFieldValue();
	int SnapBitmap();
	int	SnapTransCode();
	int		SnapDeviceHead	(										);
	int		SnapDigramLength(										);//��ȡ����
	int		ToOutDigram		(char *res								);
	void	CharToHex		(char c,char *h							);
	int		ToInnerDigram	(const char *newVal,int len				);
	int		InitAnalyseMap	(int type								);
	int		SetBitmap		(const char * newVal,int len			);

//property
	char	*strDigram			;//����
	int		iDigramLen			;//���ĳ���
	int		iAnalyseMap[FLD_NUM];//���ķ����ο�ͼ 

	char	*strLength			;//���ĳ���
	char	*strDevHead			;//�豸ͷ
	char	*strTransCd			;//������
	char	*strBitmap			;//λԪ��
	char	*strFldVal[FLD_NUM]	;//��ֵ
	int		iFldLen[FLD_NUM]	;//�򳤶�


	int		curpos				;//��ǰָ��
public:	
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
