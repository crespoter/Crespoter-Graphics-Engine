#include "PointLightComponent.h"
#include "../../../ServiceLocator/ServiceLocator.h"
#include "../../../Core/ObjectReferenceManager/ObjectReferenceManager.h"
#include "../../../GameObject/GameObject.h"
#include "../../TransformationComponent/TransformationComponent.h"



CPointLightComponent::CPointLightComponent(const std::string& InComponentName) : IComponent(InComponentName) 
{
	ServiceLocator::GetObjectReferenceManager()->AddPointLightComponent(this);
}

CPointLightComponent::~CPointLightComponent()
{
	ServiceLocator::GetObjectReferenceManager() ->RemovePointLightComponent(this);
}

void CPointLightComponent::SetLightProperties(glm::vec3 AmbientColor, glm::vec3 DiffuseColor, glm::vec3 SpecularColor)
{
	LightProperties.AmbientColor = AmbientColor;
	LightProperties.DiffuseColor = DiffuseColor;
	LightProperties.SpecularColor = SpecularColor;
}

void CPointLightComponent::SetLightProperties(const FPointLightProperties &InLightProperties)
{
	LightProperties = InLightProperties;
}

void CPointLightComponent::UpdateLightAttenuationProperty(FLightAttenuation UpdatedLightAttenuation)
{
	LightProperties.LightAttenuation = UpdatedLightAttenuation;
}

void CPointLightComponent::UpdateLightAttenuationProperty(float ConstantCoeff, float LinearCoeff, float QuadraticCoeff)
{
	LightProperties.LightAttenuation.ConstantCoeff = ConstantCoeff;
	LightProperties.LightAttenuation.LinearCoeff = LinearCoeff;
	LightProperties.LightAttenuation.QuadraticCoeff = QuadraticCoeff;
}

glm::vec3 CPointLightComponent::GetAmbientColor()
{
	return LightProperties.AmbientColor;
}

glm::vec3 CPointLightComponent::GetDiffuseColor()
{
	return LightProperties.DiffuseColor;
}

glm::vec3 CPointLightComponent::GetSpecularColor()
{
	return LightProperties.SpecularColor;
}

glm::vec3 CPointLightComponent::GetLightPosition()
{
	return ParentGameObject->GetComponent<CTransformationComponent>()->GetPosition();
}

float CPointLightComponent::GetLinearAttenuationCoeff()
{
	return LightProperties.LightAttenuation.LinearCoeff;
}

float CPointLightComponent::GetConstantAttenuationCoeff()
{
	return LightProperties.LightAttenuation.ConstantCoeff;
}

float CPointLightComponent::GetQuadraticAttenuationCoeff()
{
	return LightProperties.LightAttenuation.QuadraticCoeff;
}

