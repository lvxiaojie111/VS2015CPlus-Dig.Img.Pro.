// chap1_5View.h : interface of the CChap1_5View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_5VIEW_H__50555E1C_4B83_4655_9A9B_D9F4EA35ECC2__INCLUDED_)
#define AFX_CHAP1_5VIEW_H__50555E1C_4B83_4655_9A9B_D9F4EA35ECC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_5View : public CScrollView
{
protected: // create from serialization only
	CChap1_5View();
	DECLARE_DYNCREATE(CChap1_5View)

// Attributes
public:
	CChap1_5Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_5View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_5View)
	afx_msg void OnDataAccess1();
	afx_msg void OnDataAccess2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chap1_5View.cpp
inline CChap1_5Doc* CChap1_5View::GetDocument()
   { return (CChap1_5Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_5VIEW_H__50555E1C_4B83_4655_9A9B_D9F4EA35ECC2__INCLUDED_)
