// UmspFinance.h : main header file for the UMSPFINANCE application
//

#if !defined(AFX_UMSPFINANCE_H__ED5FA212_5CE8_48A0_9294_D39CE751824F__INCLUDED_)
#define AFX_UMSPFINANCE_H__ED5FA212_5CE8_48A0_9294_D39CE751824F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CUmspFinanceApp:
// See UmspFinance.cpp for the implementation of this class
//

class CUmspFinanceApp : public CWinApp
{
public:
	CUmspFinanceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUmspFinanceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CUmspFinanceApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UMSPFINANCE_H__ED5FA212_5CE8_48A0_9294_D39CE751824F__INCLUDED_)
