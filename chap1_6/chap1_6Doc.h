// chap1_6Doc.h : interface of the CChap1_6Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHAP1_6DOC_H__B1D1C6A1_1833_4FB4_9306_04F2E14A6597__INCLUDED_)
#define AFX_CHAP1_6DOC_H__B1D1C6A1_1833_4FB4_9306_04F2E14A6597__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageCenterDib.h"

class CChap1_6Doc : public CDocument
{
protected: // create from serialization only
	CChap1_6Doc();
	DECLARE_DYNCREATE(CChap1_6Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_6Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChap1_6Doc();
	
	//����m_dib��ָ��
	ImgCenterDib *GetPDib()
	{
		return &m_dib;
	}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
private:

	//ImgCenterDib��Ķ���
	ImgCenterDib m_dib;

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChap1_6Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_6DOC_H__B1D1C6A1_1833_4FB4_9306_04F2E14A6597__INCLUDED_)
