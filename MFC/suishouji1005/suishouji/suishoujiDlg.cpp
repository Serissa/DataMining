
// SuiShouJiDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "SuiShouJi.h"
#include "SuiShouJiDlg.h"
#include "afxdialogex.h"
#include "OpenMsgDlg.h"

#include "EditMsgDlg.h"
#include "DBSDK.h"
#include "wordSearch.h"

#include "TestComDlg.h"
#include "TestCom.h"

#include "AdvancedSearchDlg.h"
#include "DB_operater.h"
#include "CApplication.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CApplication0.h"
#include "AddMsgDlg.h"
#include "InitializeCtrl.h"
#include "HtmlMsgDlg.h"
#include "DiaryDlg.h"
#include "CloseDlg.h"
#include "ChangeSkin.h"

#include <MsHTML.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()

};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_COMMAND(ID_32781, &CAboutDlg::On32781)
END_MESSAGE_MAP()


// CSuiShouJiDlg 对话框




CSuiShouJiDlg::CSuiShouJiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSuiShouJiDlg::IDD, pParent)
	, checktime1(TRUE)
	, checktime2(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
	htmldlg = NULL;	
//	m_advancesearch = NULL;

}

CSuiShouJiDlg::~CSuiShouJiDlg()
{
	Shell_NotifyIcon(IDR_MAINFRAME, &m_notify);
	dialogbool = false;
}


void CSuiShouJiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_webTree);
	DDX_Control(pDX, IDC_LIST1, m_CheckList);
	DDX_Control(pDX, IDC_BUTTON4, m_RightButton);
	DDX_Control(pDX, IDC_BUTTON3, m_LeftButton);
	DDX_Control(pDX, IDC_BUTTON2, m_DeleteButton);
	DDX_Control(pDX, IDC_BUTTON1, m_AddButton);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//DDX_Control(pDX, IDC_IMG, m_jzmPicture);
	DDX_Control(pDX, IDC_BUTTON7, m_menuOut);
	DDX_Control(pDX, IDC_LIST2, m_msgList);

	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Control(pDX, IDC_EXPLORER1, m_nyweb);
	DDX_Control(pDX, IDC_BUTTON5, m_searchbutton);
	//DDX_Control(pDX, IDC_STATIC100, m_title);
	DDX_Control(pDX, IDC_CHECK1, m_attachment);
	DDX_Control(pDX, IDC_MAINEDIT_BTN, m_mainedit);
}

BEGIN_MESSAGE_MAP(CSuiShouJiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &CSuiShouJiDlg::OnTreeR_Click)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, &CSuiShouJiDlg::OnTreeL_Edit)
	ON_COMMAND(ID_32772, &CSuiShouJiDlg::OnModify)
	ON_COMMAND(ID_32773, &CSuiShouJiDlg::OnDelete)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CSuiShouJiDlg::OnTreeL_Click)
	ON_BN_CLICKED(IDC_BUTTON5, &CSuiShouJiDlg::OnQuery)			
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON7, &CSuiShouJiDlg::OnBnClickedButton7)
	ON_WM_CLOSE()
	//ON_COMMAND(ID_32774, &CSuiShouJiDlg::OnOpenFile)
	ON_COMMAND(ID_32781, &CSuiShouJiDlg::OnInsertMenu)		
	ON_WM_TIMER()
	ON_COMMAND(ID_32775, &CSuiShouJiDlg::OnDeleteFile)
	ON_COMMAND(ID_Menu, &CSuiShouJiDlg::OnMenu)
	ON_COMMAND(ID_4, &CSuiShouJiDlg::OnOpen_Child)
	ON_COMMAND(ID_5, &CSuiShouJiDlg::OnModify_Child)
    ON_NOTIFY(NM_DBLCLK, IDC_LIST2, &CSuiShouJiDlg::OnNMDblclkList2)	
	//ON_COMMAND(ID_32776, &CSuiShouJiDlg::OnModifyMsg)
	ON_COMMAND(ID_32788, &CSuiShouJiDlg::OnAddFolder)
	ON_COMMAND(ID_32789, &CSuiShouJiDlg::OnMsgInsert)
	ON_NOTIFY(NM_RCLICK, IDC_LIST2, &CSuiShouJiDlg::OnNMRClickList2)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &CSuiShouJiDlg::OnNMDblclkTree1)
	ON_COMMAND(ID_32795, &CSuiShouJiDlg::OnAddMsg_Child1)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, &CSuiShouJiDlg::OnTvnBeginlabeleditTree1)
	ON_COMMAND(ID_32790, &CSuiShouJiDlg::OnExport)
	ON_COMMAND(ID_32779, &CSuiShouJiDlg::OnBackUp)
	ON_COMMAND(ID_32799, &CSuiShouJiDlg::OnRename)
	ON_COMMAND(ID_32801, &CSuiShouJiDlg::OnRenameFile)
	ON_COMMAND(ID_7, &CSuiShouJiDlg::OnRename_Child)
	ON_COMMAND(ID_32802, &CSuiShouJiDlg::OnExportWord)
	ON_COMMAND(ID_32780, &CSuiShouJiDlg::OnReCover)
	ON_COMMAND(ID_32803, &CSuiShouJiDlg::OnEditMsg)
	//ON_MESSAGE(WM_USER_NOTIFYICON,&CSuiShouJiDlg::OnNotifyMsg) 
	//ON_MESSAGE(WM_USER_NOTIFYICON, &CSuiShouJiDlg::WindowProc)
	ON_COMMAND(ID_32804, &CSuiShouJiDlg::OnExitSuiShouJi)
	ON_COMMAND(ID_32806, &CSuiShouJiDlg::OnAddDaily)
	ON_COMMAND(ID_32818, &CSuiShouJiDlg::OnSortByDay)
	ON_COMMAND(ID_32819, &CSuiShouJiDlg::OnSortByMonth)
	ON_COMMAND(ID_32813, &CSuiShouJiDlg::OnAddContact)
	ON_COMMAND(ID_32814, &CSuiShouJiDlg::OnAddTag)
	ON_COMMAND(ID_32815, &CSuiShouJiDlg::OnExportTelephoneBook)
	ON_COMMAND(ID_32811, &CSuiShouJiDlg::OnSortByMajor)
	ON_COMMAND(ID_32812, &CSuiShouJiDlg::OnSortByPart)
	ON_COMMAND(ID_32810, &CSuiShouJiDlg::OnSortByName)
	ON_COMMAND(ID_32821, &CSuiShouJiDlg::OnDiaryExport)
	ON_COMMAND(ID_32823, &CSuiShouJiDlg::OnDiaryDelete)
	ON_COMMAND(ID_32822, &CSuiShouJiDlg::OnDiaryEdit)
	ON_BN_CLICKED(IDC_BUTTON8, &CSuiShouJiDlg::OnBnClickedButton8)
	ON_COMMAND(ID_32824, &CSuiShouJiDlg::OnAddTime1Row)
	ON_WM_INITMENUPOPUP()
	ON_UPDATE_COMMAND_UI(ID_32824, &CSuiShouJiDlg::OnUpdateTime1)
	ON_COMMAND(ID_32827, &CSuiShouJiDlg::OnAddTime2Row)
	ON_UPDATE_COMMAND_UI(ID_32827, &CSuiShouJiDlg::OnUpdateTime2)
	ON_COMMAND(ID_32828, &CSuiShouJiDlg::OnAdanceSearch)
	ON_WM_NCHITTEST()
	ON_WM_SIZING()

	ON_BN_CLICKED(IDC_MAINEDIT_BTN, &CSuiShouJiDlg::OnBnClickedMaineditBtn)
	ON_BN_CLICKED(IDC_MAINDEL_BTN, &CSuiShouJiDlg::OnBnClickedMaindelBtn)
	ON_BN_CLICKED(IDC_MAINEXP_BTN, &CSuiShouJiDlg::OnBnClickedMainexpBtn)
	ON_BN_CLICKED(IDC_MAINSAVE_BTN, &CSuiShouJiDlg::OnBnClickedMainsaveBtn)
	ON_WM_NCLBUTTONDOWN()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE1, &CSuiShouJiDlg::OnTvnItemexpandedTree1)
	ON_BN_CLICKED(IDC_BUTTON11, &CSuiShouJiDlg::OnBnClickedButton11)
END_MESSAGE_MAP()

