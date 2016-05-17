#pragma once
class AnalyticalPE
{
public:
	AnalyticalPE(void);
	~AnalyticalPE(void);
public:
	CString PeFileName;
	char* buf ;
	PIMAGE_DOS_HEADER pDosH;	//DOS头
	PIMAGE_NT_HEADERS32 pNtH;	//NT头
	PIMAGE_OPTIONAL_HEADER32 pOptH;//可选头
	PIMAGE_SECTION_HEADER pSecH;//区段头
	PIMAGE_DATA_DIRECTORY pDatD;//数据目录
	PIMAGE_EXPORT_DIRECTORY pExpD;// 导出表数据
	void ObtainPeInfo(TCHAR *FileName);					//获取PE信息
	void ClosePeHandle();
	HANDLE hFile ;
	DWORD ChangeNumber(CString NeedValue);			//进制转换
	void OutPutPeInfo(CString &StrPeValue,DWORD WithPeValue);
	DWORD CalcOffset(DWORD Rva);		//计算位置
};

