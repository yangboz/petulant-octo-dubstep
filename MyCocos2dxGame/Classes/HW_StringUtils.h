#ifndef __HW_STRING_UTILS_H__
#define __HW_STRING_UTILS_H__

#include <string>

class HW_StringUtils
{
public:
	static std::string ws2s(const std::wstring& ws);
	static std::wstring s2ws(const std::string& s);
	//ChineseCharacters Wrapper
	static std::string WStrToUTF8(const std::wstring &str);
private:
	static void WStrToUTF8Convert(std::string& dest, const std::wstring& src);
};

#endif