// chap1_2Doc.h : interface of the CChap1_2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_2DOC_H__CE8461CD_AFD1_41A4_8714_B97EB63122CF__INCLUDED_)
#define AFX_CHAP1_2DOC_H__CE8461CD_AFD1_41A4_8714_B97EB63122CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_2Doc : public CDocument
{
protected: // create from serialization only
	CChap1_2Doc();
	DECLARE_DYNCREATE(CChap1_2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_2DOC_H__CE8461CD_AFD1_41A4_8714_B97EB63122CF__INCLUDED_)
