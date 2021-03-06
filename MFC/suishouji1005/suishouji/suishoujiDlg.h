
// SuiShouJiDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "atltypes.h"
#include "Afxtempl.h"
#include "ado2.h"
#include "explorer1.h"
#include "HtmlMsgDlg.h"
#include "AdvancedSearchDlg.h"
#define WM_USER_NOTIFYICON WM_USER+1 

// CSuiShouJiDlg 对话框
class CSuiShouJiDlg : public CDialogEx
{
// 构造
public:
	CSuiShouJiDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CSuiShouJiDlg();

// 对话框数据
	enum { IDD = IDD_SUISHOUJI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


	CFont m_treeFont;
private:
	CHtmlMsgDlg* htmldlg;
	
// 实现
protected:
	HICON m_hIcon;

	NOTIFYICONDATA m_notify;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 树形控件变量
	//CAdvancedSearchDlg* m_advancesearch;
	bool dialogbool;
	afx_msg void OnTreeR_Click(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnModify();
	afx_msg void OnDelete();
	afx_msg void OnDeleteFile();
	afx_msg void OnMenu();
	afx_msg void OnOpen_Child();
	afx_msg void OnModify_Child();
	afx_msg void OnDelete_Child();
	//afx_msg void OnAdd_Child();
	//afx_msg void OnModifyMsg();
	afx_msg void OnOK();
	afx_msg void OnClose();
	afx_msg void OnTreeL_Click(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTreeL_Edit(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnQuery();	
	afx_msg void OnDeleteMsg();	
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnBnClickedButton7();	
	//afx_msg void OnOpenFile();	
	afx_msg void OnInsertMenu();		
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddFolder();
	afx_msg void OnMsgInsert();
	afx_msg void OnNMRClickList2(NMHDR *pNMHDR, LRESULT *pResult);

	INDEX_TABLE m_index_table;
	CEdit m_edit;
	CList<CRect,CRect&> listRect;
	int isfresh;
	CButton m_RightButton;
	CButton m_LeftButton;
	CButton m_DeleteButton;
	CButton m_AddButton;
	CTreeCtrl m_webTree;
	CImageList m_imageList;
	CCheckListBox m_CheckList;
	CButton m_menuOut;
	CListCtrl m_msgList;	
	HTREEITEM hRoot;     // 树的根节点的句柄
	CFont DefaultFont,TitleFont,NameFont,TextFont;
	int m_selectnum;
	//CStatic m_static1;
	CString m_edittext;
	CString sorttag1;   //通讯录展开规则
	CString sorttag2;    //日记展开规则
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddMsg_Child1();
	afx_msg void OnTvnBeginlabeleditTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnExport();
	CListCtrl m_list;
	afx_msg void OnBackUp();
	afx_msg void OnRename();
	afx_msg void OnRenameFile();
	afx_msg void OnRename_Child();
	CExplorer1 m_nyweb;
	afx_msg void OnExportWord();
	CString sWordFile;
	afx_msg void OnReCover();
	afx_msg BOOL PreTranslateMessage(MSG*   pMsg);
	CButton m_searchbutton;
	//CStatic m_title;
	afx_msg void OnEditMsg();
	CToolTipCtrl    m_Mytip;
	//afx_msg LRESULT OnNotifyMsg(WPARAM wparam,LPARAM lparam);//托盘
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnExitSuiShouJi();
	afx_msg void OnAddDaily();
	afx_msg void OnSortByDay();
	afx_msg void OnSortByMonth();
	afx_msg void OnAddContact();
	afx_msg void OnAddTag();
	afx_msg void OnExportTelephoneBook();
	afx_msg void OnSortByMajor();
	afx_msg void OnSortByPart();
	afx_msg void OnSortByName();
	afx_msg void OnDiaryExport();
	afx_msg void OnDiaryDelete();
	afx_msg void OnDiaryEdit();
	afx_msg void OnBnClickedButton8();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnAddTime1Row();
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnUpdateTime1(CCmdUI *pCmdUI);
	int pos[4];
	bool checktime1;
	afx_msg void OnAddTime2Row();
	afx_msg void OnUpdateTime2(CCmdUI *pCmdUI);
	bool checktime2;
	afx_msg void OnAdanceSearch();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	
	// 是否搜索附件
	CButton m_attachment;
	afx_msg void OnBnClickedMaineditBtn();
	afx_msg void OnBnClickedMaindelBtn();
	afx_msg void OnBnClickedMainexpBtn();
	afx_msg void OnBnClickedMainsaveBtn();
	int flage;
	CButton m_mainedit;
	//CString exe_path;
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	virtual BOOL DestroyWindow();

	

	afx_msg void OnTvnItemexpandedTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton11();
};
