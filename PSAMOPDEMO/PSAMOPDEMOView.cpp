// PSAMOPDEMOView.cpp : implementation of the CPSAMOPDEMOView class
//

#include "stdafx.h"
#include "PSAMOPDEMO.h"

#include "PSAMOPDEMODoc.h"
#include "PSAMOPDEMOView.h"
#include "EncryptorAdap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView

IMPLEMENT_DYNCREATE(CPSAMOPDEMOView, CListView)

BEGIN_MESSAGE_MAP(CPSAMOPDEMOView, CListView)
//{{AFX_MSG_MAP(CPSAMOPDEMOView)
ON_COMMAND(MENU_SELECT_MF, OnSelectMf)
ON_COMMAND(MEMU_CREATE_MF, OnCreateMf)
ON_COMMAND(TB_SHUT_COM1, OnShutCom1)
ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_COMMAND(MENU_WRITE_EF_PUB, OnWriteEfPub)
	ON_COMMAND(MEMU_SET_DELAY, OnSetDelay)
	ON_COMMAND(MENU_CARD_IN, OnCardIn)
	ON_COMMAND(MENU_CARD_RESET, OnCardReset)
	ON_COMMAND(MENU_CREATE_ADF_KEY_FILE, OnCreateAdfKeyFile)
	ON_COMMAND(MENU_CREATE_DF_APP, OnCreateDfApp)
	ON_COMMAND(MENU_CREATE_EF_CARD_KEY, OnCreateEfCardKey)
	ON_COMMAND(MENU_CREATE_EF_DIR, OnCreateEfDir)
	ON_COMMAND(MENU_CREATE_EF_PUB, OnCreateEfPub)
	ON_COMMAND(MENU_POWEROFF, OnPoweroff)
	ON_COMMAND(MENU_POWERON, OnPoweron)
	ON_COMMAND(MENU_PSAM_CMD, OnPsamCmd)
	ON_COMMAND(MENU_WRITE_ADF_WORK_KEY, OnWriteAdfWorkKey)
	ON_COMMAND(MENU_WRITE_EF_DIR, OnWriteEfDir)
	ON_COMMAND(MENU_WRITE_EF_MK, OnWriteEfMk)
	ON_COMMAND(MENU_MAKE_NEW_CARD, OnMakeNewCard)
	ON_COMMAND(MENU_WRITE_APP_MK, OnWriteAppMk)
	ON_COMMAND(MENU_END_CREATE_ADF, OnEndCreateAdf)
	ON_COMMAND(MENU_END_CREATE_MF, OnEndCreateMf)
	ON_COMMAND(MENU_SETTING_ENV, OnSettingEnv)
	ON_COMMAND(MENU_WASH_CARD, OnWashCard)
	ON_COMMAND(MENU_FILLL_AWK, OnFilllAwk)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(MENU_CHANGE_AWK, OnChangeAwk)
	ON_COMMAND(TB_Check_Card, OnCheckCard)
	//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView construction/destruction

CPSAMOPDEMOView::CPSAMOPDEMOView()
{
	// TODO: add construction code here
	st340=NULL;
	bSortAscending=FALSE;
	envdlg=NULL;
	iComx=1;
}

CPSAMOPDEMOView::~CPSAMOPDEMOView()
{
	if(st340!=NULL)
	{
		delete st340;
		st340=NULL;
	}
	if(envdlg!=NULL)
	{
		delete envdlg;
		envdlg=NULL;
	}
}

BOOL CPSAMOPDEMOView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView drawing

void CPSAMOPDEMOView::OnDraw(CDC* pDC)
{
	CPSAMOPDEMODoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here

}

void CPSAMOPDEMOView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	
	this->ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	CListCtrl &theCtrl=this->GetListCtrl();
	theCtrl.SetExtendedStyle(
		theCtrl.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES
		);
	
	theCtrl.InsertColumn (0,"序号",LVCFMT_CENTER,50);
	theCtrl.InsertColumn (1,"命令",LVCFMT_LEFT,500);
	theCtrl.InsertColumn (2,"响应",LVCFMT_LEFT,350);
//	theCtrl.InsertColumn (3,"注释",LVCFMT_LEFT,300);
	OnSettingEnv();
}

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView printing

