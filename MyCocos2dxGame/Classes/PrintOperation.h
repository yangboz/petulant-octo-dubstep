#ifndef __HELLOWORLD_PRINT_OPERATION__
#define __HELLOWORLD_PRINT_OPERATION__

#include <string>
using namespace std;
//@see http://msdn.microsoft.com/zh-cn/library/32762a1z.aspx
//#include "windows.h"

#include "HW_StringUtils.h"

class PrintOperation
{
public:
	//@see http://cplusplusblogsbyrex.blogspot.com/2012/07/open-print-dialog-using-c.html
	static void printDialog();
private:
	//Print related variables
	//static void onPrint(CDC *pdc, CPrintInfo *pInfo);
};

#endif