// Format.h : main header file for the FORMAT application
//

#if !defined(AFX_FORMAT_H__226725EF_ED4A_4148_A69A_961CDFAFA97B__INCLUDED_)
#define AFX_FORMAT_H__226725EF_ED4A_4148_A69A_961CDFAFA97B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFormatApp:
// See Format.cpp for the implementation of this class
//

class CFormatApp : public CWinApp
{
public:
	CFormatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CFormatApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMAT_H__226725EF_ED4A_4148_A69A_961CDFAFA97B__INCLUDED_)
