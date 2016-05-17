#pragma once
#include "afxcmn.h"


// MyRelocation 对话框

class MyRelocation : public CDialogEx
{
	DECLARE_DYNAMIC(MyRelocation)

public:
	MyRelocation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyRelocation();

// 对话框数据
	enum { IDD = Relocation };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowRelocation();
	CListCtrl m_FirstReloc;
	CListCtrl m_SecondReloc;
	virtual BOOL OnInitDialog();
	void OnNMClickList(NMHDR *pNMHDR,LRESULT *pResult);
};
