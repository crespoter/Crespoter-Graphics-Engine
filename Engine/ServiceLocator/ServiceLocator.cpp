#include "ServiceLocator.h"

CCameraComponent* ServiceLocator::ActiveCamera = nullptr;

void ServiceLocator::Provide(CCameraComponent* ActiveCamera)
{
	assert(ActiveCamera != nullptr);
}

CCameraComponent* ServiceLocator::GetActiveCamera()
{
	if (!ActiveCamera)
	{
		throw std::runtime_error("Error getting active camera: Active Camera is not set");
	}
	return ActiveCamera;
}

