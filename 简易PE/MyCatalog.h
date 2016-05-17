
#pragma once


// MyCatalog 对话框

class MyCatalog : public CDialogEx
{
	DECLARE_DYNAMIC(MyCatalog)

public:
	MyCatalog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MyCatalog();

// 对话框数据
	enum { IDD = Catalog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnBnClickedButton9();
	virtual BOOL OnInitDialog();
public:
	
	void ShowPeInfo();
	void OutPutPeInfo(CString &m_PeRvaInfo,CString &m_PeSizeInfo,DWORD PeRvaValue,DWORD PeSizeValue);//输出PE相关信息
	CString m_ExportRva;
	CString m_ExportSize;
	CString m_ImportRva;
	CString m_ImportSize;
	CString m_ResourceRva;
	CString m_ResourceSize;
	CString m_ExceptionRva;
	CString m_ExceptionSize;
	CString m_SecurityRva;
	CString m_SecuritySize;
	CString m_BaserelocRva;
	CString m_BaserelocSize;
	CString M_DebugRva;
	CString M_DebugSize;
	CString m_ArchitectureRva;
	CString m_ArchitectureSize;
	CString m_GlobalptrRva;
	CString m_GlobalptrSize;
	CString m_TlsRva;
	CString m_TlsSize;
	CString m_LoadConfigRva;
	CString m_LoadConfigSize;
	CString m_BoundImportRva;
	CString m_BoundImportSize;
	CString m_IatRva;
	CString m_IatSize;
	CString m_DelayImportRva;
	CString m_DelayImportSize;
	CString m_ComDescriptorRva;
	CString m_ComDescriptorSize;
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton21();
};
