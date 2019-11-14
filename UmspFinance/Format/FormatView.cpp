// FormatView.cpp : implementation of the CFormatView class
//

#include "stdafx.h"
#include "Format.h"

#include "FormatDoc.h"
#include "FormatView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatView

IMPLEMENT_DYNCREATE(CFormatView, CListView)

BEGIN_MESSAGE_MAP(CFormatView, CListView)
	//{{AFX_MSG_MAP(CFormatView)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(TB_ADD, OnAdd)
	ON_COMMAND(TB_DEL, OnDel)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_CHAR()
	ON_COMMAND(TB_UPDATE, OnUpdate)
	ON_COMMAND(TB_START_SERVICE, OnStartService)
	ON_UPDATE_COMMAND_UI(TB_START_SERVICE, OnUpdateStartService)
	ON_COMMAND(TB_STOP_SERVICE, OnStopService)
	ON_UPDATE_COMMAND_UI(TB_STOP_SERVICE, OnUpdateStopService)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
	ON_MESSAGE(ADDITEM,AddItem)
	ON_MESSAGE(TRS_MSG_UPDATE,OnUpdateList)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatView construction/destruction
CliMsg CFormatView::cliMsg;

CFormatView::CFormatView()
{
	// TODO: add construction code here
	bEnable=TRUE;
	dlg=NULL;
	msgdlg=NULL;
	thdListen=NULL;
	bHost=TRUE;
}

CFormatView::~CFormatView()
{
}

BOOL CFormatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style |= LVS_REPORT     |
			 LVS_SINGLESEL     |
			 LVS_SHOWSELALWAYS |
			 LVS_ICON          ;
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFormatView drawing

void CFormatView::OnDraw(CDC* pDC)
{
	CFormatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CFormatView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	GyInit();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CFormatView printing

BOOL CFormatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFormatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFormatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFormatView diagnostics

#ifdef _DEBUG
void CFormatView::AssertValid() const
{
	CListView::AssertValid();
}

void CFormatView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CFormatDoc* CFormatView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFormatDoc)));
	return (CFormatDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormatView message handlers

void CFormatView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	bSortAscending = !bSortAscending;
	SortTextItems(phdn->iButton , bSortAscending, 0, -1 );
	*pResult = 0;
}

BOOL CFormatView::SortTextItems(int nCol, BOOL bAscending, int low, int high)
{
	CListCtrl &theCtrl=this->GetListCtrl ();
	if( nCol >= ((CHeaderCtrl*)GetDlgItem(0))->GetItemCount() )
		return FALSE;

		if( high == -1 ) high = theCtrl.GetItemCount() - 1;

		int lo = low;
		int hi = high;
		CString midItem;

		if( hi <= lo ) return FALSE;

		midItem = theCtrl.GetItemText( (lo+hi)/2, nCol );

		// loop through the list until indices cross
		while( lo <= hi )
		{
			// rowText will hold all column text for one row
			CStringArray rowText;

			// find the first element that is greater than or equal to?
			// the partition element starting from the left Index.
			if( bAscending )
				while( ( lo < high ) && ( theCtrl.GetItemText(lo, nCol) < midItem ) )
					++lo;
			else
				while( ( lo < high ) && ( theCtrl.GetItemText(lo, nCol) > midItem ) )
					++lo;

			// find an element that is smaller than or equal to?
			// the partition element starting from the right Index.
			if( bAscending )
				while( ( hi > low ) && ( theCtrl.GetItemText(hi, nCol) > midItem ) )
					--hi;
			else
				while( ( hi > low ) && ( theCtrl.GetItemText(hi, nCol) < midItem ) )
					--hi;

			// if the indexes have not crossed, swap
			// and if the items are not equal
			if( lo <= hi )
			{
				// swap only if the items are not equal
				if( theCtrl.GetItemText(lo, nCol) != theCtrl.GetItemText(hi, nCol))
				{
					// swap the rows
					LV_ITEM lvitemlo, lvitemhi;
					int nColCount =
						((CHeaderCtrl*)GetDlgItem(0))->GetItemCount();
					rowText.SetSize( nColCount );
					int i;
					for( i=0; i<nColCount; i++)
						rowText[i] = theCtrl.GetItemText(lo, i);
					lvitemlo.mask = LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
					lvitemlo.iItem = lo;
					lvitemlo.iSubItem = 0;
					lvitemlo.stateMask = LVIS_CUT | LVIS_DROPHILITED |
							LVIS_FOCUSED | LVIS_SELECTED |
							LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK;

					lvitemhi = lvitemlo;
					lvitemhi.iItem = hi;

					theCtrl.GetItem( &lvitemlo );
					theCtrl.GetItem( &lvitemhi );

					for( i=0; i<nColCount; i++)
						theCtrl.SetItemText(lo, i, theCtrl.GetItemText(hi, i));

					lvitemhi.iItem = lo;
					theCtrl.SetItem( &lvitemhi );

					for( i=0; i<nColCount; i++)
						theCtrl.SetItemText(hi, i, rowText[i]);

					lvitemlo.iItem = hi;
					theCtrl.SetItem( &lvitemlo );
				}

				++lo;
				--hi;
			}
		}

		// If the right index has not reached the left side of array
		// must now sort the left partition.
		if( low < hi )
			SortTextItems( nCol, bAscending , low, hi);

		// If the left index has not reached the right side of array
		// must now sort the right partition.
		if( lo < high )
			SortTextItems( nCol, bAscending , lo, high );

		return TRUE;
}

