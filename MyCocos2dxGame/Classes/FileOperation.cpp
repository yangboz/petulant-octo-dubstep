// to enable CCLOG()
#define COCOS2D_DEBUG 1

#include "cocos2d.h"
#include "FileOperation.h"
#include <stdio.h>

using namespace std;

void FileOperation::saveFile()
{
	string path = getFilePath();
	FILE *fp = fopen(path.c_str(), "w");

	if (!fp)
	{
		CCLOG("can not create file %s", path.c_str());
		return;
	}

	fputs("file example", fp);
	fclose(fp);
}

void FileOperation::readFile(std::wstring filePath)
{
	//string path = getFilePath();
	string path = HW_StringUtils::ws2s(filePath);
	FILE *fp = fopen(path.c_str(), "r");
	char buf[50] = { 0 };

	if (!fp)
	{
		CCLOG("can not open file %s", path.c_str());
		return;
	}

	fgets(buf, 50, fp);
	CCLOG("read content %s", buf);

	fclose(fp);
}

string FileOperation::getFilePath()
{
	string path("");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// In android, every programe has a director under /data/data.
	// The path is /data/data/ + start activity package name.
	// You can save application specific data here.
	path.append("/data/data/org.cocos2dx.application/tmpfile");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	// You can save file in anywhere if you have the permision.
	path.append("C:/invalid.txt");
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
	path = cocos2d::CCApplication::sharedApplication().getAppDataPath();

#ifdef _TRANZDA_VM_
	// If runs on WoPhone simulator, you should insert "D:/Work7" at the
	// begin. We will fix the bug in no far future.
	path = "C:/" + path;
	path.append("tmpfile");
#endif

#endif

	return path;
}

std::string FileOperation::openFile()
{
	HRESULT hr = S_OK;
	//std::vector<std::wstring> filePaths;
	std::wstring filePaths;
	std::string filePath;

	IFileOpenDialog *fileDlg = NULL;
	hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fileDlg));
	if (FAILED(hr)) return filePath;
	ON_SCOPE_EXIT([&] { fileDlg->Release(); });

	IKnownFolderManager *pkfm = NULL;
	hr = CoCreateInstance(CLSID_KnownFolderManager,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pkfm));
	if (FAILED(hr)) return filePath;
	ON_SCOPE_EXIT([&] { pkfm->Release(); });

	IKnownFolder *pKnownFolder = NULL;
	hr = pkfm->GetFolder(FOLDERID_PublicMusic, &pKnownFolder);
	//if (FAILED(hr)) return filePaths;
	ON_SCOPE_EXIT([&] { pKnownFolder->Release(); });

	IShellItem *psi = NULL;
	hr = pKnownFolder->GetShellItem(0, IID_PPV_ARGS(&psi));
	if (FAILED(hr)) return filePath;
	ON_SCOPE_EXIT([&] { psi->Release(); });

	hr = fileDlg->AddPlace(psi, FDAP_BOTTOM);
	COMDLG_FILTERSPEC rgSpec[] = {
		{ L"图片文件", L"*.png;*.jpg;*.jpeg;*.gif;" }
	};
	fileDlg->SetFileTypes(1, rgSpec);

	DWORD dwOptions;
	fileDlg->GetOptions(&dwOptions);
	//
	fileDlg->SetOptions(dwOptions | FOS_FILEMUSTEXIST);
	hr = fileDlg->Show(NULL);
	if (SUCCEEDED(hr)) {
		IShellItemArray *pRets;
		hr = fileDlg->GetResults(&pRets);
		if (SUCCEEDED(hr)) {
			DWORD count;
			pRets->GetCount(&count);
			for (DWORD i = 0; i < count; i++) {
				IShellItem *pRet;
				LPWSTR nameBuffer;
				pRets->GetItemAt(i, &pRet);
				pRet->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &nameBuffer);
				//filePaths.push_back(std::wstring(nameBuffer));
				filePaths = std::wstring(nameBuffer);
				pRet->Release();
				CoTaskMemFree(nameBuffer);
			}
			pRets->Release();
		}
	}
	//
	filePath = HW_StringUtils::ws2s(filePaths);
	CCLOG("Selected image file path: %s \\n", filePath.c_str());
	return filePath;
}

std::vector<std::wstring> openFiles()
{
	HRESULT hr = S_OK;
	std::vector<std::wstring> filePaths;

	IFileOpenDialog *fileDlg = NULL;
	hr = CoCreateInstance(CLSID_FileOpenDialog,
		NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&fileDlg));
	if (FAILED(hr)) return filePaths;
	ON_SCOPE_EXIT([&] { fileDlg->Release(); });

	IKnownFolderManager *pkfm = NULL;
	hr = CoCreateInstance(CLSID_KnownFolderManager,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&pkfm));
	if (FAILED(hr)) return filePaths;
	ON_SCOPE_EXIT([&] { pkfm->Release(); });

	IKnownFolder *pKnownFolder = NULL;
	hr = pkfm->GetFolder(FOLDERID_PublicMusic, &pKnownFolder);
	//if (FAILED(hr)) return filePaths;
	ON_SCOPE_EXIT([&] { pKnownFolder->Release(); });

	IShellItem *psi = NULL;
	hr = pKnownFolder->GetShellItem(0, IID_PPV_ARGS(&psi));
	if (FAILED(hr)) return filePaths;
	ON_SCOPE_EXIT([&] { psi->Release(); });

	hr = fileDlg->AddPlace(psi, FDAP_BOTTOM);
	COMDLG_FILTERSPEC rgSpec[] = {
		{ L"图片文件", L"*.png;*.jpg;*.jpeg;*.gif;" }
	};
	fileDlg->SetFileTypes(1, rgSpec);

	DWORD dwOptions;
	fileDlg->GetOptions(&dwOptions);
	//
	fileDlg->SetOptions(dwOptions | FOS_ALLOWMULTISELECT);
	hr = fileDlg->Show(NULL);
	if (SUCCEEDED(hr)) {
		IShellItemArray *pRets;
		hr = fileDlg->GetResults(&pRets);
		if (SUCCEEDED(hr)) {
			DWORD count;
			pRets->GetCount(&count);
			for (DWORD i = 0; i < count; i++) {
				IShellItem *pRet;
				LPWSTR nameBuffer;
				pRets->GetItemAt(i, &pRet);
				pRet->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, &nameBuffer);
				filePaths.push_back(std::wstring(nameBuffer));
				pRet->Release();
				CoTaskMemFree(nameBuffer);
			}
			pRets->Release();
		}
	}
	CCLOG("Selected image files path: c \\n", filePaths);
	return filePaths;
}