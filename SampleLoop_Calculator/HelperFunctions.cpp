// HelperFunctions.cpp

#include "HelperFunctions.h"

int CalcLength(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox)
{
	int val;
	double volNum, idNum, lengthNum;
	char volText[100], idText[100], lengthText[100];
	std::string lengthString;


	TCHAR msgStandard[100] = { _T(" A standard size.") };
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
	volNum = strtod(volText, nullptr);
	idNum = strtod(idText, nullptr);

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