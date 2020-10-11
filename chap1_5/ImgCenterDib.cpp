#include "stdafx.h"
#include "ImageCenterDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************
* 函数名称：
* ImgCenterDib()
*
*说明：无参数的构造函数，对成员变量进行初始化
***********************************************************************/
ImgCenterDib::ImgCenterDib()
{

	m_lpDib=NULL;//初始化m_lpDib为空。

	m_lpColorTable=NULL;//颜色表指针为空

	m_pImgData=NULL;  // 图像数据指针为空

	m_lpBmpInfoHead=NULL; //  图像信息头指针为空

	m_hPalette = NULL;//调色板为空
}

/***********************************************************************
* 函数名称：
* ImgCenterDib()
*
*函数参数：
*  CSize size -图像大小（宽、高）
*  int nBitCount  -每像素所占位数
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据指针
*
*返回值：
*   无
*
*说明：本函数为带参数的构造函数，给定位图的大小、每像素位数、颜色表
*      及位图数据等信息，创建ImgCenterDib类的对象
***********************************************************************/
ImgCenterDib::ImgCenterDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
						   unsigned char *pImgData)
{
	//如果没有位图数据传入，我们认为是空的DIB，此时不分配DIB内存
	if(pImgData==NULL){
		m_lpDib=NULL;
		m_lpColorTable=NULL;
		m_pImgData=NULL; 
		m_lpBmpInfoHead=NULL; 
		m_hPalette = NULL;
	}
	else{//如果有位图数据传入
		
		//图像的宽、高、每像素位数等成员变量赋值
		m_imgWidth=size.cx;
		m_imgHeight=size.cy;
		m_nBitCount=nBitCount;

		//根据每像素位数，计算颜色表长度
		m_nColorTableLength=ComputeColorTabalLength(nBitCount);
		
		//每行像素所占字节数，必须扩展成4的倍数
		int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;

		//位图数据缓冲区的大小（图像大小）
		int imgBufSize=m_imgHeight*lineByte;

		//为m_lpDib一次性分配内存，生成DIB结构
		m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + 
			sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];
		
		//填写BITMAPINFOHEADER结构
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER) m_lpDib;
		m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
		m_lpBmpInfoHead->biWidth = m_imgWidth;
		m_lpBmpInfoHead->biHeight = m_imgHeight;
		m_lpBmpInfoHead->biPlanes = 1;
		m_lpBmpInfoHead->biBitCount = m_nBitCount;
		m_lpBmpInfoHead->biCompression = BI_RGB;
		m_lpBmpInfoHead->biSizeImage = 0;
		m_lpBmpInfoHead->biXPelsPerMeter = 0;
		m_lpBmpInfoHead->biYPelsPerMeter = 0;
		m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
		m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;
		
		//调色板句柄初始化为空，有颜色表时，MakePalette()函数要创建新的逻辑调色板
		m_hPalette = NULL;
		if(m_nColorTableLength!=0){ //若有颜色表，则将颜色表拷贝进DIB的颜色表位置
			//用m_lpColorTable指向DIB颜色表的起始位置
			m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));

			//颜色表拷贝
			memcpy(m_lpColorTable,lpColorTable,
				sizeof(RGBQUAD) * m_nColorTableLength);

			//创建逻辑调色板
			MakePalette();
		}

		//用m_pImgData指向DIB位图数据起始位置
		m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+
			        sizeof(RGBQUAD) * m_nColorTableLength;

		//拷贝图像数据进DIB位图数据区
		memcpy(m_pImgData,pImgData,imgBufSize);
	}
}



/***********************************************************************
* 函数名称：
*   ~ImgCenterDib()

*
*说明：析构函数，释放资源
***********************************************************************/
ImgCenterDib::~ImgCenterDib()
{
	//释放m_lpDib所指向的内存缓冲区
	if(m_lpDib != NULL) 
		delete [] m_lpDib; 
	
	//如果有调色板，释放调色板
	if(m_hPalette != NULL)
		::DeleteObject(m_hPalette);
		
}



/***********************************************************************
* 函数名称：
* Draw()
*
*函数参数：
*  CDC* pDC  -设备环境指针
*  CPoint origin  -显示矩形区域的左上角
*  CSize size     -显示矩形区域的尺寸
*
*返回值：
*   0为失败,1为成功
*
*说明：给定设备环境指针，以及需要显示的矩形区域在设备环境中的位置
*      将m_lpDib所指向的DIB显示出来
***********************************************************************/
BOOL ImgCenterDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	//旧的调色板句柄
	HPALETTE hOldPal=NULL;

	//如果DIB为空，则返回0
	if(m_lpDib == NULL) return FALSE;

	//如果DIB有调色板，则选进设备环境中
	if(m_hPalette != NULL) {
		hOldPal=::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	//设置位图伸缩模式
	pDC->SetStretchBltMode(COLORONCOLOR);

	//将DIB在pDC所指向的设备上进行显示
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy,
		0, 0, m_lpBmpInfoHead->biWidth, m_lpBmpInfoHead->biHeight,m_pImgData,
		 (LPBITMAPINFO) m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);

	//恢复旧的调色板
	if(hOldPal!=NULL)
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);

	//函数返回
	return TRUE;
}



