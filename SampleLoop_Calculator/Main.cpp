// Sample loop calculator.

#include "Window.h"
#include "framework.h"
#

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow )
{

    try
    {
        // Instantiate the window.
        Window wnd(315, 515, "Sample Loop Calculator");

        // The message loop.
        MSG msg;
        BOOL gResult;

		// Register Hot Keys.
		RegisterHotKey(NULL, ESC_HOTKEY, MOD_NOREPEAT, VK_ESCAPE);

		// Load the combobox with item list.  
		// Send a CB_ADDSTRING message to load each item.

		const char Valve[3][50] =
		{
			"1/8 OD Teflon Tubing",
			"1/16 OD Stainless Steal Tubing",
			"User Defined"

		};

		char A[60];		// Buffer for Tube ComboBox.
		int  k = 0;		// To traverse the array.

		memset(&A, 0, sizeof(A));   // Allocate memory for the Tubing buffer and set to 0.

		for (k = 0; k <= 2; k += 1)
		{
			strcpy_s(A, sizeof(A) / sizeof(char), (char*)Valve[k]);

			// Add string to combobox.
			SendMessage(hTubeComboBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)A);
		}

		// Send the CB_SETCURSEL message to display an initial item 
		// in the selection field.
		SendMessage(hTubeComboBox, CB_SETCURSEL, (WPARAM)2, (LPARAM)0);

        while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
        {
			// Hot Keys.
			if (msg.wParam == ESC_HOTKEY)
			{
				return 0;
				//MessageBox(NULL, TEXT("Escape Key Down"), TEXT("Key Down"), MB_OK);
			}

			if (!IsDialogMessage(wnd.GetWinHandle(), &msg))
			{
				TranslateMessage(&msg); // Translate virtual-key messages into character messages.
				DispatchMessage(&msg);  // Send message to windows procedure.
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