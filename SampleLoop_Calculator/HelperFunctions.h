// HelperFunctions.h

#pragma once

#include "Window.h"

// Helper functions.
void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox);
double ComputeLength(double vol, double id);
std::string ToString(double);