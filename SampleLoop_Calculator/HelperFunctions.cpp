// HelperFunctions.cpp

#include "HelperFunctions.h"

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