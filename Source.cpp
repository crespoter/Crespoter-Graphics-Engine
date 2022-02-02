
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/CameraComponent/FreeCameraComponent/FreeCameraComponent.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Component/RenderComponent/RenderComponent.h"
#include "Engine/Core/Core.h"
#include "Engine/Component/LightComponents/PointLightComponent/PointLightComponent.h"
#include "Engine/Component/LightComponents/DirectionalLightComponent/DirectionalLightComponent.h"


int main()
{
	
	COpenGLWindow Window = *(ServiceLocator::GetWindow());
	CCore* Core = ServiceLocator::GetCore();

	// Camera game object
	CGameObject Camera("Camera Game Object");
	Camera.AddComponent<CFreeCameraComponent>();

	// Scene game object
	CGameObject MainScene("Scene");
	MainScene.AddComponent<CRenderComponent>();
	MainScene.GetComponent<CRenderComponent>()->SetModel("Assets/Models/Garden/garden.obj");

	// Point light game object
	CGameObject PointLight("Red Light");
	PointLight.AddComponent<CPointLightComponent>();
	PointLight.GetComponent<CPointLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Directional Light
	CGameObject DirectionalLight("Directional Light");
	DirectionalLight.AddComponent<CDirectionalLightComponent>();
	DirectionalLight.GetComponent<CDirectionalLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, -0.5f, 0.5f));

	Core->StartEngine();

	return 0;
}
