
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/CameraComponent/FreeCameraComponent/FreeCameraComponent.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Component/RenderComponent/RenderComponent.h"
#include "Engine/Core/Core.h"


int main()
{
	
	COpenGLWindow Window = *(ServiceLocator::GetWindow());
	CCore* Core = ServiceLocator::GetCore();

	CGameObject Camera("Camera Game Object");
	Camera.AddComponent<CFreeCameraComponent>();

	CGameObject MainScene("Scene");
	MainScene.AddComponent<CRenderComponent>();
	MainScene.GetComponent<CRenderComponent>()->SetModel("Assets/Models/Garden/garden.obj");

	Core->StartEngine();

	return 0;
}