BOOL CSuiShouJiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	int i,j,m;
	int msg;  
	dialogbool = false;
	//函数返回信息
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//GetModuleDir(&exe_path);

	CString dbPath;//easydb.mdb";
	//GetWorkDir(&dbPath);
	dbPath = exe_path;
	dbPath = dbPath+_T("\\easydb.mdb");
	IMVL_Initialize(dbPath);

	
	 
	
	TextFont.CreatePointFont(120,_T("微软雅黑"));
	TitleFont.CreatePointFont(110,_T("微软雅黑"));
	NameFont.CreatePointFont(130,_T("微软雅黑"));
	DefaultFont.CreatePointFont(140,_T("楷体"));
	SetTimer(1,1000,NULL);   
	//isfresh=0;
	
	m_edit.SetFont(&TextFont);
	HICON hIcon_1 = theApp.LoadIcon(IDI_ICON7);
	m_menuOut.SetIcon(hIcon_1);
	HICON hIcon_2=theApp.LoadIcon(IDI_ICON13);
	//m_searchbutton.SetIcon(hIcon_2);



	//记录窗口的初始大小
	CRect rect;
	GetWindowRect(&rect);
	GetDlgItem(IDC_TREE1)->MoveWindow(0, 0, rect.Width()/4, rect.Height()-30, TRUE);
	GetDlgItem(IDC_LIST2)->MoveWindow(rect.Width()/4, 34, rect.Width()*3/4, rect.Height()-64, TRUE);

	GetDlgItem(IDC_EXPLORER1)->MoveWindow(rect.Width()/4, 68, rect.Width()*3/4, rect.Height()-98, TRUE);
	//GetDlgItem(IDC_EXPLORER1)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_BUTTON5)->MoveWindow(rect.Width()-85, 3, 60, 28, TRUE);
	m_searchbutton.SetFont(&DefaultFont);
	GetDlgItem(IDC_BUTTON5)->SetWindowText(_T("搜索"));

	GetDlgItem(IDC_BUTTON7)->MoveWindow(rect.Width()-20, 3, 20, 28, TRUE);

    GetDlgItem(IDC_EDIT1)->MoveWindow(rect.Width()-480, 3, 395, 28, TRUE);
	
	GetDlgItem(IDC_CHECK1)->MoveWindow(rect.Width()-550, 3, 70, 28, TRUE);

	GetDlgItem(IDC_MAINEDIT_BTN)->MoveWindow(rect.Width()-550, 37, 60, 20, TRUE);
	GetDlgItem(IDC_MAINDEL_BTN)->MoveWindow(rect.Width()-480, 37, 60, 20, TRUE);
	GetDlgItem(IDC_MAINEXP_BTN)->MoveWindow(rect.Width()-410, 37, 60, 20, TRUE);
	GetDlgItem(IDC_MAINSAVE_BTN)->MoveWindow(rect.Width()-340, 37, 60, 20, TRUE);



	listRect.AddTail(rect);
	 
	CWnd* pWnd = GetWindow(GW_CHILD);//获取子窗体
	while(pWnd)
		 {
			  pWnd->GetWindowRect(rect);//子窗体的区域
			  listRect.AddTail(rect);           //CList<CRect,CRect> m_listRect成员变量
			  pWnd = pWnd->GetNextWindow();//取下一个子窗体
		  }	
	
	//托盘显示
	m_notify.cbSize=sizeof NOTIFYICONDATA;  
	m_notify.hWnd=this->m_hWnd;    
	m_notify.uID=IDR_MAINFRAME;  
	m_notify.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));  
	strcpy(m_notify.szTip,"随手记");  
	m_notify.uCallbackMessage=WM_USER_NOTIFYICON;  
	m_notify.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;    
	Shell_NotifyIcon(NIM_ADD,&m_notify); 

	HICON hIcon[3];      // 图标句柄数组
	hIcon[0] = theApp.LoadIcon(IDI_ICON_folder_y);   
	hIcon[1] = theApp.LoadIcon(IDI_ICON_file);  
	hIcon[2] = theApp.LoadIcon(IDI_ICON_file);
	//m_imageList.Create(16, 16, ILD_TRANSPARENT, 3, 3);   
	  m_imageList.Create(16, 16, ILC_COLOR32 | ILC_MASK | ILD_TRANSPARENT, 3, 3);//ILC_COLOR32真彩色，ILC_MASK背景透明位图
	for (int i=0; i<3; i++)   
	{   
		m_imageList.Add(hIcon[i]);   
	}     
	

	m_webTree.SetFont(&TextFont);
	m_msgList.SetFont(&TitleFont);
	//this->SetBackgroundColor(WHITE_BRUSH,TRUE);
	
    InitializeTreeCtrl(&m_webTree,&m_imageList);
	sorttag1 = _T("专业");
	sorttag2 = _T("月");
	InitializeTreeCtrlHead(&m_msgList);	
	for (int j =0;j<4;j++)
	{
		pos[j]=j;
	}
	m_msgList.GetHeaderCtrl()->SetFont(&NameFont);

	 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSuiShouJiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSuiShouJiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSuiShouJiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

static void   GetCellName(int nRow, int nCol, CString &strName)
{
	CString strRow;
	char cCell = (char)('A' + nCol - 1);

	strName.Format(_T("%c"), cCell);
	strRow.Format(_T( "%d "), nRow);
	strName += strRow;
}


//右击加载菜单
void CSuiShouJiDlg::OnTreeR_Click(NMHDR *pNMHDR, LRESULT *pResult)  
{
	// TODO: 在此添加控件通知处理程序代码
	LPNMTREEVIEW  pTVDispInfo = reinterpret_cast< LPNMTREEVIEW >(pNMHDR);
	CPoint point;
	CMenu menuSetPara;	
	int no;
	GetCursorPos(&point);
	CPoint pointInTree = point;
	m_webTree.ScreenToClient(&pointInTree);
	UINT flag = TVHT_ONITEM;
	HTREEITEM rhItem = m_webTree.HitTest(pointInTree, &flag);
	if (rhItem!=NULL)
	{		
		m_webTree.SelectItem(rhItem);
	} 		
	
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	HTREEITEM pItem = m_webTree.GetParentItem(hItem);
	CString str = m_webTree.GetItemText(hItem);
	HTREEITEM root=m_webTree.GetRootItem( );
	no = m_webTree.GetItemData(hItem);	
	if (no!=-1)
	{
		INDEX_NODE indexnode;
		IMVL_GetNode(no,&indexnode);	
		if (hItem!=root)
		{				
			if (indexnode.IsFolder!=1)
			{
				if (indexnode.iPID==28)
				{
					 menuSetPara.LoadMenu(IDR_MENU12);
				}
				else
				{
                     menuSetPara.LoadMenu(IDR_MENU2);
				}
													
			}
			else
			{
				if ( indexnode.iPID==1)
				{
					if (strcmp(str,"日记")==0)
					{
						menuSetPara.LoadMenu(IDR_MENU10);
					}
					else if (strcmp(str,"通讯录")==0)
					{
						menuSetPara.LoadMenu(IDR_MENU11);
					}					
					else
					{
						menuSetPara.LoadMenu(IDR_MENU1);
					}

				}
				else 
				{
					if (strcmp(m_webTree.GetItemText(pItem),"日记")==0||strcmp(m_webTree.GetItemText(pItem),"日记")==0)
					{
					}
					else
					{
						menuSetPara.LoadMenu(IDR_MENU5);
					}

				} 				
			}			
		}
		else{
			menuSetPara.LoadMenu(IDR_MENU4);			
		}	
		CMenu *pa=menuSetPara.GetSubMenu(0);
		CPoint pt; GetCursorPos(&pt);			
		pa->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);	  
		menuSetPara.DestroyMenu();	
	}	
	*pResult = 0;
}


void CSuiShouJiDlg::OnModify()   //2级目录修改属性
{
	// TODO: 在此添加命令处理程序代码
	CTestCom dlg;	
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	dlg.sql_text.Format("%d", m_webTree.GetItemData(hItem));	
	dlg.m_isChild=0;
	dlg.DoModal();	  
	//this->ShowWindow(1);
}