BOOL CPSAMOPDEMOView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPSAMOPDEMOView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPSAMOPDEMOView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView diagnostics

#ifdef _DEBUG
void CPSAMOPDEMOView::AssertValid() const
{
	CListView::AssertValid();
}

void CPSAMOPDEMOView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CPSAMOPDEMODoc* CPSAMOPDEMOView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPSAMOPDEMODoc)));
	return (CPSAMOPDEMODoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOView message handlers
void CPSAMOPDEMOView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	
}

//DEL void CPSAMOPDEMOView::OnPoweron() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	if(st340==NULL)
//DEL 		st340=new CST340(1);
//DEL 	st340->CardPowerOn ();
//DEL }

void CPSAMOPDEMOView::OnSelectMf() 
{
	CPsamCard psamcard;
	CommitRequest (2,psamcard.SelectMF ());
}

void CPSAMOPDEMOView::AddHistory(char *req, char *res)
{
	static int i=0;

	CString str;
	str.Format ("%3d",i);

	CListCtrl &theCtrl=this->GetListCtrl ();
	theCtrl.InsertItem (0,str);
	theCtrl.SetItemText (0,1,req);
	theCtrl.SetItemText (0,2,res);

	i++;
}

void CPSAMOPDEMOView::CommitRequest(int flag, const char *cmd)
{
	memset(res,0,sizeof(res));
	if(envdlg!=NULL)
	{
		if(iComx!=envdlg->m_iComx )
		{
			if(st340!=NULL)
				delete st340;
			st340=NULL;
			iComx=envdlg->m_iComx ;
		}
	}
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive)
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	if(cmd==NULL)
		return;
	st340->PSAMCommand (flag,cmd);
	AddHistory(st340->GetRequest (),st340->GetResponse ());
	this->Invalidate (FALSE);
	strcpy(res,st340->GetResponse ());
}

void CPSAMOPDEMOView::OnCreateMf() 
{
	CPsamCard psamcard;
	CommitRequest (2,psamcard.CreateMF ());
}

void CPSAMOPDEMOView::OnShutCom1() 
{
	if(st340!=NULL)
		delete st340;
	st340=NULL;
	CListCtrl &theCtrl=this->GetListCtrl ();
	/*保存到文件*/
	SaveToHisFile("his");
	/*删除列表项*/
	theCtrl.DeleteAllItems ();
}

BOOL CPSAMOPDEMOView::SortTextItems(int nCol, BOOL bAscending, int low, int high)
{
	CListCtrl &theCtrl=this->GetListCtrl ();
	
	if( nCol >= theCtrl.GetHeaderCtrl ()->GetItemCount() )
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
									theCtrl.GetHeaderCtrl ()->GetItemCount();
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

void CPSAMOPDEMOView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	bSortAscending = !bSortAscending;
	SortTextItems(phdn->iButton , bSortAscending, 0, -1 );	
	*pResult = 0;
}

void CPSAMOPDEMOView::OnWriteEfPub() 
{
	CPsamCard psamcard;
	char sid[17];
	memset(sid,0,sizeof(sid));
	if(envdlg!=NULL)
		strcpy(sid,envdlg->m_strSid);
	else
		strcpy(sid,"1234567890123456");
	
	this->CommitRequest (2,psamcard.WritePUB (sid));


}

void CPSAMOPDEMOView::OnSetDelay() 
{
	iComx=envdlg->m_iComx ;
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive )
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	st340->SetDelay(10);
	AddHistory(st340->GetRequest (),st340->GetResponse ());
	strcpy(res,st340->GetResponse ());

}

void CPSAMOPDEMOView::OnCardIn() 
{
	iComx=envdlg->m_iComx ;
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive )
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	st340->CardInCheck ();
	AddHistory(st340->GetRequest (),st340->GetResponse  ());
	strcpy(res,st340->GetResponse ());

}

void CPSAMOPDEMOView::OnCardReset() 
{
	iComx=envdlg->m_iComx ;
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive )
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	st340->CardReset ();
	AddHistory(st340->GetRequest (),st340->GetResponse ());
	strcpy(res,st340->GetResponse ());
}