/***********************************************************************
* 函数名称：
* Read()
*
*函数参数：
*  LPCTSTR lpszPathName -文件名字及路径
*
*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像文件名及其路径，分配内存，读取图像数据进内存生成DIB，
*      并存放在m_lpDib所指向的缓冲区
***********************************************************************/
BOOL ImgCenterDib::Read(LPCTSTR lpszPathName)
{
	//读模式打开图像文件
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;
	
	BITMAPFILEHEADER bmfh;
	try {
		//清理空间
		Empty();

		//读取BITMAPFILEHEADER结构到变量bmfh中
		int nCount=file.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		//异常判断
		if(nCount != sizeof(BITMAPFILEHEADER)) {
			//throw new CException;
			throw " nCount != sizeof(BITMAPFILEHEADER)";
		}
		if(bmfh.bfType != 0x4d42) {
			//throw new CException;
			throw "bmfh.bfType != 0x4d42 ";
		}

		//为m_lpDib分配空间，读取DIB进内存
		if(m_lpDib!=NULL)
			delete []m_lpDib;
		m_lpDib=new BYTE[file.GetLength() -sizeof(BITMAPFILEHEADER)];
		file.Read(m_lpDib, file.GetLength() -sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHead位置为m_lpDib起始位置
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//为成员变量赋值
		m_imgWidth=m_lpBmpInfoHead->biWidth;
		m_imgHeight=m_lpBmpInfoHead->biHeight;
		m_nBitCount=m_lpBmpInfoHead->biBitCount; 

		//计算颜色表长度
		m_nColorTableLength=
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//生成逻辑调色板
		m_hPalette = NULL;
		if(m_nColorTableLength!=0){
			m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
	    	MakePalette();
		}

		//m_pImgData指向DIB的位图数据起始位置
		m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;
	}
	catch(CException* pe) {
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}

	//函数返回
	return TRUE;
}

/***********************************************************************
* 函数名称：
* Write()
*
*函数参数：
*  LPCTSTR lpszPathName -指定图像文件名字及路径
*
*返回值：
*   0为失败,1为成功
*
*说明：给定一个图像文件名及其路径，将m_lpDib指向的DIB数据存盘
***********************************************************************/
BOOL ImgCenterDib::Write(LPCTSTR lpszPathName)
{
	//写模式打开文件
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate | CFile::modeReadWrite 
		| CFile::shareExclusive))
		return FALSE;

	//填写文件头结构
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;	
	try {
		//文件头结构写进文件
		file.Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		
		//文件信息头结构写进文件
		file.Write(m_lpBmpInfoHead,  sizeof(BITMAPINFOHEADER));

		//如果有颜色表的话，颜色表写进文件
		if(m_nColorTableLength!=0)
	    	file.Write(m_lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

		//位图数据写进文件
		int imgBufSize=(m_imgWidth*m_nBitCount/8+3)/4*4*m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch(CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}

	//函数返回
	return TRUE;
}


/***********************************************************************
* 函数名称：
* ReplaceDib()
*
*函数参数：
*  CSize size   -要替换的新图像尺寸
*  int nBitCount  -每像素的位数
*  LPRGBQUAD lpColorTable  -颜色表指针
*  unsigned char *pImgData  -位图数据的指针

*返回值：
*   无
*
*说明：给定新图像的尺寸、每像素位数、颜色表、及位图数据等信息，将m_lpDib
*      所指向的现有的DIB替换成新的DIB
***********************************************************************/
void ImgCenterDib::ReplaceDib(CSize size, int nBitCount,  
						 LPRGBQUAD lpColorTable,unsigned char *pImgData)
{ 
	//释放原DIB所占空间
	Empty();

	//成员变量赋值
	m_imgWidth=size.cx;
	m_imgHeight=size.cy;
	m_nBitCount=nBitCount;

	//计算颜色表的长度
	m_nColorTableLength=ComputeColorTabalLength(nBitCount);

	//每行像素所占字节数，扩展成4的倍数
	int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;

	//位图数据的大小
	int imgBufSize=m_imgHeight*lineByte;

	//为m_lpDib重新分配空间，以存放新的DIB
	m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + 
		             sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];

	//填写位图信息头BITMAPINFOHEADER结构
	m_lpBmpInfoHead = (LPBITMAPINFOHEADER) m_lpDib;
	m_lpBmpInfoHead->biSize = sizeof(BITMAPINFOHEADER);
	m_lpBmpInfoHead->biWidth = m_imgWidth;
	m_lpBmpInfoHead->biHeight = m_imgHeight;
	m_lpBmpInfoHead->biPlanes = 1;
	m_lpBmpInfoHead->biBitCount = m_nBitCount;
	m_lpBmpInfoHead->biCompression = BI_RGB;
	m_lpBmpInfoHead->biSizeImage = 0;
	m_lpBmpInfoHead->biXPelsPerMeter = 0;
	m_lpBmpInfoHead->biYPelsPerMeter = 0;
	m_lpBmpInfoHead->biClrUsed = m_nColorTableLength;
	m_lpBmpInfoHead->biClrImportant = m_nColorTableLength;

	//调色板置空
	m_hPalette = NULL;

	//如果有颜色表，则将颜色表拷贝至新生成的DIB，并生成调色板
	if(m_nColorTableLength!=0){
		m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
		memcpy(m_lpColorTable,lpColorTable,sizeof(RGBQUAD) * m_nColorTableLength);
		MakePalette();
	}

	//m_pImgData指向DIB的位图数据起始位置
	m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQUAD) * m_nColorTableLength;

	//将新位图数据拷贝至新的DIB中
	memcpy(m_pImgData,pImgData,imgBufSize);
}


