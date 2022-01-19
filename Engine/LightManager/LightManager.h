#pragma once
#include<iostream>
#include<vector>

class CDirectionalLightComponent;
class CFlashLightComponent;
class CPointLightComponent;

/**
 * Class used to track all the lighting objects in the screen
 */
class LightManager
{
public:
	/**
	 * Registers the directional light
	 * @param InDirectionalLight : Directional light component to register
	 * Pass nullptr to unregister
	 */
	void RegisterDirectionalLight(CDirectionalLightComponent* InDirectionalLight);
	
	/**
	 * Registers the flash light
	 * @param InFlashLight: Flash light component to register
	 * Pass nullptr to unregister
	*/
	void RegisterFlashLight(CFlashLightComponent* InFlashLightComponent);

	/**
	* Registers a point light. Multiple point lights can be added
	* @param InPointLight: Point light component to register
	*/
	void RegisterPointLight(CPointLightComponent* InPointLightComponent);

	/**
	 * Unregisters a point light
	 * @param InPointLight: Point light component to unregister
	 */
	void UnregisterPointLight(CPointLightComponent* InPointLightComponent);

private:	
	CDirectionalLightComponent* DirectionLight;
	CFlashLightComponent* FlashLightComponent;
	std::vector<CPointLightComponent*> PointLightComponents;
};