void CPSAMOPDEMOView::OnCreateAdfKeyFile() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.CreateEnKeyFile());
}

void CPSAMOPDEMOView::OnCreateDfApp() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.CreateDF ("HDSY1PBOC"));
}

void CPSAMOPDEMOView::OnCreateEfCardKey() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.CreateKeyFile());	
}

void CPSAMOPDEMOView::OnCreateEfDir() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.CreateEFDIR());
}

void CPSAMOPDEMOView::OnCreateEfPub() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.CreatePUB());
}

void CPSAMOPDEMOView::OnPoweroff() 
{
	iComx=envdlg->m_iComx ;
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive )
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	st340->CardPowerDown  ();
	AddHistory(st340->GetRequest (),st340->GetResponse ());
	strcpy(res,st340->GetResponse ());

}

void CPSAMOPDEMOView::OnPoweron() 
{
	iComx=envdlg->m_iComx ;
	if(st340==NULL)
	{
		st340=new CST340(iComx);
	}
	if(!st340->bActive )
	{
		AfxMessageBox("ST340未在工作状态.");
		return;
	}
	st340->CardPowerOn();
	AddHistory(st340->GetRequest (),st340->GetResponse  ());
	strcpy(res,st340->GetResponse ());

}

void CPSAMOPDEMOView::OnPsamCmd() 
{
	CTestPsamCmdDlg dlg;
	dlg.DoModal ();
}
extern CEncryptorAdap enadap;
void CPSAMOPDEMOView::OnWriteAdfWorkKey() 
{
	CPsamCard psamcard;
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*获取SID*/
	char sid[17];
		memset(sid,0,sizeof(sid));
		CommitRequest(2,"00A40200020015");
		CommitRequest(3,psamcard.ReadPub ());
		if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			strncpy(sid,res+10,16);
		}
		else
		{
			strcpy(sid,"1234567890123456");
		}
	/*选择ADF*/
		CommitRequest (2,psamcard.SelectDFByName("HDSY1PBOC"));
	/*取随机数:然后写入应用主工作密钥*/
		CommitRequest(3,psamcard.GetRnd (4));
		if(memcmp(res+14,"9000",4)==0)
		{
			char machex[9];
			memset(machex,0,sizeof(machex));
			strncpy(machex,res+6,8);
			/*写应用主控密钥*/
			//CommitRequest(2,psamcard.LoadAppMK("88888888888888888888888888888888",machex));
			//CommitRequest(2,psamcard.LoadAppWK ("88888888888888888888888888888888","88888888888888888888888888888888",machex));
			if(enadap.iPort ==0)
				CommitRequest(2,psamcard.EnLoadAWKLocal (envdlg->m_strAmk,envdlg->m_strCmk,sid,machex));
			else
			{

				CommitRequest(2,psamcard.EnLoadAWK (sid,machex));
			}
		}
	/*显示处理结果*/
		if(strlen(res)<=4)
		{
			AfxMessageBox("注入应用密钥失败!!!!");	
			return;
		}
		if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			AfxMessageBox("成功注入应用密钥!!!!");
			return;
		}
		else
		{
			AfxMessageBox("注入应用密钥失败!!!!");	
			return;
		}
	/*卡片下电*/
		OnPoweroff();
}

void CPSAMOPDEMOView::OnWriteEfDir() 
{
	CPsamCard psamcard;
	this->CommitRequest (2,psamcard.WriteEFDIR("HDSY1PBOC"));
}

void CPSAMOPDEMOView::OnWriteEfMk() 
{
	CPsamCard psamcard;
	char cmk[33];
	memset(cmk,0,sizeof(cmk));
	if(envdlg!=NULL)
		strcpy(cmk,envdlg->m_strCmk);
	else
		strcpy(cmk,"88888888888888888888888888888888");
	
	this->CommitRequest (2,psamcard.SimpleAddMK(cmk));
}

