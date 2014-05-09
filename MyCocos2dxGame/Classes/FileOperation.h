#ifndef __HELLOWORLD_FILE_OPERATION__
#define __HELLOWORLD_FILE_OPERATION__

#include <string>

#include <Shlobj.h>
#include <Shobjidl.h>
#include <iostream>
#include <vector>

#include "scope_guard.h"

class FileOperation
{
public:
	static void saveFile(void);
	static void readFile(void);
	static std::string getFilePath();
	static void openFile(void);
};

#endif