void CSuiShouJiDlg::OnDelete()   //删除目录
{
	// TODO: 在此添加命令处理程序代码
	//CTipDlg dlg;	
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	INDEX_NODE index;
	CString tip,str;
	IMVL_GetNode(no,&index);
	str = index.name;
	if (index.IsFolder==1)
	{
		tip=_T("确定要删除目录：")+ str;	
	} 
	else
	{
		tip=_T("确定要删除文件：")+str;	
	}
	if(MessageBox(tip,_T("提示"),MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
	{
		int msg=IMVL_Delete(no);
		m_webTree.DeleteItem(hItem);	
	}
}


void CSuiShouJiDlg::OnTreeL_Click(NMHDR *pNMHDR, LRESULT *pResult)//树形菜单左击事件
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	InitializeTreeCtrlHead(&m_msgList);
	HTREEITEM hItem = m_webTree.GetSelectedItem();

	UINT ret = m_webTree.GetItemState(hItem, TVIS_EXPANDEDONCE);


	int listrowcount = 0;
	if (m_webTree.GetItemData(hItem)!=-1)
	{
		HTREEITEM rItem = m_webTree.GetRootItem();
		CString liststr;
		INDEX_NODE indexnode;
		INDEX_NODE foldernode;
		int no = m_webTree.GetItemData(hItem);

		IMVL_GetNode(no,&indexnode);	
		int count=0;
		if (hItem==rItem)
		{		
			m_msgList.DeleteAllItems();			
		} 
	else{
		CString str;		                               
		if (indexnode.IsFolder==1)
		{
			m_msgList.DeleteAllItems();		   	  
			BOOL acs=m_msgList.IsWindowVisible();	
			HTREEITEM phItem = m_webTree.GetParentItem(hItem);
			
			if (!m_msgList.IsWindowVisible())
			{
				m_msgList.ShowWindow(TRUE);	
				GetDlgItem(IDC_MAINEDIT_BTN)->ShowWindow(FALSE);
				GetDlgItem(IDC_MAINDEL_BTN)->ShowWindow(FALSE);
				GetDlgItem(IDC_MAINEXP_BTN)->ShowWindow(FALSE);
				GetDlgItem(IDC_MAINSAVE_BTN)->ShowWindow(FALSE);
			}		   
		}

		else
		{			
			IMVL_GetNode(indexnode.iPID,&foldernode);
			CString key[MAX_DATA_NUM],val[MAX_DATA_NUM],val1[MAX_DATA_NUM];
			//AfxMessageBox(indexnode.content);
			int num = Getkeyval(indexnode.content, key, val );
			Getkeyval(foldernode.content, key, val1 );
			//SetHtml(val1,val,key,indexnode.name,"MFCHtml.htm", num);
			HTREEITEM hItem1 = m_webTree.GetParentItem(hItem);
			HTREEITEM hItem2 = m_webTree.GetParentItem(hItem1);
			if (strcmp(m_webTree.GetItemText(hItem1),"日记")==0||strcmp(m_webTree.GetItemText(hItem2),"日记")==0)
			{
				//CString diary_path = exe_path + "\\html\\DiaryHtml.htm";
				//if (!m_nyweb.IsWindowVisible())
				//{
				//	GetDlgItem(IDC_EXPLORER1)->ShowWindow(SW_SHOW);
				//}

                SetDiaryHtml(val, exe_path);
				m_nyweb.Navigate((exe_path+_T("\\html\\DiaryHtml.htm")),NULL,NULL,NULL,NULL);	
				liststr.Format("%s",indexnode.name);
				GetDlgItem(IDC_MAINEDIT_BTN)->ShowWindow(TRUE);
				//GetDlgItem(IDC_MAINDEL_BTN)->ShowWindow(TRUE);
				//GetDlgItem(IDC_MAINEXP_BTN)->ShowWindow(TRUE);
				GetDlgItem(IDC_MAINSAVE_BTN)->ShowWindow(TRUE);

			} 
			else
			{
				//if (!m_nyweb.IsWindowVisible())
				//{
				//	GetDlgItem(IDC_EXPLORER1)->ShowWindow(SW_SHOW);
				//}
				//CString mfc_path = exe_path + "\\html\\MFCHtml.htm";
				SetHtml(val1,val,key,indexnode.name,exe_path, num);
				m_nyweb.Navigate((exe_path+_T("\\html\\MFCHtml.htm")),NULL,NULL,NULL,NULL);	
				liststr.Format("%s",indexnode.name);
				GetDlgItem(IDC_MAINEDIT_BTN)->ShowWindow(FALSE);
				//GetDlgItem(IDC_MAINDEL_BTN)->ShowWindow(TRUE);
				//GetDlgItem(IDC_MAINEXP_BTN)->ShowWindow(TRUE);
				GetDlgItem(IDC_MAINSAVE_BTN)->ShowWindow(FALSE);


			}
			//SetDiaryHtml(val1, "MFCHtml.htm");

			BOOL acs1=m_msgList.IsWindowVisible();	
			if (m_msgList.IsWindowVisible())
			{
			m_msgList.ShowWindow(FALSE);			
			}		    
			
		}
	}
	if (m_webTree.GetChildItem(hItem)!=NULL)
	{
		int selectno = m_webTree.GetItemData(hItem);
		HTREEITEM par_hItem = m_webTree.GetParentItem(hItem);
//		int par_no = m_webTree.GetItemData(par_hItem);
		if(selectno!=27&&selectno!=28)
		{
		HTREEITEM subhItem=m_webTree.GetChildItem(hItem);		
		CString str;		
		while (subhItem!=NULL)
		{	
			int a=m_webTree.GetItemData(subhItem);
		//	UpdateListRow(&m_msgList,a);
			
			INDEX_NODE index;
			IMVL_GetNode(a,&index);
			str=m_webTree.GetItemText(subhItem);			
			int idc=m_msgList.InsertItem(count,str);

			m_msgList.SetItemText(count, 1, m_webTree.GetItemText(hItem));
			for (int i =2;i<4;i++)
			{
				if (pos[2]!=-1)
				{
					m_msgList.SetItemText(count, 2, index.modifyTime);
					m_msgList.SetItemText(count, 3, index.createTime);
				}
				else
				{
					m_msgList.SetItemText(count, 2, index.createTime);
				}
			}			
			m_msgList.SetItemData(count,a);
			subhItem=m_webTree.GetNextSiblingItem(subhItem);
			count++	;	
		}
		
		}
		else
		{
			UpdateList(&m_msgList,selectno,m_webTree.GetItemText(hItem),pos);
			m_msgList.DeleteColumn(1);
		}
	 }
	}
	else
	{
		if (m_webTree.GetChildItem(hItem)!=NULL)
	{
		int count = 0;
		m_msgList.DeleteAllItems();
		HTREEITEM subhItem=m_webTree.GetChildItem(hItem);		
		CString str;		
		while (subhItem!=NULL)
		{	
			int a=m_webTree.GetItemData(subhItem);
			INDEX_NODE index;
			IMVL_GetNode(a,&index);                           
			str=m_webTree.GetItemText(subhItem);			
			int idc=m_msgList.InsertItem(count,str);
			m_msgList.SetItemText(count, 1, m_webTree.GetItemText(hItem));
			for (int i =2;i<4;i++)
			{
				if (pos[2]!=-1)
				{
					m_msgList.SetItemText(count, 2, index.modifyTime);
					m_msgList.SetItemText(count, 3, index.createTime);
				}
				else
				{
					m_msgList.SetItemText(count, 2, index.createTime);
				}
			}		
			m_msgList.SetItemData(count,a);
			subhItem=m_webTree.GetNextSiblingItem(subhItem);
			count++	;	
		}
		HTREEITEM par_hItem = m_webTree.GetParentItem(hItem);
		int par_no = m_webTree.GetItemData(par_hItem);
		if (par_no == 27||par_no == 28)
		{
			m_msgList.DeleteColumn(1);
		}
	 }
	}
	*pResult = 0;
}

//搜索响应事件
void CSuiShouJiDlg::OnQuery()   
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString sqltext, textSpace;
	int i;
	m_edit.GetWindowTextA(sqltext);
	((CEdit*)GetDlgItem(IDC_EDIT1))->ModifyStyleEx( 0,ES_PASSWORD,0);//SWP_NOZORDER
	//m_edit.ModifyStyle(WS_EX_CLIENTEDGE,NULL);
	//m_edit.SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_DRAWFRAME);
	return;
	INDEX_TABLE indextable, resulttable;
	indextable.num = 0;
	resulttable.num = 0;
	if (strcmp(sqltext,_T(""))==0)
	{
		//MessageBox(_T("搜索关键字不可为空"),_T("提示"),MB_OK|MB_ICONWARNING);
	} 
	else
	{
		if (m_attachment.GetCheck())   //附件搜索
		{
//			MessageBox(_T("文档附件都搜索"),_T("提示"),MB_OK|MB_ICONWARNING);
			IMVL_Search(sqltext,&indextable);
			CString str = _T("");
			IMVL_Search(str,&indextable);
			IMVL_WordSearch(sqltext, &indextable, &resulttable);
		}
	else  
		{
//			MessageBox(_T("只搜文档"),_T("提示"),MB_OK|MB_ICONWARNING);
			IMVL_Search(sqltext,&indextable);
		}
MessageBox("搜索完成！");
   }
	
	//m_msgList.DeleteAllItems();
	InitializeTreeCtrlHead(&m_msgList);
	INDEX_NODE index;
	int count = 0;
	for (int j=0;j<resulttable.num;j++)
	{
		if (resulttable.index[j].ID!=-1)
		{
			IMVL_GetNode(resulttable.index[j].iPID,&index);
			m_msgList.InsertItem(count,resulttable.index[j].name);
			m_msgList.SetItemData(count,resulttable.index[j].ID);
			m_msgList.SetItemText(count,1,index.name);
			m_msgList.SetItemText(count,2,resulttable.index[j].modifyTime);
			m_msgList.SetItemText(count,3,resulttable.index[j].createTime);
			count++;
		}		
	}
	for (int j =0;j<4;j++)
	{
		pos[j]=j;
	}
	if (!m_msgList.IsWindowVisible())
	{
		m_msgList.ShowWindow(TRUE);			  
	}

	
	/*HTREEITEM hitem = m_webTree.GetSelectedItem();
	CString name = m_webTree.GetItemText(hitem);
	
	int child[MAX_DATA_NUM];
	int num = 0;
	TreeGetChild(&m_webTree,hitem,child,&num);
	CString number;
	number.Format("%d",child[0]);
	GetDlgItem(IDC_EDIT4)->SetWindowTextA(number);*/
}

//修改窗口中控件的大小
void CSuiShouJiDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(nType == 1) return;  //最小化则什么都不做 

	if (m_webTree)
	{
			m_webTree.MoveWindow(0, 0, cx/4, cy, TRUE);
	}

	if (m_msgList)
	{
			m_msgList.MoveWindow(cx/4, 34, cx*3/4, cy-34, TRUE);
	}

	if (m_nyweb)
	{
			m_nyweb.MoveWindow(cx/4, 68, cx*3/4, cy-68, TRUE);
	}
if (m_searchbutton)
{
	if (m_searchbutton.IsWindowVisible() == TRUE)
	{
		m_searchbutton.MoveWindow(cx-85, 3, 60, 28, TRUE);
	}
}

if (m_menuOut)
{
	if (m_menuOut.IsWindowVisible() == TRUE)
	{
		m_menuOut.MoveWindow(cx-20, 3, 20, 28, TRUE);
	}
}

if (m_edit)
{
	if (m_edit.IsWindowVisible() == TRUE)
	{
		m_edit.MoveWindow(cx-480, 3, 395, 28, TRUE);
	}
}
if (m_attachment)
{
	m_attachment.MoveWindow(cx-550, 3, 70, 28, TRUE);
}

if (m_mainedit)
{
GetDlgItem(IDC_MAINEDIT_BTN)->MoveWindow(cx-550, 37, 60, 20, TRUE);
GetDlgItem(IDC_MAINDEL_BTN)->MoveWindow(cx-480, 37, 60, 20, TRUE);
GetDlgItem(IDC_MAINEXP_BTN)->MoveWindow(cx-410, 37, 60, 20, TRUE);
GetDlgItem(IDC_MAINSAVE_BTN)->MoveWindow(cx-340, 37, 60, 20, TRUE);
}

m_nyweb.Refresh();
Invalidate();



}

void CSuiShouJiDlg::OnOK()
{ //里面什么也不写
}


void CSuiShouJiDlg::OnBnClickedButton7()    //三角下拉菜单
{
	// TODO: 在此添加控件通知处理程序代码
	CMenu menuSetPara;
	menuSetPara.LoadMenu(IDR_MENU3);
	CMenu *pa=menuSetPara.GetSubMenu(0);
	CPoint pt; GetCursorPos(&pt);
	//ClientToScreen(&pt); 
	pa->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);	  
	menuSetPara.DestroyMenu();
}