void CFormatView::GyInit()
{
	CListCtrl &theCtrl=this->GetListCtrl();
	theCtrl.SetExtendedStyle(theCtrl.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	if(!bHost)
	{
		theCtrl.InsertColumn (0,"Name",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (1,"type",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (2,"length",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (3,"exist",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (4,"display",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (5,"Read",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (6,"Write",LVCFMT_LEFT,100);
		theCtrl.InsertColumn (7,"Generate",LVCFMT_LEFT,100);
	}
	else
	{
		theCtrl.InsertColumn (0,"Time",LVCFMT_LEFT,150);
		theCtrl.InsertColumn (1,"Sender(ip)",LVCFMT_LEFT,150);
		theCtrl.InsertColumn (2,"Message(hex display)",LVCFMT_LEFT,500);
	}
}

void CFormatView::OnAdd() 
{
	// TODO: Add your command handler code here
	if(dlg==NULL)
	{
		dlg=new CAddDlg;
		dlg->Create (IDD_DIALOG1,this);
	}
	dlg->ShowWindow (SW_NORMAL);

/*	if(dlg->ShowWindow (SW_NORMAL)==IDOK)
	{
		CListCtrl &theCtrl=this->GetListCtrl ();
		theCtrl.InsertItem (theCtrl.GetItemCount (),dlg->m_name );
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,1,dlg->m_type);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,2,dlg->m_len);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,3,dlg->m_exist);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,4,dlg->m_disp);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,5,dlg->m_read);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,6,dlg->m_write);
		theCtrl.SetItemText (theCtrl.GetItemCount ()-1,7,dlg->m_gen);
	}*/
	dlg->SetP(this->m_hWnd );
}

void CFormatView::OnDel() 
{
	// TODO: Add your command handler code here
	CListCtrl &theCtrl=this->GetListCtrl ();
	POSITION pos=theCtrl.GetFirstSelectedItemPosition ();
	theCtrl.DeleteItem (theCtrl.GetNextSelectedItem (pos));
}

void CFormatView::AddItem()
{
	CListCtrl &theCtrl=this->GetListCtrl ();
	theCtrl.InsertItem (theCtrl.GetItemCount (),dlg->m_name );
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,1,dlg->m_type);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,2,dlg->m_len);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,3,dlg->m_exist);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,4,dlg->m_disp);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,5,dlg->m_read);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,6,dlg->m_write);
	theCtrl.SetItemText (theCtrl.GetItemCount ()-1,7,dlg->m_gen);
}
void CFormatView::OnUpdateList()
{
	CString strTm;
	CListCtrl &theCtrl=this->GetListCtrl ();
	SYSTEMTIME sysTime;
	GetSystemTime(&sysTime);
	strTm.Format ("%d-%d-%d(%d:%d:%d)",sysTime.wYear ,sysTime.wMonth ,sysTime.wDay ,
		sysTime.wHour+8 ,sysTime.wMinute ,sysTime.wSecond );
	theCtrl.InsertItem (0,strTm );
	theCtrl.SetItemText (0,2,cliMsg.msg );
	theCtrl.SetItemText (0,1,cliMsg.ip );
//	this->Invalidate (FALSE);
}
void CFormatView::OnFileSave() 
{
	// TODO: Add your command handler code here
	AfxMessageBox("将覆盖程序目录中的记录文件!");
	CListCtrl &theCtrl=this->GetListCtrl ();
	CString strTmp;
	char strPath[1024];
	memset(strPath,0,1024);
	GetModuleFileName(NULL,(LPSTR)strPath,1024);
	char * p;
	p=&strPath[strlen(strPath-1)];
	while(p!=NULL)
	{
		if(*p=='\\')
			break;
		p--;
	}
	p++;
	strcpy(p,"gaoyong");
	CFile f;
	f.Open (strPath,CFile::modeReadWrite|CFile::modeCreate);
	CArchive ar(&f,CArchive::store);
	int icount=theCtrl.GetItemCount ();
	ar<<icount;
	for(int i=0;i<icount;i++)
	{
		for(int j=0;j<8;j++)
		{
			strTmp=theCtrl.GetItemText (i,j);
			ar<<strTmp;
		}
	}
	ar.Close();
	f.Close ();
}

void CFormatView::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	
}

