#include "LightManager.h"
#include "../Constants/ShaderConstants.h"
#include <assert.h>

void LightManager::RegisterDirectionalLight(CDirectionalLightComponent* InDirectionalLight)
{
	DirectionLight = InDirectionalLight;
}

void LightManager::RegisterFlashLight(CFlashLightComponent* InFlashLightComponent)
{
	FlashLightComponent = InFlashLightComponent;
}

void LightManager::RegisterPointLight(CPointLightComponent* InPointLightComponent)
{
	assert(PointLightComponents.size() != ShaderConstants::MAX_POINT_LIGHTS); // Max lights reached. Cannot add more lights
	PointLightComponents.push_back(InPointLightComponent);
}

void LightManager::UnregisterPointLight(CPointLightComponent* InPointLightComponent)
{
	assert(InPointLightComponent != nullptr); // nullptr passed as point light
	
	for (auto i = PointLightComponents.begin(); i != PointLightComponents.end(); i++)
	{
		if (*i == InPointLightComponent)
		{
			PointLightComponents.erase(i);
			return;
		}
	}
}

