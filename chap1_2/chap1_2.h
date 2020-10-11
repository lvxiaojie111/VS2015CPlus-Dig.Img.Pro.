// chap1_2.h : main header file for the CHAP1_2 application
//

#if !defined(AFX_CHAP1_2_H__AAB42E7A_8377_469C_AE7B_8FA1A084BE31__INCLUDED_)
#define AFX_CHAP1_2_H__AAB42E7A_8377_469C_AE7B_8FA1A084BE31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChap1_2App:
// See chap1_2.cpp for the implementation of this class
//

class CChap1_2App : public CWinApp
{
public:
	CChap1_2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChap1_2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChap1_2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHAP1_2_H__AAB42E7A_8377_469C_AE7B_8FA1A084BE31__INCLUDED_)
