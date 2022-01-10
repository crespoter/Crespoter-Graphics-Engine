#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../WindowInterface.h"


/**
 * Class responsible for initializing window for opengl and handling its context. Also handles keyboard and mouse inputs
 */
class COpenGLWindow : public IWindowInterface
{
public:
	COpenGLWindow(unsigned int MajorVersion, unsigned int MinorVersion);

	~COpenGLWindow();

	/**
	* Pass NULL for Height and Window to initialize resolution to monitors resolution
	*/
	void InitializeWindow(std::string WindowName, int Height, int Width, WINDOW_MODE WindowMode) override;
	
	/**
	* Closes this window
	*/
	void CloseWindow() override;
	
	/**
	* Sets the clear color. This value would be used when clearing the screen.
	*/
	void SetClearColor(float R, float G, float B, float A) override;
	
	/**
	* Clears the screen
	*/
	void Clear() override;
	
	/**
	* A boolean check to see if window is closing or already has closed
	*/
	bool ShouldWindowClose() const override;

	/**
	* Swaps the buffers.
	*/
	void SwapBuffers() const override;
 
	/**
	* Checks if the provided keycode is pressed.
	* @param GLFWKeyCode - Key code of the key to check. Refer https://www.glfw.org/docs/3.3/group__keys.html for list of key codes
	*/
	bool IsKeyPressed(int GLFWKeyCode) const override;
	
	/**
	* Gets the current mouse position. The cooridnates are in pixels of the rendering screen
	*/
	FMousePosition GetMousePosition() const override;

	/**
	* Gets the current aspect ratio.
	*/
	float GetAspectRatio() const override;

private:
	unsigned int MajorVersion;
	unsigned int MinorVersion;
	GLFWwindow* Window = nullptr;
	static void FrameBufferSizeCallback(GLFWwindow* Window, int Width, int Height);
};