#pragma once
#include "../Component/CameraComponent/CameraComponent.h"

/**
 * static class that keeps a track of the engine state.
 */
class ServiceLocator
{
public:
	/**
	 * Sets the current active camera
	 */
	static void Provide(CCameraComponent* ActiveCamera);

	/**
	 * Returns the active camera
	 */
	static CCameraComponent* GetActiveCamera();

private:
	ServiceLocator() { };
	static CCameraComponent* ActiveCamera;
};