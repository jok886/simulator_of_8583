// DesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rs232tcpadaptor.h"
#include "DesDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDesDlg dialog


CDesDlg::CDesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDesDlg)
	m_key = _T("3131313131313131");
	m_src = _T("4FD96EC0D3304EF6");
	m_tag = _T("0000000000000000");
	//}}AFX_DATA_INIT
}


void CDesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDesDlg)
	DDX_Text(pDX, EDT_KEY, m_key);
	DDX_Text(pDX, EDT_SRC, m_src);
	DDX_Text(pDX, EDT_TAG, m_tag);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDesDlg, CDialog)
	//{{AFX_MSG_MAP(CDesDlg)
	ON_BN_CLICKED(BTN_ENCODE, OnEncode)
	ON_BN_CLICKED(BTN_ENCRY, OnEncry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void AsciiToBcd(const char *str, unsigned char *hex, int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        hex[i] = ((str[i * 2] <= 0x39) ? str[i * 2] - 0x30 
                                       : str[i * 2] - 0x41 + 10);
        hex[i] = hex[i] << 4;
        hex[i] += ((str[i * 2 + 1] <= 0x39) ? str[i * 2 + 1] - 0x30
                                       : str[i * 2 + 1] - 0x41 + 10);
    }
}
unsigned char ToHex(unsigned char c)
{
	unsigned char tmp1=c;
	if(tmp1<=9 && tmp1>=0)
		tmp1+='0';
	else if(tmp1<=15 && tmp1>=10)
		tmp1+='A'-10;
	else
		tmp1='0';
	return tmp1;
}
unsigned char IsBmp1InBmp2(unsigned char * bmp1,unsigned char *bmp2,unsigned char len)
{
	unsigned char i,j,k,l;
	
	for(i=0;i<len;i++)
	{
		if((*(bmp1+i))!=((*(bmp1+i))&(*(bmp2+i))))
		{
			j=(*(bmp1+i))^((*(bmp1+i))&(*(bmp2+i)));
			k=0x80;
			for(l=0;l<8;l++)
			{
				if((j&(k>>l))!=0)
					return i*8+l+1;	//BMP1有的位，在BMP2中无
			}
		}
	}
	return 0;//BMP1中有的位，BMP2中全部有
}
void BcdToAscii(const char *hex, unsigned char *str, int count)
{
   int i;
	unsigned char t;
    for(i=0;i<count;i++)
    {
		t=(hex[i]&(0xf0));
		t=t>>4;
        str[2*i]=ToHex(t );
		t=(hex[i]&(0x0f));
		str[2*i+1]=ToHex(t);		
    }
}
extern unsigned char IsBmp1InBmp2(unsigned char * bmp1,unsigned char *bmp2,unsigned char len);
/////////////////////////////////////////////////////////////////////////////
// CDesDlg message handlers
void CDesDlg::OnEncode() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDes des;
	char dg[8],out[8],key[8];
	unsigned char tmp[17];
	memset(tmp,0,17);
	unsigned char udg[8],uout[8],ukey[8];
	AsciiToBcd(m_key,ukey,8);
	memset(key,31,8);
	AsciiToBcd(m_src,udg,8);
	//memcpy(udg,dg,8);
	//memcpy(ukey,key,8);
	//memcpy(uout,out,8);
	des.EnCode (udg,uout,ukey);
	memcpy(dg,udg,8);
	memcpy(key,ukey,8);
	memcpy(out,uout,8);
	BcdToAscii(out,tmp,8);
	m_tag.Format("%s",tmp);
	UpdateData(FALSE);

	unsigned char b1[9]="11111111";
	unsigned char b2[9]="32222222";

	AsciiToBcd(m_key,b1,8);
	AsciiToBcd(m_src,b2,8);
	
	int i=IsBmp1InBmp2(b1,b2,8);
	//3,4,8,11,12,16,19,20,24,27,28,32,35,36,40,43,44,48,51,52,56,59,60,64,
	//3,4,7,8,11,12,15,19,20,23,27,28,31,35,36,39,43,44,47,51,52,55,59,60,63,
	CString strTmp;
	strTmp.Format("第%d位不被包含",i);
	AfxMessageBox(strTmp);

}

void CDesDlg::OnEncry() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDes des;
	char dg[8],out[8],key[8];
	unsigned char tmp[17];
	memset(tmp,0,17);
	unsigned char udg[8],uout[8],ukey[8];
	AsciiToBcd(m_key,ukey,8);
	AsciiToBcd(m_src,udg,8);
	//memcpy(udg,dg,8);
	//memcpy(ukey,key,8);
	//memcpy(uout,out,8);
	des.DeCode (udg,uout,ukey);
	memcpy(dg,udg,8);
	memcpy(key,ukey,8);
	memcpy(out,uout,8);
	BcdToAscii(out,tmp,8);
	m_tag.Format("%s",tmp);
	UpdateData(FALSE);
}
