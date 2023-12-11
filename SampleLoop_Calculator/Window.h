// Window.h

#pragma once

#include <Windows.h>

// Encapsulates the creation and destruction of the window and handles messages.
class Window
{
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
	Window(int width, int height, const char* name) noexcept; // Constructs the window.
	~Window();	// Destroys the window.
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
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
	HWND hWnd;	// The handle to the window.
};
