// BuyticketDlg.h : header file
//

#if !defined(AFX_BUYTICKETDLG_H__5E765EDF_56A2_478F_B850_F48D5369D8B3__INCLUDED_)
#define AFX_BUYTICKETDLG_H__5E765EDF_56A2_478F_B850_F48D5369D8B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBuyticketDlg dialog

class CBuyticketDlg : public CDialog
{
// Construction
public:
	CBuyticketDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBuyticketDlg)
	enum { IDD = IDD_BUYTICKET_DIALOG };
	CEdit	m_buynum;
	CStatic	m_title;
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuyticketDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CBuyticketDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickList3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUYTICKETDLG_H__5E765EDF_56A2_478F_B850_F48D5369D8B3__INCLUDED_)
