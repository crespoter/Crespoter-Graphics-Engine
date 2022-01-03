#include "OpenGLWindow.h"
#include <assert.h>
#include <GLFW/glfw3.h>

COpenGLWindow::COpenGLWindow(unsigned int InMajorVersion, unsigned int InMinorVersion)
{
	MajorVersion = InMajorVersion;
	MinorVersion = InMinorVersion;
}


COpenGLWindow::~COpenGLWindow()
{
	glfwTerminate();
}


void COpenGLWindow::FrameBufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
	glViewport(0, 0, Width, Height);
}


void COpenGLWindow::InitializeWindow(std::string WindowName, int Height, int Width, WINDOW_MODE WindowMode)
{
	// TODO : Handle Borderless and fullscreen window modes
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, MajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, MinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	Window = glfwCreateWindow(Height, Width, WindowName.c_str(), NULL, NULL);
	CurrentWidth = Width;
	CurrentHeight = Height;
	if (Window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		return;
	}
	glfwMakeContextCurrent(Window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, Height, Width);
	glfwSetFramebufferSizeCallback(Window, COpenGLWindow::FrameBufferSizeCallback);
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	glEnable(GL_DEPTH_TEST);
	bIsInitialized = true;
}

void COpenGLWindow::CloseWindow()
{
	assert(bIsInitialized);
	glfwSetWindowShouldClose(Window, true);
}

void COpenGLWindow::Clear()
{
	assert(bIsInitialized);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool COpenGLWindow::ShouldWindowClose() const
{
	assert(bIsInitialized);
	return glfwWindowShouldClose(Window);
}

void COpenGLWindow::SwapBuffers() const
{
	assert(bIsInitialized);
	glfwSwapBuffers(Window);
}

void COpenGLWindow::SetClearColor(float R, float G, float B, float A)
{
	assert(bIsInitialized);
	glClearColor(R, G, B, A);
}


bool COpenGLWindow::IsKeyPressed(int GLFWKeyCode) const
{
	return glfwGetKey(Window, GLFWKeyCode) == GLFW_PRESS;
}

COpenGLWindow::FMousePosition COpenGLWindow::GetMousePosition() const
{
	double PosX, PosY;
	glfwGetCursorPos(Window, &PosX, &PosY);
	FMousePosition MousePosition((float)PosX, (float)PosY);
	return MousePosition;
}

float COpenGLWindow::GetAspectRatio() const
{
	int Width, Height;
	glfwGetWindowSize(Window, &Width, &Height);
	return (float)Width / (float)Height;
}