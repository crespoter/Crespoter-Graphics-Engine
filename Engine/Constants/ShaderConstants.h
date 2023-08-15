#pragma once
#include <iostream>
#include <glm/glm.hpp>

struct FShaderPathDefinition
{
	FShaderPathDefinition(std::string InVertexShaderPath, std::string InFragmentShaderPath)
	{
		VertexShaderPath = InVertexShaderPath;
		FragmentShaderPath = InFragmentShaderPath;
	}
	std::string VertexShaderPath = "";
	std::string FragmentShaderPath = "";
};

namespace ShaderConstants
{
	const static inline FShaderPathDefinition DEFAULT_SHADER = 
		FShaderPathDefinition("Engine/Shaders/OpenGL Shaders/Default/DefaultVertexShader.vert", "Engine/Shaders/OpenGL Shaders/Default/DefaultFragmentShader.frag");
	const static inline FShaderPathDefinition SKY_BOX_SHADER = 
		FShaderPathDefinition("Engine/Shaders/OpenGL Shaders/Skybox Shaders/SkyboxVertexShader.vert", "Engine/Shaders/OpenGL Shaders/Skybox Shaders/SkyboxFragmentShader.frag");
	const  static inline unsigned int MAX_POINT_LIGHTS = 10;
	const static inline unsigned int MAX_TEXTURES = 10;
	const static inline std::string TEXTURE_NOT_FOUND_TEXTURE = "Engine/Resources/Textures/default.jpg";
	const static inline glm::vec3 DEFAULT_CLEAR_COLOR = glm::vec3(0.0f, 0.5f, 0.0f);
}
