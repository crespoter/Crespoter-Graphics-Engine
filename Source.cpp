
#include <iostream>
#include "Engine/ShaderProgram/ShaderProgram.h"
#include "Engine/Window/OpenGLWindow/OpenGLWindow.h"
#include "Engine/Texture/OpenGLTexture/OpenGLTexture.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"
#include "Engine/Component/CameraComponent/CameraComponent.h"
#include "Engine/Component/CameraComponent/FreeCameraComponent/FreeCameraComponent.h"
#include "Engine/Model/Model.h"

void ProcessInput(COpenGLWindow &InWindow);



int main()
{
	COpenGLWindow Window(3, 3);
	Window.InitializeWindow("Crespoter Graphics Engine", NULL, NULL, IWindowInterface::WINDOW_MODE::WINDOWED);
	Window.SetClearColor(0.0f, 0.5f, 0.0f, 1.0f);


	CModel Backpack("Assets/Models/Backpack/backpack.obj");



	CShaderProgram DefaultShader;
	DefaultShader.Activate();
	DefaultShader.SetVec3("LightPos", glm::vec3(2.0f, 2.0f, 2.0f));
	DefaultShader.SetVec3("Light.Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	DefaultShader.SetVec3("Light.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	DefaultShader.SetVec3("Light.Specular", glm::vec3(1.0f, 1.0f, 1.0f));


	DefaultShader.SetFloat("Material.Shininess", 32.0f);

	glm::mat4 ModelMatrix = glm::mat4(1.0f);




	CGameObject* GameObject[10];

	CGameObject Camera("Camera Game Object");
	Camera.AddComponent<CFreeCameraComponent>();

	CFreeCameraComponent* CameraRef = Camera.GetComponent<CFreeCameraComponent>();
	CTransformationComponent* CameraTransformationComponent = Camera.GetComponent<CTransformationComponent>();
	CameraTransformationComponent->MoveTo(glm::vec3(0.0f, 0.0f, -3.0f));
	
	CFreeCameraComponent::FFreeCameraControlInput CameraControlInput;
	CameraControlInput.CameraMoveSpeed = 0.05f;
	CameraControlInput.MouseSensitivity = 0.1f;
	CameraControlInput.MoveBackwardKey = GLFW_KEY_S;
	CameraControlInput.MoveForwardKey = GLFW_KEY_W;
	CameraControlInput.MoveDownKey = GLFW_KEY_Q;
	CameraControlInput.MoveUpKey = GLFW_KEY_E;
	CameraControlInput.MoveLeftKey = GLFW_KEY_A;
	CameraControlInput.MoveRightKey = GLFW_KEY_D;

	CameraRef->SetupMovementControls(&Window, CameraControlInput);


	CGameObject LightGameObject("Light Sample");
	LightGameObject.AddComponent<CTransformationComponent>();

	LightGameObject.GetComponent<CTransformationComponent>()->MoveTo(glm::vec3(2.0f, 2.0f, 2.0f));

	// Start for all objects. TODO: Automate
	Camera.Start();
	CameraRef->SetFov(75.0f);

	while (!Window.ShouldWindowClose())
	{
		// TODO: Create object loop
		ProcessInput(Window);
		Camera.Update(1.0f);
		LightGameObject.Update(1.0f);


		Window.SwapBuffers();
		Window.Clear();
		// Bind main VAO, shaders
		DefaultShader.Activate();


		DefaultShader.SetMat4("ViewMatrix", CameraRef->GetViewMatrix());
		DefaultShader.SetMat4("ProjectionMatrix", CameraRef->GetProjectionMatrix(&Window));
		DefaultShader.SetVec3("ViewPosition", CameraRef->GetParentTransformationComponent()->GetPosition());
	
		DefaultShader.SetMat4("ModelMatrix", ModelMatrix);


		Backpack.Draw(&DefaultShader);

		glfwPollEvents();
	}
	return 0;
}


void ProcessInput(COpenGLWindow& InWindow)
{
	if (InWindow.IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		InWindow.CloseWindow();
	}
}
