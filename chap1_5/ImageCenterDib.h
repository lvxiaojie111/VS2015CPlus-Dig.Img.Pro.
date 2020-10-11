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

	//ͼ����Ϣͷָ��
	LPBITMAPINFOHEADER m_lpBmpInfoHead;  
	
	//��ɫ����
	HPALETTE m_hPalette;

	//��ɫ����
	int m_nColorTableLength;

public:

	//���������Ĺ��캯��
	ImgCenterDib();

	//�������Ĺ��캯��
	ImgCenterDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable, 
		         unsigned char *pImgData);

	//��������
	~ImgCenterDib();

	//DIB������
	BOOL Read(LPCTSTR lpszPathName);


	//DIBд����
	BOOL Write(LPCTSTR lpszPathName);

	//DIB��ʾ����
	BOOL Draw(CDC* pDC, CPoint origin, CSize size); 

	//�߼���ɫ�����ɺ���
	void MakePalette();

	//��ȡDIB�ĳߴ磨��ߣ�
	CSize GetDimensions();

	//����ռ�
	void Empty();

	//���µ������滻��ǰDIB
	void ReplaceDib(CSize size, int nBitCount, LPRGBQUAD lpColorTable,
		             unsigned char *pImgData);

	//������ɫ��ĳ���
	int ComputeColorTabalLength(int nBitCount);

protected:

	//ͼ��Ŀ�����Ϊ��λ
	int m_imgWidth;

	//ͼ��ĸߣ�����Ϊ��λ
	int m_imgHeight;
	
};
#endif // _INSIDE_VISUAL_CPP_IMGCENTERDIB
