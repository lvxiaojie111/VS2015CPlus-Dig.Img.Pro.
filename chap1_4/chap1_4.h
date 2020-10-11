// chap1_4.h : main header file for the CHAP1_4 application
//

#if !defined(AFX_CHAP1_4_H__5ECD2294_7E8D_4559_A2AC_16583E230672__INCLUDED_)
#define AFX_CHAP1_4_H__5ECD2294_7E8D_4559_A2AC_16583E230672__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChap1_4App:
// See chap1_4.cpp for the implementation of this class
//

class CChap1_4App : public CWinApp
{
public:
	CChap1_4App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_4App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChap1_4App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_4_H__5ECD2294_7E8D_4559_A2AC_16583E230672__INCLUDED_)
