#include "stdafx.h"
#include "ImageCenterDib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/***********************************************************************
* �������ƣ�
* ImgCenterDib()
*
*˵�����޲����Ĺ��캯�����Գ�Ա�������г�ʼ��
***********************************************************************/
ImgCenterDib::ImgCenterDib()
{

	m_lpDib=NULL;//��ʼ��m_lpDibΪ�ա�

	m_lpColorTable=NULL;//��ɫ��ָ��Ϊ��

	m_pImgData=NULL;  // ͼ������ָ��Ϊ��

	m_lpBmpInfoHead=NULL; //  ͼ����Ϣͷָ��Ϊ��

	m_hPalette = NULL;//��ɫ��Ϊ��
}

/***********************************************************************
* �������ƣ�
* ImgCenterDib()
*
*����������
*  CSize size -ͼ���С�����ߣ�
*  int nBitCount  -ÿ������ռλ��
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ����ָ��
*
*����ֵ��
*   ��
*
*˵����������Ϊ�������Ĺ��캯��������λͼ�Ĵ�С��ÿ����λ������ɫ��
*      ��λͼ���ݵ���Ϣ������ImgCenterDib��Ķ���
***********************************************************************/
ImgCenterDib::ImgCenterDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
						   unsigned char *pImgData)
{
	//���û��λͼ���ݴ��룬������Ϊ�ǿյ�DIB����ʱ������DIB�ڴ�
	if(pImgData==NULL){
		m_lpDib=NULL;
		m_lpColorTable=NULL;
		m_pImgData=NULL; 
		m_lpBmpInfoHead=NULL; 
		m_hPalette = NULL;
	}
	else{//�����λͼ���ݴ���
		
		//ͼ��Ŀ��ߡ�ÿ����λ���ȳ�Ա������ֵ
		m_imgWidth=size.cx;
		m_imgHeight=size.cy;
		m_nBitCount=nBitCount;

		//����ÿ����λ����������ɫ����
		m_nColorTableLength=ComputeColorTabalLength(nBitCount);
		
		//ÿ��������ռ�ֽ�����������չ��4�ı���
		int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;

		//λͼ���ݻ������Ĵ�С��ͼ���С��
		int imgBufSize=m_imgHeight*lineByte;

		//Ϊm_lpDibһ���Է����ڴ棬����DIB�ṹ
		m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + 
			sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];
		
		//��дBITMAPINFOHEADER�ṹ
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
		
		//��ɫ������ʼ��Ϊ�գ�����ɫ��ʱ��MakePalette()����Ҫ�����µ��߼���ɫ��
		m_hPalette = NULL;
		if(m_nColorTableLength!=0){ //������ɫ������ɫ������DIB����ɫ��λ��
			//��m_lpColorTableָ��DIB��ɫ�����ʼλ��
			m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));

			//��ɫ����
			memcpy(m_lpColorTable,lpColorTable,
				sizeof(RGBQUAD) * m_nColorTableLength);

			//�����߼���ɫ��
			MakePalette();
		}

		//��m_pImgDataָ��DIBλͼ������ʼλ��
		m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+
			        sizeof(RGBQUAD) * m_nColorTableLength;

		//����ͼ�����ݽ�DIBλͼ������
		memcpy(m_pImgData,pImgData,imgBufSize);
	}
}



/***********************************************************************
* �������ƣ�
*   ~ImgCenterDib()

*
*˵���������������ͷ���Դ
***********************************************************************/
ImgCenterDib::~ImgCenterDib()
{
	//�ͷ�m_lpDib��ָ����ڴ滺����
	if(m_lpDib != NULL) 
		delete [] m_lpDib; 
	
	//����е�ɫ�壬�ͷŵ�ɫ��
	if(m_hPalette != NULL)
		::DeleteObject(m_hPalette);
		
}



/***********************************************************************
* �������ƣ�
* Draw()
*
*����������
*  CDC* pDC  -�豸����ָ��
*  CPoint origin  -��ʾ������������Ͻ�
*  CSize size     -��ʾ��������ĳߴ�
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵���������豸����ָ�룬�Լ���Ҫ��ʾ�ľ����������豸�����е�λ��
*      ��m_lpDib��ָ���DIB��ʾ����
***********************************************************************/
BOOL ImgCenterDib::Draw(CDC* pDC, CPoint origin, CSize size)
{
	//�ɵĵ�ɫ����
	HPALETTE hOldPal=NULL;

	//���DIBΪ�գ��򷵻�0
	if(m_lpDib == NULL) return FALSE;

	//���DIB�е�ɫ�壬��ѡ���豸������
	if(m_hPalette != NULL) {
		hOldPal=::SelectPalette(pDC->GetSafeHdc(), m_hPalette, TRUE);
	}

	//����λͼ����ģʽ
	pDC->SetStretchBltMode(COLORONCOLOR);

	//��DIB��pDC��ָ����豸�Ͻ�����ʾ
	::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y, size.cx, size.cy,
		0, 0, m_lpBmpInfoHead->biWidth, m_lpBmpInfoHead->biHeight,m_pImgData,
		 (LPBITMAPINFO) m_lpBmpInfoHead, DIB_RGB_COLORS, SRCCOPY);

	//�ָ��ɵĵ�ɫ��
	if(hOldPal!=NULL)
		::SelectPalette(pDC->GetSafeHdc(), hOldPal, TRUE);

	//��������
	return TRUE;
}



