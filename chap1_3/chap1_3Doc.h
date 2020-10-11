// chap1_3Doc.h : interface of the CChap1_3Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_3DOC_H__844F1201_0675_4149_AAEC_5F2815833434__INCLUDED_)
#define AFX_CHAP1_3DOC_H__844F1201_0675_4149_AAEC_5F2815833434__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_3Doc : public CDocument
{
protected: // create from serialization only
	CChap1_3Doc();
	DECLARE_DYNCREATE(CChap1_3Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_3Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_3Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_3DOC_H__844F1201_0675_4149_AAEC_5F2815833434__INCLUDED_)
