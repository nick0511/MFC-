// storage_manageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "storage_manage.h"
#include "storage_manageDlg.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include<vector>
#include <algorithm>
#include <sstream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
	int size=1024;
	int used=0;
	//初始化变量
typedef struct Memory
{
	int block_number;//分区号
	char job_name;//作业名
	int start_address;//起始地址
	int block_size;//分区大小
	int state;//状态 （0 1）   1：已分配 2：未分配
} memory;

vector<memory> me;

bool cmp(memory a,memory b)
{
	return a.start_address<b.start_address;
}
	char name='a';
void FF()   //首次适应算法
{
	int flag=0;//分配成功 1  失败 0
	memory node;//申请新节点
	//input
	cout<<"作业名(一个字符):";
	node.job_name=name;
	name++;
	
	int u=rand()%150+1;
	node.block_size=u;
	//ff算法
	sort(me.begin(),me.end(),cmp);//地址递增排序
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
		if((*it).state==0)   //空闲分区链
		{
			if((*it).block_size>u)
			{
				if((*it).block_size-u<=2)
				{
					(*it).state=1;//将该分区从空闲链中移除
					(*it).job_name=name;
					flag=1;
					break;
				}
				else     //有空闲块能满足需求且有剩余
				{
					node.block_number=(*it).block_number;
					node.start_address=(*it).start_address;
					(*it).block_number+=1;
					(*it).start_address+=u;
					(*it).block_size-=u;
					node.state=1;
					me.insert(it--,node);
					flag=1;
					break;
				}
			}
		}
	}
	if(flag==1)
	{
		AfxMessageBox("分配成功！！！");
		used+=u;
		size-=u;
	}
	else
		AfxMessageBox("分配失败！！！");

}

void recovery(char name)   //回收内存
{
	if(me.size()==1)
	{
		me[0].job_name=' ';
		me[0].state=0;
		used-=me.size();
		size+=me.size();
		return;
	}
	for(int i=0; i<me.size(); i++)
	{
		if(i==0&&me[i].job_name==name)
		{
			if(me[i+1].state==0)
			{
				me[i].block_size+=me[i+1].block_size;//合并 回收区与f2
				me[i].state=0;
				me[i].job_name=' ';
				for(int j=i+1; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();

				used-=me.size();
				size+=me.size();
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;

				used-=me.size();
				size+=me.size();
				break;
			}
		}
		if((i==(me.size()-1))&&me[i].job_name==name)
		{
			if(me[i-1].state==0)
			{
				me[i-1].block_size+=me[i].block_size;
				me[i-1].job_name=' ';
				me.pop_back();
				used-=me.size();
				size+=me.size();
				break;
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				used-=me.size();
				size+=me.size();
				break;
			}
		}
		if(me[i].job_name==name)
		{
			if(me[i-1].state==0&&me[i+1].state==0)
			{
				me[i-1].block_size=me[i-1].block_size+me[i].block_size+me[i+1].block_size;
				me[i-1].job_name=' ';
				for(int j=i; j<me.size()-1; j++) //i+1->i i+2->i
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
				for( j=i; j<me.size()-1; j++) // i+2->i
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
				used-=me.size();
				size+=me.size();
				break;
			}
			else if(me[i-1].state==0)
			{
				me[i-1].block_size+=me[i].block_size;
				me[i-1].job_name=' ';
				for(int j=i; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
			}
			else if(me[i+1].state==0)
			{
				me[i].block_size+=me[i+1].block_size;
				me[i].job_name=' ';
				me[i].state=0;
				for(int j=i+1; j<me.size()-1; j++)
				{
					me[j].job_name=me[j+1].job_name;
					me[j].start_address=me[j+1].start_address;
					me[j].block_size=me[j+1].block_size;
					me[j].state=me[j+1].state;
				}
				me.pop_back();
			}
			else
			{
				me[i].job_name=' ';
				me[i].state=0;
				used-=me.size();
				size+=me.size();
				break;
			}
		}
	}
}




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
// CStorage_manageDlg dialog

CStorage_manageDlg::CStorage_manageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStorage_manageDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStorage_manageDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStorage_manageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStorage_manageDlg)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStorage_manageDlg, CDialog)
	//{{AFX_MSG_MAP(CStorage_manageDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Create_BTN, OnBtn)
	ON_BN_CLICKED(CancelBTN, OnCancelBTN)
