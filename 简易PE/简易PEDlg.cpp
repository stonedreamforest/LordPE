
// 简易PEDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "简易PE.h"
#include "简易PEDlg.h"
#include "afxdialogex.h"
#include "MyCatalog.h"
#include "MyAreaTable.h"
#include "MyFileLocation.h"



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
END_MESSAGE_MAP()


// C简易PEDlg 对话框



C简易PEDlg::C简易PEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C简易PEDlg::IDD, pParent)
	
	, m_EntryPoint(_T(""))
	, m_ImageBase(_T(""))
	, m_SizeOfImage(_T(""))
	, m_BaseOfCode(_T(""))
	, m_BaseOfData(_T(""))
	, m_SectionAlignment(_T(""))
	, m_FileAlignment(_T(""))
	, m_Magic(_T(""))
	, m_Subsystem(_T(""))
	, m_NumberOfSections(_T(""))
	, m_TimeDateStamp(_T(""))
	, m_SizeOfHeaders(_T(""))
	, m_Characteristics(_T(""))
	, m_CheckSum(_T(""))
	, m_SizeOfOptionalHeader(_T(""))
	, m_NumberOfRvaAndSizes(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C简易PEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_EDIT1, m_EntryPoint);
	DDX_Text(pDX, IDC_EDIT1, m_EntryPoint);
	DDX_Text(pDX, IDC_EDIT2, m_ImageBase);
	DDX_Text(pDX, IDC_EDIT3, m_SizeOfImage);
	DDX_Text(pDX, IDC_EDIT4, m_BaseOfCode);
	DDX_Text(pDX, IDC_EDIT5, m_BaseOfData);
	DDX_Text(pDX, IDC_EDIT6, m_SectionAlignment);
	DDX_Text(pDX, IDC_EDIT7, m_FileAlignment);
	DDX_Text(pDX, IDC_EDIT8, m_Magic);
	DDX_Text(pDX, IDC_EDIT9, m_Subsystem);
	DDX_Text(pDX, IDC_EDIT10, m_NumberOfSections);
	DDX_Text(pDX, IDC_EDIT11, m_TimeDateStamp);
	DDX_Text(pDX, IDC_EDIT12, m_SizeOfHeaders);
	DDX_Text(pDX, IDC_EDIT13, m_Characteristics);
	DDX_Text(pDX, IDC_EDIT14, m_CheckSum);
	DDX_Text(pDX, IDC_EDIT15, m_SizeOfOptionalHeader);
	DDX_Text(pDX, IDC_EDIT16, m_NumberOfRvaAndSizes);
}

