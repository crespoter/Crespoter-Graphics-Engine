#include "ServiceLocator.h"
#include <assert.h>
#include "../ShaderProgram/ShaderProgram.h"
#include "../Core/Core.h"
#include "../Core/ObjectReferenceManager/ObjectReferenceManager.h"

CCameraComponent* ServiceLocator::ActiveCamera = nullptr;
CShaderProgram* ServiceLocator::MainRenderShader = nullptr;
CCore ServiceLocator::Core;
CObjectReferenceManager ServiceLocator::ObjectReferenceManager;
COpenGLWindow* ServiceLocator::Window = nullptr;


void ServiceLocator::Provide(COpenGLWindow* InWindow)
{
	Window = InWindow;
}

void ServiceLocator::Provide(CShaderProgram* InMainRenderShaderProgram)
{
	MainRenderShader = InMainRenderShaderProgram;
}


void ServiceLocator::Provide(CCameraComponent* InActiveCamera)
{
	ActiveCamera = InActiveCamera;
}

CCameraComponent* ServiceLocator::GetActiveCamera()
{
	return ActiveCamera;
}

CShaderProgram* ServiceLocator::GetMainShaderProgram()
{
	return MainRenderShader;
}

COpenGLWindow* ServiceLocator::GetWindow()
{
	return Window;
}

CCore* ServiceLocator::GetCore()
{
	return &Core;
}

CObjectReferenceManager* ServiceLocator::GetObjectReferenceManager()
{
	return &ObjectReferenceManager;
}
