// TranslateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "yy.h"
#include "TranslateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg dialog


CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTranslateDlg)
	m_bitoa = FALSE;
	m_tar = _T("");
	m_src = _T("");
	//}}AFX_DATA_INIT
}


void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTranslateDlg)
	DDX_Check(pDX, IDC_CHECK1, m_bitoa);
	DDX_Text(pDX, edt_target, m_tar);
	DDX_Text(pDX, edt_src, m_src);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialog)
	//{{AFX_MSG_MAP(CTranslateDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTranslateDlg message handlers

void CTranslateDlg::OnOK() 
{
	UpdateData(TRUE);
	int k,i,j=m_src.GetLength();
	LPCTSTR s1=(LPCTSTR)m_src;
	char	a;
	char s[4],t[1024],aaa[2];
	memset(s,0,4);
	memset(aaa,0,2);
	memset(t,0,1024);

	if(m_bitoa)
	{
		for(i=0;i<j;i+=4)
		{
			sscanf(s1+i,"%03d",&k);
			sprintf(aaa,"%c",k);
			strcat(t,aaa);
		}
	}
	else
	{
		for(i=0;i<j;i++)
		{
			a=m_src.GetAt(i);
			if(i==j-1)
				sprintf(s,"%03d",a);
			else
				sprintf(s,"%03d@",a);
			strcat(t,s);
		}
	}
	m_tar.Format("%s",t);
	UpdateData(FALSE);
}

void CTranslateDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	/*char s[4];
	sprintf(s,"%c%c",-72,-33);
	m_tar.Format("%s",s);
	UpdateData(FALSE);*/
}
