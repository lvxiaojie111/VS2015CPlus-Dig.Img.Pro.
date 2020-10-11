// SpecialEffectShow.h: interface for the SpecialEffectShow class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECIALEFFECTSHOW_H__3F17BE6F_939E_4079_BEF0_C7B378BF4731__INCLUDED_)
#define AFX_SPECIALEFFECTSHOW_H__3F17BE6F_939E_4079_BEF0_C7B378BF4731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ImageCenterDib.h"

class SpecialEffectShow : public ImgCenterDib  
{
public:
	//�������Ĺ��캯��
	SpecialEffectShow(	CSize size, int nBitCount, 
						LPRGBQUAD lpColorTable, unsigned char *pImgData);	
	void Scan(CDC*pDC);//ɨ����Ч��ʾ
	void Slide(CDC*pDC);//������Ч��ʾ
	void FadeIn(CDC * pDC);//������Ч��ʾ
	void Mosaik(CDC * pDC);//��������Ч��ʾ
		
	virtual ~SpecialEffectShow();
protected:
	SpecialEffectShow();//��ֹ���ⲿ�����޲����Ĺ��캯��
};

#endif // !defined(AFX_SPECIALEFFECTSHOW_H__3F17BE6F_939E_4079_BEF0_C7B378BF4731__INCLUDED_)