void CSuiShouJiDlg::OnInsertMenu()    //头结点插入文件夹
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hCataItem;
	hRoot = m_webTree.GetRootItem();
	hCataItem = m_webTree.InsertItem(_T("新建文件夹"), 0, 0, hRoot, TVI_LAST);
	m_webTree.EditLabel(hCataItem);
	m_webTree.Expand(hRoot,TVE_EXPAND);
	Invalidate();
}

void CSuiShouJiDlg::OnTimer(UINT_PTR nIDEvent)  //定时刷新
{
	//if(nIDEvent   ==   10)   
	//{   

	//	KillTimer(nIDEvent);   
	//	//DestroyWindow();   //可以用这个
	//	keybd_event(VK_RETURN,0,0,0);   
	//	keybd_event(VK_RETURN,0,KEYEVENTF_KEYUP,0);//模拟"回车"命令  

	//}

}

//删除文件
void CSuiShouJiDlg::OnDeleteFile()              
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	INDEX_NODE index;
	CString tip,str;
	IMVL_GetNode(no,&index);
	str = index.name;
	if (index.IsFolder==1)
	{
		tip=_T("确定要删除目录：")+ str;	
	} 
	else
	{
		tip=_T("确定要删除文件：")+str;	
	}
	if(MessageBox(tip,_T("提示"),MB_OKCANCEL|MB_ICONASTERISK ) == IDOK)
	{
		int msg=IMVL_Delete(no);
		if (msg==SUCCESS_VALUE)
		{
			m_webTree.DeleteItem(hItem);
		}
		
	}
}

//三级目录文件夹删除 
void CSuiShouJiDlg::OnMenu()      
{
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	INDEX_NODE index;
	CString tip,str;
	IMVL_GetNode(no,&index);
	str = index.name;
	if (index.IsFolder==1)
	{
		tip=_T("确定要删除目录：")+ str;	
	} 
	else
	{
		tip=_T("确定要删除文件：")+str;	
	}
	if(MessageBox(tip,_T("提示"),MB_OKCANCEL|MB_ICONASTERISK) == IDOK)
	{
		int msg=IMVL_Delete(no);
		if (msg==SUCCESS_VALUE)
		{			
			m_webTree.DeleteItem(hItem);
		}		
	}
}


void CSuiShouJiDlg::OnOpen_Child()     //3级目录导出Excel
{
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	int msg = InitializeExcelList(&m_list,no);
	if (msg ==2)
	{
		MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
	} 
	else
	{
	//CListCtrlToExcel(&m_list,_T("数据表")); 
	CFileDialog FileDialog(FALSE,_T("xls"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2000(*.xls)|*.xls|所有文件(*.*)"),this);

	//if(FileDialog.DoModal()!=IDOK)   
	//{  
	//	return;   
	//}  
	CString cStrFile;//=FileDialog.GetPathName();  //选择保存路径名称  
	CString sDriver;
	//检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"//
	sDriver = GetExcelDriver();
	if(sDriver.IsEmpty())
	{
		//没有发现Excel驱动
		AfxMessageBox(_T("没有安装Excel!\n请先安装Excel软件才能使用导出功能!"));
		return;
	}

	//默认文件名
	HTREEITEM hItemChild = m_webTree.GetSelectedItem();
	CString strhTtem = m_webTree.GetItemText(hItemChild);
	if(!GetDefaultFileName(cStrFile, strhTtem, _T("xls")))
		return;

	if(::PathFileExists(cStrFile))   
		DeleteFile(cStrFile);   

	//CString cStrFile = _T("E:\\myexcel.xls");  
	COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);  

	CApplication0 app; //Excel程序  
	CWorkbooks books; //工作簿集合  
	CWorkbook book;  //工作表  
	CWorksheets sheets;  //工作簿集合  
	CWorksheet sheet; //工作表集合  
	CRange range; //使用区域  

	//CoUninitialize();  

	book.PrintPreview(_variant_t(false));  
	//if(CoInitialize(NULL)==S_FALSE)   
	//{  
	//	//MessageBox(_T("初始化COM支持库失败！"));  
	//	return;  
	//}  

	if(!app.CreateDispatch(_T("Excel.Application"))); //创建IDispatch接口对象  
	{  
		//MessageBox(_T("Error!"));  

	}  


	books = app.get_Workbooks();  

	book = books.Add(covOptional);  


	sheets = book.get_Worksheets();  
	sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表  

	CHeaderCtrl   *pmyHeaderCtrl= m_list.GetHeaderCtrl(); //获取表头  

	int   m_cols   = pmyHeaderCtrl-> GetItemCount(); //获取列数  
	int   m_rows = m_list.GetItemCount();  //获取行数  


	TCHAR     lpBuffer[256];      

	HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
	hdi.mask   =   HDI_TEXT;  
	hdi.pszText   =   lpBuffer;  
	hdi.cchTextMax   =   256;   

	CString   colname;  
	CString strTemp;  

	int   iRow,iCol;  
	for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL   
	{   
		GetCellName(1 ,iCol + 1, colname); //(colname就是对应表格的A1,B1,C1,D1)  

		range   =   sheet.get_Range(COleVariant(colname),COleVariant(colname));    

		pmyHeaderCtrl-> GetItem(iCol,   &hdi); //获取表头每列的信息  

		range.put_Value2(COleVariant(hdi.pszText));  //设置每列的内容  

		int   nWidth   =   m_list.GetColumnWidth(iCol)/6;   

		//得到第iCol+1列     
		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol+1)),vtMissing).pdispVal,true);     

		//设置列宽    
		range.put_ColumnWidth(_variant_t((long)nWidth));  

	}   

	range   =   sheet.get_Range(COleVariant( _T("A1 ")),   COleVariant(colname));   

	range.put_RowHeight(_variant_t((long)20));//设置行的高度   


	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

	COleSafeArray   saRet; //COleSafeArray类是用于处理任意类型和维数的数组的类  
	DWORD   numElements[]={m_rows,m_cols};       //行列写入数组  
	saRet.Create(VT_BSTR,   2,   numElements); //创建所需的数组  

	range = sheet.get_Range(COleVariant( _T("A2 ")),covOptional); //从A2开始  
	range = range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols)); //表的区域  

	long   index[2];    

	for(   iRow   =   1;   iRow   <=   m_rows;   iRow++)//将列表内容写入EXCEL   
	{   
		for   (   iCol   =   1;   iCol   <=   m_cols;   iCol++)    
		{   
			index[0]=iRow-1;   
			index[1]=iCol-1;   

			CString   szTemp;   

			szTemp=m_list.GetItemText(iRow-1,iCol-1); //取得m_list控件中的内容  

			BSTR   bstr   =   szTemp.AllocSysString(); //The AllocSysString method allocates a new BSTR string that is Automation compatible  

			saRet.PutElement(index,bstr); //把m_list控件中的内容放入saRet  

			SysFreeString(bstr);  
		}   
	}    
	range.put_Value2(COleVariant(saRet)); //将得到的数据的saRet数组值放入表格  
	book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件  
	book.put_Saved(true);  

	books.Close();  

	//  
	book.ReleaseDispatch();  
	books.ReleaseDispatch();   

	app.ReleaseDispatch();  
	app.Quit();  
	}
}

//三级目录修改属性
void CSuiShouJiDlg::OnModify_Child()     
{
	// TODO: 在此添加命令处理程序代码
	CTestComDlg dlg;	
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	dlg.sql_text.Format("%d", m_webTree.GetItemData(hItem));
		
	dlg.DoModal();	  
	//this->ShowWindow(1);
}


void CSuiShouJiDlg::OnTreeL_Edit(NMHDR *pNMHDR, LRESULT *pResult)//树形菜单文本编辑事件
{
	//////////////
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);	
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	if (m_webTree.GetItemData(hitem)!=-1)
	{
		INDEX_NODE foldernode;
		strcpy_s(foldernode.content,_T("")); 
		int i;
		TV_DISPINFO* pTVDispinfo = (TV_DISPINFO*)pNMHDR; 
		CString str = m_webTree.GetItemText(pTVDispinfo->item.hItem);
		HTREEITEM parentHitem;
		parentHitem = m_webTree.GetParentItem(pTVDispinfo->item.hItem);	
		if (pTVDispinfo->item.pszText==NULL)
		{
			m_webTree.SetItemText(pTVDispinfo->item.hItem,str);
		} 
		else
		{
			if(strcmp(pTVDispinfo->item.pszText,_T(""))==0 )
			{
				m_webTree.SetItemText(pTVDispinfo->item.hItem,str);
			}
			else{
				m_webTree.SetItemText(pTVDispinfo->item.hItem,pTVDispinfo->item.pszText);
			}
		}

		if (m_webTree.GetItemData(pTVDispinfo->item.hItem)==NULL)
		{
			strcpy_s(foldernode.name,m_webTree.GetItemText(pTVDispinfo->item.hItem));
			foldernode.IsFolder = 1;
			if (parentHitem!=hRoot)
			{
				int a = m_webTree.GetItemData(parentHitem);
				INDEX_NODE pfoldernode;
				IMVL_GetNode(a, &pfoldernode);
				strcpy_s(foldernode.content ,pfoldernode.content);			
				foldernode.iPID = m_webTree.GetItemData(parentHitem);
			} 
			else
			{			
				foldernode.iPID=1;
			}
			CString time;
			GetCurrTime(&time);
			strcpy_s(foldernode.createTime,time);
			strcpy_s(foldernode.modifyTime,time);
			if (IMVL_Create(foldernode.iPID,&foldernode)==SUCCESS_VALUE)
			{			
				m_webTree.SetItemData(pTVDispinfo->item.hItem, foldernode.ID);
			} 
			else
			{
				MessageBox(_T("DATABASE CREATE FOLDER ERROR"),_T("提示"),MB_OKCANCEL);
			}

		}	
		else{
			INDEX_NODE node;
			IMVL_GetNode(m_webTree.GetItemData(pTVDispinfo->item.hItem),&node);
			strcpy_s(node.name,m_webTree.GetItemText(pTVDispinfo->item.hItem));
			IMVL_Update(&node);
		}
	}	
	
	*pResult = 0;
}
//文件信息listctrl双击事件
void CSuiShouJiDlg::OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult)  
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//COpenMsgDlg dlg;
	CString strLangName;      
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;   
	int selNum;
	INDEX_NODE indexnode;	
	if (-1 != pNMListView->iItem)          
	{   		   
		strLangName = m_msgList.GetItemText(pNMListView->iItem, 0);   		
		selNum =  pNMListView->iItem;	
		int no = m_msgList.GetItemData(selNum);
		IMVL_GetNode(no,&indexnode);
		if (indexnode.IsFolder==1)
		{
			if (strcmp(indexnode.content,_T(""))==0)
			{
				MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
			}
			else
			{
				COpenMsgDlg dlg;
				dlg.sql_text.Format("%d",no );
				dlg.DoModal();	  
				//this->ShowWindow(1);
			}
			
		}
		else
		{				
			htmldlg = new CHtmlMsgDlg(); 
			htmldlg->selectno = no;			
			htmldlg->Create(IDD_SHOWHTML, this); 
			htmldlg->ShowWindow(SW_SHOW);  
		}	
	}
	
}

