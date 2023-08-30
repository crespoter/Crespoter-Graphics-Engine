#pragma once

class IWindowInterface;
class CShaderProgram;

class CCore
{
public:
	CCore();
	~CCore();
	void StartEngine();
private:
	float LastTime = 0.0f;
	IWindowInterface* Window = nullptr;
	CShaderProgram* MainRenderShader = nullptr;
};