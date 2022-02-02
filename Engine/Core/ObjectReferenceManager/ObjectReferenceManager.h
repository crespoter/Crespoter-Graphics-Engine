#pragma once
#include <vector>

class CGameObject;
class CRenderComponent;
class ServiceLocator;
class CCore;

class CObjectReferenceManager
{
friend ServiceLocator; 
friend CCore;

public:

	void AddGameObject(CGameObject* InGameObject);
	void AddRenderComponent(CRenderComponent* InRenderComponent);

	void RemoveGameObect(CGameObject* InGameObject);
	void RemoveRenderComponent(CRenderComponent* InRenderComponent);

private:
	CObjectReferenceManager();
	~CObjectReferenceManager();
	static bool bIsInitialized;
	std::vector<CGameObject*> GameObjects;
	std::vector<CRenderComponent*> RenderComponents;
};