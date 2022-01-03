#pragma once
#include "../Component/CameraComponent/CameraComponent.h"

/**
 * static class that keeps a track of the engine state.
 */
class ServiceLocator
{
private:
	ServiceLocator() { };
	static CCameraComponent* ActiveCamera;
public:
	/**
	 * Sets the current active camera
	 */
	static void Provide(CCameraComponent* ActiveCamera);

	/**
	 * Returns the active camera
	 */
	static CCameraComponent* GetActiveCamera();
};