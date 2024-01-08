// Sample loop calculator.
// Calculates the length of a sample loop in inches from input of
// volume in ml. or cc. and type of tubing used.
// Made for use in FID type gas analyzers.

#include "Window.h"


int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow )
{

    try
    {
        // Instantiate the window.
        Window mainWnd(315, 515, "Sample Loop Calculator");

        // Message loop identifiers.
        MSG msg;
        BOOL gResult;

		// Load the accelerator table.
		HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));

		// Register Hot Keys.
		RegisterHotKey(NULL, ESC_HOTKEY, MOD_NOREPEAT, VK_ESCAPE);

		// Item list for combobox.
		const char tubeList[3][50] =
		{
			"1/8 OD Teflon Tubing",
			"1/16 OD Stainless Steal Tubing",
			"User Defined"

		};

		char tubeBuff[80];		// Buffer for comboBox list.

		memset(&tubeBuff, 0, sizeof(tubeBuff));   // Allocate memory for the tube buffer and set to 0.

		for (int k = 0; k <= 2; k++)	// Traverse the array.
		{
			strcpy_s(tubeBuff, sizeof(tubeBuff) / sizeof(char), (char*)tubeList[k]);

			// Add string to combobox.
			// Load the combobox with item list.  
			// Send a CB_ADDSTRING message to load each item.
			SendMessage(hComboBoxSelTb, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)tubeBuff);
		}

		// Send the CB_SETCURSEL message to display an initial item 
		// in the selection field.
		SendMessage(hComboBoxSelTb, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

		// The message loop.
        while ((gResult = GetMessage(&msg, NULL, 0, 0)) > 0)
        {
			// Hot Keys.
			if (msg.wParam == ESC_HOTKEY)
			{
				return 0;
				//MessageBox(NULL, TEXT("Escape Key Down"), TEXT("Key Down"), MB_OK);
			}

			//// To use keyboard accelerator table.
			//if (!TranslateAccelerator(mainWnd.GetWinHandle(), hAccelTable, &msg))
			//{
			//	TranslateMessage(&msg);
			//	DispatchMessage(&msg);
			//}

			//// To use tabstops.
			//if (!IsDialogMessage(mainWnd.GetWinHandle(), &msg))
			//{
			//	TranslateMessage(&msg); // Translate virtual-key messages into character messages.
			//	DispatchMessage(&msg);  // Send message to windows procedure.
			//}

			// To use them both - (Causes "0.0625" in ID box).
			if (!TranslateAccelerator(mainWnd.GetWinHandle(), hAccelTable, &msg))
			{
				if (!IsDialogMessage(mainWnd.GetWinHandle(), &msg))
				{
					TranslateMessage(&msg); // Translate virtual-key messages into character messages.
					DispatchMessage(&msg);  // Send message to windows procedure.
				}
			}
            
        }

		// Check GetMessage for error.
		if (gResult == -1)
		{
			throw GTWND_LAST_EXCEPT();
		}

		// wParam here is the value passed to PostQuitMessage.
		return (int)msg.wParam;
	}
	catch (const GTException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	return -1;
    
}