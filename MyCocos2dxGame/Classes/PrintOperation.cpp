#include "PrintOperation.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

void PrintOperation::print()
{
	char szprinter[80];
	//
	wchar_t wtext[20];
	mbstowcs(wtext, szprinter, strlen(szprinter) + 1);//Plus null
	LPWSTR szprinter_lp = wtext;
	//
	char *szDevice, *szDriver, *szOutput;
	LPCTSTR szDevice_lp = (LPCTSTR)szDevice;
	LPCTSTR szDriver_lp = (LPCTSTR)szDevice;
	LPCTSTR szOutput_lp = (LPCTSTR)szOutput;
	//

	//
	HDC hdcprint; // 定义一个设备环境句柄
	//定义一个打印作业
	static DOCINFO di = { sizeof (DOCINFO), L"printer", NULL };
	// 得到设备字符串存入数组szprinter中 
	GetProfileString(L"windows", L"device", L",,,", szprinter_lp, 80);
	// 将设备字符串分解
	if (NULL != (szDevice = strtok(szprinter, ",")) && NULL != (szDriver = strtok(NULL, ",")) &&
		NULL != (szOutput = strtok(NULL, ",")))
		// 创建一个打印机设备句柄
	if ((hdcprint = CreateDC(szDriver_lp, szDevice_lp, szOutput_lp, NULL)) != 0)
	{
		if (StartDoc(hdcprint, &di)>0) //开始执行一个打印作业
		{
			StartPage(hdcprint); //打印机走纸,开始打印
			SaveDC(hdcprint); //保存打印机设备句柄
			// 输出一行文字
			TextOut(hdcprint, 1, 1, L"热烈祝贺编程实例出版发行！", 16);
			RestoreDC(hdcprint, -1); //恢复打印机设备句柄
			EndPage(hdcprint); //打印机停纸, 停止打印
			EndDoc(hdcprint); //结束一个打印作业
			CCLOG("打印完毕!", "提示", MB_ICONINFORMATION);
		}
		// 用API函数DeleteDC销毁一个打印机设备句柄
		DeleteDC(hdcprint);
	}
	else
	{
		CCLOG("没有 默认打印机,或者没有安装打印机!");
		return;
	}
}
/*
void PrintOperation::onPrint(CDC *pdc, CPrintInfo *pInfo)
{
	
}
*/