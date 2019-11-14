// TransLogDoc.cpp : implementation file
//

#include "stdafx.h"
#include "UmspFinance.h"
#include "TransLogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransLogDoc

IMPLEMENT_DYNCREATE(CTransLogDoc, CDocument)

CTransLogDoc::CTransLogDoc()
{
}

BOOL CTransLogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CTransLogDoc::~CTransLogDoc()
{
}


BEGIN_MESSAGE_MAP(CTransLogDoc, CDocument)
	//{{AFX_MSG_MAP(CTransLogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransLogDoc diagnostics

#ifdef _DEBUG
void CTransLogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTransLogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransLogDoc serialization

void CTransLogDoc::Serialize(CArchive& ar)
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
// CTransLogDoc commands
