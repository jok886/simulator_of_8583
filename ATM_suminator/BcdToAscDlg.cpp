// BcdToAscDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yy.h"
#include "BcdToAscDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBcdToAscDlg dialog


CBcdToAscDlg::CBcdToAscDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBcdToAscDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBcdToAscDlg)
	m_bcd = _T("");
	//}}AFX_DATA_INIT
}


void CBcdToAscDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBcdToAscDlg)
	DDX_Text(pDX, edt_bcd, m_bcd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBcdToAscDlg, CDialog)
	//{{AFX_MSG_MAP(CBcdToAscDlg)
	ON_EN_CHANGE(edt_bcd, OnChangebcd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBcdToAscDlg message handlers

void CBcdToAscDlg::OnChangebcd() 
{
	UpdateData(TRUE);
	len=m_bcd.GetLength ();
	m_bcd.MakeUpper ();



	memset(hex,0,2048);
	memset(asc,0,1024);

	memcpy(hex,m_bcd,len);
	if((len%2)!=0)
	{
		hex[len]='0';
		len++;
	}
	

	AsciiToBcd(hex,asc,len/2);
	CString m_asc1;
	m_asc1.Format ("%s",asc);

	this->GetDlgItem(edt_asc)->SetWindowText(m_asc1);
}

void CBcdToAscDlg::AsciiToBcd(const char * str, char *hex, int count)
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
