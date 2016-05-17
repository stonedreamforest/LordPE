#pragma once
#include "afxcmn.h"


// MyResources 对话框

class MyResources : public CDialogEx
{
	DECLARE_DYNAMIC(MyResources)

public:
	MyResources(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyResources();

// 对话框数据
	enum { IDD = Resources };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_ResTreeList;
	void ShowResourcesInfo();
	virtual BOOL OnInitDialog();
	CString m_Name;
	CString m_Id;
	CString m_Name2;
	CString m_Id2;
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_Rva;
	CString m_Offset;
	CString m_Size;
};
