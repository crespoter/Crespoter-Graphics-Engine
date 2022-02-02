#include "Core.h"
#include "../Window/OpenGLWindow/OpenGLWindow.h"
#include "../Configurations/Config.h"
#include "../Constants/ShaderConstants.h"
#include "../ServiceLocator/ServiceLocator.h"
#include "../ShaderProgram/ShaderProgram.h"
#include "../GameObject/GameObject.h"
#include "ObjectReferenceManager/ObjectReferenceManager.h"
#include "../Component/RenderComponent/RenderComponent.h"
#include "../Component/CameraComponent/CameraComponent.h"
#include "../Component/TransformationComponent/TransformationComponent.h"

CCore::CCore()
{
	// Initialize Window
	Window = new COpenGLWindow(3, 3);
	Window->InitializeWindow(ENGINE_CONFIG::WINDOW_NAME, NULL, NULL, ENGINE_CONFIG::WINDOW_MODE);
	Window->SetClearColor(ShaderConstants::DEFAULT_CLEAR_COLOR.x, ShaderConstants::DEFAULT_CLEAR_COLOR.y, ShaderConstants::DEFAULT_CLEAR_COLOR.z, 1.0f);
	
	//Initialize Main Shader
	MainRenderShader = new CShaderProgram();


	// Register in provider
	ServiceLocator::Provide(Window);
	ServiceLocator::Provide(MainRenderShader);
}

CCore::~CCore()
{
	// Deinitialize in reverse order of initialization
	delete MainRenderShader;
	delete Window;
}

void CCore::StartEngine()
{
	CObjectReferenceManager* ObjectReferenceManager =  ServiceLocator::GetObjectReferenceManager();
	LastTime = (float)glfwGetTime();

	while (!Window->ShouldWindowClose())
	{	
		Window->SwapBuffers();
		Window->Clear();
		float CurrentTime = (float)glfwGetTime();
		float DeltaTime = CurrentTime - LastTime;
		LastTime = CurrentTime;
		// Game object loop
		for (auto i = ObjectReferenceManager->GameObjects.begin(); i != ObjectReferenceManager->GameObjects.end(); i++)
		{
			CGameObject* GameObject = *i;
			if (!GameObject->bIsInitialized)
			{
				GameObject->Start();
				GameObject->bIsInitialized = true;
			}
			GameObject->Update(DeltaTime);
		}

		// Main Rendering loop

		// TODO: Handle lights automatically
		MainRenderShader->Activate();
		MainRenderShader->SetVec3("LightPos", glm::vec3(2.0f, 10.0f, 2.0f));
		MainRenderShader->SetVec3("Light.Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		MainRenderShader->SetVec3("Light.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		MainRenderShader->SetVec3("Light.Specular", glm::vec3(1.0f, 1.0f, 1.0f));
		CCameraComponent* CameraComponent = ServiceLocator::GetActiveCamera();

		for (auto i = ObjectReferenceManager->RenderComponents.begin(); i != ObjectReferenceManager->RenderComponents.end(); i++)
		{
			MainRenderShader->SetMat4("ViewMatrix", CameraComponent->GetViewMatrix());
			MainRenderShader->SetMat4("ProjectionMatrix", CameraComponent->GetProjectionMatrix(Window));
			MainRenderShader->SetVec3("ViewPosition", CameraComponent->GetParentTransformationComponent()->GetPosition());

			MainRenderShader->SetMat4("ModelMatrix", glm::mat4(1.0f));
			
			CRenderComponent* RenderComponent = *i;
			RenderComponent->Render();
		}
		glfwPollEvents();
	}
}