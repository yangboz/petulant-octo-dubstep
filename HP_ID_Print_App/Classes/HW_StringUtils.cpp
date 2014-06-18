#include "HW_StringUtils.h"

std::string HW_StringUtils::ws2s(const std::wstring& widestring)
{
	unsigned len = widestring.size() * 4;
	setlocale(LC_CTYPE, "");
	char *p = new char[len];
	wcstombs(p, widestring.c_str(), len);
	std::string str1(p);
	delete[] p;
	return str1;
}

std::wstring HW_StringUtils::s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}
/*
void HW_StringUtils::charTowchar(const char *chr, wchar_t *wchar, int size)
{
	MultiByteToWideChar(CP_ACP, 0, chr,strlen(chr) + 1, wchar, size / sizeof(wchar[0]));
}

void HW_StringUtils::wcharTochar(const wchar_t *wchar, char *chr, int length)
{
	WideCharToMultiByte(CP_ACP, 0, wchar, -1,chr, length, NULL, NULL);
}
*/
//Chinese character warpper
//! convert from wstring to UTF8 using self-coding-converting  
void HW_StringUtils::WStrToUTF8Convert(std::string& dest, const std::wstring& src)
{
	dest.clear();

	for (size_t i = 0; i < src.size(); i++){
		wchar_t w = src[i];
		if (w <= 0x7f)
			dest.push_back((char)w);
		else if (w <= 0x7ff)
		{
			dest.push_back(0xc0 | ((w >> 6) & 0x1f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (w <= 0xffff)
		{
			dest.push_back(0xe0 | ((w >> 12) & 0x0f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else if (sizeof(wchar_t) > 2 && w <= 0x10ffff)
		{
			dest.push_back(0xf0 | ((w >> 18) & 0x07)); // wchar_t 4-bytes situation  
			dest.push_back(0x80 | ((w >> 12) & 0x3f));
			dest.push_back(0x80 | ((w >> 6) & 0x3f));
			dest.push_back(0x80 | (w & 0x3f));
		}
		else
			dest.push_back('?');
	}
}

std::string HW_StringUtils::WStrToUTF8(const std::wstring &str)
{
	std::string result;
	WStrToUTF8Convert(result, str);
	return result;
}