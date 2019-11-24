// pvDlg.h : header file
//

#if !defined(AFX_PVDLG_H__53302F36_4562_4D26_B9F2_69E71D2A2817__INCLUDED_)
#define AFX_PVDLG_H__53302F36_4562_4D26_B9F2_69E71D2A2817__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPvDlg dialog

class CPvDlg : public CDialog
{
// Construction
public:
	CPvDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPvDlg)
	enum { IDD = IDD_PV_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPvDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPvDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFather();
	afx_msg void OnMom();
	afx_msg void OnDaughter();
	afx_msg void OnSon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PVDLG_H__53302F36_4562_4D26_B9F2_69E71D2A2817__INCLUDED_)
