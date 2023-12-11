// Sample loop calculator.

#include "Window.h"

int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow )
{
    // Instantiate the window.
    Window wnd(330, 475, "Sample Loop Calculator");

    // The message loop.
    MSG msg;
    BOOL gResult;

    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&msg); // translate virtual-key messages into character messages.
        DispatchMessage(&msg);  // Send message to windows procedure.
    }

    if (gResult == -1)
    {
        return -1;
    }

    return (int)msg.wParam;
}