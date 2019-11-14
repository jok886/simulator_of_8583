// PSAMOPDEMODoc.h : interface of the CPSAMOPDEMODoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSAMOPDEMODOC_H__33F10660_C1FF_485F_90EC_FB454F8ABAFF__INCLUDED_)
#define AFX_PSAMOPDEMODOC_H__33F10660_C1FF_485F_90EC_FB454F8ABAFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPSAMOPDEMODoc : public CDocument
{
protected: // create from serialization only
	CPSAMOPDEMODoc();
	DECLARE_DYNCREATE(CPSAMOPDEMODoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSAMOPDEMODoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSAMOPDEMODoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPSAMOPDEMODoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSAMOPDEMODOC_H__33F10660_C1FF_485F_90EC_FB454F8ABAFF__INCLUDED_)
