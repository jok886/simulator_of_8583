// yy.h : main header file for the YY application
//

#if !defined(AFX_YY_H__DB3598EF_D6F6_461D_8071_7F8430D75DC7__INCLUDED_)
#define AFX_YY_H__DB3598EF_D6F6_461D_8071_7F8430D75DC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CYyApp:
// See yy.cpp for the implementation of this class
//

class CYyApp : public CWinApp
{
public:
	CYyApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CYyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YY_H__DB3598EF_D6F6_461D_8071_7F8430D75DC7__INCLUDED_)
