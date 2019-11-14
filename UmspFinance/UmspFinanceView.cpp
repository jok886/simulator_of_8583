// UmspFinanceView.cpp : implementation of the CUmspFinanceView class
//

#include "stdafx.h"
#include "UmspFinance.h"

#include "UmspFinanceDoc.h"
#include "UmspFinanceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView

IMPLEMENT_DYNCREATE(CUmspFinanceView, CListView)

BEGIN_MESSAGE_MAP(CUmspFinanceView, CListView)
	//{{AFX_MSG_MAP(CUmspFinanceView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView construction/destruction

CUmspFinanceView::CUmspFinanceView()
{
	// TODO: add construction code here

}

CUmspFinanceView::~CUmspFinanceView()
{
}

BOOL CUmspFinanceView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView drawing

void CUmspFinanceView::OnDraw(CDC* pDC)
{
	CUmspFinanceDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CUmspFinanceView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView printing

BOOL CUmspFinanceView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUmspFinanceView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUmspFinanceView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView diagnostics

#ifdef _DEBUG
void CUmspFinanceView::AssertValid() const
{
	CListView::AssertValid();
}

void CUmspFinanceView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CUmspFinanceDoc* CUmspFinanceView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUmspFinanceDoc)));
	return (CUmspFinanceDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceView message handlers
