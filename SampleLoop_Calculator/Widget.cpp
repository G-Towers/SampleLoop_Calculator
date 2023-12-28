// Interface.cpp

#include "Widget.h"


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

HWND Widget::MsgBox(int posx, int posy, int width, int height, HWND hWnd, HMENU option)
{
	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE, "static", "",
		WS_VISIBLE | WS_CHILD,
		posx, posy, width, height, hWnd, option, nullptr, nullptr);

	return hWnd;
}




