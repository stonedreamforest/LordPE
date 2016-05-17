// MyResources.cpp : 实现文件
//

#include "stdafx.h"
#include "简易PE.h"
#include "MyResources.h"
#include "afxdialogex.h"
#include "vector"
using namespace std;
typedef struct _RESTHIRDINFO
{
	DWORD Rva;
	DWORD Offset;
	DWORD Size;
}RESTHIRDINFO,*PRESTHIRDINFO;

typedef struct _RESSENCONDINFO
{
	DWORD NameIsString;
	DWORD ReSize2;
}RESSENCONDINFO,*PRESSENCONDINFO;

vector<RESTHIRDINFO> m_VecResthdInfo[20];
vector<RESSENCONDINFO> m_VecResSedInfo;
vector<HTREEITEM> m_VecHtreeItem;
// MyResources 对话框

IMPLEMENT_DYNAMIC(MyResources, CDialogEx)

MyResources::MyResources(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyResources::IDD, pParent)
	, m_Name(_T(""))
	, m_Id(_T(""))
	, m_Name2(_T(""))
	, m_Id2(_T(""))
	, m_Rva(_T(""))
	, m_Offset(_T(""))
	, m_Size(_T(""))
{

}

MyResources::~MyResources()
{
}

void MyResources::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ResTreeList);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT4, m_Id);
	DDX_Text(pDX, IDC_EDIT5, m_Name2);
	DDX_Text(pDX, IDC_EDIT6, m_Id2);
	DDX_Text(pDX, IDC_EDIT7, m_Rva);
	DDX_Text(pDX, IDC_EDIT8, m_Offset);
	DDX_Text(pDX, IDC_EDIT9, m_Size);
}


BEGIN_MESSAGE_MAP(MyResources, CDialogEx)
//	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &MyResources::OnNMClickTree)
END_MESSAGE_MAP()


// MyResources 消息处理程序


BOOL MyResources::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_ResTreeList.ModifyStyle(NULL,TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT);
	//for (int i=0;i<2;i++)
	//{
	//	HTREEITEM hItem = m_ResTreeList.InsertItem(L"root",NULL,NULL);///root就是节点的标题
	//
	//for (int i=0;i<4;i++)
	//	{
	//		HTREEITEM hSubItem = m_ResTreeList.InsertItem(L"item",NULL,NULL,hItem);
	//		m_ResTreeList.SetItemData(hSubItem, i);
	///*	for (j=0;j<3;j++)
	//	{
	//		m_ResTreeList.InsertItem(L"subitem",NULL,NULL,hSubItem);
	//	}**/
	//	}
	//}
	ShowResourcesInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
}

