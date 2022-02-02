#include "GameObject.h"
#include "../Component/Component.h"
#include "../Component/TransformationComponent/TransformationComponent.h"
#include "../ServiceLocator/ServiceLocator.h"
#include "../Core/ObjectReferenceManager/ObjectReferenceManager.h"

CGameObject::CGameObject(const std::string& InName)
{
	Name = InName;
	this->AddComponent<CTransformationComponent>();

	// Add game object to reference manager
	ServiceLocator::GetObjectReferenceManager()->AddGameObject(this);
}

CGameObject::~CGameObject()
{
	// Clear memory of all components
	for (auto i = ComponentsList.begin(); i != ComponentsList.end(); i++)
	{
		IComponent* Component = *i;
		delete Component;
	}
	ComponentsList.clear();
	ServiceLocator::GetObjectReferenceManager()->RemoveGameObect(this);
}

void CGameObject::Start()
{
	// Call Start on all components
	for (auto i = ComponentsList.begin(); i != ComponentsList.end(); i++)
	{
		IComponent* Component = *i;
		Component->Start();
	}
}

void CGameObject::Update(float DeltaTime)
{
	// Call update on all components
	for (auto i = ComponentsList.begin(); i != ComponentsList.end(); i++)
	{
		IComponent* Component = *i;
		Component->Update(DeltaTime);
	}
}

void CGameObject::AddComponent(IComponent* InComponent)
{
	assert(InComponent != nullptr);
	ComponentsList.push_back(InComponent);
	InComponent->UpdateParent(this);
}