void CSuiShouJiDlg::OnAddFolder()      //2级目录添加文件夹
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hCataItem,pCataItem;
	pCataItem = m_webTree.GetSelectedItem();
	hCataItem = m_webTree.InsertItem(_T("新建文件夹"), 0, 0, pCataItem, TVI_FIRST);
	m_webTree.Expand(pCataItem,TVE_EXPAND);
	m_webTree.EditLabel(hCataItem);
	
	//Invalidate();
}

 //文件增加菜单
void CSuiShouJiDlg::OnMsgInsert()    
{
	// TODO: 在此添加命令处理程序代码
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	HTREEITEM hItem = m_webTree.GetSelectedItem();	
	INDEX_NODE indexnode;
	IMVL_GetNode(m_webTree.GetItemData(hItem),&indexnode);
	if (strcmp(indexnode.content,_T(""))==0)
	{
		MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
	}
	else
	{
		CTreeCtrl *m_tree;
		CExplorer1 *addmsg;
		AddMsgDlg dlg;		
		dlg.selectno = m_webTree.GetItemData(hItem);			
		int num = Getkeyval(indexnode.content, key, val);
		dlg.maxsroll= GetSrollMaxHight(val) + 140;
		dlg.isedit=0;		
		m_tree=&m_webTree;
		dlg.m_tree=m_tree;
		addmsg = &m_nyweb;
		dlg.m_nyweb= addmsg;
		dlg.DoModal();	  
		//this->ShowWindow(1);
	}
	
}


void CSuiShouJiDlg::OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult)   //右边listCtrl右击菜单
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);	
	//*pResult = 0;
}


void CSuiShouJiDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)    //树控件 双击事件
{
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM hItem;
	int selectno;
	INDEX_NODE idexnode;
	hItem=m_webTree.GetSelectedItem();
	hRoot=m_webTree.GetRootItem();
	selectno = m_webTree.GetItemData(hItem);
	if(selectno!=-1)
	{
IMVL_GetNode(selectno,&idexnode);
	if (hItem!=hRoot)
	{
		if (idexnode.IsFolder==1)    //打开文件夹
	        {
				if (strcmp(idexnode.content,_T(""))==0)
				{
					MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
				}
				else
				{
					COpenMsgDlg dlg;
					dlg.sql_text.Format("%d",selectno );
					dlg.isFresh = &isfresh;
					dlg.DoModal();	  
					//this->ShowWindow(TRUE);
				}
	        }	
	}
	}
	
	
	*pResult = 0;
}

//3级目录添加文件
void CSuiShouJiDlg::OnAddMsg_Child1()   
{
	// TODO: 在此添加命令处理程序代码
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	HTREEITEM hItem = m_webTree.GetSelectedItem();	
	INDEX_NODE indexnode;
	IMVL_GetNode(m_webTree.GetItemData(hItem),&indexnode);
	if (strcmp(indexnode.content,_T(""))==0)
	{
		MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
	}
	else
	{
		CTreeCtrl *m_tree;
		AddMsgDlg dlg;		
		dlg.selectno = m_webTree.GetItemData(hItem);			
		int num = Getkeyval(indexnode.content, key, val);
		dlg.maxsroll= GetSrollMaxHight(val) + 140;
		dlg.isedit=0;		
		m_tree=&m_webTree;
		dlg.m_tree=m_tree;	
		dlg.DoModal();	  
		//this->ShowWindow(1);
	}
	
}	


void CSuiShouJiDlg::OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTVDISPINFO pTVDispInfo = reinterpret_cast<LPNMTVDISPINFO>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	TV_DISPINFO* pTVDispinfo = (TV_DISPINFO*)pNMHDR; 
	m_edittext = m_webTree.GetItemText(pTVDispinfo->item.hItem);
	*pResult = 0;
}


void CSuiShouJiDlg::OnExport()   //2级目录导出Excel
{
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	int msg = InitializeExcelList(&m_list,no);
	if (msg ==2)
	{
		MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
	} 
	else
	{
		CFileDialog FileDialog(FALSE,_T("xls"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2000(*.xls)|*.xls|所有文件(*.*)"),this);

		//if(FileDialog.DoModal()!=IDOK)   
		//{  
		//	return;   
		//}  
		CString cStrFile;//=FileDialog.GetPathName();  //选择保存路径名称  
		CString sDriver;
		//检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"//
		sDriver = GetExcelDriver();
		if(sDriver.IsEmpty())
		{
			//没有发现Excel驱动
			AfxMessageBox(_T("没有安装Excel!\n请先安装Excel软件才能使用导出功能!"));
			return;
		}

		//默认文件名
		HTREEITEM hItemOn = m_webTree.GetSelectedItem();
		CString strhTtem = m_webTree.GetItemText(hItemOn);
		if(!GetDefaultFileName(cStrFile, strhTtem, _T("xls")))
			return;

		if(::PathFileExists(cStrFile))   
			DeleteFile(cStrFile);   

		//CString cStrFile = _T("E:\\myexcel.xls");  
		COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);  

		CApplication0 app; //Excel程序  
		CWorkbooks books; //工作簿集合  
		CWorkbook book;  //工作表  
		CWorksheets sheets;  //工作簿集合  
		CWorksheet sheet; //工作表集合  
		CRange range; //使用区域  

		//CoUninitialize();  

		book.PrintPreview(_variant_t(false));  
		//if(CoInitialize(NULL)==S_FALSE)   
		//{  
		//	//MessageBox(_T("初始化COM支持库失败！"));  
		//	return;  
		//}  

		if(!app.CreateDispatch(_T("Excel.Application"))); //创建IDispatch接口对象  
		{  
			//MessageBox(_T("Error!"));  

		}  


		books = app.get_Workbooks();  

		book = books.Add(covOptional);  


		sheets = book.get_Worksheets();  
		sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表  

		CHeaderCtrl   *pmyHeaderCtrl= m_list.GetHeaderCtrl(); //获取表头  

		int   m_cols   = pmyHeaderCtrl-> GetItemCount(); //获取列数  
		int   m_rows = m_list.GetItemCount();  //获取行数  


		TCHAR     lpBuffer[256];      

		HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
		hdi.mask   =   HDI_TEXT;  
		hdi.pszText   =   lpBuffer;  
		hdi.cchTextMax   =   256;   

		CString   colname;  
		CString strTemp;  

		int   iRow,iCol;  
		for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL   
		{   
			GetCellName(1 ,iCol + 1, colname); //(colname就是对应表格的A1,B1,C1,D1)  

			range   =   sheet.get_Range(COleVariant(colname),COleVariant(colname));    

			pmyHeaderCtrl-> GetItem(iCol,   &hdi); //获取表头每列的信息  

			range.put_Value2(COleVariant(hdi.pszText));  //设置每列的内容  

			int   nWidth   =   m_list.GetColumnWidth(iCol)/6;   

			//得到第iCol+1列     
			range.AttachDispatch(range.get_Item(_variant_t((long)(iCol+1)),vtMissing).pdispVal,true);     

			//设置列宽    
			range.put_ColumnWidth(_variant_t((long)nWidth));  

		}   

		range   =   sheet.get_Range(COleVariant( _T("A1 ")),   COleVariant(colname));   

		range.put_RowHeight(_variant_t((long)20));//设置行的高度   


		range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

		COleSafeArray   saRet; //COleSafeArray类是用于处理任意类型和维数的数组的类  
		DWORD   numElements[]={m_rows,m_cols};       //行列写入数组  
		saRet.Create(VT_BSTR,   2,   numElements); //创建所需的数组  

		range = sheet.get_Range(COleVariant( _T("A2 ")),covOptional); //从A2开始  
		range = range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols)); //表的区域  

		long   index[2];    

		for(   iRow   =   1;   iRow   <=   m_rows;   iRow++)//将列表内容写入EXCEL   
		{   
			for   (   iCol   =   1;   iCol   <=   m_cols;   iCol++)    
			{   
				index[0]=iRow-1;   
				index[1]=iCol-1;   

				CString   szTemp;   

				szTemp=m_list.GetItemText(iRow-1,iCol-1); //取得m_list控件中的内容  

				BSTR   bstr   =   szTemp.AllocSysString(); //The AllocSysString method allocates a new BSTR string that is Automation compatible  

				saRet.PutElement(index,bstr); //把m_list控件中的内容放入saRet  

				SysFreeString(bstr);  
			}   
		}    
		range.put_Value2(COleVariant(saRet)); //将得到的数据的saRet数组值放入表格  
		book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件  
		book.put_Saved(true);  

		books.Close();  

		//  
		book.ReleaseDispatch();  
		books.ReleaseDispatch();   

		app.ReleaseDispatch();  
		app.Quit();  
	}	

}


