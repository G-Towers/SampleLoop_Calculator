// HelperFunctions.cpp

#include "HelperFunctions.h"

void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox)
{
	const char* emptyText = "";

	SetWindowText(hVol, emptyText);
	SetWindowText(hID, emptyText);
	SetWindowText(hLength, emptyText);
	SetWindowText(hMsgBox, emptyText);
	SendMessage(hComboBoxSelTb, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);	// Set to "User Defined".
	SetFocus(hInBxVol);	// Set focus to Volume box.
}

double ComputeLength(double vol, double id)
{
	const double conversionFactor = 0.06102374;	// To convert cubic centimeters to cubic inches (1cc in ci).
	const double pi = 3.141592654;

	double result = (vol * conversionFactor) / (pi * ((id / 2) * (id / 2)));

	return result;

}

std::string ToString(double num)
{
	std::stringstream ss;    // Declare a string stream var.

	// Set the decimal point.
	ss.setf(std::ios::fixed);
	ss.setf(std::ios::showpoint);
	ss.precision(3);

	ss << num;	// Output to stream.

	return ss.str();	// Return as string.
}
