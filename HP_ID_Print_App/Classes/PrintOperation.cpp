#include "PrintOperation.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

std::string PrintOperation::printDialog()
{
	BOOL            printDlgReturn = FALSE;
	HDC                printerDC = NULL;
	PRINTDLG        printDlgInfo = { 0 };
	LPWSTR            localPrinterName = NULL;
	PDEVMODE        returnedDevmode = NULL;
	PDEVMODE        localDevmode = NULL;
	int                localNumberOfCopies = 0;

	// Initialize the print dialog box's data structure.
	printDlgInfo.lStructSize = sizeof(printDlgInfo);
	printDlgInfo.Flags =
		// Return a printer device context.
		PD_RETURNDC
		// Don't allow separate print to file.
		// Remove these flags if you want to support this feature.
		| PD_HIDEPRINTTOFILE
		| PD_DISABLEPRINTTOFILE 
		// Don't allow selecting individual document pages to print.
		// Remove this flag if you want to support this feature.
		| PD_NOSELECTION;

	// Display the printer dialog and retrieve the printer DC.
	printDlgReturn = PrintDlg(&printDlgInfo);

	// Check the return value.
	if (TRUE == printDlgReturn)
	{

		// Get the HDC of the selected printer
		printerDC = printDlgInfo.hDC;


		//  Lock the handle to get a pointer to the DEVMODE structure.
		returnedDevmode = (PDEVMODE)GlobalLock(printDlgInfo.hDevMode);

		localDevmode = (LPDEVMODE)HeapAlloc(
			GetProcessHeap(),
			HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS,
			returnedDevmode->dmSize);

		if (NULL != localDevmode)
		{
			memcpy(
				(LPVOID)localDevmode,
				(LPVOID)returnedDevmode,
				returnedDevmode->dmSize);

			//	const CCHDEVICENAME = 32;
			localPrinterName = localDevmode->dmDeviceName;//Note: that this name may be truncated to fit in the dmDeviceName array.


			localNumberOfCopies = printDlgInfo.nCopies;
		}
		else
		{
			// Unable to allocate a new structure 
		}

		//  dialog box.
		if (NULL != printDlgInfo.hDevMode)
		{
			GlobalFree(printDlgInfo.hDevMode);
		}
	}
	else
	{
		// The user cancelled out of the print dialog box.
		return "";
	}
	//
	std::wstring wstr(localPrinterName);
	std::string str(wstr.begin(), wstr.end());
	return str;
}
/*
void PrintOperation::onPrint(CDC *pdc, CPrintInfo *pInfo)
{

}
*/
void PrintOperation::printJpegImage(IplImage *image, std::string context)
{
	HANDLE print_handle;
	DOC_INFO_1 docinfo1;
	DWORD bytes_written;

	docinfo1.pDocName = (LPTSTR)L"HP_ID_Print.jpg";
	docinfo1.pOutputFile = NULL;
	docinfo1.pDatatype = (LPTSTR)L"RAW";

	BOOL bool1, bool2, bool3, bool4;

	//bool1 = OpenPrinter((LPTSTR)L"csi01p107.asiapacific.hpqcorp.net", &print_handle, NULL);
	bool1 = OpenPrinter((LPTSTR)context.c_str(), &print_handle, NULL);
	bool2 = StartDocPrinter(print_handle, 1, (LPBYTE)&docinfo1);

	bool3 = StartPagePrinter(print_handle);
	bool4 = WritePrinter(print_handle, (LPVOID)image->imageData, (DWORD)image->imageSize, &bytes_written);
	EndPagePrinter(print_handle);
	EndDocPrinter(print_handle);

	ClosePrinter(print_handle);
}

bool PrintOperation::printCommand(std::string imageFilePath, std::string printerName)
{
	//@see http://www.ehow.com/list_6520303_microsoft-paint-command-line-options.html
	//std::string  command = "C:\\Windows\\System32\\mspaint.exe C:\\lena.png /p";
	std::string command = "C:\\Windows\\System32\\mspaint.exe " + imageFilePath + " /pt " + printerName;
	//std::string command = "C:\\Windows\\System32\\mspaint.exe " + imageFilePath + " /pt ";
	//system("CLS");
	CCLOG("PrintOperation::printCommand cmd:%s", command.c_str());
	int result = system(command.c_str());
	//Sleep(5000);
	//system("PAUSE");
	CCLOG("PrintOperation::printCommand result:%i",result);
	return (bool)result;
}