void CSuiShouJiDlg::OnBackUp()
{
	// TODO: 在此添加命令处理程序代码
	int msg=BackUp();
	if(msg!=SUCCESS_VALUE)
	{
		MessageBox(_T("备份失败"),_T("提示"),MB_OK|MB_ICONHAND );
	}
	else{
		MessageBox(_T("备份成功"),_T("提示"),MB_OK|MB_ICONASTERISK );
	}

	/*HTREEITEM hItem = m_webTree.GetSelectedItem();
	m_webTree.EditLabel(hItem);*/
}


void CSuiShouJiDlg::OnRename()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	m_webTree.EditLabel(hItem);
}


void CSuiShouJiDlg::OnRenameFile()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	m_webTree.EditLabel(hItem);
}


void CSuiShouJiDlg::OnRename_Child()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	m_webTree.EditLabel(hItem);
}


void CSuiShouJiDlg::OnExportWord()
{
	// TODO: 在此添加命令处理程序代码
	INDEX_NODE indexnode;  //wenjian
	INDEX_NODE foldernode;  //wenjianjia
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	HTREEITEM pItem = m_webTree.GetParentItem(hItem);
	int no = m_webTree.GetItemData(hItem);	
	int pno = m_webTree.GetItemData(pItem);	
	IMVL_GetNode(no,&indexnode);
	IMVL_GetNode(indexnode.iPID,&foldernode);
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM],val1[MAX_DATA_NUM];
	int num = Getkeyval(indexnode.content, key, val );
	Getkeyval(foldernode.content, key, val1 );
	for (int i = 0; i < num; i++)
	{
		val[i].Replace("<br>", "");
	}

	if(!GetDefaultFileName(sWordFile, indexnode.name, _T("doc")))
		return;
	Exportword(sWordFile, val1, val, key, indexnode.name, num);
}


void CSuiShouJiDlg::OnReCover()
{
	// TODO: 在此添加命令处理程序代码
	int msg = Recover();
	if(msg!=SUCCESS_VALUE)
	{
		MessageBox(_T("恢复失败"),_T("提示"),MB_OK|MB_ICONHAND );
	}
	else{
		MessageBox(_T("恢复成功"),_T("提示"),MB_OK|MB_ICONASTERISK  );
	}
}

BOOL   CSuiShouJiDlg::PreTranslateMessage(MSG*   pMsg)    
{  
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_ESCAPE)     return   TRUE;  
	if(pMsg->message==WM_KEYDOWN   &&   pMsg->wParam==VK_RETURN)   return   TRUE;    
	else    
		return   CDialog::PreTranslateMessage(pMsg);  
}

//编辑文件
void CSuiShouJiDlg::OnEditMsg()
{
	// TODO: 在此添加命令处理程序代码
	AddMsgDlg dlg;		
	//dlg.isfresh = &isfresh;		
	CString key[MAX_DATA_NUM], val1[MAX_DATA_NUM];
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	//HTREEITEM pItem = m_webTree.GetParentItem(hItem);
	INDEX_NODE index;
	IMVL_GetNode(no,&index);
	IMVL_GetNode(index.iPID,&index);  //wenjianjia
	int numkeyval = Getkeyval(index.content, key, val1 );
	dlg.m_nyweb = &m_nyweb;
	dlg.maxsroll= GetSrollMaxHight(val1) + 140;
	dlg.selectno = no;
	dlg.isedit =1;
	dlg.DoModal();
	//this->ShowWindow(1);

}

//LRESULT  CSuiShouJiDlg::OnNotifyMsg(WPARAM wparam,LPARAM lparam)  
//	//wParam接收的是图标的ID，而lParam接收的是鼠标的行为     
//{  
// 	if(wparam!=IDR_MAINFRAME)     
// 		return    1;     
// 	switch(lparam)     
// 	{     
// 	case  WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”     
// 		{       
// 			LPPOINT    lpoint=new    tagPOINT;     
// 			::GetCursorPos(lpoint);//得到鼠标位置     
// 			CMenu    menu;     
// 			menu.CreatePopupMenu();			
// 			menu.AppendMenu(MF_STRING,WM_DESTROY,"关闭"); 			  
// 			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);  		   
// 			HMENU    hmenu=menu.Detach();     
// 			menu.DestroyMenu();     
// 			delete    lpoint;     
// 		}     
// 		//break;     
// 	case    WM_LBUTTONDBLCLK:   
// 		{     
// 			this->ShowWindow(SW_SHOW);
// 		}     
// 		break;     
// 	}      
//	return 0;  
//}  


LRESULT CSuiShouJiDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	 //TODO: 在此添加专用代码和/或调用基类
	switch(message) //判断消息类型  
	{   
	case WM_USER_NOTIFYICON:   
		//如果是用户定义的消息   
		if(lParam==WM_LBUTTONDBLCLK)  
		{   
			//鼠标双击时主窗口出现   
			if(AfxGetApp()->m_pMainWnd->IsWindowVisible()) //判断窗口当前状态  
			{  
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); //隐藏窗口  
			}  
			else  
			{  
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW); //显示窗口  
			}  

		}   
		else if(lParam==WM_RBUTTONDOWN)  
		{ //鼠标右键单击弹出选单   
			CMenu menu;   
			menu.LoadMenu(IDR_MENU9); //载入事先定义的选单
			CMenu *pMenu=menu.GetSubMenu(0);   
			CPoint pos;   
			GetCursorPos(&pos);   
			pMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pos.x,pos.y,AfxGetMainWnd()); 
			menu.DestroyMenu();
		}   
		break;   
	case WM_SYSCOMMAND:   
		
		if(wParam==SC_CLOSE)  
		{  			
			 
		}  
		break;  
	} 
	 
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CSuiShouJiDlg::OnExitSuiShouJi()
{
	// TODO: 在此添加命令处理程序代码

	
}

void CSuiShouJiDlg::OnClose()  
{ 
	int check;
	CCloseDlg dlg;
	dlg.m_check = &check;
	int nResponse =dlg.DoModal();
	if (nResponse == IDOK)  
	{
		if (check == 1)
		{
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);   
			return;  
		}
		else
		{
			::Shell_NotifyIcon(NIM_DELETE,&m_notify);
		}
	}
	else
	{
        return;
	}
	CDialogEx::OnClose(); 	
}  

void CSuiShouJiDlg::OnAddDaily()
{
	// TODO: 在此添加命令处理程序代码
	CDiaryDlg dlg;
	dlg.m_tree = &m_webTree;
	dlg.isedit = 0;
	dlg.sorttag2 = sorttag2;
	dlg.DoModal();
	//this->ShowWindow(1);
}


void CSuiShouJiDlg::OnSortByDay()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	SortByDay(&m_webTree,hitem,28);
	sorttag2 = _T("天");
}


void CSuiShouJiDlg::OnSortByMonth()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	SortByMonth(&m_webTree,hitem);
	sorttag2 = _T("月");
}

//添加联系人
void CSuiShouJiDlg::OnAddContact()
{
	// TODO: 在此添加命令处理程序代码
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	HTREEITEM hItem = m_webTree.GetSelectedItem();	
	INDEX_NODE indexnode;
	IMVL_GetNode(m_webTree.GetItemData(hItem),&indexnode);
	if (strcmp(indexnode.content,_T(""))==0)
	{
		MessageBox(_T("文件夹还未设置属性"),_T("提示"),MB_OK|MB_ICONHAND );
	}
	else
	{
		CTreeCtrl *m_tree;
		AddMsgDlg dlg;		
		dlg.selectno = m_webTree.GetItemData(hItem);			
		int num = Getkeyval(indexnode.content, key, val);
		dlg.maxsroll= GetSrollMaxHight(val) + 140;
		dlg.isedit=0;
		dlg.sorttag1 = sorttag1;
		dlg.sorttag2 = sorttag2;
		m_tree=&m_webTree;
		dlg.m_tree=m_tree;	
		dlg.DoModal();	  
		//this->ShowWindow(1);
	}
}

//标签设置
void CSuiShouJiDlg::OnAddTag()
{
	// TODO: 在此添加命令处理程序代码
	CTestCom dlg;	
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	dlg.sql_text.Format("%d", m_webTree.GetItemData(hItem));
	
	dlg.m_isChild=0;
	dlg.DoModal();	  
	//this->ShowWindow(1);
}

