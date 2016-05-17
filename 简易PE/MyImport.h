#pragma once
#include "afxcmn.h"


// MyImport 对话框

class MyImport : public CDialogEx
{
	DECLARE_DYNAMIC(MyImport)

public:
	MyImport(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyImport();

// 对话框数据
	enum { IDD = Import };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowImportList();		//显示输入表信息
	CListCtrl m_UpImport;
	CListCtrl m_DownImport;
	virtual BOOL OnInitDialog();
//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
};