void CPSAMOPDEMOView::OnMakeNewCard() 
{
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*建立MF*/
		OnCreateMf();
	/*建立DIR文件*/
		OnCreateEfDir();
	/*写DIR文件*/
		OnWriteEfDir();
	/*建立PUB文件*/
		OnCreateEfPub();
	/*写PUB文件*/
		OnWriteEfPub();
	/*建立卡片密钥文件*/
		OnCreateEfCardKey();
	/*写入卡片主控密钥*/
		OnWriteEfMk();
	/*建立ADF*/
		OnCreateDfApp();
	/*建立应用密钥文件*/
		OnCreateAdfKeyFile();
	/*写入应用主控密钥*/
		OnWriteAppMk();
		//OnWriteAdfWorkKey();
		if(strlen(res)<=4)
		{
			AfxMessageBox("发卡失败!!!!");
		}
		else if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			AfxMessageBox("发卡成功!!!!");
		}
		else
		{
			AfxMessageBox("发卡失败!!!!");	
		}
	/*结束创建DF*/
		OnEndCreateAdf();
	/*结束创建MF*/
		OnEndCreateMf();
	/*卡片下电*/
		OnPoweroff();
}

void CPSAMOPDEMOView::OnWriteAppMk() 
{
	CPsamCard psamcard;
	char cmk[33],amk[33];
	memset(cmk,0,sizeof(cmk));
	memset(amk,0,sizeof(amk));
	if(envdlg!=NULL)
	{
		strcpy(cmk,envdlg->m_strCmk);
		strcpy(amk,envdlg->m_strAmk );
	}
	else
	{
		strcpy(cmk,"88888888888888888888888888888888");
		strcpy(amk,"88888888888888888888888888888888");
	}

	CommitRequest (2,psamcard.SelectDFByName("HDSY1PBOC"));
	CommitRequest(3,psamcard.GetRnd (4));
	if(memcmp(res+14,"9000",4)==0)
	{
		char machex[9];
		memset(machex,0,sizeof(machex));
		strncpy(machex,res+6,8);
		/*写应用主控密钥*/
		//CommitRequest(2,psamcard.LoadAppMK("88888888888888888888888888888888",machex));
		/*写应用工作密钥*/
		CommitRequest(2,psamcard.LoadAppMK(cmk,amk,machex));
	}	
}

void CPSAMOPDEMOView::OnEndCreateAdf() 
{
	CPsamCard psamcard;

	CommitRequest (2,"80E00101022F01");
}

void CPSAMOPDEMOView::OnEndCreateMf() 
{
	CPsamCard psamcard;

	CommitRequest (2,"80E00001023F00");
		
}

void CPSAMOPDEMOView::OnSettingEnv() 
{
	if(envdlg==NULL)
	{
		envdlg=new CDisSettingDlg();
		envdlg->Create (IDD_DIALOG2);
	}
	envdlg->ShowWindow (SW_NORMAL);
}

void CPSAMOPDEMOView::OnWashCard() 
{
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*删除卡片MF*/
		CommitRequest (2,"800E000008FFFFFFFFFFFFFFFF");
		Sleep(10);
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*建立MF*/
		OnCreateMf();
	/*建立DIR文件*/
		OnCreateEfDir();
	/*写DIR文件*/
		OnWriteEfDir();
	/*建立PUB文件*/
		OnCreateEfPub();
	/*写PUB文件*/
		OnWriteEfPub();
	/*建立卡片密钥文件*/
		OnCreateEfCardKey();
	/*写入卡片主控密钥*/
		OnWriteEfMk();
	/*建立ADF*/
		OnCreateDfApp();
	/*建立应用密钥文件*/
		OnCreateAdfKeyFile();
	/*写入应用主控密钥*/
		OnWriteAppMk();
		//OnWriteAdfWorkKey();
		if(strlen(res)<=4)
		{
			AfxMessageBox("洗卡失败!!!!");	
		}
		else if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			AfxMessageBox("洗卡成功!!!!");
		}
		else
		{
			AfxMessageBox("洗卡失败!!!!");
		}
	/*写入应用工作主密钥
		OnWriteAdfWorkKey();*/
	/*结束创建DF*/
		OnEndCreateAdf();
	/*结束创建MF*/
		OnEndCreateMf();
	/*卡片下电*/
		OnPoweroff();	
}

void CPSAMOPDEMOView::OnFilllAwk() 
{
	OnWriteAdfWorkKey();
}

