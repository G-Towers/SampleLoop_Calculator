// Widget.cpp

#include "Widget.h"

Widget::Widget()
{}

HWND Widget::RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	hWnd = CreateWindowEx(WS_EX_RIGHT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return hWnd;
}

HWND Widget::LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd)
{
	hWnd = CreateWindowEx(WS_EX_LEFT, "static", text,
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);
	HFONT hfVol = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "MS Sans Serif");
	SendMessage(hWnd, WM_SETFONT, (WPARAM)hfVol, 0);

	return hWnd;
}

HWND Widget::GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst)
{
	hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		posx, posy, width, height, hWnd, nullptr, 
		hInst, nullptr);

	return hWnd;
}

HWND Widget::InputBox(int posx, int posy, int width, int height, HWND hWnd)
{
	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "Edit", "",
		WS_CHILD | WS_VISIBLE | WS_TABSTOP,
		posx, posy, width, height, hWnd, NULL, NULL, NULL);

	return hWnd;
}

HWND Widget::ComboBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst)
{
	hWnd = CreateWindow(
		"COMBOBOX",
		text,
		CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_VISIBLE,
		posx, posy, width, height, hWnd, nullptr, hInst, nullptr);
	//HFONT hfTube = CreateFont(/*size=*/-14, 0, 0, 0, FW_NORMAL, 0, 0, 0,
	//    ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("MS Sans Serif"));
	//SendMessage(hTubeComboBox, WM_SETFONT, (WPARAM)hfTube, 0);

	return hWnd;
}

HWND Widget::Button(int posx, int posy, int width, int height, const char* text, HWND hWnd, HMENU option)
{
	hWnd = CreateWindow(
		"BUTTON",
		text,
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_PUSHBUTTON,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return hWnd;
}

HWND Widget::ResultBox(int posx, int posy, int width, int height, HWND hWnd)
{
	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, nullptr, nullptr, nullptr);

	return hWnd;
}

HWND Widget::MsgBox(int posx, int posy, int width, int height, HWND hWnd)
{
	CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, (HMENU)ID_MSGBOX, nullptr, nullptr);

	return HWND();
}

void Widget::Interface(HWND hWnd, HINSTANCE hInst)
{
	// Call Widget functions to draw the interface. 
	GroupBox(15, 10, 285, 220, "Volume and ID Information", hWnd, hInst);
	RLabel(45, 50, 120, 30, "Enter Volume in Cubic Centemeters: ", hWnd);
	hVol = InputBox(180, 55, 100, 25, hWnd);
	LLabel(25, 100, 220, 30, "Select Tubing: ", hWnd);
	hTubeComboBox = ComboBox(25, 120, 265, 150, "", hWnd, hInst);
	RLabel(20, 170, 150, 30, "Enter inside diameter of tube in inches: ", hWnd);
	hID = InputBox(180, 175, 100, 25, hWnd);
	hClrBtn = Button(15, 255, 100, 30, "Clear", hWnd, (HMENU)CLEAR_BUTTON);
	hCalcBtn = Button(200, 255, 100, 30, "Calculate", hWnd, (HMENU)CALCULATE_BUTTON);
	GroupBox(15, 305, 285, 175, "Sample Loop Results", hWnd, hInst);
	RLabel(20, 350, 120, 60, "The length of your sample loop is: ", hWnd);
	hLength = ResultBox(150, 355, 80, 25, hWnd);
	LLabel(240, 365, 50, 25, "inches.", hWnd);
	hMsgBox = MsgBox(30, 415, 255, 40, hWnd);

}


