#pragma once
#include <iostream>
/**
 * Abstract class for window handling. Window application classes are expected to override all required functionalities. Also handles inputs
 */
class IWindowInterface
{
protected:
	IWindowInterface() {};
	unsigned int CurrentHeight = 0;
	unsigned int CurrentWidth = 0;
	bool bIsInitialized = false;
public:
	/**
	 * Window mode to be used
	 */
	enum class WINDOW_MODE
	{
		FULL_SCREEN,
		WINDOWED,
		BORDERLESS
	};
	
	/*
	* Function used to create a window
	* @param Height of window
	* @param Width of window
	* @param WindowMode: Type of window mode - Fullscreen, Windowed or Borderless
	*/
	virtual void InitializeWindow(std::string WindowName, int Height, int Width, WINDOW_MODE WindowMode) = 0;
	
	/**
	 * Closes window
	 */
	virtual void CloseWindow() = 0;
	
	/*
	* Sets the clear color to be used by ClearColor() function
	*/
	virtual void SetClearColor(float R, float G, float B, float A) = 0;
	
	/**
	 * Clears the screen and any buffers being used
	 */
	virtual void Clear() = 0;
	
	/**
	 * Closes window
	 */
	virtual bool ShouldWindowClose() const = 0;
	
	/**
	 * Swaps buffers
	 */
	virtual void SwapBuffers() const = 0;
	
	/**
	 * Returns if the window has been initialized or not
	 */
	virtual bool IsInitialized() const;

	/**
	 * Returns true if the key provided is pressed, false otherwise
	 */
	virtual bool IsKeyPressed(int GLFWKeyCode) const = 0;
};