
#include <iostream>
#include "Engine/ShaderProgram/ShaderProgram.h"
#include "Engine/Window/OpenGLWindow/OpenGLWindow.h"
#include "Engine/Texture/OpenGLTexture/OpenGLTexture.h"
#include <glm/gtc/type_ptr.hpp>
#include "Engine/GameObject/GameObject.h"
#include "Engine/Component/TransformationComponent/TransformationComponent.h"
#include "Engine/Component/CameraComponent/CameraComponent.h"

void ProcessInput(COpenGLWindow &InWindow, CCameraComponent* CameraComponent);

const float PlaneVertices[] = {
    // positions				//texture coords s,r
	-0.5f, 0.5f, 0.0f,			0.0f, 1.0f, // left top
	0.5f, 0.5f, 0.0f,			1.0f, 1.0f, // right top
	0.5f, -0.5f, 0.0f,			1.0f, 0.0f, // right bottom 
	-0.5f, -0.5f, 0.0f,			0.0f, 0.0f // left bottom
};

const float CubeVertices[] = {
	 // Back face
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

};



const unsigned int indices[] = {
	0, 2, 1,   // first triangle
	0, 2, 3    // second triangle
};



int main()
{
	COpenGLWindow Window(3, 3);
	Window.InitializeWindow("Crespoter Graphics Engine", 800, 600, IWindowInterface::WINDOW_MODE::WINDOWED);
	Window.SetClearColor(0.05f, 0.278f, 0.631f, 1.0f);

	// Main Vertex array
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	
	// Vertex buffer object for array buffer. Vertex data would be stored here
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(CubeVertices), CubeVertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


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
	
	// Indices
	// unsigned int EBO;
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	CShaderProgram DefaultShader("Engine/Shaders/OpenGL Shaders/Default/DefaultVertexShader.vert", "Engine/Shaders/OpenGL Shaders/Default/DefaultFragmentShader.frag");

	COpenGLTexture RickRollTexture("Assets/Textures/rickroll.jpg");
	COpenGLTexture BrickTexture("Assets/Textures/brick-wall.jpg");
	glm::mat4 ModelMatrix = glm::mat4(1.0f);



	glm::mat4 ProjectionMatrix = glm::mat4(1.0f);

	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	CGameObject* GameObject[10];

	CGameObject Camera("Camera Game Object");
	Camera.AddComponent<CCameraComponent>();
	Camera.AddComponent<CTransformationComponent>();

	CCameraComponent* CameraRef = Camera.GetComponent<CCameraComponent>();
	CTransformationComponent* CameraTransformationComponent = Camera.GetComponent<CTransformationComponent>();
	CameraTransformationComponent->MoveTo(glm::vec3(0.0f, 0.0f, -3.0f));

	for (int i = 0; i < 10; i++)
	{
		GameObject[i] = new CGameObject("Rick roll");
		GameObject[i]->AddComponent<CTransformationComponent>();
		GameObject[i]->GetComponent<CTransformationComponent>()->Translate(CubePositions[i]);
	}


	// Start for all objects. TODO: Automate
	Camera.Start();


	while (!Window.ShouldWindowClose())
	{
		// TODO: Create object loop
		Camera.Update(0.0f);

		ProcessInput(Window, CameraRef);

		Window.SwapBuffers();
		Window.Clear();
		// Bind main VAO, shaders
		DefaultShader.Activate();

		glBindVertexArray(VAO);
		RickRollTexture.BindTexture(&DefaultShader, "Texture", 0);
		BrickTexture.BindTexture(&DefaultShader, "Texture2", 1);

		DefaultShader.SetMat4("ViewMatrix", CameraRef->GetViewMatrix());
		DefaultShader.SetMat4("ProjectionMatrix", ProjectionMatrix);
		
		
		
		for (unsigned int i = 0; i < 10; i++)
		{
			ModelMatrix = GameObject[i]->GetComponent<CTransformationComponent>()->GetModelMatrix();

			ModelMatrix = glm::rotate(ModelMatrix, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 0.3f, 0.5f));
			DefaultShader.SetMat4("ModelMatrix", ModelMatrix);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}


		// Uninitialize
		glBindVertexArray(0);
		glfwPollEvents();
	}

	for (int i = 0; i < 10; i++)
		delete GameObject[i];

	return 0;
}

void ProcessInput(COpenGLWindow& InWindow, CCameraComponent* CameraComponent)
{
	float CameraSpeed = 0.05f;
	CTransformationComponent* CameraTransformationComponent = CameraComponent->GetParentTransformationComponent();
	glm::vec3 CameraForward = CameraComponent->GetCameraForward();
	glm::vec3 CameraRight = CameraComponent->GetCameraRight();
	if (InWindow.IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		InWindow.CloseWindow();
	}
	if (InWindow.IsKeyPressed(GLFW_KEY_W))
	{ 
		CameraTransformationComponent->Translate(CameraSpeed * CameraForward);
	}
	if (InWindow.IsKeyPressed(GLFW_KEY_S))
	{ 
		CameraTransformationComponent->Translate(-CameraSpeed * CameraForward);
	}
	if (InWindow.IsKeyPressed(GLFW_KEY_A))
	{ 
		CameraTransformationComponent->Translate(-CameraSpeed * CameraRight);
	}
	if (InWindow.IsKeyPressed(GLFW_KEY_D))
	{ 
		CameraTransformationComponent->Translate(CameraSpeed * CameraRight);
	}
}

