#include "ServiceLocator.h"
#include <assert.h>
#include "../ShaderProgram/ShaderProgram.h"
#include "../Core/Core.h"
#include "../Core/ObjectReferenceManager/ObjectReferenceManager.h"
#include <Engine/Window/WindowInterface.h>

CCameraComponent* ServiceLocator::ActiveCamera = nullptr;
CShaderProgram* ServiceLocator::MainRenderShader = nullptr;
CCore ServiceLocator::Core;
CObjectReferenceManager ServiceLocator::ObjectReferenceManager;
IWindowInterface* ServiceLocator::Window = nullptr;


void ServiceLocator::Provide(IWindowInterface* InWindow)
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

IWindowInterface* ServiceLocator::GetWindow()
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
