// pv.h : main header file for the PV application
//

#if !defined(AFX_PV_H__76153D10_A934_4EE0_871A_D5971484EC1A__INCLUDED_)
#define AFX_PV_H__76153D10_A934_4EE0_871A_D5971484EC1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPvApp:
// See pv.cpp for the implementation of this class
//

class CPvApp : public CWinApp
{
public:
	CPvApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPvApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPvApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PV_H__76153D10_A934_4EE0_871A_D5971484EC1A__INCLUDED_)
