// Widget.h

#pragma once
#include "Window.h"


namespace Widget
{
	HWND RLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND LLabel(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND GroupBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);
	HWND InputBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND ComboBox(int posx, int posy, int width, int height, const char* text, HWND hWnd, HINSTANCE hInst);
	HWND Button(int posx, int posy, int width, int height, const char* text, HWND hWnd);
	HWND ResultBox(int posx, int posy, int width, int height, HWND hWnd);
	HWND MsgBox(int posx, int posy, int width, int height, HWND hWnd);

	void Interface(HWND hWnd, HINSTANCE hInst);
}

