// BuyticketDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Buyticket.h"
#include "BuyticketDlg.h"
#include "global.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuyticketDlg dialog

CBuyticketDlg::CBuyticketDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBuyticketDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuyticketDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBuyticketDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuyticketDlg)
	DDX_Control(pDX, IDC_EDIT1, m_buynum);
	DDX_Control(pDX, m_Static, m_title);
	DDX_Control(pDX, IDC_LIST3, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBuyticketDlg, CDialog)
	//{{AFX_MSG_MAP(CBuyticketDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST3, OnClickList3)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuyticketDlg message handlers

	CWinThread* mythread;
	CWinThread* mythread1;
	CWinThread* mythread2;
	//线程处理函数
static 	UINT Buytick (LPVOID lpParam)
	{
		CBuyticketDlg *dlg = (CBuyticketDlg*)lpParam;
		for (;;)
		{
			int j=  rand()%8;		//随机数 0-3
			int num= rand()%10;		//随机数 0-9
			if(tick_num[j]>=num)
			{
				while(lock[j]==1)		//随机等待法加锁
				{
					int randtime=rand()%100;
					Sleep(randtime);
				}
				lock[j]=1;
				tick_num[j] -=num;
				CString str;
				str.Format("%d",tick_num[j]);
				
				dlg->m_list.SetItemText(j,3,str);
				lock[j]=0;		
				Sleep(500);
				lock[j]=0;
				
			}		
			
		}
		return 0;
	}


BOOL CBuyticketDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	//启动三个子线程
	mythread = AfxBeginThread(
		Buytick,//即上面定义的函数
		(LPVOID)this
		);
	mythread1 = AfxBeginThread(
			Buytick,//即上面定义的函数
			(LPVOID)this
			);
	mythread2 = AfxBeginThread(
		Buytick,//即上面定义的函数
		(LPVOID)this
		);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically






	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
//初始化标题
	CFont m_editFont;
	m_editFont.CreatePointFont(400, _T("宋体"));
	m_title.SetFont(&m_editFont);
	
//初始化列表
    m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);    //报表样式
    m_list.InsertColumn(0, TEXT("班次"),LVCFMT_CENTER,80);//增加一列，居中，80px
    m_list.InsertColumn(1, TEXT("时间"),LVCFMT_CENTER,80);//增加一列，居中，80px
	m_list.InsertColumn(2, TEXT("票价"),LVCFMT_CENTER,80);//增加一列，居中，80px
	m_list.InsertColumn(4, TEXT("路线"),LVCFMT_CENTER,80);//增加一列，居中，80px
    m_list.InsertColumn(3, TEXT("余票"),LVCFMT_CENTER,80);//增加一列，居中，80px
	DWORD dwStyle = m_list.GetExtendedStyle();                    //添加列表框的网格线
    dwStyle |= LVS_EX_FULLROWSELECT;            
    dwStyle |= LVS_EX_GRIDLINES;                
    m_list.SetExtendedStyle(dwStyle);

	// TODO: Add extra initialization here

	for(int n=0;n<8;n++)
		m_list.InsertItem(n,"");

	CString str;
	str.Format("%d",tick_num[0]);
	m_list.SetItemText(0,0,"2001");
	m_list.SetItemText(0,1,"7:00");
	m_list.SetItemText(0,2,"￥40");
	m_list.SetItemText(0,3,str);
	m_list.SetItemText(0,4,"广州-->江门");

	str.Format("%d",tick_num[1]);
	m_list.SetItemText(1,0,"2002");
	m_list.SetItemText(1,1,"9:00");
	m_list.SetItemText(1,2,"￥40");
	m_list.SetItemText(1,3,str);
	m_list.SetItemText(1,4,"广州-->江门");

	str.Format("%d",tick_num[2]);
	m_list.SetItemText(2,0,"2003");
	m_list.SetItemText(2,1,"11:00");
	m_list.SetItemText(2,2,"￥40");
	m_list.SetItemText(2,3,str);
	m_list.SetItemText(2,4,"广州-->江门");

	str.Format("%d",tick_num[3]);
	m_list.SetItemText(3,0,"2004");
	m_list.SetItemText(3,1,"14:00");
	m_list.SetItemText(3,2,"￥40");
	m_list.SetItemText(3,3,str);
	m_list.SetItemText(3,4,"广州-->江门");

	str.Format("%d",tick_num[4]);
	m_list.SetItemText(4,0,"3001");
	m_list.SetItemText(4,1,"8:00");
	m_list.SetItemText(4,2,"￥40");
	m_list.SetItemText(4,3,str);
	m_list.SetItemText(4,4,"江门-->广州");

	str.Format("%d",tick_num[5]);
	m_list.SetItemText(5,0,"3002");
	m_list.SetItemText(5,1,"10:00");
	m_list.SetItemText(5,2,"￥40");
	m_list.SetItemText(5,3,str);
	m_list.SetItemText(5,4,"江门-->广州");

	str.Format("%d",tick_num[6]);
	m_list.SetItemText(6,0,"3003");
	m_list.SetItemText(6,1,"13:00");
	m_list.SetItemText(6,2,"￥40");
	m_list.SetItemText(6,3,str);
	m_list.SetItemText(6,4,"江门-->广州");

	str.Format("%d",tick_num[7]);
	m_list.SetItemText(7,0,"3004");
	m_list.SetItemText(7,1,"16:00");
	m_list.SetItemText(7,2,"￥40");
	m_list.SetItemText(7,3,str);
	m_list.SetItemText(7,4,"江门-->广州");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBuyticketDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBuyticketDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBuyticketDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HBRUSH CBuyticketDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	
	// TODO: Return a different brush if the default is not desired

     if (pWnd->GetDlgCtrlID() == IDC_STATIC)// IDC_Display为所选文本框ID
 
     {
 
         pDC->SetTextColor(RGB(255, 0, 0));//设置字体颜色
 
		
 
         //pDC->SetBkMode(TRANSPARENT);//设置背景透明
 
    }


	return hbr;
}

void CBuyticketDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CBuyticketDlg::OnClickList3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	POSITION pos = m_list.GetFirstSelectedItemPosition();
	int nSel = m_list.GetNextSelectedItem(pos);

	SetDlgItemText(ticketnum,m_list.GetItemText(nSel,0));  
}

void CBuyticketDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	CString buynum,seqnum;
	GetDlgItemText(IDC_EDIT1,buynum);
	GetDlgItemText(ticketnum,seqnum);
	
	if(seqnum=="2001")
	{
		int nNum;
		nNum=atoi(buynum);
	
		while(lock[0]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[0]=1;
				if(nNum<=tick_num[0])
		{
				
				tick_num[0] -=nNum;
				CString str;
				str.Format("%d",tick_num[0]);
				m_list.SetItemText(0,3,str);
			
			
		}
		else
			AfxMessageBox("余票不足"); 
		lock[0]=0;
	}
	if(seqnum=="2002")
	{
		int nNum;
		nNum=atoi(buynum);
		while(lock[1]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[1]=1;
		if(nNum<=tick_num[1])
		{

			tick_num[1] -=nNum;
			CString str;
			str.Format("%d",tick_num[1]);
			m_list.SetItemText(1,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[1]=0;
	}
	if(seqnum=="2003")
	{
		while(lock[2]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		int nNum;
		nNum=atoi(buynum);
		lock[2]=1;
		if(nNum<=tick_num[2])
		{
			tick_num[2] -=nNum;
			CString str;
			str.Format("%d",tick_num[2]);
			m_list.SetItemText(2,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[2]=0;
	}
	if(seqnum=="2004")
	{

		int nNum;
		nNum=atoi(buynum);

		while(lock[3]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[3]=1;
		if(nNum<=tick_num[3])
		{
			tick_num[3] -=nNum;
			CString str;
			str.Format("%d",tick_num[3]);
			m_list.SetItemText(3,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[2]=0;
	}
	if(seqnum=="3001")
	{
		int nNum;
		nNum=atoi(buynum);
		while(lock[4]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}

		lock[4]=1;
		if(nNum<=tick_num[4])
		{
			tick_num[4] -=nNum;
			CString str;
			str.Format("%d",tick_num[4]);
			m_list.SetItemText(4,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[4]=0;
	}
	if(seqnum=="3002")
	{
		int nNum;
		nNum=atoi(buynum);
		while(lock[5]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[5]=1;
		if(nNum<=tick_num[5])
		{
			tick_num[5] -=nNum;
			CString str;
			str.Format("%d",tick_num[5]);
			m_list.SetItemText(5,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[5]=0;
	}
	if(seqnum=="3003")
	{
		int nNum;
		nNum=atoi(buynum);
		while(lock[6]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[6]=1;
		if(nNum<=tick_num[6])
		{
			tick_num[6] -=nNum;
			CString str;
			str.Format("%d",tick_num[6]);
			m_list.SetItemText(6,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[6]=0;
	}
	if(seqnum=="3004")
	{
		int nNum;
		nNum=atoi(buynum);
		while(lock[7]==1)
		{
			int randtime=rand()%100;
			Sleep(randtime);
		}
		lock[7]=1;
		if(nNum<=tick_num[7])
		{
			tick_num[7] -=nNum;
			CString str;
			str.Format("%d",tick_num[7]);
			m_list.SetItemText(7,3,str);
		}
		else
			AfxMessageBox("余票不足"); 
		lock[7]=0;
	}

	SetDlgItemText(ticketnum,seqnum);
}
