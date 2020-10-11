// chap1_5Doc.h : interface of the CChap1_5Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_5DOC_H__CC900299_2DB1_481F_9E49_7CE4E0E0BCAF__INCLUDED_)
#define AFX_CHAP1_5DOC_H__CC900299_2DB1_481F_9E49_7CE4E0E0BCAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageCenterDib.h"

class CChap1_5Doc : public CDocument
{
protected: // create from serialization only
	CChap1_5Doc();
	DECLARE_DYNCREATE(CChap1_5Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_5Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_5Doc();

	//返回m_dib的指针
	ImgCenterDib *GetPDib()
	{
		return &m_dib;
	}

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

private:

	//ImgCenterDib类的对象
	ImgCenterDib m_dib;

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_5Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_5DOC_H__CC900299_2DB1_481F_9E49_7CE4E0E0BCAF__INCLUDED_)