//	ON_BN_CLICKED(EXIT_BTN, OnBtn)
	ON_BN_CLICKED(BTN_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////W
// CStorage_manageDlg message handlers

BOOL CStorage_manageDlg::OnInitDialog()
{

	CDialog::OnInitDialog();

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

	m_list.InsertColumn(0, TEXT("分区号"),LVCFMT_CENTER,100);
    m_list.InsertColumn(1, TEXT("大小"),LVCFMT_CENTER,100);
	m_list.InsertColumn(2, TEXT("起址"),LVCFMT_CENTER,100);
	m_list.InsertColumn(3, TEXT("状态"),LVCFMT_CENTER,100);
	DWORD dwStyle = m_list.GetExtendedStyle();                    //添加列表框的网格线
    dwStyle |= LVS_EX_FULLROWSELECT;            
    dwStyle |= LVS_EX_GRIDLINES;                
    m_list.SetExtendedStyle(dwStyle);

	for(int n=0;n<30;n++)
		m_list.InsertItem(n,"");
	//初始内容

	// TODO: Add extra initialization here
	//初始化头结点
	CString size_str,used_str;
	size_str.Format("%d",size);
	used_str.Format("%d",used);
	SetDlgItemText(Used,used_str);  
	SetDlgItemText(Free,size_str);  
	memory head;
	head.block_number=0;
	head.start_address=0;
	head.block_size=1024;
	head.state=0;
	me.push_back(head);


	
	int i=0;
	vector<memory>::iterator it;
	for(it=me.begin(); it!=me.end(); it++)
	{
	
			CString num_str,block_size_str,start_address_str,state_str;
			num_str.Format("%d",(*it).block_number);
			block_size_str.Format("%d",(*it).block_size);
			start_address_str.Format("%d",(*it).start_address);
			if((*it).state==0)
				state_str="空闲";
			else
				state_str=(*it).job_name;
			
			m_list.SetItemText(i,0,num_str);
			m_list.SetItemText(i,1,block_size_str);
			m_list.SetItemText(i,2,start_address_str);
			m_list.SetItemText(i,3,state_str);
			i++;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStorage_manageDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStorage_manageDlg::OnPaint() 
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
HCURSOR CStorage_manageDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
int process_num=1;
void CStorage_manageDlg::OnBtn() 
{
	// TODO: Add your control notification handler code here
	FF();

	//更新面板
	vector<memory>::iterator it;
	int i=0;
	for(it=me.begin(); it!=me.end(); it++)
	{
	
			CString num_str,block_size_str,start_address_str,state_str;
			num_str.Format("%d",(*it).block_number);
			block_size_str.Format("%d",(*it).block_size);
			start_address_str.Format("%d",(*it).start_address);
			if((*it).state==0)
				state_str="空闲";
			else
				state_str=(*it).job_name;
			m_list.SetItemText(i,0,num_str);
			m_list.SetItemText(i,1,block_size_str);
			m_list.SetItemText(i,2,start_address_str);
			m_list.SetItemText(i,3,state_str);
			i++;
	}
	CString size_str,used_str;
	size_str.Format("%d",size);
	used_str.Format("%d",used);
	SetDlgItemText(Used,used_str);  
	SetDlgItemText(Free,size_str);  

}
char CString2string(CString csStrData)
{
	string strRet ;
 
	char ss[2048];
	memset(ss, 0, sizeof(char)*2048);
	sprintf(ss, "%s", csStrData);
 
	strRet = ss;
	return strRet[0];
}

void CStorage_manageDlg::OnCancelBTN() 
{
	// TODO: Add your control notification handler code here
	
	CString str; //定义一个变量str
	m_edit.GetWindowText(str); //获取编辑框文本到str
	char a =	CString2string(str);
	recovery(a);
vector<memory>::iterator it;
	int i=0;
	m_list.DeleteAllItems();
	for(int n=0;n<30;n++)
		m_list.InsertItem(n,"");
	for(it=me.begin(); it!=me.end(); it++)
	{
			
			CString num_str,block_size_str,start_address_str,state_str;
			num_str.Format("%d",(*it).block_number);
			block_size_str.Format("%d",(*it).block_size);
			start_address_str.Format("%d",(*it).start_address);
			if((*it).state==0)
				state_str="空闲";
			else
				state_str=(*it).job_name;
			m_list.SetItemText(i,0,num_str);
			m_list.SetItemText(i,1,block_size_str);
			m_list.SetItemText(i,2,start_address_str);
			m_list.SetItemText(i,3,state_str);
			i++;
	}
	CString size_str,used_str;
	size_str.Format("%d",size);
	used_str.Format("%d",used);
	SetDlgItemText(Used,used_str);  
	SetDlgItemText(Free,size_str); 

	size_str.Format("%d",size);
	used_str.Format("%d",used);
	SetDlgItemText(Used,used_str);  
	SetDlgItemText(Free,size_str);  

}

void CStorage_manageDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	PostQuitMessage(0);
}