void CFormatView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	if(bHost)
	{
		CListCtrl &theCtrl=this->GetListCtrl ();
		//情空列表信息
			theCtrl.DeleteAllItems ();
			CHeaderCtrl *pHeadCtrl=theCtrl.GetHeaderCtrl ();
			int nCount = pHeadCtrl->GetItemCount();

			// Delete all of the items.
			for (int i=0;i < nCount;i++)
			{
			   pHeadCtrl->DeleteItem(0);
			}
			/*theCtrl.RedrawWindow ();*/

		OnInitialUpdate();
		bHost=FALSE;
		GyInit();
	}
	CListCtrl &theCtrl=this->GetListCtrl ();
	theCtrl.DeleteAllItems ();
	CString strTmp;
	char strPath[1024];
	memset(strPath,0,1024);
	GetModuleFileName(NULL,(LPSTR)strPath,1024);
	char * p;
	p=&strPath[strlen(strPath-1)];
	while(p!=NULL)
	{
		if(*p=='\\')
			break;
		p--;
	}
	p++;
	strcpy(p,"gaoyong");
	CFile f;
	f.Open (strPath,CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	int icount;
	ar>>icount;
	for(int i=0;i<icount;i++)
	{
		ar>>strTmp;
		theCtrl.InsertItem (i,strTmp);
		for(int j=1;j<8;j++)
		{
			ar>>strTmp;
			theCtrl.SetItemText (i,j,strTmp);
		}
	}
	ar.Close();
	f.Close ();	
}

void CFormatView::OnFileNew() 
{
	// TODO: Add your command handler code here
	
}

void CFormatView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_ESCAPE)
		OnDel();
	CListView::OnChar(nChar, nRepCnt, nFlags);
}

