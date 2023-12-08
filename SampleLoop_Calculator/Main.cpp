// Sample loop calculator.

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow )
{
    const auto szWindowClass = "smplLoopCalc";
    const auto szTitle = "Sample Loop Calculator";

	// Register window class.
	WNDCLASSEX wcex = { 0 };

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = nullptr; //LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAMPLOOPCALC5));
    wcex.hCursor = nullptr; //LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_SAMPLOOPCALC5);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = nullptr; //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);

	// Create window instance.
    // The main window.
    HWND hWnd = CreateWindowEx(
        0,
        szWindowClass, 
        szTitle, 
        WS_CAPTION | WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_SYSMENU,
        100, 
        100, 
        330, 
        555, 
        nullptr, 
        nullptr, 
        hInstance, 
        nullptr 
    );

    // Show the window.
    ShowWindow(hWnd, SW_SHOW);

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
    else
    {
        return msg.wParam;
    }

	return 0;
}