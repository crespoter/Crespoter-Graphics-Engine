#include "ObjectReferenceManager.h"
#include <assert.h>

bool CObjectReferenceManager::bIsInitialized = false;

CObjectReferenceManager::CObjectReferenceManager()
{
	assert(!bIsInitialized); // The object has already been initialized.
	bIsInitialized = true;
}

CObjectReferenceManager::~CObjectReferenceManager()
{
	bIsInitialized = false;
}

void CObjectReferenceManager::AddGameObject(CGameObject* InGameObject)
{
	assert(InGameObject != nullptr);
	GameObjects.push_back(InGameObject);
}

void CObjectReferenceManager::AddRenderComponent(CRenderComponent* InRenderComponent)
{
	assert(InRenderComponent != nullptr);
	RenderComponents.push_back(InRenderComponent);
}

void CObjectReferenceManager::RemoveGameObect(CGameObject* InGameObject)
{
	assert(InGameObject != nullptr); // nullptr passed as point light

	for (auto i = GameObjects.begin(); i != GameObjects.end(); i++)
	{
		if (*i == InGameObject)
		{
			GameObjects.erase(i);
			return;
		}
	}
}

void CObjectReferenceManager::RemoveRenderComponent(CRenderComponent* InRenderComponent)
{
	assert(InRenderComponent != nullptr);
	for (auto i = RenderComponents.begin(); i != RenderComponents.end(); i++)
	{
		if (*i == InRenderComponent)
		{
			RenderComponents.erase(i);
			return;
		}
	}
}