/***********************************************************************
* 函数名称：
* ComputeColorTabalLength()
*
*函数参数：
*  int nBitCount -DIB每像素位数
*
*返回值：
*   颜色表的长度
*
*说明：给定每像素的位数，计算出DIB颜色表的长度，颜色表长度
*      为2的nBitCount次幂，但是24位位图颜色表长度为0
***********************************************************************/
int ImgCenterDib::ComputeColorTabalLength(int nBitCount)
{
	int colorTableLength;
	switch(nBitCount) {
	case 1:
		colorTableLength = 2;
		break;
	case 4:
		colorTableLength = 16;
		break;
	case 8:
		colorTableLength = 256;
		break;
	case 16:
	case 24:
	case 32:
		colorTableLength = 0;
		break;
	default:
		ASSERT(FALSE);
	}
	
	ASSERT((colorTableLength >= 0) && (colorTableLength <= 256)); 
	return colorTableLength;
}

/***********************************************************************
* 函数名称：
* MakePalette()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：根据DIB的颜色表，生成一个逻辑调色板（m_hPalette），
*      该调色板在显示位图时将被选进设备环境中
***********************************************************************/
void ImgCenterDib::MakePalette()
{
	// makes a logical palette (m_hPalette) from the DIB's color table
	// this palette will be selected and realized prior to drawing the DIB

	//如果颜色表长度为0，则不生成逻辑调色板
	if(m_nColorTableLength == 0) 
		return;

	//删除旧的调色板对象
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);

	//申请缓冲区，生成逻辑调色板
	LPLOGPALETTE pLogPal = (LPLOGPALETTE) new char[2 * sizeof(WORD) +
		m_nColorTableLength * sizeof(PALETTEENTRY)];
	pLogPal->palVersion = 0x300;
	pLogPal->palNumEntries = m_nColorTableLength;
	LPRGBQUAD m_lpDibQuad = (LPRGBQUAD) m_lpColorTable;
	for(int i = 0; i < m_nColorTableLength; i++) {
		pLogPal->palPalEntry[i].peRed = m_lpDibQuad->rgbRed;
		pLogPal->palPalEntry[i].peGreen = m_lpDibQuad->rgbGreen;
		pLogPal->palPalEntry[i].peBlue = m_lpDibQuad->rgbBlue;
		pLogPal->palPalEntry[i].peFlags = 0;
		m_lpDibQuad++;
	}

	//创建逻辑调色板
	m_hPalette = ::CreatePalette(pLogPal);

	//释放缓冲区
	delete pLogPal;

}	



/***********************************************************************
* 函数名称：
* Empty()
*
*函数参数：
*  无
*
*返回值：
*   无
*
*说明：清理空间
***********************************************************************/
void ImgCenterDib::Empty()
{
	//释放m_lpDib所指向的缓冲区
	if(m_lpDib != NULL) {
		delete [] m_lpDib;
		m_lpDib=NULL;
		m_lpColorTable=NULL;
		m_pImgData=NULL; 
		m_lpBmpInfoHead=NULL; 
	}
	//释放逻辑调色板缓冲区
	if(m_hPalette != NULL){
		::DeleteObject(m_hPalette);
		m_hPalette = NULL;
	}
}



/***********************************************************************
* 函数名称：
* GetDimensions()
*
*函数参数：
*  无
*
*返回值：
*   图像的尺寸，用CSize类型表达
*
*说明：返回图像的宽和高
***********************************************************************/
CSize ImgCenterDib::GetDimensions()
{	
	if(m_lpDib == NULL) return CSize(0, 0);
	return CSize(m_imgWidth, m_imgHeight);
}