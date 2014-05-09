#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

#include <Shlobj.h>
#include <Shobjidl.h>
#include <iostream>
#include <vector>

#include "scope_guard.h"

#include "StringUtils.h"

class FileOperation
{
public:
	static void saveFile(void);
	static void readFile(std::wstring filePath);
	static std::string getFilePath();
	static std::wstring openFile();
	static std::vector<std::wstring> openFiles();
};

#endif