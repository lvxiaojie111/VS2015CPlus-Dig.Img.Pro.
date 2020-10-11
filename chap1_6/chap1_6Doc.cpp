// chap1_6Doc.cpp : implementation of the CChap1_6Doc class
//

#include "stdafx.h"
#include "chap1_6.h"

#include "chap1_6Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_6Doc

IMPLEMENT_DYNCREATE(CChap1_6Doc, CDocument)

BEGIN_MESSAGE_MAP(CChap1_6Doc, CDocument)
	//{{AFX_MSG_MAP(CChap1_6Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_6Doc construction/destruction

CChap1_6Doc::CChap1_6Doc()
{
	// TODO: add one-time construction code here

}

CChap1_6Doc::~CChap1_6Doc()
{
}

BOOL CChap1_6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChap1_6Doc serialization

void CChap1_6Doc::Serialize(CArchive& ar)
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
// CChap1_6Doc diagnostics

#ifdef _DEBUG
void CChap1_6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChap1_6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_6Doc commands

BOOL CChap1_6Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (m_dib.Read(lpszPathName) == TRUE) {	
		SetModifiedFlag(FALSE);     // start off with unmodified
		return TRUE;
	}
	else 
		return FALSE;
}

BOOL CChap1_6Doc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	if(m_dib.Write(lpszPathName) == TRUE)	{
		SetModifiedFlag(FALSE);     // have saved
		return TRUE;
	}
	else 
		return FALSE;
}
