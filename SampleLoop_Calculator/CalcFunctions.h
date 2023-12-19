// CalcFunctions.h

#pragma once
#include "Window.h"
#include <string>
#include <sstream>

const double CONVERSION_FACTOR = 0.06102374;    // Converts cubic centimeters to cubic inches (1cc in ci).
const double PI = 3.141592654;                  // Pi.

namespace CalcFunctions
{
	int CalcLength(HWND hWnd, HWND hVol, HWND hID, HWND hLength, HWND hMsgBox);
	void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox);
	double ComputeLength(double vol, double id);
	std::string ToString(double);
}
