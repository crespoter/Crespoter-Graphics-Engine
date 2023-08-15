#include "DirectionalLightComponent.h"
#include "../../../ServiceLocator/ServiceLocator.h"
#include "../../../Core/ObjectReferenceManager/ObjectReferenceManager.h"

CDirectionalLightComponent::CDirectionalLightComponent(const std::string& ComponentName) : IComponent(ComponentName)
{
	ServiceLocator::GetObjectReferenceManager()->UpdateDirectionalLightComponent(this);
}

CDirectionalLightComponent::~CDirectionalLightComponent()
{
	ServiceLocator::GetObjectReferenceManager()->UpdateDirectionalLightComponent(nullptr);
}

void CDirectionalLightComponent::SetLightProperties(const FDirectionalLightProperties& InLightProperties)
{
	LightProperties = InLightProperties;
}

void CDirectionalLightComponent::SetLightProperties(const glm::vec3& AmbientColor, const glm::vec3& DiffuseColor, const glm::vec3& SpecularColor, const glm::vec3& Direction)
{
	LightProperties.AmbientColor = AmbientColor;
	LightProperties.DiffuseColor = DiffuseColor;
	LightProperties.SpecularColor = SpecularColor;
	LightProperties.LightDirection = Direction;
}

glm::vec3 CDirectionalLightComponent::GetAmbientColor() const
{
	return LightProperties.AmbientColor;
}

glm::vec3 CDirectionalLightComponent::GetDiffuseColor() const
{
	return LightProperties.DiffuseColor;
}

glm::vec3 CDirectionalLightComponent::GetSpecularColor() const
{
	return LightProperties.SpecularColor;
}

glm::vec3 CDirectionalLightComponent::GetLightDirection() const
{
	return LightProperties.LightDirection;
}

