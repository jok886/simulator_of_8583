// PSAMOPDEMODoc.cpp : implementation of the CPSAMOPDEMODoc class
//

#include "stdafx.h"
#include "PSAMOPDEMO.h"

#include "PSAMOPDEMODoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMODoc

IMPLEMENT_DYNCREATE(CPSAMOPDEMODoc, CDocument)

BEGIN_MESSAGE_MAP(CPSAMOPDEMODoc, CDocument)
	//{{AFX_MSG_MAP(CPSAMOPDEMODoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMODoc construction/destruction

CPSAMOPDEMODoc::CPSAMOPDEMODoc()
{
	// TODO: add one-time construction code here

}

CPSAMOPDEMODoc::~CPSAMOPDEMODoc()
{
}

BOOL CPSAMOPDEMODoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMODoc serialization

void CPSAMOPDEMODoc::Serialize(CArchive& ar)
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
// CPSAMOPDEMODoc diagnostics

#ifdef _DEBUG
void CPSAMOPDEMODoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPSAMOPDEMODoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMODoc commands
