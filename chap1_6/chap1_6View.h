// chap1_6View.h : interface of the CChap1_6View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_6VIEW_H__D5DC2090_B364_44FF_9F54_BFFACB1ED4E4__INCLUDED_)
#define AFX_CHAP1_6VIEW_H__D5DC2090_B364_44FF_9F54_BFFACB1ED4E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CChap1_6View : public CScrollView
{
protected: // create from serialization only
	CChap1_6View();
	DECLARE_DYNCREATE(CChap1_6View)

// Attributes
public:
	CChap1_6Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_6View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_6View)
	afx_msg void OnScan();
	afx_msg void OnSlide();
	afx_msg void OnFadein();
	afx_msg void OnMosaik();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in chap1_6View.cpp
inline CChap1_6Doc* CChap1_6View::GetDocument()
   { return (CChap1_6Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_6VIEW_H__D5DC2090_B364_44FF_9F54_BFFACB1ED4E4__INCLUDED_)
