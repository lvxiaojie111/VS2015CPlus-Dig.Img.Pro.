#ifndef _INSIDE_VISUAL_CPP_IMGCENTERDIB
#define _INSIDE_VISUAL_CPP_IMGCENTERDIB

//ImgCenterDib类,image processing center,北航图像中心编写的DIB类

//ImgCenterDib类
class ImgCenterDib
{
public:	
	//图像数据指针
	unsigned char * m_pImgData; 

	//图像颜色表指针
	LPRGBQUAD m_lpColorTable; 

	//每像素占的位数
	int m_nBitCount;


private:
	//指向DIB的指针（包含BITMAPFILEHEADER，BITMAPINFOHEADER和颜色表）
	LPBYTE m_lpDib;

	//图像信息头指针
	LPBITMAPINFOHEADER m_lpBmpInfoHead;  
	
	//调色板句柄
	HPALETTE m_hPalette;

	//颜色表长度
	int m_nColorTableLength;

public:

	//不带参数的构造函数
	ImgCenterDib();

	//带参数的构造函数
	ImgCenterDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		         unsigned char *pImgData);

	//析构函数
	~ImgCenterDib();

	//DIB读函数
	BOOL Read(LPCTSTR lpszPathName);


	//DIB写函数
	BOOL Write(LPCTSTR lpszPathName);

	//DIB显示函数
	BOOL Draw(CDC* pDC, CPoint origin, CSize size); 

	//逻辑调色板生成函数
	void MakePalette();

	//获取DIB的尺寸（宽高）
	CSize GetDimensions();

	//清理空间
	void Empty();

	//用新的数据替换当前DIB
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		             unsigned char *pImgData);

	//计算颜色表的长度
	int ComputeColorTabalLength(int nBitCount);

protected:

	//图像的宽，像素为单位
	int m_imgWidth;

	//图像的高，像素为单位
	int m_imgHeight;
	
};
#endif // _INSIDE_VISUAL_CPP_IMGCENTERDIB
