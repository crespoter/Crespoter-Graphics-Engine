#pragma once
#include <iostream>

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
	const FShaderPathDefinition DEFAULT_SHADER = FShaderPathDefinition("Engine/Shaders/OpenGL Shaders/Default/DefaultVertexShader.vert", "Engine/Shaders/OpenGL Shaders/Default/DefaultFragmentShader.frag");
	const FShaderPathDefinition DEFAULT_LIGHT_SHADER = FShaderPathDefinition("Engine/Shaders/OpenGL Shaders/Light Shaders/LightShader.vert", "Engine/Shaders/OpenGL Shaders/Light Shaders/LightShader.frag");
}