/***********************************************************************
* �������ƣ�
* Read()
*
*����������
*  LPCTSTR lpszPathName -�ļ����ּ�·��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵��������һ��ͼ���ļ�������·���������ڴ棬��ȡͼ�����ݽ��ڴ�����DIB��
*      �������m_lpDib��ָ��Ļ�����
***********************************************************************/
BOOL ImgCenterDib::Read(LPCTSTR lpszPathName)
{
	//��ģʽ��ͼ���ļ�
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;
	
	BITMAPFILEHEADER bmfh;
	try {
		//����ռ�
		Empty();

		//��ȡBITMAPFILEHEADER�ṹ������bmfh��
		int nCount=file.Read((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));

		//�쳣�ж�
		if(nCount != sizeof(BITMAPFILEHEADER)) {
			//throw new CException;
			throw " nCount != sizeof(BITMAPFILEHEADER)";
		}
		if(bmfh.bfType != 0x4d42) {
			//throw new CException;
			throw "bmfh.bfType != 0x4d42 ";
		}

		//Ϊm_lpDib����ռ䣬��ȡDIB���ڴ�
		if(m_lpDib!=NULL)
			delete []m_lpDib;
		m_lpDib=new BYTE[file.GetLength() -sizeof(BITMAPFILEHEADER)];
		file.Read(m_lpDib, file.GetLength() -sizeof(BITMAPFILEHEADER));

		//m_lpBmpInfoHeadλ��Ϊm_lpDib��ʼλ��
		m_lpBmpInfoHead = (LPBITMAPINFOHEADER)m_lpDib;

		//Ϊ��Ա������ֵ
		m_imgWidth=m_lpBmpInfoHead->biWidth;
		m_imgHeight=m_lpBmpInfoHead->biHeight;
		m_nBitCount=m_lpBmpInfoHead->biBitCount; 

		//������ɫ����
		m_nColorTableLength=
			ComputeColorTabalLength(m_lpBmpInfoHead->biBitCount);

		//�����߼���ɫ��
		m_hPalette = NULL;
		if(m_nColorTableLength!=0){
			m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
	    	MakePalette();
		}

		//m_pImgDataָ��DIB��λͼ������ʼλ��
		m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;
	}
	catch(CException* pe) {
		AfxMessageBox("Read error");
		pe->Delete();
		return FALSE;
	}

	//��������
	return TRUE;
}

/***********************************************************************
* �������ƣ�
* Write()
*
*����������
*  LPCTSTR lpszPathName -ָ��ͼ���ļ����ּ�·��
*
*����ֵ��
*   0Ϊʧ��,1Ϊ�ɹ�
*
*˵��������һ��ͼ���ļ�������·������m_lpDibָ���DIB���ݴ���
***********************************************************************/
BOOL ImgCenterDib::Write(LPCTSTR lpszPathName)
{
	//дģʽ���ļ�
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate | CFile::modeReadWrite 
		| CFile::shareExclusive))
		return FALSE;

	//��д�ļ�ͷ�ṹ
	BITMAPFILEHEADER bmfh;
	bmfh.bfType = 0x4d42;  // 'BM'
	bmfh.bfSize = 0;
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
			sizeof(RGBQUAD) * m_nColorTableLength;	
	try {
		//�ļ�ͷ�ṹд���ļ�
		file.Write((LPVOID) &bmfh, sizeof(BITMAPFILEHEADER));
		
		//�ļ���Ϣͷ�ṹд���ļ�
		file.Write(m_lpBmpInfoHead,  sizeof(BITMAPINFOHEADER));

		//�������ɫ��Ļ�����ɫ��д���ļ�
		if(m_nColorTableLength!=0)
	    	file.Write(m_lpColorTable, sizeof(RGBQUAD) * m_nColorTableLength);

		//λͼ����д���ļ�
		int imgBufSize=(m_imgWidth*m_nBitCount/8+3)/4*4*m_imgHeight;
		file.Write(m_pImgData, imgBufSize);
	}
	catch(CException* pe) {
		pe->Delete();
		AfxMessageBox("write error");
		return FALSE;
	}

	//��������
	return TRUE;
}


