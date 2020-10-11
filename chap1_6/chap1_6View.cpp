// chap1_6View.cpp : implementation of the CChap1_6View class
//

#include "stdafx.h"
#include "chap1_6.h"

#include "chap1_6Doc.h"
#include "chap1_6View.h"
#include "ImageCenterDib.h"//dib类头文件
#include "SpecialEffectShow.h"//特效显示类
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
	//获取文档类指针
	CChap1_6Doc* pDoc = GetDocument();

	//返回m_dib的指针
	ImgCenterDib *pDib=pDoc->GetPDib();

	//获取DIB的尺寸
	CSize sizeFileDib = pDib->GetDimensions();

	//显示DIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}

void CChap1_6View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//获取文档类指针
	CChap1_6Doc* pDoc = GetDocument();

	//获取DIB的指针
	ImgCenterDib *pDib=pDoc->GetPDib();

	//根据DIB尺寸设置视窗大小
	if(pDib!=NULL)
    	SetScrollSizes(MM_TEXT, pDib->GetDimensions());
	else{
		//如果m_dib为空，则设置一个固定的尺寸
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
	//获取文档类中m_dib的指针，访问当前DIB数据
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();

	//只处理彩色图像或灰度图象
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}

	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	//获得设备环境变量
	CClientDC aDC(this);

	//调用扫描程序，传递设备环境指针
	SpShow.Scan(&aDC);
}

void CChap1_6View::OnSlide() 
{
	//获取文档类中m_dib的指针，访问当前DIB数据
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}
	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//获得设备环境变量
	SpShow.Slide(&aDC);//调用滑动显示程序，传递设备环境指针
}

void CChap1_6View::OnFadein() 
{
	//获取文档类中m_dib的指针，访问当前DIB数据
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}

	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//获得设备环境变量
	SpShow.FadeIn(&aDC);//调用渐进显示程序，传递设备环境指针	
}

void CChap1_6View::OnMosaik() 
{
	//获取文档类中m_dib的指针，访问当前DIB数据
	CChap1_6Doc *pDoc=GetDocument();
	ImgCenterDib *pDib=pDoc->GetPDib();
	if(pDib->m_nBitCount!=24&&pDib->m_nBitCount!=8){
	  ::MessageBox(0,"只处理彩色和灰度图像",MB_OK,0);
	  return ;
	}

	//定义SpecialEffectShow类的对象SpShow，用当前DIB数据为其初始化
	SpecialEffectShow SpShow(pDib->GetDimensions(),
	  pDib->m_nBitCount,pDib->m_lpColorTable,pDib->m_pImgData);

	CClientDC aDC(this);//获得设备环境变量
	SpShow.Mosaik(&aDC);//调用马赛克显示程序，传递设备环境指针
}
