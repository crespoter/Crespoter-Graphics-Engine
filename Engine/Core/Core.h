#pragma once

class COpenGLWindow;
class CShaderProgram;

class CCore
{
public:
	CCore();
	~CCore();
	void StartEngine();
private:
	float LastTime = 0.0f;
	COpenGLWindow* Window = nullptr;
	CShaderProgram* MainRenderShader = nullptr;
};