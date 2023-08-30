#pragma once
#include <glm/glm.hpp>

// TODO: This could be loaded from a config file instead of being set here.

struct FLightAttenuation
{
	// Default values for distance up to 50 units.
	// Refer http://www.ogre3d.org/tikiwiki/tiki-index.php?page=-Point+Light+Attenuation
	float ConstantCoeff = 1.0f;
	float LinearCoeff = 0.07f;
	float QuadraticCoeff = 0.017f;
};

struct FLightProperties
{
	glm::vec3 AmbientColor = glm::vec3(0.0f);
	glm::vec3 DiffuseColor = glm::vec3(0.0f);
	glm::vec3 SpecularColor = glm::vec3(0.0f);
};

struct FPointLightProperties : FLightProperties
{
	FLightAttenuation LightAttenuation;
};

struct FDirectionalLightProperties : FLightProperties
{
	glm::vec3 LightDirection = glm::vec3(1.0f);
};