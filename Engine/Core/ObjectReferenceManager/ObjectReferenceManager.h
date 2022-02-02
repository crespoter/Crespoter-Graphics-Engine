#pragma once
#include <vector>

class CGameObject;
class CRenderComponent;
class ServiceLocator;
class CCore;
class CPointLightComponent;
class CDirectionalLightComponent;

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
	
private:
	CObjectReferenceManager();
	~CObjectReferenceManager();
	static bool bIsInitialized;
	std::vector<CGameObject*> GameObjects;
	std::vector<CRenderComponent*> RenderComponents;
	std::vector<CPointLightComponent*> PointLightComponents;
	CDirectionalLightComponent* DirectionalLightComponent = nullptr;
};