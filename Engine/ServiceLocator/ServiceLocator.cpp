#include "ServiceLocator.h"
#include <assert.h>

CCameraComponent* ServiceLocator::ActiveCamera = nullptr;

void ServiceLocator::Provide(CCameraComponent* InActiveCamera)
{
	assert(InActiveCamera != nullptr);
	ActiveCamera = InActiveCamera;
}

CCameraComponent* ServiceLocator::GetActiveCamera()
{
	return ActiveCamera;
}