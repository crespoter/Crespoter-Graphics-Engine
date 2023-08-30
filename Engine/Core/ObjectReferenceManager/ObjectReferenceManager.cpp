#include "ObjectReferenceManager.h"
#include <assert.h>
#include "Engine/Constants/ShaderConstants.h"


void CObjectReferenceManager::AddGameObject(CGameObject* InGameObject)
{
	assert(InGameObject);
	assert(std::find(GameObjects.begin(), GameObjects.end(), InGameObject) == GameObjects.end());
	GameObjects.push_back(InGameObject);
}

void CObjectReferenceManager::AddRenderComponent(CRenderComponent* InRenderComponent)
{
	assert(InRenderComponent);
	assert(std::find(RenderComponents.begin(), RenderComponents.end(), InRenderComponent) == RenderComponents.end());
	RenderComponents.push_back(InRenderComponent);
}

void CObjectReferenceManager::RemoveGameObect(CGameObject* InGameObject)
{
	assert(InGameObject);
	GameObjects.erase(std::remove(GameObjects.begin(), GameObjects.end(), InGameObject),
		GameObjects.end());
}

void CObjectReferenceManager::RemoveRenderComponent(CRenderComponent* InRenderComponent)
{
	assert(InRenderComponent);
	RenderComponents.erase(std::remove(RenderComponents.begin(), RenderComponents.end(), InRenderComponent),
		RenderComponents.end());
}

void CObjectReferenceManager::AddPointLightComponent(CPointLightComponent* InPointLightComponent)
{
	// TODO: Support point lights without a maximum limit
	assert(InPointLightComponent);
	assert(PointLightComponents.size() < ShaderConstants::MAX_POINT_LIGHTS); // Maximum permitted point lights exceeded
	PointLightComponents.push_back(InPointLightComponent);
}

void CObjectReferenceManager::RemovePointLightComponent(CPointLightComponent* InPointLightComponent)
{
	assert(InPointLightComponent != nullptr);
	PointLightComponents.erase(std::remove(PointLightComponents.begin(), PointLightComponents.end(), InPointLightComponent),
		PointLightComponents.end());
}


void CObjectReferenceManager::UpdateDirectionalLightComponent(CDirectionalLightComponent* InDirectionalLightComponent)
{
	// Directional light could be nullptr to imply no directional light.
	DirectionalLightComponent = InDirectionalLightComponent;
}

void CObjectReferenceManager::UpdateSkybox(CSkybox* InSkybox)
{
	// Skybox can be nullptr to not draw a skybox
	Skybox = InSkybox;
}
