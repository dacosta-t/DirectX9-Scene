#pragma once
#include <windows.h>
#include <string>

#include "Includes.h"

class GameEngine;

/**
	Window
	Emulates a window to display the game on.
*/
class Window {
public:
	/** Handles messages passed to the window. 
	
		@param hwnd - Handle to the window
		@param uMessage - Message being passed
		@param wParam - Additional information passed
		@param lParam - Additional information passed
		
		@return Result of the message processing
	*/
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

	/** Contructs objects of type Window.
		Creates and registers a window to the operating system.
		
		@param hInstance - Handle to the instance
		@param title - Text to display on the window bar
	*/
	Window(const HINSTANCE hInstance, const std::string title);

	/** Default destructor. */
	virtual ~Window() = default;
	
	/** Gets the handle to the window.
		
		@return Handle to the window
	*/
	HWND GetHwnd() const;

	/** Displays the window.
		
		@return Pass or fail result of window displaying
	*/
	bool Show() const;

	/** Passes message to update/repaint the window immediately.
		
		@return Pass or fail result of window updating
	*/
	bool Update() const;

	/** Sets the game engine.
		
		@param game - Game engine
	*/
	void SetGameEngine(const GameEngine* engine);

private:
	HWND mHwnd; // Handle to the window
};