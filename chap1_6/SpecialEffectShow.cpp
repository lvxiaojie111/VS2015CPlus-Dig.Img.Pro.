// SpecialEffectShow.cpp: implementation of the SpecialEffectShow class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SpecialEffectShow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SpecialEffectShow::SpecialEffectShow(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
					   unsigned char *pImgData)
					   :ImgCenterDib(size, nBitCount, lpColorTable, pImgData)
{

}

SpecialEffectShow::~SpecialEffectShow()
{

}

void SpecialEffectShow::Scan(CDC *pDC) //ɨ����ʾһ��ͼ��
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(255,255,255));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɰ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

	for(int j=0;j<bitmapHeight;j++)//ɨ����Ч��ʾ�ľ����㷨
	{
		::StretchDIBits(pDC->GetSafeHdc(),
			0, j, bitmapWidth, 1,
			0, bitmapHeight-j, bitmapWidth, 1,
			m_pImgData, pBitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//������ʱʱ��
	}
}

void SpecialEffectShow::Slide(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(255,255,255));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɰ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

	for(int i=0;i<=bitmapWidth;i++)//������Ч��ʾ�ľ����㷨
	{
		for(int j=0;j<=bitmapHeight;j=j+8)
		{
			::StretchDIBits(pDC->GetSafeHdc(),
				0,  j-8 ,  i+1, 8,
				bitmapWidth-i, bitmapHeight-j, i+1, 8,
				m_pImgData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
		Sleep(3);//������ʱʱ��
	}
}

void SpecialEffectShow::FadeIn(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(0,0,0));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɺ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����

		
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;//ÿ������ռ�ֽ���������Ϊ4�ı���
	LPBYTE temp =new BYTE[bitmapHeight*lineByte];//�ڶ��Ϸ����ڴ�洢��ʱͼ������
	memset (temp,0,bitmapHeight*lineByte);//��ʼ����

	for(int m=0;m<256;m++)
	{
		for(int j = 0; j < bitmapHeight; j++)
		{
			for(int i = 0; i < lineByte; i ++)
				temp[j*lineByte+i]=m_pImgData[j*lineByte+i]*m/256;
		}
		::StretchDIBits(pDC->GetSafeHdc(),
			0, 0, bitmapWidth, bitmapHeight,
			0, 0, bitmapWidth, bitmapHeight,
			temp, pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//������ʱʱ��
	}
	delete [] temp;//�ͷŶ��Ϸ�����ڴ�
}

void SpecialEffectShow::Mosaik(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//���Դͼ��Ŀ�ȣ�������Ϊ��λ
	int bitmapHeight=GetDimensions().cy;//���Դͼ��ĸ߶ȣ�������Ϊ��λ

	CRect rect(0,0,bitmapWidth,bitmapHeight);//��Դͼ��ĳߴ紴��һ������
	CBrush brush(RGB(255,255,255));	//���û�ˢΪ��ɫ
	pDC->FillRect(&rect,&brush);//���Ѿ���ʾ������ԭͼ���������óɰ�ɫ���ﵽˢ����Ļ��Ч��

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//Ϊ��ӦStretchDIBits��������Ҫ����ͼ����Ϣͷָ��ǿ��ת��ΪLPBITMAPINFO����


	//�����˵Ĵ�С����Ϊ��߶���12������
	int WithFalg=0; //ͼ�����12���������ı�־
	int HeightFlag=0;//ͼ�����12���������ı�־
	if((bitmapWidth%12)!=0)WithFalg=1;
	if((bitmapHeight%12)!=0)HeightFlag=1;
	long ArrayLength=(bitmapWidth/12+WithFalg)*(bitmapHeight/12+HeightFlag);
	//��ͼ���߶�������12��������,Ȼ��ͼ��ֳ�12X12��С�飬����˳�����г�һ������

	struct Square
	{
		CPoint pt;//��¼ÿ��12X12��С������Ͻ�����
		bool HitFlag;//�����ɨ������С���ʱ�򣬼�¼�Ƿ�������ɨ���
	};//�Լ�����һ���ṹ����һ��Cpoint���ͺ�һ�����б�־����

	Square* SquareArray=new Square[ArrayLength];
	int x=0;
	int y=0;

	for(int i=0; i<ArrayLength; i++)
	{
		//��ʼ��ÿ��С��������
		SquareArray[i].pt.x=x;
		SquareArray[i].pt.y=y;
		x=x+12;
		if(x>bitmapWidth)
		{x=0;y=y+12;}

		//��ʼ����С�鶼δ�����й�
		SquareArray[i].HitFlag=FALSE;
	}
	
	long RandNum;//�漴����
	srand( (unsigned)time( NULL ) );//�����������
	int i;
	for(i=0;i<=ArrayLength;i++)
	{	
		do
		{
			RandNum=(long)( ( (double)ArrayLength )*rand()/RAND_MAX );//���������0��ArrayLength-1֮��ȡֵ
			x=SquareArray[RandNum].pt.x;
			y=SquareArray[RandNum].pt.y;		
		}while(SquareArray[RandNum].HitFlag==TRUE);//���С����ǰ�Ƿ񱻻��й�������ǣ����¼���һ�������
		SquareArray[RandNum].HitFlag=TRUE;//���û��б�־

		::StretchDIBits(pDC->GetSafeHdc(),
			x, y, 12,12,
			x,bitmapHeight-y-12, 12,12,
			m_pImgData, pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
		Sleep(1);//������ʱʱ��
	}
	delete [] SquareArray;
}
