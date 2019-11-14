// LeftViewOne.cpp : implementation file
//

#include "stdafx.h"
#include "PSAMOPDEMO.h"
#include "LeftViewOne.h"

#include "PSAMOPDEMODoc.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftViewOne

IMPLEMENT_DYNCREATE(CLeftViewOne, CTreeView)



BEGIN_MESSAGE_MAP(CLeftViewOne, CTreeView)
//{{AFX_MSG_MAP(CLeftViewOne)
// NOTE - the ClassWizard will add and remove mapping macros here.
//{{AFX_MSG_MAP(CLeftView)
ON_COMMAND(ID_FILE_NEW, OnFileNew)
ON_WM_ACTIVATE()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CLeftViewOne::CLeftViewOne()
{
}

CLeftViewOne::~CLeftViewOne()
{
}

BOOL CLeftViewOne::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|=TVS_SHOWSELALWAYS|WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
		| TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
		| TVS_DISABLEDRAGDROP;
	return CTreeView::PreCreateWindow(cs);
}



/////////////////////////////////////////////////////////////////////////////
// CLeftViewOne drawing

void CLeftViewOne::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	ASSERT_VALID(pDoc);
}


BOOL CLeftViewOne::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftViewOne::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftViewOne::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


void CLeftViewOne::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	CTreeCtrl &theCtrl=GetTreeCtrl();
	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("ST340");
	
	HTREEITEM hCountry = theCtrl.InsertItem(&tvInsert);
	
	HTREEITEM hPA=theCtrl.InsertItem(TVIF_TEXT,_T("ÇëÇó"), 0, 0, 0, 0, 0, hCountry, NULL);
	
	this->EnableWindow (FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CLeftViewOne diagnostics

#ifdef _DEBUG
void CLeftViewOne::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftViewOne::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CPSAMOPDEMODoc* CLeftViewOne::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPSAMOPDEMODoc)));
	return (CPSAMOPDEMODoc*)m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftViewOne message handlers

void CLeftViewOne::OnFileNew() 
{
	
}

void CLeftViewOne::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CTreeView::OnActivate(nState, pWndOther, bMinimized);
}