// Window.cpp

#include "Window.h"
#include "Widget.h"
#include <sstream>

// Define global variables for linker to see them.
HWND hVol, hID, hClrBtn, hCalcBtn, hLength, hMsgBox, hTubeComboBox;
BOOL bMsgRed = 0;

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

// Message handler for Info box.
INT_PTR CALLBACK Info(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;

	}
	return (INT_PTR)FALSE;
}

void Interface(HWND hWnd, HINSTANCE hInst)
{
	// Call Widget functions to draw the interface. 
	Widget::GroupBox(15, 10, 285, 220, "Volume and ID Information", hWnd, hInst);
	Widget::RLabel(45, 50, 120, 30, "Enter Volume in Cubic Centemeters: ", hWnd);
	hVol = Widget::InputBox(180, 55, 100, 25, hWnd);
	Widget::LLabel(25, 100, 220, 30, "Select Tubing: ", hWnd);
	hTubeComboBox = Widget::ComboBox(25, 120, 265, 150, "", hWnd, hInst);
	Widget::RLabel(20, 170, 150, 30, "Enter inside diameter of tube in inches: ", hWnd);
	hID = Widget::InputBox(180, 175, 100, 25, hWnd);
	hClrBtn = Widget::Button(15, 255, 100, 30, "Clear", hWnd, (HMENU)CLEAR_BUTTON);
	hCalcBtn = Widget::Button(200, 255, 100, 30, "Calculate", hWnd, (HMENU)CALCULATE_BUTTON);
	Widget::GroupBox(15, 305, 285, 175, "Sample Loop Results", hWnd, hInst);
	Widget::RLabel(20, 350, 120, 60, "The length of your sample loop is: ", hWnd);
	hLength = Widget::ResultBox(150, 355, 80, 25, hWnd);
	Widget::LLabel(240, 365, 50, 25, "inches.", hWnd);
	hMsgBox = Widget::MsgBox(30, 415, 255, 40, hWnd);

}

int CalcLength(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox, BOOL bMsgRed)
{
	int val;
	double volNum, idNum, lengthNum;
	char volText[100], idText[100], lengthText[100];
	std::string lengthString;


	const char* msgStandard = " A standard size.";
	const char* msgLarge = " A very large sample loop. Make sure\n there is enough space.";
	const char* msgTooSmall = " The sample loop is too small.";

	GetWindowText(hVol, volText, 100);	// Retrieve the volume text.
	GetWindowText(hID, idText, 100);	// Retrieve the ID text.

	// Validate user input.
	if (strcmp(volText, "") == 0 || strcmp(idText, "") == 0)
	{
		val = MessageBoxEx(Window::GetWinHandle(), "You are missing input!\nPlease enter both volume and inside diameter.",
			NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

		switch (val)
		{
		case IDCANCEL:
			DestroyWindow(Window::GetWinHandle());
			break;

		case IDOK:
			return 0;
			break;

		}
	}

	for (size_t i = 0; i < strlen(volText); i++)
	{
		if (!isdigit(volText[i]) && volText[i] != '.')
		{
			val = MessageBoxEx(Window::GetWinHandle(), "Volume is not a valid number!\nPlease enter volume as a valid number."
				"\nSee -- Help \\ Info-- for more information.",
				NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (val)
			{
			case IDCANCEL:
				DestroyWindow(Window::GetWinHandle());
				break;

			case IDOK:
				return 0;
				break;

			}
		}
	}

	for (size_t i = 0; i < strlen(idText); i++)
	{
		if (!isdigit(idText[i]) && idText[i] != '.')
		{
			val = MessageBoxEx(Window::GetWinHandle(), "ID is not a valid number!\nPlease enter a valid number for inside diameter."
				"\nSee -- Help \\ Info -- for more information.",
				NULL, MB_OKCANCEL | MB_ICONERROR, NULL);

			switch (val)
			{
			case IDCANCEL:
				DestroyWindow(Window::GetWinHandle());
				break;

			case IDOK:
				return 0;
				break;

			}
		}
	}

	// Convert  to double.
	volNum = strtod(volText, NULL);
	idNum = strtod(idText, NULL);

	// Call function to compute the length.
	lengthNum = ComputeLength(volNum, idNum);

	// Convert result to char* arr.
	//sprintf_s(lengthText, "%f", lengthNum);

	lengthString = ToString(lengthNum); // Get the string.
	strcpy_s(lengthText, lengthString.c_str());   // Convert to C-string

	SetWindowText(hLength, lengthText);	// Display the result.


	// Conditional statements for message box text.
	if (lengthNum >= 5 && lengthNum <= 69)
	{
		bMsgRed = 0;
		SetWindowText(hMsgBox, msgStandard);

	}

	else if (lengthNum > 69)
	{
		bMsgRed = 1;
		SetWindowText(hMsgBox, msgLarge);

	}

	else if (lengthNum < 5)
	{
		bMsgRed = 1;
		SetWindowText(hMsgBox, msgTooSmall);

	}

	return 0;
}

void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox)
{
	const char* emptyText = "";

	SetWindowText(hVol, emptyText);
	SetWindowText(hID, emptyText);
	SetWindowText(hLength, emptyText);
	SetWindowText(hMsgBox, emptyText);
}


double ComputeLength(double vol, double id)
{
	const double conversionFactor = 0.06102374;	// Converts cubic centimeters to cubic inches (1cc in ci).
	const double pi = 3.141592654;	// Pi.

	double result;

	result = (vol * conversionFactor) / (pi * ((id / 2) * (id / 2)));

	return result;

}

std::string ToString(double num)
{
	std::stringstream ss;    // Declare a string stream var.

	// Set the decimal point.
	ss.setf(std::ios::fixed);
	ss.setf(std::ios::showpoint);
	ss.precision(3);

	ss << num;

	return ss.str();
}

// Register the window class.
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))	// Gets the handle to the instance.
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 256, 256, 0));
	wc.hCursor = nullptr;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = GetName();
	wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0));;
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


