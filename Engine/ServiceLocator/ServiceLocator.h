#pragma once

class CCameraComponent;
class CShaderProgram;
class CCore;
class COpenGLWindow;
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
	static void Provide(COpenGLWindow* InWindow);
	static void Provide(CShaderProgram* InMainRenderShaderProgram);

	/**
	 * Returns the active camera
	 */
	static CCameraComponent* GetActiveCamera();

	static CShaderProgram* GetMainShaderProgram();

	static COpenGLWindow* GetWindow();

	static CCore* GetCore();

	static CObjectReferenceManager* GetObjectReferenceManager();

private:
	ServiceLocator() { };
	static CCameraComponent* ActiveCamera;
	static CCore Core;
	static COpenGLWindow* Window;
	static CShaderProgram* MainRenderShader;
	static CObjectReferenceManager ObjectReferenceManager;
};