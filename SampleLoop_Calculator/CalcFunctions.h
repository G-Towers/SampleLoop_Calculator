// CalcFunctions.h

#pragma once
#include "Window.h"
#include "Widget.h"
#include <string>
#include <sstream>


class CalcFunctions
{
public:

	int CalcLength(Widget& obj);
	void ClearAllText(Widget& obj);
	double ComputeLength(double vol, double id);
	std::string ToString(double);

public:
	const double CONVERSION_FACTOR = 0.06102374;    // Converts cubic centimeters to cubic inches (1cc in ci).
	const double PI = 3.141592654;                  // Pi.

};
