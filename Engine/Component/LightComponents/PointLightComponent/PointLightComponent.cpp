#include "PointLightComponent.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Core/ObjectReferenceManager/ObjectReferenceManager.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"



CPointLightComponent::CPointLightComponent(const std::string& InComponentName) : IComponent(InComponentName) 
{
	ServiceLocator::GetObjectReferenceManager()->AddPointLightComponent(this);
}

void CPointLightComponent::Start()
{
	ParentTransformationComponent = ParentGameObject->GetComponent<CTransformationComponent>();
	assert(ParentTransformationComponent);
}

CPointLightComponent::~CPointLightComponent()
{
	ServiceLocator::GetObjectReferenceManager() ->RemovePointLightComponent(this);
}

void CPointLightComponent::SetLightProperties(const glm::vec3& AmbientColor, const glm::vec3& DiffuseColor, const glm::vec3& SpecularColor)
{
	LightProperties.AmbientColor = AmbientColor;
	LightProperties.DiffuseColor = DiffuseColor;
	LightProperties.SpecularColor = SpecularColor;
}

void CPointLightComponent::SetLightProperties(const FPointLightProperties &InLightProperties)
{
	LightProperties = InLightProperties;
}

void CPointLightComponent::UpdateLightAttenuationProperty(const FLightAttenuation& UpdatedLightAttenuation)
{
	LightProperties.LightAttenuation = UpdatedLightAttenuation;
}

void CPointLightComponent::UpdateLightAttenuationProperty(const float ConstantCoeff, const float LinearCoeff, const float QuadraticCoeff)
{
	LightProperties.LightAttenuation.ConstantCoeff = ConstantCoeff;
	LightProperties.LightAttenuation.LinearCoeff = LinearCoeff;
	LightProperties.LightAttenuation.QuadraticCoeff = QuadraticCoeff;
}

glm::vec3 CPointLightComponent::GetAmbientColor() const
{
	return LightProperties.AmbientColor;
}

glm::vec3 CPointLightComponent::GetDiffuseColor() const
{
	return LightProperties.DiffuseColor;
}

glm::vec3 CPointLightComponent::GetSpecularColor() const
{
	return LightProperties.SpecularColor;
}

glm::vec3 CPointLightComponent::GetLightPosition() const
{
	assert(ParentTransformationComponent);
	return ParentTransformationComponent->GetPosition();
}

float CPointLightComponent::GetLinearAttenuationCoeff() const
{
	return LightProperties.LightAttenuation.LinearCoeff;
}

float CPointLightComponent::GetConstantAttenuationCoeff() const
{
	return LightProperties.LightAttenuation.ConstantCoeff;
}

float CPointLightComponent::GetQuadraticAttenuationCoeff() const
{
	return LightProperties.LightAttenuation.QuadraticCoeff;
}