/***********************************************************************
* �������ƣ�
* ReplaceDib()
*
*����������
*  CSize size   -Ҫ�滻����ͼ��ߴ�
*  int nBitCount  -ÿ���ص�λ��
*  LPRGBQUAD lpColorTable  -��ɫ��ָ��
*  unsigned char *pImgData  -λͼ���ݵ�ָ��

*����ֵ��
*   ��
*
*˵����������ͼ��ĳߴ硢ÿ����λ������ɫ����λͼ���ݵ���Ϣ����m_lpDib
*      ��ָ������е�DIB�滻���µ�DIB
***********************************************************************/
void ImgCenterDib::ReplaceDib(CSize size, int nBitCount,  
						 LPRGBQUAD lpColorTable,unsigned char *pImgData)
{ 
	//�ͷ�ԭDIB��ռ�ռ�
	Empty();

	//��Ա������ֵ
	m_imgWidth=size.cx;
	m_imgHeight=size.cy;
	m_nBitCount=nBitCount;

	//������ɫ��ĳ���
	m_nColorTableLength=ComputeColorTabalLength(nBitCount);

	//ÿ��������ռ�ֽ�������չ��4�ı���
	int lineByte=(m_imgWidth*nBitCount/8+3)/4*4;

	//λͼ���ݵĴ�С
	int imgBufSize=m_imgHeight*lineByte;

	//Ϊm_lpDib���·���ռ䣬�Դ���µ�DIB
	m_lpDib=new BYTE [sizeof(BITMAPINFOHEADER) + 
		             sizeof(RGBQUAD) * m_nColorTableLength+imgBufSize];

	//��дλͼ��ϢͷBITMAPINFOHEADER�ṹ
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

	//��ɫ���ÿ�
	m_hPalette = NULL;

	//�������ɫ������ɫ�����������ɵ�DIB�������ɵ�ɫ��
	if(m_nColorTableLength!=0){
		m_lpColorTable=(LPRGBQUAD)(m_lpDib+sizeof(BITMAPINFOHEADER));
		memcpy(m_lpColorTable,lpColorTable,sizeof(RGBQUAD) * m_nColorTableLength);
		MakePalette();
	}

	//m_pImgDataָ��DIB��λͼ������ʼλ��
	m_pImgData = (LPBYTE)m_lpDib+sizeof(BITMAPINFOHEADER)+
		sizeof(RGBQUAD) * m_nColorTableLength;

	//����λͼ���ݿ������µ�DIB��
	memcpy(m_pImgData,pImgData,imgBufSize);
}


/***********************************************************************
* �������ƣ�
* ComputeColorTabalLength()
*
*����������
*  int nBitCount -DIBÿ����λ��
*
*����ֵ��
*   ��ɫ��ĳ���
*
*˵��������ÿ���ص�λ���������DIB��ɫ��ĳ��ȣ���ɫ����
*      Ϊ2��nBitCount���ݣ�����24λλͼ��ɫ����Ϊ0
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
* �������ƣ�
* MakePalette()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������DIB����ɫ������һ���߼���ɫ�壨m_hPalette����
*      �õ�ɫ������ʾλͼʱ����ѡ���豸������
***********************************************************************/
void ImgCenterDib::MakePalette()
{
	// makes a logical palette (m_hPalette) from the DIB's color table
	// this palette will be selected and realized prior to drawing the DIB

	//�����ɫ����Ϊ0���������߼���ɫ��
	if(m_nColorTableLength == 0) 
		return;

	//ɾ���ɵĵ�ɫ�����
	if(m_hPalette != NULL) ::DeleteObject(m_hPalette);

	//���뻺�����������߼���ɫ��
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

	//�����߼���ɫ��
	m_hPalette = ::CreatePalette(pLogPal);

	//�ͷŻ�����
	delete pLogPal;

}	



/***********************************************************************
* �������ƣ�
* Empty()
*
*����������
*  ��
*
*����ֵ��
*   ��
*
*˵��������ռ�
***********************************************************************/
void ImgCenterDib::Empty()
{
	//�ͷ�m_lpDib��ָ��Ļ�����
	if(m_lpDib != NULL) {
		delete [] m_lpDib;
		m_lpDib=NULL;
		m_lpColorTable=NULL;
		m_pImgData=NULL; 
		m_lpBmpInfoHead=NULL; 
	}
	//�ͷ��߼���ɫ�建����
	if(m_hPalette != NULL){
		::DeleteObject(m_hPalette);
		m_hPalette = NULL;
	}
}



/***********************************************************************
* �������ƣ�
* GetDimensions()
*
*����������
*  ��
*
*����ֵ��
*   ͼ��ĳߴ磬��CSize���ͱ��
*
*˵��������ͼ��Ŀ�͸�
***********************************************************************/
CSize ImgCenterDib::GetDimensions()
{	
	if(m_lpDib == NULL) return CSize(0, 0);
	return CSize(m_imgWidth, m_imgHeight);
}