//导出通讯录
void CSuiShouJiDlg::OnExportTelephoneBook()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	InitializeExcelList(&m_list,no);
	//CListCtrlToExcel(&m_list,_T("数据表")); 
	CFileDialog FileDialog(FALSE,_T("xls"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("Microsoft Excel 2000(*.xls)|*.xls|所有文件(*.*)"),this);

	//if(FileDialog.DoModal()!=IDOK)   
	//{  
	//	return;   
	//}  
	CString cStrFile;//=FileDialog.GetPathName();  //选择保存路径名称  
	CString sDriver;
	//检索是否安装有Excel驱动 "Microsoft Excel Driver (*.xls)"//
	sDriver = GetExcelDriver();
	if(sDriver.IsEmpty())
	{
		//没有发现Excel驱动
		AfxMessageBox(_T("没有安装Excel!\n请先安装Excel软件才能使用导出功能!"));
		return;
	}

	//默认文件名
	HTREEITEM hItemChild = m_webTree.GetSelectedItem();
	CString strhTtem = m_webTree.GetItemText(hItemChild);
	if(!GetDefaultFileName(cStrFile, strhTtem, _T("xls")))
		return;

	if(::PathFileExists(cStrFile))   
		DeleteFile(cStrFile);   

	//CString cStrFile = _T("E:\\myexcel.xls");  
	COleVariant covTrue((short)TRUE),covFalse((short)FALSE),covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);  

	CApplication0 app; //Excel程序  
	CWorkbooks books; //工作簿集合  
	CWorkbook book;  //工作表  
	CWorksheets sheets;  //工作簿集合  
	CWorksheet sheet; //工作表集合  
	CRange range; //使用区域  

	//CoUninitialize();  

	book.PrintPreview(_variant_t(false));  
	//if(CoInitialize(NULL)==S_FALSE)   
	//{  
	//	//MessageBox(_T("初始化COM支持库失败！"));  
	//	return;  
	//}  

	if(!app.CreateDispatch(_T("Excel.Application"))); //创建IDispatch接口对象  
	{  
		//MessageBox(_T("Error!"));  

	}  


	books = app.get_Workbooks();  

	book = books.Add(covOptional);  


	sheets = book.get_Worksheets();  
	sheet = sheets.get_Item(COleVariant((short)1));  //得到第一个工作表  

	CHeaderCtrl   *pmyHeaderCtrl= m_list.GetHeaderCtrl(); //获取表头  

	int   m_cols   = pmyHeaderCtrl-> GetItemCount(); //获取列数  
	int   m_rows = m_list.GetItemCount();  //获取行数  


	TCHAR     lpBuffer[256];      

	HDITEM   hdi; //This structure contains information about an item in a header control. This structure has been updated to support header item images and order values.  
	hdi.mask   =   HDI_TEXT;  
	hdi.pszText   =   lpBuffer;  
	hdi.cchTextMax   =   256;   

	CString   colname;  
	CString strTemp;  

	int   iRow,iCol;  
	for(iCol=0;   iCol <m_cols;   iCol++)//将列表的标题头写入EXCEL   
	{   
		GetCellName(1 ,iCol + 1, colname); //(colname就是对应表格的A1,B1,C1,D1)  

		range   =   sheet.get_Range(COleVariant(colname),COleVariant(colname));    

		pmyHeaderCtrl-> GetItem(iCol,   &hdi); //获取表头每列的信息  

		range.put_Value2(COleVariant(hdi.pszText));  //设置每列的内容  

		int   nWidth   =   m_list.GetColumnWidth(iCol)/6;   

		//得到第iCol+1列     
		range.AttachDispatch(range.get_Item(_variant_t((long)(iCol+1)),vtMissing).pdispVal,true);     

		//设置列宽    
		range.put_ColumnWidth(_variant_t((long)nWidth));  

	}   

	range   =   sheet.get_Range(COleVariant( _T("A1 ")),   COleVariant(colname));   

	range.put_RowHeight(_variant_t((long)20));//设置行的高度   


	range.put_VerticalAlignment(COleVariant((short)-4108));//xlVAlignCenter   =   -4108   

	COleSafeArray   saRet; //COleSafeArray类是用于处理任意类型和维数的数组的类  
	DWORD   numElements[]={m_rows,m_cols};       //行列写入数组  
	saRet.Create(VT_BSTR,   2,   numElements); //创建所需的数组  

	range = sheet.get_Range(COleVariant( _T("A2 ")),covOptional); //从A2开始  
	range = range.get_Resize(COleVariant((short)m_rows),COleVariant((short)m_cols)); //表的区域  

	long   index[2];    

	for(   iRow   =   1;   iRow   <=   m_rows;   iRow++)//将列表内容写入EXCEL   
	{   
		for   (   iCol   =   1;   iCol   <=   m_cols;   iCol++)    
		{   
			index[0]=iRow-1;   
			index[1]=iCol-1;   

			CString   szTemp;   

			szTemp=m_list.GetItemText(iRow-1,iCol-1); //取得m_list控件中的内容  

			BSTR   bstr   =   szTemp.AllocSysString(); //The AllocSysString method allocates a new BSTR string that is Automation compatible  

			saRet.PutElement(index,bstr); //把m_list控件中的内容放入saRet  

			SysFreeString(bstr);  
		}   
	}    
	range.put_Value2(COleVariant(saRet)); //将得到的数据的saRet数组值放入表格  
	book.SaveCopyAs(COleVariant(cStrFile)); //保存到cStrFile文件  
	book.put_Saved(true);  

	books.Close();  

	//  
	book.ReleaseDispatch();  
	books.ReleaseDispatch();   

	app.ReleaseDispatch();  
	app.Quit();  
}


void CSuiShouJiDlg::OnSortByMajor()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	SortByTag(&m_webTree,hitem,_T("专业"));
	sorttag1 = _T("专业");
}


void CSuiShouJiDlg::OnSortByPart()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	SortByTag(&m_webTree,hitem,_T("单位"));
	sorttag1 = _T("单位");
}


void CSuiShouJiDlg::OnSortByName()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hitem = m_webTree.GetSelectedItem();
	SortByDay(&m_webTree,hitem,27);
	sorttag1 = _T("名字");
}


void CSuiShouJiDlg::OnDiaryExport()
{
	// TODO: 在此添加命令处理程序代码
	INDEX_NODE indexnode;  //wenjian
	INDEX_NODE foldernode;  //wenjianjia
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	HTREEITEM pItem = m_webTree.GetParentItem(hItem);
	int no = m_webTree.GetItemData(hItem);	
	int pno = m_webTree.GetItemData(pItem);	
	IMVL_GetNode(no,&indexnode);
	IMVL_GetNode(indexnode.iPID,&foldernode);
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM],val1[MAX_DATA_NUM];
	int num = Getkeyval(indexnode.content, key, val );
	Getkeyval(foldernode.content, key, val1 );
	for (int i = 0; i < num; i++)
	{
		val[i].Replace("<br>", "");
	}

	if(!GetDefaultFileName(sWordFile, indexnode.name, _T("doc")))
		return;
	Exportword(sWordFile, val1, val, key, indexnode.name, num);
}


void CSuiShouJiDlg::OnDiaryDelete()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	INDEX_NODE index;
	CString tip,str;
	IMVL_GetNode(no,&index);
	str = index.name;
	if (index.IsFolder==1)
	{
		tip=_T("确定要删除目录：")+ str;	
	} 
	else
	{
		tip=_T("确定要删除文件：")+str;	
	}
	if(MessageBox(tip,_T("提示"),MB_OKCANCEL|MB_ICONASTERISK ) == IDOK)
	{
		int msg=IMVL_Delete(no);
		if (msg==SUCCESS_VALUE)
		{
			m_webTree.DeleteItem(hItem);
		}
	}
}


void CSuiShouJiDlg::OnDiaryEdit()
{
	// TODO: 在此添加命令处理程序代码
	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	CDiaryDlg dlg;
	dlg.isedit = 1;
	dlg.id = no;
	
	dlg.m_tree = &m_webTree;
	dlg.sorttag2 = sorttag2;

	CExplorer1 *diaryedit;
	diaryedit = &m_nyweb;
	dlg.diaryedit = diaryedit;
	dlg.DoModal();
	//this->ShowWindow(1);
}


void CSuiShouJiDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CSuiShouJiDlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类
	if ((((LPNMHDR)lParam)->code == NM_RCLICK))  
	{  
		CPoint pt, pt2;
		CMenu menuSetPara;
		GetCursorPos(&pt);  
		pt2 = pt;  
		m_msgList.ScreenToClient(&pt);  
		CWnd* pWnd = m_msgList.ChildWindowFromPoint(pt);  
		CHeaderCtrl* pHeader = m_msgList.GetHeaderCtrl();  
		if(pWnd && (pWnd->GetSafeHwnd() == pHeader->GetSafeHwnd()))  
		{  
			HDHITTESTINFO info = {0};  
			info.pt = pt;  
			pHeader->SendMessage(HDM_HITTEST, 0, (LPARAM)&info); 
			
			menuSetPara.LoadMenu(IDR_MENU13);
			CMenu *pa=menuSetPara.GetSubMenu(0);
			CPoint pt; GetCursorPos(&pt);
			pa->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);	  
			menuSetPara.DestroyMenu();
		}  
	}  
	return CDialogEx::OnNotify(wParam, lParam, pResult);
}


void CSuiShouJiDlg::OnAddTime1Row()
{

	CRect rect; 	
	int num = m_msgList.GetHeaderCtrl()->GetItemCount();
	m_msgList.GetClientRect(&rect);
	if (checktime1==false)
	{
		pos[2] = m_msgList.InsertColumn(2, _T("修改时间"), LVCFMT_CENTER,rect.Width()/4, 2);
		UpdateListRow(&m_msgList,pos[2],1);
	} 
	else
	{
		
		m_msgList.DeleteColumn(pos[2]);
		pos[2]=-1;
		
	}
	checktime1 = !checktime1;
}


void CSuiShouJiDlg::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CDialogEx::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	ASSERT(pPopupMenu != NULL);
	// Check the enabled state of various menu items.

	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// Determine if menu is popup in top-level menu and set m_pOther to
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup).
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu)
		state.m_pParentMenu = pPopupMenu;    // Parent == child for tracking popup.
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = this;
		// Child windows don't have menus--need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu)
				{
					// When popup is found, m_pParentMenu is containing menu.
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
		state.m_nIndex++)
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // Menu separator or invalid cmd - ignore it.

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// Possibly a popup menu, route to first item of that popup.
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // First item of popup can't be routed to.
			}
			state.DoUpdate(this, TRUE);   // Popups are never auto disabled.
		}
		else
		{
			// Normal menu item.
			// Auto enable/disable if frame window has m_bAutoMenuEnable
			// set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(this, FALSE);
		}

		// Adjust for menu deletions and additions.
		UINT nCount = pPopupMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
	// TODO: 在此处添加消息处理程序代码
}


