#include "Component.h"
#include <assert.h>


IComponent::IComponent(const std::string InComponentName)
{
	assert(InComponentName.length() > 0);
	ComponentName = InComponentName;
}

void IComponent::UpdateParent(CGameObject* InParentGameObject)
{
	assert(InParentGameObject);
	ParentGameObject = InParentGameObject;
}

void IComponent::GetName(std::string& outName) const
{
	outName = ComponentName;
}