/************************** Window Stuff*******************************/

Window::Window(int width, int height, const char* name)
{
	// Calculate window size based on the desired client region.
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;
	if (AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0)
	{
		throw GTWND_LAST_EXCEPT();
	};

	// Throw a test exception.
	//throw GTWND_EXCEPT(ERROR_ARENA_TRASHED);
	//throw std::runtime_error("Seemore Butts");
	//throw 69;

	// Create a window and get hWnd.
	hWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);

	// Check for error.
	if (hWnd == nullptr)
	{
		throw GTWND_LAST_EXCEPT();
	}

	// Show the window.
	ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(hWnd);
}

HWND Window::GetWinHandle() noexcept
{
	return HWND();
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side.
	if (msg == WM_NCCREATE)
	{
		// Extract ptr to window class from creation data.
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		// Set WinAPI-managed user data to store ptr to window class.
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// Set message proc to normal (non-setup) handler now that setup is finished.
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
		// Forward message to window class handler.
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// If we get a message before the WM_NCCREATE message, handle with default handler.
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	// Retrieve ptr to window class.
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// Forward message to window class handler.
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	LRESULT result = 0;
	bool wasHandled = false;
	int wmId = LOWORD(wParam);
	char eighthTube[100] = "0.0625";
	char sixteenthTube[100] = "0.040";
	char empty[100] = "";

	switch (msg)
	{
	case WM_COMMAND:
	{

		// ComboBox
		if (HIWORD(wParam) == CBN_SELCHANGE)
			// If the user makes a selection from the list:
			//   Send CB_GETCURSEL message to get the index of the selected list item.
			//   Send CB_GETLBTEXT message to get the item.
			//   Display the item in a messagebox.
		{
			int ItemIndex = SendMessage((HWND)lParam, (UINT)CB_GETCURSEL,
				(WPARAM)0, (LPARAM)0);
			TCHAR  ListItem[256];
			(TCHAR)SendMessage((HWND)lParam, (UINT)CB_GETLBTEXT,
				(WPARAM)ItemIndex, (LPARAM)ListItem);
			//MessageBox(hWnd, (LPCWSTR)ListItem, _T("Item Selected"), MB_OK);
			if (ItemIndex == (WPARAM)0)
				SetWindowTextA(hID, eighthTube);
			else if (ItemIndex == (WPARAM)1)
				SetWindowTextA(hID, sixteenthTube);
			else
				SetWindowTextA(hID, empty);

		}

		wasHandled = true;
		result = 0;

		// Parse the menu selections:
		switch (wmId)
		{
		case IDD_DIALOG1:
			DialogBox(WindowClass::GetInstance(), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
			break;

		case IDD_DIALOG2:
			DialogBox(WindowClass::GetInstance(), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Info);
			break;

		case IDM_EXIT:
			if (MessageBox(hWnd, " Are you sure you want to quit?", "Quit?", MB_OKCANCEL | MB_ICONEXCLAMATION) == IDOK)
			{
				DestroyWindow(hWnd);
			}
			break;

		case CLEAR_BUTTON:
			ClearAllText(hVol, hID, hLength, hMsgBox);
			break;

		case CALCULATE_BUTTON:
			CalcLength(hVol, hID, hLength, hMsgBox, bMsgRed);
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
	}
	break;

	case WM_CREATE:
		Interface(hWnd, WindowClass::GetInstance());
		break;

	case WM_SETFOCUS:
		SetFocus(hVol);
		break;

	// Only works when focus is on main window.
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case VK_ESCAPE:
	//		//PostQuitMessage(EXIT_SUCCESS);
	//		MessageBox(NULL, TEXT("Escape Key Down"), TEXT("Key Down"), MB_OK);
	//		break;
	//	}

		return 0;

	case WM_CTLCOLORSTATIC:
	{

		if (bMsgRed && (HWND)lParam == GetDlgItem(hWnd, ID_MSGBOX))
		{
			SetBkColor((HDC)wParam, GetSysColor(COLOR_MENU));
			SetTextColor((HDC)wParam, RGB(230, 0, 0));


			return (LRESULT)GetSysColorBrush(COLOR_MENU);
		}

		else if ((HWND)lParam == GetDlgItem(hWnd, ID_MSGBOX))
		{
			SetBkColor((HDC)wParam, GetSysColor(COLOR_MENU));
			SetTextColor((HDC)wParam, RGB(0, 160, 0));


			return (LRESULT)GetSysColorBrush(COLOR_MENU);
		}
	}

	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;	// Return 0 instead of break to destroy the window using the destructor
					// and not let DefProc handle this message.
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

/************************** Window Exception Stuff ************************************/

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	:
	GTException(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetErrorCode() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{
	return "GT Window Exception";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept
{
	char* pMsgBuf = nullptr;
	// windows will allocate memory for err string and make our pointer point to it
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr
	);
	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = pMsgBuf;
	// free windows buffer
	LocalFree(pMsgBuf);
	return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateErrorCode(hr);
}
