// chap1_6View.cpp : implementation of the CChap1_6View class
//

#include "stdafx.h"
#include "chap1_6.h"

#include "chap1_6Doc.h"
#include "chap1_6View.h"
#include "ImageCenterDib.h"//dib��ͷ�ļ�
#include "SpecialEffectShow.h"//��Ч��ʾ��
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_6View

IMPLEMENT_DYNCREATE(CChap1_6View, CScrollView)

BEGIN_MESSAGE_MAP(CChap1_6View, CScrollView)
	//{{AFX_MSG_MAP(CChap1_6View)
	ON_COMMAND(ID_SCAN, OnScan)
	ON_COMMAND(ID_SLIDE, OnSlide)
	ON_COMMAND(ID_FADEIN, OnFadein)
	ON_COMMAND(ID_MOSAIK, OnMosaik)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_6View construction/destruction

CChap1_6View::CChap1_6View()
{
	// TODO: add construction code here

}

CChap1_6View::~CChap1_6View()
{
}

BOOL CChap1_6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_6View drawing

void CChap1_6View::OnDraw(CDC* pDC)
{
	//��ȡ�ĵ���ָ��
	CChap1_6Doc* pDoc = GetDocument();

	//����m_dib��ָ��
	ImgCenterDib *pDib=pDoc->GetPDib();

	//��ȡDIB�ĳߴ�
	CSize sizeFileDib = pDib->GetDimensions();

	//��ʾDIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}

void CChap1_6View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//��ȡ�ĵ���ָ��
	CChap1_6Doc* pDoc = GetDocument();

	//��ȡDIB��ָ��
	ImgCenterDib *pDib=pDoc->GetPDib();

	//����DIB�ߴ������Ӵ���С
	if(pDib!=NULL)
    	SetScrollSizes(MM_TEXT, pDib->GetDimensions());
	else{
		//���m_dibΪ�գ�������һ���̶��ĳߴ�
		CSize sizeTotal;
		sizeTotal.cx = sizeTotal.cy = 100;
		SetScrollSizes(MM_TEXT, sizeTotal);
	}

}

/////////////////////////////////////////////////////////////////////////////
// CChap1_6View diagnostics

#ifdef _DEBUG
void CChap1_6View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CChap1_6View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CChap1_6Doc* CChap1_6View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap1_6Doc)));
	return (CChap1_6Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_6View message handlers

void CChap1_6View::OnScan() 
{
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();

	//ֻ�����ɫͼ���Ҷ�ͼ��
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}

	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	//����豸��������
	CClientDC aDC(this);

	//����ɨ����򣬴����豸����ָ��
	SpShow.Scan(&aDC);
}

void CChap1_6View::OnSlide() 
{
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}
	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//����豸��������
	SpShow.Slide(&aDC);//���û�����ʾ���򣬴����豸����ָ��
}

void CChap1_6View::OnFadein() 
{
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}

	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//����豸��������
	SpShow.FadeIn(&aDC);//���ý�����ʾ���򣬴����豸����ָ��	
}

void CChap1_6View::OnMosaik() 
{
	//��ȡ�ĵ�����m_dib��ָ�룬���ʵ�ǰDIB����
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"ֻ�����ɫ�ͻҶ�ͼ��",MB_OK,0);
	  return ;
	}

	//����SpecialEffectShow��Ķ���SpShow���õ�ǰDIB����Ϊ���ʼ��
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//����豸��������
	SpShow.Mosaik(&aDC);//������������ʾ���򣬴����豸����ָ��
}
