
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/CameraComponent/FreeCameraComponent/FreeCameraComponent.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Component/RenderComponent/RenderComponent.h"
#include "Engine/Core/Core.h"
#include "Engine/Component/LightComponents/PointLightComponent/PointLightComponent.h"
#include "Engine/Component/LightComponents/DirectionalLightComponent/DirectionalLightComponent.h"
#include "Engine/Skybox/Skybox.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"
#include "Engine/Window/WindowInterface.h"

int main()
{
	
	IWindowInterface* Window = (ServiceLocator::GetWindow());
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
	PointLight.GetComponent<CTransformationComponent>()->MoveTo(glm::vec3(-4.0f, 1.5f, -4.0f));
	PointLight.GetComponent<CPointLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Second point light
	CGameObject PointLight2("Red Light 2");
	PointLight2.AddComponent<CPointLightComponent>();
	PointLight2.GetComponent<CTransformationComponent>()->MoveTo(glm::vec3(-1.0f, 1.5f, -4.0f));

	PointLight2.GetComponent<CPointLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Third point light
	CGameObject PointLight3("Red Light 3");
	PointLight3.AddComponent<CPointLightComponent>();
	PointLight3.GetComponent<CTransformationComponent>()->Scale(glm::vec3(0.05, 0.05, 0.05));
	PointLight3.GetComponent<CTransformationComponent>()->MoveTo(glm::vec3(1.0f, 2.5f, -2.5f));

	PointLight2.GetComponent<CPointLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.8f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	// Directional Light
	CGameObject DirectionalLight("Directional Light");
	DirectionalLight.AddComponent<CDirectionalLightComponent>();
	DirectionalLight.GetComponent<CDirectionalLightComponent>()->SetLightProperties(glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, -0.5f, 0.5f));

	// Skybox
	CSkybox Skybox("Assets/Textures/Cubemaps/skybox");

	Core->StartEngine();

	return 0;
}
