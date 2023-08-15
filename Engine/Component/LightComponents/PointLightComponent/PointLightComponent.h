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
	virtual ~CPointLightComponent();
	void SetLightProperties(const FPointLightProperties &InLightProperties);
	void SetLightProperties(const glm::vec3& AmbientColor, const glm::vec3& DiffuseColor, const glm::vec3& SpecularColor);
	void UpdateLightAttenuationProperty(const FLightAttenuation& UpdatedLightAttenuation);
	void UpdateLightAttenuationProperty(const float ConstantCoeff, const float LinearCoeff, const float QuadraticCoeff);

	glm::vec3 GetAmbientColor() const;
	glm::vec3 GetDiffuseColor() const;
	glm::vec3 GetSpecularColor() const;
	glm::vec3 GetLightPosition() const;

	float GetLinearAttenuationCoeff() const;
	float GetConstantAttenuationCoeff() const;
	float GetQuadraticAttenuationCoeff() const;

private:
	FPointLightProperties LightProperties;
};