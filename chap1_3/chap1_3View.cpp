// chap1_3View.cpp : implementation of the CChap1_3View class
//

#include "stdafx.h"
#include "chap1_3.h"

#include "chap1_3Doc.h"
#include "chap1_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_3View

IMPLEMENT_DYNCREATE(CChap1_3View, CView)

BEGIN_MESSAGE_MAP(CChap1_3View, CView)
	//{{AFX_MSG_MAP(CChap1_3View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_3View construction/destruction

CChap1_3View::CChap1_3View()
{
	// TODO: add construction code here

}

CChap1_3View::~CChap1_3View()
{
}

BOOL CChap1_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_3View drawing

void CChap1_3View::OnDraw(CDC* pDC)
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

	//��128*128��ͼ��������ʾ���ԣ�0��0���㿪ʼ��450*250��һ��������
	pDC->StretchBlt(0,0,450,250, &dcMemory,0,0,400,300,SRCCOPY);

	//�ͷ�bitmap���ָ�ԭGDIλͼ
	dcMemory.SelectObject(oldbitmap);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_3View diagnostics

#ifdef _DEBUG
void CChap1_3View::AssertValid() const
{
	CView::AssertValid();
}

void CChap1_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChap1_3Doc* CChap1_3View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap1_3Doc)));
	return (CChap1_3Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_3View message handlers
