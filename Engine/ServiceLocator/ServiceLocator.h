#pragma once

class CCameraComponent;
class LightManager;

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
	static LightManager* LightManager;
};