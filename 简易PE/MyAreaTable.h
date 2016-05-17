#pragma once
#include "afxcmn.h"


// MyAreaTable 对话框

class MyAreaTable : public CDialogEx
{
	DECLARE_DYNAMIC(MyAreaTable)

public:
	MyAreaTable(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyAreaTable();

// 对话框数据
	enum { IDD = AreaTable };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_AreaTabList;
	void ShowAreaTable();
//	afx_msg void OnClose();
//	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
