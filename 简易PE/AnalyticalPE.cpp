#include "stdafx.h"
#include "AnalyticalPE.h"


AnalyticalPE::AnalyticalPE(void)
{
}


AnalyticalPE::~AnalyticalPE(void)
{
}
void AnalyticalPE::ObtainPeInfo(TCHAR *FileName)
{
	//	TCHAR FileName[] = _T("C:\\Users\\Administrator\\Desktop\\PEText.exe");
	PeFileName=FileName;
	buf = nullptr;
	//得到文件句柄
	hFile =CreateFile(
		FileName, GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	//得到文件大小
	DWORD dwFileSize = 
		GetFileSize(hFile, NULL);
	DWORD ReadSize = 0;
	buf = new char[dwFileSize];
	//将文件读取到内存
	ReadFile(hFile, buf, dwFileSize, &
		ReadSize, NULL);
	pDosH=(PIMAGE_DOS_HEADER)buf;
	if(IMAGE_DOS_SIGNATURE!=pDosH->e_magic)
	{
		//MessageBox(L"不是DOS头",L"s")
		AfxMessageBox(L"不是DOS头");
		return ;
	}
	//printf_s("DOS头:0x%X\n",pDosH->e_magic);
	//printf_s("EXE文件的偏移头:0x%X\n",pDosH->e_lfanew);
	//获取NT头
	pNtH=(PIMAGE_NT_HEADERS32)(buf+pDosH->e_lfanew);  
	//PIMAGE_NT_HEADERS32 pNtH=(PIMAGE_NT_HEADERS32)buf;  
	if (pNtH->Signature!=IMAGE_NT_SIGNATURE)
	{
	//	MessageBox(L"不是NT头");
		AfxMessageBox(L"不是NT头");
		return ;
	}
	//获取区段头
	pSecH=IMAGE_FIRST_SECTION(pNtH);
	//获取可选头数据
	pOptH=&(pNtH->OptionalHeader);
	//获取数据目录
	pDatD=&(pOptH->DataDirectory[0]);
	//获取导出表数据
	//pExpD=(PIMAGE_EXPORT_DIRECTORY)(buf+CalcOffset(pDatD->VirtualAddress));
}

void AnalyticalPE::ClosePeHandle()
{
	CloseHandle(hFile);
}

DWORD AnalyticalPE::ChangeNumber(CString NeedValue)
{
	CStringA PeValue(NeedValue);
	char *p=PeValue.GetBuffer();	//转换为char* 类型
	return strtoul(p,0,16);		//转换为十进制数字

}



void AnalyticalPE::OutPutPeInfo(CString &StrPeValue,DWORD WithPeValue)
{
	CString NewStrPeValue;
	NewStrPeValue.Format(L"%08X",WithPeValue);//转16进制
	StrPeValue=NewStrPeValue;
	
}

DWORD AnalyticalPE::CalcOffset(DWORD Rva)
{
	//循环比较在那个区段  不在这个区段就继续循环  
	//PIMAGE_NT_HEADERS32 pnt=pNtH;
	PIMAGE_SECTION_HEADER pSecHTemp=IMAGE_FIRST_SECTION(pNtH);//区段头
	int index=0;
	while (!(Rva>=pSecHTemp->VirtualAddress&&
		Rva<pSecHTemp->VirtualAddress+pSecHTemp->SizeOfRawData))
	{
		//找完所有区段还没有找到
		if (index>pNtH->FileHeader.NumberOfSections)
		{
			//	m_Section=L"部首";
			////	DWORD a[5];
			//	_memccpy(&Address,pSecHTemp,6,24);
			//	//Address=(int);			

			return Rva;
		}
		++index;
		++pSecHTemp;
	}
	return Rva-pSecHTemp->VirtualAddress+pSecHTemp->PointerToRawData;;
}
