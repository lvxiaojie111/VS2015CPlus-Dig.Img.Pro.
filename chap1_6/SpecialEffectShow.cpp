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

void SpecialEffectShow::Scan(CDC *pDC) //扫描显示一幅图象
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(255,255,255));	//设置画刷为白色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成白色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

	for(int j=0;j<bitmapHeight;j++)//扫描特效显示的具体算法
	{
		::StretchDIBits(pDC->GetSafeHdc(),
			0, j, bitmapWidth, 1,
			0, bitmapHeight-j, bitmapWidth, 1,
			m_pImgData, pBitmapInfo,
			DIB_RGB_COLORS, SRCCOPY);
		Sleep(3);//设置延时时间
	}
}

void SpecialEffectShow::Slide(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(255,255,255));	//设置画刷为白色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成白色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

	for(int i=0;i<=bitmapWidth;i++)//滑动特效显示的具体算法
	{
		for(int j=0;j<=bitmapHeight;j=j+8)
		{
			::StretchDIBits(pDC->GetSafeHdc(),
				0,  j-8 ,  i+1, 8,
				bitmapWidth-i, bitmapHeight-j, i+1, 8,
				m_pImgData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
		}
		Sleep(3);//设置延时时间
	}
}

void SpecialEffectShow::FadeIn(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(0,0,0));	//设置画刷为黑色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成黑色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型

		
	int lineByte=(m_imgWidth*m_nBitCount/8+3)/4*4;//每行像素占字节数，必须为4的倍数
	LPBYTE temp =new BYTE[bitmapHeight*lineByte];//在堆上分配内存存储临时图象数据
	memset (temp,0,bitmapHeight*lineByte);//初始置零

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
		Sleep(3);//设置延时时间
	}
	delete [] temp;//释放堆上分配的内存
}

void SpecialEffectShow::Mosaik(CDC *pDC)
{
	int bitmapWidth=GetDimensions().cx;//获得源图象的宽度，以象素为单位
	int bitmapHeight=GetDimensions().cy;//获得源图象的高度，以象素为单位

	CRect rect(0,0,bitmapWidth,bitmapHeight);//以源图象的尺寸创建一个矩形
	CBrush brush(RGB(255,255,255));	//设置画刷为白色
	pDC->FillRect(&rect,&brush);//将已经显示出来的原图象重新设置成白色，达到刷新屏幕的效果

	LPBITMAPINFO pBitmapInfo=(BITMAPINFO*)m_lpBmpInfoHead;
	//为适应StretchDIBits函数的需要，将图像信息头指针强制转换为LPBITMAPINFO类型


	//马赛克的大小设置为宽高都是12个像素
	int WithFalg=0; //图象宽是12的整数倍的标志
	int HeightFlag=0;//图象高是12的整数倍的标志
	if((bitmapWidth%12)!=0)WithFalg=1;
	if((bitmapHeight%12)!=0)HeightFlag=1;
	long ArrayLength=(bitmapWidth/12+WithFalg)*(bitmapHeight/12+HeightFlag);
	//将图象宽高都延拓至12的整数倍,然后将图象分成12X12的小块，按行顺序排列成一个数组

	struct Square
	{
		CPoint pt;//记录每个12X12的小块的左上角坐标
		bool HitFlag;//当随机扫描所有小块的时候，记录是否曾经被扫描过
	};//自己定义一个结构，由一个Cpoint类型和一个击中标志构成

	Square* SquareArray=new Square[ArrayLength];
	int x=0;
	int y=0;

	for(int i=0; i<ArrayLength; i++)
	{
		//初始化每个小块的坐标点
		SquareArray[i].pt.x=x;
		SquareArray[i].pt.y=y;
		x=x+12;
		if(x>bitmapWidth)
		{x=0;y=y+12;}

		//初始所有小块都未被击中过
		SquareArray[i].HitFlag=FALSE;
	}
	
	long RandNum;//随即变量
	srand( (unsigned)time( NULL ) );//生成随机种子
	int i;
	for(i=0;i<=ArrayLength;i++)
	{	
		do
		{
			RandNum=(long)( ( (double)ArrayLength )*rand()/RAND_MAX );//随机变量在0到ArrayLength-1之间取值
			x=SquareArray[RandNum].pt.x;
			y=SquareArray[RandNum].pt.y;		
		}while(SquareArray[RandNum].HitFlag==TRUE);//检查小块以前是否被击中过，如果是，重新计算一个随机数
		SquareArray[RandNum].HitFlag=TRUE;//设置击中标志

		::StretchDIBits(pDC->GetSafeHdc(),
			x, y, 12,12,
			x,bitmapHeight-y-12, 12,12,
			m_pImgData, pBitmapInfo,DIB_RGB_COLORS, SRCCOPY);
		Sleep(1);//设置延时时间
	}
	delete [] SquareArray;
}
