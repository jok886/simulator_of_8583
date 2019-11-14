// TransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "pos.h"
#include "TransDlg.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog


CTransDlg::CTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTransDlg)
	m_digramhex = _T("");
	m_strPrompt = _T("");
	m_Write = FALSE;
	m_strMy = _T("");
	//}}AFX_DATA_INIT
	dlg=NULL;
}


void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransDlg)
	DDX_Text(pDX, EDT_DIRAM, m_digramhex);
	DDX_Text(pDX, EDT_PROMPT, m_strPrompt);
	DDX_Check(pDX, IDC_CHECK1, m_Write);
	DDX_Text(pDX, EDT_DIRAM2, m_strMy);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransDlg, CDialog)
	//{{AFX_MSG_MAP(CTransDlg)
	ON_BN_CLICKED(BTN_EXIT, OnExit)
	ON_WM_CHAR()
	ON_BN_CLICKED(BTN_OPTION, OnOption)
	ON_BN_CLICKED(BTN_LSTN, OnLstn)
	ON_BN_CLICKED(BTN_PARS, OnPars)
	ON_BN_CLICKED(BTN_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(BTN_GENERATE, OnGenerate)
	ON_CONTROL_RANGE(EN_SETFOCUS, EDT_FLD_01, EDT_FLD_64, OnSetfocusFldX)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(BTN_SEND, OnSend)
	ON_EN_CHANGE(EDT_FLD_01, OnChangeFld01)
	//}}AFX_MSG_MAP
	ON_MESSAGE(PARSLE,ParsleDigram)
	ON_MESSAGE(TEST_HDSY,CCCCC)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransDlg message handlers

void CTransDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CTransDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CTransDlg::OnOption() 
{
	// TODO: Add your control notification handler code here
	if(dlg==NULL)
	{
		dlg=new COptionDlg;
		dlg->Create(DLG_OPTION,this);
	}
	dlg->ShowWindow (SW_SHOW);
}



DWORD WINAPI ClientThread(LPVOID lpParam)
{
	struct InData *inData=(struct InData *)lpParam;
    SOCKET        sock=inData->s ;
    char          szBuff[1024];
    int           ret=0;

	memset (szBuff,0,1024);
    ret = recv(sock, szBuff, 1024, 0);
    if (ret == 0||ret == SOCKET_ERROR)
        return 1;
	inData->len =ret;
	memset(inData->digram ,0,1024);
	memcpy(inData->digram ,szBuff,ret);
	SendMessage(inData->hWnd ,PARSLE,NULL,NULL);
	
    return 0;
}
DWORD WINAPI ClientListen(LPVOID lpParam)
{
	struct	InData *	inData=(struct InData *)lpParam;
	CString			sMsg;
	char			szAddress[128];
	SOCKET			sClient;
	int			iAddrSize;
	short			iPort;
	HANDLE			hThread;
	DWORD			dwThreadId;
	struct sockaddr_in	local,client;

    inData->sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	SOCKET sListen=inData->sListen;
    if (sListen == SOCKET_ERROR)
    {
        sMsg.Format ("socket() failed: %d\n", WSAGetLastError());
		AfxMessageBox(sMsg);
        return 1;
    }
    // Select the local interface, and bind to it
    //
	
	strcpy(szAddress,"192.168.0.79");
	iPort=5819;

    local.sin_addr.s_addr = htonl(INADDR_ANY);
    local.sin_family = AF_INET;
    local.sin_port = htons(iPort);

    if (bind(sListen, (struct sockaddr *)&local, 
            sizeof(local)) == SOCKET_ERROR)
    {
        sMsg.Format("bind() failed: %d\n", WSAGetLastError());
		AfxMessageBox(sMsg);
        return 1;
    }
    listen(sListen, 8);
    //
    // In a continuous loop, wait for incoming clients. Once one 
    // is detected, create a thread and pass the handle off to it.
    //
    while (1)
    {
        iAddrSize = sizeof(client);
        sClient = accept(sListen, (struct sockaddr *)&client,
                        &iAddrSize);        
        if (sClient == INVALID_SOCKET)
        {        
            sMsg.Format("accept() failed: %d\n", WSAGetLastError());
			AfxMessageBox(sMsg);
            break;
        }
        //sMsg.Format ("Accepted client: %s:%d\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		//AfxMessageBox(sMsg);
		inData->s =sClient;
		

        hThread = CreateThread(NULL, 0, ClientThread, 
                    (LPVOID)inData, 0, &dwThreadId);
        if (hThread == NULL)
        {
            sMsg.Format("CreateThread() failed: %d\n", GetLastError());
			AfxMessageBox(sMsg);
            break;
        }
        CloseHandle(hThread);
    }
    closesocket(sListen);
	return 0;
}
void CTransDlg::ParsleDigram()
{
//	CString sMsg;
/////////////////////////////
	char 	t[2048];
	memset(t,0,2048);
	BcdToAscii(inData.digram ,t,inData.len );

	m_digramhex.Format ("%s",t);
	UpdateData(FALSE);
	OnSend();
////////////////////////////
//	AfxMessageBox(sMsg);
}
void CTransDlg::CCCCC ()
{
	static int i;
	static CString t;
	CString str;
	if(t.IsEmpty ())
		this->GetWindowText (t);
	str.Format ("%s  %03d",t,i);
	i++;
	this->SetWindowText (str);
}
void CTransDlg::OnLstn() 
{
	CWnd *pW=
		this->GetDlgItem(BTN_LSTN);
	pW->EnableWindow (FALSE);
	CString sMsg;
	DWORD         dwThreadId;
	inData.hWnd =this->m_hWnd ;
	
	HANDLE hThread = CreateThread(NULL, 0, ClientListen, 
                (LPVOID)&inData, 0, &dwThreadId);
    if (hThread == NULL)
    {
        sMsg.Format("ClientListen() failed: %d\n", GetLastError());
		AfxMessageBox(sMsg);
		return;
    }
    CloseHandle(hThread);
}
void CTransDlg::AsciiToBcd(const char * str, char *hex, int count)
{
    int i;
	count=(count+1)/2;
    for(i=0;i<count;i++)
    {
        hex[i] = ((str[i * 2] <= 0x39) ? str[i * 2] - 0x30 
                                       : str[i * 2] - 0x41 + 10);
        hex[i] = hex[i] << 4;
        hex[i] += ((str[i * 2 + 1] <= 0x39) ? str[i * 2 + 1] - 0x30
                                       : str[i * 2 + 1] - 0x41 + 10);
    }
}
void CTransDlg::BcdToAscii(const char * hex, char *str, int count)
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

char CTransDlg::ToHex(char c)
{
	char tmp1=c;
	if(tmp1<=9 && tmp1>=0)
		tmp1+='0';
	else if(tmp1<=15 && tmp1>=10)
		tmp1+='A'-10;
	else
		tmp1='0';
	return tmp1;
}

void CTransDlg::OnPars() 
{
	InitDisplay();
	// TODO: Add your control notification handler code here
	/*
	C8583PosDigram posDigram;
	posDigram.len =inData.len ;
	strcpy(posDigram.digram,m_digramhex);
	posDigram.Parse ();
	
	//
	CWnd *pWnd=NULL;
	CString str;
	for(int i=0;i<64;i++)
	{		
		if(posDigram.GetFldValue(i+1)!=NULL)
		{
			str.Format ("%s",posDigram.GetFldValue(i+1));
			pWnd=this->GetDlgItem (5819+i+1);
			if(pWnd!=NULL)
				pWnd->SetWindowText(str);
		}
	}
	//
	pWnd=this->GetDlgItem (EDT_FLD_00);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.xxm);
	pWnd=this->GetDlgItem (EDT_FLD_01);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.Bitmap);
	pWnd=this->GetDlgItem (EDT_FLD_F2);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.Len);
	pWnd=this->GetDlgItem (EDT_FLD_F1);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.NacHead );*/
	posDigram.ResetDigram ();
	UpdateData(TRUE);
	if(inData.len >0)
		posDigram.Parse (inData.digram ,inData.len ,2);
	else
		posDigram.Parse(m_strMy,m_strMy.GetLength (),2);
	CWnd *pWnd=NULL;
	char buf[1024];
	int len;
	CString str;
	for(int i=0;i<64;i++)
	{	
		memset(buf,0,1024);
		len=posDigram.GetFieldValue (i,buf);
		if(len>0)
		{
			str.Format ("%s",buf);
			pWnd=this->GetDlgItem (5819+i+1);
			if(pWnd!=NULL)
				pWnd->SetWindowText(str);
		}
	}
	memset(buf,0,1024);
	posDigram.GetBitmap (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_01)->SetWindowText(str);

	memset(buf,0,1024);
	posDigram.GetTransCode (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_00)->SetWindowText(str);

	memset(buf,0,1024);
	posDigram.GetDeviceHead (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_F1)->SetWindowText(str);

	memset(buf,0,1024);
	posDigram.GetLengthHead(buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_F2)->SetWindowText(str);
}

void CTransDlg::OnDisconnect() 
{
	// TODO: Add your control notification handler code here
	closesocket(inData.sListen);
	CWnd *pWnd=NULL;
	pWnd=this->GetDlgItem (BTN_LSTN);
	pWnd->EnableWindow(TRUE);
}

void CTransDlg::InitDisplay()
{
	CWnd *pWnd=NULL;
	for(int i=-2;i<=64;i++)
	{
		pWnd=this->GetDlgItem (5819+i);
		if(pWnd!=NULL)
			pWnd->SetWindowText("");
	}
}

void CTransDlg::OnGenerate() 
{
/*	C8583PosDigram posDigram;
	posDigram.len =inData.len ;
	strcpy(posDigram.digram,m_digramhex);
	posDigram.Parse ();
	
	//
	CWnd *pWnd=NULL;
	CString str;
	for(int i=0;i<64;i++)
	{		
		if(posDigram.GetFldValue(i+1)!=NULL)
		{
			str.Format ("%s",posDigram.GetFldValue(i+1));
			pWnd=this->GetDlgItem (5819+i+1);
			if(pWnd!=NULL)
				pWnd->SetWindowText(str);
		}
	}
	//
	pWnd=this->GetDlgItem (EDT_FLD_00);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.xxm);
	pWnd=this->GetDlgItem (EDT_FLD_01);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.Bitmap);
	pWnd=this->GetDlgItem (EDT_FLD_F2);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.Len);
	pWnd=this->GetDlgItem (EDT_FLD_F1);
	if(pWnd!=NULL)
		pWnd->SetWindowText (posDigram.NacHead );*/
	posDigram.ResetDigram ();
	CWnd *pWnd=NULL;
	CString str;
	pWnd=this->GetDlgItem (EDT_FLD_F1);
	if(pWnd!=NULL)
		pWnd->GetWindowText (str);
	posDigram.SetDevHead (str,str.GetLength ());

	pWnd=this->GetDlgItem (EDT_FLD_00);
	if(pWnd!=NULL)
		pWnd->GetWindowText (str);
	posDigram.SetTransCode (str,str.GetLength ());
	for(int i=1;i<64;i++)
	{		
		pWnd=this->GetDlgItem (5819+i+1);
		if(pWnd!=NULL)
		{
			pWnd->GetWindowText(str);
			posDigram.SetFieldValue (i,str,str.GetLength ());
		}
		pWnd=NULL;
	}
	char buf[2024],buf1[4096];
	memset(buf1,0,4096);
	int ll=0;
	memset(buf,0,2024);
	ll=posDigram.Generate (buf,0);
	BcdToAscii(buf,buf1,ll);
	str.Format ("%s",buf1);
	this->GetDlgItem(EDT_DIRAM2)->SetWindowText(str);

	memset(buf,0,2024);
	posDigram.GetBitmap (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_01)->SetWindowText(str);

	memset(buf,0,2024);
	posDigram.GetTransCode (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_00)->SetWindowText(str);

	memset(buf,0,2024);
	posDigram.GetDeviceHead (buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_F1)->SetWindowText(str);

	memset(buf,0,2024);
	posDigram.GetLengthHead(buf);
	str.Format ("%s",buf);
	this->GetDlgItem (EDT_FLD_F2)->SetWindowText(str);
}

void CTransDlg::OnSetfocusFldX() 
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Empty ();
	if(m_Write)
	{
		this->GetDlgItem (EDT_PROMPT)->GetWindowText (str);
		char hex[1024];
		memset(hex,0,1024);
		BcdToAscii(str,hex,str.GetLength ());
		str.Empty ();
		str.Format ("%s",hex);
		this->GetFocus()->SetWindowText (str);
	}
	else
	{
		this->GetFocus()->GetWindowText (str);
		char hex[1024];
		memset(hex,0,1024);
		AsciiToBcd(str,hex,str.GetLength ());
		str.Empty ();
		str.Format ("%s",hex);
		this->GetDlgItem (EDT_PROMPT)->SetWindowText (str);
	}
}

void CTransDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	m_Write=!m_Write;
	CWnd *pWnd=NULL;
	for(int i0=0;i0<64;i0++)
	{
		pWnd=this->GetDlgItem (5819+i0+1);
		if(pWnd!=NULL)
			pWnd->EnableWindow(1);
	}
	this->SendMessage(TEST_HDSY);
}

void CTransDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	CString str;
	this->GetDlgItem(EDT_DIRAM2)->GetWindowText(str);
	char hex[1024];
	memset(hex,0,1024);
	memset(hex,0x02,1);
	AsciiToBcd(str,hex+1,str.GetLength ());
	memset(hex+1+str.GetLength ()/2,0x03,1);
	BYTE c=0;
	for(int i=1;i<=2+str.GetLength ()/2;i++)
	{
		c^=hex[i];
	}
	memset(hex+2+str.GetLength ()/2,c,1);
	send(inData.s,hex,str.GetLength ()/2+3,0);
	closesocket(inData.s );
	//send(inData.s ,,13,0);
}

void CTransDlg::OnChangeFld01() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	char strBitmap[17];memset(strBitmap,0,17);
	this->GetDlgItem (EDT_FLD_01)->GetWindowText(strBitmap,17);
	if(strlen(strBitmap)!=16)
		return;
	int iFldLen[64];
	unsigned char tmp,j;
	int i,k;
	for(i=0;i<16;i++)
	{
		j=0x08;
		tmp=*(strBitmap+i);
		if(tmp<'0'||tmp>'F'||(tmp>'9'&&tmp<'A'))
		{
			return ;		//invalid bitmap;
		}
		else
		{
			if(tmp<='9'&&tmp>='0')
				tmp-=0x30;
			else
				tmp-=0x37;
		}
		for(k=0;k<4;k++)
		{
			if(tmp&j)
			{
				iFldLen[i*4+k]=1;
								
			}
			else
				iFldLen[i*4+k]=0;
			j>>=1;
		}
	}
	CWnd *pWnd=NULL;
	for(int i0=0;i0<64;i0++)
	{
		pWnd=this->GetDlgItem (5819+i0+1);
		if(pWnd!=NULL)
			pWnd->EnableWindow(iFldLen[i0]);
	}
	return ;	
}
