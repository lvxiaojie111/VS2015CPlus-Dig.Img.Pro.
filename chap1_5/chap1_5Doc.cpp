// chap1_5Doc.cpp : implementation of the CChap1_5Doc class
//

#include "stdafx.h"
#include "chap1_5.h"

#include "chap1_5Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_5Doc

IMPLEMENT_DYNCREATE(CChap1_5Doc, CDocument)

BEGIN_MESSAGE_MAP(CChap1_5Doc, CDocument)
	//{{AFX_MSG_MAP(CChap1_5Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_5Doc construction/destruction

CChap1_5Doc::CChap1_5Doc()
{
	// TODO: add one-time construction code here

}

CChap1_5Doc::~CChap1_5Doc()
{
}

BOOL CChap1_5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChap1_5Doc serialization

void CChap1_5Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_5Doc diagnostics

#ifdef _DEBUG
void CChap1_5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChap1_5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_5Doc commands

BOOL CChap1_5Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_dib.Read(lpszPathName) == TRUE) {	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return FALSE;
}

BOOL CChap1_5Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(m_dib.Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return FALSE;
}