void CFormatView::OnUpdate() 
{
	CListCtrl &theCtrl=this->GetListCtrl ();
	POSITION pos=theCtrl.GetFirstSelectedItemPosition ();
	int iRec=theCtrl.GetNextSelectedItem (pos);
	if(iRec==-1)
		return;
//	theCtrl.DeleteItem ();	
	
	if(dlg==NULL)
	{
		dlg=new CAddDlg;
		dlg->Create (IDD_DIALOG1,this);
	}
	dlg->m_name =theCtrl.GetItemText (iRec,0);
	dlg->m_type =theCtrl.GetItemText (iRec,1);
	dlg->m_len	=theCtrl.GetItemText (iRec,2);
	dlg->m_exist =theCtrl.GetItemText(iRec,3);
	dlg->m_disp  =theCtrl.GetItemText(iRec,4);
	dlg->m_read =theCtrl.GetItemText(iRec,5);
	dlg->m_write  =theCtrl.GetItemText(iRec,6);
	dlg->m_gen  =theCtrl.GetItemText(iRec,7);
	dlg->SetP(this->m_hWnd );
	dlg->UpdateData (FALSE);
	dlg->ShowWindow (SW_NORMAL);	
}
extern void BcdToAscii(const char *hex, unsigned char *str, int count);
UINT ClientThread(LPVOID lpParam)
{
	struct _HDSY_CLI_MSG_ *inData=(struct _HDSY_CLI_MSG_ *)lpParam;
	char          szBuff[1024];
	int           ret=0;
	
	memset (szBuff,0,1024);
	ret = recv(inData->sock, szBuff, 1024, 0);
	if (ret == 0||ret == SOCKET_ERROR)
		return 1;
	
	memset(inData->msg,0,sizeof(inData->msg ));
	for(int i=0,j=0;i<ret;i++)
	{
		sprintf(inData->msg+j,"%02X",(unsigned char )*(szBuff+i));
		j+=2;
	}
	send(inData->sock,szBuff,1024,0);
	PostMessage(inData->hWnd,TRS_MSG_UPDATE,0,0);

	unsigned char uuu[33333];
	BcdToAscii(szBuff,uuu,1024);
    return 0;
}
UINT LsnThread(LPVOID pData)
{
	//HWND hWnd=(HWND) pData;
	struct _HDSY_CLI_MSG_ *cliMsg=(struct _HDSY_CLI_MSG_ *)pData;
/*	char cliIP[20];
	memset(cliIP,0,sizeof(cliIP));
	char msg[8019];
	memset(msg,0,sizeof(msg));
	PostMessage(hWnd,TRS_MSG_UPDATE,0,0);
	return 1;*/

	CString			sMsg;
	char			szAddress[128];
	SOCKET			sClient,sListen;
	int			iAddrSize;
	short			iPort;
	struct sockaddr_in	local,client;

	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sListen == SOCKET_ERROR)
	{
		sMsg.Format ("socket() failed: %d\n", WSAGetLastError());
		AfxMessageBox(sMsg);
		return 1;
	}
	// Select the local interface, and bind to it
	//

	strcpy(szAddress,"127.0.0.1");
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
		MSG msg;
		if(::PeekMessage(&msg,NULL,0,0,0)>0)
		{
			switch(msg.message )
			{
			case (WM_USER+1):				
				closesocket(sListen);
				return -1;
				break;
			default:break;
			}
		}
		iAddrSize = sizeof(client);
		sClient = accept(sListen, (struct sockaddr *)&client,
		&iAddrSize);        
		if (sClient == INVALID_SOCKET)
		{        
			sMsg.Format("accept() failed: %d\n", WSAGetLastError());
			AfxMessageBox(sMsg);
			break;
		}
		
		sMsg.Format ("%s:%d\n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		//AfxMessageBox(sMsg);
		memset((char *)cliMsg->ip ,0,sizeof(cliMsg->ip));
		memcpy(cliMsg->ip,sMsg,sMsg.GetLength ());
		cliMsg->sock=sClient;
		AfxBeginThread(ClientThread,(LPVOID)cliMsg);
	}
	closesocket(sListen);
	return 0;
}
void CFormatView::OnStartService() 
{
	if(!bHost)
	{
		bHost=TRUE;
		CListCtrl &theCtrl=this->GetListCtrl ();
		//情空列表信息
			theCtrl.DeleteAllItems ();
			CHeaderCtrl *pHeadCtrl=theCtrl.GetHeaderCtrl ();
			int nCount = pHeadCtrl->GetItemCount();

			// Delete all of the items.
			for (int i=0;i < nCount;i++)
			{
			   pHeadCtrl->DeleteItem(0);
			}
			/*theCtrl.RedrawWindow ();*/

		OnInitialUpdate();
	}
	bEnable=!bEnable;
	//启动监听线程
		memset((char *)&cliMsg,0,sizeof(cliMsg));
		cliMsg.hWnd =this->m_hWnd ;
		thdListen=AfxBeginThread(LsnThread,(LPVOID)&cliMsg);
}

void CFormatView::OnUpdateStartService(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable (bEnable);
}

void CFormatView::OnStopService() 
{
	// TODO: Add your command handler code here
	if(thdListen!=NULL)
	{
		::PostThreadMessage (thdListen->m_nThreadID ,WM_USER+1,0,0);
		//::TerminateThread (thdListen->m_hThread ,6819);
		bEnable=TRUE;
	}
	bEnable=TRUE;
}

void CFormatView::OnUpdateStopService(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CFormatView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CListCtrl &m_lstComm=this->GetListCtrl ();
	if(msgdlg==NULL)
	{
		msgdlg= new CMsgDetailDlg;
		msgdlg->Create (IDD_DIALOG2);
	}
	CString str;
	POSITION pos=
		m_lstComm.GetFirstSelectedItemPosition ();
	int idx=
		m_lstComm.GetNextSelectedItem (pos);
	str=m_lstComm.GetItemText (idx,2);

	
	msgdlg->msg.ResetDigram();//ClearDigram ()
	msgdlg->msg.Parse (str,str.GetLength (),0);
	//memset(gen8583,0,sizeof(gen8583));
	//ilen=dlg->msg.Generate((char *)gen8583,4,"623E40808AC18411");//dlg->msg.Generate ((char *)gen8583,4);
	msgdlg->FillData ();
	msgdlg->ShowWindow (SW_NORMAL);//DoModal ();
	*pResult = 0;
}
