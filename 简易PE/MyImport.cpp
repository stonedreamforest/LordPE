// MyImport.cpp : 实现文件
//

#include "stdafx.h"
#include "简易PE.h"
#include "MyImport.h"
#include "afxdialogex.h"
#include "vector"
using namespace std;


vector<PIMAGE_IMPORT_DESCRIPTOR> m_VecImport;
// MyImport 对话框

IMPLEMENT_DYNAMIC(MyImport, CDialogEx)

MyImport::MyImport(CWnd* pParent /*=NULL*/)
	: CDialogEx(MyImport::IDD, pParent)
{

}

MyImport::~MyImport()
{
}

void MyImport::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_UpImport);
	DDX_Control(pDX, IDC_LIST2, m_DownImport);
}


BEGIN_MESSAGE_MAP(MyImport, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &MyImport::OnNMClickList)
//	ON_WM_CHAR()
END_MESSAGE_MAP()


// MyImport 消息处理程序


BOOL MyImport::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str[]={L"DLL名称",L"OriginalFirstThunk",L"日期时间标志",L"ForwarderChain",L"名称",L"FirstThunk"};
	CString str1[]={L"ThunkRVA",L"Thunk偏移",L"Thunk值",L"提示",L"API名称"};
	m_UpImport.SetExtendedStyle(m_UpImport.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);//可选中风格
	m_DownImport.SetExtendedStyle(m_DownImport.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	for (int i=0;i<sizeof(str)/sizeof(str[0]);i++)
	{
		m_UpImport.InsertColumn(i,str[i],LVCFMT_LEFT,67);
	}
	for (int i=0;i<sizeof(str1)/sizeof(str1[0]);i++)
	{
		m_DownImport.InsertColumn(i,str1[i],LVCFMT_LEFT,67);
	}
	ShowImportList();
	return TRUE;  // return TRUE unless you set the focus to a control

	// 异常: OCX 属性页应返回 FALSE
}



void MyImport::ShowImportList()
{
	//获取导入表
	PIMAGE_IMPORT_DESCRIPTOR  pImpD;
	AnalPE.pDatD=&(	AnalPE.pOptH->DataDirectory[1]);
	pImpD=(PIMAGE_IMPORT_DESCRIPTOR)((long)AnalPE.buf+AnalPE.CalcOffset(AnalPE.pDatD->VirtualAddress));
	//第一层循环 每个导入的DLL依次解析
	int i=0;
	CString str;
	while(pImpD->Name)
	{
		//DLL名称相关
		//printf_s("DLL名称：%s  ",(AnalPE.buf+AnalPE.CalcOffset(pImpD->Name)));
		CString str((AnalPE.buf+AnalPE.CalcOffset(pImpD->Name)));
		//m_UpImport.InsertItem(i,L"(AnalPE.buf+AnalPE.CalcOffset(pImpD->Name))");
		m_UpImport.InsertItem(i,str);
		
		//printf_s("INT(输入名称表)：%08X  ",pImpD->OriginalFirstThunk);
		str.Format(L"%08X",pImpD->OriginalFirstThunk);
		m_UpImport.SetItemText(i,1,str);
		//printf_s("日期时间标志：%08X  ",pImpD->TimeDateStamp);
		str.Format(L"%08X",pImpD->TimeDateStamp);
		m_UpImport.SetItemText(i,2,str);
	//	printf_s("ForwarderChain：%08X  ",pImpD->ForwarderChain);
		str.Format(L"%08X",pImpD->ForwarderChain);
		m_UpImport.SetItemText(i,3,str);
	//	printf_s("名称：%08X  ",pImpD->Name);
		str.Format(L"%08X",pImpD->Name);
		m_UpImport.SetItemText(i,4,str);
	//	printf_s("FirstThunk：%08X\n",pImpD->FirstThunk);
		str.Format(L"%08X",pImpD->FirstThunk);
		m_UpImport.SetItemText(i,5,str);
		m_VecImport.push_back(pImpD);
		i++;
		
		//system("pause");
		pImpD++;
	}
}


