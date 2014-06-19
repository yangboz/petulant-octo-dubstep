#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

#include <Shlobj.h>
#include <Shobjidl.h>
#include <iostream>
#include <vector>

#include "scope_guard.h"

#include "HW_StringUtils.h"
#include "HW_DataModel.h"

#include <locale>

class FileOperation
{
public:
	static std::string saveFileDialog();
	static void readFile(std::wstring filePath);
	static std::string getFilePath();
	static std::string openFileDialog();
	static std::vector<std::wstring> openFilesDialog();
	//@see https://answers.yahoo.com/question/index?qid=20081125140921AA3VB5V
	static bool copyFileToWorkspace(std::string src, std::string dst);
};

#endif