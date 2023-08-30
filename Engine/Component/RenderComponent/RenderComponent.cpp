#include "RenderComponent.h"
#include "Engine/Model/Model.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Core/ObjectReferenceManager/ObjectReferenceManager.h"
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"

CRenderComponent::CRenderComponent(const std::string& ComponentName) : IComponent(ComponentName)
{
	// TODO: Using an Render System with ECS would be very beneficial here.
	// Moreover, it would help seperate rendering from the update loop to a seperate render function
	// Additionally would help us multithread rendering away from update operation.
	ServiceLocator::GetObjectReferenceManager()->AddRenderComponent(this);
}

CRenderComponent::~CRenderComponent()
{
	ServiceLocator::GetObjectReferenceManager()->RemoveRenderComponent(this);
}

void CRenderComponent::Start()
{
	assert(ParentGameObject);
	ParentTransformationComponent = ParentGameObject->GetComponent<CTransformationComponent>();
	assert(ParentTransformationComponent);
}

void CRenderComponent::SetModel(const std::string& ModelPath)
{
	ModelObject = std::make_unique<CModel>(ModelPath);
}

void CRenderComponent::Render()
{
	ModelObject->Draw(ServiceLocator::GetMainShaderProgram());
}

void CRenderComponent::GetModelMatrix(glm::mat4& outModelmatrix)
{
	assert(ParentTransformationComponent);
	ParentTransformationComponent->GetModelMatrix(outModelmatrix);
}

