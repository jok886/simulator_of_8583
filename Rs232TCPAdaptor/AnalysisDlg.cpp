// AnalysisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "rs232tcpadaptor.h"
#include "AnalysisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg dialog


CAnalysisDlg::CAnalysisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnalysisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnalysisDlg)
	m_iBitsNum	= 64;
	m_strParams = _T("");
	m_strResult = _T("");
	//}}AFX_DATA_INIT
	hexData=(unsigned char *)malloc(8*sizeof(unsigned char));
	memset(hexData,0,8);
}



void CAnalysisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnalysisDlg)
	DDX_Text(pDX, EDT_BITS, m_iBitsNum);
	DDX_Text(pDX, EDT_INDATA, m_strParams);
	DDX_Text(pDX, EDT_RESULT, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnalysisDlg, CDialog)
	//{{AFX_MSG_MAP(CAnalysisDlg)
	ON_BN_CLICKED(BTN_GEN, OnGen)
	ON_BN_CLICKED(BTN_PARSEL, OnParsel)
	ON_EN_CHANGE(EDT_BITS, OnChangeBits)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalysisDlg message handlers

void CAnalysisDlg::OnGen() 
{
	// TODO: Add your control notification handler code here
	int a[128];
	int i,j,k;
	CString tmp;
	TCHAR c;
	i=0;j=0;k=0;
	UpdateData();
	for(i;i<m_strParams.GetLength ();i++)
	{
		c=m_strParams.GetAt (i);
		if((c<='9'&&c>='0')||c==',')
		{
			if(c==',')
				continue;
			for(j=i;j<m_strParams.GetLength ();j++)
			{
				if(m_strParams.GetAt (j)==',')
					break;
			}
			tmp=m_strParams.Mid (i,j-i);
			sscanf(tmp,"%d",&a[k]);k++;i=j;
		}
		else
		{
			break;
		}
	}
	memset(hexData,0,m_iBitsNum/8);
	for(i=0;i<k;i++)
	{
		SetBit(a[i]);
	}
	tmp.Empty ();
	m_strResult.Empty ();
	for(i=0;i<m_iBitsNum/8;i++)
	{
		tmp.Format ("%02X",hexData[i]);
		m_strResult+=tmp;
	}
	UpdateData(FALSE);
}

void CAnalysisDlg::OnParsel() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	memset(hexData,0,m_iBitsNum/8);
	int j=0;
	for(int i=0;i<m_strParams.GetLength (); i+=2)
	{
		sscanf(((LPCTSTR)m_strParams)+i,"%02X",&hexData[j]);
		j++;
	}
	CString tmp;
	m_strResult.Empty ();
	for(i=1;i<=64;i++)
	{
		if(IsBitExsit(i))
		{
			tmp.Format ("%d,",i);
			m_strResult+=tmp;
		}
	}
	UpdateData(FALSE);
}

void CAnalysisDlg::SetBit(int index)
{
	if(hexData==NULL||index>m_iBitsNum||index<=0)
		return;
	unsigned char c=0x80;
	int i=index-1;
	hexData[i/8]|=c>>(i%8);
}

BOOL CAnalysisDlg::IsBitExsit(int index)
{
	if(hexData==NULL)
		return FALSE;
	unsigned char c=0x80;
	int i=index-1;
	return ((hexData[i/8])&(c>>(i%8)))!=0;
}

void CAnalysisDlg::OnChangeBits() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	UpdateData();
	free(hexData);
	hexData=(unsigned char *)malloc((m_iBitsNum/8 +1)*sizeof(unsigned char));
}
