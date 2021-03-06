#include "stdafx.h"
#include "InitializeCtrl.h"
#include "DB_operater.h"
#include "CApplication.h"
#include "CDocument0.h"
#include "CDocuments.h"
#include "CApplication0.h"
#include "CFont0.h"
#include "CnlineShape.h"
#include "CnlineShapes.h"
#include "CPageSetup.h"
#include "CParagraphFormat.h"
#include "CRange.h"
#include "CSelection.h"
#include "CTables0.h"
#include "CHyperlinks.h"
////实现的方法

int ErrorValue(int msg)
{
	if (msg==SUCCESS_VALUE)
	{
		return 1;
	}   
	else if (msg==ERROR_FAILED_VALUE)
	{
		return 0;
	}
	else{
		return 2;
	}
}

int Getkeyval(CString str, CString *key, CString *val)//, CString *str_doc)
{
	CString str_cut = str;	
	int count_key = 0;
	int count_val = 0;
	int node_num = 0;
	int doc_num = 0;

	while(strlen(str_cut))
	{
		if(strcmp(str_cut,"k(e}y") != 0)
		{
			count_key = str_cut.Find("k(e}y",0);
			count_val = str_cut.Find("v(a}l",0);
			key[node_num] = str_cut.Mid(count_key+5,count_val-5);
			str_cut = str_cut.Mid(count_val,strlen(str_cut));

			count_key = str_cut.Find("k(e}y",0);
			count_val = str_cut.Find("v(a}l",0);
			val[node_num] = str_cut.Mid(count_val+5, count_key-5);
			str_cut = str_cut.Mid(count_key,strlen(str_cut));

			//if (val[node_num].Find(s1) != -1)
			//{
			//	str_doc[doc_num] = val[node_num];
			//	doc_num = doc_num + 1;
			//}
			node_num= node_num + 1;
		}
		else
			break;
	}
	return (node_num);
}


int GetDocFile(const CString str, CString *str_doc)
{
	CString str_cut = str;	
	int count_key = 0;
	int count_val = 0;
	int doc_num = 0;

	CString s1=".doc";
	int sss = str.Find("k(e}y");

	if (str.Find("k(e}y") != -1)
	{
while(strlen(str_cut))
	{
		if(strcmp(str_cut,"k(e}y") != 0)
		{
			count_key = str_cut.Find("k(e}y",0);
			count_val = str_cut.Find("v(a}l",0);
			//key[node_num] = str_cut.Mid(count_key+5,count_val-5);
			str_cut = str_cut.Mid(count_val,strlen(str_cut));

			count_key = str_cut.Find("k(e}y",0);
			count_val = str_cut.Find("v(a}l",0);
			CString str_val = str_cut.Mid(count_val+5, count_key-5);
			str_cut = str_cut.Mid(count_key,strlen(str_cut));
			
			if (str_val.Find(s1) != -1)
			{
				str_doc[doc_num] = str_val;
				doc_num = doc_num + 1;
			}
		}
		else
			break;
	}
	}
	
	return (doc_num);
}

