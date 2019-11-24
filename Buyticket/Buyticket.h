// Buyticket.h : main header file for the BUYTICKET application
//

#if !defined(AFX_BUYTICKET_H__9B82C0C0_9C18_4DEA_BF92_EC6C3D878CEF__INCLUDED_)
#define AFX_BUYTICKET_H__9B82C0C0_9C18_4DEA_BF92_EC6C3D878CEF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBuyticketApp:
// See Buyticket.cpp for the implementation of this class
//

class CBuyticketApp : public CWinApp
{
public:
	CBuyticketApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuyticketApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBuyticketApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYTICKET_H__9B82C0C0_9C18_4DEA_BF92_EC6C3D878CEF__INCLUDED_)
