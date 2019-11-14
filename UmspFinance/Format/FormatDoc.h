// FormatDoc.h : interface of the CFormatDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMATDOC_H__F2116CE0_D2BE_4C7E_B69E_9251A01D504D__INCLUDED_)
#define AFX_FORMATDOC_H__F2116CE0_D2BE_4C7E_B69E_9251A01D504D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFormatDoc : public CDocument
{
protected: // create from serialization only
	CFormatDoc();
	DECLARE_DYNCREATE(CFormatDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormatDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFormatDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormatDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMATDOC_H__F2116CE0_D2BE_4C7E_B69E_9251A01D504D__INCLUDED_)
