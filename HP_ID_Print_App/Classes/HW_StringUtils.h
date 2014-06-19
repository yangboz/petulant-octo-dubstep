#ifndef __HW_STRING_UTILS_H__
#define __HW_STRING_UTILS_H__

#include <string>
#include "external/win32-specific/icon/include/iconv.h"
//
using namespace std;

#define GB2312 "gb2312";
#define UTF8 "utf-8";

class HW_StringUtils
{
public:
	static std::string ws2s(const std::wstring& wstring);
	static std::wstring s2ws(const std::string& s);
	//purpose:char to WCHAR 、wchar_t、LPWSTR etc
	/*
	void charTowchar(const char *chr, wchar_t *wchar, int size);
	void wcharTochar(const wchar_t *wchar, char *chr, int length);
	*/
	//ChineseCharacters Wrapper
	static std::string WStrToUTF8(const std::wstring &str);
	//@see http://bbs.9ria.com/blog-226579-20287.html
	static int gBKToUTF8(std::string & gbkStr);
private:
	static void WStrToUTF8Convert(std::string& dest, const std::wstring& src);
};

#endif