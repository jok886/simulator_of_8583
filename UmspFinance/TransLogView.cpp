// TransLogView.cpp : implementation file
//

#include "stdafx.h"
#include "UmspFinance.h"
#include "TransLogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransLogView

IMPLEMENT_DYNCREATE(CTransLogView, CListView)

CTransLogView::CTransLogView()
{
}

CTransLogView::~CTransLogView()
{
}


BEGIN_MESSAGE_MAP(CTransLogView, CListView)
	//{{AFX_MSG_MAP(CTransLogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransLogView drawing

void CTransLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTransLogView diagnostics

#ifdef _DEBUG
void CTransLogView::AssertValid() const
{
	CListView::AssertValid();
}

void CTransLogView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransLogView message handlers

BOOL CTransLogView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT     |
			 LVS_SINGLESEL     |
			 LVS_SHOWSELALWAYS |
			 LVS_ICON          ;
	return CListView::PreCreateWindow(cs);
}

void CTransLogView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CListCtrl &theCtrl=this->GetListCtrl();
	theCtrl.SetExtendedStyle(theCtrl.GetExtendedStyle()|LVS_EX_HEADERDRAGDROP|LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	theCtrl.InsertColumn (0,"��������",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (1,"���ʺ�",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (2,"���׽��",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (3,"�ն˱�Ǻ�",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (4,"�̻���Ǻ�",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (5,"�ɷ�����",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (6,"��������",LVCFMT_LEFT,100);
	theCtrl.InsertColumn (7,"���",LVCFMT_LEFT,100);
}