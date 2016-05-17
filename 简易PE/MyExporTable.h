#pragma once
#include "afxcmn.h"


// MyExporTable 对话框

class MyExporTable : public CDialogEx
{
	DECLARE_DYNAMIC(MyExporTable)

public:
	MyExporTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyExporTable();

// 对话框数据
	enum { IDD = ExporTable };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnCbnSelchangeCombo2();
	void ShowExportInfo();		//显示输出表信息	
	void ShowExportList();		//显示输出表信息	
	virtual BOOL OnInitDialog();	 
	CString m_ExportOffest;			 //输出表偏移
	CString m_Characteristic;		 //特征值
	CString m_Plot;					 //基址
	CString m_Name;					 //名称
	CString m_NameString;			 //名称字符串
	CString m_FunctionNumber;		 //函数数量
	CString m_FunctionNameNumber;	 //函数名数量
	CString m_FunctionAddr;			 //函数地址
	CString m_FunctionNameAddr;		 //函数名称地址
	CString m_FunSerialNumberAddr;	 //函数名序号地址
	CListCtrl m_ExportList;
};
