// chap1_2View.cpp : implementation of the CChap1_2View class
//

#include "stdafx.h"
#include "chap1_2.h"

#include "chap1_2Doc.h"
#include "chap1_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_2View

IMPLEMENT_DYNCREATE(CChap1_2View, CView)

BEGIN_MESSAGE_MAP(CChap1_2View, CView)
	//{{AFX_MSG_MAP(CChap1_2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_2View construction/destruction

CChap1_2View::CChap1_2View()
{
	// TODO: add construction code here

}

CChap1_2View::~CChap1_2View()
{
}

BOOL CChap1_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_2View drawing

void CChap1_2View::OnDraw(CDC* pDC)
{
	//CBitmap����
	CBitmap bitmap;

	//�豸���������
	CDC dcMemory;

	//������Դλͼ
	bitmap.LoadBitmap(IDB_building);

	//�����ڴ��豸����
	dcMemory.CreateCompatibleDC(pDC);

	//��λͼѡ���ڴ��豸������������ɵ�GDIλͼ����
	CBitmap *oldbitmap=dcMemory.SelectObject(&bitmap);

	//��ʾ
	pDC->BitBlt(0,0,400,300, &dcMemory,0,0,SRCCOPY);

	//�ͷ�bitmap���ָ�ԭGDIλͼ
	dcMemory.SelectObject(oldbitmap);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_2View diagnostics

#ifdef _DEBUG
void CChap1_2View::AssertValid() const
{
	CView::AssertValid();
}

void CChap1_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap1_2Doc* CChap1_2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap1_2Doc)));
	return (CChap1_2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_2View message handlers
