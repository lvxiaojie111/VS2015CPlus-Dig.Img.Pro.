// chap1_5View.cpp : implementation of the CChap1_5View class
//

#include "stdafx.h"
#include "chap1_5.h"

#include "chap1_5Doc.h"
#include "chap1_5View.h"
#include "MainFrm.h"
#include "ImageCenterDib.h"//dib类头文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChap1_5View

IMPLEMENT_DYNCREATE(CChap1_5View, CScrollView)

BEGIN_MESSAGE_MAP(CChap1_5View, CScrollView)
	//{{AFX_MSG_MAP(CChap1_5View)
	ON_COMMAND(id_DataAccess1, OnDataAccess1)
	ON_COMMAND(id_DataAccess2, OnDataAccess2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChap1_5View construction/destruction

CChap1_5View::CChap1_5View()
{
	// TODO: add construction code here

}

CChap1_5View::~CChap1_5View()
{
}

BOOL CChap1_5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CChap1_5View drawing

void CChap1_5View::OnDraw(CDC* pDC)
{
	//获取文档类指针
	CChap1_5Doc* pDoc = GetDocument();

	//返回m_dib的指针
	ImgCenterDib *pDib=pDoc->GetPDib();

	//获取DIB的尺寸
	CSize sizeFileDib = pDib->GetDimensions();

	//显示DIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}

void CChap1_5View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//获取文档类指针
	CChap1_5Doc* pDoc = GetDocument();

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
// CChap1_5View diagnostics

#ifdef _DEBUG
void CChap1_5View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CChap1_5View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CChap1_5Doc* CChap1_5View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChap1_5Doc)));
	return (CChap1_5Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChap1_5View message handlers

void CChap1_5View::OnDataAccess1() 
{
	
	//获取文档类指针
	CChap1_5Doc *pDoc=GetDocument();
	
	//获取ImgCenterDib类对象的指针，访问打开文件的数据
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//位图数据的指针
	unsigned char *imgData=pDib->m_pImgData;
	
	//位图阵列的大小
	CSize imgSize=pDib->GetDimensions();
	
	//每像素的位数
	int nBitCount=pDib->m_nBitCount;
	
	//循环变量，图像坐标
	int i,j;
	
	//每像素占字节数
	int bytePerPixel=nBitCount/8;
	
	//每行像素所占字节数，必须是4的倍数
	int lineByte=(imgSize.cx*nBitCount/8+3)/4*4;
	
	//循环变量，每像素各字节访问的循环变量
	int k;
	
	//将图像左下角1/4部分置黑色
	for(i=0;i<imgSize.cy/2;i++){
		for(j=0;j<imgSize.cx/2;j++){
			for(k=0;k<bytePerPixel;k++){
				*(imgData+i*lineByte+j*bytePerPixel+k)=0;
			}
		}
	}
	
	//刷新显示
	Invalidate();
}

void CChap1_5View::OnDataAccess2() 
{
	//获取文档类指针
	CChap1_5Doc *pDoc=GetDocument();
	
	//获取ImgCenterDib类对象的指针，访问打开文件的数据
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//位图数据的指针
	unsigned char *imgData=pDib->m_pImgData;
	
	//位图阵列的大小
	CSize imgSize=pDib->GetDimensions();
	
	//每像素的位数
	int nBitCount=pDib->m_nBitCount;
	
	//每像素占字节数
	int bytePerPixel=nBitCount/8;
	
	//每行像素所占字节数，必须是4的倍数
	int lineByte=(imgSize.cx*nBitCount/8+3)/4*4;

	//申请缓冲区pBuf
	unsigned char* pBuf=new unsigned char[lineByte*imgSize.cy];

	//将原DIB位图数据拷贝至pBuf
	memcpy(pBuf, imgData, lineByte*imgSize.cy);
	
	//循环变量，图像坐标
	int i,j;
	//循环变量，每像素各字节访问的循环变量
	int k;
	
	//将pBuf左下角1/4部分置黑色
	for(i=0;i<imgSize.cy/2;i++){
		for(j=0;j<imgSize.cx/2;j++){
			for(k=0;k<bytePerPixel;k++){
				*(pBuf+i*lineByte+j*bytePerPixel+k)=0;
			}
		}
	}
	
	//打开新视图，显示分割结果
  CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
  //发送一个新建文件的消息，创建一个新的文档-视图
  pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);

  //获取新建视图指针
  CChap1_5View* pView=(CChap1_5View*)pFrame->MDIGetActive()->GetActiveView();

  //获取相关联的新的文档类指针
  CChap1_5Doc* pDocNew=pView->GetDocument();

  //获取新文档中的ImgCenterDib类对象指针
  ImgCenterDib *dibNew=pDocNew->GetPDib();
  
  //调用ReplaceDib，用改变以后的位图数据替换原位图,
  dibNew->ReplaceDib(imgSize,nBitCount,pDib->m_lpColorTable, pBuf);

  //文档数据置脏，提示存盘信息
  pDocNew->SetModifiedFlag(TRUE);

  //各视图刷新显示
  pDocNew->UpdateAllViews(pView);
}
