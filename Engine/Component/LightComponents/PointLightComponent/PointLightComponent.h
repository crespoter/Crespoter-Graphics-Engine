#pragma once
#include "../../Component.h"
#include <string.h>
#include "../LightData.h"
namespace
{
	const std::string POINT_LIGHT_DEFAULT_NAME = "Point Light";
}

class CPointLightComponent : public IComponent
{
public:
	CPointLightComponent(const std::string &ComponentName = POINT_LIGHT_DEFAULT_NAME);
	~CPointLightComponent();
	void SetLightProperties(const FPointLightProperties &InLightProperties);
	void SetLightProperties(glm::vec3 AmbientColor, glm::vec3 DiffuseColor, glm::vec3 SpecularColor);
	void UpdateLightAttenuationProperty(FLightAttenuation UpdatedLightAttenuation);
	void UpdateLightAttenuationProperty(float ConstantCoeff, float LinearCoeff, float QuadraticCoeff);

	glm::vec3 GetAmbientColor();
	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	glm::vec3 GetLightPosition();

	float GetLinearAttenuationCoeff();
	float GetConstantAttenuationCoeff();
	float GetQuadraticAttenuationCoeff();

private:
	FPointLightProperties LightProperties;
};