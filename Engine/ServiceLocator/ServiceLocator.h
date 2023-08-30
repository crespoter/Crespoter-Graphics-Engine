#pragma once

class CCameraComponent;
class CShaderProgram;
class CCore;
class IWindowInterface;
class CObjectReferenceManager;

/**
 * static class that keeps a track of the engine state.
 */
class ServiceLocator
{
public:
	/**
	 * Provides
	 */
	static void Provide(CCameraComponent* ActiveCamera);
	static void Provide(IWindowInterface* InWindow);
	static void Provide(CShaderProgram* InMainRenderShaderProgram);

	/**
	 * Returns the active camera
	 */
	static CCameraComponent* GetActiveCamera();

	static CShaderProgram* GetMainShaderProgram();

	static IWindowInterface* GetWindow();

	static CCore* GetCore();

	static CObjectReferenceManager* GetObjectReferenceManager();


private:
	ServiceLocator() { };
	static CCameraComponent* ActiveCamera;
	static CCore Core;
	static IWindowInterface* Window;
	static CShaderProgram* MainRenderShader;
	static CObjectReferenceManager ObjectReferenceManager;
};