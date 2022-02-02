#include "RenderComponent.h"
#include "../../Model/Model.h"
#include "../../ServiceLocator/ServiceLocator.h"
#include "../../Core/ObjectReferenceManager/ObjectReferenceManager.h"

CRenderComponent::CRenderComponent(const std::string& ComponentName) : IComponent(ComponentName)
{
	ServiceLocator::GetObjectReferenceManager()->AddRenderComponent(this);
}

CRenderComponent::~CRenderComponent()
{
	delete ModelObject;
	ServiceLocator::GetObjectReferenceManager()->RemoveRenderComponent(this);
}

void CRenderComponent::SetModel(const std::string& ModelPath)
{
	ModelObject = new CModel(ModelPath);
}

void CRenderComponent::Render()
{
	ModelObject->Draw(ServiceLocator::GetMainShaderProgram());
}

