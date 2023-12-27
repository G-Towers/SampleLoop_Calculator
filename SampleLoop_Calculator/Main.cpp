// Sample loop calculator.

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
        Window wnd(315, 515, "Sample Loop Calculator");

        // The message loop.
        MSG msg;
        BOOL gResult;

		// Register Hot Keys.
		RegisterHotKey(NULL, ESC_HOTKEY, MOD_NOREPEAT, VK_ESCAPE);

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
				TranslateMessage(&msg); // translate virtual-key messages into character messages.
				DispatchMessage(&msg);  // Send message to windows procedure.
			}
            
        }

		// check if GetMessage call itself borked
		if (gResult == -1)
		{
			throw GTWND_LAST_EXCEPT();
		}

		// wParam here is the value passed to PostQuitMessage
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