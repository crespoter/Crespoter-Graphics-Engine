#pragma once
#include "../../Component.h"
#include "../LightData.h"
#include <string>

static const std::string DIRECTIONAL_LIGHT_DEFAULT_NAME = "DirectionalLight";

class CDirectionalLightComponent : public IComponent
{
public:
	explicit CDirectionalLightComponent(const std::string& ComponentName = DIRECTIONAL_LIGHT_DEFAULT_NAME);
	~CDirectionalLightComponent();
	void SetLightProperties(const FDirectionalLightProperties& InLightProperties);
	void SetLightProperties(const glm::vec3& AmbientColor, const glm::vec3& DiffuseColor, const glm::vec3& SpecularColor, const glm::vec3& Direction);

	glm::vec3 GetAmbientColor() const;
	glm::vec3 GetDiffuseColor() const;
	glm::vec3 GetSpecularColor() const;
	glm::vec3 GetLightDirection() const;
private:
	FDirectionalLightProperties LightProperties;
};