int InitializeListCtrl(CListCtrl *m_list,int id,int page)
{
	CRect rect; 
	int i,j,m,msg,num;
	int count =0;
	INDEX_NODE file;
	INDEX_NODE folder;
	INDEX_TABLE indextable;
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	CString pkey[MAX_DATA_NUM],pval[MAX_DATA_NUM];
	CString str1,str2;	
	m_list->GetClientRect(&rect); 	
	m_list->SetExtendedStyle(m_list->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
	m_list->DeleteAllItems();
	IMVL_LoadIndexTable(&indextable);		
	IMVL_GetNode(id, &folder);
	num = Getkeyval(folder.content,pkey,pval);
	for(i=0;i<num;i++)
	{
	    m_list->InsertColumn(i, pkey[i], LVCFMT_CENTER, rect.Width()/num, i);
	}

	for (i=0;i<indextable.num;i++)
	{
		if (indextable.index[i].iPID==id)
		{
			if (indextable.index[i].IsFolder!=1)
			{
				count++;
				if (count>=(page-1)*20+1&&count<=20*page)
				{
					int num1 = Getkeyval(indextable.index[i].content,key,val);
					str1 = val[0];		
												
					m_list->InsertItem(count-1,str1);		
					m_list->SetItemData(count-1,indextable.index[i].ID);

					for (j=1;j<num1;j++)
					{  
						str2 = val[j];					
						m_list->SetItemText(count-1, j, str2);											
						
					}
				}
			}
			
		}
	}	
	return 1;
		
}

int InitializeExcelList(CListCtrl* m_list,int id)
{
	CRect rect; 
	int i,j,msg,num;
	int count =0;
	INDEX_NODE file;
	INDEX_NODE folder;
	INDEX_TABLE indextable;
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	CString str1,str2;

	m_list->GetClientRect(&rect);   
		
	m_list->SetExtendedStyle(m_list->GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); 
	m_list->DeleteAllItems();
	int num1 = m_list->GetHeaderCtrl()->GetItemCount();
	for (int i=0;i<num1;i++)
	{
		m_list->DeleteColumn(0);
	}
	
	IMVL_LoadIndexTable(&indextable);	
	IMVL_GetNode(id, &folder);
	if (strcmp(folder.content, _T(""))==0)
	{
		return 2;
	} 
	else
	{
		num = Getkeyval(folder.content,key,val);
		for(i=0;i<num;i++)
		{
			m_list->InsertColumn(i, key[i], LVCFMT_CENTER, rect.Width()/num, i);
		}

		for (i=0;i<indextable.num;i++)
		{
			if (indextable.index[i].iPID==id)
			{
				if (indextable.index[i].IsFolder!=1)
				{
					count++;
					int num1 = Getkeyval(indextable.index[i].content,key,val);
					//str1 = val[0];	
					HtmlToTextblock(&val[0],&str1);
					m_list->InsertItem(count-1,str1);		
					m_list->SetItemData(count-1,indextable.index[i].ID);
					for (j=1;j<num1;j++)
					{ 						
						HtmlToTextblock(&val[j],&str2);
						m_list->SetItemText(count-1, j, str2);
					}
				}
			}
		}	
		return 1;
	}	

}

int InitializePropertyGrid(CMFCPropertyGridCtrl *m_property,int id)
{
	
	return 1;
}

int InitializeTreeCtrl(CTreeCtrl *m_tree,CImageList *m_imageList)
{
	INDEX_TABLE indextable;
	CFont TextFont;
	int i,j,m;
	HTREEITEM hRoot; 
	HTREEITEM hCataItem;  
	HTREEITEM hArtItem; 
	HTREEITEM hSubItem;
	m_tree->DeleteAllItems();
	TextFont.CreatePointFont(120,_T("微软雅黑"));

	//m_tree->SetFont(&TextFont);

	int msg=IMVL_LoadIndexTable(&indextable);
	if (msg!=SUCCESS_VALUE)
	{		
		return 0;
	} 
	else
	{	
		//CreateDirectory(".\\BackUp",NULL);
		//CopyFile(".\\Demo.mdb",".\\BackUp",TRUE);
		m_tree->SetImageList(m_imageList, TVSIL_NORMAL);
		//m_tree->SetFont(&TextFont);
		hRoot = m_tree->InsertItem(_T("目录"), 0, 0);
		hCataItem =m_tree->InsertItem(_T("日记"), 0, 0, hRoot, TVI_LAST);
		m_tree->SetItemData(hCataItem, 28);
		SortByMonth(m_tree, hCataItem);
		hCataItem =m_tree->InsertItem(_T("通讯录"), 0, 0, hRoot, TVI_LAST);
		m_tree->SetItemData(hCataItem, 27);
		SortByTag(m_tree,hCataItem, _T("专业"));
		m_tree->SetItemData(hRoot,1);		
		for (i=0;i<indextable.num;i++)
		{
			if (indextable.index[i].iPID==1&&indextable.index[i].ID!=27&&indextable.index[i].ID!=28)
			{				
				hCataItem = m_tree->InsertItem(indextable.index[i].name, 0, 0, hRoot, TVI_LAST);
				m_tree->SetItemData(hCataItem, indextable.index[i].ID);  
				for (j=0;j<indextable.num;j++)
				{
					if (indextable.index[j].iPID==indextable.index[i].ID)
					{
						if (indextable.index[j].IsFolder==1)
						{
							hArtItem = m_tree->InsertItem(indextable.index[j].name, 0, 0, hCataItem, TVI_LAST);
							m_tree->SetItemData(hArtItem, indextable.index[j].ID); 
							for (m=0; m<indextable.num;m++)
							{
								if (indextable.index[m].iPID==indextable.index[j].ID)
								{
									hSubItem=m_tree->InsertItem(indextable.index[m].name, 1, 1, hArtItem, TVI_LAST);
									m_tree->SetItemData(hSubItem, indextable.index[m].ID); 
								}
							}
						} 
						else if (indextable.index[i].iPID!=27&&indextable.index[i].iPID!=28)						
						{
							hArtItem = m_tree->InsertItem(indextable.index[j].name, 1, 1, hCataItem, TVI_LAST);
							m_tree->SetItemData(hArtItem, indextable.index[j].ID); 

						}
					}
				}
			}

		}
		//m_webTree.DeleteAllItems(); 
		m_tree->Expand(hRoot,TVE_EXPAND);
		HTREEITEM hCataItem = m_tree->GetChildItem(hRoot);
		//while (hCataItem!=NULL)
		//{
		//	m_tree->Expand(hCataItem,TVE_EXPAND);//展开树形结构
		//	hCataItem = m_tree->GetNextSiblingItem(hCataItem);
		//}
		return 1;
	}
}

int SaveListCtrlAsFolder(const CListCtrl *m_list,int id)
{
	INDEX_NODE foldernode,oldfoldernode;
	INDEX_TABLE index;
	IMVL_LoadIndexTable(&index);
	CString str,str1,str2;
	str = _T("");
	int i,j,isempty=0;	
	int imagecount=0;
	int filecount=0;
	IMVL_GetNode(id, &oldfoldernode);
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	int num1 = Getkeyval(oldfoldernode.content,key,val);
	int num=m_list->GetItemCount();

	//读取content   可单独抽象出来
	for (i=0;i<num;i++)
	{
		str1=m_list->GetItemText(i,0);
		str2=m_list->GetItemText(i,1);
		if (str1==_T("")||str2==_T(""))
		{			
			return 2;			
		} 
		else
		{
			str = str+_T("k(e}y")+str1;			
			str=str+_T("v(a}l")+str2;
			if (strcmp(str2,_T("图片"))==0)
			{
				imagecount++;
			}
			else if (strcmp(str2,_T("文档"))==0||strcmp(str2,_T("附件"))==0)
			{
				filecount++;
			}
		}	

	}
	if (imagecount>20)
	{
		return 4;
	}
	else if (filecount>30)
	{
		return 5;
	}
	str=str+_T("k(e}y");
	foldernode.iPID=oldfoldernode.iPID;
	strcpy_s(foldernode.name,oldfoldernode.name);
	foldernode.ID=oldfoldernode.ID;
	if (strlen(str)>1300)
	{
		return 3;
	} 	
	strcpy_s(foldernode.content,str);
	foldernode.IsFolder=1;
	CString time;
	GetCurrTime(&time);
	strcpy_s(foldernode.modifyTime,time);
	strcpy_s(foldernode.createTime,oldfoldernode.createTime);
	int msg=IMVL_Update(&foldernode);	

	//级联修改属性    可抽取出来
	CString savestr,savestr1;
	if(num>num1)
	{
		for (i=num1;i<num;i++)
		{
			str1=m_list->GetItemText(i,0);
			str2=m_list->GetItemText(i,1);
			if (str1==_T("")||str2==_T(""))
			{			
				return 2;			
			} 
			else
		   {
			   savestr = savestr+_T("k(e}y")+str1;
			   savestr1 = savestr1+_T("k(e}y")+str1;
			   savestr=savestr+_T("v(a}l")+str2;
			   savestr1=savestr1+_T("v(a}l")+_T("");
		   }	
	   }
	
	   for (i=0;i<index.num;i++)
	   {
		    CString addstr;
		    if (index.index[i].iPID == id)
		    {
			    if (index.index[i].IsFolder == 1)
			      {
					  addstr = index.index[i].content;
					  GetStrKeyVal(&addstr,savestr,num1);
					  if (strcmp(index.index[i].content,_T(""))==0)
					  {
						  addstr=addstr+_T("k(e}y");
					  }	
				   
					strcpy_s(index.index[i].content ,addstr);
					IMVL_Update(&index.index[i]);
				    for (j=0;j<index.num;j++)
				    {
					   if (index.index[j].iPID == index.index[i].ID)
					   {
						   addstr = index.index[j].content;
						   GetStrKeyVal(&addstr,savestr1,num1);
						   if (strcmp(index.index[j].content,_T(""))==0)
						   {
							   addstr=addstr+_T("k(e}y");
						   }	
						   strcpy_s(index.index[j].content ,addstr);
						   IMVL_Update(&index.index[j]);
					   }
				    }
			     } 
			    else
			    {
					addstr = index.index[i].content;
					GetStrKeyVal(&addstr,savestr1,num1);
					if (strcmp(index.index[i].content,_T(""))==0)
					{
						addstr=addstr+_T("k(e}y");
					}	
					strcpy_s(index.index[i].content ,addstr);
					IMVL_Update(&index.index[i]);
				}
		    } 		
	    }
	}
	
	if (msg!=SUCCESS_VALUE)
	{
		return 0;
	} 
	else
	{
		return 1;
	}
}

int SaveListCtrlAsFile(const CListCtrl *m_list,int id)
{
	int i,j,num;	
	CString str1,str2;		
	INDEX_NODE file;
	INDEX_NODE folder;
	CString key[MAX_DATA_NUM],val[MAX_DATA_NUM];
	IMVL_GetNode(id,&folder);
	num=m_list->GetItemCount();
	for (i=0;i<num;i++)
	{	
		if (m_list->GetItemText(i,0).IsEmpty()==1)
			{
				return 2;
			}
		CString str;
		if (m_list->GetItemText(i,0).GetLength()>500)
		{
			return 3;
		}
		strcpy_s(file.name,m_list->GetItemText(i,0));
		int keynum = Getkeyval(folder.content,key,val);
		for (j=0;j<keynum;j++)
		{			
			str2 = key[j];
			str = str + _T("k(e}y")+str2;
			if (m_list->GetItemText(i,j).GetLength()>500)
			{
				return 3;
			}
			str1=m_list->GetItemText(i,j);
			if(strcmp(val[j],_T("图片"))==0)
			{
				CString save;
				int msg = FileSave(str1,&save,0);
				str1 = save;
			}
			else if (strcmp(val[j],_T("文档"))==0)
			{
				CString save;
				int msg = FileSave(str1,&save,1);
				str1 = save;
			}
			else if (strcmp(val[j],_T("附件"))==0)
			{
				CString save;
				int msg = FileSave(str1,&save,2);
				str1 = save;
			}
			str = str + _T("v(a}l")+str1;
		}
		str = str+_T("k(e}y");
		strcpy_s(file.content,str);
		if (strlen(str)>1300)
		{
			return 3;
		}
		file.IsFolder=0;
		int msg = IMVL_Create(id,&file);
		if (msg!=SUCCESS_VALUE)
		{
			return 0;
		}
	}
	return 1;
}


int InitializeTreeCtrlHead(CListCtrl *m_list)
{
	CRect rect1;
	m_list->DeleteAllItems();
	int num1 = m_list->GetHeaderCtrl()->GetItemCount();
	for (int i=0;i<num1;i++)
	{
		m_list->DeleteColumn(0);
	}
	m_list->GetClientRect(&rect1); 
	m_list->SetExtendedStyle(m_list->GetExtendedStyle() | LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES );  
	//m_list->SetFont(&TextFont);	
	m_list->InsertColumn(0, _T("名称"), LVCFMT_CENTER, rect1.Width()/4, 0);   
	m_list->InsertColumn(1, _T("类型"), LVCFMT_CENTER, rect1.Width()/4, 1); 
	m_list->InsertColumn(2, _T("修改时间"), LVCFMT_CENTER, rect1.Width()/4, 2);
	m_list->InsertColumn(3, _T("创建时间"), LVCFMT_CENTER, rect1.Width()/4, 3);
	//m_list->GetHeaderCtrl()->EnableWindow(FALSE);
	
	return 1;
}

void SetHtml(CString *val1, CString *val, CString *key, CString headstr, CString htmlname, int node_num)
{
	ifstream infilebe(htmlname+"/html/begin.txt");
	ifstream infileend(htmlname+"/html/end.txt");
	CString htmlSave = htmlname+_T("/html/MFCHtml.htm");
	ofstream outfile(htmlSave);

	string temp;
	while(getline(infilebe,temp))
	{
		outfile<<temp<<endl ;

	}
	infilebe.close();
	outfile<<"<h3><center><b>"<<"<font size=\"5\">"<<headstr<<"</font>"<<"</b><center></h3>"<<endl;
	outfile<<"<TABLE align="<<"left"<<">"<<endl;
	for(int i = 0; i<node_num; i++)
	{
		if(strcmp(val1[i],_T("图片")) == 0)
		{
			outfile<<"<tr>"<<endl;
			outfile<<"<td><p style="<<"'font-size:120%'"<<">&nbsp&nbsp"<<key[i]<<"</p></td>"<<endl;
			outfile<<"</tr>"<<endl;

			outfile<<"<tr>"<<endl;
			outfile<<"<td>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<img src= "<<exe_path + "\\image\\"+val[i]<<" width="<<"270"<<"height="<<"180"<<"></td>"<<endl;
			outfile<<"</tr>"<<endl;	
		}
		else if (strcmp(val1[i],_T("文档")) == 0||strcmp(val1[i],_T("附件")) == 0)
		{
			//<a href="C:\Users\Administrator\Desktop\意见汇总.doc" type="application/ms-word">打开word </a>
			CString str ;
			CString msgstr ="鼠标悬停时显示";
			GetFileName(val[i],&str);
			outfile<<"<tr>"<<endl;
			outfile<<"<td><p style="<<"""font-size:120%"""<<">&nbsp&nbsp"<<key[i]<<"</p></td>"<<endl;
			outfile<<"</tr>"<<endl;

			outfile<<"<tr>"<<endl;
			outfile<<"<td>&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<a href="<<exe_path+"\\attachment\\"+val[i]<<" title = "<<msgstr<<"  type="<<"application/ms-word"<<">"<<str<<" </a>"<<"</td>"<<endl;
			
			outfile<<"</tr>"<<endl;	
		}
		else 
		{
			outfile<<"<tr>"<<endl;
			outfile<<"<td><p style="<<"""font-size:120%"""<<">&nbsp&nbsp"<<key[i]<<"</p></td>"<<endl;
			outfile<<"</tr>"<<endl;
			outfile<<"<tr>"<<endl;
			outfile<<"<td>";//<<&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp"<<val[i]<<"</p></td>"<<endl;
				
			CString val_str = val[i];
			int count = 0;
			while(val[i].Find("<br>") != -1)
			{   int pos = val[i].Find("<br>");
				CString str = val[i].Mid(0, pos+4);
				val[i] = val[i].Mid(pos+4, strlen(val[i]));
				if(count == 0)
				{
					outfile<<"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp"<<str;
				}
				else
				{
					outfile<<"&nbsp&nbsp&nbsp&nbsp&nbsp"<<str;
				}
				count = count + 1;
			}
			if(val_str.Find("<br>") == -1 && strlen(val_str) != 0)
			{
				outfile<<"&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp"<<val[i];
			}
			else
			{
				outfile<<"<br> &nbsp&nbsp&nbsp&nbsp</br>";
			}
			
			outfile<<"</td>"<<"</tr>"<<endl;
		}		
	}
	while(getline(infileend,temp))
	{
		outfile<<temp<<endl ;

	}
	infileend.close();
	outfile.close();

}

void SetPicHtml(CString picturepath,CString htmlname)
{
	ifstream infilebe("begin.txt");
	ifstream infileend("end.txt");

	ofstream outfile(htmlname);
	string temp;
	while(getline(infilebe,temp))
	{
		outfile<<temp<<endl ;

	}
	infilebe.close();
	
	
	
	outfile<<"<img src= "<<picturepath<<" width="<<"225"<<"height="<<"145"<<">"<<endl;
	

	while(getline(infileend,temp))
	{
		outfile<<temp<<endl ;

	}
	infileend.close();
	outfile.close();
}


//导出word
void Exportword(CString strFileName, CString *val1, CString *val, CString *key, CString headstr, int node_num)
{
	COleVariant vTrue((short)TRUE),
		vFalse((short)FALSE),
		vOpt((long)DISP_E_PARAMNOTFOUND, VT_ERROR);

	CApplication oWordApp;	//开始一个新的Microsoft Word 2000实例
	if (!oWordApp.CreateDispatch(_T("Word.Application"), NULL)){
		AfxMessageBox(_T("服务创建失败，请确定已经安装了Office 2000或以上版本."), MB_OK | MB_SETFOREGROUND);
		return;
	}

	CDocuments oDocs;    //创建一个新的word文档
	CDocument0 oDoc;
	oDocs = oWordApp.get_Documents();
	oDoc = oDocs.Add(vOpt, vOpt, vOpt, vOpt);//如果是word 98，则应该带两个参数，如oDocs.Add(vOpt, vOpt)  

	CDocument0 curDoc = oWordApp.get_ActiveDocument();
	CPageSetup p = curDoc.get_PageSetup();
	p.put_LeftMargin(54);
	p.put_RightMargin(54);
	p.put_TopMargin(72);
	p.put_BottomMargin(72);

	CString cstr1, cstr2, cstr3,cstr4;

	CSelection oSel;          //把文本添加到word文档
	oSel = oWordApp.get_Selection();
	CFont0 f=oSel.get_Font();
	f.put_Size(22);//宋体2号

	setlocale(LC_ALL, "chs");//以汉字显示
	CParagraphFormat format = oSel.get_ParagraphFormat();
	format.put_Alignment(1);
	//抬头信息
	f.put_Name(_T("黑体"));


	oSel.TypeText(headstr);//显示标题 //this->GetDlgItem(IDC_nameEDIT1)->GetWindowText(cstr1);
	oSel.TypeParagraph();

	//oSel.TypeText(_T(""));//空一行
	//oSel.TypeParagraph();

	for(int i = 0;i< node_num;i++)
	{	  
		if(strcmp(val1[i],_T("图片")) == 0)
		{
			f.put_Size(18);//3号字体
			format.put_Alignment(3);
			f.put_Name(_T("宋体"));
			//key[i]->GetWindowText(cstr2);
			oSel.TypeText(key[i]);
			oSel.TypeParagraph();

			char pFileName[MAX_PATH];   
			int nPos = GetCurrentDirectory( MAX_PATH, pFileName);   
			CString csFullPath(pFileName); 

			//CString str_picture = val[i];////_T("F:\\bmp\\u31.bmp");//
			//if (val[i].IsEmpty())
			//{
			//	oSel.TypeParagraph();
			//} 
			if (!val[i].IsEmpty())
			{
				CString img_str = exe_path + "\\image\\"+val[i];
				CnlineShapes nline_shapes = oSel.get_InlineShapes();
				CnlineShape nline_shape = nline_shapes.AddPicture(img_str,vFalse, vTrue, vOpt);

				
			}
            oSel.TypeParagraph();
		}
		else if((strcmp(val1[i],_T("文档")) == 0)||(strcmp(val1[i],_T("附件")) == 0))
		{
			f.put_Size(18);//3号字体
			format.put_Alignment(3);
			f.put_Name(_T("宋体"));
			oSel.TypeText(key[i]);
			oSel.TypeParagraph();

			f.put_Size(16);  //小3号字体
			format.put_Alignment(3);  
			f.put_Name(_T("宋体"));
			CString cstr4 = _T("  ");
			oSel.TypeText(cstr4);

			if (!val[i].IsEmpty())
			{				
				CHyperlinks m_hyperlink;
				m_hyperlink = oSel.get_Hyperlinks();
				CString file_str = exe_path + "\\attachment\\"+val[i];
				m_hyperlink.Add(oSel.get_Range(),COleVariant(file_str), vOpt,vOpt,vOpt,vOpt);				
			} 			
			oSel.TypeParagraph();
		}
		else if((strcmp(val1[i],_T("文本块")) == 0))
		{
			f.put_Size(18);//3号字体
			format.put_Alignment(3);
			f.put_Name(_T("宋体"));
			oSel.TypeText(key[i]);
			oSel.TypeParagraph();

			f.put_Size(16);  //小3号字体
			format.put_Alignment(3);  
			f.put_Name(_T("宋体"));
			CString cstr4 = _T("  ");
            //cstr3 = cstr4 + val[i];
			CString textstr;
			HtmlToWord(&val[i] ,&textstr);
			cstr3 = cstr4 + textstr;
			
			oSel.TypeText(cstr3);
			if (val[i].IsEmpty())
			{
				oSel.TypeParagraph();
			}
		}
		else
		{
			f.put_Size(18);//3号字体
			format.put_Alignment(3);
			f.put_Name(_T("宋体"));
			oSel.TypeText(key[i]);
			oSel.TypeParagraph();

			f.put_Size(16);  //小3号字体
			format.put_Alignment(3);  
			f.put_Name(_T("宋体"));
			CString cstr4 = _T("  ");
			cstr3 = cstr4 + val[i];
			oSel.TypeText(cstr3);
			oSel.TypeParagraph();

		}
	}
	//oSel.TypeParagraph();

	//保存word文档
	CDocument0 oActiveDoc; 
	oActiveDoc = oWordApp.get_ActiveDocument();
	oActiveDoc.SaveAs(COleVariant(strFileName)
		,COleVariant((short)0),vFalse, COleVariant(_T(""))
		, vTrue, COleVariant(_T(""))
		,vFalse, vFalse, vFalse, vFalse, vFalse, vFalse, vFalse, vFalse, vFalse, vFalse);

	
oDoc.Close(&vFalse,&vOpt,&vOpt);
	oWordApp.Quit(vOpt, vOpt, vOpt);
	oWordApp.ReleaseDispatch();
oSel.ReleaseDispatch();
	oDoc.ReleaseDispatch();
	oDocs.ReleaseDispatch();
	

	
	//oActiveDoc.RecheckSmartTags();


	

}


	void GetStrKeyVal(CString *strfile, CString addstr, int pos)
	{
		int findnum = 0;
		for(int i = 0; i < pos; i++)
		{
			findnum = strfile->Find("k(e}y",findnum+1);
		}
		strfile->Insert(findnum,addstr);

	}


	int  GetSrollMaxHight(CString* val)
	{
		int i = 0;
		int maxlength = 0;
		while (!val[i].IsEmpty())
		{
			if (strcmp(val[i],_T("文本")) == 0) //strcmp(val[i],_T("文本块")) == 0)
			{
				maxlength = maxlength + 70;
			} 
			else if(strcmp(val[i],_T("文本块")) == 0)
			{
				maxlength = maxlength + 185;
			}
			else if(strcmp(val[i],_T("日期"))==0)
			{
				maxlength = maxlength + 80;
			}
			else if(strcmp(val[i],_T("附件"))==0||strcmp(val[i],_T("文档"))==0)
			{
				maxlength = maxlength + 75;
			}
			else if (strcmp(val[i],_T("图片"))==0)
			{
				maxlength = maxlength + 230;
			}
			i++;
		}

		return maxlength;
	}


int SetDiaryHtml(CString *diary_val, CString html_name)
{
	ifstream infilebe(html_name+"\\html\\diary_begin.txt");
	ifstream infilemid(html_name+"\\html\\diary_mid.txt");
	ifstream infileend(html_name+"\\html\\diary_end.txt");
	CString htmlSave = html_name+_T("\\html\\DiaryHtml.htm");
	ofstream outfile(htmlSave);

	string temp;
	while(getline(infilebe,temp))
	{
		outfile<<temp<<endl ;

	}
	infilebe.close();
	CString str1 = diary_val[1];
	CString str2 = diary_val[0];
	CString str3 = diary_val[2];

	outfile<<"<div class="<<"\""<<"box_title"<<"\""<<">"<<endl;
	outfile<<"<h1 id=\"title\">"<<str1<<"</h1>"<<endl;
	outfile<<"<input type=\"text\" id=\"txt_head\" size=\"10\">"<<endl;
	outfile<<"</div>"<<endl;
	outfile<<"<h5 id = \"time\" align=\"center\">"<<str2<<"</h5>"<<endl;
	outfile<<"<div class=\"box_content\">"<<endl;


	outfile<<"<p id=\"content\">";//<<str3<<"</p>"<<endl;

	//int count = 0;
	//CString outfilestr;
	//while(str3.Find("br>") != -1)
	//{
	//	int pos = str3.Find("<br>");
	//	CString str = str3.Mid(0, pos+4);
	//	str3 = str3.Mid(pos+4, strlen(str3));
	//	outfilestr += str;
	//	
	//}
	//outfilestr += str3.Mid(0, strlen(str3));

	//if(strlen(outfilestr) != 0)
	//{
	outfile<<str3<<"</p>"<<endl;



	outfile<<"<textarea id=\"txt_content\" rows=\"25\" cols=\"135\"></textarea>"<<endl;
    outfile<<"</div>"<<endl;

	while(getline(infilemid,temp))
	{
		outfile<<temp<<endl ;
	}
	html_name.Replace("\\", "//");
	outfile<<"var f= fso.createtextfile("<<"\""<<html_name<<"//html//日记//日记.txt\""<<",1);";
	while(getline(infileend,temp))
	{
		outfile<<temp<<endl ;

	}
	infileend.close();
	outfile.close();
	return 0;

	
}

int GetTxtStr(CString *str, CString path)
{   
	ifstream infilebe(path+"\\html\\日记\\日记.txt");
	string temp="";
	string outfile="";
	while(getline(infilebe,temp))
	{
		outfile = outfile + temp;
	}

		CString str1;
		str1 = outfile.c_str();
		//str1.Format("%s", outfile);
		*str = str1;

		//system("del ./html/日记/日记.txt");
return 0;
}