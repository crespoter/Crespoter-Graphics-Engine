#pragma once
#include "../../Component.h"
#include <string>
#include "../LightData.h"

static const std::string DIRECTIONAL_LIGHT_DEFAULT_NAME = "DirectionalLight";

class CDirectionalLightComponent : public IComponent
{
public:
	CDirectionalLightComponent(const std::string& ComponentName = DIRECTIONAL_LIGHT_DEFAULT_NAME);
	~CDirectionalLightComponent();
	void SetLightProperties(const FDirectionalLightProperties& InLightProperties);
	void SetLightProperties(glm::vec3 AmbientColor, glm::vec3 DiffuseColor, glm::vec3 SpecularColor, glm::vec3 Direction);

	glm::vec3 GetAmbientColor();
	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	glm::vec3 GetLightDirection();
private:
	FDirectionalLightProperties LightProperties;
};