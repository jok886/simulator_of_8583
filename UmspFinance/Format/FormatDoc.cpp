// FormatDoc.cpp : implementation of the CFormatDoc class
//

#include "stdafx.h"
#include "Format.h"

#include "FormatDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormatDoc

IMPLEMENT_DYNCREATE(CFormatDoc, CDocument)

BEGIN_MESSAGE_MAP(CFormatDoc, CDocument)
	//{{AFX_MSG_MAP(CFormatDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormatDoc construction/destruction

CFormatDoc::CFormatDoc()
{
	// TODO: add one-time construction code here

}

CFormatDoc::~CFormatDoc()
{
}

BOOL CFormatDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFormatDoc serialization

void CFormatDoc::Serialize(CArchive& ar)
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
// CFormatDoc diagnostics

#ifdef _DEBUG
void CFormatDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFormatDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormatDoc commands
