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

	// Data Members
private:
	unsigned int MajorVersion;
	unsigned int MinorVersion;
	GLFWwindow* Window = nullptr;

// Member Functions
private:
	static void FrameBufferSizeCallback(GLFWwindow* Window, int Width, int Height);
public:
	void InitializeWindow(std::string WindowName, int Height, int Width, WINDOW_MODE WindowMode) override;
	void CloseWindow() override;
	void SetClearColor(float R, float G, float B, float A) override;
	void Clear() override;
	bool ShouldWindowClose() const override;
	void SwapBuffers() const override;
	bool IsKeyPressed(int GLFWKeyCode) const override;
};