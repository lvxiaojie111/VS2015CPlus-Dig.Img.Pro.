#ifndef _INSIDE_VISUAL_CPP_IMGCENTERDIB
#define _INSIDE_VISUAL_CPP_IMGCENTERDIB

//ImgCenterDib��,image processing center,����ͼ�����ı�д��DIB��

//ImgCenterDib��
class ImgCenterDib
{
public:	
	//ͼ������ָ��
	unsigned char * m_pImgData; 

	//ͼ����ɫ��ָ��
	LPRGBQUAD m_lpColorTable; 

	//ÿ����ռ��λ��
	int m_nBitCount;


private:
	//ָ��DIB��ָ�루����BITMAPFILEHEADER��BITMAPINFOHEADER����ɫ��
	LPBYTE m_lpDib;
	
	//�߼���ɫ����
	HPALETTE m_hPalette;

	//��ɫ���ȣ����ٸ����
	int m_nColorTableLength;

protected:
	//ͼ��Ŀ�����Ϊ��λ
	int m_imgWidth;

	//ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeight;

	//ͼ����Ϣͷָ��
	LPBITMAPINFOHEADER m_lpBmpInfoHead; 

public:
	//���������Ĺ��캯��
	ImgCenterDib();

	//�������Ĺ��캯��
	ImgCenterDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		unsigned char *pImgData);

	//��������
	~ImgCenterDib();

	//��ȡDIB�ĳߴ磨��ߣ�
	CSize GetDimensions();

	//DIB������
	BOOL Read(LPCTSTR lpszPathName);

	//DIBд����
	BOOL Write(LPCTSTR lpszPathName);

	//��ʾDIB
	BOOL Draw(CDC* pDC, CPoint origin, CSize size);  

	//���µ������滻DIB
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		unsigned char *pImgData);

	//������ɫ��ĳ���
	int ComputeColorTabalLength(int nBitCount);
	
private:
	//�����߼���ɫ��
	void MakePalette();

	//����ռ�
	void Empty();	
};
#endif // _INSIDE_VISUAL_CPP_IMGCENTERDIB
