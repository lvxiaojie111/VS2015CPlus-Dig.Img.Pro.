// chap1_5View.cpp : implementation of the CChap1_5View class
//

#include "stdafx.h"
#include "chap1_5.h"

#include "chap1_5Doc.h"
#include "chap1_5View.h"
#include "MainFrm.h"
#include "ImageCenterDib.h"//dib��ͷ�ļ�

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
	//��ȡ�ĵ���ָ��
	CChap1_5Doc* pDoc = GetDocument();

	//����m_dib��ָ��
	ImgCenterDib *pDib=pDoc->GetPDib();

	//��ȡDIB�ĳߴ�
	CSize sizeFileDib = pDib->GetDimensions();

	//��ʾDIB
	pDib->Draw(pDC, CPoint(0, 0), sizeFileDib);
}

void CChap1_5View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//��ȡ�ĵ���ָ��
	CChap1_5Doc* pDoc = GetDocument();

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
	
	//��ȡ�ĵ���ָ��
	CChap1_5Doc *pDoc=GetDocument();
	
	//��ȡImgCenterDib������ָ�룬���ʴ��ļ�������
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//λͼ���ݵ�ָ��
	unsigned char *imgData=pDib->m_pImgData;
	
	//λͼ���еĴ�С
	CSize imgSize=pDib->GetDimensions();
	
	//ÿ���ص�λ��
	int nBitCount=pDib->m_nBitCount;
	
	//ѭ��������ͼ������
	int i,j;
	
	//ÿ����ռ�ֽ���
	int bytePerPixel=nBitCount/8;
	
	//ÿ��������ռ�ֽ�����������4�ı���
	int lineByte=(imgSize.cx*nBitCount/8+3)/4*4;
	
	//ѭ��������ÿ���ظ��ֽڷ��ʵ�ѭ������
	int k;
	
	//��ͼ�����½�1/4�����ú�ɫ
	for(i=0;i<imgSize.cy/2;i++){
		for(j=0;j<imgSize.cx/2;j++){
			for(k=0;k<bytePerPixel;k++){
				*(imgData+i*lineByte+j*bytePerPixel+k)=0;
			}
		}
	}
	
	//ˢ����ʾ
	Invalidate();
}

void CChap1_5View::OnDataAccess2() 
{
	//��ȡ�ĵ���ָ��
	CChap1_5Doc *pDoc=GetDocument();
	
	//��ȡImgCenterDib������ָ�룬���ʴ��ļ�������
	ImgCenterDib *pDib=pDoc->GetPDib();
	
	//λͼ���ݵ�ָ��
	unsigned char *imgData=pDib->m_pImgData;
	
	//λͼ���еĴ�С
	CSize imgSize=pDib->GetDimensions();
	
	//ÿ���ص�λ��
	int nBitCount=pDib->m_nBitCount;
	
	//ÿ����ռ�ֽ���
	int bytePerPixel=nBitCount/8;
	
	//ÿ��������ռ�ֽ�����������4�ı���
	int lineByte=(imgSize.cx*nBitCount/8+3)/4*4;

	//���뻺����pBuf
	unsigned char* pBuf=new unsigned char[lineByte*imgSize.cy];

	//��ԭDIBλͼ���ݿ�����pBuf
	memcpy(pBuf, imgData, lineByte*imgSize.cy);
	
	//ѭ��������ͼ������
	int i,j;
	//ѭ��������ÿ���ظ��ֽڷ��ʵ�ѭ������
	int k;
	
	//��pBuf���½�1/4�����ú�ɫ
	for(i=0;i<imgSize.cy/2;i++){
		for(j=0;j<imgSize.cx/2;j++){
			for(k=0;k<bytePerPixel;k++){
				*(pBuf+i*lineByte+j*bytePerPixel+k)=0;
			}
		}
	}
	
	//������ͼ����ʾ�ָ���
  CMainFrame* pFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
  //����һ���½��ļ�����Ϣ������һ���µ��ĵ�-��ͼ
  pFrame->SendMessage(WM_COMMAND, ID_FILE_NEW);

  //��ȡ�½���ͼָ��
  CChap1_5View* pView=(CChap1_5View*)pFrame->MDIGetActive()->GetActiveView();

  //��ȡ��������µ��ĵ���ָ��
  CChap1_5Doc* pDocNew=pView->GetDocument();

  //��ȡ���ĵ��е�ImgCenterDib�����ָ��
  ImgCenterDib *dibNew=pDocNew->GetPDib();
  
  //����ReplaceDib���øı��Ժ��λͼ�����滻ԭλͼ,
  dibNew->ReplaceDib(imgSize,nBitCount,pDib->m_lpColorTable, pBuf);

  //�ĵ��������࣬��ʾ������Ϣ
  pDocNew->SetModifiedFlag(TRUE);

  //����ͼˢ����ʾ
  pDocNew->UpdateAllViews(pView);
}
