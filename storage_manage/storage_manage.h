// storage_manage.h : main header file for the STORAGE_MANAGE application
//

#if !defined(AFX_STORAGE_MANAGE_H__1367DB3B_44FB_41D4_A703_D51175FF745F__INCLUDED_)
#define AFX_STORAGE_MANAGE_H__1367DB3B_44FB_41D4_A703_D51175FF745F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStorage_manageApp:
// See storage_manage.cpp for the implementation of this class
//

class CStorage_manageApp : public CWinApp
{
public:
	CStorage_manageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorage_manageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStorage_manageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORAGE_MANAGE_H__1367DB3B_44FB_41D4_A703_D51175FF745F__INCLUDED_)