BEGIN_MESSAGE_MAP(C简易PEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &C简易PEDlg::OnEnChangeEdit1)
	ON_WM_DROPFILES()
	ON_EN_CHANGE(IDC_EDIT2, &C简易PEDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON12, &C简易PEDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON3, &C简易PEDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON13, &C简易PEDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON10, &C简易PEDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &C简易PEDlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// C简易PEDlg 消息处理程序

BOOL C简易PEDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C简易PEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C简易PEDlg::OnPaint()
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
HCURSOR C简易PEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//实现文件拖拽
void C简易PEDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UINT movecount=DragQueryFile(hDropInfo,-1,NULL,0);
	TCHAR movefile[MAX_PATH]={0};
	for (UINT i=0;i<movecount;i++)
	{

		DragQueryFile(hDropInfo,i,movefile,MAX_PATH);
		SetWindowText(movefile);
		//	UpdateData(FALSE);
	}
	DragFinish(hDropInfo);
	AnalPE.ObtainPeInfo(movefile);
	ShowPeInfo();
	CDialogEx::OnDropFiles(hDropInfo);
}
//界面显示PE相关信息
void C简易PEDlg::ShowPeInfo()
{
	//BaseOfCode;
	if (AnalPE.buf==NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return ;
	}
	AnalPE.OutPutPeInfo(m_EntryPoint,AnalPE.pOptH->AddressOfEntryPoint);		//入口点
	AnalPE.OutPutPeInfo(m_ImageBase,AnalPE.pOptH->ImageBase);					//镜像地址
	AnalPE.OutPutPeInfo(m_SizeOfImage,AnalPE.pOptH->SizeOfImage);				//镜像大小
	AnalPE.OutPutPeInfo(m_BaseOfCode,AnalPE.pOptH->BaseOfCode);					//代码基址
	AnalPE.OutPutPeInfo(m_BaseOfData,AnalPE.pOptH->BaseOfData);					//数据基址
	AnalPE.OutPutPeInfo(m_SectionAlignment,AnalPE.pOptH->SectionAlignment);		//块对齐
	AnalPE.OutPutPeInfo(m_FileAlignment,AnalPE.pOptH->FileAlignment);			//文件块对齐
	AnalPE.OutPutPeInfo(m_Magic,AnalPE.pOptH->Magic);							//标志字
	//第二版
	AnalPE.OutPutPeInfo(m_Subsystem,AnalPE.pOptH->Subsystem);					//子系统
	AnalPE.OutPutPeInfo(m_NumberOfSections,AnalPE.pNtH->FileHeader.NumberOfSections);			//区段数目
	AnalPE.OutPutPeInfo(m_TimeDateStamp,AnalPE.pNtH->FileHeader.TimeDateStamp);				//日期时间标志
	AnalPE.OutPutPeInfo(m_SizeOfHeaders,AnalPE.pOptH->SizeOfHeaders);			//部首大小
	AnalPE.OutPutPeInfo(m_Characteristics,AnalPE.pNtH->FileHeader.Characteristics);			//特征值
	AnalPE.OutPutPeInfo(m_CheckSum,AnalPE.pOptH->CheckSum);						//校验和
	AnalPE.OutPutPeInfo(m_SizeOfOptionalHeader,AnalPE.pNtH->FileHeader.SizeOfOptionalHeader);	//可选头部大小
	AnalPE.OutPutPeInfo(m_NumberOfRvaAndSizes,AnalPE.pOptH->NumberOfRvaAndSizes);//RVA数及大小
	UpdateData(FALSE);
}
//
//
void C简易PEDlg::OutPutPeInfo(CString &m_PeInfo,DWORD PeValue)
{
	CString str;
	str.Format(L"%08X",PeValue);//转16进制
	m_PeInfo=str;
	UpdateData(FALSE);
}

//入口点
void C简易PEDlg::OnEnChangeEdit1()
{
	UpdateData(TRUE);
}




//镜像地址
void C简易PEDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。


	// TODO:  在此添加控件通知处理程序代码
}

//目录
void C简易PEDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	MyCatalog dialog;
	dialog.DoModal();
}

//部首大小 +
void C简易PEDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	CStringA PeValue(m_SizeOfHeaders);
	char *p=PeValue.GetBuffer();	//转换为char* 类型
	AnalPE.pOptH->SizeOfHeaders=strtoul(p,0,16)+512;;		//转换为10进制DWORD  512为16进制200
	OutPutPeInfo(m_SizeOfHeaders,AnalPE.pOptH->SizeOfHeaders);			//部首大小
//	WriteFile(AnalPE.hFile,cs,strlen(cs),&dwsize,NULL);	
	AnalPE.ClosePeHandle();
}

//区段表
void C简易PEDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AnalPE.buf==NULL)
	{
		AfxMessageBox(L"请拖入PE文件");
		return ;
	}
	MyAreaTable dlg;
	dlg.DoModal();
}

//位置计算器
void C简易PEDlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	MyFileLocation dlg;
	dlg.DoModal();
}


void C简易PEDlg::OnBnClickedButton9()
{
	EndDialog(0);
	// TODO: 在此添加控件通知处理程序代码
}
