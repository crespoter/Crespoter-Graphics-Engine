#pragma once
#include "Engine/Component/Component.h"
#include "Engine/Component/LightComponents/LightData.h"
#include <string>

static const std::string DIRECTIONAL_LIGHT_DEFAULT_NAME = "DirectionalLight";

class CDirectionalLightComponent : public IComponent
{
public:
	explicit CDirectionalLightComponent(const std::string& ComponentName = DIRECTIONAL_LIGHT_DEFAULT_NAME);
	~CDirectionalLightComponent();
	void SetLightProperties(const FDirectionalLightProperties& InLightProperties);
	void SetLightProperties(const glm::vec3& AmbientColor, const glm::vec3& DiffuseColor, const glm::vec3& SpecularColor, const glm::vec3& Direction);

	[[nodiscard]] glm::vec3 GetAmbientColor() const;
	[[nodiscard]] glm::vec3 GetDiffuseColor() const;
	[[nodiscard]] glm::vec3 GetSpecularColor() const;
	[[nodiscard]] glm::vec3 GetLightDirection() const;
private:
	FDirectionalLightProperties LightProperties;
};