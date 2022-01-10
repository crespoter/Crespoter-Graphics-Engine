#include "GameObject.h"
#include "../Component/Component.h"
#include "../Component/TransformationComponent/TransformationComponent.h"

CGameObject::CGameObject(const std::string& InName)
{
	Name = InName;
	this->AddComponent<CTransformationComponent>();
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
