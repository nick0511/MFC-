// storage_manageDlg.h : header file
//

#if !defined(AFX_STORAGE_MANAGEDLG_H__63B54C4A_9DA9_4A14_A112_3BBC677BFD47__INCLUDED_)
#define AFX_STORAGE_MANAGEDLG_H__63B54C4A_9DA9_4A14_A112_3BBC677BFD47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CStorage_manageDlg dialog

class CStorage_manageDlg : public CDialog
{
// Construction
public:
	CStorage_manageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStorage_manageDlg)
	enum { IDD = IDD_STORAGE_MANAGE_DIALOG };
	CEdit	m_edit;
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStorage_manageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStorage_manageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtn();
	afx_msg void OnCancelBTN();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STORAGE_MANAGEDLG_H__63B54C4A_9DA9_4A14_A112_3BBC677BFD47__INCLUDED_)
