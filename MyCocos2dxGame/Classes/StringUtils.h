#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>

class StringUtils
{
public:
	static std::string ws2s(const std::wstring& ws);
	static std::wstring s2ws(const std::string& s);
};

#endif