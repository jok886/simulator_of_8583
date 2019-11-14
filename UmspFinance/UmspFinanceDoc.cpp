// UmspFinanceDoc.cpp : implementation of the CUmspFinanceDoc class
//

#include "stdafx.h"
#include "UmspFinance.h"

#include "UmspFinanceDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceDoc

IMPLEMENT_DYNCREATE(CUmspFinanceDoc, CDocument)

BEGIN_MESSAGE_MAP(CUmspFinanceDoc, CDocument)
	//{{AFX_MSG_MAP(CUmspFinanceDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceDoc construction/destruction

CUmspFinanceDoc::CUmspFinanceDoc()
{
	// TODO: add one-time construction code here

}

CUmspFinanceDoc::~CUmspFinanceDoc()
{
}

BOOL CUmspFinanceDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceDoc serialization

void CUmspFinanceDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceDoc diagnostics

#ifdef _DEBUG
void CUmspFinanceDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CUmspFinanceDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceDoc commands
