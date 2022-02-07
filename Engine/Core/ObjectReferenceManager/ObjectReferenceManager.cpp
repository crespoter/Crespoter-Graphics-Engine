#include "ObjectReferenceManager.h"
#include <assert.h>
#include "../../Constants/ShaderConstants.h"

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

void CObjectReferenceManager::AddPointLightComponent(CPointLightComponent* InPointLightComponent)
{
	assert(InPointLightComponent != nullptr);
	assert(PointLightComponents.size() < ShaderConstants::MAX_POINT_LIGHTS); // Maximum permitted point lights exceeded
	PointLightComponents.push_back(InPointLightComponent);
}

void CObjectReferenceManager::RemovePointLightComponent(CPointLightComponent* InPointLightComponent)
{
	assert(InPointLightComponent != nullptr);
	for (auto i = PointLightComponents.begin(); i != PointLightComponents.end(); i++)
	{
		if (*i == InPointLightComponent)
		{
			PointLightComponents.erase(i);
			return;
		}
	}
}


void CObjectReferenceManager::UpdateDirectionalLightComponent(CDirectionalLightComponent* InDirectionalLightComponent)
{
	DirectionalLightComponent = InDirectionalLightComponent;
}

void CObjectReferenceManager::UpdateSkybox(CSkybox* InSkybox)
{
	Skybox = InSkybox;
}
