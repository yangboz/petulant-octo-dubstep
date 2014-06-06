#include "PrintOperation.h"

// to enable CCLOG()
#define COCOS2D_DEBUG 1
#include "cocos2d.h"

void PrintOperation::printDialog()
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

			localPrinterName = localDevmode->dmDeviceName;


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
	}
}
/*
void PrintOperation::onPrint(CDC *pdc, CPrintInfo *pInfo)
{

}
*/
void PrintOperation::printJpegImage(std::string context)
{
	
}