void CSuiShouJiDlg::OnUpdateTime1(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(checktime1);
}


void CSuiShouJiDlg::OnAddTime2Row()
{
	// TODO: 在此添加命令处理程序代码
	CRect rect; 	
	int num = m_msgList.GetHeaderCtrl()->GetItemCount();
	m_msgList.GetClientRect(&rect);
	if (checktime2==false)
	{
		pos[3] = m_msgList.InsertColumn(3, _T("创建时间"), LVCFMT_CENTER,rect.Width()/4, 3);
		UpdateListRow(&m_msgList,pos[3],2);
	} 
	else
	{		
		m_msgList.DeleteColumn(num-1);
		pos[3]=-1;
	}
	checktime2 = !checktime2;
}


void CSuiShouJiDlg::OnUpdateTime2(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(checktime2);
}


void CSuiShouJiDlg::OnAdanceSearch()
{
	// TODO: 在此添加命令处理程序代码
	if (dialogbool == false)   
	{
		CAdvancedSearchDlg *m_advancesearch= new CAdvancedSearchDlg();
		m_advancesearch->isdialog = &dialogbool;
		m_advancesearch->pos = pos;
		m_advancesearch->m_list = &m_msgList;
		m_advancesearch->Create(IDD_DIALOG2, this);
		m_advancesearch->ShowWindow(SW_SHOW); 
		dialogbool = true;		
	}
}

//添加鼠标拖动窗口实现缩放
LRESULT CSuiShouJiDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);
	//return CDialogEx::OnNcHitTest(point);
}

//在鼠标拖动窗口时设置最小窗口大小
void CSuiShouJiDlg::OnSizing(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnSizing(fwSide, pRect);
	// TODO: 在此处添加消息处理程序代码
	int L = pRect->left;
	int T = pRect->top;

	CRect rect(pRect);
	int width = rect.Width();
	int height = rect.Height();
	if((width < 750) ||(height < 400))
	{
		if (width < 750)
		{
			width = 750;
		}
		if (height < 400)
		{
			height = 400;
		}
		pRect->left = L;
		pRect->top = T;
		
		pRect->right = L + width;
        pRect->bottom = T + height;
	}

}


void CSuiShouJiDlg::OnBnClickedMaineditBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	flage = 1;
	CString allPointData;     

	IDispatch *pDisp = m_nyweb.get_Document();  
	IHTMLDocument2* pDocument;   
	IHTMLElementCollection* pCollection;  

	pDisp->QueryInterface(IID_IHTMLDocument2,(void**)&pDocument);      
	HRESULT hr;  
	hr = pDocument->get_all(&pCollection);  
	if( hr == S_OK )  
	{  
		long celem;  
		hr = pCollection->get_length(&celem);   //得到所有节点的个数用以遍历  
		if( hr == S_OK )  
		{  
			VARIANT varIndex, var;  
			for ( int i = 0; i < celem; i++ )  
			{  
				varIndex.vt = VT_UINT;  
				varIndex.lVal = i;  
				VariantInit(&var);  
				hr = pCollection->item(varIndex,var,&pDisp);  
				if ( hr == S_OK )  
				{  
					IHTMLElement *pElement;  
					hr = pDisp->QueryInterface(IID_IHTMLElement,(void**)&pElement);  
					if ( hr == S_OK )  
					{  
						CString pointData,id;  
						BSTR bs;  
						pElement->get_id(&bs);  
						id = CString(bs);  
						if ( id == _T("edit") )  
						{ 
							//MessageBox(_T("找到按钮了"),_T("提示"),0);
							pElement->click();
						}  
					}  
				}  
			}  
		}  
	}     

}


void CSuiShouJiDlg::OnBnClickedMaindelBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSuiShouJiDlg::OnBnClickedMainexpBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSuiShouJiDlg::OnBnClickedMainsaveBtn()
{
	// TODO: 在此添加控件通知处理程序代码
	if (flage == 1)
	{
		flage = 0;
	CString allPointData;     

	IDispatch *pDisp = m_nyweb.get_Document();  
	IHTMLDocument2* pDocument;   
	IHTMLElementCollection* pCollection;  

	pDisp->QueryInterface(IID_IHTMLDocument2,(void**)&pDocument);      
	HRESULT hr;  
	hr = pDocument->get_all(&pCollection);  
	if( hr == S_OK )  
	{  
		long celem;  
		hr = pCollection->get_length(&celem);   //得到所有节点的个数用以遍历  
		if( hr == S_OK )  
		{  
			VARIANT varIndex, var;  
			for ( int i = 0; i < celem; i++ )  
			{  
				varIndex.vt = VT_UINT;  
				varIndex.lVal = i;  
				VariantInit(&var);  
				hr = pCollection->item(varIndex,var,&pDisp);  
				if ( hr == S_OK )  
				{  
					IHTMLElement *pElement;  
					hr = pDisp->QueryInterface(IID_IHTMLElement,(void**)&pElement);  
					if ( hr == S_OK )  
					{  
						CString pointData,id;  
						BSTR bs;  
						pElement->get_id(&bs);  
						id = CString(bs);  
						if ( id == _T("save") )  
						{ 
							//MessageBox(_T("找到按钮了"),_T("提示"),0);
							pElement->click();

						}  
					}  
				}  
			}  
		}  
	}     
	Sleep(800);
	//CString str;
	//GetTxtStr(&str);


	HTREEITEM hItem = m_webTree.GetSelectedItem();
	int no = m_webTree.GetItemData(hItem);
	CString name = m_webTree.GetItemText(hItem);
	CString keyvaluestr;
	int msg;						
	INDEX_NODE filenode;
	GetTxtStr(&keyvaluestr, exe_path);
	filenode.IsFolder=0;
	filenode.iPID=28;
	strcpy_s(filenode.name, name);							
	if (strlen(keyvaluestr)>1300)
	{
		MessageBox(_T("日记内容过大，编辑失败"),_T("操作提示"),MB_OK|MB_ICONERROR);
	}
	else
	{
		CString time;
		GetCurrTime(&time);								
		INDEX_NODE foldernode;
		IMVL_GetNode(no,&foldernode);
		strcpy_s(filenode.createTime, foldernode.createTime);
		strcpy_s(filenode.modifyTime, time);
		strcpy_s(filenode.content, keyvaluestr);
		filenode.ID = no;
		msg = IMVL_Update(&filenode);

		if (msg == SUCCESS_VALUE)
		{
			MessageBox(_T("日记保存成功"),_T("操作提示"),MB_OK|MB_ICONASTERISK  );
			/*if(strcmp(sorttag2,_T("天"))==0)
			{
			HTREEITEM hArtItem;
			hArtItem = m_webTree.InsertItem(filenode.name, 1, 1, m_webTree.GetSelectedItem(), TVI_LAST);
			m_webTree.SetItemData(hArtItem, filenode.ID);
			}
			else
			{
			SortByMonth(&m_webTree,m_webTree.GetSelectedItem());
			}*/
			//UpdateTree(m_tree,filenode.ID,filenode.name);
		}
		else
		{
			MessageBox(_T("日记保存失败"),_T("操作提示"),MB_OK|MB_ICONERROR  );
		}
	}	
	}

	

	
}


void CSuiShouJiDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CPoint pt = point;
	pt.x -=rcWindow.left;
	pt.y -= rcWindow.top;
	int mfc_with = rcWindow.Width() - pt.x;

	if (0 <= pt.y && pt.y < 27 && 108<mfc_with && mfc_with<135 )
	{
		CChangeSkin dlg;

		dlg.DoModal();	  


		//char szFilters[]= "All Files (*.she)|*.she||";
		//CString pathskin = exe_path + "\\skin\\";
		//CFileDialog fileDlg (TRUE, "*", pathskin, OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
		//if( IDOK == fileDlg.DoModal() )
		//{
		//	CString fileName = fileDlg.GetFileName();
		//	CString path = "skin//"+fileName;
		//	CString pt = fileDlg.GetPathName();
		//	CString path_skin = exe_path + "\\skin\\"+fileName;



		//	CString skin_Save = exe_path+_T("\\skin\\skinsave.txt");//保存皮肤
		//	ofstream outfile(skin_Save);
		//	outfile<<fileName<<endl ;

  //          SetTimer(10,0,NULL); 

		//	SkinH_AttachEx(path_skin, NULL);



		//}

	}


	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


BOOL CSuiShouJiDlg::DestroyWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	Shell_NotifyIcon(NIM_DELETE, &m_notify);          
	return CDialogEx::DestroyWindow();
}


void CSuiShouJiDlg::OnTvnItemexpandedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	HTREEITEM curitem=pNMTreeView->itemNew.hItem;

	//if ( TVIS_EXPANDED & m_webTree.GetItemState(curitem, TVIS_EXPANDED) )
	//{
	//	AfxMessageBox("展开");//,m_webTree.GetItemText(curitem));
	//}
	//else
	//{
	//	AfxMessageBox("没有");
	//}

	*pResult = 0;
}


void CSuiShouJiDlg::OnBnClickedButton11()
{
	m_edit.ModifyStyle(0,WS_BORDER);
	//m_edit.SetWindowPos(NULL,0,0,0,0,SWP_NOZORDER|SWP_NOSIZE|SWP_NOMOVE|SWP_DRAWFRAME);
}
