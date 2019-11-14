// PSAMOPDEMO.h : main header file for the PSAMOPDEMO application
//

#if !defined(AFX_PSAMOPDEMO_H__41AFBE76_C0DF_406B_A2DC_FBC4CDF3CF08__INCLUDED_)
#define AFX_PSAMOPDEMO_H__41AFBE76_C0DF_406B_A2DC_FBC4CDF3CF08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPSAMOPDEMOApp:
// See PSAMOPDEMO.cpp for the implementation of this class
//

class CPSAMOPDEMOApp : public CWinApp
{
public:
	CPSAMOPDEMOApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSAMOPDEMOApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPSAMOPDEMOApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSAMOPDEMO_H__41AFBE76_C0DF_406B_A2DC_FBC4CDF3CF08__INCLUDED_)
