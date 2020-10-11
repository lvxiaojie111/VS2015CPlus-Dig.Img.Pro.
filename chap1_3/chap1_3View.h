// chap1_3View.h : interface of the CChap1_3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_3VIEW_H__799C9761_16B5_4C45_A21F_35E38F068288__INCLUDED_)
#define AFX_CHAP1_3VIEW_H__799C9761_16B5_4C45_A21F_35E38F068288__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_3View : public CView
{
protected: // create from serialization only
	CChap1_3View();
	DECLARE_DYNCREATE(CChap1_3View)

// Attributes
public:
	CChap1_3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_3View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_3View)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chap1_3View.cpp
inline CChap1_3Doc* CChap1_3View::GetDocument()
   { return (CChap1_3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_3VIEW_H__799C9761_16B5_4C45_A21F_35E38F068288__INCLUDED_)
