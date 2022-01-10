
#include <iostream>
#include "Engine/ShaderProgram/ShaderProgram.h"
#include "Engine/Window/OpenGLWindow/OpenGLWindow.h"
#include "Engine/Texture/OpenGLTexture/OpenGLTexture.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"
#include "Engine/Component/CameraComponent/CameraComponent.h"
#include "Engine/ServiceLocator/ServiceLocator.h"
#include "Engine/Component/CameraComponent/FreeCameraComponent/FreeCameraComponent.h"

void ProcessInput(COpenGLWindow &InWindow);

const float PlaneVertices[] = {
    // positions				//texture coords s,r
	-0.5f, 0.5f, 0.0f,			0.0f, 1.0f, // left top
	0.5f, 0.5f, 0.0f,			1.0f, 1.0f, // right top
	0.5f, -0.5f, 0.0f,			1.0f, 0.0f, // right bottom 
	-0.5f, -0.5f, 0.0f,			0.0f, 0.0f // left bottom
};

const float CubeVertices[] = {
	// Vertex			  //Texture coords  //Normal
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,	0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	-1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	-1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,	 0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,	0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const float LightCubeVertices[] = {
	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,

	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f, -0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,

	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,

	-0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f, -0.5f,
	 0.5f, -0.5f,  0.5f,
	 0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f,  0.5f,
	-0.5f, -0.5f, -0.5f,

	-0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f, -0.5f,
	 0.5f,  0.5f,  0.5f,
	 0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f, -0.5f,
};





int main()
{
	COpenGLWindow Window(3, 3);
	Window.InitializeWindow("Crespoter Graphics Engine", NULL, NULL, IWindowInterface::WINDOW_MODE::BORDERLESS);
	Window.SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Main Vertex array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	
	// Vertex buffer object for array buffer. Vertex data would be stored here
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);




	// Light VAO
	unsigned int LightVAO;
	glGenVertexArrays(1, &LightVAO);
	glBindVertexArray(LightVAO);


	// Vertex buffer object for array buffer. Vertex data would be stored here
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(LightCubeVertices), LightCubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	glm::vec3 CubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	

	CShaderProgram DefaultShader;
	CShaderProgram LightShader(ShaderConstants::DEFAULT_LIGHT_SHADER);
	DefaultShader.Activate();
	DefaultShader.SetVec3("LightPos", glm::vec3(2.0f, 2.0f, 2.0f));
	
	DefaultShader.SetVec3("Material.Ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	DefaultShader.SetVec3("Material.Diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	DefaultShader.SetVec3("Material.Specular", glm::vec3(0.5f, 0.5f, 0.5f));

	DefaultShader.SetVec3("Light.Ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	DefaultShader.SetVec3("Light.Diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	DefaultShader.SetVec3("Light.Specular", glm::vec3(1.0f, 1.0f, 1.0f));


	DefaultShader.SetFloat("Material.Shininess", 32.0f);
	LightShader.Activate();
	LightShader.SetVec3("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	LightShader.SetVec3("lightColor", glm::vec3(0.0f, 1.0f, 1.0f));

	COpenGLTexture RickRollTexture("Assets/Textures/rickroll.jpg");
	COpenGLTexture BrickTexture("Assets/Textures/brick-wall.jpg");
	glm::mat4 ModelMatrix = glm::mat4(1.0f);





	CGameObject* GameObject[10];

	CGameObject Camera("Camera Game Object");
	Camera.AddComponent<CFreeCameraComponent>();

	CFreeCameraComponent* CameraRef = Camera.GetComponent<CFreeCameraComponent>();
	CTransformationComponent* CameraTransformationComponent = Camera.GetComponent<CTransformationComponent>();
	CameraTransformationComponent->MoveTo(glm::vec3(0.0f, 0.0f, -3.0f));
	
	CFreeCameraComponent::FFreeCameraControlInput CameraControlInput;
	CameraControlInput.CameraMoveSpeed = 0.001f;
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


	for (int i = 0; i < 10; i++)
	{
		GameObject[i] = new CGameObject("Rick roll cube");
		GameObject[i]->AddComponent<CTransformationComponent>();
		GameObject[i]->GetComponent<CTransformationComponent>()->Translate(CubePositions[i]);
	}
	LightGameObject.GetComponent<CTransformationComponent>()->MoveTo(glm::vec3(2.0f, 2.0f, 2.0f));

	// Start for all objects. TODO: Automate
	Camera.Start();
	CameraRef->SetFov(75.0f);

	ServiceLocator::Provide(CameraRef);

	while (!Window.ShouldWindowClose())
	{
		// TODO: Create object loop
		ProcessInput(Window);
		Camera.Update(1.0f);
		LightGameObject.Update(1.0f);

		// ProcessInput(Window, CameraRef);

		Window.SwapBuffers();
		Window.Clear();
		// Bind main VAO, shaders
		DefaultShader.Activate();

		glBindVertexArray(VAO);
		RickRollTexture.BindTexture(&DefaultShader, "Texture", 0);
		BrickTexture.BindTexture(&DefaultShader, "Texture2", 1);

		DefaultShader.SetMat4("ViewMatrix", CameraRef->GetViewMatrix());
		DefaultShader.SetMat4("ProjectionMatrix", CameraRef->GetProjectionMatrix(&Window));
		DefaultShader.SetVec3("ViewPosition", CameraRef->GetParentTransformationComponent()->GetPosition());

		
		for (unsigned int i = 0; i < 10; i++)
		{
			ModelMatrix = GameObject[i]->GetComponent<CTransformationComponent>()->GetModelMatrix();

			ModelMatrix = glm::rotate(ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
			DefaultShader.SetMat4("ModelMatrix", ModelMatrix);
			
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(LightVAO);
		LightShader.Activate();
		LightShader.SetMat4("ViewMatrix", CameraRef->GetViewMatrix());
		LightShader.SetMat4("ProjectionMatrix", CameraRef->GetProjectionMatrix(&Window));
		LightShader.SetMat4("ModelMatrix", LightGameObject.GetComponent<CTransformationComponent>()->GetModelMatrix());
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Uninitialize
		glBindVertexArray(0);
		glfwPollEvents();
	}

	for (int i = 0; i < 10; i++)
		delete GameObject[i];

	return 0;
}


void ProcessInput(COpenGLWindow& InWindow)
{
	if (InWindow.IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		InWindow.CloseWindow();
	}
}
