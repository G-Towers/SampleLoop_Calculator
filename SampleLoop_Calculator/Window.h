// Window.h

#pragma once

#include <Windows.h>
#include "GTException.h"
#include "resource.h"

// Global variables.
extern HWND hVol, hID, hClrBtn, hCalcBtn, hLength, hMsgBox, hTubeComboBox;	
extern BOOL bMsgRed;


// Dialog Box Procs
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Info(HWND, UINT, WPARAM, LPARAM);

// Helper functions.
void Interface(HWND hWnd, HINSTANCE hInst);
int CalcLength(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox, BOOL bMsgRed);
void ClearAllText(HWND hVol, HWND hID, HWND hLength, HWND hMsgBox);
double ComputeLength(double vol, double id);
std::string ToString(double);

// Encapsulates the creation and destruction of the window and handles messages.
class Window
{
public:
	class Exception : public GTException
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateErrorCode(HRESULT hr) noexcept;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

private:
	// Singleton that manages the registration and cleanup of window class.
	class WindowClass
	{
	public:
		static const char* GetName() noexcept;	// Gets the name of the class.
		static HINSTANCE GetInstance() noexcept;	// Gets the handle to the instance.
	private:
		WindowClass() noexcept;	// Registers the windows class.
		~WindowClass();	// Unregisters the class.
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "SampleLoopCalc";
		static WindowClass wndClass;
		HINSTANCE hInst;	// Stores the handle to the instance.
	};
public:
	Window(int width, int height, const char* name); // Constructs the window.
	~Window();	// Destroys the window.
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	static HWND GetWinHandle() noexcept;

private:
	static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	// Setup a pointer to the instance of the class.
	 
	static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	// Forward the pointer to HandleMsg().

	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	// Handles all windows messages.

private:
	int width;
	int height;
	//static Window wnd;
	HWND hWnd;	// The handle to the window.

};

// Error exception helper macros.
#define GTWND_EXCEPT( hr ) Window::Exception( __LINE__,__FILE__,hr )
#define GTWND_LAST_EXCEPT() Window::Exception( __LINE__,__FILE__,GetLastError() )
