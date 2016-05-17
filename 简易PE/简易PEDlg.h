
// 简易PEDlg.h : 头文件
//
#include "AnalyticalPE.h"
#pragma once


// C简易PEDlg 对话框
class C简易PEDlg : public CDialogEx
{
// 构造
public:
	C简易PEDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	DWORD m_EntryPoint;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnDropFiles(HDROP hDropInfo);
public:
	
	void ShowPeInfo();			//显示PE相关信息
	void OutPutPeInfo(CString &m_PeInfo,DWORD PeValue);	//输出PE相关信息
	CString m_EntryPoint;
	CString m_ImageBase;
	afx_msg void OnEnChangeEdit2();
	CString m_SizeOfImage;
	CString m_BaseOfCode;
	CString m_BaseOfData;
	CString m_SectionAlignment;
	CString m_FileAlignment;
	CString m_Magic;
	CString m_Subsystem;
	CString m_NumberOfSections;
	CString m_TimeDateStamp;
	CString m_SizeOfHeaders;
	CString m_Characteristics;
	CString m_CheckSum;
	CString m_SizeOfOptionalHeader;
	CString m_NumberOfRvaAndSizes;
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
};
