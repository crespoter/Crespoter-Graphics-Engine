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
#include "../Component/LightComponents/PointLightComponent/PointLightComponent.h"
#include "../Component/LightComponents/DirectionalLightComponent/DirectionalLightComponent.h"

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
		MainRenderShader->Activate();

		// TODO: Handle lights automatically

		// Handle Lights
		
		// Directional Light
		if (ObjectReferenceManager->DirectionalLightComponent == nullptr)
		{
			MainRenderShader->SetBool("DirectionalLight.bIsActive", false);
		}
		else
		{
			MainRenderShader->SetBool("DirectionalLight.bIsActive", true);
			MainRenderShader->SetVec3("DirectionalLight.Ambient", ObjectReferenceManager->DirectionalLightComponent->GetAmbientColor());
			MainRenderShader->SetVec3("DirectionalLight.Diffuse", ObjectReferenceManager->DirectionalLightComponent->GetDiffuseColor());
			MainRenderShader->SetVec3("DirectionalLight.Specular", ObjectReferenceManager->DirectionalLightComponent->GetSpecularColor());
			MainRenderShader->SetVec3("DirectionalLight.Direction", ObjectReferenceManager->DirectionalLightComponent->GetLightDirection());
		}

		// Point Lights
		int Count = 0;
		for (auto i = ObjectReferenceManager->PointLightComponents.begin(); i != ObjectReferenceManager->PointLightComponents.end(); i++)
		{
			std::string PointLightUniformPrefix = "PointLights[" + std::to_string(Count) + "]";
			CPointLightComponent* PointLightComponent = *i;
			MainRenderShader->SetVec3(PointLightUniformPrefix + ".Ambient", PointLightComponent->GetAmbientColor());
			MainRenderShader->SetVec3(PointLightUniformPrefix + ".Diffuse", PointLightComponent->GetDiffuseColor());
			MainRenderShader->SetVec3(PointLightUniformPrefix + ".Specular", PointLightComponent->GetSpecularColor());
			
			MainRenderShader->SetVec3(PointLightUniformPrefix + ".LightPos", PointLightComponent->GetLightPosition());

			MainRenderShader->SetFloat(PointLightUniformPrefix + ".Attenuation.ConstantCoeff", PointLightComponent->GetConstantAttenuationCoeff());
			MainRenderShader->SetFloat(PointLightUniformPrefix + ".Attenuation.LinearCoeff", PointLightComponent->GetLinearAttenuationCoeff());
			MainRenderShader->SetFloat(PointLightUniformPrefix + ".Attenuation.QuadraticCoeff", PointLightComponent->GetQuadraticAttenuationCoeff());
			
			Count++;
		}
		MainRenderShader->SetInteger("PointLightCount", Count);

		// Handle all render objects
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