// HelperFunctions.h

#pragma once

#include "Window.h"

// Helper functions.
void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox);
// Clears all text boxes and resets the combobox.

double ComputeLength(double vol, double id);
// Returns the length of the length of the sample loop in inches.
// Takes the volume and inside diameter as parameters.

std::string ToString(double);
// Convert double to string.