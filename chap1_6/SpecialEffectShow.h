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
	//带参数的构造函数
	SpecialEffectShow(	CSize size, int nBitCount, 
						LPRGBQUAD lpColorTable, unsigned char *pImgData);	
	void Scan(CDC*pDC);//扫描特效显示
	void Slide(CDC*pDC);//滑动特效显示
	void FadeIn(CDC * pDC);//渐进特效显示
	void Mosaik(CDC * pDC);//马赛克特效显示
		
	virtual ~SpecialEffectShow();
protected:
	SpecialEffectShow();//防止从外部访问无参数的构造函数
};

#endif // !defined(AFX_SPECIALEFFECTSHOW_H__3F17BE6F_939E_4079_BEF0_C7B378BF4731__INCLUDED_)