//void MyImport::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
//}

void MyImport::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	POSITION pos = m_UpImport.GetFirstSelectedItemPosition();
	int nIndex=(int)pos;
	if (pos == NULL)//判断是否为空
	{
		return;
	}
	//while(m_DownImport.DeleteColumn(0));
	m_DownImport.DeleteAllItems();
	//从获取的DLL导入函数地址表 IAT 计算偏移
	PIMAGE_THUNK_DATA32 pInt=(PIMAGE_THUNK_DATA32)(AnalPE.buf+AnalPE.CalcOffset(m_VecImport[nIndex-1]->FirstThunk));
	
	//循环解析导入地址表IAT
	int i=0;
	CString str;
	while(pInt->u1.Function)
	{

		DWORD ThunkOffest=AnalPE.CalcOffset(m_VecImport[nIndex-1]->OriginalFirstThunk);
		//判断最高位是否为1 不为1按名称导入
		if (!IMAGE_SNAP_BY_ORDINAL32(pInt->u1.Ordinal))
		{
			//找到函数序号名地址 并将其取出  
			//printf_s("ThunkRVA：%08X  ",m_VecImport[nIndex]->OriginalFirstThunk);
			str.Format(L"%08X",m_VecImport[nIndex-1]->OriginalFirstThunk);
			m_DownImport.InsertItem(i,str);
			//printf_s("Thunk偏移：%08X  ",ThunkOffest);
			str.Format(L"%08X",ThunkOffest);
			m_DownImport.SetItemText(i,1,str);
		//	printf_s("Thunk值：%08X  ",pInt->u1.AddressOfData);
			str.Format(L"%08X",pInt->u1.AddressOfData);
			m_DownImport.SetItemText(i,2,str);
			PIMAGE_IMPORT_BY_NAME pFunName=(PIMAGE_IMPORT_BY_NAME)(AnalPE.buf+AnalPE.CalcOffset(pInt->u1.AddressOfData));
		//	printf_s("提示：%04X  ",pFunName->Hint);
			str.Format(L"%04X",pFunName->Hint);
			m_DownImport.SetItemText(i,3,str);
		//	printf_s("API名称：%s\n",pFunName->Name);
			CString str(pFunName->Name);
			//str.Format(L"%s",pFunName->Name);
			m_DownImport.SetItemText(i,4,str);
			//每次偏移四个字节
			m_VecImport[nIndex-1]->OriginalFirstThunk+=4;
			ThunkOffest+=4;
		}
		else
		{
			//m_DownImport.DeleteColumn(0);
			
			////找到函数序号名地址 并将其取出  
			////	PIMAGE_IMPORT_BY_NAME pFunName=(PIMAGE_IMPORT_BY_NAME)(buf+CalcOffset(pInt->u1.AddressOfData,pNtH));
			////printf_s("ThunkRVA：%08X  ",m_VecImport[nIndex]->OriginalFirstThunk);
			str.Format(L"%08X",m_VecImport[nIndex-1]->OriginalFirstThunk);
			m_DownImport.InsertItem(i,str);
		//	printf_s("Thunk偏移：%08X  ",ThunkOffest);
			str.Format(L"%08X",ThunkOffest);
			m_DownImport.SetItemText(i,1,str);
		//	printf_s("Thunk值：%08X  ",pInt->u1.AddressOfData);
			str.Format(L"%08X",pInt->u1.AddressOfData);
			m_DownImport.SetItemText(i,2,str);
			//printf_s("提示：-  ");
			m_DownImport.SetItemText(i,3,L"-");
		//	printf_s("序号：%4xH  %4dD\n",pInt->u1.Ordinal&0x7fffffff,pInt->u1.Ordinal&0x7fffffff);
			CString str2;
			str2.Format(L"%4xH",pInt->u1.Ordinal&0x7fffffff);
			str.Format(L"%4dD",pInt->u1.Ordinal&0x7fffffff);
			m_DownImport.SetItemText(i,4,str2+L" "+str);
		}
		i++;
		pInt++;
	}
}
