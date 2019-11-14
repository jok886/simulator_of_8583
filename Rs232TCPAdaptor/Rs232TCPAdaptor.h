// Rs232TCPAdaptor.h : main header file for the RS232TCPADAPTOR application
//

#if !defined(AFX_RS232TCPADAPTOR_H__D338208A_FE67_465E_AEAE_C4E540997660__INCLUDED_)
#define AFX_RS232TCPADAPTOR_H__D338208A_FE67_465E_AEAE_C4E540997660__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRs232TCPAdaptorApp:
// See Rs232TCPAdaptor.cpp for the implementation of this class
//

class CRs232TCPAdaptorApp : public CWinApp
{
public:
	CRs232TCPAdaptorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRs232TCPAdaptorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRs232TCPAdaptorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RS232TCPADAPTOR_H__D338208A_FE67_465E_AEAE_C4E540997660__INCLUDED_)
