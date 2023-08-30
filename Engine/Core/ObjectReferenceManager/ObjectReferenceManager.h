#pragma once
#include <vector>

class CGameObject;
class CRenderComponent;
class ServiceLocator;
class CCore;
class CSkybox;
class CPointLightComponent;
class CDirectionalLightComponent;


// TODO: Also store all available cameras here.
// This might be a better place to store the active camera too instead of service locator.

class CObjectReferenceManager
{
friend ServiceLocator; 
friend CCore;

public:

	void AddGameObject(CGameObject* InGameObject);
	void RemoveGameObect(CGameObject* InGameObject);

	void AddRenderComponent(CRenderComponent* InRenderComponent);
	void RemoveRenderComponent(CRenderComponent* InRenderComponent);

	void AddPointLightComponent(CPointLightComponent* InPointLightComponent);
	void RemovePointLightComponent(CPointLightComponent* InPointLightComponent);

	void UpdateDirectionalLightComponent(CDirectionalLightComponent* InDirectionalLightComponent);
	
	void UpdateSkybox(CSkybox* InSkybox);

private:
	CObjectReferenceManager() = default;

	std::vector<CGameObject*> GameObjects;
	std::vector<CRenderComponent*> RenderComponents;
	std::vector<CPointLightComponent*> PointLightComponents;
	CDirectionalLightComponent* DirectionalLightComponent = nullptr;
	CSkybox* Skybox = nullptr;
};