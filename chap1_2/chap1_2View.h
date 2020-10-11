// chap1_2View.h : interface of the CChap1_2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_2VIEW_H__E0B11A5D_27F0_4E24_BE1F_711AB1255447__INCLUDED_)
#define AFX_CHAP1_2VIEW_H__E0B11A5D_27F0_4E24_BE1F_711AB1255447__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_2View : public CView
{
protected: // create from serialization only
	CChap1_2View();
	DECLARE_DYNCREATE(CChap1_2View)

// Attributes
public:
	CChap1_2Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_2View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chap1_2View.cpp
inline CChap1_2Doc* CChap1_2View::GetDocument()
   { return (CChap1_2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_2VIEW_H__E0B11A5D_27F0_4E24_BE1F_711AB1255447__INCLUDED_)