void MyResources::ShowResourcesInfo()
{
	RESSENCONDINFO ResSendInfo;
	RESTHIRDINFO ResThirdInfo;
	AnalPE.pDatD=&(	AnalPE.pOptH->DataDirectory[2]);
	PIMAGE_RESOURCE_DIRECTORY pResD=(PIMAGE_RESOURCE_DIRECTORY)(AnalPE.buf+	AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	DWORD ReSize=pResD->NumberOfIdEntries+pResD->NumberOfNamedEntries;
	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE=(PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD+sizeof(IMAGE_RESOURCE_DIRECTORY));
	//AnalPE.OutPutPeInfo(m_Name,pResDE->NameIsString);
	//AnalPE.OutPutPeInfo(m_Id,ReSize);
	//另一种写法
	m_Name.Format(L"%04X",pResDE->NameIsString);
	m_Id.Format(L"%04X",ReSize);
	HTREEITEM hItem ;
	HTREEITEM hSubItem ;
	//HTREEITEM hThirdItem;
	//此处也可使用std::map      喜欢什么用什么吧 

	CString str;
	for (DWORD FirstOrder=0;FirstOrder<ReSize;FirstOrder++)
	{
		//第一层 假如是字符串标识
		if (pResDE->NameIsString==1)
		{
			PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU=(PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD+pResDE->NameOffset);
			//printf_s("资源类型名：%s",pREsDStrU->NameString);
			hItem = m_ResTreeList.InsertItem(pREsDStrU->NameString,NULL,NULL);///root就是节点的标题
		}
		//假如是一直类型 用序号作为标识
		else
		{
			switch (pResDE->Name)
			{
			case 0x1:
				//printf_s("第一层：%s\n",ResourceName[0]);
				hItem = m_ResTreeList.InsertItem(L"鼠标指针",NULL,NULL);
				break;		    
			case 0x2:		    
				//printf_s("第一层：%s\n",ResourceName[1]);
				hItem = m_ResTreeList.InsertItem(L"位图",NULL,NULL);
				break;		    
			case 0x3:		    
				//printf_s("第一层：%s\n",ResourceName[2]);
				hItem = m_ResTreeList.InsertItem(L"图标",NULL,NULL);
				break;		    
			case 0x4:		    
				//printf_s("第一层：%s\n",ResourceName[3]);
				hItem = m_ResTreeList.InsertItem(L"菜单",NULL,NULL);
				break;		    
			case 0x5:		    
				//printf_s("第一层：%s\n",ResourceName[4]);
				hItem = m_ResTreeList.InsertItem(L"对话框",NULL,NULL);
				break;		    
			case 0x6:		    
				//printf_s("第一层：%s\n",ResourceName[5]);
				hItem = m_ResTreeList.InsertItem(L"字符串列表",NULL,NULL);
				break;		    
			case 0x7:		    
				//printf_s("第一层：%s\n",ResourceName[6]);
				hItem = m_ResTreeList.InsertItem(L"字体目录",NULL,NULL);
				break;		    
			case 0x8:		    
				//printf_s("第一层：%s\n",ResourceName[7]);
				hItem = m_ResTreeList.InsertItem(L"字体",NULL,NULL);
				break;		    
			case 0x9:		    
				//printf_s("第一层：%s\n",ResourceName[8]);
				hItem = m_ResTreeList.InsertItem(L"快捷键",NULL,NULL);
				break;		    
			case 0xA:		    
				//printf_s("第一层：%s\n",ResourceName[9]);
				hItem = m_ResTreeList.InsertItem(L"非格式化资源",NULL,NULL);
				break;		    
			case 0xB:		    
				//printf_s("第一层：%s\n",ResourceName[10]);
				hItem = m_ResTreeList.InsertItem(L"消息列表",NULL,NULL);
				break;		    
			case 0xC:		    
				//printf_s("第一层：%s\n",ResourceName[11]);
				hItem = m_ResTreeList.InsertItem(L"鼠标指针组",NULL,NULL);
				break;		    
			case 0xE:		    
				//printf_s("第一层：%s\n",ResourceName[12]);
				hItem = m_ResTreeList.InsertItem(L"图标组",NULL,NULL);
				break;		    
			case 0x10:		    
				//printf_s("第一层：%s\n",ResourceName[13]);
				hItem = m_ResTreeList.InsertItem(L"版本信息",NULL,NULL);
				break;		    
			default:
				//printf_s("第一层：%d\n",pResDE->Name);
				str.Format(L"%d",pResDE->Name);
				hItem = m_ResTreeList.InsertItem(str,NULL,NULL);
				break;
			}
		}
		//找第二层 注意OFFEST 是相对于pResD也就是资源开始位置的偏移
		PIMAGE_RESOURCE_DIRECTORY pResD2=(PIMAGE_RESOURCE_DIRECTORY)((long)pResD+pResDE->OffsetToDirectory);
		DWORD ReSize2=pResD2->NumberOfIdEntries+pResD2->NumberOfNamedEntries;
		PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE2=(PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD2+sizeof(IMAGE_RESOURCE_DIRECTORY));

		m_ResTreeList.SetItemData(hItem, FirstOrder);
		//printf_s("第er层[名称条目]->：%04X   ",pResDE2->NameIsString);	
		//AnalPE.OutPutPeInfo(m_Name2,pResDE2->NameIsString);
		ResSendInfo.NameIsString=pResD2->NumberOfNamedEntries;
		ResSendInfo.ReSize2=pResD2->NumberOfIdEntries;
		m_VecResSedInfo.push_back(ResSendInfo);
		//printf_s("第er层[ID条目]->：%04X   \n",pResDE2->Id);
		//AnalPE.OutPutPeInfo(m_Id2,ReSize2);	

		DWORD SecondOrder=0;
		for (;SecondOrder<ReSize2;SecondOrder++)
		{
			if (pResDE2->DataIsDirectory==1)
			{
				//输出第二层资源的标识看是数字还是字符串
				if (pResDE2->NameIsString==1)
				{
					PIMAGE_RESOURCE_DIR_STRING_U pREsDStrU2=(PIMAGE_RESOURCE_DIR_STRING_U)((long)pResD+pResDE2->NameOffset);
					//输出资源类型名字
					//printf("第二层->资源类型名：%ls   ",pREsDStrU2->NameString);
					hSubItem = m_ResTreeList.InsertItem(pREsDStrU2->NameString,NULL,NULL,hItem);
					m_ResTreeList.SetItemData(hSubItem, SecondOrder);
				}
				else
				{
					//printf_s("第二层->资源类型名ID：%d   ",pResDE2->Id);	
					str.Format(L"%d",pResDE2->Id);
					hSubItem = m_ResTreeList.InsertItem(str,NULL,NULL,hItem);
					m_ResTreeList.SetItemData(hSubItem, SecondOrder);
				}
				//解析第三层 
				PIMAGE_RESOURCE_DIRECTORY pResD3=(PIMAGE_RESOURCE_DIRECTORY)((long)pResD+pResDE2->OffsetToDirectory);
				PIMAGE_RESOURCE_DIRECTORY_ENTRY pResDE3=(PIMAGE_RESOURCE_DIRECTORY_ENTRY)((long)pResD3+sizeof(IMAGE_RESOURCE_DIRECTORY));
				PIMAGE_RESOURCE_DATA_ENTRY pResDataE=(PIMAGE_RESOURCE_DATA_ENTRY)((long)pResD+pResDE3->OffsetToData);
				//printf_s("第三层->RVA：%08X   ",pResDataE->OffsetToData);  
				//AnalPE.OutPutPeInfo()
				//根据第一层 也就是父节点 区分 
				ResThirdInfo.Rva=pResDataE->OffsetToData;
				ResThirdInfo.Offset=(AnalPE.CalcOffset(pResDataE->OffsetToData));
				ResThirdInfo.Size=pResDataE->Size;
				m_VecResthdInfo[FirstOrder].push_back(ResThirdInfo);
			//	str.Format(L"%08X",pResDataE->OffsetToData);
			//	m_ResTreeList.InsertItem(str,NULL,NULL,hSubItem);
			////	printf_s("第三层->偏移：%08X   ",(AnalPE.CalcOffset(pResDataE->OffsetToData)));
			//	str.Format(L"%08X",(AnalPE.CalcOffset(pResDataE->OffsetToData)));
			//	m_ResTreeList.InsertItem(str,NULL,NULL,hSubItem);
			////	printf_s("第三层->大小：%08X\n",pResDataE->Size);
			//	str.Format(L"%08X",pResDataE->Size);
			//	m_ResTreeList.InsertItem(str,NULL,NULL,hSubItem);

			}
			else
			{
				break;
			}
			pResDE2++;
		}
		//保存父节点的句柄
		m_VecHtreeItem.push_back(hItem);
		pResDE++;
	}
	m_Name2.Format(L"%04X",m_VecResSedInfo[0].NameIsString);
	m_Id2.Format(L"%04X",m_VecResSedInfo[0].ReSize2);
	UpdateData(FALSE);
}


//void MyResources::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值m_ResTreeList
//	m_ResTreeList.SelectItem()
//	//CTreeCtrl&  LeftTree=AfxGetApp()->GetTreeCtrl();
//	//UINT flags=TVHT_ONITEM;
//	//HTREEITEM hTreeItem=LeftTree.HitTest(point,&flags);
//	//CString text=LeftTree.GetItemText(hTreeItem);
//	//afxDump << text << "\n";
//	////	CTreeView::OnRButtonDown(nFlags, point);
//	//CDialogEx::OnLButtonDown(nFlags, point);
//}

void MyResources::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	 //获取当前鼠标点击消息的坐标点
	CPoint pt = GetCurrentMessage()->pt;  
	 //将鼠标的屏幕坐标，转换成树形控件的客户区坐标
	m_ResTreeList.ScreenToClient(&pt);  
	UINT uFlags = 0;
	HTREEITEM hItem = m_ResTreeList.HitTest(pt, &uFlags);
	//获得父节点句柄
	HTREEITEM RootHItem=m_ResTreeList.GetParentItem(hItem);
	int RootTreePos;
	
	//找到对应父节点位置
	for (UINT i=0;i<m_VecHtreeItem.size();i++)
	{
		if (RootHItem==NULL)
		{
			break;
		}
		if (RootHItem==m_VecHtreeItem[i])
		{
			RootTreePos=i;
			break;
		}
		//最后一个
		RootTreePos=i;
	}
	//m_ResTreeList.getn
	//如果点击的位置是在节点位置上面
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		//得到点中的序号
		m_ResTreeList.SelectItem(hItem);
		int nDat = m_ResTreeList.GetItemData(hItem);
		//判断是父节点还是子节点
		if (RootHItem==NULL)
		{
			m_Name2.Format(L"%04X",m_VecResSedInfo[nDat].NameIsString);
			m_Id2.Format(L"%04X",m_VecResSedInfo[nDat].ReSize2);
		}
		else
		{
			AnalPE.OutPutPeInfo(m_Rva,m_VecResthdInfo[RootTreePos][nDat].Rva);
			AnalPE.OutPutPeInfo(m_Offset,m_VecResthdInfo[RootTreePos][nDat].Offset);
			AnalPE.OutPutPeInfo(m_Size,	m_VecResthdInfo[RootTreePos][nDat].Size);
		}
	/*	if (hItem==m_VecHtreeItem[nDat])
		{
			m_Name2.Format(L"%04X",m_VecResSedInfo[nDat].NameIsString);
			m_Id2.Format(L"%04X",m_VecResSedInfo[nDat].ReSize2);
		}
		else
		{
			AnalPE.OutPutPeInfo(m_Rva,m_VecResthdInfo[RootTreePos][nDat].Rva);
			AnalPE.OutPutPeInfo(m_Offset,m_VecResthdInfo[RootTreePos][nDat].Offset);
			AnalPE.OutPutPeInfo(m_Size,	m_VecResthdInfo[RootTreePos][nDat].Size);
		}*/
		
	}
	UpdateData(FALSE);
}
