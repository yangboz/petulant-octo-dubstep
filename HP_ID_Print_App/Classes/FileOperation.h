#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

#include <Shlobj.h>
#include <Shobjidl.h>
#include <iostream>
#include <vector>

#include "scope_guard.h"

#include "HW_StringUtils.h"

#include <locale>

class FileOperation
{
public:
	static std::string saveFileDialog();
	static void readFile(std::wstring filePath);
	static std::string getFilePath();
	static std::string openFileDialog();
	static std::vector<std::wstring> openFilesDialog();
};

#endif