void CPSAMOPDEMOView::SaveToHisFile(char *filename)
{
	CListCtrl &theCtrl=this->GetListCtrl ();
	/*保存到文件*/
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
	strcpy(p,filename);
	CFile f;
	f.Open (strPath,CFile::modeReadWrite|CFile::modeCreate);
	CArchive ar(&f,CArchive::store);
	int icount=theCtrl.GetItemCount ();
	int icol=theCtrl.GetHeaderCtrl ()->GetItemCount ();
	ar<<icount;
	ar<<icol;
	for(int i=0;i<icount;i++)
	{
		for(int j=0;j<icol;j++)
		{
			strTmp=theCtrl.GetItemText (i,j);
			ar<<strTmp;
		}
	}
	ar.Close();
	f.Close ();
}

void CPSAMOPDEMOView::RestoreFromHisFile(char *filename)
{
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
	strcpy(p,filename);
	CFile f;
	f.Open (strPath,CFile::modeRead);
	CArchive ar(&f,CArchive::load);
	int icount,icol;
	ar>>icount;ar>>icol;
	for(int i=0;i<icount;i++)
	{
		ar>>strTmp;
		theCtrl.InsertItem (i,strTmp);
		for(int j=1;j<icol;j++)
		{
			ar>>strTmp;
			theCtrl.SetItemText (i,j,strTmp);
		}
	}
	ar.Close();
	f.Close ();	
}

void CPSAMOPDEMOView::OnFileOpen() 
{
	this->RestoreFromHisFile ("his");
}

void CPSAMOPDEMOView::OnFileSave() 
{
	SaveToHisFile("his");	
}

void CPSAMOPDEMOView::OnFileNew() 
{
	
}

void CPSAMOPDEMOView::OnChangeAwk() 
{
	CPsamCard psamcard;
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*获取SID*/
	char sid[17];
		memset(sid,0,sizeof(sid));
		CommitRequest(2,"00A40200020015");
		CommitRequest(3,psamcard.ReadPub ());
		if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			strncpy(sid,res+10,16);
		}
		else
		{
			strcpy(sid,"1234567890123456");
		}
	/*选择ADF*/
		CommitRequest (2,psamcard.SelectDFByName("HDSY1PBOC"));
	/*取随机数:然后写入应用主工作密钥*/
		CommitRequest(3,psamcard.GetRnd (4));
		if(memcmp(res+14,"9000",4)==0)
		{
			char machex[9];
			memset(machex,0,sizeof(machex));
			strncpy(machex,res+6,8);
			/*写应用主控密钥*/
			//CommitRequest(2,psamcard.LoadAppMK("88888888888888888888888888888888",machex));
			//CommitRequest(2,psamcard.LoadAppWK ("88888888888888888888888888888888","88888888888888888888888888888888",machex));
			if(enadap.iPort ==0)
				CommitRequest(2,psamcard.UpdateAWKLocal(envdlg->m_strAmk,envdlg->m_strCmk,sid,machex));
			else
			{

				CommitRequest(2,psamcard.UpdateAWK  (sid,machex));
			}
		}
	/*显示处理结果*/
		if(strlen(res)<=4)
			AfxMessageBox("注入应用密钥失败!!!!");	
		if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			AfxMessageBox("成功注入应用密钥!!!!");
		}
		else
		{
			AfxMessageBox("注入应用密钥失败!!!!");	
		}
	/*卡片下电*/
		OnPoweroff();
}

void CPSAMOPDEMOView::OnCheckCard() 
{
	CPsamCard psamcard;
	/*卡上电*/
		OnPoweron();
	/*卡到位*/
		OnCardIn();
	/*卡复位*/
		OnCardReset();
	/*设置延时*/
		OnSetDelay();
	/*选择ADF*/
		CommitRequest (2,psamcard.SelectDFByName("HDSY1PBOC"));
	/*初始化DES加密算法*/
		CommitRequest(2,psamcard.InitDes ());

	/*显示处理结果*/
		if(strlen(res)<=4)
			AfxMessageBox("不能使用!!!!");	
		if(memcmp(res+strlen(res)-4,"9000",4)==0)
		{
			AfxMessageBox("可以使用!!!!");
		}
		else
		{
			AfxMessageBox("不能使用!!!!");	
		}
}
